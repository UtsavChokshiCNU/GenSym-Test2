/* stktls.c
 * Input file:  stack-utils.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "stktls.h"


static Object Qall;                /* all */

static Object list_constant;       /* # */

/* MAKE-EVALUATOR-DESCRIPTION */
Object make_evaluator_description(evaluator_name,instruction_name,
	    evaluator_instruction_precedence,environments,arguments,
	    result_type,printer_function,
	    implementation_function_or_macro_name,in_line_qm,
	    evaluator_number,result_in_register_1_qm,pprinter_function,
	    function_name_qm)
    Object evaluator_name, instruction_name, evaluator_instruction_precedence;
    Object environments, arguments, result_type, printer_function;
    Object implementation_function_or_macro_name, in_line_qm, evaluator_number;
    Object result_in_register_1_qm, pprinter_function, function_name_qm;
{
    Object new_description, converted_arguments, converted_result_type;
    Object svref_new_value;

    x_note_fn_call(204,0);
    new_description = make_array(1,FIX((SI_Long)15L));
    converted_arguments = arguments;
    converted_result_type = result_type;
    SVREF(new_description,FIX((SI_Long)0L)) = evaluator_name;
    SVREF(new_description,FIX((SI_Long)1L)) = instruction_name;
    SVREF(new_description,FIX((SI_Long)2L)) = evaluator_instruction_precedence;
    svref_new_value = EQ(environments,Qall) ? list_constant : environments;
    SVREF(new_description,FIX((SI_Long)3L)) = svref_new_value;
    SVREF(new_description,FIX((SI_Long)4L)) = converted_arguments;
    SVREF(new_description,FIX((SI_Long)5L)) = converted_result_type;
    SVREF(new_description,FIX((SI_Long)6L)) = printer_function;
    SVREF(new_description,FIX((SI_Long)7L)) = 
	    implementation_function_or_macro_name;
    SVREF(new_description,FIX((SI_Long)8L)) = in_line_qm;
    SVREF(new_description,FIX((SI_Long)9L)) = evaluator_number;
    SVREF(new_description,FIX((SI_Long)10L)) = result_in_register_1_qm;
    SVREF(new_description,FIX((SI_Long)11L)) = pprinter_function;
    SVREF(new_description,FIX((SI_Long)13L)) = function_name_qm;
    return VALUES_1(new_description);
}

static Object Qstack_evaluators;   /* stack-evaluators */

/* REGISTER-IN-LINE-EVALUATOR */
Object register_in_line_evaluator(evaluator_description,
	    evaluator_instruction_number)
    Object evaluator_description, evaluator_instruction_number;
{
    Object old_description, temp, new_instruction_name, gensymed_symbol;
    Object old_description_cons, push_arg, temp_1, stack_evaluators_new_value;

    x_note_fn_call(204,1);
    if (IFIX(evaluator_instruction_number) < (SI_Long)0L || 
	    FIXNUM_GE(evaluator_instruction_number,
	    FIXNUM_ADD(Maximum_number_of_in_line_evaluators,
	    Maximum_number_of_extended_inline_evaluators)))
	error((SI_Long)3L,
		"In-line evaluator number ~a above maximum for ~a.",
		evaluator_instruction_number,ISVREF(evaluator_description,
		(SI_Long)0L));
    if (FIXNUM_EQ(evaluator_instruction_number,Dispatch_instruction_number))
	error((SI_Long)1L,
		"Evaluator instruction number collides with dispatch instruction number");
    old_description = ISVREF(In_line_evaluator_array,
	    IFIX(evaluator_instruction_number));
    if (old_description &&  !EQ(ISVREF(old_description,(SI_Long)1L),
	    ISVREF(evaluator_description,(SI_Long)1L)))
	warn((SI_Long)4L,"In-line evaluator #~a changing from ~a to ~a.",
		evaluator_instruction_number,ISVREF(old_description,
		(SI_Long)1L),ISVREF(evaluator_description,(SI_Long)1L));
    temp = In_line_evaluator_array;
    SVREF(temp,evaluator_instruction_number) = evaluator_description;
    new_instruction_name = ISVREF(evaluator_description,(SI_Long)1L);
    gensymed_symbol = ISVREF(evaluator_description,(SI_Long)0L);
    old_description_cons = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qstack_evaluators);
  next_loop:
    if ( !TRUEP(old_description_cons))
	goto end_loop;
    if (EQ(ISVREF(CAR(old_description_cons),(SI_Long)1L),
		new_instruction_name)) {
	if (FIXNUM_NE(ISVREF(CAR(old_description_cons),(SI_Long)9L),
		ISVREF(evaluator_description,(SI_Long)9L)))
	    warn((SI_Long)4L,
		    "In-line evaluator ~a changing from #~a to #~a.",
		    new_instruction_name,ISVREF(CAR(old_description_cons),
		    (SI_Long)9L),ISVREF(evaluator_description,(SI_Long)9L));
	M_CAR(old_description_cons) = evaluator_description;
	return VALUES_1(Nil);
    }
    old_description_cons = M_CDR(old_description_cons);
    goto next_loop;
  end_loop:
    push_arg = evaluator_description;
    temp = ISVREF(evaluator_description,(SI_Long)0L);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(temp),
	    Qstack_evaluators);
    stack_evaluators_new_value = CONS(push_arg,temp_1);
    mutate_global_property(temp,stack_evaluators_new_value,Qstack_evaluators);
    return VALUES_1(Qnil);
}

/* REGISTER-FUNCALLED-EVALUATOR */
Object register_funcalled_evaluator(evaluator_description,evaluator_number,
	    evaluator_dispatch_type)
    Object evaluator_description, evaluator_number, evaluator_dispatch_type;
{
    Object old_description, temp, temp_1, push_arg, temp_2;

    x_note_fn_call(204,2);
    if (IFIX(evaluator_number) < (SI_Long)0L || FIXNUM_GE(evaluator_number,
	    Maximum_number_of_funcalled_evaluators))
	error((SI_Long)3L,
		"Funcalled evaluator number ~a above maximum for ~a.",
		evaluator_number,ISVREF(evaluator_description,(SI_Long)0L));
    old_description = ISVREF(Funcalled_evaluator_array,IFIX(evaluator_number));
    if (old_description &&  !EQ(ISVREF(old_description,(SI_Long)1L),
	    ISVREF(evaluator_description,(SI_Long)1L)))
	warn((SI_Long)4L,"Funcalled evaluator #~a changing from ~a to ~a.",
		evaluator_number,ISVREF(old_description,(SI_Long)1L),
		ISVREF(evaluator_description,(SI_Long)1L));
    temp = Funcalled_evaluator_functions;
    temp_1 = ISVREF(evaluator_description,(SI_Long)7L);
    SVREF(temp,evaluator_number) = temp_1;
    temp = Funcalled_evaluator_dispatch_type;
    SVREF(temp,evaluator_number) = evaluator_dispatch_type;
    temp = Funcalled_evaluator_array;
    SVREF(temp,evaluator_number) = evaluator_description;
    push_arg = evaluator_description;
    temp = ISVREF(evaluator_description,(SI_Long)0L);
    temp_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(temp),
	    Qstack_evaluators);
    temp_1 = CONS(push_arg,temp_2);
    mutate_global_property(temp,temp_1,Qstack_evaluators);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Dummy_evaluators_list, Qdummy_evaluators_list);

/* REGISTER-DUMMY-EVALUATOR */
Object register_dummy_evaluator(evaluator_description)
    Object evaluator_description;
{
    Object new_evaluator_name, old_description_cons, push_arg;
    Object dummy_evaluators_list_new_value;

    x_note_fn_call(204,3);
    new_evaluator_name = ISVREF(evaluator_description,(SI_Long)0L);
    old_description_cons = Dummy_evaluators_list;
  next_loop:
    if ( !TRUEP(old_description_cons))
	goto end_loop;
    if (EQ(new_evaluator_name,ISVREF(CAR(old_description_cons),(SI_Long)0L))) {
	M_CAR(old_description_cons) = evaluator_description;
	return VALUES_1(Nil);
    }
    old_description_cons = M_CDR(old_description_cons);
    goto next_loop;
  end_loop:
    push_arg = evaluator_description;
    dummy_evaluators_list_new_value = CONS(push_arg,Dummy_evaluators_list);
    Dummy_evaluators_list = dummy_evaluators_list_new_value;
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Funcalled_instructions, Qfuncalled_instructions);

DEFINE_VARIABLE_WITH_SYMBOL(Funcalled_instruction_functions, Qfuncalled_instruction_functions);

Object Funcalled_instruction_description_prop = UNBOUND;

static Object Qfuncalled_instruction_description;  /* funcalled-instruction-description */

/* MAKE-AND-REGISTER-FUNCALLED-INSTRUCTION-DESCRIPTION */
Object make_and_register_funcalled_instruction_description(name,
	    instruction_number,environments,argument_count,result_count,
	    implementation_function,printer_qm,pprinter_qm,function_name)
    Object name, instruction_number, environments, argument_count;
    Object result_count, implementation_function, printer_qm, pprinter_qm;
    Object function_name;
{
    Object description, temp, old_description_qm;
    XDeclare_area(1);

    x_note_fn_call(204,4);
    if (PUSH_AREA(Dynamic_area,0))
	description = make_array(1,FIX((SI_Long)9L));
    POP_AREA(0);
    SVREF(description,FIX((SI_Long)0L)) = name;
    SVREF(description,FIX((SI_Long)1L)) = instruction_number;
    temp = EQ(environments,Qall) ? list_constant : environments;
    SVREF(description,FIX((SI_Long)2L)) = temp;
    SVREF(description,FIX((SI_Long)3L)) = argument_count;
    SVREF(description,FIX((SI_Long)4L)) = result_count;
    SVREF(description,FIX((SI_Long)6L)) = implementation_function;
    SVREF(description,FIX((SI_Long)5L)) = printer_qm;
    SVREF(description,FIX((SI_Long)7L)) = pprinter_qm;
    SVREF(description,FIX((SI_Long)8L)) = function_name;
    old_description_qm = ISVREF(Funcalled_instructions,
	    IFIX(instruction_number));
    if (old_description_qm &&  !EQ(ISVREF(old_description_qm,(SI_Long)0L),
	    name))
	warn((SI_Long)4L,
		"Funcalled-instruction #~a changing from ~a to ~a.",
		instruction_number,ISVREF(old_description_qm,(SI_Long)0L),
		name);
    temp = Funcalled_instructions;
    SVREF(temp,instruction_number) = description;
    temp = Funcalled_instruction_functions;
    SVREF(temp,instruction_number) = implementation_function;
    mutate_global_property(name,description,
	    Qfuncalled_instruction_description);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_stack, Qglobal_stack);

/* MAKE-GLOBAL-STACK */
Object make_global_stack()
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(204,5);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(1,Global_stack_size);
    POP_AREA(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Free_global_stacks, Qfree_global_stacks);

Object Stack_eval_locals_bindings = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Float_contagion_stack_operators, Qfloat_contagion_stack_operators);

/* FLOAT-CONTAGION-STACK-OPERATOR-P */
Object float_contagion_stack_operator_p(stack_operator)
    Object stack_operator;
{
    x_note_fn_call(204,6);
    return memq_function(stack_operator,Float_contagion_stack_operators);
}

/* LONG-CODE-CONSTANT-IN-BYTE-VECTOR */
Object long_code_constant_in_byte_vector(byte_vector,index_init)
    Object byte_vector, index_init;
{
    Object temp;
    SI_Long index_1;

    x_note_fn_call(204,7);
    index_1 = IFIX(index_init);
    temp = FIX((UBYTE_8_ISAREF_1(byte_vector,index_1) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(byte_vector,index_1 + (SI_Long)1L));
    return VALUES_1(temp);
}

/* SETF-LONG-CODE-CONSTANT */
Object setf_long_code_constant(byte_vector,index_1,long_code_constant)
    Object byte_vector, index_1, long_code_constant;
{
    Object aref_arg_2;
    SI_Long aref_new_value, gensymed_symbol;

    x_note_fn_call(204,8);
    aref_new_value = IFIX(long_code_constant) >>  -  - (SI_Long)8L;
    UBYTE_8_ISASET_1(byte_vector,IFIX(index_1),aref_new_value);
    aref_arg_2 = FIXNUM_ADD1(index_1);
    gensymed_symbol = IFIX(long_code_constant) & (SI_Long)255L;
    UBYTE_8_ISASET_1(byte_vector,IFIX(aref_arg_2),gensymed_symbol);
    return VALUES_1(long_code_constant);
}

/* EMIT-LONG-CODE-CONSTANT-TO-STREAM */
Object emit_long_code_constant_to_stream(byte_code_stream,constant)
    Object byte_code_stream, constant;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(204,9);
    write_byte_code_to_stream(byte_code_stream,FIX(IFIX(constant) >>  -  - 
	    (SI_Long)8L));
    gensymed_symbol = IFIX(constant) & (SI_Long)255L;
    write_byte_code_to_stream(byte_code_stream,FIX(gensymed_symbol));
    return VALUES_1(Nil);
}

/* RELATIVE-CODE-CONSTANT-IN-BYTE-VECTOR */
Object relative_code_constant_in_byte_vector(byte_vector,index_init)
    Object byte_vector, index_init;
{
    Object temp;
    SI_Long index_1;

    x_note_fn_call(204,10);
    index_1 = IFIX(index_init);
    temp = FIX(UBYTE_8_ISAREF_1(byte_vector,index_1) - (SI_Long)128L);
    return VALUES_1(temp);
}

/* SETF-RELATIVE-CODE-CONSTANT-IN-BYTE-VECTOR */
Object setf_relative_code_constant_in_byte_vector(byte_vector,index_1,constant)
    Object byte_vector, index_1, constant;
{
    SI_Long aref_new_value;

    x_note_fn_call(204,11);
    aref_new_value = IFIX(constant) + (SI_Long)128L;
    UBYTE_8_ISASET_1(byte_vector,IFIX(index_1),aref_new_value);
    return VALUES_1(constant);
}

/* RELATIVE-CODE-CONSTANT-P */
Object relative_code_constant_p(fixnum)
    Object fixnum;
{
    x_note_fn_call(204,12);
    return VALUES_1(IFIX(fixnum) >= (SI_Long)-128L ? (IFIX(fixnum) <= 
	    (SI_Long)127L ? T : Nil) : Qnil);
}

/* EMIT-RELATIVE-CODE-CONSTANT-TO-STREAM */
Object emit_relative_code_constant_to_stream(byte_code_stream,constant)
    Object byte_code_stream, constant;
{
    x_note_fn_call(204,13);
    return write_byte_code_to_stream(byte_code_stream,FIX(IFIX(constant) + 
	    (SI_Long)128L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Stack_instructions, Qstack_instructions);

Object Instruction_description_prop = UNBOUND;

static Object Qstack_instruction;  /* stack-instruction */

static Object Qinstruction_description;  /* instruction-description */

/* MAKE-AND-REGISTER-STACK-INSTRUCTION-DESCRIPTION */
Object make_and_register_stack_instruction_description(name,
	    length_in_bytes,argument_count_qm,printer_qm,
	    instruction_number,macro_name,pprinter_qm)
    Object name, length_in_bytes, argument_count_qm, printer_qm;
    Object instruction_number, macro_name, pprinter_qm;
{
    Object description, old_description, svref_arg_1;
    XDeclare_area(1);

    x_note_fn_call(204,14);
    if (PUSH_AREA(Dynamic_area,0))
	description = make_array(1,FIX((SI_Long)9L));
    POP_AREA(0);
    SVREF(description,FIX((SI_Long)0L)) = Qstack_instruction;
    SVREF(description,FIX((SI_Long)1L)) = name;
    SVREF(description,FIX((SI_Long)2L)) = length_in_bytes;
    SVREF(description,FIX((SI_Long)3L)) = argument_count_qm;
    SVREF(description,FIX((SI_Long)4L)) = printer_qm;
    SVREF(description,FIX((SI_Long)5L)) = instruction_number;
    SVREF(description,FIX((SI_Long)6L)) = macro_name;
    SVREF(description,FIX((SI_Long)7L)) = pprinter_qm;
    old_description = ISVREF(Stack_instructions,IFIX(instruction_number));
    if (old_description &&  !EQ(ISVREF(old_description,(SI_Long)1L),name))
	warn((SI_Long)4L,"Stack instruction #~a changing from ~a to ~a.",
		instruction_number,ISVREF(old_description,(SI_Long)1L),name);
    svref_arg_1 = Stack_instructions;
    SVREF(svref_arg_1,instruction_number) = description;
    mutate_global_property(name,description,Qinstruction_description);
    return VALUES_1(Nil);
}

/* STACK-INSTRUCTION-DESCRIPTION-P */
Object stack_instruction_description_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(204,15);
    temp = SIMPLE_VECTOR_P(thing) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)0L ? 
	    (EQ(ISVREF(thing,(SI_Long)0L),Qstack_instruction) ? T : Nil) : 
	    Qnil;
    return VALUES_1(temp);
}

/* ADD-TEXT-TO-STRING-WITH-ALIGN */
Object add_text_to_string_with_align(main_string,string_to_append,
	    gap_length,reclaim_main_qm,reclaim_appendee_qm)
    Object main_string, string_to_append, gap_length, reclaim_main_qm;
    Object reclaim_appendee_qm;
{
    Object pad_line, composed_line_1, composed_line;

    x_note_fn_call(204,16);
    pad_line = make_stringw_function(gap_length,FIX((SI_Long)32L));
    composed_line_1 = concatenate_text_strings(main_string,pad_line);
    composed_line = concatenate_text_strings(composed_line_1,string_to_append);
    if (reclaim_main_qm)
	reclaim_wide_string(main_string);
    if (reclaim_appendee_qm)
	reclaim_wide_string(string_to_append);
    reclaim_wide_string(pad_line);
    reclaim_wide_string(composed_line_1);
    return VALUES_1(composed_line);
}

static Object string_constant;     /* "Not enough arguments passed to ~a.  It needed ~a and received ~a.  ~?
				    *          Please report this stack evaluator internal error to Gensym software ~?
				    *          support with the source code of the item named in the error message."
				    */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* "Wrong argument type given to ~a.  It needed ~NT and received " */

static Object string_constant_2;   /* ".  Please report this stack evaluator internal error to Gensym ~?
				    *              software support with the source code of the item named in the ~?
				    *              error message."
				    */

/* CHECK-STACK-EVALUATOR-ARGUMENTS */
Object check_stack_evaluator_arguments(evaluator_number_or_op_code,
	    in_line_qm,local_stack,top_of_stack)
    Object evaluator_number_or_op_code, in_line_qm, local_stack, top_of_stack;
{
    Object evaluator_description, argument_types, argument_count;
    Object incremented_top_of_stack, top_of_stack_1, message_1, argument_type;
    Object ab_loop_list_, argument, ab_loop_iter_flag_, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long stack_index, bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(204,17);
    evaluator_description = in_line_qm ? ISVREF(In_line_evaluator_array,
	    IFIX(FIXNUM_MINUS(evaluator_number_or_op_code,
	    Base_in_line_evaluator_number))) : 
	    ISVREF(Funcalled_evaluator_array,
	    IFIX(evaluator_number_or_op_code));
    argument_types = ISVREF(evaluator_description,(SI_Long)4L);
    argument_count = length(argument_types);
    incremented_top_of_stack = FIXNUM_ADD1(top_of_stack);
    if (FIXNUM_LT(incremented_top_of_stack,argument_count)) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant,
		ISVREF(evaluator_description,(SI_Long)1L),argument_count,
		incremented_top_of_stack);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    argument_type = Nil;
    ab_loop_list_ = argument_types;
    stack_index = IFIX(FIXNUM_MINUS(incremented_top_of_stack,argument_count));
    argument = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	stack_index = stack_index + (SI_Long)1L;
    argument = ISVREF(local_stack,stack_index);
    if ( !TRUEP(type_specification_type_p(argument,argument_type))) {
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
		      tformat(3,string_constant_1,
			      ISVREF(evaluator_description,(SI_Long)1L),
			      argument_type);
		      write_stored_value(argument);
		      tformat(1,string_constant_2);
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
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_3;   /* "Wrong result type returned from ~a.  It should return ~NT, but ~?
				    *            instead returned "
				    */

static Object string_constant_4;   /* ".  Please report this evaluator internal error to Gensym software ~?
				    *            support with the source code of the item named in the error message."
				    */

/* CHECK-STACK-EVALUATOR-RESULT */
Object check_stack_evaluator_result(evaluator_number_or_op_code,in_line_qm,
	    return_value,top_of_stack)
    Object evaluator_number_or_op_code, in_line_qm, return_value, top_of_stack;
{
    Object evaluator_description, value_type, top_of_stack_1, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(204,18);
    evaluator_description = in_line_qm ? ISVREF(In_line_evaluator_array,
	    IFIX(FIXNUM_MINUS(evaluator_number_or_op_code,
	    Base_in_line_evaluator_number))) : 
	    ISVREF(Funcalled_evaluator_array,
	    IFIX(evaluator_number_or_op_code));
    value_type = ISVREF(evaluator_description,(SI_Long)5L);
    if ( !TRUEP(type_specification_type_p(return_value,value_type))) {
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
		      tformat(3,string_constant_3,
			      ISVREF(evaluator_description,(SI_Long)0L),
			      value_type);
		      write_stored_value(return_value);
		      tformat(1,string_constant_4);
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
    else
	return VALUES_1(Nil);
}

static Object string_constant_5;   /* "op-code fetcher" */

static Object string_constant_6;   /* "No stack instruction description for ~a." */

/* OP-CODE-FOR-STACK-INSTRUCTION */
Object op_code_for_stack_instruction(name)
    Object name;
{
    Object description, temp;

    x_note_fn_call(204,19);
    description = getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qinstruction_description);
    if (description)
	temp = ISVREF(description,(SI_Long)5L);
    else {
	compiler_bug(3,string_constant_5,string_constant_6,name);
	temp = FIX((SI_Long)0L);
    }
    return VALUES_1(temp);
}

/* INSTRUCTION-DESCRIPTION-FOR-OP-CODE */
Object instruction_description_for_op_code(op_code_init)
    Object op_code_init;
{
    Object temp;
    SI_Long op_code;

    x_note_fn_call(204,20);
    op_code = IFIX(op_code_init);
    temp = ISVREF(Stack_instructions,op_code);
    return VALUES_1(temp);
}

Object Byte_code_resolver_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_code_body_entry, Qcurrent_code_body_entry);

/* ENTRY-POINT-NUMBER */
Object entry_point_number(address,compiler_code_body)
    Object address, compiler_code_body;
{
    Object entry_points, temp, svref_new_value;

    x_note_fn_call(204,21);
    entry_points = ISVREF(compiler_code_body,(SI_Long)5L);
    temp = position(2,address,entry_points);
    if (temp)
	return VALUES_1(temp);
    else if (entry_points) {
	temp = last(entry_points,_);
	RPLACD(temp,phrase_cons(address,Nil));
	return VALUES_1(FIXNUM_SUB1(length(entry_points)));
    }
    else {
	svref_new_value = phrase_cons(address,Nil);
	SVREF(compiler_code_body,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX((SI_Long)0L));
    }
}

static Object Qbyte_code_resolver;  /* byte-code-resolver */

static Object string_constant_7;   /* "address resolver" */

static Object string_constant_8;   /* "No address resolver for stack instruction op-code ~a." */

/* RESOLVE-PROCEDURE-BYTE-CODE-ADDRESSES */
Object resolve_procedure_byte_code_addresses varargs_1(int, n)
{
    Object byte_code_stream;
    Object code_body_entry_qm, current_code_body_entry, byte_vector, address;
    Object tag_or_tag_list, ab_loop_list_, op_code, instruction_description_qm;
    Object instruction_name_qm, resolver_qm, ab_loop_desetq_;
    Object error_handler_spec_qm, temp, first_new_value;
    SI_Long byte_vector_length;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(204,22);
    INIT_ARGS_nonrelocating();
    byte_code_stream = REQUIRED_ARG_nonrelocating();
    code_body_entry_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_code_body_entry = code_body_entry_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_code_body_entry,Qcurrent_code_body_entry,current_code_body_entry,
	    0);
      byte_vector = read_byte_code_stream_vector(byte_code_stream);
      byte_vector_length = IFIX(ISVREF(byte_code_stream,(SI_Long)1L));
      address = Nil;
      tag_or_tag_list = Nil;
      ab_loop_list_ = ISVREF(byte_code_stream,(SI_Long)3L);
      op_code = Nil;
      instruction_description_qm = Nil;
      instruction_name_qm = Nil;
      resolver_qm = Nil;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      address = CAR(ab_loop_desetq_);
      tag_or_tag_list = CDR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      op_code = FIX(UBYTE_8_ISAREF_1(byte_vector,IFIX(address)));
      instruction_description_qm = 
	      instruction_description_for_op_code(op_code);
      instruction_name_qm = instruction_description_qm ? 
	      ISVREF(instruction_description_qm,(SI_Long)1L) : Nil;
      resolver_qm = instruction_name_qm ? 
	      getfq_function_no_default(INLINE_SYMBOL_PLIST(instruction_name_qm),
	      Qbyte_code_resolver) : Nil;
      if (resolver_qm)
	  inline_funcall_4(resolver_qm,byte_code_stream,byte_vector,
		  address,tag_or_tag_list);
      else
	  compiler_bug(3,string_constant_7,string_constant_8,op_code);
      goto next_loop;
    end_loop:
      if (code_body_entry_qm) {
	  error_handler_spec_qm = ISVREF(code_body_entry_qm,(SI_Long)7L);
	  if (error_handler_spec_qm) {
	      temp = 
		      instruction_address_for_tag(FIRST(error_handler_spec_qm),
		      T);
	      first_new_value = entry_point_number(temp,
		      nth(ISVREF(code_body_entry_qm,(SI_Long)4L),
		      Code_body_entries_in_compilation));
	      M_FIRST(error_handler_spec_qm) = first_new_value;
	  }
      }
      result = VALUES_2(byte_vector,FIX(byte_vector_length));
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* ACTIVITY-AND-TEXT-POSITION-INFORMATION */
Object activity_and_text_position_information(byte_code_stream)
    Object byte_code_stream;
{
    Object activity_info_qm, text_position_info_qm;

    x_note_fn_call(204,23);
    activity_info_qm = ISVREF(byte_code_stream,(SI_Long)7L);
    text_position_info_qm = ISVREF(byte_code_stream,(SI_Long)8L);
    SVREF(byte_code_stream,FIX((SI_Long)7L)) = Nil;
    SVREF(byte_code_stream,FIX((SI_Long)8L)) = Nil;
    return VALUES_2(activity_info_qm,text_position_info_qm);
}

static Object string_constant_9;   /* "Environment~%" */

static Object string_constant_10;  /* "~%Constants" */

static Object string_constant_11;  /* "~%" */

static Object array_constant;      /* # */

static Object string_constant_12;  /* "~%  Inherited from base code body" */

static Object string_constant_13;  /* "~%  None" */

static Object string_constant_14;  /* "~%Free References" */

static Object string_constant_15;  /* "~%Instructions" */

/* WRITE-BYTE-CODE-BODY */
Object write_byte_code_body(byte_code_body,constant_vector)
    Object byte_code_body, constant_vector;
{
    Object bytes, environment_description, value, incff_1_arg;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(204,24);
    bytes = ISVREF(byte_code_body,(SI_Long)1L);
    environment_description = ISVREF(byte_code_body,(SI_Long)4L);
    tformat(1,string_constant_9);
    write_code_body_environment(environment_description,Nil);
    tformat(1,string_constant_10);
    if (constant_vector) {
	if (EQ(constant_vector,ISVREF(byte_code_body,(SI_Long)3L))) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length(constant_vector));
	    value = Nil;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    value = ISVREF(constant_vector,index_1);
	    tformat(1,string_constant_11);
	    twrite_right_justified_unsigned_short(FIX(index_1),
		    FIX((SI_Long)4L));
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)3L));
	    write_stored_value(value);
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else
	    tformat(1,string_constant_12);
    }
    else
	tformat(1,string_constant_13);
    tformat(1,string_constant_14);
    write_byte_code_body_free_references(byte_code_body);
    tformat(1,string_constant_15);
    index_1 = (SI_Long)0L;
  next_loop_1:
    if ( !(index_1 < IFIX(bytes)))
	goto end_loop_1;
    tformat(1,string_constant_11);
    incff_1_arg = write_stack_instruction(FIX(index_1),byte_code_body,
	    constant_vector);
    index_1 = index_1 + IFIX(incff_1_arg);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qsystem_call;        /* system-call */

static Object Qnupec_synchronize;  /* nupec-synchronize */

static Object Qhalt;               /* halt */

static Object Qadd_to_action_cache;  /* add-to-action-cache */

static Object Qrestore_from_action_cache_or_branch;  /* restore-from-action-cache-or-branch */

static Object Qreset_kb;           /* reset-kb */

/* INSTRUCTION-SHOULD-NOT-BE-COMPILED */
Object instruction_should_not_be_compiled(op_code)
    Object op_code;
{
    Object description, name, temp;

    x_note_fn_call(204,25);
    if ( !(FIXNUM_GE(op_code,Base_in_line_evaluator_number) && 
	    FIXNUM_LT(op_code,FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators)))) {
	description = instruction_description_for_op_code(op_code);
	name = description ? ISVREF(description,(SI_Long)1L) : Qnil;
	temp =  !TRUEP(description) ? T : Nil;
	if (temp);
	else
	    temp = EQ(Qsystem_call,name) ? T : Nil;
	if (temp);
	else
	    temp = EQ(Qnupec_synchronize,name) ? T : Nil;
	if (temp);
	else
	    temp = EQ(Qhalt,name) ? T : Nil;
	if (temp);
	else
	    temp = EQ(Qadd_to_action_cache,name) ? T : Nil;
	if (temp);
	else
	    temp = EQ(Qrestore_from_action_cache_or_branch,name) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(EQ(Qreset_kb,name) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Maximum_byte_code_body_length_to_compile = UNBOUND;

/* BYTE-CODE-BODY-IS-TOO-LONG-TO-COMPILE-P */
Object byte_code_body_is_too_long_to_compile_p(byte_code_body)
    Object byte_code_body;
{
    x_note_fn_call(204,26);
    return VALUES_1(FIXNUM_LT(Maximum_byte_code_body_length_to_compile,
	    ISVREF(byte_code_body,(SI_Long)1L)) ? T : Nil);
}

/* BYTE-CODE-BODY-CONTAINS-INSTRUCTION-THAT-SHOULD-NOT-BE-COMPILED-P */
Object byte_code_body_contains_instruction_that_should_not_be_compiled_p(byte_code_body,
	    constant_vector)
    Object byte_code_body, constant_vector;
{
    Object total_bytes, instruction_vector, op_code, incff_1_arg, description;
    Object byte_length_or_function_qm, byte_length_qm;
    SI_Long program_counter;

    x_note_fn_call(204,27);
    total_bytes = ISVREF(byte_code_body,(SI_Long)1L);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    program_counter = (SI_Long)0L;
    op_code = Nil;
  next_loop:
    if ( !(program_counter < IFIX(total_bytes)))
	goto end_loop;
    op_code = FIX(UBYTE_8_ISAREF_1(instruction_vector,program_counter));
    if (FIXNUM_GE(op_code,Base_in_line_evaluator_number) && 
	    FIXNUM_LT(op_code,FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators)))
	incff_1_arg = FIX((SI_Long)1L);
    else {
	description = instruction_description_for_op_code(op_code);
	byte_length_or_function_qm = description ? ISVREF(description,
		(SI_Long)2L) : Qnil;
	if (FIXNUMP(byte_length_or_function_qm))
	    byte_length_qm = byte_length_or_function_qm;
	else if (COMPILED_FUNCTION_P(byte_length_or_function_qm))
	    byte_length_qm = FUNCALL_3(byte_length_or_function_qm,
		    FIX(program_counter),instruction_vector,constant_vector);
	else
	    byte_length_qm = FIX((SI_Long)1L);
	if (instruction_should_not_be_compiled(op_code))
	    return VALUES_1(T);
	incff_1_arg = byte_length_qm;
    }
    program_counter = program_counter + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qbranch;             /* branch */

static Object Qbranch_if_not_true;  /* branch-if-not-true */

static Object Qbranch_if_known;    /* branch-if-known */

static Object Qbranch_long;        /* branch-long */

static Object Qbranch_long_if_not_true;  /* branch-long-if-not-true */

static Object Qbranch_long_if_known;  /* branch-long-if-known */

static Object Qboolean_branch_long_if_not_true;  /* boolean-branch-long-if-not-true */

static Object Qbranch_relative;    /* branch-relative */

static Object Qbranch_relative_if_not_true;  /* branch-relative-if-not-true */

static Object Qbranch_relative_if_known;  /* branch-relative-if-known */

static Object Qboolean_branch_relative_if_not_true;  /* boolean-branch-relative-if-not-true */

static Object list_constant_1;     /* # */

/* BYTE-CODE-BODY-CONTAINS-BACKWARD-BRANCH-P */
Object byte_code_body_contains_backward_branch_p(byte_code_body,
	    constant_vector)
    Object byte_code_body, constant_vector;
{
    Object total_bytes, instruction_vector, op_code, incff_1_arg, description;
    Object byte_length_or_function_qm, byte_length_qm, temp;
    Object lowest_address_from_instruction_qm;
    SI_Long program_counter, stack_program_counter;

    x_note_fn_call(204,28);
    total_bytes = ISVREF(byte_code_body,(SI_Long)1L);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    program_counter = (SI_Long)0L;
    op_code = Nil;
  next_loop:
    if ( !(program_counter < IFIX(total_bytes)))
	goto end_loop;
    op_code = FIX(UBYTE_8_ISAREF_1(instruction_vector,program_counter));
    if (FIXNUM_GE(op_code,Base_in_line_evaluator_number) && 
	    FIXNUM_LT(op_code,FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators)))
	incff_1_arg = FIX((SI_Long)1L);
    else {
	description = instruction_description_for_op_code(op_code);
	if (description);
	else
	    return VALUES_1(Nil);
	byte_length_or_function_qm = ISVREF(description,(SI_Long)2L);
	if (FIXNUMP(byte_length_or_function_qm))
	    byte_length_qm = byte_length_or_function_qm;
	else if (COMPILED_FUNCTION_P(byte_length_or_function_qm))
	    byte_length_qm = FUNCALL_3(byte_length_or_function_qm,
		    FIX(program_counter),instruction_vector,constant_vector);
	else
	    byte_length_qm = FIX((SI_Long)1L);
	temp = ISVREF(description,(SI_Long)1L);
	if (EQ(temp,Qbranch) || EQ(temp,Qbranch_if_not_true) || EQ(temp,
		Qbranch_if_known)) {
	    stack_program_counter = program_counter + (SI_Long)1L;
	    lowest_address_from_instruction_qm = 
		    FIX(UBYTE_8_ISAREF_1(instruction_vector,
		    stack_program_counter));
	}
	else if (EQ(temp,Qbranch_long) || EQ(temp,
		Qbranch_long_if_not_true) || EQ(temp,
		Qbranch_long_if_known) || EQ(temp,
		Qboolean_branch_long_if_not_true)) {
	    stack_program_counter = program_counter + (SI_Long)1L;
	    lowest_address_from_instruction_qm = 
		    FIX((UBYTE_8_ISAREF_1(instruction_vector,
		    stack_program_counter) << (SI_Long)8L) + 
		    UBYTE_8_ISAREF_1(instruction_vector,
		    stack_program_counter + (SI_Long)1L));
	}
	else if (EQ(temp,Qbranch_relative) || EQ(temp,
		Qbranch_relative_if_not_true) || EQ(temp,
		Qbranch_relative_if_known) || EQ(temp,
		Qboolean_branch_relative_if_not_true)) {
	    stack_program_counter = program_counter + (SI_Long)1L;
	    lowest_address_from_instruction_qm = FIX(program_counter + 
		    (UBYTE_8_ISAREF_1(instruction_vector,
		    stack_program_counter) - (SI_Long)128L));
	}
	else if (member_eql(temp,list_constant_1))
	    lowest_address_from_instruction_qm = Nil;
	else
	    lowest_address_from_instruction_qm = Nil;
	if (lowest_address_from_instruction_qm && 
		IFIX(lowest_address_from_instruction_qm) < program_counter)
	    return VALUES_1(T);
	incff_1_arg = byte_length_qm;
    }
    program_counter = program_counter + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Show_stack_bytes_qm, Qshow_stack_bytes_qm);

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* WRITE-STACK-INSTRUCTION */
Object write_stack_instruction(op_code_address,byte_code_body,constants)
    Object op_code_address, byte_code_body, constants;
{
    Object raw_byte_vector, environment_description, bytes, description_qm;
    Object printer_function_qm, byte_length_or_function_qm, byte_length_qm;
    SI_Long op_code, index_1, ab_loop_repeat_;

    x_note_fn_call(204,29);
    raw_byte_vector = ISVREF(byte_code_body,(SI_Long)2L);
    environment_description = ISVREF(byte_code_body,(SI_Long)4L);
    op_code = UBYTE_8_ISAREF_1(raw_byte_vector,IFIX(op_code_address));
    bytes = Nil;
    twrite_right_justified_unsigned_short(op_code_address,FIX((SI_Long)5L));
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)3L));
    if (op_code >= IFIX(Base_in_line_evaluator_number) && op_code < 
	    IFIX(FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators))) {
	description_qm = ISVREF(In_line_evaluator_array,op_code - 
		IFIX(Base_in_line_evaluator_number));
	if (description_qm)
	    twrite_symbol(1,ISVREF(description_qm,(SI_Long)1L));
	else {
	    twrite_beginning_of_wide_string(array_constant_1,
		    FIX((SI_Long)45L));
	    twrite_positive_fixnum(FIX(op_code));
	}
	bytes = FIX((SI_Long)1L);
    }
    else {
	description_qm = instruction_description_for_op_code(FIX(op_code));
	printer_function_qm = description_qm ? ISVREF(description_qm,
		(SI_Long)4L) : Nil;
	byte_length_or_function_qm = description_qm ? 
		ISVREF(description_qm,(SI_Long)2L) : Nil;
	if (FIXNUMP(byte_length_or_function_qm))
	    byte_length_qm = byte_length_or_function_qm;
	else if (COMPILED_FUNCTION_P(byte_length_or_function_qm))
	    byte_length_qm = FUNCALL_3(byte_length_or_function_qm,
		    op_code_address,raw_byte_vector,constants);
	else
	    byte_length_qm = Nil;
	if (printer_function_qm) {
	    twrite_symbol(1,ISVREF(description_qm,(SI_Long)1L));
	    inline_funcall_4(printer_function_qm,op_code_address,
		    raw_byte_vector,constants,environment_description);
	    bytes = byte_length_qm;
	}
	else if (description_qm) {
	    twrite_symbol(1,ISVREF(description_qm,(SI_Long)1L));
	    bytes = byte_length_qm;
	}
	else {
	    twrite_beginning_of_wide_string(array_constant_2,
		    FIX((SI_Long)32L));
	    twrite_positive_fixnum(FIX(op_code));
	    bytes = FIX((SI_Long)1L);
	}
    }
    if (Show_stack_bytes_qm) {
	index_1 = IFIX(op_code_address);
	ab_loop_repeat_ = IFIX(bytes);
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)10L));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !(index_1 == IFIX(op_code_address)))
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)2L));
	twrite_positive_fixnum(FIX(UBYTE_8_ISAREF_1(raw_byte_vector,index_1)));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	twrite_character(FIX((SI_Long)62L));
    }
    return VALUES_1(bytes);
}

static Object string_constant_16;  /* "" */

static Object string_constant_17;  /* "    " */

static Object string_constant_18;  /* "   " */

static Object string_constant_19;  /* "  " */

static Object string_constant_20;  /* " " */

/* TWRITE-RIGHT-JUSTIFIED-UNSIGNED-SHORT */
Object twrite_right_justified_unsigned_short(unsigned_short,field_width)
    Object unsigned_short, field_width;
{
    Object integer_width, temp;

    x_note_fn_call(204,30);
    if (IFIX(unsigned_short) < (SI_Long)10L)
	integer_width = FIX((SI_Long)1L);
    else if (IFIX(unsigned_short) < (SI_Long)100L)
	integer_width = FIX((SI_Long)2L);
    else if (IFIX(unsigned_short) < (SI_Long)1000L)
	integer_width = FIX((SI_Long)3L);
    else if (IFIX(unsigned_short) < (SI_Long)10000L)
	integer_width = FIX((SI_Long)4L);
    else
	integer_width = FIX((SI_Long)5L);
    if (FIXNUM_GT(field_width,integer_width)) {
	temp = FIXNUM_MINUS(field_width,integer_width);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = string_constant_16;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 4:
		temp = string_constant_17;
		break;
	      case 3:
		temp = string_constant_18;
		break;
	      case 2:
		temp = string_constant_19;
		break;
	      case 1:
		temp = string_constant_20;
		break;
	      default:
		temp = string_constant_16;
		break;
	    }
	twrite_general_string(temp);
    }
    twrite_positive_fixnum(unsigned_short);
    return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* PPRINT-STACK-INSTRUCTION */
Object pprint_stack_instruction(op_code_address,byte_code_body,constants,
	    stack,top_of_stack)
    Object op_code_address, byte_code_body, constants, stack, top_of_stack;
{
    Object raw_byte_vector, bytes, description_qm, arg_count, pprinter_qm;
    Object pprinter_function_qm, byte_length_or_function_qm, byte_length_qm;
    SI_Long op_code, index_1, ab_loop_repeat_;

    x_note_fn_call(204,31);
    raw_byte_vector = ISVREF(byte_code_body,(SI_Long)2L);
    op_code = UBYTE_8_ISAREF_1(raw_byte_vector,IFIX(op_code_address));
    bytes = Nil;
    if (op_code >= IFIX(Base_in_line_evaluator_number) && op_code < 
	    IFIX(FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators))) {
	description_qm = ISVREF(In_line_evaluator_array,op_code - 
		IFIX(Base_in_line_evaluator_number));
	arg_count = description_qm ? length(ISVREF(description_qm,
		(SI_Long)4L)) : Nil;
	pprinter_qm = description_qm ? ISVREF(description_qm,(SI_Long)11L) 
		: Nil;
	if ( !TRUEP(description_qm)) {
	    twrite_beginning_of_wide_string(array_constant_5,
		    FIX((SI_Long)36L));
	    twrite_positive_fixnum(FIX(op_code));
	}
	else if (pprinter_qm)
	    inline_funcall_6(pprinter_qm,description_qm,op_code_address,
		    byte_code_body,constants,stack,top_of_stack);
	else if (IFIX(arg_count) == (SI_Long)2L)
	    pprint_infix_evaluator(description_qm,op_code_address,
		    byte_code_body,constants,stack,top_of_stack);
	else
	    pprint_functional_evaluator(description_qm,op_code_address,
		    byte_code_body,constants,stack,top_of_stack);
	bytes = FIX((SI_Long)1L);
    }
    else {
	description_qm = instruction_description_for_op_code(FIX(op_code));
	pprinter_function_qm = description_qm ? ISVREF(description_qm,
		(SI_Long)7L) : Nil;
	byte_length_or_function_qm = description_qm ? 
		ISVREF(description_qm,(SI_Long)2L) : Nil;
	if (FIXNUMP(byte_length_or_function_qm))
	    byte_length_qm = byte_length_or_function_qm;
	else if (COMPILED_FUNCTION_P(byte_length_or_function_qm))
	    byte_length_qm = inline_funcall_3(byte_length_or_function_qm,
		    op_code_address,raw_byte_vector,constants);
	else
	    byte_length_qm = FIX((SI_Long)1L);
	if (pprinter_function_qm) {
	    inline_funcall_5(pprinter_function_qm,op_code_address,
		    byte_code_body,constants,stack,top_of_stack);
	    bytes = byte_length_qm;
	}
	else {
	    twrite_beginning_of_wide_string(array_constant_6,
		    FIX((SI_Long)17L));
	    twrite_positive_fixnum(FIX(op_code));
	    bytes = byte_length_qm;
	}
    }
    if (Show_stack_bytes_qm) {
	index_1 = IFIX(op_code_address);
	ab_loop_repeat_ = IFIX(bytes);
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)10L));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !(index_1 == IFIX(op_code_address)))
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)2L));
	twrite_positive_fixnum(FIX(UBYTE_8_ISAREF_1(raw_byte_vector,index_1)));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	twrite_character(FIX((SI_Long)62L));
    }
    return VALUES_1(bytes);
}

static Object Qfuncall_instruction;  /* funcall-instruction */

/* PPRINTER-FOR-STACK-INSTRUCTION-P */
Object pprinter_for_stack_instruction_p(op_code_address_init,byte_code_body)
    Object op_code_address_init, byte_code_body;
{
    Object raw_byte_vector, temp, description_qm;
    SI_Long op_code_address, op_code;

    x_note_fn_call(204,32);
    op_code_address = IFIX(op_code_address_init);
    raw_byte_vector = ISVREF(byte_code_body,(SI_Long)2L);
    op_code = UBYTE_8_ISAREF_1(raw_byte_vector,op_code_address);
    temp = op_code >= IFIX(Base_in_line_evaluator_number) ? (op_code < 
	    IFIX(FIXNUM_ADD(Base_in_line_evaluator_number,
	    Maximum_number_of_in_line_evaluators)) ? T : Nil) : Qnil;
    if (temp);
    else {
	description_qm = instruction_description_for_op_code(FIX(op_code));
	temp = description_qm ? (EQ(ISVREF(description_qm,(SI_Long)1L),
		Qfuncall_instruction) ? 
		pprinter_for_funcalled_instruction_p(FIX(UBYTE_8_ISAREF_1(raw_byte_vector,
		op_code_address + (SI_Long)1L))) : ISVREF(description_qm,
		(SI_Long)7L)) : Nil;
    }
    return VALUES_1(temp);
}

/* PPRINTER-FOR-FUNCALLED-INSTRUCTION-P */
Object pprinter_for_funcalled_instruction_p(funcalled_instruction_number_init)
    Object funcalled_instruction_number_init;
{
    Object funcalled_instruction_description_qm, temp;
    SI_Long funcalled_instruction_number;

    x_note_fn_call(204,33);
    funcalled_instruction_number = IFIX(funcalled_instruction_number_init);
    funcalled_instruction_description_qm = ISVREF(Funcalled_instructions,
	    funcalled_instruction_number);
    temp = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)7L) : Qnil;
    return VALUES_1(temp);
}

static Object array_constant_7;    /* # */

/* WRITE-STACK-ARGUMENT */
Object write_stack_argument(index_1,arg_count,stack,top_of_stack)
    Object index_1, arg_count, stack, top_of_stack;
{
    Object arg_index;

    x_note_fn_call(204,34);
    arg_index = FIXNUM_MINUS(top_of_stack,FIXNUM_MINUS(arg_count,index_1));
    if (FIXNUM_EQ(top_of_stack,Cached_top_of_stack) &&  
	    !FIXNUM_MINUSP(arg_index))
	return write_stored_value(ISVREF(stack,IFIX(arg_index)));
    else
	return twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)22L));
}

static Object array_constant_8;    /* # */

/* WRITE-CALLED-FUNCTION-AND-ARGUMENTS */
Object write_called_function_and_arguments varargs_1(int, n)
{
    Object stack, base;
    Object nargs, function, temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long argument_count, first_argument_index, thing, argument_index;
    SI_Long ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(204,35);
    INIT_ARGS_nonrelocating();
    stack = REQUIRED_ARG_nonrelocating();
    base = REQUIRED_ARG_nonrelocating();
    nargs = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    function = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = function;
    if (temp);
    else
	temp = ISVREF(stack,IFIX(base) - (SI_Long)7L);
    function = temp;
    temp = nargs;
    if (temp);
    else
	temp = ISVREF(stack,IFIX(base) - (SI_Long)8L);
    argument_count = IFIX(temp);
    first_argument_index = IFIX(base) - argument_count - (SI_Long)10L;
    denote_component_of_block(3,T,Nil,function);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)40L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)40L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    argument_index = first_argument_index;
    ab_loop_bind_ = first_argument_index + argument_count;
  next_loop:
    if (argument_index >= ab_loop_bind_)
	goto end_loop;
    if ( !(argument_index == first_argument_index))
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)2L));
    write_stored_value(ISVREF(stack,argument_index));
    argument_index = argument_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)1L));
}

static Object array_constant_9;    /* # */

static Object string_constant_21;  /* "Error:  (~a)" */

static Object string_constant_22;  /* "~%~%~nw~%~%" */

/* GENERATE-STANDARD-ERROR-MESSAGE */
Object generate_standard_error_message(error_1,error_text_string,
	    computation_frame,computation_component_particulars,
	    computation_instance,byte_code_body_qm,constant_vector_qm,
	    current_program_counter_qm,local_stack_qm,top_of_stack_qm,
	    local_var_vector_qm)
    Object error_1, error_text_string, computation_frame;
    Object computation_component_particulars, computation_instance;
    Object byte_code_body_qm, constant_vector_qm, current_program_counter_qm;
    Object local_stack_qm, top_of_stack_qm, local_var_vector_qm;
{
    Object error_name, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(204,36);
    error_name = SYMBOLP(error_1) ? error_1 : ISVREF(ISVREF(error_1,
	    (SI_Long)1L),(SI_Long)1L);
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
		  if (EQ(error_name,Qerror))
		      twrite_beginning_of_wide_string(array_constant_9,
			      FIX((SI_Long)6L));
		  else
		      tformat(2,string_constant_21,error_name);
		  tformat(2,string_constant_22,error_text_string);
		  write_computation_context(computation_frame,
			  computation_component_particulars,
			  computation_instance,byte_code_body_qm,
			  constant_vector_qm,current_program_counter_qm,
			  local_stack_qm,top_of_stack_qm,local_var_vector_qm);
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

static Object array_constant_10;   /* # */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant_23;  /* "~%Program Counter: ~a" */

static Object string_constant_24;  /* "~%Activity: " */

static Object string_constant_25;  /* "~%Within: " */

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

static Object string_constant_26;  /* "~%Local Names:~%" */

/* WRITE-COMPUTATION-CONTEXT */
Object write_computation_context(computation_frame,
	    computation_component_particulars,computation_instance,
	    byte_code_body_qm,constant_vector_qm,program_counter_qm,
	    local_stack_qm,top_of_stack_qm,local_var_vector_qm)
    Object computation_frame, computation_component_particulars;
    Object computation_instance, byte_code_body_qm, constant_vector_qm;
    Object program_counter_qm, local_stack_qm, top_of_stack_qm;
    Object local_var_vector_qm;
{
    Object x2, type_name, computation_instance_byte_code_body_qm;
    Object environment_description_qm;
    char temp;

    x_note_fn_call(204,37);
    if (program_counter_qm && byte_code_body_qm && local_stack_qm && 
	    top_of_stack_qm) {
	twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)11L));
	pprint_stack_instruction(program_counter_qm,byte_code_body_qm,
		constant_vector_qm,local_stack_qm,top_of_stack_qm);
    }
    if (program_counter_qm && Disassemble_enabled_qm) {
	if (SIMPLE_VECTOR_P(computation_frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(computation_frame)) > 
		(SI_Long)2L &&  !EQ(ISVREF(computation_frame,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(computation_frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !(temp ? TRUEP(in_order_p(computation_frame)) : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (byte_code_body_qm && constant_vector_qm) {
	    tformat(1,string_constant_11);
	    write_stack_instruction(program_counter_qm,byte_code_body_qm,
		    constant_vector_qm);
	}
	tformat(2,string_constant_23,program_counter_qm);
    }
    if (byte_code_body_qm && computation_frame && program_counter_qm && 
	    ISVREF(byte_code_body_qm,(SI_Long)5L)) {
	tformat(1,string_constant_24);
	write_activity_given_pc_and_byte_code_body(byte_code_body_qm,
		program_counter_qm);
    }
    else if (computation_frame && Current_computation_activity) {
	tformat(1,string_constant_24);
	write_activity_given_index(computation_frame,
		computation_component_particulars,
		Current_computation_activity);
    }
    tformat(1,string_constant_25);
    write_stack_evaluator_backtrace(computation_frame,
	    computation_component_particulars,computation_instance,
	    local_stack_qm,top_of_stack_qm,Cached_stack_frame_base);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	write_code_body_invocation_environment(computation_instance,
		FIX((SI_Long)0L),Nil);
    else if (local_var_vector_qm) {
	tformat(1,string_constant_26);
	computation_instance_byte_code_body_qm = 
		computation_instance_byte_code_body(computation_instance);
	environment_description_qm = 
		computation_instance_byte_code_body_qm ? 
		ISVREF(computation_instance_byte_code_body_qm,(SI_Long)4L) 
		: Nil;
	write_code_body_environment(environment_description_qm,
		local_var_vector_qm);
    }
    if (Disassemble_enabled_qm && local_stack_qm && top_of_stack_qm) {
	if (SIMPLE_VECTOR_P(computation_frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(computation_frame)) > 
		(SI_Long)2L &&  !EQ(ISVREF(computation_frame,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(computation_frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !(temp ? TRUEP(in_order_p(computation_frame)) : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return write_stack_contents(3,local_stack_qm,top_of_stack_qm,
		FIX((SI_Long)4L));
    else
	return VALUES_1(Nil);
}

static Object string_constant_27;  /* "  tos: ~d" */

/* WRITE-COMPUTATION-CONTEXT-TO-CONSOLE */
Object write_computation_context_to_console(computation_frame,
	    computation_component_particulars,computation_instance,
	    byte_code_body_qm,constant_vector_qm,program_counter_qm,
	    local_stack,top_of_stack)
    Object computation_frame, computation_component_particulars;
    Object computation_instance, byte_code_body_qm, constant_vector_qm;
    Object program_counter_qm, local_stack, top_of_stack;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(204,38);
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
	      if (program_counter_qm) {
		  if (byte_code_body_qm && constant_vector_qm)
		      write_stack_instruction(program_counter_qm,
			      byte_code_body_qm,constant_vector_qm);
		  tformat(1,string_constant_19);
	      }
	      write_stack_evaluator_top_frame(computation_frame,
		      computation_component_particulars,
		      computation_instance,local_stack,
		      Cached_stack_frame_base);
	      if (top_of_stack)
		  tformat(2,string_constant_27,top_of_stack);
	      string_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    notify_user_at_console(1,string_1);
    return reclaim_text_string(string_1);
}

static Object string_constant_28;  /* "~%Local Names, Calling level ~a:~%" */

/* WRITE-CODE-BODY-INVOCATION-ENVIRONMENT */
Object write_code_body_invocation_environment(code_body_invocation,depth,
	    writing_local_vars_from_inferior_code_body_qm)
    Object code_body_invocation, depth;
    Object writing_local_vars_from_inferior_code_body_qm;
{
    Object computation_instance_byte_code_body_qm, environment_description_qm;
    Object local_var_vector_qm, write_local_vars_qm, temp, temp_1, temp_2;

    x_note_fn_call(204,39);
    computation_instance_byte_code_body_qm = 
	    computation_instance_byte_code_body(code_body_invocation);
    environment_description_qm = computation_instance_byte_code_body_qm ? 
	    ISVREF(computation_instance_byte_code_body_qm,(SI_Long)4L) : Nil;
    local_var_vector_qm = ISVREF(code_body_invocation,(SI_Long)2L);
    write_local_vars_qm = environment_description_qm ? local_var_vector_qm 
	    : Qnil;
    if ( ! !(SIMPLE_VECTOR_P(code_body_invocation) && 
	    EQ(ISVREF(code_body_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_code_body_invocation_g2_struct))) {
	temp = ISVREF(code_body_invocation,(SI_Long)12L);
	temp_1 = depth;
	temp_2 = writing_local_vars_from_inferior_code_body_qm;
	if (temp_2);
	else
	    temp_2 = write_local_vars_qm;
	depth = write_code_body_invocation_environment(temp,temp_1,temp_2);
    }
    if (write_local_vars_qm) {
	if (IFIX(depth) == (SI_Long)0L &&  
		!TRUEP(writing_local_vars_from_inferior_code_body_qm))
	    tformat(1,string_constant_26);
	else
	    tformat(2,string_constant_28,depth);
	write_code_body_environment(environment_description_qm,
		local_var_vector_qm);
    }
    return add1(depth);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_inference_background_collection_g2_struct;  /* g2-defstruct-structure-name::inference-background-collection-g2-struct */

/* COMPUTATION-INSTANCE-BYTE-CODE-BODY */
Object computation_instance_byte_code_body(computation_instance)
    Object computation_instance;
{
    Object type_name, x2, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object byte_code_body;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(204,40);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(ISVREF(computation_instance,(SI_Long)1L));
    else if (SIMPLE_VECTOR_P(computation_instance) && 
	    EQ(ISVREF(computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))
	return VALUES_1(ISVREF(computation_instance,(SI_Long)1L));
    else if (SIMPLE_VECTOR_P(computation_instance) && 
	    EQ(ISVREF(computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct))
	return VALUES_1(ISVREF(computation_instance,(SI_Long)1L));
    else if (SIMPLE_VECTOR_P(computation_instance) && 
	    EQ(ISVREF(computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_inference_background_collection_g2_struct))
	return VALUES_1(Nil);
    else {
	if (SIMPLE_VECTOR_P(computation_instance) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(computation_instance)) > 
		(SI_Long)2L &&  !EQ(ISVREF(computation_instance,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(computation_instance,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_expression_cell_class_description,
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
	if (temp)
	    return VALUES_1(ISVREF(computation_instance,(SI_Long)10L));
	else {
	    if (SIMPLE_VECTOR_P(computation_instance) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(computation_instance)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(computation_instance,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(computation_instance,(SI_Long)1L);
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
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (Current_simulation_runtime_structure) {
		    if (state_variable_p(computation_instance) && 
			    Initializing_state_variables_qm) {
			if (need_to_stack_eval_to_get_initial_value_for_state_variable_qm(computation_instance,
				Current_simulation_runtime_structure)) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(Current_computation_frame,
				    (SI_Long)1L),(SI_Long)19L);
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
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				temp_1 = ISVREF(Current_computation_frame,
					(SI_Long)21L);
			    else {
				sub_class_bit_vector = 
					ISVREF(ISVREF(Current_computation_frame,
					(SI_Long)1L),(SI_Long)19L);
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
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    temp_1 = 
					    ISVREF(Current_computation_frame,
					    (SI_Long)24L);
				else
				    temp_1 = Qnil;
			    }
			    byte_code_body = temp_1;
			}
			else {
			    temp_1 = Nil;
			    byte_code_body = temp_1;
			}
		    }
		    else {
			temp_1 = 
				ISVREF(Current_simulation_runtime_structure,
				(SI_Long)17L);
			byte_code_body = temp_1;
		    }
		    return VALUES_1(byte_code_body);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
}

Object Backtrace_depth_limit = UNBOUND;

static Object string_constant_29;  /* "~%  <- " */

static Object string_constant_30;  /* "[~a intervening function~a]" */

static Object string_constant_31;  /* "s" */

static Object string_constant_32;  /* "[~a intervening procedure~a]" */

static Object string_constant_33;  /* "called from G2GL process ~NF" */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* WRITE-STACK-EVALUATOR-BACKTRACE */
Object write_stack_evaluator_backtrace(computation_frame,
	    computation_component_particulars,computation_instance,stack,
	    top_of_stack,stack_frame_base)
    Object computation_frame, computation_component_particulars;
    Object computation_instance, stack, top_of_stack, stack_frame_base;
{
    Object separator_format_control_string, skipping_qm, count_1, first_qm;
    Object gensymed_symbol, sub_class_bit_vector, next_computation_frame;
    Object next_is_function_qm, skipped_frames, procedure_invocation;
    Object calling_procedure_invocation_qm, calling_invoc, purposes, purpose;
    Object ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(204,41);
    separator_format_control_string = string_constant_29;
    skipping_qm = Nil;
    count_1 = FIX((SI_Long)1L);
    first_qm = T;
  next_loop:
    if ( !TRUEP(computation_frame))
	goto end_loop;
    if ( !(first_qm || skipping_qm))
	tformat(1,separator_format_control_string);
    gensymed_symbol = ISVREF(computation_frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Function_definition_class_description,(SI_Long)18L));
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
    if (temp) {
	next_computation_frame = ISVREF(stack,IFIX(stack_frame_base) - 
		(SI_Long)2L);
	sub_class_bit_vector = ISVREF(ISVREF(next_computation_frame,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Function_definition_class_description,
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
	    next_is_function_qm = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	}
	else
	    next_is_function_qm = Nil;
	skipped_frames = FIXNUM_SUB1(FIXNUM_MINUS(count_1,
		Backtrace_depth_limit));
	if (FIXNUM_GT(count_1,Backtrace_depth_limit) &&  
		!TRUEP(skipping_qm) && next_is_function_qm)
	    skipping_qm = T;
	else if (skipping_qm &&  !TRUEP(next_is_function_qm)) {
	    tformat(3,string_constant_30,skipped_frames,
		    IFIX(skipped_frames) == (SI_Long)1L ? 
		    string_constant_16 : string_constant_31);
	    tformat(1,separator_format_control_string);
	    write_called_function_and_arguments(2,stack,stack_frame_base);
	    skipping_qm = Nil;
	    count_1 = FIX((SI_Long)0L);
	}
	else if ( !TRUEP(skipping_qm))
	    write_called_function_and_arguments(2,stack,stack_frame_base);
	computation_frame = next_computation_frame;
	computation_component_particulars = ISVREF(stack,
		IFIX(FIXNUM_SUB1(stack_frame_base)));
	stack_frame_base = ISVREF(stack,IFIX(stack_frame_base) - (SI_Long)6L);
    }
    else {
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
	    procedure_invocation = ISVREF(computation_instance,(SI_Long)11L);
	    calling_procedure_invocation_qm = 
		    calling_procedure_invocation(procedure_invocation);
	    if (FIXNUM_GT(count_1,Backtrace_depth_limit) &&  
		    !TRUEP(skipping_qm) && calling_procedure_invocation_qm)
		skipping_qm = T;
	    else if (skipping_qm &&  !TRUEP(calling_procedure_invocation_qm)) {
		tformat(3,string_constant_32,
			FIXNUM_SUB1(FIXNUM_MINUS(count_1,
			Backtrace_depth_limit)),
			IFIX(FIXNUM_SUB1(FIXNUM_MINUS(count_1,
			Backtrace_depth_limit))) == (SI_Long)1L ? 
			string_constant_16 : string_constant_31);
		tformat(1,separator_format_control_string);
		write_procedure_invocation_instance_from_slot(procedure_invocation,
			Nil);
		skipping_qm = Nil;
	    }
	    else if ( !TRUEP(skipping_qm))
		write_procedure_invocation_instance_from_slot(procedure_invocation,
			Nil);
	    if (calling_procedure_invocation_qm) {
		computation_frame = ISVREF(calling_procedure_invocation_qm,
			(SI_Long)23L);
		computation_component_particulars = Nil;
		computation_instance = calling_procedure_invocation_qm;
	    }
	    else {
		computation_frame = Nil;
		computation_component_particulars = Nil;
		computation_instance = Nil;
		if ( 
			!TRUEP(true_base_of_procedure_invocation_stack_p(procedure_invocation))) 
			    {
		    tformat(1,separator_format_control_string);
		    calling_invoc = ISVREF(procedure_invocation,(SI_Long)12L);
		    if (g2gl_call_invocation_p_function(calling_invoc))
			tformat(2,string_constant_33,
				calling_process_of_g2gl_call_invocation(calling_invoc));
		    else
			twrite_beginning_of_wide_string(array_constant_11,
				FIX((SI_Long)44L));
		}
	    }
	}
	else {
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		denote_component_of_block(3,T,
			computation_component_particulars,computation_frame);
		purposes = ISVREF(computation_instance,(SI_Long)16L);
		if ( !TRUEP(purposes));
		else if ( !TRUEP(M_CDR(purposes))) {
		    twrite_beginning_of_wide_string(array_constant_12,
			    FIX((SI_Long)13L));
		    write_rule_purpose(M_CAR(purposes));
		}
		else {
		    twrite_beginning_of_wide_string(array_constant_13,
			    FIX((SI_Long)27L));
		    purpose = Nil;
		    ab_loop_list_ = purposes;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    purpose = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    tformat(1,separator_format_control_string);
		    twrite_beginning_of_wide_string(array_constant_14,
			    FIX((SI_Long)2L));
		    write_rule_purpose(purpose);
		    goto next_loop_1;
		  end_loop_1:;
		}
		computation_frame = Nil;
		computation_component_particulars = Nil;
		computation_instance = Nil;
	    }
	    else {
		denote_component_of_block(3,T,
			computation_component_particulars,computation_frame);
		computation_frame = Nil;
		computation_component_particulars = Nil;
		computation_instance = Nil;
	    }
	}
    }
    count_1 = FIXNUM_ADD1(count_1);
    first_qm = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-STACK-EVALUATOR-TOP-FRAME */
Object write_stack_evaluator_top_frame(computation_frame,
	    computation_component_particulars,computation_instance,stack,
	    stack_frame_base)
    Object computation_frame, computation_component_particulars;
    Object computation_instance, stack, stack_frame_base;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(204,42);
    gensymed_symbol = ISVREF(computation_frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Function_definition_class_description,(SI_Long)18L));
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
    if (temp)
	return write_called_function_and_arguments(2,stack,stack_frame_base);
    else {
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
	if (temp)
	    return write_procedure_invocation_instance_from_slot(ISVREF(computation_instance,
		    (SI_Long)11L),Nil);
	else
	    return denote_component_of_block(3,T,
		    computation_component_particulars,computation_frame);
    }
}

static Object Qbackward_chaining;  /* backward-chaining */

static Object string_constant_34;  /* "backward chaining for ~NF" */

static Object Quser_menu_choice;   /* user-menu-choice */

static Object string_constant_35;  /* "user menu choice selection" */

static Object Qaction_button;      /* action-button */

static Object string_constant_36;  /* "action button selection" */

static Object Qforward_chaining;   /* forward-chaining */

static Object string_constant_37;  /* "forward chaining" */

static Object Qscanning;           /* scanning */

static Object string_constant_38;  /* "scan interval" */

static Object Qinitializing;       /* initializing */

static Object string_constant_39;  /* "initial rule invocation" */

static Object Qfocusing;           /* focusing */

static Object string_constant_40;  /* "focus action" */

static Object Qinvoking;           /* invoking */

static Object string_constant_41;  /* "invoke action" */

static Object string_constant_42;  /* "rule purpose not recorded" */

static Object array_constant_15;   /* # */

/* WRITE-RULE-PURPOSE */
Object write_rule_purpose(purpose)
    Object purpose;
{
    Object temp;

    x_note_fn_call(204,43);
    if (CONSP(purpose) && EQ(M_CAR(purpose),Qbackward_chaining))
	return tformat(2,string_constant_34,M_CDR(purpose));
    else if (SYMBOLP(purpose)) {
	if (EQ(purpose,Quser_menu_choice))
	    temp = string_constant_35;
	else if (EQ(purpose,Qaction_button))
	    temp = string_constant_36;
	else if (EQ(purpose,Qforward_chaining))
	    temp = string_constant_37;
	else if (EQ(purpose,Qscanning))
	    temp = string_constant_38;
	else if (EQ(purpose,Qinitializing))
	    temp = string_constant_39;
	else if (EQ(purpose,Qfocusing))
	    temp = string_constant_40;
	else if (EQ(purpose,Qinvoking))
	    temp = string_constant_41;
	else
	    temp = string_constant_42;
	return twrite_general_string(temp);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_15,
		FIX((SI_Long)25L));
}

/* GET-CALL-SEQUENCE */
Object get_call_sequence(depth,computation_frame,computation_instance,
	    stack_frame_base)
    Object depth, computation_frame, computation_instance, stack_frame_base;
{
    Object stack, current_frame, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensymed_symbol, sub_class_bit_vector, temp_1, procedure_invocation;
    Object calling_procedure_invocation_qm, x2;
    SI_Long count_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;

    x_note_fn_call(204,44);
    stack = Global_stack;
    count_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(depth);
    current_frame = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (count_1 > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(computation_frame))
	goto end_loop;
    gensymed_symbol = ISVREF(computation_frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Function_definition_class_description,(SI_Long)18L));
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
    if (temp) {
	temp_1 = ISVREF(stack,IFIX(stack_frame_base) - (SI_Long)7L);
	computation_frame = ISVREF(stack,IFIX(stack_frame_base) - (SI_Long)2L);
	stack_frame_base = ISVREF(stack,IFIX(stack_frame_base) - (SI_Long)6L);
	current_frame = temp_1;
    }
    else {
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
	    procedure_invocation = ISVREF(computation_instance,(SI_Long)11L);
	    calling_procedure_invocation_qm = 
		    calling_procedure_invocation(procedure_invocation);
	    temp_1 = ISVREF(procedure_invocation,(SI_Long)23L);
	    if (calling_procedure_invocation_qm) {
		computation_frame = ISVREF(calling_procedure_invocation_qm,
			(SI_Long)23L);
		computation_instance = calling_procedure_invocation_qm;
	    }
	    else {
		computation_frame = Nil;
		computation_instance = Nil;
	    }
	    current_frame = temp_1;
	}
	else {
	    temp_1 = computation_frame;
	    computation_frame = Nil;
	    computation_instance = Nil;
	    current_frame = temp_1;
	}
    }
    if (SIMPLE_VECTOR_P(current_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_frame)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(current_frame,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(current_frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	ab_loopvar__2 = eval_cons_1(current_frame,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp_1);
}

/* GET-COMPUTATION-INSTANCE-FOR-BLOCK */
Object get_computation_instance_for_block(block,computation_frame,
	    computation_instance,stack_frame_base)
    Object block, computation_frame, computation_instance, stack_frame_base;
{
    Object stack, computation_instance_for_current_frame, current_frame;
    Object ab_loop_iter_flag_, type_name, gensymed_symbol;
    Object sub_class_bit_vector, temp_1, procedure_invocation;
    Object calling_procedure_invocation_qm;
    SI_Long index_1, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(204,45);
    stack = Global_stack;
    index_1 = (SI_Long)0L;
    computation_instance_for_current_frame = Nil;
    current_frame = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (computation_frame) {
	if (SIMPLE_VECTOR_P(computation_instance)) {
	    type_name = ISVREF(computation_instance,(SI_Long)0L);
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp);
	    else
		temp = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    computation_instance_for_current_frame = computation_instance;
    gensymed_symbol = ISVREF(computation_frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Function_definition_class_description,(SI_Long)18L));
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
    if (temp) {
	if ((SI_Long)0L <= IFIX(FIXNUM_ADD1(stack_frame_base)) - 
		    (SI_Long)10L) {
	    temp_1 = ISVREF(stack,IFIX(stack_frame_base) - (SI_Long)7L);
	    computation_frame = ISVREF(stack,IFIX(stack_frame_base) - 
		    (SI_Long)2L);
	    stack_frame_base = ISVREF(stack,IFIX(stack_frame_base) - 
		    (SI_Long)6L);
	    current_frame = temp_1;
	}
	else
	    current_frame = Nil;
    }
    else {
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
	    procedure_invocation = ISVREF(computation_instance,(SI_Long)11L);
	    calling_procedure_invocation_qm = 
		    calling_procedure_invocation(procedure_invocation);
	    temp_1 = ISVREF(procedure_invocation,(SI_Long)23L);
	    if (calling_procedure_invocation_qm) {
		computation_frame = ISVREF(calling_procedure_invocation_qm,
			(SI_Long)23L);
		computation_instance = calling_procedure_invocation_qm;
	    }
	    else {
		computation_frame = Nil;
		computation_instance = Nil;
	    }
	    current_frame = temp_1;
	}
	else {
	    temp_1 = computation_frame;
	    computation_frame = Nil;
	    computation_instance = Nil;
	    current_frame = temp_1;
	}
    }
    if (EQ(block,current_frame))
	return VALUES_2(computation_instance_for_current_frame,FIX(index_1));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* EXECUTE-COMPUTATION-INSTANCE */
Object execute_computation_instance(computation_instance)
    Object computation_instance;
{
    Object fixnum_time_limit_qm, byte_code_body, constant_vector;
    Object local_var_vector, stack_program_counter, instance;

    x_note_fn_call(204,46);
    if (queue_invocation_for_lock_if_necessary(computation_instance)) {
	if (Inside_breakpoint_p)
	    schedule_computation_instance_execution_for_breakpoint(computation_instance);
	else {
	    fixnum_time_limit_qm = 
		    enter_or_reclaim_computation_instance_context(computation_instance);
	    if ( !(Current_schedule_task && 
		    FIXNUM_EQ(ISVREF(Current_schedule_task,(SI_Long)4L),
		    Higher_than_any_priority)))
		Cached_fixnum_start_time = 
			c_native_clock_ticks_or_cache(Nil,Nil);
	    if (Current_computation_instance) {
		byte_code_body = Nil;
		constant_vector = Nil;
		local_var_vector = Nil;
		stack_program_counter = Nil;
		instance = Current_computation_instance;
		byte_code_body = ISVREF(instance,(SI_Long)1L);
		Cached_byte_code_body = byte_code_body;
		local_var_vector = ISVREF(instance,(SI_Long)2L);
		constant_vector = ISVREF(instance,(SI_Long)4L);
		stack_program_counter = ISVREF(instance,(SI_Long)3L);
		Cached_stack_program_counter = stack_program_counter;
		stack_eval_for_execute_computation_instance(byte_code_body,
			constant_vector,local_var_vector,
			Cached_fixnum_start_time,fixnum_time_limit_qm,
			stack_program_counter);
		clear_computation_context_variables();
	    }
	}
    }
    return VALUES_1(Nil);
}

/* RECLAIM-TOP-OF-STACK */
Object reclaim_top_of_stack()
{
    Object thing;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(204,47);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Cached_top_of_stack);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    thing = ISVREF(Global_stack,index_1);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* WITHIN-STACK-EVAL-P */
Object within_stack_eval_p()
{
    x_note_fn_call(204,48);
    return VALUES_1(Current_computation_instance);
}

static Object Qprocedure;          /* procedure */

static Object Qproc;               /* proc */

/* DETECT-DEADLOCKS */
Object detect_deadlocks(find_cycle)
    Object find_cycle;
{
    Object invocations_hash_table, invocations_to_process, invocation_entries;
    Object awaiting_serialization, number_of_unserialized_invocations;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, method, invocations;
    Object ab_hash_table_, ab_tree_form_, ab_node_stack_, ab_current_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_skip_list_p_, ab_tail_node_;
    Object invocation, ab_less_than_branch_qm_, gensymed_symbol, temp_1;
    Object proc_pop_store, cons_1, next_cons, temp_2, svref_arg_2;
    Object invocation_entry, waited_for_invocation, ab_loop_list_;
    Object waiting_invocation, ab_loop_list__1, proc_push_modify_macro_arg;
    Object car_1, cdr_1, waiter, entry;
    SI_Long ab_table_length_, ab_index_;
    char temp;
    Declare_special(2);

    x_note_fn_call(204,49);
    invocations_hash_table = make_eq_hash_table(FIX((SI_Long)10L),Nil,Nil);
    invocations_to_process = Nil;
    invocation_entries = Nil;
    awaiting_serialization = Nil;
    number_of_unserialized_invocations = FIX((SI_Long)0L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    method = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qprocedure);
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
      method = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      invocations = ISVREF(method,(SI_Long)26L);
      if (invocations) {
	  scope_conses = Scope_conses;
	  ab_hash_table_ = invocations;
	  ab_table_length_ = (SI_Long)0L;
	  ab_index_ = (SI_Long)0L;
	  ab_tree_form_ = Nil;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_skip_list_p_ = Nil;
	  ab_tail_node_ = Nil;
	  invocation = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_current_node_ && ab_skip_list_p_) {
		ab_current_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			(SI_Long)0L),(SI_Long)0L));
		if (EQ(ab_current_node_,ab_tail_node_))
		    ab_current_node_ = Nil;
		else
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	    }
	    else if (ab_current_node_) {
		ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		if (ab_current_node_) {
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack_) {
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		if (ab_current_node_) {
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_)) {
	      next_loop_4:
		if ( !(ab_index_ < ab_table_length_))
		    goto end_loop_3;
		ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		if (ab_index_ == (SI_Long)0L) {
		    gensymed_symbol = CDR(ab_tree_form_);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			temp_1 = M_CDR(gensymed_symbol);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		}
		ab_index_ = ab_index_ + (SI_Long)1L;
		if (ab_skip_list_p_) {
		    ab_current_node_ = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_tree_form_)),
			    (SI_Long)0L),(SI_Long)0L));
		    ab_tail_node_ = M_CDR(M_CDR(ab_tree_form_));
		    if (EQ(ab_current_node_,ab_tail_node_))
			ab_current_node_ = Nil;
		    else {
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
				(SI_Long)2L),ISVREF(ab_current_node_,
				(SI_Long)3L));
			goto end_loop_3;
		    }
		}
		else {
		    ab_current_node_ = CDR(ab_tree_form_);
		    if (ab_current_node_) {
			ab_less_than_branch_qm_ = Nil;
		      next_loop_5:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_4;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_5;
		      end_loop_4:;
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
			goto end_loop_3;
		    }
		}
		goto next_loop_4;
	      end_loop_3:;
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_5;
	    invocation = M_CDR(ab_entry_cons_);
	    invocations_to_process = proc_cons_1(invocation,
		    invocations_to_process);
	    goto next_loop_2;
	  end_loop_5:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
  next_loop_6:
    if ( !TRUEP(invocations_to_process))
	goto end_loop_6;
    proc_pop_store = Nil;
    cons_1 = invocations_to_process;
    if (cons_1) {
	proc_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qproc);
	if (ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = cons_1;
	    temp_2 = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	else {
	    temp_2 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	    temp_2 = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    invocations_to_process = next_cons;
    invocation = proc_pop_store;
    if ( !TRUEP(eq_gethash(invocations_hash_table,invocation,Nil))) {
	if (ISVREF(invocation,(SI_Long)19L))
	    temp_1 = FIX((SI_Long)1L);
	else if (waiting_for_do_in_parallel_until_one_completes(invocation))
	    temp_1 = ISVREF(invocation,(SI_Long)13L) ? FIX((SI_Long)1L) : 
		    FIX((SI_Long)0L);
	else
	    temp_1 = length(ISVREF(invocation,(SI_Long)13L));
	invocation_entry = proc_list_3(invocation,temp_1,Nil);
	eq_puthash(invocations_hash_table,invocation,invocation_entry);
	invocation_entries = proc_cons_1(invocation_entry,invocation_entries);
	number_of_unserialized_invocations = 
		FIXNUM_ADD1(number_of_unserialized_invocations);
	waited_for_invocation = Nil;
	ab_loop_list_ = ISVREF(invocation,(SI_Long)13L);
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	waited_for_invocation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(eq_gethash(invocations_hash_table,
		waited_for_invocation,Nil)))
	    invocations_to_process = proc_cons_1(waited_for_invocation,
		    invocations_to_process);
	goto next_loop_7;
      end_loop_7:;
    }
    goto next_loop_6;
  end_loop_6:
    invocation_entry = Nil;
    ab_loop_list_ = invocation_entries;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    invocation_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    invocation = CAR(invocation_entry);
    waiting_invocation = Nil;
    ab_loop_list__1 = ISVREF(invocation,(SI_Long)18L);
  next_loop_9:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_9;
    waiting_invocation = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    proc_push_modify_macro_arg = eq_gethash(invocations_hash_table,
	    waiting_invocation,Nil);
    car_1 = proc_push_modify_macro_arg;
    cdr_1 = THIRD(invocation_entry);
    temp_2 = proc_cons_1(car_1,cdr_1);
    M_THIRD(invocation_entry) = temp_2;
    goto next_loop_9;
  end_loop_9:;
    if (ISVREF(invocation,(SI_Long)12L)) {
	proc_push_modify_macro_arg = eq_gethash(invocations_hash_table,
		ISVREF(invocation,(SI_Long)12L),Nil);
	car_1 = proc_push_modify_macro_arg;
	cdr_1 = THIRD(invocation_entry);
	temp_2 = proc_cons_1(car_1,cdr_1);
	M_THIRD(invocation_entry) = temp_2;
    }
    if (IFIX(SECOND(invocation_entry)) == (SI_Long)0L)
	awaiting_serialization = proc_cons_1(invocation_entry,
		awaiting_serialization);
    goto next_loop_8;
  end_loop_8:;
    reclaim_eq_hash_table(invocations_hash_table);
  next_loop_10:
    if ( !TRUEP(awaiting_serialization))
	goto end_loop_10;
    proc_pop_store = Nil;
    cons_1 = awaiting_serialization;
    if (cons_1) {
	proc_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qproc);
	if (ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = cons_1;
	    temp_2 = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	else {
	    temp_2 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	    temp_2 = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    awaiting_serialization = next_cons;
    invocation_entry = proc_pop_store;
    number_of_unserialized_invocations = 
	    FIXNUM_SUB1(number_of_unserialized_invocations);
    waiter = Nil;
    ab_loop_list_ = THIRD(invocation_entry);
  next_loop_11:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_11;
    waiter = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_2 = FIXNUM_SUB1(SECOND(waiter));
    if (IFIX(M_SECOND(waiter) = temp_2) == (SI_Long)0L)
	awaiting_serialization = proc_cons_1(waiter,awaiting_serialization);
    goto next_loop_11;
  end_loop_11:;
    goto next_loop_10;
  end_loop_10:
    temp_1 = IFIX(number_of_unserialized_invocations) == (SI_Long)0L ? Nil 
	    : find_cycle ? 
	    find_cycle_in_invocation_entry_list(invocation_entries) : T;
    entry = Nil;
    ab_loop_list_ = invocation_entries;
  next_loop_12:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_12;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_proc_list_1(THIRD(entry));
    reclaim_proc_list_1(entry);
    goto next_loop_12;
  end_loop_12:;
    reclaim_proc_list_1(invocation_entries);
    return VALUES_1(temp_1);
}

static Object Qabort_called_code_bodies;  /* abort-called-code-bodies */

/* WAITING-FOR-DO-IN-PARALLEL-UNTIL-ONE-COMPLETES */
Object waiting_for_do_in_parallel_until_one_completes(invocation)
    Object invocation;
{
    x_note_fn_call(204,50);
    return VALUES_1(EQ(ISVREF(instruction_description_for_op_code(FIX(UBYTE_8_ISAREF_1(ISVREF(ISVREF(invocation,
	    (SI_Long)1L),(SI_Long)2L),IFIX(ISVREF(invocation,
	    (SI_Long)3L))))),(SI_Long)1L),Qabort_called_code_bodies) ? T : 
	    Nil);
}

/* FIND-CYCLE-IN-INVOCATION-ENTRY-LIST */
Object find_cycle_in_invocation_entry_list(invocation_entries)
    Object invocation_entries;
{
    Object entry, ab_loop_list_, cycle;

    x_note_fn_call(204,51);
    entry = Nil;
    ab_loop_list_ = invocation_entries;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(IFIX(SECOND(entry)) == (SI_Long)0L)) {
	cycle = find_cycle_or_extend_path_in_invocation_entry_list(entry);
	if (cycle)
	    return VALUES_1(cycle);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-CYCLE-OR-EXTEND-PATH-IN-INVOCATION-ENTRY-LIST */
Object find_cycle_or_extend_path_in_invocation_entry_list(entry)
    Object entry;
{
    Object temp, waiting_for_this, ab_loop_list_, path_or_cycle, end_of_path;
    Object result;

    x_note_fn_call(204,52);
    if (EQ(SECOND(entry),T)) {
	temp = proc_cons_1(CAR(entry),Nil);
	return VALUES_2(temp,CAR(entry));
    }
    else {
	waiting_for_this = Nil;
	ab_loop_list_ = THIRD(entry);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	waiting_for_this = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(waiting_for_this,entry)) {
	    temp = proc_cons_1(CAR(entry),Nil);
	    return VALUES_2(temp,Nil);
	}
	else if (EQ(SECOND(waiting_for_this),FIX((SI_Long)0L)))
	    return VALUES_2(Nil,Nil);
	else {
	    M_SECOND(entry) = T;
	    result = find_cycle_or_extend_path_in_invocation_entry_list(waiting_for_this);
	    MVS_2(result,path_or_cycle,end_of_path);
	    if (end_of_path) {
		if (EQ(end_of_path,CAR(entry)))
		    return VALUES_2(path_or_cycle,Nil);
		else {
		    temp = proc_cons_1(CAR(entry),path_or_cycle);
		    return VALUES_2(temp,end_of_path);
		}
	    }
	    else if (path_or_cycle)
		return VALUES_2(path_or_cycle,Nil);
	    else
		M_SECOND(entry) = FIX((SI_Long)0L);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_43;  /* "Procedure aborted to break a deadlock" */

static Object Qg2_deadlock_error;  /* g2-deadlock-error */

/* ABORT-TO-BREAK-DEADLOCK */
Object abort_to_break_deadlock(code_body_invocation)
    Object code_body_invocation;
{
    Object temp;

    x_note_fn_call(204,53);
    temp = copy_text_string(string_constant_43);
    return signal_code_body_invocation_error(9,code_body_invocation,
	    Qg2_deadlock_error,FIX((SI_Long)1L),temp,
	    ISVREF(code_body_invocation,(SI_Long)1L),Nil,Global_stack,
	    FIX((SI_Long)-1L),T);
}

/* DETECT-AND-BREAK-DEADLOCKS */
Object detect_and_break_deadlocks()
{
    Object deadlock_found, invocation_cycle;

    x_note_fn_call(204,54);
    deadlock_found = Nil;
  next_loop:
    invocation_cycle = detect_deadlocks(T);
    if ( !TRUEP(invocation_cycle))
	return VALUES_1(deadlock_found);
    deadlock_found = T;
    break_one_deadlock(invocation_cycle);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* BREAK-ONE-DEADLOCK */
Object break_one_deadlock(invocation_cycle)
    Object invocation_cycle;
{
    Object candidate_procedure_to_abort_cons, candidate, next;

    x_note_fn_call(204,55);
    candidate_procedure_to_abort_cons = invocation_cycle;
    candidate = invocation_cycle;
  next_loop:
    if ( !TRUEP(candidate))
	goto end_loop;
    if (find_error_handler_for_code_body_invocation(Qg2_deadlock_error,
	    CAR(candidate))) {
	candidate_procedure_to_abort_cons = candidate;
	goto end_loop;
    }
    candidate = M_CDR(candidate);
    goto next_loop;
  end_loop:;
  next_loop_1:
    next = CDR(candidate_procedure_to_abort_cons);
    if (next);
    else
	next = invocation_cycle;
    if (EQ(ISVREF(CAR(next),(SI_Long)12L),
	    CAR(candidate_procedure_to_abort_cons)))
	candidate_procedure_to_abort_cons = next;
    else
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:
    abort_to_break_deadlock(CAR(candidate_procedure_to_abort_cons));
    reclaim_proc_list_1(invocation_cycle);
    return VALUES_1(Nil);
}

static Object string_constant_44;  /* "Deadlock detected: Use detect-and-break-deadlocks to abort deadlocked procedures" */

static Object string_constant_45;  /* "No deadlock detected" */

/* DETECT-DEADLOCKS-FOR-UI */
Object detect_deadlocks_for_ui()
{
    x_note_fn_call(204,56);
    if (detect_deadlocks(Nil))
	return notify_user(1,string_constant_44);
    else
	return notify_user(1,string_constant_45);
}

/* DETECT-AND-BREAK-DEADLOCKS-FOR-UI */
Object detect_and_break_deadlocks_for_ui()
{
    x_note_fn_call(204,57);
    if ( !TRUEP(detect_and_break_deadlocks()))
	return notify_user(1,string_constant_45);
    else
	return VALUES_1(Nil);
}

/* G2-DETECT-DEADLOCKS */
Object g2_detect_deadlocks()
{
    x_note_fn_call(204,58);
    if (detect_deadlocks(Nil))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-DETECT-AND-BREAK-DEADLOCKS */
Object g2_detect_and_break_deadlocks()
{
    x_note_fn_call(204,59);
    if (detect_and_break_deadlocks())
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Automatic_deadlock_detection_task, Qautomatic_deadlock_detection_task);

DEFINE_VARIABLE_WITH_SYMBOL(Automatic_deadlock_detection_frequency, Qautomatic_deadlock_detection_frequency);

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qdetect_and_break_deadlocks;  /* detect-and-break-deadlocks */

/* SET-DEADLOCK-DETECTION-FREQUENCY */
Object set_deadlock_detection_frequency(new_frequency,force_qm)
    Object new_frequency, force_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object frequency_as_float, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value, task;
    char svref_new_value_1;
    double temp_1, temp_2, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(204,60);
    if ( !( !TRUEP(force_qm) && ( !TRUEP(new_frequency) &&  
	    !TRUEP(Automatic_deadlock_detection_frequency) || 
	    new_frequency && Automatic_deadlock_detection_frequency && 
	    FIXNUM_EQ(new_frequency,
		Automatic_deadlock_detection_frequency)))) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = Automatic_deadlock_detection_task;
	if (CAS_SYMBOL(Qautomatic_deadlock_detection_task,gensymed_symbol,
		    Nil)) {
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
	if (new_frequency) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		frequency_as_float = lfloat(new_frequency,_);
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = Automatic_deadlock_detection_task;
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_schedule_task_g2_struct;
		}
		else
		    def_structure_schedule_task_variable = 
			    make_permanent_schedule_task_structure_internal();
		inline_note_allocate_cons(def_structure_schedule_task_variable,
			Nil);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		temp_1 = g2ext_unix_time_as_float();
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(frequency_as_float);
		aref_new_value = temp_1 + temp_2;
		DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(frequency_as_float);
		DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
		svref_new_value_1 =  !TRUEP(Nil);
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = Qdetect_and_break_deadlocks;
		temp = SYMBOL_FUNCTION(Qdetect_and_break_deadlocks);
		SVREF(task,FIX((SI_Long)8L)) = temp;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
		new_1 = task;
		if (CAS_SYMBOL(Qautomatic_deadlock_detection_task,old,new_1)) {
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
			temp = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(old,FIX((SI_Long)0L)) = temp;
			temp = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = old;
		    }
		    future_task_schedule_2(new_1);
		    goto end_2;
		}
		else {
		    inline_note_reclaim_cons(new_1,Nil);
		    structure_being_reclaimed = new_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
		      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(new_1,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = new_1;
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    Automatic_deadlock_detection_frequency = new_frequency;
	    return VALUES_1(Automatic_deadlock_detection_frequency);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_46;  /* "Trying to write a string longer than 2MB!" */

/* HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR */
Object handle_extend_current_text_string_error()
{
    Object top_of_stack, message_1;

    x_note_fn_call(204,61);
    if (within_stack_eval_p()) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_46);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return error((SI_Long)1L,"Trying to write a string longer than 2MB!");
}

void stack_utils_INIT()
{
    Object gensymed_symbol, the_array;
    SI_Long i, ab_loop_bind_;
    Object Qhandle_extend_current_text_string_error, AB_package;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qstack_utils;
    Object Qg2_detect_and_break_deadlocks;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_detect_deadlocks, Qexecute_computation_instance;
    Object list_constant_29, Qnumber_of_extra_stack_frame_values;
    Object Qserve_next_iteration_value, Qopen_role_iteration;
    Object Qopen_role_iteration_no_domain, Qcase_dispatch;
    Object Qstack_instructions_count_in_g2, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, list_constant_13, list_constant_12;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_8, list_constant_7, Qfloat_register_2;
    Object Qfloat_register_1, float_constant, Qinitial_recursion_depth;
    Object Qrecursion_depth, list_constant_4, Qfixnum_register_2;
    Object Qfixnum_register_1, list_constant_6, Qregister_5, Qregister_4;
    Object Qregister_3, Qregister_2, Qregister_1, Qmajor_tracing_qm;
    Object Qdetailed_tracing_qm, list_constant_5, Qlocal_truth_threshold;
    Object Qtruth_threshold, Qbyte_instruction, Qinstruction_count;
    Object Qinitial_program_counter, Qstack_program_counter;
    Object Qinitial_stack_frame_base, Qstack_frame_base, Qinitial_top_of_stack;
    Object Qtop_of_stack, Qlocal_stack, list_constant_3, Qinstruction_vector;
    Object Qbyte_code_body, Qbyte_code_body_byte_vector;
    Object Qmaximum_stack_frame_size, Qmake_global_stack, list_constant_2;
    Object Qutilities0, Kfuncall, Qglobal_stack_size, Qfuncall_eval_type_8_arg;
    Object Qfuncall_eval_type_7_arg, Qfuncall_eval_type_6_arg;
    Object Qfuncall_eval_type_5_arg, Qfuncall_eval_type_4_arg;
    Object Qfuncall_eval_type_3_arg, Qfuncall_eval_type_2_arg;
    Object Qfuncall_eval_type_1_arg, Qfuncall_eval_type_0_arg;
    Object Qmaximum_number_of_funcalled_instructions, Qsimulator, Qinference;

    x_note_fn_call(204,62);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qall = STATIC_SYMBOL("ALL",AB_package);
    Qinference = STATIC_SYMBOL("INFERENCE",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qinference,Qprocedure,Qsimulator);
    Qstack_evaluators = STATIC_SYMBOL("STACK-EVALUATORS",AB_package);
    if (Dummy_evaluators_list == UNBOUND)
	Dummy_evaluators_list = Nil;
    Qmaximum_number_of_funcalled_instructions = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-FUNCALLED-INSTRUCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_number_of_funcalled_instructions,
	    FIX((SI_Long)100L));
    if (Funcalled_instructions == UNBOUND) {
	gensymed_symbol = Maximum_number_of_funcalled_instructions;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	Funcalled_instructions = the_array;
    }
    if (Funcalled_instruction_functions == UNBOUND) {
	gensymed_symbol = Maximum_number_of_funcalled_instructions;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	Funcalled_instruction_functions = the_array;
    }
    Qfuncalled_instruction_description = 
	    STATIC_SYMBOL("FUNCALLED-INSTRUCTION-DESCRIPTION",AB_package);
    Funcalled_instruction_description_prop = 
	    Qfuncalled_instruction_description;
    Qfuncall_eval_type_0_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-0-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_0_arg,FIX((SI_Long)0L));
    Qfuncall_eval_type_1_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-1-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_1_arg,FIX((SI_Long)1L));
    Qfuncall_eval_type_2_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-2-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_2_arg,FIX((SI_Long)2L));
    Qfuncall_eval_type_3_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-3-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_3_arg,FIX((SI_Long)3L));
    Qfuncall_eval_type_4_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-4-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_4_arg,FIX((SI_Long)4L));
    Qfuncall_eval_type_5_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-5-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_5_arg,FIX((SI_Long)5L));
    Qfuncall_eval_type_6_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-6-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_6_arg,FIX((SI_Long)6L));
    Qfuncall_eval_type_7_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-7-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_7_arg,FIX((SI_Long)7L));
    Qfuncall_eval_type_8_arg = STATIC_SYMBOL("FUNCALL-EVAL-TYPE-8-ARG",
	    AB_package);
    SET_SYMBOL_VALUE(Qfuncall_eval_type_8_arg,FIX((SI_Long)8L));
    Qglobal_stack_size = STATIC_SYMBOL("GLOBAL-STACK-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qglobal_stack_size,FIX((SI_Long)8192L));
    Qglobal_stack = STATIC_SYMBOL("GLOBAL-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_stack,Global_stack);
    Qutilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_global_stack = STATIC_SYMBOL("MAKE-GLOBAL-STACK",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Kfuncall,Qmake_global_stack);
    record_system_variable(Qglobal_stack,Qutilities0,list_constant_2,Qnil,
	    Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qmake_global_stack,
	    STATIC_FUNCTION(make_global_stack,NIL,FALSE,0,0));
    Qfree_global_stacks = STATIC_SYMBOL("FREE-GLOBAL-STACKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfree_global_stacks,Free_global_stacks);
    Qstack_utils = STATIC_SYMBOL("STACK-UTILS",AB_package);
    record_system_variable(Qfree_global_stacks,Qstack_utils,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qmaximum_stack_frame_size = STATIC_SYMBOL("MAXIMUM-STACK-FRAME-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmaximum_stack_frame_size,FIX((SI_Long)350L));
    Qinstruction_vector = STATIC_SYMBOL("INSTRUCTION-VECTOR",AB_package);
    Qbyte_code_body_byte_vector = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-BYTE-VECTOR",AB_package);
    Qbyte_code_body = STATIC_SYMBOL("BYTE-CODE-BODY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qbyte_code_body_byte_vector,
	    Qbyte_code_body);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qinstruction_vector,
	    list_constant_3);
    Qlocal_stack = STATIC_SYMBOL("LOCAL-STACK",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qlocal_stack,Qglobal_stack);
    Qtop_of_stack = STATIC_SYMBOL("TOP-OF-STACK",AB_package);
    Qinitial_top_of_stack = STATIC_SYMBOL("INITIAL-TOP-OF-STACK",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qtop_of_stack,
	    Qinitial_top_of_stack);
    Qstack_frame_base = STATIC_SYMBOL("STACK-FRAME-BASE",AB_package);
    Qinitial_stack_frame_base = STATIC_SYMBOL("INITIAL-STACK-FRAME-BASE",
	    AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qstack_frame_base,
	    Qinitial_stack_frame_base);
    Qstack_program_counter = STATIC_SYMBOL("STACK-PROGRAM-COUNTER",AB_package);
    Qinitial_program_counter = STATIC_SYMBOL("INITIAL-PROGRAM-COUNTER",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qstack_program_counter,
	    Qinitial_program_counter);
    Qinstruction_count = STATIC_SYMBOL("INSTRUCTION-COUNT",AB_package);
    list_constant_4 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_13 = STATIC_CONS(Qinstruction_count,list_constant_4);
    Qbyte_instruction = STATIC_SYMBOL("BYTE-INSTRUCTION",AB_package);
    list_constant_14 = STATIC_CONS(Qbyte_instruction,list_constant_4);
    Qlocal_truth_threshold = STATIC_SYMBOL("LOCAL-TRUTH-THRESHOLD",AB_package);
    Qtruth_threshold = STATIC_SYMBOL("TRUTH-THRESHOLD",AB_package);
    Qinference_engine_parameters = 
	    STATIC_SYMBOL("INFERENCE-ENGINE-PARAMETERS",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qtruth_threshold,
	    Qinference_engine_parameters);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qlocal_truth_threshold,
	    list_constant_5);
    Qdetailed_tracing_qm = STATIC_SYMBOL("DETAILED-TRACING\?",AB_package);
    list_constant_6 = STATIC_CONS(Qnil,Qnil);
    list_constant_16 = STATIC_CONS(Qdetailed_tracing_qm,list_constant_6);
    Qmajor_tracing_qm = STATIC_SYMBOL("MAJOR-TRACING\?",AB_package);
    list_constant_17 = STATIC_CONS(Qmajor_tracing_qm,list_constant_6);
    Qregister_1 = STATIC_SYMBOL("REGISTER-1",AB_package);
    list_constant_18 = STATIC_CONS(Qregister_1,list_constant_6);
    Qregister_2 = STATIC_SYMBOL("REGISTER-2",AB_package);
    list_constant_19 = STATIC_CONS(Qregister_2,list_constant_6);
    Qregister_3 = STATIC_SYMBOL("REGISTER-3",AB_package);
    list_constant_20 = STATIC_CONS(Qregister_3,list_constant_6);
    Qregister_4 = STATIC_SYMBOL("REGISTER-4",AB_package);
    list_constant_21 = STATIC_CONS(Qregister_4,list_constant_6);
    Qregister_5 = STATIC_SYMBOL("REGISTER-5",AB_package);
    list_constant_22 = STATIC_CONS(Qregister_5,list_constant_6);
    Qfixnum_register_1 = STATIC_SYMBOL("FIXNUM-REGISTER-1",AB_package);
    list_constant_23 = STATIC_CONS(Qfixnum_register_1,list_constant_4);
    Qfixnum_register_2 = STATIC_SYMBOL("FIXNUM-REGISTER-2",AB_package);
    list_constant_24 = STATIC_CONS(Qfixnum_register_2,list_constant_4);
    Qrecursion_depth = STATIC_SYMBOL("RECURSION-DEPTH",AB_package);
    Qinitial_recursion_depth = STATIC_SYMBOL("INITIAL-RECURSION-DEPTH",
	    AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qrecursion_depth,
	    Qinitial_recursion_depth);
    Qfloat_register_1 = STATIC_SYMBOL("FLOAT-REGISTER-1",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    list_constant_7 = STATIC_CONS(float_constant,Qnil);
    list_constant_26 = STATIC_CONS(Qfloat_register_1,list_constant_7);
    Qfloat_register_2 = STATIC_SYMBOL("FLOAT-REGISTER-2",AB_package);
    list_constant_27 = STATIC_CONS(Qfloat_register_2,list_constant_7);
    list_constant_28 = STATIC_LIST((SI_Long)20L,list_constant_8,
	    list_constant_9,list_constant_10,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24,list_constant_25,list_constant_26,
	    list_constant_27);
    Stack_eval_locals_bindings = list_constant_28;
    if (Float_contagion_stack_operators == UNBOUND)
	Float_contagion_stack_operators = Nil;
    Qstack_instructions_count_in_g2 = 
	    STATIC_SYMBOL("STACK-INSTRUCTIONS-COUNT-IN-G2",AB_package);
    SET_SYMBOL_VALUE(Qstack_instructions_count_in_g2,FIX((SI_Long)300L));
    if (Stack_instructions == UNBOUND) {
	gensymed_symbol = Stack_instructions_count_in_g2;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	Stack_instructions = the_array;
    }
    Qinstruction_description = STATIC_SYMBOL("INSTRUCTION-DESCRIPTION",
	    AB_package);
    Instruction_description_prop = Qinstruction_description;
    Qstack_instruction = STATIC_SYMBOL("STACK-INSTRUCTION",AB_package);
    string_constant = 
	    string_append2(STATIC_STRING("Not enough arguments passed to ~a.  It needed ~a and received ~a.  ~\r\n         Please report this stack evaluator internal error to Gensym software ~\r\n         support with th"),
	    STATIC_STRING("e source code of the item named in the error message."));
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Wrong argument type given to ~a.  It needed ~NT and received ");
    string_constant_2 = 
	    STATIC_STRING(".  Please report this stack evaluator internal error to Gensym ~\r\n             software support with the source code of the item named in the ~\r\n             error message.");
    string_constant_3 = 
	    STATIC_STRING("Wrong result type returned from ~a.  It should return ~NT, but ~\r\n           instead returned ");
    string_constant_4 = 
	    STATIC_STRING(".  Please report this evaluator internal error to Gensym software ~\r\n           support with the source code of the item named in the error message.");
    string_constant_5 = STATIC_STRING("op-code fetcher");
    string_constant_6 = 
	    STATIC_STRING("No stack instruction description for ~a.");
    Qbyte_code_resolver = STATIC_SYMBOL("BYTE-CODE-RESOLVER",AB_package);
    Byte_code_resolver_prop = Qbyte_code_resolver;
    if (Current_code_body_entry == UNBOUND)
	Current_code_body_entry = Nil;
    string_constant_7 = STATIC_STRING("address resolver");
    string_constant_8 = 
	    STATIC_STRING("No address resolver for stack instruction op-code ~a.");
    string_constant_9 = STATIC_STRING("Environment~%");
    string_constant_10 = STATIC_STRING("~%Constants");
    string_constant_11 = STATIC_STRING("~%");
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_12 = STATIC_STRING("~%  Inherited from base code body");
    string_constant_13 = STATIC_STRING("~%  None");
    string_constant_14 = STATIC_STRING("~%Free References");
    string_constant_15 = STATIC_STRING("~%Instructions");
    Qsystem_call = STATIC_SYMBOL("SYSTEM-CALL",AB_package);
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    Qhalt = STATIC_SYMBOL("HALT",AB_package);
    Qadd_to_action_cache = STATIC_SYMBOL("ADD-TO-ACTION-CACHE",AB_package);
    Qrestore_from_action_cache_or_branch = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH",AB_package);
    Qreset_kb = STATIC_SYMBOL("RESET-KB",AB_package);
    Maximum_byte_code_body_length_to_compile = FIX((SI_Long)5000L);
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    Qbranch_if_not_true = STATIC_SYMBOL("BRANCH-IF-NOT-TRUE",AB_package);
    Qbranch_if_known = STATIC_SYMBOL("BRANCH-IF-KNOWN",AB_package);
    Qbranch_long = STATIC_SYMBOL("BRANCH-LONG",AB_package);
    Qbranch_long_if_not_true = STATIC_SYMBOL("BRANCH-LONG-IF-NOT-TRUE",
	    AB_package);
    Qbranch_long_if_known = STATIC_SYMBOL("BRANCH-LONG-IF-KNOWN",AB_package);
    Qboolean_branch_long_if_not_true = 
	    STATIC_SYMBOL("BOOLEAN-BRANCH-LONG-IF-NOT-TRUE",AB_package);
    Qbranch_relative = STATIC_SYMBOL("BRANCH-RELATIVE",AB_package);
    Qbranch_relative_if_not_true = 
	    STATIC_SYMBOL("BRANCH-RELATIVE-IF-NOT-TRUE",AB_package);
    Qbranch_relative_if_known = STATIC_SYMBOL("BRANCH-RELATIVE-IF-KNOWN",
	    AB_package);
    Qboolean_branch_relative_if_not_true = 
	    STATIC_SYMBOL("BOOLEAN-BRANCH-RELATIVE-IF-NOT-TRUE",AB_package);
    Qcase_dispatch = STATIC_SYMBOL("CASE-DISPATCH",AB_package);
    Qopen_role_iteration_no_domain = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN",AB_package);
    Qopen_role_iteration = STATIC_SYMBOL("OPEN-ROLE-ITERATION",AB_package);
    Qserve_next_iteration_value = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qcase_dispatch,
	    Qopen_role_iteration_no_domain,Qopen_role_iteration,
	    Qserve_next_iteration_value,Qrestore_from_action_cache_or_branch);
    if (Show_stack_bytes_qm == UNBOUND)
	Show_stack_bytes_qm = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_16 = STATIC_STRING("");
    string_constant_17 = STATIC_STRING("    ");
    string_constant_18 = STATIC_STRING("   ");
    string_constant_19 = STATIC_STRING("  ");
    string_constant_20 = STATIC_STRING(" ");
    array_constant_5 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    Qfuncall_instruction = STATIC_SYMBOL("FUNCALL-INSTRUCTION",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)57344L);
    Qnumber_of_extra_stack_frame_values = 
	    STATIC_SYMBOL("NUMBER-OF-EXTRA-STACK-FRAME-VALUES",AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_extra_stack_frame_values,FIX((SI_Long)6L));
    array_constant_8 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    string_constant_21 = STATIC_STRING("Error:  (~a)");
    string_constant_22 = STATIC_STRING("~%~%~nw~%~%");
    array_constant_10 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_23 = STATIC_STRING("~%Program Counter: ~a");
    string_constant_24 = STATIC_STRING("~%Activity: ");
    string_constant_25 = STATIC_STRING("~%Within: ");
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_26 = STATIC_STRING("~%Local Names:~%");
    string_constant_27 = STATIC_STRING("  tos: ~d");
    string_constant_28 = STATIC_STRING("~%Local Names, Calling level ~a:~%");
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_inference_background_collection_g2_struct 
	    = STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Backtrace_depth_limit = FIX((SI_Long)20L);
    string_constant_29 = STATIC_STRING("~%  <- ");
    string_constant_30 = STATIC_STRING("[~a intervening function~a]");
    string_constant_31 = STATIC_STRING("s");
    string_constant_32 = STATIC_STRING("[~a intervening procedure~a]");
    string_constant_33 = STATIC_STRING("called from G2GL process ~NF");
    array_constant_11 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)42L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    Qbackward_chaining = STATIC_SYMBOL("BACKWARD-CHAINING",AB_package);
    string_constant_34 = STATIC_STRING("backward chaining for ~NF");
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    string_constant_35 = STATIC_STRING("user menu choice selection");
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    string_constant_36 = STATIC_STRING("action button selection");
    Qforward_chaining = STATIC_SYMBOL("FORWARD-CHAINING",AB_package);
    string_constant_37 = STATIC_STRING("forward chaining");
    Qscanning = STATIC_SYMBOL("SCANNING",AB_package);
    string_constant_38 = STATIC_STRING("scan interval");
    Qinitializing = STATIC_SYMBOL("INITIALIZING",AB_package);
    string_constant_39 = STATIC_STRING("initial rule invocation");
    Qfocusing = STATIC_SYMBOL("FOCUSING",AB_package);
    string_constant_40 = STATIC_STRING("focus action");
    Qinvoking = STATIC_SYMBOL("INVOKING",AB_package);
    string_constant_41 = STATIC_STRING("invoke action");
    string_constant_42 = STATIC_STRING("rule purpose not recorded");
    array_constant_15 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)31L,(SI_Long)57344L);
    Qexecute_computation_instance = 
	    STATIC_SYMBOL("EXECUTE-COMPUTATION-INSTANCE",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_computation_instance,
	    STATIC_FUNCTION(execute_computation_instance,NIL,FALSE,1,1));
    Qproc = STATIC_SYMBOL("PROC",AB_package);
    Qabort_called_code_bodies = STATIC_SYMBOL("ABORT-CALLED-CODE-BODIES",
	    AB_package);
    string_constant_43 = 
	    STATIC_STRING("Procedure aborted to break a deadlock");
    Qg2_deadlock_error = STATIC_SYMBOL("G2-DEADLOCK-ERROR",AB_package);
    Qdetect_and_break_deadlocks = 
	    STATIC_SYMBOL("DETECT-AND-BREAK-DEADLOCKS",AB_package);
    SET_SYMBOL_FUNCTION(Qdetect_and_break_deadlocks,
	    STATIC_FUNCTION(detect_and_break_deadlocks,NIL,FALSE,0,0));
    string_constant_44 = 
	    STATIC_STRING("Deadlock detected: Use detect-and-break-deadlocks to abort deadlocked procedures");
    string_constant_45 = STATIC_STRING("No deadlock detected");
    Qg2_detect_deadlocks = STATIC_SYMBOL("G2-DETECT-DEADLOCKS",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_detect_deadlocks,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_detect_deadlocks,
	    STATIC_FUNCTION(g2_detect_deadlocks,NIL,FALSE,0,0));
    Qg2_detect_and_break_deadlocks = 
	    STATIC_SYMBOL("G2-DETECT-AND-BREAK-DEADLOCKS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_detect_and_break_deadlocks,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_detect_and_break_deadlocks,
	    STATIC_FUNCTION(g2_detect_and_break_deadlocks,NIL,FALSE,0,0));
    Qautomatic_deadlock_detection_task = 
	    STATIC_SYMBOL("AUTOMATIC-DEADLOCK-DETECTION-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qautomatic_deadlock_detection_task,
	    Automatic_deadlock_detection_task);
    record_system_variable(Qautomatic_deadlock_detection_task,Qstack_utils,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qautomatic_deadlock_detection_frequency = 
	    STATIC_SYMBOL("AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qautomatic_deadlock_detection_frequency,
	    Automatic_deadlock_detection_frequency);
    record_system_variable(Qautomatic_deadlock_detection_frequency,
	    Qstack_utils,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_46 = 
	    STATIC_STRING("Trying to write a string longer than 2MB!");
    Qhandle_extend_current_text_string_error = 
	    STATIC_SYMBOL("HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_extend_current_text_string_error,
	    STATIC_FUNCTION(handle_extend_current_text_string_error,NIL,
	    FALSE,0,0));
}
