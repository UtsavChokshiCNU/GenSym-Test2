/* pcnst.c
 * Input file:  proc-inst.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pcnst.h"


static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* PRINT-START-INSTRUCTION */
Object print_start_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, argument_expressions, priority_qm;
    Object wait_qm, across_qm, arg, ab_loop_list_, first_time_qm;
    Object ab_loop_iter_flag_;

    x_note_fn_call(211,0);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    argument_expressions = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    priority_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    across_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)6L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = argument_expressions;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)8L));
    if (wait_qm)
	write_expression(wait_qm);
    else
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)2L));
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)12L));
    if (priority_qm) {
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)9L));
	write_expression(priority_qm);
    }
    else
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)16L));
    if (across_qm) {
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)8L));
	return print_designation(across_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qannotation;         /* annotation */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qitem_or_datum;      /* item-or-datum */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object string_constant;     /* "Because of an argument count mismatch for ~ND, a call to it ~
				    *                 could not be optimized."
				    */

static Object Qstable_remote_procedure_call;  /* stable-remote-procedure-call */

static Object Qstable_procedure_call;  /* stable-procedure-call */

static Object Qbegin_activity;     /* begin-activity */

static Object Qstart_rpc_prolog;   /* start-rpc-prolog */

static Object Qstart_prolog;       /* start-prolog */

static Object Qstart_rpc_epilog;   /* start-rpc-epilog */

static Object Qstart_epilog;       /* start-epilog */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qremote_procedure_call;  /* remote-procedure-call */

static Object Qprocedure_call;     /* procedure-call */

/* START-ACTION-COMPILER */
Object start_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object argument_expressions, priority_qm, wait_qm, across_qm;
    Object argument_count, argument_stack_nodes, stable_procedure_qm;
    Object stable_arg_types_qm, recorded_procedure_call_free_reference_qm;
    Object compiled_procedure_or_rpd, temp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1, temp_2, temp_3, block_of_variables_qm;
    Object gensymed_symbol_3, car_new_value, argument, ab_loop_list_;
    Object type_cons_qm, ab_loop_iter_flag_, argument_node;
    SI_Long ab_loop_repeat_, gensymed_symbol_4, gensymed_symbol_5;

    x_note_fn_call(211,1);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    argument_expressions = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    priority_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    wait_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    across_qm = CAR(gensymed_symbol_2);
    argument_count = length(argument_expressions);
    argument_stack_nodes = Nil;
    stable_procedure_qm = Nil;
    stable_arg_types_qm = Nil;
    recorded_procedure_call_free_reference_qm = Nil;
    compiled_procedure_or_rpd = compile_stack_expression(designation,
	    maybe_add_unknown(across_qm ? list_constant : list_constant_1,
	    unknown_allowed_qm));
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = phrase_cons(generate_new_variable_spot(1,across_qm ? 
		list_constant : list_constant_1),Nil);
	ab_loop_repeat_ = IFIX(argument_count);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,
		Qitem_or_datum),Nil);
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
	if (across_qm) {
	    temp_2 = generate_new_variable_spot(1,list_constant_2);
	    temp_3 = generate_new_variable_spot(1,list_constant_3);
	    temp_3 = phrase_list_3(temp_2,temp_3,
		    generate_new_variable_spot(1,list_constant_4));
	}
	else {
	    temp_3 = generate_new_variable_spot(1,list_constant_2);
	    temp_3 = phrase_list_2(temp_3,generate_new_variable_spot(1,
		    list_constant_3));
	}
	block_of_variables_qm = nconc2(temp,nconc2(temp_1,temp_3));
    }
    else
	block_of_variables_qm = Nil;
    if (dependent_compilation_p(0)) {
	stable_procedure_qm = stable_denoted_procedure_p(1,
		compiled_procedure_or_rpd);
	if (stable_procedure_qm) {
	    stable_arg_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)24L));
	    if (FIXNUM_NE(length(stable_arg_types_qm),argument_count)) {
		compiler_dependence_warning(2,string_constant,designation);
		stable_arg_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else {
		recorded_procedure_call_free_reference_qm = T;
		record_free_reference(across_qm ? 
			Qstable_remote_procedure_call : 
			Qstable_procedure_call,phrase_list_3(designation,
			stable_arg_types_qm,Nil));
	    }
	}
    }
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,across_qm ? FIX((SI_Long)22L) : 
	    FIX((SI_Long)23L),unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)9L));
    gensymed_symbol_3 = gensymed_symbol_2;
    car_new_value = across_qm ? Qstart_rpc_prolog : Qstart_prolog;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = compiled_procedure_or_rpd;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    argument = Nil;
    ab_loop_list_ = argument_expressions;
    type_cons_qm = stable_arg_types_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	type_cons_qm = CDR(type_cons_qm);
    temp = argument;
    temp_3 = CAR(type_cons_qm);
    if (temp_3);
    else
	temp_3 = Qitem_or_datum;
    ab_loopvar__2 = phrase_cons(compile_stack_expression(temp,
	    maybe_add_unknown(temp_3,unknown_allowed_qm)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    argument_stack_nodes = ab_loopvar_;
    goto end_2;
    argument_stack_nodes = Qnil;
  end_2:;
    M_CAR(gensymed_symbol_3) = argument_stack_nodes;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = priority_qm ? compile_stack_expression(priority_qm,
	    maybe_add_unknown(Qinteger,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = wait_qm ? compile_stack_expression(wait_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = across_qm ? compile_stack_expression(across_qm,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = stable_procedure_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,across_qm ? 
		FIX((SI_Long)22L) : FIX((SI_Long)23L)));
    temp_3 = block_of_variables_qm;
    if (temp_3);
    else {
	gensymed_symbol_4 = IFIX(length(argument_expressions));
	gensymed_symbol_5 = across_qm ? (SI_Long)4L : (SI_Long)3L;
	temp_3 = FIX(gensymed_symbol_4 + gensymed_symbol_5);
    }
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(across_qm ? Qstart_rpc_epilog : Qstart_epilog,
	    temp_3));
    if ( !TRUEP(recorded_procedure_call_free_reference_qm) && 
	    SYMBOLP(designation) &&  
	    !TRUEP(indirectly_denoted_item_p(compiled_procedure_or_rpd))) {
	argument_node = Nil;
	ab_loop_list_ = argument_stack_nodes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(type_specification_minus_type(type_specification_minus_type(ISVREF(argument_node,
		(SI_Long)6L),list_constant_5),list_constant_6),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	temp_3 = ab_loopvar_;
	goto end_3;
	temp_3 = Qnil;
      end_3:;
	record_free_reference(across_qm ? Qremote_procedure_call : 
		Qprocedure_call,phrase_list_3(designation,temp_3,Nil));
    }
    temp_3 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_3);
    return VALUES_1(Nil);
}

/* EMIT-COMMON-START-BYTES */
Object emit_common_start_bytes(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure, arguments, priority_qm, wait_qm;
    Object argument, ab_loop_list_;

    x_note_fn_call(211,2);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    priority_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(priority_qm) &&  !TRUEP(wait_qm))
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)2L));
    else {
	if (priority_qm)
	    emit_stack_node_tree(byte_code_stream,priority_qm);
	else
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	if (wait_qm)
	    emit_stack_node_tree(byte_code_stream,wait_qm);
	else
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    }
    return length(arguments);
}

static Object Qprepare_possibly_unknown_procedure_arguments;  /* prepare-possibly-unknown-procedure-arguments */

static Object Qprepare_procedure_arguments;  /* prepare-procedure-arguments */

/* EMIT-ACTION-COMMON-START-BYTES */
Object emit_action_common_start_bytes(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure, arguments, priority_qm, wait_qm;
    Object across_qm, unknown_allowed_qm, var_spot_block_qm;
    Object stable_procedure_qm, argument, ab_loop_list_, args_plus_1;

    x_note_fn_call(211,3);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    priority_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    across_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    stable_procedure_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(stable_procedure_qm)) {
	args_plus_1 = add1(length(arguments));
	emit_funcall_instruction_byte_codes(4,byte_code_stream,
		unknown_allowed_qm ? 
		Qprepare_possibly_unknown_procedure_arguments : 
		Qprepare_procedure_arguments,args_plus_1,args_plus_1);
    }
    if ( !TRUEP(priority_qm) &&  !TRUEP(wait_qm))
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)2L));
    else {
	if (priority_qm)
	    emit_stack_node_tree(byte_code_stream,priority_qm);
	else
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	if (wait_qm)
	    emit_stack_node_tree(byte_code_stream,wait_qm);
	else
	    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    }
    if (across_qm)
	emit_stack_node_tree(byte_code_stream,across_qm);
    if (var_spot_block_qm)
	return emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    else
	return VALUES_1(Nil);
}

/* START-PROLOG-PSEUDO-EMITTER */
Object start_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,4);
    emit_action_common_start_bytes(byte_code_stream,instruction);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* START-RPC-PROLOG-PSEUDO-EMITTER */
Object start_rpc_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,5);
    emit_action_common_start_bytes(byte_code_stream,instruction);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstart;              /* start */

/* START-EPILOG-PSEUDO-EMITTER */
Object start_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, var_spot, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long args_remaining;

    x_note_fn_call(211,6);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm &&  !FIXNUMP(var_spot_block_qm)) {
	var_spot = Nil;
	ab_loop_list_ = var_spot_block_qm;
	args_remaining = IFIX(FIXNUM_SUB1(length(var_spot_block_qm)));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    args_remaining = args_remaining - (SI_Long)1L;
	if (args_remaining < (SI_Long)0L)
	    goto end_loop;
	if (args_remaining == (SI_Long)1L || args_remaining == (SI_Long)0L)
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	else
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    emit_funcall_instruction_byte_codes(4,byte_code_stream,Qstart,
	    FIXNUMP(var_spot_block_qm) ? var_spot_block_qm : 
	    length(var_spot_block_qm),FIX((SI_Long)0L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstart_rpc;          /* start-rpc */

/* START-RPC-EPILOG-PSEUDO-EMITTER */
Object start_rpc_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, var_spot, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long args_remaining;

    x_note_fn_call(211,7);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm &&  !FIXNUMP(var_spot_block_qm)) {
	var_spot = Nil;
	ab_loop_list_ = var_spot_block_qm;
	args_remaining = IFIX(FIXNUM_SUB1(length(var_spot_block_qm)));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    args_remaining = args_remaining - (SI_Long)1L;
	if (args_remaining < (SI_Long)0L)
	    goto end_loop;
	if (args_remaining == (SI_Long)2L || args_remaining == (SI_Long)1L)
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	else
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    emit_funcall_instruction_byte_codes(4,byte_code_stream,Qstart_rpc,
	    FIXNUMP(var_spot_block_qm) ? var_spot_block_qm : 
	    length(var_spot_block_qm),FIX((SI_Long)0L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qattribute_value;    /* attribute-value */

static Object Qdatum;              /* datum */

static Object list_constant_7;     /* # */

static Object Qitem;               /* item */

static Object Qattribute_of_class;  /* attribute-of-class */

static Object Qclass_qualified_attribute_of_class;  /* class-qualified-attribute-of-class */

static Object Qconclude_attribute_prolog;  /* conclude-attribute-prolog */

static Object Qtrue;               /* true */

static Object Qconclude_attribute_epilog;  /* conclude-attribute-epilog */

static Object Qtruth_value;        /* truth-value */

static Object string_constant_1;   /* "In the conclude action, the local name ~a is declared to ~
				    *                         hold ~NT, not ~NT."
				    */

static Object Qcompare_and_swap_prolog;  /* compare-and-swap-prolog */

static Object Qcompare_and_swap_epilog;  /* compare-and-swap-epilog */

static Object Qconclude_prolog;    /* conclude-prolog */

static Object Qconclude_epilog;    /* conclude-epilog */

/* COMPILE-CONCLUDE-ACTION */
Object compile_conclude_action(designation,expression_qm,expiration_qm,
	    collection_qm,old_value_qm,local_name_qm,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object designation, expression_qm, expiration_qm, collection_qm;
    Object old_value_qm, local_name_qm, unknown_allowed_qm, leave_on_stack_qm;
    Object prolog_stream, epilog_stream;
{
    Object role, item_designation, attribute_name_expr, class_qualifier_qm;
    Object value_type, temp_1, temp_2, temp_3, block_of_variables_qm;
    Object compiled_class_qualifer_qm, compiled_attribute_name;
    Object compiled_item_or_place_reference, item_or_place_reference_type;
    Object item_class, gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object var_spot_qm, var_spot_description_qm, var_spot_type_qm;
    Object compiler_error_qm, created_type, check_created_type_qm;
    char temp;
    Object result;

    x_note_fn_call(211,8);
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)24L),
	    unknown_allowed_qm));
    designation = rebuild_deep_conclude_designation(designation);
    if ( !TRUEP(expiration_qm) &&  !TRUEP(collection_qm)) {
	if (CONSP(designation) && IFIX(length(designation)) >= (SI_Long)3L) {
	    role = SECOND(designation);
	    temp = SYMBOLP(role);
	    if (temp);
	    else
		temp = CONSP(role) ? EQ(M_CAR(role),Qclass_qualified_name) 
			: TRUEP(Qnil);
	    if (temp);
	    else
		temp = CONSP(role) ? EQ(M_CAR(role),Qattribute_value) : 
			TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	role = SECOND(designation);
	item_designation = THIRD(designation);
	if (SYMBOLP(role))
	    attribute_name_expr = phrase_list_2(Qquote,role);
	else if (CONSP(role) && EQ(M_CAR(role),Qclass_qualified_name))
	    attribute_name_expr = phrase_list_2(Qquote,CONSP(role) ? 
		    M_CAR(M_CDR(M_CDR(role))) : role);
	else
	    attribute_name_expr = FOURTH(designation);
	class_qualifier_qm = CONSP(role) && EQ(M_CAR(role),
		Qclass_qualified_name) ? (CONSP(role) ? M_CAR(M_CDR(role)) 
		: Nil) : Nil;
	value_type = CONSP(role) && EQ(M_CAR(role),Qattribute_value) ? 
		type_specification_of_role(role) : Qdatum;
	if ( !TRUEP(leave_on_stack_qm)) {
	    temp_1 = generate_new_variable_spot(1,Qsymbol);
	    temp_2 = generate_new_variable_spot(1,Qsymbol);
	    temp_3 = generate_new_variable_spot(1,list_constant_4);
	    block_of_variables_qm = phrase_list_4(temp_1,temp_2,temp_3,
		    generate_new_variable_spot(1,Qdatum));
	}
	else
	    block_of_variables_qm = Nil;
	compiled_class_qualifer_qm = class_qualifier_qm ? 
		compile_stack_expression(phrase_list_2(Qquote,
		class_qualifier_qm),Qsymbol) : Nil;
	compiled_attribute_name = 
		compile_stack_expression(attribute_name_expr,Qsymbol);
	compiled_item_or_place_reference = 
		compile_stack_expression(item_designation,
		maybe_add_unknown(list_constant_7,unknown_allowed_qm));
	item_or_place_reference_type = 
		primary_type_of_type_specification(ISVREF(compiled_item_or_place_reference,
		(SI_Long)6L));
	if (CONSP(attribute_name_expr) && EQ(CAR(attribute_name_expr),
		    Qquote)) {
	    temp_3 = SECOND(attribute_name_expr);
	    temp = SYMBOLP(temp_3);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? 
		TRUEP(type_specification_subtype_p(item_or_place_reference_type,
		list_constant_4)) : TRUEP(Nil)) {
	    item_class = 
		    class_type_specification_p(item_or_place_reference_type) 
		    ? M_CAR(M_CDR(item_or_place_reference_type)) : Qitem;
	    if ( !TRUEP(class_qualifier_qm))
		record_free_reference(Qattribute_of_class,
			phrase_cons(SECOND(attribute_name_expr),item_class));
	    else
		record_free_reference(Qclass_qualified_attribute_of_class,
			phrase_list_3(SECOND(attribute_name_expr),
			class_qualifier_qm,item_class));
	}
	if ( !TRUEP(type_specification_subtype_p(value_type,Qdatum)))
	    value_type = Qdatum;
	gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qconclude_attribute_prolog;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = compiled_class_qualifer_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = compiled_attribute_name;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = compiled_item_or_place_reference;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = expression_qm ? 
		compile_stack_expression(expression_qm,
		maybe_add_unknown(value_type,unknown_allowed_qm)) : 
		compile_stack_expression(Qtrue,value_type);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = block_of_variables_qm;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)24L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qconclude_attribute_epilog,
		block_of_variables_qm));
	return VALUES_1(block_of_variables_qm);
    }
    else if (old_value_qm) {
	var_spot_qm = Nil;
	var_spot_description_qm = Nil;
	var_spot_type_qm = Nil;
	compiler_error_qm = Nil;
	created_type = Qtruth_value;
	check_created_type_qm = Nil;
	if ( !TRUEP(leave_on_stack_qm)) {
	    temp_1 = generate_new_variable_spot(1,list_constant_7);
	    temp_2 = generate_new_variable_spot(1,Qdatum);
	    temp_3 = generate_new_variable_spot(1,Qdatum);
	    block_of_variables_qm = phrase_list_4(temp_1,temp_2,temp_3,
		    generate_new_variable_spot(1,Qdatum));
	}
	else
	    block_of_variables_qm = Nil;
	if (local_name_qm) {
	    result = variable_spot_and_description_for_local_name(local_name_qm);
	    MVS_2(result,var_spot_qm,var_spot_description_qm);
	    if ( !TRUEP(var_spot_qm)) {
		compiler_error_qm = T;
		procedure_compiler_missing_local_name_error(local_name_qm);
	    }
	    else {
		var_spot_type_qm = 
			getfq_function_no_default(CDR(var_spot_description_qm),
			Ktype);
		if ( !TRUEP(type_specification_subtype_p(created_type,
			var_spot_type_qm))) {
		    if (type_specifications_could_intersect_p(created_type,
			    var_spot_type_qm))
			check_created_type_qm = var_spot_type_qm;
		    else
			compiler_error(4,string_constant_1,local_name_qm,
				var_spot_type_qm,created_type);
		}
	    }
	}
	if ( !TRUEP(compiler_error_qm)) {
	    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qcompare_and_swap_prolog;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = compile_stack_expression(designation,
		    maybe_add_unknown(list_constant_7,unknown_allowed_qm));
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = expression_qm ? 
		    compile_stack_expression(expression_qm,
		    maybe_add_unknown(Qdatum,unknown_allowed_qm)) : 
		    compile_stack_expression(Qtrue,Qdatum);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = old_value_qm ? 
		    compile_stack_expression(old_value_qm,
		    maybe_add_unknown(Qdatum,unknown_allowed_qm)) : Nil;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = block_of_variables_qm;
	    emit_already_consed_instruction_to_stream(prolog_stream,
		    gensymed_symbol);
	    if (unknown_allowed_qm)
		emit_already_consed_instruction_to_stream(epilog_stream,
			phrase_list_2(Qbegin_activity,FIX((SI_Long)24L)));
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_4(Qcompare_and_swap_epilog,var_spot_qm,
		    check_created_type_qm,block_of_variables_qm));
	}
	return VALUES_1(block_of_variables_qm);
    }
    else {
	if ( !TRUEP(leave_on_stack_qm)) {
	    temp_1 = generate_new_variable_spot(1,list_constant_7);
	    temp_2 = generate_new_variable_spot(1,Qdatum);
	    temp_3 = generate_new_variable_spot(1,Qnumber);
	    block_of_variables_qm = phrase_list_4(temp_1,temp_2,temp_3,
		    generate_new_variable_spot(1,Qnumber));
	}
	else
	    block_of_variables_qm = Nil;
	gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qconclude_prolog;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = compile_stack_expression(designation,
		maybe_add_unknown(list_constant_7,unknown_allowed_qm));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = expression_qm ? 
		compile_stack_expression(expression_qm,
		maybe_add_unknown(Qdatum,unknown_allowed_qm)) : 
		compile_stack_expression(Qtrue,Qdatum);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = expiration_qm ? 
		compile_stack_expression(expiration_qm,
		maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = collection_qm ? 
		compile_stack_expression(collection_qm,
		maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = block_of_variables_qm;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)24L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qconclude_epilog,block_of_variables_qm));
	return VALUES_1(block_of_variables_qm);
    }
}

/* CONCLUDE-ACTION-COMPILER */
Object conclude_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object expression_qm, expiration_qm, collection_qm, old_value_qm;
    Object local_name_qm, temp;

    x_note_fn_call(211,9);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    expression_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    expiration_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    collection_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    old_value_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    temp = compile_conclude_action(designation,expression_qm,expiration_qm,
	    collection_qm,old_value_qm,local_name_qm,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* REBUILD-DEEP-CONCLUDE-DESIGNATION */
Object rebuild_deep_conclude_designation(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(211,10);
    temp = Current_let_action_bindings ? 
	    rebuild_deep_conclude_designation_1(copy_tree_using_phrase_conses(designation)) 
	    : designation;
    return VALUES_1(temp);
}

Object Deep_concludable_role_names = UNBOUND;

/* REBUILD-DEEP-CONCLUDE-DESIGNATION-1 */
Object rebuild_deep_conclude_designation_1(designation)
    Object designation;
{
    Object temp, original_expression_qm, role_qm, role, role_name;
    Object third_new_value;
    char temp_1;

    x_note_fn_call(211,11);
    if (SYMBOLP(designation)) {
	temp = assq_function(designation,Current_let_action_bindings);
	original_expression_qm = SECOND(temp);
	role_qm = (ATOM(original_expression_qm) ? original_expression_qm 
		&& SYMBOLP(original_expression_qm) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(original_expression_qm)))) 
		&& CONSP(original_expression_qm) && 
		IFIX(length(original_expression_qm)) >= (SI_Long)3L ? 
		simple_role_of_role(role_of_designation(original_expression_qm)) 
		: Qnil;
	if (role_qm) {
	    temp_1 = SYMBOLP(role_qm);
	    if (temp_1);
	    else {
		temp = role_name_of_role(role_qm);
		temp_1 = TRUEP(memq_function(temp,
			Deep_concludable_role_names));
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? 
		rebuild_deep_conclude_designation_1(original_expression_qm) 
		: designation;
    }
    else if (CONSP(designation) && IFIX(length(designation)) >= (SI_Long)3L) {
	role = simple_role_of_role(role_of_designation(designation));
	role_name = role_name_of_role(role);
	if (SYMBOLP(role) || memq_function(role_name,
		Deep_concludable_role_names)) {
	    third_new_value = 
		    rebuild_deep_conclude_designation_1(THIRD(designation));
	    M_THIRD(designation) = third_new_value;
	}
	temp = designation;
    }
    else
	temp = designation;
    return VALUES_1(temp);
}

static Object Qfalse;              /* false */

/* CONCLUDE-NOT-ACTION-COMPILER */
Object conclude_not_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object expiration_qm, collection_qm, old_value_qm, local_name_qm, temp;

    x_note_fn_call(211,12);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    expiration_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    collection_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    old_value_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    temp = compile_conclude_action(designation,Qfalse,expiration_qm,
	    collection_qm,old_value_qm,local_name_qm,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CONCLUDE-PROLOG-PSEUDO-EMITTER */
Object conclude_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, variable_or_parameter, datum, expiration_qm;
    Object collection_qm, var_spot_block_qm;

    x_note_fn_call(211,13);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    variable_or_parameter = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    datum = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    collection_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,variable_or_parameter);
    emit_stack_node_tree(byte_code_stream,datum);
    if (expiration_qm) {
	emit_stack_node_tree(byte_code_stream,expiration_qm);
	if (collection_qm)
	    emit_stack_node_tree(byte_code_stream,collection_qm);
	else
	    emit_push_constant_byte_codes(byte_code_stream,Nil);
    }
    else if (collection_qm) {
	emit_push_constant_byte_codes(byte_code_stream,Nil);
	emit_stack_node_tree(byte_code_stream,collection_qm);
    }
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)2L));
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPARE-AND-SWAP-PROLOG-PSEUDO-EMITTER */
Object compare_and_swap_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, variable_or_parameter, datum, old_value_qm;
    Object var_spot_block_qm;

    x_note_fn_call(211,14);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    variable_or_parameter = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    datum = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    old_value_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    emit_stack_node_tree(byte_code_stream,variable_or_parameter);
    emit_stack_node_tree(byte_code_stream,datum);
    if (old_value_qm)
	emit_stack_node_tree(byte_code_stream,old_value_qm);
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qconclude;           /* conclude */

/* CONCLUDE-EPILOG-PSEUDO-EMITTER */
Object conclude_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,15);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qconclude);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcompare_and_swap;   /* compare-and-swap */

/* COMPARE-AND-SWAP-EPILOG-PSEUDO-EMITTER */
Object compare_and_swap_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item_var_spot_qm, item_var_spot_type_to_check_qm;
    Object var_spot_block_qm;

    x_note_fn_call(211,16);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_type_to_check_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qcompare_and_swap);
    if (item_var_spot_qm) {
	if (item_var_spot_type_to_check_qm)
	    emit_type_check_byte_codes(byte_code_stream,
		    item_var_spot_type_to_check_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		item_var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CONCLUDE-ATTRIBUTE-PROLOG-PSEUDO-EMITTER */
Object conclude_attribute_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, class_qualifier_qm, attribute_name, item, value;
    Object var_spot_block_qm;

    x_note_fn_call(211,17);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    class_qualifier_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    attribute_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (class_qualifier_qm)
	emit_stack_node_tree(byte_code_stream,class_qualifier_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    emit_stack_node_tree(byte_code_stream,attribute_name);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,value);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qconclude_attribute;  /* conclude-attribute */

/* CONCLUDE-ATTRIBUTE-EPILOG-PSEUDO-EMITTER */
Object conclude_attribute_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,18);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		FOURTH(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qconclude_attribute);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* PRINT-MOVE-INSTRUCTION */
Object print_move_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, x_expression, y_expression;

    x_note_fn_call(211,19);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)5L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)4L));
    write_expression(x_expression);
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
    return write_expression(y_expression);
}

static Object Qmove_prolog;        /* move-prolog */

static Object Qmove_epilog;        /* move-epilog */

/* MOVE-ACTION-COMPILER */
Object move_action_compiler(statement,unknown_allowed_qm,leave_on_stack_qm,
	    prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object delta_x, delta_y, temp, temp_1, block_of_variables_qm;
    Object gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,20);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    delta_x = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    delta_y = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qnumber);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qnumber));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)27L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qmove_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(delta_x,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(delta_y,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)27L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qmove_epilog,block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* MOVE-PROLOG-PSEUDO-EMITTER */
Object move_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, delta_x, delta_y, var_spot_block_qm;

    x_note_fn_call(211,21);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    delta_x = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    delta_y = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,delta_x);
    emit_stack_node_tree(byte_code_stream,delta_y);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmove;               /* move */

/* MOVE-EPILOG-PSEUDO-EMITTER */
Object move_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,22);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmove);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

/* PRINT-SET-POSITION-INSTRUCTION */
Object print_set_position_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, x_expression, y_expression;

    x_note_fn_call(211,23);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)5L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    write_expression(x_expression);
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
    return write_expression(y_expression);
}

static Object Qset_position_prolog;  /* set-position-prolog */

static Object Qset_position_epilog;  /* set-position-epilog */

/* SET-POSITION-ACTION-COMPILER */
Object set_position_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object x_expression, y_expression, temp, temp_1, block_of_variables_qm;
    Object gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,24);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_expression = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_expression = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qnumber);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qnumber));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)27L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qset_position_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(x_expression,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(y_expression,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)27L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qset_position_epilog,block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* SET-POSITION-PROLOG-PSEUDO-EMITTER */
Object set_position_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, x_expression, y_expression;
    Object var_spot_block_qm;

    x_note_fn_call(211,25);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,x_expression);
    emit_stack_node_tree(byte_code_stream,y_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qset_position;       /* set-position */

/* SET-POSITION-EPILOG-PSEUDO-EMITTER */
Object set_position_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,26);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qset_position);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* PRINT-ROTATE-INSTRUCTION */
Object print_rotate_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, degree_of_rotation;

    x_note_fn_call(211,27);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    degree_of_rotation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)7L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)4L));
    write_expression(degree_of_rotation);
    return twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)8L));
}

static Object Qrotate_prolog;      /* rotate-prolog */

static Object Qrotate_epilog;      /* rotate-epilog */

/* ROTATE-ACTION-COMPILER */
Object rotate_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object degree, temp, block_of_variables_qm;

    x_note_fn_call(211,28);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    degree = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,Qnumber));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)28L),
	    unknown_allowed_qm));
    temp = compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qrotate_prolog,temp,
	    compile_stack_expression(degree,maybe_add_unknown(Qnumber,
	    unknown_allowed_qm)),block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)28L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qrotate_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* ROTATE-PROLOG-PSEUDO-EMITTER */
Object rotate_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, degree_expression, var_spot_block_qm;

    x_note_fn_call(211,29);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    degree_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,degree_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qrotate;             /* rotate */

/* ROTATE-EPILOG-PSEUDO-EMITTER */
Object rotate_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,30);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qrotate);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_14;   /* # */

/* PRINT-SET-HEADING-INSTRUCTION */
Object print_set_heading_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, degree_of_rotation;

    x_note_fn_call(211,31);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    degree_of_rotation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)7L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)16L));
    write_expression(degree_of_rotation);
    return twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)8L));
}

static Object Qset_heading_prolog;  /* set-heading-prolog */

static Object Qset_heading_epilog;  /* set-heading-epilog */

/* SET-HEADING-ACTION-COMPILER */
Object set_heading_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object degree, temp, block_of_variables_qm;

    x_note_fn_call(211,32);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    degree = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,Qnumber));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)28L),
	    unknown_allowed_qm));
    temp = compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qset_heading_prolog,temp,
	    compile_stack_expression(degree,maybe_add_unknown(Qnumber,
	    unknown_allowed_qm)),block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)28L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qset_heading_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* SET-HEADING-PROLOG-PSEUDO-EMITTER */
Object set_heading_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, degree_expression, var_spot_block_qm;

    x_note_fn_call(211,33);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    degree_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,degree_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qset_heading;        /* set-heading */

/* SET-HEADING-EPILOG-PSEUDO-EMITTER */
Object set_heading_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,34);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qset_heading);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* PRINT-CONCLUDE-HAS-NO-CURRENT-VALUE-INSTRUCTION */
Object print_conclude_has_no_current_value_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation;

    x_note_fn_call(211,35);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)14L));
    print_designation(designation);
    return twrite_beginning_of_wide_string(array_constant_16,
	    FIX((SI_Long)21L));
}

static Object Qconclude_has_no_current_value_prolog;  /* conclude-has-no-current-value-prolog */

static Object list_constant_8;     /* # */

static Object Qconclude_has_no_current_value_epilog;  /* conclude-has-no-current-value-epilog */

/* CONCLUDE-HAS-NO-CURRENT-VALUE-ACTION-COMPILER */
Object conclude_has_no_current_value_action_compiler(statement,
	    unknown_allowed_qm,leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,36);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)25L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qconclude_has_no_current_value_prolog,
	    compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_8,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)25L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qconclude_has_no_current_value_epilog,
	    block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CONCLUDE-HAS-NO-CURRENT-VALUE-PROLOG-PSEUDO-EMITTER */
Object conclude_has_no_current_value_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, variable, var_spot_block_qm;

    x_note_fn_call(211,37);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    variable = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,variable);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qconclude_has_no_current_value;  /* conclude-has-no-current-value */

/* CONCLUDE-HAS-NO-CURRENT-VALUE-EPILOG-PSEUDO-EMITTER */
Object conclude_has_no_current_value_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,38);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qconclude_has_no_current_value);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_17;   /* # */

/* PRINT-CONCLUDE-HAS-NO-VALUE-INSTRUCTION */
Object print_conclude_has_no_value_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation;

    x_note_fn_call(211,39);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)14L));
    print_designation(designation);
    return twrite_beginning_of_wide_string(array_constant_17,
	    FIX((SI_Long)13L));
}

static Object Qconclude_has_no_value_prolog;  /* conclude-has-no-value-prolog */

static Object list_constant_9;     /* # */

static Object Qconclude_has_no_value_epilog;  /* conclude-has-no-value-epilog */

/* CONCLUDE-HAS-NO-VALUE-ACTION-COMPILER */
Object conclude_has_no_value_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,40);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)26L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qconclude_has_no_value_prolog,
	    compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_9,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)26L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qconclude_has_no_value_epilog,
	    block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CONCLUDE-HAS-NO-VALUE-PROLOG-PSEUDO-EMITTER */
Object conclude_has_no_value_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, variable, var_spot_block_qm;

    x_note_fn_call(211,41);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    variable = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,variable);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qconclude_has_no_value;  /* conclude-has-no-value */

/* CONCLUDE-HAS-NO-VALUE-EPILOG-PSEUDO-EMITTER */
Object conclude_has_no_value_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,42);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qconclude_has_no_value);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

/* PRINT-FOCUS-INSTRUCTION */
Object print_focus_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, wait_qm;

    x_note_fn_call(211,43);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)9L));
    print_designation(designation);
    if (wait_qm)
	return twrite_beginning_of_wide_string(array_constant_19,
		FIX((SI_Long)21L));
    else
	return VALUES_1(Nil);
}

static Object Qfocus_prolog;       /* focus-prolog */

static Object Qfocus_epilog;       /* focus-epilog */

/* FOCUS-ACTION-COMPILER */
Object focus_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object wait_qm, block_of_variables_qm, temp;

    x_note_fn_call(211,44);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    wait_qm = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)29L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qfocus_prolog,
	    compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)29L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qfocus_epilog,block_of_variables_qm,wait_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* FOCUS-PROLOG-PSEUDO-EMITTER */
Object focus_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, designation, var_spot_block_qm;

    x_note_fn_call(211,45);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,designation);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qfocus_with_wait;    /* focus-with-wait */

static Object Qfocus;              /* focus */

/* FOCUS-EPILOG-PSEUDO-EMITTER */
Object focus_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, wait_qm;

    x_note_fn_call(211,46);
    var_spot_block_qm = SECOND(instruction);
    wait_qm = THIRD(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,wait_qm ? 
	    Qfocus_with_wait : Qfocus);
    if (wait_qm)
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)72L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

/* PRINT-INVOKE-INSTRUCTION */
Object print_invoke_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, query_restriction, entity_expression_qm, wait_qm;

    x_note_fn_call(211,47);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    query_restriction = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    entity_expression_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)7L));
    write_list_in_chicago_style(2,CDR(query_restriction),Qand);
    if (entity_expression_qm) {
	twrite_beginning_of_wide_string(array_constant_21,FIX((SI_Long)5L));
	print_designation(entity_expression_qm);
    }
    if (wait_qm)
	return twrite_beginning_of_wide_string(array_constant_19,
		FIX((SI_Long)21L));
    else
	return VALUES_1(Nil);
}

static Object Qinvoke_prolog;      /* invoke-prolog */

static Object Qinvoke_epilog;      /* invoke-epilog */

/* INVOKE-ACTION-COMPILER */
Object invoke_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object query_restriction, focal_entity_qm, wait_qm, temp;
    Object block_of_variables_qm;

    x_note_fn_call(211,48);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    query_restriction = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    focal_entity_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    wait_qm = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,Qinteger);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,list_constant_4));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)30L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qinvoke_prolog,query_restriction,focal_entity_qm 
	    ? compile_stack_expression(focal_entity_qm,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)) : Nil,
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)30L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_4(Qinvoke_epilog, ! !TRUEP(focal_entity_qm) ? T : 
	    Nil,block_of_variables_qm,wait_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* INVOKE-PROLOG-PSEUDO-EMITTER */
Object invoke_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, query_restriction, focal_entity_qm;
    Object var_spot_block_qm, index_1;

    x_note_fn_call(211,49);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    query_restriction = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    focal_entity_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    index_1 = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    query_restriction);
    emit_push_constant_byte_codes(byte_code_stream,index_1);
    if (focal_entity_qm)
	emit_stack_node_tree(byte_code_stream,focal_entity_qm);
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qinvoke_with_wait;   /* invoke-with-wait */

static Object Qinvoke;             /* invoke */

/* INVOKE-EPILOG-PSEUDO-EMITTER */
Object invoke_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, entity_p_qm, var_spot_block_qm, wait_qm;

    x_note_fn_call(211,50);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    entity_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    wait_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	if (entity_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
    }
    write_byte_code_to_stream(byte_code_stream,
	    op_code_for_stack_instruction(wait_qm ? Qinvoke_with_wait : 
	    Qinvoke));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_22;   /* # */

static Object string_constant_2;   /* " ~(~a~) " */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object string_constant_3;   /* " ~(~a~)" */

/* PRINT-CHANGE-ITEM-COLOR-INSTRUCTION */
Object print_change_item_color_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, color_expression, region_expression;

    x_note_fn_call(211,51);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    color_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    region_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)11L));
    if (CONSP(region_expression) && EQ(CAR(region_expression),Qquote))
	tformat(2,string_constant_2,SECOND(region_expression));
    else {
	twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)21L));
	write_expression(region_expression);
    }
    twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)4L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    if (CONSP(color_expression) && EQ(CAR(color_expression),Qquote))
	return tformat(2,string_constant_3,SECOND(color_expression));
    else
	return write_expression(color_expression);
}

static Object Qchange_item_color_prolog;  /* change-item-color-prolog */

static Object Qchange_item_color_epilog;  /* change-item-color-epilog */

/* CHANGE-ITEM-COLOR-ACTION-COMPILER */
Object change_item_color_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item, color;
    Object region, temp, temp_1, block_of_variables_qm, gensymed_symbol_3;
    Object car_new_value;

    x_note_fn_call(211,52);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    color = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    region = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qsymbol);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qsymbol));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)31L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qchange_item_color_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(color,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(region,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)31L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qchange_item_color_epilog,block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* CHANGE-ITEM-COLOR-PROLOG-PSEUDO-EMITTER */
Object change_item_color_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, color_expression, region_expression;
    Object var_spot_block_qm;

    x_note_fn_call(211,53);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    color_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    region_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,color_expression);
    emit_stack_node_tree(byte_code_stream,region_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qchange_item_color;  /* change-item-color */

/* CHANGE-ITEM-COLOR-EPILOG-PSEUDO-EMITTER */
Object change_item_color_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,54);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qchange_item_color);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_25;   /* # */

static Object string_constant_4;   /* "~%    " */

static Object array_constant_26;   /* # */

/* PRINT-CHANGE-ITEM-COLOR-PATTERN-INSTRUCTION */
Object print_change_item_color_pattern_instruction(instruction)
    Object instruction;
{
    Object designation, color_pattern, pattern, ab_loop_list_;

    x_note_fn_call(211,55);
    designation = SECOND(instruction);
    color_pattern = CDDR(instruction);
    twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)28L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    pattern = Nil;
    ab_loop_list_ = color_pattern;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pattern = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(1,string_constant_4);
    write_expression(FIRST(pattern));
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)3L));
    write_expression(CDR(pattern));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qchange_item_color_pattern_prolog;  /* change-item-color-pattern-prolog */

static Object Qchange_item_color_pattern_epilog;  /* change-item-color-pattern-epilog */

/* CHANGE-ITEM-COLOR-PATTERN-ACTION-COMPILER */
Object change_item_color_pattern_action_compiler(statement,
	    unknown_allowed_qm,leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object color_pattern, temp, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp_1, block_of_variables_qm, region_expression, color_expression;
    Object ab_loop_list_, ab_loop_desetq_;
    SI_Long color_pattern_count, ab_loop_repeat_;

    x_note_fn_call(211,56);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    color_pattern = CDR(gensymed_symbol_2);
    color_pattern_count = IFIX(length(color_pattern)) * (SI_Long)2L;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil);
	ab_loop_repeat_ = color_pattern_count;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,Qsymbol),Nil);
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
	block_of_variables_qm = nconc2(temp,temp_1);
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)31L),
	    unknown_allowed_qm));
    temp_1 = compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    region_expression = Nil;
    color_expression = Nil;
    ab_loop_list_ = color_pattern;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region_expression = CAR(ab_loop_desetq_);
    color_expression = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = compile_stack_expression(region_expression,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm));
    ab_loopvar__2 = phrase_cons(phrase_cons(temp,
	    compile_stack_expression(color_expression,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm))),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qchange_item_color_pattern_prolog,temp_1,temp,
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)31L)));
    temp_1 = block_of_variables_qm;
    if (temp_1);
    else
	temp_1 = FIX(color_pattern_count + (SI_Long)1L);
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qchange_item_color_pattern_epilog,temp_1));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* CHANGE-ITEM-COLOR-PATTERN-PROLOG-PSEUDO-EMITTER */
Object change_item_color_pattern_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, color_pattern, var_spot_block_qm, region;
    Object color, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(211,57);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    color_pattern = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    region = Nil;
    color = Nil;
    ab_loop_list_ = color_pattern;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region = CAR(ab_loop_desetq_);
    color = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,region);
    emit_stack_node_tree(byte_code_stream,color);
    goto next_loop;
  end_loop:;
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qchange_item_color_pattern;  /* change-item-color-pattern */

/* CHANGE-ITEM-COLOR-PATTERN-EPILOG-PSEUDO-EMITTER */
Object change_item_color_pattern_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,58);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm &&  !FIXNUMP(var_spot_block_qm)) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(4,byte_code_stream,
	    Qchange_item_color_pattern,FIXNUMP(var_spot_block_qm) ? 
	    var_spot_block_qm : length(var_spot_block_qm),FIX((SI_Long)0L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_27;   /* # */

static Object Qscale;              /* scale */

static Object array_constant_28;   /* # */

static Object array_constant_29;   /* # */

static Object Qworkspace_position;  /* workspace-position */

static Object array_constant_30;   /* # */

static Object array_constant_31;   /* # */

static Object array_constant_32;   /* # */

static Object Qscreen_position;    /* screen-position */

static Object Qin;                 /* in */

static Object array_constant_33;   /* # */

/* PRINT-SHOW-INSTRUCTION */
Object print_show_instruction(instruction)
    Object instruction;
{
    Object designation, show_detail_list, show_detail, temp;

    x_note_fn_call(211,59);
    designation = SECOND(instruction);
    show_detail_list = CDDR(instruction);
    twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)5L));
    print_designation(designation);
    show_detail = FIRST(show_detail_list);
  next_loop:
    if ( !TRUEP(show_detail_list))
	goto end_loop;
    show_detail_list = CDR(show_detail_list);
    temp = CAR(show_detail);
    if (EQ(temp,Qscale)) {
	twrite_beginning_of_wide_string(array_constant_28,FIX((SI_Long)4L));
	twrite(SECOND(show_detail));
	twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)6L));
    }
    else if (EQ(temp,Qworkspace_position)) {
	twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)10L));
	twrite_reference_point_details(CDR(show_detail));
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
	temp = FIRST(show_detail_list);
	twrite_reference_point_details(CDR(temp));
	twrite_beginning_of_wide_string(array_constant_32,FIX((SI_Long)14L));
	show_detail_list = CDR(show_detail_list);
    }
    else if (EQ(temp,Qscreen_position)) {
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
	twrite_reference_point_details(CDR(show_detail));
	twrite_beginning_of_wide_string(array_constant_32,FIX((SI_Long)14L));
    }
    else if (EQ(temp,Qin)) {
	twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)4L));
	print_designation(SECOND(show_detail));
    }
    show_detail = FIRST(show_detail_list);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_34;   /* # */

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object array_constant_35;   /* # */

static Object array_constant_36;   /* # */

static Object Qab_at;              /* at */

static Object array_constant_37;   /* # */

/* TWRITE-REFERENCE-POINT-DETAILS */
Object twrite_reference_point_details(reference_point_detail_list)
    Object reference_point_detail_list;
{
    Object reference_point_details, first_reference_point_qm, element_1;
    Object element_2;

    x_note_fn_call(211,60);
    reference_point_details = reference_point_detail_list;
    first_reference_point_qm = T;
  next_loop:
    if ( !TRUEP(reference_point_details))
	goto end_loop;
    element_1 = FIRST(reference_point_details);
    element_2 = SECOND(reference_point_details);
    if (first_reference_point_qm)
	first_reference_point_qm = Nil;
    else
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
    if (CONSP(element_1)) {
	twrite_reference_point_details(element_1);
	reference_point_details = CDR(reference_point_details);
    }
    else if (NUMBERP(element_2)) {
	twrite(element_2);
	twrite_beginning_of_wide_string(array_constant_34,FIX((SI_Long)7L));
	twrite(element_1);
	if (EQ(element_1,Qleft) || EQ(element_1,Qright))
	    twrite_beginning_of_wide_string(array_constant_24,
		    FIX((SI_Long)4L));
	if (CDDR(reference_point_details))
	    twrite_beginning_of_wide_string(array_constant_35,
		    FIX((SI_Long)3L));
	else
	    twrite_beginning_of_wide_string(array_constant_36,
		    FIX((SI_Long)3L));
	reference_point_details = CDDR(reference_point_details);
    }
    else {
	twrite(element_1);
	if (EQ(element_1,Qab_at))
	    twrite_beginning_of_wide_string(array_constant_37,
		    FIX((SI_Long)4L));
	reference_point_details = CDR(reference_point_details);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qshow_prolog;        /* show-prolog */

static Object list_constant_10;    /* # */

static Object Qshow_epilog;        /* show-epilog */

/* SHOW-ACTION-COMPILER */
Object show_action_compiler(statement,unknown_allowed_qm,leave_on_stack_qm,
	    prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object show_details_qm, temp, window_designation_qm, temp_1;
    Object block_of_variables_qm, gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,61);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    show_details_qm = CDR(gensymed_symbol_2);
    if (EQ(CAAR(show_details_qm),Qin)) {
	temp = CAR(show_details_qm);
	window_designation_qm = SECOND(temp);
    }
    else
	window_designation_qm = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp_1 = generate_new_variable_spot(1,list_constant_4);
	temp = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_3(temp_1,temp,
		generate_new_variable_spot(1,Qinteger));
    }
    else
	block_of_variables_qm = Nil;
    if (window_designation_qm)
	show_details_qm = CDR(show_details_qm);
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)32L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qshow_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = window_designation_qm ? 
	    compile_stack_expression(window_designation_qm,
	    maybe_add_unknown(list_constant_10,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = show_details_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)32L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qshow_epilog, ! !TRUEP(window_designation_qm) ? 
	    T : Nil,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* SHOW-PROLOG-PSEUDO-EMITTER */
Object show_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, window_qm, show_details_qm;
    Object var_spot_block_qm, index_1;

    x_note_fn_call(211,62);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    show_details_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (window_qm)
	emit_stack_node_tree(byte_code_stream,window_qm);
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (show_details_qm) {
	index_1 = 
		register_internal_constant_in_byte_code_stream(byte_code_stream,
		show_details_qm);
	emit_push_constant_byte_codes(byte_code_stream,index_1);
    }
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SHOW-EPILOG-PSEUDO-EMITTER */
Object show_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, window_p_qm, var_spot_block_qm;

    x_note_fn_call(211,63);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    window_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	if (window_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm));
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)100L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRINT-SHOW-NEW-INSTRUCTION */
Object print_show_new_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,64);
    return print_show_instruction(instruction);
}

static Object Qboolean;            /* boolean */

static Object Qshow_new_prolog;    /* show-new-prolog */

static Object Qshow_new_epilog;    /* show-new-epilog */

/* SHOW-NEW-ACTION-COMPILER */
Object show_new_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object show_details_qm, preserving_layering_qm, temp;
    Object window_designation_qm, go_to_block_qm, gensymed_symbol_3;
    Object car_new_value, block_of_variables_qm, symbolic_x_scale_qm;
    Object symbolic_y_scale_qm, symbolic_x_in_workspace_qm;
    Object symbolic_y_in_workspace_qm, symbolic_x_in_window_qm;
    Object symbolic_y_in_window_qm, x_offset_units_qm;
    Object symbolic_x_offset_direction_qm, y_offset_units_qm;
    Object symbolic_y_offset_direction_qm, x_magnification_qm;
    Object y_magnification_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object x_in_window_qm, y_in_window_qm;

    x_note_fn_call(211,65);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    show_details_qm = CDR(gensymed_symbol_2);
    if (show_details_qm && EQ(M_CAR(show_details_qm),T)) {
	show_details_qm = CDR(show_details_qm);
	preserving_layering_qm = T;
    }
    else
	preserving_layering_qm = Nil;
    if (EQ(CAAR(show_details_qm),Qin)) {
	temp = CAR(show_details_qm);
	window_designation_qm = SECOND(temp);
    }
    else
	window_designation_qm = Nil;
    go_to_block_qm = preserving_layering_qm;
    if ( !TRUEP(leave_on_stack_qm)) {
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)19L));
	gensymed_symbol_3 = gensymed_symbol_2;
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qboolean);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	block_of_variables_qm = gensymed_symbol_2;
    }
    else
	block_of_variables_qm = Nil;
    if (window_designation_qm)
	show_details_qm = CDR(show_details_qm);
    gensymed_symbol_2 = decode_show_details_as_phrase_list(show_details_qm);
    symbolic_x_scale_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_y_scale_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_x_in_workspace_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_y_in_workspace_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_x_in_window_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_y_in_window_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_offset_units_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_x_offset_direction_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_offset_units_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    symbolic_y_offset_direction_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_magnification_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_magnification_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_in_workspace_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_in_workspace_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_in_window_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_in_window_qm = CAR(gensymed_symbol_2);
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)32L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)21L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qshow_new_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = window_designation_qm ? 
	    compile_stack_expression(window_designation_qm,
	    maybe_add_unknown(list_constant_10,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = go_to_block_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_x_scale_qm ? 
	    compile_stack_expression(symbolic_x_scale_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_y_scale_qm ? 
	    compile_stack_expression(symbolic_y_scale_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_x_in_workspace_qm ? 
	    compile_stack_expression(symbolic_x_in_workspace_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_y_in_workspace_qm ? 
	    compile_stack_expression(symbolic_y_in_workspace_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_x_in_window_qm ? 
	    compile_stack_expression(symbolic_x_in_window_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_y_in_window_qm ? 
	    compile_stack_expression(symbolic_y_in_window_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = x_offset_units_qm ? 
	    compile_stack_expression(x_offset_units_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_x_offset_direction_qm ? 
	    compile_stack_expression(symbolic_x_offset_direction_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = y_offset_units_qm ? 
	    compile_stack_expression(y_offset_units_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = symbolic_y_offset_direction_qm ? 
	    compile_stack_expression(symbolic_y_offset_direction_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = x_magnification_qm ? 
	    compile_stack_expression(x_magnification_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = y_magnification_qm ? 
	    compile_stack_expression(y_magnification_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = x_in_workspace_qm ? 
	    compile_stack_expression(x_in_workspace_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = y_in_workspace_qm ? 
	    compile_stack_expression(y_in_workspace_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = x_in_window_qm ? 
	    compile_stack_expression(x_in_window_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = y_in_window_qm ? 
	    compile_stack_expression(y_in_window_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)32L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qshow_new_epilog, ! 
	    !TRUEP(window_designation_qm) ? T : Nil,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qshow_new;           /* show-new */

/* SHOW-NEW-PSEUDO-EMITTER */
Object show_new_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, the_item, show_details_qm;

    x_note_fn_call(211,66);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    the_item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    show_details_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,the_item);
    emit_stack_node_tree(byte_code_stream,show_details_qm);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qshow_new);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SHOW-NEW-PROLOG-PSEUDO-EMITTER */
Object show_new_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, g2_window_qm, go_to_block_qm;
    Object symbolic_x_scale_qm, symbolic_y_scale_qm;
    Object symbolic_x_in_workspace_qm, symbolic_y_in_workspace_qm;
    Object symbolic_x_in_window_qm, symbolic_y_in_window_qm, x_offset_units_qm;
    Object symbolic_x_offset_direction_qm, y_offset_units_qm;
    Object symbolic_y_offset_direction_qm, x_magnification_qm;
    Object y_magnification_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object x_in_window_qm, y_in_window_qm, var_spot_block_qm;

    x_note_fn_call(211,67);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    go_to_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_x_scale_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_y_scale_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_x_in_workspace_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_y_in_workspace_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_x_in_window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_y_in_window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_offset_units_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_x_offset_direction_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_offset_units_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    symbolic_y_offset_direction_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_magnification_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_magnification_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_workspace_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_workspace_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (g2_window_qm)
	emit_stack_node_tree(byte_code_stream,g2_window_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    emit_push_constant_byte_codes(byte_code_stream,go_to_block_qm);
    if (symbolic_x_scale_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_x_scale_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_y_scale_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_y_scale_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_x_in_workspace_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_x_in_workspace_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_y_in_workspace_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_y_in_workspace_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_x_in_window_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_x_in_window_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_y_in_window_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_y_in_window_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (x_offset_units_qm)
	emit_stack_node_tree(byte_code_stream,x_offset_units_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_x_offset_direction_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_x_offset_direction_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (y_offset_units_qm)
	emit_stack_node_tree(byte_code_stream,y_offset_units_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (symbolic_y_offset_direction_qm)
	emit_stack_node_tree(byte_code_stream,symbolic_y_offset_direction_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (x_magnification_qm)
	emit_stack_node_tree(byte_code_stream,x_magnification_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (y_magnification_qm)
	emit_stack_node_tree(byte_code_stream,y_magnification_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (x_in_workspace_qm)
	emit_stack_node_tree(byte_code_stream,x_in_workspace_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (y_in_workspace_qm)
	emit_stack_node_tree(byte_code_stream,y_in_workspace_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (x_in_window_qm)
	emit_stack_node_tree(byte_code_stream,x_in_window_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (y_in_window_qm)
	emit_stack_node_tree(byte_code_stream,y_in_window_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SHOW-NEW-EPILOG-PSEUDO-EMITTER */
Object show_new_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, window_p_qm, var_spot_block_qm;

    x_note_fn_call(211,68);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    window_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	if (window_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm),length(CDDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qshow_new);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_38;   /* # */

/* PRINT-HIDE-INSTRUCTION */
Object print_hide_instruction(instruction)
    Object instruction;
{
    Object hide_details_qm, temp;

    x_note_fn_call(211,69);
    twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)5L));
    print_designation(SECOND(instruction));
    hide_details_qm = CDDR(instruction);
    if (EQ(CAAR(hide_details_qm),Qin)) {
	twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)4L));
	temp = CAR(hide_details_qm);
	return print_designation(SECOND(temp));
    }
    else
	return VALUES_1(Nil);
}

static Object Qhide_prolog;        /* hide-prolog */

static Object Qhide_epilog;        /* hide-epilog */

/* HIDE-ACTION-COMPILER */
Object hide_action_compiler(statement,unknown_allowed_qm,leave_on_stack_qm,
	    prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object hide_details_qm, temp, window_designation_qm, block_of_variables_qm;

    x_note_fn_call(211,70);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    hide_details_qm = CDR(gensymed_symbol_2);
    if (EQ(CAAR(hide_details_qm),Qin)) {
	temp = CAR(hide_details_qm);
	window_designation_qm = SECOND(temp);
    }
    else
	window_designation_qm = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,list_constant_4));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)33L),
	    unknown_allowed_qm));
    temp = compile_stack_expression(item,maybe_add_unknown(list_constant_4,
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qhide_prolog,temp,window_designation_qm ? 
	    compile_stack_expression(window_designation_qm,
	    maybe_add_unknown(list_constant_10,unknown_allowed_qm)) : Nil,
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)33L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qhide_epilog, ! !TRUEP(window_designation_qm) ? 
	    T : Nil,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* HIDE-PROLOG-PSEUDO-EMITTER */
Object hide_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, window_qm, var_spot_block_qm;

    x_note_fn_call(211,71);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    window_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (window_qm)
	emit_stack_node_tree(byte_code_stream,window_qm);
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qhide;               /* hide */

/* HIDE-EPILOG-PSEUDO-EMITTER */
Object hide_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, window_p_qm, var_spot_block_qm;

    x_note_fn_call(211,72);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    window_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	if (window_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qhide);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_39;   /* # */

/* PRINT-ACTIVATE-INSTRUCTION */
Object print_activate_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,73);
    twrite_beginning_of_wide_string(array_constant_39,FIX((SI_Long)29L));
    return print_designation(SECOND(instruction));
}

static Object Qactivate_prolog;    /* activate-prolog */

static Object Qactivate_epilog;    /* activate-epilog */

/* ACTIVATE-ACTION-COMPILER */
Object activate_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,74);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)34L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qactivate_prolog,compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)34L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qactivate_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* ACTIVATE-PROLOG-PSEUDO-EMITTER */
Object activate_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, var_spot_block_qm;

    x_note_fn_call(211,75);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (var_spot_block_qm)
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qactivate;           /* activate */

/* ACTIVATE-EPILOG-PSEUDO-EMITTER */
Object activate_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,76);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qactivate);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_40;   /* # */

/* PRINT-DEACTIVATE-INSTRUCTION */
Object print_deactivate_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,77);
    twrite_beginning_of_wide_string(array_constant_40,FIX((SI_Long)31L));
    return print_designation(SECOND(instruction));
}

static Object Qprocedure_flags;    /* procedure-flags */

static Object Qdeactivate_prolog;  /* deactivate-prolog */

static Object Qdeactivate_epilog;  /* deactivate-epilog */

/* DEACTIVATE-ACTION-COMPILER */
Object deactivate_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object block_of_variables_qm, sub_class_bit_vector, svref_arg_1;
    Object svref_new_value, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(211,78);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_4 = (SI_Long)1L;
	gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	temp = (SI_Long)0L < gensymed_symbol_3;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_can_invalidate_environment_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)35L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qdeactivate_prolog,compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)35L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qdeactivate_epilog,block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* DEACTIVATE-PROLOG-PSEUDO-EMITTER */
Object deactivate_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, var_spot_block_qm;

    x_note_fn_call(211,79);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (var_spot_block_qm)
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qdeactivate;         /* deactivate */

/* DEACTIVATE-EPILOG-PSEUDO-EMITTER */
Object deactivate_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,80);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qdeactivate);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcall_action;        /* call-action */

static Object Qg2_deactivate;      /* g2-deactivate */

static Object Qevaluated_structure;  /* evaluated-structure */

static Object Qdeactivate_subworkspace_only;  /* deactivate-subworkspace-only */

/* DECODE-DEACTIVATE-DETAILS-IN-PHRASE-RULE */
Object decode_deactivate_details_in_phrase_rule(statement)
    Object statement;
{
    Object gensymed_symbol, item;

    x_note_fn_call(211,81);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    return phrase_list_3(Qcall_action,Qg2_deactivate,phrase_list_2(item,
	    phrase_list_3(Qevaluated_structure,
	    phrase_quote_if_non_nil(Qdeactivate_subworkspace_only),Qtrue)));
}

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

static Object Qtext;               /* text */

static Object array_constant_43;   /* # */

/* PRINT-HALT-INSTRUCTION */
Object print_halt_instruction(instruction)
    Object instruction;
{
    Object text_message;

    x_note_fn_call(211,82);
    text_message = SECOND(instruction);
    twrite_beginning_of_wide_string(array_constant_41,FIX((SI_Long)4L));
    if (text_message) {
	twrite_beginning_of_wide_string(array_constant_42,FIX((SI_Long)6L));
	print_constant(2,text_message,Qtext);
    }
    return twrite_beginning_of_wide_string(array_constant_43,
	    FIX((SI_Long)27L));
}

static Object Qhalt_prolog;        /* halt-prolog */

static Object Qhalt_epilog;        /* halt-epilog */

/* HALT-ACTION-COMPILER */
Object halt_action_compiler(statement,unknown_allowed_qm,leave_on_stack_qm,
	    prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object text_message_qm, block_of_variables_qm, temp;

    x_note_fn_call(211,83);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    text_message_qm = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,Qtext),Nil) : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)36L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qhalt_prolog,text_message_qm ? 
	    compile_stack_expression(text_message_qm,
	    maybe_add_unknown(Qtext,unknown_allowed_qm)) : Nil,
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)36L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qhalt_epilog, ! !TRUEP(text_message_qm) ? T : 
	    Nil,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* HALT-PROLOG-PSEUDO-EMITTER */
Object halt_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, text_qm, var_spot_block_qm;

    x_note_fn_call(211,84);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    text_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (text_qm)
	emit_stack_node_tree(byte_code_stream,text_qm);
    else
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    if (var_spot_block_qm)
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* HALT-EPILOG-PSEUDO-EMITTER */
Object halt_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, text_p_qm, var_spot_block_qm;

    x_note_fn_call(211,85);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    text_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	if (text_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    FIRST(var_spot_block_qm));
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    FIRST(var_spot_block_qm));
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)99L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_44;   /* # */

/* PRINT-SET-INSTRUCTION */
Object print_set_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, place_designation, expression;

    x_note_fn_call(211,86);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    place_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_44,FIX((SI_Long)4L));
    print_designation(place_designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    return write_expression(expression);
}

static Object list_constant_11;    /* # */

static Object Qset_prolog;         /* set-prolog */

static Object Qset_epilog;         /* set-epilog */

/* SET-ACTION-COMPILER */
Object set_action_compiler(statement,unknown_allowed_qm,leave_on_stack_qm,
	    prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, place, datum;
    Object temp, block_of_variables_qm;

    x_note_fn_call(211,87);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    place = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    datum = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_11);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,Qdatum));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)37L),
	    unknown_allowed_qm));
    temp = compile_stack_expression(place,
	    maybe_add_unknown(list_constant_11,unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qset_prolog,temp,compile_stack_expression(datum,
	    maybe_add_unknown(Qdatum,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)37L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qset_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* SET-PROLOG-PSEUDO-EMITTER */
Object set_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, place, expression, var_spot_block_qm;

    x_note_fn_call(211,88);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    place = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,place);
    emit_stack_node_tree(byte_code_stream,expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SET-EPILOG-PSEUDO-EMITTER */
Object set_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,89);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qset);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qduration;           /* duration */

static Object Qon;                 /* on */

static Object list_constant_12;    /* # */

static Object Qabove;              /* above */

static Object Qbelow;              /* below */

/* COMPILE-PROCEDURE-INFORM-FEATURE */
Object compile_procedure_inform_feature(inform_option)
    Object inform_option;
{
    Object temp;

    x_note_fn_call(211,90);
    if ( !TRUEP(inform_option))
	return VALUES_1(Nil);
    else if (EQ(CAR(inform_option),Qduration)) {
	temp = CAR(inform_option);
	return phrase_list_2(temp,
		compile_stack_expression(SECOND(inform_option),Qinteger));
    }
    else if (EQ(CAR(inform_option),Qon)) {
	temp = CAR(inform_option);
	return phrase_list_2(temp,
		compile_stack_expression(SECOND(inform_option),
		list_constant_12));
    }
    else if (EQ(CAR(inform_option),Qabove)) {
	temp = CAR(inform_option);
	return phrase_list_2(temp,
		compile_stack_expression(SECOND(inform_option),
		list_constant_4));
    }
    else if (EQ(CAR(inform_option),Qbelow)) {
	temp = CAR(inform_option);
	return phrase_list_2(temp,
		compile_stack_expression(SECOND(inform_option),
		list_constant_4));
    }
    else
	return VALUES_1(inform_option);
}

static Object string_constant_5;   /* "Inform action" */

static Object string_constant_6;   /* "Unknown Inform option ~a." */

static Object string_constant_7;   /* "Missing Inform option." */

/* COMPILE-ACTION-INFORM-FEATURE */
Object compile_action_inform_feature(inform_option,unknown_allowed_qm)
    Object inform_option, unknown_allowed_qm;
{
    x_note_fn_call(211,91);
    if (EQ(CAR(inform_option),Qduration))
	return compile_stack_expression(SECOND(inform_option),
		maybe_add_unknown(Qinteger,unknown_allowed_qm));
    else if (EQ(CAR(inform_option),Qon))
	return compile_stack_expression(SECOND(inform_option),
		maybe_add_unknown(list_constant_12,unknown_allowed_qm));
    else if (EQ(CAR(inform_option),Qabove))
	return compile_stack_expression(SECOND(inform_option),
		maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    else if (EQ(CAR(inform_option),Qbelow))
	return compile_stack_expression(SECOND(inform_option),
		maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    else if (inform_option)
	return compiler_bug(3,string_constant_5,string_constant_6,
		inform_option);
    else
	return compiler_bug(2,string_constant_5,string_constant_7);
}

static Object array_constant_45;   /* # */

static Object array_constant_46;   /* # */

static Object array_constant_47;   /* # */

static Object array_constant_48;   /* # */

static Object Qseconds;            /* seconds */

static Object array_constant_49;   /* # */

static Object Qab_format;          /* format */

static Object Qfixed_format;       /* fixed-format */

/* PRINT-INFORM-INSTRUCTION */
Object print_inform_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, destinations, message_1, features, feature;
    Object ab_loop_list_, temp, message_component;

    x_note_fn_call(211,92);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    destinations = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    message_1 = CAR(gensymed_symbol);
    features = CDR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_45,FIX((SI_Long)7L));
    print_designation(destinations);
    feature = Nil;
    ab_loop_list_ = features;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    feature = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FIRST(feature);
    if (EQ(temp,Qon)) {
	twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)4L));
	print_designation(SECOND(feature));
    }
    else if (EQ(temp,Qabove)) {
	twrite_beginning_of_wide_string(array_constant_46,FIX((SI_Long)7L));
	print_designation(SECOND(feature));
    }
    else if (EQ(temp,Qbelow)) {
	twrite_beginning_of_wide_string(array_constant_47,FIX((SI_Long)7L));
	print_designation(SECOND(feature));
    }
    else if (EQ(temp,Qduration)) {
	twrite_beginning_of_wide_string(array_constant_48,FIX((SI_Long)14L));
	print_constant(2,SECOND(feature),Qseconds);
    }
    else
	twrite(feature);
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_49,FIX((SI_Long)6L));
    if (CONSP(message_1)) {
	message_component = Nil;
	ab_loop_list_ = CDR(message_1);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	message_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(message_component))
	    twrite_parsably(message_component);
	else if (CONSP(message_component)) {
	    temp = FIRST(message_component);
	    if (EQ(temp,Qab_format) || EQ(temp,Qfixed_format)) {
		temp = SECOND(message_component);
		if (EQ(FIRST(temp),Qthe))
		    print_designation(SECOND(message_component));
		else
		    twrite(SECOND(message_component));
	    }
	    else if (EQ(temp,Qthe))
		print_designation(message_component);
	    else
		write_expression(message_component);
	}
	else
	    twrite(message_component);
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return print_constant(2,message_1,Qtext);
}

static Object list_constant_13;    /* # */

static Object Qoperator;           /* operator */

static Object Qinform_prolog;      /* inform-prolog */

static Object Qformat_form;        /* format-form */

static Object Qfirst_that_has_a_value;  /* first-that-has-a-value */

static Object array_constant_50;   /* # */

static Object list_constant_14;    /* # */

static Object Qmessage_board;      /* message-board */

static Object Qinform_epilog;      /* inform-epilog */

/* INFORM-ACTION-COMPILER */
Object inform_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object destination_or_operator, message_1, inform_options;
    Object gensymed_symbol_3, car_new_value, block_of_variables_qm;
    Object destination_qm, duration_p_qm, on_p_qm, above_p_qm, below_p_qm;
    Object option, ab_loop_list_, temp;
    char car_new_value_1;

    x_note_fn_call(211,93);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    destination_or_operator = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    message_1 = CAR(gensymed_symbol_2);
    inform_options = CDR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_3 = gensymed_symbol_2;
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qtext);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,Qnumber);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,list_constant_12);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_3) = car_new_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_3) = car_new_value;
	block_of_variables_qm = gensymed_symbol_2;
    }
    else
	block_of_variables_qm = Nil;
    destination_qm =  !EQUAL(destination_or_operator,list_constant_13) &&  
	    !EQ(destination_or_operator,Qoperator) ? 
	    destination_or_operator : Qnil;
    duration_p_qm = Nil;
    on_p_qm = Nil;
    above_p_qm = Nil;
    below_p_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)38L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)8L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qinform_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = destination_qm ? 
	    compile_stack_expression(destination_qm,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    if (CONSP(message_1) && EQ(CAR(message_1),Qand)) {
	M_CAR(message_1) = Qformat_form;
	car_new_value = unknown_allowed_qm ? 
		compile_stack_expression(phrase_list_3(Qfirst_that_has_a_value,
		message_1,array_constant_50),list_constant_14) : 
		compile_stack_expression(message_1,Qtext);
    }
    else
	car_new_value = compile_stack_expression(message_1,
		maybe_add_unknown(Qtext,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    option = Nil;
    ab_loop_list_ = inform_options;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    option = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(CAR(option),Qduration)) {
	duration_p_qm = T;
	car_new_value = compile_action_inform_feature(option,
		unknown_allowed_qm);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    car_new_value = Qnil;
  end_1:;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    option = Nil;
    ab_loop_list_ = inform_options;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    option = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(CAR(option),Qon) &&  !EQ(CADR(option),Qmessage_board)) {
	on_p_qm = T;
	car_new_value = compile_action_inform_feature(option,
		unknown_allowed_qm);
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
    car_new_value = Qnil;
  end_2:;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    option = Nil;
    ab_loop_list_ = inform_options;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    option = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(CAR(option),Qabove)) {
	above_p_qm = T;
	car_new_value = compile_action_inform_feature(option,
		unknown_allowed_qm);
	goto end_3;
    }
    goto next_loop_2;
  end_loop_2:
    car_new_value = Qnil;
  end_3:;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    option = Nil;
    ab_loop_list_ = inform_options;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    option = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(CAR(option),Qbelow)) {
	below_p_qm = T;
	car_new_value = compile_action_inform_feature(option,
		unknown_allowed_qm);
	goto end_4;
    }
    goto next_loop_3;
  end_loop_3:
    car_new_value = Qnil;
  end_4:;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)38L)));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qinform_epilog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value_1 =  ! !TRUEP(destination_qm);
    M_CAR(gensymed_symbol_3) = car_new_value_1 ? T : Nil;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = duration_p_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = on_p_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = above_p_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = below_p_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(epilog_stream,gensymed_symbol_2);
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* INFORM-PROLOG-PSEUDO-EMITTER */
Object inform_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, destination, message_1, duration_qm, on_qm;
    Object above_qm, below_qm, var_spot_block_qm, nil_arg_count;

    x_note_fn_call(211,94);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    destination = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    message_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    duration_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    on_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    above_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    below_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    nil_arg_count = FIX((SI_Long)0L);
    if ( !TRUEP(destination))
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    else
	emit_stack_node_tree(byte_code_stream,destination);
    emit_stack_node_tree(byte_code_stream,message_1);
    if (duration_qm)
	emit_stack_node_tree(byte_code_stream,duration_qm);
    else
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
    if (on_qm) {
	if (IFIX(nil_arg_count) > (SI_Long)0L) {
	    emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
	    nil_arg_count = FIX((SI_Long)0L);
	}
	emit_stack_node_tree(byte_code_stream,on_qm);
    }
    else
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
    if (above_qm) {
	if (IFIX(nil_arg_count) > (SI_Long)0L) {
	    emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
	    nil_arg_count = FIX((SI_Long)0L);
	}
	emit_stack_node_tree(byte_code_stream,above_qm);
    }
    else
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
    if (below_qm) {
	if (IFIX(nil_arg_count) > (SI_Long)0L) {
	    emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
	    nil_arg_count = FIX((SI_Long)0L);
	}
	emit_stack_node_tree(byte_code_stream,below_qm);
    }
    else {
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
	emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
    }
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qinform;             /* inform */

/* INFORM-EPILOG-PSEUDO-EMITTER */
Object inform_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, destination_p_qm, duration_p_qm, on_p_qm;
    Object above_p_qm, below_p_qm, var_spot_block_qm, destination, message_1;
    Object duration, on, above, below;

    x_note_fn_call(211,95);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    destination_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    duration_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    on_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    above_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    below_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	destination = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	message_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	duration = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	on = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	above = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	below = CAR(gensymed_symbol);
	if (destination_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    destination);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    destination);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		message_1);
	if (duration_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    duration);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    duration);
	if (on_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    on);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    on);
	if (above_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    above);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    above);
	if (below_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    below);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    below);
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qinform);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* " IS ~a " */

/* PRINT-ADD-RELATION */
Object print_add_relation(instruction)
    Object instruction;
{
    Object gensymed_symbol, relation_name, designation_1, designation_2;

    x_note_fn_call(211,96);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    relation_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    designation_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    designation_2 = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)14L));
    print_designation(designation_1);
    tformat(2,string_constant_8,relation_name);
    return print_designation(designation_2);
}

static Object Qadd_relation_prolog;  /* add-relation-prolog */

static Object Qadd_relation_epilog;  /* add-relation-epilog */

/* ADD-RELATION-ACTION-COMPILER */
Object add_relation_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object relation_name, item1, item2, now_case_qm, temp, temp_1, temp_2;
    Object block_of_variables_qm, gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,97);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    relation_name = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item2 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    now_case_qm = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,Qsymbol);
	temp_1 = generate_new_variable_spot(1,list_constant_4);
	temp_2 = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_4(temp,temp_1,temp_2,
		generate_new_variable_spot(1,Qtruth_value));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)39L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qadd_relation_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = relation_name;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item1,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item2,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(now_case_qm ? Qtrue : Qfalse,
	    Qtruth_value);
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)39L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qadd_relation_epilog,block_of_variables_qm));
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

/* ADD-RELATION-PROLOG-PSEUDO-EMITTER */
Object add_relation_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, relation_name, item_1, item_2, now_case_expression;
    Object var_spot_block_qm;

    x_note_fn_call(211,98);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    relation_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_2 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    now_case_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_push_constant_byte_codes(byte_code_stream,relation_name);
    emit_stack_node_tree(byte_code_stream,item_1);
    emit_stack_node_tree(byte_code_stream,item_2);
    emit_stack_node_tree(byte_code_stream,now_case_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qadd_relation;       /* add-relation */

/* ADD-RELATION-EPILOG-PSEUDO-EMITTER */
Object add_relation_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, gensymed_symbol, relation_name, item_1, item_2;
    Object now_case_qm;

    x_note_fn_call(211,99);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	relation_name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	item_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	item_2 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	now_case_qm = CAR(gensymed_symbol);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		relation_name);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		item_1);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		item_2);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		now_case_qm);
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qadd_relation);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qremove_relation_prolog;  /* remove-relation-prolog */

static Object Qremove_relation_epilog;  /* remove-relation-epilog */

/* REMOVE-RELATION-ACTION-COMPILER */
Object remove_relation_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object relation_name, item1, item2, temp, temp_1, block_of_variables_qm;
    Object gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,100);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    relation_name = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item2 = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,Qsymbol);
	temp_1 = generate_new_variable_spot(1,list_constant_4);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,list_constant_4));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)40L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qremove_relation_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = relation_name;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item1,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item2,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)40L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qremove_relation_epilog,block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* REMOVE-RELATION-PROLOG-PSEUDO-EMITTER */
Object remove_relation_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, relation_name, item_1, item_2, var_spot_block_qm;

    x_note_fn_call(211,101);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    relation_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_2 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_push_constant_byte_codes(byte_code_stream,relation_name);
    emit_stack_node_tree(byte_code_stream,item_1);
    emit_stack_node_tree(byte_code_stream,item_2);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qremove_relation;    /* remove-relation */

/* REMOVE-RELATION-EPILOG-PSEUDO-EMITTER */
Object remove_relation_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,102);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qremove_relation);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_51;   /* # */

static Object array_constant_52;   /* # */

/* PRINT-CREATE-INSTRUCTION */
Object print_create_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, class_expression, local_name_qm;

    x_note_fn_call(211,103);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    class_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_51,FIX((SI_Long)19L));
    if (local_name_qm) {
	print_designation(local_name_qm);
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
    }
    twrite_beginning_of_wide_string(array_constant_52,FIX((SI_Long)22L));
    return write_expression(class_expression);
}

static Object string_constant_9;   /* "In the create action, the local name ~a is declared to ~
				    *                        hold ~NT, not ~NT."
				    */

static Object Qcreate_prolog;      /* create-prolog */

static Object Qcreate_epilog;      /* create-epilog */

/* CREATE-ACTION-COMPILER */
Object create_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object class_expression, local_name_qm, var_spot_qm;
    Object var_spot_description_qm, var_spot_type_qm, compiler_error_qm;
    Object created_type, check_created_type_qm, block_of_variables_qm, temp;
    Object result;

    x_note_fn_call(211,104);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    class_expression = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    var_spot_qm = Nil;
    var_spot_description_qm = Nil;
    var_spot_type_qm = Nil;
    compiler_error_qm = Nil;
    created_type = make_class_type_specification(CONSP(class_expression) 
	    && EQ(CAR(class_expression),Qquote) ? SECOND(class_expression) 
	    : Qitem);
    check_created_type_qm = Nil;
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,Qsymbol),Nil) : Nil;
    if (local_name_qm) {
	result = variable_spot_and_description_for_local_name(local_name_qm);
	MVS_2(result,var_spot_qm,var_spot_description_qm);
	if ( !TRUEP(var_spot_qm)) {
	    compiler_error_qm = T;
	    procedure_compiler_missing_local_name_error(local_name_qm);
	}
	else {
	    var_spot_type_qm = 
		    getfq_function_no_default(CDR(var_spot_description_qm),
		    Ktype);
	    if ( !TRUEP(type_specification_subtype_p(created_type,
		    var_spot_type_qm))) {
		if (type_specifications_could_intersect_p(created_type,
			var_spot_type_qm))
		    check_created_type_qm = var_spot_type_qm;
		else
		    compiler_error(4,string_constant_9,local_name_qm,
			    var_spot_type_qm,created_type);
	    }
	}
    }
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)41L),
	    unknown_allowed_qm));
    if ( !TRUEP(compiler_error_qm)) {
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qcreate_prolog,
		compile_stack_expression(class_expression,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm)),
		block_of_variables_qm));
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)41L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_4(Qcreate_epilog,var_spot_qm,
		check_created_type_qm,block_of_variables_qm));
    }
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CREATE-PROLOG-PSEUDO-EMITTER */
Object create_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, symbol_expression, var_spot_block_qm;

    x_note_fn_call(211,105);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    symbol_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,symbol_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcreate;             /* create */

/* CREATE-EPILOG-PSEUDO-EMITTER */
Object create_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item_var_spot_qm, item_var_spot_type_to_check_qm;
    Object var_spot_block_qm;

    x_note_fn_call(211,106);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_type_to_check_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm)
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qcreate);
    if (item_var_spot_qm) {
	if (item_var_spot_type_to_check_qm)
	    emit_type_check_byte_codes(byte_code_stream,
		    item_var_spot_type_to_check_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		item_var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CREATE-PSEUDO-EMITTER */
Object create_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, the_class, item_var_spot_qm;
    Object item_var_spot_type_to_check_qm;

    x_note_fn_call(211,107);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    the_class = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_type_to_check_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,the_class);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qcreate);
    if (item_var_spot_qm) {
	if (item_var_spot_type_to_check_qm)
	    emit_type_check_byte_codes(byte_code_stream,
		    item_var_spot_type_to_check_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		item_var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_53;   /* # */

/* PRINT-DELETE-INSTRUCTION */
Object print_delete_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,108);
    twrite_beginning_of_wide_string(array_constant_53,FIX((SI_Long)7L));
    return print_designation(SECOND(instruction));
}

static Object Qdelete_prolog;      /* delete-prolog */

static Object Qwithout_permanence_checks_without_leaving_stubs;  /* without-permanence-checks-without-leaving-stubs */

static Object Qwithout_permanence_checks;  /* without-permanence-checks */

static Object Qdelete_epilog;      /* delete-epilog */

/* DELETE-ACTION-COMPILER */
Object delete_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object delete_connections_without_leaving_stubs_qm;
    Object without_permanence_checks_qm, temp, block_of_variables_qm;
    Object sub_class_bit_vector, svref_arg_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(211,109);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    delete_connections_without_leaving_stubs_qm = CAR(gensymed_symbol_2);
    PUSH_SPECIAL_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm,Qdelete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
	    0);
      gensymed_symbol_2 = CDR(gensymed_symbol_2);
      without_permanence_checks_qm = CAR(gensymed_symbol_2);
      if ( !TRUEP(leave_on_stack_qm)) {
	  temp = generate_new_variable_spot(1,list_constant_4);
	  block_of_variables_qm = phrase_list_2(temp,
		  generate_new_variable_spot(1,Qdatum));
      }
      else
	  block_of_variables_qm = Nil;
      sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	      (SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	      (SI_Long)18L));
      sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
      if (sub_class_vector_index < 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	  gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		  sub_class_vector_index);
	  gensymed_symbol_4 = (SI_Long)1L;
	  gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	  gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	  gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	  temp_1 = (SI_Long)0L < gensymed_symbol_3;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Current_computation_frame,
		      Qprocedure_flags);
	  svref_arg_1 = Current_computation_frame;
	  svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		  (SI_Long)29L),Procedure_can_invalidate_environment_mask);
	  SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
      }
      emit_already_consed_instruction_to_stream(prolog_stream,
	      phrase_list_3(Qbegin_activity,FIX((SI_Long)42L),
	      unknown_allowed_qm));
      temp = compile_stack_expression(item,
	      maybe_add_unknown(list_constant_4,unknown_allowed_qm));
      emit_already_consed_instruction_to_stream(prolog_stream,
	      phrase_list_4(Qdelete_prolog,temp,
	      without_permanence_checks_qm ? 
	      (Delete_connections_without_leaving_stubs_qm ? 
	      Qwithout_permanence_checks_without_leaving_stubs : 
	      Qwithout_permanence_checks) : 
	      Delete_connections_without_leaving_stubs_qm,
	      block_of_variables_qm));
      if (unknown_allowed_qm)
	  emit_already_consed_instruction_to_stream(epilog_stream,
		  phrase_list_2(Qbegin_activity,FIX((SI_Long)42L)));
      emit_already_consed_instruction_to_stream(epilog_stream,
	      phrase_list_2(Qdelete_epilog,block_of_variables_qm));
      temp = block_of_variables_qm;
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* DELETE-PROLOG-PSEUDO-EMITTER */
Object delete_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, delete_connections_without_leaving_stubs_qm;
    Object var_spot_block_qm;
    Declare_special(1);

    x_note_fn_call(211,110);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    delete_connections_without_leaving_stubs_qm = CAR(gensymed_symbol);
    PUSH_SPECIAL_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm,Qdelete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
	    0);
      gensymed_symbol = CDR(gensymed_symbol);
      var_spot_block_qm = CAR(gensymed_symbol);
      emit_stack_node_tree(byte_code_stream,item);
      emit_push_constant_byte_codes(byte_code_stream,
	      Delete_connections_without_leaving_stubs_qm);
      if (var_spot_block_qm)
	  emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		  FIRST(var_spot_block_qm),length(var_spot_block_qm));
    POP_SPECIAL();
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* DELETE-EPILOG-PSEUDO-EMITTER */
Object delete_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_block_qm;

    x_note_fn_call(211,111);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qdelete);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_54;   /* # */

static Object array_constant_55;   /* # */

static Object array_constant_56;   /* # */

static Object array_constant_57;   /* # */

/* PRINT-TRANSFER-INSTRUCTION */
Object print_transfer_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, object_designation, workspace_designation_qm;
    Object x_expression_qm, y_expression_qm;

    x_note_fn_call(211,112);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    object_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    workspace_designation_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_expression_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_expression_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_54,FIX((SI_Long)9L));
    print_designation(object_designation);
    if (workspace_designation_qm) {
	twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
	print_designation(workspace_designation_qm);
	if (x_expression_qm) {
	    twrite_beginning_of_wide_string(array_constant_55,
		    FIX((SI_Long)5L));
	    write_expression(x_expression_qm);
	    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
	    write_expression(y_expression_qm);
	    return twrite_beginning_of_wide_string(array_constant_56,
		    FIX((SI_Long)1L));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_57,
		FIX((SI_Long)4L));
}

static Object Qmouse;              /* mouse */

static Object list_constant_15;    /* # */

static Object Qtransfer_prolog;    /* transfer-prolog */

static Object Qtransfer_epilog;    /* transfer-epilog */

/* TRANSFER-ACTION-COMPILER */
Object transfer_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object transient_item, workspace_or_designation_qm, x_qm, y_qm;
    Object transfer_item_to_mouse_qm, type_of_destination;
    Object block_of_variables_qm, role, temp, temp_1, temp_2;
    Object sub_class_bit_vector, temp_4, svref_new_value, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3, car_new_value;

    x_note_fn_call(211,113);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    transient_item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    workspace_or_designation_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    x_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    y_qm = CAR(gensymed_symbol_2);
    transfer_item_to_mouse_qm = CONSP(workspace_or_designation_qm) && 
	    EQ(FIRST(workspace_or_designation_qm),Qthe) && 
	    EQ(SECOND(workspace_or_designation_qm),Qmouse) ? ( ! 
	    !TRUEP(THIRD(workspace_or_designation_qm)) ? T : Nil) : Qnil;
    type_of_destination = Nil;
    block_of_variables_qm = Nil;
    if (CONSP(workspace_or_designation_qm) && 
	    IFIX(length(workspace_or_designation_qm)) == (SI_Long)3L)
	role = SECOND(workspace_or_designation_qm);
    type_of_destination = transfer_item_to_mouse_qm ? list_constant_15 : 
	    list_constant_7;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,type_of_destination);
	temp_2 = generate_new_variable_spot(1,Qnumber);
	block_of_variables_qm = phrase_list_4(temp,temp_1,temp_2,
		generate_new_variable_spot(1,Qnumber));
    }
    else
	block_of_variables_qm = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_4 = (SI_Long)1L;
	gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	temp_3 = (SI_Long)0L < gensymed_symbol_3;
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	temp_4 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_can_invalidate_environment_mask);
	SVREF(temp_4,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)43L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_6 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_6) = Qtransfer_prolog;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_4 = compile_stack_expression(transient_item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_6) = temp_4;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    if ( !TRUEP(workspace_or_designation_qm))
	temp_4 = Nil;
    else if (transfer_item_to_mouse_qm)
	temp_4 = 
		compile_stack_expression(THIRD(workspace_or_designation_qm),
		maybe_add_unknown(type_of_destination,unknown_allowed_qm));
    else
	temp_4 = compile_stack_expression(workspace_or_designation_qm,
		maybe_add_unknown(type_of_destination,unknown_allowed_qm));
    M_CAR(gensymed_symbol_6) = temp_4;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_4 = x_qm ? compile_stack_expression(x_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_6) = temp_4;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_4 = y_qm ? compile_stack_expression(y_qm,
	    maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_6) = temp_4;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)43L)));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_6 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_6) = Qtransfer_epilog;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    car_new_value =  ! !TRUEP(workspace_or_designation_qm);
    M_CAR(gensymed_symbol_6) = car_new_value ? T : Nil;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    car_new_value =  ! !TRUEP(x_qm);
    M_CAR(gensymed_symbol_6) = car_new_value ? T : Nil;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    car_new_value =  ! !TRUEP(y_qm);
    M_CAR(gensymed_symbol_6) = car_new_value ? T : Nil;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(epilog_stream,gensymed_symbol_2);
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

/* TRANSFER-PROLOG-PSEUDO-EMITTER */
Object transfer_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, workspace_qm, x_qm, y_qm, var_spot_block_qm;
    Object nil_arg_count;

    x_note_fn_call(211,114);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    workspace_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    nil_arg_count = FIX((SI_Long)0L);
    emit_stack_node_tree(byte_code_stream,item);
    if (workspace_qm)
	emit_stack_node_tree(byte_code_stream,workspace_qm);
    else
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
    if (x_qm) {
	if (IFIX(nil_arg_count) > (SI_Long)0L) {
	    emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
	    nil_arg_count = FIX((SI_Long)0L);
	}
	emit_stack_node_tree(byte_code_stream,x_qm);
    }
    else
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
    if (y_qm) {
	if (IFIX(nil_arg_count) > (SI_Long)0L) {
	    emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
	    nil_arg_count = FIX((SI_Long)0L);
	}
	emit_stack_node_tree(byte_code_stream,y_qm);
    }
    else {
	nil_arg_count = FIXNUM_ADD1(nil_arg_count);
	emit_push_nones_byte_codes(byte_code_stream,nil_arg_count);
    }
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qtransfer;           /* transfer */

/* TRANSFER-EPILOG-PSEUDO-EMITTER */
Object transfer_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, workspace_p_qm, x_p_qm, y_p_qm, var_spot_block_qm;
    Object item, workspace, x, y;

    x_note_fn_call(211,115);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    workspace_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	item = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	workspace = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	x = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	y = CAR(gensymed_symbol);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,item);
	if (workspace_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    workspace);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    workspace);
	if (x_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    x);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    x);
	if (y_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    y);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    y);
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qtransfer);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRINT-CHANGE-SYSTEM-ATTRIBUTE-INSTRUCTION */
Object print_change_system_attribute_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, item_designation, gensymed_symbol_1;
    Object system_attribute_name, value_expression;

    x_note_fn_call(211,116);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    system_attribute_name = CAR(gensymed_symbol_1);
    value_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)11L));
    twrite(system_attribute_name);
    twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)4L));
    print_designation(item_designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    return write_expression(value_expression);
}

static Object Qchange_system_attribute_prolog;  /* change-system-attribute-prolog */

static Object Qchange_system_attribute_epilog;  /* change-system-attribute-epilog */

/* CHANGE-SYSTEM-ATTRIBUTE-ACTION-COMPILER */
Object change_system_attribute_action_compiler(statement,
	    unknown_allowed_qm,leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object name_of_attribute, value, temp, temp_1, block_of_variables_qm;
    Object gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,117);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    name_of_attribute = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    value = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qsymbol);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qdatum));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)44L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qchange_system_attribute_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(name_of_attribute,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(value,
	    maybe_add_unknown(Qdatum,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)44L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qchange_system_attribute_epilog,
	    block_of_variables_qm));
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* CHANGE-SYSTEM-ATTRIBUTE-PROLOG-PSEUDO-EMITTER */
Object change_system_attribute_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, name_of_attribute, value, var_spot_block_qm;

    x_note_fn_call(211,118);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    name_of_attribute = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,name_of_attribute);
    emit_stack_node_tree(byte_code_stream,value);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qchange_system_attribute;  /* change-system-attribute */

/* CHANGE-SYSTEM-ATTRIBUTE-EPILOG-PSEUDO-EMITTER */
Object change_system_attribute_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_block_qm;

    x_note_fn_call(211,119);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qchange_system_attribute);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_58;   /* # */

/* PRINT-CHANGE-THE-TEXT-OF-INSTRUCTION */
Object print_change_the_text_of_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, item_designation, value_expression;

    x_note_fn_call(211,120);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    value_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_58,FIX((SI_Long)19L));
    print_designation(item_designation);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)4L));
    return write_expression(value_expression);
}

static Object Qchange_the_text_of_attribute_prolog;  /* change-the-text-of-attribute-prolog */

static Object Qchange_the_text_of_attribute_epilog;  /* change-the-text-of-attribute-epilog */

/* CHANGE-THE-TEXT-OF-ATTRIBUTE-ACTION-COMPILER */
Object change_the_text_of_attribute_action_compiler(statement,
	    unknown_allowed_qm,leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object item_or_place, text, temp, block_of_variables_qm;
    Object compile_reference_to_system_slot;
    Declare_special(1);

    x_note_fn_call(211,121);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item_or_place = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    text = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_7);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,Qtext));
    }
    else
	block_of_variables_qm = Nil;
    compile_reference_to_system_slot = T;
    PUSH_SPECIAL_WITH_SYMBOL(Compile_reference_to_system_slot,Qcompile_reference_to_system_slot,compile_reference_to_system_slot,
	    0);
      emit_already_consed_instruction_to_stream(prolog_stream,
	      phrase_list_3(Qbegin_activity,FIX((SI_Long)45L),
	      unknown_allowed_qm));
      temp = compile_stack_expression(item_or_place,
	      maybe_add_unknown(list_constant_7,unknown_allowed_qm));
      emit_already_consed_instruction_to_stream(prolog_stream,
	      phrase_list_4(Qchange_the_text_of_attribute_prolog,temp,
	      compile_stack_expression(text,maybe_add_unknown(Qtext,
	      unknown_allowed_qm)),block_of_variables_qm));
      if (unknown_allowed_qm)
	  emit_already_consed_instruction_to_stream(epilog_stream,
		  phrase_list_2(Qbegin_activity,FIX((SI_Long)45L)));
      emit_already_consed_instruction_to_stream(epilog_stream,
	      phrase_list_2(Qchange_the_text_of_attribute_epilog,
	      block_of_variables_qm));
      temp = block_of_variables_qm;
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CHANGE-THE-TEXT-OF-ATTRIBUTE-PROLOG-PSEUDO-EMITTER */
Object change_the_text_of_attribute_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item_or_place, text_expression, var_spot_block_qm;

    x_note_fn_call(211,122);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_or_place = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    text_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item_or_place);
    emit_stack_node_tree(byte_code_stream,text_expression);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qchange_the_text_of_attribute;  /* change-the-text-of-attribute */

/* CHANGE-THE-TEXT-OF-ATTRIBUTE-EPILOG-PSEUDO-EMITTER */
Object change_the_text_of_attribute_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_block_qm;

    x_note_fn_call(211,123);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm),length(CDR(var_spot_block_qm)));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qchange_the_text_of_attribute);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_59;   /* # */

/* PRINT-CHANGE-NTH-ELEMENT-INSTRUCTION */
Object print_change_nth_element_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, g2_array_element_designation, element_expression;

    x_note_fn_call(211,124);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_array_element_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_59,FIX((SI_Long)7L));
    print_designation(g2_array_element_designation);
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)3L));
    return write_expression(element_expression);
}

static Object Qnth_element;        /* nth-element */

static Object string_constant_10;  /* "parentheses should be added around the expression ~
				    *                         before the [ ] in `~ND' to avoid misinterpretation.  ~
				    *                         (This current interpretation, which G2 ~
				    *                         Version 3.0 introduced in error, is ~
				    *                         subject to change in a future release)"
				    */

static Object string_constant_11;  /* "Cannot compile a statement containing the change ~
				    *                          action.  `~ND' does not refer to an array or list ~
				    *                          element"
				    */

static Object string_constant_12;  /* "Cannot compile a statement containing the change ~
				    *               action.  `~ND' does not refer to an array or list ~
				    *               element"
				    */

static Object Qchange_nth_element_prolog;  /* change-nth-element-prolog */

static Object list_constant_16;    /* # */

static Object Qchange_nth_element_epilog;  /* change-nth-element-epilog */

/* CHANGE-NTH-ELEMENT-ACTION-COMPILER */
Object change_nth_element_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, designation, element, item;
    Object index_1, temp, temp_1, block_of_variables_qm;
    Object action_compiler_error_qm, current_designation, domain_designation;
    Object domain_role, temp_3, plist, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;

    x_note_fn_call(211,125);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    designation = SECOND(statement);
    element = THIRD(statement);
    item = Nil;
    index_1 = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qitem_or_datum);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qinteger));
    }
    else
	block_of_variables_qm = Nil;
    action_compiler_error_qm = Nil;
    if (SYMBOLP(designation)) {
	item = SECOND(statement);
	index_1 = THIRD(statement);
	element = FOURTH(statement);
    }
    else {
	if (CONSP(designation)) {
	    temp_1 = SECOND(designation);
	    temp_2 = CONSP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(M_CAR(SECOND(designation)),Qnth_element) : 
		    TRUEP(Nil)) {
	    item = THIRD(designation);
	    index_1 = FOURTH(designation);
	}
	else if (CONSP(designation) && CDDR(designation)) {
	    current_designation = designation;
	    domain_designation = Nil;
	    domain_role = Nil;
	  next_loop:
	    domain_designation = THIRD(current_designation);
	    domain_role = SECOND(domain_designation);
	    if ( !TRUEP(current_designation) || LISTP(domain_role) && 
		    EQ(FIRST(domain_role),Qnth_element))
		goto end_loop;
	    current_designation = LISTP(current_designation) ? 
		    THIRD(current_designation) : Qnil;
	    goto next_loop;
	  end_loop:
	    if (LISTP(domain_role) && EQ(FIRST(domain_role),Qnth_element)) {
		compiler_warning(2,string_constant_10,designation);
		temp_3 = THIRD(domain_designation);
		M_THIRD(current_designation) = temp_3;
		item = designation;
		index_1 = FOURTH(domain_designation);
	    }
	    else {
		action_compiler_error_qm = T;
		compiler_error(2,string_constant_11,designation);
	    }
	}
	else {
	    action_compiler_error_qm = T;
	    compiler_error(2,string_constant_12,designation);
	}
    }
    if ( !TRUEP(action_compiler_error_qm)) {
	plist = create_pseudo_instruction_property_list();
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)46L),
		unknown_allowed_qm));
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_3 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_3) = Qchange_nth_element_prolog;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_3 = compile_stack_expression(item,
		maybe_add_unknown(list_constant_16,unknown_allowed_qm));
	M_CAR(gensymed_symbol_3) = temp_3;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_3 = compile_stack_expression(element,
		maybe_add_unknown(Qitem_or_datum,unknown_allowed_qm));
	M_CAR(gensymed_symbol_3) = temp_3;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_3 = compile_stack_expression(index_1,
		maybe_add_unknown(Qinteger,unknown_allowed_qm));
	M_CAR(gensymed_symbol_3) = temp_3;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = block_of_variables_qm;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = plist;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)46L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(Qchange_nth_element_epilog,
		block_of_variables_qm,plist));
    }
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object array_constant_60;   /* # */

/* PRINT-CHANGE-NTH-ELEMENT-TO-NO-VALUE-INSTRUCTION */
Object print_change_nth_element_to_no_value_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, g2_array_element_designation;

    x_note_fn_call(211,126);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_array_element_designation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_59,FIX((SI_Long)7L));
    print_designation(g2_array_element_designation);
    return twrite_beginning_of_wide_string(array_constant_60,
	    FIX((SI_Long)11L));
}

static Object Qchange_nth_element_to_no_value_prolog;  /* change-nth-element-to-no-value-prolog */

static Object Qchange_nth_element_to_no_value_epilog;  /* change-nth-element-to-no-value-epilog */

/* CHANGE-NTH-ELEMENT-TO-NO-VALUE-ACTION-COMPILER */
Object change_nth_element_to_no_value_action_compiler(statement,
	    unknown_allowed_qm,leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, designation, item, index_1;
    Object temp, temp_1, block_of_variables_qm, action_compiler_error_qm;
    Object current_designation, domain_designation, domain_role, temp_3, plist;
    Object gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;

    x_note_fn_call(211,127);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    designation = SECOND(statement);
    item = Nil;
    index_1 = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qitem_or_datum);
	block_of_variables_qm = phrase_list_3(temp,temp_1,
		generate_new_variable_spot(1,Qinteger));
    }
    else
	block_of_variables_qm = Nil;
    action_compiler_error_qm = Nil;
    if (SYMBOLP(designation)) {
	item = SECOND(statement);
	index_1 = THIRD(statement);
    }
    else {
	if (CONSP(designation)) {
	    temp_1 = SECOND(designation);
	    temp_2 = CONSP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(M_CAR(SECOND(designation)),Qnth_element) : 
		    TRUEP(Nil)) {
	    item = THIRD(designation);
	    index_1 = FOURTH(designation);
	}
	else if (CONSP(designation) && CDDR(designation)) {
	    current_designation = designation;
	    domain_designation = Nil;
	    domain_role = Nil;
	  next_loop:
	    domain_designation = THIRD(current_designation);
	    domain_role = SECOND(domain_designation);
	    if ( !TRUEP(current_designation) || LISTP(domain_role) && 
		    EQ(FIRST(domain_role),Qnth_element))
		goto end_loop;
	    current_designation = LISTP(current_designation) ? 
		    THIRD(current_designation) : Qnil;
	    goto next_loop;
	  end_loop:
	    if (LISTP(domain_role) && EQ(FIRST(domain_role),Qnth_element)) {
		compiler_warning(2,string_constant_10,designation);
		temp_3 = THIRD(domain_designation);
		M_THIRD(current_designation) = temp_3;
		item = designation;
		index_1 = FOURTH(domain_designation);
	    }
	    else {
		action_compiler_error_qm = T;
		compiler_error(2,string_constant_11,designation);
	    }
	}
	else {
	    action_compiler_error_qm = T;
	    compiler_error(2,string_constant_12,designation);
	}
    }
    if ( !TRUEP(action_compiler_error_qm)) {
	plist = create_pseudo_instruction_property_list();
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)46L),
		unknown_allowed_qm));
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_3 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_3) = Qchange_nth_element_to_no_value_prolog;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_3 = compile_stack_expression(item,
		maybe_add_unknown(list_constant_16,unknown_allowed_qm));
	M_CAR(gensymed_symbol_3) = temp_3;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_3 = compile_stack_expression(index_1,
		maybe_add_unknown(Qinteger,unknown_allowed_qm));
	M_CAR(gensymed_symbol_3) = temp_3;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = block_of_variables_qm;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = plist;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)46L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(Qchange_nth_element_to_no_value_epilog,
		block_of_variables_qm,plist));
    }
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object Qvalue_type_of_array;  /* value-type-of-array */

static Object Qvalue_type_of_index;  /* value-type-of-index */

/* CHANGE-NTH-ELEMENT-PROLOG-PSEUDO-EMITTER */
Object change_nth_element_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, element, index_1, unknown_allowed_qm;
    Object var_spot_block_qm, plist;

    x_note_fn_call(211,128);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    index_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    plist = CAR(gensymed_symbol);
    set_pseudo_instruction_property(plist,Qvalue_type_of_array,ISVREF(item,
	    (SI_Long)6L));
    set_pseudo_instruction_property(plist,Qvalue_type_of_index,
	    ISVREF(index_1,(SI_Long)6L));
    emit_stack_node_tree(byte_code_stream,item);
    emit_stack_node_tree(byte_code_stream,element);
    emit_coerce_matching_element_type_or_unknown_if_necessary(byte_code_stream,
	    item,element,unknown_allowed_qm);
    emit_stack_node_tree(byte_code_stream,index_1);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object Qchange_nth_element;  /* change-nth-element */

/* CHANGE-NTH-ELEMENT-EPILOG-PSEUDO-EMITTER */
Object change_nth_element_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_block_qm, plist;

    x_note_fn_call(211,129);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    plist = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm));
    }
    if (Allow_inline_evaluate_role_instructions_p && 
	    getfq_function_no_default(ISVREF(plist,(SI_Long)0L),
	    Qvalue_type_of_index) && 
	    type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
	    (SI_Long)0L),Qvalue_type_of_index),Qinteger)) {
	if (type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
		(SI_Long)0L),Qvalue_type_of_array),list_constant_17))
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)135L));
	else if (type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
		(SI_Long)0L),Qvalue_type_of_array),list_constant_18))
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)136L));
	else
	    emit_funcall_instruction_byte_codes(2,byte_code_stream,
		    Qchange_nth_element);
    }
    else
	emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qchange_nth_element);
    reclaim_create_pseudo_instruction_property_list(plist);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CHANGE-NTH-ELEMENT-TO-NO-VALUE-PROLOG-PSEUDO-EMITTER */
Object change_nth_element_to_no_value_prolog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, index_1, var_spot_block_qm, plist;

    x_note_fn_call(211,130);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    index_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    plist = CAR(gensymed_symbol);
    set_pseudo_instruction_property(plist,Qvalue_type_of_array,ISVREF(item,
	    (SI_Long)6L));
    set_pseudo_instruction_property(plist,Qvalue_type_of_index,
	    ISVREF(index_1,(SI_Long)6L));
    emit_stack_node_tree(byte_code_stream,item);
    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)107L));
    emit_stack_node_tree(byte_code_stream,index_1);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CHANGE-NTH-ELEMENT-TO-NO-VALUE-EPILOG-PSEUDO-EMITTER */
Object change_nth_element_to_no_value_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_block_qm, plist;

    x_note_fn_call(211,131);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    plist = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		THIRD(var_spot_block_qm));
    }
    if (Allow_inline_evaluate_role_instructions_p && 
	    getfq_function_no_default(ISVREF(plist,(SI_Long)0L),
	    Qvalue_type_of_index) && 
	    type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
	    (SI_Long)0L),Qvalue_type_of_index),Qinteger)) {
	if (type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
		(SI_Long)0L),Qvalue_type_of_array),list_constant_17))
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)135L));
	else if (type_specification_subtype_p(getfq_function_no_default(ISVREF(plist,
		(SI_Long)0L),Qvalue_type_of_array),list_constant_18))
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)136L));
	else
	    emit_funcall_instruction_byte_codes(2,byte_code_stream,
		    Qchange_nth_element);
    }
    else
	emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qchange_nth_element);
    reclaim_create_pseudo_instruction_property_list(plist);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_61;   /* # */

static Object Qbeginning;          /* beginning */

static Object string_constant_13;  /* " AT THE BEGINNING OF THE ~a LIST " */

static Object Qend;                /* end */

static Object string_constant_14;  /* " AT THE END OF THE ~a LIST " */

static Object Qbefore;             /* before */

static Object array_constant_62;   /* # */

static Object string_constant_15;  /* " IN THE ~a LIST " */

static Object Qafter;              /* after */

static Object array_constant_63;   /* # */

/* PRINT-G2-LIST-INSERT-EXPRESSION-INSTRUCTION */
Object print_g2_list_insert_expression_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, grammar_list_type;
    Object element_expression_1, insert_type, element_expression_2;

    x_note_fn_call(211,132);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    grammar_list_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_expression_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    insert_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_expression_2 = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)7L));
    write_expression(element_expression_1);
    if (EQ(insert_type,Qbeginning)) {
	tformat(2,string_constant_13,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qend)) {
	tformat(2,string_constant_14,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qbefore)) {
	twrite_beginning_of_wide_string(array_constant_62,FIX((SI_Long)8L));
	write_expression(element_expression_2);
	tformat(2,string_constant_15,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qafter)) {
	twrite_beginning_of_wide_string(array_constant_63,FIX((SI_Long)7L));
	write_expression(element_expression_2);
	tformat(2,string_constant_15,grammar_list_type);
	return print_designation(list_designation);
    }
    else
	return VALUES_1(Qnil);
}

/* PRINT-G2-LIST-INSERT-DESIGNATION-INSTRUCTION */
Object print_g2_list_insert_designation_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, grammar_list_type;
    Object element_designation_1, insert_type, element_designation_2;

    x_note_fn_call(211,133);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    grammar_list_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_designation_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    insert_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_designation_2 = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)7L));
    print_designation(element_designation_1);
    if (EQ(insert_type,Qbeginning)) {
	tformat(2,string_constant_13,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qend)) {
	tformat(2,string_constant_14,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qbefore)) {
	twrite_beginning_of_wide_string(array_constant_62,FIX((SI_Long)8L));
	print_designation(element_designation_2);
	tformat(2,string_constant_15,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qafter)) {
	twrite_beginning_of_wide_string(array_constant_63,FIX((SI_Long)7L));
	print_designation(element_designation_2);
	tformat(2,string_constant_15,grammar_list_type);
	return print_designation(list_designation);
    }
    else
	return VALUES_1(Qnil);
}

static Object array_constant_64;   /* # */

static Object array_constant_65;   /* # */

static Object array_constant_66;   /* # */

/* PRINT-G2-LIST-INSERT-INSTRUCTION */
Object print_g2_list_insert_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, item_or_datum, element_qm;
    Object insert_type;

    x_note_fn_call(211,134);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_or_datum = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    insert_type = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)7L));
    write_expression(item_or_datum);
    if (EQ(insert_type,Qbeginning)) {
	twrite_beginning_of_wide_string(array_constant_64,FIX((SI_Long)21L));
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qend)) {
	twrite_beginning_of_wide_string(array_constant_65,FIX((SI_Long)15L));
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qbefore)) {
	twrite_beginning_of_wide_string(array_constant_62,FIX((SI_Long)8L));
	write_expression(element_qm);
	twrite_beginning_of_wide_string(array_constant_66,FIX((SI_Long)4L));
	return print_designation(list_designation);
    }
    else if (EQ(insert_type,Qafter)) {
	twrite_beginning_of_wide_string(array_constant_63,FIX((SI_Long)7L));
	write_expression(element_qm);
	twrite_beginning_of_wide_string(array_constant_66,FIX((SI_Long)4L));
	return print_designation(list_designation);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qg2_list_insert_prolog;  /* g2-list-insert-prolog */

static Object list_constant_19;    /* # */

static Object Qg2_list_insert_epilog;  /* g2-list-insert-epilog */

/* G2-LIST-INSERT-ACTION-COMPILER */
Object g2_list_insert_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, g2_list;
    Object item_or_datum, element_qm, insertion_type, temp, temp_1, temp_2;
    Object block_of_variables_qm, gensymed_symbol_3, car_new_value;

    x_note_fn_call(211,135);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    g2_list = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item_or_datum = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    element_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    insertion_type = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qitem_or_datum);
	temp_2 = generate_new_variable_spot(1,Qitem_or_datum);
	block_of_variables_qm = phrase_list_4(temp,temp_1,temp_2,
		generate_new_variable_spot(1,Qsymbol));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)47L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qg2_list_insert_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(g2_list,
	    maybe_add_unknown(list_constant_19,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(item_or_datum,
	    maybe_add_unknown(Qitem_or_datum,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = element_qm ? compile_stack_expression(element_qm,
	    maybe_add_unknown(Qitem_or_datum,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = insertion_type;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)47L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qg2_list_insert_epilog, ! !TRUEP(element_qm) ? T 
	    : Nil,block_of_variables_qm));
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

static Object Qcoerce_item_or_values_to_matching_element_type_or_unknown;  /* coerce-item-or-values-to-matching-element-type-or-unknown */

static Object Qcoerce_item_or_values_to_matching_element_type;  /* coerce-item-or-values-to-matching-element-type */

/* G2-LIST-INSERT-PROLOG-PSEUDO-EMITTER */
Object g2_list_insert_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, g2_list, item_or_datum, element_qm, insertion_type;
    Object unknown_allowed_qm, var_spot_block_qm;

    x_note_fn_call(211,136);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_or_datum = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    insertion_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,g2_list);
    emit_stack_node_tree(byte_code_stream,item_or_datum);
    if ( !TRUEP(element_qm)) {
	emit_coerce_matching_element_type_or_unknown_if_necessary(byte_code_stream,
		g2_list,item_or_datum,unknown_allowed_qm);
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    }
    else if (memq_function(insertion_type,list_constant_20)) {
	if ( !TRUEP(stack_node_matches_element_type_p(g2_list,item_or_datum)))
	    emit_funcall_instruction_byte_codes(4,byte_code_stream,
		    unknown_allowed_qm ? 
		    Qcoerce_item_or_values_to_matching_element_type_or_unknown 
		    : Qcoerce_item_or_values_to_matching_element_type,
		    FIX((SI_Long)2L),FIX((SI_Long)2L));
	emit_stack_node_tree(byte_code_stream,element_qm);
	emit_type_check_byte_codes(byte_code_stream,Qinteger);
    }
    else {
	emit_stack_node_tree(byte_code_stream,element_qm);
	if ( !(stack_node_matches_element_type_p(g2_list,item_or_datum) && 
		stack_node_matches_element_type_p(g2_list,element_qm)))
	    emit_funcall_instruction_byte_codes(4,byte_code_stream,
		    unknown_allowed_qm ? 
		    Qcoerce_item_or_values_to_matching_element_type_or_unknown 
		    : Qcoerce_item_or_values_to_matching_element_type,
		    FIX((SI_Long)3L),FIX((SI_Long)3L));
    }
    emit_push_constant_byte_codes(byte_code_stream,insertion_type);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qg2_list_insert;     /* g2-list-insert */

/* G2-LIST-INSERT-EPILOG-PSEUDO-EMITTER */
Object g2_list_insert_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, element_p_qm, var_spot_block_qm, g2_list;
    Object item_or_datum, element_qm, insertion_type;

    x_note_fn_call(211,137);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    element_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	g2_list = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	item_or_datum = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	element_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	insertion_type = CAR(gensymed_symbol);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		g2_list);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		item_or_datum);
	if (element_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    element_qm);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    element_qm);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		insertion_type);
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qg2_list_insert);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_67;   /* # */

static Object string_constant_16;  /* "THE FIRST ~a FROM " */

static Object string_constant_17;  /* "THE LAST ~a FROM " */

static Object Qelement;            /* element */

static Object string_constant_18;  /* " FROM THE ~a LIST " */

/* PRINT-G2-LIST-REMOVE-EXPRESSION-INSTRUCTION */
Object print_g2_list_remove_expression_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, grammar_list_type, remove_type;
    Object element_expression;

    x_note_fn_call(211,138);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    grammar_list_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    remove_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_expression = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_67,FIX((SI_Long)7L));
    if (EQ(remove_type,Qfirst)) {
	tformat(2,string_constant_16,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(remove_type,Qlast)) {
	tformat(2,string_constant_17,grammar_list_type);
	return print_designation(list_designation);
    }
    else if (EQ(remove_type,Qelement)) {
	write_expression(element_expression);
	tformat(2,string_constant_18,grammar_list_type);
	return print_designation(list_designation);
    }
    else
	return VALUES_1(Qnil);
}

/* PRINT-G2-LIST-REMOVE-DESIGNATION-INSTRUCTION */
Object print_g2_list_remove_designation_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, grammar_list_type;
    Object element_designation;

    x_note_fn_call(211,139);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    grammar_list_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_designation = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_67,FIX((SI_Long)7L));
    print_designation(element_designation);
    tformat(2,string_constant_18,grammar_list_type);
    return print_designation(list_designation);
}

static Object Qitem_or_value;      /* item-or-value */

static Object array_constant_68;   /* # */

/* PRINT-G2-LIST-REMOVE-INSTRUCTION */
Object print_g2_list_remove_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, list_designation, element_expression_qm;
    Object required_element_type_qm, removal_type, temp;

    x_note_fn_call(211,140);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    list_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    element_expression_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    required_element_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    removal_type = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_67,FIX((SI_Long)7L));
    if (EQ(removal_type,Qfirst)) {
	temp = required_element_type_qm;
	if (temp);
	else
	    temp = Qitem_or_value;
	tformat(2,string_constant_16,temp);
	return print_designation(list_designation);
    }
    else if (EQ(removal_type,Qlast)) {
	temp = required_element_type_qm;
	if (temp);
	else
	    temp = Qitem_or_value;
	tformat(2,string_constant_17,temp);
	return print_designation(list_designation);
    }
    else if (EQ(removal_type,Qelement)) {
	write_expression(element_expression_qm);
	twrite_beginning_of_wide_string(array_constant_68,FIX((SI_Long)6L));
	return print_designation(list_designation);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qg2_list_remove_prolog;  /* g2-list-remove-prolog */

static Object Qg2_list_remove_epilog;  /* g2-list-remove-epilog */

/* G2-LIST-REMOVE-ACTION-COMPILER */
Object g2_list_remove_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, g2_list;
    Object item_or_datum_qm, required_element_type_qm, removal_type, temp;
    Object temp_1, temp_2, block_of_variables_qm, gensymed_symbol_3;
    Object car_new_value;

    x_note_fn_call(211,141);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    g2_list = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item_or_datum_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    required_element_type_qm = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    removal_type = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_4);
	temp_1 = generate_new_variable_spot(1,Qitem_or_datum);
	temp_2 = generate_new_variable_spot(1,Qsymbol);
	block_of_variables_qm = phrase_list_4(temp,temp_1,temp_2,
		generate_new_variable_spot(1,Qsymbol));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)48L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qg2_list_remove_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(g2_list,
	    maybe_add_unknown(list_constant_19,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = item_or_datum_qm ? 
	    compile_stack_expression(item_or_datum_qm,
	    maybe_add_unknown(Qitem_or_datum,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = required_element_type_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = removal_type;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)48L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qg2_list_remove_epilog, ! 
	    !TRUEP(item_or_datum_qm) ? T : Nil,block_of_variables_qm));
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

static Object Qelement_position;   /* element-position */

/* G2-LIST-REMOVE-PROLOG-PSEUDO-EMITTER */
Object g2_list_remove_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, g2_list, item_or_datum_qm;
    Object required_element_type_qm, removal_type, unknown_allowed_qm;
    Object var_spot_block_qm;

    x_note_fn_call(211,142);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_or_datum_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    required_element_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    removal_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,g2_list);
    if (item_or_datum_qm) {
	emit_stack_node_tree(byte_code_stream,item_or_datum_qm);
	if ( !EQ(removal_type,Qelement_position))
	    emit_coerce_matching_element_type_or_unknown_if_necessary(byte_code_stream,
		    g2_list,item_or_datum_qm,unknown_allowed_qm);
    }
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    if (required_element_type_qm)
	emit_push_constant_byte_codes(byte_code_stream,
		required_element_type_qm);
    else
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
    emit_push_constant_byte_codes(byte_code_stream,removal_type);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qg2_list_remove;     /* g2-list-remove */

/* G2-LIST-REMOVE-EPILOG-PSEUDO-EMITTER */
Object g2_list_remove_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item_or_datum_p_qm, var_spot_block_qm, g2_list;
    Object item_or_datum_qm, required_element_type_qm, removal_type;

    x_note_fn_call(211,143);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_or_datum_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	g2_list = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	item_or_datum_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	required_element_type_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	removal_type = CAR(gensymed_symbol);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		g2_list);
	if (item_or_datum_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    item_or_datum_qm);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    item_or_datum_qm);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		required_element_type_qm);
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		removal_type);
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qg2_list_remove);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_69;   /* # */

/* PRINT-NUPEC-SYNCHRONIZE-INSTRUCTION */
Object print_nupec_synchronize_instruction(inst)
    Object inst;
{
    x_note_fn_call(211,144);
    return twrite_beginning_of_wide_string(array_constant_69,
	    FIX((SI_Long)17L));
}

static Object Qnupec_synchronize_prolog;  /* nupec-synchronize-prolog */

static Object Qnupec_synchronize_epilog;  /* nupec-synchronize-epilog */

/* NUPEC-SYNCHRONIZE-ACTION-COMPILER */
Object nupec_synchronize_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object g2_to_g2_object, designation_list, class_list, designation_count;
    Object temp, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1, temp_2;
    Object block_of_variables_qm, gensymed_symbol_3, car_new_value;
    Object designation, ab_loop_list_;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(211,145);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    g2_to_g2_object = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation_list = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    class_list = CAR(gensymed_symbol_2);
    designation_count = length(designation_list);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil);
	ab_loop_repeat_ = IFIX(designation_count);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,
		list_constant_4),Nil);
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
	temp_2 = generate_new_variable_spot(1,Qinteger);
	block_of_variables_qm = nconc2(temp,nconc2(temp_1,
		phrase_list_2(temp_2,generate_new_variable_spot(1,Qinteger))));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)49L),
	    unknown_allowed_qm));
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qnupec_synchronize_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = compile_stack_expression(g2_to_g2_object,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm));
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    designation = Nil;
    ab_loop_list_ = designation_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
    ab_loopvar_ = Qnil;
  end_2:;
    M_CAR(gensymed_symbol_3) = ab_loopvar_;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = class_list;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)49L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_3(Qnupec_synchronize_epilog,block_of_variables_qm,
	    FIX(IFIX(designation_count) + (SI_Long)2L)));
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

/* NUPEC-SYNCHRONIZE-PROLOG-PSEUDO-EMITTER */
Object nupec_synchronize_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, g2_to_g2_object, list_of_designations;
    Object list_of_classes, var_spot_block_qm, index_1, designation;
    Object ab_loop_list_;

    x_note_fn_call(211,146);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_to_g2_object = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    list_of_designations = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    list_of_classes = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    index_1 = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    list_of_classes);
    emit_stack_node_tree(byte_code_stream,g2_to_g2_object);
    designation = Nil;
    ab_loop_list_ = list_of_designations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,designation);
    goto next_loop;
  end_loop:;
    emit_push_constant_byte_codes(byte_code_stream,index_1);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NUPEC-SYNCHRONIZE-EPILOG-PSEUDO-EMITTER */
Object nupec_synchronize_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, var_spot, ab_loop_list_;

    x_note_fn_call(211,147);
    var_spot_block_qm = SECOND(instruction);
    var_spot = Nil;
    ab_loop_list_ = var_spot_block_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var_spot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    goto next_loop;
  end_loop:;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)117L));
    write_byte_code_to_stream(byte_code_stream,THIRD(instruction));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_70;   /* # */

static Object array_constant_71;   /* # */

/* PRINT-CREATE-EXPLANATION-INSTRUCTION */
Object print_create_explanation_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, designation, local_name_qm;

    x_note_fn_call(211,148);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_70,FIX((SI_Long)22L));
    if (local_name_qm) {
	print_designation(local_name_qm);
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
    }
    twrite_beginning_of_wide_string(array_constant_71,FIX((SI_Long)4L));
    return print_designation(designation);
}

static Object Qexplanation;        /* explanation */

static Object string_constant_19;  /* "In the create explanation action, the local name ~
				    *                 ~a is declared to hold ~NT, not ~NT."
				    */

static Object Qcreate_explanation_prolog;  /* create-explanation-prolog */

static Object Qcreate_explanation_epilog;  /* create-explanation-epilog */

/* CREATE-EXPLANATION-ACTION-COMPILER */
Object create_explanation_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object variable_or_parameter_designation, local_name_qm, var_spot_qm;
    Object var_spot_description_qm, var_spot_type_qm, compiler_error_qm;
    Object created_type, block_of_variables_qm, temp;
    Object result;

    x_note_fn_call(211,149);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    variable_or_parameter_designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    var_spot_qm = Nil;
    var_spot_description_qm = Nil;
    var_spot_type_qm = Nil;
    compiler_error_qm = Nil;
    created_type = make_class_type_specification(Qexplanation);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,Qsymbol),Nil) : Nil;
    if (local_name_qm) {
	result = variable_spot_and_description_for_local_name(local_name_qm);
	MVS_2(result,var_spot_qm,var_spot_description_qm);
	if ( !TRUEP(var_spot_qm)) {
	    compiler_error_qm = T;
	    procedure_compiler_missing_local_name_error(local_name_qm);
	}
	else {
	    var_spot_type_qm = 
		    getfq_function_no_default(CDR(var_spot_description_qm),
		    Ktype);
	    if ( !TRUEP(type_specifications_could_intersect_p(created_type,
		    var_spot_type_qm))) {
		compiler_error_qm = T;
		compiler_error(4,string_constant_19,local_name_qm,
			var_spot_type_qm,created_type);
	    }
	}
    }
    if ( !TRUEP(compiler_error_qm)) {
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)50L),
		unknown_allowed_qm));
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qcreate_explanation_prolog,
		compile_stack_expression(variable_or_parameter_designation,
		maybe_add_unknown(list_constant_11,unknown_allowed_qm)),
		block_of_variables_qm));
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)50L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_4(Qcreate_explanation_epilog,var_spot_qm,
		var_spot_type_qm,block_of_variables_qm));
    }
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CREATE-EXPLANATION-PROLOG-PSEUDO-EMITTER */
Object create_explanation_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, variable_or_parameter, var_spot_block_qm;

    x_note_fn_call(211,150);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    variable_or_parameter = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,variable_or_parameter);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcreate_explanation;  /* create-explanation */

/* CREATE-EXPLANATION-EPILOG-PSEUDO-EMITTER */
Object create_explanation_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, var_spot_qm, var_spot_type_qm, var_spot_block_qm;

    x_note_fn_call(211,151);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm)
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,
	    Qcreate_explanation);
    if (var_spot_qm) {
	emit_type_check_byte_codes(byte_code_stream,var_spot_type_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_72;   /* # */

/* PRINT-UPDATE-INSTRUCTION */
Object print_update_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,152);
    twrite_beginning_of_wide_string(array_constant_72,FIX((SI_Long)7L));
    return write_expression(SECOND(instruction));
}

static Object Qupdate_prolog;      /* update-prolog */

static Object Qupdate_epilog;      /* update-epilog */

/* UPDATE-ACTION-COMPILER */
Object update_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, display;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,153);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    display = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)51L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qupdate_prolog,compile_stack_expression(display,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)51L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qupdate_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* UPDATE-PROLOG-PSEUDO-EMITTER */
Object update_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, chart, var_spot_block_qm;
    Declare_special(1);

    x_note_fn_call(211,154);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    chart = CAR(gensymed_symbol);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      gensymed_symbol = CDR(gensymed_symbol);
      var_spot_block_qm = CAR(gensymed_symbol);
      emit_stack_node_tree(byte_code_stream,Chart);
      if (var_spot_block_qm)
	  emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		  FIRST(var_spot_block_qm),length(var_spot_block_qm));
    POP_SPECIAL();
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qupdate;             /* update */

/* UPDATE-EPILOG-PSEUDO-EMITTER */
Object update_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,155);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qupdate);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRINT-CREATE-CONNECTION-INSTRUCTION */
Object print_create_connection_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, class_expression, connection_specification;
    Object local_name_qm;

    x_note_fn_call(211,156);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    class_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    connection_specification = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_51,FIX((SI_Long)19L));
    if (local_name_qm) {
	print_designation(local_name_qm);
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
    }
    twrite_beginning_of_wide_string(array_constant_52,FIX((SI_Long)22L));
    return write_expression(class_expression);
}

static Object Qconnected_between;  /* connected-between */

static Object list_constant_21;    /* # */

static Object string_constant_20;  /* "The local name ~a is declared to hold the type ~
				    *                             ~NT, which does not include the type ~NT."
				    */

/* CREATE-CONNECTION-ACTION-COMPILER */
Object create_connection_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object class_expression, connection_specification, local_name_qm, temp;
    Object var_spot, description, type;
    char connected_between_case_qm;
    Object result;

    x_note_fn_call(211,157);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    class_expression = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    connection_specification = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    connected_between_case_qm = EQ(FIRST(connection_specification),
	    Qconnected_between);
    if ( !TRUEP(local_name_qm))
	temp = emit_create_connection_action(connected_between_case_qm ? T 
		: Nil,class_expression,connection_specification,Nil,Nil,
		prolog_stream,epilog_stream,leave_on_stack_qm,
		unknown_allowed_qm);
    else {
	result = variable_spot_and_description_for_local_name(local_name_qm);
	MVS_2(result,var_spot,description);
	if ( !TRUEP(var_spot))
	    temp = procedure_compiler_missing_local_name_error(local_name_qm);
	else {
	    type = getfq_function_no_default(CDR(description),Ktype);
	    temp =  
		    !TRUEP(type_specifications_could_intersect_p(list_constant_21,
		    type)) ? compiler_error(4,string_constant_20,
		    local_name_qm,type,list_constant_21) : 
		    emit_create_connection_action(connected_between_case_qm 
		    ? T : Nil,class_expression,connection_specification,
		    var_spot,type,prolog_stream,epilog_stream,
		    leave_on_stack_qm,unknown_allowed_qm);
	}
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qcreate_connection_prolog;  /* create-connection-prolog */

static Object Qcreate_connection_epilog;  /* create-connection-epilog */

/* EMIT-CREATE-CONNECTION-ACTION */
Object emit_create_connection_action(connected_between_case_qm,
	    class_expression_qm,connection_specification,var_spot_qm,
	    var_spot_type_qm,prolog_stream_qm,epilog_stream_qm,
	    leave_on_stack_qm,unknown_allowed_qm)
    Object connected_between_case_qm, class_expression_qm;
    Object connection_specification, var_spot_qm, var_spot_type_qm;
    Object prolog_stream_qm, epilog_stream_qm, leave_on_stack_qm;
    Object unknown_allowed_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object block_of_variables_qm, temp, temp_1, end_1_designation_qm;
    Object make_new_stub_1_qm, side_1_qm, position_1_qm, portname_1_qm;
    Object end_2_designation_qm, make_new_stub_2_qm, side_2_qm, position_2_qm;
    Object portname_2_qm, style_qm, direction_qm, vertices_qm;
    char car_new_value_1;

    x_note_fn_call(211,158);
    if ( !TRUEP(leave_on_stack_qm)) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)14L));
	gensymed_symbol_1 = gensymed_symbol;
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qinteger);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,list_constant_4);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qinteger);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qsymbol);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = generate_new_variable_spot(1,Qitem_or_datum);
	M_CAR(gensymed_symbol_1) = car_new_value;
	block_of_variables_qm = gensymed_symbol;
    }
    else
	block_of_variables_qm = Nil;
    temp = 
	    compile_connection_end_specifier(SECOND(connection_specification),
	    unknown_allowed_qm);
    temp_1 = connected_between_case_qm ? 
	    compile_connection_end_specifier(THIRD(connection_specification),
	    unknown_allowed_qm) : compile_connection_end_specifier(Nil,
	    unknown_allowed_qm);
    gensymed_symbol = nconc2(temp,nconc2(temp_1,connected_between_case_qm ?
	     
	    compile_connection_creation_details(FOURTH(connection_specification),
	    unknown_allowed_qm) : 
	    compile_connection_creation_details(THIRD(connection_specification),
	    unknown_allowed_qm)));
    end_1_designation_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    end_2_designation_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    style_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    direction_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    vertices_qm = CAR(gensymed_symbol);
    emit_already_consed_instruction_to_stream(prolog_stream_qm,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)52L),
	    unknown_allowed_qm));
    gensymed_symbol = make_phrase_list(FIX((SI_Long)16L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qcreate_connection_prolog;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = class_expression_qm ? 
	    compile_stack_expression(class_expression_qm,
	    maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = end_1_designation_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = make_new_stub_1_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = side_1_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = position_1_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = portname_1_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = end_2_designation_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = make_new_stub_2_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = side_2_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = position_2_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = portname_2_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = style_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = direction_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = vertices_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = block_of_variables_qm;
    emit_already_consed_instruction_to_stream(prolog_stream_qm,
	    gensymed_symbol);
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream_qm,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)52L)));
    gensymed_symbol = make_phrase_list(FIX((SI_Long)17L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qcreate_connection_epilog;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(end_1_designation_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(make_new_stub_1_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(side_1_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(position_1_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(portname_1_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(end_2_designation_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(make_new_stub_2_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(side_2_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(position_2_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(portname_2_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(style_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(direction_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 =  ! !TRUEP(vertices_qm);
    M_CAR(gensymed_symbol_1) = car_new_value_1 ? T : Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = var_spot_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = var_spot_type_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = block_of_variables_qm;
    return emit_already_consed_instruction_to_stream(epilog_stream_qm,
	    gensymed_symbol);
}

static Object Qnewly_located_at;   /* newly-located-at */

/* COMPILE-CONNECTION-END-SPECIFIER */
Object compile_connection_end_specifier(end_specifier_qm,unknown_allowed_qm)
    Object end_specifier_qm, unknown_allowed_qm;
{
    Object end_position_specifier, side_qm, position_on_side_qm, portname_qm;
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;
    char make_new_stub_qm;

    x_note_fn_call(211,159);
    if (end_specifier_qm) {
	end_position_specifier = SECOND(end_specifier_qm);
	make_new_stub_qm = EQ(FIRST(end_position_specifier),Qnewly_located_at);
	side_qm = SECOND(end_position_specifier);
	position_on_side_qm = THIRD(end_position_specifier);
	portname_qm = FOURTH(end_position_specifier);
	gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	car_new_value = compile_stack_expression(FIRST(end_specifier_qm),
		maybe_add_unknown(list_constant_4,unknown_allowed_qm));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = make_new_stub_qm ? T : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = side_qm ? compile_stack_expression(side_qm,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = position_on_side_qm ? 
		compile_stack_expression(position_on_side_qm,
		maybe_add_unknown(Qnumber,unknown_allowed_qm)) : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = portname_qm ? compile_stack_expression(portname_qm,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	return VALUES_1(gensymed_symbol);
    }
    else {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Nil;
	return VALUES_1(gensymed_symbol);
    }
}

static Object list_constant_22;    /* # */

/* COMPILE-CONNECTION-CREATION-DETAILS */
Object compile_connection_creation_details(details_qm,unknown_allowed_qm)
    Object details_qm, unknown_allowed_qm;
{
    Object style_details_qm, direction_details_qm, vertices_details_qm, temp;
    Object temp_1;

    x_note_fn_call(211,160);
    if (details_qm) {
	style_details_qm = FIRST(details_qm);
	direction_details_qm = SECOND(details_qm);
	vertices_details_qm = THIRD(details_qm);
	temp = style_details_qm ? 
		compile_stack_expression(style_details_qm,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
	temp_1 = direction_details_qm ? 
		compile_stack_expression(direction_details_qm,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm)) : Nil;
	return phrase_list_3(temp,temp_1,vertices_details_qm ? 
		(CONSP(vertices_details_qm) &&  
		!(ATOM(vertices_details_qm) ? vertices_details_qm && 
		SYMBOLP(vertices_details_qm) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(vertices_details_qm)))) 
		? vertices_details_qm : 
		compile_stack_expression(vertices_details_qm,
		maybe_add_unknown(list_constant_22,unknown_allowed_qm))) : 
		Nil);
    }
    else
	return phrase_list_3(Nil,Nil,Nil);
}

static Object Qconnection;         /* connection */

/* CREATE-CONNECTION-PROLOG-PSEUDO-EMITTER */
Object create_connection_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, class_qm, end_1_designation_qm, make_new_stub_1_qm;
    Object side_1_qm, position_1_qm, portname_1_qm, end_2_designation_qm;
    Object make_new_stub_2_qm, side_2_qm, position_2_qm, portname_2_qm;
    Object style_qm, direction_qm, vertices_qm, var_spot_block_qm, index_1;

    x_note_fn_call(211,161);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    class_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    end_1_designation_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    end_2_designation_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    style_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    direction_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    vertices_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if ( !TRUEP(class_qm))
	emit_push_constant_byte_codes(byte_code_stream,Qconnection);
    else
	emit_stack_node_tree(byte_code_stream,class_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,end_1_designation_qm);
    emit_push_constant_byte_codes(byte_code_stream,make_new_stub_1_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,side_1_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,position_1_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,portname_1_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,end_2_designation_qm);
    emit_push_constant_byte_codes(byte_code_stream,make_new_stub_2_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,side_2_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,position_2_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,portname_2_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,style_qm);
    emit_stack_node_tree_or_nil(byte_code_stream,direction_qm);
    if ( !TRUEP(vertices_qm))
	emit_push_constant_byte_codes(byte_code_stream,Nil);
    else if (CONSP(vertices_qm)) {
	index_1 = 
		register_internal_constant_in_byte_code_stream(byte_code_stream,
		vertices_qm);
	emit_push_constant_byte_codes(byte_code_stream,index_1);
    }
    else
	emit_stack_node_tree(byte_code_stream,vertices_qm);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CREATE-CONNECTION-EPILOG-PSEUDO-EMITTER */
Object create_connection_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, end_1_designation_p_qm, make_new_stub_1_p_qm;
    Object side_1_p_qm, position_1_p_qm, portname_1_p_qm;
    Object end_2_designation_p_qm, make_new_stub_2_p_qm, side_2_p_qm;
    Object position_2_p_qm, portname_2_p_qm, style_p_qm, direction_p_qm;
    Object vertices_p_qm, var_spot_qm, var_spot_type_qm, var_spot_block_qm;
    Object class_1, end_1_var_spot, make_new_stub_1_var_spot, side_1_var_spot;
    Object position_1_var_spot, portname_1_var_spot, end_2_var_spot;
    Object make_new_stub_2_var_spot, side_2_var_spot, position_2_var_spot;
    Object portname_2_var_spot, style_var_spot, direction_var_spot;
    Object vertices_var_spot;

    x_note_fn_call(211,162);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    end_1_designation_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_1_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_1_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_1_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_1_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    end_2_designation_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    make_new_stub_2_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side_2_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_2_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    portname_2_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    style_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    direction_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    vertices_p_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_type_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm) {
	gensymed_symbol = var_spot_block_qm;
	class_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	end_1_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	make_new_stub_1_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	side_1_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	position_1_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	portname_1_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	end_2_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	make_new_stub_2_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	side_2_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	position_2_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	portname_2_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	style_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	direction_var_spot = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	vertices_var_spot = CAR(gensymed_symbol);
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		class_1);
	if (end_1_designation_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    end_1_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    end_1_var_spot);
	if (make_new_stub_1_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    make_new_stub_1_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    make_new_stub_1_var_spot);
	if (side_1_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    side_1_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    side_1_var_spot);
	if (position_1_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    position_1_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    position_1_var_spot);
	if (portname_1_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    portname_1_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    portname_1_var_spot);
	if (end_2_designation_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    end_2_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    end_2_var_spot);
	if (make_new_stub_2_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    make_new_stub_2_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    make_new_stub_2_var_spot);
	if (side_2_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    side_2_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    side_2_var_spot);
	if (position_2_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    position_2_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    position_2_var_spot);
	if (portname_2_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    portname_2_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    portname_2_var_spot);
	if (style_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    style_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    style_var_spot);
	if (direction_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    direction_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    direction_var_spot);
	if (vertices_p_qm)
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    vertices_var_spot);
	else
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    vertices_var_spot);
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)98L));
    if (var_spot_qm) {
	emit_type_check_byte_codes(byte_code_stream,var_spot_type_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_73;   /* # */

/* PRINT-ABORT-INSTRUCTION */
Object print_abort_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,163);
    twrite_beginning_of_wide_string(array_constant_73,FIX((SI_Long)6L));
    return write_expression(SECOND(instruction));
}

static Object Qabort_prolog;       /* abort-prolog */

static Object list_constant_23;    /* # */

static Object Qabort_epilog;       /* abort-epilog */

/* ABORT-ACTION-COMPILER */
Object abort_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object procedure_or_invocation, block_of_variables_qm, temp;

    x_note_fn_call(211,164);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    procedure_or_invocation = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)53L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qabort_prolog,
	    compile_stack_expression(procedure_or_invocation,
	    maybe_add_unknown(list_constant_23,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)53L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qabort_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* ABORT-PROLOG-PSEUDO-EMITTER */
Object abort_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure_or_invocation, var_spot_block_qm;

    x_note_fn_call(211,165);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_or_invocation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure_or_invocation);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qabort_g2;           /* abort */

/* ABORT-EPILOG-PSEUDO-EMITTER */
Object abort_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,166);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qabort_g2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_74;   /* # */

/* PRINT-SHUT-DOWN-G2-INSTRUCTION */
Object print_shut_down_g2_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,167);
    return twrite_beginning_of_wide_string(array_constant_74,
	    FIX((SI_Long)12L));
}

static Object Qshut_down_g2_prolog;  /* shut-down-g2-prolog */

static Object Qshut_down_g2_epilog;  /* shut-down-g2-epilog */

/* SHUT-DOWN-G2-ACTION-COMPILER */
Object shut_down_g2_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(211,168);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_cons(Qshut_down_g2_prolog,Nil));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qbegin_activity,FIX((SI_Long)54L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_cons(Qshut_down_g2_epilog,Nil));
    temp = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* SHUT-DOWN-G2-PROLOG-PSEUDO-EMITTER */
Object shut_down_g2_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,169);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qshut_down_g2;       /* shut-down-g2 */

/* SHUT-DOWN-G2-EPILOG-PSEUDO-EMITTER */
Object shut_down_g2_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,170);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qshut_down_g2);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_75;   /* # */

/* PRINT-RESET-KB-INSTRUCTION */
Object print_reset_kb_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,171);
    return twrite_beginning_of_wide_string(array_constant_75,
	    FIX((SI_Long)20L));
}

static Object Qreset_kb_prolog;    /* reset-kb-prolog */

static Object Qreset_kb_epilog;    /* reset-kb-epilog */

/* RESET-KB-ACTION-COMPILER */
Object reset_kb_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(211,172);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_cons(Qreset_kb_prolog,Nil));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qbegin_activity,FIX((SI_Long)55L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_cons(Qreset_kb_epilog,Nil));
    temp = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* RESET-KB-PROLOG-PSEUDO-EMITTER */
Object reset_kb_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,173);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RESET-KB-EPILOG-PSEUDO-EMITTER */
Object reset_kb_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,174);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)116L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_76;   /* # */

/* PRINT-PAUSE-KB-INSTRUCTION */
Object print_pause_kb_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,175);
    return twrite_beginning_of_wide_string(array_constant_76,
	    FIX((SI_Long)20L));
}

static Object Qpause_kb_prolog;    /* pause-kb-prolog */

static Object Qpause_kb_epilog;    /* pause-kb-epilog */

/* PAUSE-KB-ACTION-COMPILER */
Object pause_kb_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(211,176);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_cons(Qpause_kb_prolog,Nil));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qbegin_activity,FIX((SI_Long)56L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_cons(Qpause_kb_epilog,Nil));
    temp = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* PAUSE-KB-PROLOG-PSEUDO-EMITTER */
Object pause_kb_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,177);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PAUSE-KB-EPILOG-PSEUDO-EMITTER */
Object pause_kb_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,178);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)115L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_21;  /* "OF THE CLASS NAMED BY ~NE BY CLONING ~ND." */

/* PRINT-CREATE-BY-CLONING-STATEMENT */
Object print_create_by_cloning_statement(instruction)
    Object instruction;
{
    Object gensymed_symbol, class_expression, designation, local_name_qm;

    x_note_fn_call(211,179);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    class_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_51,FIX((SI_Long)19L));
    if (local_name_qm) {
	print_designation(local_name_qm);
	twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)1L));
    }
    return tformat(3,string_constant_21,class_expression,designation);
}

static Object Qcreate_by_cloning_prolog;  /* create-by-cloning-prolog */

static Object Qcreate_by_cloning_epilog;  /* create-by-cloning-epilog */

/* CREATE-BY-CLONING-ACTION-COMPILER */
Object create_by_cloning_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object class_expression, designation, local_name_qm, var_spot_qm;
    Object var_spot_description_qm, var_spot_type_qm, compiler_error_qm;
    Object created_type, check_created_type_qm, temp, block_of_variables_qm;
    Object result;

    x_note_fn_call(211,180);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    class_expression = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name_qm = CAR(gensymed_symbol_2);
    var_spot_qm = Nil;
    var_spot_description_qm = Nil;
    var_spot_type_qm = Nil;
    compiler_error_qm = Nil;
    created_type = make_class_type_specification(CONSP(class_expression) 
	    && EQ(CAR(class_expression),Qquote) ? SECOND(class_expression) 
	    : Qitem);
    check_created_type_qm = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,Qsymbol);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,created_type));
    }
    else
	block_of_variables_qm = Nil;
    if (local_name_qm) {
	result = variable_spot_and_description_for_local_name(local_name_qm);
	MVS_2(result,var_spot_qm,var_spot_description_qm);
	if ( !TRUEP(var_spot_qm)) {
	    compiler_error_qm = T;
	    procedure_compiler_missing_local_name_error(local_name_qm);
	}
	else {
	    var_spot_type_qm = 
		    getfq_function_no_default(CDR(var_spot_description_qm),
		    Ktype);
	    if (type_specifications_could_intersect_p(created_type,
		    var_spot_type_qm))
		check_created_type_qm = var_spot_type_qm;
	    else
		compiler_error(4,string_constant_9,local_name_qm,
			var_spot_type_qm,created_type);
	}
    }
    if ( !TRUEP(compiler_error_qm)) {
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)57L),
		unknown_allowed_qm));
	temp = compile_stack_expression(class_expression,
		maybe_add_unknown(Qsymbol,unknown_allowed_qm));
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_4(Qcreate_by_cloning_prolog,temp,
		compile_stack_expression(designation,
		maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
		block_of_variables_qm));
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)57L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_4(Qcreate_by_cloning_epilog,var_spot_qm,
		check_created_type_qm,block_of_variables_qm));
    }
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CREATE-BY-CLONING-PROLOG-PSEUDO-EMITTER */
Object create_by_cloning_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, symbol_expression, designation, var_spot_block_qm;

    x_note_fn_call(211,181);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    symbol_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,symbol_expression);
    emit_stack_node_tree(byte_code_stream,designation);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcreate_by_cloning;  /* create-by-cloning */

/* CREATE-BY-CLONING-EPILOG-PSEUDO-EMITTER */
Object create_by_cloning_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item_var_spot_qm, item_var_spot_type_to_check_qm;
    Object var_spot_block_qm;

    x_note_fn_call(211,182);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item_var_spot_type_to_check_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    if (var_spot_block_qm)
	emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qcreate_by_cloning);
    if (item_var_spot_qm) {
	if (item_var_spot_type_to_check_qm)
	    emit_type_check_byte_codes(byte_code_stream,
		    item_var_spot_type_to_check_qm);
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		item_var_spot_qm);
    }
    else
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_22;  /* "MAKE ~ND PERMANENT" */

/* PRINT-MAKE-PERMANENT-INSTRUCTION */
Object print_make_permanent_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,183);
    return tformat(2,string_constant_22,SECOND(instruction));
}

static Object Qmake_permanent_prolog;  /* make-permanent-prolog */

static Object Qmake_permanent_epilog;  /* make-permanent-epilog */

/* MAKE-PERMANENT-ACTION-COMPILER */
Object make_permanent_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,184);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)58L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qmake_permanent_prolog,
	    compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)58L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qmake_permanent_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* MAKE-PERMANENT-PROLOG-PSEUDO-EMITTER */
Object make_permanent_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, var_spot_block_qm;

    x_note_fn_call(211,185);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmake_permanent;     /* make-permanent */

/* MAKE-PERMANENT-EPILOG-PSEUDO-EMITTER */
Object make_permanent_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,186);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmake_permanent);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_23;  /* "MAKE ~ND TRANSIENT" */

/* PRINT-MAKE-TRANSIENT-INSTRUCTION */
Object print_make_transient_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,187);
    return tformat(2,string_constant_23,SECOND(instruction));
}

static Object Qmake_transient_prolog;  /* make-transient-prolog */

static Object Qmake_transient_epilog;  /* make-transient-epilog */

/* MAKE-TRANSIENT-ACTION-COMPILER */
Object make_transient_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,188);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)59L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qmake_transient_prolog,
	    compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)59L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qmake_transient_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* MAKE-TRANSIENT-PROLOG-PSEUDO-EMITTER */
Object make_transient_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, item, var_spot_block_qm;

    x_note_fn_call(211,189);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,item);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmake_transient;     /* make-transient */

/* MAKE-TRANSIENT-EPILOG-PSEUDO-EMITTER */
Object make_transient_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,190);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmake_transient);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_24;  /* "MAKE ~ND THE SUBWORKSPACE OF ~ND" */

/* PRINT-MAKE-SUBWORKSPACE-INSTRUCTION */
Object print_make_subworkspace_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,191);
    return tformat(3,string_constant_24,SECOND(instruction),
	    THIRD(instruction));
}

static Object Qmake_subworkspace_prolog;  /* make-subworkspace-prolog */

static Object Qmake_subworkspace_epilog;  /* make-subworkspace-epilog */

/* MAKE-SUBWORKSPACE-ACTION-COMPILER */
Object make_subworkspace_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, kb_workspace;
    Object item, temp, block_of_variables_qm;

    x_note_fn_call(211,192);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    kb_workspace = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = generate_new_variable_spot(1,list_constant_12);
	block_of_variables_qm = phrase_list_2(temp,
		generate_new_variable_spot(1,list_constant_4));
    }
    else
	block_of_variables_qm = Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)60L),
	    unknown_allowed_qm));
    temp = compile_stack_expression(kb_workspace,
	    maybe_add_unknown(list_constant_12,unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_4(Qmake_subworkspace_prolog,temp,
	    compile_stack_expression(item,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)60L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qmake_subworkspace_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* MAKE-SUBWORKSPACE-PROLOG-PSEUDO-EMITTER */
Object make_subworkspace_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, kb_workspace, item, var_spot_block_qm;

    x_note_fn_call(211,193);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    kb_workspace = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,kb_workspace);
    emit_stack_node_tree(byte_code_stream,item);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmake_subworkspace;  /* make-subworkspace */

/* MAKE-SUBWORKSPACE-EPILOG-PSEUDO-EMITTER */
Object make_subworkspace_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,194);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm) {
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		SECOND(var_spot_block_qm));
    }
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qmake_subworkspace);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_25;  /* "PRINT ~ND" */

/* PRINT-PRINT-INSTRUCTION */
Object print_print_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,195);
    return tformat(2,string_constant_25,SECOND(instruction));
}

static Object Qprint_prolog;       /* print-prolog */

static Object Qprint_epilog;       /* print-epilog */

/* PRINT-ACTION-COMPILER */
Object print_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, workspace;
    Object block_of_variables_qm, temp;

    x_note_fn_call(211,196);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    workspace = CAR(gensymed_symbol_2);
    block_of_variables_qm =  !TRUEP(leave_on_stack_qm) ? 
	    phrase_cons(generate_new_variable_spot(1,list_constant_4),Nil) 
	    : Nil;
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qbegin_activity,FIX((SI_Long)61L),
	    unknown_allowed_qm));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_3(Qprint_prolog,compile_stack_expression(workspace,
	    maybe_add_unknown(list_constant_4,unknown_allowed_qm)),
	    block_of_variables_qm));
    if (unknown_allowed_qm)
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_2(Qbegin_activity,FIX((SI_Long)61L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qprint_epilog,block_of_variables_qm));
    temp = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* PRINT-PROLOG-PSEUDO-EMITTER */
Object print_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, workspace, var_spot_block_qm;

    x_note_fn_call(211,197);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    workspace = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,workspace);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PRINT-EPILOG-PSEUDO-EMITTER */
Object print_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm;

    x_note_fn_call(211,198);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm)
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		FIRST(var_spot_block_qm));
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qprint);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qg2_print;           /* g2-print */

/* DECODE-PRINT-DETAILS-AS-PHRASE-RULE */
Object decode_print_details_as_phrase_rule(statement)
    Object statement;
{
    Object gensymed_symbol, workspace;

    x_note_fn_call(211,199);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    workspace = CAR(gensymed_symbol);
    return phrase_list_3(Qstart,Qg2_print,phrase_list_2(workspace,Qfalse));
}

static Object array_constant_77;   /* # */

static Object array_constant_78;   /* # */

static Object array_constant_79;   /* # */

/* PRINT-CALL-INSTRUCTION */
Object print_call_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, procedure_designation, argument_list;
    Object desired_value_count, arg, ab_loop_list_, first_time_qm;
    Object ab_loop_iter_flag_;

    x_note_fn_call(211,200);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    argument_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    desired_value_count = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_77,FIX((SI_Long)5L));
    print_designation(procedure_designation);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = argument_list;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_78,FIX((SI_Long)11L));
    write_expression(desired_value_count);
    return twrite_beginning_of_wide_string(array_constant_79,FIX((SI_Long)7L));
}

/* PRINT-CALL-ASSIGNMENT-INSTRUCTION */
Object print_call_assignment_instruction(instruction)
    Object instruction;
{
    Object gensymed_symbol, procedure_designation, argument_list;
    Object desired_value_count, arg, ab_loop_list_, first_time_qm;
    Object ab_loop_iter_flag_;

    x_note_fn_call(211,201);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    procedure_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    argument_list = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    desired_value_count = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_77,FIX((SI_Long)5L));
    print_designation(procedure_designation);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = argument_list;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_78,FIX((SI_Long)11L));
    write_expression(desired_value_count);
    return twrite_beginning_of_wide_string(array_constant_79,FIX((SI_Long)7L));
}

static Object string_constant_26;  /* "CALL accepts a maximum of 255 arguments, this call passed ~a." */

static Object string_constant_27;  /* "CALL receives a maximum of 255 values, this call requested ~a." */

static Object Qcall_prolog;        /* call-prolog */

static Object Qcall_dependent_epilog;  /* call-dependent-epilog */

static Object Qcall_epilog;        /* call-epilog */

static Object Qcall_dependent_rpc_epilog;  /* call-dependent-rpc-epilog */

static Object Qcall_rpc_epilog;    /* call-rpc-epilog */

/* CALL-ACTION-ACTION-COMPILER */
Object call_action_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object procedure_designation, argument_list, across_qm, argument_count;
    Object argument_stack_nodes, stable_procedure_qm, stable_arg_types_qm;
    Object recorded_procedure_call_free_reference_qm, compiled_procedure, temp;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;
    Object block_of_variables_qm, sub_class_bit_vector, temp_3;
    Object svref_new_value, gensymed_symbol_6, argument, ab_loop_list_;
    Object type_cons_qm, ab_loop_iter_flag_, argument_node;
    SI_Long desired_value_count, ab_loop_repeat_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5;
    char temp_2;

    x_note_fn_call(211,202);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    procedure_designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    argument_list = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    across_qm = CAR(gensymed_symbol_2);
    argument_count = length(argument_list);
    desired_value_count = (SI_Long)0L;
    argument_stack_nodes = Nil;
    stable_procedure_qm = Nil;
    stable_arg_types_qm = Nil;
    recorded_procedure_call_free_reference_qm = Nil;
    compiled_procedure = compile_stack_expression(procedure_designation,
	    maybe_add_unknown(across_qm ? list_constant : list_constant_1,
	    unknown_allowed_qm));
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = phrase_cons(generate_new_variable_spot(1,across_qm ? 
		list_constant : list_constant_1),Nil);
	ab_loop_repeat_ = IFIX(argument_count);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,
		Qitem_or_datum),Nil);
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
	block_of_variables_qm = nconc2(temp,temp_1);
    }
    else
	block_of_variables_qm = Nil;
    if (IFIX(argument_count) > (SI_Long)255L)
	compiler_error(2,string_constant_26,argument_count);
    if (desired_value_count > (SI_Long)255L)
	compiler_error(2,string_constant_27,FIX(desired_value_count));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp_2) {
	if (indirectly_denoted_item_p(compiled_procedure)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp_3 = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_contains_indirect_procedure_call_mask);
	    SVREF(temp_3,FIX((SI_Long)29L)) = svref_new_value;
	}
	if ( !TRUEP(dependent_compilation_p(0))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp_3 = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_call_without_validated_environment_mask);
	    SVREF(temp_3,FIX((SI_Long)29L)) = svref_new_value;
	}
    }
    if (dependent_compilation_p(0)) {
	stable_procedure_qm = stable_denoted_procedure_p(1,compiled_procedure);
	if (stable_procedure_qm) {
	    stable_arg_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)24L));
	    if (FIXNUM_NE(length(stable_arg_types_qm),argument_count)) {
		compiler_dependence_warning(2,string_constant,
			procedure_designation);
		stable_arg_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else {
		recorded_procedure_call_free_reference_qm = T;
		record_free_reference(across_qm ? 
			Qstable_remote_procedure_call : 
			Qstable_procedure_call,
			phrase_list_3(procedure_designation,
			stable_arg_types_qm,Nil));
	    }
	}
    }
    if ( !TRUEP(across_qm)) {
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)66L),
		unknown_allowed_qm));
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)9L));
	gensymed_symbol_6 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_6) = Qcall_prolog;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = block_of_variables_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = FIX(desired_value_count);
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = unknown_allowed_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = stable_procedure_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	argument = Nil;
	ab_loop_list_ = argument_list;
	type_cons_qm = stable_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp = argument;
	temp_1 = CAR(type_cons_qm);
	if (temp_1);
	else
	    temp_1 = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp,
		maybe_add_unknown(temp_1,unknown_allowed_qm)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	argument_stack_nodes = ab_loopvar_;
	goto end_2;
	argument_stack_nodes = Qnil;
      end_2:;
	M_CAR(gensymed_symbol_6) = argument_stack_nodes;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = Nil;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)66L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(stable_procedure_qm ? Qcall_dependent_epilog 
		: Qcall_epilog,block_of_variables_qm,argument_count));
    }
    else {
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_3(Qbegin_activity,FIX((SI_Long)67L),
		unknown_allowed_qm));
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)9L));
	gensymed_symbol_6 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_6) = Qcall_prolog;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = block_of_variables_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = FIX(desired_value_count);
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = unknown_allowed_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = stable_procedure_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	argument = Nil;
	ab_loop_list_ = argument_list;
	type_cons_qm = stable_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp = argument;
	temp_1 = CAR(type_cons_qm);
	if (temp_1);
	else
	    temp_1 = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp,
		maybe_add_unknown(temp_1,unknown_allowed_qm)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_2;
      end_loop_2:
	argument_stack_nodes = ab_loopvar_;
	goto end_3;
	argument_stack_nodes = Qnil;
      end_3:;
	M_CAR(gensymed_symbol_6) = argument_stack_nodes;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp_3 = compile_stack_expression(across_qm,
		maybe_add_unknown(list_constant_4,unknown_allowed_qm));
	M_CAR(gensymed_symbol_6) = temp_3;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	if (unknown_allowed_qm)
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbegin_activity,FIX((SI_Long)67L)));
	emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(stable_procedure_qm ? 
		Qcall_dependent_rpc_epilog : Qcall_rpc_epilog,
		block_of_variables_qm,argument_count));
    }
    if ( !TRUEP(recorded_procedure_call_free_reference_qm) && 
	    SYMBOLP(procedure_designation) &&  
	    !TRUEP(indirectly_denoted_item_p(compiled_procedure))) {
	argument_node = Nil;
	ab_loop_list_ = argument_stack_nodes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(type_specification_minus_type(type_specification_minus_type(ISVREF(argument_node,
		(SI_Long)6L),list_constant_5),list_constant_6),Nil);
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
	record_free_reference(across_qm ? Qremote_procedure_call : 
		Qprocedure_call,phrase_list_3(procedure_designation,temp_1,
		Nil));
    }
    temp_1 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* CALL-PROLOG-PSEUDO-EMITTER */
Object call_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, argument_count, var_spot_block_qm, procedure;
    Object unknown_allowed_qm, stable_procedure_qm, arguments, across_qm;
    Object argument, ab_loop_list_;

    x_note_fn_call(211,203);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    argument_count = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    procedure = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    stable_procedure_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    across_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(stable_procedure_qm))
	emit_funcall_instruction_byte_codes(4,byte_code_stream,
		unknown_allowed_qm ? 
		Qprepare_possibly_unknown_procedure_arguments : 
		Qprepare_procedure_arguments,FIXNUM_ADD1(argument_count),
		FIXNUM_ADD1(argument_count));
    if (across_qm)
	emit_stack_node_tree(byte_code_stream,across_qm);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-COMMON-CALL-EPILOG-BYTES */
Object emit_common_call_epilog_bytes(byte_code_stream,instruction,call_type)
    Object byte_code_stream, instruction, call_type;
{
    Object var_spot_block_qm, arg_count, var_spot_cons, var_spot;

    x_note_fn_call(211,204);
    var_spot_block_qm = SECOND(instruction);
    arg_count = THIRD(instruction);
    var_spot_cons = var_spot_block_qm;
    var_spot = Nil;
  next_loop:
    var_spot = FIRST(var_spot_cons);
    if ( !TRUEP(var_spot_cons))
	goto end_loop;
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    var_spot_cons = CDR(var_spot_cons);
    goto next_loop;
  end_loop:
    write_byte_code_to_stream(byte_code_stream,
	    op_code_for_stack_instruction(call_type));
    write_byte_code_to_stream(byte_code_stream,arg_count);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
    return VALUES_1(Qnil);
}

static Object Qcall;               /* call */

/* CALL-EPILOG-PSEUDO-EMITTER */
Object call_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,205);
    emit_common_call_epilog_bytes(byte_code_stream,instruction,Qcall);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qdependent_call;     /* dependent-call */

/* CALL-DEPENDENT-EPILOG-PSEUDO-EMITTER */
Object call_dependent_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,206);
    emit_common_call_epilog_bytes(byte_code_stream,instruction,
	    Qdependent_call);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcall_rpc;           /* call-rpc */

/* CALL-RPC-EPILOG-PSEUDO-EMITTER */
Object call_rpc_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,207);
    emit_common_call_epilog_bytes(byte_code_stream,instruction,Qcall_rpc);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_28;  /* "Because of a return value count mismatch for ~ND, a call to ~
				    *                 it could not be optimized."
				    */

static Object Qcall_assignment_prolog;  /* call-assignment-prolog */

static Object Qcall_assignment_dependent_epilog;  /* call-assignment-dependent-epilog */

static Object Qcall_assignment_epilog;  /* call-assignment-epilog */

static Object Qreceive_values;     /* receive-values */

static Object Qcall_assignment_dependent_rpc_epilog;  /* call-assignment-dependent-rpc-epilog */

static Object Qcall_assignment_rpc_epilog;  /* call-assignment-rpc-epilog */

/* CALL-ASSIGNMENT-ACTION-ACTION-COMPILER */
Object call_assignment_action_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, local_names;
    Object designation, argument_list, across_qm, argument_count, return_spots;
    Object return_types, argument_stack_nodes, desired_return_types;
    Object stable_procedure_qm, stable_proc_arg_types_qm;
    Object stable_proc_return_types_qm;
    Object recorded_procedure_call_free_reference_qm;
    Object compiled_procedure_or_rpd, compiler_error_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, block_of_variables_qm, temp_1;
    Object temp_2, svref_new_value, var_spot, description, type, local_name;
    Object ab_loop_list_, sub_class_bit_vector, stable_type, desired_type_cons;
    Object ab_loop_iter_flag_, gensymed_symbol_6, argument, type_cons_qm;
    SI_Long ab_loop_repeat_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Object result;

    x_note_fn_call(211,208);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    Call_statement_processed_qm = T;
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_names = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    argument_list = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    across_qm = CAR(gensymed_symbol_2);
    argument_count = length(argument_list);
    return_spots = Nil;
    return_types = Nil;
    argument_stack_nodes = Nil;
    desired_return_types = Nil;
    stable_procedure_qm = Nil;
    stable_proc_arg_types_qm = Nil;
    stable_proc_return_types_qm = Nil;
    recorded_procedure_call_free_reference_qm = Nil;
    compiled_procedure_or_rpd =  !TRUEP(across_qm) ? 
	    compile_procedure_expression(2,designation,list_constant_1) : 
	    compile_procedure_expression(2,designation,list_constant);
    compiler_error_qm = Nil;
    if ( !TRUEP(leave_on_stack_qm)) {
	ab_loop_repeat_ = IFIX(argument_count);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,
		Qitem_or_datum),Nil);
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
	block_of_variables_qm = temp;
    }
    else
	block_of_variables_qm = Nil;
    temp_1 = CAR(Lexically_visible_code_bodies);
    temp_2 = ISVREF(CAR(Lexically_visible_code_bodies),(SI_Long)2L);
    temp = length(local_names);
    svref_new_value = FIXNUM_MAX(temp_2,temp);
    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    var_spot = Nil;
    description = Nil;
    type = Nil;
    local_name = Nil;
    ab_loop_list_ = local_names;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    local_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = variable_spot_and_description_for_local_name(local_name);
    MVS_2(result,var_spot,description);
    type = getfq_function_no_default(CDR(description),Ktype);
    if ( !TRUEP(var_spot)) {
	procedure_compiler_missing_local_name_error(local_name);
	compiler_error_qm = T;
    }
    return_spots = phrase_cons(var_spot,return_spots);
    return_types = phrase_cons(type,return_types);
    goto next_loop_1;
  end_loop_1:;
    return_spots = nreverse(return_spots);
    return_types = nreverse(return_types);
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_4 = (SI_Long)1L;
	gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	temp_3 = (SI_Long)0L < gensymed_symbol_3;
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	if (indirectly_denoted_item_p(compiled_procedure_or_rpd)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp_1 = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_contains_indirect_procedure_call_mask);
	    SVREF(temp_1,FIX((SI_Long)29L)) = svref_new_value;
	}
	if ( !TRUEP(dependent_compilation_p(0))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp_1 = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_call_without_validated_environment_mask);
	    SVREF(temp_1,FIX((SI_Long)29L)) = svref_new_value;
	}
    }
    if ( !TRUEP(compiler_error_qm) && dependent_compilation_p(0)) {
	stable_procedure_qm = stable_denoted_procedure_p(1,
		compiled_procedure_or_rpd);
	sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	    temp_3 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    if (T) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(Current_computation_frame,
			    Qprocedure_flags);
		temp_1 = Current_computation_frame;
		svref_new_value = 
			FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
			(SI_Long)29L),
			Procedure_call_without_validated_environment_mask);
		SVREF(temp_1,FIX((SI_Long)29L)) = svref_new_value;
	    }
	}
	if (stable_procedure_qm) {
	    stable_proc_arg_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)24L));
	    stable_proc_return_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)25L));
	    if (FIXNUM_NE(length(stable_proc_arg_types_qm),
		    length(argument_list))) {
		compiler_dependence_warning(2,string_constant,designation);
		stable_proc_arg_types_qm = Nil;
		stable_proc_return_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else if (FIXNUM_LT(length(return_types),length(local_names))) {
		compiler_dependence_warning(2,string_constant_28,designation);
		stable_proc_arg_types_qm = Nil;
		stable_proc_return_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else {
		recorded_procedure_call_free_reference_qm = T;
		record_free_reference(across_qm ? 
			Qstable_remote_procedure_call : 
			Qstable_procedure_call,phrase_list_3(designation,
			stable_proc_arg_types_qm,stable_proc_return_types_qm));
	    }
	}
    }
    if (stable_proc_return_types_qm) {
	desired_return_types = copy_list_using_phrase_conses(return_types);
	stable_type = Nil;
	ab_loop_list_ = stable_proc_return_types_qm;
	desired_type_cons = desired_return_types;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	stable_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    desired_type_cons = M_CDR(desired_type_cons);
	if ( !TRUEP(desired_type_cons))
	    goto end_loop_2;
	if (type_specification_subtype_p(stable_type,M_CAR(desired_type_cons)))
	    M_CAR(desired_type_cons) = Nil;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_2;
      end_loop_2:;
    }
    else
	desired_return_types = return_types;
    if ( !TRUEP(across_qm)) {
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)10L));
	gensymed_symbol_6 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_6) = Qcall_assignment_prolog;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = block_of_variables_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure_or_rpd;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp_1 = length(local_names);
	M_CAR(gensymed_symbol_6) = temp_1;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = local_names;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = T;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = stable_procedure_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	argument = Nil;
	ab_loop_list_ = argument_list;
	type_cons_qm = stable_proc_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp_2 = argument;
	temp = CAR(type_cons_qm);
	if (temp);
	else
	    temp = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp_2,
		maybe_add_unknown(temp,unknown_allowed_qm)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_3;
      end_loop_3:
	argument_stack_nodes = ab_loopvar_;
	goto end_2;
	argument_stack_nodes = Qnil;
      end_2:;
	M_CAR(gensymed_symbol_6) = argument_stack_nodes;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = Nil;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_6 = gensymed_symbol_2;
	temp_1 = stable_procedure_qm ? Qcall_assignment_dependent_epilog : 
		Qcall_assignment_epilog;
	M_CAR(gensymed_symbol_6) = temp_1;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure_or_rpd;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = local_names;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = return_spots;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = desired_return_types;
	emit_already_consed_instruction_to_stream(epilog_stream,
		gensymed_symbol_2);
	temp = emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(Qreceive_values,return_spots,return_types));
    }
    else {
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)10L));
	gensymed_symbol_6 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_6) = Qcall_assignment_prolog;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = block_of_variables_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure_or_rpd;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp_1 = length(local_names);
	M_CAR(gensymed_symbol_6) = temp_1;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = local_names;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = T;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = stable_procedure_qm;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	argument = Nil;
	ab_loop_list_ = argument_list;
	type_cons_qm = stable_proc_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp_2 = argument;
	temp = CAR(type_cons_qm);
	if (temp);
	else
	    temp = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp_2,
		maybe_add_unknown(temp,unknown_allowed_qm)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_4;
      end_loop_4:
	argument_stack_nodes = ab_loopvar_;
	goto end_3;
	argument_stack_nodes = Qnil;
      end_3:;
	M_CAR(gensymed_symbol_6) = argument_stack_nodes;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp_1 = compile_stack_expression(across_qm,
		maybe_add_unknown(list_constant_4,unknown_allowed_qm));
	M_CAR(gensymed_symbol_6) = temp_1;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol_2);
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_6 = gensymed_symbol_2;
	temp_1 = stable_procedure_qm ? 
		Qcall_assignment_dependent_rpc_epilog : 
		Qcall_assignment_rpc_epilog;
	M_CAR(gensymed_symbol_6) = temp_1;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = argument_count;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure_or_rpd;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = local_names;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = return_spots;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = desired_return_types;
	emit_already_consed_instruction_to_stream(epilog_stream,
		gensymed_symbol_2);
	temp = emit_already_consed_instruction_to_stream(epilog_stream,
		phrase_list_3(Qreceive_values,return_spots,return_types));
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CALL-ASSIGNMENT-PROLOG-PSEUDO-EMITTER */
Object call_assignment_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, argument_count, var_spot_block_qm, procedure;
    Object unknown_allowed_qm, stable_procedure_qm, arguments, across_qm;
    Object argument, ab_loop_list_;

    x_note_fn_call(211,209);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    argument_count = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    procedure = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    stable_procedure_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    across_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(stable_procedure_qm))
	emit_funcall_instruction_byte_codes(4,byte_code_stream,
		unknown_allowed_qm ? 
		Qprepare_possibly_unknown_procedure_arguments : 
		Qprepare_procedure_arguments,FIXNUM_ADD1(argument_count),
		FIXNUM_ADD1(argument_count));
    if (across_qm)
	emit_stack_node_tree(byte_code_stream,across_qm);
    if (var_spot_block_qm)
	emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-COMMON-CALL-ASSIGNMENT-EPILOG-BYTES */
Object emit_common_call_assignment_epilog_bytes(byte_code_stream,
	    instruction,call_type)
    Object byte_code_stream, instruction, call_type;
{
    Object gensymed_symbol, argument_count, local_names;

    x_note_fn_call(211,210);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    argument_count = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_names = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    write_byte_code_to_stream(byte_code_stream,
	    op_code_for_stack_instruction(call_type));
    write_byte_code_to_stream(byte_code_stream,argument_count);
    return write_byte_code_to_stream(byte_code_stream,length(local_names));
}

/* CALL-ASSIGNMENT-EPILOG-PSEUDO-EMITTER */
Object call_assignment_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,211);
    emit_common_call_assignment_epilog_bytes(byte_code_stream,instruction,
	    Qcall);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-ASSIGNMENT-RPC-EPILOG-PSEUDO-EMITTER */
Object call_assignment_rpc_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,212);
    emit_common_call_assignment_epilog_bytes(byte_code_stream,instruction,
	    Qcall_rpc);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-ASSIGNMENT-DEPENDENT-EPILOG-PSEUDO-EMITTER */
Object call_assignment_dependent_epilog_pseudo_emitter(byte_code_stream,
	    instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,213);
    emit_common_call_assignment_epilog_bytes(byte_code_stream,instruction,
	    Qdependent_call);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_80;   /* # */

/* PRINT-START-KB-INSTRUCTION */
Object print_start_kb_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,214);
    return twrite_beginning_of_wide_string(array_constant_80,
	    FIX((SI_Long)20L));
}

static Object Qstart_kb_prolog;    /* start-kb-prolog */

static Object Qstart_kb_epilog;    /* start-kb-epilog */

/* START-KB-ACTION-COMPILER */
Object start_kb_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(211,215);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_cons(Qstart_kb_prolog,Nil));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qbegin_activity,FIX((SI_Long)62L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_cons(Qstart_kb_epilog,Nil));
    temp = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* START-KB-PROLOG-PSEUDO-EMITTER */
Object start_kb_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,216);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstart_kb;           /* start-kb */

/* START-KB-EPILOG-PSEUDO-EMITTER */
Object start_kb_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,217);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qstart_kb);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_81;   /* # */

/* PRINT-RESUME-KB-INSTRUCTION */
Object print_resume_kb_instruction(instruction)
    Object instruction;
{
    x_note_fn_call(211,218);
    return twrite_beginning_of_wide_string(array_constant_81,
	    FIX((SI_Long)21L));
}

static Object Qresume_kb_epilog;   /* resume-kb-epilog */

/* RESUME-KB-ACTION-COMPILER */
Object resume_kb_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(211,219);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_cons(Qstart_kb_prolog,Nil));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qbegin_activity,FIX((SI_Long)63L)));
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_cons(Qresume_kb_epilog,Nil));
    temp = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* RESUME-KB-PROLOG-PSEUDO-EMITTER */
Object resume_kb_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,220);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qresume_kb;          /* resume-kb */

/* RESUME-KB-EPILOG-PSEUDO-EMITTER */
Object resume_kb_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,221);
    emit_funcall_instruction_byte_codes(2,byte_code_stream,Qresume_kb);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-ACTION-START-THREAD-BYTES */
Object emit_action_start_thread_bytes(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object gensymed_symbol, procedure, arguments, unknown_allowed_qm;
    Object var_spot_block_qm, stable_procedure_qm, argument, ab_loop_list_;
    Object args_plus_1;

    x_note_fn_call(211,222);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    procedure = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arguments = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    unknown_allowed_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    var_spot_block_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    stable_procedure_qm = CAR(gensymed_symbol);
    emit_stack_node_tree(byte_code_stream,procedure);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(stable_procedure_qm)) {
	args_plus_1 = add1(length(arguments));
	emit_funcall_instruction_byte_codes(4,byte_code_stream,
		unknown_allowed_qm ? 
		Qprepare_possibly_unknown_procedure_arguments : 
		Qprepare_procedure_arguments,args_plus_1,args_plus_1);
    }
    emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)2L));
    if (var_spot_block_qm)
	return emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
		CAR(var_spot_block_qm),length(var_spot_block_qm));
    else
	return VALUES_1(Nil);
}

/* START-THREAD-PROLOG-PSEUDO-EMITTER */
Object start_thread_prolog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    x_note_fn_call(211,223);
    emit_action_start_thread_bytes(byte_code_stream,instruction);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstart_thread;       /* start-thread */

/* START-THREAD-EPILOG-PSEUDO-EMITTER */
Object start_thread_epilog_pseudo_emitter(byte_code_stream,instruction)
    Object byte_code_stream, instruction;
{
    Object var_spot_block_qm, var_spot, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long args_remaining;

    x_note_fn_call(211,224);
    var_spot_block_qm = SECOND(instruction);
    if (var_spot_block_qm &&  !FIXNUMP(var_spot_block_qm)) {
	var_spot = Nil;
	ab_loop_list_ = var_spot_block_qm;
	args_remaining = IFIX(FIXNUM_SUB1(length(var_spot_block_qm)));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    args_remaining = args_remaining - (SI_Long)1L;
	if (args_remaining < (SI_Long)0L)
	    goto end_loop;
	if (args_remaining == (SI_Long)1L || args_remaining == (SI_Long)0L)
	    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	else
	    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    emit_funcall_instruction_byte_codes(4,byte_code_stream,Qstart_thread,
	    FIXNUMP(var_spot_block_qm) ? var_spot_block_qm : 
	    length(var_spot_block_qm),FIX((SI_Long)0L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstart_thread_prolog;  /* start-thread-prolog */

static Object Qstart_thread_epilog;  /* start-thread-epilog */

/* START-THREAD-ACTION-COMPILER */
Object start_thread_action_compiler(statement,unknown_allowed_qm,
	    leave_on_stack_qm,prolog_stream,epilog_stream)
    Object statement, unknown_allowed_qm, leave_on_stack_qm, prolog_stream;
    Object epilog_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, designation;
    Object argument_expressions, argument_count, argument_stack_nodes;
    Object stable_procedure_qm, stable_arg_types_qm;
    Object recorded_procedure_call_free_reference_qm;
    Object compiled_procedure_or_rpd, temp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1, temp_2, block_of_variables_qm;
    Object gensymed_symbol_3, argument, ab_loop_list_, type_cons_qm;
    Object ab_loop_iter_flag_, argument_node;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(211,225);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    argument_expressions = CAR(gensymed_symbol_2);
    argument_count = length(argument_expressions);
    argument_stack_nodes = Nil;
    stable_procedure_qm = Nil;
    stable_arg_types_qm = Nil;
    recorded_procedure_call_free_reference_qm = Nil;
    compiled_procedure_or_rpd = compile_stack_expression(designation,
	    maybe_add_unknown(list_constant_1,unknown_allowed_qm));
    if ( !TRUEP(leave_on_stack_qm)) {
	temp = phrase_cons(generate_new_variable_spot(1,list_constant_1),Nil);
	ab_loop_repeat_ = IFIX(argument_count);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = phrase_cons(generate_new_variable_spot(1,
		Qitem_or_datum),Nil);
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
	temp_2 = generate_new_variable_spot(1,list_constant_2);
	block_of_variables_qm = nconc2(temp,nconc2(temp_1,
		phrase_list_2(temp_2,generate_new_variable_spot(1,
		list_constant_3))));
    }
    else
	block_of_variables_qm = Nil;
    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = Qstart_thread_prolog;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = compiled_procedure_or_rpd;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    argument = Nil;
    ab_loop_list_ = argument_expressions;
    type_cons_qm = stable_arg_types_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	type_cons_qm = CDR(type_cons_qm);
    temp = argument;
    temp_2 = CAR(type_cons_qm);
    if (temp_2);
    else
	temp_2 = Qitem_or_datum;
    ab_loopvar__2 = phrase_cons(compile_stack_expression(temp,
	    maybe_add_unknown(temp_2,unknown_allowed_qm)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    argument_stack_nodes = ab_loopvar_;
    goto end_2;
    argument_stack_nodes = Qnil;
  end_2:;
    M_CAR(gensymed_symbol_3) = argument_stack_nodes;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = unknown_allowed_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = block_of_variables_qm;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = stable_procedure_qm;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol_2);
    temp_2 = block_of_variables_qm;
    if (temp_2);
    else
	temp_2 = FIX(IFIX(length(argument_expressions)) + (SI_Long)3L);
    emit_already_consed_instruction_to_stream(epilog_stream,
	    phrase_list_2(Qstart_thread_epilog,temp_2));
    if ( !TRUEP(recorded_procedure_call_free_reference_qm) && 
	    SYMBOLP(designation) &&  
	    !TRUEP(indirectly_denoted_item_p(compiled_procedure_or_rpd))) {
	argument_node = Nil;
	ab_loop_list_ = argument_stack_nodes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(type_specification_minus_type(type_specification_minus_type(ISVREF(argument_node,
		(SI_Long)6L),list_constant_5),list_constant_6),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	temp_2 = ab_loopvar_;
	goto end_3;
	temp_2 = Qnil;
      end_3:;
	record_free_reference(Qprocedure_call,phrase_list_3(designation,
		temp_2,Nil));
    }
    temp_2 = block_of_variables_qm;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

void proc_inst_INIT()
{
    Object start_action_compiler_1, start_prolog_pseudo_emitter_1;
    Object start_rpc_prolog_pseudo_emitter_1, start_epilog_pseudo_emitter_1;
    Object start_rpc_epilog_pseudo_emitter_1, conclude_action_compiler_1;
    Object conclude_not_action_compiler_1, conclude_prolog_pseudo_emitter_1;
    Object compare_and_swap_prolog_pseudo_emitter_1;
    Object conclude_epilog_pseudo_emitter_1;
    Object compare_and_swap_epilog_pseudo_emitter_1;
    Object conclude_attribute_prolog_pseudo_emitter_1;
    Object conclude_attribute_epilog_pseudo_emitter_1, move_action_compiler_1;
    Object move_prolog_pseudo_emitter_1, move_epilog_pseudo_emitter_1;
    Object set_position_action_compiler_1;
    Object set_position_prolog_pseudo_emitter_1;
    Object set_position_epilog_pseudo_emitter_1, rotate_action_compiler_1;
    Object rotate_prolog_pseudo_emitter_1, rotate_epilog_pseudo_emitter_1;
    Object set_heading_action_compiler_1, set_heading_prolog_pseudo_emitter_1;
    Object set_heading_epilog_pseudo_emitter_1;
    Object conclude_has_no_current_value_action_compiler_1;
    Object conclude_has_no_current_value_prolog_pseudo_emitter_1;
    Object conclude_has_no_current_value_epilog_pseudo_emitter_1;
    Object conclude_has_no_value_action_compiler_1;
    Object conclude_has_no_value_prolog_pseudo_emitter_1;
    Object conclude_has_no_value_epilog_pseudo_emitter_1;
    Object focus_action_compiler_1, focus_prolog_pseudo_emitter_1;
    Object focus_epilog_pseudo_emitter_1, invoke_action_compiler_1;
    Object invoke_prolog_pseudo_emitter_1, invoke_epilog_pseudo_emitter_1;
    Object change_item_color_action_compiler_1;
    Object change_item_color_prolog_pseudo_emitter_1;
    Object change_item_color_epilog_pseudo_emitter_1;
    Object change_item_color_pattern_action_compiler_1;
    Object change_item_color_pattern_prolog_pseudo_emitter_1;
    Object change_item_color_pattern_epilog_pseudo_emitter_1;
    Object show_action_compiler_1, show_prolog_pseudo_emitter_1;
    Object show_epilog_pseudo_emitter_1, show_new_action_compiler_1;
    Object show_new_pseudo_emitter_1, show_new_prolog_pseudo_emitter_1;
    Object show_new_epilog_pseudo_emitter_1, hide_action_compiler_1;
    Object hide_prolog_pseudo_emitter_1, hide_epilog_pseudo_emitter_1;
    Object activate_action_compiler_1, activate_prolog_pseudo_emitter_1;
    Object activate_epilog_pseudo_emitter_1, deactivate_action_compiler_1;
    Object deactivate_prolog_pseudo_emitter_1;
    Object deactivate_epilog_pseudo_emitter_1, halt_action_compiler_1;
    Object halt_prolog_pseudo_emitter_1, halt_epilog_pseudo_emitter_1;
    Object set_action_compiler_1, set_prolog_pseudo_emitter_1;
    Object set_epilog_pseudo_emitter_1, inform_action_compiler_1;
    Object inform_prolog_pseudo_emitter_1, inform_epilog_pseudo_emitter_1;
    Object add_relation_action_compiler_1;
    Object add_relation_prolog_pseudo_emitter_1;
    Object add_relation_epilog_pseudo_emitter_1;
    Object remove_relation_action_compiler_1;
    Object remove_relation_prolog_pseudo_emitter_1;
    Object remove_relation_epilog_pseudo_emitter_1, create_action_compiler_1;
    Object create_prolog_pseudo_emitter_1, create_epilog_pseudo_emitter_1;
    Object create_pseudo_emitter_1, delete_action_compiler_1;
    Object delete_prolog_pseudo_emitter_1, delete_epilog_pseudo_emitter_1;
    Object transfer_action_compiler_1, transfer_prolog_pseudo_emitter_1;
    Object transfer_epilog_pseudo_emitter_1;
    Object change_system_attribute_action_compiler_1;
    Object change_system_attribute_prolog_pseudo_emitter_1;
    Object change_system_attribute_epilog_pseudo_emitter_1;
    Object change_the_text_of_attribute_action_compiler_1;
    Object change_the_text_of_attribute_prolog_pseudo_emitter_1;
    Object change_the_text_of_attribute_epilog_pseudo_emitter_1;
    Object change_nth_element_action_compiler_1;
    Object change_nth_element_to_no_value_action_compiler_1;
    Object change_nth_element_prolog_pseudo_emitter_1;
    Object change_nth_element_epilog_pseudo_emitter_1;
    Object change_nth_element_to_no_value_prolog_pseudo_emitter_1;
    Object change_nth_element_to_no_value_epilog_pseudo_emitter_1;
    Object g2_list_insert_action_compiler_1;
    Object g2_list_insert_prolog_pseudo_emitter_1;
    Object g2_list_insert_epilog_pseudo_emitter_1;
    Object g2_list_remove_action_compiler_1;
    Object g2_list_remove_prolog_pseudo_emitter_1;
    Object g2_list_remove_epilog_pseudo_emitter_1;
    Object nupec_synchronize_action_compiler_1;
    Object nupec_synchronize_prolog_pseudo_emitter_1;
    Object nupec_synchronize_epilog_pseudo_emitter_1;
    Object create_explanation_action_compiler_1;
    Object create_explanation_prolog_pseudo_emitter_1;
    Object create_explanation_epilog_pseudo_emitter_1;
    Object update_action_compiler_1, update_prolog_pseudo_emitter_1;
    Object update_epilog_pseudo_emitter_1, create_connection_action_compiler_1;
    Object create_connection_prolog_pseudo_emitter_1;
    Object create_connection_epilog_pseudo_emitter_1, abort_action_compiler_1;
    Object abort_prolog_pseudo_emitter_1, abort_epilog_pseudo_emitter_1;
    Object shut_down_g2_action_compiler_1;
    Object shut_down_g2_prolog_pseudo_emitter_1;
    Object shut_down_g2_epilog_pseudo_emitter_1, reset_kb_action_compiler_1;
    Object reset_kb_prolog_pseudo_emitter_1, reset_kb_epilog_pseudo_emitter_1;
    Object pause_kb_action_compiler_1, pause_kb_prolog_pseudo_emitter_1;
    Object pause_kb_epilog_pseudo_emitter_1;
    Object create_by_cloning_action_compiler_1;
    Object create_by_cloning_prolog_pseudo_emitter_1;
    Object create_by_cloning_epilog_pseudo_emitter_1;
    Object make_permanent_action_compiler_1;
    Object make_permanent_prolog_pseudo_emitter_1;
    Object make_permanent_epilog_pseudo_emitter_1;
    Object make_transient_action_compiler_1;
    Object make_transient_prolog_pseudo_emitter_1;
    Object make_transient_epilog_pseudo_emitter_1;
    Object make_subworkspace_action_compiler_1;
    Object make_subworkspace_prolog_pseudo_emitter_1;
    Object make_subworkspace_epilog_pseudo_emitter_1, print_action_compiler_1;
    Object print_prolog_pseudo_emitter_1, print_epilog_pseudo_emitter_1;
    Object call_action_action_compiler_1, call_prolog_pseudo_emitter_1;
    Object call_epilog_pseudo_emitter_1;
    Object call_dependent_epilog_pseudo_emitter_1;
    Object call_rpc_epilog_pseudo_emitter_1;
    Object call_assignment_action_action_compiler_1;
    Object call_assignment_prolog_pseudo_emitter_1;
    Object call_assignment_epilog_pseudo_emitter_1;
    Object call_assignment_rpc_epilog_pseudo_emitter_1;
    Object call_assignment_dependent_epilog_pseudo_emitter_1;
    Object start_kb_action_compiler_1, start_kb_prolog_pseudo_emitter_1;
    Object start_kb_epilog_pseudo_emitter_1, resume_kb_action_compiler_1;
    Object resume_kb_prolog_pseudo_emitter_1;
    Object resume_kb_epilog_pseudo_emitter_1;
    Object start_thread_prolog_pseudo_emitter_1;
    Object start_thread_epilog_pseudo_emitter_1;
    Object start_thread_action_compiler_1;
    Object Qaction_compiler, Qpseudo_instruction_byte_code_emitter, AB_package;
    Object Qresume_kb_prolog, Qprocedure_statement_writer;
    Object Qprint_pause_kb_instruction, list_constant_24;
    Object Qcall_assignment_action, Qprint_call_assignment_instruction;
    Object Qprint_call_instruction, Qprint_print_instruction;
    Object Qprint_make_subworkspace_instruction;
    Object Qprint_make_transient_instruction;
    Object Qprint_make_permanent_instruction;
    Object Qprint_create_by_cloning_statement, Qpause_kb, Qreset_kb;
    Object Qprint_reset_kb_instruction, Qprint_shut_down_g2_instruction;
    Object list_constant_30, Qab_or, Qprocedure_invocation, Qab_class;
    Object Qprint_abort_instruction, Qquantity_list, Qcreate_connection;
    Object Qprint_create_connection_statement, Qprint_update_instruction;
    Object Qprint_create_explanation_statement, Qnupec_synchronize;
    Object Qprint_nupec_synchronize_instruction;
    Object Qprint_g2_list_remove_instruction, Qafter_element, Qbefore_element;
    Object Qprint_g2_list_insert_instruction, Qfloat_array, Qinteger_array;
    Object Qchange_nth_element_to_no_value;
    Object Qprint_change_nth_element_to_no_value_instruction, list_constant_29;
    Object Qg2_list, Qg2_array, Qprint_change_nth_element_instruction;
    Object Qprint_change_the_text_of_instruction;
    Object Qprint_change_system_attribute_instruction, Qg2_window;
    Object Qprint_transfer_instruction, Qprint_delete_instruction;
    Object Qprint_create_instruction, Qprint_add_relation, list_constant_25;
    Object Qprint_inform_instruction, Qkb_workspace, Qvariable_or_parameter;
    Object Qprint_set_instruction, Qhalt, Qprint_halt_instruction;
    Object Qprint_deactivate_instruction, Qprint_activate_instruction;
    Object Qprint_hide_instruction, Qprint_show_new_instruction, Qshow;
    Object Qui_client_item, Qprint_show_instruction;
    Object Qprint_change_item_color_pattern_instruction;
    Object Qprint_change_item_color_instruction, Qprint_invoke_instruction;
    Object Qprint_focus_instruction, list_constant_28, list_constant_26;
    Object Qprint_conclude_has_no_value_instruction;
    Object Qprint_conclude_has_no_current_value_instruction;
    Object Qprint_set_heading_instruction, Qprint_rotate_instruction;
    Object Qprint_set_position_instruction, Qprint_move_instruction;
    Object Qconclude_not, Qwrite_conclude_that_statement, list_constant_27;
    Object Qplace_reference, Qno_item, Qunknown_datum, Qprocedure;
    Object Qremote_procedure_declaration, Qprint_start_instruction;

    x_note_fn_call(211,226);
    SET_PACKAGE("AB");
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    AB_package = STATIC_PACKAGE("AB");
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qprint_start_instruction = STATIC_SYMBOL("PRINT-START-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_start_instruction,
	    STATIC_FUNCTION(print_start_instruction,NIL,FALSE,1,1));
    Qprocedure_statement_writer = 
	    STATIC_SYMBOL("PROCEDURE-STATEMENT-WRITER",AB_package);
    mutate_global_property(Qstart,
	    SYMBOL_FUNCTION(Qprint_start_instruction),
	    Qprocedure_statement_writer);
    Qaction_compiler = STATIC_SYMBOL("ACTION-COMPILER",AB_package);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qremote_procedure_declaration);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_5 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant_25 = STATIC_CONS(list_constant_5,Qnil);
    list_constant_2 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_25);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_25);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    string_constant = 
	    STATIC_STRING("Because of an argument count mismatch for ~ND, a call to it ~\n                could not be optimized.");
    Qstable_remote_procedure_call = 
	    STATIC_SYMBOL("STABLE-REMOTE-PROCEDURE-CALL",AB_package);
    Qstable_procedure_call = STATIC_SYMBOL("STABLE-PROCEDURE-CALL",AB_package);
    Qbegin_activity = STATIC_SYMBOL("BEGIN-ACTIVITY",AB_package);
    Qstart_rpc_prolog = STATIC_SYMBOL("START-RPC-PROLOG",AB_package);
    Qstart_prolog = STATIC_SYMBOL("START-PROLOG",AB_package);
    Qstart_rpc_epilog = STATIC_SYMBOL("START-RPC-EPILOG",AB_package);
    Qstart_epilog = STATIC_SYMBOL("START-EPILOG",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_6 = STATIC_CONS(Qno_item,Qnil);
    Qremote_procedure_call = STATIC_SYMBOL("REMOTE-PROCEDURE-CALL",AB_package);
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    start_action_compiler_1 = STATIC_FUNCTION(start_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qstart,start_action_compiler_1,Qaction_compiler);
    Qprepare_possibly_unknown_procedure_arguments = 
	    STATIC_SYMBOL("PREPARE-POSSIBLY-UNKNOWN-PROCEDURE-ARGUMENTS",
	    AB_package);
    Qprepare_procedure_arguments = 
	    STATIC_SYMBOL("PREPARE-PROCEDURE-ARGUMENTS",AB_package);
    Qpseudo_instruction_byte_code_emitter = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-BYTE-CODE-EMITTER",AB_package);
    start_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_prolog,start_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    start_rpc_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_rpc_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_rpc_prolog,
	    start_rpc_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    start_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_epilog,start_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qstart_rpc = STATIC_SYMBOL("START-RPC",AB_package);
    start_rpc_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_rpc_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_rpc_epilog,
	    start_rpc_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    list_constant_26 = STATIC_CONS(Qplace_reference,Qnil);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_4,
	    list_constant_26);
    Qattribute_of_class = STATIC_SYMBOL("ATTRIBUTE-OF-CLASS",AB_package);
    Qclass_qualified_attribute_of_class = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS",AB_package);
    Qconclude_attribute_prolog = STATIC_SYMBOL("CONCLUDE-ATTRIBUTE-PROLOG",
	    AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qconclude_attribute_epilog = STATIC_SYMBOL("CONCLUDE-ATTRIBUTE-EPILOG",
	    AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant_1 = 
	    STATIC_STRING("In the conclude action, the local name ~a is declared to ~\n                        hold ~NT, not ~NT.");
    Qcompare_and_swap_prolog = STATIC_SYMBOL("COMPARE-AND-SWAP-PROLOG",
	    AB_package);
    Qcompare_and_swap_epilog = STATIC_SYMBOL("COMPARE-AND-SWAP-EPILOG",
	    AB_package);
    Qconclude_prolog = STATIC_SYMBOL("CONCLUDE-PROLOG",AB_package);
    Qconclude_epilog = STATIC_SYMBOL("CONCLUDE-EPILOG",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qwrite_conclude_that_statement = 
	    STATIC_SYMBOL("WRITE-CONCLUDE-THAT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_conclude_that_statement,
	    STATIC_FUNCTION(write_conclude_that_statement,NIL,FALSE,1,1));
    mutate_global_property(Qconclude,
	    SYMBOL_FUNCTION(Qwrite_conclude_that_statement),
	    Qprocedure_statement_writer);
    conclude_action_compiler_1 = STATIC_FUNCTION(conclude_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qconclude,conclude_action_compiler_1,
	    Qaction_compiler);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qnth_element,
	    Qclass_qualified_name,Qattribute_value);
    Deep_concludable_role_names = list_constant_27;
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    mutate_global_property(Qconclude_not,
	    SYMBOL_FUNCTION(Qwrite_conclude_that_statement),
	    Qprocedure_statement_writer);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    conclude_not_action_compiler_1 = 
	    STATIC_FUNCTION(conclude_not_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qconclude_not,conclude_not_action_compiler_1,
	    Qaction_compiler);
    conclude_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qconclude_prolog,
	    conclude_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    compare_and_swap_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(compare_and_swap_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcompare_and_swap_prolog,
	    compare_and_swap_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    conclude_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qconclude_epilog,
	    conclude_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcompare_and_swap = STATIC_SYMBOL("COMPARE-AND-SWAP",AB_package);
    compare_and_swap_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(compare_and_swap_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcompare_and_swap_epilog,
	    compare_and_swap_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    conclude_attribute_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_attribute_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qconclude_attribute_prolog,
	    conclude_attribute_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qconclude_attribute = STATIC_SYMBOL("CONCLUDE-ATTRIBUTE",AB_package);
    conclude_attribute_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_attribute_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qconclude_attribute_epilog,
	    conclude_attribute_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_9 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qprint_move_instruction = STATIC_SYMBOL("PRINT-MOVE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_move_instruction,
	    STATIC_FUNCTION(print_move_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qmove,SYMBOL_FUNCTION(Qprint_move_instruction),
	    Qprocedure_statement_writer);
    Qmove_prolog = STATIC_SYMBOL("MOVE-PROLOG",AB_package);
    Qmove_epilog = STATIC_SYMBOL("MOVE-EPILOG",AB_package);
    move_action_compiler_1 = STATIC_FUNCTION(move_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qmove,move_action_compiler_1,Qaction_compiler);
    move_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(move_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qmove_prolog,move_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    move_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(move_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qmove_epilog,move_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_11 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    Qset_position = STATIC_SYMBOL("SET-POSITION",AB_package);
    Qprint_set_position_instruction = 
	    STATIC_SYMBOL("PRINT-SET-POSITION-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_set_position_instruction,
	    STATIC_FUNCTION(print_set_position_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qset_position,
	    SYMBOL_FUNCTION(Qprint_set_position_instruction),
	    Qprocedure_statement_writer);
    Qset_position_prolog = STATIC_SYMBOL("SET-POSITION-PROLOG",AB_package);
    Qset_position_epilog = STATIC_SYMBOL("SET-POSITION-EPILOG",AB_package);
    set_position_action_compiler_1 = 
	    STATIC_FUNCTION(set_position_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qset_position,set_position_action_compiler_1,
	    Qaction_compiler);
    set_position_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_position_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_position_prolog,
	    set_position_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    set_position_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_position_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_position_epilog,
	    set_position_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_12 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Qrotate = STATIC_SYMBOL("ROTATE",AB_package);
    Qprint_rotate_instruction = STATIC_SYMBOL("PRINT-ROTATE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_rotate_instruction,
	    STATIC_FUNCTION(print_rotate_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qrotate,
	    SYMBOL_FUNCTION(Qprint_rotate_instruction),
	    Qprocedure_statement_writer);
    Qrotate_prolog = STATIC_SYMBOL("ROTATE-PROLOG",AB_package);
    Qrotate_epilog = STATIC_SYMBOL("ROTATE-EPILOG",AB_package);
    rotate_action_compiler_1 = STATIC_FUNCTION(rotate_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qrotate,rotate_action_compiler_1,Qaction_compiler);
    rotate_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(rotate_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qrotate_prolog,rotate_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    rotate_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(rotate_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qrotate_epilog,rotate_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_14 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)57344L);
    Qset_heading = STATIC_SYMBOL("SET-HEADING",AB_package);
    Qprint_set_heading_instruction = 
	    STATIC_SYMBOL("PRINT-SET-HEADING-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_set_heading_instruction,
	    STATIC_FUNCTION(print_set_heading_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qset_heading,
	    SYMBOL_FUNCTION(Qprint_set_heading_instruction),
	    Qprocedure_statement_writer);
    Qset_heading_prolog = STATIC_SYMBOL("SET-HEADING-PROLOG",AB_package);
    Qset_heading_epilog = STATIC_SYMBOL("SET-HEADING-EPILOG",AB_package);
    set_heading_action_compiler_1 = 
	    STATIC_FUNCTION(set_heading_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qset_heading,set_heading_action_compiler_1,
	    Qaction_compiler);
    set_heading_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_heading_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_heading_prolog,
	    set_heading_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    set_heading_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_heading_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_heading_epilog,
	    set_heading_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_15 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)57344L);
    Qconclude_has_no_current_value = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE",AB_package);
    Qprint_conclude_has_no_current_value_instruction = 
	    STATIC_SYMBOL("PRINT-CONCLUDE-HAS-NO-CURRENT-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_conclude_has_no_current_value_instruction,
	    STATIC_FUNCTION(print_conclude_has_no_current_value_instruction,
	    NIL,FALSE,1,1));
    mutate_global_property(Qconclude_has_no_current_value,
	    SYMBOL_FUNCTION(Qprint_conclude_has_no_current_value_instruction),
	    Qprocedure_statement_writer);
    Qconclude_has_no_current_value_prolog = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE-PROLOG",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qvariable);
    Qconclude_has_no_current_value_epilog = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE-EPILOG",AB_package);
    conclude_has_no_current_value_action_compiler_1 = 
	    STATIC_FUNCTION(conclude_has_no_current_value_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qconclude_has_no_current_value,
	    conclude_has_no_current_value_action_compiler_1,Qaction_compiler);
    conclude_has_no_current_value_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_has_no_current_value_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconclude_has_no_current_value_prolog,
	    conclude_has_no_current_value_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    conclude_has_no_current_value_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_has_no_current_value_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconclude_has_no_current_value_epilog,
	    conclude_has_no_current_value_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_17 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    Qconclude_has_no_value = STATIC_SYMBOL("CONCLUDE-HAS-NO-VALUE",AB_package);
    Qprint_conclude_has_no_value_instruction = 
	    STATIC_SYMBOL("PRINT-CONCLUDE-HAS-NO-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_conclude_has_no_value_instruction,
	    STATIC_FUNCTION(print_conclude_has_no_value_instruction,NIL,
	    FALSE,1,1));
    mutate_global_property(Qconclude_has_no_value,
	    SYMBOL_FUNCTION(Qprint_conclude_has_no_value_instruction),
	    Qprocedure_statement_writer);
    Qconclude_has_no_value_prolog = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-VALUE-PROLOG",AB_package);
    list_constant_28 = STATIC_CONS(list_constant_26,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_28);
    Qconclude_has_no_value_epilog = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-VALUE-EPILOG",AB_package);
    conclude_has_no_value_action_compiler_1 = 
	    STATIC_FUNCTION(conclude_has_no_value_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qconclude_has_no_value,
	    conclude_has_no_value_action_compiler_1,Qaction_compiler);
    conclude_has_no_value_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_has_no_value_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconclude_has_no_value_prolog,
	    conclude_has_no_value_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    conclude_has_no_value_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(conclude_has_no_value_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconclude_has_no_value_epilog,
	    conclude_has_no_value_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_18 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    Qfocus = STATIC_SYMBOL("FOCUS",AB_package);
    Qprint_focus_instruction = STATIC_SYMBOL("PRINT-FOCUS-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_focus_instruction,
	    STATIC_FUNCTION(print_focus_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qfocus,
	    SYMBOL_FUNCTION(Qprint_focus_instruction),
	    Qprocedure_statement_writer);
    Qfocus_prolog = STATIC_SYMBOL("FOCUS-PROLOG",AB_package);
    Qfocus_epilog = STATIC_SYMBOL("FOCUS-EPILOG",AB_package);
    focus_action_compiler_1 = STATIC_FUNCTION(focus_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qfocus,focus_action_compiler_1,Qaction_compiler);
    focus_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(focus_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qfocus_prolog,focus_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qfocus_with_wait = STATIC_SYMBOL("FOCUS-WITH-WAIT",AB_package);
    focus_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(focus_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qfocus_epilog,focus_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_20 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    Qinvoke = STATIC_SYMBOL("INVOKE",AB_package);
    Qprint_invoke_instruction = STATIC_SYMBOL("PRINT-INVOKE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_invoke_instruction,
	    STATIC_FUNCTION(print_invoke_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qinvoke,
	    SYMBOL_FUNCTION(Qprint_invoke_instruction),
	    Qprocedure_statement_writer);
    Qinvoke_prolog = STATIC_SYMBOL("INVOKE-PROLOG",AB_package);
    Qinvoke_epilog = STATIC_SYMBOL("INVOKE-EPILOG",AB_package);
    invoke_action_compiler_1 = STATIC_FUNCTION(invoke_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qinvoke,invoke_action_compiler_1,Qaction_compiler);
    invoke_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(invoke_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qinvoke_prolog,invoke_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qinvoke_with_wait = STATIC_SYMBOL("INVOKE-WITH-WAIT",AB_package);
    invoke_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(invoke_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qinvoke_epilog,invoke_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_22 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING(" ~(~a~) ");
    array_constant_23 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)18L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)19L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)57344L);
    string_constant_3 = STATIC_STRING(" ~(~a~)");
    Qchange_item_color = STATIC_SYMBOL("CHANGE-ITEM-COLOR",AB_package);
    Qprint_change_item_color_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-ITEM-COLOR-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_item_color_instruction,
	    STATIC_FUNCTION(print_change_item_color_instruction,NIL,FALSE,
	    1,1));
    mutate_global_property(Qchange_item_color,
	    SYMBOL_FUNCTION(Qprint_change_item_color_instruction),
	    Qprocedure_statement_writer);
    Qchange_item_color_prolog = STATIC_SYMBOL("CHANGE-ITEM-COLOR-PROLOG",
	    AB_package);
    Qchange_item_color_epilog = STATIC_SYMBOL("CHANGE-ITEM-COLOR-EPILOG",
	    AB_package);
    change_item_color_action_compiler_1 = 
	    STATIC_FUNCTION(change_item_color_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qchange_item_color,
	    change_item_color_action_compiler_1,Qaction_compiler);
    change_item_color_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_item_color_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qchange_item_color_prolog,
	    change_item_color_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_item_color_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_item_color_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qchange_item_color_epilog,
	    change_item_color_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_25 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)31L,(SI_Long)57344L);
    string_constant_4 = STATIC_STRING("~%    ");
    array_constant_26 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)57344L);
    Qchange_item_color_pattern = STATIC_SYMBOL("CHANGE-ITEM-COLOR-PATTERN",
	    AB_package);
    Qprint_change_item_color_pattern_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-ITEM-COLOR-PATTERN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_item_color_pattern_instruction,
	    STATIC_FUNCTION(print_change_item_color_pattern_instruction,
	    NIL,FALSE,1,1));
    mutate_global_property(Qchange_item_color_pattern,
	    SYMBOL_FUNCTION(Qprint_change_item_color_pattern_instruction),
	    Qprocedure_statement_writer);
    Qchange_item_color_pattern_prolog = 
	    STATIC_SYMBOL("CHANGE-ITEM-COLOR-PATTERN-PROLOG",AB_package);
    Qchange_item_color_pattern_epilog = 
	    STATIC_SYMBOL("CHANGE-ITEM-COLOR-PATTERN-EPILOG",AB_package);
    change_item_color_pattern_action_compiler_1 = 
	    STATIC_FUNCTION(change_item_color_pattern_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qchange_item_color_pattern,
	    change_item_color_pattern_action_compiler_1,Qaction_compiler);
    change_item_color_pattern_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_item_color_pattern_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_item_color_pattern_prolog,
	    change_item_color_pattern_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_item_color_pattern_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_item_color_pattern_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_item_color_pattern_epilog,
	    change_item_color_pattern_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_27 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    Qscale = STATIC_SYMBOL("SCALE",AB_package);
    array_constant_28 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    array_constant_29 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    Qworkspace_position = STATIC_SYMBOL("WORKSPACE-POSITION",AB_package);
    array_constant_30 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)23L,(SI_Long)57344L);
    Qscreen_position = STATIC_SYMBOL("SCREEN-POSITION",AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    array_constant_33 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    array_constant_35 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)57344L);
    Qab_at = STATIC_SYMBOL("AT",AB_package);
    array_constant_37 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57344L);
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qprint_show_instruction = STATIC_SYMBOL("PRINT-SHOW-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_show_instruction,
	    STATIC_FUNCTION(print_show_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qshow,SYMBOL_FUNCTION(Qprint_show_instruction),
	    Qprocedure_statement_writer);
    Qshow_prolog = STATIC_SYMBOL("SHOW-PROLOG",AB_package);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qab_class,Qui_client_item);
    Qshow_epilog = STATIC_SYMBOL("SHOW-EPILOG",AB_package);
    show_action_compiler_1 = STATIC_FUNCTION(show_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qshow,show_action_compiler_1,Qaction_compiler);
    show_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(show_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshow_prolog,show_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    show_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(show_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshow_epilog,show_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qshow_new = STATIC_SYMBOL("SHOW-NEW",AB_package);
    Qprint_show_new_instruction = 
	    STATIC_SYMBOL("PRINT-SHOW-NEW-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_show_new_instruction,
	    STATIC_FUNCTION(print_show_new_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qshow_new,
	    SYMBOL_FUNCTION(Qprint_show_new_instruction),
	    Qprocedure_statement_writer);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qshow_new_prolog = STATIC_SYMBOL("SHOW-NEW-PROLOG",AB_package);
    Qshow_new_epilog = STATIC_SYMBOL("SHOW-NEW-EPILOG",AB_package);
    show_new_action_compiler_1 = STATIC_FUNCTION(show_new_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qshow_new,show_new_action_compiler_1,
	    Qaction_compiler);
    show_new_pseudo_emitter_1 = STATIC_FUNCTION(show_new_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qshow_new,show_new_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    show_new_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(show_new_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshow_new_prolog,
	    show_new_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    show_new_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(show_new_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshow_new_epilog,
	    show_new_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_38 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)57344L);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qprint_hide_instruction = STATIC_SYMBOL("PRINT-HIDE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_hide_instruction,
	    STATIC_FUNCTION(print_hide_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qhide,SYMBOL_FUNCTION(Qprint_hide_instruction),
	    Qprocedure_statement_writer);
    Qhide_prolog = STATIC_SYMBOL("HIDE-PROLOG",AB_package);
    Qhide_epilog = STATIC_SYMBOL("HIDE-EPILOG",AB_package);
    hide_action_compiler_1 = STATIC_FUNCTION(hide_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qhide,hide_action_compiler_1,Qaction_compiler);
    hide_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(hide_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qhide_prolog,hide_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    hide_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(hide_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qhide_epilog,hide_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_39 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)10L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)16L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)17L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)18L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)19L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)20L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)21L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)22L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)23L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)24L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)26L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)27L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)31L,(SI_Long)57344L);
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    Qprint_activate_instruction = 
	    STATIC_SYMBOL("PRINT-ACTIVATE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_activate_instruction,
	    STATIC_FUNCTION(print_activate_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qactivate,
	    SYMBOL_FUNCTION(Qprint_activate_instruction),
	    Qprocedure_statement_writer);
    Qactivate_prolog = STATIC_SYMBOL("ACTIVATE-PROLOG",AB_package);
    Qactivate_epilog = STATIC_SYMBOL("ACTIVATE-EPILOG",AB_package);
    activate_action_compiler_1 = STATIC_FUNCTION(activate_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qactivate,activate_action_compiler_1,
	    Qaction_compiler);
    activate_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(activate_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qactivate_prolog,
	    activate_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    activate_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(activate_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qactivate_epilog,
	    activate_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_40 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)12L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)13L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)15L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)16L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)17L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)18L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)20L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)21L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)22L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)23L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)24L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)25L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)26L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)28L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)29L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)39L,(SI_Long)57344L);
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    Qprint_deactivate_instruction = 
	    STATIC_SYMBOL("PRINT-DEACTIVATE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_deactivate_instruction,
	    STATIC_FUNCTION(print_deactivate_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qdeactivate,
	    SYMBOL_FUNCTION(Qprint_deactivate_instruction),
	    Qprocedure_statement_writer);
    Qprocedure_flags = STATIC_SYMBOL("PROCEDURE-FLAGS",AB_package);
    Qdeactivate_prolog = STATIC_SYMBOL("DEACTIVATE-PROLOG",AB_package);
    Qdeactivate_epilog = STATIC_SYMBOL("DEACTIVATE-EPILOG",AB_package);
    deactivate_action_compiler_1 = 
	    STATIC_FUNCTION(deactivate_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qdeactivate,deactivate_action_compiler_1,
	    Qaction_compiler);
    deactivate_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(deactivate_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qdeactivate_prolog,
	    deactivate_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    deactivate_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(deactivate_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qdeactivate_epilog,
	    deactivate_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_action = STATIC_SYMBOL("CALL-ACTION",AB_package);
    Qg2_deactivate = STATIC_SYMBOL("G2-DEACTIVATE",AB_package);
    Qevaluated_structure = STATIC_SYMBOL("EVALUATED-STRUCTURE",AB_package);
    Qdeactivate_subworkspace_only = 
	    STATIC_SYMBOL("DEACTIVATE-SUBWORKSPACE-ONLY",AB_package);
    array_constant_41 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)57344L);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    array_constant_43 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)8L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)9L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)11L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)13L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)17L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)18L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)20L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)21L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)22L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)23L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)24L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)25L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)26L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)31L,(SI_Long)57344L);
    Qhalt = STATIC_SYMBOL("HALT",AB_package);
    Qprint_halt_instruction = STATIC_SYMBOL("PRINT-HALT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_halt_instruction,
	    STATIC_FUNCTION(print_halt_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qhalt,SYMBOL_FUNCTION(Qprint_halt_instruction),
	    Qprocedure_statement_writer);
    Qhalt_prolog = STATIC_SYMBOL("HALT-PROLOG",AB_package);
    Qhalt_epilog = STATIC_SYMBOL("HALT-EPILOG",AB_package);
    halt_action_compiler_1 = STATIC_FUNCTION(halt_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qhalt,halt_action_compiler_1,Qaction_compiler);
    halt_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(halt_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qhalt_prolog,halt_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    halt_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(halt_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qhalt_epilog,halt_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_44 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)57344L);
    Qprint_set_instruction = STATIC_SYMBOL("PRINT-SET-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_set_instruction,
	    STATIC_FUNCTION(print_set_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qset,SYMBOL_FUNCTION(Qprint_set_instruction),
	    Qprocedure_statement_writer);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    Qset_prolog = STATIC_SYMBOL("SET-PROLOG",AB_package);
    Qset_epilog = STATIC_SYMBOL("SET-EPILOG",AB_package);
    set_action_compiler_1 = STATIC_FUNCTION(set_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qset,set_action_compiler_1,Qaction_compiler);
    set_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_prolog,set_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    set_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(set_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qset_epilog,set_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qduration = STATIC_SYMBOL("DURATION",AB_package);
    Qon = STATIC_SYMBOL("ON",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qbelow = STATIC_SYMBOL("BELOW",AB_package);
    string_constant_5 = STATIC_STRING("Inform action");
    string_constant_6 = STATIC_STRING("Unknown Inform option ~a.");
    string_constant_7 = STATIC_STRING("Missing Inform option.");
    array_constant_45 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)57344L);
    array_constant_46 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)15L,(SI_Long)57344L);
    array_constant_47 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)57344L);
    array_constant_48 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)11L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)23L,(SI_Long)57344L);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    array_constant_49 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)15L,(SI_Long)57344L);
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    Qfixed_format = STATIC_SYMBOL("FIXED-FORMAT",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qprint_inform_instruction = STATIC_SYMBOL("PRINT-INFORM-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_inform_instruction,
	    STATIC_FUNCTION(print_inform_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qinform,
	    SYMBOL_FUNCTION(Qprint_inform_instruction),
	    Qprocedure_statement_writer);
    Qoperator = STATIC_SYMBOL("OPERATOR",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qthe,Qoperator);
    Qinform_prolog = STATIC_SYMBOL("INFORM-PROLOG",AB_package);
    Qformat_form = STATIC_SYMBOL("FORMAT-FORM",AB_package);
    Qfirst_that_has_a_value = STATIC_SYMBOL("FIRST-THAT-HAS-A-VALUE",
	    AB_package);
    array_constant_50 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)57344L);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_25);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    Qinform_epilog = STATIC_SYMBOL("INFORM-EPILOG",AB_package);
    inform_action_compiler_1 = STATIC_FUNCTION(inform_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qinform,inform_action_compiler_1,Qaction_compiler);
    inform_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(inform_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qinform_prolog,inform_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    inform_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(inform_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qinform_epilog,inform_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_8 = STATIC_STRING(" IS ~a ");
    Qadd_relation = STATIC_SYMBOL("ADD-RELATION",AB_package);
    Qprint_add_relation = STATIC_SYMBOL("PRINT-ADD-RELATION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_add_relation,
	    STATIC_FUNCTION(print_add_relation,NIL,FALSE,1,1));
    mutate_global_property(Qadd_relation,
	    SYMBOL_FUNCTION(Qprint_add_relation),Qprocedure_statement_writer);
    Qadd_relation_prolog = STATIC_SYMBOL("ADD-RELATION-PROLOG",AB_package);
    Qadd_relation_epilog = STATIC_SYMBOL("ADD-RELATION-EPILOG",AB_package);
    add_relation_action_compiler_1 = 
	    STATIC_FUNCTION(add_relation_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qadd_relation,add_relation_action_compiler_1,
	    Qaction_compiler);
    add_relation_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(add_relation_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qadd_relation_prolog,
	    add_relation_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    add_relation_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(add_relation_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qadd_relation_epilog,
	    add_relation_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qremove_relation = STATIC_SYMBOL("REMOVE-RELATION",AB_package);
    mutate_global_property(Qremove_relation,
	    SYMBOL_FUNCTION(Qprint_add_relation),Qprocedure_statement_writer);
    Qremove_relation_prolog = STATIC_SYMBOL("REMOVE-RELATION-PROLOG",
	    AB_package);
    Qremove_relation_epilog = STATIC_SYMBOL("REMOVE-RELATION-EPILOG",
	    AB_package);
    remove_relation_action_compiler_1 = 
	    STATIC_FUNCTION(remove_relation_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qremove_relation,
	    remove_relation_action_compiler_1,Qaction_compiler);
    remove_relation_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(remove_relation_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qremove_relation_prolog,
	    remove_relation_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    remove_relation_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(remove_relation_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qremove_relation_epilog,
	    remove_relation_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_51 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)10L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)11L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)13L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)16L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)17L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)23L,(SI_Long)57344L);
    array_constant_52 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)10L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)15L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)17L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)19L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)20L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)31L,(SI_Long)57344L);
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    Qprint_create_instruction = STATIC_SYMBOL("PRINT-CREATE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_create_instruction,
	    STATIC_FUNCTION(print_create_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qcreate,
	    SYMBOL_FUNCTION(Qprint_create_instruction),
	    Qprocedure_statement_writer);
    string_constant_9 = 
	    STATIC_STRING("In the create action, the local name ~a is declared to ~\n                       hold ~NT, not ~NT.");
    Qcreate_prolog = STATIC_SYMBOL("CREATE-PROLOG",AB_package);
    Qcreate_epilog = STATIC_SYMBOL("CREATE-EPILOG",AB_package);
    create_action_compiler_1 = STATIC_FUNCTION(create_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qcreate,create_action_compiler_1,Qaction_compiler);
    create_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcreate_prolog,create_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    create_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcreate_epilog,create_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    create_pseudo_emitter_1 = STATIC_FUNCTION(create_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate,create_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_53 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)15L,(SI_Long)57344L);
    Qprint_delete_instruction = STATIC_SYMBOL("PRINT-DELETE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_delete_instruction,
	    STATIC_FUNCTION(print_delete_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qdelete,
	    SYMBOL_FUNCTION(Qprint_delete_instruction),
	    Qprocedure_statement_writer);
    Qdelete_prolog = STATIC_SYMBOL("DELETE-PROLOG",AB_package);
    Qwithout_permanence_checks_without_leaving_stubs = 
	    STATIC_SYMBOL("WITHOUT-PERMANENCE-CHECKS-WITHOUT-LEAVING-STUBS",
	    AB_package);
    Qwithout_permanence_checks = STATIC_SYMBOL("WITHOUT-PERMANENCE-CHECKS",
	    AB_package);
    Qdelete_epilog = STATIC_SYMBOL("DELETE-EPILOG",AB_package);
    delete_action_compiler_1 = STATIC_FUNCTION(delete_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qdelete,delete_action_compiler_1,Qaction_compiler);
    delete_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(delete_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qdelete_prolog,delete_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    delete_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(delete_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qdelete_epilog,delete_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_54 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)15L,(SI_Long)57344L);
    array_constant_55 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)4L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)7L,(SI_Long)57344L);
    array_constant_56 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)57344L);
    array_constant_57 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)3L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)7L,(SI_Long)57344L);
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    Qprint_transfer_instruction = 
	    STATIC_SYMBOL("PRINT-TRANSFER-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_transfer_instruction,
	    STATIC_FUNCTION(print_transfer_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qtransfer,
	    SYMBOL_FUNCTION(Qprint_transfer_instruction),
	    Qprocedure_statement_writer);
    Qmouse = STATIC_SYMBOL("MOUSE",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_window);
    Qtransfer_prolog = STATIC_SYMBOL("TRANSFER-PROLOG",AB_package);
    Qtransfer_epilog = STATIC_SYMBOL("TRANSFER-EPILOG",AB_package);
    transfer_action_compiler_1 = STATIC_FUNCTION(transfer_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qtransfer,transfer_action_compiler_1,
	    Qaction_compiler);
    transfer_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(transfer_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qtransfer_prolog,
	    transfer_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    transfer_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(transfer_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qtransfer_epilog,
	    transfer_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qchange_system_attribute = STATIC_SYMBOL("CHANGE-SYSTEM-ATTRIBUTE",
	    AB_package);
    Qprint_change_system_attribute_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-SYSTEM-ATTRIBUTE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_system_attribute_instruction,
	    STATIC_FUNCTION(print_change_system_attribute_instruction,NIL,
	    FALSE,1,1));
    mutate_global_property(Qchange_system_attribute,
	    SYMBOL_FUNCTION(Qprint_change_system_attribute_instruction),
	    Qprocedure_statement_writer);
    Qchange_system_attribute_prolog = 
	    STATIC_SYMBOL("CHANGE-SYSTEM-ATTRIBUTE-PROLOG",AB_package);
    Qchange_system_attribute_epilog = 
	    STATIC_SYMBOL("CHANGE-SYSTEM-ATTRIBUTE-EPILOG",AB_package);
    change_system_attribute_action_compiler_1 = 
	    STATIC_FUNCTION(change_system_attribute_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qchange_system_attribute,
	    change_system_attribute_action_compiler_1,Qaction_compiler);
    change_system_attribute_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_system_attribute_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_system_attribute_prolog,
	    change_system_attribute_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_system_attribute_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_system_attribute_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_system_attribute_epilog,
	    change_system_attribute_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_58 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)8L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)13L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)14L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)16L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)17L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)23L,(SI_Long)57344L);
    Qchange_the_text_of_attribute = 
	    STATIC_SYMBOL("CHANGE-THE-TEXT-OF-ATTRIBUTE",AB_package);
    Qprint_change_the_text_of_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-THE-TEXT-OF-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_the_text_of_instruction,
	    STATIC_FUNCTION(print_change_the_text_of_instruction,NIL,FALSE,
	    1,1));
    mutate_global_property(Qchange_the_text_of_attribute,
	    SYMBOL_FUNCTION(Qprint_change_the_text_of_instruction),
	    Qprocedure_statement_writer);
    Qchange_the_text_of_attribute_prolog = 
	    STATIC_SYMBOL("CHANGE-THE-TEXT-OF-ATTRIBUTE-PROLOG",AB_package);
    Qchange_the_text_of_attribute_epilog = 
	    STATIC_SYMBOL("CHANGE-THE-TEXT-OF-ATTRIBUTE-EPILOG",AB_package);
    change_the_text_of_attribute_action_compiler_1 = 
	    STATIC_FUNCTION(change_the_text_of_attribute_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qchange_the_text_of_attribute,
	    change_the_text_of_attribute_action_compiler_1,Qaction_compiler);
    change_the_text_of_attribute_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_the_text_of_attribute_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_the_text_of_attribute_prolog,
	    change_the_text_of_attribute_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_the_text_of_attribute_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_the_text_of_attribute_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_the_text_of_attribute_epilog,
	    change_the_text_of_attribute_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_59 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)3L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)15L,(SI_Long)57344L);
    Qchange_nth_element = STATIC_SYMBOL("CHANGE-NTH-ELEMENT",AB_package);
    Qprint_change_nth_element_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-NTH-ELEMENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_nth_element_instruction,
	    STATIC_FUNCTION(print_change_nth_element_instruction,NIL,FALSE,
	    1,1));
    mutate_global_property(Qchange_nth_element,
	    SYMBOL_FUNCTION(Qprint_change_nth_element_instruction),
	    Qprocedure_statement_writer);
    string_constant_10 = 
	    string_append2(STATIC_STRING("parentheses should be added around the expression ~\n                        before the [ ] in `~ND\' to avoid misinterpretation.  ~\n                        (This current interp"),
	    STATIC_STRING("retation, which G2 ~\n                        Version 3.0 introduced in error, is ~\n                        subject to change in a future release)"));
    string_constant_11 = 
	    STATIC_STRING("Cannot compile a statement containing the change ~\n                         action.  `~ND\' does not refer to an array or list ~\n                         element");
    string_constant_12 = 
	    STATIC_STRING("Cannot compile a statement containing the change ~\n              action.  `~ND\' does not refer to an array or list ~\n              element");
    Qchange_nth_element_prolog = STATIC_SYMBOL("CHANGE-NTH-ELEMENT-PROLOG",
	    AB_package);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_array);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_list);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_19);
    Qchange_nth_element_epilog = STATIC_SYMBOL("CHANGE-NTH-ELEMENT-EPILOG",
	    AB_package);
    change_nth_element_action_compiler_1 = 
	    STATIC_FUNCTION(change_nth_element_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qchange_nth_element,
	    change_nth_element_action_compiler_1,Qaction_compiler);
    array_constant_60 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)15L,(SI_Long)57344L);
    Qchange_nth_element_to_no_value = 
	    STATIC_SYMBOL("CHANGE-NTH-ELEMENT-TO-NO-VALUE",AB_package);
    Qprint_change_nth_element_to_no_value_instruction = 
	    STATIC_SYMBOL("PRINT-CHANGE-NTH-ELEMENT-TO-NO-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_change_nth_element_to_no_value_instruction,
	    STATIC_FUNCTION(print_change_nth_element_to_no_value_instruction,
	    NIL,FALSE,1,1));
    mutate_global_property(Qchange_nth_element_to_no_value,
	    SYMBOL_FUNCTION(Qprint_change_nth_element_to_no_value_instruction),
	    Qprocedure_statement_writer);
    Qchange_nth_element_to_no_value_prolog = 
	    STATIC_SYMBOL("CHANGE-NTH-ELEMENT-TO-NO-VALUE-PROLOG",AB_package);
    Qchange_nth_element_to_no_value_epilog = 
	    STATIC_SYMBOL("CHANGE-NTH-ELEMENT-TO-NO-VALUE-EPILOG",AB_package);
    change_nth_element_to_no_value_action_compiler_1 = 
	    STATIC_FUNCTION(change_nth_element_to_no_value_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qchange_nth_element_to_no_value,
	    change_nth_element_to_no_value_action_compiler_1,Qaction_compiler);
    Qvalue_type_of_array = STATIC_SYMBOL("VALUE-TYPE-OF-ARRAY",AB_package);
    Qvalue_type_of_index = STATIC_SYMBOL("VALUE-TYPE-OF-INDEX",AB_package);
    change_nth_element_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_nth_element_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qchange_nth_element_prolog,
	    change_nth_element_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qab_class,Qinteger_array);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qab_class,Qfloat_array);
    change_nth_element_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_nth_element_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qchange_nth_element_epilog,
	    change_nth_element_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_nth_element_to_no_value_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_nth_element_to_no_value_prolog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_nth_element_to_no_value_prolog,
	    change_nth_element_to_no_value_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    change_nth_element_to_no_value_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(change_nth_element_to_no_value_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qchange_nth_element_to_no_value_epilog,
	    change_nth_element_to_no_value_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_61 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)15L,(SI_Long)57344L);
    Qbeginning = STATIC_SYMBOL("BEGINNING",AB_package);
    string_constant_13 = STATIC_STRING(" AT THE BEGINNING OF THE ~a LIST ");
    Qend = STATIC_SYMBOL("END",AB_package);
    string_constant_14 = STATIC_STRING(" AT THE END OF THE ~a LIST ");
    Qbefore = STATIC_SYMBOL("BEFORE",AB_package);
    array_constant_62 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)3L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)15L,(SI_Long)57344L);
    string_constant_15 = STATIC_STRING(" IN THE ~a LIST ");
    Qafter = STATIC_SYMBOL("AFTER",AB_package);
    array_constant_63 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)15L,(SI_Long)57344L);
    array_constant_64 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)5L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)11L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)14L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)16L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)18L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)19L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)23L,(SI_Long)57344L);
    array_constant_65 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)5L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)10L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)13L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)23L,(SI_Long)57344L);
    array_constant_66 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)7L,(SI_Long)57344L);
    Qg2_list_insert = STATIC_SYMBOL("G2-LIST-INSERT",AB_package);
    Qprint_g2_list_insert_instruction = 
	    STATIC_SYMBOL("PRINT-G2-LIST-INSERT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_g2_list_insert_instruction,
	    STATIC_FUNCTION(print_g2_list_insert_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qg2_list_insert,
	    SYMBOL_FUNCTION(Qprint_g2_list_insert_instruction),
	    Qprocedure_statement_writer);
    Qg2_list_insert_prolog = STATIC_SYMBOL("G2-LIST-INSERT-PROLOG",AB_package);
    Qg2_list_insert_epilog = STATIC_SYMBOL("G2-LIST-INSERT-EPILOG",AB_package);
    g2_list_insert_action_compiler_1 = 
	    STATIC_FUNCTION(g2_list_insert_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qg2_list_insert,
	    g2_list_insert_action_compiler_1,Qaction_compiler);
    Qbefore_element = STATIC_SYMBOL("BEFORE-ELEMENT",AB_package);
    Qafter_element = STATIC_SYMBOL("AFTER-ELEMENT",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qbefore_element,Qafter_element);
    Qcoerce_item_or_values_to_matching_element_type_or_unknown = 
	    STATIC_SYMBOL("COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE-OR-UNKNOWN",
	    AB_package);
    Qcoerce_item_or_values_to_matching_element_type = 
	    STATIC_SYMBOL("COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE",
	    AB_package);
    g2_list_insert_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(g2_list_insert_prolog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qg2_list_insert_prolog,
	    g2_list_insert_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    g2_list_insert_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(g2_list_insert_epilog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qg2_list_insert_epilog,
	    g2_list_insert_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_67 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)4L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)15L,(SI_Long)57344L);
    string_constant_16 = STATIC_STRING("THE FIRST ~a FROM ");
    string_constant_17 = STATIC_STRING("THE LAST ~a FROM ");
    Qelement = STATIC_SYMBOL("ELEMENT",AB_package);
    string_constant_18 = STATIC_STRING(" FROM THE ~a LIST ");
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    array_constant_68 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)4L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)15L,(SI_Long)57344L);
    Qg2_list_remove = STATIC_SYMBOL("G2-LIST-REMOVE",AB_package);
    Qprint_g2_list_remove_instruction = 
	    STATIC_SYMBOL("PRINT-G2-LIST-REMOVE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_g2_list_remove_instruction,
	    STATIC_FUNCTION(print_g2_list_remove_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qg2_list_remove,
	    SYMBOL_FUNCTION(Qprint_g2_list_remove_instruction),
	    Qprocedure_statement_writer);
    Qg2_list_remove_prolog = STATIC_SYMBOL("G2-LIST-REMOVE-PROLOG",AB_package);
    Qg2_list_remove_epilog = STATIC_SYMBOL("G2-LIST-REMOVE-EPILOG",AB_package);
    g2_list_remove_action_compiler_1 = 
	    STATIC_FUNCTION(g2_list_remove_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qg2_list_remove,
	    g2_list_remove_action_compiler_1,Qaction_compiler);
    Qelement_position = STATIC_SYMBOL("ELEMENT-POSITION",AB_package);
    g2_list_remove_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(g2_list_remove_prolog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qg2_list_remove_prolog,
	    g2_list_remove_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    g2_list_remove_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(g2_list_remove_epilog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qg2_list_remove_epilog,
	    g2_list_remove_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_69 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)7L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)9L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)10L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)14L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)15L,(SI_Long)90L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)23L,(SI_Long)57344L);
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    Qprint_nupec_synchronize_instruction = 
	    STATIC_SYMBOL("PRINT-NUPEC-SYNCHRONIZE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_nupec_synchronize_instruction,
	    STATIC_FUNCTION(print_nupec_synchronize_instruction,NIL,FALSE,
	    1,1));
    mutate_global_property(Qnupec_synchronize,
	    SYMBOL_FUNCTION(Qprint_nupec_synchronize_instruction),
	    Qprocedure_statement_writer);
    Qnupec_synchronize_prolog = STATIC_SYMBOL("NUPEC-SYNCHRONIZE-PROLOG",
	    AB_package);
    Qnupec_synchronize_epilog = STATIC_SYMBOL("NUPEC-SYNCHRONIZE-EPILOG",
	    AB_package);
    nupec_synchronize_action_compiler_1 = 
	    STATIC_FUNCTION(nupec_synchronize_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qnupec_synchronize,
	    nupec_synchronize_action_compiler_1,Qaction_compiler);
    nupec_synchronize_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(nupec_synchronize_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnupec_synchronize_prolog,
	    nupec_synchronize_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    nupec_synchronize_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(nupec_synchronize_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnupec_synchronize_epilog,
	    nupec_synchronize_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_70 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)11L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)12L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)17L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)18L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)20L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)31L,(SI_Long)57344L);
    array_constant_71 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)7L,(SI_Long)57344L);
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    Qprint_create_explanation_statement = 
	    STATIC_SYMBOL("PRINT-CREATE-EXPLANATION-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_create_explanation_statement,
	    STATIC_FUNCTION(print_create_explanation_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcreate_explanation,
	    SYMBOL_FUNCTION(Qprint_create_explanation_statement),
	    Qprocedure_statement_writer);
    Qexplanation = STATIC_SYMBOL("EXPLANATION",AB_package);
    string_constant_19 = 
	    STATIC_STRING("In the create explanation action, the local name ~\n                ~a is declared to hold ~NT, not ~NT.");
    Qcreate_explanation_prolog = STATIC_SYMBOL("CREATE-EXPLANATION-PROLOG",
	    AB_package);
    Qcreate_explanation_epilog = STATIC_SYMBOL("CREATE-EXPLANATION-EPILOG",
	    AB_package);
    create_explanation_action_compiler_1 = 
	    STATIC_FUNCTION(create_explanation_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qcreate_explanation,
	    create_explanation_action_compiler_1,Qaction_compiler);
    create_explanation_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_explanation_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_explanation_prolog,
	    create_explanation_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    create_explanation_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_explanation_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_explanation_epilog,
	    create_explanation_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_72 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)1L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)15L,(SI_Long)57344L);
    Qupdate = STATIC_SYMBOL("UPDATE",AB_package);
    Qprint_update_instruction = STATIC_SYMBOL("PRINT-UPDATE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_update_instruction,
	    STATIC_FUNCTION(print_update_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qupdate,
	    SYMBOL_FUNCTION(Qprint_update_instruction),
	    Qprocedure_statement_writer);
    Qupdate_prolog = STATIC_SYMBOL("UPDATE-PROLOG",AB_package);
    Qupdate_epilog = STATIC_SYMBOL("UPDATE-EPILOG",AB_package);
    update_action_compiler_1 = STATIC_FUNCTION(update_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qupdate,update_action_compiler_1,Qaction_compiler);
    update_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(update_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qupdate_prolog,update_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    update_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(update_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qupdate_epilog,update_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcreate_connection = STATIC_SYMBOL("CREATE-CONNECTION",AB_package);
    Qprint_create_connection_statement = 
	    STATIC_SYMBOL("PRINT-CREATE-CONNECTION-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_create_connection_statement,
	    STATIC_FUNCTION(print_create_connection_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcreate_connection,
	    SYMBOL_FUNCTION(Qprint_create_connection_statement),
	    Qprocedure_statement_writer);
    Qconnected_between = STATIC_SYMBOL("CONNECTED-BETWEEN",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    string_constant_20 = 
	    STATIC_STRING("The local name ~a is declared to hold the type ~\n                            ~NT, which does not include the type ~NT.");
    create_connection_action_compiler_1 = 
	    STATIC_FUNCTION(create_connection_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qcreate_connection,
	    create_connection_action_compiler_1,Qaction_compiler);
    Qcreate_connection_prolog = STATIC_SYMBOL("CREATE-CONNECTION-PROLOG",
	    AB_package);
    Qcreate_connection_epilog = STATIC_SYMBOL("CREATE-CONNECTION-EPILOG",
	    AB_package);
    Qnewly_located_at = STATIC_SYMBOL("NEWLY-LOCATED-AT",AB_package);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qab_class,Qquantity_list);
    create_connection_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_connection_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_connection_prolog,
	    create_connection_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    create_connection_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_connection_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_connection_epilog,
	    create_connection_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_73 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)15L,(SI_Long)57344L);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    Qprint_abort_instruction = STATIC_SYMBOL("PRINT-ABORT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_abort_instruction,
	    STATIC_FUNCTION(print_abort_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qabort_g2,
	    SYMBOL_FUNCTION(Qprint_abort_instruction),
	    Qprocedure_statement_writer);
    Qabort_prolog = STATIC_SYMBOL("ABORT-PROLOG",AB_package);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qprocedure_invocation);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_30);
    Qabort_epilog = STATIC_SYMBOL("ABORT-EPILOG",AB_package);
    abort_action_compiler_1 = STATIC_FUNCTION(abort_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qabort_g2,abort_action_compiler_1,Qaction_compiler);
    abort_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(abort_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qabort_prolog,abort_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    abort_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(abort_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qabort_epilog,abort_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_74 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)2L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)7L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)11L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)15L,(SI_Long)57344L);
    Qshut_down_g2 = STATIC_SYMBOL("SHUT-DOWN-G2",AB_package);
    Qprint_shut_down_g2_instruction = 
	    STATIC_SYMBOL("PRINT-SHUT-DOWN-G2-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_shut_down_g2_instruction,
	    STATIC_FUNCTION(print_shut_down_g2_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qshut_down_g2,
	    SYMBOL_FUNCTION(Qprint_shut_down_g2_instruction),
	    Qprocedure_statement_writer);
    Qshut_down_g2_prolog = STATIC_SYMBOL("SHUT-DOWN-G2-PROLOG",AB_package);
    Qshut_down_g2_epilog = STATIC_SYMBOL("SHUT-DOWN-G2-EPILOG",AB_package);
    shut_down_g2_action_compiler_1 = 
	    STATIC_FUNCTION(shut_down_g2_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qshut_down_g2,shut_down_g2_action_compiler_1,
	    Qaction_compiler);
    shut_down_g2_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(shut_down_g2_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshut_down_g2_prolog,
	    shut_down_g2_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    shut_down_g2_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(shut_down_g2_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qshut_down_g2_epilog,
	    shut_down_g2_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_75 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)9L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)12L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)13L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)16L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)17L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)18L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)19L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)23L,(SI_Long)57344L);
    Qreset_kb = STATIC_SYMBOL("RESET-KB",AB_package);
    Qprint_reset_kb_instruction = 
	    STATIC_SYMBOL("PRINT-RESET-KB-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_reset_kb_instruction,
	    STATIC_FUNCTION(print_reset_kb_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qreset_kb,
	    SYMBOL_FUNCTION(Qprint_reset_kb_instruction),
	    Qprocedure_statement_writer);
    Qreset_kb_prolog = STATIC_SYMBOL("RESET-KB-PROLOG",AB_package);
    Qreset_kb_epilog = STATIC_SYMBOL("RESET-KB-EPILOG",AB_package);
    reset_kb_action_compiler_1 = STATIC_FUNCTION(reset_kb_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qreset_kb,reset_kb_action_compiler_1,
	    Qaction_compiler);
    reset_kb_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(reset_kb_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qreset_kb_prolog,
	    reset_kb_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    reset_kb_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(reset_kb_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qreset_kb_epilog,
	    reset_kb_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_76 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)2L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)9L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)12L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)13L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)16L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)17L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)18L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)19L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)23L,(SI_Long)57344L);
    Qpause_kb = STATIC_SYMBOL("PAUSE-KB",AB_package);
    Qprint_pause_kb_instruction = 
	    STATIC_SYMBOL("PRINT-PAUSE-KB-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_pause_kb_instruction,
	    STATIC_FUNCTION(print_pause_kb_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qpause_kb,
	    SYMBOL_FUNCTION(Qprint_pause_kb_instruction),
	    Qprocedure_statement_writer);
    Qpause_kb_prolog = STATIC_SYMBOL("PAUSE-KB-PROLOG",AB_package);
    Qpause_kb_epilog = STATIC_SYMBOL("PAUSE-KB-EPILOG",AB_package);
    pause_kb_action_compiler_1 = STATIC_FUNCTION(pause_kb_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qpause_kb,pause_kb_action_compiler_1,
	    Qaction_compiler);
    pause_kb_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(pause_kb_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qpause_kb_prolog,
	    pause_kb_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    pause_kb_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(pause_kb_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qpause_kb_epilog,
	    pause_kb_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_21 = 
	    STATIC_STRING("OF THE CLASS NAMED BY ~NE BY CLONING ~ND.");
    Qcreate_by_cloning = STATIC_SYMBOL("CREATE-BY-CLONING",AB_package);
    Qprint_create_by_cloning_statement = 
	    STATIC_SYMBOL("PRINT-CREATE-BY-CLONING-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_create_by_cloning_statement,
	    STATIC_FUNCTION(print_create_by_cloning_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcreate_by_cloning,
	    SYMBOL_FUNCTION(Qprint_create_by_cloning_statement),
	    Qprocedure_statement_writer);
    Qcreate_by_cloning_prolog = STATIC_SYMBOL("CREATE-BY-CLONING-PROLOG",
	    AB_package);
    Qcreate_by_cloning_epilog = STATIC_SYMBOL("CREATE-BY-CLONING-EPILOG",
	    AB_package);
    create_by_cloning_action_compiler_1 = 
	    STATIC_FUNCTION(create_by_cloning_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qcreate_by_cloning,
	    create_by_cloning_action_compiler_1,Qaction_compiler);
    create_by_cloning_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_by_cloning_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_by_cloning_prolog,
	    create_by_cloning_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    create_by_cloning_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(create_by_cloning_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcreate_by_cloning_epilog,
	    create_by_cloning_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_22 = STATIC_STRING("MAKE ~ND PERMANENT");
    Qmake_permanent = STATIC_SYMBOL("MAKE-PERMANENT",AB_package);
    Qprint_make_permanent_instruction = 
	    STATIC_SYMBOL("PRINT-MAKE-PERMANENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_make_permanent_instruction,
	    STATIC_FUNCTION(print_make_permanent_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qmake_permanent,
	    SYMBOL_FUNCTION(Qprint_make_permanent_instruction),
	    Qprocedure_statement_writer);
    Qmake_permanent_prolog = STATIC_SYMBOL("MAKE-PERMANENT-PROLOG",AB_package);
    Qmake_permanent_epilog = STATIC_SYMBOL("MAKE-PERMANENT-EPILOG",AB_package);
    make_permanent_action_compiler_1 = 
	    STATIC_FUNCTION(make_permanent_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qmake_permanent,
	    make_permanent_action_compiler_1,Qaction_compiler);
    make_permanent_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_permanent_prolog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmake_permanent_prolog,
	    make_permanent_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    make_permanent_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_permanent_epilog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmake_permanent_epilog,
	    make_permanent_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_23 = STATIC_STRING("MAKE ~ND TRANSIENT");
    Qmake_transient = STATIC_SYMBOL("MAKE-TRANSIENT",AB_package);
    Qprint_make_transient_instruction = 
	    STATIC_SYMBOL("PRINT-MAKE-TRANSIENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_make_transient_instruction,
	    STATIC_FUNCTION(print_make_transient_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qmake_transient,
	    SYMBOL_FUNCTION(Qprint_make_transient_instruction),
	    Qprocedure_statement_writer);
    Qmake_transient_prolog = STATIC_SYMBOL("MAKE-TRANSIENT-PROLOG",AB_package);
    Qmake_transient_epilog = STATIC_SYMBOL("MAKE-TRANSIENT-EPILOG",AB_package);
    make_transient_action_compiler_1 = 
	    STATIC_FUNCTION(make_transient_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qmake_transient,
	    make_transient_action_compiler_1,Qaction_compiler);
    make_transient_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_transient_prolog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmake_transient_prolog,
	    make_transient_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    make_transient_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_transient_epilog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmake_transient_epilog,
	    make_transient_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_24 = STATIC_STRING("MAKE ~ND THE SUBWORKSPACE OF ~ND");
    Qmake_subworkspace = STATIC_SYMBOL("MAKE-SUBWORKSPACE",AB_package);
    Qprint_make_subworkspace_instruction = 
	    STATIC_SYMBOL("PRINT-MAKE-SUBWORKSPACE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_make_subworkspace_instruction,
	    STATIC_FUNCTION(print_make_subworkspace_instruction,NIL,FALSE,
	    1,1));
    mutate_global_property(Qmake_subworkspace,
	    SYMBOL_FUNCTION(Qprint_make_subworkspace_instruction),
	    Qprocedure_statement_writer);
    Qmake_subworkspace_prolog = STATIC_SYMBOL("MAKE-SUBWORKSPACE-PROLOG",
	    AB_package);
    Qmake_subworkspace_epilog = STATIC_SYMBOL("MAKE-SUBWORKSPACE-EPILOG",
	    AB_package);
    make_subworkspace_action_compiler_1 = 
	    STATIC_FUNCTION(make_subworkspace_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qmake_subworkspace,
	    make_subworkspace_action_compiler_1,Qaction_compiler);
    make_subworkspace_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_subworkspace_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmake_subworkspace_prolog,
	    make_subworkspace_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    make_subworkspace_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(make_subworkspace_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmake_subworkspace_epilog,
	    make_subworkspace_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    string_constant_25 = STATIC_STRING("PRINT ~ND");
    Qprint_print_instruction = STATIC_SYMBOL("PRINT-PRINT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_print_instruction,
	    STATIC_FUNCTION(print_print_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qprint,
	    SYMBOL_FUNCTION(Qprint_print_instruction),
	    Qprocedure_statement_writer);
    Qprint_prolog = STATIC_SYMBOL("PRINT-PROLOG",AB_package);
    Qprint_epilog = STATIC_SYMBOL("PRINT-EPILOG",AB_package);
    print_action_compiler_1 = STATIC_FUNCTION(print_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qprint,print_action_compiler_1,Qaction_compiler);
    print_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(print_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qprint_prolog,print_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    print_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(print_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qprint_epilog,print_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qg2_print = STATIC_SYMBOL("G2-PRINT",AB_package);
    array_constant_77 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)7L,(SI_Long)57344L);
    array_constant_78 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)15L,(SI_Long)57344L);
    array_constant_79 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)1L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)15L,(SI_Long)57344L);
    Qprint_call_instruction = STATIC_SYMBOL("PRINT-CALL-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_call_instruction,
	    STATIC_FUNCTION(print_call_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qcall_action,
	    SYMBOL_FUNCTION(Qprint_call_instruction),
	    Qprocedure_statement_writer);
    string_constant_26 = 
	    STATIC_STRING("CALL accepts a maximum of 255 arguments, this call passed ~a.");
    string_constant_27 = 
	    STATIC_STRING("CALL receives a maximum of 255 values, this call requested ~a.");
    Qcall_prolog = STATIC_SYMBOL("CALL-PROLOG",AB_package);
    Qcall_dependent_epilog = STATIC_SYMBOL("CALL-DEPENDENT-EPILOG",AB_package);
    Qcall_epilog = STATIC_SYMBOL("CALL-EPILOG",AB_package);
    Qcall_dependent_rpc_epilog = STATIC_SYMBOL("CALL-DEPENDENT-RPC-EPILOG",
	    AB_package);
    Qcall_rpc_epilog = STATIC_SYMBOL("CALL-RPC-EPILOG",AB_package);
    call_action_action_compiler_1 = 
	    STATIC_FUNCTION(call_action_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qcall_action,call_action_action_compiler_1,
	    Qaction_compiler);
    call_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcall_prolog,call_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    call_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcall_epilog,call_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qdependent_call = STATIC_SYMBOL("DEPENDENT-CALL",AB_package);
    call_dependent_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_dependent_epilog_pseudo_emitter,NIL,FALSE,
	    2,2);
    mutate_global_property(Qcall_dependent_epilog,
	    call_dependent_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_rpc = STATIC_SYMBOL("CALL-RPC",AB_package);
    call_rpc_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_rpc_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qcall_rpc_epilog,
	    call_rpc_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qcall_assignment_action = STATIC_SYMBOL("CALL-ASSIGNMENT-ACTION",
	    AB_package);
    Qprint_call_assignment_instruction = 
	    STATIC_SYMBOL("PRINT-CALL-ASSIGNMENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_call_assignment_instruction,
	    STATIC_FUNCTION(print_call_assignment_instruction,NIL,FALSE,1,1));
    mutate_global_property(Qcall_assignment_action,
	    SYMBOL_FUNCTION(Qprint_call_assignment_instruction),
	    Qprocedure_statement_writer);
    string_constant_28 = 
	    STATIC_STRING("Because of a return value count mismatch for ~ND, a call to ~\n                it could not be optimized.");
    Qcall_assignment_prolog = STATIC_SYMBOL("CALL-ASSIGNMENT-PROLOG",
	    AB_package);
    Qcall_assignment_dependent_epilog = 
	    STATIC_SYMBOL("CALL-ASSIGNMENT-DEPENDENT-EPILOG",AB_package);
    Qcall_assignment_epilog = STATIC_SYMBOL("CALL-ASSIGNMENT-EPILOG",
	    AB_package);
    Qreceive_values = STATIC_SYMBOL("RECEIVE-VALUES",AB_package);
    Qcall_assignment_dependent_rpc_epilog = 
	    STATIC_SYMBOL("CALL-ASSIGNMENT-DEPENDENT-RPC-EPILOG",AB_package);
    Qcall_assignment_rpc_epilog = 
	    STATIC_SYMBOL("CALL-ASSIGNMENT-RPC-EPILOG",AB_package);
    call_assignment_action_action_compiler_1 = 
	    STATIC_FUNCTION(call_assignment_action_action_compiler,NIL,
	    FALSE,5,5);
    mutate_global_property(Qcall_assignment_action,
	    call_assignment_action_action_compiler_1,Qaction_compiler);
    call_assignment_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_assignment_prolog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcall_assignment_prolog,
	    call_assignment_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    call_assignment_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_assignment_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcall_assignment_epilog,
	    call_assignment_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    call_assignment_rpc_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_assignment_rpc_epilog_pseudo_emitter,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcall_assignment_rpc_epilog,
	    call_assignment_rpc_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    call_assignment_dependent_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(call_assignment_dependent_epilog_pseudo_emitter,
	    NIL,FALSE,2,2);
    mutate_global_property(Qcall_assignment_dependent_epilog,
	    call_assignment_dependent_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_80 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)9L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)12L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)13L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)16L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)17L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)18L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)19L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)23L,(SI_Long)57344L);
    Qstart_kb = STATIC_SYMBOL("START-KB",AB_package);
    mutate_global_property(Qstart_kb,
	    SYMBOL_FUNCTION(Qprint_pause_kb_instruction),
	    Qprocedure_statement_writer);
    Qstart_kb_prolog = STATIC_SYMBOL("START-KB-PROLOG",AB_package);
    Qstart_kb_epilog = STATIC_SYMBOL("START-KB-EPILOG",AB_package);
    start_kb_action_compiler_1 = STATIC_FUNCTION(start_kb_action_compiler,
	    NIL,FALSE,5,5);
    mutate_global_property(Qstart_kb,start_kb_action_compiler_1,
	    Qaction_compiler);
    start_kb_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_kb_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_kb_prolog,
	    start_kb_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    start_kb_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_kb_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_kb_epilog,
	    start_kb_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    array_constant_81 = STATIC_ARRAY(list_constant_24,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)4L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)10L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)13L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)14L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)15L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)17L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)18L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)19L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)20L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)23L,(SI_Long)57344L);
    Qresume_kb = STATIC_SYMBOL("RESUME-KB",AB_package);
    mutate_global_property(Qresume_kb,
	    SYMBOL_FUNCTION(Qprint_pause_kb_instruction),
	    Qprocedure_statement_writer);
    Qresume_kb_epilog = STATIC_SYMBOL("RESUME-KB-EPILOG",AB_package);
    resume_kb_action_compiler_1 = 
	    STATIC_FUNCTION(resume_kb_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qresume_kb,resume_kb_action_compiler_1,
	    Qaction_compiler);
    Qresume_kb_prolog = STATIC_SYMBOL("RESUME-KB-PROLOG",AB_package);
    resume_kb_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(resume_kb_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qresume_kb_prolog,
	    resume_kb_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    resume_kb_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(resume_kb_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qresume_kb_epilog,
	    resume_kb_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qstart_thread_prolog = STATIC_SYMBOL("START-THREAD-PROLOG",AB_package);
    start_thread_prolog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_thread_prolog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_thread_prolog,
	    start_thread_prolog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    Qstart_thread_epilog = STATIC_SYMBOL("START-THREAD-EPILOG",AB_package);
    Qstart_thread = STATIC_SYMBOL("START-THREAD",AB_package);
    start_thread_epilog_pseudo_emitter_1 = 
	    STATIC_FUNCTION(start_thread_epilog_pseudo_emitter,NIL,FALSE,2,2);
    mutate_global_property(Qstart_thread_epilog,
	    start_thread_epilog_pseudo_emitter_1,
	    Qpseudo_instruction_byte_code_emitter);
    start_thread_action_compiler_1 = 
	    STATIC_FUNCTION(start_thread_action_compiler,NIL,FALSE,5,5);
    mutate_global_property(Qstart_thread,start_thread_action_compiler_1,
	    Qaction_compiler);
}
