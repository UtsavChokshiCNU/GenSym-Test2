/* pccmp.c
 * Input file:  proc-comp.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pccmp.h"


DEFINE_VARIABLE_WITH_SYMBOL(Generated_var_spots_for_base_code_body_return, Qgenerated_var_spots_for_base_code_body_return);

DEFINE_VARIABLE_WITH_SYMBOL(Returned_values_description, Qreturned_values_description);

DEFINE_VARIABLE_WITH_SYMBOL(Return_statement_processed_qm, Qreturn_statement_processed_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Call_statement_processed_qm, Qcall_statement_processed_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Expression_bound_local_names, Qexpression_bound_local_names);

static Object Qprocedure_statement_writer;  /* procedure-statement-writer */

static Object string_constant;     /* "~a" */

/* WRITE-PROCEDURE-STATEMENT */
Object write_procedure_statement(statement_to_write)
    Object statement_to_write;
{
    Object gensymed_symbol, writer;

    x_note_fn_call(161,0);
    gensymed_symbol = CAR(statement_to_write);
    writer = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qprocedure_statement_writer);
    if (writer)
	FUNCALL_1(writer,statement_to_write);
    else
	tformat(2,string_constant,statement_to_write);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_branch_short_cuts, Qprocedure_branch_short_cuts);

static Object string_constant_1;   /* "instruction address lookup" */

static Object string_constant_2;   /* "The tag ~a was referenced via a JUMP instruction, but ~
				    *                          no such reference had been noted."
				    */

static Object string_constant_3;   /* "The tag ~a was referenced, but no such tag is declared for ~
				    *                  this procedure."
				    */

static Object string_constant_4;   /* "address resolver" */

static Object string_constant_5;   /* "The tag ~a did not have a registered address at address ~
				    *              resolution time."
				    */

/* INSTRUCTION-ADDRESS-FOR-TAG */
Object instruction_address_for_tag(tag_name,jump_reference_qm)
    Object tag_name, jump_reference_qm;
{
    Object temp, goto_tag_entry_qm, address_qm;

    x_note_fn_call(161,1);
    if (Procedure_branch_short_cuts) {
	if (jump_reference_qm)
	    return VALUES_1(tag_name);
	else {
	    temp = assoc_eql(tag_name,Procedure_branch_short_cuts);
	    temp = CDR(temp);
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(tag_name);
	}
    }
    else {
	goto_tag_entry_qm = goto_tag_entry_with_name(tag_name,
		Goto_tags_in_compilation);
	address_qm = Nil;
	if (goto_tag_entry_qm) {
	    if (jump_reference_qm) {
		if (ISVREF(goto_tag_entry_qm,(SI_Long)4L))
		    address_qm = ISVREF(goto_tag_entry_qm,(SI_Long)6L);
		else {
		    compiler_bug(3,string_constant_1,string_constant_2,
			    tag_name);
		    address_qm = FIX((SI_Long)0L);
		}
	    }
	    else
		address_qm = ISVREF(goto_tag_entry_qm,(SI_Long)5L);
	}
	else {
	    compiler_error(2,string_constant_3,tag_name);
	    address_qm = FIX((SI_Long)0L);
	}
	if ( !TRUEP(address_qm)) {
	    compiler_bug(3,string_constant_4,string_constant_5,tag_name);
	    address_qm = FIX((SI_Long)0L);
	}
	return VALUES_1(address_qm);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Base_code_body_return_tag, Qbase_code_body_return_tag);

/* GOTO-TAG-ENTRY-WITH-NAME */
Object goto_tag_entry_with_name(tag_name,tag_entries)
    Object tag_name, tag_entries;
{
    Object entry, ab_loop_list_, entry_tag_name;
    char tag_name_is_fixnum_qm;

    x_note_fn_call(161,2);
    tag_name_is_fixnum_qm = FIXNUMP(tag_name);
    entry = Nil;
    ab_loop_list_ = tag_entries;
    entry_tag_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    entry_tag_name = ISVREF(entry,(SI_Long)1L);
    if (tag_name_is_fixnum_qm ? FIXNUMP(entry_tag_name) && 
	    FIXNUM_EQ(tag_name,entry_tag_name) :  !FIXNUMP(entry_tag_name) 
	    && EQ(tag_name,entry_tag_name))
	return VALUES_1(entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qpseudo_instruction_byte_code_emitter;  /* pseudo-instruction-byte-code-emitter */

static Object string_constant_6;   /* "byte code emitter" */

static Object string_constant_7;   /* "The pseudo instruction ~a had no byte code emitter function." */

/* EMIT-BYTE-CODE-VECTOR-FOR-PROCEDURE */
Object emit_byte_code_vector_for_procedure(byte_code_stream,instructions)
    Object byte_code_stream, instructions;
{
    Object compiler_instruction, ab_loop_list_, instruction_name;
    Object emitter_function_qm;

    x_note_fn_call(161,3);
    compiler_instruction = Nil;
    ab_loop_list_ = instructions;
    instruction_name = Nil;
    emitter_function_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    compiler_instruction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    instruction_name = CONSP(compiler_instruction) ? 
	    M_CAR(compiler_instruction) : Nil;
    emitter_function_qm = instruction_name ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(instruction_name),
	    Qpseudo_instruction_byte_code_emitter) : Nil;
    if (emitter_function_qm)
	inline_funcall_2(emitter_function_qm,byte_code_stream,
		compiler_instruction);
    else
	compiler_bug(3,string_constant_6,string_constant_7,instruction_name);
    goto next_loop;
  end_loop:;
    return coalesce_lookup_structures(2,ISVREF(byte_code_stream,
	    (SI_Long)8L),byte_code_stream);
}

Object Goto_tag_replacer_prop = UNBOUND;

Object Goto_tag_references_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_return_values_position, Qcurrent_return_values_position);

/* LIST-TO-MANAGED-ARRAY */
Object list_to_managed_array(list_1)
    Object list_1;
{
    Object length_1, array, item, ab_loop_list_, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(161,4);
    length_1 = length(list_1);
    array = allocate_managed_array(1,length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    item = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(array,svref_arg_2) = item;
    }
    else {
	svref_arg_1 = ISVREF(array,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = item;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(array);
}

static Object Qbegin_statement;    /* begin-statement */

/* PROCEDURE-HAS-EMPTY-CODE-BODY-P */
Object procedure_has_empty_code_body_p(proc_def)
    Object proc_def;
{
    Object body, body_length, first_operator;

    x_note_fn_call(161,5);
    body = FIFTH(proc_def);
    body_length = length(body);
    first_operator = CAR(body);
    if (EQ(first_operator,Qbegin_statement) && EQ(body_length,
	    FIX((SI_Long)1L)))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

static Object Qcompile_procedure_note;  /* compile-procedure-note */

static Object Qhas_empty_code_body_qm;  /* has-empty-code-body? */

static Object Qn_compiles_this_session;  /* n-compiles-this-session */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qname;               /* name */

static Object Qargument_count;     /* argument-count */

static Object Qargument_list_description;  /* argument-list-description */

static Object Qprocedure_method_class;  /* procedure-method-class */

static Object string_constant_8;   /* "the procedure method must have at least one argument" */

static Object string_constant_9;   /* "the first argument of a procedure method must be of type item" */

static Object Qprocedure_method_name;  /* procedure-method-name */

static Object string_constant_10;  /* "Procedure body completed without a return statement.  This procedure must use a return statement since it is declared to return values." */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_11;  /* "Procedure body for ~a completed without a return statement.  This procedure must use a return statement since it is declared to return values." */

static Object list_constant;       /* # */

static Object Qsignal_error;       /* signal-error */

static Object Qtext;               /* text */

static Object Qtag_statement;      /* tag-statement */

static Object Qreturn_values;      /* return-values */

static Object Kreturn_value;       /* :return-value */

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

static Object Qenvironment_description;  /* environment-description */

static Object Qbad;                /* bad */

static Object Qparse_results_qm;   /* parse-results? */

/* COMPILE-PROCEDURE-DEFINITION */
Object compile_procedure_definition(procedure,procedure_definition)
    Object procedure, procedure_definition;
{
    Object temp, gensymed_symbol, name, args, return_types, local_vars;
    Object body_statement, current_computation_frame;
    Object current_computation_component_particulars;
    Object missing_local_names_already_reported;
    Object duplicate_local_names_already_reported, base_environment;
    Object returned_values_description, return_statement_processed_qm;
    Object call_statement_processed_qm, argument_list_description;
    Object variable_initializations, code_body_frames, warning_string;
    Object inlineable_qm, incoming_parse_result, sub_class_bit_vector;
    Object specific_method_p_qm, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, svref_new_value;
    Object gensymed_symbol_4, stack_of_slot_value_changes, gensymed_symbol_5;
    Object gensymed_symbol_6, slot_description_1, current_edit_state;
    Object compiler_errors, compiler_warnings, new_goto_tag_counter;
    Object goto_tags_in_compilation, lexically_visible_goto_tags;
    Object lexically_visible_code_bodies, code_body_entries_in_compilation;
    Object stack_nodes_to_reclaim, compiler_free_references;
    Object collecting_free_references, suppress_updates_to_name_boxes, temp_3;
    Object first_argument_type_qm, first_argument_class_qm, old_method_name_qm;
    Object old_method_class_qm, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object generated_var_spots_for_base_code_body_return;
    Object base_code_body_return_tag, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object description, ab_loop_list_, var_spot_name, ab_loop_list__1;
    Object var_spot, type, return_expressions, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, code_body, code_body_entry, temp_4;
    Object base_code_body_entry, byte_code_stream, ab_loop_iter_flag_;
    Object current_return_values_position, maximum_received_values;
    Object byte_code_vector, byte_code_constants, activity_position;
    Object current_block_of_dependent_frame, environment, environment_length;
    Object temp_5, first_code_body_qm, byte_code_body_zero_qm, tag;
    Object frame_and_slot_or_atom, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    SI_Long bv16_length, aref_new_value, length_1, ab_loop_repeat_;
    SI_Long return_index, ab_loop_bind_, byte_codes_count;
    char temp_6;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(32);
    Object result;

    x_note_fn_call(161,6);
    SAVE_STACK();
    delete_frame_note_if_any(Qcompile_procedure_note,procedure);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qhas_empty_code_body_qm);
    set_lookup_slot_value_1(procedure,Qhas_empty_code_body_qm,
	    procedure_has_empty_code_body_p(procedure_definition));
    temp = FIXNUM_ADD1(get_lookup_slot_value_given_default(procedure,
	    Qn_compiles_this_session,FIX((SI_Long)0L)));
    set_non_savable_lookup_slot_value(procedure,Qn_compiles_this_session,temp);
    gensymed_symbol = procedure_definition;
    name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    return_types = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_vars = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    body_statement = CAR(gensymed_symbol);
    current_computation_frame = procedure;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    31);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      30);
	missing_local_names_already_reported = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Missing_local_names_already_reported,Qmissing_local_names_already_reported,missing_local_names_already_reported,
		29);
	  duplicate_local_names_already_reported = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Duplicate_local_names_already_reported,Qduplicate_local_names_already_reported,duplicate_local_names_already_reported,
		  28);
	    base_environment = Nil;
	    returned_values_description = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Returned_values_description,Qreturned_values_description,returned_values_description,
		    27);
	      return_statement_processed_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Return_statement_processed_qm,Qreturn_statement_processed_qm,return_statement_processed_qm,
		      26);
		call_statement_processed_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Call_statement_processed_qm,Qcall_statement_processed_qm,call_statement_processed_qm,
			25);
		  argument_list_description = Nil;
		  variable_initializations = Nil;
		  code_body_frames = Nil;
		  warning_string = Nil;
		  inlineable_qm = block_can_be_inlined_p(procedure);
		  incoming_parse_result = inlineable_qm ? 
			  copy_for_slot_value(procedure_definition) : Nil;
		  sub_class_bit_vector = ISVREF(ISVREF(procedure,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
		      specific_method_p_qm = (SI_Long)0L < 
			      gensymed_symbol_1 ? T : Nil;
		  }
		  else
		      specific_method_p_qm = Nil;
		  result_1 = Nil;
		  current_flag_state_qm = Nil;
		  slot_description = 
			  get_slot_description_of_class_description_function(Qframe_status_and_notes,
			  ISVREF(procedure,(SI_Long)1L),Nil);
		  new_cons = ISVREF(Available_stack_change_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp = Available_stack_change_conses_vector;
		      temp_1 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,temp_1) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_stack_change_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp = Available_stack_change_conses_tail_vector;
			  temp_1 = Current_thread_index;
			  SVREF(temp,temp_1) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_stack_change_cons_pool();
		  if (Nil)
		      gensymed_symbol_4 = 
			      nconc2(stack_change_list_2(procedure,
			      slot_description),stack_change_cons_1(Nil,Nil));
		  else {
		      new_cons = 
			      ISVREF(Available_stack_change_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  temp = Available_stack_change_conses_vector;
			  temp_1 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,temp_1) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_stack_change_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_stack_change_conses_tail_vector;
			      temp_1 = Current_thread_index;
			      SVREF(temp,temp_1) = Nil;
			  }
			  gensymed_symbol_4 = new_cons;
		      }
		      else
			  gensymed_symbol_4 = Nil;
		      if ( !TRUEP(gensymed_symbol_4))
			  gensymed_symbol_4 = 
				  replenish_stack_change_cons_pool();
		      M_CAR(gensymed_symbol_4) = procedure;
		      M_CDR(gensymed_symbol_4) = slot_description;
		      inline_note_allocate_cons(gensymed_symbol_4,
			      Qstack_change);
		  }
		  M_CAR(gensymed_symbol) = gensymed_symbol_4;
		  temp = Stack_of_slot_value_changes;
		  M_CDR(gensymed_symbol) = temp;
		  inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		  stack_of_slot_value_changes = gensymed_symbol;
		  PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			  24);
		    current_flag_state_qm = (SI_Long)0L != 
			    (IFIX(ISVREF(procedure,(SI_Long)5L)) & 
			    (SI_Long)16777216L) ? T : Nil;
		    if ( !TRUEP(current_flag_state_qm)) {
			gensymed_symbol = 
				ISVREF(ISVREF(ISVREF(ISVREF(procedure,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
				(SI_Long)1L);
			gensymed_symbol_4 = procedure;
			gensymed_symbol_5 = Nil;
			gensymed_symbol_6 = T;
			inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
				gensymed_symbol_5,gensymed_symbol_6);
			temp_2 = IFIX(ISVREF(procedure,(SI_Long)5L)) | 
				(SI_Long)16777216L;
			ISVREF(procedure,(SI_Long)5L) = FIX(temp_2);
		    }
		    slot_description_1 = 
			    get_slot_description_of_class_description_function(Qframe_status_and_notes,
			    ISVREF(procedure,(SI_Long)1L),Nil);
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp = Available_stack_change_conses_vector;
			temp_1 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp,temp_1) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp = Available_stack_change_conses_tail_vector;
			    temp_1 = Current_thread_index;
			    SVREF(temp,temp_1) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_stack_change_cons_pool();
		    if (Nil)
			gensymed_symbol_4 = 
				nconc2(stack_change_list_2(procedure,
				slot_description_1),
				stack_change_cons_1(Nil,Nil));
		    else {
			new_cons = 
				ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp = Available_stack_change_conses_vector;
			    temp_1 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp,temp_1) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_stack_change_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp = 
					Available_stack_change_conses_tail_vector;
				temp_1 = Current_thread_index;
				SVREF(temp,temp_1) = Nil;
			    }
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = 
				    replenish_stack_change_cons_pool();
			M_CAR(gensymed_symbol_4) = procedure;
			M_CDR(gensymed_symbol_4) = slot_description_1;
			inline_note_allocate_cons(gensymed_symbol_4,
				Qstack_change);
		    }
		    M_CAR(gensymed_symbol) = gensymed_symbol_4;
		    temp = Stack_of_slot_value_changes;
		    M_CDR(gensymed_symbol) = temp;
		    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		    stack_of_slot_value_changes = gensymed_symbol;
		    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			    23);
		      gensymed_symbol = Current_edit_state;
		      if (Generate_source_annotation_info) {
			  gensymed_symbol_4 = Current_edit_state ? 
				  get_current_sexp_annotation_hash() : Nil;
			  if (gensymed_symbol_4);
			  else
			      gensymed_symbol_4 = make_sexp_annotation_hash();
		      }
		      else
			  gensymed_symbol_4 = Nil;
		      current_edit_state = make_edit_state_1();
		      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			      22);
			temp = Current_edit_state;
			SVREF(temp,FIX((SI_Long)90L)) = gensymed_symbol_4;
			compiler_errors = Nil;
			compiler_warnings = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Compiler_warnings,Qcompiler_warnings,compiler_warnings,
				21);
			  PUSH_SPECIAL_WITH_SYMBOL(Compiler_errors,Qcompiler_errors,compiler_errors,
				  20);
			    remove_compiler_error_and_warning_frame_notes();
			    if (PUSH_UNWIND_PROTECT(3)) {
				new_goto_tag_counter = FIX((SI_Long)0L);
				goto_tags_in_compilation = Nil;
				lexically_visible_goto_tags = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
					19);
				  PUSH_SPECIAL_WITH_SYMBOL(Goto_tags_in_compilation,Qgoto_tags_in_compilation,goto_tags_in_compilation,
					  18);
				    PUSH_SPECIAL_WITH_SYMBOL(New_goto_tag_counter,Qnew_goto_tag_counter,new_goto_tag_counter,
					    17);
				      if (PUSH_UNWIND_PROTECT(2)) {
					  lexically_visible_code_bodies = Nil;
					  code_body_entries_in_compilation 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Code_body_entries_in_compilation,Qcode_body_entries_in_compilation,code_body_entries_in_compilation,
						  16);
					    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
						    15);
					      if (PUSH_UNWIND_PROTECT(1)) {
						  stack_nodes_to_reclaim = Nil;
						  PUSH_SPECIAL_WITH_SYMBOL(Stack_nodes_to_reclaim,Qstack_nodes_to_reclaim,stack_nodes_to_reclaim,
							  14);
						    if (PUSH_UNWIND_PROTECT(0)) 
								{
							compiler_free_references 
								= Nil;
							collecting_free_references 
								= T;
							PUSH_SPECIAL_WITH_SYMBOL(Collecting_free_references,Qcollecting_free_references,collecting_free_references,
								13);
							  PUSH_SPECIAL_WITH_SYMBOL(Compiler_free_references,Qcompiler_free_references,compiler_free_references,
								  12);
							    if ( 
								    !TRUEP(specific_method_p_qm)) 
									{
								if (EQ(name,
									get_lookup_slot_value_given_default(procedure,
									Qname_or_names_for_frame,
									Nil))) 
									    {
								    suppress_updates_to_name_boxes 
									    = 
									    T;
								    PUSH_SPECIAL_WITH_SYMBOL(Suppress_updates_to_name_boxes,Qsuppress_updates_to_name_boxes,suppress_updates_to_name_boxes,
									    0);
								      change_slot_value(3,
									      procedure,
									      Qname_or_names_for_frame,
									      name);
								    POP_SPECIAL();
								}
								else
								    change_slot_value(3,
									    procedure,
									    Qname_or_names_for_frame,
									    name);
							    }
							    else
								record_free_reference(Qname,
									name);
							    clear_procedure_compilation_frame_flags(Current_computation_frame);
							    result = generate_environment_descriptions(args,
								    return_types,
								    local_vars);
							    MVS_4(result,
								    argument_list_description,
								    base_environment,
								    Returned_values_description,
								    variable_initializations);
							    if (Noting_changes_to_kb_p)
								note_change_to_block_1(procedure,
									Qargument_count);
							    temp = 
								    length(argument_list_description);
							    SVREF(procedure,
								    FIX((SI_Long)23L)) 
								    = temp;
							    change_slot_value(3,
								    procedure,
								    Qargument_list_description,
								    convert_description_list_to_managed_array(1,
								    argument_list_description));
							    change_slot_value(3,
								    procedure,
								    Qreturned_values_description,
								    convert_description_list_to_managed_array(2,
								    Returned_values_description,
								    T));
							    if (specific_method_p_qm) 
									{
								if (argument_list_description) 
									    {
								    temp_3 
									    = 
									    CAR(argument_list_description);
								    first_argument_type_qm 
									    = 
									    getfq_function_no_default(CDR(temp_3),
									    Ktype);
								}
								else
								    first_argument_type_qm 
									    = 
									    Nil;
								first_argument_class_qm 
									= 
									class_type_specification_p(first_argument_type_qm) 
									? 
									M_CAR(M_CDR(first_argument_type_qm)) 
									: Qnil;
								old_method_name_qm 
									= 
									ISVREF(procedure,
									(SI_Long)30L);
								old_method_class_qm 
									= 
									ISVREF(procedure,
									(SI_Long)31L);
								if (first_argument_class_qm) 
									    {
								    if (EQ(name,
									    old_method_name_qm) 
									    && 
									    EQ(first_argument_class_qm,
									    old_method_class_qm)) 
										{
									suppress_updates_to_name_boxes 
										= 
										T;
									PUSH_SPECIAL_WITH_SYMBOL(Suppress_updates_to_name_boxes,Qsuppress_updates_to_name_boxes,suppress_updates_to_name_boxes,
										0);
									  change_slot_value(3,
										  procedure,
										  Qname_or_names_for_frame,
										  make_unique_slot_name_symbol(first_argument_class_qm,
										  name));
									POP_SPECIAL();
								    }
								    else
									change_slot_value(3,
										procedure,
										Qname_or_names_for_frame,
										make_unique_slot_name_symbol(first_argument_class_qm,
										name));
								}
								if (old_method_name_qm) 
									    {
								    if (old_method_class_qm)
									unregister_method_declaration(old_method_name_qm,
										procedure,
										old_method_class_qm);
								    if ( 
									    !EQ(name,
									    old_method_name_qm))
									analyze_compiled_items_for_consistency(old_method_name_qm);
								}
								if ( 
									!TRUEP(argument_list_description)) 
									    {
								    change_slot_value(3,
									    procedure,
									    Qprocedure_method_class,
									    Nil);
								    compiler_error(1,
									    string_constant_8);
								}
								else if ( 
									!TRUEP(first_argument_class_qm)) 
									    {
								    change_slot_value(3,
									    procedure,
									    Qprocedure_method_class,
									    Nil);
								    compiler_error(1,
									    string_constant_9);
								}
								else {
								    if (EQ(first_argument_class_qm,
									    old_method_class_qm)) 
										{
									suppress_updates_to_name_boxes 
										= 
										T;
									PUSH_SPECIAL_WITH_SYMBOL(Suppress_updates_to_name_boxes,Qsuppress_updates_to_name_boxes,suppress_updates_to_name_boxes,
										0);
									  change_slot_value(3,
										  procedure,
										  Qprocedure_method_class,
										  first_argument_class_qm);
									POP_SPECIAL();
								    }
								    else
									change_slot_value(3,
										procedure,
										Qprocedure_method_class,
										first_argument_class_qm);
								    if (EQ(name,
									    old_method_name_qm)) 
										{
									suppress_updates_to_name_boxes 
										= 
										T;
									PUSH_SPECIAL_WITH_SYMBOL(Suppress_updates_to_name_boxes,Qsuppress_updates_to_name_boxes,suppress_updates_to_name_boxes,
										0);
									  change_slot_value(3,
										  procedure,
										  Qprocedure_method_name,
										  name);
									POP_SPECIAL();
								    }
								    else
									change_slot_value(3,
										procedure,
										Qprocedure_method_name,
										name);
								    register_method_declaration(name,
									    procedure,
									    first_argument_class_qm);
								}
							    }
							    if (variable_initializations) 
									{
								temp = 
									last(variable_initializations,
									_);
								temp_1 = 
									phrase_cons(body_statement,
									Nil);
								M_CDR(temp) 
									= 
									temp_1;
								body_statement 
									= 
									phrase_cons(Qbegin_statement,
									variable_initializations);
							    }
							    gensymed_symbol_4 
								    = 
								    CAR(Lexically_visible_code_bodies);
							    temp_3 = 
								    base_environment;
							    gensymed_symbol_4 
								    = 
								    make_compiler_code_body_entry_1(temp_3,
								    gensymed_symbol_4 
								    ? 
								    position(2,
								    gensymed_symbol_4,
								    Code_body_entries_in_compilation) 
								    : Nil);
							    lexically_visible_code_bodies 
								    = 
								    phrase_cons(gensymed_symbol_4,
								    Lexically_visible_code_bodies);
							    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
								    11);
							      Code_body_entries_in_compilation 
								      = 
								      nconc2(Code_body_entries_in_compilation,
								      phrase_cons(gensymed_symbol_4,
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
								      10);
								PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
									9);
								  PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
									  8);
								    lexically_visible_goto_tags 
									    = 
									    Lexically_visible_goto_tags;
								    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
									    7);
								      temp 
									      = 
									      CAR(Code_body_entries_in_compilation);
								      SVREF(temp,
									      FIX((SI_Long)10L)) 
									      = 
									      argument_list_description;
								      temp 
									      = 
									      CAR(Code_body_entries_in_compilation);
								      SVREF(temp,
									      FIX((SI_Long)11L)) 
									      = 
									      local_vars;
								      generated_var_spots_for_base_code_body_return 
									      = 
									      Nil;
								      base_code_body_return_tag 
									      = 
									      generate_new_goto_tag();
								      PUSH_SPECIAL_WITH_SYMBOL(Base_code_body_return_tag,Qbase_code_body_return_tag,base_code_body_return_tag,
									      6);
									PUSH_SPECIAL_WITH_SYMBOL(Generated_var_spots_for_base_code_body_return,Qgenerated_var_spots_for_base_code_body_return,generated_var_spots_for_base_code_body_return,
										5);
									  record_goto_tags(body_statement);
									  compile_procedure_statement(body_statement);
									  if (Returned_values_description) 
										      {
									      if ( 
										      !TRUEP(Return_statement_processed_qm))
										  compiler_warning(1,
											  string_constant_10);
									      current_wide_string_list 
										      = 
										      Qdo_not_use;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
										      4);
										wide_string_bv16 
											= 
											allocate_byte_vector_16(FIX((SI_Long)2048L 
											+ 
											(SI_Long)3L));
										bv16_length 
											= 
											IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
										temp_2 
											= 
											bv16_length 
											- 
											(SI_Long)2L;
										aref_new_value 
											= 
											(SI_Long)2048L 
											& 
											(SI_Long)65535L;
										UBYTE_16_ISASET_1(wide_string_bv16,
											temp_2,
											aref_new_value);
										temp_2 
											= 
											bv16_length 
											- 
											(SI_Long)1L;
										aref_new_value 
											= 
											(SI_Long)57344L 
											| 
											(SI_Long)0L;
										UBYTE_16_ISASET_1(wide_string_bv16,
											temp_2,
											aref_new_value);
										UBYTE_16_ISASET_1(wide_string_bv16,
											(SI_Long)2048L,
											(SI_Long)0L);
										current_wide_string 
											= 
											wide_string_bv16;
										PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
											3);
										  fill_pointer_for_current_wide_string 
											  = 
											  FIX((SI_Long)0L);
										  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
											  2);
										    length_1 
											    = 
											    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
										    total_length_of_current_wide_string 
											    = 
											    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
											    length_1 
											    - 
											    (SI_Long)2L) 
											    + 
											    ((UBYTE_16_ISAREF_1(Current_wide_string,
											    length_1 
											    - 
											    (SI_Long)1L) 
											    & 
											    (SI_Long)8191L) 
											    << 
											    (SI_Long)16L));
										    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
											    1);
										      current_twriting_output_type 
											      = 
											      Qwide_string;
										      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
											      0);
											tformat(2,
												string_constant_11,
												name);
											warning_string 
												= 
												copy_out_current_wide_string();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									      temp_3 
										      = 
										      compile_stack_expression(list_constant,
										      Qsymbol);
									      emit_already_consed_instruction(phrase_list_3(Qsignal_error,
										      temp_3,
										      compile_stack_expression(warning_string,
										      Qtext)));
									      reclaim_text_string(warning_string);
									  }
									  if ( 
										  !TRUEP(Returned_values_description) 
										  || 
										  ISVREF(goto_tag_entry_with_name(Base_code_body_return_tag,
										  Goto_tags_in_compilation),
										  (SI_Long)4L)) 
										      {
									      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
										      Base_code_body_return_tag));
									      description 
										      = 
										      Nil;
									      ab_loop_list_ 
										      = 
										      Returned_values_description;
									      var_spot_name 
										      = 
										      Nil;
									      ab_loop_list__1 
										      = 
										      Generated_var_spots_for_base_code_body_return;
									      var_spot 
										      = 
										      Nil;
									      type 
										      = 
										      Nil;
									      return_expressions 
										      = 
										      Nil;
									      ab_loopvar_ 
										      = 
										      Nil;
									      ab_loopvar__1 
										      = 
										      Nil;
									    next_loop:
									      if ( 
										      !TRUEP(ab_loop_list_))
										  goto end_loop;
									      description 
										      = 
										      M_CAR(ab_loop_list_);
									      ab_loop_list_ 
										      = 
										      M_CDR(ab_loop_list_);
									      if ( 
										      !TRUEP(ab_loop_list__1))
										  goto end_loop;
									      var_spot_name 
										      = 
										      M_CAR(ab_loop_list__1);
									      ab_loop_list__1 
										      = 
										      M_CDR(ab_loop_list__1);
									      var_spot 
										      = 
										      variable_spot_and_description_for_local_name(var_spot_name);
									      type 
										      = 
										      getfq_function_no_default(description,
										      Ktype);
									      ab_loopvar__1 
										      = 
										      phrase_cons(compile_procedure_var_spot(var_spot,
										      type),
										      Nil);
									      if (ab_loopvar_)
										  M_CDR(ab_loopvar_) 
											  = 
											  ab_loopvar__1;
									      else
										  return_expressions 
											  = 
											  ab_loopvar__1;
									      ab_loopvar_ 
										      = 
										      ab_loopvar__1;
									      goto next_loop;
									    end_loop:
									      emit_already_consed_instruction(phrase_list_2(Qreturn_values,
										      return_expressions));
									  }
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							    warn_of_unreferenced_goto_tags();
							    if ( 
								    !TRUEP(Compiler_errors)) 
									{
								ab_loop_repeat_ 
									= 
									IFIX(length(Code_body_entries_in_compilation));
								ab_loopvar_ 
									= Nil;
								ab_loopvar__1 
									= Nil;
								ab_loopvar__2 
									= Nil;
							      next_loop_1:
								if ( 
									!((SI_Long)0L 
									< 
									ab_loop_repeat_))
								    goto end_loop_1;
								ab_loop_repeat_ 
									= 
									ab_loop_repeat_ 
									- 
									(SI_Long)1L;
								ab_loopvar__2 
									= 
									slot_value_cons_1(make_frame(Qcode_body),
									Nil);
								if (ab_loopvar__1)
								    M_CDR(ab_loopvar__1) 
									    = 
									    ab_loopvar__2;
								else
								    ab_loopvar_ 
									    = 
									    ab_loopvar__2;
								ab_loopvar__1 
									= 
									ab_loopvar__2;
								goto next_loop_1;
							      end_loop_1:
								code_body_frames 
									= 
									ab_loopvar_;
								goto end_1;
								code_body_frames 
									= Qnil;
							      end_1:;
								code_body 
									= Nil;
								ab_loop_list_ 
									= 
									code_body_frames;
								PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,
									1);
								  code_body_entry 
									  = 
									  Nil;
								  ab_loop_list__1 
									  = 
									  Code_body_entries_in_compilation;
								  lexically_visible_code_bodies 
									  = 
									  Nil;
								  PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
									  0);
								  next_loop_2:
								    if ( 
									    !TRUEP(ab_loop_list_))
									goto end_loop_2;
								    Code_body 
									    = 
									    M_CAR(ab_loop_list_);
								    ab_loop_list_ 
									    = 
									    M_CDR(ab_loop_list_);
								    if ( 
									    !TRUEP(ab_loop_list__1))
									goto end_loop_2;
								    code_body_entry 
									    = 
									    M_CAR(ab_loop_list__1);
								    ab_loop_list__1 
									    = 
									    M_CDR(ab_loop_list__1);
								    Lexically_visible_code_bodies 
									    = 
									    generate_list_of_lexically_visible_code_bodies(code_body_entry);
								    temp = 
									    Code_body;
								    SVREF(code_body_entry,
									    FIX((SI_Long)6L)) 
									    = 
									    temp;
								    temp = 
									    expand_jump_targets(nreverse(ISVREF(code_body_entry,
									    (SI_Long)1L)));
								    SVREF(code_body_entry,
									    FIX((SI_Long)8L)) 
									    = 
									    temp;
								    if ( 
									    !TRUEP(Compiler_errors)) 
										{
									temp 
										= 
										optimize_procedure_instructions(ISVREF(code_body_entry,
										(SI_Long)8L),
										code_body_entry);
									SVREF(code_body_entry,
										FIX((SI_Long)8L)) 
										= 
										temp;
								    }
								    temp_4 
									    = 
									    ISVREF(code_body_entry,
									    (SI_Long)3L);
								    return_index 
									    = 
									    (SI_Long)1L;
								    ab_loop_bind_ 
									    = 
									    IFIX(ISVREF(code_body_entry,
									    (SI_Long)2L));
								    ab_loopvar_ 
									    = 
									    Nil;
								    ab_loopvar__1 
									    = 
									    Nil;
								    ab_loopvar__2 
									    = 
									    Nil;
								  next_loop_3:
								    if (return_index 
									    > 
									    ab_loop_bind_)
									goto end_loop_3;
								    ab_loopvar__2 
									    = 
									    phrase_cons(phrase_list_3(Nil,
									    Kreturn_value,
									    FIX(return_index)),
									    Nil);
								    if (ab_loopvar__1)
									M_CDR(ab_loopvar__1) 
										= 
										ab_loopvar__2;
								    else
									ab_loopvar_ 
										= 
										ab_loopvar__2;
								    ab_loopvar__1 
									    = 
									    ab_loopvar__2;
								    return_index 
									    = 
									    return_index 
									    + 
									    (SI_Long)1L;
								    goto next_loop_3;
								  end_loop_3:
								    temp_3 
									    = 
									    ab_loopvar_;
								    goto end_2;
								    temp_3 
									    = 
									    Qnil;
								  end_2:;
								    temp = 
									    nconc2(temp_4,
									    temp_3);
								    SVREF(code_body_entry,
									    FIX((SI_Long)3L)) 
									    = 
									    temp;
								    goto next_loop_2;
								  end_loop_2:;
								  POP_SPECIAL();
								POP_SPECIAL();
								base_code_body_entry 
									= 
									FIRST(Code_body_entries_in_compilation);
								code_body_entry 
									= Nil;
								ab_loop_list_ 
									= 
									Code_body_entries_in_compilation;
								lexically_visible_code_bodies 
									= Nil;
								PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
									1);
								  byte_code_stream 
									  = 
									  make_byte_code_stream_1();
								  ab_loop_iter_flag_ 
									  = T;
								next_loop_4:
								  if ( 
									  !TRUEP(ab_loop_list_))
								      goto end_loop_4;
								  code_body_entry 
									  = 
									  M_CAR(ab_loop_list_);
								  ab_loop_list_ 
									  = 
									  M_CDR(ab_loop_list_);
								  Lexically_visible_code_bodies 
									  = 
									  generate_list_of_lexically_visible_code_bodies(code_body_entry);
								  if ( 
									  !TRUEP(ab_loop_iter_flag_))
								      byte_code_stream 
									      = 
									      make_byte_code_stream_given_base_stream(ISVREF(base_code_body_entry,
									      (SI_Long)9L));
								  current_return_values_position 
									  = 
									  FIXNUM_MINUS(length(ISVREF(code_body_entry,
									  (SI_Long)3L)),
									  ISVREF(code_body_entry,
									  (SI_Long)2L));
								  PUSH_SPECIAL_WITH_SYMBOL(Current_return_values_position,Qcurrent_return_values_position,current_return_values_position,
									  0);
								    SVREF(code_body_entry,
									    FIX((SI_Long)9L)) 
									    = 
									    byte_code_stream;
								    if ( 
									    !TRUEP(Compiler_errors))
									emit_byte_code_vector_for_procedure(byte_code_stream,
										ISVREF(code_body_entry,
										(SI_Long)8L));
								  POP_SPECIAL();
								  ab_loop_iter_flag_ 
									  = 
									  Nil;
								  goto next_loop_4;
								end_loop_4:;
								POP_SPECIAL();
								code_body 
									= Nil;
								ab_loop_list_ 
									= 
									code_body_frames;
								PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,
									1);
								  code_body_entry 
									  = 
									  Nil;
								  ab_loop_list__1 
									  = 
									  Code_body_entries_in_compilation;
								  byte_code_stream 
									  = 
									  Nil;
								  maximum_received_values 
									  = 
									  Nil;
								  byte_code_vector 
									  = 
									  Nil;
								  byte_codes_count 
									  = 
									  (SI_Long)0L;
								  byte_code_constants 
									  = 
									  Nil;
								  activity_position 
									  = 
									  Nil;
								next_loop_5:
								  if ( 
									  !TRUEP(ab_loop_list_))
								      goto end_loop_5;
								  Code_body 
									  = 
									  M_CAR(ab_loop_list_);
								  ab_loop_list_ 
									  = 
									  M_CDR(ab_loop_list_);
								  if ( 
									  !TRUEP(ab_loop_list__1))
								      goto end_loop_5;
								  code_body_entry 
									  = 
									  M_CAR(ab_loop_list__1);
								  ab_loop_list__1 
									  = 
									  M_CDR(ab_loop_list__1);
								  byte_code_stream 
									  = 
									  ISVREF(code_body_entry,
									  (SI_Long)9L);
								  maximum_received_values 
									  = 
									  ISVREF(code_body_entry,
									  (SI_Long)2L);
								  byte_code_vector 
									  = 
									  Nil;
								  byte_codes_count 
									  = 
									  (SI_Long)0L;
								  byte_code_constants 
									  = 
									  Nil;
								  activity_position 
									  = 
									  Nil;
								  if ( 
									  !TRUEP(Compiler_errors)) 
									      {
								      result = resolve_procedure_byte_code_addresses(2,
									      byte_code_stream,
									      code_body_entry);
								      MVS_2(result,
									      byte_code_vector,
									      temp_3);
								      byte_codes_count 
									      = 
									      IFIX(temp_3);
								      activity_position 
									      = 
									      ISVREF(byte_code_stream,
									      (SI_Long)7L);
								  }
								  if ( 
									  !TRUEP(Compiler_errors))
								      byte_code_constants 
									      = 
									      make_procedure_byte_code_constants(byte_code_stream);
								  reclaim_byte_code_stream_1(byte_code_stream);
								  if ( 
									  !TRUEP(Compiler_errors)) 
									      {
								      current_block_of_dependent_frame 
									      = 
									      Qdependent_frame_has_no_owner;
								      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
									      0);
									environment 
										= 
										ISVREF(code_body_entry,
										(SI_Long)3L);
									environment_length 
										= 
										length(environment);
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									SVREF(temp,
										FIX((SI_Long)2L)) 
										= 
										procedure;
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									temp_1 
										= 
										FIXNUM_MINUS(environment_length,
										maximum_received_values);
									SVREF(temp,
										FIX((SI_Long)4L)) 
										= 
										temp_1;
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									SVREF(temp,
										FIX((SI_Long)5L)) 
										= 
										maximum_received_values;
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									SVREF(temp,
										FIX((SI_Long)6L)) 
										= 
										environment_length;
									temp_3 
										= 
										Code_body;
									change_slot_value(3,
										temp_3,
										Qenvironment_description,
										convert_description_list_to_managed_array(1,
										environment));
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									temp_1 
										= 
										ISVREF(code_body_entry,
										(SI_Long)4L);
									SVREF(temp,
										FIX((SI_Long)3L)) 
										= 
										temp_1;
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									temp_5 
										= 
										FIX(byte_codes_count);
									temp_4 
										= 
										byte_code_vector;
									temp_3 
										= 
										byte_code_constants;
									temp_1 
										= 
										make_byte_code_body_1(temp_5,
										temp_4,
										temp_3,
										convert_description_list_to_managed_array(1,
										environment),
										Nil);
									SVREF(temp,
										FIX((SI_Long)8L)) 
										= 
										temp_1;
									temp 
										= 
										ISVREF(Code_body,
										(SI_Long)8L);
									SVREF(temp,
										FIX((SI_Long)5L)) 
										= 
										activity_position;
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									temp_1 
										= 
										copy_for_slot_value(ISVREF(code_body_entry,
										(SI_Long)7L));
									SVREF(temp,
										FIX((SI_Long)10L)) 
										= 
										temp_1;
								      POP_SPECIAL();
								  }
								  goto next_loop_5;
								end_loop_5:;
								POP_SPECIAL();
								current_block_of_dependent_frame 
									= 
									Qdependent_frame_has_no_owner;
								PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
									1);
								  code_body 
									  = 
									  Nil;
								  ab_loop_list_ 
									  = 
									  code_body_frames;
								  PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,
									  0);
								    code_body_entry 
									    = 
									    Nil;
								    ab_loop_list__1 
									    = 
									    Code_body_entries_in_compilation;
								  next_loop_6:
								    if ( 
									    !TRUEP(ab_loop_list_))
									goto end_loop_6;
								    Code_body 
									    = 
									    M_CAR(ab_loop_list_);
								    ab_loop_list_ 
									    = 
									    M_CDR(ab_loop_list_);
								    if ( 
									    !TRUEP(ab_loop_list__1))
									goto end_loop_6;
								    code_body_entry 
									    = 
									    M_CAR(ab_loop_list__1);
								    ab_loop_list__1 
									    = 
									    M_CDR(ab_loop_list__1);
								    if (ISVREF(code_body_entry,
									    (SI_Long)5L)) 
										{
									if (Noting_changes_to_kb_p)
									    note_change_to_dependent_frame_1();
									temp 
										= 
										Code_body;
									temp_1 
										= 
										list_to_managed_array(ISVREF(code_body_entry,
										(SI_Long)5L));
									SVREF(temp,
										FIX((SI_Long)9L)) 
										= 
										temp_1;
								    }
								    goto next_loop_6;
								  end_loop_6:;
								  POP_SPECIAL();
								POP_SPECIAL();
							    }
							    if (Compiler_errors) 
									{
								if (code_body_frames) 
									    {
								    code_body 
									    = 
									    Nil;
								    ab_loop_list_ 
									    = 
									    code_body_frames;
								    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,
									    0);
								    next_loop_7:
								      if ( 
									      !TRUEP(ab_loop_list_))
									  goto end_loop_7;
								      Code_body 
									      = 
									      M_CAR(ab_loop_list_);
								      ab_loop_list_ 
									      = 
									      M_CDR(ab_loop_list_);
								      delete_frame(Code_body);
								      goto next_loop_7;
								    end_loop_7:;
								    POP_SPECIAL();
								    reclaim_slot_value_list_1(code_body_frames);
								    code_body_frames 
									    = 
									    Nil;
								}
								if (Compiler_free_references) 
									    {
								    code_body_frames 
									    = 
									    slot_value_cons_1(make_frame(Qcode_body),
									    Nil);
								    current_block_of_dependent_frame 
									    = 
									    Qdependent_frame_has_no_owner;
								    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
									    0);
								      gensymed_symbol_4 
									      = 
									      CAR(code_body_frames);
								      if (Noting_changes_to_kb_p)
									  note_change_to_dependent_frame_1();
								      temp 
									      = 
									      make_byte_code_body_1(FIX((SI_Long)0L),
									      allocate_byte_vector(FIX((SI_Long)4L)),
									      Nil,
									      Nil,
									      Nil);
								      SVREF(gensymed_symbol_4,
									      FIX((SI_Long)8L)) 
									      = 
									      temp;
								    POP_SPECIAL();
								}
							    }
							    first_code_body_qm 
								    = 
								    CAR(code_body_frames);
							    byte_code_body_zero_qm 
								    = 
								    first_code_body_qm 
								    ? 
								    ISVREF(first_code_body_qm,
								    (SI_Long)8L) 
								    : Nil;
							    if (byte_code_body_zero_qm) 
									{
								install_free_references_in_byte_code_body(byte_code_body_zero_qm,
									Compiler_free_references);
								Compiler_free_references 
									= Nil;
							    }
							    change_slot_value(3,
								    procedure,
								    Procedure_code_bodies_slot_name,
								    code_body_frames);
							    if (Compiler_errors) 
									{
								update_frame_status(procedure,
									Qbad,
									Nil);
								if (Noting_changes_to_kb_p)
								    note_change_to_block_1(procedure,
									    Qargument_count);
								ISVREF(procedure,
									(SI_Long)23L) 
									= 
									FIX((SI_Long)0L);
								change_slot_value(3,
									procedure,
									Qargument_list_description,
									Nil);
								change_slot_value(3,
									procedure,
									Qreturned_values_description,
									Nil);
								remove_md5_identifier(procedure);
								change_slot_value(3,
									procedure,
									Qparse_results_qm,
									Nil);
								reclaim_slot_value(incoming_parse_result);
							    }
							    else {
								if (inlineable_qm) 
									    {
								    add_md5_identifier(procedure);
								    change_slot_value(3,
									    procedure,
									    Qparse_results_qm,
									    incoming_parse_result);
								}
								else {
								    reclaim_slot_value(incoming_parse_result);
								    remove_md5_identifier(procedure);
								    change_slot_value(3,
									    procedure,
									    Qparse_results_qm,
									    Nil);
								}
								update_frame_status(procedure,
									Nil,
									Nil);
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
					      ab_loop_list_ = 
						      Code_body_entries_in_compilation;
					    next_loop_8:
					      if ( !TRUEP(ab_loop_list_))
						  goto end_loop_8;
					      code_body_entry = 
						      M_CAR(ab_loop_list_);
					      ab_loop_list_ = 
						      M_CDR(ab_loop_list_);
					      reclaim_compiler_code_body_entry_1(code_body_entry);
					      goto next_loop_8;
					    end_loop_8:;
					      CONTINUE_UNWINDING(1);
					    POP_SPECIAL();
					  POP_SPECIAL();
				      }
				      POP_UNWIND_PROTECT(2);
				      tag = Nil;
				      ab_loop_list_ = Goto_tags_in_compilation;
				    next_loop_9:
				      if ( !TRUEP(ab_loop_list_))
					  goto end_loop_9;
				      tag = M_CAR(ab_loop_list_);
				      ab_loop_list_ = M_CDR(ab_loop_list_);
				      reclaim_goto_tag_entry_1(tag);
				      goto next_loop_9;
				    end_loop_9:;
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
			if (gensymed_symbol) {
			    temp = Current_edit_state;
			    SVREF(temp,FIX((SI_Long)90L)) = Nil;
			}
			reclaim_edit_state_1(Current_edit_state);
		      POP_SPECIAL();
		      temp_6 = 
			      TRUEP(Suppress_updating_of_slot_value_representations_qm);
		      if (temp_6);
		      else if (M_CDR(Stack_of_slot_value_changes)) {
			  frame_and_slot_or_atom = Nil;
			  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
			  ab_loop_it_ = Nil;
			next_loop_10:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_10;
			  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if (ATOM(frame_and_slot_or_atom))
			      goto end_loop_10;
			  temp_6 = EQ(slot_description_1,
				  M_CDR(frame_and_slot_or_atom));
			  if (temp_6);
			  else {
			      temp_3 = M_CDR(frame_and_slot_or_atom);
			      temp_6 = CONSP(temp_3) ? 
				      EQ(slot_description_1,
				      SECOND(frame_and_slot_or_atom)) && 
				      EQ(Nil,
				      THIRD(frame_and_slot_or_atom)) && 
				      EQ(Nil,
				      CDDDR(frame_and_slot_or_atom)) : 
				      TRUEP(Nil);
			  }
			  ab_loop_it_ = temp_6 ? (EQ(procedure,
				  M_CAR(frame_and_slot_or_atom)) ? T : 
				  Nil) : Nil;
			  if (ab_loop_it_) {
			      temp_6 = TRUEP(ab_loop_it_);
			      goto end_3;
			  }
			  goto next_loop_10;
			end_loop_10:
			  temp_6 = TRUEP(Qnil);
			end_3:;
		      }
		      else
			  temp_6 = TRUEP(Nil);
		      if ( !temp_6)
			  update_all_representations_of_slot(procedure,
				  slot_description_1,Nil,Nil);
		      if (ISVREF(slot_description_1,(SI_Long)14L))
			  update_frame_name_references(procedure);
		      stack_change_pop_store = Nil;
		      cons_1 = Stack_of_slot_value_changes;
		      if (cons_1) {
			  stack_change_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qstack_change);
			  if (ISVREF(Available_stack_change_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_stack_change_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp) = cons_1;
			      temp = Available_stack_change_conses_tail_vector;
			      temp_1 = Current_thread_index;
			      SVREF(temp,temp_1) = cons_1;
			  }
			  else {
			      temp = Available_stack_change_conses_vector;
			      temp_1 = Current_thread_index;
			      SVREF(temp,temp_1) = cons_1;
			      temp = Available_stack_change_conses_tail_vector;
			      temp_1 = Current_thread_index;
			      SVREF(temp,temp_1) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      Stack_of_slot_value_changes = next_cons;
		      reclaim_stack_change_tree_1(stack_change_pop_store);
		      if (Stack_of_slot_value_changes) {
			  temp_3 = M_CAR(Stack_of_slot_value_changes);
			  temp_6 = ATOM(temp_3);
		      }
		      else
			  temp_6 = TRUEP(Nil);
		      if (temp_6 ?  
			      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			      : TRUEP(Nil))
			  do_deferred_updates_to_representations_in_tables();
		    POP_SPECIAL();
		    result_1 = analyze_compiled_items_for_consistency(name);
		    if ( !TRUEP(current_flag_state_qm)) {
			temp_2 = IFIX(ISVREF(procedure,(SI_Long)5L)) &  
				~(SI_Long)16777216L;
			ISVREF(procedure,(SI_Long)5L) = FIX(temp_2);
			gensymed_symbol = 
				ISVREF(ISVREF(ISVREF(ISVREF(procedure,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
				(SI_Long)1L);
			gensymed_symbol_4 = procedure;
			gensymed_symbol_5 = T;
			gensymed_symbol_6 = Nil;
			inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
				gensymed_symbol_5,gensymed_symbol_6);
		    }
		    temp_6 = 
			    TRUEP(Suppress_updating_of_slot_value_representations_qm);
		    if (temp_6);
		    else if (M_CDR(Stack_of_slot_value_changes)) {
			frame_and_slot_or_atom = Nil;
			ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
			ab_loop_it_ = Nil;
		      next_loop_11:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_11;
			frame_and_slot_or_atom = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if (ATOM(frame_and_slot_or_atom))
			    goto end_loop_11;
			temp_6 = EQ(slot_description,
				M_CDR(frame_and_slot_or_atom));
			if (temp_6);
			else {
			    temp_3 = M_CDR(frame_and_slot_or_atom);
			    temp_6 = CONSP(temp_3) ? EQ(slot_description,
				    SECOND(frame_and_slot_or_atom)) && 
				    EQ(Nil,THIRD(frame_and_slot_or_atom)) 
				    && EQ(Nil,
				    CDDDR(frame_and_slot_or_atom)) : 
				    TRUEP(Nil);
			}
			ab_loop_it_ = temp_6 ? (EQ(procedure,
				M_CAR(frame_and_slot_or_atom)) ? T : Nil) :
				 Nil;
			if (ab_loop_it_) {
			    temp_6 = TRUEP(ab_loop_it_);
			    goto end_4;
			}
			goto next_loop_11;
		      end_loop_11:
			temp_6 = TRUEP(Qnil);
		      end_4:;
		    }
		    else
			temp_6 = TRUEP(Nil);
		    if ( !temp_6)
			update_all_representations_of_slot(procedure,
				slot_description,Nil,Nil);
		    if (ISVREF(slot_description,(SI_Long)14L))
			update_frame_name_references(procedure);
		    stack_change_pop_store = Nil;
		    cons_1 = Stack_of_slot_value_changes;
		    if (cons_1) {
			stack_change_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qstack_change);
			if (ISVREF(Available_stack_change_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_stack_change_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_stack_change_conses_tail_vector;
			    temp_1 = Current_thread_index;
			    SVREF(temp,temp_1) = cons_1;
			}
			else {
			    temp = Available_stack_change_conses_vector;
			    temp_1 = Current_thread_index;
			    SVREF(temp,temp_1) = cons_1;
			    temp = Available_stack_change_conses_tail_vector;
			    temp_1 = Current_thread_index;
			    SVREF(temp,temp_1) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Stack_of_slot_value_changes = next_cons;
		    reclaim_stack_change_tree_1(stack_change_pop_store);
		    if (Stack_of_slot_value_changes) {
			temp_3 = M_CAR(Stack_of_slot_value_changes);
			temp_6 = ATOM(temp_3);
		    }
		    else
			temp_6 = TRUEP(Nil);
		    if (temp_6 ?  
			    !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			    : TRUEP(Nil))
			do_deferred_updates_to_representations_in_tables();
		  POP_SPECIAL();
		  SAVE_VALUES(VALUES_1(result_1));
		  clear_inlining_data();
		  result = RESTORE_VALUES();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qcar_eq;             /* car-eq */

static Object string_constant_12;  /* "<returned value>" */

static Object Qassignment_statement;  /* assignment-statement */

/* GENERATE-ENVIRONMENT-DESCRIPTIONS */
Object generate_environment_descriptions(args,return_types,local_vars)
    Object args, return_types, local_vars;
{
    Object argument_list_description, environment_description;
    Object returned_values_description, variable_initializations, arg_name;
    Object type, ab_loop_list_, remaining_args, ab_loop_iter_flag_;
    Object ab_loop_desetq_, temp, new_description, local_name;
    Object initialization_qm, remaining_local_vars, temp_1, temp_2, temp_3;
    SI_Long return_value_count;
    Declare_special(1);
    Object result;

    x_note_fn_call(161,7);
    argument_list_description = Nil;
    environment_description = Nil;
    returned_values_description = Nil;
    variable_initializations = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Returned_values_description,Qreturned_values_description,returned_values_description,
	    0);
      arg_name = Nil;
      type = Nil;
      ab_loop_list_ = args;
      remaining_args = CDR(args);
      ab_loop_iter_flag_ = T;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      arg_name = CAR(ab_loop_desetq_);
      temp = CDR(ab_loop_desetq_);
      type = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  remaining_args = CDR(remaining_args);
      if (member(4,arg_name,remaining_args,Ktest,SYMBOL_FUNCTION(Qcar_eq)))
	  procedure_compiler_duplicate_local_name_error(arg_name);
      type = convert_procedure_type_if_necessary(2,type,arg_name);
      new_description = phrase_list_3(arg_name,Ktype,type);
      argument_list_description = phrase_cons(new_description,
	      argument_list_description);
      environment_description = phrase_cons(new_description,
	      environment_description);
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:;
      type = Nil;
      ab_loop_list_ = return_types;
      return_value_count = (SI_Long)1L;
      ab_loop_iter_flag_ = T;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      type = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  return_value_count = return_value_count + (SI_Long)1L;
      type = convert_procedure_type_if_necessary(2,type,string_constant_12);
      Returned_values_description = phrase_cons(phrase_list_2(Ktype,type),
	      Returned_values_description);
      ab_loop_iter_flag_ = Nil;
      goto next_loop_1;
    end_loop_1:;
      local_name = Nil;
      type = Nil;
      initialization_qm = Nil;
      ab_loop_list_ = local_vars;
      remaining_local_vars = CDR(local_vars);
      ab_loop_iter_flag_ = T;
      ab_loop_desetq_ = Nil;
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      local_name = CAR(ab_loop_desetq_);
      temp = CDR(ab_loop_desetq_);
      type = CAR(temp);
      temp = CDR(ab_loop_desetq_);
      temp = CDR(temp);
      initialization_qm = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  remaining_local_vars = CDR(remaining_local_vars);
      if (member(4,local_name,remaining_local_vars,Ktest,
	      SYMBOL_FUNCTION(Qcar_eq)) || member(4,local_name,args,Ktest,
	      SYMBOL_FUNCTION(Qcar_eq)))
	  procedure_compiler_duplicate_local_name_error(local_name);
      type = convert_procedure_type_if_necessary(2,type,local_name);
      environment_description = phrase_cons(phrase_list_3(local_name,Ktype,
	      type),environment_description);
      if (initialization_qm)
	  variable_initializations = 
		  phrase_cons(phrase_list_3(Qassignment_statement,
		  local_name,initialization_qm),variable_initializations);
      ab_loop_iter_flag_ = Nil;
      goto next_loop_2;
    end_loop_2:;
      temp_1 = nreverse(argument_list_description);
      temp_2 = nreverse(environment_description);
      temp_3 = nreverse(Returned_values_description);
      temp = nreverse(variable_initializations);
      result = VALUES_4(temp_1,temp_2,temp_3,temp);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(New_descriptions, Qnew_descriptions);

/* PRINT-DESCRIPTION */
Object print_description(vector_1)
    Object vector_1;
{
    Object i, val, desc, return_value_qm, temp;
    SI_Long index_1;

    x_note_fn_call(161,8);
    index_1 = (SI_Long)0L;
    i = FIX((SI_Long)0L);
    val = Nil;
    desc = Nil;
    return_value_qm = Nil;
  next_loop:
    temp = length(vector_1);
    if ( !NUM_LT(i,temp))
	goto end_loop;
    val = ISVREF(vector_1,IFIX(i));
    i = FIXNUM_ADD1(i);
    desc = ISVREF(vector_1,IFIX(i));
    i = FIXNUM_ADD1(i);
    if (CONSP(desc) && EQ(CAR(desc),Kreturn_value)) {
	return_value_qm = T;
	desc = CDR(desc);
    }
    format((SI_Long)6L,T,"~% [~a] ~a,~a return\? ~a",FIX(index_1),val,desc,
	    return_value_qm);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qcell_array;         /* cell-array */

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

static Object Qrule_byte_code_body;  /* rule-byte-code-body */

static Object Qfunction_definition_byte_code_body;  /* function-definition-byte-code-body */

static Object Qsimulation_subtable_byte_code_body;  /* simulation-subtable-byte-code-body */

static Object Qsimulation_subtable_initial_value_byte_code_body;  /* simulation-subtable-initial-value-byte-code-body */

static Object Qgeneric_simulation_formula_byte_code_body;  /* generic-simulation-formula-byte-code-body */

static Object Qgeneric_simulation_initial_value_byte_code_body;  /* generic-simulation-initial-value-byte-code-body */

static Object Qimage_definition;   /* image-definition */

static Object Qimage_definition_saveable_image_info;  /* image-definition-saveable-image-info */

/* CONVERT-FRAME-INTERNALS-TO-VECTORS-AS-NECESSARY */
Object convert_frame_internals_to_vectors_as_necessary()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object g2_cell_array_qm, g2_cell_array_managed_array_qm;
    Object g2_expression_cell_qm, byte_code_body_, old_value, temp_1;
    Object gensymed_symbol, sub_class_bit_vector, code_body, ab_loop_list_;
    Object svref_new_value, temp_2, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);

    x_note_fn_call(161,9);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,2);
      if ( !(IFIX(Kb_flags) >= (SI_Long)254L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    g2_cell_array_qm = Nil;
	    ab_loopvar_ = collect_subclasses(Qblock);
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
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    g2_cell_array_qm = get_lookup_slot_value_given_default(block,
		    Qcell_array,Nil);
	    if (g2_cell_array_qm) {
		g2_cell_array_managed_array_qm = 
			g2_cell_array_managed_array_function(g2_cell_array_qm);
		g2_expression_cell_qm = g2_cell_array_managed_array_qm ? 
			(FIXNUM_LE(ISVREF(g2_cell_array_managed_array_qm,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(g2_cell_array_managed_array_qm,(SI_Long)0L 
			+ IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(g2_cell_array_managed_array_qm,
			(SI_Long)2L),(SI_Long)0L)) : Nil;
		if (g2_expression_cell_qm) {
		    byte_code_body_ = 
			    g2_expression_cell_byte_code_body_function(g2_expression_cell_qm);
		    if (SIMPLE_VECTOR_P(byte_code_body_) && 
			    EQ(ISVREF(byte_code_body_,(SI_Long)0L),
			    Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
				{
			old_value = ISVREF(byte_code_body_,(SI_Long)4L);
			if (CONSP(old_value)) {
			    temp_1 = 
				    convert_description_list_to_managed_array(1,
				    old_value);
			    SVREF(byte_code_body_,FIX((SI_Long)4L)) = temp_1;
			    reclaim_slot_value(old_value);
			}
		    }
		}
	    }
	    gensymed_symbol = ISVREF(block,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	    if (temp) {
		old_value = ISVREF(block,(SI_Long)24L);
		if (CONSP(old_value)) {
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(block,
				Qargument_list_description);
		    temp_1 = convert_description_list_to_managed_array(1,
			    old_value);
		    SVREF(block,FIX((SI_Long)24L)) = temp_1;
		    reclaim_slot_value(old_value);
		}
		old_value = ISVREF(block,(SI_Long)25L);
		if (CONSP(old_value)) {
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(block,
				Qreturned_values_description);
		    temp_1 = convert_description_list_to_managed_array(1,
			    old_value);
		    SVREF(block,FIX((SI_Long)25L)) = temp_1;
		    reclaim_slot_value(old_value);
		}
		code_body = Nil;
		ab_loop_list_ = get_slot_value_function(block,
			Procedure_code_bodies_slot_name,Nil);
		PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  Code_body = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  old_value = ISVREF(Code_body,(SI_Long)7L);
		  if (CONSP(old_value)) {
		      if (Noting_changes_to_kb_p)
			  note_change_to_dependent_frame_1();
		      temp_1 = Code_body;
		      svref_new_value = 
			      convert_description_list_to_managed_array(1,
			      old_value);
		      SVREF(temp_1,FIX((SI_Long)7L)) = svref_new_value;
		      reclaim_slot_value(old_value);
		  }
		  goto next_loop_2;
		end_loop_2:;
		POP_SPECIAL();
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Remote_procedure_declaration_class_description,
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    old_value = 
			    remote_procedure_returned_values_description_function(block);
		    if (CONSP(old_value)) {
			temp_2 = block;
			set_remote_procedure_returned_values_description_function(temp_2,
				convert_description_list_to_managed_array(1,
				old_value));
			reclaim_slot_value(old_value);
		    }
		    old_value = 
			    remote_procedure_argument_description_function(block);
		    if (CONSP(old_value)) {
			temp_2 = block;
			set_remote_procedure_argument_description_function(temp_2,
				convert_description_list_to_managed_array(1,
				old_value));
			reclaim_slot_value(old_value);
		    }
		}
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			byte_code_body_ = get_slot_value_function(block,
				Qrule_byte_code_body,Nil);
			if (SIMPLE_VECTOR_P(byte_code_body_) && 
				EQ(ISVREF(byte_code_body_,(SI_Long)0L),
				Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
				    {
			    old_value = ISVREF(byte_code_body_,(SI_Long)4L);
			    if (CONSP(old_value)) {
				temp_1 = 
					convert_description_list_to_managed_array(1,
					old_value);
				SVREF(byte_code_body_,FIX((SI_Long)4L)) = 
					temp_1;
				reclaim_slot_value(old_value);
			    }
			}
		    }
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Function_definition_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    byte_code_body_ = 
				    get_slot_value_function(block,
				    Qfunction_definition_byte_code_body,Nil);
			    if (SIMPLE_VECTOR_P(byte_code_body_) && 
				    EQ(ISVREF(byte_code_body_,(SI_Long)0L),
				    Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
					{
				old_value = ISVREF(byte_code_body_,
					(SI_Long)4L);
				if (CONSP(old_value)) {
				    temp_1 = 
					    convert_description_list_to_managed_array(1,
					    old_value);
				    SVREF(byte_code_body_,
					    FIX((SI_Long)4L)) = temp_1;
				    reclaim_slot_value(old_value);
				}
			    }
			}
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Simulation_subtable_class_description,
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
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				byte_code_body_ = 
					get_slot_value_function(block,
					Qsimulation_subtable_byte_code_body,
					Nil);
				if (SIMPLE_VECTOR_P(byte_code_body_) && 
					EQ(ISVREF(byte_code_body_,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
					    {
				    old_value = ISVREF(byte_code_body_,
					    (SI_Long)4L);
				    if (CONSP(old_value)) {
					temp_1 = 
						convert_description_list_to_managed_array(1,
						old_value);
					SVREF(byte_code_body_,
						FIX((SI_Long)4L)) = temp_1;
					reclaim_slot_value(old_value);
				    }
				}
				byte_code_body_ = 
					get_slot_value_function(block,
					Qsimulation_subtable_initial_value_byte_code_body,
					Nil);
				if (SIMPLE_VECTOR_P(byte_code_body_) && 
					EQ(ISVREF(byte_code_body_,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
					    {
				    old_value = ISVREF(byte_code_body_,
					    (SI_Long)4L);
				    if (CONSP(old_value)) {
					temp_1 = 
						convert_description_list_to_managed_array(1,
						old_value);
					SVREF(byte_code_body_,
						FIX((SI_Long)4L)) = temp_1;
					reclaim_slot_value(old_value);
				    }
				}
			    }
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Generic_simulation_formula_class_description,
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
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
				if (temp) {
				    byte_code_body_ = 
					    get_slot_value_function(block,
					    Qgeneric_simulation_formula_byte_code_body,
					    Nil);
				    if (SIMPLE_VECTOR_P(byte_code_body_) 
					    && EQ(ISVREF(byte_code_body_,
					    (SI_Long)0L),
					    Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
						{
					old_value = ISVREF(byte_code_body_,
						(SI_Long)4L);
					if (CONSP(old_value)) {
					    temp_1 = 
						    convert_description_list_to_managed_array(1,
						    old_value);
					    SVREF(byte_code_body_,
						    FIX((SI_Long)4L)) = temp_1;
					    reclaim_slot_value(old_value);
					}
				    }
				    byte_code_body_ = 
					    get_slot_value_function(block,
					    Qgeneric_simulation_initial_value_byte_code_body,
					    Nil);
				    if (SIMPLE_VECTOR_P(byte_code_body_) 
					    && EQ(ISVREF(byte_code_body_,
					    (SI_Long)0L),
					    Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
						{
					old_value = ISVREF(byte_code_body_,
						(SI_Long)4L);
					if (CONSP(old_value)) {
					    temp_1 = 
						    convert_description_list_to_managed_array(1,
						    old_value);
					    SVREF(byte_code_body_,
						    FIX((SI_Long)4L)) = temp_1;
					    reclaim_slot_value(old_value);
					}
				    }
				}
				else {
				    gensymed_symbol_4 = 
					    lookup_global_or_kb_specific_property_value(Qimage_definition,
					    Class_description_gkbprop);
				    if (gensymed_symbol_4) {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(gensymed_symbol_4,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
					if (sub_class_vector_index < 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						    {
					    gensymed_symbol_1 = 
						    UBYTE_8_ISAREF_1(sub_class_bit_vector,
						    sub_class_vector_index);
					    gensymed_symbol_2 = (SI_Long)1L;
					    gensymed_symbol_3 = 
						    superior_class_bit_number 
						    & (SI_Long)7L;
					    gensymed_symbol_2 = 
						    gensymed_symbol_2 << 
						    gensymed_symbol_3;
					    gensymed_symbol_1 = 
						    gensymed_symbol_1 & 
						    gensymed_symbol_2;
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp) {
					byte_code_body_ = 
						get_slot_value_function(block,
						Qimage_definition_saveable_image_info,
						Nil);
					if (SIMPLE_VECTOR_P(byte_code_body_) 
						&& 
						EQ(ISVREF(byte_code_body_,
						(SI_Long)0L),
						Qg2_defstruct_structure_name_byte_code_body_g2_struct)) 
						    {
					    old_value = 
						    ISVREF(byte_code_body_,
						    (SI_Long)4L);
					    if (CONSP(old_value)) {
						temp_1 = 
							convert_description_list_to_managed_array(1,
							old_value);
						SVREF(byte_code_body_,
							FIX((SI_Long)4L)) 
							= temp_1;
						reclaim_slot_value(old_value);
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Kgeneral_description;  /* :general-description */

/* CONVERT-DESCRIPTION-LIST-TO-MANAGED-ARRAY */
Object convert_description_list_to_managed_array varargs_1(int, n)
{
    Object description_as_list;
    Object static_p, description_vector, description, ab_loop_list_, id;
    Object keyword, value, description_length, index_1, description_old_value;
    Object temp, temp_1, svref_new_value;
    SI_Long vector_length, svref_arg_2;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(161,10);
    INIT_ARGS_nonrelocating();
    description_as_list = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    static_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (description_as_list) {
	vector_length = (SI_Long)2L * IFIX(length(description_as_list));
	description_vector = static_p ? allocate_managed_array_static(1,
		FIX(vector_length)) : allocate_managed_array(1,
		FIX(vector_length));
	description = Nil;
	ab_loop_list_ = description_as_list;
	id = Nil;
	keyword = Nil;
	value = Nil;
	description_length = Nil;
	index_1 = FIX((SI_Long)0L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	description_length = CONSP(description) ? length(description) : 
		FIX((SI_Long)0L);
	if (CONSP(description)) {
	    description_old_value = description;
	    temp = FIRST(description_old_value);
	    description = REST(description_old_value);
	    id = temp;
	    value = SECOND(description);
	    if (KEYWORDP(id)) {
		keyword = id;
		value = CAR(description);
		id = Nil;
		if (FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		    svref_new_value = copy_for_slot_value(id);
		    SVREF(description_vector,temp_1) = svref_new_value;
		}
		else {
		    temp_1 = ISVREF(description_vector,(IFIX(index_1) >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
		    svref_new_value = copy_for_slot_value(id);
		    ISVREF(temp_1,svref_arg_2) = svref_new_value;
		}
	    }
	    else {
		if (FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		    svref_new_value = copy_for_slot_value(id);
		    SVREF(description_vector,temp_1) = svref_new_value;
		}
		else {
		    temp_1 = ISVREF(description_vector,(IFIX(index_1) >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
		    svref_new_value = copy_for_slot_value(id);
		    ISVREF(temp_1,svref_arg_2) = svref_new_value;
		}
		keyword = CAR(description);
	    }
	}
	else {
	    value = description;
	    keyword = Ktype;
	}
	index_1 = FIXNUM_ADD1(index_1);
	if (EQ(keyword,Ktype)) {
	    temp = FIX((SI_Long)2L);
	    temp_2 = NUM_GT(description_length,temp);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    if (FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		svref_new_value = slot_value_cons_1(Kgeneral_description,
			slot_value_cons_1(keyword,EQ(CAR(description),
			Ktype) ? copy_for_slot_value(CDR(description)) : 
			copy_for_slot_value(description)));
		SVREF(description_vector,temp_1) = svref_new_value;
	    }
	    else {
		temp_1 = ISVREF(description_vector,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
		svref_new_value = slot_value_cons_1(Kgeneral_description,
			slot_value_cons_1(keyword,EQ(CAR(description),
			Ktype) ? copy_for_slot_value(CDR(description)) : 
			copy_for_slot_value(description)));
		ISVREF(temp_1,svref_arg_2) = svref_new_value;
	    }
	}
	else if (EQ(keyword,Ktype)) {
	    if (FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		svref_new_value = copy_for_slot_value(value);
		SVREF(description_vector,temp_1) = svref_new_value;
	    }
	    else {
		temp_1 = ISVREF(description_vector,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
		svref_new_value = copy_for_slot_value(value);
		ISVREF(temp_1,svref_arg_2) = svref_new_value;
	    }
	}
	else if (FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    svref_new_value = slot_value_cons_1(Kgeneral_description,
		    copy_for_slot_value(description));
	    SVREF(description_vector,temp_1) = svref_new_value;
	}
	else {
	    temp_1 = ISVREF(description_vector,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	    svref_new_value = slot_value_cons_1(Kgeneral_description,
		    copy_for_slot_value(description));
	    ISVREF(temp_1,svref_arg_2) = svref_new_value;
	}
	index_1 = FIXNUM_ADD1(index_1);
	goto next_loop;
      end_loop:;
	return VALUES_1(description_vector);
    }
    else
	return VALUES_1(Nil);
}

/* ALLOCATE-MANAGED-ARRAY-STATIC */
Object allocate_managed_array_static varargs_1(int, n)
{
    Object length_init;
    Object dont_initialize, spine_vector, svref_new_value;
    SI_Long length_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);

    x_note_fn_call(161,11);
    INIT_ARGS_nonrelocating();
    length_init = REQUIRED_ARG_nonrelocating();
    length_1 = IFIX(length_init);
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_AREA(Dynamic_area,0))
	spine_vector = make_array(1,FIX(length_1 + 
		IFIX(Managed_array_index_offset)));
    POP_AREA(0);
    svref_new_value = Managed_array_unique_marker;
    SVREF(spine_vector,FIX((SI_Long)0L)) = svref_new_value;
    ISVREF(spine_vector,(SI_Long)1L) = FIX(length_1);
    if ( !TRUEP(dont_initialize))
	fill_managed_array(spine_vector,Nil);
    return VALUES_1(spine_vector);
}

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qab_class;           /* class */

static Object Qquantity;           /* quantity */

static Object Qtime_stamp;         /* time-stamp */

/* CONVERT-PROCEDURE-TYPE-IF-NECESSARY */
Object convert_procedure_type_if_necessary varargs_1(int, n)
{
    Object type;
    Object local_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(161,12);
    INIT_ARGS_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    local_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (valid_type_specification_p(type) && 
	    type_specification_subtype_p(type,Qitem_or_datum)) {
	if (class_type_specification_p(type))
	    record_free_reference(Qab_class,M_CAR(M_CDR(type)));
	return VALUES_1(type);
    }
    else if (EQ(type,Qquantity))
	return VALUES_1(Qnumber);
    else if (EQ(type,Qtime_stamp)) {
	warn_of_obsolete_time_stamp_type(local_name);
	return VALUES_1(Qnumber);
    }
    else {
	unknown_type_compiler_error(local_name,type);
	return VALUES_1(Qitem_or_datum);
    }
}

static Object string_constant_13;  /* "The type TIME-STAMP for the argument ~a is being phased out.  This ~
				    *        type should be replaced with quantity, integer, or float.  Quantity ~
				    *        will be used for now."
				    */

/* WARN-OF-OBSOLETE-TIME-STAMP-TYPE */
Object warn_of_obsolete_time_stamp_type(local_name)
    Object local_name;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(161,13);
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
	      twrite_compiler_message_header();
	      tformat(2,string_constant_13,local_name);
	      candidate_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    a_string = Nil;
    ab_loop_list_ = Compiler_warnings;
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
    if (temp) {
	reclaim_text_string(candidate_string);
	return VALUES_1(Nil);
    }
    else {
	Compiler_warnings = phrase_cons(candidate_string,Compiler_warnings);
	return VALUES_1(Nil);
    }
}

static Object string_constant_14;  /* "local-name declarations" */

static Object string_constant_15;  /* "The type ~a was given for the local-name ~a, but is not a valid type." */

/* UNKNOWN-TYPE-COMPILER-ERROR */
Object unknown_type_compiler_error(local_name,type)
    Object local_name, type;
{
    x_note_fn_call(161,14);
    return compiler_bug(4,string_constant_14,string_constant_15,type,
	    local_name);
}

static Object Qvar_spot;           /* var-spot */

/* GET-CLASS-AND-TYPE-OF-VARIABLE-DESIGNATION */
Object get_class_and_type_of_variable_designation(variable_designation)
    Object variable_designation;
{
    Object code_body_qm, type_qm, class_qm, var_designation, ab_loop_list_;

    x_note_fn_call(161,15);
    code_body_qm = CAR(Code_body_entries_in_compilation);
    type_qm = Nil;
    class_qm = Nil;
    if (code_body_qm) {
	if (CONSP(variable_designation) && EQ(M_CAR(variable_designation),
		Qvar_spot)) {
	    type_qm = var_spot_type(variable_designation,
		    Lexically_visible_code_bodies);
	    if (CONSP(type_qm) && EQ(CAR(type_qm),Qab_class))
		class_qm = SECOND(type_qm);
	}
	if ( !TRUEP(type_qm)) {
	    var_designation = Nil;
	    ab_loop_list_ = ISVREF(code_body_qm,(SI_Long)11L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    var_designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (type_qm)
		goto end_loop;
	    if (EQ(CAR(var_designation),variable_designation))
		type_qm = SECOND(var_designation);
	    if (CONSP(type_qm) && EQ(CAR(type_qm),Qab_class))
		class_qm = SECOND(type_qm);
	    goto next_loop;
	  end_loop:;
	}
	if ( !TRUEP(type_qm)) {
	    var_designation = Nil;
	    ab_loop_list_ = ISVREF(code_body_qm,(SI_Long)10L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    var_designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (type_qm)
		goto end_loop_1;
	    if (EQ(CAR(var_designation),variable_designation)) {
		type_qm = getfq_function_no_default(CDR(var_designation),
			Ktype);
		if (CONSP(type_qm) && EQ(CAR(type_qm),Qab_class))
		    class_qm = SECOND(type_qm);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	if ( !TRUEP(type_qm)) {
	    var_designation = Nil;
	    ab_loop_list_ = ISVREF(code_body_qm,(SI_Long)3L);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    var_designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (type_qm)
		goto end_loop_2;
	    if (EQ(CAR(var_designation),variable_designation)) {
		type_qm = getfq_function_no_default(CDR(var_designation),
			Ktype);
		if (CONSP(type_qm) && EQ(CAR(type_qm),Qab_class))
		    class_qm = SECOND(type_qm);
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
    }
    return VALUES_2(class_qm,type_qm);
}

/* GET-TYPE-OF-VARIABLE-DESIGNATION */
Object get_type_of_variable_designation(variable_designation)
    Object variable_designation;
{
    Object type_qm;
    Object result;

    x_note_fn_call(161,16);
    result = get_class_and_type_of_variable_designation(variable_designation);
    type_qm = NTH_VALUE((SI_Long)1L, result);
    return VALUES_1(type_qm);
}

/* G2-DISABLE-INLINING */
Object g2_disable_inlining()
{
    x_note_fn_call(161,17);
    No_inlining_qm = T;
    return VALUES_1(No_inlining_qm);
}

/* G2-ENABLE-INLINING */
Object g2_enable_inlining()
{
    x_note_fn_call(161,18);
    No_inlining_qm = Nil;
    return VALUES_1(No_inlining_qm);
}

static Object Qcall_action;        /* call-action */

static Object Qcall_assignment_statement;  /* call-assignment-statement */

static Object Qcall_assignment_action;  /* call-assignment-action */

/* DESTRUCTURE-STATEMENT-DESIGNATION-LOCALS-ARGS-ACROSS? */
Object destructure_statement_designation_locals_args_across_qm(statement)
    Object statement;
{
    Object designation, locals, args, across_qm, gensymed_symbol;
    Object statement_designation, statement_args, statement_across_qm;
    Object statement_local_names;

    x_note_fn_call(161,19);
    designation = Nil;
    locals = Nil;
    args = Nil;
    across_qm = Nil;
    if (CONSP(statement)) {
	if (EQ(CAR(statement),Qcall_action)) {
	    gensymed_symbol = statement;
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_designation = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_args = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_across_qm = CAR(gensymed_symbol);
	    designation = statement_designation;
	    args = statement_args;
	    across_qm = statement_across_qm;
	}
	else if (EQ(CAR(statement),Qcall_assignment_statement) || 
		EQ(CAR(statement),Qcall_assignment_action)) {
	    gensymed_symbol = statement;
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_local_names = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_designation = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_args = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement_across_qm = CAR(gensymed_symbol);
	    locals = statement_local_names;
	    designation = statement_designation;
	    args = statement_args;
	    across_qm = statement_across_qm;
	}
    }
    return VALUES_5(designation,locals,args,across_qm,Nil);
}

Object Call_statements = UNBOUND;

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qmd5_identifier_qm;  /* md5-identifier? */

/* ADD-MD5-IDENTIFIER */
Object add_md5_identifier(item)
    Object item;
{
    Object text, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(161,20);
    text = Text_of_definition_being_compiled;
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    if (temp)
	return change_slot_value(3,item,Qmd5_identifier_qm,
		md5_id_string(text));
    else
	return VALUES_1(Qt);
}

/* REMOVE-MD5-IDENTIFIER */
Object remove_md5_identifier(item)
    Object item;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(161,21);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    if (temp)
	return change_slot_value(3,item,Qmd5_identifier_qm,Nil);
    else
	return VALUES_1(Qt);
}

/* MD5-ID-STRING */
Object md5_id_string(definition_text)
    Object definition_text;
{
    Object digest, result_1, definition_text_as_text_string;
    Object definition_text_as_gensym_string, digest_index;
    SI_Long index_1, aref_new_value;

    x_note_fn_call(161,22);
    digest = obtain_simple_gensym_string(FIX((SI_Long)16L));
    result_1 = obtain_text_string(FIX((SI_Long)8L));
    definition_text_as_text_string = convert_text_to_text_string(1,
	    definition_text);
    definition_text_as_gensym_string = 
	    wide_string_to_gensym_string(definition_text_as_text_string);
    g2ext_init_g2_MD5_context((SI_Long)0L);
    update_indexed_md5_context(FIX((SI_Long)0L),
	    definition_text_as_gensym_string);
    finalize_indexed_md5_context(FIX((SI_Long)0L),digest);
    index_1 = (SI_Long)0L;
    digest_index = Nil;
  next_loop:
    if (index_1 >= (SI_Long)8L)
	goto end_loop;
    digest_index = FIX(index_1 << (SI_Long)1L);
    aref_new_value = (IFIX(CHAR_CODE(SCHAR(digest,digest_index))) << 
	    (SI_Long)8L) + IFIX(CHAR_CODE(SCHAR(digest,
	    FIXNUM_ADD1(digest_index))));
    UBYTE_16_ISASET_1(result_1,index_1,aref_new_value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_simple_gensym_string(digest);
    reclaim_text_string(definition_text_as_text_string);
    reclaim_gensym_string(definition_text_as_gensym_string);
    return VALUES_1(result_1);
}

/* IN-INLINING-CONTEXT? */
Object in_inlining_context_qm()
{
    x_note_fn_call(161,23);
    if (ISVREF(Inlining_data,(SI_Long)1L))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

/* INLINING-CONTEXT? */
Object inlining_context_qm()
{
    x_note_fn_call(161,24);
    if (ISVREF(Inlining_data,(SI_Long)1L))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

/* INLINING-DATA-RECIEVED-VALUE-COMPILATIONS? */
Object inlining_data_recieved_value_compilations_qm()
{
    Object temp;

    x_note_fn_call(161,25);
    if (ISVREF(Inlining_data,(SI_Long)5L)) {
	temp = ISVREF(Inlining_data,(SI_Long)5L);
	return VALUES_1(CAR(temp));
    }
    else
	return VALUES_1(Nil);
}

/* GET-PROCEDURE-METHOD-NAME-IN-CONTEXT */
Object get_procedure_method_name_in_context()
{
    Object context_qm;

    x_note_fn_call(161,26);
    context_qm = ISVREF(Inlining_data,(SI_Long)1L);
    if (context_qm)
	return VALUES_1(ISVREF(CAR(context_qm),(SI_Long)30L));
    else
	return VALUES_1(ISVREF(Current_computation_frame,(SI_Long)30L));
}

/* ENVIRONMENT-INDEX-OK-IN-THIS-CONTEXT? */
Object environment_index_ok_in_this_context_qm(index_1)
    Object index_1;
{
    Object temp;

    x_note_fn_call(161,27);
    if (ISVREF(Inlining_data,(SI_Long)6L)) {
	temp = ISVREF(Inlining_data,(SI_Long)6L);
	temp = sub1(CAR(temp));
	return VALUES_1(NUM_GT(index_1,temp) ? T : Nil);
    }
    else
	return VALUES_1(T);
}

/* GET-PROCEDURE-METHOD-CLASS-IN-CONTEXT */
Object get_procedure_method_class_in_context()
{
    Object context_qm;

    x_note_fn_call(161,28);
    context_qm = ISVREF(Inlining_data,(SI_Long)1L);
    if (context_qm)
	return VALUES_1(ISVREF(CAR(context_qm),(SI_Long)31L));
    else
	return VALUES_1(ISVREF(Current_computation_frame,(SI_Long)31L));
}

/* GET-PROCEDURE-ARGUMENT-DESCRIPTIONS-IN-CONTEXT */
Object get_procedure_argument_descriptions_in_context()
{
    Object context_qm;

    x_note_fn_call(161,29);
    context_qm = ISVREF(Inlining_data,(SI_Long)1L);
    if (context_qm)
	return collect_description_into_list_using_phrase_conses(ISVREF(CAR(context_qm),
		(SI_Long)24L));
    else
	return VALUES_1(ISVREF(CAR(Code_body_entries_in_compilation),
		(SI_Long)10L));
}

/* GET-PROCEDURE-IN-CONTEXT */
Object get_procedure_in_context()
{
    Object context_qm;

    x_note_fn_call(161,30);
    context_qm = ISVREF(Inlining_data,(SI_Long)1L);
    if (context_qm)
	return VALUES_1(CAR(context_qm));
    else
	return VALUES_1(Current_computation_frame);
}

static Object string_constant_16;  /* "{~a::~a~@[~a~]}~a" */

static Object string_constant_17;  /* "{~a~@[~a~]}~a" */

/* MANGLE-SYMBOL-USING */
Object mangle_symbol_using varargs_1(int, n)
{
    Object symbol_to_mangle, item_for_mangling_prefix;
    Object inline_call_number, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(161,31);
    INIT_ARGS_nonrelocating();
    symbol_to_mangle = REQUIRED_ARG_nonrelocating();
    item_for_mangling_prefix = REQUIRED_ARG_nonrelocating();
    inline_call_number = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    sub_class_bit_vector = ISVREF(ISVREF(item_for_mangling_prefix,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
    return intern_text_string(1,temp ? tformat_text_string(5,
	    string_constant_16,ISVREF(item_for_mangling_prefix,
	    (SI_Long)31L),ISVREF(item_for_mangling_prefix,(SI_Long)30L),
	    inline_call_number,symbol_to_mangle) : tformat_text_string(4,
	    string_constant_17,
	    get_lookup_slot_value_given_default(item_for_mangling_prefix,
	    Qname_or_names_for_frame,Nil),inline_call_number,
	    symbol_to_mangle));
}

/* MANGLE-TAG-IN-CONTEXT */
Object mangle_tag_in_context(tag_name)
    Object tag_name;
{
    Object procedure_in_context;

    x_note_fn_call(161,32);
    if (FIXNUMP(tag_name))
	return VALUES_1(tag_name);
    else {
	procedure_in_context = get_procedure_in_context();
	return mangle_symbol_using(3,tag_name,procedure_in_context,
		get_inline_call_number(procedure_in_context));
    }
}

static Object Qassign_local_var;   /* assign-local-var */

/* COMPILE-INLINE-SUBSTITUTION */
Object compile_inline_substitution(parsed_statements,code_body,
	    original_statement,item_being_inlined)
    Object parsed_statements, code_body, original_statement;
    Object item_being_inlined;
{
    Object argument_list_description, base_environment;
    Object returned_values_description, variable_initializations;
    Object added_environment_length, arg_compilations;
    Object return_local_compilations, sub_class_bit_vector, inlining_method_qm;
    Object temp, temp_1, temp_2, temp_3, calling_locals, calling_args;
    Object gensymed_symbol_3, args, return_types, local_vars, body_statement;
    Object arg, ab_loop_list_, type, ab_loop_list__1, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, var_spot, description, var_spot_name;
    Object lexically_visible_goto_tags, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_4, modify_macro_for_phrase_push_arg, temp_5, name_qm;
    Object arg_compilation, arg_spot, base_code_body_return_tag, start_index;
    Object ab_loop_iter_flag_, most_recent_inlined_context;
    Object already_inlined_context_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, index_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(161,33);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,3);
      argument_list_description = Nil;
      base_environment = Nil;
      returned_values_description = Nil;
      variable_initializations = Nil;
      added_environment_length = FIX((SI_Long)0L);
      arg_compilations = Nil;
      return_local_compilations = Nil;
      sub_class_bit_vector = ISVREF(ISVREF(item_being_inlined,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
	  inlining_method_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
      }
      else
	  inlining_method_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Returned_values_description,Qreturned_values_description,returned_values_description,
	      2);
	temp = inlining_method_qm ? ISVREF(item_being_inlined,
		(SI_Long)31L) : Nil;
	temp_1 = inlining_method_qm ? ISVREF(item_being_inlined,
		(SI_Long)30L) : 
		get_lookup_slot_value_given_default(item_being_inlined,
		Qname_or_names_for_frame,Nil);
	temp_2 = ISVREF(item_being_inlined,(SI_Long)23L);
	record_free_reference(Qinline,phrase_list_4(temp,temp_1,temp_2,
		copy_for_phrase(get_lookup_slot_value_given_default(item_being_inlined,
		Qmd5_identifier_qm,Nil))));
	result = destructure_statement_designation_locals_args_across_qm(original_statement);
	MVS_3(result,temp,calling_locals,calling_args);
	if (memq_function(CAR(original_statement),Call_statements))
	    Call_statement_processed_qm = T;
	gensymed_symbol_3 = parsed_statements;
	gensymed_symbol_3 = CDR(gensymed_symbol_3);
	args = CAR(gensymed_symbol_3);
	gensymed_symbol_3 = CDR(gensymed_symbol_3);
	return_types = CAR(gensymed_symbol_3);
	gensymed_symbol_3 = CDR(gensymed_symbol_3);
	local_vars = CAR(gensymed_symbol_3);
	gensymed_symbol_3 = CDR(gensymed_symbol_3);
	body_statement = CAR(gensymed_symbol_3);
	arg = Nil;
	ab_loop_list_ = calling_args;
	type = Nil;
	ab_loop_list__1 = 
		collect_types_into_list_using_phrase_conses(ISVREF(item_being_inlined,
		(SI_Long)24L));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	type = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loopvar__2 = phrase_cons(compile_stack_expression(arg,type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	arg_compilations = ab_loopvar_;
	goto end_1;
	arg_compilations = Qnil;
      end_1:;
	var_spot = Nil;
	description = Nil;
	var_spot_name = Nil;
	ab_loop_list_ = calling_locals;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	var_spot_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = variable_spot_and_description_for_local_name(var_spot_name);
	MVS_2(result,var_spot,description);
	if ( !TRUEP(var_spot)) {
	    var_spot = generate_new_variable_spot(1,Qitem_or_datum);
	    procedure_compiler_missing_local_name_error(var_spot_name);
	}
	return_local_compilations = phrase_cons(var_spot,
		return_local_compilations);
	goto next_loop_1;
      end_loop_1:;
	return_local_compilations = nreverse(return_local_compilations);
	lexically_visible_goto_tags = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		1);
	  gensymed_symbol_3 = item_being_inlined;
	  gensymed_symbol_4 = return_local_compilations;
	  gensymed_symbol_5 = Code_body;
	  temp_4 = Inlining_data;
	  modify_macro_for_phrase_push_arg = gensymed_symbol_5;
	  temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		  (SI_Long)11L),modify_macro_for_phrase_push_arg);
	  SVREF(temp_4,FIX((SI_Long)11L)) = temp_5;
	  temp_4 = Inlining_data;
	  modify_macro_for_phrase_push_arg = gensymed_symbol_3;
	  temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		  (SI_Long)1L),modify_macro_for_phrase_push_arg);
	  SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
	  temp_4 = Inlining_data;
	  modify_macro_for_phrase_push_arg = gensymed_symbol_4;
	  temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		  (SI_Long)5L),modify_macro_for_phrase_push_arg);
	  SVREF(temp_4,FIX((SI_Long)5L)) = temp_5;
	  gensymed_symbol_4 = length(ISVREF(gensymed_symbol_5,(SI_Long)3L));
	  temp_4 = Inlining_data;
	  modify_macro_for_phrase_push_arg = gensymed_symbol_4;
	  temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		  (SI_Long)6L),modify_macro_for_phrase_push_arg);
	  SVREF(temp_4,FIX((SI_Long)6L)) = temp_5;
	  gensymed_symbol_4 = length(ISVREF(gensymed_symbol_5,(SI_Long)11L));
	  temp_4 = Inlining_data;
	  modify_macro_for_phrase_push_arg = gensymed_symbol_4;
	  temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		  (SI_Long)7L),modify_macro_for_phrase_push_arg);
	  SVREF(temp_4,FIX((SI_Long)7L)) = temp_5;
	  if ( !TRUEP(block_is_optimizable_p(gensymed_symbol_3))) {
	      temp_4 = Inlining_data;
	      SVREF(temp_4,FIX((SI_Long)9L)) = Nil;
	  }
	  result = generate_environment_descriptions(args,return_types,
		  local_vars);
	  MVS_4(result,argument_list_description,base_environment,
		  Returned_values_description,variable_initializations);
	  added_environment_length = length(base_environment);
	  temp_4 = Code_body;
	  temp_5 = nconc2(ISVREF(Code_body,(SI_Long)3L),base_environment);
	  SVREF(temp_4,FIX((SI_Long)3L)) = temp_5;
	  temp_4 = Code_body;
	  temp = ISVREF(Code_body,(SI_Long)11L);
	  temp_5 = nconc2(temp,copy_list_using_phrase_conses(local_vars));
	  SVREF(temp_4,FIX((SI_Long)11L)) = temp_5;
	  description = Nil;
	  ab_loop_list_ = argument_list_description;
	  name_qm = Nil;
	  arg_compilation = Nil;
	  ab_loop_list__1 = arg_compilations;
	  arg_spot = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  name_qm = CAR(description);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_2;
	  arg_compilation = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  arg_spot = variable_spot_and_description_for_local_name(name_qm);
	  emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		  arg_spot,arg_compilation));
	  goto next_loop_2;
	end_loop_2:;
	  if (variable_initializations) {
	      temp_4 = last(variable_initializations,_);
	      temp_5 = phrase_cons(body_statement,Nil);
	      M_CDR(temp_4) = temp_5;
	      body_statement = phrase_cons(Qbegin_statement,
		      variable_initializations);
	  }
	  base_code_body_return_tag = generate_new_goto_tag();
	  PUSH_SPECIAL_WITH_SYMBOL(Base_code_body_return_tag,Qbase_code_body_return_tag,base_code_body_return_tag,
		  0);
	    record_goto_tags(body_statement);
	    compile_procedure_statement(body_statement);
	    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		    Base_code_body_return_tag));
	  POP_SPECIAL();
	  description = Nil;
	  ab_loop_list_ = ISVREF(Code_body,(SI_Long)3L);
	  index_1 = (SI_Long)0L;
	  temp = ISVREF(Inlining_data,(SI_Long)6L);
	  start_index = CAR(temp);
	  ab_loop_iter_flag_ = T;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      index_1 = index_1 + (SI_Long)1L;
	  if ( !(index_1 < IFIX(FIXNUM_ADD(start_index,
		  added_environment_length))))
	      goto end_loop_3;
	  if (CAR(description) && index_1 >= IFIX(start_index)) {
	      temp_4 = mangle_symbol_using(2,CAR(description),
		      item_being_inlined);
	      M_CAR(description) = temp_4;
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop_3;
	end_loop_3:;
	  temp = ISVREF(Inlining_data,(SI_Long)1L);
	  most_recent_inlined_context = CAR(temp);
	  already_inlined_context_qm = 
		  assq_function(most_recent_inlined_context,
		  ISVREF(Inlining_data,(SI_Long)8L));
	  if (already_inlined_context_qm) {
	      temp_4 = FIXNUM_ADD1(M_CDR(already_inlined_context_qm));
	      M_CDR(already_inlined_context_qm) = temp_4;
	  }
	  else {
	      gensymed_symbol_3 = phrase_cons(most_recent_inlined_context,
		      FIX((SI_Long)1L));
	      temp_4 = Inlining_data;
	      modify_macro_for_phrase_push_arg = gensymed_symbol_3;
	      temp_5 = phrase_cons_with_args_reversed(ISVREF(temp_4,
		      (SI_Long)8L),modify_macro_for_phrase_push_arg);
	      SVREF(temp_4,FIX((SI_Long)8L)) = temp_5;
	  }
	  temp_4 = Inlining_data;
	  temp = ISVREF(Inlining_data,(SI_Long)11L);
	  temp_5 = CDR(temp);
	  SVREF(temp_4,FIX((SI_Long)11L)) = temp_5;
	  temp_4 = Inlining_data;
	  temp = ISVREF(Inlining_data,(SI_Long)1L);
	  temp_5 = CDR(temp);
	  SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
	  temp_4 = Inlining_data;
	  temp = ISVREF(Inlining_data,(SI_Long)6L);
	  temp_5 = CDR(temp);
	  SVREF(temp_4,FIX((SI_Long)6L)) = temp_5;
	  temp_4 = Inlining_data;
	  temp = ISVREF(Inlining_data,(SI_Long)7L);
	  temp_5 = CDR(temp);
	  SVREF(temp_4,FIX((SI_Long)7L)) = temp_5;
	  temp_4 = Inlining_data;
	  temp = ISVREF(Inlining_data,(SI_Long)5L);
	  temp_5 = CDR(temp);
	  result = VALUES_1(SVREF(temp_4,FIX((SI_Long)5L)) = temp_5);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qprocedure_statement;  /* procedure-statement */

static Object Qaction_compiler;    /* action-compiler */

static Object Qprocedure_statement_compiler;  /* procedure-statement-compiler */

static Object string_constant_18;  /* "statement compiler" */

static Object string_constant_19;  /* "The statement ~A is not defined." */

static Object string_constant_20;  /* "The statement ~a is not in the correct format." */

/* COMPILE-PROCEDURE-STATEMENT */
Object compile_procedure_statement(statement)
    Object statement;
{
    Object current_computation_component_particulars, statement_name;
    Object statement_compiler, action_compiler, prolog_stream, epilog_stream;
    Declare_special(1);
    Object result;

    x_note_fn_call(161,34);
    current_computation_component_particulars = 
	    phrase_list_3(Qprocedure_statement,statement,
	    Qcurrent_computation_frame);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	    0);
      statement_name = CONSP(statement) ? CAR(statement) : Nil;
      statement_compiler = Nil;
      action_compiler = Nil;
      if (SYMBOLP(statement_name)) {
	  action_compiler = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(statement_name),
		  Qaction_compiler);
	  if ( !TRUEP(action_compiler))
	      statement_compiler = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(statement_name),
		      Qprocedure_statement_compiler);
      }
      if (action_compiler) {
	  prolog_stream = make_pseudo_instruction_stream_1();
	  epilog_stream = make_pseudo_instruction_stream_1();
	  inline_funcall_5(action_compiler,statement,Nil,T,prolog_stream,
		  epilog_stream);
	  merge_pseudo_instruction_stream(prolog_stream);
	  result = merge_pseudo_instruction_stream(epilog_stream);
      }
      else if (statement_compiler)
	  result = VALUES_1(inline_funcall_1(statement_compiler,statement));
      else if (SYMBOLP(statement_name) && statement_name)
	  result = compiler_bug(3,string_constant_18,string_constant_19,
		  statement_name);
      else
	  result = compiler_bug(3,string_constant_18,string_constant_20,
		  statement);
    POP_SPECIAL();
    return result;
}

/* COMPILE-PROCEDURE-VAR-SPOT */
Object compile_procedure_var_spot(var_spot,required_type)
    Object var_spot, required_type;
{
    x_note_fn_call(161,35);
    return compile_stack_expression_into_nodes(var_spot,required_type);
}

/* COMPILE-PROCEDURE-EXPRESSION */
Object compile_procedure_expression varargs_1(int, n)
{
    Object expression;
    Object required_type, expression_bound_local_names;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(161,36);
    INIT_ARGS_nonrelocating();
    expression = REQUIRED_ARG_nonrelocating();
    required_type = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    expression_bound_local_names = Expression_bound_local_names;
    PUSH_SPECIAL_WITH_SYMBOL(Expression_bound_local_names,Qexpression_bound_local_names,expression_bound_local_names,
	    0);
      result = compile_stack_expression_into_nodes(expression,required_type);
    POP_SPECIAL();
    return result;
}

/* COMPILE-STACK-EXPRESSION */
Object compile_stack_expression(expression,required_type)
    Object expression, required_type;
{
    Object expression_bound_local_names;
    Declare_special(1);
    Object result;

    x_note_fn_call(161,37);
    expression_bound_local_names = Expression_bound_local_names;
    PUSH_SPECIAL_WITH_SYMBOL(Expression_bound_local_names,Qexpression_bound_local_names,expression_bound_local_names,
	    0);
      result = compile_stack_expression_into_nodes(expression,required_type);
    POP_SPECIAL();
    return result;
}

static Object Qrelated;            /* related */

static Object Qrelation;           /* relation */

static Object Qat_port;            /* at-port */

static Object Qport_name;          /* port-name */

static Object Qclass_qualified_method;  /* class-qualified-method */

static Object Qtext_of_attribute;  /* text-of-attribute */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qclass_qualified_attribute_of_class;  /* class-qualified-attribute-of-class */

static Object Qattribute_of_class;  /* attribute-of-class */

static Object Qattribute;          /* attribute */

/* RECORD-FREE-REFERENCES-OF-ROLE */
Object record_free_references_of_role varargs_1(int, n)
{
    Object role;
    Object domain_type_list_qm, simple_role, type_qm, attribute_role;
    Declare_varargs_nonrelocating;

    x_note_fn_call(161,38);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_type_list_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    simple_role = simple_role_of_role(role);
    if (CONSP(simple_role)) {
	type_qm = type_specification_of_role(simple_role);
	if (class_type_specification_p(type_qm))
	    record_free_reference(Qab_class,M_CAR(M_CDR(type_qm)));
	if (EQ(CAR(simple_role),Qrelated))
	    return record_free_reference(Qrelation,SECOND(simple_role));
	else if (EQ(CAR(simple_role),Qat_port))
	    return record_free_reference(Qport_name,
		    phrase_cons(SECOND(simple_role),Nil));
	else if (EQ(CAR(simple_role),Qclass_qualified_method))
	    return record_free_reference(Qclass_qualified_method,
		    phrase_list_2(THIRD(simple_role),SECOND(simple_role)));
	else if (EQ(CAR(simple_role),Qtext_of_attribute)) {
	    compiler_warning_if_superseded_attribute(SECOND(simple_role));
	    attribute_role = SECOND(simple_role);
	    if (IFIX(length(domain_type_list_qm)) == (SI_Long)1L && 
		    class_type_specification_p(CAR(domain_type_list_qm))) {
		if (CONSP(attribute_role) && EQ(M_CAR(attribute_role),
			Qclass_qualified_name))
		    return record_free_reference(Qclass_qualified_attribute_of_class,
			    phrase_list_3(THIRD(attribute_role),
			    SECOND(attribute_role),
			    M_CAR(M_CDR(CAR(domain_type_list_qm)))));
		else
		    return record_free_reference(Qattribute_of_class,
			    phrase_cons(attribute_role,
			    M_CAR(M_CDR(CAR(domain_type_list_qm)))));
	    }
	    else
		return record_free_reference(Qattribute,attribute_role);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* OPTIMIZE-PROCEDURE-INSTRUCTIONS */
Object optimize_procedure_instructions(procedure_instructions,code_body_entry)
    Object procedure_instructions, code_body_entry;
{
    Object optimized_procedure_instructions;

    x_note_fn_call(161,39);
    optimized_procedure_instructions = procedure_instructions;
    if (optimized_procedure_instructions) {
	optimized_procedure_instructions = 
		short_cut_branch_to_branch_procedure_instructions(optimized_procedure_instructions);
	optimized_procedure_instructions = 
		remove_dead_procedure_instructions(optimized_procedure_instructions,
		code_body_entry);
    }
    return VALUES_1(optimized_procedure_instructions);
}

/* SHORT-CUT-BRANCH-TO-BRANCH-PROCEDURE-INSTRUCTIONS */
Object short_cut_branch_to_branch_procedure_instructions(procedure_instructions)
    Object procedure_instructions;
{
    Object tags_to_forward_alist, procedure_branch_short_cuts;
    Declare_special(1);

    x_note_fn_call(161,40);
    tags_to_forward_alist = 
	    collect_forwardable_goto_tags(procedure_instructions);
    if (tags_to_forward_alist) {
	procedure_branch_short_cuts = tags_to_forward_alist;
	PUSH_SPECIAL_WITH_SYMBOL(Procedure_branch_short_cuts,Qprocedure_branch_short_cuts,procedure_branch_short_cuts,
		0);
	  replace_goto_tags_with_instruction_addresses(procedure_instructions);
	POP_SPECIAL();
    }
    return VALUES_1(procedure_instructions);
}

static Object Qbranch;             /* branch */

/* COLLECT-FORWARDABLE-GOTO-TAGS */
Object collect_forwardable_goto_tags(procedure_instructions)
    Object procedure_instructions;
{
    Object short_cuts, combined_sources_to_target, instruction_cons, temp;
    Object source, target, cs_to_t_cons, ab_loop_list_, combined_sources;
    Object combined_target, car_new_value, combined_cons, sources, source_cons;
    Object next_source_cons;

    x_note_fn_call(161,41);
    short_cuts = Nil;
    combined_sources_to_target = Nil;
    instruction_cons = procedure_instructions;
  next_loop:
    if ( !TRUEP(instruction_cons))
	goto end_loop;
    if (EQ(CAAR(instruction_cons),Qtag_statement) && 
	    EQ(CAADR(instruction_cons),Qbranch)) {
	temp = FIRST(instruction_cons);
	source = SECOND(temp);
	temp = SECOND(instruction_cons);
	target = SECOND(temp);
	cs_to_t_cons = Nil;
	ab_loop_list_ = combined_sources_to_target;
	combined_sources = Nil;
	combined_target = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	cs_to_t_cons = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	combined_sources = CAR(cs_to_t_cons);
	combined_target = CDR(cs_to_t_cons);
	if (EQ(target,combined_target) || memq_function(target,
		combined_sources)) {
	    car_new_value = phrase_cons(source,combined_sources);
	    M_CAR(cs_to_t_cons) = car_new_value;
	    goto end_combine;
	}
	else if (EQ(source,combined_target)) {
	    M_CDR(cs_to_t_cons) = target;
	    car_new_value = phrase_cons(source,combined_sources);
	    M_CAR(cs_to_t_cons) = car_new_value;
	    goto end_combine;
	}
	goto next_loop_1;
      end_loop_1:
	combined_sources_to_target = 
		phrase_cons(phrase_cons(phrase_cons(source,Nil),target),
		combined_sources_to_target);
      end_combine:;
    }
    instruction_cons = M_CDR(instruction_cons);
    goto next_loop;
  end_loop:;
    combined_cons = Nil;
    ab_loop_list_ = combined_sources_to_target;
    sources = Nil;
    target = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    combined_cons = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sources = CAR(combined_cons);
    target = CDR(combined_cons);
    source_cons = sources;
    next_source_cons = Nil;
  next_loop_3:
    next_source_cons = CDR(source_cons);
    if ( !TRUEP(source_cons))
	goto end_loop_3;
    if ( !TRUEP(next_source_cons)) {
	M_CDR(combined_cons) = short_cuts;
	short_cuts = combined_cons;
	M_CAR(combined_cons) = source_cons;
	M_CDR(source_cons) = target;
    }
    else {
	M_CDR(source_cons) = target;
	short_cuts = phrase_cons(source_cons,short_cuts);
    }
    source_cons = next_source_cons;
    goto next_loop_3;
  end_loop_3:;
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(short_cuts);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qgoto_tag_references;  /* goto-tag-references */

static Object Qgoto_tag_replacer;  /* goto-tag-replacer */

static Object string_constant_21;  /* "tag replacers" */

static Object string_constant_22;  /* "No goto tag replacer function exists for ~a." */

static Object Qphrase_pool;        /* phrase-pool */

static Object string_constant_23;  /* "dead code optimizer" */

static Object string_constant_24;  /* "Malformed tag ~a in ~a instruction." */

/* REMOVE-DEAD-PROCEDURE-INSTRUCTIONS */
Object remove_dead_procedure_instructions(procedure_instructions,
	    code_body_entry)
    Object procedure_instructions, code_body_entry;
{
    Object unconditional_branches, entry_points, tags_to_eliminate;
    Object leading_cons, code_eliminated_qm, referenced_tags, existing_tags;
    Object cons_trailer, instruction_cons, instruction, instruction_name, tag;
    Object gensymed_symbol, referencer_function_qm, ab_loop_list_;
    Object gensymed_symbol_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_2, cons_1, temp, temp_2;
    Object restart_cons, restart_point_or_end;
    SI_Long gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(161,42);
    unconditional_branches = list_constant_1;
    entry_points = list_constant_2;
    tags_to_eliminate = Nil;
    leading_cons = phrase_cons(Nil,procedure_instructions);
    code_eliminated_qm = Nil;
    referenced_tags = Nil;
    existing_tags = Nil;
  next_loop:
    code_eliminated_qm = Nil;
    referenced_tags = Nil;
    existing_tags = Nil;
    cons_trailer = leading_cons;
    instruction_cons = CDR(leading_cons);
    instruction = Nil;
    instruction_name = Nil;
  next_loop_1:
    if ( !TRUEP(instruction_cons))
	goto end_loop;
    instruction = CAR(instruction_cons);
    instruction_name = CAR(instruction);
    tag = Nil;
    gensymed_symbol = M_CAR(instruction);
    referencer_function_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qgoto_tag_references);
    if (referencer_function_qm) {
	gensymed_symbol = M_CAR(instruction);
	if ( 
		!TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qgoto_tag_replacer)))
	    compiler_bug(3,string_constant_21,string_constant_22,
		    M_CAR(instruction));
	ab_loop_list_ = inline_funcall_1(referencer_function_qm,instruction);
    }
    else
	ab_loop_list_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    tag = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(tag) || SYMBOLP(tag)) {
	gensymed_symbol = referenced_tags;
	gensymed_symbol_1 = tag;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_phrase_pool_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_phrase_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_phrase_pool_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_phrase_pool_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_phrase_pool_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qphrase_pool);
	    cons_1 = gensymed_symbol_2;
	    if (Current_edit_state) {
		gensymed_symbol_3 = 
			IFIX(atomic_incff_svslot(Current_edit_state,
			FIX((SI_Long)38L),FIX( - (SI_Long)1L)));
		if (gensymed_symbol_3 < (SI_Long)0L)
		    gensymed_symbol_3 = 
			    IFIX(add_another_vector_for_phrase_conses());
		temp = ISVREF(Current_edit_state,(SI_Long)37L);
		svref_arg_1 = CAR(temp);
		referenced_tags = ISVREF(svref_arg_1,gensymed_symbol_3) = 
			cons_1;
	    }
	    else
		referenced_tags = cons_1;
	}
    }
    else
	compiler_bug(4,string_constant_23,string_constant_24,tag,
		CAR(instruction));
    goto next_loop_2;
  end_loop_1:;
    if (EQ(instruction_name,Qbranch)) {
	temp = SECOND(instruction_cons);
	temp_1 = EQ(CAR(temp),Qtag_statement);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = SECOND(instruction);
	temp = SECOND(instruction_cons);
	temp = SECOND(temp);
	temp_1 = EQL(temp_2,temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	code_eliminated_qm = T;
	instruction_cons = CDR(instruction_cons);
	M_CDR(cons_trailer) = instruction_cons;
    }
    else if (memq_function(instruction_name,unconditional_branches)) {
	restart_cons = CDR(instruction_cons);
      next_loop_3:
	if ( !TRUEP(restart_cons))
	    goto end_loop_2;
	if (memq_function(CAAR(restart_cons),entry_points)) {
	    temp_1 =  !EQ(CAAR(restart_cons),Qtag_statement);
	    if (temp_1);
	    else {
		temp = CAR(restart_cons);
		temp_1 =  !TRUEP(member_eql(SECOND(temp),tags_to_eliminate));
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    restart_point_or_end = restart_cons;
	    goto end_1;
	}
	restart_cons = M_CDR(restart_cons);
	goto next_loop_3;
      end_loop_2:
	restart_point_or_end = Nil;
	goto end_1;
	restart_point_or_end = Qnil;
      end_1:;
	if ( !EQ(CDR(instruction_cons),restart_point_or_end)) {
	    code_eliminated_qm = T;
	    M_CDR(instruction_cons) = restart_point_or_end;
	}
	cons_trailer = instruction_cons;
	instruction_cons = CDR(instruction_cons);
    }
    else if (EQ(instruction_name,Qtag_statement)) {
	if (member_eql(SECOND(instruction),tags_to_eliminate)) {
	    code_eliminated_qm = T;
	    instruction_cons = CDR(instruction_cons);
	    M_CDR(cons_trailer) = instruction_cons;
	}
	else {
	    existing_tags = phrase_cons(SECOND(instruction),existing_tags);
	    cons_trailer = instruction_cons;
	    instruction_cons = CDR(instruction_cons);
	}
    }
    else {
	cons_trailer = instruction_cons;
	instruction_cons = CDR(instruction_cons);
    }
    goto next_loop_1;
  end_loop:;
    tags_to_eliminate = Nil;
    tag = Nil;
    ab_loop_list_ = existing_tags;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    tag = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(member_eql(tag,referenced_tags)))
	tags_to_eliminate = phrase_cons(tag,tags_to_eliminate);
    goto next_loop_4;
  end_loop_3:;
    if ( !(code_eliminated_qm || tags_to_eliminate))
	goto end_loop_4;
    goto next_loop;
  end_loop_4:;
    return VALUES_1(CDR(leading_cons));
}

static Object string_constant_25;  /* "The tag ~a was declared but not referenced." */

/* WARN-OF-UNREFERENCED-GOTO-TAGS */
Object warn_of_unreferenced_goto_tags()
{
    Object entry, ab_loop_list_, name, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, ab_loop_list__1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(161,43);
    entry = Nil;
    ab_loop_list_ = Goto_tags_in_compilation;
    name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name = ISVREF(entry,(SI_Long)1L);
    if ( !(ISVREF(entry,(SI_Long)3L) || ISVREF(entry,(SI_Long)4L) || 
	    FIXNUMP(name) && IFIX(name) < (SI_Long)0L)) {
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
		  tformat(2,string_constant_25,name);
		  candidate_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	a_string = Nil;
	ab_loop_list__1 = Compiler_warnings;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	a_string = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (string_eq_w(a_string,candidate_string)) {
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	if (temp)
	    reclaim_text_string(candidate_string);
	else
	    Compiler_warnings = phrase_cons(candidate_string,
		    Compiler_warnings);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_26;  /* "tags directory" */

static Object string_constant_27;  /* "The tag ~a was in instructions, but not in the directory ~
				    *                   of tags at jump expansion time."
				    */

static Object Qjump_tag_statement;  /* jump-tag-statement */

static Object Qabort_called_code_bodies;  /* abort-called-code-bodies */

/* EXPAND-JUMP-TARGETS */
Object expand_jump_targets(instructions)
    Object instructions;
{
    Object head_of_instructions, list_trailer, instruction_cons, tag_name;
    Object entry, new_instructions, cdr_arg;

    x_note_fn_call(161,44);
    head_of_instructions = phrase_cons(Nil,instructions);
    list_trailer = head_of_instructions;
    instruction_cons = Nil;
  next_loop:
    instruction_cons = M_CDR(list_trailer);
    if ( !TRUEP(instruction_cons))
	goto end_loop;
    if (EQ(M_CAR(M_CAR(instruction_cons)),Qtag_statement)) {
	tag_name = M_CAR(M_CDR(M_CAR(instruction_cons)));
	entry = goto_tag_entry_with_name(tag_name,Goto_tags_in_compilation);
	if ( !TRUEP(entry))
	    compiler_bug(3,string_constant_26,string_constant_27,tag_name);
	else if (ISVREF(entry,(SI_Long)4L)) {
	    new_instructions = phrase_list_3(phrase_list_2(Qbranch,
		    tag_name),phrase_list_2(Qjump_tag_statement,tag_name),
		    phrase_cons(Qabort_called_code_bodies,Nil));
	    M_CDR(list_trailer) = new_instructions;
	    cdr_arg = last(new_instructions,_);
	    M_CDR(cdr_arg) = instruction_cons;
	}
    }
    list_trailer = instruction_cons;
    goto next_loop;
  end_loop:
    return VALUES_1(CDR(head_of_instructions));
    return VALUES_1(Qnil);
}

static Object string_constant_28;  /* "The tag ~a had no entry at address generation time." */

static Object string_constant_29;  /* "The JUMP tag ~a had no entry at address generation time." */

/* COLLECT-GOTO-TAG-ADDRESSES */
Object collect_goto_tag_addresses(instructions)
    Object instructions;
{
    Object leading_cons, tag, entry, trailer, instruction_cons;
    Object instruction_name, temp;
    SI_Long instruction_address;

    x_note_fn_call(161,45);
    leading_cons = phrase_cons(Nil,instructions);
    tag = Nil;
    entry = Nil;
    instruction_address = (SI_Long)0L;
    trailer = leading_cons;
    instruction_cons = instructions;
    instruction_name = Nil;
  next_loop:
    if ( !TRUEP(instruction_cons))
	goto end_loop;
    instruction_name = CAAR(instruction_cons);
    if (EQ(instruction_name,Qtag_statement)) {
	temp = CAR(instruction_cons);
	tag = SECOND(temp);
	entry = goto_tag_entry_with_name(tag,Goto_tags_in_compilation);
	if ( !TRUEP(entry))
	    compiler_bug(3,string_constant_4,string_constant_28,tag);
	else
	    ISVREF(entry,(SI_Long)5L) = FIX(instruction_address);
	instruction_cons = CDR(instruction_cons);
	M_CDR(trailer) = instruction_cons;
    }
    else if (EQ(instruction_name,Qjump_tag_statement)) {
	temp = CAR(instruction_cons);
	tag = SECOND(temp);
	entry = goto_tag_entry_with_name(tag,Goto_tags_in_compilation);
	if ( !TRUEP(entry))
	    compiler_bug(3,string_constant_4,string_constant_29,tag);
	else
	    ISVREF(entry,(SI_Long)6L) = FIX(instruction_address);
	instruction_cons = CDR(instruction_cons);
	M_CDR(trailer) = instruction_cons;
    }
    else {
	instruction_address = instruction_address + (SI_Long)1L;
	trailer = instruction_cons;
	instruction_cons = CDR(instruction_cons);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(CDR(leading_cons));
}

static Object string_constant_30;  /* "address registrar" */

static Object string_constant_31;  /* "The tag ~a had no entry." */

static Object string_constant_32;  /* "The tag ~a is registered at multiple addresses." */

/* REGISTER-GOTO-TAG-ADDRESS */
Object register_goto_tag_address(tag,address,jump_tag_qm)
    Object tag, address, jump_tag_qm;
{
    Object entry;

    x_note_fn_call(161,46);
    entry = goto_tag_entry_with_name(tag,Goto_tags_in_compilation);
    if ( !TRUEP(entry))
	compiler_bug(3,string_constant_30,string_constant_31,tag);
    else if ( !TRUEP(jump_tag_qm)) {
	if (ISVREF(entry,(SI_Long)5L))
	    compiler_error(2,string_constant_32,tag);
	SVREF(entry,FIX((SI_Long)5L)) = address;
    }
    else {
	if (ISVREF(entry,(SI_Long)6L))
	    compiler_error(2,string_constant_32,tag);
	SVREF(entry,FIX((SI_Long)6L)) = address;
    }
    return VALUES_1(Nil);
}

/* REPLACE-GOTO-TAGS-WITH-INSTRUCTION-ADDRESSES */
Object replace_goto_tags_with_instruction_addresses(instructions)
    Object instructions;
{
    Object instruction_cons, replacer_function_qm, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value;

    x_note_fn_call(161,47);
    instruction_cons = instructions;
    replacer_function_qm = Nil;
  next_loop:
    if ( !TRUEP(instruction_cons))
	goto end_loop;
    gensymed_symbol = M_CAR(M_CAR(instruction_cons));
    replacer_function_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qgoto_tag_replacer);
    if (replacer_function_qm) {
	gensymed_symbol = replacer_function_qm;
	gensymed_symbol_1 = M_CAR(instruction_cons);
	car_new_value = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	M_CAR(instruction_cons) = car_new_value;
    }
    instruction_cons = M_CDR(instruction_cons);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qjump;               /* jump */

/* EMIT-BRANCH-OR-JUMP */
Object emit_branch_or_jump(tag)
    Object tag;
{
    Object jump_depth_qm;

    x_note_fn_call(161,48);
    jump_depth_qm = jump_depth_for_tag_qm(tag);
    if ( !TRUEP(jump_depth_qm))
	return emit_already_consed_instruction(phrase_list_2(Qbranch,tag));
    else
	return emit_already_consed_instruction(phrase_list_3(Qjump,
		jump_depth_qm,tag));
}

static Object Qbranch_if_true;     /* branch-if-true */

/* EMIT-BRANCH-OR-JUMP-IF-TRUE */
Object emit_branch_or_jump_if_true(compiled_expression,tag)
    Object compiled_expression, tag;
{
    Object jump_depth_qm, new_tag;

    x_note_fn_call(161,49);
    jump_depth_qm = jump_depth_for_tag_qm(tag);
    if ( !TRUEP(jump_depth_qm))
	return emit_already_consed_instruction(phrase_list_3(Qbranch_if_true,
		compiled_expression,tag));
    else {
	new_tag = generate_new_goto_tag();
	emit_branch_or_jump_if_not_true(compiled_expression,new_tag);
	emit_already_consed_instruction(phrase_list_3(Qjump,jump_depth_qm,
		tag));
	return emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		new_tag));
    }
}

static Object Qbranch_if_not_true;  /* branch-if-not-true */

/* EMIT-BRANCH-OR-JUMP-IF-NOT-TRUE */
Object emit_branch_or_jump_if_not_true(compiled_expression,tag)
    Object compiled_expression, tag;
{
    Object jump_depth_qm, new_tag;

    x_note_fn_call(161,50);
    jump_depth_qm = jump_depth_for_tag_qm(tag);
    if ( !TRUEP(jump_depth_qm))
	return emit_already_consed_instruction(phrase_list_3(Qbranch_if_not_true,
		compiled_expression,tag));
    else {
	new_tag = generate_new_goto_tag();
	emit_branch_or_jump_if_true(compiled_expression,new_tag);
	emit_already_consed_instruction(phrase_list_3(Qjump,jump_depth_qm,
		tag));
	return emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		new_tag));
    }
}

static Object string_constant_33;  /* "~a = " */

/* PRINT-ASSIGNMENT-STATEMENT */
Object print_assignment_statement(statement)
    Object statement;
{
    x_note_fn_call(161,51);
    tformat(2,string_constant_33,SECOND(statement));
    return write_expression(THIRD(statement));
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* WRITE-RETURN-STATEMENT */
Object write_return_statement(statement)
    Object statement;
{
    Object expression, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,52);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)7L));
    expression = Nil;
    ab_loop_list_ = CDR(statement);
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm)) {
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	write_expression(expression);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* WRITE-IF-THEN-STATEMENT */
Object write_if_then_statement(statement)
    Object statement;
{
    x_note_fn_call(161,53);
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)3L));
    write_expression(SECOND(statement));
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)6L));
    return write_procedure_statement(THIRD(statement));
}

static Object array_constant_4;    /* # */

/* WRITE-IF-THEN-ELSE-STATEMENT */
Object write_if_then_else_statement(statement)
    Object statement;
{
    x_note_fn_call(161,54);
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)3L));
    write_expression(SECOND(statement));
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)6L));
    write_procedure_statement(THIRD(statement));
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)6L));
    return write_procedure_statement(FOURTH(statement));
}

static Object array_constant_5;    /* # */

static Object string_constant_34;  /* ")~%  " */

static Object string_constant_35;  /* ";~%  " */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object string_constant_36;  /* "~%  END" */

/* PRINT-CASE-STATEMENT */
Object print_case_statement(statement)
    Object statement;
{
    Object expression, case_choices, case_choice, ab_loop_list_, values_1;
    Object case_statement, first_choice_qm, ab_loop_iter_flag_, value;
    Object ab_loop_list__1, first_value_qm, temp;

    x_note_fn_call(161,55);
    expression = SECOND(statement);
    case_choices = CDDR(statement);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)6L));
    write_expression(expression);
    tformat(1,string_constant_34);
    case_choice = Nil;
    ab_loop_list_ = case_choices;
    values_1 = Nil;
    case_statement = Nil;
    first_choice_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    case_choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    values_1 = FIRST(case_choice);
    case_statement = SECOND(case_choice);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_choice_qm = Nil;
    if ( !TRUEP(first_choice_qm))
	tformat(1,string_constant_35);
    if (EQ(values_1,Qotherwise))
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)9L));
    else {
	value = Nil;
	ab_loop_list__1 = values_1;
	first_value_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_value_qm = Nil;
	if ( !TRUEP(first_value_qm))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	temp = value;
	print_constant(2,temp,data_type_of_non_logical_datum(value));
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)3L));
    write_procedure_statement(case_statement);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return tformat(1,string_constant_36);
}

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* WRITE-REPEAT-STATEMENT */
Object write_repeat_statement(statement)
    Object statement;
{
    Object sub_statement, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,56);
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)7L));
    sub_statement = Nil;
    ab_loop_list_ = CDR(statement);
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_procedure_statement(sub_statement);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)4L));
}

static Object array_constant_11;   /* # */

/* WRITE-EXIT-IF-STATEMENT */
Object write_exit_if_statement(statement)
    Object statement;
{
    x_note_fn_call(161,57);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)8L));
    return write_expression(SECOND(statement));
}

static Object string_constant_37;  /* "FOR ~a = EACH " */

static Object Qfor_each_statement;  /* for-each-statement */

static Object string_constant_38;  /* " DO" */

static Object Qfor_each_in_parallel_statement;  /* for-each-in-parallel-statement */

static Object string_constant_39;  /* " DO IN PARALLEL" */

static Object Qfor_each_in_parallel_race_statement;  /* for-each-in-parallel-race-statement */

static Object string_constant_40;  /* " DO IN PARALLEL UNTIL ONE COMPLETES" */

static Object string_constant_41;  /* "~%  " */

/* WRITE-FOR-EACH-STATEMENT */
Object write_for_each_statement(statement)
    Object statement;
{
    Object gensymed_symbol, statement_name, gensymed_symbol_1, local_name;
    Object designation, statements, role, domain, temp, aref_arg_2, temp_1;
    Object sub_statement, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,58);
    gensymed_symbol = statement;
    statement_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    designation = CAR(gensymed_symbol_1);
    statements = gensymed_symbol;
    tformat(2,string_constant_37,local_name);
    role = role_of_designation(designation);
    domain = domain_of_designation(designation);
    if (domain) {
	print_role(role);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)32L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	print_designation(domain);
    }
    else if (ATOM(role))
	twrite_symbol(1,role);
    else
	print_role(role);
    if (EQ(statement_name,Qfor_each_statement))
	temp_1 = string_constant_38;
    else if (EQ(statement_name,Qfor_each_in_parallel_statement))
	temp_1 = string_constant_39;
    else if (EQ(statement_name,Qfor_each_in_parallel_race_statement))
	temp_1 = string_constant_40;
    else
	temp_1 = Qnil;
    twrite_general_string(temp_1);
    sub_statement = Nil;
    ab_loop_list_ = statements;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    tformat(1,string_constant_41);
    write_procedure_statement(sub_statement);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)4L));
}

static Object string_constant_42;  /* "FOR ~a = " */

static Object Qto;                 /* to */

static Object string_constant_43;  /* " TO " */

static Object string_constant_44;  /* " DOWN TO " */

static Object array_constant_12;   /* # */

static Object Qdo_in_parallel;     /* do-in-parallel */

static Object string_constant_45;  /* "~% END" */

/* PRINT-FOR-NUMERIC-STATEMENT */
Object print_for_numeric_statement(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_name, to_or_down_to, init;
    Object final, by_qm, execution_specifier, statements, temp, sub_statement;
    Object ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,59);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    to_or_down_to = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    init = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    final = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    by_qm = CAR(gensymed_symbol_1);
    execution_specifier = CAR(gensymed_symbol);
    statements = CDR(gensymed_symbol);
    tformat(2,string_constant_42,local_name);
    write_expression(init);
    twrite_general_string(EQ(to_or_down_to,Qto) ? string_constant_43 : 
	    string_constant_44);
    write_expression(final);
    if (by_qm) {
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)4L));
	write_expression(by_qm);
    }
    if (EQ(execution_specifier,Qdo))
	temp = string_constant_38;
    else if (EQ(execution_specifier,Qdo_in_parallel))
	temp = string_constant_39;
    else
	temp = string_constant_40;
    twrite_general_string(temp);
    sub_statement = Nil;
    ab_loop_list_ = statements;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    tformat(1,string_constant_41);
    write_procedure_statement(sub_statement);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return tformat(1,string_constant_45);
}

static Object string_constant_46;  /* "GO TO ~a" */

/* WRITE-GO-TO-STATEMENT */
Object write_go_to_statement(statement)
    Object statement;
{
    x_note_fn_call(161,60);
    return tformat(2,string_constant_46,SECOND(statement));
}

static Object string_constant_47;  /* "~a :" */

/* WRITE-TAG-STATEMENT */
Object write_tag_statement(statement)
    Object statement;
{
    x_note_fn_call(161,61);
    return tformat(2,string_constant_47,SECOND(statement));
}

static Object array_constant_13;   /* # */

/* WRITE-BEGIN-STATEMENT */
Object write_begin_statement(statement)
    Object statement;
{
    Object sub_statement, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,62);
    twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)6L));
    sub_statement = Nil;
    ab_loop_list_ = CDR(statement);
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_procedure_statement(sub_statement);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)4L));
}

static Object Qab_gensym;          /* gensym */

/* WRITE-CALL-STATEMENT */
Object write_call_statement(statement)
    Object statement;
{
    Object new_statement, gensym_list, gensym_list_tail, gensym_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(161,63);
    new_statement = nconc2(gensym_list_2(Qcall_assignment_statement,Nil),
	    CDR(statement));
    write_call_assignment_statement(new_statement);
    gensym_list = new_statement;
    gensym_list_tail = CDR(new_statement);
    if (gensym_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	gensym_cons = gensym_list;
      next_loop:
	inline_note_reclaim_cons(gensym_cons,Qab_gensym);
	if (EQ(gensym_cons,gensym_list_tail))
	    goto end_1;
	else if ( !TRUEP(gensym_cons))
	    goto end_1;
	else
	    gensym_cons = CDR(gensym_cons);
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = gensym_list;
	temp = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_list_tail;
    }
    else {
	temp = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_list;
	temp = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_list_tail;
    }
    M_CDR(gensym_list_tail) = Nil;
    return VALUES_1(Nil);
}

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

/* WRITE-CALL-ASSIGNMENT-STATEMENT */
Object write_call_assignment_statement(statement)
    Object statement;
{
    Object gensymed_symbol, local_names, designation, args, across_qm, name;
    Object ab_loop_list_, first_time_qm, ab_loop_iter_flag_, arg;

    x_note_fn_call(161,64);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    local_names = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    across_qm = CAR(gensymed_symbol);
    if (local_names) {
	name = Nil;
	ab_loop_list_ = local_names;
	first_time_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_time_qm = Nil;
	if ( !TRUEP(first_time_qm))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	tformat(2,string_constant,name);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)3L));
    }
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)5L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = args;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:;
    twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)1L));
    if (across_qm) {
	twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)8L));
	return print_designation(across_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_19;   /* # */

/* WRITE-CALL-NEXT-METHOD-ASSIGNMENT-STATEMENT */
Object write_call_next_method_assignment_statement(statement)
    Object statement;
{
    Object local_names, name, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,65);
    local_names = M_CAR(M_CDR(statement));
    name = Nil;
    ab_loop_list_ = local_names;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    tformat(2,string_constant,name);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_19,
	    FIX((SI_Long)19L));
}

static Object array_constant_20;   /* # */

/* WRITE-SYSTEM-CALL-ASSIGNMENT-STATEMENT */
Object write_system_call_assignment_statement(statement)
    Object statement;
{
    Object gensymed_symbol, local_names, lisp_function_name, args, name;
    Object ab_loop_list_, first_time_qm, ab_loop_iter_flag_, arg;

    x_note_fn_call(161,66);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    local_names = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_function_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    name = Nil;
    ab_loop_list_ = local_names;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    tformat(2,string_constant,name);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)3L));
    twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)12L));
    twrite(lisp_function_name);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = args;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:;
    return twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)1L));
}

static Object array_constant_21;   /* # */

/* WRITE-CALL-NEXT-METHOD-STATEMENT */
Object write_call_next_method_statement(statement)
    Object statement;
{
    x_note_fn_call(161,67);
    return twrite_beginning_of_wide_string(array_constant_21,
	    FIX((SI_Long)16L));
}

/* WRITE-SYSTEM-CALL-STATEMENT */
Object write_system_call_statement(statement)
    Object statement;
{
    Object gensymed_symbol, lisp_function_name, args, arg, ab_loop_list_;
    Object first_time_qm, ab_loop_iter_flag_;

    x_note_fn_call(161,68);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_function_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)12L));
    twrite(lisp_function_name);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)2L));
    arg = Nil;
    ab_loop_list_ = args;
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
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    write_expression(arg);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)1L));
}

static Object array_constant_22;   /* # */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object string_constant_48;  /* "~a " */

/* WRITE-CONCLUDE-THAT-STATEMENT */
Object write_conclude_that_statement(statement)
    Object statement;
{
    Object gensymed_symbol, designation, expression, expiration_qm;
    Object collection_qm, old_value_qm, local_name_qm;

    x_note_fn_call(161,69);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    expiration_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    collection_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    old_value_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)14L));
    print_designation(designation);
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)3L));
    write_expression(expression);
    if (expiration_qm) {
	twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)17L));
	write_expression(expiration_qm);
    }
    if (collection_qm) {
	twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)22L));
	write_expression(collection_qm);
    }
    if (old_value_qm) {
	twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)9L));
	write_expression(old_value_qm);
    }
    if (local_name_qm) {
	twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)11L));
	return tformat(2,string_constant_48,local_name_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_27;   /* # */

/* WRITE-ALLOW-OTHER-PROCESSING-STATEMENT */
Object write_allow_other_processing_statement(ignored_statement)
    Object ignored_statement;
{
    x_note_fn_call(161,70);
    return twrite_beginning_of_wide_string(array_constant_27,
	    FIX((SI_Long)22L));
}

static Object array_constant_28;   /* # */

static Object array_constant_29;   /* # */

static Object string_constant_49;  /* "~%  ~a = " */

static Object array_constant_30;   /* # */

static Object string_constant_50;  /* "~%  IF TIMEOUT THEN " */

static Object string_constant_51;  /* "~%END" */

/* WRITE-COLLECT-DATA-STATEMENT */
Object write_collect_data_statement(statement)
    Object statement;
{
    Object gensymed_symbol, name_expression_pairs, timeout_qm;
    Object timeout_statement_qm, name, expression, ab_loop_list_;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(161,71);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    name_expression_pairs = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    timeout_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    timeout_statement_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_28,FIX((SI_Long)13L));
    if (timeout_qm) {
	twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)19L));
	write_expression(timeout_qm);
	twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)1L));
    }
    name = Nil;
    expression = Nil;
    ab_loop_list_ = name_expression_pairs;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    expression = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(2,string_constant_49,name);
    write_expression(expression);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:;
    if (timeout_statement_qm) {
	tformat(1,string_constant_50);
	write_procedure_statement(timeout_statement_qm);
	twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)1L));
    }
    return tformat(1,string_constant_51);
}

static Object array_constant_31;   /* # */

/* WRITE-DO-IN-PARALLEL-STATEMENT */
Object write_do_in_parallel_statement(statement)
    Object statement;
{
    Object parallel_statement, ab_loop_list_;

    x_note_fn_call(161,72);
    twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)14L));
    parallel_statement = Nil;
    ab_loop_list_ = CDR(statement);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    parallel_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(1,string_constant_41);
    write_procedure_statement(parallel_statement);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:;
    return tformat(1,string_constant_51);
}

static Object array_constant_32;   /* # */

/* WRITE-DO-IN-PARALLEL-UNTIL-ONE-COMPLETES-STATEMENT */
Object write_do_in_parallel_until_one_completes_statement(statement)
    Object statement;
{
    Object parallel_statement, ab_loop_list_;

    x_note_fn_call(161,73);
    twrite_beginning_of_wide_string(array_constant_32,FIX((SI_Long)34L));
    parallel_statement = Nil;
    ab_loop_list_ = CDR(statement);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    parallel_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(1,string_constant_41);
    write_procedure_statement(parallel_statement);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:;
    return tformat(1,string_constant_51);
}

static Object array_constant_33;   /* # */

/* WRITE-WAIT-FOR-STATEMENT */
Object write_wait_for_statement(statement)
    Object statement;
{
    x_note_fn_call(161,74);
    twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)9L));
    return write_expression(SECOND(statement));
}

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

/* WRITE-WAIT-UNTIL-STATEMENT */
Object write_wait_until_statement(statement)
    Object statement;
{
    x_note_fn_call(161,75);
    twrite_beginning_of_wide_string(array_constant_34,FIX((SI_Long)11L));
    write_expression(SECOND(statement));
    twrite_beginning_of_wide_string(array_constant_35,FIX((SI_Long)15L));
    return write_expression(THIRD(statement));
}

/* WRITE-WAIT-UNTIL-EVENT-STATEMENT */
Object write_wait_until_event_statement(statement)
    Object statement;
{
    x_note_fn_call(161,76);
    twrite_beginning_of_wide_string(array_constant_34,FIX((SI_Long)11L));
    return write_expression(SECOND(statement));
}

static Object array_constant_36;   /* # */

/* WRITE-SYSTEM-WAIT-STATEMENT */
Object write_system_wait_statement(statement)
    Object statement;
{
    x_note_fn_call(161,77);
    return twrite_beginning_of_wide_string(array_constant_36,
	    FIX((SI_Long)11L));
}

static Object string_constant_52;  /* "CREATE A(N) ~NE ~a " */

static Object string_constant_53;  /* "CREATE A(N) ~NE " */

static Object array_constant_37;   /* # */

static Object array_constant_38;   /* # */

/* PRINT-CREATE-STATEMENT */
Object print_create_statement(statement)
    Object statement;
{
    Object gensymed_symbol, class_expression, local_name_qm;

    x_note_fn_call(161,78);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    class_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    if (CONSP(class_expression) && CDR(class_expression) && 
	    EQ(CAR(class_expression),Qquote)) {
	if (local_name_qm)
	    return tformat(3,string_constant_52,SECOND(class_expression),
		    local_name_qm);
	else
	    return tformat(2,string_constant_53,SECOND(class_expression));
    }
    else {
	twrite_beginning_of_wide_string(array_constant_37,FIX((SI_Long)19L));
	if (local_name_qm)
	    tformat(2,string_constant_48,local_name_qm);
	twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)22L));
	return write_expression(class_expression);
    }
}

/* PRINT-CREATE-CONNECTION-STATEMENT */
Object print_create_connection_statement(statement)
    Object statement;
{
    Object gensymed_symbol, class_expression, connection_specification;
    Object local_name_qm;

    x_note_fn_call(161,79);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    class_expression = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    connection_specification = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_37,FIX((SI_Long)19L));
    if (local_name_qm)
	tformat(2,string_constant_48,local_name_qm);
    twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)22L));
    return write_expression(class_expression);
}

static Object array_constant_39;   /* # */

static Object array_constant_40;   /* # */

/* PRINT-CREATE-EXPLANATION-STATEMENT */
Object print_create_explanation_statement(statement)
    Object statement;
{
    Object gensymed_symbol, variable_or_parameter_designation, local_name_qm;

    x_note_fn_call(161,80);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    variable_or_parameter_designation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name_qm = CAR(gensymed_symbol);
    twrite_beginning_of_wide_string(array_constant_39,FIX((SI_Long)22L));
    if (local_name_qm)
	tformat(2,string_constant_48,local_name_qm);
    twrite_beginning_of_wide_string(array_constant_40,FIX((SI_Long)4L));
    return print_designation(variable_or_parameter_designation);
}

static Object string_constant_54;  /* " ON ERROR (~a, ~a) " */

/* PRINT-ON-ERROR-STATEMENT */
Object print_on_error_statement(statement)
    Object statement;
{
    Object gensymed_symbol, protected_statement, local1, local2;
    Object error_statement;

    x_note_fn_call(161,81);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    protected_statement = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local2 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    error_statement = CAR(gensymed_symbol);
    write_procedure_statement(protected_statement);
    tformat(3,string_constant_54,local1,local2);
    return write_procedure_statement(error_statement);
}

static Object string_constant_55;  /* "SIGNAL ~NE, ~NE" */

/* PRINT-SIGNAL-STATEMENT */
Object print_signal_statement(statement)
    Object statement;
{
    x_note_fn_call(161,82);
    return tformat(3,string_constant_55,SECOND(statement),THIRD(statement));
}

static Object string_constant_56;  /* " ON ERROR (~a) " */

/* PRINT-ON-ERROR-STATEMENT-NEW */
Object print_on_error_statement_new(statement)
    Object statement;
{
    Object gensymed_symbol, protected_statement, local1, error_statement;

    x_note_fn_call(161,83);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    protected_statement = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    error_statement = CAR(gensymed_symbol);
    write_procedure_statement(protected_statement);
    tformat(2,string_constant_56,local1);
    return write_procedure_statement(error_statement);
}

static Object string_constant_57;  /* "SIGNAL ~NE" */

/* PRINT-SIGNAL-STATEMENT-NEW */
Object print_signal_statement_new(statement)
    Object statement;
{
    x_note_fn_call(161,84);
    return tformat(2,string_constant_57,SECOND(statement));
}

static Object Qannotation;         /* annotation */

static Object Qbegin_activity;     /* begin-activity */

static Object Qmove_from_surrounding_local_var;  /* move-from-surrounding-local-var */

/* ASSIGNMENT-STATEMENT-COMPILER */
Object assignment_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_name, expression;
    Object var_spot, description, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object stack_node, single_read_reference_qm, gensymed_symbol_2;
    Declare_special(3);
    Object result;

    x_note_fn_call(161,85);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)1L)));
    local_name = SECOND(statement);
    expression = THIRD(statement);
    var_spot = Nil;
    description = Nil;
    result = variable_spot_and_description_for_local_name(local_name);
    MVS_2(result,var_spot,description);
    outermost_stack_frame_var_binding_qm = Nil;
    next_stack_frame_var_location = Nil;
    stack_frame_vars_ok_in_procedure_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		0);
	  if (var_spot) {
	      stack_node = compile_stack_expression(expression,
		      getfq_function_no_default(CDR(description),Ktype));
	      single_read_reference_qm = 
		      IFIX(stack_node_references_to_var_spot(stack_node,
		      var_spot)) == (SI_Long)1L ? 
		      stack_node_first_reference_to_var_spot(stack_node,
		      var_spot) : Qnil;
	      if (single_read_reference_qm)
		  SVREF(single_read_reference_qm,FIX((SI_Long)1L)) = 
			  Qmove_from_surrounding_local_var;
	      emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		      var_spot,stack_node));
	  }
	  else
	      procedure_compiler_missing_local_name_error(local_name);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_stack_node_instruction_g2_struct;  /* g2-defstruct-structure-name::stack-node-instruction-g2-struct */

static Object list_constant_3;     /* # */

/* STACK-NODE-REFERENCES-TO-VAR-SPOT */
Object stack_node_references_to_var_spot(stack_node,var_spot)
    Object stack_node, var_spot;
{
    Object temp, args, arg, ab_loop_list_, incff_1_arg;
    SI_Long gensymed_symbol, sum, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(161,86);
    if (SIMPLE_VECTOR_P(stack_node) && EQ(ISVREF(stack_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct) 
	    && memq_function(ISVREF(stack_node,(SI_Long)1L),list_constant_3)) {
	temp = ISVREF(stack_node,(SI_Long)12L);
	temp_1 = FIXNUM_EQ(SECOND(temp),SECOND(var_spot));
    }
    else
	temp_1 = TRUEP(Nil);
    gensymed_symbol = temp_1 ? (SI_Long)1L : (SI_Long)0L;
    args = ISVREF(stack_node,(SI_Long)2L);
    if (args) {
	sum = (SI_Long)0L;
	arg = Nil;
	ab_loop_list_ = args;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	incff_1_arg = stack_node_references_to_var_spot(arg,var_spot);
	sum = sum + IFIX(incff_1_arg);
	goto next_loop;
      end_loop:
	gensymed_symbol_1 = sum;
	goto end_1;
	gensymed_symbol_1 = IFIX(Qnil);
      end_1:;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

static Object Qpush_from_surrounding_local_var;  /* push-from-surrounding-local-var */

static Object list_constant_4;     /* # */

/* STACK-NODE-FIRST-REFERENCE-TO-VAR-SPOT */
Object stack_node_first_reference_to_var_spot(stack_node,var_spot)
    Object stack_node, var_spot;
{
    Object stack_node_inst_qm, operation, temp, arg, ab_loop_list_;
    Object ab_loop_it_;
    char temp_1;

    x_note_fn_call(161,87);
    stack_node_inst_qm = SIMPLE_VECTOR_P(stack_node) ? 
	    (EQ(ISVREF(stack_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct) 
	    ? T : Nil) : Qnil;
    operation = ISVREF(stack_node,(SI_Long)1L);
    if (stack_node_inst_qm && EQ(operation,Qpush_from_surrounding_local_var)) {
	temp = ISVREF(stack_node,(SI_Long)12L);
	temp_1 = FIXNUM_EQ(SECOND(temp),SECOND(var_spot));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	temp = stack_node;
    else if ( !TRUEP(stack_node_inst_qm) || memq_function(operation,
	    list_constant_4)) {
	arg = Nil;
	ab_loop_list_ = ISVREF(stack_node,(SI_Long)2L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = stack_node_first_reference_to_var_spot(arg,var_spot);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant_58;  /* "Returning ~a values, but the procedure is declared to return ~a ~
				    *          values."
				    */

static Object string_constant_59;  /* "A returned value from the inlined procedure ~NF of type ~NT ~
				    *                    could not be assigned into a local-name of type ~NT."
				    */

/* RETURN-STATEMENT-COMPILER */
Object return_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, expressions, expression;
    Object ab_loop_list_, description, ab_loop_list__1, type, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, var_spot, ab_loop_list__2;
    Object return_type, var_spot_type_1, var_spot_name, gensymed_symbol_2;

    x_note_fn_call(161,88);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    if ( !TRUEP(in_inlining_context_qm()))
	emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
		FIX((SI_Long)2L)));
    Return_statement_processed_qm = T;
    expressions = CDR(statement);
    if (FIXNUM_NE(length(expressions),length(Returned_values_description)))
	compiler_error(3,string_constant_58,length(expressions),
		length(Returned_values_description));
    if (EQ(CAR(Lexically_visible_code_bodies),
	    CAR(Code_body_entries_in_compilation)) &&  
	    !TRUEP(in_inlining_context_qm())) {
	expression = Nil;
	ab_loop_list_ = expressions;
	description = Nil;
	ab_loop_list__1 = Returned_values_description;
	type = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	description = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	type = getfq_function_no_default(description,Ktype);
	ab_loopvar__2 = phrase_cons(compile_stack_expression(expression,
		type),Nil);
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
	emit_already_consed_instruction(phrase_list_2(Qreturn_values,temp));
    }
    else if (in_inlining_context_qm()) {
	expression = Nil;
	ab_loop_list_ = expressions;
	description = Nil;
	ab_loop_list__1 = Returned_values_description;
	var_spot = Nil;
	ab_loop_list__2 = inlining_data_recieved_value_compilations_qm();
	return_type = Nil;
	var_spot_type_1 = Nil;
	type = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	description = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_1;
	var_spot = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	return_type = getfq_function_no_default(description,Ktype);
	var_spot_type_1 = var_spot_type(var_spot,
		Lexically_visible_code_bodies);
	type = make_type_specification_intersection(return_type,
		var_spot_type_1);
	if ( !TRUEP(type_specifications_could_intersect_p(return_type,
		var_spot_type_1))) {
	    temp = get_procedure_in_context();
	    compiler_error(4,string_constant_59,temp,return_type,
		    var_spot_type_1);
	}
	else {
	    temp = var_spot;
	    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		    temp,compile_stack_expression(expression,type)));
	}
	goto next_loop_1;
      end_loop_1:
	emit_branch_or_jump(Base_code_body_return_tag);
    }
    else {
	if ( !TRUEP(Generated_var_spots_for_base_code_body_return))
	    generate_var_spots_for_base_code_body_return();
	expression = Nil;
	ab_loop_list_ = expressions;
	description = Nil;
	ab_loop_list__1 = Returned_values_description;
	type = Nil;
	var_spot_name = Nil;
	ab_loop_list__2 = Generated_var_spots_for_base_code_body_return;
	var_spot = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	description = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	type = getfq_function_no_default(description,Ktype);
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	var_spot_name = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	var_spot = variable_spot_and_description_for_local_name(var_spot_name);
	temp = var_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp,compile_stack_expression(expression,type)));
	goto next_loop_2;
      end_loop_2:
	emit_branch_or_jump(Base_code_body_return_tag);
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qreturn_value;       /* return-value */

/* GENERATE-VAR-SPOTS-FOR-BASE-CODE-BODY-RETURN */
Object generate_var_spots_for_base_code_body_return()
{
    Object description, ab_loop_list_, type, new_name, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(161,89);
    description = Nil;
    ab_loop_list_ = Returned_values_description;
    type = Nil;
    new_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    type = getfq_function_no_default(description,Ktype);
    new_name = phrase_cons(Qreturn_value,Nil);
    generate_new_variable_spot(3,type,new_name,
	    CAR(Code_body_entries_in_compilation));
    ab_loopvar__2 = phrase_cons(new_name,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    Generated_var_spots_for_base_code_body_return = ab_loopvar_;
    goto end_1;
    Generated_var_spots_for_base_code_body_return = Qnil;
  end_1:;
    return VALUES_1(Generated_var_spots_for_base_code_body_return);
}

static Object Qtruth_value;        /* truth-value */

/* IF-THEN-STATEMENT-COMPILER */
Object if_then_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, new_tag;
    Object outermost_stack_frame_var_binding_qm, next_stack_frame_var_location;
    Object stack_frame_vars_ok_in_procedure_qm, gensymed_symbol_2;
    Declare_special(3);

    x_note_fn_call(161,90);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)3L)));
    new_tag = generate_new_goto_tag();
    outermost_stack_frame_var_binding_qm = Nil;
    next_stack_frame_var_location = Nil;
    stack_frame_vars_ok_in_procedure_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		0);
	  emit_branch_or_jump_if_not_true(compile_stack_expression(SECOND(statement),
		  Qtruth_value),new_tag);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    compile_procedure_statement(THIRD(statement));
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,new_tag));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* IF-THEN-STATEMENT-GOTO-TAG-RECORDER */
Object if_then_statement_goto_tag_recorder(statement)
    Object statement;
{
    x_note_fn_call(161,91);
    record_goto_tags(THIRD(statement));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* IF-THEN-ELSE-STATEMENT-COMPILER */
Object if_then_else_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object logical_expression, then_statement, else_statement, else_tag;
    Object end_of_if_tag, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Declare_special(3);

    x_note_fn_call(161,92);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)4L)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    logical_expression = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    then_statement = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    else_statement = CAR(gensymed_symbol_2);
    else_tag = generate_new_goto_tag();
    end_of_if_tag = generate_new_goto_tag();
    outermost_stack_frame_var_binding_qm = Nil;
    next_stack_frame_var_location = Nil;
    stack_frame_vars_ok_in_procedure_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		0);
	  emit_branch_or_jump_if_not_true(compile_stack_expression(logical_expression,
		  Qtruth_value),else_tag);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    compile_procedure_statement(then_statement);
    emit_branch_or_jump(end_of_if_tag);
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,else_tag));
    compile_procedure_statement(else_statement);
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    end_of_if_tag));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* IF-THEN-ELSE-STATEMENT-GOTO-TAG-RECORDER */
Object if_then_else_statement_goto_tag_recorder(statement)
    Object statement;
{
    Object gensymed_symbol, then, else_1;

    x_note_fn_call(161,93);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    then = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    else_1 = CAR(gensymed_symbol);
    record_goto_tags(then);
    record_goto_tags(else_1);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qdatum;              /* datum */

static Object string_constant_60;  /* "First CASE value, ~a, was not of a known type!" */

/* CASE-STATEMENT-COMPILER */
Object case_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, key;
    Object case_choices, first_key, compiled_key, first_type;

    x_note_fn_call(161,94);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)5L)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    key = CAR(gensymed_symbol_2);
    case_choices = CDR(gensymed_symbol_2);
    first_key = CAAAR(case_choices);
    compiled_key = compile_stack_expression(key,Qdatum);
    first_type = ISVREF(compiled_key,(SI_Long)6L);
    if ( !TRUEP(first_type))
	compiler_error(2,string_constant_60,first_key);
    else if (type_specification_subtype_p(first_type,Qinteger) && 
	    case_choices_can_be_integer_optimized_p(case_choices))
	compile_integer_optimized_case_statement(compiled_key,case_choices);
    else
	compile_unoptimized_case_statement(compiled_key,first_type,
		case_choices);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CASE-STATEMENT-GOTO-TAG-RECORDER */
Object case_statement_goto_tag_recorder(statement)
    Object statement;
{
    Object case_choice, ab_loop_list_, case_statement;

    x_note_fn_call(161,95);
    case_choice = Nil;
    ab_loop_list_ = CDDR(statement);
    case_statement = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    case_choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    case_statement = SECOND(case_choice);
    record_goto_tags(case_statement);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* CASE-CHOICES-CAN-BE-INTEGER-OPTIMIZED-P */
Object case_choices_can_be_integer_optimized_p(case_choices)
    Object case_choices;
{
    Object value_list_or_otherwise, ab_loop_list_, ab_loop_desetq_, value;
    Object ab_loop_list__1, max_case_value, min_case_value, count_1;
    char temp;

    x_note_fn_call(161,96);
    value_list_or_otherwise = Nil;
    ab_loop_list_ = case_choices;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    value_list_or_otherwise = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = EQ(value_list_or_otherwise,Qotherwise);
    if (temp);
    else {
	value = Nil;
	ab_loop_list__1 = value_list_or_otherwise;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( 
		!TRUEP(type_specification_subtype_p(data_type_of_non_logical_datum(value),
		Qinteger))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
    }
    if ( !temp) {
	temp = TRUEP(Nil);
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(T);
    goto end_2;
    temp = TRUEP(Qnil);
  end_2:;
    if (temp) {
	max_case_value = Most_negative_fixnum;
	min_case_value = Most_positive_fixnum;
	count_1 = FIX((SI_Long)0L);
	value_list_or_otherwise = Nil;
	ab_loop_list_ = case_choices;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	value_list_or_otherwise = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(value_list_or_otherwise,Qotherwise)) {
	    value = Nil;
	    ab_loop_list__1 = value_list_or_otherwise;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    value = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    max_case_value = FIXNUM_MAX(max_case_value,value);
	    min_case_value = FIXNUM_MIN(min_case_value,value);
	    count_1 = FIXNUM_ADD1(count_1);
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(IFIX(count_1) * (SI_Long)2L > 
		IFIX(FIXNUM_MINUS(max_case_value,min_case_value)) ? T : Nil);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_61;  /* "This CASE statement had no values to dispatch upon." */

static Object string_constant_62;  /* "A CASE clause had no values associated with it." */

static Object string_constant_63;  /* "The CASE key value OTHERWISE was the key for a clause ~
				    *                   other than the last one in the CASE statement."
				    */

static Object Qcase_dispatch;      /* case-dispatch */

static Object list_constant_5;     /* # */

static Object string_constant_64;  /* "CASE key value did not match any of the CASE statement choices." */

/* COMPILE-INTEGER-OPTIMIZED-CASE-STATEMENT */
Object compile_integer_optimized_case_statement(compiled_key,case_choices)
    Object compiled_key, case_choices;
{
    Object max_choice, min_choice, count_1, tag_list, tag_and_forms_list;
    Object else_tag, error_tag, end_of_case_tag, value_list_or_otherwise;
    Object ab_loop_list_, ab_loop_desetq_, value, ab_loop_list__1;
    Object case_choice_cons, case_choice, value_statement, case_choice_tag;
    Object temp, tag_cons, gensymed_symbol, gensymed_symbol_1, tag, statement;
    Object temp_1;

    x_note_fn_call(161,97);
    max_choice = Most_negative_fixnum;
    min_choice = Most_positive_fixnum;
    count_1 = FIX((SI_Long)0L);
    tag_list = Nil;
    tag_and_forms_list = Nil;
    else_tag = Nil;
    error_tag = Nil;
    end_of_case_tag = generate_new_goto_tag();
    value_list_or_otherwise = Nil;
    ab_loop_list_ = case_choices;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    value_list_or_otherwise = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(value_list_or_otherwise,Qotherwise)) {
	value = Nil;
	ab_loop_list__1 = value_list_or_otherwise;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	max_choice = FIXNUM_MAX(max_choice,value);
	min_choice = FIXNUM_MIN(min_choice,value);
	count_1 = FIXNUM_ADD1(count_1);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    if (IFIX(count_1) == (SI_Long)0L)
	compiler_error(1,string_constant_61);
    tag_list = make_phrase_list(FIXNUM_ADD1(FIXNUM_MINUS(max_choice,
	    min_choice)));
    fill(2,tag_list,Nil);
    case_choice_cons = case_choices;
    case_choice = Nil;
    value_list_or_otherwise = Nil;
    value_statement = Nil;
    case_choice_tag = Nil;
  next_loop_2:
    if ( !TRUEP(case_choice_cons))
	goto end_loop_2;
    case_choice = CAR(case_choice_cons);
    value_list_or_otherwise = CAR(case_choice);
    value_statement = SECOND(case_choice);
    case_choice_tag = generate_new_goto_tag();
    if ( !TRUEP(value_list_or_otherwise))
	compiler_error(1,string_constant_62);
    else if (EQ(value_list_or_otherwise,Qotherwise)) {
	if (CDR(case_choice_cons))
	    compiler_error(1,string_constant_63);
	else_tag = case_choice_tag;
    }
    else {
	value = Nil;
	ab_loop_list_ = value_list_or_otherwise;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = nthcdr(FIXNUM_MINUS(value,min_choice),tag_list);
	M_CAR(temp) = case_choice_tag;
	goto next_loop_3;
      end_loop_3:;
    }
    tag_and_forms_list = phrase_cons(phrase_cons(case_choice_tag,
	    value_statement),tag_and_forms_list);
    case_choice_cons = M_CDR(case_choice_cons);
    goto next_loop_2;
  end_loop_2:;
    if ( !TRUEP(else_tag)) {
	error_tag = generate_new_goto_tag();
	else_tag = error_tag;
    }
    tag_cons = tag_list;
  next_loop_4:
    if ( !TRUEP(tag_cons))
	goto end_loop_4;
    if ( !TRUEP(CAR(tag_cons)))
	M_CAR(tag_cons) = else_tag;
    tag_cons = M_CDR(tag_cons);
    goto next_loop_4;
  end_loop_4:;
    gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qcase_dispatch;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = compiled_key;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = min_choice;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = FIXNUM_ADD1(FIXNUM_MINUS(max_choice,min_choice));
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = else_tag;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = tag_list;
    emit_already_consed_instruction(gensymed_symbol);
    tag = Nil;
    statement = Nil;
    ab_loop_list_ = nreverse(tag_and_forms_list);
    ab_loop_desetq_ = Nil;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    tag = CAR(ab_loop_desetq_);
    statement = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,tag));
    compile_procedure_statement(statement);
    emit_branch_or_jump(end_of_case_tag);
    goto next_loop_5;
  end_loop_5:;
    if (error_tag) {
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		error_tag));
	temp_1 = compile_stack_expression(list_constant_5,Qsymbol);
	emit_already_consed_instruction(phrase_list_3(Qsignal_error,temp_1,
		compile_stack_expression(string_constant_64,Qtext)));
    }
    return emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    end_of_case_tag));
}

static Object string_constant_65;  /* "Unknown CASE value type for ~a" */

static Object string_constant_66;  /* "The data type of the CASE value ~NC, ~NT, ~
				    *                               was not compatible with the type ~NT of the ~
				    *                               key expression for the CASE statement."
				    */

static Object string_constant_67;  /* "No values in CASE clause." */

static Object Qab_or;              /* or */

/* COMPILE-UNOPTIMIZED-CASE-STATEMENT */
Object compile_unoptimized_case_statement(compiled_key,first_type,case_choices)
    Object compiled_key, first_type, case_choices;
{
    Object key_spot, end_of_case_tag, choice_cons, case_choice;
    Object value_list_or_otherwise, value_statement, next_tag, equal_clauses;
    Object value, ab_loop_list_, evalable_value, type, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(161,98);
    key_spot = generate_new_variable_spot(1,first_type);
    end_of_case_tag = generate_new_goto_tag();
    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
	    key_spot,compiled_key));
    choice_cons = case_choices;
    case_choice = Nil;
    value_list_or_otherwise = Nil;
    value_statement = Nil;
    next_tag = Nil;
    equal_clauses = Nil;
  next_loop:
    if ( !TRUEP(choice_cons))
	goto end_loop;
    case_choice = CAR(choice_cons);
    value_list_or_otherwise = CAR(case_choice);
    value_statement = SECOND(case_choice);
    next_tag = generate_new_goto_tag();
    if (EQ(value_list_or_otherwise,Qotherwise))
	equal_clauses = value_list_or_otherwise;
    else {
	value = Nil;
	ab_loop_list_ = value_list_or_otherwise;
	evalable_value = Nil;
	type = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	evalable_value = SYMBOLP(value) ? phrase_list_2(Qquote,value) : value;
	type = data_type_of_non_logical_datum(value);
	ab_loopvar__2 = phrase_cons(phrase_list_3(Qnum_eq,key_spot,
		evalable_value),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if ( !TRUEP(type))
	    compiler_error(2,string_constant_65,value);
	else if ( !TRUEP(type_specifications_could_intersect_p(type,
		first_type)))
	    compiler_error(5,string_constant_66,value,type,type,first_type);
	goto next_loop_1;
      end_loop_1:
	equal_clauses = ab_loopvar_;
	goto end_1;
	equal_clauses = Qnil;
      end_1:;
    }
    if ( !TRUEP(equal_clauses))
	compiler_error(1,string_constant_67);
    else if (EQ(equal_clauses,Qotherwise)) {
	if (CDR(choice_cons))
	    compiler_error(1,string_constant_63);
    }
    else {
	temp = compile_stack_expression( !TRUEP(CDR(equal_clauses)) ? 
		CAR(equal_clauses) : phrase_cons(Qab_or,equal_clauses),
		Qtruth_value);
	emit_branch_or_jump_if_not_true(temp,next_tag);
    }
    compile_procedure_statement(value_statement);
    emit_branch_or_jump(end_of_case_tag);
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,next_tag));
    choice_cons = M_CDR(choice_cons);
    goto next_loop;
  end_loop:;
    temp = compile_stack_expression(list_constant_5,Qsymbol);
    emit_already_consed_instruction(phrase_list_3(Qsignal_error,temp,
	    compile_stack_expression(string_constant_64,Qtext)));
    return emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    end_of_case_tag));
}

DEFINE_VARIABLE_WITH_SYMBOL(Tightest_end_of_loop_tag, Qtightest_end_of_loop_tag);

/* REPEAT-STATEMENT-COMPILER */
Object repeat_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, lexically_visible_goto_tags;
    Object iteration_statement, ab_loop_list_, start_of_loop_tag;
    Object tightest_end_of_loop_tag, sub_statement, gensymed_symbol_2;
    Declare_special(2);

    x_note_fn_call(161,99);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)6L)));
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    1);
      iteration_statement = Nil;
      ab_loop_list_ = CDR(statement);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      iteration_statement = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      record_goto_tags(iteration_statement);
      goto next_loop;
    end_loop:;
      start_of_loop_tag = generate_new_goto_tag();
      tightest_end_of_loop_tag = generate_new_goto_tag();
      PUSH_SPECIAL_WITH_SYMBOL(Tightest_end_of_loop_tag,Qtightest_end_of_loop_tag,tightest_end_of_loop_tag,
	      0);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		start_of_loop_tag));
	sub_statement = Nil;
	ab_loop_list_ = CDR(statement);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	sub_statement = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	compile_procedure_statement(sub_statement);
	goto next_loop_1;
      end_loop_1:;
	emit_branch_or_jump(start_of_loop_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		Tightest_end_of_loop_tag));
      POP_SPECIAL();
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_68;  /* "Exit if statement was not within an iteration form." */

/* EXIT-IF-STATEMENT-COMPILER */
Object exit_if_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(161,100);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)7L)));
    if ( !TRUEP(Tightest_end_of_loop_tag)) {
	compiler_error(1,string_constant_68);
	compile_stack_expression(SECOND(statement),Qtruth_value);
    }
    else {
	temp = compile_stack_expression(SECOND(statement),Qtruth_value);
	emit_branch_or_jump_if_true(temp,Tightest_end_of_loop_tag);
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_69;  /* "The local name ~a is declared to be of type ~NT but the ~
				    *                      iteration reference returns values of type ~NT."
				    */

static Object string_constant_70;  /* "All local names for procedures must be declared at the top of ~
				    *                the procedure definition.  This designation could not be ~
				    *                compiled: ~ND."
				    */

static Object Qrole_server;        /* role-server */

static Object Qrequired_domain_types_of_role;  /* required-domain-types-of-role */

static Object array_constant_41;   /* # */

static Object string_constant_71;  /* ", ~a, did not match the required count, ~a" */

static Object Qopen_role_iteration_no_domain;  /* open-role-iteration-no-domain */

static Object Qopen_role_iteration;  /* open-role-iteration */

static Object Qserve_next_iteration_value;  /* serve-next-iteration-value */

static Object Qclose_iteration;    /* close-iteration */

/* FOR-EACH-STATEMENT-COMPILER */
Object for_each_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, local_name, designation, statements;
    Object lexically_visible_goto_tags, iteration_statement, ab_loop_list_;
    Object tightest_end_of_loop_tag, next_loop_tag, continuation_spot;
    Object designation_type_qm, role, domain_list, required_domain_types;
    Object local_var_type, value_spot, description, role_1, role_car;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, car_new_value, domain, type_cons, type;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp_1, sub_statement;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(161,101);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)8L)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    gensymed_symbol_3 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_name = CAR(gensymed_symbol_3);
    gensymed_symbol_3 = CDR(gensymed_symbol_3);
    designation = CAR(gensymed_symbol_3);
    statements = gensymed_symbol_2;
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    6);
      iteration_statement = Nil;
      ab_loop_list_ = statements;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      iteration_statement = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      record_goto_tags(iteration_statement);
      goto next_loop;
    end_loop:;
      tightest_end_of_loop_tag = generate_new_goto_tag();
      next_loop_tag = generate_new_goto_tag();
      continuation_spot = generate_new_variable_spot(1,
	      make_type_specification_for_iteration_state());
      designation_type_qm = type_specification_of_designation(designation);
      role = role_of_designation(designation);
      domain_list = domain_list_of_designation(designation);
      required_domain_types = Nil;
      local_var_type = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Tightest_end_of_loop_tag,Qtightest_end_of_loop_tag,tightest_end_of_loop_tag,
	      5);
	result = variable_spot_and_description_for_local_name(local_name);
	MVS_2(result,value_spot,description);
	if ( !TRUEP(value_spot)) {
	    procedure_compiler_missing_local_name_error(local_name);
	    local_var_type = Qitem_or_datum;
	}
	else {
	    local_var_type = getfq_function_no_default(CDR(description),Ktype);
	    if (designation_type_qm &&  
		    !TRUEP(type_specifications_could_intersect_p(designation_type_qm,
		    local_var_type)))
		compiler_error(4,string_constant_69,local_name,
			local_var_type,designation_type_qm);
	}
	if ( !TRUEP(simple_role_p(role))) {
	    compiler_error(2,string_constant_70,designation);
	    role = simple_role_of_role(role);
	}
	if ( !SYMBOLP(role)) {
	    role_1 = role;
	    role_car = M_CAR(role_1);
	    gensymed_symbol_2 = EQ(role_car,Qrole_server) ? 
		    M_CAR(M_CDR(role_1)) : role_car;
	    required_domain_types = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_2),
		    Qrequired_domain_types_of_role);
	}
	else
	    required_domain_types = Nil;
	if (FIXNUM_NE(length(required_domain_types),length(domain_list))) {
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
		      twrite_beginning_of_wide_string(array_constant_41,
			      FIX((SI_Long)27L));
		      print_role(role);
		      tformat(3,string_constant_71,length(domain_list),
			      length(required_domain_types));
		      candidate_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    a_string = Nil;
	    ab_loop_list_ = Compiler_errors;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    a_string = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (string_eq_w(a_string,candidate_string)) {
		temp = TRUEP(T);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp)
		reclaim_text_string(candidate_string);
	    else
		Compiler_errors = phrase_cons(candidate_string,
			Compiler_errors);
	}
	if ( !TRUEP(domain_list)) {
	    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
	    gensymed_symbol_3 = gensymed_symbol_2;
	    M_CAR(gensymed_symbol_3) = Qopen_role_iteration_no_domain;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = role;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = continuation_spot;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = value_spot;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = local_var_type;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = designation_type_qm;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    car_new_value = Tightest_end_of_loop_tag;
	    M_CAR(gensymed_symbol_3) = car_new_value;
	    emit_already_consed_instruction(gensymed_symbol_2);
	}
	else {
	    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)7L));
	    gensymed_symbol_3 = gensymed_symbol_2;
	    M_CAR(gensymed_symbol_3) = Qopen_role_iteration;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = role;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = continuation_spot;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = value_spot;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = local_var_type;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    M_CAR(gensymed_symbol_3) = designation_type_qm;
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    car_new_value = Tightest_end_of_loop_tag;
	    M_CAR(gensymed_symbol_3) = car_new_value;
	    domain = Nil;
	    ab_loop_list_ = domain_list;
	    type_cons = required_domain_types;
	    type = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    domain = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		type_cons = CDR(type_cons);
	    temp_1 = CAR(type_cons);
	    if (temp_1);
	    else
		temp_1 = Qitem_or_datum;
	    type = temp_1;
	    ab_loopvar__2 = phrase_cons(compile_stack_expression(domain,
		    type),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = ab_loopvar_;
	    goto end_2;
	    temp_1 = Qnil;
	  end_2:;
	    emit_already_consed_instruction(nconc2(gensymed_symbol_2,temp_1));
	}
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		next_loop_tag));
	sub_statement = Nil;
	ab_loop_list_ = statements;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	sub_statement = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	compile_procedure_statement(sub_statement);
	goto next_loop_3;
      end_loop_3:;
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_3 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_3) = Qserve_next_iteration_value;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = continuation_spot;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = value_spot;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = local_var_type;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	M_CAR(gensymed_symbol_3) = designation_type_qm;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	car_new_value = Tightest_end_of_loop_tag;
	M_CAR(gensymed_symbol_3) = car_new_value;
	emit_already_consed_instruction(gensymed_symbol_2);
	emit_branch_or_jump(next_loop_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		Tightest_end_of_loop_tag));
	emit_already_consed_instruction(phrase_list_2(Qclose_iteration,
		continuation_spot));
      POP_SPECIAL();
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FOR-EACH-IN-PARALLEL-STATEMENT-COMPILER */
Object for_each_in_parallel_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,102);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    compile_for_each_parallel(statement);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qprocedure_flags;    /* procedure-flags */

static Object Qclose_code_body;    /* close-code-body */

static Object Qcall_scheduled_code_body;  /* call-scheduled-code-body */

static Object Qallow_other_processing;  /* allow-other-processing */

static Object Qpause_if_called_code_bodies;  /* pause-if-called-code-bodies */

static Object Qwait_for_called_code_bodies;  /* wait-for-called-code-bodies */

/* COMPILE-FOR-EACH-PARALLEL */
Object compile_for_each_parallel(statement)
    Object statement;
{
    Object gensymed_symbol, statement_name, gensymed_symbol_1, local_name;
    Object designation, statements, sub_class_bit_vector, temp_1;
    Object svref_new_value, lexically_visible_goto_tags;
    Object tightest_end_of_loop_tag, end_of_launch_tag, next_loop_tag;
    Object continuation_spot, code_body_number_for_iteration;
    Object iteration_launch_var_spot, local_var_type, designation_type_qm;
    Object domain_list, role, required_domain_list, value_spot, description;
    Object temp_2, lexically_visible_code_bodies;
    Object outermost_stack_frame_var_binding_qm, next_stack_frame_var_location;
    Object stack_frame_vars_ok_in_procedure_qm, iteration_statement;
    Object ab_loop_list_, role_1, role_car, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object candidate_string, a_string, domain, type_cons, type, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp, until_one_completes_qm;
    Declare_special(7);
    Object result;

    x_note_fn_call(161,103);
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)9L)));
    gensymed_symbol = statement;
    statement_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    designation = CAR(gensymed_symbol_1);
    statements = gensymed_symbol;
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	temp_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(temp_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    6);
      tightest_end_of_loop_tag = generate_new_goto_tag();
      PUSH_SPECIAL_WITH_SYMBOL(Tightest_end_of_loop_tag,Qtightest_end_of_loop_tag,tightest_end_of_loop_tag,
	      5);
	end_of_launch_tag = generate_new_goto_tag();
	next_loop_tag = generate_new_goto_tag();
	continuation_spot = generate_new_variable_spot(1,
		make_type_specification_for_iteration_state());
	until_one_completes_qm = EQ(statement_name,
		Qfor_each_in_parallel_race_statement);
	code_body_number_for_iteration = FIX((SI_Long)0L);
	iteration_launch_var_spot = Nil;
	local_var_type = Nil;
	designation_type_qm = type_specification_of_designation(designation);
	domain_list = domain_list_of_designation(designation);
	role = role_of_designation(designation);
	required_domain_list = Nil;
	result = variable_spot_and_description_for_local_name(local_name);
	MVS_2(result,value_spot,description);
	if ( !TRUEP(value_spot)) {
	    procedure_compiler_missing_local_name_error(local_name);
	    local_var_type = Qitem_or_datum;
	}
	else {
	    local_var_type = getfq_function_no_default(CDR(description),Ktype);
	    if (designation_type_qm &&  
		    !TRUEP(type_specifications_could_intersect_p(designation_type_qm,
		    local_var_type)))
		compiler_error(4,string_constant_69,local_name,
			local_var_type,designation_type_qm);
	}
	gensymed_symbol = CAR(Lexically_visible_code_bodies);
	temp_2 = phrase_cons(phrase_list_3(local_name,Ktype,
		local_var_type),Nil);
	gensymed_symbol = make_compiler_code_body_entry_1(temp_2,
		gensymed_symbol ? position(2,gensymed_symbol,
		Code_body_entries_in_compilation) : Nil);
	lexically_visible_code_bodies = phrase_cons(gensymed_symbol,
		Lexically_visible_code_bodies);
	PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
		4);
	  Code_body_entries_in_compilation = 
		  nconc2(Code_body_entries_in_compilation,
		  phrase_cons(gensymed_symbol,Nil));
	  check_for_new_code_body_errors();
	  if (inlining_context_qm())
	      adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
	  outermost_stack_frame_var_binding_qm = Nil;
	  next_stack_frame_var_location = Nil;
	  stack_frame_vars_ok_in_procedure_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		      1);
		lexically_visible_goto_tags = Lexically_visible_goto_tags;
		PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
			0);
		  code_body_number_for_iteration = position(2,
			  CAR(Lexically_visible_code_bodies),
			  Code_body_entries_in_compilation);
		  iteration_statement = Nil;
		  ab_loop_list_ = statements;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  iteration_statement = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  record_goto_tags(iteration_statement);
		  goto next_loop;
		end_loop:;
		  iteration_statement = Nil;
		  ab_loop_list_ = statements;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  iteration_statement = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  compile_procedure_statement(iteration_statement);
		  goto next_loop_1;
		end_loop_1:;
		  if (until_one_completes_qm)
		      emit_branch_or_jump(Tightest_end_of_loop_tag);
		  else
		      emit_already_consed_instruction(phrase_cons(Qclose_code_body,
			      Nil));
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	iteration_launch_var_spot = generate_new_variable_spot(1,
		local_var_type);
	if ( !TRUEP(simple_role_p(role))) {
	    compiler_error(2,string_constant_70,designation);
	    role = simple_role_of_role(role);
	}
	if ( !SYMBOLP(role)) {
	    role_1 = role;
	    role_car = M_CAR(role_1);
	    gensymed_symbol = EQ(role_car,Qrole_server) ? 
		    M_CAR(M_CDR(role_1)) : role_car;
	    required_domain_list = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qrequired_domain_types_of_role);
	}
	else
	    required_domain_list = Nil;
	if (FIXNUM_NE(length(required_domain_list),length(domain_list))) {
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
		      twrite_beginning_of_wide_string(array_constant_41,
			      FIX((SI_Long)27L));
		      print_role(role);
		      tformat(3,string_constant_71,length(domain_list),
			      length(required_domain_list));
		      candidate_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    a_string = Nil;
	    ab_loop_list_ = Compiler_errors;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    a_string = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (string_eq_w(a_string,candidate_string)) {
		temp = TRUEP(T);
		goto end_1;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp)
		reclaim_text_string(candidate_string);
	    else
		Compiler_errors = phrase_cons(candidate_string,
			Compiler_errors);
	}
	if ( !TRUEP(domain_list)) {
	    gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qopen_role_iteration_no_domain;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = role;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = continuation_spot;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = iteration_launch_var_spot;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = local_var_type;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = designation_type_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp_1 = Tightest_end_of_loop_tag;
	    M_CAR(gensymed_symbol_1) = temp_1;
	    emit_already_consed_instruction(gensymed_symbol);
	}
	else {
	    gensymed_symbol = make_phrase_list(FIX((SI_Long)7L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qopen_role_iteration;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = role;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = continuation_spot;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = iteration_launch_var_spot;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = local_var_type;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = designation_type_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp_1 = Tightest_end_of_loop_tag;
	    M_CAR(gensymed_symbol_1) = temp_1;
	    domain = Nil;
	    ab_loop_list_ = domain_list;
	    type_cons = required_domain_list;
	    type = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    domain = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		type_cons = CDR(type_cons);
	    temp_2 = CAR(type_cons);
	    if (temp_2);
	    else
		temp_2 = Qitem_or_datum;
	    type = temp_2;
	    ab_loopvar__2 = phrase_cons(compile_stack_expression(domain,
		    type),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:
	    temp_2 = ab_loopvar_;
	    goto end_2;
	    temp_2 = Qnil;
	  end_2:;
	    emit_already_consed_instruction(nconc2(gensymed_symbol,temp_2));
	}
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		next_loop_tag));
	temp_2 = code_body_number_for_iteration;
	emit_already_consed_instruction(phrase_list_3(Qcall_scheduled_code_body,
		temp_2,compile_stack_expression(iteration_launch_var_spot,
		local_var_type)));
	emit_already_consed_instruction(phrase_cons(Qallow_other_processing,
		Nil));
	gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qserve_next_iteration_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = continuation_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = iteration_launch_var_spot;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = local_var_type;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = designation_type_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = end_of_launch_tag;
	emit_already_consed_instruction(gensymed_symbol);
	emit_branch_or_jump(next_loop_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		end_of_launch_tag));
	if (until_one_completes_qm)
	    emit_already_consed_instruction(phrase_cons(Qpause_if_called_code_bodies,
		    Nil));
	else
	    emit_already_consed_instruction(phrase_cons(Qwait_for_called_code_bodies,
		    Nil));
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		Tightest_end_of_loop_tag));
	result = emit_already_consed_instruction(phrase_list_2(Qclose_iteration,
		continuation_spot));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* FOR-EACH-IN-PARALLEL-RACE-STATEMENT-COMPILER */
Object for_each_in_parallel_race_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,104);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)10L)));
    compile_for_each_parallel(statement);
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* FOR-NUMERIC-STATEMENT-COMPILER */
Object for_numeric_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,105);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    if (EQ(THIRD(statement),Qdo)) {
	emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
		FIX((SI_Long)8L)));
	compile_sequential_for_numeric_statement(statement);
    }
    else {
	emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
		FIX((SI_Long)9L)));
	compile_parallel_for_numeric_statement(statement);
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_72;  /* "The iteration variable ~a was of type ~NT instead of being ~
				    *                  of type ~NT."
				    */

/* COMPILE-SEQUENTIAL-FOR-NUMERIC-STATEMENT */
Object compile_sequential_for_numeric_statement(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_name, to_or_down_to, init;
    Object final, by_qm, statements, lexically_visible_goto_tags;
    Object iteration_statement, ab_loop_list_, tightest_end_of_loop_tag;
    Object next_loop_tag, type, final_spot, step_value, iter_spot, description;
    Object temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(161,106);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    to_or_down_to = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    init = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    final = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    by_qm = CAR(gensymed_symbol_1);
    gensymed_symbol = CDR(gensymed_symbol);
    statements = gensymed_symbol;
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    1);
      iteration_statement = Nil;
      ab_loop_list_ = statements;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      iteration_statement = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      record_goto_tags(iteration_statement);
      goto next_loop;
    end_loop:;
      tightest_end_of_loop_tag = generate_new_goto_tag();
      next_loop_tag = generate_new_goto_tag();
      type = Nil;
      final_spot = Nil;
      step_value = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Tightest_end_of_loop_tag,Qtightest_end_of_loop_tag,tightest_end_of_loop_tag,
	      0);
	result = variable_spot_and_description_for_local_name(local_name);
	MVS_2(result,iter_spot,description);
	if ( !TRUEP(iter_spot)) {
	    procedure_compiler_missing_local_name_error(local_name);
	    type = Qnumber;
	    iter_spot = generate_new_variable_spot(1,type);
	}
	else
	    type = getfq_function_no_default(CDR(description),Ktype);
	if ( !TRUEP(type_specification_subtype_p(type,Qnumber))) {
	    if ( !(EQ(type,Qdatum) || EQ(type,Qitem_or_datum)))
		compiler_error(4,string_constant_72,local_name,type,Qnumber);
	    type = Qnumber;
	}
	final_spot = generate_new_variable_spot(1,type);
	if (by_qm)
	    step_value = generate_new_variable_spot(1,type);
	else if (EQ(to_or_down_to,Qto))
	    step_value = FIX((SI_Long)1L);
	else
	    step_value = FIX((SI_Long)-1L);
	temp = iter_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp,compile_stack_expression(init,type)));
	temp = final_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp,compile_stack_expression(final,type)));
	if (by_qm) {
	    temp = step_value;
	    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		    temp,compile_stack_expression(by_qm,type)));
	}
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		next_loop_tag));
	temp = compile_stack_expression(phrase_list_3(EQ(to_or_down_to,
		Qto) ? Qnum_le : Qnum_ge,iter_spot,final_spot),Qtruth_value);
	emit_branch_or_jump_if_not_true(temp,Tightest_end_of_loop_tag);
	iteration_statement = Nil;
	ab_loop_list_ = statements;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	iteration_statement = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	compile_procedure_statement(iteration_statement);
	goto next_loop_1;
      end_loop_1:;
	temp = iter_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp,compile_stack_expression(phrase_list_3(Qplus,
		iter_spot,step_value),type)));
	emit_branch_or_jump(next_loop_tag);
	result = emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		Tightest_end_of_loop_tag));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qdo_in_parallel_until_one_completes;  /* do-in-parallel-until-one-completes */

static Object string_constant_73;  /* "The iteration variable ~a was of type ~NT instead of being ~
				    *                  of type ~NF."
				    */

/* COMPILE-PARALLEL-FOR-NUMERIC-STATEMENT */
Object compile_parallel_for_numeric_statement(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_name, to_or_down_to, init;
    Object final, by_qm, execution_specifier, statements, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, lexically_visible_goto_tags;
    Object tightest_end_of_loop_tag, end_of_launch_tag, next_loop_tag;
    Object code_body_number_for_iteration, type, iteration_launch_var_spot;
    Object final_spot, step_value, value_spot, description, temp_1;
    Object lexically_visible_code_bodies, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object iteration_statement, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp, until_one_completes_qm;
    Declare_special(7);
    Object result;

    x_note_fn_call(161,107);
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    local_name = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    to_or_down_to = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    init = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    final = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    by_qm = CAR(gensymed_symbol_1);
    execution_specifier = CAR(gensymed_symbol);
    statements = CDR(gensymed_symbol);
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    6);
      tightest_end_of_loop_tag = generate_new_goto_tag();
      end_of_launch_tag = generate_new_goto_tag();
      next_loop_tag = generate_new_goto_tag();
      until_one_completes_qm = EQ(execution_specifier,
	      Qdo_in_parallel_until_one_completes);
      code_body_number_for_iteration = FIX((SI_Long)0L);
      type = Nil;
      iteration_launch_var_spot = Nil;
      final_spot = Nil;
      step_value = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Tightest_end_of_loop_tag,Qtightest_end_of_loop_tag,tightest_end_of_loop_tag,
	      5);
	result = variable_spot_and_description_for_local_name(local_name);
	MVS_2(result,value_spot,description);
	if ( !TRUEP(value_spot)) {
	    procedure_compiler_missing_local_name_error(local_name);
	    type = Qnumber;
	}
	else
	    type = getfq_function_no_default(CDR(description),Ktype);
	if ( !TRUEP(type_specification_subtype_p(type,Qnumber))) {
	    if ( !(EQ(type,Qdatum) || EQ(type,Qitem_or_datum)))
		compiler_error(4,string_constant_73,local_name,type,Qnumber);
	    type = Qnumber;
	}
	gensymed_symbol = CAR(Lexically_visible_code_bodies);
	temp_1 = phrase_cons(phrase_list_3(local_name,Ktype,type),Nil);
	gensymed_symbol = make_compiler_code_body_entry_1(temp_1,
		gensymed_symbol ? position(2,gensymed_symbol,
		Code_body_entries_in_compilation) : Nil);
	lexically_visible_code_bodies = phrase_cons(gensymed_symbol,
		Lexically_visible_code_bodies);
	PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
		4);
	  Code_body_entries_in_compilation = 
		  nconc2(Code_body_entries_in_compilation,
		  phrase_cons(gensymed_symbol,Nil));
	  check_for_new_code_body_errors();
	  if (inlining_context_qm())
	      adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
	  outermost_stack_frame_var_binding_qm = Nil;
	  next_stack_frame_var_location = Nil;
	  stack_frame_vars_ok_in_procedure_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		      1);
		lexically_visible_goto_tags = Lexically_visible_goto_tags;
		PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
			0);
		  code_body_number_for_iteration = position(2,
			  CAR(Lexically_visible_code_bodies),
			  Code_body_entries_in_compilation);
		  iteration_statement = Nil;
		  ab_loop_list_ = statements;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  iteration_statement = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  record_goto_tags(iteration_statement);
		  goto next_loop;
		end_loop:;
		  iteration_statement = Nil;
		  ab_loop_list_ = statements;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  iteration_statement = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  compile_procedure_statement(iteration_statement);
		  goto next_loop_1;
		end_loop_1:;
		  if (until_one_completes_qm)
		      emit_branch_or_jump(Tightest_end_of_loop_tag);
		  else
		      emit_already_consed_instruction(phrase_cons(Qclose_code_body,
			      Nil));
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	iteration_launch_var_spot = generate_new_variable_spot(1,type);
	final_spot = generate_new_variable_spot(1,type);
	if (by_qm)
	    step_value = generate_new_variable_spot(1,type);
	else if (EQ(to_or_down_to,Qto))
	    step_value = FIX((SI_Long)1L);
	else
	    step_value = FIX((SI_Long)-1L);
	temp_1 = iteration_launch_var_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp_1,compile_stack_expression(init,type)));
	temp_1 = final_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp_1,compile_stack_expression(final,type)));
	if (by_qm) {
	    temp_1 = step_value;
	    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		    temp_1,compile_stack_expression(by_qm,type)));
	}
	temp_1 = compile_stack_expression(phrase_list_3(EQ(to_or_down_to,
		Qto) ? Qnum_le : Qnum_ge,iteration_launch_var_spot,
		final_spot),Qtruth_value);
	emit_branch_or_jump_if_not_true(temp_1,Tightest_end_of_loop_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		next_loop_tag));
	temp_1 = code_body_number_for_iteration;
	emit_already_consed_instruction(phrase_list_3(Qcall_scheduled_code_body,
		temp_1,compile_stack_expression(iteration_launch_var_spot,
		type)));
	emit_already_consed_instruction(phrase_cons(Qallow_other_processing,
		Nil));
	temp_1 = iteration_launch_var_spot;
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		temp_1,compile_stack_expression(phrase_list_3(Qplus,
		iteration_launch_var_spot,step_value),type)));
	emit_branch_or_jump_if_not_true(compile_stack_expression(phrase_list_3(EQ(to_or_down_to,
		Qto) ? Qnum_le : Qnum_ge,iteration_launch_var_spot,
		final_spot),Qtruth_value),end_of_launch_tag);
	emit_branch_or_jump(next_loop_tag);
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		end_of_launch_tag));
	if (until_one_completes_qm)
	    emit_already_consed_instruction(phrase_cons(Qpause_if_called_code_bodies,
		    Nil));
	else
	    emit_already_consed_instruction(phrase_cons(Qwait_for_called_code_bodies,
		    Nil));
	result = emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		Tightest_end_of_loop_tag));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GO-TO-STATEMENT-COMPILER */
Object go_to_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,108);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_branch_or_jump(mangle_tag_in_context(SECOND(statement)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* TAG-STATEMENT-COMPILER */
Object tag_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(161,109);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    temp = FIRST(statement);
    emit_already_consed_instruction(phrase_list_2(temp,
	    mangle_tag_in_context(SECOND(statement))));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* TAG-STATEMENT-GOTO-TAG-RECORDER */
Object tag_statement_goto_tag_recorder(statement)
    Object statement;
{
    x_note_fn_call(161,110);
    record_new_goto_tag(SECOND(statement));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BEGIN-STATEMENT-COMPILER */
Object begin_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_statement, ab_loop_list_;
    Object gensymed_symbol_2;

    x_note_fn_call(161,111);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_statement = Nil;
    ab_loop_list_ = CDR(statement);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    compile_procedure_statement(sub_statement);
    goto next_loop;
  end_loop:;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BEGIN-STATEMENT-GOTO-TAG-RECORDER */
Object begin_statement_goto_tag_recorder(statement)
    Object statement;
{
    Object sequential_statement, ab_loop_list_;

    x_note_fn_call(161,112);
    sequential_statement = Nil;
    ab_loop_list_ = CDR(statement);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sequential_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    record_goto_tags(sequential_statement);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qmethod_declaration;  /* method-declaration */

/* COMPILE-TIME-SELECTED-METHOD-P */
Object compile_time_selected_method_p(global_name_qm,
	    first_arg_class_description,arg_count)
    Object global_name_qm, first_arg_class_description, arg_count;
{
    Object stable_procedure_qm, declaration_qm, first_arg_class_qm;
    Object scope_conses, ab_loopvar_, subclass, temp_1, method, ab_loop_list_;
    Object ab_loop_it_;
    char temp;
    Declare_special(1);

    x_note_fn_call(161,113);
    stable_procedure_qm = get_specific_method(global_name_qm,
	    first_arg_class_description,arg_count,Nil,T,Nil);
    if (stable_procedure_qm &&  !TRUEP(text_string_p(stable_procedure_qm)) 
	    &&  !TRUEP(block_is_unstable_p(stable_procedure_qm))) {
	temp = TRUEP(block_has_stable_heirarchy_p(stable_procedure_qm));
	if (temp);
	else {
	    declaration_qm = 
		    get_instance_with_name_if_any(Qmethod_declaration,
		    global_name_qm);
	    temp = declaration_qm ? 
		    TRUEP(block_has_stable_heirarchy_p(declaration_qm)) : 
		    TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	first_arg_class_qm = ISVREF(first_arg_class_description,(SI_Long)1L);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = first_arg_class_qm;
	subclass = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  temp_1 = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  subclass = temp_1;
	  if ( !EQ(subclass,first_arg_class_qm)) {
	      method = Nil;
	      temp_1 = 
		      get_named_procedure_methods_for_class(global_name_qm,
		      subclass);
	      ab_loop_list_ = CDR(temp_1);
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      method = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loop_it_ = FIXNUM_EQ(ISVREF(method,(SI_Long)23L),
		      arg_count) ? T : Nil;
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
	      temp = TRUEP(Nil);
	  if (temp) {
	      temp = TRUEP(Nil);
	      goto end_2;
	  }
	  goto next_loop;
	end_loop:
	  temp = TRUEP(T);
	  goto end_2;
	  temp = TRUEP(Qnil);
	end_2:;
	POP_SPECIAL();
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(stable_procedure_qm);
    else
	return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object string_constant_74;  /* "Because of an argument count mismatch for ~ND, a call to it ~
				    *                 could not be optimized."
				    */

static Object string_constant_75;  /* "Because of a return value count mismatch for ~ND, a call to ~
				    *                 it could not be optimized."
				    */

static Object string_constant_76;  /* "Because of a return type mismatch for ~ND, a call to it could ~
				    *                 not be optimized."
				    */

static Object Qstable_compile_time_selected_method;  /* stable-compile-time-selected-method */

static Object Qstable_remote_procedure_call;  /* stable-remote-procedure-call */

static Object Qstable_procedure_call;  /* stable-procedure-call */

static Object Qdependent_call;     /* dependent-call */

static Object Qcall;               /* call */

static Object Qreceive_values;     /* receive-values */

static Object Qdependent_call_rpc;  /* dependent-call-rpc */

static Object Qcall_rpc;           /* call-rpc */

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object Qremote_procedure_call;  /* remote-procedure-call */

static Object Qprocedure_call;     /* procedure-call */

/* CALL-ASSIGNMENT-STATEMENT-COMPILER */
Object call_assignment_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, local_names;
    Object designation, args, across_qm, return_spots, return_types;
    Object desired_return_types, argument_stack_nodes, stable_procedure_qm;
    Object stable_proc_arg_types_qm, stable_proc_return_types_qm;
    Object stable_compile_time_selected_method_name_qm;
    Object stable_compile_time_selected_method_class_qm;
    Object stable_compile_time_selected_method_first_arg_class_qm;
    Object recorded_procedure_call_free_reference_qm;
    Object compiled_procedure_or_rpd, global_name_qm, compiler_error_qm, temp;
    Object temp_1, temp_2, svref_new_value, var_spot, description, type;
    Object local_name, ab_loop_list_, sub_class_bit_vector, first_argument;
    Object first_arg_type, first_arg_class_qm, first_arg_class_description_qm;
    Object unique_name_qm, return_type, stable_proc_return_type;
    Object ab_loop_list__1, ab_loop_it_, gensymed_symbol_6, stable_type;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_4;
    Object desired_type_cons, ab_loop_iter_flag_, arg, type_cons_qm, temp_5;
    Object argument_node;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long ab_loop_repeat_;
    char temp_3;
    Object result;

    x_note_fn_call(161,114);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)11L)));
    Call_statement_processed_qm = T;
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    local_names = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    designation = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    args = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    across_qm = CAR(gensymed_symbol_2);
    return_spots = Nil;
    return_types = Nil;
    desired_return_types = Nil;
    argument_stack_nodes = Nil;
    stable_procedure_qm = Nil;
    stable_proc_arg_types_qm = Nil;
    stable_proc_return_types_qm = Nil;
    stable_compile_time_selected_method_name_qm = Nil;
    stable_compile_time_selected_method_class_qm = Nil;
    stable_compile_time_selected_method_first_arg_class_qm = Nil;
    recorded_procedure_call_free_reference_qm = Nil;
    compiled_procedure_or_rpd =  !TRUEP(across_qm) ? 
	    compile_procedure_expression(2,designation,list_constant_6) : 
	    compile_procedure_expression(2,designation,list_constant_7);
    global_name_qm = Nil;
    compiler_error_qm = Nil;
    temp = CAR(Lexically_visible_code_bodies);
    temp_1 = ISVREF(CAR(Lexically_visible_code_bodies),(SI_Long)2L);
    temp_2 = length(local_names);
    svref_new_value = FIXNUM_MAX(temp_1,temp_2);
    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    var_spot = Nil;
    description = Nil;
    type = Nil;
    local_name = Nil;
    ab_loop_list_ = local_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
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
    goto next_loop;
  end_loop:;
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
	    temp = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_contains_indirect_procedure_call_mask);
	    SVREF(temp,FIX((SI_Long)29L)) = svref_new_value;
	}
    }
    if ( !TRUEP(compiler_error_qm) && dependent_compilation_p(0)) {
	stable_procedure_qm = stable_denoted_procedure_p(1,
		compiled_procedure_or_rpd);
	temp_3 =  !TRUEP(stable_procedure_qm);
	if (temp_3);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(stable_procedure_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_declaration_class_description,
		    (SI_Long)18L));
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
	}
	if (temp_3 ?  ! !TRUEP(args) : TRUEP(Nil)) {
	    stable_procedure_qm = Nil;
	    global_name_qm = 
		    denoted_name_of_type_p(compiled_procedure_or_rpd,
		    list_constant_8);
	    if (get_instance_with_name_if_any(Qmethod_declaration,
		    global_name_qm)) {
		first_argument = compile_stack_expression(CAR(args),
			Qitem_or_datum);
		first_arg_type = ISVREF(first_argument,(SI_Long)6L);
		first_arg_class_qm = 
			class_type_specification_p(first_arg_type) ? 
			M_CAR(M_CDR(first_arg_type)) : Qnil;
		first_arg_class_description_qm = first_arg_class_qm ? 
			lookup_global_or_kb_specific_property_value(first_arg_class_qm,
			Class_description_gkbprop) : Qnil;
		if (first_arg_class_description_qm) {
		    stable_procedure_qm = 
			    compile_time_selected_method_p(global_name_qm,
			    first_arg_class_description_qm,length(args));
		    if (stable_procedure_qm) {
			unique_name_qm = 
				get_unique_name_for_frame_if_any(stable_procedure_qm);
			if (unique_name_qm) {
			    designation = unique_name_qm;
			    compiled_procedure_or_rpd = 
				    compile_stack_expression(unique_name_qm,
				    list_constant_6);
			}
			stable_compile_time_selected_method_name_qm = 
				global_name_qm;
			stable_compile_time_selected_method_class_qm = 
				ISVREF(stable_procedure_qm,(SI_Long)31L);
			stable_compile_time_selected_method_first_arg_class_qm 
				= first_arg_class_qm;
		    }
		    else
			stable_procedure_qm = Nil;
		}
	    }
	}
	if (stable_procedure_qm) {
	    stable_proc_arg_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)24L));
	    stable_proc_return_types_qm = 
		    collect_types_into_list_using_phrase_conses(ISVREF(stable_procedure_qm,
		    (SI_Long)25L));
	    if (FIXNUM_NE(length(stable_proc_arg_types_qm),length(args))) {
		compiler_dependence_warning(2,string_constant_74,designation);
		stable_proc_arg_types_qm = Nil;
		stable_proc_return_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else if (FIXNUM_LT(length(stable_proc_return_types_qm),
		    length(local_names))) {
		compiler_dependence_warning(2,string_constant_75,designation);
		stable_proc_arg_types_qm = Nil;
		stable_proc_return_types_qm = Nil;
		stable_procedure_qm = Nil;
	    }
	    else {
		return_type = Nil;
		ab_loop_list_ = return_types;
		stable_proc_return_type = Nil;
		ab_loop_list__1 = stable_proc_return_types_qm;
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		return_type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		stable_proc_return_type = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		ab_loop_it_ =  
			!TRUEP(type_specifications_could_intersect_p(stable_proc_return_type,
			return_type)) ? T : Nil;
		if (ab_loop_it_) {
		    temp_3 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop_1;
	      end_loop_1:
		temp_3 = TRUEP(Qnil);
	      end_1:;
		if (temp_3) {
		    compiler_dependence_warning(2,string_constant_76,
			    designation);
		    stable_proc_arg_types_qm = Nil;
		    stable_proc_return_types_qm = Nil;
		    stable_procedure_qm = Nil;
		}
		else if (stable_compile_time_selected_method_name_qm) {
		    recorded_procedure_call_free_reference_qm = T;
		    gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
		    gensymed_symbol_6 = gensymed_symbol_2;
		    M_CAR(gensymed_symbol_6) = 
			    stable_compile_time_selected_method_class_qm;
		    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
		    M_CAR(gensymed_symbol_6) = 
			    stable_compile_time_selected_method_name_qm;
		    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
		    M_CAR(gensymed_symbol_6) = 
			    stable_compile_time_selected_method_first_arg_class_qm;
		    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
		    M_CAR(gensymed_symbol_6) = stable_proc_arg_types_qm;
		    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
		    M_CAR(gensymed_symbol_6) = stable_proc_return_types_qm;
		    record_free_reference(Qstable_compile_time_selected_method,
			    gensymed_symbol_2);
		}
		else {
		    recorded_procedure_call_free_reference_qm = T;
		    temp_2 = designation;
		    temp_1 = stable_proc_arg_types_qm;
		    ab_loop_repeat_ = IFIX(length(return_types));
		    stable_type = Nil;
		    ab_loop_list_ = stable_proc_return_types_qm;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    stable_type = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    ab_loopvar__2 = phrase_cons(stable_type,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    temp_4 = ab_loopvar_;
		    goto end_2;
		    temp_4 = Qnil;
		  end_2:;
		    record_free_reference(across_qm ? 
			    Qstable_remote_procedure_call : 
			    Qstable_procedure_call,phrase_list_3(temp_2,
			    temp_1,temp_4));
		}
	    }
	}
    }
    if (stable_proc_return_types_qm) {
	desired_return_types = copy_list_using_phrase_conses(return_types);
	stable_type = Nil;
	ab_loop_list_ = stable_proc_return_types_qm;
	desired_type_cons = desired_return_types;
	ab_loop_iter_flag_ = T;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	stable_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    desired_type_cons = M_CDR(desired_type_cons);
	if ( !TRUEP(desired_type_cons))
	    goto end_loop_3;
	if (type_specification_subtype_p(stable_type,M_CAR(desired_type_cons)))
	    M_CAR(desired_type_cons) = Nil;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_3;
      end_loop_3:;
    }
    else
	desired_return_types = return_types;
    if (stable_procedure_qm &&  
	    !TRUEP(inner_block_cant_be_inlined_in_outer_block_qm(stable_procedure_qm,
	    Current_computation_frame)) && 
	    get_lookup_slot_value_given_default(stable_procedure_qm,
	    Qmd5_identifier_qm,Nil) && 
	    get_lookup_slot_value_given_default(stable_procedure_qm,
	    Qparse_results_qm,Nil) &&  
	    !TRUEP(memq_function(stable_procedure_qm,ISVREF(Inlining_data,
	    (SI_Long)1L)))) {
	temp_2 = 
		copy_tree_using_phrase_conses(get_lookup_slot_value_given_default(stable_procedure_qm,
		Qparse_results_qm,Nil));
	compile_inline_substitution(temp_2,
		CAR(Code_body_entries_in_compilation),statement,
		stable_procedure_qm);
    }
    else if ( !TRUEP(across_qm)) {
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
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_call_without_validated_environment_mask);
	    SVREF(temp,FIX((SI_Long)29L)) = svref_new_value;
	}
	temp_2 = stable_procedure_qm ? Qdependent_call : Qcall;
	temp_1 = compiled_procedure_or_rpd;
	arg = Nil;
	ab_loop_list_ = args;
	type_cons_qm = stable_proc_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp_5 = arg;
	temp_4 = CAR(type_cons_qm);
	if (temp_4);
	else
	    temp_4 = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp_5,
		temp_4),Nil);
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
	emit_already_consed_instruction(phrase_list_4(temp_2,temp_1,
		argument_stack_nodes,length(local_names)));
	if (return_spots)
	    emit_already_consed_instruction(phrase_list_3(Qreceive_values,
		    return_spots,desired_return_types));
    }
    else {
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
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Current_computation_frame,
			Qprocedure_flags);
	    temp = Current_computation_frame;
	    svref_new_value = 
		    FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		    (SI_Long)29L),
		    Procedure_call_without_validated_environment_mask);
	    SVREF(temp,FIX((SI_Long)29L)) = svref_new_value;
	}
	gensymed_symbol_2 = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_6 = gensymed_symbol_2;
	temp = stable_procedure_qm ? Qdependent_call_rpc : Qcall_rpc;
	M_CAR(gensymed_symbol_6) = temp;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	M_CAR(gensymed_symbol_6) = compiled_procedure_or_rpd;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp = compile_procedure_expression(2,across_qm,list_constant_9);
	M_CAR(gensymed_symbol_6) = temp;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	arg = Nil;
	ab_loop_list_ = args;
	type_cons_qm = stable_proc_arg_types_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    type_cons_qm = CDR(type_cons_qm);
	temp_1 = arg;
	temp_2 = CAR(type_cons_qm);
	if (temp_2);
	else
	    temp_2 = Qitem_or_datum;
	ab_loopvar__2 = phrase_cons(compile_stack_expression(temp_1,
		temp_2),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_5;
      end_loop_5:
	argument_stack_nodes = ab_loopvar_;
	goto end_4;
	argument_stack_nodes = Qnil;
      end_4:;
	M_CAR(gensymed_symbol_6) = argument_stack_nodes;
	gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
	temp = length(local_names);
	M_CAR(gensymed_symbol_6) = temp;
	emit_already_consed_instruction(gensymed_symbol_2);
	if (return_spots)
	    emit_already_consed_instruction(phrase_list_3(Qreceive_values,
		    return_spots,desired_return_types));
    }
    if ( !TRUEP(recorded_procedure_call_free_reference_qm) &&  
	    !TRUEP(compiler_error_qm) && SYMBOLP(designation) &&  
	    !TRUEP(indirectly_denoted_item_p(compiled_procedure_or_rpd))) {
	temp_2 = designation;
	argument_node = Nil;
	ab_loop_list_ = argument_stack_nodes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	argument_node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(type_specification_minus_type(type_specification_minus_type(ISVREF(argument_node,
		(SI_Long)6L),list_constant_10),list_constant_11),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_6;
      end_loop_6:
	temp_1 = ab_loopvar_;
	goto end_5;
	temp_1 = Qnil;
      end_5:;
	record_free_reference(across_qm ? Qremote_procedure_call : 
		Qprocedure_call,phrase_list_3(temp_2,temp_1,return_types));
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

static Object Qnext_procedure_method;  /* next-procedure-method */

static Object list_constant_13;    /* # */

static Object Qexists;             /* exists */

static Object Qboolean;            /* boolean */

static Object list_constant_14;    /* # */

static Object string_constant_77;  /* "There is no next method defined for this method and arguments." */

/* CALL-NEXT-METHOD-ASSIGNMENT-STATEMENT-COMPILER */
Object call_next_method_assignment_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_names, local_var_1;
    Object argument_descriptions, first_arg_description, first_arg_name;
    Object method_class_qm, method_name_qm, argument_count, call_tag, temp;
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensymed_symbol_2;

    x_note_fn_call(161,115);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)65L)));
    Call_statement_processed_qm = T;
    local_names = M_CAR(M_CDR(statement));
    local_var_1 = generate_new_variable_spot(1,list_constant_12);
    argument_descriptions = get_procedure_argument_descriptions_in_context();
    first_arg_description = CAR(argument_descriptions);
    first_arg_name = CAR(first_arg_description);
    method_class_qm = get_procedure_method_class_in_context();
    method_name_qm = get_procedure_method_name_in_context();
    argument_count = length(argument_descriptions);
    call_tag = generate_new_goto_tag();
    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
	    local_var_1,compile_stack_expression(phrase_list_3(Qthe,
	    phrase_list_4(Qnext_procedure_method,method_name_qm,
	    method_class_qm,argument_count),first_arg_name),
	    list_constant_13)));
    emit_branch_or_jump_if_not_true(compile_stack_expression(phrase_list_2(Qnot,
	    phrase_list_2(Qexists,local_var_1)),Qboolean),call_tag);
    temp = compile_stack_expression(list_constant_14,Qsymbol);
    emit_already_consed_instruction(phrase_list_3(Qsignal_error,temp,
	    compile_stack_expression(string_constant_77,Qtext)));
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,call_tag));
    argument = Nil;
    ab_loop_list_ = argument_descriptions;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(CAR(argument),Nil);
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
    compile_procedure_statement(phrase_list_4(Qcall_assignment_statement,
	    local_names,local_var_1,temp));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SYSTEM-CALL-ASSIGNMENT-STATEMENT-COMPILER */
Object system_call_assignment_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,116);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    compile_system_call_assignment_statement(statement);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qfunction_keeps_procedure_environment_valid_qm;  /* function-keeps-procedure-environment-valid? */

static Object string_constant_78;  /* "The System-Call statement can not accept more than ~a arguments." */

static Object string_constant_79;  /* "The System-Call statement can not return more than ~a values." */

static Object Qsystem_call;        /* system-call */

/* COMPILE-SYSTEM-CALL-ASSIGNMENT-STATEMENT */
Object compile_system_call_assignment_statement(statement)
    Object statement;
{
    Object gensymed_symbol, local_names, lisp_function_name, args, svref_arg_1;
    Object svref_new_value, return_spots, return_types, var_spot, description;
    Object type, local_name, ab_loop_list_, gensymed_symbol_1, arg;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object result;

    x_note_fn_call(161,117);
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)12L)));
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    local_names = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_function_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(lisp_function_name),
	    Qfunction_keeps_procedure_environment_valid_qm))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),
		Procedure_call_without_validated_environment_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    if (args) {
	if ( !FIXNUM_LE(length(args),Maximum_number_of_lisp_call_arguments))
	    compiler_error(2,string_constant_78,
		    Maximum_number_of_lisp_call_arguments);
    }
    if (local_names) {
	if ( !FIXNUM_LE(length(local_names),
		Maximum_number_of_lisp_call_return_values))
	    compiler_error(2,string_constant_79,
		    Maximum_number_of_lisp_call_return_values);
    }
    return_spots = Nil;
    return_types = Nil;
    var_spot = Nil;
    description = Nil;
    type = Nil;
    local_name = Nil;
    ab_loop_list_ = local_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = variable_spot_and_description_for_local_name(local_name);
    MVS_2(result,var_spot,description);
    type = getfq_function_no_default(CDR(description),Ktype);
    if ( !TRUEP(var_spot))
	procedure_compiler_missing_local_name_error(local_name);
    return_spots = phrase_cons(var_spot,return_spots);
    return_types = phrase_cons(type,return_types);
    goto next_loop;
  end_loop:;
    return_spots = nreverse(return_spots);
    return_types = nreverse(return_types);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qsystem_call;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_spots;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_types;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = lisp_function_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    arg = Nil;
    ab_loop_list_ = args;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compile_stack_expression(arg,
	    Qitem_or_datum),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    goto end_1;
    ab_loopvar_ = Qnil;
  end_1:;
    M_CAR(gensymed_symbol_1) = ab_loopvar_;
    return emit_already_consed_instruction(gensymed_symbol);
}

/* CALL-STATEMENT-COMPILER */
Object call_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,118);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    compile_procedure_statement(phrase_cons(Qcall_assignment_statement,
	    phrase_cons(Nil,CDR(statement))));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcall_statement;     /* call-statement */

/* CALL-NEXT-METHOD-STATEMENT-COMPILER */
Object call_next_method_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, local_var_1;
    Object argument_descriptions, first_arg_description, first_arg_name;
    Object method_class_qm, method_name_qm, argument_count, dont_call_tag;
    Object argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, gensymed_symbol_2;

    x_note_fn_call(161,119);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)65L)));
    Call_statement_processed_qm = T;
    local_var_1 = generate_new_variable_spot(1,list_constant_12);
    argument_descriptions = get_procedure_argument_descriptions_in_context();
    first_arg_description = CAR(argument_descriptions);
    first_arg_name = CAR(first_arg_description);
    method_class_qm = get_procedure_method_class_in_context();
    method_name_qm = get_procedure_method_name_in_context();
    argument_count = length(argument_descriptions);
    dont_call_tag = generate_new_goto_tag();
    emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
	    local_var_1,compile_stack_expression(phrase_list_3(Qthe,
	    phrase_list_4(Qnext_procedure_method,method_name_qm,
	    method_class_qm,argument_count),first_arg_name),
	    list_constant_13)));
    emit_branch_or_jump_if_not_true(compile_stack_expression(phrase_list_2(Qexists,
	    local_var_1),Qboolean),dont_call_tag);
    argument = Nil;
    ab_loop_list_ = argument_descriptions;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(CAR(argument),Nil);
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
    compile_procedure_statement(phrase_list_3(Qcall_statement,local_var_1,
	    temp));
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    dont_call_tag));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SYSTEM-CALL-STATEMENT-COMPILER */
Object system_call_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,120);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    compile_system_call_statement(statement);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPILE-SYSTEM-CALL-STATEMENT */
Object compile_system_call_statement(statement)
    Object statement;
{
    Object gensymed_symbol, lisp_function_name, args, svref_arg_1;
    Object svref_new_value, gensymed_symbol_1, arg, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(161,121);
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)12L)));
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_function_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(lisp_function_name),
	    Qfunction_keeps_procedure_environment_valid_qm))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),
		Procedure_call_without_validated_environment_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    if (args &&  !FIXNUM_LE(length(args),
	    Maximum_number_of_lisp_call_arguments))
	compiler_error(2,string_constant_78,
		Maximum_number_of_lisp_call_arguments);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qsystem_call;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = lisp_function_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    arg = Nil;
    ab_loop_list_ = args;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compile_stack_expression(arg,
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
    M_CAR(gensymed_symbol_1) = ab_loopvar_;
    return emit_already_consed_instruction(gensymed_symbol);
}

/* SYSTEM-ACTION-STATEMENT-COMPILER */
Object system_action_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,122);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    compile_system_action_statement(statement);
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* COMPILE-SYSTEM-ACTION-STATEMENT */
Object compile_system_action_statement(statement)
    Object statement;
{
    Object gensymed_symbol, lisp_function_name, args, svref_arg_1;
    Object svref_new_value, gensymed_symbol_1, arg, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(161,123);
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)12L)));
    gensymed_symbol = statement;
    gensymed_symbol = CDR(gensymed_symbol);
    lisp_function_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(lisp_function_name),
	    Qfunction_keeps_procedure_environment_valid_qm))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),
		Procedure_call_without_validated_environment_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    if (args &&  !FIXNUM_LE(length(args),
	    Maximum_number_of_lisp_call_arguments))
	compiler_error(2,string_constant_78,
		Maximum_number_of_lisp_call_arguments);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qsystem_call;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = lisp_function_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    arg = Nil;
    ab_loop_list_ = args;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compile_stack_expression(arg,
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
    M_CAR(gensymed_symbol_1) = ab_loopvar_;
    return emit_already_consed_instruction(gensymed_symbol);
}

static Object array_constant_42;   /* # */

/* WRITE-SHOW-STATEMENT */
Object write_show_statement(statement)
    Object statement;
{
    x_note_fn_call(161,124);
    twrite_beginning_of_wide_string(array_constant_42,FIX((SI_Long)11L));
    write_expression(SECOND(statement));
    if (FIXNUM_GT(length(statement),FIX((SI_Long)2L)))
	return write_expression(THIRD(statement));
    else
	return VALUES_1(Nil);
}

static Object Qshow_new;           /* show-new */

static Object list_constant_15;    /* # */

/* SHOW-STATEMENT-COMPILER */
Object show_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object show_details_qm, temp;

    x_note_fn_call(161,125);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    show_details_qm = CAR(gensymed_symbol_2);
    temp = compile_stack_expression(item,list_constant_9);
    emit_already_consed_instruction(phrase_list_3(Qshow_new,temp,
	    compile_stack_expression(show_details_qm,
	    maybe_add_unknown(list_constant_15,T))));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_43;   /* # */

/* WRITE-CREATE-STATEMENT */
Object write_create_statement(statement)
    Object statement;
{
    x_note_fn_call(161,126);
    twrite_beginning_of_wide_string(array_constant_43,FIX((SI_Long)14L));
    return write_expression(SECOND(statement));
}

static Object Qitem;               /* item */

static Object string_constant_80;  /* "In the create action, the local name ~a is declared to ~
				    *                        hold ~NT, not ~NT."
				    */

static Object Qcreate;             /* create */

/* CREATE-STATEMENT-COMPILER */
Object create_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object class_expression, local_name_qm, var_spot_qm;
    Object var_spot_description_qm, var_spot_type_qm, compiler_error_qm;
    Object check_created_type_qm, created_type, temp;
    Object result;

    x_note_fn_call(161,127);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
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
    check_created_type_qm = Nil;
    created_type = make_class_type_specification(CONSP(class_expression) 
	    && EQ(CAR(class_expression),Qquote) ? SECOND(class_expression) 
	    : Qitem);
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
		    compiler_error(4,string_constant_80,local_name_qm,
			    var_spot_type_qm,created_type);
	    }
	}
    }
    if ( !TRUEP(compiler_error_qm)) {
	temp = compile_stack_expression(class_expression,Qsymbol);
	emit_already_consed_instruction(phrase_list_4(Qcreate,temp,
		var_spot_qm,check_created_type_qm));
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_44;   /* # */

/* WRITE-CREATE-BY-CLONING-STATEMENT */
Object write_create_by_cloning_statement(statement)
    Object statement;
{
    x_note_fn_call(161,128);
    twrite_beginning_of_wide_string(array_constant_44,FIX((SI_Long)25L));
    return write_expression(SECOND(statement));
}

static Object array_constant_45;   /* # */

/* WRITE-DELETE-STATEMENT */
Object write_delete_statement(statement)
    Object statement;
{
    x_note_fn_call(161,129);
    twrite_beginning_of_wide_string(array_constant_45,FIX((SI_Long)13L));
    write_expression(SECOND(statement));
    if (FIXNUM_GT(length(statement),FIX((SI_Long)2L)))
	return write_expression(THIRD(statement));
    else
	return VALUES_1(Nil);
}

/* DELETE-STATEMENT-COMPILER */
Object delete_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object delete_details_qm, sub_class_bit_vector, svref_arg_1;
    Object svref_new_value, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(161,130);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    delete_details_qm = CAR(gensymed_symbol_2);
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
    temp_1 = compile_stack_expression(item,list_constant_9);
    emit_already_consed_instruction(phrase_list_3(Qdelete,temp_1,
	    compile_stack_expression(delete_details_qm,
	    maybe_add_unknown(list_constant_15,T))));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_46;   /* # */

/* WRITE-ACTIVATE-STATEMENT */
Object write_activate_statement(statement)
    Object statement;
{
    x_note_fn_call(161,131);
    twrite_beginning_of_wide_string(array_constant_46,FIX((SI_Long)15L));
    return write_expression(SECOND(statement));
}

static Object Qactivate;           /* activate */

/* ACTIVATE-STATEMENT-COMPILER */
Object activate_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, the_item;
    Object details, seq_var_name, seq_var_spot_qm, seq_var_spot_description_qm;
    Object compiler_error_qm, sub_class_bit_vector, svref_arg_1;
    Object svref_new_value, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Object result;

    x_note_fn_call(161,132);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    the_item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    details = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    seq_var_name = CAR(gensymed_symbol_2);
    seq_var_spot_qm = Nil;
    seq_var_spot_description_qm = Nil;
    compiler_error_qm = Nil;
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
    if (seq_var_name) {
	result = variable_spot_and_description_for_local_name(seq_var_name);
	MVS_2(result,seq_var_spot_qm,seq_var_spot_description_qm);
	if ( !TRUEP(seq_var_spot_qm)) {
	    compiler_error_qm = T;
	    procedure_compiler_missing_local_name_error(seq_var_name);
	}
    }
    temp_1 = compile_stack_expression(the_item,list_constant_9);
    temp_2 = compile_stack_expression(details,
	    maybe_add_unknown(list_constant_15,T));
    emit_already_consed_instruction(phrase_list_4(Qactivate,temp_1,temp_2,
	    seq_var_spot_qm));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_47;   /* # */

/* WRITE-DEACTIVATE-STATEMENT */
Object write_deactivate_statement(statement)
    Object statement;
{
    x_note_fn_call(161,133);
    twrite_beginning_of_wide_string(array_constant_47,FIX((SI_Long)17L));
    return write_expression(SECOND(statement));
}

static Object Qdeactivate;         /* deactivate */

/* DEACTIVATE-STATEMENT-COMPILER */
Object deactivate_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object details, sub_class_bit_vector, svref_arg_1, svref_new_value, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(161,134);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    details = CAR(gensymed_symbol_2);
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
    temp_1 = compile_stack_expression(item,list_constant_9);
    emit_already_consed_instruction(phrase_list_3(Qdeactivate,temp_1,
	    compile_stack_expression(details,
	    maybe_add_unknown(list_constant_15,T))));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_48;   /* # */

/* WRITE-HIDE-STATEMENT */
Object write_hide_statement(statement)
    Object statement;
{
    x_note_fn_call(161,135);
    twrite_beginning_of_wide_string(array_constant_48,FIX((SI_Long)11L));
    write_expression(SECOND(statement));
    return write_expression(THIRD(statement));
}

static Object Qhide;               /* hide */

/* HIDE-STATEMENT-COMPILER */
Object hide_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, workspace;
    Object window_qm, temp;

    x_note_fn_call(161,136);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    workspace = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    window_qm = CAR(gensymed_symbol_2);
    temp = compile_stack_expression(workspace,list_constant_9);
    emit_already_consed_instruction(phrase_list_3(Qhide,temp,
	    compile_stack_expression(window_qm,Qitem_or_datum)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_49;   /* # */

/* WRITE-START-KB-STATEMENT */
Object write_start_kb_statement(statement)
    Object statement;
{
    x_note_fn_call(161,137);
    return twrite_beginning_of_wide_string(array_constant_49,
	    FIX((SI_Long)26L));
}

static Object Qstart_kb_epilog;    /* start-kb-epilog */

/* START-KB-STATEMENT-COMPILER */
Object start_kb_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object sub_class_bit_vector, svref_arg_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(161,138);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
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
    emit_already_consed_instruction(phrase_cons(Qstart_kb_epilog,Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_50;   /* # */

/* WRITE-RESET-KB-STATEMENT */
Object write_reset_kb_statement(statement)
    Object statement;
{
    x_note_fn_call(161,139);
    return twrite_beginning_of_wide_string(array_constant_50,
	    FIX((SI_Long)26L));
}

static Object Qreset_kb_epilog;    /* reset-kb-epilog */

/* RESET-KB-STATEMENT-COMPILER */
Object reset_kb_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object sub_class_bit_vector, svref_arg_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(161,140);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
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
    emit_already_consed_instruction(phrase_cons(Qreset_kb_epilog,Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_51;   /* # */

/* WRITE-ENABLE-STATEMENT */
Object write_enable_statement(statement)
    Object statement;
{
    x_note_fn_call(161,141);
    twrite_beginning_of_wide_string(array_constant_51,FIX((SI_Long)13L));
    return write_expression(SECOND(statement));
}

static Object Qenable;             /* enable */

/* ENABLE-STATEMENT-COMPILER */
Object enable_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object seq_var_name, seq_var_spot_qm, seq_var_spot_description_qm;
    Object compiler_error_qm, sub_class_bit_vector, svref_arg_1;
    Object svref_new_value, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Object result;

    x_note_fn_call(161,142);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    seq_var_name = CAR(gensymed_symbol_2);
    seq_var_spot_qm = Nil;
    seq_var_spot_description_qm = Nil;
    compiler_error_qm = Nil;
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
    if (seq_var_name) {
	result = variable_spot_and_description_for_local_name(seq_var_name);
	MVS_2(result,seq_var_spot_qm,seq_var_spot_description_qm);
	if ( !TRUEP(seq_var_spot_qm)) {
	    compiler_error_qm = T;
	    procedure_compiler_missing_local_name_error(seq_var_name);
	}
    }
    temp_1 = compile_stack_expression(item,list_constant_9);
    emit_already_consed_instruction(phrase_list_3(Qenable,temp_1,
	    seq_var_spot_qm));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_52;   /* # */

/* WRITE-DISABLE-STATEMENT */
Object write_disable_statement(statement)
    Object statement;
{
    x_note_fn_call(161,143);
    twrite_beginning_of_wide_string(array_constant_52,FIX((SI_Long)14L));
    return write_expression(SECOND(statement));
}

static Object Qdisable;            /* disable */

/* DISABLE-STATEMENT-COMPILER */
Object disable_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, item;
    Object sub_class_bit_vector, svref_arg_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;

    x_note_fn_call(161,144);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    item = CAR(gensymed_symbol_2);
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
    emit_already_consed_instruction(phrase_list_2(Qdisable,
	    compile_stack_expression(item,list_constant_9)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object array_constant_53;   /* # */

/* WRITE-PRINT-STATEMENT */
Object write_print_statement(statement)
    Object statement;
{
    x_note_fn_call(161,145);
    twrite_beginning_of_wide_string(array_constant_53,FIX((SI_Long)12L));
    return write_expression(SECOND(statement));
}

static Object list_constant_16;    /* # */

/* PRINT-STATEMENT-COMPILER */
Object print_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, the_item;

    x_note_fn_call(161,146);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    the_item = CAR(gensymed_symbol_2);
    emit_already_consed_instruction(phrase_list_2(Qprint,
	    compile_stack_expression(the_item,list_constant_16)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ALLOW-OTHER-PROCESSING-STATEMENT-COMPILER */
Object allow_other_processing_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,147);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)13L)));
    emit_already_consed_instruction(phrase_cons(Qallow_other_processing,Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

static Object Qcollect_data;       /* collect-data */

/* COLLECT-DATA-STATEMENT-COMPILER */
Object collect_data_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    Object svref_new_value, gensymed_symbol_5, name_expression_pairs;
    Object timeout_qm, timeout_statement_qm, evals_succeeded_spot;
    Object timeout_spot_qm, timeout_predicate_qm, time_remaining_expression_qm;
    Object success_tag_qm, timeout_tag_qm, timeout_time_compiled, result_pairs;
    Object var_spot, description, type, local_name, expression, ab_loop_list_;
    Object ab_loop_desetq_, temp_2, temp_3, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Object result;

    x_note_fn_call(161,148);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	temp_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(temp_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)14L)));
    gensymed_symbol_5 = statement;
    gensymed_symbol_5 = CDR(gensymed_symbol_5);
    name_expression_pairs = CAR(gensymed_symbol_5);
    gensymed_symbol_5 = CDR(gensymed_symbol_5);
    timeout_qm = CAR(gensymed_symbol_5);
    gensymed_symbol_5 = CDR(gensymed_symbol_5);
    timeout_statement_qm = CAR(gensymed_symbol_5);
    evals_succeeded_spot = generate_new_variable_spot(1,Qtruth_value);
    timeout_spot_qm = Nil;
    timeout_predicate_qm = Nil;
    time_remaining_expression_qm = Nil;
    success_tag_qm = generate_new_goto_tag();
    timeout_tag_qm = timeout_statement_qm ? generate_new_goto_tag() : 
	    success_tag_qm;
    if (timeout_qm) {
	timeout_time_compiled = 
		compile_stack_expression(phrase_list_3(Qplus,
		list_constant_17,timeout_qm),Qfloat);
	timeout_spot_qm = generate_new_variable_spot(1,Qfloat);
	emit_already_consed_instruction(phrase_list_3(Qassign_local_var,
		timeout_spot_qm,timeout_time_compiled));
	timeout_predicate_qm = 
		compile_stack_expression(phrase_list_3(Qnum_ge,
		list_constant_17,timeout_spot_qm),Qtruth_value);
	time_remaining_expression_qm = 
		compile_stack_expression(phrase_list_3(Qminus,
		timeout_spot_qm,list_constant_17),Qfloat);
    }
    result_pairs = Nil;
    var_spot = Nil;
    description = Nil;
    type = Nil;
    local_name = Nil;
    expression = Nil;
    ab_loop_list_ = name_expression_pairs;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    local_name = CAR(ab_loop_desetq_);
    temp_2 = CDR(ab_loop_desetq_);
    expression = CAR(temp_2);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = variable_spot_and_description_for_local_name(local_name);
    MVS_2(result,var_spot,description);
    type = getfq_function_no_default(CDR(description),Ktype);
    if ( !TRUEP(var_spot)) {
	procedure_compiler_missing_local_name_error(local_name);
	type = Qitem_or_datum;
    }
    temp_3 = var_spot;
    temp_2 = expression;
    temp_2 = phrase_list_2(temp_3,compile_stack_expression(temp_2,
	    make_type_specification_union(type,list_constant_10)));
    result_pairs = phrase_cons(temp_2,result_pairs);
    goto next_loop;
  end_loop:
    gensymed_symbol_5 = make_phrase_list(FIX((SI_Long)8L));
    gensymed_symbol_6 = gensymed_symbol_5;
    M_CAR(gensymed_symbol_6) = Qcollect_data;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_1 = nreverse(result_pairs);
    M_CAR(gensymed_symbol_6) = temp_1;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = timeout_spot_qm;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = success_tag_qm;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = timeout_tag_qm;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = timeout_predicate_qm;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = evals_succeeded_spot;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = time_remaining_expression_qm;
    emit_already_consed_instruction(gensymed_symbol_5);
    if (timeout_statement_qm) {
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		timeout_tag_qm));
	compile_procedure_statement(timeout_statement_qm);
    }
    emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	    success_tag_qm));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qcall_code_body;     /* call-code-body */

/* DO-IN-PARALLEL-STATEMENT-COMPILER */
Object do_in_parallel_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, code_bodies_to_launch;
    Object parallel_statement, ab_loop_list_, gensymed_symbol_5;
    Object lexically_visible_code_bodies, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object lexically_visible_goto_tags, temp_1, code_body_number;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(5);

    x_note_fn_call(161,149);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)15L)));
    code_bodies_to_launch = Nil;
    parallel_statement = Nil;
    ab_loop_list_ = CDR(statement);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    parallel_statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_5 = CAR(Lexically_visible_code_bodies);
    gensymed_symbol_5 = make_compiler_code_body_entry_1(Nil,
	    gensymed_symbol_5 ? position(2,gensymed_symbol_5,
	    Code_body_entries_in_compilation) : Nil);
    lexically_visible_code_bodies = phrase_cons(gensymed_symbol_5,
	    Lexically_visible_code_bodies);
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
	    4);
      Code_body_entries_in_compilation = 
	      nconc2(Code_body_entries_in_compilation,
	      phrase_cons(gensymed_symbol_5,Nil));
      check_for_new_code_body_errors();
      if (inlining_context_qm())
	  adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
      outermost_stack_frame_var_binding_qm = Nil;
      next_stack_frame_var_location = Nil;
      stack_frame_vars_ok_in_procedure_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		  1);
	    lexically_visible_goto_tags = Lexically_visible_goto_tags;
	    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		    0);
	      temp_1 = position(2,CAR(Lexically_visible_code_bodies),
		      Code_body_entries_in_compilation);
	      code_bodies_to_launch = phrase_cons(temp_1,
		      code_bodies_to_launch);
	      record_goto_tags(parallel_statement);
	      compile_procedure_statement(parallel_statement);
	      emit_already_consed_instruction(phrase_cons(Qclose_code_body,
		      Nil));
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    goto next_loop;
  end_loop:;
    code_body_number = Nil;
    ab_loop_list_ = nreverse(code_bodies_to_launch);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    code_body_number = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    emit_already_consed_instruction(phrase_list_2(Qcall_code_body,
	    code_body_number));
    goto next_loop_1;
  end_loop_1:;
    emit_already_consed_instruction(phrase_cons(Qwait_for_called_code_bodies,
	    Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qpause;              /* pause */

/* DO-IN-PARALLEL-UNTIL-ONE-COMPLETES-STATEMENT-COMPILER */
Object do_in_parallel_until_one_completes_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, statements, code_bodies_to_launch;
    Object winner_tag, parallel_statement, ab_loop_list_, gensymed_symbol_5;
    Object lexically_visible_code_bodies, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Object lexically_visible_goto_tags, temp_1, code_body_number;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(5);

    x_note_fn_call(161,150);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)16L)));
    statements = CDR(statement);
    if (statements) {
	code_bodies_to_launch = Nil;
	winner_tag = generate_new_goto_tag();
	parallel_statement = Nil;
	ab_loop_list_ = CDR(statement);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	parallel_statement = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_5 = CAR(Lexically_visible_code_bodies);
	gensymed_symbol_5 = make_compiler_code_body_entry_1(Nil,
		gensymed_symbol_5 ? position(2,gensymed_symbol_5,
		Code_body_entries_in_compilation) : Nil);
	lexically_visible_code_bodies = phrase_cons(gensymed_symbol_5,
		Lexically_visible_code_bodies);
	PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
		4);
	  Code_body_entries_in_compilation = 
		  nconc2(Code_body_entries_in_compilation,
		  phrase_cons(gensymed_symbol_5,Nil));
	  check_for_new_code_body_errors();
	  if (inlining_context_qm())
	      adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
	  outermost_stack_frame_var_binding_qm = Nil;
	  next_stack_frame_var_location = Nil;
	  stack_frame_vars_ok_in_procedure_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		      1);
		lexically_visible_goto_tags = Lexically_visible_goto_tags;
		PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
			0);
		  temp_1 = position(2,CAR(Lexically_visible_code_bodies),
			  Code_body_entries_in_compilation);
		  code_bodies_to_launch = phrase_cons(temp_1,
			  code_bodies_to_launch);
		  record_goto_tags(parallel_statement);
		  compile_procedure_statement(parallel_statement);
		  emit_branch_or_jump(winner_tag);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	goto next_loop;
      end_loop:;
	code_body_number = Nil;
	ab_loop_list_ = nreverse(code_bodies_to_launch);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	code_body_number = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_already_consed_instruction(phrase_list_2(Qcall_code_body,
		code_body_number));
	goto next_loop_1;
      end_loop_1:;
	emit_already_consed_instruction(phrase_cons(Qpause,Nil));
	emit_already_consed_instruction(phrase_list_2(Qtag_statement,
		winner_tag));
    }
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qwait_for_interval;  /* wait-for-interval */

/* WAIT-FOR-STATEMENT-COMPILER */
Object wait_for_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,151);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)17L)));
    emit_already_consed_instruction(phrase_list_2(Qwait_for_interval,
	    compile_stack_expression(SECOND(statement),Qnumber)));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_18;    /* # */

static Object Qpolled_wait;        /* polled-wait */

/* WAIT-UNTIL-STATEMENT-COMPILER */
Object wait_until_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, temp_1, temp_2, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,152);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)18L)));
    temp_1 = compile_stack_expression(SECOND(statement),list_constant_18);
    temp_2 = compile_stack_expression(THIRD(statement),Qnumber);
    emit_already_consed_instruction(phrase_list_4(Qpolled_wait,temp_1,
	    temp_2,generate_new_variable_spot(1,Qnumber)));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qreceives_a_value;   /* receives-a-value */

static Object list_constant_19;    /* # */

static Object Qinstall_event_detector;  /* install-event-detector */

static Object list_constant_20;    /* # */

static Object string_constant_81;  /* "wait until event statement" */

static Object string_constant_82;  /* "The malformed event ~a was received." */

static Object Qwait;               /* wait */

static Object Qclear_event_detectors;  /* clear-event-detectors */

/* WAIT-UNTIL-EVENT-STATEMENT-COMPILER */
Object wait_until_event_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, event_antecedent, events, event;
    Object ab_loop_list_, event_type, designation, temp_1, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,153);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)19L)));
    event_antecedent = SECOND(statement);
    events = CONSP(event_antecedent) && EQ(CAR(event_antecedent),Qab_or) ? 
	    CDR(event_antecedent) : phrase_cons(event_antecedent,Nil);
    event = Nil;
    ab_loop_list_ = events;
    event_type = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    event = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    event_type = CONSP(event) ? M_CAR(event) : Nil;
    if (EQ(event_type,Qreceives_a_value)) {
	designation = SECOND(event);
	temp_1 = compile_stack_expression(designation,list_constant_19);
	emit_already_consed_instruction(phrase_list_3(Qinstall_event_detector,
		temp_1,compile_stack_expression(list_constant_20,Qsymbol)));
    }
    else
	compiler_bug(3,string_constant_81,string_constant_82,event);
    goto next_loop;
  end_loop:;
    emit_already_consed_instruction(phrase_cons(Qwait,Nil));
    emit_already_consed_instruction(phrase_cons(Qclear_event_detectors,Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* SYSTEM-WAIT-STATEMENT-COMPILER */
Object system_wait_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object svref_arg_1, svref_new_value, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(161,154);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Current_computation_frame,Qprocedure_flags);
	svref_arg_1 = Current_computation_frame;
	svref_new_value = FIXNUM_LOGIOR(ISVREF(Current_computation_frame,
		(SI_Long)29L),Procedure_contains_wait_state_mask);
	SVREF(svref_arg_1,FIX((SI_Long)29L)) = svref_new_value;
    }
    emit_already_consed_instruction(phrase_cons(Qwait,Nil));
    if (gensymed_symbol_1) {
	gensymed_symbol_5 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_5))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ON-ERROR-STATEMENT-COMPILER */
Object on_error_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object protected_statement, error_name, error_text, handler_statement;
    Object protected_code_body, cleanup_code_tag, no_error_tag;
    Object lexically_visible_goto_tags, error_name_var_spot;
    Object error_name_description, error_text_var_spot, error_text_description;
    Object lexically_visible_code_bodies, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(161,155);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)20L)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    protected_statement = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    error_name = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    error_text = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    handler_statement = CAR(gensymed_symbol_2);
    protected_code_body = Nil;
    cleanup_code_tag = Nil;
    no_error_tag = Nil;
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    5);
      cleanup_code_tag = generate_new_goto_tag();
      no_error_tag = generate_new_goto_tag();
      record_goto_tags(handler_statement);
      result = variable_spot_and_description_for_local_name(error_name);
      MVS_2(result,error_name_var_spot,error_name_description);
      ensure_var_spot_receives_type(error_name,error_name_var_spot,
	      error_name_description,Qsymbol);
      result = variable_spot_and_description_for_local_name(error_text);
      MVS_2(result,error_text_var_spot,error_text_description);
      ensure_var_spot_receives_type(error_text,error_text_var_spot,
	      error_text_description,Qtext);
      gensymed_symbol_2 = CAR(Lexically_visible_code_bodies);
      gensymed_symbol_2 = make_compiler_code_body_entry_1(Nil,
	      gensymed_symbol_2 ? position(2,gensymed_symbol_2,
	      Code_body_entries_in_compilation) : Nil);
      lexically_visible_code_bodies = phrase_cons(gensymed_symbol_2,
	      Lexically_visible_code_bodies);
      PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
	      4);
	Code_body_entries_in_compilation = 
		nconc2(Code_body_entries_in_compilation,
		phrase_cons(gensymed_symbol_2,Nil));
	check_for_new_code_body_errors();
	if (inlining_context_qm())
	    adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
	outermost_stack_frame_var_binding_qm = Nil;
	next_stack_frame_var_location = Nil;
	stack_frame_vars_ok_in_procedure_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		    1);
	      lexically_visible_goto_tags = Lexically_visible_goto_tags;
	      PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		      0);
		protected_code_body = position(2,
			CAR(Lexically_visible_code_bodies),
			Code_body_entries_in_compilation);
		record_goto_tags(protected_statement);
		compile_procedure_statement(protected_statement);
		emit_branch_or_jump(no_error_tag);
		register_error_handler_spec(phrase_list_3(cleanup_code_tag,
			SECOND(error_name_var_spot),
			SECOND(error_text_var_spot)));
		jump_depth_for_tag_qm(cleanup_code_tag);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      emit_already_consed_instruction(phrase_list_2(Qcall_code_body,
	      protected_code_body));
      emit_already_consed_instruction(phrase_cons(Qpause,Nil));
      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	      cleanup_code_tag));
      compile_procedure_statement(handler_statement);
      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	      no_error_tag));
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_21;    /* # */

/* ON-ERROR-STATEMENT-NEW-COMPILER */
Object on_error_statement_new_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object protected_statement, error_1, handler_statement;
    Object protected_code_body, cleanup_code_tag, no_error_tag;
    Object lexically_visible_goto_tags, error_var_spot, error_description;
    Object lexically_visible_code_bodies, outermost_stack_frame_var_binding_qm;
    Object next_stack_frame_var_location, stack_frame_vars_ok_in_procedure_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(161,156);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)20L)));
    gensymed_symbol_2 = statement;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    protected_statement = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    error_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    handler_statement = CAR(gensymed_symbol_2);
    protected_code_body = Nil;
    cleanup_code_tag = Nil;
    no_error_tag = Nil;
    lexically_visible_goto_tags = Lexically_visible_goto_tags;
    PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
	    5);
      cleanup_code_tag = generate_new_goto_tag();
      no_error_tag = generate_new_goto_tag();
      record_goto_tags(handler_statement);
      result = variable_spot_and_description_for_local_name(error_1);
      MVS_2(result,error_var_spot,error_description);
      gensymed_symbol_2 = CAR(Lexically_visible_code_bodies);
      gensymed_symbol_2 = make_compiler_code_body_entry_1(Nil,
	      gensymed_symbol_2 ? position(2,gensymed_symbol_2,
	      Code_body_entries_in_compilation) : Nil);
      lexically_visible_code_bodies = phrase_cons(gensymed_symbol_2,
	      Lexically_visible_code_bodies);
      PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_code_bodies,Qlexically_visible_code_bodies,lexically_visible_code_bodies,
	      4);
	Code_body_entries_in_compilation = 
		nconc2(Code_body_entries_in_compilation,
		phrase_cons(gensymed_symbol_2,Nil));
	check_for_new_code_body_errors();
	if (inlining_context_qm())
	    adjust_nesting_of_inlining_data_received_value_compilations(FIX((SI_Long)1L));
	outermost_stack_frame_var_binding_qm = Nil;
	next_stack_frame_var_location = Nil;
	stack_frame_vars_ok_in_procedure_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_frame_vars_ok_in_procedure_qm,Qstack_frame_vars_ok_in_procedure_qm,stack_frame_vars_ok_in_procedure_qm,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Next_stack_frame_var_location,Qnext_stack_frame_var_location,next_stack_frame_var_location,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Outermost_stack_frame_var_binding_qm,Qoutermost_stack_frame_var_binding_qm,outermost_stack_frame_var_binding_qm,
		    1);
	      lexically_visible_goto_tags = Lexically_visible_goto_tags;
	      PUSH_SPECIAL_WITH_SYMBOL(Lexically_visible_goto_tags,Qlexically_visible_goto_tags,lexically_visible_goto_tags,
		      0);
		protected_code_body = position(2,
			CAR(Lexically_visible_code_bodies),
			Code_body_entries_in_compilation);
		record_goto_tags(protected_statement);
		compile_procedure_statement(protected_statement);
		emit_branch_or_jump(no_error_tag);
		ensure_var_spot_receives_type(error_1,error_var_spot,
			error_description,list_constant_21);
		register_error_handler_spec(phrase_list_3(cleanup_code_tag,
			SECOND(error_var_spot),
			getfq_function_no_default(CDR(error_description),
			Ktype)));
		jump_depth_for_tag_qm(cleanup_code_tag);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      emit_already_consed_instruction(phrase_list_2(Qcall_code_body,
	      protected_code_body));
      emit_already_consed_instruction(phrase_cons(Qpause,Nil));
      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	      cleanup_code_tag));
      compile_procedure_statement(handler_statement);
      emit_already_consed_instruction(phrase_list_2(Qtag_statement,
	      no_error_tag));
    POP_SPECIAL();
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_83;  /* "No type could be determined for the local varible ~a." */

static Object string_constant_84;  /* "The type of ~a, ~NT does not allow it to receive values of ~
				    *                   type ~NT."
				    */

/* ENSURE-VAR-SPOT-RECEIVES-TYPE */
Object ensure_var_spot_receives_type(var_name,var_spot_qm,description_qm,type)
    Object var_name, var_spot_qm, description_qm, type;
{
    Object var_spot_type_qm;

    x_note_fn_call(161,157);
    if ( !TRUEP(var_spot_qm))
	procedure_compiler_missing_local_name_error(var_name);
    else {
	var_spot_type_qm = getfq_function_no_default(CDR(description_qm),
		Ktype);
	if ( !TRUEP(var_spot_type_qm))
	    compiler_error(2,string_constant_83,var_name);
	else if ( 
		!TRUEP(type_specifications_could_intersect_p(var_spot_type_qm,
		type)))
	    compiler_error(4,string_constant_84,var_name,var_spot_type_qm,
		    type);
    }
    return VALUES_1(Nil);
}

/* REGISTER-ERROR-HANDLER-SPEC */
Object register_error_handler_spec(spec)
    Object spec;
{
    Object svref_arg_1;

    x_note_fn_call(161,158);
    svref_arg_1 = CAR(Lexically_visible_code_bodies);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = spec;
    return VALUES_1(Nil);
}

/* SIGNAL-STATEMENT-COMPILER */
Object signal_statement_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2;

    x_note_fn_call(161,159);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)21L)));
    temp = compile_stack_expression(SECOND(statement),Qsymbol);
    emit_already_consed_instruction(phrase_list_3(Qsignal_error,temp,
	    compile_stack_expression(THIRD(statement),Qtext)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qsignal_error_new;   /* signal-error-new */

/* SIGNAL-STATEMENT-NEW-COMPILER */
Object signal_statement_new_compiler(statement)
    Object statement;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(161,160);
    gensymed_symbol = statement;
    gensymed_symbol_1 = Generate_source_annotation_info && 
	    CONSP(gensymed_symbol) ? 
	    get_current_annotation_context(gensymed_symbol) : Qnil;
    if (Generate_source_annotation_info)
	emit_already_consed_instruction(phrase_list_2(Qannotation,
		get_current_annotation_context(statement)));
    emit_already_consed_instruction(phrase_list_2(Qbegin_activity,
	    FIX((SI_Long)21L)));
    emit_already_consed_instruction(phrase_list_2(Qsignal_error_new,
	    compile_stack_expression(SECOND(statement),list_constant_21)));
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = get_current_annotation_context(gensymed_symbol);
	if ( !EQ(gensymed_symbol_1,gensymed_symbol_2))
	    set_current_annotation_context(gensymed_symbol,
		    clone_annotation(gensymed_symbol_1));
    }
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* BRANCH-TAG-REFERENCER */
Object branch_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,161);
    return VALUES_1(M_CDR(instruction));
}

/* BRANCH-TAG-REPLACER */
Object branch_tag_replacer(instruction)
    Object instruction;
{
    Object second_new_value;

    x_note_fn_call(161,162);
    second_new_value = instruction_address_for_tag(SECOND(instruction),Nil);
    M_SECOND(instruction) = second_new_value;
    return VALUES_1(instruction);
}

/* BRANCH-IF-KNOWN-TAG-REFERENCER */
Object branch_if_known_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,163);
    return VALUES_1(M_CDR(instruction));
}

/* BRANCH-IF-KNOWN-TAG-REPLACER */
Object branch_if_known_tag_replacer(instruction)
    Object instruction;
{
    Object second_new_value;

    x_note_fn_call(161,164);
    second_new_value = instruction_address_for_tag(SECOND(instruction),Nil);
    M_SECOND(instruction) = second_new_value;
    return VALUES_1(instruction);
}

/* RESTORE-FROM-ACTION-CACHE-OR-BRANCH-TAG-REFERENCER */
Object restore_from_action_cache_or_branch_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,165);
    return VALUES_1(M_CDR(M_CDR(M_CDR(instruction))));
}

/* RESTORE-FROM-ACTION-CACHE-OR-BRANCH-TAG-REPLACER */
Object restore_from_action_cache_or_branch_tag_replacer(instruction)
    Object instruction;
{
    Object fourth_new_value;

    x_note_fn_call(161,166);
    fourth_new_value = instruction_address_for_tag(FOURTH(instruction),Nil);
    M_FOURTH(instruction) = fourth_new_value;
    return VALUES_1(instruction);
}

/* BRANCH-IF-TRUE-TAG-REFERENCER */
Object branch_if_true_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,167);
    return VALUES_1(M_CDR(M_CDR(instruction)));
}

/* BRANCH-IF-TRUE-TAG-REPLACER */
Object branch_if_true_tag_replacer(instruction)
    Object instruction;
{
    Object third_new_value;

    x_note_fn_call(161,168);
    third_new_value = instruction_address_for_tag(THIRD(instruction),Nil);
    M_THIRD(instruction) = third_new_value;
    return VALUES_1(instruction);
}

/* BRANCH-IF-NOT-TRUE-TAG-REFERENCER */
Object branch_if_not_true_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,169);
    return VALUES_1(M_CDR(M_CDR(instruction)));
}

/* BRANCH-IF-NOT-TRUE-TAG-REPLACER */
Object branch_if_not_true_tag_replacer(instruction)
    Object instruction;
{
    Object third_new_value;

    x_note_fn_call(161,170);
    third_new_value = instruction_address_for_tag(THIRD(instruction),Nil);
    M_THIRD(instruction) = third_new_value;
    return VALUES_1(instruction);
}

/* CASE-DISPATCH-TAG-REFERENCER */
Object case_dispatch_tag_referencer(instruction)
    Object instruction;
{
    Object gensymed_symbol, else_tag, tag_table, temp;

    x_note_fn_call(161,171);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    else_tag = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    tag_table = CAR(gensymed_symbol);
    temp = phrase_cons(else_tag,tag_table);
    return VALUES_1(temp);
}

/* CASE-DISPATCH-TAG-REPLACER */
Object case_dispatch_tag_replacer(instruction)
    Object instruction;
{
    Object gensymed_symbol, else_tag, tag_table, temp, tag_cons;

    x_note_fn_call(161,172);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    else_tag = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    tag_table = CAR(gensymed_symbol);
    temp = instruction_address_for_tag(else_tag,Nil);
    M_FIFTH(instruction) = temp;
    tag_cons = tag_table;
  next_loop:
    if ( !TRUEP(tag_cons))
	goto end_loop;
    temp = instruction_address_for_tag(M_CAR(tag_cons),Nil);
    M_CAR(tag_cons) = temp;
    tag_cons = M_CDR(tag_cons);
    goto next_loop;
  end_loop:;
    return VALUES_1(instruction);
}

/* OPEN-ROLE-ITERATION-TAG-REFERENCER */
Object open_role_iteration_tag_referencer(instruction)
    Object instruction;
{
    Object temp;

    x_note_fn_call(161,173);
    temp = phrase_cons(SEVENTH(instruction),Nil);
    return VALUES_1(temp);
}

/* OPEN-ROLE-ITERATION-TAG-REPLACER */
Object open_role_iteration_tag_replacer(instruction)
    Object instruction;
{
    Object seventh_new_value;

    x_note_fn_call(161,174);
    seventh_new_value = instruction_address_for_tag(SEVENTH(instruction),Nil);
    M_SEVENTH(instruction) = seventh_new_value;
    return VALUES_1(instruction);
}

/* OPEN-ROLE-ITERATION-NO-DOMAIN-TAG-REFERENCER */
Object open_role_iteration_no_domain_tag_referencer(instruction)
    Object instruction;
{
    Object temp;

    x_note_fn_call(161,175);
    temp = nthcdr(FIX((SI_Long)6L),instruction);
    return VALUES_1(temp);
}

/* OPEN-ROLE-ITERATION-NO-DOMAIN-TAG-REPLACER */
Object open_role_iteration_no_domain_tag_replacer(instruction)
    Object instruction;
{
    Object seventh_new_value;

    x_note_fn_call(161,176);
    seventh_new_value = instruction_address_for_tag(SEVENTH(instruction),Nil);
    M_SEVENTH(instruction) = seventh_new_value;
    return VALUES_1(instruction);
}

/* SERVE-NEXT-ITERATION-VALUE-TAG-REFERENCER */
Object serve_next_iteration_value_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,177);
    return VALUES_1(M_CDR(M_CDR(M_CDR(M_CDR(M_CDR(instruction))))));
}

/* SERVE-NEXT-ITERATION-VALUE-TAG-REPLACER */
Object serve_next_iteration_value_tag_replacer(instruction)
    Object instruction;
{
    Object sixth_new_value;

    x_note_fn_call(161,178);
    sixth_new_value = instruction_address_for_tag(SIXTH(instruction),Nil);
    M_SIXTH(instruction) = sixth_new_value;
    return VALUES_1(instruction);
}

/* JUMP-TAG-REPLACER */
Object jump_tag_replacer(instruction)
    Object instruction;
{
    Object third_new_value;

    x_note_fn_call(161,179);
    third_new_value = instruction_address_for_tag(THIRD(instruction),T);
    M_THIRD(instruction) = third_new_value;
    return VALUES_1(instruction);
}

/* JUMP-TAG-REFERENCER */
Object jump_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,180);
    return VALUES_1(M_CDR(M_CDR(instruction)));
}

/* COLLECT-DATA-TAG-REPLACER */
Object collect_data_tag_replacer(instruction)
    Object instruction;
{
    Object gensymed_symbol, success_tag_qm, failure_tag_qm, temp;

    x_note_fn_call(161,181);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    success_tag_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    failure_tag_qm = CAR(gensymed_symbol);
    if (success_tag_qm) {
	temp = instruction_address_for_tag(success_tag_qm,Nil);
	M_FOURTH(instruction) = temp;
    }
    if (failure_tag_qm) {
	temp = instruction_address_for_tag(failure_tag_qm,Nil);
	M_FIFTH(instruction) = temp;
    }
    return VALUES_1(instruction);
}

/* COLLECT-DATA-TAG-REFERENCER */
Object collect_data_tag_referencer(instruction)
    Object instruction;
{
    Object gensymed_symbol, success_tag_qm, failure_tag_qm, temp;

    x_note_fn_call(161,182);
    gensymed_symbol = instruction;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    success_tag_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    failure_tag_qm = CAR(gensymed_symbol);
    if (success_tag_qm && failure_tag_qm)
	temp = phrase_list_2(success_tag_qm,failure_tag_qm);
    else if (success_tag_qm)
	temp = phrase_cons(success_tag_qm,Nil);
    else if (failure_tag_qm)
	temp = phrase_cons(failure_tag_qm,Nil);
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXECUTE-ANTECEDENT-TAG-REPLACER */
Object execute_antecedent_tag_replacer(instruction)
    Object instruction;
{
    Object temp;

    x_note_fn_call(161,183);
    temp = instruction_address_for_tag(FIFTH(instruction),Nil);
    M_FIFTH(instruction) = temp;
    temp = instruction_address_for_tag(SIXTH(instruction),Nil);
    M_SIXTH(instruction) = temp;
    if (SEVENTH(instruction)) {
	temp = instruction_address_for_tag(SEVENTH(instruction),Nil);
	M_SEVENTH(instruction) = temp;
    }
    return VALUES_1(instruction);
}

/* EXECUTE-ANTECEDENT-TAG-REFERENCER */
Object execute_antecedent_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,184);
    return VALUES_1(M_CDR(M_CDR(M_CDR(M_CDR(instruction)))));
}

/* EXECUTE-SIMULATION-FORMULA-TAG-REPLACER */
Object execute_simulation_formula_tag_replacer(instruction)
    Object instruction;
{
    Object fourth_new_value;

    x_note_fn_call(161,185);
    fourth_new_value = instruction_address_for_tag(FOURTH(instruction),Nil);
    M_FOURTH(instruction) = fourth_new_value;
    return VALUES_1(instruction);
}

/* EXECUTE-SIMULATION-FORMULA-TAG-REFERENCER */
Object execute_simulation_formula_tag_referencer(instruction)
    Object instruction;
{
    x_note_fn_call(161,186);
    return VALUES_1(M_CDR(M_CDR(M_CDR(instruction))));
}

void proc_comp_INIT()
{
    Object temp, gensymed_symbol, assignment_statement_compiler_1;
    Object return_statement_compiler_1, if_then_statement_compiler_1;
    Object if_then_statement_goto_tag_recorder_1;
    Object if_then_else_statement_compiler_1;
    Object if_then_else_statement_goto_tag_recorder_1;
    Object case_statement_compiler_1, case_statement_goto_tag_recorder_1;
    Object repeat_statement_compiler_1, exit_if_statement_compiler_1;
    Object for_each_statement_compiler_1;
    Object for_each_in_parallel_statement_compiler_1;
    Object for_each_in_parallel_race_statement_compiler_1;
    Object for_numeric_statement_compiler_1, go_to_statement_compiler_1;
    Object tag_statement_compiler_1, tag_statement_goto_tag_recorder_1;
    Object begin_statement_compiler_1, begin_statement_goto_tag_recorder_1;
    Object call_assignment_statement_compiler_1;
    Object call_next_method_assignment_statement_compiler_1;
    Object system_call_assignment_statement_compiler_1;
    Object call_statement_compiler_1, call_next_method_statement_compiler_1;
    Object system_call_statement_compiler_1;
    Object system_action_statement_compiler_1, show_statement_compiler_1;
    Object create_statement_compiler_1, delete_statement_compiler_1;
    Object activate_statement_compiler_1, deactivate_statement_compiler_1;
    Object hide_statement_compiler_1, start_kb_statement_compiler_1;
    Object reset_kb_statement_compiler_1, enable_statement_compiler_1;
    Object disable_statement_compiler_1, print_statement_compiler_1;
    Object allow_other_processing_statement_compiler_1;
    Object collect_data_statement_compiler_1;
    Object do_in_parallel_statement_compiler_1;
    Object do_in_parallel_until_one_completes_statement_compiler_1;
    Object wait_for_statement_compiler_1, wait_until_statement_compiler_1;
    Object wait_until_event_statement_compiler_1;
    Object system_wait_statement_compiler_1, on_error_statement_compiler_1;
    Object on_error_statement_new_compiler_1, signal_statement_compiler_1;
    Object signal_statement_new_compiler_1;
    Object Qexecute_simulation_formula_tag_referencer;
    Object Qexecute_simulation_formula, AB_package;
    Object Qexecute_simulation_formula_tag_replacer;
    Object Qexecute_antecedent_tag_referencer, Qexecute_antecedent;
    Object Qexecute_antecedent_tag_replacer, Qcollect_data_tag_referencer;
    Object Qcollect_data_tag_replacer, Qjump_tag_referencer;
    Object Qjump_tag_replacer, Qserve_next_iteration_value_tag_replacer;
    Object Qserve_next_iteration_value_tag_referencer;
    Object Qopen_role_iteration_no_domain_tag_replacer;
    Object Qopen_role_iteration_no_domain_tag_referencer;
    Object Qopen_role_iteration_tag_replacer;
    Object Qopen_role_iteration_tag_referencer, Qcase_dispatch_tag_replacer;
    Object Qcase_dispatch_tag_referencer, Qbranch_if_not_true_tag_replacer;
    Object Qbranch_if_not_true_tag_referencer, Qbranch_if_true_tag_replacer;
    Object Qbranch_if_true_tag_referencer;
    Object Qrestore_from_action_cache_or_branch_tag_replacer;
    Object Qrestore_from_action_cache_or_branch;
    Object Qrestore_from_action_cache_or_branch_tag_referencer;
    Object Qbranch_if_known_tag_replacer, Qbranch_if_known;
    Object Qbranch_if_known_tag_referencer, Qbranch_tag_replacer;
    Object Qbranch_tag_referencer, Qsignal_statement_new;
    Object Qprint_signal_statement_new, Qsignal_statement;
    Object Qprint_signal_statement, Qon_error_statement_new;
    Object Qprint_on_error_statement_new, Qon_error_statement;
    Object Qprint_on_error_statement, Qsystem_wait_statement;
    Object Qwrite_system_wait_statement, Qwait_until_event_statement;
    Object list_constant_25, list_constant_24, Qplace_reference;
    Object Qvariable_or_parameter, Qwrite_wait_until_event_statement;
    Object Qwait_until_statement, Qwrite_wait_until_statement;
    Object Qwait_for_statement, Qwrite_wait_for_statement;
    Object Qdo_in_parallel_until_one_completes_statement;
    Object Qwrite_do_in_parallel_until_one_completes_statement;
    Object Qdo_in_parallel_statement, Qwrite_do_in_parallel_statement;
    Object Qcollect_data_statement, Qcurrent_subsecond_time;
    Object Qwrite_collect_data_statement, Qallow_other_processing_statement;
    Object Qwrite_allow_other_processing_statement, Qprint_statement;
    Object Qworkspace, Qwrite_print_statement, list_constant_23;
    Object Qdisable_statement, Qwrite_disable_statement, Qenable_statement;
    Object Qwrite_enable_statement, Qreset_kb_statement;
    Object Qwrite_start_kb_statement, Qstart_kb_statement, Qhide_statement;
    Object Qwrite_hide_statement, Qdeactivate_statement;
    Object Qwrite_deactivate_statement, Qactivate_statement;
    Object Qwrite_activate_statement, Qdelete_statement;
    Object Qwrite_delete_statement, Qcreate_statement, Qwrite_create_statement;
    Object Qshow_statement, Qab_structure, Qwrite_show_statement;
    Object Qsystem_action_statement, Qwrite_system_call_statement;
    Object Qsystem_call_statement, Qcall_next_method_statement;
    Object Qwrite_call_next_method_statement, Qwrite_call_statement;
    Object Qsystem_call_assignment_statement;
    Object Qwrite_system_call_assignment_statement;
    Object Qcall_next_method_assignment_statement, Qab_no_next_method;
    Object Qab_method, Qwrite_call_next_method_assignment_statement, Qno_item;
    Object Qunknown_datum, Qremote_procedure_declaration, Qprocedure;
    Object Qwrite_call_assignment_statement, Qgoto_tag_recorder;
    Object Qwrite_begin_statement, Qwrite_tag_statement, Qgo_to_statement;
    Object Qwrite_go_to_statement, Qfor_numeric_statement;
    Object Qprint_for_numeric_statement, Qwrite_for_each_statement;
    Object Qexit_if_statement, Qwrite_exit_if_statement, Qrepeat_statement;
    Object Qwrite_repeat_statement, Qno_case_choice, Qcase_statement;
    Object Qprint_case_statement, Qif_then_else_statement;
    Object Qwrite_if_then_else_statement, Qif_then_statement;
    Object Qwrite_if_then_statement, Qreturn_statement;
    Object Qwrite_return_statement, Qformat_form, Qcall_function, Qensure_type;
    Object Qcoerce_no_item_to_unknown, Qcoerce_to_datum, Qevaluate_role;
    Object Qevaluate_role_implicit_scope, Qcopy_into_surrounding_local_var;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qprint_assignment_statement;
    Object list_constant_22, Qg2_enable_inlining, Qg2_disable_inlining;
    Object Qconvert_frame_internals_to_vectors_as_necessary;
    Object Qno_return_statement;

    x_note_fn_call(161,187);
    SET_PACKAGE("AB");
    if (Generated_var_spots_for_base_code_body_return == UNBOUND)
	Generated_var_spots_for_base_code_body_return = Nil;
    if (Returned_values_description == UNBOUND)
	Returned_values_description = Nil;
    if (Return_statement_processed_qm == UNBOUND)
	Return_statement_processed_qm = Nil;
    if (Call_statement_processed_qm == UNBOUND)
	Call_statement_processed_qm = Nil;
    if (Expression_bound_local_names == UNBOUND)
	Expression_bound_local_names = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qprocedure_statement_writer = 
	    STATIC_SYMBOL("PROCEDURE-STATEMENT-WRITER",AB_package);
    string_constant = STATIC_STRING("~a");
    if (Procedure_branch_short_cuts == UNBOUND)
	Procedure_branch_short_cuts = Nil;
    string_constant_1 = STATIC_STRING("instruction address lookup");
    string_constant_2 = 
	    STATIC_STRING("The tag ~a was referenced via a JUMP instruction, but ~\n                         no such reference had been noted.");
    string_constant_3 = 
	    STATIC_STRING("The tag ~a was referenced, but no such tag is declared for ~\n                 this procedure.");
    string_constant_4 = STATIC_STRING("address resolver");
    string_constant_5 = 
	    STATIC_STRING("The tag ~a did not have a registered address at address ~\n             resolution time.");
    if (Base_code_body_return_tag == UNBOUND)
	Base_code_body_return_tag = Nil;
    Qpseudo_instruction_byte_code_emitter = 
	    STATIC_SYMBOL("PSEUDO-INSTRUCTION-BYTE-CODE-EMITTER",AB_package);
    string_constant_6 = STATIC_STRING("byte code emitter");
    string_constant_7 = 
	    STATIC_STRING("The pseudo instruction ~a had no byte code emitter function.");
    Qgoto_tag_replacer = STATIC_SYMBOL("GOTO-TAG-REPLACER",AB_package);
    Goto_tag_replacer_prop = Qgoto_tag_replacer;
    Qgoto_tag_references = STATIC_SYMBOL("GOTO-TAG-REFERENCES",AB_package);
    Goto_tag_references_prop = Qgoto_tag_references;
    if (Current_return_values_position == UNBOUND)
	Current_return_values_position = Nil;
    Qbegin_statement = STATIC_SYMBOL("BEGIN-STATEMENT",AB_package);
    Qcompile_procedure_note = STATIC_SYMBOL("COMPILE-PROCEDURE-NOTE",
	    AB_package);
    Qhas_empty_code_body_qm = STATIC_SYMBOL("HAS-EMPTY-CODE-BODY\?",
	    AB_package);
    Qn_compiles_this_session = STATIC_SYMBOL("N-COMPILES-THIS-SESSION",
	    AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qargument_count = STATIC_SYMBOL("ARGUMENT-COUNT",AB_package);
    Qargument_list_description = STATIC_SYMBOL("ARGUMENT-LIST-DESCRIPTION",
	    AB_package);
    Qreturned_values_description = 
	    STATIC_SYMBOL("RETURNED-VALUES-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreturned_values_description,
	    Returned_values_description);
    Qprocedure_method_class = STATIC_SYMBOL("PROCEDURE-METHOD-CLASS",
	    AB_package);
    string_constant_8 = 
	    STATIC_STRING("the procedure method must have at least one argument");
    string_constant_9 = 
	    STATIC_STRING("the first argument of a procedure method must be of type item");
    Qprocedure_method_name = STATIC_SYMBOL("PROCEDURE-METHOD-NAME",AB_package);
    string_constant_10 = 
	    STATIC_STRING("Procedure body completed without a return statement.  This procedure must use a return statement since it is declared to return values.");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_11 = 
	    STATIC_STRING("Procedure body for ~a completed without a return statement.  This procedure must use a return statement since it is declared to return values.");
    Qno_return_statement = STATIC_SYMBOL("NO-RETURN-STATEMENT",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qquote,Qno_return_statement);
    Qsignal_error = STATIC_SYMBOL("SIGNAL-ERROR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtag_statement = STATIC_SYMBOL("TAG-STATEMENT",AB_package);
    Qreturn_values = STATIC_SYMBOL("RETURN-VALUES",AB_package);
    Qcode_body = STATIC_SYMBOL("CODE-BODY",AB_package);
    Kreturn_value = STATIC_SYMBOL("RETURN-VALUE",Pkeyword);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qenvironment_description = STATIC_SYMBOL("ENVIRONMENT-DESCRIPTION",
	    AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qparse_results_qm = STATIC_SYMBOL("PARSE-RESULTS\?",AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    string_constant_12 = STATIC_STRING("<returned value>");
    Qassignment_statement = STATIC_SYMBOL("ASSIGNMENT-STATEMENT",AB_package);
    if (New_descriptions == UNBOUND)
	New_descriptions = Nil;
    Qconvert_frame_internals_to_vectors_as_necessary = 
	    STATIC_SYMBOL("CONVERT-FRAME-INTERNALS-TO-VECTORS-AS-NECESSARY",
	    AB_package);
    temp = adjoin(2,Qconvert_frame_internals_to_vectors_as_necessary,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp;
    temp = adjoin(2,Qconvert_frame_internals_to_vectors_as_necessary,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp;
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrule_byte_code_body = STATIC_SYMBOL("RULE-BYTE-CODE-BODY",AB_package);
    Qfunction_definition_byte_code_body = 
	    STATIC_SYMBOL("FUNCTION-DEFINITION-BYTE-CODE-BODY",AB_package);
    Qsimulation_subtable_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-BYTE-CODE-BODY",AB_package);
    Qsimulation_subtable_initial_value_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qgeneric_simulation_formula_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA-BYTE-CODE-BODY",
	    AB_package);
    Qgeneric_simulation_initial_value_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qimage_definition_saveable_image_info = 
	    STATIC_SYMBOL("IMAGE-DEFINITION-SAVEABLE-IMAGE-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_frame_internals_to_vectors_as_necessary,
	    STATIC_FUNCTION(convert_frame_internals_to_vectors_as_necessary,
	    NIL,FALSE,0,0));
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    string_constant_13 = 
	    STATIC_STRING("The type TIME-STAMP for the argument ~a is being phased out.  This ~\n       type should be replaced with quantity, integer, or float.  Quantity ~\n       will be used for now.");
    string_constant_14 = STATIC_STRING("local-name declarations");
    string_constant_15 = 
	    STATIC_STRING("The type ~a was given for the local-name ~a, but is not a valid type.");
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    No_inlining_qm = Nil;
    Qg2_disable_inlining = STATIC_SYMBOL("G2-DISABLE-INLINING",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_disable_inlining,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_disable_inlining,
	    STATIC_FUNCTION(g2_disable_inlining,NIL,FALSE,0,0));
    Qg2_enable_inlining = STATIC_SYMBOL("G2-ENABLE-INLINING",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_enable_inlining,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_enable_inlining,
	    STATIC_FUNCTION(g2_enable_inlining,NIL,FALSE,0,0));
    Qcall_action = STATIC_SYMBOL("CALL-ACTION",AB_package);
    Qcall_assignment_statement = STATIC_SYMBOL("CALL-ASSIGNMENT-STATEMENT",
	    AB_package);
    Qcall_assignment_action = STATIC_SYMBOL("CALL-ASSIGNMENT-ACTION",
	    AB_package);
    Qcall_next_method_assignment_statement = 
	    STATIC_SYMBOL("CALL-NEXT-METHOD-ASSIGNMENT-STATEMENT",AB_package);
    Qcall_next_method_statement = 
	    STATIC_SYMBOL("CALL-NEXT-METHOD-STATEMENT",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)5L,Qcall_assignment_statement,
	    Qcall_next_method_assignment_statement,
	    Qcall_next_method_statement,Qcall_action,Qcall_assignment_action);
    Call_statements = list_constant_22;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmd5_identifier_qm = STATIC_SYMBOL("MD5-IDENTIFIER\?",AB_package);
    string_constant_16 = STATIC_STRING("{~a::~a~@[~a~]}~a");
    string_constant_17 = STATIC_STRING("{~a~@[~a~]}~a");
    Qassign_local_var = STATIC_SYMBOL("ASSIGN-LOCAL-VAR",AB_package);
    Qprocedure_statement = STATIC_SYMBOL("PROCEDURE-STATEMENT",AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    Qaction_compiler = STATIC_SYMBOL("ACTION-COMPILER",AB_package);
    Qprocedure_statement_compiler = 
	    STATIC_SYMBOL("PROCEDURE-STATEMENT-COMPILER",AB_package);
    string_constant_18 = STATIC_STRING("statement compiler");
    string_constant_19 = STATIC_STRING("The statement ~A is not defined.");
    string_constant_20 = 
	    STATIC_STRING("The statement ~a is not in the correct format.");
    Qrelated = STATIC_SYMBOL("RELATED",AB_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qat_port = STATIC_SYMBOL("AT-PORT",AB_package);
    Qport_name = STATIC_SYMBOL("PORT-NAME",AB_package);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    Qtext_of_attribute = STATIC_SYMBOL("TEXT-OF-ATTRIBUTE",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qclass_qualified_attribute_of_class = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS",AB_package);
    Qattribute_of_class = STATIC_SYMBOL("ATTRIBUTE-OF-CLASS",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    Qjump = STATIC_SYMBOL("JUMP",AB_package);
    Qclose_code_body = STATIC_SYMBOL("CLOSE-CODE-BODY",AB_package);
    Qcase_dispatch = STATIC_SYMBOL("CASE-DISPATCH",AB_package);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qexecute_antecedent = STATIC_SYMBOL("EXECUTE-ANTECEDENT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)8L,Qbranch,Qjump,Qreturn_values,
	    Qsignal_error,Qclose_code_body,Qcase_dispatch,Qpause,
	    Qexecute_antecedent);
    Qjump_tag_statement = STATIC_SYMBOL("JUMP-TAG-STATEMENT",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qtag_statement,
	    Qjump_tag_statement);
    string_constant_21 = STATIC_STRING("tag replacers");
    string_constant_22 = 
	    STATIC_STRING("No goto tag replacer function exists for ~a.");
    Qphrase_pool = STATIC_SYMBOL("PHRASE-POOL",AB_package);
    string_constant_23 = STATIC_STRING("dead code optimizer");
    string_constant_24 = STATIC_STRING("Malformed tag ~a in ~a instruction.");
    string_constant_25 = 
	    STATIC_STRING("The tag ~a was declared but not referenced.");
    string_constant_26 = STATIC_STRING("tags directory");
    string_constant_27 = 
	    STATIC_STRING("The tag ~a was in instructions, but not in the directory ~\n                  of tags at jump expansion time.");
    Qabort_called_code_bodies = STATIC_SYMBOL("ABORT-CALLED-CODE-BODIES",
	    AB_package);
    string_constant_28 = 
	    STATIC_STRING("The tag ~a had no entry at address generation time.");
    string_constant_29 = 
	    STATIC_STRING("The JUMP tag ~a had no entry at address generation time.");
    string_constant_30 = STATIC_STRING("address registrar");
    string_constant_31 = STATIC_STRING("The tag ~a had no entry.");
    string_constant_32 = 
	    STATIC_STRING("The tag ~a is registered at multiple addresses.");
    Qbranch_if_true = STATIC_SYMBOL("BRANCH-IF-TRUE",AB_package);
    Qbranch_if_not_true = STATIC_SYMBOL("BRANCH-IF-NOT-TRUE",AB_package);
    string_constant_33 = STATIC_STRING("~a = ");
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    string_constant_34 = STATIC_STRING(")~%  ");
    string_constant_35 = STATIC_STRING(";~%  ");
    array_constant_6 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    string_constant_36 = STATIC_STRING("~%  END");
    array_constant_8 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    string_constant_37 = STATIC_STRING("FOR ~a = EACH ");
    Qfor_each_statement = STATIC_SYMBOL("FOR-EACH-STATEMENT",AB_package);
    string_constant_38 = STATIC_STRING(" DO");
    Qfor_each_in_parallel_statement = 
	    STATIC_SYMBOL("FOR-EACH-IN-PARALLEL-STATEMENT",AB_package);
    string_constant_39 = STATIC_STRING(" DO IN PARALLEL");
    Qfor_each_in_parallel_race_statement = 
	    STATIC_SYMBOL("FOR-EACH-IN-PARALLEL-RACE-STATEMENT",AB_package);
    string_constant_40 = STATIC_STRING(" DO IN PARALLEL UNTIL ONE COMPLETES");
    string_constant_41 = STATIC_STRING("~%  ");
    string_constant_42 = STATIC_STRING("FOR ~a = ");
    Qto = STATIC_SYMBOL("TO",AB_package);
    string_constant_43 = STATIC_STRING(" TO ");
    string_constant_44 = STATIC_STRING(" DOWN TO ");
    array_constant_12 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qdo_in_parallel = STATIC_SYMBOL("DO-IN-PARALLEL",AB_package);
    string_constant_45 = STATIC_STRING("~% END");
    string_constant_46 = STATIC_STRING("GO TO ~a");
    string_constant_47 = STATIC_STRING("~a :");
    array_constant_13 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)13L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)23L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    string_constant_48 = STATIC_STRING("~a ");
    array_constant_27 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)57344L);
    array_constant_29 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)17L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)57344L);
    string_constant_49 = STATIC_STRING("~%  ~a = ");
    array_constant_30 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)57344L);
    string_constant_50 = STATIC_STRING("~%  IF TIMEOUT THEN ");
    string_constant_51 = STATIC_STRING("~%END");
    array_constant_31 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)16L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)17L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)18L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)19L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)21L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)22L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)23L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)25L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)26L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)27L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)28L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)29L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)30L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)31L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)32L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)33L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)39L,(SI_Long)57344L);
    array_constant_33 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)57344L);
    string_constant_52 = STATIC_STRING("CREATE A(N) ~NE ~a ");
    string_constant_53 = STATIC_STRING("CREATE A(N) ~NE ");
    array_constant_37 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)10L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)11L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)13L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)16L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)17L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)23L,(SI_Long)57344L);
    array_constant_38 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)9L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)10L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)17L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)19L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)20L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)31L,(SI_Long)57344L);
    array_constant_39 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)10L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)11L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)12L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)17L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)18L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)20L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)31L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    string_constant_54 = STATIC_STRING(" ON ERROR (~a, ~a) ");
    string_constant_55 = STATIC_STRING("SIGNAL ~NE, ~NE");
    string_constant_56 = STATIC_STRING(" ON ERROR (~a) ");
    string_constant_57 = STATIC_STRING("SIGNAL ~NE");
    Qprint_assignment_statement = 
	    STATIC_SYMBOL("PRINT-ASSIGNMENT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_assignment_statement,
	    STATIC_FUNCTION(print_assignment_statement,NIL,FALSE,1,1));
    mutate_global_property(Qassignment_statement,
	    SYMBOL_FUNCTION(Qprint_assignment_statement),
	    Qprocedure_statement_writer);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    Qbegin_activity = STATIC_SYMBOL("BEGIN-ACTIVITY",AB_package);
    Qmove_from_surrounding_local_var = 
	    STATIC_SYMBOL("MOVE-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    assignment_statement_compiler_1 = 
	    STATIC_FUNCTION(assignment_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qassignment_statement,
	    assignment_statement_compiler_1,Qprocedure_statement_compiler);
    Qg2_defstruct_structure_name_stack_node_instruction_g2_struct = 
	    STATIC_SYMBOL("STACK-NODE-INSTRUCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpush_from_surrounding_local_var = 
	    STATIC_SYMBOL("PUSH-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    Qcopy_into_surrounding_local_var = 
	    STATIC_SYMBOL("COPY-INTO-SURROUNDING-LOCAL-VAR",AB_package);
    Qevaluate_role_implicit_scope = 
	    STATIC_SYMBOL("EVALUATE-ROLE-IMPLICIT-SCOPE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)4L,
	    Qpush_from_surrounding_local_var,
	    Qmove_from_surrounding_local_var,
	    Qcopy_into_surrounding_local_var,Qevaluate_role_implicit_scope);
    Qevaluate_role = STATIC_SYMBOL("EVALUATE-ROLE",AB_package);
    Qcoerce_to_datum = STATIC_SYMBOL("COERCE-TO-DATUM",AB_package);
    Qcoerce_no_item_to_unknown = STATIC_SYMBOL("COERCE-NO-ITEM-TO-UNKNOWN",
	    AB_package);
    Qensure_type = STATIC_SYMBOL("ENSURE-TYPE",AB_package);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qformat_form = STATIC_SYMBOL("FORMAT-FORM",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)6L,Qevaluate_role,
	    Qcoerce_to_datum,Qcoerce_no_item_to_unknown,Qensure_type,
	    Qcall_function,Qformat_form);
    Qreturn_statement = STATIC_SYMBOL("RETURN-STATEMENT",AB_package);
    Qwrite_return_statement = STATIC_SYMBOL("WRITE-RETURN-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_return_statement,
	    STATIC_FUNCTION(write_return_statement,NIL,FALSE,1,1));
    mutate_global_property(Qreturn_statement,
	    SYMBOL_FUNCTION(Qwrite_return_statement),
	    Qprocedure_statement_writer);
    string_constant_58 = 
	    STATIC_STRING("Returning ~a values, but the procedure is declared to return ~a ~\n         values.");
    string_constant_59 = 
	    STATIC_STRING("A returned value from the inlined procedure ~NF of type ~NT ~\n                   could not be assigned into a local-name of type ~NT.");
    return_statement_compiler_1 = 
	    STATIC_FUNCTION(return_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qreturn_statement,return_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qreturn_value = STATIC_SYMBOL("RETURN-VALUE",AB_package);
    Qif_then_statement = STATIC_SYMBOL("IF-THEN-STATEMENT",AB_package);
    Qwrite_if_then_statement = STATIC_SYMBOL("WRITE-IF-THEN-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_if_then_statement,
	    STATIC_FUNCTION(write_if_then_statement,NIL,FALSE,1,1));
    mutate_global_property(Qif_then_statement,
	    SYMBOL_FUNCTION(Qwrite_if_then_statement),
	    Qprocedure_statement_writer);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    if_then_statement_compiler_1 = 
	    STATIC_FUNCTION(if_then_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qif_then_statement,if_then_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qgoto_tag_recorder = STATIC_SYMBOL("GOTO-TAG-RECORDER",AB_package);
    if_then_statement_goto_tag_recorder_1 = 
	    STATIC_FUNCTION(if_then_statement_goto_tag_recorder,NIL,FALSE,1,1);
    mutate_global_property(Qif_then_statement,
	    if_then_statement_goto_tag_recorder_1,Qgoto_tag_recorder);
    Qif_then_else_statement = STATIC_SYMBOL("IF-THEN-ELSE-STATEMENT",
	    AB_package);
    Qwrite_if_then_else_statement = 
	    STATIC_SYMBOL("WRITE-IF-THEN-ELSE-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_if_then_else_statement,
	    STATIC_FUNCTION(write_if_then_else_statement,NIL,FALSE,1,1));
    mutate_global_property(Qif_then_else_statement,
	    SYMBOL_FUNCTION(Qwrite_if_then_else_statement),
	    Qprocedure_statement_writer);
    if_then_else_statement_compiler_1 = 
	    STATIC_FUNCTION(if_then_else_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qif_then_else_statement,
	    if_then_else_statement_compiler_1,Qprocedure_statement_compiler);
    if_then_else_statement_goto_tag_recorder_1 = 
	    STATIC_FUNCTION(if_then_else_statement_goto_tag_recorder,NIL,
	    FALSE,1,1);
    mutate_global_property(Qif_then_else_statement,
	    if_then_else_statement_goto_tag_recorder_1,Qgoto_tag_recorder);
    Qcase_statement = STATIC_SYMBOL("CASE-STATEMENT",AB_package);
    Qprint_case_statement = STATIC_SYMBOL("PRINT-CASE-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_case_statement,
	    STATIC_FUNCTION(print_case_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcase_statement,
	    SYMBOL_FUNCTION(Qprint_case_statement),
	    Qprocedure_statement_writer);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    string_constant_60 = 
	    STATIC_STRING("First CASE value, ~a, was not of a known type!");
    case_statement_compiler_1 = STATIC_FUNCTION(case_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcase_statement,case_statement_compiler_1,
	    Qprocedure_statement_compiler);
    case_statement_goto_tag_recorder_1 = 
	    STATIC_FUNCTION(case_statement_goto_tag_recorder,NIL,FALSE,1,1);
    mutate_global_property(Qcase_statement,
	    case_statement_goto_tag_recorder_1,Qgoto_tag_recorder);
    string_constant_61 = 
	    STATIC_STRING("This CASE statement had no values to dispatch upon.");
    string_constant_62 = 
	    STATIC_STRING("A CASE clause had no values associated with it.");
    string_constant_63 = 
	    STATIC_STRING("The CASE key value OTHERWISE was the key for a clause ~\n                  other than the last one in the CASE statement.");
    Qno_case_choice = STATIC_SYMBOL("NO-CASE-CHOICE",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qquote,Qno_case_choice);
    string_constant_64 = 
	    STATIC_STRING("CASE key value did not match any of the CASE statement choices.");
    string_constant_65 = STATIC_STRING("Unknown CASE value type for ~a");
    string_constant_66 = 
	    string_append2(STATIC_STRING("The data type of the CASE value ~NC, ~NT, ~\n                              was not compatible with the type ~NT of the ~\n                              key expression for the CA"),
	    STATIC_STRING("SE statement."));
    string_constant_67 = STATIC_STRING("No values in CASE clause.");
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    if (Tightest_end_of_loop_tag == UNBOUND)
	Tightest_end_of_loop_tag = Nil;
    Qrepeat_statement = STATIC_SYMBOL("REPEAT-STATEMENT",AB_package);
    Qwrite_repeat_statement = STATIC_SYMBOL("WRITE-REPEAT-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_repeat_statement,
	    STATIC_FUNCTION(write_repeat_statement,NIL,FALSE,1,1));
    mutate_global_property(Qrepeat_statement,
	    SYMBOL_FUNCTION(Qwrite_repeat_statement),
	    Qprocedure_statement_writer);
    repeat_statement_compiler_1 = 
	    STATIC_FUNCTION(repeat_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qrepeat_statement,repeat_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qexit_if_statement = STATIC_SYMBOL("EXIT-IF-STATEMENT",AB_package);
    Qwrite_exit_if_statement = STATIC_SYMBOL("WRITE-EXIT-IF-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_exit_if_statement,
	    STATIC_FUNCTION(write_exit_if_statement,NIL,FALSE,1,1));
    mutate_global_property(Qexit_if_statement,
	    SYMBOL_FUNCTION(Qwrite_exit_if_statement),
	    Qprocedure_statement_writer);
    string_constant_68 = 
	    STATIC_STRING("Exit if statement was not within an iteration form.");
    exit_if_statement_compiler_1 = 
	    STATIC_FUNCTION(exit_if_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qexit_if_statement,exit_if_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qwrite_for_each_statement = STATIC_SYMBOL("WRITE-FOR-EACH-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_for_each_statement,
	    STATIC_FUNCTION(write_for_each_statement,NIL,FALSE,1,1));
    mutate_global_property(Qfor_each_statement,
	    SYMBOL_FUNCTION(Qwrite_for_each_statement),
	    Qprocedure_statement_writer);
    string_constant_69 = 
	    STATIC_STRING("The local name ~a is declared to be of type ~NT but the ~\n                     iteration reference returns values of type ~NT.");
    string_constant_70 = 
	    STATIC_STRING("All local names for procedures must be declared at the top of ~\n               the procedure definition.  This designation could not be ~\n               compiled: ~ND.");
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qrequired_domain_types_of_role = 
	    STATIC_SYMBOL("REQUIRED-DOMAIN-TYPES-OF-ROLE",AB_package);
    array_constant_41 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)31L,(SI_Long)57344L);
    string_constant_71 = 
	    STATIC_STRING(", ~a, did not match the required count, ~a");
    Qopen_role_iteration_no_domain = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN",AB_package);
    Qopen_role_iteration = STATIC_SYMBOL("OPEN-ROLE-ITERATION",AB_package);
    Qserve_next_iteration_value = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE",AB_package);
    Qclose_iteration = STATIC_SYMBOL("CLOSE-ITERATION",AB_package);
    for_each_statement_compiler_1 = 
	    STATIC_FUNCTION(for_each_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qfor_each_statement,
	    for_each_statement_compiler_1,Qprocedure_statement_compiler);
    mutate_global_property(Qfor_each_in_parallel_statement,
	    SYMBOL_FUNCTION(Qwrite_for_each_statement),
	    Qprocedure_statement_writer);
    for_each_in_parallel_statement_compiler_1 = 
	    STATIC_FUNCTION(for_each_in_parallel_statement_compiler,NIL,
	    FALSE,1,1);
    mutate_global_property(Qfor_each_in_parallel_statement,
	    for_each_in_parallel_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qprocedure_flags = STATIC_SYMBOL("PROCEDURE-FLAGS",AB_package);
    Qcall_scheduled_code_body = STATIC_SYMBOL("CALL-SCHEDULED-CODE-BODY",
	    AB_package);
    Qallow_other_processing = STATIC_SYMBOL("ALLOW-OTHER-PROCESSING",
	    AB_package);
    Qpause_if_called_code_bodies = 
	    STATIC_SYMBOL("PAUSE-IF-CALLED-CODE-BODIES",AB_package);
    Qwait_for_called_code_bodies = 
	    STATIC_SYMBOL("WAIT-FOR-CALLED-CODE-BODIES",AB_package);
    mutate_global_property(Qfor_each_in_parallel_race_statement,
	    SYMBOL_FUNCTION(Qwrite_for_each_statement),
	    Qprocedure_statement_writer);
    for_each_in_parallel_race_statement_compiler_1 = 
	    STATIC_FUNCTION(for_each_in_parallel_race_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qfor_each_in_parallel_race_statement,
	    for_each_in_parallel_race_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qfor_numeric_statement = STATIC_SYMBOL("FOR-NUMERIC-STATEMENT",AB_package);
    Qprint_for_numeric_statement = 
	    STATIC_SYMBOL("PRINT-FOR-NUMERIC-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_for_numeric_statement,
	    STATIC_FUNCTION(print_for_numeric_statement,NIL,FALSE,1,1));
    mutate_global_property(Qfor_numeric_statement,
	    SYMBOL_FUNCTION(Qprint_for_numeric_statement),
	    Qprocedure_statement_writer);
    for_numeric_statement_compiler_1 = 
	    STATIC_FUNCTION(for_numeric_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qfor_numeric_statement,
	    for_numeric_statement_compiler_1,Qprocedure_statement_compiler);
    string_constant_72 = 
	    STATIC_STRING("The iteration variable ~a was of type ~NT instead of being ~\n                 of type ~NT.");
    Qdo_in_parallel_until_one_completes = 
	    STATIC_SYMBOL("DO-IN-PARALLEL-UNTIL-ONE-COMPLETES",AB_package);
    string_constant_73 = 
	    STATIC_STRING("The iteration variable ~a was of type ~NT instead of being ~\n                 of type ~NF.");
    Qgo_to_statement = STATIC_SYMBOL("GO-TO-STATEMENT",AB_package);
    Qwrite_go_to_statement = STATIC_SYMBOL("WRITE-GO-TO-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_go_to_statement,
	    STATIC_FUNCTION(write_go_to_statement,NIL,FALSE,1,1));
    mutate_global_property(Qgo_to_statement,
	    SYMBOL_FUNCTION(Qwrite_go_to_statement),
	    Qprocedure_statement_writer);
    go_to_statement_compiler_1 = STATIC_FUNCTION(go_to_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qgo_to_statement,go_to_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qwrite_tag_statement = STATIC_SYMBOL("WRITE-TAG-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tag_statement,
	    STATIC_FUNCTION(write_tag_statement,NIL,FALSE,1,1));
    mutate_global_property(Qtag_statement,
	    SYMBOL_FUNCTION(Qwrite_tag_statement),Qprocedure_statement_writer);
    tag_statement_compiler_1 = STATIC_FUNCTION(tag_statement_compiler,NIL,
	    FALSE,1,1);
    mutate_global_property(Qtag_statement,tag_statement_compiler_1,
	    Qprocedure_statement_compiler);
    tag_statement_goto_tag_recorder_1 = 
	    STATIC_FUNCTION(tag_statement_goto_tag_recorder,NIL,FALSE,1,1);
    mutate_global_property(Qtag_statement,
	    tag_statement_goto_tag_recorder_1,Qgoto_tag_recorder);
    Qwrite_begin_statement = STATIC_SYMBOL("WRITE-BEGIN-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_begin_statement,
	    STATIC_FUNCTION(write_begin_statement,NIL,FALSE,1,1));
    mutate_global_property(Qbegin_statement,
	    SYMBOL_FUNCTION(Qwrite_begin_statement),
	    Qprocedure_statement_writer);
    begin_statement_compiler_1 = STATIC_FUNCTION(begin_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qbegin_statement,begin_statement_compiler_1,
	    Qprocedure_statement_compiler);
    begin_statement_goto_tag_recorder_1 = 
	    STATIC_FUNCTION(begin_statement_goto_tag_recorder,NIL,FALSE,1,1);
    mutate_global_property(Qbegin_statement,
	    begin_statement_goto_tag_recorder_1,Qgoto_tag_recorder);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    Qwrite_call_assignment_statement = 
	    STATIC_SYMBOL("WRITE-CALL-ASSIGNMENT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_call_assignment_statement,
	    STATIC_FUNCTION(write_call_assignment_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcall_assignment_statement,
	    SYMBOL_FUNCTION(Qwrite_call_assignment_statement),
	    Qprocedure_statement_writer);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qremote_procedure_declaration);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qmethod_declaration);
    string_constant_74 = 
	    STATIC_STRING("Because of an argument count mismatch for ~ND, a call to it ~\n                could not be optimized.");
    string_constant_75 = 
	    STATIC_STRING("Because of a return value count mismatch for ~ND, a call to ~\n                it could not be optimized.");
    string_constant_76 = 
	    STATIC_STRING("Because of a return type mismatch for ~ND, a call to it could ~\n                not be optimized.");
    Qstable_compile_time_selected_method = 
	    STATIC_SYMBOL("STABLE-COMPILE-TIME-SELECTED-METHOD",AB_package);
    Qstable_remote_procedure_call = 
	    STATIC_SYMBOL("STABLE-REMOTE-PROCEDURE-CALL",AB_package);
    Qstable_procedure_call = STATIC_SYMBOL("STABLE-PROCEDURE-CALL",AB_package);
    Qdependent_call = STATIC_SYMBOL("DEPENDENT-CALL",AB_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qreceive_values = STATIC_SYMBOL("RECEIVE-VALUES",AB_package);
    Qdependent_call_rpc = STATIC_SYMBOL("DEPENDENT-CALL-RPC",AB_package);
    Qcall_rpc = STATIC_SYMBOL("CALL-RPC",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_10 = STATIC_CONS(Qunknown_datum,Qnil);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_11 = STATIC_CONS(Qno_item,Qnil);
    Qremote_procedure_call = STATIC_SYMBOL("REMOTE-PROCEDURE-CALL",AB_package);
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    call_assignment_statement_compiler_1 = 
	    STATIC_FUNCTION(call_assignment_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qcall_assignment_statement,
	    call_assignment_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qwrite_call_next_method_assignment_statement = 
	    STATIC_SYMBOL("WRITE-CALL-NEXT-METHOD-ASSIGNMENT-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_call_next_method_assignment_statement,
	    STATIC_FUNCTION(write_call_next_method_assignment_statement,
	    NIL,FALSE,1,1));
    mutate_global_property(Qcall_next_method_assignment_statement,
	    SYMBOL_FUNCTION(Qwrite_call_next_method_assignment_statement),
	    Qprocedure_statement_writer);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab_class,Qab_method);
    Qnext_procedure_method = STATIC_SYMBOL("NEXT-PROCEDURE-METHOD",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,
	    list_constant_11);
    Qexists = STATIC_SYMBOL("EXISTS",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qab_no_next_method = STATIC_SYMBOL("NO-NEXT-METHOD",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qquote,Qab_no_next_method);
    string_constant_77 = 
	    STATIC_STRING("There is no next method defined for this method and arguments.");
    call_next_method_assignment_statement_compiler_1 = 
	    STATIC_FUNCTION(call_next_method_assignment_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcall_next_method_assignment_statement,
	    call_next_method_assignment_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qsystem_call_assignment_statement = 
	    STATIC_SYMBOL("SYSTEM-CALL-ASSIGNMENT-STATEMENT",AB_package);
    Qwrite_system_call_assignment_statement = 
	    STATIC_SYMBOL("WRITE-SYSTEM-CALL-ASSIGNMENT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_system_call_assignment_statement,
	    STATIC_FUNCTION(write_system_call_assignment_statement,NIL,
	    FALSE,1,1));
    mutate_global_property(Qsystem_call_assignment_statement,
	    SYMBOL_FUNCTION(Qwrite_system_call_assignment_statement),
	    Qprocedure_statement_writer);
    system_call_assignment_statement_compiler_1 = 
	    STATIC_FUNCTION(system_call_assignment_statement_compiler,NIL,
	    FALSE,1,1);
    mutate_global_property(Qsystem_call_assignment_statement,
	    system_call_assignment_statement_compiler_1,
	    Qprocedure_statement_compiler);
    string_constant_78 = 
	    STATIC_STRING("The System-Call statement can not accept more than ~a arguments.");
    string_constant_79 = 
	    STATIC_STRING("The System-Call statement can not return more than ~a values.");
    Qsystem_call = STATIC_SYMBOL("SYSTEM-CALL",AB_package);
    Qcall_statement = STATIC_SYMBOL("CALL-STATEMENT",AB_package);
    Qwrite_call_statement = STATIC_SYMBOL("WRITE-CALL-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_call_statement,
	    STATIC_FUNCTION(write_call_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcall_statement,
	    SYMBOL_FUNCTION(Qwrite_call_statement),
	    Qprocedure_statement_writer);
    call_statement_compiler_1 = STATIC_FUNCTION(call_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qcall_statement,call_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qwrite_call_next_method_statement = 
	    STATIC_SYMBOL("WRITE-CALL-NEXT-METHOD-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_call_next_method_statement,
	    STATIC_FUNCTION(write_call_next_method_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcall_next_method_statement,
	    SYMBOL_FUNCTION(Qwrite_call_next_method_statement),
	    Qprocedure_statement_writer);
    call_next_method_statement_compiler_1 = 
	    STATIC_FUNCTION(call_next_method_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qcall_next_method_statement,
	    call_next_method_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qsystem_call_statement = STATIC_SYMBOL("SYSTEM-CALL-STATEMENT",AB_package);
    Qwrite_system_call_statement = 
	    STATIC_SYMBOL("WRITE-SYSTEM-CALL-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_system_call_statement,
	    STATIC_FUNCTION(write_system_call_statement,NIL,FALSE,1,1));
    mutate_global_property(Qsystem_call_statement,
	    SYMBOL_FUNCTION(Qwrite_system_call_statement),
	    Qprocedure_statement_writer);
    system_call_statement_compiler_1 = 
	    STATIC_FUNCTION(system_call_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qsystem_call_statement,
	    system_call_statement_compiler_1,Qprocedure_statement_compiler);
    Qsystem_action_statement = STATIC_SYMBOL("SYSTEM-ACTION-STATEMENT",
	    AB_package);
    mutate_global_property(Qsystem_action_statement,
	    SYMBOL_FUNCTION(Qwrite_system_call_statement),
	    Qprocedure_statement_writer);
    system_action_statement_compiler_1 = 
	    STATIC_FUNCTION(system_action_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qsystem_action_statement,
	    system_action_statement_compiler_1,Qprocedure_statement_compiler);
    array_constant_42 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)57344L);
    Qshow_statement = STATIC_SYMBOL("SHOW-STATEMENT",AB_package);
    Qwrite_show_statement = STATIC_SYMBOL("WRITE-SHOW-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_show_statement,
	    STATIC_FUNCTION(write_show_statement,NIL,FALSE,1,1));
    mutate_global_property(Qshow_statement,
	    SYMBOL_FUNCTION(Qwrite_show_statement),
	    Qprocedure_statement_writer);
    Qshow_new = STATIC_SYMBOL("SHOW-NEW",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_15 = STATIC_CONS(Qab_structure,Qnil);
    show_statement_compiler_1 = STATIC_FUNCTION(show_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qshow_statement,show_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_43 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)23L,(SI_Long)57344L);
    Qcreate_statement = STATIC_SYMBOL("CREATE-STATEMENT",AB_package);
    Qwrite_create_statement = STATIC_SYMBOL("WRITE-CREATE-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_create_statement,
	    STATIC_FUNCTION(write_create_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcreate_statement,
	    SYMBOL_FUNCTION(Qwrite_create_statement),
	    Qprocedure_statement_writer);
    string_constant_80 = 
	    STATIC_STRING("In the create action, the local name ~a is declared to ~\n                       hold ~NT, not ~NT.");
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    create_statement_compiler_1 = 
	    STATIC_FUNCTION(create_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qcreate_statement,create_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_44 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)17L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)23L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)31L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)57344L);
    Qdelete_statement = STATIC_SYMBOL("DELETE-STATEMENT",AB_package);
    Qwrite_delete_statement = STATIC_SYMBOL("WRITE-DELETE-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_delete_statement,
	    STATIC_FUNCTION(write_delete_statement,NIL,FALSE,1,1));
    mutate_global_property(Qdelete_statement,
	    SYMBOL_FUNCTION(Qwrite_delete_statement),
	    Qprocedure_statement_writer);
    delete_statement_compiler_1 = 
	    STATIC_FUNCTION(delete_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qdelete_statement,delete_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_46 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)23L,(SI_Long)57344L);
    Qactivate_statement = STATIC_SYMBOL("ACTIVATE-STATEMENT",AB_package);
    Qwrite_activate_statement = STATIC_SYMBOL("WRITE-ACTIVATE-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_activate_statement,
	    STATIC_FUNCTION(write_activate_statement,NIL,FALSE,1,1));
    mutate_global_property(Qactivate_statement,
	    SYMBOL_FUNCTION(Qwrite_activate_statement),
	    Qprocedure_statement_writer);
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    activate_statement_compiler_1 = 
	    STATIC_FUNCTION(activate_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qactivate_statement,
	    activate_statement_compiler_1,Qprocedure_statement_compiler);
    array_constant_47 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)13L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)23L,(SI_Long)57344L);
    Qdeactivate_statement = STATIC_SYMBOL("DEACTIVATE-STATEMENT",AB_package);
    Qwrite_deactivate_statement = 
	    STATIC_SYMBOL("WRITE-DEACTIVATE-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_deactivate_statement,
	    STATIC_FUNCTION(write_deactivate_statement,NIL,FALSE,1,1));
    mutate_global_property(Qdeactivate_statement,
	    SYMBOL_FUNCTION(Qwrite_deactivate_statement),
	    Qprocedure_statement_writer);
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    deactivate_statement_compiler_1 = 
	    STATIC_FUNCTION(deactivate_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qdeactivate_statement,
	    deactivate_statement_compiler_1,Qprocedure_statement_compiler);
    array_constant_48 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)15L,(SI_Long)57344L);
    Qhide_statement = STATIC_SYMBOL("HIDE-STATEMENT",AB_package);
    Qwrite_hide_statement = STATIC_SYMBOL("WRITE-HIDE-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hide_statement,
	    STATIC_FUNCTION(write_hide_statement,NIL,FALSE,1,1));
    mutate_global_property(Qhide_statement,
	    SYMBOL_FUNCTION(Qwrite_hide_statement),
	    Qprocedure_statement_writer);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    hide_statement_compiler_1 = STATIC_FUNCTION(hide_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qhide_statement,hide_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_49 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)12L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)15L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)31L,(SI_Long)57344L);
    Qstart_kb_statement = STATIC_SYMBOL("START-KB-STATEMENT",AB_package);
    Qwrite_start_kb_statement = STATIC_SYMBOL("WRITE-START-KB-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_start_kb_statement,
	    STATIC_FUNCTION(write_start_kb_statement,NIL,FALSE,1,1));
    mutate_global_property(Qstart_kb_statement,
	    SYMBOL_FUNCTION(Qwrite_start_kb_statement),
	    Qprocedure_statement_writer);
    Qstart_kb_epilog = STATIC_SYMBOL("START-KB-EPILOG",AB_package);
    start_kb_statement_compiler_1 = 
	    STATIC_FUNCTION(start_kb_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qstart_kb_statement,
	    start_kb_statement_compiler_1,Qprocedure_statement_compiler);
    array_constant_50 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)12L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)15L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)31L,(SI_Long)57344L);
    Qreset_kb_statement = STATIC_SYMBOL("RESET-KB-STATEMENT",AB_package);
    mutate_global_property(Qreset_kb_statement,
	    SYMBOL_FUNCTION(Qwrite_start_kb_statement),
	    Qprocedure_statement_writer);
    Qreset_kb_epilog = STATIC_SYMBOL("RESET-KB-EPILOG",AB_package);
    reset_kb_statement_compiler_1 = 
	    STATIC_FUNCTION(reset_kb_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qreset_kb_statement,
	    reset_kb_statement_compiler_1,Qprocedure_statement_compiler);
    array_constant_51 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)15L,(SI_Long)57344L);
    Qenable_statement = STATIC_SYMBOL("ENABLE-STATEMENT",AB_package);
    Qwrite_enable_statement = STATIC_SYMBOL("WRITE-ENABLE-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_enable_statement,
	    STATIC_FUNCTION(write_enable_statement,NIL,FALSE,1,1));
    mutate_global_property(Qenable_statement,
	    SYMBOL_FUNCTION(Qwrite_enable_statement),
	    Qprocedure_statement_writer);
    Qenable = STATIC_SYMBOL("ENABLE",AB_package);
    enable_statement_compiler_1 = 
	    STATIC_FUNCTION(enable_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qenable_statement,enable_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_52 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)23L,(SI_Long)57344L);
    Qdisable_statement = STATIC_SYMBOL("DISABLE-STATEMENT",AB_package);
    Qwrite_disable_statement = STATIC_SYMBOL("WRITE-DISABLE-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_disable_statement,
	    STATIC_FUNCTION(write_disable_statement,NIL,FALSE,1,1));
    mutate_global_property(Qdisable_statement,
	    SYMBOL_FUNCTION(Qwrite_disable_statement),
	    Qprocedure_statement_writer);
    Qdisable = STATIC_SYMBOL("DISABLE",AB_package);
    disable_statement_compiler_1 = 
	    STATIC_FUNCTION(disable_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qdisable_statement,disable_statement_compiler_1,
	    Qprocedure_statement_compiler);
    array_constant_53 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)15L,(SI_Long)57344L);
    Qprint_statement = STATIC_SYMBOL("PRINT-STATEMENT",AB_package);
    Qwrite_print_statement = STATIC_SYMBOL("WRITE-PRINT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_print_statement,
	    STATIC_FUNCTION(write_print_statement,NIL,FALSE,1,1));
    mutate_global_property(Qprint_statement,
	    SYMBOL_FUNCTION(Qwrite_print_statement),
	    Qprocedure_statement_writer);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qab_class,Qworkspace);
    print_statement_compiler_1 = STATIC_FUNCTION(print_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qprint_statement,print_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qallow_other_processing_statement = 
	    STATIC_SYMBOL("ALLOW-OTHER-PROCESSING-STATEMENT",AB_package);
    Qwrite_allow_other_processing_statement = 
	    STATIC_SYMBOL("WRITE-ALLOW-OTHER-PROCESSING-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_allow_other_processing_statement,
	    STATIC_FUNCTION(write_allow_other_processing_statement,NIL,
	    FALSE,1,1));
    mutate_global_property(Qallow_other_processing_statement,
	    SYMBOL_FUNCTION(Qwrite_allow_other_processing_statement),
	    Qprocedure_statement_writer);
    allow_other_processing_statement_compiler_1 = 
	    STATIC_FUNCTION(allow_other_processing_statement_compiler,NIL,
	    FALSE,1,1);
    mutate_global_property(Qallow_other_processing_statement,
	    allow_other_processing_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qcollect_data_statement = STATIC_SYMBOL("COLLECT-DATA-STATEMENT",
	    AB_package);
    Qwrite_collect_data_statement = 
	    STATIC_SYMBOL("WRITE-COLLECT-DATA-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_collect_data_statement,
	    STATIC_FUNCTION(write_collect_data_statement,NIL,FALSE,1,1));
    mutate_global_property(Qcollect_data_statement,
	    SYMBOL_FUNCTION(Qwrite_collect_data_statement),
	    Qprocedure_statement_writer);
    Qcurrent_subsecond_time = STATIC_SYMBOL("CURRENT-SUBSECOND-TIME",
	    AB_package);
    list_constant_17 = STATIC_CONS(Qcurrent_subsecond_time,Qnil);
    Qcollect_data = STATIC_SYMBOL("COLLECT-DATA",AB_package);
    collect_data_statement_compiler_1 = 
	    STATIC_FUNCTION(collect_data_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qcollect_data_statement,
	    collect_data_statement_compiler_1,Qprocedure_statement_compiler);
    Qdo_in_parallel_statement = STATIC_SYMBOL("DO-IN-PARALLEL-STATEMENT",
	    AB_package);
    Qwrite_do_in_parallel_statement = 
	    STATIC_SYMBOL("WRITE-DO-IN-PARALLEL-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_do_in_parallel_statement,
	    STATIC_FUNCTION(write_do_in_parallel_statement,NIL,FALSE,1,1));
    mutate_global_property(Qdo_in_parallel_statement,
	    SYMBOL_FUNCTION(Qwrite_do_in_parallel_statement),
	    Qprocedure_statement_writer);
    Qcall_code_body = STATIC_SYMBOL("CALL-CODE-BODY",AB_package);
    do_in_parallel_statement_compiler_1 = 
	    STATIC_FUNCTION(do_in_parallel_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qdo_in_parallel_statement,
	    do_in_parallel_statement_compiler_1,Qprocedure_statement_compiler);
    Qdo_in_parallel_until_one_completes_statement = 
	    STATIC_SYMBOL("DO-IN-PARALLEL-UNTIL-ONE-COMPLETES-STATEMENT",
	    AB_package);
    Qwrite_do_in_parallel_until_one_completes_statement = 
	    STATIC_SYMBOL("WRITE-DO-IN-PARALLEL-UNTIL-ONE-COMPLETES-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_do_in_parallel_until_one_completes_statement,
	    STATIC_FUNCTION(write_do_in_parallel_until_one_completes_statement,
	    NIL,FALSE,1,1));
    mutate_global_property(Qdo_in_parallel_until_one_completes_statement,
	    SYMBOL_FUNCTION(Qwrite_do_in_parallel_until_one_completes_statement),
	    Qprocedure_statement_writer);
    do_in_parallel_until_one_completes_statement_compiler_1 = 
	    STATIC_FUNCTION(do_in_parallel_until_one_completes_statement_compiler,
	    NIL,FALSE,1,1);
    mutate_global_property(Qdo_in_parallel_until_one_completes_statement,
	    do_in_parallel_until_one_completes_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qwait_for_statement = STATIC_SYMBOL("WAIT-FOR-STATEMENT",AB_package);
    Qwrite_wait_for_statement = STATIC_SYMBOL("WRITE-WAIT-FOR-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_wait_for_statement,
	    STATIC_FUNCTION(write_wait_for_statement,NIL,FALSE,1,1));
    mutate_global_property(Qwait_for_statement,
	    SYMBOL_FUNCTION(Qwrite_wait_for_statement),
	    Qprocedure_statement_writer);
    Qwait_for_interval = STATIC_SYMBOL("WAIT-FOR-INTERVAL",AB_package);
    wait_for_statement_compiler_1 = 
	    STATIC_FUNCTION(wait_for_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qwait_for_statement,
	    wait_for_statement_compiler_1,Qprocedure_statement_compiler);
    Qwait_until_statement = STATIC_SYMBOL("WAIT-UNTIL-STATEMENT",AB_package);
    Qwrite_wait_until_statement = 
	    STATIC_SYMBOL("WRITE-WAIT-UNTIL-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_wait_until_statement,
	    STATIC_FUNCTION(write_wait_until_statement,NIL,FALSE,1,1));
    mutate_global_property(Qwait_until_statement,
	    SYMBOL_FUNCTION(Qwrite_wait_until_statement),
	    Qprocedure_statement_writer);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant_10);
    Qpolled_wait = STATIC_SYMBOL("POLLED-WAIT",AB_package);
    wait_until_statement_compiler_1 = 
	    STATIC_FUNCTION(wait_until_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qwait_until_statement,
	    wait_until_statement_compiler_1,Qprocedure_statement_compiler);
    Qwait_until_event_statement = 
	    STATIC_SYMBOL("WAIT-UNTIL-EVENT-STATEMENT",AB_package);
    Qwrite_wait_until_event_statement = 
	    STATIC_SYMBOL("WRITE-WAIT-UNTIL-EVENT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_wait_until_event_statement,
	    STATIC_FUNCTION(write_wait_until_event_statement,NIL,FALSE,1,1));
    mutate_global_property(Qwait_until_event_statement,
	    SYMBOL_FUNCTION(Qwrite_wait_until_event_statement),
	    Qprocedure_statement_writer);
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    list_constant_25 = STATIC_CONS(Qplace_reference,Qnil);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_24,
	    list_constant_25);
    Qinstall_event_detector = STATIC_SYMBOL("INSTALL-EVENT-DETECTOR",
	    AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qquote,Qreceives_a_value);
    string_constant_81 = STATIC_STRING("wait until event statement");
    string_constant_82 = STATIC_STRING("The malformed event ~a was received.");
    Qwait = STATIC_SYMBOL("WAIT",AB_package);
    Qclear_event_detectors = STATIC_SYMBOL("CLEAR-EVENT-DETECTORS",AB_package);
    wait_until_event_statement_compiler_1 = 
	    STATIC_FUNCTION(wait_until_event_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qwait_until_event_statement,
	    wait_until_event_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qsystem_wait_statement = STATIC_SYMBOL("SYSTEM-WAIT-STATEMENT",AB_package);
    Qwrite_system_wait_statement = 
	    STATIC_SYMBOL("WRITE-SYSTEM-WAIT-STATEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_system_wait_statement,
	    STATIC_FUNCTION(write_system_wait_statement,NIL,FALSE,1,1));
    mutate_global_property(Qsystem_wait_statement,
	    SYMBOL_FUNCTION(Qwrite_system_wait_statement),
	    Qprocedure_statement_writer);
    system_wait_statement_compiler_1 = 
	    STATIC_FUNCTION(system_wait_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qsystem_wait_statement,
	    system_wait_statement_compiler_1,Qprocedure_statement_compiler);
    Qon_error_statement = STATIC_SYMBOL("ON-ERROR-STATEMENT",AB_package);
    Qprint_on_error_statement = STATIC_SYMBOL("PRINT-ON-ERROR-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_on_error_statement,
	    STATIC_FUNCTION(print_on_error_statement,NIL,FALSE,1,1));
    mutate_global_property(Qon_error_statement,
	    SYMBOL_FUNCTION(Qprint_on_error_statement),
	    Qprocedure_statement_writer);
    on_error_statement_compiler_1 = 
	    STATIC_FUNCTION(on_error_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qon_error_statement,
	    on_error_statement_compiler_1,Qprocedure_statement_compiler);
    Qon_error_statement_new = STATIC_SYMBOL("ON-ERROR-STATEMENT-NEW",
	    AB_package);
    Qprint_on_error_statement_new = 
	    STATIC_SYMBOL("PRINT-ON-ERROR-STATEMENT-NEW",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_on_error_statement_new,
	    STATIC_FUNCTION(print_on_error_statement_new,NIL,FALSE,1,1));
    mutate_global_property(Qon_error_statement_new,
	    SYMBOL_FUNCTION(Qprint_on_error_statement_new),
	    Qprocedure_statement_writer);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qab_class,Qerror);
    on_error_statement_new_compiler_1 = 
	    STATIC_FUNCTION(on_error_statement_new_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qon_error_statement_new,
	    on_error_statement_new_compiler_1,Qprocedure_statement_compiler);
    string_constant_83 = 
	    STATIC_STRING("No type could be determined for the local varible ~a.");
    string_constant_84 = 
	    STATIC_STRING("The type of ~a, ~NT does not allow it to receive values of ~\n                  type ~NT.");
    Qsignal_statement = STATIC_SYMBOL("SIGNAL-STATEMENT",AB_package);
    Qprint_signal_statement = STATIC_SYMBOL("PRINT-SIGNAL-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_signal_statement,
	    STATIC_FUNCTION(print_signal_statement,NIL,FALSE,1,1));
    mutate_global_property(Qsignal_statement,
	    SYMBOL_FUNCTION(Qprint_signal_statement),
	    Qprocedure_statement_writer);
    signal_statement_compiler_1 = 
	    STATIC_FUNCTION(signal_statement_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qsignal_statement,signal_statement_compiler_1,
	    Qprocedure_statement_compiler);
    Qsignal_statement_new = STATIC_SYMBOL("SIGNAL-STATEMENT-NEW",AB_package);
    Qprint_signal_statement_new = 
	    STATIC_SYMBOL("PRINT-SIGNAL-STATEMENT-NEW",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_signal_statement_new,
	    STATIC_FUNCTION(print_signal_statement_new,NIL,FALSE,1,1));
    mutate_global_property(Qsignal_statement_new,
	    SYMBOL_FUNCTION(Qprint_signal_statement_new),
	    Qprocedure_statement_writer);
    Qsignal_error_new = STATIC_SYMBOL("SIGNAL-ERROR-NEW",AB_package);
    signal_statement_new_compiler_1 = 
	    STATIC_FUNCTION(signal_statement_new_compiler,NIL,FALSE,1,1);
    mutate_global_property(Qsignal_statement_new,
	    signal_statement_new_compiler_1,Qprocedure_statement_compiler);
    Qbranch_tag_referencer = STATIC_SYMBOL("BRANCH-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_tag_referencer,
	    STATIC_FUNCTION(branch_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch,SYMBOL_FUNCTION(Qbranch_tag_referencer),
	    Qgoto_tag_references);
    Qbranch_tag_replacer = STATIC_SYMBOL("BRANCH-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_tag_replacer,
	    STATIC_FUNCTION(branch_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch,SYMBOL_FUNCTION(Qbranch_tag_replacer),
	    Qgoto_tag_replacer);
    Qbranch_if_known = STATIC_SYMBOL("BRANCH-IF-KNOWN",AB_package);
    Qbranch_if_known_tag_referencer = 
	    STATIC_SYMBOL("BRANCH-IF-KNOWN-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_known_tag_referencer,
	    STATIC_FUNCTION(branch_if_known_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_known,
	    SYMBOL_FUNCTION(Qbranch_if_known_tag_referencer),
	    Qgoto_tag_references);
    Qbranch_if_known_tag_replacer = 
	    STATIC_SYMBOL("BRANCH-IF-KNOWN-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_known_tag_replacer,
	    STATIC_FUNCTION(branch_if_known_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_known,
	    SYMBOL_FUNCTION(Qbranch_if_known_tag_replacer),Qgoto_tag_replacer);
    Qrestore_from_action_cache_or_branch = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH",AB_package);
    Qrestore_from_action_cache_or_branch_tag_referencer = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH-TAG-REFERENCER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrestore_from_action_cache_or_branch_tag_referencer,
	    STATIC_FUNCTION(restore_from_action_cache_or_branch_tag_referencer,
	    NIL,FALSE,1,1));
    mutate_global_property(Qrestore_from_action_cache_or_branch,
	    SYMBOL_FUNCTION(Qrestore_from_action_cache_or_branch_tag_referencer),
	    Qgoto_tag_references);
    Qrestore_from_action_cache_or_branch_tag_replacer = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH-TAG-REPLACER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrestore_from_action_cache_or_branch_tag_replacer,
	    STATIC_FUNCTION(restore_from_action_cache_or_branch_tag_replacer,
	    NIL,FALSE,1,1));
    mutate_global_property(Qrestore_from_action_cache_or_branch,
	    SYMBOL_FUNCTION(Qrestore_from_action_cache_or_branch_tag_replacer),
	    Qgoto_tag_replacer);
    Qbranch_if_true_tag_referencer = 
	    STATIC_SYMBOL("BRANCH-IF-TRUE-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_true_tag_referencer,
	    STATIC_FUNCTION(branch_if_true_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_true,
	    SYMBOL_FUNCTION(Qbranch_if_true_tag_referencer),
	    Qgoto_tag_references);
    Qbranch_if_true_tag_replacer = 
	    STATIC_SYMBOL("BRANCH-IF-TRUE-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_true_tag_replacer,
	    STATIC_FUNCTION(branch_if_true_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_true,
	    SYMBOL_FUNCTION(Qbranch_if_true_tag_replacer),Qgoto_tag_replacer);
    Qbranch_if_not_true_tag_referencer = 
	    STATIC_SYMBOL("BRANCH-IF-NOT-TRUE-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_not_true_tag_referencer,
	    STATIC_FUNCTION(branch_if_not_true_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_not_true,
	    SYMBOL_FUNCTION(Qbranch_if_not_true_tag_referencer),
	    Qgoto_tag_references);
    Qbranch_if_not_true_tag_replacer = 
	    STATIC_SYMBOL("BRANCH-IF-NOT-TRUE-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qbranch_if_not_true_tag_replacer,
	    STATIC_FUNCTION(branch_if_not_true_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qbranch_if_not_true,
	    SYMBOL_FUNCTION(Qbranch_if_not_true_tag_replacer),
	    Qgoto_tag_replacer);
    Qcase_dispatch_tag_referencer = 
	    STATIC_SYMBOL("CASE-DISPATCH-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qcase_dispatch_tag_referencer,
	    STATIC_FUNCTION(case_dispatch_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qcase_dispatch,
	    SYMBOL_FUNCTION(Qcase_dispatch_tag_referencer),
	    Qgoto_tag_references);
    Qcase_dispatch_tag_replacer = 
	    STATIC_SYMBOL("CASE-DISPATCH-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qcase_dispatch_tag_replacer,
	    STATIC_FUNCTION(case_dispatch_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qcase_dispatch,
	    SYMBOL_FUNCTION(Qcase_dispatch_tag_replacer),Qgoto_tag_replacer);
    Qopen_role_iteration_tag_referencer = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qopen_role_iteration_tag_referencer,
	    STATIC_FUNCTION(open_role_iteration_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qopen_role_iteration,
	    SYMBOL_FUNCTION(Qopen_role_iteration_tag_referencer),
	    Qgoto_tag_references);
    Qopen_role_iteration_tag_replacer = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qopen_role_iteration_tag_replacer,
	    STATIC_FUNCTION(open_role_iteration_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qopen_role_iteration,
	    SYMBOL_FUNCTION(Qopen_role_iteration_tag_replacer),
	    Qgoto_tag_replacer);
    Qopen_role_iteration_no_domain_tag_referencer = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN-TAG-REFERENCER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qopen_role_iteration_no_domain_tag_referencer,
	    STATIC_FUNCTION(open_role_iteration_no_domain_tag_referencer,
	    NIL,FALSE,1,1));
    mutate_global_property(Qopen_role_iteration_no_domain,
	    SYMBOL_FUNCTION(Qopen_role_iteration_no_domain_tag_referencer),
	    Qgoto_tag_references);
    Qopen_role_iteration_no_domain_tag_replacer = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN-TAG-REPLACER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qopen_role_iteration_no_domain_tag_replacer,
	    STATIC_FUNCTION(open_role_iteration_no_domain_tag_replacer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qopen_role_iteration_no_domain,
	    SYMBOL_FUNCTION(Qopen_role_iteration_no_domain_tag_replacer),
	    Qgoto_tag_replacer);
    Qserve_next_iteration_value_tag_referencer = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE-TAG-REFERENCER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_iteration_value_tag_referencer,
	    STATIC_FUNCTION(serve_next_iteration_value_tag_referencer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qserve_next_iteration_value,
	    SYMBOL_FUNCTION(Qserve_next_iteration_value_tag_referencer),
	    Qgoto_tag_references);
    Qserve_next_iteration_value_tag_replacer = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE-TAG-REPLACER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_iteration_value_tag_replacer,
	    STATIC_FUNCTION(serve_next_iteration_value_tag_replacer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qserve_next_iteration_value,
	    SYMBOL_FUNCTION(Qserve_next_iteration_value_tag_replacer),
	    Qgoto_tag_replacer);
    Qjump_tag_replacer = STATIC_SYMBOL("JUMP-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qjump_tag_replacer,
	    STATIC_FUNCTION(jump_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qjump,SYMBOL_FUNCTION(Qjump_tag_replacer),
	    Qgoto_tag_replacer);
    Qjump_tag_referencer = STATIC_SYMBOL("JUMP-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qjump_tag_referencer,
	    STATIC_FUNCTION(jump_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qjump,SYMBOL_FUNCTION(Qjump_tag_referencer),
	    Qgoto_tag_references);
    Qcollect_data_tag_replacer = STATIC_SYMBOL("COLLECT-DATA-TAG-REPLACER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcollect_data_tag_replacer,
	    STATIC_FUNCTION(collect_data_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qcollect_data,
	    SYMBOL_FUNCTION(Qcollect_data_tag_replacer),Qgoto_tag_replacer);
    Qcollect_data_tag_referencer = 
	    STATIC_SYMBOL("COLLECT-DATA-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qcollect_data_tag_referencer,
	    STATIC_FUNCTION(collect_data_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qcollect_data,
	    SYMBOL_FUNCTION(Qcollect_data_tag_referencer),
	    Qgoto_tag_references);
    Qexecute_antecedent_tag_replacer = 
	    STATIC_SYMBOL("EXECUTE-ANTECEDENT-TAG-REPLACER",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_antecedent_tag_replacer,
	    STATIC_FUNCTION(execute_antecedent_tag_replacer,NIL,FALSE,1,1));
    mutate_global_property(Qexecute_antecedent,
	    SYMBOL_FUNCTION(Qexecute_antecedent_tag_replacer),
	    Qgoto_tag_replacer);
    Qexecute_antecedent_tag_referencer = 
	    STATIC_SYMBOL("EXECUTE-ANTECEDENT-TAG-REFERENCER",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_antecedent_tag_referencer,
	    STATIC_FUNCTION(execute_antecedent_tag_referencer,NIL,FALSE,1,1));
    mutate_global_property(Qexecute_antecedent,
	    SYMBOL_FUNCTION(Qexecute_antecedent_tag_referencer),
	    Qgoto_tag_references);
    Qexecute_simulation_formula = 
	    STATIC_SYMBOL("EXECUTE-SIMULATION-FORMULA",AB_package);
    Qexecute_simulation_formula_tag_replacer = 
	    STATIC_SYMBOL("EXECUTE-SIMULATION-FORMULA-TAG-REPLACER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_simulation_formula_tag_replacer,
	    STATIC_FUNCTION(execute_simulation_formula_tag_replacer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qexecute_simulation_formula,
	    SYMBOL_FUNCTION(Qexecute_simulation_formula_tag_replacer),
	    Qgoto_tag_replacer);
    Qexecute_simulation_formula_tag_referencer = 
	    STATIC_SYMBOL("EXECUTE-SIMULATION-FORMULA-TAG-REFERENCER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_simulation_formula_tag_referencer,
	    STATIC_FUNCTION(execute_simulation_formula_tag_referencer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qexecute_simulation_formula,
	    SYMBOL_FUNCTION(Qexecute_simulation_formula_tag_referencer),
	    Qgoto_tag_references);
}
