/* stkvl2.c
 * Input file:  stack-eval2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "stkvl2.h"


static Object Qthere_exists_literal;  /* there-exists-literal */

static Object string_constant;     /* "there exists parse converter" */

static Object string_constant_1;   /* "The iteration reference in ~NE cannot be compiled, since there is ~
				    *             no local name or class name in the designation which can be used ~
				    *             for later reference."
				    */

static Object string_constant_2;   /* "The iteration reference in ~NE could not be compiled because no ~
				    *             type can be deduced from the reference."
				    */

static Object Qitem_or_datum;      /* item-or-datum */

static Object string_constant_3;   /* "Type mismatch between the local name ~A and the type ~
				    *                        ~NT referenced by the THERE EXISTS form iteration."
				    */

static Object Qindexed_attribute;  /* indexed-attribute */

/* THERE-EXISTS-LITERAL-STACK-NODE-CONVERTER */
Object there_exists_literal_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, scope, logical_expression, sub_class_bit_vector;
    Object compiling_procedures_qm, role, domain_list, simple_role, type_qm;
    Object local_name_qm, naming_element_qm, binding, instruction_node, temp;
    Object var_spot_qm, var_spot_type_1;
    Object possible_indexed_attribute_expression_qm;
    Object possible_indexed_attribute_qm, indexed_attribute_new_domain_qm;
    Object temp_1, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, svref_new_value, actual_role;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(208,0);
    gensymed_symbol = expression;
    gensymed_symbol = CDR(gensymed_symbol);
    scope = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    logical_expression = CAR(gensymed_symbol);
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
	compiling_procedures_qm = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
    }
    else
	compiling_procedures_qm = Nil;
    role = CAR(scope);
    domain_list = compiling_procedures_qm ? CDR(scope) : CDDR(scope);
    simple_role = simple_role_of_role(role);
    type_qm = SYMBOLP(simple_role) ? 
	    make_class_type_specification(simple_role) : 
	    type_specification_of_role(simple_role);
    local_name_qm = compiling_procedures_qm ? 
	    get_explicitly_specified_local_name_of_role_if_any(role) : 
	    SECOND(scope);
    naming_element_qm = atomic_naming_element_of_role(role);
    binding = local_name_qm;
    if (binding);
    else
	binding = phrase_list_2(Qthe,naming_element_qm);
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qthere_exists_literal,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    if ( !(local_name_qm || naming_element_qm))
	compiler_bug(3,string_constant,string_constant_1,expression);
    else if ( !TRUEP(type_qm)) {
	compiler_bug(3,string_constant,string_constant_2,expression);
	type_qm = Qitem_or_datum;
	temp = phrase_cons(binding,
		generate_new_stack_frame_var_spot(Qitem_or_datum));
	Expression_bound_local_names = phrase_cons(temp,
		Expression_bound_local_names);
    }
    else {
	var_spot_qm = resolve_stack_name_reference(binding);
	var_spot_type_1 = Nil;
	possible_indexed_attribute_expression_qm = 
		expression_may_use_indexed_attribute_p(expression);
	if (possible_indexed_attribute_expression_qm) {
	    temp = SECOND(possible_indexed_attribute_expression_qm);
	    possible_indexed_attribute_qm = SECOND(temp);
	}
	else
	    possible_indexed_attribute_qm = Nil;
	indexed_attribute_new_domain_qm = possible_indexed_attribute_qm ? 
		THIRD(possible_indexed_attribute_expression_qm) : Nil;
	if (valid_var_spot_p(var_spot_qm))
	    var_spot_type_1 = var_spot_type(var_spot_qm,
		    Lexically_visible_code_bodies);
	else
	    var_spot_qm = Nil;
	if ( !TRUEP(var_spot_qm) && compiling_procedures_qm && local_name_qm) {
	    var_spot_type_1 = type_qm;
	    var_spot_qm = generate_new_variable_spot(2,type_qm,local_name_qm);
	}
	else if ( !TRUEP(var_spot_qm)) {
	    var_spot_type_1 = type_qm;
	    var_spot_qm = generate_new_stack_frame_var_spot(var_spot_type_1);
	    Expression_bound_local_names = phrase_cons(phrase_cons(binding,
		    var_spot_qm),Expression_bound_local_names);
	}
	else if ( !TRUEP(var_spot_type_1) ||  
		!TRUEP(type_specifications_could_intersect_p(type_qm,
		var_spot_type_1)))
	    compiler_error(3,string_constant_3,binding,type_qm);
	temp_1 = convert_expression_to_stack_node_tree(logical_expression);
	if (possible_indexed_attribute_qm)
	    temp = indexed_attribute_new_domain_qm ? 
		    stack_cons_1(convert_expression_to_stack_node_tree(indexed_attribute_new_domain_qm),
		    Nil) : Nil;
	else {
	    domain = Nil;
	    ab_loop_list_ = domain_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    domain = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    stack_cons_1(convert_expression_to_stack_node_tree(domain),
		    Nil);
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
	}
	svref_new_value = stack_cons_1(temp_1,temp);
	SVREF(instruction_node,FIX((SI_Long)2L)) = svref_new_value;
	actual_role = possible_indexed_attribute_qm ? 
		phrase_list_3(Qindexed_attribute,
		possible_indexed_attribute_qm,simple_role) : simple_role;
	svref_new_value = phrase_list_3(actual_role,var_spot_qm,
		var_spot_type_1);
	SVREF(instruction_node,FIX((SI_Long)12L)) = svref_new_value;
    }
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object Qtruth_value;        /* truth-value */

/* THERE-EXISTS-LITERAL-I-CHOOSER */
Object there_exists_literal_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,1);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    Qtruth_value,Qtruth_value,Nil,FIX((SI_Long)3L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qrequired_domain_types_of_role;  /* required-domain-types-of-role */

static Object Qab_class;           /* class */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object string_constant_4;   /* " requires ~a arguments, but instead received ~a" */

static Object Qdatum;              /* datum */

/* AGGREGATOR-INSTRUCTION-CHOOSER */
Object aggregator_instruction_chooser(stack_node_instruction,required_type,
	    result_type,iteration_type,generate_iteration_local_var_qm,
	    length_of_persistent_info)
    Object stack_node_instruction, required_type, result_type, iteration_type;
    Object generate_iteration_local_var_qm, length_of_persistent_info;
{
    Object extra_info, extra_info_length, role, unknown_allowed_qm;
    Object no_item_allowed_qm, no_item_implies_unknown_allowed_qm;
    Object argument_nodes, domain_node_list, unknown_argument_qm;
    Object gensymed_symbol, required_domain_type_list, original_role;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, domain_node_cons;
    Object required_domain_type, actual_type, temp_1, temp_2, temp_3, temp_4;
    Object temp_5;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_repeat_;
    char temp;
    Declare_special(5);

    x_note_fn_call(208,2);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    extra_info_length = length(extra_info);
    role = FIRST(extra_info);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    domain_node_list = CDR(argument_nodes);
    unknown_argument_qm = Nil;
    if ( !SYMBOLP(role)) {
	gensymed_symbol = role_name_of_role(role);
	required_domain_type_list = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qrequired_domain_types_of_role);
    }
    else
	required_domain_type_list = Nil;
    if (SYMBOLP(role) &&  !TRUEP(domain_node_list))
	record_free_reference(Qab_class,role);
    else {
	if (CONSP(role) && EQ(FIRST(role),Qindexed_attribute)) {
	    original_role = THIRD(role);
	    if (SYMBOLP(original_role))
		record_free_reference(Qab_class,original_role);
	    else
		record_free_references_of_role(1,original_role);
	}
	record_free_references_of_role(1,role);
    }
    if (FIXNUM_NE(length(required_domain_type_list),
		length(domain_node_list))) {
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
		  twrite_compiler_message_header();
		  twrite_beginning_of_wide_string(array_constant,
			  FIX((SI_Long)9L));
		  print_role(role);
		  tformat(3,string_constant_4,
			  length(required_domain_type_list),
			  length(domain_node_list));
		  candidate_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	a_string = Nil;
	ab_loop_list_ = Compiler_errors;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	a_string = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_eq_w(a_string,candidate_string)) {
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	if (temp)
	    reclaim_text_string(candidate_string);
	else
	    Compiler_errors = phrase_cons(candidate_string,Compiler_errors);
	ab_loop_repeat_ = IFIX(length(domain_node_list));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(Qitem_or_datum,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	required_domain_type_list = ab_loopvar_;
	goto end_2;
	required_domain_type_list = Qnil;
      end_2:;
    }
    domain_node_cons = domain_node_list;
    required_domain_type = Nil;
    ab_loop_list_ = required_domain_type_list;
    actual_type = Nil;
  next_loop_2:
    if ( !TRUEP(domain_node_cons))
	goto end_loop_2;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    required_domain_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    actual_type = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(maybe_add_no_item(required_domain_type,
	    no_item_allowed_qm),unknown_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    temp_1 = choose_stack_node_instructions_and_types(2,
	    CAR(domain_node_cons),actual_type);
    M_CAR(domain_node_cons) = temp_1;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(domain_node_cons),(SI_Long)6L)))
	unknown_argument_qm = T;
    domain_node_cons = M_CDR(domain_node_cons);
    goto next_loop_2;
  end_loop_2:;
    temp_1 = choose_stack_node_instructions_and_types(2,
	    CAR(argument_nodes),
	    maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(iteration_type,
	    unknown_allowed_qm),no_item_allowed_qm),
	    no_item_implies_unknown_allowed_qm));
    M_CAR(argument_nodes) = temp_1;
    if (type_specification_subtype_p(list_constant,
	    ISVREF(CAR(argument_nodes),(SI_Long)6L)))
	unknown_argument_qm = T;
    temp_1 = maybe_add_unknown(result_type,unknown_argument_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp_1;
    if (unknown_argument_qm) {
	temp_2 = IFIX(extra_info_length) == 
		IFIX(length_of_persistent_info) + (SI_Long)4L ? T : Nil;
	if (temp_2)
	    return VALUES_1(temp_2);
	else {
	    if (FIXNUM_EQ(length_of_persistent_info,extra_info_length));
	    else if (IFIX(length_of_persistent_info) == (SI_Long)2L)
		extra_info = phrase_list_2(FIRST(extra_info),
			SECOND(extra_info));
	    else if (IFIX(length_of_persistent_info) == (SI_Long)3L)
		extra_info = phrase_list_3(FIRST(extra_info),
			SECOND(extra_info),THIRD(extra_info));
	    else;
	    temp_3 = extra_info;
	    temp_4 = 
		    generate_new_stack_frame_var_spot(make_type_specification_for_iteration_state());
	    temp_5 = generate_iteration_local_var_qm ? 
		    generate_new_stack_frame_var_spot(EQ(generate_iteration_local_var_qm,
		    T) ? ISVREF(CAR(argument_nodes),(SI_Long)6L) : 
		    generate_iteration_local_var_qm) : Nil;
	    temp_2 = generate_new_stack_frame_var_spot(Qdatum);
	    temp_1 = nconc2(temp_3,phrase_list_4(temp_4,temp_5,temp_2,
		    generate_new_stack_frame_var_spot(Qdatum)));
	    return VALUES_1(SVREF(stack_node_instruction,
		    FIX((SI_Long)12L)) = temp_1);
	}
    }
    else {
	temp_2 = IFIX(extra_info_length) == 
		IFIX(length_of_persistent_info) + (SI_Long)2L ? T : Nil;
	if (temp_2)
	    return VALUES_1(temp_2);
	else {
	    if (FIXNUM_EQ(length_of_persistent_info,extra_info_length));
	    else if (IFIX(length_of_persistent_info) == (SI_Long)2L)
		extra_info = phrase_list_2(FIRST(extra_info),
			SECOND(extra_info));
	    else if (IFIX(length_of_persistent_info) == (SI_Long)3L)
		extra_info = phrase_list_3(FIRST(extra_info),
			SECOND(extra_info),THIRD(extra_info));
	    else;
	    temp_5 = extra_info;
	    temp_2 = 
		    generate_new_stack_frame_var_spot(make_type_specification_for_iteration_state());
	    temp_1 = nconc2(temp_5,phrase_list_2(temp_2,
		    generate_iteration_local_var_qm ? 
		    generate_new_stack_frame_var_spot(EQ(generate_iteration_local_var_qm,
		    T) ? ISVREF(CAR(argument_nodes),(SI_Long)6L) : 
		    generate_iteration_local_var_qm) : Nil));
	    return VALUES_1(SVREF(stack_node_instruction,
		    FIX((SI_Long)12L)) = temp_1);
	}
    }
}

static Object Qpush_constant;      /* push-constant */

/* THERE-EXISTS-LITERAL-I-EMIT */
Object there_exists_literal_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object gensymed_symbol, role, value_spot, value_spot_type;
    Object continuation_spot, expiration_var_qm;
    Object cached_global_expiration_var_qm, argument_nodes, logical_expression;
    Object domain_list_qm, role_type_qm, evaluation_value;
    Object default_logical_expression_qm, domain_ok_tag, value_served_tag;
    Object known_value_tag, true_value_tag, end_of_instruction_tag, domain;
    Object ab_loop_list_, possible_unknown_domain_qm, ab_loop_iter_flag_;
    SI_Long count_1;
    char unknown_allowed_qm;

    x_note_fn_call(208,3);
    gensymed_symbol = extra_info;
    role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    cached_global_expiration_var_qm = CAR(gensymed_symbol);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    logical_expression = FIRST(argument_nodes);
    domain_list_qm = CDR(argument_nodes);
    role_type_qm = SYMBOLP(role) ? make_class_type_specification(role) : 
	    type_specification_of_role(role);
    unknown_allowed_qm =  ! !TRUEP(cached_global_expiration_var_qm);
    if (EQ(ISVREF(logical_expression,(SI_Long)1L),Qpush_constant)) {
	evaluation_value = ISVREF(logical_expression,(SI_Long)12L);
	default_logical_expression_qm = CONSP(evaluation_value) && 
		EQ(M_CDR(evaluation_value),Qtruth_value) ? 
		(EQ(M_CAR(ISVREF(logical_expression,(SI_Long)12L)),Truth) ?
		 T : Nil) : Nil;
    }
    else
	default_logical_expression_qm = Nil;
    domain_ok_tag = generate_new_goto_tag();
    value_served_tag = generate_new_goto_tag();
    known_value_tag = generate_new_goto_tag();
    true_value_tag = generate_new_goto_tag();
    end_of_instruction_tag = generate_new_goto_tag();
    if (unknown_allowed_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
    }
    emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
    if (domain_list_qm) {
	domain = Nil;
	ab_loop_list_ = domain_list_qm;
	possible_unknown_domain_qm = Nil;
	count_1 = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	possible_unknown_domain_qm = 
		type_specification_subtype_p(list_constant,
		ISVREF(stack_node_instruction,(SI_Long)6L));
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	emit_stack_node_tree(byte_code_stream,domain);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (possible_unknown_domain_qm) {
	    emit_branch_long_if_known_byte_codes(byte_code_stream,
		    domain_ok_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,domain_ok_tag);
	}
	emit_open_role_iteration_byte_codes(byte_code_stream,role,
		end_of_instruction_tag,default_logical_expression_qm ? 
		FIX((SI_Long)0L) : FIX(count_1));
    }
    else
	emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,
		role,end_of_instruction_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    register_tag_in_byte_code_stream(2,byte_code_stream,value_served_tag);
    if ( !(role_type_qm && type_specification_subtype_p(role_type_qm,
	    value_spot_type)))
	emit_type_check_byte_codes(byte_code_stream,value_spot_type);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    emit_stack_node_tree(byte_code_stream,logical_expression);
    if (unknown_allowed_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_value_tag);
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)80L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
    emit_branch_long_if_true_byte_codes(byte_code_stream,true_value_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,end_of_instruction_tag);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_instruction_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    register_tag_in_byte_code_stream(2,byte_code_stream,true_value_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    emit_close_iteration_byte_codes(byte_code_stream,continuation_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FOR-EVERY-LITERAL-STACK-NODE-CONVERTER */
Object for_every_literal_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,4);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

static Object string_constant_5;   /* "aggregator parse converter" */

static Object string_constant_6;   /* "The iteration reference in ~NE cannot be compiled, since there is ~
				    *             no local name or class name in the designation which can be used ~
				    *             as a binding reference."
				    */

/* AGGREGATOR-SPECIAL-FORM-CONVERTER */
Object aggregator_special_form_converter(expression)
    Object expression;
{
    Object gensymed_symbol, stack_node_operation, scope, iteration_expression;
    Object sub_class_bit_vector, compiling_procedures_qm, role, domain_list;
    Object simple_role, type_qm, local_name_qm, naming_element_qm, binding;
    Object instruction_node, temp, var_spot;
    Object possible_indexed_attribute_expression_qm;
    Object possible_indexed_attribute_qm, indexed_attribute_new_domain_qm;
    Object temp_1, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, svref_new_value, actual_role;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(208,5);
    gensymed_symbol = expression;
    stack_node_operation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    scope = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    iteration_expression = CAR(gensymed_symbol);
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
	compiling_procedures_qm = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
    }
    else
	compiling_procedures_qm = Nil;
    role = CAR(scope);
    domain_list = compiling_procedures_qm ? CDR(scope) : CDDR(scope);
    simple_role = simple_role_of_role(role);
    type_qm = SYMBOLP(simple_role) ? 
	    make_class_type_specification(simple_role) : 
	    type_specification_of_role(simple_role);
    local_name_qm = compiling_procedures_qm ? 
	    get_explicitly_specified_local_name_of_role_if_any(role) : 
	    SECOND(scope);
    naming_element_qm = atomic_naming_element_of_role(role);
    binding = local_name_qm;
    if (binding);
    else
	binding = phrase_list_2(Qthe,naming_element_qm);
    gensymed_symbol = make_stack_node_instruction_1_1(stack_node_operation,
	    Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    if ( !(local_name_qm || naming_element_qm))
	compiler_bug(3,string_constant_5,string_constant_6,expression);
    else if ( !TRUEP(type_qm)) {
	compiler_bug(3,string_constant_5,string_constant_2,expression);
	temp = phrase_cons(binding,
		generate_new_stack_frame_var_spot(Qitem_or_datum));
	Expression_bound_local_names = phrase_cons(temp,
		Expression_bound_local_names);
    }
    else {
	var_spot = generate_new_stack_frame_var_spot(type_qm);
	possible_indexed_attribute_expression_qm = 
		expression_may_use_indexed_attribute_p(expression);
	if (possible_indexed_attribute_expression_qm) {
	    temp = SECOND(possible_indexed_attribute_expression_qm);
	    possible_indexed_attribute_qm = SECOND(temp);
	}
	else
	    possible_indexed_attribute_qm = Nil;
	indexed_attribute_new_domain_qm = possible_indexed_attribute_qm ? 
		THIRD(possible_indexed_attribute_expression_qm) : Nil;
	Expression_bound_local_names = phrase_cons(phrase_cons(binding,
		var_spot),Expression_bound_local_names);
	temp_1 = convert_expression_to_stack_node_tree(iteration_expression);
	if (possible_indexed_attribute_qm)
	    temp = indexed_attribute_new_domain_qm ? 
		    stack_cons_1(convert_expression_to_stack_node_tree(indexed_attribute_new_domain_qm),
		    Nil) : Nil;
	else {
	    domain = Nil;
	    ab_loop_list_ = domain_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    domain = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    stack_cons_1(convert_expression_to_stack_node_tree(domain),
		    Nil);
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
	}
	svref_new_value = stack_cons_1(temp_1,temp);
	SVREF(instruction_node,FIX((SI_Long)2L)) = svref_new_value;
	actual_role = possible_indexed_attribute_qm ? 
		phrase_list_3(Qindexed_attribute,
		possible_indexed_attribute_qm,simple_role) : simple_role;
	svref_new_value = phrase_list_2(actual_role,var_spot);
	SVREF(instruction_node,FIX((SI_Long)12L)) = svref_new_value;
    }
    return VALUES_1(instruction_node);
}

/* FOR-EVERY-LITERAL-I-CHOOSER */
Object for_every_literal_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,6);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    Qtruth_value,Qtruth_value,Nil,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FOR-EVERY-LITERAL-I-EMIT */
Object for_every_literal_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object gensymed_symbol, simple_role, value_spot, continuation_spot;
    Object expiration_var_qm, cached_global_expiration_var_qm, argument_nodes;
    Object logical_expression, domain_list_qm, domain_ok_tag, value_served_tag;
    Object known_value_tag, false_value_tag, end_of_instruction_tag, domain;
    Object ab_loop_list_, possible_unknown_domain_qm, ab_loop_iter_flag_;
    SI_Long count_1;
    char unknown_allowed_qm;

    x_note_fn_call(208,7);
    gensymed_symbol = extra_info;
    simple_role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    cached_global_expiration_var_qm = CAR(gensymed_symbol);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    logical_expression = FIRST(argument_nodes);
    domain_list_qm = CDR(argument_nodes);
    unknown_allowed_qm =  ! !TRUEP(cached_global_expiration_var_qm);
    domain_ok_tag = generate_new_goto_tag();
    value_served_tag = generate_new_goto_tag();
    known_value_tag = generate_new_goto_tag();
    false_value_tag = generate_new_goto_tag();
    end_of_instruction_tag = generate_new_goto_tag();
    if (unknown_allowed_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
    }
    emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
    if (domain_list_qm) {
	domain = Nil;
	ab_loop_list_ = domain_list_qm;
	possible_unknown_domain_qm = Nil;
	count_1 = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	possible_unknown_domain_qm = 
		type_specification_subtype_p(list_constant,
		ISVREF(stack_node_instruction,(SI_Long)6L));
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	emit_stack_node_tree(byte_code_stream,domain);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (possible_unknown_domain_qm) {
	    emit_branch_long_if_known_byte_codes(byte_code_stream,
		    domain_ok_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,domain_ok_tag);
	}
	emit_open_role_iteration_byte_codes(byte_code_stream,simple_role,
		end_of_instruction_tag,FIX(count_1));
    }
    else
	emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,
		simple_role,end_of_instruction_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    register_tag_in_byte_code_stream(2,byte_code_stream,value_served_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    emit_stack_node_tree(byte_code_stream,logical_expression);
    if (unknown_allowed_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_value_tag);
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)79L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
    emit_branch_long_if_false_byte_codes(byte_code_stream,false_value_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,end_of_instruction_tag);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_instruction_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    register_tag_in_byte_code_stream(2,byte_code_stream,false_value_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    emit_close_iteration_byte_codes(byte_code_stream,continuation_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qexists;             /* exists */

/* EXISTS-STACK-NODE-CONVERTER */
Object exists_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, svref_new_value;

    x_note_fn_call(208,8);
    gensymed_symbol = make_stack_node_instruction_1_1(Qexists,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    svref_new_value = 
	    stack_cons_1(convert_expression_to_stack_node_tree(SECOND(expression)),
	    Nil);
    SVREF(instruction_node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qboolean;            /* boolean */

/* EXISTS-I-CHOOSER */
Object exists_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, temp;

    x_note_fn_call(208,9);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    temp = choose_stack_node_instructions_and_types(2,
	    FIRST(argument_nodes),
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(list_constant_3,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm));
    M_FIRST(argument_nodes) = temp;
    temp = type_specification_subtype_p(list_constant,
	    ISVREF(FIRST(argument_nodes),(SI_Long)6L)) ? list_constant_4 : 
	    Qboolean;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EXISTS-I-EMIT */
Object exists_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp;

    x_note_fn_call(208,10);
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(temp));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qexists);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* FUNCALL-EXISTS-INST */
Object funcall_exists_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object item_or_datum_arg_qm, result_1, x2;
    char temp;

    x_note_fn_call(208,11);
    item_or_datum_arg_qm = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !TRUEP(item_or_datum_arg_qm))
	result_1 = Evaluation_false_value;
    else {
	if (SIMPLE_VECTOR_P(item_or_datum_arg_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_arg_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_datum_arg_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_datum_arg_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  !TRUEP(serve_item_p(item_or_datum_arg_qm)) : TRUEP(Nil))
	    result_1 = Evaluation_false_value;
	else
	    result_1 = Evaluation_true_value;
    }
    if ( !(FIXNUMP(item_or_datum_arg_qm) || SYMBOLP(item_or_datum_arg_qm) 
	    || SIMPLE_VECTOR_P(item_or_datum_arg_qm)))
	reclaim_if_evaluation_value_1(item_or_datum_arg_qm);
    SVREF(local_stack,top_of_stack) = result_1;
    return VALUES_1(Nil);
}

static Object Qsum;                /* sum */

static Object Qproduct;            /* product */

static Object string_constant_7;   /* "aggregator emitter" */

static Object string_constant_8;   /* "Missing accumular operator type." */

static Object float_constant;      /* 0.0 */

static Object float_constant_1;    /* 1.0 */

/* EMIT-AGGREGATOR-INSTRUCTION */
Object emit_aggregator_instruction(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object gensymed_symbol, simple_role, value_spot, continuation_spot;
    Object expiration_var_qm, cached_global_expiration_var_qm, argument_nodes;
    Object operator_1, accumulator_operator_qm, iteration_expression;
    Object accumulator_operator_type_qm;
    Object accumulator_operator_type_without_unknown_qm, empty_role_value_qm;
    Object domain_list_qm, domain_ok_tag, value_served_tag, count_tag_qm;
    Object known_value_tag_qm, unknown_value_tag_qm, end_of_instruction_tag;
    Object domain, ab_loop_list_, possible_unknown_domain_qm;
    Object ab_loop_iter_flag_;
    SI_Long count_1;
    char unknown_allowed_qm, count_aggregator_qm;

    x_note_fn_call(208,12);
    gensymed_symbol = extra_info;
    simple_role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    cached_global_expiration_var_qm = CAR(gensymed_symbol);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm =  ! !TRUEP(cached_global_expiration_var_qm);
    operator_1 = ISVREF(stack_node_instruction,(SI_Long)1L);
    count_aggregator_qm = EQ(operator_1,Qcount);
    if (EQ(operator_1,Qsum) || EQ(operator_1,Qcount))
	accumulator_operator_qm = Qplus;
    else if (EQ(operator_1,Qproduct))
	accumulator_operator_qm = Qstar;
    else
	accumulator_operator_qm = Nil;
    iteration_expression = FIRST(argument_nodes);
    accumulator_operator_type_qm = accumulator_operator_qm ? 
	    (EQ(operator_1,Qcount) ? ISVREF(stack_node_instruction,
	    (SI_Long)6L) : ISVREF(iteration_expression,(SI_Long)6L)) : Nil;
    accumulator_operator_type_without_unknown_qm = 
	    accumulator_operator_type_qm ? 
	    (union_type_specification_p(accumulator_operator_type_qm) ? 
	    type_specification_minus_type(accumulator_operator_type_qm,
	    list_constant) : accumulator_operator_type_qm) : 
	    compiler_bug(2,string_constant_7,string_constant_8);
    if (EQ(operator_1,Qsum) || EQ(operator_1,Qcount))
	empty_role_value_qm = 
		EQ(accumulator_operator_type_without_unknown_qm,Qfloat) ? 
		float_constant : FIX((SI_Long)0L);
    else if (EQ(operator_1,Qproduct))
	empty_role_value_qm = 
		EQ(accumulator_operator_type_without_unknown_qm,Qfloat) ? 
		float_constant_1 : FIX((SI_Long)1L);
    else
	empty_role_value_qm = Nil;
    domain_list_qm = CDR(argument_nodes);
    domain_ok_tag = generate_new_goto_tag();
    value_served_tag = generate_new_goto_tag();
    count_tag_qm = count_aggregator_qm ? generate_new_goto_tag() : Nil;
    known_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    unknown_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    end_of_instruction_tag = generate_new_goto_tag();
    if (unknown_allowed_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
    }
    emit_push_constant_byte_codes(byte_code_stream,empty_role_value_qm ? 
	    make_evaluation_quantity(empty_role_value_qm) : Nil);
    if (domain_list_qm) {
	domain = Nil;
	ab_loop_list_ = domain_list_qm;
	possible_unknown_domain_qm = Nil;
	count_1 = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	possible_unknown_domain_qm = 
		type_specification_subtype_p(list_constant,
		ISVREF(stack_node_instruction,(SI_Long)6L));
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	emit_stack_node_tree(byte_code_stream,domain);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (possible_unknown_domain_qm) {
	    emit_branch_long_if_known_byte_codes(byte_code_stream,
		    domain_ok_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,domain_ok_tag);
	}
	emit_open_role_iteration_byte_codes(byte_code_stream,simple_role,
		end_of_instruction_tag,FIX(count_1));
    }
    else
	emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,
		simple_role,end_of_instruction_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    register_tag_in_byte_code_stream(2,byte_code_stream,value_served_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    emit_stack_node_tree(byte_code_stream,iteration_expression);
    if (unknown_allowed_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		known_value_tag_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_branch_long_byte_codes(byte_code_stream,unknown_value_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		known_value_tag_qm);
    }
    if ( !count_aggregator_qm)
	emit_operator_of_type(byte_code_stream,accumulator_operator_qm,
		accumulator_operator_type_without_unknown_qm);
    else {
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,count_tag_qm);
	emit_push_constant_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_operator_of_type(byte_code_stream,accumulator_operator_qm,
		accumulator_operator_type_without_unknown_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,count_tag_qm);
    }
    if (unknown_allowed_qm) {
	register_tag_in_byte_code_stream(2,byte_code_stream,
		unknown_value_tag_qm);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,end_of_instruction_tag);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_instruction_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    return emit_close_iteration_byte_codes(byte_code_stream,continuation_spot);
}

static Object Qmaximum;            /* maximum */

static Object Qminimum;            /* minimum */

static Object string_constant_9;   /* "max or min aggregator emitter" */

static Object string_constant_10;  /* "The maximum over an empty set of values has no value.  This was not an expected result." */

static Object string_constant_11;  /* "The minimum over an empty set of values has no value.  This was not an expected result." */

/* EMIT-MAX-OR-MIN-AGGREGATOR-INSTRUCTION */
Object emit_max_or_min_aggregator_instruction(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object gensymed_symbol, simple_role, value_spot, continuation_spot;
    Object iteration_var, expiration_var_qm, cached_global_expiration_var_qm;
    Object argument_nodes, no_item_allowed_qm, operator_1;
    Object accumulator_operator_qm, iteration_expression;
    Object accumulator_operator_type_qm;
    Object accumulator_operator_type_without_unknown_qm, domain_list_qm;
    Object domain_ok_tag, no_value_tag, value_served_tag;
    Object no_previous_value_tag, accumulate_tag, known_value_tag_qm;
    Object unknown_value_tag_qm, push_accumulator_tag, end_of_instruction_tag;
    Object some_unknown_domain_qm, domain, ab_loop_list_, domain_type;
    Object possible_unknown_domain_qm, possible_no_item_domain_qm;
    Object ab_loop_iter_flag_, temp, domain_known_tag;
    Object leave_domain_on_stack_tag;
    SI_Long count_1;
    char unknown_allowed_qm;

    x_note_fn_call(208,13);
    gensymed_symbol = extra_info;
    simple_role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    iteration_var = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    cached_global_expiration_var_qm = CAR(gensymed_symbol);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm =  ! !TRUEP(cached_global_expiration_var_qm);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    ISVREF(stack_node_instruction,(SI_Long)5L));
    operator_1 = ISVREF(stack_node_instruction,(SI_Long)1L);
    if (EQ(operator_1,Qmaximum))
	accumulator_operator_qm = Qmax;
    else if (EQ(operator_1,Qminimum))
	accumulator_operator_qm = Qmin;
    else
	accumulator_operator_qm = Nil;
    iteration_expression = FIRST(argument_nodes);
    accumulator_operator_type_qm = accumulator_operator_qm ? 
	    ISVREF(iteration_expression,(SI_Long)6L) : Nil;
    accumulator_operator_type_without_unknown_qm = 
	    accumulator_operator_type_qm ? 
	    type_specification_minus_type(type_specification_minus_type(accumulator_operator_type_qm,
	    list_constant_1),list_constant) : compiler_bug(2,
	    string_constant_9,string_constant_8);
    domain_list_qm = CDR(argument_nodes);
    domain_ok_tag = generate_new_goto_tag();
    no_value_tag = generate_new_goto_tag();
    value_served_tag = generate_new_goto_tag();
    no_previous_value_tag = generate_new_goto_tag();
    accumulate_tag = generate_new_goto_tag();
    known_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    unknown_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    push_accumulator_tag = generate_new_goto_tag();
    end_of_instruction_tag = generate_new_goto_tag();
    if (unknown_allowed_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
    }
    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    iteration_var);
    if (domain_list_qm) {
	some_unknown_domain_qm = Nil;
	domain = Nil;
	ab_loop_list_ = domain_list_qm;
	domain_type = Nil;
	possible_unknown_domain_qm = Nil;
	possible_no_item_domain_qm = Nil;
	count_1 = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	domain_type = ISVREF(stack_node_instruction,(SI_Long)6L);
	possible_unknown_domain_qm = 
		type_specification_subtype_p(list_constant,domain_type);
	possible_no_item_domain_qm = 
		type_specification_subtype_p(list_constant_1,domain_type);
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	temp = some_unknown_domain_qm;
	if (temp);
	else
	    temp = possible_unknown_domain_qm;
	some_unknown_domain_qm = temp;
	emit_stack_node_tree(byte_code_stream,domain);
	if (possible_no_item_domain_qm) {
	    domain_known_tag = generate_new_goto_tag();
	    leave_domain_on_stack_tag = generate_new_goto_tag();
	    if (possible_unknown_domain_qm) {
		emit_branch_long_if_known_byte_codes(byte_code_stream,
			domain_known_tag);
		emit_branch_long_byte_codes(byte_code_stream,
			leave_domain_on_stack_tag);
	    }
	    register_tag_in_byte_code_stream(2,byte_code_stream,
		    domain_known_tag);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	    emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		    leave_domain_on_stack_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,no_value_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,
		    leave_domain_on_stack_tag);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (some_unknown_domain_qm) {
	    emit_branch_long_if_known_byte_codes(byte_code_stream,
		    domain_ok_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,domain_ok_tag);
	}
	emit_open_role_iteration_byte_codes(byte_code_stream,simple_role,
		no_value_tag,FIX(count_1));
    }
    else
	emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,
		simple_role,no_value_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,no_value_tag);
    if (no_item_allowed_qm) {
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_branch_long_byte_codes(byte_code_stream,end_of_instruction_tag);
    }
    else {
	emit_push_constant_byte_codes(byte_code_stream,Qerror);
	emit_push_constant_byte_codes(byte_code_stream,EQ(operator_1,
		Qmaximum) ? copy_as_wide_string(string_constant_10) : 
		copy_as_wide_string(string_constant_11));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)56L));
    }
    register_tag_in_byte_code_stream(2,byte_code_stream,value_served_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    emit_stack_node_tree(byte_code_stream,iteration_expression);
    if (unknown_allowed_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		known_value_tag_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_branch_long_byte_codes(byte_code_stream,unknown_value_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		known_value_tag_qm);
    }
    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    iteration_var);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
    emit_branch_long_if_true_byte_codes(byte_code_stream,
	    no_previous_value_tag);
    emit_operator_of_type(byte_code_stream,accumulator_operator_qm,
	    accumulator_operator_type_without_unknown_qm);
    emit_branch_long_byte_codes(byte_code_stream,accumulate_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,no_previous_value_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    register_tag_in_byte_code_stream(2,byte_code_stream,accumulate_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    iteration_var);
    if (unknown_allowed_qm) {
	register_tag_in_byte_code_stream(2,byte_code_stream,
		unknown_value_tag_qm);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,push_accumulator_tag);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,push_accumulator_tag);
    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    iteration_var);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_instruction_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    return emit_close_iteration_byte_codes(byte_code_stream,continuation_spot);
}

static Object string_constant_12;  /* "The average over an empty set of values has no value.  This was not an expected result." */

/* EMIT-AGGREGATED-AVERAGE-INSTRUCTION */
Object emit_aggregated_average_instruction(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object gensymed_symbol, simple_role, value_spot, continuation_spot;
    Object count_var, expiration_var_qm, cached_global_expiration_var_qm;
    Object argument_nodes, no_item_allowed_qm, iteration_expression;
    Object iteration_type, iteration_type_without_unknown, initial_value;
    Object domain_list_qm, domain_ok_tag, no_value_tag, value_served_tag;
    Object known_value_tag_qm, unknown_value_tag_qm;
    Object compute_average_if_known_tag, end_of_instruction_tag;
    Object some_unknown_domain_qm, domain, ab_loop_list_, domain_type;
    Object possible_unknown_domain_qm, possible_no_item_domain_qm;
    Object ab_loop_iter_flag_, temp, domain_known_tag;
    Object leave_domain_on_stack_tag;
    SI_Long initial_count_value, count_value, count_1;
    char unknown_allowed_qm, iteration_float_type_qm;

    x_note_fn_call(208,14);
    gensymed_symbol = extra_info;
    simple_role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    count_var = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    cached_global_expiration_var_qm = CAR(gensymed_symbol);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm =  ! !TRUEP(cached_global_expiration_var_qm);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    ISVREF(stack_node_instruction,(SI_Long)5L));
    iteration_expression = FIRST(argument_nodes);
    iteration_type = ISVREF(iteration_expression,(SI_Long)6L);
    iteration_type_without_unknown = 
	    union_type_specification_p(iteration_type) ? 
	    type_specification_minus_type(iteration_type,list_constant) : 
	    iteration_type;
    iteration_float_type_qm = EQ(iteration_type_without_unknown,Qfloat);
    initial_value = float_constant;
    initial_count_value = (SI_Long)0L;
    count_value = (SI_Long)1L;
    domain_list_qm = CDR(argument_nodes);
    domain_ok_tag = generate_new_goto_tag();
    no_value_tag = generate_new_goto_tag();
    value_served_tag = generate_new_goto_tag();
    known_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    unknown_value_tag_qm = unknown_allowed_qm ? generate_new_goto_tag() : Nil;
    compute_average_if_known_tag = generate_new_goto_tag();
    end_of_instruction_tag = generate_new_goto_tag();
    if (unknown_allowed_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
    }
    emit_push_constant_byte_codes(byte_code_stream,
	    make_evaluation_quantity(FIX(initial_count_value)));
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,count_var);
    emit_push_constant_byte_codes(byte_code_stream,
	    make_evaluation_quantity(initial_value));
    if (domain_list_qm) {
	some_unknown_domain_qm = Nil;
	domain = Nil;
	ab_loop_list_ = domain_list_qm;
	domain_type = Nil;
	possible_unknown_domain_qm = Nil;
	possible_no_item_domain_qm = Nil;
	count_1 = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	domain_type = ISVREF(stack_node_instruction,(SI_Long)6L);
	possible_unknown_domain_qm = 
		type_specification_subtype_p(list_constant,domain_type);
	possible_no_item_domain_qm = 
		type_specification_subtype_p(list_constant_1,domain_type);
	if ( !TRUEP(ab_loop_iter_flag_))
	    count_1 = count_1 + (SI_Long)1L;
	temp = some_unknown_domain_qm;
	if (temp);
	else
	    temp = possible_unknown_domain_qm;
	some_unknown_domain_qm = temp;
	emit_stack_node_tree(byte_code_stream,domain);
	if (possible_no_item_domain_qm) {
	    domain_known_tag = generate_new_goto_tag();
	    leave_domain_on_stack_tag = generate_new_goto_tag();
	    if (possible_unknown_domain_qm) {
		emit_branch_long_if_known_byte_codes(byte_code_stream,
			domain_known_tag);
		emit_branch_long_byte_codes(byte_code_stream,
			leave_domain_on_stack_tag);
	    }
	    register_tag_in_byte_code_stream(2,byte_code_stream,
		    domain_known_tag);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	    emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		    leave_domain_on_stack_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,no_value_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,
		    leave_domain_on_stack_tag);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (some_unknown_domain_qm) {
	    emit_branch_long_if_known_byte_codes(byte_code_stream,
		    domain_ok_tag);
	    emit_pop_values_byte_codes(byte_code_stream,FIX(count_1));
	    emit_branch_long_byte_codes(byte_code_stream,
		    end_of_instruction_tag);
	    register_tag_in_byte_code_stream(2,byte_code_stream,domain_ok_tag);
	}
	emit_open_role_iteration_byte_codes(byte_code_stream,simple_role,
		no_value_tag,FIX(count_1));
    }
    else
	emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,
		simple_role,no_value_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,no_value_tag);
    if (no_item_allowed_qm) {
	emit_pop_values_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_branch_long_byte_codes(byte_code_stream,end_of_instruction_tag);
    }
    else {
	emit_push_constant_byte_codes(byte_code_stream,Qerror);
	emit_push_constant_byte_codes(byte_code_stream,
		copy_as_wide_string(string_constant_12));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)56L));
    }
    register_tag_in_byte_code_stream(2,byte_code_stream,value_served_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    emit_stack_node_tree(byte_code_stream,iteration_expression);
    if (unknown_allowed_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,
		known_value_tag_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_branch_long_byte_codes(byte_code_stream,unknown_value_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		known_value_tag_qm);
    }
    if ( !iteration_float_type_qm)
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)36L));
    emit_operator_of_type(byte_code_stream,Qplus,Qfloat);
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
	    count_var);
    emit_push_constant_byte_codes(byte_code_stream,
	    make_evaluation_quantity(FIX(count_value)));
    emit_operator_of_type(byte_code_stream,Qplus,Qinteger);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,count_var);
    if (unknown_allowed_qm) {
	register_tag_in_byte_code_stream(2,byte_code_stream,
		unknown_value_tag_qm);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,compute_average_if_known_tag);
    emit_branch_long_byte_codes(byte_code_stream,value_served_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    compute_average_if_known_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)96L));
	emit_branch_long_if_true_byte_codes(byte_code_stream,
		end_of_instruction_tag);
    }
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
	    count_var);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)36L));
    emit_operator_of_type(byte_code_stream,Qslash,Qfloat);
    register_tag_in_byte_code_stream(2,byte_code_stream,
	    end_of_instruction_tag);
    if (unknown_allowed_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		cached_global_expiration_var_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
    }
    return emit_close_iteration_byte_codes(byte_code_stream,continuation_spot);
}

/* SUM-STACK-NODE-CONVERTER */
Object sum_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,15);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

/* SUM-I-CHOOSER */
Object sum_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,16);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    Qnumber,Qnumber,Nil,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SUM-I-EMIT */
Object sum_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,17);
    emit_aggregator_instruction(stack_node_instruction,byte_code_stream,
	    extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRODUCT-STACK-NODE-CONVERTER */
Object product_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,18);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

/* PRODUCT-I-CHOOSER */
Object product_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,19);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    Qnumber,Qnumber,Nil,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRODUCT-I-EMIT */
Object product_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,20);
    emit_aggregator_instruction(stack_node_instruction,byte_code_stream,
	    extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COUNT-STACK-NODE-CONVERTER */
Object count_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,21);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

/* COUNT-I-CHOOSER */
Object count_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,22);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    Qinteger,Qtruth_value,Nil,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COUNT-I-EMIT */
Object count_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,23);
    emit_aggregator_instruction(stack_node_instruction,byte_code_stream,
	    extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AGGREGATED-AVERAGE-STACK-NODE-CONVERTER */
Object aggregated_average_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,24);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

/* AGGREGATED-AVERAGE-I-CHOOSER */
Object aggregated_average_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,25);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    list_constant_5,Qnumber,Qinteger,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* AGGREGATED-AVERAGE-I-EMIT */
Object aggregated_average_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,26);
    emit_aggregated_average_instruction(stack_node_instruction,
	    byte_code_stream,extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MAXIMUM-STACK-NODE-CONVERTER */
Object maximum_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,27);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

/* MAXIMUM-I-CHOOSER */
Object maximum_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,28);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    list_constant_6,Qnumber,T,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MAXIMUM-I-EMIT */
Object maximum_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,29);
    emit_max_or_min_aggregator_instruction(stack_node_instruction,
	    byte_code_stream,extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MINIMUM-STACK-NODE-CONVERTER */
Object minimum_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,30);
    GENSYM_RETURN_ONE(aggregator_special_form_converter(expression));
    return VALUES_1(Nil);
}

/* MINIMUM-I-CHOOSER */
Object minimum_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(208,31);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    aggregator_instruction_chooser(stack_node_instruction,required_type,
	    list_constant_6,Qnumber,T,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MINIMUM-I-EMIT */
Object minimum_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,32);
    emit_max_or_min_aggregator_instruction(stack_node_instruction,
	    byte_code_stream,extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qsimulator;          /* simulator */

static Object Qsimulated_value;    /* simulated-value */

static Object Qfloat_array;        /* float-array */

/* EVAL-CURRENT-SUBSECOND-TIME-FUNCALLED */
Object eval_current_subsecond_time_funcalled()
{
    Object gensymed_symbol, integer_portion, micro_time, temp, temp_1;
    Object amf_available_array_cons_qm, amf_array, temp_2, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(208,33);
    if (EQ(Current_environment,Qsimulator) || EQ(Current_environment,
	    Qsimulated_value)) {
	gensymed_symbol = get_current_time_in_simulation_environment();
	integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	if (IFIX(micro_time) == (SI_Long)0L) {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	else {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion) + 
		    (double)IFIX(micro_time) / 100000.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	temp_1 = copy_managed_float(Simulation_time_managed_float);
    }
    else {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
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
	aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) - 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_1 = new_float;
    }
    return VALUES_1(temp_1);
}

/* EVAL-CURRENT-SYSTEM-TIME-FUNCALLED */
Object eval_current_system_time_funcalled()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(208,34);
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
    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* EVAL-CURRENT-SUBSECOND-REAL-TIME-FUNCALLED */
Object eval_current_subsecond_real_time_funcalled()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double temp_2, aref_new_value;

    x_note_fn_call(208,35);
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
    temp_2 = g2ext_unix_time_as_float();
    aref_new_value = temp_2 - DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* EVAL-CURRENT-SYSTEM-REAL-TIME-FUNCALLED */
Object eval_current_system_real_time_funcalled()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(208,36);
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
    aref_new_value = g2ext_unix_time_as_float();
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

static Object Qcollection_time_of;  /* collection-time-of */

/* COLLECTION-TIME-OF-STACK-NODE-CONVERTER */
Object collection_time_of_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(208,37);
    gensymed_symbol = make_stack_node_instruction_1_1(Qcollection_time_of,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

/* COLLECTION-TIME-OF-I-CHOOSER */
Object collection_time_of_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_list, unknown_allowed_qm, temp;
    char svref_new_value;

    x_note_fn_call(208,38);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    temp = choose_stack_node_instructions_and_types(2,M_CAR(argument_list),
	    list_constant_7);
    M_CAR(argument_list) = temp;
    svref_new_value =  ! !TRUEP(unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = svref_new_value ? T :
	     Nil;
    temp = maybe_add_unknown(Qnumber,unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COLLECTION-TIME-OF-I-EMIT */
Object collection_time_of_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,39);
    emit_stack_node_tree(byte_code_stream,
	    M_CAR(ISVREF(stack_node_instruction,(SI_Long)2L)));
    emit_push_constant_byte_codes(byte_code_stream,extra_info ? 
	    Evaluation_true_value : Evaluation_false_value);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qcollection_time_of);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_13;  /* "~NF does not have a value." */

/* NO-VALUE-EVAL-ERROR-MESSAGE */
Object no_value_eval_error_message(item)
    Object item;
{
    x_note_fn_call(208,40);
    return tformat_stack_error_text_string(2,string_constant_13,item);
}

/* FUNCALL-COLLECTION-TIME-OF-INST */
Object funcall_collection_time_of_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object variable_or_parameter, simulation_environment_qm, collection_time;
    Object managed_number_or_value, unknown_allowed_arg;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char unknown_allowed_qm;
    double gensymed_symbol_2, gensymed_symbol_3, result_float, arg, arg_1;

    x_note_fn_call(208,41);
    variable_or_parameter = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    simulation_environment_qm = EQ(Current_environment,Qsimulator) ? T : Nil;
    if (simulation_environment_qm);
    else
	simulation_environment_qm = EQ(Current_environment,
		Qsimulated_value) ? T : Nil;
    if (simulation_environment_qm)
	collection_time = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(get_simulation_environment_gensym_time_for_variable_as_float(variable_or_parameter),
		(SI_Long)0L));
    else {
	managed_number_or_value = ISVREF(variable_or_parameter,(SI_Long)21L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    collection_time = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    collection_time = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    collection_time = copy_text_string(managed_number_or_value);
	else
	    collection_time = managed_number_or_value;
    }
    unknown_allowed_arg = ISVREF(local_stack,IFIX(top_of_stack));
    unknown_allowed_qm = FIXNUM_GE(M_CAR(unknown_allowed_arg),Truth);
    if (SYMBOLP(collection_time) || FIXNUMP(collection_time) && 
	    FIXNUM_EQ(collection_time,Some_time_ago)) {
	if (unknown_allowed_qm) {
	    Stack_expiration = Nil;
	    collection_time = FIX((SI_Long)0L);
	}
	else
	    raw_stack_error_named_error(top_of_stack,
		    no_value_eval_error_message(variable_or_parameter));
    }
    else if (FIXNUMP(collection_time)) {
	gensymed_symbol = IFIX(collection_time);
	gensymed_symbol_1 = simulation_environment_qm ? 
		IFIX(Gensym_time_at_start) : 
		inline_floor_1(DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L));
	collection_time = FIX(gensymed_symbol - gensymed_symbol_1);
    }
    else if (FLOATP(collection_time)) {
	gensymed_symbol_2 = DOUBLE_FLOAT_TO_DOUBLE(collection_time);
	gensymed_symbol_3 = simulation_environment_qm ? 
		(double)IFIX(Gensym_time_at_start) : 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	result_float = gensymed_symbol_2 - gensymed_symbol_3;
	arg = result_float;
	arg_1 = inline_ffloor_1(result_float);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    collection_time = LONG_TO_FIXNUM(inline_floor_1(result_float));
	else {
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,result_float);
	    collection_time = new_float;
	}
    }
    if ( !(EQ(unknown_allowed_arg,Evaluation_true_value) || 
	    EQ(unknown_allowed_arg,Evaluation_false_value)))
	reclaim_eval_cons_1(unknown_allowed_arg);
    temp = FIXNUM_SUB1(top_of_stack);
    SVREF(local_stack,temp) = collection_time;
    return VALUES_1(Nil);
}

static Object Qcollection_time_of_previous_datapoint;  /* collection-time-of-previous-datapoint */

/* COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-STACK-NODE-CONVERTER */
Object collection_time_of_previous_datapoint_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(208,42);
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qcollection_time_of_previous_datapoint,
	    Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

/* COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-I-CHOOSER */
Object collection_time_of_previous_datapoint_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm;
    Object argument_nodes, temp, temp_1;

    x_note_fn_call(208,43);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    if (argument_nodes) {
	temp = choose_stack_node_instructions_and_types(2,
		FIRST(argument_nodes),
		maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(list_constant_7,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm));
	M_FIRST(argument_nodes) = temp;
    }
    if (CDR(argument_nodes)) {
	temp = choose_stack_node_instructions_and_types(2,
		SECOND(argument_nodes),
		maybe_add_no_item(maybe_add_unknown(Qnil ? Qsymbol : 
		Qnumber,unknown_allowed_qm),no_item_allowed_qm));
	M_SECOND(argument_nodes) = temp;
    }
    if (CDDR(argument_nodes)) {
	temp_1 = THIRD(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_THIRD(argument_nodes) = temp;
    }
    if (CDDDR(argument_nodes)) {
	temp_1 = FOURTH(argument_nodes);
	temp = choose_stack_node_instructions_and_types(2,temp_1,
		make_type_specification_union(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qnumber,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Qtruth_value));
	M_FOURTH(argument_nodes) = temp;
    }
    temp_1 = unknown_allowed_qm;
    if (temp_1);
    else
	temp_1 = no_item_implies_unknown_allowed_qm;
    temp = maybe_add_no_item(maybe_add_unknown(Qnumber,temp_1),
	    no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-I-EMIT */
Object collection_time_of_previous_datapoint_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, unknown_allowed_qm, no_item_allowed_qm, argument;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(208,44);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    ISVREF(stack_node_instruction,(SI_Long)6L));
    argument = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    gensymed_symbol = unknown_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    gensymed_symbol = no_item_allowed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    emit_push_constant_byte_codes(byte_code_stream,temp);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qcollection_time_of_previous_datapoint);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_14;  /* "Cannot reference the collection time of ~NF as of ~d datapoints ago.  A ~
				    *       history datapoint must be referenced by a non-negative integer."
				    */

static Object string_constant_15;  /* "Cannot get a collection time for ~NF as of ~a datapoints ago.  ~
				    *            There was no value at that datapoint."
				    */

/* FUNCALL-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-INST */
Object funcall_collection_time_of_previous_datapoint_inst(top_of_stack,
	    local_stack)
    Object top_of_stack, local_stack;
{
    Object variable_or_parameter, number_of_datapoints_ago, unknown_allowed;
    Object no_item_allowed, collection_time_qm, return_value_qm;
    Object top_of_stack_1, message_1, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;
    Object evaluation_truth_value;
    SI_Long top_of_stack_new_value;
    double collection_time_float_qm, arg, arg_1;

    x_note_fn_call(208,45);
    variable_or_parameter = ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)3L);
    number_of_datapoints_ago = 
	    evaluation_quantity_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L));
    unknown_allowed = M_CAR(ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))));
    no_item_allowed = M_CAR(ISVREF(local_stack,IFIX(top_of_stack)));
    collection_time_qm = Nil;
    return_value_qm = Nil;
    if (IFIX(number_of_datapoints_ago) < (SI_Long)0L) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_14,
		variable_or_parameter,number_of_datapoints_ago);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    temp = EQ(Current_environment,Qsimulator) ? T : Nil;
    if (temp);
    else
	temp = EQ(Current_environment,Qsimulated_value) ? T : Nil;
    collection_time_qm = 
	    get_collection_time_of_previous_datapoint(variable_or_parameter,
	    temp,number_of_datapoints_ago);
    if (collection_time_qm) {
	collection_time_float_qm = DOUBLE_FLOAT_TO_DOUBLE(collection_time_qm);
	arg = collection_time_float_qm;
	arg_1 = inline_ffloor_1(collection_time_float_qm);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    return_value_qm = 
		    LONG_TO_FIXNUM(inline_floor_1(collection_time_float_qm));
	else {
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,collection_time_float_qm);
	    return_value_qm = new_float;
	}
    }
    else if (FIXNUM_EQ(unknown_allowed,Truth)) {
	Stack_expiration = Nil;
	return_value_qm = Nil;
    }
    else if (FIXNUM_EQ(no_item_allowed,Truth))
	return_value_qm = Nil;
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_15,
		variable_or_parameter,number_of_datapoints_ago);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    reclaim_evaluation_quantity(ISVREF(local_stack,IFIX(top_of_stack) - 
	    (SI_Long)2L));
    evaluation_truth_value = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    evaluation_truth_value = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(EQ(evaluation_truth_value,Evaluation_true_value) || 
	    EQ(evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(evaluation_truth_value);
    top_of_stack_new_value = IFIX(top_of_stack) - (SI_Long)3L;
    top_of_stack = FIX(top_of_stack_new_value);
    SVREF(local_stack,top_of_stack) = return_value_qm;
    return VALUES_1(Nil);
}

static Object Qexpiration_time_of;  /* expiration-time-of */

/* EXPIRATION-TIME-OF-STACK-NODE-CONVERTER */
Object expiration_time_of_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(208,46);
    gensymed_symbol = make_stack_node_instruction_1_1(Qexpiration_time_of,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

/* EXPIRATION-TIME-OF-I-CHOOSER */
Object expiration_time_of_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_list, no_item_implies_unknown_allowed_qm;
    Object unknown_allowed_qm, temp;
    char svref_new_value;

    x_note_fn_call(208,47);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    temp = choose_stack_node_instructions_and_types(2,M_CAR(argument_list),
	    list_constant_8);
    M_CAR(argument_list) = temp;
    svref_new_value =  ! !TRUEP(unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = svref_new_value ? T :
	     Nil;
    temp = maybe_add_no_item_implies_unknown(maybe_add_unknown(Qnumber,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EXPIRATION-TIME-OF-I-EMIT */
Object expiration_time_of_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(208,48);
    emit_stack_node_tree(byte_code_stream,
	    M_CAR(ISVREF(stack_node_instruction,(SI_Long)2L)));
    emit_push_constant_byte_codes(byte_code_stream,extra_info ? 
	    Evaluation_true_value : Evaluation_false_value);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qexpiration_time_of);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FUNCALL-EXPIRATION-TIME-OF-INST */
Object funcall_expiration_time_of_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object variable, expiration, unknown_allowed_arg, svref_arg_2;
    char unknown_allowed_qm;

    x_note_fn_call(208,49);
    variable = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    expiration = ISVREF(variable,(SI_Long)26L);
    unknown_allowed_arg = ISVREF(local_stack,IFIX(top_of_stack));
    unknown_allowed_qm = FIXNUM_GE(M_CAR(unknown_allowed_arg),Truth);
    if (SYMBOLP(expiration) || FIXNUM_EQ(expiration,Some_time_ago)) {
	if (unknown_allowed_qm) {
	    Stack_expiration = Nil;
	    expiration = FIX((SI_Long)0L);
	}
	else
	    raw_stack_error_named_error(top_of_stack,
		    no_value_eval_error_message(variable));
    }
    else
	expiration = FIXNUM_MINUS(expiration,Gensym_time_at_start);
    if ( !(EQ(unknown_allowed_arg,Evaluation_true_value) || 
	    EQ(unknown_allowed_arg,Evaluation_false_value)))
	reclaim_eval_cons_1(unknown_allowed_arg);
    svref_arg_2 = FIXNUM_SUB1(top_of_stack);
    SVREF(local_stack,svref_arg_2) = expiration;
    return VALUES_1(Nil);
}

static Object Qg2_list_or_sequence_member_p;  /* g2-list-or-sequence-member-p */

/* G2-LIST-OR-SEQUENCE-MEMBER-P-STACK-NODE-CONVERTER */
Object g2_list_or_sequence_member_p_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, instruction_node, argument, ab_loop_list_;
    Object converted_argument_list, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(208,50);
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qg2_list_or_sequence_member_p,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    instruction_node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    converted_argument_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	converted_argument_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    SVREF(instruction_node,FIX((SI_Long)2L)) = converted_argument_list;
    GENSYM_RETURN_ONE(instruction_node);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

/* G2-LIST-OR-SEQUENCE-MEMBER-P-I-CHOOSER */
Object g2_list_or_sequence_member_p_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, argument_nodes, g2_list_node;
    Object element_node, g2_list_spec, g2_list_class_qm;
    Object g2_list_element_type_qm, temp, temp_1;

    x_note_fn_call(208,51);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    g2_list_node = FIRST(argument_nodes);
    element_node = SECOND(argument_nodes);
    g2_list_spec = Nil;
    g2_list_class_qm = Nil;
    g2_list_element_type_qm = Nil;
    temp = choose_stack_node_instructions_and_types(2,g2_list_node,
	    list_constant_9);
    M_FIRST(argument_nodes) = temp;
    g2_list_spec = ISVREF(g2_list_node,(SI_Long)6L);
    g2_list_class_qm = class_type_specification_p(g2_list_spec) ? 
	    M_CAR(M_CDR(g2_list_spec)) : Qnil;
    g2_list_element_type_qm = 
	    g2_list_or_array_class_element_type(g2_list_class_qm,T);
    temp_1 = g2_list_element_type_qm;
    if (temp_1);
    else
	temp_1 = Qitem_or_datum;
    temp = choose_stack_node_instructions_and_types(2,element_node,
	    maybe_add_unknown(temp_1,unknown_allowed_qm));
    M_SECOND(argument_nodes) = temp;
    if (unknown_allowed_qm && type_specification_subtype_p(list_constant_8,
	    ISVREF(element_node,(SI_Long)6L)))
	temp = maybe_add_no_item_implies_unknown(list_constant_4,
		no_item_implies_unknown_allowed_qm);
    else if (unknown_allowed_qm && 
	    type_specification_subtype_p(list_constant,ISVREF(element_node,
	    (SI_Long)6L)))
	temp = list_constant_4;
    else
	temp = Qboolean;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* G2-LIST-OR-SEQUENCE-MEMBER-P-I-EMIT */
Object g2_list_or_sequence_member_p_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object value_type, unknown_is_allowed_qm, argument_nodes;

    x_note_fn_call(208,52);
    value_type = ISVREF(stack_node_instruction,(SI_Long)6L);
    unknown_is_allowed_qm = type_specification_subtype_p(list_constant,
	    value_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    emit_stack_node_tree(byte_code_stream,SECOND(argument_nodes));
    if (unknown_is_allowed_qm)
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
    else
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qg2_list_or_sequence_member_p);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_16;  /* "Cannot test that ~NA is a member of the g2-list ~NF.  This item or value ~
				    *    conflicts with the element-type, ~a, of the g2-list."
				    */

/* MEMBER-IN-G2-LIST-ELEMENT-ERROR-MESSAGE */
Object member_in_g2_list_element_error_message(element,g2_list)
    Object element, g2_list;
{
    x_note_fn_call(208,53);
    return tformat_stack_error_text_string(4,string_constant_16,element,
	    g2_list,ISVREF(g2_list,(SI_Long)21L));
}

/* FUNCALL-G2-LIST-OR-SEQUENCE-MEMBER-P-INST */
Object funcall_g2_list_or_sequence_member_p_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object g2_list_or_sequence, potential_element, unknown_allowed_flag;
    Object coerced_element_qm, result_qm, gensymed_symbol, held_vector, elt_1;
    Object ab_loop_it_, elt_2, validated_elt, register_1, register_2;
    SI_Long next_index, length_1, svref_arg_2;
    char temp;
    Object result;

    x_note_fn_call(208,54);
    g2_list_or_sequence = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    potential_element = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    unknown_allowed_flag = ISVREF(local_stack,IFIX(top_of_stack));
    coerced_element_qm = Nil;
    result_qm = Nil;
    if (CONSP(g2_list_or_sequence) && EQ(M_CDR(g2_list_or_sequence),
		Qsequence)) {
	gensymed_symbol = g2_list_or_sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	elt_1 = Nil;
	ab_loop_it_ = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_2 ? validate_item_or_evaluation_value(elt_2,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	elt_1 = validated_elt;
	ab_loop_it_ = item_or_value_equalp(elt_1,potential_element);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	result_qm = temp ? Evaluation_true_value : Evaluation_false_value;
    }
    else {
	result = coerce_matching_element_type_or_unknown(g2_list_or_sequence,
		potential_element,top_of_stack,CONSP(unknown_allowed_flag) 
		&& EQ(M_CDR(unknown_allowed_flag),Qtruth_value) ? 
		(EQ(M_CAR(unknown_allowed_flag),Truth) ? T : Nil) : Qnil);
	MVS_2(result,register_1,register_2);
	if (register_2)
	    raw_stack_error_named_error(top_of_stack,register_2);
	coerced_element_qm = register_1;
	if ( !TRUEP(coerced_element_qm))
	    result_qm = Nil;
	else if (g2_list_member_p(coerced_element_qm,g2_list_or_sequence))
	    result_qm = Evaluation_true_value;
	else
	    result_qm = Evaluation_false_value;
    }
    if ( !(FIXNUMP(g2_list_or_sequence) || SYMBOLP(g2_list_or_sequence) || 
	    SIMPLE_VECTOR_P(g2_list_or_sequence)))
	reclaim_if_evaluation_value_1(g2_list_or_sequence);
    if ( !(FIXNUMP(potential_element) || SYMBOLP(potential_element) || 
	    SIMPLE_VECTOR_P(potential_element)))
	reclaim_if_evaluation_value_1(potential_element);
    if ( !(FIXNUMP(coerced_element_qm) || SYMBOLP(coerced_element_qm) || 
	    SIMPLE_VECTOR_P(coerced_element_qm)))
	reclaim_if_evaluation_value_1(coerced_element_qm);
    svref_arg_2 = IFIX(top_of_stack) - (SI_Long)2L;
    ISVREF(local_stack,svref_arg_2) = result_qm;
    return VALUES_1(Nil);
}

static Object Qnext_list_element;  /* next-list-element */

/* NEXT-LIST-ELEMENT-STACK-NODE-CONVERTER */
Object next_list_element_stack_node_converter(expression)
    Object expression;
{
    Object temp, arguments, gensymed_symbol, next_list_element_node;

    x_note_fn_call(208,55);
    temp = convert_expression_to_stack_node_tree(SECOND(expression));
    arguments = stack_list_2(temp,
	    convert_expression_to_stack_node_tree(THIRD(expression)));
    gensymed_symbol = make_stack_node_instruction_1_1(Qnext_list_element,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    next_list_element_node = gensymed_symbol;
    SVREF(next_list_element_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(next_list_element_node);
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

/* NEXT-LIST-ELEMENT-I-CHOOSER */
Object next_list_element_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, argument_nodes, type_spec, temp;

    x_note_fn_call(208,56);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,required_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    type_spec = list_constant_3;
    temp = choose_stack_node_instructions_and_types(2,
	    FIRST(argument_nodes),list_constant_10);
    M_FIRST(argument_nodes) = temp;
    temp = choose_stack_node_instructions_and_types(2,
	    SECOND(argument_nodes),Qitem_or_datum);
    M_SECOND(argument_nodes) = temp;
    temp = maybe_add_no_item_implies_unknown(maybe_add_unknown(type_spec,
	    unknown_allowed_qm),no_item_implies_unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

/* NEXT-LIST-ELEMENT-I-EMIT */
Object next_list_element_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object value_type, unknown_is_allowed_qm, no_item_allowed_qm;
    Object argument_nodes;

    x_note_fn_call(208,57);
    value_type = ISVREF(stack_node_instruction,(SI_Long)6L);
    unknown_is_allowed_qm = type_specification_subtype_p(list_constant,
	    value_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    value_type);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    emit_stack_node_tree(byte_code_stream,SECOND(argument_nodes));
    if (unknown_is_allowed_qm)
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)106L));
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)107L));
    emit_evaluate_role_byte_codes(byte_code_stream,list_constant_11,
	    FIX((SI_Long)2L),no_item_allowed_qm,Nil,Nil,Nil);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_17;  /* "The item ~NF is not an attribute of another item." */

/* ATTRIBUTE-ITEM-EVAL-ERROR-MESSAGE */
Object attribute_item_eval_error_message(item)
    Object item;
{
    x_note_fn_call(208,58);
    return tformat_stack_error_text_string(2,string_constant_17,item);
}

static Object string_constant_18;  /* "Cannot compute the ABS of ~NV.  The result is too large to ~
				    *      represent as an integer and cannot be coerced to a float since the ~
				    *      required result type is integer."
				    */

/* ABS-FIXNUM-OVERFLOW-ERROR-MESSAGE */
Object abs_fixnum_overflow_error_message(fixnum_register_1)
    Object fixnum_register_1;
{
    x_note_fn_call(208,59);
    return tformat_stack_error_text_string(2,string_constant_18,
	    fixnum_register_1);
}

static Object string_constant_19;  /* "The ~s function requires ~d or more quantity arguments and ~
				    *               received ~d."
				    */

/* AVERAGE-STACK-NODE-CONVERTER */
Object average_stack_node_converter(expression)
    Object expression;
{
    Object number_of_arguments, temp;

    x_note_fn_call(208,60);
    number_of_arguments = length(CDR(expression));
    if (IFIX(number_of_arguments) < (SI_Long)2L) {
	compiler_error(4,string_constant_19,CAR(expression),
		FIX((SI_Long)2L),number_of_arguments);
	temp = make_dummy_stack_node();
    }
    else
	temp = convert_expression_to_stack_node_tree(phrase_list_3(Qslash,
		phrase_cons(Qplus,CDR(expression)),length(CDR(expression))));
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_20;  /* "Cannot compute the CEILING of ~NV.  The result is outside the ~
				    *    range of integers."
				    */

/* CEILING-FLOAT-ERROR-MESSAGE */
Object ceiling_float_error_message(evaluation_float)
    Object evaluation_float;
{
    x_note_fn_call(208,61);
    return tformat_stack_error_text_string(2,string_constant_20,
	    evaluation_float);
}

static Object string_constant_21;  /* "Cannot compute the FLOOR of ~NV.  The result is too large to ~
				    *    represent as an integer."
				    */

/* FLOOR-EVALUATION-ERROR-MESSAGE */
Object floor_evaluation_error_message(evaluation_float)
    Object evaluation_float;
{
    x_note_fn_call(208,62);
    return tformat_stack_error_text_string(2,string_constant_21,
	    evaluation_float);
}

static Object string_constant_22;  /* "The ~a operator received the negative argument ~a." */

/* NEGATIVE-ARG-EVAL-ERROR-MESSAGE */
Object negative_arg_eval_error_message(negative_arg,evaluator_name)
    Object negative_arg, evaluator_name;
{
    x_note_fn_call(208,63);
    return tformat_stack_error_text_string(3,string_constant_22,
	    evaluator_name,FIXNUMP(negative_arg) || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(negative_arg) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(negative_arg)) == (SI_Long)1L 
	    || INLINE_LONG_VECTOR_P(negative_arg) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(negative_arg)) == (SI_Long)1L ? 
	    evaluation_quantity_value(negative_arg) : negative_arg);
}

/* LOG-10 */
Object log_10(n_1)
    Object n_1;
{
    x_note_fn_call(208,64);
    return llog(n_1,FIX((SI_Long)10L));
}

/* MAX-STACK-NODE-CONVERTER */
Object max_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,65);
    GENSYM_RETURN_ONE(special_form_converter_with_minimum_argument_count(expression,
	    FIX((SI_Long)2L)));
    return VALUES_1(Nil);
}

/* MIN-STACK-NODE-CONVERTER */
Object min_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,66);
    GENSYM_RETURN_ONE(special_form_converter_with_minimum_argument_count(expression,
	    FIX((SI_Long)2L)));
    return VALUES_1(Nil);
}

static Object Qstack_evaluators;   /* stack-evaluators */

/* SPECIAL-FORM-CONVERTER-WITH-MINIMUM-ARGUMENT-COUNT */
Object special_form_converter_with_minimum_argument_count(expression,
	    minimum_argument_count)
    Object expression, minimum_argument_count;
{
    Object instruction_node, stack_evaluator_descriptions_qm, operator_1;
    Object arguments, gensymed_symbol, svref_new_value;

    x_note_fn_call(208,67);
    instruction_node = Nil;
    stack_evaluator_descriptions_qm = Nil;
    operator_1 = FIRST(expression);
    arguments = CDR(expression);
    if (FIXNUM_GE(length(arguments),minimum_argument_count)) {
	stack_evaluator_descriptions_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
		Qstack_evaluators);
	gensymed_symbol = make_stack_node_1_1(operator_1,
		stack_evaluator_descriptions_qm);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	instruction_node = gensymed_symbol;
	svref_new_value = make_stack_argument_nodes(operator_1,arguments,
		stack_evaluator_descriptions_qm);
	SVREF(instruction_node,FIX((SI_Long)2L)) = svref_new_value;
    }
    else {
	instruction_node = make_dummy_stack_node();
	compiler_error(4,string_constant_19,operator_1,
		minimum_argument_count,length(arguments));
    }
    return VALUES_1(instruction_node);
}

static Object string_constant_23;  /* "The result of the ~a expression, ~NV, is out of the range ~
				    *    of integers."
				    */

/* TRUNCATE-EVALUATION-ERROR-MESSAGE */
Object truncate_evaluation_error_message(operation,e_float_1)
    Object operation, e_float_1;
{
    x_note_fn_call(208,68);
    return tformat_stack_error_text_string(3,string_constant_23,operation,
	    e_float_1);
}

static Object Qquotient;           /* quotient */

/* TRUNCATE-EVALUATION-QUANTITIES */
Object truncate_evaluation_quantities(number_1,number_2,top_of_stack)
    Object number_1, number_2, top_of_stack;
{
    Object e_float_1, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float, temp_2, e_float_2, result_1;
    SI_Long result_2;
    char temp_4;
    double aref_new_value, float_register_1, temp_3, arg, arg_1;

    x_note_fn_call(208,69);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_1)) == (SI_Long)1L)
	e_float_1 = number_1;
    else {
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
	if (FIXNUMP(number_1))
	    aref_new_value = (double)IFIX(number_1);
	else if (INLINE_LONG_VECTOR_P(number_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_1)) == (SI_Long)1L) {
	    temp_2 = convert_g2longint_to_double(aref1(number_1,
		    FIX((SI_Long)0L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	}
	else
	    aref_new_value = DFLOAT_ISAREF_1(number_1,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
	reclaim_evaluation_quantity(number_1);
	e_float_1 = temp_2;
    }
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_2) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_2)) == (SI_Long)1L)
	e_float_2 = number_2;
    else {
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
	if (FIXNUMP(number_2))
	    aref_new_value = (double)IFIX(number_2);
	else if (INLINE_LONG_VECTOR_P(number_2) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_2)) == (SI_Long)1L) {
	    temp_2 = convert_g2longint_to_double(aref1(number_2,
		    FIX((SI_Long)0L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	}
	else
	    aref_new_value = DFLOAT_ISAREF_1(number_2,(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
	reclaim_evaluation_quantity(number_2);
	e_float_2 = temp_2;
    }
    aref_new_value = DFLOAT_ISAREF_1(e_float_1,(SI_Long)0L) / 
	    DFLOAT_ISAREF_1(e_float_2,(SI_Long)0L);
    DFLOAT_ISASET_1(e_float_1,(SI_Long)0L,aref_new_value);
    float_register_1 = DFLOAT_ISAREF_1(e_float_1,(SI_Long)0L);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
    arg = float_register_1 - temp_3;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
    temp_4 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_4);
    else {
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	arg = temp_3 - float_register_1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
	temp_4 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_4)
	result_1 = raw_stack_error_named_error(top_of_stack,
		truncate_evaluation_error_message(Qquotient,e_float_1));
    else {
	result_2 = 0.0 < float_register_1 ? 
		inline_floor_1(DFLOAT_ISAREF_1(e_float_1,(SI_Long)0L)) :  
		- inline_floor_1( - float_register_1);
	reclaim_managed_simple_float_array_of_length_1(e_float_1);
	result_1 = FIX(result_2);
    }
    reclaim_managed_simple_float_array_of_length_1(e_float_2);
    return VALUES_1(result_1);
}

/* TRUNCATE-EVALUATION-FLOAT-FUNCTION */
Object truncate_evaluation_float_function(e_float_1,operation,top_of_stack)
    Object e_float_1, operation, top_of_stack;
{
    SI_Long result_1;
    char temp_1;
    double float_register_1, temp, arg, arg_1;

    x_note_fn_call(208,70);
    float_register_1 = DFLOAT_ISAREF_1(e_float_1,(SI_Long)0L);
    temp = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
    arg = float_register_1 - temp;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
    temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_1);
    else {
	temp = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	arg = temp - float_register_1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_1)
	return raw_stack_error_named_error(top_of_stack,
		truncate_evaluation_error_message(operation,e_float_1));
    else {
	result_1 = 0.0 < float_register_1 ? 
		inline_floor_1(DFLOAT_ISAREF_1(e_float_1,(SI_Long)0L)) :  
		- inline_floor_1( - float_register_1);
	reclaim_managed_simple_float_array_of_length_1(e_float_1);
	return VALUES_1(FIX(result_1));
    }
}

Object Plus_recip_most_positive_fixnum_plus = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Random_real_0_result, Qrandom_real_0_result);

/* RANDOM-REAL-0 */
Object random_real_0()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double temp_3, temp_4, aref_new_value;

    x_note_fn_call(208,71);
    if ( !TRUEP(Random_real_0_result)) {
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	Random_real_0_result = new_float;
    }
    temp = Random_real_0_result;
    temp_2 = coerce(g2_random(Most_positive_fixnum),Qdouble_float);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(Plus_recip_most_positive_fixnum_plus);
    aref_new_value = temp_3 * temp_4;
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    return VALUES_1(Random_real_0_result);
}

static Object string_constant_24;  /* "The ~a operator received the non-positive argument ~a." */

/* NON-POSITIVE-ARG-EVAL-ERROR-MESSAGE */
Object non_positive_arg_eval_error_message(non_positive_arg,evaluator_name)
    Object non_positive_arg, evaluator_name;
{
    x_note_fn_call(208,72);
    return tformat_stack_error_text_string(3,string_constant_24,
	    evaluator_name,FIXNUMP(non_positive_arg) || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(non_positive_arg) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(non_positive_arg)) == 
	    (SI_Long)1L || INLINE_LONG_VECTOR_P(non_positive_arg) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(non_positive_arg)) == 
	    (SI_Long)1L ? evaluation_quantity_value(non_positive_arg) : 
	    non_positive_arg);
}

static Object Qiteration_state;    /* iteration-state */

static Object list_constant_12;    /* # */

static Object string_constant_25;  /* " one more than" */

static Object string_constant_26;  /* "" */

static Object string_constant_27;  /* "The ~a operator requires the argument ~a to be less than~a the argument ~a." */

static Object string_constant_28;  /* "The ~a operator requires the start-index, ~a, to be ~
				    *        less than or equal to~a the end-index, ~a."
				    */

/* ARG1-NOT-LESS-THAN-ARG2-EVAL-ERROR-MESSAGE */
Object arg1_not_less_than_arg2_eval_error_message(stack_arg_1,stack_arg_2,
	    argument_p,evaluator_name)
    Object stack_arg_1, stack_arg_2, argument_p, evaluator_name;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, temp_3, temp_4;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(208,73);
    gensymed_symbol = stack_arg_1;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? evaluation_value_value(stack_arg_1) : stack_arg_1;
    temp_2 = memq_function(evaluator_name,list_constant_12) ? 
	    string_constant_25 : string_constant_26;
    gensymed_symbol = stack_arg_2;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_4 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_4);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_4 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_4);
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(5,argument_p ? 
	    string_constant_27 : string_constant_28,evaluator_name,temp_1,
	    temp_2,temp ? evaluation_value_value(stack_arg_2) : stack_arg_2);
}

/* COMPUTE-REMAINDER-QUANTITY */
Object compute_remainder_quantity(numerator_1,denominator_1)
    Object numerator_1, denominator_1;
{
    Object numerator_ef, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float, temp_2, denominator_ef;
    SI_int64 n_1, d;
    double aref_new_value;

    x_note_fn_call(208,74);
    if (FIXNUMP(numerator_1) && FIXNUMP(denominator_1))
	return rem_fixnums(numerator_1,denominator_1);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(numerator_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(numerator_1)) == (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(denominator_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(denominator_1)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(numerator_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(numerator_1)) == (SI_Long)1L)
	    numerator_ef = numerator_1;
	else {
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
	    if (FIXNUMP(numerator_1))
		aref_new_value = (double)IFIX(numerator_1);
	    else if (INLINE_LONG_VECTOR_P(numerator_1) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(numerator_1)) == 
		    (SI_Long)1L) {
		temp_2 = convert_g2longint_to_double(aref1(numerator_1,
			FIX((SI_Long)0L)));
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	    }
	    else
		aref_new_value = DFLOAT_ISAREF_1(numerator_1,(SI_Long)0L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_2 = new_float;
	    reclaim_evaluation_quantity(numerator_1);
	    numerator_ef = temp_2;
	}
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(denominator_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(denominator_1)) == (SI_Long)1L)
	    denominator_ef = denominator_1;
	else {
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
	    if (FIXNUMP(denominator_1))
		aref_new_value = (double)IFIX(denominator_1);
	    else if (INLINE_LONG_VECTOR_P(denominator_1) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(denominator_1)) == 
		    (SI_Long)1L) {
		temp_2 = convert_g2longint_to_double(aref1(denominator_1,
			FIX((SI_Long)0L)));
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	    }
	    else
		aref_new_value = DFLOAT_ISAREF_1(denominator_1,(SI_Long)0L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_2 = new_float;
	    reclaim_evaluation_quantity(denominator_1);
	    denominator_ef = temp_2;
	}
	return compute_remainder_float(numerator_ef,denominator_ef);
    }
    else {
	if (FIXNUMP(numerator_1))
	    numerator_1 = make_evaluation_long(numerator_1);
	if (FIXNUMP(denominator_1))
	    denominator_1 = make_evaluation_long(denominator_1);
	temp_2 = aref1(numerator_1,FIX((SI_Long)0L));
	n_1 = INTEGER_TO_INT64(temp_2);
	temp_2 = aref1(denominator_1,FIX((SI_Long)0L));
	d = INTEGER_TO_INT64(temp_2);
	temp_2 = make_evaluation_long(minus(INT64_TO_INTEGER(n_1),
		ltimes(divide(INT64_TO_INTEGER(n_1),INT64_TO_INTEGER(d)),
		INT64_TO_INTEGER(d))));
	reclaim_managed_simple_long_array_of_length_1(numerator_1);
	reclaim_managed_simple_long_array_of_length_1(denominator_1);
	return VALUES_1(temp_2);
    }
}

/* COMPUTE-REMAINDER-FLOAT */
Object compute_remainder_float(numerator_ef,denominator_ef)
    Object numerator_ef, denominator_ef;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, remainder_result;
    double aref_new_value;

    x_note_fn_call(208,75);
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
    aref_new_value = DFLOAT_ISAREF_1(numerator_ef,(SI_Long)0L) / 
	    DFLOAT_ISAREF_1(denominator_ef,(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    remainder_result = new_float;
    aref_new_value = 0.0 > DFLOAT_ISAREF_1(remainder_result,(SI_Long)0L) ? 
	     - inline_ffloor_1( - DFLOAT_ISAREF_1(remainder_result,
	    (SI_Long)0L)) : 
	    inline_ffloor_1(DFLOAT_ISAREF_1(remainder_result,(SI_Long)0L));
    DFLOAT_ISASET_1(remainder_result,(SI_Long)0L,aref_new_value);
    aref_new_value = DFLOAT_ISAREF_1(numerator_ef,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(denominator_ef,(SI_Long)0L) * 
	    DFLOAT_ISAREF_1(remainder_result,(SI_Long)0L);
    DFLOAT_ISASET_1(remainder_result,(SI_Long)0L,aref_new_value);
    reclaim_managed_simple_float_array_of_length_1(numerator_ef);
    reclaim_managed_simple_float_array_of_length_1(denominator_ef);
    return VALUES_1(remainder_result);
}

/* EVAL-TRUTH-VALUE-OF-TRUTH-VALUE-FUNCALLED */
Object eval_truth_value_of_truth_value_funcalled(truth_value)
    Object truth_value;
{
    x_note_fn_call(208,76);
    return VALUES_1(truth_value);
}

static Object string_constant_29;  /* "Unknown kind of number, ~NV, given to truth-value." */

/* INVALID-ARGUMENT-TO-TRUTH-VALUE-MESSAGE */
Object invalid_argument_to_truth_value_message(number)
    Object number;
{
    x_note_fn_call(208,77);
    return tformat_stack_error_text_string(2,string_constant_29,number);
}

/* EVAL-TRUTH-VALUE-QUANTITY-FUNCALLED */
Object eval_truth_value_quantity_funcalled(quantity)
    Object quantity;
{
    Object quantity_value, result_1, temp_1;
    double arg, arg_1, temp, float_1;

    x_note_fn_call(208,78);
    quantity_value = evaluation_quantity_value(quantity);
    if (FIXNUMP(quantity_value)) {
	if (IFIX(quantity_value) >= (SI_Long)1L)
	    result_1 = Truth;
	else if (IFIX(quantity_value) == (SI_Long)0L)
	    result_1 = FIX((SI_Long)0L);
	else
	    result_1 = Falsity;
    }
    else if (FLOATP(quantity_value)) {
	arg = DOUBLE_FLOAT_TO_DOUBLE(quantity_value);
	arg_1 = 1.0;
	if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    result_1 = Truth;
	else {
	    arg = DOUBLE_FLOAT_TO_DOUBLE(quantity_value);
	    arg_1 = -1.0;
	    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		result_1 = Falsity;
	    else {
		temp = DOUBLE_FLOAT_TO_DOUBLE(quantity_value);
		float_1 = temp * 1000.0;
		arg = float_1;
		arg_1 = 0.0;
		result_1 = ltruncate(arg > arg_1 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1) ? 
			DOUBLE_TO_DOUBLE_FLOAT(float_1 + 0.5) : 
			DOUBLE_TO_DOUBLE_FLOAT(float_1 - 0.5),_);
	    }
	}
    }
    else
	result_1 = Qnil;
    if ( !TRUEP(result_1)) {
	temp_1 = Cached_top_of_stack;
	raw_stack_error_named_error(temp_1,
		invalid_argument_to_truth_value_message(quantity));
    }
    if (FIXNUM_EQ(result_1,Truth))
	result_1 = Evaluation_true_value;
    else if (FIXNUM_EQ(result_1,Falsity))
	result_1 = Evaluation_false_value;
    else
	result_1 = eval_cons_1(result_1,Qtruth_value);
    reclaim_evaluation_quantity(quantity);
    return VALUES_1(result_1);
}

/* EVAL-TRUTH-VALUE-INTEGER-FUNCALLED */
Object eval_truth_value_integer_funcalled(integer_arg)
    Object integer_arg;
{
    Object integer_value, result_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(208,79);
    integer_value = integer_arg;
    result_1 = Nil;
    if (IFIX(integer_value) >= (SI_Long)1L)
	result_1 = Evaluation_true_value;
    else if (IFIX(integer_value) <= (SI_Long)-1L)
	result_1 = Evaluation_false_value;
    else {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = Qtruth_value;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	result_1 = gensymed_symbol;
    }
    return VALUES_1(result_1);
}

/* EVAL-TRUTH-VALUE-FLOAT-FUNCALLED */
Object eval_truth_value_float_funcalled(float_1)
    Object float_1;
{
    Object result_1;
    double float_value, arg, arg_1, float_2;

    x_note_fn_call(208,80);
    float_value = DFLOAT_ISAREF_1(float_1,(SI_Long)0L);
    arg = float_value;
    arg_1 = 1.0;
    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	result_1 = Truth;
    else {
	arg = float_value;
	arg_1 = -1.0;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    result_1 = Falsity;
	else {
	    float_2 = float_value * 1000.0;
	    arg = float_2;
	    arg_1 = 0.0;
	    result_1 = ltruncate(arg > arg_1 &&  
		    !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1) ? 
		    DOUBLE_TO_DOUBLE_FLOAT(float_2 + 0.5) : 
		    DOUBLE_TO_DOUBLE_FLOAT(float_2 - 0.5),_);
	}
    }
    if (FIXNUM_EQ(result_1,Truth))
	result_1 = Evaluation_true_value;
    else if (FIXNUM_EQ(result_1,Falsity))
	result_1 = Evaluation_false_value;
    else
	result_1 = eval_cons_1(result_1,Qtruth_value);
    reclaim_managed_simple_float_array_of_length_1(float_1);
    return VALUES_1(result_1);
}

/* TRUTH-VALUE-EVALUATION-NUMBER */
Object truth_value_evaluation_number(evaluation_number,top_of_stack)
    Object evaluation_number, top_of_stack;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(208,81);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_number)) == (SI_Long)1L)
	return truth_value_evaluation_float(evaluation_number,top_of_stack);
    else if (IFIX(evaluation_number) >= (SI_Long)1L)
	return VALUES_1(Evaluation_true_value);
    else if (IFIX(evaluation_number) <= (SI_Long)-1L)
	return VALUES_1(Evaluation_false_value);
    else {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = FIX((SI_Long)0L);
	M_CDR(gensymed_symbol) = Qtruth_value;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	return VALUES_1(gensymed_symbol);
    }
}

/* TRUTH-VALUE-EVALUATION-FLOAT */
Object truth_value_evaluation_float(evaluation_float,top_of_stack)
    Object evaluation_float, top_of_stack;
{
    Object gensymed_symbol;
    SI_Long result_1;
    char temp_1;
    double arg, arg_1, aref_new_value, float_register_1, temp;

    x_note_fn_call(208,82);
    arg = DFLOAT_ISAREF_1(evaluation_float,(SI_Long)0L);
    arg_1 = 1.0;
    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	reclaim_managed_simple_float_array_of_length_1(evaluation_float);
	return VALUES_1(Evaluation_true_value);
    }
    else {
	arg = DFLOAT_ISAREF_1(evaluation_float,(SI_Long)0L);
	arg_1 = -1.0;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    reclaim_managed_simple_float_array_of_length_1(evaluation_float);
	    return VALUES_1(Evaluation_false_value);
	}
	else {
	    aref_new_value = DFLOAT_ISAREF_1(evaluation_float,(SI_Long)0L) 
		    * 1000.0;
	    DFLOAT_ISASET_1(evaluation_float,(SI_Long)0L,aref_new_value);
	    aref_new_value = 0.0 < DFLOAT_ISAREF_1(evaluation_float,
		    (SI_Long)0L) ? DFLOAT_ISAREF_1(evaluation_float,
		    (SI_Long)0L) + 0.5 : DFLOAT_ISAREF_1(evaluation_float,
		    (SI_Long)0L) - 0.5;
	    DFLOAT_ISASET_1(evaluation_float,(SI_Long)0L,aref_new_value);
	    float_register_1 = DFLOAT_ISAREF_1(evaluation_float,(SI_Long)0L);
	    temp = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	    arg = float_register_1 - temp;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
	    temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp_1);
	    else {
		temp = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		arg = temp - float_register_1;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Rational_float_epsilon);
		temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp_1)
		gensymed_symbol = raw_stack_error_named_error(top_of_stack,
			truncate_evaluation_error_message(Qround,
			evaluation_float));
	    else {
		result_1 = 0.0 < float_register_1 ? 
			inline_floor_1(DFLOAT_ISAREF_1(evaluation_float,
			(SI_Long)0L)) :  - inline_floor_1( - float_register_1);
		reclaim_managed_simple_float_array_of_length_1(evaluation_float);
		gensymed_symbol = FIX(result_1);
	    }
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		return VALUES_1(Evaluation_true_value);
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		return VALUES_1(Evaluation_false_value);
	    else
		return eval_cons_1(gensymed_symbol,Qtruth_value);
	}
    }
}

/* EVAL-IS-CONTAINED-IN-TEXT-FUNCALLED */
Object eval_is_contained_in_text_funcalled(locate_text,original_text)
    Object locate_text, original_text;
{
    Object locate_text_value, original_text_value, result_1;

    x_note_fn_call(208,83);
    locate_text_value = locate_text;
    original_text_value = original_text;
    result_1 = text_string_search(locate_text_value,original_text_value,
	    Nil,Nil) ? Evaluation_true_value : Evaluation_false_value;
    reclaim_text_string(locate_text);
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

/* EVAL-LENGTH-OF-TEXT-FUNCALLED */
Object eval_length_of_text_funcalled(original_text)
    Object original_text;
{
    Object result_1;

    x_note_fn_call(208,84);
    result_1 = text_string_length(original_text);
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

/* EVAL-POSITION-OF-TEXT-FUNCALLED */
Object eval_position_of_text_funcalled(locate_text,original_text)
    Object locate_text, original_text;
{
    Object locate_text_value, original_text_value, result_1, temp;

    x_note_fn_call(208,85);
    locate_text_value = locate_text;
    original_text_value = original_text;
    result_1 = text_string_search(locate_text_value,original_text_value,
	    Nil,Nil);
    reclaim_text_string(locate_text);
    reclaim_text_string(original_text);
    temp = result_1 ? FIXNUM_ADD1(result_1) : FIX((SI_Long)0L);
    return VALUES_1(temp);
}

static Object Qunderflow;          /* underflow */

static Object Qoverflow;           /* overflow */

/* EVAL-TEXT-BEGINS-WITH-QUANTITY-FUNCALLED */
Object eval_text_begins_with_quantity_funcalled(original_text)
    Object original_text;
{
    Object number_qm, result_1;

    x_note_fn_call(208,86);
    number_qm = read_number_from_text_string(1,original_text);
    result_1 =  !( !TRUEP(number_qm) || EQ(number_qm,Qunderflow) || 
	    EQ(number_qm,Qoverflow)) ? Evaluation_true_value : 
	    Evaluation_false_value;
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

static Object Kall;                /* :all */

/* EVAL-UPPER-CASE-TEXT-FUNCALLED */
Object eval_upper_case_text_funcalled(original_text)
    Object original_text;
{
    Object original_text_value, result_1;

    x_note_fn_call(208,87);
    original_text_value = original_text;
    result_1 = copy_text_string_with_case_conversion(original_text_value,Kall);
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

static Object Knone;               /* :none */

/* EVAL-LOWER-CASE-TEXT-FUNCALLED */
Object eval_lower_case_text_funcalled(original_text)
    Object original_text;
{
    Object original_text_value, result_1;

    x_note_fn_call(208,88);
    original_text_value = original_text;
    result_1 = copy_text_string_with_case_conversion(original_text_value,
	    Knone);
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

static Object Kfirst_of_each_word;  /* :first-of-each-word */

/* EVAL-CAPITALIZE-WORDS-FUNCALLED */
Object eval_capitalize_words_funcalled(original_text)
    Object original_text;
{
    Object original_text_value, result_1;

    x_note_fn_call(208,89);
    original_text_value = original_text;
    result_1 = copy_text_string_with_case_conversion(original_text_value,
	    Kfirst_of_each_word);
    reclaim_text_string(original_text);
    return VALUES_1(result_1);
}

static Object string_constant_30;  /* "The ~a evaluator failed to produce an answer despite the fact~
				    *    that it's arguments were within bounds.  Please report this~
				    *    internal error to Gensym software support with the source code
				    *    of the item named in the error message."
				    */

/* UNKNOWN-TEXT-EVAL-ERROR-MESSAGE */
Object unknown_text_eval_error_message(evaluator_name)
    Object evaluator_name;
{
    x_note_fn_call(208,90);
    return tformat_stack_error_text_string(2,string_constant_30,
	    evaluator_name);
}

/* REPORT-TEXT-INDICES-ERROR */
Object report_text_indices_error(original_text,start_index,end_index,
	    evaluator_name)
    Object original_text, start_index, end_index, evaluator_name;
{
    Object original_text_value, original_text_length, start_index_value;
    Object end_index_value, temp;

    x_note_fn_call(208,91);
    original_text_value = original_text;
    original_text_length = text_string_length(original_text);
    start_index_value = start_index;
    end_index_value =  !TRUEP(end_index) ? original_text_length : end_index;
    if (IFIX(start_index_value) < (SI_Long)1L) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		non_positive_arg_eval_error_message(start_index_value,
		evaluator_name));
    }
    else if (IFIX(end_index_value) < (SI_Long)1L) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		non_positive_arg_eval_error_message(end_index_value,
		evaluator_name));
    }
    else if (FIXNUM_GT(start_index_value,original_text_length))
	index_of_g2_text_too_large_eval_error(start_index_value,
		original_text_value,evaluator_name,Cached_top_of_stack);
    else if (FIXNUM_GT(end_index_value,original_text_length))
	index_of_g2_text_too_large_eval_error(end_index_value,
		original_text_value,evaluator_name,Cached_top_of_stack);
    else if (FIXNUM_GT(start_index_value,end_index_value)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		arg1_not_less_than_arg2_eval_error_message(start_index_value,
		end_index_value,Nil,evaluator_name));
    }
    else {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		unknown_text_eval_error_message(evaluator_name));
    }
    if (end_index)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

static Object Qinsert_in_text;     /* insert-in-text */

/* EVAL-INSERT-IN-TEXT-FUNCALLED */
Object eval_insert_in_text_funcalled(text_to_insert,original_text,start_index)
    Object text_to_insert, original_text, start_index;
{
    Object end_index, original_text_value, original_text_length;
    Object start_index_value, end_index_value, text_to_insert_value, result_1;
    Object temp;

    x_note_fn_call(208,92);
    end_index = Nil;
    original_text_value = original_text;
    original_text_length = text_string_length(original_text);
    start_index_value = start_index;
    end_index_value =  !TRUEP(end_index) ? original_text_length : end_index;
    text_to_insert_value = text_to_insert ? text_to_insert : Qnil;
    result_1 = insert_in_g2_text(text_to_insert_value,original_text_value,
	    start_index_value);
    if ( !TRUEP(result_1)) {
	if (text_to_insert_value && 
		FIXNUM_GT(FIXNUM_ADD(original_text_length,
		text_string_length(text_to_insert_value)),
		Maximum_length_for_user_text_strings))
	    merged_string_would_be_too_long_eval_error(original_text_value,
		    text_to_insert_value,Qinsert_in_text,Cached_top_of_stack);
	else if (IFIX(start_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(start_index_value,
		    Qinsert_in_text));
	}
	else if (IFIX(end_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(end_index_value,
		    Qinsert_in_text));
	}
	else if (FIXNUM_GT(start_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(start_index_value,
		    original_text_value,Qinsert_in_text,Cached_top_of_stack);
	else if (FIXNUM_GT(end_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(end_index_value,
		    original_text_value,Qinsert_in_text,Cached_top_of_stack);
	else if (FIXNUM_GT(start_index_value,end_index_value)) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    arg1_not_less_than_arg2_eval_error_message(start_index_value,
		    end_index_value,Nil,Qinsert_in_text));
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    unknown_text_eval_error_message(Qinsert_in_text));
	}
    }
    reclaim_text_string(original_text);
    if (text_to_insert)
	reclaim_text_string(text_to_insert);
    return VALUES_1(result_1);
}

static Object Qomit_from_text;     /* omit-from-text */

/* EVAL-OMIT-FROM-TEXT-FUNCALLED */
Object eval_omit_from_text_funcalled(original_text,start_index,end_index)
    Object original_text, start_index, end_index;
{
    Object text_to_insert, original_text_value, original_text_length;
    Object start_index_value, end_index_value, text_to_insert_value, result_1;
    Object temp;

    x_note_fn_call(208,93);
    text_to_insert = Nil;
    original_text_value = original_text;
    original_text_length = text_string_length(original_text);
    start_index_value = start_index;
    end_index_value =  !TRUEP(end_index) ? original_text_length : end_index;
    text_to_insert_value = text_to_insert ? text_to_insert : Qnil;
    result_1 = omit_from_g2_text(original_text_value,start_index_value,
	    end_index_value);
    if ( !TRUEP(result_1)) {
	if (text_to_insert_value && 
		FIXNUM_GT(FIXNUM_ADD(original_text_length,
		text_string_length(text_to_insert_value)),
		Maximum_length_for_user_text_strings))
	    merged_string_would_be_too_long_eval_error(original_text_value,
		    text_to_insert_value,Qomit_from_text,Cached_top_of_stack);
	else if (IFIX(start_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(start_index_value,
		    Qomit_from_text));
	}
	else if (IFIX(end_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(end_index_value,
		    Qomit_from_text));
	}
	else if (FIXNUM_GT(start_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(start_index_value,
		    original_text_value,Qomit_from_text,Cached_top_of_stack);
	else if (FIXNUM_GT(end_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(end_index_value,
		    original_text_value,Qomit_from_text,Cached_top_of_stack);
	else if (FIXNUM_GT(start_index_value,end_index_value)) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    arg1_not_less_than_arg2_eval_error_message(start_index_value,
		    end_index_value,Nil,Qomit_from_text));
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    unknown_text_eval_error_message(Qomit_from_text));
	}
    }
    reclaim_text_string(original_text);
    if (text_to_insert)
	reclaim_text_string(text_to_insert);
    return VALUES_1(result_1);
}

static Object Qget_from_text;      /* get-from-text */

/* EVAL-GET-FROM-TEXT-FUNCALLED */
Object eval_get_from_text_funcalled(original_text,start_index,end_index)
    Object original_text, start_index, end_index;
{
    Object text_to_insert, original_text_value, original_text_length;
    Object start_index_value, end_index_value, text_to_insert_value, result_1;
    Object temp;

    x_note_fn_call(208,94);
    text_to_insert = Nil;
    original_text_value = original_text;
    original_text_length = text_string_length(original_text);
    start_index_value = start_index;
    end_index_value =  !TRUEP(end_index) ? original_text_length : end_index;
    text_to_insert_value = text_to_insert ? text_to_insert : Qnil;
    result_1 = get_from_g2_text(original_text_value,start_index_value,
	    end_index_value);
    if ( !TRUEP(result_1)) {
	if (text_to_insert_value && 
		FIXNUM_GT(FIXNUM_ADD(original_text_length,
		text_string_length(text_to_insert_value)),
		Maximum_length_for_user_text_strings))
	    merged_string_would_be_too_long_eval_error(original_text_value,
		    text_to_insert_value,Qget_from_text,Cached_top_of_stack);
	else if (IFIX(start_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(start_index_value,
		    Qget_from_text));
	}
	else if (IFIX(end_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(end_index_value,
		    Qget_from_text));
	}
	else if (FIXNUM_GT(start_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(start_index_value,
		    original_text_value,Qget_from_text,Cached_top_of_stack);
	else if (FIXNUM_GT(end_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(end_index_value,
		    original_text_value,Qget_from_text,Cached_top_of_stack);
	else if (FIXNUM_GT(start_index_value,end_index_value)) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    arg1_not_less_than_arg2_eval_error_message(start_index_value,
		    end_index_value,Nil,Qget_from_text));
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    unknown_text_eval_error_message(Qget_from_text));
	}
    }
    reclaim_text_string(original_text);
    if (text_to_insert)
	reclaim_text_string(text_to_insert);
    return VALUES_1(result_1);
}

static Object Qreplace_in_text;    /* replace-in-text */

/* EVAL-REPLACE-IN-TEXT-FUNCALLED */
Object eval_replace_in_text_funcalled(text_to_insert,original_text,
	    start_index,end_index)
    Object text_to_insert, original_text, start_index, end_index;
{
    Object original_text_value, original_text_length, start_index_value;
    Object end_index_value, text_to_insert_value, result_1, temp;

    x_note_fn_call(208,95);
    original_text_value = original_text;
    original_text_length = text_string_length(original_text);
    start_index_value = start_index;
    end_index_value =  !TRUEP(end_index) ? original_text_length : end_index;
    text_to_insert_value = text_to_insert ? text_to_insert : Qnil;
    result_1 = replace_in_g2_text(text_to_insert_value,original_text_value,
	    start_index_value,end_index_value);
    if ( !TRUEP(result_1)) {
	if (text_to_insert_value && 
		FIXNUM_GT(FIXNUM_ADD(original_text_length,
		text_string_length(text_to_insert_value)),
		Maximum_length_for_user_text_strings))
	    merged_string_would_be_too_long_eval_error(original_text_value,
		    text_to_insert_value,Qreplace_in_text,Cached_top_of_stack);
	else if (IFIX(start_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(start_index_value,
		    Qreplace_in_text));
	}
	else if (IFIX(end_index_value) < (SI_Long)1L) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    non_positive_arg_eval_error_message(end_index_value,
		    Qreplace_in_text));
	}
	else if (FIXNUM_GT(start_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(start_index_value,
		    original_text_value,Qreplace_in_text,Cached_top_of_stack);
	else if (FIXNUM_GT(end_index_value,original_text_length))
	    index_of_g2_text_too_large_eval_error(end_index_value,
		    original_text_value,Qreplace_in_text,Cached_top_of_stack);
	else if (FIXNUM_GT(start_index_value,end_index_value)) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    arg1_not_less_than_arg2_eval_error_message(start_index_value,
		    end_index_value,Nil,Qreplace_in_text));
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    unknown_text_eval_error_message(Qreplace_in_text));
	}
    }
    reclaim_text_string(original_text);
    if (text_to_insert)
	reclaim_text_string(text_to_insert);
    return VALUES_1(result_1);
}

/* BAD-REGULAR-EXPRESSION-ERROR-MESSAGE */
Object bad_regular_expression_error_message(pattern,evaluator_name,
	    preprocessor_errors_qm)
    Object pattern, evaluator_name, preprocessor_errors_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(208,96);
    PUSH_SPECIAL_WITH_SYMBOL(Preprocessor_errors_qm,Qpreprocessor_errors_qm,preprocessor_errors_qm,
	    0);
      result = tformat_stack_error_text_string(1,
	      make_error_string_for_bad_regular_expression(pattern,
	      evaluator_name,Preprocessor_errors_qm));
    POP_SPECIAL();
    return result;
}

static Object Qfind_next_pattern;  /* find-next-pattern */

static Object Qg2_defstruct_structure_name_lexing_table_g2_struct;  /* g2-defstruct-structure-name::lexing-table-g2-struct */

/* EVAL-FIND-NEXT-PATTERN-3-FUNCALLED */
Object eval_find_next_pattern_3_funcalled(search_pattern,source_text,
	    search_position)
    Object search_pattern, source_text, search_position;
{
    Object source_text_value, search_position_value, lexing_table;
    Object search_pattern_value, source_text_length, result_1, temp;

    x_note_fn_call(208,97);
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_pattern,Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_pattern,Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct))
	    result_1 = indices_for_match(lexing_table,source_text_value,
		    search_position_value);
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_next_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    return VALUES_1(result_1);
}

static Object Qfind_next_substring_matching_pattern;  /* find-next-substring-matching-pattern */

/* EVAL-FIND-NEXT-SUBSTRING-MATCHING-PATTERN-3-FUNCALLED */
Object eval_find_next_substring_matching_pattern_3_funcalled(search_pattern,
	    source_text,search_position)
    Object search_pattern, source_text, search_position;
{
    Object source_text_value, search_position_value, lexing_table;
    Object search_pattern_value, source_text_length, result_1, temp;

    x_note_fn_call(208,98);
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_substring_matching_pattern,
		Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_substring_matching_pattern,
		Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct))
	    result_1 = substring_for_match(lexing_table,source_text_value,
		    search_position_value);
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_next_substring_matching_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    return VALUES_1(result_1);
}

static Object Qfind_and_replace_pattern;  /* find-and-replace-pattern */

/* EVAL-FIND-AND-REPLACE-PATTERN-5-FUNCALLED */
Object eval_find_and_replace_pattern_5_funcalled(search_pattern,
	    text_to_insert,source_text,search_position,end_position)
    Object search_pattern, text_to_insert, source_text, search_position;
    Object end_position;
{
    Object end_position_value, text_to_insert_value, source_text_value;
    Object search_position_value, lexing_table, search_pattern_value;
    Object source_text_length, result_1, search_position_value_1;
    Object end_position_value_1, source_text_value_1, source_text_length_1;
    Object temp;

    x_note_fn_call(208,99);
    end_position_value = end_position;
    text_to_insert_value = text_to_insert;
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_and_replace_pattern,
		Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_and_replace_pattern,
		Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct)) {
	    search_position_value_1 = search_position;
	    end_position_value_1 = end_position;
	    source_text_value_1 = source_text;
	    source_text_length_1 = text_string_length(source_text);
	    if (FIXNUM_GT(end_position_value_1,source_text_length_1))
		index_of_g2_text_too_large_eval_error(end_position_value_1,
			source_text_value_1,Qfind_and_replace_pattern,
			Cached_top_of_stack);
	    else if (IFIX(end_position_value_1) < (SI_Long)1L)
		index_of_g2_text_too_large_eval_error(end_position_value_1,
			source_text_value,Qfind_and_replace_pattern,
			Cached_top_of_stack);
	    else if (FIXNUM_GT(search_position_value_1,end_position_value_1)) {
		temp = Cached_top_of_stack;
		raw_stack_error_named_error(temp,
			arg1_not_less_than_arg2_eval_error_message(search_position_value_1,
			end_position_value_1,Nil,Qfind_and_replace_pattern));
	    }
	    else
		result_1 = text_with_replacements(lexing_table,
			text_to_insert_value,source_text_value,
			search_position_value,end_position_value);
	    reclaim_text_string(text_to_insert);
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_and_replace_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    return VALUES_1(result_1);
}

/* EVAL-FIND-NEXT-PATTERN-4-FUNCALLED */
Object eval_find_next_pattern_4_funcalled(search_pattern,source_text,
	    search_position,other_args)
    Object search_pattern, source_text, search_position, other_args;
{
    Object other_args_value, source_text_value, search_position_value;
    Object lexing_table, search_pattern_value, source_text_length, result_1;
    Object temp;

    x_note_fn_call(208,100);
    other_args_value = M_CAR(other_args);
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_pattern,Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_pattern,Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct))
	    result_1 = indices_for_match(lexing_table,source_text_value,
		    search_position_value);
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_next_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    reclaim_evaluation_structure(other_args);
    return VALUES_1(result_1);
}

/* EVAL-FIND-NEXT-SUBSTRING-MATCHING-PATTERN-4-FUNCALLED */
Object eval_find_next_substring_matching_pattern_4_funcalled(search_pattern,
	    source_text,search_position,other_args)
    Object search_pattern, source_text, search_position, other_args;
{
    Object other_args_value, source_text_value, search_position_value;
    Object lexing_table, search_pattern_value, source_text_length, result_1;
    Object temp;

    x_note_fn_call(208,101);
    other_args_value = M_CAR(other_args);
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_substring_matching_pattern,
		Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_next_substring_matching_pattern,
		Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct))
	    result_1 = substring_for_match(lexing_table,source_text_value,
		    search_position_value);
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_next_substring_matching_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    reclaim_evaluation_structure(other_args);
    return VALUES_1(result_1);
}

/* EVAL-FIND-AND-REPLACE-PATTERN-6-FUNCALLED */
Object eval_find_and_replace_pattern_6_funcalled(search_pattern,
	    text_to_insert,source_text,search_position,end_position,other_args)
    Object search_pattern, text_to_insert, source_text, search_position;
    Object end_position, other_args;
{
    Object end_position_value, text_to_insert_value, other_args_value;
    Object source_text_value, search_position_value, lexing_table;
    Object search_pattern_value, source_text_length, result_1;
    Object search_position_value_1, end_position_value_1, source_text_value_1;
    Object source_text_length_1, temp;

    x_note_fn_call(208,102);
    end_position_value = end_position;
    text_to_insert_value = text_to_insert;
    other_args_value = M_CAR(other_args);
    source_text_value = source_text;
    search_position_value = search_position;
    lexing_table = Nil;
    search_pattern_value = search_pattern;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_and_replace_pattern,
		Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)1L)
	index_of_g2_text_too_large_eval_error(search_position_value,
		source_text_value,Qfind_and_replace_pattern,
		Cached_top_of_stack);
    else {
	lexing_table = get_lexing_table_for_regexp(search_pattern_value);
	if (SIMPLE_VECTOR_P(lexing_table) && EQ(ISVREF(lexing_table,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_lexing_table_g2_struct)) {
	    search_position_value_1 = search_position;
	    end_position_value_1 = end_position;
	    source_text_value_1 = source_text;
	    source_text_length_1 = text_string_length(source_text);
	    if (FIXNUM_GT(end_position_value_1,source_text_length_1))
		index_of_g2_text_too_large_eval_error(end_position_value_1,
			source_text_value_1,Qfind_and_replace_pattern,
			Cached_top_of_stack);
	    else if (IFIX(end_position_value_1) < (SI_Long)1L)
		index_of_g2_text_too_large_eval_error(end_position_value_1,
			source_text_value,Qfind_and_replace_pattern,
			Cached_top_of_stack);
	    else if (FIXNUM_GT(search_position_value_1,end_position_value_1)) {
		temp = Cached_top_of_stack;
		raw_stack_error_named_error(temp,
			arg1_not_less_than_arg2_eval_error_message(search_position_value_1,
			end_position_value_1,Nil,Qfind_and_replace_pattern));
	    }
	    else
		result_1 = text_with_replacements(lexing_table,
			text_to_insert_value,source_text_value,
			search_position_value,end_position_value);
	    reclaim_text_string(text_to_insert);
	}
	else {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    bad_regular_expression_error_message(search_pattern_value,
		    Qfind_and_replace_pattern,lexing_table));
	}
    }
    reclaim_text_string(source_text);
    reclaim_text_string(search_pattern_value);
    reclaim_evaluation_structure(other_args);
    return VALUES_1(result_1);
}

static Object string_constant_31;  /* "Tokenizer ~NF was passed to ~a, but it is not OK:~%~s~%" */

/* BAD-TOKENIZER-SPECIFICATION-ERROR-MESSAGE */
Object bad_tokenizer_specification_error_message(tokenizer,evaluator_name)
    Object tokenizer, evaluator_name;
{
    x_note_fn_call(208,103);
    return tformat_stack_error_text_string(3,string_constant_31,tokenizer,
	    evaluator_name);
}

static Object Qget_next_token;     /* get-next-token */

/* EVAL-GET-NEXT-TOKEN-3-FUNCALLED */
Object eval_get_next_token_3_funcalled(tokenizer,source_text,search_position)
    Object tokenizer, source_text, search_position;
{
    Object search_position_value, source_text_value, source_text_length;
    Object result_1, temp, result_struct;

    x_note_fn_call(208,104);
    search_position_value = FIXNUM_SUB1(search_position);
    source_text_value = source_text;
    source_text_length = text_string_length(source_text_value);
    result_1 = Nil;
    if (ISVREF(tokenizer,(SI_Long)8L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		bad_tokenizer_specification_error_message(tokenizer,
		Qget_next_token));
    }
    else if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(FIXNUM_ADD1(search_position_value),
		source_text_value,Qget_next_token,Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)0L)
	index_of_g2_text_too_large_eval_error(FIXNUM_ADD1(search_position_value),
		source_text_value,Qget_next_token,Cached_top_of_stack);
    else {
	result_struct = search_for_match_using_tokenizer(tokenizer,
		source_text_value,search_position_value);
	result_1 = 
		make_evaluation_structure_from_parse_object_reclaiming_it(result_struct);
    }
    reclaim_text_string(source_text);
    return VALUES_1(result_1);
}

/* EVAL-GET-NEXT-TOKEN-4-FUNCALLED */
Object eval_get_next_token_4_funcalled(tokenizer,source_text,
	    search_position,include_string_p_arg)
    Object tokenizer, source_text, search_position, include_string_p_arg;
{
    Object search_position_value, source_text_value, source_text_length;
    Object include_string_p, result_1, temp, result_struct;

    x_note_fn_call(208,105);
    search_position_value = FIXNUM_SUB1(search_position);
    source_text_value = source_text;
    source_text_length = text_string_length(source_text_value);
    include_string_p = M_CAR(include_string_p_arg);
    result_1 = Nil;
    if (ISVREF(tokenizer,(SI_Long)8L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		bad_tokenizer_specification_error_message(tokenizer,
		Qget_next_token));
    }
    else if (FIXNUM_GT(search_position_value,source_text_length))
	index_of_g2_text_too_large_eval_error(FIXNUM_ADD1(search_position_value),
		source_text_value,Qget_next_token,Cached_top_of_stack);
    else if (IFIX(search_position_value) < (SI_Long)0L)
	index_of_g2_text_too_large_eval_error(FIXNUM_ADD1(search_position_value),
		source_text_value,Qget_next_token,Cached_top_of_stack);
    else {
	result_struct = search_for_match_using_tokenizer(tokenizer,
		source_text_value,search_position_value);
	result_1 = include_string_p ? 
		make_evaluation_structure_with_text_from_parse_object_reclaiming_it(result_struct,
		source_text) : 
		make_evaluation_structure_from_parse_object_reclaiming_it(result_struct);
    }
    reclaim_text_string(source_text);
    return VALUES_1(result_1);
}

static Object Qstart_index;        /* start-index */

static Object Qend_index;          /* end-index */

static Object array_constant_1;    /* # */

/* EVAL-LEXEME-FUNCALLED */
Object eval_lexeme_funcalled(source_text,token)
    Object source_text, token;
{
    Object match_start, match_end, temp;

    x_note_fn_call(208,106);
    match_start = structure_slot_1(CAR(token),Qstart_index,
	    No_tokenizer_match_start_index);
    match_end = structure_slot_1(CAR(token),Qend_index,
	    No_tokenizer_match_end_index);
    temp = FIXNUM_EQ(match_end,No_tokenizer_match_end_index) ? 
	    copy_as_wide_string(array_constant_1) : 
	    get_from_g2_text(source_text,match_start,match_end);
    return VALUES_1(temp);
}

static Object string_constant_32;  /* "The ~a function received a text argument \"\"." */

/* EMPTY-STRING-EVAL-ERROR-MESSAGE */
Object empty_string_eval_error_message(evaluator_name)
    Object evaluator_name;
{
    x_note_fn_call(208,107);
    return tformat_stack_error_text_string(2,string_constant_32,
	    evaluator_name);
}

static Object string_constant_33;  /* "The ~a function could not convert the argument ~NV to type ~a." */

static Object string_constant_34;  /* "The ~a function could not convert the argument ~A to type ~a." */

/* TYPE-CONVERSION-EVAL-ERROR-MESSAGE */
Object type_conversion_eval_error_message(value,type,evaluator_name)
    Object value, type, evaluator_name;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(208,108);
    gensymed_symbol = value;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(4,temp ? string_constant_33 : 
	    string_constant_34,evaluator_name,value,type);
}

static Object Qquantity;           /* quantity */

/* COERCE-EVALUATION-VALUE-TO-QUANTITY */
Object coerce_evaluation_value_to_quantity(number_truth_value_or_text)
    Object number_truth_value_or_text;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, text_length, end_index, start_index, number_qm, kind;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,109);
    if (CONSP(number_truth_value_or_text) && 
	    EQ(M_CDR(number_truth_value_or_text),Qtruth_value)) {
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
	aref_new_value = (double)IFIX(M_CAR(number_truth_value_or_text)) / 
		1000.0;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (FIXNUMP(number_truth_value_or_text) || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(number_truth_value_or_text) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_truth_value_or_text)) == 
	    (SI_Long)1L || 
	    INLINE_LONG_VECTOR_P(number_truth_value_or_text) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_truth_value_or_text)) == 
	    (SI_Long)1L)
	return make_evaluation_quantity(evaluation_quantity_value(number_truth_value_or_text));
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(number_truth_value_or_text) 
	    != (SI_Long)0L) {
	text_length = text_string_length(number_truth_value_or_text);
	end_index = Nil;
	start_index = Nil;
	if (IFIX(text_length) == (SI_Long)0L)
	    return empty_string_eval_error_message(Qquantity);
	else {
	    end_index = text_length;
	    start_index = 
		    skip_whitespace_in_string(number_truth_value_or_text,
		    FIX((SI_Long)0L),end_index);
	    if (FIXNUM_GE(start_index,end_index))
		return type_conversion_eval_error_message(number_truth_value_or_text,
			Qquantity,Qquantity);
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    result = read_number_from_text_string(3,
			    number_truth_value_or_text,start_index,end_index);
		    MVS_2(result,number_qm,kind);
		    if ( !TRUEP(number_qm) || EQ(number_qm,Qunderflow) || 
			    EQ(number_qm,Qoverflow))
			result = type_conversion_eval_error_message(number_truth_value_or_text,
				Qquantity,Qquantity);
		    else if (EQ(kind,Qfloat)) {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp = Vector_of_simple_float_array_pools;
			    temp_1 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp) = amf_available_array_cons_qm;
				temp = 
					Available_float_array_conses_tail_vector;
				temp_1 = Current_thread_index;
				SVREF(temp,temp_1) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp = Available_float_array_conses_vector;
				temp_1 = Current_thread_index;
				SVREF(temp,temp_1) = 
					amf_available_array_cons_qm;
				temp = 
					Available_float_array_conses_tail_vector;
				temp_1 = Current_thread_index;
				SVREF(temp,temp_1) = 
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
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(number_qm);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			result = VALUES_1(new_float);
		    }
		    else
			result = VALUES_1(number_qm);
		}
		POP_LOCAL_ALLOCATION(0,0);
		return result;
	    }
	}
    }
    else
	return VALUES_1(Qnil);
}

/* EVAL-QUANTITY-TRUTH-VALUE-FUNCALLED */
Object eval_quantity_truth_value_funcalled(truth_value)
    Object truth_value;
{
    Object truth_value_value, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, result_1;
    double aref_new_value;

    x_note_fn_call(208,110);
    truth_value_value = M_CAR(truth_value);
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
    aref_new_value = (double)IFIX(truth_value_value) / 1000.0;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    result_1 = new_float;
    if ( !(EQ(truth_value,Evaluation_true_value) || EQ(truth_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value);
    return VALUES_1(result_1);
}

/* EVAL-QUANTITY-QUANTITY-FUNCALLED */
Object eval_quantity_quantity_funcalled(quantity)
    Object quantity;
{
    x_note_fn_call(208,111);
    return VALUES_1(quantity);
}

static Object Qlong;               /* long */

/* EVAL-QUANTITY-TEXT-FUNCALLED */
Object eval_quantity_text_funcalled(text)
    Object text;
{
    Object text_value, text_length, end_index, start_index, result_1, temp;
    Object number_qm, kind, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float, temp_3;
    char temp_4;
    double aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,112);
    text_value = text;
    PUSH_SPECIAL_WITH_SYMBOL(Text_value,Qtext_value,text_value,0);
      text_length = text_string_length(Text_value);
      end_index = Nil;
      start_index = Nil;
      result_1 = Nil;
      if (IFIX(text_length) == (SI_Long)0L) {
	  temp = Cached_top_of_stack;
	  raw_stack_error_named_error(temp,
		  empty_string_eval_error_message(Qquantity));
      }
      else {
	  end_index = text_length;
	  start_index = skip_whitespace_in_string(Text_value,
		  FIX((SI_Long)0L),end_index);
	  if (FIXNUM_GE(start_index,end_index)) {
	      temp = Cached_top_of_stack;
	      raw_stack_error_named_error(temp,
		      type_conversion_eval_error_message(Text_value,
		      Qquantity,Qquantity));
	  }
	  else {
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		  result = read_number_from_text_string(3,Text_value,
			  start_index,end_index);
		  MVS_2(result,number_qm,kind);
		  if ( !TRUEP(number_qm) || EQ(number_qm,Qunderflow) || 
			  EQ(number_qm,Qoverflow)) {
		      temp = Cached_top_of_stack;
		      raw_stack_error_named_error(temp,
			      type_conversion_eval_error_message(Text_value,
			      Qquantity,Qquantity));
		  }
		  else if (EQ(kind,Qfloat)) {
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
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_2 = Current_thread_index;
			      SVREF(temp_1,temp_2) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_1 = Available_float_array_conses_vector;
			      temp_2 = Current_thread_index;
			      SVREF(temp_1,temp_2) = 
				      amf_available_array_cons_qm;
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_2 = Current_thread_index;
			      SVREF(temp_1,temp_2) = 
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(number_qm);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      result_1 = new_float;
		  }
		  else if (EQ(kind,Qlong))
		      result_1 = make_evaluation_long(number_qm);
		  else
		      result_1 = number_qm;
		  if (EQ(FIX((SI_Long)0L),result_1)) {
		      temp_3 = minus(end_index,start_index);
		      temp = FIX((SI_Long)10L);
		      temp_4 = NUM_LT(temp_3,temp);
		  }
		  else
		      temp_4 = TRUEP(Nil);
		  if (temp_4)
		      result_1 = 
			      read_hex_number_from_text_string(Text_value,
			      start_index,end_index);
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	  }
      }
      reclaim_text_string(text);
      temp = result_1;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant_35;  /* "beginning with \"~a...\"" */

static Object string_constant_36;  /* "\"~a\"" */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_37;  /* "The ~(~a~) function could not convert the text ~a to a symbol." */

static Object string_constant_38;  /* "  ~a" */

/* SYMBOL-CONVERSION-ERROR */
Object symbol_conversion_error varargs_1(int, n)
{
    Object evaluation_text_string, top_of_stack, problem_string_qm;
    Object function_name_qm, length_1, small_text, the_text, top_of_stack_1;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, message_1;
    SI_Long max_length, bv16_length, aref_arg_2, aref_new_value, length_2;
    char truncate_p;
    Declare_varargs_nonrelocating;
    Declare_special(7);

    x_note_fn_call(208,113);
    INIT_ARGS_nonrelocating();
    evaluation_text_string = REQUIRED_ARG_nonrelocating();
    top_of_stack = REQUIRED_ARG_nonrelocating();
    problem_string_qm = REQUIRED_ARG_nonrelocating();
    function_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length_1 = text_string_length(evaluation_text_string);
    max_length = (SI_Long)200L;
    truncate_p = IFIX(length_1) > max_length;
    small_text = truncate_p ? text_string_substring(evaluation_text_string,
	    FIX((SI_Long)0L),FIX(max_length)) : evaluation_text_string;
    the_text = tformat_text_string(2,truncate_p ? string_constant_35 : 
	    string_constant_36,small_text);
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
		  temp = function_name_qm;
		  if (temp);
		  else
		      temp = Qsymbol;
		  tformat(3,string_constant_37,temp,the_text);
		  if (problem_string_qm)
		      tformat(2,string_constant_38,problem_string_qm);
		  if (truncate_p)
		      reclaim_text_string(small_text);
		  reclaim_text_string(the_text);
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
    return raw_stack_error_named_error(top_of_stack_1,message_1);
}

static Object Knil;                /* :nil */

static Object string_constant_39;  /* "~A::~A" */

/* CREATE-SYMBOL-FROM-TEXT-STRING */
Object create_symbol_from_text_string(evaluation_text_string,top_of_stack)
    Object evaluation_text_string, top_of_stack;
{
    Object temp_1, temp_2, attribute_name_qm, class_qualifier_qm;
    Object class_qualified_symbol_text_string, problem_string_qm;
    SI_Long start, end_1, index_1, char_1, arg, arg_1, arg_2;
    char temp;
    Object result;

    x_note_fn_call(208,114);
    start = (SI_Long)0L;
    end_1 = IFIX(lengthw(evaluation_text_string));
    index_1 = (SI_Long)0L;
    char_1 = (SI_Long)0L;
    if (end_1 <= (SI_Long)200L) {
      next_loop:
	if (index_1 >= end_1)
	    goto end_loop;
	char_1 = UBYTE_16_ISAREF_1(evaluation_text_string,index_1);
	arg = (SI_Long)97L;
	arg_1 = char_1;
	arg_2 = (SI_Long)122L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	if (temp);
	else {
	    arg = (SI_Long)65L;
	    arg_1 = char_1;
	    arg_2 = (SI_Long)90L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	if (temp);
	else
	    temp = char_1 == (SI_Long)95L;
	if (temp);
	else
	    temp = char_1 == (SI_Long)39L;
	if (temp ? TRUEP(T) : TRUEP(Nil)) {
	    start = index_1;
	    temp = TRUEP(T);
	    goto end_2;
	}
	if ( !(char_1 == (SI_Long)32L || char_1 == (SI_Long)9L)) {
	    temp = TRUEP(Nil);
	    goto end_2;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_2:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
      next_loop_1:
	if (index_1 >= end_1)
	    goto end_loop_1;
	char_1 = UBYTE_16_ISAREF_1(evaluation_text_string,index_1);
	arg = (SI_Long)97L;
	arg_1 = char_1;
	arg_2 = (SI_Long)122L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	if (temp);
	else {
	    arg = (SI_Long)65L;
	    arg_1 = char_1;
	    arg_2 = (SI_Long)90L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	if (temp);
	else {
	    arg = (SI_Long)48L;
	    arg_1 = char_1;
	    arg_2 = (SI_Long)57L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	if (temp);
	else
	    temp = char_1 == (SI_Long)39L;
	if (temp);
	else
	    temp = char_1 == (SI_Long)95L;
	if (temp);
	else
	    temp = char_1 == (SI_Long)45L;
	if (temp);
	else
	    temp = char_1 == (SI_Long)46L;
	if (temp ? TRUEP(T) : TRUEP(Nil))
	    index_1 = index_1 + (SI_Long)1L;
	else {
	    arg = (SI_Long)32L;
	    arg_1 = char_1;
	    arg_2 = (SI_Long)126L;
	    temp = (arg <= arg_1 && arg_1 <= arg_2 ?  !(char_1 == 
		    (SI_Long)64L) : TRUEP(Nil)) ?  !(char_1 == 
		    (SI_Long)58L) : TRUEP(Nil);
	    if (temp);
	    else
		temp = char_1 == (SI_Long)9L;
	    if (temp);
	    else
		temp = TRUEP(newline_p(FIX(char_1)));
	    if (temp)
		goto end_loop_1;
	    else {
		temp = TRUEP(Nil);
		goto end_3;
	    }
	}
	goto next_loop_1;
      end_loop_1:
	end_1 = index_1;
	temp = TRUEP(T);
	goto end_3;
	temp = TRUEP(Qnil);
      end_3:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = 
		intern_and_upcase_simple_symbol_portion_of_wide_string(evaluation_text_string,
		FIX(start),FIX(end_1),Nil);
	if (temp_1);
	else
	    temp_1 = Knil;
	reclaim_wide_string(evaluation_text_string);
    }
    else
	temp_1 = Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	result = read_attribute_name_from_text_string_1(evaluation_text_string,
		Nil,Nil);
	MVS_3(result,attribute_name_qm,temp_1,class_qualifier_qm);
	if (class_qualifier_qm) {
	    class_qualified_symbol_text_string = tformat_text_string(3,
		    string_constant_39,class_qualifier_qm,attribute_name_qm);
	    problem_string_qm = 
		    non_valid_symbol_text_string_p(class_qualified_symbol_text_string);
	    if (problem_string_qm) {
		reclaim_text_string(class_qualified_symbol_text_string);
		return symbol_conversion_error(3,evaluation_text_string,
			top_of_stack,problem_string_qm);
	    }
	    else {
		reclaim_text_string(evaluation_text_string);
		return intern_text_string(2,
			class_qualified_symbol_text_string,Keyword_package_1);
	    }
	}
	else if (attribute_name_qm) {
	    problem_string_qm = 
		    non_valid_symbol_text_string_p(symbol_name_text_string(attribute_name_qm));
	    if (problem_string_qm)
		return symbol_conversion_error(3,evaluation_text_string,
			top_of_stack,problem_string_qm);
	    else {
		reclaim_text_string(evaluation_text_string);
		return VALUES_1(attribute_name_qm);
	    }
	}
	else
	    return symbol_conversion_error(3,evaluation_text_string,
		    top_of_stack,Nil);
    }
}

/* EVAL-SYMBOL-DATUM-FUNCALLED */
Object eval_symbol_datum_funcalled(symbol_or_text)
    Object symbol_or_text;
{
    Object temp;

    x_note_fn_call(208,115);
    temp = symbol_or_text && SYMBOLP(symbol_or_text) ? symbol_or_text : 
	    eval_symbol_text_funcalled(symbol_or_text);
    return VALUES_1(temp);
}

/* EVAL-SYMBOL-TEXT-FUNCALLED */
Object eval_symbol_text_funcalled(text)
    Object text;
{
    Object temp;

    x_note_fn_call(208,116);
    temp = create_symbol_from_text_string(text,Cached_top_of_stack);
    return VALUES_1(temp);
}

static Object Qtext_to_symbol;     /* text-to-symbol */

static Object Qgensym_string;      /* gensym-string */

static Object Qnumeric;            /* numeric */

static Object Qtype_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

/* EVAL-TEXT-TO-SYMBOL-FUNCALLED */
Object eval_text_to_symbol_funcalled(text)
    Object text;
{
    Object problem_string_qm, temp, number_parsing_state, possibly_numeric_p;
    Object wide_string, index_1, next_char, using_string_buffer_p;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object char_1, code, temp_2, temp_3, wide_character_code, code_1;
    Object extended_code, unicode, row, gensym_character_code_qm;
    Object gensym_character_code, extended_code_qm, char_2;
    Object simple_gensym_character_code, character_or_character_code;
    Object escape_character_qm, thing, schar_new_value, kanji_code, octet_1_qm;
    Object quotient, remainder_1, simple_or_wide_character, gensymed_symbol_2;
    Object symbol;
    SI_Long length_1, i, ab_loop_bind_, gensym_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(208,117);
    problem_string_qm = non_valid_symbol_text_string_p(text);
    if (problem_string_qm &&  !EQ(problem_string_qm,
	    Message_illegal_symbol_text_string_empty))
	temp = symbol_conversion_error(4,text,Cached_top_of_stack,
		problem_string_qm,Qtext_to_symbol);
    else {
	number_parsing_state = Nil;
	possibly_numeric_p = T;
	wide_string = text;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	length_1 = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L);
	index_1 = FIX((SI_Long)0L);
	next_char = Nil;
	using_string_buffer_p = T;
	current_gensym_string = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		4);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  3);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    2);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      1);
		i = (SI_Long)0L;
		ab_loop_bind_ = length_1;
		char_1 = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		char_1 = FIX(UBYTE_16_ISAREF_1(wide_string,i));
		next_char = char_1;
		if (using_string_buffer_p && FIXNUM_LT(index_1,
			Intern_string_buffer_length)) {
		    code = next_char;
		    temp_1 = IFIX(code) < (SI_Long)127L ?  !((SI_Long)64L 
			    == IFIX(code) || (SI_Long)126L == IFIX(code) 
			    || (SI_Long)92L == IFIX(code)) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp_2 = Intern_string_buffer;
		    temp_3 = CODE_CHAR(next_char);
		    SET_CHAR(temp_2,index_1,temp_3);
		}
		else {
		    if (using_string_buffer_p) {
			using_string_buffer_p = Nil;
			Current_gensym_string = 
				obtain_simple_gensym_string(FIX((SI_Long)2048L));
			twrite_intern_string_buffer_as_gensym_characters(index_1);
		    }
		    wide_character_code = next_char;
		    code_1 = Nil;
		    extended_code = Nil;
		    unicode = wide_character_code;
		    extended_code = Nil;
		    code = unicode;
		    if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == 
			    IFIX(code) || (SI_Long)126L == IFIX(code) || 
			    (SI_Long)92L == IFIX(code))) {
			code_1 = unicode;
			temp = code_1;
		    }
		    else {
			row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
			PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			  gensym_full_row = 
				  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				  IFIX(Row));
			  if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			      gensymed_symbol = gensym_full_row << (SI_Long)8L;
			      gensymed_symbol_1 = (SI_Long)255L & 
				      IFIX(unicode);
			      gensym_character_code_qm = 
				      FIX(gensymed_symbol + gensymed_symbol_1);
			  }
			  else
			      gensym_character_code_qm = Nil;
			POP_SPECIAL();
			if (gensym_character_code_qm) {
			    temp_1 = IFIX(gensym_character_code_qm) < 
				    (SI_Long)256L ? 
				    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(gensym_character_code_qm))) : 
				    TRUEP(Nil);
			    if (temp_1);
			    else if (FIXNUM_EQ(gensym_character_code_qm,
				    Gensym_code_for_capital_ligature_oe))
				temp_1 = 'W';
			    else if (FIXNUM_EQ(gensym_character_code_qm,
				    Gensym_code_for_small_ligature_oe))
				temp_1 = 'w';
			    else if (FIXNUM_EQ(gensym_character_code_qm,
				    Gensym_code_for_bullet))
				temp_1 = '*';
			    else if (FIXNUM_EQ(gensym_character_code_qm,
				    Gensym_code_for_small_letter_f_with_hook))
				temp_1 = '&';
			    else if (FIXNUM_EQ(gensym_character_code_qm,
				    Gensym_code_for_trade_mark_sign))
				temp_1 = ':';
			    else
				temp_1 = TRUEP(Qnil);
			    if (temp_1);
			    else
				temp_1 = (SI_Long)8192L <= 
					IFIX(gensym_character_code_qm) ? 
					IFIX(gensym_character_code_qm) <= 
					(SI_Long)8447L : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    code_1 = gensym_character_code_qm;
			    temp = code_1;
			}
			else
			    temp = Nil;
			if (temp);
			else {
			    code_1 = 
				    map_unicode_to_gensym_han_character_code(unicode);
			    temp = code_1;
			    if (temp);
			    else {
				row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
				PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				  gensym_full_row = 
					  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
					  IFIX(Row));
				  if ( !(gensym_full_row == 
					  IFIX(Invalid_gensym_full_row))) {
				      gensymed_symbol = gensym_full_row << 
					      (SI_Long)8L;
				      gensymed_symbol_1 = (SI_Long)255L & 
					      IFIX(unicode);
				      code_1 = FIX(gensymed_symbol + 
					      gensymed_symbol_1);
				  }
				  else
				      code_1 = Nil;
				POP_SPECIAL();
				temp = code_1;
				if (temp);
				else {
				    gensymed_symbol = (SI_Long)63488L;
				    gensymed_symbol_1 = (SI_Long)255L & 
					    IFIX(unicode);
				    extended_code = FIX(gensymed_symbol + 
					    gensymed_symbol_1);
				    code_1 = FIX((SI_Long)63232L + 
					    (IFIX(unicode) >>  -  - 
					    (SI_Long)8L));
				    temp = code_1;
				}
			    }
			}
		    }
		    result = VALUES_2(temp,extended_code);
		    MVS_2(result,gensym_character_code,extended_code_qm);
		    char_2 = Nil;
		    if (FIXNUM_EQ(gensym_character_code,
			    Gensym_code_for_linebreak))
			result = VALUES_2(Gensym_char_or_code_for_linebreak,
				Gensym_esc_for_linebreak_qm);
		    else if (FIXNUM_EQ(gensym_character_code,
			    Gensym_code_for_paragraph_break))
			result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				Gensym_esc_for_paragraph_break_qm);
		    else {
			if ((SI_Long)32L <= IFIX(gensym_character_code) && 
				IFIX(gensym_character_code) <= (SI_Long)126L) {
			    simple_gensym_character_code = 
				    gensym_character_code;
			    temp_1 =  
				    !(FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)64L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)126L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)92L)));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = CODE_CHAR(gensym_character_code);
			    result = VALUES_2(temp,Nil);
			}
			else {
			    temp = IFIX(gensym_character_code) < 
				    (SI_Long)256L ? 
				    ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(gensym_character_code)) : Nil;
			    if (temp);
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_capital_ligature_oe))
				temp = CHR('W');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_small_ligature_oe))
				temp = CHR('w');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_bullet))
				temp = CHR('*');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_small_letter_f_with_hook))
				temp = CHR('&');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_trade_mark_sign))
				temp = CHR(':');
			    else
				temp = Qnil;
			    char_2 = temp;
			    if (char_2)
				result = VALUES_2(char_2,CHR('~'));
			    else
				result = VALUES_2(gensym_character_code,
					CHR('\\'));
			}
		    }
		    MVS_2(result,character_or_character_code,
			    escape_character_qm);
		    if ( !TRUEP(escape_character_qm)) {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = (SI_Long)92L;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			code = kanji_code;
			result = chestnut_floorf_function(FIX(IFIX(code) & 
				(SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
				(SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = simple_or_wide_character;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = escape_character_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    if (extended_code_qm) {
			char_2 = Nil;
			if (FIXNUM_EQ(extended_code_qm,
				Gensym_code_for_linebreak))
			    result = VALUES_2(Gensym_char_or_code_for_linebreak,
				    Gensym_esc_for_linebreak_qm);
			else if (FIXNUM_EQ(extended_code_qm,
				Gensym_code_for_paragraph_break))
			    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				    Gensym_esc_for_paragraph_break_qm);
			else {
			    if ((SI_Long)32L <= IFIX(extended_code_qm) && 
				    IFIX(extended_code_qm) <= (SI_Long)126L) {
				simple_gensym_character_code = 
					extended_code_qm;
				temp_1 =  
					!(FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)64L)) || 
					FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)126L)) || 
					FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)92L)));
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1) {
				temp = CODE_CHAR(extended_code_qm);
				result = VALUES_2(temp,Nil);
			    }
			    else {
				temp = IFIX(extended_code_qm) < 
					(SI_Long)256L ? 
					ISVREF(Iso_latin1_special_character_code_map,
					IFIX(extended_code_qm)) : Nil;
				if (temp);
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_capital_ligature_oe))
				    temp = CHR('W');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_small_ligature_oe))
				    temp = CHR('w');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_bullet))
				    temp = CHR('*');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_small_letter_f_with_hook))
				    temp = CHR('&');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_trade_mark_sign))
				    temp = CHR(':');
				else
				    temp = Qnil;
				char_2 = temp;
				if (char_2)
				    result = VALUES_2(char_2,CHR('~'));
				else
				    result = VALUES_2(extended_code_qm,
					    CHR('\\'));
			    }
			}
			MVS_2(result,character_or_character_code,
				escape_character_qm);
			if ( !TRUEP(escape_character_qm)) {
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = character_or_character_code;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = character_or_character_code;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			    kanji_code = character_or_character_code;
			    octet_1_qm = Nil;
			    octet_2 = (SI_Long)0L;
			    octet_3 = (SI_Long)0L;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = (SI_Long)92L;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = (SI_Long)92L;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    code = kanji_code;
			    result = chestnut_floorf_function(FIX(IFIX(code) 
				    & (SI_Long)8191L),FIX((SI_Long)95L));
			    MVS_2(result,quotient,remainder_1);
			    octet_2 = IFIX(quotient) + (SI_Long)40L;
			    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			    octet_1_qm =  !(IFIX(code) >>  -  - 
				    (SI_Long)13L == (SI_Long)1L) ? 
				    FIX((IFIX(code) >>  -  - (SI_Long)13L) 
				    + (SI_Long)32L) : Nil;
			    if (octet_1_qm) {
				simple_or_wide_character = octet_1_qm;
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = simple_or_wide_character;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    temp_3 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = simple_or_wide_character;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,temp_3,schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
			    }
			    simple_or_wide_character_1 = octet_2;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = simple_or_wide_character_1;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = simple_or_wide_character_1;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    simple_or_wide_character_1 = octet_3;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = simple_or_wide_character_1;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = simple_or_wide_character_1;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			else {
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = escape_character_qm;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = escape_character_qm;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = character_or_character_code;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = character_or_character_code;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
		    }
		}
		index_1 = FIXNUM_ADD1(index_1);
		if (possibly_numeric_p) {
		    gensymed_symbol = IFIX(char_1);
		    if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol 
			    <= (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
			    (SI_Long)48L)) : TRUEP(Nil)) {
			if ( !TRUEP(number_parsing_state) || 
				IFIX(number_parsing_state) <= (SI_Long)2L)
			    number_parsing_state = FIX((SI_Long)2L);
			else if (IFIX(number_parsing_state) <= (SI_Long)4L)
			    number_parsing_state = FIX((SI_Long)4L);
			else
			    number_parsing_state = FIX((SI_Long)7L);
		    }
		    else if (EQ(number_parsing_state,Qnil)) {
			if (EQ(char_1,FIX((SI_Long)45L)))
			    number_parsing_state = FIX((SI_Long)1L);
			else if (EQ(char_1,FIX((SI_Long)46L)))
			    number_parsing_state = FIX((SI_Long)3L);
			else
			    number_parsing_state = Qnil;
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)1L)))
			number_parsing_state = EQ(char_1,
				FIX((SI_Long)46L)) ? FIX((SI_Long)3L) : Nil;
		    else if (EQ(number_parsing_state,FIX((SI_Long)2L))) {
			if (EQ(char_1,FIX((SI_Long)46L)))
			    number_parsing_state = FIX((SI_Long)4L);
			else if ( !TRUEP(Nil) && (IFIX(char_1) == 
				(SI_Long)101L || IFIX(char_1) == (SI_Long)69L))
			    number_parsing_state = FIX((SI_Long)5L);
			else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
				FIX((SI_Long)39L)) || EQ(char_1,
				FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_1;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qinteger;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)4L))) {
			if ( !TRUEP(Nil) && (IFIX(char_1) == (SI_Long)101L 
				|| IFIX(char_1) == (SI_Long)69L))
			    number_parsing_state = FIX((SI_Long)5L);
			else if (EQ(char_1,FIX((SI_Long)46L)))
			    number_parsing_state = Nil;
			else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
				FIX((SI_Long)39L)) || EQ(char_1,
				FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_1;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qfloat;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)5L)))
			number_parsing_state = EQ(char_1,
				FIX((SI_Long)43L)) || EQ(char_1,
				FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
		    else if (EQ(number_parsing_state,FIX((SI_Long)7L))) {
			if (EQ(char_1,FIX((SI_Long)46L)))
			    number_parsing_state = Nil;
			else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
				FIX((SI_Long)39L)) || EQ(char_1,
				FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_1;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qfloat;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else
			number_parsing_state = Qnil;
		    possibly_numeric_p = FIXNUMP(number_parsing_state) ? T 
			    : Nil;
		}
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
		symbol = using_string_buffer_p ? 
			intern_using_string_buffer(Intern_string_buffer,
			index_1,Nil) : intern_gensym_string(2,
			copy_out_current_gensym_string(),Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (symbol);
	else
	    symbol = Knil;
	if (possibly_numeric_p) {
	    if (possibly_numeric_p) {
		gensymed_symbol = (SI_Long)32L;
		if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
			(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
			(SI_Long)48L)) : TRUEP(Nil)) {
		    if ( !TRUEP(number_parsing_state) || 
			    IFIX(number_parsing_state) <= (SI_Long)2L)
			number_parsing_state = FIX((SI_Long)2L);
		    else if (IFIX(number_parsing_state) <= (SI_Long)4L)
			number_parsing_state = FIX((SI_Long)4L);
		    else
			number_parsing_state = FIX((SI_Long)7L);
		}
		else if (EQ(number_parsing_state,Qnil)) {
		    if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)))
			number_parsing_state = FIX((SI_Long)1L);
		    else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
			number_parsing_state = FIX((SI_Long)3L);
		    else
			number_parsing_state = Qnil;
		}
		else if (EQ(number_parsing_state,FIX((SI_Long)1L)))
		    number_parsing_state = EQ(FIX((SI_Long)32L),
			    FIX((SI_Long)46L)) ? FIX((SI_Long)3L) : Nil;
		else if (EQ(number_parsing_state,FIX((SI_Long)2L))) {
		    if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
			number_parsing_state = FIX((SI_Long)4L);
		    else if ( !TRUEP(Nil) && ((SI_Long)32L == 
			    (SI_Long)101L || (SI_Long)32L == (SI_Long)69L))
			number_parsing_state = FIX((SI_Long)5L);
		    else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
			number_parsing_state = Nil;
		    else {
			gensymed_symbol = (SI_Long)32L;
			if ( !((SI_Long)97L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)122L || 
				(SI_Long)65L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)90L))
			    number_parsing_state = Qinteger;
			else
			    number_parsing_state = Qnil;
		    }
		}
		else if (EQ(number_parsing_state,FIX((SI_Long)4L))) {
		    if ( !TRUEP(Nil) && ((SI_Long)32L == (SI_Long)101L || 
			    (SI_Long)32L == (SI_Long)69L))
			number_parsing_state = FIX((SI_Long)5L);
		    else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
			number_parsing_state = Nil;
		    else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
			number_parsing_state = Nil;
		    else {
			gensymed_symbol = (SI_Long)32L;
			if ( !((SI_Long)97L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)122L || 
				(SI_Long)65L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)90L))
			    number_parsing_state = Qfloat;
			else
			    number_parsing_state = Qnil;
		    }
		}
		else if (EQ(number_parsing_state,FIX((SI_Long)5L)))
		    number_parsing_state = EQ(FIX((SI_Long)32L),
			    FIX((SI_Long)43L)) || EQ(FIX((SI_Long)32L),
			    FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
		else if (EQ(number_parsing_state,FIX((SI_Long)7L))) {
		    if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
			number_parsing_state = Nil;
		    else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			    EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
			number_parsing_state = Nil;
		    else {
			gensymed_symbol = (SI_Long)32L;
			if ( !((SI_Long)97L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)122L || 
				(SI_Long)65L <= gensymed_symbol && 
				gensymed_symbol <= (SI_Long)90L))
			    number_parsing_state = Qfloat;
			else
			    number_parsing_state = Qnil;
		    }
		}
		else
		    number_parsing_state = Qnil;
		possibly_numeric_p = FIXNUMP(number_parsing_state) ? T : Nil;
	    }
	    if (EQ(number_parsing_state,Qinteger))
		temp_1 = TRUEP(Qinteger);
	    else if (EQ(number_parsing_state,Qfloat))
		temp_1 = TRUEP(Qfloat);
	    else
		temp_1 = TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    mutate_global_property(symbol,Qnumeric,Qtype_of_syntactic_anomaly);
	reclaim_wide_string(wide_string);
	temp = symbol;
    }
    return VALUES_1(temp);
}

static Object string_constant_40;  /* "The ~a function received an invalid ~a argument ~NV." */

static Object string_constant_41;  /* "The ~a function received an invalid ~a argument ~A." */

/* INVALID-ARGUMENT-EVAL-ERROR-MESSAGE */
Object invalid_argument_eval_error_message(value,argument_name,evaluator_name)
    Object value, argument_name, evaluator_name;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(208,118);
    gensymed_symbol = value;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(4,temp ? string_constant_40 : 
	    string_constant_41,evaluator_name,argument_name,value);
}

static Object Qyear;               /* year */

/* EVAL-YEAR-FUNCALLED */
Object eval_year_funcalled(time_1)
    Object time_1;
{
    Object year, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,119);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	year = NTH_VALUE((SI_Long)5L, result);
	temp = year;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    year = NTH_VALUE((SI_Long)5L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = year;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,Qyear));
    }
    return VALUES_1(temp);
}

static Object Qmonth;              /* month */

/* EVAL-MONTH-FUNCALLED */
Object eval_month_funcalled(time_1)
    Object time_1;
{
    Object month, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,120);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	month = NTH_VALUE((SI_Long)4L, result);
	temp = month;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    month = NTH_VALUE((SI_Long)4L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = month;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,Qmonth));
    }
    return VALUES_1(temp);
}

static Object Qday_of_the_month;   /* day-of-the-month */

/* EVAL-DAY-OF-THE-MONTH-FUNCALLED */
Object eval_day_of_the_month_funcalled(time_1)
    Object time_1;
{
    Object date, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,121);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	date = NTH_VALUE((SI_Long)3L, result);
	temp = date;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    date = NTH_VALUE((SI_Long)3L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = date;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,
		Qday_of_the_month));
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Day_of_the_week_names, Qday_of_the_week_names);

static Object Qday_of_the_week;    /* day-of-the-week */

/* EVAL-DAY-OF-THE-WEEK-FUNCALLED */
Object eval_day_of_the_week_funcalled(time_1)
    Object time_1;
{
    Object day_of_the_week, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,122);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	day_of_the_week = NTH_VALUE((SI_Long)6L, result);
	temp = nth(day_of_the_week,Day_of_the_week_names);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    day_of_the_week = NTH_VALUE((SI_Long)6L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = nth(day_of_the_week,Day_of_the_week_names);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,
		Qday_of_the_week));
    }
    return VALUES_1(temp);
}

static Object Qhour;               /* hour */

/* EVAL-HOUR-FUNCALLED */
Object eval_hour_funcalled(time_1)
    Object time_1;
{
    Object hour, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,123);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	hour = NTH_VALUE((SI_Long)2L, result);
	temp = hour;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    hour = NTH_VALUE((SI_Long)2L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = hour;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,Qhour));
    }
    return VALUES_1(temp);
}

static Object Qminute;             /* minute */

/* EVAL-MINUTE-FUNCALLED */
Object eval_minute_funcalled(time_1)
    Object time_1;
{
    Object minute, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(208,124);
    if (FIXNUMP(time_1)) {
	result = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	minute = NTH_VALUE((SI_Long)1L, result);
	temp = minute;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    minute = NTH_VALUE((SI_Long)1L, result);
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = minute;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,Qminute));
    }
    return VALUES_1(temp);
}

/* EVAL-SECOND-FUNCALLED */
Object eval_second_funcalled(time_1)
    Object time_1;
{
    Object second_1, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(208,125);
    if (FIXNUMP(time_1)) {
	second_1 = decode_gensym_time(FIXNUM_ADD(time_1,Gensym_time_at_start));
	temp = second_1;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    second_1 = 
		    gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_1,
		    (SI_Long)0L) + DFLOAT_ISAREF_1(G2_time_at_start,
		    (SI_Long)0L)));
	    reclaim_managed_simple_float_array_of_length_1(time_1);
	    temp = second_1;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	temp = Cached_top_of_stack;
	temp = raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(time_1,Qtime,Qsecond));
    }
    return VALUES_1(temp);
}

/* EVAL-TIME-FUNCALLED */
Object eval_time_funcalled(year,month,date,hour,minute,second_1)
    Object year, month, date, hour, minute, second_1;
{
    Object year_value, month_value, date_value, hour_value, minute_value;
    Object second_value, temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    double float_encoded_time, arg_2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(208,126);
    year_value = year;
    month_value = month;
    date_value = date;
    hour_value = hour;
    minute_value = minute;
    second_value = second_1;
    if ( !(IFIX(year_value) >= (SI_Long)1900L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(year_value,Qyear,Qtime));
    }
    if ( !((SI_Long)1L <= IFIX(month_value) && IFIX(month_value) <= 
	    (SI_Long)12L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(month_value,Qmonth,Qtime));
    }
    temp = month_value;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	temp = (SI_Long)1L <= IFIX(date_value) ? (IFIX(date_value) <= 
		(SI_Long)31L ? T : Nil) : Qnil;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 2:
	    temp = leap_year_p(year_value) ? ((SI_Long)1L <= 
		    IFIX(date_value) ? (IFIX(date_value) <= (SI_Long)29L ? 
		    T : Nil) : Qnil) : (SI_Long)1L <= IFIX(date_value) ? 
		    (IFIX(date_value) <= (SI_Long)28L ? T : Nil) : Qnil;
	    break;
	  case 4:
	  case 6:
	  case 9:
	  case 11:
	    temp = (SI_Long)1L <= IFIX(date_value) ? (IFIX(date_value) <= 
		    (SI_Long)30L ? T : Nil) : Qnil;
	    break;
	  default:
	    temp = (SI_Long)1L <= IFIX(date_value) ? (IFIX(date_value) <= 
		    (SI_Long)31L ? T : Nil) : Qnil;
	    break;
	}
    if ( !TRUEP(temp)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(date_value,
		Qday_of_the_month,Qtime));
    }
    if ( !((SI_Long)0L <= IFIX(hour_value) && IFIX(hour_value) <= 
	    (SI_Long)24L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(hour_value,Qhour,Qtime));
    }
    if ( !((SI_Long)0L <= IFIX(minute_value) && IFIX(minute_value) <= 
	    (SI_Long)59L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(minute_value,Qminute,
		Qtime));
    }
    if ( !((SI_Long)0L <= IFIX(second_value) && IFIX(second_value) <= 
	    (SI_Long)59L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(second_value,Qsecond,
		Qtime));
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	unix_time = g2ext_get_encoded_unix_time(IFIX(second_value),
		IFIX(minute_value),IFIX(hour_value),IFIX(date_value),
		IFIX(month_value),IFIX(year_value));
	arg = unix_time;
	arg_1 = -1.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = encode_unix_time_after_failure(second_value,
		    minute_value,hour_value,date_value,month_value,year_value);
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    gensymed_symbol = unix_time;
	gensymed_symbol_1 = (double)((SI_Long)60L * 
		IFIX(Global_daylight_saving_time_adjustment));
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	float_encoded_time = gensymed_symbol - gensymed_symbol_1;
	arg = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	arg_1 = float_encoded_time;
	arg_2 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	if (arg <= arg_1 && arg_1 <= arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2))
	    temp = LONG_TO_FIXNUM(inline_floor_1(float_encoded_time));
	else {
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,float_encoded_time);
	    temp = new_float;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* EVAL-IS-RELATED-FUNCALLED */
Object eval_is_related_funcalled(given_relation_name,item1,item2)
    Object given_relation_name, item1, item2;
{
    Object given_name, relation_instances, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash;
    Object relation_instance_form, the_block, blocks, result_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(208,127);
    given_name = given_relation_name;
    relation_instances = ISVREF(item2,(SI_Long)12L);
    if (relation_instances) {
	skip_list = CDR(relation_instances);
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
	relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (relation_instance_form) {
	    the_block = item1;
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    result_1 = temp_2 ? Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

/* EVAL-IS-NOT-RELATED-FUNCALLED */
Object eval_is_not_related_funcalled(given_relation_name,item1,item2)
    Object given_relation_name, item1, item2;
{
    Object given_name, relation_instances, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash;
    Object relation_instance_form, the_block, blocks, result_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(208,128);
    given_name = given_relation_name;
    relation_instances = ISVREF(item2,(SI_Long)12L);
    if (relation_instances) {
	skip_list = CDR(relation_instances);
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
	relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (relation_instance_form) {
	    the_block = item1;
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    result_1 = temp_2 ? Evaluation_false_value : Evaluation_true_value;
    return VALUES_1(result_1);
}

static Object Qpush_from_surrounding_local_var;  /* push-from-surrounding-local-var */

/* VAR-SPOT-STACK-NODE-CONVERTER */
Object var_spot_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol;

    x_note_fn_call(208,129);
    gensymed_symbol = 
	    make_stack_node_instruction_1_1(Qpush_from_surrounding_local_var,
	    expression);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

/* EVAL-FALSE-FUNCALLED */
Object eval_false_funcalled(truth_value)
    Object truth_value;
{
    Object result_value, temp;

    x_note_fn_call(208,130);
    result_value = FIXNUM_NEGATE(M_CAR(truth_value));
    if ( !(EQ(truth_value,Evaluation_true_value) || EQ(truth_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(truth_value);
    if (FIXNUM_EQ(result_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(result_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(result_value,Qtruth_value);
    return VALUES_1(temp);
}

/* IDENTITY-STACK-NODE-CONVERTER */
Object identity_stack_node_converter(expression)
    Object expression;
{
    x_note_fn_call(208,131);
    GENSYM_RETURN_ONE(convert_expression_to_stack_node_tree(SECOND(expression)));
    return VALUES_1(Nil);
}

static Object Qattribute_value;    /* attribute-value */

/* ATTRIBUTE-VALUE-STACK-NODE-CONVERTER */
Object attribute_value_stack_node_converter(expression)
    Object expression;
{
    Object temp, arguments, gensymed_symbol, attribute_value_node;

    x_note_fn_call(208,132);
    temp = convert_expression_to_stack_node_tree(SECOND(expression));
    arguments = stack_list_2(temp,
	    convert_expression_to_stack_node_tree(THIRD(expression)));
    gensymed_symbol = make_stack_node_instruction_1_1(Qattribute_value,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    attribute_value_node = gensymed_symbol;
    SVREF(attribute_value_node,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(attribute_value_node);
    return VALUES_1(Nil);
}

static Object list_constant_13;    /* # */

/* ATTRIBUTE-VALUE-I-CHOOSER */
Object attribute_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object argument_nodes, temp;

    x_note_fn_call(208,133);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    temp = choose_stack_node_instructions_and_types(2,
	    FIRST(argument_nodes),list_constant_13);
    M_FIRST(argument_nodes) = temp;
    temp = choose_stack_node_instructions_and_types(2,
	    SECOND(argument_nodes),Qsymbol);
    M_SECOND(argument_nodes) = temp;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = list_constant_3;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

/* ATTRIBUTE-VALUE-I-EMIT */
Object attribute_value_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes;

    x_note_fn_call(208,134);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,FIRST(argument_nodes));
    emit_stack_node_tree(byte_code_stream,SECOND(argument_nodes));
    emit_evaluate_role_byte_codes(byte_code_stream,list_constant_14,
	    FIX((SI_Long)2L),type_specification_subtype_p(list_constant_1,
	    ISVREF(stack_node_instruction,(SI_Long)6L)),Nil,Nil,Nil);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcall_procedure;     /* call-procedure */

/* CALL-PROCEDURE-STACK-NODE-CONVERTER */
Object call_procedure_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, procedure_definition_designation;
    Object argument_expressions, node, argument, ab_loop_list_, arg_nodes;
    Object ab_loopvar_, ab_loopvar__1, temp, svref_new_value;

    x_note_fn_call(208,135);
    gensymed_symbol = expression;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_definition_designation = CAR(gensymed_symbol);
    argument_expressions = CDR(gensymed_symbol);
    gensymed_symbol = make_stack_node_instruction_1_1(Qcall_procedure,
	    phrase_list_2(Nil,SYMBOLP(procedure_definition_designation) ? 
	    procedure_definition_designation : Nil));
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    node = gensymed_symbol;
    argument = Nil;
    ab_loop_list_ = CAR(argument_expressions) ? CAR(argument_expressions) :
	     Qnil;
    arg_nodes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(argument),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	arg_nodes = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = 
	    convert_designation_to_stack_node_tree(procedure_definition_designation);
    svref_new_value = stack_cons_1(temp,arg_nodes);
    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
    temp = node;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qcall;               /* call */

static Object Qcall_function;      /* call-function */

static Object string_constant_42;  /* "The first argument to call-function ~
				    * ???     must be an item of class ~
				    *                              function-definition, tabular-function, ~
				    *                              or foreign-function-declaration, ~
				    *                              but the expression `~NE' could not ~
				    *                              refer to such an item."
				    */

/* CALL-FUNCTION-STACK-NODE-CONVERTER */
Object call_function_stack_node_converter(expression)
    Object expression;
{
    Object gensymed_symbol, function_definition_designation;
    Object argument_expressions, arg, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, node, argument, arg_nodes, temp;
    Object svref_new_value;

    x_note_fn_call(208,136);
    gensymed_symbol = expression;
    gensymed_symbol = CDR(gensymed_symbol);
    function_definition_designation = CAR(gensymed_symbol);
    argument_expressions = CDR(gensymed_symbol);
    if (Nil) {
	gensymed_symbol = make_stack_node_instruction_1_1(Qcall,
		compile_stack_expression_into_nodes(function_definition_designation,
		Qitem_or_datum));
	arg = Nil;
	ab_loop_list_ = argument_expressions;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = stack_cons_1(compile_stack_expression(arg,
		Qitem_or_datum),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	goto end_1;
	ab_loopvar_ = Qnil;
      end_1:;
	SVREF(gensymed_symbol,FIX((SI_Long)13L)) = ab_loopvar_;
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	node = gensymed_symbol;
	argument = Nil;
	ab_loop_list_ = argument_expressions;
	arg_nodes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = 
		stack_cons_1(convert_expression_to_stack_node_tree(argument),
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    arg_nodes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	temp = 
		convert_designation_to_stack_node_tree(function_definition_designation);
	svref_new_value = stack_cons_1(temp,arg_nodes);
	SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	temp = node;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else {
	gensymed_symbol = make_stack_node_instruction_1_1(Qcall_function,
		phrase_list_2(Nil,SYMBOLP(function_definition_designation) 
		? function_definition_designation : Nil));
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	node = gensymed_symbol;
	argument = Nil;
	ab_loop_list_ = argument_expressions;
	arg_nodes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = 
		stack_cons_1(convert_expression_to_stack_node_tree(argument),
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    arg_nodes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_2;
      end_loop_2:
	if (ATOM(function_definition_designation) ? 
		function_definition_designation && 
		SYMBOLP(function_definition_designation) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(function_definition_designation))))
	    temp = 
		    convert_designation_to_stack_node_tree(function_definition_designation);
	else {
	    compiler_error(2,string_constant_42,
		    function_definition_designation);
	    temp = make_dummy_stack_node();
	}
	svref_new_value = stack_cons_1(temp,arg_nodes);
	SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	temp = node;
	goto end_3;
	temp = Qnil;
      end_3:;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* EVAL-RECEIVES-A-VALUE-FUNCALLED */
Object eval_receives_a_value_funcalled(item_or_datum)
    Object item_or_datum;
{
    x_note_fn_call(208,137);
    if ( !(FIXNUMP(item_or_datum) || SYMBOLP(item_or_datum) || 
	    SIMPLE_VECTOR_P(item_or_datum)))
	reclaim_if_evaluation_value_1(item_or_datum);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-FAILS-TO-RECEIVE-A-VALUE-FUNCALLED */
Object eval_fails_to_receive_a_value_funcalled(item)
    Object item;
{
    x_note_fn_call(208,138);
    return VALUES_1(T ? ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)32L) ? Evaluation_true_value : 
	    Evaluation_false_value) : Nil);
}

/* EVAL-IS-MOVED-FUNCALLED */
Object eval_is_moved_funcalled(item)
    Object item;
{
    x_note_fn_call(208,139);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-MOVED-BY-THE-USER-FUNCALLED */
Object eval_is_moved_by_the_user_funcalled(item)
    Object item;
{
    x_note_fn_call(208,140);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-MOVED-BY-G2-FUNCALLED */
Object eval_is_moved_by_g2_funcalled(item)
    Object item;
{
    x_note_fn_call(208,141);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-BECOMES-RELATED-FUNCALLED */
Object eval_becomes_related_funcalled(given_relation_name,item1,item2)
    Object given_relation_name, item1, item2;
{
    Object given_name, relation_instances, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash;
    Object relation_instance_form, the_block, blocks, result_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(208,142);
    given_name = given_relation_name;
    relation_instances = ISVREF(item2,(SI_Long)12L);
    if (relation_instances) {
	skip_list = CDR(relation_instances);
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
	relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (relation_instance_form) {
	    the_block = item1;
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    result_1 = temp_2 ? Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

/* EVAL-CEASES-TO-BE-RELATED-FUNCALLED */
Object eval_ceases_to_be_related_funcalled(given_relation_name,item1,item2)
    Object given_relation_name, item1, item2;
{
    Object given_name, relation_instances, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash;
    Object relation_instance_form, the_block, blocks, result_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(208,143);
    given_name = given_relation_name;
    relation_instances = ISVREF(item2,(SI_Long)12L);
    if (relation_instances) {
	skip_list = CDR(relation_instances);
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
	relation_instance_form = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (relation_instance_form) {
	    the_block = item1;
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    result_1 = temp_2 ? Evaluation_false_value : Evaluation_true_value;
    return VALUES_1(result_1);
}

/* EVAL-IS-ACTIVATED-FUNCALLED */
Object eval_is_activated_funcalled(item)
    Object item;
{
    x_note_fn_call(208,144);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-DEACTIVATED-FUNCALLED */
Object eval_is_deactivated_funcalled(item)
    Object item;
{
    x_note_fn_call(208,145);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-ENABLED-FUNCALLED */
Object eval_is_enabled_funcalled(item)
    Object item;
{
    x_note_fn_call(208,146);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-DISABLED-FUNCALLED */
Object eval_is_disabled_funcalled(item)
    Object item;
{
    x_note_fn_call(208,147);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-LOSES-ITS-VALUE-FUNCALLED */
Object eval_loses_its_value_funcalled(variable)
    Object variable;
{
    x_note_fn_call(208,148);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-IS-CREATED-FUNCALLED */
Object eval_is_created_funcalled(item)
    Object item;
{
    x_note_fn_call(208,149);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-GENERIC-EVENT-FUNCALLED */
Object eval_generic_event_funcalled(item,event_name,event_object)
    Object item, event_name, event_object;
{
    x_note_fn_call(208,150);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-GENERIC-BECOMES-RELATED-FUNCALLED */
Object eval_generic_becomes_related_funcalled(item1,item2)
    Object item1, item2;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance_form, ab_loop_it_;
    Object ab_less_than_branch_qm_, the_block, blocks, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(208,151);
    relation_instances = ISVREF(item2,(SI_Long)12L);
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
	  relation_instance_form = M_CDR(ab_entry_cons_);
	  the_block = item1;
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
	next_loop_2:
	  if (level < ab_loop_bind_)
	      goto end_loop_2;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_3:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_2 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_2,temp);
	  MVS_2(result,succ,marked);
	next_loop_4:
	  if ( !TRUEP(marked))
	      goto end_loop_3;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_2 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_2,temp);
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
	  ab_loop_it_ = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop;
	end_loop_1:
	  temp_1 = TRUEP(Qnil);
	end_2:;
	POP_SPECIAL();
    }
    else
	temp_1 = TRUEP(Nil);
    return VALUES_1(temp_1 ? Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-GENERIC-CEASES-TO-BE-RELATED-FUNCALLED */
Object eval_generic_ceases_to_be_related_funcalled(item1,item2)
    Object item1, item2;
{
    Object relation_instances, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance_form, ab_loop_it_;
    Object ab_less_than_branch_qm_, the_block, blocks, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(208,152);
    relation_instances = ISVREF(item2,(SI_Long)12L);
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
	  relation_instance_form = M_CDR(ab_entry_cons_);
	  the_block = item1;
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
	next_loop_2:
	  if (level < ab_loop_bind_)
	      goto end_loop_2;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_3:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_2 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_2,temp);
	  MVS_2(result,succ,marked);
	next_loop_4:
	  if ( !TRUEP(marked))
	      goto end_loop_3;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_2 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_2,temp);
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
	  ab_loop_it_ = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop;
	end_loop_1:
	  temp_1 = TRUEP(Qnil);
	end_2:;
	POP_SPECIAL();
    }
    else
	temp_1 = TRUEP(Nil);
    return VALUES_1(temp_1 ? Evaluation_false_value : Evaluation_true_value);
}

/* EVAL-GENERIC-DIRECTLY-CONNECTED-TO-FUNCALLED */
Object eval_generic_directly_connected_to_funcalled(connection,
	    filter_symbol,item)
    Object connection, filter_symbol, item;
{
    x_note_fn_call(208,153);
    return VALUES_1(generic_directly_connected_p(connection,item) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-GENERIC-DIRECTLY-DISCONNECTED-FROM-FUNCALLED */
Object eval_generic_directly_disconnected_from_funcalled(filter_symbol,item)
    Object filter_symbol, item;
{
    x_note_fn_call(208,154);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-DIRECTLY-CONNECTED-TO-FUNCALLED */
Object eval_directly_connected_to_funcalled(connection,filter_symbol,item)
    Object connection, filter_symbol, item;
{
    x_note_fn_call(208,155);
    return VALUES_1(generic_directly_connected_p(connection,item) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-DIRECTLY-DISCONNECTED-FROM-FUNCALLED */
Object eval_directly_disconnected_from_funcalled(connection_class,
	    filter_symbol,item)
    Object connection_class, filter_symbol, item;
{
    x_note_fn_call(208,156);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-INDIRECTLY-CONNECTED-TO-FUNCALLED */
Object eval_indirectly_connected_to_funcalled(item1,item2)
    Object item1, item2;
{
    x_note_fn_call(208,157);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-INDIRECTLY-DISCONNECTED-FROM-FUNCALLED */
Object eval_indirectly_disconnected_from_funcalled(item1,item2)
    Object item1, item2;
{
    x_note_fn_call(208,158);
    return VALUES_1(Evaluation_true_value);
}

/* EVAL-NUPEC-SYNCHRONIZATION-OCCURS-FUNCALLED */
Object eval_nupec_synchronization_occurs_funcalled()
{
    x_note_fn_call(208,159);
    return VALUES_1(Evaluation_true_value);
}

/* IS-OF-CLASS-STACK-NODE-CONVERTER */
Object is_of_class_stack_node_converter(expression)
    Object expression;
{
    Object operator_1, stack_evaluator_descriptions_qm, gensymed_symbol, node;
    Object class_expr, temp, svref_new_value;
    char temp_1;

    x_note_fn_call(208,160);
    operator_1 = CAR(expression);
    stack_evaluator_descriptions_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
	    Qstack_evaluators);
    gensymed_symbol = make_stack_node_1_1(operator_1,
	    stack_evaluator_descriptions_qm);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    node = gensymed_symbol;
    class_expr = THIRD(expression);
    if (CONSP(class_expr) && EQ(CAR(class_expr),Qquote)) {
	temp = SECOND(class_expr);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  
	    !TRUEP(type_specification_for_user_or_datum_type(SECOND(class_expr))) 
	    : TRUEP(Nil))
	record_free_reference(Qab_class,SECOND(class_expr));
    svref_new_value = make_stack_argument_nodes(operator_1,CDR(expression),
	    stack_evaluator_descriptions_qm);
    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(node);
    return VALUES_1(Nil);
}

static Object string_constant_43;  /* "In the expression ~NA IS A ~s, ~s is not a class name or type." */

/* INVALID-TYPE-OR-CLASS-MESSAGE */
Object invalid_type_or_class_message(item_or_datum_to_test,type_or_class)
    Object item_or_datum_to_test, type_or_class;
{
    x_note_fn_call(208,161);
    return tformat_stack_error_text_string(4,string_constant_43,
	    item_or_datum_to_test,type_or_class,type_or_class);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* EVAL-IS-OF-CLASS-FUNCALLED */
Object eval_is_of_class_funcalled(item_or_datum_to_test,type_or_class)
    Object item_or_datum_to_test, type_or_class;
{
    Object type_specification_of_user_type_qm, result_1, x, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, class_description_qm, item_class_p_qm, x2;
    Object sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(208,162);
    if (type_or_class) {
	type_specification_of_user_type_qm = 
		type_specification_for_user_or_datum_type(type_or_class);
	result_1 = Falsity;
	if (type_specification_of_user_type_qm) {
	    if (type_specification_type_p(item_or_datum_to_test,
		    type_specification_of_user_type_qm))
		result_1 = Truth;
	}
	else {
	    x = type_or_class;
	    if (SYMBOLP(x)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = x;
		key_hash_value = SXHASH_SYMBOL_1(x) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    gensymed_symbol = x;
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
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
			goto end_3;
		    goto next_loop_7;
		  end_loop_8:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_6;
		  end_loop_6:;
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
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
			goto end_4;
		    goto next_loop_10;
		  end_loop_11:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		class_description_qm = resulting_value;
	    }
	    else
		class_description_qm = Nil;
	    item_class_p_qm = class_description_qm ? 
		    ISVREF(class_description_qm,(SI_Long)16L) : Qnil;
	    if ( !TRUEP(item_class_p_qm)) {
		temp_1 = Cached_top_of_stack;
		raw_stack_error_named_error(temp_1,
			invalid_type_or_class_message(item_or_datum_to_test,
			type_or_class));
	    }
	    else {
		if (SIMPLE_VECTOR_P(item_or_datum_to_test) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_to_test)) 
			> (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_to_test,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_datum_to_test,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    gensymed_symbol = ISVREF(item_or_datum_to_test,
			    (SI_Long)1L);
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(class_description_qm,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
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
		if (temp_2)
		    result_1 = Truth;
	    }
	}
	if ( !(FIXNUMP(item_or_datum_to_test) || 
		SYMBOLP(item_or_datum_to_test) || 
		SIMPLE_VECTOR_P(item_or_datum_to_test)))
	    reclaim_if_evaluation_value_1(item_or_datum_to_test);
	if (FIXNUM_EQ(result_1,Truth))
	    temp_1 = Evaluation_true_value;
	else if (FIXNUM_EQ(result_1,Falsity))
	    temp_1 = Evaluation_false_value;
	else
	    temp_1 = eval_cons_1(result_1,Qtruth_value);
    }
    else
	temp_1 = Evaluation_false_value;
    return VALUES_1(temp_1);
}

/* EVAL-IS-ACTIVE-FUNCALLED */
Object eval_is_active_funcalled(kb_workspace)
    Object kb_workspace;
{
    x_note_fn_call(208,163);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) 
	    & (SI_Long)1L) ? Evaluation_true_value : Evaluation_false_value);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* EVAL-HAS-A-NAME-FUNCALLED */
Object eval_has_a_name_funcalled(item)
    Object item;
{
    x_note_fn_call(208,164);
    return VALUES_1(get_lookup_slot_value_given_default(item,
	    Qname_or_names_for_frame,Nil) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

static Object string_constant_44;  /* "CONNECTION-PORTNAME" */

static Object Qnone;               /* none */

/* EVAL-CONNECTION-PORTNAME-FUNCALLED */
Object eval_connection_portname_funcalled(block,connection)
    Object block, connection;
{
    Object portname_qm;

    x_note_fn_call(208,165);
    check_args_for_connection_evaluator(block,connection,
	    string_constant_44,Cached_top_of_stack);
    portname_qm = get_port_name_given_block_and_connection(2,block,
	    ISVREF(connection,(SI_Long)21L));
    return VALUES_1(portname_qm ? portname_qm : Qnone);
}

static Object string_constant_45;  /* "CONNECTION-SIDE" */

static Object array_constant_2;    /* # */

/* EVAL-CONNECTION-SIDE-FUNCALLED */
Object eval_connection_side_funcalled(block,connection)
    Object block, connection;
{
    Object temp;

    x_note_fn_call(208,166);
    check_args_for_connection_evaluator(block,connection,
	    string_constant_45,Cached_top_of_stack);
    temp = ISVREF(array_constant_2,
	    IFIX(get_position_at_this_end_of_connection(ISVREF(connection,
	    (SI_Long)21L),block)) & (SI_Long)3L);
    return VALUES_1(temp);
}

static Object string_constant_46;  /* "CONNECTION-POSITION" */

/* EVAL-CONNECTION-POSITION-FUNCALLED */
Object eval_connection_position_funcalled(block,connection)
    Object block, connection;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(208,167);
    check_args_for_connection_evaluator(block,connection,
	    string_constant_46,Cached_top_of_stack);
    temp = IFIX(get_position_at_this_end_of_connection(ISVREF(connection,
	    (SI_Long)21L),block));
    temp_1 = make_evaluation_quantity(FIX(temp >>  -  - (SI_Long)2L));
    return VALUES_1(temp_1);
}

static Object string_constant_47;  /* "CONNECTION-DIRECTION" */

/* EVAL-CONNECTION-DIRECTION-FUNCALLED */
Object eval_connection_direction_funcalled(block,connection)
    Object block, connection;
{
    Object temp;

    x_note_fn_call(208,168);
    check_args_for_connection_evaluator(block,connection,
	    string_constant_47,Cached_top_of_stack);
    temp = get_direction_of_connection(2,ISVREF(connection,(SI_Long)21L),
	    block);
    if (temp);
    else
	temp = Qnone;
    return VALUES_1(temp);
}

/* EVAL-CONNECTION-STYLE-FUNCALLED */
Object eval_connection_style_funcalled(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(208,169);
    temp = get_style_of_connection(ISVREF(connection,(SI_Long)21L));
    return VALUES_1(temp);
}

static Object string_constant_48;  /* "The first argument to ~a was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object string_constant_49;  /* "The connection argument to ~a was a connection which is not ~
				    *         connected to the block. The connection was ~NF."
				    */

/* CHECK-ARGS-FOR-CONNECTION-EVALUATOR */
Object check_args_for_connection_evaluator(item,connection,
	    evaluator_name_string,top_of_stack)
    Object item, connection, evaluator_name_string, top_of_stack;
{
    Object sub_class_bit_vector, top_of_stack_1, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,170);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if ( !temp) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_48,
		evaluator_name_string,item);
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else if ( !TRUEP(connection_connected_to_block_p(ISVREF(connection,
	    (SI_Long)21L),item))) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_49,
		evaluator_name_string,connection);
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_50;  /* "The first argument to items-are-connected was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object string_constant_51;  /* "The second argument to items-are-connected was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

/* EVAL-ITEMS-ARE-CONNECTED-FUNCALLED */
Object eval_items_are_connected_funcalled(block1,block2)
    Object block1, block2;
{
    Object sub_class_bit_vector, top_of_stack, message_1, class_of_block2;
    Object connected_items_qm, connected_item, ab_loop_list_, result_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,171);
    sub_class_bit_vector = ISVREF(ISVREF(block1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_50,
		block1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	if ( !temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_51,block2);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    class_of_block2 = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)1L);
    connected_items_qm = search_for_directly_connected_entities(block1,
	    class_of_block2,Nil,Nil,Nil,Nil,Nil,Nil);
    connected_item = Nil;
    ab_loop_list_ = connected_items_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connected_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(connected_item,block2)) {
	result_1 = Evaluation_true_value;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    result_1 = Evaluation_false_value;
    goto end_1;
    result_1 = Qnil;
  end_1:;
    reclaim_eval_tree_1(connected_items_qm);
    return VALUES_1(result_1);
}

static Object string_constant_52;  /* "The first argument to items-are-connected-with-direction was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object string_constant_53;  /* "The second argument to items-are-connected-with-direction was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object Qinput;              /* input */

static Object Qoutput;             /* output */

static Object string_constant_54;  /* "The third argument to items-are-connected-with-direction was ~NF.  It has to be either input or output." */

/* EVAL-ITEMS-ARE-CONNECTED-WITH-DIRECTION-FUNCALLED */
Object eval_items_are_connected_with_direction_funcalled(block1,block2,
	    direction)
    Object block1, block2, direction;
{
    Object sub_class_bit_vector, top_of_stack, message_1, class_of_block2;
    Object connected_items_qm, connected_item, ab_loop_list_, result_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,172);
    sub_class_bit_vector = ISVREF(ISVREF(block1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_52,
		block1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	if ( !temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_53,block2);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if ( !(EQ(direction,Qinput) || EQ(direction,Qoutput))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_54,direction);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    class_of_block2 = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)1L);
    connected_items_qm = search_for_directly_connected_entities(block1,
	    class_of_block2,Nil,direction,direction,Nil,Nil,Nil);
    connected_item = Nil;
    ab_loop_list_ = connected_items_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connected_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(connected_item,block2)) {
	result_1 = Evaluation_true_value;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    result_1 = Evaluation_false_value;
    goto end_1;
    result_1 = Qnil;
  end_1:;
    reclaim_eval_tree_1(connected_items_qm);
    return VALUES_1(result_1);
}

static Object string_constant_55;  /* "The first argument to items-are-connected-at-ports was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object string_constant_56;  /* "The second argument to items-are-connected-at-ports was an item which was not a block ~
				    *         so it has no connections.  The argument was ~NF."
				    */

static Object Qany;                /* any */

static Object Qport_names;         /* port-names */

/* EVAL-ITEMS-ARE-CONNECTED-AT-PORTS-FUNCALLED */
Object eval_items_are_connected_at_ports_funcalled(block1,block2,
	    source_port,target_port)
    Object block1, block2, source_port, target_port;
{
    Object sub_class_bit_vector, top_of_stack, message_1, class_of_block2;
    Object connected_items_qm, connected_item, ab_loop_list_, temp_1;
    Object connected_item_entry;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,173);
    sub_class_bit_vector = ISVREF(ISVREF(block1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_55,
		block1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	if ( !temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_56,block2);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    class_of_block2 = ISVREF(ISVREF(block2,(SI_Long)1L),(SI_Long)1L);
    if (EQ(source_port,Qany) && EQ(target_port,Qany))
	connected_items_qm = search_for_directly_connected_entities(block1,
		class_of_block2,Nil,Nil,Nil,Nil,Nil,Nil);
    else if (EQ(target_port,Qany))
	connected_items_qm = search_for_directly_connected_entities(block1,
		class_of_block2,source_port,Nil,Nil,Nil,Nil,Nil);
    else if (EQ(source_port,Qany))
	connected_items_qm = search_for_directly_connected_entities(block1,
		class_of_block2,Nil,Nil,Nil,Qport_names,Nil,Nil);
    else
	connected_items_qm = search_for_directly_connected_entities(block1,
		class_of_block2,source_port,Nil,Nil,Qport_names,Nil,Nil);
    if (EQ(target_port,Qany)) {
	connected_item = Nil;
	ab_loop_list_ = connected_items_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connected_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(connected_item,block2)) {
	    reclaim_eval_tree_1(connected_items_qm);
	    temp_1 = Evaluation_true_value;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	reclaim_eval_tree_1(connected_items_qm);
	temp_1 = Evaluation_false_value;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else {
	connected_item_entry = Nil;
	ab_loop_list_ = connected_items_qm;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	connected_item_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(FIRST(connected_item_entry),block2) && 
		memq_function(target_port,SECOND(connected_item_entry))) {
	    reclaim_eval_tree_1(connected_items_qm);
	    temp_1 = Evaluation_true_value;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_tree_1(connected_items_qm);
	temp_1 = Evaluation_false_value;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
    }
    return VALUES_1(temp_1);
}

static Object Qfocal_objects;      /* focal-objects */

/* EVAL-WHICH-HAS-THE-FOCAL-OBJECT-FUNCALLED */
Object eval_which_has_the_focal_object_funcalled(rule,symbol)
    Object rule, symbol;
{
    Object result_1;

    x_note_fn_call(208,174);
    result_1 = do_query_evaluation_for_rule_restriction(3,rule,symbol,
	    Qfocal_objects) ? Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

static Object Qfocal_classes;      /* focal-classes */

/* EVAL-WHICH-HAS-THE-FOCAL-CLASS-FUNCALLED */
Object eval_which_has_the_focal_class_funcalled(rule,symbol)
    Object rule, symbol;
{
    Object result_1;

    x_note_fn_call(208,175);
    result_1 = do_query_evaluation_for_rule_restriction(3,rule,symbol,
	    Qfocal_classes) ? Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

static Object Qrule_categories;    /* rule-categories */

/* EVAL-IN-THE-CATEGORY-FUNCALLED */
Object eval_in_the_category_funcalled(rule,symbol)
    Object rule, symbol;
{
    Object result_1;

    x_note_fn_call(208,176);
    result_1 = do_query_evaluation_for_rule_restriction(3,rule,symbol,
	    Qrule_categories) ? Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

/* EVAL-WITH-STATUS-FUNCALLED */
Object eval_with_status_funcalled(item,status)
    Object item, status;
{
    Object result_1;

    x_note_fn_call(208,177);
    result_1 = do_query_evaluation_for_with_status(item,status) ? 
	    Evaluation_true_value : Evaluation_false_value;
    return VALUES_1(result_1);
}

/* EVAL-WITH-NOTES-FUNCALLED */
Object eval_with_notes_funcalled(item)
    Object item;
{
    x_note_fn_call(208,178);
    return VALUES_1(ISVREF(item,(SI_Long)8L) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

/* EVAL-CONTAINING-FUNCALLED */
Object eval_containing_funcalled(item,what_to_look_for)
    Object item, what_to_look_for;
{
    Object result_1;
    char text_p_qm;

    x_note_fn_call(208,179);
    text_p_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(what_to_look_for) != 
	    (SI_Long)0L;
    result_1 = do_query_evaluation_for_containing(item,text_p_qm ? 
	    what_to_look_for : what_to_look_for,Nil) ? 
	    Evaluation_true_value : Evaluation_false_value;
    if (text_p_qm)
	reclaim_text_string(what_to_look_for);
    return VALUES_1(result_1);
}

/* EVAL-CONTAINING-WORD-FUNCALLED */
Object eval_containing_word_funcalled(item,what_to_look_for)
    Object item, what_to_look_for;
{
    Object result_1;
    char text_p_qm;

    x_note_fn_call(208,180);
    text_p_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(what_to_look_for) != 
	    (SI_Long)0L;
    result_1 = do_query_evaluation_for_containing(item,text_p_qm ? 
	    what_to_look_for : what_to_look_for,T) ? Evaluation_true_value 
	    : Evaluation_false_value;
    if (text_p_qm)
	reclaim_text_string(what_to_look_for);
    return VALUES_1(result_1);
}

/* EVAL-CONTAINING-SYMBOL-FUNCALLED */
Object eval_containing_symbol_funcalled(item,what_to_look_for)
    Object item, what_to_look_for;
{
    Object result_1;
    char text_p_qm;

    x_note_fn_call(208,181);
    text_p_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(what_to_look_for) != 
	    (SI_Long)0L;
    result_1 = do_query_evaluation_for_containing(item,text_p_qm ? 
	    what_to_look_for : what_to_look_for,Qsymbol) ? 
	    Evaluation_true_value : Evaluation_false_value;
    if (text_p_qm)
	reclaim_text_string(what_to_look_for);
    return VALUES_1(result_1);
}

static Object Qname_for_debugging;  /* name-for-debugging */

/* EVAL-G2-INSPECT-INTERNAL-NAME-FOR-DEBUGGING-P-FUNCALLED */
Object eval_g2_inspect_internal_name_for_debugging_p_funcalled(item,
	    symbol_or_string)
    Object item, symbol_or_string;
{
    Object sub_class_bit_vector, gensymed_symbol_3, result_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,182);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	gensymed_symbol_3 = get_lookup_slot_value_given_default(item,
		Qname_for_debugging,Nil);
	temp = text_string_p(gensymed_symbol_3) ? 
		TRUEP(string_eq_w(gensymed_symbol_3,
		SYMBOLP(symbol_or_string) ? 
		symbol_name_text_string(symbol_or_string) : 
		symbol_or_string)) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    result_1 = temp ? Evaluation_true_value : Evaluation_false_value;
    reclaim_evaluation_value(symbol_or_string);
    return VALUES_1(result_1);
}

/* EVAL-ASSIGNED-TO-MODULE-FUNCALLED */
Object eval_assigned_to_module_funcalled(item,module,search_hierarchy_p)
    Object item, module, search_hierarchy_p;
{
    Object result_1;

    x_note_fn_call(208,183);
    result_1 = (evaluation_truth_value_true_p(search_hierarchy_p) ? 
	    TRUEP(within_module_hierarchy_p(item,module)) : 
	    EQ(get_module_block_is_in(item),module)) ? 
	    Evaluation_true_value : Evaluation_false_value;
    if ( !(EQ(search_hierarchy_p,Evaluation_true_value) || 
	    EQ(search_hierarchy_p,Evaluation_false_value)))
	reclaim_eval_cons_1(search_hierarchy_p);
    return VALUES_1(result_1);
}

/* EVAL-WITH-CHANGES-LOGGED-2-FUNCALLED */
Object eval_with_changes_logged_2_funcalled(item,before,after,author)
    Object item, before, after, author;
{
    x_note_fn_call(208,184);
    return VALUES_1(item_has_changes_logged_p(item,before,after,author) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* FUNCALL-COERCE-NO-ITEM-TO-UNKNOWN-INST */
Object funcall_coerce_no_item_to_unknown_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    x_note_fn_call(208,185);
    if ( !TRUEP(ISVREF(local_stack,IFIX(top_of_stack))))
	Stack_expiration = Nil;
    return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object string_constant_57;  /* " given to the operator ~a is out of bounds of ~
				    *                   the empty text."
				    */

static Object string_constant_58;  /* " given to the operator ~a is out of bounds of the ~
				    *                    text \"~a\", which has length ~d."
				    */

/* INDEX-OF-G2-TEXT-TOO-LARGE-EVAL-ERROR */
Object index_of_g2_text_too_large_eval_error(index_1,g2_text,
	    evaluator_name,top_of_stack)
    Object index_1, g2_text, evaluator_name, top_of_stack;
{
    Object top_of_stack_1, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(208,186);
    if (string_equalw(g2_text,array_constant_1)) {
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
		      twrite_beginning_of_wide_string(array_constant_3,
			      FIX((SI_Long)10L));
		      gensymed_symbol = index_1;
		      temp = FIXNUMP(gensymed_symbol);
		      if (temp);
		      else
			  temp = 
				  INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
				  (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = gensymed_symbol ? 
				  SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = 
				  INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L;
		      if (temp);
		      else if (CONSP(gensymed_symbol)) {
			  gensymed_symbol = M_CDR(gensymed_symbol);
			  temp = EQ(gensymed_symbol,Qtruth_value);
			  if (temp);
			  else
			      temp = EQ(gensymed_symbol,Qiteration_state);
			  if (temp);
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
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			    next_loop_2:
			      if ( !TRUEP(marked))
				  goto end_loop_1;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			      goto next_loop_2;
			    end_loop_1:
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
			      goto next_loop_1;
			    end_loop_2:
			    end_1:
			      level = level - (SI_Long)1L;
			      goto next_loop;
			    end_loop:;
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
		      if (temp)
			  write_evaluation_value(1,index_1);
		      else
			  twrite(index_1);
		      tformat(2,string_constant_57,evaluator_name);
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
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else {
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
		      twrite_beginning_of_wide_string(array_constant_3,
			      FIX((SI_Long)10L));
		      gensymed_symbol = index_1;
		      temp = FIXNUMP(gensymed_symbol);
		      if (temp);
		      else
			  temp = 
				  INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
				  (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = gensymed_symbol ? 
				  SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = 
				  INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L;
		      if (temp);
		      else if (CONSP(gensymed_symbol)) {
			  gensymed_symbol = M_CDR(gensymed_symbol);
			  temp = EQ(gensymed_symbol,Qtruth_value);
			  if (temp);
			  else
			      temp = EQ(gensymed_symbol,Qiteration_state);
			  if (temp);
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
			    next_loop_3:
			      if (level < ab_loop_bind_)
				  goto end_loop_3;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_4:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			    next_loop_5:
			      if ( !TRUEP(marked))
				  goto end_loop_4;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			      goto next_loop_5;
			    end_loop_4:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
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
		      if (temp)
			  write_evaluation_value(1,index_1);
		      else
			  twrite(index_1);
		      gensymed_symbol = g2_text;
		      temp = FIXNUMP(gensymed_symbol);
		      if (temp);
		      else
			  temp = 
				  INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
				  (SI_Long)0L ? 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				  == (SI_Long)1L : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = gensymed_symbol ? 
				  SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = 
				  INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				  != (SI_Long)0L;
		      if (temp);
		      else if (CONSP(gensymed_symbol)) {
			  gensymed_symbol = M_CDR(gensymed_symbol);
			  temp = EQ(gensymed_symbol,Qtruth_value);
			  if (temp);
			  else
			      temp = EQ(gensymed_symbol,Qiteration_state);
			  if (temp);
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
			    next_loop_6:
			      if (level < ab_loop_bind_)
				  goto end_loop_6;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_7:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			    next_loop_8:
			      if ( !TRUEP(marked))
				  goto end_loop_7;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_1 = ATOMIC_REF_OBJECT(reference);
			      temp_2 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_1,temp_2);
			      MVS_2(result,succ,marked);
			      goto next_loop_8;
			    end_loop_7:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
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
		      temp_2 = temp ? g2_text : g2_text;
		      tformat(4,string_constant_58,evaluator_name,temp_2,
			      text_string_length(g2_text));
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
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
}

static Object string_constant_59;  /* "The ~a operator cannot return a text containing ~
				    *          more than ~a characters.  The text arguments began with ~
				    *          \"~a...\" and \"~a...\"."
				    */

/* MERGED-STRING-WOULD-BE-TOO-LONG-EVAL-ERROR */
Object merged_string_would_be_too_long_eval_error(source_text_value,
	    destination_text_value,evaluator_name,top_of_stack)
    Object source_text_value, destination_text_value, evaluator_name;
    Object top_of_stack;
{
    Object small_source_text, small_destination_text, top_of_stack_1;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(208,187);
    small_source_text = text_string_substring(source_text_value,
	    FIX((SI_Long)0L),FIX((SI_Long)20L));
    small_destination_text = text_string_substring(destination_text_value,
	    FIX((SI_Long)0L),FIX((SI_Long)20L));
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
		  tformat(5,string_constant_59,evaluator_name,
			  Maximum_length_for_user_text_strings,
			  small_source_text,small_destination_text);
		  reclaim_text_string(small_source_text);
		  reclaim_text_string(small_destination_text);
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
    return raw_stack_error_named_error(top_of_stack_1,message_1);
}

/* EVAL-BITWISE-NOT-FUNCALLED */
Object eval_bitwise_not_funcalled(value1)
    Object value1;
{
    SI_Long quantity_value1;

    x_note_fn_call(208,188);
    quantity_value1 = IFIX(value1);
    return VALUES_1(FIX( ~quantity_value1));
}

/* EVAL-BITWISE-XOR-FUNCALLED */
Object eval_bitwise_xor_funcalled(value1,value2)
    Object value1, value2;
{
    SI_Long quantity_value1, quantity_value2;

    x_note_fn_call(208,189);
    quantity_value1 = IFIX(value1);
    quantity_value2 = IFIX(value2);
    return VALUES_1(FIX(quantity_value1 ^ quantity_value2));
}

/* EVAL-BITWISE-RIGHT-SHIFT-FUNCALLED */
Object eval_bitwise_right_shift_funcalled(value,shift_count)
    Object value, shift_count;
{
    SI_Long quantity_value, quantity_shift_count;

    x_note_fn_call(208,190);
    quantity_value = IFIX(value);
    quantity_shift_count = IFIX(FIXNUM_NEGATE(shift_count));
    return VALUES_1((SI_Long)0L <= quantity_shift_count ? 
	    FIX(quantity_value << quantity_shift_count) : 
	    FIX(quantity_value >>  - quantity_shift_count));
}

/* EVAL-BITWISE-LEFT-SHIFT-FUNCALLED */
Object eval_bitwise_left_shift_funcalled(value,shift_count)
    Object value, shift_count;
{
    SI_Long quantity_value, quantity_shift_count;

    x_note_fn_call(208,191);
    quantity_value = IFIX(value);
    quantity_shift_count = IFIX(shift_count);
    return VALUES_1((SI_Long)0L <= quantity_shift_count ? 
	    FIX(quantity_value << quantity_shift_count) : 
	    FIX(quantity_value >>  - quantity_shift_count));
}

static Object string_constant_60;  /* "Desired test index ~a is outside the range 0-29" */

/* EVAL-BITWISE-TEST-FUNCALLED */
Object eval_bitwise_test_funcalled(value,location)
    Object value, location;
{
    Object top_of_stack, message_1;
    SI_Long quantity_value, quantity_location;

    x_note_fn_call(208,192);
    quantity_value = IFIX(value);
    quantity_location = IFIX(location);
    if ((SI_Long)0L > quantity_location || quantity_location > (SI_Long)29L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_60,
		FIX(quantity_location));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(quantity_location == (SI_Long)29L ? ((SI_Long)0L > 
	    quantity_value ? Evaluation_true_value : 
	    Evaluation_false_value) : (SI_Long)0L != ((SI_Long)1L << 
	    quantity_location & quantity_value) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

static Object string_constant_61;  /* "Desired set index ~a is outside the range 0-28" */

/* EVAL-BITWISE-SET-FUNCALLED */
Object eval_bitwise_set_funcalled(value,location)
    Object value, location;
{
    Object top_of_stack, message_1;
    SI_Long quantity_value, quantity_location, set_value;

    x_note_fn_call(208,193);
    quantity_value = IFIX(value);
    quantity_location = IFIX(location);
    set_value = (SI_Long)1L;
    if ((SI_Long)0L > quantity_location || quantity_location > (SI_Long)28L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_61,
		FIX(quantity_location));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    set_value = set_value << quantity_location;
    return VALUES_1(FIX(quantity_value | set_value));
}

static Object Qlatitude;           /* latitude */

static Object Qgreat_circle_distance;  /* great-circle-distance */

static Object Qlongitude;          /* longitude */

static Object Qradius;             /* radius */

/* EVAL-GREAT-CIRCLE-DISTANCE-FUNCALLED */
Object eval_great_circle_distance_funcalled(lat1,long1,lat2,long2,radius)
    Object lat1, long1, lat2, long2, radius;
{
    Object lat1_value, long1_value, lat2_value, long2_value, temp;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    double radius_value, arg, arg_1, arg_2, temp_1, gensymed_symbol;
    double gensymed_symbol_1, temp_4, sin_value, gensymed_symbol_2;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(208,194);
    lat1_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(lat1,(SI_Long)0L));
    long1_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(long1,(SI_Long)0L));
    lat2_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(lat2,(SI_Long)0L));
    long2_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(long2,(SI_Long)0L));
    radius_value = DFLOAT_ISAREF_1(radius,(SI_Long)0L);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	arg = -90.1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(lat1_value);
	arg_2 = 90.1;
	if ( !(arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2))) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    invalid_argument_eval_error_message(lat1_value,
		    Qlatitude,Qgreat_circle_distance));
	}
	arg = -90.1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(lat2_value);
	arg_2 = 90.1;
	if ( !(arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2))) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    invalid_argument_eval_error_message(lat2_value,
		    Qlatitude,Qgreat_circle_distance));
	}
	arg = -180.1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(long1_value);
	arg_2 = 180.1;
	if ( !(arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2))) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    invalid_argument_eval_error_message(long1_value,
		    Qlongitude,Qgreat_circle_distance));
	}
	arg = -180.1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(long2_value);
	arg_2 = 180.1;
	if ( !(arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2))) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    invalid_argument_eval_error_message(long2_value,
		    Qlongitude,Qgreat_circle_distance));
	}
	if (0.0 > radius_value) {
	    temp = Cached_top_of_stack;
	    raw_stack_error_named_error(temp,
		    invalid_argument_eval_error_message(DOUBLE_TO_DOUBLE_FLOAT(radius_value),
		    Qradius,Qgreat_circle_distance));
	}
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(lat1_value);
	lat1_value = DOUBLE_TO_DOUBLE_FLOAT(0.017453292519943295 * temp_1);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(long1_value);
	long1_value = DOUBLE_TO_DOUBLE_FLOAT(0.017453292519943295 * temp_1);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(lat2_value);
	lat2_value = DOUBLE_TO_DOUBLE_FLOAT(0.017453292519943295 * temp_1);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(long2_value);
	long2_value = DOUBLE_TO_DOUBLE_FLOAT(0.017453292519943295 * temp_1);
	reclaim_managed_simple_float_array_of_length_1(lat1);
	reclaim_managed_simple_float_array_of_length_1(long1);
	reclaim_managed_simple_float_array_of_length_1(lat2);
	reclaim_managed_simple_float_array_of_length_1(long2);
	reclaim_managed_simple_float_array_of_length_1(radius);
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
	gensymed_symbol = 2.0;
	gensymed_symbol_1 = radius_value;
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(lat1_value);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(lat2_value);
	sin_value = sin((temp_4 - temp_1) / 2.0);
	gensymed_symbol_2 = sin_value * sin_value;
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(lat1_value);
	gensymed_symbol_3 = cos(temp_1);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(lat2_value);
	gensymed_symbol_4 = cos(temp_1);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(long1_value);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(long2_value);
	sin_value = sin((temp_4 - temp_1) / 2.0);
	gensymed_symbol_5 = sin_value * sin_value;
	gensymed_symbol_3 = gensymed_symbol_3 * gensymed_symbol_4 * 
		gensymed_symbol_5;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_2 = sqrt(gensymed_symbol_2);
	temp = lasin(DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol_2));
	gensymed_symbol_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	aref_new_value = gensymed_symbol * gensymed_symbol_1 * 
		gensymed_symbol_2;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

static Object Qcolor_value;        /* color-value */

static Object Qrgb_symbol;         /* rgb-symbol */

static Object Qtformat_text_string;  /* tformat-text-string */

static Object string_constant_62;  /* "RGB~c~c~c~c~c~c" */

/* EVAL-RGB-SYMBOL-FUNCALLED */
Object eval_rgb_symbol_funcalled(red_value,green_value,blue_value)
    Object red_value, green_value, blue_value;
{
    Object red_value_value, green_value_value, blue_value_value, hex_char_list;
    Object hex_char_1, hex_char_2, temp, result_1;
    Object result;

    x_note_fn_call(208,195);
    red_value_value = red_value;
    green_value_value = green_value;
    blue_value_value = blue_value;
    hex_char_list = Nil;
    hex_char_1 = Nil;
    hex_char_2 = Nil;
    if ( !((SI_Long)0L <= IFIX(red_value_value) && IFIX(red_value_value) 
	    <= (SI_Long)255L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(red_value_value,
		Qcolor_value,Qrgb_symbol));
    }
    if ( !((SI_Long)0L <= IFIX(green_value_value) && 
	    IFIX(green_value_value) <= (SI_Long)255L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(green_value_value,
		Qcolor_value,Qrgb_symbol));
    }
    if ( !((SI_Long)0L <= IFIX(blue_value_value) && IFIX(blue_value_value) 
	    <= (SI_Long)255L)) {
	temp = Cached_top_of_stack;
	raw_stack_error_named_error(temp,
		invalid_argument_eval_error_message(blue_value_value,
		Qcolor_value,Qrgb_symbol));
    }
    result = hex_color_values(blue_value_value);
    MVS_2(result,hex_char_1,hex_char_2);
    hex_char_list = gensym_cons_1(hex_char_1,gensym_cons_1(hex_char_2,
	    hex_char_list));
    result = hex_color_values(green_value_value);
    MVS_2(result,hex_char_1,hex_char_2);
    hex_char_list = gensym_cons_1(hex_char_1,gensym_cons_1(hex_char_2,
	    hex_char_list));
    result = hex_color_values(red_value_value);
    MVS_2(result,hex_char_1,hex_char_2);
    hex_char_list = gensym_cons_1(hex_char_1,gensym_cons_1(hex_char_2,
	    hex_char_list));
    temp = SYMBOL_FUNCTION(Qtformat_text_string);
    result_1 = intern_text_string(1,APPLY_2(temp,string_constant_62,
	    hex_char_list));
    reclaim_gensym_list_1(hex_char_list);
    return VALUES_1(result_1);
}

/* HEX-COLOR-VALUES */
Object hex_color_values(color_value)
    Object color_value;
{
    Object hex_digit_1, hex_digit_2, temp, temp_1;
    Object result;

    x_note_fn_call(208,196);
    result = chestnut_floorf_function(color_value,FIX((SI_Long)16L));
    MVS_2(result,hex_digit_1,hex_digit_2);
    temp = digit_char(hex_digit_1,FIX((SI_Long)16L),_);
    temp_1 = digit_char(hex_digit_2,FIX((SI_Long)16L),_);
    return VALUES_2(temp,temp_1);
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* PPRINT-CQN-FRAME-OR-PLACE-REFERENCE-INSTRUCTION */
Object pprint_cqn_frame_or_place_reference_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack;
{
    x_note_fn_call(208,197);
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)10L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)2L));
    write_stack_argument(FIX((SI_Long)3L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    return VALUES_1(Nil);
}

/* FUNCALL-CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE-INST */
Object funcall_class_qualified_name_frame_or_place_reference_inst(top_of_stack,
	    local_stack)
    Object top_of_stack, local_stack;
{
    Object parent_frame, class_qualifier, pretty_slot_name;
    Object frame_or_place_reference;
    SI_Long svref_arg_2;

    x_note_fn_call(208,198);
    parent_frame = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    class_qualifier = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    pretty_slot_name = ISVREF(local_stack,IFIX(top_of_stack));
    frame_or_place_reference = 
	    fetch_attribute_frame_or_place_reference(parent_frame,
	    pretty_slot_name,class_qualifier,top_of_stack);
    svref_arg_2 = IFIX(top_of_stack) - (SI_Long)2L;
    ISVREF(local_stack,svref_arg_2) = frame_or_place_reference;
    return VALUES_1(Nil);
}

/* SEQUENCE-STACK-NODE-CONVERTER */
Object sequence_stack_node_converter(expression)
    Object expression;
{
    Object arg, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(208,199);
    arg = Nil;
    ab_loop_list_ = M_CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(arg),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qsequence,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object list_constant_15;    /* # */

/* SEQUENCE-I-CHOOSER */
Object sequence_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, arg_required_type;
    Object unknown_args_qm, arg_cons, arg, svref_new_value;

    x_note_fn_call(208,200);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    arg_required_type = maybe_add_unknown(Qitem_or_datum,unknown_allowed_qm);
    unknown_args_qm = Nil;
    arg_cons = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg = Nil;
  next_loop:
    if ( !TRUEP(arg_cons))
	goto end_loop;
    arg = choose_stack_node_instructions_and_types(2,M_CAR(arg_cons),
	    arg_required_type);
    M_CAR(arg_cons) = arg;
    if (unknown_allowed_qm &&  !TRUEP(unknown_args_qm) && 
	    type_specification_subtype_p(list_constant,ISVREF(arg,
	    (SI_Long)6L)))
	unknown_args_qm = T;
    arg_cons = M_CDR(arg_cons);
    goto next_loop;
  end_loop:;
    svref_new_value = maybe_add_unknown(list_constant_15,unknown_args_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmake_evaluation_sequence;  /* make-evaluation-sequence */

/* SEQUENCE-I-EMIT */
Object sequence_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object args, arg, ab_loop_list_;

    x_note_fn_call(208,201);
    args = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg = Nil;
    ab_loop_list_ = args;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:
    emit_funcall_instruction_byte_codes(4,byte_code_stream,
	    Qmake_evaluation_sequence,length(args),FIX((SI_Long)1L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* PPRINT-MAKE-EVALUATION-SEQUENCE-INSTRUCTION */
Object pprint_make_evaluation_sequence_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack,arg_count,
	    result_count)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack, arg_count, result_count;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(208,202);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)9L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(arg_count);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if ( !(index_1 == (SI_Long)1L))
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
    write_stack_argument(FIX(index_1),arg_count,stack,top_of_stack);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    twrite_character(FIX((SI_Long)41L));
    return VALUES_1(Nil);
}

/* FUNCALL-MAKE-EVALUATION-SEQUENCE-INST */
Object funcall_make_evaluation_sequence_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object element_count_arg, new_sequence;
    SI_Long elt_count, base_stack_index;

    x_note_fn_call(208,203);
    element_count_arg = ISVREF(local_stack,IFIX(top_of_stack));
    elt_count = IFIX(element_count_arg);
    base_stack_index = IFIX(top_of_stack) - elt_count;
    new_sequence = 
	    allocate_new_evaluation_sequence_from_simple_vector(local_stack,
	    FIX(base_stack_index),FIX(elt_count));
    ISVREF(local_stack,base_stack_index) = new_sequence;
    return VALUES_1(Nil);
}

static Object Qevaluated_structure;  /* evaluated-structure */

/* EVALUATED-STRUCTURE-STACK-NODE-CONVERTER */
Object evaluated_structure_stack_node_converter(expression)
    Object expression;
{
    Object arg, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(208,204);
    arg = Nil;
    ab_loop_list_ = M_CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(arg),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qevaluated_structure,
	    Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

static Object string_constant_63;  /* "Evaluated-structure requires an even number of arguments, it received ~a." */

static Object list_constant_16;    /* # */

/* EVALUATED-STRUCTURE-I-CHOOSER */
Object evaluated_structure_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, name_arg_required_type;
    Object value_arg_required_type, unknown_args_qm, args, arg_cons, name_arg;
    Object value_arg, svref_new_value;

    x_note_fn_call(208,205);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    name_arg_required_type = maybe_add_unknown(Qsymbol,unknown_allowed_qm);
    value_arg_required_type = maybe_add_unknown(Qitem_or_datum,
	    unknown_allowed_qm);
    unknown_args_qm = Nil;
    args = ISVREF(stack_node_instruction,(SI_Long)2L);
    if ( !((IFIX(length(args)) & (SI_Long)1L) == (SI_Long)0L)) {
	compiler_error(2,string_constant_63,length(args));
	args = Nil;
    }
    arg_cons = args;
    name_arg = Nil;
    value_arg = Nil;
  next_loop:
    if ( !TRUEP(arg_cons))
	goto end_loop;
    name_arg = choose_stack_node_instructions_and_types(2,CAR(arg_cons),
	    name_arg_required_type);
    value_arg = choose_stack_node_instructions_and_types(2,
	    SECOND(arg_cons),value_arg_required_type);
    M_CAR(arg_cons) = name_arg;
    M_SECOND(arg_cons) = value_arg;
    if (unknown_allowed_qm &&  !TRUEP(unknown_args_qm) && 
	    (type_specification_subtype_p(list_constant,ISVREF(name_arg,
	    (SI_Long)6L)) || type_specification_subtype_p(list_constant,
	    ISVREF(value_arg,(SI_Long)6L))))
	unknown_args_qm = T;
    arg_cons = CDDR(arg_cons);
    goto next_loop;
  end_loop:;
    svref_new_value = maybe_add_unknown(list_constant_16,unknown_args_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmake_evaluated_structure;  /* make-evaluated-structure */

/* EVALUATED-STRUCTURE-I-EMIT */
Object evaluated_structure_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object args, arg, ab_loop_list_;

    x_note_fn_call(208,206);
    args = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg = Nil;
    ab_loop_list_ = args;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:
    emit_funcall_instruction_byte_codes(4,byte_code_stream,
	    Qmake_evaluated_structure,length(args),FIX((SI_Long)1L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

/* PPRINT-MAKE-EVALUATED-STRUCTURE-INSTRUCTION */
Object pprint_make_evaluated_structure_instruction(description,pc,
	    byte_code_body,constant_vector,stack,top_of_stack,arg_count,
	    result_count)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack, arg_count, result_count;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(208,207);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)20L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(arg_count);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if ( !(index_1 == (SI_Long)1L))
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
    write_stack_argument(FIX(index_1),arg_count,stack,top_of_stack);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    twrite_character(FIX((SI_Long)41L));
    return VALUES_1(Nil);
}

/* FUNCALL-MAKE-EVALUATED-STRUCTURE-INST */
Object funcall_make_evaluated_structure_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object key_count_times_two_arg, new_sequence;
    SI_Long key_count_times_two, base_stack_index;

    x_note_fn_call(208,208);
    key_count_times_two_arg = ISVREF(local_stack,IFIX(top_of_stack));
    key_count_times_two = IFIX(key_count_times_two_arg);
    base_stack_index = IFIX(top_of_stack) - key_count_times_two;
    new_sequence = allocate_evaluation_structure_from_vector(local_stack,
	    FIX(base_stack_index),FIX(key_count_times_two));
    ISVREF(local_stack,base_stack_index) = new_sequence;
    return VALUES_1(Nil);
}

static Object string_constant_64;  /* "~NA, element ~d of sequence ~NA, is not an integer ~
				    *                        between 0 and 65535, and therefore not a valid ~
				    *                        character code."
				    */

static Object string_constant_65;  /* "The character-codes-to-text function cannot return a text containing ~
				    *                      more than ~d characters; the argument sequence had ~d elements"
				    */

/* EVAL-CHARACTER-CODES-TO-TEXT-FUNCALLED */
Object eval_character_codes_to_text_funcalled(character_codes_sequence)
    Object character_codes_sequence;
{
    Object gensymed_symbol, held_vector, value, elt_1, validated_elt;
    Object top_of_stack, message_1, text_string, ab_loop_iter_flag_, temp;
    SI_Long index_1, next_index, length_1, i;

    x_note_fn_call(208,209);
    index_1 = (SI_Long)0L;
    gensymed_symbol = character_codes_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    value = Nil;
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
    value = validated_elt;
    if ( !(FIXNUMP(value) && (SI_Long)0L <= IFIX(value) && IFIX(value) <= 
	    (SI_Long)65535L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_64,
		value,FIX(index_1),character_codes_sequence);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (index_1 > IFIX(Maximum_length_for_user_text_strings)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_65,
		Maximum_length_for_user_text_strings,FIX(index_1));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    text_string = obtain_text_string(FIX(index_1));
    gensymed_symbol = character_codes_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    value = Nil;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop_1:
    if (next_index >= length_1)
	goto end_loop_1;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    value = validated_elt;
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    UBYTE_16_ISASET_1(text_string,i,IFIX(value));
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:;
    temp = copy_as_wide_string(text_string);
    reclaim_evaluation_sequence(character_codes_sequence);
    reclaim_text_string(text_string);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* EVAL-TEXT-TO-CHARACTER-CODES-FUNCALLED */
Object eval_text_to_character_codes_funcalled(text)
    Object text;
{
    Object length_1, sequence, managed_array, svref_arg_1;
    SI_Long i, j, ab_loop_repeat_, svref_arg_2, svref_new_value;

    x_note_fn_call(208,210);
    length_1 = text_string_length(text);
    sequence = allocate_empty_evaluation_sequence(length_1);
    managed_array = CAR(sequence);
    i = (SI_Long)1L;
    j = (SI_Long)0L;
    ab_loop_repeat_ = IFIX(length_1);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	svref_new_value = UBYTE_16_ISAREF_1(text,j);
	ISVREF(managed_array,svref_arg_2) = FIX(svref_new_value);
    }
    else {
	svref_arg_1 = ISVREF(managed_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = UBYTE_16_ISAREF_1(text,j);
	ISVREF(svref_arg_1,svref_arg_2) = FIX(svref_new_value);
    }
    i = i + (SI_Long)1L;
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_text_string(text);
    return VALUES_1(sequence);
}

static Object string_constant_66;  /* "~NA is not an integer ~
				    *           between 0 and 65535, and therefore not a valid ~
				    *           character code."
				    */

/* REQUIRE-EVALUATION-VALUE-AS-VALID-CHARACTER-CODE */
Object require_evaluation_value_as_valid_character_code(evaluation_value)
    Object evaluation_value;
{
    Object top_of_stack, message_1, temp_1;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(208,211);
    if (FIXNUMP(evaluation_value)) {
	arg = (SI_Long)0L;
	arg_1 = IFIX(evaluation_value);
	arg_2 = (SI_Long)65535L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_66,
		evaluation_value);
	temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* EVAL-IS-UPPERCASE-FUNCALLED */
Object eval_is_uppercase_funcalled(character_code)
    Object character_code;
{
    x_note_fn_call(208,212);
    require_evaluation_value_as_valid_character_code(character_code);
    return VALUES_1(unicode_lowercase_if_uppercase(character_code) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-IS-TITLECASE-FUNCALLED */
Object eval_is_titlecase_funcalled(character_code)
    Object character_code;
{
    x_note_fn_call(208,213);
    require_evaluation_value_as_valid_character_code(character_code);
    return VALUES_1(IFIX(character_code) == (SI_Long)453L || 
	    IFIX(character_code) == (SI_Long)456L || IFIX(character_code) 
	    == (SI_Long)459L || IFIX(character_code) == (SI_Long)498L ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-IS-LOWERCASE-FUNCALLED */
Object eval_is_lowercase_funcalled(character_code)
    Object character_code;
{
    x_note_fn_call(208,214);
    require_evaluation_value_as_valid_character_code(character_code);
    return VALUES_1(unicode_uppercase_if_lowercase(character_code) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-TO-UPPERCASE-FUNCALLED */
Object eval_to_uppercase_funcalled(character_code)
    Object character_code;
{
    Object temp;

    x_note_fn_call(208,215);
    require_evaluation_value_as_valid_character_code(character_code);
    if (IFIX(character_code) < (SI_Long)127L)
	temp = (SI_Long)97L <= IFIX(character_code) && 
		IFIX(character_code) <= (SI_Long)122L ? 
		FIX(IFIX(character_code) + (SI_Long)-32L) : character_code;
    else {
	temp = unicode_uppercase_if_lowercase(character_code);
	if (temp);
	else
	    temp = character_code;
    }
    return VALUES_1(temp);
}

/* EVAL-TO-TITLECASE-FUNCALLED */
Object eval_to_titlecase_funcalled(character_code)
    Object character_code;
{
    Object temp;

    x_note_fn_call(208,216);
    require_evaluation_value_as_valid_character_code(character_code);
    if ( !(FIXNUMP(character_code) && FIXNUM_LE(FIX((SI_Long)-32768L),
	    character_code) && FIXNUM_LE(character_code,
		FIX((SI_Long)32767L)))) {
	if (IFIX(character_code) < (SI_Long)127L)
	    temp = (SI_Long)97L <= IFIX(character_code) && 
		    IFIX(character_code) <= (SI_Long)122L ? 
		    FIX(IFIX(character_code) + (SI_Long)-32L) : character_code;
	else {
	    temp = unicode_uppercase_if_lowercase(character_code);
	    if (temp);
	    else
		temp = character_code;
	}
    }
    else
	switch (INTEGER_TO_SHORT(character_code)) {
	  case 453:
	    temp = FIX((SI_Long)452L);
	    break;
	  case 456:
	    temp = FIX((SI_Long)455L);
	    break;
	  case 459:
	    temp = FIX((SI_Long)458L);
	    break;
	  case 498:
	    temp = FIX((SI_Long)497L);
	    break;
	  default:
	    if (IFIX(character_code) < (SI_Long)127L)
		temp = (SI_Long)97L <= IFIX(character_code) && 
			IFIX(character_code) <= (SI_Long)122L ? 
			FIX(IFIX(character_code) + (SI_Long)-32L) : 
			character_code;
	    else {
		temp = unicode_uppercase_if_lowercase(character_code);
		if (temp);
		else
		    temp = character_code;
	    }
	    break;
	}
    return VALUES_1(temp);
}

/* EVAL-TO-LOWERCASE-FUNCALLED */
Object eval_to_lowercase_funcalled(character_code)
    Object character_code;
{
    Object temp;

    x_note_fn_call(208,217);
    require_evaluation_value_as_valid_character_code(character_code);
    if (IFIX(character_code) < (SI_Long)127L)
	temp = (SI_Long)65L <= IFIX(character_code) && 
		IFIX(character_code) <= (SI_Long)90L ? 
		FIX(IFIX(character_code) + (SI_Long)32L) : character_code;
    else {
	temp = unicode_lowercase_if_uppercase(character_code);
	if (temp);
	else
	    temp = character_code;
    }
    return VALUES_1(temp);
}

/* EVAL-IS-DIGIT-FUNCALLED */
Object eval_is_digit_funcalled(character_code)
    Object character_code;
{
    x_note_fn_call(208,218);
    require_evaluation_value_as_valid_character_code(character_code);
    return VALUES_1((SI_Long)48L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)57L || (SI_Long)1632L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)1641L 
	    || (SI_Long)1776L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)1785L || (SI_Long)2406L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)2415L 
	    || (SI_Long)2534L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)2543L || (SI_Long)2662L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)2671L 
	    || (SI_Long)2790L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)2799L || (SI_Long)2918L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)2927L 
	    || (SI_Long)3047L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)3055L || (SI_Long)3174L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)3183L 
	    || (SI_Long)3302L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)3311L || (SI_Long)3430L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)3439L 
	    || (SI_Long)3664L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)3673L || (SI_Long)3792L <= 
	    IFIX(character_code) && IFIX(character_code) <= (SI_Long)3801L 
	    || (SI_Long)65296L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)65305L ? 
	    Evaluation_true_value : Evaluation_false_value);
}

/* EVAL-IS-READABLE-DIGIT-FUNCALLED */
Object eval_is_readable_digit_funcalled(character_code)
    Object character_code;
{
    x_note_fn_call(208,219);
    require_evaluation_value_as_valid_character_code(character_code);
    return VALUES_1((SI_Long)48L <= IFIX(character_code) && 
	    IFIX(character_code) <= (SI_Long)57L ? Evaluation_true_value : 
	    Evaluation_false_value);
}

static Object string_constant_67;  /* "~NA is not an integer ~
				    *           between 2 and 36, and therefore not a valid radix."
				    */

/* REQUIRE-EVALUATION-VALUE-AS-VALID-RADIX */
Object require_evaluation_value_as_valid_radix(evaluation_value)
    Object evaluation_value;
{
    Object top_of_stack, message_1;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(208,220);
    if (FIXNUMP(evaluation_value)) {
	arg = (SI_Long)2L;
	arg_1 = IFIX(evaluation_value);
	arg_2 = (SI_Long)36L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_67,
		evaluation_value);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return VALUES_1(Nil);
}

/* EVAL-IS-READABLE-DIGIT-IN-RADIX-FUNCALLED */
Object eval_is_readable_digit_in_radix_funcalled(character_code,radix)
    Object character_code, radix;
{
    x_note_fn_call(208,221);
    require_evaluation_value_as_valid_character_code(character_code);
    require_evaluation_value_as_valid_radix(radix);
    return VALUES_1(digit_char_pw_function(character_code,radix) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

static Object string_constant_68;  /* "The value ~NV has no readable representation." */

/* EVAL-READABLE-TEXT-FOR-VALUE-FUNCALLED */
Object eval_readable_text_for_value_funcalled(value)
    Object value;
{
    Object result_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, top_of_stack, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(208,222);
    result_1 = Nil;
    if (FIXNUMP(value) || INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
	    (SI_Long)1L || INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L || 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L || 
	    value && SYMBOLP(value) || CONSP(value) && EQ(M_CDR(value),
	    Qtruth_value)) {
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
		  write_evaluation_value(1,value);
		  result_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	    reclaim_if_evaluation_value_1(value);
	temp = result_1;
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_68,
		value);
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(temp);
}

/* EVAL-READABLE-TEXT-FUNCALLED */
Object eval_readable_text_funcalled(printed_representation_text)
    Object printed_representation_text;
{
    Object write_strings_parsably_qm, result_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(208,223);
    write_strings_parsably_qm = T;
    result_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
	    5);
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
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		twrite_general_string(printed_representation_text);
		result_1 = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      reclaim_text_string(printed_representation_text);
      temp = result_1;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant_69;  /* "The text beginning with \"~a...\" is not valid as the text of a symbol.  ~a" */

static Object string_constant_70;  /* "The text \"~a\" is not valid as the text of a symbol.  ~a" */

static Object Qpunctuation_mark_p;  /* punctuation-mark-p */

/* EVAL-READABLE-SYMBOL-TEXT-FUNCALLED */
Object eval_readable_symbol_text_funcalled(printed_representation_text)
    Object printed_representation_text;
{
    Object problem_string_qm, length_1, small_text, top_of_stack, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, temp, symbol, write_symbols_parsably_qm, result_1;
    SI_Long max_length, bv16_length, aref_arg_2, aref_new_value, length_2;
    char truncate_p;
    Declare_special(7);

    x_note_fn_call(208,224);
    problem_string_qm = 
	    non_valid_symbol_text_string_p(printed_representation_text);
    if (problem_string_qm) {
	length_1 = text_string_length(printed_representation_text);
	max_length = (SI_Long)200L;
	truncate_p = IFIX(length_1) > max_length;
	small_text = truncate_p ? 
		text_string_substring(printed_representation_text,
		FIX((SI_Long)0L),FIX(max_length)) : 
		printed_representation_text;
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
		  length_2 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_2 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(3,truncate_p ? string_constant_69 : 
			      string_constant_70,small_text,problem_string_qm);
		      if (truncate_p)
			  reclaim_text_string(small_text);
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
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	symbol = intern_text_string(1,
		copy_text_string(printed_representation_text));
	write_symbols_parsably_qm = T;
	result_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		5);
	  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		  Qpunctuation_mark_p)) {
	      temp = copy_text_string(printed_representation_text);
	      symbol = intern_text_string(2,temp,Keyword_package_1);
	  }
	  else if (syntactically_numeric_p(symbol_name_text_string(symbol)))
	      mutate_global_property(symbol,Qnumeric,
		      Qtype_of_syntactic_anomaly);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
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
		length_2 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    twrite_symbol(1,symbol);
		    result_1 = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  reclaim_text_string(printed_representation_text);
	  temp = result_1;
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

/* EVAL-COMPARE-TEXT-FUNCALLED */
Object eval_compare_text_funcalled(text_1,text_2)
    Object text_1, text_2;
{
    SI_Long temp;

    x_note_fn_call(208,225);
    temp = string_lt_w(text_1,text_2) ? (SI_Long)-1L : string_eq_w(text_1,
	    text_2) ? (SI_Long)0L : (SI_Long)1L;
    reclaim_text_string(text_1);
    reclaim_text_string(text_2);
    return VALUES_1(FIX(temp));
}

static Object Qinternal_structure_for_text_conversion_style;  /* internal-structure-for-text-conversion-style */

/* MAP-TO-INTERNAL-TEXT-CONVERSION-STYLE */
Object map_to_internal_text_conversion_style(text_conversion_style_frame)
    Object text_conversion_style_frame;
{
    Object temp;

    x_note_fn_call(208,226);
    temp = get_lookup_slot_value_given_default(text_conversion_style_frame,
	    Qinternal_structure_for_text_conversion_style,Nil);
    return VALUES_1(temp);
}

/* EVAL-IMPORT-TEXT-FUNCALLED */
Object eval_import_text_funcalled(text,text_conversion_style)
    Object text, text_conversion_style;
{
    Object temp;

    x_note_fn_call(208,227);
    temp = map_to_internal_text_conversion_style(text_conversion_style);
    if (temp);
    else
	temp = Default_text_conversion_style;
    temp = import_text_string_per_text_conversion_style(2,text,temp);
    reclaim_text_string(text);
    return VALUES_1(temp);
}

/* EVAL-EXPORT-TEXT-FUNCALLED */
Object eval_export_text_funcalled(text,text_conversion_style)
    Object text, text_conversion_style;
{
    Object temp;

    x_note_fn_call(208,228);
    temp = map_to_internal_text_conversion_style(text_conversion_style);
    if (temp);
    else
	temp = Default_text_conversion_style;
    temp = export_text_string_per_text_conversion_style(2,text,temp);
    reclaim_text_string(text);
    return VALUES_1(temp);
}

/* EVAL-TRANSFORM-TEXT-FOR-UNICODE-COMPARISON-FUNCALLED */
Object eval_transform_text_for_unicode_comparison_funcalled(text,
	    consider_case_p)
    Object text, consider_case_p;
{
    Object temp;

    x_note_fn_call(208,229);
    temp = evaluation_truth_value_true_p(consider_case_p) ? text : 
	    nstring_downcasew(text);
    return VALUES_1(temp);
}

static Object Qutf_g_wide_string;  /* utf-g-wide-string */

/* EVAL-TRANSFORM-TEXT-FOR-G2-4.0-COMPARISON-FUNCALLED */
Object eval_transform_text_for_g2_4_dot_0_comparison_funcalled(text,
	    consider_case_p)
    Object text, consider_case_p;
{
    Object temp;

    x_note_fn_call(208,230);
    temp = export_text_string(2,
	    evaluation_truth_value_true_p(consider_case_p) ? text : 
	    nstring_downcasew(text),Qutf_g_wide_string);
    reclaim_text_string(text);
    return VALUES_1(temp);
}

static Object string_constant_71;  /* "The index ~A was not within the range of indices for ~NE." */

/* EVAL-REMOVE-FUNCALLED */
Object eval_remove_funcalled(sequence,index_to_remove)
    Object sequence, index_to_remove;
{
    Object new_sequence, temp, top_of_stack, message_1;

    x_note_fn_call(208,231);
    new_sequence = evaluation_sequence_remove_element_at_index(sequence,
	    index_to_remove);
    if (new_sequence)
	temp = new_sequence;
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_71,
		index_to_remove,sequence);
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(temp);
}

/* EVAL-INSERT-AT-BEGINNING-FUNCALLED */
Object eval_insert_at_beginning_funcalled(sequence,item_or_value_to_add)
    Object sequence, item_or_value_to_add;
{
    Object temp;

    x_note_fn_call(208,232);
    temp = evaluation_sequence_insert_at_beginning(sequence,
	    item_or_value_to_add);
    return VALUES_1(temp);
}

/* EVAL-INSERT-AT-END-FUNCALLED */
Object eval_insert_at_end_funcalled(sequence,item_or_value_to_add)
    Object sequence, item_or_value_to_add;
{
    Object temp;

    x_note_fn_call(208,233);
    temp = evaluation_sequence_insert_at_end(sequence,item_or_value_to_add);
    return VALUES_1(temp);
}

static Object string_constant_72;  /* "Unable to find ~NA in ~NA, cannot insert ~NA as new element." */

/* EVALUATION-SEQUENCE-INSERT-BEFORE-OR-AFTER */
Object evaluation_sequence_insert_before_or_after(sequence,new_element,
	    existing_element,before_qm)
    Object sequence, new_element, existing_element, before_qm;
{
    Object new_sequence, insertion_done, gensymed_symbol, held_vector, element;
    Object elt_1, validated_elt, svref_arg_1, item_or_value, x2;
    Object svref_new_value, top_of_stack, message_1;
    SI_Long new_length, index_1, next_index, length_1, gensymed_symbol_1;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(208,234);
    new_length = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L))) + 
	    (SI_Long)1L;
    new_sequence = allocate_empty_evaluation_sequence(FIX(new_length));
    insertion_done = Nil;
    index_1 = (SI_Long)0L;
    gensymed_symbol = sequence;
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
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    if ( !TRUEP(insertion_done) && before_qm && item_or_value_eql(element,
	    existing_element)) {
	gensymed_symbol = M_CAR(new_sequence);
	gensymed_symbol_1 = index_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_1 = M_CAR(new_sequence);
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    item_or_value = new_element;
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
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	index_1 = index_1 + (SI_Long)1L;
	insertion_done = T;
    }
    gensymed_symbol = M_CAR(new_sequence);
    gensymed_symbol_1 = index_1 + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_1 = M_CAR(new_sequence);
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	item_or_value = FIXNUMP(element) || element && SYMBOLP(element) || 
		SIMPLE_VECTOR_P(element) ? element : 
		copy_if_evaluation_value_1(element);
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
	ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	item_or_value = FIXNUMP(element) || element && SYMBOLP(element) || 
		SIMPLE_VECTOR_P(element) ? element : 
		copy_if_evaluation_value_1(element);
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
	ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    if ( !TRUEP(insertion_done) &&  !TRUEP(before_qm) && 
	    item_or_value_eql(element,existing_element)) {
	index_1 = index_1 + (SI_Long)1L;
	gensymed_symbol = M_CAR(new_sequence);
	gensymed_symbol_1 = index_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_1 = M_CAR(new_sequence);
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    item_or_value = new_element;
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
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	insertion_done = T;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !TRUEP(insertion_done)) {
	reclaim_evaluation_sequence(new_sequence);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_72,
		existing_element,sequence,new_element);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    reclaim_evaluation_sequence(sequence);
    if ( !(FIXNUMP(existing_element) || SYMBOLP(existing_element) || 
	    SIMPLE_VECTOR_P(existing_element)))
	reclaim_if_evaluation_value_1(existing_element);
    return VALUES_1(new_sequence);
}

/* EVAL-INSERT-BEFORE-FUNCALLED */
Object eval_insert_before_funcalled(sequence,new_element,existing_element)
    Object sequence, new_element, existing_element;
{
    Object temp;

    x_note_fn_call(208,235);
    temp = evaluation_sequence_insert_before_or_after(sequence,new_element,
	    existing_element,T);
    return VALUES_1(temp);
}

/* EVAL-INSERT-AFTER-FUNCALLED */
Object eval_insert_after_funcalled(sequence,new_element,existing_element)
    Object sequence, new_element, existing_element;
{
    Object temp;

    x_note_fn_call(208,236);
    temp = evaluation_sequence_insert_before_or_after(sequence,new_element,
	    existing_element,Nil);
    return VALUES_1(temp);
}

static Object string_constant_73;  /* "Index ~NA in ~NA is out of range, cannot insert ~NA ~
				    *                         as new element."
				    */

/* EVALUATION-SEQUENCE-INSERT-OR-REPLACE-AT-INDEX */
Object evaluation_sequence_insert_or_replace_at_index(sequence,new_element,
	    element_index,insert_qm)
    Object sequence, new_element, element_index, insert_qm;
{
    Object thing, gensymed_symbol, gensymed_symbol_1, svref_arg_1, temp_1;
    Object item_or_value, x2, svref_new_value, temp_2, new_sequence;
    Object insertion_done_qm, held_vector, value, elt_1, validated_elt;
    Object top_of_stack, message_1;
    SI_Long arg, arg_1, arg_2, svref_arg_2, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, new_length, index_1, next_index, length_1;
    char temp;

    x_note_fn_call(208,237);
    if ( !TRUEP(insert_qm) && (FIXNUM_LE(ISVREF(M_CAR(sequence),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    IFIX(ISVREF(M_CAR(sequence),(SI_Long)0L + 
	    IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(M_CAR(sequence),(SI_Long)2L),(SI_Long)0L))) 
	    == (SI_Long)1L) {
	arg = (SI_Long)0L;
	arg_1 = IFIX(element_index);
	arg_2 = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L)));
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	thing = evaluation_sequence_aref(sequence,element_index);
	if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	    reclaim_if_evaluation_value_1(thing);
	gensymed_symbol = M_CAR(sequence);
	gensymed_symbol_1 = FIXNUM_ADD1(element_index);
	if (FIXNUM_LE(ISVREF(M_CAR(sequence),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_1 = M_CAR(sequence);
	    temp_1 = FIXNUM_ADD(gensymed_symbol_1,Managed_array_index_offset);
	    item_or_value = new_element;
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
	    SVREF(svref_arg_1,temp_1) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(gensymed_symbol_1) & (SI_Long)1023L;
	    item_or_value = new_element;
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
	    temp_1 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
	}
	temp_2 = sequence;
    }
    else {
	gensymed_symbol_2 = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),
		(SI_Long)1L)));
	gensymed_symbol_3 = insert_qm ? (SI_Long)1L : (SI_Long)0L;
	new_length = gensymed_symbol_2 + gensymed_symbol_3;
	new_sequence = allocate_empty_evaluation_sequence(FIX(new_length));
	if (IFIX(element_index) == new_length - (SI_Long)1L && 
		IFIX(element_index) != (SI_Long)-1L) {
	    copy_evaluation_sequence_elements(sequence,FIX((SI_Long)0L),
		    FIX(new_length - (SI_Long)1L),new_sequence,
		    FIX((SI_Long)0L));
	    gensymed_symbol = M_CAR(new_sequence);
	    gensymed_symbol_2 = new_length - (SI_Long)1L + (SI_Long)1L;
	    if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_1 = M_CAR(new_sequence);
		svref_arg_2 = gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset);
		item_or_value = new_element;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		ISVREF(svref_arg_1,svref_arg_2) = temp_1;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_2 >> 
			 -  - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
		item_or_value = new_element;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		ISVREF(svref_arg_1,svref_arg_2) = temp_1;
	    }
	}
	else {
	    insertion_done_qm = Nil;
	    index_1 = (SI_Long)0L;
	    gensymed_symbol = sequence;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    value = Nil;
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
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    value = validated_elt;
	    if ( !TRUEP(insertion_done_qm) && index_1 == IFIX(element_index)) {
		gensymed_symbol = M_CAR(new_sequence);
		gensymed_symbol_2 = index_1 + (SI_Long)1L;
		if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_1 = M_CAR(new_sequence);
		    svref_arg_2 = gensymed_symbol_2 + 
			    IFIX(Managed_array_index_offset);
		    item_or_value = new_element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		}
		else {
		    svref_arg_1 = ISVREF(gensymed_symbol,
			    (gensymed_symbol_2 >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
		    item_or_value = new_element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		}
		insertion_done_qm = T;
		if (insert_qm) {
		    index_1 = index_1 + (SI_Long)1L;
		    gensymed_symbol = M_CAR(new_sequence);
		    gensymed_symbol_2 = index_1 + (SI_Long)1L;
		    if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_1 = M_CAR(new_sequence);
			svref_arg_2 = gensymed_symbol_2 + 
				IFIX(Managed_array_index_offset);
			item_or_value = FIXNUMP(value) || value && 
				SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? 
				value : copy_if_evaluation_value_1(value);
			if (SIMPLE_VECTOR_P(item_or_value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				> (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(item_or_value,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			temp_1 = temp ? 
				get_reference_to_item(item_or_value) : 
				item_or_value;
			ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		    }
		    else {
			svref_arg_1 = ISVREF(gensymed_symbol,
				(gensymed_symbol_2 >>  -  - (SI_Long)10L) 
				+ (SI_Long)2L);
			svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
			item_or_value = FIXNUMP(value) || value && 
				SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? 
				value : copy_if_evaluation_value_1(value);
			if (SIMPLE_VECTOR_P(item_or_value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				> (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(item_or_value,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			temp_1 = temp ? 
				get_reference_to_item(item_or_value) : 
				item_or_value;
			ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		    }
		}
	    }
	    else {
		gensymed_symbol = M_CAR(new_sequence);
		gensymed_symbol_2 = index_1 + (SI_Long)1L;
		if (FIXNUM_LE(ISVREF(M_CAR(new_sequence),(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_1 = M_CAR(new_sequence);
		    svref_arg_2 = gensymed_symbol_2 + 
			    IFIX(Managed_array_index_offset);
		    item_or_value = FIXNUMP(value) || value && 
			    SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? 
			    value : copy_if_evaluation_value_1(value);
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		}
		else {
		    svref_arg_1 = ISVREF(gensymed_symbol,
			    (gensymed_symbol_2 >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
		    item_or_value = FIXNUMP(value) || value && 
			    SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? 
			    value : copy_if_evaluation_value_1(value);
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
		}
	    }
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    if ( !TRUEP(insertion_done_qm)) {
		reclaim_evaluation_sequence(new_sequence);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_73,element_index,sequence,new_element);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	}
	reclaim_evaluation_sequence(sequence);
	temp_2 = new_sequence;
    }
    return VALUES_1(temp_2);
}

/* EVAL-INSERT-BEFORE-ELEMENT-FUNCALLED */
Object eval_insert_before_element_funcalled(sequence,index_1,new_element)
    Object sequence, index_1, new_element;
{
    Object temp;

    x_note_fn_call(208,238);
    temp = evaluation_sequence_insert_or_replace_at_index(sequence,
	    new_element,index_1,T);
    return VALUES_1(temp);
}

/* EVAL-INSERT-AFTER-ELEMENT-FUNCALLED */
Object eval_insert_after_element_funcalled(sequence,index_1,new_element)
    Object sequence, index_1, new_element;
{
    Object temp;

    x_note_fn_call(208,239);
    temp = evaluation_sequence_insert_or_replace_at_index(sequence,
	    new_element,FIXNUM_ADD1(index_1),T);
    return VALUES_1(temp);
}

/* EVAL-CHANGE-ELEMENT-FUNCALLED */
Object eval_change_element_funcalled(sequence,index_1,new_element)
    Object sequence, index_1, new_element;
{
    Object temp;

    x_note_fn_call(208,240);
    temp = evaluation_sequence_insert_or_replace_at_index(sequence,
	    new_element,index_1,Nil);
    return VALUES_1(temp);
}

/* CONCATENATE-STACK-NODE-CONVERTER */
Object concatenate_stack_node_converter(expression)
    Object expression;
{
    Object arg, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object arguments, gensymed_symbol, stack_node_instruction;

    x_note_fn_call(208,241);
    arg = Nil;
    ab_loop_list_ = M_CDR(expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    stack_cons_1(convert_expression_to_stack_node_tree(arg),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    arguments = ab_loopvar_;
    goto end_1;
    arguments = Qnil;
  end_1:;
    gensymed_symbol = make_stack_node_instruction_1_1(Qconcatenate,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    stack_node_instruction = gensymed_symbol;
    SVREF(stack_node_instruction,FIX((SI_Long)2L)) = arguments;
    GENSYM_RETURN_ONE(stack_node_instruction);
    return VALUES_1(Nil);
}

/* CONCATENATE-I-CHOOSER */
Object concatenate_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, unknown_allowed_qm, arg_required_type;
    Object unknown_args_qm, args, arg_cons, arg, svref_new_value;

    x_note_fn_call(208,242);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,
	    required_type);
    arg_required_type = maybe_add_unknown(list_constant_15,unknown_allowed_qm);
    unknown_args_qm = Nil;
    args = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg_cons = args;
    arg = Nil;
  next_loop:
    if ( !TRUEP(arg_cons))
	goto end_loop;
    arg = choose_stack_node_instructions_and_types(2,M_CAR(arg_cons),
	    arg_required_type);
    M_CAR(arg_cons) = arg;
    if (unknown_allowed_qm &&  !TRUEP(unknown_args_qm) && 
	    type_specification_subtype_p(list_constant,ISVREF(arg,
	    (SI_Long)6L)))
	unknown_args_qm = T;
    arg_cons = M_CDR(arg_cons);
    goto next_loop;
  end_loop:;
    svref_new_value = maybe_add_unknown(list_constant_15,unknown_args_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CONCATENATE-I-EMIT */
Object concatenate_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object args, arg, ab_loop_list_;

    x_note_fn_call(208,243);
    args = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg = Nil;
    ab_loop_list_ = args;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:
    emit_funcall_instruction_byte_codes(4,byte_code_stream,Qconcatenate,
	    length(args),FIX((SI_Long)1L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_10;   /* # */

/* PPRINT-CONCATENATE-INSTRUCTION */
Object pprint_concatenate_instruction(description,pc,byte_code_body,
	    constant_vector,stack,top_of_stack,arg_count,result_count)
    Object description, pc, byte_code_body, constant_vector, stack;
    Object top_of_stack, arg_count, result_count;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(208,244);
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)12L));
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(arg_count);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if ( !(index_1 == (SI_Long)1L))
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
    write_stack_argument(FIX(index_1),arg_count,stack,top_of_stack);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    twrite_character(FIX((SI_Long)41L));
    return VALUES_1(Nil);
}

/* FUNCALL-CONCATENATE-INST */
Object funcall_concatenate_inst(top_of_stack,local_stack)
    Object top_of_stack, local_stack;
{
    Object arg_count_arg, arg_count, base_stack_index, seq, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, sequence_pairs, pair, ab_loop_list_;
    Object new_length, new_sequence, length_1;
    SI_Long index_1, ab_loop_bind_, ab_loopvar__3, insertion_point;

    x_note_fn_call(208,245);
    arg_count_arg = ISVREF(local_stack,IFIX(top_of_stack));
    arg_count = arg_count_arg;
    base_stack_index = FIXNUM_MINUS(top_of_stack,arg_count);
    index_1 = IFIX(base_stack_index);
    ab_loop_bind_ = IFIX(top_of_stack);
    seq = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    seq = ISVREF(local_stack,index_1);
    ab_loopvar__2 = eval_cons_1(eval_cons_1(seq,
	    FIXNUM_SUB1(ISVREF(M_CAR(seq),(SI_Long)1L))),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    sequence_pairs = ab_loopvar_;
    goto end_1;
    sequence_pairs = Qnil;
  end_1:;
    pair = Nil;
    ab_loop_list_ = sequence_pairs;
    ab_loopvar__3 = (SI_Long)0L;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__3 = IFIX(M_CDR(pair)) + ab_loopvar__3;
    goto next_loop_1;
  end_loop_1:
    new_length = FIX(ab_loopvar__3);
    goto end_2;
    new_length = Qnil;
  end_2:;
    new_sequence = allocate_empty_evaluation_sequence(new_length);
    insertion_point = (SI_Long)0L;
    pair = Nil;
    ab_loop_list_ = sequence_pairs;
    seq = Nil;
    length_1 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    seq = M_CAR(pair);
    length_1 = M_CDR(pair);
    reclaim_eval_cons_1(pair);
    copy_evaluation_sequence_elements(seq,FIX((SI_Long)0L),length_1,
	    new_sequence,FIX(insertion_point));
    reclaim_evaluation_sequence(seq);
    insertion_point = insertion_point + IFIX(length_1);
    goto next_loop_2;
  end_loop_2:;
    reclaim_eval_list_1(sequence_pairs);
    SVREF(local_stack,base_stack_index) = new_sequence;
    return VALUES_1(Nil);
}

static Object string_constant_74;  /* "In PORTION, the starting index argument, ~a, was less than zero." */

static Object string_constant_75;  /* "In PORTION, the number of elements to copy argument, ~a, was less than zero." */

static Object string_constant_76;  /* "In PORTION, the starting index, ~a, plus the number of elements to ~@
				    *          copy, ~a, was greater than the length of the source sequence, ~a."
				    */

/* EVAL-PORTION-FUNCALLED */
Object eval_portion_funcalled(sequence,start_index,number_to_copy)
    Object sequence, start_index, number_to_copy;
{
    Object top_of_stack, message_1, new_sequence;
    SI_Long index_1, count_1, source_length;

    x_note_fn_call(208,246);
    index_1 = IFIX(start_index);
    count_1 = IFIX(number_to_copy);
    source_length = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L)));
    if (index_1 < (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_74,
		FIX(index_1));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (count_1 < (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_75,
		FIX(count_1));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (index_1 + count_1 > source_length) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_76,
		FIX(index_1),FIX(count_1),FIX(source_length));
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    new_sequence = allocate_empty_evaluation_sequence(FIX(count_1));
    copy_evaluation_sequence_elements(sequence,FIX(index_1),FIX(count_1),
	    new_sequence,FIX((SI_Long)0L));
    reclaim_evaluation_sequence(sequence);
    return VALUES_1(new_sequence);
}

static Object Qchange_evaluated_attribute;  /* change-evaluated-attribute */

static Object string_constant_77;  /* "The second argument to change-attribute should be the attribute name ~
				    *          to be changed, not an expression that evaluates to that name.  ~
				    *          \"~NE\" was provided instead of a name."
				    */

static Object Qstand_in;           /* stand-in */

/* CHANGE-ATTRIBUTE-STACK-NODE-CONVERTER */
Object change_attribute_stack_node_converter(expression)
    Object expression;
{
    Object evaluator_descriptions, gensymed_symbol, node, attribute_name;
    Object svref_new_value;

    x_note_fn_call(208,247);
    evaluator_descriptions = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_evaluated_attribute),
	    Qstack_evaluators);
    gensymed_symbol = make_stack_node_1_1(Qchange_evaluated_attribute,
	    evaluator_descriptions);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    node = gensymed_symbol;
    attribute_name = THIRD(expression);
    if ( !(attribute_name && SYMBOLP(attribute_name))) {
	compiler_error(2,string_constant_77,attribute_name);
	attribute_name = Qstand_in;
    }
    svref_new_value = 
	    make_stack_argument_nodes(Qchange_evaluated_attribute,
	    phrase_list_3(SECOND(expression),phrase_list_2(Qquote,
	    attribute_name),FOURTH(expression)),evaluator_descriptions);
    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(node);
    return VALUES_1(Nil);
}

/* EVAL-CHANGE-EVALUATED-ATTRIBUTE-FUNCALLED */
Object eval_change_evaluated_attribute_funcalled(struct_1,attribute,new_value)
    Object struct_1, attribute, new_value;
{
    Object gensymed_symbol, gensymed_symbol_1, result_struct, temp, name;
    Object gensymed_symbol_3, item_or_value, x2, gensymed_symbol_4;
    Object svref_arg_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_5, ab_loop_bind_, value_index;
    SI_Long svref_arg_2;
    char temp_1;

    x_note_fn_call(208,248);
    gensymed_symbol = struct_1;
    gensymed_symbol_1 = M_CAR(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)0L;
    if ((FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(gensymed_symbol_1,
	    gensymed_symbol_2 + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
	    (SI_Long)1023L))) == (SI_Long)1L)
	result_struct = gensymed_symbol;
    else {
	temp = make_unique_evaluation_structure_copy_1(gensymed_symbol_1);
	reclaim_evaluation_structure(gensymed_symbol);
	result_struct = temp;
    }
    name = attribute;
    gensymed_symbol = result_struct;
    gensymed_symbol_1 = M_CAR(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)1L));
    gensymed_symbol_3 = name;
    item_or_value = new_value;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    gensymed_symbol_4 = temp_1 ? get_reference_to_item(item_or_value) : 
	    item_or_value;
    gensymed_symbol_5 = (SI_Long)1L;
    ab_loop_bind_ = gensymed_symbol_2;
  next_loop:
    if (gensymed_symbol_5 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_1,
	    gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(gensymed_symbol_1,(gensymed_symbol_5 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
	    (SI_Long)1023L),gensymed_symbol_3)) {
	value_index = gensymed_symbol_5 + (SI_Long)1L;
	reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_1,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(gensymed_symbol_1,value_index + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_1,(value_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),value_index & (SI_Long)1023L));
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_1,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = value_index & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_1;
    }
    gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = adjust_managed_array(2,gensymed_symbol_1,
	    FIX(gensymed_symbol_2 + (SI_Long)2L));
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_3;
    }
    else {
	svref_arg_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
    }
    gensymed_symbol_2 = gensymed_symbol_2 + (SI_Long)1L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol_1,svref_arg_2) = gensymed_symbol_4;
    }
    else {
	svref_arg_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
    }
    goto end_1;
  end_1:;
    return VALUES_1(result_struct);
}

static Object Qremove_evaluated_attribute;  /* remove-evaluated-attribute */

static Object string_constant_78;  /* "The second argument to remove-attribute should be the attribute name ~
				    *          to be removed, not an expression that evaluates to that name.  ~
				    *          \"~NE\" was provided instead of a name."
				    */

/* REMOVE-ATTRIBUTE-STACK-NODE-CONVERTER */
Object remove_attribute_stack_node_converter(expression)
    Object expression;
{
    Object evaluator_descriptions, gensymed_symbol, node, attribute_name;
    Object svref_new_value;

    x_note_fn_call(208,249);
    evaluator_descriptions = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qremove_evaluated_attribute),
	    Qstack_evaluators);
    gensymed_symbol = make_stack_node_1_1(Qremove_evaluated_attribute,
	    evaluator_descriptions);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    node = gensymed_symbol;
    attribute_name = THIRD(expression);
    if ( !(attribute_name && SYMBOLP(attribute_name))) {
	compiler_error(2,string_constant_78,attribute_name);
	attribute_name = Qstand_in;
    }
    svref_new_value = 
	    make_stack_argument_nodes(Qremove_evaluated_attribute,
	    phrase_list_2(SECOND(expression),phrase_list_2(Qquote,
	    attribute_name)),evaluator_descriptions);
    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
    GENSYM_RETURN_ONE(node);
    return VALUES_1(Nil);
}

/* EVAL-REMOVE-EVALUATED-ATTRIBUTE-FUNCALLED */
Object eval_remove_evaluated_attribute_funcalled(struct_1,attribute)
    Object struct_1, attribute;
{
    Object name, result_struct_qm, temp;

    x_note_fn_call(208,250);
    name = attribute;
    result_struct_qm = remove_evaluation_structure_attribute(struct_1,name);
    if (result_struct_qm) {
	reclaim_evaluation_structure(struct_1);
	temp = result_struct_qm;
    }
    else
	temp = struct_1;
    return VALUES_1(temp);
}

static Object string_constant_79;  /* "FIND-JAVA-CLASS works only in exported methods and procedures" */

/* EVAL-FIND-JAVA-CLASS-FUNCALLED */
Object eval_find_java_class_funcalled(java_class_name_as_text)
    Object java_class_name_as_text;
{
    Object top_of_stack, message_1, temp;

    x_note_fn_call(208,251);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(1,string_constant_79);
    raw_stack_error_named_error(top_of_stack,message_1);
    temp = reclaim_text_string(java_class_name_as_text);
    return VALUES_1(temp);
}

static Object string_constant_80;  /* "Could not find a network interface for ~NF" */

/* EVAL-NETWORK-INTERFACE-FOR-FUNCALLED */
Object eval_network_interface_for_funcalled(item)
    Object item;
{
    Object interface_qm, top_of_stack, message_1;

    x_note_fn_call(208,252);
    interface_qm = g2_lookup_network_interface_for_home(g2_item_home(item));
    if ( !TRUEP(interface_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_80,item);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(interface_qm);
}

/* EVAL-IN-THE-TRACKED-ITEM-SET-FUNCALLED */
Object eval_in_the_tracked_item_set_funcalled(item)
    Object item;
{
    x_note_fn_call(208,253);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)134217728L) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

static Object Qsystem_frame;       /* system-frame */

static Object Qattributes_permamently_changed;  /* attributes-permamently-changed */

/* ITEM-HAS-UNSAVED-CHANGES-P */
Object item_has_unsaved_changes_p(item)
    Object item;
{
    Object sub_class_bit_vector, gensymed_symbol_3, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,254);
    if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(item,
	    (SI_Long)4L)) & (SI_Long)1L)) {
	temp = TRUEP(superior_frame(item));
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(Qsystem_frame,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
			(SI_Long)18L));
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
	    if (temp) {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qserver_parameters,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 =  !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)16L)) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = get_lookup_slot_value_given_default(item,
		    Qattributes_permamently_changed,Nil);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* ITEM-HAS-UNSAVED-CHANGES-VISIBLE-IN-TABLES-P */
Object item_has_unsaved_changes_visible_in_tables_p(item)
    Object item;
{
    Object sub_class_bit_vector, gensymed_symbol_3, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,255);
    if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(item,
	    (SI_Long)4L)) & (SI_Long)1L)) {
	temp = TRUEP(superior_frame(item));
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(Qsystem_frame,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
			(SI_Long)18L));
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
	    if (temp) {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qserver_parameters,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 =  !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)16L)) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = item_has_unsaved_changes_visible_in_tables_p_1(item);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* ATTRIBUTE-MAY-BE-VISIBLE-IN-TABLES-P */
Object attribute_may_be_visible_in_tables_p(item,attribute)
    Object item, attribute;
{
    Object temp, slot_description_qm;

    x_note_fn_call(208,256);
    temp = CONSP(attribute) ? T : Nil;
    if (temp);
    else {
	slot_description_qm = 
		get_slot_description_of_class_description_function(attribute,
		ISVREF(item,(SI_Long)1L),Nil);
	if (slot_description_qm &&  
		!TRUEP(do_not_put_slot_in_attribute_tables_p(3,
		slot_description_qm,Nil,item))) {
	    temp = assq_function(Qtype,ISVREF(slot_description_qm,
		    (SI_Long)9L));
	    temp = SECOND(temp);
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* ITEM-HAS-UNSAVED-CHANGES-VISIBLE-IN-TABLES-P-1 */
Object item_has_unsaved_changes_visible_in_tables_p_1(item)
    Object item;
{
    Object attributes, temp, attribute, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(208,257);
    attributes = get_lookup_slot_value_given_default(item,
	    Qattributes_permamently_changed,Nil);
    temp =  !LISTP(attributes) ? T : Nil;
    if (temp);
    else {
	attribute = Nil;
	ab_loop_list_ = attributes;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = attribute_may_be_visible_in_tables_p(item,attribute);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* ITEM-HAS-UNSAVED-CHANGES-NOT-VISIBLE-IN-TABLES-P */
Object item_has_unsaved_changes_not_visible_in_tables_p(item)
    Object item;
{
    Object sub_class_bit_vector, gensymed_symbol_3, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(208,258);
    if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(item,
	    (SI_Long)4L)) & (SI_Long)1L)) {
	temp = TRUEP(superior_frame(item));
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(Qsystem_frame,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
			(SI_Long)18L));
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
	    if (temp) {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qserver_parameters,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 =  !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)16L)) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = item_has_unsaved_changes_not_visible_in_tables_p_1(item);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* ITEM-HAS-UNSAVED-CHANGES-NOT-VISIBLE-IN-TABLES-P-1 */
Object item_has_unsaved_changes_not_visible_in_tables_p_1(item)
    Object item;
{
    Object attributes, temp, attribute, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(208,259);
    attributes = get_lookup_slot_value_given_default(item,
	    Qattributes_permamently_changed,Nil);
    temp =  !LISTP(attributes) ? T : Nil;
    if (temp);
    else {
	attribute = Nil;
	ab_loop_list_ = attributes;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ =  !TRUEP(attribute_may_be_visible_in_tables_p(item,
		attribute)) ? T : Nil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* EVAL-WITH-UNSAVED-CHANGES-FUNCALLED */
Object eval_with_unsaved_changes_funcalled(item)
    Object item;
{
    x_note_fn_call(208,260);
    return VALUES_1(item_has_unsaved_changes_p(item) ? 
	    Evaluation_true_value : Evaluation_false_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Mark_for_modules_with_unsaved_changes, Qmark_for_modules_with_unsaved_changes);

Object Module_has_unsaved_changes_kbprop = UNBOUND;

static Object Qitem;               /* item */

/* MODULES-WITH-UNSAVED-CHANGES */
Object modules_with_unsaved_changes()
{
    Object mark_for_modules_with_unsaved_changes_new_value, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, item, temp_1, temp_2, suite;
    Object ab_loop_list_, module_information_instance, module_name;
    Object unsaved_changes_p, ab_loopvar__2;
    char temp;
    Declare_special(1);

    x_note_fn_call(208,261);
    mark_for_modules_with_unsaved_changes_new_value = 
	    FIXNUM_ADD1(Mark_for_modules_with_unsaved_changes);
    Mark_for_modules_with_unsaved_changes = 
	    mark_for_modules_with_unsaved_changes_new_value;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
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
      if (item_has_unsaved_changes_p(item)) {
	  temp_1 = ISVREF(item,(SI_Long)3L);
	  temp_2 = FIX((SI_Long)-1L);
	  temp =  !EQUAL(temp_1,temp_2);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  temp_2 = get_module_block_is_in(item);
	  mutate_kb_specific_property_value(temp_2,
		  Mark_for_modules_with_unsaved_changes,
		  Module_has_unsaved_changes_kbprop);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_information_instance = Nil;
    module_name = Nil;
    unsaved_changes_p = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_information_instance = FIRST(suite);
    module_name = ISVREF(module_information_instance,(SI_Long)23L);
    temp_2 = lookup_kb_specific_property_value(module_name,
	    Module_has_unsaved_changes_kbprop);
    unsaved_changes_p = EQL(temp_2,Mark_for_modules_with_unsaved_changes) ?
	     T : Nil;
    if (unsaved_changes_p) {
	ab_loopvar__2 = gensym_cons_1(module_name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_2;
  end_loop_2:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    return VALUES_1(temp_2);
}

static Object string_constant_81;  /* "~%" */

static Object string_constant_82;  /* "(Note that there are unsaved changes.)" */

static Object string_constant_83;  /* "(Note that the module~a ~L,& ~a unsaved changes.)" */

static Object string_constant_84;  /* "s" */

static Object string_constant_85;  /* "have" */

static Object string_constant_86;  /* "has" */

/* TWRITE-CHANGED-MODULES-NOTE */
Object twrite_changed_modules_note()
{
    Object module_list;

    x_note_fn_call(208,262);
    module_list = modules_with_unsaved_changes();
    if (module_list) {
	tformat(1,string_constant_81);
	if (memq_function(Nil,module_list))
	    tformat(1,string_constant_82);
	else
	    tformat(4,string_constant_83,CDR(module_list) ? 
		    string_constant_84 : string_constant_26,module_list,
		    CDR(module_list) ? string_constant_85 : 
		    string_constant_86);
	reclaim_gensym_list_1(module_list);
    }
    return VALUES_1(Nil);
}

static Object string_constant_87;  /* "~NF is divided by zero." */

/* DIVIDE-BY-ZERO-ERROR-MESSAGE */
Object divide_by_zero_error_message(item)
    Object item;
{
    x_note_fn_call(208,263);
    return tformat_stack_error_text_string(2,string_constant_87,item);
}

/* EVAL-DIV-LONG-FUNCALLED */
Object eval_div_long_funcalled(dividend,divisor)
    Object dividend, divisor;
{
    Object item, top_of_stack, temp;

    x_note_fn_call(208,264);
    if (FIXNUMP(dividend))
	dividend = make_evaluation_long(dividend);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(dividend) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(dividend)) == (SI_Long)1L)
	dividend = 
		make_evaluation_long(l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(dividend,
		(SI_Long)0L)),_));
    if (FIXNUMP(divisor))
	divisor = make_evaluation_long(divisor);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(divisor) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(divisor)) == (SI_Long)1L)
	divisor = 
		make_evaluation_long(l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(divisor,
		(SI_Long)0L)),_));
    if (zerop(aref1(divisor,FIX((SI_Long)0L)))) {
	item = aref1(divisor,FIX((SI_Long)0L));
	top_of_stack = Cached_top_of_stack;
	temp = raw_stack_error_named_error(top_of_stack,
		divide_by_zero_error_message(item));
    }
    else
	temp = div_long(dividend,divisor);
    reclaim_managed_simple_long_array_of_length_1(divisor);
    return VALUES_1(temp);
}

/* EVAL-KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-FUNCALLED */
Object eval_kbf_g2nke_count_history_matching_op_funcalled(arg_subj,arg_n,
	    arg_nstart,arg_fellow_val,arg_requiredgoodsize,arg_compareoperator)
    Object arg_subj, arg_n, arg_nstart, arg_fellow_val, arg_requiredgoodsize;
    Object arg_compareoperator;
{
    Object temp;

    x_note_fn_call(208,265);
    temp = kb_g2nke_count_history_matching_op(arg_subj,arg_n,arg_nstart,
	    arg_fellow_val,arg_requiredgoodsize,arg_compareoperator);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_subj, Qcached_subj);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_n, Qcached_n);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_nstart, Qcached_nstart);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_fellow_val, Qcached_fellow_val);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_eventflag, Qcached_eventflag);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_event_bit, Qcached_event_bit);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_requiredgoodsize, Qcached_requiredgoodsize);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_compareoperator, Qcached_compareoperator);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_result, Qcached_result);

/* EVAL-KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG-FUNCALLED */
Object eval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled(arg_subj,
	    arg_n,arg_nstart,arg_fellow_val,arg_eventflag,arg_event_bit,
	    arg_requiredgoodsize,arg_compareoperator)
    Object arg_subj, arg_n, arg_nstart, arg_fellow_val, arg_eventflag;
    Object arg_event_bit, arg_requiredgoodsize, arg_compareoperator;
{
    Object temp;

    x_note_fn_call(208,266);
    if (EQ(Cached_subj,arg_subj) && EQ(Cached_n,arg_n) && EQ(Cached_nstart,
	    arg_nstart) && EQ(Cached_fellow_val,arg_fellow_val) && 
	    EQ(Cached_eventflag,arg_eventflag) && EQ(Cached_event_bit,
	    arg_event_bit) && EQ(Cached_requiredgoodsize,
	    arg_requiredgoodsize) && EQ(Cached_compareoperator,
	    arg_compareoperator))
	temp = copy_managed_float(Cached_result);
    else {
	Cached_subj = arg_subj;
	Cached_n = arg_n;
	Cached_nstart = arg_nstart;
	Cached_fellow_val = arg_fellow_val;
	Cached_eventflag = arg_eventflag;
	Cached_event_bit = arg_event_bit;
	Cached_requiredgoodsize = arg_requiredgoodsize;
	Cached_compareoperator = arg_compareoperator;
	Cached_result = 
		kb_g2nke_count_history_matching_op_and_eventflag(arg_subj,
		arg_n,arg_nstart,arg_fellow_val,arg_eventflag,
		arg_event_bit,arg_requiredgoodsize,arg_compareoperator);
	temp = copy_managed_float(Cached_result);
    }
    return VALUES_1(temp);
}

/* EVAL-VECTOR-ADD-FUNCALLED */
Object eval_vector_add_funcalled(array1,array2,array3)
    Object array1, array2, array3;
{
    x_note_fn_call(208,267);
    g2_vector_add(array1,array2,array3,FIX((SI_Long)0L));
    return VALUES_1(array3);
}

/* EVAL-VECTOR-MULTIPLY-FUNCALLED */
Object eval_vector_multiply_funcalled(array1,array2)
    Object array1, array2;
{
    Object temp;

    x_note_fn_call(208,268);
    temp = g2_array_multiply(array1,array2);
    return VALUES_1(temp);
}

/* EVAL-VECTOR-SCALAR-MULTIPLY-FUNCALLED */
Object eval_vector_scalar_multiply_funcalled(array1,x,array2)
    Object array1, x, array2;
{
    x_note_fn_call(208,269);
    g2_scalar_multiply(array1,array2,x);
    return VALUES_1(array2);
}

/* EVAL-IS-RESIZED-BY-THE-USER-FUNCALLED */
Object eval_is_resized_by_the_user_funcalled(item)
    Object item;
{
    x_note_fn_call(208,270);
    return VALUES_1(Evaluation_true_value);
}

void stack_eval2_INIT()
{
    Object there_exists_literal_stack_node_converter_1;
    Object there_exists_literal_i_chooser_1, there_exists_literal_i_emit_1;
    Object for_every_literal_stack_node_converter_1;
    Object for_every_literal_i_chooser_1, for_every_literal_i_emit_1;
    Object exists_stack_node_converter_1, exists_i_chooser_1, exists_i_emit_1;
    Object sum_stack_node_converter_1, sum_i_chooser_1, sum_i_emit_1;
    Object product_stack_node_converter_1, product_i_chooser_1;
    Object product_i_emit_1, count_stack_node_converter_1, count_i_chooser_1;
    Object count_i_emit_1, aggregated_average_stack_node_converter_1;
    Object aggregated_average_i_chooser_1, aggregated_average_i_emit_1;
    Object maximum_stack_node_converter_1, maximum_i_chooser_1;
    Object maximum_i_emit_1, minimum_stack_node_converter_1;
    Object minimum_i_chooser_1, minimum_i_emit_1;
    Object collection_time_of_stack_node_converter_1;
    Object collection_time_of_i_chooser_1, collection_time_of_i_emit_1;
    Object collection_time_of_previous_datapoint_stack_node_converter_1;
    Object collection_time_of_previous_datapoint_i_chooser_1;
    Object collection_time_of_previous_datapoint_i_emit_1;
    Object expiration_time_of_stack_node_converter_1;
    Object expiration_time_of_i_chooser_1, expiration_time_of_i_emit_1;
    Object g2_list_or_sequence_member_p_stack_node_converter_1;
    Object g2_list_or_sequence_member_p_i_chooser_1;
    Object g2_list_or_sequence_member_p_i_emit_1;
    Object next_list_element_stack_node_converter_1;
    Object next_list_element_i_chooser_1, next_list_element_i_emit_1;
    Object average_stack_node_converter_1;
    Object float_contagion_stack_operators_new_value;
    Object max_stack_node_converter_1, min_stack_node_converter_1;
    Object var_spot_stack_node_converter_1, identity_stack_node_converter_1;
    Object attribute_value_stack_node_converter_1, attribute_value_i_chooser_1;
    Object attribute_value_i_emit_1, call_procedure_stack_node_converter_1;
    Object call_function_stack_node_converter_1;
    Object is_of_class_stack_node_converter_1, sequence_stack_node_converter_1;
    Object sequence_i_chooser_1, sequence_i_emit_1;
    Object evaluated_structure_stack_node_converter_1;
    Object evaluated_structure_i_chooser_1, evaluated_structure_i_emit_1;
    Object concatenate_stack_node_converter_1, concatenate_i_chooser_1;
    Object concatenate_i_emit_1, change_attribute_stack_node_converter_1;
    Object remove_attribute_stack_node_converter_1;
    Object Qeval_is_resized_by_the_user_funcalled, list_constant_22;
    Object list_constant_55, Qis_resized_by_the_user, AB_package;
    Object Qvector_scalar_multiply, Qeval_vector_scalar_multiply_funcalled;
    Object list_constant_101, list_constant_105, Qall, list_constant_104;
    Object Qvector_multiply, Qeval_vector_multiply_funcalled;
    Object list_constant_103, Qvector_add, Qeval_vector_add_funcalled;
    Object list_constant_102, Qquantity_array;
    Object Qkbf_g2nke_count_history_matching_op_and_eventflag;
    Object Qeval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled;
    Object list_constant_100, list_constant_81, list_constant_98;
    Object Qkbf_g2nke_count_history_matching_op;
    Object Qeval_kbf_g2nke_count_history_matching_op_funcalled;
    Object list_constant_99, list_constant_28, Qquantitative_parameter;
    Object Qdiv_long, Qeval_div_long_funcalled, list_constant_27;
    Object Qmodule_has_unsaved_changes;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qeval_with_unsaved_changes_funcalled, list_constant_71;
    Object Qwith_unsaved_changes, Qeval_in_the_tracked_item_set_funcalled;
    Object Qpprint_functional_evaluator, Qin_the_tracked_item_set;
    Object Qeval_network_interface_for_funcalled, list_constant_97;
    Object Qnetwork_interface_for, Qnetwork_interface;
    Object Qeval_find_java_class_funcalled, list_constant_33, list_constant_96;
    Object Qfind_java_class, Qprocedure;
    Object Qeval_remove_evaluated_attribute_funcalled, list_constant_95;
    Object list_constant_19, list_constant_67, Qstack_special_form_converter;
    Object Qremove_attribute, Qeval_change_evaluated_attribute_funcalled;
    Object list_constant_94, list_constant_54, Qchange_attribute;
    Object Qeval_portion_funcalled, list_constant_93, Qportion;
    Object Qfuncall_concatenate_inst, Qpprint_concatenate_instruction;
    Object list_constant_83, list_constant_17, Qstack_node_instruction_emitter;
    Object Qpreferred_instruction_chooser, Qeval_change_element_funcalled;
    Object list_constant_92, Qchange_element;
    Object Qeval_insert_after_element_funcalled, Qinsert_after_element;
    Object Qeval_insert_before_element_funcalled, Qinsert_before_element;
    Object Qeval_insert_after_funcalled, list_constant_91, Qinsert_after;
    Object Qeval_insert_before_funcalled, Qinsert_before;
    Object Qeval_insert_at_end_funcalled, list_constant_90, Qinsert_at_end;
    Object Qeval_insert_at_beginning_funcalled, Qinsert_at_beginning;
    Object Qeval_remove_funcalled, list_constant_89, list_constant_24;
    Object Qeval_transform_text_for_g2_4_dot_0_comparison_funcalled, Qtext;
    Object list_constant_88, Qtransform_text_for_g2_4_dot_0_comparison;
    Object Qeval_transform_text_for_unicode_comparison_funcalled;
    Object Qtransform_text_for_unicode_comparison, list_constant_31;
    Object Qeval_export_text_funcalled, list_constant_87, Qexport_text;
    Object Qeval_import_text_funcalled, Qimport_text, list_constant_86;
    Object Qtext_conversion_style, Qeval_compare_text_funcalled;
    Object list_constant_32, Qcompare_text;
    Object Qeval_readable_symbol_text_funcalled, Qreadable_symbol_text;
    Object Qeval_readable_text_funcalled, Qreadable_text;
    Object Qeval_readable_text_for_value_funcalled, list_constant_85;
    Object Qreadable_text_for_value;
    Object Qeval_is_readable_digit_in_radix_funcalled;
    Object Qis_readable_digit_in_radix, Qeval_is_readable_digit_funcalled;
    Object Qis_readable_digit, Qeval_is_digit_funcalled, Qis_digit;
    Object Qeval_to_lowercase_funcalled, Qto_lowercase;
    Object Qeval_to_titlecase_funcalled, Qto_titlecase;
    Object Qeval_to_uppercase_funcalled, Qto_uppercase;
    Object Qeval_is_lowercase_funcalled, Qis_lowercase;
    Object Qeval_is_titlecase_funcalled, Qis_titlecase;
    Object Qeval_is_uppercase_funcalled, Qis_uppercase;
    Object Qeval_text_to_character_codes_funcalled, Qtext_to_character_codes;
    Object Qeval_character_codes_to_text_funcalled, list_constant_84;
    Object Qcharacter_codes_to_text, Qfuncall_make_evaluated_structure_inst;
    Object Qpprint_make_evaluated_structure_instruction;
    Object Qfuncall_make_evaluation_sequence_inst;
    Object Qpprint_make_evaluation_sequence_instruction, list_constant_82;
    Object Qfuncall_class_qualified_name_frame_or_place_reference_inst;
    Object Qpprint_cqn_frame_or_place_reference_instruction;
    Object Qclass_qualified_name_frame_or_place_reference;
    Object Qeval_rgb_symbol_funcalled, Qeval_great_circle_distance_funcalled;
    Object list_constant_80, list_constant_26, Qbitwise_set;
    Object Qeval_bitwise_set_funcalled, Qbitwise_test;
    Object Qeval_bitwise_test_funcalled, Qbitwise_left_shift;
    Object Qeval_bitwise_left_shift_funcalled, Qbitwise_right_shift;
    Object Qeval_bitwise_right_shift_funcalled, Qbitwise_xor;
    Object Qeval_bitwise_xor_funcalled, Qbitwise_not;
    Object Qeval_bitwise_not_funcalled, Qbitwise_or, Qeval_bitwise_or_in_line;
    Object Qbitwise_and, Qeval_bitwise_and_in_line;
    Object Qfuncall_coerce_no_item_to_unknown_inst, Qcoerce_no_item_to_unknown;
    Object Qeval_with_changes_logged_2_funcalled, list_constant_79;
    Object Qwith_changes_logged_2, list_constant_78, list_constant_77;
    Object list_constant_21, Qab_or, list_constant_76;
    Object Qeval_assigned_to_module_funcalled, list_constant_75;
    Object Qassigned_to_module;
    Object Qeval_g2_inspect_internal_name_for_debugging_p_funcalled;
    Object list_constant_74, Qg2_inspect_internal_name_for_debugging_p;
    Object Qeval_containing_symbol_funcalled, Qcontaining_symbol;
    Object Qeval_containing_word_funcalled, Qcontaining_word;
    Object Qeval_containing_funcalled, Qcontaining, list_constant_50;
    Object Qeval_with_notes_funcalled, Qwith_notes;
    Object Qeval_with_status_funcalled, list_constant_73, Qwith_status;
    Object Qeval_in_the_category_funcalled, list_constant_72, Qin_the_category;
    Object Qeval_which_has_the_focal_class_funcalled;
    Object Qwhich_has_the_focal_class;
    Object Qeval_which_has_the_focal_object_funcalled;
    Object Qwhich_has_the_focal_object, list_constant_70, Qrule, Qprocedures;
    Object Qinference, Qitems_are_connected_at_ports;
    Object Qeval_items_are_connected_at_ports_funcalled, list_constant_69;
    Object Qitems_are_connected_with_direction;
    Object Qeval_items_are_connected_with_direction_funcalled;
    Object list_constant_68, Qitems_are_connected;
    Object Qeval_items_are_connected_funcalled, list_constant_59;
    Object Qconnection_style, Qeval_connection_style_funcalled;
    Object list_constant_66, list_constant_60, Qconnection_direction;
    Object Qeval_connection_direction_funcalled, list_constant_65;
    Object Qconnection_position, Qeval_connection_position_funcalled;
    Object Qconnection_side, Qeval_connection_side_funcalled, Qright, Qbottom;
    Object Qleft, Qtop, Qconnection_portname;
    Object Qeval_connection_portname_funcalled, Qeval_has_a_name_funcalled;
    Object Qpprint_has_a_name_evaluator, Qhas_a_name;
    Object Qeval_is_active_funcalled, Qpprint_is_active_evaluator, Qis_active;
    Object Qeval_is_of_class_funcalled, Qpprint_is_of_class_evaluator;
    Object list_constant_64, Qis_of_class;
    Object Qeval_nupec_synchronization_occurs_funcalled;
    Object Qnupec_synchronization_occurs;
    Object Qeval_indirectly_disconnected_from_funcalled;
    Object Qindirectly_disconnected_from;
    Object Qeval_indirectly_connected_to_funcalled, Qindirectly_connected_to;
    Object Qeval_directly_disconnected_from_funcalled, list_constant_63;
    Object Qdirectly_disconnected_from, list_constant_61;
    Object Qeval_directly_connected_to_funcalled, list_constant_62;
    Object Qdirectly_connected_to;
    Object Qeval_generic_directly_disconnected_from_funcalled;
    Object Qgeneric_directly_disconnected_from;
    Object Qeval_generic_directly_connected_to_funcalled;
    Object Qgeneric_directly_connected_to, Qconnection;
    Object Qeval_generic_ceases_to_be_related_funcalled;
    Object Qgeneric_ceases_to_be_related;
    Object Qeval_generic_becomes_related_funcalled, Qgeneric_becomes_related;
    Object Qeval_generic_event_funcalled, list_constant_58, Qgeneric_event;
    Object Qeval_is_created_funcalled, Qis_created;
    Object Qeval_loses_its_value_funcalled, list_constant_57, Qloses_its_value;
    Object Qeval_is_disabled_funcalled, Qis_disabled;
    Object Qeval_is_enabled_funcalled, Qis_enabled;
    Object Qeval_is_deactivated_funcalled, Qis_deactivated;
    Object Qeval_is_activated_funcalled, Qis_activated;
    Object Qeval_ceases_to_be_related_funcalled, list_constant_53;
    Object Qceases_to_be_related, Qeval_becomes_related_funcalled;
    Object Qbecomes_related, Qeval_is_moved_by_g2_funcalled, Qis_moved_by_g2;
    Object Qeval_is_moved_by_the_user_funcalled, Qis_moved_by_the_user;
    Object Qeval_is_moved_funcalled, Qis_moved;
    Object Qeval_fails_to_receive_a_value_funcalled, Qfails_to_receive_a_value;
    Object Qeval_receives_a_value_funcalled, list_constant_56;
    Object Qreceives_a_value, Qobject, Qeval_false_funcalled;
    Object Qpprint_false_evaluator, Qfalse, Qvar_spot;
    Object Qeval_is_not_related_funcalled, Qpprint_is_not_related_evaluator;
    Object Qis_not_related, Qeval_is_related_funcalled;
    Object Qpprint_is_related_evaluator, Qis_related, Qeval_time_funcalled;
    Object list_constant_52, Qeval_second_funcalled, list_constant_23;
    Object Qeval_minute_funcalled, Qeval_hour_funcalled;
    Object Qeval_day_of_the_week_funcalled, list_constant_51, Qsunday;
    Object Qsaturday, Qfriday, Qthursday, Qwednesday, Qtuesday, Qmonday;
    Object Qeval_day_of_the_month_funcalled, Qeval_month_funcalled;
    Object Qeval_year_funcalled, Qeval_text_to_symbol_funcalled;
    Object Qeval_symbol_text_funcalled, Qsymbol_text;
    Object Qeval_symbol_datum_funcalled, Qsymbol_datum, list_constant_49;
    Object Qeval_quantity_text_funcalled, Qquantity_text;
    Object Qeval_quantity_quantity_funcalled, Qquantity_quantity;
    Object Qeval_quantity_truth_value_funcalled, Qquantity_truth_value;
    Object Qeval_quantity_datum_in_line, list_constant_48, Qquantity_datum;
    Object list_constant_47, Qeval_lexeme_funcalled, list_constant_46, Qlexeme;
    Object list_constant_45, Qeval_get_next_token_4_funcalled;
    Object list_constant_44, Qget_next_token_4, list_constant_41;
    Object Qeval_get_next_token_3_funcalled, list_constant_43;
    Object Qget_next_token_3, list_constant_42, Qtokenizer;
    Object Qeval_find_and_replace_pattern_6_funcalled, list_constant_40;
    Object Qfind_and_replace_pattern_6, list_constant_39;
    Object Qeval_find_next_substring_matching_pattern_4_funcalled;
    Object list_constant_38, Qfind_next_substring_matching_pattern_4;
    Object Qeval_find_next_pattern_4_funcalled, Qfind_next_pattern_4;
    Object Qeval_find_and_replace_pattern_5_funcalled, list_constant_37;
    Object Qfind_and_replace_pattern_5, list_constant_36;
    Object Qeval_find_next_substring_matching_pattern_3_funcalled;
    Object list_constant_34, Qfind_next_substring_matching_pattern_3;
    Object Qeval_find_next_pattern_3_funcalled, Qfind_next_pattern_3;
    Object Qab_structure, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qeval_replace_in_text_funcalled, list_constant_35;
    Object Qeval_get_from_text_funcalled, Qeval_omit_from_text_funcalled;
    Object Qeval_insert_in_text_funcalled, Qeval_capitalize_words_funcalled;
    Object Qcapitalize_words, Qeval_lower_case_text_funcalled;
    Object Qlower_case_text, Qeval_upper_case_text_funcalled, Qupper_case_text;
    Object Qeval_text_begins_with_quantity_funcalled;
    Object Qtext_begins_with_quantity, Qeval_position_of_text_funcalled;
    Object Qposition_of_text, Qeval_length_of_text_funcalled, Qlength_of_text;
    Object Qeval_is_contained_in_text_funcalled, Qis_contained_in_text;
    Object Qeval_truth_value_float_funcalled, list_constant_25;
    Object Qtruth_value_float, Qeval_truth_value_integer_funcalled;
    Object Qtruth_value_integer, Qeval_truth_value_quantity_funcalled;
    Object Qtruth_value_quantity, Qeval_truth_value_of_truth_value_funcalled;
    Object Qtruth_value_of_truth_value, Qeval_truth_value_datum_in_line;
    Object list_constant_30, Qtruth_value_datum, list_constant_29;
    Object Qeval_truncate_float_in_line, Qtruncate_float;
    Object Qeval_tan_float_in_line, Qtan_float, Qeval_sqrt_float_in_line;
    Object Qsqrt_float, Qeval_sin_float_in_line, Qsin_float;
    Object Qeval_round_float_in_line, Qround_float;
    Object Qeval_round_quantity_in_line, Qround_quantity;
    Object Qeval_remainder_float_in_line, Qremainder_float, Qremainder;
    Object Qeval_remainder_integer_in_line, Qremainder_integer;
    Object Qeval_remainder_quantity_in_line, Qremainder_quantity;
    Object Qeval_random_float_2_in_line, Qrandom_float_2;
    Object Qeval_random_integer_2_in_line, Qrandom_integer_2;
    Object Qeval_random_quantity_2_in_line, Qrandom_quantity_2;
    Object Qeval_random_float_in_line, Qrandom_float;
    Object Qeval_random_integer_in_line, Qrandom_integer;
    Object Qeval_random_quantity_in_line, Qrandom_quantity;
    Object Qeval_quotient_float_in_line, Qquotient_float;
    Object Qeval_quotient_integer_in_line, Qquotient_integer;
    Object Qeval_quotient_quantity_in_line, Qquotient_quantity;
    Object Qeval_min_float_in_line, Qmin_float, Qeval_min_integer_in_line;
    Object Qmin_integer, Qeval_min_quantity_in_line, Qmin_quantity;
    Object Qeval_max_float_in_line, Qmax_float, Qeval_max_integer_in_line;
    Object Qmax_integer, Qeval_max_quantity_in_line, Qmax_quantity;
    Object Qeval_log_float_in_line, Qlog_float, Qeval_ln_float_in_line;
    Object Qln_float, Qln, Qeval_floor_float_in_line, Qfloor_float;
    Object Qeval_floor_quantity_in_line, Qfloor_quantity;
    Object Qeval_expt_float_in_line, Qexpt_float, Qeval_expt_quantity_in_line;
    Object Qexpt_quantity, Qeval_exp_float_in_line, Qexp_float;
    Object Qeval_cos_float_in_line, Qcos_float, Qeval_ceiling_float_in_line;
    Object Qceiling_float, Qeval_ceiling_quantity_in_line, Qceiling_quantity;
    Object Qaverage, Qeval_arctan_2_in_line, Qarctan_2, Qarctan;
    Object Qeval_arctan_1_in_line, Qarctan_1, Qeval_abs_float_in_line;
    Object Qabs_float, Qeval_abs_integer_in_line, Qabs_integer;
    Object Qeval_abs_quantity_in_line, Qabs_quantity;
    Object Qpprint_attribute_name_evaluator, Qeval_attribute_name_in_line;
    Object Qattribute_name, Qexpiration_source_operator_p;
    Object Qpprint_g2_list_or_sequence_length_evaluator;
    Object Qeval_g2_list_or_sequence_length_in_line, list_constant_20;
    Object Qg2_list_or_sequence_length;
    Object Qfuncall_g2_list_or_sequence_member_p_inst;
    Object Qpprint_g2_list_or_sequence_member_p_instruction, Qg2_list;
    Object Qfuncall_expiration_time_of_inst;
    Object Qpprint_expiration_time_of_instruction;
    Object Qfuncall_collection_time_of_previous_datapoint_inst;
    Object Qpprint_collection_time_of_previous_datapoint_instruction;
    Object Qfuncall_collection_time_of_inst;
    Object Qpprint_collection_time_of_instruction, Qvariable_or_parameter;
    Object Qeval_current_system_real_time_funcalled, Qcurrent_system_real_time;
    Object Qeval_current_subsecond_real_time_funcalled;
    Object Qcurrent_subsecond_real_time, Qpprint_current_real_time_evaluator;
    Object Qeval_current_real_time_in_line;
    Object Qeval_current_system_time_funcalled, Qcurrent_system_time;
    Object Qeval_current_subsecond_time_funcalled, Qcurrent_subsecond_time;
    Object Qpprint_current_time_evaluator, Qeval_current_time_in_line;
    Object Qcurrent_time, Qexpiration_special_form_operator_p;
    Object list_constant_18, Qaggregated_average, Qfuncall_exists_inst;
    Object Qpprint_exists_instruction, Qfor_every_literal;
    Object Qno_item_implies_unknown, Qno_item, Qunknown_datum;

    x_note_fn_call(208,271);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qstack_special_form_converter = 
	    STATIC_SYMBOL("STACK-SPECIAL-FORM-CONVERTER",AB_package);
    string_constant = STATIC_STRING("there exists parse converter");
    string_constant_1 = 
	    string_append2(STATIC_STRING("The iteration reference in ~NE cannot be compiled, since there is ~\n            no local name or class name in the designation which can be used ~\n            for later refere"),
	    STATIC_STRING("nce."));
    string_constant_2 = 
	    STATIC_STRING("The iteration reference in ~NE could not be compiled because no ~\n            type can be deduced from the reference.");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    string_constant_3 = 
	    STATIC_STRING("Type mismatch between the local name ~A and the type ~\n                       ~NT referenced by the THERE EXISTS form iteration.");
    Qindexed_attribute = STATIC_SYMBOL("INDEXED-ATTRIBUTE",AB_package);
    there_exists_literal_stack_node_converter_1 = 
	    STATIC_FUNCTION(there_exists_literal_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qthere_exists_literal,
	    there_exists_literal_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qpreferred_instruction_chooser = 
	    STATIC_SYMBOL("PREFERRED-INSTRUCTION-CHOOSER",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    there_exists_literal_i_chooser_1 = 
	    STATIC_FUNCTION(there_exists_literal_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qthere_exists_literal,
	    there_exists_literal_i_chooser_1,Qpreferred_instruction_chooser);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant = STATIC_CONS(Qunknown_datum,Qnil);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_1 = STATIC_CONS(Qno_item,Qnil);
    Qno_item_implies_unknown = STATIC_SYMBOL("NO-ITEM-IMPLIES-UNKNOWN",
	    AB_package);
    list_constant_2 = STATIC_CONS(Qno_item_implies_unknown,Qnil);
    Qrequired_domain_types_of_role = 
	    STATIC_SYMBOL("REQUIRED-DOMAIN-TYPES-OF-ROLE",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    string_constant_4 = 
	    STATIC_STRING(" requires ~a arguments, but instead received ~a");
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qexpiration_special_form_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SPECIAL-FORM-OPERATOR-P",AB_package);
    mutate_global_property(Qthere_exists_literal,T,
	    Qexpiration_special_form_operator_p);
    Qstack_node_instruction_emitter = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EMITTER",AB_package);
    Qpush_constant = STATIC_SYMBOL("PUSH-CONSTANT",AB_package);
    there_exists_literal_i_emit_1 = 
	    STATIC_FUNCTION(there_exists_literal_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qthere_exists_literal,
	    there_exists_literal_i_emit_1,Qstack_node_instruction_emitter);
    Qfor_every_literal = STATIC_SYMBOL("FOR-EVERY-LITERAL",AB_package);
    for_every_literal_stack_node_converter_1 = 
	    STATIC_FUNCTION(for_every_literal_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qfor_every_literal,
	    for_every_literal_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_5 = STATIC_STRING("aggregator parse converter");
    string_constant_6 = 
	    string_append2(STATIC_STRING("The iteration reference in ~NE cannot be compiled, since there is ~\n            no local name or class name in the designation which can be used ~\n            as a binding ref"),
	    STATIC_STRING("erence."));
    for_every_literal_i_chooser_1 = 
	    STATIC_FUNCTION(for_every_literal_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qfor_every_literal,
	    for_every_literal_i_chooser_1,Qpreferred_instruction_chooser);
    mutate_global_property(Qfor_every_literal,T,
	    Qexpiration_special_form_operator_p);
    for_every_literal_i_emit_1 = STATIC_FUNCTION(for_every_literal_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qfor_every_literal,for_every_literal_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qexists = STATIC_SYMBOL("EXISTS",AB_package);
    exists_stack_node_converter_1 = 
	    STATIC_FUNCTION(exists_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qexists,exists_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_1);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_or,Qboolean,list_constant);
    exists_i_chooser_1 = STATIC_FUNCTION(exists_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qexists,exists_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qexists,T,Qexpiration_special_form_operator_p);
    exists_i_emit_1 = STATIC_FUNCTION(exists_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qexists,exists_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qall = STATIC_SYMBOL("ALL",AB_package);
    Qfuncall_exists_inst = STATIC_SYMBOL("FUNCALL-EXISTS-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_exists_inst,
	    STATIC_FUNCTION(funcall_exists_inst,NIL,FALSE,2,2));
    Qpprint_exists_instruction = STATIC_SYMBOL("PPRINT-EXISTS-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_exists_instruction,
	    STATIC_FUNCTION(pprint_exists_instruction,NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qexists,
	    FIX((SI_Long)37L),Qall,FIX((SI_Long)1L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_exists_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_exists_instruction),Qfuncall_exists_inst);
    Qsum = STATIC_SYMBOL("SUM",AB_package);
    Qproduct = STATIC_SYMBOL("PRODUCT",AB_package);
    string_constant_7 = STATIC_STRING("aggregator emitter");
    string_constant_8 = STATIC_STRING("Missing accumular operator type.");
    float_constant = STATIC_FLOAT(0.0);
    float_constant_1 = STATIC_FLOAT(1.0);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    string_constant_9 = STATIC_STRING("max or min aggregator emitter");
    string_constant_10 = 
	    STATIC_STRING("The maximum over an empty set of values has no value.  This was not an expected result.");
    string_constant_11 = 
	    STATIC_STRING("The minimum over an empty set of values has no value.  This was not an expected result.");
    string_constant_12 = 
	    STATIC_STRING("The average over an empty set of values has no value.  This was not an expected result.");
    sum_stack_node_converter_1 = STATIC_FUNCTION(sum_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qsum,sum_stack_node_converter_1,
	    Qstack_special_form_converter);
    sum_i_chooser_1 = STATIC_FUNCTION(sum_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qsum,sum_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qsum,T,Qexpiration_special_form_operator_p);
    sum_i_emit_1 = STATIC_FUNCTION(sum_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qsum,sum_i_emit_1,Qstack_node_instruction_emitter);
    product_stack_node_converter_1 = 
	    STATIC_FUNCTION(product_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qproduct,product_stack_node_converter_1,
	    Qstack_special_form_converter);
    product_i_chooser_1 = STATIC_FUNCTION(product_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qproduct,product_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qproduct,T,Qexpiration_special_form_operator_p);
    product_i_emit_1 = STATIC_FUNCTION(product_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qproduct,product_i_emit_1,
	    Qstack_node_instruction_emitter);
    count_stack_node_converter_1 = 
	    STATIC_FUNCTION(count_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qcount,count_stack_node_converter_1,
	    Qstack_special_form_converter);
    count_i_chooser_1 = STATIC_FUNCTION(count_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qcount,count_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qcount,T,Qexpiration_special_form_operator_p);
    count_i_emit_1 = STATIC_FUNCTION(count_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qcount,count_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qaggregated_average = STATIC_SYMBOL("AGGREGATED-AVERAGE",AB_package);
    aggregated_average_stack_node_converter_1 = 
	    STATIC_FUNCTION(aggregated_average_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qaggregated_average,
	    aggregated_average_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_18 = STATIC_CONS(list_constant_1,Qnil);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qfloat,
	    list_constant_18);
    aggregated_average_i_chooser_1 = 
	    STATIC_FUNCTION(aggregated_average_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qaggregated_average,
	    aggregated_average_i_chooser_1,Qpreferred_instruction_chooser);
    mutate_global_property(Qaggregated_average,T,
	    Qexpiration_special_form_operator_p);
    aggregated_average_i_emit_1 = 
	    STATIC_FUNCTION(aggregated_average_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qaggregated_average,aggregated_average_i_emit_1,
	    Qstack_node_instruction_emitter);
    maximum_stack_node_converter_1 = 
	    STATIC_FUNCTION(maximum_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qmaximum,maximum_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_18);
    maximum_i_chooser_1 = STATIC_FUNCTION(maximum_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qmaximum,maximum_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qmaximum,T,Qexpiration_special_form_operator_p);
    maximum_i_emit_1 = STATIC_FUNCTION(maximum_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qmaximum,maximum_i_emit_1,
	    Qstack_node_instruction_emitter);
    minimum_stack_node_converter_1 = 
	    STATIC_FUNCTION(minimum_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qminimum,minimum_stack_node_converter_1,
	    Qstack_special_form_converter);
    minimum_i_chooser_1 = STATIC_FUNCTION(minimum_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qminimum,minimum_i_chooser_1,
	    Qpreferred_instruction_chooser);
    mutate_global_property(Qminimum,T,Qexpiration_special_form_operator_p);
    minimum_i_emit_1 = STATIC_FUNCTION(minimum_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qminimum,minimum_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qcurrent_time = STATIC_SYMBOL("CURRENT-TIME",AB_package);
    Qeval_current_time_in_line = STATIC_SYMBOL("EVAL-CURRENT-TIME-IN-LINE",
	    AB_package);
    Qpprint_current_time_evaluator = 
	    STATIC_SYMBOL("PPRINT-CURRENT-TIME-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_current_time_evaluator,
	    STATIC_FUNCTION(pprint_current_time_evaluator,NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qcurrent_time,
	    Qcurrent_time,FIX((SI_Long)1L),Qall,Qnil,Qinteger,Nil,
	    Qeval_current_time_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)56L),Nil,
	    SYMBOL_FUNCTION(Qpprint_current_time_evaluator),Nil),
	    FIX((SI_Long)56L));
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qsimulated_value = STATIC_SYMBOL("SIMULATED-VALUE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qcurrent_subsecond_time = STATIC_SYMBOL("CURRENT-SUBSECOND-TIME",
	    AB_package);
    Qeval_current_subsecond_time_funcalled = 
	    STATIC_SYMBOL("EVAL-CURRENT-SUBSECOND-TIME-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_current_subsecond_time_funcalled,
	    STATIC_FUNCTION(eval_current_subsecond_time_funcalled,NIL,
	    FALSE,0,0));
    register_funcalled_evaluator(make_evaluator_description(Qcurrent_subsecond_time,
	    Qcurrent_subsecond_time,FIX((SI_Long)1L),Qall,Qnil,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_current_subsecond_time_funcalled),Nil,
	    FIX((SI_Long)95L),Nil,Nil,
	    Qeval_current_subsecond_time_funcalled),FIX((SI_Long)95L),
	    Funcall_eval_type_0_arg);
    Qcurrent_system_time = STATIC_SYMBOL("CURRENT-SYSTEM-TIME",AB_package);
    Qeval_current_system_time_funcalled = 
	    STATIC_SYMBOL("EVAL-CURRENT-SYSTEM-TIME-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_current_system_time_funcalled,
	    STATIC_FUNCTION(eval_current_system_time_funcalled,NIL,FALSE,0,0));
    register_funcalled_evaluator(make_evaluator_description(Qcurrent_system_time,
	    Qcurrent_system_time,FIX((SI_Long)1L),Qall,Qnil,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_current_system_time_funcalled),Nil,
	    FIX((SI_Long)141L),Nil,Nil,
	    Qeval_current_system_time_funcalled),FIX((SI_Long)141L),
	    Funcall_eval_type_0_arg);
    Qcurrent_real_time = STATIC_SYMBOL("CURRENT-REAL-TIME",AB_package);
    Qeval_current_real_time_in_line = 
	    STATIC_SYMBOL("EVAL-CURRENT-REAL-TIME-IN-LINE",AB_package);
    Qpprint_current_real_time_evaluator = 
	    STATIC_SYMBOL("PPRINT-CURRENT-REAL-TIME-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_current_real_time_evaluator,
	    STATIC_FUNCTION(pprint_current_real_time_evaluator,NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qcurrent_real_time,
	    Qcurrent_real_time,FIX((SI_Long)1L),Qall,Qnil,Qinteger,Nil,
	    Qeval_current_real_time_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)57L),Nil,
	    SYMBOL_FUNCTION(Qpprint_current_real_time_evaluator),Nil),
	    FIX((SI_Long)57L));
    Qcurrent_subsecond_real_time = 
	    STATIC_SYMBOL("CURRENT-SUBSECOND-REAL-TIME",AB_package);
    Qeval_current_subsecond_real_time_funcalled = 
	    STATIC_SYMBOL("EVAL-CURRENT-SUBSECOND-REAL-TIME-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_current_subsecond_real_time_funcalled,
	    STATIC_FUNCTION(eval_current_subsecond_real_time_funcalled,NIL,
	    FALSE,0,0));
    register_funcalled_evaluator(make_evaluator_description(Qcurrent_subsecond_real_time,
	    Qcurrent_subsecond_real_time,FIX((SI_Long)1L),Qall,Qnil,Qfloat,
	    Qnil,
	    SYMBOL_FUNCTION(Qeval_current_subsecond_real_time_funcalled),
	    Nil,FIX((SI_Long)96L),Nil,Nil,
	    Qeval_current_subsecond_real_time_funcalled),FIX((SI_Long)96L),
	    Funcall_eval_type_0_arg);
    Qcurrent_system_real_time = STATIC_SYMBOL("CURRENT-SYSTEM-REAL-TIME",
	    AB_package);
    Qeval_current_system_real_time_funcalled = 
	    STATIC_SYMBOL("EVAL-CURRENT-SYSTEM-REAL-TIME-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_current_system_real_time_funcalled,
	    STATIC_FUNCTION(eval_current_system_real_time_funcalled,NIL,
	    FALSE,0,0));
    register_funcalled_evaluator(make_evaluator_description(Qcurrent_system_real_time,
	    Qcurrent_system_real_time,FIX((SI_Long)1L),Qall,Qnil,Qfloat,
	    Qnil,SYMBOL_FUNCTION(Qeval_current_system_real_time_funcalled),
	    Nil,FIX((SI_Long)142L),Nil,Nil,
	    Qeval_current_system_real_time_funcalled),FIX((SI_Long)142L),
	    Funcall_eval_type_0_arg);
    Qcollection_time_of = STATIC_SYMBOL("COLLECTION-TIME-OF",AB_package);
    Qexpiration_source_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SOURCE-OPERATOR-P",AB_package);
    mutate_global_property(Qcollection_time_of,T,
	    Qexpiration_source_operator_p);
    collection_time_of_stack_node_converter_1 = 
	    STATIC_FUNCTION(collection_time_of_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qcollection_time_of,
	    collection_time_of_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    collection_time_of_i_chooser_1 = 
	    STATIC_FUNCTION(collection_time_of_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qcollection_time_of,
	    collection_time_of_i_chooser_1,Qpreferred_instruction_chooser);
    collection_time_of_i_emit_1 = 
	    STATIC_FUNCTION(collection_time_of_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qcollection_time_of,collection_time_of_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_13 = STATIC_STRING("~NF does not have a value.");
    Qfuncall_collection_time_of_inst = 
	    STATIC_SYMBOL("FUNCALL-COLLECTION-TIME-OF-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_collection_time_of_inst,
	    STATIC_FUNCTION(funcall_collection_time_of_inst,NIL,FALSE,2,2));
    Qpprint_collection_time_of_instruction = 
	    STATIC_SYMBOL("PPRINT-COLLECTION-TIME-OF-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_collection_time_of_instruction,
	    STATIC_FUNCTION(pprint_collection_time_of_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qcollection_time_of,
	    FIX((SI_Long)69L),Qall,FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_collection_time_of_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_collection_time_of_instruction),
	    Qfuncall_collection_time_of_inst);
    Qcollection_time_of_previous_datapoint = 
	    STATIC_SYMBOL("COLLECTION-TIME-OF-PREVIOUS-DATAPOINT",AB_package);
    mutate_global_property(Qcollection_time_of_previous_datapoint,T,
	    Qexpiration_source_operator_p);
    collection_time_of_previous_datapoint_stack_node_converter_1 = 
	    STATIC_FUNCTION(collection_time_of_previous_datapoint_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcollection_time_of_previous_datapoint,
	    collection_time_of_previous_datapoint_stack_node_converter_1,
	    Qstack_special_form_converter);
    collection_time_of_previous_datapoint_i_chooser_1 = 
	    STATIC_FUNCTION(collection_time_of_previous_datapoint_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcollection_time_of_previous_datapoint,
	    collection_time_of_previous_datapoint_i_chooser_1,
	    Qpreferred_instruction_chooser);
    collection_time_of_previous_datapoint_i_emit_1 = 
	    STATIC_FUNCTION(collection_time_of_previous_datapoint_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qcollection_time_of_previous_datapoint,
	    collection_time_of_previous_datapoint_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_14 = 
	    STATIC_STRING("Cannot reference the collection time of ~NF as of ~d datapoints ago.  A ~\n      history datapoint must be referenced by a non-negative integer.");
    string_constant_15 = 
	    STATIC_STRING("Cannot get a collection time for ~NF as of ~a datapoints ago.  ~\n           There was no value at that datapoint.");
    Qfuncall_collection_time_of_previous_datapoint_inst = 
	    STATIC_SYMBOL("FUNCALL-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_collection_time_of_previous_datapoint_inst,
	    STATIC_FUNCTION(funcall_collection_time_of_previous_datapoint_inst,
	    NIL,FALSE,2,2));
    Qpprint_collection_time_of_previous_datapoint_instruction = 
	    STATIC_SYMBOL("PPRINT-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_collection_time_of_previous_datapoint_instruction,
	    STATIC_FUNCTION(pprint_collection_time_of_previous_datapoint_instruction,
	    NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qcollection_time_of_previous_datapoint,
	    FIX((SI_Long)67L),Qall,FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_collection_time_of_previous_datapoint_inst),
	    Qnil,
	    SYMBOL_FUNCTION(Qpprint_collection_time_of_previous_datapoint_instruction),
	    Qfuncall_collection_time_of_previous_datapoint_inst);
    Qexpiration_time_of = STATIC_SYMBOL("EXPIRATION-TIME-OF",AB_package);
    mutate_global_property(Qexpiration_time_of,T,
	    Qexpiration_source_operator_p);
    expiration_time_of_stack_node_converter_1 = 
	    STATIC_FUNCTION(expiration_time_of_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qexpiration_time_of,
	    expiration_time_of_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qvariable);
    expiration_time_of_i_chooser_1 = 
	    STATIC_FUNCTION(expiration_time_of_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qexpiration_time_of,
	    expiration_time_of_i_chooser_1,Qpreferred_instruction_chooser);
    expiration_time_of_i_emit_1 = 
	    STATIC_FUNCTION(expiration_time_of_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qexpiration_time_of,expiration_time_of_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qfuncall_expiration_time_of_inst = 
	    STATIC_SYMBOL("FUNCALL-EXPIRATION-TIME-OF-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_expiration_time_of_inst,
	    STATIC_FUNCTION(funcall_expiration_time_of_inst,NIL,FALSE,2,2));
    Qpprint_expiration_time_of_instruction = 
	    STATIC_SYMBOL("PPRINT-EXPIRATION-TIME-OF-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_expiration_time_of_instruction,
	    STATIC_FUNCTION(pprint_expiration_time_of_instruction,NIL,
	    FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qexpiration_time_of,
	    FIX((SI_Long)70L),Qall,FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_expiration_time_of_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_expiration_time_of_instruction),
	    Qfuncall_expiration_time_of_inst);
    Qg2_list_or_sequence_member_p = 
	    STATIC_SYMBOL("G2-LIST-OR-SEQUENCE-MEMBER-P",AB_package);
    mutate_global_property(Qg2_list_or_sequence_member_p,T,
	    Qexpiration_source_operator_p);
    g2_list_or_sequence_member_p_stack_node_converter_1 = 
	    STATIC_FUNCTION(g2_list_or_sequence_member_p_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qg2_list_or_sequence_member_p,
	    g2_list_or_sequence_member_p_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_list);
    list_constant_15 = STATIC_CONS(Qsequence,Qnil);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_10,
	    list_constant_15);
    g2_list_or_sequence_member_p_i_chooser_1 = 
	    STATIC_FUNCTION(g2_list_or_sequence_member_p_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qg2_list_or_sequence_member_p,
	    g2_list_or_sequence_member_p_i_chooser_1,
	    Qpreferred_instruction_chooser);
    g2_list_or_sequence_member_p_i_emit_1 = 
	    STATIC_FUNCTION(g2_list_or_sequence_member_p_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qg2_list_or_sequence_member_p,
	    g2_list_or_sequence_member_p_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_16 = 
	    STATIC_STRING("Cannot test that ~NA is a member of the g2-list ~NF.  This item or value ~\n   conflicts with the element-type, ~a, of the g2-list.");
    Qfuncall_g2_list_or_sequence_member_p_inst = 
	    STATIC_SYMBOL("FUNCALL-G2-LIST-OR-SEQUENCE-MEMBER-P-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_g2_list_or_sequence_member_p_inst,
	    STATIC_FUNCTION(funcall_g2_list_or_sequence_member_p_inst,NIL,
	    FALSE,2,2));
    Qpprint_g2_list_or_sequence_member_p_instruction = 
	    STATIC_SYMBOL("PPRINT-G2-LIST-OR-SEQUENCE-MEMBER-P-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_g2_list_or_sequence_member_p_instruction,
	    STATIC_FUNCTION(pprint_g2_list_or_sequence_member_p_instruction,
	    NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qg2_list_or_sequence_member_p,
	    FIX((SI_Long)75L),Qall,FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_g2_list_or_sequence_member_p_inst),
	    Qnil,
	    SYMBOL_FUNCTION(Qpprint_g2_list_or_sequence_member_p_instruction),
	    Qfuncall_g2_list_or_sequence_member_p_inst);
    Qg2_list_or_sequence_length = 
	    STATIC_SYMBOL("G2-LIST-OR-SEQUENCE-LENGTH",AB_package);
    Qinference = STATIC_SYMBOL("INFERENCE",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qinference,Qprocedure);
    list_constant_20 = STATIC_CONS(list_constant_9,Qnil);
    Qeval_g2_list_or_sequence_length_in_line = 
	    STATIC_SYMBOL("EVAL-G2-LIST-OR-SEQUENCE-LENGTH-IN-LINE",
	    AB_package);
    Qpprint_g2_list_or_sequence_length_evaluator = 
	    STATIC_SYMBOL("PPRINT-G2-LIST-OR-SEQUENCE-LENGTH-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_g2_list_or_sequence_length_evaluator,
	    STATIC_FUNCTION(pprint_g2_list_or_sequence_length_evaluator,
	    NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qg2_list_or_sequence_length,
	    Qg2_list_or_sequence_length,FIX((SI_Long)1L),list_constant_19,
	    list_constant_20,Qinteger,Nil,
	    Qeval_g2_list_or_sequence_length_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)58L),Nil,
	    SYMBOL_FUNCTION(Qpprint_g2_list_or_sequence_length_evaluator),
	    Nil),FIX((SI_Long)58L));
    Qnext_list_element = STATIC_SYMBOL("NEXT-LIST-ELEMENT",AB_package);
    next_list_element_stack_node_converter_1 = 
	    STATIC_FUNCTION(next_list_element_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qnext_list_element,
	    next_list_element_stack_node_converter_1,
	    Qstack_special_form_converter);
    next_list_element_i_chooser_1 = 
	    STATIC_FUNCTION(next_list_element_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qnext_list_element,
	    next_list_element_i_chooser_1,Qpreferred_instruction_chooser);
    mutate_global_property(Qnext_list_element,T,Qexpiration_source_operator_p);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnext_list_element,
	    Qitem_or_datum);
    next_list_element_i_emit_1 = STATIC_FUNCTION(next_list_element_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qnext_list_element,next_list_element_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_17 = 
	    STATIC_STRING("The item ~NF is not an attribute of another item.");
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_22 = STATIC_CONS(list_constant_21,Qnil);
    Qeval_attribute_name_in_line = 
	    STATIC_SYMBOL("EVAL-ATTRIBUTE-NAME-IN-LINE",AB_package);
    Qpprint_attribute_name_evaluator = 
	    STATIC_SYMBOL("PPRINT-ATTRIBUTE-NAME-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_attribute_name_evaluator,
	    STATIC_FUNCTION(pprint_attribute_name_evaluator,NIL,FALSE,6,6));
    register_in_line_evaluator(make_evaluator_description(Qattribute_name,
	    Qattribute_name,FIX((SI_Long)1L),list_constant_19,
	    list_constant_22,Qsymbol,Nil,Qeval_attribute_name_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)59L),T,
	    SYMBOL_FUNCTION(Qpprint_attribute_name_evaluator),Nil),
	    FIX((SI_Long)59L));
    string_constant_18 = 
	    STATIC_STRING("Cannot compute the ABS of ~NV.  The result is too large to ~\n     represent as an integer and cannot be coerced to a float since the ~\n     required result type is integer.");
    Qabs_quantity = STATIC_SYMBOL("ABS-QUANTITY",AB_package);
    list_constant_23 = STATIC_CONS(Qnumber,Qnil);
    Qeval_abs_quantity_in_line = STATIC_SYMBOL("EVAL-ABS-QUANTITY-IN-LINE",
	    AB_package);
    Qpprint_functional_evaluator = 
	    STATIC_SYMBOL("PPRINT-FUNCTIONAL-EVALUATOR",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qabs,
	    Qabs_quantity,FIX((SI_Long)3L),Qall,list_constant_23,Qnumber,
	    Nil,Qeval_abs_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)60L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)60L));
    Qabs_integer = STATIC_SYMBOL("ABS-INTEGER",AB_package);
    list_constant_24 = STATIC_CONS(Qinteger,Qnil);
    Qeval_abs_integer_in_line = STATIC_SYMBOL("EVAL-ABS-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qabs,
	    Qabs_integer,FIX((SI_Long)1L),Qall,list_constant_24,Qinteger,
	    Nil,Qeval_abs_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)61L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)61L));
    Qabs_float = STATIC_SYMBOL("ABS-FLOAT",AB_package);
    list_constant_25 = STATIC_CONS(Qfloat,Qnil);
    Qeval_abs_float_in_line = STATIC_SYMBOL("EVAL-ABS-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qabs,Qabs_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_abs_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)62L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)62L));
    Qarctan = STATIC_SYMBOL("ARCTAN",AB_package);
    Qarctan_1 = STATIC_SYMBOL("ARCTAN-1",AB_package);
    Qeval_arctan_1_in_line = STATIC_SYMBOL("EVAL-ARCTAN-1-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qarctan,
	    Qarctan_1,FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_arctan_1_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)63L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)63L));
    Qarctan_2 = STATIC_SYMBOL("ARCTAN-2",AB_package);
    list_constant_26 = STATIC_CONS(Qfloat,list_constant_25);
    Qeval_arctan_2_in_line = STATIC_SYMBOL("EVAL-ARCTAN-2-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qarctan,
	    Qarctan_2,FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,Nil,
	    Qeval_arctan_2_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)64L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)64L));
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    string_constant_19 = 
	    STATIC_STRING("The ~s function requires ~d or more quantity arguments and ~\n              received ~d.");
    average_stack_node_converter_1 = 
	    STATIC_FUNCTION(average_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qaverage,average_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_20 = 
	    STATIC_STRING("Cannot compute the CEILING of ~NV.  The result is outside the ~\n   range of integers.");
    Qceiling_quantity = STATIC_SYMBOL("CEILING-QUANTITY",AB_package);
    Qeval_ceiling_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-CEILING-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qceiling,
	    Qceiling_quantity,FIX((SI_Long)3L),Qall,list_constant_23,
	    Qnumber,Nil,Qeval_ceiling_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)65L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)65L));
    Qceiling_float = STATIC_SYMBOL("CEILING-FLOAT",AB_package);
    Qeval_ceiling_float_in_line = 
	    STATIC_SYMBOL("EVAL-CEILING-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qceiling,
	    Qceiling_float,FIX((SI_Long)2L),Qall,list_constant_25,Qinteger,
	    Nil,Qeval_ceiling_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)66L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)66L));
    Qcos_float = STATIC_SYMBOL("COS-FLOAT",AB_package);
    Qeval_cos_float_in_line = STATIC_SYMBOL("EVAL-COS-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qcos,Qcos_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_cos_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)67L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)67L));
    Qexp_float = STATIC_SYMBOL("EXP-FLOAT",AB_package);
    Qeval_exp_float_in_line = STATIC_SYMBOL("EVAL-EXP-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qexp,Qexp_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_exp_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)68L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)68L));
    float_contagion_stack_operators_new_value = adjoin(2,Qexpt,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qexpt_quantity = STATIC_SYMBOL("EXPT-QUANTITY",AB_package);
    list_constant_27 = STATIC_CONS(Qnumber,list_constant_23);
    Qeval_expt_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-EXPT-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qexpt,
	    Qexpt_quantity,FIX((SI_Long)3L),Qall,list_constant_27,Qnumber,
	    Nil,Qeval_expt_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)69L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)69L));
    Qexpt_float = STATIC_SYMBOL("EXPT-FLOAT",AB_package);
    Qeval_expt_float_in_line = STATIC_SYMBOL("EVAL-EXPT-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qexpt,
	    Qexpt_float,FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,Nil,
	    Qeval_expt_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)70L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)70L));
    string_constant_21 = 
	    STATIC_STRING("Cannot compute the FLOOR of ~NV.  The result is too large to ~\n   represent as an integer.");
    Qfloor_quantity = STATIC_SYMBOL("FLOOR-QUANTITY",AB_package);
    Qeval_floor_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-FLOOR-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qfloor,
	    Qfloor_quantity,FIX((SI_Long)3L),Qall,list_constant_23,Qnumber,
	    Nil,Qeval_floor_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)71L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)71L));
    Qfloor_float = STATIC_SYMBOL("FLOOR-FLOAT",AB_package);
    Qeval_floor_float_in_line = STATIC_SYMBOL("EVAL-FLOOR-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qfloor,
	    Qfloor_float,FIX((SI_Long)2L),Qall,list_constant_25,Qinteger,
	    Nil,Qeval_floor_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)72L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)72L));
    string_constant_22 = 
	    STATIC_STRING("The ~a operator received the negative argument ~a.");
    Qln = STATIC_SYMBOL("LN",AB_package);
    Qln_float = STATIC_SYMBOL("LN-FLOAT",AB_package);
    Qeval_ln_float_in_line = STATIC_SYMBOL("EVAL-LN-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qln,Qln_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_ln_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)73L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)73L));
    Qlog_float = STATIC_SYMBOL("LOG-FLOAT",AB_package);
    Qeval_log_float_in_line = STATIC_SYMBOL("EVAL-LOG-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qlog,Qlog_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_log_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)74L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)74L));
    max_stack_node_converter_1 = STATIC_FUNCTION(max_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qmax,max_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qmax_quantity = STATIC_SYMBOL("MAX-QUANTITY",AB_package);
    Qeval_max_quantity_in_line = STATIC_SYMBOL("EVAL-MAX-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmax,
	    Qmax_quantity,FIX((SI_Long)3L),Qall,list_constant_27,Qnumber,
	    Nil,Qeval_max_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)75L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)75L));
    Qmax_integer = STATIC_SYMBOL("MAX-INTEGER",AB_package);
    list_constant_28 = STATIC_CONS(Qinteger,list_constant_24);
    Qeval_max_integer_in_line = STATIC_SYMBOL("EVAL-MAX-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmax,
	    Qmax_integer,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Nil,Qeval_max_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)76L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)76L));
    Qmax_float = STATIC_SYMBOL("MAX-FLOAT",AB_package);
    Qeval_max_float_in_line = STATIC_SYMBOL("EVAL-MAX-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmax,Qmax_float,
	    FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,Nil,
	    Qeval_max_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)77L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)77L));
    min_stack_node_converter_1 = STATIC_FUNCTION(min_stack_node_converter,
	    NIL,FALSE,1,1);
    mutate_global_property(Qmin,min_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qmin_quantity = STATIC_SYMBOL("MIN-QUANTITY",AB_package);
    Qeval_min_quantity_in_line = STATIC_SYMBOL("EVAL-MIN-QUANTITY-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmin,
	    Qmin_quantity,FIX((SI_Long)3L),Qall,list_constant_27,Qnumber,
	    Nil,Qeval_min_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)78L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)78L));
    Qmin_integer = STATIC_SYMBOL("MIN-INTEGER",AB_package);
    Qeval_min_integer_in_line = STATIC_SYMBOL("EVAL-MIN-INTEGER-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmin,
	    Qmin_integer,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Nil,Qeval_min_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)79L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)79L));
    Qmin_float = STATIC_SYMBOL("MIN-FLOAT",AB_package);
    Qeval_min_float_in_line = STATIC_SYMBOL("EVAL-MIN-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qmin,Qmin_float,
	    FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,Nil,
	    Qeval_min_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)80L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)80L));
    Qstack_evaluators = STATIC_SYMBOL("STACK-EVALUATORS",AB_package);
    Qquotient = STATIC_SYMBOL("QUOTIENT",AB_package);
    float_contagion_stack_operators_new_value = adjoin(2,Qquotient,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    string_constant_23 = 
	    STATIC_STRING("The result of the ~a expression, ~NV, is out of the range ~\n   of integers.");
    Qquotient_quantity = STATIC_SYMBOL("QUOTIENT-QUANTITY",AB_package);
    Qeval_quotient_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-QUOTIENT-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qquotient,
	    Qquotient_quantity,FIX((SI_Long)3L),list_constant_19,
	    list_constant_27,Qnumber,Nil,Qeval_quotient_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)81L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)81L));
    Qquotient_integer = STATIC_SYMBOL("QUOTIENT-INTEGER",AB_package);
    Qeval_quotient_integer_in_line = 
	    STATIC_SYMBOL("EVAL-QUOTIENT-INTEGER-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qquotient,
	    Qquotient_integer,FIX((SI_Long)1L),list_constant_19,
	    list_constant_28,Qinteger,Nil,Qeval_quotient_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)82L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)82L));
    Qquotient_float = STATIC_SYMBOL("QUOTIENT-FLOAT",AB_package);
    Qeval_quotient_float_in_line = 
	    STATIC_SYMBOL("EVAL-QUOTIENT-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qquotient,
	    Qquotient_float,FIX((SI_Long)2L),list_constant_19,
	    list_constant_26,Qinteger,Nil,Qeval_quotient_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)83L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)83L));
    Plus_recip_most_positive_fixnum_plus = DOUBLE_TO_DOUBLE_FLOAT(1.0 / 
	    (double)IFIX(Most_positive_fixnum));
    if (Random_real_0_result == UNBOUND)
	Random_real_0_result = Nil;
    string_constant_24 = 
	    STATIC_STRING("The ~a operator received the non-positive argument ~a.");
    Qrandom_quantity = STATIC_SYMBOL("RANDOM-QUANTITY",AB_package);
    Qeval_random_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-RANDOM-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_quantity,FIX((SI_Long)3L),Qall,list_constant_23,
	    Qnumber,Nil,Qeval_random_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)84L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)84L));
    Qrandom_integer = STATIC_SYMBOL("RANDOM-INTEGER",AB_package);
    Qeval_random_integer_in_line = 
	    STATIC_SYMBOL("EVAL-RANDOM-INTEGER-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_integer,FIX((SI_Long)1L),Qall,list_constant_24,
	    Qinteger,Nil,Qeval_random_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)85L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)85L));
    Qrandom_float = STATIC_SYMBOL("RANDOM-FLOAT",AB_package);
    Qeval_random_float_in_line = STATIC_SYMBOL("EVAL-RANDOM-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_float,FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,
	    Nil,Qeval_random_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)86L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)86L));
    float_contagion_stack_operators_new_value = adjoin(2,Qrandom,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qget_from_text = STATIC_SYMBOL("GET-FROM-TEXT",AB_package);
    Qreplace_in_text = STATIC_SYMBOL("REPLACE-IN-TEXT",AB_package);
    Qomit_from_text = STATIC_SYMBOL("OMIT-FROM-TEXT",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qget_from_text,
	    Qreplace_in_text,Qomit_from_text);
    string_constant_25 = STATIC_STRING(" one more than");
    string_constant_26 = STATIC_STRING("");
    string_constant_27 = 
	    STATIC_STRING("The ~a operator requires the argument ~a to be less than~a the argument ~a.");
    string_constant_28 = 
	    STATIC_STRING("The ~a operator requires the start-index, ~a, to be ~\n       less than or equal to~a the end-index, ~a.");
    Qrandom_quantity_2 = STATIC_SYMBOL("RANDOM-QUANTITY-2",AB_package);
    Qeval_random_quantity_2_in_line = 
	    STATIC_SYMBOL("EVAL-RANDOM-QUANTITY-2-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_quantity_2,FIX((SI_Long)3L),Qall,list_constant_27,
	    Qnumber,Nil,Qeval_random_quantity_2_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)87L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)87L));
    Qrandom_integer_2 = STATIC_SYMBOL("RANDOM-INTEGER-2",AB_package);
    Qeval_random_integer_2_in_line = 
	    STATIC_SYMBOL("EVAL-RANDOM-INTEGER-2-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_integer_2,FIX((SI_Long)1L),Qall,list_constant_28,
	    Qinteger,Nil,Qeval_random_integer_2_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)88L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)88L));
    Qrandom_float_2 = STATIC_SYMBOL("RANDOM-FLOAT-2",AB_package);
    Qeval_random_float_2_in_line = 
	    STATIC_SYMBOL("EVAL-RANDOM-FLOAT-2-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qrandom,
	    Qrandom_float_2,FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,
	    Nil,Qeval_random_float_2_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)89L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)89L));
    Qremainder = STATIC_SYMBOL("REMAINDER",AB_package);
    float_contagion_stack_operators_new_value = adjoin(2,Qremainder,
	    Float_contagion_stack_operators);
    Float_contagion_stack_operators = 
	    float_contagion_stack_operators_new_value;
    Qremainder_quantity = STATIC_SYMBOL("REMAINDER-QUANTITY",AB_package);
    Qeval_remainder_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-REMAINDER-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qremainder,
	    Qremainder_quantity,FIX((SI_Long)3L),Qall,list_constant_27,
	    Qnumber,Nil,Qeval_remainder_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)90L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)90L));
    Qremainder_integer = STATIC_SYMBOL("REMAINDER-INTEGER",AB_package);
    Qeval_remainder_integer_in_line = 
	    STATIC_SYMBOL("EVAL-REMAINDER-INTEGER-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qremainder,
	    Qremainder_integer,FIX((SI_Long)1L),Qall,list_constant_28,
	    Qinteger,Nil,Qeval_remainder_integer_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)91L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)91L));
    Qremainder_float = STATIC_SYMBOL("REMAINDER-FLOAT",AB_package);
    Qeval_remainder_float_in_line = 
	    STATIC_SYMBOL("EVAL-REMAINDER-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qremainder,
	    Qremainder_float,FIX((SI_Long)2L),Qall,list_constant_26,Qfloat,
	    Nil,Qeval_remainder_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)92L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)92L));
    Qround_quantity = STATIC_SYMBOL("ROUND-QUANTITY",AB_package);
    Qeval_round_quantity_in_line = 
	    STATIC_SYMBOL("EVAL-ROUND-QUANTITY-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qround,
	    Qround_quantity,FIX((SI_Long)3L),Qall,list_constant_23,Qnumber,
	    Nil,Qeval_round_quantity_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)93L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)93L));
    Qround_float = STATIC_SYMBOL("ROUND-FLOAT",AB_package);
    Qeval_round_float_in_line = STATIC_SYMBOL("EVAL-ROUND-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qround,
	    Qround_float,FIX((SI_Long)2L),Qall,list_constant_25,Qinteger,
	    Nil,Qeval_round_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)94L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)94L));
    Qsin_float = STATIC_SYMBOL("SIN-FLOAT",AB_package);
    Qeval_sin_float_in_line = STATIC_SYMBOL("EVAL-SIN-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qsin,Qsin_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_sin_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)95L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)95L));
    Qsqrt_float = STATIC_SYMBOL("SQRT-FLOAT",AB_package);
    Qeval_sqrt_float_in_line = STATIC_SYMBOL("EVAL-SQRT-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qsqrt,
	    Qsqrt_float,FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_sqrt_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)96L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)96L));
    Qtan_float = STATIC_SYMBOL("TAN-FLOAT",AB_package);
    Qeval_tan_float_in_line = STATIC_SYMBOL("EVAL-TAN-FLOAT-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qtan,Qtan_float,
	    FIX((SI_Long)2L),Qall,list_constant_25,Qfloat,Nil,
	    Qeval_tan_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)98L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)98L));
    Qtruncate_float = STATIC_SYMBOL("TRUNCATE-FLOAT",AB_package);
    Qeval_truncate_float_in_line = 
	    STATIC_SYMBOL("EVAL-TRUNCATE-FLOAT-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qtruncate,
	    Qtruncate_float,FIX((SI_Long)2L),Qall,list_constant_25,
	    Qinteger,Nil,Qeval_truncate_float_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)97L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)97L));
    Qtruth_value_datum = STATIC_SYMBOL("TRUTH-VALUE-DATUM",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qab_or,Qnumber,Qtruth_value);
    list_constant_30 = STATIC_CONS(list_constant_29,Qnil);
    Qeval_truth_value_datum_in_line = 
	    STATIC_SYMBOL("EVAL-TRUTH-VALUE-DATUM-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qtruth_value,
	    Qtruth_value_datum,FIX((SI_Long)5L),list_constant_19,
	    list_constant_30,Qtruth_value,Nil,
	    Qeval_truth_value_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)15L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)15L));
    Qtruth_value_of_truth_value = 
	    STATIC_SYMBOL("TRUTH-VALUE-OF-TRUTH-VALUE",AB_package);
    list_constant_31 = STATIC_CONS(Qtruth_value,Qnil);
    Qeval_truth_value_of_truth_value_funcalled = 
	    STATIC_SYMBOL("EVAL-TRUTH-VALUE-OF-TRUTH-VALUE-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_truth_value_of_truth_value_funcalled,
	    STATIC_FUNCTION(eval_truth_value_of_truth_value_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtruth_value,
	    Qtruth_value_of_truth_value,FIX((SI_Long)4L),list_constant_19,
	    list_constant_31,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_truth_value_of_truth_value_funcalled),
	    Nil,FIX((SI_Long)34L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_truth_value_of_truth_value_funcalled),FIX((SI_Long)34L),
	    Funcall_eval_type_1_arg);
    string_constant_29 = 
	    STATIC_STRING("Unknown kind of number, ~NV, given to truth-value.");
    Qtruth_value_quantity = STATIC_SYMBOL("TRUTH-VALUE-QUANTITY",AB_package);
    Qeval_truth_value_quantity_funcalled = 
	    STATIC_SYMBOL("EVAL-TRUTH-VALUE-QUANTITY-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_truth_value_quantity_funcalled,
	    STATIC_FUNCTION(eval_truth_value_quantity_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtruth_value,
	    Qtruth_value_quantity,FIX((SI_Long)3L),list_constant_19,
	    list_constant_23,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_truth_value_quantity_funcalled),Nil,
	    FIX((SI_Long)35L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_truth_value_quantity_funcalled),FIX((SI_Long)35L),
	    Funcall_eval_type_1_arg);
    Qtruth_value_integer = STATIC_SYMBOL("TRUTH-VALUE-INTEGER",AB_package);
    Qeval_truth_value_integer_funcalled = 
	    STATIC_SYMBOL("EVAL-TRUTH-VALUE-INTEGER-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_truth_value_integer_funcalled,
	    STATIC_FUNCTION(eval_truth_value_integer_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtruth_value,
	    Qtruth_value_integer,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_truth_value_integer_funcalled),Nil,
	    FIX((SI_Long)36L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_truth_value_integer_funcalled),FIX((SI_Long)36L),
	    Funcall_eval_type_1_arg);
    Qtruth_value_float = STATIC_SYMBOL("TRUTH-VALUE-FLOAT",AB_package);
    Qeval_truth_value_float_funcalled = 
	    STATIC_SYMBOL("EVAL-TRUTH-VALUE-FLOAT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_truth_value_float_funcalled,
	    STATIC_FUNCTION(eval_truth_value_float_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtruth_value,
	    Qtruth_value_float,FIX((SI_Long)2L),list_constant_19,
	    list_constant_25,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_truth_value_float_funcalled),Nil,
	    FIX((SI_Long)37L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_truth_value_float_funcalled),FIX((SI_Long)37L),
	    Funcall_eval_type_1_arg);
    Qis_contained_in_text = STATIC_SYMBOL("IS-CONTAINED-IN-TEXT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qtext,Qtext);
    Qeval_is_contained_in_text_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-CONTAINED-IN-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_contained_in_text_funcalled,
	    STATIC_FUNCTION(eval_is_contained_in_text_funcalled,NIL,FALSE,
	    2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_contained_in_text,
	    Qis_contained_in_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_32,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_contained_in_text_funcalled),Nil,
	    FIX((SI_Long)38L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_contained_in_text_funcalled),FIX((SI_Long)38L),
	    Funcall_eval_type_2_arg);
    Qlength_of_text = STATIC_SYMBOL("LENGTH-OF-TEXT",AB_package);
    list_constant_33 = STATIC_CONS(Qtext,Qnil);
    Qeval_length_of_text_funcalled = 
	    STATIC_SYMBOL("EVAL-LENGTH-OF-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_length_of_text_funcalled,
	    STATIC_FUNCTION(eval_length_of_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qlength_of_text,
	    Qlength_of_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_length_of_text_funcalled),Nil,
	    FIX((SI_Long)39L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_length_of_text_funcalled),FIX((SI_Long)39L),
	    Funcall_eval_type_1_arg);
    Qposition_of_text = STATIC_SYMBOL("POSITION-OF-TEXT",AB_package);
    Qeval_position_of_text_funcalled = 
	    STATIC_SYMBOL("EVAL-POSITION-OF-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_position_of_text_funcalled,
	    STATIC_FUNCTION(eval_position_of_text_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qposition_of_text,
	    Qposition_of_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_32,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_position_of_text_funcalled),Nil,
	    FIX((SI_Long)40L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_position_of_text_funcalled),FIX((SI_Long)40L),
	    Funcall_eval_type_2_arg);
    Qunderflow = STATIC_SYMBOL("UNDERFLOW",AB_package);
    Qoverflow = STATIC_SYMBOL("OVERFLOW",AB_package);
    Qtext_begins_with_quantity = STATIC_SYMBOL("TEXT-BEGINS-WITH-QUANTITY",
	    AB_package);
    Qeval_text_begins_with_quantity_funcalled = 
	    STATIC_SYMBOL("EVAL-TEXT-BEGINS-WITH-QUANTITY-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_text_begins_with_quantity_funcalled,
	    STATIC_FUNCTION(eval_text_begins_with_quantity_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtext_begins_with_quantity,
	    Qtext_begins_with_quantity,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_text_begins_with_quantity_funcalled),Nil,
	    FIX((SI_Long)41L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_text_begins_with_quantity_funcalled),FIX((SI_Long)41L),
	    Funcall_eval_type_1_arg);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qupper_case_text = STATIC_SYMBOL("UPPER-CASE-TEXT",AB_package);
    Qeval_upper_case_text_funcalled = 
	    STATIC_SYMBOL("EVAL-UPPER-CASE-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_upper_case_text_funcalled,
	    STATIC_FUNCTION(eval_upper_case_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qupper_case_text,
	    Qupper_case_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_upper_case_text_funcalled),Nil,
	    FIX((SI_Long)42L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_upper_case_text_funcalled),FIX((SI_Long)42L),
	    Funcall_eval_type_1_arg);
    Knone = STATIC_SYMBOL("NONE",Pkeyword);
    Qlower_case_text = STATIC_SYMBOL("LOWER-CASE-TEXT",AB_package);
    Qeval_lower_case_text_funcalled = 
	    STATIC_SYMBOL("EVAL-LOWER-CASE-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_lower_case_text_funcalled,
	    STATIC_FUNCTION(eval_lower_case_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qlower_case_text,
	    Qlower_case_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_lower_case_text_funcalled),Nil,
	    FIX((SI_Long)43L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_lower_case_text_funcalled),FIX((SI_Long)43L),
	    Funcall_eval_type_1_arg);
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Qcapitalize_words = STATIC_SYMBOL("CAPITALIZE-WORDS",AB_package);
    Qeval_capitalize_words_funcalled = 
	    STATIC_SYMBOL("EVAL-CAPITALIZE-WORDS-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_capitalize_words_funcalled,
	    STATIC_FUNCTION(eval_capitalize_words_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qcapitalize_words,
	    Qcapitalize_words,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_capitalize_words_funcalled),Nil,
	    FIX((SI_Long)44L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_capitalize_words_funcalled),FIX((SI_Long)44L),
	    Funcall_eval_type_1_arg);
    string_constant_30 = 
	    string_append2(STATIC_STRING("The ~a evaluator failed to produce an answer despite the fact~\n   that it\'s arguments were within bounds.  Please report this~\n   internal error to Gensym software support wit"),
	    STATIC_STRING("h the source code\n   of the item named in the error message."));
    Qinsert_in_text = STATIC_SYMBOL("INSERT-IN-TEXT",AB_package);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,Qtext,Qtext,
	    list_constant_24);
    Qeval_insert_in_text_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-IN-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_in_text_funcalled,
	    STATIC_FUNCTION(eval_insert_in_text_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_in_text,
	    Qinsert_in_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_34,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_in_text_funcalled),Nil,
	    FIX((SI_Long)45L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_in_text_funcalled),FIX((SI_Long)45L),
	    Funcall_eval_type_3_arg);
    list_constant_35 = STATIC_CONS(Qtext,list_constant_28);
    Qeval_omit_from_text_funcalled = 
	    STATIC_SYMBOL("EVAL-OMIT-FROM-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_omit_from_text_funcalled,
	    STATIC_FUNCTION(eval_omit_from_text_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qomit_from_text,
	    Qomit_from_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_35,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_omit_from_text_funcalled),Nil,
	    FIX((SI_Long)46L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_omit_from_text_funcalled),FIX((SI_Long)46L),
	    Funcall_eval_type_3_arg);
    Qeval_get_from_text_funcalled = 
	    STATIC_SYMBOL("EVAL-GET-FROM-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_get_from_text_funcalled,
	    STATIC_FUNCTION(eval_get_from_text_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qget_from_text,
	    Qget_from_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_35,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_get_from_text_funcalled),Nil,
	    FIX((SI_Long)47L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_get_from_text_funcalled),FIX((SI_Long)47L),
	    Funcall_eval_type_3_arg);
    list_constant_36 = STATIC_CONS(Qtext,list_constant_35);
    Qeval_replace_in_text_funcalled = 
	    STATIC_SYMBOL("EVAL-REPLACE-IN-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_replace_in_text_funcalled,
	    STATIC_FUNCTION(eval_replace_in_text_funcalled,NIL,FALSE,4,4));
    register_funcalled_evaluator(make_evaluator_description(Qreplace_in_text,
	    Qreplace_in_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_36,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_replace_in_text_funcalled),Nil,
	    FIX((SI_Long)66L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_replace_in_text_funcalled),FIX((SI_Long)66L),
	    Funcall_eval_type_4_arg);
    Qfind_next_pattern = STATIC_SYMBOL("FIND-NEXT-PATTERN",AB_package);
    Qg2_defstruct_structure_name_lexing_table_g2_struct = 
	    STATIC_SYMBOL("LEXING-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfind_next_pattern_3 = STATIC_SYMBOL("FIND-NEXT-PATTERN-3",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_16 = STATIC_CONS(Qab_structure,Qnil);
    Qeval_find_next_pattern_3_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-NEXT-PATTERN-3-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_next_pattern_3_funcalled,
	    STATIC_FUNCTION(eval_find_next_pattern_3_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qfind_next_pattern,
	    Qfind_next_pattern_3,FIX((SI_Long)3L),list_constant_19,
	    list_constant_34,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_next_pattern_3_funcalled),Nil,
	    FIX((SI_Long)27L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_next_pattern_3_funcalled),FIX((SI_Long)27L),
	    Funcall_eval_type_3_arg);
    Qfind_next_substring_matching_pattern = 
	    STATIC_SYMBOL("FIND-NEXT-SUBSTRING-MATCHING-PATTERN",AB_package);
    Qfind_next_substring_matching_pattern_3 = 
	    STATIC_SYMBOL("FIND-NEXT-SUBSTRING-MATCHING-PATTERN-3",AB_package);
    Qeval_find_next_substring_matching_pattern_3_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-NEXT-SUBSTRING-MATCHING-PATTERN-3-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_next_substring_matching_pattern_3_funcalled,
	    STATIC_FUNCTION(eval_find_next_substring_matching_pattern_3_funcalled,
	    NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qfind_next_substring_matching_pattern,
	    Qfind_next_substring_matching_pattern_3,FIX((SI_Long)3L),
	    list_constant_19,list_constant_34,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_next_substring_matching_pattern_3_funcalled),
	    Nil,FIX((SI_Long)28L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_next_substring_matching_pattern_3_funcalled),
	    FIX((SI_Long)28L),Funcall_eval_type_3_arg);
    Qfind_and_replace_pattern = STATIC_SYMBOL("FIND-AND-REPLACE-PATTERN",
	    AB_package);
    Qfind_and_replace_pattern_5 = 
	    STATIC_SYMBOL("FIND-AND-REPLACE-PATTERN-5",AB_package);
    list_constant_37 = STATIC_CONS(Qtext,list_constant_36);
    Qeval_find_and_replace_pattern_5_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-AND-REPLACE-PATTERN-5-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_and_replace_pattern_5_funcalled,
	    STATIC_FUNCTION(eval_find_and_replace_pattern_5_funcalled,NIL,
	    FALSE,5,5));
    register_funcalled_evaluator(make_evaluator_description(Qfind_and_replace_pattern,
	    Qfind_and_replace_pattern_5,FIX((SI_Long)5L),list_constant_19,
	    list_constant_37,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_and_replace_pattern_5_funcalled),
	    Nil,FIX((SI_Long)29L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_and_replace_pattern_5_funcalled),FIX((SI_Long)29L),
	    Funcall_eval_type_5_arg);
    Qfind_next_pattern_4 = STATIC_SYMBOL("FIND-NEXT-PATTERN-4",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)4L,Qtext,Qtext,Qinteger,
	    list_constant_16);
    Qeval_find_next_pattern_4_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-NEXT-PATTERN-4-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_next_pattern_4_funcalled,
	    STATIC_FUNCTION(eval_find_next_pattern_4_funcalled,NIL,FALSE,4,4));
    register_funcalled_evaluator(make_evaluator_description(Qfind_next_pattern,
	    Qfind_next_pattern_4,FIX((SI_Long)4L),list_constant_19,
	    list_constant_38,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_next_pattern_4_funcalled),Nil,
	    FIX((SI_Long)33L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_next_pattern_4_funcalled),FIX((SI_Long)33L),
	    Funcall_eval_type_4_arg);
    Qfind_next_substring_matching_pattern_4 = 
	    STATIC_SYMBOL("FIND-NEXT-SUBSTRING-MATCHING-PATTERN-4",AB_package);
    Qeval_find_next_substring_matching_pattern_4_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-NEXT-SUBSTRING-MATCHING-PATTERN-4-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_next_substring_matching_pattern_4_funcalled,
	    STATIC_FUNCTION(eval_find_next_substring_matching_pattern_4_funcalled,
	    NIL,FALSE,4,4));
    register_funcalled_evaluator(make_evaluator_description(Qfind_next_substring_matching_pattern,
	    Qfind_next_substring_matching_pattern_4,FIX((SI_Long)4L),
	    list_constant_19,list_constant_38,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_next_substring_matching_pattern_4_funcalled),
	    Nil,FIX((SI_Long)79L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_next_substring_matching_pattern_4_funcalled),
	    FIX((SI_Long)79L),Funcall_eval_type_4_arg);
    Qfind_and_replace_pattern_6 = 
	    STATIC_SYMBOL("FIND-AND-REPLACE-PATTERN-6",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qinteger,list_constant_16);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)5L,Qtext,Qtext,Qtext,
	    Qinteger,list_constant_39);
    Qeval_find_and_replace_pattern_6_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-AND-REPLACE-PATTERN-6-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_and_replace_pattern_6_funcalled,
	    STATIC_FUNCTION(eval_find_and_replace_pattern_6_funcalled,NIL,
	    FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfind_and_replace_pattern,
	    Qfind_and_replace_pattern_6,FIX((SI_Long)6L),list_constant_19,
	    list_constant_40,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_and_replace_pattern_6_funcalled),
	    Nil,FIX((SI_Long)98L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_and_replace_pattern_6_funcalled),FIX((SI_Long)98L),
	    Funcall_eval_type_6_arg);
    string_constant_31 = 
	    STATIC_STRING("Tokenizer ~NF was passed to ~a, but it is not OK:~%~s~%");
    Qget_next_token = STATIC_SYMBOL("GET-NEXT-TOKEN",AB_package);
    Qget_next_token_3 = STATIC_SYMBOL("GET-NEXT-TOKEN-3",AB_package);
    Qtokenizer = STATIC_SYMBOL("TOKENIZER",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qab_class,Qtokenizer);
    list_constant_42 = STATIC_CONS(Qtext,list_constant_24);
    list_constant_43 = STATIC_CONS(list_constant_41,list_constant_42);
    Qeval_get_next_token_3_funcalled = 
	    STATIC_SYMBOL("EVAL-GET-NEXT-TOKEN-3-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_get_next_token_3_funcalled,
	    STATIC_FUNCTION(eval_get_next_token_3_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qget_next_token,
	    Qget_next_token_3,FIX((SI_Long)3L),list_constant_19,
	    list_constant_43,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_get_next_token_3_funcalled),Nil,
	    FIX((SI_Long)25L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_get_next_token_3_funcalled),FIX((SI_Long)25L),
	    Funcall_eval_type_3_arg);
    Qget_next_token_4 = STATIC_SYMBOL("GET-NEXT-TOKEN-4",AB_package);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)4L,list_constant_41,Qtext,
	    Qinteger,list_constant_31);
    Qeval_get_next_token_4_funcalled = 
	    STATIC_SYMBOL("EVAL-GET-NEXT-TOKEN-4-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_get_next_token_4_funcalled,
	    STATIC_FUNCTION(eval_get_next_token_4_funcalled,NIL,FALSE,4,4));
    register_funcalled_evaluator(make_evaluator_description(Qget_next_token,
	    Qget_next_token_4,FIX((SI_Long)4L),list_constant_19,
	    list_constant_44,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_get_next_token_4_funcalled),Nil,
	    FIX((SI_Long)32L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_get_next_token_4_funcalled),FIX((SI_Long)32L),
	    Funcall_eval_type_4_arg);
    Qstart_index = STATIC_SYMBOL("START-INDEX",AB_package);
    Qend_index = STATIC_SYMBOL("END-INDEX",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qlexeme = STATIC_SYMBOL("LEXEME",AB_package);
    list_constant_45 = STATIC_CONS(list_constant_16,Qnil);
    list_constant_46 = STATIC_CONS(Qtext,list_constant_45);
    Qeval_lexeme_funcalled = STATIC_SYMBOL("EVAL-LEXEME-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_lexeme_funcalled,
	    STATIC_FUNCTION(eval_lexeme_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qlexeme,
	    Qlexeme,FIX((SI_Long)1L),list_constant_19,list_constant_46,
	    Qtext,Qnil,SYMBOL_FUNCTION(Qeval_lexeme_funcalled),Nil,
	    FIX((SI_Long)99L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_lexeme_funcalled),FIX((SI_Long)99L),Funcall_eval_type_2_arg);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qquantity_datum = STATIC_SYMBOL("QUANTITY-DATUM",AB_package);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,Qnumber,
	    Qtruth_value,list_constant_33);
    list_constant_48 = STATIC_CONS(list_constant_47,Qnil);
    Qeval_quantity_datum_in_line = 
	    STATIC_SYMBOL("EVAL-QUANTITY-DATUM-IN-LINE",AB_package);
    register_in_line_evaluator(make_evaluator_description(Qquantity,
	    Qquantity_datum,FIX((SI_Long)5L),list_constant_19,
	    list_constant_48,Qnumber,Nil,Qeval_quantity_datum_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)51L),T,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)51L));
    string_constant_32 = 
	    STATIC_STRING("The ~a function received a text argument \"\".");
    string_constant_33 = 
	    STATIC_STRING("The ~a function could not convert the argument ~NV to type ~a.");
    string_constant_34 = 
	    STATIC_STRING("The ~a function could not convert the argument ~A to type ~a.");
    Qquantity_truth_value = STATIC_SYMBOL("QUANTITY-TRUTH-VALUE",AB_package);
    Qeval_quantity_truth_value_funcalled = 
	    STATIC_SYMBOL("EVAL-QUANTITY-TRUTH-VALUE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_quantity_truth_value_funcalled,
	    STATIC_FUNCTION(eval_quantity_truth_value_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qquantity,
	    Qquantity_truth_value,FIX((SI_Long)4L),list_constant_19,
	    list_constant_31,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_quantity_truth_value_funcalled),Nil,
	    FIX((SI_Long)48L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_quantity_truth_value_funcalled),FIX((SI_Long)48L),
	    Funcall_eval_type_1_arg);
    Qquantity_quantity = STATIC_SYMBOL("QUANTITY-QUANTITY",AB_package);
    Qeval_quantity_quantity_funcalled = 
	    STATIC_SYMBOL("EVAL-QUANTITY-QUANTITY-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_quantity_quantity_funcalled,
	    STATIC_FUNCTION(eval_quantity_quantity_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qquantity,
	    Qquantity_quantity,FIX((SI_Long)3L),list_constant_19,
	    list_constant_23,Qnumber,Qnil,
	    SYMBOL_FUNCTION(Qeval_quantity_quantity_funcalled),Nil,
	    FIX((SI_Long)49L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_quantity_quantity_funcalled),FIX((SI_Long)49L),
	    Funcall_eval_type_1_arg);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qquantity_text = STATIC_SYMBOL("QUANTITY-TEXT",AB_package);
    Qeval_quantity_text_funcalled = 
	    STATIC_SYMBOL("EVAL-QUANTITY-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_quantity_text_funcalled,
	    STATIC_FUNCTION(eval_quantity_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qquantity,
	    Qquantity_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qnumber,Qnil,
	    SYMBOL_FUNCTION(Qeval_quantity_text_funcalled),Nil,
	    FIX((SI_Long)50L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_quantity_text_funcalled),FIX((SI_Long)50L),
	    Funcall_eval_type_1_arg);
    string_constant_35 = STATIC_STRING("beginning with \"~a...\"");
    string_constant_36 = STATIC_STRING("\"~a\"");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_37 = 
	    STATIC_STRING("The ~(~a~) function could not convert the text ~a to a symbol.");
    string_constant_38 = STATIC_STRING("  ~a");
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    string_constant_39 = STATIC_STRING("~A::~A");
    Qsymbol_datum = STATIC_SYMBOL("SYMBOL-DATUM",AB_package);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_33);
    list_constant_50 = STATIC_CONS(list_constant_49,Qnil);
    Qeval_symbol_datum_funcalled = 
	    STATIC_SYMBOL("EVAL-SYMBOL-DATUM-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_symbol_datum_funcalled,
	    STATIC_FUNCTION(eval_symbol_datum_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qsymbol,
	    Qsymbol_datum,FIX((SI_Long)5L),list_constant_19,
	    list_constant_50,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qeval_symbol_datum_funcalled),Nil,
	    FIX((SI_Long)30L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_symbol_datum_funcalled),FIX((SI_Long)30L),
	    Funcall_eval_type_1_arg);
    Qsymbol_text = STATIC_SYMBOL("SYMBOL-TEXT",AB_package);
    Qeval_symbol_text_funcalled = 
	    STATIC_SYMBOL("EVAL-SYMBOL-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_symbol_text_funcalled,
	    STATIC_FUNCTION(eval_symbol_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qsymbol,
	    Qsymbol_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qeval_symbol_text_funcalled),Nil,
	    FIX((SI_Long)31L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_symbol_text_funcalled),FIX((SI_Long)31L),
	    Funcall_eval_type_1_arg);
    Qtext_to_symbol = STATIC_SYMBOL("TEXT-TO-SYMBOL",AB_package);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    Qeval_text_to_symbol_funcalled = 
	    STATIC_SYMBOL("EVAL-TEXT-TO-SYMBOL-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_text_to_symbol_funcalled,
	    STATIC_FUNCTION(eval_text_to_symbol_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtext_to_symbol,
	    Qtext_to_symbol,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qeval_text_to_symbol_funcalled),Nil,
	    FIX((SI_Long)114L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_text_to_symbol_funcalled),FIX((SI_Long)114L),
	    Funcall_eval_type_1_arg);
    string_constant_40 = 
	    STATIC_STRING("The ~a function received an invalid ~a argument ~NV.");
    string_constant_41 = 
	    STATIC_STRING("The ~a function received an invalid ~a argument ~A.");
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    Qeval_year_funcalled = STATIC_SYMBOL("EVAL-YEAR-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_year_funcalled,
	    STATIC_FUNCTION(eval_year_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qyear,Qyear,
	    FIX((SI_Long)1L),Qall,list_constant_23,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_year_funcalled),Nil,FIX((SI_Long)51L),
	    Nil,SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_year_funcalled),FIX((SI_Long)51L),Funcall_eval_type_1_arg);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    Qeval_month_funcalled = STATIC_SYMBOL("EVAL-MONTH-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_month_funcalled,
	    STATIC_FUNCTION(eval_month_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qmonth,Qmonth,
	    FIX((SI_Long)1L),Qall,list_constant_23,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_month_funcalled),Nil,FIX((SI_Long)52L),
	    Nil,SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_month_funcalled),FIX((SI_Long)52L),Funcall_eval_type_1_arg);
    Qday_of_the_month = STATIC_SYMBOL("DAY-OF-THE-MONTH",AB_package);
    Qeval_day_of_the_month_funcalled = 
	    STATIC_SYMBOL("EVAL-DAY-OF-THE-MONTH-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_day_of_the_month_funcalled,
	    STATIC_FUNCTION(eval_day_of_the_month_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qday_of_the_month,
	    Qday_of_the_month,FIX((SI_Long)1L),Qall,list_constant_23,
	    Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_day_of_the_month_funcalled),Nil,
	    FIX((SI_Long)53L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_day_of_the_month_funcalled),FIX((SI_Long)53L),
	    Funcall_eval_type_1_arg);
    Qmonday = STATIC_SYMBOL("MONDAY",AB_package);
    Qtuesday = STATIC_SYMBOL("TUESDAY",AB_package);
    Qwednesday = STATIC_SYMBOL("WEDNESDAY",AB_package);
    Qthursday = STATIC_SYMBOL("THURSDAY",AB_package);
    Qfriday = STATIC_SYMBOL("FRIDAY",AB_package);
    Qsaturday = STATIC_SYMBOL("SATURDAY",AB_package);
    Qsunday = STATIC_SYMBOL("SUNDAY",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)7L,Qmonday,Qtuesday,Qwednesday,
	    Qthursday,Qfriday,Qsaturday,Qsunday);
    if (Day_of_the_week_names == UNBOUND)
	Day_of_the_week_names = list_constant_51;
    Qday_of_the_week = STATIC_SYMBOL("DAY-OF-THE-WEEK",AB_package);
    Qeval_day_of_the_week_funcalled = 
	    STATIC_SYMBOL("EVAL-DAY-OF-THE-WEEK-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_day_of_the_week_funcalled,
	    STATIC_FUNCTION(eval_day_of_the_week_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qday_of_the_week,
	    Qday_of_the_week,FIX((SI_Long)1L),Qall,list_constant_23,
	    Qsymbol,Qnil,SYMBOL_FUNCTION(Qeval_day_of_the_week_funcalled),
	    Nil,FIX((SI_Long)54L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_day_of_the_week_funcalled),FIX((SI_Long)54L),
	    Funcall_eval_type_1_arg);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qeval_hour_funcalled = STATIC_SYMBOL("EVAL-HOUR-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_hour_funcalled,
	    STATIC_FUNCTION(eval_hour_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qhour,Qhour,
	    FIX((SI_Long)1L),Qall,list_constant_23,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_hour_funcalled),Nil,FIX((SI_Long)55L),
	    Nil,SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_hour_funcalled),FIX((SI_Long)55L),Funcall_eval_type_1_arg);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qeval_minute_funcalled = STATIC_SYMBOL("EVAL-MINUTE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_minute_funcalled,
	    STATIC_FUNCTION(eval_minute_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qminute,
	    Qminute,FIX((SI_Long)1L),Qall,list_constant_23,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_minute_funcalled),Nil,FIX((SI_Long)56L),
	    Nil,SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_minute_funcalled),FIX((SI_Long)56L),Funcall_eval_type_1_arg);
    Qeval_second_funcalled = STATIC_SYMBOL("EVAL-SECOND-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_second_funcalled,
	    STATIC_FUNCTION(eval_second_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qsecond,
	    Qsecond,FIX((SI_Long)1L),Qall,list_constant_23,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_second_funcalled),Nil,FIX((SI_Long)57L),
	    Nil,SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_second_funcalled),FIX((SI_Long)57L),Funcall_eval_type_1_arg);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)5L,Qinteger,Qinteger,
	    Qinteger,Qinteger,list_constant_28);
    Qeval_time_funcalled = STATIC_SYMBOL("EVAL-TIME-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_time_funcalled,
	    STATIC_FUNCTION(eval_time_funcalled,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qtime,Qtime,
	    FIX((SI_Long)1L),list_constant_19,list_constant_52,Qnumber,
	    Qnil,SYMBOL_FUNCTION(Qeval_time_funcalled),Nil,
	    FIX((SI_Long)58L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_time_funcalled),FIX((SI_Long)58L),Funcall_eval_type_6_arg);
    Qis_related = STATIC_SYMBOL("IS-RELATED",AB_package);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)3L,Qsymbol,
	    list_constant_21,list_constant_22);
    Qeval_is_related_funcalled = STATIC_SYMBOL("EVAL-IS-RELATED-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_related_funcalled,
	    STATIC_FUNCTION(eval_is_related_funcalled,NIL,FALSE,3,3));
    Qpprint_is_related_evaluator = 
	    STATIC_SYMBOL("PPRINT-IS-RELATED-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_related_evaluator,
	    STATIC_FUNCTION(pprint_is_related_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qis_related,
	    Qis_related,FIX((SI_Long)1L),Qall,list_constant_53,Qboolean,
	    Qnil,SYMBOL_FUNCTION(Qeval_is_related_funcalled),Nil,
	    FIX((SI_Long)59L),Nil,
	    SYMBOL_FUNCTION(Qpprint_is_related_evaluator),
	    Qeval_is_related_funcalled),FIX((SI_Long)59L),
	    Funcall_eval_type_3_arg);
    Qis_not_related = STATIC_SYMBOL("IS-NOT-RELATED",AB_package);
    Qeval_is_not_related_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-NOT-RELATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_not_related_funcalled,
	    STATIC_FUNCTION(eval_is_not_related_funcalled,NIL,FALSE,3,3));
    Qpprint_is_not_related_evaluator = 
	    STATIC_SYMBOL("PPRINT-IS-NOT-RELATED-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_not_related_evaluator,
	    STATIC_FUNCTION(pprint_is_not_related_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qis_not_related,
	    Qis_not_related,FIX((SI_Long)1L),Qall,list_constant_53,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_is_not_related_funcalled),
	    Nil,FIX((SI_Long)60L),Nil,
	    SYMBOL_FUNCTION(Qpprint_is_not_related_evaluator),
	    Qeval_is_not_related_funcalled),FIX((SI_Long)60L),
	    Funcall_eval_type_3_arg);
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    Qpush_from_surrounding_local_var = 
	    STATIC_SYMBOL("PUSH-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    var_spot_stack_node_converter_1 = 
	    STATIC_FUNCTION(var_spot_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qvar_spot,var_spot_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    Qeval_false_funcalled = STATIC_SYMBOL("EVAL-FALSE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_false_funcalled,
	    STATIC_FUNCTION(eval_false_funcalled,NIL,FALSE,1,1));
    Qpprint_false_evaluator = STATIC_SYMBOL("PPRINT-FALSE-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_false_evaluator,
	    STATIC_FUNCTION(pprint_false_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qfalse,Qfalse,
	    FIX((SI_Long)1L),list_constant_19,list_constant_31,
	    Qtruth_value,Qnil,SYMBOL_FUNCTION(Qeval_false_funcalled),Nil,
	    FIX((SI_Long)61L),Nil,SYMBOL_FUNCTION(Qpprint_false_evaluator),
	    Qeval_false_funcalled),FIX((SI_Long)61L),Funcall_eval_type_1_arg);
    identity_stack_node_converter_1 = 
	    STATIC_FUNCTION(identity_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qidentity,identity_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    attribute_value_stack_node_converter_1 = 
	    STATIC_FUNCTION(attribute_value_stack_node_converter,NIL,FALSE,
	    1,1);
    mutate_global_property(Qattribute_value,
	    attribute_value_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qab_class,Qobject);
    attribute_value_i_chooser_1 = 
	    STATIC_FUNCTION(attribute_value_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qattribute_value,attribute_value_i_chooser_1,
	    Qpreferred_instruction_chooser);
    list_constant_54 = STATIC_CONS(Qitem_or_datum,Qnil);
    list_constant_14 = STATIC_CONS(Qattribute_value,list_constant_54);
    attribute_value_i_emit_1 = STATIC_FUNCTION(attribute_value_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qattribute_value,attribute_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qcall_procedure = STATIC_SYMBOL("CALL-PROCEDURE",AB_package);
    call_procedure_stack_node_converter_1 = 
	    STATIC_FUNCTION(call_procedure_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qcall_procedure,
	    call_procedure_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    string_constant_42 = 
	    string_append2(STATIC_STRING("The first argument to call-function ~\n\t\t\t     must be an item of class ~\n                             function-definition, tabular-function, ~\n                             or "),
	    STATIC_STRING("foreign-function-declaration, ~\n                             but the expression `~NE\' could not ~\n                             refer to such an item."));
    call_function_stack_node_converter_1 = 
	    STATIC_FUNCTION(call_function_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qcall_function,
	    call_function_stack_node_converter_1,
	    Qstack_special_form_converter);
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    list_constant_55 = STATIC_CONS(Qinference,Qnil);
    list_constant_56 = STATIC_CONS(list_constant_3,Qnil);
    Qeval_receives_a_value_funcalled = 
	    STATIC_SYMBOL("EVAL-RECEIVES-A-VALUE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_receives_a_value_funcalled,
	    STATIC_FUNCTION(eval_receives_a_value_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qreceives_a_value,
	    Qreceives_a_value,FIX((SI_Long)1L),list_constant_55,
	    list_constant_56,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_receives_a_value_funcalled),Nil,
	    FIX((SI_Long)62L),Nil,Nil,Qeval_receives_a_value_funcalled),
	    FIX((SI_Long)62L),Funcall_eval_type_1_arg);
    Qfails_to_receive_a_value = STATIC_SYMBOL("FAILS-TO-RECEIVE-A-VALUE",
	    AB_package);
    Qeval_fails_to_receive_a_value_funcalled = 
	    STATIC_SYMBOL("EVAL-FAILS-TO-RECEIVE-A-VALUE-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_fails_to_receive_a_value_funcalled,
	    STATIC_FUNCTION(eval_fails_to_receive_a_value_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qfails_to_receive_a_value,
	    Qfails_to_receive_a_value,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_fails_to_receive_a_value_funcalled),Nil,
	    FIX((SI_Long)63L),Nil,Nil,
	    Qeval_fails_to_receive_a_value_funcalled),FIX((SI_Long)63L),
	    Funcall_eval_type_1_arg);
    Qis_moved = STATIC_SYMBOL("IS-MOVED",AB_package);
    Qeval_is_moved_funcalled = STATIC_SYMBOL("EVAL-IS-MOVED-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_moved_funcalled,
	    STATIC_FUNCTION(eval_is_moved_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_moved,
	    Qis_moved,FIX((SI_Long)1L),list_constant_55,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_is_moved_funcalled),Nil,
	    FIX((SI_Long)64L),Nil,Nil,Qeval_is_moved_funcalled),
	    FIX((SI_Long)64L),Funcall_eval_type_1_arg);
    Qis_moved_by_the_user = STATIC_SYMBOL("IS-MOVED-BY-THE-USER",AB_package);
    Qeval_is_moved_by_the_user_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-MOVED-BY-THE-USER-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_moved_by_the_user_funcalled,
	    STATIC_FUNCTION(eval_is_moved_by_the_user_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_moved_by_the_user,
	    Qis_moved_by_the_user,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_moved_by_the_user_funcalled),Nil,
	    FIX((SI_Long)65L),Nil,Nil,
	    Qeval_is_moved_by_the_user_funcalled),FIX((SI_Long)65L),
	    Funcall_eval_type_1_arg);
    Qis_moved_by_g2 = STATIC_SYMBOL("IS-MOVED-BY-G2",AB_package);
    Qeval_is_moved_by_g2_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-MOVED-BY-G2-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_moved_by_g2_funcalled,
	    STATIC_FUNCTION(eval_is_moved_by_g2_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_moved_by_g2,
	    Qis_moved_by_g2,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_moved_by_g2_funcalled),Nil,
	    FIX((SI_Long)67L),Nil,Nil,Qeval_is_moved_by_g2_funcalled),
	    FIX((SI_Long)67L),Funcall_eval_type_1_arg);
    Qbecomes_related = STATIC_SYMBOL("BECOMES-RELATED",AB_package);
    Qeval_becomes_related_funcalled = 
	    STATIC_SYMBOL("EVAL-BECOMES-RELATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_becomes_related_funcalled,
	    STATIC_FUNCTION(eval_becomes_related_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qbecomes_related,
	    Qbecomes_related,FIX((SI_Long)1L),list_constant_55,
	    list_constant_53,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_becomes_related_funcalled),Nil,
	    FIX((SI_Long)68L),Nil,Nil,Qeval_becomes_related_funcalled),
	    FIX((SI_Long)68L),Funcall_eval_type_3_arg);
    Qceases_to_be_related = STATIC_SYMBOL("CEASES-TO-BE-RELATED",AB_package);
    Qeval_ceases_to_be_related_funcalled = 
	    STATIC_SYMBOL("EVAL-CEASES-TO-BE-RELATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_ceases_to_be_related_funcalled,
	    STATIC_FUNCTION(eval_ceases_to_be_related_funcalled,NIL,FALSE,
	    3,3));
    register_funcalled_evaluator(make_evaluator_description(Qceases_to_be_related,
	    Qceases_to_be_related,FIX((SI_Long)1L),list_constant_55,
	    list_constant_53,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_ceases_to_be_related_funcalled),Nil,
	    FIX((SI_Long)69L),Nil,Nil,
	    Qeval_ceases_to_be_related_funcalled),FIX((SI_Long)69L),
	    Funcall_eval_type_3_arg);
    Qis_activated = STATIC_SYMBOL("IS-ACTIVATED",AB_package);
    Qeval_is_activated_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-ACTIVATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_activated_funcalled,
	    STATIC_FUNCTION(eval_is_activated_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_activated,
	    Qis_activated,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_activated_funcalled),Nil,
	    FIX((SI_Long)10L),Nil,Nil,Qeval_is_activated_funcalled),
	    FIX((SI_Long)10L),Funcall_eval_type_1_arg);
    Qis_deactivated = STATIC_SYMBOL("IS-DEACTIVATED",AB_package);
    Qeval_is_deactivated_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-DEACTIVATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_deactivated_funcalled,
	    STATIC_FUNCTION(eval_is_deactivated_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_deactivated,
	    Qis_deactivated,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_deactivated_funcalled),Nil,
	    FIX((SI_Long)11L),Nil,Nil,Qeval_is_deactivated_funcalled),
	    FIX((SI_Long)11L),Funcall_eval_type_1_arg);
    Qis_enabled = STATIC_SYMBOL("IS-ENABLED",AB_package);
    Qeval_is_enabled_funcalled = STATIC_SYMBOL("EVAL-IS-ENABLED-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_enabled_funcalled,
	    STATIC_FUNCTION(eval_is_enabled_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_enabled,
	    Qis_enabled,FIX((SI_Long)1L),list_constant_55,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_is_enabled_funcalled),Nil,
	    FIX((SI_Long)12L),Nil,Nil,Qeval_is_enabled_funcalled),
	    FIX((SI_Long)12L),Funcall_eval_type_1_arg);
    Qis_disabled = STATIC_SYMBOL("IS-DISABLED",AB_package);
    Qeval_is_disabled_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-DISABLED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_disabled_funcalled,
	    STATIC_FUNCTION(eval_is_disabled_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_disabled,
	    Qis_disabled,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_disabled_funcalled),Nil,
	    FIX((SI_Long)13L),Nil,Nil,Qeval_is_disabled_funcalled),
	    FIX((SI_Long)13L),Funcall_eval_type_1_arg);
    Qloses_its_value = STATIC_SYMBOL("LOSES-ITS-VALUE",AB_package);
    list_constant_57 = STATIC_CONS(list_constant_8,Qnil);
    Qeval_loses_its_value_funcalled = 
	    STATIC_SYMBOL("EVAL-LOSES-ITS-VALUE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_loses_its_value_funcalled,
	    STATIC_FUNCTION(eval_loses_its_value_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qloses_its_value,
	    Qloses_its_value,FIX((SI_Long)1L),list_constant_55,
	    list_constant_57,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_loses_its_value_funcalled),Nil,
	    FIX((SI_Long)14L),Nil,Nil,Qeval_loses_its_value_funcalled),
	    FIX((SI_Long)14L),Funcall_eval_type_1_arg);
    Qis_created = STATIC_SYMBOL("IS-CREATED",AB_package);
    Qeval_is_created_funcalled = STATIC_SYMBOL("EVAL-IS-CREATED-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_created_funcalled,
	    STATIC_FUNCTION(eval_is_created_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_created,
	    Qis_created,FIX((SI_Long)1L),list_constant_55,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_is_created_funcalled),Nil,
	    FIX((SI_Long)15L),Nil,Nil,Qeval_is_created_funcalled),
	    FIX((SI_Long)15L),Funcall_eval_type_1_arg);
    Qgeneric_event = STATIC_SYMBOL("GENERIC-EVENT",AB_package);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    Qsymbol,list_constant_22);
    Qeval_generic_event_funcalled = 
	    STATIC_SYMBOL("EVAL-GENERIC-EVENT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_generic_event_funcalled,
	    STATIC_FUNCTION(eval_generic_event_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qgeneric_event,
	    Qgeneric_event,FIX((SI_Long)1L),list_constant_55,
	    list_constant_58,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_generic_event_funcalled),Nil,
	    FIX((SI_Long)16L),Nil,Nil,Qeval_generic_event_funcalled),
	    FIX((SI_Long)16L),Funcall_eval_type_3_arg);
    Qgeneric_becomes_related = STATIC_SYMBOL("GENERIC-BECOMES-RELATED",
	    AB_package);
    list_constant_59 = STATIC_CONS(list_constant_21,list_constant_22);
    Qeval_generic_becomes_related_funcalled = 
	    STATIC_SYMBOL("EVAL-GENERIC-BECOMES-RELATED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_generic_becomes_related_funcalled,
	    STATIC_FUNCTION(eval_generic_becomes_related_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qgeneric_becomes_related,
	    Qgeneric_becomes_related,FIX((SI_Long)1L),list_constant_55,
	    list_constant_59,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_generic_becomes_related_funcalled),Nil,
	    FIX((SI_Long)17L),Nil,Nil,
	    Qeval_generic_becomes_related_funcalled),FIX((SI_Long)17L),
	    Funcall_eval_type_2_arg);
    Qgeneric_ceases_to_be_related = 
	    STATIC_SYMBOL("GENERIC-CEASES-TO-BE-RELATED",AB_package);
    Qeval_generic_ceases_to_be_related_funcalled = 
	    STATIC_SYMBOL("EVAL-GENERIC-CEASES-TO-BE-RELATED-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_generic_ceases_to_be_related_funcalled,
	    STATIC_FUNCTION(eval_generic_ceases_to_be_related_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qgeneric_ceases_to_be_related,
	    Qgeneric_ceases_to_be_related,FIX((SI_Long)1L),
	    list_constant_55,list_constant_59,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_generic_ceases_to_be_related_funcalled),
	    Nil,FIX((SI_Long)18L),Nil,Nil,
	    Qeval_generic_ceases_to_be_related_funcalled),
	    FIX((SI_Long)18L),Funcall_eval_type_2_arg);
    Qgeneric_directly_connected_to = 
	    STATIC_SYMBOL("GENERIC-DIRECTLY-CONNECTED-TO",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    list_constant_61 = STATIC_CONS(Qsymbol,list_constant_22);
    list_constant_62 = STATIC_CONS(list_constant_60,list_constant_61);
    Qeval_generic_directly_connected_to_funcalled = 
	    STATIC_SYMBOL("EVAL-GENERIC-DIRECTLY-CONNECTED-TO-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_generic_directly_connected_to_funcalled,
	    STATIC_FUNCTION(eval_generic_directly_connected_to_funcalled,
	    NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qgeneric_directly_connected_to,
	    Qgeneric_directly_connected_to,FIX((SI_Long)1L),
	    list_constant_55,list_constant_62,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_generic_directly_connected_to_funcalled),
	    Nil,FIX((SI_Long)19L),Nil,Nil,
	    Qeval_generic_directly_connected_to_funcalled),
	    FIX((SI_Long)19L),Funcall_eval_type_3_arg);
    Qgeneric_directly_disconnected_from = 
	    STATIC_SYMBOL("GENERIC-DIRECTLY-DISCONNECTED-FROM",AB_package);
    Qeval_generic_directly_disconnected_from_funcalled = 
	    STATIC_SYMBOL("EVAL-GENERIC-DIRECTLY-DISCONNECTED-FROM-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_generic_directly_disconnected_from_funcalled,
	    STATIC_FUNCTION(eval_generic_directly_disconnected_from_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qgeneric_directly_disconnected_from,
	    Qgeneric_directly_disconnected_from,FIX((SI_Long)1L),
	    list_constant_55,list_constant_61,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_generic_directly_disconnected_from_funcalled),
	    Nil,FIX((SI_Long)20L),Nil,Nil,
	    Qeval_generic_directly_disconnected_from_funcalled),
	    FIX((SI_Long)20L),Funcall_eval_type_2_arg);
    Qdirectly_connected_to = STATIC_SYMBOL("DIRECTLY-CONNECTED-TO",AB_package);
    Qeval_directly_connected_to_funcalled = 
	    STATIC_SYMBOL("EVAL-DIRECTLY-CONNECTED-TO-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_directly_connected_to_funcalled,
	    STATIC_FUNCTION(eval_directly_connected_to_funcalled,NIL,FALSE,
	    3,3));
    register_funcalled_evaluator(make_evaluator_description(Qdirectly_connected_to,
	    Qdirectly_connected_to,FIX((SI_Long)1L),list_constant_55,
	    list_constant_62,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_directly_connected_to_funcalled),Nil,
	    FIX((SI_Long)21L),Nil,Nil,
	    Qeval_directly_connected_to_funcalled),FIX((SI_Long)21L),
	    Funcall_eval_type_3_arg);
    Qdirectly_disconnected_from = 
	    STATIC_SYMBOL("DIRECTLY-DISCONNECTED-FROM",AB_package);
    list_constant_63 = STATIC_CONS(Qsymbol,list_constant_61);
    Qeval_directly_disconnected_from_funcalled = 
	    STATIC_SYMBOL("EVAL-DIRECTLY-DISCONNECTED-FROM-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_directly_disconnected_from_funcalled,
	    STATIC_FUNCTION(eval_directly_disconnected_from_funcalled,NIL,
	    FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qdirectly_disconnected_from,
	    Qdirectly_disconnected_from,FIX((SI_Long)1L),list_constant_55,
	    list_constant_63,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_directly_disconnected_from_funcalled),
	    Nil,FIX((SI_Long)22L),Nil,Nil,
	    Qeval_directly_disconnected_from_funcalled),FIX((SI_Long)22L),
	    Funcall_eval_type_3_arg);
    Qindirectly_connected_to = STATIC_SYMBOL("INDIRECTLY-CONNECTED-TO",
	    AB_package);
    Qeval_indirectly_connected_to_funcalled = 
	    STATIC_SYMBOL("EVAL-INDIRECTLY-CONNECTED-TO-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_indirectly_connected_to_funcalled,
	    STATIC_FUNCTION(eval_indirectly_connected_to_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qindirectly_connected_to,
	    Qindirectly_connected_to,FIX((SI_Long)1L),list_constant_55,
	    list_constant_59,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_indirectly_connected_to_funcalled),Nil,
	    FIX((SI_Long)23L),Nil,Nil,
	    Qeval_indirectly_connected_to_funcalled),FIX((SI_Long)23L),
	    Funcall_eval_type_2_arg);
    Qindirectly_disconnected_from = 
	    STATIC_SYMBOL("INDIRECTLY-DISCONNECTED-FROM",AB_package);
    Qeval_indirectly_disconnected_from_funcalled = 
	    STATIC_SYMBOL("EVAL-INDIRECTLY-DISCONNECTED-FROM-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_indirectly_disconnected_from_funcalled,
	    STATIC_FUNCTION(eval_indirectly_disconnected_from_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qindirectly_disconnected_from,
	    Qindirectly_disconnected_from,FIX((SI_Long)1L),
	    list_constant_55,list_constant_59,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_indirectly_disconnected_from_funcalled),
	    Nil,FIX((SI_Long)24L),Nil,Nil,
	    Qeval_indirectly_disconnected_from_funcalled),
	    FIX((SI_Long)24L),Funcall_eval_type_2_arg);
    Qnupec_synchronization_occurs = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-OCCURS",AB_package);
    Qeval_nupec_synchronization_occurs_funcalled = 
	    STATIC_SYMBOL("EVAL-NUPEC-SYNCHRONIZATION-OCCURS-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_nupec_synchronization_occurs_funcalled,
	    STATIC_FUNCTION(eval_nupec_synchronization_occurs_funcalled,
	    NIL,FALSE,0,0));
    register_funcalled_evaluator(make_evaluator_description(Qnupec_synchronization_occurs,
	    Qnupec_synchronization_occurs,FIX((SI_Long)1L),
	    list_constant_55,Qnil,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_nupec_synchronization_occurs_funcalled),
	    Nil,FIX((SI_Long)70L),Nil,Nil,
	    Qeval_nupec_synchronization_occurs_funcalled),
	    FIX((SI_Long)70L),Funcall_eval_type_0_arg);
    Qis_of_class = STATIC_SYMBOL("IS-OF-CLASS",AB_package);
    is_of_class_stack_node_converter_1 = 
	    STATIC_FUNCTION(is_of_class_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qis_of_class,is_of_class_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_43 = 
	    STATIC_STRING("In the expression ~NA IS A ~s, ~s is not a class name or type.");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qitem_or_datum,Qsymbol);
    Qeval_is_of_class_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-OF-CLASS-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_of_class_funcalled,
	    STATIC_FUNCTION(eval_is_of_class_funcalled,NIL,FALSE,2,2));
    Qpprint_is_of_class_evaluator = 
	    STATIC_SYMBOL("PPRINT-IS-OF-CLASS-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_of_class_evaluator,
	    STATIC_FUNCTION(pprint_is_of_class_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qis_of_class,
	    Qis_of_class,FIX((SI_Long)1L),Qall,list_constant_64,Qboolean,
	    Qnil,SYMBOL_FUNCTION(Qeval_is_of_class_funcalled),Nil,
	    FIX((SI_Long)71L),Nil,
	    SYMBOL_FUNCTION(Qpprint_is_of_class_evaluator),
	    Qeval_is_of_class_funcalled),FIX((SI_Long)71L),
	    Funcall_eval_type_2_arg);
    Qis_active = STATIC_SYMBOL("IS-ACTIVE",AB_package);
    Qeval_is_active_funcalled = STATIC_SYMBOL("EVAL-IS-ACTIVE-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_active_funcalled,
	    STATIC_FUNCTION(eval_is_active_funcalled,NIL,FALSE,1,1));
    Qpprint_is_active_evaluator = 
	    STATIC_SYMBOL("PPRINT-IS-ACTIVE-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_is_active_evaluator,
	    STATIC_FUNCTION(pprint_is_active_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qis_active,
	    Qis_active,FIX((SI_Long)1L),list_constant_19,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_is_active_funcalled),Nil,
	    FIX((SI_Long)72L),Nil,
	    SYMBOL_FUNCTION(Qpprint_is_active_evaluator),
	    Qeval_is_active_funcalled),FIX((SI_Long)72L),
	    Funcall_eval_type_1_arg);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qhas_a_name = STATIC_SYMBOL("HAS-A-NAME",AB_package);
    Qeval_has_a_name_funcalled = STATIC_SYMBOL("EVAL-HAS-A-NAME-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_has_a_name_funcalled,
	    STATIC_FUNCTION(eval_has_a_name_funcalled,NIL,FALSE,1,1));
    Qpprint_has_a_name_evaluator = 
	    STATIC_SYMBOL("PPRINT-HAS-A-NAME-EVALUATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_has_a_name_evaluator,
	    STATIC_FUNCTION(pprint_has_a_name_evaluator,NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qhas_a_name,
	    Qhas_a_name,FIX((SI_Long)1L),list_constant_19,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_has_a_name_funcalled),Nil,
	    FIX((SI_Long)73L),Nil,
	    SYMBOL_FUNCTION(Qpprint_has_a_name_evaluator),
	    Qeval_has_a_name_funcalled),FIX((SI_Long)73L),
	    Funcall_eval_type_1_arg);
    string_constant_44 = STATIC_STRING("CONNECTION-PORTNAME");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qconnection_portname = STATIC_SYMBOL("CONNECTION-PORTNAME",AB_package);
    list_constant_65 = STATIC_LIST((SI_Long)2L,list_constant_21,
	    list_constant_60);
    Qeval_connection_portname_funcalled = 
	    STATIC_SYMBOL("EVAL-CONNECTION-PORTNAME-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_connection_portname_funcalled,
	    STATIC_FUNCTION(eval_connection_portname_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qconnection_portname,
	    Qconnection_portname,FIX((SI_Long)1L),Qall,list_constant_65,
	    Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qeval_connection_portname_funcalled),Nil,
	    FIX((SI_Long)74L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_connection_portname_funcalled),FIX((SI_Long)74L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qconnection_portname,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_45 = STATIC_STRING("CONNECTION-SIDE");
    array_constant_2 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant_2,(SI_Long)0L,Qtop);
    ISASET_1(array_constant_2,(SI_Long)1L,Qleft);
    ISASET_1(array_constant_2,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant_2,(SI_Long)3L,Qright);
    Qconnection_side = STATIC_SYMBOL("CONNECTION-SIDE",AB_package);
    Qeval_connection_side_funcalled = 
	    STATIC_SYMBOL("EVAL-CONNECTION-SIDE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_connection_side_funcalled,
	    STATIC_FUNCTION(eval_connection_side_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qconnection_side,
	    Qconnection_side,FIX((SI_Long)1L),Qall,list_constant_65,
	    Qsymbol,Qnil,SYMBOL_FUNCTION(Qeval_connection_side_funcalled),
	    Nil,FIX((SI_Long)75L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_connection_side_funcalled),FIX((SI_Long)75L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qconnection_side,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_46 = STATIC_STRING("CONNECTION-POSITION");
    Qconnection_position = STATIC_SYMBOL("CONNECTION-POSITION",AB_package);
    Qeval_connection_position_funcalled = 
	    STATIC_SYMBOL("EVAL-CONNECTION-POSITION-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_connection_position_funcalled,
	    STATIC_FUNCTION(eval_connection_position_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qconnection_position,
	    Qconnection_position,FIX((SI_Long)1L),Qall,list_constant_65,
	    Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_connection_position_funcalled),Nil,
	    FIX((SI_Long)76L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_connection_position_funcalled),FIX((SI_Long)76L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qconnection_position,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_47 = STATIC_STRING("CONNECTION-DIRECTION");
    Qconnection_direction = STATIC_SYMBOL("CONNECTION-DIRECTION",AB_package);
    Qeval_connection_direction_funcalled = 
	    STATIC_SYMBOL("EVAL-CONNECTION-DIRECTION-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_connection_direction_funcalled,
	    STATIC_FUNCTION(eval_connection_direction_funcalled,NIL,FALSE,
	    2,2));
    register_funcalled_evaluator(make_evaluator_description(Qconnection_direction,
	    Qconnection_direction,FIX((SI_Long)1L),Qall,list_constant_65,
	    Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qeval_connection_direction_funcalled),Nil,
	    FIX((SI_Long)77L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_connection_direction_funcalled),FIX((SI_Long)77L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qconnection_direction,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    list_constant_66 = STATIC_CONS(list_constant_60,Qnil);
    Qeval_connection_style_funcalled = 
	    STATIC_SYMBOL("EVAL-CONNECTION-STYLE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_connection_style_funcalled,
	    STATIC_FUNCTION(eval_connection_style_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qconnection_style,
	    Qconnection_style,FIX((SI_Long)1L),Qall,list_constant_66,
	    Qsymbol,Qnil,SYMBOL_FUNCTION(Qeval_connection_style_funcalled),
	    Nil,FIX((SI_Long)78L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_connection_style_funcalled),FIX((SI_Long)78L),
	    Funcall_eval_type_1_arg);
    mutate_global_or_kb_specific_property_value(Qconnection_style,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    string_constant_48 = 
	    STATIC_STRING("The first argument to ~a was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    string_constant_49 = 
	    STATIC_STRING("The connection argument to ~a was a connection which is not ~\n        connected to the block. The connection was ~NF.");
    string_constant_50 = 
	    STATIC_STRING("The first argument to items-are-connected was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    string_constant_51 = 
	    STATIC_STRING("The second argument to items-are-connected was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    Qitems_are_connected = STATIC_SYMBOL("ITEMS-ARE-CONNECTED",AB_package);
    Qeval_items_are_connected_funcalled = 
	    STATIC_SYMBOL("EVAL-ITEMS-ARE-CONNECTED-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_items_are_connected_funcalled,
	    STATIC_FUNCTION(eval_items_are_connected_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qitems_are_connected,
	    Qitems_are_connected,FIX((SI_Long)1L),Qall,list_constant_59,
	    Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_items_are_connected_funcalled),Nil,
	    FIX((SI_Long)134L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_items_are_connected_funcalled),FIX((SI_Long)134L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qitems_are_connected,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_52 = 
	    STATIC_STRING("The first argument to items-are-connected-with-direction was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    string_constant_53 = 
	    STATIC_STRING("The second argument to items-are-connected-with-direction was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    string_constant_54 = 
	    STATIC_STRING("The third argument to items-are-connected-with-direction was ~NF.  It has to be either input or output.");
    Qitems_are_connected_with_direction = 
	    STATIC_SYMBOL("ITEMS-ARE-CONNECTED-WITH-DIRECTION",AB_package);
    list_constant_67 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    list_constant_21,list_constant_67);
    Qeval_items_are_connected_with_direction_funcalled = 
	    STATIC_SYMBOL("EVAL-ITEMS-ARE-CONNECTED-WITH-DIRECTION-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_items_are_connected_with_direction_funcalled,
	    STATIC_FUNCTION(eval_items_are_connected_with_direction_funcalled,
	    NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qitems_are_connected_with_direction,
	    Qitems_are_connected_with_direction,FIX((SI_Long)1L),Qall,
	    list_constant_68,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_items_are_connected_with_direction_funcalled),
	    Nil,FIX((SI_Long)135L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_items_are_connected_with_direction_funcalled),
	    FIX((SI_Long)135L),Funcall_eval_type_3_arg);
    mutate_global_or_kb_specific_property_value(Qitems_are_connected_with_direction,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    string_constant_55 = 
	    STATIC_STRING("The first argument to items-are-connected-at-ports was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    string_constant_56 = 
	    STATIC_STRING("The second argument to items-are-connected-at-ports was an item which was not a block ~\n        so it has no connections.  The argument was ~NF.");
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qport_names = STATIC_SYMBOL("PORT-NAMES",AB_package);
    Qitems_are_connected_at_ports = 
	    STATIC_SYMBOL("ITEMS-ARE-CONNECTED-AT-PORTS",AB_package);
    list_constant_69 = STATIC_LIST_STAR((SI_Long)4L,list_constant_21,
	    list_constant_21,Qsymbol,list_constant_67);
    Qeval_items_are_connected_at_ports_funcalled = 
	    STATIC_SYMBOL("EVAL-ITEMS-ARE-CONNECTED-AT-PORTS-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_items_are_connected_at_ports_funcalled,
	    STATIC_FUNCTION(eval_items_are_connected_at_ports_funcalled,
	    NIL,FALSE,4,4));
    register_funcalled_evaluator(make_evaluator_description(Qitems_are_connected_at_ports,
	    Qitems_are_connected_at_ports,FIX((SI_Long)1L),Qall,
	    list_constant_69,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_items_are_connected_at_ports_funcalled),
	    Nil,FIX((SI_Long)136L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_items_are_connected_at_ports_funcalled),
	    FIX((SI_Long)136L),Funcall_eval_type_4_arg);
    mutate_global_or_kb_specific_property_value(Qitems_are_connected_at_ports,
	    FIX((SI_Long)4L),Argument_range_gkbprop);
    Qfocal_objects = STATIC_SYMBOL("FOCAL-OBJECTS",AB_package);
    Qwhich_has_the_focal_object = 
	    STATIC_SYMBOL("WHICH-HAS-THE-FOCAL-OBJECT",AB_package);
    Qprocedures = STATIC_SYMBOL("PROCEDURES",AB_package);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qinference,Qprocedures);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qab_class,Qrule);
    list_constant_72 = STATIC_CONS(list_constant_70,list_constant_67);
    Qeval_which_has_the_focal_object_funcalled = 
	    STATIC_SYMBOL("EVAL-WHICH-HAS-THE-FOCAL-OBJECT-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_which_has_the_focal_object_funcalled,
	    STATIC_FUNCTION(eval_which_has_the_focal_object_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qwhich_has_the_focal_object,
	    Qwhich_has_the_focal_object,FIX((SI_Long)1L),list_constant_71,
	    list_constant_72,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_which_has_the_focal_object_funcalled),
	    Nil,FIX((SI_Long)80L),Nil,Nil,
	    Qeval_which_has_the_focal_object_funcalled),FIX((SI_Long)80L),
	    Funcall_eval_type_2_arg);
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    Qwhich_has_the_focal_class = STATIC_SYMBOL("WHICH-HAS-THE-FOCAL-CLASS",
	    AB_package);
    Qeval_which_has_the_focal_class_funcalled = 
	    STATIC_SYMBOL("EVAL-WHICH-HAS-THE-FOCAL-CLASS-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_which_has_the_focal_class_funcalled,
	    STATIC_FUNCTION(eval_which_has_the_focal_class_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qwhich_has_the_focal_class,
	    Qwhich_has_the_focal_class,FIX((SI_Long)1L),list_constant_71,
	    list_constant_72,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_which_has_the_focal_class_funcalled),Nil,
	    FIX((SI_Long)81L),Nil,Nil,
	    Qeval_which_has_the_focal_class_funcalled),FIX((SI_Long)81L),
	    Funcall_eval_type_2_arg);
    Qrule_categories = STATIC_SYMBOL("RULE-CATEGORIES",AB_package);
    Qin_the_category = STATIC_SYMBOL("IN-THE-CATEGORY",AB_package);
    Qeval_in_the_category_funcalled = 
	    STATIC_SYMBOL("EVAL-IN-THE-CATEGORY-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_in_the_category_funcalled,
	    STATIC_FUNCTION(eval_in_the_category_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qin_the_category,
	    Qin_the_category,FIX((SI_Long)1L),list_constant_55,
	    list_constant_72,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_in_the_category_funcalled),Nil,
	    FIX((SI_Long)82L),Nil,Nil,Qeval_in_the_category_funcalled),
	    FIX((SI_Long)82L),Funcall_eval_type_2_arg);
    Qwith_status = STATIC_SYMBOL("WITH-STATUS",AB_package);
    list_constant_73 = STATIC_CONS(list_constant_21,list_constant_67);
    Qeval_with_status_funcalled = 
	    STATIC_SYMBOL("EVAL-WITH-STATUS-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_with_status_funcalled,
	    STATIC_FUNCTION(eval_with_status_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qwith_status,
	    Qwith_status,FIX((SI_Long)1L),list_constant_71,
	    list_constant_73,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_with_status_funcalled),Nil,
	    FIX((SI_Long)83L),Nil,Nil,Qeval_with_status_funcalled),
	    FIX((SI_Long)83L),Funcall_eval_type_2_arg);
    Qwith_notes = STATIC_SYMBOL("WITH-NOTES",AB_package);
    Qeval_with_notes_funcalled = STATIC_SYMBOL("EVAL-WITH-NOTES-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_with_notes_funcalled,
	    STATIC_FUNCTION(eval_with_notes_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qwith_notes,
	    Qwith_notes,FIX((SI_Long)1L),list_constant_71,list_constant_22,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_with_notes_funcalled),Nil,
	    FIX((SI_Long)84L),Nil,Nil,Qeval_with_notes_funcalled),
	    FIX((SI_Long)84L),Funcall_eval_type_1_arg);
    Qcontaining = STATIC_SYMBOL("CONTAINING",AB_package);
    list_constant_74 = STATIC_CONS(list_constant_21,list_constant_50);
    Qeval_containing_funcalled = STATIC_SYMBOL("EVAL-CONTAINING-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_containing_funcalled,
	    STATIC_FUNCTION(eval_containing_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qcontaining,
	    Qcontaining,FIX((SI_Long)1L),list_constant_71,list_constant_74,
	    Qboolean,Qnil,SYMBOL_FUNCTION(Qeval_containing_funcalled),Nil,
	    FIX((SI_Long)85L),Nil,Nil,Qeval_containing_funcalled),
	    FIX((SI_Long)85L),Funcall_eval_type_2_arg);
    Qcontaining_word = STATIC_SYMBOL("CONTAINING-WORD",AB_package);
    Qeval_containing_word_funcalled = 
	    STATIC_SYMBOL("EVAL-CONTAINING-WORD-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_containing_word_funcalled,
	    STATIC_FUNCTION(eval_containing_word_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qcontaining_word,
	    Qcontaining_word,FIX((SI_Long)1L),list_constant_71,
	    list_constant_74,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_containing_word_funcalled),Nil,
	    FIX((SI_Long)86L),Nil,Nil,Qeval_containing_word_funcalled),
	    FIX((SI_Long)86L),Funcall_eval_type_2_arg);
    Qcontaining_symbol = STATIC_SYMBOL("CONTAINING-SYMBOL",AB_package);
    Qeval_containing_symbol_funcalled = 
	    STATIC_SYMBOL("EVAL-CONTAINING-SYMBOL-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_containing_symbol_funcalled,
	    STATIC_FUNCTION(eval_containing_symbol_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qcontaining_symbol,
	    Qcontaining_symbol,FIX((SI_Long)1L),list_constant_71,
	    list_constant_74,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_containing_symbol_funcalled),Nil,
	    FIX((SI_Long)97L),Nil,Nil,Qeval_containing_symbol_funcalled),
	    FIX((SI_Long)97L),Funcall_eval_type_2_arg);
    Qname_for_debugging = STATIC_SYMBOL("NAME-FOR-DEBUGGING",AB_package);
    Qg2_inspect_internal_name_for_debugging_p = 
	    STATIC_SYMBOL("G2-INSPECT-INTERNAL-NAME-FOR-DEBUGGING-P",
	    AB_package);
    Qeval_g2_inspect_internal_name_for_debugging_p_funcalled = 
	    STATIC_SYMBOL("EVAL-G2-INSPECT-INTERNAL-NAME-FOR-DEBUGGING-P-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_g2_inspect_internal_name_for_debugging_p_funcalled,
	    STATIC_FUNCTION(eval_g2_inspect_internal_name_for_debugging_p_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qg2_inspect_internal_name_for_debugging_p,
	    Qg2_inspect_internal_name_for_debugging_p,FIX((SI_Long)1L),
	    list_constant_71,list_constant_74,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_g2_inspect_internal_name_for_debugging_p_funcalled),
	    Nil,FIX((SI_Long)87L),Nil,Nil,
	    Qeval_g2_inspect_internal_name_for_debugging_p_funcalled),
	    FIX((SI_Long)87L),Funcall_eval_type_2_arg);
    Qassigned_to_module = STATIC_SYMBOL("ASSIGNED-TO-MODULE",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)3L,list_constant_21,Qsymbol,
	    Qboolean);
    Qeval_assigned_to_module_funcalled = 
	    STATIC_SYMBOL("EVAL-ASSIGNED-TO-MODULE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_assigned_to_module_funcalled,
	    STATIC_FUNCTION(eval_assigned_to_module_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qassigned_to_module,
	    Qassigned_to_module,FIX((SI_Long)1L),list_constant_71,
	    list_constant_75,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_assigned_to_module_funcalled),Nil,
	    FIX((SI_Long)88L),Nil,Nil,Qeval_assigned_to_module_funcalled),
	    FIX((SI_Long)88L),Funcall_eval_type_3_arg);
    Qwith_changes_logged_2 = STATIC_SYMBOL("WITH-CHANGES-LOGGED-2",AB_package);
    list_constant_76 = STATIC_CONS(Qinteger,list_constant_31);
    list_constant_77 = STATIC_CONS(Qab_or,list_constant_76);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_31);
    list_constant_79 = STATIC_LIST((SI_Long)4L,list_constant_21,
	    list_constant_77,list_constant_77,list_constant_78);
    Qeval_with_changes_logged_2_funcalled = 
	    STATIC_SYMBOL("EVAL-WITH-CHANGES-LOGGED-2-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_with_changes_logged_2_funcalled,
	    STATIC_FUNCTION(eval_with_changes_logged_2_funcalled,NIL,FALSE,
	    4,4));
    register_funcalled_evaluator(make_evaluator_description(Qwith_changes_logged_2,
	    Qwith_changes_logged_2,FIX((SI_Long)1L),list_constant_71,
	    list_constant_79,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_with_changes_logged_2_funcalled),Nil,
	    FIX((SI_Long)149L),Nil,Nil,
	    Qeval_with_changes_logged_2_funcalled),FIX((SI_Long)149L),
	    Funcall_eval_type_4_arg);
    Qcoerce_no_item_to_unknown = STATIC_SYMBOL("COERCE-NO-ITEM-TO-UNKNOWN",
	    AB_package);
    Qfuncall_coerce_no_item_to_unknown_inst = 
	    STATIC_SYMBOL("FUNCALL-COERCE-NO-ITEM-TO-UNKNOWN-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_coerce_no_item_to_unknown_inst,
	    STATIC_FUNCTION(funcall_coerce_no_item_to_unknown_inst,NIL,
	    FALSE,2,2));
    make_and_register_funcalled_instruction_description(Qcoerce_no_item_to_unknown,
	    FIX((SI_Long)68L),Qall,FIX((SI_Long)1L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_coerce_no_item_to_unknown_inst),Qnil,
	    Nil,Qfuncall_coerce_no_item_to_unknown_inst);
    array_constant_3 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    string_constant_57 = 
	    STATIC_STRING(" given to the operator ~a is out of bounds of ~\n                  the empty text.");
    string_constant_58 = 
	    STATIC_STRING(" given to the operator ~a is out of bounds of the ~\n                   text \"~a\", which has length ~d.");
    string_constant_59 = 
	    STATIC_STRING("The ~a operator cannot return a text containing ~\n         more than ~a characters.  The text arguments began with ~\n         \"~a...\" and \"~a...\".");
    Qbitwise_and = STATIC_SYMBOL("BITWISE-AND",AB_package);
    Qeval_bitwise_and_in_line = STATIC_SYMBOL("EVAL-BITWISE-AND-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qbitwise_and,
	    Qbitwise_and,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Nil,Qeval_bitwise_and_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)52L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)52L));
    mutate_global_or_kb_specific_property_value(Qbitwise_and,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qbitwise_or = STATIC_SYMBOL("BITWISE-OR",AB_package);
    Qeval_bitwise_or_in_line = STATIC_SYMBOL("EVAL-BITWISE-OR-IN-LINE",
	    AB_package);
    register_in_line_evaluator(make_evaluator_description(Qbitwise_or,
	    Qbitwise_or,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Nil,Qeval_bitwise_or_in_line,T,
	    FIX(IFIX(Base_in_line_evaluator_number) + (SI_Long)53L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),Nil),
	    FIX((SI_Long)53L));
    mutate_global_or_kb_specific_property_value(Qbitwise_or,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qbitwise_not = STATIC_SYMBOL("BITWISE-NOT",AB_package);
    Qeval_bitwise_not_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-NOT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_not_funcalled,
	    STATIC_FUNCTION(eval_bitwise_not_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_not,
	    Qbitwise_not,FIX((SI_Long)1L),Qall,list_constant_24,Qinteger,
	    Qnil,SYMBOL_FUNCTION(Qeval_bitwise_not_funcalled),Nil,
	    FIX((SI_Long)89L),Nil,Nil,Qeval_bitwise_not_funcalled),
	    FIX((SI_Long)89L),Funcall_eval_type_1_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_not,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qbitwise_xor = STATIC_SYMBOL("BITWISE-XOR",AB_package);
    Qeval_bitwise_xor_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-XOR-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_xor_funcalled,
	    STATIC_FUNCTION(eval_bitwise_xor_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_xor,
	    Qbitwise_xor,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Qnil,SYMBOL_FUNCTION(Qeval_bitwise_xor_funcalled),Nil,
	    FIX((SI_Long)90L),Nil,Nil,Qeval_bitwise_xor_funcalled),
	    FIX((SI_Long)90L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_xor,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qbitwise_right_shift = STATIC_SYMBOL("BITWISE-RIGHT-SHIFT",AB_package);
    Qeval_bitwise_right_shift_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-RIGHT-SHIFT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_right_shift_funcalled,
	    STATIC_FUNCTION(eval_bitwise_right_shift_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_right_shift,
	    Qbitwise_right_shift,FIX((SI_Long)1L),Qall,list_constant_28,
	    Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_bitwise_right_shift_funcalled),Nil,
	    FIX((SI_Long)91L),Nil,Nil,Qeval_bitwise_right_shift_funcalled),
	    FIX((SI_Long)91L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_right_shift,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qbitwise_left_shift = STATIC_SYMBOL("BITWISE-LEFT-SHIFT",AB_package);
    Qeval_bitwise_left_shift_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-LEFT-SHIFT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_left_shift_funcalled,
	    STATIC_FUNCTION(eval_bitwise_left_shift_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_left_shift,
	    Qbitwise_left_shift,FIX((SI_Long)1L),Qall,list_constant_28,
	    Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_bitwise_left_shift_funcalled),Nil,
	    FIX((SI_Long)92L),Nil,Nil,Qeval_bitwise_left_shift_funcalled),
	    FIX((SI_Long)92L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_left_shift,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_60 = 
	    STATIC_STRING("Desired test index ~a is outside the range 0-29");
    Qbitwise_test = STATIC_SYMBOL("BITWISE-TEST",AB_package);
    Qeval_bitwise_test_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-TEST-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_test_funcalled,
	    STATIC_FUNCTION(eval_bitwise_test_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_test,
	    Qbitwise_test,FIX((SI_Long)1L),Qall,list_constant_28,Qboolean,
	    Qnil,SYMBOL_FUNCTION(Qeval_bitwise_test_funcalled),Nil,
	    FIX((SI_Long)93L),Nil,Nil,Qeval_bitwise_test_funcalled),
	    FIX((SI_Long)93L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_test,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    string_constant_61 = 
	    STATIC_STRING("Desired set index ~a is outside the range 0-28");
    Qbitwise_set = STATIC_SYMBOL("BITWISE-SET",AB_package);
    Qeval_bitwise_set_funcalled = 
	    STATIC_SYMBOL("EVAL-BITWISE-SET-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_bitwise_set_funcalled,
	    STATIC_FUNCTION(eval_bitwise_set_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qbitwise_set,
	    Qbitwise_set,FIX((SI_Long)1L),Qall,list_constant_28,Qinteger,
	    Qnil,SYMBOL_FUNCTION(Qeval_bitwise_set_funcalled),Nil,
	    FIX((SI_Long)94L),Nil,Nil,Qeval_bitwise_set_funcalled),
	    FIX((SI_Long)94L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qbitwise_set,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qlatitude = STATIC_SYMBOL("LATITUDE",AB_package);
    Qgreat_circle_distance = STATIC_SYMBOL("GREAT-CIRCLE-DISTANCE",AB_package);
    Qlongitude = STATIC_SYMBOL("LONGITUDE",AB_package);
    Qradius = STATIC_SYMBOL("RADIUS",AB_package);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)4L,Qfloat,Qfloat,Qfloat,
	    list_constant_26);
    Qeval_great_circle_distance_funcalled = 
	    STATIC_SYMBOL("EVAL-GREAT-CIRCLE-DISTANCE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_great_circle_distance_funcalled,
	    STATIC_FUNCTION(eval_great_circle_distance_funcalled,NIL,FALSE,
	    5,5));
    register_funcalled_evaluator(make_evaluator_description(Qgreat_circle_distance,
	    Qgreat_circle_distance,FIX((SI_Long)1L),list_constant_19,
	    list_constant_80,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_great_circle_distance_funcalled),Nil,
	    FIX((SI_Long)120L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_great_circle_distance_funcalled),FIX((SI_Long)120L),
	    Funcall_eval_type_5_arg);
    Qcolor_value = STATIC_SYMBOL("COLOR-VALUE",AB_package);
    Qrgb_symbol = STATIC_SYMBOL("RGB-SYMBOL",AB_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    string_constant_62 = STATIC_STRING("RGB~c~c~c~c~c~c");
    list_constant_81 = STATIC_CONS(Qinteger,list_constant_28);
    Qeval_rgb_symbol_funcalled = STATIC_SYMBOL("EVAL-RGB-SYMBOL-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_rgb_symbol_funcalled,
	    STATIC_FUNCTION(eval_rgb_symbol_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qrgb_symbol,
	    Qrgb_symbol,FIX((SI_Long)1L),list_constant_19,list_constant_81,
	    Qsymbol,Qnil,SYMBOL_FUNCTION(Qeval_rgb_symbol_funcalled),Nil,
	    FIX((SI_Long)122L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_rgb_symbol_funcalled),FIX((SI_Long)122L),
	    Funcall_eval_type_3_arg);
    array_constant_4 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    Qclass_qualified_name_frame_or_place_reference = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE",
	    AB_package);
    Qfuncall_class_qualified_name_frame_or_place_reference_inst = 
	    STATIC_SYMBOL("FUNCALL-CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_class_qualified_name_frame_or_place_reference_inst,
	    STATIC_FUNCTION(funcall_class_qualified_name_frame_or_place_reference_inst,
	    NIL,FALSE,2,2));
    Qpprint_cqn_frame_or_place_reference_instruction = 
	    STATIC_SYMBOL("PPRINT-CQN-FRAME-OR-PLACE-REFERENCE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_cqn_frame_or_place_reference_instruction,
	    STATIC_FUNCTION(pprint_cqn_frame_or_place_reference_instruction,
	    NIL,FALSE,6,6));
    make_and_register_funcalled_instruction_description(Qclass_qualified_name_frame_or_place_reference,
	    FIX((SI_Long)76L),Qall,FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_class_qualified_name_frame_or_place_reference_inst),
	    Qnil,
	    SYMBOL_FUNCTION(Qpprint_cqn_frame_or_place_reference_instruction),
	    Qfuncall_class_qualified_name_frame_or_place_reference_inst);
    sequence_stack_node_converter_1 = 
	    STATIC_FUNCTION(sequence_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qsequence,sequence_stack_node_converter_1,
	    Qstack_special_form_converter);
    sequence_i_chooser_1 = STATIC_FUNCTION(sequence_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qsequence,sequence_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qmake_evaluation_sequence = STATIC_SYMBOL("MAKE-EVALUATION-SEQUENCE",
	    AB_package);
    sequence_i_emit_1 = STATIC_FUNCTION(sequence_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qsequence,sequence_i_emit_1,
	    Qstack_node_instruction_emitter);
    array_constant_7 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    list_constant_82 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_83 = STATIC_LIST((SI_Long)3L,Qplus,list_constant_82,
	    FIX((SI_Long)1L));
    Qfuncall_make_evaluation_sequence_inst = 
	    STATIC_SYMBOL("FUNCALL-MAKE-EVALUATION-SEQUENCE-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_make_evaluation_sequence_inst,
	    STATIC_FUNCTION(funcall_make_evaluation_sequence_inst,NIL,
	    FALSE,2,2));
    Qpprint_make_evaluation_sequence_instruction = 
	    STATIC_SYMBOL("PPRINT-MAKE-EVALUATION-SEQUENCE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_make_evaluation_sequence_instruction,
	    STATIC_FUNCTION(pprint_make_evaluation_sequence_instruction,
	    NIL,FALSE,8,8));
    make_and_register_funcalled_instruction_description(Qmake_evaluation_sequence,
	    FIX((SI_Long)78L),Qall,list_constant_83,FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_make_evaluation_sequence_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_make_evaluation_sequence_instruction),
	    Qfuncall_make_evaluation_sequence_inst);
    Qevaluated_structure = STATIC_SYMBOL("EVALUATED-STRUCTURE",AB_package);
    evaluated_structure_stack_node_converter_1 = 
	    STATIC_FUNCTION(evaluated_structure_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qevaluated_structure,
	    evaluated_structure_stack_node_converter_1,
	    Qstack_special_form_converter);
    string_constant_63 = 
	    STATIC_STRING("Evaluated-structure requires an even number of arguments, it received ~a.");
    evaluated_structure_i_chooser_1 = 
	    STATIC_FUNCTION(evaluated_structure_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qevaluated_structure,
	    evaluated_structure_i_chooser_1,Qpreferred_instruction_chooser);
    Qmake_evaluated_structure = STATIC_SYMBOL("MAKE-EVALUATED-STRUCTURE",
	    AB_package);
    evaluated_structure_i_emit_1 = 
	    STATIC_FUNCTION(evaluated_structure_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qevaluated_structure,
	    evaluated_structure_i_emit_1,Qstack_node_instruction_emitter);
    array_constant_9 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)57344L);
    Qfuncall_make_evaluated_structure_inst = 
	    STATIC_SYMBOL("FUNCALL-MAKE-EVALUATED-STRUCTURE-INST",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_make_evaluated_structure_inst,
	    STATIC_FUNCTION(funcall_make_evaluated_structure_inst,NIL,
	    FALSE,2,2));
    Qpprint_make_evaluated_structure_instruction = 
	    STATIC_SYMBOL("PPRINT-MAKE-EVALUATED-STRUCTURE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_make_evaluated_structure_instruction,
	    STATIC_FUNCTION(pprint_make_evaluated_structure_instruction,
	    NIL,FALSE,8,8));
    make_and_register_funcalled_instruction_description(Qmake_evaluated_structure,
	    FIX((SI_Long)79L),Qall,list_constant_83,FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_make_evaluated_structure_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_make_evaluated_structure_instruction),
	    Qfuncall_make_evaluated_structure_inst);
    string_constant_64 = 
	    STATIC_STRING("~NA, element ~d of sequence ~NA, is not an integer ~\n                       between 0 and 65535, and therefore not a valid ~\n                       character code.");
    string_constant_65 = 
	    STATIC_STRING("The character-codes-to-text function cannot return a text containing ~\n                     more than ~d characters; the argument sequence had ~d elements");
    Qcharacter_codes_to_text = STATIC_SYMBOL("CHARACTER-CODES-TO-TEXT",
	    AB_package);
    list_constant_84 = STATIC_CONS(list_constant_15,Qnil);
    Qeval_character_codes_to_text_funcalled = 
	    STATIC_SYMBOL("EVAL-CHARACTER-CODES-TO-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_character_codes_to_text_funcalled,
	    STATIC_FUNCTION(eval_character_codes_to_text_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qcharacter_codes_to_text,
	    Qcharacter_codes_to_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_84,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_character_codes_to_text_funcalled),Nil,
	    FIX((SI_Long)100L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_character_codes_to_text_funcalled),FIX((SI_Long)100L),
	    Funcall_eval_type_1_arg);
    Qtext_to_character_codes = STATIC_SYMBOL("TEXT-TO-CHARACTER-CODES",
	    AB_package);
    Qeval_text_to_character_codes_funcalled = 
	    STATIC_SYMBOL("EVAL-TEXT-TO-CHARACTER-CODES-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_text_to_character_codes_funcalled,
	    STATIC_FUNCTION(eval_text_to_character_codes_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qtext_to_character_codes,
	    Qtext_to_character_codes,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_text_to_character_codes_funcalled),Nil,
	    FIX((SI_Long)101L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_text_to_character_codes_funcalled),FIX((SI_Long)101L),
	    Funcall_eval_type_1_arg);
    string_constant_66 = 
	    STATIC_STRING("~NA is not an integer ~\n          between 0 and 65535, and therefore not a valid ~\n          character code.");
    Qis_uppercase = STATIC_SYMBOL("IS-UPPERCASE",AB_package);
    Qeval_is_uppercase_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-UPPERCASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_uppercase_funcalled,
	    STATIC_FUNCTION(eval_is_uppercase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_uppercase,
	    Qis_uppercase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_uppercase_funcalled),Nil,
	    FIX((SI_Long)102L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_uppercase_funcalled),FIX((SI_Long)102L),
	    Funcall_eval_type_1_arg);
    Qis_titlecase = STATIC_SYMBOL("IS-TITLECASE",AB_package);
    Qeval_is_titlecase_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-TITLECASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_titlecase_funcalled,
	    STATIC_FUNCTION(eval_is_titlecase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_titlecase,
	    Qis_titlecase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_titlecase_funcalled),Nil,
	    FIX((SI_Long)103L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_titlecase_funcalled),FIX((SI_Long)103L),
	    Funcall_eval_type_1_arg);
    Qis_lowercase = STATIC_SYMBOL("IS-LOWERCASE",AB_package);
    Qeval_is_lowercase_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-LOWERCASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_lowercase_funcalled,
	    STATIC_FUNCTION(eval_is_lowercase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_lowercase,
	    Qis_lowercase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_lowercase_funcalled),Nil,
	    FIX((SI_Long)104L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_lowercase_funcalled),FIX((SI_Long)104L),
	    Funcall_eval_type_1_arg);
    Qto_uppercase = STATIC_SYMBOL("TO-UPPERCASE",AB_package);
    Qeval_to_uppercase_funcalled = 
	    STATIC_SYMBOL("EVAL-TO-UPPERCASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_to_uppercase_funcalled,
	    STATIC_FUNCTION(eval_to_uppercase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qto_uppercase,
	    Qto_uppercase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_to_uppercase_funcalled),Nil,
	    FIX((SI_Long)105L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_to_uppercase_funcalled),FIX((SI_Long)105L),
	    Funcall_eval_type_1_arg);
    Qto_titlecase = STATIC_SYMBOL("TO-TITLECASE",AB_package);
    Qeval_to_titlecase_funcalled = 
	    STATIC_SYMBOL("EVAL-TO-TITLECASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_to_titlecase_funcalled,
	    STATIC_FUNCTION(eval_to_titlecase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qto_titlecase,
	    Qto_titlecase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_to_titlecase_funcalled),Nil,
	    FIX((SI_Long)106L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_to_titlecase_funcalled),FIX((SI_Long)106L),
	    Funcall_eval_type_1_arg);
    Qto_lowercase = STATIC_SYMBOL("TO-LOWERCASE",AB_package);
    Qeval_to_lowercase_funcalled = 
	    STATIC_SYMBOL("EVAL-TO-LOWERCASE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_to_lowercase_funcalled,
	    STATIC_FUNCTION(eval_to_lowercase_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qto_lowercase,
	    Qto_lowercase,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_to_lowercase_funcalled),Nil,
	    FIX((SI_Long)107L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_to_lowercase_funcalled),FIX((SI_Long)107L),
	    Funcall_eval_type_1_arg);
    Qis_digit = STATIC_SYMBOL("IS-DIGIT",AB_package);
    Qeval_is_digit_funcalled = STATIC_SYMBOL("EVAL-IS-DIGIT-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_digit_funcalled,
	    STATIC_FUNCTION(eval_is_digit_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_digit,
	    Qis_digit,FIX((SI_Long)1L),list_constant_19,list_constant_24,
	    Qtruth_value,Qnil,SYMBOL_FUNCTION(Qeval_is_digit_funcalled),
	    Nil,FIX((SI_Long)108L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_digit_funcalled),FIX((SI_Long)108L),
	    Funcall_eval_type_1_arg);
    Qis_readable_digit = STATIC_SYMBOL("IS-READABLE-DIGIT",AB_package);
    Qeval_is_readable_digit_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-READABLE-DIGIT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_readable_digit_funcalled,
	    STATIC_FUNCTION(eval_is_readable_digit_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_readable_digit,
	    Qis_readable_digit,FIX((SI_Long)1L),list_constant_19,
	    list_constant_24,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_readable_digit_funcalled),Nil,
	    FIX((SI_Long)109L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_readable_digit_funcalled),FIX((SI_Long)109L),
	    Funcall_eval_type_1_arg);
    string_constant_67 = 
	    STATIC_STRING("~NA is not an integer ~\n          between 2 and 36, and therefore not a valid radix.");
    Qis_readable_digit_in_radix = 
	    STATIC_SYMBOL("IS-READABLE-DIGIT-IN-RADIX",AB_package);
    Qeval_is_readable_digit_in_radix_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-READABLE-DIGIT-IN-RADIX-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_readable_digit_in_radix_funcalled,
	    STATIC_FUNCTION(eval_is_readable_digit_in_radix_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qis_readable_digit_in_radix,
	    Qis_readable_digit_in_radix,FIX((SI_Long)1L),list_constant_19,
	    list_constant_28,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_readable_digit_in_radix_funcalled),
	    Nil,FIX((SI_Long)110L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_is_readable_digit_in_radix_funcalled),FIX((SI_Long)110L),
	    Funcall_eval_type_2_arg);
    string_constant_68 = 
	    STATIC_STRING("The value ~NV has no readable representation.");
    Qreadable_text_for_value = STATIC_SYMBOL("READABLE-TEXT-FOR-VALUE",
	    AB_package);
    list_constant_85 = STATIC_CONS(Qdatum,Qnil);
    Qeval_readable_text_for_value_funcalled = 
	    STATIC_SYMBOL("EVAL-READABLE-TEXT-FOR-VALUE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_readable_text_for_value_funcalled,
	    STATIC_FUNCTION(eval_readable_text_for_value_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qreadable_text_for_value,
	    Qreadable_text_for_value,FIX((SI_Long)1L),list_constant_19,
	    list_constant_85,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_readable_text_for_value_funcalled),Nil,
	    FIX((SI_Long)111L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_readable_text_for_value_funcalled),FIX((SI_Long)111L),
	    Funcall_eval_type_1_arg);
    Qreadable_text = STATIC_SYMBOL("READABLE-TEXT",AB_package);
    Qeval_readable_text_funcalled = 
	    STATIC_SYMBOL("EVAL-READABLE-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_readable_text_funcalled,
	    STATIC_FUNCTION(eval_readable_text_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qreadable_text,
	    Qreadable_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_readable_text_funcalled),Nil,
	    FIX((SI_Long)112L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_readable_text_funcalled),FIX((SI_Long)112L),
	    Funcall_eval_type_1_arg);
    string_constant_69 = 
	    STATIC_STRING("The text beginning with \"~a...\" is not valid as the text of a symbol.  ~a");
    string_constant_70 = 
	    STATIC_STRING("The text \"~a\" is not valid as the text of a symbol.  ~a");
    Qpunctuation_mark_p = STATIC_SYMBOL("PUNCTUATION-MARK-P",AB_package);
    Qreadable_symbol_text = STATIC_SYMBOL("READABLE-SYMBOL-TEXT",AB_package);
    Qeval_readable_symbol_text_funcalled = 
	    STATIC_SYMBOL("EVAL-READABLE-SYMBOL-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_readable_symbol_text_funcalled,
	    STATIC_FUNCTION(eval_readable_symbol_text_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qreadable_symbol_text,
	    Qreadable_symbol_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_33,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_readable_symbol_text_funcalled),Nil,
	    FIX((SI_Long)113L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_readable_symbol_text_funcalled),FIX((SI_Long)113L),
	    Funcall_eval_type_1_arg);
    Qcompare_text = STATIC_SYMBOL("COMPARE-TEXT",AB_package);
    Qeval_compare_text_funcalled = 
	    STATIC_SYMBOL("EVAL-COMPARE-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_compare_text_funcalled,
	    STATIC_FUNCTION(eval_compare_text_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qcompare_text,
	    Qcompare_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_32,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qeval_compare_text_funcalled),Nil,
	    FIX((SI_Long)115L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_compare_text_funcalled),FIX((SI_Long)115L),
	    Funcall_eval_type_2_arg);
    Qinternal_structure_for_text_conversion_style = 
	    STATIC_SYMBOL("INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE",
	    AB_package);
    Qimport_text = STATIC_SYMBOL("IMPORT-TEXT",AB_package);
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    list_constant_86 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qtext_conversion_style);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qtext,list_constant_86);
    Qeval_import_text_funcalled = 
	    STATIC_SYMBOL("EVAL-IMPORT-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_import_text_funcalled,
	    STATIC_FUNCTION(eval_import_text_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qimport_text,
	    Qimport_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_87,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_import_text_funcalled),Nil,
	    FIX((SI_Long)116L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_import_text_funcalled),FIX((SI_Long)116L),
	    Funcall_eval_type_2_arg);
    Qexport_text = STATIC_SYMBOL("EXPORT-TEXT",AB_package);
    Qeval_export_text_funcalled = 
	    STATIC_SYMBOL("EVAL-EXPORT-TEXT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_export_text_funcalled,
	    STATIC_FUNCTION(eval_export_text_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qexport_text,
	    Qexport_text,FIX((SI_Long)1L),list_constant_19,
	    list_constant_87,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_export_text_funcalled),Nil,
	    FIX((SI_Long)117L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_export_text_funcalled),FIX((SI_Long)117L),
	    Funcall_eval_type_2_arg);
    Qtransform_text_for_unicode_comparison = 
	    STATIC_SYMBOL("TRANSFORM-TEXT-FOR-UNICODE-COMPARISON",AB_package);
    list_constant_88 = STATIC_CONS(Qtext,list_constant_31);
    Qeval_transform_text_for_unicode_comparison_funcalled = 
	    STATIC_SYMBOL("EVAL-TRANSFORM-TEXT-FOR-UNICODE-COMPARISON-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_transform_text_for_unicode_comparison_funcalled,
	    STATIC_FUNCTION(eval_transform_text_for_unicode_comparison_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qtransform_text_for_unicode_comparison,
	    Qtransform_text_for_unicode_comparison,FIX((SI_Long)1L),
	    list_constant_19,list_constant_88,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_transform_text_for_unicode_comparison_funcalled),
	    Nil,FIX((SI_Long)118L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_transform_text_for_unicode_comparison_funcalled),
	    FIX((SI_Long)118L),Funcall_eval_type_2_arg);
    Qutf_g_wide_string = STATIC_SYMBOL("UTF-G-WIDE-STRING",AB_package);
    Qtransform_text_for_g2_4_dot_0_comparison = 
	    STATIC_SYMBOL("TRANSFORM-TEXT-FOR-G2-4.0-COMPARISON",AB_package);
    Qeval_transform_text_for_g2_4_dot_0_comparison_funcalled = 
	    STATIC_SYMBOL("EVAL-TRANSFORM-TEXT-FOR-G2-4.0-COMPARISON-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_transform_text_for_g2_4_dot_0_comparison_funcalled,
	    STATIC_FUNCTION(eval_transform_text_for_g2_4_dot_0_comparison_funcalled,
	    NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qtransform_text_for_g2_4_dot_0_comparison,
	    Qtransform_text_for_g2_4_dot_0_comparison,FIX((SI_Long)1L),
	    list_constant_19,list_constant_88,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qeval_transform_text_for_g2_4_dot_0_comparison_funcalled),
	    Nil,FIX((SI_Long)119L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_transform_text_for_g2_4_dot_0_comparison_funcalled),
	    FIX((SI_Long)119L),Funcall_eval_type_2_arg);
    string_constant_71 = 
	    STATIC_STRING("The index ~A was not within the range of indices for ~NE.");
    list_constant_89 = STATIC_CONS(list_constant_15,list_constant_24);
    Qeval_remove_funcalled = STATIC_SYMBOL("EVAL-REMOVE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_remove_funcalled,
	    STATIC_FUNCTION(eval_remove_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qremove,
	    Qremove,FIX((SI_Long)1L),list_constant_19,list_constant_89,
	    list_constant_15,Qnil,SYMBOL_FUNCTION(Qeval_remove_funcalled),
	    Nil,FIX((SI_Long)123L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_remove_funcalled),FIX((SI_Long)123L),
	    Funcall_eval_type_2_arg);
    Qinsert_at_beginning = STATIC_SYMBOL("INSERT-AT-BEGINNING",AB_package);
    list_constant_90 = STATIC_CONS(list_constant_15,list_constant_54);
    Qeval_insert_at_beginning_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-AT-BEGINNING-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_at_beginning_funcalled,
	    STATIC_FUNCTION(eval_insert_at_beginning_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_at_beginning,
	    Qinsert_at_beginning,FIX((SI_Long)1L),list_constant_19,
	    list_constant_90,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_at_beginning_funcalled),Nil,
	    FIX((SI_Long)124L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_at_beginning_funcalled),FIX((SI_Long)124L),
	    Funcall_eval_type_2_arg);
    Qinsert_at_end = STATIC_SYMBOL("INSERT-AT-END",AB_package);
    Qeval_insert_at_end_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-AT-END-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_at_end_funcalled,
	    STATIC_FUNCTION(eval_insert_at_end_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_at_end,
	    Qinsert_at_end,FIX((SI_Long)1L),list_constant_19,
	    list_constant_90,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_at_end_funcalled),Nil,
	    FIX((SI_Long)125L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_at_end_funcalled),FIX((SI_Long)125L),
	    Funcall_eval_type_2_arg);
    string_constant_72 = 
	    STATIC_STRING("Unable to find ~NA in ~NA, cannot insert ~NA as new element.");
    Qinsert_before = STATIC_SYMBOL("INSERT-BEFORE",AB_package);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)3L,list_constant_15,
	    Qitem_or_datum,list_constant_54);
    Qeval_insert_before_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-BEFORE-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_before_funcalled,
	    STATIC_FUNCTION(eval_insert_before_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_before,
	    Qinsert_before,FIX((SI_Long)1L),list_constant_19,
	    list_constant_91,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_before_funcalled),Nil,
	    FIX((SI_Long)126L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_before_funcalled),FIX((SI_Long)126L),
	    Funcall_eval_type_3_arg);
    Qinsert_after = STATIC_SYMBOL("INSERT-AFTER",AB_package);
    Qeval_insert_after_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-AFTER-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_after_funcalled,
	    STATIC_FUNCTION(eval_insert_after_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_after,
	    Qinsert_after,FIX((SI_Long)1L),list_constant_19,
	    list_constant_91,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_after_funcalled),Nil,
	    FIX((SI_Long)127L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_after_funcalled),FIX((SI_Long)127L),
	    Funcall_eval_type_3_arg);
    string_constant_73 = 
	    STATIC_STRING("Index ~NA in ~NA is out of range, cannot insert ~NA ~\n                        as new element.");
    Qinsert_before_element = STATIC_SYMBOL("INSERT-BEFORE-ELEMENT",AB_package);
    list_constant_92 = STATIC_LIST_STAR((SI_Long)3L,list_constant_15,
	    Qinteger,list_constant_54);
    Qeval_insert_before_element_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-BEFORE-ELEMENT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_before_element_funcalled,
	    STATIC_FUNCTION(eval_insert_before_element_funcalled,NIL,FALSE,
	    3,3));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_before_element,
	    Qinsert_before_element,FIX((SI_Long)1L),list_constant_19,
	    list_constant_92,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_before_element_funcalled),Nil,
	    FIX((SI_Long)128L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_before_element_funcalled),FIX((SI_Long)128L),
	    Funcall_eval_type_3_arg);
    Qinsert_after_element = STATIC_SYMBOL("INSERT-AFTER-ELEMENT",AB_package);
    Qeval_insert_after_element_funcalled = 
	    STATIC_SYMBOL("EVAL-INSERT-AFTER-ELEMENT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_insert_after_element_funcalled,
	    STATIC_FUNCTION(eval_insert_after_element_funcalled,NIL,FALSE,
	    3,3));
    register_funcalled_evaluator(make_evaluator_description(Qinsert_after_element,
	    Qinsert_after_element,FIX((SI_Long)1L),list_constant_19,
	    list_constant_92,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_insert_after_element_funcalled),Nil,
	    FIX((SI_Long)129L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_insert_after_element_funcalled),FIX((SI_Long)129L),
	    Funcall_eval_type_3_arg);
    Qchange_element = STATIC_SYMBOL("CHANGE-ELEMENT",AB_package);
    Qeval_change_element_funcalled = 
	    STATIC_SYMBOL("EVAL-CHANGE-ELEMENT-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_change_element_funcalled,
	    STATIC_FUNCTION(eval_change_element_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qchange_element,
	    Qchange_element,FIX((SI_Long)1L),list_constant_19,
	    list_constant_92,list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qeval_change_element_funcalled),Nil,
	    FIX((SI_Long)130L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_change_element_funcalled),FIX((SI_Long)130L),
	    Funcall_eval_type_3_arg);
    concatenate_stack_node_converter_1 = 
	    STATIC_FUNCTION(concatenate_stack_node_converter,NIL,FALSE,1,1);
    mutate_global_property(Qconcatenate,concatenate_stack_node_converter_1,
	    Qstack_special_form_converter);
    concatenate_i_chooser_1 = STATIC_FUNCTION(concatenate_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qconcatenate,concatenate_i_chooser_1,
	    Qpreferred_instruction_chooser);
    concatenate_i_emit_1 = STATIC_FUNCTION(concatenate_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qconcatenate,concatenate_i_emit_1,
	    Qstack_node_instruction_emitter);
    array_constant_10 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    Qfuncall_concatenate_inst = STATIC_SYMBOL("FUNCALL-CONCATENATE-INST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_concatenate_inst,
	    STATIC_FUNCTION(funcall_concatenate_inst,NIL,FALSE,2,2));
    Qpprint_concatenate_instruction = 
	    STATIC_SYMBOL("PPRINT-CONCATENATE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_concatenate_instruction,
	    STATIC_FUNCTION(pprint_concatenate_instruction,NIL,FALSE,8,8));
    make_and_register_funcalled_instruction_description(Qconcatenate,
	    FIX((SI_Long)84L),Qall,list_constant_83,FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qfuncall_concatenate_inst),Qnil,
	    SYMBOL_FUNCTION(Qpprint_concatenate_instruction),
	    Qfuncall_concatenate_inst);
    string_constant_74 = 
	    STATIC_STRING("In PORTION, the starting index argument, ~a, was less than zero.");
    string_constant_75 = 
	    STATIC_STRING("In PORTION, the number of elements to copy argument, ~a, was less than zero.");
    string_constant_76 = 
	    STATIC_STRING("In PORTION, the starting index, ~a, plus the number of elements to ~@\n         copy, ~a, was greater than the length of the source sequence, ~a.");
    Qportion = STATIC_SYMBOL("PORTION",AB_package);
    list_constant_93 = STATIC_CONS(list_constant_15,list_constant_28);
    Qeval_portion_funcalled = STATIC_SYMBOL("EVAL-PORTION-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_portion_funcalled,
	    STATIC_FUNCTION(eval_portion_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qportion,
	    Qportion,FIX((SI_Long)1L),list_constant_19,list_constant_93,
	    list_constant_15,Qnil,SYMBOL_FUNCTION(Qeval_portion_funcalled),
	    Nil,FIX((SI_Long)131L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_portion_funcalled),FIX((SI_Long)131L),
	    Funcall_eval_type_3_arg);
    Qchange_attribute = STATIC_SYMBOL("CHANGE-ATTRIBUTE",AB_package);
    Qchange_evaluated_attribute = 
	    STATIC_SYMBOL("CHANGE-EVALUATED-ATTRIBUTE",AB_package);
    string_constant_77 = 
	    string_append2(STATIC_STRING("The second argument to change-attribute should be the attribute name ~\n         to be changed, not an expression that evaluates to that name.  ~\n         \"~NE\" was provided in"),
	    STATIC_STRING("stead of a name."));
    Qstand_in = STATIC_SYMBOL("STAND-IN",AB_package);
    change_attribute_stack_node_converter_1 = 
	    STATIC_FUNCTION(change_attribute_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qchange_attribute,
	    change_attribute_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_94 = STATIC_LIST_STAR((SI_Long)3L,list_constant_16,
	    Qsymbol,list_constant_54);
    Qeval_change_evaluated_attribute_funcalled = 
	    STATIC_SYMBOL("EVAL-CHANGE-EVALUATED-ATTRIBUTE-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_change_evaluated_attribute_funcalled,
	    STATIC_FUNCTION(eval_change_evaluated_attribute_funcalled,NIL,
	    FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qchange_evaluated_attribute,
	    Qchange_evaluated_attribute,FIX((SI_Long)1L),list_constant_19,
	    list_constant_94,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_change_evaluated_attribute_funcalled),
	    Nil,FIX((SI_Long)132L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_change_evaluated_attribute_funcalled),FIX((SI_Long)132L),
	    Funcall_eval_type_3_arg);
    Qremove_attribute = STATIC_SYMBOL("REMOVE-ATTRIBUTE",AB_package);
    Qremove_evaluated_attribute = 
	    STATIC_SYMBOL("REMOVE-EVALUATED-ATTRIBUTE",AB_package);
    string_constant_78 = 
	    string_append2(STATIC_STRING("The second argument to remove-attribute should be the attribute name ~\n         to be removed, not an expression that evaluates to that name.  ~\n         \"~NE\" was provided in"),
	    STATIC_STRING("stead of a name."));
    remove_attribute_stack_node_converter_1 = 
	    STATIC_FUNCTION(remove_attribute_stack_node_converter,NIL,
	    FALSE,1,1);
    mutate_global_property(Qremove_attribute,
	    remove_attribute_stack_node_converter_1,
	    Qstack_special_form_converter);
    list_constant_95 = STATIC_CONS(list_constant_16,list_constant_67);
    Qeval_remove_evaluated_attribute_funcalled = 
	    STATIC_SYMBOL("EVAL-REMOVE-EVALUATED-ATTRIBUTE-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_remove_evaluated_attribute_funcalled,
	    STATIC_FUNCTION(eval_remove_evaluated_attribute_funcalled,NIL,
	    FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qremove_evaluated_attribute,
	    Qremove_evaluated_attribute,FIX((SI_Long)1L),list_constant_19,
	    list_constant_95,list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qeval_remove_evaluated_attribute_funcalled),
	    Nil,FIX((SI_Long)133L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_remove_evaluated_attribute_funcalled),FIX((SI_Long)133L),
	    Funcall_eval_type_2_arg);
    string_constant_79 = 
	    STATIC_STRING("FIND-JAVA-CLASS works only in exported methods and procedures");
    Qfind_java_class = STATIC_SYMBOL("FIND-JAVA-CLASS",AB_package);
    list_constant_96 = STATIC_CONS(Qprocedure,Qnil);
    Qeval_find_java_class_funcalled = 
	    STATIC_SYMBOL("EVAL-FIND-JAVA-CLASS-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_find_java_class_funcalled,
	    STATIC_FUNCTION(eval_find_java_class_funcalled,NIL,FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qfind_java_class,
	    Qfind_java_class,FIX((SI_Long)1L),list_constant_96,
	    list_constant_33,Qitem_or_datum,Qnil,
	    SYMBOL_FUNCTION(Qeval_find_java_class_funcalled),Nil,
	    FIX((SI_Long)137L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_find_java_class_funcalled),FIX((SI_Long)137L),
	    Funcall_eval_type_1_arg);
    string_constant_80 = 
	    STATIC_STRING("Could not find a network interface for ~NF");
    Qnetwork_interface_for = STATIC_SYMBOL("NETWORK-INTERFACE-FOR",AB_package);
    Qnetwork_interface = STATIC_SYMBOL("NETWORK-INTERFACE",AB_package);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qab_class,Qnetwork_interface);
    Qeval_network_interface_for_funcalled = 
	    STATIC_SYMBOL("EVAL-NETWORK-INTERFACE-FOR-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_network_interface_for_funcalled,
	    STATIC_FUNCTION(eval_network_interface_for_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qnetwork_interface_for,
	    Qnetwork_interface_for,FIX((SI_Long)1L),Qall,list_constant_22,
	    list_constant_97,Qnil,
	    SYMBOL_FUNCTION(Qeval_network_interface_for_funcalled),Nil,
	    FIX((SI_Long)138L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_network_interface_for_funcalled),FIX((SI_Long)138L),
	    Funcall_eval_type_1_arg);
    Qin_the_tracked_item_set = STATIC_SYMBOL("IN-THE-TRACKED-ITEM-SET",
	    AB_package);
    Qeval_in_the_tracked_item_set_funcalled = 
	    STATIC_SYMBOL("EVAL-IN-THE-TRACKED-ITEM-SET-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_in_the_tracked_item_set_funcalled,
	    STATIC_FUNCTION(eval_in_the_tracked_item_set_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qin_the_tracked_item_set,
	    Qin_the_tracked_item_set,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_in_the_tracked_item_set_funcalled),Nil,
	    FIX((SI_Long)139L),Nil,
	    SYMBOL_FUNCTION(Qpprint_functional_evaluator),
	    Qeval_in_the_tracked_item_set_funcalled),FIX((SI_Long)139L),
	    Funcall_eval_type_1_arg);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qserver_parameters = STATIC_SYMBOL("SERVER-PARAMETERS",AB_package);
    Qattributes_permamently_changed = 
	    STATIC_SYMBOL("ATTRIBUTES-PERMAMENTLY-CHANGED",AB_package);
    Qwith_unsaved_changes = STATIC_SYMBOL("WITH-UNSAVED-CHANGES",AB_package);
    Qeval_with_unsaved_changes_funcalled = 
	    STATIC_SYMBOL("EVAL-WITH-UNSAVED-CHANGES-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_with_unsaved_changes_funcalled,
	    STATIC_FUNCTION(eval_with_unsaved_changes_funcalled,NIL,FALSE,
	    1,1));
    register_funcalled_evaluator(make_evaluator_description(Qwith_unsaved_changes,
	    Qwith_unsaved_changes,FIX((SI_Long)1L),list_constant_71,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_with_unsaved_changes_funcalled),Nil,
	    FIX((SI_Long)140L),Nil,Nil,
	    Qeval_with_unsaved_changes_funcalled),FIX((SI_Long)140L),
	    Funcall_eval_type_1_arg);
    if (Mark_for_modules_with_unsaved_changes == UNBOUND)
	Mark_for_modules_with_unsaved_changes = FIX((SI_Long)0L);
    Qmodule_has_unsaved_changes = 
	    STATIC_SYMBOL("MODULE-HAS-UNSAVED-CHANGES",AB_package);
    Kb_specific_property_names = CONS(Qmodule_has_unsaved_changes,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qmodule_has_unsaved_changes,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_has_unsaved_changes_kbprop = Qmodule_has_unsaved_changes;
    string_constant_81 = STATIC_STRING("~%");
    string_constant_82 = 
	    STATIC_STRING("(Note that there are unsaved changes.)");
    string_constant_83 = 
	    STATIC_STRING("(Note that the module~a ~L,& ~a unsaved changes.)");
    string_constant_84 = STATIC_STRING("s");
    string_constant_85 = STATIC_STRING("have");
    string_constant_86 = STATIC_STRING("has");
    string_constant_87 = STATIC_STRING("~NF is divided by zero.");
    Qdiv_long = STATIC_SYMBOL("DIV-LONG",AB_package);
    Qeval_div_long_funcalled = STATIC_SYMBOL("EVAL-DIV-LONG-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_div_long_funcalled,
	    STATIC_FUNCTION(eval_div_long_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qdiv_long,
	    Qdiv_long,FIX((SI_Long)1L),Qall,list_constant_27,Qlong,Qnil,
	    SYMBOL_FUNCTION(Qeval_div_long_funcalled),Nil,
	    FIX((SI_Long)143L),Nil,Nil,Qeval_div_long_funcalled),
	    FIX((SI_Long)143L),Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qdiv_long,FIX((SI_Long)2L),
	    Argument_range_gkbprop);
    Qkbf_g2nke_count_history_matching_op = 
	    STATIC_SYMBOL("KBF-G2NKE-COUNT-HISTORY-MATCHING-OP",AB_package);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qquantitative_parameter);
    list_constant_99 = STATIC_LIST_STAR((SI_Long)5L,list_constant_98,
	    Qinteger,Qinteger,Qnumber,list_constant_28);
    Qeval_kbf_g2nke_count_history_matching_op_funcalled = 
	    STATIC_SYMBOL("EVAL-KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_kbf_g2nke_count_history_matching_op_funcalled,
	    STATIC_FUNCTION(eval_kbf_g2nke_count_history_matching_op_funcalled,
	    NIL,FALSE,6,6));
    register_funcalled_evaluator(make_evaluator_description(Qkbf_g2nke_count_history_matching_op,
	    Qkbf_g2nke_count_history_matching_op,FIX((SI_Long)1L),Qall,
	    list_constant_99,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_kbf_g2nke_count_history_matching_op_funcalled),
	    Nil,FIX((SI_Long)144L),Nil,Nil,
	    Qeval_kbf_g2nke_count_history_matching_op_funcalled),
	    FIX((SI_Long)144L),Funcall_eval_type_6_arg);
    mutate_global_or_kb_specific_property_value(Qkbf_g2nke_count_history_matching_op,
	    FIX((SI_Long)6L),Argument_range_gkbprop);
    if (Cached_subj == UNBOUND)
	Cached_subj = Nil;
    if (Cached_n == UNBOUND)
	Cached_n = Nil;
    if (Cached_nstart == UNBOUND)
	Cached_nstart = Nil;
    if (Cached_fellow_val == UNBOUND)
	Cached_fellow_val = Nil;
    if (Cached_eventflag == UNBOUND)
	Cached_eventflag = Nil;
    if (Cached_event_bit == UNBOUND)
	Cached_event_bit = Nil;
    if (Cached_requiredgoodsize == UNBOUND)
	Cached_requiredgoodsize = Nil;
    if (Cached_compareoperator == UNBOUND)
	Cached_compareoperator = Nil;
    if (Cached_result == UNBOUND)
	Cached_result = Nil;
    Qkbf_g2nke_count_history_matching_op_and_eventflag = 
	    STATIC_SYMBOL("KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG",
	    AB_package);
    list_constant_100 = STATIC_LIST_STAR((SI_Long)6L,list_constant_98,
	    Qinteger,Qinteger,Qnumber,list_constant_98,list_constant_81);
    Qeval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled = 
	    STATIC_SYMBOL("EVAL-KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled,
	    STATIC_FUNCTION(eval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled,
	    NIL,FALSE,8,8));
    register_funcalled_evaluator(make_evaluator_description(Qkbf_g2nke_count_history_matching_op_and_eventflag,
	    Qkbf_g2nke_count_history_matching_op_and_eventflag,
	    FIX((SI_Long)1L),Qall,list_constant_100,Qfloat,Qnil,
	    SYMBOL_FUNCTION(Qeval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled),
	    Nil,FIX((SI_Long)145L),Nil,Nil,
	    Qeval_kbf_g2nke_count_history_matching_op_and_eventflag_funcalled),
	    FIX((SI_Long)145L),Funcall_eval_type_8_arg);
    mutate_global_or_kb_specific_property_value(Qkbf_g2nke_count_history_matching_op_and_eventflag,
	    FIX((SI_Long)8L),Argument_range_gkbprop);
    Qvector_add = STATIC_SYMBOL("VECTOR-ADD",AB_package);
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qab_class,Qquantity_array);
    list_constant_102 = STATIC_LIST((SI_Long)3L,list_constant_101,
	    list_constant_101,list_constant_101);
    Qeval_vector_add_funcalled = STATIC_SYMBOL("EVAL-VECTOR-ADD-FUNCALLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeval_vector_add_funcalled,
	    STATIC_FUNCTION(eval_vector_add_funcalled,NIL,FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qvector_add,
	    Qvector_add,FIX((SI_Long)1L),Qall,list_constant_102,
	    list_constant_101,Qnil,
	    SYMBOL_FUNCTION(Qeval_vector_add_funcalled),Nil,
	    FIX((SI_Long)146L),Nil,Nil,Qeval_vector_add_funcalled),
	    FIX((SI_Long)146L),Funcall_eval_type_3_arg);
    mutate_global_or_kb_specific_property_value(Qvector_add,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qvector_multiply = STATIC_SYMBOL("VECTOR-MULTIPLY",AB_package);
    list_constant_103 = STATIC_LIST((SI_Long)2L,list_constant_101,
	    list_constant_101);
    Qeval_vector_multiply_funcalled = 
	    STATIC_SYMBOL("EVAL-VECTOR-MULTIPLY-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_vector_multiply_funcalled,
	    STATIC_FUNCTION(eval_vector_multiply_funcalled,NIL,FALSE,2,2));
    register_funcalled_evaluator(make_evaluator_description(Qvector_multiply,
	    Qvector_multiply,FIX((SI_Long)1L),Qall,list_constant_103,
	    Qfloat,Qnil,SYMBOL_FUNCTION(Qeval_vector_multiply_funcalled),
	    Nil,FIX((SI_Long)147L),Nil,Nil,
	    Qeval_vector_multiply_funcalled),FIX((SI_Long)147L),
	    Funcall_eval_type_2_arg);
    mutate_global_or_kb_specific_property_value(Qvector_multiply,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qvector_scalar_multiply = STATIC_SYMBOL("VECTOR-SCALAR-MULTIPLY",
	    AB_package);
    list_constant_104 = STATIC_CONS(list_constant_101,Qnil);
    list_constant_105 = STATIC_LIST_STAR((SI_Long)3L,list_constant_101,
	    Qfloat,list_constant_104);
    Qeval_vector_scalar_multiply_funcalled = 
	    STATIC_SYMBOL("EVAL-VECTOR-SCALAR-MULTIPLY-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_vector_scalar_multiply_funcalled,
	    STATIC_FUNCTION(eval_vector_scalar_multiply_funcalled,NIL,
	    FALSE,3,3));
    register_funcalled_evaluator(make_evaluator_description(Qvector_scalar_multiply,
	    Qvector_scalar_multiply,FIX((SI_Long)1L),Qall,
	    list_constant_105,list_constant_101,Qnil,
	    SYMBOL_FUNCTION(Qeval_vector_scalar_multiply_funcalled),Nil,
	    FIX((SI_Long)148L),Nil,Nil,
	    Qeval_vector_scalar_multiply_funcalled),FIX((SI_Long)148L),
	    Funcall_eval_type_3_arg);
    mutate_global_or_kb_specific_property_value(Qvector_scalar_multiply,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qis_resized_by_the_user = STATIC_SYMBOL("IS-RESIZED-BY-THE-USER",
	    AB_package);
    Qeval_is_resized_by_the_user_funcalled = 
	    STATIC_SYMBOL("EVAL-IS-RESIZED-BY-THE-USER-FUNCALLED",AB_package);
    SET_SYMBOL_FUNCTION(Qeval_is_resized_by_the_user_funcalled,
	    STATIC_FUNCTION(eval_is_resized_by_the_user_funcalled,NIL,
	    FALSE,1,1));
    register_funcalled_evaluator(make_evaluator_description(Qis_resized_by_the_user,
	    Qis_resized_by_the_user,FIX((SI_Long)1L),list_constant_55,
	    list_constant_22,Qboolean,Qnil,
	    SYMBOL_FUNCTION(Qeval_is_resized_by_the_user_funcalled),Nil,
	    FIX((SI_Long)150L),Nil,Nil,
	    Qeval_is_resized_by_the_user_funcalled),FIX((SI_Long)150L),
	    Funcall_eval_type_1_arg);
}
