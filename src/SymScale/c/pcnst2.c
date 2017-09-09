/* pcnst2.c
 * Input file:  proc-inst2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pcnst2.h"


/* TAG-STATEMENT-PSEUDO-EMITTER */
Object tag_statement_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,0);
    register_tag_in_byte_code_stream(2,byte_code_stream,SECOND(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* JUMP-TAG-STATEMENT-PSEUDO-EMITTER */
Object jump_tag_statement_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,1);
    register_tag_in_byte_code_stream(3,byte_code_stream,SECOND(instruction),T);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ASSIGN-LOCAL-VAR-PSEUDO-EMITTER */
Object assign_local_var_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot, expression;

    x_note_fn_call(212,2);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,expression);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BRANCH-PSEUDO-EMITTER */
Object branch_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, tag;

    x_note_fn_call(212,3);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    tag = CAR(gensymed_symbol);
    emit_branch_long_byte_codes(byte_code_stream,tag);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BRANCH-IF-TRUE-PSEUDO-EMITTER */
Object branch_if_true_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, logical_expression, target_address;

    x_note_fn_call(212,4);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    logical_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    target_address = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,logical_expression);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)50L));
    emit_branch_long_if_not_true_byte_codes(byte_code_stream,target_address);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BRANCH-IF-NOT-TRUE-PSEUDO-EMITTER */
Object branch_if_not_true_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, logical_expression, target_address;

    x_note_fn_call(212,5);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    logical_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    target_address = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,logical_expression);
    emit_branch_long_if_not_true_byte_codes(byte_code_stream,target_address);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* JUMP-PSEUDO-EMITTER */
Object jump_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,6);
    emit_jump_byte_codes(byte_code_stream,SECOND(instruction),
	    THIRD(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CASE-DISPATCH-PSEUDO-EMITTER */
Object case_dispatch_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, expression, table_base, table_length, else_tag;
    Object tag_table;

    x_note_fn_call(212,7);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    table_base = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    table_length = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    else_tag = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    tag_table = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,expression);
    emit_case_dispatch_byte_codes(byte_code_stream,table_base,table_length,
	    else_tag,tag_table);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RETURN-VALUES-PSEUDO-EMITTER */
Object return_values_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object expressions, expression, ab_loop_list_;

    x_note_fn_call(212,8);
    expressions = SECOND(instruction);
    expression = Nil;
    ab_loop_list_ = expressions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,expression);
    goto next_loop;
  end_loop:;
    emit_return_values_byte_codes(byte_code_stream,length(expressions));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant;     /* "CALL accepts a maximum of 255 arguments, this call passed ~a." */

static Object string_constant_1;   /* "CALL receives a maximum of 255 values, this call requested ~a." */

/* CALL-PSEUDO-EMITTER */
Object call_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure_designation, argument_list;
    Object desired_value_count, arg_count, emit_byte_codes_p, arg;
    Object ab_loop_list_;

    x_note_fn_call(212,9);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    argument_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    desired_value_count = CAR(gensymed_symbol);
    arg_count = length(argument_list);
    emit_byte_codes_p = T;
    if (IFIX(arg_count) > (SI_Long)255L) {
	compiler_error(2,string_constant,arg_count);
	emit_byte_codes_p = Nil;
    }
    if (IFIX(desired_value_count) > (SI_Long)255L) {
	compiler_error(2,string_constant_1,desired_value_count);
	emit_byte_codes_p = Nil;
    }
    if (emit_byte_codes_p) {
	emit_stack_node_tree(byte_code_stream,procedure_designation);
	arg = Nil;
	ab_loop_list_ = argument_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_stack_node_tree(byte_code_stream,arg);
	goto next_loop;
      end_loop:;
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)57L));
	write_byte_code_to_stream(byte_code_stream,arg_count);
	write_byte_code_to_stream(byte_code_stream,desired_value_count);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* DEPENDENT-CALL-PSEUDO-EMITTER */
Object dependent_call_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure_designation, argument_list;
    Object desired_value_count, arg_count, emit_byte_codes_p, arg;
    Object ab_loop_list_;

    x_note_fn_call(212,10);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    argument_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    desired_value_count = CAR(gensymed_symbol);
    arg_count = length(argument_list);
    emit_byte_codes_p = T;
    if (IFIX(arg_count) > (SI_Long)255L) {
	compiler_error(2,string_constant,arg_count);
	emit_byte_codes_p = Nil;
    }
    if (IFIX(desired_value_count) > (SI_Long)255L) {
	compiler_error(2,string_constant_1,desired_value_count);
	emit_byte_codes_p = Nil;
    }
    if (emit_byte_codes_p) {
	emit_stack_node_tree(byte_code_stream,procedure_designation);
	arg = Nil;
	ab_loop_list_ = argument_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_stack_node_tree(byte_code_stream,arg);
	goto next_loop;
      end_loop:;
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)81L));
	write_byte_code_to_stream(byte_code_stream,arg_count);
	write_byte_code_to_stream(byte_code_stream,desired_value_count);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qpush_returned_values_long;  /* push-returned-values-long */

static Object Qpush_returned_values;  /* push-returned-values */

/* RECEIVE-VALUES-PSEUDO-EMITTER */
Object receive_values_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spots, types, var_length;
    Object need_long_instruction_p, temp, var_spot, ab_loop_list_, type_qm;
    Object ab_loop_list__1;

    x_note_fn_call(212,11);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spots = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    types = CAR(gensymed_symbol);
    if (var_spots) {
	var_length = length(var_spots);
	need_long_instruction_p = IFIX(var_length) > (SI_Long)255L ? T : Nil;
	if (need_long_instruction_p);
	else
	    need_long_instruction_p = Current_return_values_position ? 
		    (IFIX(Current_return_values_position) > (SI_Long)255L ?
		     T : Nil) : Qnil;
	write_byte_code_to_stream(byte_code_stream,
		op_code_for_stack_instruction(need_long_instruction_p ? 
		Qpush_returned_values_long : Qpush_returned_values));
	if (need_long_instruction_p) {
	    emit_long_code_constant_to_stream(byte_code_stream,var_length);
	    temp = Current_return_values_position;
	    if (temp);
	    else
		temp = var_length;
	    emit_long_code_constant_to_stream(byte_code_stream,temp);
	}
	else {
	    write_byte_code_to_stream(byte_code_stream,var_length);
	    temp = Current_return_values_position;
	    if (temp);
	    else
		temp = var_length;
	    write_byte_code_to_stream(byte_code_stream,temp);
	}
	var_spot = Nil;
	ab_loop_list_ = var_spots;
	type_qm = Nil;
	ab_loop_list__1 = types;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	type_qm = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (type_qm)
	    emit_type_check_byte_codes(byte_code_stream,type_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot);
	goto next_loop;
      end_loop:;
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_2;   /* "CALL-ACROSS accepts a maximum of 255 arguments, this call passed ~a." */

static Object string_constant_3;   /* "CALL-ACROSS receives a maximum of 255 values, this call requested ~a." */

/* CALL-RPC-PSEUDO-EMITTER */
Object call_rpc_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, designation, icp_designation, arguments;
    Object desired_values_count, arg_count, emit_byte_codes_p, arg;
    Object ab_loop_list_;

    x_note_fn_call(212,12);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    icp_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    desired_values_count = CAR(gensymed_symbol);
    arg_count = length(arguments);
    emit_byte_codes_p = T;
    if (IFIX(arg_count) > (SI_Long)255L) {
	compiler_error(2,string_constant_2,arg_count);
	emit_byte_codes_p = Nil;
    }
    if (IFIX(desired_values_count) > (SI_Long)255L) {
	compiler_error(2,string_constant_3,desired_values_count);
	emit_byte_codes_p = Nil;
    }
    if (emit_byte_codes_p) {
	emit_stack_node_tree(byte_code_stream,designation);
	emit_stack_node_tree(byte_code_stream,icp_designation);
	arg = Nil;
	ab_loop_list_ = arguments;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_stack_node_tree(byte_code_stream,arg);
	goto next_loop;
      end_loop:;
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)58L));
	write_byte_code_to_stream(byte_code_stream,arg_count);
	write_byte_code_to_stream(byte_code_stream,desired_values_count);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ALLOW-OTHER-PROCESSING-PSEUDO-EMITTER */
Object allow_other_processing_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,13);
    write_byte_code_to_stream(byte_code_stream,
	    op_code_for_stack_instruction(CAR(instruction)));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qab_class;           /* class */

/* OPEN-ROLE-ITERATION-NO-DOMAIN-PSEUDO-EMITTER */
Object open_role_iteration_no_domain_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, role, continuation_spot, value_spot, value_type;
    Object role_type_qm, no_value_tag;

    x_note_fn_call(212,14);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    role_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    no_value_tag = CAR(gensymed_symbol);
    if (SYMBOLP(role))
	record_free_reference(Qab_class,role);
    else
	record_free_references_of_role(1,role);
    emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,role,
	    no_value_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    if ( !(role_type_qm && type_specification_subtype_p(role_type_qm,
	    value_type)))
	emit_type_check_byte_codes(byte_code_stream,value_type);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* OPEN-ROLE-ITERATION-PSEUDO-EMITTER */
Object open_role_iteration_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, role, continuation_spot, value_spot, value_type;
    Object role_type_qm, no_value_tag, domain_list, domain, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(212,15);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    role_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    no_value_tag = CAR(gensymed_symbol);
    domain_list = CDR(gensymed_symbol);
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
    ab_loopvar__2 = phrase_cons(ISVREF(domain,(SI_Long)6L),Nil);
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
    record_free_references_of_role(2,role,temp);
    domain = Nil;
    ab_loop_list_ = domain_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    domain = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,domain);
    goto next_loop_1;
  end_loop_1:;
    emit_open_role_iteration_byte_codes(byte_code_stream,role,no_value_tag,
	    length(domain_list));
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    continuation_spot);
    if ( !(role_type_qm && type_specification_subtype_p(role_type_qm,
	    value_type)))
	emit_type_check_byte_codes(byte_code_stream,value_type);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SERVE-NEXT-ITERATION-VALUE-PSEUDO-EMITTER */
Object serve_next_iteration_value_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, continuation_spot, value_spot, required_type;
    Object iteration_type_qm, no_values_tag;

    x_note_fn_call(212,16);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    continuation_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    required_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    iteration_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    no_values_tag = CAR(gensymed_symbol);
    emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    continuation_spot,no_values_tag);
    if ( !(iteration_type_qm && 
	    type_specification_subtype_p(iteration_type_qm,required_type)))
	emit_type_check_byte_codes(byte_code_stream,required_type);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    value_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLOSE-ITERATION-PSEUDO-EMITTER */
Object close_iteration_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,17);
    emit_close_iteration_byte_codes(byte_code_stream,SECOND(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SIGNAL-ERROR-PSEUDO-EMITTER */
Object signal_error_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,18);
    emit_stack_node_tree(byte_code_stream,SECOND(instruction));
    emit_stack_node_tree(byte_code_stream,THIRD(instruction));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)56L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLOSE-CODE-BODY-PSEUDO-EMITTER */
Object close_code_body_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,19);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)67L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-CODE-BODY-PSEUDO-EMITTER */
Object call_code_body_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, code_body_number, arg_expressions, arg;
    Object ab_loop_list_;

    x_note_fn_call(212,20);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    code_body_number = CAR(gensymed_symbol);
    arg_expressions = CDR(gensymed_symbol);
    arg = Nil;
    ab_loop_list_ = arg_expressions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:;
    emit_call_code_body_byte_codes(byte_code_stream,code_body_number,
	    length(arg_expressions));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-SCHEDULED-CODE-BODY-PSEUDO-EMITTER */
Object call_scheduled_code_body_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, code_body_number, arg_expressions, arg;
    Object ab_loop_list_;

    x_note_fn_call(212,21);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    code_body_number = CAR(gensymed_symbol);
    arg_expressions = CDR(gensymed_symbol);
    arg = Nil;
    ab_loop_list_ = arg_expressions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:;
    emit_call_scheduled_code_body_byte_codes(byte_code_stream,
	    code_body_number,length(arg_expressions));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* WAIT-FOR-CALLED-CODE-BODIES-PSEUDO-EMITTER */
Object wait_for_called_code_bodies_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,22);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)70L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ABORT-CALLED-CODE-BODIES-PSEUDO-EMITTER */
Object abort_called_code_bodies_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,23);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)61L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PAUSE-PSEUDO-EMITTER */
Object pause_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,24);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)72L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PAUSE-IF-CALLED-CODE-BODIES-PSEUDO-EMITTER */
Object pause_if_called_code_bodies_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,25);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)73L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* POLLED-WAIT-PSEUDO-EMITTER */
Object polled_wait_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, inferred_logical, wait_interval, wait_var;
    Object try_again_tag, known_value_tag, unknown_rejoins_tag, get_out_tag;

    x_note_fn_call(212,26);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    inferred_logical = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_interval = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_var = CAR(gensymed_symbol);
    if (type_specification_subtype_p(list_constant,ISVREF(inferred_logical,
	    (SI_Long)6L))) {
	try_again_tag = generate_new_goto_tag();
	known_value_tag = generate_new_goto_tag();
	unknown_rejoins_tag = generate_new_goto_tag();
	get_out_tag = generate_new_goto_tag();
	emit_stack_node_tree(byte_code_stream,wait_interval);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		wait_var);
	register_tag_in_byte_code_stream(2,byte_code_stream,try_again_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)84L));
	emit_stack_node_tree(byte_code_stream,inferred_logical);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)83L));
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)85L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	emit_branch_long_byte_codes(byte_code_stream,unknown_rejoins_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_value_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)86L));
	register_tag_in_byte_code_stream(2,byte_code_stream,
		unknown_rejoins_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	emit_branch_long_if_not_false_byte_codes(byte_code_stream,get_out_tag);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		wait_var);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)88L));
	emit_begin_activity_byte_codes(byte_code_stream,FIX((SI_Long)18L),T);
	emit_branch_long_byte_codes(byte_code_stream,try_again_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,get_out_tag);
    }
    else {
	try_again_tag = generate_new_goto_tag();
	get_out_tag = generate_new_goto_tag();
	emit_stack_node_tree(byte_code_stream,wait_interval);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		wait_var);
	register_tag_in_byte_code_stream(2,byte_code_stream,try_again_tag);
	emit_stack_node_tree(byte_code_stream,inferred_logical);
	emit_branch_long_if_not_false_byte_codes(byte_code_stream,get_out_tag);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		wait_var);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)88L));
	emit_begin_activity_byte_codes(byte_code_stream,FIX((SI_Long)18L),T);
	emit_branch_long_byte_codes(byte_code_stream,try_again_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,get_out_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* WAIT-FOR-INTERVAL-PSEUDO-EMITTER */
Object wait_for_interval_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,27);
    emit_stack_node_tree(byte_code_stream,SECOND(instruction));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)88L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* WAIT-PSEUDO-EMITTER */
Object wait_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,28);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)72L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qinstall_event_detector;  /* install-event-detector */

/* INSTALL-EVENT-DETECTOR-PSEUDO-EMITTER */
Object install_event_detector_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, location_expression, event_type_expression;

    x_note_fn_call(212,29);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    location_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    event_type_expression = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,location_expression);
    emit_stack_node_tree(byte_code_stream,event_type_expression);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qinstall_event_detector);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLEAR-EVENT-DETECTORS-PSEUDO-EMITTER */
Object clear_event_detectors_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,30);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COLLECT-DATA-PSEUDO-EMITTER */
Object collect_data_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_expression_pairs, timeout_varspot_qm;
    Object completed_tag_qm, failed_tag_qm, timeout_predicate_qm, success_spot;
    Object time_remaining_expression_qm, retry_tag, some_failed_tag;
    Object non_timeout_tag, success_tag, reversed_var_spots, var_spot;
    Object expression, ab_loop_list_, unknown_allowed_qm, ab_loop_desetq_;
    Object temp, known_tag;

    x_note_fn_call(212,31);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_expression_pairs = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    timeout_varspot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    completed_tag_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    failed_tag_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    timeout_predicate_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    success_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    time_remaining_expression_qm = CAR(gensymed_symbol);
    retry_tag = generate_new_goto_tag();
    some_failed_tag = generate_new_goto_tag();
    non_timeout_tag = generate_new_goto_tag();
    success_tag = generate_new_goto_tag();
    reversed_var_spots = Nil;
    if (timeout_varspot_qm) {
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	register_tag_in_byte_code_stream(2,byte_code_stream,retry_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)89L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)84L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	var_spot = Nil;
	expression = Nil;
	ab_loop_list_ = var_spot_expression_pairs;
	unknown_allowed_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	var_spot = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	expression = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	unknown_allowed_qm = type_specification_subtype_p(list_constant,
		ISVREF(expression,(SI_Long)6L));
	reversed_var_spots = phrase_cons(var_spot,reversed_var_spots);
	emit_stack_node_tree(byte_code_stream,expression);
	if (unknown_allowed_qm) {
	    known_tag = generate_new_goto_tag();
	    emit_branch_long_if_known_byte_codes(byte_code_stream,known_tag);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	    emit_push_constant_byte_codes(byte_code_stream,
		    Evaluation_false_value);
	    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		    success_spot);
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	    register_tag_in_byte_code_stream(2,byte_code_stream,known_tag);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	}
	goto next_loop;
      end_loop:;
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	emit_branch_long_if_true_byte_codes(byte_code_stream,success_tag);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	emit_branch_long_if_true_byte_codes(byte_code_stream,success_tag);
	emit_stack_node_tree(byte_code_stream,timeout_predicate_qm);
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		non_timeout_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)86L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)89L));
	var_spot = Nil;
	ab_loop_list_ = reversed_var_spots;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot);
	goto next_loop_1;
      end_loop_1:;
	if ( !EQL(completed_tag_qm,failed_tag_qm)) {
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    success_spot);
	    emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		    failed_tag_qm);
	}
	emit_branch_long_byte_codes(byte_code_stream,completed_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,non_timeout_tag);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		some_failed_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,success_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)86L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	var_spot = Nil;
	ab_loop_list_ = reversed_var_spots;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot);
	goto next_loop_2;
      end_loop_2:;
	emit_branch_long_byte_codes(byte_code_stream,completed_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,some_failed_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)85L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	emit_pop_values_byte_codes(byte_code_stream,
		length(reversed_var_spots));
	emit_stack_node_tree(byte_code_stream,time_remaining_expression_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)88L));
	emit_stack_node_tree(byte_code_stream,timeout_predicate_qm);
	emit_branch_long_byte_codes(byte_code_stream,retry_tag);
    }
    else {
	register_tag_in_byte_code_stream(2,byte_code_stream,retry_tag);
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)84L));
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_true_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	var_spot = Nil;
	expression = Nil;
	ab_loop_list_ = var_spot_expression_pairs;
	unknown_allowed_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	var_spot = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	expression = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	unknown_allowed_qm = type_specification_subtype_p(list_constant,
		ISVREF(expression,(SI_Long)6L));
	reversed_var_spots = phrase_cons(var_spot,reversed_var_spots);
	emit_stack_node_tree(byte_code_stream,expression);
	if (unknown_allowed_qm) {
	    known_tag = generate_new_goto_tag();
	    emit_branch_long_if_known_byte_codes(byte_code_stream,known_tag);
	    emit_push_constant_byte_codes(byte_code_stream,
		    Evaluation_false_value);
	    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		    success_spot);
	    register_tag_in_byte_code_stream(2,byte_code_stream,known_tag);
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
	}
	goto next_loop_3;
      end_loop_3:;
	emit_push_constant_byte_codes(byte_code_stream,Evaluation_false_value);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)119L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		success_spot);
	emit_branch_long_if_not_true_byte_codes(byte_code_stream,
		some_failed_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)86L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	var_spot = Nil;
	ab_loop_list_ = reversed_var_spots;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot);
	goto next_loop_4;
      end_loop_4:;
	emit_branch_long_byte_codes(byte_code_stream,completed_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,some_failed_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)85L));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
	emit_pop_values_byte_codes(byte_code_stream,
		length(reversed_var_spots));
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)72L));
	emit_branch_long_byte_codes(byte_code_stream,retry_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RETURN-FROM-FUNCTION-PSEUDO-EMITTER */
Object return_from_function_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object stack_node, stack_frame_vars;

    x_note_fn_call(212,32);
    stack_node = SECOND(instruction);
    stack_frame_vars = ISVREF(stack_node,(SI_Long)9L);
    if (IFIX(stack_frame_vars) > (SI_Long)0L) {
	emit_push_nones_byte_codes(byte_code_stream,stack_frame_vars);
	ISVREF(stack_node,(SI_Long)9L) = FIX((SI_Long)0L);
    }
    emit_stack_node_tree(byte_code_stream,stack_node);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)95L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SYSTEM-CALL-PSEUDO-EMITTER */
Object system_call_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spots, return_types, lisp_name, arguments, arg;
    Object ab_loop_list_, var_spot, return_type, ab_loop_list__1;

    x_note_fn_call(212,33);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spots = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    return_types = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    emit_push_constant_byte_codes(byte_code_stream,lisp_name);
    arg = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg);
    goto next_loop;
  end_loop:;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)97L));
    write_byte_code_to_stream(byte_code_stream,length(arguments));
    write_byte_code_to_stream(byte_code_stream,length(var_spots));
    var_spot = Nil;
    ab_loop_list_ = var_spots;
    return_type = Nil;
    ab_loop_list__1 = return_types;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    var_spot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    return_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    emit_type_check_byte_codes(byte_code_stream,return_type);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    goto next_loop_1;
  end_loop_1:;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EXECUTE-ANTECEDENT-PSEUDO-EMITTER */
Object execute_antecedent_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, logical_expression, certainty_var_spot_qm;
    Object expiration_var_spot_qm, true_tag, false_tag, unknown_tag_qm;
    Object known_tag;

    x_note_fn_call(212,34);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    logical_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    certainty_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    true_tag = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    false_tag = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_tag_qm = CAR(gensymed_symbol);
    known_tag = generate_new_goto_tag();
    emit_stack_node_tree(byte_code_stream,logical_expression);
    if (unknown_tag_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
	emit_branch_long_byte_codes(byte_code_stream,unknown_tag_qm);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_tag);
    }
    if (certainty_var_spot_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		certainty_var_spot_qm);
    }
    if (expiration_var_spot_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_var_spot_qm);
    }
    emit_branch_long_if_not_true_byte_codes(byte_code_stream,false_tag);
    emit_branch_long_byte_codes(byte_code_stream,true_tag);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EXECUTE-SIMULATION-FORMULA-PSEUDO-EMITTER */
Object execute_simulation_formula_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, expression, result_var_spot, unknown_tag;
    Object known_tag;

    x_note_fn_call(212,35);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    result_var_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_tag = CAR(gensymed_symbol);
    known_tag = generate_new_goto_tag();
    emit_stack_node_tree(byte_code_stream,expression);
    emit_branch_long_if_known_byte_codes(byte_code_stream,known_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    result_var_spot);
    emit_branch_long_byte_codes(byte_code_stream,unknown_tag);
    register_tag_in_byte_code_stream(2,byte_code_stream,known_tag);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    result_var_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPLETE-RULE-INSTANCE-PSEUDO-EMITTER */
Object complete_rule_instance_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,36);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)108L));
    write_byte_code_to_stream(byte_code_stream,SECOND(instruction) ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPLETE-SIMULATION-VARIABLE-EVALUATION-PSEUDO-EMITTER */
Object complete_simulation_variable_evaluation_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object value_known_qm;

    x_note_fn_call(212,37);
    value_known_qm = SECOND(instruction);
    emit_push_constant_byte_codes(byte_code_stream,value_known_qm ? 
	    Evaluation_true_value : Evaluation_false_value);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)114L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CHECK-STACK-PSEUDO-EMITTER */
Object check_stack_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,38);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)103L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* OPEN-WAKE-UP-COLLECTION-PSEUDO-EMITTER */
Object open_wake_up_collection_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,39);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)84L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SET-WAKE-UPS-PSEUDO-EMITTER */
Object set_wake_ups_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,40);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)85L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLEAR-WAKE-UPS-PSEUDO-EMITTER */
Object clear_wake_ups_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,41);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)86L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLOSE-WAKE-UP-COLLECTION-PSEUDO-EMITTER */
Object close_wake_up_collection_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,42);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)87L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SET-EXPIRATION-PSEUDO-EMITTER */
Object set_expiration_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot;

    x_note_fn_call(212,43);
    var_spot = SECOND(instruction);
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)22L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BRANCH-IF-KNOWN-PSEUDO-EMITTER */
Object branch_if_known_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object tag;

    x_note_fn_call(212,44);
    tag = SECOND(instruction);
    emit_branch_long_if_known_byte_codes(byte_code_stream,tag);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BEGIN-RULE-ACTIONS-PSEUDO-EMITTER */
Object begin_rule_actions_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,45);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)111L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ADD-TO-ACTION-CACHE-PSEUDO-EMITTER */
Object add_to_action_cache_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, action_cache, var_spot_block;

    x_note_fn_call(212,46);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    action_cache = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block = CAR(gensymed_symbol);
    emit_add_to_action_cache_byte_codes(byte_code_stream,action_cache,
	    var_spot_block);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RESTORE-FROM-ACTION-CACHE-OR-BRANCH-PSEUDO-EMITTER */
Object restore_from_action_cache_or_branch_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, action_cache, var_spot_block;
    Object action_cache_empty_tag;

    x_note_fn_call(212,47);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    action_cache = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    action_cache_empty_tag = CAR(gensymed_symbol);
    emit_restore_from_action_cache_or_branch_byte_codes(byte_code_stream,
	    action_cache,var_spot_block,action_cache_empty_tag);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CLEAR-ACTION-CACHE-PSEUDO-EMITTER */
Object clear_action_cache_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,48);
    emit_push_constant_byte_codes(byte_code_stream,Nil);
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    SECOND(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ALLOCATE-STACK-FRAME-VARS-PSEUDO-EMITTER */
Object allocate_stack_frame_vars_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_count_1;

    x_note_fn_call(212,49);
    var_count_1 = SECOND(instruction);
    if (IFIX(var_count_1) > (SI_Long)0L)
	emit_push_nones_byte_codes(byte_code_stream,var_count_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* DEALLOCATE-STACK-FRAME-VARS-PSEUDO-EMITTER */
Object deallocate_stack_frame_vars_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_count_1;

    x_note_fn_call(212,50);
    var_count_1 = SECOND(instruction);
    if (IFIX(var_count_1) > (SI_Long)0L)
	emit_pop_values_byte_codes(byte_code_stream,var_count_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPLETE-GENERIC-FORMULA-PSEUDO-EMITTER */
Object complete_generic_formula_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,51);
    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    SECOND(instruction));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)125L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPLETE-CELL-EXPRESSION-PSEUDO-EMITTER */
Object complete_cell_expression_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,52);
    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    SECOND(instruction));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)126L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BEGIN-ACTIVITY-PSEUDO-EMITTER */
Object begin_activity_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,53);
    emit_begin_activity_byte_codes(byte_code_stream,SECOND(instruction),
	    THIRD(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ASSERT-PSEUDO-EMITTER */
Object assert_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,54);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SIGNAL-ERROR-NEW-PSEUDO-EMITTER */
Object signal_error_new_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(212,55);
    emit_stack_node_tree(byte_code_stream,SECOND(instruction));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)137L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ANNOTATION-PSEUDO-EMITTER */
Object annotation_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object annotation_qm, gensymed_symbol, modify_macro_for_phrase_push_arg;
    Object svref_new_value;

    x_note_fn_call(212,56);
    annotation_qm = CADR(instruction);
    if (annotation_qm) {
	gensymed_symbol = phrase_list_3(ISVREF(byte_code_stream,
		(SI_Long)1L),ISVREF(annotation_qm,(SI_Long)1L),
		ISVREF(annotation_qm,(SI_Long)2L));
	modify_macro_for_phrase_push_arg = gensymed_symbol;
	svref_new_value = 
		phrase_cons_with_args_reversed(ISVREF(byte_code_stream,
		(SI_Long)8L),modify_macro_for_phrase_push_arg);
	SVREF(byte_code_stream,FIX((SI_Long)8L)) = svref_new_value;
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

void proc_inst2_INIT()
{
    Object tag_statement_pseudo_emitter_1, jump_tag_statement_pseudo_emitter_1;
    Object assign_local_var_pseudo_emitter_1, branch_pseudo_emitter_1;
    Object branch_if_true_pseudo_emitter_1;
    Object branch_if_not_true_pseudo_emitter_1, jump_pseudo_emitter_1;
    Object case_dispatch_pseudo_emitter_1, return_values_pseudo_emitter_1;
    Object call_pseudo_emitter_1, dependent_call_pseudo_emitter_1;
    Object receive_values_pseudo_emitter_1, call_rpc_pseudo_emitter_1;
    Object allow_other_processing_pseudo_emitter_1;
    Object open_role_iteration_no_domain_pseudo_emitter_1;
    Object open_role_iteration_pseudo_emitter_1;
    Object serve_next_iteration_value_pseudo_emitter_1;
    Object close_iteration_pseudo_emitter_1, signal_error_pseudo_emitter_1;
    Object close_code_body_pseudo_emitter_1, call_code_body_pseudo_emitter_1;
    Object call_scheduled_code_body_pseudo_emitter_1;
    Object wait_for_called_code_bodies_pseudo_emitter_1;
    Object abort_called_code_bodies_pseudo_emitter_1, pause_pseudo_emitter_1;
    Object pause_if_called_code_bodies_pseudo_emitter_1;
    Object polled_wait_pseudo_emitter_1, wait_for_interval_pseudo_emitter_1;
    Object wait_pseudo_emitter_1, install_event_detector_pseudo_emitter_1;
    Object clear_event_detectors_pseudo_emitter_1;
    Object collect_data_pseudo_emitter_1;
    Object return_from_function_pseudo_emitter_1, system_call_pseudo_emitter_1;
    Object execute_antecedent_pseudo_emitter_1;
    Object execute_simulation_formula_pseudo_emitter_1;
    Object complete_rule_instance_pseudo_emitter_1;
    Object complete_simulation_variable_evaluation_pseudo_emitter_1;
    Object check_stack_pseudo_emitter_1;
    Object open_wake_up_collection_pseudo_emitter_1;
    Object set_wake_ups_pseudo_emitter_1, clear_wake_ups_pseudo_emitter_1;
    Object close_wake_up_collection_pseudo_emitter_1;
    Object set_expiration_pseudo_emitter_1, branch_if_known_pseudo_emitter_1;
    Object begin_rule_actions_pseudo_emitter_1;
    Object add_to_action_cache_pseudo_emitter_1;
    Object restore_from_action_cache_or_branch_pseudo_emitter_1;
    Object clear_action_cache_pseudo_emitter_1;
    Object allocate_stack_frame_vars_pseudo_emitter_1;
    Object deallocate_stack_frame_vars_pseudo_emitter_1;
    Object complete_generic_formula_pseudo_emitter_1;
    Object complete_cell_expression_pseudo_emitter_1;
    Object begin_activity_pseudo_emitter_1, assert_pseudo_emitter_1;
    Object signal_error_new_pseudo_emitter_1, annotation_pseudo_emitter_1;
    Object Qpseudo_instruction_byte_code_emitter, Qannotation, AB_package;
    Object Qsignal_error_new, Qbegin_activity, Qcomplete_cell_expression;
    Object Qcomplete_generic_formula, Qdeallocate_stack_frame_vars;
    Object Qallocate_stack_frame_vars, Qclear_action_cache;
    Object Qrestore_from_action_cache_or_branch, Qadd_to_action_cache;
    Object Qbegin_rule_actions, Qbranch_if_known, Qset_expiration;
    Object Qclose_wake_up_collection, Qclear_wake_ups, Qset_wake_ups;
    Object Qopen_wake_up_collection, Qcheck_stack;
    Object Qcomplete_simulation_variable_evaluation, Qcomplete_rule_instance;
    Object Qexecute_simulation_formula, Qexecute_antecedent, Qsystem_call;
    Object Qreturn_from_function, Qcollect_data, Qclear_event_detectors, Qwait;
    Object Qwait_for_interval, Qpolled_wait, Qunknown_datum;
    Object Qpause_if_called_code_bodies, Qpause, Qabort_called_code_bodies;
    Object Qwait_for_called_code_bodies, Qcall_scheduled_code_body;
    Object Qcall_code_body, Qclose_code_body, Qsignal_error, Qclose_iteration;
    Object Qserve_next_iteration_value, Qopen_role_iteration;
    Object Qopen_role_iteration_no_domain, Qallow_other_processing, Qcall_rpc;
    Object Qreceive_values, Qdependent_call, Qcall, Qreturn_values;
    Object Qcase_dispatch, Qjump, Qbranch_if_not_true, Qbranch_if_true;
    Object Qbranch, Qassign_local_var, Qjump_tag_statement, Qtag_statement;

    x_note_fn_call(212,57);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qtag_statement = STATIC_SYMBOL("TAG-STATEMENT",AB_package);
    Qpseudo_instruction_byte_code_emitter = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-BYTE-CODE-EMITTER",AB_package);
    tag_statement_pseudo_emitter_1 = 
	    STATIC_FUNCTION(tag_statement_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qtag_statement,tag_statement_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qjump_tag_statement = STATIC_SYMBOL("JUMP-TAG-STATEMENT",AB_package);
    jump_tag_statement_pseudo_emitter_1 = 
	    STATIC_FUNCTION(jump_tag_statement_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qjump_tag_statement,
	    jump_tag_statement_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qassign_local_var = STATIC_SYMBOL("ASSIGN-LOCAL-VAR",AB_package);
    assign_local_var_pseudo_emitter_1 = 
	    STATIC_FUNCTION(assign_local_var_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qassign_local_var,
	    assign_local_var_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    branch_pseudo_emitter_1 = STATIC_FUNCTION(branch_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qbranch,branch_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbranch_if_true = STATIC_SYMBOL("BRANCH-IF-TRUE",AB_package);
    branch_if_true_pseudo_emitter_1 = 
	    STATIC_FUNCTION(branch_if_true_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qbranch_if_true,branch_if_true_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbranch_if_not_true = STATIC_SYMBOL("BRANCH-IF-NOT-TRUE",AB_package);
    branch_if_not_true_pseudo_emitter_1 = 
	    STATIC_FUNCTION(branch_if_not_true_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qbranch_if_not_true,
	    branch_if_not_true_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qjump = STATIC_SYMBOL("JUMP",AB_package);
    jump_pseudo_emitter_1 = STATIC_FUNCTION(jump_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qjump,jump_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcase_dispatch = STATIC_SYMBOL("CASE-DISPATCH",AB_package);
    case_dispatch_pseudo_emitter_1 = 
	    STATIC_FUNCTION(case_dispatch_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcase_dispatch,case_dispatch_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qreturn_values = STATIC_SYMBOL("RETURN-VALUES",AB_package);
    return_values_pseudo_emitter_1 = 
	    STATIC_FUNCTION(return_values_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qreturn_values,return_values_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    string_constant = 
	    STATIC_STRING("CALL accepts a maximum of 255 arguments, this call passed ~a.");
    string_constant_1 = 
	    STATIC_STRING("CALL receives a maximum of 255 values, this call requested ~a.");
    call_pseudo_emitter_1 = STATIC_FUNCTION(call_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcall,call_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qdependent_call = STATIC_SYMBOL("DEPENDENT-CALL",AB_package);
    dependent_call_pseudo_emitter_1 = 
	    STATIC_FUNCTION(dependent_call_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qdependent_call,dependent_call_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qreceive_values = STATIC_SYMBOL("RECEIVE-VALUES",AB_package);
    Qpush_returned_values_long = STATIC_SYMBOL("PUSH-RETURNED-VALUES-LONG",
	    AB_package);
    Qpush_returned_values = STATIC_SYMBOL("PUSH-RETURNED-VALUES",AB_package);
    receive_values_pseudo_emitter_1 = 
	    STATIC_FUNCTION(receive_values_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qreceive_values,receive_values_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_rpc = STATIC_SYMBOL("CALL-RPC",AB_package);
    string_constant_2 = 
	    STATIC_STRING("CALL-ACROSS accepts a maximum of 255 arguments, this call passed ~a.");
    string_constant_3 = 
	    STATIC_STRING("CALL-ACROSS receives a maximum of 255 values, this call requested ~a.");
    call_rpc_pseudo_emitter_1 = STATIC_FUNCTION(call_rpc_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qcall_rpc,call_rpc_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qallow_other_processing = STATIC_SYMBOL("ALLOW-OTHER-PROCESSING",
	    AB_package);
    allow_other_processing_pseudo_emitter_1 = 
	    STATIC_FUNCTION(allow_other_processing_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qallow_other_processing,
	    allow_other_processing_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qopen_role_iteration_no_domain = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    open_role_iteration_no_domain_pseudo_emitter_1 = 
	    STATIC_FUNCTION(open_role_iteration_no_domain_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qopen_role_iteration_no_domain,
	    open_role_iteration_no_domain_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qopen_role_iteration = STATIC_SYMBOL("OPEN-ROLE-ITERATION",AB_package);
    open_role_iteration_pseudo_emitter_1 = 
	    STATIC_FUNCTION(open_role_iteration_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qopen_role_iteration,
	    open_role_iteration_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qserve_next_iteration_value = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE",AB_package);
    serve_next_iteration_value_pseudo_emitter_1 = 
	    STATIC_FUNCTION(serve_next_iteration_value_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qserve_next_iteration_value,
	    serve_next_iteration_value_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclose_iteration = STATIC_SYMBOL("CLOSE-ITERATION",AB_package);
    close_iteration_pseudo_emitter_1 = 
	    STATIC_FUNCTION(close_iteration_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qclose_iteration,
	    close_iteration_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qsignal_error = STATIC_SYMBOL("SIGNAL-ERROR",AB_package);
    signal_error_pseudo_emitter_1 = 
	    STATIC_FUNCTION(signal_error_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qsignal_error,signal_error_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclose_code_body = STATIC_SYMBOL("CLOSE-CODE-BODY",AB_package);
    close_code_body_pseudo_emitter_1 = 
	    STATIC_FUNCTION(close_code_body_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qclose_code_body,
	    close_code_body_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_code_body = STATIC_SYMBOL("CALL-CODE-BODY",AB_package);
    call_code_body_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_code_body_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcall_code_body,call_code_body_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_scheduled_code_body = STATIC_SYMBOL("CALL-SCHEDULED-CODE-BODY",
	    AB_package);
    call_scheduled_code_body_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_scheduled_code_body_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcall_scheduled_code_body,
	    call_scheduled_code_body_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qwait_for_called_code_bodies = 
	    STATIC_SYMBOL("WAIT-FOR-CALLED-CODE-BODIES",AB_package);
    wait_for_called_code_bodies_pseudo_emitter_1 = 
	    STATIC_FUNCTION(wait_for_called_code_bodies_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qwait_for_called_code_bodies,
	    wait_for_called_code_bodies_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qabort_called_code_bodies = STATIC_SYMBOL("ABORT-CALLED-CODE-BODIES",
	    AB_package);
    abort_called_code_bodies_pseudo_emitter_1 = 
	    STATIC_FUNCTION(abort_called_code_bodies_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qabort_called_code_bodies,
	    abort_called_code_bodies_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    pause_pseudo_emitter_1 = STATIC_FUNCTION(pause_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qpause,pause_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qpause_if_called_code_bodies = 
	    STATIC_SYMBOL("PAUSE-IF-CALLED-CODE-BODIES",AB_package);
    pause_if_called_code_bodies_pseudo_emitter_1 = 
	    STATIC_FUNCTION(pause_if_called_code_bodies_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qpause_if_called_code_bodies,
	    pause_if_called_code_bodies_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qpolled_wait = STATIC_SYMBOL("POLLED-WAIT",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant = STATIC_CONS(Qunknown_datum,Qnil);
    polled_wait_pseudo_emitter_1 = 
	    STATIC_FUNCTION(polled_wait_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qpolled_wait,polled_wait_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qwait_for_interval = STATIC_SYMBOL("WAIT-FOR-INTERVAL",AB_package);
    wait_for_interval_pseudo_emitter_1 = 
	    STATIC_FUNCTION(wait_for_interval_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qwait_for_interval,
	    wait_for_interval_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qwait = STATIC_SYMBOL("WAIT",AB_package);
    wait_pseudo_emitter_1 = STATIC_FUNCTION(wait_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qwait,wait_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qinstall_event_detector = STATIC_SYMBOL("INSTALL-EVENT-DETECTOR",
	    AB_package);
    install_event_detector_pseudo_emitter_1 = 
	    STATIC_FUNCTION(install_event_detector_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qinstall_event_detector,
	    install_event_detector_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclear_event_detectors = STATIC_SYMBOL("CLEAR-EVENT-DETECTORS",AB_package);
    clear_event_detectors_pseudo_emitter_1 = 
	    STATIC_FUNCTION(clear_event_detectors_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qclear_event_detectors,
	    clear_event_detectors_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcollect_data = STATIC_SYMBOL("COLLECT-DATA",AB_package);
    collect_data_pseudo_emitter_1 = 
	    STATIC_FUNCTION(collect_data_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcollect_data,collect_data_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qreturn_from_function = STATIC_SYMBOL("RETURN-FROM-FUNCTION",AB_package);
    return_from_function_pseudo_emitter_1 = 
	    STATIC_FUNCTION(return_from_function_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qreturn_from_function,
	    return_from_function_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qsystem_call = STATIC_SYMBOL("SYSTEM-CALL",AB_package);
    system_call_pseudo_emitter_1 = 
	    STATIC_FUNCTION(system_call_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qsystem_call,system_call_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qexecute_antecedent = STATIC_SYMBOL("EXECUTE-ANTECEDENT",AB_package);
    execute_antecedent_pseudo_emitter_1 = 
	    STATIC_FUNCTION(execute_antecedent_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qexecute_antecedent,
	    execute_antecedent_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qexecute_simulation_formula = 
	    STATIC_SYMBOL("EXECUTE-SIMULATION-FORMULA",AB_package);
    execute_simulation_formula_pseudo_emitter_1 = 
	    STATIC_FUNCTION(execute_simulation_formula_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qexecute_simulation_formula,
	    execute_simulation_formula_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcomplete_rule_instance = STATIC_SYMBOL("COMPLETE-RULE-INSTANCE",
	    AB_package);
    complete_rule_instance_pseudo_emitter_1 = 
	    STATIC_FUNCTION(complete_rule_instance_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcomplete_rule_instance,
	    complete_rule_instance_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcomplete_simulation_variable_evaluation = 
	    STATIC_SYMBOL("COMPLETE-SIMULATION-VARIABLE-EVALUATION",
	    AB_package);
    complete_simulation_variable_evaluation_pseudo_emitter_1 = 
	    STATIC_FUNCTION(complete_simulation_variable_evaluation_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qcomplete_simulation_variable_evaluation,
	    complete_simulation_variable_evaluation_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcheck_stack = STATIC_SYMBOL("CHECK-STACK",AB_package);
    check_stack_pseudo_emitter_1 = 
	    STATIC_FUNCTION(check_stack_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcheck_stack,check_stack_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qopen_wake_up_collection = STATIC_SYMBOL("OPEN-WAKE-UP-COLLECTION",
	    AB_package);
    open_wake_up_collection_pseudo_emitter_1 = 
	    STATIC_FUNCTION(open_wake_up_collection_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qopen_wake_up_collection,
	    open_wake_up_collection_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qset_wake_ups = STATIC_SYMBOL("SET-WAKE-UPS",AB_package);
    set_wake_ups_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_wake_ups_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_wake_ups,set_wake_ups_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclear_wake_ups = STATIC_SYMBOL("CLEAR-WAKE-UPS",AB_package);
    clear_wake_ups_pseudo_emitter_1 = 
	    STATIC_FUNCTION(clear_wake_ups_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qclear_wake_ups,clear_wake_ups_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclose_wake_up_collection = STATIC_SYMBOL("CLOSE-WAKE-UP-COLLECTION",
	    AB_package);
    close_wake_up_collection_pseudo_emitter_1 = 
	    STATIC_FUNCTION(close_wake_up_collection_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qclose_wake_up_collection,
	    close_wake_up_collection_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qset_expiration = STATIC_SYMBOL("SET-EXPIRATION",AB_package);
    set_expiration_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_expiration_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_expiration,set_expiration_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbranch_if_known = STATIC_SYMBOL("BRANCH-IF-KNOWN",AB_package);
    branch_if_known_pseudo_emitter_1 = 
	    STATIC_FUNCTION(branch_if_known_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qbranch_if_known,
	    branch_if_known_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbegin_rule_actions = STATIC_SYMBOL("BEGIN-RULE-ACTIONS",AB_package);
    begin_rule_actions_pseudo_emitter_1 = 
	    STATIC_FUNCTION(begin_rule_actions_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qbegin_rule_actions,
	    begin_rule_actions_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qadd_to_action_cache = STATIC_SYMBOL("ADD-TO-ACTION-CACHE",AB_package);
    add_to_action_cache_pseudo_emitter_1 = 
	    STATIC_FUNCTION(add_to_action_cache_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qadd_to_action_cache,
	    add_to_action_cache_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qrestore_from_action_cache_or_branch = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH",AB_package);
    restore_from_action_cache_or_branch_pseudo_emitter_1 = 
	    STATIC_FUNCTION(restore_from_action_cache_or_branch_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qrestore_from_action_cache_or_branch,
	    restore_from_action_cache_or_branch_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclear_action_cache = STATIC_SYMBOL("CLEAR-ACTION-CACHE",AB_package);
    clear_action_cache_pseudo_emitter_1 = 
	    STATIC_FUNCTION(clear_action_cache_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qclear_action_cache,
	    clear_action_cache_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qallocate_stack_frame_vars = STATIC_SYMBOL("ALLOCATE-STACK-FRAME-VARS",
	    AB_package);
    allocate_stack_frame_vars_pseudo_emitter_1 = 
	    STATIC_FUNCTION(allocate_stack_frame_vars_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qallocate_stack_frame_vars,
	    allocate_stack_frame_vars_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qdeallocate_stack_frame_vars = 
	    STATIC_SYMBOL("DEALLOCATE-STACK-FRAME-VARS",AB_package);
    deallocate_stack_frame_vars_pseudo_emitter_1 = 
	    STATIC_FUNCTION(deallocate_stack_frame_vars_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qdeallocate_stack_frame_vars,
	    deallocate_stack_frame_vars_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcomplete_generic_formula = STATIC_SYMBOL("COMPLETE-GENERIC-FORMULA",
	    AB_package);
    complete_generic_formula_pseudo_emitter_1 = 
	    STATIC_FUNCTION(complete_generic_formula_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcomplete_generic_formula,
	    complete_generic_formula_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcomplete_cell_expression = STATIC_SYMBOL("COMPLETE-CELL-EXPRESSION",
	    AB_package);
    complete_cell_expression_pseudo_emitter_1 = 
	    STATIC_FUNCTION(complete_cell_expression_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcomplete_cell_expression,
	    complete_cell_expression_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qbegin_activity = STATIC_SYMBOL("BEGIN-ACTIVITY",AB_package);
    begin_activity_pseudo_emitter_1 = 
	    STATIC_FUNCTION(begin_activity_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qbegin_activity,begin_activity_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    assert_pseudo_emitter_1 = STATIC_FUNCTION(assert_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qassert,assert_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qsignal_error_new = STATIC_SYMBOL("SIGNAL-ERROR-NEW",AB_package);
    signal_error_new_pseudo_emitter_1 = 
	    STATIC_FUNCTION(signal_error_new_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qsignal_error_new,
	    signal_error_new_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    annotation_pseudo_emitter_1 = 
	    STATIC_FUNCTION(annotation_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qannotation,annotation_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
}
