/* gwtl1.c
 * Input file:  gwutil-1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gwtl1.h"


Object G2int_max_of_foreign_string_pad = UNBOUND;

Object G2int_current_foreign_string_pad = UNBOUND;

/* COERCE-INTO-FOREIGN-STRING-PAD */
Object g2int_coerce_into_foreign_string_pad(string_1)
    Object string_1;
{
    Object pad, length_1;
    SI_Long i, ab_loop_bind_;
    char char_new_value;

    x_note_fn_call(53,0);
    pad = G2int_current_foreign_string_pad;
    length_1 = length(string_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_new_value = ICHAR(string_1,i);
    SET_ICHAR(pad,i,char_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    SET_CHAR(pad,length_1,G2int_null_character_for_c_strings);
    return VALUES_1(pad);
}

/* COERCE-INTO-FOREIGN-STRING-PAD-WITH-CRLF */
Object g2int_coerce_into_foreign_string_pad_with_crlf(string_1)
    Object string_1;
{
    Object pad, length_1, temp, char_arg_2;
    SI_Long i, ab_loop_bind_;
    char char_new_value;

    x_note_fn_call(53,1);
    pad = G2int_current_foreign_string_pad;
    length_1 = length(string_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_new_value = ICHAR(string_1,i);
    SET_ICHAR(pad,i,char_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = CHR('\r');
    SET_CHAR(pad,length_1,temp);
    char_arg_2 = add1(length_1);
    temp = CHR('\n');
    SET_CHAR(pad,char_arg_2,temp);
    char_arg_2 = add(FIX((SI_Long)2L),length_1);
    SET_CHAR(pad,char_arg_2,G2int_null_character_for_c_strings);
    return VALUES_1(pad);
}

/* MAKE-TEXT-STRING-FROM-FOREIGN-STRING-PAD */
Object g2int_make_text_string_from_foreign_string_pad(length_1)
    Object length_1;
{
    Object pad, text_string;
    SI_Long i, ab_loop_bind_;
    char char_new_value;

    x_note_fn_call(53,2);
    pad = G2int_current_foreign_string_pad;
    text_string = g2int_obtain_simple_gensym_string(length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_new_value = ICHAR(pad,i);
    SET_ICHAR(text_string,i,char_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(text_string);
}

/* MAKE-TEXT-STRING-FROM-C-STRING-IN-FOREIGN-STRING-PAD */
Object g2int_make_text_string_from_c_string_in_foreign_string_pad()
{
    Object null_char, pad, result_1;
    SI_Long i, ab_loop_bind_, j;
    char char_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(53,3);
    null_char = CODE_CHAR(FIX((SI_Long)0L));
    PUSH_SPECIAL(G2int_null_char,null_char,0);
      pad = G2int_current_foreign_string_pad;
      i = (SI_Long)0L;
      ab_loop_bind_ = IFIX(length(pad));
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(G2int_null_char,CHR(ICHAR(pad,i)))) {
	  result_1 = g2int_obtain_simple_gensym_string(FIX(i));
	  j = (SI_Long)0L;
	  ab_loop_bind_ = i;
	next_loop_1:
	  if (j >= ab_loop_bind_)
	      goto end_loop_1;
	  char_new_value = ICHAR(pad,j);
	  SET_ICHAR(result_1,j,char_new_value);
	  j = j + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:;
	  result = VALUES_1(result_1);
	  goto end;
      }
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end:;
    POP_SPECIAL();
    return result;
}

/* MAKE-TEXT-SAFE-FOR-C */
Object g2int_make_text_safe_for_c(string_1)
    Object string_1;
{
    x_note_fn_call(53,4);
    if (SIMPLE_STRING_P(string_1))
	return VALUES_1(string_1);
    else
	return g2int_coerce_into_foreign_string_pad(string_1);
}

Object G2int_tilde_escape_to_iso_latin_1_map = UNBOUND;

static Object Qg2int_wide_string;  /* wide-string */

/* TWRITE-TEXT-GENSYM-PT-TO-I-ASCII */
Object g2int_twrite_text_gensym_pt_to_i_ascii(text_string)
    Object text_string;
{
    Object escape_character_qm, character_or_character_code, gensym_string;
    Object temp_1, gensymed_symbol, thing, temp_3, schar_arg_2;
    Object schar_new_value, simple_or_wide_character;
    SI_Long length_of_string, i, ascii_code, temp_2;
    char string_is_simple_qm, gensym_string_is_simple_qm;
    char temp, character_1;
    char gensymed_symbol_1;
    char thing_1;

    x_note_fn_call(53,5);
    escape_character_qm = Nil;
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(text_string);
    length_of_string = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string)) : 
	    IFIX(length(text_string));
    i = (SI_Long)0L;
    character_or_character_code = Nil;
  next_loop:
    if ( !(i < length_of_string))
	goto end_loop;
    gensym_string = text_string;
    gensym_string_is_simple_qm = string_is_simple_qm;
    temp = gensym_string_is_simple_qm ? ISCHAR(gensym_string,i) : 
	    ICHAR(gensym_string,i);
    i = i + (SI_Long)1L;
    character_1 = temp;
    temp_1 = CHAR_CODE(CHAR_TO_CHARACTER(character_1));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
	    FIX((SI_Long)127L)))) {
	escape_character_qm = Nil;
	character_or_character_code = CHAR_TO_CHARACTER(character_1);
    }
    else
	switch (INTEGER_TO_CHAR(temp_1)) {
	  case 64:
	  case 126:
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
	    temp_1 = gensym_string_is_simple_qm ? CHR(ISCHAR(gensym_string,
		    i)) : CHR(ICHAR(gensym_string,i));
	    i = i + (SI_Long)1L;
	    character_or_character_code = temp_1;
	    break;
	  case 92:
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
	    gensymed_symbol = gensym_string;
	    gensymed_symbol_1 = gensym_string_is_simple_qm;
	    temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
		    ICHAR(gensymed_symbol,i);
	    i = i + (SI_Long)1L;
	    ascii_code = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
	    if (ascii_code < (SI_Long)40L) {
		temp_2 = ascii_code << (SI_Long)13L;
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		temp_2 = temp_2 + (SI_Long)95L * 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		character_or_character_code = FIX(temp_2 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp))) + 
			(SI_Long)-265976L);
	    }
	    else {
		temp_2 = (SI_Long)95L * ascii_code;
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		character_or_character_code = FIX(temp_2 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp))) + 
			(SI_Long)4360L);
	    }
	    break;
	  default:
	    escape_character_qm = Nil;
	    character_or_character_code = CHAR_TO_CHARACTER(character_1);
	    break;
	}
    if ( !TRUEP(escape_character_qm)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = character_or_character_code;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_3 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_3;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('~'))) {
	simple_or_wide_character = 
		SCHAR(G2int_tilde_escape_to_iso_latin_1_map,
		CHAR_CODE(character_or_character_code));
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_3 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_3;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('@'))) {
	temp_1 = CHAR_CODE(character_or_character_code);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = ' ';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_3 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = ' ';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_3;
	    }
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 76:
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing_1 = '\r';
		    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_3 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing_1 = '\r';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_3;
		}
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing_1 = '\n';
		    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_3 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing_1 = '\n';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	      case 80:
		break;
	      default:
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing_1 = ' ';
		    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_3 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing_1 = ' ';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	    }
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = ' ';
	    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
		    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_3 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = ' ';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
		    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_3;
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_handling_of_iso_latin_1_character = UNBOUND;

Object G2int_gensym_character_of_iso_latin_1_character = UNBOUND;

/* TWRITE-TEXT-I-ASCII-TO-GENSYM-PT */
Object g2int_twrite_text_i_ascii_to_gensym_pt(ascii_string)
    Object ascii_string;
{
    Object char_1, char_code_1, just_saw_return_qm, temp;
    Object simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long length_of_string, i;
    char string_is_simple_qm;
    char thing_1;

    x_note_fn_call(53,6);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(ascii_string);
    length_of_string = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ascii_string)) : 
	    IFIX(length(ascii_string));
    i = (SI_Long)0L;
    char_1 = Nil;
    char_code_1 = Nil;
    just_saw_return_qm = Nil;
  next_loop:
    if (i == length_of_string)
	goto end_loop;
    temp = string_is_simple_qm ? CHR(ISCHAR(ascii_string,i)) : 
	    CHR(ICHAR(ascii_string,i));
    i = i + (SI_Long)1L;
    char_1 = temp;
    char_code_1 = CHAR_CODE(char_1);
    temp = ISVREF(G2int_handling_of_iso_latin_1_character,IFIX(char_code_1));
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    simple_or_wide_character = 
		    SCHAR(G2int_gensym_character_of_iso_latin_1_character,
		    char_code_1);
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = simple_or_wide_character;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
	    }
	    break;
	  case 1:
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = '~';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = '~';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
	    }
	    simple_or_wide_character = 
		    SCHAR(G2int_gensym_character_of_iso_latin_1_character,
		    char_code_1);
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = simple_or_wide_character;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
	    }
	    break;
	  case 2:
	    if ( !TRUEP(just_saw_return_qm)) {
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing_1 = '@';
		    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_1 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing_1 = '@';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		    temp_1 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_1;
		}
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing_1 = 'L';
		    g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_1 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing_1 = 'L';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		    temp_1 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_1;
		}
	    }
	    break;
	  case 3:
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = '@';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = '@';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
	    }
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = 'L';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = 'L';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
	    }
	    break;
	  case 4:
	    break;
	  default:
	    break;
	}
    just_saw_return_qm = EQ(CHR('\r'),char_1) ? T : Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ALARM-P */
Object g2int_alarm_p(alarm_time_mf)
    Object alarm_time_mf;
{
    Object temp;

    x_note_fn_call(53,7);
    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(alarm_time_mf,(SI_Long)0L));
    temp = FIXNUM_LT(temp,
	    DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float())) ? T : Nil;
    return VALUES_1(temp);
}

void gwutil_1_INIT()
{
    Object string_constant, array_constant, AB_package;

    x_note_fn_call(53,8);
    SET_PACKAGE("AB");
    G2int_max_of_foreign_string_pad = FIX((SI_Long)10000L);
    G2int_current_foreign_string_pad = make_string(1,
	    G2int_max_of_foreign_string_pad);
    G2int_tilde_escape_to_iso_latin_1_map = coerce(list(256,CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR('\241'),CHR(' '),
	    CHR('\243'),CHR('\245'),CHR('\242'),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR('\353'),CHR('\313'),CHR('\357'),CHR('\317'),CHR('\343'),
	    CHR('\303'),CHR('\365'),CHR('\325'),CHR('\373'),CHR('\333'),
	    CHR(' '),CHR('\256'),CHR('\253'),CHR(' '),CHR('\273'),
	    CHR('\277'),CHR('@'),CHR('\304'),CHR('\301'),CHR('\307'),
	    CHR('\302'),CHR('\311'),CHR('\312'),CHR('\310'),CHR('\314'),
	    CHR('\315'),CHR('\316'),CHR(' '),CHR(' '),CHR('\300'),
	    CHR('\321'),CHR('\326'),CHR('\323'),CHR('\324'),CHR('\305'),
	    CHR(' '),CHR('\330'),CHR('\334'),CHR('\332'),CHR(' '),
	    CHR('\306'),CHR('\322'),CHR('\331'),CHR(' '),CHR('\\'),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR('\344'),CHR('\341'),
	    CHR('\347'),CHR('\342'),CHR('\351'),CHR('\352'),CHR('\350'),
	    CHR('\354'),CHR('\355'),CHR('\356'),CHR(' '),CHR(' '),
	    CHR('\340'),CHR('\361'),CHR('\366'),CHR('\363'),CHR('\364'),
	    CHR('\345'),CHR('\337'),CHR('\370'),CHR('\374'),CHR('\372'),
	    CHR(' '),CHR('\346'),CHR('\362'),CHR('\371'),CHR(' '),
	    CHR('\251'),CHR(' '),CHR('~'),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),CHR(' '),
	    CHR(' ')),Qstring);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)256L));
    ISASET_1(array_constant,(SI_Long)0L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)1L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)2L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)3L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)4L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)5L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)6L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)7L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)8L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)9L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)10L,FIX((SI_Long)2L));
    ISASET_1(array_constant,(SI_Long)11L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)12L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)13L,FIX((SI_Long)3L));
    ISASET_1(array_constant,(SI_Long)14L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)15L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)16L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)17L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)18L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)19L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)20L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)21L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)22L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)23L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)24L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)25L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)26L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)27L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)28L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)29L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)30L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)31L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)32L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)33L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)34L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)35L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)36L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)37L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)38L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)39L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)40L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)41L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)42L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)43L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)44L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)45L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)46L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)47L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)48L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)49L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)50L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)51L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)52L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)53L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)54L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)55L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)56L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)57L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)58L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)59L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)60L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)61L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)62L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)63L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)64L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)65L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)66L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)67L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)68L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)69L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)70L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)71L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)72L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)73L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)74L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)75L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)76L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)77L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)78L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)79L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)80L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)81L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)82L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)83L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)84L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)85L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)86L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)87L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)88L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)89L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)90L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)91L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)92L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)93L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)94L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)95L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)96L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)97L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)98L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)99L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)100L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)101L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)102L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)103L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)104L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)105L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)106L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)107L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)108L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)109L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)110L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)111L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)112L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)113L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)114L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)115L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)116L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)117L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)118L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)119L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)120L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)121L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)122L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)123L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)124L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)125L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)126L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)127L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)128L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)129L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)130L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)131L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)132L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)133L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)134L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)135L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)136L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)137L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)138L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)139L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)140L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)141L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)142L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)143L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)144L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)145L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)146L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)147L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)148L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)149L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)150L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)151L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)152L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)153L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)154L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)155L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)156L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)157L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)158L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)159L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)160L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)161L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)162L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)163L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)164L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)165L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)166L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)167L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)168L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)169L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)170L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)171L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)172L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)173L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)174L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)175L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)176L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)177L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)178L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)179L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)180L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)181L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)182L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)183L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)184L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)185L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)186L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)187L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)188L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)189L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)190L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)191L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)192L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)193L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)194L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)195L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)196L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)197L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)198L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)199L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)200L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)201L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)202L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)203L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)204L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)205L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)206L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)207L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)208L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)209L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)210L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)211L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)212L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)213L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)214L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)215L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)216L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)217L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)218L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)219L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)220L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)221L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)222L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)223L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)224L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)225L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)226L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)227L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)228L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)229L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)230L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)231L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)232L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)233L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)234L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)235L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)236L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)237L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)238L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)239L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)240L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)241L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)242L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)243L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)244L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)245L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)246L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)247L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)248L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)249L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)250L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)251L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)252L,FIX((SI_Long)1L));
    ISASET_1(array_constant,(SI_Long)253L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)254L,FIX((SI_Long)0L));
    ISASET_1(array_constant,(SI_Long)255L,FIX((SI_Long)0L));
    if (G2int_handling_of_iso_latin_1_character == UNBOUND)
	G2int_handling_of_iso_latin_1_character = array_constant;
    string_constant = 
	    string_append2(STATIC_STRING("                                 !\"#$%&\'()*+,-./0123456789:;<=>\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~                                  !%# $   | <  ;"),
	    STATIC_STRING("            >   \?MBD5ARXCGEF1HIJ3 NYPQ7O TZV9U  smbd4arxcgef0hij2 nypq6o tzv8u   "));
    if (G2int_gensym_character_of_iso_latin_1_character == UNBOUND)
	G2int_gensym_character_of_iso_latin_1_character = string_constant;
}
