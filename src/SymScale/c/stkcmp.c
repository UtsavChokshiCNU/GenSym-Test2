/* stkcmp.c
 * Input file:  stack-comp.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "stkcmp.h"


static Object QUNKNOWN_ALLOWED;    /* |unknown-allowed| */

static Object QNO_ITEM_ALLOWED;    /* |no-item-allowed| */

static Object Qtruth_value;        /* truth-value */

static Object Qitem_or_datum;      /* item-or-datum */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qdatum;              /* datum */

static Object list_constant_2;     /* # */

static Object Qreturn_from_function;  /* return-from-function */

static Object Qtag_statement;      /* tag-statement */

static Object list_constant_3;     /* # */

static Object Qsignal_error;       /* signal-error */

static Object string_constant;     /* "This function can only be called in contexts where unknown is allowed." */

static Object Qtext;               /* text */

static Object string_constant_1;   /* "~a is also the name of a system-defined function.  The system ~
				    *              function will be used if ~a is called."
				    */

/* COMPILE-FUNCTION-DEFINITION-FOR-STACK */
Object compile_function_definition_for_stack(function_name,
	    function_definition,expression,arguments)
    Object function_name, function_definition, expression, arguments;
{
    Object name_resolution_compile_qm, unknown_allowed_var;
    Object no_item_allowed_var, byte_code_vector, byte_codes_count;
    Object byte_code_constants;
    volatile Object byte_code_body_to_return;
    Object code_body_entry, compiler_errors, compiler_warnings;
    Object new_goto_tag_counter, goto_tags_in_compilation;
    Object lexically_visible_goto_tags, lexically_visible_code_bodies;
    Object code_body_entries_in_compilation, stack_nodes_to_reclaim;
    Object compiler_free_references, collecting_free_references;
    Object gensymed_symbol, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object temp, temp_1, argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_iter_flag_, temp_2;
    Object expression_bound_local_names, unknown_allowed;
    Object known_only_compile_qm, known_only_no_item_allowed_compile_qm;
    Object unknown_no_item_allowed_compile_qm;
    Object inhibit_free_reference_recording, known_only_tag;
    Object known_and_item_tag, unknown_and_item_tag, byte_code_stream;
    Object instructions, tag;
    SI_Long arg_number;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(17);
    Object result;

    x_note_fn_call(206,0);
    SAVE_STACK();
    name_resolution_compile_qm = expression;
    unknown_allowed_var = QUNKNOWN_ALLOWED;
    no_item_allowed_var = QNO_ITEM_ALLOWED;
    byte_code_vector = Nil;
    byte_codes_count = Nil;
    byte_code_constants = Nil;
    byte_code_body_to_return = Nil;
    code_body_entry = Nil;
    if (name_resolution_compile_qm) {
	compiler_errors = Nil;
	compiler_warnings = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
		16);
	  PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
		  15);
	    remove_compiler_error_and_warning_frame_notes();
	    if (PUSH_UNWIND_PROTECT(3)) {
		new_goto_tag_counter = FIX((SI_Long)0L);
		goto_tags_in_compilation = Nil;
		lexically_visible_goto_tags = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
			14);
		  PUSH_SPECIAL_WITH_SYMBOL(Goto_tags_in_compilation,Qgoto_tags_in_compilation,goto_tags_in_compilation,
			  13);
		    PUSH_SPECIAL_WITH_SYMBOL(New_goto_tag_counter,Qnew_goto_tag_counter,new_goto_tag_counter,
			    12);
		      if (PUSH_UNWIND_PROTECT(2)) {
			  lexically_visible_code_bodies = Nil;
			  code_body_entries_in_compilation = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Code_body_entries_in_compilation,Qcode_body_entries_in_compilation,code_body_entries_in_compilation,
				  11);
			    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
				    10);
			      if (PUSH_UNWIND_PROTECT(1)) {
				  stack_nodes_to_reclaim = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Stack_nodes_to_reclaim,Qstack_nodes_to_reclaim,stack_nodes_to_reclaim,
					  9);
				    if (PUSH_UNWIND_PROTECT(0)) {
					compiler_free_references = Nil;
					collecting_free_references = T;
					PUSH_SPECIAL_WITH_SYMBOL(Collecting_free_references,Qcollecting_free_references,collecting_free_references,
						8);
					  PUSH_SPECIAL_WITH_SYMBOL(Compiler_free_references,Qcompiler_free_references,compiler_free_references,
						  7);
					    gensymed_symbol = 
						    CAR(Lexically_visible_code_bodies);
					    gensymed_symbol = 
						    make_compiler_code_body_entry_1(Nil,
						    gensymed_symbol ? 
						    position(2,
						    gensymed_symbol,
						    Code_body_entries_in_compilation) 
						    : Nil);
					    lexically_visible_code_bodies 
						    = 
						    phrase_cons(gensymed_symbol,
						    Lexically_visible_code_bodies);
					    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
						    6);
					      Code_body_entries_in_compilation 
						      = 
						      nconc2(Code_body_entries_in_compilation,
						      phrase_cons(gensymed_symbol,
						      Nil));
					      check_for_new_code_body_errors();
					      if (inlining_context_qm())
						  adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
					      outermost_stack_frame_var_binding_qm 
						      = Nil;
					      next_stack_frame_var_location 
						      = Nil;
					      stack_frame_vars_ok_in_procedure_qm 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
						      5);
						PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
							4);
						  PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
							  3);
						    lexically_visible_goto_tags 
							    = 
							    Lexically_visible_goto_tags;
						    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
							    2);
						      code_body_entry = 
							      M_CAR(Lexically_visible_code_bodies);
						      temp = 
							      phrase_cons(no_item_allowed_var,
							      generate_new_stack_arg_var_spot(FIX((SI_Long)0L),
							      Qtruth_value));
						      temp_1 = 
							      phrase_cons(unknown_allowed_var,
							      generate_new_stack_arg_var_spot(FIX((SI_Long)1L),
							      Qtruth_value));
						      argument = Nil;
						      ab_loop_list_ = 
							      arguments;
						      arg_number = 
							      IFIX(FIXNUM_ADD1(length(arguments)));
						      ab_loopvar_ = Nil;
						      ab_loopvar__1 = Nil;
						      ab_loopvar__2 = Nil;
						      ab_loop_iter_flag_ = T;
						    next_loop:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop;
						      argument = 
							      M_CAR(ab_loop_list_);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if ( 
							      !TRUEP(ab_loop_iter_flag_))
							  arg_number = 
								  arg_number 
								  - 
								  (SI_Long)1L;
						      temp_2 = argument;
						      ab_loopvar__2 = 
							      phrase_cons(phrase_cons(temp_2,
							      generate_new_stack_arg_var_spot(FIX(arg_number),
							      Qitem_or_datum)),
							      Nil);
						      if (ab_loopvar__1)
							  M_CDR(ab_loopvar__1) 
								  = 
								  ab_loopvar__2;
						      else
							  ab_loopvar_ = 
								  ab_loopvar__2;
						      ab_loopvar__1 = 
							      ab_loopvar__2;
						      ab_loop_iter_flag_ = Nil;
						      goto next_loop;
						    end_loop:
						      temp_2 = ab_loopvar_;
						      goto end_1;
						      temp_2 = Qnil;
						    end_1:;
						      expression_bound_local_names 
							      = 
							      phrase_cons(temp,
							      phrase_cons(temp_1,
							      temp_2));
						      PUSH_SPECIAL_WITH_SYMBOL(Expression_bound_local_names,Qexpression_bound_local_names,expression_bound_local_names,
							      1);
							unknown_allowed = 
								compile_stack_expression_into_nodes(name_resolution_compile_qm,
								list_constant);
							known_only_compile_qm 
								= Nil;
							known_only_no_item_allowed_compile_qm 
								= Nil;
							unknown_no_item_allowed_compile_qm 
								= Nil;
							if ( 
								!TRUEP(Compiler_errors)) 
								    {
							    inhibit_free_reference_recording 
								    = T;
							    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_free_reference_recording,Qinhibit_free_reference_recording,inhibit_free_reference_recording,
								    0);
							      unknown_no_item_allowed_compile_qm 
								      = 
								      compile_stack_expression_into_nodes(name_resolution_compile_qm,
								      list_constant_1);
							      if ( 
								      !TRUEP(Compiler_errors)) 
									  {
								  known_only_compile_qm 
									  = 
									  compile_stack_expression_into_nodes(name_resolution_compile_qm,
									  Qdatum);
								  if (Compiler_errors) 
									      {
								      clear_compiler_errors();
								      known_only_compile_qm 
									      = 
									      Nil;
								  }
								  known_only_no_item_allowed_compile_qm 
									  = 
									  compile_stack_expression_into_nodes(name_resolution_compile_qm,
									  list_constant_2);
								  if (Compiler_errors) 
									      {
								      clear_compiler_errors();
								      known_only_no_item_allowed_compile_qm 
									      = 
									      Nil;
								  }
							      }
							    POP_SPECIAL();
							}
							if ( 
								!TRUEP(Compiler_errors)) 
								    {
							    known_only_tag 
								    = 
								    generate_new_goto_tag();
							    known_and_item_tag 
								    = 
								    generate_new_goto_tag();
							    unknown_and_item_tag 
								    = 
								    generate_new_goto_tag();
							    emit_branch_or_jump_if_not_true(compile_stack_expression_into_nodes(unknown_allowed_var,
								    Qtruth_value),
								    known_only_tag);
							    emit_branch_or_jump_if_not_true(compile_stack_expression_into_nodes(no_item_allowed_var,
								    Qtruth_value),
								    unknown_and_item_tag);
							    emit_already_consed_instruction(phrase_list_2(Qreturn_from_function,
								    unknown_no_item_allowed_compile_qm));
							    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
								    unknown_and_item_tag));
							    emit_already_consed_instruction(phrase_list_2(Qreturn_from_function,
								    unknown_allowed));
							    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
								    known_only_tag));
							    emit_branch_or_jump_if_not_true(compile_stack_expression_into_nodes(no_item_allowed_var,
								    Qtruth_value),
								    known_and_item_tag);
							    if (known_only_no_item_allowed_compile_qm)
								emit_already_consed_instruction(phrase_list_2(Qreturn_from_function,
									known_only_no_item_allowed_compile_qm));
							    else {
								temp_2 = 
									compile_stack_expression_into_nodes(list_constant_3,
									Qsymbol);
								emit_already_consed_instruction(phrase_list_3(Qsignal_error,
									temp_2,
									compile_stack_expression_into_nodes(string_constant,
									Qtext)));
							    }
							    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
								    known_and_item_tag));
							    if (known_only_compile_qm)
								emit_already_consed_instruction(phrase_list_2(Qreturn_from_function,
									known_only_compile_qm));
							    else {
								temp_2 = 
									compile_stack_expression_into_nodes(list_constant_3,
									Qsymbol);
								emit_already_consed_instruction(phrase_list_3(Qsignal_error,
									temp_2,
									compile_stack_expression_into_nodes(string_constant,
									Qtext)));
							    }
							}
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					    if ( !TRUEP(Compiler_errors)) {
						byte_code_stream = 
							make_byte_code_stream_1();
						instructions = 
							nreverse(ISVREF(CAR(Code_body_entries_in_compilation),
							(SI_Long)1L));
						lexically_visible_code_bodies 
							= 
							generate_list_of_lexically_visible_code_bodies(code_body_entry);
						PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
							0);
						  emit_byte_code_vector_for_procedure(byte_code_stream,
							  instructions);
						POP_SPECIAL();
						if ( !TRUEP(Compiler_errors)) {
						    result = resolve_procedure_byte_code_addresses(1,
							    byte_code_stream);
						    MVS_2(result,
							    byte_code_vector,
							    byte_codes_count);
						}
						if ( !TRUEP(Compiler_errors))
						    byte_code_constants = 
							    make_procedure_byte_code_constants(byte_code_stream);
						reclaim_byte_code_stream_1(byte_code_stream);
					    }
					    if (Compiler_errors)
						byte_code_body_to_return = Nil;
					    else
						byte_code_body_to_return = 
							make_byte_code_body_1(byte_codes_count,
							byte_code_vector,
							byte_code_constants,
							Nil,Nil);
					    if (memq_function(function_name,
						    Built_in_functions))
						compiler_warning(3,
							string_constant_1,
							function_name,
							function_name);
					    if (byte_code_body_to_return) {
						if (Compiler_free_references)
						    Compiler_free_references 
							    = 
							    remove_spurious_free_references_for_function_compilation(Compiler_free_references);
						install_free_references_in_byte_code_body(byte_code_body_to_return,
							Compiler_free_references);
					    }
					  POP_SPECIAL();
					POP_SPECIAL();
				    }
				    POP_UNWIND_PROTECT(0);
				    reclaim_stack_list_of_nodes(Stack_nodes_to_reclaim);
				    CONTINUE_UNWINDING(0);
				  POP_SPECIAL();
			      }
			      POP_UNWIND_PROTECT(1);
			      code_body_entry = Nil;
			      ab_loop_list_ = Code_body_entries_in_compilation;
			    next_loop_1:
			      if ( !TRUEP(ab_loop_list_))
				  goto end_loop_1;
			      code_body_entry = M_CAR(ab_loop_list_);
			      ab_loop_list_ = M_CDR(ab_loop_list_);
			      reclaim_compiler_code_body_entry_1(code_body_entry);
			      goto next_loop_1;
			    end_loop_1:;
			      CONTINUE_UNWINDING(1);
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		      POP_UNWIND_PROTECT(2);
		      tag = Nil;
		      ab_loop_list_ = Goto_tags_in_compilation;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      tag = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      reclaim_goto_tag_entry_1(tag);
		      goto next_loop_2;
		    end_loop_2:;
		      CONTINUE_UNWINDING(2);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(3);
	    add_compiler_error_and_warning_frame_notes();
	    CONTINUE_UNWINDING(3);
	  POP_SPECIAL();
	POP_SPECIAL();
	analyze_compiled_items_for_consistency(function_name);
	RESTORE_STACK();
	return VALUES_1(byte_code_body_to_return);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* REMOVE-SPURIOUS-FREE-REFERENCES-FOR-FUNCTION-COMPILATION */
Object remove_spurious_free_references_for_function_compilation(reference_list)
    Object reference_list;
{
    Object references_to_delete, reference, ab_loop_list_, ref;

    x_note_fn_call(206,1);
    references_to_delete = Nil;
    reference = Nil;
    ab_loop_list_ = reference_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (redundant_parameter_free_reference_qm(reference,reference_list))
	references_to_delete = phrase_cons(reference,references_to_delete);
    goto next_loop;
  end_loop:;
    ref = Nil;
    ab_loop_list_ = references_to_delete;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ref = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reference_list = ldelete(6,ref,reference_list,Ktest,
	    SYMBOL_FUNCTION(Qeq),Kcount,FIX((SI_Long)1L));
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(reference_list);
}

static Object QRECACHE_NEEDED;     /* |recache-needed| */

static Object Qab_let;             /* let */

static Object Qassign_local_var;   /* assign-local-var */

static Object list_constant_4;     /* # */

static Object Qpause;              /* pause */

static Object Qexecute_simulation_formula;  /* execute-simulation-formula */

static Object Qcomplete_simulation_variable_evaluation;  /* complete-simulation-variable-evaluation */

/* COMPILE-SIMULATION-FORMULA-FOR-STACK */
Object compile_simulation_formula_for_stack(expression,focus_name_qm,
	    focus_class_name_qm,initial_value_expression_qm)
    Object expression, focus_name_qm, focus_class_name_qm;
    Object initial_value_expression_qm;
{
    Object recaching_needed_var, result_var_spot;
    Object number_of_bindings_cached_var_spot, focus_type_specification_qm;
    Object byte_code_vector, byte_codes_count, byte_code_constants;
    Object byte_code_body_to_return, cached_bindings, uncached_bindings;
    Object environment, code_body_entry, compiler_errors, compiler_warnings;
    Object new_goto_tag_counter, goto_tags_in_compilation;
    Object lexically_visible_goto_tags, lexically_visible_code_bodies;
    Object code_body_entries_in_compilation, stack_nodes_to_reclaim;
    Object compiler_free_references, collecting_free_references;
    Object gensymed_symbol, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object end_of_recache_tag, unknown_tag, binding_list, inner_expression;
    Object binding_var_spot, binding, designation, ab_loop_list_;
    Object ab_loop_desetq_, temp, byte_code_stream, instructions, temp_1;
    Object temp_2, tag;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(15);
    Object result;

    x_note_fn_call(206,2);
    SAVE_STACK();
    recaching_needed_var = QRECACHE_NEEDED;
    result_var_spot = Nil;
    number_of_bindings_cached_var_spot = Nil;
    focus_type_specification_qm = focus_class_name_qm ? 
	    make_class_type_specification(focus_class_name_qm) : Nil;
    byte_code_vector = Nil;
    byte_codes_count = Nil;
    byte_code_constants = Nil;
    byte_code_body_to_return = Nil;
    cached_bindings = Nil;
    uncached_bindings = Nil;
    environment = Nil;
    code_body_entry = Nil;
    compiler_errors = Nil;
    compiler_warnings = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
	    14);
      PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
	      13);
	remove_compiler_error_and_warning_frame_notes();
	if (PUSH_UNWIND_PROTECT(3)) {
	    new_goto_tag_counter = FIX((SI_Long)0L);
	    goto_tags_in_compilation = Nil;
	    lexically_visible_goto_tags = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		    12);
	      PUSH_SPECIAL_WITH_SYMBOL(Goto_tags_in_compilation,Qgoto_tags_in_compilation,goto_tags_in_compilation,
		      11);
		PUSH_SPECIAL_WITH_SYMBOL(New_goto_tag_counter,Qnew_goto_tag_counter,new_goto_tag_counter,
			10);
		  if (PUSH_UNWIND_PROTECT(2)) {
		      lexically_visible_code_bodies = Nil;
		      code_body_entries_in_compilation = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Code_body_entries_in_compilation,Qcode_body_entries_in_compilation,code_body_entries_in_compilation,
			      9);
			PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
				8);
			  if (PUSH_UNWIND_PROTECT(1)) {
			      stack_nodes_to_reclaim = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Stack_nodes_to_reclaim,Qstack_nodes_to_reclaim,stack_nodes_to_reclaim,
				      7);
				if (PUSH_UNWIND_PROTECT(0)) {
				    compiler_free_references = Nil;
				    collecting_free_references = T;
				    PUSH_SPECIAL_WITH_SYMBOL(Collecting_free_references,Qcollecting_free_references,collecting_free_references,
					    6);
				      PUSH_SPECIAL_WITH_SYMBOL(Compiler_free_references,Qcompiler_free_references,compiler_free_references,
					      5);
					gensymed_symbol = 
						CAR(Lexically_visible_code_bodies);
					gensymed_symbol = 
						make_compiler_code_body_entry_1(Nil,
						gensymed_symbol ? 
						position(2,gensymed_symbol,
						Code_body_entries_in_compilation) 
						: Nil);
					lexically_visible_code_bodies = 
						phrase_cons(gensymed_symbol,
						Lexically_visible_code_bodies);
					PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
						4);
					  Code_body_entries_in_compilation 
						  = 
						  nconc2(Code_body_entries_in_compilation,
						  phrase_cons(gensymed_symbol,
						  Nil));
					  check_for_new_code_body_errors();
					  if (inlining_context_qm())
					      adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
					  outermost_stack_frame_var_binding_qm 
						  = Nil;
					  next_stack_frame_var_location = Nil;
					  stack_frame_vars_ok_in_procedure_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
						  3);
					    PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
						    2);
					      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
						      1);
						lexically_visible_goto_tags 
							= 
							Lexically_visible_goto_tags;
						PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
							0);
						  code_body_entry = 
							  M_CAR(Lexically_visible_code_bodies);
						  generate_new_variable_spot(2,
							  Qtruth_value,
							  recaching_needed_var);
						  result_var_spot = 
							  generate_new_variable_spot(1,
							  Qdatum);
						  number_of_bindings_cached_var_spot 
							  = 
							  generate_new_variable_spot(1,
							  Qnumber);
						  if (focus_name_qm)
						      generate_new_variable_spot(2,
							      focus_type_specification_qm,
							      focus_name_qm);
						  if ( 
							  !TRUEP(initial_value_expression_qm)) 
							      {
						      end_of_recache_tag = 
							      generate_new_goto_tag();
						      unknown_tag = 
							      generate_new_goto_tag();
						      emit_branch_or_jump_if_not_true(compile_stack_expression_into_nodes(recaching_needed_var,
							      Qtruth_value),
							      end_of_recache_tag);
						    next_loop:
						      if ( 
							      !(CONSP(expression) 
							      && 
							      EQ(CAR(expression),
							      Qab_let)))
							  goto end_loop;
						      binding_list = 
							      SECOND(expression);
						      inner_expression = 
							      THIRD(expression);
						      binding_var_spot = Nil;
						      binding = Nil;
						      designation = Nil;
						      ab_loop_list_ = 
							      binding_list;
						      ab_loop_desetq_ = Nil;
						    next_loop_1:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_1;
						      ab_loop_desetq_ = 
							      M_CAR(ab_loop_list_);
						      binding = 
							      CAR(ab_loop_desetq_);
						      temp = 
							      CDR(ab_loop_desetq_);
						      designation = CAR(temp);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if (simulation_designation_can_be_cached_qm(designation,
							      cached_bindings,
							      uncached_bindings)) 
								  {
							  cached_bindings 
								  = 
								  phrase_cons(phrase_list_2(binding,
								  designation),
								  cached_bindings);
							  binding_var_spot 
								  = 
								  generate_new_variable_spot(2,
								  Qitem_or_datum,
								  binding);
							  temp = 
								  binding_var_spot;
							  emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
								  temp,
								  compile_stack_expression_into_nodes(designation,
								  list_constant_4)));
						      }
						      else
							  uncached_bindings 
								  = 
								  nconc2(uncached_bindings,
								  phrase_cons(phrase_list_2(binding,
								  designation),
								  Nil));
						      goto next_loop_1;
						    end_loop_1:;
						      expression = 
							      inner_expression;
						      goto next_loop;
						    end_loop:
						      temp = 
							      number_of_bindings_cached_var_spot;
						      emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
							      temp,
							      compile_stack_expression_into_nodes(length(cached_bindings),
							      Qinteger)));
						      emit_already_consed_instruction(phrase_cons(Qpause,
							      Nil));
						      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
							      end_of_recache_tag));
						      binding = Nil;
						      designation = Nil;
						      ab_loop_list_ = 
							      uncached_bindings;
						      binding_var_spot = Nil;
						      ab_loop_desetq_ = Nil;
						    next_loop_2:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_2;
						      ab_loop_desetq_ = 
							      M_CAR(ab_loop_list_);
						      binding = 
							      CAR(ab_loop_desetq_);
						      temp = 
							      CDR(ab_loop_desetq_);
						      designation = CAR(temp);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      binding_var_spot = 
							      generate_new_variable_spot(2,
							      Qitem_or_datum,
							      binding);
						      if (designation) {
							  temp = 
								  binding_var_spot;
							  emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
								  temp,
								  compile_stack_expression_into_nodes(designation,
								  list_constant_4)));
						      }
						      goto next_loop_2;
						    end_loop_2:;
						      temp = 
							      compile_stack_expression_into_nodes(expression,
							      list_constant);
						      emit_already_consed_instruction(phrase_list_4(Qexecute_simulation_formula,
							      temp,
							      result_var_spot,
							      unknown_tag));
						      emit_already_consed_instruction(phrase_list_2(Qcomplete_simulation_variable_evaluation,
							      T));
						      emit_already_consed_instruction(phrase_cons(Qpause,
							      Nil));
						      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
							      unknown_tag));
						      emit_already_consed_instruction(phrase_list_2(Qcomplete_simulation_variable_evaluation,
							      Nil));
						      emit_already_consed_instruction(phrase_cons(Qpause,
							      Nil));
						  }
						  else {
						      unknown_tag = 
							      generate_new_goto_tag();
						      temp = 
							      compile_stack_expression_into_nodes(expression,
							      list_constant);
						      emit_already_consed_instruction(phrase_list_4(Qexecute_simulation_formula,
							      temp,
							      result_var_spot,
							      unknown_tag));
						      emit_already_consed_instruction(phrase_list_2(Qcomplete_simulation_variable_evaluation,
							      T));
						      emit_already_consed_instruction(phrase_cons(Qpause,
							      Nil));
						      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
							      unknown_tag));
						      emit_already_consed_instruction(phrase_list_2(Qcomplete_simulation_variable_evaluation,
							      Nil));
						      emit_already_consed_instruction(phrase_cons(Qpause,
							      Nil));
						  }
						  environment = 
							  ISVREF(CAR(Lexically_visible_code_bodies),
							  (SI_Long)3L);
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
					if ( !TRUEP(Compiler_errors)) {
					    byte_code_stream = 
						    make_byte_code_stream_1();
					    instructions = 
						    nreverse(ISVREF(CAR(Code_body_entries_in_compilation),
						    (SI_Long)1L));
					    lexically_visible_code_bodies 
						    = 
						    generate_list_of_lexically_visible_code_bodies(code_body_entry);
					    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
						    0);
					      emit_byte_code_vector_for_procedure(byte_code_stream,
						      instructions);
					    POP_SPECIAL();
					    if ( !TRUEP(Compiler_errors)) {
						result = resolve_procedure_byte_code_addresses(1,
							byte_code_stream);
						MVS_2(result,
							byte_code_vector,
							byte_codes_count);
					    }
					    if ( !TRUEP(Compiler_errors))
						byte_code_constants = 
							make_procedure_byte_code_constants(byte_code_stream);
					    reclaim_byte_code_stream_1(byte_code_stream);
					}
					if (Compiler_errors)
					    byte_code_body_to_return = Nil;
					else {
					    temp_1 = byte_codes_count;
					    temp_2 = byte_code_vector;
					    temp = byte_code_constants;
					    byte_code_body_to_return = 
						    make_byte_code_body_1(temp_1,
						    temp_2,temp,
						    convert_description_list_to_managed_array(1,
						    environment),Nil);
					    install_free_references_in_byte_code_body(byte_code_body_to_return,
						    Compiler_free_references);
					}
					SAVE_VALUES(VALUES_1(byte_code_body_to_return));
				      POP_SPECIAL();
				    POP_SPECIAL();
				}
				POP_UNWIND_PROTECT(0);
				reclaim_stack_list_of_nodes(Stack_nodes_to_reclaim);
				CONTINUE_UNWINDING(0);
			      POP_SPECIAL();
			  }
			  POP_UNWIND_PROTECT(1);
			  code_body_entry = Nil;
			  ab_loop_list_ = Code_body_entries_in_compilation;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_3;
			  code_body_entry = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  reclaim_compiler_code_body_entry_1(code_body_entry);
			  goto next_loop_3;
			end_loop_3:;
			  CONTINUE_UNWINDING(1);
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  POP_UNWIND_PROTECT(2);
		  tag = Nil;
		  ab_loop_list_ = Goto_tags_in_compilation;
		next_loop_4:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_4;
		  tag = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  reclaim_goto_tag_entry_1(tag);
		  goto next_loop_4;
		end_loop_4:;
		  CONTINUE_UNWINDING(2);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(3);
	add_compiler_error_and_warning_frame_notes();
	CONTINUE_UNWINDING(3);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qrole_server;        /* role-server */

/* SIMULATION-DESIGNATION-CAN-BE-CACHED? */
Object simulation_designation_can_be_cached_qm(designation,alist,
	    uncacheable_alist)
    Object designation, alist, uncacheable_alist;
{
    Object role, domain_qm, temp, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(206,3);
    if ( !TRUEP(designation))
	return VALUES_1(Nil);
    else if (CONSP(designation)) {
	if (EQ(CAR(designation),Qthe)) {
	    role = SECOND(designation);
	    domain_qm = THIRD(designation);
	    if (CONSP(role)) {
		if (role_can_be_cached_qm(CAR(role)))
		    return simulation_designation_can_be_cached_qm(domain_qm,
			    alist,uncacheable_alist);
		else
		    return VALUES_1(Nil);
	    }
	    else if ( !TRUEP(domain_qm)) {
		temp = assq_function(role,alist);
		if (temp)
		    return VALUES_1(temp);
		else {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = role;
		    key_hash_value = SXHASH_SYMBOL_1(role) & 
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = role;
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
			gensymed_symbol = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp,gensymed_symbol_1);
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
		  next_loop_3:
		    if (level < ab_loop_bind_)
			goto end_loop_3;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		      next_loop_6:
			if (level < ab_loop_bind_)
			    goto end_loop_6;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_7:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_8:
			if ( !TRUEP(marked))
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
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
		      next_loop_9:
			if (level < ab_loop_bind_)
			    goto end_loop_9;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_10:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_11:
			if ( !TRUEP(marked))
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
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
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    if (gensymed_symbol)
			return VALUES_1(ISVREF(gensymed_symbol,(SI_Long)16L));
		    else
			return VALUES_1(Nil);
		}
	    }
	    else if ( 
		    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(role),
		    Qrole_server)) || role_can_be_cached_qm(role))
		return simulation_designation_can_be_cached_qm(domain_qm,
			alist,uncacheable_alist);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1( !TRUEP(assq_function(designation,
		uncacheable_alist)) ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Conclude_parent_attribute_bindings, Qconclude_parent_attribute_bindings);

DEFINE_VARIABLE_WITH_SYMBOL(Local_name_to_cached_designation_alist, Qlocal_name_to_cached_designation_alist);

DEFINE_VARIABLE_WITH_SYMBOL(Rule_certainty_var, Qrule_certainty_var);

DEFINE_VARIABLE_WITH_SYMBOL(Rule_expiration_var, Qrule_expiration_var);

DEFINE_VARIABLE_WITH_SYMBOL(Conclude_attribute_binding_symbol_counter, Qconclude_attribute_binding_symbol_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Conclude_attribute_binding_listed_next_symbol, Qconclude_attribute_binding_listed_next_symbol);

DEFINE_VARIABLE_WITH_SYMBOL(Conclude_attribute_binding_symbol_supply, Qconclude_attribute_binding_symbol_supply);

static Object string_constant_2;   /* "CONCLUDE-ATTRIBUTE-BINDING" */

/* INTERNED-CONCLUDE-ATTRIBUTE-BINDING-SYMBOL */
Object interned_conclude_attribute_binding_symbol()
{
    Object temp, cdr_arg, cdr_new_value;
    XDeclare_area(1);

    x_note_fn_call(206,4);
    if (ATOM(Conclude_attribute_binding_listed_next_symbol)) {
	atomic_incff_symval(Qconclude_attribute_binding_symbol_counter,
		FIX((SI_Long)1L));
	if (PUSH_AREA(Dynamic_area,0))
	    Conclude_attribute_binding_listed_next_symbol = 
		    LIST_1(intern(format((SI_Long)4L,Nil,"~A-~D",
		    string_constant_2,
		    Conclude_attribute_binding_symbol_counter),_));
	POP_AREA(0);
    }
    if (CDR(Conclude_attribute_binding_listed_next_symbol)) {
	temp = CAR(Conclude_attribute_binding_listed_next_symbol);
	atomic_incff_symval(Qconclude_attribute_binding_symbol_counter,
		FIX((SI_Long)1L));
	Conclude_attribute_binding_listed_next_symbol = 
		CDR(Conclude_attribute_binding_listed_next_symbol);
	return VALUES_1(temp);
    }
    else {
	temp = CAR(Conclude_attribute_binding_listed_next_symbol);
	atomic_incff_symval(Qconclude_attribute_binding_symbol_counter,
		FIX((SI_Long)1L));
	cdr_arg = Conclude_attribute_binding_listed_next_symbol;
	if (PUSH_AREA(Dynamic_area,0))
	    cdr_new_value = LIST_1(intern(format((SI_Long)4L,Nil,"~A-~D",
		    string_constant_2,
		    Conclude_attribute_binding_symbol_counter),_));
	POP_AREA(0);
	M_CDR(cdr_arg) = cdr_new_value;
	Conclude_attribute_binding_listed_next_symbol = 
		CDR(Conclude_attribute_binding_listed_next_symbol);
	return VALUES_1(temp);
    }
}

static Object Qallocate_stack_frame_vars;  /* allocate-stack-frame-vars */

static Object Qopen_wake_up_collection;  /* open-wake-up-collection */

static Object Qrule_let;           /* rule-let */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qin_order;           /* in-order */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qbranch_if_known;    /* branch-if-known */

static Object list_constant_9;     /* # */

static Object Qexecute_antecedent;  /* execute-antecedent */

static Object Qset_wake_ups;       /* set-wake-ups */

static Object Qclose_wake_up_collection;  /* close-wake-up-collection */

static Object Qcomplete_rule_instance;  /* complete-rule-instance */

static Object Qbegin_activity;     /* begin-activity */

static Object Qbegin_rule_actions;  /* begin-rule-actions */

static Object Qrule_maximum_received_value_count;  /* rule-maximum-received-value-count */

static Object Qrule_return_value_position;  /* rule-return-value-position */

static Object Qrule_byte_code_body;  /* rule-byte-code-body */

static Object Qrule_context_length;  /* rule-context-length */

static Object Qrule_environment_length;  /* rule-environment-length */

/* COMPILE-RULE-FOR-STACK */
Object compile_rule_for_stack(rule,parse_and_compilations)
    Object rule, parse_and_compilations;
{
    Object rule_certainty_var, certainty_var_spot, rule_expiration_var;
    Object expiration_var_spot, byte_code_vector, byte_codes_count;
    Object byte_code_constants, byte_code_body_to_return, initial_environment;
    Object compiled_rule_body;
    volatile Object context_list;
    Object universal_context, rule_bindings_executed_qm, restart_tag;
    Object action_list, in_order_qm, context_length;
    Object push_stack_frame_vars_instruction;
    volatile Object environment;
    volatile Object environment_length;
    Object local_name_to_cached_designation_alist;
    Object conclude_parent_attribute_bindings;
    Object antecedent_or_bindings_could_be_unknown_qm, context_element;
    Object ab_loop_list_, quantifier, role, binding, domain_qm;
    Object cached_designation, type_specification, vars, ab_loopvar_;
    Object ab_loopvar__1, cached_bindings, ab_loopvar__2, temp;
    Object compiler_errors, compiler_warnings, new_goto_tag_counter;
    Object goto_tags_in_compilation, lexically_visible_goto_tags;
    Object lexically_visible_code_bodies, code_body_entries_in_compilation;
    Object stack_nodes_to_reclaim, compiler_free_references;
    Object collecting_free_references;
    Object conclude_attribute_binding_symbol_counter;
    Object conclude_attribute_binding_listed_next_symbol, gensymed_symbol;
    Object outermost_stack_frame_var_binding_qm, next_stack_frame_var_location;
    Object stack_frame_vars_ok_in_procedure_qm, binding_list, inner_body;
    Object designation, var_spot, ab_loop_desetq_, compiled_binding_expression;
    Object antecedent, true_tag, close_rule_tag, unknown_tag;
    Object compiled_binding_designation, known_rule_let_tag;
    Object compiled_logical_expression, gensymed_symbol_1, gensymed_symbol_2;
    Object known_tag, prolog_stream, epilog_stream, action_count;
    Object second_new_value, byte_code_stream, code_body_entry, instructions;
    Object maximum_received_values, temp_1, temp_2, tag;
    Declare_stack_pointer;
    Declare_catch(5);
    Declare_special(22);
    Object result;

    x_note_fn_call(206,5);
    SAVE_STACK();
    rule_certainty_var = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Rule_certainty_var,Qrule_certainty_var,rule_certainty_var,
	    21);
      certainty_var_spot = Nil;
      rule_expiration_var = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Rule_expiration_var,Qrule_expiration_var,rule_expiration_var,
	      20);
	expiration_var_spot = Nil;
	byte_code_vector = Nil;
	byte_codes_count = Nil;
	byte_code_constants = Nil;
	byte_code_body_to_return = Nil;
	initial_environment = Nil;
	compiled_rule_body = SECOND(parse_and_compilations);
	context_list = CDDR(parse_and_compilations);
	universal_context = CAR(context_list);
	rule_bindings_executed_qm = Nil;
	restart_tag = Nil;
	action_list = Nil;
	in_order_qm = Nil;
	context_length = length(CDR(universal_context));
	push_stack_frame_vars_instruction = 
		phrase_list_2(Qallocate_stack_frame_vars,FIX((SI_Long)0L));
	environment = Nil;
	environment_length = Nil;
	local_name_to_cached_designation_alist = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Local_name_to_cached_designation_alist,Qlocal_name_to_cached_designation_alist,local_name_to_cached_designation_alist,
		19);
	  conclude_parent_attribute_bindings = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Conclude_parent_attribute_bindings,Qconclude_parent_attribute_bindings,conclude_parent_attribute_bindings,
		  18);
	    antecedent_or_bindings_could_be_unknown_qm = Nil;
	    context_element = Nil;
	    ab_loop_list_ = CDR(universal_context);
	    quantifier = Nil;
	    role = Nil;
	    binding = Nil;
	    domain_qm = Nil;
	    cached_designation = Nil;
	    type_specification = Nil;
	    vars = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    cached_bindings = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    context_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    quantifier = CAR(context_element);
	    temp = CDR(context_element);
	    role = CAR(temp);
	    temp = CDR(context_element);
	    temp = CDR(temp);
	    binding = CAR(temp);
	    temp = CDR(context_element);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    domain_qm = CAR(temp);
	    cached_designation = domain_qm ? phrase_list_3(quantifier,role,
		    domain_qm) : phrase_list_2(quantifier,role);
	    temp = type_specification_of_designation(cached_designation);
	    if (temp);
	    else
		temp = Qitem_or_datum;
	    type_specification = temp;
	    ab_loopvar__1 = phrase_cons(phrase_list_3(binding,Ktype,
		    type_specification),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		vars = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    ab_loopvar__1 = phrase_cons(phrase_list_2(binding,
		    cached_designation),Nil);
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__1;
	    else
		cached_bindings = ab_loopvar__1;
	    ab_loopvar__2 = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    initial_environment = vars;
	    Local_name_to_cached_designation_alist = cached_bindings;
	    compiler_errors = Nil;
	    compiler_warnings = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
		    17);
	      PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
		      16);
		remove_compiler_error_and_warning_frame_notes();
		if (PUSH_UNWIND_PROTECT(4)) {
		    new_goto_tag_counter = FIX((SI_Long)0L);
		    goto_tags_in_compilation = Nil;
		    lexically_visible_goto_tags = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
			    15);
		      PUSH_SPECIAL_WITH_SYMBOL(Goto_tags_in_compilation,Qgoto_tags_in_compilation,goto_tags_in_compilation,
			      14);
			PUSH_SPECIAL_WITH_SYMBOL(New_goto_tag_counter,Qnew_goto_tag_counter,new_goto_tag_counter,
				13);
			  if (PUSH_UNWIND_PROTECT(3)) {
			      lexically_visible_code_bodies = Nil;
			      code_body_entries_in_compilation = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Code_body_entries_in_compilation,Qcode_body_entries_in_compilation,code_body_entries_in_compilation,
				      12);
				PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
					11);
				  if (PUSH_UNWIND_PROTECT(2)) {
				      stack_nodes_to_reclaim = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Stack_nodes_to_reclaim,Qstack_nodes_to_reclaim,stack_nodes_to_reclaim,
					      10);
					if (PUSH_UNWIND_PROTECT(1)) {
					    compiler_free_references = Nil;
					    collecting_free_references = T;
					    PUSH_SPECIAL_WITH_SYMBOL(Collecting_free_references,Qcollecting_free_references,collecting_free_references,
						    9);
					      PUSH_SPECIAL_WITH_SYMBOL(Compiler_free_references,Qcompiler_free_references,compiler_free_references,
						      8);
						conclude_attribute_binding_symbol_counter 
							= FIX((SI_Long)1L);
						conclude_attribute_binding_listed_next_symbol 
							= 
							Conclude_attribute_binding_symbol_supply;
						PUSH_SPECIAL_WITH_SYMBOL(Conclude_attribute_binding_listed_next_symbol,Qconclude_attribute_binding_listed_next_symbol,conclude_attribute_binding_listed_next_symbol,
							7);
						  PUSH_SPECIAL_WITH_SYMBOL(Conclude_attribute_binding_symbol_counter,Qconclude_attribute_binding_symbol_counter,conclude_attribute_binding_symbol_counter,
							  6);
						    gensymed_symbol = 
							    CAR(Lexically_visible_code_bodies);
						    temp = initial_environment;
						    gensymed_symbol = 
							    make_compiler_code_body_entry_1(temp,
							    gensymed_symbol 
							    ? position(2,
							    gensymed_symbol,
							    Code_body_entries_in_compilation) 
							    : Nil);
						    lexically_visible_code_bodies 
							    = 
							    phrase_cons(gensymed_symbol,
							    Lexically_visible_code_bodies);
						    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
							    5);
						      Code_body_entries_in_compilation 
							      = 
							      nconc2(Code_body_entries_in_compilation,
							      phrase_cons(gensymed_symbol,
							      Nil));
						      check_for_new_code_body_errors();
						      if (inlining_context_qm())
							  adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
						      outermost_stack_frame_var_binding_qm 
							      = Nil;
						      next_stack_frame_var_location 
							      = Nil;
						      stack_frame_vars_ok_in_procedure_qm 
							      = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
							      4);
							PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
								3);
							  PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
								  2);
							    lexically_visible_goto_tags 
								    = 
								    Lexically_visible_goto_tags;
							    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
								    1);
							      gensymed_symbol 
								      = 
								      Next_stack_frame_var_location;
							      outermost_stack_frame_var_binding_qm 
								      =  
								      !TRUEP(gensymed_symbol) 
								      ? T :
								       Nil;
							      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
								      0);
								if (PUSH_UNWIND_PROTECT(0)) 
									    {
								    if ( 
									    !TRUEP(gensymed_symbol))
									Next_stack_frame_var_location 
										= 
										FIX((SI_Long)0L);
								    restart_tag 
									    = 
									    generate_new_goto_tag();
								    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
									    restart_tag));
								    emit_already_consed_instruction(push_stack_frame_vars_instruction);
								    emit_already_consed_instruction(phrase_cons(Qopen_wake_up_collection,
									    Nil));
								    binding_list 
									    = 
									    Nil;
								    inner_body 
									    = 
									    Nil;
								  next_loop_1:
								    if ( 
									    !EQ(CAR(compiled_rule_body),
									    Qrule_let))
									goto end_loop_1;
								    binding_list 
									    = 
									    SECOND(compiled_rule_body);
								    inner_body 
									    = 
									    THIRD(compiled_rule_body);
								    rule_bindings_executed_qm 
									    = 
									    T;
								    binding 
									    = 
									    Nil;
								    designation 
									    = 
									    Nil;
								    ab_loop_list_ 
									    = 
									    binding_list;
								    var_spot 
									    = 
									    Nil;
								    ab_loop_desetq_ 
									    = 
									    Nil;
								  next_loop_2:
								    if ( 
									    !TRUEP(ab_loop_list_))
									goto end_loop_2;
								    ab_loop_desetq_ 
									    = 
									    M_CAR(ab_loop_list_);
								    binding 
									    = 
									    CAR(ab_loop_desetq_);
								    temp = 
									    CDR(ab_loop_desetq_);
								    designation 
									    = 
									    CAR(temp);
								    ab_loop_list_ 
									    = 
									    M_CDR(ab_loop_list_);
								    temp = 
									    type_specification_of_designation(designation);
								    if (temp);
								    else
									temp 
										= 
										Qitem_or_datum;
								    var_spot 
									    = 
									    generate_new_variable_spot(2,
									    temp,
									    binding);
								    if (designation) 
										{
									Local_name_to_cached_designation_alist 
										= 
										phrase_cons(phrase_list_2(binding,
										designation),
										Local_name_to_cached_designation_alist);
									compiled_binding_expression 
										= 
										compile_stack_expression_into_nodes(designation,
										list_constant_5);
									temp 
										= 
										antecedent_or_bindings_could_be_unknown_qm;
									if (temp);
									else
									    temp 
										    = 
										     
										    !TRUEP(type_specification_not_subtype_p(list_constant_6,
										    ISVREF(compiled_binding_expression,
										    (SI_Long)6L))) 
										    ?
										     T : Nil;
									antecedent_or_bindings_could_be_unknown_qm 
										= 
										temp;
									emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
										var_spot,
										compiled_binding_expression));
								    }
								    goto next_loop_2;
								  end_loop_2:;
								    compiled_rule_body 
									    = 
									    inner_body;
								    goto next_loop_1;
								  end_loop_1:;
								    antecedent 
									    = 
									    SECOND(compiled_rule_body);
								    true_tag 
									    = 
									    generate_new_goto_tag();
								    close_rule_tag 
									    = 
									    generate_new_goto_tag();
								    unknown_tag 
									    = 
									    generate_new_goto_tag();
								    action_list 
									    = 
									    THIRD(compiled_rule_body);
								    in_order_qm 
									    = 
									    EQ(CAR(action_list),
									    Qin_order) 
									    ?
									     T : Nil;
								    action_list 
									    = 
									    CDR(action_list);
								    action_list 
									    = 
									    rewrite_conclude_actions_in_action_list(action_list,
									    in_order_qm);
								    binding 
									    = 
									    Nil;
								    designation 
									    = 
									    Nil;
								    ab_loop_list_ 
									    = 
									    Conclude_parent_attribute_bindings;
								    compiled_binding_designation 
									    = 
									    Nil;
								    ab_loop_desetq_ 
									    = 
									    Nil;
								  next_loop_3:
								    if ( 
									    !TRUEP(ab_loop_list_))
									goto end_loop_3;
								    ab_loop_desetq_ 
									    = 
									    M_CAR(ab_loop_list_);
								    binding 
									    = 
									    CAR(ab_loop_desetq_);
								    temp = 
									    CDR(ab_loop_desetq_);
								    designation 
									    = 
									    CAR(temp);
								    ab_loop_list_ 
									    = 
									    M_CDR(ab_loop_list_);
								    compiled_binding_designation 
									    = 
									    compile_stack_expression_into_nodes(designation,
									    list_constant_7);
								    temp = 
									    antecedent_or_bindings_could_be_unknown_qm;
								    if (temp);
								    else
									temp 
										= 
										 
										!TRUEP(type_specification_not_subtype_p(list_constant_6,
										ISVREF(compiled_binding_designation,
										(SI_Long)6L))) 
										?
										 T : Nil;
								    antecedent_or_bindings_could_be_unknown_qm 
									    = 
									    temp;
								    temp = 
									    type_specification_of_designation(designation);
								    if (temp);
								    else
									temp 
										= 
										list_constant_8;
								    temp = 
									    generate_new_variable_spot(2,
									    temp,
									    binding);
								    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
									    temp,
									    compiled_binding_designation));
								    goto next_loop_3;
								  end_loop_3:;
								    if (rule_bindings_executed_qm 
									    && 
									    antecedent_or_bindings_could_be_unknown_qm) 
										{
									known_rule_let_tag 
										= 
										generate_new_goto_tag();
									emit_already_consed_instruction(phrase_list_2(Qbranch_if_known,
										known_rule_let_tag));
									emit_branch_or_jump(unknown_tag);
									emit_already_consed_instruction(phrase_list_2(Qtag_statement,
										known_rule_let_tag));
								    }
								    if (Rule_certainty_var)
									certainty_var_spot 
										= 
										generate_new_variable_spot(2,
										Qtruth_value,
										Rule_certainty_var);
								    if (Rule_expiration_var)
									expiration_var_spot 
										= 
										generate_new_variable_spot(2,
										Qdatum,
										Rule_expiration_var);
								    compiled_logical_expression 
									    = 
									    compile_stack_expression_into_nodes(antecedent,
									    list_constant_9);
								    temp = 
									    antecedent_or_bindings_could_be_unknown_qm;
								    if (temp);
								    else
									temp 
										= 
										 
										!TRUEP(type_specification_not_subtype_p(list_constant_6,
										ISVREF(compiled_logical_expression,
										(SI_Long)6L))) 
										?
										 T : Nil;
								    antecedent_or_bindings_could_be_unknown_qm 
									    = 
									    temp;
								    if (antecedent_or_bindings_could_be_unknown_qm) 
										{
									gensymed_symbol_1 
										= 
										make_phrase_list(FIX((SI_Long)7L));
									gensymed_symbol_2 
										= 
										gensymed_symbol_1;
									M_CAR(gensymed_symbol_2) 
										= 
										Qexecute_antecedent;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										compiled_logical_expression;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										certainty_var_spot;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										expiration_var_spot;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										true_tag;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										close_rule_tag;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										unknown_tag;
									emit_already_consed_instruction(gensymed_symbol_1);
								    }
								    else {
									gensymed_symbol_1 
										= 
										make_phrase_list(FIX((SI_Long)6L));
									gensymed_symbol_2 
										= 
										gensymed_symbol_1;
									M_CAR(gensymed_symbol_2) 
										= 
										Qexecute_antecedent;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										compiled_logical_expression;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										certainty_var_spot;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										expiration_var_spot;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										true_tag;
									gensymed_symbol_2 
										= 
										M_CDR(gensymed_symbol_2);
									M_CAR(gensymed_symbol_2) 
										= 
										close_rule_tag;
									emit_already_consed_instruction(gensymed_symbol_1);
								    }
								    if (antecedent_or_bindings_could_be_unknown_qm) 
										{
									emit_already_consed_instruction(phrase_list_2(Qtag_statement,
										unknown_tag));
									emit_already_consed_instruction(phrase_cons(Qset_wake_ups,
										Nil));
									emit_already_consed_instruction(phrase_cons(Qclose_wake_up_collection,
										Nil));
									emit_already_consed_instruction(phrase_list_2(Qcomplete_rule_instance,
										Nil));
									emit_branch_or_jump(restart_tag);
								    }
								    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
									    true_tag));
								    if (in_order_qm) 
										{
									emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
										FIX((SI_Long)64L)));
									emit_already_consed_instruction(phrase_cons(Qbegin_rule_actions,
										Nil));
									compile_in_order_actions(action_list,
										expiration_var_spot,
										push_stack_frame_vars_instruction);
								    }
								    else {
									known_tag 
										= 
										generate_new_goto_tag();
									prolog_stream 
										= 
										make_pseudo_instruction_stream_1();
									epilog_stream 
										= 
										make_pseudo_instruction_stream_1();
									action_count 
										= 
										length(action_list);
									compile_simultaneous_actions(action_list,
										prolog_stream,
										epilog_stream,
										action_count,
										Nil);
									merge_pseudo_instruction_stream(prolog_stream);
									emit_already_consed_instruction(phrase_list_2(Qbranch_if_known,
										known_tag));
									emit_already_consed_instruction(phrase_cons(Qset_wake_ups,
										Nil));
									emit_already_consed_instruction(phrase_cons(Qclose_wake_up_collection,
										Nil));
									emit_already_consed_instruction(phrase_list_2(Qcomplete_rule_instance,
										Nil));
									emit_branch_or_jump(restart_tag);
									emit_already_consed_instruction(phrase_list_2(Qtag_statement,
										known_tag));
									emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
										FIX((SI_Long)64L)));
									emit_already_consed_instruction(phrase_cons(Qbegin_rule_actions,
										Nil));
									merge_pseudo_instruction_stream(epilog_stream);
								    }
								    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
									    close_rule_tag));
								    emit_already_consed_instruction(phrase_cons(Qclose_wake_up_collection,
									    Nil));
								    emit_already_consed_instruction(phrase_list_2(Qcomplete_rule_instance,
									    T));
								    context_list 
									    = 
									    rewrite_contexts_for_stack_compile(context_list);
								    second_new_value 
									    = 
									    Next_stack_frame_var_location;
								    M_SECOND(push_stack_frame_vars_instruction) 
									    = 
									    second_new_value;
								    environment 
									    = 
									    ISVREF(CAR(Lexically_visible_code_bodies),
									    (SI_Long)3L);
								    environment_length 
									    = 
									    length(environment);
								}
								POP_UNWIND_PROTECT(0);
								if ( 
									!TRUEP(gensymed_symbol))
								    Next_stack_frame_var_location 
									    = 
									    gensymed_symbol;
								CONTINUE_UNWINDING(0);
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						    if ( 
							    !TRUEP(Compiler_errors)) 
								{
							byte_code_stream = 
								make_byte_code_stream_1();
							code_body_entry = 
								CAR(Code_body_entries_in_compilation);
							instructions = 
								nreverse(ISVREF(code_body_entry,
								(SI_Long)1L));
							maximum_received_values 
								= 
								ISVREF(code_body_entry,
								(SI_Long)2L);
							instructions = 
								optimize_procedure_instructions(instructions,
								CAR(Code_body_entries_in_compilation));
							if ( 
								!TRUEP(Compiler_errors)) 
								    {
							    lexically_visible_code_bodies 
								    = 
								    generate_list_of_lexically_visible_code_bodies(code_body_entry);
							    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
								    0);
							      emit_byte_code_vector_for_procedure(byte_code_stream,
								      instructions);
							    POP_SPECIAL();
							}
							if ( 
								!TRUEP(Compiler_errors)) 
								    {
							    result = resolve_procedure_byte_code_addresses(1,
								    byte_code_stream);
							    MVS_2(result,
								    byte_code_vector,
								    byte_codes_count);
							}
							if ( 
								!TRUEP(Compiler_errors))
							    byte_code_constants 
								    = 
								    make_procedure_byte_code_constants(byte_code_stream);
							reclaim_byte_code_stream_1(byte_code_stream);
							change_slot_value(3,
								rule,
								Qrule_maximum_received_value_count,
								maximum_received_values);
							change_slot_value(3,
								rule,
								Qrule_return_value_position,
								FIXNUM_MINUS(environment_length,
								maximum_received_values));
						    }
						    if (Compiler_errors)
							byte_code_body_to_return 
								= 
								make_byte_code_body_1(FIX((SI_Long)4L),
								allocate_byte_vector(FIX((SI_Long)4L)),
								Nil,Nil,Nil);
						    else {
							temp_1 = 
								byte_codes_count;
							temp_2 = 
								byte_code_vector;
							temp = 
								byte_code_constants;
							byte_code_body_to_return 
								= 
								make_byte_code_body_1(temp_1,
								temp_2,
								temp,
								convert_description_list_to_managed_array(1,
								environment),
								Nil);
						    }
						    install_free_references_in_byte_code_body(byte_code_body_to_return,
							    Compiler_free_references);
						    change_slot_value(3,
							    rule,
							    Qrule_byte_code_body,
							    byte_code_body_to_return);
						    change_slot_value(3,
							    rule,
							    Qrule_context_length,
							    context_length);
						    change_slot_value(3,
							    rule,
							    Qrule_environment_length,
							    environment_length);
						    SAVE_VALUES(phrase_cons(FIRST(parse_and_compilations),
							    phrase_cons(SECOND(parse_and_compilations),
							    context_list)));
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					}
					POP_UNWIND_PROTECT(1);
					reclaim_stack_list_of_nodes(Stack_nodes_to_reclaim);
					CONTINUE_UNWINDING(1);
				      POP_SPECIAL();
				  }
				  POP_UNWIND_PROTECT(2);
				  code_body_entry = Nil;
				  ab_loop_list_ = 
					  Code_body_entries_in_compilation;
				next_loop_4:
				  if ( !TRUEP(ab_loop_list_))
				      goto end_loop_4;
				  code_body_entry = M_CAR(ab_loop_list_);
				  ab_loop_list_ = M_CDR(ab_loop_list_);
				  reclaim_compiler_code_body_entry_1(code_body_entry);
				  goto next_loop_4;
				end_loop_4:;
				  CONTINUE_UNWINDING(2);
				POP_SPECIAL();
			      POP_SPECIAL();
			  }
			  POP_UNWIND_PROTECT(3);
			  tag = Nil;
			  ab_loop_list_ = Goto_tags_in_compilation;
			next_loop_5:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_5;
			  tag = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  reclaim_goto_tag_entry_1(tag);
			  goto next_loop_5;
			end_loop_5:;
			  CONTINUE_UNWINDING(3);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(4);
		add_compiler_error_and_warning_frame_notes();
		CONTINUE_UNWINDING(4);
		result = RESTORE_VALUES();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Quniversal_compilation;  /* universal-compilation */

static Object Qany;                /* any */

static Object Qany_inverse;        /* any-inverse */

static Object Qthe_inverse;        /* the-inverse */

static Object Qthe_inverse_no_bind;  /* the-inverse-no-bind */

static Object string_constant_3;   /* "rule context rewriter" */

static Object string_constant_4;   /* "Unrecognized context quantifier ~a." */

/* REWRITE-CONTEXTS-FOR-STACK-COMPILE */
Object rewrite_contexts_for_stack_compile(context_list)
    Object context_list;
{
    Object universal_context, universal_prefix, focus_spec, current_prefix;
    Object ab_loop_list_, prefix, focus_name_qm, binding_qm, focus_index_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Object iterator, ab_loop_list__1, quantifier, ab_loopvar__3, ab_loopvar__4;
    Object gensymed_symbol, role, range_binding, domain_qm, gensymed_symbol_1;
    Object car_new_value, temp_1, short_designation, domain_binding;

    x_note_fn_call(206,6);
    universal_context = CAR(context_list);
    universal_prefix = CDR(universal_context);
    focus_spec = Nil;
    current_prefix = Nil;
    ab_loop_list_ = context_list;
    prefix = Nil;
    focus_name_qm = Nil;
    binding_qm = Nil;
    focus_index_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    focus_spec = CAR(ab_loop_desetq_);
    current_prefix = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    prefix = EQ(current_prefix,Quniversal_compilation) ? universal_prefix :
	     current_prefix;
    focus_name_qm = CONSP(focus_spec) ? FIRST(focus_spec) : focus_spec;
    binding_qm = CONSP(focus_spec) ? SECOND(focus_spec) : focus_spec;
    focus_index_qm = focus_spec ? 
	    lookup_or_generate_var_spot_index_for_local_name(binding_qm) : Nil;
    temp = focus_index_qm ? phrase_list_3(focus_name_qm,binding_qm,
	    focus_index_qm) : Nil;
    iterator = Nil;
    ab_loop_list__1 = prefix;
    quantifier = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    iterator = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    quantifier = CAR(iterator);
    if (EQ(quantifier,Qthe) || EQ(quantifier,Qany)) {
	gensymed_symbol = iterator;
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	range_binding = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	domain_qm = CAR(gensymed_symbol);
	record_free_references_of_role_given_domain_name(role,domain_qm);
	gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = quantifier;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = range_binding;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = domain_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = 
		lookup_or_generate_var_spot_index_for_local_name(range_binding);
	M_CAR(gensymed_symbol_1) = car_new_value;
	temp_1 = nconc2(gensymed_symbol,domain_qm ? 
		phrase_cons(var_spot_index_or_global_name(domain_qm),Nil) :
		 Nil);
    }
    else if (EQ(quantifier,Qany_inverse) || EQ(quantifier,Qthe_inverse)) {
	gensymed_symbol = iterator;
	gensymed_symbol = CDR(gensymed_symbol);
	range_binding = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	short_designation = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	domain_binding = CAR(gensymed_symbol);
	record_free_references_of_role_given_domain_name(role,domain_binding);
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = quantifier;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = range_binding;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = short_designation;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = domain_binding;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = 
		lookup_or_generate_var_spot_index_for_local_name(range_binding);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = EQ(short_designation,domain_binding) ? 
		domain_binding : 
		lookup_or_generate_var_spot_index_for_local_name(domain_binding);
	M_CAR(gensymed_symbol_1) = car_new_value;
	temp_1 = gensymed_symbol;
    }
    else if (EQ(quantifier,Qthe_inverse_no_bind)) {
	gensymed_symbol = iterator;
	gensymed_symbol = CDR(gensymed_symbol);
	range_binding = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	short_designation = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	domain_binding = CAR(gensymed_symbol);
	record_free_references_of_role_given_domain_name(role,domain_binding);
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = quantifier;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = range_binding;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = short_designation;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = domain_binding;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = 
		lookup_or_generate_var_spot_index_for_local_name(range_binding);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = EQ(domain_binding,short_designation) ? 
		domain_binding : 
		lookup_or_generate_var_spot_index_for_local_name(domain_binding);
	M_CAR(gensymed_symbol_1) = car_new_value;
	temp_1 = gensymed_symbol;
    }
    else
	temp_1 = compiler_bug(3,string_constant_3,string_constant_4,
		quantifier);
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
    ab_loopvar__2 = phrase_cons(phrase_cons(temp,temp_1),Nil);
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

static Object Qab_class;           /* class */

/* RECORD-FREE-REFERENCES-OF-ROLE-GIVEN-DOMAIN-NAME */
Object record_free_references_of_role_given_domain_name(role,domain_name_qm)
    Object role, domain_name_qm;
{
    x_note_fn_call(206,7);
    if (SYMBOLP(role)) {
	if ( !TRUEP(domain_name_qm))
	    return record_free_reference(Qab_class,role);
	else
	    return VALUES_1(Nil);
    }
    else
	return record_free_references_of_role(1,role);
}

/* TYPE-OF-GLOBAL-OR-LOCAL-NAME */
Object type_of_global_or_local_name(possible_local_name)
    Object possible_local_name;
{
    Object description_qm, temp;
    Object result;

    x_note_fn_call(206,8);
    result = variable_spot_and_description_for_local_name(possible_local_name);
    description_qm = NTH_VALUE((SI_Long)1L, result);
    temp = description_qm ? getfq_function_no_default(CDR(description_qm),
	    Ktype) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(list_constant_8);
}

static Object string_constant_5;   /* "rule context rewrite" */

static Object string_constant_6;   /* "The local name ~a hadn't been registered." */

/* VAR-SPOT-INDEX-FOR-LOCAL-NAME */
Object var_spot_index_for_local_name(local_name)
    Object local_name;
{
    Object var_spot_qm;

    x_note_fn_call(206,9);
    var_spot_qm = variable_spot_and_description_for_local_name(local_name);
    if (var_spot_qm)
	return VALUES_1(SECOND(var_spot_qm));
    else {
	compiler_bug(3,string_constant_5,string_constant_6,local_name);
	return VALUES_1(FIX((SI_Long)0L));
    }
}

/* VAR-SPOT-INDEX-OR-GLOBAL-NAME */
Object var_spot_index_or_global_name(local_or_global_name)
    Object local_or_global_name;
{
    Object var_spot_qm;

    x_note_fn_call(206,10);
    var_spot_qm = 
	    variable_spot_and_description_for_local_name(local_or_global_name);
    if (var_spot_qm)
	return VALUES_1(SECOND(var_spot_qm));
    else
	return VALUES_1(local_or_global_name);
}

/* LOOKUP-OR-GENERATE-VAR-SPOT-INDEX-FOR-LOCAL-NAME */
Object lookup_or_generate_var_spot_index_for_local_name(local_name)
    Object local_name;
{
    Object var_spot_qm, temp;

    x_note_fn_call(206,11);
    var_spot_qm = variable_spot_and_description_for_local_name(local_name);
    if (var_spot_qm)
	return VALUES_1(SECOND(var_spot_qm));
    else {
	temp = generate_new_variable_spot(2,Qitem_or_datum,local_name);
	return VALUES_1(SECOND(temp));
    }
}

static Object Qlet_action;         /* let-action */

static Object Qconclude;           /* conclude */

static Object Qconclude_not;       /* conclude-not */

static Object QCERTAINTY_VAR;      /* |certainty-var| */

static Object QEXPIRATION_VAR;     /* |expiration-var| */

/* REWRITE-CONCLUDE-ACTIONS-IN-ACTION-LIST */
Object rewrite_conclude_actions_in_action_list(action_list,in_order_rule_qm)
    Object action_list, in_order_rule_qm;
{
    Object action, ab_loop_list_, action_name, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, temp_1, gensymed_symbol, place, value;
    Object other_args, cached_designation_qm, parent_designation;
    Object generated_local_name;
    char temp_2;

    x_note_fn_call(206,12);
    action = Nil;
    ab_loop_list_ = action_list;
    action_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    action = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    action_name = CAR(action);
    if (EQ(action_name,Qevery) || EQ(action_name,Qlet_action)) {
	temp = action_name;
	temp_1 = SECOND(action);
	temp_1 = phrase_cons(temp,phrase_cons(temp_1,
		rewrite_conclude_actions_in_action_list(CDDR(action),
		in_order_rule_qm)));
    }
    else if (EQ(action_name,Qconclude) || EQ(action_name,Qconclude_not)) {
	if (EQ(action_name,Qconclude_not)) {
	    Rule_certainty_var = QCERTAINTY_VAR;
	    action_name = Qconclude;
	    action = phrase_cons(Qconclude,phrase_cons(SECOND(action),
		    phrase_cons(phrase_list_2(Qnot,Rule_certainty_var),
		    CDDR(action))));
	}
	gensymed_symbol = action;
	gensymed_symbol = CDR(gensymed_symbol);
	place = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	value = CAR(gensymed_symbol);
	other_args = CDR(gensymed_symbol);
	if (in_order_rule_qm)
	    Rule_expiration_var = QEXPIRATION_VAR;
	if ( !TRUEP(value)) {
	    Rule_certainty_var = QCERTAINTY_VAR;
	    value = Rule_certainty_var;
	}
	if ( !SYMBOLP(place))
	    temp_1 = phrase_cons(action_name,phrase_cons(place,
		    phrase_cons(value,other_args)));
	else {
	    temp_1 = assq_function(place,
		    Local_name_to_cached_designation_alist);
	    cached_designation_qm = SECOND(temp_1);
	    if (CONSP(cached_designation_qm) && 
		    IFIX(length(cached_designation_qm)) == (SI_Long)3L && 
		    EQ(CAR(cached_designation_qm),Qthe)) {
		temp_1 = SECOND(cached_designation_qm);
		temp_2 = SYMBOLP(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if ( !temp_2)
		temp_1 = phrase_cons(action_name,phrase_cons(place,
			phrase_cons(value,other_args)));
	    else if (name_rooted_attribute_only_designation_p(THIRD(cached_designation_qm)))
		temp_1 = phrase_cons(action_name,
			phrase_cons(cached_designation_qm,
			phrase_cons(value,other_args)));
	    else {
		parent_designation = THIRD(cached_designation_qm);
		generated_local_name = 
			interned_conclude_attribute_binding_symbol();
		Conclude_parent_attribute_bindings = 
			phrase_cons(phrase_list_2(generated_local_name,
			parent_designation),
			Conclude_parent_attribute_bindings);
		temp_1 = phrase_cons(action_name,
			phrase_cons(phrase_list_3(Qthe,
			SECOND(cached_designation_qm),
			generated_local_name),phrase_cons(value,other_args)));
	    }
	}
    }
    else
	temp_1 = action;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
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

static Object Qpause_kb;           /* pause-kb */

static Object string_constant_7;   /* "Pause knowledge-base must be the last action in a rule." */

/* COMPILE-IN-ORDER-ACTIONS */
Object compile_in_order_actions(action_list,expiration_var_spot_qm,
	    push_stack_frame_vars_instruction)
    Object action_list, expiration_var_spot_qm;
    Object push_stack_frame_vars_instruction;
{
    Object action_list_cons, action, action_name;

    x_note_fn_call(206,13);
    action_list_cons = action_list;
    action = Nil;
    action_name = Nil;
  next_loop:
    if ( !TRUEP(action_list_cons))
	goto end_loop;
    action = CAR(action_list_cons);
    action_name = CAR(action);
    if (EQ(action_name,Qevery))
	compile_in_order_every_action(action,expiration_var_spot_qm,
		push_stack_frame_vars_instruction);
    else if (EQ(action_name,Qlet_action))
	compile_in_order_let_action(action,expiration_var_spot_qm,
		push_stack_frame_vars_instruction);
    else {
	if (EQ(action_name,Qpause_kb) && CDR(action_list_cons))
	    compiler_error(1,string_constant_7);
	compile_in_order_action(action,expiration_var_spot_qm,
		push_stack_frame_vars_instruction);
    }
    action_list_cons = M_CDR(action_list_cons);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qrequired_domain_types_of_role;  /* required-domain-types-of-role */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object string_constant_8;   /* ", ~a, did not match the required count, ~a" */

static Object Qopen_role_iteration;  /* open-role-iteration */

static Object Qopen_role_iteration_no_domain;  /* open-role-iteration-no-domain */

static Object Qserve_next_iteration_value;  /* serve-next-iteration-value */

static Object Qclose_iteration;    /* close-iteration */

/* COMPILE-IN-ORDER-EVERY-ACTION */
Object compile_in_order_every_action(action,expiration_var_spot,
	    push_stack_frame_vars_instruction)
    Object action, expiration_var_spot, push_stack_frame_vars_instruction;
{
    Object gensymed_symbol, gensymed_symbol_1, role, binding, domain_list;
    Object inner_action_list, iteration_designation, iteration_type;
    Object iteration_spot, continuation_spot, role_1, role_car;
    Object required_domain_types, next_iteration_tag, end_of_every_tag;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_, domain, type_cons, type;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(206,14);
    gensymed_symbol = action;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    role = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    binding = CAR(gensymed_symbol_1);
    domain_list = CDR(gensymed_symbol_1);
    inner_action_list = gensymed_symbol;
    iteration_designation = phrase_cons(Qany,phrase_cons(role,domain_list));
    iteration_type = type_specification_of_designation(iteration_designation);
    if (iteration_type);
    else
	iteration_type = Qitem_or_datum;
    iteration_spot = generate_new_variable_spot(2,iteration_type,binding);
    continuation_spot = generate_new_variable_spot(1,
	    make_type_specification_for_iteration_state());
    if ( !SYMBOLP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	gensymed_symbol = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) 
		: role_car;
	required_domain_types = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qrequired_domain_types_of_role);
    }
    else
	required_domain_types = Nil;
    next_iteration_tag = generate_new_goto_tag();
    end_of_every_tag = generate_new_goto_tag();
    if (FIXNUM_NE(length(required_domain_types),length(domain_list))) {
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
			  FIX((SI_Long)27L));
		  print_role(role);
		  tformat(3,string_constant_8,length(domain_list),
			  length(required_domain_types));
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
    }
    if (domain_list) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qopen_role_iteration;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = continuation_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = end_of_every_tag;
	domain = Nil;
	ab_loop_list_ = domain_list;
	type_cons = required_domain_types;
	type = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons = CDR(type_cons);
	temp_1 = CAR(type_cons);
	if (temp_1);
	else
	    temp_1 = Qitem_or_datum;
	type = temp_1;
	ab_loopvar__2 = 
		phrase_cons(compile_stack_expression_into_nodes(domain,
		type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	emit_already_consed_instruction(nconc2(gensymed_symbol,temp_1));
    }
    else {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qopen_role_iteration_no_domain;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = continuation_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = end_of_every_tag;
	emit_already_consed_instruction(gensymed_symbol);
    }
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    next_iteration_tag));
    compile_in_order_actions(inner_action_list,expiration_var_spot,
	    push_stack_frame_vars_instruction);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qserve_next_iteration_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = continuation_spot;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_spot;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = end_of_every_tag;
    emit_already_consed_instruction(gensymed_symbol);
    emit_branch_or_jump(next_iteration_tag);
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    end_of_every_tag));
    return emit_already_consed_instruction(phrase_list_2(Qclose_iteration,
	    continuation_spot));
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_let_action_bindings, Qcurrent_let_action_bindings);

static Object list_constant_10;    /* # */

/* COMPILE-IN-ORDER-LET-ACTION */
Object compile_in_order_let_action(action,expiration_var_spot,
	    push_stack_frame_vars_instruction)
    Object action, expiration_var_spot, push_stack_frame_vars_instruction;
{
    Object current_let_action_bindings, gensymed_symbol, bindings;
    Object inner_actions, binding, ab_loop_list_, binding_name, expression_qm;
    Object compiled_expression_qm, expression_type_qm, var_spot_type_1;
    Object var_spot;
    Declare_special(1);
    Object result;

    x_note_fn_call(206,15);
    current_let_action_bindings = Current_let_action_bindings;
    PUSH_SPECIAL_WITH_SYMBOL(Current_let_action_bindings,Qcurrent_let_action_bindings,current_let_action_bindings,
	    0);
      gensymed_symbol = action;
      gensymed_symbol = CDR(gensymed_symbol);
      bindings = CAR(gensymed_symbol);
      inner_actions = CDR(gensymed_symbol);
      binding = Nil;
      ab_loop_list_ = bindings;
      binding_name = Nil;
      expression_qm = Nil;
      compiled_expression_qm = Nil;
      expression_type_qm = Nil;
      var_spot_type_1 = Nil;
      var_spot = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      binding = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      binding_name = CAR(binding);
      expression_qm = SECOND(binding);
      compiled_expression_qm = expression_qm ? 
	      compile_stack_expression_into_nodes(expression_qm,
	      list_constant_5) : Nil;
      expression_type_qm = compiled_expression_qm ? 
	      ISVREF(compiled_expression_qm,(SI_Long)6L) : Nil;
      var_spot_type_1 =  !TRUEP(expression_type_qm) ? Qitem_or_datum : 
	      type_specification_minus_type(type_specification_minus_type(expression_type_qm,
	      list_constant_6),list_constant_10);
      var_spot = generate_new_variable_spot(2,var_spot_type_1,binding_name);
      if (compiled_expression_qm) {
	  emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		  var_spot,compiled_expression_qm));
	  Current_let_action_bindings = phrase_cons(binding,
		  Current_let_action_bindings);
      }
      goto next_loop;
    end_loop:;
      result = compile_in_order_actions(inner_actions,expiration_var_spot,
	      push_stack_frame_vars_instruction);
    POP_SPECIAL();
    return result;
}

static Object Qaction_compiler;    /* action-compiler */

static Object Qset_expiration;     /* set-expiration */

static Object Qclear_wake_ups;     /* clear-wake-ups */

static Object string_constant_9;   /* "rule action compiler" */

static Object string_constant_10;  /* "No compiler for action ~a." */

/* COMPILE-IN-ORDER-ACTION */
Object compile_in_order_action(action,expiration_var_spot,
	    push_stack_frame_vars_instruction)
    Object action, expiration_var_spot, push_stack_frame_vars_instruction;
{
    Object action_name, action_compiler_qm, resume_tag, prolog_stream;
    Object epilog_stream, epilog_tag, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5;

    x_note_fn_call(206,16);
    action_name = M_CAR(action);
    action_compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(action_name),
	    Qaction_compiler);
    resume_tag = generate_new_goto_tag();
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,resume_tag));
    if (expiration_var_spot)
	emit_already_consed_instruction(phrase_list_2(Qset_expiration,
		expiration_var_spot));
    if (action_compiler_qm) {
	prolog_stream = make_pseudo_instruction_stream_1();
	epilog_stream = make_pseudo_instruction_stream_1();
	epilog_tag = generate_new_goto_tag();
	gensymed_symbol = action_compiler_qm;
	gensymed_symbol_1 = action;
	gensymed_symbol_2 = T;
	gensymed_symbol_3 = T;
	gensymed_symbol_4 = prolog_stream;
	gensymed_symbol_5 = epilog_stream;
	inline_funcall_5(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5);
	merge_pseudo_instruction_stream(prolog_stream);
	emit_already_consed_instruction(phrase_list_2(Qbranch_if_known,
		epilog_tag));
	emit_already_consed_instruction(phrase_cons(Qset_wake_ups,Nil));
	emit_already_consed_instruction(phrase_cons(Qclose_wake_up_collection,
		Nil));
	emit_already_consed_instruction(phrase_list_2(Qcomplete_rule_instance,
		Nil));
	emit_already_consed_instruction(push_stack_frame_vars_instruction);
	emit_already_consed_instruction(phrase_cons(Qopen_wake_up_collection,
		Nil));
	emit_branch_or_jump(resume_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		epilog_tag));
	emit_already_consed_instruction(phrase_cons(Qclear_wake_ups,Nil));
	return merge_pseudo_instruction_stream(epilog_stream);
    }
    else
	return compiler_bug(3,string_constant_9,string_constant_10,
		action_name);
}

static Object Qadd_to_action_cache;  /* add-to-action-cache */

static Object Qrestore_from_action_cache_or_branch;  /* restore-from-action-cache-or-branch */

static Object Qbranch;             /* branch */

/* COMPILE-SIMULTANEOUS-ACTIONS */
Object compile_simultaneous_actions(action_list,prolog_stream,
	    epilog_stream,action_count,action_cache_qm)
    Object action_list, prolog_stream, epilog_stream, action_count;
    Object action_cache_qm;
{
    Object action_list_cons, action, action_name, action_compiler_qm;
    Object action_epilog_stream, epilog_next_iteration_tag;
    Object epilog_action_cache_empty_tag, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, var_spot_block;
    char gensymed_symbol_6;

    x_note_fn_call(206,17);
    action_list_cons = action_list;
    action = Nil;
    action_name = Nil;
    action_compiler_qm = Nil;
  next_loop:
    if ( !TRUEP(action_list_cons))
	goto end_loop;
    action = CAR(action_list_cons);
    action_name = CAR(action);
    action_compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(action_name),
	    Qaction_compiler);
    if (EQ(action_name,Qevery))
	compile_simultaneous_every_action(action,prolog_stream,
		epilog_stream,action_count,action_cache_qm);
    else if (EQ(action_name,Qlet_action))
	compile_simultaneous_let_action(action,prolog_stream,epilog_stream,
		action_count,action_cache_qm);
    else if (action_compiler_qm) {
	if (EQ(action_name,Qpause_kb) && CDR(action_list_cons))
	    compiler_error(1,string_constant_7);
	if (action_cache_qm) {
	    action_epilog_stream = make_pseudo_instruction_stream_1();
	    epilog_next_iteration_tag = generate_new_goto_tag();
	    epilog_action_cache_empty_tag = generate_new_goto_tag();
	    gensymed_symbol = action_compiler_qm;
	    gensymed_symbol_1 = action;
	    gensymed_symbol_2 = T;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = prolog_stream;
	    gensymed_symbol_5 = action_epilog_stream;
	    var_spot_block = inline_funcall_5(gensymed_symbol,
		    gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3,
		    gensymed_symbol_4,gensymed_symbol_5);
	    emit_already_consed_instruction_to_stream(prolog_stream,
		    phrase_list_3(Qadd_to_action_cache,action_cache_qm,
		    var_spot_block));
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qtag_statement,epilog_next_iteration_tag));
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_4(Qrestore_from_action_cache_or_branch,
		    action_cache_qm,var_spot_block,
		    epilog_action_cache_empty_tag));
	    merge_pseudo_instruction_streams(epilog_stream,
		    action_epilog_stream);
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qbranch,epilog_next_iteration_tag));
	    emit_already_consed_instruction_to_stream(epilog_stream,
		    phrase_list_2(Qtag_statement,
		    epilog_action_cache_empty_tag));
	}
	else {
	    gensymed_symbol = action_compiler_qm;
	    gensymed_symbol_1 = action;
	    gensymed_symbol_2 = T;
	    gensymed_symbol_6 = IFIX(action_count) == (SI_Long)1L;
	    gensymed_symbol_3 = prolog_stream;
	    gensymed_symbol_4 = epilog_stream;
	    inline_funcall_5(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_6 ? T : Nil,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
    }
    else
	compiler_bug(3,string_constant_9,string_constant_10,action_name);
    action_list_cons = M_CDR(action_list_cons);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_11;    /* # */

static Object Qclear_action_cache;  /* clear-action-cache */

/* COMPILE-SIMULTANEOUS-EVERY-ACTION */
Object compile_simultaneous_every_action(action,prolog_stream,
	    epilog_stream,action_count,previous_action_cache_qm)
    Object action, prolog_stream, epilog_stream, action_count;
    Object previous_action_cache_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, role, binding, domain_list;
    Object inner_action_list, iteration_designation, iteration_type;
    Object iteration_spot, continuation_spot, role_1, role_car;
    Object required_domain_types, next_iteration_tag, action_cache;
    Object end_of_every_tag, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_, domain, type_cons, type;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(206,18);
    gensymed_symbol = action;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    role = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    binding = CAR(gensymed_symbol_1);
    domain_list = CDR(gensymed_symbol_1);
    inner_action_list = gensymed_symbol;
    iteration_designation = phrase_cons(Qany,phrase_cons(role,domain_list));
    iteration_type = type_specification_of_designation(iteration_designation);
    if (iteration_type);
    else
	iteration_type = Qitem_or_datum;
    iteration_spot = generate_new_variable_spot(2,iteration_type,binding);
    continuation_spot = generate_new_variable_spot(1,
	    make_type_specification_for_iteration_state());
    if ( !SYMBOLP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	gensymed_symbol = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) 
		: role_car;
	required_domain_types = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qrequired_domain_types_of_role);
    }
    else
	required_domain_types = Nil;
    next_iteration_tag = generate_new_goto_tag();
    action_cache = previous_action_cache_qm;
    if (action_cache);
    else
	action_cache = generate_new_variable_spot(1,list_constant_11);
    end_of_every_tag = generate_new_goto_tag();
    if (FIXNUM_NE(length(required_domain_types),length(domain_list))) {
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
			  FIX((SI_Long)27L));
		  print_role(role);
		  tformat(3,string_constant_8,length(domain_list),
			  length(required_domain_types));
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
    }
    if ( !TRUEP(previous_action_cache_qm))
	emit_already_consed_instruction_to_stream(prolog_stream,
		phrase_list_2(Qclear_action_cache,action_cache));
    if (domain_list) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qopen_role_iteration;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = continuation_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = end_of_every_tag;
	domain = Nil;
	ab_loop_list_ = domain_list;
	type_cons = required_domain_types;
	type = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons = CDR(type_cons);
	temp_1 = CAR(type_cons);
	if (temp_1);
	else
	    temp_1 = Qitem_or_datum;
	type = temp_1;
	ab_loopvar__2 = 
		phrase_cons(compile_stack_expression_into_nodes(domain,
		type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	emit_already_consed_instruction_to_stream(prolog_stream,
		nconc2(gensymed_symbol,temp_1));
    }
    else {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qopen_role_iteration_no_domain;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = role;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = continuation_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = end_of_every_tag;
	emit_already_consed_instruction_to_stream(prolog_stream,
		gensymed_symbol);
    }
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_2(Qtag_statement,next_iteration_tag));
    compile_simultaneous_actions(inner_action_list,prolog_stream,
	    epilog_stream,action_count,action_cache);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qserve_next_iteration_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = continuation_spot;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_spot;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = iteration_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = end_of_every_tag;
    emit_already_consed_instruction_to_stream(prolog_stream,gensymed_symbol);
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_2(Qbranch,next_iteration_tag));
    emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_2(Qtag_statement,end_of_every_tag));
    return emit_already_consed_instruction_to_stream(prolog_stream,
	    phrase_list_2(Qclose_iteration,continuation_spot));
}

/* COMPILE-SIMULTANEOUS-LET-ACTION */
Object compile_simultaneous_let_action(action,prolog_stream,epilog_stream,
	    action_count,action_cache_qm)
    Object action, prolog_stream, epilog_stream, action_count, action_cache_qm;
{
    Object current_let_action_bindings, gensymed_symbol, bindings;
    Object inner_actions, binding, ab_loop_list_, binding_name, expression_qm;
    Object compiled_expression_qm, expression_type_qm, var_spot_type_1;
    Object var_spot;
    Declare_special(1);
    Object result;

    x_note_fn_call(206,19);
    current_let_action_bindings = Current_let_action_bindings;
    PUSH_SPECIAL_WITH_SYMBOL(Current_let_action_bindings,Qcurrent_let_action_bindings,current_let_action_bindings,
	    0);
      gensymed_symbol = action;
      gensymed_symbol = CDR(gensymed_symbol);
      bindings = CAR(gensymed_symbol);
      inner_actions = CDR(gensymed_symbol);
      binding = Nil;
      ab_loop_list_ = bindings;
      binding_name = Nil;
      expression_qm = Nil;
      compiled_expression_qm = Nil;
      expression_type_qm = Nil;
      var_spot_type_1 = Nil;
      var_spot = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      binding = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      binding_name = CAR(binding);
      expression_qm = SECOND(binding);
      compiled_expression_qm = expression_qm ? 
	      compile_stack_expression_into_nodes(expression_qm,
	      list_constant_5) : Nil;
      expression_type_qm = compiled_expression_qm ? 
	      ISVREF(compiled_expression_qm,(SI_Long)6L) : Nil;
      var_spot_type_1 =  !TRUEP(expression_type_qm) ? Qitem_or_datum : 
	      type_specification_minus_type(type_specification_minus_type(expression_type_qm,
	      list_constant_6),list_constant_10);
      var_spot = generate_new_variable_spot(2,var_spot_type_1,binding_name);
      if (compiled_expression_qm) {
	  emit_already_consed_instruction_to_stream(prolog_stream,
		  phrase_list_3(Qassign_local_var,var_spot,
		  compiled_expression_qm));
	  Current_let_action_bindings = phrase_cons(binding,
		  Current_let_action_bindings);
      }
      goto next_loop;
    end_loop:;
      result = compile_simultaneous_actions(inner_actions,prolog_stream,
	      epilog_stream,action_count,action_cache_qm);
    POP_SPECIAL();
    return result;
}

static Object list_constant_12;    /* # */

static Object Qcomplete_cell_expression;  /* complete-cell-expression */

/* COMPILE-EXPRESSION-CELL-FOR-STACK */
Object compile_expression_cell_for_stack(expression,arguments_and_types,
	    result_type)
    Object expression, arguments_and_types, result_type;
{
    Object byte_code_vector, byte_codes_count, byte_code_constants;
    Object byte_code_body_to_return, environment, expression_type;
    Object variable_type, code_body_entry, compiler_errors, compiler_warnings;
    Object new_goto_tag_counter, goto_tags_in_compilation;
    Object lexically_visible_goto_tags, lexically_visible_code_bodies;
    Object code_body_entries_in_compilation, stack_nodes_to_reclaim;
    Object compiler_free_references, collecting_free_references;
    Object gensymed_symbol, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object result_var_spot, binding_name, type, ab_loop_list_, ab_loop_desetq_;
    Object temp, byte_code_stream, instructions, temp_1, temp_2, tag;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(15);
    Object result;

    x_note_fn_call(206,20);
    SAVE_STACK();
    byte_code_vector = Nil;
    byte_codes_count = Nil;
    byte_code_constants = Nil;
    byte_code_body_to_return = Nil;
    environment = Nil;
    expression_type = type_specification_minus_type(result_type,
	    list_constant_12);
    variable_type = type_specification_minus_type(expression_type,
	    list_constant_6);
    code_body_entry = Nil;
    compiler_errors = Nil;
    compiler_warnings = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
	    14);
      PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
	      13);
	remove_compiler_error_and_warning_frame_notes();
	if (PUSH_UNWIND_PROTECT(3)) {
	    new_goto_tag_counter = FIX((SI_Long)0L);
	    goto_tags_in_compilation = Nil;
	    lexically_visible_goto_tags = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		    12);
	      PUSH_SPECIAL_WITH_SYMBOL(Goto_tags_in_compilation,Qgoto_tags_in_compilation,goto_tags_in_compilation,
		      11);
		PUSH_SPECIAL_WITH_SYMBOL(New_goto_tag_counter,Qnew_goto_tag_counter,new_goto_tag_counter,
			10);
		  if (PUSH_UNWIND_PROTECT(2)) {
		      lexically_visible_code_bodies = Nil;
		      code_body_entries_in_compilation = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Code_body_entries_in_compilation,Qcode_body_entries_in_compilation,code_body_entries_in_compilation,
			      9);
			PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
				8);
			  if (PUSH_UNWIND_PROTECT(1)) {
			      stack_nodes_to_reclaim = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Stack_nodes_to_reclaim,Qstack_nodes_to_reclaim,stack_nodes_to_reclaim,
				      7);
				if (PUSH_UNWIND_PROTECT(0)) {
				    compiler_free_references = Nil;
				    collecting_free_references = T;
				    PUSH_SPECIAL_WITH_SYMBOL(Collecting_free_references,Qcollecting_free_references,collecting_free_references,
					    6);
				      PUSH_SPECIAL_WITH_SYMBOL(Compiler_free_references,Qcompiler_free_references,compiler_free_references,
					      5);
					gensymed_symbol = 
						CAR(Lexically_visible_code_bodies);
					gensymed_symbol = 
						make_compiler_code_body_entry_1(Nil,
						gensymed_symbol ? 
						position(2,gensymed_symbol,
						Code_body_entries_in_compilation) 
						: Nil);
					lexically_visible_code_bodies = 
						phrase_cons(gensymed_symbol,
						Lexically_visible_code_bodies);
					PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
						4);
					  Code_body_entries_in_compilation 
						  = 
						  nconc2(Code_body_entries_in_compilation,
						  phrase_cons(gensymed_symbol,
						  Nil));
					  check_for_new_code_body_errors();
					  if (inlining_context_qm())
					      adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
					  outermost_stack_frame_var_binding_qm 
						  = Nil;
					  next_stack_frame_var_location = Nil;
					  stack_frame_vars_ok_in_procedure_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
						  3);
					    PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
						    2);
					      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
						      1);
						lexically_visible_goto_tags 
							= 
							Lexically_visible_goto_tags;
						PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
							0);
						  code_body_entry = 
							  M_CAR(Lexically_visible_code_bodies);
						  result_var_spot = 
							  generate_new_variable_spot(1,
							  variable_type);
						  binding_name = Nil;
						  type = Nil;
						  ab_loop_list_ = 
							  arguments_and_types;
						  ab_loop_desetq_ = Nil;
						next_loop:
						  if ( !TRUEP(ab_loop_list_))
						      goto end_loop;
						  ab_loop_desetq_ = 
							  M_CAR(ab_loop_list_);
						  binding_name = 
							  CAR(ab_loop_desetq_);
						  temp = CDR(ab_loop_desetq_);
						  type = CAR(temp);
						  ab_loop_list_ = 
							  M_CDR(ab_loop_list_);
						  generate_new_variable_spot(2,
							  type,binding_name);
						  goto next_loop;
						end_loop:;
						  emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
							  result_var_spot,
							  compile_stack_expression_into_nodes(expression,
							  expression_type)));
						  emit_already_consed_instruction(phrase_list_2(Qcomplete_cell_expression,
							  result_var_spot));
						  environment = 
							  ISVREF(CAR(Lexically_visible_code_bodies),
							  (SI_Long)3L);
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
					if ( !TRUEP(Compiler_errors)) {
					    byte_code_stream = 
						    make_byte_code_stream_1();
					    instructions = 
						    nreverse(ISVREF(CAR(Code_body_entries_in_compilation),
						    (SI_Long)1L));
					    instructions = 
						    optimize_procedure_instructions(instructions,
						    CAR(Code_body_entries_in_compilation));
					    if ( !TRUEP(Compiler_errors)) {
						lexically_visible_code_bodies 
							= 
							generate_list_of_lexically_visible_code_bodies(code_body_entry);
						PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
							0);
						  emit_byte_code_vector_for_procedure(byte_code_stream,
							  instructions);
						POP_SPECIAL();
					    }
					    if ( !TRUEP(Compiler_errors)) {
						result = resolve_procedure_byte_code_addresses(1,
							byte_code_stream);
						MVS_2(result,
							byte_code_vector,
							byte_codes_count);
					    }
					    if ( !TRUEP(Compiler_errors))
						byte_code_constants = 
							make_procedure_byte_code_constants(byte_code_stream);
					    reclaim_byte_code_stream_1(byte_code_stream);
					}
					if (Compiler_errors)
					    byte_code_body_to_return = Nil;
					else {
					    temp_1 = byte_codes_count;
					    temp_2 = byte_code_vector;
					    temp = byte_code_constants;
					    byte_code_body_to_return = 
						    make_byte_code_body_1(temp_1,
						    temp_2,temp,
						    convert_description_list_to_managed_array(1,
						    environment),Nil);
					}
					if (byte_code_body_to_return)
					    install_free_references_in_byte_code_body(byte_code_body_to_return,
						    Compiler_free_references);
					SAVE_VALUES(VALUES_1(byte_code_body_to_return));
				      POP_SPECIAL();
				    POP_SPECIAL();
				}
				POP_UNWIND_PROTECT(0);
				reclaim_stack_list_of_nodes(Stack_nodes_to_reclaim);
				CONTINUE_UNWINDING(0);
			      POP_SPECIAL();
			  }
			  POP_UNWIND_PROTECT(1);
			  code_body_entry = Nil;
			  ab_loop_list_ = Code_body_entries_in_compilation;
			next_loop_1:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_1;
			  code_body_entry = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  reclaim_compiler_code_body_entry_1(code_body_entry);
			  goto next_loop_1;
			end_loop_1:;
			  CONTINUE_UNWINDING(1);
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  POP_UNWIND_PROTECT(2);
		  tag = Nil;
		  ab_loop_list_ = Goto_tags_in_compilation;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  tag = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  reclaim_goto_tag_entry_1(tag);
		  goto next_loop_2;
		end_loop_2:;
		  CONTINUE_UNWINDING(2);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(3);
	add_compiler_error_and_warning_frame_notes();
	CONTINUE_UNWINDING(3);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qannotation;         /* annotation */

/* COMPILE-STACK-EXPRESSION-INTO-NODES */
Object compile_stack_expression_into_nodes(expression,required_type)
    Object expression, required_type;
{
    Object annotation_qm, gensymed_symbol;
    Object outermost_stack_frame_var_binding_qm, stack_node_tree;
    Object svref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(206,21);
    SAVE_STACK();
    annotation_qm = Generate_source_annotation_info && CONSP(expression) ? 
	    get_current_annotation_context(expression) : Qnil;
    if (annotation_qm)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		annotation_qm));
    gensymed_symbol = Next_stack_frame_var_location;
    outermost_stack_frame_var_binding_qm =  !TRUEP(gensymed_symbol) ? T : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
	    0);
      if (PUSH_UNWIND_PROTECT(0)) {
	  if ( !TRUEP(gensymed_symbol))
	      Next_stack_frame_var_location = FIX((SI_Long)0L);
	  stack_node_tree = convert_expression_to_stack_node_tree(expression);
	  stack_node_tree = choose_stack_node_instructions_and_types(2,
		  stack_node_tree,required_type);
	  ensure_argument_types_satisfy_operators(Nil,stack_node_tree);
	  stack_node_tree = 
		  rewrite_stack_node_trees_for_unknown(stack_node_tree);
	  if (Outermost_stack_frame_var_binding_qm) {
	      svref_new_value = Next_stack_frame_var_location;
	      SVREF(stack_node_tree,FIX((SI_Long)9L)) = svref_new_value;
	  }
	  check_ensure_type_nodes(stack_node_tree);
	  SAVE_VALUES(VALUES_1(stack_node_tree));
      }
      POP_UNWIND_PROTECT(0);
      if ( !TRUEP(gensymed_symbol))
	  Next_stack_frame_var_location = gensymed_symbol;
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* DUMMY-INSTRUCTION-I-CHOOSER */
Object dummy_instruction_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    x_note_fn_call(206,22);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = Qitem_or_datum;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NO-OP-I-CHOOSER */
Object no_op_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type;

    x_note_fn_call(206,23);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = required_type;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_13;    /* # */

static Object Qfloat_array;        /* float-array */

static Object string_constant_11;  /* "The text beginning with \"~a...\" contains more than ~a characters." */

/* PUSH-CONSTANT-I-CHOOSER */
Object push_constant_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, float_required_qm;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, new_constant, small_text;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(206,24);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    float_required_qm = type_specification_subtype_p(required_type,
	    list_constant_13);
    if (float_required_qm && FIXNUMP(extra_info)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
	    aref_new_value = (double)IFIX(extra_info);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    new_constant = new_float;
	    extra_info = new_constant;
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = new_constant;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    if (float_required_qm && INLINE_LONG_VECTOR_P(extra_info) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(extra_info)) == 
	    (SI_Long)1L) {
	new_constant = make_evaluation_float_from_evaluation_long(1,
		extra_info);
	reclaim_managed_simple_long_array_of_length_1(extra_info);
	extra_info = new_constant;
	SVREF(stack_node_instruction,FIX((SI_Long)12L)) = new_constant;
    }
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(extra_info) != (SI_Long)0L && 
	    FIXNUM_GT(lengthw(extra_info),
	    Maximum_length_for_user_text_strings)) {
	small_text = text_string_substring(extra_info,FIX((SI_Long)0L),
		FIX((SI_Long)20L));
	compiler_error(3,string_constant_11,small_text,
		Maximum_length_for_user_text_strings);
	reclaim_text_string(small_text);
    }
    temp = evaluation_value_type(extra_info);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

static Object Qstable_name_of_class_instance;  /* stable-name-of-class-instance */

static Object Qitem;               /* item */

static Object Qstable_name;        /* stable-name */

static Object Qname_of_type;       /* name-of-type */

/* NAME-REFERENCE-I-CHOOSER */
Object name_reference_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, name, unknown_allowed_qm;
    Object no_item_allowed_qm, no_item_implies_unknown_allowed_qm;
    Object stripped_type, stable_item_qm, stable_item_of_class_qm;
    Object svref_new_value;

    x_note_fn_call(206,25);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    name = extra_info;
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    stripped_type = 
	    type_specification_minus_type(type_specification_minus_type(type_specification_minus_type(required_type,
	    list_constant_6),list_constant_10),list_constant_14);
    stable_item_qm = stable_name_p(1,name);
    stable_item_of_class_qm = stable_item_qm ? stable_name_of_class_p(name,
	    ISVREF(ISVREF(stable_item_qm,(SI_Long)1L),(SI_Long)1L),
	    Current_computation_frame) : Nil;
    if (stable_item_of_class_qm) {
	svref_new_value = 
		make_class_type_specification(ISVREF(ISVREF(stable_item_qm,
		(SI_Long)1L),(SI_Long)1L));
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
	record_free_reference(Qstable_name_of_class_instance,
		phrase_cons(name,ISVREF(ISVREF(stable_item_of_class_qm,
		(SI_Long)1L),(SI_Long)1L)));
    }
    else if (stable_item_qm) {
	svref_new_value = make_class_type_specification(Qitem);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
	record_free_reference(Qstable_name,name);
    }
    else {
	svref_new_value = 
		maybe_add_unknown(maybe_add_no_item(make_class_type_specification(Qitem),
		no_item_allowed_qm),no_item_implies_unknown_allowed_qm);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
	if (datum_type_specification_p(stripped_type))
	    record_free_reference(Qname_of_type,phrase_cons(name,
		    unknown_allowed_qm ? 
		    type_specification_returning_datum_type_or_unknown(2,
		    stripped_type,T) : 
		    type_specification_returning_datum_type(2,
		    stripped_type,T)));
	else
	    record_free_reference(Qname_of_type,phrase_cons(name,
		    stripped_type));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PUSH-CACHED-ITEM-I-CHOOSER */
Object push_cached_item_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, name, stable_item_qm;
    Object stable_item_of_class_qm, class_1, no_item_allowed_qm;
    Object svref_new_value;

    x_note_fn_call(206,26);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    name = extra_info;
    stable_item_qm = dependent_compilation_p(0) ? stable_name_p(1,name) : Nil;
    stable_item_of_class_qm = stable_item_qm ? stable_name_of_class_p(name,
	    ISVREF(ISVREF(stable_item_qm,(SI_Long)1L),(SI_Long)1L),
	    Current_computation_frame) : Nil;
    class_1 = stable_item_of_class_qm ? 
	    ISVREF(ISVREF(stable_item_of_class_qm,(SI_Long)1L),
	    (SI_Long)1L) : Qitem;
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    svref_new_value = 
	    maybe_add_no_item(make_class_type_specification(class_1), 
	    !TRUEP(stable_item_qm) ? no_item_allowed_qm : Qnil);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    if (stable_item_qm)
	record_free_reference(Qstable_name_of_class_instance,
		phrase_cons(name,class_1));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* EVALUATE-ROLE-WITH-NO-DOMAIN-I-CHOOSER */
Object evaluate_role_with_no_domain_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, no_item_allowed_qm, svref_new_value;
    Object role, role_car, gensymed_symbol, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(206,27);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    if (SYMBOLP(extra_info)) {
	record_free_reference(Qab_class,extra_info);
	svref_new_value = 
		maybe_add_no_item(make_class_type_specification(extra_info),
		no_item_allowed_qm);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    }
    else {
	role = extra_info;
	role_car = M_CAR(role);
	gensymed_symbol = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car;
	if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qrequired_domain_types_of_role)) {
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
		      twrite_compiler_message_header();
		      twrite_beginning_of_wide_string(array_constant_1,
			      FIX((SI_Long)9L));
		      print_role(extra_info);
		      twrite_beginning_of_wide_string(array_constant_2,
			      FIX((SI_Long)38L));
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
		Compiler_errors = phrase_cons(candidate_string,
			Compiler_errors);
	    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = Qitem_or_datum;
	}
	else {
	    record_free_references_of_role(1,extra_info);
	    temp_1 = type_specification_of_role(extra_info);
	    if (temp_1);
	    else
		temp_1 = Qitem_or_datum;
	    svref_new_value = maybe_add_no_item(temp_1,no_item_allowed_qm);
	    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Sorted_static_evaluate_role_dispatchers, Qsorted_static_evaluate_role_dispatchers);

Object Unique_value_of_role_instruction_name_prop = UNBOUND;

Object Static_evaluate_role_dispatch_predicate_prop = UNBOUND;

Object Static_evaluate_role_dispatch_parent_prop = UNBOUND;

/* G2-TOGGLE-EVALUATE-ROLE-INLINE */
Object g2_toggle_evaluate_role_inline(ev_truth_value)
    Object ev_truth_value;
{
    x_note_fn_call(206,28);
    Allow_inline_evaluate_role_instructions_p =  !EQ(ev_truth_value,
	    Evaluation_false_value) ? T : Nil;
    return VALUES_1(Allow_inline_evaluate_role_instructions_p);
}

/* INVALIDATE-STATIC-EVAULATE-ROLE-DISPATCHER */
Object invalidate_static_evaulate_role_dispatcher()
{
    x_note_fn_call(206,29);
    Sorted_static_evaluate_role_dispatchers = Nil;
    return VALUES_1(Sorted_static_evaluate_role_dispatchers);
}

static Object Qcdr_greater_p;      /* cdr-greater-p */

static Object Qstatic_evaluate_role_dispatch_predicate;  /* static-evaluate-role-dispatch-predicate */

/* VALIDATE-STATIC-EVAULATE-ROLE-DISPATCHER */
Object validate_static_evaulate_role_dispatcher()
{
    Object role, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object pair_list, pair, result_1, role_name, function_qm, push_arg;

    x_note_fn_call(206,30);
    if ( !TRUEP(Sorted_static_evaluate_role_dispatchers)) {
	role = Nil;
	ab_loop_list_ = Unique_value_roles;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	role = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = LIST_1(pair_role_with_depth(role));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	pair_list = ab_loopvar_;
	goto end_1;
	pair_list = Qnil;
      end_1:;
	pair_list = sort(2,pair_list,Qcdr_greater_p);
	pair = Nil;
	ab_loop_list_ = pair_list;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = LIST_1(CAR(pair));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	Unique_value_roles = ab_loopvar_;
	goto end_2;
	Unique_value_roles = Qnil;
      end_2:;
	result_1 = Nil;
	role_name = Nil;
	ab_loop_list_ = Unique_value_roles;
	function_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	role_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	function_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
		Qstatic_evaluate_role_dispatch_predicate);
	if (function_qm) {
	    push_arg = function_qm;
	    result_1 = CONS(push_arg,result_1);
	}
	else
	    error((SI_Long)2L,
		    "No dispatcher defined for unique-role-server ~s",
		    role_name);
	goto next_loop_2;
      end_loop_2:
	Sorted_static_evaluate_role_dispatchers = nreverse(result_1);
	goto end_3;
	Sorted_static_evaluate_role_dispatchers = Qnil;
      end_3:;
	return VALUES_1(Sorted_static_evaluate_role_dispatchers);
    }
    else
	return VALUES_1(Nil);
}

/* CDR-GREATER-P */
Object cdr_greater_p(p1,p2)
    Object p1, p2;
{
    Object temp, temp_1;

    x_note_fn_call(206,31);
    temp = CDR(p1);
    temp_1 = CDR(p2);
    return VALUES_1(NUM_GT(temp,temp_1) ? T : Nil);
}

static Object Qstatic_evaluate_role_dispatch_parent;  /* static-evaluate-role-dispatch-parent */

/* PAIR-ROLE-WITH-DEPTH */
Object pair_role_with_depth(role_name)
    Object role_name;
{
    Object res, role_name_1;

    x_note_fn_call(206,32);
    res = FIX((SI_Long)0L);
    role_name_1 = role_name;
  next_loop:
    if ( !TRUEP(role_name_1))
	goto end_loop;
    res = FIXNUM_ADD1(res);
    role_name_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name_1),
	    Qstatic_evaluate_role_dispatch_parent);
    goto next_loop;
  end_loop:
    return VALUES_1(CONS(role_name,res));
    return VALUES_1(Qnil);
}

/* STATIC-ROLE-DISPATCHER-LESS-THAN */
Object static_role_dispatcher_less_than(role_name_1,role_name_2)
    Object role_name_1, role_name_2;
{
    Object role_name, next_name_qm;

    x_note_fn_call(206,33);
    role_name = role_name_1;
    next_name_qm = Nil;
  next_loop:
    next_name_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
	    Qstatic_evaluate_role_dispatch_parent);
    if ( !TRUEP(next_name_qm))
	goto end_loop;
    if (EQ(next_name_qm,role_name_2))
	return VALUES_1(T);
    role_name = next_name_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHOOSE-OPTIMIZED-EVALUATE-ROLE-INSTRUCTION */
Object choose_optimized_evaluate_role_instruction(stack_node_instruction,
	    argument_list,value_type,no_item_allowed_qm,unknown_allowed_qm)
    Object stack_node_instruction, argument_list, value_type;
    Object no_item_allowed_qm, unknown_allowed_qm;
{
    Object role_constant, domain_1_arg, domain_2_arg, dispatcher;
    Object ab_loop_list_, specialized_role_qm, instruction_name_qm;
    Object refined_value_type_qm, svref_new_value, temp;
    Object result;

    x_note_fn_call(206,34);
    validate_static_evaulate_role_dispatcher();
    role_constant = ISVREF(stack_node_instruction,(SI_Long)12L);
    domain_1_arg = FIRST(argument_list);
    domain_2_arg = CDR(argument_list) ? SECOND(argument_list) : Qnil;
    dispatcher = Nil;
    ab_loop_list_ = Sorted_static_evaluate_role_dispatchers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dispatcher = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(CDR(argument_list)))
	result = FUNCALL_5(dispatcher,role_constant,no_item_allowed_qm,
		unknown_allowed_qm,ISVREF(domain_1_arg,(SI_Long)6L),Nil);
    else
	result = FUNCALL_5(dispatcher,role_constant,no_item_allowed_qm,
		unknown_allowed_qm,ISVREF(domain_1_arg,(SI_Long)6L),
		ISVREF(domain_2_arg,(SI_Long)6L));
    MVS_3(result,specialized_role_qm,instruction_name_qm,
	    refined_value_type_qm);
    if (specialized_role_qm) {
	svref_new_value = phrase_list_2(specialized_role_qm,
		instruction_name_qm);
	SVREF(stack_node_instruction,FIX((SI_Long)13L)) = svref_new_value;
	temp = refined_value_type_qm;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(value_type);
    }
    goto next_loop;
  end_loop:
    SVREF(stack_node_instruction,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(value_type);
    return VALUES_1(Qnil);
}

static Object Qnamed_by;           /* named-by */

static Object Qnamed_by_symbol;    /* named-by-symbol */

/* NAMED-BY-SYMBOL-DISPATCH-PREDICATE */
Object named_by_symbol_dispatch_predicate(role_constant,no_item_allowed_qm,
	    unknown_allowed_qm,domain_arg_type_qm,ingored_domain_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object domain_arg_type_qm, ingored_domain_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,35);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qnamed_by);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(type_specification_subtype_p(domain_arg_type_qm,
	    Qsymbol)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qnamed_by_symbol);
	return VALUES_3(temp_1,Qnil,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qname;               /* name */

static Object Qname_of_item;       /* name-of-item */

/* NAME-OF-ITEM-DISPATCH-PREDICATE */
Object name_of_item_dispatch_predicate(role_constant,no_item_allowed_qm,
	    unknown_allowed_qm,domain_arg_type_qm,ingored_domain_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object domain_arg_type_qm, ingored_domain_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,36);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qname);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(type_specification_subtype_p(domain_arg_type_qm,
	    list_constant_8)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qname_of_item);
	return VALUES_3(temp_1,Qnil,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrelated;            /* related */

static Object Qrelated_to_item;    /* related-to-item */

/* RELATED-TO-ITEM-DISPATCH-PREDICATE */
Object related_to_item_dispatch_predicate(role_constant,no_item_allowed_qm,
	    unknown_allowed_qm,domain_arg_type_qm,ingored_domain_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object domain_arg_type_qm, ingored_domain_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,37);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qrelated);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(type_specification_subtype_p(domain_arg_type_qm,
	    list_constant_8)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qrelated_to_item);
	return VALUES_3(temp_1,Qnil,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qnth_element;        /* nth-element */

static Object list_constant_15;    /* # */

static Object Qnth_element_of_integer_array;  /* nth-element-of-integer-array */

static Object Qnth_integer_array_element;  /* nth-integer-array-element */

/* NTH-ELEMENT-OF-INTEGER-ARRAY-DISPATCH-PREDICATE */
Object nth_element_of_integer_array_dispatch_predicate(role_constant,
	    no_item_allowed_qm,unknown_allowed_qm,array_arg_type_qm,
	    index_arg_type_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object array_arg_type_qm, index_arg_type_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,38);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qnth_element);
    }
    else
	temp = TRUEP(Nil);
    if (((temp ?  !TRUEP(no_item_allowed_qm) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(array_arg_type_qm,
	    list_constant_15)) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(index_arg_type_qm,
	    Qinteger)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qnth_element_of_integer_array);
	return VALUES_3(temp_1,Qnth_integer_array_element,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object Qnth_element_of_float_array;  /* nth-element-of-float-array */

static Object Qnth_float_array_element;  /* nth-float-array-element */

/* NTH-ELEMENT-OF-FLOAT-ARRAY-DISPATCH-PREDICATE */
Object nth_element_of_float_array_dispatch_predicate(role_constant,
	    no_item_allowed_qm,unknown_allowed_qm,array_arg_type_qm,
	    index_arg_type_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object array_arg_type_qm, index_arg_type_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,39);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qnth_element);
    }
    else
	temp = TRUEP(Nil);
    if (((temp ?  !TRUEP(no_item_allowed_qm) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(array_arg_type_qm,
	    list_constant_16)) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(index_arg_type_qm,
	    Qinteger)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qnth_element_of_float_array);
	return VALUES_3(temp_1,Qnth_float_array_element,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

static Object Qnth_element_of_value_array;  /* nth-element-of-value-array */

/* NTH-ELEMENT-OF-VALUE-ARRAY-DISPATCH-PREDICATE */
Object nth_element_of_value_array_dispatch_predicate(role_constant,
	    no_item_allowed_qm,unknown_allowed_qm,array_arg_type_qm,
	    index_arg_type_qm)
    Object role_constant, no_item_allowed_qm, unknown_allowed_qm;
    Object array_arg_type_qm, index_arg_type_qm;
{
    Object role, role_car, temp_1;
    char temp;

    x_note_fn_call(206,40);
    if (CONSP(role_constant)) {
	role = role_constant;
	role_car = M_CAR(role);
	temp = EQ(EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role)) : 
		role_car,Qnth_element);
    }
    else
	temp = TRUEP(Nil);
    if (((temp ?  !TRUEP(no_item_allowed_qm) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(array_arg_type_qm,
	    list_constant_17)) : TRUEP(Nil)) ? 
	    TRUEP(type_specification_subtype_p(index_arg_type_qm,
	    Qinteger)) : TRUEP(Nil)) {
	temp_1 = copy_for_phrase(Qnth_element_of_value_array);
	return VALUES_3(temp_1,Qnil,Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_18;    /* # */

static Object Qattribute_value;    /* attribute-value */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

static Object string_constant_12;  /* "role compiler" */

static Object string_constant_13;  /* "Unknown role type ~a." */

static Object array_constant_3;    /* # */

static Object string_constant_14;  /* "\" requires ~a arguments, but received ~a." */

static Object string_constant_15;  /* "attribute place reference" */

static Object string_constant_16;  /* "Cannot compile concludes or changes on attributes when the ~
				    *                   frame containing the attribute is permitted to be missing.  ~
				    *                   Required type = ~NT, attribute = ~a."
				    */

static Object list_constant_21;    /* # */

static Object Qattribute_of_class;  /* attribute-of-class */

static Object Qpush_constant;      /* push-constant */

static Object Qattribute_frame_or_place_reference;  /* attribute-frame-or-place-reference */

static Object Qclass_qualified_attribute_of_class;  /* class-qualified-attribute-of-class */

static Object Qclass_qualified_name_frame_or_place_reference;  /* class-qualified-name-frame-or-place-reference */

static Object Qelement_frame_or_place_reference;  /* element-frame-or-place-reference */

static Object list_constant_22;    /* # */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* EVALUATE-ROLE-I-CHOOSER */
Object evaluate_role_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, unknown_allowed_qm;
    Object place_reference_allowed_qm, no_item_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, unknown_argument_qm, value_type;
    Object role, role_1, role_car, role_name, attribute_value_role_p;
    Object class_qualified_name_role_p, nth_element_role_p;
    Object domain_required_type_list, type_count, argument_list, arg_count;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_, domain_node_cons;
    Object type_cons_qm, type, ab_loop_iter_flag_, temp_2, domain_type;
    Object domain_class_qm, gensymed_symbol, result_type_qm, argument;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, domain_types, x2;
    Object sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char cons_role_p, symbol_role_p, temp_1;
    Declare_special(5);

    x_note_fn_call(206,41);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    place_reference_allowed_qm = 
	    type_specification_subtype_p(list_constant_18,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    unknown_argument_qm = Nil;
    value_type = Nil;
    role = extra_info;
    if (CONSP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : 
		role_car;
    }
    else
	role_name = Nil;
    cons_role_p = CONSP(role);
    symbol_role_p = SYMBOLP(role);
    attribute_value_role_p = cons_role_p ? (EQ(M_CAR(role),
	    Qattribute_value) ? T : Nil) : Qnil;
    class_qualified_name_role_p = cons_role_p ? (EQ(M_CAR(role),
	    Qclass_qualified_name) ? T : Nil) : Qnil;
    nth_element_role_p = cons_role_p ? (EQ(M_CAR(role),Qnth_element) ? T : 
	    Nil) : Qnil;
    domain_required_type_list = cons_role_p ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
	    Qrequired_domain_types_of_role) : place_reference_allowed_qm ? 
	    list_constant_19 : list_constant_20;
    type_count = length(domain_required_type_list);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    arg_count = length(argument_list);
    if (nth_element_role_p && place_reference_allowed_qm) {
	temp = 
		make_type_specification_union(CAR(domain_required_type_list),
		list_constant_18);
	domain_required_type_list = phrase_cons(temp,
		CDR(domain_required_type_list));
    }
    if ( !SYMBOLP(role) &&  !TRUEP(role_name))
	compiler_bug(3,string_constant_12,string_constant_13,role);
    else if (FIXNUM_NE(type_count,arg_count)) {
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
		  twrite_beginning_of_wide_string(array_constant_3,
			  FIX((SI_Long)10L));
		  print_role(role);
		  tformat(3,string_constant_14,type_count,arg_count);
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
	    temp_1 = TRUEP(T);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1)
	    reclaim_text_string(candidate_string);
	else
	    Compiler_errors = phrase_cons(candidate_string,Compiler_errors);
    }
    domain_node_cons = argument_list;
    type_cons_qm = domain_required_type_list;
    type = Nil;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(domain_node_cons))
	goto end_loop_1;
    if ( !TRUEP(ab_loop_iter_flag_))
	type_cons_qm = CDR(type_cons_qm);
    temp = CAR(type_cons_qm);
    if (temp);
    else
	temp = Qitem_or_datum;
    type = temp;
    type = 
	    maybe_add_unknown(maybe_add_no_item(maybe_add_no_item_implies_unknown(type,
	    no_item_implies_unknown_allowed_qm),no_item_allowed_qm),
	    unknown_allowed_qm);
    temp_2 = choose_stack_node_instructions_and_types(2,
	    M_CAR(domain_node_cons),type);
    M_CAR(domain_node_cons) = temp_2;
    if (type_specification_subtype_p(list_constant_6,
	    ISVREF(M_CAR(domain_node_cons),(SI_Long)6L)))
	unknown_argument_qm = T;
    ab_loop_iter_flag_ = Nil;
    domain_node_cons = M_CDR(domain_node_cons);
    goto next_loop_1;
  end_loop_1:;
    if (symbol_role_p || attribute_value_role_p || 
	    class_qualified_name_role_p || nth_element_role_p) {
	domain_type = 
		type_specification_minus_type(type_specification_minus_type(ISVREF(CAR(argument_list),
		(SI_Long)6L),list_constant_10),list_constant_6);
	domain_class_qm = class_type_specification_p(domain_type) ? 
		M_CAR(M_CDR(domain_type)) : Nil;
	if (place_reference_allowed_qm) {
	    if (no_item_allowed_qm)
		compiler_bug(4,string_constant_15,string_constant_16,
			required_type,role);
	    if (SYMBOLP(role)) {
		if ( 
			!TRUEP(type_specifications_could_intersect_p(domain_type,
			list_constant_21)))
		    record_free_reference(Qattribute_of_class,
			    phrase_cons(role,domain_class_qm));
		compiler_warning_if_superseded_attribute(role);
		gensymed_symbol = 
			make_stack_node_instruction_1_1(Qpush_constant,role);
		Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
			Stack_nodes_to_reclaim);
		temp_2 = 
			stack_cons_1(choose_stack_node_instructions_and_types(2,
			gensymed_symbol,Qsymbol),Nil);
		M_CDR(argument_list) = temp_2;
		arg_count = FIXNUM_ADD1(arg_count);
		role = phrase_list_2(Qattribute_frame_or_place_reference,Nil);
	    }
	    else if (class_qualified_name_role_p) {
		record_free_reference(Qclass_qualified_attribute_of_class,
			phrase_list_3(THIRD(role),SECOND(role),
			domain_class_qm));
		compiler_warning_if_superseded_attribute(THIRD(role));
		role = 
			phrase_cons(Qclass_qualified_name_frame_or_place_reference,
			M_CDR(role));
	    }
	    else if (attribute_value_role_p)
		role = phrase_list_2(Qattribute_frame_or_place_reference,Nil);
	    else if (nth_element_role_p)
		role = phrase_list_2(Qelement_frame_or_place_reference,Nil);
	    else;
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = role;
	    value_type = list_constant_22;
	}
	else if (nth_element_role_p) {
	    temp = domain_class_qm ? 
		    g2_list_or_array_class_element_type(domain_class_qm,T) 
		    : Qnil;
	    if (temp);
	    else
		temp = Qitem_or_datum;
	    value_type = temp;
	}
	else if (attribute_value_role_p) {
	    temp = type_specification_of_role(role);
	    if (temp);
	    else
		temp = Qitem_or_datum;
	    value_type = temp;
	}
	else
	    value_type = Qitem_or_datum;
    }
    else {
	result_type_qm = type_specification_of_role(role);
	argument = Nil;
	ab_loop_list_ = argument_list;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(primary_type_of_type_specification(ISVREF(argument,
		(SI_Long)6L)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	domain_types = ab_loopvar_;
	goto end_2;
	domain_types = Qnil;
      end_2:;
	record_free_references_of_role(2,role,domain_types);
	temp = result_type_qm;
	if (temp);
	else
	    temp = Qitem_or_datum;
	value_type = temp;
    }
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
    if (temp_1)
	SVREF(stack_node_instruction,FIX((SI_Long)13L)) = Nil;
    else
	value_type = 
		choose_optimized_evaluate_role_instruction(stack_node_instruction,
		argument_list,value_type,no_item_allowed_qm,
		unknown_allowed_qm);
    value_type = maybe_add_unknown(maybe_add_no_item(value_type,
	    no_item_allowed_qm),unknown_argument_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = value_type;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_17;  /* "the attribute ~a ~a" */

/* COMPILER-WARNING-IF-SUPERSEDED-ATTRIBUTE */
Object compiler_warning_if_superseded_attribute(attribute)
    Object attribute;
{
    x_note_fn_call(206,42);
    if (attribute_previously_put_in_attribute_tables_p(1,attribute))
	return compiler_warning(3,string_constant_17,attribute,
		Frame_note_for_superseded_attributes_1);
    else
	return VALUES_1(Nil);
}

/* GIVER-OF-VALUE-I-CHOOSER */
Object giver_of_value_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, no_item_allowed_qm, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, type, argument_list, temp;

    x_note_fn_call(206,43);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    type = 
	    maybe_add_no_item_implies_unknown(maybe_add_unknown(maybe_add_no_item(make_class_type_specification(extra_info),
	    no_item_allowed_qm),unknown_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    record_free_reference(Qab_class,extra_info);
    temp = choose_stack_node_instructions_and_types(2,M_CAR(argument_list),
	    type);
    M_CAR(argument_list) = temp;
    temp = ISVREF(M_CAR(argument_list),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_18;  /* "instruction chooser" */

static Object string_constant_19;  /* "No type could be determined for var-spot ~a." */

/* PUSH-FROM-SURROUNDING-LOCAL-VAR-I-CHOOSER */
Object push_from_surrounding_local_var_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, type_qm, no_item_allowed_qm;
    Object svref_new_value;

    x_note_fn_call(206,44);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    type_qm = var_spot_type(extra_info,Lexically_visible_code_bodies);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    if ( !TRUEP(type_qm)) {
	compiler_bug(3,string_constant_18,string_constant_19,extra_info);
	type_qm = required_type;
    }
    svref_new_value = maybe_add_no_item(type_qm,no_item_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_20;  /* "copy into surrounding local var instruction chooser" */

/* COPY-INTO-SURROUNDING-LOCAL-VAR-I-CHOOSER */
Object copy_into_surrounding_local_var_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, type_qm, argument_list, temp, temp_1;
    Object temp_2;

    x_note_fn_call(206,45);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    type_qm = var_spot_type(extra_info,Lexically_visible_code_bodies);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    if ( !TRUEP(type_qm)) {
	compiler_bug(3,string_constant_20,string_constant_19,extra_info);
	type_qm = required_type;
    }
    temp = M_CAR(argument_list);
    temp_1 = make_type_specification_intersection(required_type,
	    add_secondary_type_specifications(type_qm,required_type));
    temp_2 = choose_stack_node_instructions_and_types(4,temp,temp_1,Nil,
	    ISVREF(stack_node_instruction,(SI_Long)11L));
    M_CAR(argument_list) = temp_2;
    temp_2 = ISVREF(CAR(argument_list),(SI_Long)6L);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp_2;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_21;  /* "In move-from-surrounding-local-var, no type could be determined or  ~
				    *            no-item allowed.  Var-spot ~a, type = ~a."
				    */

/* MOVE-FROM-SURROUNDING-LOCAL-VAR-I-CHOOSER */
Object move_from_surrounding_local_var_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, type_qm, no_item_allowed_qm;

    x_note_fn_call(206,46);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    type_qm = var_spot_type(extra_info,Lexically_visible_code_bodies);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    if ( !TRUEP(type_qm) || no_item_allowed_qm) {
	compiler_bug(4,string_constant_18,string_constant_21,extra_info,
		required_type);
	type_qm = required_type;
    }
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = type_qm;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_23;    /* # */

static Object list_constant_24;    /* # */

/* COERCE-TO-DATUM-I-CHOOSER */
Object coerce_to_datum_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, stripped_required_type, argument_list, argument_node;
    Object argument_type, unknown_allowed_qm, no_item_allowed_qm;
    Object no_item_implies_unknown_qm, argument_could_be_datum_qm;
    Object stripped_desired_value_type, desired_primary_type_of_sub_node_qm;
    Object temp, required_type_of_sub_node, held_type_qm, svref_new_value;

    x_note_fn_call(206,47);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    stripped_required_type = primary_type_of_type_specification(required_type);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_node = M_CAR(argument_list);
    argument_type = ISVREF(argument_node,(SI_Long)6L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    no_item_implies_unknown_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    argument_could_be_datum_qm = 
	    type_specifications_could_intersect_p(Qdatum,argument_type);
    stripped_desired_value_type = EQ(stripped_required_type,Qfloat) ? 
	    Qnumber : stripped_required_type;
    desired_primary_type_of_sub_node_qm = 
	    datum_type_specification_p(stripped_required_type) ? 
	    (unknown_allowed_qm ? 
	    type_specification_returning_datum_type_or_unknown(2,
	    stripped_desired_value_type,T) : 
	    type_specification_returning_datum_type(2,
	    stripped_desired_value_type,T)) : Nil;
    if (argument_could_be_datum_qm)
	temp = Qitem_or_datum;
    else if (class_type_specification_p(desired_primary_type_of_sub_node_qm))
	temp = desired_primary_type_of_sub_node_qm;
    else if (unknown_allowed_qm)
	temp = list_constant_23;
    else
	temp = list_constant_24;
    required_type_of_sub_node = 
	    maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(temp,
	    unknown_allowed_qm),no_item_allowed_qm),
	    no_item_implies_unknown_qm);
    argument_node = choose_stack_node_instructions_and_types(4,
	    argument_node,required_type_of_sub_node,T,
	    desired_primary_type_of_sub_node_qm);
    M_CAR(argument_list) = argument_node;
    argument_type = ISVREF(argument_node,(SI_Long)6L);
    held_type_qm = type_specification_held_in_type(argument_type);
    svref_new_value =  !TRUEP(held_type_qm) ? (unknown_allowed_qm ? 
	    list_constant : maybe_add_no_item(Qdatum,no_item_allowed_qm)) :
	     held_type_qm;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = svref_new_value;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COERCE-NO-ITEM-TO-UNKNOWN-I-CHOOSER */
Object coerce_no_item_to_unknown_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_list, temp, value_type;

    x_note_fn_call(206,48);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_list = ISVREF(stack_node_instruction,(SI_Long)2L);
    temp = choose_stack_node_instructions_and_types(4,CAR(argument_list),
	    required_type,T,ISVREF(stack_node_instruction,(SI_Long)11L));
    M_CAR(argument_list) = temp;
    value_type = ISVREF(CAR(argument_list),(SI_Long)6L);
    temp = type_specification_minus_type(maybe_add_unknown(value_type,
	    type_specification_not_subtype_p(list_constant_6,value_type) ? 
	    type_specification_subtype_p(list_constant_10,value_type) : 
	    Qnil),list_constant_10);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ENSURE-TYPE-I-CHOOSER */
Object ensure_type_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_node, return_type, temp, temp_1;
    char temp_2;

    x_note_fn_call(206,49);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_node = M_CAR(ISVREF(stack_node_instruction,(SI_Long)2L));
    return_type = Nil;
    argument_node = choose_stack_node_instructions_and_types(4,
	    argument_node,required_type,T,ISVREF(stack_node_instruction,
	    (SI_Long)11L));
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    M_CAR(temp) = argument_node;
    return_type = ISVREF(argument_node,(SI_Long)6L);
    if (type_specification_subtype_p(return_type,required_type))
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = return_type;
    else {
	if (type_specification_subtype_p(list_constant_10,return_type)) {
	    temp_1 = type_specification_minus_type(return_type,
		    list_constant_10);
	    temp_2 = TRUEP(type_specification_subtype_p(temp_1,required_type));
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp = type_specification_union_minus_type(return_type,
		    list_constant_10);
	    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
	}
	else {
	    required_type = type_specification_minus_type(required_type,
		    list_constant_14);
	    if (type_specification_subtype_p(list_constant_6,
		    required_type) && 
		    type_specification_not_subtype_p(list_constant_6,
		    return_type))
		required_type = 
			type_specification_minus_type(required_type,
			list_constant_6);
	    if (type_specification_subtype_p(list_constant_10,
		    required_type) && 
		    type_specification_not_subtype_p(list_constant_10,
		    return_type))
		required_type = 
			type_specification_minus_type(required_type,
			list_constant_10);
	    required_type = 
		    type_specification_minimal_required_type(required_type,
		    return_type);
	    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = required_type;
	}
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* TYPE-SPECIFICATION-MINIMAL-REQUIRED-TYPE */
Object type_specification_minimal_required_type(required_type,return_type)
    Object required_type, return_type;
{
    Object subsetted_required_type, sub_required_type, ab_loop_list_;
    Object sub_return_type, ab_loop_list__1, ab_loop_it_, temp_1;
    char temp;

    x_note_fn_call(206,50);
    if (union_type_specification_p(required_type)) {
	subsetted_required_type = required_type;
	sub_required_type = Nil;
	ab_loop_list_ = CDR(required_type);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_required_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = 
		TRUEP(type_specifications_could_intersect_p(sub_required_type,
		return_type));
	if (temp);
	else if (valid_datum_type_specification_p(sub_required_type)) {
	    if (union_type_specification_p(return_type)) {
		sub_return_type = Nil;
		ab_loop_list__1 = CDR(return_type);
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		sub_return_type = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		ab_loop_it_ = 
			datum_type_specifications_could_be_coerced_p(sub_return_type,
			sub_required_type);
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop_1;
	      end_loop_1:
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = 
			TRUEP(datum_type_specifications_could_be_coerced_p(return_type,
			sub_required_type));
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    subsetted_required_type = 
		    type_specification_minus_type(subsetted_required_type,
		    sub_required_type);
	goto next_loop;
      end_loop:
	temp_1 = subsetted_required_type;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
    }
    else
	temp_1 = required_type;
    return VALUES_1(temp_1);
}

/* EXECUTE-NORMAL-FORM-TREE-I-CHOOSER */
Object execute_normal_form_tree_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, argument_nodes, primary_value_type;
    Object unknown_allowed_qm, argument_cons, argument_type, temp;

    x_note_fn_call(206,51);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    primary_value_type = Nil;
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    argument_cons = argument_nodes;
    argument_type = Nil;
  next_loop:
    if ( !TRUEP(argument_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(4,M_CAR(argument_cons),
	    required_type,Nil,ISVREF(stack_node_instruction,(SI_Long)11L));
    M_CAR(argument_cons) = temp;
    argument_type = ISVREF(M_CAR(argument_cons),(SI_Long)6L);
    primary_value_type = most_general_primary_type(argument_type,
	    primary_value_type);
    if (type_specification_subtype_p(list_constant_6,argument_type))
	unknown_allowed_qm = T;
    argument_cons = M_CDR(argument_cons);
    goto next_loop;
  end_loop:;
    if (unknown_allowed_qm) {
	temp = make_type_specification_union(primary_value_type,
		list_constant_6);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    }
    else
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = primary_value_type;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_25;    /* # */

/* CALL-PROCEDURE-I-CHOOSER */
Object call_procedure_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object sub_nodes, argument_nodes, car_new_value, arg_cons;

    x_note_fn_call(206,52);
    sub_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_nodes = CDR(sub_nodes);
    car_new_value = choose_stack_node_instructions_and_types(2,
	    CAR(sub_nodes),list_constant_25);
    M_CAR(sub_nodes) = car_new_value;
    arg_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(arg_cons))
	goto end_loop;
    car_new_value = choose_stack_node_instructions_and_types(2,
	    CAR(arg_cons),Qitem_or_datum);
    M_CAR(arg_cons) = car_new_value;
    arg_cons = M_CDR(arg_cons);
    goto next_loop;
  end_loop:;
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = Qitem_or_datum;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qpush_cached_item;   /* push-cached-item */

static Object Qfunction_call;      /* function-call */

/* CALL-FUNCTION-I-CHOOSER */
Object call_function_i_chooser(stack_node_instruction)
    Object stack_node_instruction;
{
    Object required_type, extra_info, unknown_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, no_item_allowed_qm, arg_type;
    Object unknown_arg_qm, sub_nodes, extra_info_second_qm;
    Object symbol_designation_qm, argument_nodes, temp, arg_cons;
    Object argument_node, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_2;
    char temp_1;

    x_note_fn_call(206,53);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    extra_info = ISVREF(stack_node_instruction,(SI_Long)12L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    arg_type = 
	    maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(Qitem_or_datum,
	    unknown_allowed_qm),no_item_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    unknown_arg_qm = Nil;
    sub_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    extra_info_second_qm = extra_info && CONSP(extra_info) && 
	    M_CDR(extra_info) ? M_CAR(M_CDR(extra_info)) : Qnil;
    symbol_designation_qm = SYMBOLP(extra_info_second_qm) ? 
	    extra_info_second_qm : Qnil;
    argument_nodes = CDR(sub_nodes);
    temp = choose_stack_node_instructions_and_types(2,CAR(sub_nodes),
	    unknown_allowed_qm ? list_constant_25 : list_constant_8);
    M_CAR(sub_nodes) = temp;
    if (unknown_allowed_qm && type_specification_subtype_p(list_constant_6,
	    ISVREF(CAR(sub_nodes),(SI_Long)6L)))
	unknown_arg_qm = T;
    arg_cons = argument_nodes;
  next_loop:
    if ( !TRUEP(arg_cons))
	goto end_loop;
    temp = choose_stack_node_instructions_and_types(2,CAR(arg_cons),arg_type);
    M_CAR(arg_cons) = temp;
    if (unknown_allowed_qm && type_specification_subtype_p(list_constant_6,
	    ISVREF(CAR(arg_cons),(SI_Long)6L)))
	unknown_arg_qm = T;
    arg_cons = M_CDR(arg_cons);
    goto next_loop;
  end_loop:;
    if (unknown_arg_qm) {
	if (extra_info && CONSP(extra_info)) {
	    temp = generate_new_stack_frame_var_spot(Qdatum);
	    temp_1 = TRUEP(M_FIRST(extra_info) = temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = phrase_list_2(generate_new_stack_frame_var_spot(Qdatum),
		    Nil);
	    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = temp;
	}
    }
    if (symbol_designation_qm && EQ(ISVREF(CAR(sub_nodes),(SI_Long)1L),
	    Qpush_cached_item)) {
	argument_node = Nil;
	ab_loop_list_ = argument_nodes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(type_specification_minus_type(type_specification_minus_type(ISVREF(argument_node,
		(SI_Long)6L),list_constant_6),list_constant_10),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	record_free_reference(Qfunction_call,
		phrase_list_2(symbol_designation_qm,temp_2));
    }
    temp = maybe_add_unknown(maybe_add_no_item(maybe_add_unknown(Qdatum,
	    unknown_allowed_qm),no_item_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    SVREF(stack_node_instruction,FIX((SI_Long)6L)) = temp;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* DUMMY-INSTRUCTION-I-EMIT */
Object dummy_instruction_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,54);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* NO-OP-I-EMIT */
Object no_op_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,55);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PUSH-CONSTANT-I-EMIT */
Object push_constant_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,56);
    emit_push_constant_byte_codes(byte_code_stream,extra_info);
    SVREF(stack_node_instruction,FIX((SI_Long)12L)) = Nil;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PUSH-CONSTANT-I-RECLAIM */
Object push_constant_i_reclaim(extra_info)
    Object extra_info;
{
    x_note_fn_call(206,57);
    if ( !(FIXNUMP(extra_info) || SYMBOLP(extra_info) || 
	    SIMPLE_VECTOR_P(extra_info)))
	reclaim_if_evaluation_value_1(extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PUSH-CONSTANT-I-COPY */
Object push_constant_i_copy(instruction_original)
    Object instruction_original;
{
    Object thing;

    x_note_fn_call(206,58);
    thing = ISVREF(instruction_original,(SI_Long)12L);
    GENSYM_RETURN_ONE(FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : 
	    copy_if_evaluation_value_1(thing));
    return VALUES_1(Nil);
}

/* NAME-REFERENCE-I-EMIT */
Object name_reference_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,59);
    emit_name_reference_byte_codes(byte_code_stream,extra_info,
	    type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)6L)));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* PUSH-CACHED-ITEM-I-EMIT */
Object push_cached_item_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object name, stable_item_qm, required_type, temp;

    x_note_fn_call(206,60);
    name = extra_info;
    stable_item_qm = dependent_compilation_p(0) ? stable_name_p(1,name) : Nil;
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    emit_push_cached_item_byte_codes(byte_code_stream,extra_info,
	    type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)6L)));
    if ( !TRUEP(stable_item_qm)) {
	temp = ISVREF(stack_node_instruction,(SI_Long)11L);
	if (temp);
	else
	    temp = 
		    type_specification_minus_type(type_specification_minus_type(type_specification_minus_type(required_type,
		    list_constant_6),list_constant_10),list_constant_14);
	record_free_reference(Qname_of_type,phrase_cons(name,temp));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_stack_node_instruction_g2_struct;  /* g2-defstruct-structure-name::stack-node-instruction-g2-struct */

static Object Qname_reference;     /* name-reference */

static Object Qensure_type;        /* ensure-type */

/* GET-DENOTED-ITEM-NAME-IF-ANY */
Object get_denoted_item_name_if_any(stack_node_tree)
    Object stack_node_tree;
{
    Object operation;

    x_note_fn_call(206,61);
    if (SIMPLE_VECTOR_P(stack_node_tree) && EQ(ISVREF(stack_node_tree,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct)) {
	operation = ISVREF(stack_node_tree,(SI_Long)1L);
	if (EQ(operation,Qname_reference))
	    return VALUES_1(ISVREF(stack_node_tree,(SI_Long)12L));
	else if (EQ(operation,Qpush_cached_item))
	    return VALUES_1(ISVREF(stack_node_tree,(SI_Long)12L));
	else if (EQ(operation,Qensure_type)) {
	    if (type_specifications_could_intersect_p(ISVREF(stack_node_tree,
		    (SI_Long)5L),list_constant_8))
		return get_denoted_item_name_if_any(M_CAR(ISVREF(stack_node_tree,
			(SI_Long)2L)));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PUSH-FROM-SURROUNDING-LOCAL-VAR-I-EMIT */
Object push_from_surrounding_local_var_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,62);
    if (type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)5L)))
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		extra_info);
    else
	emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
		extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COPY-INTO-SURROUNDING-LOCAL-VAR-I-EMIT */
Object copy_into_surrounding_local_var_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp;

    x_note_fn_call(206,63);
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    emit_stack_node_tree(byte_code_stream,CAR(temp));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* MOVE-FROM-SURROUNDING-LOCAL-VAR-I-EMIT */
Object move_from_surrounding_local_var_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,64);
    emit_move_from_surrounding_local_var_byte_codes(byte_code_stream,
	    extra_info);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EVALUATE-ROLE-WITH-NO-DOMAIN-I-EMIT */
Object evaluate_role_with_no_domain_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    x_note_fn_call(206,65);
    emit_evaluate_role_with_no_domain_byte_codes(byte_code_stream,
	    extra_info,type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)6L)));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EVALUATE-ROLE-I-EMIT */
Object evaluate_role_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, domain_1_item_name_qm, domain_1_value_type;
    Object argument_node, ab_loop_list_, first_domain_qm;

    x_note_fn_call(206,66);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    domain_1_item_name_qm = Nil;
    domain_1_value_type = Nil;
    argument_node = Nil;
    ab_loop_list_ = argument_nodes;
    first_domain_qm = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument_node);
    if (first_domain_qm) {
	domain_1_item_name_qm = get_denoted_item_name_if_any(argument_node);
	domain_1_value_type = ISVREF(argument_node,(SI_Long)6L);
    }
    first_domain_qm = Nil;
    goto next_loop;
  end_loop:;
    emit_evaluate_role_byte_codes(byte_code_stream,extra_info,
	    length(argument_nodes),
	    type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)6L)),
	    domain_1_item_name_qm,domain_1_value_type,
	    ISVREF(stack_node_instruction,(SI_Long)13L));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EVALUATE-ROLE-IMPLICIT-SCOPE-I-EMIT */
Object evaluate_role_implicit_scope_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, var_spot, last_val, argument_node, ab_loop_list_;

    x_note_fn_call(206,67);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    var_spot = Nil;
    last_val = Nil;
    argument_node = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument_node);
    goto next_loop;
  end_loop:;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)77L));
    var_spot = extra_info;
    last_val = 
	    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* GIVER-OF-VALUE-I-EMIT */
Object giver_of_value_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_node, ab_loop_list_;

    x_note_fn_call(206,68);
    argument_node = Nil;
    ab_loop_list_ = ISVREF(stack_node_instruction,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument_node);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COERCE-TO-DATUM-I-EMIT */
Object coerce_to_datum_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp, argument_type, required_type, no_item_allowed_qm;
    Object argument_node, ab_loop_list_;

    x_note_fn_call(206,69);
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_type = ISVREF(CAR(temp),(SI_Long)6L);
    required_type = ISVREF(stack_node_instruction,(SI_Long)5L);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    argument_node = Nil;
    ab_loop_list_ = ISVREF(stack_node_instruction,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument_node);
    goto next_loop;
  end_loop:;
    if (type_specification_subtype_p(argument_type,list_constant_24))
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)47L));
    else if (type_specification_subtype_p(argument_type,list_constant_23) 
	    && type_specification_subtype_p(list_constant_6,required_type))
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)74L));
    else if (type_specification_subtype_p(list_constant_6,required_type))
	emit_coerce_to_datum_or_unknown_byte_codes(byte_code_stream,
		no_item_allowed_qm);
    else
	emit_coerce_to_datum_byte_codes(byte_code_stream,no_item_allowed_qm);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcoerce_no_item_to_unknown;  /* coerce-no-item-to-unknown */

/* COERCE-NO-ITEM-TO-UNKNOWN-I-EMIT */
Object coerce_no_item_to_unknown_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object temp, argument_node;

    x_note_fn_call(206,70);
    temp = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_node = CAR(temp);
    emit_stack_node_tree(byte_code_stream,argument_node);
    if ( !TRUEP(type_specification_not_subtype_p(list_constant_10,
	    ISVREF(argument_node,(SI_Long)6L))))
	emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qcoerce_no_item_to_unknown);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qlong;               /* long */

/* ENSURE-TYPE-I-EMIT */
Object ensure_type_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object argument_nodes, raw_argument_type, argument_type, raw_required_type;
    Object required_type, argument_remainder, argument_node, ab_loop_list_;

    x_note_fn_call(206,71);
    argument_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    raw_argument_type = ISVREF(M_CAR(argument_nodes),(SI_Long)6L);
    argument_type = type_specification_minus_type(raw_argument_type,
	    list_constant_6);
    raw_required_type = ISVREF(stack_node_instruction,(SI_Long)6L);
    required_type = 
	    type_specification_minus_type(type_specification_minus_type(raw_required_type,
	    list_constant_6),list_constant_14);
    if (type_specification_subtype_p(list_constant_10,argument_type) &&  
	    !TRUEP(type_specification_subtype_p(list_constant_10,
	    required_type))) {
	argument_remainder = type_specification_minus_type(argument_type,
		list_constant_10);
	if (type_specification_subtype_p(argument_remainder,required_type))
	    required_type = argument_remainder;
    }
    argument_node = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,argument_node);
    goto next_loop;
  end_loop:;
    if (type_specification_subtype_p(argument_type,required_type));
    else if (type_specification_subtype_p(argument_type,Qinteger) && 
	    type_specification_subtype_p(required_type,Qfloat))
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)48L));
    else if (type_specification_subtype_p(argument_type,Qnumber) && 
	    type_specification_subtype_p(required_type,Qfloat))
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)49L));
    else if (type_specification_subtype_p(argument_type,Qinteger) && 
	    type_specification_subtype_p(required_type,Qlong))
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)144L));
    else if (type_specifications_could_intersect_p(argument_type,
	    required_type) || type_specification_subtype_p(required_type,
	    Qfloat) && type_specifications_could_intersect_p(argument_type,
	    Qnumber))
	emit_type_check_byte_codes(byte_code_stream,required_type);
    else
	emit_type_check_byte_codes(byte_code_stream,required_type);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_22;  /* "The result of an expression was required to be of type ~NT, but it returned type ~NT." */

/* CHECK-ENSURE-TYPE-NODES */
Object check_ensure_type_nodes(stack_node)
    Object stack_node;
{
    Object argument_node, ab_loop_list_, argument_nodes, raw_argument_type;
    Object argument_type, raw_required_type, required_type, argument_remainder;

    x_note_fn_call(206,72);
    argument_node = Nil;
    ab_loop_list_ = ISVREF(stack_node,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    check_ensure_type_nodes(argument_node);
    goto next_loop;
  end_loop:;
    if (SIMPLE_VECTOR_P(stack_node) && EQ(ISVREF(stack_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct) 
	    && EQ(ISVREF(stack_node,(SI_Long)1L),Qensure_type)) {
	argument_nodes = ISVREF(stack_node,(SI_Long)2L);
	raw_argument_type = ISVREF(M_CAR(argument_nodes),(SI_Long)6L);
	argument_type = type_specification_minus_type(raw_argument_type,
		list_constant_6);
	raw_required_type = ISVREF(stack_node,(SI_Long)6L);
	required_type = 
		type_specification_minus_type(type_specification_minus_type(raw_required_type,
		list_constant_6),list_constant_14);
	if (type_specification_subtype_p(list_constant_10,argument_type)) {
	    argument_remainder = 
		    type_specification_minus_type(argument_type,
		    list_constant_10);
	    if (type_specification_subtype_p(argument_remainder,required_type))
		required_type = argument_remainder;
	}
	if (type_specification_subtype_p(argument_type,required_type))
	    return VALUES_1(Nil);
	else if (type_specification_subtype_p(argument_type,Qinteger) && 
		type_specification_subtype_p(required_type,Qfloat))
	    return VALUES_1(Nil);
	else if (type_specification_subtype_p(argument_type,Qinteger) && 
		type_specification_subtype_p(required_type,Qlong))
	    return VALUES_1(Nil);
	else if (type_specification_subtype_p(argument_type,Qnumber) && 
		type_specification_subtype_p(required_type,Qfloat))
	    return VALUES_1(Nil);
	else if (type_specifications_could_intersect_p(argument_type,
		required_type) || 
		type_specification_subtype_p(required_type,Qfloat) && 
		type_specifications_could_intersect_p(argument_type,Qnumber))
	    return VALUES_1(Nil);
	else
	    return compiler_error(3,string_constant_22,required_type,
		    argument_type);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* "normal form tree emitter" */

static Object string_constant_24;  /* "Normal form tree has no arguments with expirations." */

/* EXECUTE-NORMAL-FORM-TREE-I-EMIT */
Object execute_normal_form_tree_i_emit(stack_node_instruction,
	    byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object known_tag, end_of_expression_tag, reversed_variables, arg_nodes;
    Object trivial_tree, expiration_nodes, node, ab_loop_list_, var_spot_qm;

    x_note_fn_call(206,73);
    known_tag = generate_new_goto_tag();
    end_of_expression_tag = generate_new_goto_tag();
    reversed_variables = extra_info;
    arg_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    trivial_tree = CAR(arg_nodes);
    expiration_nodes = CDR(arg_nodes);
    if ( !TRUEP(reversed_variables) ||  !TRUEP(expiration_nodes))
	compiler_bug(2,string_constant_23,string_constant_24);
    else {
	node = Nil;
	ab_loop_list_ = expiration_nodes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_stack_node_tree(byte_code_stream,node);
	goto next_loop;
      end_loop:;
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_tag);
	emit_pop_values_byte_codes(byte_code_stream,length(expiration_nodes));
	emit_push_nones_byte_codes(byte_code_stream,FIX((SI_Long)1L));
	emit_branch_long_byte_codes(byte_code_stream,end_of_expression_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_tag);
	var_spot_qm = Nil;
	ab_loop_list_ = reversed_variables;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	var_spot_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (var_spot_qm)
	    emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		    var_spot_qm);
	goto next_loop_1;
      end_loop_1:;
	emit_stack_node_tree(byte_code_stream,trivial_tree);
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_expression_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-PROCEDURE-I-EMIT */
Object call_procedure_i_emit(stack_node_instruction,byte_code_stream,
	    extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object sub_nodes, argument_nodes, arg_node, ab_loop_list_;

    x_note_fn_call(206,74);
    sub_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_nodes = CDR(sub_nodes);
    arg_node = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg_node);
    goto next_loop;
  end_loop:;
    emit_stack_node_tree(byte_code_stream,CAR(sub_nodes));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)143L));
    write_byte_code_to_stream(byte_code_stream,length(argument_nodes));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CALL-FUNCTION-I-EMIT */
Object call_function_i_emit(stack_node_instruction,byte_code_stream,extra_info)
    Object stack_node_instruction, byte_code_stream, extra_info;
{
    Object sub_nodes, argument_nodes, unknown_allowed_qm, no_item_allowed_qm;
    Object expiration_cache_qm, end_of_function_tag, known_args_tag, arg_node;
    Object ab_loop_list_;

    x_note_fn_call(206,75);
    sub_nodes = ISVREF(stack_node_instruction,(SI_Long)2L);
    argument_nodes = CDR(sub_nodes);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    ISVREF(stack_node_instruction,(SI_Long)5L));
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node_instruction,(SI_Long)5L));
    expiration_cache_qm = extra_info && CONSP(extra_info) ? 
	    M_CAR(extra_info) : Qnil;
    end_of_function_tag = expiration_cache_qm ? generate_new_goto_tag() : Nil;
    known_args_tag = expiration_cache_qm ? generate_new_goto_tag() : Nil;
    if (expiration_cache_qm) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)21L));
	emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_cache_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)17L));
    }
    arg_node = Nil;
    ab_loop_list_ = argument_nodes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_stack_node_tree(byte_code_stream,arg_node);
    goto next_loop;
  end_loop:;
    emit_push_constant_byte_codes(byte_code_stream,unknown_allowed_qm ? 
	    Evaluation_true_value : Evaluation_false_value);
    emit_push_constant_byte_codes(byte_code_stream,no_item_allowed_qm ? 
	    Evaluation_true_value : Evaluation_false_value);
    emit_stack_node_tree(byte_code_stream,CAR(sub_nodes));
    if (expiration_cache_qm) {
	emit_branch_long_if_known_byte_codes(byte_code_stream,known_args_tag);
	emit_pop_values_byte_codes(byte_code_stream,
		FIX(IFIX(length(argument_nodes)) + (SI_Long)2L));
	emit_branch_long_byte_codes(byte_code_stream,end_of_function_tag);
	register_tag_in_byte_code_stream(2,byte_code_stream,known_args_tag);
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)94L));
    write_byte_code_to_stream(byte_code_stream,length(argument_nodes));
    if (expiration_cache_qm) {
	emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
		expiration_cache_qm);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)23L));
	register_tag_in_byte_code_stream(2,byte_code_stream,
		end_of_function_tag);
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qstack_node_instruction_emitter;  /* stack-node-instruction-emitter */

static Object string_constant_25;  /* "stack node emitter" */

static Object string_constant_26;  /* "The stack node instruction ~a had no byte code emitter." */

static Object string_constant_27;  /* "A preferred evaluator had not been chosen for ~a." */

/* EMIT-STACK-NODE-TREE */
Object emit_stack_node_tree(byte_code_stream,stack_node)
    Object byte_code_stream, stack_node;
{
    Object stack_frame_vars, operation, emitter, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object chosen_description, no_item_possible, tag_after_evaluator;
    Object argument_node, ab_loop_list_;

    x_note_fn_call(206,76);
    stack_frame_vars = ISVREF(stack_node,(SI_Long)9L);
    if (IFIX(stack_frame_vars) > (SI_Long)0L)
	emit_push_nones_byte_codes(byte_code_stream,stack_frame_vars);
    if (SIMPLE_VECTOR_P(stack_node) && EQ(ISVREF(stack_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct)) {
	operation = ISVREF(stack_node,(SI_Long)1L);
	emitter = getfq_function_no_default(INLINE_SYMBOL_PLIST(operation),
		Qstack_node_instruction_emitter);
	if (emitter) {
	    gensymed_symbol = emitter;
	    gensymed_symbol_1 = stack_node;
	    gensymed_symbol_2 = byte_code_stream;
	    gensymed_symbol_3 = ISVREF(stack_node,(SI_Long)12L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    compiler_bug(3,string_constant_25,string_constant_26,operation);
    }
    else {
	chosen_description = ISVREF(stack_node,(SI_Long)4L);
	no_item_possible = Nil;
	tag_after_evaluator = Nil;
	argument_node = Nil;
	ab_loop_list_ = ISVREF(stack_node,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_stack_node_tree(byte_code_stream,argument_node);
	if (type_specification_subtype_p(list_constant_10,
		ISVREF(argument_node,(SI_Long)6L)))
	    no_item_possible = T;
	goto next_loop;
      end_loop:;
	if (no_item_possible &&  
		!TRUEP(can_accept_no_item_args(chosen_description))) {
	    tag_after_evaluator = generate_new_goto_tag();
	    emit_allow_no_item_for_evaluator_byte_codes(byte_code_stream,
		    length(ISVREF(stack_node,(SI_Long)2L)),
		    tag_after_evaluator);
	}
	if ( !TRUEP(chosen_description))
	    compiler_bug(2,string_constant_25,string_constant_27);
	else if (ISVREF(chosen_description,(SI_Long)8L))
	    write_byte_code_to_stream(byte_code_stream,
		    ISVREF(chosen_description,(SI_Long)9L));
	else
	    emit_funcall_evaluator_byte_codes(byte_code_stream,
		    ISVREF(chosen_description,(SI_Long)9L));
	if (tag_after_evaluator)
	    register_tag_in_byte_code_stream(2,byte_code_stream,
		    tag_after_evaluator);
    }
    if (IFIX(stack_frame_vars) > (SI_Long)0L)
	return emit_pop_copy_down_the_stack_byte_codes(byte_code_stream,
		stack_frame_vars);
    else
	return VALUES_1(Nil);
}

static Object list_constant_26;    /* # */

/* CAN-ACCEPT-NO-ITEM-ARGS */
Object can_accept_no_item_args(chosen_description)
    Object chosen_description;
{
    Object temp;

    x_note_fn_call(206,77);
    temp = memq_function(ISVREF(chosen_description,(SI_Long)0L),
	    list_constant_26);
    return VALUES_1(temp);
}

/* EMIT-STACK-NODE-TREE-OR-NIL */
Object emit_stack_node_tree_or_nil(byte_code_stream,stack_node_qm)
    Object byte_code_stream, stack_node_qm;
{
    x_note_fn_call(206,78);
    if (stack_node_qm)
	return emit_stack_node_tree(byte_code_stream,stack_node_qm);
    else
	return emit_push_constant_byte_codes(byte_code_stream,Nil);
}

static Object Qstack_evaluators;   /* stack-evaluators */

static Object string_constant_28;  /* "op-code-for-operator-of-type" */

static Object string_constant_29;  /* "Can't find evaluator for ~a of ~NT." */

/* EMIT-OPERATOR-OF-TYPE */
Object emit_operator_of_type(byte_code_stream,operator_1,type_specification_1)
    Object byte_code_stream, operator_1, type_specification_1;
{
    Object preferred_evaluator_qm, type_specification, evaluator_description;
    Object ab_loop_list_;

    x_note_fn_call(206,79);
    preferred_evaluator_qm = Nil;
    type_specification = 
	    type_specification_minus_type(type_specification_minus_type(type_specification_1,
	    list_constant_6),list_constant_10);
    evaluator_description = Nil;
    ab_loop_list_ = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
	    Qstack_evaluators);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    evaluator_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (type_specification_subtype_p(type_specification,
	    ISVREF(evaluator_description,(SI_Long)5L)) && ( 
	    !TRUEP(preferred_evaluator_qm) || 
	    FIXNUM_LE(ISVREF(evaluator_description,(SI_Long)2L),
	    ISVREF(preferred_evaluator_qm,(SI_Long)2L))))
	preferred_evaluator_qm = evaluator_description;
    goto next_loop;
  end_loop:;
    if ( !TRUEP(preferred_evaluator_qm))
	return compiler_bug(4,string_constant_28,string_constant_29,
		operator_1,type_specification);
    else if (ISVREF(preferred_evaluator_qm,(SI_Long)8L))
	return write_byte_code_to_stream(byte_code_stream,
		ISVREF(preferred_evaluator_qm,(SI_Long)9L));
    else
	return emit_funcall_evaluator_byte_codes(byte_code_stream,
		ISVREF(preferred_evaluator_qm,(SI_Long)9L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Already_mutated_evaluators, Qalready_mutated_evaluators);

static Object Qab_structure;       /* structure */

static Object Qstack_special_form_converter;  /* stack-special-form-converter */

static Object Qcall_function;      /* call-function */

static Object Qdoes_not_exist;     /* does-not-exist */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* CONVERT-EXPRESSION-TO-STACK-NODE-TREE */
Object convert_expression_to_stack_node_tree(expression)
    Object expression;
{
    Object expression_bound_local_names, gensymed_symbol;
    Object evaluation_sequence_or_structure, value, temp, operator_1;
    Object special_form_converter_qm, stack_evaluator_descriptions_qm;
    Object gensymed_symbol_1, node, current_evaluator_number, first_evaluator;
    Object temp_1, argument, ab_loop_list_, arg_nodes, ab_loopvar_;
    Object ab_loopvar__1, amf_available_array_cons_qm, amf_array, temp_2;
    Object amf_result, new_float;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(206,80);
    expression_bound_local_names = Expression_bound_local_names;
    PUSH_SPECIAL_WITH_SYMBOL(Expression_bound_local_names,Qexpression_bound_local_names,expression_bound_local_names,
	    0);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(expression) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expression)) == (SI_Long)1L) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  copy_evaluation_float_from_phrase_float(expression));
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (INLINE_LONG_VECTOR_P(expression) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expression)) == (SI_Long)1L) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  copy_evaluation_long_from_phrase_long(expression));
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (CONSP(expression) && EQ(M_CDR(expression),
	      Phrase_sequence_marker) || CONSP(expression) && 
	      EQ(M_CDR(expression),Phrase_structure_marker)) {
	  evaluation_sequence_or_structure = copy_for_slot_value(expression);
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  evaluation_sequence_or_structure);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (CONSP(expression) && EQ(M_CDR(expression),Qsequence) || 
	      CONSP(expression) && EQ(M_CDR(expression),Qab_structure)) {
	  evaluation_sequence_or_structure = FIXNUMP(expression) || 
		  expression && SYMBOLP(expression) ? expression : 
		  copy_evaluation_value_1(expression);
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  evaluation_sequence_or_structure);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (truth_value_phrase_p(expression)) {
	  value = truth_value_phrase_value(expression);
	  if (EQ(value,Truth))
	      temp = Evaluation_true_value;
	  else if (EQ(value,Falsity))
	      temp = Evaluation_false_value;
	  else if (FIXNUM_EQ(value,Truth))
	      temp = Evaluation_true_value;
	  else if (FIXNUM_EQ(value,Falsity))
	      temp = Evaluation_false_value;
	  else
	      temp = eval_cons_1(value,Qtruth_value);
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  temp);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (CONSP(expression)) {
	  operator_1 = CAR(expression);
	  if (ATOM(expression) ? expression && SYMBOLP(expression) : 
		  TRUEP(designation_operator_or_giver_of_value_p(CAR(expression))))
	      result = convert_designation_to_stack_node_tree(expression);
	  else if (SYMBOLP(operator_1)) {
	      special_form_converter_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
		      Qstack_special_form_converter);
	      stack_evaluator_descriptions_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
		      Qstack_evaluators);
	      if (special_form_converter_qm) {
		  gensymed_symbol = special_form_converter_qm;
		  gensymed_symbol_1 = expression;
		  result = VALUES_1(inline_funcall_1(gensymed_symbol,
			  gensymed_symbol_1));
	      }
	      else if (stack_evaluator_descriptions_qm) {
		  node = Nil;
		  current_evaluator_number = FIX((SI_Long)0L);
		  first_evaluator = FIRST(stack_evaluator_descriptions_qm);
		  current_evaluator_number = ISVREF(first_evaluator,
			  (SI_Long)9L);
		  if (FIXNUM_GT(current_evaluator_number,
			  Dispatch_instruction_number)) {
		      SVREF(first_evaluator,FIX((SI_Long)9L)) = 
			      Dispatch_instruction_number;
		      temp_1 = 
			      nconc2(copy_list_using_gensym_conses_1(ISVREF(first_evaluator,
			      (SI_Long)4L)),gensym_cons_1(Qinteger,Nil));
		      SVREF(first_evaluator,FIX((SI_Long)4L)) = temp_1;
		      temp_1 = FIXNUM_MINUS(current_evaluator_number,
			      Dispatch_instruction_number);
		      SVREF(first_evaluator,FIX((SI_Long)14L)) = temp_1;
		      Already_mutated_evaluators = 
			      nconc2(gensym_cons_1(operator_1,Nil),
			      Already_mutated_evaluators);
		  }
		  gensymed_symbol = make_stack_node_1_1(operator_1,
			  stack_evaluator_descriptions_qm);
		  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
			  Stack_nodes_to_reclaim);
		  node = gensymed_symbol;
		  temp_1 = make_stack_argument_nodes(operator_1,
			  member_eql(operator_1,
			  Already_mutated_evaluators) ? 
			  nconc2(copy_list_using_gensym_conses_1(CDR(expression)),
			  gensym_cons_1(ISVREF(first_evaluator,
			  (SI_Long)14L),Nil)) : CDR(expression),
			  stack_evaluator_descriptions_qm);
		  SVREF(node,FIX((SI_Long)2L)) = temp_1;
		  result = VALUES_1(node);
	      }
	      else {
		  gensymed_symbol = 
			  make_stack_node_instruction_1_1(Qcall_function,
			  phrase_list_2(Nil,SYMBOLP(operator_1) ? 
			  operator_1 : Nil));
		  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
			  Stack_nodes_to_reclaim);
		  node = gensymed_symbol;
		  argument = Nil;
		  ab_loop_list_ = CDR(expression);
		  arg_nodes = Nil;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
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
		  goto next_loop;
		end_loop:
		  temp = convert_designation_to_stack_node_tree(operator_1);
		  temp_1 = stack_cons_1(temp,arg_nodes);
		  SVREF(node,FIX((SI_Long)2L)) = temp_1;
		  result = VALUES_1(node);
		  goto end_1;
		  result = VALUES_1(Qnil);
		end_1:;
	      }
	  }
	  else if (NUMBERP(operator_1)) {
	      gensymed_symbol = 
		      make_stack_node_instruction_1_1(Qpush_constant,
		      make_evaluation_quantity(operator_1));
	      Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		      Stack_nodes_to_reclaim);
	      result = VALUES_1(gensymed_symbol);
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(operator_1) != (SI_Long)0L 
		  && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(operator_1)) == 
		  (SI_Long)1L) {
	      gensymed_symbol = 
		      make_stack_node_instruction_1_1(Qpush_constant,
		      copy_evaluation_float_from_phrase_float(operator_1));
	      Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		      Stack_nodes_to_reclaim);
	      result = VALUES_1(gensymed_symbol);
	  }
	  else if (INLINE_LONG_VECTOR_P(operator_1) != (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(operator_1)) == (SI_Long)1L) {
	      gensymed_symbol = 
		      make_stack_node_instruction_1_1(Qpush_constant,
		      copy_evaluation_long_from_phrase_long(operator_1));
	      Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		      Stack_nodes_to_reclaim);
	      result = VALUES_1(gensymed_symbol);
	  }
	  else {
	      mal_formed_stack_expression(expression);
	      result = make_dummy_stack_node();
	  }
      }
      else if (FIXNUMP(expression)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  expression);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (text_string_p(expression)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  copy_as_wide_string(expression));
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (STRINGP(expression)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  copy_as_wide_string(expression));
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (FLOATP(expression)) {
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
		  temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(expression);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  new_float);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (INLINE_LONG_P(expression) != (SI_Long)0L) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  make_evaluation_long(expression));
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (EQ(expression,Qdoes_not_exist)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  Nil);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (EQ(expression,Qtrue)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  Evaluation_true_value);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (EQ(expression,Qfalse)) {
	  gensymed_symbol = make_stack_node_instruction_1_1(Qpush_constant,
		  Evaluation_false_value);
	  Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		  Stack_nodes_to_reclaim);
	  result = VALUES_1(gensymed_symbol);
      }
      else if (SYMBOLP(expression))
	  result = convert_designation_to_stack_node_tree(expression);
      else {
	  mal_formed_stack_expression(expression);
	  result = make_dummy_stack_node();
      }
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Compile_reference_to_system_slot, Qcompile_reference_to_system_slot);

static Object Qpush_from_surrounding_local_var;  /* push-from-surrounding-local-var */

static Object Qcopy_into_surrounding_local_var;  /* copy-into-surrounding-local-var */

static Object string_constant_30;  /* "All local names for procedures must be declared at ~
				    *                    the top of the procedure definition.  This ~
				    *                    designation could not be compiled: ~ND."
				    */

static Object string_constant_31;  /* "No local name could be found for \"~ND\"." */

static Object Qevaluate_role_with_no_domain;  /* evaluate-role-with-no-domain */

static Object string_constant_32;  /* "All local names for procedures must be declared at the top of the ~
				    *             procedure definition.  This designation could not be ~
				    *             compiled: ~ND."
				    */

static Object Qgiver_of_value;     /* giver-of-value */

static Object Qevaluate_role;      /* evaluate-role */

static Object string_constant_33;  /* "The reference \"~ND\" cannot be compiled because it references a ~
				    *               system defined attribute, ~a.  You can use \"the text of\" ~
				    *               around references to system defined attributes to get the text ~
				    *               that is visible in attribute tables for that attribute."
				    */

/* CONVERT-DESIGNATION-TO-STACK-NODE-TREE */
Object convert_designation_to_stack_node_tree(designation)
    Object designation;
{
    Object var_spot_or_symbol, gensymed_symbol, role, role_node, role_name;
    Object temp, temp_1, new_designation, stack_list, simple_role;
    Object bound_reference_qm, var_spot, quantifier, domain_list, domain;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object domain_stack_node_arguments;

    x_note_fn_call(206,81);
    if ( !(ATOM(designation) ? designation && SYMBOLP(designation) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(designation))))) 
		{
	mal_formed_stack_designation(designation);
	make_dummy_stack_node();
    }
    if (SYMBOLP(designation)) {
	var_spot_or_symbol = resolve_stack_name_reference(designation);
	if ( !SYMBOLP(var_spot_or_symbol)) {
	    gensymed_symbol = 
		    make_stack_node_instruction_1_1(Qpush_from_surrounding_local_var,
		    var_spot_or_symbol);
	    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		    Stack_nodes_to_reclaim);
	    return VALUES_1(gensymed_symbol);
	}
	else {
	    gensymed_symbol = 
		    make_stack_node_instruction_1_1(Qpush_cached_item,
		    designation);
	    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		    Stack_nodes_to_reclaim);
	    return VALUES_1(gensymed_symbol);
	}
    }
    else if ( !TRUEP(simple_role_p(role_of_designation(designation)))) {
	role = role_of_designation(designation);
	role_node = Nil;
	role_name = get_name_provided_by_role(role);
	temp = CAR(designation);
	temp_1 = simple_role_of_role(role);
	new_designation = stack_cons_1(temp,stack_cons_1(temp_1,
		CDDR(designation)));
	stack_list = 
		stack_cons_1(convert_designation_to_stack_node_tree(new_designation),
		Nil);
	reclaim_stack_cons_1(CDR(new_designation));
	reclaim_stack_cons_1(new_designation);
	if ( !TRUEP(variable_spot_and_description_for_local_name(role_name)))
	    generate_new_variable_spot(2,
		    valid_type_specification_p(type_specification_of_role(role_of_designation(designation))) 
		    ? 
		    type_specification_of_role(role_of_designation(designation)) 
		    : Qitem_or_datum,role_name);
	gensymed_symbol = 
		make_stack_node_instruction_1_1(Qcopy_into_surrounding_local_var,
		variable_spot_and_description_for_local_name(role_name));
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	role_node = gensymed_symbol;
	SVREF(role_node,FIX((SI_Long)2L)) = stack_list;
	return VALUES_1(role_node);
    }
    else if (IFIX(length(designation)) == (SI_Long)2L) {
	role = role_of_designation(designation);
	if ( !TRUEP(simple_role_p(role))) {
	    simple_role = simple_role_of_role(role);
	    compiler_error(2,string_constant_30,designation);
	    record_free_references_of_role(1,simple_role);
	    return make_dummy_stack_node();
	}
	else if (quantifier_requires_previous_reference_p(CAR(designation)) 
		&& SYMBOLP(role)) {
	    bound_reference_qm = assoc_equal(designation,
		    Expression_bound_local_names);
	    if (bound_reference_qm) {
		var_spot = CDR(bound_reference_qm);
		gensymed_symbol = 
			make_stack_node_instruction_1_1(Qpush_from_surrounding_local_var,
			var_spot);
		Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
			Stack_nodes_to_reclaim);
		return VALUES_1(gensymed_symbol);
	    }
	    else {
		compiler_error(2,string_constant_31,designation);
		return make_dummy_stack_node();
	    }
	}
	else {
	    gensymed_symbol = 
		    make_stack_node_instruction_1_1(Qevaluate_role_with_no_domain,
		    role);
	    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		    Stack_nodes_to_reclaim);
	    return VALUES_1(gensymed_symbol);
	}
    }
    else {
	gensymed_symbol = designation;
	quantifier = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol);
	domain_list = CDR(gensymed_symbol);
	if ( !TRUEP(simple_role_p(role))) {
	    compiler_error(2,string_constant_32,designation);
	    role = simple_role_of_role(role);
	}
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
	domain_stack_node_arguments = ab_loopvar_;
	goto end_1;
	domain_stack_node_arguments = Qnil;
      end_1:;
	if (EQ(quantifier,Qgiver_of_value)) {
	    gensymed_symbol = 
		    make_stack_node_instruction_1_1(Qgiver_of_value,role);
	    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		    Stack_nodes_to_reclaim);
	    role_node = gensymed_symbol;
	}
	else {
	    gensymed_symbol = 
		    make_stack_node_instruction_1_1(Qevaluate_role,role);
	    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		    Stack_nodes_to_reclaim);
	    role_node = gensymed_symbol;
	}
	if ( !EQ(quantifier,Qgiver_of_value) &&  
		!TRUEP(Compile_reference_to_system_slot) && SYMBOLP(role) 
		&& IFIX(length(domain_list)) == (SI_Long)1L && 
		unauthorized_system_slot_p(role))
	    compiler_error(3,string_constant_33,designation,role);
	SVREF(role_node,FIX((SI_Long)2L)) = domain_stack_node_arguments;
	return VALUES_1(role_node);
    }
}

/* RESOLVE-STACK-NAME-REFERENCE */
Object resolve_stack_name_reference(possible_local_name)
    Object possible_local_name;
{
    Object bound_var_spot_qm, temp;

    x_note_fn_call(206,82);
    bound_var_spot_qm = assq_function(possible_local_name,
	    Expression_bound_local_names);
    if (bound_var_spot_qm)
	return VALUES_1(CDR(bound_var_spot_qm));
    temp = variable_spot_and_description_for_local_name(possible_local_name);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(possible_local_name);
}

static Object string_constant_34;  /* "The malformed expression ~a (" */

static Object array_constant_4;    /* # */

static Object string_constant_35;  /* " ~a" */

static Object string_constant_36;  /* " . ~a" */

static Object array_constant_5;    /* # */

static Object string_constant_37;  /* "stack node converter" */

static Object string_constant_38;  /* "The malformed expression ~a could not be compiled." */

/* MAL-FORMED-STACK-EXPRESSION */
Object mal_formed_stack_expression(expression)
    Object expression;
{
    Object operator_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object thing, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(206,83);
    if (CONSP(expression)) {
	operator_1 = CAR(expression);
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
		  tformat(2,string_constant_34,operator_1);
		  thing = CDR(expression);
		next_loop:
		  if ( !TRUEP(thing))
		      twrite_beginning_of_wide_string(array_constant_4,
			      FIX((SI_Long)1L));
		  else if (CONSP(thing))
		      tformat(2,string_constant_35,CAR(thing));
		  else
		      tformat(2,string_constant_36,thing);
		  if (ATOM(thing))
		      goto end_loop;
		  thing = CDR(thing);
		  goto next_loop;
		end_loop:;
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)23L));
		  message_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	compiler_bug(2,string_constant_37,message_1);
	return reclaim_text_string(message_1);
    }
    else
	return compiler_bug(3,string_constant_37,string_constant_38,
		expression);
}

static Object string_constant_39;  /* "The malformed designation ~a could not be compiled." */

/* MAL-FORMED-STACK-DESIGNATION */
Object mal_formed_stack_designation(designation)
    Object designation;
{
    x_note_fn_call(206,84);
    return compiler_bug(3,string_constant_37,string_constant_39,designation);
}

static Object Qdummy_instruction;  /* dummy-instruction */

/* MAKE-DUMMY-STACK-NODE */
Object make_dummy_stack_node()
{
    Object gensymed_symbol;

    x_note_fn_call(206,85);
    gensymed_symbol = make_stack_node_instruction_1_1(Qdummy_instruction,Nil);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    return VALUES_1(gensymed_symbol);
}

static Object list_constant_27;    /* # */

/* NARY-OPERATOR-STACK-IMPLEMENTED-AS-BINARY */
Object nary_operator_stack_implemented_as_binary(operator_1)
    Object operator_1;
{
    x_note_fn_call(206,86);
    return VALUES_1( ! !TRUEP(memq_function(operator_1,list_constant_27)) ?
	     T : Nil);
}

/* MAKE-STACK-ARGUMENT-NODES */
Object make_stack_argument_nodes(operator_1,argument_expressions,
	    evaluator_descriptions)
    Object operator_1, argument_expressions, evaluator_descriptions;
{
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(206,87);
    if (nary_operator_stack_implemented_as_binary(operator_1) && 
	    IFIX(length(argument_expressions)) > (SI_Long)2L)
	return make_binary_stack_argument_nodes(operator_1,
		argument_expressions,evaluator_descriptions);
    else {
	argument = Nil;
	ab_loop_list_ = argument_expressions;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		stack_cons_1(convert_expression_to_stack_node_tree(argument),
		Nil);
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
}

/* MAKE-BINARY-STACK-ARGUMENT-NODES */
Object make_binary_stack_argument_nodes(operator_1,argument_list,
	    evaluator_descriptions)
    Object operator_1, argument_list, evaluator_descriptions;
{
    Object arguments_length, temp, temp_1;

    x_note_fn_call(206,88);
    arguments_length = length(argument_list);
    temp = make_stack_node_combining_arguments(operator_1,argument_list,
	    evaluator_descriptions,arguments_length,
	    FIX(IFIX(arguments_length) - (SI_Long)2L));
    temp_1 = last(argument_list,_);
    return stack_list_2(temp,
	    convert_expression_to_stack_node_tree(CAR(temp_1)));
}

/* MAKE-STACK-NODE-COMBINING-ARGUMENTS */
Object make_stack_node_combining_arguments(operator_1,argument_list,
	    evaluator_descriptions,argument_count,combine_index)
    Object operator_1, argument_list, evaluator_descriptions, argument_count;
    Object combine_index;
{
    Object gensymed_symbol, new_node, temp, svref_new_value;

    x_note_fn_call(206,89);
    gensymed_symbol = make_stack_node_1_1(operator_1,evaluator_descriptions);
    Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
	    Stack_nodes_to_reclaim);
    new_node = gensymed_symbol;
    temp = IFIX(combine_index) == (SI_Long)1L ? 
	    convert_expression_to_stack_node_tree(FIRST(argument_list)) : 
	    make_stack_node_combining_arguments(operator_1,argument_list,
	    evaluator_descriptions,argument_count,FIXNUM_SUB1(combine_index));
    svref_new_value = stack_list_2(temp,
	    convert_expression_to_stack_node_tree(nth(combine_index,
	    argument_list)));
    SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
    return VALUES_1(new_node);
}

/* MOST-GENERAL-ARGUMENT-TYPE-LIST */
Object most_general_argument_type_list(stack_node)
    Object stack_node;
{
    Object most_general, required_type, unknown_allowed_qm, no_item_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, evaluator_descriptions;
    Object argument_list_length, description, ab_loop_list_, argument_types;
    Object type, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(206,90);
    most_general = Nil;
    required_type = ISVREF(stack_node,(SI_Long)5L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    evaluator_descriptions = ISVREF(stack_node,(SI_Long)3L);
    argument_list_length = length(ISVREF(stack_node,(SI_Long)2L));
    description = Nil;
    ab_loop_list_ = evaluator_descriptions;
    argument_types = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    argument_types = ISVREF(description,(SI_Long)4L);
    if (FIXNUM_EQ(length(argument_types),argument_list_length)) {
	if ( !TRUEP(most_general) || 
		more_general_argument_list_description_p(argument_types,
		most_general))
	    most_general = argument_types;
    }
    goto next_loop;
  end_loop:;
    if (no_item_allowed_qm || unknown_allowed_qm || 
	    no_item_implies_unknown_allowed_qm) {
	type = Nil;
	ab_loop_list_ = most_general;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(type,
		unknown_allowed_qm),no_item_allowed_qm),
		no_item_implies_unknown_allowed_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(most_general);
}

/* MORE-GENERAL-ARGUMENT-LIST-DESCRIPTION-P */
Object more_general_argument_list_description_p(superior_arg_list,
	    inferior_arg_list)
    Object superior_arg_list, inferior_arg_list;
{
    Object superior_arg_type, ab_loop_list_, inferior_arg_type;
    Object ab_loop_list__1;

    x_note_fn_call(206,91);
    if (FIXNUM_EQ(length(superior_arg_list),length(inferior_arg_list))) {
	superior_arg_type = Nil;
	ab_loop_list_ = superior_arg_list;
	inferior_arg_type = Nil;
	ab_loop_list__1 = inferior_arg_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior_arg_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	inferior_arg_type = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(type_specification_subtype_p(inferior_arg_type,
		superior_arg_type)))
	    return VALUES_1(Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_40;  /* "preferred evaluation chooser" */

static Object string_constant_41;  /* "No evaluator was choosen for ~a." */

/* CHOOSE-PREFERRED-STACK-EVALUATOR */
Object choose_preferred_stack_evaluator(stack_node)
    Object stack_node;
{
    Object operation, required_type, evaluator_descriptions;
    Object unknown_allowed_qm, no_item_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, known_required_type;
    Object argument_nodes, argument_count, preferred_evaluator_qm, description;
    Object ab_loop_list_, argument_types, arg_float_type, node, ab_loop_it_;
    Object evaluator_arguments, arg_type, ab_loop_list__1;
    Object float_contagion_evaluator_qm, integer_contagion_evaluator_qm;
    Object arg_integer_type, long_contagion_evaluator_qm, arg_long_type;
    Object arg_node_cons, temp_1, unknown_arguments_qm, node_cons, node_type;
    Object evaluator_argument_type;
    char temp;

    x_note_fn_call(206,92);
    operation = ISVREF(stack_node,(SI_Long)1L);
    required_type = ISVREF(stack_node,(SI_Long)5L);
    evaluator_descriptions = ISVREF(stack_node,(SI_Long)3L);
    unknown_allowed_qm = type_specification_subtype_p(list_constant_6,
	    required_type);
    no_item_allowed_qm = type_specification_subtype_p(list_constant_10,
	    required_type);
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_14,required_type);
    known_required_type = primary_type_of_type_specification(required_type);
    argument_nodes = ISVREF(stack_node,(SI_Long)2L);
    argument_count = length(argument_nodes);
    preferred_evaluator_qm = Nil;
    description = Nil;
    ab_loop_list_ = evaluator_descriptions;
    argument_types = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    argument_types = ISVREF(description,(SI_Long)4L);
    if (FIXNUM_EQ(length(argument_types),argument_count) && 
	    stack_evaluator_nodes_produce_types_p(argument_nodes,
	    argument_types,unknown_allowed_qm,no_item_allowed_qm,
	    no_item_implies_unknown_allowed_qm) && ( 
	    !TRUEP(preferred_evaluator_qm) || FIXNUM_LE(ISVREF(description,
	    (SI_Long)2L),ISVREF(preferred_evaluator_qm,(SI_Long)2L))))
	preferred_evaluator_qm = description;
    goto next_loop;
  end_loop:;
    arg_float_type = float_contagion_stack_operator_p(operation) ? 
	    maybe_add_no_item(maybe_add_unknown(Qfloat,unknown_allowed_qm),
	    no_item_allowed_qm) : Nil;
    if (arg_float_type) {
	temp = TRUEP(type_specification_subtype_p(known_required_type,Qfloat));
	if (temp);
	else {
	    node = Nil;
	    ab_loop_list_ = argument_nodes;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    node = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_subtype_p(ISVREF(node,
		    (SI_Long)6L),arg_float_type);
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	description = Nil;
	ab_loop_list_ = evaluator_descriptions;
	evaluator_arguments = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	evaluator_arguments = ISVREF(description,(SI_Long)4L);
	if (FIXNUM_EQ(length(evaluator_arguments),argument_count)) {
	    arg_type = Nil;
	    ab_loop_list__1 = evaluator_arguments;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    arg_type = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(type_specification_subtype_p(arg_type,Qfloat))) {
		temp = TRUEP(Nil);
		goto end_2;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = TRUEP(T);
	    goto end_2;
	    temp = TRUEP(Qnil);
	  end_2:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    float_contagion_evaluator_qm = description;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	float_contagion_evaluator_qm = Qnil;
      end_3:;
    }
    else
	float_contagion_evaluator_qm = Nil;
    if (float_contagion_stack_operator_p(operation) && 
	    type_specification_subtype_p(known_required_type,Qinteger)) {
	description = Nil;
	ab_loop_list_ = evaluator_descriptions;
	evaluator_arguments = Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	evaluator_arguments = ISVREF(description,(SI_Long)4L);
	if (FIXNUM_EQ(length(evaluator_arguments),argument_count)) {
	    arg_type = Nil;
	    ab_loop_list__1 = evaluator_arguments;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    arg_type = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(type_specification_subtype_p(arg_type,Qinteger))) {
		temp = TRUEP(Nil);
		goto end_4;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    temp = TRUEP(T);
	    goto end_4;
	    temp = TRUEP(Qnil);
	  end_4:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    integer_contagion_evaluator_qm = description;
	    goto end_5;
	}
	goto next_loop_4;
      end_loop_4:
	integer_contagion_evaluator_qm = Qnil;
      end_5:;
    }
    else
	integer_contagion_evaluator_qm = Nil;
    arg_integer_type = integer_contagion_evaluator_qm ? 
	    maybe_add_no_item(maybe_add_unknown(Qinteger,
	    unknown_allowed_qm),no_item_allowed_qm) : Qnil;
    if (float_contagion_stack_operator_p(operation) && 
	    type_specification_subtype_p(known_required_type,Qlong)) {
	description = Nil;
	ab_loop_list_ = evaluator_descriptions;
	evaluator_arguments = Nil;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	evaluator_arguments = ISVREF(description,(SI_Long)4L);
	if (FIXNUM_EQ(length(evaluator_arguments),argument_count)) {
	    arg_type = Nil;
	    ab_loop_list__1 = evaluator_arguments;
	  next_loop_7:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_7;
	    arg_type = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(type_specification_subtype_p(arg_type,Qlong))) {
		temp = TRUEP(Nil);
		goto end_6;
	    }
	    goto next_loop_7;
	  end_loop_7:
	    temp = TRUEP(T);
	    goto end_6;
	    temp = TRUEP(Qnil);
	  end_6:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    long_contagion_evaluator_qm = description;
	    goto end_7;
	}
	goto next_loop_6;
      end_loop_6:
	long_contagion_evaluator_qm = Qnil;
      end_7:;
    }
    else
	long_contagion_evaluator_qm = Nil;
    arg_long_type = long_contagion_evaluator_qm ? 
	    maybe_add_no_item(maybe_add_unknown(Qlong,unknown_allowed_qm),
	    no_item_allowed_qm) : Qnil;
    if (long_contagion_evaluator_qm && ( !TRUEP(preferred_evaluator_qm) || 
	    FIXNUM_LT(ISVREF(long_contagion_evaluator_qm,(SI_Long)2L),
	    ISVREF(preferred_evaluator_qm,(SI_Long)2L)))) {
	arg_node_cons = argument_nodes;
      next_loop_8:
	if ( !TRUEP(arg_node_cons))
	    goto end_loop_8;
	temp_1 = choose_stack_node_instructions_and_types(2,
		CAR(arg_node_cons),arg_long_type);
	M_CAR(arg_node_cons) = temp_1;
	arg_node_cons = M_CDR(arg_node_cons);
	goto next_loop_8;
      end_loop_8:;
	preferred_evaluator_qm = long_contagion_evaluator_qm;
    }
    if (integer_contagion_evaluator_qm && ( !TRUEP(preferred_evaluator_qm) 
	    || FIXNUM_LT(ISVREF(integer_contagion_evaluator_qm,
	    (SI_Long)2L),ISVREF(preferred_evaluator_qm,(SI_Long)2L)))) {
	arg_node_cons = argument_nodes;
      next_loop_9:
	if ( !TRUEP(arg_node_cons))
	    goto end_loop_9;
	temp_1 = choose_stack_node_instructions_and_types(2,
		CAR(arg_node_cons),arg_integer_type);
	M_CAR(arg_node_cons) = temp_1;
	arg_node_cons = M_CDR(arg_node_cons);
	goto next_loop_9;
      end_loop_9:;
	preferred_evaluator_qm = integer_contagion_evaluator_qm;
    }
    if (float_contagion_evaluator_qm && ( !TRUEP(preferred_evaluator_qm) 
	    || FIXNUM_LT(ISVREF(float_contagion_evaluator_qm,(SI_Long)2L),
	    ISVREF(preferred_evaluator_qm,(SI_Long)2L)))) {
	arg_node_cons = argument_nodes;
      next_loop_10:
	if ( !TRUEP(arg_node_cons))
	    goto end_loop_10;
	temp_1 = choose_stack_node_instructions_and_types(2,
		CAR(arg_node_cons),arg_float_type);
	M_CAR(arg_node_cons) = temp_1;
	arg_node_cons = M_CDR(arg_node_cons);
	goto next_loop_10;
      end_loop_10:;
	preferred_evaluator_qm = float_contagion_evaluator_qm;
    }
    if (preferred_evaluator_qm) {
	SVREF(stack_node,FIX((SI_Long)4L)) = preferred_evaluator_qm;
	unknown_arguments_qm = Nil;
	node_cons = argument_nodes;
	node = Nil;
	node_type = Nil;
	evaluator_argument_type = Nil;
	ab_loop_list_ = ISVREF(preferred_evaluator_qm,(SI_Long)4L);
      next_loop_11:
	if ( !TRUEP(node_cons))
	    goto end_loop_11;
	node = M_CAR(node_cons);
	node_type = ISVREF(node,(SI_Long)6L);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	evaluator_argument_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (type_specification_subtype_p(list_constant_6,node_type))
	    unknown_arguments_qm = T;
	node_cons = M_CDR(node_cons);
	goto next_loop_11;
      end_loop_11:
	temp_1 = maybe_add_unknown(ISVREF(preferred_evaluator_qm,
		(SI_Long)5L),unknown_arguments_qm);
	SVREF(stack_node,FIX((SI_Long)6L)) = temp_1;
	return VALUES_1(Qnil);
    }
    else
	return compiler_bug(3,string_constant_40,string_constant_41,operation);
}

/* STACK-EVALUATOR-NODES-PRODUCE-TYPES-P */
Object stack_evaluator_nodes_produce_types_p(argument_nodes,argument_types,
	    unknown_allowed_qm,no_item_allowed_qm,
	    no_item_implies_unknown_allowed_qm)
    Object argument_nodes, argument_types, unknown_allowed_qm;
    Object no_item_allowed_qm, no_item_implies_unknown_allowed_qm;
{
    Object arg_type, ab_loop_list_, arg_node, ab_loop_list__1, node_type;

    x_note_fn_call(206,93);
    arg_type = Nil;
    ab_loop_list_ = argument_types;
    arg_node = Nil;
    ab_loop_list__1 = argument_nodes;
    node_type = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    arg_node = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    node_type = ISVREF(arg_node,(SI_Long)6L);
    if (unknown_allowed_qm)
	node_type = type_specification_minus_type(node_type,list_constant_6);
    if (no_item_allowed_qm)
	node_type = type_specification_minus_type(node_type,list_constant_10);
    if (no_item_implies_unknown_allowed_qm)
	node_type = type_specification_minus_type(node_type,list_constant_14);
    if ( !TRUEP(node_type_produces_argument_type_p(node_type,arg_type)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* NODE-TYPE-PRODUCES-ARGUMENT-TYPE-P */
Object node_type_produces_argument_type_p(node_type,argument_type)
    Object node_type, argument_type;
{
    Object temp;

    x_note_fn_call(206,94);
    temp = type_specification_subtype_p(node_type,argument_type);
    if (temp)
	return VALUES_1(temp);
    else if (type_specification_subtype_p(argument_type,list_constant_8))
	return type_specifications_could_intersect_p(node_type,argument_type);
    else
	return VALUES_1(Nil);
}

static Object Qpreferred_instruction_chooser;  /* preferred-instruction-chooser */

static Object string_constant_42;  /* "preferred evaluator instruction chooser" */

static Object string_constant_43;  /* "The stack node instruction ~a had no preferred instruction ~
				    *               chooser."
				    */

/* CHOOSE-PREFERRED-STACK-INSTRUCTION */
Object choose_preferred_stack_instruction(stack_node_instruction)
    Object stack_node_instruction;
{
    Object operation, chooser_function, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(206,95);
    operation = ISVREF(stack_node_instruction,(SI_Long)1L);
    chooser_function = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(operation),
	    Qpreferred_instruction_chooser);
    if (chooser_function) {
	gensymed_symbol = chooser_function;
	gensymed_symbol_1 = stack_node_instruction;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else {
	compiler_bug(3,string_constant_42,string_constant_43,operation);
	SVREF(stack_node_instruction,FIX((SI_Long)6L)) = Nil;
    }
    return VALUES_1(Nil);
}

static Object string_constant_44;  /* "instruction and type chooser" */

static Object string_constant_45;  /* "No value type chosen for operation ~a." */

/* CHOOSE-STACK-NODE-INSTRUCTIONS-AND-TYPES */
Object choose_stack_node_instructions_and_types varargs_1(int, n)
{
    Object node_tree, required_type;
    Object called_from_ensure_type_qm, free_reference_type_qm, node;
    Object ab_loop_list_, sub_node_cons, sub_type_cons_qm, sub_type;
    Object ab_loop_iter_flag_, temp_1, car_new_value;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(206,96);
    INIT_ARGS_nonrelocating();
    node_tree = REQUIRED_ARG_nonrelocating();
    required_type = REQUIRED_ARG_nonrelocating();
    called_from_ensure_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    free_reference_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    SVREF(node_tree,FIX((SI_Long)5L)) = required_type;
    SVREF(node_tree,FIX((SI_Long)11L)) = free_reference_type_qm;
    if (SIMPLE_VECTOR_P(node_tree) && EQ(ISVREF(node_tree,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct))
	choose_preferred_stack_instruction(node_tree);
    else {
	node = Nil;
	ab_loop_list_ = ISVREF(node_tree,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ISVREF(node,(SI_Long)6L))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp) {
	    sub_node_cons = ISVREF(node_tree,(SI_Long)2L);
	    sub_type_cons_qm = most_general_argument_type_list(node_tree);
	    sub_type = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(sub_node_cons))
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_))
		sub_type_cons_qm = CDR(sub_type_cons_qm);
	    temp_1 = CAR(sub_type_cons_qm);
	    if (temp_1);
	    else
		temp_1 = list_constant_5;
	    sub_type = temp_1;
	    car_new_value = choose_stack_node_instructions_and_types(2,
		    CAR(sub_node_cons),sub_type);
	    M_CAR(sub_node_cons) = car_new_value;
	    ab_loop_iter_flag_ = Nil;
	    sub_node_cons = M_CDR(sub_node_cons);
	    goto next_loop_1;
	  end_loop_1:;
	}
	choose_preferred_stack_evaluator(node_tree);
    }
    if ( !TRUEP(ISVREF(node_tree,(SI_Long)6L))) {
	compiler_bug(3,string_constant_44,string_constant_45,
		ISVREF(node_tree,(SI_Long)1L));
	SVREF(node_tree,FIX((SI_Long)6L)) = Qitem_or_datum;
    }
    if ( !TRUEP(called_from_ensure_type_qm) && ( 
	    !TRUEP(type_specification_subtype_p(ISVREF(node_tree,
	    (SI_Long)6L),required_type)) || 
	    type_specification_subtype_p(list_constant_14,required_type) 
	    && type_specification_subtype_p(list_constant_10,
	    ISVREF(node_tree,(SI_Long)6L))))
	node_tree = add_ensure_type_stack_node_instruction(node_tree,
		required_type);
    return VALUES_1(node_tree);
}

static Object Qcoerce_to_datum;    /* coerce-to-datum */

/* ADD-ENSURE-TYPE-STACK-NODE-INSTRUCTION */
Object add_ensure_type_stack_node_instruction(stack_node,required_type)
    Object stack_node, required_type;
{
    Object coerce_to_datum_added_qm, gensymed_symbol, new_node;
    Object svref_new_value;

    x_note_fn_call(206,97);
    coerce_to_datum_added_qm = Nil;
    if (type_specification_subtype_p(list_constant_14,required_type) && 
	    type_specification_subtype_p(list_constant_10,
	    ISVREF(stack_node,(SI_Long)6L))) {
	gensymed_symbol = 
		make_stack_node_instruction_1_1(Qcoerce_no_item_to_unknown,
		Nil);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	new_node = gensymed_symbol;
	svref_new_value = stack_cons_1(stack_node,Nil);
	SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
	stack_node = choose_stack_node_instructions_and_types(4,new_node,
		required_type,T,ISVREF(stack_node,(SI_Long)11L));
    }
    if (type_specification_subtype_p(type_specification_minus_type(type_specification_minus_type(required_type,
	    list_constant_10),list_constant_14),list_constant) && 
	    type_specifications_could_intersect_p(list_constant_8,
	    ISVREF(stack_node,(SI_Long)6L))) {
	gensymed_symbol = make_stack_node_instruction_1_1(Qcoerce_to_datum,
		Nil);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	new_node = gensymed_symbol;
	coerce_to_datum_added_qm = T;
	svref_new_value = stack_cons_1(stack_node,Nil);
	SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
	stack_node = choose_stack_node_instructions_and_types(4,new_node,
		required_type,T,ISVREF(stack_node,(SI_Long)11L));
    }
    if (coerce_to_datum_added_qm ||  
	    !(type_specification_subtype_p(ISVREF(stack_node,(SI_Long)6L),
	    required_type) || SIMPLE_VECTOR_P(stack_node) && 
	    EQ(ISVREF(stack_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct) 
	    && EQ(ISVREF(stack_node,(SI_Long)1L),Qensure_type))) {
	gensymed_symbol = make_stack_node_instruction_1_1(Qensure_type,Nil);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	new_node = gensymed_symbol;
	svref_new_value = stack_cons_1(stack_node,Nil);
	SVREF(new_node,FIX((SI_Long)2L)) = svref_new_value;
	stack_node = choose_stack_node_instructions_and_types(4,new_node,
		required_type,T,ISVREF(stack_node,(SI_Long)11L));
    }
    return VALUES_1(stack_node);
}

static Object string_constant_46;  /* "An argument to ~a, which is required to be of type ~NT, was of ~
				    *                type ~NT."
				    */

static Object string_constant_47;  /* "The operation ~a is required to produce a value of type ~NT, ~
				    *                but instead produces values of type ~NT."
				    */

static Object Qexpiration_source_operator_p;  /* expiration-source-operator-p */

static Object Qsource;             /* source */

static Object Qtrivial_tree;       /* trivial-tree */

static Object Qsingle_source_tree;  /* single-source-tree */

static Object Qsource_tree;        /* source-tree */

static Object Qexpiration_special_form_operator_p;  /* expiration-special-form-operator-p */

static Object Qspecial_tree;       /* special-tree */

static Object Qminimizing;         /* minimizing */

static Object Qnormal_tree;        /* normal-tree */

/* ENSURE-ARGUMENT-TYPES-SATISFY-OPERATORS */
Object ensure_argument_types_satisfy_operators(parent_node_qm,stack_node)
    Object parent_node_qm, stack_node;
{
    Object argument_node, ab_loop_list_, required_type, return_type, operation;
    Object returns_unknown_qm, temp, arg;
    char temp_1;

    x_note_fn_call(206,98);
    argument_node = Nil;
    ab_loop_list_ = ISVREF(stack_node,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ensure_argument_types_satisfy_operators(stack_node,argument_node);
    goto next_loop;
  end_loop:;
    required_type = ISVREF(stack_node,(SI_Long)5L);
    return_type = ISVREF(stack_node,(SI_Long)6L);
    operation = ISVREF(stack_node,(SI_Long)1L);
    returns_unknown_qm = type_specification_subtype_p(list_constant_6,
	    return_type);
    if ( !TRUEP(type_specification_subtype_p(return_type,required_type))) {
	if (EQ(ISVREF(stack_node,(SI_Long)1L),Qensure_type)) {
	    temp = type_specifications_could_intersect_p(return_type,
		    required_type);
	    if (temp);
	    else
		temp = 
			datum_type_specifications_could_be_coerced_p(return_type,
			required_type);
	}
	else if (EQ(ISVREF(stack_node,(SI_Long)1L),Qcoerce_to_datum)) {
	    temp = type_specifications_could_intersect_p(return_type,
		    required_type);
	    if (temp);
	    else
		temp = type_specifications_could_be_coerced_p(return_type,
			required_type);
	    if (temp);
	    else
		temp = parent_node_qm ? (EQ(ISVREF(parent_node_qm,
			(SI_Long)1L),Qensure_type) ? T : Nil) : Qnil;
	}
	else if (EQ(ISVREF(stack_node,(SI_Long)1L),Qcoerce_no_item_to_unknown))
	    temp = T;
	else if (parent_node_qm) {
	    temp = EQ(ISVREF(parent_node_qm,(SI_Long)1L),Qensure_type) ? T 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(parent_node_qm,(SI_Long)1L),
			Qcoerce_to_datum) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(parent_node_qm,(SI_Long)1L),
			Qcoerce_no_item_to_unknown) ? T : Nil;
	}
	else
	    temp = Nil;
	if ( !TRUEP(temp)) {
	    if (parent_node_qm)
		compiler_error(4,string_constant_46,ISVREF(parent_node_qm,
			(SI_Long)1L),required_type,return_type);
	    else
		compiler_error(4,string_constant_47,ISVREF(stack_node,
			(SI_Long)1L),required_type,return_type);
	}
    }
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(operation),
	    Qexpiration_source_operator_p)) {
	SVREF(stack_node,FIX((SI_Long)7L)) = Qsource;
	if ( !TRUEP(returns_unknown_qm))
	    return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
		    Qtrivial_tree);
	else {
	    arg = Nil;
	    ab_loop_list_ = ISVREF(stack_node,(SI_Long)2L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    arg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !EQ(ISVREF(arg,(SI_Long)8L),Qtrivial_tree)) {
		temp_1 = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(T);
	    goto end_1;
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    if (temp_1)
		return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
			Qsingle_source_tree);
	    else
		return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
			Qsource_tree);
	}
    }
    else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(operation),
	    Qexpiration_special_form_operator_p)) {
	SVREF(stack_node,FIX((SI_Long)7L)) = Qspecial;
	if (returns_unknown_qm)
	    return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
		    Qspecial_tree);
	else
	    return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
		    Qtrivial_tree);
    }
    else {
	SVREF(stack_node,FIX((SI_Long)7L)) = Qminimizing;
	if (returns_unknown_qm)
	    return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = Qnormal_tree);
	else
	    return VALUES_1(SVREF(stack_node,FIX((SI_Long)8L)) = 
		    Qtrivial_tree);
    }
}

/* TYPE-SPECIFICATIONS-COULD-BE-COERCED-P */
Object type_specifications_could_be_coerced_p(value_type,required_type)
    Object value_type, required_type;
{
    Object held_type_qm, temp;

    x_note_fn_call(206,99);
    if (type_specification_subtype_p(required_type,Qdatum)) {
	if (type_specifications_could_intersect_p(value_type,
		    list_constant_24)) {
	    held_type_qm = type_specification_held_in_type(value_type);
	    temp =  !TRUEP(held_type_qm) ? T : Nil;
	    if (temp);
	    else
		temp = type_specifications_could_intersect_p(held_type_qm,
			required_type);
	    if (temp)
		return VALUES_1(temp);
	    else
		return datum_type_specifications_could_be_coerced_p(held_type_qm,
			required_type);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (type_specification_subtype_p(required_type,list_constant)) {
	if (type_specifications_could_intersect_p(value_type,
		    list_constant_23)) {
	    held_type_qm = type_specification_held_in_type(value_type);
	    temp =  !TRUEP(held_type_qm) ? T : Nil;
	    if (temp);
	    else
		temp = type_specifications_could_intersect_p(held_type_qm,
			required_type);
	    if (temp)
		return VALUES_1(temp);
	    else
		return datum_type_specifications_could_be_coerced_p(held_type_qm,
			required_type);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

/* DATUM-TYPE-SPECIFICATIONS-COULD-BE-COERCED-P */
Object datum_type_specifications_could_be_coerced_p(datum_value_type,
	    datum_required_type)
    Object datum_value_type, datum_required_type;
{
    Object temp;

    x_note_fn_call(206,100);
    if (type_specification_subtype_p(datum_required_type,list_constant_28) 
	    && type_specification_subtype_p(datum_value_type,
		list_constant_29)) {
	temp =  !TRUEP(type_specification_subtype_p(list_constant_6,
		datum_value_type)) ? T : Nil;
	if (temp);
	else
	    temp = type_specification_subtype_p(list_constant_6,
		    datum_required_type);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object list_constant_30;    /* # */

static Object string_constant_48;  /* "The value of an expression could possibly be unknown.  This expression ~
				    *        must be executed within a COLLECT DATA or WAIT UNTIL statement."
				    */

static Object Qexecute_normal_form_tree;  /* execute-normal-form-tree */

static Object string_constant_49;  /* "unknown value stack node tree rewrite" */

static Object string_constant_50;  /* "Unknown tree type ~a." */

/* REWRITE-STACK-NODE-TREES-FOR-UNKNOWN */
Object rewrite_stack_node_trees_for_unknown(stack_node)
    Object stack_node;
{
    Object temp, argument_node_cons, temp_1, reverse_var_spot_list;
    Object gensymed_symbol, new_node, var_spot_to_tree_alist, alist_cons;
    Object ab_loop_list_, expiration_node, expiration_nodes, ab_loopvar_;
    Object ab_loopvar__1;

    x_note_fn_call(206,101);
    if (type_specification_subtype_p(list_constant_6,ISVREF(stack_node,
	    (SI_Long)6L)) && 
	    type_specification_not_subtype_p(list_constant_6,
	    ISVREF(stack_node,(SI_Long)5L)) &&  
	    !TRUEP(memq_function(ISVREF(stack_node,(SI_Long)1L),
	    list_constant_30)))
	compiler_error(1,string_constant_48);
    temp = ISVREF(stack_node,(SI_Long)8L);
    if (EQ(temp,Qspecial_tree) || EQ(temp,Qsingle_source_tree) || EQ(temp,
	    Qtrivial_tree)) {
	argument_node_cons = ISVREF(stack_node,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(argument_node_cons))
	    goto end_loop;
	temp_1 = rewrite_stack_node_trees_for_unknown(CAR(argument_node_cons));
	M_CAR(argument_node_cons) = temp_1;
	argument_node_cons = M_CDR(argument_node_cons);
	goto next_loop;
      end_loop:;
	return VALUES_1(stack_node);
    }
    else if (EQ(temp,Qnormal_tree) || EQ(temp,Qsource_tree)) {
	reverse_var_spot_list = Nil;
	gensymed_symbol = 
		make_stack_node_instruction_1_1(Qexecute_normal_form_tree,Nil);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	new_node = gensymed_symbol;
	var_spot_to_tree_alist = 
		collect_special_and_source_subtree_alist(ISVREF(stack_node,
		(SI_Long)2L),T);
	alist_cons = Nil;
	ab_loop_list_ = var_spot_to_tree_alist;
	expiration_node = Nil;
	expiration_nodes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	alist_cons = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	expiration_node = CDR(alist_cons);
	M_CDR(alist_cons) = reverse_var_spot_list;
	reverse_var_spot_list = alist_cons;
	expiration_node = 
		rewrite_stack_node_trees_for_unknown(expiration_node);
	ab_loopvar__1 = stack_cons_1(expiration_node,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    expiration_nodes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ISVREF(stack_node,(SI_Long)5L);
	SVREF(new_node,FIX((SI_Long)5L)) = temp_1;
	temp_1 = ISVREF(stack_node,(SI_Long)6L);
	SVREF(new_node,FIX((SI_Long)6L)) = temp_1;
	SVREF(new_node,FIX((SI_Long)12L)) = reverse_var_spot_list;
	temp_1 = stack_cons_1(stack_node,expiration_nodes);
	SVREF(new_node,FIX((SI_Long)2L)) = temp_1;
	return VALUES_1(new_node);
	return VALUES_1(Qnil);
    }
    else {
	compiler_bug(3,string_constant_49,string_constant_50,
		ISVREF(stack_node,(SI_Long)8L));
	return VALUES_1(stack_node);
    }
}

static Object Qno_op;              /* no-op */

static Object string_constant_51;  /* "unknown subtree search" */

/* COLLECT-SPECIAL-AND-SOURCE-SUBTREE-ALIST */
Object collect_special_and_source_subtree_alist(argument_nodes,
	    optimize_push_qm)
    Object argument_nodes, optimize_push_qm;
{
    Object alist_so_far, argument_node_cons, argument_node, tree_type, temp;
    Object arg_value_type, new_var_type_qm, new_var_spot_qm, gensymed_symbol;
    Object new_node, svref_new_value;

    x_note_fn_call(206,102);
    alist_so_far = Nil;
    argument_node_cons = argument_nodes;
    argument_node = Nil;
    tree_type = Nil;
  next_loop:
    if ( !TRUEP(argument_node_cons))
	goto end_loop;
    argument_node = CAR(argument_node_cons);
    tree_type = ISVREF(argument_node,(SI_Long)8L);
    if (EQ(tree_type,Qnormal_tree)) {
	temp = alist_so_far;
	alist_so_far = nconc2(temp,
		collect_special_and_source_subtree_alist(ISVREF(argument_node,
		(SI_Long)2L),optimize_push_qm));
	optimize_push_qm = Nil;
    }
    else if (EQ(tree_type,Qtrivial_tree))
	optimize_push_qm = Nil;
    else if (EQ(tree_type,Qspecial_tree) || EQ(tree_type,Qsource_tree) || 
	    EQ(tree_type,Qsingle_source_tree)) {
	arg_value_type = ISVREF(argument_node,(SI_Long)6L);
	new_var_type_qm = union_type_specification_p(arg_value_type) && 
		type_specification_subtype_p(list_constant_6,
		arg_value_type) ? 
		type_specification_union_minus_type(arg_value_type,
		list_constant_6) : Qnil;
	new_var_spot_qm =  !TRUEP(optimize_push_qm) ? (new_var_type_qm && 
		type_specification_subtype_p(new_var_type_qm,Qdatum) ? 
		generate_new_stack_frame_var_spot(new_var_type_qm) : 
		generate_new_stack_frame_var_spot(Qitem_or_datum)) : Nil;
	gensymed_symbol = make_stack_node_instruction_1_1(new_var_spot_qm ?
		 Qpush_from_surrounding_local_var : Qno_op,new_var_spot_qm);
	Stack_nodes_to_reclaim = stack_cons_1(gensymed_symbol,
		Stack_nodes_to_reclaim);
	new_node = gensymed_symbol;
	svref_new_value = ISVREF(argument_node,(SI_Long)5L);
	SVREF(new_node,FIX((SI_Long)5L)) = svref_new_value;
	svref_new_value = ISVREF(argument_node,(SI_Long)6L);
	SVREF(new_node,FIX((SI_Long)6L)) = svref_new_value;
	M_CAR(argument_node_cons) = new_node;
	alist_so_far = nconc2(alist_so_far,
		phrase_cons(phrase_cons(new_var_spot_qm,argument_node),Nil));
    }
    else {
	optimize_push_qm = Nil;
	compiler_bug(3,string_constant_51,string_constant_50,tree_type);
    }
    argument_node_cons = M_CDR(argument_node_cons);
    goto next_loop;
  end_loop:;
    return VALUES_1(alist_so_far);
}

void stack_comp_INIT()
{
    Object dummy_instruction_i_chooser_1, no_op_i_chooser_1;
    Object push_constant_i_chooser_1, name_reference_i_chooser_1;
    Object push_cached_item_i_chooser_1;
    Object evaluate_role_with_no_domain_i_chooser_1, gensymed_symbol;
    Object named_by_symbol_dispatch_predicate_1;
    Object name_of_item_dispatch_predicate_1;
    Object related_to_item_dispatch_predicate_1;
    Object nth_element_of_integer_array_dispatch_predicate_1;
    Object nth_element_of_float_array_dispatch_predicate_1;
    Object nth_element_of_value_array_dispatch_predicate_1;
    Object evaluate_role_i_chooser_1, giver_of_value_i_chooser_1;
    Object push_from_surrounding_local_var_i_chooser_1;
    Object copy_into_surrounding_local_var_i_chooser_1;
    Object move_from_surrounding_local_var_i_chooser_1;
    Object coerce_to_datum_i_chooser_1, coerce_no_item_to_unknown_i_chooser_1;
    Object ensure_type_i_chooser_1, execute_normal_form_tree_i_chooser_1;
    Object call_procedure_i_chooser_1, call_function_i_chooser_1;
    Object dummy_instruction_i_emit_1, no_op_i_emit_1, push_constant_i_emit_1;
    Object push_constant_i_reclaim_1, push_constant_i_copy_1;
    Object name_reference_i_emit_1, push_cached_item_i_emit_1;
    Object push_from_surrounding_local_var_i_emit_1;
    Object copy_into_surrounding_local_var_i_emit_1;
    Object move_from_surrounding_local_var_i_emit_1;
    Object evaluate_role_with_no_domain_i_emit_1, evaluate_role_i_emit_1;
    Object evaluate_role_implicit_scope_i_emit_1, giver_of_value_i_emit_1;
    Object coerce_to_datum_i_emit_1, coerce_no_item_to_unknown_i_emit_1;
    Object ensure_type_i_emit_1, execute_normal_form_tree_i_emit_1;
    Object call_procedure_i_emit_1, call_function_i_emit_1;
    Object Qfirst_that_has_a_current_value, Qvalue_of, Qhas_a_value;
    Object Qfirst_that_has_a_value, AB_package, list_constant_34, Qab_or;
    Object list_constant_35, Qis_of_class, Qindirectly_disconnected_from;
    Object Qindirectly_connected_to, Qdirectly_disconnected_from;
    Object Qgeneric_directly_disconnected_from, Qgeneric_event, Qis_created;
    Object Qloses_its_value, Qis_disabled, Qis_enabled, Qis_deactivated;
    Object Qis_activated, Qis_resized_by_the_user, Qis_moved_by_g2;
    Object Qis_moved_by_the_user, Qis_moved, Qreceives_a_value;
    Object Qcall_procedure, Qevaluate_role_implicit_scope;
    Object Qmove_from_surrounding_local_var;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qstack_node_instruction_extra_info_copier;
    Object Qstack_node_instruction_reclaimer, Qparameter;
    Object Qvariable_or_parameter, list_constant_36, Qplace_reference;
    Object Qvalue_array, Qunique_value_of_role_instruction_name;
    Object Qinteger_array, Qg2_toggle_evaluate_role_inline;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qno_item_implies_unknown, list_constant_33, Qobsolete_datum;
    Object Qaction_cache, list_constant_31, list_constant_32, Qutilities3;
    Object Qconclude_attribute_binding_1, Kfuncall, Qstack_comp;
    Object Qfunction_can_return_unknown, Qno_item, Qunknown_datum;

    x_note_fn_call(206,103);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    QUNKNOWN_ALLOWED = STATIC_SYMBOL("unknown-allowed",AB_package);
    QNO_ITEM_ALLOWED = STATIC_SYMBOL("no-item-allowed",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_6 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant = STATIC_LIST((SI_Long)3L,Qab_or,Qdatum,list_constant_6);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_10 = STATIC_CONS(Qno_item,Qnil);
    list_constant_31 = STATIC_CONS(list_constant_10,Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,Qdatum,
	    list_constant_6,list_constant_31);
    list_constant_2 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_31);
    Qreturn_from_function = STATIC_SYMBOL("RETURN-FROM-FUNCTION",AB_package);
    Qtag_statement = STATIC_SYMBOL("TAG-STATEMENT",AB_package);
    Qfunction_can_return_unknown = 
	    STATIC_SYMBOL("FUNCTION-CAN-RETURN-UNKNOWN",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qfunction_can_return_unknown);
    Qsignal_error = STATIC_SYMBOL("SIGNAL-ERROR",AB_package);
    string_constant = 
	    STATIC_STRING("This function can only be called in contexts where unknown is allowed.");
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_1 = 
	    STATIC_STRING("~a is also the name of a system-defined function.  The system ~\n             function will be used if ~a is called.");
    QRECACHE_NEEDED = STATIC_SYMBOL("recache-needed",AB_package);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qassign_local_var = STATIC_SYMBOL("ASSIGN-LOCAL-VAR",AB_package);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_31);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qexecute_simulation_formula = 
	    STATIC_SYMBOL("EXECUTE-SIMULATION-FORMULA",AB_package);
    Qcomplete_simulation_variable_evaluation = 
	    STATIC_SYMBOL("COMPLETE-SIMULATION-VARIABLE-EVALUATION",
	    AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qconclude_parent_attribute_bindings = 
	    STATIC_SYMBOL("CONCLUDE-PARENT-ATTRIBUTE-BINDINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconclude_parent_attribute_bindings,
	    Conclude_parent_attribute_bindings);
    Qstack_comp = STATIC_SYMBOL("STACK-COMP",AB_package);
    record_system_variable(Qconclude_parent_attribute_bindings,Qstack_comp,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qlocal_name_to_cached_designation_alist = 
	    STATIC_SYMBOL("LOCAL-NAME-TO-CACHED-DESIGNATION-ALIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_name_to_cached_designation_alist,
	    Local_name_to_cached_designation_alist);
    record_system_variable(Qlocal_name_to_cached_designation_alist,
	    Qstack_comp,Nil,Qnil,Qnil,Qnil,Qnil);
    Qrule_certainty_var = STATIC_SYMBOL("RULE-CERTAINTY-VAR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrule_certainty_var,Rule_certainty_var);
    record_system_variable(Qrule_certainty_var,Qstack_comp,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qrule_expiration_var = STATIC_SYMBOL("RULE-EXPIRATION-VAR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrule_expiration_var,Rule_expiration_var);
    record_system_variable(Qrule_expiration_var,Qstack_comp,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qconclude_attribute_binding_symbol_supply = 
	    STATIC_SYMBOL("CONCLUDE-ATTRIBUTE-BINDING-SYMBOL-SUPPLY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconclude_attribute_binding_symbol_supply,
	    Conclude_attribute_binding_symbol_supply);
    Qutilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qconclude_attribute_binding_1 = 
	    STATIC_SYMBOL("CONCLUDE-ATTRIBUTE-BINDING-1",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)3L,Kfuncall,Qlist,
	    Qconclude_attribute_binding_1);
    record_system_variable(Qconclude_attribute_binding_symbol_supply,
	    Qutilities3,list_constant_32,Qnil,Qt,Qnil,Qnil);
    Qconclude_attribute_binding_symbol_counter = 
	    STATIC_SYMBOL("CONCLUDE-ATTRIBUTE-BINDING-SYMBOL-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconclude_attribute_binding_symbol_counter,
	    Conclude_attribute_binding_symbol_counter);
    string_constant_2 = STATIC_STRING("CONCLUDE-ATTRIBUTE-BINDING");
    Qallocate_stack_frame_vars = STATIC_SYMBOL("ALLOCATE-STACK-FRAME-VARS",
	    AB_package);
    Qopen_wake_up_collection = STATIC_SYMBOL("OPEN-WAKE-UP-COLLECTION",
	    AB_package);
    Qrule_let = STATIC_SYMBOL("RULE-LET",AB_package);
    list_constant_33 = STATIC_CONS(list_constant_6,list_constant_31);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_33);
    Qin_order = STATIC_SYMBOL("IN-ORDER",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_33);
    Qbranch_if_known = STATIC_SYMBOL("BRANCH-IF-KNOWN",AB_package);
    list_constant_34 = STATIC_CONS(list_constant_6,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant_34);
    Qexecute_antecedent = STATIC_SYMBOL("EXECUTE-ANTECEDENT",AB_package);
    Qset_wake_ups = STATIC_SYMBOL("SET-WAKE-UPS",AB_package);
    Qclose_wake_up_collection = STATIC_SYMBOL("CLOSE-WAKE-UP-COLLECTION",
	    AB_package);
    Qcomplete_rule_instance = STATIC_SYMBOL("COMPLETE-RULE-INSTANCE",
	    AB_package);
    Qbegin_activity = STATIC_SYMBOL("BEGIN-ACTIVITY",AB_package);
    Qbegin_rule_actions = STATIC_SYMBOL("BEGIN-RULE-ACTIONS",AB_package);
    Qrule_maximum_received_value_count = 
	    STATIC_SYMBOL("RULE-MAXIMUM-RECEIVED-VALUE-COUNT",AB_package);
    Qrule_return_value_position = 
	    STATIC_SYMBOL("RULE-RETURN-VALUE-POSITION",AB_package);
    Qrule_byte_code_body = STATIC_SYMBOL("RULE-BYTE-CODE-BODY",AB_package);
    Qrule_context_length = STATIC_SYMBOL("RULE-CONTEXT-LENGTH",AB_package);
    Qrule_environment_length = STATIC_SYMBOL("RULE-ENVIRONMENT-LENGTH",
	    AB_package);
    Quniversal_compilation = STATIC_SYMBOL("UNIVERSAL-COMPILATION",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qany_inverse = STATIC_SYMBOL("ANY-INVERSE",AB_package);
    Qthe_inverse = STATIC_SYMBOL("THE-INVERSE",AB_package);
    Qthe_inverse_no_bind = STATIC_SYMBOL("THE-INVERSE-NO-BIND",AB_package);
    string_constant_3 = STATIC_STRING("rule context rewriter");
    string_constant_4 = STATIC_STRING("Unrecognized context quantifier ~a.");
    string_constant_5 = STATIC_STRING("rule context rewrite");
    string_constant_6 = 
	    STATIC_STRING("The local name ~a hadn\'t been registered.");
    Qlet_action = STATIC_SYMBOL("LET-ACTION",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    QCERTAINTY_VAR = STATIC_SYMBOL("certainty-var",AB_package);
    QEXPIRATION_VAR = STATIC_SYMBOL("expiration-var",AB_package);
    Qpause_kb = STATIC_SYMBOL("PAUSE-KB",AB_package);
    string_constant_7 = 
	    STATIC_STRING("Pause knowledge-base must be the last action in a rule.");
    Qrequired_domain_types_of_role = 
	    STATIC_SYMBOL("REQUIRED-DOMAIN-TYPES-OF-ROLE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    string_constant_8 = 
	    STATIC_STRING(", ~a, did not match the required count, ~a");
    Qopen_role_iteration = STATIC_SYMBOL("OPEN-ROLE-ITERATION",AB_package);
    Qopen_role_iteration_no_domain = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN",AB_package);
    Qserve_next_iteration_value = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE",AB_package);
    Qclose_iteration = STATIC_SYMBOL("CLOSE-ITERATION",AB_package);
    if (Current_let_action_bindings == UNBOUND)
	Current_let_action_bindings = Nil;
    Qaction_compiler = STATIC_SYMBOL("ACTION-COMPILER",AB_package);
    Qset_expiration = STATIC_SYMBOL("SET-EXPIRATION",AB_package);
    Qclear_wake_ups = STATIC_SYMBOL("CLEAR-WAKE-UPS",AB_package);
    string_constant_9 = STATIC_STRING("rule action compiler");
    string_constant_10 = STATIC_STRING("No compiler for action ~a.");
    Qadd_to_action_cache = STATIC_SYMBOL("ADD-TO-ACTION-CACHE",AB_package);
    Qrestore_from_action_cache_or_branch = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH",AB_package);
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    Qaction_cache = STATIC_SYMBOL("ACTION-CACHE",AB_package);
    list_constant_11 = STATIC_CONS(Qaction_cache,Qnil);
    Qclear_action_cache = STATIC_SYMBOL("CLEAR-ACTION-CACHE",AB_package);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    list_constant_12 = STATIC_CONS(Qobsolete_datum,Qnil);
    Qcomplete_cell_expression = STATIC_SYMBOL("COMPLETE-CELL-EXPRESSION",
	    AB_package);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    Qdummy_instruction = STATIC_SYMBOL("DUMMY-INSTRUCTION",AB_package);
    Qpreferred_instruction_chooser = 
	    STATIC_SYMBOL("PREFERRED-INSTRUCTION-CHOOSER",AB_package);
    dummy_instruction_i_chooser_1 = 
	    STATIC_FUNCTION(dummy_instruction_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qdummy_instruction,
	    dummy_instruction_i_chooser_1,Qpreferred_instruction_chooser);
    Qno_op = STATIC_SYMBOL("NO-OP",AB_package);
    no_op_i_chooser_1 = STATIC_FUNCTION(no_op_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qno_op,no_op_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qpush_constant = STATIC_SYMBOL("PUSH-CONSTANT",AB_package);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qfloat,
	    list_constant_33);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    string_constant_11 = 
	    STATIC_STRING("The text beginning with \"~a...\" contains more than ~a characters.");
    push_constant_i_chooser_1 = STATIC_FUNCTION(push_constant_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qpush_constant,push_constant_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qname_reference = STATIC_SYMBOL("NAME-REFERENCE",AB_package);
    Qno_item_implies_unknown = STATIC_SYMBOL("NO-ITEM-IMPLIES-UNKNOWN",
	    AB_package);
    list_constant_14 = STATIC_CONS(Qno_item_implies_unknown,Qnil);
    Qstable_name_of_class_instance = 
	    STATIC_SYMBOL("STABLE-NAME-OF-CLASS-INSTANCE",AB_package);
    Qstable_name = STATIC_SYMBOL("STABLE-NAME",AB_package);
    Qname_of_type = STATIC_SYMBOL("NAME-OF-TYPE",AB_package);
    name_reference_i_chooser_1 = STATIC_FUNCTION(name_reference_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qname_reference,name_reference_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qpush_cached_item = STATIC_SYMBOL("PUSH-CACHED-ITEM",AB_package);
    push_cached_item_i_chooser_1 = 
	    STATIC_FUNCTION(push_cached_item_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qpush_cached_item,push_cached_item_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qevaluate_role_with_no_domain = 
	    STATIC_SYMBOL("EVALUATE-ROLE-WITH-NO-DOMAIN",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)57344L);
    evaluate_role_with_no_domain_i_chooser_1 = 
	    STATIC_FUNCTION(evaluate_role_with_no_domain_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qevaluate_role_with_no_domain,
	    evaluate_role_with_no_domain_i_chooser_1,
	    Qpreferred_instruction_chooser);
    if (Sorted_static_evaluate_role_dispatchers == UNBOUND)
	Sorted_static_evaluate_role_dispatchers = Nil;
    Qunique_value_of_role_instruction_name = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-INSTRUCTION-NAME",AB_package);
    Unique_value_of_role_instruction_name_prop = 
	    Qunique_value_of_role_instruction_name;
    Qstatic_evaluate_role_dispatch_predicate = 
	    STATIC_SYMBOL("STATIC-EVALUATE-ROLE-DISPATCH-PREDICATE",
	    AB_package);
    Static_evaluate_role_dispatch_predicate_prop = 
	    Qstatic_evaluate_role_dispatch_predicate;
    Qstatic_evaluate_role_dispatch_parent = 
	    STATIC_SYMBOL("STATIC-EVALUATE-ROLE-DISPATCH-PARENT",AB_package);
    Static_evaluate_role_dispatch_parent_prop = 
	    Qstatic_evaluate_role_dispatch_parent;
    Qg2_toggle_evaluate_role_inline = 
	    STATIC_SYMBOL("G2-TOGGLE-EVALUATE-ROLE-INLINE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_toggle_evaluate_role_inline,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_toggle_evaluate_role_inline,
	    STATIC_FUNCTION(g2_toggle_evaluate_role_inline,NIL,FALSE,1,1));
    Qcdr_greater_p = STATIC_SYMBOL("CDR-GREATER-P",AB_package);
    SET_SYMBOL_FUNCTION(Qcdr_greater_p,STATIC_FUNCTION(cdr_greater_p,NIL,
	    FALSE,2,2));
    Qnamed_by_symbol = STATIC_SYMBOL("NAMED-BY-SYMBOL",AB_package);
    mutate_global_property(Qnamed_by_symbol,Qnil,
	    Qunique_value_of_role_instruction_name);
    mutate_global_property(Qnamed_by_symbol,Qnil,
	    Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    Qnamed_by = STATIC_SYMBOL("NAMED-BY",AB_package);
    named_by_symbol_dispatch_predicate_1 = 
	    STATIC_FUNCTION(named_by_symbol_dispatch_predicate,NIL,FALSE,5,5);
    mutate_global_property(Qnamed_by_symbol,
	    named_by_symbol_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    Qname_of_item = STATIC_SYMBOL("NAME-OF-ITEM",AB_package);
    mutate_global_property(Qname_of_item,Qnil,
	    Qunique_value_of_role_instruction_name);
    mutate_global_property(Qname_of_item,Qnil,
	    Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    Qname = STATIC_SYMBOL("NAME",AB_package);
    name_of_item_dispatch_predicate_1 = 
	    STATIC_FUNCTION(name_of_item_dispatch_predicate,NIL,FALSE,5,5);
    mutate_global_property(Qname_of_item,name_of_item_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    Qrelated_to_item = STATIC_SYMBOL("RELATED-TO-ITEM",AB_package);
    mutate_global_property(Qrelated_to_item,Qnil,
	    Qunique_value_of_role_instruction_name);
    mutate_global_property(Qrelated_to_item,Qnil,
	    Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    Qrelated = STATIC_SYMBOL("RELATED",AB_package);
    related_to_item_dispatch_predicate_1 = 
	    STATIC_FUNCTION(related_to_item_dispatch_predicate,NIL,FALSE,5,5);
    mutate_global_property(Qrelated_to_item,
	    related_to_item_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    Qnth_element_of_integer_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-INTEGER-ARRAY",AB_package);
    Qnth_integer_array_element = STATIC_SYMBOL("NTH-INTEGER-ARRAY-ELEMENT",
	    AB_package);
    mutate_global_property(Qnth_element_of_integer_array,
	    Qnth_integer_array_element,Qunique_value_of_role_instruction_name);
    Qnth_element_of_value_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-VALUE-ARRAY",AB_package);
    mutate_global_property(Qnth_element_of_integer_array,
	    Qnth_element_of_value_array,Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qab_class,Qinteger_array);
    nth_element_of_integer_array_dispatch_predicate_1 = 
	    STATIC_FUNCTION(nth_element_of_integer_array_dispatch_predicate,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_integer_array,
	    nth_element_of_integer_array_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    Qnth_element_of_float_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-FLOAT-ARRAY",AB_package);
    Qnth_float_array_element = STATIC_SYMBOL("NTH-FLOAT-ARRAY-ELEMENT",
	    AB_package);
    mutate_global_property(Qnth_element_of_float_array,
	    Qnth_float_array_element,Qunique_value_of_role_instruction_name);
    mutate_global_property(Qnth_element_of_float_array,
	    Qnth_element_of_value_array,Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qab_class,Qfloat_array);
    nth_element_of_float_array_dispatch_predicate_1 = 
	    STATIC_FUNCTION(nth_element_of_float_array_dispatch_predicate,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_float_array,
	    nth_element_of_float_array_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    mutate_global_property(Qnth_element_of_value_array,Qnil,
	    Qunique_value_of_role_instruction_name);
    mutate_global_property(Qnth_element_of_value_array,Qnil,
	    Qstatic_evaluate_role_dispatch_parent);
    Sorted_static_evaluate_role_dispatchers = Nil;
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qab_class,Qvalue_array);
    nth_element_of_value_array_dispatch_predicate_1 = 
	    STATIC_FUNCTION(nth_element_of_value_array_dispatch_predicate,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_value_array,
	    nth_element_of_value_array_dispatch_predicate_1,
	    Qstatic_evaluate_role_dispatch_predicate);
    Qevaluate_role = STATIC_SYMBOL("EVALUATE-ROLE",AB_package);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    list_constant_18 = STATIC_CONS(Qplace_reference,Qnil);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_18);
    list_constant_19 = STATIC_CONS(list_constant_22,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_21 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_36 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_21);
    list_constant_20 = STATIC_CONS(list_constant_36,Qnil);
    string_constant_12 = STATIC_STRING("role compiler");
    string_constant_13 = STATIC_STRING("Unknown role type ~a.");
    array_constant_3 = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    string_constant_14 = 
	    STATIC_STRING("\" requires ~a arguments, but received ~a.");
    string_constant_15 = STATIC_STRING("attribute place reference");
    string_constant_16 = 
	    string_append2(STATIC_STRING("Cannot compile concludes or changes on attributes when the ~\n                  frame containing the attribute is permitted to be missing.  ~\n                  Required type = "),
	    STATIC_STRING("~NT, attribute = ~a."));
    Qattribute_of_class = STATIC_SYMBOL("ATTRIBUTE-OF-CLASS",AB_package);
    Qattribute_frame_or_place_reference = 
	    STATIC_SYMBOL("ATTRIBUTE-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qclass_qualified_attribute_of_class = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS",AB_package);
    Qclass_qualified_name_frame_or_place_reference = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE",
	    AB_package);
    Qelement_frame_or_place_reference = 
	    STATIC_SYMBOL("ELEMENT-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    evaluate_role_i_chooser_1 = STATIC_FUNCTION(evaluate_role_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qevaluate_role,evaluate_role_i_chooser_1,
	    Qpreferred_instruction_chooser);
    string_constant_17 = STATIC_STRING("the attribute ~a ~a");
    Qgiver_of_value = STATIC_SYMBOL("GIVER-OF-VALUE",AB_package);
    giver_of_value_i_chooser_1 = STATIC_FUNCTION(giver_of_value_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qgiver_of_value,giver_of_value_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qpush_from_surrounding_local_var = 
	    STATIC_SYMBOL("PUSH-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    string_constant_18 = STATIC_STRING("instruction chooser");
    string_constant_19 = 
	    STATIC_STRING("No type could be determined for var-spot ~a.");
    push_from_surrounding_local_var_i_chooser_1 = 
	    STATIC_FUNCTION(push_from_surrounding_local_var_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qpush_from_surrounding_local_var,
	    push_from_surrounding_local_var_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qcopy_into_surrounding_local_var = 
	    STATIC_SYMBOL("COPY-INTO-SURROUNDING-LOCAL-VAR",AB_package);
    string_constant_20 = 
	    STATIC_STRING("copy into surrounding local var instruction chooser");
    copy_into_surrounding_local_var_i_chooser_1 = 
	    STATIC_FUNCTION(copy_into_surrounding_local_var_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qcopy_into_surrounding_local_var,
	    copy_into_surrounding_local_var_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qmove_from_surrounding_local_var = 
	    STATIC_SYMBOL("MOVE-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    string_constant_21 = 
	    STATIC_STRING("In move-from-surrounding-local-var, no type could be determined or  ~\n           no-item allowed.  Var-spot ~a, type = ~a.");
    move_from_surrounding_local_var_i_chooser_1 = 
	    STATIC_FUNCTION(move_from_surrounding_local_var_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qmove_from_surrounding_local_var,
	    move_from_surrounding_local_var_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qcoerce_to_datum = STATIC_SYMBOL("COERCE-TO-DATUM",AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qab_class,Qparameter);
    coerce_to_datum_i_chooser_1 = 
	    STATIC_FUNCTION(coerce_to_datum_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qcoerce_to_datum,coerce_to_datum_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qcoerce_no_item_to_unknown = STATIC_SYMBOL("COERCE-NO-ITEM-TO-UNKNOWN",
	    AB_package);
    coerce_no_item_to_unknown_i_chooser_1 = 
	    STATIC_FUNCTION(coerce_no_item_to_unknown_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qcoerce_no_item_to_unknown,
	    coerce_no_item_to_unknown_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qensure_type = STATIC_SYMBOL("ENSURE-TYPE",AB_package);
    ensure_type_i_chooser_1 = STATIC_FUNCTION(ensure_type_i_chooser,NIL,
	    FALSE,1,1);
    mutate_global_property(Qensure_type,ensure_type_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qexecute_normal_form_tree = STATIC_SYMBOL("EXECUTE-NORMAL-FORM-TREE",
	    AB_package);
    execute_normal_form_tree_i_chooser_1 = 
	    STATIC_FUNCTION(execute_normal_form_tree_i_chooser,NIL,FALSE,1,1);
    mutate_global_property(Qexecute_normal_form_tree,
	    execute_normal_form_tree_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qcall_procedure = STATIC_SYMBOL("CALL-PROCEDURE",AB_package);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_34);
    call_procedure_i_chooser_1 = STATIC_FUNCTION(call_procedure_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcall_procedure,call_procedure_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qfunction_call = STATIC_SYMBOL("FUNCTION-CALL",AB_package);
    call_function_i_chooser_1 = STATIC_FUNCTION(call_function_i_chooser,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcall_function,call_function_i_chooser_1,
	    Qpreferred_instruction_chooser);
    Qstack_node_instruction_emitter = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EMITTER",AB_package);
    dummy_instruction_i_emit_1 = STATIC_FUNCTION(dummy_instruction_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qdummy_instruction,dummy_instruction_i_emit_1,
	    Qstack_node_instruction_emitter);
    no_op_i_emit_1 = STATIC_FUNCTION(no_op_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qno_op,no_op_i_emit_1,
	    Qstack_node_instruction_emitter);
    push_constant_i_emit_1 = STATIC_FUNCTION(push_constant_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qpush_constant,push_constant_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qstack_node_instruction_reclaimer = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-RECLAIMER",AB_package);
    push_constant_i_reclaim_1 = STATIC_FUNCTION(push_constant_i_reclaim,
	    NIL,FALSE,1,1);
    mutate_global_property(Qpush_constant,push_constant_i_reclaim_1,
	    Qstack_node_instruction_reclaimer);
    Qstack_node_instruction_extra_info_copier = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-EXTRA-INFO-COPIER",
	    AB_package);
    push_constant_i_copy_1 = STATIC_FUNCTION(push_constant_i_copy,NIL,
	    FALSE,1,1);
    mutate_global_property(Qpush_constant,push_constant_i_copy_1,
	    Qstack_node_instruction_extra_info_copier);
    name_reference_i_emit_1 = STATIC_FUNCTION(name_reference_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qname_reference,name_reference_i_emit_1,
	    Qstack_node_instruction_emitter);
    push_cached_item_i_emit_1 = STATIC_FUNCTION(push_cached_item_i_emit,
	    NIL,FALSE,3,3);
    mutate_global_property(Qpush_cached_item,push_cached_item_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    push_from_surrounding_local_var_i_emit_1 = 
	    STATIC_FUNCTION(push_from_surrounding_local_var_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qpush_from_surrounding_local_var,
	    push_from_surrounding_local_var_i_emit_1,
	    Qstack_node_instruction_emitter);
    copy_into_surrounding_local_var_i_emit_1 = 
	    STATIC_FUNCTION(copy_into_surrounding_local_var_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qcopy_into_surrounding_local_var,
	    copy_into_surrounding_local_var_i_emit_1,
	    Qstack_node_instruction_emitter);
    move_from_surrounding_local_var_i_emit_1 = 
	    STATIC_FUNCTION(move_from_surrounding_local_var_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qmove_from_surrounding_local_var,
	    move_from_surrounding_local_var_i_emit_1,
	    Qstack_node_instruction_emitter);
    evaluate_role_with_no_domain_i_emit_1 = 
	    STATIC_FUNCTION(evaluate_role_with_no_domain_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qevaluate_role_with_no_domain,
	    evaluate_role_with_no_domain_i_emit_1,
	    Qstack_node_instruction_emitter);
    evaluate_role_i_emit_1 = STATIC_FUNCTION(evaluate_role_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qevaluate_role,evaluate_role_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qevaluate_role_implicit_scope = 
	    STATIC_SYMBOL("EVALUATE-ROLE-IMPLICIT-SCOPE",AB_package);
    evaluate_role_implicit_scope_i_emit_1 = 
	    STATIC_FUNCTION(evaluate_role_implicit_scope_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qevaluate_role_implicit_scope,
	    evaluate_role_implicit_scope_i_emit_1,
	    Qstack_node_instruction_emitter);
    giver_of_value_i_emit_1 = STATIC_FUNCTION(giver_of_value_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qgiver_of_value,giver_of_value_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qexpiration_source_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SOURCE-OPERATOR-P",AB_package);
    mutate_global_property(Qcoerce_to_datum,T,Qexpiration_source_operator_p);
    coerce_to_datum_i_emit_1 = STATIC_FUNCTION(coerce_to_datum_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qcoerce_to_datum,coerce_to_datum_i_emit_1,
	    Qstack_node_instruction_emitter);
    mutate_global_property(Qcoerce_no_item_to_unknown,T,
	    Qexpiration_source_operator_p);
    coerce_no_item_to_unknown_i_emit_1 = 
	    STATIC_FUNCTION(coerce_no_item_to_unknown_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qcoerce_no_item_to_unknown,
	    coerce_no_item_to_unknown_i_emit_1,
	    Qstack_node_instruction_emitter);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    ensure_type_i_emit_1 = STATIC_FUNCTION(ensure_type_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qensure_type,ensure_type_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_22 = 
	    STATIC_STRING("The result of an expression was required to be of type ~NT, but it returned type ~NT.");
    string_constant_23 = STATIC_STRING("normal form tree emitter");
    string_constant_24 = 
	    STATIC_STRING("Normal form tree has no arguments with expirations.");
    execute_normal_form_tree_i_emit_1 = 
	    STATIC_FUNCTION(execute_normal_form_tree_i_emit,NIL,FALSE,3,3);
    mutate_global_property(Qexecute_normal_form_tree,
	    execute_normal_form_tree_i_emit_1,Qstack_node_instruction_emitter);
    Qexpiration_special_form_operator_p = 
	    STATIC_SYMBOL("EXPIRATION-SPECIAL-FORM-OPERATOR-P",AB_package);
    mutate_global_property(Qcall_procedure,T,
	    Qexpiration_special_form_operator_p);
    call_procedure_i_emit_1 = STATIC_FUNCTION(call_procedure_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qcall_procedure,call_procedure_i_emit_1,
	    Qstack_node_instruction_emitter);
    mutate_global_property(Qcall_function,T,
	    Qexpiration_special_form_operator_p);
    call_function_i_emit_1 = STATIC_FUNCTION(call_function_i_emit,NIL,
	    FALSE,3,3);
    mutate_global_property(Qcall_function,call_function_i_emit_1,
	    Qstack_node_instruction_emitter);
    string_constant_25 = STATIC_STRING("stack node emitter");
    string_constant_26 = 
	    STATIC_STRING("The stack node instruction ~a had no byte code emitter.");
    string_constant_27 = 
	    STATIC_STRING("A preferred evaluator had not been chosen for ~a.");
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    Qis_moved = STATIC_SYMBOL("IS-MOVED",AB_package);
    Qis_moved_by_the_user = STATIC_SYMBOL("IS-MOVED-BY-THE-USER",AB_package);
    Qis_moved_by_g2 = STATIC_SYMBOL("IS-MOVED-BY-G2",AB_package);
    Qis_resized_by_the_user = STATIC_SYMBOL("IS-RESIZED-BY-THE-USER",
	    AB_package);
    Qis_activated = STATIC_SYMBOL("IS-ACTIVATED",AB_package);
    Qis_deactivated = STATIC_SYMBOL("IS-DEACTIVATED",AB_package);
    Qis_enabled = STATIC_SYMBOL("IS-ENABLED",AB_package);
    Qis_disabled = STATIC_SYMBOL("IS-DISABLED",AB_package);
    Qloses_its_value = STATIC_SYMBOL("LOSES-ITS-VALUE",AB_package);
    Qis_created = STATIC_SYMBOL("IS-CREATED",AB_package);
    Qgeneric_event = STATIC_SYMBOL("GENERIC-EVENT",AB_package);
    Qgeneric_directly_disconnected_from = 
	    STATIC_SYMBOL("GENERIC-DIRECTLY-DISCONNECTED-FROM",AB_package);
    Qdirectly_disconnected_from = 
	    STATIC_SYMBOL("DIRECTLY-DISCONNECTED-FROM",AB_package);
    Qindirectly_connected_to = STATIC_SYMBOL("INDIRECTLY-CONNECTED-TO",
	    AB_package);
    Qindirectly_disconnected_from = 
	    STATIC_SYMBOL("INDIRECTLY-DISCONNECTED-FROM",AB_package);
    Qis_of_class = STATIC_SYMBOL("IS-OF-CLASS",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)17L,Qreceives_a_value,
	    Qis_moved,Qis_moved_by_the_user,Qis_moved_by_g2,
	    Qis_resized_by_the_user,Qis_activated,Qis_deactivated,
	    Qis_enabled,Qis_disabled,Qloses_its_value,Qis_created,
	    Qgeneric_event,Qgeneric_directly_disconnected_from,
	    Qdirectly_disconnected_from,Qindirectly_connected_to,
	    Qindirectly_disconnected_from,Qis_of_class);
    Qstack_evaluators = STATIC_SYMBOL("STACK-EVALUATORS",AB_package);
    string_constant_28 = STATIC_STRING("op-code-for-operator-of-type");
    string_constant_29 = STATIC_STRING("Can\'t find evaluator for ~a of ~NT.");
    if (Already_mutated_evaluators == UNBOUND)
	Already_mutated_evaluators = Nil;
    Qstack_special_form_converter = 
	    STATIC_SYMBOL("STACK-SPECIAL-FORM-CONVERTER",AB_package);
    Qdoes_not_exist = STATIC_SYMBOL("DOES-NOT-EXIST",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    if (Compile_reference_to_system_slot == UNBOUND)
	Compile_reference_to_system_slot = Nil;
    string_constant_30 = 
	    STATIC_STRING("All local names for procedures must be declared at ~\n                   the top of the procedure definition.  This ~\n                   designation could not be compiled: ~ND.");
    string_constant_31 = 
	    STATIC_STRING("No local name could be found for \"~ND\".");
    string_constant_32 = 
	    STATIC_STRING("All local names for procedures must be declared at the top of the ~\n            procedure definition.  This designation could not be ~\n            compiled: ~ND.");
    string_constant_33 = 
	    string_append2(STATIC_STRING("The reference \"~ND\" cannot be compiled because it references a ~\n              system defined attribute, ~a.  You can use \"the text of\" ~\n              around references to sy"),
	    STATIC_STRING("stem defined attributes to get the text ~\n              that is visible in attribute tables for that attribute."));
    string_constant_34 = STATIC_STRING("The malformed expression ~a (");
    array_constant_4 = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_35 = STATIC_STRING(" ~a");
    string_constant_36 = STATIC_STRING(" . ~a");
    array_constant_5 = STATIC_ARRAY(list_constant_35,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    string_constant_37 = STATIC_STRING("stack node converter");
    string_constant_38 = 
	    STATIC_STRING("The malformed expression ~a could not be compiled.");
    string_constant_39 = 
	    STATIC_STRING("The malformed designation ~a could not be compiled.");
    list_constant_27 = STATIC_LIST((SI_Long)4L,Qplus,Qstar,Qmax,Qmin);
    string_constant_40 = STATIC_STRING("preferred evaluation chooser");
    string_constant_41 = STATIC_STRING("No evaluator was choosen for ~a.");
    string_constant_42 = 
	    STATIC_STRING("preferred evaluator instruction chooser");
    string_constant_43 = 
	    STATIC_STRING("The stack node instruction ~a had no preferred instruction ~\n              chooser.");
    string_constant_44 = STATIC_STRING("instruction and type chooser");
    string_constant_45 = 
	    STATIC_STRING("No value type chosen for operation ~a.");
    string_constant_46 = 
	    STATIC_STRING("An argument to ~a, which is required to be of type ~NT, was of ~\n               type ~NT.");
    string_constant_47 = 
	    STATIC_STRING("The operation ~a is required to produce a value of type ~NT, ~\n               but instead produces values of type ~NT.");
    Qsource = STATIC_SYMBOL("SOURCE",AB_package);
    Qtrivial_tree = STATIC_SYMBOL("TRIVIAL-TREE",AB_package);
    Qsingle_source_tree = STATIC_SYMBOL("SINGLE-SOURCE-TREE",AB_package);
    Qsource_tree = STATIC_SYMBOL("SOURCE-TREE",AB_package);
    Qspecial_tree = STATIC_SYMBOL("SPECIAL-TREE",AB_package);
    Qminimizing = STATIC_SYMBOL("MINIMIZING",AB_package);
    Qnormal_tree = STATIC_SYMBOL("NORMAL-TREE",AB_package);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qfloat,
	    list_constant_34);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_34);
    Qfirst_that_has_a_value = STATIC_SYMBOL("FIRST-THAT-HAS-A-VALUE",
	    AB_package);
    Qhas_a_value = STATIC_SYMBOL("HAS-A-VALUE",AB_package);
    Qvalue_of = STATIC_SYMBOL("VALUE-OF",AB_package);
    Qfirst_that_has_a_current_value = 
	    STATIC_SYMBOL("FIRST-THAT-HAS-A-CURRENT-VALUE",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)4L,Qfirst_that_has_a_value,
	    Qhas_a_value,Qvalue_of,Qfirst_that_has_a_current_value);
    string_constant_48 = 
	    STATIC_STRING("The value of an expression could possibly be unknown.  This expression ~\n       must be executed within a COLLECT DATA or WAIT UNTIL statement.");
    string_constant_49 = 
	    STATIC_STRING("unknown value stack node tree rewrite");
    string_constant_50 = STATIC_STRING("Unknown tree type ~a.");
    string_constant_51 = STATIC_STRING("unknown subtree search");
}
