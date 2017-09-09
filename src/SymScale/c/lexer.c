/* lexer.c
 * Input file:  lexer.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lexer.h"


static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object Qbuilt_in;           /* built-in */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* FORMAT-NOTE-FOR-PREPROCESSOR-ERROR */
Object format_note_for_preprocessor_error(name,expression,preprocessor_errors)
    Object name, expression, preprocessor_errors;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object number_of_errors, macro_name, type_of_error, ab_loop_list_;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, iterator;
    Declare_special(5);

    x_note_fn_call(188,0);
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
	      twrite_symbol(2,name,T);
	      twrite_beginning_of_wide_string(array_constant,
		      FIX((SI_Long)19L));
	      twrite_general_string(expression);
	      twrite_beginning_of_wide_string(array_constant_1,
		      FIX((SI_Long)10L));
	      if (ATOM(preprocessor_errors))
		  twrite_beginning_of_wide_string(array_constant_2,
			  FIX((SI_Long)36L));
	      else {
		  number_of_errors = length(preprocessor_errors);
		  macro_name = Nil;
		  type_of_error = Nil;
		  ab_loop_list_ = preprocessor_errors;
		  iterator = (SI_Long)1L;
		  ab_loop_iter_flag_ = T;
		  ab_loop_desetq_ = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  ab_loop_desetq_ = M_CAR(ab_loop_list_);
		  macro_name = CAR(ab_loop_desetq_);
		  temp = CDR(ab_loop_desetq_);
		  type_of_error = CAR(temp);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if ( !TRUEP(ab_loop_iter_flag_))
		      iterator = iterator + (SI_Long)1L;
		  if (EQ(type_of_error,Qbuilt_in))
		      twrite_beginning_of_wide_string(array_constant_3,
			      FIX((SI_Long)44L));
		  else if (EQ(type_of_error,Qvariable))
		      twrite_beginning_of_wide_string(array_constant_4,
			      FIX((SI_Long)41L));
		  else
		      twrite_beginning_of_wide_string(array_constant_5,
			      FIX((SI_Long)10L));
		  twrite_symbol(1,macro_name);
		  if ( !(iterator == IFIX(number_of_errors))) {
		      if (iterator == IFIX(FIXNUM_SUB1(number_of_errors)))
			  twrite_beginning_of_wide_string(array_constant_6,
				  FIX((SI_Long)6L));
		      else
			  twrite_beginning_of_wide_string(array_constant_7,
				  FIX((SI_Long)2L));
		  }
		  ab_loop_iter_flag_ = Nil;
		  goto next_loop;
		end_loop:;
	      }
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

/* MAKE-ERROR-STRING-FOR-BAD-REGULAR-EXPRESSION */
Object make_error_string_for_bad_regular_expression(pattern,evaluator_name,
	    preprocessor_errors_qm)
    Object pattern, evaluator_name, preprocessor_errors_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object number_of_errors, macro_name, type_of_error, ab_loop_list_;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp, result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, iterator;
    Declare_special(6);
    Object result;

    x_note_fn_call(188,1);
    PUSH_SPECIAL_WITH_SYMBOL(Preprocessor_errors_qm,Qpreprocessor_errors_qm,preprocessor_errors_qm,
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
		twrite_beginning_of_wide_string(array_constant_8,
			FIX((SI_Long)24L));
		twrite_general_string(pattern);
		twrite_beginning_of_wide_string(array_constant_9,
			FIX((SI_Long)11L));
		twrite_symbol(2,evaluator_name,T);
		twrite_beginning_of_wide_string(array_constant_10,
			FIX((SI_Long)21L));
		if (Preprocessor_errors_qm) {
		    twrite_beginning_of_wide_string(array_constant_11,
			    FIX((SI_Long)27L));
		    number_of_errors = length(Preprocessor_errors_qm);
		    macro_name = Nil;
		    type_of_error = Nil;
		    ab_loop_list_ = Preprocessor_errors_qm;
		    iterator = (SI_Long)1L;
		    ab_loop_iter_flag_ = T;
		    ab_loop_desetq_ = Nil;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    ab_loop_desetq_ = M_CAR(ab_loop_list_);
		    macro_name = CAR(ab_loop_desetq_);
		    temp = CDR(ab_loop_desetq_);
		    type_of_error = CAR(temp);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if ( !TRUEP(ab_loop_iter_flag_))
			iterator = iterator + (SI_Long)1L;
		    if (EQ(type_of_error,Qbuilt_in))
			twrite_beginning_of_wide_string(array_constant_3,
				FIX((SI_Long)44L));
		    else
			twrite_beginning_of_wide_string(array_constant_5,
				FIX((SI_Long)10L));
		    twrite_symbol(1,macro_name);
		    if ( !(iterator == IFIX(number_of_errors))) {
			if (iterator == IFIX(FIXNUM_SUB1(number_of_errors)))
			    twrite_beginning_of_wide_string(array_constant_6,
				    FIX((SI_Long)6L));
			else
			    twrite_beginning_of_wide_string(array_constant_7,
				    FIX((SI_Long)2L));
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop;
		  end_loop:
		    reclaim_token_tree_1(Preprocessor_errors_qm);
		}
		result_1 = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      result = VALUES_1(result_1);
    POP_SPECIAL();
    return result;
}

static Object array_constant_12;   /* # */

static Object string_constant;     /* "   (~c~c) " */

static Object string_constant_1;   /* "   (~c) " */

static Object string_constant_2;   /* "~a" */

/* WRITE-TOKENIZER-PATTERN-NOTES-NOTE */
Object write_tokenizer_pattern_notes_note(note_strings,gensymed_symbol)
    Object note_strings, gensymed_symbol;
{
    Object note, ab_loop_list_, ab_loop_iter_flag_, temp, aref_arg_2, char1;
    Object char2;
    SI_Long note_index;
    Object result;

    x_note_fn_call(188,2);
    twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)59L));
    note = Nil;
    ab_loop_list_ = note_strings;
    note_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    note = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	note_index = note_index + (SI_Long)1L;
    if ( !(note_index == (SI_Long)0L)) {
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)59L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
    }
    if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
	    Total_length_of_current_wide_string))
	extend_current_wide_string(Fill_pointer_for_current_wide_string);
    temp = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)8232L);
    temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp;
    if (note_index >= (SI_Long)26L) {
	result = chestnut_floorf_function(FIX(note_index),FIX((SI_Long)26L));
	MVS_2(result,char1,char2);
	tformat(3,string_constant,FIX((SI_Long)96L + IFIX(char1)),
		FIX((SI_Long)97L + IFIX(char2)));
    }
    else
	tformat(2,string_constant_1,FIX((SI_Long)97L + note_index));
    tformat(2,string_constant_2,note);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object array_constant_13;   /* # */

/* FORMAT-NOTE-FOR-DUPLICATE-PATTERN */
Object format_note_for_duplicate_pattern(name)
    Object name;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(188,3);
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
	      twrite_symbol(2,name,T);
	      twrite_beginning_of_wide_string(array_constant_13,
		      FIX((SI_Long)26L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object array_constant_14;   /* # */

/* WRITE-TOKENIZER-TOKEN-NOTES-NOTE */
Object write_tokenizer_token_notes_note(note_strings,gensymed_symbol)
    Object note_strings, gensymed_symbol;
{
    Object note, ab_loop_list_, ab_loop_iter_flag_, temp, aref_arg_2;
    SI_Long note_index;

    x_note_fn_call(188,4);
    twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)57L));
    note = Nil;
    ab_loop_list_ = note_strings;
    note_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    note = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	note_index = note_index + (SI_Long)1L;
    if ( !(note_index == (SI_Long)0L)) {
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)59L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
    }
    if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
	    Total_length_of_current_wide_string))
	extend_current_wide_string(Fill_pointer_for_current_wide_string);
    temp = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)8232L);
    temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp;
    tformat(2,string_constant_1,FIX((SI_Long)97L + note_index));
    tformat(2,string_constant_2,note);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* FORMAT-PATTERN-NOTES */
Object format_pattern_notes(unparsable_patterns,duplicate_patterns)
    Object unparsable_patterns, duplicate_patterns;
{
    Object formatted_list, name, expression, preprocessor_errors;
    Object ab_loop_list_, message_1, ab_loop_desetq_, temp;

    x_note_fn_call(188,5);
    formatted_list = Qnil;
    name = Nil;
    expression = Nil;
    preprocessor_errors = Nil;
    ab_loop_list_ = unparsable_patterns;
    message_1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    expression = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    preprocessor_errors = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    message_1 = format_note_for_preprocessor_error(name,expression,
	    preprocessor_errors);
    formatted_list = slot_value_cons_1(message_1,formatted_list);
    goto next_loop;
  end_loop:;
    name = Nil;
    ab_loop_list_ = duplicate_patterns;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = format_note_for_duplicate_pattern(name);
    formatted_list = slot_value_cons_1(temp,formatted_list);
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(formatted_list);
}

/* FORMAT-TOKEN-NOTES */
Object format_token_notes(unparsable_tokens)
    Object unparsable_tokens;
{
    Object formatted_list, name, expression, preprocessor_errors;
    Object ab_loop_list_, message_1, ab_loop_desetq_, temp;

    x_note_fn_call(188,6);
    formatted_list = Nil;
    name = Nil;
    expression = Nil;
    preprocessor_errors = Nil;
    ab_loop_list_ = unparsable_tokens;
    message_1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    expression = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    preprocessor_errors = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    message_1 = format_note_for_preprocessor_error(name,expression,
	    preprocessor_errors);
    formatted_list = slot_value_cons_1(message_1,formatted_list);
    goto next_loop;
  end_loop:
    temp = formatted_list;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qtokenizer_pattern_notes;  /* tokenizer-pattern-notes */

/* ADD-TOKENIZER-PATTERN-FRAME-NOTES */
Object add_tokenizer_pattern_frame_notes(tokenizer,pattern_notes,
	    duplicate_patterns)
    Object tokenizer, pattern_notes, duplicate_patterns;
{
    x_note_fn_call(188,7);
    delete_frame_note_if_any(Qtokenizer_pattern_notes,tokenizer);
    if (pattern_notes || duplicate_patterns) {
	add_frame_note(5,Qtokenizer_pattern_notes,tokenizer,
		format_pattern_notes(pattern_notes,duplicate_patterns),T,Nil);
	reclaim_token_list_1(duplicate_patterns);
	reclaim_token_tree_1(pattern_notes);
    }
    return VALUES_1(Nil);
}

static Object Qtokenizer_token_notes;  /* tokenizer-token-notes */

/* ADD-TOKENIZER-TOKEN-FRAME-NOTES */
Object add_tokenizer_token_frame_notes(tokenizer,token_notes)
    Object tokenizer, token_notes;
{
    x_note_fn_call(188,8);
    delete_frame_note_if_any(Qtokenizer_token_notes,tokenizer);
    if (token_notes) {
	add_frame_note(5,Qtokenizer_token_notes,tokenizer,
		format_token_notes(token_notes),T,Nil);
	reclaim_token_notes(token_notes);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-TOKEN-NOTES */
Object reclaim_token_notes(token_notes)
    Object token_notes;
{
    Object action, expression, preprocessed_expression, ab_loop_list_;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(188,9);
    action = Nil;
    expression = Nil;
    preprocessed_expression = Nil;
    ab_loop_list_ = token_notes;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    action = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    expression = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    preprocessed_expression = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(preprocessed_expression) != 
	    (SI_Long)0L)
	reclaim_wide_string(preprocessed_expression);
    goto next_loop;
  end_loop:;
    reclaim_token_tree_1(token_notes);
    return VALUES_1(Nil);
}

static Object Qtokenizer;          /* tokenizer */

static Object Qincomplete;         /* incomplete */

/* INITIALIZE-FOR-TOKENIZER */
Object initialize_for_tokenizer(tokenizer)
    Object tokenizer;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(188,10);
    frame = tokenizer;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtokenizer)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return update_frame_status(tokenizer,Qincomplete,Nil);
}

static Object Qlexing_table;       /* lexing-table */

/* SEARCH-FOR-MATCH-USING-TOKENIZER */
Object search_for_match_using_tokenizer(tokenizer,source_text,start_index)
    Object tokenizer, source_text, start_index;
{
    Object current_tokenizer, current_start_state, current_anchor_p;
    Object next_token, svref_new_value, temp;
    Declare_special(4);

    x_note_fn_call(188,11);
    current_tokenizer = get_lookup_slot_value_given_default(tokenizer,
	    Qlexing_table,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_tokenizer,Qcurrent_tokenizer,current_tokenizer,
	    3);
      current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_start_state,Qcurrent_start_state,current_start_state,
	      2);
	current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		1);
	  current_anchor_p = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		  0);
	    next_token = INLINE_UNSIGNED_BYTE_16_VECTOR_P(source_text) != 
		    (SI_Long)0L ? 
		    get_next_token_from_text_string_1(source_text,
		    start_index,Nil) : Qnil;
	    svref_new_value = FIXNUM_ADD1(ISVREF(next_token,(SI_Long)2L));
	    SVREF(next_token,FIX((SI_Long)2L)) = svref_new_value;
	    temp = next_token;
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* PATTERN-IS-ALREADY-PRESENT-IN-LEXING-STRINGS */
Object pattern_is_already_present_in_lexing_strings(new_name)
    Object new_name;
{
    Object name, expression, ab_loop_list_, ab_loop_it_, ab_loop_desetq_, temp;

    x_note_fn_call(188,12);
    name = Nil;
    expression = Nil;
    ab_loop_list_ = Current_lexing_strings;
    ab_loop_it_ = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    expression = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(name,new_name) ? T : Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* PARSE-PATTERNS */
Object parse_patterns(patterns)
    Object patterns;
{
    Object temp, current_lexing_strings, unparsable_patterns;
    Object duplicate_pattern_names, name, expression, ab_loop_list_;
    Object preprocessed_expression_or_list_of_errors, parsed_expression;
    Object ab_loop_desetq_, gensymed_symbol;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(188,13);
    if (LISTP(patterns)) {
	temp = CAR(patterns);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	current_lexing_strings = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_strings,Qcurrent_lexing_strings,current_lexing_strings,
		0);
	  unparsable_patterns = Qnil;
	  duplicate_pattern_names = Qnil;
	  name = Nil;
	  expression = Nil;
	  ab_loop_list_ = patterns;
	  preprocessed_expression_or_list_of_errors = Nil;
	  parsed_expression = Nil;
	  ab_loop_desetq_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  name = CAR(ab_loop_desetq_);
	  expression = CDR(ab_loop_desetq_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  preprocessed_expression_or_list_of_errors = 
		  preprocess_regexp_string(expression,T);
	  parsed_expression = 
		  INLINE_UNSIGNED_BYTE_16_VECTOR_P(preprocessed_expression_or_list_of_errors) 
		  != (SI_Long)0L ? 
		  parse_regexp_string(preprocessed_expression_or_list_of_errors) 
		  : Qnil;
	  if ( !TRUEP(parsed_expression)) {
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(preprocessed_expression_or_list_of_errors) 
		      != (SI_Long)0L) {
		  reclaim_wide_string(preprocessed_expression_or_list_of_errors);
		  preprocessed_expression_or_list_of_errors = Nil;
	      }
	      unparsable_patterns = token_cons_1(token_list_3(name,
		      expression,
		      preprocessed_expression_or_list_of_errors),
		      unparsable_patterns);
	  }
	  else {
	      if (pattern_is_already_present_in_lexing_strings(name)) {
		  gensymed_symbol = duplicate_pattern_names;
		next_loop_1:
		  if ( !TRUEP(gensymed_symbol))
		      goto end_loop_1;
		  if (EQ(M_CAR(gensymed_symbol),name)) {
		      temp_1 = TRUEP(gensymed_symbol);
		      goto end_1;
		  }
		  gensymed_symbol = M_CDR(gensymed_symbol);
		  goto next_loop_1;
		end_loop_1:
		  temp_1 = TRUEP(Qnil);
		end_1:;
		  duplicate_pattern_names = temp_1 ? 
			  duplicate_pattern_names : token_cons_1(name,
			  duplicate_pattern_names);
	      }
	      Current_lexing_strings = 
		      slot_value_cons_1(slot_value_cons_1(name,
		      preprocessed_expression_or_list_of_errors),
		      Current_lexing_strings);
	  }
	  goto next_loop;
	end_loop:
	  result = VALUES_3(Current_lexing_strings,unparsable_patterns,
		  duplicate_pattern_names);
	  goto end_2;
	  result = VALUES_1(Qnil);
	end_2:;
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PARSE-TOKENS */
Object parse_tokens(tokens)
    Object tokens;
{
    Object temp, parsed_tokens, unparsable_tokens, action, expression;
    Object ab_loop_list_, preprocessed_expression, parsed_expression;
    Object ab_loop_desetq_;
    char temp_1;

    x_note_fn_call(188,14);
    temp = CAR(tokens);
    if (LISTP(temp)) {
	temp = CAAR(tokens);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	parsed_tokens = Qnil;
	unparsable_tokens = Qnil;
	action = Nil;
	expression = Nil;
	ab_loop_list_ = CAR(tokens);
	preprocessed_expression = Nil;
	parsed_expression = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	action = CAR(ab_loop_desetq_);
	expression = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	preprocessed_expression = preprocess_regexp_string(expression,T);
	parsed_expression = 
		INLINE_UNSIGNED_BYTE_16_VECTOR_P(preprocessed_expression) 
		!= (SI_Long)0L ? 
		parse_regexp_string(preprocessed_expression) : Qnil;
	if ( !TRUEP(parsed_expression))
	    unparsable_tokens = token_cons_1(token_list_3(action,
		    expression,preprocessed_expression),unparsable_tokens);
	else {
	    reclaim_wide_string(preprocessed_expression);
	    parsed_tokens = slot_value_cons_1(slot_value_list_2(action,
		    copy_tree_using_slot_value_conses_1(parsed_expression)),
		    parsed_tokens);
	}
	goto next_loop;
      end_loop:
	temp = nreverse(parsed_tokens);
	return VALUES_2(temp,unparsable_tokens);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PATTERNS-STRINGS-VALUE */
Object reclaim_patterns_strings_value(patterns_strings,tokenizer)
    Object patterns_strings, tokenizer;
{
    x_note_fn_call(188,15);
    reclaim_patterns_strings(patterns_strings,tokenizer);
    return VALUES_1(Nil);
}

static Object Qpatterns_strings;   /* patterns-strings */

/* RECLAIM-PATTERNS-STRINGS */
Object reclaim_patterns_strings(patterns_strings,tokenizer)
    Object patterns_strings, tokenizer;
{
    Object name, pattern, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(188,16);
    name = Nil;
    pattern = Nil;
    ab_loop_list_ = patterns_strings;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    pattern = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_wide_string(pattern);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_tree_1(patterns_strings);
    set_non_savable_lookup_slot_value(tokenizer,Qpatterns_strings,Nil);
    return VALUES_1(Nil);
}

/* RECLAIM-TOKENS-CONS-VALUE */
Object reclaim_tokens_cons_value(tokens_cons,tokenizer)
    Object tokens_cons, tokenizer;
{
    x_note_fn_call(188,17);
    reclaim_tokens_cons(tokens_cons,tokenizer);
    return VALUES_1(Nil);
}

static Object Qtokens_cons;        /* tokens-cons */

/* RECLAIM-TOKENS-CONS */
Object reclaim_tokens_cons(tokens_cons,tokenizer)
    Object tokens_cons, tokenizer;
{
    x_note_fn_call(188,18);
    reclaim_slot_value_tree_1(tokens_cons);
    set_non_savable_lookup_slot_value(tokenizer,Qtokens_cons,Nil);
    return VALUES_1(Nil);
}

/* RECLAIM-LEXING-TABLE-VALUE */
Object reclaim_lexing_table_value(lexing_table,tokenizer)
    Object lexing_table, tokenizer;
{
    x_note_fn_call(188,19);
    reclaim_dfa_if_any(lexing_table);
    set_non_savable_lookup_slot_value(tokenizer,Qlexing_table,Nil);
    return VALUES_1(Nil);
}

static Object Qpatterns_definition;  /* patterns-definition */

static Object Qtoken;              /* token */

static Object Qbad;                /* bad */

/* PUT-PATTERNS-DEFINITION */
Object put_patterns_definition(tokenizer,patterns_definition,gensymed_symbol)
    Object tokenizer, patterns_definition, gensymed_symbol;
{
    Object current_lexing_strings, unparsable_patterns, duplicate_patterns;
    Object tokens_cons, unparsable_tokens, token_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(188,20);
    delete_frame_note_if_any(Qtokenizer_pattern_notes,tokenizer);
    delete_frame_note_if_any(Qtokenizer_token_notes,tokenizer);
    result = parse_patterns(CAR(patterns_definition));
    MVS_3(result,current_lexing_strings,unparsable_patterns,
	    duplicate_patterns);
    PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_strings,Qcurrent_lexing_strings,current_lexing_strings,
	    0);
      add_tokenizer_pattern_frame_notes(tokenizer,unparsable_patterns,
	      duplicate_patterns);
      result = parse_tokens(ISVREF(tokenizer,(SI_Long)21L));
      MVS_2(result,tokens_cons,unparsable_tokens);
      add_tokenizer_token_frame_notes(tokenizer,unparsable_tokens);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(tokenizer,Qpatterns_definition);
      SVREF(tokenizer,FIX((SI_Long)20L)) = patterns_definition;
      reclaim_patterns_strings(get_lookup_slot_value_given_default(tokenizer,
	      Qpatterns_strings,Nil),tokenizer);
      set_non_savable_lookup_slot_value(tokenizer,Qpatterns_strings,
	      Current_lexing_strings);
      reclaim_tokens_cons(get_lookup_slot_value_given_default(tokenizer,
	      Qtokens_cons,Nil),tokenizer);
      set_non_savable_lookup_slot_value(tokenizer,Qtokens_cons,tokens_cons);
      reclaim_dfa_if_any(get_lookup_slot_value_given_default(tokenizer,
	      Qlexing_table,Nil));
      if (tokens_cons &&  !TRUEP(unparsable_tokens)) {
	  update_frame_status(tokenizer,Nil,Nil);
	  tokens_cons = token_cons_1(Nil,tokens_cons);
	  set_non_savable_lookup_slot_value(tokenizer,Qlexing_table,
		  compile_lexing_table(tokens_cons));
	  token_pop_store = Nil;
	  cons_1 = tokens_cons;
	  if (cons_1) {
	      token_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qtoken);
	      if (ISVREF(Available_token_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_token_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_token_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_token_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_token_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  tokens_cons = next_cons;
      }
      else {
	  if (unparsable_tokens)
	      update_frame_status(tokenizer,Qbad,Nil);
	  else
	      update_frame_status(tokenizer,Qincomplete,Nil);
	  set_non_savable_lookup_slot_value(tokenizer,Qlexing_table,Nil);
      }
    POP_SPECIAL();
    return VALUES_1(patterns_definition);
}

/* COMPILE-PATTERNS-DEFINITION-FOR-SLOT */
Object compile_patterns_definition_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(188,21);
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
    if (CONSP(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* WRITE-PATTERNS-DEFINITION-FROM-SLOT */
Object write_patterns_definition_from_slot(patterns_definition,gensymed_symbol)
    Object patterns_definition, gensymed_symbol;
{
    Object name, expression, ab_loop_list_, ab_loop_desetq_, temp, aref_arg_2;

    x_note_fn_call(188,22);
    if ( !TRUEP(patterns_definition))
	return twrite_beginning_of_wide_string(array_constant_15,
		FIX((SI_Long)4L));
    else {
	name = Nil;
	expression = Nil;
	ab_loop_list_ = patterns_definition;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	expression = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	twrite_symbol(2,name,T);
	twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)3L));
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)34L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	twrite_general_string(expression);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)34L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)8232L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qpattern_name;       /* pattern-name */

static Object Qno_name;            /* no-name */

static Object Qpattern_regexp;     /* pattern-regexp */

static Object string_constant_3;   /* "no-value" */

static Object string_constant_4;   /* "~NT " */

static Object string_constant_5;   /* "~NV must be one of the following types: ~a" */

/* PATTERNS-DEFINITION-EVALUATION-SETTER */
Object patterns_definition_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, struct_1, name, regexp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(188,23);
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
		      goto end_patterns_definition_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_2)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	struct_1 = Nil;
	name = Nil;
	regexp = Nil;
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
	struct_1 = CAR(element);
	name = structure_slot_1(struct_1,Qpattern_name,Qno_name);
	regexp = structure_slot_1(struct_1,Qpattern_regexp,Qno_value);
	temp_1 = name;
	ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,SYMBOLP(regexp) ? 
		stringw(string_constant_3) : regexp),Nil);
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
		  tformat(2,string_constant_4,list_constant_2);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_5,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_patterns_definition_evaluation_setter:
    return result;
}

/* PATTERNS-DEFINITION-EVALUATION-GETTER */
Object patterns_definition_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, pattern_def, ab_loop_list_, result_1, ab_loopvar_;
    Object ab_loopvar__1, new_structure;

    x_note_fn_call(188,24);
    if ( !TRUEP(slot_value))
	temp = allocate_evaluation_sequence(Nil);
    else {
	pattern_def = Nil;
	ab_loop_list_ = slot_value;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pattern_def = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_structure = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(new_structure,Qpattern_name,
		CAR(pattern_def));
	set_evaluation_structure_slot(new_structure,Qpattern_regexp,
		copy_as_wide_string(CDR(pattern_def)));
	ab_loopvar__1 = eval_cons_1(new_structure,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(result_1);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qtokens_definition;  /* tokens-definition */

/* PUT-TOKENS-DEFINITION */
Object put_tokens_definition(tokenizer,tokens_definition,gensymed_symbol)
    Object tokenizer, tokens_definition, gensymed_symbol;
{
    Object current_lexing_strings, tokens_cons, unparsable_tokens;
    Object token_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(188,25);
    current_lexing_strings = get_lookup_slot_value_given_default(tokenizer,
	    Qpatterns_strings,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_strings,Qcurrent_lexing_strings,current_lexing_strings,
	    0);
      result = parse_tokens(tokens_definition);
      MVS_2(result,tokens_cons,unparsable_tokens);
      add_tokenizer_token_frame_notes(tokenizer,unparsable_tokens);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(tokenizer,Qtokens_definition);
      SVREF(tokenizer,FIX((SI_Long)21L)) = tokens_definition;
      reclaim_tokens_cons(get_lookup_slot_value_given_default(tokenizer,
	      Qtokens_cons,Nil),tokenizer);
      set_non_savable_lookup_slot_value(tokenizer,Qtokens_cons,tokens_cons);
      reclaim_dfa_if_any(get_lookup_slot_value_given_default(tokenizer,
	      Qlexing_table,Nil));
      if (tokens_cons &&  !TRUEP(unparsable_tokens)) {
	  update_frame_status(tokenizer,Nil,Nil);
	  tokens_cons = token_cons_1(Nil,tokens_cons);
	  set_non_savable_lookup_slot_value(tokenizer,Qlexing_table,
		  compile_lexing_table(tokens_cons));
	  token_pop_store = Nil;
	  cons_1 = tokens_cons;
	  if (cons_1) {
	      token_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qtoken);
	      if (ISVREF(Available_token_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_token_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_token_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_token_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_token_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  tokens_cons = next_cons;
      }
      else {
	  if (unparsable_tokens)
	      update_frame_status(tokenizer,Qbad,Nil);
	  else
	      update_frame_status(tokenizer,Qincomplete,Nil);
	  set_non_savable_lookup_slot_value(tokenizer,Qlexing_table,Nil);
      }
    POP_SPECIAL();
    return VALUES_1(tokens_definition);
}

/* COMPILE-TOKENS-DEFINITION-FOR-SLOT */
Object compile_tokens_definition_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(188,26);
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
    if (CONSP(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

/* WRITE-TOKENS-DEFINITION-FROM-SLOT */
Object write_tokens_definition_from_slot(tokens_definition,gensymed_symbol)
    Object tokens_definition, gensymed_symbol;
{
    Object type, expression, ab_loop_list_, ab_loop_desetq_, temp, aref_arg_2;

    x_note_fn_call(188,27);
    if ( !TRUEP(tokens_definition))
	return twrite_beginning_of_wide_string(array_constant_15,
		FIX((SI_Long)4L));
    else {
	type = Nil;
	expression = Nil;
	ab_loop_list_ = tokens_definition;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	type = CAR(ab_loop_desetq_);
	expression = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)34L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	twrite_general_string(expression);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)34L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	twrite_beginning_of_wide_string(array_constant_16,FIX((SI_Long)3L));
	twrite_symbol(2,type,T);
	if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		Total_length_of_current_wide_string))
	    extend_current_wide_string(Fill_pointer_for_current_wide_string);
	temp = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),(SI_Long)8232L);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qtoken_type;         /* token-type */

static Object Qtoken_regexp;       /* token-regexp */

static Object list_constant_5;     /* # */

/* TOKENS-DEFINITION-EVALUATION-SETTER */
Object tokens_definition_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, struct_1, name, regexp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(188,28);
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
		      goto end_tokens_definition_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_2)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	struct_1 = Nil;
	name = Nil;
	regexp = Nil;
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
	struct_1 = CAR(element);
	name = structure_slot_1(struct_1,Qtoken_type,Qno_name);
	regexp = structure_slot_1(struct_1,Qtoken_regexp,Qno_value);
	temp_1 = name;
	ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,SYMBOLP(regexp) ? 
		stringw(string_constant_3) : regexp),Nil);
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
    else if (type_specification_type_p(gensymed_symbol,list_constant_5)) {
	gensymed_symbol = evaluation_value;
	temp_1 = estructure_slot(gensymed_symbol,Qtoken_type,Nil);
	result = phrase_cons(temp_1,estructure_slot(gensymed_symbol,
		Qtoken_regexp,Nil));
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
		  tformat(2,string_constant_4,list_constant_2);
		  tformat(2,string_constant_4,list_constant_5);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_5,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_tokens_definition_evaluation_setter:
    return result;
}

/* TOKENS-DEFINITION-EVALUATION-GETTER */
Object tokens_definition_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, token_def, ab_loop_list_, result_1, ab_loopvar_;
    Object ab_loopvar__1, new_structure;

    x_note_fn_call(188,29);
    if ( !TRUEP(slot_value))
	temp = allocate_evaluation_sequence(Nil);
    else {
	token_def = Nil;
	ab_loop_list_ = slot_value;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	token_def = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_structure = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(new_structure,Qtoken_type,
		CAR(token_def));
	set_evaluation_structure_slot(new_structure,Qtoken_regexp,
		copy_as_wide_string(CDR(token_def)));
	ab_loopvar__1 = eval_cons_1(new_structure,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(result_1);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qmatch;              /* match */

static Object Qstart_index;        /* start-index */

static Object Qend_index;          /* end-index */

/* MAKE-EVALUATION-STRUCTURE-FROM-PARSE-OBJECT-RECLAIMING-IT */
Object make_evaluation_structure_from_parse_object_reclaiming_it(parse_object)
    Object parse_object;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, result_1;

    x_note_fn_call(188,30);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qtoken_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(parse_object,(SI_Long)1L);
    if (car_new_value);
    else
	car_new_value = Qmatch;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qstart_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(parse_object,(SI_Long)2L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qend_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(parse_object,(SI_Long)3L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    result_1 = allocate_evaluation_structure(gensymed_symbol);
    reclaim_parse_object_1(parse_object);
    return VALUES_1(result_1);
}

static Object Qlexeme;             /* lexeme */

/* MAKE-EVALUATION-STRUCTURE-WITH-TEXT-FROM-PARSE-OBJECT-RECLAIMING-IT */
Object make_evaluation_structure_with_text_from_parse_object_reclaiming_it(parse_object,
	    source_text)
    Object parse_object, source_text;
{
    Object start_index, end_index, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, result_1;

    x_note_fn_call(188,31);
    start_index = ISVREF(parse_object,(SI_Long)2L);
    end_index = ISVREF(parse_object,(SI_Long)3L);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qtoken_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(parse_object,(SI_Long)1L);
    if (car_new_value);
    else
	car_new_value = Qmatch;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qlexeme;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = get_from_g2_text(source_text,start_index,end_index);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qstart_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = start_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qend_index;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = end_index;
    result_1 = allocate_evaluation_structure(gensymed_symbol);
    reclaim_parse_object_1(parse_object);
    return VALUES_1(result_1);
}

void lexer_INIT()
{
    Object write_tokenizer_pattern_notes_note_1;
    Object write_tokenizer_token_notes_note_1, temp, temp_1, temp_2;
    Object patterns_definition_evaluation_setter_1;
    Object patterns_definition_evaluation_getter_1;
    Object tokens_definition_evaluation_setter_1;
    Object tokens_definition_evaluation_getter_1;
    Object AB_package, string_constant_34, Qdo_nothing, string_constant_33;
    Object string_constant_32, string_constant_31, Qab_structure, Qnamed;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, list_constant_13, Qtext;
    Object Qtype_specification_simple_expansion, Qslot_value_writer;
    Object Qwrite_tokens_definition_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_tokens_definition_for_slot;
    Object Qslot_putter, Qput_tokens_definition, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8;
    Object Qwrite_patterns_definition_from_slot, list_constant_6;
    Object Qcompile_patterns_definition_for_slot, Qput_patterns_definition;
    Object Qslot_value_reclaimer, Qreclaim_lexing_table_value;
    Object Qreclaim_tokens_cons_value, Qreclaim_patterns_strings_value;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, Qclasses_which_define, Qinitialize;
    Object Qinitialize_for_tokenizer, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, list_constant_7;
    Object Qcreate_icon_description, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, Qentity, Qitem, Qframe_note_writer_1;

    x_note_fn_call(188,32);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)57344L);
    Qbuilt_in = STATIC_SYMBOL("BUILT-IN",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)57344L);
    Qtokenizer_pattern_notes = STATIC_SYMBOL("TOKENIZER-PATTERN-NOTES",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    array_constant_12 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)33L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)43L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)45L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)46L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)47L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)48L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)49L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)50L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)52L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)54L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)55L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)56L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)57L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)62L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)63L,(SI_Long)57344L);
    string_constant = STATIC_STRING("   (~c~c) ");
    string_constant_1 = STATIC_STRING("   (~c) ");
    string_constant_2 = STATIC_STRING("~a");
    write_tokenizer_pattern_notes_note_1 = 
	    STATIC_FUNCTION(write_tokenizer_pattern_notes_note,NIL,FALSE,2,2);
    mutate_global_property(Qtokenizer_pattern_notes,
	    write_tokenizer_pattern_notes_note_1,Qframe_note_writer_1);
    array_constant_13 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)57344L);
    Qtokenizer_token_notes = STATIC_SYMBOL("TOKENIZER-TOKEN-NOTES",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)28L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)33L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)40L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)42L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)43L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)44L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)46L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)48L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)49L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)50L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)53L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)54L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)55L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)62L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)63L,(SI_Long)57344L);
    write_tokenizer_token_notes_note_1 = 
	    STATIC_FUNCTION(write_tokenizer_token_notes_note,NIL,FALSE,2,2);
    mutate_global_property(Qtokenizer_token_notes,
	    write_tokenizer_token_notes_note_1,Qframe_note_writer_1);
    Qtokenizer = STATIC_SYMBOL("TOKENIZER",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qtokenizer,list_constant_7);
    string_constant_6 = 
	    STATIC_STRING("1n1m8v83AGy1l8t1m83-Cy53ryTokenizers allow text to be broken up into smaller pieces");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_7 = 
	    STATIC_STRING("1t4z8r83--y83--y83AGy83AGy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_8 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_9 = 
	    STATIC_STRING("0004z8r83-0y83-0y83AGy83AGy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_10 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy83AGy83AGy00001q1l8l1l83Cy1m8p83-ky1l83Uy1l83*-y1m83Dy53MySee comment in class ");
    string_constant_11 = 
	    STATIC_STRING("block000004z8r8u8u83AGy83AGy01p8w9k3ky3ky1p1p83Jy1mkk1m3kyk1m3ky3ky1mk3ky1p83Jy1m3Fy3Wy1m3Fy3by1m3by3by1m3by3Wy1p83Jy1m3Fy3Ny1m3");
    string_constant_12 = 
	    STATIC_STRING("Fy3Sy1m3by3Sy1m3by3Ny1p83Jy1m3Fy3Ey1m3Fy3Jy1m3by3Jy1m3by3Ey1p83Jy1mts1mtx1m3byx1m3bys001o1l8l1l8o1l8z1m83Dy53YySee comment on EN");
    string_constant_13 = 
	    STATIC_STRING("TITY class definition000004z8r83EIy83EIy83AGy83AGy00001n1n8p83EIy83Gy1l8o1l8l000004z8r83FSy83FSy83AGy83AGy00001n1n8p83FSy83Gy1l8");
    string_constant_14 = 
	    STATIC_STRING("o1l8l000004z8r83Xhy83Xhy83AGy83AGy00001l1l8l000004z8r83cBy83cBy83AGy83AGy00001l1l8l000004z8r837Ay837Ay83AGy83AGy00001l1l8l00000");
    string_constant_15 = 
	    STATIC_STRING("1v8q1p83AGy1m83Ry83-+y1m8v83AGy8t1m83-Cy53ryTokenizers allow text to be broken up into smaller pieces1n83--y01m8p83-*y1n83-0y01m");
    string_constant_16 = 
	    STATIC_STRING("8p83-0y1o83-Fy08l83Cy1m8u1p8w9k3ky3ky1p1p83Jy1mkk1m3kyk1m3ky3ky1mk3ky1p83Jy1m3Fy3Wy1m3Fy3by1m3by3by1m3by3Wy1p83Jy1m3Fy3Ny1m3Fy3S");
    string_constant_17 = 
	    STATIC_STRING("y1m3by3Sy1m3by3Ny1p83Jy1m3Fy3Ey1m3Fy3Jy1m3by3Jy1m3by3Ey1p83Jy1mts1mtx1m3byx1m3bys1p83EIy01n8p83EIy83Gy8o8l1p83FSy01n8p83FSy83Gy8");
    string_constant_18 = STATIC_STRING("o8l1n83Xhy08l1n83cBy08l1n837Ay08l");
    temp = regenerate_optimized_constant(string_constant_6);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_7,
	    string_constant_8,string_constant_9,string_constant_10,
	    string_constant_11,string_constant_12,string_constant_13,
	    string_constant_14));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qtokenizer,list_constant_7,Nil,temp,Nil,
	    temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_4(string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18)),Nil);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qinitialize_for_tokenizer = STATIC_SYMBOL("INITIALIZE-FOR-TOKENIZER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_tokenizer,
	    STATIC_FUNCTION(initialize_for_tokenizer,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_tokenizer);
    set_get(Qtokenizer,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qtokenizer,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qlexing_table = STATIC_SYMBOL("LEXING-TABLE",AB_package);
    string_constant_19 = STATIC_STRING("1l1m83m7y83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_19));
    string_constant_20 = STATIC_STRING("1l1n83-m-y1n83-Rry83-BUy83-Rrym");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_20));
    string_constant_21 = 
	    STATIC_STRING("13Ny1m83-BUy83-lRy1n83-BUy1m83-LTy83-lRy1m83-Jgym1m83-lRy83-Jdy1n83-Jdy1n83-lUy83-Jcy83-Jdy1n83gxyln1m83-Jdy83-lUy1n83-lUy1m83-j");
    string_constant_22 = 
	    STATIC_STRING("Uy83-lUy1n83-oDylm1m83-lUy83-jUy1m83-jUy83-Kcy1m83-jUy83-c6y1n83-c6y1m83-Kcy83-c5y1m83-c4yl1n83-c6y1m83-Kcy83-jCy1m83-jCyl1n83-c");
    string_constant_23 = 
	    STATIC_STRING("6y1m83-Kcy83-l0y1m83-e2yl1m83-h+y83-BQy1m83-h+y83-YKy1m83-h+y83-n3y1n83-Kcy1n83-cMy83-lRy83-n5ym1m83-Kcy83-MAy1n83-Kcy83vHy1l83v");
    string_constant_24 = 
	    STATIC_STRING("Hy1m83-Kcy83-h+y1n83-MAy1n83-cKy83-9vy83-n3y1m83-MAym1n83-MAy1o83-cKy83-LTy83-9vy83-n3y1m83-aayn1n83-9vy83-l8y1ll1n83-9vy1m83-l8");
    string_constant_25 = 
	    STATIC_STRING("y83-9vy2llm1m83-l8y83-M9y1m83-l8y83-BQy1n83-M9y1n83-BQy83-YKy83-BQy2lln1m83-Z5y83-Z4y");
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25)));
    Qpatterns_strings = STATIC_SYMBOL("PATTERNS-STRINGS",AB_package);
    Qreclaim_patterns_strings_value = 
	    STATIC_SYMBOL("RECLAIM-PATTERNS-STRINGS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_patterns_strings_value,
	    STATIC_FUNCTION(reclaim_patterns_strings_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qpatterns_strings,
	    SYMBOL_FUNCTION(Qreclaim_patterns_strings_value),
	    Qslot_value_reclaimer);
    Qtokens_cons = STATIC_SYMBOL("TOKENS-CONS",AB_package);
    Qreclaim_tokens_cons_value = STATIC_SYMBOL("RECLAIM-TOKENS-CONS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_tokens_cons_value,
	    STATIC_FUNCTION(reclaim_tokens_cons_value,NIL,FALSE,2,2));
    mutate_global_property(Qtokens_cons,
	    SYMBOL_FUNCTION(Qreclaim_tokens_cons_value),Qslot_value_reclaimer);
    Qreclaim_lexing_table_value = 
	    STATIC_SYMBOL("RECLAIM-LEXING-TABLE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_lexing_table_value,
	    STATIC_FUNCTION(reclaim_lexing_table_value,NIL,FALSE,2,2));
    mutate_global_property(Qlexing_table,
	    SYMBOL_FUNCTION(Qreclaim_lexing_table_value),
	    Qslot_value_reclaimer);
    Qpatterns_definition = STATIC_SYMBOL("PATTERNS-DEFINITION",AB_package);
    Qtoken = STATIC_SYMBOL("TOKEN",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qput_patterns_definition = STATIC_SYMBOL("PUT-PATTERNS-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_patterns_definition,
	    STATIC_FUNCTION(put_patterns_definition,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qpatterns_definition,
	    SYMBOL_FUNCTION(Qput_patterns_definition),Qslot_putter);
    Qcompile_patterns_definition_for_slot = 
	    STATIC_SYMBOL("COMPILE-PATTERNS-DEFINITION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_patterns_definition_for_slot,
	    STATIC_FUNCTION(compile_patterns_definition_for_slot,NIL,TRUE,
	    3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qpatterns_definition,
	    SYMBOL_FUNCTION(Qcompile_patterns_definition_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qpatterns_definition,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_15 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_patterns_definition_from_slot = 
	    STATIC_SYMBOL("WRITE-PATTERNS-DEFINITION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_patterns_definition_from_slot,
	    STATIC_FUNCTION(write_patterns_definition_from_slot,NIL,FALSE,
	    2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qpatterns_definition,
	    SYMBOL_FUNCTION(Qwrite_patterns_definition_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    list_constant_2 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qpatterns_definition),
	    Qtype_specification_simple_expansion,list_constant_2);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qpattern_name = STATIC_SYMBOL("PATTERN-NAME",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qpattern_name,Qsymbol);
    Qpattern_regexp = STATIC_SYMBOL("PATTERN-REGEXP",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qpattern_regexp,Qtext);
    list_constant_10 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    list_constant_9);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qand,Qpattern_name,
	    Qpattern_regexp);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_10,list_constant_11);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_12,
	    FIX((SI_Long)0L));
    define_type_specification_explicit_complex_type(Qpatterns_definition,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qpatterns_definition);
    Qno_name = STATIC_SYMBOL("NO-NAME",AB_package);
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    string_constant_3 = STATIC_STRING("no-value");
    string_constant_4 = STATIC_STRING("~NT ");
    string_constant_5 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    patterns_definition_evaluation_setter_1 = 
	    STATIC_FUNCTION(patterns_definition_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qpatterns_definition,
	    patterns_definition_evaluation_setter_1);
    patterns_definition_evaluation_getter_1 = 
	    STATIC_FUNCTION(patterns_definition_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpatterns_definition,
	    patterns_definition_evaluation_getter_1);
    string_constant_26 = STATIC_STRING("1m1m83EIy1m9k83Zy1m83EIy83-8ny");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_26));
    string_constant_27 = 
	    STATIC_STRING("1m1n83-8ny83-8my1ll1n83-8ny1m83-8my83-8ny2llm");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    string_constant_28 = STATIC_STRING("1l1n83-8my1m83-8oy83m7y2llm");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    string_constant_29 = STATIC_STRING("1l1m83-8oy83-2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_29));
    string_constant_30 = 
	    STATIC_STRING("1m1n83-ify83-BQy1ll1n83-ify1m83-BQy83-ify2llm");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_30));
    Qtokens_definition = STATIC_SYMBOL("TOKENS-DEFINITION",AB_package);
    Qput_tokens_definition = STATIC_SYMBOL("PUT-TOKENS-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_tokens_definition,
	    STATIC_FUNCTION(put_tokens_definition,NIL,FALSE,3,3));
    mutate_global_property(Qtokens_definition,
	    SYMBOL_FUNCTION(Qput_tokens_definition),Qslot_putter);
    Qcompile_tokens_definition_for_slot = 
	    STATIC_SYMBOL("COMPILE-TOKENS-DEFINITION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_tokens_definition_for_slot,
	    STATIC_FUNCTION(compile_tokens_definition_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qtokens_definition,
	    SYMBOL_FUNCTION(Qcompile_tokens_definition_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtokens_definition,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_tokens_definition_from_slot = 
	    STATIC_SYMBOL("WRITE-TOKENS-DEFINITION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tokens_definition_from_slot,
	    STATIC_FUNCTION(write_tokens_definition_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qtokens_definition,
	    SYMBOL_FUNCTION(Qwrite_tokens_definition_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qtokens_definition),
	    Qtype_specification_simple_expansion,list_constant_2);
    Qtoken_regexp = STATIC_SYMBOL("TOKEN-REGEXP",AB_package);
    list_constant_13 = STATIC_CONS(Qtext,Qnil);
    list_constant_15 = STATIC_CONS(Qtoken_regexp,list_constant_13);
    Qtoken_type = STATIC_SYMBOL("TOKEN-TYPE",AB_package);
    list_constant_14 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_16 = STATIC_CONS(Qtoken_type,list_constant_14);
    list_constant_17 = STATIC_LIST((SI_Long)2L,list_constant_15,
	    list_constant_16);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qand,Qtoken_type,Qtoken_regexp);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_17,list_constant_18);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_19,list_constant_20);
    define_type_specification_explicit_complex_type(Qtokens_definition,
	    list_constant_4);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qtokens_definition);
    list_constant_5 = STATIC_CONS(Qab_structure,Qnil);
    tokens_definition_evaluation_setter_1 = 
	    STATIC_FUNCTION(tokens_definition_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtokens_definition,
	    tokens_definition_evaluation_setter_1);
    tokens_definition_evaluation_getter_1 = 
	    STATIC_FUNCTION(tokens_definition_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtokens_definition,
	    tokens_definition_evaluation_getter_1);
    string_constant_31 = STATIC_STRING("1m1m83FSy1m9k83Zy1m83FSy83-F5y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_31));
    string_constant_32 = 
	    STATIC_STRING("1m1n83-F5y83-F4y1ll1n83-F5y1m83-F4y83-F5y2llm");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_32));
    string_constant_33 = STATIC_STRING("1l1n83-F4y1m83m7y83-F3y2lml");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_33));
    Qdo_nothing = STATIC_SYMBOL("DO-NOTHING",AB_package);
    string_constant_34 = STATIC_STRING("1m1m83-F3y1m9k9l1m83-F3y83-2y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qdo_nothing);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_34));
    Qmatch = STATIC_SYMBOL("MATCH",AB_package);
    Qstart_index = STATIC_SYMBOL("START-INDEX",AB_package);
    Qend_index = STATIC_SYMBOL("END-INDEX",AB_package);
    Qlexeme = STATIC_SYMBOL("LEXEME",AB_package);
}
