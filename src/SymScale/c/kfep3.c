/* kfep3.c
 * Input file:  kfep3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kfep3.h"


Object Jis_kana_to_ascii = UNBOUND;

Object Jis_offsets_for_y_prefix_kana_characters = UNBOUND;

Object Jis_offsets_for_y_kana_characters = UNBOUND;

/* TFLUSH-STRIPPED-KANA-BUFFER-IF-NECESSARY */
Object tflush_stripped_kana_buffer_if_necessary(stripped_kana_buffer,
	    number_of_bytes_in_stripped_kana_buffer)
    Object stripped_kana_buffer, number_of_bytes_in_stripped_kana_buffer;
{
    Object stripped_kana_buffer_index, translation_qm;
    Object stripped_kana_buffer_index_increment_qm, incff_1_arg;
    Object result;

    x_note_fn_call(122,0);
    stripped_kana_buffer_index = FIX((SI_Long)0L);
  next_loop:
    if ( !FIXNUM_LT(stripped_kana_buffer_index,
	    number_of_bytes_in_stripped_kana_buffer))
	goto end_loop;
    result = map_longest_possible_substring_using_jis_map(stripped_kana_buffer,
	    Kana_to_ascii_map,stripped_kana_buffer_index,
	    number_of_bytes_in_stripped_kana_buffer,
	    Maximum_length_of_kana_string);
    MVS_2(result,translation_qm,stripped_kana_buffer_index_increment_qm);
    if (STRINGP(translation_qm)) {
	twrite_general_string(translation_qm);
	incff_1_arg = stripped_kana_buffer_index_increment_qm;
	stripped_kana_buffer_index = FIXNUM_ADD(stripped_kana_buffer_index,
		incff_1_arg);
    }
    else
	stripped_kana_buffer_index = FIXNUM_ADD1(stripped_kana_buffer_index);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* CONVERT-TO-ASCII-ROMAN-IF-POSSIBLE */
Object convert_to_ascii_roman_if_possible(text_string_to_convert,
	    case_normalization_qm)
    Object text_string_to_convert, case_normalization_qm;
{
    Object success_qm, stripped_kana_buffer, stripped_kana_buffer_index;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_length, string_index, character_1, jis_code_qm, temp;
    Object unicode, cjk_code, cjk_code_mapping_vector, l, temp_2;
    Object gensymed_symbol_1, code, simple_or_wide_character, thing;
    Object schar_arg_2, schar_new_value, new_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, temp_1;
    SI_Long gensymed_symbol;
    Declare_special(5);

    x_note_fn_call(122,1);
    success_qm = Nil;
    stripped_kana_buffer = 
	    obtain_simple_gensym_string(text_string_length(text_string_to_convert));
    stripped_kana_buffer_index = FIX((SI_Long)0L);
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
	      string_length = text_string_length(text_string_to_convert);
	      string_index = FIX((SI_Long)0L);
	      character_1 = Nil;
	      jis_code_qm = Nil;
	    next_loop:
	      if (FIXNUM_GE(string_index,string_length)) {
		  success_qm = T;
		  goto end_loop;
	      }
	      temp = FIX(UBYTE_16_ISAREF_1(text_string_to_convert,
		      IFIX(string_index)));
	      string_index = FIXNUM_ADD1(string_index);
	      character_1 = temp;
	      unicode = character_1;
	      cjk_code = unicode;
	      cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
	      temp_1 = IFIX(cjk_code) % (SI_Long)307L;
	      l = ISVREF(cjk_code_mapping_vector,temp_1);
	    next_loop_1:
	      if ( !TRUEP(l))
		  goto end_loop_1;
	      if (FIXNUM_EQ(CAR(l),cjk_code)) {
		  jis_code_qm = CADR(l);
		  goto end_1;
	      }
	      l = CDDR(l);
	      goto next_loop_1;
	    end_loop_1:
	      jis_code_qm = Qnil;
	    end_1:;
	      if (jis_code_qm) {
		  if ((SI_Long)9249L <= IFIX(jis_code_qm) && 
			  IFIX(jis_code_qm) <= (SI_Long)9331L || 
			  (SI_Long)9505L <= IFIX(jis_code_qm) && 
			  IFIX(jis_code_qm) <= (SI_Long)9590L) {
		      gensymed_symbol = (SI_Long)255L & IFIX(jis_code_qm);
		      temp_2 = CODE_CHAR(FIX(gensymed_symbol));
		      SET_CHAR(stripped_kana_buffer,
			      stripped_kana_buffer_index,temp_2);
		      stripped_kana_buffer_index = 
			      FIXNUM_ADD1(stripped_kana_buffer_index);
		  }
		  else {
		      if (IFIX(stripped_kana_buffer_index) > (SI_Long)0L) {
			  tflush_stripped_kana_buffer_if_necessary(stripped_kana_buffer,
				  stripped_kana_buffer_index);
			  stripped_kana_buffer_index = FIX((SI_Long)0L);
		      }
		      if ((SI_Long)9025L <= IFIX(jis_code_qm) && 
			      IFIX(jis_code_qm) <= (SI_Long)9050L)
			  twrite_character(FIX((SI_Long)65L + 
				  (IFIX(jis_code_qm) - (SI_Long)9025L)));
		      else if ((SI_Long)9057L <= IFIX(jis_code_qm) && 
			      IFIX(jis_code_qm) <= (SI_Long)9082L)
			  twrite_character(FIX((SI_Long)97L + 
				  (IFIX(jis_code_qm) - (SI_Long)9057L)));
		      else if ((SI_Long)9008L <= IFIX(jis_code_qm) && 
			      IFIX(jis_code_qm) <= (SI_Long)9017L)
			  twrite_character(FIX((SI_Long)48L + 
				  (IFIX(jis_code_qm) - (SI_Long)9008L)));
		      else
			  goto end_loop;
		  }
	      }
	      else {
		  gensymed_symbol_1 = character_1;
		  if ((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			  IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			  (SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			  IFIX(gensymed_symbol_1) <= (SI_Long)90L) {
		      if (IFIX(stripped_kana_buffer_index) > (SI_Long)0L) {
			  tflush_stripped_kana_buffer_if_necessary(stripped_kana_buffer,
				  stripped_kana_buffer_index);
			  stripped_kana_buffer_index = FIX((SI_Long)0L);
		      }
		      if (lower_case_pw(character_1)) {
			  if (EQ(case_normalization_qm,Qchar_upcase)) {
			      code = character_1;
			      if (IFIX(code) < (SI_Long)127L)
				  simple_or_wide_character = (SI_Long)97L 
					  <= IFIX(code) && IFIX(code) <= 
					  (SI_Long)122L ? FIX(IFIX(code) + 
					  (SI_Long)-32L) : code;
			      else {
				  simple_or_wide_character = 
					  unicode_uppercase_if_lowercase(code);
				  if (simple_or_wide_character);
				  else
				      simple_or_wide_character = code;
			      }
			  }
			  else
			      simple_or_wide_character = character_1;
		      }
		      else if (EQ(case_normalization_qm,Qchar_downcase)) {
			  code = character_1;
			  if (IFIX(code) < (SI_Long)127L)
			      simple_or_wide_character = (SI_Long)65L <= 
				      IFIX(code) && IFIX(code) <= 
				      (SI_Long)90L ? FIX(IFIX(code) + 
				      (SI_Long)32L) : code;
			  else {
			      simple_or_wide_character = 
				      unicode_lowercase_if_uppercase(code);
			      if (simple_or_wide_character);
			      else
				  simple_or_wide_character = code;
			  }
		      }
		      else
			  simple_or_wide_character = character_1;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = simple_or_wide_character;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_2 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = simple_or_wide_character;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
			  temp_2 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_2;
		      }
		  }
		  else if (wide_character_member(character_1,
			  Allowable_non_alpha_characters_in_kfep_conversions)) 
			      {
		      if (IFIX(stripped_kana_buffer_index) > (SI_Long)0L) {
			  tflush_stripped_kana_buffer_if_necessary(stripped_kana_buffer,
				  stripped_kana_buffer_index);
			  stripped_kana_buffer_index = FIX((SI_Long)0L);
		      }
		      twrite_character(character_1);
		  }
		  else
		      goto end_loop;
	      }
	      goto next_loop;
	    end_loop:;
	      new_text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_gensym_string(stripped_kana_buffer);
    if (success_qm)
	return VALUES_1(new_text_string);
    else {
	reclaim_text_string(new_text_string);
	return VALUES_1(Nil);
    }
}

static Object list_constant;       /* # */

/* CONVERT-TO-HIRAGANA-IN-JIS-STRING-IF-POSSIBLE */
Object convert_to_hiragana_in_jis_string_if_possible(text_string)
    Object text_string;
{
    Object ascii_roman_text_string_qm, ascii_roman_string_length;
    Object last_character_is_m_qm, jis_string_for_hiragana;
    Object ascii_roman_lisp_string, result_1, actual_number_of_jis_bytes;
    Object simple_character, char_new_value, string_length, string_index;
    Object jis_string_index, character_1, jis_code_qm, temp_1, cjk_code;
    Object cjk_code_mapping_vector, l;
    SI_Long number_of_jis_characters_available, number_of_jis_bytes_available;
    SI_Long temp, jis_char_new_value, base_index, gensymed_symbol, temp_2;

    x_note_fn_call(122,2);
    ascii_roman_text_string_qm = 
	    convert_to_ascii_roman_if_possible(text_string,Nil);
    if (ascii_roman_text_string_qm) {
	ascii_roman_string_length = 
		text_string_length(ascii_roman_text_string_qm);
	last_character_is_m_qm = Nil;
	number_of_jis_characters_available = 
		IFIX(ascii_roman_string_length) << (SI_Long)1L;
	number_of_jis_bytes_available = number_of_jis_characters_available 
		<< (SI_Long)1L;
	jis_string_for_hiragana = 
		obtain_simple_gensym_string(FIX(number_of_jis_characters_available 
		<< (SI_Long)1L));
	ascii_roman_lisp_string = Nil;
	last_character_is_m_qm = 
		wide_character_member(FIX(UBYTE_16_ISAREF_1(ascii_roman_text_string_qm,
		IFIX(FIXNUM_SUB1(ascii_roman_string_length)))),
		list_constant) ? 
		FIX(UBYTE_16_ISAREF_1(ascii_roman_text_string_qm,
		IFIX(FIXNUM_SUB1(ascii_roman_string_length)))) : Nil;
	if (last_character_is_m_qm)
	    ascii_roman_string_length = FIXNUM_SUB1(ascii_roman_string_length);
	ascii_roman_lisp_string = 
		copy_text_string_as_managed_lisp_string(ascii_roman_text_string_qm,
		FIX((SI_Long)0L),ascii_roman_string_length);
	reclaim_text_string(ascii_roman_text_string_qm);
	result_1 = roman_kana_g2(ascii_roman_lisp_string,
		ascii_roman_string_length,jis_string_for_hiragana,
		FIX(number_of_jis_bytes_available),FIX((SI_Long)0L));
	actual_number_of_jis_bytes = IFIX(result_1) == (SI_Long)-1L ? 
		FIX((SI_Long)0L) : roman_kana_g2(ascii_roman_lisp_string,
		ascii_roman_string_length,jis_string_for_hiragana,
		FIX(number_of_jis_bytes_available),FIX((SI_Long)1L));
	if (last_character_is_m_qm) {
	    temp = IFIX(actual_number_of_jis_bytes) >>  -  - (SI_Long)1L;
	    simple_character = CODE_CHAR(last_character_is_m_qm);
	    jis_char_new_value = IFIX(CHAR_INT(simple_character)) + 
		    (SI_Long)8960L;
	    base_index = temp << (SI_Long)1L;
	    char_new_value = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
		    (SI_Long)8L));
	    SET_ICHAR(jis_string_for_hiragana,base_index,
		    ICHAR_CODE(char_new_value));
	    temp = base_index + (SI_Long)1L;
	    gensymed_symbol = jis_char_new_value & (SI_Long)255L;
	    char_new_value = CODE_CHAR(FIX(gensymed_symbol));
	    SET_ICHAR(jis_string_for_hiragana,temp,ICHAR_CODE(char_new_value));
	    actual_number_of_jis_bytes = 
		    FIX(IFIX(actual_number_of_jis_bytes) + (SI_Long)2L);
	}
	reclaim_gensym_string(ascii_roman_lisp_string);
	if (IFIX(actual_number_of_jis_bytes) >= (SI_Long)0L)
	    return VALUES_2(jis_string_for_hiragana,
		    actual_number_of_jis_bytes);
	else {
	    reclaim_gensym_string(jis_string_for_hiragana);
	    return VALUES_1(Nil);
	}
    }
    else {
	string_length = text_string_length(text_string);
	string_index = FIX((SI_Long)0L);
	jis_string_for_hiragana = 
		obtain_simple_gensym_string(FIX(IFIX(string_length) >>  -  
		- (SI_Long)1L << (SI_Long)1L));
	jis_string_index = FIX((SI_Long)0L);
	character_1 = Nil;
	jis_code_qm = Nil;
      next_loop:
	if (FIXNUM_GE(string_index,string_length))
	    return VALUES_2(jis_string_for_hiragana,
		    FIX(IFIX(jis_string_index) << (SI_Long)1L));
	temp_1 = FIX(UBYTE_16_ISAREF_1(text_string,IFIX(string_index)));
	string_index = FIXNUM_ADD1(string_index);
	character_1 = temp_1;
	cjk_code = character_1;
	cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
	temp_2 = IFIX(cjk_code) % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp_2);
      next_loop_1:
	if ( !TRUEP(l))
	    goto end_loop;
	if (FIXNUM_EQ(CAR(l),cjk_code)) {
	    jis_code_qm = CADR(l);
	    goto end_1;
	}
	l = CDDR(l);
	goto next_loop_1;
      end_loop:
	jis_code_qm = Qnil;
      end_1:;
	if (jis_code_qm && (SI_Long)9249L <= IFIX(jis_code_qm) && 
		IFIX(jis_code_qm) <= (SI_Long)9331L) {
	    base_index = IFIX(jis_string_index) << (SI_Long)1L;
	    char_new_value = CODE_CHAR(FIX(IFIX(jis_code_qm) >>  -  - 
		    (SI_Long)8L));
	    SET_ICHAR(jis_string_for_hiragana,base_index,
		    ICHAR_CODE(char_new_value));
	    temp = base_index + (SI_Long)1L;
	    gensymed_symbol = IFIX(jis_code_qm) & (SI_Long)255L;
	    char_new_value = CODE_CHAR(FIX(gensymed_symbol));
	    SET_ICHAR(jis_string_for_hiragana,temp,ICHAR_CODE(char_new_value));
	    jis_string_index = FIXNUM_ADD1(jis_string_index);
	}
	else
	    goto end_loop_1;
	goto next_loop;
      end_loop_1:
	reclaim_gensym_string(jis_string_for_hiragana);
	return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
}

/* CONVERT-TO-HIRAGANA-IF-POSSIBLE */
Object convert_to_hiragana_if_possible(string_1)
    Object string_1;
{
    Object jis_string_for_hiragana_qm, actual_number_of_jis_bytes_qm, temp;
    Object result;

    x_note_fn_call(122,3);
    result = convert_to_hiragana_in_jis_string_if_possible(string_1);
    MVS_2(result,jis_string_for_hiragana_qm,actual_number_of_jis_bytes_qm);
    if (jis_string_for_hiragana_qm) {
	temp = 
		convert_jis_string_to_text_string(jis_string_for_hiragana_qm,
		FIX(IFIX(actual_number_of_jis_bytes_qm) >>  -  - (SI_Long)1L));
	reclaim_gensym_string(jis_string_for_hiragana_qm);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-TO-KATAKANA-IF-POSSIBLE */
Object convert_to_katakana_if_possible(string_1)
    Object string_1;
{
    Object ascii_roman_text_string_qm, ascii_roman_string_length;
    Object jis_string_for_katakana, last_character_is_m_qm;
    Object ascii_roman_lisp_string, result_1, actual_number_of_jis_bytes;
    Object simple_character, char_new_value, temp_1;
    SI_Long number_of_jis_characters_available, number_of_jis_bytes_available;
    SI_Long temp, jis_char_new_value, base_index, gensymed_symbol;

    x_note_fn_call(122,4);
    ascii_roman_text_string_qm = 
	    convert_to_ascii_roman_if_possible(string_1,Nil);
    if (ascii_roman_text_string_qm) {
	ascii_roman_string_length = 
		text_string_length(ascii_roman_text_string_qm);
	number_of_jis_characters_available = 
		IFIX(ascii_roman_string_length) << (SI_Long)1L;
	number_of_jis_bytes_available = number_of_jis_characters_available 
		<< (SI_Long)1L;
	jis_string_for_katakana = 
		obtain_simple_gensym_string(FIX(number_of_jis_characters_available 
		<< (SI_Long)1L));
	last_character_is_m_qm = Nil;
	ascii_roman_lisp_string = Nil;
	last_character_is_m_qm = 
		wide_character_member(FIX(UBYTE_16_ISAREF_1(ascii_roman_text_string_qm,
		IFIX(FIXNUM_SUB1(ascii_roman_string_length)))),
		list_constant) ? 
		FIX(UBYTE_16_ISAREF_1(ascii_roman_text_string_qm,
		IFIX(FIXNUM_SUB1(ascii_roman_string_length)))) : Nil;
	if (last_character_is_m_qm)
	    ascii_roman_string_length = FIXNUM_SUB1(ascii_roman_string_length);
	ascii_roman_lisp_string = 
		copy_text_string_as_managed_lisp_string(ascii_roman_text_string_qm,
		FIX((SI_Long)0L),ascii_roman_string_length);
	reclaim_text_string(ascii_roman_text_string_qm);
	result_1 = roman_kata_g2(ascii_roman_lisp_string,
		ascii_roman_string_length,jis_string_for_katakana,
		FIX(number_of_jis_bytes_available),FIX((SI_Long)0L));
	actual_number_of_jis_bytes = IFIX(result_1) == (SI_Long)-1L ? 
		FIX((SI_Long)0L) : roman_kata_g2(ascii_roman_lisp_string,
		ascii_roman_string_length,jis_string_for_katakana,
		FIX(number_of_jis_bytes_available),FIX((SI_Long)1L));
	if (last_character_is_m_qm) {
	    temp = IFIX(actual_number_of_jis_bytes) >>  -  - (SI_Long)1L;
	    simple_character = CODE_CHAR(last_character_is_m_qm);
	    jis_char_new_value = IFIX(CHAR_INT(simple_character)) + 
		    (SI_Long)8960L;
	    base_index = temp << (SI_Long)1L;
	    char_new_value = CODE_CHAR(FIX(jis_char_new_value >>  -  - 
		    (SI_Long)8L));
	    SET_ICHAR(jis_string_for_katakana,base_index,
		    ICHAR_CODE(char_new_value));
	    temp = base_index + (SI_Long)1L;
	    gensymed_symbol = jis_char_new_value & (SI_Long)255L;
	    char_new_value = CODE_CHAR(FIX(gensymed_symbol));
	    SET_ICHAR(jis_string_for_katakana,temp,ICHAR_CODE(char_new_value));
	    actual_number_of_jis_bytes = 
		    FIX(IFIX(actual_number_of_jis_bytes) + (SI_Long)2L);
	}
	temp_1 = IFIX(actual_number_of_jis_bytes) >= (SI_Long)0L ? 
		convert_jis_string_to_text_string(jis_string_for_katakana,
		FIX(IFIX(actual_number_of_jis_bytes) >>  -  - 
		(SI_Long)1L)) : Nil;
	reclaim_gensym_string(ascii_roman_lisp_string);
	reclaim_gensym_string(jis_string_for_katakana);
	return VALUES_1(temp_1);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-JIS-STRING-TO-TEXT-STRING */
Object convert_jis_string_to_text_string(jis_string,
	    actual_number_of_jis_characters)
    Object jis_string, actual_number_of_jis_characters;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_is_simple_qm, kanji_code, thing, contiguous_code_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_, base_index;
    Declare_special(5);
    Object result;

    x_note_fn_call(122,5);
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
	      string_is_simple_qm = Nil;
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(actual_number_of_jis_characters);
	      kanji_code = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      if (string_is_simple_qm) {
		  base_index = i << (SI_Long)1L;
		  kanji_code = FIX((IFIX(CHAR_INT(CHR(ISCHAR(jis_string,
			  base_index)))) << (SI_Long)8L) + 
			  IFIX(CHAR_INT(CHR(ISCHAR(jis_string,base_index + 
			  (SI_Long)1L)))));
	      }
	      else {
		  base_index = i << (SI_Long)1L;
		  kanji_code = FIX((IFIX(CHAR_INT(CHR(ICHAR(jis_string,
			  base_index)))) << (SI_Long)8L) + 
			  IFIX(CHAR_INT(CHR(ICHAR(jis_string,base_index + 
			  (SI_Long)1L)))));
	      }
	      if ((SI_Long)9025L <= IFIX(kanji_code) && IFIX(kanji_code) 
		      <= (SI_Long)9050L)
		  twrite_character(FIX((SI_Long)65L + (IFIX(kanji_code) - 
			  (SI_Long)9025L)));
	      else if ((SI_Long)9057L <= IFIX(kanji_code) && 
		      IFIX(kanji_code) <= (SI_Long)9082L)
		  twrite_character(FIX((SI_Long)97L + (IFIX(kanji_code) - 
			  (SI_Long)9057L)));
	      else if ((SI_Long)9008L <= IFIX(kanji_code) && 
		      IFIX(kanji_code) <= (SI_Long)9017L)
		  twrite_character(FIX((SI_Long)48L + (IFIX(kanji_code) - 
			  (SI_Long)9008L)));
	      else if (IFIX(kanji_code) == (SI_Long)8556L)
		  twrite_character(FIX((SI_Long)39L));
	      else if ( 
			  !TRUEP(legal_gensym_jis_character_code_p(kanji_code))) {
		  thing = kanji_code;
		  twrite_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
			  thing);
	      }
	      else {
		  contiguous_code_qm = 
			  gensym_jis_code_to_contiguous(kanji_code);
		  thing = contiguous_code_qm ? 
			  FIX(UBYTE_16_ISAREF_1(Jis_x_0208_to_unicode_map,
			  IFIX(contiguous_code_qm))) : Nil;
		  twrite_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
			  thing);
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* NUMBER-OF-CHARACTERS-UNTRANSLATED */
Object number_of_characters_untranslated(translated_jis_string,
	    original_jis_string)
    Object translated_jis_string, original_jis_string;
{
    Object original_jis_string_is_simple_qm;
    Object translated_jis_string_is_simple_qm, ab_loop_iter_flag_, temp;
    Object temp_1;
    SI_Long largest_index_of_translated_jis_string;
    SI_Long largest_index_of_original_jis_string, original_jis_string_index;
    SI_Long translated_jis_string_index, ab_loopvar_, base_index;

    x_note_fn_call(122,6);
    largest_index_of_translated_jis_string = 
	    (IFIX(length(translated_jis_string)) >>  -  - (SI_Long)1L) - 
	    (SI_Long)1L;
    largest_index_of_original_jis_string = 
	    (IFIX(length(original_jis_string)) >>  -  - (SI_Long)1L) - 
	    (SI_Long)1L;
    original_jis_string_is_simple_qm = Nil;
    translated_jis_string_is_simple_qm = Nil;
    original_jis_string_index = largest_index_of_original_jis_string;
    translated_jis_string_index = largest_index_of_translated_jis_string;
    ab_loopvar_ = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (original_jis_string_index < (SI_Long)0L)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	translated_jis_string_index = translated_jis_string_index - 
		(SI_Long)1L;
    if (translated_jis_string_index < (SI_Long)0L)
	goto end_loop;
    if (translated_jis_string_is_simple_qm) {
	base_index = translated_jis_string_index << (SI_Long)1L;
	temp = FIX((IFIX(CHAR_INT(CHR(ISCHAR(translated_jis_string,
		base_index)))) << (SI_Long)8L) + 
		IFIX(CHAR_INT(CHR(ISCHAR(translated_jis_string,base_index 
		+ (SI_Long)1L)))));
    }
    else {
	base_index = translated_jis_string_index << (SI_Long)1L;
	temp = FIX((IFIX(CHAR_INT(CHR(ICHAR(translated_jis_string,
		base_index)))) << (SI_Long)8L) + 
		IFIX(CHAR_INT(CHR(ICHAR(translated_jis_string,base_index + 
		(SI_Long)1L)))));
    }
    if (original_jis_string_is_simple_qm) {
	base_index = original_jis_string_index << (SI_Long)1L;
	temp_1 = FIX((IFIX(CHAR_INT(CHR(ISCHAR(original_jis_string,
		base_index)))) << (SI_Long)8L) + 
		IFIX(CHAR_INT(CHR(ISCHAR(original_jis_string,base_index + 
		(SI_Long)1L)))));
    }
    else {
	base_index = original_jis_string_index << (SI_Long)1L;
	temp_1 = FIX((IFIX(CHAR_INT(CHR(ICHAR(original_jis_string,
		base_index)))) << (SI_Long)8L) + 
		IFIX(CHAR_INT(CHR(ICHAR(original_jis_string,base_index + 
		(SI_Long)1L)))));
    }
    if (FIXNUM_NE(temp,temp_1))
	goto end_loop;
    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    ab_loop_iter_flag_ = Nil;
    original_jis_string_index = original_jis_string_index - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(ab_loopvar_));
    return VALUES_1(Qnil);
}

Object Maximum_number_of_hiragana_bytes_to_translate = UNBOUND;

/* GET-LIST-OF-CHOICES-OF-KANJI-TRANSLATION */
Object get_list_of_choices_of_kanji_translation(hiragana_jis_buffer,
	    number_of_hiragana_bytes)
    Object hiragana_jis_buffer, number_of_hiragana_bytes;
{
    Object kanji_buffer, choices, tail_of_choices, hiragana_jis_string;
    Object number_of_characters_not_used, number_of_jis_characters_used;
    Object number_of_output_bytes_qm, number_of_candidates_left_qm, jis_string;
    Object characters_to_drop, unacceptable_string, ab_loop_list_;
    Object gensymed_symbol, string_1, temp_2;
    SI_Long number_of_hiragana_characters, temp, length_of_kanji_buffer;
    SI_Long translated_jis_string_length, start_qm, end_qm;
    char temp_1;
    Object result;

    x_note_fn_call(122,7);
    if (FIXNUM_GT(number_of_hiragana_bytes,
	    Maximum_number_of_hiragana_bytes_to_translate))
	number_of_hiragana_bytes = 
		Maximum_number_of_hiragana_bytes_to_translate;
    number_of_hiragana_characters = IFIX(number_of_hiragana_bytes) >>  -  
	    - (SI_Long)1L;
    temp = IFIX(number_of_hiragana_bytes) >>  -  - (SI_Long)1L;
    length_of_kanji_buffer = MAX(temp,(SI_Long)30L);
    kanji_buffer = obtain_simple_gensym_string(FIX(length_of_kanji_buffer 
	    << (SI_Long)1L));
    choices = Nil;
    tail_of_choices = Nil;
    hiragana_jis_string = 
	    convert_n_bytes_to_jis_string(hiragana_jis_buffer,
	    number_of_hiragana_bytes);
    number_of_characters_not_used = FIX(number_of_hiragana_characters);
    result = kka_p_batkanakan(FIX((SI_Long)1L),hiragana_jis_buffer,
	    number_of_hiragana_bytes,kanji_buffer);
    MVS_3(result,number_of_jis_characters_used,number_of_output_bytes_qm,
	    number_of_candidates_left_qm);
    jis_string = Nil;
    characters_to_drop = Nil;
  next_loop:
    if ( !(IFIX(number_of_jis_characters_used) > (SI_Long)0L))
	goto end_loop;
    jis_string = convert_n_bytes_to_jis_string(kanji_buffer,
	    number_of_output_bytes_qm);
    characters_to_drop = number_of_characters_untranslated(jis_string,
	    hiragana_jis_string);
    if (FIXNUM_LE(characters_to_drop,number_of_characters_not_used)) {
	if (FIXNUM_LT(characters_to_drop,number_of_characters_not_used)) {
	    reclaim_slot_value(choices);
	    choices = Nil;
	    number_of_characters_not_used = characters_to_drop;
	}
	translated_jis_string_length = IFIX(length(jis_string)) - 
		(IFIX(characters_to_drop) << (SI_Long)1L);
	if (translated_jis_string_length != (SI_Long)0L &&  
		!TRUEP(string_eq(4,jis_string,hiragana_jis_string,Kend1,
		FIX(translated_jis_string_length)))) {
	    unacceptable_string = Nil;
	    ab_loop_list_ = choices;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    unacceptable_string = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (string_eq(4,jis_string,unacceptable_string,Kend1,
		    FIX(translated_jis_string_length))) {
		temp_1 = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(T);
	    goto end_1;
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (IFIX(characters_to_drop) == (SI_Long)0L)
		gensymed_symbol = jis_string;
	    else {
		string_1 = jis_string;
		start_qm = (SI_Long)0L;
		end_qm = (IFIX(length(jis_string)) >>  -  - (SI_Long)1L) - 
			IFIX(characters_to_drop);
		temp_2 = gensym_string_substring(string_1,FIX(start_qm) ? 
			FIX(start_qm << (SI_Long)1L) : Nil,FIX(end_qm) ? 
			FIX(end_qm << (SI_Long)1L) : Nil);
		reclaim_gensym_string(jis_string);
		gensymed_symbol = temp_2;
	    }
	    gensymed_symbol = slot_value_cons_1(gensymed_symbol,Nil);
	    if (choices) {
		if ( !TRUEP(tail_of_choices))
		    tail_of_choices = last(choices,_);
		M_CDR(tail_of_choices) = gensymed_symbol;
	    }
	    else
		choices = gensymed_symbol;
	    tail_of_choices = gensymed_symbol;
	}
	else
	    reclaim_gensym_string(jis_string);
    }
    else
	reclaim_gensym_string(jis_string);
    if (IFIX(number_of_candidates_left_qm) <= (SI_Long)0L)
	goto end_2;
    else {
	result = kka_p_batkanakan(FIX((SI_Long)0L),hiragana_jis_buffer,
		number_of_hiragana_bytes,kanji_buffer);
	MVS_3(result,number_of_jis_characters_used,
		number_of_output_bytes_qm,number_of_candidates_left_qm);
    }
    goto next_loop;
  end_loop:
    goto end_2;
  end_2:;
    reclaim_gensym_string(hiragana_jis_string);
    reclaim_gensym_string(kanji_buffer);
    return VALUES_2(choices,FIX(number_of_hiragana_characters - 
	    IFIX(number_of_characters_not_used)));
}

/* SEARCH-FOR-LONGEST-PREFIX-WITH-KFEP-WORD-CHOICES */
Object search_for_longest_prefix_with_kfep_word_choices varargs_1(int, n)
{
    Object text_string, minimum_number_of_gensym_characters_to_convert;
    Object ok_to_get_first_choice_only_qm, jis_text_strings_qm;
    Object number_of_characters_used_qm, jis_string_to_translate_qm;
    Object actual_number_of_jis_bytes_qm, jis_buffer, reclaim_qm;
    Object number_of_bytes_in_jis_string_to_translate;
    Object slot_value_list_of_jis_strings, number_of_gensym_characters_used, l;
    Object jis_string, car_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(122,8);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    minimum_number_of_gensym_characters_to_convert = REQUIRED_ARG_nonrelocating();
    ok_to_get_first_choice_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    jis_text_strings_qm = Nil;
    number_of_characters_used_qm = Nil;
    if (IFIX(length(text_string)) != (SI_Long)0L) {
	result = convert_to_jis_string_if_possible(text_string);
	MVS_2(result,jis_string_to_translate_qm,actual_number_of_jis_bytes_qm);
	if (jis_string_to_translate_qm) {
	    jis_buffer = jis_string_to_translate_qm;
	    reclaim_qm = Nil;
	    if (ARRAY_HAS_FILL_POINTER_P(jis_string_to_translate_qm)) {
		reclaim_qm = T;
		jis_buffer = 
			copy_managed_lisp_string(jis_string_to_translate_qm,
			FIX((SI_Long)0L),actual_number_of_jis_bytes_qm);
	    }
	    number_of_bytes_in_jis_string_to_translate = 
		    actual_number_of_jis_bytes_qm;
	  next_loop:
	    if ( !( !TRUEP(jis_text_strings_qm) && 
		    IFIX(number_of_bytes_in_jis_string_to_translate) >>  - 
		     - (SI_Long)1L >= 
		    IFIX(minimum_number_of_gensym_characters_to_convert)))
		goto end_loop;
	    result = get_list_of_choices_of_kanji_translation(jis_buffer,
		    number_of_bytes_in_jis_string_to_translate);
	    MVS_2(result,slot_value_list_of_jis_strings,
		    number_of_gensym_characters_used);
	    if (slot_value_list_of_jis_strings) {
		l = slot_value_list_of_jis_strings;
		jis_string = Nil;
	      next_loop_1:
		if ( !TRUEP(l))
		    goto end_loop_1;
		jis_string = CAR(l);
		car_new_value = 
			convert_jis_string_to_text_string(jis_string,
			FIX(IFIX(length(jis_string)) >>  -  - (SI_Long)1L));
		M_CAR(l) = car_new_value;
		reclaim_gensym_string(jis_string);
		l = M_CDR(l);
		goto next_loop_1;
	      end_loop_1:
		jis_text_strings_qm = slot_value_list_of_jis_strings;
	    }
	    number_of_characters_used_qm = number_of_gensym_characters_used;
	    goto end_1;
	    goto next_loop;
	  end_loop:
	  end_1:;
	    if (reclaim_qm)
		reclaim_gensym_string(jis_buffer);
	}
    }
    return VALUES_2(jis_text_strings_qm,number_of_characters_used_qm);
}

Object Kfep_learning_capability_qm = UNBOUND;

/* NOTE-KFEP-CONVERSION-CHOICE */
Object note_kfep_conversion_choice(string_1,list_of_choices,choice_index)
    Object string_1, list_of_choices, choice_index;
{
    x_note_fn_call(122,9);
    if (Kfep_learning_capability_qm)
	return kfep_kka_p_update_kojin(choice_index);
    else
	return VALUES_1(Nil);
}

void kfep3_INIT()
{
    Object AB_package, string_constant_79, Qjis_offsets_for_y_kana_characters;
    Object string_constant_78, Qjis_offsets_for_y_prefix_kana_characters;
    Object array_constant, string_constant_11, string_constant_9;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_10, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant;

    x_note_fn_call(122,10);
    SET_PACKAGE("AB");
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)87L));
    string_constant = STATIC_STRING("");
    string_constant_1 = STATIC_STRING("xa");
    string_constant_2 = STATIC_STRING("a");
    string_constant_3 = STATIC_STRING("i");
    string_constant_4 = STATIC_STRING("xu");
    string_constant_5 = STATIC_STRING("u");
    string_constant_6 = STATIC_STRING("e");
    string_constant_7 = STATIC_STRING("xo");
    string_constant_8 = STATIC_STRING("o");
    string_constant_9 = STATIC_STRING("ka");
    string_constant_10 = STATIC_STRING("ga");
    string_constant_11 = STATIC_STRING("ki");
    string_constant_12 = STATIC_STRING("gi");
    string_constant_13 = STATIC_STRING("ku");
    string_constant_14 = STATIC_STRING("gu");
    string_constant_15 = STATIC_STRING("ke");
    string_constant_16 = STATIC_STRING("ge");
    string_constant_17 = STATIC_STRING("ko");
    string_constant_18 = STATIC_STRING("go");
    string_constant_19 = STATIC_STRING("sa");
    string_constant_20 = STATIC_STRING("za");
    string_constant_21 = STATIC_STRING("si");
    string_constant_22 = STATIC_STRING("zi");
    string_constant_23 = STATIC_STRING("su");
    string_constant_24 = STATIC_STRING("zu");
    string_constant_25 = STATIC_STRING("se");
    string_constant_26 = STATIC_STRING("ze");
    string_constant_27 = STATIC_STRING("so");
    string_constant_28 = STATIC_STRING("zo");
    string_constant_29 = STATIC_STRING("ta");
    string_constant_30 = STATIC_STRING("da");
    string_constant_31 = STATIC_STRING("ti");
    string_constant_32 = STATIC_STRING("di");
    string_constant_33 = STATIC_STRING("tu");
    string_constant_34 = STATIC_STRING("du");
    string_constant_35 = STATIC_STRING("te");
    string_constant_36 = STATIC_STRING("de");
    string_constant_37 = STATIC_STRING("to");
    string_constant_38 = STATIC_STRING("do");
    string_constant_39 = STATIC_STRING("na");
    string_constant_40 = STATIC_STRING("ni");
    string_constant_41 = STATIC_STRING("nu");
    string_constant_42 = STATIC_STRING("ne");
    string_constant_43 = STATIC_STRING("no");
    string_constant_44 = STATIC_STRING("ha");
    string_constant_45 = STATIC_STRING("ba");
    string_constant_46 = STATIC_STRING("pa");
    string_constant_47 = STATIC_STRING("hi");
    string_constant_48 = STATIC_STRING("bi");
    string_constant_49 = STATIC_STRING("pi");
    string_constant_50 = STATIC_STRING("hu");
    string_constant_51 = STATIC_STRING("bu");
    string_constant_52 = STATIC_STRING("pu");
    string_constant_53 = STATIC_STRING("he");
    string_constant_54 = STATIC_STRING("be");
    string_constant_55 = STATIC_STRING("pe");
    string_constant_56 = STATIC_STRING("ho");
    string_constant_57 = STATIC_STRING("bo");
    string_constant_58 = STATIC_STRING("po");
    string_constant_59 = STATIC_STRING("ma");
    string_constant_60 = STATIC_STRING("mi");
    string_constant_61 = STATIC_STRING("mu");
    string_constant_62 = STATIC_STRING("me");
    string_constant_63 = STATIC_STRING("mo");
    string_constant_64 = STATIC_STRING("ya");
    string_constant_65 = STATIC_STRING("yu");
    string_constant_66 = STATIC_STRING("yo");
    string_constant_67 = STATIC_STRING("ra");
    string_constant_68 = STATIC_STRING("ri");
    string_constant_69 = STATIC_STRING("ru");
    string_constant_70 = STATIC_STRING("re");
    string_constant_71 = STATIC_STRING("ro");
    string_constant_72 = STATIC_STRING("wa");
    string_constant_73 = STATIC_STRING("wi");
    string_constant_74 = STATIC_STRING("we");
    string_constant_75 = STATIC_STRING("wo");
    string_constant_76 = STATIC_STRING("n");
    string_constant_77 = STATIC_STRING("v");
    ISASET_1(array_constant,(SI_Long)0L,string_constant);
    ISASET_1(array_constant,(SI_Long)1L,string_constant_1);
    ISASET_1(array_constant,(SI_Long)2L,string_constant_2);
    ISASET_1(array_constant,(SI_Long)3L,string_constant_3);
    ISASET_1(array_constant,(SI_Long)4L,string_constant_3);
    ISASET_1(array_constant,(SI_Long)5L,string_constant_4);
    ISASET_1(array_constant,(SI_Long)6L,string_constant_5);
    ISASET_1(array_constant,(SI_Long)7L,string_constant_6);
    ISASET_1(array_constant,(SI_Long)8L,string_constant_6);
    ISASET_1(array_constant,(SI_Long)9L,string_constant_7);
    ISASET_1(array_constant,(SI_Long)10L,string_constant_8);
    ISASET_1(array_constant,(SI_Long)11L,string_constant_9);
    ISASET_1(array_constant,(SI_Long)12L,string_constant_10);
    ISASET_1(array_constant,(SI_Long)13L,string_constant_11);
    ISASET_1(array_constant,(SI_Long)14L,string_constant_12);
    ISASET_1(array_constant,(SI_Long)15L,string_constant_13);
    ISASET_1(array_constant,(SI_Long)16L,string_constant_14);
    ISASET_1(array_constant,(SI_Long)17L,string_constant_15);
    ISASET_1(array_constant,(SI_Long)18L,string_constant_16);
    ISASET_1(array_constant,(SI_Long)19L,string_constant_17);
    ISASET_1(array_constant,(SI_Long)20L,string_constant_18);
    ISASET_1(array_constant,(SI_Long)21L,string_constant_19);
    ISASET_1(array_constant,(SI_Long)22L,string_constant_20);
    ISASET_1(array_constant,(SI_Long)23L,string_constant_21);
    ISASET_1(array_constant,(SI_Long)24L,string_constant_22);
    ISASET_1(array_constant,(SI_Long)25L,string_constant_23);
    ISASET_1(array_constant,(SI_Long)26L,string_constant_24);
    ISASET_1(array_constant,(SI_Long)27L,string_constant_25);
    ISASET_1(array_constant,(SI_Long)28L,string_constant_26);
    ISASET_1(array_constant,(SI_Long)29L,string_constant_27);
    ISASET_1(array_constant,(SI_Long)30L,string_constant_28);
    ISASET_1(array_constant,(SI_Long)31L,string_constant_29);
    ISASET_1(array_constant,(SI_Long)32L,string_constant_30);
    ISASET_1(array_constant,(SI_Long)33L,string_constant_31);
    ISASET_1(array_constant,(SI_Long)34L,string_constant_32);
    ISASET_1(array_constant,(SI_Long)35L,string_constant_33);
    ISASET_1(array_constant,(SI_Long)36L,string_constant_33);
    ISASET_1(array_constant,(SI_Long)37L,string_constant_34);
    ISASET_1(array_constant,(SI_Long)38L,string_constant_35);
    ISASET_1(array_constant,(SI_Long)39L,string_constant_36);
    ISASET_1(array_constant,(SI_Long)40L,string_constant_37);
    ISASET_1(array_constant,(SI_Long)41L,string_constant_38);
    ISASET_1(array_constant,(SI_Long)42L,string_constant_39);
    ISASET_1(array_constant,(SI_Long)43L,string_constant_40);
    ISASET_1(array_constant,(SI_Long)44L,string_constant_41);
    ISASET_1(array_constant,(SI_Long)45L,string_constant_42);
    ISASET_1(array_constant,(SI_Long)46L,string_constant_43);
    ISASET_1(array_constant,(SI_Long)47L,string_constant_44);
    ISASET_1(array_constant,(SI_Long)48L,string_constant_45);
    ISASET_1(array_constant,(SI_Long)49L,string_constant_46);
    ISASET_1(array_constant,(SI_Long)50L,string_constant_47);
    ISASET_1(array_constant,(SI_Long)51L,string_constant_48);
    ISASET_1(array_constant,(SI_Long)52L,string_constant_49);
    ISASET_1(array_constant,(SI_Long)53L,string_constant_50);
    ISASET_1(array_constant,(SI_Long)54L,string_constant_51);
    ISASET_1(array_constant,(SI_Long)55L,string_constant_52);
    ISASET_1(array_constant,(SI_Long)56L,string_constant_53);
    ISASET_1(array_constant,(SI_Long)57L,string_constant_54);
    ISASET_1(array_constant,(SI_Long)58L,string_constant_55);
    ISASET_1(array_constant,(SI_Long)59L,string_constant_56);
    ISASET_1(array_constant,(SI_Long)60L,string_constant_57);
    ISASET_1(array_constant,(SI_Long)61L,string_constant_58);
    ISASET_1(array_constant,(SI_Long)62L,string_constant_59);
    ISASET_1(array_constant,(SI_Long)63L,string_constant_60);
    ISASET_1(array_constant,(SI_Long)64L,string_constant_61);
    ISASET_1(array_constant,(SI_Long)65L,string_constant_62);
    ISASET_1(array_constant,(SI_Long)66L,string_constant_63);
    ISASET_1(array_constant,(SI_Long)67L,string_constant_64);
    ISASET_1(array_constant,(SI_Long)68L,string_constant_64);
    ISASET_1(array_constant,(SI_Long)69L,string_constant_65);
    ISASET_1(array_constant,(SI_Long)70L,string_constant_65);
    ISASET_1(array_constant,(SI_Long)71L,string_constant_66);
    ISASET_1(array_constant,(SI_Long)72L,string_constant_66);
    ISASET_1(array_constant,(SI_Long)73L,string_constant_67);
    ISASET_1(array_constant,(SI_Long)74L,string_constant_68);
    ISASET_1(array_constant,(SI_Long)75L,string_constant_69);
    ISASET_1(array_constant,(SI_Long)76L,string_constant_70);
    ISASET_1(array_constant,(SI_Long)77L,string_constant_71);
    ISASET_1(array_constant,(SI_Long)78L,string_constant_72);
    ISASET_1(array_constant,(SI_Long)79L,string_constant_72);
    ISASET_1(array_constant,(SI_Long)80L,string_constant_73);
    ISASET_1(array_constant,(SI_Long)81L,string_constant_74);
    ISASET_1(array_constant,(SI_Long)82L,string_constant_75);
    ISASET_1(array_constant,(SI_Long)83L,string_constant_76);
    ISASET_1(array_constant,(SI_Long)84L,string_constant_77);
    ISASET_1(array_constant,(SI_Long)85L,string_constant_9);
    ISASET_1(array_constant,(SI_Long)86L,string_constant_11);
    Jis_kana_to_ascii = array_constant;
    AB_package = STATIC_PACKAGE("AB");
    Qjis_offsets_for_y_prefix_kana_characters = 
	    STATIC_SYMBOL("JIS-OFFSETS-FOR-Y-PREFIX-KANA-CHARACTERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjis_offsets_for_y_prefix_kana_characters,
	    Jis_offsets_for_y_prefix_kana_characters);
    string_constant_78 = 
	    STATIC_STRING("1yxy3Jy3Ky3Ty3Uy3dy3ky3ly3my3xy3-6y3-Cy3-Iy");
    SET_SYMBOL_VALUE(Qjis_offsets_for_y_prefix_kana_characters,
	    regenerate_optimized_constant(string_constant_78));
    Qjis_offsets_for_y_kana_characters = 
	    STATIC_SYMBOL("JIS-OFFSETS-FOR-Y-KANA-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjis_offsets_for_y_kana_characters,
	    Jis_offsets_for_y_kana_characters);
    string_constant_79 = STATIC_STRING("1n3-=y3-1y3-3y");
    SET_SYMBOL_VALUE(Qjis_offsets_for_y_kana_characters,
	    regenerate_optimized_constant(string_constant_79));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)77L),
	    FIX((SI_Long)109L));
    Maximum_number_of_hiragana_bytes_to_translate = FIX((SI_Long)40L);
    Kfep_learning_capability_qm = Nil;
}
