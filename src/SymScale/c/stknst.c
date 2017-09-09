/* stknst.c
 * Input file:  stack-inst.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "stknst.h"


/* PRINT-OP-AND-CODE-CONSTANT */
Object print_op_and_code_constant(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,0);
    twrite_character(FIX((SI_Long)32L));
    twrite_positive_fixnum(FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)))));
    return VALUES_1(Nil);
}

static Object string_constant;     /* ", " */

/* PRINT-OP-AND-CODE-CONSTANT-AND-TYPECODE */
Object print_op_and_code_constant_and_typecode(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,1);
    print_op_and_code_constant(pc,instructions,constants,environment);
    twrite(string_constant);
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)2L)));
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-LONG-CODE-CONSTANT */
Object print_op_and_long_code_constant(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,2);
    twrite_character(FIX((SI_Long)32L));
    twrite_positive_fixnum(long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc)));
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-RELATIVE-CODE-CONSTANT */
Object print_op_and_relative_code_constant(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,3);
    twrite_character(FIX((SI_Long)32L));
    twrite_fixnum(relative_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc)));
    return VALUES_1(Nil);
}

static Object string_constant_1;   /* " by ~a to ~a" */

/* PRINT-OP-AND-RELATIVE-CODE-CONSTANT-ADDRESS */
Object print_op_and_relative_code_constant_address(pc,instructions,
	    constants,environment)
    Object pc, instructions, constants, environment;
{
    Object relative_constant;

    x_note_fn_call(205,4);
    relative_constant = relative_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    tformat(3,string_constant_1,relative_constant,FIXNUM_ADD(pc,
	    relative_constant));
    return VALUES_1(Nil);
}

static Object string_constant_2;   /* " #~a (" */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

static Object array_constant;      /* # */

/* PRINT-OP-AND-CONSTANT */
Object print_op_and_constant(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant, gensymed_symbol, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, temp_2, entry_hash;
    SI_Long constant_index, key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,5);
    constant_index = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    constant = ISVREF(constants,constant_index);
    tformat(2,string_constant_2,FIX(constant_index));
    gensymed_symbol = constant;
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
    if (temp)
	write_evaluation_value(1,constant);
    else
	twrite(constant);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-CONSTANT-LONG */
Object print_op_and_constant_long(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, constant, gensymed_symbol, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,6);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    constant = ISVREF(constants,IFIX(constant_index));
    tformat(2,string_constant_2,constant_index);
    gensymed_symbol = constant;
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
    if (temp)
	write_evaluation_value(1,constant);
    else
	twrite(constant);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant_3;   /* "~NF" */

static Object string_constant_4;   /* ", ~a" */

/* PRINT-OP-CONSTANT-LONG-AND-CODE-CONSTANT */
Object print_op_constant_long_and_code_constant(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, constant, gensymed_symbol, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash, x2;
    SI_Long code_constant, key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,7);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    constant = ISVREF(constants,IFIX(constant_index));
    code_constant = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)3L);
    tformat(2,string_constant_2,constant_index);
    if ( !TRUEP(constant))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)8L));
    else {
	gensymed_symbol = constant;
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    write_evaluation_value(1,constant);
	else {
	    if (SIMPLE_VECTOR_P(constant) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(constant,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(constant,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		tformat(2,string_constant_3,constant);
	    else
		twrite(constant);
	}
    }
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    tformat(2,string_constant_4,FIX(code_constant));
    return VALUES_1(Nil);
}

static Object string_constant_5;   /* " #~a, " */

/* PRINT-OP-AND-ROLE-NO-DOMAIN-LONG */
Object print_op_and_role_no_domain_long(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, role;
    SI_Long code_constant;

    x_note_fn_call(205,8);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    role = ISVREF(constants,IFIX(constant_index));
    code_constant = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)3L);
    tformat(2,string_constant_5,constant_index);
    if (SYMBOLP(role))
	twrite_symbol(1,role);
    else
	print_role(role);
    tformat(2,string_constant_4,FIX(code_constant));
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* " #~a, the " */

/* PRINT-OP-AND-ROLE-LONG */
Object print_op_and_role_long(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, role;

    x_note_fn_call(205,9);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    role = ISVREF(constants,IFIX(constant_index));
    tformat(2,string_constant_6,constant_index);
    print_role(role);
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* ", ~a arguments" */

/* PRINT-OP-ROLE-LONG-AND-ARG-COUNT */
Object print_op_role_long_and_arg_count(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, role;
    SI_Long arg_count;

    x_note_fn_call(205,10);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    role = ISVREF(constants,IFIX(constant_index));
    arg_count = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)3L);
    tformat(2,string_constant_6,constant_index);
    print_role(role);
    tformat(2,string_constant_7,FIX(arg_count));
    return VALUES_1(Nil);
}

static Object Qerror_unused_index;  /* error-unused-index */

/* PRINT-FUNCALL-EVALUATOR */
Object print_funcall_evaluator(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object function_description_qm, instruction_name;

    x_note_fn_call(205,11);
    function_description_qm = ISVREF(Funcalled_evaluator_array,
	    UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc))));
    instruction_name = function_description_qm ? 
	    ISVREF(function_description_qm,(SI_Long)1L) : Qerror_unused_index;
    twrite_character(FIX((SI_Long)32L));
    twrite_symbol(1,instruction_name);
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "internal out-of-line evaluator ~a" */

/* PPRINT-FUNCALL-EVALUATOR */
Object pprint_funcall_evaluator(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, description_qm, pprinter_qm, argument_count;
    SI_Long evaluator_number;

    x_note_fn_call(205,12);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    evaluator_number = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    description_qm = ISVREF(Funcalled_evaluator_array,evaluator_number);
    pprinter_qm = description_qm ? ISVREF(description_qm,(SI_Long)11L) : Nil;
    argument_count = description_qm ? length(ISVREF(description_qm,
	    (SI_Long)4L)) : Nil;
    if ( !TRUEP(description_qm))
	tformat(2,string_constant_8,FIX(evaluator_number));
    else if (pprinter_qm)
	inline_funcall_6(pprinter_qm,description_qm,pc,byte_code_body,
		constant_vector,stack,top_of_stack);
    else if (IFIX(argument_count) == (SI_Long)2L)
	pprint_infix_evaluator(description_qm,pc,byte_code_body,
		constant_vector,stack,top_of_stack);
    else
	pprint_functional_evaluator(description_qm,pc,byte_code_body,
		constant_vector,stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PRINT-FUNCALLED-INSTRUCTION */
Object print_funcalled_instruction(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object funcalled_instruction_description_qm, printer_qm, instruction_name;
    SI_Long funcalled_instruction_number;

    x_note_fn_call(205,13);
    funcalled_instruction_number = UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)));
    funcalled_instruction_description_qm = ISVREF(Funcalled_instructions,
	    funcalled_instruction_number);
    printer_qm = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)5L) : Qnil;
    instruction_name = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)0L) : 
	    Qerror_unused_index;
    twrite_character(FIX((SI_Long)32L));
    if (printer_qm)
	FUNCALL_0(SYMBOL_FUNCTION(printer_qm));
    else
	twrite_symbol(1,instruction_name);
    return VALUES_1(Nil);
}

static Object string_constant_9;   /* "internal out-of-line instruction ~a" */

/* PPRINT-FUNCALLED-INSTRUCTION */
Object pprint_funcalled_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, funcalled_instruction_description_qm, pprinter_qm;
    SI_Long funcalled_instruction_number;

    x_note_fn_call(205,14);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    funcalled_instruction_number = UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)));
    funcalled_instruction_description_qm = ISVREF(Funcalled_instructions,
	    funcalled_instruction_number);
    pprinter_qm = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)7L) : Qnil;
    if (pprinter_qm)
	inline_funcall_6(pprinter_qm,funcalled_instruction_description_qm,
		pc,byte_code_body,constant_vector,stack,top_of_stack);
    else
	tformat(2,string_constant_9,FIX(funcalled_instruction_number));
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* " (~D arguments, ~D results)" */

/* PRINT-FUNCALLED-INSTRUCTION-N */
Object print_funcalled_instruction_n(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object funcalled_instruction_description_qm, printer_qm, instruction_name;
    Object arg_count;
    SI_Long funcalled_instruction_number, result_count;

    x_note_fn_call(205,15);
    funcalled_instruction_number = UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)));
    funcalled_instruction_description_qm = ISVREF(Funcalled_instructions,
	    funcalled_instruction_number);
    printer_qm = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)5L) : Qnil;
    instruction_name = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)0L) : 
	    Qerror_unused_index;
    arg_count = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)3L));
    result_count = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)2L);
    twrite_character(FIX((SI_Long)32L));
    if (printer_qm)
	FUNCALL_0(SYMBOL_FUNCTION(printer_qm));
    else
	twrite_symbol(1,instruction_name);
    tformat(3,string_constant_10,arg_count,FIX(result_count));
    return VALUES_1(Nil);
}

/* PPRINT-FUNCALLED-INSTRUCTION-N */
Object pprint_funcalled_instruction_n(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, funcalled_instruction_description_qm, pprinter_qm;
    Object arg_count;
    SI_Long funcalled_instruction_number, result_count;

    x_note_fn_call(205,16);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    funcalled_instruction_number = UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)));
    funcalled_instruction_description_qm = ISVREF(Funcalled_instructions,
	    funcalled_instruction_number);
    pprinter_qm = funcalled_instruction_description_qm ? 
	    ISVREF(funcalled_instruction_description_qm,(SI_Long)7L) : Qnil;
    arg_count = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)3L));
    result_count = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)2L);
    if (pprinter_qm)
	inline_funcall_8(pprinter_qm,funcalled_instruction_description_qm,
		pc,byte_code_body,constant_vector,stack,top_of_stack,
		arg_count,FIX(result_count));
    else
	tformat(2,string_constant_9,FIX(funcalled_instruction_number));
    return VALUES_1(Nil);
}

static Object Qvar_spot;           /* var-spot */

/* PRINT-OP-AND-SURROUNDING-LOCAL-VAR */
Object print_op_and_surrounding_local_var(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    Object var_spot_index, var_spot;

    x_note_fn_call(205,17);
    var_spot_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    var_spot = gensym_list_2(Qvar_spot,var_spot_index);
    twrite_character(FIX((SI_Long)32L));
    print_var_spot_for_stack(2,var_spot,environment);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-SURROUNDING-LOCAL-VAR-AND-TYPECODE */
Object print_op_and_surrounding_local_var_and_typecode(pc,instructions,
	    constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,18);
    print_op_and_surrounding_local_var(pc,instructions,constants,environment);
    twrite(string_constant);
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)3L)));
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-LOCAL-VAR */
Object print_op_and_local_var(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object var_spot;
    SI_Long second_new_value;

    x_note_fn_call(205,19);
    var_spot = gensym_list_2(Qvar_spot,FIX((SI_Long)0L));
    twrite_character(FIX((SI_Long)32L));
    second_new_value = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    M_SECOND(var_spot) = FIX(second_new_value);
    print_var_spot_for_stack(2,var_spot,environment);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

/* PRINT-OP-AND-LOCAL-VAR-AND-TYPECODE */
Object print_op_and_local_var_and_typecode(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,20);
    print_op_and_local_var(pc,instructions,constants,environment);
    twrite(string_constant);
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)2L)));
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* ", base = ~a, highest = ~a, index->address = " */

static Object string_constant_12;  /* "~a->~a, " */

static Object string_constant_13;  /* "else->~a" */

/* PRINT-CASE-DISPATCH */
Object print_case_dispatch(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object table_base, table_length, else_address;
    SI_Long address_table_pc, index_1, ab_loop_repeat_;

    x_note_fn_call(205,21);
    table_base = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    table_length = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)3L));
    else_address = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)5L));
    tformat(3,string_constant_11,table_base,
	    FIXNUM_SUB1(FIXNUM_ADD(table_base,table_length)));
    address_table_pc = IFIX(pc) + (SI_Long)7L;
    index_1 = IFIX(table_base);
    ab_loop_repeat_ = IFIX(table_length);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    tformat(3,string_constant_12,FIX(index_1),
	    long_code_constant_in_byte_vector(instructions,
	    FIX(address_table_pc + (index_1 - IFIX(table_base)) * 
	    (SI_Long)2L)));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    tformat(2,string_constant_13,else_address);
    return VALUES_1(Nil);
}

static Object string_constant_14;  /* ", argument-count = ~a, values-count = ~a" */

/* PRINT-CALL-STACK-INSTRUCTION */
Object print_call_stack_instruction(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,22);
    tformat(3,string_constant_14,FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)))),FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(pc) + (SI_Long)2L)));
    return VALUES_1(Nil);
}

static Object string_constant_15;  /* ", argument-count = ~a" */

/* PRINT-CALL-FUNCTION-STACK-INSTRUCTION */
Object print_call_function_stack_instruction(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,23);
    tformat(2,string_constant_15,FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)))));
    return VALUES_1(Nil);
}

static Object string_constant_16;  /* " out ~a code bodies to entry point #~a" */

/* PRINT-STACK-JUMP */
Object print_stack_jump(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,24);
    tformat(3,string_constant_16,
	    long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc)),
	    long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) + 
	    (SI_Long)3L)));
    return VALUES_1(Nil);
}

static Object array_constant_2;    /* # */

static Object string_constant_17;  /* ", branch to ~a if no values" */

/* PRINT-OPEN-ROLE-NO-DOMAIN-ITERATION */
Object print_open_role_no_domain_iteration(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, role;

    x_note_fn_call(205,25);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    role = ISVREF(constants,IFIX(constant_index));
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)9L));
    if (SYMBOLP(role)) {
	twrite_character(FIX((SI_Long)32L));
	twrite_symbol(1,role);
    }
    else
	print_role(role);
    tformat(2,string_constant_17,
	    long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) + 
	    (SI_Long)3L)));
    return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object string_constant_18;  /* ", for there exists" */

/* PRINT-OPEN-ROLE-ITERATION */
Object print_open_role_iteration(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, role;
    SI_Long domain_count;

    x_note_fn_call(205,26);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    role = ISVREF(constants,IFIX(constant_index));
    domain_count = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)5L);
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)10L));
    print_role(role);
    tformat(2,string_constant_17,
	    long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) + 
	    (SI_Long)3L)));
    if (domain_count == (SI_Long)0L)
	tformat(1,string_constant_18);
    return VALUES_1(Nil);
}

/* PRINT-SERVE-NEXT-ITERATION-VALUE */
Object print_serve_next_iteration_value(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,27);
    tformat(2,string_constant_17,
	    long_code_constant_in_byte_vector(instructions,FIXNUM_ADD1(pc)));
    return VALUES_1(Nil);
}

static Object string_constant_19;  /* " #~a, argument-count = ~a" */

/* PRINT-STACK-CALL-CODE-BODY */
Object print_stack_call_code_body(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    x_note_fn_call(205,28);
    tformat(3,string_constant_19,FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)))),FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(pc) + (SI_Long)2L)));
    return VALUES_1(Nil);
}

static Object string_constant_20;  /* " #~a, ~NT" */

/* PRINT-OP-AND-TYPE-LONG */
Object print_op_and_type_long(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object index_1, type;

    x_note_fn_call(205,29);
    index_1 = long_code_constant_in_byte_vector(instructions,FIXNUM_ADD1(pc));
    type = ISVREF(constants,IFIX(index_1));
    tformat(3,string_constant_20,index_1,type);
    return VALUES_1(Nil);
}

static Object array_constant_4;    /* # */

static Object string_constant_21;  /* ", ~a elements" */

/* PRINT-BLOCK-COPY */
Object print_block_copy(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object var_spot;
    SI_Long count_1;

    x_note_fn_call(205,30);
    var_spot = gensym_list_2(Qvar_spot,
	    long_code_constant_in_byte_vector(instructions,FIXNUM_ADD1(pc)));
    count_1 = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)3L);
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)13L));
    print_var_spot_for_stack(2,var_spot,environment);
    tformat(2,string_constant_21,FIX(count_1));
    return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object string_constant_22;  /* " starting at " */

/* PRINT-ACTION-CACHE-AND-INDICES */
Object print_action_cache_and_indices(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object cache, count_1, target, var_spot;

    x_note_fn_call(205,31);
    cache = long_code_constant_in_byte_vector(instructions,FIXNUM_ADD1(pc));
    count_1 = long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) 
	    + (SI_Long)3L));
    target = long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) + 
	    (SI_Long)5L));
    var_spot = gensym_list_2(Qvar_spot,cache);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)1L));
    print_var_spot_for_stack(2,var_spot,environment);
    tformat(2,string_constant_21,count_1);
    if (IFIX(count_1) > (SI_Long)0L) {
	tformat(1,string_constant_22);
	M_SECOND(var_spot) = target;
	print_var_spot_for_stack(2,var_spot,environment);
    }
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

static Object string_constant_23;  /* ", branch to ~a if empty" */

/* PRINT-ACTION-CACHE-INDICES-AND-ADDRESS */
Object print_action_cache_indices_and_address(pc,instructions,constants,
	    environment)
    Object pc, instructions, constants, environment;
{
    Object cache, count_1, target, address, var_spot;

    x_note_fn_call(205,32);
    cache = long_code_constant_in_byte_vector(instructions,FIXNUM_ADD1(pc));
    count_1 = long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) 
	    + (SI_Long)3L));
    target = long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) + 
	    (SI_Long)5L));
    address = long_code_constant_in_byte_vector(instructions,FIX(IFIX(pc) 
	    + (SI_Long)7L));
    var_spot = gensym_list_2(Qvar_spot,cache);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)1L));
    print_var_spot_for_stack(2,var_spot,environment);
    tformat(2,string_constant_21,count_1);
    if (IFIX(count_1) > (SI_Long)0L) {
	tformat(1,string_constant_22);
	M_SECOND(var_spot) = target;
	print_var_spot_for_stack(2,var_spot,environment);
    }
    tformat(2,string_constant_23,address);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

/* PRINT-CACHED-ITEM */
Object print_cached_item(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, constant, gensymed_symbol, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash, x2;
    SI_Long code_constant, key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,33);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    constant = ISVREF(constants,IFIX(constant_index));
    code_constant = UBYTE_8_ISAREF_1(instructions,IFIX(pc) + (SI_Long)3L);
    tformat(2,string_constant_2,constant_index);
    if ( !TRUEP(constant))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)8L));
    else {
	gensymed_symbol = constant;
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    write_evaluation_value(1,constant);
	else if (CONSP(constant))
	    twrite(M_CAR(constant));
	else {
	    if (SIMPLE_VECTOR_P(constant) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(constant,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(constant,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		tformat(2,string_constant_3,constant);
	    else
		twrite(constant);
	}
    }
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    tformat(2,string_constant_4,FIX(code_constant));
    return VALUES_1(Nil);
}

/* PRINT-CACHED-ATTRIBUTE */
Object print_cached_attribute(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object constant_index, constant, gensymed_symbol, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,34);
    constant_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    constant = ISVREF(constants,IFIX(constant_index));
    tformat(2,string_constant_2,constant_index);
    gensymed_symbol = constant;
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
    if (temp)
	write_evaluation_value(1,constant);
    else if (CONSP(constant))
	twrite(M_CAR(constant));
    else
	twrite(constant);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_6;    /* # */

/* PPRINT-BRANCH-INSTRUCTION */
Object pprint_branch_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,35);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX(UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter))),T);
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-LONG-INSTRUCTION */
Object pprint_branch_long_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,36);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX((UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))),T);
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-RELATIVE-INSTRUCTION */
Object pprint_branch_relative_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,37);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX(IFIX(pc) + 
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) - (SI_Long)128L)),T);
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

/* PPRINT-BRANCH-IF-NOT-TRUE-INSTRUCTION */
Object pprint_branch_if_not_true_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,38);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX(UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter))),T);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)14L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-LONG-IF-NOT-TRUE-INSTRUCTION */
Object pprint_branch_long_if_not_true_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,39);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX((UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))),T);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)14L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-RELATIVE-IF-NOT-TRUE-INSTRUCTION */
Object pprint_branch_relative_if_not_true_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,40);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)10L));
    write_evaluation_value(2,FIX(IFIX(pc) + 
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) - (SI_Long)128L)),T);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)14L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object string_constant_24;  /* "branch if known (~a) to ~a" */

static Object string_constant_25;  /* "known" */

static Object string_constant_26;  /* "unknown" */

/* PPRINT-BRANCH-IF-KNOWN-INSTRUCTION */
Object pprint_branch_if_known_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,41);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    tformat(3,string_constant_24,Stack_expiration ? string_constant_25 : 
	    string_constant_26,FIX(UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter))));
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-LONG-IF-KNOWN-INSTRUCTION */
Object pprint_branch_long_if_known_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,42);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    tformat(3,string_constant_24,Stack_expiration ? string_constant_25 : 
	    string_constant_26,FIX((UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))));
    return VALUES_1(Nil);
}

/* PPRINT-BRANCH-RELATIVE-IF-KNOWN-INSTRUCTION */
Object pprint_branch_relative_if_known_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,43);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    tformat(3,string_constant_24,Stack_expiration ? string_constant_25 : 
	    string_constant_26,FIX(IFIX(pc) + 
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) - (SI_Long)128L)));
    return VALUES_1(Nil);
}

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

/* PPRINT-PUSH-FROM-STACK-ARG-INSTRUCTION */
Object pprint_push_from_stack_arg_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,44);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)25L));
    write_evaluation_value(2,FIX(UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter))),T);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instruction_vector,IFIX(pc) + 
	    (SI_Long)2L)));
    return VALUES_1(Nil);
}

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

/* PPRINT-CASE-DISPATCH-INSTRUCTION */
Object pprint_case_dispatch_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, table_base, table_length, else_address;
    SI_Long address_table_pc, index_1, ab_loop_repeat_;

    x_note_fn_call(205,45);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    table_base = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    table_length = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)3L));
    else_address = long_code_constant_in_byte_vector(instructions,
	    FIX(IFIX(pc) + (SI_Long)5L));
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)6L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)15L));
    address_table_pc = IFIX(pc) + (SI_Long)7L;
    index_1 = IFIX(table_base);
    ab_loop_repeat_ = IFIX(table_length);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    tformat(3,string_constant_12,FIX(index_1),
	    long_code_constant_in_byte_vector(instructions,
	    FIX(address_table_pc + (index_1 - IFIX(table_base)) * 
	    (SI_Long)2L)));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    tformat(2,string_constant_13,else_address);
    return VALUES_1(Nil);
}

static Object array_constant_12;   /* # */

static Object string_constant_27;  /* " is a ~NT" */

/* PPRINT-TYPE-CHECK */
Object pprint_type_check(type_spec,stack,top_of_stack)
    Object type_spec, stack, top_of_stack;
{
    x_note_fn_call(205,46);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_27,type_spec);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-TRUTH-VALUE-INSTRUCTION */
Object pprint_type_check_truth_value_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,47);
    pprint_type_check(Qtruth_value,stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-SYMBOL-INSTRUCTION */
Object pprint_type_check_symbol_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,48);
    pprint_type_check(Qsymbol,stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object Qtext;               /* text */

/* PPRINT-TYPE-CHECK-TEXT-INSTRUCTION */
Object pprint_type_check_text_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,49);
    pprint_type_check(Qtext,stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-QUANTITY-INSTRUCTION */
Object pprint_type_check_quantity_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,50);
    pprint_type_check(Qnumber,stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-INTEGER-INSTRUCTION */
Object pprint_type_check_integer_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,51);
    pprint_type_check(Qinteger,stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-FLOAT-INSTRUCTION */
Object pprint_type_check_float_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,52);
    pprint_type_check(Qfloat,stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object string_constant_28;  /* " is a ~a" */

/* PPRINT-TYPE-CHECK-CLASS-INSTRUCTION */
Object pprint_type_check_class_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,53);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_28,ISVREF(constant_vector,
	    UBYTE_8_ISAREF_1(instruction_vector,IFIX(stack_program_counter))));
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-CLASS-LONG-INSTRUCTION */
Object pprint_type_check_class_long_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,54);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_28,ISVREF(constant_vector,
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))));
    return VALUES_1(Nil);
}

static Object Qitem_or_datum;      /* item-or-datum */

/* PPRINT-TYPE-CHECK-ITEM-OR-DATUM-INSTRUCTION */
Object pprint_type_check_item_or_datum_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,55);
    pprint_type_check(Qitem_or_datum,stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* PPRINT-POP-INTO-SURROUNDING-LOCAL-VAR-INSTRUCTION */
Object pprint_pop_into_surrounding_local_var_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, environment, var_spot_index, var_spot;

    x_note_fn_call(205,56);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    environment = ISVREF(byte_code_body,(SI_Long)4L);
    var_spot_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    var_spot = gensym_list_2(Qvar_spot,var_spot_index);
    twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)7L));
    print_var_spot_for_stack(2,var_spot,environment);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)3L)));
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)3L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

/* PPRINT-POP-INTO-LOCAL-VAR-INSTRUCTION */
Object pprint_pop_into_local_var_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, environment, var_spot;
    SI_Long second_new_value;

    x_note_fn_call(205,57);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    environment = ISVREF(byte_code_body,(SI_Long)4L);
    var_spot = gensym_list_2(Qvar_spot,FIX((SI_Long)0L));
    second_new_value = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    M_SECOND(var_spot) = FIX(second_new_value);
    twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)7L));
    print_var_spot_for_stack(2,var_spot,environment);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)2L)));
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)3L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

/* PPRINT-PUSH-FROM-SURROUNDING-LOCAL-VAR-INSTRUCTION */
Object pprint_push_from_surrounding_local_var_instruction(pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, environment, var_spot_index, var_spot;

    x_note_fn_call(205,58);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    environment = ISVREF(byte_code_body,(SI_Long)4L);
    var_spot_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    var_spot = gensym_list_2(Qvar_spot,var_spot_index);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    print_var_spot_for_stack(2,var_spot,environment);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)3L)));
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

static Object array_constant_16;   /* # */

/* PPRINT-MOVE-FROM-SURROUNDING-LOCAL-VAR-INSTRUCTION */
Object pprint_move_from_surrounding_local_var_instruction(pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, environment, var_spot_index, var_spot;

    x_note_fn_call(205,59);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    environment = ISVREF(byte_code_body,(SI_Long)4L);
    var_spot_index = long_code_constant_in_byte_vector(instructions,
	    FIXNUM_ADD1(pc));
    var_spot = gensym_list_2(Qvar_spot,var_spot_index);
    twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)16L));
    print_var_spot_for_stack(2,var_spot,environment);
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

/* PPRINT-PUSH-FROM-LOCAL-VAR-INSTRUCTION */
Object pprint_push_from_local_var_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instructions, environment, var_spot;
    SI_Long second_new_value;

    x_note_fn_call(205,60);
    instructions = ISVREF(byte_code_body,(SI_Long)2L);
    environment = ISVREF(byte_code_body,(SI_Long)4L);
    var_spot = gensym_list_2(Qvar_spot,FIX((SI_Long)0L));
    second_new_value = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    M_SECOND(var_spot) = FIX(second_new_value);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    print_var_spot_for_stack(2,var_spot,environment);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    twrite_typecode(FIX(UBYTE_8_ISAREF_1(instructions,IFIX(pc) + 
	    (SI_Long)2L)));
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(Nil);
}

static Object string_constant_29;  /* "~a" */

/* PPRINT-NAME-REFERENCE-INSTRUCTION */
Object pprint_name_reference_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,61);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    tformat(2,string_constant_29,ISVREF(constant_vector,
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))));
    return VALUES_1(Nil);
}

static Object array_constant_17;   /* # */

/* PPRINT-EVALUATE-ROLE-INSTRUCTION */
Object pprint_evaluate_role_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, role, index_1;
    Object first_arg_qm;
    SI_Long role_index, arg_count;

    x_note_fn_call(205,62);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    role_index = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    arg_count = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)2L);
    role = ISVREF(constant_vector,role_index);
    twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)10L));
    print_role(role);
    twrite_character(FIX((SI_Long)32L));
    index_1 = FIX((SI_Long)1L);
    first_arg_qm = T;
  next_loop:
    if (IFIX(index_1) > arg_count)
	goto end_loop;
    if (first_arg_qm)
	first_arg_qm = Nil;
    else
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_stack_argument(index_1,FIX(arg_count),stack,top_of_stack);
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* PPRINT-EVALUATE-ROLE-WITH-NO-DOMAIN-INSTRUCTION */
Object pprint_evaluate_role_with_no_domain_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, role;
    SI_Long role_index;

    x_note_fn_call(205,63);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    role_index = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    role = ISVREF(constant_vector,role_index);
    twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)10L));
    print_role(role);
    return VALUES_1(Nil);
}

static Object array_constant_18;   /* # */

/* PPRINT-PARAMETER-VALUE-INSTRUCTION */
Object pprint_parameter_value_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,64);
    twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)19L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_19;   /* # */

/* PPRINT-COERCE-INTEGER-TO-FLOAT-INSTRUCTION */
Object pprint_coerce_integer_to_float_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,65);
    twrite_beginning_of_wide_string(array_constant_19,FIX((SI_Long)24L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_20;   /* # */

/* PPRINT-COERCE-QUANTITY-TO-FLOAT-INSTRUCTION */
Object pprint_coerce_quantity_to_float_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,66);
    twrite_beginning_of_wide_string(array_constant_20,FIX((SI_Long)25L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_21;   /* # */

/* PPRINT-NOT-INSTRUCTION */
Object pprint_not_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,67);
    twrite_beginning_of_wide_string(array_constant_21,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_22;   /* # */

/* PPRINT-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE-INSTRUCTION */
Object pprint_attribute_frame_or_place_reference_instruction(pc,
	    byte_code_body,constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,68);
    twrite_beginning_of_wide_string(array_constant_17,FIX((SI_Long)10L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_22,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object string_constant_30;  /* "fetch the ~a of " */

/* PPRINT-ATTRIBUTE-VALUE-INSTRUCTION */
Object pprint_attribute_value_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;

    x_note_fn_call(205,69);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    tformat(2,string_constant_30,ISVREF(constant_vector,
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)))));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_23;   /* # */

static Object string_constant_31;  /* " at location ~a" */

/* PPRINT-CACHED-ATTRIBUTE-VALUE-INSTRUCTION */
Object pprint_cached_attribute_value_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, attribute_index_or_cons;

    x_note_fn_call(205,70);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    attribute_index_or_cons = ISVREF(constant_vector,
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter))));
    if (CONSP(attribute_index_or_cons)) {
	tformat(2,string_constant_30,M_CAR(attribute_index_or_cons));
	write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
		top_of_stack);
    }
    else {
	twrite_beginning_of_wide_string(array_constant_23,FIX((SI_Long)23L));
	write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
		top_of_stack);
	tformat(2,string_constant_31,attribute_index_or_cons);
    }
    return VALUES_1(Nil);
}

static Object array_constant_24;   /* # */

/* PPRINT-RETURN-VALUES-INSTRUCTION */
Object pprint_return_values_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, index_1, first_arg_qm;
    SI_Long arg_count;

    x_note_fn_call(205,71);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    arg_count = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter));
    twrite_beginning_of_wide_string(array_constant_24,FIX((SI_Long)7L));
    index_1 = FIX((SI_Long)1L);
    first_arg_qm = T;
  next_loop:
    if (IFIX(index_1) > arg_count)
	goto end_loop;
    if (first_arg_qm)
	first_arg_qm = Nil;
    else
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_stack_argument(index_1,FIX(arg_count),stack,top_of_stack);
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object array_constant_25;   /* # */

/* PPRINT-SIGNAL-ERROR-INSTRUCTION */
Object pprint_signal_error_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,72);
    twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)7L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-SIGNAL-ERROR-NEW-INSTRUCTION */
Object pprint_signal_error_new_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,73);
    twrite_beginning_of_wide_string(array_constant_25,FIX((SI_Long)7L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

static Object array_constant_28;   /* # */

/* PPRINT-CALL-INSTRUCTION */
Object pprint_call_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, index_1, first_arg_qm;
    SI_Long proc_arg_count, stack_arg_count;

    x_note_fn_call(205,74);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    proc_arg_count = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter));
    stack_arg_count = proc_arg_count + (SI_Long)1L;
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)1L),FIX(stack_arg_count),stack,
	    top_of_stack);
    twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)2L));
    index_1 = FIX((SI_Long)2L);
    first_arg_qm = T;
  next_loop:
    if (IFIX(index_1) > stack_arg_count)
	goto end_loop;
    if (first_arg_qm)
	first_arg_qm = Nil;
    else
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_stack_argument(index_1,FIX(stack_arg_count),stack,top_of_stack);
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_28,FIX((SI_Long)2L));
    return VALUES_1(Nil);
}

static Object array_constant_29;   /* # */

/* PPRINT-CALL-RPC-INSTRUCTION */
Object pprint_call_rpc_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, index_1, first_arg_qm;
    SI_Long proc_arg_count, stack_arg_count;

    x_note_fn_call(205,75);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    proc_arg_count = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter));
    stack_arg_count = proc_arg_count + (SI_Long)2L;
    twrite_beginning_of_wide_string(array_constant_26,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)1L),FIX(stack_arg_count),stack,
	    top_of_stack);
    twrite_beginning_of_wide_string(array_constant_27,FIX((SI_Long)2L));
    index_1 = FIX((SI_Long)3L);
    first_arg_qm = T;
  next_loop:
    if (IFIX(index_1) > stack_arg_count)
	goto end_loop;
    if (first_arg_qm)
	first_arg_qm = Nil;
    else
	twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
    write_stack_argument(index_1,FIX(stack_arg_count),stack,top_of_stack);
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:;
    twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)9L));
    write_stack_argument(FIX((SI_Long)2L),FIX(stack_arg_count),stack,
	    top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_30;   /* # */

/* PPRINT-ALLOW-OTHER-PROCESSING-INSTRUCTION */
Object pprint_allow_other_processing_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,76);
    twrite_beginning_of_wide_string(array_constant_30,FIX((SI_Long)22L));
    return VALUES_1(Nil);
}

static Object array_constant_31;   /* # */

static Object string_constant_32;  /* ", branch to ~a if none" */

/* PPRINT-OPEN-ROLE-ITERATION-NO-DOMAIN-INSTRUCTION */
Object pprint_open_role_iteration_no_domain_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, role;
    SI_Long role_index, branch_address;

    x_note_fn_call(205,77);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    role_index = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    role = ISVREF(constant_vector,role_index);
    branch_address = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)2L) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)3L);
    twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)30L));
    if (SYMBOLP(role))
	twrite_symbol(1,role);
    else
	print_role(role);
    tformat(2,string_constant_32,FIX(branch_address));
    return VALUES_1(Nil);
}

/* PPRINT-OPEN-ROLE-ITERATION-INSTRUCTION */
Object pprint_open_role_iteration_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, role;
    SI_Long role_index, branch_address, domain_count;

    x_note_fn_call(205,78);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    role_index = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    role = ISVREF(constant_vector,role_index);
    branch_address = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)2L) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)3L);
    domain_count = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter) + (SI_Long)4L);
    twrite_beginning_of_wide_string(array_constant_31,FIX((SI_Long)30L));
    print_role(role);
    twrite_character(FIX((SI_Long)32L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_32,FIX(branch_address));
    if (domain_count == (SI_Long)0L)
	tformat(1,string_constant_18);
    return VALUES_1(Nil);
}

static Object array_constant_32;   /* # */

/* PPRINT-SERVE-NEXT-ITERATION-VALUE-INSTRUCTION */
Object pprint_serve_next_iteration_value_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter;
    SI_Long branch_address;

    x_note_fn_call(205,79);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    branch_address = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    twrite_beginning_of_wide_string(array_constant_32,FIX((SI_Long)24L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_32,FIX(branch_address));
    return VALUES_1(Nil);
}

static Object string_constant_33;  /* " is an item" */

/* PPRINT-TYPE-CHECK-ITEM-INSTRUCTION */
Object pprint_type_check_item_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,80);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(1,string_constant_33);
    return VALUES_1(Nil);
}

/* PPRINT-FETCH-VALUE-OF */
Object pprint_fetch_value_of(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,81);
    twrite_beginning_of_wide_string(array_constant_18,FIX((SI_Long)19L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_33;   /* # */

/* PPRINT-AND-INSTRUCTION */
Object pprint_and_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,82);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_34;   /* # */

/* PPRINT-OR-INSTRUCTION */
Object pprint_or_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,83);
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_34,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_35;   /* # */

static Object Qseconds;            /* seconds */

/* PPRINT-WAIT-FOR-INTERVAL-INSTRUCTION */
Object pprint_wait_for_interval_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object wait_interval_qm;
    char stack_args_ok_qm;

    x_note_fn_call(205,84);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    wait_interval_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack)) 
	    : Qnil;
    twrite_beginning_of_wide_string(array_constant_35,FIX((SI_Long)9L));
    if (wait_interval_qm && (FIXNUMP(wait_interval_qm) || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(wait_interval_qm) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wait_interval_qm)) == 
	    (SI_Long)1L || INLINE_LONG_VECTOR_P(wait_interval_qm) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wait_interval_qm)) == (SI_Long)1L))
	print_constant(2,evaluation_quantity_value(wait_interval_qm),Qseconds);
    else
	write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,
		top_of_stack);
    return VALUES_1(Nil);
}

/* PPRINT-TYPE-CHECK-INSTRUCTION */
Object pprint_type_check_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, type_spec;
    SI_Long type_spec_index;

    x_note_fn_call(205,85);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    type_spec_index = (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter)));
    type_spec = ISVREF(constant_vector,type_spec_index);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    tformat(2,string_constant_27,type_spec);
    return VALUES_1(Nil);
}

/* PPRINT-CALL-FUNCTION-INSTRUCTION */
Object pprint_call_function_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, function;
    SI_Long stack_frame_base, nargs;

    x_note_fn_call(205,86);
    stack_frame_base = IFIX(FIXNUM_ADD(top_of_stack,
	    Number_of_extra_stack_frame_values)) + (SI_Long)2L;
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    nargs = UBYTE_8_ISAREF_1(instruction_vector,IFIX(stack_program_counter));
    function = ISVREF(stack,IFIX(top_of_stack));
    write_called_function_and_arguments(4,stack,FIX(stack_frame_base),
	    FIX(nargs),function);
    return VALUES_1(Nil);
}

static Object array_constant_36;   /* # */

/* PPRINT-RETURN-FROM-FUNCTION-INSTRUCTION */
Object pprint_return_from_function_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,87);
    twrite_beginning_of_wide_string(array_constant_36,FIX((SI_Long)22L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_37;   /* # */

/* PPRINT-SYSTEM-PROCEDURE-INSTRUCTION */
Object pprint_system_procedure_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,88);
    twrite_beginning_of_wide_string(array_constant_37,FIX((SI_Long)26L));
    return VALUES_1(Nil);
}

static Object Qinput;              /* input */

static Object array_constant_38;   /* # */

static Object Qconnection;         /* connection */

static Object string_constant_34;  /* "of class ~a " */

static Object array_constant_39;   /* # */

static Object array_constant_40;   /* # */

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

static Object array_constant_43;   /* # */

static Object array_constant_44;   /* # */

static Object array_constant_45;   /* # */

static Object string_constant_35;  /* "~a " */

static Object array_constant_46;   /* # */

/* PPRINT-CREATE-CONNECTION-INSTRUCTION */
Object pprint_create_connection_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object class_1, end_1_item, make_new_stub_1_qm, side_1_qm, position_1_qm;
    Object portname_1_qm, evaluation_value, end_2_item_qm, make_new_stub_2_qm;
    Object side_2_qm, position_2_qm, portname_2_qm, style_qm, direction_qm;
    Object vertices_list_or_constant_index_qm, portname_1_qm_temp;
    Object position_1_qm_temp, side_1_qm_temp, make_new_stub_1_qm_temp;
    Object end_1_item_temp, index_1, ab_loop_list_;

    x_note_fn_call(205,89);
    class_1 = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)13L);
    end_1_item = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)12L);
    make_new_stub_1_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)11L);
    side_1_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)10L);
    position_1_qm = evaluation_value_value(ISVREF(stack,IFIX(top_of_stack) 
	    - (SI_Long)9L));
    portname_1_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)8L);
    evaluation_value = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)7L);
    end_2_item_qm = evaluation_value && SYMBOLP(evaluation_value) ? 
	    ISVREF(stack,IFIX(top_of_stack) - (SI_Long)7L) : ISVREF(stack,
	    IFIX(top_of_stack) - (SI_Long)7L);
    make_new_stub_2_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)6L);
    side_2_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)5L);
    position_2_qm = evaluation_value_value(ISVREF(stack,IFIX(top_of_stack) 
	    - (SI_Long)4L));
    portname_2_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)3L);
    style_qm = ISVREF(stack,IFIX(top_of_stack) - (SI_Long)2L);
    direction_qm = ISVREF(stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    vertices_list_or_constant_index_qm = ISVREF(stack,IFIX(top_of_stack));
    if (position_1_qm)
	position_1_qm = l_round(position_1_qm,_);
    if (position_2_qm)
	position_2_qm = l_round(position_2_qm,_);
    if (vertices_list_or_constant_index_qm && 
	    SYMBOLP(vertices_list_or_constant_index_qm));
    else if (FIXNUMP(vertices_list_or_constant_index_qm))
	vertices_list_or_constant_index_qm = ISVREF(constant_vector,
		IFIX(vertices_list_or_constant_index_qm));
    if (EQ(direction_qm,Qinput)) {
	portname_1_qm_temp = portname_2_qm;
	position_1_qm_temp = position_2_qm;
	side_1_qm_temp = side_2_qm;
	make_new_stub_1_qm_temp = make_new_stub_2_qm;
	end_1_item_temp = end_2_item_qm;
	portname_2_qm = portname_1_qm;
	portname_1_qm = portname_1_qm_temp;
	position_2_qm = position_1_qm;
	position_1_qm = position_1_qm_temp;
	side_2_qm = side_1_qm;
	side_1_qm = side_1_qm_temp;
	make_new_stub_2_qm = make_new_stub_1_qm;
	make_new_stub_1_qm = make_new_stub_1_qm_temp;
	end_2_item_qm = end_1_item;
	end_1_item = end_1_item_temp;
    }
    twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)20L));
    if ( !EQ(class_1,Qconnection))
	tformat(2,string_constant_34,class_1);
    if (end_2_item_qm)
	twrite_beginning_of_wide_string(array_constant_39,FIX((SI_Long)18L));
    else
	twrite_beginning_of_wide_string(array_constant_40,FIX((SI_Long)13L));
    write_stored_value(end_1_item);
    if (make_new_stub_1_qm) {
	twrite_beginning_of_wide_string(array_constant_41,FIX((SI_Long)35L));
	write_stored_value(side_1_qm);
	twrite_character(FIX((SI_Long)32L));
	write_stored_value(position_1_qm);
	twrite_beginning_of_wide_string(array_constant_42,FIX((SI_Long)13L));
	write_stored_value(portname_1_qm);
    }
    else {
	twrite_beginning_of_wide_string(array_constant_42,FIX((SI_Long)13L));
	write_stored_value(portname_1_qm);
	twrite_beginning_of_wide_string(array_constant_43,FIX((SI_Long)29L));
	write_stored_value(side_1_qm);
	twrite_character(FIX((SI_Long)32L));
	write_stored_value(position_1_qm);
    }
    if (end_2_item_qm) {
	twrite_beginning_of_wide_string(array_constant_33,FIX((SI_Long)5L));
	write_stored_value(end_2_item_qm);
	if (make_new_stub_2_qm) {
	    twrite_beginning_of_wide_string(array_constant_41,
		    FIX((SI_Long)35L));
	    write_stored_value(side_2_qm);
	    twrite_character(FIX((SI_Long)32L));
	    write_stored_value(position_2_qm);
	    twrite_beginning_of_wide_string(array_constant_42,
		    FIX((SI_Long)13L));
	    write_stored_value(portname_2_qm);
	}
	else {
	    twrite_beginning_of_wide_string(array_constant_42,
		    FIX((SI_Long)13L));
	    write_stored_value(portname_2_qm);
	    twrite_beginning_of_wide_string(array_constant_43,
		    FIX((SI_Long)29L));
	    write_stored_value(side_2_qm);
	    twrite_character(FIX((SI_Long)32L));
	    write_stored_value(position_2_qm);
	}
    }
    twrite_beginning_of_wide_string(array_constant_44,FIX((SI_Long)12L));
    write_stored_value(style_qm);
    twrite_beginning_of_wide_string(array_constant_45,FIX((SI_Long)16L));
    if (vertices_list_or_constant_index_qm && 
	    LISTP(vertices_list_or_constant_index_qm)) {
	index_1 = Nil;
	ab_loop_list_ = vertices_list_or_constant_index_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	index_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	tformat(2,string_constant_35,index_1);
	goto next_loop;
      end_loop:;
    }
    else
	write_stored_value(vertices_list_or_constant_index_qm);
    twrite_beginning_of_wide_string(array_constant_46,FIX((SI_Long)17L));
    write_stored_value(direction_qm);
    return VALUES_1(Nil);
}

static Object array_constant_47;   /* # */

static Object array_constant_48;   /* # */

/* PPRINT-HALT-INSTRUCTION */
Object pprint_halt_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,90);
    twrite_beginning_of_wide_string(array_constant_47,FIX((SI_Long)10L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_48,FIX((SI_Long)26L));
    return VALUES_1(Nil);
}

static Object array_constant_49;   /* # */

static Object array_constant_50;   /* # */

static Object Qscale;              /* scale */

static Object array_constant_51;   /* # */

static Object array_constant_52;   /* # */

static Object Qworkspace_position;  /* workspace-position */

static Object array_constant_53;   /* # */

static Object array_constant_54;   /* # */

static Object Qscreen_position;    /* screen-position */

/* PPRINT-SHOW-INSTRUCTION */
Object pprint_show_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object window_qm, show_details_constant_index_qm, show_details_qm;
    Object show_detail, temp;
    char stack_args_ok_qm;

    x_note_fn_call(205,91);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    window_qm = stack_args_ok_qm ? ISVREF(stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))) : Qnil;
    show_details_constant_index_qm = stack_args_ok_qm ? ISVREF(stack,
	    IFIX(top_of_stack)) : Nil;
    show_details_qm = show_details_constant_index_qm ? 
	    ISVREF(constant_vector,IFIX(show_details_constant_index_qm)) : Nil;
    twrite_beginning_of_wide_string(array_constant_49,FIX((SI_Long)5L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    if (window_qm) {
	twrite_beginning_of_wide_string(array_constant_50,FIX((SI_Long)4L));
	write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,
		top_of_stack);
    }
    show_detail = FIRST(show_details_qm);
  next_loop:
    if ( !TRUEP(show_details_qm))
	goto end_loop;
    show_details_qm = CDR(show_details_qm);
    temp = CAR(show_detail);
    if (EQ(temp,Qscale)) {
	twrite_beginning_of_wide_string(array_constant_51,FIX((SI_Long)4L));
	twrite(SECOND(show_detail));
	twrite_beginning_of_wide_string(array_constant_52,FIX((SI_Long)6L));
    }
    else if (EQ(temp,Qworkspace_position)) {
	twrite_beginning_of_wide_string(array_constant_53,FIX((SI_Long)10L));
	twrite_reference_point_details(CDR(show_detail));
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)1L));
	temp = FIRST(show_details_qm);
	twrite_reference_point_details(CDR(temp));
	twrite_beginning_of_wide_string(array_constant_54,FIX((SI_Long)14L));
	show_details_qm = CDR(show_details_qm);
    }
    else if (EQ(temp,Qscreen_position)) {
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)1L));
	twrite_reference_point_details(CDR(show_detail));
	twrite_beginning_of_wide_string(array_constant_54,FIX((SI_Long)14L));
    }
    show_detail = FIRST(show_details_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object array_constant_55;   /* # */

static Object array_constant_56;   /* # */

static Object array_constant_57;   /* # */

static Object array_constant_58;   /* # */

/* PPRINT-INVOKE-INSTRUCTION */
Object pprint_invoke_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object query_restriction_constant_index_qm, query_restriction_qm;
    Object focal_entity_qm, category, ab_loop_list_, first_arg_qm;
    char stack_args_ok_qm;

    x_note_fn_call(205,92);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    query_restriction_constant_index_qm = stack_args_ok_qm ? ISVREF(stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))) : Qnil;
    query_restriction_qm = query_restriction_constant_index_qm ? 
	    ISVREF(constant_vector,
	    IFIX(query_restriction_constant_index_qm)) : Qnil;
    focal_entity_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack)) :
	     Qnil;
    twrite_beginning_of_wide_string(array_constant_55,FIX((SI_Long)7L));
    if (stack_args_ok_qm) {
	category = Nil;
	ab_loop_list_ = CDR(query_restriction_qm);
	first_arg_qm = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (first_arg_qm)
	    first_arg_qm = Nil;
	else
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
	tformat(2,string_constant_29,category);
	goto next_loop;
      end_loop:;
    }
    else
	twrite_beginning_of_wide_string(array_constant_56,FIX((SI_Long)22L));
    twrite_beginning_of_wide_string(array_constant_57,FIX((SI_Long)6L));
    if (focal_entity_qm) {
	twrite_beginning_of_wide_string(array_constant_58,FIX((SI_Long)5L));
	write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
		top_of_stack);
    }
    return VALUES_1(Nil);
}

static Object array_constant_59;   /* # */

/* PPRINT-INVOKE-WITH-WAIT-INSTRUCTION */
Object pprint_invoke_with_wait_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object query_restriction_constant_index_qm, query_restriction_qm;
    Object focal_entity_qm, category, ab_loop_list_, first_arg_qm;
    char stack_args_ok_qm;

    x_note_fn_call(205,93);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    query_restriction_constant_index_qm = stack_args_ok_qm ? ISVREF(stack,
	    IFIX(FIXNUM_SUB1(top_of_stack))) : Qnil;
    query_restriction_qm = query_restriction_constant_index_qm ? 
	    ISVREF(constant_vector,
	    IFIX(query_restriction_constant_index_qm)) : Qnil;
    focal_entity_qm = stack_args_ok_qm ? ISVREF(stack,IFIX(top_of_stack)) :
	     Qnil;
    twrite_beginning_of_wide_string(array_constant_55,FIX((SI_Long)7L));
    if (stack_args_ok_qm) {
	category = Nil;
	ab_loop_list_ = CDR(query_restriction_qm);
	first_arg_qm = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (first_arg_qm)
	    first_arg_qm = Nil;
	else
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
	tformat(2,string_constant_29,category);
	goto next_loop;
      end_loop:;
    }
    else
	twrite_beginning_of_wide_string(array_constant_56,FIX((SI_Long)22L));
    twrite_beginning_of_wide_string(array_constant_57,FIX((SI_Long)6L));
    if (focal_entity_qm) {
	twrite_beginning_of_wide_string(array_constant_58,FIX((SI_Long)5L));
	write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,
		top_of_stack);
    }
    twrite_beginning_of_wide_string(array_constant_59,FIX((SI_Long)21L));
    return VALUES_1(Nil);
}

static Object array_constant_60;   /* # */

/* PPRINT-COERCE-MATCHING-ELEMENT-TYPE-INSTRUCTION */
Object pprint_coerce_matching_element_type_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,94);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_60,FIX((SI_Long)18L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_61;   /* # */

/* PPRINT-PAUSE-KB-INSTRUCTION */
Object pprint_pause_kb_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,95);
    twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)20L));
    return VALUES_1(Nil);
}

static Object array_constant_62;   /* # */

/* PPRINT-RESET-KB-INSTRUCTION */
Object pprint_reset_kb_instruction(pc,byte_code_body,constant_vector,stack,
	    top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,96);
    twrite_beginning_of_wide_string(array_constant_62,FIX((SI_Long)20L));
    return VALUES_1(Nil);
}

static Object array_constant_63;   /* # */

static Object string_constant_36;  /* "every ~a" */

static Object array_constant_64;   /* # */

/* PPRINT-NUPEC-SYNCHRONIZE-INSTRUCTION */
Object pprint_nupec_synchronize_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, synch_item_arg_count_qm;
    Object stack_arg_count_qm, class_arg_count, class_constant_index, classes;
    Object first_class_qm, class_1, ab_loop_list_, index_1;
    Object last_synch_item_arg_index, first_item_qm;
    SI_Long stack_arg_count_minus_one;
    char stack_args_ok_qm;

    x_note_fn_call(205,97);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    stack_args_ok_qm = FIXNUM_EQ(top_of_stack,Cached_top_of_stack);
    stack_arg_count_minus_one = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter));
    synch_item_arg_count_qm = stack_args_ok_qm ? 
	    FIX(stack_arg_count_minus_one - (SI_Long)2L) : Nil;
    stack_arg_count_qm = stack_args_ok_qm ? FIX(stack_arg_count_minus_one) 
	    : Nil;
    class_arg_count = FIX((SI_Long)0L);
    twrite_beginning_of_wide_string(array_constant_63,FIX((SI_Long)17L));
    if ( !stack_args_ok_qm)
	twrite_beginning_of_wide_string(array_constant_56,FIX((SI_Long)22L));
    else {
	class_constant_index = ISVREF(stack,IFIX(top_of_stack));
	classes = ISVREF(constant_vector,IFIX(class_constant_index));
	first_class_qm = T;
	class_1 = Nil;
	ab_loop_list_ = classes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (first_class_qm)
	    first_class_qm = Nil;
	else
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
	tformat(2,string_constant_36,class_1);
	goto next_loop;
      end_loop:
	class_arg_count = length(classes);
	index_1 = FIX((SI_Long)2L);
	last_synch_item_arg_index = FIXNUM_ADD1(synch_item_arg_count_qm);
	first_item_qm = T;
      next_loop_1:
	if (FIXNUM_GT(index_1,last_synch_item_arg_index))
	    goto end_loop_1;
	if (first_item_qm) {
	    first_item_qm = Nil;
	    if ( !(IFIX(class_arg_count) == (SI_Long)0L))
		twrite_beginning_of_wide_string(array_constant_9,
			FIX((SI_Long)2L));
	}
	else
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)2L));
	write_stack_argument(index_1,stack_arg_count_qm,stack,top_of_stack);
	index_1 = FIXNUM_ADD1(index_1);
	goto next_loop_1;
      end_loop_1:;
    }
    twrite_beginning_of_wide_string(array_constant_64,FIX((SI_Long)8L));
    if ( !stack_args_ok_qm)
	twrite_beginning_of_wide_string(array_constant_56,FIX((SI_Long)22L));
    else
	write_stack_argument(FIX((SI_Long)1L),stack_arg_count_qm,stack,
		top_of_stack);
    return VALUES_1(Nil);
}

static Object array_constant_65;   /* # */

static Object array_constant_66;   /* # */

/* PPRINT-NTH-ELEMENT-INSTRUCTION */
Object pprint_nth_element_instruction(pc,byte_code_body,constant_vector,
	    stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,98);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_65,FIX((SI_Long)1L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_66,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_67;   /* # */

/* PPRINT-COMPLETE-GENERIC-FORMULA-INSTRUCTION */
Object pprint_complete_generic_formula_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,99);
    twrite_beginning_of_wide_string(array_constant_67,FIX((SI_Long)26L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object array_constant_68;   /* # */

/* PPRINT-COMPLETE-CELL-EXPRESSION-INSTRUCTION */
Object pprint_complete_cell_expression_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,100);
    twrite_beginning_of_wide_string(array_constant_68,FIX((SI_Long)30L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

/* PPRINT-PUSH-CACHED-ITEM-INSTRUCTION */
Object pprint_push_cached_item_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, item_or_cons_qm, x2;
    char temp;

    x_note_fn_call(205,101);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    item_or_cons_qm = ISVREF(constant_vector,
	    (UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter)) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(FIXNUM_ADD1(stack_program_counter))));
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    if ( !TRUEP(item_or_cons_qm))
	twrite_beginning_of_wide_string(array_constant_56,FIX((SI_Long)22L));
    else {
	if (SIMPLE_VECTOR_P(item_or_cons_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_cons_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_cons_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_cons_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    tformat(2,string_constant_3,item_or_cons_qm);
	else if (CONSP(item_or_cons_qm))
	    tformat(2,string_constant_29,M_CAR(item_or_cons_qm));
	else
	    twrite_beginning_of_wide_string(array_constant_56,
		    FIX((SI_Long)22L));
    }
    return VALUES_1(Nil);
}

static Object string_constant_37;  /* "Attempted to execute ~a, which does not name a valid instruction.  ~
				    *      Execution has proceeded past the end of valid instructions or is ~
				    *      executing data.  Please report this G2 byte code executor bug to Gensym ~
				    *      software support."
				    */

/* BAD-INSTRUCTION-ERROR */
Object bad_instruction_error(instruction,top_of_stack)
    Object instruction, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(205,102);
    top_of_stack_1 = top_of_stack;
    message_1 = tformat_stack_error_text_string(2,string_constant_37,
	    instruction);
    raw_stack_error_named_error(top_of_stack_1,message_1);
    return VALUES_1(Nil);
}

/* EMIT-BRANCH-LONG-BYTE-CODES */
Object emit_branch_long_byte_codes(byte_code_stream,target_tag_marker)
    Object byte_code_stream, target_tag_marker;
{
    x_note_fn_call(205,103);
    register_byte_code_tag_resolution_point(byte_code_stream,
	    target_tag_marker);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)2L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
}

static Object Qbranch;             /* branch */

static Object Qbranch_relative;    /* branch-relative */

/* BC-BRANCH-LONG-RESOLVER */
Object bc_branch_long_resolver(byte_code_stream,byte_vector,address,tag)
    Object byte_code_stream, byte_vector, address, tag;
{
    Object tag_address, relative_offset, temp;

    x_note_fn_call(205,104);
    tag_address = instruction_address_for_tag(tag,Nil);
    relative_offset = FIXNUM_MINUS(tag_address,address);
    if (IFIX(tag_address) < (SI_Long)256L) {
	temp = op_code_for_stack_instruction(Qbranch);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	temp = FIXNUM_ADD1(address);
	UBYTE_8_ISASET_1(byte_vector,IFIX(temp),IFIX(tag_address));
    }
    else if (relative_code_constant_p(relative_offset)) {
	temp = op_code_for_stack_instruction(Qbranch_relative);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	setf_relative_code_constant_in_byte_vector(byte_vector,
		FIXNUM_ADD1(address),relative_offset);
    }
    else
	setf_long_code_constant(byte_vector,FIXNUM_ADD1(address),tag_address);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-BRANCH-LONG-IF-NOT-TRUE-BYTE-CODES */
Object emit_branch_long_if_not_true_byte_codes(byte_code_stream,
	    target_tag_statement)
    Object byte_code_stream, target_tag_statement;
{
    x_note_fn_call(205,105);
    register_byte_code_tag_resolution_point(byte_code_stream,
	    target_tag_statement);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)5L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
}

static Object Qbranch_if_not_true;  /* branch-if-not-true */

static Object Qbranch_relative_if_not_true;  /* branch-relative-if-not-true */

/* BC-BRANCH-LONG-IF-NOT-TRUE-RESOLVER */
Object bc_branch_long_if_not_true_resolver(byte_code_stream,byte_vector,
	    address,tag)
    Object byte_code_stream, byte_vector, address, tag;
{
    Object tag_address, relative_offset, temp;

    x_note_fn_call(205,106);
    tag_address = instruction_address_for_tag(tag,Nil);
    relative_offset = FIXNUM_MINUS(tag_address,address);
    if (IFIX(tag_address) < (SI_Long)256L) {
	temp = op_code_for_stack_instruction(Qbranch_if_not_true);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	temp = FIXNUM_ADD1(address);
	UBYTE_8_ISASET_1(byte_vector,IFIX(temp),IFIX(tag_address));
    }
    else if (relative_code_constant_p(relative_offset)) {
	temp = op_code_for_stack_instruction(Qbranch_relative_if_not_true);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	setf_relative_code_constant_in_byte_vector(byte_vector,
		FIXNUM_ADD1(address),relative_offset);
    }
    else
	setf_long_code_constant(byte_vector,FIXNUM_ADD1(address),tag_address);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-BRANCH-LONG-IF-NOT-FALSE-BYTE-CODES */
Object emit_branch_long_if_not_false_byte_codes(byte_code_stream,target_tag)
    Object byte_code_stream, target_tag;
{
    x_note_fn_call(205,107);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)50L));
    return emit_branch_long_if_not_true_byte_codes(byte_code_stream,
	    target_tag);
}

/* EMIT-BRANCH-LONG-IF-FALSE-BYTE-CODES */
Object emit_branch_long_if_false_byte_codes(byte_code_stream,target_tag)
    Object byte_code_stream, target_tag;
{
    x_note_fn_call(205,108);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)50L));
    return emit_branch_long_if_true_byte_codes(byte_code_stream,target_tag);
}

/* EMIT-BRANCH-LONG-IF-TRUE-BYTE-CODES */
Object emit_branch_long_if_true_byte_codes(byte_code_stream,target_tag)
    Object byte_code_stream, target_tag;
{
    Object new_tag;

    x_note_fn_call(205,109);
    new_tag = generate_new_goto_tag();
    emit_branch_long_if_not_true_byte_codes(byte_code_stream,new_tag);
    emit_branch_long_byte_codes(byte_code_stream,target_tag);
    return register_tag_in_byte_code_stream(2,byte_code_stream,new_tag);
}

/* EMIT-PUSH-CONSTANT-BYTE-CODES */
Object emit_push_constant_byte_codes(byte_code_stream,evaluation_value)
    Object byte_code_stream, evaluation_value;
{
    Object index_1;

    x_note_fn_call(205,110);
    if (FIXNUMP(evaluation_value) && 
	    relative_code_constant_p(evaluation_value)) {
	if ( !(FIXNUMP(evaluation_value) && FIXNUM_LE(FIX((SI_Long)-128L),
		evaluation_value) && FIXNUM_LE(evaluation_value,
		FIX((SI_Long)127L)))) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)9L));
	    return emit_relative_code_constant_to_stream(byte_code_stream,
		    evaluation_value);
	}
	else
	    switch (INTEGER_TO_CHAR(evaluation_value)) {
	      case 0:
		return write_byte_code_to_stream(byte_code_stream,
			FIX((SI_Long)12L));
	      case 1:
		return write_byte_code_to_stream(byte_code_stream,
			FIX((SI_Long)13L));
	      default:
		write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)9L));
		return emit_relative_code_constant_to_stream(byte_code_stream,
			evaluation_value);
	    }
    }
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value) && FIXNUM_EQ(M_CAR(evaluation_value),Truth))
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)10L));
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value) && FIXNUM_EQ(M_CAR(evaluation_value),Falsity))
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)11L));
    else if ( !TRUEP(evaluation_value))
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)14L));
    else {
	index_1 = register_constant_in_byte_code_stream(byte_code_stream,
		evaluation_value);
	if (IFIX(index_1) < (SI_Long)255L) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)7L));
	    return write_byte_code_to_stream(byte_code_stream,index_1);
	}
	else {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)8L));
	    return emit_long_code_constant_to_stream(byte_code_stream,index_1);
	}
    }
}

/* EMIT-PUSH-INTERNAL-CONSTANT-BYTE-CODES */
Object emit_push_internal_constant_byte_codes(byte_code_stream,slot_value)
    Object byte_code_stream, slot_value;
{
    Object index_1;

    x_note_fn_call(205,111);
    index_1 = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    slot_value);
    if (IFIX(index_1) < (SI_Long)255L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)15L));
	return write_byte_code_to_stream(byte_code_stream,index_1);
    }
    else {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)16L));
	return emit_long_code_constant_to_stream(byte_code_stream,index_1);
    }
}

/* EMIT-BRANCH-LONG-IF-KNOWN-BYTE-CODES */
Object emit_branch_long_if_known_byte_codes(byte_code_stream,target_tag)
    Object byte_code_stream, target_tag;
{
    x_note_fn_call(205,112);
    register_byte_code_tag_resolution_point(byte_code_stream,target_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)19L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
}

static Object Qbranch_if_known;    /* branch-if-known */

static Object Qbranch_relative_if_known;  /* branch-relative-if-known */

/* BC-BRANCH-LONG-IF-KNOWN-RESOLVER */
Object bc_branch_long_if_known_resolver(byte_code_stream,byte_vector,
	    address,tag)
    Object byte_code_stream, byte_vector, address, tag;
{
    Object tag_address, relative_offset, temp;

    x_note_fn_call(205,113);
    tag_address = instruction_address_for_tag(tag,Nil);
    relative_offset = FIXNUM_MINUS(tag_address,address);
    if (IFIX(tag_address) < (SI_Long)256L) {
	temp = op_code_for_stack_instruction(Qbranch_if_known);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	temp = FIXNUM_ADD1(address);
	UBYTE_8_ISASET_1(byte_vector,IFIX(temp),IFIX(tag_address));
    }
    else if (relative_code_constant_p(relative_offset)) {
	temp = op_code_for_stack_instruction(Qbranch_relative_if_known);
	UBYTE_8_ISASET_1(byte_vector,IFIX(address),IFIX(temp));
	setf_relative_code_constant_in_byte_vector(byte_vector,
		FIXNUM_ADD1(address),relative_offset);
    }
    else
	setf_long_code_constant(byte_vector,FIXNUM_ADD1(address),tag_address);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-POP-STACK-BYTE-CODES */
Object emit_pop_stack_byte_codes(byte_code_stream)
    Object byte_code_stream;
{
    x_note_fn_call(205,114);
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
}

static Object string_constant_38;  /* "pop-values stack instruction emitter" */

static Object string_constant_39;  /* "Trying to pop ~a values, can't pop less than zero." */

/* EMIT-POP-VALUES-BYTE-CODES */
Object emit_pop_values_byte_codes(byte_code_stream,values_to_pop)
    Object byte_code_stream, values_to_pop;
{
    Object overflows, remainder_1;
    SI_Long ab_loop_repeat_;
    Object result;

    x_note_fn_call(205,115);
    if (IFIX(values_to_pop) < (SI_Long)0L) {
	compiler_bug(3,string_constant_38,string_constant_39,values_to_pop);
	values_to_pop = FIX((SI_Long)0L);
    }
    result = lfloor(values_to_pop,FIX((SI_Long)255L));
    MVS_2(result,overflows,remainder_1);
    ab_loop_repeat_ = IFIX(overflows);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)25L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)255L));
    goto next_loop;
  end_loop:;
    if (IFIX(remainder_1) == (SI_Long)1L)
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)24L));
    else if (IFIX(remainder_1) > (SI_Long)0L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)25L));
	return write_byte_code_to_stream(byte_code_stream,remainder_1);
    }
    else
	return VALUES_1(Qnil);
}

/* EMIT-TYPECODE-TO-STREAM */
Object emit_typecode_to_stream(byte_code_stream,var_spot)
    Object byte_code_stream, var_spot;
{
    Object typecode, temp;

    x_note_fn_call(205,116);
    typecode = gensym_type_to_typecode(var_spot_type(var_spot,
	    Lexically_visible_code_bodies));
    temp = write_byte_code_to_stream(byte_code_stream,typecode);
    return VALUES_1(temp);
}

static Object string_constant_40;  /* "unrecognized typecode" */

static Object string_constant_41;  /* "null" */

static Object string_constant_42;  /* "integer" */

static Object string_constant_43;  /* "float" */

static Object string_constant_44;  /* "symbol" */

static Object string_constant_45;  /* "truth-value" */

static Object string_constant_46;  /* "text" */

static Object string_constant_47;  /* "item" */

static Object string_constant_48;  /* "iteration state" */

static Object string_constant_49;  /* "defined valuation type" */

static Object string_constant_50;  /* "evaluation type" */

static Object string_constant_51;  /* "item or datum" */

static Object string_constant_52;  /* "object of unknown type" */

static Object string_constant_53;  /* "sequence type" */

static Object string_constant_54;  /* "structure type" */

static Object string_constant_55;  /* "long" */

/* SIMPLE-TYPECODE-TO-TEXT */
Object simple_typecode_to_text(typecode)
    Object typecode;
{
    Object temp;

    x_note_fn_call(205,117);
    temp = typecode;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	temp = string_constant_40;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    temp = string_constant_41;
	    break;
	  case 1:
	    temp = string_constant_42;
	    break;
	  case 2:
	    temp = string_constant_43;
	    break;
	  case 3:
	    temp = string_constant_44;
	    break;
	  case 4:
	    temp = string_constant_45;
	    break;
	  case 5:
	    temp = string_constant_46;
	    break;
	  case 6:
	    temp = string_constant_47;
	    break;
	  case 7:
	    temp = string_constant_48;
	    break;
	  case 8:
	    temp = string_constant_49;
	    break;
	  case 9:
	    temp = string_constant_50;
	    break;
	  case 10:
	    temp = string_constant_51;
	    break;
	  case 11:
	    temp = string_constant_52;
	    break;
	  case 12:
	    temp = string_constant_53;
	    break;
	  case 13:
	    temp = string_constant_54;
	    break;
	  case 14:
	    temp = string_constant_55;
	    break;
	  default:
	    temp = string_constant_40;
	    break;
	}
    return VALUES_1(temp);
}

static Object string_constant_56;  /* "either null or " */

/* TWRITE-TYPECODE */
Object twrite_typecode(typecode)
    Object typecode;
{
    Object s;

    x_note_fn_call(205,118);
    if (FIXNUM_LT(typecode,Or_nil_typecode_modifier)) {
	s = simple_typecode_to_text(typecode);
	twrite(supply_a_or_an(s));
	twrite(s);
    }
    else {
	twrite(string_constant_56);
	twrite(FIXNUM_MINUS(typecode,Or_nil_typecode_modifier));
    }
    return VALUES_1(Nil);
}

Object Types_and_typecodes = UNBOUND;

Object No_information_typecode = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Use_type_info, Quse_type_info);

static Object list_constant;       /* # */

/* GENSYM-TYPE-TO-TYPECODE */
Object gensym_type_to_typecode(type)
    Object type;
{
    Object tail, pair, temp;

    x_note_fn_call(205,119);
    if (Use_type_info) {
	tail = Types_and_typecodes;
	pair = Nil;
	for ( ; !ENDP(tail); tail = CDR(tail)) {
	    pair = CAR(tail);
	    if (type_specification_subtype_p(type,FIRST(pair)))
		return VALUES_1(SECOND(pair));
	}
	tail = Types_and_typecodes;
	pair = Nil;
	for ( ; !ENDP(tail); tail = CDR(tail)) {
	    pair = CAR(tail);
	    if (type_specification_subtype_p(type,
		    make_type_specification_union(FIRST(pair),list_constant)))
		return VALUES_1(FIXNUM_ADD(Or_nil_typecode_modifier,
			SECOND(pair)));
	}
	temp = Anything_typecode;
    }
    else
	temp = Anything_typecode;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Always_make_runtime_nil_checks, Qalways_make_runtime_nil_checks);

/* EMIT-PUSH-FROM-STACK-FRAME-VAR-BYTE-CODES */
Object emit_push_from_stack_frame_var_byte_codes(byte_code_stream,var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,120);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)27L));
    write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    return emit_typecode_to_stream(byte_code_stream,var_spot);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_57;  /* "Nothing was returned from an expression which should have ~
				    *               returned a value of the type ~NT."
				    */

static Object array_constant_69;   /* # */

static Object string_constant_58;  /* " is being given to an operation which requires values of the ~
				    *               type ~NT."
				    */

/* SIGNAL-STACK-TYPE-CHECK-ERROR-MESSAGE */
Object signal_stack_type_check_error_message(value,type,top_of_stack)
    Object value, type, top_of_stack;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(205,121);
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
		  if ( !TRUEP(value))
		      tformat(2,string_constant_57,type);
		  else {
		      if ( !(INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			      (SI_Long)1L)) {
			  if (SIMPLE_VECTOR_P(value) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
				  (SI_Long)2L &&  !EQ(ISVREF(value,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(value,(SI_Long)1L);
			      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp = TRUEP(Nil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  tformat(2,string_constant_3,value);
		      else {
			  gensymed_symbol = value;
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
			      temp = INLINE_LONG_VECTOR_P(gensymed_symbol) 
				      != (SI_Long)0L ? 
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
				  skip_list = 
					  CDR(Defined_evaluation_value_types);
				  key_value = gensymed_symbol;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(gensymed_symbol) 
					  & IFIX(Most_positive_fixnum);
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
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_1:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_1 = ATOMIC_REF_OBJECT(reference);
				  temp_2 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_1,temp_2);
				  MVS_2(result,succ,marked);
				next_loop_2:
				  if ( !TRUEP(marked))
				      goto end_loop_1;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_1 = ATOMIC_REF_OBJECT(reference);
				  temp_2 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_1,temp_2);
				  MVS_2(result,succ,marked);
				  goto next_loop_2;
				end_loop_1:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
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
			      write_evaluation_value(1,value);
			  else
			      twrite_beginning_of_wide_string(array_constant_69,
				      FIX((SI_Long)15L));
		      }
		      tformat(2,string_constant_58,type);
		  }
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

/* EMIT-PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR-BYTE-CODES */
Object emit_push_value_or_none_from_stack_frame_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,122);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)121L));
    write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    return emit_typecode_to_stream(byte_code_stream,var_spot);
}

/* EMIT-POP-INTO-STACK-ARG-BYTE-CODES */
Object emit_pop_into_stack_arg_byte_codes(byte_code_stream,index_1)
    Object byte_code_stream, index_1;
{
    x_note_fn_call(205,123);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)28L));
    return write_byte_code_to_stream(byte_code_stream,index_1);
}

/* EMIT-PUSH-FROM-STACK-ARG-BYTE-CODES */
Object emit_push_from_stack_arg_byte_codes(byte_code_stream,var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,124);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)29L));
    write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    return emit_typecode_to_stream(byte_code_stream,var_spot);
}

/* EMIT-PUSH-VALUE-OR-NONE-FROM-STACK-ARG-BYTE-CODES */
Object emit_push_value_or_none_from_stack_arg_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,125);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)122L));
    write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    return emit_typecode_to_stream(byte_code_stream,var_spot);
}

/* CASE-DISPATCH-BYTE-COUNT */
Object case_dispatch_byte_count(address,raw_byte_vector,constant_vector)
    Object address, raw_byte_vector, constant_vector;
{
    x_note_fn_call(205,126);
    return VALUES_1(FIX((SI_Long)7L + (SI_Long)2L * 
	    IFIX(long_code_constant_in_byte_vector(raw_byte_vector,
	    FIX(IFIX(address) + (SI_Long)3L)))));
}

/* EMIT-CASE-DISPATCH-BYTE-CODES */
Object emit_case_dispatch_byte_codes(byte_code_stream,table_base,
	    table_length,else_tag,tag_table)
    Object byte_code_stream, table_base, table_length, else_tag, tag_table;
{
    SI_Long ab_loop_repeat_;

    x_note_fn_call(205,127);
    if ( !(IFIX(table_base) >= (SI_Long)0L && IFIX(table_base) <= 
	    (SI_Long)65535L)) {
	emit_push_constant_byte_codes(byte_code_stream,
		FIXNUM_NEGATE(table_base));
	emit_operator_of_type(byte_code_stream,Qplus,Qinteger);
	table_base = FIX((SI_Long)0L);
    }
    register_byte_code_tag_resolution_point(byte_code_stream,
	    compiler_cons_1(else_tag,
	    copy_list_using_compiler_conses_1(tag_table)));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)30L));
    emit_long_code_constant_to_stream(byte_code_stream,table_base);
    emit_long_code_constant_to_stream(byte_code_stream,table_length);
    ab_loop_repeat_ = IFIX(FIXNUM_ADD1(table_length));
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    emit_long_code_constant_to_stream(byte_code_stream,FIX((SI_Long)0L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* BC-CASE-DISPATCH-RESOLVER */
Object bc_case_dispatch_resolver(byte_code_stream,byte_vector,address,
	    else_tag_and_table)
    Object byte_code_stream, byte_vector, address, else_tag_and_table;
{
    Object tag, ab_loop_list_, temp;
    SI_Long byte_address;

    x_note_fn_call(205,128);
    byte_address = IFIX(address) + (SI_Long)5L;
    tag = Nil;
    ab_loop_list_ = else_tag_and_table;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    tag = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FIX(byte_address);
    setf_long_code_constant(byte_vector,temp,
	    instruction_address_for_tag(tag,Nil));
    byte_address = byte_address + (SI_Long)2L;
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* ATTEMPT-TO-COERCE-TO-GENSYM-FLOAT */
Object attempt_to_coerce_to_gensym_float(thing)
    Object thing;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2, x2, gensymed_symbol, sub_class_bit_vector;
    Object managed_number_or_value, value, type;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_3;
    double aref_new_value;

    x_note_fn_call(205,129);
    if (FIXNUMP(thing)) {
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
	aref_new_value = (double)IFIX(thing);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
    }
    else {
	if (SIMPLE_VECTOR_P(thing) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L &&  
		!EQ(ISVREF(thing,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing,(SI_Long)1L);
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
		    IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		temp_3 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_3 = TRUEP(Nil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    managed_number_or_value = ISVREF(thing,(SI_Long)23L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		value = copy_text_string(managed_number_or_value);
	    else
		value = managed_number_or_value;
	    type = type_specification_of_variable_or_parameter_value(thing);
	    if (EQ(type,Qtruth_value)) {
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
			temp = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = (double)IFIX(value) / 1000.0;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_2 = new_float;
	    }
	    else if (FLOATP(value)) {
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
			temp = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_2 = new_float;
	    }
	    else if (FIXNUMP(value)) {
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
			temp = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = (double)IFIX(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_2 = new_float;
	    }
	    else
		temp_2 = Nil;
	}
	else
	    temp_2 = Nil;
    }
    return VALUES_1(temp_2);
}

Object Classes_type_checked_inline = UNBOUND;

static Object string_constant_59;  /* "~A ~A ~A." */

static Object string_constant_60;  /* "~NF ~A ~A." */

static Object string_constant_61;  /* "The symbol ~NV ~A ~A." */

static Object string_constant_62;  /* "~NV ~A ~A." */

static Object string_constant_63;  /* "None" */

static Object string_constant_64;  /* "should have been an instance of the class" */

/* SIGNAL-STACK-CLASS-TYPE-CHECK-ERROR-MESSAGE */
Object signal_stack_class_type_check_error_message(thing,class_1)
    Object thing, class_1;
{
    Object temp, x2, gensymed_symbol, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(205,130);
    if ( !TRUEP(thing))
	temp = string_constant_59;
    else {
	if (SIMPLE_VECTOR_P(thing) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L &&  
		!EQ(ISVREF(thing,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = string_constant_60;
	else if (thing && SYMBOLP(thing))
	    temp = string_constant_61;
	else {
	    gensymed_symbol = thing;
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
	    if (temp_1)
		temp = string_constant_62;
	    else
		temp = Qnil;
	}
    }
    return tformat_stack_error_text_string(4,temp,thing ? thing : 
	    string_constant_63,string_constant_64,FIXNUMP(class_1) ? 
	    nth(class_1,Classes_type_checked_inline) : class_1);
}

static Object Qitem;               /* item */

/* EMIT-TYPE-CHECK-CLASS-BYTE-CODES */
Object emit_type_check_class_byte_codes(byte_code_stream,class_name)
    Object byte_code_stream, class_name;
{
    Object index_1;

    x_note_fn_call(205,131);
    if (EQ(class_name,Qitem))
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)71L));
    else if (memq_function(class_name,Classes_type_checked_inline))
	return emit_type_check_class_inline_byte_codes(byte_code_stream,
		class_name);
    else {
	index_1 = register_constant_in_byte_code_stream(byte_code_stream,
		class_name);
	if (IFIX(index_1) < (SI_Long)256L) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)37L));
	    return write_byte_code_to_stream(byte_code_stream,index_1);
	}
	else {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)38L));
	    return emit_long_code_constant_to_stream(byte_code_stream,index_1);
	}
    }
}

static Object string_constant_65;  /* "type check emitter" */

static Object string_constant_66;  /* "Invalid type ~a given to instruction emitter." */

static Object list_constant_1;     /* # */

static Object Qtype_check_item_or_datum;  /* type-check-item-or-datum */

static Object Qtype_check_truth_value;  /* type-check-truth-value */

static Object Qtype_check_symbol;  /* type-check-symbol */

static Object Qtype_check_text;    /* type-check-text */

static Object Qtype_check_quantity;  /* type-check-quantity */

static Object Qtype_check_integer;  /* type-check-integer */

static Object Qtype_check_float;   /* type-check-float */

/* EMIT-TYPE-CHECK-BYTE-CODES */
Object emit_type_check_byte_codes(byte_code_stream,type)
    Object byte_code_stream, type;
{
    Object temp, subtype, ab_loop_list_, constant_index;

    x_note_fn_call(205,132);
    if ( !TRUEP(valid_type_specification_p(type)))
	return compiler_bug(3,string_constant_65,string_constant_66,type);
    else if (class_type_specification_p(type))
	return emit_type_check_class_byte_codes(byte_code_stream,
		M_CAR(M_CDR(type)));
    else if (memq_function(type,list_constant_1)) {
	if (EQ(type,Qitem_or_datum))
	    temp = Qtype_check_item_or_datum;
	else if (EQ(type,Qtruth_value))
	    temp = Qtype_check_truth_value;
	else if (EQ(type,Qsymbol))
	    temp = Qtype_check_symbol;
	else if (EQ(type,Qtext))
	    temp = Qtype_check_text;
	else if (EQ(type,Qnumber))
	    temp = Qtype_check_quantity;
	else if (EQ(type,Qinteger))
	    temp = Qtype_check_integer;
	else if (EQ(type,Qfloat))
	    temp = Qtype_check_float;
	else
	    temp = Qnil;
	return write_byte_code_to_stream(byte_code_stream,
		op_code_for_stack_instruction(temp));
    }
    else if (intersection_type_specification_p(type)) {
	subtype = Nil;
	ab_loop_list_ = CDR(type);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subtype = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	emit_type_check_byte_codes(byte_code_stream,subtype);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	constant_index = 
		register_internal_constant_in_byte_code_stream(byte_code_stream,
		type);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)91L));
	return emit_long_code_constant_to_stream(byte_code_stream,
		constant_index);
    }
}

static Object string_constant_67;  /* "An attempt was made to reference surrounding local var ~a.  This kind of ~
				    *    reference should only happen within procedures."
				    */

/* SIGNAL-NESTED-CODE-BODIES-OUT-OF-PROCEDURES-MESSAGE */
Object signal_nested_code_bodies_out_of_procedures_message(local_var_index)
    Object local_var_index;
{
    x_note_fn_call(205,133);
    return tformat_stack_error_text_string(2,string_constant_67,
	    local_var_index);
}

static Object string_constant_68;  /* "pop-into-local-var emitter" */

static Object string_constant_69;  /* "An invalid var spot, ~a, was given." */

static Object list_constant_2;     /* # */

static Object Qstack_frame_var;    /* stack-frame-var */

static Object Qstack_arg;          /* stack-arg */

/* EMIT-POP-INTO-SURROUNDING-LOCAL-VAR-BYTE-CODES */
Object emit_pop_into_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    Object first_index;

    x_note_fn_call(205,134);
    if ( !TRUEP(valid_var_spot_p(var_spot))) {
	compiler_bug(3,string_constant_68,string_constant_69,var_spot);
	var_spot = list_constant_2;
    }
    if (EQ(CAR(var_spot),Qstack_frame_var)) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)26L));
	return write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    }
    else if (EQ(CAR(var_spot),Qstack_arg))
	return emit_pop_into_stack_arg_byte_codes(byte_code_stream,
		SECOND(var_spot));
    else {
	first_index = SECOND(var_spot);
	if (FIXNUMP(first_index) && IFIX(first_index) < (SI_Long)256L) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)41L));
	    write_byte_code_to_stream(byte_code_stream,first_index);
	    return emit_typecode_to_stream(byte_code_stream,var_spot);
	}
	else {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)40L));
	    emit_long_code_constant_to_stream(byte_code_stream,first_index);
	    return emit_typecode_to_stream(byte_code_stream,var_spot);
	}
    }
}

static Object array_constant_70;   /* # */

static Object array_constant_71;   /* # */

/* SIGNAL-NO-VALUE-IN-LOCAL-VAR-ERROR-1 */
Object signal_no_value_in_local_var_error_1(var_spot_or_index,
	    compiled_item,compiled_item_component_particulars_qm)
    Object var_spot_or_index, compiled_item;
    Object compiled_item_component_particulars_qm;
{
    Object byte_code_body_qm, consed_var_spot_qm, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(205,135);
    byte_code_body_qm = get_byte_code_body_if_any(compiled_item,
	    compiled_item_component_particulars_qm);
    consed_var_spot_qm = valid_var_spot_index_p(var_spot_or_index) ? 
	    gensym_list_2(Qvar_spot,var_spot_or_index) : Nil;
    if (consed_var_spot_qm)
	var_spot_or_index = consed_var_spot_qm;
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
		  twrite_beginning_of_wide_string(array_constant_70,
			  FIX((SI_Long)15L));
		  print_var_spot_for_stack(3,var_spot_or_index,
			  ISVREF(byte_code_body_qm,(SI_Long)4L),T);
		  reclaim_gensym_list_1(consed_var_spot_qm);
		  twrite_beginning_of_wide_string(array_constant_71,
			  FIX((SI_Long)37L));
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

static Object string_constant_70;  /* "push-from-local-var emitter" */

/* EMIT-PUSH-FROM-SURROUNDING-LOCAL-VAR-BYTE-CODES */
Object emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    Object first_index;

    x_note_fn_call(205,136);
    if ( !TRUEP(valid_var_spot_p(var_spot))) {
	compiler_bug(3,string_constant_70,string_constant_69,var_spot);
	var_spot = list_constant_2;
    }
    if (EQ(CAR(var_spot),Qstack_frame_var))
	return emit_push_from_stack_frame_var_byte_codes(byte_code_stream,
		var_spot);
    else if (EQ(CAR(var_spot),Qstack_arg))
	return emit_push_from_stack_arg_byte_codes(byte_code_stream,var_spot);
    else {
	first_index = SECOND(var_spot);
	if (FIXNUMP(first_index) && IFIX(first_index) < (SI_Long)256L) {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)43L));
	    write_byte_code_to_stream(byte_code_stream,first_index);
	    return emit_typecode_to_stream(byte_code_stream,var_spot);
	}
	else {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)42L));
	    emit_long_code_constant_to_stream(byte_code_stream,first_index);
	    return emit_typecode_to_stream(byte_code_stream,var_spot);
	}
    }
}

static Object string_constant_71;  /* "The item named ~a cannot be referred to because it is disabled or inactive." */

static Object string_constant_72;  /* "No item named ~a exists." */

/* NAME-REFERENCE-ERROR-MESSAGE */
Object name_reference_error_message(name)
    Object name;
{
    Object frame_with_name_qm;

    x_note_fn_call(205,137);
    frame_with_name_qm = get_instance_with_name_if_any(Qitem,name);
    return tformat_stack_error_text_string(2,frame_with_name_qm &&  
	    !((SI_Long)0L != (IFIX(ISVREF(frame_with_name_qm,(SI_Long)5L)) 
	    & (SI_Long)1L)) &&  !((IFIX(Current_computation_flags) & 
	    (SI_Long)16L) != (SI_Long)0L) ? string_constant_71 : 
	    string_constant_72,name);
}

/* LOOKUP-NAME-REFERENCE */
Object lookup_name_reference(name)
    Object name;
{
    Object frame_qm;

    x_note_fn_call(205,138);
    frame_qm = get_instance_with_name_if_any(Qitem,name);
    return VALUES_1(frame_qm && serve_item_p(frame_qm) ? frame_qm : Nil);
}

/* EMIT-NAME-REFERENCE-BYTE-CODES */
Object emit_name_reference_byte_codes(byte_code_stream,name_constant,
	    no_item_ok_qm)
    Object byte_code_stream, name_constant, no_item_ok_qm;
{
    Object index_1;

    x_note_fn_call(205,139);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)44L));
    index_1 = register_constant_in_byte_code_stream(byte_code_stream,
	    name_constant);
    emit_long_code_constant_to_stream(byte_code_stream,index_1);
    return write_byte_code_to_stream(byte_code_stream,no_item_ok_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

static Object Qrole_server;        /* role-server */

static Object Qunique_value_of_role_server_function;  /* unique-value-of-role-server-function */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* FETCH-UNIQUE-VALUE-OF-ROLE-FOR-STACK */
Object fetch_unique_value_of_role_for_stack(role,domain_count,domain_1,
	    domain_2_qm,top_of_stack,no_item_allowed_qm)
    Object role, domain_count, domain_1, domain_2_qm, top_of_stack;
    Object no_item_allowed_qm;
{
    Object value, expiration, too_many_values_qm, role_1, role_car, role_name;
    Object list_1, unique_value_function, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, virtual_attribute_qm, getter_qm, virtual_value;
    char two_arg_qm;
    Object result;

    x_note_fn_call(205,140);
    two_arg_qm = IFIX(domain_count) == (SI_Long)2L;
    value = Nil;
    expiration = Nil;
    too_many_values_qm = Nil;
    if ( !TRUEP(domain_1) || two_arg_qm &&  !TRUEP(domain_2_qm)) {
	if ( !(FIXNUMP(domain_1) || SYMBOLP(domain_1) || 
		SIMPLE_VECTOR_P(domain_1)))
	    reclaim_if_evaluation_value_1(domain_1);
	if ( !(FIXNUMP(domain_2_qm) || SYMBOLP(domain_2_qm) || 
		SIMPLE_VECTOR_P(domain_2_qm)))
	    reclaim_if_evaluation_value_1(domain_2_qm);
	return VALUES_1(Nil);
    }
    if (CONSP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : 
		role_car;
	list_1 = INLINE_SYMBOL_PLIST(role_name);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Qunique_value_of_role_server_function))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:
	unique_value_function = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	if (unique_value_function) {
	    if (two_arg_qm) {
		gensymed_symbol = unique_value_function;
		gensymed_symbol_1 = top_of_stack;
		gensymed_symbol_2 = role;
		gensymed_symbol_3 = no_item_allowed_qm;
		gensymed_symbol_4 = domain_1;
		gensymed_symbol_5 = domain_2_qm;
		return VALUES_1(inline_funcall_5(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4,
			gensymed_symbol_5));
	    }
	    else {
		gensymed_symbol = unique_value_function;
		gensymed_symbol_1 = top_of_stack;
		gensymed_symbol_2 = role;
		gensymed_symbol_3 = no_item_allowed_qm;
		gensymed_symbol_4 = domain_1;
		return VALUES_1(inline_funcall_4(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4));
	    }
	}
    }
    result = serve_unique_item_or_evaluation_value_of_role(role,domain_1,
	    domain_2_qm,Nil);
    MVS_3(result,value,expiration,too_many_values_qm);
    if ( !TRUEP(expiration)) {
	value = Nil;
	if ( !two_arg_qm && SYMBOLP(role)) {
	    virtual_attribute_qm = get_property_value_function(3,
		    get_symbol_properties_function(role),
		    Qvirtual_attribute,Nil);
	    if (virtual_attribute_qm && type_specification_type_p(domain_1,
		    ISVREF(virtual_attribute_qm,(SI_Long)2L))) {
		getter_qm = ISVREF(virtual_attribute_qm,(SI_Long)6L);
		virtual_value = getter_qm ? inline_funcall_1(getter_qm,
			domain_1) : No_component_value;
		if ( !EQ(virtual_value,No_component_value))
		    value = virtual_value;
	    }
	}
	if ( !(value || no_item_allowed_qm))
	    raw_stack_error_named_error(top_of_stack,
		    role_returned_no_values_error_1(role,domain_1,
		    domain_2_qm));
	if ( !TRUEP(value) && too_many_values_qm && 
		(IFIX(Tracing_message_level) > (SI_Long)2L || 
		IFIX(Breakpoint_level) > (SI_Long)2L) &&  
		!TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		(SI_Long)22L))
	    trace_too_many_objects_role_error(role);
    }
    if ( !(FIXNUMP(domain_1) || SYMBOLP(domain_1) || 
	    SIMPLE_VECTOR_P(domain_1)))
	reclaim_if_evaluation_value_1(domain_1);
    if ( !(FIXNUMP(domain_2_qm) || SYMBOLP(domain_2_qm) || 
	    SIMPLE_VECTOR_P(domain_2_qm)))
	reclaim_if_evaluation_value_1(domain_2_qm);
    return VALUES_1(value);
}

/* ATTRIBUTE-RETURNED-NO-VALUES-ERROR-1 */
Object attribute_returned_no_values_error_1(attribute,item_or_structure,
	    class_specific_attribute_class_qm)
    Object attribute, item_or_structure, class_specific_attribute_class_qm;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(205,141);
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
		  write_attribute_returned_no_values_error_message(attribute,
			  item_or_structure,class_specific_attribute_class_qm);
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

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qattribute_value;    /* attribute-value */

static Object array_constant_72;   /* # */

static Object array_constant_73;   /* # */

/* ROLE-RETURNED-NO-VALUES-ERROR-1 */
Object role_returned_no_values_error_1(role,domain_1_qm,domain_2_qm)
    Object role, domain_1_qm, domain_2_qm;
{
    Object x2, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, schar_arg_2, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    char temp;
    Declare_special(7);

    x_note_fn_call(205,142);
    if (SYMBOLP(role)) {
	if (SIMPLE_VECTOR_P(domain_1_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(domain_1_qm)) > (SI_Long)2L 
		&&  !EQ(ISVREF(domain_1_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(domain_1_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return attribute_returned_no_values_error_1(role,domain_1_qm,Nil);
    else if (CONSP(role) && EQ(M_CAR(role),Qclass_qualified_name))
	return attribute_returned_no_values_error_1(THIRD(role),
		domain_1_qm,SECOND(role));
    else if (CONSP(role) && EQ(M_CAR(role),Qattribute_value))
	return attribute_returned_no_values_error_1(domain_2_qm,
		domain_1_qm,Nil);
    else {
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
		      twrite_beginning_of_wide_string(array_constant_72,
			      FIX((SI_Long)37L));
		      print_role(role);
		      if (domain_1_qm) {
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = (SI_Long)32L;
			      twrite_wide_character(CHARACTERP(FIX(thing)) 
				      ? CHAR_CODE(FIX(thing)) : FIX(thing));
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp_1 = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = (SI_Long)32L;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(FIX(thing)) ? 
				      CHAR_CODE(FIX(thing)) : FIX(thing));
			      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			      temp_1 = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp_1;
			  }
			  write_stored_value(domain_1_qm);
		      }
		      if (domain_2_qm) {
			  twrite_beginning_of_wide_string(array_constant_33,
				  FIX((SI_Long)5L));
			  write_stored_value(domain_2_qm);
		      }
		      twrite_beginning_of_wide_string(array_constant_73,
			      FIX((SI_Long)37L));
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
}

static Object string_constant_73;  /* "The attribute ~A of ~NF is read-only." */

static Object string_constant_74;  /* "The attribute ~A exists in ~NF, but the attribute contained ~
				    *                            nothing, causing this reference to fail."
				    */

static Object string_constant_75;  /* "The system defined attribute ~a of ~NF cannot be ~
				    *                            referenced directly, causing this reference to fail.  ~
				    *                            However, you can reference the text of this attribute."
				    */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object string_constant_76;  /* "The attribute ~a::~a does not exist in ~NF, since ~a is not ~
				    *                  a defined class."
				    */

static Object string_constant_77;  /* "The attribute ~a::~a does not exist in ~NF, since ~NF is not ~
				    *                  an instance of the class ~a."
				    */

static Object string_constant_78;  /* "The attribute ~a exists in ~NF, but is not defined for ~
				    *                  the superior-class ~a."
				    */

static Object string_constant_79;  /* "The attribute ~a does not exist in ~NF~a." */

static Object string_constant_80;  /* ", though this attribute is defined for other classes" */

static Object string_constant_81;  /* "" */

static Object string_constant_82;  /* "The attribute ~NS exists in ~NF, but the attribute contained ~
				    *                nothing, causing this reference to fail."
				    */

static Object string_constant_83;  /* "The attribute ~NS of ~NF contained an item which was " */

static Object string_constant_84;  /* "~a." */

static Object string_constant_85;  /* "inactive or disabled." */

static Object string_constant_86;  /* "An attempt to reference the ~A::~A of ~NF failed to return a value." */

static Object string_constant_87;  /* "An attempt to reference the ~A of ~NF failed to return a value." */

static Object Qab_structure;       /* structure */

static Object string_constant_88;  /* "The attribute ~(~a~) was not found in ~NV." */

static Object string_constant_89;  /* "The attribute ~NV was not found." */

/* WRITE-ATTRIBUTE-RETURNED-NO-VALUES-ERROR-MESSAGE */
Object write_attribute_returned_no_values_error_message(attribute,
	    item_or_structure,class_specific_attribute_class_qm)
    Object attribute, item_or_structure, class_specific_attribute_class_qm;
{
    Object x2, slot_description_qm, slot_value_qm, class_1, actual_name_qm;
    Object actual_slot_description_qm, slot_type_qm, evaluator_slot_info_qm;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_1;
    Object temp_2, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object evaluation_value_writing_target_length_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(205,143);
    if (SIMPLE_VECTOR_P(item_or_structure) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_structure)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item_or_structure,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_structure,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	slot_description_qm = 
		get_slot_description_of_class_description_function(attribute,
		ISVREF(item_or_structure,(SI_Long)1L),
		class_specific_attribute_class_qm);
	slot_value_qm = slot_description_qm ? 
		get_slot_description_value(item_or_structure,
		slot_description_qm) : Nil;
	if ( !TRUEP(slot_description_qm)) {
	    class_1 = ISVREF(ISVREF(item_or_structure,(SI_Long)1L),
		    (SI_Long)1L);
	    actual_name_qm = get_slot_name_for_alias_if_any(attribute,class_1);
	    if (actual_name_qm);
	    else
		actual_name_qm = attribute;
	    actual_slot_description_qm = 
		    get_slot_description_of_class_description_function(actual_name_qm,
		    ISVREF(item_or_structure,(SI_Long)1L),
		    class_specific_attribute_class_qm);
	    slot_type_qm = actual_slot_description_qm ? 
		    assq_function(Qtype,ISVREF(actual_slot_description_qm,
		    (SI_Long)9L)) : Qnil;
	    if (slot_type_qm &&  
		    !TRUEP(do_not_put_slot_in_attribute_tables_p(2,
		    actual_slot_description_qm,Nil))) {
		evaluator_slot_info_qm = ISVREF(actual_slot_description_qm,
			(SI_Long)10L);
		if (evaluator_slot_info_qm);
		else
		    evaluator_slot_info_qm = 
			    cache_evaluator_slot_info(actual_slot_description_qm);
		if (evaluator_slot_info_qm &&  
			!TRUEP(ISVREF(evaluator_slot_info_qm,(SI_Long)2L)))
		    tformat(3,string_constant_73,attribute,item_or_structure);
		else if (evaluator_slot_info_qm &&  !TRUEP(slot_value_qm) 
			&& ISVREF(evaluator_slot_info_qm,(SI_Long)3L))
		    tformat(3,string_constant_74,attribute,item_or_structure);
		else
		    tformat(3,string_constant_75,attribute,item_or_structure);
	    }
	    else {
		if (class_specific_attribute_class_qm) {
		    if (SYMBOLP(class_specific_attribute_class_qm)) {
			skip_list = CDR(Symbol_properties_table);
			key_value = class_specific_attribute_class_qm;
			key_hash_value = 
				SXHASH_SYMBOL_1(class_specific_attribute_class_qm) 
				& IFIX(Most_positive_fixnum);
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
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_2:
			if ( !TRUEP(marked))
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
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
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = 
				    class_specific_attribute_class_qm;
			    temp_1 = Symbol_properties_table;
			    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
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
			    gensymed_symbol = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_2,gensymed_symbol_1);
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
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_5:
			if ( !TRUEP(marked))
			    goto end_loop_4;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
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
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_8:
			    if ( !TRUEP(marked))
				goto end_loop_7;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
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
			  next_loop_9:
			    if (level < ab_loop_bind_)
				goto end_loop_9;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_10:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_11:
			    if ( !TRUEP(marked))
				goto end_loop_10;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
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
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			temp = TRUEP(resulting_value);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    tformat(5,string_constant_76,
			    class_specific_attribute_class_qm,attribute,
			    item_or_structure,
			    class_specific_attribute_class_qm);
		else {
		    if (class_specific_attribute_class_qm) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(class_specific_attribute_class_qm,
				Class_description_gkbprop);
			if (gensymed_symbol) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(item_or_structure,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				temp = (SI_Long)0L < gensymed_symbol_3;
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
		    if (temp)
			tformat(6,string_constant_77,
				class_specific_attribute_class_qm,
				attribute,item_or_structure,
				item_or_structure,
				class_specific_attribute_class_qm);
		    else if (class_specific_attribute_class_qm && 
			    get_slot_description_of_class_description_function(attribute,
			    ISVREF(item_or_structure,(SI_Long)1L),Nil))
			tformat(4,string_constant_78,attribute,
				item_or_structure,
				class_specific_attribute_class_qm);
		    else
			tformat(4,string_constant_79,attribute,
				item_or_structure,
				lookup_kb_specific_property_value(attribute,
				Class_and_symbol_values_for_attribute_kbprop) 
				? string_constant_80 : string_constant_81);
		}
	    }
	}
	else if ( !TRUEP(slot_value_qm))
	    tformat(4,string_constant_82,slot_description_qm,
		    ISVREF(item_or_structure,(SI_Long)1L),item_or_structure);
	else {
	    if (SIMPLE_VECTOR_P(slot_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(slot_value_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ((temp ?  !((SI_Long)0L != (IFIX(ISVREF(slot_value_qm,
		    (SI_Long)5L)) & (SI_Long)1L)) : TRUEP(Nil)) ?  
		    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		    (SI_Long)0L) : TRUEP(Nil)) {
		tformat(4,string_constant_83,slot_description_qm,
			ISVREF(item_or_structure,(SI_Long)1L),
			item_or_structure);
		temp_2 = ISVREF(slot_value_qm,(SI_Long)8L);
		if ( ! !TRUEP(CAR(temp_2))) {
		    temp_2 = ISVREF(slot_value_qm,(SI_Long)8L);
		    tformat(2,string_constant_84,CAR(temp_2));
		}
		else
		    tformat(1,string_constant_85);
	    }
	    else if (class_specific_attribute_class_qm)
		tformat(4,string_constant_86,
			class_specific_attribute_class_qm,attribute,
			item_or_structure);
	    else
		tformat(3,string_constant_87,attribute,item_or_structure);
	}
    }
    else if (CONSP(item_or_structure) && EQ(M_CDR(item_or_structure),
	    Qab_structure)) {
	evaluation_value_writing_target_length_qm = 
		Maximum_length_for_writing_evaluation_values;
	PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
		0);
	  tformat(3,string_constant_88,attribute,item_or_structure);
	POP_SPECIAL();
    }
    else
	tformat(2,string_constant_89,attribute);
    return VALUES_1(Nil);
}

static Object array_constant_74;   /* # */

static Object array_constant_75;   /* # */

/* TRACE-TOO-MANY-OBJECTS-ROLE-ERROR */
Object trace_too_many_objects_role_error(role)
    Object role;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,144);
    if ((IFIX(Tracing_message_level) > (SI_Long)2L || 
	    IFIX(Breakpoint_level) > (SI_Long)2L) &&  
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
		  twrite_beginning_of_wide_string(array_constant_74,
			  FIX((SI_Long)32L));
		  print_role(role);
		  twrite_beginning_of_wide_string(array_constant_75,
			  FIX((SI_Long)35L));
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_detail_trace_message_function(gensymed_symbol);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_inline_evaluate_role_instructions_p, Qallow_inline_evaluate_role_instructions_p);

static Object Qattribute_frame_or_place_reference;  /* attribute-frame-or-place-reference */

static Object Qclass_qualified_name_frame_or_place_reference;  /* class-qualified-name-frame-or-place-reference */

static Object Qelement_frame_or_place_reference;  /* element-frame-or-place-reference */

static Object list_constant_3;     /* # */

static Object Qnth_element;        /* nth-element */

static Object Qevaluate_role;      /* evaluate-role */

/* EMIT-EVALUATE-ROLE-BYTE-CODES */
Object emit_evaluate_role_byte_codes(byte_code_stream,role_constant,
	    domain_count,no_item_allowed_qm,domain_1_item_name_qm,
	    domain_1_type_spec,optimized_role_info)
    Object byte_code_stream, role_constant, domain_count, no_item_allowed_qm;
    Object domain_1_item_name_qm, domain_1_type_spec, optimized_role_info;
{
    Object class_qm, class_specific_attribute_class_qm, attribute_name, temp;
    Object temp_1, instruction_name, index_1;

    x_note_fn_call(205,145);
    if (CONSP(role_constant) && EQ(M_CAR(role_constant),
	    Qattribute_frame_or_place_reference))
	return emit_attribute_frame_or_place_reference_byte_codes(byte_code_stream,
		SECOND(role_constant));
    else if (CONSP(role_constant) && EQ(M_CAR(role_constant),
	    Qclass_qualified_name_frame_or_place_reference)) {
	emit_push_constant_byte_codes(byte_code_stream,
		M_CAR(M_CDR(role_constant)));
	emit_push_constant_byte_codes(byte_code_stream,
		M_CAR(M_CDR(M_CDR(role_constant))));
	return emit_funcall_instruction_byte_codes(2,byte_code_stream,
		Qclass_qualified_name_frame_or_place_reference);
    }
    else if (CONSP(role_constant) && EQ(M_CAR(role_constant),
	    Qelement_frame_or_place_reference))
	return emit_element_frame_or_place_reference_byte_codes(byte_code_stream);
    else if (SYMBOLP(role_constant) && IFIX(domain_count) == (SI_Long)1L 
	    &&  !TRUEP(no_item_allowed_qm)) {
	if (class_type_specification_p(domain_1_type_spec))
	    class_qm = type_specification_class_function(domain_1_type_spec);
	else if (type_specifications_could_intersect_p(domain_1_type_spec,
		list_constant_3))
	    class_qm = Nil;
	else
	    class_qm = Qitem;
	return emit_cached_attribute_value_byte_codes(byte_code_stream,
		role_constant,domain_1_item_name_qm,class_qm,Nil);
    }
    else if (LISTP(role_constant) && EQ(FIRST(role_constant),
	    Qclass_qualified_name) && IFIX(domain_count) == (SI_Long)1L && 
	     !TRUEP(no_item_allowed_qm)) {
	if (class_type_specification_p(domain_1_type_spec))
	    class_qm = type_specification_class_function(domain_1_type_spec);
	else if (type_specifications_could_intersect_p(domain_1_type_spec,
		list_constant_3))
	    class_qm = Nil;
	else
	    class_qm = Qitem;
	class_specific_attribute_class_qm = SECOND(role_constant);
	attribute_name = THIRD(role_constant);
	return emit_cached_attribute_value_byte_codes(byte_code_stream,
		attribute_name,domain_1_item_name_qm,class_qm,
		class_specific_attribute_class_qm);
    }
    else if (CONSP(role_constant) && EQ(M_CAR(role_constant),Qnth_element) 
	    &&  !TRUEP(no_item_allowed_qm) &&  !TRUEP(optimized_role_info))
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)123L));
    else {
	if (optimized_role_info) {
	    if (CONSP(role_constant)) {
		temp = CAR(role_constant);
		if (SYMBOLP(temp) && EQ(CAR(role_constant),Qrole_server)) {
		    temp_1 = CAR(optimized_role_info);
		    M_CADR(role_constant) = temp_1;
		}
		else {
		    temp = CAR(role_constant);
		    if (SYMBOLP(temp)) {
			temp_1 = CAR(optimized_role_info);
			M_CAR(role_constant) = temp_1;
		    }
		}
	    }
	    else
		role_constant = CAR(optimized_role_info);
	}
	instruction_name = optimized_role_info && 
		CADR(optimized_role_info) && 
		Allow_inline_evaluate_role_instructions_p ? 
		CADR(optimized_role_info) : Qevaluate_role;
	write_byte_code_to_stream(byte_code_stream,
		op_code_for_stack_instruction(instruction_name));
	index_1 = 
		register_internal_constant_in_byte_code_stream(byte_code_stream,
		role_constant);
	emit_long_code_constant_to_stream(byte_code_stream,index_1);
	write_byte_code_to_stream(byte_code_stream,domain_count);
	return write_byte_code_to_stream(byte_code_stream,
		no_item_allowed_qm ? FIX((SI_Long)1L) : FIX((SI_Long)0L));
    }
}

/* EMIT-EVALUATE-ROLE-WITH-NO-DOMAIN-BYTE-CODES */
Object emit_evaluate_role_with_no_domain_byte_codes(byte_code_stream,
	    role_constant,no_item_allowed)
    Object byte_code_stream, role_constant, no_item_allowed;
{
    Object index_1;

    x_note_fn_call(205,146);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)46L));
    index_1 = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    role_constant);
    emit_long_code_constant_to_stream(byte_code_stream,index_1);
    return write_byte_code_to_stream(byte_code_stream,no_item_allowed ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

static Object Qsimulator;          /* simulator */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object Qsimulation_info_qm;  /* simulation-info? */

static Object Qsimulated_value;    /* simulated-value */

/* GET-CURRENT-EVALUATION-VALUE-FROM-SIMULATION-ENVIRONMENT */
Object get_current_evaluation_value_from_simulation_environment(variable_or_parameter)
    Object variable_or_parameter;
{
    Object managed_number_or_value, simulated_evaluation_value;
    Object sub_class_bit_vector, temp_1, current_model_runtime_info_qm;
    Object current_model_definition_qm, simulation_info_qm;
    Object model_definition_qm, do_not_update_simulated_value_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(3);

    x_note_fn_call(205,147);
    if (EQ(Current_environment,Qsimulator)) {
	if (Current_model_runtime_info_qm) {
	    if (SIMPLE_VECTOR_P(variable_or_parameter) && 
		    EQ(ISVREF(variable_or_parameter,(SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			{
		managed_number_or_value = ISVREF(variable_or_parameter,
			(SI_Long)1L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    simulated_evaluation_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    simulated_evaluation_value = 
			    aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    simulated_evaluation_value = 
			    copy_text_string(managed_number_or_value);
		else
		    simulated_evaluation_value = managed_number_or_value;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		if (temp)
		    simulated_evaluation_value = 
			    sim_eval_get_evaluation_value_of_variable(variable_or_parameter);
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(variable_or_parameter,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Parameter_class_description,
			    (SI_Long)18L));
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
		    if (temp)
			simulated_evaluation_value = 
				sim_eval_get_evaluation_value_of_parameter(variable_or_parameter);
		    else
			simulated_evaluation_value = Simulation_no_value;
		}
	    }
	    if (EQ(simulated_evaluation_value,Simulation_no_value)) {
		Stack_expiration = Nil;
		temp_1 = Nil;
	    }
	    else
		temp_1 = simulated_evaluation_value;
	}
	else {
	    current_model_runtime_info_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		    1);
	      current_model_definition_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
		      0);
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable_or_parameter,
			Qsimulation_info_qm,Nil);
		model_definition_qm = Nil;
		if (simulation_info_qm) {
		    model_definition_qm = ISVREF(simulation_info_qm,
			    (SI_Long)8L);
		    if (model_definition_qm) {
			Current_model_definition_qm = model_definition_qm;
			Current_model_runtime_info_qm = 
				ISVREF(model_definition_qm,(SI_Long)20L);
		    }
		    else {
			Current_model_definition_qm = Nil;
			Current_model_runtime_info_qm = 
				Main_model_runtime_info;
		    }
		}
		temp = TRUEP(simulation_info_qm);
		if (temp);
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(variable_or_parameter,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Parameter_class_description,
			    (SI_Long)18L));
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
		if (temp) {
		    if (SIMPLE_VECTOR_P(variable_or_parameter) && 
			    EQ(ISVREF(variable_or_parameter,(SI_Long)0L),
			    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
				{
			managed_number_or_value = 
				ISVREF(variable_or_parameter,(SI_Long)1L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    simulated_evaluation_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    simulated_evaluation_value = 
				    aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    simulated_evaluation_value = 
				    copy_text_string(managed_number_or_value);
			else
			    simulated_evaluation_value = 
				    managed_number_or_value;
		    }
		    else {
			sub_class_bit_vector = 
				ISVREF(ISVREF(variable_or_parameter,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Variable_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    simulated_evaluation_value = 
				    sim_eval_get_evaluation_value_of_variable(variable_or_parameter);
			else {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(variable_or_parameter,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Parameter_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				simulated_evaluation_value = 
					sim_eval_get_evaluation_value_of_parameter(variable_or_parameter);
			    else
				simulated_evaluation_value = 
					Simulation_no_value;
			}
		    }
		    if (EQ(simulated_evaluation_value,Simulation_no_value)) {
			Stack_expiration = Nil;
			temp_1 = Nil;
		    }
		    else
			temp_1 = simulated_evaluation_value;
		}
		else
		    temp_1 = Nil;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    else if (EQ(Current_environment,Qsimulated_value)) {
	if (Current_model_runtime_info_qm) {
	    do_not_update_simulated_value_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_simulated_value_qm,Qdo_not_update_simulated_value_qm,do_not_update_simulated_value_qm,
		    0);
	      if (SIMPLE_VECTOR_P(variable_or_parameter) && 
		      EQ(ISVREF(variable_or_parameter,(SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			  {
		  managed_number_or_value = ISVREF(variable_or_parameter,
			  (SI_Long)1L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      simulated_evaluation_value = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      simulated_evaluation_value = 
			      aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else if (text_string_p(managed_number_or_value))
		      simulated_evaluation_value = 
			      copy_text_string(managed_number_or_value);
		  else
		      simulated_evaluation_value = managed_number_or_value;
	      }
	      else {
		  sub_class_bit_vector = 
			  ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Variable_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      simulated_evaluation_value = 
			      sim_eval_get_evaluation_value_of_variable(variable_or_parameter);
		  else {
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(variable_or_parameter,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Parameter_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  simulated_evaluation_value = 
				  sim_eval_get_evaluation_value_of_parameter(variable_or_parameter);
		      else
			  simulated_evaluation_value = Simulation_no_value;
		  }
	      }
	      if (EQ(simulated_evaluation_value,Simulation_no_value)) {
		  Stack_expiration = Nil;
		  temp_1 = Nil;
	      }
	      else
		  temp_1 = simulated_evaluation_value;
	    POP_SPECIAL();
	}
	else {
	    current_model_runtime_info_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		    2);
	      current_model_definition_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
		      1);
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable_or_parameter,
			Qsimulation_info_qm,Nil);
		model_definition_qm = Nil;
		if (simulation_info_qm) {
		    model_definition_qm = ISVREF(simulation_info_qm,
			    (SI_Long)8L);
		    if (model_definition_qm) {
			Current_model_definition_qm = model_definition_qm;
			Current_model_runtime_info_qm = 
				ISVREF(model_definition_qm,(SI_Long)20L);
		    }
		    else {
			Current_model_definition_qm = Nil;
			Current_model_runtime_info_qm = 
				Main_model_runtime_info;
		    }
		}
		temp = TRUEP(simulation_info_qm);
		if (temp);
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(variable_or_parameter,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Parameter_class_description,
			    (SI_Long)18L));
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
		if (temp) {
		    do_not_update_simulated_value_qm = T;
		    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_simulated_value_qm,Qdo_not_update_simulated_value_qm,do_not_update_simulated_value_qm,
			    0);
		      if (SIMPLE_VECTOR_P(variable_or_parameter) && 
			      EQ(ISVREF(variable_or_parameter,(SI_Long)0L),
			      Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
				  {
			  managed_number_or_value = 
				  ISVREF(variable_or_parameter,(SI_Long)1L);
			  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				  == (SI_Long)1L)
			      simulated_evaluation_value = 
				      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				      (SI_Long)0L));
			  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				  == (SI_Long)1L)
			      simulated_evaluation_value = 
				      aref1(managed_number_or_value,
				      FIX((SI_Long)0L));
			  else if (text_string_p(managed_number_or_value))
			      simulated_evaluation_value = 
				      copy_text_string(managed_number_or_value);
			  else
			      simulated_evaluation_value = 
				      managed_number_or_value;
		      }
		      else {
			  sub_class_bit_vector = 
				  ISVREF(ISVREF(variable_or_parameter,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Variable_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_1 = (SI_Long)1L;
			      gensymed_symbol_2 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_1 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol = gensymed_symbol & 
				      gensymed_symbol_1;
			      temp = (SI_Long)0L < gensymed_symbol;
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      simulated_evaluation_value = 
				      sim_eval_get_evaluation_value_of_variable(variable_or_parameter);
			  else {
			      sub_class_bit_vector = 
				      ISVREF(ISVREF(variable_or_parameter,
				      (SI_Long)1L),(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Parameter_class_description,
				      (SI_Long)18L));
			      sub_class_vector_index = 
				      superior_class_bit_number >>  -  - 
				      (SI_Long)3L;
			      if (sub_class_vector_index < 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					  {
				  gensymed_symbol = 
					  UBYTE_8_ISAREF_1(sub_class_bit_vector,
					  sub_class_vector_index);
				  gensymed_symbol_1 = (SI_Long)1L;
				  gensymed_symbol_2 = 
					  superior_class_bit_number & 
					  (SI_Long)7L;
				  gensymed_symbol_1 = gensymed_symbol_1 << 
					  gensymed_symbol_2;
				  gensymed_symbol = gensymed_symbol & 
					  gensymed_symbol_1;
				  temp = (SI_Long)0L < gensymed_symbol;
			      }
			      else
				  temp = TRUEP(Nil);
			      if (temp)
				  simulated_evaluation_value = 
					  sim_eval_get_evaluation_value_of_parameter(variable_or_parameter);
			      else
				  simulated_evaluation_value = 
					  Simulation_no_value;
			  }
		      }
		      if (EQ(simulated_evaluation_value,Simulation_no_value)) {
			  Stack_expiration = Nil;
			  temp_1 = Nil;
		      }
		      else
			  temp_1 = simulated_evaluation_value;
		    POP_SPECIAL();
		}
		else
		    temp_1 = Nil;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    else
	temp_1 = Qnil;
    return VALUES_1(temp_1);
}

static Object string_constant_90;  /* "Error in evaluator.  The out of line evaluator #~a did not exist.  Please ~
				    *    report this G2 internal software error to Gensym Software Support."
				    */

/* FUNCALLED-EVALUATOR-ERROR-MESSAGE */
Object funcalled_evaluator_error_message(evaluator_number)
    Object evaluator_number;
{
    x_note_fn_call(205,148);
    return tformat_stack_error_text_string(2,string_constant_90,
	    evaluator_number);
}

/* EMIT-FUNCALL-EVALUATOR-BYTE-CODES */
Object emit_funcall_evaluator_byte_codes(byte_code_stream,evaluator_number)
    Object byte_code_stream, evaluator_number;
{
    x_note_fn_call(205,149);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)51L));
    return write_byte_code_to_stream(byte_code_stream,evaluator_number);
}

static Object Qfuncalled_instruction_description;  /* funcalled-instruction-description */

static Object string_constant_91;  /* "funcall-instruction emitter" */

static Object string_constant_92;  /* "No instruction description for funcalled-instruction ~a." */

/* EMIT-FUNCALL-INSTRUCTION-BYTE-CODES */
Object emit_funcall_instruction_byte_codes varargs_1(int, n)
{
    Object byte_code_stream, funcalled_instruction_name;
    Object nargs, nresults, description, funcalled_instruction_number;
    Declare_varargs_nonrelocating;

    x_note_fn_call(205,150);
    INIT_ARGS_nonrelocating();
    byte_code_stream = REQUIRED_ARG_nonrelocating();
    funcalled_instruction_name = REQUIRED_ARG_nonrelocating();
    nargs = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    nresults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(funcalled_instruction_name),
	    Qfuncalled_instruction_description);
    funcalled_instruction_number = description ? ISVREF(description,
	    (SI_Long)1L) : Nil;
    if (funcalled_instruction_number) {
	if (nargs)
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)139L));
	else
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)52L));
	write_byte_code_to_stream(byte_code_stream,
		funcalled_instruction_number);
	if (nargs) {
	    write_byte_code_to_stream(byte_code_stream,nresults);
	    return emit_long_code_constant_to_stream(byte_code_stream,nargs);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return compiler_bug(3,string_constant_91,string_constant_92,
		funcalled_instruction_name);
}

static Object Qplace_reference;    /* place-reference */

static Object Qattribute;          /* attribute */

static Object Qaliased_attribute;  /* aliased-attribute */

/* FETCH-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE */
Object fetch_attribute_frame_or_place_reference(item_or_place,
	    pretty_slot_name,class_qualifier_qm,top_of_stack)
    Object item_or_place, pretty_slot_name, class_qualifier_qm, top_of_stack;
{
    Object temp, svref_new_value, temp_1, x2, class_description;
    Object slot_description_qm, gensymed_symbol, ab_loop_list_;
    Object visible_slot_qm, slot_value_qm, frame_value_qm, place_reference_qm;
    Object actual_name_qm, actual_slot_description_qm, gensymed_symbol_1;
    char temp_2;

    x_note_fn_call(205,151);
    if (CONSP(item_or_place) && EQ(M_CDR(item_or_place),Qplace_reference)) {
	temp = M_CAR(item_or_place);
	svref_new_value = slot_value_list_4(Qattribute,pretty_slot_name,
		class_qualifier_qm,ISVREF(M_CAR(item_or_place),(SI_Long)0L));
	SVREF(temp,FIX((SI_Long)0L)) = svref_new_value;
	temp_1 = item_or_place;
    }
    else if (CONSP(item_or_place) && EQ(M_CDR(item_or_place),
	    Qab_structure) && estructure_slot(item_or_place,
	    pretty_slot_name,Nil))
	temp_1 = 
		make_evaluation_place_reference_to_place(slot_value_list_4(Qattribute,
		pretty_slot_name,class_qualifier_qm,
		Qcurrent_computation_frame),item_or_place);
    else {
	if (SIMPLE_VECTOR_P(item_or_place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_place)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_place,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_place,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    class_description = ISVREF(item_or_place,(SI_Long)1L);
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(pretty_slot_name,
		    class_description,class_qualifier_qm);
	    if (slot_description_qm) {
		gensymed_symbol = Nil;
		ab_loop_list_ = ISVREF(slot_description_qm,(SI_Long)9L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		gensymed_symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),Qtype)) {
		    temp_2 = TRUEP(gensymed_symbol);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_2 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    visible_slot_qm = temp_2 ? ( 
		    !TRUEP(do_not_put_slot_in_attribute_tables_p(2,
		    slot_description_qm,T)) ? T : Nil) : Nil;
	    slot_value_qm = visible_slot_qm ? 
		    get_slot_description_value(item_or_place,
		    slot_description_qm) : Qnil;
	    if (SIMPLE_VECTOR_P(slot_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(slot_value_qm,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    frame_value_qm = temp_2 ? slot_value_qm : Nil;
	    if ( !TRUEP(frame_value_qm)) {
		if ( !TRUEP(visible_slot_qm)) {
		    place_reference_qm = 
			    place_reference_of_virtual_attribute_qm(item_or_place,
			    pretty_slot_name);
		    if (place_reference_qm)
			temp_1 = place_reference_qm;
		    else {
			actual_name_qm = 
				get_slot_name_for_alias_if_any(pretty_slot_name,
				item_or_place);
			actual_slot_description_qm = actual_name_qm ? 
				get_slot_description_of_class_description_function(actual_name_qm,
				class_description,class_qualifier_qm) : Qnil;
			if (actual_name_qm && actual_slot_description_qm 
				&& assq_function(Qtype,
				ISVREF(actual_slot_description_qm,
				(SI_Long)9L)) &&  
				!TRUEP(do_not_put_slot_in_attribute_tables_p(2,
				actual_slot_description_qm,T))) {
			    gensymed_symbol = 
				    make_slot_value_list_1(FIX((SI_Long)5L));
			    gensymed_symbol_1 = gensymed_symbol;
			    M_CAR(gensymed_symbol_1) = Qaliased_attribute;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = pretty_slot_name;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = actual_name_qm;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp = ISVREF(actual_slot_description_qm,
				    (SI_Long)3L);
			    M_CAR(gensymed_symbol_1) = temp;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = 
				    Qcurrent_computation_frame;
			    temp_1 = 
				    make_evaluation_place_reference_to_place(gensymed_symbol,
				    item_or_place);
			}
			else
			    temp_1 = 
				    raw_stack_error_named_error(top_of_stack,
				    attribute_returned_no_values_error_1(pretty_slot_name,
				    item_or_place,class_qualifier_qm));
		    }
		}
		else
		    temp_1 = 
			    make_evaluation_place_reference_to_place(slot_value_list_4(Qattribute,
			    pretty_slot_name,ISVREF(slot_description_qm,
			    (SI_Long)3L),Qcurrent_computation_frame),
			    item_or_place);
	    }
	    else if (serve_item_p(frame_value_qm))
		temp_1 = frame_value_qm;
	    else
		temp_1 = raw_stack_error_named_error(top_of_stack,
			attribute_returned_no_values_error_1(pretty_slot_name,
			item_or_place,class_qualifier_qm));
	}
	else
	    temp_1 = raw_stack_error_named_error(top_of_stack,
		    attribute_returned_no_values_error_1(pretty_slot_name,
		    item_or_place,class_qualifier_qm));
    }
    return VALUES_1(temp_1);
}

/* EMIT-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE-BYTE-CODES */
Object emit_attribute_frame_or_place_reference_byte_codes(byte_code_stream,
	    attribute_name_qm)
    Object byte_code_stream, attribute_name_qm;
{
    x_note_fn_call(205,152);
    if (attribute_name_qm)
	emit_push_constant_byte_codes(byte_code_stream,attribute_name_qm);
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)53L));
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qinference_engine;   /* inference-engine */

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-call-g2-struct */

/* RETURN-VALUES-BODY */
Object return_values_body(nargs_init,local_stack,top_of_stack)
    Object nargs_init, local_stack, top_of_stack;
{
    Object register_1, temp, register_2, type_name;
    SI_Long nargs, decff_1_arg, top_of_stack_new_value;
    char temp_1;

    x_note_fn_call(205,153);
    nargs = IFIX(nargs_init);
    register_1 = ISVREF(Current_computation_instance,(SI_Long)12L);
    if ( !TRUEP(register_1) || g2gl_call_invocation_p_function(register_1)) {
	return_from_top_level_procedure_invocation();
	Cached_top_of_stack = top_of_stack;
	reclaim_top_of_stack();
	Current_computation_instance = Nil;
	Cached_fixnum_time_limit_qm = 
		fetch_and_enter_next_current_computation_instance(Priority_of_current_task);
	temp =  !TRUEP(Current_computation_instance) ? T : Nil;
    }
    else if (SIMPLE_VECTOR_P(register_1) && EQ(ISVREF(register_1,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct) && 
	    ISVREF(register_1,(SI_Long)27L)) {
	register_2 = Current_computation_instance;
	exit_computation_context_for_code_body_invocation(register_2,
		FIX((SI_Long)0L),T);
	close_code_body_invocation(register_2);
	Current_computation_activity = FIX((SI_Long)0L);
	Current_computation_component_particulars = Nil;
	Current_computation_frame = ISVREF(register_1,(SI_Long)8L);
	Current_computation_instance = register_1;
	Current_computation_style = Nil;
	Current_environment = Qinference_engine;
	SVREF(register_1,FIX((SI_Long)28L)) = top_of_stack;
	SVREF(register_1,FIX((SI_Long)27L)) = Nil;
	Cached_fixnum_time_limit_qm = Nil;
	temp = Cached_fixnum_time_limit_qm;
    }
    else {
	if (SIMPLE_VECTOR_P(register_1)) {
	    type_name = ISVREF(register_1,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else
	    temp_1 = SIMPLE_VECTOR_P(register_1) ? EQ(ISVREF(register_1,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_rule_instance_g2_struct) :
		     TRUEP(Qnil);
	if (temp_1) {
	    return_stack_values_to_caller(register_1,local_stack,
		    top_of_stack,FIX(nargs),Current_computation_instance);
	    decff_1_arg = nargs;
	    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
	    top_of_stack = FIX(top_of_stack_new_value);
	    register_2 = Current_computation_instance;
	    exit_computation_context_for_code_body_invocation(register_2,
		    FIX((SI_Long)0L),T);
	    close_code_body_invocation(register_2);
	    if (SIMPLE_VECTOR_P(register_1)) {
		type_name = ISVREF(register_1,(SI_Long)0L);
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
		if (temp_1);
		else
		    temp_1 = EQ(type_name,
			    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		Cached_fixnum_time_limit_qm = 
			enter_computation_context_for_invocation(register_1,T);
	    else if (SIMPLE_VECTOR_P(register_1) && EQ(ISVREF(register_1,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_rule_instance_g2_struct))
		Cached_fixnum_time_limit_qm = 
			enter_or_reclaim_rule_instance_context(register_1,T);
	    else
		Cached_fixnum_time_limit_qm = 
			return_values_bad_caller(register_1);
	    temp = Nil;
	}
	else if (SIMPLE_VECTOR_P(register_1) && EQ(ISVREF(register_1,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct)) 
		    {
	    return_stack_values_to_remote_caller(register_1,local_stack,
		    top_of_stack,FIX(nargs),Current_computation_instance);
	    decff_1_arg = nargs;
	    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
	    top_of_stack = FIX(top_of_stack_new_value);
	    close_code_body_invocation(Current_computation_instance);
	    Cached_top_of_stack = top_of_stack;
	    reclaim_top_of_stack();
	    Current_computation_instance = Nil;
	    Cached_fixnum_time_limit_qm = 
		    fetch_and_enter_next_current_computation_instance(Priority_of_current_task);
	    temp =  !TRUEP(Current_computation_instance) ? T : Nil;
	}
	else {
	    decff_1_arg = nargs;
	    top_of_stack_new_value = IFIX(top_of_stack) - decff_1_arg;
	    top_of_stack = FIX(top_of_stack_new_value);
	    Cached_top_of_stack = top_of_stack;
	    reclaim_top_of_stack();
	    Current_computation_instance = Nil;
	    Cached_fixnum_time_limit_qm = 
		    fetch_and_enter_next_current_computation_instance(Priority_of_current_task);
	    temp =  !TRUEP(Current_computation_instance) ? T : Nil;
	}
    }
    return VALUES_1(temp);
}

/* HANDLE-STACK-FOR-CALL-FROM-RULE-ANTECEDENT */
Object handle_stack_for_call_from_rule_antecedent(stack,top_of_stack,
	    values_count,returning_code_body_invocation)
    Object stack, top_of_stack, values_count, returning_code_body_invocation;
{
    x_note_fn_call(205,154);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_start_time, Qprocedure_start_time);

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_end_time, Qprocedure_end_time);

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_current_time, Qprocedure_current_time);

DEFINE_VARIABLE_WITH_SYMBOL(Execution_time_stack, Qexecution_time_stack);

static Object Qab_gensym;          /* gensym */

/* HANDLE-PROCEDURE-TIME-RETURN-VALUES */
Object handle_procedure_time_return_values(fixnum_time_limit_qm)
    Object fixnum_time_limit_qm;
{
    Object current_time, start_time, gensym_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2, temp_1;
    SI_Long difference, gensymed_symbol, incff_1_arg;
    SI_Long procedure_current_time_new_value;

    x_note_fn_call(205,155);
    if ( !TRUEP(ISVREF(Miscellaneous_parameters,(SI_Long)32L))) {
	current_time = c_native_clock_ticks_or_cache(Nil,Nil);
	start_time = Procedure_start_time;
	if (FIXNUM_GE(current_time,start_time))
	    difference = IFIX(FIXNUM_MINUS(current_time,start_time));
	else {
	    gensymed_symbol = IFIX(FIXNUM_MINUS(current_time,start_time));
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    difference = gensymed_symbol + (SI_Long)1L;
	}
	Procedure_end_time = current_time;
	incff_1_arg = difference;
	procedure_current_time_new_value = IFIX(Procedure_current_time) + 
		incff_1_arg;
	Procedure_current_time = FIX(procedure_current_time_new_value);
	if (difference >= IFIX(fixnum_time_limit_qm))
	    signal_procedure_time_error(Procedure_current_time,
		    Cached_top_of_stack);
	Procedure_start_time = current_time;
	gensym_pop_store = Nil;
	cons_1 = Execution_time_stack;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Execution_time_stack = next_cons;
	Procedure_current_time = gensym_pop_store;
	temp_1 = Procedure_current_time;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RETURN-VALUES-BAD-CALLER */
Object return_values_bad_caller(caller)
    Object caller;
{
    x_note_fn_call(205,156);
    error((SI_Long)2L,
	    "Return-values has caller ~a that is not a code-body-invocation or rule-instance.",
	    caller);
    return VALUES_1(Nil);
}

static Object string_constant_93;  /* "At most 255 values can be returned, ~a in this statement." */

/* EMIT-RETURN-VALUES-BYTE-CODES */
Object emit_return_values_byte_codes(byte_code_stream,values_to_return)
    Object byte_code_stream, values_to_return;
{
    x_note_fn_call(205,157);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)55L));
    if (IFIX(values_to_return) > (SI_Long)255L)
	return compiler_error(2,string_constant_93,values_to_return);
    else
	return write_byte_code_to_stream(byte_code_stream,values_to_return);
}

static Object string_constant_94;  /* "Procedure ~NF is requesting ~a values and ~NF can return only ~a." */

/* NOT-ENOUGH-VALUES-ERROR-MESSAGE */
Object not_enough_values_error_message(caller,requested,
	    returning_code_body_invocation,supplied)
    Object caller, requested, returning_code_body_invocation, supplied;
{
    x_note_fn_call(205,158);
    return tformat_stack_error_text_string(5,string_constant_94,
	    ISVREF(ISVREF(caller,(SI_Long)11L),(SI_Long)23L),requested,
	    ISVREF(ISVREF(returning_code_body_invocation,(SI_Long)11L),
	    (SI_Long)23L),supplied);
}

/* RETURN-FROM-TOP-LEVEL-PROCEDURE-INVOCATION */
Object return_from_top_level_procedure_invocation()
{
    Object temp;

    x_note_fn_call(205,159);
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(Current_computation_frame))) {
	    temp = Current_computation_frame;
	    issue_tracing_and_breakpoint_exit_message(temp,
		    return_from_top_level_procedure_invocation_exit_message());
	}
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    close_code_body_invocation(Current_computation_instance);
    return VALUES_1(Nil);
}

static Object array_constant_76;   /* # */

static Object array_constant_77;   /* # */

/* RETURN-FROM-TOP-LEVEL-PROCEDURE-INVOCATION-EXIT-MESSAGE */
Object return_from_top_level_procedure_invocation_exit_message()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object procedure_invocation, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,160);
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
	      procedure_invocation = ISVREF(Current_computation_instance,
		      (SI_Long)11L);
	      twrite_beginning_of_wide_string(array_constant_76,
		      FIX((SI_Long)15L));
	      write_procedure_invocation_instance_from_slot(procedure_invocation,
		      Nil);
	      twrite_beginning_of_wide_string(array_constant_77,
		      FIX((SI_Long)35L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* RETURN-STACK-VALUES-TO-CALLER */
Object return_stack_values_to_caller(caller,stack,top_of_stack,
	    values_count,returning_code_body_invocation)
    Object caller, stack, top_of_stack, values_count;
    Object returning_code_body_invocation;
{
    Object returning_procedure_invocation, returning_procedure;
    Object calling_environment, target_position, target_count, exit_message_qm;
    Object argument_strings_for_trace, new_value, x2, temp_1, svref_new_value;
    SI_Long stack_index, target_index, ab_loop_bind_;
    char temp;

    x_note_fn_call(205,161);
    returning_procedure_invocation = ISVREF(returning_code_body_invocation,
	    (SI_Long)11L);
    returning_procedure = ISVREF(returning_procedure_invocation,(SI_Long)23L);
    calling_environment = ISVREF(caller,(SI_Long)2L);
    target_position = ISVREF(caller,(SI_Long)5L);
    target_count = ISVREF(caller,(SI_Long)6L);
    exit_message_qm = Saved_warning_level && (IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L) && 
	    ISVREF(Debugging_parameters,(SI_Long)22L) ? ( 
	    !TRUEP(in_order_p(returning_procedure)) ? T : Nil) : Qnil;
    argument_strings_for_trace = Nil;
    if (FIXNUM_GT(target_count,values_count))
	raw_stack_error_named_error(top_of_stack,
		not_enough_values_error_message(caller,target_count,
		returning_code_body_invocation,values_count));
    if ( !(IFIX(FIXNUM_LOGAND(Procedure_invalidates_environment_union_mask,
	    ISVREF(returning_procedure,(SI_Long)29L))) == (SI_Long)0L))
	validate_computation_instance_environment(caller,Nil,Nil);
    update_code_body_invocation_frame_serial_number(caller);
    if (exit_message_qm) {
	new_value = Nil;
	stack_index = IFIX(FIXNUM_ADD1(FIXNUM_MINUS(top_of_stack,
		values_count)));
	target_index = IFIX(target_position);
	ab_loop_bind_ = IFIX(FIXNUM_ADD(target_position,target_count));
      next_loop:
	if (target_index >= ab_loop_bind_)
	    goto end_loop;
	new_value = ISVREF(stack,stack_index);
	ISVREF(calling_environment,target_index) = new_value;
	if (SIMPLE_VECTOR_P(new_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(new_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(new_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = temp ? tformat_text_string(2,string_constant_3,new_value) 
		: write_evaluation_value_to_text_string(new_value);
	argument_strings_for_trace = proc_cons_1(temp_1,
		argument_strings_for_trace);
	stack_index = stack_index + (SI_Long)1L;
	target_index = target_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
      next_loop_1:
	if (stack_index > IFIX(top_of_stack))
	    goto end_loop_1;
	new_value = ISVREF(stack,stack_index);
	if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
		SIMPLE_VECTOR_P(new_value)))
	    reclaim_if_evaluation_value_1(new_value);
	stack_index = stack_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else {
	new_value = Nil;
	stack_index = IFIX(FIXNUM_ADD1(FIXNUM_MINUS(top_of_stack,
		values_count)));
	target_index = IFIX(target_position);
	ab_loop_bind_ = IFIX(FIXNUM_ADD(target_position,target_count));
      next_loop_2:
	if (target_index >= ab_loop_bind_)
	    goto end_loop_2;
	svref_new_value = ISVREF(stack,stack_index);
	ISVREF(calling_environment,target_index) = svref_new_value;
	stack_index = stack_index + (SI_Long)1L;
	target_index = target_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
      next_loop_3:
	if (stack_index > IFIX(top_of_stack))
	    goto end_loop_3;
	new_value = ISVREF(stack,stack_index);
	if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
		SIMPLE_VECTOR_P(new_value)))
	    reclaim_if_evaluation_value_1(new_value);
	stack_index = stack_index + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
    }
    if (exit_message_qm) {
	if (Saved_warning_level) {
	    if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		    IFIX(Tracing_message_level) > (SI_Long)0L) && 
		    ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		    !TRUEP(in_order_p(returning_procedure)))
		issue_tracing_and_breakpoint_exit_message(returning_procedure,
			return_to_procedure_caller_exit_message(returning_procedure_invocation,
			nreverse(argument_strings_for_trace),caller));
	    Warning_message_level = Saved_warning_level;
	    Tracing_message_level = Saved_tracing_level;
	    Breakpoint_level = Saved_breakpoint_level;
	    Source_stepping_level = Saved_source_stepping_level;
	}
    }
    else if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(returning_procedure)))
	    issue_tracing_and_breakpoint_exit_message(returning_procedure,Nil);
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    return VALUES_1(Nil);
}

static Object array_constant_78;   /* # */

static Object array_constant_79;   /* # */

static Object array_constant_80;   /* # */

/* RETURN-TO-PROCEDURE-CALLER-EXIT-MESSAGE */
Object return_to_procedure_caller_exit_message(procedure_invocation,
	    return_value_strings,caller)
    Object procedure_invocation, return_value_strings, caller;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_1, ab_loop_list_, first_time_qm, ab_loop_iter_flag_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,162);
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
	      Forgive_long_procedure_instruction_qm = T;
	      twrite_beginning_of_wide_string(array_constant_78,
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
		  twrite_beginning_of_wide_string(array_constant_9,
			  FIX((SI_Long)2L));
	      twrite_general_string(string_1);
	      reclaim_text_string(string_1);
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop;
	    end_loop:;
	      reclaim_proc_list_1(return_value_strings);
	      twrite_beginning_of_wide_string(array_constant_79,
		      FIX((SI_Long)7L));
	      write_procedure_invocation_instance_from_slot(procedure_invocation,
		      Nil);
	      twrite_beginning_of_wide_string(array_constant_80,
		      FIX((SI_Long)4L));
	      write_procedure_invocation_instance_from_slot(ISVREF(caller,
		      (SI_Long)11L),Nil);
	      twrite_character(FIX((SI_Long)46L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* HANDLE-PROCEDURE-TIME-CALL */
Object handle_procedure_time_call()
{
    Object current_time, start_time, temp;
    SI_Long difference, gensymed_symbol, incff_1_arg;
    SI_Long procedure_current_time_new_value;

    x_note_fn_call(205,163);
    if ( !TRUEP(ISVREF(Miscellaneous_parameters,(SI_Long)32L))) {
	current_time = c_native_clock_ticks_or_cache(Nil,Nil);
	start_time = Procedure_start_time;
	if (FIXNUM_GE(current_time,start_time))
	    difference = IFIX(FIXNUM_MINUS(current_time,start_time));
	else {
	    gensymed_symbol = IFIX(FIXNUM_MINUS(current_time,start_time));
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    difference = gensymed_symbol + (SI_Long)1L;
	}
	Procedure_end_time = current_time;
	incff_1_arg = difference;
	procedure_current_time_new_value = IFIX(Procedure_current_time) + 
		incff_1_arg;
	Procedure_current_time = FIX(procedure_current_time_new_value);
	Execution_time_stack = gensym_cons_1(Procedure_current_time,
		Execution_time_stack);
	Procedure_start_time = current_time;
	Procedure_current_time = FIX((SI_Long)0L);
	temp = Procedure_current_time;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qcall;               /* call */

static Object Kawaiting_lock;      /* :awaiting-lock */

/* SWITCH-CONTEXT-FOR-PROCEDURE-CALL */
Object switch_context_for_procedure_call(procedure,arg_count,return_count,
	    local_stack,top_of_stack,return_program_counter,
	    arguments_known_to_be_correct_p_qm)
    Object procedure, arg_count, return_count, local_stack, top_of_stack;
    Object return_program_counter, arguments_known_to_be_correct_p_qm;
{
    Object new_code_body_invocation, type_name, svref_arg_1;
    Object ready_to_execute_qm, temp_1;
    char temp;

    x_note_fn_call(205,164);
    new_code_body_invocation = 
	    generate_procedure_and_code_body_invocation_in_place(procedure,
	    Current_computation_instance,local_stack,top_of_stack,
	    arg_count,Evaluating_simulator_procedure_qm,Nil,top_of_stack,
	    arguments_known_to_be_correct_p_qm,Qcall,
	    ISVREF(Current_computation_instance,(SI_Long)21L));
    if (SIMPLE_VECTOR_P(new_code_body_invocation)) {
	type_name = ISVREF(new_code_body_invocation,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_2(Kerror,new_code_body_invocation);
    svref_arg_1 = Current_computation_instance;
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = return_count;
    exit_computation_context_for_code_body_invocation(Current_computation_instance,
	    return_program_counter,T);
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(Current_computation_frame)))
	    issue_tracing_and_breakpoint_exit_message(Current_computation_frame,
		    Nil);
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    ready_to_execute_qm = 
	    queue_invocation_for_lock_if_necessary(new_code_body_invocation);
    if (ready_to_execute_qm) {
	temp_1 = 
		enter_computation_context_for_invocation(new_code_body_invocation,
		T);
	return VALUES_2(T,temp_1);
    }
    else
	return VALUES_2(Kawaiting_lock,Nil);
}

static Object array_constant_81;   /* # */

static Object array_constant_82;   /* # */

/* CALL-PROCEDURE-ENTER-TRACING-CONTEXT-MESSAGE */
Object call_procedure_enter_tracing_context_message(new_procedure_invocation)
    Object new_procedure_invocation;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(205,165);
    Forgive_long_procedure_instruction_qm = T;
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
	      twrite_beginning_of_wide_string(array_constant_81,
		      FIX((SI_Long)18L));
	      write_procedure_invocation_instance_from_slot(new_procedure_invocation,
		      Nil);
	      twrite_beginning_of_wide_string(array_constant_82,
		      FIX((SI_Long)1L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_95;  /* "Attempted to call a remote procedure across ~NF, but could not because ~
				    *    it does not have either the G2-TO-G2-DATA-INTERFACE nor the ~
				    *    GSI-INTERFACE capability, and so cannot be a pathway for ~
				    *    a remote procedure call."
				    */

/* RPC-NOT-AN-INTERFACE-ERROR-MESSAGE */
Object rpc_not_an_interface_error_message(non_icp_interface)
    Object non_icp_interface;
{
    x_note_fn_call(205,166);
    return tformat_stack_error_text_string(2,string_constant_95,
	    non_icp_interface);
}

static Object string_constant_96;  /* "Calling remote procedure ~NF(" */

static Object string_constant_97;  /* ") across ~NF." */

/* WRITE-MAJOR-TRACE-OF-RPC-CALL */
Object write_major_trace_of_rpc_call(remote_procedure,argument_list,
	    icp_interface)
    Object remote_procedure, argument_list, icp_interface;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,167);
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
		  Forgive_long_procedure_instruction_qm = T;
		  tformat(2,string_constant_96,remote_procedure);
		  write_procedure_argument_list(argument_list);
		  tformat(2,string_constant_97,icp_interface);
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

/* EMIT-JUMP-BYTE-CODES */
Object emit_jump_byte_codes(byte_code_stream,code_bodies,target_tag)
    Object byte_code_stream, code_bodies, target_tag;
{
    x_note_fn_call(205,168);
    register_byte_code_tag_resolution_point(byte_code_stream,target_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)60L));
    emit_long_code_constant_to_stream(byte_code_stream,code_bodies);
    return emit_long_code_constant_to_stream(byte_code_stream,
	    FIX((SI_Long)0L));
}

/* BC-JUMP-RESOLVER */
Object bc_jump_resolver(byte_code_stream,byte_vector,pc,tag)
    Object byte_code_stream, byte_vector, pc, tag;
{
    Object code_body_entry, limit, count_1, temp, temp_1;

    x_note_fn_call(205,169);
    code_body_entry = Current_code_body_entry;
    limit = long_code_constant_in_byte_vector(byte_vector,FIXNUM_ADD1(pc));
    count_1 = FIX((SI_Long)0L);
    for ( ; !NUM_GE(count_1,limit); count_1 = add1(count_1))
      count_2: {
	code_body_entry = nth(ISVREF(code_body_entry,(SI_Long)4L),
		Code_body_entries_in_compilation);
    }
    temp = FIX(IFIX(pc) + (SI_Long)3L);
    temp_1 = instruction_address_for_tag(tag,T);
    setf_long_code_constant(byte_vector,temp,entry_point_number(temp_1,
	    code_body_entry));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* ABORT-CALLED-CODE-BODIES-FUNCTION */
Object abort_called_code_bodies_function()
{
    Object called_code_bodies, called_code_bodies_copy, code_bodies_tail;
    Object code_body, code_bodies_next_tail, eval_cons, temp, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(205,170);
    called_code_bodies = ISVREF(Current_computation_instance,(SI_Long)13L);
    if (called_code_bodies) {
	called_code_bodies_copy = 
		copy_list_using_eval_conses_1(called_code_bodies);
	code_bodies_tail = called_code_bodies_copy;
	code_body = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
	  code_bodies_next_tail = Nil;
	next_loop:
	  Code_body = M_CAR(code_bodies_tail);
	  code_bodies_next_tail = M_CDR(code_bodies_tail);
	  abort_code_body_invocation(Code_body);
	  if ( !TRUEP(code_bodies_next_tail))
	      goto end_loop;
	  code_bodies_tail = code_bodies_next_tail;
	  goto next_loop;
	end_loop:
	  if (called_code_bodies_copy &&  !((SI_Long)0L == 
		  inline_debugging_consing())) {
	      eval_cons = called_code_bodies_copy;
	    next_loop_1:
	      inline_note_reclaim_cons(eval_cons,Qeval);
	      if (EQ(eval_cons,code_bodies_tail))
		  goto end_1;
	      else if ( !TRUEP(eval_cons))
		  goto end_1;
	      else
		  eval_cons = CDR(eval_cons);
	      goto next_loop_1;
	    end_loop_1:
	    end_1:;
	  }
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = called_code_bodies_copy;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = code_bodies_tail;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = called_code_bodies_copy;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = code_bodies_tail;
	  }
	  M_CDR(code_bodies_tail) = Nil;
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* EMIT-OPEN-ROLE-ITERATION-NO-DOMAIN-BYTE-CODES */
Object emit_open_role_iteration_no_domain_byte_codes(byte_code_stream,role,
	    no_values_tag)
    Object byte_code_stream, role, no_values_tag;
{
    x_note_fn_call(205,171);
    register_byte_code_tag_resolution_point(byte_code_stream,no_values_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)63L));
    emit_long_code_constant_to_stream(byte_code_stream,
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    role));
    return emit_long_code_constant_to_stream(byte_code_stream,
	    FIX((SI_Long)0L));
}

/* BC-OPEN-ROLE-ITERATION-NO-DOMAIN-RESOLVER */
Object bc_open_role_iteration_no_domain_resolver(byte_code_stream,
	    byte_vector,pc,tag)
    Object byte_code_stream, byte_vector, pc, tag;
{
    Object temp;

    x_note_fn_call(205,172);
    temp = FIX(IFIX(pc) + (SI_Long)3L);
    setf_long_code_constant(byte_vector,temp,
	    instruction_address_for_tag(tag,Nil));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_98;  /* "open role iteration emitter" */

static Object string_constant_99;  /* "Iterations can only handle zero or one domain roles, not ~a domains." */

/* EMIT-OPEN-ROLE-ITERATION-BYTE-CODES */
Object emit_open_role_iteration_byte_codes(byte_code_stream,role,
	    no_values_tag,domain_count)
    Object byte_code_stream, role, no_values_tag, domain_count;
{
    x_note_fn_call(205,173);
    if (IFIX(domain_count) != (SI_Long)0L && IFIX(domain_count) != (SI_Long)1L)
	compiler_bug(3,string_constant_98,string_constant_99,domain_count);
    register_byte_code_tag_resolution_point(byte_code_stream,no_values_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)64L));
    emit_long_code_constant_to_stream(byte_code_stream,
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    role));
    emit_long_code_constant_to_stream(byte_code_stream,FIX((SI_Long)0L));
    return write_byte_code_to_stream(byte_code_stream,domain_count);
}

/* BC-OPEN-ROLE-ITERATION-RESOLVER */
Object bc_open_role_iteration_resolver(byte_code_stream,byte_vector,pc,tag)
    Object byte_code_stream, byte_vector, pc, tag;
{
    Object temp;

    x_note_fn_call(205,174);
    temp = FIX(IFIX(pc) + (SI_Long)3L);
    setf_long_code_constant(byte_vector,temp,
	    instruction_address_for_tag(tag,Nil));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-SERVE-NEXT-ITERATION-VALUE-BYTE-CODES */
Object emit_serve_next_iteration_value_byte_codes(byte_code_stream,
	    var_spot,no_values_tag)
    Object byte_code_stream, var_spot, no_values_tag;
{
    x_note_fn_call(205,175);
    emit_push_from_surrounding_local_var_byte_codes(byte_code_stream,var_spot);
    register_byte_code_tag_resolution_point(byte_code_stream,no_values_tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)65L));
    return emit_long_code_constant_to_stream(byte_code_stream,
	    FIX((SI_Long)0L));
}

/* BC-SERVE-NEXT-ITERATION-VALUE-RESOLVER */
Object bc_serve_next_iteration_value_resolver(byte_code_stream,byte_vector,
	    pc,tag)
    Object byte_code_stream, byte_vector, pc, tag;
{
    Object temp;

    x_note_fn_call(205,176);
    temp = FIXNUM_ADD1(pc);
    setf_long_code_constant(byte_vector,temp,
	    instruction_address_for_tag(tag,Nil));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* EMIT-CLOSE-ITERATION-BYTE-CODES */
Object emit_close_iteration_byte_codes(byte_code_stream,var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,177);
    emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot);
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)66L));
}

/* EMIT-CALL-CODE-BODY-BYTE-CODES */
Object emit_call_code_body_byte_codes(byte_code_stream,code_body_number,
	    argument_count)
    Object byte_code_stream, code_body_number, argument_count;
{
    x_note_fn_call(205,178);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)68L));
    write_byte_code_to_stream(byte_code_stream,code_body_number);
    return write_byte_code_to_stream(byte_code_stream,argument_count);
}

/* EMIT-CALL-SCHEDULED-CODE-BODY-BYTE-CODES */
Object emit_call_scheduled_code_body_byte_codes(byte_code_stream,
	    code_body_number,argument_count)
    Object byte_code_stream, code_body_number, argument_count;
{
    x_note_fn_call(205,179);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)69L));
    write_byte_code_to_stream(byte_code_stream,code_body_number);
    return write_byte_code_to_stream(byte_code_stream,argument_count);
}

static Object string_constant_100;  /* "Attempted to get a value from ~NF, but it was not a ~a." */

static Object string_constant_101;  /* "Expected some kind of value, but received ~NV." */

/* SIGNAL-COERCE-TO-DATUM-ERROR-MESSAGE */
Object signal_coerce_to_datum_error_message(thing,class_1)
    Object thing, class_1;
{
    Object x2;
    char temp;

    x_note_fn_call(205,180);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    return tformat_stack_error_text_string(3,temp ? string_constant_100 : 
	    string_constant_101,thing,class_1);
}

/* THING-IS-VARIABLE-OR-PARAMETER-P */
Object thing_is_variable_or_parameter_p(thing)
    Object thing;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(205,181);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EMIT-COERCE-TO-DATUM-OR-UNKNOWN-BYTE-CODES */
Object emit_coerce_to_datum_or_unknown_byte_codes(byte_code_stream,
	    allow_no_item_qm)
    Object byte_code_stream, allow_no_item_qm;
{
    x_note_fn_call(205,182);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)75L));
    return write_byte_code_to_stream(byte_code_stream,allow_no_item_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

/* THING-IS-PARAMETER-P */
Object thing_is_parameter_p(thing)
    Object thing;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(205,183);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* EMIT-COERCE-TO-DATUM-BYTE-CODES */
Object emit_coerce_to_datum_byte_codes(byte_code_stream,no_item_allowed_qm)
    Object byte_code_stream, no_item_allowed_qm;
{
    x_note_fn_call(205,184);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)76L));
    return write_byte_code_to_stream(byte_code_stream,no_item_allowed_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

/* EMIT-POP-COPY-DOWN-THE-STACK-BYTE-CODES */
Object emit_pop_copy_down_the_stack_byte_codes(byte_code_stream,count_1)
    Object byte_code_stream, count_1;
{
    Object overflows, remainder_1;
    SI_Long ab_loop_repeat_;
    Object result;

    x_note_fn_call(205,185);
    result = lfloor(count_1,FIX((SI_Long)255L));
    MVS_2(result,overflows,remainder_1);
    ab_loop_repeat_ = IFIX(overflows);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)78L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)255L));
    goto next_loop;
  end_loop:;
    if (IFIX(remainder_1) > (SI_Long)0L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)78L));
	return write_byte_code_to_stream(byte_code_stream,remainder_1);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_102;  /* "An unknown type of current computation instance was encountered in ~
				     *    enable-wake-up-collection.  Please report this stack eval bug to ~
				     *    Gensym software support."
				     */

/* UNKNOWN-INSTANCE-ERROR-MESSAGE */
Object unknown_instance_error_message()
{
    x_note_fn_call(205,186);
    return tformat_stack_error_text_string(1,string_constant_102);
}

static Object string_constant_103;  /* "An unknown type of current computation instance was encountered in ~
				     *        enable-wake-up-collection.  Please report this stack eval bug to ~
				     *        Gensym software support."
				     */

/* UNKNOWN-INSTANCE-WARNING */
Object unknown_instance_warning()
{
    x_note_fn_call(205,187);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(2,FIX((SI_Long)1L),string_constant_103);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_inference_background_collection_g2_struct;  /* g2-defstruct-structure-name::inference-background-collection-g2-struct */

/* OPEN-WAKE-UP-COLLECTION-FUNCTION */
Object open_wake_up_collection_function(top_of_stack_qm)
    Object top_of_stack_qm;
{
    Object wake_ups, wake_up_holder, type_name, svref_arg_1, temp_1, variable;
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(205,188);
    wake_ups = Nil;
    wake_up_holder = Nil;
    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	wake_ups = ISVREF(Current_computation_instance,(SI_Long)14L);
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)14L)) = Nil;
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)15L)) = wake_ups;
	wake_up_holder = Current_computation_instance;
	temp_1 = Nil;
    }
    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	wake_ups = ISVREF(Current_computation_instance,(SI_Long)17L);
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)17L)) = Nil;
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)23L)) = wake_ups;
	wake_up_holder = Current_computation_instance;
	temp_1 = Nil;
    }
    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct)) {
	variable = ISVREF(Current_computation_instance,(SI_Long)8L);
	wake_ups = ISVREF(variable,(SI_Long)35L);
	ISVREF(variable,(SI_Long)35L) = Nil;
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)11L)) = wake_ups;
	wake_up_holder = variable;
	temp_1 = Nil;
    }
    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_inference_background_collection_g2_struct)) 
		{
	wake_ups = ISVREF(Current_computation_instance,(SI_Long)4L);
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = wake_ups;
	wake_up_holder = Current_computation_instance;
	temp_1 = Nil;
    }
    else {
	if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_instance)) 
		> (SI_Long)2L &&  !EQ(ISVREF(Current_computation_instance,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(Current_computation_instance,(SI_Long)1L);
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
	if (temp) {
	    wake_ups = ISVREF(Current_computation_instance,(SI_Long)8L);
	    svref_arg_1 = Current_computation_instance;
	    ISVREF(svref_arg_1,(SI_Long)8L) = Nil;
	    svref_arg_1 = Current_computation_instance;
	    ISVREF(svref_arg_1,(SI_Long)12L) = wake_ups;
	    wake_up_holder = Current_computation_instance;
	    temp_1 = Nil;
	}
	else if (top_of_stack_qm)
	    temp_1 = unknown_instance_error_message();
	else
	    temp_1 = unknown_instance_warning();
    }
    if (wake_ups)
	remove_wake_ups_postponing_clean_up(wake_up_holder,wake_ups);
    return VALUES_1(temp_1);
}

/* SET-WAKE-UPS-FUNCTION */
Object set_wake_ups_function(top_of_stack_qm)
    Object top_of_stack_qm;
{
    Object interesting_variables, variable_qm, already_interesting_variables;
    Object type_name, svref_arg_1, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(205,189);
    interesting_variables = Variables_that_did_not_have_values;
    variable_qm = SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct) ? 
	    ISVREF(Current_computation_instance,(SI_Long)8L) : Nil;
    if (interesting_variables) {
	Variables_that_did_not_have_values = Nil;
	set_pending_wake_ups(variable_qm ? variable_qm : 
		Current_computation_instance,interesting_variables);
	if (variable_qm) {
	    already_interesting_variables = ISVREF(variable_qm,(SI_Long)35L);
	    if (already_interesting_variables)
		interesting_variables = nconc2(interesting_variables,
			already_interesting_variables);
	    ISVREF(variable_qm,(SI_Long)35L) = interesting_variables;
	    return VALUES_1(Nil);
	}
	else {
	    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
		type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
		temp = EQ(type_name,
			Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
		if (temp);
		else
		    temp = EQ(type_name,
			    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		already_interesting_variables = 
			ISVREF(Current_computation_instance,(SI_Long)14L);
		if (already_interesting_variables)
		    interesting_variables = nconc2(interesting_variables,
			    already_interesting_variables);
		svref_arg_1 = Current_computation_instance;
		SVREF(svref_arg_1,FIX((SI_Long)14L)) = interesting_variables;
		return VALUES_1(Nil);
	    }
	    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
		already_interesting_variables = 
			ISVREF(Current_computation_instance,(SI_Long)17L);
		if (already_interesting_variables)
		    interesting_variables = nconc2(interesting_variables,
			    already_interesting_variables);
		svref_arg_1 = Current_computation_instance;
		SVREF(svref_arg_1,FIX((SI_Long)17L)) = interesting_variables;
		return VALUES_1(Nil);
	    }
	    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		    Qg2_defstruct_structure_name_inference_background_collection_g2_struct)) 
			{
		already_interesting_variables = 
			ISVREF(Current_computation_instance,(SI_Long)4L);
		if (already_interesting_variables)
		    interesting_variables = nconc2(interesting_variables,
			    already_interesting_variables);
		svref_arg_1 = Current_computation_instance;
		SVREF(svref_arg_1,FIX((SI_Long)4L)) = interesting_variables;
		return VALUES_1(Nil);
	    }
	    else {
		if (SIMPLE_VECTOR_P(Current_computation_instance) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_instance)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(Current_computation_instance,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(Current_computation_instance,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(G2_expression_cell_class_description,
			    (SI_Long)18L));
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    already_interesting_variables = 
			    ISVREF(Current_computation_instance,(SI_Long)8L);
		    if (already_interesting_variables)
			interesting_variables = 
				nconc2(interesting_variables,
				already_interesting_variables);
		    svref_arg_1 = Current_computation_instance;
		    ISVREF(svref_arg_1,(SI_Long)8L) = interesting_variables;
		    return VALUES_1(Nil);
		}
		else if (top_of_stack_qm)
		    return unknown_instance_error_message();
		else
		    return raw_stack_error_named_error(top_of_stack_qm,
			    unknown_instance_error_message());
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_104;  /* "An unknown type of current computation instance was encountered in ~
				     *             clean-up-wake-ups-state-if-any.  Please report this stack eval ~
				     *             bug to Gensym software support."
				     */

/* CLEAN-UP-WAKE-UPS-STATE-IF-ANY */
Object clean_up_wake_ups_state_if_any()
{
    Object computation_instance, type_name, x2, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(205,190);
    clear_pending_wake_ups();
    computation_instance = Current_computation_instance;
    if (computation_instance) {
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
	if (temp) {
	    perform_postponed_clean_ups(computation_instance,
		    ISVREF(computation_instance,(SI_Long)15L));
	    SVREF(computation_instance,FIX((SI_Long)15L)) = Nil;
	}
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	    perform_postponed_clean_ups(computation_instance,
		    ISVREF(computation_instance,(SI_Long)23L));
	    SVREF(computation_instance,FIX((SI_Long)23L)) = Nil;
	}
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_formula_invocation_g2_struct)) {
	    perform_postponed_clean_ups(ISVREF(computation_instance,
		    (SI_Long)8L),ISVREF(computation_instance,(SI_Long)11L));
	    SVREF(computation_instance,FIX((SI_Long)11L)) = Nil;
	}
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct)) 
		    {
	    perform_postponed_clean_ups(computation_instance,
		    ISVREF(computation_instance,(SI_Long)6L));
	    SVREF(computation_instance,FIX((SI_Long)6L)) = Nil;
	}
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
			IFIX(ISVREF(G2_expression_cell_class_description,
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
		perform_postponed_clean_ups(computation_instance,
			ISVREF(computation_instance,(SI_Long)12L));
		ISVREF(computation_instance,(SI_Long)12L) = Nil;
	    }
	    else if (error_occurred_in_simulator_qm());
	    else if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(2,FIX((SI_Long)1L),string_constant_104);
	}
    }
    return VALUES_1(Nil);
}

/* ERROR-OCCURRED-IN-SIMULATOR? */
Object error_occurred_in_simulator_qm()
{
    x_note_fn_call(205,191);
    return VALUES_1(Within_simulator_for_stack_error_qm);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qwake_up_code_body_invocation;  /* wake-up-code-body-invocation */

static Object Qexecute_computation_instance;  /* execute-computation-instance */

/* SCHEDULE-WAIT-FOR-INTERVAL-TASK */
Object schedule_wait_for_interval_task(evaluation_quantity)
    Object evaluation_quantity;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, type_name, old, new_1;
    Object def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    char gensymed_symbol_2, temp_1, svref_new_value_1;
    double float_delay, arg, arg_1, gensymed_symbol_3, aref_new_value;
    Declare_special(1);

    x_note_fn_call(205,192);
    if (FIXNUMP(evaluation_quantity))
	float_delay = (double)IFIX(evaluation_quantity);
    else if (INLINE_LONG_VECTOR_P(evaluation_quantity) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity)) == 
	    (SI_Long)1L) {
	temp = convert_g2longint_to_double(aref1(evaluation_quantity,
		FIX((SI_Long)0L)));
	float_delay = DOUBLE_FLOAT_TO_DOUBLE(temp);
    }
    else
	float_delay = DFLOAT_ISAREF_1(evaluation_quantity,(SI_Long)0L);
    reclaim_evaluation_quantity(evaluation_quantity);
    arg = float_delay;
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	gensymed_symbol = Current_computation_instance;
	gensymed_symbol_1 = Priority_of_current_task;
	gensymed_symbol_2 = (SI_Long)0L != 
		(IFIX(ISVREF(Current_computation_frame,(SI_Long)4L)) & 
		(SI_Long)16777216L);
	gensymed_symbol_3 = DFLOAT_ISAREF_1(gensymed_symbol_2 ? 
		Current_real_time : Current_g2_time,(SI_Long)0L) + float_delay;
	if (SIMPLE_VECTOR_P(gensymed_symbol)) {
	    type_name = ISVREF(gensymed_symbol,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(gensymed_symbol,(SI_Long)7L);
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,gensymed_symbol_3);
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !gensymed_symbol_2;
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    SVREF(task,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = Qwake_up_code_body_invocation;
	    temp_2 = SYMBOL_FUNCTION(Qwake_up_code_body_invocation);
	    SVREF(task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = gensymed_symbol;
	    new_1 = task;
	    if (CAS_SVREF(gensymed_symbol,(SI_Long)7L,old,new_1)) {
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
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
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
	}
	else {
	    old = Nil;
	    new_1 = Nil;
	  next_loop_1:
	    old = ISVREF(gensymed_symbol,(SI_Long)7L);
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,gensymed_symbol_3);
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !gensymed_symbol_2;
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    SVREF(task,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
	    temp_2 = SYMBOL_FUNCTION(Qexecute_computation_instance);
	    SVREF(task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = gensymed_symbol;
	    new_1 = task;
	    if (CAS_SVREF(gensymed_symbol,(SI_Long)7L,old,new_1)) {
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
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = old;
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
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = new_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	  end_2:;
	}
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EMIT-PUSH-NONES-BYTE-CODES */
Object emit_push_nones_byte_codes(byte_code_stream,count_1)
    Object byte_code_stream, count_1;
{
    Object overflows, remainder_1;
    SI_Long ab_loop_repeat_;
    Object result;

    x_note_fn_call(205,193);
    result = lfloor(count_1,FIX((SI_Long)255L));
    MVS_2(result,overflows,remainder_1);
    ab_loop_repeat_ = IFIX(overflows);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)92L));
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)255L));
    goto next_loop;
  end_loop:;
    if (IFIX(remainder_1) == (SI_Long)1L)
	return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)14L));
    else if (IFIX(remainder_1) > (SI_Long)0L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)92L));
	return write_byte_code_to_stream(byte_code_stream,remainder_1);
    }
    else
	return VALUES_1(Qnil);
}

/* EMIT-PUSH-VALUE-OR-NONE-FROM-SURROUNDING-LOCAL-VAR-BYTE-CODES */
Object emit_push_value_or_none_from_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    Object first_index;

    x_note_fn_call(205,194);
    if (EQ(CAR(var_spot),Qstack_frame_var))
	return emit_push_value_or_none_from_stack_frame_var_byte_codes(byte_code_stream,
		var_spot);
    else if (EQ(CAR(var_spot),Qstack_arg))
	return emit_push_value_or_none_from_stack_arg_byte_codes(byte_code_stream,
		var_spot);
    else {
	first_index = SECOND(var_spot);
	if (FIXNUMP(first_index) && IFIX(first_index) < (SI_Long)256L)
	    return emit_push_value_or_none_from_local_var_byte_codes(byte_code_stream,
		    var_spot);
	else {
	    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)93L));
	    emit_long_code_constant_to_stream(byte_code_stream,first_index);
	    return emit_typecode_to_stream(byte_code_stream,var_spot);
	}
    }
}

static Object string_constant_105;  /* "Attempted to call ~NF as a function, but it is an instance of the class ~(~a~)." */

/* NOT-A-FUNCTION-MESSAGE */
Object not_a_function_message(non_function)
    Object non_function;
{
    x_note_fn_call(205,195);
    return tformat_stack_error_text_string(3,string_constant_105,
	    non_function,ISVREF(ISVREF(non_function,(SI_Long)1L),(SI_Long)1L));
}

/* COMPLETE-CALL-FROM-RULE-ANTECEDENT */
Object complete_call_from_rule_antecedent(completion_form)
    Object completion_form;
{
    x_note_fn_call(205,196);
    return VALUES_1(Nil);
}

static Object string_constant_106;  /* "Can't call the function ~NF because its status is not OK." */

static Object Qnever;              /* never */

static Object Qprocedure;          /* procedure */

static Object Qvariable_or_parameter;  /* variable-or-parameter */

static Object Qparameter;          /* parameter */

static Object string_constant_107;  /* "Argument number ~a to the foreign function ~NF was the ~
				     *                value ~NE.  Foreign functions can only accept arguments ~
				     *                of the types quantity, symbol, and text."
				     */

/* COERCE-ARGUMENTS-AND-CALL-FOREIGN-FUNCTION */
Object coerce_arguments_and_call_foreign_function(foreign_function_declaration,
	    local_stack,stack_location,argument_count,top_of_stack)
    Object foreign_function_declaration, local_stack, stack_location;
    Object argument_count, top_of_stack;
{
    Object gensymed_symbol, temp, first_argument_index;
    Object last_argument_index_plus_1, old_stack_expiration, no_item_seen_qm;
    Object argument;
    SI_Long index_1, ab_loop_bind_;
    char unknown_allowed_qm, no_item_allowed_qm, temp_1;

    x_note_fn_call(205,197);
    gensymed_symbol = foreign_function_declaration;
    temp = ISVREF(gensymed_symbol,(SI_Long)8L);
    if ( ! !TRUEP(CAR(temp))) {
	temp = tformat_stack_error_text_string(2,string_constant_106,
		gensymed_symbol);
	return VALUES_2(Nil,temp);
    }
    unknown_allowed_qm = FIXNUM_GE(M_CAR(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)3L)),
	    ISVREF(Inference_engine_parameters,(SI_Long)26L));
    no_item_allowed_qm = FIXNUM_GE(M_CAR(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)2L)),
	    ISVREF(Inference_engine_parameters,(SI_Long)26L));
    first_argument_index = stack_location;
    last_argument_index_plus_1 = FIXNUM_ADD(stack_location,argument_count);
    old_stack_expiration = Stack_expiration;
    no_item_seen_qm = Nil;
    if (unknown_allowed_qm)
	Stack_expiration = Qnever;
    index_1 = IFIX(first_argument_index);
    ab_loop_bind_ = IFIX(last_argument_index_plus_1);
    argument = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    argument = ISVREF(local_stack,index_1);
    gensymed_symbol = argument;
    temp_1 = FIXNUMP(gensymed_symbol);
    if (temp_1);
    else
	temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp_1);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp_1 = EQ(gensymed_symbol,Qtruth_value);
	if (temp_1);
	else
	    temp_1 = TRUEP(memq_function(gensymed_symbol,
		    Defined_evaluation_datum_types));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else if (unknown_allowed_qm) {
	if (thing_is_variable_or_parameter_p(argument)) {
	    Cached_top_of_stack = top_of_stack;
	    argument = EQ(Current_environment,Qinference_engine) || 
		    EQ(Current_environment,Qprocedure) ? 
		    get_current_evaluation_value(argument,Nil) : 
		    get_current_evaluation_value_from_simulation_environment(argument);
	}
	else if ( !TRUEP(argument) && no_item_allowed_qm)
	    Stack_expiration = Nil;
	else
	    raw_stack_error_named_error(top_of_stack,
		    signal_coerce_to_datum_error_message(argument,
		    Qvariable_or_parameter));
    }
    else if (thing_is_parameter_p(argument)) {
	Cached_top_of_stack = top_of_stack;
	argument = EQ(Current_environment,Qinference_engine) || 
		EQ(Current_environment,Qprocedure) ? 
		get_current_evaluation_value(argument,Nil) : 
		get_current_evaluation_value_from_simulation_environment(argument);
    }
    else if ( !TRUEP(argument) && no_item_allowed_qm)
	no_item_seen_qm = T;
    else
	return signal_coerce_to_datum_error_message(argument,Qparameter);
    if (CONSP(argument) && EQ(M_CDR(argument),Qtruth_value)) {
	temp = tformat_stack_error_text_string(4,string_constant_107,
		FIX(index_1 - IFIX(first_argument_index) + (SI_Long)1L),
		foreign_function_declaration,argument);
	return VALUES_2(Nil,temp);
    }
    ISVREF(local_stack,index_1) = argument;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (no_item_seen_qm)
	return VALUES_1(Nil);
    else if (unknown_allowed_qm &&  !TRUEP(Stack_expiration))
	return VALUES_1(Nil);
    else {
	if (unknown_allowed_qm) {
	    if (EQ(Stack_expiration,Qnever))
		Stack_expiration = old_stack_expiration;
	    else if (EQ(old_stack_expiration,Qnever));
	    else if ( !TRUEP(Stack_expiration) ||  
		    !TRUEP(old_stack_expiration))
		Stack_expiration = Nil;
	    else
		Stack_expiration = FIXNUM_MIN(Stack_expiration,
			old_stack_expiration);
	}
	return new_call_foreign_function(foreign_function_declaration,
		local_stack,stack_location,argument_count,top_of_stack);
    }
}

static Object string_constant_108;  /* "Calling ~NF with ~a arguments, it requires 1." */

static Object string_constant_109;  /* "The tabular function ~NF, can not take the value ~NV." */

static Object string_constant_110;  /* "The tabular function ~NF, given the value ~NV, did not return a value." */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

static Object string_constant_111;  /* "~A ~NF ~A, ~A.  ~A ~A.  ~A" */

static Object string_constant_112;  /* "The tabular function" */

static Object string_constant_113;  /* "returned a datum which is not a number" */

static Object string_constant_114;  /* "symbol, truth value, or text" */

static Object string_constant_115;  /* "This is an internal G2 error caused by" */

static Object string_constant_116;  /* "some unusual use of tabular functions" */

static Object string_constant_117;  /* "Please report this bug to Gensym software support." */

/* CALL-TABULAR-FUNCTION */
Object call_tabular_function(tabular_function,local_stack,top_of_stack,
	    first_argument_index,arg_count)
    Object tabular_function, local_stack, top_of_stack, first_argument_index;
    Object arg_count;
{
    Object gensymed_symbol, temp, unknown_truth_value, no_item_allowed;
    Object argument, evaluation_value_qm, error_qm, argument_value;
    Object top_of_stack_1, message_1, value, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;
    char unknown_ok_qm;
    double aref_new_value;
    Object result;

    x_note_fn_call(205,198);
    if (IFIX(arg_count) != (SI_Long)1L)
	return tformat_stack_error_text_string(3,string_constant_108,
		tabular_function,arg_count);
    gensymed_symbol = tabular_function;
    temp = ISVREF(gensymed_symbol,(SI_Long)8L);
    if ( ! !TRUEP(CAR(temp)))
	return tformat_stack_error_text_string(2,string_constant_106,
		gensymed_symbol);
    unknown_truth_value = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)3L);
    no_item_allowed = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    unknown_ok_qm = FIXNUM_GE(M_CAR(unknown_truth_value),
	    ISVREF(Inference_engine_parameters,(SI_Long)26L));
    argument = ISVREF(local_stack,IFIX(first_argument_index));
    result = coerce_tabular_function_argument_to_evaluation_value(argument,
	    unknown_ok_qm ? T : Nil,top_of_stack);
    MVS_2(result,evaluation_value_qm,error_qm);
    if (error_qm)
	return VALUES_1(error_qm);
    argument_value = evaluation_value_qm ? 
	    evaluation_value_value(evaluation_value_qm) : Nil;
    if (CONSP(evaluation_value_qm) && EQ(M_CDR(evaluation_value_qm),
	    Qsequence) || CONSP(evaluation_value_qm) && 
	    EQ(M_CDR(evaluation_value_qm),Qab_structure)) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_109,
		tabular_function,evaluation_value_qm);
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else
	value = evaluation_value_qm ? 
		compute_value_of_tabular_function_if_any(tabular_function,
		argument_value) : Nil;
    if ( !TRUEP(value) && unknown_ok_qm) {
	if (EQ(Stack_expiration,Qnever))
	    Stack_expiration = Nil;
	else if (EQ(Nil,Qnever));
	else if ( !TRUEP(Stack_expiration) ||  !TRUEP(Nil))
	    Stack_expiration = Nil;
	else
	    Stack_expiration = FIXNUM_MIN(Stack_expiration,Nil);
    }
    else if ( !TRUEP(value)) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_110,
		tabular_function,evaluation_value_qm);
	return raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    else if (FIXNUMP(value));
    else if (INLINE_LONG_P(value) != (SI_Long)0L)
	value = make_evaluation_long(value);
    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	value = copy_managed_long(value);
    else if (FLOATP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	value = new_float;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	value = copy_managed_float(value);
    else if (SYMBOLP(value)) {
	if (EQ(value,Qtrue))
	    value = Evaluation_true_value;
	else if (EQ(value,Qfalse))
	    value = Evaluation_false_value;
	else;
    }
    else if (text_string_p(value))
	value = copy_as_wide_string(value);
    else
	return tformat_stack_error_text_string(8,string_constant_111,
		string_constant_112,tabular_function,string_constant_113,
		string_constant_114,string_constant_115,
		string_constant_116,string_constant_117);
    if ( !(EQ(unknown_truth_value,Evaluation_true_value) || 
	    EQ(unknown_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(unknown_truth_value);
    if ( !(EQ(no_item_allowed,Evaluation_true_value) || EQ(no_item_allowed,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(no_item_allowed);
    if (evaluation_value_qm)
	reclaim_evaluation_value(evaluation_value_qm);
    SVREF(local_stack,first_argument_index) = value;
    return VALUES_1(Nil);
}

static Object string_constant_118;  /* "Unknown thing ~a given as argument to tabular function." */

/* COERCE-TABULAR-FUNCTION-ARGUMENT-TO-EVALUATION-VALUE */
Object coerce_tabular_function_argument_to_evaluation_value(argument,
	    unknown_ok_qm,top_of_stack)
    Object argument, unknown_ok_qm, top_of_stack;
{
    Object gensymed_symbol, x2, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(205,199);
    gensymed_symbol = argument;
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
	    temp = TRUEP(memq_function(gensymed_symbol,
		    Defined_evaluation_datum_types));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_2(argument,Nil);
    else {
	if (SIMPLE_VECTOR_P(argument) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument)) > (SI_Long)2L && 
		 !EQ(ISVREF(argument,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(argument,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(argument,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		Cached_top_of_stack = top_of_stack;
		temp_1 = EQ(Current_environment,Qinference_engine) || 
			EQ(Current_environment,Qprocedure) ? 
			get_current_evaluation_value(argument,Nil) : 
			get_current_evaluation_value_from_simulation_environment(argument);
		return VALUES_2(temp_1,Nil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		    if (unknown_ok_qm) {
			Cached_top_of_stack = top_of_stack;
			temp_1 = EQ(Current_environment,Qinference_engine) 
				|| EQ(Current_environment,Qprocedure) ? 
				get_current_evaluation_value(argument,Nil) 
				: 
				get_current_evaluation_value_from_simulation_environment(argument);
			return VALUES_2(temp_1,Nil);
		    }
		    else {
			temp_1 = 
				signal_coerce_to_datum_error_message(argument,
				Qparameter);
			return VALUES_2(Nil,temp_1);
		    }
		}
		else {
		    temp_1 = signal_coerce_to_datum_error_message(argument,
			    unknown_ok_qm ? Qvariable_or_parameter : 
			    Qparameter);
		    return VALUES_2(Nil,temp_1);
		}
	    }
	}
	else {
	    temp_1 = tformat_stack_error_text_string(2,string_constant_118,
		    argument);
	    return VALUES_2(Nil,temp_1);
	}
    }
}

Object Recursion_warning_explanation_1 = UNBOUND;

Object Recursion_warning_explanation_2 = UNBOUND;

static Object string_constant_119;  /* "The recursion limit ~a has been exceeded while attempting to call ~NF.  ~a, ~a" */

static Object string_constant_120;  /* "The stack has overflowed while attempting to call the function ~NF.  ~
				     *          There are currently ~a function calls on the stack.  ~a."
				     */

static Object string_constant_121;  /* "The function ~NF received ~a arguments, but it requires ~a." */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

/* BEGIN-CALL-TO-FUNCTION-DEFINITION */
Object begin_call_to_function_definition(local_stack,top_of_stack_init,
	    function_definition,recursion_depth_init,stack_frame_base_init,
	    stack_program_counter_init,byte_code_body,constant_vector)
    Object local_stack, top_of_stack_init, function_definition;
    Object recursion_depth_init, stack_frame_base_init;
    Object stack_program_counter_init, byte_code_body, constant_vector;
{
    Object gensymed_symbol, temp, svref_new_value;
    SI_Long top_of_stack, recursion_depth, stack_frame_base;
    SI_Long stack_program_counter, argument_count, parameter_count, new_base;
    SI_Long svref_arg_2;

    x_note_fn_call(205,200);
    top_of_stack = IFIX(top_of_stack_init);
    recursion_depth = IFIX(recursion_depth_init);
    stack_frame_base = IFIX(stack_frame_base_init);
    stack_program_counter = IFIX(stack_program_counter_init);
    if (recursion_depth > IFIX(ISVREF(Inference_engine_parameters,
	    (SI_Long)22L)))
	return tformat_stack_error_text_string(5,string_constant_119,
		ISVREF(Inference_engine_parameters,(SI_Long)22L),
		function_definition,Recursion_warning_explanation_1,
		Recursion_warning_explanation_2);
    if (top_of_stack > IFIX(FIXNUM_MINUS(Global_stack_size,
	    Maximum_stack_frame_size)))
	return tformat_stack_error_text_string(4,string_constant_120,
		function_definition,FIX(recursion_depth),
		Recursion_warning_explanation_1);
    gensymed_symbol = function_definition;
    temp = ISVREF(gensymed_symbol,(SI_Long)8L);
    if ( ! !TRUEP(CAR(temp)))
	return tformat_stack_error_text_string(2,string_constant_106,
		gensymed_symbol);
    argument_count = IFIX(ISVREF(local_stack,top_of_stack - (SI_Long)1L));
    temp = ISVREF(function_definition,(SI_Long)16L);
    temp = CAR(temp);
    parameter_count = IFIX(length(SECOND(temp)));
    new_base = top_of_stack + 
	    IFIX(FIXNUM_ADD1(Number_of_extra_stack_frame_values));
    if (argument_count != parameter_count)
	return tformat_stack_error_text_string(4,string_constant_121,
		function_definition,FIX(argument_count),FIX(parameter_count));
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(Current_computation_frame)))
	    issue_tracing_and_breakpoint_exit_message(Current_computation_frame,
		    Nil);
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    svref_arg_2 = new_base - (SI_Long)6L;
    ISVREF(local_stack,svref_arg_2) = FIX(stack_frame_base);
    svref_arg_2 = new_base - (SI_Long)5L;
    ISVREF(local_stack,svref_arg_2) = FIX(stack_program_counter);
    svref_arg_2 = new_base - (SI_Long)4L;
    ISVREF(local_stack,svref_arg_2) = byte_code_body;
    svref_arg_2 = new_base - (SI_Long)3L;
    ISVREF(local_stack,svref_arg_2) = constant_vector;
    svref_arg_2 = new_base - (SI_Long)2L;
    svref_new_value = Current_computation_frame;
    ISVREF(local_stack,svref_arg_2) = svref_new_value;
    svref_arg_2 = new_base - (SI_Long)1L;
    svref_new_value = Current_computation_component_particulars;
    ISVREF(local_stack,svref_arg_2) = svref_new_value;
    gensymed_symbol = get_lookup_slot_value(function_definition,
	    Qtracing_and_breakpoints);
    if ((gensymed_symbol || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(function_definition,
		gensymed_symbol);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L)
	    issue_tracing_and_breakpoints_entry_message(function_definition,
		    begin_function_definition_enter_tracing_context_message(function_definition,
		    local_stack,FIX(top_of_stack),FIX(argument_count)));
    }
    return VALUES_1(Nil);
}

static Object string_constant_122;  /* "Calling function ~NF(" */

static Object array_constant_83;   /* # */

/* BEGIN-FUNCTION-DEFINITION-ENTER-TRACING-CONTEXT-MESSAGE */
Object begin_function_definition_enter_tracing_context_message(function_definition,
	    local_stack,top_of_stack,argument_count)
    Object function_definition, local_stack, top_of_stack, argument_count;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, argument_index;
    SI_Long current_argument, ab_loop_bind_;
    Declare_special(5);
    Object result;

    x_note_fn_call(205,201);
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
	      tformat(2,string_constant_122,function_definition);
	      argument_index = IFIX(top_of_stack) - (SI_Long)2L - 
		      IFIX(argument_count);
	      current_argument = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(argument_count);
	    next_loop:
	      if (current_argument >= ab_loop_bind_)
		  goto end_loop;
	      if ( !(current_argument == (SI_Long)0L))
		  twrite_beginning_of_wide_string(array_constant_9,
			  FIX((SI_Long)2L));
	      write_stored_value(ISVREF(local_stack,argument_index));
	      argument_index = argument_index + (SI_Long)1L;
	      current_argument = current_argument + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      twrite_beginning_of_wide_string(array_constant_83,
		      FIX((SI_Long)2L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* BEGIN-RETURN-FROM-FUNCTION-DEFINITION */
Object begin_return_from_function_definition(local_stack,top_of_stack_init,
	    stack_frame_base_init)
    Object local_stack, top_of_stack_init, stack_frame_base_init;
{
    Object temp, value, gensymed_symbol;
    SI_Long top_of_stack, stack_frame_base, index_1, ab_loop_bind_;
    SI_Long argument_count_index, argument_count, first_argument_index;

    x_note_fn_call(205,202);
    top_of_stack = IFIX(top_of_stack_init);
    stack_frame_base = IFIX(stack_frame_base_init);
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(Current_computation_frame))) {
	    temp = Current_computation_frame;
	    issue_tracing_and_breakpoint_exit_message(temp,
		    return_from_function_definition_exit_context_message(local_stack,
		    FIX(top_of_stack)));
	}
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    Current_computation_frame = ISVREF(local_stack,stack_frame_base - 
	    (SI_Long)2L);
    Current_computation_component_particulars = ISVREF(local_stack,
	    stack_frame_base - (SI_Long)1L);
    index_1 = stack_frame_base;
    ab_loop_bind_ = top_of_stack;
    value = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    value = ISVREF(local_stack,index_1);
    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	reclaim_if_evaluation_value_1(value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = get_lookup_slot_value(Current_computation_frame,
	    Qtracing_and_breakpoints);
    if ((gensymed_symbol || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(Current_computation_frame,
		gensymed_symbol);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L)
	    issue_tracing_and_breakpoints_entry_message(Current_computation_frame,
		    Nil);
    }
    argument_count_index = stack_frame_base - (SI_Long)8L;
    argument_count = IFIX(ISVREF(local_stack,argument_count_index));
    first_argument_index = stack_frame_base - argument_count - (SI_Long)10L;
    index_1 = first_argument_index;
    ab_loop_bind_ = first_argument_index + argument_count;
    value = Nil;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    value = ISVREF(local_stack,index_1);
    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	reclaim_if_evaluation_value_1(value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(FIX(argument_count));
    return VALUES_1(Qnil);
}

static Object array_constant_84;   /* # */

static Object array_constant_85;   /* # */

static Object string_constant_123;  /* " from function ~NF." */

/* RETURN-FROM-FUNCTION-DEFINITION-EXIT-CONTEXT-MESSAGE */
Object return_from_function_definition_exit_context_message(local_stack,
	    top_of_stack)
    Object local_stack, top_of_stack;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(205,203);
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
	      twrite_beginning_of_wide_string(array_constant_84,
		      FIX((SI_Long)10L));
	      if (Stack_expiration)
		  write_stored_value(ISVREF(local_stack,IFIX(top_of_stack)));
	      else
		  twrite_beginning_of_wide_string(array_constant_85,
			  FIX((SI_Long)7L));
	      tformat(2,string_constant_123,Current_computation_frame);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_124;  /* " ~NF" */

static Object string_constant_125;  /* " ~NV" */

/* TWRITE-ITEM-OR-EVALUATION-VALUE */
Object twrite_item_or_evaluation_value(argument)
    Object argument;
{
    Object x2;
    char temp;

    x_note_fn_call(205,204);
    if (SIMPLE_VECTOR_P(argument) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument)) > (SI_Long)2L &&  
	    !EQ(ISVREF(argument,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(argument,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return tformat(2,string_constant_124,argument);
    else
	return tformat(2,string_constant_125,argument);
}

static Object string_constant_126;  /* "calling ~(~a~):" */

/* TRACE-ENTER-SYSTEM-CALL */
Object trace_enter_system_call(function_name,arguments)
    Object function_name, arguments;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object argument, ab_loop_list_, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,205);
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
	      tformat(2,string_constant_126,function_name);
	      argument = Nil;
	      ab_loop_list_ = arguments;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      argument = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      twrite_item_or_evaluation_value(argument);
	      goto next_loop;
	    end_loop:;
	      message_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    notify_user_at_console(1,message_1);
    reclaim_text_string(message_1);
    return VALUES_1(Nil);
}

static Object string_constant_127;  /* "returning:" */

/* TRACE-EXIT-SYSTEM-CALL */
Object trace_exit_system_call(argument_count,return_value1_qm,
	    return_value2_qm,return_value3_qm,return_value4_qm,
	    return_value5_qm,return_value6_qm,return_value7_qm,
	    return_value8_qm)
    Object argument_count, return_value1_qm, return_value2_qm;
    Object return_value3_qm, return_value4_qm, return_value5_qm;
    Object return_value6_qm, return_value7_qm, return_value8_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,206);
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
	      tformat(1,string_constant_127);
	      if ((SI_Long)0L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value1_qm);
	      if ((SI_Long)1L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value2_qm);
	      if ((SI_Long)2L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value3_qm);
	      if ((SI_Long)3L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value4_qm);
	      if ((SI_Long)4L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value5_qm);
	      if ((SI_Long)5L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value6_qm);
	      if ((SI_Long)6L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value7_qm);
	      if ((SI_Long)7L < IFIX(argument_count))
		  twrite_item_or_evaluation_value(return_value8_qm);
	      message_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    notify_user_at_console(1,message_1);
    reclaim_text_string(message_1);
    return VALUES_1(Nil);
}

static Object Qfunction_keeps_procedure_environment_valid_qm;  /* function-keeps-procedure-environment-valid? */

static Object string_constant_128;  /* "The number of arguments to the System Procedure ~a is ~
				     *              beyond the maximum allowed.  Please report this error to ~
				     *              Gensym Software Support."
				     */

static Object string_constant_129;  /* "Attempting to make a system call to ~A, which is not defined.  ~
				     *              Please report this G2 internal error to Gensym software support."
				     */

static Object string_constant_130;  /* "System call tracing limit reached." */

static Object string_constant_131;  /* "Missing return value ~a in System Procedure.  Please ~
				     *                     call Gensym Software Support!"
				     */

static Object Qstack;              /* stack */

/* EXECUTE-LISP-CALL-STACK-INSTRUCTION */
Object execute_lisp_call_stack_instruction(local_stack,top_of_stack,
	    argument_count,expected_return_value_count)
    Object local_stack, top_of_stack, argument_count;
    Object expected_return_value_count;
{
    Object first_stack_value_index, lisp_function_name, valid_environment_qm;
    Object stack_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object argument_list, type_name, temp_1, frame_serial_number_setf_arg, old;
    Object new_1, temp_2, arg, ab_loop_list_, top_of_stack_1, message_1;
    Object gensymed_symbol, arg1_qm, arg2_qm, arg3_qm, arg4_qm, arg5_qm;
    Object arg6_qm, arg7_qm, arg8_qm, arg9_qm, arg10_qm, temp_3;
    Object return_value1_qm, return_value2_qm, return_value3_qm;
    Object return_value4_qm, return_value5_qm, return_value6_qm;
    Object return_value7_qm, return_value8_qm, gensymed_symbol_1;
    Object return_values, return_value_cons, return_value_qm;
    Object return_value_expected_qm, reversed_return_value_list_qm;
    Object ab_loop_iter_flag_, last_1, next_qm;
    SI_Long stack_index, ab_loop_bind_, return_value_count;
    SI_Long return_value_stack_index;
    char temp;
    Object result;

    x_note_fn_call(205,207);
    first_stack_value_index = FIXNUM_MINUS(top_of_stack,argument_count);
    lisp_function_name = ISVREF(local_stack,IFIX(first_stack_value_index));
    valid_environment_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(lisp_function_name),
	    Qfunction_keeps_procedure_environment_valid_qm);
    stack_index = IFIX(FIXNUM_ADD1(first_stack_value_index));
    ab_loop_bind_ = IFIX(top_of_stack);
    stack_value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (stack_index > ab_loop_bind_)
	goto end_loop;
    stack_value = ISVREF(local_stack,stack_index);
    ab_loopvar__2 = stack_cons_1(stack_value,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    stack_index = stack_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    argument_list = ab_loopvar_;
    goto end_1;
    argument_list = Qnil;
  end_1:;
    if ( !TRUEP(valid_environment_qm)) {
	if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	    type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
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
	    update_code_body_invocation_frame_serial_number(Current_computation_instance);
	else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	    temp_1 = Current_computation_instance;
	    frame_serial_number_setf_arg = Current_frame_serial_number;
	    old = ISVREF(temp_1,(SI_Long)11L);
	    new_1 = frame_serial_number_setf_arg;
	    temp_2 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		    !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(temp_1,FIX((SI_Long)11L)) = temp_2;
	}
    }
    Cached_top_of_stack = FIXNUM_MINUS(top_of_stack,argument_count);
    if (IFIX(argument_count) > (SI_Long)10L ||  
	    !TRUEP(fboundp(lisp_function_name))) {
	arg = Nil;
	ab_loop_list_ = argument_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(FIXNUMP(arg) || SYMBOLP(arg) || SIMPLE_VECTOR_P(arg)))
	    reclaim_if_evaluation_value_1(arg);
	goto next_loop_1;
      end_loop_1:;
	reclaim_stack_list_1(argument_list);
	if (IFIX(argument_count) > (SI_Long)10L) {
	    top_of_stack_1 = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_128,lisp_function_name);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else {
	    top_of_stack_1 = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_129,lisp_function_name);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    if (Trace_system_calls_p)
	trace_enter_system_call(lisp_function_name,argument_list);
    gensymed_symbol = argument_list;
    arg1_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg2_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg3_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg4_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg5_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg6_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg7_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg8_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg9_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg10_qm = CAR(gensymed_symbol);
    reclaim_stack_list_1(argument_list);
    if ( !(FIXNUMP(argument_count) && FIXNUM_LE(FIX((SI_Long)-128L),
	    argument_count) && FIXNUM_LE(argument_count,FIX((SI_Long)127L))))
	result = VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(argument_count)) {
	  case 0:
	    result = FUNCALL_0(SYMBOL_FUNCTION(lisp_function_name));
	    break;
	  case 1:
	    temp_3 = SYMBOL_FUNCTION(lisp_function_name);
	    result = FUNCALL_1(temp_3,arg1_qm);
	    break;
	  case 2:
	    temp_3 = SYMBOL_FUNCTION(lisp_function_name);
	    result = FUNCALL_2(temp_3,arg1_qm,arg2_qm);
	    break;
	  case 3:
	    temp_3 = SYMBOL_FUNCTION(lisp_function_name);
	    result = FUNCALL_3(temp_3,arg1_qm,arg2_qm,arg3_qm);
	    break;
	  case 4:
	    temp_3 = SYMBOL_FUNCTION(lisp_function_name);
	    result = FUNCALL_4(temp_3,arg1_qm,arg2_qm,arg3_qm,arg4_qm);
	    break;
	  case 5:
	    temp_3 = SYMBOL_FUNCTION(lisp_function_name);
	    result = FUNCALL_5(temp_3,arg1_qm,arg2_qm,arg3_qm,arg4_qm,arg5_qm);
	    break;
	  case 6:
	    result = funcall(7,SYMBOL_FUNCTION(lisp_function_name),arg1_qm,
		    arg2_qm,arg3_qm,arg4_qm,arg5_qm,arg6_qm);
	    break;
	  case 7:
	    result = funcall(8,SYMBOL_FUNCTION(lisp_function_name),arg1_qm,
		    arg2_qm,arg3_qm,arg4_qm,arg5_qm,arg6_qm,arg7_qm);
	    break;
	  case 8:
	    result = funcall(9,SYMBOL_FUNCTION(lisp_function_name),arg1_qm,
		    arg2_qm,arg3_qm,arg4_qm,arg5_qm,arg6_qm,arg7_qm,arg8_qm);
	    break;
	  case 9:
	    result = funcall(10,SYMBOL_FUNCTION(lisp_function_name),
		    arg1_qm,arg2_qm,arg3_qm,arg4_qm,arg5_qm,arg6_qm,
		    arg7_qm,arg8_qm,arg9_qm);
	    break;
	  case 10:
	    result = funcall(11,SYMBOL_FUNCTION(lisp_function_name),
		    arg1_qm,arg2_qm,arg3_qm,arg4_qm,arg5_qm,arg6_qm,
		    arg7_qm,arg8_qm,arg9_qm,arg10_qm);
	    break;
	  default:
	    result = VALUES_1(Nil);
	    break;
	}
    MVS_8(result,return_value1_qm,return_value2_qm,return_value3_qm,
	    return_value4_qm,return_value5_qm,return_value6_qm,
	    return_value7_qm,return_value8_qm);
    if (Trace_system_calls_p) {
	trace_exit_system_call(expected_return_value_count,
		return_value1_qm,return_value2_qm,return_value3_qm,
		return_value4_qm,return_value5_qm,return_value6_qm,
		return_value7_qm,return_value8_qm);
	if (FIXNUMP(Trace_system_calls_p)) {
	    temp_1 = FIXNUM_SUB1(Trace_system_calls_p);
	    Trace_system_calls_p = temp_1;
	    if ((SI_Long)0L == IFIX(Trace_system_calls_p)) {
		notify_user_at_console(1,string_constant_130);
		Trace_system_calls_p = Nil;
	    }
	}
    }
    if ( !TRUEP(valid_environment_qm))
	validate_computation_instance_environment(Current_computation_instance,
		Nil,Nil);
    gensymed_symbol = make_stack_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = return_value1_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value2_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value3_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value4_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value5_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value6_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value7_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = return_value8_qm;
    return_values = gensymed_symbol;
    return_value_cons = return_values;
    return_value_qm = Nil;
    return_value_count = (SI_Long)1L;
    return_value_expected_qm = Nil;
    reversed_return_value_list_qm = Nil;
    ab_loop_iter_flag_ = T;
  next_loop_2:
    if ( !TRUEP(return_value_cons))
	goto end_loop_2;
    return_value_qm = M_CAR(return_value_cons);
    if ( !TRUEP(ab_loop_iter_flag_))
	return_value_count = return_value_count + (SI_Long)1L;
    return_value_expected_qm = return_value_count <= 
	    IFIX(expected_return_value_count) ? T : Nil;
    if ( !(return_value_qm || return_value_expected_qm))
	goto end_loop_2;
    if ( !TRUEP(return_value_qm)) {
	top_of_stack_1 = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_131,
		FIXNUM_ADD1(FIXNUM_MINUS(length(return_values),
		length(return_value_cons))));
	raw_stack_error_named_error(top_of_stack_1,message_1);
	if (return_values) {
	    last_1 = return_values;
	    next_qm = Nil;
	  next_loop_3:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_3;
	    inline_note_reclaim_cons(last_1,Qstack);
	    last_1 = next_qm;
	    goto next_loop_3;
	  end_loop_3:
	    inline_note_reclaim_cons(last_1,Qstack);
	    if (ISVREF(Available_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = return_values;
		temp_1 = Available_stack_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = last_1;
	    }
	    else {
		temp_1 = Available_stack_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = return_values;
		temp_1 = Available_stack_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    else if ( !TRUEP(return_value_expected_qm)) {
	if ( !(FIXNUMP(return_value_qm) || SYMBOLP(return_value_qm) || 
		SIMPLE_VECTOR_P(return_value_qm)))
	    reclaim_if_evaluation_value_1(return_value_qm);
    }
    else
	reversed_return_value_list_qm = stack_cons_1(return_value_qm,
		reversed_return_value_list_qm);
    ab_loop_iter_flag_ = Nil;
    return_value_cons = M_CDR(return_value_cons);
    goto next_loop_2;
  end_loop_2:
    return_value_stack_index = IFIX(first_stack_value_index);
    return_value_qm = Nil;
    ab_loop_list_ = reversed_return_value_list_qm;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    return_value_qm = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ISVREF(local_stack,return_value_stack_index) = return_value_qm;
    return_value_stack_index = return_value_stack_index + (SI_Long)1L;
    goto next_loop_4;
  end_loop_4:;
    reclaim_stack_list_1(return_values);
    reclaim_stack_list_1(reversed_return_value_list_qm);
    return VALUES_1(FIXNUM_ADD(FIXNUM_SUB1(first_stack_value_index),
	    expected_return_value_count));
    return VALUES_1(Qnil);
}

Object Valid_styles = UNBOUND;

Object Valid_directions = UNBOUND;

Object Valid_sides = UNBOUND;

/* EXECUTE-CREATE-CONNECTION-STACK-INSTRUCTION */
Object execute_create_connection_stack_instruction(local_stack,
	    top_of_stack,constant_vector)
    Object local_stack, top_of_stack, constant_vector;
{
    Object class_1, class_description_qm, end_1_item, make_new_stub_1_qm;
    Object side_1_qm, position_1_qm, portname_1_qm, evaluation_value;
    Object end_2_item_qm, make_new_stub_2_qm, side_2_qm, position_2_qm;
    Object portname_2_qm, style_qm, direction_qm;
    Object vertices_list_or_constant_index_qm, new_transient_connection_qm;
    Object type_name, svref_arg_1, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value, temp_1, thing;
    char temp;

    x_note_fn_call(205,208);
    class_1 = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)13L);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    end_1_item = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)12L);
    make_new_stub_1_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)11L);
    side_1_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)10L);
    position_1_qm = evaluation_value_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)9L));
    portname_1_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)8L);
    evaluation_value = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)7L);
    end_2_item_qm = evaluation_value && SYMBOLP(evaluation_value) ? 
	    ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)7L) : 
	    ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)7L);
    make_new_stub_2_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)6L);
    side_2_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)5L);
    position_2_qm = evaluation_value_value(ISVREF(local_stack,
	    IFIX(top_of_stack) - (SI_Long)4L));
    portname_2_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)3L);
    style_qm = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    direction_qm = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    vertices_list_or_constant_index_qm = ISVREF(local_stack,
	    IFIX(top_of_stack));
    new_transient_connection_qm = Nil;
    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
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
	update_code_body_invocation_frame_serial_number(Current_computation_instance);
    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	svref_arg_1 = Current_computation_instance;
	frame_serial_number_setf_arg = Current_frame_serial_number;
	old = ISVREF(svref_arg_1,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(svref_arg_1,FIX((SI_Long)11L)) = svref_new_value;
    }
    if (vertices_list_or_constant_index_qm && 
	    SYMBOLP(vertices_list_or_constant_index_qm))
	temp_1 = vertices_list_or_constant_index_qm;
    else if (FIXNUMP(vertices_list_or_constant_index_qm))
	temp_1 = ISVREF(constant_vector,
		IFIX(vertices_list_or_constant_index_qm));
    else
	temp_1 = vertices_list_or_constant_index_qm;
    new_transient_connection_qm = 
	    execute_create_connection_stack_instruction_internal(class_1,
	    class_description_qm,end_1_item,make_new_stub_1_qm,side_1_qm,
	    position_1_qm,portname_1_qm,end_2_item_qm,make_new_stub_2_qm,
	    side_2_qm,position_2_qm,portname_2_qm,style_qm,direction_qm,
	    temp_1,top_of_stack);
    thing = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)9L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    thing = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)7L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    thing = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)4L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    thing = ISVREF(local_stack,IFIX(top_of_stack));
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    validate_computation_instance_environment(Current_computation_instance,
	    Nil,Nil);
    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
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
	update_code_body_invocation_frame_serial_number(Current_computation_instance);
    else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	svref_arg_1 = Current_computation_instance;
	frame_serial_number_setf_arg = Current_frame_serial_number;
	old = ISVREF(svref_arg_1,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(svref_arg_1,FIX((SI_Long)11L)) = svref_new_value;
    }
    top_of_stack = FIX(IFIX(top_of_stack) - (SI_Long)13L);
    SVREF(local_stack,top_of_stack) = new_transient_connection_qm;
    return VALUES_1(top_of_stack);
}

static Object string_constant_132;  /* "~a is not a defined class." */

static Object Qnot_user_instantiable;  /* not-user-instantiable */

static Object string_constant_133;  /* "In a CREATE statement, attempted to make an instance of ~a, ~
				     *          but you cannot instantiate a class which is not a final ~
				     *          menu choice."
				     */

static Object string_constant_134;  /* "When creating transient instances of the class ~a, you should not ~
				     *          use the additional CONNECTED grammar."
				     */

static Object string_constant_135;  /* "The connection style specifier ~
				     *          in a CREATE action evaluated to ~s ~
				     *          which is not one of the valid styles diagonal, or orthogonal."
				     */

static Object string_constant_136;  /* "The connection direction specifier in a CREATE action evaluated to ~s ~
				     *          which is not one of the valid directions input, or output"
				     */

static Object float_constant;      /* 0.5 */

/* EXECUTE-CREATE-CONNECTION-STACK-INSTRUCTION-INTERNAL */
Object execute_create_connection_stack_instruction_internal(class_1,
	    class_description_qm,end_1_item,make_new_stub_1_qm,side_1_qm,
	    position_1_qm,portname_1_qm,end_2_item_qm,make_new_stub_2_qm,
	    side_2_qm,position_2_qm,portname_2_qm,style_qm,direction_qm,
	    vertices_list_or_constant_vertex_list_qm,top_of_stack)
    Object class_1, class_description_qm, end_1_item, make_new_stub_1_qm;
    Object side_1_qm, position_1_qm, portname_1_qm, end_2_item_qm;
    Object make_new_stub_2_qm, side_2_qm, position_2_qm, portname_2_qm;
    Object style_qm, direction_qm, vertices_list_or_constant_vertex_list_qm;
    Object top_of_stack;
{
    Object delta_list_qm, top_of_stack_1, message_1, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector, error_string_qm, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, x2, delta_tail_qm, number, portname_1_qm_temp;
    Object position_1_qm_temp, side_1_qm_temp, make_new_stub_1_qm_temp;
    Object end_1_item_temp, transient_connection_error_qm;
    Object new_transient_connection_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long next_index, length_1;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(205,209);
    delta_list_qm = Nil;
    if (position_1_qm)
	position_1_qm = l_round(position_1_qm,_);
    if (position_2_qm)
	position_2_qm = l_round(position_2_qm,_);
    if ( !TRUEP(class_description_qm)) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_132,class_1);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_132,class_1);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    if ( !TRUEP(Called_within_clear_text_loading) && 
	    assq_function(Qnot_user_instantiable,
	    ISVREF(class_description_qm,(SI_Long)12L))) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_133,class_1);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_133,class_1);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
	    temp_2 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
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
	    temp_2 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
    else
	temp_3 = TRUEP(Nil);
    if ( !temp_3) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_134,class_1);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_134,class_1);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    if (style_qm &&  !TRUEP(memq_function(style_qm,Valid_styles))) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_135,style_qm);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_135,style_qm);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    if (direction_qm &&  !TRUEP(memq_function(direction_qm,
		Valid_directions))) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_136,direction_qm);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_136,direction_qm);
	    raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    error_string_qm = check_for_illegal_side_error(side_1_qm,top_of_stack);
    if (error_string_qm);
    else
	error_string_qm = check_for_illegal_side_error(side_2_qm,top_of_stack);
    if (error_string_qm);
    else
	error_string_qm = check_for_illegal_position_error(position_1_qm,
		top_of_stack);
    if (error_string_qm);
    else
	error_string_qm = check_for_illegal_position_error(position_2_qm,
		top_of_stack);
    if (error_string_qm)
	return VALUES_1(error_string_qm);
    if (CONSP(vertices_list_or_constant_vertex_list_qm) && 
	    EQ(M_CDR(vertices_list_or_constant_vertex_list_qm),Qsequence)) {
	gensymed_symbol = vertices_list_or_constant_vertex_list_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_12:
	if (next_index >= length_1)
	    goto end_loop_12;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	ab_loopvar__2 = eval_cons_1(element,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_12;
      end_loop_12:
	delta_list_qm = ab_loopvar_;
	goto end_5;
	delta_list_qm = Qnil;
      end_5:;
    }
    else if (CONSP(vertices_list_or_constant_vertex_list_qm)) {
	temp_1 = CAR(vertices_list_or_constant_vertex_list_qm);
	if (NUMBERP(temp_1))
	    delta_list_qm = 
		    copy_list_using_eval_conses_1(vertices_list_or_constant_vertex_list_qm);
    }
    else {
	if (SIMPLE_VECTOR_P(vertices_list_or_constant_vertex_list_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vertices_list_or_constant_vertex_list_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(vertices_list_or_constant_vertex_list_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(vertices_list_or_constant_vertex_list_qm,(SI_Long)1L);
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
		    IFIX(ISVREF(Quantity_list_class_description,(SI_Long)18L));
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
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    delta_tail_qm = Nil;
	    gensymed_symbol = vertices_list_or_constant_vertex_list_qm;
	    ab_loopvar_ = ISVREF(gensymed_symbol,(SI_Long)20L);
	    ab_loopvar__1 = Nil;
	    element = Nil;
	    ab_loopvar__1 = ab_loopvar_ ? 
		    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		    ab_loopvar_) : Nil;
	  next_loop_13:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop_13;
	    element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	    if ( !TRUEP(delta_tail_qm)) {
		number = evaluation_quantity_value(element);
		temp_1 = FIX((SI_Long)0L);
		delta_list_qm = eval_cons_1(ltruncate(NUM_GT(number,
			temp_1) ? add(number,float_constant) : 
			minus(number,float_constant),_),Nil);
		delta_tail_qm = delta_list_qm;
	    }
	    else {
		number = evaluation_quantity_value(element);
		temp_1 = FIX((SI_Long)0L);
		temp_2 = eval_cons_1(ltruncate(NUM_GT(number,temp_1) ? 
			add(number,float_constant) : minus(number,
			float_constant),_),Nil);
		M_CDR(delta_tail_qm) = temp_2;
		delta_tail_qm = CDR(delta_tail_qm);
	    }
	    goto next_loop_13;
	  end_loop_13:
	    goto end_6;
	  end_6:;
	}
    }
    if (EQ(direction_qm,Qinput)) {
	portname_1_qm_temp = portname_2_qm;
	position_1_qm_temp = position_2_qm;
	side_1_qm_temp = side_2_qm;
	make_new_stub_1_qm_temp = make_new_stub_2_qm;
	end_1_item_temp = end_2_item_qm;
	portname_2_qm = portname_1_qm;
	portname_1_qm = portname_1_qm_temp;
	position_2_qm = position_1_qm;
	position_1_qm = position_1_qm_temp;
	side_2_qm = side_1_qm;
	side_1_qm = side_1_qm_temp;
	make_new_stub_2_qm = make_new_stub_1_qm;
	make_new_stub_1_qm = make_new_stub_1_qm_temp;
	end_2_item_qm = end_1_item;
	end_1_item = end_1_item_temp;
    }
    transient_connection_error_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Transient_connection_error_qm,Qtransient_connection_error_qm,transient_connection_error_qm,
	    0);
      new_transient_connection_qm = make_transient_connection(class_1,
	      end_1_item,make_new_stub_1_qm,side_1_qm,position_1_qm,
	      portname_1_qm,end_2_item_qm,make_new_stub_2_qm,side_2_qm,
	      position_2_qm,portname_2_qm,direction_qm,style_qm,
	      delta_list_qm,T);
      if ( !TRUEP(new_transient_connection_qm)) {
	  reclaim_eval_list_1(delta_list_qm);
	  stack_eval_handle_transient_connection_error_qm(Transient_connection_error_qm,
		  top_of_stack);
      }
      else {
	  invoke_rules_for_direct_connection_chaining(ISVREF(new_transient_connection_qm,
		  (SI_Long)21L),Nil);
	  invoke_rules_for_indirect_connection_chaining(ISVREF(new_transient_connection_qm,
		  (SI_Long)21L),Nil);
      }
      result = VALUES_1(new_transient_connection_qm);
    POP_SPECIAL();
    return result;
}

static Object string_constant_137;  /* "A CREATE action could not make a connection to the ~
				     *        object ~NF because this object has no-manual-connections capability"
				     */

/* CHECK-FOR-NO-MANUAL-CONNECTIONS-ERROR */
Object check_for_no_manual_connections_error(end_item_qm,top_of_stack)
    Object end_item_qm, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(205,210);
    if (end_item_qm && no_manual_connections_p(end_item_qm)) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_137,end_item_qm);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_137,end_item_qm);
	    return raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_138;  /* "A connection side specifier in a CREATE action evaluated to ~s ~
				     *       which is not one of the valid sides left, right, top, or bottom"
				     */

/* CHECK-FOR-ILLEGAL-SIDE-ERROR */
Object check_for_illegal_side_error(side_qm,top_of_stack)
    Object side_qm, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(205,211);
    if (side_qm &&  !TRUEP(memq_function(side_qm,Valid_sides))) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_138,side_qm);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_138,side_qm);
	    return raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_139;  /* "A connection end position specifier in a CREATE action evaluated to ~s ~
				     *        which is not a non-negative integer."
				     */

/* CHECK-FOR-ILLEGAL-POSITION-ERROR */
Object check_for_illegal_position_error(position_qm,top_of_stack)
    Object position_qm, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(205,212);
    if (position_qm &&  !(IFIX(position_qm) >= (SI_Long)0L)) {
	if (Disable_stack_error)
	    return tformat_text_string(2,string_constant_139,position_qm);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_139,position_qm);
	    return raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qnot_same_workspace;  /* not-same-workspace */

static Object string_constant_140;  /* "In a CREATE action, attempt to make a connection between ~NF and ~NF ~
				     *                   was unsuccessful because the objects are not on the same workspace."
				     */

static Object Qnot_on_workspace;   /* not-on-workspace */

static Object string_constant_141;  /* "In a CREATE action, attempt to make a connection to ~NF was ~
				     *                   unsuccessful because the object is not on a workspace."
				     */

static Object Qnot_transient;      /* not-transient */

static Object string_constant_142;  /* "In a CREATE action, attempt to make a connection to ~NF was ~
				     *                   unsuccessful because the connection to connect to is not transient."
				     */

static Object Qbad_designation;    /* bad-designation */

static Object string_constant_143;  /* "In a CREATE action, attempt to make a connection to ~NF was ~
				     *                   unsuccessful because the designated stub was not found."
				     */

/* STACK-EVAL-HANDLE-TRANSIENT-CONNECTION-ERROR? */
Object stack_eval_handle_transient_connection_error_qm(error_qm,top_of_stack)
    Object error_qm, top_of_stack;
{
    Object gensymed_symbol, kind_of_error, second_1, third_1, format_string;
    Object top_of_stack_1, message_1;

    x_note_fn_call(205,213);
    if (error_qm) {
	gensymed_symbol = error_qm;
	kind_of_error = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	second_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	third_1 = CAR(gensymed_symbol);
	reclaim_gensym_list_1(error_qm);
	if (EQ(kind_of_error,Qnot_same_workspace))
	    format_string = string_constant_140;
	else if (EQ(kind_of_error,Qnot_on_workspace))
	    format_string = string_constant_141;
	else if (EQ(kind_of_error,Qnot_transient))
	    format_string = string_constant_142;
	else if (EQ(kind_of_error,Qbad_designation))
	    format_string = string_constant_143;
	else
	    format_string = Qnil;
	if (Disable_stack_error)
	    return tformat_text_string(3,format_string,second_1,third_1);
	else {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,format_string,
		    second_1,third_1);
	    return raw_stack_error_named_error(top_of_stack_1,message_1);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_144;  /* "  ~a = " */

static Object string_constant_145;  /* "~%" */

static Object string_constant_146;  /* "In ~a" */

static Object string_constant_147;  /* " {about to execute instruction ~a}." */

static Object string_constant_148;  /* "~%~%At source code line #~d." */

static Object string_constant_149;  /* "~%~%~a" */

static Object string_constant_150;  /* "~%~%Stack:~%" */

static Object string_constant_151;  /* "  Empty stack~%" */

static Object string_constant_152;  /* "~%Environment:~%~a" */

/* CAPTURE-HALT-INFORMATION */
Object capture_halt_information(halt_reason,halt_message_qm,
	    current_program_counter,top_of_stack,local_stack,
	    local_var_vector,byte_code_body)
    Object halt_reason, halt_message_qm, current_program_counter, top_of_stack;
    Object local_stack, local_var_vector, byte_code_body;
{
    Object procedure_invocation_to_print, code_body, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object procedure_and_arguments_as_text, stack_qm, env, line_index_qm;
    Object type_name, source_line_qm, source_character_index_qm, temp_1;
    Object procedure_text, non_word_wrapped_text, new_line_index;
    Object new_char_index, text_tail, index_at_end, source_code_qm, message_1;
    Object hi, svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_;
    char temp;
    Declare_special(6);
    Object result;

    x_note_fn_call(205,214);
    procedure_invocation_to_print = ISVREF(Current_computation_instance,
	    (SI_Long)11L);
    code_body = ISVREF(Current_computation_instance,(SI_Long)8L);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,5);
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
		write_procedure_invocation_instance_from_slot(procedure_invocation_to_print,
			Nil);
		procedure_and_arguments_as_text = 
			copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      if (IFIX(top_of_stack) >= (SI_Long)0L) {
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
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    index_1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(top_of_stack);
		  next_loop:
		    if (index_1 > ab_loop_bind_)
			goto end_loop;
		    tformat(2,string_constant_144,FIX(index_1));
		    write_stored_value(ISVREF(local_stack,index_1));
		    tformat(1,string_constant_145);
		    index_1 = index_1 + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    stack_qm = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      else
	  stack_qm = Nil;
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
		write_code_body_environment(ISVREF(byte_code_body,
			(SI_Long)4L),local_var_vector);
		env = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      line_index_qm = Nil;
      if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	  type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
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
	  result = get_annotation_for_address_if_any(current_program_counter,
		  Code_body);
      else
	  result = VALUES_1(Nil);
      MVS_2(result,source_line_qm,source_character_index_qm);
      if (source_line_qm) {
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
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    temp_1 = ISVREF(ISVREF(procedure_invocation_to_print,
			    (SI_Long)23L),(SI_Long)27L);
		    procedure_text = CDR(temp_1);
		    result = convert_to_non_word_wrapped_text(3,
			    procedure_text,source_line_qm,
			    source_character_index_qm);
		    MVS_3(result,non_word_wrapped_text,new_line_index,
			    new_char_index);
		    text_tail = 
			    find_text_tail_for_line(non_word_wrapped_text,
			    new_line_index);
		    index_at_end = find_end_of_line_of_text(text_tail,T);
		    line_index_qm = FIXNUM_GE(new_char_index,index_at_end) 
			    && advance_text_tail(text_tail,
			    FIX((SI_Long)1L)) ? 
			    FIXNUM_ADD1(new_line_index) : new_line_index;
		    tformat_surrounding_source_code_at_halt(non_word_wrapped_text,
			    line_index_qm);
		    reclaim_text(non_word_wrapped_text);
		    source_code_qm = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      else
	  source_code_qm = Nil;
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
		tformat(2,string_constant_146,procedure_and_arguments_as_text);
		tformat(2,string_constant_147,current_program_counter);
		if (source_code_qm) {
		    tformat(2,string_constant_148,line_index_qm);
		    twrite_general_string(source_code_qm);
		}
		if (halt_message_qm)
		    tformat(2,string_constant_149,halt_message_qm);
		tformat(1,string_constant_150);
		if (stack_qm)
		    twrite_general_string(stack_qm);
		else
		    tformat(1,string_constant_151);
		tformat(2,string_constant_152,env);
		message_1 = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      hi = make_halt_info_1();
      SVREF(hi,FIX((SI_Long)1L)) = halt_reason;
      SVREF(hi,FIX((SI_Long)8L)) = message_1;
      svref_new_value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(halt_message_qm) 
	      != (SI_Long)0L ? copy_text_string(halt_message_qm) : 
	      halt_message_qm;
      SVREF(hi,FIX((SI_Long)7L)) = svref_new_value;
      SVREF(hi,FIX((SI_Long)2L)) = procedure_and_arguments_as_text;
      SVREF(hi,FIX((SI_Long)5L)) = current_program_counter;
      SVREF(hi,FIX((SI_Long)3L)) = stack_qm;
      SVREF(hi,FIX((SI_Long)4L)) = env;
      SVREF(hi,FIX((SI_Long)6L)) = line_index_qm;
      result = VALUES_1(hi);
    POP_SPECIAL();
    return result;
}

static Object string_constant_153;  /* "~%[ ~a~d ~a~a] " */

static Object string_constant_154;  /* " #" */

static Object string_constant_155;  /* "#" */

static Object string_constant_156;  /* "=>" */

static Object string_constant_157;  /* "  " */

static Object string_constant_158;  /* "?" */

/* TFORMAT-SURROUNDING-SOURCE-CODE-AT-HALT */
Object tformat_surrounding_source_code_at_halt(non_word_wrapped_text,
	    line_index)
    Object non_word_wrapped_text, line_index;
{
    Object text_line, line_length, lost_space_at_end_of_line, text_tail_qm;
    Object temp_1;
    SI_Long n_before, n_after, temp, n_1st_line_no, line_no, ab_loop_bind_;
    Object result;

    x_note_fn_call(205,215);
    n_before = (SI_Long)1L;
    n_after = (SI_Long)1L;
    text_line = Nil;
    line_length = Nil;
    lost_space_at_end_of_line = Nil;
    temp = IFIX(line_index) - n_before;
    n_1st_line_no = MAX((SI_Long)1L,temp);
    text_tail_qm = find_text_tail_for_line(non_word_wrapped_text,
	    FIX(n_1st_line_no));
    temp = IFIX(line_index) - n_before;
    line_no = MAX((SI_Long)1L,temp);
    ab_loop_bind_ = IFIX(line_index) + n_after;
  next_loop:
    if (line_no > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(text_tail_qm))
	goto end_loop;
    tformat(5,string_constant_153,line_no < (SI_Long)10L ? 
	    string_constant_154 : string_constant_155,FIX(line_no),line_no 
	    == IFIX(line_index) ? string_constant_156 : 
	    string_constant_157,string_constant_158);
    result = get_next_text_line(text_tail_qm);
    MVS_4(result,text_line,line_length,lost_space_at_end_of_line,text_tail_qm);
    temp_1 = text_line;
    twrite_portion_of_wide_string_unparsably_to_current_wide_string(temp_1,
	    get_character_index_past_separator(text_tail_qm),Nil);
    line_no = line_no + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qshow_workspace;     /* show-workspace */

static Object string_constant_159;  /* "Cannot show ~NF.  The show action has been restricted for this item." */

/* EXECUTE-SHOW-STACK-INSTRUCTION */
Object execute_show_stack_instruction(local_stack,top_of_stack,constant_vector)
    Object local_stack, top_of_stack, constant_vector;
{
    Object item, window_arg, designated_window_g2_extension_qm;
    Object show_details_arg_qm, show_details, sub_class_bit_vector;
    Object ok_to_show_qm, workspace_qm, top_of_stack_1, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(205,216);
    item = ISVREF(local_stack,IFIX(top_of_stack) - (SI_Long)2L);
    window_arg = ISVREF(local_stack,IFIX(FIXNUM_SUB1(top_of_stack)));
    designated_window_g2_extension_qm = window_arg && SYMBOLP(window_arg) ?
	     window_arg : window_arg;
    show_details_arg_qm = ISVREF(local_stack,IFIX(top_of_stack));
    show_details = FIXNUMP(show_details_arg_qm) ? ISVREF(constant_vector,
	    IFIX(show_details_arg_qm)) : Nil;
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
    if (temp)
	ok_to_show_qm = 
		frame_system_operation_is_allowed_p(Qshow_workspace,item);
    else {
	workspace_qm = get_workspace_if_any(item);
	ok_to_show_qm = workspace_qm ? 
		frame_system_operation_is_allowed_p(Qshow_workspace,
		workspace_qm) : Qnil;
    }
    if (ok_to_show_qm)
	show_or_hide(4,item,T,show_details,designated_window_g2_extension_qm);
    else {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_159,
		item);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    FIXNUMP(show_details_arg_qm);
    top_of_stack = FIX(IFIX(top_of_stack) - (SI_Long)3L);
    return VALUES_1(top_of_stack);
}

static Object Qinvoking;           /* invoking */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* EXECUTE-INVOKE-STACK-INSTRUCTION */
Object execute_invoke_stack_instruction varargs_1(int, n)
{
    Object local_stack, top_of_stack, constant_vector;
    Object wait_p, query_restriction_index_arg, query_restriction;
    Object focal_entity_arg, focal_entity_qm;
    Object current_ri_completion_notification_collection_qm, class_1;
    Object class_description, ab_loop_list_, rule_of_this_role_name;
    Object ab_loop_list__1, categories_of_rule_of_this_role_name, category;
    Object ab_loop_list__2, ab_loop_it_, name_of_object;
    Object rule_of_this_object_name, categories_of_rule_of_this_object_name;
    Object name, rule_of_this_category;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(205,217);
    INIT_ARGS_nonrelocating();
    local_stack = REQUIRED_ARG_nonrelocating();
    top_of_stack = REQUIRED_ARG_nonrelocating();
    constant_vector = REQUIRED_ARG_nonrelocating();
    wait_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    query_restriction_index_arg = ISVREF(local_stack,
	    IFIX(FIXNUM_SUB1(top_of_stack)));
    query_restriction = ISVREF(constant_vector,
	    IFIX(query_restriction_index_arg));
    focal_entity_arg = ISVREF(local_stack,IFIX(top_of_stack));
    focal_entity_qm = focal_entity_arg;
    current_ri_completion_notification_collection_qm = wait_p ? 
	    set_up_completion_notification_collection(Current_computation_instance) 
	    : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_ri_completion_notification_collection_qm,Qcurrent_ri_completion_notification_collection_qm,current_ri_completion_notification_collection_qm,
	    0);
      if (focal_entity_qm) {
	  class_1 = Nil;
	  class_description = ISVREF(focal_entity_qm,(SI_Long)1L);
	  ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  class_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  rule_of_this_role_name = Nil;
	  ab_loop_list__1 = lookup_kb_specific_property_value(class_1,
		  Rules_of_this_class_or_object_name_kbprop);
	next_loop_1:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  rule_of_this_role_name = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  categories_of_rule_of_this_role_name = 
		  ISVREF(rule_of_this_role_name,(SI_Long)24L);
	  category = Nil;
	  ab_loop_list__2 = CDR(query_restriction);
	  ab_loop_it_ = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list__2))
	      goto end_loop_2;
	  category = M_CAR(ab_loop_list__2);
	  ab_loop_list__2 = M_CDR(ab_loop_list__2);
	  ab_loop_it_ = memq_function(category,
		  categories_of_rule_of_this_role_name);
	  if (ab_loop_it_) {
	      temp = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop_2;
	end_loop_2:
	  temp = TRUEP(Qnil);
	end_1:;
	  if (temp)
	      schedule_rule_instances_if_rule_is_not_embedded(rule_of_this_role_name,
		      class_1,Nil,focal_entity_qm,Qinvoking);
	  goto next_loop_1;
	end_loop_1:;
	  if (EQ(class_1,Qitem))
	      goto end_loop;
	  goto next_loop;
	end_loop:;
	  name_of_object = 
		  get_lookup_slot_value_given_default(focal_entity_qm,
		  Qname_or_names_for_frame,Nil);
	  if (name_of_object && SYMBOLP(name_of_object)) {
	      rule_of_this_object_name = Nil;
	      ab_loop_list_ = 
		      lookup_kb_specific_property_value(name_of_object,
		      Rules_of_this_class_or_object_name_kbprop);
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      rule_of_this_object_name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      categories_of_rule_of_this_object_name = 
		      ISVREF(rule_of_this_object_name,(SI_Long)24L);
	      category = Nil;
	      ab_loop_list__1 = CDR(query_restriction);
	      ab_loop_it_ = Nil;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_4;
	      category = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      ab_loop_it_ = memq_function(category,
		      categories_of_rule_of_this_object_name);
	      if (ab_loop_it_) {
		  temp = TRUEP(ab_loop_it_);
		  goto end_2;
	      }
	      goto next_loop_4;
	    end_loop_4:
	      temp = TRUEP(Qnil);
	    end_2:;
	      if (temp)
		  schedule_rule_instances_if_rule_is_not_embedded(rule_of_this_object_name,
			  Nil,Nil,Nil,Qinvoking);
	      goto next_loop_3;
	    end_loop_3:;
	  }
	  else if (CONSP(name_of_object)) {
	      name = Nil;
	      ab_loop_list_ = name_of_object;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_5;
	      name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      rule_of_this_object_name = Nil;
	      ab_loop_list__1 = lookup_kb_specific_property_value(name,
		      Rules_of_this_class_or_object_name_kbprop);
	    next_loop_6:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_6;
	      rule_of_this_object_name = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      categories_of_rule_of_this_object_name = 
		      ISVREF(rule_of_this_object_name,(SI_Long)24L);
	      category = Nil;
	      ab_loop_list__2 = CDR(query_restriction);
	      ab_loop_it_ = Nil;
	    next_loop_7:
	      if ( !TRUEP(ab_loop_list__2))
		  goto end_loop_7;
	      category = M_CAR(ab_loop_list__2);
	      ab_loop_list__2 = M_CDR(ab_loop_list__2);
	      ab_loop_it_ = memq_function(category,
		      categories_of_rule_of_this_object_name);
	      if (ab_loop_it_) {
		  temp = TRUEP(ab_loop_it_);
		  goto end_3;
	      }
	      goto next_loop_7;
	    end_loop_7:
	      temp = TRUEP(Qnil);
	    end_3:;
	      if (temp)
		  schedule_rule_instances_if_rule_is_not_embedded(rule_of_this_object_name,
			  Nil,Nil,Nil,Qinvoking);
	      goto next_loop_6;
	    end_loop_6:;
	      goto next_loop_5;
	    end_loop_5:;
	  }
      }
      else {
	  category = Nil;
	  ab_loop_list_ = CDR(query_restriction);
	next_loop_8:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_8;
	  category = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  rule_of_this_category = Nil;
	  ab_loop_list__1 = lookup_kb_specific_property_value(category,
		  Rules_of_this_category_kbprop);
	next_loop_9:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_9;
	  rule_of_this_category = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  schedule_rule_instances_if_rule_is_not_embedded(rule_of_this_category,
		  Nil,Nil,Nil,Qinvoking);
	  goto next_loop_9;
	end_loop_9:;
	  goto next_loop_8;
	end_loop_8:;
      }
      if (wait_p)
	  remove_completion_notification_collection_if_empty(Current_computation_instance);
      top_of_stack = FIX(IFIX(top_of_stack) - (SI_Long)2L);
      result = VALUES_1(top_of_stack);
    POP_SPECIAL();
    return result;
}

static Object Qparent_frame;       /* parent-frame */

/* SCHEDULE-RULE-INSTANCES-IF-RULE-IS-NOT-EMBEDDED */
Object schedule_rule_instances_if_rule_is_not_embedded(rule,focal_role_qm,
	    local_name_qm,focal_object_qm,purpose)
    Object rule, focal_role_qm, local_name_qm, focal_object_qm, purpose;
{
    Object parent_frame_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(205,218);
    parent_frame_qm = get_lookup_slot_value_given_default(rule,
	    Qparent_frame,Nil);
    if (parent_frame_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(parent_frame_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
	    sub_class_bit_vector = ISVREF(ISVREF(parent_frame_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(User_menu_choice_class_description,
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
	}
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return generate_and_schedule_rule_instances(rule,focal_role_qm,
		local_name_qm,focal_object_qm,purpose,Nil,Nil,Nil);
    else
	return VALUES_1(Nil);
}

/* EMIT-PUSH-VALUE-OR-NONE-FROM-LOCAL-VAR-BYTE-CODES */
Object emit_push_value_or_none_from_local_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,219);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)102L));
    write_byte_code_to_stream(byte_code_stream,SECOND(var_spot));
    return emit_typecode_to_stream(byte_code_stream,var_spot);
}

static Object string_constant_160;  /* "Top-of-stack was not -1." */

/* CHECK-STACK-ERROR-MESSAGE */
Object check_stack_error_message()
{
    x_note_fn_call(205,220);
    return tformat_stack_error_text_string(1,string_constant_160);
}

static Object array_constant_86;   /* # */

static Object array_constant_87;   /* # */

static Object string_constant_161;  /* " is not a valid element for the ~A ~NF." */

static Object string_constant_162;  /* "G2-array" */

static Object string_constant_163;  /* "G2-list" */

/* SIGNAL-COERCE-MATCHING-ELEMENT-TYPE-ERROR-1 */
Object signal_coerce_matching_element_type_error_1(g2_array_or_list,
	    bad_item_or_datum)
    Object g2_array_or_list, bad_item_or_datum;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, managed_number_or_value;
    Object sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(205,221);
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
		  twrite_beginning_of_wide_string(array_constant_86,
			  FIX((SI_Long)10L));
		  if (SIMPLE_VECTOR_P(bad_item_or_datum) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(bad_item_or_datum)) 
			  > (SI_Long)2L &&  !EQ(ISVREF(bad_item_or_datum,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(bad_item_or_datum,(SI_Long)1L);
		      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
			      EQ(ISVREF(x2,(SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      gensymed_symbol = Nil;
		  if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
		      tformat(2,string_constant_124,bad_item_or_datum);
		  else {
		      gensymed_symbol = bad_item_or_datum;
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
			  write_evaluation_value(1,bad_item_or_datum);
		      else if ( !TRUEP(bad_item_or_datum))
			  twrite_beginning_of_wide_string(array_constant_87,
				  FIX((SI_Long)4L));
		      else if (SIMPLE_VECTOR_P(bad_item_or_datum) && 
			      EQ(ISVREF(bad_item_or_datum,(SI_Long)0L),
			      Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
				  {
			  managed_number_or_value = 
				  ISVREF(bad_item_or_datum,(SI_Long)1L);
			  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				  == (SI_Long)1L)
			      temp_2 = 
				      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				      (SI_Long)0L));
			  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				  == (SI_Long)1L)
			      temp_2 = aref1(managed_number_or_value,
				      FIX((SI_Long)0L));
			  else
			      temp_2 = managed_number_or_value;
			  print_constant(2,temp_2,ISVREF(bad_item_or_datum,
				  (SI_Long)2L));
		      }
		      else
			  twrite(bad_item_or_datum);
		  }
		  sub_class_bit_vector = ISVREF(ISVREF(g2_array_or_list,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(G2_array_class_description,
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
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  tformat(3,string_constant_161,temp ? string_constant_162 
			  : string_constant_163,g2_array_or_list);
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

/* COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN */
Object coerce_matching_element_type_or_unknown(g2_array_or_list,
	    item_or_evaluation_value_element,top_of_stack,unknown_allowed_qm)
    Object g2_array_or_list, item_or_evaluation_value_element, top_of_stack;
    Object unknown_allowed_qm;
{
    Object sub_class_bit_vector, g2_array_p_qm, element_type;
    Object possible_item_element_p_qm, element_qm, x2;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, new_result, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double aref_new_value;

    x_note_fn_call(205,222);
    sub_class_bit_vector = ISVREF(ISVREF(g2_array_or_list,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	g2_array_p_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	g2_array_p_qm = Nil;
    element_type = g2_array_p_qm ? ISVREF(g2_array_or_list,(SI_Long)21L) : 
	    ISVREF(g2_array_or_list,(SI_Long)21L);
    possible_item_element_p_qm = 
	    g2_list_or_array_element_type_may_contain_item_p(element_type);
    element_qm = FIXNUMP(item_or_evaluation_value_element) || 
	    item_or_evaluation_value_element && 
	    SYMBOLP(item_or_evaluation_value_element) || 
	    SIMPLE_VECTOR_P(item_or_evaluation_value_element) ? 
	    item_or_evaluation_value_element : 
	    copy_if_evaluation_value_1(item_or_evaluation_value_element);
    if ( !TRUEP(possible_item_element_p_qm)) {
	if (SIMPLE_VECTOR_P(element_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_qm)) > (SI_Long)2L 
		&&  !EQ(ISVREF(element_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(element_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (unknown_allowed_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(element_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(element_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Cached_top_of_stack = top_of_stack;
	element_qm = EQ(Current_environment,Qinference_engine) || 
		EQ(Current_environment,Qprocedure) ? 
		get_current_evaluation_value(element_qm,Nil) : 
		get_current_evaluation_value_from_simulation_environment(element_qm);
    }
    if ( !TRUEP(element_qm) && possible_item_element_p_qm)
	return VALUES_1(Nil);
    else if ( !TRUEP(element_qm) && unknown_allowed_qm && 
	    item_or_evaluation_value_element)
	return VALUES_1(Nil);
    else if (FIXNUMP(element_qm) && EQ(element_type,Qfloat)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	aref_new_value = (double)IFIX(element_qm);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	new_result = new_float;
	return VALUES_1(new_result);
    }
    else if (g2_list_or_array_element_ok_p(element_qm,element_type))
	return VALUES_1(element_qm);
    else {
	temp_3 = 
		signal_coerce_matching_element_type_error_1(g2_array_or_list,
		element_qm);
	if ( !(FIXNUMP(element_qm) || SYMBOLP(element_qm) || 
		SIMPLE_VECTOR_P(element_qm)))
	    reclaim_if_evaluation_value_1(element_qm);
	return VALUES_2(Nil,temp_3);
    }
}

/* EMIT-COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN-IF-NECESSARY */
Object emit_coerce_matching_element_type_or_unknown_if_necessary(byte_code_stream,
	    g2_array_or_list_stack_node,element_stack_node,unknown_allowed_qm)
    Object byte_code_stream, g2_array_or_list_stack_node, element_stack_node;
    Object unknown_allowed_qm;
{
    x_note_fn_call(205,223);
    if ( 
	    !TRUEP(stack_node_matches_element_type_p(g2_array_or_list_stack_node,
	    element_stack_node))) {
	if (unknown_allowed_qm)
	    return write_byte_code_to_stream(byte_code_stream,
		    FIX((SI_Long)106L));
	else
	    return write_byte_code_to_stream(byte_code_stream,
		    FIX((SI_Long)107L));
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

/* STACK-NODE-MATCHES-ELEMENT-TYPE-P */
Object stack_node_matches_element_type_p(g2_array_or_list_stack_node,
	    element_stack_node)
    Object g2_array_or_list_stack_node, element_stack_node;
{
    Object sequence_type, sequence_class_qm, contained_type_qm, value_type;

    x_note_fn_call(205,224);
    sequence_type = 
	    type_specification_minus_type(ISVREF(g2_array_or_list_stack_node,
	    (SI_Long)6L),list_constant_4);
    sequence_class_qm = class_type_specification_p(sequence_type) ? 
	    M_CAR(M_CDR(sequence_type)) : Qnil;
    contained_type_qm = sequence_class_qm ? 
	    g2_list_or_array_class_element_type(sequence_class_qm,T) : Qnil;
    value_type = type_specification_minus_type(ISVREF(element_stack_node,
	    (SI_Long)6L),list_constant_4);
    if (contained_type_qm) {
	if (EQ(contained_type_qm,Qinteger))
	    return VALUES_1(EQ(value_type,Qinteger) ? T : Nil);
	else if (EQ(contained_type_qm,Qfloat))
	    return VALUES_1(EQ(value_type,Qfloat) ? T : Nil);
	else if (EQ(contained_type_qm,Qtruth_value))
	    return VALUES_1(EQ(value_type,Qtruth_value) ? T : Nil);
	else if (EQ(contained_type_qm,Qsymbol))
	    return VALUES_1(EQ(value_type,Qsymbol) ? T : Nil);
	else if (EQ(contained_type_qm,Qtext))
	    return VALUES_1(EQ(value_type,Qtext) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_164;  /* "pop-into-block-of-local-vars emitter" */

static Object string_constant_165;  /* "An invalid variable location, ~a, was given." */

/* EMIT-POP-INTO-BLOCK-OF-LOCAL-VARS-BYTE-CODES */
Object emit_pop_into_block_of_local_vars_byte_codes(byte_code_stream,
	    first_var_spot,count_1)
    Object byte_code_stream, first_var_spot, count_1;
{
    Object overflows, remainder_1, first_index;
    SI_Long ab_loop_repeat_, first_index_new_value;
    Object result;

    x_note_fn_call(205,225);
    if ( !TRUEP(valid_var_spot_p(first_var_spot))) {
	compiler_bug(3,string_constant_164,string_constant_165,first_var_spot);
	first_var_spot = list_constant_2;
    }
    result = lfloor(count_1,FIX((SI_Long)255L));
    MVS_2(result,overflows,remainder_1);
    first_index = SECOND(first_var_spot);
    ab_loop_repeat_ = IFIX(overflows);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)109L));
    emit_long_code_constant_to_stream(byte_code_stream,first_index);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)255L));
    first_index_new_value = IFIX(first_index) + (SI_Long)255L;
    first_index = FIX(first_index_new_value);
    goto next_loop;
  end_loop:;
    if (IFIX(remainder_1) > (SI_Long)0L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)109L));
	emit_long_code_constant_to_stream(byte_code_stream,first_index);
	return write_byte_code_to_stream(byte_code_stream,remainder_1);
    }
    else
	return VALUES_1(Nil);
}

/* EMIT-PUSH-FROM-BLOCK-OF-LOCAL-VARS-BYTE-CODES */
Object emit_push_from_block_of_local_vars_byte_codes(byte_code_stream,
	    first_var_spot,count_1)
    Object byte_code_stream, first_var_spot, count_1;
{
    Object overflows, remainder_1, first_index;
    SI_Long ab_loop_repeat_, first_index_new_value;
    Object result;

    x_note_fn_call(205,226);
    result = lfloor(count_1,FIX((SI_Long)255L));
    MVS_2(result,overflows,remainder_1);
    first_index = SECOND(first_var_spot);
    ab_loop_repeat_ = IFIX(overflows);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)110L));
    emit_long_code_constant_to_stream(byte_code_stream,first_index);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)255L));
    first_index_new_value = IFIX(first_index) + (SI_Long)255L;
    first_index = FIX(first_index_new_value);
    goto next_loop;
  end_loop:;
    if (IFIX(remainder_1) > (SI_Long)0L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)110L));
	emit_long_code_constant_to_stream(byte_code_stream,first_index);
	return write_byte_code_to_stream(byte_code_stream,remainder_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qaction_cache;       /* action-cache */

/* EXECUTE-ADD-TO-ACTION-CACHE */
Object execute_add_to_action_cache(local_vars,cache_index,value_count,
	    target_index)
    Object local_vars, cache_index, value_count, target_index;
{
    Object action_cache, vector_1, ab_loop_iter_flag_, temp, temp_1;
    Object new_element;
    SI_Long index_1, ab_loop_bind_, target;

    x_note_fn_call(205,227);
    action_cache = ISVREF(local_vars,IFIX(cache_index));
    if (IFIX(value_count) != (SI_Long)0L) {
	vector_1 = 
		allocate_managed_simple_vector(buffer_size_for_partial_buffer(value_count,
		Environment_allocation_schemes));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(value_count);
	target = IFIX(target_index);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    target = target + (SI_Long)1L;
	temp = ISVREF(local_vars,target);
	ISVREF(vector_1,index_1) = temp;
	ISVREF(local_vars,target) = Nil;
	ab_loop_iter_flag_ = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	index_1 = IFIX(value_count);
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(vector_1,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	temp_1 = vector_1;
    }
    else
	temp_1 = Nil;
    new_element = eval_cons_1(value_count,temp_1);
    if ( !TRUEP(action_cache)) {
	action_cache = eval_cons_1(eval_cons_1(new_element,Nil),Qaction_cache);
	return VALUES_1(SVREF(local_vars,cache_index) = action_cache);
    }
    else {
	temp = eval_cons_1(new_element,M_CAR(action_cache));
	return VALUES_1(M_CAR(action_cache) = temp);
    }
}

static Object string_constant_166;  /* "add to action cache byte code emitter" */

/* EMIT-ADD-TO-ACTION-CACHE-BYTE-CODES */
Object emit_add_to_action_cache_byte_codes(byte_code_stream,
	    action_cache_var_spot,var_spot_block)
    Object byte_code_stream, action_cache_var_spot, var_spot_block;
{
    Object temp;

    x_note_fn_call(205,228);
    if (action_cache_and_var_spot_block_ok_p(action_cache_var_spot,
	    var_spot_block,string_constant_166)) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)112L));
	emit_long_code_constant_to_stream(byte_code_stream,
		SECOND(action_cache_var_spot));
	emit_long_code_constant_to_stream(byte_code_stream,
		length(var_spot_block));
	if (var_spot_block) {
	    temp = CAR(var_spot_block);
	    temp = SECOND(temp);
	}
	else
	    temp = FIX((SI_Long)0L);
	return emit_long_code_constant_to_stream(byte_code_stream,temp);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_167;  /* "The action cache location ~a wasn't local." */

static Object string_constant_168;  /* "The initial spot ~a wasn't local." */

static Object string_constant_169;  /* "An element of the variable block was out of order or not local.  ~
				     *                Expected index was ~a, actual was ~a."
				     */

/* ACTION-CACHE-AND-VAR-SPOT-BLOCK-OK-P */
Object action_cache_and_var_spot_block_ok_p(action_cache_var_spot,
	    var_spot_block,location_string)
    Object action_cache_var_spot, var_spot_block, location_string;
{
    Object initial_spot, initial_index, var_spot, ab_loop_list_, index_1;
    SI_Long expected_index;

    x_note_fn_call(205,229);
    initial_spot = CAR(var_spot_block);
    initial_index = SECOND(initial_spot);
    if ( !(IFIX(SECOND(action_cache_var_spot)) >>  -  - (SI_Long)10L == 
	    (SI_Long)0L)) {
	compiler_bug(3,location_string,string_constant_167,
		action_cache_var_spot);
	return VALUES_1(Nil);
    }
    if (var_spot_block) {
	if ( !FIXNUMP(initial_index)) {
	    compiler_bug(3,location_string,string_constant_168,initial_spot);
	    return VALUES_1(Nil);
	}
	expected_index = IFIX(FIXNUM_ADD1(initial_index));
	var_spot = Nil;
	ab_loop_list_ = CDR(var_spot_block);
	index_1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	var_spot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	index_1 = SECOND(var_spot);
	if ( !FIXNUMP(index_1) || IFIX(index_1) != expected_index) {
	    compiler_bug(4,location_string,string_constant_169,
		    FIX(expected_index),index_1);
	    return VALUES_1(Nil);
	}
	expected_index = expected_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(T);
}

static Object string_constant_170;  /* "An internal G2 error has occurred restoring action-cache ~
				     *                   values.  Attempt to restore ~a elements from a ~a element
				     *                   cache."
				     */

/* RESTORE-FROM-ACTION-CACHE */
Object restore_from_action_cache(local_vars,cache_index,value_count,
	    target_index,top_of_stack)
    Object local_vars, cache_index, value_count, target_index, top_of_stack;
{
    Object action_cache, cache_list, cache_to_restore, rest_of_cache_list;
    Object count_1, vector_1, top_of_stack_1, message_1, old_value;
    Object ab_loop_iter_flag_, temp, svref_arg_2;
    SI_Long index_1, ab_loop_bind_, local_var_index;

    x_note_fn_call(205,230);
    action_cache = ISVREF(local_vars,IFIX(cache_index));
    if (action_cache) {
	cache_list = M_CAR(action_cache);
	if (cache_list) {
	    cache_to_restore = M_CAR(cache_list);
	    rest_of_cache_list = M_CDR(cache_list);
	    count_1 = M_CAR(cache_to_restore);
	    vector_1 = M_CDR(cache_to_restore);
	    if (FIXNUM_NE(count_1,value_count)) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_170,value_count,count_1);
		raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    if (IFIX(value_count) != (SI_Long)0L) {
		index_1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(value_count);
		local_var_index = IFIX(target_index);
		old_value = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index_1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    local_var_index = local_var_index + (SI_Long)1L;
		old_value = ISVREF(local_vars,local_var_index);
		if ( !(FIXNUMP(old_value) || SYMBOLP(old_value) || 
			SIMPLE_VECTOR_P(old_value)))
		    reclaim_if_evaluation_value_1(old_value);
		temp = ISVREF(vector_1,index_1);
		ISVREF(local_vars,local_var_index) = temp;
		ab_loop_iter_flag_ = Nil;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
		reclaim_managed_simple_vector(vector_1);
	    }
	    inline_note_reclaim_cons(cache_to_restore,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cache_to_restore;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_to_restore;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_to_restore;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_to_restore;
	    }
	    M_CDR(cache_to_restore) = Nil;
	    inline_note_reclaim_cons(cache_list,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cache_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_list;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_list;
	    }
	    M_CDR(cache_list) = Nil;
	    cache_list = rest_of_cache_list;
	    M_CAR(action_cache) = cache_list;
	    if ( !TRUEP(cache_list)) {
		reclaim_evaluation_action_cache(action_cache);
		SVREF(local_vars,cache_index) = Nil;
	    }
	    return VALUES_1(T);
	}
	else {
	    reclaim_evaluation_action_cache(action_cache);
	    SVREF(local_vars,cache_index) = Nil;
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_171;  /* "restore from action cache byte code emitter" */

/* EMIT-RESTORE-FROM-ACTION-CACHE-OR-BRANCH-BYTE-CODES */
Object emit_restore_from_action_cache_or_branch_byte_codes(byte_code_stream,
	    action_cache_var_spot,var_spot_block,empty_tag)
    Object byte_code_stream, action_cache_var_spot, var_spot_block, empty_tag;
{
    Object temp;

    x_note_fn_call(205,231);
    if (action_cache_and_var_spot_block_ok_p(action_cache_var_spot,
	    var_spot_block,string_constant_171)) {
	register_byte_code_tag_resolution_point(byte_code_stream,empty_tag);
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)113L));
	emit_long_code_constant_to_stream(byte_code_stream,
		SECOND(action_cache_var_spot));
	emit_long_code_constant_to_stream(byte_code_stream,
		length(var_spot_block));
	if (var_spot_block) {
	    temp = CAR(var_spot_block);
	    temp = SECOND(temp);
	}
	else
	    temp = FIX((SI_Long)0L);
	emit_long_code_constant_to_stream(byte_code_stream,temp);
	return emit_long_code_constant_to_stream(byte_code_stream,
		FIX((SI_Long)0L));
    }
    else
	return VALUES_1(Nil);
}

/* BC-RESTORE-FROM-ACTION-CACHE-OR-BRANCH-RESOLVER */
Object bc_restore_from_action_cache_or_branch_resolver(byte_code_stream,
	    byte_vector,address,tag)
    Object byte_code_stream, byte_vector, address, tag;
{
    Object temp;

    x_note_fn_call(205,232);
    temp = FIX(IFIX(address) + (SI_Long)7L);
    setf_long_code_constant(byte_vector,temp,
	    instruction_address_for_tag(tag,Nil));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

/* RUNS-WHILE-RESET-PROCEDURE-P */
Object runs_while_reset_procedure_p()
{
    Object type_name, invocation_qm, block, temp_1;
    char temp;

    x_note_fn_call(205,233);
    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	invocation_qm = ISVREF(Current_computation_instance,(SI_Long)11L);
	if (invocation_qm) {
	    block = ISVREF(invocation_qm,(SI_Long)23L);
	    temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		    (SI_Long)16777216L) ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* G2-GET-BLOCKS-NEEDING-STATUS-REFRESHED */
Object g2_get_blocks_needing_status_refreshed()
{
    Object pre_sequence, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    char temp;
    Declare_special(1);

    x_note_fn_call(205,234);
    pre_sequence = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      if (ISVREF(block,(SI_Long)9L) && 
	      frame_status_and_notes_reflects_flags_of_frame_p(block))
	  pre_sequence = eval_cons_1(block,pre_sequence);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return allocate_evaluation_sequence(nreverse(pre_sequence));
}

static Object Qkb_workspace;       /* kb-workspace */

/* G2-GET-TOP-LEVEL-TRANSIENT-WORKSPACES */
Object g2_get_top_level_transient_workspaces()
{
    Object pre_sequence, scope_conses, ab_loopvar_, ab_loopvar__1, item;
    char temp;
    Declare_special(1);

    x_note_fn_call(205,235);
    pre_sequence = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qkb_workspace);
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
      if ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	      (SI_Long)262144L) &&  !TRUEP(ISVREF(item,(SI_Long)18L)))
	  pre_sequence = eval_cons_1(item,pre_sequence);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return allocate_evaluation_sequence(nreverse(pre_sequence));
}

/* G2-GET-TOP-LEVEL-TRANSIENT-ITEMS-AND-CONNECTIONS */
Object g2_get_top_level_transient_items_and_connections()
{
    Object pre_item_sequence, pre_connection_sequence, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, block, superior_qm, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object temp_1, ab_less_than_branch_qm_, temp_2;
    char temp;
    Declare_special(2);

    x_note_fn_call(205,236);
    pre_item_sequence = Nil;
    pre_connection_sequence = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      superior_qm = Nil;
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
      superior_qm = superior_frame(block);
      if (ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L)) {
	  if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		  (SI_Long)262144L) && ( !TRUEP(superior_qm) ||  
		  !((SI_Long)0L != (IFIX(ISVREF(superior_qm,(SI_Long)5L)) 
		  & (SI_Long)262144L))))
	      pre_item_sequence = eval_cons_1(block,pre_item_sequence);
	  remove_transient_relation_instances(block,T);
      }
      if ( !EQ(CAR(pre_item_sequence),block)) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	  ab_skip_list_form_ = gensymed_symbol;
	  ab_skip_list_p_ = Nil;
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_connection_ = Nil;
	  ab_connection_item_ = Nil;
	  connection = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    gensymed_symbol = CDR(ab_skip_list_form_);
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
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = CDR(ab_skip_list_form_);
	  next_loop_2:
	  next_loop_3:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_connection_ = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
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
		    ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		    ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
		}
		else
		    ab_current_node_ = Nil;
	    }
	    else {
		if (ab_next_node_) {
		    ab_current_node_ = ab_next_node_;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_4:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_4;
		  end_loop_2:;
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
		    ab_connection_ = M_CAR(ab_entry_cons_);
		    ab_connection_item_ = M_CDR(ab_entry_cons_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		    ab_connection_ && EQ(ISVREF(ab_connection_,
		    (SI_Long)3L),block))
		goto end_1;
	    goto next_loop_3;
	  end_loop_3:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_4;
	    connection = ab_connection_;
	    if ((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)64L)) {
		temp_1 = ISVREF(connection,(SI_Long)1L);
		temp = SYMBOLP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		pre_connection_sequence = eval_cons_1(connection,
			pre_connection_sequence);
	    goto next_loop_2;
	  end_loop_4:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    temp_2 = allocate_evaluation_sequence(nreverse(pre_item_sequence));
    temp_1 = allocate_evaluation_sequence(nreverse(pre_connection_sequence));
    return VALUES_2(temp_2,temp_1);
}

static Object Qg2_extension;       /* g2-extension */

static Object Qmessage_board;      /* message-board */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

/* G2-COMPLETE-RESET-KB */
Object g2_complete_reset_kb(evaluation_sequence)
    Object evaluation_sequence;
{
    Object items_to_delete, delete_connections_without_leaving_stubs_qm;
    Object connections_to_delete, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object item;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object serial_number, ab_loop_list_, gensymed_symbol, xa, ya, block;
    Object superior_qm, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object temp_1, ab_less_than_branch_qm_, g2_extension, gensymed_symbol_1;
    Object gensymed_symbol_2, message_board_qm, server, shut_down_function_qm;
    Object held_vector, elt_1, validated_elt;
    SI_Long next_index, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(205,237);
    SAVE_STACK();
    LOCK(Procedure_invocations_lock);
    if (PUSH_UNWIND_PROTECT(0))
	clear_procedure_invocations_1();
    POP_UNWIND_PROTECT(0);
    UNLOCK(Procedure_invocations_lock);
    CONTINUE_UNWINDING(0);
    items_to_delete = Nil;
    delete_connections_without_leaving_stubs_qm = T;
    connections_to_delete = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm,Qdelete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
	    2);
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      item = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qkb_workspace);
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
	if ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)262144L) &&  !TRUEP(ISVREF(item,(SI_Long)18L)))
	    items_to_delete = gensym_cons_1(item,items_to_delete);
	goto next_loop;
      end_loop_1:;
      POP_SPECIAL();
      inhibit_updating_module_related_frame_notes_for_all_workspaces_qm = T;
      PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
	      0);
	serial_number = copy_frame_serial_number(Current_frame_serial_number);
	item = Nil;
	ab_loop_list_ = items_to_delete;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(item,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp)
	    delete_frame(item);
	goto next_loop_2;
      end_loop_2:
	reclaim_frame_serial_number(serial_number);
      POP_SPECIAL();
      if ( 
	      !TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm))
	  update_module_related_frame_notes_for_all_workspaces(0);
      reclaim_gensym_list_1(items_to_delete);
      items_to_delete = Nil;
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      block = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	superior_qm = Nil;
	ab_loopvar_ = collect_subclasses(Qblock);
      next_loop_3:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_4:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_3;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_3;
	    goto next_loop_4;
	  end_loop_3:
	    temp =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    goto end_loop_4;
	block = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	superior_qm = superior_frame(block);
	if (ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L)) {
	    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		    (SI_Long)262144L) && ( !TRUEP(superior_qm) ||  
		    !((SI_Long)0L != (IFIX(ISVREF(superior_qm,
		    (SI_Long)5L)) & (SI_Long)262144L))))
		items_to_delete = gensym_cons_1(block,items_to_delete);
	    remove_transient_relation_instances(block,T);
	}
	if ( !EQ(CAR(items_to_delete),block)) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol;
	    ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_connection_ = Nil;
	    ab_connection_item_ = Nil;
	    connection = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      gensymed_symbol = CDR(ab_skip_list_form_);
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
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = CDR(ab_skip_list_form_);
	    next_loop_5:
	    next_loop_6:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
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
		      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_connection_item_ = ISVREF(ab_current_node_,
			      (SI_Long)3L);
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_7:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_5;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_7;
		    end_loop_5:;
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
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_ && EQ(ISVREF(ab_connection_,
		      (SI_Long)3L),block))
		  goto end_1;
	      goto next_loop_6;
	    end_loop_6:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_7;
	      connection = ab_connection_;
	      if ((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)64L)) {
		  temp_1 = ISVREF(connection,(SI_Long)1L);
		  temp = SYMBOLP(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  connections_to_delete = gensym_cons_1(connection,
			  connections_to_delete);
	      goto next_loop_5;
	    end_loop_7:;
	    POP_SPECIAL();
	}
	goto next_loop_3;
      end_loop_4:;
      POP_SPECIAL();
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      g2_extension = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qg2_extension);
      next_loop_8:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_9:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_8;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_8;
	    goto next_loop_9;
	  end_loop_8:
	    temp =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    goto end_loop_9;
	g2_extension = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	gensymed_symbol = ACCESS_ONCE(ISVREF(g2_extension,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if (gensymed_symbol) {
	    temp_1 = ISVREF(g2_extension,(SI_Long)8L);
	    temp =  !TRUEP(CAR(temp_1));
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_extension,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_1 = g2_extension;
	    gensymed_symbol_2 = Nil;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	goto next_loop_8;
      end_loop_9:;
      POP_SPECIAL();
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      block = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qkb_workspace);
      next_loop_10:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_11:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_10;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_10;
	    goto next_loop_11;
	  end_loop_10:
	    temp =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    goto end_loop_11;
	block = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if ( !TRUEP(gensymed_symbol) ?  !TRUEP(ISVREF(block,(SI_Long)18L)) 
		: TRUEP(Nil)) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_1 = block;
	    gensymed_symbol_2 = Nil;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	goto next_loop_10;
      end_loop_11:;
      POP_SPECIAL();
      message_board_qm = get_instance_with_name_if_any(Qmessage_board,
	      Qmessage_board);
      if (message_board_qm) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(message_board_qm,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	  gensymed_symbol_1 = message_board_qm;
	  gensymed_symbol_2 = Nil;
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2);
      }
      clear_g2_schedule();
      undo_kb_state_changes();
      clear_inform_messages();
      server = Nil;
      ab_loop_list_ = List_of_all_data_servers;
      shut_down_function_qm = Nil;
    next_loop_12:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_12;
      server = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      shut_down_function_qm = ISVREF(server,(SI_Long)9L);
      if (shut_down_function_qm)
	  FUNCALL_0(SYMBOL_FUNCTION(shut_down_function_qm));
      goto next_loop_12;
    end_loop_12:;
      cancel_data_server_accept_data_calls();
      gensymed_symbol = evaluation_sequence;
      held_vector = Nil;
      next_index = (SI_Long)1L;
      length_1 = (SI_Long)0L;
      block = Nil;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop_13:
      if (next_index >= length_1)
	  goto end_loop_13;
      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	      Nil) : Nil;
      next_index = next_index + (SI_Long)1L;
      block = validated_elt;
      update_representations_of_slot_value(2,block,Qframe_status_and_notes);
      goto next_loop_13;
    end_loop_13:;
      Gensym_time_at_start = Gensym_time;
      result = VALUES_1(Gensym_time_at_start);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_172;  /* "NUPEC-SYNCHRONIZE" */

static Object string_constant_173;  /* "This knowledge base was written in a NUPEC enhanced ~
				     *        version of G2, but this version of G2 is not enhanced ~
				     *        for NUPEC.  The NUPEC SYNCHRONIZE instruction cannot ~
				     *        be executed."
				     */

static Object string_constant_174;  /* "In the NUPEC synchronize action, ~NF is not an instance of a class ~
				     *          containing the G2-to-G2-data-inferface capability."
				     */

static Object string_constant_175;  /* "In the NUPEC synchronize action, ~a is not a defined class." */

/* EXECUTE-NUPEC-SYNCHRONIZE-STACK-INSTRUCTION */
Object execute_nupec_synchronize_stack_instruction(local_stack,
	    top_of_stack,constant_vector,arg_count)
    Object local_stack, top_of_stack, constant_vector, arg_count;
{
    Object code, top_of_stack_1, message_1, class_list_stack_index;
    Object class_list_constant_index, class_list, stack_index, g2_to_g2_object;
    Object items_to_synchronize, item, class_1, ab_loop_list_, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, scope_conses, ab_loopvar_, ab_loopvar__1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(205,238);
    if (Evaluating_simulator_procedure_qm)
	not_a_simulator_procedure_instruction(string_constant_172,
		top_of_stack);
    code = M_CAR(M_CDR(Journal_shutout_scan_p));
    if ( !(FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) : TRUEP(Nil))) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_173);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    class_list_stack_index = top_of_stack;
    class_list_constant_index = ISVREF(local_stack,
	    IFIX(class_list_stack_index));
    class_list = ISVREF(constant_vector,IFIX(class_list_constant_index));
    stack_index = FIXNUM_ADD1(FIXNUM_MINUS(top_of_stack,arg_count));
    g2_to_g2_object = ISVREF(local_stack,IFIX(stack_index));
    items_to_synchronize = Nil;
    if ( !TRUEP(g2_to_g2_data_interface_p_function(g2_to_g2_object))) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_174,
		g2_to_g2_object);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    if ( !(IFIX(arg_count) <= (SI_Long)2L)) {
	stack_index = FIXNUM_ADD1(stack_index);
	item = Nil;
      next_loop:
	if ( !NUM_LT(stack_index,class_list_stack_index))
	    goto end_loop;
	item = ISVREF(local_stack,IFIX(stack_index));
	items_to_synchronize = eval_cons_1(item,items_to_synchronize);
	stack_index = FIXNUM_ADD1(stack_index);
	goto next_loop;
      end_loop:;
    }
    class_1 = Nil;
    ab_loop_list_ = class_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
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
  next_loop_2:
    if (level < ab_loop_bind_)
	goto end_loop_2;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_3:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_4:
    if ( !TRUEP(marked))
	goto end_loop_3;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
  next_loop_5:
    if (level < ab_loop_bind_)
	goto end_loop_5;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_6:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_7:
    if ( !TRUEP(marked))
	goto end_loop_6;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_7;
  end_loop_6:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_6;
  end_loop_7:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_5;
  end_loop_5:;
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
      next_loop_8:
	if (level < ab_loop_bind_)
	    goto end_loop_8;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_9:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_10:
	if ( !TRUEP(marked))
	    goto end_loop_9;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_10;
      end_loop_9:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_9;
      end_loop_10:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_8;
      end_loop_8:;
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
      next_loop_11:
	if (level < ab_loop_bind_)
	    goto end_loop_11;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_12:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_13:
	if ( !TRUEP(marked))
	    goto end_loop_12;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_13;
      end_loop_12:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_12;
      end_loop_13:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_11;
      end_loop_11:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(class_1);
	next_loop_14:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_15:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_14;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_14;
	      goto next_loop_15;
	    end_loop_14:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_15;
	  item = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (serve_item_p(item))
	      items_to_synchronize = eval_cons_1(item,items_to_synchronize);
	  goto next_loop_14;
	end_loop_15:;
	POP_SPECIAL();
    }
    else {
	reclaim_eval_list_1(items_to_synchronize);
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_175,
		class_1);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    goto next_loop_1;
  end_loop_1:;
    nupec_synchronize(variables_and_parameters_in_items(items_to_synchronize),
	    g2_to_g2_object);
    Forgive_long_procedure_instruction_qm = T;
    reclaim_eval_list_1(items_to_synchronize);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Items_to_traverse, Qitems_to_traverse);

/* ADD-TO-ITEMS-TO-TRAVERSE */
Object add_to_items_to_traverse(item)
    Object item;
{
    Object temp;

    x_note_fn_call(205,239);
    if (serve_item_p(item)) {
	Items_to_traverse = eval_cons_1(item,Items_to_traverse);
	temp = Items_to_traverse;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qadd_to_items_to_traverse;  /* add-to-items-to-traverse */

/* VARIABLES-AND-PARAMETERS-IN-ITEMS */
Object variables_and_parameters_in_items(item_list)
    Object item_list;
{
    Object items_to_traverse, items_to_return, item_cons, item, temp;
    Object svref_arg_2, sub_class_bit_vector, slot_description;
    Object class_description, ab_loop_list_, vector_slot_index_qm, slot_value;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm, x2, gensymed_symbol_3, gensymed_symbol_4;
    Object ab_queue_form_, ab_next_queue_element_, subblock, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object connection_frame_or_class, temp_2, ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, max_i, i, ab_loop_bind_;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(205,240);
    items_to_traverse = copy_list_using_eval_conses_1(item_list);
    items_to_return = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Items_to_traverse,Qitems_to_traverse,items_to_traverse,
	    1);
      item_cons = Nil;
      item = Nil;
    next_loop:
      if ( !TRUEP(Items_to_traverse))
	  goto end_loop;
      item_cons = Items_to_traverse;
      item = CAR(item_cons);
      Items_to_traverse = CDR(item_cons);
      inline_note_reclaim_cons(item_cons,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = item_cons;
	  temp = Available_eval_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = item_cons;
      }
      else {
	  temp = Available_eval_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = item_cons;
	  temp = Available_eval_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = item_cons;
      }
      M_CDR(item_cons) = Nil;
      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Variable_or_parameter_class_description,
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
	      items_to_return = eval_cons_1(item,items_to_return);
	  slot_description = Nil;
	  class_description = ISVREF(item,(SI_Long)1L);
	  ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  slot_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ISVREF(slot_description,(SI_Long)8L)) {
	      vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	      if (vector_slot_index_qm)
		  slot_value = ISVREF(item,IFIX(vector_slot_index_qm));
	      else {
		  user_vector_slot_index_qm = ISVREF(slot_description,
			  (SI_Long)8L);
		  if (user_vector_slot_index_qm)
		      slot_value = ISVREF(ISVREF(item,(SI_Long)0L),
			      IFIX(user_vector_slot_index_qm));
		  else {
		      slot_name = ISVREF(slot_description,(SI_Long)1L);
		      lookup_structure_qm = ISVREF(item,(SI_Long)0L);
		      if (lookup_structure_qm) {
			  max_i = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			  max_i = max_i - (SI_Long)1L;
			  i = IFIX(ISVREF(ISVREF(item,(SI_Long)1L),
				  (SI_Long)15L));
			  ab_loop_bind_ = max_i;
			next_loop_2:
			  if (i >= ab_loop_bind_)
			      goto end_loop_2;
			  if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			      slot_index_qm = FIX(i + (SI_Long)1L);
			      goto end_1;
			  }
			  i = i + (SI_Long)2L;
			  goto next_loop_2;
			end_loop_2:
			  slot_index_qm = Qnil;
			end_1:;
			  slot_value = slot_index_qm ? 
				  ISVREF(lookup_structure_qm,
				  IFIX(slot_index_qm)) : 
				  ISVREF(slot_description,(SI_Long)6L);
		      }
		      else
			  slot_value = ISVREF(slot_description,(SI_Long)6L);
		  }
	      }
	      if (SIMPLE_VECTOR_P(slot_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(slot_value,(SI_Long)1L);
		  gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol_3 = Nil;
	      if (gensymed_symbol_3 && ISVREF(gensymed_symbol_3,
			  (SI_Long)16L)) {
		  gensymed_symbol_3 = 
			  SYMBOL_FUNCTION(Qadd_to_items_to_traverse);
		  gensymed_symbol_4 = slot_value;
		  inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
	      }
	  }
	  goto next_loop_1;
	end_loop_1:;
      }
      else {
	  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
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
	      temp_1 = (SI_Long)0L < gensymed_symbol;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      gensymed_symbol_3 = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	      gensymed_symbol_3 = gensymed_symbol_3 ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	      ab_queue_form_ = gensymed_symbol_3;
	      ab_next_queue_element_ = Nil;
	      subblock = Nil;
	      if (ab_queue_form_)
		  ab_next_queue_element_ = 
			  constant_queue_next(ISVREF(ab_queue_form_,
			  (SI_Long)2L),ab_queue_form_);
	    next_loop_3:
	      if ( !TRUEP(ab_next_queue_element_))
		  goto end_loop_3;
	      subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	      ab_next_queue_element_ = 
		      constant_queue_next(ab_next_queue_element_,
		      ab_queue_form_);
	      if (ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)16L)) {
		  sub_class_bit_vector = ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp_1 = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1);
		  else {
		      sub_class_bit_vector = ISVREF(ISVREF(subblock,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Message_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp_1 = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? TRUEP(serve_item_p(subblock)) : TRUEP(Nil)) {
		  Items_to_traverse = eval_cons_1(subblock,Items_to_traverse);
		  scope_conses = Scope_conses;
		  ab_node_stack_ = Nil;
		  ab_current_node_ = Nil;
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subblock,
			  (SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)6L)) : Nil;
		  ab_skip_list_form_ = gensymed_symbol_3;
		  ab_skip_list_p_ = Nil;
		  ab_next_node_ = Nil;
		  ab_tail_node_ = Nil;
		  ab_current_alist_ = Nil;
		  ab_entry_cons_ = Nil;
		  ab_connection_ = Nil;
		  ab_connection_item_ = Nil;
		  connection = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			  0);
		    connection_frame_or_class = Nil;
		    gensymed_symbol_3 = CDR(ab_skip_list_form_);
		    if (CONSP(gensymed_symbol_3)) {
			temp_2 = M_CAR(gensymed_symbol_3);
			temp_1 = SIMPLE_VECTOR_P(temp_2);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			temp_2 = M_CDR(gensymed_symbol_3);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_2) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		    if (ab_skip_list_p_) {
			ab_next_node_ = 
				ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
				(SI_Long)0L),(SI_Long)0L));
			ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
			if (EQ(ab_next_node_,ab_tail_node_))
			    ab_next_node_ = Nil;
		    }
		    else
			ab_next_node_ = CDR(ab_skip_list_form_);
		  next_loop_4:
		  next_loop_5:
		    if (ab_current_alist_) {
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_connection_ = M_CAR(ab_entry_cons_);
			ab_connection_item_ = M_CDR(ab_entry_cons_);
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
			    ab_connection_ = ISVREF(ab_current_node_,
				    (SI_Long)2L);
			    ab_connection_item_ = ISVREF(ab_current_node_,
				    (SI_Long)3L);
			}
			else
			    ab_current_node_ = Nil;
		    }
		    else {
			if (ab_next_node_) {
			    ab_current_node_ = ab_next_node_;
			    ab_less_than_branch_qm_ = Nil;
			  next_loop_6:
			    ab_less_than_branch_qm_ = 
				    ISVREF(ab_current_node_,(SI_Long)1L);
			    if ( !TRUEP(ab_less_than_branch_qm_))
				goto end_loop_4;
			    ab_node_stack_ = scope_cons(ab_current_node_,
				    ab_node_stack_);
			    ab_current_node_ = ab_less_than_branch_qm_;
			    goto next_loop_6;
			  end_loop_4:;
			}
			else if (ab_node_stack_) {
			    ab_next_node_ = ab_node_stack_;
			    ab_current_node_ = M_CAR(ab_node_stack_);
			    ab_node_stack_ = M_CDR(ab_node_stack_);
			}
			else
			    ab_current_node_ = Nil;
			if (ab_current_node_) {
			    ab_next_node_ = ISVREF(ab_current_node_,
				    (SI_Long)2L);
			    ab_current_alist_ = ISVREF(ab_current_node_,
				    (SI_Long)3L);
			    ab_entry_cons_ = M_CAR(ab_current_alist_);
			    ab_connection_ = M_CAR(ab_entry_cons_);
			    ab_connection_item_ = M_CDR(ab_entry_cons_);
			    ab_current_alist_ = M_CDR(ab_current_alist_);
			}
		    }
		    if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
			    ab_connection_ && EQ(ISVREF(ab_connection_,
			    (SI_Long)3L),subblock))
			goto end_2;
		    goto next_loop_5;
		  end_loop_5:
		  end_2:
		    if ( !TRUEP(ab_current_node_))
			goto end_loop_6;
		    connection = ab_connection_;
		    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
		    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(connection_frame_or_class,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if ((temp_1 ? 
			    TRUEP(ISVREF(ISVREF(connection_frame_or_class,
			    (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil)) ? 
			    TRUEP(serve_item_p(connection_frame_or_class)) 
			    : TRUEP(Nil))
			Items_to_traverse = 
				eval_cons_1(connection_frame_or_class,
				Items_to_traverse);
		    goto next_loop_4;
		  end_loop_6:;
		  POP_SPECIAL();
	      }
	      goto next_loop_3;
	    end_loop_3:;
	  }
	  else {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
	      if (temp_1) {
		  slot_description = Nil;
		  class_description = ISVREF(item,(SI_Long)1L);
		  ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
		next_loop_7:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_7;
		  slot_description = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ISVREF(slot_description,(SI_Long)8L)) {
		      vector_slot_index_qm = ISVREF(slot_description,
			      (SI_Long)7L);
		      if (vector_slot_index_qm)
			  slot_value = ISVREF(item,IFIX(vector_slot_index_qm));
		      else {
			  user_vector_slot_index_qm = 
				  ISVREF(slot_description,(SI_Long)8L);
			  if (user_vector_slot_index_qm)
			      slot_value = ISVREF(ISVREF(item,(SI_Long)0L),
				      IFIX(user_vector_slot_index_qm));
			  else {
			      slot_name = ISVREF(slot_description,(SI_Long)1L);
			      lookup_structure_qm = ISVREF(item,(SI_Long)0L);
			      if (lookup_structure_qm) {
				  max_i = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
				  max_i = max_i - (SI_Long)1L;
				  i = IFIX(ISVREF(ISVREF(item,(SI_Long)1L),
					  (SI_Long)15L));
				  ab_loop_bind_ = max_i;
				next_loop_8:
				  if (i >= ab_loop_bind_)
				      goto end_loop_8;
				  if (EQ(ISVREF(lookup_structure_qm,i),
					  slot_name)) {
				      slot_index_qm = FIX(i + (SI_Long)1L);
				      goto end_3;
				  }
				  i = i + (SI_Long)2L;
				  goto next_loop_8;
				end_loop_8:
				  slot_index_qm = Qnil;
				end_3:;
				  slot_value = slot_index_qm ? 
					  ISVREF(lookup_structure_qm,
					  IFIX(slot_index_qm)) : 
					  ISVREF(slot_description,(SI_Long)6L);
			      }
			      else
				  slot_value = ISVREF(slot_description,
					  (SI_Long)6L);
			  }
		      }
		      if (SIMPLE_VECTOR_P(slot_value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(slot_value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(slot_value,(SI_Long)1L);
			  gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && 
				  EQ(ISVREF(x2,(SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? x2 : Qnil;
		      }
		      else
			  gensymed_symbol_3 = Nil;
		      if (gensymed_symbol_3 && ISVREF(gensymed_symbol_3,
			      (SI_Long)16L)) {
			  gensymed_symbol_3 = 
				  SYMBOL_FUNCTION(Qadd_to_items_to_traverse);
			  gensymed_symbol_4 = slot_value;
			  inline_funcall_1(gensymed_symbol_3,
				  gensymed_symbol_4);
		      }
		  }
		  goto next_loop_7;
		end_loop_7:;
	      }
	  }
      }
      goto next_loop;
    end_loop:;
      result = VALUES_1(items_to_return);
    POP_SPECIAL();
    return result;
}

static Object string_constant_176;  /* "Cannot modify the element at index ~a in ~NA.  This item is not ~
				     *          a g2-list, g2-array, or sequence in an attribute of an item."
				     */

static Object string_constant_177;  /* "An attempt was made to refer to element ~a of ~NF, but it is ~
				     *          only ~a elements long."
				     */

static Object list_constant_5;     /* # */

static Object Qelement;            /* element */

/* FETCH-ELEMENT-FRAME-OR-PLACE-REFERENCE */
Object fetch_element_frame_or_place_reference(item_or_place_reference,
	    index_1,top_of_stack)
    Object item_or_place_reference, index_1, top_of_stack;
{
    Object place_reference_qm, x2, class_description_qm, sub_class_bit_vector;
    Object g2_array_p_qm, g2_list_p_qm, servable_item_element_qm;
    Object top_of_stack_1, message_1, length_1, stored_item_or_value_qm;
    Object gensymed_symbol_3, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, svref_arg_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(205,241);
    place_reference_qm = CONSP(item_or_place_reference) ? 
	    (EQ(M_CDR(item_or_place_reference),Qplace_reference) ? T : 
	    Nil) : Qnil;
    if ( !TRUEP(place_reference_qm)) {
	if (SIMPLE_VECTOR_P(item_or_place_reference) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_place_reference)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_place_reference,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_place_reference,(SI_Long)1L);
	    class_description_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    class_description_qm = Nil;
    }
    else
	class_description_qm = Nil;
    if ( !TRUEP(place_reference_qm) && class_description_qm) {
	sub_class_bit_vector = ISVREF(class_description_qm,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	    g2_array_p_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    g2_array_p_qm = Nil;
    }
    else
	g2_array_p_qm = Nil;
    if ( !TRUEP(place_reference_qm) && class_description_qm) {
	sub_class_bit_vector = ISVREF(class_description_qm,(SI_Long)19L);
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
	    g2_list_p_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    g2_list_p_qm = Nil;
    }
    else
	g2_list_p_qm = Nil;
    servable_item_element_qm = Nil;
    if ( !(g2_array_p_qm || g2_list_p_qm || place_reference_qm)) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_176,
		index_1,item_or_place_reference);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    if (g2_array_p_qm) {
	length_1 = ISVREF(item_or_place_reference,(SI_Long)20L);
	temp =  !(FIXNUMP(index_1) && IFIX(index_1) >= (SI_Long)0L && 
		FIXNUM_LT(index_1,length_1));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack_1 = top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_177,
		index_1,item_or_place_reference,
		ISVREF(item_or_place_reference,(SI_Long)20L));
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    if ( !TRUEP(place_reference_qm) && 
	    g2_list_or_array_element_type_may_contain_item_p(ISVREF(item_or_place_reference,
	    (SI_Long)21L))) {
	stored_item_or_value_qm = g2_array_p_qm ? 
		g2_array_aref(item_or_place_reference,index_1) : 
		nth_g2_list_item_or_evaluation_value(index_1,
		item_or_place_reference,Nil);
	if (stored_item_or_value_qm) {
	    gensymed_symbol_3 = stored_item_or_value_qm;
	    temp = FIXNUMP(gensymed_symbol_3);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_3) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol_3) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol_3 ? SYMBOLP(gensymed_symbol_3) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_3) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol_3)) {
		gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
		temp = EQ(gensymed_symbol_3,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol_3,Qiteration_state);
		if (temp);
		else if (SYMBOLP(gensymed_symbol_3)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = gensymed_symbol_3;
		    key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else if (stored_item_or_value_qm && 
		serve_item_p(stored_item_or_value_qm))
	    servable_item_element_qm = stored_item_or_value_qm;
	else
	    raw_stack_error_named_error(top_of_stack,
		    role_returned_no_values_error_1(list_constant_5,
		    item_or_place_reference,index_1));
    }
    if (servable_item_element_qm)
	temp_2 = servable_item_element_qm;
    else if (place_reference_qm) {
	svref_arg_1 = M_CAR(item_or_place_reference);
	svref_new_value = slot_value_list_3(Qelement,index_1,
		ISVREF(M_CAR(item_or_place_reference),(SI_Long)0L));
	SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
	temp_2 = item_or_place_reference;
    }
    else
	temp_2 = 
		make_evaluation_place_reference_to_place(slot_value_list_3(Qelement,
		index_1,Qcurrent_computation_frame),item_or_place_reference);
    return VALUES_1(temp_2);
}

/* EMIT-ELEMENT-FRAME-OR-PLACE-REFERENCE-BYTE-CODES */
Object emit_element_frame_or_place_reference_byte_codes(byte_code_stream)
    Object byte_code_stream;
{
    x_note_fn_call(205,242);
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)120L));
}

static Object string_constant_178;  /* " ~(~a~)" */

/* PRINT-TYPE-CHECK-CLASS-INLINE */
Object print_type_check_class_inline(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    Object class_1;

    x_note_fn_call(205,243);
    class_1 = nth(FIX(UBYTE_8_ISAREF_1(instructions,
	    IFIX(FIXNUM_ADD1(pc)))),Classes_type_checked_inline);
    return tformat(2,string_constant_178,class_1);
}

static Object Qunknown_class;      /* unknown-class */

/* PPRINT-TYPE-CHECK-CLASS-INLINE-INSTRUCTION */
Object pprint_type_check_class_inline_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    Object instruction_vector, stack_program_counter, class_name, class_1;
    Object ab_loop_list_, ab_loop_iter_flag_;
    SI_Long inline_class_index, count_1;

    x_note_fn_call(205,244);
    instruction_vector = ISVREF(byte_code_body,(SI_Long)2L);
    stack_program_counter = FIXNUM_ADD1(pc);
    inline_class_index = UBYTE_8_ISAREF_1(instruction_vector,
	    IFIX(stack_program_counter));
    class_name = Qunknown_class;
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)11L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)1L),stack,top_of_stack);
    class_1 = Nil;
    ab_loop_list_ = Classes_type_checked_inline;
    count_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	count_1 = count_1 + (SI_Long)1L;
    if (count_1 == inline_class_index)
	class_name = class_1;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return tformat(2,string_constant_28,class_name);
}

static Object string_constant_179;  /* "An internal error has just occured in the type-check-class-inline ~
				     *                  instruction.  The index ~a was out of range."
				     */

/* INLINE-TYPE-CHECK-CLASS */
Object inline_type_check_class(thing,class_number,top_of_stack)
    Object thing, class_number, top_of_stack;
{
    Object x2, class_description_qm, temp, top_of_stack_1, message_1;
    Object not_error_p, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(205,245);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	class_description_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	class_description_qm = Nil;
    if (class_description_qm) {
	temp = class_number;
	if ( !(FIXNUM_LE(FIX((SI_Long)0L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)255L)))) {
	    top_of_stack_1 = top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_179,class_number);
	    not_error_p = raw_stack_error_named_error(top_of_stack_1,
		    message_1);
	}
	else
	    switch (INTEGER_TO_UNSIGNED_CHAR(temp)) {
	      case 0:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_frame_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 1:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Temporary_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 2:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Invisible_entity_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 3:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Message_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 4:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Format_frame_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 5:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Menu_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 6:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Language_translation_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 7:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(User_menu_choice_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 8:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_formula_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 9:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Logical_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 10:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 11:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 12:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Symbolic_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 13:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 14:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Logical_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 15:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantitative_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 16:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 17:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 18:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Symbolic_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 19:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 20:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Forward_chaining_link_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 21:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(True_value_update_recipient_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 22:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Backward_chaining_link_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 23:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Function_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 24:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Units_of_measure_declaration_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 25:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Tabular_function_of_1_arg_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 26:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_cell_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 27:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_cell_array_cell_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 28:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_query_cell_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 29:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_designation_cell_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 30:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_expression_cell_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 31:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Remote_procedure_declaration_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 32:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Dial_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 33:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 34:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Digital_clock_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 35:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Graph_grid_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 36:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Plot_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 37:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Model_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 38:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Foreign_function_declaration_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 39:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(External_simulation_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 40:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Authorized_user_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 41:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Statement_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 42:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Edit_box_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 43:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_invocation_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 44:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Logbook_page_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 45:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Page_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 46:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Menu_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 47:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Category_instance_menu_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 48:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Inspect_command_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 49:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Icon_cell_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 50:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Explanation_table_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 51:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 52:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 53:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 54:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Category_menu_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 55:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Scrap_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 56:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_region_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 57:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kfep_conversion_choice_menu_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 58:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Subordinate_text_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 59:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Dialog_button_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 60:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 61:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_name_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 62:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 63:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Dependent_frame_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 64:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Non_kb_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 65:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_post_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 66:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Message_board_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 67:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Action_button_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 68:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Chart_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 69:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Default_junction_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 70:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ruling_for_dial_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 71:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Pointer_for_dial_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 72:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ruling_for_meter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 73:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Marker_for_meter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 74:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Readout_table_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 75:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Graph_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 76:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ok_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 77:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_simulation_formula_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 78:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 79:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 80:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 81:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 82:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Relation_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 83:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Simulation_subtable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 84:
		not_error_p = ISVREF(class_description_qm,(SI_Long)16L) ? 
			T : Nil;
		break;
	      case 85:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 86:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 87:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 88:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 89:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 90:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 91:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantitative_variable_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 92:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Slider_minimum_value_label_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 93:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 94:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Question_mark_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 95:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Slider_readout_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 96:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Button_label_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 97:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Slider_needle_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 98:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Type_in_text_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 99:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Button_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 100:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_action_button_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 101:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Type_in_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 102:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Arrow_button_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 103:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 104:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 105:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 106:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 107:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Icon_editor_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 108:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 109:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Icon_editor_table_info_frame_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 110:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Bounding_box_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 111:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Tabular_function_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 112:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 113:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Item_list_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 114:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 115:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 116:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 117:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Symbol_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 118:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_list_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 119:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Truth_value_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 120:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 121:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Item_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 122:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 123:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 124:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 125:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Symbol_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 126:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 127:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Truth_value_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 128:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_list_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      case 129:
		sub_class_bit_vector = ISVREF(class_description_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_array_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		not_error_p = temp_1 ? T : Nil;
		break;
	      default:
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_179,class_number);
		not_error_p = raw_stack_error_named_error(top_of_stack_1,
			message_1);
		break;
	    }
    }
    else
	not_error_p = Nil;
    if ( !TRUEP(not_error_p))
	raw_stack_error_named_error(top_of_stack,
		signal_stack_class_type_check_error_message(thing,
		class_number));
    return VALUES_1(Nil);
}

/* EMIT-TYPE-CHECK-CLASS-INLINE-BYTE-CODES */
Object emit_type_check_class_inline_byte_codes(byte_code_stream,class_name)
    Object byte_code_stream, class_name;
{
    x_note_fn_call(205,246);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)124L));
    return write_byte_code_to_stream(byte_code_stream,position(2,
	    class_name,Classes_type_checked_inline));
}

static Object string_constant_180;  /* "An error occured while concluding a formula result.  ~a" */

/* SIGNAL-ERROR-CONCLUDING-FORMULA-RESULT */
Object signal_error_concluding_formula_result(problem_description)
    Object problem_description;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(205,247);
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
		  tformat(2,string_constant_180,problem_description);
		  reclaim_text_string(problem_description);
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

/* COMPLETE-FORMULA-FUNCTION */
Object complete_formula_function(computed_value_qm,top_of_stack)
    Object computed_value_qm, top_of_stack;
{
    Object variable, problem_description_qm;
    Object variable_had_interests_before_this_attempt_qm, circular_path_qm;

    x_note_fn_call(205,248);
    variable = ISVREF(Current_computation_instance,(SI_Long)8L);
    if (computed_value_qm && Stack_expiration) {
	clean_up_wake_ups_state_if_any();
	problem_description_qm = put_current_evaluation_value(variable,
		computed_value_qm,Stack_expiration,Nil,Nil);
	if (problem_description_qm)
	    return signal_error_concluding_formula_result(problem_description_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	variable_had_interests_before_this_attempt_qm = 
		ISVREF(Current_computation_instance,(SI_Long)11L);
	if ( !(FIXNUMP(computed_value_qm) || SYMBOLP(computed_value_qm) || 
		SIMPLE_VECTOR_P(computed_value_qm)))
	    reclaim_if_evaluation_value_1(computed_value_qm);
	circular_path_qm = variable_had_interests_before_this_attempt_qm ? 
		circular_variable_interests_1(variable,variable) : Qnil;
	if (circular_path_qm)
	    write_circular_path_warning(variable,circular_path_qm);
	else
	    set_wake_ups_function(top_of_stack);
	clean_up_wake_ups_state_if_any();
	return VALUES_1(Nil);
    }
}

static Object array_constant_88;   /* # */

static Object string_constant_181;  /* " (~a)" */

/* PRINT-BEGIN-ACTIVITY */
Object print_begin_activity(pc,instructions,constants,environment)
    Object pc, instructions, constants, environment;
{
    SI_Long arg;
    char suppress_profile_qm;

    x_note_fn_call(205,249);
    arg = UBYTE_8_ISAREF_1(instructions,IFIX(FIXNUM_ADD1(pc)));
    suppress_profile_qm = arg > (SI_Long)127L;
    twrite_character(FIX((SI_Long)32L));
    write_activity_given_index(Nil,Nil,FIX(arg & (SI_Long)127L));
    if (suppress_profile_qm)
	twrite_beginning_of_wide_string(array_constant_88,FIX((SI_Long)18L));
    return tformat(2,string_constant_181,FIX(arg));
}

static Object string_constant_182;  /* "About to execute the activity: " */

static Object string_constant_183;  /* "~%Within: " */

/* WRITE-MAJOR-TRACE-OF-ACTIVITY */
Object write_major_trace_of_activity(local_stack,top_of_stack)
    Object local_stack, top_of_stack;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(205,250);
    if (IFIX(Tracing_message_level) == (SI_Long)2L || 
	    IFIX(Breakpoint_level) == (SI_Long)2L) {
	if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		!TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		(SI_Long)22L)) {
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
		      Forgive_long_procedure_instruction_qm = T;
		      tformat(1,string_constant_182);
		      write_activity_given_index(Current_computation_frame,
			      Current_computation_component_particulars,
			      Current_computation_activity);
		      tformat(1,string_constant_183);
		      write_stack_evaluator_backtrace(Current_computation_frame,
			      Current_computation_component_particulars,
			      Current_computation_instance,local_stack,
			      top_of_stack,Cached_stack_frame_base);
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
    else
	return VALUES_1(Nil);
}

Object Insert_begin_activity_instruction_into_byte_code_stream_qm = UNBOUND;

static Object string_constant_184;  /* "begin activity byte code emitter" */

static Object string_constant_185;  /* "The given activity number, ~a, was out of range." */

/* EMIT-BEGIN-ACTIVITY-BYTE-CODES */
Object emit_begin_activity_byte_codes(byte_code_stream,activity,
	    suppress_profile_qm)
    Object byte_code_stream, activity, suppress_profile_qm;
{
    SI_Long activity_new_value;

    x_note_fn_call(205,251);
    if (Insert_begin_activity_instruction_into_byte_code_stream_qm || 
	    IFIX(activity) == (SI_Long)64L) {
	write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)127L));
	if (FIXNUM_MINUSP(activity) || FIXNUM_GT(activity,
		length(Registered_activities_array)) || IFIX(activity) > 
		(SI_Long)127L) {
	    compiler_bug(3,string_constant_184,string_constant_185,activity);
	    activity = FIX((SI_Long)0L);
	}
	if (suppress_profile_qm) {
	    activity_new_value = IFIX(activity) + (SI_Long)128L;
	    activity = FIX(activity_new_value);
	}
	return write_byte_code_to_stream(byte_code_stream,activity);
    }
    else {
	add_activity_translation_to_code_stream(byte_code_stream,
		ISVREF(byte_code_stream,(SI_Long)1L),activity);
	return VALUES_1(Nil);
    }
}

static Object string_constant_186;  /* "The designated item does not exist." */

static Object string_constant_187;  /* "~NF cannot be referenced because it is disabled or inactive." */

/* CACHED-ITEM-ERROR-MESSAGE */
Object cached_item_error_message(item_or_item_name_qm)
    Object item_or_item_name_qm;
{
    Object temp;

    x_note_fn_call(205,252);
    if ( !TRUEP(item_or_item_name_qm))
	temp = string_constant_186;
    else if (SYMBOLP(item_or_item_name_qm))
	temp = string_constant_72;
    else if (ISVREF(ISVREF(item_or_item_name_qm,(SI_Long)1L),(SI_Long)16L) 
	    &&  !((SI_Long)0L != (IFIX(ISVREF(item_or_item_name_qm,
	    (SI_Long)5L)) & (SI_Long)1L)) &&  
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != (SI_Long)0L))
	temp = string_constant_187;
    else
	temp = string_constant_186;
    return tformat_stack_error_text_string(2,temp,item_or_item_name_qm);
}

static Object Qcached_name;        /* cached-name */

/* EMIT-PUSH-CACHED-ITEM-BYTE-CODES */
Object emit_push_cached_item_byte_codes(byte_code_stream,name_constant,
	    no_item_ok_qm)
    Object byte_code_stream, name_constant, no_item_ok_qm;
{
    Object name_constant_cons, constant_index;

    x_note_fn_call(205,253);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)128L));
    name_constant_cons = slot_value_cons_1(name_constant,
	    Cached_name_cons_marker);
    constant_index = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    name_constant_cons);
    reclaim_slot_value_cons_1(name_constant_cons);
    emit_long_code_constant_to_stream(byte_code_stream,constant_index);
    write_byte_code_to_stream(byte_code_stream,no_item_ok_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
    return record_free_reference(Qcached_name,phrase_cons(name_constant,
	    constant_index));
}

static Object string_constant_188;  /* "An attribute of ~NF contained nothing, causing this reference to fail." */

/* CACHED-ATTRIBUTE-VALUE-NO-VALUE-ERROR-1 */
Object cached_attribute_value_no_value_error_1(compiled_item,
	    compiled_item_component_particulars_qm,constant_vector_index,
	    constant_vector_attribute_cache,item)
    Object compiled_item, compiled_item_component_particulars_qm;
    Object constant_vector_index, constant_vector_attribute_cache, item;
{
    Object attribute_name_qm, class_specific_attribute_class_qm;
    Object slot_description_qm, cached_attribute_free_reference_qm;

    x_note_fn_call(205,254);
    attribute_name_qm = Nil;
    class_specific_attribute_class_qm = Nil;
    slot_description_qm = Nil;
    if (CONSP(constant_vector_attribute_cache)) {
	attribute_name_qm = CAR(constant_vector_attribute_cache);
	class_specific_attribute_class_qm = 
		FOURTH(constant_vector_attribute_cache);
    }
    else if (INTEGERP(constant_vector_attribute_cache)) {
	cached_attribute_free_reference_qm = 
		find_cached_attribute_free_reference(constant_vector_index,
		compiled_item,compiled_item_component_particulars_qm);
	if (cached_attribute_free_reference_qm)
	    class_specific_attribute_class_qm = 
		    FIFTH(cached_attribute_free_reference_qm);
	slot_description_qm = 
		get_slot_description_with_user_vector_slot_index(constant_vector_attribute_cache,
		item);
	if (slot_description_qm)
	    attribute_name_qm = ISVREF(slot_description_qm,(SI_Long)2L);
    }
    else;
    if (attribute_name_qm)
	return attribute_returned_no_values_error_1(attribute_name_qm,item,
		class_specific_attribute_class_qm);
    else
	return tformat_stack_error_text_string(2,string_constant_188,item);
}

/* FIND-CACHED-ATTRIBUTE-FREE-REFERENCE */
Object find_cached_attribute_free_reference(constant_vector_index,
	    compiled_item,compiled_item_component_particulars_qm)
    Object constant_vector_index, compiled_item;
    Object compiled_item_component_particulars_qm;
{
    Object byte_code_body_qm, free_references_qm;
    Object cached_attribute_free_reference_qm, vector_length, free_ref;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(205,255);
    byte_code_body_qm = get_byte_code_body_if_any(compiled_item,
	    compiled_item_component_particulars_qm);
    free_references_qm = byte_code_body_qm ? ISVREF(byte_code_body_qm,
	    (SI_Long)7L) : Qnil;
    cached_attribute_free_reference_qm = Nil;
    if (free_references_qm) {
	vector_length = length(free_references_qm);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(vector_length);
	free_ref = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	free_ref = ISVREF(free_references_qm,index_1);
	if (cached_attribute_free_reference_qm)
	    goto end_loop;
	if (CONSP(free_ref) && EQ(length(free_ref),FIX((SI_Long)6L)) && 
		EQ(SIXTH(free_ref),Cached_attribute_cons_marker) && 
		EQ(FOURTH(free_ref),constant_vector_index))
	    cached_attribute_free_reference_qm = free_ref;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(cached_attribute_free_reference_qm);
}

static Object Qcached_attribute;   /* cached-attribute */

/* EMIT-CACHED-ATTRIBUTE-VALUE-BYTE-CODES */
Object emit_cached_attribute_value_byte_codes(byte_code_stream,
	    attribute_name,item_name_qm,class_name_qm,
	    class_specific_attribute_class_qm)
    Object byte_code_stream, attribute_name, item_name_qm, class_name_qm;
    Object class_specific_attribute_class_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, attribute_constant_list;
    Object constant_index;

    x_note_fn_call(205,256);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)132L));
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = attribute_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = item_name_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = class_name_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = class_specific_attribute_class_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Cached_attribute_cons_marker;
    attribute_constant_list = gensymed_symbol;
    constant_index = 
	    register_internal_constant_in_byte_code_stream(byte_code_stream,
	    attribute_constant_list);
    reclaim_slot_value_list_1(attribute_constant_list);
    emit_long_code_constant_to_stream(byte_code_stream,constant_index);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = attribute_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = item_name_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = class_name_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = constant_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = class_specific_attribute_class_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Cached_attribute_cons_marker;
    record_free_reference(Qcached_attribute,gensymed_symbol);
    return compiler_warning_if_superseded_attribute(attribute_name);
}

/* PPRINT-NTH-ARRAY-ELEMENT-INSTRUCTION */
Object pprint_nth_array_element_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,257);
    twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)6L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_65,FIX((SI_Long)1L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)2L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_66,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object string_constant_189;  /* "The g2-array ~NF contains no element at index ~a." */

/* NO-ELEMENT-FOR-ARRAY-INDEX-ERROR-MESSAGE */
Object no_element_for_array_index_error_message(item,index_value)
    Object item, index_value;
{
    x_note_fn_call(205,258);
    return tformat_stack_error_text_string(3,string_constant_189,item,
	    index_value);
}

static Object array_constant_89;   /* # */

static Object array_constant_90;   /* # */

/* PPRINT-CHANGE-NTH-ARRAY-ELEMENT-INSTRUCTION */
Object pprint_change_nth_array_element_instruction(pc,byte_code_body,
	    constant_vector,stack,top_of_stack)
    Object pc, byte_code_body, constant_vector, stack, top_of_stack;
{
    x_note_fn_call(205,259);
    twrite_beginning_of_wide_string(array_constant_89,FIX((SI_Long)7L));
    write_stack_argument(FIX((SI_Long)1L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_65,FIX((SI_Long)1L));
    write_stack_argument(FIX((SI_Long)3L),FIX((SI_Long)3L),stack,top_of_stack);
    twrite_beginning_of_wide_string(array_constant_90,FIX((SI_Long)4L));
    write_stack_argument(FIX((SI_Long)2L),FIX((SI_Long)3L),stack,top_of_stack);
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

static Object string_constant_190;  /* "move-from-local-var emitter" */

/* EMIT-MOVE-FROM-SURROUNDING-LOCAL-VAR-BYTE-CODES */
Object emit_move_from_surrounding_local_var_byte_codes(byte_code_stream,
	    var_spot)
    Object byte_code_stream, var_spot;
{
    x_note_fn_call(205,260);
    if ( !(valid_var_spot_p(var_spot) &&  
	    !TRUEP(memq_function(CAR(var_spot),list_constant_6)))) {
	compiler_bug(3,string_constant_190,string_constant_69,var_spot);
	var_spot = list_constant_2;
    }
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)138L));
    return emit_long_code_constant_to_stream(byte_code_stream,
	    SECOND(var_spot));
}

/* EMIT-ALLOW-NO-ITEM-FOR-EVALUATOR-BYTE-CODES */
Object emit_allow_no_item_for_evaluator_byte_codes(byte_code_stream,nargs,tag)
    Object byte_code_stream, nargs, tag;
{
    x_note_fn_call(205,261);
    register_byte_code_tag_resolution_point(byte_code_stream,tag);
    write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)140L));
    write_byte_code_to_stream(byte_code_stream,nargs);
    return write_byte_code_to_stream(byte_code_stream,FIX((SI_Long)0L));
}

/* BC-ALLOW-NO-ITEM-FOR-EVALUATOR-RESOLVER */
Object bc_allow_no_item_for_evaluator_resolver(byte_code_stream,
	    byte_vector,address,tag)
    Object byte_code_stream, byte_vector, address, tag;
{
    Object aref_new_value;
    SI_Long aref_arg_2;

    x_note_fn_call(205,262);
    aref_arg_2 = IFIX(address) + (SI_Long)2L;
    aref_new_value = 
	    FIXNUM_SUB1(FIXNUM_MINUS(instruction_address_for_tag(tag,Nil),
	    address));
    UBYTE_8_ISASET_1(byte_vector,aref_arg_2,IFIX(aref_new_value));
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

void stack_inst_INIT()
{
    Object bc_branch_long_resolver_1, bc_branch_long_if_not_true_resolver_1;
    Object bc_branch_long_if_known_resolver_1, bc_case_dispatch_resolver_1;
    Object bc_jump_resolver_1, bc_open_role_iteration_no_domain_resolver_1;
    Object bc_open_role_iteration_resolver_1;
    Object bc_serve_next_iteration_value_resolver_1;
    Object bc_restore_from_action_cache_or_branch_resolver_1, gensymed_symbol;
    Object bc_allow_no_item_for_evaluator_resolver_1;
    Object Qstack_coerce_integer_to_long_body, Qcoerce_integer_to_long;
    Object AB_package, Qstack_allow_no_item_for_evaluator_body;
    Object Qallow_no_item_for_evaluator, Qbyte_code_resolver;
    Object Qpprint_move_from_surrounding_local_var_instruction;
    Object Qstack_move_from_surrounding_local_var_body;
    Object Qprint_op_and_surrounding_local_var;
    Object Qmove_from_surrounding_local_var;
    Object Qpprint_signal_error_new_instruction, Qstack_signal_error_new_body;
    Object Qsignal_error_new, Qpprint_nth_array_element_instruction;
    Object Qstack_change_nth_float_array_element_body;
    Object Qchange_nth_float_array_element;
    Object Qstack_change_nth_integer_array_element_body;
    Object Qchange_nth_integer_array_element, list_constant_7;
    Object Qstack_nth_float_array_element_body, Qnth_float_array_element;
    Object Qstack_nth_integer_array_element_body, Qnth_integer_array_element;
    Object Qpprint_branch_relative_if_not_true_instruction;
    Object Qstack_boolean_branch_relative_if_not_true_body;
    Object Qprint_op_and_relative_code_constant_address;
    Object Qboolean_branch_relative_if_not_true;
    Object Qpprint_branch_long_if_not_true_instruction;
    Object Qstack_boolean_branch_long_if_not_true_body;
    Object Qprint_op_and_long_code_constant, Qboolean_branch_long_if_not_true;
    Object Qpprint_branch_if_not_true_instruction;
    Object Qstack_boolean_branch_if_not_true_body, Qprint_op_and_code_constant;
    Object Qboolean_branch_if_not_true;
    Object Qpprint_cached_attribute_value_instruction;
    Object Qstack_cached_attribute_value_body, Qprint_cached_attribute;
    Object Qcached_attribute_value, Qpprint_push_cached_item_instruction;
    Object Qstack_push_cached_item_body, Qprint_cached_item, Qpush_cached_item;
    Object Qstack_begin_activity_body, Qprint_begin_activity, Qbegin_activity;
    Object Qpprint_complete_cell_expression_instruction;
    Object Qstack_complete_cell_expression_body, Qcomplete_cell_expression;
    Object Qpprint_complete_generic_formula_instruction;
    Object Qstack_complete_generic_formula_body, Qcomplete_generic_formula;
    Object Qpprint_type_check_class_inline_instruction;
    Object Qstack_type_check_class_inline_body, Qprint_type_check_class_inline;
    Object Qtype_check_class_inline, Qpprint_nth_element_instruction;
    Object Qstack_nth_element_body;
    Object Qstack_element_frame_or_place_reference_body;
    Object Qstack_pop_into_default_allow_data_seeking_body;
    Object Qpop_into_default_allow_data_seeking;
    Object Qstack_push_from_default_allow_data_seeking_body;
    Object Qpush_from_default_allow_data_seeking;
    Object Qpprint_nupec_synchronize_instruction;
    Object Qstack_nupec_synchronize_body, Qnupec_synchronize;
    Object Qg2_complete_reset_kb;
    Object Qg2_get_top_level_transient_items_and_connections;
    Object Qg2_get_top_level_transient_workspaces;
    Object Qg2_get_blocks_needing_status_refreshed;
    Object Qpprint_reset_kb_instruction, Qstack_reset_kb_body, Qreset_kb;
    Object Qpprint_pause_kb_instruction, Qstack_pause_kb_body, Qpause_kb;
    Object Qstack_complete_simulation_variable_evaluation_body;
    Object Qcomplete_simulation_variable_evaluation;
    Object Qrestore_from_action_cache_or_branch;
    Object Qstack_restore_from_action_cache_or_branch_body;
    Object Qprint_action_cache_indices_and_address;
    Object Qstack_add_to_action_cache_body, Qprint_action_cache_and_indices;
    Object Qadd_to_action_cache, Qstack_begin_rule_actions_body;
    Object Qbegin_rule_actions, Qstack_push_from_block_of_local_vars_body;
    Object Qprint_block_copy, Qpush_from_block_of_local_vars;
    Object Qstack_pop_into_block_of_local_vars_body;
    Object Qpop_into_block_of_local_vars, Qstack_complete_rule_instance_body;
    Object Qcomplete_rule_instance, Qunknown_datum;
    Object Qpprint_coerce_matching_element_type_instruction;
    Object Qstack_coerce_matching_element_type_body;
    Object Qcoerce_matching_element_type;
    Object Qstack_coerce_matching_element_type_or_unknown_body;
    Object Qcoerce_matching_element_type_or_unknown;
    Object Qstack_pop_current_environment_body, Qpop_current_environment;
    Object Qstack_push_current_environment_body, Qpush_current_environment;
    Object Qstack_check_stack_body, Qcheck_stack;
    Object Qpprint_push_from_local_var_instruction;
    Object Qstack_push_value_or_none_from_local_var_body;
    Object Qprint_op_and_local_var_and_typecode;
    Object Qpush_value_or_none_from_local_var;
    Object Qpprint_invoke_with_wait_instruction, Qstack_invoke_with_wait_body;
    Object Qinvoke_with_wait, Qpprint_invoke_instruction, Qstack_invoke_body;
    Object Qinvoke, Qpprint_show_instruction, Qstack_show_body, Qshow;
    Object Qpprint_halt_instruction, Qstack_halt_body, Qhalt, list_constant_37;
    Object Qbottom, Qright, Qtop, Qleft, list_constant_36, Qoutput;
    Object list_constant_35, Qorthogonal, Qdiagonal;
    Object Qpprint_create_connection_instruction;
    Object Qstack_create_connection_body, Qcreate_connection;
    Object Qpprint_system_procedure_instruction, Qstack_system_call_body;
    Object Qprint_call_stack_instruction, Qsystem_call, Qstack_none_test_body;
    Object Qnone_test, Qpprint_return_from_function_instruction;
    Object Qstack_return_from_function_body, Qreturn_from_function;
    Object string_constant_192, string_constant_191;
    Object Qpprint_call_function_instruction, Qstack_call_function_body;
    Object Qprint_call_function_stack_instruction, Qcall_function;
    Object Qstack_call_procedure_body, Qcall_procedure;
    Object Qpprint_push_from_surrounding_local_var_instruction;
    Object Qstack_push_value_or_none_from_surrounding_local_var_body;
    Object Qprint_op_and_surrounding_local_var_and_typecode;
    Object Qpush_value_or_none_from_surrounding_local_var;
    Object Qstack_push_nones_body, Qpush_nones, Qpprint_type_check_instruction;
    Object Qstack_type_check_body, Qprint_op_and_type_long, Qtype_check;
    Object Qstack_push_wake_ups_count_body, Qpush_wake_ups_count;
    Object Qstack_pop_into_final_evaluation_attempt_body;
    Object Qpop_into_final_evaluation_attempt;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qpprint_wait_for_interval_instruction;
    Object Qstack_wait_for_interval_body, Qwait_for_interval;
    Object Qstack_close_wake_up_collection_body, Qclose_wake_up_collection;
    Object Qstack_clear_wake_ups_body, Qclear_wake_ups;
    Object Qstack_set_wake_ups_body, Qset_wake_ups;
    Object Qstack_open_wake_up_collection_body, Qopen_wake_up_collection;
    Object Qstack_pop_into_allow_data_seeking_body;
    Object Qpop_into_allow_data_seeking;
    Object Qstack_push_from_allow_data_seeking_body;
    Object Qpush_from_allow_data_seeking, Qpprint_or_instruction;
    Object Qstack_fuzzy_or_body, Qfuzzy_or, Qpprint_and_instruction;
    Object Qstack_fuzzy_and_body, Qfuzzy_and;
    Object Qstack_pop_copy_down_the_stack_body, Qpop_copy_down_the_stack;
    Object Qstack_push_copy_of_top_of_stack_body, Qpush_copy_of_top_of_stack;
    Object Qpprint_fetch_value_of, Qstack_coerce_to_datum_body;
    Object Qcoerce_to_datum, Qstack_coerce_to_datum_or_unknown_body;
    Object Qcoerce_to_datum_or_unknown, Qstack_variable_value_or_unknown_body;
    Object Qvariable_value_or_unknown, Qstack_pause_if_called_code_bodies_body;
    Object Qpause_if_called_code_bodies, Qstack_pause_body, Qpause;
    Object Qpprint_type_check_item_instruction, Qstack_type_check_item_body;
    Object Qtype_check_item, Qstack_wait_for_called_code_bodies_body;
    Object Qwait_for_called_code_bodies, Qstack_call_scheduled_code_body_body;
    Object Qprint_stack_call_code_body, Qcall_scheduled_code_body;
    Object Qstack_call_code_body_body, Qcall_code_body;
    Object Qstack_close_code_body_body, Qclose_code_body;
    Object Qstack_close_iteration_body, Qclose_iteration;
    Object Qserve_next_iteration_value;
    Object Qpprint_serve_next_iteration_value_instruction;
    Object Qstack_serve_next_iteration_value_body;
    Object Qprint_serve_next_iteration_value, Qopen_role_iteration;
    Object Qpprint_open_role_iteration_instruction;
    Object Qstack_open_role_iteration_body, Qprint_open_role_iteration;
    Object Qopen_role_iteration_no_domain;
    Object Qpprint_open_role_iteration_no_domain_instruction;
    Object Qstack_open_role_iteration_no_domain_body;
    Object Qprint_open_role_no_domain_iteration;
    Object Qpprint_allow_other_processing_instruction;
    Object Qstack_allow_other_processing_body, Qallow_other_processing;
    Object Qstack_abort_called_code_bodies_body, Qabort_called_code_bodies;
    Object Qjump, Qstack_jump_body, Qprint_stack_jump;
    Object Qstack_push_returned_values_long_body, Qpush_returned_values_long;
    Object Qstack_push_returned_values_body, Qpush_returned_values;
    Object Qpprint_call_rpc_instruction, Qstack_call_rpc_body, Qcall_rpc;
    Object Qpprint_call_instruction, Qstack_dependent_call_body;
    Object Qdependent_call, Qstack_call_body, Qpprint_signal_error_instruction;
    Object Qstack_signal_error_body, Qsignal_error;
    Object Qpprint_return_values_instruction, Qstack_return_values_body;
    Object Qreturn_values, Qpprint_attribute_value_instruction;
    Object Qstack_attribute_value_body, Qprint_op_and_constant_long;
    Object Qpprint_attribute_frame_or_place_reference_instruction;
    Object Qstack_attribute_frame_or_place_reference_body;
    Object Qpprint_funcalled_instruction_n, Qstack_funcall_instruction_n_body;
    Object Qprint_funcalled_instruction_n, Qfuncall_instruction_n;
    Object Qpprint_funcalled_instruction, Qstack_funcall_instruction_body;
    Object Qprint_funcalled_instruction, Qfuncall_instruction;
    Object Qpprint_funcall_evaluator, Qstack_funcall_evaluator_body;
    Object Qprint_funcall_evaluator, Qfuncall_evaluator;
    Object Qpprint_not_instruction, Qstack_not_body;
    Object Qpprint_coerce_quantity_to_float_instruction;
    Object Qstack_coerce_quantity_to_float_body, Qcoerce_quantity_to_float;
    Object Qpprint_coerce_integer_to_float_instruction;
    Object Qstack_coerce_integer_to_float_body, Qcoerce_integer_to_float;
    Object Qpprint_parameter_value_instruction, Qstack_parameter_value_body;
    Object Qparameter_value, Qpprint_evaluate_role_with_no_domain_instruction;
    Object Qstack_evaluate_role_with_no_domain_body;
    Object Qprint_op_and_role_no_domain_long, Qevaluate_role_with_no_domain;
    Object Qpprint_evaluate_role_instruction, Qstack_evaluate_role_body;
    Object Qprint_op_role_long_and_arg_count;
    Object Qpprint_name_reference_instruction, Qstack_name_reference_body;
    Object Qprint_op_constant_long_and_code_constant, Qname_reference;
    Object Qstack_push_from_local_var_body, Qpush_from_local_var;
    Object Qstack_push_from_surrounding_local_var_body;
    Object Qpush_from_surrounding_local_var;
    Object Qpprint_pop_into_local_var_instruction;
    Object Qstack_pop_into_local_var_body, Qpop_into_local_var;
    Object list_constant_34;
    Object Qpprint_pop_into_surrounding_local_var_instruction;
    Object Qstack_pop_into_surrounding_local_var_body;
    Object Qpop_into_surrounding_local_var;
    Object Qpprint_type_check_item_or_datum_instruction;
    Object Qstack_type_check_item_or_datum_body;
    Object Qpprint_type_check_class_long_instruction;
    Object Qstack_type_check_class_long_body, Qtype_check_class_long;
    Object Qpprint_type_check_class_instruction, Qstack_type_check_class_body;
    Object Qprint_op_and_constant, Qtype_check_class, list_constant_33;
    Object Qclasses_type_checked_inline, list_constant_32, Qg2_expression_cell;
    Object Qg2_designation_cell, Qg2_query_cell, Qg2_cell_array_cell;
    Object Qg2_cell_array, Qtabular_function_of_1_arg;
    Object Qunits_of_measure_declaration, Qfunction_definition;
    Object Qbackward_chaining_link, Qtrue_value_update_recipient;
    Object Qforward_chaining_link, Qtext_parameter, Qsymbolic_parameter;
    Object Qfloat_parameter, Qinteger_parameter, Qquantitative_parameter;
    Object Qlogical_parameter, Qtext_variable, Qsymbolic_variable;
    Object Qinteger_variable, Qfloat_variable, Qlogical_variable;
    Object Qgeneric_formula, Quser_menu_choice, Qlanguage_translation, Qmenu;
    Object Qformat_frame, Qmessage_definition, Qinvisible_entity;
    Object Qtemporary_workspace, Qkb_frame, list_constant_31;
    Object Qworkspace_name_box, Qconnection_definition, Qdialog_button;
    Object Qsubordinate_text_box, Qkfep_conversion_choice_menu, Qtext_region;
    Object Qscrap, Qcategory_menu, Qname_box, Qg2_login, Qtext_box;
    Object Qexplanation_table, Qicon_cell, Qinspect_command;
    Object Qcategory_instance_menu_workspace, Qmenu_workspace, Qpage;
    Object Qlogbook_page, Qprocedure_invocation, Qedit_box, Qstatement;
    Object Qauthorized_user, Qexternal_simulation_definition;
    Object Qforeign_function_declaration, Qmodel_definition, Qplot;
    Object Qgraph_grid, Qdigital_clock, Qmeter, Qdial;
    Object Qremote_procedure_declaration, list_constant_30;
    Object Qslider_minimum_value_label, Qquantitative_variable, Qloose_end;
    Object Qmessage, Qtable, Qsimulation_subtable, Qrelation, Qobject;
    Object Qgeneric_simulation_formula, Qok, Qgraph, Qreadout_table;
    Object Qmarker_for_meter, Qruling_for_meter, Qpointer_for_dial;
    Object Qruling_for_dial, Qdefault_junction, Qaction_button;
    Object Qconnection_post, Qnon_kb_workspace, Qdependent_frame, Qdefinition;
    Object list_constant_29, Qinteger_array, Qitem_array, Qg2_array;
    Object Qtruth_value_list, Qtext_list, Qsymbol_list, Qquantity_list;
    Object Qfloat_list, Qinteger_list, Qitem_list, Qg2_list, Qtabular_function;
    Object Qbounding_box, Qicon_editor_table_info_frame, Qobject_definition;
    Object Qicon_editor_workspace, Qworkspace, Qentity, Qg2_window;
    Object Qarrow_button, Qtype_in_box, Qgeneric_action_button, Qbutton;
    Object Qtype_in_text_box, Qslider_needle, Qbutton_label, Qslider_readout;
    Object Qquestion_mark_box, Qrule, Qvalue_array, Qvalue_list;
    Object Qtruth_value_array, Qtext_array, Qsymbol_array, Qquantity_array;
    Object Qpprint_type_check_float_instruction, Qstack_type_check_float_body;
    Object Qpprint_type_check_integer_instruction;
    Object Qstack_type_check_integer_body;
    Object Qpprint_type_check_quantity_instruction;
    Object Qstack_type_check_quantity_body;
    Object Qpprint_type_check_text_instruction, Qstack_type_check_text_body;
    Object Qpprint_type_check_symbol_instruction;
    Object Qstack_type_check_symbol_body;
    Object Qpprint_type_check_truth_value_instruction;
    Object Qstack_type_check_truth_value_body, Qcase_dispatch;
    Object Qpprint_case_dispatch_instruction, Qstack_case_dispatch_body;
    Object Qprint_case_dispatch, Qcase_dispatch_byte_count;
    Object Qpprint_push_from_stack_arg_instruction;
    Object Qstack_push_value_or_none_from_stack_arg_body;
    Object Qprint_op_and_code_constant_and_typecode;
    Object Qpush_value_or_none_from_stack_arg, Qstack_push_from_stack_arg_body;
    Object Qpush_from_stack_arg, Qstack_pop_into_stack_arg_body;
    Object Qpop_into_stack_arg;
    Object Qstack_push_value_or_none_from_stack_frame_var_body;
    Object Qpush_value_or_none_from_stack_frame_var;
    Object Qstack_push_from_stack_frame_var_body, Qpush_from_stack_frame_var;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object Qevaluation_value, list_constant_13, list_constant_12;
    Object list_constant_11, list_constant_9, Qlong, Qab_or, list_constant_10;
    Object list_constant_8, Qab_class, Qno_item, Qor_nil_typecode_modifier;
    Object Qlong_typecode, Qstructure_typecode, Qsequence_typecode;
    Object Qanything_typecode, Qitem_or_datum_typecode;
    Object Qevaluation_type_typecode, Qdefined_evaluation_type_typecode;
    Object Qiteration_state_typecode, Qitem_typecode, Qtext_typecode;
    Object Qtruth_value_typecode, Qsymbol_typecode, Qfloat_typecode;
    Object Qinteger_typecode, Qnil_typecode;
    Object Qstack_pop_into_stack_frame_var_body, Qpop_into_stack_frame_var;
    Object Qstack_pop_values_body, Qpop_values, Qstack_pop_body;
    Object Qstack_minimize_expiration_body, Qminimize_expiration;
    Object Qstack_pop_expiration_body, Qpop_expiration;
    Object Qstack_push_expiration_body, Qpush_expiration;
    Object Qbranch_long_if_known, Qpprint_branch_relative_if_known_instruction;
    Object Qstack_branch_relative_if_known_body;
    Object Qpprint_branch_long_if_known_instruction;
    Object Qstack_branch_long_if_known_body;
    Object Qpprint_branch_if_known_instruction, Qstack_branch_if_known_body;
    Object Qstack_reset_expiration_body, Qreset_expiration;
    Object Qstack_push_internal_constant_long_body;
    Object Qpush_internal_constant_long, Qstack_push_internal_constant_body;
    Object Qpush_internal_constant, Qstack_push_none_body, Qpush_none;
    Object Qstack_push_one_body, Qpush_one, Qstack_push_zero_body, Qpush_zero;
    Object Qstack_push_false_body, Qpush_false, Qstack_push_true_body;
    Object Qpush_true, Qstack_push_small_integer_body;
    Object Qprint_op_and_relative_code_constant, Qpush_small_integer;
    Object Qstack_push_constant_long_body, Qpush_constant_long;
    Object Qstack_push_constant_body, Qpush_constant, Qbranch_long_if_not_true;
    Object Qstack_branch_relative_if_not_true_body;
    Object Qstack_branch_long_if_not_true_body, Qstack_branch_if_not_true_body;
    Object Qbranch_long, Qpprint_branch_relative_instruction;
    Object Qstack_branch_relative_body, Qpprint_branch_long_instruction;
    Object Qstack_branch_long_body, Qpprint_branch_instruction;
    Object Qstack_branch_body;

    x_note_fn_call(205,263);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING(", ");
    string_constant_1 = STATIC_STRING(" by ~a to ~a");
    string_constant_2 = STATIC_STRING(" #~a (");
    AB_package = STATIC_PACKAGE("AB");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_3 = STATIC_STRING("~NF");
    string_constant_4 = STATIC_STRING(", ~a");
    string_constant_5 = STATIC_STRING(" #~a, ");
    string_constant_6 = STATIC_STRING(" #~a, the ");
    string_constant_7 = STATIC_STRING(", ~a arguments");
    Qerror_unused_index = STATIC_SYMBOL("ERROR-UNUSED-INDEX",AB_package);
    string_constant_8 = STATIC_STRING("internal out-of-line evaluator ~a");
    string_constant_9 = STATIC_STRING("internal out-of-line instruction ~a");
    string_constant_10 = STATIC_STRING(" (~D arguments, ~D results)");
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    string_constant_11 = 
	    STATIC_STRING(", base = ~a, highest = ~a, index->address = ");
    string_constant_12 = STATIC_STRING("~a->~a, ");
    string_constant_13 = STATIC_STRING("else->~a");
    string_constant_14 = 
	    STATIC_STRING(", argument-count = ~a, values-count = ~a");
    string_constant_15 = STATIC_STRING(", argument-count = ~a");
    string_constant_16 = 
	    STATIC_STRING(" out ~a code bodies to entry point #~a");
    array_constant_2 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    string_constant_17 = STATIC_STRING(", branch to ~a if no values");
    array_constant_3 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    string_constant_18 = STATIC_STRING(", for there exists");
    string_constant_19 = STATIC_STRING(" #~a, argument-count = ~a");
    string_constant_20 = STATIC_STRING(" #~a, ~NT");
    array_constant_4 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    string_constant_21 = STATIC_STRING(", ~a elements");
    array_constant_5 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    string_constant_22 = STATIC_STRING(" starting at ");
    string_constant_23 = STATIC_STRING(", branch to ~a if empty");
    array_constant_6 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    string_constant_24 = STATIC_STRING("branch if known (~a) to ~a");
    string_constant_25 = STATIC_STRING("known");
    string_constant_26 = STATIC_STRING("unknown");
    array_constant_8 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    string_constant_27 = STATIC_STRING(" is a ~NT");
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_28 = STATIC_STRING(" is a ~a");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    array_constant_13 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)57344L);
    string_constant_29 = STATIC_STRING("~a");
    array_constant_17 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)31L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    string_constant_30 = STATIC_STRING("fetch the ~a of ");
    array_constant_23 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)31L,(SI_Long)57344L);
    string_constant_31 = STATIC_STRING(" at location ~a");
    array_constant_24 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    array_constant_29 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)31L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)39L,(SI_Long)57344L);
    string_constant_32 = STATIC_STRING(", branch to ~a if none");
    array_constant_32 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)22L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)31L,(SI_Long)57344L);
    string_constant_33 = STATIC_STRING(" is an item");
    array_constant_33 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)57344L);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    array_constant_36 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)21L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)31L,(SI_Long)57344L);
    array_constant_37 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)31L,(SI_Long)57344L);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    array_constant_38 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)23L,(SI_Long)57344L);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    string_constant_34 = STATIC_STRING("of class ~a ");
    array_constant_39 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)23L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)15L,(SI_Long)57344L);
    array_constant_41 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)39L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)57344L);
    array_constant_43 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)31L,(SI_Long)57344L);
    array_constant_44 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)23L,(SI_Long)57344L);
    string_constant_35 = STATIC_STRING("~a ");
    array_constant_46 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)23L,(SI_Long)57344L);
    array_constant_47 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)57344L);
    array_constant_48 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)31L,(SI_Long)57344L);
    array_constant_49 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)57344L);
    array_constant_50 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)57344L);
    Qscale = STATIC_SYMBOL("SCALE",AB_package);
    array_constant_51 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)57344L);
    array_constant_52 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)15L,(SI_Long)57344L);
    Qworkspace_position = STATIC_SYMBOL("WORKSPACE-POSITION",AB_package);
    array_constant_53 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)15L,(SI_Long)57344L);
    array_constant_54 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)23L,(SI_Long)57344L);
    Qscreen_position = STATIC_SYMBOL("SCREEN-POSITION",AB_package);
    array_constant_55 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)15L,(SI_Long)57344L);
    array_constant_56 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)21L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)31L,(SI_Long)57344L);
    array_constant_57 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)15L,(SI_Long)57344L);
    array_constant_58 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)7L,(SI_Long)57344L);
    array_constant_59 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)23L,(SI_Long)57344L);
    array_constant_60 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)23L,(SI_Long)57344L);
    array_constant_61 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)23L,(SI_Long)57344L);
    array_constant_62 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)23L,(SI_Long)57344L);
    array_constant_63 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)14L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)23L,(SI_Long)57344L);
    string_constant_36 = STATIC_STRING("every ~a");
    array_constant_64 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)15L,(SI_Long)57344L);
    array_constant_65 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)0L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)7L,(SI_Long)57344L);
    array_constant_66 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)0L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)7L,(SI_Long)57344L);
    array_constant_67 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)25L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)31L,(SI_Long)57344L);
    array_constant_68 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)19L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)29L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)39L,(SI_Long)57344L);
    string_constant_37 = 
	    string_append2(STATIC_STRING("Attempted to execute ~a, which does not name a valid instruction.  ~\n     Execution has proceeded past the end of valid instructions or is ~\n     executing data.  Please repor"),
	    STATIC_STRING("t this G2 byte code executor bug to Gensym ~\n     software support."));
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    Qprint_op_and_code_constant = 
	    STATIC_SYMBOL("PRINT-OP-AND-CODE-CONSTANT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_code_constant,
	    STATIC_FUNCTION(print_op_and_code_constant,NIL,FALSE,4,4));
    Qstack_branch_body = STATIC_SYMBOL("STACK-BRANCH-BODY",AB_package);
    Qpprint_branch_instruction = STATIC_SYMBOL("PPRINT-BRANCH-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_instruction,
	    STATIC_FUNCTION(pprint_branch_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)1L),
	    Qstack_branch_body,SYMBOL_FUNCTION(Qpprint_branch_instruction));
    Qbranch_long = STATIC_SYMBOL("BRANCH-LONG",AB_package);
    Qprint_op_and_long_code_constant = 
	    STATIC_SYMBOL("PRINT-OP-AND-LONG-CODE-CONSTANT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_long_code_constant,
	    STATIC_FUNCTION(print_op_and_long_code_constant,NIL,FALSE,4,4));
    Qstack_branch_long_body = STATIC_SYMBOL("STACK-BRANCH-LONG-BODY",
	    AB_package);
    Qpprint_branch_long_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-LONG-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_long_instruction,
	    STATIC_FUNCTION(pprint_branch_long_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_long,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_long_code_constant),
	    FIX((SI_Long)2L),Qstack_branch_long_body,
	    SYMBOL_FUNCTION(Qpprint_branch_long_instruction));
    Qbranch_relative = STATIC_SYMBOL("BRANCH-RELATIVE",AB_package);
    Qprint_op_and_relative_code_constant_address = 
	    STATIC_SYMBOL("PRINT-OP-AND-RELATIVE-CODE-CONSTANT-ADDRESS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant_address,
	    STATIC_FUNCTION(print_op_and_relative_code_constant_address,
	    NIL,FALSE,4,4));
    Qstack_branch_relative_body = 
	    STATIC_SYMBOL("STACK-BRANCH-RELATIVE-BODY",AB_package);
    Qpprint_branch_relative_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-RELATIVE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_relative_instruction,
	    STATIC_FUNCTION(pprint_branch_relative_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_relative,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant_address),
	    FIX((SI_Long)3L),Qstack_branch_relative_body,
	    SYMBOL_FUNCTION(Qpprint_branch_relative_instruction));
    Qbyte_code_resolver = STATIC_SYMBOL("BYTE-CODE-RESOLVER",AB_package);
    bc_branch_long_resolver_1 = STATIC_FUNCTION(bc_branch_long_resolver,
	    NIL,FALSE,4,4);
    mutate_global_property(Qbranch_long,bc_branch_long_resolver_1,
	    Qbyte_code_resolver);
    Qbranch_if_not_true = STATIC_SYMBOL("BRANCH-IF-NOT-TRUE",AB_package);
    Qstack_branch_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BRANCH-IF-NOT-TRUE-BODY",AB_package);
    Qpprint_branch_if_not_true_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-IF-NOT-TRUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_if_not_true_instruction,
	    STATIC_FUNCTION(pprint_branch_if_not_true_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)4L),
	    Qstack_branch_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_if_not_true_instruction));
    Qbranch_long_if_not_true = STATIC_SYMBOL("BRANCH-LONG-IF-NOT-TRUE",
	    AB_package);
    Qstack_branch_long_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BRANCH-LONG-IF-NOT-TRUE-BODY",AB_package);
    Qpprint_branch_long_if_not_true_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-LONG-IF-NOT-TRUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_long_if_not_true_instruction,
	    STATIC_FUNCTION(pprint_branch_long_if_not_true_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_long_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_long_code_constant),
	    FIX((SI_Long)5L),Qstack_branch_long_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_long_if_not_true_instruction));
    Qbranch_relative_if_not_true = 
	    STATIC_SYMBOL("BRANCH-RELATIVE-IF-NOT-TRUE",AB_package);
    Qstack_branch_relative_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BRANCH-RELATIVE-IF-NOT-TRUE-BODY",AB_package);
    Qpprint_branch_relative_if_not_true_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-RELATIVE-IF-NOT-TRUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_relative_if_not_true_instruction,
	    STATIC_FUNCTION(pprint_branch_relative_if_not_true_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_relative_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant_address),
	    FIX((SI_Long)6L),Qstack_branch_relative_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_relative_if_not_true_instruction));
    bc_branch_long_if_not_true_resolver_1 = 
	    STATIC_FUNCTION(bc_branch_long_if_not_true_resolver,NIL,FALSE,4,4);
    mutate_global_property(Qbranch_long_if_not_true,
	    bc_branch_long_if_not_true_resolver_1,Qbyte_code_resolver);
    Qpush_constant = STATIC_SYMBOL("PUSH-CONSTANT",AB_package);
    Qprint_op_and_constant = STATIC_SYMBOL("PRINT-OP-AND-CONSTANT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_constant,
	    STATIC_FUNCTION(print_op_and_constant,NIL,FALSE,4,4));
    Qstack_push_constant_body = STATIC_SYMBOL("STACK-PUSH-CONSTANT-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_constant,
	    FIX((SI_Long)2L),Nil,SYMBOL_FUNCTION(Qprint_op_and_constant),
	    FIX((SI_Long)7L),Qstack_push_constant_body,Nil);
    Qpush_constant_long = STATIC_SYMBOL("PUSH-CONSTANT-LONG",AB_package);
    Qprint_op_and_constant_long = 
	    STATIC_SYMBOL("PRINT-OP-AND-CONSTANT-LONG",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_constant_long,
	    STATIC_FUNCTION(print_op_and_constant_long,NIL,FALSE,4,4));
    Qstack_push_constant_long_body = 
	    STATIC_SYMBOL("STACK-PUSH-CONSTANT-LONG-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_constant_long,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_constant_long),FIX((SI_Long)8L),
	    Qstack_push_constant_long_body,Nil);
    Qpush_small_integer = STATIC_SYMBOL("PUSH-SMALL-INTEGER",AB_package);
    Qprint_op_and_relative_code_constant = 
	    STATIC_SYMBOL("PRINT-OP-AND-RELATIVE-CODE-CONSTANT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant,
	    STATIC_FUNCTION(print_op_and_relative_code_constant,NIL,FALSE,
	    4,4));
    Qstack_push_small_integer_body = 
	    STATIC_SYMBOL("STACK-PUSH-SMALL-INTEGER-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_small_integer,
	    FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant),
	    FIX((SI_Long)9L),Qstack_push_small_integer_body,Nil);
    Qpush_true = STATIC_SYMBOL("PUSH-TRUE",AB_package);
    Qstack_push_true_body = STATIC_SYMBOL("STACK-PUSH-TRUE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_true,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)10L),
	    Qstack_push_true_body,Nil);
    Qpush_false = STATIC_SYMBOL("PUSH-FALSE",AB_package);
    Qstack_push_false_body = STATIC_SYMBOL("STACK-PUSH-FALSE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_false,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)11L),
	    Qstack_push_false_body,Nil);
    Qpush_zero = STATIC_SYMBOL("PUSH-ZERO",AB_package);
    Qstack_push_zero_body = STATIC_SYMBOL("STACK-PUSH-ZERO-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_zero,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)12L),
	    Qstack_push_zero_body,Nil);
    Qpush_one = STATIC_SYMBOL("PUSH-ONE",AB_package);
    Qstack_push_one_body = STATIC_SYMBOL("STACK-PUSH-ONE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_one,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)13L),
	    Qstack_push_one_body,Nil);
    Qpush_none = STATIC_SYMBOL("PUSH-NONE",AB_package);
    Qstack_push_none_body = STATIC_SYMBOL("STACK-PUSH-NONE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_none,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)14L),
	    Qstack_push_none_body,Nil);
    Qpush_internal_constant = STATIC_SYMBOL("PUSH-INTERNAL-CONSTANT",
	    AB_package);
    Qstack_push_internal_constant_body = 
	    STATIC_SYMBOL("STACK-PUSH-INTERNAL-CONSTANT-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_internal_constant,
	    FIX((SI_Long)2L),Nil,SYMBOL_FUNCTION(Qprint_op_and_constant),
	    FIX((SI_Long)15L),Qstack_push_internal_constant_body,Nil);
    Qpush_internal_constant_long = 
	    STATIC_SYMBOL("PUSH-INTERNAL-CONSTANT-LONG",AB_package);
    Qstack_push_internal_constant_long_body = 
	    STATIC_SYMBOL("STACK-PUSH-INTERNAL-CONSTANT-LONG-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_internal_constant_long,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_constant_long),FIX((SI_Long)16L),
	    Qstack_push_internal_constant_long_body,Nil);
    Qreset_expiration = STATIC_SYMBOL("RESET-EXPIRATION",AB_package);
    Qstack_reset_expiration_body = 
	    STATIC_SYMBOL("STACK-RESET-EXPIRATION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qreset_expiration,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)17L),
	    Qstack_reset_expiration_body,Nil);
    Qbranch_if_known = STATIC_SYMBOL("BRANCH-IF-KNOWN",AB_package);
    Qstack_branch_if_known_body = 
	    STATIC_SYMBOL("STACK-BRANCH-IF-KNOWN-BODY",AB_package);
    Qpprint_branch_if_known_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-IF-KNOWN-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_if_known_instruction,
	    STATIC_FUNCTION(pprint_branch_if_known_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_if_known,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)18L),
	    Qstack_branch_if_known_body,
	    SYMBOL_FUNCTION(Qpprint_branch_if_known_instruction));
    Qbranch_long_if_known = STATIC_SYMBOL("BRANCH-LONG-IF-KNOWN",AB_package);
    Qstack_branch_long_if_known_body = 
	    STATIC_SYMBOL("STACK-BRANCH-LONG-IF-KNOWN-BODY",AB_package);
    Qpprint_branch_long_if_known_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-LONG-IF-KNOWN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_long_if_known_instruction,
	    STATIC_FUNCTION(pprint_branch_long_if_known_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_long_if_known,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_long_code_constant),
	    FIX((SI_Long)19L),Qstack_branch_long_if_known_body,
	    SYMBOL_FUNCTION(Qpprint_branch_long_if_known_instruction));
    Qbranch_relative_if_known = STATIC_SYMBOL("BRANCH-RELATIVE-IF-KNOWN",
	    AB_package);
    Qstack_branch_relative_if_known_body = 
	    STATIC_SYMBOL("STACK-BRANCH-RELATIVE-IF-KNOWN-BODY",AB_package);
    Qpprint_branch_relative_if_known_instruction = 
	    STATIC_SYMBOL("PPRINT-BRANCH-RELATIVE-IF-KNOWN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_branch_relative_if_known_instruction,
	    STATIC_FUNCTION(pprint_branch_relative_if_known_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qbranch_relative_if_known,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant_address),
	    FIX((SI_Long)20L),Qstack_branch_relative_if_known_body,
	    SYMBOL_FUNCTION(Qpprint_branch_relative_if_known_instruction));
    bc_branch_long_if_known_resolver_1 = 
	    STATIC_FUNCTION(bc_branch_long_if_known_resolver,NIL,FALSE,4,4);
    mutate_global_property(Qbranch_long_if_known,
	    bc_branch_long_if_known_resolver_1,Qbyte_code_resolver);
    Qpush_expiration = STATIC_SYMBOL("PUSH-EXPIRATION",AB_package);
    Qstack_push_expiration_body = 
	    STATIC_SYMBOL("STACK-PUSH-EXPIRATION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_expiration,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)21L),
	    Qstack_push_expiration_body,Nil);
    Qpop_expiration = STATIC_SYMBOL("POP-EXPIRATION",AB_package);
    Qstack_pop_expiration_body = STATIC_SYMBOL("STACK-POP-EXPIRATION-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpop_expiration,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)22L),
	    Qstack_pop_expiration_body,Nil);
    Qminimize_expiration = STATIC_SYMBOL("MINIMIZE-EXPIRATION",AB_package);
    Qstack_minimize_expiration_body = 
	    STATIC_SYMBOL("STACK-MINIMIZE-EXPIRATION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qminimize_expiration,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)23L),
	    Qstack_minimize_expiration_body,Nil);
    Qstack_pop_body = STATIC_SYMBOL("STACK-POP-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop,FIX((SI_Long)1L),
	    Nil,Nil,FIX((SI_Long)24L),Qstack_pop_body,Nil);
    Qpop_values = STATIC_SYMBOL("POP-VALUES",AB_package);
    Qstack_pop_values_body = STATIC_SYMBOL("STACK-POP-VALUES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_values,
	    FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)25L),
	    Qstack_pop_values_body,Nil);
    string_constant_38 = STATIC_STRING("pop-values stack instruction emitter");
    string_constant_39 = 
	    STATIC_STRING("Trying to pop ~a values, can\'t pop less than zero.");
    Qpop_into_stack_frame_var = STATIC_SYMBOL("POP-INTO-STACK-FRAME-VAR",
	    AB_package);
    Qstack_pop_into_stack_frame_var_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-STACK-FRAME-VAR-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_into_stack_frame_var,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)26L),
	    Qstack_pop_into_stack_frame_var_body,Nil);
    Qnil_typecode = STATIC_SYMBOL("NIL-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qnil_typecode,FIX((SI_Long)0L));
    Qinteger_typecode = STATIC_SYMBOL("INTEGER-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qinteger_typecode,FIX((SI_Long)1L));
    Qfloat_typecode = STATIC_SYMBOL("FLOAT-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qfloat_typecode,FIX((SI_Long)2L));
    Qsymbol_typecode = STATIC_SYMBOL("SYMBOL-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qsymbol_typecode,FIX((SI_Long)3L));
    Qtruth_value_typecode = STATIC_SYMBOL("TRUTH-VALUE-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qtruth_value_typecode,FIX((SI_Long)4L));
    Qtext_typecode = STATIC_SYMBOL("TEXT-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qtext_typecode,FIX((SI_Long)5L));
    Qitem_typecode = STATIC_SYMBOL("ITEM-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qitem_typecode,FIX((SI_Long)6L));
    Qiteration_state_typecode = STATIC_SYMBOL("ITERATION-STATE-TYPECODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qiteration_state_typecode,FIX((SI_Long)7L));
    Qdefined_evaluation_type_typecode = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qdefined_evaluation_type_typecode,FIX((SI_Long)8L));
    Qevaluation_type_typecode = STATIC_SYMBOL("EVALUATION-TYPE-TYPECODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qevaluation_type_typecode,FIX((SI_Long)9L));
    Qitem_or_datum_typecode = STATIC_SYMBOL("ITEM-OR-DATUM-TYPECODE",
	    AB_package);
    SET_SYMBOL_VALUE(Qitem_or_datum_typecode,FIX((SI_Long)10L));
    Qanything_typecode = STATIC_SYMBOL("ANYTHING-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qanything_typecode,FIX((SI_Long)11L));
    Qsequence_typecode = STATIC_SYMBOL("SEQUENCE-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qsequence_typecode,FIX((SI_Long)12L));
    Qstructure_typecode = STATIC_SYMBOL("STRUCTURE-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qstructure_typecode,FIX((SI_Long)13L));
    Qlong_typecode = STATIC_SYMBOL("LONG-TYPECODE",AB_package);
    SET_SYMBOL_VALUE(Qlong_typecode,FIX((SI_Long)14L));
    Qor_nil_typecode_modifier = STATIC_SYMBOL("OR-NIL-TYPECODE-MODIFIER",
	    AB_package);
    SET_SYMBOL_VALUE(Qor_nil_typecode_modifier,FIX((SI_Long)32L));
    string_constant_40 = STATIC_STRING("unrecognized typecode");
    string_constant_41 = STATIC_STRING("null");
    string_constant_42 = STATIC_STRING("integer");
    string_constant_43 = STATIC_STRING("float");
    string_constant_44 = STATIC_STRING("symbol");
    string_constant_45 = STATIC_STRING("truth-value");
    string_constant_46 = STATIC_STRING("text");
    string_constant_47 = STATIC_STRING("item");
    string_constant_48 = STATIC_STRING("iteration state");
    string_constant_49 = STATIC_STRING("defined valuation type");
    string_constant_50 = STATIC_STRING("evaluation type");
    string_constant_51 = STATIC_STRING("item or datum");
    string_constant_52 = STATIC_STRING("object of unknown type");
    string_constant_53 = STATIC_STRING("sequence type");
    string_constant_54 = STATIC_STRING("structure type");
    string_constant_55 = STATIC_STRING("long");
    string_constant_56 = STATIC_STRING("either null or ");
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant = STATIC_CONS(Qno_item,Qnil);
    list_constant_14 = STATIC_LIST((SI_Long)2L,list_constant,FIX((SI_Long)0L));
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qinteger,FIX((SI_Long)1L));
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qlong,FIX((SI_Long)14L));
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qfloat,FIX((SI_Long)2L));
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qsymbol,FIX((SI_Long)3L));
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qtruth_value,FIX((SI_Long)4L));
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qtext,FIX((SI_Long)5L));
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_21 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    FIX((SI_Long)6L));
    list_constant_9 = STATIC_CONS(Qiteration_state,Qnil);
    list_constant_22 = STATIC_LIST((SI_Long)2L,list_constant_9,
	    FIX((SI_Long)7L));
    list_constant_10 = STATIC_CONS(Qsequence,Qnil);
    list_constant_23 = STATIC_LIST((SI_Long)2L,list_constant_10,
	    FIX((SI_Long)12L));
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_3 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_24 = STATIC_LIST((SI_Long)2L,list_constant_3,
	    FIX((SI_Long)13L));
    Qevaluation_value = STATIC_SYMBOL("EVALUATION-VALUE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)8L,Qab_or,Qinteger,Qlong,
	    Qfloat,Qsymbol,Qtruth_value,Qtext,list_constant_9);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_11);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qand,Qevaluation_value,
	    list_constant_12);
    list_constant_25 = STATIC_LIST((SI_Long)2L,list_constant_13,
	    FIX((SI_Long)8L));
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qevaluation_value,
	    FIX((SI_Long)9L));
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qitem_or_datum,
	    FIX((SI_Long)10L));
    list_constant_28 = STATIC_LIST((SI_Long)14L,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24,list_constant_25,list_constant_26,
	    list_constant_27);
    Types_and_typecodes = list_constant_28;
    No_information_typecode = add(FIX((SI_Long)10L),FIX((SI_Long)32L));
    if (Use_type_info == UNBOUND)
	Use_type_info = T;
    if (Always_make_runtime_nil_checks == UNBOUND)
	Always_make_runtime_nil_checks = T;
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_57 = 
	    STATIC_STRING("Nothing was returned from an expression which should have ~\n              returned a value of the type ~NT.");
    array_constant_69 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)14L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)23L,(SI_Long)57344L);
    string_constant_58 = 
	    STATIC_STRING(" is being given to an operation which requires values of the ~\n              type ~NT.");
    Qpush_from_stack_frame_var = STATIC_SYMBOL("PUSH-FROM-STACK-FRAME-VAR",
	    AB_package);
    Qprint_op_and_code_constant_and_typecode = 
	    STATIC_SYMBOL("PRINT-OP-AND-CODE-CONSTANT-AND-TYPECODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_code_constant_and_typecode,
	    STATIC_FUNCTION(print_op_and_code_constant_and_typecode,NIL,
	    FALSE,4,4));
    Qstack_push_from_stack_frame_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-STACK-FRAME-VAR-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_from_stack_frame_var,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant_and_typecode),
	    FIX((SI_Long)27L),Qstack_push_from_stack_frame_var_body,Nil);
    Qpush_value_or_none_from_stack_frame_var = 
	    STATIC_SYMBOL("PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR",
	    AB_package);
    Qstack_push_value_or_none_from_stack_frame_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-VALUE-OR-NONE-FROM-STACK-FRAME-VAR-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_value_or_none_from_stack_frame_var,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant_and_typecode),
	    FIX((SI_Long)121L),
	    Qstack_push_value_or_none_from_stack_frame_var_body,Nil);
    Qpop_into_stack_arg = STATIC_SYMBOL("POP-INTO-STACK-ARG",AB_package);
    Qstack_pop_into_stack_arg_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-STACK-ARG-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_into_stack_arg,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)28L),
	    Qstack_pop_into_stack_arg_body,Nil);
    Qpush_from_stack_arg = STATIC_SYMBOL("PUSH-FROM-STACK-ARG",AB_package);
    Qstack_push_from_stack_arg_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-STACK-ARG-BODY",AB_package);
    Qpprint_push_from_stack_arg_instruction = 
	    STATIC_SYMBOL("PPRINT-PUSH-FROM-STACK-ARG-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_push_from_stack_arg_instruction,
	    STATIC_FUNCTION(pprint_push_from_stack_arg_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qpush_from_stack_arg,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant_and_typecode),
	    FIX((SI_Long)29L),Qstack_push_from_stack_arg_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_stack_arg_instruction));
    Qpush_value_or_none_from_stack_arg = 
	    STATIC_SYMBOL("PUSH-VALUE-OR-NONE-FROM-STACK-ARG",AB_package);
    Qstack_push_value_or_none_from_stack_arg_body = 
	    STATIC_SYMBOL("STACK-PUSH-VALUE-OR-NONE-FROM-STACK-ARG-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_value_or_none_from_stack_arg,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant_and_typecode),
	    FIX((SI_Long)122L),
	    Qstack_push_value_or_none_from_stack_arg_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_stack_arg_instruction));
    Qcase_dispatch = STATIC_SYMBOL("CASE-DISPATCH",AB_package);
    Qcase_dispatch_byte_count = STATIC_SYMBOL("CASE-DISPATCH-BYTE-COUNT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcase_dispatch_byte_count,
	    STATIC_FUNCTION(case_dispatch_byte_count,NIL,FALSE,3,3));
    Qprint_case_dispatch = STATIC_SYMBOL("PRINT-CASE-DISPATCH",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_case_dispatch,
	    STATIC_FUNCTION(print_case_dispatch,NIL,FALSE,4,4));
    Qstack_case_dispatch_body = STATIC_SYMBOL("STACK-CASE-DISPATCH-BODY",
	    AB_package);
    Qpprint_case_dispatch_instruction = 
	    STATIC_SYMBOL("PPRINT-CASE-DISPATCH-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_case_dispatch_instruction,
	    STATIC_FUNCTION(pprint_case_dispatch_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcase_dispatch,
	    SYMBOL_FUNCTION(Qcase_dispatch_byte_count),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_case_dispatch),FIX((SI_Long)30L),
	    Qstack_case_dispatch_body,
	    SYMBOL_FUNCTION(Qpprint_case_dispatch_instruction));
    bc_case_dispatch_resolver_1 = 
	    STATIC_FUNCTION(bc_case_dispatch_resolver,NIL,FALSE,4,4);
    mutate_global_property(Qcase_dispatch,bc_case_dispatch_resolver_1,
	    Qbyte_code_resolver);
    Qtype_check_truth_value = STATIC_SYMBOL("TYPE-CHECK-TRUTH-VALUE",
	    AB_package);
    Qstack_type_check_truth_value_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-TRUTH-VALUE-BODY",AB_package);
    Qpprint_type_check_truth_value_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-TRUTH-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_truth_value_instruction,
	    STATIC_FUNCTION(pprint_type_check_truth_value_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_truth_value,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)31L),
	    Qstack_type_check_truth_value_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_truth_value_instruction));
    Qtype_check_symbol = STATIC_SYMBOL("TYPE-CHECK-SYMBOL",AB_package);
    Qstack_type_check_symbol_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-SYMBOL-BODY",AB_package);
    Qpprint_type_check_symbol_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-SYMBOL-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_symbol_instruction,
	    STATIC_FUNCTION(pprint_type_check_symbol_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qtype_check_symbol,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)32L),
	    Qstack_type_check_symbol_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_symbol_instruction));
    Qtype_check_text = STATIC_SYMBOL("TYPE-CHECK-TEXT",AB_package);
    Qstack_type_check_text_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-TEXT-BODY",AB_package);
    Qpprint_type_check_text_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-TEXT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_text_instruction,
	    STATIC_FUNCTION(pprint_type_check_text_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_text,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)33L),
	    Qstack_type_check_text_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_text_instruction));
    Qtype_check_quantity = STATIC_SYMBOL("TYPE-CHECK-QUANTITY",AB_package);
    Qstack_type_check_quantity_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-QUANTITY-BODY",AB_package);
    Qpprint_type_check_quantity_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-QUANTITY-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_quantity_instruction,
	    STATIC_FUNCTION(pprint_type_check_quantity_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_quantity,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)34L),
	    Qstack_type_check_quantity_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_quantity_instruction));
    Qtype_check_integer = STATIC_SYMBOL("TYPE-CHECK-INTEGER",AB_package);
    Qstack_type_check_integer_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-INTEGER-BODY",AB_package);
    Qpprint_type_check_integer_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-INTEGER-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_integer_instruction,
	    STATIC_FUNCTION(pprint_type_check_integer_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_integer,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)35L),
	    Qstack_type_check_integer_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_integer_instruction));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtype_check_float = STATIC_SYMBOL("TYPE-CHECK-FLOAT",AB_package);
    Qstack_type_check_float_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-FLOAT-BODY",AB_package);
    Qpprint_type_check_float_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-FLOAT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_float_instruction,
	    STATIC_FUNCTION(pprint_type_check_float_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qtype_check_float,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)36L),
	    Qstack_type_check_float_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_float_instruction));
    Qclasses_type_checked_inline = 
	    STATIC_SYMBOL("CLASSES-TYPE-CHECKED-INLINE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclasses_type_checked_inline,
	    Classes_type_checked_inline);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qinvisible_entity = STATIC_SYMBOL("INVISIBLE-ENTITY",AB_package);
    Qmessage_definition = STATIC_SYMBOL("MESSAGE-DEFINITION",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qlanguage_translation = STATIC_SYMBOL("LANGUAGE-TRANSLATION",AB_package);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    Qlogical_variable = STATIC_SYMBOL("LOGICAL-VARIABLE",AB_package);
    Qfloat_variable = STATIC_SYMBOL("FLOAT-VARIABLE",AB_package);
    Qinteger_variable = STATIC_SYMBOL("INTEGER-VARIABLE",AB_package);
    Qsymbolic_variable = STATIC_SYMBOL("SYMBOLIC-VARIABLE",AB_package);
    Qtext_variable = STATIC_SYMBOL("TEXT-VARIABLE",AB_package);
    Qlogical_parameter = STATIC_SYMBOL("LOGICAL-PARAMETER",AB_package);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    Qinteger_parameter = STATIC_SYMBOL("INTEGER-PARAMETER",AB_package);
    Qfloat_parameter = STATIC_SYMBOL("FLOAT-PARAMETER",AB_package);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
    Qtext_parameter = STATIC_SYMBOL("TEXT-PARAMETER",AB_package);
    Qforward_chaining_link = STATIC_SYMBOL("FORWARD-CHAINING-LINK",AB_package);
    Qtrue_value_update_recipient = 
	    STATIC_SYMBOL("TRUE-VALUE-UPDATE-RECIPIENT",AB_package);
    Qbackward_chaining_link = STATIC_SYMBOL("BACKWARD-CHAINING-LINK",
	    AB_package);
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    Qunits_of_measure_declaration = 
	    STATIC_SYMBOL("UNITS-OF-MEASURE-DECLARATION",AB_package);
    Qtabular_function_of_1_arg = STATIC_SYMBOL("TABULAR-FUNCTION-OF-1-ARG",
	    AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qg2_cell_array_cell = STATIC_SYMBOL("G2-CELL-ARRAY-CELL",AB_package);
    Qg2_query_cell = STATIC_SYMBOL("G2-QUERY-CELL",AB_package);
    Qg2_designation_cell = STATIC_SYMBOL("G2-DESIGNATION-CELL",AB_package);
    Qg2_expression_cell = STATIC_SYMBOL("G2-EXPRESSION-CELL",AB_package);
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qdigital_clock = STATIC_SYMBOL("DIGITAL-CLOCK",AB_package);
    Qgraph_grid = STATIC_SYMBOL("GRAPH-GRID",AB_package);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    Qmodel_definition = STATIC_SYMBOL("MODEL-DEFINITION",AB_package);
    Qforeign_function_declaration = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-DECLARATION",AB_package);
    Qexternal_simulation_definition = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION",AB_package);
    Qauthorized_user = STATIC_SYMBOL("AUTHORIZED-USER",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    Qedit_box = STATIC_SYMBOL("EDIT-BOX",AB_package);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    Qlogbook_page = STATIC_SYMBOL("LOGBOOK-PAGE",AB_package);
    Qpage = STATIC_SYMBOL("PAGE",AB_package);
    Qmenu_workspace = STATIC_SYMBOL("MENU-WORKSPACE",AB_package);
    Qcategory_instance_menu_workspace = 
	    STATIC_SYMBOL("CATEGORY-INSTANCE-MENU-WORKSPACE",AB_package);
    Qinspect_command = STATIC_SYMBOL("INSPECT-COMMAND",AB_package);
    Qicon_cell = STATIC_SYMBOL("ICON-CELL",AB_package);
    Qexplanation_table = STATIC_SYMBOL("EXPLANATION-TABLE",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qg2_login = STATIC_SYMBOL("G2-LOGIN",AB_package);
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    Qcategory_menu = STATIC_SYMBOL("CATEGORY-MENU",AB_package);
    Qscrap = STATIC_SYMBOL("SCRAP",AB_package);
    Qtext_region = STATIC_SYMBOL("TEXT-REGION",AB_package);
    Qkfep_conversion_choice_menu = 
	    STATIC_SYMBOL("KFEP-CONVERSION-CHOICE-MENU",AB_package);
    Qsubordinate_text_box = STATIC_SYMBOL("SUBORDINATE-TEXT-BOX",AB_package);
    Qdialog_button = STATIC_SYMBOL("DIALOG-BUTTON",AB_package);
    Qconnection_definition = STATIC_SYMBOL("CONNECTION-DEFINITION",AB_package);
    Qworkspace_name_box = STATIC_SYMBOL("WORKSPACE-NAME-BOX",AB_package);
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    Qnon_kb_workspace = STATIC_SYMBOL("NON-KB-WORKSPACE",AB_package);
    Qconnection_post = STATIC_SYMBOL("CONNECTION-POST",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    Qruling_for_dial = STATIC_SYMBOL("RULING-FOR-DIAL",AB_package);
    Qpointer_for_dial = STATIC_SYMBOL("POINTER-FOR-DIAL",AB_package);
    Qruling_for_meter = STATIC_SYMBOL("RULING-FOR-METER",AB_package);
    Qmarker_for_meter = STATIC_SYMBOL("MARKER-FOR-METER",AB_package);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qquantitative_variable = STATIC_SYMBOL("QUANTITATIVE-VARIABLE",AB_package);
    Qslider_minimum_value_label = 
	    STATIC_SYMBOL("SLIDER-MINIMUM-VALUE-LABEL",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qquestion_mark_box = STATIC_SYMBOL("QUESTION-MARK-BOX",AB_package);
    Qslider_readout = STATIC_SYMBOL("SLIDER-READOUT",AB_package);
    Qbutton_label = STATIC_SYMBOL("BUTTON-LABEL",AB_package);
    Qslider_needle = STATIC_SYMBOL("SLIDER-NEEDLE",AB_package);
    Qtype_in_text_box = STATIC_SYMBOL("TYPE-IN-TEXT-BOX",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qgeneric_action_button = STATIC_SYMBOL("GENERIC-ACTION-BUTTON",AB_package);
    Qtype_in_box = STATIC_SYMBOL("TYPE-IN-BOX",AB_package);
    Qarrow_button = STATIC_SYMBOL("ARROW-BUTTON",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qicon_editor_workspace = STATIC_SYMBOL("ICON-EDITOR-WORKSPACE",AB_package);
    Qobject_definition = STATIC_SYMBOL("OBJECT-DEFINITION",AB_package);
    Qicon_editor_table_info_frame = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME",AB_package);
    Qbounding_box = STATIC_SYMBOL("BOUNDING-BOX",AB_package);
    Qtabular_function = STATIC_SYMBOL("TABULAR-FUNCTION",AB_package);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qitem_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    Qinteger_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    Qfloat_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    Qtext_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    Qtruth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qtext_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qvalue_list = STATIC_SYMBOL("VALUE-LIST",AB_package);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)6L,Qquantity_array,
	    Qsymbol_array,Qtext_array,Qtruth_value_array,Qvalue_list,
	    Qvalue_array);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)32L,Qrule,
	    Qquestion_mark_box,Qslider_readout,Qbutton_label,
	    Qslider_needle,Qtype_in_text_box,Qbutton,
	    Qgeneric_action_button,Qtype_in_box,Qarrow_button,Qg2_window,
	    Qconnection,Qentity,Qworkspace,Qicon_editor_workspace,
	    Qobject_definition,Qicon_editor_table_info_frame,Qbounding_box,
	    Qtabular_function,Qg2_list,Qitem_list,Qinteger_list,
	    Qfloat_list,Qquantity_list,Qsymbol_list,Qtext_list,
	    Qtruth_value_list,Qg2_array,Qitem_array,Qinteger_array,
	    Qfloat_array,list_constant_29);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)32L,Qdefinition,
	    Qdependent_frame,Qnon_kb_workspace,Qconnection_post,
	    Qmessage_board,Qaction_button,Qchart,Qdefault_junction,
	    Qruling_for_dial,Qpointer_for_dial,Qruling_for_meter,
	    Qmarker_for_meter,Qreadout_table,Qgraph,Qok,
	    Qgeneric_simulation_formula,Qobject,Qprocedure,Qblock,
	    Qvariable_or_parameter,Qrelation,Qsimulation_subtable,Qitem,
	    Qkb_workspace,Qtable,Qmessage,Qloose_end,Qparameter,Qvariable,
	    Qquantitative_variable,Qslider_minimum_value_label,
	    list_constant_30);
    list_constant_32 = STATIC_LIST_STAR((SI_Long)32L,
	    Qremote_procedure_declaration,Qdial,Qmeter,Qdigital_clock,
	    Qgraph_grid,Qplot,Qmodel_definition,
	    Qforeign_function_declaration,Qexternal_simulation_definition,
	    Qauthorized_user,Qstatement,Qedit_box,Qprocedure_invocation,
	    Qlogbook_page,Qpage,Qmenu_workspace,
	    Qcategory_instance_menu_workspace,Qinspect_command,Qicon_cell,
	    Qexplanation_table,Qtext_box,Qg2_login,Qname_box,
	    Qcategory_menu,Qscrap,Qtext_region,
	    Qkfep_conversion_choice_menu,Qsubordinate_text_box,
	    Qdialog_button,Qconnection_definition,Qworkspace_name_box,
	    list_constant_31);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)32L,Qkb_frame,
	    Qtemporary_workspace,Qinvisible_entity,Qmessage_definition,
	    Qformat_frame,Qmenu,Qlanguage_translation,Quser_menu_choice,
	    Qgeneric_formula,Qlogical_variable,Qfloat_variable,
	    Qinteger_variable,Qsymbolic_variable,Qtext_variable,
	    Qlogical_parameter,Qquantitative_parameter,Qinteger_parameter,
	    Qfloat_parameter,Qsymbolic_parameter,Qtext_parameter,
	    Qforward_chaining_link,Qtrue_value_update_recipient,
	    Qbackward_chaining_link,Qfunction_definition,
	    Qunits_of_measure_declaration,Qtabular_function_of_1_arg,
	    Qg2_cell_array,Qg2_cell_array_cell,Qg2_query_cell,
	    Qg2_designation_cell,Qg2_expression_cell,list_constant_32);
    SET_SYMBOL_VALUE(Qclasses_type_checked_inline,list_constant_33);
    string_constant_59 = STATIC_STRING("~A ~A ~A.");
    string_constant_60 = STATIC_STRING("~NF ~A ~A.");
    string_constant_61 = STATIC_STRING("The symbol ~NV ~A ~A.");
    string_constant_62 = STATIC_STRING("~NV ~A ~A.");
    string_constant_63 = STATIC_STRING("None");
    string_constant_64 = 
	    STATIC_STRING("should have been an instance of the class");
    Qtype_check_class = STATIC_SYMBOL("TYPE-CHECK-CLASS",AB_package);
    Qstack_type_check_class_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-CLASS-BODY",AB_package);
    Qpprint_type_check_class_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-CLASS-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_class_instruction,
	    STATIC_FUNCTION(pprint_type_check_class_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qtype_check_class,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_constant),FIX((SI_Long)37L),
	    Qstack_type_check_class_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_class_instruction));
    Qtype_check_class_long = STATIC_SYMBOL("TYPE-CHECK-CLASS-LONG",AB_package);
    Qstack_type_check_class_long_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-CLASS-LONG-BODY",AB_package);
    Qpprint_type_check_class_long_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-CLASS-LONG-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_class_long_instruction,
	    STATIC_FUNCTION(pprint_type_check_class_long_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_class_long,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_constant_long),FIX((SI_Long)38L),
	    Qstack_type_check_class_long_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_class_long_instruction));
    Qtype_check_item_or_datum = STATIC_SYMBOL("TYPE-CHECK-ITEM-OR-DATUM",
	    AB_package);
    Qstack_type_check_item_or_datum_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-ITEM-OR-DATUM-BODY",AB_package);
    Qpprint_type_check_item_or_datum_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-ITEM-OR-DATUM-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_item_or_datum_instruction,
	    STATIC_FUNCTION(pprint_type_check_item_or_datum_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_item_or_datum,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)39L),
	    Qstack_type_check_item_or_datum_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_item_or_datum_instruction));
    string_constant_65 = STATIC_STRING("type check emitter");
    string_constant_66 = 
	    STATIC_STRING("Invalid type ~a given to instruction emitter.");
    list_constant_1 = STATIC_LIST((SI_Long)7L,Qitem_or_datum,Qtruth_value,
	    Qsymbol,Qtext,Qnumber,Qinteger,Qfloat);
    string_constant_67 = 
	    STATIC_STRING("An attempt was made to reference surrounding local var ~a.  This kind of ~\n   reference should only happen within procedures.");
    Qpop_into_surrounding_local_var = 
	    STATIC_SYMBOL("POP-INTO-SURROUNDING-LOCAL-VAR",AB_package);
    Qprint_op_and_surrounding_local_var_and_typecode = 
	    STATIC_SYMBOL("PRINT-OP-AND-SURROUNDING-LOCAL-VAR-AND-TYPECODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var_and_typecode,
	    STATIC_FUNCTION(print_op_and_surrounding_local_var_and_typecode,
	    NIL,FALSE,4,4));
    Qstack_pop_into_surrounding_local_var_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-SURROUNDING-LOCAL-VAR-BODY",
	    AB_package);
    Qpprint_pop_into_surrounding_local_var_instruction = 
	    STATIC_SYMBOL("PPRINT-POP-INTO-SURROUNDING-LOCAL-VAR-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_pop_into_surrounding_local_var_instruction,
	    STATIC_FUNCTION(pprint_pop_into_surrounding_local_var_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qpop_into_surrounding_local_var,
	    FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var_and_typecode),
	    FIX((SI_Long)40L),Qstack_pop_into_surrounding_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_pop_into_surrounding_local_var_instruction));
    string_constant_68 = STATIC_STRING("pop-into-local-var emitter");
    string_constant_69 = STATIC_STRING("An invalid var spot, ~a, was given.");
    list_constant_34 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_2 = STATIC_CONS(Qvar_spot,list_constant_34);
    Qstack_frame_var = STATIC_SYMBOL("STACK-FRAME-VAR",AB_package);
    Qstack_arg = STATIC_SYMBOL("STACK-ARG",AB_package);
    Qpop_into_local_var = STATIC_SYMBOL("POP-INTO-LOCAL-VAR",AB_package);
    Qprint_op_and_local_var_and_typecode = 
	    STATIC_SYMBOL("PRINT-OP-AND-LOCAL-VAR-AND-TYPECODE",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_local_var_and_typecode,
	    STATIC_FUNCTION(print_op_and_local_var_and_typecode,NIL,FALSE,
	    4,4));
    Qstack_pop_into_local_var_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-LOCAL-VAR-BODY",AB_package);
    Qpprint_pop_into_local_var_instruction = 
	    STATIC_SYMBOL("PPRINT-POP-INTO-LOCAL-VAR-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_pop_into_local_var_instruction,
	    STATIC_FUNCTION(pprint_pop_into_local_var_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qpop_into_local_var,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_local_var_and_typecode),
	    FIX((SI_Long)41L),Qstack_pop_into_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_pop_into_local_var_instruction));
    array_constant_70 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)23L,(SI_Long)57344L);
    array_constant_71 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)33L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)34L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)36L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)39L,(SI_Long)57344L);
    Qpush_from_surrounding_local_var = 
	    STATIC_SYMBOL("PUSH-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    Qstack_push_from_surrounding_local_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-SURROUNDING-LOCAL-VAR-BODY",
	    AB_package);
    Qpprint_push_from_surrounding_local_var_instruction = 
	    STATIC_SYMBOL("PPRINT-PUSH-FROM-SURROUNDING-LOCAL-VAR-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_push_from_surrounding_local_var_instruction,
	    STATIC_FUNCTION(pprint_push_from_surrounding_local_var_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qpush_from_surrounding_local_var,
	    FIX((SI_Long)4L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var_and_typecode),
	    FIX((SI_Long)42L),Qstack_push_from_surrounding_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_surrounding_local_var_instruction));
    Qpush_from_local_var = STATIC_SYMBOL("PUSH-FROM-LOCAL-VAR",AB_package);
    Qstack_push_from_local_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-LOCAL-VAR-BODY",AB_package);
    Qpprint_push_from_local_var_instruction = 
	    STATIC_SYMBOL("PPRINT-PUSH-FROM-LOCAL-VAR-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_push_from_local_var_instruction,
	    STATIC_FUNCTION(pprint_push_from_local_var_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qpush_from_local_var,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_local_var_and_typecode),
	    FIX((SI_Long)43L),Qstack_push_from_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_local_var_instruction));
    string_constant_70 = STATIC_STRING("push-from-local-var emitter");
    string_constant_71 = 
	    STATIC_STRING("The item named ~a cannot be referred to because it is disabled or inactive.");
    string_constant_72 = STATIC_STRING("No item named ~a exists.");
    Qname_reference = STATIC_SYMBOL("NAME-REFERENCE",AB_package);
    Qprint_op_constant_long_and_code_constant = 
	    STATIC_SYMBOL("PRINT-OP-CONSTANT-LONG-AND-CODE-CONSTANT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_constant_long_and_code_constant,
	    STATIC_FUNCTION(print_op_constant_long_and_code_constant,NIL,
	    FALSE,4,4));
    Qstack_name_reference_body = STATIC_SYMBOL("STACK-NAME-REFERENCE-BODY",
	    AB_package);
    Qpprint_name_reference_instruction = 
	    STATIC_SYMBOL("PPRINT-NAME-REFERENCE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_name_reference_instruction,
	    STATIC_FUNCTION(pprint_name_reference_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qname_reference,
	    FIX((SI_Long)4L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_constant_long_and_code_constant),
	    FIX((SI_Long)44L),Qstack_name_reference_body,
	    SYMBOL_FUNCTION(Qpprint_name_reference_instruction));
    Qevaluate_role = STATIC_SYMBOL("EVALUATE-ROLE",AB_package);
    Qprint_op_role_long_and_arg_count = 
	    STATIC_SYMBOL("PRINT-OP-ROLE-LONG-AND-ARG-COUNT",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_role_long_and_arg_count,
	    STATIC_FUNCTION(print_op_role_long_and_arg_count,NIL,FALSE,4,4));
    Qstack_evaluate_role_body = STATIC_SYMBOL("STACK-EVALUATE-ROLE-BODY",
	    AB_package);
    Qpprint_evaluate_role_instruction = 
	    STATIC_SYMBOL("PPRINT-EVALUATE-ROLE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_evaluate_role_instruction,
	    STATIC_FUNCTION(pprint_evaluate_role_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qevaluate_role,
	    FIX((SI_Long)5L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_role_long_and_arg_count),
	    FIX((SI_Long)45L),Qstack_evaluate_role_body,
	    SYMBOL_FUNCTION(Qpprint_evaluate_role_instruction));
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qunique_value_of_role_server_function = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-SERVER-FUNCTION",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    array_constant_72 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)34L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)39L,(SI_Long)57344L);
    array_constant_73 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)36L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)39L,(SI_Long)57344L);
    string_constant_73 = 
	    STATIC_STRING("The attribute ~A of ~NF is read-only.");
    string_constant_74 = 
	    STATIC_STRING("The attribute ~A exists in ~NF, but the attribute contained ~\n                           nothing, causing this reference to fail.");
    string_constant_75 = 
	    string_append2(STATIC_STRING("The system defined attribute ~a of ~NF cannot be ~\n                           referenced directly, causing this reference to fail.  ~\n                           However, you c"),
	    STATIC_STRING("an reference the text of this attribute."));
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    string_constant_76 = 
	    STATIC_STRING("The attribute ~a::~a does not exist in ~NF, since ~a is not ~\n                 a defined class.");
    string_constant_77 = 
	    STATIC_STRING("The attribute ~a::~a does not exist in ~NF, since ~NF is not ~\n                 an instance of the class ~a.");
    string_constant_78 = 
	    STATIC_STRING("The attribute ~a exists in ~NF, but is not defined for ~\n                 the superior-class ~a.");
    string_constant_79 = 
	    STATIC_STRING("The attribute ~a does not exist in ~NF~a.");
    string_constant_80 = 
	    STATIC_STRING(", though this attribute is defined for other classes");
    string_constant_81 = STATIC_STRING("");
    string_constant_82 = 
	    STATIC_STRING("The attribute ~NS exists in ~NF, but the attribute contained ~\n               nothing, causing this reference to fail.");
    string_constant_83 = 
	    STATIC_STRING("The attribute ~NS of ~NF contained an item which was ");
    string_constant_84 = STATIC_STRING("~a.");
    string_constant_85 = STATIC_STRING("inactive or disabled.");
    string_constant_86 = 
	    STATIC_STRING("An attempt to reference the ~A::~A of ~NF failed to return a value.");
    string_constant_87 = 
	    STATIC_STRING("An attempt to reference the ~A of ~NF failed to return a value.");
    string_constant_88 = 
	    STATIC_STRING("The attribute ~(~a~) was not found in ~NV.");
    string_constant_89 = STATIC_STRING("The attribute ~NV was not found.");
    array_constant_74 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)26L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)30L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)39L,(SI_Long)57344L);
    array_constant_75 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)25L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)34L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)39L,(SI_Long)57344L);
    if (Allow_inline_evaluate_role_instructions_p == UNBOUND)
	Allow_inline_evaluate_role_instructions_p = Nil;
    Qattribute_frame_or_place_reference = 
	    STATIC_SYMBOL("ATTRIBUTE-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qclass_qualified_name_frame_or_place_reference = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE",
	    AB_package);
    Qelement_frame_or_place_reference = 
	    STATIC_SYMBOL("ELEMENT-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    Qevaluate_role_with_no_domain = 
	    STATIC_SYMBOL("EVALUATE-ROLE-WITH-NO-DOMAIN",AB_package);
    Qprint_op_and_role_no_domain_long = 
	    STATIC_SYMBOL("PRINT-OP-AND-ROLE-NO-DOMAIN-LONG",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_role_no_domain_long,
	    STATIC_FUNCTION(print_op_and_role_no_domain_long,NIL,FALSE,4,4));
    Qstack_evaluate_role_with_no_domain_body = 
	    STATIC_SYMBOL("STACK-EVALUATE-ROLE-WITH-NO-DOMAIN-BODY",
	    AB_package);
    Qpprint_evaluate_role_with_no_domain_instruction = 
	    STATIC_SYMBOL("PPRINT-EVALUATE-ROLE-WITH-NO-DOMAIN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_evaluate_role_with_no_domain_instruction,
	    STATIC_FUNCTION(pprint_evaluate_role_with_no_domain_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qevaluate_role_with_no_domain,
	    FIX((SI_Long)4L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_role_no_domain_long),
	    FIX((SI_Long)46L),Qstack_evaluate_role_with_no_domain_body,
	    SYMBOL_FUNCTION(Qpprint_evaluate_role_with_no_domain_instruction));
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qsimulated_value = STATIC_SYMBOL("SIMULATED-VALUE",AB_package);
    Qparameter_value = STATIC_SYMBOL("PARAMETER-VALUE",AB_package);
    Qstack_parameter_value_body = 
	    STATIC_SYMBOL("STACK-PARAMETER-VALUE-BODY",AB_package);
    Qpprint_parameter_value_instruction = 
	    STATIC_SYMBOL("PPRINT-PARAMETER-VALUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_parameter_value_instruction,
	    STATIC_FUNCTION(pprint_parameter_value_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qparameter_value,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)47L),
	    Qstack_parameter_value_body,
	    SYMBOL_FUNCTION(Qpprint_parameter_value_instruction));
    Qcoerce_integer_to_float = STATIC_SYMBOL("COERCE-INTEGER-TO-FLOAT",
	    AB_package);
    Qstack_coerce_integer_to_float_body = 
	    STATIC_SYMBOL("STACK-COERCE-INTEGER-TO-FLOAT-BODY",AB_package);
    Qpprint_coerce_integer_to_float_instruction = 
	    STATIC_SYMBOL("PPRINT-COERCE-INTEGER-TO-FLOAT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_coerce_integer_to_float_instruction,
	    STATIC_FUNCTION(pprint_coerce_integer_to_float_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qcoerce_integer_to_float,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)48L),
	    Qstack_coerce_integer_to_float_body,
	    SYMBOL_FUNCTION(Qpprint_coerce_integer_to_float_instruction));
    Qcoerce_quantity_to_float = STATIC_SYMBOL("COERCE-QUANTITY-TO-FLOAT",
	    AB_package);
    Qstack_coerce_quantity_to_float_body = 
	    STATIC_SYMBOL("STACK-COERCE-QUANTITY-TO-FLOAT-BODY",AB_package);
    Qpprint_coerce_quantity_to_float_instruction = 
	    STATIC_SYMBOL("PPRINT-COERCE-QUANTITY-TO-FLOAT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_coerce_quantity_to_float_instruction,
	    STATIC_FUNCTION(pprint_coerce_quantity_to_float_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcoerce_quantity_to_float,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)49L),
	    Qstack_coerce_quantity_to_float_body,
	    SYMBOL_FUNCTION(Qpprint_coerce_quantity_to_float_instruction));
    Qstack_not_body = STATIC_SYMBOL("STACK-NOT-BODY",AB_package);
    Qpprint_not_instruction = STATIC_SYMBOL("PPRINT-NOT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_not_instruction,
	    STATIC_FUNCTION(pprint_not_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qnot,FIX((SI_Long)1L),
	    FIX((SI_Long)1L),Nil,FIX((SI_Long)50L),Qstack_not_body,
	    SYMBOL_FUNCTION(Qpprint_not_instruction));
    string_constant_90 = 
	    STATIC_STRING("Error in evaluator.  The out of line evaluator #~a did not exist.  Please ~\n   report this G2 internal software error to Gensym Software Support.");
    Qfuncall_evaluator = STATIC_SYMBOL("FUNCALL-EVALUATOR",AB_package);
    Qprint_funcall_evaluator = STATIC_SYMBOL("PRINT-FUNCALL-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_funcall_evaluator,
	    STATIC_FUNCTION(print_funcall_evaluator,NIL,FALSE,4,4));
    Qstack_funcall_evaluator_body = 
	    STATIC_SYMBOL("STACK-FUNCALL-EVALUATOR-BODY",AB_package);
    Qpprint_funcall_evaluator = STATIC_SYMBOL("PPRINT-FUNCALL-EVALUATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_funcall_evaluator,
	    STATIC_FUNCTION(pprint_funcall_evaluator,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qfuncall_evaluator,
	    FIX((SI_Long)2L),Nil,SYMBOL_FUNCTION(Qprint_funcall_evaluator),
	    FIX((SI_Long)51L),Qstack_funcall_evaluator_body,
	    SYMBOL_FUNCTION(Qpprint_funcall_evaluator));
    Qfuncall_instruction = STATIC_SYMBOL("FUNCALL-INSTRUCTION",AB_package);
    Qprint_funcalled_instruction = 
	    STATIC_SYMBOL("PRINT-FUNCALLED-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_funcalled_instruction,
	    STATIC_FUNCTION(print_funcalled_instruction,NIL,FALSE,4,4));
    Qstack_funcall_instruction_body = 
	    STATIC_SYMBOL("STACK-FUNCALL-INSTRUCTION-BODY",AB_package);
    Qpprint_funcalled_instruction = 
	    STATIC_SYMBOL("PPRINT-FUNCALLED-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_funcalled_instruction,
	    STATIC_FUNCTION(pprint_funcalled_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qfuncall_instruction,
	    FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qprint_funcalled_instruction),
	    FIX((SI_Long)52L),Qstack_funcall_instruction_body,
	    SYMBOL_FUNCTION(Qpprint_funcalled_instruction));
    Qfuncall_instruction_n = STATIC_SYMBOL("FUNCALL-INSTRUCTION-N",AB_package);
    Qprint_funcalled_instruction_n = 
	    STATIC_SYMBOL("PRINT-FUNCALLED-INSTRUCTION-N",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_funcalled_instruction_n,
	    STATIC_FUNCTION(print_funcalled_instruction_n,NIL,FALSE,4,4));
    Qstack_funcall_instruction_n_body = 
	    STATIC_SYMBOL("STACK-FUNCALL-INSTRUCTION-N-BODY",AB_package);
    Qpprint_funcalled_instruction_n = 
	    STATIC_SYMBOL("PPRINT-FUNCALLED-INSTRUCTION-N",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_funcalled_instruction_n,
	    STATIC_FUNCTION(pprint_funcalled_instruction_n,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qfuncall_instruction_n,
	    FIX((SI_Long)5L),Nil,
	    SYMBOL_FUNCTION(Qprint_funcalled_instruction_n),
	    FIX((SI_Long)139L),Qstack_funcall_instruction_n_body,
	    SYMBOL_FUNCTION(Qpprint_funcalled_instruction_n));
    Qfuncalled_instruction_description = 
	    STATIC_SYMBOL("FUNCALLED-INSTRUCTION-DESCRIPTION",AB_package);
    string_constant_91 = STATIC_STRING("funcall-instruction emitter");
    string_constant_92 = 
	    STATIC_STRING("No instruction description for funcalled-instruction ~a.");
    Qstack_attribute_frame_or_place_reference_body = 
	    STATIC_SYMBOL("STACK-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE-BODY",
	    AB_package);
    Qpprint_attribute_frame_or_place_reference_instruction = 
	    STATIC_SYMBOL("PPRINT-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_attribute_frame_or_place_reference_instruction,
	    STATIC_FUNCTION(pprint_attribute_frame_or_place_reference_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qattribute_frame_or_place_reference,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)53L),
	    Qstack_attribute_frame_or_place_reference_body,
	    SYMBOL_FUNCTION(Qpprint_attribute_frame_or_place_reference_instruction));
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    Qaliased_attribute = STATIC_SYMBOL("ALIASED-ATTRIBUTE",AB_package);
    Qstack_attribute_value_body = 
	    STATIC_SYMBOL("STACK-ATTRIBUTE-VALUE-BODY",AB_package);
    Qpprint_attribute_value_instruction = 
	    STATIC_SYMBOL("PPRINT-ATTRIBUTE-VALUE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_attribute_value_instruction,
	    STATIC_FUNCTION(pprint_attribute_value_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qattribute_value,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_constant_long),FIX((SI_Long)54L),
	    Qstack_attribute_value_body,
	    SYMBOL_FUNCTION(Qpprint_attribute_value_instruction));
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreturn_values = STATIC_SYMBOL("RETURN-VALUES",AB_package);
    Qstack_return_values_body = STATIC_SYMBOL("STACK-RETURN-VALUES-BODY",
	    AB_package);
    Qpprint_return_values_instruction = 
	    STATIC_SYMBOL("PPRINT-RETURN-VALUES-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_return_values_instruction,
	    STATIC_FUNCTION(pprint_return_values_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qreturn_values,
	    FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)55L),
	    Qstack_return_values_body,
	    SYMBOL_FUNCTION(Qpprint_return_values_instruction));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    string_constant_93 = 
	    STATIC_STRING("At most 255 values can be returned, ~a in this statement.");
    string_constant_94 = 
	    STATIC_STRING("Procedure ~NF is requesting ~a values and ~NF can return only ~a.");
    array_constant_76 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)23L,(SI_Long)57344L);
    array_constant_77 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)34L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)39L,(SI_Long)57344L);
    array_constant_78 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)17L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)23L,(SI_Long)57344L);
    array_constant_79 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)15L,(SI_Long)57344L);
    array_constant_80 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)7L,(SI_Long)57344L);
    Qsignal_error = STATIC_SYMBOL("SIGNAL-ERROR",AB_package);
    Qstack_signal_error_body = STATIC_SYMBOL("STACK-SIGNAL-ERROR-BODY",
	    AB_package);
    Qpprint_signal_error_instruction = 
	    STATIC_SYMBOL("PPRINT-SIGNAL-ERROR-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_signal_error_instruction,
	    STATIC_FUNCTION(pprint_signal_error_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qsignal_error,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)56L),
	    Qstack_signal_error_body,
	    SYMBOL_FUNCTION(Qpprint_signal_error_instruction));
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qprint_call_stack_instruction = 
	    STATIC_SYMBOL("PRINT-CALL-STACK-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_call_stack_instruction,
	    STATIC_FUNCTION(print_call_stack_instruction,NIL,FALSE,4,4));
    Qstack_call_body = STATIC_SYMBOL("STACK-CALL-BODY",AB_package);
    Qpprint_call_instruction = STATIC_SYMBOL("PPRINT-CALL-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_call_instruction,
	    STATIC_FUNCTION(pprint_call_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcall,FIX((SI_Long)3L),
	    Nil,SYMBOL_FUNCTION(Qprint_call_stack_instruction),
	    FIX((SI_Long)57L),Qstack_call_body,
	    SYMBOL_FUNCTION(Qpprint_call_instruction));
    Kawaiting_lock = STATIC_SYMBOL("AWAITING-LOCK",Pkeyword);
    array_constant_81 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)23L,(SI_Long)57344L);
    array_constant_82 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)7L,(SI_Long)57344L);
    Qdependent_call = STATIC_SYMBOL("DEPENDENT-CALL",AB_package);
    Qstack_dependent_call_body = STATIC_SYMBOL("STACK-DEPENDENT-CALL-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qdependent_call,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_call_stack_instruction),
	    FIX((SI_Long)81L),Qstack_dependent_call_body,
	    SYMBOL_FUNCTION(Qpprint_call_instruction));
    string_constant_95 = 
	    string_append2(STATIC_STRING("Attempted to call a remote procedure across ~NF, but could not because ~\n   it does not have either the G2-TO-G2-DATA-INTERFACE nor the ~\n   GSI-INTERFACE capability, and so c"),
	    STATIC_STRING("annot be a pathway for ~\n   a remote procedure call."));
    Qcall_rpc = STATIC_SYMBOL("CALL-RPC",AB_package);
    Qstack_call_rpc_body = STATIC_SYMBOL("STACK-CALL-RPC-BODY",AB_package);
    Qpprint_call_rpc_instruction = 
	    STATIC_SYMBOL("PPRINT-CALL-RPC-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_call_rpc_instruction,
	    STATIC_FUNCTION(pprint_call_rpc_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcall_rpc,
	    FIX((SI_Long)3L),Nil,Nil,FIX((SI_Long)58L),
	    Qstack_call_rpc_body,
	    SYMBOL_FUNCTION(Qpprint_call_rpc_instruction));
    string_constant_96 = STATIC_STRING("Calling remote procedure ~NF(");
    string_constant_97 = STATIC_STRING(") across ~NF.");
    Qpush_returned_values = STATIC_SYMBOL("PUSH-RETURNED-VALUES",AB_package);
    Qstack_push_returned_values_body = 
	    STATIC_SYMBOL("STACK-PUSH-RETURNED-VALUES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_returned_values,
	    FIX((SI_Long)3L),Nil,Nil,FIX((SI_Long)59L),
	    Qstack_push_returned_values_body,Nil);
    Qpush_returned_values_long = STATIC_SYMBOL("PUSH-RETURNED-VALUES-LONG",
	    AB_package);
    Qstack_push_returned_values_long_body = 
	    STATIC_SYMBOL("STACK-PUSH-RETURNED-VALUES-LONG-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_returned_values_long,
	    FIX((SI_Long)5L),Nil,Nil,FIX((SI_Long)141L),
	    Qstack_push_returned_values_long_body,Nil);
    Qjump = STATIC_SYMBOL("JUMP",AB_package);
    Qprint_stack_jump = STATIC_SYMBOL("PRINT-STACK-JUMP",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_stack_jump,STATIC_FUNCTION(print_stack_jump,
	    NIL,FALSE,4,4));
    Qstack_jump_body = STATIC_SYMBOL("STACK-JUMP-BODY",AB_package);
    make_and_register_stack_instruction_description(Qjump,FIX((SI_Long)5L),
	    Nil,SYMBOL_FUNCTION(Qprint_stack_jump),FIX((SI_Long)60L),
	    Qstack_jump_body,Nil);
    bc_jump_resolver_1 = STATIC_FUNCTION(bc_jump_resolver,NIL,FALSE,4,4);
    mutate_global_property(Qjump,bc_jump_resolver_1,Qbyte_code_resolver);
    Qabort_called_code_bodies = STATIC_SYMBOL("ABORT-CALLED-CODE-BODIES",
	    AB_package);
    Qstack_abort_called_code_bodies_body = 
	    STATIC_SYMBOL("STACK-ABORT-CALLED-CODE-BODIES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qabort_called_code_bodies,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)61L),
	    Qstack_abort_called_code_bodies_body,Nil);
    Qallow_other_processing = STATIC_SYMBOL("ALLOW-OTHER-PROCESSING",
	    AB_package);
    Qstack_allow_other_processing_body = 
	    STATIC_SYMBOL("STACK-ALLOW-OTHER-PROCESSING-BODY",AB_package);
    Qpprint_allow_other_processing_instruction = 
	    STATIC_SYMBOL("PPRINT-ALLOW-OTHER-PROCESSING-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_allow_other_processing_instruction,
	    STATIC_FUNCTION(pprint_allow_other_processing_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qallow_other_processing,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)62L),
	    Qstack_allow_other_processing_body,
	    SYMBOL_FUNCTION(Qpprint_allow_other_processing_instruction));
    Qopen_role_iteration_no_domain = 
	    STATIC_SYMBOL("OPEN-ROLE-ITERATION-NO-DOMAIN",AB_package);
    Qprint_open_role_no_domain_iteration = 
	    STATIC_SYMBOL("PRINT-OPEN-ROLE-NO-DOMAIN-ITERATION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_open_role_no_domain_iteration,
	    STATIC_FUNCTION(print_open_role_no_domain_iteration,NIL,FALSE,
	    4,4));
    Qstack_open_role_iteration_no_domain_body = 
	    STATIC_SYMBOL("STACK-OPEN-ROLE-ITERATION-NO-DOMAIN-BODY",
	    AB_package);
    Qpprint_open_role_iteration_no_domain_instruction = 
	    STATIC_SYMBOL("PPRINT-OPEN-ROLE-ITERATION-NO-DOMAIN-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_open_role_iteration_no_domain_instruction,
	    STATIC_FUNCTION(pprint_open_role_iteration_no_domain_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qopen_role_iteration_no_domain,
	    FIX((SI_Long)5L),Nil,
	    SYMBOL_FUNCTION(Qprint_open_role_no_domain_iteration),
	    FIX((SI_Long)63L),Qstack_open_role_iteration_no_domain_body,
	    SYMBOL_FUNCTION(Qpprint_open_role_iteration_no_domain_instruction));
    bc_open_role_iteration_no_domain_resolver_1 = 
	    STATIC_FUNCTION(bc_open_role_iteration_no_domain_resolver,NIL,
	    FALSE,4,4);
    mutate_global_property(Qopen_role_iteration_no_domain,
	    bc_open_role_iteration_no_domain_resolver_1,Qbyte_code_resolver);
    Qopen_role_iteration = STATIC_SYMBOL("OPEN-ROLE-ITERATION",AB_package);
    Qprint_open_role_iteration = STATIC_SYMBOL("PRINT-OPEN-ROLE-ITERATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_open_role_iteration,
	    STATIC_FUNCTION(print_open_role_iteration,NIL,FALSE,4,4));
    Qstack_open_role_iteration_body = 
	    STATIC_SYMBOL("STACK-OPEN-ROLE-ITERATION-BODY",AB_package);
    Qpprint_open_role_iteration_instruction = 
	    STATIC_SYMBOL("PPRINT-OPEN-ROLE-ITERATION-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_open_role_iteration_instruction,
	    STATIC_FUNCTION(pprint_open_role_iteration_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qopen_role_iteration,
	    FIX((SI_Long)6L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_open_role_iteration),FIX((SI_Long)64L),
	    Qstack_open_role_iteration_body,
	    SYMBOL_FUNCTION(Qpprint_open_role_iteration_instruction));
    string_constant_98 = STATIC_STRING("open role iteration emitter");
    string_constant_99 = 
	    STATIC_STRING("Iterations can only handle zero or one domain roles, not ~a domains.");
    bc_open_role_iteration_resolver_1 = 
	    STATIC_FUNCTION(bc_open_role_iteration_resolver,NIL,FALSE,4,4);
    mutate_global_property(Qopen_role_iteration,
	    bc_open_role_iteration_resolver_1,Qbyte_code_resolver);
    Qserve_next_iteration_value = 
	    STATIC_SYMBOL("SERVE-NEXT-ITERATION-VALUE",AB_package);
    Qprint_serve_next_iteration_value = 
	    STATIC_SYMBOL("PRINT-SERVE-NEXT-ITERATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_serve_next_iteration_value,
	    STATIC_FUNCTION(print_serve_next_iteration_value,NIL,FALSE,4,4));
    Qstack_serve_next_iteration_value_body = 
	    STATIC_SYMBOL("STACK-SERVE-NEXT-ITERATION-VALUE-BODY",AB_package);
    Qpprint_serve_next_iteration_value_instruction = 
	    STATIC_SYMBOL("PPRINT-SERVE-NEXT-ITERATION-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_serve_next_iteration_value_instruction,
	    STATIC_FUNCTION(pprint_serve_next_iteration_value_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qserve_next_iteration_value,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_serve_next_iteration_value),
	    FIX((SI_Long)65L),Qstack_serve_next_iteration_value_body,
	    SYMBOL_FUNCTION(Qpprint_serve_next_iteration_value_instruction));
    bc_serve_next_iteration_value_resolver_1 = 
	    STATIC_FUNCTION(bc_serve_next_iteration_value_resolver,NIL,
	    FALSE,4,4);
    mutate_global_property(Qserve_next_iteration_value,
	    bc_serve_next_iteration_value_resolver_1,Qbyte_code_resolver);
    Qclose_iteration = STATIC_SYMBOL("CLOSE-ITERATION",AB_package);
    Qstack_close_iteration_body = 
	    STATIC_SYMBOL("STACK-CLOSE-ITERATION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qclose_iteration,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)66L),
	    Qstack_close_iteration_body,Nil);
    Qclose_code_body = STATIC_SYMBOL("CLOSE-CODE-BODY",AB_package);
    Qstack_close_code_body_body = 
	    STATIC_SYMBOL("STACK-CLOSE-CODE-BODY-BODY",AB_package);
    make_and_register_stack_instruction_description(Qclose_code_body,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)67L),
	    Qstack_close_code_body_body,Nil);
    Qcall_code_body = STATIC_SYMBOL("CALL-CODE-BODY",AB_package);
    Qprint_stack_call_code_body = 
	    STATIC_SYMBOL("PRINT-STACK-CALL-CODE-BODY",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_stack_call_code_body,
	    STATIC_FUNCTION(print_stack_call_code_body,NIL,FALSE,4,4));
    Qstack_call_code_body_body = STATIC_SYMBOL("STACK-CALL-CODE-BODY-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qcall_code_body,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_stack_call_code_body),FIX((SI_Long)68L),
	    Qstack_call_code_body_body,Nil);
    Qcall_scheduled_code_body = STATIC_SYMBOL("CALL-SCHEDULED-CODE-BODY",
	    AB_package);
    Qstack_call_scheduled_code_body_body = 
	    STATIC_SYMBOL("STACK-CALL-SCHEDULED-CODE-BODY-BODY",AB_package);
    make_and_register_stack_instruction_description(Qcall_scheduled_code_body,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_stack_call_code_body),FIX((SI_Long)69L),
	    Qstack_call_scheduled_code_body_body,Nil);
    Qwait_for_called_code_bodies = 
	    STATIC_SYMBOL("WAIT-FOR-CALLED-CODE-BODIES",AB_package);
    Qstack_wait_for_called_code_bodies_body = 
	    STATIC_SYMBOL("STACK-WAIT-FOR-CALLED-CODE-BODIES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qwait_for_called_code_bodies,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)70L),
	    Qstack_wait_for_called_code_bodies_body,Nil);
    Qtype_check_item = STATIC_SYMBOL("TYPE-CHECK-ITEM",AB_package);
    Qstack_type_check_item_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-ITEM-BODY",AB_package);
    Qpprint_type_check_item_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-ITEM-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_item_instruction,
	    STATIC_FUNCTION(pprint_type_check_item_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_item,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)71L),
	    Qstack_type_check_item_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_item_instruction));
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qstack_pause_body = STATIC_SYMBOL("STACK-PAUSE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpause,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)72L),Qstack_pause_body,Nil);
    Qpause_if_called_code_bodies = 
	    STATIC_SYMBOL("PAUSE-IF-CALLED-CODE-BODIES",AB_package);
    Qstack_pause_if_called_code_bodies_body = 
	    STATIC_SYMBOL("STACK-PAUSE-IF-CALLED-CODE-BODIES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpause_if_called_code_bodies,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)73L),
	    Qstack_pause_if_called_code_bodies_body,Nil);
    Qvariable_value_or_unknown = STATIC_SYMBOL("VARIABLE-VALUE-OR-UNKNOWN",
	    AB_package);
    Qstack_variable_value_or_unknown_body = 
	    STATIC_SYMBOL("STACK-VARIABLE-VALUE-OR-UNKNOWN-BODY",AB_package);
    Qpprint_fetch_value_of = STATIC_SYMBOL("PPRINT-FETCH-VALUE-OF",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_fetch_value_of,
	    STATIC_FUNCTION(pprint_fetch_value_of,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qvariable_value_or_unknown,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)74L),
	    Qstack_variable_value_or_unknown_body,
	    SYMBOL_FUNCTION(Qpprint_fetch_value_of));
    string_constant_100 = 
	    STATIC_STRING("Attempted to get a value from ~NF, but it was not a ~a.");
    string_constant_101 = 
	    STATIC_STRING("Expected some kind of value, but received ~NV.");
    Qcoerce_to_datum_or_unknown = 
	    STATIC_SYMBOL("COERCE-TO-DATUM-OR-UNKNOWN",AB_package);
    Qstack_coerce_to_datum_or_unknown_body = 
	    STATIC_SYMBOL("STACK-COERCE-TO-DATUM-OR-UNKNOWN-BODY",AB_package);
    make_and_register_stack_instruction_description(Qcoerce_to_datum_or_unknown,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)75L),
	    Qstack_coerce_to_datum_or_unknown_body,
	    SYMBOL_FUNCTION(Qpprint_fetch_value_of));
    Qcoerce_to_datum = STATIC_SYMBOL("COERCE-TO-DATUM",AB_package);
    Qstack_coerce_to_datum_body = 
	    STATIC_SYMBOL("STACK-COERCE-TO-DATUM-BODY",AB_package);
    make_and_register_stack_instruction_description(Qcoerce_to_datum,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)76L),
	    Qstack_coerce_to_datum_body,
	    SYMBOL_FUNCTION(Qpprint_fetch_value_of));
    Qpush_copy_of_top_of_stack = STATIC_SYMBOL("PUSH-COPY-OF-TOP-OF-STACK",
	    AB_package);
    Qstack_push_copy_of_top_of_stack_body = 
	    STATIC_SYMBOL("STACK-PUSH-COPY-OF-TOP-OF-STACK-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_copy_of_top_of_stack,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)77L),
	    Qstack_push_copy_of_top_of_stack_body,Nil);
    Qpop_copy_down_the_stack = STATIC_SYMBOL("POP-COPY-DOWN-THE-STACK",
	    AB_package);
    Qstack_pop_copy_down_the_stack_body = 
	    STATIC_SYMBOL("STACK-POP-COPY-DOWN-THE-STACK-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_copy_down_the_stack,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)78L),
	    Qstack_pop_copy_down_the_stack_body,Nil);
    Qfuzzy_and = STATIC_SYMBOL("FUZZY-AND",AB_package);
    Qstack_fuzzy_and_body = STATIC_SYMBOL("STACK-FUZZY-AND-BODY",AB_package);
    Qpprint_and_instruction = STATIC_SYMBOL("PPRINT-AND-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_and_instruction,
	    STATIC_FUNCTION(pprint_and_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qfuzzy_and,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)79L),
	    Qstack_fuzzy_and_body,SYMBOL_FUNCTION(Qpprint_and_instruction));
    Qfuzzy_or = STATIC_SYMBOL("FUZZY-OR",AB_package);
    Qstack_fuzzy_or_body = STATIC_SYMBOL("STACK-FUZZY-OR-BODY",AB_package);
    Qpprint_or_instruction = STATIC_SYMBOL("PPRINT-OR-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_or_instruction,
	    STATIC_FUNCTION(pprint_or_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qfuzzy_or,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)80L),
	    Qstack_fuzzy_or_body,SYMBOL_FUNCTION(Qpprint_or_instruction));
    Qpush_from_allow_data_seeking = 
	    STATIC_SYMBOL("PUSH-FROM-ALLOW-DATA-SEEKING",AB_package);
    Qstack_push_from_allow_data_seeking_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-ALLOW-DATA-SEEKING-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_from_allow_data_seeking,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)82L),
	    Qstack_push_from_allow_data_seeking_body,Nil);
    Qpop_into_allow_data_seeking = 
	    STATIC_SYMBOL("POP-INTO-ALLOW-DATA-SEEKING",AB_package);
    Qstack_pop_into_allow_data_seeking_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-ALLOW-DATA-SEEKING-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_into_allow_data_seeking,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)83L),
	    Qstack_pop_into_allow_data_seeking_body,Nil);
    Qopen_wake_up_collection = STATIC_SYMBOL("OPEN-WAKE-UP-COLLECTION",
	    AB_package);
    Qstack_open_wake_up_collection_body = 
	    STATIC_SYMBOL("STACK-OPEN-WAKE-UP-COLLECTION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qopen_wake_up_collection,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)84L),
	    Qstack_open_wake_up_collection_body,Nil);
    string_constant_102 = 
	    STATIC_STRING("An unknown type of current computation instance was encountered in ~\n   enable-wake-up-collection.  Please report this stack eval bug to ~\n   Gensym software support.");
    string_constant_103 = 
	    STATIC_STRING("An unknown type of current computation instance was encountered in ~\n       enable-wake-up-collection.  Please report this stack eval bug to ~\n       Gensym software support.");
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_inference_background_collection_g2_struct 
	    = STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qset_wake_ups = STATIC_SYMBOL("SET-WAKE-UPS",AB_package);
    Qstack_set_wake_ups_body = STATIC_SYMBOL("STACK-SET-WAKE-UPS-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qset_wake_ups,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)85L),
	    Qstack_set_wake_ups_body,Nil);
    Qclear_wake_ups = STATIC_SYMBOL("CLEAR-WAKE-UPS",AB_package);
    Qstack_clear_wake_ups_body = STATIC_SYMBOL("STACK-CLEAR-WAKE-UPS-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qclear_wake_ups,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)86L),
	    Qstack_clear_wake_ups_body,Nil);
    Qclose_wake_up_collection = STATIC_SYMBOL("CLOSE-WAKE-UP-COLLECTION",
	    AB_package);
    Qstack_close_wake_up_collection_body = 
	    STATIC_SYMBOL("STACK-CLOSE-WAKE-UP-COLLECTION-BODY",AB_package);
    make_and_register_stack_instruction_description(Qclose_wake_up_collection,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)87L),
	    Qstack_close_wake_up_collection_body,Nil);
    string_constant_104 = 
	    string_append2(STATIC_STRING("An unknown type of current computation instance was encountered in ~\n            clean-up-wake-ups-state-if-any.  Please report this stack eval ~\n            bug to Gensym sof"),
	    STATIC_STRING("tware support."));
    Qwait_for_interval = STATIC_SYMBOL("WAIT-FOR-INTERVAL",AB_package);
    Qstack_wait_for_interval_body = 
	    STATIC_SYMBOL("STACK-WAIT-FOR-INTERVAL-BODY",AB_package);
    Qpprint_wait_for_interval_instruction = 
	    STATIC_SYMBOL("PPRINT-WAIT-FOR-INTERVAL-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_wait_for_interval_instruction,
	    STATIC_FUNCTION(pprint_wait_for_interval_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qwait_for_interval,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)88L),
	    Qstack_wait_for_interval_body,
	    SYMBOL_FUNCTION(Qpprint_wait_for_interval_instruction));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qwake_up_code_body_invocation = 
	    STATIC_SYMBOL("WAKE-UP-CODE-BODY-INVOCATION",AB_package);
    Qexecute_computation_instance = 
	    STATIC_SYMBOL("EXECUTE-COMPUTATION-INSTANCE",AB_package);
    Qpop_into_final_evaluation_attempt = 
	    STATIC_SYMBOL("POP-INTO-FINAL-EVALUATION-ATTEMPT",AB_package);
    Qstack_pop_into_final_evaluation_attempt_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-FINAL-EVALUATION-ATTEMPT-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpop_into_final_evaluation_attempt,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)89L),
	    Qstack_pop_into_final_evaluation_attempt_body,Nil);
    Qpush_wake_ups_count = STATIC_SYMBOL("PUSH-WAKE-UPS-COUNT",AB_package);
    Qstack_push_wake_ups_count_body = 
	    STATIC_SYMBOL("STACK-PUSH-WAKE-UPS-COUNT-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_wake_ups_count,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)90L),
	    Qstack_push_wake_ups_count_body,Nil);
    Qtype_check = STATIC_SYMBOL("TYPE-CHECK",AB_package);
    Qprint_op_and_type_long = STATIC_SYMBOL("PRINT-OP-AND-TYPE-LONG",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_type_long,
	    STATIC_FUNCTION(print_op_and_type_long,NIL,FALSE,4,4));
    Qstack_type_check_body = STATIC_SYMBOL("STACK-TYPE-CHECK-BODY",AB_package);
    Qpprint_type_check_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_instruction,
	    STATIC_FUNCTION(pprint_type_check_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_type_long),FIX((SI_Long)91L),
	    Qstack_type_check_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_instruction));
    Qpush_nones = STATIC_SYMBOL("PUSH-NONES",AB_package);
    Qstack_push_nones_body = STATIC_SYMBOL("STACK-PUSH-NONES-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_nones,
	    FIX((SI_Long)2L),FIX((SI_Long)0L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),FIX((SI_Long)92L),
	    Qstack_push_nones_body,Nil);
    Qpush_value_or_none_from_surrounding_local_var = 
	    STATIC_SYMBOL("PUSH-VALUE-OR-NONE-FROM-SURROUNDING-LOCAL-VAR",
	    AB_package);
    Qstack_push_value_or_none_from_surrounding_local_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-VALUE-OR-NONE-FROM-SURROUNDING-LOCAL-VAR-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_value_or_none_from_surrounding_local_var,
	    FIX((SI_Long)4L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var_and_typecode),
	    FIX((SI_Long)93L),
	    Qstack_push_value_or_none_from_surrounding_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_surrounding_local_var_instruction));
    string_constant_105 = 
	    STATIC_STRING("Attempted to call ~NF as a function, but it is an instance of the class ~(~a~).");
    Qcall_procedure = STATIC_SYMBOL("CALL-PROCEDURE",AB_package);
    Qstack_call_procedure_body = STATIC_SYMBOL("STACK-CALL-PROCEDURE-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qcall_procedure,
	    FIX((SI_Long)2L),Nil,Nil,FIX((SI_Long)143L),
	    Qstack_call_procedure_body,Nil);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qprint_call_function_stack_instruction = 
	    STATIC_SYMBOL("PRINT-CALL-FUNCTION-STACK-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_call_function_stack_instruction,
	    STATIC_FUNCTION(print_call_function_stack_instruction,NIL,
	    FALSE,4,4));
    Qstack_call_function_body = STATIC_SYMBOL("STACK-CALL-FUNCTION-BODY",
	    AB_package);
    Qpprint_call_function_instruction = 
	    STATIC_SYMBOL("PPRINT-CALL-FUNCTION-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_call_function_instruction,
	    STATIC_FUNCTION(pprint_call_function_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcall_function,
	    FIX((SI_Long)2L),Nil,
	    SYMBOL_FUNCTION(Qprint_call_function_stack_instruction),
	    FIX((SI_Long)94L),Qstack_call_function_body,
	    SYMBOL_FUNCTION(Qpprint_call_function_instruction));
    string_constant_106 = 
	    STATIC_STRING("Can\'t call the function ~NF because its status is not OK.");
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    string_constant_107 = 
	    string_append2(STATIC_STRING("Argument number ~a to the foreign function ~NF was the ~\n               value ~NE.  Foreign functions can only accept arguments ~\n               of the types quantity, symbol,"),
	    STATIC_STRING(" and text."));
    string_constant_108 = 
	    STATIC_STRING("Calling ~NF with ~a arguments, it requires 1.");
    string_constant_109 = 
	    STATIC_STRING("The tabular function ~NF, can not take the value ~NV.");
    string_constant_110 = 
	    STATIC_STRING("The tabular function ~NF, given the value ~NV, did not return a value.");
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    string_constant_111 = STATIC_STRING("~A ~NF ~A, ~A.  ~A ~A.  ~A");
    string_constant_112 = STATIC_STRING("The tabular function");
    string_constant_113 = 
	    STATIC_STRING("returned a datum which is not a number");
    string_constant_114 = STATIC_STRING("symbol, truth value, or text");
    string_constant_115 = 
	    STATIC_STRING("This is an internal G2 error caused by");
    string_constant_116 = 
	    STATIC_STRING("some unusual use of tabular functions");
    string_constant_117 = 
	    STATIC_STRING("Please report this bug to Gensym software support.");
    string_constant_118 = 
	    STATIC_STRING("Unknown thing ~a given as argument to tabular function.");
    string_constant_191 = 
	    STATIC_STRING("There may be an infinite recursion involving this function");
    Recursion_warning_explanation_1 = string_constant_191;
    string_constant_192 = 
	    STATIC_STRING("or the recursion limit attribute of the inference-engine-parameters system table should be increased for this knowledge base.");
    Recursion_warning_explanation_2 = string_constant_192;
    string_constant_119 = 
	    STATIC_STRING("The recursion limit ~a has been exceeded while attempting to call ~NF.  ~a, ~a");
    string_constant_120 = 
	    STATIC_STRING("The stack has overflowed while attempting to call the function ~NF.  ~\n         There are currently ~a function calls on the stack.  ~a.");
    string_constant_121 = 
	    STATIC_STRING("The function ~NF received ~a arguments, but it requires ~a.");
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    string_constant_122 = STATIC_STRING("Calling function ~NF(");
    array_constant_83 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)7L,(SI_Long)57344L);
    Qreturn_from_function = STATIC_SYMBOL("RETURN-FROM-FUNCTION",AB_package);
    Qstack_return_from_function_body = 
	    STATIC_SYMBOL("STACK-RETURN-FROM-FUNCTION-BODY",AB_package);
    Qpprint_return_from_function_instruction = 
	    STATIC_SYMBOL("PPRINT-RETURN-FROM-FUNCTION-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_return_from_function_instruction,
	    STATIC_FUNCTION(pprint_return_from_function_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qreturn_from_function,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)95L),
	    Qstack_return_from_function_body,
	    SYMBOL_FUNCTION(Qpprint_return_from_function_instruction));
    array_constant_84 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)15L,(SI_Long)57344L);
    array_constant_85 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)15L,(SI_Long)57344L);
    string_constant_123 = STATIC_STRING(" from function ~NF.");
    Qnone_test = STATIC_SYMBOL("NONE-TEST",AB_package);
    Qstack_none_test_body = STATIC_SYMBOL("STACK-NONE-TEST-BODY",AB_package);
    make_and_register_stack_instruction_description(Qnone_test,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)96L),
	    Qstack_none_test_body,Nil);
    Qsystem_call = STATIC_SYMBOL("SYSTEM-CALL",AB_package);
    Qstack_system_call_body = STATIC_SYMBOL("STACK-SYSTEM-CALL-BODY",
	    AB_package);
    Qpprint_system_procedure_instruction = 
	    STATIC_SYMBOL("PPRINT-SYSTEM-PROCEDURE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_system_procedure_instruction,
	    STATIC_FUNCTION(pprint_system_procedure_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qsystem_call,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_call_stack_instruction),
	    FIX((SI_Long)97L),Qstack_system_call_body,
	    SYMBOL_FUNCTION(Qpprint_system_procedure_instruction));
    if (Trace_system_calls_p == UNBOUND)
	Trace_system_calls_p = Nil;
    string_constant_124 = STATIC_STRING(" ~NF");
    string_constant_125 = STATIC_STRING(" ~NV");
    string_constant_126 = STATIC_STRING("calling ~(~a~):");
    string_constant_127 = STATIC_STRING("returning:");
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    string_constant_128 = 
	    STATIC_STRING("The number of arguments to the System Procedure ~a is ~\n             beyond the maximum allowed.  Please report this error to ~\n             Gensym Software Support.");
    string_constant_129 = 
	    STATIC_STRING("Attempting to make a system call to ~A, which is not defined.  ~\n             Please report this G2 internal error to Gensym software support.");
    string_constant_130 = STATIC_STRING("System call tracing limit reached.");
    string_constant_131 = 
	    STATIC_STRING("Missing return value ~a in System Procedure.  Please ~\n                    call Gensym Software Support!");
    Qstack = STATIC_SYMBOL("STACK",AB_package);
    Qcreate_connection = STATIC_SYMBOL("CREATE-CONNECTION",AB_package);
    Qstack_create_connection_body = 
	    STATIC_SYMBOL("STACK-CREATE-CONNECTION-BODY",AB_package);
    Qpprint_create_connection_instruction = 
	    STATIC_SYMBOL("PPRINT-CREATE-CONNECTION-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_create_connection_instruction,
	    STATIC_FUNCTION(pprint_create_connection_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qcreate_connection,
	    FIX((SI_Long)1L),FIX((SI_Long)14L),Nil,FIX((SI_Long)98L),
	    Qstack_create_connection_body,
	    SYMBOL_FUNCTION(Qpprint_create_connection_instruction));
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qdiagonal,Qorthogonal);
    Valid_styles = list_constant_35;
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qinput,Qoutput);
    Valid_directions = list_constant_36;
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)4L,Qleft,Qtop,Qright,Qbottom);
    Valid_sides = list_constant_37;
    if (Disable_stack_error == UNBOUND)
	Disable_stack_error = Nil;
    if (Permit_transfer_of_permanent_items_p == UNBOUND)
	Permit_transfer_of_permanent_items_p = Nil;
    string_constant_132 = STATIC_STRING("~a is not a defined class.");
    Qnot_user_instantiable = STATIC_SYMBOL("NOT-USER-INSTANTIABLE",AB_package);
    string_constant_133 = 
	    STATIC_STRING("In a CREATE statement, attempted to make an instance of ~a, ~\n         but you cannot instantiate a class which is not a final ~\n         menu choice.");
    string_constant_134 = 
	    STATIC_STRING("When creating transient instances of the class ~a, you should not ~\n         use the additional CONNECTED grammar.");
    string_constant_135 = 
	    STATIC_STRING("The connection style specifier ~\n         in a CREATE action evaluated to ~s ~\n         which is not one of the valid styles diagonal, or orthogonal.");
    string_constant_136 = 
	    STATIC_STRING("The connection direction specifier in a CREATE action evaluated to ~s ~\n         which is not one of the valid directions input, or output");
    float_constant = STATIC_FLOAT(0.5);
    string_constant_137 = 
	    STATIC_STRING("A CREATE action could not make a connection to the ~\n       object ~NF because this object has no-manual-connections capability");
    string_constant_138 = 
	    STATIC_STRING("A connection side specifier in a CREATE action evaluated to ~s ~\n      which is not one of the valid sides left, right, top, or bottom");
    string_constant_139 = 
	    STATIC_STRING("A connection end position specifier in a CREATE action evaluated to ~s ~\n       which is not a non-negative integer.");
    Qnot_same_workspace = STATIC_SYMBOL("NOT-SAME-WORKSPACE",AB_package);
    string_constant_140 = 
	    STATIC_STRING("In a CREATE action, attempt to make a connection between ~NF and ~NF ~\n                  was unsuccessful because the objects are not on the same workspace.");
    Qnot_on_workspace = STATIC_SYMBOL("NOT-ON-WORKSPACE",AB_package);
    string_constant_141 = 
	    STATIC_STRING("In a CREATE action, attempt to make a connection to ~NF was ~\n                  unsuccessful because the object is not on a workspace.");
    Qnot_transient = STATIC_SYMBOL("NOT-TRANSIENT",AB_package);
    string_constant_142 = 
	    STATIC_STRING("In a CREATE action, attempt to make a connection to ~NF was ~\n                  unsuccessful because the connection to connect to is not transient.");
    Qbad_designation = STATIC_SYMBOL("BAD-DESIGNATION",AB_package);
    string_constant_143 = 
	    STATIC_STRING("In a CREATE action, attempt to make a connection to ~NF was ~\n                  unsuccessful because the designated stub was not found.");
    Qhalt = STATIC_SYMBOL("HALT",AB_package);
    Qstack_halt_body = STATIC_SYMBOL("STACK-HALT-BODY",AB_package);
    Qpprint_halt_instruction = STATIC_SYMBOL("PPRINT-HALT-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_halt_instruction,
	    STATIC_FUNCTION(pprint_halt_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qhalt,FIX((SI_Long)1L),
	    FIX((SI_Long)1L),Nil,FIX((SI_Long)99L),Qstack_halt_body,
	    SYMBOL_FUNCTION(Qpprint_halt_instruction));
    string_constant_144 = STATIC_STRING("  ~a = ");
    string_constant_145 = STATIC_STRING("~%");
    string_constant_146 = STATIC_STRING("In ~a");
    string_constant_147 = STATIC_STRING(" {about to execute instruction ~a}.");
    string_constant_148 = STATIC_STRING("~%~%At source code line #~d.");
    string_constant_149 = STATIC_STRING("~%~%~a");
    string_constant_150 = STATIC_STRING("~%~%Stack:~%");
    string_constant_151 = STATIC_STRING("  Empty stack~%");
    string_constant_152 = STATIC_STRING("~%Environment:~%~a");
    string_constant_153 = STATIC_STRING("~%[ ~a~d ~a~a] ");
    string_constant_154 = STATIC_STRING(" #");
    string_constant_155 = STATIC_STRING("#");
    string_constant_156 = STATIC_STRING("=>");
    string_constant_157 = STATIC_STRING("  ");
    string_constant_158 = STATIC_STRING("\t");
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qstack_show_body = STATIC_SYMBOL("STACK-SHOW-BODY",AB_package);
    Qpprint_show_instruction = STATIC_SYMBOL("PPRINT-SHOW-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_show_instruction,
	    STATIC_FUNCTION(pprint_show_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qshow,FIX((SI_Long)1L),
	    FIX((SI_Long)3L),Nil,FIX((SI_Long)100L),Qstack_show_body,
	    SYMBOL_FUNCTION(Qpprint_show_instruction));
    Qshow_workspace = STATIC_SYMBOL("SHOW-WORKSPACE",AB_package);
    string_constant_159 = 
	    STATIC_STRING("Cannot show ~NF.  The show action has been restricted for this item.");
    Qinvoke = STATIC_SYMBOL("INVOKE",AB_package);
    Qstack_invoke_body = STATIC_SYMBOL("STACK-INVOKE-BODY",AB_package);
    Qpprint_invoke_instruction = STATIC_SYMBOL("PPRINT-INVOKE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_invoke_instruction,
	    STATIC_FUNCTION(pprint_invoke_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qinvoke,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)101L),
	    Qstack_invoke_body,SYMBOL_FUNCTION(Qpprint_invoke_instruction));
    Qinvoke_with_wait = STATIC_SYMBOL("INVOKE-WITH-WAIT",AB_package);
    Qstack_invoke_with_wait_body = 
	    STATIC_SYMBOL("STACK-INVOKE-WITH-WAIT-BODY",AB_package);
    Qpprint_invoke_with_wait_instruction = 
	    STATIC_SYMBOL("PPRINT-INVOKE-WITH-WAIT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_invoke_with_wait_instruction,
	    STATIC_FUNCTION(pprint_invoke_with_wait_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qinvoke_with_wait,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)142L),
	    Qstack_invoke_with_wait_body,
	    SYMBOL_FUNCTION(Qpprint_invoke_with_wait_instruction));
    Qinvoking = STATIC_SYMBOL("INVOKING",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qpush_value_or_none_from_local_var = 
	    STATIC_SYMBOL("PUSH-VALUE-OR-NONE-FROM-LOCAL-VAR",AB_package);
    Qstack_push_value_or_none_from_local_var_body = 
	    STATIC_SYMBOL("STACK-PUSH-VALUE-OR-NONE-FROM-LOCAL-VAR-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_value_or_none_from_local_var,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_local_var_and_typecode),
	    FIX((SI_Long)102L),
	    Qstack_push_value_or_none_from_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_push_from_local_var_instruction));
    string_constant_160 = STATIC_STRING("Top-of-stack was not -1.");
    Qcheck_stack = STATIC_SYMBOL("CHECK-STACK",AB_package);
    Qstack_check_stack_body = STATIC_SYMBOL("STACK-CHECK-STACK-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qcheck_stack,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)103L),
	    Qstack_check_stack_body,Nil);
    Qpush_current_environment = STATIC_SYMBOL("PUSH-CURRENT-ENVIRONMENT",
	    AB_package);
    Qstack_push_current_environment_body = 
	    STATIC_SYMBOL("STACK-PUSH-CURRENT-ENVIRONMENT-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpush_current_environment,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)104L),
	    Qstack_push_current_environment_body,Nil);
    Qpop_current_environment = STATIC_SYMBOL("POP-CURRENT-ENVIRONMENT",
	    AB_package);
    Qstack_pop_current_environment_body = 
	    STATIC_SYMBOL("STACK-POP-CURRENT-ENVIRONMENT-BODY",AB_package);
    make_and_register_stack_instruction_description(Qpop_current_environment,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)105L),
	    Qstack_pop_current_environment_body,Nil);
    array_constant_86 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)15L,(SI_Long)57344L);
    array_constant_87 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)7L,(SI_Long)57344L);
    string_constant_161 = 
	    STATIC_STRING(" is not a valid element for the ~A ~NF.");
    string_constant_162 = STATIC_STRING("G2-array");
    string_constant_163 = STATIC_STRING("G2-list");
    Qcoerce_matching_element_type_or_unknown = 
	    STATIC_SYMBOL("COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcoerce_matching_element_type_or_unknown,
	    STATIC_FUNCTION(coerce_matching_element_type_or_unknown,NIL,
	    FALSE,4,4));
    Qstack_coerce_matching_element_type_or_unknown_body = 
	    STATIC_SYMBOL("STACK-COERCE-MATCHING-ELEMENT-TYPE-OR-UNKNOWN-BODY",
	    AB_package);
    Qpprint_coerce_matching_element_type_instruction = 
	    STATIC_SYMBOL("PPRINT-COERCE-MATCHING-ELEMENT-TYPE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_coerce_matching_element_type_instruction,
	    STATIC_FUNCTION(pprint_coerce_matching_element_type_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcoerce_matching_element_type_or_unknown,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)106L),
	    Qstack_coerce_matching_element_type_or_unknown_body,
	    SYMBOL_FUNCTION(Qpprint_coerce_matching_element_type_instruction));
    Qcoerce_matching_element_type = 
	    STATIC_SYMBOL("COERCE-MATCHING-ELEMENT-TYPE",AB_package);
    Qstack_coerce_matching_element_type_body = 
	    STATIC_SYMBOL("STACK-COERCE-MATCHING-ELEMENT-TYPE-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qcoerce_matching_element_type,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)107L),
	    Qstack_coerce_matching_element_type_body,
	    SYMBOL_FUNCTION(Qpprint_coerce_matching_element_type_instruction));
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_4 = STATIC_CONS(Qunknown_datum,Qnil);
    Qcomplete_rule_instance = STATIC_SYMBOL("COMPLETE-RULE-INSTANCE",
	    AB_package);
    Qstack_complete_rule_instance_body = 
	    STATIC_SYMBOL("STACK-COMPLETE-RULE-INSTANCE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qcomplete_rule_instance,
	    FIX((SI_Long)2L),Nil,Nil,FIX((SI_Long)108L),
	    Qstack_complete_rule_instance_body,Nil);
    Qpop_into_block_of_local_vars = 
	    STATIC_SYMBOL("POP-INTO-BLOCK-OF-LOCAL-VARS",AB_package);
    Qprint_block_copy = STATIC_SYMBOL("PRINT-BLOCK-COPY",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_block_copy,STATIC_FUNCTION(print_block_copy,
	    NIL,FALSE,4,4));
    Qstack_pop_into_block_of_local_vars_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-BLOCK-OF-LOCAL-VARS-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpop_into_block_of_local_vars,
	    FIX((SI_Long)4L),Nil,SYMBOL_FUNCTION(Qprint_block_copy),
	    FIX((SI_Long)109L),Qstack_pop_into_block_of_local_vars_body,Nil);
    string_constant_164 = 
	    STATIC_STRING("pop-into-block-of-local-vars emitter");
    string_constant_165 = 
	    STATIC_STRING("An invalid variable location, ~a, was given.");
    Qpush_from_block_of_local_vars = 
	    STATIC_SYMBOL("PUSH-FROM-BLOCK-OF-LOCAL-VARS",AB_package);
    Qstack_push_from_block_of_local_vars_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-BLOCK-OF-LOCAL-VARS-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_from_block_of_local_vars,
	    FIX((SI_Long)4L),Nil,SYMBOL_FUNCTION(Qprint_block_copy),
	    FIX((SI_Long)110L),Qstack_push_from_block_of_local_vars_body,Nil);
    Qbegin_rule_actions = STATIC_SYMBOL("BEGIN-RULE-ACTIONS",AB_package);
    Qstack_begin_rule_actions_body = 
	    STATIC_SYMBOL("STACK-BEGIN-RULE-ACTIONS-BODY",AB_package);
    make_and_register_stack_instruction_description(Qbegin_rule_actions,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)111L),
	    Qstack_begin_rule_actions_body,Nil);
    Qadd_to_action_cache = STATIC_SYMBOL("ADD-TO-ACTION-CACHE",AB_package);
    Qprint_action_cache_and_indices = 
	    STATIC_SYMBOL("PRINT-ACTION-CACHE-AND-INDICES",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_action_cache_and_indices,
	    STATIC_FUNCTION(print_action_cache_and_indices,NIL,FALSE,4,4));
    Qstack_add_to_action_cache_body = 
	    STATIC_SYMBOL("STACK-ADD-TO-ACTION-CACHE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qadd_to_action_cache,
	    FIX((SI_Long)7L),Nil,
	    SYMBOL_FUNCTION(Qprint_action_cache_and_indices),
	    FIX((SI_Long)112L),Qstack_add_to_action_cache_body,Nil);
    Qaction_cache = STATIC_SYMBOL("ACTION-CACHE",AB_package);
    string_constant_166 = 
	    STATIC_STRING("add to action cache byte code emitter");
    string_constant_167 = 
	    STATIC_STRING("The action cache location ~a wasn\'t local.");
    string_constant_168 = STATIC_STRING("The initial spot ~a wasn\'t local.");
    string_constant_169 = 
	    STATIC_STRING("An element of the variable block was out of order or not local.  ~\n               Expected index was ~a, actual was ~a.");
    Qrestore_from_action_cache_or_branch = 
	    STATIC_SYMBOL("RESTORE-FROM-ACTION-CACHE-OR-BRANCH",AB_package);
    Qprint_action_cache_indices_and_address = 
	    STATIC_SYMBOL("PRINT-ACTION-CACHE-INDICES-AND-ADDRESS",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_action_cache_indices_and_address,
	    STATIC_FUNCTION(print_action_cache_indices_and_address,NIL,
	    FALSE,4,4));
    Qstack_restore_from_action_cache_or_branch_body = 
	    STATIC_SYMBOL("STACK-RESTORE-FROM-ACTION-CACHE-OR-BRANCH-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qrestore_from_action_cache_or_branch,
	    FIX((SI_Long)9L),Nil,
	    SYMBOL_FUNCTION(Qprint_action_cache_indices_and_address),
	    FIX((SI_Long)113L),
	    Qstack_restore_from_action_cache_or_branch_body,Nil);
    string_constant_170 = 
	    STATIC_STRING("An internal G2 error has occurred restoring action-cache ~\n                  values.  Attempt to restore ~a elements from a ~a element\n                  cache.");
    string_constant_171 = 
	    STATIC_STRING("restore from action cache byte code emitter");
    bc_restore_from_action_cache_or_branch_resolver_1 = 
	    STATIC_FUNCTION(bc_restore_from_action_cache_or_branch_resolver,
	    NIL,FALSE,4,4);
    mutate_global_property(Qrestore_from_action_cache_or_branch,
	    bc_restore_from_action_cache_or_branch_resolver_1,
	    Qbyte_code_resolver);
    Qcomplete_simulation_variable_evaluation = 
	    STATIC_SYMBOL("COMPLETE-SIMULATION-VARIABLE-EVALUATION",
	    AB_package);
    Qstack_complete_simulation_variable_evaluation_body = 
	    STATIC_SYMBOL("STACK-COMPLETE-SIMULATION-VARIABLE-EVALUATION-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qcomplete_simulation_variable_evaluation,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)114L),
	    Qstack_complete_simulation_variable_evaluation_body,Nil);
    Qpause_kb = STATIC_SYMBOL("PAUSE-KB",AB_package);
    Qstack_pause_kb_body = STATIC_SYMBOL("STACK-PAUSE-KB-BODY",AB_package);
    Qpprint_pause_kb_instruction = 
	    STATIC_SYMBOL("PPRINT-PAUSE-KB-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_pause_kb_instruction,
	    STATIC_FUNCTION(pprint_pause_kb_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qpause_kb,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)115L),
	    Qstack_pause_kb_body,
	    SYMBOL_FUNCTION(Qpprint_pause_kb_instruction));
    Qreset_kb = STATIC_SYMBOL("RESET-KB",AB_package);
    Qstack_reset_kb_body = STATIC_SYMBOL("STACK-RESET-KB-BODY",AB_package);
    Qpprint_reset_kb_instruction = 
	    STATIC_SYMBOL("PPRINT-RESET-KB-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_reset_kb_instruction,
	    STATIC_FUNCTION(pprint_reset_kb_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qreset_kb,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)116L),
	    Qstack_reset_kb_body,
	    SYMBOL_FUNCTION(Qpprint_reset_kb_instruction));
    Qg2_get_blocks_needing_status_refreshed = 
	    STATIC_SYMBOL("G2-GET-BLOCKS-NEEDING-STATUS-REFRESHED",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_blocks_needing_status_refreshed,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_blocks_needing_status_refreshed,
	    STATIC_FUNCTION(g2_get_blocks_needing_status_refreshed,NIL,
	    FALSE,0,0));
    Qg2_get_top_level_transient_workspaces = 
	    STATIC_SYMBOL("G2-GET-TOP-LEVEL-TRANSIENT-WORKSPACES",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_top_level_transient_workspaces,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_top_level_transient_workspaces,
	    STATIC_FUNCTION(g2_get_top_level_transient_workspaces,NIL,
	    FALSE,0,0));
    Qg2_get_top_level_transient_items_and_connections = 
	    STATIC_SYMBOL("G2-GET-TOP-LEVEL-TRANSIENT-ITEMS-AND-CONNECTIONS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_top_level_transient_items_and_connections,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_top_level_transient_items_and_connections,
	    STATIC_FUNCTION(g2_get_top_level_transient_items_and_connections,
	    NIL,FALSE,0,0));
    Qg2_complete_reset_kb = STATIC_SYMBOL("G2-COMPLETE-RESET-KB",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_complete_reset_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_extension = STATIC_SYMBOL("G2-EXTENSION",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_complete_reset_kb,
	    STATIC_FUNCTION(g2_complete_reset_kb,NIL,FALSE,1,1));
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    Qstack_nupec_synchronize_body = 
	    STATIC_SYMBOL("STACK-NUPEC-SYNCHRONIZE-BODY",AB_package);
    Qpprint_nupec_synchronize_instruction = 
	    STATIC_SYMBOL("PPRINT-NUPEC-SYNCHRONIZE-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_nupec_synchronize_instruction,
	    STATIC_FUNCTION(pprint_nupec_synchronize_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qnupec_synchronize,
	    FIX((SI_Long)2L),Nil,Nil,FIX((SI_Long)117L),
	    Qstack_nupec_synchronize_body,
	    SYMBOL_FUNCTION(Qpprint_nupec_synchronize_instruction));
    string_constant_172 = STATIC_STRING("NUPEC-SYNCHRONIZE");
    string_constant_173 = 
	    string_append2(STATIC_STRING("This knowledge base was written in a NUPEC enhanced ~\n       version of G2, but this version of G2 is not enhanced ~\n       for NUPEC.  The NUPEC SYNCHRONIZE instruction canno"),
	    STATIC_STRING("t ~\n       be executed."));
    string_constant_174 = 
	    STATIC_STRING("In the NUPEC synchronize action, ~NF is not an instance of a class ~\n         containing the G2-to-G2-data-inferface capability.");
    string_constant_175 = 
	    STATIC_STRING("In the NUPEC synchronize action, ~a is not a defined class.");
    if (Items_to_traverse == UNBOUND)
	Items_to_traverse = Nil;
    Qadd_to_items_to_traverse = STATIC_SYMBOL("ADD-TO-ITEMS-TO-TRAVERSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_to_items_to_traverse,
	    STATIC_FUNCTION(add_to_items_to_traverse,NIL,FALSE,1,1));
    Qpush_from_default_allow_data_seeking = 
	    STATIC_SYMBOL("PUSH-FROM-DEFAULT-ALLOW-DATA-SEEKING",AB_package);
    Qstack_push_from_default_allow_data_seeking_body = 
	    STATIC_SYMBOL("STACK-PUSH-FROM-DEFAULT-ALLOW-DATA-SEEKING-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpush_from_default_allow_data_seeking,
	    FIX((SI_Long)1L),Nil,Nil,FIX((SI_Long)118L),
	    Qstack_push_from_default_allow_data_seeking_body,Nil);
    Qpop_into_default_allow_data_seeking = 
	    STATIC_SYMBOL("POP-INTO-DEFAULT-ALLOW-DATA-SEEKING",AB_package);
    Qstack_pop_into_default_allow_data_seeking_body = 
	    STATIC_SYMBOL("STACK-POP-INTO-DEFAULT-ALLOW-DATA-SEEKING-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qpop_into_default_allow_data_seeking,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)119L),
	    Qstack_pop_into_default_allow_data_seeking_body,Nil);
    Qstack_element_frame_or_place_reference_body = 
	    STATIC_SYMBOL("STACK-ELEMENT-FRAME-OR-PLACE-REFERENCE-BODY",
	    AB_package);
    Qpprint_nth_element_instruction = 
	    STATIC_SYMBOL("PPRINT-NTH-ELEMENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_nth_element_instruction,
	    STATIC_FUNCTION(pprint_nth_element_instruction,NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qelement_frame_or_place_reference,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)120L),
	    Qstack_element_frame_or_place_reference_body,
	    SYMBOL_FUNCTION(Qpprint_nth_element_instruction));
    string_constant_176 = 
	    STATIC_STRING("Cannot modify the element at index ~a in ~NA.  This item is not ~\n         a g2-list, g2-array, or sequence in an attribute of an item.");
    string_constant_177 = 
	    STATIC_STRING("An attempt was made to refer to element ~a of ~NF, but it is ~\n         only ~a elements long.");
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnth_element,Qitem_or_datum);
    Qelement = STATIC_SYMBOL("ELEMENT",AB_package);
    Qstack_nth_element_body = STATIC_SYMBOL("STACK-NTH-ELEMENT-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qnth_element,
	    FIX((SI_Long)1L),FIX((SI_Long)2L),Nil,FIX((SI_Long)123L),
	    Qstack_nth_element_body,
	    SYMBOL_FUNCTION(Qpprint_nth_element_instruction));
    string_constant_178 = STATIC_STRING(" ~(~a~)");
    Qunknown_class = STATIC_SYMBOL("UNKNOWN-CLASS",AB_package);
    string_constant_179 = 
	    STATIC_STRING("An internal error has just occured in the type-check-class-inline ~\n                 instruction.  The index ~a was out of range.");
    Qtype_check_class_inline = STATIC_SYMBOL("TYPE-CHECK-CLASS-INLINE",
	    AB_package);
    Qprint_type_check_class_inline = 
	    STATIC_SYMBOL("PRINT-TYPE-CHECK-CLASS-INLINE",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_type_check_class_inline,
	    STATIC_FUNCTION(print_type_check_class_inline,NIL,FALSE,4,4));
    Qstack_type_check_class_inline_body = 
	    STATIC_SYMBOL("STACK-TYPE-CHECK-CLASS-INLINE-BODY",AB_package);
    Qpprint_type_check_class_inline_instruction = 
	    STATIC_SYMBOL("PPRINT-TYPE-CHECK-CLASS-INLINE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_type_check_class_inline_instruction,
	    STATIC_FUNCTION(pprint_type_check_class_inline_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qtype_check_class_inline,
	    FIX((SI_Long)2L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_type_check_class_inline),
	    FIX((SI_Long)124L),Qstack_type_check_class_inline_body,
	    SYMBOL_FUNCTION(Qpprint_type_check_class_inline_instruction));
    string_constant_180 = 
	    STATIC_STRING("An error occured while concluding a formula result.  ~a");
    Qcomplete_generic_formula = STATIC_SYMBOL("COMPLETE-GENERIC-FORMULA",
	    AB_package);
    Qstack_complete_generic_formula_body = 
	    STATIC_SYMBOL("STACK-COMPLETE-GENERIC-FORMULA-BODY",AB_package);
    Qpprint_complete_generic_formula_instruction = 
	    STATIC_SYMBOL("PPRINT-COMPLETE-GENERIC-FORMULA-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_complete_generic_formula_instruction,
	    STATIC_FUNCTION(pprint_complete_generic_formula_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcomplete_generic_formula,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)125L),
	    Qstack_complete_generic_formula_body,
	    SYMBOL_FUNCTION(Qpprint_complete_generic_formula_instruction));
    Qcomplete_cell_expression = STATIC_SYMBOL("COMPLETE-CELL-EXPRESSION",
	    AB_package);
    Qstack_complete_cell_expression_body = 
	    STATIC_SYMBOL("STACK-COMPLETE-CELL-EXPRESSION-BODY",AB_package);
    Qpprint_complete_cell_expression_instruction = 
	    STATIC_SYMBOL("PPRINT-COMPLETE-CELL-EXPRESSION-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_complete_cell_expression_instruction,
	    STATIC_FUNCTION(pprint_complete_cell_expression_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qcomplete_cell_expression,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)126L),
	    Qstack_complete_cell_expression_body,
	    SYMBOL_FUNCTION(Qpprint_complete_cell_expression_instruction));
    array_constant_88 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)23L,(SI_Long)57344L);
    string_constant_181 = STATIC_STRING(" (~a)");
    Qbegin_activity = STATIC_SYMBOL("BEGIN-ACTIVITY",AB_package);
    Qprint_begin_activity = STATIC_SYMBOL("PRINT-BEGIN-ACTIVITY",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_begin_activity,
	    STATIC_FUNCTION(print_begin_activity,NIL,FALSE,4,4));
    Qstack_begin_activity_body = STATIC_SYMBOL("STACK-BEGIN-ACTIVITY-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qbegin_activity,
	    FIX((SI_Long)2L),Nil,SYMBOL_FUNCTION(Qprint_begin_activity),
	    FIX((SI_Long)127L),Qstack_begin_activity_body,Nil);
    string_constant_182 = STATIC_STRING("About to execute the activity: ");
    string_constant_183 = STATIC_STRING("~%Within: ");
    Insert_begin_activity_instruction_into_byte_code_stream_qm = T;
    string_constant_184 = STATIC_STRING("begin activity byte code emitter");
    string_constant_185 = 
	    STATIC_STRING("The given activity number, ~a, was out of range.");
    string_constant_186 = STATIC_STRING("The designated item does not exist.");
    string_constant_187 = 
	    STATIC_STRING("~NF cannot be referenced because it is disabled or inactive.");
    Qpush_cached_item = STATIC_SYMBOL("PUSH-CACHED-ITEM",AB_package);
    Qprint_cached_item = STATIC_SYMBOL("PRINT-CACHED-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_cached_item,
	    STATIC_FUNCTION(print_cached_item,NIL,FALSE,4,4));
    Qstack_push_cached_item_body = 
	    STATIC_SYMBOL("STACK-PUSH-CACHED-ITEM-BODY",AB_package);
    Qpprint_push_cached_item_instruction = 
	    STATIC_SYMBOL("PPRINT-PUSH-CACHED-ITEM-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_push_cached_item_instruction,
	    STATIC_FUNCTION(pprint_push_cached_item_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qpush_cached_item,
	    FIX((SI_Long)4L),Nil,SYMBOL_FUNCTION(Qprint_cached_item),
	    FIX((SI_Long)128L),Qstack_push_cached_item_body,
	    SYMBOL_FUNCTION(Qpprint_push_cached_item_instruction));
    Qcached_name = STATIC_SYMBOL("CACHED-NAME",AB_package);
    Qcached_attribute_value = STATIC_SYMBOL("CACHED-ATTRIBUTE-VALUE",
	    AB_package);
    Qprint_cached_attribute = STATIC_SYMBOL("PRINT-CACHED-ATTRIBUTE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_cached_attribute,
	    STATIC_FUNCTION(print_cached_attribute,NIL,FALSE,4,4));
    Qstack_cached_attribute_value_body = 
	    STATIC_SYMBOL("STACK-CACHED-ATTRIBUTE-VALUE-BODY",AB_package);
    Qpprint_cached_attribute_value_instruction = 
	    STATIC_SYMBOL("PPRINT-CACHED-ATTRIBUTE-VALUE-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_cached_attribute_value_instruction,
	    STATIC_FUNCTION(pprint_cached_attribute_value_instruction,NIL,
	    FALSE,5,5));
    make_and_register_stack_instruction_description(Qcached_attribute_value,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_cached_attribute),FIX((SI_Long)132L),
	    Qstack_cached_attribute_value_body,
	    SYMBOL_FUNCTION(Qpprint_cached_attribute_value_instruction));
    string_constant_188 = 
	    STATIC_STRING("An attribute of ~NF contained nothing, causing this reference to fail.");
    Qcached_attribute = STATIC_SYMBOL("CACHED-ATTRIBUTE",AB_package);
    Qboolean_branch_if_not_true = 
	    STATIC_SYMBOL("BOOLEAN-BRANCH-IF-NOT-TRUE",AB_package);
    Qstack_boolean_branch_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BOOLEAN-BRANCH-IF-NOT-TRUE-BODY",AB_package);
    make_and_register_stack_instruction_description(Qboolean_branch_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_code_constant),
	    FIX((SI_Long)129L),Qstack_boolean_branch_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_if_not_true_instruction));
    Qboolean_branch_long_if_not_true = 
	    STATIC_SYMBOL("BOOLEAN-BRANCH-LONG-IF-NOT-TRUE",AB_package);
    Qstack_boolean_branch_long_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BOOLEAN-BRANCH-LONG-IF-NOT-TRUE-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qboolean_branch_long_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_long_code_constant),
	    FIX((SI_Long)130L),Qstack_boolean_branch_long_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_long_if_not_true_instruction));
    Qboolean_branch_relative_if_not_true = 
	    STATIC_SYMBOL("BOOLEAN-BRANCH-RELATIVE-IF-NOT-TRUE",AB_package);
    Qstack_boolean_branch_relative_if_not_true_body = 
	    STATIC_SYMBOL("STACK-BOOLEAN-BRANCH-RELATIVE-IF-NOT-TRUE-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qboolean_branch_relative_if_not_true,
	    FIX((SI_Long)3L),FIX((SI_Long)1L),
	    SYMBOL_FUNCTION(Qprint_op_and_relative_code_constant_address),
	    FIX((SI_Long)131L),
	    Qstack_boolean_branch_relative_if_not_true_body,
	    SYMBOL_FUNCTION(Qpprint_branch_relative_if_not_true_instruction));
    string_constant_189 = 
	    STATIC_STRING("The g2-array ~NF contains no element at index ~a.");
    Qnth_integer_array_element = STATIC_SYMBOL("NTH-INTEGER-ARRAY-ELEMENT",
	    AB_package);
    Qstack_nth_integer_array_element_body = 
	    STATIC_SYMBOL("STACK-NTH-INTEGER-ARRAY-ELEMENT-BODY",AB_package);
    Qpprint_nth_array_element_instruction = 
	    STATIC_SYMBOL("PPRINT-NTH-ARRAY-ELEMENT-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_nth_array_element_instruction,
	    STATIC_FUNCTION(pprint_nth_array_element_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qnth_integer_array_element,
	    FIX((SI_Long)5L),FIX((SI_Long)2L),Nil,FIX((SI_Long)133L),
	    Qstack_nth_integer_array_element_body,
	    SYMBOL_FUNCTION(Qpprint_nth_array_element_instruction));
    Qnth_float_array_element = STATIC_SYMBOL("NTH-FLOAT-ARRAY-ELEMENT",
	    AB_package);
    Qstack_nth_float_array_element_body = 
	    STATIC_SYMBOL("STACK-NTH-FLOAT-ARRAY-ELEMENT-BODY",AB_package);
    make_and_register_stack_instruction_description(Qnth_float_array_element,
	    FIX((SI_Long)5L),FIX((SI_Long)2L),Nil,FIX((SI_Long)134L),
	    Qstack_nth_float_array_element_body,
	    SYMBOL_FUNCTION(Qpprint_nth_array_element_instruction));
    array_constant_89 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_89,(SI_Long)15L,(SI_Long)57344L);
    array_constant_90 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)0L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)2L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_90,(SI_Long)7L,(SI_Long)57344L);
    Qchange_nth_integer_array_element = 
	    STATIC_SYMBOL("CHANGE-NTH-INTEGER-ARRAY-ELEMENT",AB_package);
    Qstack_change_nth_integer_array_element_body = 
	    STATIC_SYMBOL("STACK-CHANGE-NTH-INTEGER-ARRAY-ELEMENT-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qchange_nth_integer_array_element,
	    FIX((SI_Long)1L),FIX((SI_Long)3L),Nil,FIX((SI_Long)135L),
	    Qstack_change_nth_integer_array_element_body,
	    SYMBOL_FUNCTION(Qpprint_nth_array_element_instruction));
    Qchange_nth_float_array_element = 
	    STATIC_SYMBOL("CHANGE-NTH-FLOAT-ARRAY-ELEMENT",AB_package);
    Qstack_change_nth_float_array_element_body = 
	    STATIC_SYMBOL("STACK-CHANGE-NTH-FLOAT-ARRAY-ELEMENT-BODY",
	    AB_package);
    make_and_register_stack_instruction_description(Qchange_nth_float_array_element,
	    FIX((SI_Long)1L),FIX((SI_Long)3L),Nil,FIX((SI_Long)136L),
	    Qstack_change_nth_float_array_element_body,
	    SYMBOL_FUNCTION(Qpprint_nth_array_element_instruction));
    Qsignal_error_new = STATIC_SYMBOL("SIGNAL-ERROR-NEW",AB_package);
    Qstack_signal_error_new_body = 
	    STATIC_SYMBOL("STACK-SIGNAL-ERROR-NEW-BODY",AB_package);
    Qpprint_signal_error_new_instruction = 
	    STATIC_SYMBOL("PPRINT-SIGNAL-ERROR-NEW-INSTRUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_signal_error_new_instruction,
	    STATIC_FUNCTION(pprint_signal_error_new_instruction,NIL,FALSE,
	    5,5));
    make_and_register_stack_instruction_description(Qsignal_error_new,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)137L),
	    Qstack_signal_error_new_body,
	    SYMBOL_FUNCTION(Qpprint_signal_error_new_instruction));
    Qmove_from_surrounding_local_var = 
	    STATIC_SYMBOL("MOVE-FROM-SURROUNDING-LOCAL-VAR",AB_package);
    Qprint_op_and_surrounding_local_var = 
	    STATIC_SYMBOL("PRINT-OP-AND-SURROUNDING-LOCAL-VAR",AB_package);
    SET_SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var,
	    STATIC_FUNCTION(print_op_and_surrounding_local_var,NIL,FALSE,4,4));
    Qstack_move_from_surrounding_local_var_body = 
	    STATIC_SYMBOL("STACK-MOVE-FROM-SURROUNDING-LOCAL-VAR-BODY",
	    AB_package);
    Qpprint_move_from_surrounding_local_var_instruction = 
	    STATIC_SYMBOL("PPRINT-MOVE-FROM-SURROUNDING-LOCAL-VAR-INSTRUCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpprint_move_from_surrounding_local_var_instruction,
	    STATIC_FUNCTION(pprint_move_from_surrounding_local_var_instruction,
	    NIL,FALSE,5,5));
    make_and_register_stack_instruction_description(Qmove_from_surrounding_local_var,
	    FIX((SI_Long)3L),Nil,
	    SYMBOL_FUNCTION(Qprint_op_and_surrounding_local_var),
	    FIX((SI_Long)138L),Qstack_move_from_surrounding_local_var_body,
	    SYMBOL_FUNCTION(Qpprint_move_from_surrounding_local_var_instruction));
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qstack_frame_var,Qstack_arg);
    string_constant_190 = STATIC_STRING("move-from-local-var emitter");
    Qallow_no_item_for_evaluator = 
	    STATIC_SYMBOL("ALLOW-NO-ITEM-FOR-EVALUATOR",AB_package);
    bc_allow_no_item_for_evaluator_resolver_1 = 
	    STATIC_FUNCTION(bc_allow_no_item_for_evaluator_resolver,NIL,
	    FALSE,4,4);
    mutate_global_property(Qallow_no_item_for_evaluator,
	    bc_allow_no_item_for_evaluator_resolver_1,Qbyte_code_resolver);
    Qstack_allow_no_item_for_evaluator_body = 
	    STATIC_SYMBOL("STACK-ALLOW-NO-ITEM-FOR-EVALUATOR-BODY",AB_package);
    make_and_register_stack_instruction_description(Qallow_no_item_for_evaluator,
	    FIX((SI_Long)3L),Nil,Nil,FIX((SI_Long)140L),
	    Qstack_allow_no_item_for_evaluator_body,Nil);
    Qcoerce_integer_to_long = STATIC_SYMBOL("COERCE-INTEGER-TO-LONG",
	    AB_package);
    Qstack_coerce_integer_to_long_body = 
	    STATIC_SYMBOL("STACK-COERCE-INTEGER-TO-LONG-BODY",AB_package);
    make_and_register_stack_instruction_description(Qcoerce_integer_to_long,
	    FIX((SI_Long)1L),FIX((SI_Long)1L),Nil,FIX((SI_Long)144L),
	    Qstack_coerce_integer_to_long_body,Nil);
}
