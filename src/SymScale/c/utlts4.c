/* utlts4.c
 * Input file:  utilities4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts4.h"


/* TEXT-STRING-SEARCH */
Object text_string_search(text_to_seek,source_text,source_start_qm,
	    source_end_qm)
    Object text_to_seek, source_text, source_start_qm, source_end_qm;
{
    Object length_1, source_length, source_limit, source_anchor, character_1;
    Object source_character, temp_1, index_1, source_index, code, temp_2;
    SI_Long temp;
    char temp_3;

    x_note_fn_call(33,0);
    length_1 = text_string_length(text_to_seek);
    source_length = text_string_length(source_text);
    if (source_end_qm) {
	temp = IFIX(FIXNUM_MIN(source_length,source_end_qm));
	source_limit = FIX(MAX((SI_Long)0L,temp));
    }
    else
	source_limit = source_length;
    if (source_start_qm) {
	temp = MAX((SI_Long)0L,IFIX(source_start_qm));
	source_anchor = FIX(MIN(IFIX(source_limit),temp));
    }
    else
	source_anchor = FIX((SI_Long)0L);
    character_1 = Nil;
    source_character = Nil;
    if (FIXNUM_EQ(source_limit,source_anchor) ||  !TRUEP(text_to_seek)) {
	temp_1 = Nil;
	goto end_1;
    }
  next_loop:
    if (FIXNUM_GE(source_anchor,source_limit))
	goto end_loop;
    index_1 = FIX((SI_Long)0L);
    source_index = source_anchor;
  next_loop_1:
    temp_1 = FIX(UBYTE_16_ISAREF_1(text_to_seek,IFIX(index_1)));
    index_1 = FIXNUM_ADD1(index_1);
    character_1 = temp_1;
    temp_1 = FIX(UBYTE_16_ISAREF_1(source_text,IFIX(source_index)));
    source_index = FIXNUM_ADD1(source_index);
    source_character = temp_1;
    code = character_1;
    if (IFIX(code) < (SI_Long)127L)
	temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_1 = unicode_lowercase_if_uppercase(code);
	if (temp_1);
	else
	    temp_1 = code;
    }
    code = source_character;
    if (IFIX(code) < (SI_Long)127L)
	temp_2 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_2 = unicode_lowercase_if_uppercase(code);
	if (temp_2);
	else
	    temp_2 = code;
    }
    if ( !NUM_EQ(temp_1,temp_2)) {
	temp_3 = TRUEP(Nil);
	goto end_2;
    }
    if (FIXNUM_GE(index_1,length_1))
	goto end_loop_1;
    if (FIXNUM_GE(source_index,source_limit))
	return VALUES_1(Nil);
    goto next_loop_1;
  end_loop_1:
    temp_3 = TRUEP(T);
    goto end_2;
    temp_3 = TRUEP(Qnil);
  end_2:;
    if (temp_3) {
	temp_1 = source_anchor;
	goto end_1;
    }
    source_anchor = FIXNUM_ADD1(source_anchor);
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* G2-TEXT-CHARACTER-SEARCH */
Object g2_text_character_search(character_to_seek,source_text)
    Object character_to_seek, source_text;
{
    Object source_length, source_index, source_character, temp, code, temp_1;

    x_note_fn_call(33,1);
    if (source_text && character_to_seek) {
	source_length = text_string_length(source_text);
	source_index = FIX((SI_Long)0L);
	source_character = Nil;
      next_loop:
	if (FIXNUM_EQ(source_index,source_length))
	    goto end_loop;
	temp = FIX(UBYTE_16_ISAREF_1(source_text,IFIX(source_index)));
	source_index = FIXNUM_ADD1(source_index);
	source_character = temp;
	code = character_to_seek;
	if (IFIX(code) < (SI_Long)127L)
	    temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    temp = unicode_lowercase_if_uppercase(code);
	    if (temp);
	    else
		temp = code;
	}
	code = source_character;
	if (IFIX(code) < (SI_Long)127L)
	    temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    temp_1 = unicode_lowercase_if_uppercase(code);
	    if (temp_1);
	    else
		temp_1 = code;
	}
	if (NUM_EQ(temp,temp_1)) {
	    temp = FIXNUM_SUB1(source_index);
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

/* CONVERT-USER-G2-TEXT-INDICES-TO-INTERNAL-INDICES */
Object convert_user_g2_text_indices_to_internal_indices(g2_text,
	    g2_text_start_index_qm,g2_text_end_index_qm)
    Object g2_text, g2_text_start_index_qm, g2_text_end_index_qm;
{
    SI_Long g2_text_length, g2_text_start_index, g2_text_end_index;

    x_note_fn_call(33,2);
    g2_text_length = IFIX(text_string_length(g2_text));
    g2_text_start_index = FIXNUMP(g2_text_start_index_qm) ? 
	    IFIX(FIXNUM_SUB1(g2_text_start_index_qm)) : (SI_Long)0L;
    g2_text_end_index = FIXNUMP(g2_text_end_index_qm) ? 
	    IFIX(g2_text_end_index_qm) : g2_text_length;
    if ((SI_Long)0L <= g2_text_start_index && g2_text_start_index <= 
	    g2_text_end_index && g2_text_end_index <= g2_text_length)
	return VALUES_2(FIX(g2_text_start_index),FIX(g2_text_end_index));
    else
	return VALUES_2(Nil,Nil);
}

/* GET-FROM-G2-TEXT */
Object get_from_g2_text(g2_text,g2_text_start_index_qm,g2_text_end_index_qm)
    Object g2_text, g2_text_start_index_qm, g2_text_end_index_qm;
{
    Object g2_text_start_index, g2_text_end_index, wide_string_bv16, result_1;
    Object gensymed_symbol, gensymed_symbol_2, temp;
    SI_Long part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    Object result;

    x_note_fn_call(33,3);
    result = convert_user_g2_text_indices_to_internal_indices(g2_text,
	    g2_text_start_index_qm,g2_text_end_index_qm);
    MVS_2(result,g2_text_start_index,g2_text_end_index);
    if (g2_text_start_index) {
	part_length = IFIX(FIXNUM_MINUS(g2_text_end_index,
		g2_text_start_index));
	wide_string_bv16 = allocate_byte_vector_16(FIX(part_length + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = part_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | part_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
	result_1 = wide_string_bv16;
	gensymed_symbol = g2_text;
	gensymed_symbol_1 = IFIX(g2_text_start_index);
	gensymed_symbol_2 = result_1;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = part_length;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	temp = result_1;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* OMIT-FROM-G2-TEXT */
Object omit_from_g2_text(g2_text,g2_text_start_index,g2_text_end_index)
    Object g2_text, g2_text_start_index, g2_text_end_index;
{
    Object start_char_index_qm, end_char_index_qm, length_of_g2_text;
    Object new_g2_text, temp;
    Object result;

    x_note_fn_call(33,4);
    result = convert_user_g2_text_indices_to_internal_indices(g2_text,
	    g2_text_start_index,g2_text_end_index);
    MVS_2(result,start_char_index_qm,end_char_index_qm);
    if (start_char_index_qm && end_char_index_qm) {
	length_of_g2_text = text_string_length(g2_text);
	new_g2_text = obtain_text_string(FIXNUM_MINUS(length_of_g2_text,
		FIXNUM_MINUS(end_char_index_qm,start_char_index_qm)));
	if (IFIX(g2_text_start_index) > (SI_Long)0L)
	    copy_portion_of_string_into_text_string(g2_text,
		    FIX((SI_Long)0L),start_char_index_qm,new_g2_text,
		    FIX((SI_Long)0L));
	if (FIXNUM_LE(g2_text_start_index,length_of_g2_text))
	    copy_portion_of_string_into_text_string(g2_text,
		    end_char_index_qm,length_of_g2_text,new_g2_text,
		    start_char_index_qm);
	temp = new_g2_text;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INSERT-IN-G2-TEXT */
Object insert_in_g2_text(insertion_g2_text,original_g2_text,
	    original_g2_text_start_index)
    Object insertion_g2_text, original_g2_text, original_g2_text_start_index;
{
    Object original_g2_text_index_qm, original_g2_text_length;
    Object insertion_g2_text_length, destination_g2_text_length, temp;
    Object destination_g2_text;
    Object result;

    x_note_fn_call(33,5);
    result = convert_user_g2_text_indices_to_internal_indices(original_g2_text,
	    original_g2_text_start_index,Nil);
    MVS_2(result,original_g2_text_index_qm,original_g2_text_length);
    if (original_g2_text_index_qm) {
	insertion_g2_text_length = text_string_length(insertion_g2_text);
	destination_g2_text_length = FIXNUM_ADD(insertion_g2_text_length,
		original_g2_text_length);
	if (FIXNUM_GT(destination_g2_text_length,
		Maximum_length_for_user_text_strings))
	    temp = Nil;
	else {
	    destination_g2_text = 
		    obtain_text_string(destination_g2_text_length);
	    if ( !(IFIX(original_g2_text_index_qm) == (SI_Long)0L))
		copy_portion_of_text_string_into_text_string_given_count(original_g2_text,
			FIX((SI_Long)0L),destination_g2_text,
			FIX((SI_Long)0L),original_g2_text_index_qm);
	    copy_portion_of_text_string_into_text_string_given_count(insertion_g2_text,
		    FIX((SI_Long)0L),destination_g2_text,
		    original_g2_text_index_qm,insertion_g2_text_length);
	    if ( !FIXNUM_EQ(original_g2_text_index_qm,original_g2_text_length))
		copy_portion_of_string_into_text_string(original_g2_text,
			original_g2_text_index_qm,original_g2_text_length,
			destination_g2_text,
			FIXNUM_ADD(original_g2_text_index_qm,
			insertion_g2_text_length));
	    temp = destination_g2_text;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REPLACE-IN-G2-TEXT */
Object replace_in_g2_text(insertion_g2_text,original_g2_text,
	    original_g2_text_start_index,original_g2_text_end_index)
    Object insertion_g2_text, original_g2_text, original_g2_text_start_index;
    Object original_g2_text_end_index;
{
    Object g2_text_start_index_qm, g2_text_end_index_qm;
    Object original_g2_text_length, insertion_g2_text_length;
    Object omission_g2_text_length, destination_g2_text, temp;
    Object result;

    x_note_fn_call(33,6);
    result = convert_user_g2_text_indices_to_internal_indices(original_g2_text,
	    original_g2_text_start_index,original_g2_text_end_index);
    MVS_2(result,g2_text_start_index_qm,g2_text_end_index_qm);
    if (g2_text_start_index_qm) {
	original_g2_text_length = text_string_length(original_g2_text);
	insertion_g2_text_length = text_string_length(insertion_g2_text);
	omission_g2_text_length = FIXNUM_MINUS(g2_text_end_index_qm,
		g2_text_start_index_qm);
	destination_g2_text = 
		obtain_text_string(FIXNUM_MINUS(original_g2_text_length,
		FIXNUM_MINUS(omission_g2_text_length,
		insertion_g2_text_length)));
	if ( !(IFIX(g2_text_start_index_qm) == (SI_Long)0L))
	    copy_portion_of_text_string_into_text_string_given_count(original_g2_text,
		    FIX((SI_Long)0L),destination_g2_text,FIX((SI_Long)0L),
		    g2_text_start_index_qm);
	copy_portion_of_text_string_into_text_string_given_count(insertion_g2_text,
		FIX((SI_Long)0L),destination_g2_text,
		g2_text_start_index_qm,insertion_g2_text_length);
	if ( !FIXNUM_EQ(g2_text_end_index_qm,original_g2_text_length))
	    copy_portion_of_string_into_text_string(original_g2_text,
		    g2_text_end_index_qm,original_g2_text_length,
		    destination_g2_text,FIXNUM_ADD(g2_text_start_index_qm,
		    insertion_g2_text_length));
	temp = destination_g2_text;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NEXT-PARSE-OBJECT */
Object next_parse_object(lexing_table,original_g2_text,start_index,end_index)
    Object lexing_table, original_g2_text, start_index, end_index;
{
    Object temp, g2_text_start_index, current_tokenizer, current_start_state;
    Object current_anchor_p, match_parse_object, svref_new_value;
    Declare_special(3);

    x_note_fn_call(33,7);
    temp = 
	    convert_user_g2_text_indices_to_internal_indices(original_g2_text,
	    start_index,Nil);
    g2_text_start_index = temp;
    if (g2_text_start_index) {
	current_tokenizer = lexing_table;
	PUSH_SPECIAL_WITH_SYMBOL(Current_tokenizer,Qcurrent_tokenizer,current_tokenizer,
		2);
	  current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_start_state,Qcurrent_start_state,current_start_state,
		  1);
	    current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		    0);
	      match_parse_object = 
		      INLINE_UNSIGNED_BYTE_16_VECTOR_P(original_g2_text) 
		      != (SI_Long)0L ? 
		      get_next_token_from_text_string_1(original_g2_text,
		      g2_text_start_index,Nil) : Qnil;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	svref_new_value = FIXNUM_ADD1(ISVREF(match_parse_object,(SI_Long)2L));
	SVREF(match_parse_object,FIX((SI_Long)2L)) = svref_new_value;
	temp = match_parse_object;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INDICES-FOR-MATCH */
Object indices_for_match(lexing_table,source_text,search_position)
    Object lexing_table, source_text, search_position;
{
    Object temp;

    x_note_fn_call(33,8);
    temp = 
	    make_evaluation_structure_from_parse_object_reclaiming_it(next_parse_object(lexing_table,
	    source_text,search_position,Nil));
    return VALUES_1(temp);
}

/* SUBSTRING-FOR-MATCH */
Object substring_for_match(lexing_table,original_g2_text,start_index)
    Object lexing_table, original_g2_text, start_index;
{
    Object result_struct, match_start, match_end, substring;

    x_note_fn_call(33,9);
    result_struct = next_parse_object(lexing_table,original_g2_text,
	    start_index,Nil);
    match_start = ISVREF(result_struct,(SI_Long)2L);
    match_end = ISVREF(result_struct,(SI_Long)3L);
    substring = FIXNUM_EQ(match_end,No_tokenizer_match_end_index) ? 
	    obtain_text_string(FIX((SI_Long)0L)) : 
	    get_from_g2_text(original_g2_text,match_start,match_end);
    reclaim_parse_object_1(result_struct);
    return VALUES_1(substring);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* TEXT-WITH-REPLACEMENTS */
Object text_with_replacements(lexing_table,text_to_insert,original_g2_text,
	    search_position,stop_searching)
    Object lexing_table, text_to_insert, original_g2_text, search_position;
    Object stop_searching;
{
    Object g2_text_start_index, g2_text_end_index, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object source_index, next_token, start_of_match, end_of_match;
    Object part_of_original_text, part_match, part_end_index, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long replacement_length;
    Declare_special(5);
    Object result;

    x_note_fn_call(33,10);
    result = convert_user_g2_text_indices_to_internal_indices(original_g2_text,
	    search_position,stop_searching);
    MVS_2(result,g2_text_start_index,g2_text_end_index);
    if (g2_text_start_index) {
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
		  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_to_insert));
		  replacement_length = UBYTE_16_ISAREF_1(text_to_insert,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(text_to_insert,length_1 - 
			  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
		  source_index = g2_text_start_index;
		  next_token = Nil;
		  start_of_match = Nil;
		  end_of_match = Nil;
		  twrite_portion_of_wide_string_unparsably_to_current_wide_string(original_g2_text,
			  FIX((SI_Long)0L),g2_text_start_index);
		next_loop:
		  next_token = next_parse_object(lexing_table,
			  original_g2_text,FIXNUM_ADD1(source_index),Nil);
		  start_of_match = FIXNUM_SUB1(ISVREF(next_token,(SI_Long)2L));
		  end_of_match = ISVREF(next_token,(SI_Long)3L);
		  if (FIXNUM_EQ(end_of_match,No_tokenizer_match_end_index) 
			  || FIXNUM_GE(start_of_match,g2_text_end_index))
		      goto end_loop;
		  reclaim_parse_object_1(next_token);
		  twrite_portion_of_wide_string_unparsably_to_current_wide_string(original_g2_text,
			  source_index,start_of_match);
		  if (FIXNUM_LE(end_of_match,g2_text_end_index))
		      twrite_portion_of_wide_string_unparsably_to_current_wide_string(text_to_insert,
			      FIX((SI_Long)0L),FIX(replacement_length));
		  else {
		      part_of_original_text = 
			      get_from_g2_text(original_g2_text,
			      FIXNUM_ADD1(start_of_match),g2_text_end_index);
		      part_match = next_parse_object(lexing_table,
			      part_of_original_text,FIX((SI_Long)1L),Nil);
		      part_end_index = ISVREF(part_match,(SI_Long)3L);
		      if (FIXNUM_EQ(part_end_index,
			      No_tokenizer_match_end_index))
			  twrite_portion_of_wide_string_unparsably_to_current_wide_string(original_g2_text,
				  start_of_match,end_of_match);
		      else {
			  twrite_portion_of_wide_string_unparsably_to_current_wide_string(text_to_insert,
				  FIX((SI_Long)0L),FIX(replacement_length));
			  twrite_portion_of_wide_string_unparsably_to_current_wide_string(original_g2_text,
				  FIXNUM_ADD(start_of_match,
				  part_end_index),end_of_match);
		      }
		      reclaim_parse_object_1(part_match);
		      reclaim_text_string(part_of_original_text);
		  }
		  source_index = end_of_match;
		  goto next_loop;
		end_loop:
		  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_g2_text));
		  twrite_portion_of_wide_string_unparsably_to_current_wide_string(original_g2_text,
			  source_index,
			  FIX(UBYTE_16_ISAREF_1(original_g2_text,length_1 
			  - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(original_g2_text,length_1 - 
			  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)));
		  reclaim_parse_object_1(next_token);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COMPUTE-TEXT-HASH-CODE */
Object compute_text_hash_code(text_string)
    Object text_string;
{
    Object temp_1;
    SI_Long character_1, length_1, index_1, downcase_character_code, hash_sum;
    SI_Long temp, code, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,11);
    character_1 = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
    length_1 = UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    index_1 = (SI_Long)0L;
    downcase_character_code = (SI_Long)0L;
    hash_sum = (SI_Long)0L;
  next_loop:
    if ( !(index_1 < length_1))
	goto end_loop;
    temp = UBYTE_16_ISAREF_1(text_string,index_1);
    index_1 = index_1 + (SI_Long)1L;
    character_1 = temp;
    code = character_1;
    if (code < (SI_Long)127L)
	gensymed_symbol = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		code + (SI_Long)32L : code;
    else {
	temp_1 = unicode_lowercase_if_uppercase(FIX(code));
	if (temp_1);
	else
	    temp_1 = FIX(code);
	gensymed_symbol = IFIX(temp_1);
    }
    gensymed_symbol_1 = (SI_Long)127L;
    downcase_character_code = gensymed_symbol & gensymed_symbol_1;
    if (g2_enterprise_p())
	hash_sum = ((hash_sum & (SI_Long)2097151L) << (SI_Long)7L) + 
		(hash_sum >>  -  - (SI_Long)21L) ^ downcase_character_code;
    else
	hash_sum = ((hash_sum & (SI_Long)134217727L) << (SI_Long)1L) + 
		(hash_sum >>  -  - (SI_Long)27L) ^ downcase_character_code;
    goto next_loop;
  end_loop:
    temp_1 = FIX(hash_sum);
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_kb_property_conses, Qavailable_kb_property_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_kb_property_conses_tail, Qavailable_kb_property_conses_tail);

Object Available_kb_property_conses_vector = UNBOUND;

Object Available_kb_property_conses_tail_vector = UNBOUND;

Object Kb_property_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Kb_property_cons_counter, Qkb_property_cons_counter);

/* OUTSTANDING-KB-PROPERTY-CONSES */
Object outstanding_kb_property_conses()
{
    Object temp;

    x_note_fn_call(33,12);
    temp = FIXNUM_MINUS(Kb_property_cons_counter,
	    length(Available_kb_property_conses));
    return VALUES_1(temp);
}

/* KB-PROPERTY-CONS-MEMORY-USAGE */
Object kb_property_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(33,13);
    temp = FIXNUM_TIMES(Kb_property_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-KB-PROPERTY-CONS-POOL */
Object replenish_kb_property_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(33,14);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qkb_property_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Kb_property_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qkb_property;        /* kb-property */

/* KB-PROPERTY-CONS-1 */
Object kb_property_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(33,15);
    new_cons = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_kb_property_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_kb_property_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qkb_property);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-KB-PROPERTY-LIST-POOL */
Object replenish_kb_property_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(33,16);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qkb_property_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-KB-PROPERTY-LIST-1 */
Object make_kb_property_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(33,17);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_kb_property_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_kb_property_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* KB-PROPERTY-LIST-2 */
Object kb_property_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,18);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_kb_property_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qkb_property);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_kb_property_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* KB-PROPERTY-LIST-3 */
Object kb_property_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,19);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_kb_property_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qkb_property);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_kb_property_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* KB-PROPERTY-LIST-4 */
Object kb_property_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,20);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_kb_property_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qkb_property);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_kb_property_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* KB-PROPERTY-LIST-TRACE-HOOK */
Object kb_property_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(33,21);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-KB-PROPERTY-CONSES-1 */
Object copy_tree_using_kb_property_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,22);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_kb_property_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_kb_property_cons_pool();
	temp_1 = copy_tree_using_kb_property_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_kb_property_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_kb_property_cons_pool();
	temp_1 = 
		copy_tree_using_kb_property_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-KB-PROPERTY-CONSES-1 */
Object copy_list_using_kb_property_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,23);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_kb_property_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_kb_property_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_kb_property_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_kb_property_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_kb_property_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-KB-PROPERTY-CONS-1 */
Object reclaim_kb_property_cons_1(kb_property_cons)
    Object kb_property_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(33,24);
    inline_note_reclaim_cons(kb_property_cons,Qkb_property);
    if (ISVREF(Available_kb_property_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_kb_property_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = kb_property_cons;
	temp = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = kb_property_cons;
    }
    else {
	temp = Available_kb_property_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = kb_property_cons;
	temp = Available_kb_property_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = kb_property_cons;
    }
    M_CDR(kb_property_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-KB-PROPERTY-LIST-1 */
Object reclaim_kb_property_list_1(kb_property_list)
    Object kb_property_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,25);
    if (kb_property_list) {
	last_1 = kb_property_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qkb_property);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qkb_property);
	if (ISVREF(Available_kb_property_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_kb_property_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = kb_property_list;
	    temp = Available_kb_property_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_kb_property_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = kb_property_list;
	    temp = Available_kb_property_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-KB-PROPERTY-LIST*-1 */
Object reclaim_kb_property_list_star_1(kb_property_list)
    Object kb_property_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(33,26);
    if (CONSP(kb_property_list)) {
	temp = last(kb_property_list,_);
	M_CDR(temp) = Nil;
	if (kb_property_list) {
	    last_1 = kb_property_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qkb_property);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qkb_property);
	    if (ISVREF(Available_kb_property_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_kb_property_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = kb_property_list;
		temp = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_kb_property_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = kb_property_list;
		temp = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-KB-PROPERTY-TREE-1 */
Object reclaim_kb_property_tree_1(tree)
    Object tree;
{
    Object e, e2, kb_property_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,27);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_kb_property_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		kb_property_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(kb_property_cons,Qkb_property);
		if (EQ(kb_property_cons,e))
		    goto end_1;
		else if ( !TRUEP(kb_property_cons))
		    goto end_1;
		else
		    kb_property_cons = CDR(kb_property_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_kb_property_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_kb_property_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_kb_property_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-KB-PROPERTY-ELEMENT-1 */
Object delete_kb_property_element_1(element,kb_property_list)
    Object element, kb_property_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(33,28);
    if (kb_property_list) {
	if (EQ(element,M_CAR(kb_property_list))) {
	    temp = CDR(kb_property_list);
	    inline_note_reclaim_cons(kb_property_list,Qkb_property);
	    if (ISVREF(Available_kb_property_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_kb_property_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = kb_property_list;
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = kb_property_list;
	    }
	    else {
		temp_1 = Available_kb_property_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = kb_property_list;
		temp_1 = Available_kb_property_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = kb_property_list;
	    }
	    M_CDR(kb_property_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = kb_property_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qkb_property);
		if (ISVREF(Available_kb_property_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_kb_property_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_kb_property_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_kb_property_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_kb_property_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = kb_property_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-KB-PROPERTY-CONS-1 */
Object delete_kb_property_cons_1(kb_property_cons,kb_property_list)
    Object kb_property_cons, kb_property_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(33,29);
    if (EQ(kb_property_cons,kb_property_list))
	temp = CDR(kb_property_list);
    else {
	l_trailer_qm = Nil;
	l = kb_property_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,kb_property_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = kb_property_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_kb_property_cons_1(kb_property_cons);
    return VALUES_1(temp);
}

/* RECLAIM-KB-PROPERTY-LIST-FUNCTION */
Object reclaim_kb_property_list_function(kb_property_list)
    Object kb_property_list;
{
    x_note_fn_call(33,30);
    return reclaim_kb_property_list_1(kb_property_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);

Object Locations_of_kb_specific_property_lists = UNBOUND;

/* INITIALIZE-KB-STATE-CHANGES */
Object initialize_kb_state_changes()
{
    x_note_fn_call(33,31);
    return kb_property_cons_1(Nil,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_state_changes, Qkb_state_changes);

DEFINE_VARIABLE_WITH_SYMBOL(There_is_a_current_kb_qm, Qthere_is_a_current_kb_qm);

Object Kb_specific_property_names = UNBOUND;

Object Function_to_copy_global_value_for_this_property_name_prop = UNBOUND;

Object Do_not_carry_global_property_value_into_kbs_qm_prop = UNBOUND;

Object Function_to_reclaim_kb_specific_property_value_qm_prop = UNBOUND;

Object No_specific_property_value = UNBOUND;

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-SYMBOL-PROPERTIES-HASH-TABLE-SKIP-LIST-SENTINEL */
Object make_symbol_properties_hash_table_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(33,32);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-SYMBOL-PROPERTIES-HASH-TABLE-NODES */
Object reclaim_symbol_properties_hash_table_nodes(symbol_properties_hash_table_skip_list,
	    tail)
    Object symbol_properties_hash_table_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(33,33);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(symbol_properties_hash_table_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(symbol_properties_hash_table_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(symbol_properties_hash_table_skip_list,(SI_Long)2L);
    entry = ISVREF(symbol_properties_hash_table_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(symbol_properties_hash_table_skip_list);
    symbol_properties_hash_table_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-SYMBOL-PROPERTIES-HASH-TABLE-SKIP-LIST */
Object clear_symbol_properties_hash_table_skip_list(symbol_properties_hash_table_skip_list)
    Object symbol_properties_hash_table_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(33,34);
    head = M_CAR(M_CDR(symbol_properties_hash_table_skip_list));
    tail = M_CDR(M_CDR(symbol_properties_hash_table_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_symbol_properties_hash_table_nodes(element_qm,tail);
    return VALUES_1(symbol_properties_hash_table_skip_list);
}

Object Symbol_properties_table = UNBOUND;

/* IS-PROPERTY-VALUE-IN-HASH-TABLE? */
Object is_property_value_in_hash_table_qm(properties,property_name)
    Object properties, property_name;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,35);
    if (properties) {
	skip_list = CDR(properties);
	key_value = property_name;
	key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
	if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value) {
	    if (EQ(key_value,ISVREF(curr,(SI_Long)2L)))
		return VALUES_1(ISVREF(curr,(SI_Long)3L));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* GET-KB-SPECIFIC-PROPERTIES-FROM-HASH-TABLE */
Object get_kb_specific_properties_from_hash_table(symbol)
    Object symbol;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, symbol_properties, kb_specific_properties;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,36);
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = symbol;
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
    symbol_properties = gensymed_symbol;
    skip_list = CDR(symbol_properties);
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
    kb_specific_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
	    key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    if (kb_specific_properties);
    else
	kb_specific_properties = Nil;
    if ( !TRUEP(kb_specific_properties)) {
	register_symbol_as_location_of_kb_specific_properties(symbol);
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol) = Qsymbol_properties_hash_table;
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
	M_CAR(gensymed_symbol_1) = head;
	M_CDR(gensymed_symbol_1) = tail;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	M_CDR(gensymed_symbol) = gensymed_symbol_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	kb_specific_properties = gensymed_symbol;
	gensymed_symbol = Current_kb_specific_property_list_property_name;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	set_skip_list_entry(symbol_properties,FIX((SI_Long)31L),Qeq,Nil,T,
		gensymed_symbol,temp_1,kb_specific_properties);
    }
    return VALUES_1(kb_specific_properties);
}

/* GET-SYMBOL-PROPERTIES-FROM-PLIST */
Object get_symbol_properties_from_plist(symbol)
    Object symbol;
{
    x_note_fn_call(33,37);
    return VALUES_1(SYMBOL_PLIST(symbol));
}

/* PUT-SYMBOL-PROPERTIES-INTO-PLIST */
Object put_symbol_properties_into_plist(symbol,properties)
    Object symbol, properties;
{
    x_note_fn_call(33,38);
    return VALUES_1(SET_SYMBOL_PLIST(symbol,properties));
}

/* GET-PROPERTY-VALUE-FROM-PLIST-WITHOUT-DEFAULT */
Object get_property_value_from_plist_without_default(properties,property_name)
    Object properties, property_name;
{
    Object list_1;

    x_note_fn_call(33,39);
    list_1 = properties;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : Nil);
}

/* GET-PROPERTY-VALUE-FROM-PLIST-WITH-DEFAULT */
Object get_property_value_from_plist_with_default(properties,property_name,
	    default_1)
    Object properties, property_name, default_1;
{
    Object list_1;

    x_note_fn_call(33,40);
    list_1 = properties;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : default_1);
}

/* SET-PROPERTY-VALUE-INTO-PLIST */
Object set_property_value_into_plist(properties,property_1,value)
    Object properties, property_1, value;
{
    Object property_cons, value_place;

    x_note_fn_call(33,41);
    property_cons = properties;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(M_CAR(property_cons),property_1)) {
	property_cons = M_CDR(property_cons);
	value_place = property_cons;
	goto end_1;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    value_place = Qnil;
  end_1:;
    if (value_place) {
	M_CAR(value_place) = value;
	return VALUES_1(properties);
    }
    else
	return kb_property_cons_1(property_1,kb_property_cons_1(value,
		properties));
}

/* GET-KB-SPECIFIC-PROPERTIES-FROM-PLIST */
Object get_kb_specific_properties_from_plist(symbol)
    Object symbol;
{
    Object property_list, property_1, property_cons;
    Object kb_specific_properties_place, kb_specific_properties;

    x_note_fn_call(33,42);
    property_list = get_symbol_properties_from_plist(symbol);
    property_1 = Current_kb_specific_property_list_property_name;
    property_cons = property_list;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(M_CAR(property_cons),property_1)) {
	property_cons = M_CDR(property_cons);
	kb_specific_properties_place = property_cons;
	goto end_1;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    kb_specific_properties_place = Qnil;
  end_1:;
    kb_specific_properties = Nil;
    if (kb_specific_properties_place)
	kb_specific_properties = M_CAR(kb_specific_properties_place);
    else
	register_symbol_as_location_of_kb_specific_properties(symbol);
    return VALUES_1(kb_specific_properties);
}

/* IS-PROPERTY-VALUE-IN-PLIST? */
Object is_property_value_in_plist_qm(properties,property_name)
    Object properties, property_name;
{
    Object property_cons;
    char temp;

    x_note_fn_call(33,43);
    property_cons = properties;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(M_CAR(property_cons),property_name)) {
	property_cons = M_CDR(property_cons);
	temp = TRUEP(property_cons);
	goto end_1;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    return VALUES_1( ! !temp ? T : Nil);
}

/* GET-SYMBOL-PROPERTIES-FUNCTION */
Object get_symbol_properties_function(symbol)
    Object symbol;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,44);
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = symbol;
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
    return VALUES_1(gensymed_symbol);
}

/* GET-PROPERTY-VALUE-FUNCTION */
Object get_property_value_function varargs_1(int, n)
{
    Object properties, property_name;
    Object default_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(33,45);
    INIT_ARGS_nonrelocating();
    properties = REQUIRED_ARG_nonrelocating();
    property_name = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    skip_list = CDR(properties);
    key_value = property_name;
    key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(default_1);
}

/* SET-PROPERTY-VALUE-FUNCTION */
Object set_property_value_function(properties,property_1,value)
    Object properties, property_1, value;
{
    Object gensymed_symbol;

    x_note_fn_call(33,46);
    gensymed_symbol = property_1;
    set_skip_list_entry(properties,FIX((SI_Long)31L),Qeq,Nil,T,
	    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),value);
    return VALUES_1(value);
}

/* REGISTER-SYMBOL-AS-LOCATION-OF-KB-SPECIFIC-PROPERTIES */
Object register_symbol_as_location_of_kb_specific_properties(symbol)
    Object symbol;
{
    Object gensymed_symbol, ab_loop_list_;
    Object location_of_list_of_kb_specific_symbols, cdr_new_value;

    x_note_fn_call(33,47);
    gensymed_symbol = Nil;
    ab_loop_list_ = Locations_of_kb_specific_property_lists;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
	    Current_kb_specific_property_list_property_name)) {
	location_of_list_of_kb_specific_symbols = gensymed_symbol;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    location_of_list_of_kb_specific_symbols = Qnil;
  end_1:;
    if (location_of_list_of_kb_specific_symbols) {
	cdr_new_value = kb_property_cons_1(symbol,
		CDR(location_of_list_of_kb_specific_symbols));
	return VALUES_1(M_CDR(location_of_list_of_kb_specific_symbols) = 
		cdr_new_value);
    }
    else
	return error((SI_Long)1L,
		"*location-of-list-of-kb-specific-symbols* is not initialized");
}

/* LOOKUP-GLOBAL-OR-KB-SPECIFIC-PROPERTY-VALUE */
Object lookup_global_or_kb_specific_property_value(symbol,property_name)
    Object symbol, property_name;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,48);
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = symbol;
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
	key_value = property_name;
	key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
	key_value = property_name;
	key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
    return VALUES_1(resulting_value);
}

/* MUTATE-GLOBAL-OR-KB-SPECIFIC-PROPERTY-VALUE */
Object mutate_global_or_kb_specific_property_value(symbol,value,property_1)
    Object symbol, value, property_1;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, properties;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,49);
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = symbol;
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
    if (There_is_a_current_kb_qm) {
	gensymed_symbol = Current_kb_specific_property_list_property_name;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	gensymed_symbol_1 = property_1;
	temp = get_kb_specific_properties_from_hash_table(symbol);
	set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,
		gensymed_symbol_1,FIX(SXHASH_SYMBOL_1(gensymed_symbol_1) & 
		IFIX(Most_positive_fixnum)),value);
	set_skip_list_entry(global_properties,FIX((SI_Long)31L),Qeq,Nil,T,
		gensymed_symbol,temp_1,
		get_kb_specific_properties_from_hash_table(symbol));
	properties = global_properties;
    }
    else {
	gensymed_symbol = property_1;
	set_skip_list_entry(global_properties,FIX((SI_Long)31L),Qeq,Nil,T,
		gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),value);
	properties = global_properties;
    }
    gensymed_symbol = symbol;
    temp_1 = Symbol_properties_table;
    set_skip_list_entry(temp_1,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),properties);
    return VALUES_1(value);
}

static Object Qfunction_to_copy_global_value_for_this_property_name;  /* function-to-copy-global-value-for-this-property-name */

/* COPY-KB-SPECIFIC-PROPERTY-FROM-GLOBAL-IF-NECESSARY */
Object copy_kb_specific_property_from_global_if_necessary(symbol,property_1)
    Object symbol, property_1;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, temp_2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(33,50);
    skip_list = CDR(Symbol_properties_table);
    key_value = symbol;
    key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = symbol;
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
    skip_list = CDR(gensymed_symbol);
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
    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (temp_1);
    else
	temp_1 = Nil;
    if ( !TRUEP(is_property_value_in_hash_table_qm(temp_1,property_1))) {
	temp = 
		SYMBOL_FUNCTION(getfq_function_no_default(INLINE_SYMBOL_PLIST(property_1),
		Qfunction_to_copy_global_value_for_this_property_name));
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol;
	key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
	    temp_2 = Symbol_properties_table;
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
	    gensymed_symbol = set_skip_list_entry(temp_2,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	skip_list = CDR(gensymed_symbol);
	key_value = property_1;
	key_hash_value = SXHASH_SYMBOL_1(property_1) & 
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
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
	temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (temp_1);
	else
	    temp_1 = Nil;
	return mutate_global_or_kb_specific_property_value(symbol,
		FUNCALL_1(temp,temp_1),property_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfunction_to_reclaim_kb_specific_property_value_qm;  /* function-to-reclaim-kb-specific-property-value? */

/* RECLAIM-KB-SPECIFIC-PROPERTIES */
Object reclaim_kb_specific_properties(keep_locations_entry_qm)
    Object keep_locations_entry_qm;
{
    Object entry_cons, location_cons_qm, symbol, ab_loop_list_;
    Object symbol_properties, specific_property_list, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, property_1, property_value;
    Object reclaimer_qm, ab_less_than_branch_qm_, head_1, tail_1, element_qm;
    Object last_1, next_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(33,51);
    entry_cons = Locations_of_kb_specific_property_lists;
  next_loop:
    if ( !TRUEP(entry_cons))
	goto end_loop;
    if (EQ(CAAR(entry_cons),Current_kb_specific_property_list_property_name)) {
	location_cons_qm = entry_cons;
	goto end_1;
    }
    entry_cons = M_CDR(entry_cons);
    goto next_loop;
  end_loop:
    location_cons_qm = Qnil;
  end_1:;
    if (location_cons_qm) {
	symbol = Nil;
	ab_loop_list_ = CDAR(location_cons_qm);
	symbol_properties = Nil;
	specific_property_list = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol;
	key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	    goto end_2;
	goto next_loop_3;
      end_loop_4:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	symbol_properties = gensymed_symbol;
	skip_list = CDR(symbol_properties);
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
	    goto end_3;
	goto next_loop_6;
      end_loop_7:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:;
	temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (temp_1);
	else
	    temp_1 = Nil;
	specific_property_list = temp_1;
	if (specific_property_list &&  ! 
		    !TRUEP(M_CDR(specific_property_list))) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = specific_property_list;
	    ab_binary_tree_form_ = specific_property_list;
	    gensymed_symbol = CDR(specific_property_list);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_3 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    property_1 = Nil;
	    property_value = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      reclaimer_qm = Nil;
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
	    next_loop_8:
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
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_9:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_8;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_9;
		    end_loop_8:;
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
		  goto end_loop_9;
	      property_1 = CAR(ab_entry_cons_);
	      property_value = CDR(ab_entry_cons_);
	      reclaimer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(property_1),
		      Qfunction_to_reclaim_kb_specific_property_value_qm);
	      if (reclaimer_qm) {
		  temp_1 = SYMBOL_FUNCTION(reclaimer_qm);
		  FUNCALL_1(temp_1,property_value);
	      }
	      goto next_loop_8;
	    end_loop_9:;
	    POP_SPECIAL();
	    head_1 = M_CAR(M_CDR(specific_property_list));
	    tail_1 = M_CDR(M_CDR(specific_property_list));
	    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head_1,
		    (SI_Long)0L),(SI_Long)0L));
	    if ( !EQ(element_qm,tail_1))
		reclaim_symbol_properties_hash_table_nodes(element_qm,tail_1);
	    reclaim_skip_list_element(head_1);
	    reclaim_skip_list_element(tail_1);
	    M_CDDR(specific_property_list) = Nil;
	    M_CADR(specific_property_list) = Nil;
	    M_CAR(specific_property_list) = Nil;
	    if (specific_property_list) {
		last_1 = specific_property_list;
		next_qm = Nil;
	      next_loop_10:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_10;
		inline_note_reclaim_cons(last_1,Qlookup);
		last_1 = next_qm;
		goto next_loop_10;
	      end_loop_10:
		inline_note_reclaim_cons(last_1,Qlookup);
		if (ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = specific_property_list;
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		else {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = specific_property_list;
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	}
	temp_1 = Current_kb_specific_property_list_property_name;
	temp = symbol_properties;
	delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,temp,
		FIX((SI_Long)31L),
		FIX(SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum)));
	goto next_loop_1;
      end_loop_1:;
	reclaim_kb_property_list_1(CDAR(location_cons_qm));
	M_CDAR(location_cons_qm) = Nil;
	if ( !TRUEP(keep_locations_entry_qm)) {
	    reclaim_kb_property_cons_1(CAR(location_cons_qm));
	    Locations_of_kb_specific_property_lists = 
		    delete_kb_property_cons_1(location_cons_qm,
		    Locations_of_kb_specific_property_lists);
	    return VALUES_1(Locations_of_kb_specific_property_lists);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* LOOKUP-KB-SPECIFIC-PROPERTY-VALUE */
Object lookup_kb_specific_property_value(symbol,kb_specific_property_name)
    Object symbol, kb_specific_property_name;
{
    Object list_1;

    x_note_fn_call(33,52);
    list_1 = INLINE_SYMBOL_PLIST(symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),kb_specific_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : Nil);
}

/* LOOKUP-KB-SPECIFIC-PROPERTY-VALUE-WITH-DEFAULT */
Object lookup_kb_specific_property_value_with_default(symbol,
	    kb_specific_property_name,default_1)
    Object symbol, kb_specific_property_name, default_1;
{
    Object list_1;

    x_note_fn_call(33,53);
    list_1 = INLINE_SYMBOL_PLIST(symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),kb_specific_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : default_1);
}

/* MUTATE-KB-SPECIFIC-PROPERTY-VALUE */
Object mutate_kb_specific_property_value(symbol,value,property_1)
    Object symbol, value, property_1;
{
    Object property_list, property_2, property_cons;
    Object kb_specific_property_list_cons, property_value_cons, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object ab_loop_list_, location_of_list_of_kb_specific_symbols;

    x_note_fn_call(33,54);
    property_list = SYMBOL_PLIST(symbol);
    property_2 = Current_kb_specific_property_list_property_name;
    property_cons = property_list;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(M_CAR(property_cons),property_2)) {
	property_cons = M_CDR(property_cons);
	kb_specific_property_list_cons = property_cons;
	goto end_1;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    kb_specific_property_list_cons = Qnil;
  end_1:;
    if (kb_specific_property_list_cons) {
	property_list = M_CAR(kb_specific_property_list_cons);
	property_cons = property_list;
      next_loop_1:
	if ( !TRUEP(property_cons))
	    goto end_loop_1;
	if (EQ(M_CAR(property_cons),property_1)) {
	    property_cons = M_CDR(property_cons);
	    property_value_cons = property_cons;
	    goto end_2;
	}
	property_cons = M_CDR(M_CDR(property_cons));
	goto next_loop_1;
      end_loop_1:
	property_value_cons = Qnil;
      end_2:;
	if (property_value_cons)
	    M_CAR(property_value_cons) = value;
	else {
	    new_cons = ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_kb_property_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_kb_property_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_kb_property_cons_pool();
	    M_CAR(gensymed_symbol) = property_1;
	    new_cons = ISVREF(Available_kb_property_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_kb_property_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_kb_property_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_kb_property_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_kb_property_cons_pool();
	    M_CAR(gensymed_symbol_1) = value;
	    temp = M_CAR(kb_specific_property_list_cons);
	    M_CDR(gensymed_symbol_1) = temp;
	    inline_note_allocate_cons(gensymed_symbol_1,Qkb_property);
	    M_CDR(gensymed_symbol) = gensymed_symbol_1;
	    inline_note_allocate_cons(gensymed_symbol,Qkb_property);
	    M_CAR(kb_specific_property_list_cons) = gensymed_symbol;
	}
    }
    else {
	gensymed_symbol = Nil;
	ab_loop_list_ = Locations_of_kb_specific_property_lists;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Current_kb_specific_property_list_property_name)) {
	    location_of_list_of_kb_specific_symbols = gensymed_symbol;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	location_of_list_of_kb_specific_symbols = Qnil;
      end_3:;
	temp = kb_property_cons_1(symbol,
		M_CDR(location_of_list_of_kb_specific_symbols));
	M_CDR(location_of_list_of_kb_specific_symbols) = temp;
	temp = 
		kb_property_cons_1(Current_kb_specific_property_list_property_name,
		kb_property_cons_1(kb_property_cons_1(property_1,
		kb_property_cons_1(value,Nil)),SYMBOL_PLIST(symbol)));
	SET_SYMBOL_PLIST(symbol,temp);
    }
    return VALUES_1(value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_assigned_global_kb_number, Qlast_assigned_global_kb_number);

Object Global_grammar = UNBOUND;

static Object string_constant;     /* "KB-~D" */

static Object Qlocations_of_kb_specific_property_lists;  /* *locations-of-kb-specific-property-lists* */

/* SWITCH-TO-NEW-EMPTY-KB */
Object switch_to_new_empty_kb()
{
    Object gensymed_symbol, gensymed_symbol_1;
    Object kb_specific_property_list_property_name, new_value, old_value, temp;

    x_note_fn_call(33,55);
    restore_debugging_parameters_to_default_values();
    restore_backup_journaling_parameters_to_default_values();
    reclaim_items_deleted_since_load_or_save();
  next_loop:
    gensymed_symbol = There_is_a_current_kb_qm;
    gensymed_symbol_1 = T;
    if (CAS_SYMBOL(Qthere_is_a_current_kb_qm,gensymed_symbol,
	    gensymed_symbol_1))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
    set_current_grammar(Global_grammar);
    kb_specific_property_list_property_name = intern_text_string(1,
	    tformat_text_string(2,string_constant,
	    atomic_incff_symval(Qlast_assigned_global_kb_number,
	    FIX((SI_Long)1L))));
    new_value = 
	    kb_property_cons_1(kb_property_cons_1(kb_specific_property_list_property_name,
	    Nil),Nil);
    old_value = Nil;
  next_loop_1:
    old_value = Locations_of_kb_specific_property_lists;
    M_CDR(new_value) = old_value;
    if (CAS_SYMBOL(Qlocations_of_kb_specific_property_lists,old_value,
	    new_value))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    switch_to_kb(kb_specific_property_list_property_name);
    initialize_data_server_properties();
    initialize_modules_and_system_tables_a_list();
    temp = initialize_kb_name_directories();
    return VALUES_1(temp);
}

Object Kb_specific_variable_plist_kbprop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);

static Object Qlisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

static Object Qsystem_variable_descriptions;  /* system-variable-descriptions */

/* SWITCH-TO-KB */
Object switch_to_kb(kb_specific_property_list_property_name)
    Object kb_specific_property_list_property_name;
{
    Object kb_specific_variable_plist, l, cadr_new_value, module_name;
    Object ab_loop_list_, system_variable_name, kb_specific_qm;
    Object ab_loop_list__1, ab_loop_desetq_, temp, kb_specific_variable, value;
    Object initialization;

    x_note_fn_call(33,56);
    if ( !EQ(kb_specific_property_list_property_name,
	    Current_kb_specific_property_list_property_name)) {
	if (assq_function(Current_kb_specific_property_list_property_name,
		Locations_of_kb_specific_property_lists)) {
	    kb_specific_variable_plist = 
		    lookup_kb_specific_property_value(Current_kb_specific_property_list_property_name,
		    Kb_specific_variable_plist_kbprop);
	    if (kb_specific_variable_plist) {
		l = kb_specific_variable_plist;
	      next_loop:
		if ( !TRUEP(l))
		    goto end_loop;
		cadr_new_value = SYMBOL_VALUE(CAR(l));
		M_CADR(l) = cadr_new_value;
		l = CDDR(l);
		goto next_loop;
	      end_loop:;
	    }
	    else {
		module_name = Nil;
		ab_loop_list_ = get(Current_system_name,
			Qlisp_modules_to_be_loaded,_);
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		module_name = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		system_variable_name = Nil;
		kb_specific_qm = Nil;
		ab_loop_list__1 = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
			Qsystem_variable_descriptions);
		ab_loop_desetq_ = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_2;
		ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		system_variable_name = CAR(ab_loop_desetq_);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		temp = CDR(temp);
		kb_specific_qm = CAR(temp);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if (kb_specific_qm)
		    kb_specific_variable_plist = 
			    gensym_cons_1(system_variable_name,
			    gensym_cons_1(SYMBOL_VALUE(system_variable_name),
			    kb_specific_variable_plist));
		goto next_loop_2;
	      end_loop_2:;
		goto next_loop_1;
	      end_loop_1:
		mutate_kb_specific_property_value(Current_kb_specific_property_list_property_name,
			kb_specific_variable_plist,
			Kb_specific_variable_plist_kbprop);
	    }
	}
	Current_kb_specific_property_list_property_name = 
		kb_specific_property_list_property_name;
	kb_specific_variable_plist = 
		lookup_kb_specific_property_value(Current_kb_specific_property_list_property_name,
		Kb_specific_variable_plist_kbprop);
	if (kb_specific_variable_plist) {
	    kb_specific_variable = Nil;
	    value = Nil;
	    ab_loop_list_ = kb_specific_variable_plist;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	  next_loop_3:
	    kb_specific_variable = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    value = CAR(temp);
	    set(kb_specific_variable,value);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    goto next_loop_3;
	  end_loop_3:
	    temp = Qnil;
	}
	else {
	    kb_specific_variable_plist = Nil;
	    module_name = Nil;
	    ab_loop_list_ = get(Current_system_name,
		    Qlisp_modules_to_be_loaded,_);
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    module_name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    system_variable_name = Nil;
	    initialization = Nil;
	    kb_specific_qm = Nil;
	    ab_loop_list__1 = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
		    Qsystem_variable_descriptions);
	    ab_loop_desetq_ = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	    system_variable_name = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    initialization = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    kb_specific_qm = CAR(temp);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (kb_specific_qm) {
		set_system_variable_as_appropriate(system_variable_name,
			initialization);
		kb_specific_variable_plist = 
			gensym_cons_1(system_variable_name,
			gensym_cons_1(SYMBOL_VALUE(system_variable_name),
			kb_specific_variable_plist));
	    }
	    goto next_loop_5;
	  end_loop_5:;
	    goto next_loop_4;
	  end_loop_4:;
	    temp = 
		    mutate_kb_specific_property_value(Current_kb_specific_property_list_property_name,
		    kb_specific_variable_plist,
		    Kb_specific_variable_plist_kbprop);
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-VALUES-OF-KB-SPECIFIC-VARIABLES */
Object reclaim_values_of_kb_specific_variables(system_name)
    Object system_name;
{
    Object module_name, ab_loop_list_, system_variable_name, kb_specific_qm;
    Object value_reclaimer_qm, ab_loop_list__1, ab_loop_desetq_, temp;

    x_note_fn_call(33,57);
    module_name = Nil;
    ab_loop_list_ = get(system_name,Qlisp_modules_to_be_loaded,_);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    system_variable_name = Nil;
    kb_specific_qm = Nil;
    value_reclaimer_qm = Nil;
    ab_loop_list__1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qsystem_variable_descriptions);
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    system_variable_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    kb_specific_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    value_reclaimer_qm = CAR(temp);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (kb_specific_qm && value_reclaimer_qm) {
	temp = SYMBOL_FUNCTION(value_reclaimer_qm);
	FUNCALL_1(temp,SYMBOL_VALUE(system_variable_name));
	set(system_variable_name,Nil);
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Function_keeps_procedure_environment_valid_qm_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(In_edit_warning_context_p, Qin_edit_warning_context_p);

DEFINE_VARIABLE_WITH_SYMBOL(Items_warned_in_edit_warning_context, Qitems_warned_in_edit_warning_context);

DEFINE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);

/* CURRENT-FRAME-SERIAL-NUMBER-FUNCTION */
Object current_frame_serial_number_function()
{
    x_note_fn_call(33,58);
    return VALUES_1(Current_frame_serial_number);
}

/* COPY-OF-CURRENT-FRAME-SERIAL-NUMBER-FUNCTION */
Object copy_of_current_frame_serial_number_function()
{
    x_note_fn_call(33,59);
    return copy_frame_serial_number(Current_frame_serial_number);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_frame_serial_conses, Qavailable_frame_serial_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_frame_serial_conses_tail, Qavailable_frame_serial_conses_tail);

Object Available_frame_serial_conses_vector = UNBOUND;

Object Available_frame_serial_conses_tail_vector = UNBOUND;

Object Frame_serial_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Frame_serial_cons_counter, Qframe_serial_cons_counter);

/* OUTSTANDING-FRAME-SERIAL-CONSES */
Object outstanding_frame_serial_conses()
{
    Object temp;

    x_note_fn_call(33,60);
    temp = FIXNUM_MINUS(Frame_serial_cons_counter,
	    length(Available_frame_serial_conses));
    return VALUES_1(temp);
}

/* FRAME-SERIAL-CONS-MEMORY-USAGE */
Object frame_serial_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(33,61);
    temp = FIXNUM_TIMES(Frame_serial_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-FRAME-SERIAL-CONS-POOL */
Object replenish_frame_serial_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(33,62);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qframe_serial_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Frame_serial_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qframe_serial;       /* frame-serial */

/* FRAME-SERIAL-CONS-1 */
Object frame_serial_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(33,63);
    new_cons = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_frame_serial_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_frame_serial_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-FRAME-SERIAL-LIST-POOL */
Object replenish_frame_serial_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(33,64);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qframe_serial_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-FRAME-SERIAL-LIST-1 */
Object make_frame_serial_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(33,65);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_frame_serial_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_frame_serial_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_frame_serial_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FRAME-SERIAL-LIST-2 */
Object frame_serial_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,66);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_serial_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe_serial);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_serial_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* FRAME-SERIAL-LIST-3 */
Object frame_serial_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,67);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_serial_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe_serial);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_serial_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* FRAME-SERIAL-LIST-4 */
Object frame_serial_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,68);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_serial_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe_serial);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_serial_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* FRAME-SERIAL-LIST-TRACE-HOOK */
Object frame_serial_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(33,69);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-FRAME-SERIAL-CONSES-1 */
Object copy_tree_using_frame_serial_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,70);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_serial_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_serial_cons_pool();
	temp_1 = copy_tree_using_frame_serial_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_serial_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_serial_cons_pool();
	temp_1 = 
		copy_tree_using_frame_serial_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-FRAME-SERIAL-CONSES-1 */
Object copy_list_using_frame_serial_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,71);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_serial_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_serial_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_frame_serial_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_serial_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_serial_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_serial_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe_serial);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-FRAME-SERIAL-CONS-1 */
Object reclaim_frame_serial_cons_1(frame_serial_cons)
    Object frame_serial_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(33,72);
    inline_note_reclaim_cons(frame_serial_cons,Qframe_serial);
    if (ISVREF(Available_frame_serial_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_frame_serial_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = frame_serial_cons;
	temp = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_serial_cons;
    }
    else {
	temp = Available_frame_serial_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_serial_cons;
	temp = Available_frame_serial_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_serial_cons;
    }
    M_CDR(frame_serial_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-LIST-1 */
Object reclaim_frame_serial_list_1(frame_serial_list)
    Object frame_serial_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,73);
    if (frame_serial_list) {
	last_1 = frame_serial_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qframe_serial);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qframe_serial);
	if (ISVREF(Available_frame_serial_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_frame_serial_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = frame_serial_list;
	    temp = Available_frame_serial_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_frame_serial_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = frame_serial_list;
	    temp = Available_frame_serial_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-FRAME-SERIAL-LIST*-1 */
Object reclaim_frame_serial_list_star_1(frame_serial_list)
    Object frame_serial_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(33,74);
    if (CONSP(frame_serial_list)) {
	temp = last(frame_serial_list,_);
	M_CDR(temp) = Nil;
	if (frame_serial_list) {
	    last_1 = frame_serial_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qframe_serial);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qframe_serial);
	    if (ISVREF(Available_frame_serial_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_frame_serial_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = frame_serial_list;
		temp = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_frame_serial_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = frame_serial_list;
		temp = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-FRAME-SERIAL-TREE-1 */
Object reclaim_frame_serial_tree_1(tree)
    Object tree;
{
    Object e, e2, frame_serial_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,75);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_frame_serial_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		frame_serial_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(frame_serial_cons,Qframe_serial);
		if (EQ(frame_serial_cons,e))
		    goto end_1;
		else if ( !TRUEP(frame_serial_cons))
		    goto end_1;
		else
		    frame_serial_cons = CDR(frame_serial_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_frame_serial_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_frame_serial_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_frame_serial_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-FRAME-SERIAL-ELEMENT-1 */
Object delete_frame_serial_element_1(element,frame_serial_list)
    Object element, frame_serial_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(33,76);
    if (frame_serial_list) {
	if (EQ(element,M_CAR(frame_serial_list))) {
	    temp = CDR(frame_serial_list);
	    inline_note_reclaim_cons(frame_serial_list,Qframe_serial);
	    if (ISVREF(Available_frame_serial_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_frame_serial_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = frame_serial_list;
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_serial_list;
	    }
	    else {
		temp_1 = Available_frame_serial_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_serial_list;
		temp_1 = Available_frame_serial_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_serial_list;
	    }
	    M_CDR(frame_serial_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = frame_serial_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qframe_serial);
		if (ISVREF(Available_frame_serial_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_frame_serial_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_frame_serial_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_frame_serial_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_frame_serial_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = frame_serial_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-FRAME-SERIAL-CONS-1 */
Object delete_frame_serial_cons_1(frame_serial_cons,frame_serial_list)
    Object frame_serial_cons, frame_serial_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(33,77);
    if (EQ(frame_serial_cons,frame_serial_list))
	temp = CDR(frame_serial_list);
    else {
	l_trailer_qm = Nil;
	l = frame_serial_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,frame_serial_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = frame_serial_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_frame_serial_cons_1(frame_serial_cons);
    return VALUES_1(temp);
}

Object Max_fixnum_frame_serial_number = UNBOUND;

/* INCREMENT-CURRENT-FRAME-SERIAL-NUMBER */
Object increment_current_frame_serial_number()
{
    Object current, temp, temp_1;

    x_note_fn_call(33,78);
    current = Current_frame_serial_number;
    if (FIXNUMP(current)) {
	Current_frame_serial_number = FIXNUM_EQ(current,
		Max_fixnum_frame_serial_number) ? 
		frame_serial_cons_1(FIX((SI_Long)1L),FIX((SI_Long)0L)) : 
		FIXNUM_ADD1(current);
	temp = Current_frame_serial_number;
    }
    else {
	if (FIXNUM_EQ(M_CDR(current),Max_fixnum_frame_serial_number)) {
	    temp_1 = FIXNUM_ADD1(M_CAR(current));
	    M_CAR(current) = temp_1;
	    M_CDR(current) = FIX((SI_Long)0L);
	}
	else {
	    temp_1 = FIXNUM_ADD1(M_CDR(current));
	    M_CDR(current) = temp_1;
	}
	temp = current;
    }
    return VALUES_1(temp);
}

/* COPY-FRAME-SERIAL-NUMBER */
Object copy_frame_serial_number(x)
    Object x;
{
    Object temp, msp, lsp;

    x_note_fn_call(33,79);
    if (FIXNUMP(x) ||  !TRUEP(x))
	temp = x;
    else {
	msp = M_CAR(x);
	lsp = M_CDR(x);
	temp = frame_serial_cons_1(msp,lsp);
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-<=-FUNCTION */
Object frame_serial_number_lt_eq_function(x,y)
    Object x, y;
{
    Object temp, xa, ya;

    x_note_fn_call(33,80);
    if (FIXNUMP(x))
	temp = FIXNUMP(y) ? (FIXNUM_LE(x,y) ? T : Nil) : T;
    else if (FIXNUMP(y))
	temp = Nil;
    else {
	xa = M_CAR(x);
	ya = M_CAR(y);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? (FIXNUM_LE(M_CDR(x),M_CDR(y)) ? T : 
		    Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER->=-FUNCTION */
Object frame_serial_number_gt_eq_function(x,y)
    Object x, y;
{
    Object temp, xa, ya;

    x_note_fn_call(33,81);
    if (FIXNUMP(y))
	temp = FIXNUMP(x) ? (FIXNUM_LE(y,x) ? T : Nil) : T;
    else if (FIXNUMP(x))
	temp = Nil;
    else {
	xa = M_CAR(y);
	ya = M_CAR(x);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? (FIXNUM_LE(M_CDR(y),M_CDR(x)) ? T : 
		    Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-<-FUNCTION */
Object frame_serial_number_lt_function(x,y)
    Object x, y;
{
    Object temp, xa, ya;

    x_note_fn_call(33,82);
    if (FIXNUMP(x))
	temp = FIXNUMP(y) ? (FIXNUM_LT(x,y) ? T : Nil) : T;
    else if (FIXNUMP(y))
	temp = Nil;
    else {
	xa = M_CAR(x);
	ya = M_CAR(y);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? (FIXNUM_LT(M_CDR(x),M_CDR(y)) ? T : 
		    Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER->-FUNCTION */
Object frame_serial_number_gt_function(x,y)
    Object x, y;
{
    Object temp, xa, ya;

    x_note_fn_call(33,83);
    if (FIXNUMP(y))
	temp = FIXNUMP(x) ? (FIXNUM_LT(y,x) ? T : Nil) : T;
    else if (FIXNUMP(x))
	temp = Nil;
    else {
	xa = M_CAR(y);
	ya = M_CAR(x);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? (FIXNUM_LT(M_CDR(y),M_CDR(x)) ? T : 
		    Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-EQUAL-FUNCTION */
Object frame_serial_number_equal_function(x,y)
    Object x, y;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;

    x_note_fn_call(33,84);
    gensymed_symbol = x;
    gensymed_symbol_1 = y;
    temp = FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	    (FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) ? T : Nil) : 
	    Nil) : FIXNUMP(gensymed_symbol_1) ? Nil : 
	    FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) ? 
	    (FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1)) ? 
	    T : Nil) : Qnil;
    return VALUES_1(temp);
}

Object Reclaimed_frame_serial_number_marker = UNBOUND;

/* RECLAIM-FRAME-SERIAL-NUMBER */
Object reclaim_frame_serial_number(x)
    Object x;
{
    x_note_fn_call(33,85);
    if ( !(FIXNUMP(x) ||  !TRUEP(x) || EQ(x,No_saved_initial_value)))
	reclaim_frame_serial_cons_1(x);
    return VALUES_1(Nil);
}

/* FRAME-SERIAL-NUMBER-SETF-HELPER-1 */
Object frame_serial_number_setf_helper_1(old,new_1)
    Object old, new_1;
{
    Object temp, new_msp, new_lsp;

    x_note_fn_call(33,86);
    if ( !TRUEP(old) || FIXNUMP(old) || EQ(old,No_saved_initial_value))
	temp = copy_frame_serial_number(new_1);
    else if ( !TRUEP(new_1) || FIXNUMP(new_1)) {
	reclaim_frame_serial_number(old);
	temp = new_1;
    }
    else {
	new_msp = M_CAR(new_1);
	new_lsp = M_CDR(new_1);
	M_CAR(old) = new_msp;
	M_CDR(old) = new_lsp;
	temp = old;
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-0 */
Object frame_serial_number_0()
{
    x_note_fn_call(33,87);
    return VALUES_1(FIX((SI_Long)0L));
}

/* FRAME-SERIAL-NUMBER-RECYCLED-FUNCTION */
Object frame_serial_number_recycled_function()
{
    x_note_fn_call(33,88);
    return VALUES_1(FIX((SI_Long)-1L));
}

/* FRAME-SERIAL-NUMBER-HASH-FUNCTION */
Object frame_serial_number_hash_function(fsn)
    Object fsn;
{
    Object temp;

    x_note_fn_call(33,89);
    temp = FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn));
    return VALUES_1(temp);
}

static Object float_constant;      /* 0.0 */

/* G2-INSTANCE-CREATION-COUNT-AS-FLOAT */
Object g2_instance_creation_count_as_float()
{
    Object fsn, temp;
    double temp_1, temp_2, temp_3;

    x_note_fn_call(33,90);
    fsn = Current_frame_serial_number;
    if (FIXNUMP(fsn))
	return lfloat(fsn,float_constant);
    else {
	temp = lfloat(M_CDR(fsn),float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(M_CAR(fsn),float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(Max_fixnum_frame_serial_number,float_constant);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2 * (temp_3 + 
		1.0)));
    }
}

/* RESET-CURRENT-FRAME-SERIAL-NUMBER */
Object reset_current_frame_serial_number()
{
    Object frame_serial_number_setf_arg;
    Object star_current_frame_serial_number_star_new_value;

    x_note_fn_call(33,91);
    frame_serial_number_setf_arg = frame_serial_number_0();
    star_current_frame_serial_number_star_new_value = 
	    (FIXNUMP(Current_frame_serial_number) ||  
	    !TRUEP(Current_frame_serial_number)) && 
	    (FIXNUMP(frame_serial_number_setf_arg) ||  
	    !TRUEP(frame_serial_number_setf_arg)) ? 
	    frame_serial_number_setf_arg : 
	    frame_serial_number_setf_helper_1(Current_frame_serial_number,
	    frame_serial_number_setf_arg);
    Current_frame_serial_number = 
	    star_current_frame_serial_number_star_new_value;
    return VALUES_1(Current_frame_serial_number);
}

Object The_type_description_of_byte_code_body = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_byte_code_bodys, Qchain_of_available_byte_code_bodys);

DEFINE_VARIABLE_WITH_SYMBOL(Byte_code_body_count, Qbyte_code_body_count);

Object Chain_of_available_byte_code_bodys_vector = UNBOUND;

/* BYTE-CODE-BODY-STRUCTURE-MEMORY-USAGE */
Object byte_code_body_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,92);
    temp = Byte_code_body_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BYTE-CODE-BODY-COUNT */
Object outstanding_byte_code_body_count()
{
    Object def_structure_byte_code_body_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,93);
    gensymed_symbol = IFIX(Byte_code_body_count);
    def_structure_byte_code_body_variable = Chain_of_available_byte_code_bodys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_byte_code_body_variable))
	goto end_loop;
    def_structure_byte_code_body_variable = 
	    ISVREF(def_structure_byte_code_body_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BYTE-CODE-BODY-1 */
Object reclaim_byte_code_body_1(byte_code_body)
    Object byte_code_body;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(33,94);
    inline_note_reclaim_cons(byte_code_body,Nil);
    structure_being_reclaimed = byte_code_body;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_byte_vector(ISVREF(byte_code_body,(SI_Long)2L));
      SVREF(byte_code_body,FIX((SI_Long)2L)) = Nil;
      reclaim_if_simple_vector_of_slot_values(ISVREF(byte_code_body,
	      (SI_Long)3L));
      SVREF(byte_code_body,FIX((SI_Long)3L)) = Nil;
      reclaim_slot_value(ISVREF(byte_code_body,(SI_Long)4L));
      SVREF(byte_code_body,FIX((SI_Long)4L)) = Nil;
      reclaim_slot_value(ISVREF(byte_code_body,(SI_Long)5L));
      SVREF(byte_code_body,FIX((SI_Long)5L)) = Nil;
      reclaim_slot_value(ISVREF(byte_code_body,(SI_Long)6L));
      SVREF(byte_code_body,FIX((SI_Long)6L)) = Nil;
      reclaim_if_simple_vector_of_slot_values(ISVREF(byte_code_body,
	      (SI_Long)7L));
      SVREF(byte_code_body,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_byte_code_bodys_vector,
	    IFIX(Current_thread_index));
    SVREF(byte_code_body,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_byte_code_bodys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = byte_code_body;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BYTE-CODE-BODY */
Object reclaim_structure_for_byte_code_body(byte_code_body)
    Object byte_code_body;
{
    x_note_fn_call(33,95);
    return reclaim_byte_code_body_1(byte_code_body);
}

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

/* MAKE-PERMANENT-BYTE-CODE-BODY-STRUCTURE-INTERNAL */
Object make_permanent_byte_code_body_structure_internal()
{
    Object def_structure_byte_code_body_variable;
    Object defstruct_g2_byte_code_body_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,96);
    def_structure_byte_code_body_variable = Nil;
    atomic_incff_symval(Qbyte_code_body_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_byte_code_body_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_byte_code_body_variable = the_array;
	SVREF(defstruct_g2_byte_code_body_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_byte_code_body_g2_struct;
	def_structure_byte_code_body_variable = 
		defstruct_g2_byte_code_body_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_byte_code_body_variable);
}

/* MAKE-BYTE-CODE-BODY-1 */
Object make_byte_code_body_1(byte_code_body_length,
	    byte_code_body_byte_vector,byte_code_body_constant_vector,
	    byte_code_body_environment_description,
	    byte_code_body_free_references)
    Object byte_code_body_length, byte_code_body_byte_vector;
    Object byte_code_body_constant_vector;
    Object byte_code_body_environment_description;
    Object byte_code_body_free_references;
{
    Object def_structure_byte_code_body_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,97);
    def_structure_byte_code_body_variable = 
	    ISVREF(Chain_of_available_byte_code_bodys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_byte_code_body_variable) {
	svref_arg_1 = Chain_of_available_byte_code_bodys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_byte_code_body_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_byte_code_body_g2_struct;
    }
    else
	def_structure_byte_code_body_variable = 
		make_permanent_byte_code_body_structure_internal();
    inline_note_allocate_cons(def_structure_byte_code_body_variable,Nil);
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)1L)) = 
	    byte_code_body_length;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)2L)) = 
	    byte_code_body_byte_vector;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)3L)) = 
	    byte_code_body_constant_vector;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)4L)) = 
	    byte_code_body_environment_description;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)7L)) = 
	    byte_code_body_free_references;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_byte_code_body_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_byte_code_body_variable);
}

/* RECLAIM-IF-SIMPLE-VECTOR-OF-SLOT-VALUES */
Object reclaim_if_simple_vector_of_slot_values(simple_vector_qm)
    Object simple_vector_qm;
{
    x_note_fn_call(33,98);
    if (simple_vector_qm)
	return reclaim_simple_vector_of_slot_values(simple_vector_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-SIMPLE-VECTOR-OF-SLOT-VALUES */
Object reclaim_simple_vector_of_slot_values(simple_vector)
    Object simple_vector;
{
    Object value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(33,99);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simple_vector));
    value = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    value = ISVREF(simple_vector,index_1);
    if ( !(FIXNUMP(value) || SYMBOLP(value)))
	reclaim_slot_value(value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_managed_simple_vector(simple_vector);
    return VALUES_1(Nil);
}

/* COPY-IF-BYTE-CODE-SUBVECTOR */
Object copy_if_byte_code_subvector(simple_vector_qm)
    Object simple_vector_qm;
{
    Object vector_length, new_vector, value, svref_new_value, temp;
    SI_Long constant_index, ab_loop_bind_;

    x_note_fn_call(33,100);
    if (simple_vector_qm) {
	vector_length = SIMPLE_ARRAY_ANY_1_LENGTH(simple_vector_qm);
	new_vector = allocate_managed_simple_vector(vector_length);
	constant_index = (SI_Long)0L;
	ab_loop_bind_ = IFIX(vector_length);
	value = Nil;
      next_loop:
	if (constant_index >= ab_loop_bind_)
	    goto end_loop;
	value = ISVREF(simple_vector_qm,constant_index);
	if (FIXNUMP(value) || SYMBOLP(value))
	    ISVREF(new_vector,constant_index) = value;
	else if (thing_is_item_p(value))
	    ISVREF(new_vector,constant_index) = Nil;
	else {
	    svref_new_value = copy_for_slot_value(value);
	    ISVREF(new_vector,constant_index) = svref_new_value;
	}
	constant_index = constant_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	temp = new_vector;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COPY-BYTE-CODE-BODY */
Object copy_byte_code_body(byte_code_body)
    Object byte_code_body;
{
    Object byte_vector_length, old_byte_vector, new_byte_vector;
    Object new_constant_vector, new_environment_description;
    Object new_free_reference_vector, temp;

    x_note_fn_call(33,101);
    byte_vector_length = ISVREF(byte_code_body,(SI_Long)1L);
    old_byte_vector = ISVREF(byte_code_body,(SI_Long)2L);
    new_byte_vector = allocate_byte_vector(byte_vector_length);
    new_constant_vector = 
	    copy_if_byte_code_subvector(ISVREF(byte_code_body,(SI_Long)3L));
    new_environment_description = 
	    copy_for_slot_value(ISVREF(byte_code_body,(SI_Long)4L));
    new_free_reference_vector = 
	    copy_if_byte_code_subvector(ISVREF(byte_code_body,(SI_Long)7L));
    copy_byte_vector_portion(old_byte_vector,FIX((SI_Long)0L),
	    new_byte_vector,FIX((SI_Long)0L),byte_vector_length);
    temp = make_byte_code_body_1(byte_vector_length,new_byte_vector,
	    new_constant_vector,new_environment_description,
	    new_free_reference_vector);
    return VALUES_1(temp);
}

Object Special_annotation_lookup_structure_marker = UNBOUND;

/* GET-LOOKUP-STRUCTURE-IF-ANY */
Object get_lookup_structure_if_any(item)
    Object item;
{
    Object byte_code_body_qm, constant_vector_qm, lookup_structure_qm;

    x_note_fn_call(33,102);
    byte_code_body_qm = get_byte_code_body_if_any(item,Nil);
    constant_vector_qm = byte_code_body_qm ? ISVREF(byte_code_body_qm,
	    (SI_Long)3L) : Qnil;
    lookup_structure_qm = constant_vector_qm ? ISVREF(constant_vector_qm,
	    IFIX(FIXNUM_SUB1(length(constant_vector_qm)))) : Qnil;
    if (CONSP(lookup_structure_qm) && EQ(M_CAR(lookup_structure_qm),
	    Special_annotation_lookup_structure_marker))
	return VALUES_2(M_CDR(lookup_structure_qm),constant_vector_qm);
    else
	return VALUES_1(Nil);
}

/* CLEAN-OUT-ANNOTATION-LOOKUP-STRUCTURE */
Object clean_out_annotation_lookup_structure(item)
    Object item;
{
    Object lookup_structure_qm, constant_vector, svref_arg_2;
    Object result;

    x_note_fn_call(33,103);
    result = get_lookup_structure_if_any(item);
    MVS_2(result,lookup_structure_qm,constant_vector);
    if (lookup_structure_qm) {
	reclaim_slot_value(lookup_structure_qm);
	svref_arg_2 = FIXNUM_SUB1(length(constant_vector));
	ISVREF(constant_vector,IFIX(svref_arg_2)) = FIX((SI_Long)0L);
    }
    return VALUES_1(Nil);
}

/* DUPLICATES-P */
Object duplicates_p(list_1)
    Object list_1;
{
    Object element, ab_loop_list_, rest_of_list, ab_loop_it_;
    Object ab_loop_iter_flag_;

    x_note_fn_call(33,104);
    element = Nil;
    ab_loop_list_ = list_1;
    rest_of_list = CDR(list_1);
    ab_loop_it_ = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	rest_of_list = CDR(rest_of_list);
    ab_loop_it_ = memq_function(element,rest_of_list);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INTERSECTS-P */
Object intersects_p(list1,list2)
    Object list1, list2;
{
    Object symbol, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(33,105);
    symbol = Nil;
    ab_loop_list_ = list1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = memq_function(symbol,list2);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Tree_traversal_marker = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Available_tree_ordering_conses, Qavailable_tree_ordering_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_tree_ordering_conses_tail, Qavailable_tree_ordering_conses_tail);

Object Available_tree_ordering_conses_vector = UNBOUND;

Object Available_tree_ordering_conses_tail_vector = UNBOUND;

Object Tree_ordering_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Tree_ordering_cons_counter, Qtree_ordering_cons_counter);

/* OUTSTANDING-TREE-ORDERING-CONSES */
Object outstanding_tree_ordering_conses()
{
    Object temp;

    x_note_fn_call(33,106);
    temp = FIXNUM_MINUS(Tree_ordering_cons_counter,
	    length(Available_tree_ordering_conses));
    return VALUES_1(temp);
}

/* TREE-ORDERING-CONS-MEMORY-USAGE */
Object tree_ordering_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(33,107);
    temp = FIXNUM_TIMES(Tree_ordering_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-TREE-ORDERING-CONS-POOL */
Object replenish_tree_ordering_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(33,108);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qtree_ordering_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Tree_ordering_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qtree_ordering;      /* tree-ordering */

/* TREE-ORDERING-CONS-1 */
Object tree_ordering_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(33,109);
    new_cons = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_tree_ordering_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-TREE-ORDERING-LIST-POOL */
Object replenish_tree_ordering_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(33,110);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qtree_ordering_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-TREE-ORDERING-LIST-1 */
Object make_tree_ordering_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(33,111);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_tree_ordering_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_tree_ordering_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TREE-ORDERING-LIST-2 */
Object tree_ordering_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,112);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_tree_ordering_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtree_ordering);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_tree_ordering_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* TREE-ORDERING-LIST-3 */
Object tree_ordering_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,113);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_tree_ordering_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtree_ordering);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_tree_ordering_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* TREE-ORDERING-LIST-4 */
Object tree_ordering_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(33,114);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_tree_ordering_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtree_ordering);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_tree_ordering_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* TREE-ORDERING-LIST-TRACE-HOOK */
Object tree_ordering_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(33,115);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-TREE-ORDERING-CONSES-1 */
Object copy_tree_using_tree_ordering_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,116);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_tree_ordering_cons_pool();
	temp_1 = copy_tree_using_tree_ordering_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_tree_ordering_cons_pool();
	temp_1 = 
		copy_tree_using_tree_ordering_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-TREE-ORDERING-CONSES-1 */
Object copy_list_using_tree_ordering_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(33,117);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_tree_ordering_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_tree_ordering_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_tree_ordering_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_tree_ordering_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtree_ordering);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-TREE-ORDERING-CONS-1 */
Object reclaim_tree_ordering_cons_1(tree_ordering_cons)
    Object tree_ordering_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(33,118);
    inline_note_reclaim_cons(tree_ordering_cons,Qtree_ordering);
    if (ISVREF(Available_tree_ordering_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_tree_ordering_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = tree_ordering_cons;
	temp = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = tree_ordering_cons;
    }
    else {
	temp = Available_tree_ordering_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = tree_ordering_cons;
	temp = Available_tree_ordering_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = tree_ordering_cons;
    }
    M_CDR(tree_ordering_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-TREE-ORDERING-LIST-1 */
Object reclaim_tree_ordering_list_1(tree_ordering_list)
    Object tree_ordering_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,119);
    if (tree_ordering_list) {
	last_1 = tree_ordering_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qtree_ordering);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qtree_ordering);
	if (ISVREF(Available_tree_ordering_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = tree_ordering_list;
	    temp = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = tree_ordering_list;
	    temp = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-TREE-ORDERING-LIST*-1 */
Object reclaim_tree_ordering_list_star_1(tree_ordering_list)
    Object tree_ordering_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(33,120);
    if (CONSP(tree_ordering_list)) {
	temp = last(tree_ordering_list,_);
	M_CDR(temp) = Nil;
	if (tree_ordering_list) {
	    last_1 = tree_ordering_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qtree_ordering);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qtree_ordering);
	    if (ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree_ordering_list;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_tree_ordering_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree_ordering_list;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-TREE-ORDERING-TREE-1 */
Object reclaim_tree_ordering_tree_1(tree)
    Object tree;
{
    Object e, e2, tree_ordering_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(33,121);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_tree_ordering_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		tree_ordering_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(tree_ordering_cons,Qtree_ordering);
		if (EQ(tree_ordering_cons,e))
		    goto end_1;
		else if ( !TRUEP(tree_ordering_cons))
		    goto end_1;
		else
		    tree_ordering_cons = CDR(tree_ordering_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_tree_ordering_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-TREE-ORDERING-ELEMENT-1 */
Object delete_tree_ordering_element_1(element,tree_ordering_list)
    Object element, tree_ordering_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(33,122);
    if (tree_ordering_list) {
	if (EQ(element,M_CAR(tree_ordering_list))) {
	    temp = CDR(tree_ordering_list);
	    inline_note_reclaim_cons(tree_ordering_list,Qtree_ordering);
	    if (ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = tree_ordering_list;
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = tree_ordering_list;
	    }
	    else {
		temp_1 = Available_tree_ordering_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = tree_ordering_list;
		temp_1 = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = tree_ordering_list;
	    }
	    M_CDR(tree_ordering_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = tree_ordering_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qtree_ordering);
		if (ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_tree_ordering_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_tree_ordering_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = tree_ordering_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-TREE-ORDERING-CONS-1 */
Object delete_tree_ordering_cons_1(tree_ordering_cons,tree_ordering_list)
    Object tree_ordering_cons, tree_ordering_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(33,123);
    if (EQ(tree_ordering_cons,tree_ordering_list))
	temp = CDR(tree_ordering_list);
    else {
	l_trailer_qm = Nil;
	l = tree_ordering_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,tree_ordering_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = tree_ordering_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_tree_ordering_cons_1(tree_ordering_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_sub_profiling_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sub_profiling_structures, Qchain_of_available_sub_profiling_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Sub_profiling_structure_count, Qsub_profiling_structure_count);

Object Chain_of_available_sub_profiling_structures_vector = UNBOUND;

/* SUB-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object sub_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,124);
    temp = Sub_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SUB-PROFILING-STRUCTURE-COUNT */
Object outstanding_sub_profiling_structure_count()
{
    Object def_structure_sub_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,125);
    gensymed_symbol = IFIX(Sub_profiling_structure_count);
    def_structure_sub_profiling_structure_variable = 
	    Chain_of_available_sub_profiling_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_sub_profiling_structure_variable))
	goto end_loop;
    def_structure_sub_profiling_structure_variable = 
	    ISVREF(def_structure_sub_profiling_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SUB-PROFILING-STRUCTURE-1 */
Object reclaim_sub_profiling_structure_1(sub_profiling_structure)
    Object sub_profiling_structure;
{
    Object structure_being_reclaimed, managed_float, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(33,126);
    inline_note_reclaim_cons(sub_profiling_structure,Nil);
    structure_being_reclaimed = sub_profiling_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      managed_float = ISVREF(sub_profiling_structure,(SI_Long)2L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(sub_profiling_structure,FIX((SI_Long)2L)) = Nil;
      managed_float = ISVREF(sub_profiling_structure,(SI_Long)3L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(sub_profiling_structure,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_sub_profiling_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(sub_profiling_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sub_profiling_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = sub_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SUB-PROFILING-STRUCTURE */
Object reclaim_structure_for_sub_profiling_structure(sub_profiling_structure)
    Object sub_profiling_structure;
{
    x_note_fn_call(33,127);
    return reclaim_sub_profiling_structure_1(sub_profiling_structure);
}

static Object Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::sub-profiling-structure-g2-struct */

/* MAKE-PERMANENT-SUB-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_sub_profiling_structure_structure_internal()
{
    Object def_structure_sub_profiling_structure_variable;
    Object defstruct_g2_sub_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,128);
    def_structure_sub_profiling_structure_variable = Nil;
    atomic_incff_symval(Qsub_profiling_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_sub_profiling_structure_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_sub_profiling_structure_variable = the_array;
	SVREF(defstruct_g2_sub_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct;
	def_structure_sub_profiling_structure_variable = 
		defstruct_g2_sub_profiling_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_sub_profiling_structure_variable);
}

static Object Qfloat_array;        /* float-array */

/* MAKE-SUB-PROFILING-STRUCTURE-1 */
Object make_sub_profiling_structure_1()
{
    Object def_structure_sub_profiling_structure_variable, temp, temp_1;
    Object svref_new_value, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float;

    x_note_fn_call(33,129);
    def_structure_sub_profiling_structure_variable = 
	    ISVREF(Chain_of_available_sub_profiling_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_sub_profiling_structure_variable) {
	temp = Chain_of_available_sub_profiling_structures_vector;
	temp_1 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_sub_profiling_structure_variable,
		(SI_Long)0L);
	SVREF(temp,temp_1) = svref_new_value;
	SVREF(def_structure_sub_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct;
    }
    else
	def_structure_sub_profiling_structure_variable = 
		make_permanent_sub_profiling_structure_structure_internal();
    inline_note_allocate_cons(def_structure_sub_profiling_structure_variable,
	    Nil);
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
    SVREF(def_structure_sub_profiling_structure_variable,FIX((SI_Long)2L)) 
	    = new_float;
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
    SVREF(def_structure_sub_profiling_structure_variable,FIX((SI_Long)3L)) 
	    = new_float;
    return VALUES_1(def_structure_sub_profiling_structure_variable);
}

Object The_type_description_of_basic_profiling_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_basic_profiling_structures, Qchain_of_available_basic_profiling_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Basic_profiling_structure_count, Qbasic_profiling_structure_count);

Object Chain_of_available_basic_profiling_structures_vector = UNBOUND;

/* BASIC-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object basic_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,130);
    temp = Basic_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BASIC-PROFILING-STRUCTURE-COUNT */
Object outstanding_basic_profiling_structure_count()
{
    Object def_structure_basic_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,131);
    gensymed_symbol = IFIX(Basic_profiling_structure_count);
    def_structure_basic_profiling_structure_variable = 
	    Chain_of_available_basic_profiling_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_basic_profiling_structure_variable))
	goto end_loop;
    def_structure_basic_profiling_structure_variable = 
	    ISVREF(def_structure_basic_profiling_structure_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BASIC-PROFILING-STRUCTURE-INTERNAL-1 */
Object reclaim_basic_profiling_structure_internal_1(basic_profiling_structure)
    Object basic_profiling_structure;
{
    Object structure_being_reclaimed, managed_float, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(33,132);
    inline_note_reclaim_cons(basic_profiling_structure,Nil);
    structure_being_reclaimed = basic_profiling_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_profiling_name(ISVREF(basic_profiling_structure,(SI_Long)1L));
      SVREF(basic_profiling_structure,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(basic_profiling_structure,
	      (SI_Long)3L));
      SVREF(basic_profiling_structure,FIX((SI_Long)3L)) = Nil;
      managed_float = ISVREF(basic_profiling_structure,(SI_Long)4L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(basic_profiling_structure,FIX((SI_Long)4L)) = Nil;
      reclaim_managed_simple_vector(ISVREF(basic_profiling_structure,
	      (SI_Long)6L));
      SVREF(basic_profiling_structure,FIX((SI_Long)6L)) = Nil;
      reclaim_managed_float_array(ISVREF(basic_profiling_structure,
	      (SI_Long)7L));
      SVREF(basic_profiling_structure,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_basic_profiling_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(basic_profiling_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_basic_profiling_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = basic_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BASIC-PROFILING-STRUCTURE */
Object reclaim_structure_for_basic_profiling_structure(basic_profiling_structure)
    Object basic_profiling_structure;
{
    x_note_fn_call(33,133);
    return reclaim_basic_profiling_structure_internal_1(basic_profiling_structure);
}

static Object Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::basic-profiling-structure-g2-struct */

/* MAKE-PERMANENT-BASIC-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_basic_profiling_structure_structure_internal()
{
    Object def_structure_basic_profiling_structure_variable;
    Object defstruct_g2_basic_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,134);
    def_structure_basic_profiling_structure_variable = Nil;
    atomic_incff_symval(Qbasic_profiling_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_basic_profiling_structure_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_basic_profiling_structure_variable = the_array;
	SVREF(defstruct_g2_basic_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct;
	def_structure_basic_profiling_structure_variable = 
		defstruct_g2_basic_profiling_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_basic_profiling_structure_variable);
}

Object Registered_activities_array = UNBOUND;

/* MAKE-BASIC-PROFILING-STRUCTURE1-1 */
Object make_basic_profiling_structure1_1()
{
    Object def_structure_basic_profiling_structure_variable, temp, temp_1;
    Object svref_new_value, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float;

    x_note_fn_call(33,135);
    def_structure_basic_profiling_structure_variable = 
	    ISVREF(Chain_of_available_basic_profiling_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_basic_profiling_structure_variable) {
	temp = Chain_of_available_basic_profiling_structures_vector;
	temp_1 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_basic_profiling_structure_variable,
		(SI_Long)0L);
	SVREF(temp,temp_1) = svref_new_value;
	SVREF(def_structure_basic_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct;
    }
    else
	def_structure_basic_profiling_structure_variable = 
		make_permanent_basic_profiling_structure_structure_internal();
    inline_note_allocate_cons(def_structure_basic_profiling_structure_variable,
	    Nil);
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)3L)) = Nil;
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
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)4L)) = new_float;
    ISVREF(def_structure_basic_profiling_structure_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    temp = allocate_managed_simple_vector(length(Registered_activities_array));
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)6L)) = temp;
    temp = allocate_managed_float_array(1,length(Registered_activities_array));
    SVREF(def_structure_basic_profiling_structure_variable,
	    FIX((SI_Long)7L)) = temp;
    return VALUES_1(def_structure_basic_profiling_structure_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_profile_structure_qm, Qcurrent_profile_structure_qm);

/* RECLAIM-BASIC-PROFILING-STRUCTURE */
Object reclaim_basic_profiling_structure(bps)
    Object bps;
{
    x_note_fn_call(33,136);
    if (EQ(bps,Current_profile_structure_qm))
	Current_profile_structure_qm = Nil;
    reclaim_basic_profiling_structure_internal_1(bps);
    return VALUES_1(Nil);
}

/* RECLAIM-PROFILING-NAME */
Object reclaim_profiling_name(name)
    Object name;
{
    x_note_fn_call(33,137);
    if ( !SYMBOLP(name))
	return reclaim_frame_serial_number(name);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_call_hash_hash_vector_43_vectors, Qavailable_call_hash_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_call_hash_hash_vector_43_vectors, Qcount_of_call_hash_hash_vector_43_vectors);

Object Available_call_hash_hash_vector_43_vectors_vector = UNBOUND;

/* CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object call_hash_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(33,138);
    temp = Count_of_call_hash_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-CALL-HASH-HASH-VECTOR-43-VECTORS */
Object out_call_hash_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(33,139);
    temp = FIXNUM_MINUS(Count_of_call_hash_hash_vector_43_vectors,
	    length(Available_call_hash_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-CALL-HASH-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_call_hash_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(33,140);
    atomic_incff_symval(Qcount_of_call_hash_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-CALL-HASH-HASH-VECTOR */
Object make_call_hash_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(33,141);
    if (ISVREF(Available_call_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = Available_call_hash_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = make_permanent_call_hash_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-CALL-HASH-HASH-VECTOR */
Object reclaim_call_hash_hash_vector(call_hash_hash_vector_43_vector)
    Object call_hash_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(33,142);
    svref_arg_1 = Available_call_hash_hash_vector_43_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = call_hash_hash_vector_43_vector;
    temp = ISVREF(Available_call_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MAKE-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_call_hash_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(33,143);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_call_hash_tree_for_hash_skip_list_entry(node,new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(33,144);
    reclaim_basic_profiling_structure(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_call_hash_tree_for_hash_skip_list_entry = UNBOUND;

/* CLEAR-CALL-HASH-TREE */
Object clear_call_hash_tree(call_hash_tree_for_hash_skip_list)
    Object call_hash_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_entry;
    Object result;

    x_note_fn_call(33,145);
    head = M_CAR(M_CDR(call_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(call_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    call_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    SYMBOLP(key_qm) ? FIX(SXHASH_SYMBOL_1(key_qm) & 
	    IFIX(Most_positive_fixnum)) : frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_basic_profiling_structure(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(call_hash_tree_for_hash_skip_list);
}

static Object Qcall_hash_tree_for_hash;  /* call-hash-tree-for-hash */

/* MAKE-CALL-HASH */
Object make_call_hash()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(33,146);
    new_vector = make_call_hash_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_call_hash_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_call_hash_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qcall_hash_tree_for_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-CALL-HASH */
Object flatten_call_hash(call_hash_hash_table)
    Object call_hash_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(33,147);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(call_hash_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-CALL-HASH */
Object clear_call_hash(call_hash_hash_table)
    Object call_hash_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(33,148);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_call_hash_tree(ISVREF(call_hash_hash_table,index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-CALL-HASH */
Object reclaim_call_hash(call_hash_hash_table)
    Object call_hash_hash_table;
{
    Object call_hash_tree_for_hash_skip_list, head, tail, element_qm, key_qm;
    Object temp, old_entry, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(33,149);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    call_hash_tree_for_hash_skip_list = ISVREF(call_hash_hash_table,index_1);
    head = M_CAR(M_CDR(call_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(call_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    call_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    SYMBOLP(key_qm) ? FIX(SXHASH_SYMBOL_1(key_qm) & 
	    IFIX(Most_positive_fixnum)) : frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_basic_profiling_structure(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(call_hash_tree_for_hash_skip_list) = Nil;
    M_CADR(call_hash_tree_for_hash_skip_list) = Nil;
    M_CAR(call_hash_tree_for_hash_skip_list) = Nil;
    if (call_hash_tree_for_hash_skip_list) {
	last_1 = call_hash_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = call_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = call_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(call_hash_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_call_hash_hash_vector(call_hash_hash_table);
    return VALUES_1(temp);
}

/* MAKE-CALL-HASH-FUNCTION */
Object make_call_hash_function()
{
    x_note_fn_call(33,150);
    return make_call_hash();
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_sub_call_hash_hash_vector_43_vectors, Qavailable_sub_call_hash_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_sub_call_hash_hash_vector_43_vectors, Qcount_of_sub_call_hash_hash_vector_43_vectors);

Object Available_sub_call_hash_hash_vector_43_vectors_vector = UNBOUND;

/* SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object sub_call_hash_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(33,151);
    temp = Count_of_sub_call_hash_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS */
Object out_sub_call_hash_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(33,152);
    temp = FIXNUM_MINUS(Count_of_sub_call_hash_hash_vector_43_vectors,
	    length(Available_sub_call_hash_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_sub_call_hash_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(33,153);
    atomic_incff_symval(Qcount_of_sub_call_hash_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-SUB-CALL-HASH-HASH-VECTOR */
Object make_sub_call_hash_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(33,154);
    if (ISVREF(Available_sub_call_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_sub_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = Available_sub_call_hash_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_sub_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_sub_call_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = make_permanent_sub_call_hash_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-SUB-CALL-HASH-HASH-VECTOR */
Object reclaim_sub_call_hash_hash_vector(sub_call_hash_hash_vector_43_vector)
    Object sub_call_hash_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(33,155);
    svref_arg_1 = Available_sub_call_hash_hash_vector_43_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = sub_call_hash_hash_vector_43_vector;
    temp = ISVREF(Available_sub_call_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MAKE-SUB-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_sub_call_hash_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(33,156);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-SUB-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_sub_call_hash_tree_for_hash_skip_list_entry(node,new_key,
	    new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(33,157);
    reclaim_sub_profiling_structure_1(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_sub_call_hash_tree_for_hash_skip_list_entry = UNBOUND;

/* CLEAR-SUB-CALL-HASH-TREE */
Object clear_sub_call_hash_tree(sub_call_hash_tree_for_hash_skip_list)
    Object sub_call_hash_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_entry;
    Object result;

    x_note_fn_call(33,158);
    head = M_CAR(M_CDR(sub_call_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(sub_call_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    sub_call_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    SYMBOLP(key_qm) ? FIX(SXHASH_SYMBOL_1(key_qm) & 
	    IFIX(Most_positive_fixnum)) : frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_sub_profiling_structure_1(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(sub_call_hash_tree_for_hash_skip_list);
}

static Object Qsub_call_hash_tree_for_hash;  /* sub-call-hash-tree-for-hash */

/* MAKE-SUB-CALL-HASH */
Object make_sub_call_hash()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(33,159);
    new_vector = make_sub_call_hash_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_sub_call_hash_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_sub_call_hash_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qsub_call_hash_tree_for_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-SUB-CALL-HASH */
Object flatten_sub_call_hash(sub_call_hash_hash_table)
    Object sub_call_hash_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(33,160);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(sub_call_hash_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-SUB-CALL-HASH */
Object clear_sub_call_hash(sub_call_hash_hash_table)
    Object sub_call_hash_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(33,161);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_sub_call_hash_tree(ISVREF(sub_call_hash_hash_table,index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-SUB-CALL-HASH */
Object reclaim_sub_call_hash(sub_call_hash_hash_table)
    Object sub_call_hash_hash_table;
{
    Object sub_call_hash_tree_for_hash_skip_list, head, tail, element_qm;
    Object key_qm, temp, old_entry, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(33,162);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    sub_call_hash_tree_for_hash_skip_list = 
	    ISVREF(sub_call_hash_hash_table,index_1);
    head = M_CAR(M_CDR(sub_call_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(sub_call_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    sub_call_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    SYMBOLP(key_qm) ? FIX(SXHASH_SYMBOL_1(key_qm) & 
	    IFIX(Most_positive_fixnum)) : frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_sub_profiling_structure_1(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(sub_call_hash_tree_for_hash_skip_list) = Nil;
    M_CADR(sub_call_hash_tree_for_hash_skip_list) = Nil;
    M_CAR(sub_call_hash_tree_for_hash_skip_list) = Nil;
    if (sub_call_hash_tree_for_hash_skip_list) {
	last_1 = sub_call_hash_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = sub_call_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = sub_call_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(sub_call_hash_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_sub_call_hash_hash_vector(sub_call_hash_hash_table);
    return VALUES_1(temp);
}

Object The_type_description_of_global_profiling_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_global_profiling_structures, Qchain_of_available_global_profiling_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Global_profiling_structure_count, Qglobal_profiling_structure_count);

Object Chain_of_available_global_profiling_structures_vector = UNBOUND;

/* GLOBAL-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object global_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,163);
    temp = Global_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GLOBAL-PROFILING-STRUCTURE-COUNT */
Object outstanding_global_profiling_structure_count()
{
    Object def_structure_global_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,164);
    gensymed_symbol = IFIX(Global_profiling_structure_count);
    def_structure_global_profiling_structure_variable = 
	    Chain_of_available_global_profiling_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_global_profiling_structure_variable))
	goto end_loop;
    def_structure_global_profiling_structure_variable = 
	    ISVREF(def_structure_global_profiling_structure_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GLOBAL-PROFILING-STRUCTURE-1 */
Object reclaim_global_profiling_structure_1(global_profiling_structure)
    Object global_profiling_structure;
{
    Object structure_being_reclaimed, managed_float, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(33,165);
    inline_note_reclaim_cons(global_profiling_structure,Nil);
    structure_being_reclaimed = global_profiling_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      managed_float = ISVREF(global_profiling_structure,(SI_Long)2L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)2L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)3L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)3L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)4L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)4L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)5L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)5L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)6L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)6L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)7L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)7L)) = Nil;
      managed_float = ISVREF(global_profiling_structure,(SI_Long)8L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(global_profiling_structure,FIX((SI_Long)8L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_global_profiling_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(global_profiling_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_global_profiling_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = global_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GLOBAL-PROFILING-STRUCTURE */
Object reclaim_structure_for_global_profiling_structure(global_profiling_structure)
    Object global_profiling_structure;
{
    x_note_fn_call(33,166);
    return reclaim_global_profiling_structure_1(global_profiling_structure);
}

static Object Qg2_defstruct_structure_name_global_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::global-profiling-structure-g2-struct */

/* MAKE-PERMANENT-GLOBAL-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_global_profiling_structure_structure_internal()
{
    Object def_structure_global_profiling_structure_variable;
    Object defstruct_g2_global_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,167);
    def_structure_global_profiling_structure_variable = Nil;
    atomic_incff_symval(Qglobal_profiling_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_global_profiling_structure_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_global_profiling_structure_variable = the_array;
	SVREF(defstruct_g2_global_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_global_profiling_structure_g2_struct;
	def_structure_global_profiling_structure_variable = 
		defstruct_g2_global_profiling_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_global_profiling_structure_variable);
}

/* MAKE-GLOBAL-PROFILING-STRUCTURE-1 */
Object make_global_profiling_structure_1()
{
    Object def_structure_global_profiling_structure_variable, temp, temp_1;
    Object svref_new_value, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float;

    x_note_fn_call(33,168);
    def_structure_global_profiling_structure_variable = 
	    ISVREF(Chain_of_available_global_profiling_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_global_profiling_structure_variable) {
	temp = Chain_of_available_global_profiling_structures_vector;
	temp_1 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_global_profiling_structure_variable,
		(SI_Long)0L);
	SVREF(temp,temp_1) = svref_new_value;
	SVREF(def_structure_global_profiling_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_global_profiling_structure_g2_struct;
    }
    else
	def_structure_global_profiling_structure_variable = 
		make_permanent_global_profiling_structure_structure_internal();
    inline_note_allocate_cons(def_structure_global_profiling_structure_variable,
	    Nil);
    temp = make_call_hash_function();
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)1L)) = temp;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)2L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)3L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)4L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)5L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)6L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)7L)) = new_float;
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
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)8L)) = new_float;
    return VALUES_1(def_structure_global_profiling_structure_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);

/* CHECK-SHAPE-OF-WINDOW-WITHOUT-LOOKAHEAD-FOR-G2 */
Object check_shape_of_window_without_lookahead_for_g2(gensym_window,
	    native_window)
    Object gensym_window, native_window;
{
    Object work_was_done_qm, gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;

    x_note_fn_call(33,169);
    work_was_done_qm = Nil;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = 0.0;
    gensymed_symbol_2 = 0.0;
    if (Profiling_enabled_qm) {
	gensymed_symbol = T;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_2 = g2ext_unix_time_as_float();
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,gensymed_symbol_2);
    }
    work_was_done_qm = 
	    check_shape_of_window_without_lookahead(gensym_window,
	    native_window);
    if (Profiling_enabled_qm) {
	gensymed_symbol_3 = g2ext_unix_time_as_float();
	gensymed_symbol_4 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_5 = gensymed_symbol_3 - gensymed_symbol_4;
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)5L);
	aref_new_value = gensymed_symbol_5 + 
		DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)5L),
		(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	aref_new_value = gensymed_symbol ? gensymed_symbol_1 + 
		gensymed_symbol_5 + (gensymed_symbol_4 - 
		gensymed_symbol_2) : gensymed_symbol_3;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    return VALUES_1(work_was_done_qm);
}

/* SYNC-GRAPHICS-ON-NATIVE-WINDOW-MAYBE-WITH-TRACING */
Object sync_graphics_on_native_window_maybe_with_tracing(native_window)
    Object native_window;
{
    Object gensymed_symbol, aref_arg_1, temp;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;

    x_note_fn_call(33,170);
    gensymed_symbol = Nil;
    gensymed_symbol_1 = 0.0;
    gensymed_symbol_2 = 0.0;
    if (Profiling_enabled_qm) {
	gensymed_symbol = T;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_2 = g2ext_unix_time_as_float();
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,gensymed_symbol_2);
    }
    temp = sync_graphics_on_native_window_1(native_window);
    if (Profiling_enabled_qm) {
	gensymed_symbol_3 = g2ext_unix_time_as_float();
	gensymed_symbol_4 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_5 = gensymed_symbol_3 - gensymed_symbol_4;
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)5L);
	aref_new_value = gensymed_symbol_5 + 
		DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)5L),
		(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	aref_new_value = gensymed_symbol ? gensymed_symbol_1 + 
		gensymed_symbol_5 + (gensymed_symbol_4 - 
		gensymed_symbol_2) : gensymed_symbol_3;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    return VALUES_1(temp);
}

/* C-WRITE-EXACT-FLOAT-FROM-C */
Object c_write_exact_float_from_c(return_string,double_1)
    Object return_string, double_1;
{
    Object gensymed_symbol, temp;
    char *temp_1;
    double temp_2;

    x_note_fn_call(33,171);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(return_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = return_string;
    temp_1 = ISTRING(temp);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(double_1);
    g2ext_g_fmt(temp_1,temp_2);
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

void utilities4_INIT()
{
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, temp;
    Object reclaim_structure_for_byte_code_body_1;
    Object reclaim_structure_for_sub_profiling_structure_1;
    Object reclaim_structure_for_basic_profiling_structure_1;
    Object reclaim_structure_for_global_profiling_structure_1;
    Object Qglobal_profiling_structure, Qreclaim_structure;
    Object Qoutstanding_global_profiling_structure_count;
    Object Qglobal_profiling_structure_structure_memory_usage, Qutilities2;
    Object AB_package, string_constant_18, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_17, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmutate_sub_call_hash_tree_for_hash_skip_list_entry;
    Object Qout_sub_call_hash_hash_vector_43_vectors;
    Object Qsub_call_hash_hash_vector_43_vector_memory_usage;
    Object string_constant_16, Qmutate_call_hash_tree_for_hash_skip_list_entry;
    Object Qout_call_hash_hash_vector_43_vectors;
    Object Qcall_hash_hash_vector_43_vector_memory_usage, string_constant_15;
    Object Qbasic_profiling_structure;
    Object Qoutstanding_basic_profiling_structure_count;
    Object Qbasic_profiling_structure_structure_memory_usage;
    Object string_constant_14, string_constant_13, Qsub_profiling_structure;
    Object Qoutstanding_sub_profiling_structure_count;
    Object Qsub_profiling_structure_structure_memory_usage, string_constant_12;
    Object string_constant_11, string_constant_10;
    Object Qtree_ordering_cons_memory_usage, Qoutstanding_tree_ordering_conses;
    Object Qutilities1, list_constant_1, Qtree_ordering_cons_counter_vector;
    Object list_constant, Qavailable_tree_ordering_conses_tail_vector;
    Object Qavailable_tree_ordering_conses_vector, string_constant_9;
    Object string_constant_8, string_constant_7;
    Object Qspecial_annotation_lookup_structure_marker, Qbyte_code_body;
    Object Qoutstanding_byte_code_body_count;
    Object Qbyte_code_body_structure_memory_usage, string_constant_6;
    Object string_constant_5, Qframe_serial_number_0, string_constant_4;
    Object string_constant_3, Qframe_serial_cons_memory_usage;
    Object Qoutstanding_frame_serial_conses, Qframe_serial_cons_counter_vector;
    Object Qavailable_frame_serial_conses_tail_vector;
    Object Qavailable_frame_serial_conses_vector, list_constant_4, Qutilities4;
    Object Kfuncall, Qfunction_keeps_procedure_environment_valid_qm;
    Object Qkb_specific_variable_plist, Qreclaim_gensym_list_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, string_constant_2;
    Object Qreclaim_kb_property_list_function, list_constant_3;
    Object Qinitialize_kb_state_changes, list_constant_2, Qkb_0;
    Object string_constant_1, Qkb_property_cons_memory_usage;
    Object Qoutstanding_kb_property_conses, Qkb_property_cons_counter_vector;
    Object Qmake_thread_array, Qavailable_kb_property_conses_tail_vector;
    Object Qavailable_kb_property_conses_vector;

    x_note_fn_call(33,172);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qavailable_kb_property_conses = 
	    STATIC_SYMBOL("AVAILABLE-KB-PROPERTY-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_kb_property_conses,
	    Available_kb_property_conses);
    Qutilities4 = STATIC_SYMBOL("UTILITIES4",AB_package);
    record_system_variable(Qavailable_kb_property_conses,Qutilities4,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_kb_property_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-KB-PROPERTY-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_kb_property_conses_tail,
	    Available_kb_property_conses_tail);
    record_system_variable(Qavailable_kb_property_conses_tail,Qutilities4,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_kb_property_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-KB-PROPERTY-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_kb_property_conses_vector,
	    Available_kb_property_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_kb_property_conses_vector,
	    Qutilities4,list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_kb_property_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-KB-PROPERTY-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_kb_property_conses_tail_vector,
	    Available_kb_property_conses_tail_vector);
    record_system_variable(Qavailable_kb_property_conses_tail_vector,
	    Qutilities4,list_constant,Qnil,Qt,Qnil,Qnil);
    Qkb_property_cons_counter_vector = 
	    STATIC_SYMBOL("KB-PROPERTY-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_property_cons_counter_vector,
	    Kb_property_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qkb_property_cons_counter_vector,Qutilities4,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qkb_property_cons_counter = STATIC_SYMBOL("KB-PROPERTY-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_property_cons_counter,
	    Kb_property_cons_counter);
    record_system_variable(Qkb_property_cons_counter,Qutilities4,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_kb_property_conses = 
	    STATIC_SYMBOL("OUTSTANDING-KB-PROPERTY-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_kb_property_conses,
	    STATIC_FUNCTION(outstanding_kb_property_conses,NIL,FALSE,0,0));
    Qkb_property_cons_memory_usage = 
	    STATIC_SYMBOL("KB-PROPERTY-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qkb_property_cons_memory_usage,
	    STATIC_FUNCTION(kb_property_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_1 = STATIC_STRING("1q83-bsy9k83-bry09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_kb_property_conses);
    push_optimized_constant(Qkb_property_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qkb_property = STATIC_SYMBOL("KB-PROPERTY",AB_package);
    Qcurrent_kb_specific_property_list_property_name = 
	    STATIC_SYMBOL("*CURRENT-KB-SPECIFIC-PROPERTY-LIST-PROPERTY-NAME*",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_kb_specific_property_list_property_name,
	    Current_kb_specific_property_list_property_name);
    Qkb_0 = STATIC_SYMBOL("KB-0",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qquote,Qkb_0);
    record_system_variable(Qcurrent_kb_specific_property_list_property_name,
	    Qutilities4,list_constant_2,Qnil,Qt,Qnil,Qnil);
    if (Locations_of_kb_specific_property_lists == UNBOUND)
	Locations_of_kb_specific_property_lists = Nil;
    Qkb_state_changes = STATIC_SYMBOL("KB-STATE-CHANGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_state_changes,Kb_state_changes);
    Qinitialize_kb_state_changes = 
	    STATIC_SYMBOL("INITIALIZE-KB-STATE-CHANGES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_kb_state_changes,
	    STATIC_FUNCTION(initialize_kb_state_changes,NIL,FALSE,0,0));
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_kb_state_changes);
    Qreclaim_kb_property_list_function = 
	    STATIC_SYMBOL("RECLAIM-KB-PROPERTY-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_kb_property_list_function,
	    STATIC_FUNCTION(reclaim_kb_property_list_function,NIL,FALSE,1,1));
    record_system_variable(Qkb_state_changes,Qutilities4,list_constant_3,
	    Qnil,Qnil,Qreclaim_kb_property_list_function,Qt);
    Qthere_is_a_current_kb_qm = STATIC_SYMBOL("*THERE-IS-A-CURRENT-KB\?*",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthere_is_a_current_kb_qm,
	    There_is_a_current_kb_qm);
    record_system_variable(Qthere_is_a_current_kb_qm,Qutilities4,Nil,Qnil,
	    Qt,Qnil,Qnil);
    if (Kb_specific_property_names == UNBOUND)
	Kb_specific_property_names = Nil;
    Qfunction_to_copy_global_value_for_this_property_name = 
	    STATIC_SYMBOL("FUNCTION-TO-COPY-GLOBAL-VALUE-FOR-THIS-PROPERTY-NAME",
	    AB_package);
    Function_to_copy_global_value_for_this_property_name_prop = 
	    Qfunction_to_copy_global_value_for_this_property_name;
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    Do_not_carry_global_property_value_into_kbs_qm_prop = 
	    Qdo_not_carry_global_property_value_into_kbs_qm;
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    Function_to_reclaim_kb_specific_property_value_qm_prop = 
	    Qfunction_to_reclaim_kb_specific_property_value_qm;
    string_constant_2 = STATIC_STRING("NO-SPECIFIC-PROPERTY-VALUE");
    if (No_specific_property_value == UNBOUND)
	No_specific_property_value = make_symbol(string_constant_2);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (Symbol_properties_table == UNBOUND) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol) = Qsymbol_properties_hash_table;
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
	M_CAR(gensymed_symbol_1) = head;
	M_CDR(gensymed_symbol_1) = tail;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	M_CDR(gensymed_symbol) = gensymed_symbol_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	Symbol_properties_table = gensymed_symbol;
    }
    if (Last_assigned_global_kb_number == UNBOUND)
	Last_assigned_global_kb_number = FIX((SI_Long)0L);
    string_constant = STATIC_STRING("KB-~D");
    Qlast_assigned_global_kb_number = 
	    STATIC_SYMBOL("LAST-ASSIGNED-GLOBAL-KB-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_assigned_global_kb_number,
	    Last_assigned_global_kb_number);
    Qlocations_of_kb_specific_property_lists = 
	    STATIC_SYMBOL("*LOCATIONS-OF-KB-SPECIFIC-PROPERTY-LISTS*",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocations_of_kb_specific_property_lists,
	    Locations_of_kb_specific_property_lists);
    Qkb_specific_variable_plist = 
	    STATIC_SYMBOL("KB-SPECIFIC-VARIABLE-PLIST",AB_package);
    Kb_specific_property_names = CONS(Qkb_specific_variable_plist,
	    Kb_specific_property_names);
    mutate_global_property(Qkb_specific_variable_plist,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_gensym_list_function = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gensym_list_function,
	    STATIC_FUNCTION(reclaim_gensym_list_function,NIL,FALSE,1,1));
    mutate_global_property(Qkb_specific_variable_plist,
	    Qreclaim_gensym_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Kb_specific_variable_plist_kbprop = Qkb_specific_variable_plist;
    Qlisp_modules_to_be_loaded = STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",
	    AB_package);
    Qsystem_variable_descriptions = 
	    STATIC_SYMBOL("SYSTEM-VARIABLE-DESCRIPTIONS",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    Function_keeps_procedure_environment_valid_qm_prop = 
	    Qfunction_keeps_procedure_environment_valid_qm;
    if (In_edit_warning_context_p == UNBOUND)
	In_edit_warning_context_p = Nil;
    if (Items_warned_in_edit_warning_context == UNBOUND)
	Items_warned_in_edit_warning_context = Nil;
    Qcurrent_frame_serial_number = 
	    STATIC_SYMBOL("*CURRENT-FRAME-SERIAL-NUMBER*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_frame_serial_number,
	    Current_frame_serial_number);
    Qframe_serial_number_0 = STATIC_SYMBOL("FRAME-SERIAL-NUMBER-0",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,Qframe_serial_number_0);
    record_system_variable(Qcurrent_frame_serial_number,Qutilities4,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    Qavailable_frame_serial_conses = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_serial_conses,
	    Available_frame_serial_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_frame_serial_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_frame_serial_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_serial_conses_tail,
	    Available_frame_serial_conses_tail);
    record_system_variable(Qavailable_frame_serial_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_frame_serial_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_serial_conses_vector,
	    Available_frame_serial_conses_vector);
    record_system_variable(Qavailable_frame_serial_conses_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_frame_serial_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_serial_conses_tail_vector,
	    Available_frame_serial_conses_tail_vector);
    record_system_variable(Qavailable_frame_serial_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qframe_serial_cons_counter_vector = 
	    STATIC_SYMBOL("FRAME-SERIAL-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_serial_cons_counter_vector,
	    Frame_serial_cons_counter_vector);
    record_system_variable(Qframe_serial_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qframe_serial_cons_counter = STATIC_SYMBOL("FRAME-SERIAL-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_serial_cons_counter,
	    Frame_serial_cons_counter);
    record_system_variable(Qframe_serial_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_frame_serial_conses = 
	    STATIC_SYMBOL("OUTSTANDING-FRAME-SERIAL-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_frame_serial_conses,
	    STATIC_FUNCTION(outstanding_frame_serial_conses,NIL,FALSE,0,0));
    Qframe_serial_cons_memory_usage = 
	    STATIC_SYMBOL("FRAME-SERIAL-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_serial_cons_memory_usage,
	    STATIC_FUNCTION(frame_serial_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_3 = STATIC_STRING("1q83-V2y9k83-V1y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_frame_serial_conses);
    push_optimized_constant(Qframe_serial_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qframe_serial = STATIC_SYMBOL("FRAME-SERIAL",AB_package);
    Max_fixnum_frame_serial_number = Most_positive_fixnum;
    string_constant_4 = STATIC_STRING("reclaimed-frame-serial-number-marker");
    if (Reclaimed_frame_serial_number_marker == UNBOUND)
	Reclaimed_frame_serial_number_marker = make_symbol(string_constant_4);
    SET_SYMBOL_FUNCTION(Qframe_serial_number_0,
	    STATIC_FUNCTION(frame_serial_number_0,NIL,FALSE,0,0));
    float_constant = STATIC_FLOAT(0.0);
    Current_frame_serial_number = Nil;
    reset_current_frame_serial_number();
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbyte_code_body = STATIC_SYMBOL("BYTE-CODE-BODY",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_byte_code_body_g2_struct,
	    Qbyte_code_body,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qbyte_code_body,
	    Qg2_defstruct_structure_name_byte_code_body_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_byte_code_body == UNBOUND)
	The_type_description_of_byte_code_body = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83fVy1n83fVy8n8k1l8n0000001l1n8y83-2xy1p83rBy83r7y83r8y83r9y83rAykuk0k0");
    temp = The_type_description_of_byte_code_body;
    The_type_description_of_byte_code_body = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_byte_code_body_g2_struct,
	    The_type_description_of_byte_code_body,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qbyte_code_body,
	    The_type_description_of_byte_code_body,Qtype_description_of_type);
    Qoutstanding_byte_code_body_count = 
	    STATIC_SYMBOL("OUTSTANDING-BYTE-CODE-BODY-COUNT",AB_package);
    Qbyte_code_body_structure_memory_usage = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_6 = STATIC_STRING("1q83fVy8s83-L9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_byte_code_body_count);
    push_optimized_constant(Qbyte_code_body_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_byte_code_bodys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BYTE-CODE-BODYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_byte_code_bodys,
	    Chain_of_available_byte_code_bodys);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_byte_code_bodys,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qbyte_code_body_count = STATIC_SYMBOL("BYTE-CODE-BODY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_code_body_count,Byte_code_body_count);
    record_system_variable(Qbyte_code_body_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_byte_code_bodys_vector == UNBOUND)
	Chain_of_available_byte_code_bodys_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbyte_code_body_structure_memory_usage,
	    STATIC_FUNCTION(byte_code_body_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_byte_code_body_count,
	    STATIC_FUNCTION(outstanding_byte_code_body_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_byte_code_body_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_byte_code_body,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qbyte_code_body,
	    reclaim_structure_for_byte_code_body_1);
    Qspecial_annotation_lookup_structure_marker = 
	    STATIC_SYMBOL("SPECIAL-ANNOTATION-LOOKUP-STRUCTURE-MARKER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspecial_annotation_lookup_structure_marker,
	    Special_annotation_lookup_structure_marker);
    string_constant_7 = 
	    STATIC_STRING("spEcIal annOtatiOn LookuP strUctUrE maRkeR");
    string_constant_8 = STATIC_STRING("KEYWORD");
    SET_SYMBOL_VALUE(Qspecial_annotation_lookup_structure_marker,
	    intern(string_constant_7,find_package(string_constant_8)));
    string_constant_9 = STATIC_STRING("TREE-TRAVERSAL-MARKER");
    Tree_traversal_marker = make_symbol(string_constant_9);
    Qavailable_tree_ordering_conses = 
	    STATIC_SYMBOL("AVAILABLE-TREE-ORDERING-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_tree_ordering_conses,
	    Available_tree_ordering_conses);
    record_system_variable(Qavailable_tree_ordering_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_tree_ordering_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-TREE-ORDERING-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_tree_ordering_conses_tail,
	    Available_tree_ordering_conses_tail);
    record_system_variable(Qavailable_tree_ordering_conses_tail,
	    Qutilities1,Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_tree_ordering_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-TREE-ORDERING-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_tree_ordering_conses_vector,
	    Available_tree_ordering_conses_vector);
    record_system_variable(Qavailable_tree_ordering_conses_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_tree_ordering_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-TREE-ORDERING-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_tree_ordering_conses_tail_vector,
	    Available_tree_ordering_conses_tail_vector);
    record_system_variable(Qavailable_tree_ordering_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qtree_ordering_cons_counter_vector = 
	    STATIC_SYMBOL("TREE-ORDERING-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtree_ordering_cons_counter_vector,
	    Tree_ordering_cons_counter_vector);
    record_system_variable(Qtree_ordering_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qtree_ordering_cons_counter = 
	    STATIC_SYMBOL("TREE-ORDERING-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtree_ordering_cons_counter,
	    Tree_ordering_cons_counter);
    record_system_variable(Qtree_ordering_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_tree_ordering_conses = 
	    STATIC_SYMBOL("OUTSTANDING-TREE-ORDERING-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_tree_ordering_conses,
	    STATIC_FUNCTION(outstanding_tree_ordering_conses,NIL,FALSE,0,0));
    Qtree_ordering_cons_memory_usage = 
	    STATIC_SYMBOL("TREE-ORDERING-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qtree_ordering_cons_memory_usage,
	    STATIC_FUNCTION(tree_ordering_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_10 = STATIC_STRING("1q83-tqy9k83-tpy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_tree_ordering_conses);
    push_optimized_constant(Qtree_ordering_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qtree_ordering = STATIC_SYMBOL("TREE-ORDERING",AB_package);
    Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct = 
	    STATIC_SYMBOL("SUB-PROFILING-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsub_profiling_structure = STATIC_SYMBOL("SUB-PROFILING-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct,
	    Qsub_profiling_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsub_profiling_structure,
	    Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_sub_profiling_structure == UNBOUND)
	The_type_description_of_sub_profiling_structure = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83nTy1n83nTy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_sub_profiling_structure;
    The_type_description_of_sub_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    mutate_global_property(Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct,
	    The_type_description_of_sub_profiling_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsub_profiling_structure,
	    The_type_description_of_sub_profiling_structure,
	    Qtype_description_of_type);
    Qoutstanding_sub_profiling_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-SUB-PROFILING-STRUCTURE-COUNT",
	    AB_package);
    Qsub_profiling_structure_structure_memory_usage = 
	    STATIC_SYMBOL("SUB-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_12 = STATIC_STRING("1q83nTy8s83-rKy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sub_profiling_structure_count);
    push_optimized_constant(Qsub_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_sub_profiling_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SUB-PROFILING-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sub_profiling_structures,
	    Chain_of_available_sub_profiling_structures);
    record_system_variable(Qchain_of_available_sub_profiling_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsub_profiling_structure_count = 
	    STATIC_SYMBOL("SUB-PROFILING-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsub_profiling_structure_count,
	    Sub_profiling_structure_count);
    record_system_variable(Qsub_profiling_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_sub_profiling_structures_vector == UNBOUND)
	Chain_of_available_sub_profiling_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsub_profiling_structure_structure_memory_usage,
	    STATIC_FUNCTION(sub_profiling_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_sub_profiling_structure_count,
	    STATIC_FUNCTION(outstanding_sub_profiling_structure_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_sub_profiling_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_sub_profiling_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsub_profiling_structure,
	    reclaim_structure_for_sub_profiling_structure_1);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct = 
	    STATIC_SYMBOL("BASIC-PROFILING-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbasic_profiling_structure = STATIC_SYMBOL("BASIC-PROFILING-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct,
	    Qbasic_profiling_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qbasic_profiling_structure,
	    Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_basic_profiling_structure == UNBOUND)
	The_type_description_of_basic_profiling_structure = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83fKy1n83fKy8n8k1l8n0000001m1m83My83-A4y1m8y83-2pyksk0k0");
    temp = The_type_description_of_basic_profiling_structure;
    The_type_description_of_basic_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct,
	    The_type_description_of_basic_profiling_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qbasic_profiling_structure,
	    The_type_description_of_basic_profiling_structure,
	    Qtype_description_of_type);
    Qoutstanding_basic_profiling_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-BASIC-PROFILING-STRUCTURE-COUNT",
	    AB_package);
    Qbasic_profiling_structure_structure_memory_usage = 
	    STATIC_SYMBOL("BASIC-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83fKy8s83-Kby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_basic_profiling_structure_count);
    push_optimized_constant(Qbasic_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_basic_profiling_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BASIC-PROFILING-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_basic_profiling_structures,
	    Chain_of_available_basic_profiling_structures);
    record_system_variable(Qchain_of_available_basic_profiling_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbasic_profiling_structure_count = 
	    STATIC_SYMBOL("BASIC-PROFILING-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbasic_profiling_structure_count,
	    Basic_profiling_structure_count);
    record_system_variable(Qbasic_profiling_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_basic_profiling_structures_vector == UNBOUND)
	Chain_of_available_basic_profiling_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbasic_profiling_structure_structure_memory_usage,
	    STATIC_FUNCTION(basic_profiling_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_basic_profiling_structure_count,
	    STATIC_FUNCTION(outstanding_basic_profiling_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_basic_profiling_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_basic_profiling_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qbasic_profiling_structure,
	    reclaim_structure_for_basic_profiling_structure_1);
    Qavailable_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_call_hash_hash_vector_43_vectors,
	    Available_call_hash_hash_vector_43_vectors);
    record_system_variable(Qavailable_call_hash_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_call_hash_hash_vector_43_vectors,
	    Count_of_call_hash_hash_vector_43_vectors);
    record_system_variable(Qcount_of_call_hash_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_call_hash_hash_vector_43_vectors_vector == UNBOUND)
	Available_call_hash_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-CALL-HASH-HASH-VECTOR-43-VECTORS",AB_package);
    Qcall_hash_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_15 = STATIC_STRING("1q83-LNy83*9y83-Ony09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_call_hash_hash_vector_43_vectors);
    push_optimized_constant(Qcall_hash_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    SET_SYMBOL_FUNCTION(Qcall_hash_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(call_hash_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_call_hash_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_call_hash_hash_vector_43_vectors,NIL,FALSE,
	    0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qmutate_call_hash_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_call_hash_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_call_hash_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_call_hash_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_call_hash_tree_for_hash_skip_list_entry);
    Qcall_hash_tree_for_hash = STATIC_SYMBOL("CALL-HASH-TREE-FOR-HASH",
	    AB_package);
    Qavailable_sub_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sub_call_hash_hash_vector_43_vectors,
	    Available_sub_call_hash_hash_vector_43_vectors);
    record_system_variable(Qavailable_sub_call_hash_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_sub_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_sub_call_hash_hash_vector_43_vectors,
	    Count_of_sub_call_hash_hash_vector_43_vectors);
    record_system_variable(Qcount_of_sub_call_hash_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_sub_call_hash_hash_vector_43_vectors_vector == UNBOUND)
	Available_sub_call_hash_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_sub_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qsub_call_hash_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83-rJy83*9y83-PBy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_sub_call_hash_hash_vector_43_vectors);
    push_optimized_constant(Qsub_call_hash_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    SET_SYMBOL_FUNCTION(Qsub_call_hash_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(sub_call_hash_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_sub_call_hash_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_sub_call_hash_hash_vector_43_vectors,NIL,
	    FALSE,0,0));
    Qmutate_sub_call_hash_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-SUB-CALL-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_sub_call_hash_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_sub_call_hash_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_sub_call_hash_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_sub_call_hash_tree_for_hash_skip_list_entry);
    Qsub_call_hash_tree_for_hash = 
	    STATIC_SYMBOL("SUB-CALL-HASH-TREE-FOR-HASH",AB_package);
    Qg2_defstruct_structure_name_global_profiling_structure_g2_struct = 
	    STATIC_SYMBOL("GLOBAL-PROFILING-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qglobal_profiling_structure = 
	    STATIC_SYMBOL("GLOBAL-PROFILING-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_global_profiling_structure_g2_struct,
	    Qglobal_profiling_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qglobal_profiling_structure,
	    Qg2_defstruct_structure_name_global_profiling_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_global_profiling_structure == UNBOUND)
	The_type_description_of_global_profiling_structure = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83i1y1n83i1y8n8k1l8n0000000ktk0k0");
    temp = The_type_description_of_global_profiling_structure;
    The_type_description_of_global_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_global_profiling_structure_g2_struct,
	    The_type_description_of_global_profiling_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qglobal_profiling_structure,
	    The_type_description_of_global_profiling_structure,
	    Qtype_description_of_type);
    Qoutstanding_global_profiling_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-GLOBAL-PROFILING-STRUCTURE-COUNT",
	    AB_package);
    Qglobal_profiling_structure_structure_memory_usage = 
	    STATIC_SYMBOL("GLOBAL-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83i1y8s83-Wdy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_global_profiling_structure_count);
    push_optimized_constant(Qglobal_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_global_profiling_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GLOBAL-PROFILING-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_global_profiling_structures,
	    Chain_of_available_global_profiling_structures);
    record_system_variable(Qchain_of_available_global_profiling_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qglobal_profiling_structure_count = 
	    STATIC_SYMBOL("GLOBAL-PROFILING-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_profiling_structure_count,
	    Global_profiling_structure_count);
    record_system_variable(Qglobal_profiling_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_global_profiling_structures_vector == UNBOUND)
	Chain_of_available_global_profiling_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qglobal_profiling_structure_structure_memory_usage,
	    STATIC_FUNCTION(global_profiling_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_global_profiling_structure_count,
	    STATIC_FUNCTION(outstanding_global_profiling_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_global_profiling_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_global_profiling_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qglobal_profiling_structure,
	    reclaim_structure_for_global_profiling_structure_1);
}
