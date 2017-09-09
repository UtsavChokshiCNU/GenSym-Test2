/* attrs.c
 * Input file:  attributes.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "attrs.h"


Object Attribute_input_item_label = UNBOUND;

Object Attribute_input_attribute_label = UNBOUND;

Object Attribute_input_value_label = UNBOUND;

Object Attribute_input_white_space = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_file_input_frame, Qattribute_file_input_frame);

static Object string_constant;     /* "Could not locate ~s in the attribute file.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-NO-LABEL-WARNING */
Object attribute_input_no_label_warning(attribute_input_label)
    Object attribute_input_label;
{
    x_note_fn_call(216,0);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant,
		attribute_input_label);
    else
	return VALUES_1(Nil);
}

static Object string_constant_1;   /* "While loading an Attribute File, missing item on line ~s.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-NO-ITEM-DATA-WARNING */
Object attribute_input_no_item_data_warning(input_line)
    Object input_line;
{
    x_note_fn_call(216,1);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_1,input_line);
    else
	return VALUES_1(Nil);
}

static Object string_constant_2;   /* "While loading an Attribute File, missing attribute on line ~s.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-NO-ATTRIBUTE-DATA-WARNING */
Object attribute_input_no_attribute_data_warning(input_line)
    Object input_line;
{
    x_note_fn_call(216,2);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_2,input_line);
    else
	return VALUES_1(Nil);
}

static Object string_constant_3;   /* "While loading an Attribute File, missing value on line ~s.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-NO-VALUE-DATA-WARNING */
Object attribute_input_no_value_data_warning(input_line)
    Object input_line;
{
    x_note_fn_call(216,3);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_3,input_line);
    else
	return VALUES_1(Nil);
}

static Object string_constant_4;   /* "While loading an Attribute File, could not parse the text ~s.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-TEXT-PARSING-ERROR */
Object attribute_input_text_parsing_error(unparsable_text)
    Object unparsable_text;
{
    x_note_fn_call(216,4);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_4,
		unparsable_text);
    else
	return VALUES_1(Nil);
}

static Object string_constant_5;   /* "While loading an Attribute File, could not read the text beginning with ~
				    *      ~s.  An invalid character follows the text.  ~
				    *      Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-TEXT-BAD-CHAR-ERROR */
Object attribute_input_text_bad_char_error(gensym_string)
    Object gensym_string;
{
    x_note_fn_call(216,5);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_5,
		gensym_string);
    else
	return VALUES_1(Nil);
}

static Object string_constant_6;   /* "While loading an Attribute File, the item `~ND' ~
				    *        does not exist.  Attempting to process the remainder of the ~
				    *        file."
				    */

static Object Qattribute_file_item_designation;  /* attribute-file-item-designation */

/* ATTRIBUTE-INPUT-NON-EXISTENT-FRAME-WARNING */
Object attribute_input_non_existent_frame_warning()
{
    x_note_fn_call(216,6);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_6,
		get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file_item_designation,Nil));
    else
	return VALUES_1(Nil);
}

static Object string_constant_7;   /* "While loading an Attribute File, ~NC does not specify an item.  ~
				    *        Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-TEMPORARY-CONSTANT-FRAME-WARNING */
Object attribute_input_temporary_constant_frame_warning(temporary_constant)
    Object temporary_constant;
{
    Object managed_number_or_value, temp;

    x_note_fn_call(216,7);
    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
	managed_number_or_value = ISVREF(temporary_constant,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp = copy_text_string(managed_number_or_value);
	else
	    temp = managed_number_or_value;
	return give_warning_1(4,FIX((SI_Long)1L),string_constant_7,temp,
		ISVREF(temporary_constant,(SI_Long)2L));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_8;   /* "While loading an Attribute File, an invalid attribute name, ~s, has been ~
				    *      read.  Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-INVALID-SLOT-NAME-WARNING */
Object attribute_input_invalid_slot_name_warning(illegal_slot_name)
    Object illegal_slot_name;
{
    x_note_fn_call(216,8);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_8,
		illegal_slot_name);
    else
	return VALUES_1(Nil);
}

static Object string_constant_9;   /* "While loading an Attribute File, an illegal attribute value, ~s, has ~
				    *      been read.  Attempting to process the remainder of the file."
				    */

/* ATTRIBUTE-INPUT-INVALID-SLOT-VALUE-WARNING */
Object attribute_input_invalid_slot_value_warning(slot_value_string)
    Object slot_value_string;
{
    x_note_fn_call(216,9);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_9,
		slot_value_string);
    else
	return VALUES_1(Nil);
}

static Object string_constant_10;  /* "Error recovery.  Skipping input line: ~s." */

/* ATTRIBUTE-INPUT-ERROR-RECOVERY-IGNORE-WARNING */
Object attribute_input_error_recovery_ignore_warning(input_string)
    Object input_string;
{
    x_note_fn_call(216,10);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_10,
		input_string);
    else
	return VALUES_1(Nil);
}

static Object string_constant_11;  /* "Cannot read from the Attribute File ~s: ~a.  The file is being closed." */

static Object string_constant_12;  /* "Cannot read from an Attribute File: ~a.  The file is being closed." */

static Object Qattribute_file;     /* attribute-file */

/* ATTRIBUTE-INPUT-READ-ERROR */
Object attribute_input_read_error()
{
    Object error_text, temp;

    x_note_fn_call(216,11);
    error_text = most_recent_file_operation_status_as_text();
    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
	temp = Attribute_file_input_frame ? string_constant_11 : 
		string_constant_12;
	give_warning_1(4,FIX((SI_Long)1L),temp,Attribute_file_input_frame ?
		 
		get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file,Nil) : error_text,error_text);
    }
    return reclaim_text_string(error_text);
}

static Object string_constant_13;  /* "Could not open the attribute file ~s." */

static Object string_constant_14;  /* "Could not open the Attribute File." */

/* ATTRIBUTE-INPUT-CAN-NOT-OPEN-FILE-ERROR */
Object attribute_input_can_not_open_file_error()
{
    Object temp;

    x_note_fn_call(216,12);
    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
	temp = Attribute_file_input_frame ? string_constant_13 : 
		string_constant_14;
	return give_warning_1(3,FIX((SI_Long)1L),temp,
		Attribute_file_input_frame ? 
		get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file,Nil) : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_15;  /* "While loading the Attribute File ~s, an unexpected end-of-file occurred." */

static Object string_constant_16;  /* "While loading the Attribute File, an unexpected end-of-file occurred." */

/* ATTRIBUTE-INPUT-END-OF-FILE-WARNING */
Object attribute_input_end_of_file_warning()
{
    Object temp;

    x_note_fn_call(216,13);
    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
	temp = Attribute_file_input_frame ? string_constant_15 : 
		string_constant_16;
	return give_warning_1(3,FIX((SI_Long)1L),temp,
		Attribute_file_input_frame ? 
		get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file,Nil) : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qattribute_file_line;  /* attribute-file-line */

/* G2-STREAM-READ-LINE-FOR-ATTRIBUTE-FILE */
Object g2_stream_read_line_for_attribute_file(stream)
    Object stream;
{
    Object text_string_qm, gensym_string, legal_gensym_string_p_qm;
    Object illegal_gensym_string_char_index_qm, temp;
    Object gensym_string_substring_1;
    Object result;

    x_note_fn_call(216,14);
    text_string_qm = g2_stream_read_line(stream);
    if ( !TRUEP(text_string_qm))
	return VALUES_1(Nil);
    else {
	gensym_string = wide_string_to_string(text_string_qm);
	result = legal_gensym_string_p(1,gensym_string);
	MVS_2(result,legal_gensym_string_p_qm,
		illegal_gensym_string_char_index_qm);
	if ( !TRUEP(legal_gensym_string_p_qm)) {
	    temp = illegal_gensym_string_char_index_qm;
	    if (temp);
	    else
		temp = gensym_string_length(gensym_string);
	    gensym_string_substring_1 = 
		    gensym_string_substring(gensym_string,FIX((SI_Long)0L),
		    temp);
	    attribute_input_text_bad_char_error(gensym_string_substring_1);
	    reclaim_gensym_string(gensym_string_substring_1);
	    return VALUES_1(Nil);
	}
	else {
	    temp = import_text_string(2,gensym_string,Qattribute_file_line);
	    reclaim_text_string(text_string_qm);
	    reclaim_gensym_string(gensym_string);
	    return VALUES_1(temp);
	}
    }
}

/* ATTRIBUTE-INPUT-FIND-NON-WHITE-SPACE */
Object attribute_input_find_non_white_space varargs_1(int, n)
{
    Object string_1;
    Object start, end_1, i, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(216,15);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)0L);
    end_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    i = start;
    if (end_1) {
	temp = text_string_length(string_1);
	end_1 = FIXNUM_MIN(temp,end_1);
    }
    else
	end_1 = text_string_length(string_1);
  next_loop:
    if (FIXNUM_GE(i,end_1) ||  
	    !TRUEP(wide_character_member(FIX(UBYTE_16_ISAREF_1(string_1,
	    IFIX(i))),Attribute_input_white_space)))
	goto end_loop;
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    if (FIXNUM_GE(i,end_1))
	return VALUES_1(Nil);
    else
	return VALUES_1(i);
    return VALUES_1(Qnil);
}

/* LOCATE-ATTRIBUTE-INPUT-LABEL */
Object locate_attribute_input_label(input_string,label_string)
    Object input_string, label_string;
{
    Object start_index, end_index, label_length, end1, end2, length2;
    Object ab_loop_iter_flag_, temp, temp_1;
    SI_Long length1, index1, ab_loop_bind_, index2, ab_loop_bind__1, code;
    char temp_2;

    x_note_fn_call(216,16);
    start_index = attribute_input_find_non_white_space(1,input_string);
    end_index = text_string_length(input_string);
    label_length = text_string_length(label_string);
    if (FIXNUM_LE(label_length,FIXNUM_MINUS(end_index,start_index))) {
	end1 = text_string_length(label_string);
	end2 = FIXNUM_ADD(start_index,label_length);
	length1 = IFIX(end1) - (SI_Long)0L;
	length2 = FIXNUM_MINUS(end2,start_index);
	if (length1 == IFIX(length2)) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(end1);
	    index2 = IFIX(start_index);
	    ab_loop_bind__1 = IFIX(end2);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (index1 >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index2 = index2 + (SI_Long)1L;
	    if (index2 >= ab_loop_bind__1)
		goto end_loop;
	    code = UBYTE_16_ISAREF_1(label_string,index1);
	    if (code < (SI_Long)127L)
		temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp = unicode_lowercase_if_uppercase(FIX(code));
		if (temp);
		else
		    temp = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(input_string,index2);
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    if ( !NUM_EQ(temp,temp_1)) {
		temp_2 = TRUEP(Nil);
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp_2 = TRUEP(T);
	    goto end_1;
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    return VALUES_1(FIXNUM_ADD(start_index,label_length));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* READ-COMPLETE-ATTRIBUTE-INPUT-VALUE */
Object read_complete_attribute_input_value(input_line,input_stream)
    Object input_line, input_stream;
{
    Object fatal_error_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ends_with_newline_qm, new_input_line_qm, temp, schar_arg_2;
    Object schar_new_value, value_string_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    Declare_special(5);

    x_note_fn_call(216,17);
    fatal_error_qm = Nil;
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
	      ends_with_newline_qm = twrite_string_as_input_line(2,
		      input_line,Nil);
	      new_input_line_qm = Nil;
	    next_loop:
	      new_input_line_qm = 
		      g2_stream_read_line_for_attribute_file(input_stream);
	      if ( !TRUEP(new_input_line_qm) ||  
		      !TRUEP(attribute_input_find_non_white_space(1,
		      new_input_line_qm)))
		  goto end_loop;
	      if ( !TRUEP(ends_with_newline_qm)) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)32L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)32L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
	      }
	      ends_with_newline_qm = twrite_string_as_input_line(2,
		      new_input_line_qm, !TRUEP(ends_with_newline_qm) ? T :
		       Nil);
	      reclaim_text_string(new_input_line_qm);
	      goto next_loop;
	    end_loop:
	      if ( !TRUEP(new_input_line_qm) &&  
		      !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		      End_of_file_reached_code))
		  fatal_error_qm = T;
	      else if (new_input_line_qm)
		  reclaim_text_string(new_input_line_qm);
	      value_string_qm = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (fatal_error_qm) {
	attribute_input_read_error();
	if (text_string_p(value_string_qm))
	    reclaim_text_string(value_string_qm);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(value_string_qm);
}

/* TWRITE-STRING-AS-INPUT-LINE */
Object twrite_string_as_input_line varargs_1(int, n)
{
    Object input_line;
    Object skip_initial_whitespace_qm, string_length, past_whitespace_qm;
    Object char_1, last_char_qm, temp_1, schar_arg_2, schar_new_value, thing_1;
    SI_Long i, temp, ab_loop_repeat_, thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(216,18);
    INIT_ARGS_nonrelocating();
    input_line = REQUIRED_ARG_nonrelocating();
    skip_initial_whitespace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    string_length = text_string_length(input_line);
    past_whitespace_qm = Nil;
    char_1 = Nil;
    last_char_qm = Nil;
    i = (SI_Long)0L;
  next_loop:
    if (i == IFIX(string_length)) {
	if (last_char_qm && newline_p(last_char_qm))
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
    char_1 = FIX(UBYTE_16_ISAREF_1(input_line,i));
    if (skip_initial_whitespace_qm &&  !TRUEP(past_whitespace_qm) &&  
	    !TRUEP(wide_character_member(char_1,Attribute_input_white_space)))
	past_whitespace_qm = T;
    if (skip_initial_whitespace_qm &&  !TRUEP(past_whitespace_qm));
    else if (IFIX(char_1) == (SI_Long)9L) {
	temp = IFIX(ISVREF(Editor_parameters,(SI_Long)25L));
	ab_loop_repeat_ = MAX(temp,(SI_Long)1L);
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)32L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)32L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
	goto next_loop_1;
      end_loop:;
    }
    else if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = char_1;
	twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) : 
		thing_1);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = char_1;
	schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    last_char_qm = char_1;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object string_constant_17;  /* "Error recovery.  Skipping ~d input line~a." */

static Object string_constant_18;  /* "" */

static Object string_constant_19;  /* "s" */

/* READ-IGNORE-AND-DISPLAY-COMPLETE-ATTRIBUTE-INPUT-VALUE */
Object read_ignore_and_display_complete_attribute_input_value(input_line_qm,
	    input_stream)
    Object input_line_qm, input_stream;
{
    Object new_input_line_qm, line_count, ab_loop_iter_flag_;

    x_note_fn_call(216,19);
    attribute_input_error_recovery_ignore_warning(input_line_qm);
    new_input_line_qm = Nil;
    line_count = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
  next_loop:
    new_input_line_qm = g2_stream_read_line_for_attribute_file(input_stream);
    if ( !TRUEP(ab_loop_iter_flag_))
	line_count = FIXNUM_ADD1(line_count);
    if ( !TRUEP(new_input_line_qm) ||  
	    !TRUEP(attribute_input_find_non_white_space(1,new_input_line_qm)))
	goto end_loop;
    reclaim_text_string(new_input_line_qm);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (IFIX(line_count) > (SI_Long)0L) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)1L),string_constant_17,
		    line_count,IFIX(line_count) == (SI_Long)1L ? 
		    string_constant_18 : string_constant_19);
	Suppress_warning_message_header_qm = Nil;
    }
    if ( !TRUEP(new_input_line_qm) &&  
	    !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    End_of_file_reached_code)) {
	attribute_input_read_error();
	return VALUES_1(Nil);
    }
    else {
	if (new_input_line_qm)
	    reclaim_text_string(new_input_line_qm);
	return VALUES_1(T);
    }
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* PROCESS-ATTRIBUTE-INPUT-ITEM */
Object process_attribute_input_item(input_string,starting_index_qm)
    Object input_string, starting_index_qm;
{
    Object temp, current_index_qm, temp_1, unparsable_text;
    Object current_computation_flags, current_computation_frame, item_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(216,20);
    temp = starting_index_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    current_index_qm = attribute_input_find_non_white_space(2,input_string,
	    temp);
    if ( !TRUEP(current_index_qm)) {
	attribute_input_no_item_data_warning(input_string);
	return VALUES_1(Nil);
    }
    else {
	if (get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file_item_designation,Nil)) {
	    reclaim_slot_value(get_lookup_slot_value_given_default(Attribute_file_input_frame,
		    Qattribute_file_item_designation,Nil));
	    set_non_savable_lookup_slot_value(Attribute_file_input_frame,
		    Qattribute_file_item_designation,Nil);
	}
	temp = 
		convert_text_string_to_text(text_string_substring(input_string,
		current_index_qm,text_string_length(input_string)));
	temp_1 = Attribute_file_input_frame;
	if ( !TRUEP(parse_text_for_slot(3,temp,temp_1,
		get_slot_description_of_class_description_function(Qattribute_file_item_designation,
		ISVREF(Attribute_file_input_frame,(SI_Long)1L),Nil)))) {
	    unparsable_text = text_string_substring(input_string,
		    current_index_qm,text_string_length(input_string));
	    attribute_input_text_parsing_error(unparsable_text);
	    reclaim_text_string(unparsable_text);
	    return VALUES_1(Nil);
	}
	else {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    1);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	      current_computation_frame = Attribute_file_input_frame;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		item_qm = 
			evaluate_designation(get_lookup_slot_value_given_default(Attribute_file_input_frame,
			Qattribute_file_item_designation,Nil),Nil);
		if ( !TRUEP(item_qm)) {
		    attribute_input_non_existent_frame_warning();
		    result = VALUES_1(Nil);
		}
		else if (SIMPLE_VECTOR_P(item_qm) && EQ(ISVREF(item_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			    {
		    attribute_input_temporary_constant_frame_warning(item_qm);
		    reclaim_temporary_constant_1(item_qm);
		    item_qm = Nil;
		    result = VALUES_1(Nil);
		}
		else
		    result = VALUES_1(item_qm);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
}

/* PROCESS-ATTRIBUTE-NAME-FOR-ATTRIBUTE-INPUT-IF-LEGAL */
Object process_attribute_name_for_attribute_input_if_legal(input_string,
	    frame,starting_index_qm)
    Object input_string, frame, starting_index_qm;
{
    Object temp, current_index_qm, class_qualifier_qm, attribute_name_qm;
    Object temp_1, gensymed_symbol, gensymed_symbol_1, slot_description_qm;
    Object result;

    x_note_fn_call(216,21);
    temp = starting_index_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    current_index_qm = attribute_input_find_non_white_space(2,input_string,
	    temp);
    class_qualifier_qm = Nil;
    attribute_name_qm = Nil;
    if ( !TRUEP(current_index_qm)) {
	attribute_input_no_attribute_data_warning(input_string);
	return VALUES_1(Nil);
    }
    else {
	result = read_attribute_name_from_text_string_1(input_string,
		current_index_qm,Nil);
	MVS_3(result,gensymed_symbol,temp,gensymed_symbol_1);
	class_qualifier_qm = gensymed_symbol_1;
	attribute_name_qm = gensymed_symbol;
	if ( !TRUEP(attribute_name_qm)) {
	    attribute_input_text_parsing_error(input_string);
	    return VALUES_1(Nil);
	}
	else {
	    slot_description_qm = 
		    get_slot_description_if_editable_attribute(frame,
		    attribute_name_qm,class_qualifier_qm);
	    if ( !TRUEP(slot_description_qm)) {
		attribute_input_invalid_slot_name_warning(attribute_name_qm);
		return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(slot_description_qm);
	}
    }
}

/* PROCESS-ATTRIBUTE-INPUT-VALUE */
Object process_attribute_input_value(input_string,input_stream,frame,
	    slot_description,starting_index_qm)
    Object input_string, input_stream, frame, slot_description;
    Object starting_index_qm;
{
    Object temp, current_index_qm, first_value_input_line;
    Object complete_value_text_string_qm;

    x_note_fn_call(216,22);
    temp = starting_index_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    current_index_qm = attribute_input_find_non_white_space(2,input_string,
	    temp);
    if ( !TRUEP(current_index_qm)) {
	attribute_input_no_value_data_warning(input_string);
	return VALUES_1(Nil);
    }
    else {
	first_value_input_line = text_string_substring(input_string,
		current_index_qm,text_string_length(input_string));
	complete_value_text_string_qm = 
		read_complete_attribute_input_value(first_value_input_line,
		input_stream);
	reclaim_text_string(first_value_input_line);
	if ( !TRUEP(complete_value_text_string_qm))
	    return VALUES_1(Nil);
	else if ( !TRUEP(parse_text_for_slot(3,
		convert_text_string_to_text(text_string_substring(complete_value_text_string_qm,
		FIX((SI_Long)0L),
		text_string_length(complete_value_text_string_qm))),frame,
		slot_description))) {
	    attribute_input_invalid_slot_value_warning(complete_value_text_string_qm);
	    reclaim_text_string(complete_value_text_string_qm);
	    return VALUES_1(Nil);
	}
	else {
	    reclaim_text_string(complete_value_text_string_qm);
	    return VALUES_1(T);
	}
    }
}

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object Qattribute_file_input;  /* attribute-file-input */

/* LOAD-ATTRIBUTE-FILE */
Object load_attribute_file(gensym_pathname_1)
    Object gensym_pathname_1;
{
    Object input_file_qm, input_stream_qm, input_line_qm, input_result_qm;
    Object index_after_label_qm, item_qm, slot_description_qm;
    Object value_processed_p_qm, fatal_error_qm, non_fatal_error_qm, eof_qm;

    x_note_fn_call(216,23);
    input_file_qm = SIMPLE_VECTOR_P(gensym_pathname_1) && 
	    EQ(ISVREF(gensym_pathname_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
	    gensym_namestring(1,gensym_pathname_1) : Nil;
    input_stream_qm = input_file_qm && text_string_p(input_file_qm) ? 
	    g2_stream_open_for_input(input_file_qm) : Nil;
    if ( !TRUEP(input_stream_qm)) {
	attribute_input_can_not_open_file_error();
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(input_file_qm) != (SI_Long)0L)
	    reclaim_wide_string(input_file_qm);
	return VALUES_1(Nil);
    }
    else {
	input_line_qm = 
		g2_stream_read_line_for_attribute_file(input_stream_qm);
	input_result_qm = Nil;
	index_after_label_qm = Nil;
	item_qm = Nil;
	slot_description_qm = Nil;
	value_processed_p_qm = Nil;
	fatal_error_qm = Nil;
	non_fatal_error_qm = Nil;
	eof_qm = Nil;
	Attribute_file_input_frame = make_frame(Qattribute_file_input);
	set_non_savable_lookup_slot_value(Attribute_file_input_frame,
		Qattribute_file,input_file_qm);
      next_loop:
	if ( !TRUEP(input_line_qm)) {
	    if (FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		    End_of_file_reached_code)) {
		if ( !TRUEP(non_fatal_error_qm) &&  
			!TRUEP(value_processed_p_qm)) {
		    attribute_input_end_of_file_warning();
		    fatal_error_qm = T;
		}
		else
		    eof_qm = T;
	    }
	    else {
		attribute_input_read_error();
		fatal_error_qm = T;
	    }
	}
	else if ( !TRUEP(attribute_input_find_non_white_space(1,
		input_line_qm)));
	else if (non_fatal_error_qm) {
	    index_after_label_qm = 
		    locate_attribute_input_label(input_line_qm,
		    Attribute_input_item_label);
	    if (index_after_label_qm) {
		input_result_qm = 
			process_attribute_input_item(input_line_qm,
			index_after_label_qm);
		if ( !TRUEP(input_result_qm))
		    non_fatal_error_qm = T;
		else {
		    item_qm = input_result_qm;
		    non_fatal_error_qm = Nil;
		    slot_description_qm = Nil;
		    value_processed_p_qm = Nil;
		}
	    }
	    else if (locate_attribute_input_label(input_line_qm,
		    Attribute_input_value_label)) {
		if ( 
			!TRUEP(read_ignore_and_display_complete_attribute_input_value(input_line_qm,
			input_stream_qm)))
		    fatal_error_qm = T;
	    }
	    else
		attribute_input_error_recovery_ignore_warning(input_line_qm);
	}
	else if (value_processed_p_qm) {
	    index_after_label_qm = 
		    locate_attribute_input_label(input_line_qm,
		    Attribute_input_attribute_label);
	    if (index_after_label_qm) {
		input_result_qm = 
			process_attribute_name_for_attribute_input_if_legal(input_line_qm,
			item_qm,index_after_label_qm);
		if ( !TRUEP(input_result_qm))
		    non_fatal_error_qm = T;
		else {
		    slot_description_qm = input_result_qm;
		    value_processed_p_qm = Nil;
		}
	    }
	    else {
		index_after_label_qm = 
			locate_attribute_input_label(input_line_qm,
			Attribute_input_item_label);
		if (index_after_label_qm) {
		    input_result_qm = 
			    process_attribute_input_item(input_line_qm,
			    index_after_label_qm);
		    if ( !TRUEP(input_result_qm))
			non_fatal_error_qm = T;
		    else {
			item_qm = input_result_qm;
			slot_description_qm = Nil;
			value_processed_p_qm = Nil;
		    }
		}
		else {
		    non_fatal_error_qm = T;
		    attribute_input_no_label_warning(Attribute_input_item_label);
		}
	    }
	}
	else if (slot_description_qm) {
	    index_after_label_qm = 
		    locate_attribute_input_label(input_line_qm,
		    Attribute_input_value_label);
	    if (index_after_label_qm) {
		input_result_qm = 
			process_attribute_input_value(input_line_qm,
			input_stream_qm,item_qm,slot_description_qm,
			index_after_label_qm);
		if ( !TRUEP(input_result_qm))
		    non_fatal_error_qm = T;
		else
		    value_processed_p_qm = input_result_qm;
	    }
	    else {
		non_fatal_error_qm = T;
		attribute_input_no_label_warning(Attribute_input_value_label);
	    }
	}
	else if (item_qm) {
	    index_after_label_qm = 
		    locate_attribute_input_label(input_line_qm,
		    Attribute_input_attribute_label);
	    if (index_after_label_qm) {
		input_result_qm = 
			process_attribute_name_for_attribute_input_if_legal(input_line_qm,
			item_qm,index_after_label_qm);
		if ( !TRUEP(input_result_qm))
		    non_fatal_error_qm = T;
		else
		    slot_description_qm = input_result_qm;
	    }
	    else {
		non_fatal_error_qm = T;
		attribute_input_no_label_warning(Attribute_input_attribute_label);
	    }
	}
	else {
	    index_after_label_qm = 
		    locate_attribute_input_label(input_line_qm,
		    Attribute_input_item_label);
	    if (index_after_label_qm) {
		input_result_qm = 
			process_attribute_input_item(input_line_qm,
			index_after_label_qm);
		if ( !TRUEP(input_result_qm))
		    non_fatal_error_qm = T;
		else
		    item_qm = input_result_qm;
	    }
	    else {
		non_fatal_error_qm = T;
		attribute_input_no_label_warning(Attribute_input_item_label);
	    }
	}
	if (fatal_error_qm || eof_qm)
	    goto end_loop;
	if (input_line_qm)
	    reclaim_text_string(input_line_qm);
	input_line_qm = 
		g2_stream_read_line_for_attribute_file(input_stream_qm);
	goto next_loop;
      end_loop:
	if (text_string_p(input_line_qm))
	    reclaim_text_string(input_line_qm);
	if (input_stream_qm)
	    g2_stream_close(input_stream_qm);
	if (get_lookup_slot_value_given_default(Attribute_file_input_frame,
		Qattribute_file_item_designation,Nil)) {
	    reclaim_slot_value(get_lookup_slot_value_given_default(Attribute_file_input_frame,
		    Qattribute_file_item_designation,Nil));
	    set_non_savable_lookup_slot_value(Attribute_file_input_frame,
		    Qattribute_file_item_designation,Nil);
	}
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(input_file_qm) != (SI_Long)0L)
	    reclaim_wide_string(input_file_qm);
	set_non_savable_lookup_slot_value(Attribute_file_input_frame,
		Qattribute_file,Nil);
	delete_frame(Attribute_file_input_frame);
	if (fatal_error_qm)
	    return VALUES_1(Nil);
	else if (eof_qm)
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
}

void attributes_INIT()
{
    Object temp, temp_1;
    Object Qload_attribute_file, AB_package;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qattributes;
    Object string_constant_22, list_constant_2, string_constant_21;
    Object string_constant_20, list_constant_1, Qattribute_input_white_space;
    Object array_constant_2, Qattribute_input_value_label, list_constant;
    Object array_constant_1, Qattribute_input_attribute_label, array_constant;
    Object Qattribute_input_item_label;

    x_note_fn_call(216,24);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qattribute_input_item_label = 
	    STATIC_SYMBOL("ATTRIBUTE-INPUT-ITEM-LABEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_input_item_label,
	    Attribute_input_item_label);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qattribute_input_item_label,array_constant);
    Qattribute_input_attribute_label = 
	    STATIC_SYMBOL("ATTRIBUTE-INPUT-ATTRIBUTE-LABEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_input_attribute_label,
	    Attribute_input_attribute_label);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qattribute_input_attribute_label,array_constant_1);
    Qattribute_input_value_label = 
	    STATIC_SYMBOL("ATTRIBUTE-INPUT-VALUE-LABEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_input_value_label,
	    Attribute_input_value_label);
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qattribute_input_value_label,array_constant_2);
    Qattribute_input_white_space = 
	    STATIC_SYMBOL("ATTRIBUTE-INPUT-WHITE-SPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_input_white_space,
	    Attribute_input_white_space);
    list_constant_1 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L),FIX((SI_Long)13L));
    SET_SYMBOL_VALUE(Qattribute_input_white_space,list_constant_1);
    Qattribute_file_input = STATIC_SYMBOL("ATTRIBUTE-FILE-INPUT",AB_package);
    list_constant_2 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qattribute_file_input,
	    list_constant_2);
    string_constant_20 = STATIC_STRING("0");
    string_constant_21 = 
	    STATIC_STRING("1m4z8r83Gpy83Gpy83Goy83Goy00001o1l8l1l83Ey1m8p833ny1l83Hy000004z8r83Gny83Gny83Goy83Goy00001o1l8l1l83Ey1l83Ny1l83Hy00000");
    string_constant_22 = 
	    STATIC_STRING("1o8q1m83Goy1l9k1p83Gpy083Ey1m8p833ny83Hy1p83Gny083Ey83Ny83Hy");
    temp = regenerate_optimized_constant(string_constant_20);
    temp_1 = regenerate_optimized_constant(string_constant_21);
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qattribute_file_input,list_constant_2,Nil,
	    temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_22),Nil);
    Qattribute_file_input_frame = 
	    STATIC_SYMBOL("ATTRIBUTE-FILE-INPUT-FRAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_file_input_frame,
	    Attribute_file_input_frame);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    record_system_variable(Qattribute_file_input_frame,Qattributes,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    string_constant = 
	    STATIC_STRING("Could not locate ~s in the attribute file.  ~\n     Attempting to process the remainder of the file.");
    string_constant_1 = 
	    STATIC_STRING("While loading an Attribute File, missing item on line ~s.  ~\n     Attempting to process the remainder of the file.");
    string_constant_2 = 
	    STATIC_STRING("While loading an Attribute File, missing attribute on line ~s.  ~\n     Attempting to process the remainder of the file.");
    string_constant_3 = 
	    STATIC_STRING("While loading an Attribute File, missing value on line ~s.  ~\n     Attempting to process the remainder of the file.");
    string_constant_4 = 
	    STATIC_STRING("While loading an Attribute File, could not parse the text ~s.  ~\n     Attempting to process the remainder of the file.");
    string_constant_5 = 
	    string_append2(STATIC_STRING("While loading an Attribute File, could not read the text beginning with ~\n     ~s.  An invalid character follows the text.  ~\n     Attempting to process the remainder of the f"),
	    STATIC_STRING("ile."));
    string_constant_6 = 
	    STATIC_STRING("While loading an Attribute File, the item `~ND\' ~\n       does not exist.  Attempting to process the remainder of the ~\n       file.");
    Qattribute_file_item_designation = 
	    STATIC_SYMBOL("ATTRIBUTE-FILE-ITEM-DESIGNATION",AB_package);
    string_constant_7 = 
	    STATIC_STRING("While loading an Attribute File, ~NC does not specify an item.  ~\n       Attempting to process the remainder of the file.");
    string_constant_8 = 
	    STATIC_STRING("While loading an Attribute File, an invalid attribute name, ~s, has been ~\n     read.  Attempting to process the remainder of the file.");
    string_constant_9 = 
	    STATIC_STRING("While loading an Attribute File, an illegal attribute value, ~s, has ~\n     been read.  Attempting to process the remainder of the file.");
    string_constant_10 = 
	    STATIC_STRING("Error recovery.  Skipping input line: ~s.");
    string_constant_11 = 
	    STATIC_STRING("Cannot read from the Attribute File ~s: ~a.  The file is being closed.");
    string_constant_12 = 
	    STATIC_STRING("Cannot read from an Attribute File: ~a.  The file is being closed.");
    Qattribute_file = STATIC_SYMBOL("ATTRIBUTE-FILE",AB_package);
    string_constant_13 = 
	    STATIC_STRING("Could not open the attribute file ~s.");
    string_constant_14 = STATIC_STRING("Could not open the Attribute File.");
    string_constant_15 = 
	    STATIC_STRING("While loading the Attribute File ~s, an unexpected end-of-file occurred.");
    string_constant_16 = 
	    STATIC_STRING("While loading the Attribute File, an unexpected end-of-file occurred.");
    Qattribute_file_line = STATIC_SYMBOL("ATTRIBUTE-FILE-LINE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_17 = 
	    STATIC_STRING("Error recovery.  Skipping ~d input line~a.");
    string_constant_18 = STATIC_STRING("");
    string_constant_19 = STATIC_STRING("s");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qload_attribute_file = STATIC_SYMBOL("LOAD-ATTRIBUTE-FILE",AB_package);
    SET_SYMBOL_FUNCTION(Qload_attribute_file,
	    STATIC_FUNCTION(load_attribute_file,NIL,FALSE,1,1));
}
