/* utlts4.c
 * Input file:  utilities4.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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
	PUSH_SPECIAL(Current_tokenizer,current_tokenizer,2);
	  current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
	  PUSH_SPECIAL(Current_start_state,current_start_state,1);
	    current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	    PUSH_SPECIAL(Current_anchor_p,current_anchor_p,0);
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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

/* RECLAIM-KB-PROPERTY-LIST-FUNCTION */
Object reclaim_kb_property_list_function(kb_property_list)
    Object kb_property_list;
{
    x_note_fn_call(33,12);
    return reclaim_gensym_list_1(kb_property_list);
}

Object Current_kb_specific_property_list_property_name = UNBOUND;

Object Locations_of_kb_specific_property_lists = UNBOUND;

/* INITIALIZE-KB-STATE-CHANGES */
Object initialize_kb_state_changes()
{
    x_note_fn_call(33,13);
    return gensym_cons_1(Nil,Nil);
}

Object Kb_state_changes = UNBOUND;

Object There_is_a_current_kb_qm = UNBOUND;

Object Kb_specific_property_names = UNBOUND;

Object Function_to_copy_global_value_for_this_property_name_prop = UNBOUND;

Object Do_not_carry_global_property_value_into_kbs_qm_prop = UNBOUND;

Object Function_to_reclaim_kb_specific_property_value_qm_prop = UNBOUND;

Object No_specific_property_value = UNBOUND;

static Object Qab_gensym;          /* gensym */

/* RECLAIM-SYMBOL-PROPERTIES-HASH-TABLE-LEAVES */
Object reclaim_symbol_properties_hash_table_leaves(symbol_properties_hash_table_binary_tree)
    Object symbol_properties_hash_table_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(33,14);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(symbol_properties_hash_table_binary_tree))
	goto end_loop;
    less_than_branch_qm = ISVREF(symbol_properties_hash_table_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(symbol_properties_hash_table_binary_tree,(SI_Long)2L);
    alist = ISVREF(symbol_properties_hash_table_binary_tree,(SI_Long)3L);
    reclaim_binary_tree_element_1(symbol_properties_hash_table_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(alist_entry) = cdr_new_value;
    Available_gensym_conses = alist_entry;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	Available_gensym_conses = alist;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_symbol_properties_hash_table_leaves(less_than_branch_qm);
	symbol_properties_hash_table_binary_tree = greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	symbol_properties_hash_table_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-SYMBOL-PROPERTIES-HASH-TABLE-TREE */
Object clear_symbol_properties_hash_table_tree(symbol_properties_hash_table_binary_tree)
    Object symbol_properties_hash_table_binary_tree;
{
    Object element_qm;

    x_note_fn_call(33,15);
    element_qm = CDR(symbol_properties_hash_table_binary_tree);
    if (element_qm) {
	reclaim_symbol_properties_hash_table_leaves(element_qm);
	M_CDR(symbol_properties_hash_table_binary_tree) = Nil;
    }
    return VALUES_1(symbol_properties_hash_table_binary_tree);
}

Object Symbol_properties_table = UNBOUND;

/* IS-PROPERTY-VALUE-IN-HASH-TABLE? */
Object is_property_value_in_hash_table_qm(properties,property_name)
    Object properties, property_name;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,16);
    if (properties) {
	gensymed_symbol = CDR(properties);
	gensymed_symbol_1 = property_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(property_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4))
		return VALUES_1(M_CDR(M_CAR(gensymed_symbol)));
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* GET-KB-SPECIFIC-PROPERTIES-FROM-HASH-TABLE */
Object get_kb_specific_properties_from_hash_table(symbol)
    Object symbol;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, symbol_properties, kb_specific_properties;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,17);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = symbol;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = symbol;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    symbol_properties = gensymed_symbol;
    gensymed_symbol = CDR(symbol_properties);
    gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
    gensymed_symbol_2 = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    kb_specific_properties = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	kb_specific_properties = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    kb_specific_properties = Qnil;
  end_4:;
    if (kb_specific_properties);
    else
	kb_specific_properties = Nil;
    if ( !TRUEP(kb_specific_properties)) {
	register_symbol_as_location_of_kb_specific_properties(symbol);
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	kb_specific_properties = gensymed_symbol;
	gensymed_symbol = Current_kb_specific_property_list_property_name;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	set_balanced_binary_tree_entry(symbol_properties,Qeq,Nil,T,
		gensymed_symbol,temp_1,kb_specific_properties);
    }
    return VALUES_1(kb_specific_properties);
}

/* GET-SYMBOL-PROPERTIES-FROM-PLIST */
Object get_symbol_properties_from_plist(symbol)
    Object symbol;
{
    x_note_fn_call(33,18);
    return VALUES_1(SYMBOL_PLIST(symbol));
}

/* PUT-SYMBOL-PROPERTIES-INTO-PLIST */
Object put_symbol_properties_into_plist(symbol,properties)
    Object symbol, properties;
{
    x_note_fn_call(33,19);
    return VALUES_1(SET_SYMBOL_PLIST(symbol,properties));
}

/* GET-PROPERTY-VALUE-FROM-PLIST-WITHOUT-DEFAULT */
Object get_property_value_from_plist_without_default(properties,property_name)
    Object properties, property_name;
{
    Object list_1;

    x_note_fn_call(33,20);
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

    x_note_fn_call(33,21);
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

    x_note_fn_call(33,22);
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
	return gensym_cons_1(property_1,gensym_cons_1(value,properties));
}

/* GET-KB-SPECIFIC-PROPERTIES-FROM-PLIST */
Object get_kb_specific_properties_from_plist(symbol)
    Object symbol;
{
    Object property_list, property_1, property_cons;
    Object kb_specific_properties_place, kb_specific_properties;

    x_note_fn_call(33,23);
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

    x_note_fn_call(33,24);
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,25);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = symbol;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = symbol;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    return VALUES_1(gensymed_symbol);
}

/* GET-PROPERTY-VALUE-FUNCTION */
Object get_property_value_function varargs_1(int, n)
{
    Object properties, property_name;
    Object default_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    Object temp;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(33,26);
    INIT_ARGS_nonrelocating();
    properties = REQUIRED_ARG_nonrelocating();
    property_name = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = CDR(properties);
    gensymed_symbol_1 = property_name;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(property_name) & 
	    IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    temp = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(default_1);
}

/* SET-PROPERTY-VALUE-FUNCTION */
Object set_property_value_function(properties,property_1,value)
    Object properties, property_1, value;
{
    Object gensymed_symbol;

    x_note_fn_call(33,27);
    gensymed_symbol = property_1;
    set_balanced_binary_tree_entry(properties,Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),value);
    return VALUES_1(value);
}

/* REGISTER-SYMBOL-AS-LOCATION-OF-KB-SPECIFIC-PROPERTIES */
Object register_symbol_as_location_of_kb_specific_properties(symbol)
    Object symbol;
{
    Object gensymed_symbol, ab_loop_list_;
    Object location_of_list_of_kb_specific_symbols, cdr_new_value;

    x_note_fn_call(33,28);
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
	cdr_new_value = gensym_cons_1(symbol,
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,29);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = symbol;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = symbol;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    gensymed_symbol = CDR(global_properties);
    gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
    gensymed_symbol_2 = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    kb_properties = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	kb_properties = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    kb_properties = Qnil;
  end_4:;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	gensymed_symbol = CDR(kb_properties);
	gensymed_symbol_1 = property_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(property_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_5;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    kb_specific_value = Qnil;
	  end_5:;
	    goto end_6;
	}
	goto next_loop_4;
      end_loop_4:
	kb_specific_value = Qnil;
      end_6:;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = property_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(property_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_6:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_6;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_7:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_7;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		resulting_value = M_CDR(M_CAR(gensymed_symbol));
		goto end_7;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_7;
	  end_loop_7:
	    resulting_value = Qnil;
	  end_7:;
	    goto end_8;
	}
	goto next_loop_6;
      end_loop_6:
	resulting_value = Qnil;
      end_8:;
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
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, global_properties, properties;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,30);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = symbol;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = symbol;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    if (There_is_a_current_kb_qm) {
	gensymed_symbol = Current_kb_specific_property_list_property_name;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	gensymed_symbol_1 = property_1;
	temp = get_kb_specific_properties_from_hash_table(symbol);
	set_balanced_binary_tree_entry(temp,Qeq,Nil,T,gensymed_symbol_1,
		FIX(SXHASH_SYMBOL_1(gensymed_symbol_1) & 
		IFIX(Most_positive_fixnum)),value);
	set_balanced_binary_tree_entry(global_properties,Qeq,Nil,T,
		gensymed_symbol,temp_1,
		get_kb_specific_properties_from_hash_table(symbol));
	properties = global_properties;
    }
    else {
	gensymed_symbol = property_1;
	set_balanced_binary_tree_entry(global_properties,Qeq,Nil,T,
		gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),value);
	properties = global_properties;
    }
    gensymed_symbol = symbol;
    temp_1 = Symbol_properties_table;
    set_balanced_binary_tree_entry(temp_1,Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),properties);
    return VALUES_1(value);
}

static Object Qfunction_to_copy_global_value_for_this_property_name;  /* function-to-copy-global-value-for-this-property-name */

/* COPY-KB-SPECIFIC-PROPERTY-FROM-GLOBAL-IF-NECESSARY */
Object copy_kb_specific_property_from_global_if_necessary(symbol,property_1)
    Object symbol, property_1;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp, temp_1;
    Object new_cons, temp_2;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(33,31);
    gensymed_symbol = CDR(Symbol_properties_table);
    gensymed_symbol_1 = symbol;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    gensymed_symbol = Qnil;
  end_2:;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = symbol;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol_1) = Nil;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,T,
		gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
    gensymed_symbol_2 = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    temp_1 = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	temp_1 = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    temp_1 = Qnil;
  end_4:;
    if (temp_1);
    else
	temp_1 = Nil;
    if ( !TRUEP(is_property_value_in_hash_table_qm(temp_1,property_1))) {
	temp = 
		SYMBOL_FUNCTION(getfq_function_no_default(INLINE_SYMBOL_PLIST(property_1),
		Qfunction_to_copy_global_value_for_this_property_name));
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = symbol;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_5;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    gensymed_symbol = Qnil;
	  end_5:;
	    goto end_6;
	}
	goto next_loop_4;
      end_loop_4:
	gensymed_symbol = Qnil;
      end_6:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
	    temp_2 = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp_2,Qeq,
		    Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = property_1;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(property_1) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_6:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_6;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_7:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_7;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		temp_1 = M_CDR(M_CAR(gensymed_symbol));
		goto end_7;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_7;
	  end_loop_7:
	    temp_1 = Qnil;
	  end_7:;
	    goto end_8;
	}
	goto next_loop_6;
      end_loop_6:
	temp_1 = Qnil;
      end_8:;
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
    Object symbol_properties, specific_property_list, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_4, temp, temp_1, new_cons;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_next_node_qm_;
    Object ab_current_alist_, ab_entry_cons_, property_1, property_value;
    Object reclaimer_qm, ab_less_than_branch_qm_, element_qm, cdr_new_value;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    Declare_special(1);

    x_note_fn_call(33,32);
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
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = symbol;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(symbol) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_3;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		goto end_2;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	    gensymed_symbol = Qnil;
	  end_2:;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	gensymed_symbol = Qnil;
      end_3:;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	symbol_properties = gensymed_symbol;
	gensymed_symbol = CDR(symbol_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
	gensymed_symbol_2 = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_4:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_4;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_5:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_5;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		temp_1 = M_CDR(M_CAR(gensymed_symbol));
		goto end_4;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_5;
	  end_loop_5:
	    temp_1 = Qnil;
	  end_4:;
	    goto end_5;
	}
	goto next_loop_4;
      end_loop_4:
	temp_1 = Qnil;
      end_5:;
	if (temp_1);
	else
	    temp_1 = Nil;
	specific_property_list = temp_1;
	if (specific_property_list &&  ! 
		    !TRUEP(M_CDR(specific_property_list))) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_next_node_qm_ = specific_property_list;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    property_1 = Nil;
	    property_value = Nil;
	    PUSH_SPECIAL(Scope_conses,scope_conses,0);
	      reclaimer_qm = Nil;
	      ab_next_node_qm_ = M_CDR(ab_next_node_qm_);
	    next_loop_6:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else {
		  if (ab_next_node_qm_) {
		      ab_current_node_ = ab_next_node_qm_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_7:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_6;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_7;
		    end_loop_6:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_qm_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_qm_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_7;
	      property_1 = CAR(ab_entry_cons_);
	      property_value = CDR(ab_entry_cons_);
	      reclaimer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(property_1),
		      Qfunction_to_reclaim_kb_specific_property_value_qm);
	      if (reclaimer_qm) {
		  temp_1 = SYMBOL_FUNCTION(reclaimer_qm);
		  FUNCALL_1(temp_1,property_value);
	      }
	      goto next_loop_6;
	    end_loop_7:;
	    POP_SPECIAL();
	    element_qm = M_CDR(specific_property_list);
	    if (element_qm)
		reclaim_symbol_properties_hash_table_leaves(element_qm);
	    inline_note_reclaim_cons(specific_property_list,Qab_gensym);
	    cdr_new_value = Available_gensym_conses;
	    M_CDR(specific_property_list) = cdr_new_value;
	    Available_gensym_conses = specific_property_list;
	}
	temp_1 = Current_kb_specific_property_list_property_name;
	temp = symbol_properties;
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),temp_1,temp,
		FIX(SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum)));
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(CDAR(location_cons_qm));
	M_CDAR(location_cons_qm) = Nil;
	if ( !TRUEP(keep_locations_entry_qm)) {
	    reclaim_gensym_cons_1(CAR(location_cons_qm));
	    Locations_of_kb_specific_property_lists = 
		    delete_gensym_cons_1(location_cons_qm,
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

    x_note_fn_call(33,33);
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

    x_note_fn_call(33,34);
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
    Object kb_specific_property_list_cons, property_value_cons, new_cons;
    Object gensymed_symbol, gensymed_symbol_1, temp, ab_loop_list_;
    Object location_of_list_of_kb_specific_symbols;

    x_note_fn_call(33,35);
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
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol) = property_1;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = value;
	    temp = M_CAR(kb_specific_property_list_cons);
	    M_CDR(gensymed_symbol_1) = temp;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    M_CDR(gensymed_symbol) = gensymed_symbol_1;
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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
	temp = gensym_cons_1(symbol,
		M_CDR(location_of_list_of_kb_specific_symbols));
	M_CDR(location_of_list_of_kb_specific_symbols) = temp;
	temp = 
		gensym_cons_1(Current_kb_specific_property_list_property_name,
		gensym_cons_1(gensym_cons_1(property_1,gensym_cons_1(value,
		Nil)),SYMBOL_PLIST(symbol)));
	SET_SYMBOL_PLIST(symbol,temp);
    }
    return VALUES_1(value);
}

Object Last_assigned_global_kb_number = UNBOUND;

Object Global_grammar = UNBOUND;

static Object string_constant;     /* "KB-~D" */

/* SWITCH-TO-NEW-EMPTY-KB */
Object switch_to_new_empty_kb()
{
    Object last_assigned_global_kb_number_new_value;
    Object kb_specific_property_list_property_name, temp;

    x_note_fn_call(33,36);
    restore_debugging_parameters_to_default_values();
    restore_backup_journaling_parameters_to_default_values();
    reclaim_items_deleted_since_load_or_save();
    There_is_a_current_kb_qm = T;
    set_current_grammar(Global_grammar);
    last_assigned_global_kb_number_new_value = 
	    FIXNUM_ADD1(Last_assigned_global_kb_number);
    Last_assigned_global_kb_number = last_assigned_global_kb_number_new_value;
    kb_specific_property_list_property_name = intern_text_string(1,
	    tformat_text_string(2,string_constant,
	    Last_assigned_global_kb_number));
    Locations_of_kb_specific_property_lists = 
	    gensym_cons_1(gensym_cons_1(kb_specific_property_list_property_name,
	    Nil),Locations_of_kb_specific_property_lists);
    switch_to_kb(kb_specific_property_list_property_name);
    initialize_data_server_properties();
    initialize_modules_and_system_tables_a_list();
    temp = initialize_kb_name_directories();
    return VALUES_1(temp);
}

Object Kb_specific_variable_plist_kbprop = UNBOUND;

Object Current_system_name = UNBOUND;

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

    x_note_fn_call(33,37);
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

    x_note_fn_call(33,38);
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

Object In_edit_warning_context_p = UNBOUND;

Object Items_warned_in_edit_warning_context = UNBOUND;

Object Current_frame_serial_number = UNBOUND;

/* CURRENT-FRAME-SERIAL-NUMBER-FUNCTION */
Object current_frame_serial_number_function()
{
    x_note_fn_call(33,39);
    return VALUES_1(Current_frame_serial_number);
}

/* COPY-OF-CURRENT-FRAME-SERIAL-NUMBER-FUNCTION */
Object copy_of_current_frame_serial_number_function()
{
    x_note_fn_call(33,40);
    return copy_frame_serial_number(Current_frame_serial_number);
}

Object Max_fixnum_frame_serial_number = UNBOUND;

/* INCREMENT-CURRENT-FRAME-SERIAL-NUMBER */
Object increment_current_frame_serial_number()
{
    Object current, temp, temp_1;

    x_note_fn_call(33,41);
    current = Current_frame_serial_number;
    if (FIXNUMP(current)) {
	Current_frame_serial_number = FIXNUM_EQ(current,
		Max_fixnum_frame_serial_number) ? 
		gensym_cons_1(FIX((SI_Long)1L),FIX((SI_Long)0L)) : 
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

    x_note_fn_call(33,42);
    if (FIXNUMP(x) ||  !TRUEP(x))
	temp = x;
    else {
	msp = M_CAR(x);
	lsp = M_CDR(x);
	temp = gensym_cons_1(msp,lsp);
    }
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-<=-FUNCTION */
Object frame_serial_number_lt_eq_function(x,y)
    Object x, y;
{
    Object temp, xa, ya;

    x_note_fn_call(33,43);
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

    x_note_fn_call(33,44);
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

    x_note_fn_call(33,45);
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

    x_note_fn_call(33,46);
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

    x_note_fn_call(33,47);
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
    x_note_fn_call(33,48);
    if ( !(FIXNUMP(x) ||  !TRUEP(x) || EQ(x,No_saved_initial_value)))
	reclaim_gensym_cons_1(x);
    return VALUES_1(Nil);
}

/* FRAME-SERIAL-NUMBER-SETF-HELPER-1 */
Object frame_serial_number_setf_helper_1(old,new_1)
    Object old, new_1;
{
    Object temp, new_msp, new_lsp;

    x_note_fn_call(33,49);
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
    x_note_fn_call(33,50);
    return VALUES_1(FIX((SI_Long)0L));
}

/* FRAME-SERIAL-NUMBER-RECYCLED-FUNCTION */
Object frame_serial_number_recycled_function()
{
    x_note_fn_call(33,51);
    return VALUES_1(FIX((SI_Long)-1L));
}

/* FRAME-SERIAL-NUMBER-HASH-FUNCTION */
Object frame_serial_number_hash_function(fsn)
    Object fsn;
{
    Object temp;

    x_note_fn_call(33,52);
    temp = FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn));
    return VALUES_1(temp);
}

static Object float_constant;      /* 0.0 */

/* G2-INSTANCE-CREATION-COUNT-AS-FLOAT */
Object g2_instance_creation_count_as_float()
{
    Object fsn, temp;
    double temp_1, temp_2, temp_3;

    x_note_fn_call(33,53);
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

    x_note_fn_call(33,54);
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

Object Chain_of_available_byte_code_bodys = UNBOUND;

Object Byte_code_body_count = UNBOUND;

/* BYTE-CODE-BODY-STRUCTURE-MEMORY-USAGE */
Object byte_code_body_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,55);
    temp = Byte_code_body_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BYTE-CODE-BODY-COUNT */
Object outstanding_byte_code_body_count()
{
    Object def_structure_byte_code_body_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,56);
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
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(33,57);
    inline_note_reclaim_cons(byte_code_body,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = byte_code_body;
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
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_byte_code_bodys;
    SVREF(byte_code_body,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_byte_code_bodys = byte_code_body;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BYTE-CODE-BODY */
Object reclaim_structure_for_byte_code_body(byte_code_body)
    Object byte_code_body;
{
    x_note_fn_call(33,58);
    return reclaim_byte_code_body_1(byte_code_body);
}

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

/* MAKE-PERMANENT-BYTE-CODE-BODY-STRUCTURE-INTERNAL */
Object make_permanent_byte_code_body_structure_internal()
{
    Object def_structure_byte_code_body_variable;
    Object byte_code_body_count_new_value;
    Object defstruct_g2_byte_code_body_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,59);
    def_structure_byte_code_body_variable = Nil;
    byte_code_body_count_new_value = FIXNUM_ADD1(Byte_code_body_count);
    Byte_code_body_count = byte_code_body_count_new_value;
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
    Object def_structure_byte_code_body_variable;

    x_note_fn_call(33,60);
    def_structure_byte_code_body_variable = Chain_of_available_byte_code_bodys;
    if (def_structure_byte_code_body_variable) {
	Chain_of_available_byte_code_bodys = 
		ISVREF(def_structure_byte_code_body_variable,(SI_Long)0L);
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
    x_note_fn_call(33,61);
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

    x_note_fn_call(33,62);
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

    x_note_fn_call(33,63);
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

    x_note_fn_call(33,64);
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

    x_note_fn_call(33,65);
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

    x_note_fn_call(33,66);
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

    x_note_fn_call(33,67);
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

    x_note_fn_call(33,68);
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

Object The_type_description_of_sub_profiling_structure = UNBOUND;

Object Chain_of_available_sub_profiling_structures = UNBOUND;

Object Sub_profiling_structure_count = UNBOUND;

/* SUB-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object sub_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,69);
    temp = Sub_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SUB-PROFILING-STRUCTURE-COUNT */
Object outstanding_sub_profiling_structure_count()
{
    Object def_structure_sub_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,70);
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
    Object old_structure_being_reclaimed, managed_float, svref_new_value;

    x_note_fn_call(33,71);
    inline_note_reclaim_cons(sub_profiling_structure,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = sub_profiling_structure;
    managed_float = ISVREF(sub_profiling_structure,(SI_Long)2L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    SVREF(sub_profiling_structure,FIX((SI_Long)2L)) = Nil;
    managed_float = ISVREF(sub_profiling_structure,(SI_Long)3L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    SVREF(sub_profiling_structure,FIX((SI_Long)3L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_sub_profiling_structures;
    SVREF(sub_profiling_structure,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_sub_profiling_structures = sub_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SUB-PROFILING-STRUCTURE */
Object reclaim_structure_for_sub_profiling_structure(sub_profiling_structure)
    Object sub_profiling_structure;
{
    x_note_fn_call(33,72);
    return reclaim_sub_profiling_structure_1(sub_profiling_structure);
}

static Object Qg2_defstruct_structure_name_sub_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::sub-profiling-structure-g2-struct */

/* MAKE-PERMANENT-SUB-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_sub_profiling_structure_structure_internal()
{
    Object def_structure_sub_profiling_structure_variable;
    Object sub_profiling_structure_count_new_value;
    Object defstruct_g2_sub_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,73);
    def_structure_sub_profiling_structure_variable = Nil;
    sub_profiling_structure_count_new_value = 
	    FIXNUM_ADD1(Sub_profiling_structure_count);
    Sub_profiling_structure_count = sub_profiling_structure_count_new_value;
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

/* MAKE-SUB-PROFILING-STRUCTURE-1 */
Object make_sub_profiling_structure_1()
{
    Object def_structure_sub_profiling_structure_variable;
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float;

    x_note_fn_call(33,74);
    def_structure_sub_profiling_structure_variable = 
	    Chain_of_available_sub_profiling_structures;
    if (def_structure_sub_profiling_structure_variable) {
	Chain_of_available_sub_profiling_structures = 
		ISVREF(def_structure_sub_profiling_structure_variable,
		(SI_Long)0L);
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    SVREF(def_structure_sub_profiling_structure_variable,FIX((SI_Long)3L)) 
	    = new_float;
    return VALUES_1(def_structure_sub_profiling_structure_variable);
}

Object The_type_description_of_basic_profiling_structure = UNBOUND;

Object Chain_of_available_basic_profiling_structures = UNBOUND;

Object Basic_profiling_structure_count = UNBOUND;

/* BASIC-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object basic_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,75);
    temp = Basic_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BASIC-PROFILING-STRUCTURE-COUNT */
Object outstanding_basic_profiling_structure_count()
{
    Object def_structure_basic_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,76);
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
    Object old_structure_being_reclaimed, managed_float, svref_new_value;

    x_note_fn_call(33,77);
    inline_note_reclaim_cons(basic_profiling_structure,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = basic_profiling_structure;
    reclaim_profiling_name(ISVREF(basic_profiling_structure,(SI_Long)1L));
    SVREF(basic_profiling_structure,FIX((SI_Long)1L)) = Nil;
    reclaim_frame_serial_number(ISVREF(basic_profiling_structure,(SI_Long)3L));
    SVREF(basic_profiling_structure,FIX((SI_Long)3L)) = Nil;
    managed_float = ISVREF(basic_profiling_structure,(SI_Long)4L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    SVREF(basic_profiling_structure,FIX((SI_Long)4L)) = Nil;
    reclaim_managed_simple_vector(ISVREF(basic_profiling_structure,
	    (SI_Long)6L));
    SVREF(basic_profiling_structure,FIX((SI_Long)6L)) = Nil;
    reclaim_managed_float_array(ISVREF(basic_profiling_structure,(SI_Long)7L));
    SVREF(basic_profiling_structure,FIX((SI_Long)7L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_basic_profiling_structures;
    SVREF(basic_profiling_structure,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_basic_profiling_structures = basic_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BASIC-PROFILING-STRUCTURE */
Object reclaim_structure_for_basic_profiling_structure(basic_profiling_structure)
    Object basic_profiling_structure;
{
    x_note_fn_call(33,78);
    return reclaim_basic_profiling_structure_internal_1(basic_profiling_structure);
}

static Object Qg2_defstruct_structure_name_basic_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::basic-profiling-structure-g2-struct */

/* MAKE-PERMANENT-BASIC-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_basic_profiling_structure_structure_internal()
{
    Object def_structure_basic_profiling_structure_variable;
    Object basic_profiling_structure_count_new_value;
    Object defstruct_g2_basic_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,79);
    def_structure_basic_profiling_structure_variable = Nil;
    basic_profiling_structure_count_new_value = 
	    FIXNUM_ADD1(Basic_profiling_structure_count);
    Basic_profiling_structure_count = 
	    basic_profiling_structure_count_new_value;
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
    Object def_structure_basic_profiling_structure_variable;
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float;

    x_note_fn_call(33,80);
    def_structure_basic_profiling_structure_variable = 
	    Chain_of_available_basic_profiling_structures;
    if (def_structure_basic_profiling_structure_variable) {
	Chain_of_available_basic_profiling_structures = 
		ISVREF(def_structure_basic_profiling_structure_variable,
		(SI_Long)0L);
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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

Object Current_profile_structure_qm = UNBOUND;

/* RECLAIM-BASIC-PROFILING-STRUCTURE */
Object reclaim_basic_profiling_structure(bps)
    Object bps;
{
    x_note_fn_call(33,81);
    if (EQ(bps,Current_profile_structure_qm))
	Current_profile_structure_qm = Nil;
    reclaim_basic_profiling_structure_internal_1(bps);
    return VALUES_1(Nil);
}

/* RECLAIM-PROFILING-NAME */
Object reclaim_profiling_name(name)
    Object name;
{
    x_note_fn_call(33,82);
    if ( !SYMBOLP(name))
	return reclaim_frame_serial_number(name);
    else
	return VALUES_1(Nil);
}

Object Available_call_hash_hash_vector_43_vectors = UNBOUND;

Object Count_of_call_hash_hash_vector_43_vectors = UNBOUND;

/* CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object call_hash_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(33,83);
    temp = Count_of_call_hash_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-CALL-HASH-HASH-VECTOR-43-VECTORS */
Object out_call_hash_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(33,84);
    temp = FIXNUM_MINUS(Count_of_call_hash_hash_vector_43_vectors,
	    length(Available_call_hash_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-CALL-HASH-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_call_hash_hash_vector_43_vector_internal()
{
    Object count_of_call_hash_hash_vector_43_vectors_new_value, temp;
    XDeclare_area(1);

    x_note_fn_call(33,85);
    count_of_call_hash_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(Count_of_call_hash_hash_vector_43_vectors);
    Count_of_call_hash_hash_vector_43_vectors = 
	    count_of_call_hash_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-CALL-HASH-HASH-VECTOR */
Object make_call_hash_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(33,86);
    if (Available_call_hash_hash_vector_43_vectors) {
	temp = M_CAR(Available_call_hash_hash_vector_43_vectors);
	temp_1 = M_CDR(Available_call_hash_hash_vector_43_vectors);
	inline_note_reclaim_cons(Available_call_hash_hash_vector_43_vectors,
		Qab_gensym);
	cdr_arg = Available_call_hash_hash_vector_43_vectors;
	cdr_new_value = Available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	Available_gensym_conses = Available_call_hash_hash_vector_43_vectors;
	Available_call_hash_hash_vector_43_vectors = temp_1;
    }
    else
	temp = make_permanent_call_hash_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-CALL-HASH-HASH-VECTOR */
Object reclaim_call_hash_hash_vector(call_hash_hash_vector_43_vector)
    Object call_hash_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(33,87);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = call_hash_hash_vector_43_vector;
    cdr_new_value = Available_call_hash_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    Available_call_hash_hash_vector_43_vectors = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MUTATE-CALL-HASH-TREE-FOR-HASH-TREE-ENTRY */
Object mutate_call_hash_tree_for_hash_tree_entry(entry_cons,new_key,new_entry)
    Object entry_cons, new_key, new_entry;
{
    x_note_fn_call(33,88);
    reclaim_basic_profiling_structure(M_CDR(entry_cons));
    M_CAR(entry_cons) = new_key;
    M_CDR(entry_cons) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_call_hash_tree_for_hash_tree_entry = UNBOUND;

/* CLEAR-CALL-HASH-TREE */
Object clear_call_hash_tree(call_hash_tree_for_hash_binary_tree)
    Object call_hash_tree_for_hash_binary_tree;
{
    Object element_qm, temp, gensymed_symbol, old_entry;
    Object result;

    x_note_fn_call(33,89);
    element_qm = Nil;
  next_loop:
    element_qm = CDR(call_hash_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop;
    temp = ISVREF(element_qm,(SI_Long)3L);
    gensymed_symbol = CAAR(temp);
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,call_hash_tree_for_hash_binary_tree,
	    SYMBOLP(gensymed_symbol) ? 
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)) : 
	    frame_hash_function(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    reclaim_basic_profiling_structure(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(call_hash_tree_for_hash_binary_tree);
}

static Object Qcall_hash_tree_for_hash;  /* call-hash-tree-for-hash */

/* MAKE-CALL-HASH */
Object make_call_hash()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(33,90);
    new_vector = make_call_hash_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qcall_hash_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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

    x_note_fn_call(33,91);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(call_hash_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
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

    x_note_fn_call(33,92);
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
    Object call_hash_tree_for_hash_binary_tree, element_qm, gensymed_symbol;
    Object old_entry, cdr_new_value, temp;
    SI_Long index_1;
    Object result;

    x_note_fn_call(33,93);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    call_hash_tree_for_hash_binary_tree = ISVREF(call_hash_hash_table,index_1);
    element_qm = Nil;
  next_loop_1:
    element_qm = M_CDR(call_hash_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop_1;
    gensymed_symbol = M_CAR(M_CAR(ISVREF(element_qm,(SI_Long)3L)));
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,call_hash_tree_for_hash_binary_tree,
	    SYMBOLP(gensymed_symbol) ? 
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)) : 
	    frame_hash_function(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    reclaim_basic_profiling_structure(old_entry);
    goto next_loop_1;
  end_loop_1:
    inline_note_reclaim_cons(call_hash_tree_for_hash_binary_tree,Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(call_hash_tree_for_hash_binary_tree) = cdr_new_value;
    Available_gensym_conses = call_hash_tree_for_hash_binary_tree;
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
    x_note_fn_call(33,94);
    return make_call_hash();
}

Object Available_sub_call_hash_hash_vector_43_vectors = UNBOUND;

Object Count_of_sub_call_hash_hash_vector_43_vectors = UNBOUND;

/* SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object sub_call_hash_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(33,95);
    temp = Count_of_sub_call_hash_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS */
Object out_sub_call_hash_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(33,96);
    temp = FIXNUM_MINUS(Count_of_sub_call_hash_hash_vector_43_vectors,
	    length(Available_sub_call_hash_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_sub_call_hash_hash_vector_43_vector_internal()
{
    Object count_of_sub_call_hash_hash_vector_43_vectors_new_value, temp;
    XDeclare_area(1);

    x_note_fn_call(33,97);
    count_of_sub_call_hash_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(Count_of_sub_call_hash_hash_vector_43_vectors);
    Count_of_sub_call_hash_hash_vector_43_vectors = 
	    count_of_sub_call_hash_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-SUB-CALL-HASH-HASH-VECTOR */
Object make_sub_call_hash_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(33,98);
    if (Available_sub_call_hash_hash_vector_43_vectors) {
	temp = M_CAR(Available_sub_call_hash_hash_vector_43_vectors);
	temp_1 = M_CDR(Available_sub_call_hash_hash_vector_43_vectors);
	inline_note_reclaim_cons(Available_sub_call_hash_hash_vector_43_vectors,
		Qab_gensym);
	cdr_arg = Available_sub_call_hash_hash_vector_43_vectors;
	cdr_new_value = Available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	Available_gensym_conses = 
		Available_sub_call_hash_hash_vector_43_vectors;
	Available_sub_call_hash_hash_vector_43_vectors = temp_1;
    }
    else
	temp = make_permanent_sub_call_hash_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-SUB-CALL-HASH-HASH-VECTOR */
Object reclaim_sub_call_hash_hash_vector(sub_call_hash_hash_vector_43_vector)
    Object sub_call_hash_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(33,99);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = sub_call_hash_hash_vector_43_vector;
    cdr_new_value = Available_sub_call_hash_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    Available_sub_call_hash_hash_vector_43_vectors = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MUTATE-SUB-CALL-HASH-TREE-FOR-HASH-TREE-ENTRY */
Object mutate_sub_call_hash_tree_for_hash_tree_entry(entry_cons,new_key,
	    new_entry)
    Object entry_cons, new_key, new_entry;
{
    x_note_fn_call(33,100);
    reclaim_sub_profiling_structure_1(M_CDR(entry_cons));
    M_CAR(entry_cons) = new_key;
    M_CDR(entry_cons) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_sub_call_hash_tree_for_hash_tree_entry = UNBOUND;

/* CLEAR-SUB-CALL-HASH-TREE */
Object clear_sub_call_hash_tree(sub_call_hash_tree_for_hash_binary_tree)
    Object sub_call_hash_tree_for_hash_binary_tree;
{
    Object element_qm, temp, gensymed_symbol, old_entry;
    Object result;

    x_note_fn_call(33,101);
    element_qm = Nil;
  next_loop:
    element_qm = CDR(sub_call_hash_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop;
    temp = ISVREF(element_qm,(SI_Long)3L);
    gensymed_symbol = CAAR(temp);
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,sub_call_hash_tree_for_hash_binary_tree,
	    SYMBOLP(gensymed_symbol) ? 
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)) : 
	    frame_hash_function(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    reclaim_sub_profiling_structure_1(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(sub_call_hash_tree_for_hash_binary_tree);
}

static Object Qsub_call_hash_tree_for_hash;  /* sub-call-hash-tree-for-hash */

/* MAKE-SUB-CALL-HASH */
Object make_sub_call_hash()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(33,102);
    new_vector = make_sub_call_hash_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qsub_call_hash_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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

    x_note_fn_call(33,103);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(sub_call_hash_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
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

    x_note_fn_call(33,104);
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
    Object sub_call_hash_tree_for_hash_binary_tree, element_qm;
    Object gensymed_symbol, old_entry, cdr_new_value, temp;
    SI_Long index_1;
    Object result;

    x_note_fn_call(33,105);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    sub_call_hash_tree_for_hash_binary_tree = 
	    ISVREF(sub_call_hash_hash_table,index_1);
    element_qm = Nil;
  next_loop_1:
    element_qm = M_CDR(sub_call_hash_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop_1;
    gensymed_symbol = M_CAR(M_CAR(ISVREF(element_qm,(SI_Long)3L)));
    result = delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,sub_call_hash_tree_for_hash_binary_tree,
	    SYMBOLP(gensymed_symbol) ? 
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)) : 
	    frame_hash_function(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    reclaim_sub_profiling_structure_1(old_entry);
    goto next_loop_1;
  end_loop_1:
    inline_note_reclaim_cons(sub_call_hash_tree_for_hash_binary_tree,
	    Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(sub_call_hash_tree_for_hash_binary_tree) = cdr_new_value;
    Available_gensym_conses = sub_call_hash_tree_for_hash_binary_tree;
    ISVREF(sub_call_hash_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_sub_call_hash_hash_vector(sub_call_hash_hash_table);
    return VALUES_1(temp);
}

Object The_type_description_of_global_profiling_structure = UNBOUND;

Object Chain_of_available_global_profiling_structures = UNBOUND;

Object Global_profiling_structure_count = UNBOUND;

/* GLOBAL-PROFILING-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object global_profiling_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(33,106);
    temp = Global_profiling_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GLOBAL-PROFILING-STRUCTURE-COUNT */
Object outstanding_global_profiling_structure_count()
{
    Object def_structure_global_profiling_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,107);
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
    Object old_structure_being_reclaimed, managed_float, svref_new_value;

    x_note_fn_call(33,108);
    inline_note_reclaim_cons(global_profiling_structure,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = global_profiling_structure;
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
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_global_profiling_structures;
    SVREF(global_profiling_structure,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_global_profiling_structures = 
	    global_profiling_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GLOBAL-PROFILING-STRUCTURE */
Object reclaim_structure_for_global_profiling_structure(global_profiling_structure)
    Object global_profiling_structure;
{
    x_note_fn_call(33,109);
    return reclaim_global_profiling_structure_1(global_profiling_structure);
}

static Object Qg2_defstruct_structure_name_global_profiling_structure_g2_struct;  /* g2-defstruct-structure-name::global-profiling-structure-g2-struct */

/* MAKE-PERMANENT-GLOBAL-PROFILING-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_global_profiling_structure_structure_internal()
{
    Object def_structure_global_profiling_structure_variable;
    Object global_profiling_structure_count_new_value;
    Object defstruct_g2_global_profiling_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,110);
    def_structure_global_profiling_structure_variable = Nil;
    global_profiling_structure_count_new_value = 
	    FIXNUM_ADD1(Global_profiling_structure_count);
    Global_profiling_structure_count = 
	    global_profiling_structure_count_new_value;
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
    Object def_structure_global_profiling_structure_variable, temp;
    Object amf_available_array_cons_qm, amf_array, svref_new_value, amf_result;
    Object incff_1_arg, new_float;

    x_note_fn_call(33,111);
    def_structure_global_profiling_structure_variable = 
	    Chain_of_available_global_profiling_structures;
    if (def_structure_global_profiling_structure_variable) {
	Chain_of_available_global_profiling_structures = 
		ISVREF(def_structure_global_profiling_structure_variable,
		(SI_Long)0L);
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
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
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	temp = Available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	Available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	Created_simple_float_array_pool_arrays = temp;
	incff_1_arg = bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,incff_1_arg);
	Simple_float_array_pool_memory_usage = temp;
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    SVREF(def_structure_global_profiling_structure_variable,
	    FIX((SI_Long)8L)) = new_float;
    return VALUES_1(def_structure_global_profiling_structure_variable);
}

Object Profiling_enabled_qm = UNBOUND;

/* CHECK-SHAPE-OF-WINDOW-WITHOUT-LOOKAHEAD-FOR-G2 */
Object check_shape_of_window_without_lookahead_for_g2(gensym_window,
	    native_window)
    Object gensym_window, native_window;
{
    Object work_was_done_qm, gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;

    x_note_fn_call(33,112);
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

    x_note_fn_call(33,113);
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

    x_note_fn_call(33,114);
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
    Object new_cons, gensymed_symbol, temp;
    Object reclaim_structure_for_byte_code_body_1;
    Object reclaim_structure_for_sub_profiling_structure_1;
    Object reclaim_structure_for_basic_profiling_structure_1;
    Object reclaim_structure_for_global_profiling_structure_1;
    Object Qglobal_profiling_structure, Qreclaim_structure;
    Object Qoutstanding_global_profiling_structure_count;
    Object Qglobal_profiling_structure_structure_memory_usage, Qutilities2;
    Object Qglobal_profiling_structure_count, AB_package;
    Object Qchain_of_available_global_profiling_structures, string_constant_15;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_14, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmutate_sub_call_hash_tree_for_hash_tree_entry;
    Object Qout_sub_call_hash_hash_vector_43_vectors;
    Object Qsub_call_hash_hash_vector_43_vector_memory_usage;
    Object string_constant_13, Qcount_of_sub_call_hash_hash_vector_43_vectors;
    Object Qavailable_sub_call_hash_hash_vector_43_vectors;
    Object Qmutate_call_hash_tree_for_hash_tree_entry;
    Object Qout_call_hash_hash_vector_43_vectors;
    Object Qcall_hash_hash_vector_43_vector_memory_usage, string_constant_12;
    Object Qcount_of_call_hash_hash_vector_43_vectors;
    Object Qavailable_call_hash_hash_vector_43_vectors;
    Object Qbasic_profiling_structure;
    Object Qoutstanding_basic_profiling_structure_count;
    Object Qbasic_profiling_structure_structure_memory_usage;
    Object Qbasic_profiling_structure_count;
    Object Qchain_of_available_basic_profiling_structures, string_constant_11;
    Object string_constant_10, Qsub_profiling_structure;
    Object Qoutstanding_sub_profiling_structure_count;
    Object Qsub_profiling_structure_structure_memory_usage;
    Object Qsub_profiling_structure_count;
    Object Qchain_of_available_sub_profiling_structures, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, Qspecial_annotation_lookup_structure_marker;
    Object Qbyte_code_body, Qoutstanding_byte_code_body_count;
    Object Qbyte_code_body_structure_memory_usage, Qbyte_code_body_count;
    Object Qchain_of_available_byte_code_bodys, string_constant_4;
    Object string_constant_3, Qframe_serial_number_0, string_constant_2;
    Object list_constant_2, Qutilities4, Qcurrent_frame_serial_number;
    Object Kfuncall, Qfunction_keeps_procedure_environment_valid_qm;
    Object Qkb_specific_variable_plist, Qreclaim_gensym_list_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, string_constant_1;
    Object Qthere_is_a_current_kb_qm, Qreclaim_kb_property_list_function;
    Object list_constant_1, Qkb_state_changes, Qinitialize_kb_state_changes;
    Object list_constant, Qcurrent_kb_specific_property_list_property_name;
    Object Qkb_0;

    x_note_fn_call(33,115);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qcurrent_kb_specific_property_list_property_name = 
	    STATIC_SYMBOL("*CURRENT-KB-SPECIFIC-PROPERTY-LIST-PROPERTY-NAME*",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_kb_specific_property_list_property_name,
	    Current_kb_specific_property_list_property_name);
    Qutilities4 = STATIC_SYMBOL("UTILITIES4",AB_package);
    Qkb_0 = STATIC_SYMBOL("KB-0",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qquote,Qkb_0);
    record_system_variable(Qcurrent_kb_specific_property_list_property_name,
	    Qutilities4,list_constant,Qnil,Qt,Qnil,Qnil);
    if (Locations_of_kb_specific_property_lists == UNBOUND)
	Locations_of_kb_specific_property_lists = Nil;
    Qkb_state_changes = STATIC_SYMBOL("KB-STATE-CHANGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_state_changes,Kb_state_changes);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_kb_state_changes = 
	    STATIC_SYMBOL("INITIALIZE-KB-STATE-CHANGES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_kb_state_changes,
	    STATIC_FUNCTION(initialize_kb_state_changes,NIL,FALSE,0,0));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_kb_state_changes);
    Qreclaim_kb_property_list_function = 
	    STATIC_SYMBOL("RECLAIM-KB-PROPERTY-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_kb_property_list_function,
	    STATIC_FUNCTION(reclaim_kb_property_list_function,NIL,FALSE,1,1));
    record_system_variable(Qkb_state_changes,Qutilities4,list_constant_1,
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
    string_constant_1 = STATIC_STRING("NO-SPECIFIC-PROPERTY-VALUE");
    if (No_specific_property_value == UNBOUND)
	No_specific_property_value = make_symbol(string_constant_1);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    if (Symbol_properties_table == UNBOUND) {
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = Qsymbol_properties_hash_table;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	Symbol_properties_table = gensymed_symbol;
    }
    if (Last_assigned_global_kb_number == UNBOUND)
	Last_assigned_global_kb_number = FIX((SI_Long)0L);
    string_constant = STATIC_STRING("KB-~D");
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
    list_constant_2 = STATIC_LIST((SI_Long)2L,Kfuncall,Qframe_serial_number_0);
    record_system_variable(Qcurrent_frame_serial_number,Qutilities4,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Max_fixnum_frame_serial_number = Most_positive_fixnum;
    string_constant_2 = STATIC_STRING("reclaimed-frame-serial-number-marker");
    if (Reclaimed_frame_serial_number_marker == UNBOUND)
	Reclaimed_frame_serial_number_marker = make_symbol(string_constant_2);
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
    string_constant_3 = 
	    STATIC_STRING("43Dy8m83fay1n83fay8n8k1l8n0000001l1n8y83-3*y1p83rGy83rCy83rDy83rEy83rFykuk0k0");
    temp = The_type_description_of_byte_code_body;
    The_type_description_of_byte_code_body = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_3));
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
    string_constant_4 = STATIC_STRING("1q83fay8s83-LAy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_byte_code_body_count);
    push_optimized_constant(Qbyte_code_body_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
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
    string_constant_5 = 
	    STATIC_STRING("spEcIal annOtatiOn LookuP strUctUrE maRkeR");
    string_constant_6 = STATIC_STRING("KEYWORD");
    SET_SYMBOL_VALUE(Qspecial_annotation_lookup_structure_marker,
	    intern(string_constant_5,find_package(string_constant_6)));
    string_constant_7 = STATIC_STRING("TREE-TRAVERSAL-MARKER");
    Tree_traversal_marker = make_symbol(string_constant_7);
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
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83nYy1n83nYy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_sub_profiling_structure;
    The_type_description_of_sub_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
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
    string_constant_9 = STATIC_STRING("1q83nYy8s83-pny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sub_profiling_structure_count);
    push_optimized_constant(Qsub_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
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
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83fPy1n83fPy8n8k1l8n0000001m1m83My83-A7y1m8y83-2syksk0k0");
    temp = The_type_description_of_basic_profiling_structure;
    The_type_description_of_basic_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
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
    string_constant_11 = STATIC_STRING("1q83fPy8s83-Kcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_basic_profiling_structure_count);
    push_optimized_constant(Qbasic_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
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
    Qout_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-CALL-HASH-HASH-VECTOR-43-VECTORS",AB_package);
    Qcall_hash_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_12 = STATIC_STRING("1q83-LMy83*By83-Oiy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_call_hash_hash_vector_43_vectors);
    push_optimized_constant(Qcall_hash_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    SET_SYMBOL_FUNCTION(Qcall_hash_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(call_hash_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_call_hash_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_call_hash_hash_vector_43_vectors,NIL,FALSE,
	    0,0));
    Qmutate_call_hash_tree_for_hash_tree_entry = 
	    STATIC_SYMBOL("MUTATE-CALL-HASH-TREE-FOR-HASH-TREE-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_call_hash_tree_for_hash_tree_entry,
	    STATIC_FUNCTION(mutate_call_hash_tree_for_hash_tree_entry,NIL,
	    FALSE,3,3));
    Fp_mutate_call_hash_tree_for_hash_tree_entry = 
	    SYMBOL_FUNCTION(Qmutate_call_hash_tree_for_hash_tree_entry);
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
    Qout_sub_call_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-SUB-CALL-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qsub_call_hash_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("SUB-CALL-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83-pmy83*By83-P5y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_sub_call_hash_hash_vector_43_vectors);
    push_optimized_constant(Qsub_call_hash_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    SET_SYMBOL_FUNCTION(Qsub_call_hash_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(sub_call_hash_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_sub_call_hash_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_sub_call_hash_hash_vector_43_vectors,NIL,
	    FALSE,0,0));
    Qmutate_sub_call_hash_tree_for_hash_tree_entry = 
	    STATIC_SYMBOL("MUTATE-SUB-CALL-HASH-TREE-FOR-HASH-TREE-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_sub_call_hash_tree_for_hash_tree_entry,
	    STATIC_FUNCTION(mutate_sub_call_hash_tree_for_hash_tree_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_sub_call_hash_tree_for_hash_tree_entry = 
	    SYMBOL_FUNCTION(Qmutate_sub_call_hash_tree_for_hash_tree_entry);
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
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83i6y1n83i6y8n8k1l8n0000000ktk0k0");
    temp = The_type_description_of_global_profiling_structure;
    The_type_description_of_global_profiling_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
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
    string_constant_15 = STATIC_STRING("1q83i6y8s83-W7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_global_profiling_structure_count);
    push_optimized_constant(Qglobal_profiling_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
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
