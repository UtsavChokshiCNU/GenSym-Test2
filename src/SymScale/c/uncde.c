/* uncde.c
 * Input file:  unicode.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "uncde.h"


/* UNICODE-UPPERCASE-IF-LOWERCASE */
Object unicode_uppercase_if_lowercase(code_init)
    Object code_init;
{
    Object temp;
    SI_Long code;

    x_note_fn_call(26,0);
    code = IFIX(code_init);
    if ((SI_Long)0L <= code && code <= (SI_Long)127L)
	temp = (SI_Long)97L <= code && code <= (SI_Long)122L ? FIX(code + 
		(SI_Long)-32L) : Nil;
    else if ((SI_Long)128L <= code && code <= (SI_Long)255L) {
	if ((SI_Long)224L <= code && code <= (SI_Long)246L)
	    temp = FIX(code + (SI_Long)-32L);
	else if ((SI_Long)248L <= code && code <= (SI_Long)254L)
	    temp = FIX(code + (SI_Long)-32L);
	else if (code == (SI_Long)255L)
	    temp = FIX((SI_Long)376L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)256L <= code && code <= (SI_Long)383L) {
	if ((SI_Long)256L <= code && code <= (SI_Long)311L && ((SI_Long)1L 
		& code) == (SI_Long)1L)
	    temp = FIX(code - (SI_Long)1L);
	else if ((SI_Long)313L <= code && code <= (SI_Long)328L && 
		((SI_Long)1L & code) == (SI_Long)0L)
	    temp = FIX(code - (SI_Long)1L);
	else if ((SI_Long)330L <= code && code <= (SI_Long)375L && 
		((SI_Long)1L & code) == (SI_Long)1L)
	    temp = FIX(code - (SI_Long)1L);
	else if ((SI_Long)377L <= code && code <= (SI_Long)382L && 
		((SI_Long)1L & code) == (SI_Long)0L)
	    temp = FIX(code - (SI_Long)1L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)384L <= code && code <= (SI_Long)879L)
	temp = Qnil;
    else if ((SI_Long)880L <= code && code <= (SI_Long)975L) {
	if ((SI_Long)945L <= code && code <= (SI_Long)961L)
	    temp = FIX(code + (SI_Long)-32L);
	else if ((SI_Long)963L <= code && code <= (SI_Long)969L)
	    temp = FIX(code + (SI_Long)-32L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)976L <= code && code <= (SI_Long)1023L)
	temp = Qnil;
    else if ((SI_Long)1024L <= code && code <= (SI_Long)1151L) {
	if ((SI_Long)1072L <= code && code <= (SI_Long)1103L)
	    temp = FIX(code + (SI_Long)-32L);
	else if ((SI_Long)1105L <= code && code <= (SI_Long)1119L)
	    temp = FIX(code + (SI_Long)-80L);
	else if ((SI_Long)1120L <= code && code <= (SI_Long)1151L && 
		((SI_Long)1L & code) == (SI_Long)1L)
	    temp = FIX(code - (SI_Long)1L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)1152L <= code && code <= (SI_Long)1279L)
	temp = Qnil;
    else if ((SI_Long)1280L <= code && code <= (SI_Long)1423L)
	temp = (SI_Long)1377L <= code && code <= (SI_Long)1414L ? FIX(code 
		+ (SI_Long)-48L) : Nil;
    else if ((SI_Long)1424L <= code && code <= (SI_Long)3839L)
	temp = Qnil;
    else if ((SI_Long)4256L <= code && code <= (SI_Long)4351L)
	temp = Qnil;
    else if ((SI_Long)4352L <= code && code <= (SI_Long)4607L)
	temp = Qnil;
    else if ((SI_Long)7680L <= code && code <= (SI_Long)7935L)
	temp = Qnil;
    else if ((SI_Long)7936L <= code && code <= (SI_Long)8191L)
	temp = Qnil;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* UNICODE-LOWERCASE-IF-UPPERCASE */
Object unicode_lowercase_if_uppercase(code_init)
    Object code_init;
{
    Object temp;
    SI_Long code;

    x_note_fn_call(26,1);
    code = IFIX(code_init);
    if ((SI_Long)0L <= code && code <= (SI_Long)127L)
	temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code - 
		(SI_Long)-32L) : Nil;
    else if ((SI_Long)128L <= code && code <= (SI_Long)255L) {
	if ((SI_Long)192L <= code && code <= (SI_Long)214L)
	    temp = FIX(code - (SI_Long)-32L);
	else if ((SI_Long)216L <= code && code <= (SI_Long)222L)
	    temp = FIX(code - (SI_Long)-32L);
	else if (code == (SI_Long)376L)
	    temp = FIX((SI_Long)255L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)256L <= code && code <= (SI_Long)383L) {
	if ((SI_Long)256L <= code && code <= (SI_Long)311L && ((SI_Long)1L 
		& code) == (SI_Long)0L)
	    temp = FIX(code + (SI_Long)1L);
	else if ((SI_Long)313L <= code && code <= (SI_Long)328L && 
		((SI_Long)1L & code) == (SI_Long)1L)
	    temp = FIX(code + (SI_Long)1L);
	else if ((SI_Long)330L <= code && code <= (SI_Long)375L && 
		((SI_Long)1L & code) == (SI_Long)0L)
	    temp = FIX(code + (SI_Long)1L);
	else if ((SI_Long)377L <= code && code <= (SI_Long)382L && 
		((SI_Long)1L & code) == (SI_Long)1L)
	    temp = FIX(code + (SI_Long)1L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)384L <= code && code <= (SI_Long)879L)
	temp = Qnil;
    else if ((SI_Long)880L <= code && code <= (SI_Long)975L) {
	if ((SI_Long)913L <= code && code <= (SI_Long)929L)
	    temp = FIX(code - (SI_Long)-32L);
	else if ((SI_Long)931L <= code && code <= (SI_Long)937L)
	    temp = FIX(code - (SI_Long)-32L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)976L <= code && code <= (SI_Long)1023L)
	temp = Qnil;
    else if ((SI_Long)1024L <= code && code <= (SI_Long)1151L) {
	if ((SI_Long)1040L <= code && code <= (SI_Long)1071L)
	    temp = FIX(code - (SI_Long)-32L);
	else if ((SI_Long)1025L <= code && code <= (SI_Long)1039L)
	    temp = FIX(code - (SI_Long)-80L);
	else if ((SI_Long)1120L <= code && code <= (SI_Long)1151L && 
		((SI_Long)1L & code) == (SI_Long)0L)
	    temp = FIX(code + (SI_Long)1L);
	else
	    temp = Qnil;
    }
    else if ((SI_Long)1152L <= code && code <= (SI_Long)1279L)
	temp = Qnil;
    else if ((SI_Long)1280L <= code && code <= (SI_Long)1423L)
	temp = (SI_Long)1329L <= code && code <= (SI_Long)1366L ? FIX(code 
		- (SI_Long)-48L) : Nil;
    else if ((SI_Long)1424L <= code && code <= (SI_Long)3839L)
	temp = Qnil;
    else if ((SI_Long)4256L <= code && code <= (SI_Long)4351L)
	temp = Qnil;
    else if ((SI_Long)4352L <= code && code <= (SI_Long)4607L)
	temp = Qnil;
    else if ((SI_Long)7680L <= code && code <= (SI_Long)7935L)
	temp = Qnil;
    else if ((SI_Long)7936L <= code && code <= (SI_Long)8191L)
	temp = Qnil;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* VALID-WIDE-STRING-LENGTH-BV16 */
Object valid_wide_string_length_bv16(wide_string_bv16)
    Object wide_string_bv16;
{
    Object temp_1;
    SI_Long bv16_length, length_1;
    char temp;

    x_note_fn_call(26,2);
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    if (bv16_length >= IFIX(Extra_wide_string_bv16_elements)) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = bv16_length - IFIX(Extra_wide_string_bv16_elements) >= 
		UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - (SI_Long)2L) 
		+ ((UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? ((UBYTE_16_ISAREF_1(wide_string_bv16,bv16_length - 
	    (SI_Long)1L) & (SI_Long)57344L) == (SI_Long)57344L ? T : Nil) :
	     Nil;
    return VALUES_1(temp_1);
}

/* FILL-WIDE-STRING-1 */
Object fill_wide_string_1(wide_string,wide_character,start_init,end_init)
    Object wide_string, wide_character, start_init, end_init;
{
    SI_Long start, end_1, code, i, ab_loop_bind_;

    x_note_fn_call(26,3);
    start = IFIX(start_init);
    end_1 = IFIX(end_init);
    code = IFIX(wide_character);
    i = start;
    ab_loop_bind_ = end_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    UBYTE_16_ISASET_1(wide_string,i,code);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MAKE-WIDE-STRING-FUNCTION */
Object make_wide_string_function(length_1)
    Object length_1;
{
    Object wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(26,4);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
    return VALUES_1(wide_string_bv16);
}

/* RECLAIM-WIDE-STRING */
Object reclaim_wide_string(wide_string)
    Object wide_string;
{
    x_note_fn_call(26,5);
    reclaim_byte_vector_16(wide_string);
    return VALUES_1(Nil);
}

/* CHARW-FUNCTION */
Object charw_function(wide_string,index_1)
    Object wide_string, index_1;
{
    Object temp;

    x_note_fn_call(26,6);
    temp = FIX(UBYTE_16_ISAREF_1(wide_string,IFIX(index_1)));
    return VALUES_1(temp);
}

/* SET-CHARW-FUNCTION */
Object set_charw_function(wide_string,index_1,wide_character)
    Object wide_string, index_1, wide_character;
{
    Object temp;

    x_note_fn_call(26,7);
    temp = FIX(UBYTE_16_ISASET_1(wide_string,IFIX(index_1),
	    IFIX(wide_character)));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Print_wide_string_max_length, Qprint_wide_string_max_length);

DEFINE_VARIABLE_WITH_SYMBOL(Abbreviate_wide_strings_for_legibility, Qabbreviate_wide_strings_for_legibility);

/* PRINT-WIDE-STRING */
Object print_wide_string(wide_string,stream,print_depth)
    Object wide_string, stream, print_depth;
{
    x_note_fn_call(26,8);
    if (valid_wide_string_length_bv16(wide_string))
	return print_valid_wide_string(wide_string,stream);
    else
	return print_random_byte_vector_16(wide_string,stream);
}

static Object string_constant;     /* "Byte-vector-16 " */

static Object string_constant_1;   /* "(" */

static Object string_constant_2;   /* ")" */

static Object string_constant_3;   /* "[" */

static Object string_constant_4;   /* "|" */

static Object string_constant_5;   /* "]" */

static Object string_constant_6;   /* "\"" */

static Object string_constant_7;   /* "..." */

/* PRINT-RANDOM-BYTE-VECTOR-16 */
Object print_random_byte_vector_16(byte_vector_16,stream)
    Object byte_vector_16, stream;
{
    Object dot_object_dot, dot_stream_dot, bv16_length;
    SI_Long physical_length_limit, i, ab_loop_bind_;

    x_note_fn_call(26,9);
    dot_object_dot = byte_vector_16;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    bv16_length = SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector_16);
    write_string(2,string_constant,stream);
    write_string(1,string_constant_1);
    princ(SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector_16),stream);
    write_string(1,string_constant_2);
    write_string(2,string_constant_3,stream);
    if (IFIX(bv16_length) > (SI_Long)0L)
	princ(FIX(UBYTE_16_ISAREF_1(byte_vector_16,(SI_Long)0L)),stream);
    if (IFIX(bv16_length) > (SI_Long)1L) {
	write_string(1,string_constant_4);
	princ(FIX(UBYTE_16_ISAREF_1(byte_vector_16,(SI_Long)1L)),stream);
    }
    write_string(2,string_constant_5,stream);
    write_string(2,string_constant_6,stream);
    physical_length_limit = IFIX(bv16_length) - (SI_Long)2L;
    i = (SI_Long)0L;
    ab_loop_bind_ = MIN((SI_Long)100L,physical_length_limit);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    print_wide_character_readably_in_string(FIX(UBYTE_16_ISAREF_1(byte_vector_16,
	    i)),stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (i < physical_length_limit)
	write_string(2,string_constant_7,stream);
    write_string(1,string_constant_6);
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

/* PRINT-VALID-WIDE-STRING */
Object print_valid_wide_string(wide_string,stream)
    Object wide_string, stream;
{
    Object dot_object_dot, dot_stream_dot;
    SI_Long length_1;

    x_note_fn_call(26,10);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    length_1 = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    if (Abbreviate_wide_strings_for_legibility && 
	    IFIX(Print_wide_string_max_length) < length_1) {
	if (Print_escape) {
	    dot_object_dot = wide_string;
	    dot_stream_dot = stream;
	    print_random_object_prefix(dot_object_dot,dot_stream_dot);
	    print_valid_wide_string_1(wide_string,stream,FIX((SI_Long)0L),
		    Print_wide_string_max_length,T);
	    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
	}
	else
	    return print_valid_wide_string_1(wide_string,stream,
		    FIX((SI_Long)0L),Print_wide_string_max_length,T);
    }
    else
	return print_valid_wide_string_1(wide_string,stream,
		FIX((SI_Long)0L),FIX(length_1),Nil);
}

static Object string_constant_8;   /* "#w\"" */

/* PRINT-VALID-WIDE-STRING-1 */
Object print_valid_wide_string_1(wide_string,stream,start,end_1,
	    print_ellipsis_p)
    Object wide_string, stream, start, end_1, print_ellipsis_p;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,11);
    if (Print_escape)
	write_string(2,string_constant_8,stream);
    i = IFIX(start);
    ab_loop_bind_ = IFIX(end_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    print_wide_character_readably_in_string(FIX(UBYTE_16_ISAREF_1(wide_string,
	    i)),stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (print_ellipsis_p)
	write_string(2,string_constant_7,stream);
    if (Print_escape)
	return write_string(2,string_constant_6,stream);
    else
	return VALUES_1(Nil);
}

/* PRINT-WIDE-CHARACTER-READABLY-IN-STRING */
Object print_wide_character_readably_in_string(wide_character,stream)
    Object wide_character, stream;
{
    Object code, character_1;

    x_note_fn_call(26,12);
    code = wide_character;
    if ((SI_Long)0L <= IFIX(code) && IFIX(code) <= (SI_Long)255L) {
	character_1 = CODE_CHAR(code);
	if (Print_escape && (CHAR_EQ(character_1,CHR('\\')) || 
		CHAR_EQ(character_1,CHR('\"'))))
	    write_char(CHR('\\'),stream);
	return write_char(character_1,stream);
    }
    else {
	write_char(CHR('\\'),stream);
	write_char(CHR('u'),stream);
	if (IFIX(code) <= (SI_Long)4095L)
	    write_char(CHR('0'),stream);
	if (IFIX(code) <= (SI_Long)255L)
	    write_char(CHR('0'),stream);
	if (IFIX(code) <= (SI_Long)15L)
	    write_char(CHR('0'),stream);
	return write_in_hex_to_lisp_stream(stream,code);
    }
}

/* PRETTY-PRINT-WIDE-CHARACTER-IN-STRING */
Object pretty_print_wide_character_in_string(wide_character,stream)
    Object wide_character, stream;
{
    x_note_fn_call(26,13);
    if (IFIX(wide_character) == (SI_Long)8232L)
	return write_char(CHR('\n'),stream);
    else
	return print_wide_character_readably_in_string(wide_character,stream);
}

/* PRETTY-PRINT-WIDE-STRING-TO-STREAM */
Object pretty_print_wide_string_to_stream(wide_string,stream)
    Object wide_string, stream;
{
    SI_Long i, length_1, ab_loop_bind_;

    x_note_fn_call(26,14);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    pretty_print_wide_character_in_string(FIX(UBYTE_16_ISAREF_1(wide_string,
	    i)),stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return write_char(CHR('\n'),stream);
}

/* PRETTY-PRINT-WIDE-STRING */
Object pretty_print_wide_string(wide_string)
    Object wide_string;
{
    x_note_fn_call(26,15);
    pretty_print_wide_string_to_stream(wide_string,Standard_output);
    return VALUES_0();
}

static Object Qwide_string;        /* wide-string */

/* TWRITE-WIDE-CHARACTER-READABLY */
Object twrite_wide_character_readably(wide_character)
    Object wide_character;
{
    Object code, character_1, temp, schar_arg_2, schar_new_value, thing_1;
    char thing;

    x_note_fn_call(26,16);
    code = wide_character;
    if ((SI_Long)0L <= IFIX(code) && IFIX(code) <= (SI_Long)255L) {
	character_1 = CODE_CHAR(code);
	if (Print_escape && (CHAR_EQ(character_1,CHR('\\')) || 
		CHAR_EQ(character_1,CHR('\"')))) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = '\\';
		twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = '\\';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = character_1;
	    return twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = '\\';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = '\\';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = 'u';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = 'u';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (IFIX(code) <= (SI_Long)4095L) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = '0';
		twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (IFIX(code) <= (SI_Long)255L) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = '0';
		twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (IFIX(code) <= (SI_Long)15L) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = '0';
		twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	return twrite_positive_fixnum_in_radix(code,FIX((SI_Long)16L));
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Lisp_highest_printable_character_code, Qlisp_highest_printable_character_code);

/* PRINT-WIDE-CHARACTER */
Object print_wide_character varargs_1(int, n)
{
    Object wide_character;
    Object stream, code, character_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,17);
    INIT_ARGS_nonrelocating();
    wide_character = REQUIRED_ARG_nonrelocating();
    stream = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(stream))
	stream = Standard_output;
    code = wide_character;
    if ((SI_Long)0L <= IFIX(code) && FIXNUM_LE(code,
	    Lisp_highest_printable_character_code)) {
	character_1 = CODE_CHAR(code);
	write_char(CHR('#'),stream);
	write_char(CHR('.'),stream);
	write_char(CHR('%'),stream);
	write_char(CHR('\\'),stream);
	return write_char(character_1,stream);
    }
    else {
	write_char(CHR('#'),stream);
	write_char(CHR('u'),stream);
	if (IFIX(code) <= (SI_Long)4095L)
	    write_char(CHR('0'),stream);
	if (IFIX(code) <= (SI_Long)255L)
	    write_char(CHR('0'),stream);
	if (IFIX(code) <= (SI_Long)15L)
	    write_char(CHR('0'),stream);
	return write_in_hex_to_lisp_stream(stream,code);
    }
}

/* WRITE-IN-HEX-TO-LISP-STREAM */
Object write_in_hex_to_lisp_stream(stream,non_negative_fixnum)
    Object stream, non_negative_fixnum;
{
    SI_Long radix, temp, quotient, remainder_1;

    x_note_fn_call(26,18);
    radix = (SI_Long)16L;
    if (IFIX(non_negative_fixnum) >= radix) {
	temp = IFIX(non_negative_fixnum) / radix;
	quotient = temp;
	temp = IFIX(non_negative_fixnum) % radix;
	remainder_1 = temp;
	write_in_hex_to_lisp_stream(stream,FIX(quotient));
	write_char(digit_char(FIX(remainder_1),FIX(radix),_),stream);
    }
    else
	write_char(digit_char(non_negative_fixnum,FIX(radix),_),stream);
    return VALUES_1(Nil);
}

/* MAKE-STRINGW-FUNCTION */
Object make_stringw_function(length_1,initial_element)
    Object length_1, initial_element;
{
    Object wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(26,19);
    if (initial_element) {
	wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
		(SI_Long)3L));
	fill_wide_string_1(wide_string_bv16,initial_element,
		FIX((SI_Long)0L),length_1);
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(length_1) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
	return VALUES_1(wide_string_bv16);
    }
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(length_1) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
	return VALUES_1(wide_string_bv16);
    }
}

/* LENGTHW */
Object lengthw(real_sequence_or_wide_string)
    Object real_sequence_or_wide_string;
{
    Object temp;
    SI_Long length_1;

    x_note_fn_call(26,20);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(real_sequence_or_wide_string) != 
	    (SI_Long)0L) {
	length_1 = 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(real_sequence_or_wide_string));
	temp = FIX(UBYTE_16_ISAREF_1(real_sequence_or_wide_string,length_1 
		- (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(real_sequence_or_wide_string,length_1 
		- (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    else
	temp = length(real_sequence_or_wide_string);
    return VALUES_1(temp);
}

/* ELTW */
Object eltw(real_sequence_or_wide_string,i)
    Object real_sequence_or_wide_string, i;
{
    Object temp;

    x_note_fn_call(26,21);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(real_sequence_or_wide_string) 
	    != (SI_Long)0L ? 
	    FIX(UBYTE_16_ISAREF_1(real_sequence_or_wide_string,IFIX(i))) : 
	    elt(real_sequence_or_wide_string,i);
    return VALUES_1(temp);
}

/* CHAR=W-FUNCTION */
Object char_eq_w_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object temp;

    x_note_fn_call(26,22);
    temp = FIXNUM_EQ(wide_character_1,wide_character_2) ? T : Nil;
    return VALUES_1(temp);
}

/* CHAR/=W-FUNCTION */
Object char_sl_eq_w_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object temp;

    x_note_fn_call(26,23);
    temp = FIXNUM_NE(wide_character_1,wide_character_2) ? T : Nil;
    return VALUES_1(temp);
}

/* CHAR-EQUALW-FUNCTION */
Object char_equalw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object code, temp, temp_1;

    x_note_fn_call(26,24);
    code = wide_character_1;
    if (IFIX(code) < (SI_Long)127L)
	temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ? 
		FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp = unicode_lowercase_if_uppercase(code);
	if (temp);
	else
	    temp = code;
    }
    code = wide_character_2;
    if (IFIX(code) < (SI_Long)127L)
	temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_1 = unicode_lowercase_if_uppercase(code);
	if (temp_1);
	else
	    temp_1 = code;
    }
    temp_1 = NUM_EQ(temp,temp_1) ? T : Nil;
    return VALUES_1(temp_1);
}

/* CHAR-LESSPW-FUNCTION */
Object char_lesspw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object code, temp, temp_1;

    x_note_fn_call(26,25);
    code = wide_character_1;
    if (IFIX(code) < (SI_Long)127L)
	temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ? 
		FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp = unicode_lowercase_if_uppercase(code);
	if (temp);
	else
	    temp = code;
    }
    code = wide_character_2;
    if (IFIX(code) < (SI_Long)127L)
	temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_1 = unicode_lowercase_if_uppercase(code);
	if (temp_1);
	else
	    temp_1 = code;
    }
    temp_1 = NUM_LT(temp,temp_1) ? T : Nil;
    return VALUES_1(temp_1);
}

/* LOWER-CASE-PW */
Object lower_case_pw(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,26);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)97L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)122L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHA-CHAR-PW-FUNCTION */
Object alpha_char_pw_function(wide_character)
    Object wide_character;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(26,27);
    gensymed_symbol = wide_character;
    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? (IFIX(gensymed_symbol) 
	    <= (SI_Long)122L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* ALPHANUMERICPW-FUNCTION */
Object alphanumericpw_function(wide_character)
    Object wide_character;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(26,28);
    gensymed_symbol = wide_character;
    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? (IFIX(gensymed_symbol) 
	    <= (SI_Long)122L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
		(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* DIGIT-CHAR-PW-FUNCTION */
Object digit_char_pw_function(wide_char_init,radix_init)
    Object wide_char_init, radix_init;
{
    Object temp;
    SI_Long wide_char, radix, char_code_1, arg, arg_1, arg_2;

    x_note_fn_call(26,29);
    wide_char = IFIX(wide_char_init);
    radix = IFIX(radix_init);
    char_code_1 = wide_char;
    arg = IFIX(Pct_0);
    arg_1 = char_code_1;
    arg_2 = radix < (SI_Long)10L ? IFIX(Pct_0) + (radix - (SI_Long)1L) : 
	    IFIX(Pct_9);
    if (arg <= arg_1 && arg_1 <= arg_2)
	temp = FIX(char_code_1 - IFIX(Pct_0));
    else if (radix <= (SI_Long)10L)
	temp = Nil;
    else {
	arg = IFIX(Pct_a);
	arg_1 = char_code_1;
	arg_2 = IFIX(Pct_a) + (radix - (SI_Long)10L - (SI_Long)1L);
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = FIX(char_code_1 - IFIX(FIXNUM_MINUS(Pct_a,
		    FIX((SI_Long)10L))));
	else {
	    arg = IFIX(ab_Pct_a);
	    arg_1 = char_code_1;
	    arg_2 = IFIX(ab_Pct_a) + (radix - (SI_Long)10L - (SI_Long)1L);
	    if (arg <= arg_1 && arg_1 <= arg_2)
		temp = FIX(char_code_1 - IFIX(FIXNUM_MINUS(ab_Pct_a,
			FIX((SI_Long)10L))));
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* DECIMAL-DIGIT-CHAR-PW-FUNCTION */
Object decimal_digit_char_pw_function(wide_character)
    Object wide_character;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(26,30);
    gensymed_symbol = IFIX(wide_character);
    return VALUES_1((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil);
}

/* HEXADECIMAL-DIGIT-CHAR-PW-FUNCTION */
Object hexadecimal_digit_char_pw_function(wide_character)
    Object wide_character;
{
    Object temp;

    x_note_fn_call(26,31);
    temp = digit_char_pw_function(wide_character,FIX((SI_Long)16L));
    return VALUES_1(temp);
}

static Object string_constant_9;   /* "UNSPECIFIED" */

/* STRINGW */
Object stringw(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(26,32);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	temp = thing;
    else if (FIXNUMP(thing))
	temp = make_stringw_function(FIX((SI_Long)1L),thing);
    else if (SYMBOLP(thing))
	temp = symbol_namew(thing);
    else if (STRINGP(thing))
	temp = copy_as_wide_string(thing);
    else
	temp = copy_as_wide_string(string_constant_9);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Stringw_should_not_cons_p, Qstringw_should_not_cons_p);

/* STRING-GREATERPW */
Object string_greaterpw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,33);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    temp = IFIX(result_1) > (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING>W */
Object string_gt_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,34);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    temp = IFIX(result_1) > (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING-LESSPW */
Object string_lesspw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,35);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    temp = IFIX(result_1) < (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING<W */
Object string_lt_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,36);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    temp = IFIX(result_1) < (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING-NOT-EQUALW */
Object string_not_equalw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,37);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,T,Nil);
    temp =  !(IFIX(result_1) == (SI_Long)0L) ? FIXNUM_SUB1(result_1) : Nil;
    return VALUES_1(temp);
}

/* STRING/=W */
Object string_sl_eq_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(26,38);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,T,T);
    temp =  !(IFIX(result_1) == (SI_Long)0L) ? FIXNUM_SUB1(result_1) : Nil;
    return VALUES_1(temp);
}

/* STRING-NOT-GREATERPW */
Object string_not_greaterpw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(26,39);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    if (IFIX(result_1) < (SI_Long)0L)
	temp = FIXNUM_SUB1(FIXNUM_ABS(result_1));
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = stringw(wide_string_1);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* STRING<=W */
Object string_lt_eq_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(26,40);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    if (IFIX(result_1) < (SI_Long)0L)
	temp = FIXNUM_SUB1(FIXNUM_ABS(result_1));
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = stringw(wide_string_1);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* STRING-NOT-LESSPW */
Object string_not_lesspw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(26,41);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    if (IFIX(result_1) > (SI_Long)0L)
	temp = FIXNUM_SUB1(result_1);
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = stringw(wide_string_1);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* STRING>=W */
Object string_gt_eq_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(26,42);
    result_1 = wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    if (IFIX(result_1) > (SI_Long)0L)
	temp = FIXNUM_SUB1(result_1);
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = stringw(wide_string_1);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* STRING-EQUALW */
Object string_equalw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;

    x_note_fn_call(26,43);
    temp = IFIX(wide_string_compare(wide_string_1,wide_string_2,T,Nil)) == 
	    (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* STRING=W */
Object string_eq_w(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;

    x_note_fn_call(26,44);
    temp = EQ(wide_string_1,wide_string_2) ? T : Nil;
    if (temp);
    else
	temp = IFIX(wide_string_compare(wide_string_1,wide_string_2,T,T)) 
		== (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* WIDE-STRING-COMPARE */
Object wide_string_compare(wide_string_1,wide_string_2,
	    just_check_equality_qm,consider_case_qm)
    Object wide_string_1, wide_string_2, just_check_equality_qm;
    Object consider_case_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, temp_1, downcase_code_qm;
    SI_Long length_1, length_1_1, length_2, gensymed_symbol_2, index_1, code_1;
    SI_Long code_2, code;
    char temp;

    x_note_fn_call(26,45);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(wide_string_1) != (SI_Long)0L);
    else if (FIXNUMP(wide_string_1))
	wide_string_1 = make_stringw_function(FIX((SI_Long)1L),wide_string_1);
    else if (SYMBOLP(wide_string_1))
	wide_string_1 = symbol_namew(wide_string_1);
    else if (STRINGP(wide_string_1))
	wide_string_1 = copy_as_wide_string(wide_string_1);
    else
	wide_string_1 = copy_as_wide_string(string_constant_9);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(wide_string_2) != (SI_Long)0L);
    else if (FIXNUMP(wide_string_2))
	wide_string_2 = make_stringw_function(FIX((SI_Long)1L),wide_string_2);
    else if (SYMBOLP(wide_string_2))
	wide_string_2 = symbol_namew(wide_string_2);
    else if (STRINGP(wide_string_2))
	wide_string_2 = copy_as_wide_string(wide_string_2);
    else
	wide_string_2 = copy_as_wide_string(string_constant_9);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_1));
    length_1_1 = UBYTE_16_ISAREF_1(wide_string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_2));
    length_2 = UBYTE_16_ISAREF_1(wide_string_2,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string_2,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    if (just_check_equality_qm && consider_case_qm) {
	temp =  !(length_1_1 == length_2);
	if (temp);
	else {
	    gensymed_symbol = wide_string_1;
	    gensymed_symbol_1 = wide_string_2;
	    gensymed_symbol_2 = length_1_1;
	    temp =  
		    !(memcmp(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_1),
		    gensymed_symbol_2 << (SI_Long)1L) == (SI_Long)0L);
	}
	if (temp)
	    return VALUES_1(FIX(MIN(length_1_1,length_2) + (SI_Long)1L));
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
    if (consider_case_qm) {
	index_1 = (SI_Long)0L;
	code_1 = (SI_Long)0L;
	code_2 = (SI_Long)0L;
      next_loop:
	if (index_1 >= length_1_1) {
	    temp_1 = index_1 < length_2 ? FIX( - (index_1 + (SI_Long)1L)) :
		     FIX((SI_Long)0L);
	    goto end_1;
	}
	else if (index_1 >= length_2) {
	    temp_1 = FIX(index_1 + (SI_Long)1L);
	    goto end_1;
	}
	code_1 = UBYTE_16_ISAREF_1(wide_string_1,index_1);
	code_2 = UBYTE_16_ISAREF_1(wide_string_2,index_1);
	index_1 = index_1 + (SI_Long)1L;
	if ( !(code_1 == code_2)) {
	    temp_1 = just_check_equality_qm || code_1 > code_2 ? 
		    FIX(index_1) : FIX( - index_1);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
    }
    else {
	index_1 = (SI_Long)0L;
	code_1 = (SI_Long)0L;
	code_2 = (SI_Long)0L;
      next_loop_1:
	if (index_1 >= length_1_1) {
	    temp_1 = index_1 < length_2 ? FIX( - (index_1 + (SI_Long)1L)) :
		     FIX((SI_Long)0L);
	    goto end_2;
	}
	else if (index_1 >= length_2) {
	    temp_1 = FIX(index_1 + (SI_Long)1L);
	    goto end_2;
	}
	code_1 = UBYTE_16_ISAREF_1(wide_string_1,index_1);
	code_2 = UBYTE_16_ISAREF_1(wide_string_2,index_1);
	code = code_1;
	if ((SI_Long)0L <= code && code <= (SI_Long)127L)
	    downcase_code_qm = (SI_Long)65L <= code && code <= 
		    (SI_Long)90L ? FIX(code - (SI_Long)-32L) : Nil;
	else if ((SI_Long)128L <= code && code <= (SI_Long)255L) {
	    if ((SI_Long)192L <= code && code <= (SI_Long)214L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)216L <= code && code <= (SI_Long)222L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if (code == (SI_Long)376L)
		downcase_code_qm = FIX((SI_Long)255L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)256L <= code && code <= (SI_Long)383L) {
	    if ((SI_Long)256L <= code && code <= (SI_Long)311L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)313L <= code && code <= (SI_Long)328L && 
		    ((SI_Long)1L & code) == (SI_Long)1L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)330L <= code && code <= (SI_Long)375L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)377L <= code && code <= (SI_Long)382L && 
		    ((SI_Long)1L & code) == (SI_Long)1L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)384L <= code && code <= (SI_Long)879L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)880L <= code && code <= (SI_Long)975L) {
	    if ((SI_Long)913L <= code && code <= (SI_Long)929L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)931L <= code && code <= (SI_Long)937L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)976L <= code && code <= (SI_Long)1023L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)1024L <= code && code <= (SI_Long)1151L) {
	    if ((SI_Long)1040L <= code && code <= (SI_Long)1071L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)1025L <= code && code <= (SI_Long)1039L)
		downcase_code_qm = FIX(code - (SI_Long)-80L);
	    else if ((SI_Long)1120L <= code && code <= (SI_Long)1151L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)1152L <= code && code <= (SI_Long)1279L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)1280L <= code && code <= (SI_Long)1423L)
	    downcase_code_qm = (SI_Long)1329L <= code && code <= 
		    (SI_Long)1366L ? FIX(code - (SI_Long)-48L) : Nil;
	else if ((SI_Long)1424L <= code && code <= (SI_Long)3839L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)4256L <= code && code <= (SI_Long)4351L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)4352L <= code && code <= (SI_Long)4607L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)7680L <= code && code <= (SI_Long)7935L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)7936L <= code && code <= (SI_Long)8191L)
	    downcase_code_qm = Qnil;
	else
	    downcase_code_qm = Qnil;
	if (downcase_code_qm)
	    code_1 = IFIX(downcase_code_qm);
	code = code_2;
	if ((SI_Long)0L <= code && code <= (SI_Long)127L)
	    downcase_code_qm = (SI_Long)65L <= code && code <= 
		    (SI_Long)90L ? FIX(code - (SI_Long)-32L) : Nil;
	else if ((SI_Long)128L <= code && code <= (SI_Long)255L) {
	    if ((SI_Long)192L <= code && code <= (SI_Long)214L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)216L <= code && code <= (SI_Long)222L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if (code == (SI_Long)376L)
		downcase_code_qm = FIX((SI_Long)255L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)256L <= code && code <= (SI_Long)383L) {
	    if ((SI_Long)256L <= code && code <= (SI_Long)311L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)313L <= code && code <= (SI_Long)328L && 
		    ((SI_Long)1L & code) == (SI_Long)1L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)330L <= code && code <= (SI_Long)375L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else if ((SI_Long)377L <= code && code <= (SI_Long)382L && 
		    ((SI_Long)1L & code) == (SI_Long)1L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)384L <= code && code <= (SI_Long)879L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)880L <= code && code <= (SI_Long)975L) {
	    if ((SI_Long)913L <= code && code <= (SI_Long)929L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)931L <= code && code <= (SI_Long)937L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)976L <= code && code <= (SI_Long)1023L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)1024L <= code && code <= (SI_Long)1151L) {
	    if ((SI_Long)1040L <= code && code <= (SI_Long)1071L)
		downcase_code_qm = FIX(code - (SI_Long)-32L);
	    else if ((SI_Long)1025L <= code && code <= (SI_Long)1039L)
		downcase_code_qm = FIX(code - (SI_Long)-80L);
	    else if ((SI_Long)1120L <= code && code <= (SI_Long)1151L && 
		    ((SI_Long)1L & code) == (SI_Long)0L)
		downcase_code_qm = FIX(code + (SI_Long)1L);
	    else
		downcase_code_qm = Qnil;
	}
	else if ((SI_Long)1152L <= code && code <= (SI_Long)1279L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)1280L <= code && code <= (SI_Long)1423L)
	    downcase_code_qm = (SI_Long)1329L <= code && code <= 
		    (SI_Long)1366L ? FIX(code - (SI_Long)-48L) : Nil;
	else if ((SI_Long)1424L <= code && code <= (SI_Long)3839L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)4256L <= code && code <= (SI_Long)4351L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)4352L <= code && code <= (SI_Long)4607L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)7680L <= code && code <= (SI_Long)7935L)
	    downcase_code_qm = Qnil;
	else if ((SI_Long)7936L <= code && code <= (SI_Long)8191L)
	    downcase_code_qm = Qnil;
	else
	    downcase_code_qm = Qnil;
	if (downcase_code_qm)
	    code_2 = IFIX(downcase_code_qm);
	index_1 = index_1 + (SI_Long)1L;
	if ( !(code_1 == code_2)) {
	    temp_1 = just_check_equality_qm || code_1 > code_2 ? 
		    FIX(index_1) : FIX( - index_1);
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp_1 = Qnil;
      end_2:;
    }
    return VALUES_1(temp_1);
}

/* COPY-WIDE-STRING-GIVEN-LENGTH */
Object copy_wide_string_given_length(wide_string_to_copy,length_1)
    Object wide_string_to_copy, length_1;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,46);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    gensymed_symbol = wide_string_to_copy;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = new_wide_string;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = IFIX(length_1);
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(new_wide_string);
}

/* COPY-WIDE-STRING */
Object copy_wide_string(wide_string_to_copy)
    Object wide_string_to_copy;
{
    Object wide_string_bv16, new_wide_string, binary_p, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, bv16_length, aref_arg_2, aref_new_value, length_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,47);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_to_copy));
    length_1 = UBYTE_16_ISAREF_1(wide_string_to_copy,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_to_copy,
	    length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    wide_string_bv16 = allocate_byte_vector_16(FIX(length_1 + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = length_1 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | length_1 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(wide_string_to_copy) != (SI_Long)0L) {
	length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_to_copy));
	binary_p = (SI_Long)1L == UBYTE_16_ISAREF_1(wide_string_to_copy,
		UBYTE_16_ISAREF_1(wide_string_to_copy,length_2 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_to_copy,
		length_2 - (SI_Long)1L) & (SI_Long)8191L) << 
		(SI_Long)16L)) ? T : Nil;
    }
    else
	binary_p = Nil;
    gensymed_symbol = wide_string_to_copy;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = new_wide_string;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = length_1;
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    if (binary_p) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_wide_string));
	length_1 = UBYTE_16_ISAREF_1(new_wide_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(new_wide_string,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	UBYTE_16_ISASET_1(new_wide_string,length_1,(SI_Long)1L);
    }
    return VALUES_1(new_wide_string);
}

/* COPY-CONSTANT-WIDE-STRING-GIVEN-LENGTH */
Object copy_constant_wide_string_given_length(wide_string_to_copy,length_1)
    Object wide_string_to_copy, length_1;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,48);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    gensymed_symbol = wide_string_to_copy;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = new_wide_string;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = IFIX(length_1);
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(new_wide_string);
}

/* COPY-AS-WIDE-STRING */
Object copy_as_wide_string(wide_string_or_lisp_string)
    Object wide_string_or_lisp_string;
{
    Object string_length, wide_string_bv16, result_1, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(26,49);
    if (STRINGP(wide_string_or_lisp_string)) {
	string_length = length(wide_string_or_lisp_string);
	wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(string_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(string_length) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(string_length) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(string_length),(SI_Long)0L);
	result_1 = wide_string_bv16;
	copy_portion_of_string_into_text_string(wide_string_or_lisp_string,
		FIX((SI_Long)0L),string_length,result_1,FIX((SI_Long)0L));
	temp = result_1;
    }
    else
	temp = copy_wide_string(wide_string_or_lisp_string);
    return VALUES_1(temp);
}

/* COPY-PARTIAL-WIDE-STRING */
Object copy_partial_wide_string(wide_string_or_lisp_string,part_length)
    Object wide_string_or_lisp_string, part_length;
{
    Object wide_string_bv16, result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(26,50);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(part_length) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(part_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(part_length) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(part_length),(SI_Long)0L);
    result_1 = wide_string_bv16;
    copy_portion_of_string_into_text_string(wide_string_or_lisp_string,
	    FIX((SI_Long)0L),part_length,result_1,FIX((SI_Long)0L));
    return VALUES_1(result_1);
}

/* WIDE-STRING-SUBSTRING */
Object wide_string_substring(wide_string,start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object start, end_1, wide_string_bv16, result_1, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,51);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end_1 = end_qm;
    if (end_1);
    else {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	end_1 = FIX(UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
		+ ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) 
		& (SI_Long)8191L) << (SI_Long)16L));
    }
    part_length = IFIX(FIXNUM_MINUS(end_1,start));
    wide_string_bv16 = allocate_byte_vector_16(FIX(part_length + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = part_length & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | part_length >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
    result_1 = wide_string_bv16;
    gensymed_symbol = wide_string;
    gensymed_symbol_1 = IFIX(start);
    gensymed_symbol_2 = result_1;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = part_length;
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(result_1);
}

/* EQUALW */
Object equalw(a,b)
    Object a, b;
{
    Object temp;

    x_note_fn_call(26,52);
    if (CONSP(a) && CONSP(b))
	temp = equalw(CAR(a),CAR(b)) ? equalw(CDR(a),CDR(b)) : Qnil;
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(a) != (SI_Long)0L && 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(b) != (SI_Long)0L)
	temp = string_eq_w(a,b);
    else
	temp = EQUAL(a,b) ? T : Nil;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-MEMBER */
Object wide_character_member(item,list_1)
    Object item, list_1;
{
    Object items, temp;

    x_note_fn_call(26,53);
    items = list_1;
  next_loop:
    if ( !TRUEP(items))
	goto end_loop;
    temp = FIRST(items);
    if (EQL(item,temp)) {
	temp = items;
	goto end_1;
    }
    items = M_CDR(items);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-ASSOC */
Object wide_character_assoc(item,a_list)
    Object item, a_list;
{
    Object sublist, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(26,54);
    sublist = Nil;
    ab_loop_list_ = a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sublist = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (sublist) {
	temp = CAR(sublist);
	temp_1 = EQL(item,temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = sublist;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-RASSOC */
Object wide_character_rassoc(item,a_list)
    Object item, a_list;
{
    Object sublist, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(26,55);
    sublist = Nil;
    ab_loop_list_ = a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sublist = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (sublist) {
	temp = CDR(sublist);
	temp_1 = EQL(item,temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = sublist;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* POSITION-IN-WIDE-STRING */
Object position_in_wide_string(wide_character_init,wide_string)
    Object wide_character_init, wide_string;
{
    Object temp;
    SI_Long wide_character, i, length_1, ab_loop_bind_;

    x_note_fn_call(26,56);
    wide_character = IFIX(wide_character_init);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(wide_string,i) == wide_character) {
	temp = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* REMOVE-CHARACTER-FROM-WIDE-STRING */
Object remove_character_from_wide_string(wide_character_init,wide_string)
    Object wide_character_init, wide_string;
{
    Object count_1, wide_string_bv16, new_string, j;
    SI_Long wide_character, i, length_1, ab_loop_bind_, ab_loopvar_;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2, bv16_length, temp;
    SI_Long aref_new_value;

    x_note_fn_call(26,57);
    wide_character = IFIX(wide_character_init);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(wide_string,i) == wide_character)
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    count_1 = FIX(ab_loopvar_);
    goto end_1;
    count_1 = Qnil;
  end_1:;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    gensymed_symbol = UBYTE_16_ISAREF_1(wide_string,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    gensymed_symbol_1 = IFIX(count_1);
    length_2 = gensymed_symbol - gensymed_symbol_1;
    wide_string_bv16 = allocate_byte_vector_16(FIX(length_2 + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    temp = bv16_length - (SI_Long)2L;
    aref_new_value = length_2 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    temp = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | length_2 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,length_2,(SI_Long)0L);
    new_string = wide_string_bv16;
    j = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    if ( !(UBYTE_16_ISAREF_1(wide_string,i) == wide_character)) {
	temp = UBYTE_16_ISAREF_1(wide_string,i);
	UBYTE_16_ISASET_1(new_string,IFIX(j),temp);
	j = FIXNUM_ADD1(j);
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(new_string);
}

/* SEARCH-WIDE-STRING */
Object search_wide_string varargs_1(int, n)
{
    Object pattern, wide_string, start_qm, end_qm;
    Object skip_quoted_portions_qm, patlen, end_1, escape, quoted, temp, ch;
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long i, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_3, temp_1;
    SI_Long gensymed_symbol_4;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,58);
    INIT_ARGS_nonrelocating();
    pattern = REQUIRED_ARG_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    start_qm = REQUIRED_ARG_nonrelocating();
    end_qm = REQUIRED_ARG_nonrelocating();
    skip_quoted_portions_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    patlen = lengthw(pattern);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = lengthw(wide_string);
    escape = Nil;
    quoted = Nil;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    ab_loop_bind_ = IFIX(FIXNUM_MINUS(end_1,patlen));
    ch = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    ch = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    if (escape)
	escape = Nil;
    else if (skip_quoted_portions_qm && IFIX(ch) == (SI_Long)64L)
	escape = T;
    else if (skip_quoted_portions_qm && IFIX(ch) == (SI_Long)34L)
	quoted =  !TRUEP(quoted) ? T : Nil;
    else if (quoted);
    else {
	gensymed_symbol = pattern;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = wide_string;
	gensymed_symbol_3 = i;
	temp_1 = IFIX(end_1) - i;
	gensymed_symbol_4 = MIN(IFIX(patlen),temp_1);
	if ((SI_Long)0L == 
		INLINE_COMPARE_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4))
	    return VALUES_1(FIX(i));
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STRING-UPCASEW */
Object string_upcasew(wide_string)
    Object wide_string;
{
    Object new_string, aref_new_value, temp;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(26,59);
    new_string = copy_wide_string(wide_string);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    code = wide_character;
    if (code < (SI_Long)127L)
	aref_new_value = (SI_Long)97L <= code && code <= (SI_Long)122L ? 
		FIX(code + (SI_Long)-32L) : FIX(code);
    else {
	aref_new_value = unicode_uppercase_if_lowercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(new_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_string;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* STRING-DOWNCASEW */
Object string_downcasew(wide_string)
    Object wide_string;
{
    Object new_string, aref_new_value, temp;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(26,60);
    new_string = copy_wide_string(wide_string);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    code = wide_character;
    if (code < (SI_Long)127L)
	aref_new_value = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		FIX(code + (SI_Long)32L) : FIX(code);
    else {
	aref_new_value = unicode_lowercase_if_uppercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(new_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_string;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* NSTRING-UPCASEW */
Object nstring_upcasew(wide_string)
    Object wide_string;
{
    Object aref_new_value;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(26,61);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    code = wide_character;
    if (code < (SI_Long)127L)
	aref_new_value = (SI_Long)97L <= code && code <= (SI_Long)122L ? 
		FIX(code + (SI_Long)-32L) : FIX(code);
    else {
	aref_new_value = unicode_uppercase_if_lowercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(wide_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(wide_string);
}

/* NSTRING-DOWNCASEW */
Object nstring_downcasew(wide_string)
    Object wide_string;
{
    Object aref_new_value;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(26,62);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    code = wide_character;
    if (code < (SI_Long)127L)
	aref_new_value = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		FIX(code + (SI_Long)32L) : FIX(code);
    else {
	aref_new_value = unicode_lowercase_if_uppercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(wide_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(wide_string);
}

/* SIMPLE-SYMBOL-WIDE-CHARACTER-P */
Object simple_symbol_wide_character_p(wide_character)
    Object wide_character;
{
    Object code, temp;

    x_note_fn_call(26,63);
    code = wide_character;
    temp = IFIX(code) <= (SI_Long)127L ? 
	    simple_symbol_character_p(wide_character) : Nil;
    return VALUES_1(temp);
}

/* SIMPLE-PATHNAME-WIDE-CHARACTER-P */
Object simple_pathname_wide_character_p(wide_character)
    Object wide_character;
{
    Object code, character_qm, temp;

    x_note_fn_call(26,64);
    code = wide_character;
    character_qm = IFIX(code) <= (SI_Long)127L ? CODE_CHAR(code) : Nil;
    temp = character_qm ? simple_pathname_character_p(character_qm) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Outputting_to_wide_string, Qoutputting_to_wide_string);

DEFINE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);

DEFINE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);

DEFINE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);

DEFINE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);

Object Extend_current_text_string_error_message = UNBOUND;

static Object Qhandle_extend_current_text_string_error;  /* handle-extend-current-text-string-error */

/* EXTEND-CURRENT-WIDE-STRING */
Object extend_current_wide_string(minimum_new_total_length)
    Object minimum_new_total_length;
{
    Object new_string_length, wide_string_bv16, new_wide_string, aref_arg_1;
    Object aref_arg_2_1, temp, temp_2, new_total_length, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, temp_1, arg, arg_1, arg_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp_3;

    x_note_fn_call(26,65);
    if (FIXNUM_GT(minimum_new_total_length,Maximum_wide_string_length)) {
	if (fboundp(Qhandle_extend_current_text_string_error))
	    handle_extend_current_text_string_error();
	else
	    error((SI_Long)1L,"Trying to write a string longer than 2MB!");
    }
    if (CONSP(Current_wide_string_list)) {
	new_string_length = FIXNUM_MAX(minimum_new_total_length,
		Wide_string_list_maximum_length);
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(new_string_length) + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(new_string_length) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(new_string_length) >>  -  
		- (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(new_string_length),
		(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	aref_arg_1 = Current_wide_string;
	aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(aref_arg_1));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(aref_arg_1,IFIX(aref_arg_2_1),(SI_Long)0L);
	nconc2(Current_wide_string_list,gensym_cons_1(new_wide_string,Nil));
	Fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	Current_wide_string = new_wide_string;
	Total_length_of_current_wide_string = new_string_length;
    }
    else {
	temp = Maximum_wide_string_length;
	temp_1 = IFIX(Total_length_of_current_wide_string) * (SI_Long)3L / 
		(SI_Long)2L;
	temp_2 = FIX(temp_1);
	temp_2 = FIXNUM_MAX(temp_2,minimum_new_total_length);
	new_total_length = FIXNUM_MIN(temp,temp_2);
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(new_total_length) + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(new_total_length) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(new_total_length) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(new_total_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	if (EQ(Current_wide_string,new_wide_string)) {
	    if ((SI_Long)0L == IFIX(Fill_pointer_for_current_wide_string))
		temp_3 = TRUEP(T);
	    else {
		temp_3 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
			IFIX(Fill_pointer_for_current_wide_string) : 
			TRUEP(Qnil);
		if (temp_3);
		else {
		    arg = (SI_Long)0L;
		    arg_1 = (SI_Long)0L;
		    arg_2 = (SI_Long)0L + 
			    (IFIX(Fill_pointer_for_current_wide_string) - 
			    (SI_Long)0L);
		    temp_3 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		}
		if (temp_3) {
		    copy_byte_vector_16_portion_carefully(Current_wide_string,
			    FIX((SI_Long)0L),new_wide_string,
			    FIX((SI_Long)0L),
			    FIX(IFIX(Fill_pointer_for_current_wide_string) 
			    - (SI_Long)0L));
		    temp_3 = TRUEP(T);
		}
		else
		    temp_3 = TRUEP(Qnil);
	    }
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3);
	else {
	    gensymed_symbol = Current_wide_string;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = new_wide_string;
	    gensymed_symbol_3 = (SI_Long)0L;
	    gensymed_symbol_4 = IFIX(Fill_pointer_for_current_wide_string) 
		    - (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		    gensymed_symbol_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	reclaim_wide_string(Current_wide_string);
	Current_wide_string = new_wide_string;
	Total_length_of_current_wide_string = new_total_length;
    }
    return VALUES_1(Nil);
}

/* TWRITING-ACCUMULATED-LENGTH */
Object twriting_accumulated_length()
{
    Object string_cons, next_cons, wide_string_bv16, temp;
    SI_Long ab_loopvar_, length_1, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,66);
    if (CONSP(Current_wide_string_list)) {
	string_cons = Current_wide_string_list;
	next_cons = Nil;
	ab_loopvar_ = (SI_Long)0L;
      next_loop:
	next_cons = M_CDR(string_cons);
	if ( !TRUEP(next_cons))
	    goto end_loop;
	wide_string_bv16 = M_CAR(string_cons);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	gensymed_symbol = UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	gensymed_symbol_1 = ab_loopvar_;
	ab_loopvar_ = gensymed_symbol + gensymed_symbol_1;
	string_cons = next_cons;
	goto next_loop;
      end_loop:
	gensymed_symbol = ab_loopvar_;
	goto end_1;
	gensymed_symbol = IFIX(Qnil);
      end_1:;
	gensymed_symbol_1 = IFIX(Fill_pointer_for_current_wide_string);
	temp = FIX(gensymed_symbol + gensymed_symbol_1);
    }
    else
	temp = Fill_pointer_for_current_wide_string;
    return VALUES_1(temp);
}

/* COPY-CURRENT-WIDE-STRING */
Object copy_current_wide_string()
{
    Object new_wide_string, gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(26,67);
    new_wide_string = 
	    make_stringw_function(Fill_pointer_for_current_wide_string,Nil);
    if (EQ(Current_wide_string,new_wide_string)) {
	if ((SI_Long)0L == IFIX(Fill_pointer_for_current_wide_string))
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
		    IFIX(Fill_pointer_for_current_wide_string) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = (SI_Long)0L;
		arg_1 = (SI_Long)0L;
		arg_2 = (SI_Long)0L + 
			(IFIX(Fill_pointer_for_current_wide_string) - 
			(SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(Current_wide_string,
			FIX((SI_Long)0L),new_wide_string,FIX((SI_Long)0L),
			FIX(IFIX(Fill_pointer_for_current_wide_string) - 
			(SI_Long)0L));
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	gensymed_symbol = Current_wide_string;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = new_wide_string;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = IFIX(Fill_pointer_for_current_wide_string) - 
		(SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    return VALUES_1(new_wide_string);
}

/* COPY-OUT-CURRENT-WIDE-STRING */
Object copy_out_current_wide_string()
{
    Object temp;

    x_note_fn_call(26,68);
    temp = copy_current_wide_string();
    reclaim_wide_string(Current_wide_string);
    return VALUES_1(temp);
}

Object Maximum_suggested_length_for_wide_strings = UNBOUND;

static Object Qdo_not_use;         /* do-not-use */

/* TFORMAT-WIDE-STRING */
Object tformat_wide_string varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,69);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
		      arg8,arg9);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Kall;                /* :all */

static Object Knone;               /* :none */

static Object Kfirst_of_each_word;  /* :first-of-each-word */

/* COPY-WIDE-STRING-WITH-CASE-CONVERSION */
Object copy_wide_string_with_case_conversion(wide_string,
	    which_characters_to_upcase_qm)
    Object wide_string, which_characters_to_upcase_qm;
{
    Object new_wide_string, upcase_next_character_qm, wide_character, temp;
    Object aref_new_value, code;
    SI_Long length_1, i, ab_loop_bind_;
    char upcase_after_ordinary_character_qm;

    x_note_fn_call(26,70);
    new_wide_string = copy_as_wide_string(wide_string);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_wide_string));
    length_1 = UBYTE_16_ISAREF_1(new_wide_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(new_wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    upcase_after_ordinary_character_qm = EQ(which_characters_to_upcase_qm,
	    Kall);
    upcase_next_character_qm =  !EQ(which_characters_to_upcase_qm,Knone) ? 
	    T : Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
    wide_character = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = FIX(UBYTE_16_ISAREF_1(new_wide_string,i));
    if (word_separator_p(wide_character)) {
	if (which_characters_to_upcase_qm) {
	    temp = EQ(which_characters_to_upcase_qm,Kfirst_of_each_word) ? 
		    T : Nil;
	    if (temp);
	    else
		temp = EQ(which_characters_to_upcase_qm,Kall) ? T : Nil;
	    upcase_next_character_qm = temp;
	}
	else
	    upcase_next_character_qm = Nil;
	aref_new_value = wide_character;
    }
    else if (upcase_next_character_qm) {
	upcase_next_character_qm = upcase_after_ordinary_character_qm ? T :
		 Nil;
	code = wide_character;
	if (IFIX(code) < (SI_Long)127L)
	    aref_new_value = (SI_Long)97L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)122L ? FIX(IFIX(code) + (SI_Long)-32L) : code;
	else {
	    aref_new_value = unicode_uppercase_if_lowercase(code);
	    if (aref_new_value);
	    else
		aref_new_value = code;
	}
    }
    else {
	upcase_next_character_qm = upcase_after_ordinary_character_qm ? T :
		 Nil;
	code = wide_character;
	if (IFIX(code) < (SI_Long)127L)
	    aref_new_value = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    aref_new_value = unicode_lowercase_if_uppercase(code);
	    if (aref_new_value);
	    else
		aref_new_value = code;
	}
    }
    UBYTE_16_ISASET_1(new_wide_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(new_wide_string);
    return VALUES_1(Qnil);
}

/* COPY-SYMBOL-NAME-AS-WIDE-STRING */
Object copy_symbol_name_as_wide_string varargs_1(int, n)
{
    Object symbol, which_characters_not_to_downcase_qm;
    Object substitute_spaces_for_hyphens_qm, character_to_add_at_end_qm;
    Object acronym_list_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,71);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    which_characters_not_to_downcase_qm = REQUIRED_ARG_nonrelocating();
    substitute_spaces_for_hyphens_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_to_add_at_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    acronym_list_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      twrite_symbol_name(symbol,
		      which_characters_not_to_downcase_qm,
		      substitute_spaces_for_hyphens_qm,
		      character_to_add_at_end_qm,acronym_list_qm);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TWRITE-SYMBOL-NAME */
Object twrite_symbol_name(symbol,which_characters_not_to_downcase_qm,
	    substitute_spaces_for_hyphens_qm,character_to_add_at_end_qm,
	    acronym_list_qm)
    Object symbol, which_characters_not_to_downcase_qm;
    Object substitute_spaces_for_hyphens_qm, character_to_add_at_end_qm;
    Object acronym_list_qm;
{
    x_note_fn_call(26,72);
    return twrite_string_as_attribute_name(get_or_make_symbol_name_wide_string(symbol),
	    which_characters_not_to_downcase_qm,
	    substitute_spaces_for_hyphens_qm,character_to_add_at_end_qm,
	    acronym_list_qm);
}

static Object Kfirst;              /* :first */

/* TWRITE-STRING-AS-ATTRIBUTE-NAME */
Object twrite_string_as_attribute_name(string_1,
	    which_characters_not_to_downcase_qm,
	    substitute_spaces_for_hyphens_qm,character_to_add_at_end_qm,
	    acronym_list_qm)
    Object string_1, which_characters_not_to_downcase_qm;
    Object substitute_spaces_for_hyphens_qm, character_to_add_at_end_qm;
    Object acronym_list_qm;
{
    Object new_wide_string, indices_of_word_delimiters, i;
    Object do_not_downcase_next_character_qm, character_1, temp;
    Object aref_new_value, code, delimiter_index, ab_loop_list_, start_index;
    Object word_length, acronym, ab_loop_list__1, temp_1;
    SI_Long length_1, string_length, word_i, acronym_i, ab_loop_bind_;
    SI_Long wide_character, code_1;
    char do_not_downcase_after_ordinary_character_qm, temp_2;

    x_note_fn_call(26,73);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    string_length = UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    new_wide_string = make_stringw_function(character_to_add_at_end_qm ? 
	    FIX(string_length + (SI_Long)1L) : FIX(string_length),Nil);
    indices_of_word_delimiters = Nil;
    do_not_downcase_after_ordinary_character_qm = 
	    EQ(which_characters_not_to_downcase_qm,Kall);
    i = FIX((SI_Long)0L);
    do_not_downcase_next_character_qm = which_characters_not_to_downcase_qm;
    character_1 = Nil;
  next_loop:
    if (IFIX(i) >= string_length)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(i)));
    temp = character_1;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	if (IFIX(character_1) == (SI_Long)32L) {
	    if (acronym_list_qm)
		indices_of_word_delimiters = gensym_cons_1(i,
			indices_of_word_delimiters);
	    do_not_downcase_next_character_qm = 
		    which_characters_not_to_downcase_qm ? ( 
		    !EQ(which_characters_not_to_downcase_qm,Kfirst) ? T : 
		    Nil) : Nil;
	    aref_new_value = character_1;
	}
	else if (do_not_downcase_next_character_qm) {
	    do_not_downcase_next_character_qm = 
		    do_not_downcase_after_ordinary_character_qm ? T : Nil;
	    aref_new_value = character_1;
	}
	else {
	    do_not_downcase_next_character_qm = 
		    do_not_downcase_after_ordinary_character_qm ? T : Nil;
	    code = character_1;
	    if (IFIX(code) < (SI_Long)127L)
		aref_new_value = (SI_Long)65L <= IFIX(code) && IFIX(code) 
			<= (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : 
			code;
	    else {
		aref_new_value = unicode_lowercase_if_uppercase(code);
		if (aref_new_value);
		else
		    aref_new_value = code;
	    }
	}
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 45:
	    if (acronym_list_qm)
		indices_of_word_delimiters = gensym_cons_1(i,
			indices_of_word_delimiters);
	    do_not_downcase_next_character_qm = 
		    which_characters_not_to_downcase_qm ? ( 
		    !EQ(which_characters_not_to_downcase_qm,Kfirst) ? T : 
		    Nil) : Nil;
	    aref_new_value = substitute_spaces_for_hyphens_qm ? 
		    FIX((SI_Long)32L) : character_1;
	    break;
	  default:
	    if (IFIX(character_1) == (SI_Long)32L) {
		if (acronym_list_qm)
		    indices_of_word_delimiters = gensym_cons_1(i,
			    indices_of_word_delimiters);
		do_not_downcase_next_character_qm = 
			which_characters_not_to_downcase_qm ? ( 
			!EQ(which_characters_not_to_downcase_qm,Kfirst) ? 
			T : Nil) : Nil;
		aref_new_value = character_1;
	    }
	    else if (do_not_downcase_next_character_qm) {
		do_not_downcase_next_character_qm = 
			do_not_downcase_after_ordinary_character_qm ? T : Nil;
		aref_new_value = character_1;
	    }
	    else {
		do_not_downcase_next_character_qm = 
			do_not_downcase_after_ordinary_character_qm ? T : Nil;
		code = character_1;
		if (IFIX(code) < (SI_Long)127L)
		    aref_new_value = (SI_Long)65L <= IFIX(code) && 
			    IFIX(code) <= (SI_Long)90L ? FIX(IFIX(code) + 
			    (SI_Long)32L) : code;
		else {
		    aref_new_value = unicode_lowercase_if_uppercase(code);
		    if (aref_new_value);
		    else
			aref_new_value = code;
		}
	    }
	    break;
	}
    UBYTE_16_ISASET_1(new_wide_string,IFIX(i),IFIX(aref_new_value));
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    if (character_to_add_at_end_qm)
	UBYTE_16_ISASET_1(new_wide_string,string_length,
		IFIX(character_to_add_at_end_qm));
    if (acronym_list_qm) {
	indices_of_word_delimiters = gensym_cons_1(FIX(string_length),
		indices_of_word_delimiters);
	indices_of_word_delimiters = nreverse(indices_of_word_delimiters);
	delimiter_index = Nil;
	ab_loop_list_ = indices_of_word_delimiters;
	start_index = FIX((SI_Long)0L);
	word_length = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	delimiter_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	word_length = FIXNUM_MINUS(delimiter_index,start_index);
	acronym = Nil;
	ab_loop_list__1 = acronym_list_qm;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	acronym = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(acronym));
	if (FIXNUM_EQ(FIX(UBYTE_16_ISAREF_1(acronym,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(acronym,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    word_length)) {
	    word_i = IFIX(start_index);
	    acronym_i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(word_length);
	  next_loop_3:
	    if (acronym_i >= ab_loop_bind_)
		goto end_loop_3;
	    wide_character = UBYTE_16_ISAREF_1(new_wide_string,word_i);
	    code_1 = wide_character;
	    if (code_1 < (SI_Long)127L)
		temp = (SI_Long)97L <= code_1 && code_1 <= (SI_Long)122L ? 
			FIX(code_1 + (SI_Long)-32L) : FIX(code_1);
	    else {
		temp = unicode_uppercase_if_lowercase(FIX(code_1));
		if (temp);
		else
		    temp = FIX(code_1);
	    }
	    wide_character = UBYTE_16_ISAREF_1(acronym,acronym_i);
	    code_1 = wide_character;
	    if (code_1 < (SI_Long)127L)
		temp_1 = (SI_Long)97L <= code_1 && code_1 <= (SI_Long)122L 
			? FIX(code_1 + (SI_Long)-32L) : FIX(code_1);
	    else {
		temp_1 = unicode_uppercase_if_lowercase(FIX(code_1));
		if (temp_1);
		else
		    temp_1 = FIX(code_1);
	    }
	    if ( !EQL(temp,temp_1)) {
		temp_2 = TRUEP(Nil);
		goto end_1;
	    }
	    word_i = word_i + (SI_Long)1L;
	    acronym_i = acronym_i + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp_2 = TRUEP(T);
	    goto end_1;
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    word_i = IFIX(start_index);
	    ab_loop_bind_ = IFIX(delimiter_index);
	  next_loop_4:
	    if (word_i >= ab_loop_bind_)
		goto end_loop_4;
	    wide_character = UBYTE_16_ISAREF_1(new_wide_string,word_i);
	    code_1 = wide_character;
	    if (code_1 < (SI_Long)127L)
		aref_new_value = (SI_Long)97L <= code_1 && code_1 <= 
			(SI_Long)122L ? FIX(code_1 + (SI_Long)-32L) : 
			FIX(code_1);
	    else {
		aref_new_value = unicode_uppercase_if_lowercase(FIX(code_1));
		if (aref_new_value);
		else
		    aref_new_value = FIX(code_1);
	    }
	    UBYTE_16_ISASET_1(new_wide_string,word_i,IFIX(aref_new_value));
	    word_i = word_i + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	}
	goto next_loop_2;
      end_loop_2:;
	start_index = FIXNUM_ADD1(delimiter_index);
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(indices_of_word_delimiters);
    }
    twrite_general_string(new_wide_string);
    reclaim_wide_string(new_wide_string);
    return VALUES_1(Qnil);
}

Object Symbol_name_wide_string_prop = UNBOUND;

static Object Qsymbol_name_wide_string;  /* symbol-name-wide-string */

/* GET-OR-MAKE-SYMBOL-NAME-WIDE-STRING */
Object get_or_make_symbol_name_wide_string(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(26,74);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qsymbol_name_wide_string);
    if (temp);
    else
	temp = mutate_global_property(symbol,
		make_symbol_name_wide_string(symbol),Qsymbol_name_wide_string);
    return VALUES_1(temp);
}

/* SYMBOL-NAMEW */
Object symbol_namew(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(26,75);
    temp = get_or_make_symbol_name_wide_string(symbol);
    return VALUES_1(temp);
}

/* MAKE-SYMBOL-NAME-WIDE-STRING */
Object make_symbol_name_wide_string(symbol)
    Object symbol;
{
    Object gensym_string, temp;

    x_note_fn_call(26,76);
    gensym_string = gensym_symbol_name(symbol);
    temp = gensym_string_to_wide_string(gensym_string);
    reclaim_gensym_string(gensym_string);
    return VALUES_1(temp);
}

/* TWRITE-WIDE-CHARACTER */
Object twrite_wide_character(wide_character)
    Object wide_character;
{
    Object temp, aref_arg_2;

    x_note_fn_call(26,77);
    if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
	    Total_length_of_current_wide_string))
	extend_current_wide_string(Fill_pointer_for_current_wide_string);
    temp = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),IFIX(wide_character));
    temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp;
    return VALUES_1(Nil);
}

static Object Qnormal;             /* normal */

static Object Qescape;             /* escape */

static Object Qunicode_u;          /* unicode-u */

static Object Qunicode;            /* unicode */

/* READ-WIDE-STRING */
Object read_wide_string(stream,subchar,arg)
    Object stream, subchar, arg;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object state_1, unicode_digit_count, unicode_value, ch, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,78);
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
	      if ( !CHAR_EQ(read_char(stream,T,Nil,T),CHR('\"')))
		  error((SI_Long)1L,"#w syntax error");
	      state_1 = Qnormal;
	      unicode_digit_count = FIX((SI_Long)0L);
	      unicode_value = FIX((SI_Long)0L);
	      ch = Nil;
	    next_loop:
	      ch = read_char(stream,T,Nil,T);
	      if (EQ(state_1,Qnormal)) {
		  if (CHAR_EQ(ch,CHR('\\')))
		      state_1 = Qescape;
		  else if (CHAR_EQ(ch,CHR('\"')))
		      goto end_1;
		  else
		      twrite_wide_character(CHAR_CODE(ch));
	      }
	      else if (EQ(state_1,Qescape)) {
		  if (CHAR_EQ(ch,CHR('U')) || CHAR_EQ(ch,CHR('u'))) {
		      state_1 = Qunicode_u;
		      unicode_digit_count = FIX((SI_Long)0L);
		      unicode_value = FIX((SI_Long)0L);
		  }
		  else {
		      twrite_wide_character(CHAR_CODE(ch));
		      state_1 = Qnormal;
		  }
	      }
	      else if (EQ(state_1,Qunicode) || EQ(state_1,Qunicode_u)) {
		  if (EQ(state_1,Qunicode_u)) {
		      if (CHAR_EQ(ch,CHR('U')) || CHAR_EQ(ch,CHR('u')))
			  temp = TRUEP(T);
		      else {
			  state_1 = Qunicode;
			  temp = TRUEP(Nil);
		      }
		  }
		  else
		      temp = TRUEP(Nil);
		  if ( !temp) {
		      gensymed_symbol = IFIX(unicode_value) << (SI_Long)4L;
		      temp_1 = digit_char_p(ch,FIX((SI_Long)16L));
		      if (temp_1);
		      else
			  temp_1 = error((SI_Long)2L,
				  "bad embedded unicode char ~c in wide string",
				  ch);
		      gensymed_symbol_1 = IFIX(temp_1);
		      unicode_value = FIX(gensymed_symbol | gensymed_symbol_1);
		      unicode_digit_count = FIXNUM_ADD1(unicode_digit_count);
		      if (IFIX(unicode_digit_count) == (SI_Long)4L) {
			  twrite_wide_character(unicode_value);
			  state_1 = Qnormal;
		      }
		  }
	      }
	      goto next_loop;
	    end_loop:
	    end_1:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* HASH-WIDE-STRING */
Object hash_wide_string(wide_string)
    Object wide_string;
{
    Object temp;
    SI_Long accumulator, index_1, length_1, ab_loop_bind_;

    x_note_fn_call(26,79);
    accumulator = (SI_Long)0L;
    index_1 = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    accumulator = ((accumulator & (SI_Long)2097151L) << (SI_Long)7L) + 
	    (accumulator >>  -  - (SI_Long)21L) ^ 
	    UBYTE_16_ISAREF_1(wide_string,index_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = FIX(accumulator);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SXHASHW */
Object sxhashw(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(26,80);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    hash_wide_string(thing) : sxhash(thing);
    return VALUES_1(temp);
}

/* OBTAIN-SIMPLE-TEXT-STRING */
Object obtain_simple_text_string(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(26,81);
    temp = make_stringw_function(length_1,Nil);
    return VALUES_1(temp);
}

/* RECLAIM-SIMPLE-TEXT-STRING */
Object reclaim_simple_text_string(simple_text_string)
    Object simple_text_string;
{
    x_note_fn_call(26,82);
    reclaim_wide_string(simple_text_string);
    return VALUES_1(Nil);
}

Object Maximum_text_string_length = UNBOUND;

Object Maximum_text_string_length_exceeded_message = UNBOUND;

/* MAXIMUM-TEXT-STRING-LENGTH-ERROR */
Object maximum_text_string_length_error(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(26,83);
    temp = error((SI_Long)3L,
	    "Attempting to allocate ~a element string, which is beyond the established maximum of ~a.",
	    length_1,Maximum_gensym_string_length);
    return VALUES_1(temp);
}

/* OBTAIN-TEXT-STRING */
Object obtain_text_string(length_1)
    Object length_1;
{
    x_note_fn_call(26,84);
    return make_stringw_function(length_1,Nil);
}

/* RECLAIM-TEXT-STRING */
Object reclaim_text_string(text_string)
    Object text_string;
{
    x_note_fn_call(26,85);
    reclaim_wide_string(text_string);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-TEXT-STRING-FUNCTION */
Object reclaim_if_text_string_function(thing)
    Object thing;
{
    x_note_fn_call(26,86);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return reclaim_wide_string(thing);
    else
	return VALUES_1(Nil);
}

/* COPY-TEXT-STRING */
Object copy_text_string(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(26,87);
    temp = copy_as_wide_string(string_1);
    return VALUES_1(temp);
}

/* COPY-PARTIAL-TEXT-STRING */
Object copy_partial_text_string(string_1,part_length)
    Object string_1, part_length;
{
    Object temp;

    x_note_fn_call(26,88);
    temp = copy_partial_wide_string(string_1,part_length);
    return VALUES_1(temp);
}

/* COPY-PORTION-OF-STRING-INTO-SIMPLE-TEXT-STRING */
Object copy_portion_of_string_into_simple_text_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    x_note_fn_call(26,89);
    return copy_portion_of_string_into_text_string(source_string,
	    source_start,source_end,destination_string,destination_start);
}

/* COPY-PORTION-OF-STRING-INTO-TEXT-STRING */
Object copy_portion_of_string_into_text_string(source_string,source_start,
	    source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(26,90);
    if (STRINGP(source_string))
	copy_portion_of_gensym_string_into_wide_string(source_string,
		source_start,source_end,destination_string,destination_start);
    else {
	if (EQ(source_string,destination_string)) {
	    if (FIXNUM_EQ(source_start,source_end))
		temp = TRUEP(T);
	    else {
		temp = FIXNUM_LT(source_start,destination_start) ? 
			FIXNUM_LT(destination_start,source_end) : TRUEP(Qnil);
		if (temp);
		else {
		    arg = IFIX(destination_start);
		    arg_1 = IFIX(source_start);
		    arg_2 = IFIX(FIXNUM_ADD(destination_start,
			    FIXNUM_MINUS(source_end,source_start)));
		    temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		}
		if (temp) {
		    copy_byte_vector_16_portion_carefully(source_string,
			    source_start,destination_string,
			    destination_start,FIXNUM_MINUS(source_end,
			    source_start));
		    temp = TRUEP(T);
		}
		else
		    temp = TRUEP(Qnil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    gensymed_symbol = source_string;
	    gensymed_symbol_1 = IFIX(source_start);
	    gensymed_symbol_2 = destination_string;
	    gensymed_symbol_3 = IFIX(destination_start);
	    gensymed_symbol_4 = IFIX(FIXNUM_MINUS(source_end,source_start));
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		    gensymed_symbol_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		    gensymed_symbol_3,gensymed_symbol_4);
	}
    }
    return VALUES_1(Nil);
}

/* COPY-PORTION-OF-TEXT-STRING-INTO-TEXT-STRING-GIVEN-COUNT */
Object copy_portion_of_text_string_into_text_string_given_count(source_string,
	    source_start,destination_string,destination_start,
	    count_of_chars_to_copy)
    Object source_string, source_start, destination_string, destination_start;
    Object count_of_chars_to_copy;
{
    Object new_source_string, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,91);
    if (EQ(source_string,destination_string)) {
	new_source_string = copy_text_string(source_string);
	gensymed_symbol = new_source_string;
	gensymed_symbol_1 = IFIX(source_start);
	gensymed_symbol_2 = destination_string;
	gensymed_symbol_3 = IFIX(destination_start);
	gensymed_symbol_4 = IFIX(count_of_chars_to_copy);
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	reclaim_text_string(new_source_string);
    }
    else {
	gensymed_symbol = source_string;
	gensymed_symbol_1 = IFIX(source_start);
	gensymed_symbol_2 = destination_string;
	gensymed_symbol_3 = IFIX(destination_start);
	gensymed_symbol_4 = IFIX(count_of_chars_to_copy);
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    return VALUES_1(Nil);
}

/* COPY-PORTION-OF-GENSYM-STRING-INTO-WIDE-STRING */
Object copy_portion_of_gensym_string_into_wide_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object ab_loop_iter_flag_, aref_new_value;
    SI_Long i, ab_loop_bind_, j;

    x_note_fn_call(26,92);
    if ( !ARRAY_HAS_FILL_POINTER_P(source_string)) {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	aref_new_value = CHAR_CODE(CHR(ISCHAR(source_string,i)));
	UBYTE_16_ISASET_1(destination_string,j,IFIX(aref_new_value));
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	i = IFIX(source_start);
	ab_loop_bind_ = IFIX(source_end);
	j = IFIX(destination_start);
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	aref_new_value = CHAR_CODE(CHR(ICHAR(source_string,i)));
	UBYTE_16_ISASET_1(destination_string,j,IFIX(aref_new_value));
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

/* COPY-TEXT-STRING-WITH-CASE-CONVERSION */
Object copy_text_string_with_case_conversion(string_1,
	    which_characters_to_upcase_qm)
    Object string_1, which_characters_to_upcase_qm;
{
    Object temp;

    x_note_fn_call(26,93);
    temp = copy_wide_string_with_case_conversion(string_1,
	    which_characters_to_upcase_qm);
    return VALUES_1(temp);
}

/* CAPITALIZE-TEXT-STRING-IN-PLACE */
Object capitalize_text_string_in_place(text_string)
    Object text_string;
{
    Object aref_new_value;
    SI_Long wide_character, code;

    x_note_fn_call(26,94);
    if (IFIX(lengthw(text_string)) > (SI_Long)0L) {
	wide_character = UBYTE_16_ISAREF_1(text_string,(SI_Long)0L);
	code = wide_character;
	if (code < (SI_Long)127L)
	    aref_new_value = (SI_Long)97L <= code && code <= (SI_Long)122L 
		    ? FIX(code + (SI_Long)-32L) : FIX(code);
	else {
	    aref_new_value = unicode_uppercase_if_lowercase(FIX(code));
	    if (aref_new_value);
	    else
		aref_new_value = FIX(code);
	}
	UBYTE_16_ISASET_1(text_string,(SI_Long)0L,IFIX(aref_new_value));
    }
    return VALUES_1(Nil);
}

/* DOWNCASE-TEXT-STRING-IN-PLACE */
Object downcase_text_string_in_place(text_string)
    Object text_string;
{
    Object character_1, code, aref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,95);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(text_string));
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
    code = character_1;
    if (IFIX(code) < (SI_Long)127L)
	aref_new_value = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	aref_new_value = unicode_lowercase_if_uppercase(code);
	if (aref_new_value);
	else
	    aref_new_value = code;
    }
    UBYTE_16_ISASET_1(text_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UPCASE-TEXT-STRING-IN-PLACE */
Object upcase_text_string_in_place(text_string)
    Object text_string;
{
    Object character_1, code, aref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,96);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(text_string));
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
    code = character_1;
    if (IFIX(code) < (SI_Long)127L)
	aref_new_value = (SI_Long)97L <= IFIX(code) && IFIX(code) <= 
		(SI_Long)122L ? FIX(IFIX(code) + (SI_Long)-32L) : code;
    else {
	aref_new_value = unicode_uppercase_if_lowercase(code);
	if (aref_new_value);
	else
	    aref_new_value = code;
    }
    UBYTE_16_ISASET_1(text_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* COPY-SYMBOL-NAME */
Object copy_symbol_name varargs_1(int, n)
{
    Object symbol, which_characters_not_to_downcase_qm;
    Object substitute_spaces_for_hyphens_qm, character_to_add_at_end_qm;
    Object acronym_list_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,97);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    which_characters_not_to_downcase_qm = REQUIRED_ARG_nonrelocating();
    substitute_spaces_for_hyphens_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_to_add_at_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    acronym_list_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return copy_symbol_name_as_wide_string(5,symbol,
	    which_characters_not_to_downcase_qm,
	    substitute_spaces_for_hyphens_qm,character_to_add_at_end_qm,
	    acronym_list_qm);
}

Object Length_when_written_parsably_prop = UNBOUND;

/* TFORMAT-TEXT-STRING */
Object tformat_text_string varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,98);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
		      arg8,arg9);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TEXT-STRING-SUBSTRING */
Object text_string_substring(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object start, end_1, temp;

    x_note_fn_call(26,99);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = STRINGP(string_1) ? gensym_string_length(string_1) : 
		text_string_length(string_1);
    temp = copy_text_string_portion(string_1,start,end_1);
    return VALUES_1(temp);
}

/* COPY-TEXT-STRING-PORTION */
Object copy_text_string_portion(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object part_length, new_text_string;

    x_note_fn_call(26,100);
    part_length = FIXNUM_MINUS(end_1,start);
    new_text_string = obtain_text_string(part_length);
    copy_portion_of_string_into_text_string(string_1,start,end_1,
	    new_text_string,FIX((SI_Long)0L));
    return VALUES_1(new_text_string);
}

/* TWRITE-ASCII-FROM-TEXT-STRING */
Object twrite_ascii_from_text_string(text_string)
    Object text_string;
{
    x_note_fn_call(26,101);
    twrite_ascii_from_wide_string(text_string);
    return VALUES_1(Nil);
}

/* CONVERT-TEXT-STRING-TO-ASCII-AS-MUCH-AS-POSSIBLE */
Object convert_text_string_to_ascii_as_much_as_possible(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(26,102);
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
	      twrite_ascii_from_text_string(text_string);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CONVERT-TEXT-STRING-TO-ASCII-FILENAME-AS-MUCH-AS-POSSIBLE */
Object convert_text_string_to_ascii_filename_as_much_as_possible(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(26,103);
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
	      twrite_ascii_from_text_string(text_string);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* COPY-TEXT-STRING-WITHOUT-NEWLINES */
Object copy_text_string_without_newlines(text_string,convert_to_spaces_qm)
    Object text_string, convert_to_spaces_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object length_2, character_1, temp, temp_1, schar_arg_2, schar_new_value;
    Object thing_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i, thing;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,104);
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
	      length_2 = text_string_length(text_string);
	      i = (SI_Long)0L;
	      character_1 = Nil;
	    next_loop:
	      if ( !(i < IFIX(length_2)))
		  goto end_loop;
	      temp = FIX(UBYTE_16_ISAREF_1(text_string,i));
	      i = i + (SI_Long)1L;
	      character_1 = temp;
	      if (newline_p(character_1)) {
		  if (convert_to_spaces_qm) {
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
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = (SI_Long)32L;
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(FIX(thing)) ? 
				  CHAR_CODE(FIX(thing)) : FIX(thing));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		  }
	      }
	      else if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing_1 = character_1;
		  twrite_wide_character(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing_1 = character_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			  CHAR_CODE(thing_1) : thing_1);
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
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

/* COPY-NULL-TERMINATED-STRING-AS-TEXT-STRING */
Object copy_null_terminated_string_as_text_string(string_1)
    Object string_1;
{
    Object length_if_null_terminated_qm;

    x_note_fn_call(26,105);
    length_if_null_terminated_qm = length_of_null_terminated_string(string_1);
    if (length_if_null_terminated_qm)
	return text_string_substring(string_1,FIX((SI_Long)0L),
		length_if_null_terminated_qm);
    else
	return copy_text_string(string_1);
}

/* LENGTH-OF-NULL-TERMINATED-TEXT-STRING */
Object length_of_null_terminated_text_string(string_1)
    Object string_1;
{
    Object string_length, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,106);
    string_length = text_string_length(string_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(string_length);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(string_1,i) == (SI_Long)0L) {
	temp = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* COPY-NULL-TERMINATED-TEXT-STRING */
Object copy_null_terminated_text_string varargs_1(int, n)
{
    Object source_string;
    Object target_string_qm, target_string;
    SI_Long length_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,107);
    INIT_ARGS_nonrelocating();
    source_string = REQUIRED_ARG_nonrelocating();
    target_string_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length_1 = text_string_p(source_string) ? 
	    IFIX(length_of_null_terminated_text_string(source_string)) : 
	    IFIX(length_of_null_terminated_string(source_string));
    target_string = target_string_qm;
    if (target_string);
    else
	target_string = obtain_text_string(FIX(length_1));
    copy_portion_of_string_into_text_string(source_string,FIX((SI_Long)0L),
	    FIX(length_1),target_string,FIX((SI_Long)0L));
    if (target_string_qm)
	UBYTE_16_ISASET_1(target_string,length_1,(SI_Long)0L);
    return VALUES_1(target_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_interned_text_strings, Qcount_of_interned_text_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Memory_used_for_interned_text_strings, Qmemory_used_for_interned_text_strings);

/* INTERN-TEXT-STRING */
Object intern_text_string varargs_1(int, n)
{
    Object text_string;
    Object package_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,108);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return intern_wide_string(2,text_string,package_qm);
}

/* INTERN-TEXT-STRING-NO-RECLAIM */
Object intern_text_string_no_reclaim varargs_1(int, n)
{
    Object text_string;
    Object package_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,109);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return intern_wide_string_no_reclaim(2,text_string,package_qm);
}

/* TEXT-STRING-P */
Object text_string_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(26,110);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* SYMBOL-NAME-TEXT-STRING */
Object symbol_name_text_string(symbol_name_1)
    Object symbol_name_1;
{
    Object temp;

    x_note_fn_call(26,111);
    temp = get_or_make_symbol_name_wide_string(symbol_name_1);
    return VALUES_1(temp);
}

/* TEXT-STRING-LENGTH */
Object text_string_length(text_string)
    Object text_string;
{
    Object temp;
    SI_Long length_1;

    x_note_fn_call(26,112);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
    temp = FIX(UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L));
    return VALUES_1(temp);
}

/* GENSYM-STRING-LENGTH */
Object gensym_string_length(gensym_string)
    Object gensym_string;
{
    Object temp;

    x_note_fn_call(26,113);
    temp = length(gensym_string);
    return VALUES_1(temp);
}

static Object Qlength_when_written_parsably;  /* length-when-written-parsably */

/* COPY-SYMBOL-NAME-PARSABLY */
Object copy_symbol_name_parsably(symbol,do_not_downcase_qm)
    Object symbol, do_not_downcase_qm;
{
    Object length_when_written_parsably_qm, temp, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object write_symbols_parsably_qm, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(26,114);
    length_when_written_parsably_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qlength_when_written_parsably);
    if (length_when_written_parsably_qm && 
	    FIXNUM_EQ(length_when_written_parsably_qm,
	    lengthw(symbol_name_text_string(symbol))))
	temp = do_not_downcase_qm ? 
		copy_text_string(symbol_name_text_string(symbol)) : 
		copy_symbol_name(2,symbol,Nil);
    else {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		5);
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
		  4);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    3);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      2);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			1);
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  0);
		    twrite_symbol(2,symbol,do_not_downcase_qm);
		  POP_SPECIAL();
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	mutate_global_property(symbol,text_string_length(text_string),
		Qlength_when_written_parsably);
	temp = text_string;
    }
    return VALUES_1(temp);
}

/* ORDINARY-SPACE-P */
Object ordinary_space_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character;

    x_note_fn_call(26,115);
    wide_character = IFIX(wide_character_init);
    return VALUES_1(wide_character == (SI_Long)32L ? T : Nil);
}

/* NEWLINE-P */
Object newline_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,116);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)13L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)10L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)10L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)8232L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)8233L ? T : Nil;
    return VALUES_1(temp);
}

/* HORIZONTAL-SPACE-P */
Object horizontal_space_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,117);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)32L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)9L ? T : Nil;
    return VALUES_1(temp);
}

/* TEXT-BREAK-P */
Object text_break_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,118);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)32L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)9L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)173L ? T : Nil;
    if (temp);
    else {
	arg = (SI_Long)8194L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)8203L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* BLANK-P */
Object blank_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,119);
    wide_character = IFIX(wide_character_init);
    temp = newline_p(FIX(wide_character));
    if (temp);
    else
	temp = horizontal_space_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* GRAPHIC-WORD-SEPARATOR-P */
Object graphic_word_separator_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,120);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)45L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)95L ? T : Nil;
    return VALUES_1(temp);
}

/* WORD-SEPARATOR-P */
Object word_separator_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,121);
    wide_character = IFIX(wide_character_init);
    temp = blank_p(FIX(wide_character));
    if (temp);
    else
	temp = graphic_word_separator_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* NON-GRAPHIC-CHARACTER-P */
Object non_graphic_character_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,122);
    wide_character = IFIX(wide_character_init);
    temp = newline_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* NON-SPACING-MARK-P */
Object non_spacing_mark_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,123);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)746L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)883L;
    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    if (temp);
    else {
	arg = (SI_Long)1456L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1474L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp);
    else
	temp = wide_character == (SI_Long)3633L ? T : Nil;
    if (temp);
    else {
	arg = (SI_Long)3636L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3642L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp);
    else {
	arg = (SI_Long)3655L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3662L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* ALPHABETIC-P */
Object alphabetic_p(wide_character_init)
    Object wide_character_init;
{
    Object temp, temp_1;
    SI_Long wide_character, code, arg, arg_1, arg_2;

    x_note_fn_call(26,124);
    wide_character = IFIX(wide_character_init);
    code = wide_character;
    if (code < (SI_Long)127L)
	temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code + 
		(SI_Long)32L) : FIX(code);
    else {
	temp = unicode_lowercase_if_uppercase(FIX(code));
	if (temp);
	else
	    temp = FIX(code);
    }
    code = wide_character;
    if (code < (SI_Long)127L)
	temp_1 = (SI_Long)97L <= code && code <= (SI_Long)122L ? FIX(code 
		+ (SI_Long)-32L) : FIX(code);
    else {
	temp_1 = unicode_uppercase_if_lowercase(FIX(code));
	if (temp_1);
	else
	    temp_1 = FIX(code);
    }
    temp_1 =  !NUM_EQ(temp,temp_1) ? T : Nil;
    if (temp_1);
    else {
	arg = (SI_Long)1424L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1455L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)1456L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1469L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)1473L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1474L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else
	temp_1 = (SI_Long)1476L == wide_character ? T : Nil;
    if (temp_1);
    else {
	arg = (SI_Long)1488L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1514L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)1520L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1522L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)1523L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)1524L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3585L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3630L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3632L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3642L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3648L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3652L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3653L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3654L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else
	temp_1 = (SI_Long)3655L == wide_character ? T : Nil;
    if (temp_1);
    else {
	arg = (SI_Long)3656L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3659L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3660L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3663L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3664L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3673L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp_1);
    else {
	arg = (SI_Long)3674L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)3675L;
	temp_1 = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    return VALUES_1(temp_1);
}

/* NUMERIC-P */
Object numeric_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,125);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)48L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)57L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHA-NUMERIC-P */
Object alpha_numeric_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,126);
    wide_character = IFIX(wide_character_init);
    temp = alphabetic_p(FIX(wide_character));
    if (temp);
    else
	temp = numeric_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* CJK-UNIFIED-IDEOGRAPH-P */
Object cjk_unified_ideograph_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,127);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)19968L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)40959L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-SYLLABLE-P */
Object hangul_syllable_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,128);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)44032L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)55203L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* OBSOLETE-HANGUL-SYLLABLE-P */
Object obsolete_hangul_syllable_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,129);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)13312L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)15663L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-JAMO-P */
Object hangul_jamo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,130);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)4352L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)4607L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-COMPATIBILITY-JAMO-P */
Object hangul_compatibility_jamo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,131);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12593L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12676L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HIRAGANA-P */
Object hiragana_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,132);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12353L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12435L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* KATAKANA-P */
Object katakana_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,133);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12449L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12538L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* BOPOMOFO-P */
Object bopomofo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,134);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12549L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12588L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* READABLE-SYMBOLIC-P */
Object readable_symbolic_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,135);
    wide_character = IFIX(wide_character_init);
    temp = numeric_p(FIX(wide_character));
    if (temp);
    else
	temp = alphabetic_p(FIX(wide_character));
    if (temp);
    else
	temp = wide_character == (SI_Long)45L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)95L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)39L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)46L ? T : Nil;
    if (temp);
    else
	temp = cjk_unified_ideograph_p(FIX(wide_character));
    if (temp);
    else
	temp = hangul_syllable_p(FIX(wide_character));
    if (temp);
    else
	temp = obsolete_hangul_syllable_p(FIX(wide_character));
    if (temp);
    else
	temp = hangul_jamo_p(FIX(wide_character));
    if (temp);
    else
	temp = hangul_compatibility_jamo_p(FIX(wide_character));
    if (temp);
    else
	temp = hiragana_p(FIX(wide_character));
    if (temp);
    else
	temp = katakana_p(FIX(wide_character));
    if (temp);
    else
	temp = bopomofo_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* G2-EXPONENT-MARKER-P */
Object g2_exponent_marker_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,136);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)101L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)69L ? T : Nil;
    return VALUES_1(temp);
}

/* WORD-DELIMITING-CHARACTER-P */
Object word_delimiting_character_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(26,137);
    wide_character = IFIX(wide_character_init);
    temp =  !TRUEP(alpha_numeric_p(FIX(wide_character))) ? ( 
	    !TRUEP(chinese_or_hangul_or_kana_p(FIX(wide_character))) ? T : 
	    Nil) : Qnil;
    return VALUES_1(temp);
}

/* CHINESE-OR-HANGUL-OR-KANA-P */
Object chinese_or_hangul_or_kana_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(26,138);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)19968L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)40959L;
    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    if (temp);
    else {
	arg = (SI_Long)44032L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)55203L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp);
    else {
	arg = (SI_Long)13312L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)15663L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp);
    else {
	arg = (SI_Long)12353L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)12436L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    if (temp);
    else {
	arg = (SI_Long)12449L;
	arg_1 = wide_character;
	arg_2 = (SI_Long)12538L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

Object The_type_description_of_gensym_string_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gensym_string_streams, Qchain_of_available_gensym_string_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_string_stream_count, Qgensym_string_stream_count);

Object Chain_of_available_gensym_string_streams_vector = UNBOUND;

/* GENSYM-STRING-STREAM-STRUCTURE-MEMORY-USAGE */
Object gensym_string_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(26,139);
    temp = Gensym_string_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GENSYM-STRING-STREAM-COUNT */
Object outstanding_gensym_string_stream_count()
{
    Object def_structure_gensym_string_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,140);
    gensymed_symbol = IFIX(Gensym_string_stream_count);
    def_structure_gensym_string_stream_variable = 
	    Chain_of_available_gensym_string_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gensym_string_stream_variable))
	goto end_loop;
    def_structure_gensym_string_stream_variable = 
	    ISVREF(def_structure_gensym_string_stream_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GENSYM-STRING-STREAM-1 */
Object reclaim_gensym_string_stream_1(gensym_string_stream)
    Object gensym_string_stream;
{
    Object temp, svref_arg_2;

    x_note_fn_call(26,141);
    inline_note_reclaim_cons(gensym_string_stream,Nil);
    temp = ISVREF(Chain_of_available_gensym_string_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(gensym_string_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gensym_string_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gensym_string_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-STRING-STREAM */
Object reclaim_structure_for_gensym_string_stream(gensym_string_stream)
    Object gensym_string_stream;
{
    x_note_fn_call(26,142);
    return reclaim_gensym_string_stream_1(gensym_string_stream);
}

static Object Qg2_defstruct_structure_name_gensym_string_stream_g2_struct;  /* g2-defstruct-structure-name::gensym-string-stream-g2-struct */

/* MAKE-PERMANENT-GENSYM-STRING-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_gensym_string_stream_structure_internal()
{
    Object def_structure_gensym_string_stream_variable;
    Object defstruct_g2_gensym_string_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,143);
    def_structure_gensym_string_stream_variable = Nil;
    atomic_incff_symval(Qgensym_string_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gensym_string_stream_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_gensym_string_stream_variable = the_array;
	SVREF(defstruct_g2_gensym_string_stream_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gensym_string_stream_g2_struct;
	def_structure_gensym_string_stream_variable = 
		defstruct_g2_gensym_string_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_string_stream_variable);
}

/* MAKE-GENSYM-STRING-STREAM-INTERNAL-1 */
Object make_gensym_string_stream_internal_1()
{
    Object def_structure_gensym_string_stream_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(26,144);
    def_structure_gensym_string_stream_variable = 
	    ISVREF(Chain_of_available_gensym_string_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gensym_string_stream_variable) {
	svref_arg_1 = Chain_of_available_gensym_string_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_gensym_string_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gensym_string_stream_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_string_stream_g2_struct;
    }
    else
	def_structure_gensym_string_stream_variable = 
		make_permanent_gensym_string_stream_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_string_stream_variable,Nil);
    ISVREF(def_structure_gensym_string_stream_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_string_stream_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gensym_string_stream_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_gensym_string_stream_variable);
}

/* MAKE-GENSYM-STRING-STREAM */
Object make_gensym_string_stream(gensym_string)
    Object gensym_string;
{
    Object stream, string_is_simple_qm;
    SI_Long svref_new_value_1;
    char svref_new_value;

    x_note_fn_call(26,145);
    stream = make_gensym_string_stream_internal_1();
    SVREF(stream,FIX((SI_Long)1L)) = gensym_string;
    svref_new_value =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    SVREF(stream,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
    string_is_simple_qm = ISVREF(stream,(SI_Long)3L);
    svref_new_value_1 = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string)) : 
	    IFIX(length(gensym_string));
    ISVREF(stream,(SI_Long)2L) = FIX(svref_new_value_1);
    ISVREF(stream,(SI_Long)4L) = FIX((SI_Long)0L);
    return VALUES_1(stream);
}

/* READ-CHARACTER-CODE */
Object read_character_code(gensym_string_stream)
    Object gensym_string_stream;
{
    Object local_character_index, escape_character_qm;
    Object character_or_character_code, gensym_string;
    Object gensym_string_is_simple_qm, temp_1, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long ascii_code, temp_2;
    char temp, character_1;

    x_note_fn_call(26,146);
    local_character_index = ISVREF(gensym_string_stream,(SI_Long)6L);
    if (local_character_index);
    else
	local_character_index = ISVREF(gensym_string_stream,(SI_Long)4L);
    escape_character_qm = Nil;
    character_or_character_code = Nil;
    if (FIXNUM_EQ(local_character_index,ISVREF(gensym_string_stream,
	    (SI_Long)2L)))
	return VALUES_1(Nil);
    else {
	SVREF(gensym_string_stream,FIX((SI_Long)5L)) = local_character_index;
	gensym_string = ISVREF(gensym_string_stream,(SI_Long)1L);
	gensym_string_is_simple_qm = ISVREF(gensym_string_stream,(SI_Long)3L);
	temp = gensym_string_is_simple_qm ? 
		CHARACTER_TO_CHAR(SCHAR(gensym_string,
		local_character_index)) : 
		CHARACTER_TO_CHAR(CHAR(gensym_string,local_character_index));
	local_character_index = FIXNUM_ADD1(local_character_index);
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
		temp_1 = gensym_string_is_simple_qm ? SCHAR(gensym_string,
			local_character_index) : CHAR(gensym_string,
			local_character_index);
		local_character_index = FIXNUM_ADD1(local_character_index);
		character_or_character_code = temp_1;
		break;
	      case 92:
		escape_character_qm = CHAR_TO_CHARACTER(character_1);
		gensymed_symbol = gensym_string;
		gensymed_symbol_1 = gensym_string_is_simple_qm;
		temp = gensymed_symbol_1 ? 
			CHARACTER_TO_CHAR(SCHAR(gensymed_symbol,
			local_character_index)) : 
			CHARACTER_TO_CHAR(CHAR(gensymed_symbol,
			local_character_index));
		local_character_index = FIXNUM_ADD1(local_character_index);
		ascii_code = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
		if (ascii_code < (SI_Long)40L) {
		    temp_2 = ascii_code << (SI_Long)13L;
		    temp = gensymed_symbol_1 ? 
			    CHARACTER_TO_CHAR(SCHAR(gensymed_symbol,
			    local_character_index)) : 
			    CHARACTER_TO_CHAR(CHAR(gensymed_symbol,
			    local_character_index));
		    local_character_index = FIXNUM_ADD1(local_character_index);
		    temp_2 = temp_2 + (SI_Long)95L * 
			    IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
		    temp = gensymed_symbol_1 ? 
			    CHARACTER_TO_CHAR(SCHAR(gensymed_symbol,
			    local_character_index)) : 
			    CHARACTER_TO_CHAR(CHAR(gensymed_symbol,
			    local_character_index));
		    local_character_index = FIXNUM_ADD1(local_character_index);
		    character_or_character_code = FIX(temp_2 + 
			    IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp))) + 
			    (SI_Long)-265976L);
		}
		else {
		    temp_2 = (SI_Long)95L * ascii_code;
		    temp = gensymed_symbol_1 ? 
			    CHARACTER_TO_CHAR(SCHAR(gensymed_symbol,
			    local_character_index)) : 
			    CHARACTER_TO_CHAR(CHAR(gensymed_symbol,
			    local_character_index));
		    local_character_index = FIXNUM_ADD1(local_character_index);
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
	SVREF(gensym_string_stream,FIX((SI_Long)6L)) = Nil;
	SVREF(gensym_string_stream,FIX((SI_Long)4L)) = local_character_index;
	if ( !TRUEP(escape_character_qm))
	    return VALUES_1(CHAR_CODE(character_or_character_code));
	else {
	    if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		temp_1 = 
			ISVREF(Reverse_iso_latin1_special_character_code_map,
			IFIX(CHAR_CODE(character_or_character_code)));
		if (temp_1);
		else {
		    temp_1 = CHAR_CODE(character_or_character_code);
		    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			temp_1 = Nil;
		    else
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 87:
			    temp_1 = Gensym_code_for_capital_ligature_oe;
			    break;
			  case 119:
			    temp_1 = Gensym_code_for_small_ligature_oe;
			    break;
			  case 42:
			    temp_1 = Gensym_code_for_bullet;
			    break;
			  case 38:
			    temp_1 = Gensym_code_for_small_letter_f_with_hook;
			    break;
			  case 58:
			    temp_1 = Gensym_code_for_trade_mark_sign;
			    break;
			  default:
			    temp_1 = Nil;
			    break;
			}
		}
	    }
	    else
		temp_1 = Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(Gensym_esc_for_linebreak_qm) ? 
		    CHAR_EQ(character_or_character_code,
		    Gensym_char_or_code_for_linebreak) : 
		    EQL(character_or_character_code,
		    Gensym_char_or_code_for_linebreak) && 
		    EQL(escape_character_qm,Gensym_esc_for_linebreak_qm))
		return VALUES_1(Gensym_code_for_linebreak);
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
		    CHAR_EQ(character_or_character_code,
		    Gensym_char_or_code_for_paragraph_break) : 
		    EQL(character_or_character_code,
		    Gensym_char_or_code_for_paragraph_break) && 
		    EQL(escape_character_qm,Gensym_esc_for_paragraph_break_qm))
		return VALUES_1(Gensym_code_for_paragraph_break);
	    else {
		temp_1 =  !EQ(escape_character_qm,CHR('\\')) ? 
			FIX((SI_Long)65535L) : Nil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(character_or_character_code);
	    }
	}
    }
}

/* UNREAD-CHARACTER-CODE */
Object unread_character_code(gensym_string_stream,character_code)
    Object gensym_string_stream, character_code;
{
    Object svref_new_value;

    x_note_fn_call(26,147);
    svref_new_value = ISVREF(gensym_string_stream,(SI_Long)5L);
    SVREF(gensym_string_stream,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PEEK-CHARACTER-CODE */
Object peek_character_code(gensym_string_stream)
    Object gensym_string_stream;
{
    Object character_code_qm;

    x_note_fn_call(26,148);
    character_code_qm = read_character_code(gensym_string_stream);
    if (character_code_qm)
	unread_character_code(gensym_string_stream,character_code_qm);
    return VALUES_1(character_code_qm);
}

/* STRING-TO-WIDE-STRING */
Object string_to_wide_string(string_1)
    Object string_1;
{
    Object wide_string;
    SI_Long length_1;

    x_note_fn_call(26,149);
    length_1 = IFIX(length(string_1));
    wide_string = make_stringw_function(length(string_1),Nil);
    copy_portion_of_gensym_string_into_wide_string(string_1,
	    FIX((SI_Long)0L),FIX(length_1),wide_string,FIX((SI_Long)0L));
    return VALUES_1(wide_string);
}

/* WIDE-STRING-TO-STRING */
Object wide_string_to_string(wide_string)
    Object wide_string;
{
    Object string_1;
    SI_Long length_1;

    x_note_fn_call(26,150);
    length_1 = IFIX(lengthw(wide_string));
    string_1 = obtain_simple_gensym_string(lengthw(wide_string));
    copy_portion_of_wide_string_octets_into_simple_gensym_string(wide_string,
	    FIX((SI_Long)0L),FIX(length_1),string_1,FIX((SI_Long)0L));
    return VALUES_1(string_1);
}

/* SORT-TEXT-STRING-FUNCTION */
Object sort_text_string_function(text_string,less_than_predicate,key)
    Object text_string, less_than_predicate, key;
{
    Object lesser_elt, greater_elt, temp;
    SI_Long end_point, lesser_index, ab_loop_bind_, greater_index;
    char temp_1;

    x_note_fn_call(26,151);
    end_point = IFIX(FIXNUM_SUB1(text_string_length(text_string)));
  next_loop:
    if (end_point < (SI_Long)1L)
	goto end_loop;
    lesser_index = (SI_Long)0L;
    ab_loop_bind_ = end_point;
    lesser_elt = Nil;
    greater_index = (SI_Long)0L;
    greater_elt = Nil;
  next_loop_1:
    if (lesser_index >= ab_loop_bind_)
	goto end_loop_1;
    lesser_elt = FIX(UBYTE_16_ISAREF_1(text_string,lesser_index));
    greater_index = lesser_index + (SI_Long)1L;
    greater_elt = FIX(UBYTE_16_ISAREF_1(text_string,greater_index));
    if (key) {
	temp = FUNCALL_1(key,greater_elt);
	temp_1 = TRUEP(FUNCALL_2(less_than_predicate,temp,FUNCALL_1(key,
		lesser_elt)));
    }
    else
	temp_1 = TRUEP(FUNCALL_2(less_than_predicate,greater_elt,lesser_elt));
    if (temp_1) {
	UBYTE_16_ISASET_1(text_string,greater_index,IFIX(lesser_elt));
	UBYTE_16_ISASET_1(text_string,lesser_index,IFIX(greater_elt));
    }
    lesser_index = lesser_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    end_point = end_point - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(text_string);
}

/* QUICKSORT-TEXT-STRING-ALPHABETICALLY */
Object quicksort_text_string_alphabetically(text_string)
    Object text_string;
{
    x_note_fn_call(26,152);
    quicksort_text_string_alphabetically_1(text_string,FIX((SI_Long)0L),
	    FIXNUM_SUB1(text_string_length(text_string)));
    return VALUES_1(text_string);
}

/* QUICKSORT-TEXT-STRING-ALPHABETICALLY-1 */
Object quicksort_text_string_alphabetically_1(s,l_init,r_init)
    Object s, l_init, r_init;
{
    Object temp;
    SI_Long l, r, i, j, x, w, aref_new_value;

    x_note_fn_call(26,153);
    l = IFIX(l_init);
    r = IFIX(r_init);
    i = l;
    j = r;
    x = UBYTE_16_ISAREF_1(s,l + r >>  -  - (SI_Long)1L);
  next_loop:
  next_loop_1:
    if ( !(UBYTE_16_ISAREF_1(s,i) < x))
	goto end_loop;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop:
  next_loop_2:
    if ( !(x < UBYTE_16_ISAREF_1(s,j)))
	goto end_loop_1;
    j = j - (SI_Long)1L;
    goto next_loop_2;
  end_loop_1:
    if (i <= j) {
	w = UBYTE_16_ISAREF_1(s,i);
	aref_new_value = UBYTE_16_ISAREF_1(s,j);
	UBYTE_16_ISASET_1(s,i,aref_new_value);
	UBYTE_16_ISASET_1(s,j,w);
	i = i + (SI_Long)1L;
	j = j - (SI_Long)1L;
    }
    if (i > j)
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    if (l < j) {
	quicksort_text_string_alphabetically_1(s,FIX(l),FIX(j));
	temp = quicksort_text_string_alphabetically_1(s,FIX(i),FIX(r));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOVE-DUPLICATES-IN-TEXT-STRING */
Object remove_duplicates_in_text_string(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object length_2, char_1, ab_loop_it_, thing, temp_1, schar_arg_2;
    Object schar_new_value, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_, j, ab_loop_bind__1;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,154);
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
	      length_2 = text_string_length(text_string);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_2);
	      char_1 = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
	      j = (SI_Long)0L;
	      ab_loop_bind__1 = IFIX(Fill_pointer_for_current_wide_string);
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if (j >= ab_loop_bind__1)
		  goto end_loop_1;
	      ab_loop_it_ = IFIX(char_1) == 
		      UBYTE_16_ISAREF_1(Current_wide_string,j) ? T : Nil;
	      if (ab_loop_it_) {
		  temp = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      j = j + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      temp = TRUEP(Qnil);
	    end_1:;
	      if ( !temp) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = char_1;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = char_1;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      result = copy_current_wide_string();
	      MVS_6(result,gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3,
		      gensymed_symbol_4,gensymed_symbol_5);
	      reclaim_wide_string(Current_wide_string);
	      result = VALUES_6(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3,
		      gensymed_symbol_4,gensymed_symbol_5);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CONCATENATE-TEXT-STRINGS */
Object concatenate_text_strings(text_string_1,text_string_2)
    Object text_string_1, text_string_2;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, length_1_1, length_2, length_3, bv16_length, aref_arg_2;
    SI_Long aref_new_value, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;

    x_note_fn_call(26,155);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string_1));
    length_1_1 = UBYTE_16_ISAREF_1(text_string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string_2));
    length_2 = UBYTE_16_ISAREF_1(text_string_2,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string_2,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    length_3 = length_1_1 + length_2;
    wide_string_bv16 = allocate_byte_vector_16(FIX(length_3 + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = length_3 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | length_3 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,length_3,(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    gensymed_symbol = text_string_1;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = new_wide_string;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = length_1_1 - (SI_Long)0L;
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    gensymed_symbol = text_string_2;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = new_wide_string;
    gensymed_symbol_3 = length_1_1;
    gensymed_symbol_4 = length_2 - (SI_Long)0L;
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(new_wide_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Base_36_digits_string, Qbase_36_digits_string);

/* RECLAIM-GENSYM-STRING-OR-WIDE-STRING */
Object reclaim_gensym_string_or_wide_string(gensym_string_or_wide_string)
    Object gensym_string_or_wide_string;
{
    x_note_fn_call(26,156);
    if (STRINGP(gensym_string_or_wide_string))
	return reclaim_gensym_string(gensym_string_or_wide_string);
    else
	return reclaim_wide_string(gensym_string_or_wide_string);
}

/* GENSYM-STRING-OR-WIDE-STRING-P */
Object gensym_string_or_wide_string_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(26,157);
    temp = STRINGP(thing) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		(SI_Long)0L ? T : Nil);
}

/* RECLAIM-IF-GENSYM-STRING-OR-WIDE-STRING */
Object reclaim_if_gensym_string_or_wide_string(thing)
    Object thing;
{
    x_note_fn_call(26,158);
    if (gensym_string_or_wide_string_p(thing))
	return reclaim_gensym_string_or_wide_string(thing);
    else
	return VALUES_1(Nil);
}

/* TWRITE-LINE-SEPARATOR */
Object twrite_line_separator()
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;
    char thing_1;

    x_note_fn_call(26,159);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)8232L;
	    return twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)8232L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = '\n';
	return twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
		CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = '\n';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
		CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
	return VALUES_1(Fill_pointer_for_current_gensym_string);
    }
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qalpha;              /* alpha */

static Object Qbeta;               /* beta */

static Object Qrev_dot;            /* rev. */

/* GET-QUALITY-AND-REVISION-OF-REVISION-STRING */
Object get_quality_and_revision_of_revision_string(revision_string)
    Object revision_string;
{
    volatile Object revision_string_text_string;
    Object quality, revision, index_1, end_index, next_thing_qm;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(26,160);
    SAVE_STACK();
    revision_string_text_string = Qunbound_in_protected_let;
    quality = Qunbound_in_protected_let;
    revision = Qunbound_in_protected_let;
    index_1 = Qunbound_in_protected_let;
    end_index = Qunbound_in_protected_let;
    next_thing_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	revision_string_text_string = copy_text_string(revision_string);
	quality = FIX((SI_Long)0L);
	revision = FIX((SI_Long)0L);
	index_1 = FIX((SI_Long)0L);
	end_index = text_string_length(revision_string_text_string);
	next_thing_qm = Nil;
	index_1 = skip_spaces_in_string(revision_string_text_string,
		index_1,end_index);
	result = read_symbol_from_string(revision_string_text_string,
		index_1,end_index);
	MVS_2(result,next_thing_qm,index_1);
	if (next_thing_qm) {
	    if (EQ(next_thing_qm,Qalpha))
		quality = FIX((SI_Long)1L);
	    else if (EQ(next_thing_qm,Qbeta))
		quality = FIX((SI_Long)2L);
	    else if (EQ(next_thing_qm,Qrev_dot))
		quality = FIX((SI_Long)3L);
	    else
		quality = FIX((SI_Long)0L);
	    if (next_thing_qm) {
		temp = EQ(next_thing_qm,Qrev_dot);
		if (temp);
		else {
		    index_1 = 
			    skip_spaces_in_string(revision_string_text_string,
			    index_1,end_index);
		    result = read_symbol_from_string(revision_string_text_string,
			    index_1,end_index);
		    MVS_2(result,next_thing_qm,index_1);
		    temp = EQ(next_thing_qm,Qrev_dot);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		index_1 = 
			skip_spaces_in_string(revision_string_text_string,
			index_1,end_index);
		result = read_number_from_string(revision_string_text_string,
			index_1,end_index);
		MVS_2(result,next_thing_qm,index_1);
		if (next_thing_qm && NUMBERP(next_thing_qm))
		    revision = next_thing_qm;
	    }
	}
	SAVE_VALUES(VALUES_2(quality,revision));
    }
    POP_UNWIND_PROTECT(0);
    if (revision_string_text_string) {
	if ( !EQ(revision_string_text_string,Qunbound_in_protected_let))
	    reclaim_text_string(revision_string_text_string);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* COPY-FOREIGN-STRING-ARG-IF-APPROPRIATE */
Object copy_foreign_string_arg_if_appropriate(gensym_string_or_wide_string)
    Object gensym_string_or_wide_string;
{
    Object string_1, length_2;
    SI_Long length_1;

    x_note_fn_call(26,161);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensym_string_or_wide_string) != 
	    (SI_Long)0L) {
	length_1 = 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string_or_wide_string));
	length_1 = UBYTE_16_ISAREF_1(gensym_string_or_wide_string,length_1 
		- (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(gensym_string_or_wide_string,length_1 
		- (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	string_1 = 
		obtain_simple_gensym_string_of_quantized_length(FIX(length_1));
	copy_portion_of_wide_string_octets_into_simple_gensym_string(gensym_string_or_wide_string,
		FIX((SI_Long)0L),FIX(length_1),string_1,FIX((SI_Long)0L));
	return VALUES_1(string_1);
    }
    else if ( ! !ARRAY_HAS_FILL_POINTER_P(gensym_string_or_wide_string)) {
	length_2 = length(gensym_string_or_wide_string);
	string_1 = obtain_simple_gensym_string_of_quantized_length(length_2);
	copy_portion_of_string_into_simple_gensym_string(gensym_string_or_wide_string,
		FIX((SI_Long)0L),length_2,string_1,FIX((SI_Long)0L));
	return VALUES_1(string_1);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-PORTION-OF-WIDE-STRING-OCTETS-INTO-SIMPLE-GENSYM-STRING */
Object copy_portion_of_wide_string_octets_into_simple_gensym_string(source_string,
	    source_start_init,source_end_init,destination_string,
	    destination_start_init)
    Object source_string, source_start_init, source_end_init;
    Object destination_string, destination_start_init;
{
    Object char_1, ab_loop_iter_flag_;
    SI_Long source_start, source_end, destination_start, i, ab_loop_bind_, j;
    SI_Long gensymed_symbol;
    char schar_new_value;

    x_note_fn_call(26,162);
    source_start = IFIX(source_start_init);
    source_end = IFIX(source_end_init);
    destination_start = IFIX(destination_start_init);
    i = source_start;
    ab_loop_bind_ = source_end;
    j = destination_start;
    char_1 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    char_1 = FIX(UBYTE_16_ISAREF_1(source_string,i));
    if ((SI_Long)8232L == IFIX(char_1))
	schar_new_value = '\n';
    else {
	gensymed_symbol = (SI_Long)255L & IFIX(char_1);
	schar_new_value = CHARACTER_TO_CHAR(CODE_CHAR(FIX(gensymed_symbol)));
    }
    SET_ISCHAR(destination_string,j,schar_new_value);
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* POSITION-IN-TEXT-STRING */
Object position_in_text_string(character_1,string_1)
    Object character_1, string_1;
{
    Object temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,163);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(string_1,i) == IFIX(character_1)) {
	temp = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* POSITION-IN-TEXT-STRING-TAIL */
Object position_in_text_string_tail(character_1,string_1,start)
    Object character_1, string_1, start;
{
    Object temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,164);
    i = IFIX(start);
    ab_loop_bind_ = IFIX(lengthw(string_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(string_1,i) == IFIX(character_1)) {
	temp = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-IN-TEXT-STRING */
Object find_in_text_string(character_1,string_1)
    Object character_1, string_1;
{
    Object char_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,165);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
    if (FIXNUM_EQ(char_1,character_1)) {
	temp = char_1;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* POSITION-OF-TEXT-CHARACTER-IN-LIST */
Object position_of_text_character_in_list(character_1,list_1)
    Object character_1, list_1;
{
    Object char_1, ab_loop_list_, temp;
    SI_Long i;

    x_note_fn_call(26,166);
    i = (SI_Long)0L;
    char_1 = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    char_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(char_1,character_1)) {
	temp = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-TEXT-CHARACTER-IN-LIST */
Object find_text_character_in_list(character_1,list_1)
    Object character_1, list_1;
{
    Object char_1, ab_loop_list_, temp;
    SI_Long i;

    x_note_fn_call(26,167);
    i = (SI_Long)0L;
    char_1 = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    char_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(char_1,character_1)) {
	temp = char_1;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-TEXT-CHARACTER-IN-SEQUENCE */
Object find_text_character_in_sequence(character_1,bag)
    Object character_1, bag;
{
    Object temp, element;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,168);
    if (text_string_p(bag))
	temp = find_in_text_string(character_1,bag);
    else if (LISTP(bag))
	temp = find_text_character_in_list(character_1,bag);
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(lengthw(bag));
	element = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	element = elt(bag,FIX(i));
	if (FIXNUM_EQ(character_1,element)) {
	    temp = element;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* POSITION-OF-TEXT-CHARACTER-NOT-IN-BAG-FUNCTION */
Object position_of_text_character_not_in_bag_function(string_1,bag,start,end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,169);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = lengthw(string_1);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( 
	    !TRUEP(find_text_character_in_sequence(FIX(UBYTE_16_ISAREF_1(string_1,
	    i)),bag)))
	return VALUES_1(FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* POSITION-OF-TEXT-CHARACTER-IN-BAG-FUNCTION */
Object position_of_text_character_in_bag_function(string_1,bag,start,end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,170);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = lengthw(string_1);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (find_text_character_in_sequence(FIX(UBYTE_16_ISAREF_1(string_1,i)),
	    bag))
	return VALUES_1(FIX(i));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* POSITION-OF-TEXT-CHARACTER-NOT-IN-BAG-FROM-END-FUNCTION */
Object position_of_text_character_not_in_bag_from_end_function(string_1,
	    bag,start,end_1)
    Object string_1, bag, start, end_1;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;

    x_note_fn_call(26,171);
    temp = end_1;
    if (temp);
    else
	temp = lengthw(string_1);
    gensymed_symbol = IFIX(temp);
    gensymed_symbol_1 = (SI_Long)1L;
    i = gensymed_symbol - gensymed_symbol_1;
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    ab_loop_bind_ = IFIX(temp);
  next_loop:
    if (i < ab_loop_bind_)
	goto end_loop;
    if ( 
	    !TRUEP(find_text_character_in_sequence(FIX(UBYTE_16_ISAREF_1(string_1,
	    i)),bag)))
	return VALUES_1(FIX(i));
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TEXT-STRING-TRIM */
Object text_string_trim(character_bag,string_1)
    Object character_bag, string_1;
{
    Object character_1;
    SI_Long start, ab_loop_bind_, end_1;

    x_note_fn_call(26,172);
    start = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
    character_1 = Nil;
  next_loop:
    if (start >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,start));
    if ( !TRUEP(find_text_character_in_sequence(character_1,character_bag)))
	goto end_loop;
    start = start + (SI_Long)1L;
    goto next_loop;
  end_loop:
    end_1 = IFIX(lengthw(string_1));
    ab_loop_bind_ = start;
    character_1 = Nil;
  next_loop_1:
    if (end_1 <= ab_loop_bind_)
	goto end_loop_1;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,end_1 - (SI_Long)1L));
    if ( !TRUEP(find_text_character_in_sequence(character_1,character_bag)))
	goto end_loop_1;
    end_1 = end_1 - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    return text_string_substring(string_1,FIX(start),FIX(end_1));
    return VALUES_1(Qnil);
    return VALUES_1(Qnil);
}

/* TEXT-STRING-LEFT-TRIM */
Object text_string_left_trim(character_bag,string_1)
    Object character_bag, string_1;
{
    Object character_1;
    SI_Long start, ab_loop_bind_;

    x_note_fn_call(26,173);
    start = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
    character_1 = Nil;
  next_loop:
    if (start >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,start));
    if ( !TRUEP(find_text_character_in_sequence(character_1,character_bag)))
	goto end_loop;
    start = start + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return text_string_substring(string_1,FIX(start),Nil);
    return VALUES_1(Qnil);
}

/* TEXT-STRING-RIGHT-TRIM */
Object text_string_right_trim(character_bag,string_1)
    Object character_bag, string_1;
{
    Object character_1;
    SI_Long end_1;

    x_note_fn_call(26,174);
    end_1 = IFIX(lengthw(string_1));
    character_1 = Nil;
  next_loop:
    if (end_1 <= (SI_Long)0L)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,end_1 - (SI_Long)1L));
    if ( !TRUEP(find_text_character_in_sequence(character_1,character_bag)))
	goto end_loop;
    end_1 = end_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return text_string_substring(string_1,Nil,FIX(end_1));
    return VALUES_1(Qnil);
}

/* PARSE-TEXT-LINE-GIVEN-GROUPING-BAG */
Object parse_text_line_given_grouping_bag(text_line,delimiter_bag,trim_bag,
	    start,end_1,grouping_bag)
    Object text_line, delimiter_bag, trim_bag, start, end_1, grouping_bag;
{
    Object temp, substart, i0_qm, in_group_p, i, peek_p, j, k, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, this_char, ab_loop_it_, group_start_p;
    SI_Long start_1, end_2, grouping_start_char, grouping_end_char, i2;
    SI_Long ab_loop_bind_;

    x_note_fn_call(26,175);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start_1 = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = lengthw(text_line);
    end_2 = IFIX(temp);
    grouping_start_char = UBYTE_16_ISAREF_1(grouping_bag,(SI_Long)0L);
    grouping_end_char = UBYTE_16_ISAREF_1(grouping_bag,(SI_Long)1L);
    substart = FIX(start_1);
    i0_qm = Nil;
    in_group_p = Nil;
    i = Nil;
    peek_p = Nil;
    j = Nil;
    k = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !(IFIX(substart) < end_2))
	goto end_loop;
    i0_qm = position_of_text_character_not_in_bag_function(text_line,
	    trim_bag,substart,FIX(end_2));
    if ( !TRUEP(i0_qm))
	goto end_loop;
    temp = FIX(UBYTE_16_ISAREF_1(text_line,IFIX(i0_qm)));
    in_group_p = EQ(temp,FIX(grouping_start_char)) ? T : Nil;
    i = in_group_p ? FIXNUM_ADD1(i0_qm) : i0_qm;
    peek_p = Nil;
    if (in_group_p) {
	i2 = IFIX(i);
	ab_loop_bind_ = end_2;
	this_char = Nil;
	ab_loop_it_ = Nil;
      next_loop_1:
	if (i2 >= ab_loop_bind_)
	    goto end_loop_1;
	this_char = FIX(UBYTE_16_ISAREF_1(text_line,i2));
	ab_loop_it_ = EQ(this_char,FIX(grouping_end_char)) ? FIX(i2) : Qnil;
	if (ab_loop_it_) {
	    j = ab_loop_it_;
	    goto end_3;
	}
	i2 = i2 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	j = FIX(end_2);
	goto end_3;
	j = Qnil;
      end_3:;
    }
    else {
	i2 = IFIX(i);
	ab_loop_bind_ = end_2;
	this_char = Nil;
	group_start_p = Nil;
	ab_loop_it_ = Nil;
      next_loop_2:
	if (i2 >= ab_loop_bind_)
	    goto end_loop_2;
	this_char = FIX(UBYTE_16_ISAREF_1(text_line,i2));
	group_start_p = EQ(this_char,FIX(grouping_start_char)) ? T : Nil;
	if (group_start_p)
	    peek_p = T;
	ab_loop_it_ = group_start_p || 
		find_text_character_in_sequence(this_char,delimiter_bag) ? 
		FIX(i2) : Qnil;
	if (ab_loop_it_) {
	    j = ab_loop_it_;
	    goto end_4;
	}
	i2 = i2 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	j = Qnil;
      end_4:;
    }
    k = in_group_p ? Nil : 
	    position_of_text_character_not_in_bag_from_end_function(text_line,
	    trim_bag,i,j);
    ab_loopvar__2 = gensym_cons_1(text_string_substring(text_line,i,k ? 
	    FIXNUM_ADD1(k) : j),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if ( !TRUEP(j))
	goto end_loop;
    substart = peek_p ? j : FIXNUM_ADD1(j);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_5;
    temp = Qnil;
  end_5:;
    return VALUES_1(temp);
}

/* PARSE-TEXT-LINE-INTO-LIST-OF-TEXT-STRINGS-FUNCTION */
Object parse_text_line_into_list_of_text_strings_function(text_line,
	    delimiter_bag,trim_bag,start,end_1,grouping_bag)
    Object text_line, delimiter_bag, trim_bag, start, end_1, grouping_bag;
{
    Object temp, substart, i, j, k, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long start_1, end_2;

    x_note_fn_call(26,176);
    if (grouping_bag)
	return parse_text_line_given_grouping_bag(text_line,delimiter_bag,
		trim_bag,start,end_1,grouping_bag);
    else {
	temp = start;
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	start_1 = IFIX(temp);
	temp = end_1;
	if (temp);
	else
	    temp = lengthw(text_line);
	end_2 = IFIX(temp);
	substart = FIX(start_1);
	i = Nil;
	j = Nil;
	k = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !(IFIX(substart) <= end_2))
	    goto end_loop;
	temp = position_of_text_character_not_in_bag_function(text_line,
		trim_bag,substart,FIX(end_2));
	if (temp);
	else
	    temp = FIX(end_2);
	i = temp;
	j = position_of_text_character_in_bag_function(text_line,
		delimiter_bag,i,FIX(end_2));
	k = 
		position_of_text_character_not_in_bag_from_end_function(text_line,
		trim_bag,i,j);
	ab_loopvar__2 = gensym_cons_1(text_string_substring(text_line,i,k ?
		 FIXNUM_ADD1(k) : j),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if ( !TRUEP(j))
	    goto end_loop;
	substart = FIXNUM_ADD1(j);
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

/* PARSE-MODULE-MAP-LINE-INTO-LIST-OF-TEXT-STRINGS-FUNCTION */
Object parse_module_map_line_into_list_of_text_strings_function(text_line,
	    delimiter_bag,trim_bag,start,end_1)
    Object text_line, delimiter_bag, trim_bag, start, end_1;
{
    Object temp, substart, i, j, k, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long start_1, end_2;

    x_note_fn_call(26,177);
    temp = start;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start_1 = IFIX(temp);
    temp = end_1;
    if (temp);
    else
	temp = lengthw(text_line);
    end_2 = IFIX(temp);
    substart = FIX(start_1);
    i = Nil;
    j = Nil;
    k = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !(IFIX(substart) <= end_2))
	goto end_loop;
    temp = position_of_text_character_not_in_bag_function(text_line,
	    trim_bag,substart,FIX(end_2));
    if (temp);
    else
	temp = FIX(end_2);
    i = temp;
    j = position_of_text_character_in_bag_function(text_line,delimiter_bag,
	    i,FIX(end_2));
    k = position_of_text_character_not_in_bag_from_end_function(text_line,
	    trim_bag,i,j);
    if ( !(j || k))
	goto end_loop;
    temp = text_string_substring_from_module_map_line(text_line,i,k ? 
	    FIXNUM_ADD1(k) : j);
    delimiter_bag = Nil;
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if ( !TRUEP(j))
	goto end_loop;
    substart = FIXNUM_ADD1(j);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* TEXT-STRING-SUBSTRING-FROM-MODULE-MAP-LINE */
Object text_string_substring_from_module_map_line(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object start, end_1, temp;

    x_note_fn_call(26,178);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = lengthw(string_1);
    if (UBYTE_16_ISAREF_1(string_1,IFIX(start)) == (SI_Long)34L && 
	    UBYTE_16_ISAREF_1(string_1,IFIX(FIXNUM_SUB1(end_1))) == 
	    (SI_Long)34L) {
	start = FIXNUM_ADD1(start);
	end_1 = FIXNUM_SUB1(end_1);
    }
    temp = copy_text_string_portion(string_1,start,end_1);
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* PARSE-SPACE-DELIMITED-TEXT-LINE-INTO-LIST-OF-TEXT-STRINGS */
Object parse_space_delimited_text_line_into_list_of_text_strings(text_line)
    Object text_line;
{
    x_note_fn_call(26,179);
    return parse_module_map_line_into_list_of_text_strings_function(text_line,
	    list_constant,list_constant,Nil,Nil);
}

/* SYNTACTICALLY-NUMERIC-P */
Object syntactically_numeric_p(text_string)
    Object text_string;
{
    Object number_parsing_state, possibly_numeric_p, char_1, gensymed_symbol_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol;
    char temp;

    x_note_fn_call(26,180);
    number_parsing_state = Nil;
    possibly_numeric_p = T;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(text_string));
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
    if (possibly_numeric_p) {
	gensymed_symbol = IFIX(char_1);
	if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) :
		 TRUEP(Nil)) {
	    if ( !TRUEP(number_parsing_state) || 
		    IFIX(number_parsing_state) <= (SI_Long)2L)
		number_parsing_state = FIX((SI_Long)2L);
	    else if (IFIX(number_parsing_state) <= (SI_Long)4L)
		number_parsing_state = FIX((SI_Long)4L);
	    else
		number_parsing_state = FIX((SI_Long)7L);
	}
	else if (EQ(number_parsing_state,Qnil)) {
	    if (EQ(char_1,FIX((SI_Long)45L)))
		number_parsing_state = FIX((SI_Long)1L);
	    else if (EQ(char_1,FIX((SI_Long)46L)))
		number_parsing_state = FIX((SI_Long)3L);
	    else
		number_parsing_state = Qnil;
	}
	else if (EQ(number_parsing_state,FIX((SI_Long)1L)))
	    number_parsing_state = EQ(char_1,FIX((SI_Long)46L)) ? 
		    FIX((SI_Long)3L) : Nil;
	else if (EQ(number_parsing_state,FIX((SI_Long)2L))) {
	    if (EQ(char_1,FIX((SI_Long)46L)))
		number_parsing_state = FIX((SI_Long)4L);
	    else if ( !TRUEP(Nil) && (IFIX(char_1) == (SI_Long)101L || 
		    IFIX(char_1) == (SI_Long)69L))
		number_parsing_state = FIX((SI_Long)5L);
	    else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
		    FIX((SI_Long)39L)) || EQ(char_1,FIX((SI_Long)95L)))
		number_parsing_state = Nil;
	    else {
		gensymed_symbol_1 = char_1;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state = Qinteger;
		else
		    number_parsing_state = Qnil;
	    }
	}
	else if (EQ(number_parsing_state,FIX((SI_Long)4L))) {
	    if ( !TRUEP(Nil) && (IFIX(char_1) == (SI_Long)101L || 
		    IFIX(char_1) == (SI_Long)69L))
		number_parsing_state = FIX((SI_Long)5L);
	    else if (EQ(char_1,FIX((SI_Long)46L)))
		number_parsing_state = Nil;
	    else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
		    FIX((SI_Long)39L)) || EQ(char_1,FIX((SI_Long)95L)))
		number_parsing_state = Nil;
	    else {
		gensymed_symbol_1 = char_1;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state = Qfloat;
		else
		    number_parsing_state = Qnil;
	    }
	}
	else if (EQ(number_parsing_state,FIX((SI_Long)5L)))
	    number_parsing_state = EQ(char_1,FIX((SI_Long)43L)) || 
		    EQ(char_1,FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
	else if (EQ(number_parsing_state,FIX((SI_Long)7L))) {
	    if (EQ(char_1,FIX((SI_Long)46L)))
		number_parsing_state = Nil;
	    else if (EQ(char_1,FIX((SI_Long)45L)) || EQ(char_1,
		    FIX((SI_Long)39L)) || EQ(char_1,FIX((SI_Long)95L)))
		number_parsing_state = Nil;
	    else {
		gensymed_symbol_1 = char_1;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state = Qfloat;
		else
		    number_parsing_state = Qnil;
	    }
	}
	else
	    number_parsing_state = Qnil;
	possibly_numeric_p = FIXNUMP(number_parsing_state) ? T : Nil;
	temp = TRUEP(possibly_numeric_p);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	goto end_loop;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (possibly_numeric_p) {
	if (possibly_numeric_p) {
	    gensymed_symbol = (SI_Long)32L;
	    if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		    (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
		    (SI_Long)48L)) : TRUEP(Nil)) {
		if ( !TRUEP(number_parsing_state) || 
			IFIX(number_parsing_state) <= (SI_Long)2L)
		    number_parsing_state = FIX((SI_Long)2L);
		else if (IFIX(number_parsing_state) <= (SI_Long)4L)
		    number_parsing_state = FIX((SI_Long)4L);
		else
		    number_parsing_state = FIX((SI_Long)7L);
	    }
	    else if (EQ(number_parsing_state,Qnil)) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)))
		    number_parsing_state = FIX((SI_Long)1L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state = FIX((SI_Long)3L);
		else
		    number_parsing_state = Qnil;
	    }
	    else if (EQ(number_parsing_state,FIX((SI_Long)1L)))
		number_parsing_state = EQ(FIX((SI_Long)32L),
			FIX((SI_Long)46L)) ? FIX((SI_Long)3L) : Nil;
	    else if (EQ(number_parsing_state,FIX((SI_Long)2L))) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state = FIX((SI_Long)4L);
		else if ( !TRUEP(Nil) && ((SI_Long)32L == (SI_Long)101L || 
			(SI_Long)32L == (SI_Long)69L))
		    number_parsing_state = FIX((SI_Long)5L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state = Qinteger;
		    else
			number_parsing_state = Qnil;
		}
	    }
	    else if (EQ(number_parsing_state,FIX((SI_Long)4L))) {
		if ( !TRUEP(Nil) && ((SI_Long)32L == (SI_Long)101L || 
			(SI_Long)32L == (SI_Long)69L))
		    number_parsing_state = FIX((SI_Long)5L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state = Nil;
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state = Qfloat;
		    else
			number_parsing_state = Qnil;
		}
	    }
	    else if (EQ(number_parsing_state,FIX((SI_Long)5L)))
		number_parsing_state = EQ(FIX((SI_Long)32L),
			FIX((SI_Long)43L)) || EQ(FIX((SI_Long)32L),
			FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
	    else if (EQ(number_parsing_state,FIX((SI_Long)7L))) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state = Nil;
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state = Qfloat;
		    else
			number_parsing_state = Qnil;
		}
	    }
	    else
		number_parsing_state = Qnil;
	    possibly_numeric_p = FIXNUMP(number_parsing_state) ? T : Nil;
	}
	if (EQ(number_parsing_state,Qinteger))
	    return VALUES_1(Qinteger);
	else if (EQ(number_parsing_state,Qfloat))
	    return VALUES_1(Qfloat);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* SYNTACTICALLY-NUMERIC-SUBSTRING-P */
Object syntactically_numeric_substring_p varargs_1(int, n)
{
    Object string_1;
    Object start_qm, end_qm, disallow_junk_qm, disallow_leading_whitespace_qm;
    Object disallow_unary_plus_qm, kind_qm, start_index, end_index, strlen_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(26,181);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    disallow_junk_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    disallow_leading_whitespace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    disallow_unary_plus_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = syntactically_numeric_substring_p_1(string_1,Nil,start_qm,
	    end_qm,disallow_junk_qm,disallow_leading_whitespace_qm,
	    disallow_unary_plus_qm);
    MVS_3(result,kind_qm,start_index,end_index);
    if (kind_qm) {
	strlen_1 = lengthw(string_1);
	if (FIXNUM_GT(strlen_1,end_index) && UBYTE_16_ISAREF_1(string_1,
		IFIX(end_index)) == (SI_Long)76L)
	    end_index = FIXNUM_ADD1(end_index);
	return VALUES_3(kind_qm,start_index,end_index);
    }
    else
	return syntactically_numeric_substring_p_1(string_1,T,start_qm,
		end_qm,disallow_junk_qm,disallow_leading_whitespace_qm,
		disallow_unary_plus_qm);
}

static Object list_constant_1;     /* # */

/* SYNTACTICALLY-NUMERIC-SUBSTRING-P-1 */
Object syntactically_numeric_substring_p_1(string_1,
	    ignore_exponent_marker_qm,start_qm,end_qm,disallow_junk_qm,
	    disallow_leading_whitespace_qm,disallow_unary_plus_qm)
    Object string_1, ignore_exponent_marker_qm, start_qm, end_qm;
    Object disallow_junk_qm, disallow_leading_whitespace_qm;
    Object disallow_unary_plus_qm;
{
    Object end_1, start, initial_index, previous_number_parsing_state_qm;
    Object number_parsing_state_qm, accept_leading_plus_qm, next_character;
    Object gensymed_symbol_1;
    SI_Long i, gensymed_symbol;

    x_note_fn_call(26,182);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = lengthw(string_1);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    initial_index = disallow_leading_whitespace_qm ? start : 
	    skip_whitespace_in_string(string_1,start,end_1);
    previous_number_parsing_state_qm = Nil;
    number_parsing_state_qm = Nil;
    i = IFIX(initial_index);
    accept_leading_plus_qm =  !TRUEP(disallow_unary_plus_qm) ? T : Nil;
    next_character = Nil;
  next_loop:
    next_character = i == IFIX(end_1) ? FIX((SI_Long)32L) : 
	    FIX(UBYTE_16_ISAREF_1(string_1,i));
    if (accept_leading_plus_qm && IFIX(next_character) == (SI_Long)43L) {
	initial_index = FIXNUM_ADD1(initial_index);
	number_parsing_state_qm = FIX((SI_Long)1L);
    }
    else {
	gensymed_symbol = IFIX(next_character);
	if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) :
		 TRUEP(Nil)) {
	    if ( !TRUEP(number_parsing_state_qm) || 
		    IFIX(number_parsing_state_qm) <= (SI_Long)2L)
		number_parsing_state_qm = FIX((SI_Long)2L);
	    else if (IFIX(number_parsing_state_qm) <= (SI_Long)4L)
		number_parsing_state_qm = FIX((SI_Long)4L);
	    else
		number_parsing_state_qm = FIX((SI_Long)7L);
	}
	else if (EQ(number_parsing_state_qm,Qnil)) {
	    if (EQ(next_character,FIX((SI_Long)45L)))
		number_parsing_state_qm = FIX((SI_Long)1L);
	    else if (EQ(next_character,FIX((SI_Long)46L)))
		number_parsing_state_qm = FIX((SI_Long)3L);
	    else
		number_parsing_state_qm = Qnil;
	}
	else if (EQ(number_parsing_state_qm,FIX((SI_Long)1L)))
	    number_parsing_state_qm = EQ(next_character,FIX((SI_Long)46L)) 
		    ? FIX((SI_Long)3L) : Nil;
	else if (EQ(number_parsing_state_qm,FIX((SI_Long)2L))) {
	    if (EQ(next_character,FIX((SI_Long)46L)))
		number_parsing_state_qm = FIX((SI_Long)4L);
	    else if ( !TRUEP(ignore_exponent_marker_qm) && 
		    (IFIX(next_character) == (SI_Long)101L || 
		    IFIX(next_character) == (SI_Long)69L))
		number_parsing_state_qm = FIX((SI_Long)5L);
	    else if (EQ(next_character,FIX((SI_Long)45L)) || 
		    EQ(next_character,FIX((SI_Long)39L)) || 
		    EQ(next_character,FIX((SI_Long)95L)))
		number_parsing_state_qm = Nil;
	    else {
		gensymed_symbol_1 = next_character;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state_qm = Qinteger;
		else
		    number_parsing_state_qm = Qnil;
	    }
	}
	else if (EQ(number_parsing_state_qm,FIX((SI_Long)4L))) {
	    if ( !TRUEP(ignore_exponent_marker_qm) && 
		    (IFIX(next_character) == (SI_Long)101L || 
		    IFIX(next_character) == (SI_Long)69L))
		number_parsing_state_qm = FIX((SI_Long)5L);
	    else if (EQ(next_character,FIX((SI_Long)46L)))
		number_parsing_state_qm = Nil;
	    else if (EQ(next_character,FIX((SI_Long)45L)) || 
		    EQ(next_character,FIX((SI_Long)39L)) || 
		    EQ(next_character,FIX((SI_Long)95L)))
		number_parsing_state_qm = Nil;
	    else {
		gensymed_symbol_1 = next_character;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state_qm = Qfloat;
		else
		    number_parsing_state_qm = Qnil;
	    }
	}
	else if (EQ(number_parsing_state_qm,FIX((SI_Long)5L)))
	    number_parsing_state_qm = EQ(next_character,FIX((SI_Long)43L)) 
		    || EQ(next_character,FIX((SI_Long)45L)) ? 
		    FIX((SI_Long)6L) : Nil;
	else if (EQ(number_parsing_state_qm,FIX((SI_Long)7L))) {
	    if (EQ(next_character,FIX((SI_Long)46L)))
		number_parsing_state_qm = Nil;
	    else if (EQ(next_character,FIX((SI_Long)45L)) || 
		    EQ(next_character,FIX((SI_Long)39L)) || 
		    EQ(next_character,FIX((SI_Long)95L)))
		number_parsing_state_qm = Nil;
	    else {
		gensymed_symbol_1 = next_character;
		if ( !((SI_Long)97L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)122L || 
			(SI_Long)65L <= IFIX(gensymed_symbol_1) && 
			IFIX(gensymed_symbol_1) <= (SI_Long)90L))
		    number_parsing_state_qm = Qfloat;
		else
		    number_parsing_state_qm = Qnil;
	    }
	}
	else
	    number_parsing_state_qm = Qnil;
	if (FIXNUMP(number_parsing_state_qm)) {
	    if (i >= IFIX(end_1))
		return VALUES_1(Nil);
	}
	else if (i == IFIX(end_1)) {
	    if (memq_function(number_parsing_state_qm,list_constant_1))
		return VALUES_3(number_parsing_state_qm,initial_index,FIX(i));
	    else
		return VALUES_1(Nil);
	}
	else if ( !TRUEP(disallow_junk_qm) && 
		previous_number_parsing_state_qm && (SI_Long)1L <= 
		IFIX(previous_number_parsing_state_qm) && 
		IFIX(previous_number_parsing_state_qm) <= (SI_Long)7L) {
	    gensymed_symbol = (SI_Long)32L;
	    if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		    (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
		    (SI_Long)48L)) : TRUEP(Nil)) {
		if ( !TRUEP(previous_number_parsing_state_qm) || 
			IFIX(previous_number_parsing_state_qm) <= (SI_Long)2L)
		    number_parsing_state_qm = FIX((SI_Long)2L);
		else if (IFIX(previous_number_parsing_state_qm) <= (SI_Long)4L)
		    number_parsing_state_qm = FIX((SI_Long)4L);
		else
		    number_parsing_state_qm = FIX((SI_Long)7L);
	    }
	    else if (EQ(previous_number_parsing_state_qm,Qnil)) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)))
		    number_parsing_state_qm = FIX((SI_Long)1L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state_qm = FIX((SI_Long)3L);
		else
		    number_parsing_state_qm = Qnil;
	    }
	    else if (EQ(previous_number_parsing_state_qm,FIX((SI_Long)1L)))
		number_parsing_state_qm = EQ(FIX((SI_Long)32L),
			FIX((SI_Long)46L)) ? FIX((SI_Long)3L) : Nil;
	    else if (EQ(previous_number_parsing_state_qm,FIX((SI_Long)2L))) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state_qm = FIX((SI_Long)4L);
		else if ( !TRUEP(ignore_exponent_marker_qm) && 
			((SI_Long)32L == (SI_Long)101L || (SI_Long)32L == 
			(SI_Long)69L))
		    number_parsing_state_qm = FIX((SI_Long)5L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state_qm = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state_qm = Qinteger;
		    else
			number_parsing_state_qm = Qnil;
		}
	    }
	    else if (EQ(previous_number_parsing_state_qm,FIX((SI_Long)4L))) {
		if ( !TRUEP(ignore_exponent_marker_qm) && ((SI_Long)32L == 
			(SI_Long)101L || (SI_Long)32L == (SI_Long)69L))
		    number_parsing_state_qm = FIX((SI_Long)5L);
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state_qm = Nil;
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state_qm = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state_qm = Qfloat;
		    else
			number_parsing_state_qm = Qnil;
		}
	    }
	    else if (EQ(previous_number_parsing_state_qm,FIX((SI_Long)5L)))
		number_parsing_state_qm = EQ(FIX((SI_Long)32L),
			FIX((SI_Long)43L)) || EQ(FIX((SI_Long)32L),
			FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
	    else if (EQ(previous_number_parsing_state_qm,FIX((SI_Long)7L))) {
		if (EQ(FIX((SI_Long)32L),FIX((SI_Long)46L)))
		    number_parsing_state_qm = Nil;
		else if (EQ(FIX((SI_Long)32L),FIX((SI_Long)45L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)39L)) || 
			EQ(FIX((SI_Long)32L),FIX((SI_Long)95L)))
		    number_parsing_state_qm = Nil;
		else {
		    gensymed_symbol = (SI_Long)32L;
		    if ( !((SI_Long)97L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)122L || 
			    (SI_Long)65L <= gensymed_symbol && 
			    gensymed_symbol <= (SI_Long)90L))
			number_parsing_state_qm = Qfloat;
		    else
			number_parsing_state_qm = Qnil;
		}
	    }
	    else
		number_parsing_state_qm = Qnil;
	    if (memq_function(number_parsing_state_qm,list_constant_1))
		return VALUES_3(number_parsing_state_qm,initial_index,FIX(i));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    previous_number_parsing_state_qm = number_parsing_state_qm;
    i = i + (SI_Long)1L;
    accept_leading_plus_qm = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Message_illegal_symbol_text_string_empty, Qmessage_illegal_symbol_text_string_empty);

DEFINE_VARIABLE_WITH_SYMBOL(Message_illegal_symbol_text_string_contains_a_newline, Qmessage_illegal_symbol_text_string_contains_a_newline);

DEFINE_VARIABLE_WITH_SYMBOL(Message_illegal_symbol_text_string_contains_ffff, Qmessage_illegal_symbol_text_string_contains_ffff);

DEFINE_VARIABLE_WITH_SYMBOL(Message_illegal_symbol_text_string_contains_fffe, Qmessage_illegal_symbol_text_string_contains_fffe);

DEFINE_VARIABLE_WITH_SYMBOL(Message_illegal_symbol_text_string_too_long, Qmessage_illegal_symbol_text_string_too_long);

/* NON-VALID-SYMBOL-TEXT-STRING-P */
Object non_valid_symbol_text_string_p(printed_representation_text_string)
    Object printed_representation_text_string;
{
    Object length_1, temp;
    SI_Long character_1, i, ab_loop_bind_;

    x_note_fn_call(26,183);
    character_1 = (SI_Long)0L;
    length_1 = lengthw(printed_representation_text_string);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    if (IFIX(length_1) == (SI_Long)0L) {
	temp = Message_illegal_symbol_text_string_empty;
	goto end_1;
    }
    if (FIXNUM_GT(length_1,Maximum_length_for_user_symbols)) {
	temp = Message_illegal_symbol_text_string_too_long;
	goto end_1;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = UBYTE_16_ISAREF_1(printed_representation_text_string,i);
    if (character_1 >= (SI_Long)65534L) {
	temp = character_1 == (SI_Long)65535L ? 
		Message_illegal_symbol_text_string_contains_ffff : 
		Message_illegal_symbol_text_string_contains_fffe;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SIMPLE-SYMBOL-CHARACTER-P */
Object simple_symbol_character_p(wide_character)
    Object wide_character;
{
    x_note_fn_call(26,184);
    return VALUES_1(simple_symbol_character_p_4_dot_0(wide_character) ? ( 
	    !(IFIX(wide_character) == (SI_Long)9L) ? T : Nil) : Qnil);
}

/* SIMPLE-SYMBOL-CHARACTER-P-4.0 */
Object simple_symbol_character_p_4_dot_0(wide_character)
    Object wide_character;
{
    Object unicode, code, extended_code, unicode_1, code_1, temp, row;
    Object gensym_character_code_qm, character_code, char_1;
    Object simple_gensym_character_code, character_or_character_code_qm;
    Object escape_qm;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(26,185);
    unicode = wide_character;
    code = Nil;
    extended_code = Nil;
    unicode_1 = unicode;
    extended_code = Nil;
    code_1 = unicode_1;
    if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == IFIX(code_1) || 
	    (SI_Long)126L == IFIX(code_1) || (SI_Long)92L == IFIX(code_1))) {
	code = unicode_1;
	temp = code;
    }
    else {
	row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
	      gensym_character_code_qm = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      gensym_character_code_qm = Nil;
	POP_SPECIAL();
	if (gensym_character_code_qm) {
	    temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
		    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code_qm))) : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    Gensym_code_for_capital_ligature_oe))
		temp_1 = 'W';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    Gensym_code_for_small_ligature_oe))
		temp_1 = 'w';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    Gensym_code_for_bullet))
		temp_1 = '*';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    Gensym_code_for_small_letter_f_with_hook))
		temp_1 = '&';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    Gensym_code_for_trade_mark_sign))
		temp_1 = ':';
	    else
		temp_1 = TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = (SI_Long)8192L <= IFIX(gensym_character_code_qm) ?
			 IFIX(gensym_character_code_qm) <= (SI_Long)8447L :
			 TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    code = gensym_character_code_qm;
	    temp = code;
	}
	else
	    temp = Nil;
	if (temp);
	else {
	    code = map_unicode_to_gensym_han_character_code(unicode_1);
	    temp = code;
	    if (temp);
	    else {
		row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  gensym_full_row = 
			  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			  IFIX(Row));
		  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
		      gensymed_symbol = gensym_full_row << (SI_Long)8L;
		      gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		      code = FIX(gensymed_symbol + gensymed_symbol_1);
		  }
		  else
		      code = Nil;
		POP_SPECIAL();
		temp = code;
		if (temp);
		else {
		    gensymed_symbol = (SI_Long)63488L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		    extended_code = FIX(gensymed_symbol + gensymed_symbol_1);
		    code = FIX((SI_Long)63232L + (IFIX(unicode_1) >>  -  - 
			    (SI_Long)8L));
		    temp = code;
		}
	    }
	}
    }
    character_code = temp;
    char_1 = Nil;
    if (FIXNUM_EQ(character_code,Gensym_code_for_linebreak))
	result = VALUES_2(Gensym_char_or_code_for_linebreak,
		Gensym_esc_for_linebreak_qm);
    else if (FIXNUM_EQ(character_code,Gensym_code_for_paragraph_break))
	result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		Gensym_esc_for_paragraph_break_qm);
    else {
	if ((SI_Long)32L <= IFIX(character_code) && IFIX(character_code) 
		<= (SI_Long)126L) {
	    simple_gensym_character_code = character_code;
	    temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
		    FIX((SI_Long)64L)) || 
		    FIXNUM_EQ(simple_gensym_character_code,
		    FIX((SI_Long)126L)) || 
		    FIXNUM_EQ(simple_gensym_character_code,FIX((SI_Long)92L)));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = CODE_CHAR(character_code);
	    result = VALUES_2(temp,Nil);
	}
	else {
	    temp = IFIX(character_code) < (SI_Long)256L ? 
		    ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(character_code)) : Nil;
	    if (temp);
	    else if (FIXNUM_EQ(character_code,
		    Gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (FIXNUM_EQ(character_code,
		    Gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (FIXNUM_EQ(character_code,Gensym_code_for_bullet))
		temp = CHR('*');
	    else if (FIXNUM_EQ(character_code,
		    Gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (FIXNUM_EQ(character_code,Gensym_code_for_trade_mark_sign))
		temp = CHR(':');
	    else
		temp = Qnil;
	    char_1 = temp;
	    if (char_1)
		result = VALUES_2(char_1,CHR('~'));
	    else
		result = VALUES_2(character_code,CHR('\\'));
	}
    }
    MVS_2(result,character_or_character_code_qm,escape_qm);
    if (character_or_character_code_qm) {
	if ( !CHARACTERP(escape_qm)) {
	    temp = ALPHANUMERICP(character_or_character_code_qm) ? T : Nil;
	    if (temp);
	    else
		temp = CHAR_EQ(character_or_character_code_qm,CHR('-')) ? 
			T : Nil;
	    if (temp);
	    else
		temp = CHAR_EQ(character_or_character_code_qm,CHR('.')) ? 
			T : Nil;
	    if (temp);
	    else
		temp = CHAR_EQ(character_or_character_code_qm,CHR('\'')) ? 
			T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(CHAR_EQ(character_or_character_code_qm,
			CHR('_')) ? T : Nil);
	}
	else
	    switch (ICHAR_CODE(escape_qm)) {
	      case '@':
		return VALUES_1(Nil);
	      case '~':
		return VALUES_1(ALPHANUMERICP(character_or_character_code_qm) 
			? T : Nil);
	      case '\\':
		return VALUES_1(T);
	      default:
		temp = ALPHANUMERICP(character_or_character_code_qm) ? T : Nil;
		if (temp);
		else
		    temp = CHAR_EQ(character_or_character_code_qm,
			    CHR('-')) ? T : Nil;
		if (temp);
		else
		    temp = CHAR_EQ(character_or_character_code_qm,
			    CHR('.')) ? T : Nil;
		if (temp);
		else
		    temp = CHAR_EQ(character_or_character_code_qm,
			    CHR('\'')) ? T : Nil;
		if (temp)
		    return VALUES_1(temp);
		else
		    return VALUES_1(CHAR_EQ(character_or_character_code_qm,
			    CHR('_')) ? T : Nil);
	    }
    }
    else
	return VALUES_1(Nil);
}

/* SIMPLE-PATHNAME-CHARACTER-P */
Object simple_pathname_character_p(character_1)
    Object character_1;
{
    Object temp;

    x_note_fn_call(26,186);
    temp = simple_symbol_character_p(character_1);
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)92L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)47L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)126L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)58L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)62L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)60L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)93L ? T : Nil;
    if (temp);
    else
	temp = IFIX(character_1) == (SI_Long)91L ? T : Nil;
    return VALUES_1(temp);
}

Object Punctuation_alist = UNBOUND;

static Object Qpunctuation_mark_p;  /* punctuation-mark-p */

/* NOTE-PUNCTUATION-MARKS-AS-SUCH */
Object note_punctuation_marks_as_such(punctuation_alist_1)
    Object punctuation_alist_1;
{
    Object symbol, punctuation_alist_2, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(26,187);
    symbol = Nil;
    punctuation_alist_2 = Nil;
    ab_loop_list_ = punctuation_alist_1;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    punctuation_alist_2 = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_get(symbol,Qpunctuation_mark_p,T);
    note_punctuation_marks_as_such(punctuation_alist_2);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Standard_character_syntax_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_character_syntax_table, Qcurrent_character_syntax_table);

/* LOOK-UP-CHARACTER-SYNTAX-TABLE-ENTRY */
Object look_up_character_syntax_table_entry(unicode_wide_character)
    Object unicode_wide_character;
{
    x_note_fn_call(26,188);
    return assoc_eql(unicode_wide_character,Current_character_syntax_table);
}

/* DONT-SPACE-BEFORE-CHARACTER-P */
Object dont_space_before_character_p(unicode_wide_character)
    Object unicode_wide_character;
{
    Object temp;

    x_note_fn_call(26,189);
    temp = look_up_character_syntax_table_entry(unicode_wide_character);
    return VALUES_1(SECOND(temp));
}

/* DONT-SPACE-AFTER-CHARACTER-P */
Object dont_space_after_character_p(unicode_wide_character)
    Object unicode_wide_character;
{
    Object temp;

    x_note_fn_call(26,190);
    temp = look_up_character_syntax_table_entry(unicode_wide_character);
    return VALUES_1(THIRD(temp));
}

/* REMOVE-SPACE-BEFORE-CHARACTER-P */
Object remove_space_before_character_p(unicode_wide_character)
    Object unicode_wide_character;
{
    x_note_fn_call(26,191);
    return VALUES_1(SIXTH(look_up_character_syntax_table_entry(unicode_wide_character)));
}

/* REMOVE-SPACE-AFTER-CHARACTER-P */
Object remove_space_after_character_p(unicode_wide_character)
    Object unicode_wide_character;
{
    x_note_fn_call(26,192);
    return VALUES_1(SEVENTH(look_up_character_syntax_table_entry(unicode_wide_character)));
}

/* BRACKET-OPEN-OR-CLOSE? */
Object bracket_open_or_close_qm(unicode_wide_character)
    Object unicode_wide_character;
{
    Object temp;

    x_note_fn_call(26,193);
    temp = look_up_character_syntax_table_entry(unicode_wide_character);
    return VALUES_1(FOURTH(temp));
}

Object Ellipsis_text_string = UNBOUND;

Object Ellipsis_text_string_length = UNBOUND;

Object Punctuation_mark_p_prop = UNBOUND;

Object Type_of_syntactic_anomaly_prop = UNBOUND;

/* TWRITE-SYMBOL */
Object twrite_symbol varargs_1(int, n)
{
    Object symbol;
    Object do_not_downcase_qm, which_characters_not_to_downcase_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temporary_text_string, temporary_gensym_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(26,194);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    do_not_downcase_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    which_characters_not_to_downcase_qm = do_not_downcase_qm ? Kall : Nil;
    if (EQ(Current_twriting_output_type,Qwide_string))
	return twrite_symbol_into_text_string(2,symbol,
		which_characters_not_to_downcase_qm);
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
		  twrite_symbol_into_text_string(2,symbol,
			  which_characters_not_to_downcase_qm);
		  temporary_text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temporary_gensym_string = 
		wide_string_to_gensym_string(temporary_text_string);
	twrite_portion_of_gensym_string_unparsably(temporary_gensym_string,
		Nil,Nil);
	reclaim_text_string(temporary_text_string);
	return reclaim_gensym_string(temporary_gensym_string);
    }
}

static Object string_constant_10;  /* "A " */

static Object string_constant_11;  /* "a " */

static Object string_constant_12;  /* "An " */

static Object string_constant_13;  /* "an " */

/* WRITE-SYMBOL-WITH-A-OR-AN */
Object write_symbol_with_a_or_an varargs_1(int, n)
{
    Object symbol;
    Object capitalize_qm, symbol_name_text_string_1, temp;
    SI_Long wide_character, code;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,195);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    capitalize_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    symbol_name_text_string_1 = symbol_name_text_string(symbol);
    wide_character = UBYTE_16_ISAREF_1(symbol_name_text_string_1,(SI_Long)0L);
    code = wide_character;
    if (code < (SI_Long)127L)
	temp = (SI_Long)97L <= code && code <= (SI_Long)122L ? FIX(code + 
		(SI_Long)-32L) : FIX(code);
    else {
	temp = unicode_uppercase_if_lowercase(FIX(code));
	if (temp);
	else
	    temp = FIX(code);
    }
    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
	    FIXNUM_LE(temp,FIX((SI_Long)127L))))
	temp = capitalize_qm ? string_constant_10 : string_constant_11;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 65:
	  case 69:
	  case 73:
	  case 79:
	  case 85:
	    temp = capitalize_qm ? string_constant_12 : string_constant_13;
	    break;
	  default:
	    temp = capitalize_qm ? string_constant_10 : string_constant_11;
	    break;
	}
    twrite_general_string(temp);
    return twrite_symbol(1,symbol);
}

static Object Qtype_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

/* TWRITE-SYMBOL-INTO-TEXT-STRING */
Object twrite_symbol_into_text_string varargs_1(int, n)
{
    Object symbol;
    Object which_characters_not_to_downcase_qm, string_1, string_length;
    Object symbol_name_text_string_1, symbol_name_length, this_char;
    Object ab_loop_it_, class_qualified_symbol_qm, ellipsis_parsing_state;
    Object quote_characters_as_appropriate_qm, i_1, character_1;
    Object previous_character_qm, temp, temp_1, schar_arg_2, schar_new_value;
    Object simple_or_wide_character, code, thing_1;
    SI_Long i, ab_loop_bind_, thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,196);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    which_characters_not_to_downcase_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    string_1 = symbol_name_text_string(symbol);
    string_length = text_string_length(string_1);
    if (EQ(SYMBOL_PACKAGE(symbol),Keyword_package_1)) {
	symbol_name_text_string_1 = symbol_name_text_string(symbol);
	symbol_name_length = text_string_length(symbol_name_text_string_1);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(symbol_name_length);
	this_char = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	this_char = FIX(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i));
	ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + (SI_Long)1L < 
		IFIX(symbol_name_length) ? 
		(UBYTE_16_ISAREF_1(symbol_name_text_string_1,i + 
		(SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
	if (ab_loop_it_) {
	    class_qualified_symbol_qm = ab_loop_it_;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	class_qualified_symbol_qm = Qnil;
      end_1:;
    }
    else
	class_qualified_symbol_qm = Nil;
    ellipsis_parsing_state = FIX((SI_Long)0L);
    quote_characters_as_appropriate_qm = Write_symbols_parsably_qm ? ( 
	    !TRUEP(class_qualified_symbol_qm) ? ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qpunctuation_mark_p)) ? T : Nil) : Nil) : Nil;
    if ( !EQ(which_characters_not_to_downcase_qm,Kall) || 
	    quote_characters_as_appropriate_qm) {
	i_1 = FIX((SI_Long)0L);
	character_1 = Nil;
	previous_character_qm = Nil;
      next_loop_1:
	if (FIXNUM_GE(i_1,string_length))
	    goto end_loop_1;
	temp = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(i_1)));
	i_1 = FIXNUM_ADD1(i_1);
	character_1 = temp;
	ellipsis_parsing_state = FIXNUM_NE(ellipsis_parsing_state,
		Ellipsis_text_string_length) && IFIX(character_1) == 
		UBYTE_16_ISAREF_1(Ellipsis_text_string,
		IFIX(ellipsis_parsing_state)) ? 
		FIXNUM_ADD1(ellipsis_parsing_state) : FIX((SI_Long)0L);
	if (quote_characters_as_appropriate_qm && ( 
		!TRUEP(simple_symbol_character_p(character_1)) || 
		lower_case_pw(character_1) || 
		FIXNUM_EQ(ellipsis_parsing_state,
		Ellipsis_text_string_length) || (IFIX(i_1) == (SI_Long)1L ?
		 
		TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qtype_of_syntactic_anomaly)) : TRUEP(Nil)))) {
	    if (FIXNUM_EQ(ellipsis_parsing_state,Ellipsis_text_string_length))
		ellipsis_parsing_state = FIX((SI_Long)1L);
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = (SI_Long)64L;
		twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = (SI_Long)64L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
	    }
	}
	if (EQ(which_characters_not_to_downcase_qm,Kall))
	    temp = T;
	else if (EQ(which_characters_not_to_downcase_qm,Kfirst))
	    temp = IFIX(i_1) == (SI_Long)1L ? T : Nil;
	else if (EQ(which_characters_not_to_downcase_qm,Kfirst_of_each_word)) {
	    temp =  !TRUEP(previous_character_qm) ? T : Nil;
	    if (temp);
	    else
		temp = word_separator_p(previous_character_qm);
	}
	else if (EQ(which_characters_not_to_downcase_qm,Knone))
	    temp = Nil;
	else
	    temp = Nil;
	if (temp)
	    simple_or_wide_character = character_1;
	else {
	    code = character_1;
	    if (IFIX(code) < (SI_Long)127L)
		simple_or_wide_character = (SI_Long)65L <= IFIX(code) && 
			IFIX(code) <= (SI_Long)90L ? FIX(IFIX(code) + 
			(SI_Long)32L) : code;
	    else {
		simple_or_wide_character = 
			unicode_lowercase_if_uppercase(code);
		if (simple_or_wide_character);
		else
		    simple_or_wide_character = code;
	    }
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character;
	    twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) 
		    : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
	previous_character_qm = character_1;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return twrite_portion_of_wide_string_unparsably(string_1,
		FIX((SI_Long)0L),string_length);
}

/* TWRITE-GENERAL-STRING */
Object twrite_general_string(string_1)
    Object string_1;
{
    x_note_fn_call(26,197);
    if (Write_strings_parsably_qm)
	twrite_portion_of_string_parsably(string_1,Nil,Nil);
    else
	twrite_portion_of_string_unparsably(string_1,Nil,Nil);
    return VALUES_1(Nil);
}

/* TWRITE-BEGINNING-OF-WIDE-STRING */
Object twrite_beginning_of_wide_string(wide_string,first_n_characters)
    Object wide_string, first_n_characters;
{
    x_note_fn_call(26,198);
    if (Write_strings_parsably_qm) {
	if (EQ(Current_twriting_output_type,Qwide_string))
	    twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
		    FIX((SI_Long)0L),first_n_characters);
	else
	    twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
		    FIX((SI_Long)0L),first_n_characters);
    }
    else if (EQ(Current_twriting_output_type,Qwide_string))
	twrite_beginning_of_wide_string_unparsably_to_current_wide_string(wide_string,
		first_n_characters);
    else
	twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
		FIX((SI_Long)0L),first_n_characters);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-STRING-PARSABLY */
Object twrite_portion_of_string_parsably(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    x_note_fn_call(26,199);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	twrite_portion_of_wide_string_parsably(string_1,start_qm,end_qm);
    else
	twrite_portion_of_gensym_string_parsably(string_1,start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY */
Object twrite_portion_of_wide_string_parsably(wide_string,start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    x_note_fn_call(26,200);
    if (EQ(Current_twriting_output_type,Qwide_string))
	twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
		start_qm,end_qm);
    else
	twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
		start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY-TO-CURRENT-WIDE-STRING */
Object twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, temp_1, aref_arg_2, gensymed_symbol, gensymed_symbol_2;
    SI_Long wide_character, start, end_1, i, j, ab_loop_bind_, arg, arg_1;
    SI_Long arg_2, gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long incff_1_arg, fill_pointer_for_current_wide_string_new_value;
    char temp_2;

    x_note_fn_call(26,201);
    wide_character = (SI_Long)0L;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = lengthw(wide_string);
    end_1 = IFIX(temp);
    i = start;
    if ( !(IFIX(Fill_pointer_for_current_wide_string) + (end_1 - start) + 
	    (SI_Long)2L < IFIX(Total_length_of_current_wide_string)))
	extend_current_wide_string(FIX(IFIX(Fill_pointer_for_current_wide_string) 
		+ (end_1 - start) + (SI_Long)2L));
    temp_1 = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)34L);
    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp_1;
  next_loop:
    if ( !(i < end_1))
	goto end_loop;
    j = i;
    ab_loop_bind_ = end_1;
  next_loop_1:
    if (j >= ab_loop_bind_)
	goto end_loop_1;
    wide_character = UBYTE_16_ISAREF_1(wide_string,j);
    if (wide_character == (SI_Long)64L || wide_character == (SI_Long)34L) {
	if ( !(i == j)) {
	    if (EQ(wide_string,Current_wide_string)) {
		if (i == j)
		    temp_2 = TRUEP(T);
		else {
		    temp_2 = i < 
			    IFIX(Fill_pointer_for_current_wide_string) ? 
			    IFIX(Fill_pointer_for_current_wide_string) < j 
			    : TRUEP(Qnil);
		    if (temp_2);
		    else {
			arg = IFIX(Fill_pointer_for_current_wide_string);
			arg_1 = i;
			arg_2 = IFIX(Fill_pointer_for_current_wide_string) 
				+ (j - i);
			temp_2 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		    }
		    if (temp_2) {
			copy_byte_vector_16_portion_carefully(wide_string,
				FIX(i),Current_wide_string,
				Fill_pointer_for_current_wide_string,FIX(j 
				- i));
			temp_2 = TRUEP(T);
		    }
		    else
			temp_2 = TRUEP(Qnil);
		}
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2);
	    else {
		gensymed_symbol = wide_string;
		gensymed_symbol_1 = i;
		gensymed_symbol_2 = Current_wide_string;
		gensymed_symbol_3 = IFIX(Fill_pointer_for_current_wide_string);
		gensymed_symbol_4 = j - i;
		INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			gensymed_symbol_1,
			UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			gensymed_symbol_3,gensymed_symbol_4);
	    }
	    incff_1_arg = j - i;
	    fill_pointer_for_current_wide_string_new_value = 
		    IFIX(Fill_pointer_for_current_wide_string) + incff_1_arg;
	    Fill_pointer_for_current_wide_string = 
		    FIX(fill_pointer_for_current_wide_string_new_value);
	}
	if ( !(IFIX(Fill_pointer_for_current_wide_string) + (end_1 - j) + 
		(SI_Long)2L < IFIX(Total_length_of_current_wide_string)))
	    extend_current_wide_string(FIX(IFIX(Fill_pointer_for_current_wide_string) 
		    + (end_1 - j) + (SI_Long)2L));
	temp_1 = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)64L);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp_1;
	temp_1 = Current_wide_string;
	aref_arg_2 = Fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),wide_character);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	Fill_pointer_for_current_wide_string = temp_1;
	i = j + (SI_Long)1L;
	goto end_2;
    }
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    if (EQ(wide_string,Current_wide_string)) {
	if (i == end_1)
	    temp_2 = TRUEP(T);
	else {
	    temp_2 = i < IFIX(Fill_pointer_for_current_wide_string) ? 
		    IFIX(Fill_pointer_for_current_wide_string) < end_1 : 
		    TRUEP(Qnil);
	    if (temp_2);
	    else {
		arg = IFIX(Fill_pointer_for_current_wide_string);
		arg_1 = i;
		arg_2 = IFIX(Fill_pointer_for_current_wide_string) + 
			(end_1 - i);
		temp_2 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp_2) {
		copy_byte_vector_16_portion_carefully(wide_string,FIX(i),
			Current_wide_string,
			Fill_pointer_for_current_wide_string,FIX(end_1 - i));
		temp_2 = TRUEP(T);
	    }
	    else
		temp_2 = TRUEP(Qnil);
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2);
    else {
	gensymed_symbol = wide_string;
	gensymed_symbol_1 = i;
	gensymed_symbol_2 = Current_wide_string;
	gensymed_symbol_3 = IFIX(Fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = end_1 - i;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = end_1 - i;
    fill_pointer_for_current_wide_string_new_value = 
	    IFIX(Fill_pointer_for_current_wide_string) + incff_1_arg;
    Fill_pointer_for_current_wide_string = 
	    FIX(fill_pointer_for_current_wide_string_new_value);
    i = end_1;
  end_2:;
    goto next_loop;
  end_loop:
    temp_1 = Current_wide_string;
    aref_arg_2 = Fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)34L);
    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
    Fill_pointer_for_current_wide_string = temp_1;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY-TO-CURRENT-GENSYM-STRING */
Object twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long wide_character, start, end_1, i, ab_loop_bind_, thing;

    x_note_fn_call(26,202);
    wide_character = (SI_Long)0L;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = lengthw(wide_string);
    end_1 = IFIX(temp);
    i = start;
    ab_loop_bind_ = end_1;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)34L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)34L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    if (wide_character == (SI_Long)64L || wide_character == (SI_Long)91L 
	    || wide_character == (SI_Long)96L || wide_character == 
	    (SI_Long)34L) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)64L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)64L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = wide_character;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)34L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)34L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-GENSYM-STRING-PARSABLY */
Object twrite_portion_of_gensym_string_parsably(gensym_string,start_qm,end_qm)
    Object gensym_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long start, end_1, i, ab_loop_bind_;
    char character_1;
    char simple_qm;
    char thing;
    char thing_1;

    x_note_fn_call(26,203);
    character_1 = 'a';
    simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string) : 
		length(gensym_string);
    end_1 = IFIX(temp);
    i = start;
    ab_loop_bind_ = end_1;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = '\"';
	twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = '\"';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = simple_qm ? ISCHAR(gensym_string,i) : ICHAR(gensym_string,i);
    if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('@')) || 
	    CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\"'))) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = '@';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = '@';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = character_1;
	twrite_wide_character(CHARACTERP(CHAR_TO_CHARACTER(thing_1)) ? 
		CHAR_CODE(CHAR_TO_CHARACTER(thing_1)) : 
		CHAR_TO_CHARACTER(thing_1));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = character_1;
	schar_new_value = CODE_CHAR(CHARACTERP(CHAR_TO_CHARACTER(thing_1)) 
		? CHAR_CODE(CHAR_TO_CHARACTER(thing_1)) : 
		CHAR_TO_CHARACTER(thing_1));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = '\"';
	twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = '\"';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-STRING-UNPARSABLY */
Object twrite_portion_of_string_unparsably(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    x_note_fn_call(26,204);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	twrite_portion_of_wide_string_unparsably(string_1,start_qm,end_qm);
    else
	twrite_portion_of_gensym_string_unparsably(string_1,start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY */
Object twrite_portion_of_wide_string_unparsably(wide_string,start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    x_note_fn_call(26,205);
    if (EQ(Current_twriting_output_type,Qwide_string))
	twrite_portion_of_wide_string_unparsably_to_current_wide_string(wide_string,
		start_qm,end_qm);
    else
	twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
		start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-WIDE-STRING */
Object twrite_portion_of_wide_string_unparsably_to_current_wide_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object start, end_1, gensymed_symbol, gensymed_symbol_2, incff_1_arg;
    Object fill_pointer_for_current_wide_string_new_value;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(26,206);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end_1 = end_qm;
    if (end_1);
    else
	end_1 = lengthw(wide_string);
    if ( !FIXNUM_LT(FIXNUM_ADD(Fill_pointer_for_current_wide_string,
	    FIXNUM_MINUS(end_1,start)),Total_length_of_current_wide_string))
	extend_current_wide_string(FIXNUM_ADD(Fill_pointer_for_current_wide_string,
		FIXNUM_MINUS(end_1,start)));
    if (EQ(wide_string,Current_wide_string)) {
	if (FIXNUM_EQ(start,end_1))
	    temp = TRUEP(T);
	else {
	    temp = FIXNUM_LT(start,Fill_pointer_for_current_wide_string) ? 
		    FIXNUM_LT(Fill_pointer_for_current_wide_string,end_1) :
		     TRUEP(Qnil);
	    if (temp);
	    else {
		arg = IFIX(Fill_pointer_for_current_wide_string);
		arg_1 = IFIX(start);
		arg_2 = 
			IFIX(FIXNUM_ADD(Fill_pointer_for_current_wide_string,
			FIXNUM_MINUS(end_1,start)));
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(wide_string,start,
			Current_wide_string,
			Fill_pointer_for_current_wide_string,
			FIXNUM_MINUS(end_1,start));
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	gensymed_symbol = wide_string;
	gensymed_symbol_1 = IFIX(start);
	gensymed_symbol_2 = Current_wide_string;
	gensymed_symbol_3 = IFIX(Fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = IFIX(FIXNUM_MINUS(end_1,start));
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = FIXNUM_MINUS(end_1,start);
    fill_pointer_for_current_wide_string_new_value = 
	    FIXNUM_ADD(Fill_pointer_for_current_wide_string,incff_1_arg);
    Fill_pointer_for_current_wide_string = 
	    fill_pointer_for_current_wide_string_new_value;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-GENSYM-STRING */
Object twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, char_1, simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long start, end_1, i, ab_loop_bind_;

    x_note_fn_call(26,207);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = lengthw(wide_string);
    end_1 = IFIX(temp);
    i = start;
    ab_loop_bind_ = end_1;
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    simple_or_wide_character = IFIX(char_1) == (SI_Long)8232L ? CHR('\n') :
	     char_1;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-GENSYM-STRING-UNPARSABLY */
Object twrite_portion_of_gensym_string_unparsably(gensym_string,start_qm,
	    end_qm)
    Object gensym_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long start, end_1, i, ab_loop_bind_;
    char simple_qm;
    char simple_or_wide_character, thing;

    x_note_fn_call(26,208);
    simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = simple_qm ? SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string) : 
		length(gensym_string);
    end_1 = IFIX(temp);
    i = start;
    ab_loop_bind_ = end_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    simple_or_wide_character = simple_qm ? ISCHAR(gensym_string,i) : 
	    ICHAR(gensym_string,i);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
		CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
		CHAR_TO_CHARACTER(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
		CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
		CHAR_TO_CHARACTER(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* TWRITE-BEGINNING-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-WIDE-STRING */
Object twrite_beginning_of_wide_string_unparsably_to_current_wide_string(wide_string,
	    first_n_characters)
    Object wide_string, first_n_characters;
{
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, incff_1_arg;
    SI_Long fill_pointer_for_current_wide_string_new_value;
    char temp;

    x_note_fn_call(26,209);
    if ( !FIXNUM_LT(FIXNUM_ADD(Fill_pointer_for_current_wide_string,
	    first_n_characters),Total_length_of_current_wide_string))
	extend_current_wide_string(FIXNUM_ADD(Fill_pointer_for_current_wide_string,
		first_n_characters));
    if (EQ(wide_string,Current_wide_string)) {
	if ((SI_Long)0L == IFIX(first_n_characters))
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < 
		    IFIX(Fill_pointer_for_current_wide_string) ? 
		    FIXNUM_LT(Fill_pointer_for_current_wide_string,
		    first_n_characters) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = IFIX(Fill_pointer_for_current_wide_string);
		arg_1 = (SI_Long)0L;
		arg_2 = IFIX(Fill_pointer_for_current_wide_string) + 
			(IFIX(first_n_characters) - (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(wide_string,
			FIX((SI_Long)0L),Current_wide_string,
			Fill_pointer_for_current_wide_string,
			FIX(IFIX(first_n_characters) - (SI_Long)0L));
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	gensymed_symbol = wide_string;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = Current_wide_string;
	gensymed_symbol_3 = IFIX(Fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = IFIX(first_n_characters) - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = IFIX(first_n_characters) - (SI_Long)0L;
    fill_pointer_for_current_wide_string_new_value = 
	    IFIX(Fill_pointer_for_current_wide_string) + incff_1_arg;
    Fill_pointer_for_current_wide_string = 
	    FIX(fill_pointer_for_current_wide_string_new_value);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Wide_twrite_fixnum_buffer, Qwide_twrite_fixnum_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Most_negative_fixnum_as_string, Qmost_negative_fixnum_as_string);

DEFINE_VARIABLE_WITH_SYMBOL(Length_of_most_negative_fixnum_as_string, Qlength_of_most_negative_fixnum_as_string);

/* TWRITE-FIXNUM-INTO-WIDE-STRING */
Object twrite_fixnum_into_wide_string(fixnum_to_write_init,wide_string,
	    start_index_init)
    Object fixnum_to_write_init, wide_string, start_index_init;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object write_strings_parsably_qm, result_length, gensymed_symbol;
    Object gensymed_symbol_2, temp, buffer, aref_new_value_1;
    SI_Long fixnum_to_write, start_index, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, positive_fixnum, last_index, digit_count;
    SI_Long number, next, digit, temp_1, source_start, result_length_1;
    Declare_special(6);

    x_note_fn_call(26,210);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    start_index = IFIX(start_index_init);
    if (fixnum_to_write == IFIX(Most_negative_fixnum)) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		5);
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
		  4);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    3);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      2);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			1);
		  write_strings_parsably_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			  0);
		    result_length = Length_of_most_negative_fixnum_as_string;
		    twrite_general_string(Most_negative_fixnum_as_string);
		    gensymed_symbol = Current_wide_string;
		    gensymed_symbol_1 = (SI_Long)0L;
		    gensymed_symbol_2 = wide_string;
		    gensymed_symbol_3 = start_index;
		    gensymed_symbol_4 = IFIX(result_length) - (SI_Long)0L;
		    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			    gensymed_symbol_1,
			    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			    gensymed_symbol_3,gensymed_symbol_4);
		    temp = result_length;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else {
	positive_fixnum = fixnum_to_write < (SI_Long)0L ?  - 
		fixnum_to_write : fixnum_to_write;
	buffer = Wide_twrite_fixnum_buffer;
	last_index = IFIX(FIXNUM_SUB1(Length_of_wide_twrite_fixnum_buffer));
	digit_count = (SI_Long)0L;
	number = positive_fixnum;
	next = (SI_Long)0L;
	digit = (SI_Long)0L;
      next_loop:
	temp_1 = number / (SI_Long)10L;
	next = temp_1;
	digit = number - next * (SI_Long)10L;
	aref_arg_2 = last_index - digit_count;
	gensymed_symbol_1 = digit;
	aref_new_value_1 = gensymed_symbol_1 >= (SI_Long)0L && 
		gensymed_symbol_1 < (SI_Long)10L ? FIX((SI_Long)48L + 
		gensymed_symbol_1) : Nil;
	UBYTE_16_ISASET_1(buffer,aref_arg_2,IFIX(aref_new_value_1));
	digit_count = digit_count + (SI_Long)1L;
	if ((SI_Long)0L == next)
	    goto end_loop;
	number = next;
	goto next_loop;
      end_loop:;
	source_start = IFIX(Length_of_wide_twrite_fixnum_buffer) - digit_count;
	result_length_1 = digit_count;
	if (fixnum_to_write < (SI_Long)0L) {
	    UBYTE_16_ISASET_1(wide_string,start_index,(SI_Long)45L);
	    start_index = start_index + (SI_Long)1L;
	    result_length_1 = result_length_1 + (SI_Long)1L;
	}
	gensymed_symbol = Wide_twrite_fixnum_buffer;
	gensymed_symbol_1 = source_start;
	gensymed_symbol_2 = wide_string;
	gensymed_symbol_3 = start_index;
	gensymed_symbol_4 = IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		source_start;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	temp = FIX(result_length_1);
    }
    return VALUES_1(temp);
}

/* TWRITE-FIXNUM */
Object twrite_fixnum(fixnum_to_write_init)
    Object fixnum_to_write_init;
{
    Object write_strings_parsably_qm, temp, schar_arg_2, temp_1, buffer;
    SI_Long fixnum_to_write, positive_fixnum, last_index, digit_count, number;
    SI_Long next, digit, temp_2, aref_arg_2, gensymed_symbol;
    Declare_special(1);

    x_note_fn_call(26,211);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    if (fixnum_to_write == IFIX(Most_negative_fixnum)) {
	write_strings_parsably_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  twrite_general_string(Most_negative_fixnum_as_string);
	POP_SPECIAL();
    }
    else {
	if (fixnum_to_write < (SI_Long)0L) {
	    if (EQ(Current_twriting_output_type,Qwide_string))
		twrite_wide_character(FIX((SI_Long)45L));
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		temp_1 = CHR('-');
		SET_SCHAR(temp,schar_arg_2,temp_1);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	    positive_fixnum =  - fixnum_to_write;
	}
	else
	    positive_fixnum = fixnum_to_write;
	buffer = Wide_twrite_fixnum_buffer;
	last_index = IFIX(FIXNUM_SUB1(Length_of_wide_twrite_fixnum_buffer));
	digit_count = (SI_Long)0L;
	number = positive_fixnum;
	next = (SI_Long)0L;
	digit = (SI_Long)0L;
      next_loop:
	temp_2 = number / (SI_Long)10L;
	next = temp_2;
	digit = number - next * (SI_Long)10L;
	aref_arg_2 = last_index - digit_count;
	gensymed_symbol = digit;
	temp = gensymed_symbol >= (SI_Long)0L && gensymed_symbol < 
		(SI_Long)10L ? FIX((SI_Long)48L + gensymed_symbol) : Nil;
	UBYTE_16_ISASET_1(buffer,aref_arg_2,IFIX(temp));
	digit_count = digit_count + (SI_Long)1L;
	if ((SI_Long)0L == next)
	    goto end_loop;
	number = next;
	goto next_loop;
      end_loop:;
	if (EQ(Current_twriting_output_type,Qwide_string))
	    twrite_portion_of_wide_string_unparsably_to_current_wide_string(Wide_twrite_fixnum_buffer,
		    FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		    digit_count),Length_of_wide_twrite_fixnum_buffer);
	else
	    twrite_portion_of_string_unparsably(Wide_twrite_fixnum_buffer,
		    FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		    digit_count),Length_of_wide_twrite_fixnum_buffer);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Twrite_fixnum_buffer, Qtwrite_fixnum_buffer);

/* TWRITE-POSITIVE-FIXNUM */
Object twrite_positive_fixnum(fixnum_to_write_init)
    Object fixnum_to_write_init;
{
    Object buffer, aref_new_value;
    SI_Long fixnum_to_write, last_index, digit_count, number, next, digit;
    SI_Long temp, aref_arg_2, gensymed_symbol;

    x_note_fn_call(26,212);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    buffer = Wide_twrite_fixnum_buffer;
    last_index = IFIX(FIXNUM_SUB1(Length_of_wide_twrite_fixnum_buffer));
    digit_count = (SI_Long)0L;
    number = fixnum_to_write;
    next = (SI_Long)0L;
    digit = (SI_Long)0L;
  next_loop:
    temp = number / (SI_Long)10L;
    next = temp;
    digit = number - next * (SI_Long)10L;
    aref_arg_2 = last_index - digit_count;
    gensymed_symbol = digit;
    aref_new_value = gensymed_symbol >= (SI_Long)0L && gensymed_symbol < 
	    (SI_Long)10L ? FIX((SI_Long)48L + gensymed_symbol) : Nil;
    UBYTE_16_ISASET_1(buffer,aref_arg_2,IFIX(aref_new_value));
    digit_count = digit_count + (SI_Long)1L;
    if ((SI_Long)0L == next)
	goto end_loop;
    number = next;
    goto next_loop;
  end_loop:;
    if (EQ(Current_twriting_output_type,Qwide_string))
	twrite_portion_of_wide_string_unparsably_to_current_wide_string(Wide_twrite_fixnum_buffer,
		FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		digit_count),Length_of_wide_twrite_fixnum_buffer);
    else
	twrite_portion_of_string_unparsably(Wide_twrite_fixnum_buffer,
		FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		digit_count),Length_of_wide_twrite_fixnum_buffer);
    return VALUES_1(Nil);
}

/* TWRITE-POSITIVE-FIXNUM-IN-RADIX */
Object twrite_positive_fixnum_in_radix(fixnum_to_write_init,radix_init)
    Object fixnum_to_write_init, radix_init;
{
    Object buffer;
    SI_Long fixnum_to_write, radix, last_index, digit_count, number, next;
    SI_Long digit, temp, aref_arg_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long aref_new_value;

    x_note_fn_call(26,213);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    radix = IFIX(radix_init);
    buffer = Wide_twrite_fixnum_buffer;
    last_index = IFIX(FIXNUM_SUB1(Length_of_wide_twrite_fixnum_buffer));
    digit_count = (SI_Long)0L;
    number = fixnum_to_write;
    next = (SI_Long)0L;
    digit = (SI_Long)0L;
  next_loop:
    temp = number / radix;
    next = temp;
    digit = number - next * radix;
    aref_arg_2 = last_index - digit_count;
    gensymed_symbol = digit;
    gensymed_symbol_1 = radix;
    if ((SI_Long)2L <= gensymed_symbol_1 && gensymed_symbol_1 <= 
	    (SI_Long)36L && gensymed_symbol >= (SI_Long)0L && 
	    gensymed_symbol < gensymed_symbol_1) {
	gensymed_symbol_1 = gensymed_symbol < (SI_Long)10L ? (SI_Long)48L :
		 (SI_Long)55L;
	aref_new_value = gensymed_symbol_1 + gensymed_symbol;
    }
    else
	aref_new_value = (SI_Long)63L;
    UBYTE_16_ISASET_1(buffer,aref_arg_2,aref_new_value);
    digit_count = digit_count + (SI_Long)1L;
    if ((SI_Long)0L == next)
	goto end_loop;
    number = next;
    goto next_loop;
  end_loop:;
    if (EQ(Current_twriting_output_type,Qwide_string))
	twrite_portion_of_wide_string_unparsably_to_current_wide_string(Wide_twrite_fixnum_buffer,
		FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		digit_count),Length_of_wide_twrite_fixnum_buffer);
    else
	twrite_portion_of_string_unparsably(Wide_twrite_fixnum_buffer,
		FIX(IFIX(Length_of_wide_twrite_fixnum_buffer) - 
		digit_count),Length_of_wide_twrite_fixnum_buffer);
    return VALUES_1(Nil);
}

/* TWRITE-POSITIVE-BIGNUM */
Object twrite_positive_bignum(positive_bignum)
    Object positive_bignum;
{
    Object temp, quotient, remainder_1, simple_or_wide_character, thing;
    Object temp_1, schar_arg_2, schar_new_value, rem_2;
    SI_Long rem_1;
    Object result;

    x_note_fn_call(26,214);
    temp = FIX((SI_Long)9L);
    if (NUM_GT(positive_bignum,temp)) {
	result = lfloor(positive_bignum,FIX((SI_Long)10L));
	MVS_2(result,quotient,remainder_1);
	rem_1 = IFIX(coerce_number_to_fixnum(remainder_1));
	if (NUM_LE(quotient,Most_positive_fixnum))
	    twrite_positive_fixnum(quotient);
	else
	    twrite_positive_bignum(quotient);
	simple_or_wide_character = CODE_CHAR(FIX((SI_Long)48L + rem_1));
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else {
	rem_2 = coerce_number_to_fixnum(positive_bignum);
	simple_or_wide_character = CODE_CHAR(FIX((SI_Long)48L + IFIX(rem_2)));
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
}

/* TWRITE-POSITIVE-BIGNUM-IN-RADIX */
Object twrite_positive_bignum_in_radix(positive_bignum,radix_init)
    Object positive_bignum, radix_init;
{
    Object quotient, remainder_1, simple_or_wide_character, thing, temp;
    Object schar_arg_2, schar_new_value, rem_2;
    SI_Long radix, rem_1;
    Object result;

    x_note_fn_call(26,215);
    radix = IFIX(radix_init);
    if (NUM_GE(positive_bignum,FIX(radix))) {
	result = lfloor(positive_bignum,FIX(radix));
	MVS_2(result,quotient,remainder_1);
	rem_1 = IFIX(coerce_number_to_fixnum(remainder_1));
	if (NUM_LE(quotient,Most_positive_fixnum))
	    twrite_positive_fixnum_in_radix(quotient,FIX(radix));
	else
	    twrite_positive_bignum_in_radix(quotient,FIX(radix));
	simple_or_wide_character = digit_char(FIX(rem_1),FIX(radix),_);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else {
	rem_2 = coerce_number_to_fixnum(positive_bignum);
	simple_or_wide_character = digit_char(rem_2,FIX(radix),_);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
}

/* TWRITE-N-DIGIT-NUMBER-WITH-0-PAD */
Object twrite_n_digit_number_with_0_pad(n_1,number)
    Object n_1, number;
{
    Object num, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp, digits, digit, ab_loop_list_, simple_or_wide_character, thing;
    Object temp_1, schar_arg_2, schar_new_value;
    SI_Long i, ab_loop_bind_, gensymed_symbol;

    x_note_fn_call(26,216);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(n_1);
    num = number;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	num = chestnut_floorf_function(num,FIX((SI_Long)10L));
    ab_loopvar__2 = gensym_cons_1(chestnut_modf_function(num,
	    FIX((SI_Long)10L)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    digits = nreverse(temp);
    digit = Nil;
    ab_loop_list_ = digits;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    digit = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = IFIX(digit);
    simple_or_wide_character = gensymed_symbol >= (SI_Long)0L && 
	    gensymed_symbol < (SI_Long)10L ? FIX((SI_Long)48L + 
	    gensymed_symbol) : Nil;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_1 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_1;
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(digits);
    return VALUES_1(Nil);
}

static Object string_constant_14;  /* "-9223372036854775808" */

/* TWRITE-LONG-FUNCTION */
Object twrite_long_function(long_to_write)
    Object long_to_write;
{
    Object write_strings_parsably_qm, temp, temp_1, schar_arg_2;
    SI_int64 positive_long;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(26,217);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (NUM_EQ(long_to_write,Most_negative_int64)) {
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      twrite_general_string(string_constant_14);
	    POP_SPECIAL();
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(long_to_write,temp)) {
		if (EQ(Current_twriting_output_type,Qwide_string))
		    twrite_wide_character(FIX((SI_Long)45L));
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_1 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    temp = CHR('-');
		    SET_SCHAR(temp_1,schar_arg_2,temp);
		    temp_1 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_1;
		}
		temp = negate(long_to_write);
		positive_long = INTEGER_TO_INT64(temp);
	    }
	    else
		positive_long = INTEGER_TO_INT64(long_to_write);
	    twrite_positive_bignum_in_radix(INT64_TO_INTEGER(positive_long),
		    FIX((SI_Long)10L));
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object string_constant_15;  /* "L" */

/* TWRITE-LONG */
Object twrite_long(long_to_write)
    Object long_to_write;
{
    Object write_strings_parsably_qm, temp, temp_1, schar_arg_2;
    SI_int64 positive_long;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(26,218);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (NUM_EQ(long_to_write,Most_negative_int64)) {
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      twrite_general_string(string_constant_14);
	    POP_SPECIAL();
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(long_to_write,temp)) {
		if (EQ(Current_twriting_output_type,Qwide_string))
		    twrite_wide_character(FIX((SI_Long)45L));
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_1 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    temp = CHR('-');
		    SET_SCHAR(temp_1,schar_arg_2,temp);
		    temp_1 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_1;
		}
		temp = negate(long_to_write);
		positive_long = INTEGER_TO_INT64(temp);
	    }
	    else
		positive_long = INTEGER_TO_INT64(long_to_write);
	    twrite_positive_bignum_in_radix(INT64_TO_INTEGER(positive_long),
		    FIX((SI_Long)10L));
	}
	twrite_general_string(string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

Object Smallest_order_of_magnitude = UNBOUND;

Object Float_with_smallest_order_of_magnitude = UNBOUND;

Object Order_of_largest_fixnum_power_of_ten = UNBOUND;

Object Integer_decade_table = UNBOUND;

/* FIXNUM-ORDER-OF-MAGNITUDE */
Object fixnum_order_of_magnitude(non_negative_fixnum)
    Object non_negative_fixnum;
{
    Object temp;
    SI_Long index_1;

    x_note_fn_call(26,219);
    index_1 = 
	    IFIX(FIXNUM_SUB1(SIMPLE_ARRAY_ANY_1_LENGTH(Integer_decade_table)));
  next_loop:
    if (index_1 < (SI_Long)0L)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(Integer_decade_table,index_1),non_negative_fixnum)) {
	temp = FIX(index_1);
	goto end_1;
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = FIX((SI_Long)0L);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* TWRITE-FIXNUM-IN-FIXED-FIELD */
Object twrite_fixnum_in_fixed_field varargs_1(int, n)
{
    Object fixnum_to_write_init, field_width;
    Object pad_right_qm, pad_char, thing, temp, schar_arg_2, schar_new_value;
    SI_Long fixnum_to_write, gensymed_symbol, gensymed_symbol_1, number_width;
    SI_Long ab_loop_repeat_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,220);
    INIT_ARGS_nonrelocating();
    fixnum_to_write_init = REQUIRED_ARG_nonrelocating();
    field_width = REQUIRED_ARG_nonrelocating();
    fixnum_to_write = IFIX(fixnum_to_write_init);
    pad_right_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    pad_char = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)32L);
    END_ARGS_nonrelocating();
    gensymed_symbol = 
	    IFIX(fixnum_order_of_magnitude(FIX(ABS(fixnum_to_write))));
    gensymed_symbol_1 = (SI_Long)0L > fixnum_to_write ? (SI_Long)2L : 
	    (SI_Long)1L;
    number_width = gensymed_symbol + gensymed_symbol_1;
    if (pad_right_qm)
	twrite_fixnum(FIX(fixnum_to_write));
    ab_loop_repeat_ = IFIX(field_width) - number_width;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = pad_char;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = pad_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    goto next_loop;
  end_loop:;
    if ( !TRUEP(pad_right_qm))
	twrite_fixnum(FIX(fixnum_to_write));
    return VALUES_1(Nil);
}

/* WRITE-INTEGER-IN-FIELD */
Object write_integer_in_field(integer,field_width,trailing_zeros_qm)
    Object integer, field_width, trailing_zeros_qm;
{
    Object quotient, remainder_1;
    SI_Long index_1;
    Object result;

    x_note_fn_call(26,221);
    quotient = Nil;
    remainder_1 = integer;
    index_1 = IFIX(FIXNUM_SUB1(field_width));
  next_loop:
    if (index_1 < (SI_Long)0L)
	goto end_loop;
    result = lfloor(remainder_1,ISVREF(Integer_decade_table,index_1));
    MVS_2(result,quotient,remainder_1);
    twrite_fixnum(quotient);
    if ( !TRUEP(trailing_zeros_qm) && IFIX(remainder_1) == (SI_Long)0L)
	goto end_loop;
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TWRITE-POSITIVE-FIXNUM-IN-FIELD */
Object twrite_positive_fixnum_in_field(positive_fixnum,field_width,
	    trailing_zeros_qm)
    Object positive_fixnum, field_width, trailing_zeros_qm;
{
    Object simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long temp, quotient, remainder_1;

    x_note_fn_call(26,222);
    if (IFIX(field_width) > (SI_Long)0L) {
	temp = IFIX(positive_fixnum) / (SI_Long)10L;
	quotient = temp;
	temp = IFIX(positive_fixnum) % (SI_Long)10L;
	remainder_1 = temp;
	if ( !TRUEP(trailing_zeros_qm) &&  !(remainder_1 == (SI_Long)0L))
	    trailing_zeros_qm = T;
	twrite_positive_fixnum_in_field(FIX(quotient),
		FIXNUM_SUB1(field_width),trailing_zeros_qm);
	if (trailing_zeros_qm || IFIX(field_width) == (SI_Long)1L) {
	    simple_or_wide_character = digit_char(FIX(remainder_1),_,_);
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = simple_or_wide_character;
		return twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
		return VALUES_1(Fill_pointer_for_current_gensym_string);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_16;  /* "~x" */

/* TWRITE-RGB-AS-PADDED-HEX */
Object twrite_rgb_as_padded_hex(r_value,g_value,b_value)
    Object r_value, g_value, b_value;
{
    Object substitute_value;

    x_note_fn_call(26,223);
    if (IFIX(r_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(r_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = r_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	twrite_character(FIX((SI_Long)48L));
    tformat(2,string_constant_16,substitute_value);
    if (IFIX(g_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(g_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = g_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	twrite_character(FIX((SI_Long)48L));
    tformat(2,string_constant_16,substitute_value);
    if (IFIX(b_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(b_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = b_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	twrite_character(FIX((SI_Long)48L));
    return tformat(2,string_constant_16,substitute_value);
}

/* C-WRITE-FLOAT-FROM-C */
Object c_write_float_from_c(return_string,format_string,precision,double_1)
    Object return_string, format_string, precision, double_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1, *temp_2;
    double temp_3;

    x_note_fn_call(26,224);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(return_string);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(format_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = return_string;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = format_string;
    temp_2 = ISTRING(temp);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(double_1);
    g2ext_write_float_from_c(temp_1,temp_2,IFIX(precision),temp_3);
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(Nil);
}

Object New_decade_table = UNBOUND;

Object New_fractional_decade_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(String_for_returning_floats, Qstring_for_returning_floats);

DEFINE_VARIABLE_WITH_SYMBOL(Null_char, Qnull_char);

static Object string_constant_17;  /* "%.*f" */

/* GENSYM-SPRINTF-FLOAT */
Object gensym_sprintf_float(string_to_write_into,precision,number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    x_note_fn_call(26,225);
    return c_write_float_from_c(string_to_write_into,string_constant_17,
	    precision,number_to_write);
}

static Object string_constant_18;  /* "%.*g" */

/* GENSYM-SPRINTF-FLOAT-OR-EXPONENTIAL */
Object gensym_sprintf_float_or_exponential(string_to_write_into,precision,
	    number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    x_note_fn_call(26,226);
    return c_write_float_from_c(string_to_write_into,string_constant_18,
	    precision,number_to_write);
}

static Object string_constant_19;  /* "%.*e" */

/* GENSYM-SPRINTF-EXPONENTIAL */
Object gensym_sprintf_exponential(string_to_write_into,precision,
	    number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    Object i, this_char, index_delta, exponent_marker_encountered_p;
    Object at_least_one_nonzero_exponent_digit_written_p, schar_arg_2;
    Object schar_new_value, index_of_zero_exponent, temp;

    x_note_fn_call(26,227);
    c_write_float_from_c(string_to_write_into,string_constant_19,precision,
	    number_to_write);
    i = FIX((SI_Long)0L);
    this_char = Nil;
    index_delta = FIX((SI_Long)0L);
    exponent_marker_encountered_p = Nil;
    at_least_one_nonzero_exponent_digit_written_p = Nil;
  next_loop:
    this_char = SCHAR(string_to_write_into,i);
    if (EQL(this_char,Null_char))
	goto end_loop;
    if ( !CHARACTERP(this_char)) {
	if (exponent_marker_encountered_p &&  
		!TRUEP(at_least_one_nonzero_exponent_digit_written_p) && 
		digit_char_p(this_char,_))
	    at_least_one_nonzero_exponent_digit_written_p = T;
	schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
    }
    else
	switch (ICHAR_CODE(this_char)) {
	  case '+':
	    index_delta = FIXNUM_ADD1(index_delta);
	    break;
	  case 'e':
	    exponent_marker_encountered_p = T;
	    schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	    SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    break;
	  case '0':
	    if (exponent_marker_encountered_p &&  
		    !TRUEP(at_least_one_nonzero_exponent_digit_written_p))
		index_delta = FIXNUM_ADD1(index_delta);
	    else {
		schar_arg_2 = FIXNUM_MINUS(i,index_delta);
		SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    }
	    break;
	  default:
	    if (exponent_marker_encountered_p &&  
		    !TRUEP(at_least_one_nonzero_exponent_digit_written_p) 
		    && digit_char_p(this_char,_))
		at_least_one_nonzero_exponent_digit_written_p = T;
	    schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	    SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    break;
	}
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    if (at_least_one_nonzero_exponent_digit_written_p) {
	schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	schar_new_value = Null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    else {
	index_of_zero_exponent = FIXNUM_MINUS(i,index_delta);
	temp = CHR('0');
	SET_SCHAR(string_to_write_into,index_of_zero_exponent,temp);
	schar_arg_2 = FIXNUM_ADD1(index_of_zero_exponent);
	schar_new_value = Null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    return VALUES_1(Qnil);
}

/* GENSYM-SPRINTF-MINIMAL-EXPONENTIAL */
Object gensym_sprintf_minimal_exponential(string_to_write_into,number_to_write)
    Object string_to_write_into, number_to_write;
{
    Object i, this_char, index_delta, exponent_marker_encountered_p;
    Object at_least_one_nonzero_exponent_digit_written_p, schar_arg_2;
    Object schar_new_value, index_of_zero_exponent, temp;

    x_note_fn_call(26,228);
    c_write_float_from_c(string_to_write_into,string_constant_19,
	    FIX((SI_Long)0L),number_to_write);
    i = FIX((SI_Long)0L);
    this_char = Nil;
    index_delta = FIX((SI_Long)0L);
    exponent_marker_encountered_p = Nil;
    at_least_one_nonzero_exponent_digit_written_p = Nil;
  next_loop:
    this_char = SCHAR(string_to_write_into,i);
    if (CHAR_EQ(this_char,Null_char))
	goto end_loop;
    if ( !CHARACTERP(this_char)) {
	if (exponent_marker_encountered_p &&  
		!TRUEP(at_least_one_nonzero_exponent_digit_written_p) && 
		digit_char_p(this_char,_))
	    at_least_one_nonzero_exponent_digit_written_p = T;
	schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
    }
    else
	switch (ICHAR_CODE(this_char)) {
	  case '.':
	    index_delta = FIXNUM_ADD1(index_delta);
	    break;
	  case '+':
	    index_delta = FIXNUM_ADD1(index_delta);
	    break;
	  case 'e':
	    exponent_marker_encountered_p = T;
	    schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	    SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    break;
	  case '0':
	    if (exponent_marker_encountered_p &&  
		    !TRUEP(at_least_one_nonzero_exponent_digit_written_p))
		index_delta = FIXNUM_ADD1(index_delta);
	    else {
		schar_arg_2 = FIXNUM_MINUS(i,index_delta);
		SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    }
	    break;
	  default:
	    if (exponent_marker_encountered_p &&  
		    !TRUEP(at_least_one_nonzero_exponent_digit_written_p) 
		    && digit_char_p(this_char,_))
		at_least_one_nonzero_exponent_digit_written_p = T;
	    schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	    SET_SCHAR(string_to_write_into,schar_arg_2,this_char);
	    break;
	}
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    if (at_least_one_nonzero_exponent_digit_written_p) {
	schar_arg_2 = FIXNUM_MINUS(i,index_delta);
	schar_new_value = Null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    else {
	index_of_zero_exponent = FIXNUM_MINUS(i,index_delta);
	temp = CHR('0');
	SET_SCHAR(string_to_write_into,index_of_zero_exponent,temp);
	schar_arg_2 = FIXNUM_ADD1(index_of_zero_exponent);
	schar_new_value = Null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    return VALUES_1(Qnil);
}

/* TWRITE-NUMBER-STRING-AS-IS */
Object twrite_number_string_as_is(number_string)
    Object number_string;
{
    Object this_char, thing, temp, schar_arg_2, schar_new_value;
    SI_Long i;

    x_note_fn_call(26,229);
    i = (SI_Long)0L;
    this_char = Nil;
  next_loop:
    if (i >= IFIX(Size_of_string_for_returning_floats))
	goto end_loop;
    this_char = CHR(ISCHAR(number_string,i));
    if (CHAR_EQ(Null_char,this_char))
	goto end_loop;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = this_char;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = this_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TWRITE-NUMBER-STRING-SUPPRESSING-FRACTION-ENTIRELY */
Object twrite_number_string_suppressing_fraction_entirely(number_string)
    Object number_string;
{
    Object this_char, thing, temp, schar_arg_2, schar_new_value;
    SI_Long i;

    x_note_fn_call(26,230);
    i = (SI_Long)0L;
    this_char = Nil;
  next_loop:
    if (i >= IFIX(Size_of_string_for_returning_floats))
	goto end_loop;
    this_char = CHR(ISCHAR(number_string,i));
    if (CHAR_EQ(this_char,Null_char) || CHAR_EQ(this_char,CHR('.')))
	goto end_loop;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = this_char;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = this_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COUNT-OF-NUMBER-STRING-TRAILING-ZEROS */
Object count_of_number_string_trailing_zeros(number_string,
	    use_exponential_notation_p)
    Object number_string, use_exponential_notation_p;
{
    Object index_of_final_trailing_digit, this_char;
    Object index_of_final_nonzero_trailing_digit;
    SI_Long i;

    x_note_fn_call(26,231);
    if (use_exponential_notation_p) {
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(Size_of_string_for_returning_floats))
	    goto end_loop;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),CHR('e')))
	    goto end_loop;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_1;
	index_of_final_trailing_digit = Qnil;
      end_1:;
    }
    else {
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= IFIX(Size_of_string_for_returning_floats))
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),Null_char))
	    goto end_loop_1;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_2;
	index_of_final_trailing_digit = Qnil;
      end_2:;
    }
    i = IFIX(index_of_final_trailing_digit);
    this_char = Nil;
  next_loop_2:
    if (i < (SI_Long)0L)
	goto end_loop_2;
    this_char = CHR(ISCHAR(number_string,i));
    if ( !CHAR_EQ(this_char,CHR('0')))
	goto end_loop_2;
    i = i - (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:
    if (CHAR_EQ(this_char,CHR('.'))) {
	index_of_final_nonzero_trailing_digit = FIX(i + (SI_Long)1L);
	goto end_3;
    }
    else {
	index_of_final_nonzero_trailing_digit = FIX(i);
	goto end_3;
    }
    index_of_final_nonzero_trailing_digit = Qnil;
  end_3:;
    return VALUES_1(FIXNUM_MINUS(index_of_final_trailing_digit,
	    index_of_final_nonzero_trailing_digit));
}

/* TWRITE-NUMBER-STRING-SUPPRESSING-TRAILING-ZEROS */
Object twrite_number_string_suppressing_trailing_zeros(number_string,
	    use_exponential_notation_p)
    Object number_string, use_exponential_notation_p;
{
    Object index_of_exponent_marker_qm, index_of_final_trailing_digit;
    Object this_char, index_of_final_nonzero_trailing_digit, i_1;
    SI_Long i;

    x_note_fn_call(26,232);
    index_of_exponent_marker_qm = Nil;
    if (use_exponential_notation_p) {
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(Size_of_string_for_returning_floats))
	    goto end_loop;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),CHR('e')))
	    goto end_loop;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	index_of_exponent_marker_qm = FIX(i);
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_1;
	index_of_final_trailing_digit = Qnil;
      end_1:;
    }
    else {
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= IFIX(Size_of_string_for_returning_floats))
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),Null_char))
	    goto end_loop_1;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_2;
	index_of_final_trailing_digit = Qnil;
      end_2:;
    }
    i = IFIX(index_of_final_trailing_digit);
    this_char = Nil;
  next_loop_2:
    if (i < (SI_Long)0L)
	goto end_loop_2;
    this_char = CHR(ISCHAR(number_string,i));
    if ( !CHAR_EQ(this_char,CHR('0')))
	goto end_loop_2;
    i = i - (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:
    if (CHAR_EQ(this_char,CHR('.'))) {
	index_of_final_nonzero_trailing_digit = FIX(i + (SI_Long)1L);
	goto end_3;
    }
    else {
	index_of_final_nonzero_trailing_digit = FIX(i);
	goto end_3;
    }
    index_of_final_nonzero_trailing_digit = Qnil;
  end_3:;
    i_1 = FIX((SI_Long)0L);
    this_char = Nil;
  next_loop_3:
    this_char = SCHAR(number_string,i_1);
    if (FIXNUM_GE(i_1,Size_of_string_for_returning_floats) || 
	    CHAR_EQ(this_char,Null_char))
	goto end_loop_3;
    twrite(this_char);
    if (FIXNUM_EQ(i_1,index_of_final_nonzero_trailing_digit)) {
	if (index_of_exponent_marker_qm)
	    i_1 = index_of_exponent_marker_qm;
	else
	    goto end_loop_3;
    }
    else
	i_1 = FIXNUM_ADD1(i_1);
    goto next_loop_3;
  end_loop_3:
    return VALUES_1(Qnil);
}

static Object float_constant;      /* 0.0 */

static Object float_constant_1;    /* 1.0 */

static Object float_constant_2;    /* -1.0 */

static Object string_constant_20;  /* "0.0" */

/* TWRITE-NUMBER-STRING-IN-FIXED-FIELD */
Object twrite_number_string_in_fixed_field(number,number_string,
	    fixed_field_width,fraction_size,use_exponential_notation_p,
	    force_small_number_into_exponential_p,
	    suppress_trailing_zeros_p,over_or_underflow_char,
	    zero_fraction_size_p)
    Object number, number_string, fixed_field_width, fraction_size;
    Object use_exponential_notation_p, force_small_number_into_exponential_p;
    Object suppress_trailing_zeros_p, over_or_underflow_char;
    Object zero_fraction_size_p;
{
    Object field_width;
    volatile Object number_string_before_heuristics;
    volatile Object suppressed_trailing_zeros_unasked_qm;
    volatile Object truncated_non_exponential_qm;
    Object magnitude_less_than_one_p;
    volatile Object too_small_number_qm;
    volatile Object exponential_notation_unasked_qm;
    Object exponential_number_string, length_of_exponential_number_string;
    Object index_of_decimal_point, index_of_exponent_marker;
    Object number_of_decimal_places_before_truncation;
    Object maximum_characters_that_can_be_truncated;
    Object number_of_characters_to_truncate;
    volatile Object truncated_exponential_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, length_of_number_string, this_char;
    Object index_of_final_nonzero_trailing_digit_qm, temp_2, schar_arg_2;
    Object schar_new_value, thing_1, over_or_underflow_char_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_, ab_loop_repeat_, thing;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(26,233);
    SAVE_STACK();
    if (zero_fraction_size_p)
	number = lfloat(l_round(number,_),float_constant);
    field_width = fixed_field_width;
    number_string_before_heuristics = Qunbound_in_protected_let;
    suppressed_trailing_zeros_unasked_qm = Qunbound_in_protected_let;
    truncated_non_exponential_qm = Qunbound_in_protected_let;
    magnitude_less_than_one_p = Qunbound_in_protected_let;
    too_small_number_qm = Qunbound_in_protected_let;
    exponential_notation_unasked_qm = Qunbound_in_protected_let;
    exponential_number_string = Qunbound_in_protected_let;
    length_of_exponential_number_string = Qunbound_in_protected_let;
    index_of_decimal_point = Qunbound_in_protected_let;
    index_of_exponent_marker = Qunbound_in_protected_let;
    number_of_decimal_places_before_truncation = Qunbound_in_protected_let;
    maximum_characters_that_can_be_truncated = Qunbound_in_protected_let;
    number_of_characters_to_truncate = Qunbound_in_protected_let;
    truncated_exponential_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
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
		  if (suppress_trailing_zeros_p)
		      twrite_number_string_suppressing_trailing_zeros(number_string,
			      use_exponential_notation_p);
		  else
		      twrite_number_string_as_is(number_string);
		  number_string_before_heuristics = 
			  copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (number_string_before_heuristics) {
	    temp = 
		    length_of_null_terminated_text_string(number_string_before_heuristics);
	    if (temp);
	    else
		temp = text_string_length(number_string_before_heuristics);
	    temp_1 = NUM_LE(temp,field_width);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    SAVE_VALUES(twrite_general_string(number_string_before_heuristics));
	else {
	    if ( !TRUEP(suppress_trailing_zeros_p)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_number_string_suppressing_trailing_zeros(number_string,
				  use_exponential_notation_p);
			  suppressed_trailing_zeros_unasked_qm = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		suppressed_trailing_zeros_unasked_qm = Nil;
	    if (suppressed_trailing_zeros_unasked_qm) {
		temp = 
			length_of_null_terminated_text_string(suppressed_trailing_zeros_unasked_qm);
		if (temp);
		else
		    temp = 
			    text_string_length(suppressed_trailing_zeros_unasked_qm);
		temp_1 = NUM_LE(temp,field_width);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		SAVE_VALUES(twrite_general_string(suppressed_trailing_zeros_unasked_qm));
	    else {
		if ( !TRUEP(use_exponential_notation_p)) {
		    length_of_number_string = 
			    length_of_null_terminated_string(number_string);
		    if (length_of_number_string);
		    else
			length_of_number_string = 
				text_string_length(number_string_before_heuristics);
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(length_of_number_string);
		  next_loop:
		    if (i >= ab_loop_bind_)
			goto end_loop;
		    if (UBYTE_16_ISAREF_1(number_string_before_heuristics,
			    i) == (SI_Long)46L)
			goto end_loop;
		    i = i + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    index_of_decimal_point = FIX(i);
		    goto end_1;
		    index_of_decimal_point = Qnil;
		  end_1:;
		    maximum_characters_that_can_be_truncated = 
			    FIXNUM_MINUS(length_of_number_string,
			    index_of_decimal_point);
		    number_of_decimal_places_before_truncation = 
			    FIXNUM_SUB1(maximum_characters_that_can_be_truncated);
		    number_of_characters_to_truncate = 
			    FIXNUM_MINUS(length_of_number_string,
			    fixed_field_width);
		    if (suppress_trailing_zeros_p) {
			i = 
				IFIX(FIXNUM_MINUS(FIXNUM_SUB1(length_of_number_string),
				number_of_characters_to_truncate));
			ab_loop_bind_ = IFIX(index_of_decimal_point);
			this_char = Nil;
		      next_loop_1:
			if (i < ab_loop_bind_)
			    goto end_loop_1;
			this_char = 
				FIX(UBYTE_16_ISAREF_1(number_string_before_heuristics,
				i));
			if ( !(IFIX(this_char) == (SI_Long)48L))
			    goto end_loop_1;
			i = i - (SI_Long)1L;
			goto next_loop_1;
		      end_loop_1:
			if (IFIX(this_char) == (SI_Long)46L) {
			    index_of_final_nonzero_trailing_digit_qm = 
				    FIX(i + (SI_Long)1L);
			    goto end_2;
			}
			else {
			    index_of_final_nonzero_trailing_digit_qm = FIX(i);
			    goto end_2;
			}
			index_of_final_nonzero_trailing_digit_qm = Qnil;
		      end_2:;
		    }
		    else
			index_of_final_nonzero_trailing_digit_qm = Nil;
		    if (suppress_trailing_zeros_p && 
			    index_of_final_nonzero_trailing_digit_qm) {
			temp = 
				FIXNUM_MINUS(FIXNUM_SUB1(length_of_number_string),
				index_of_final_nonzero_trailing_digit_qm);
			number_of_characters_to_truncate = 
				FIXNUM_MAX(number_of_characters_to_truncate,
				temp);
		    }
		    if (plusp(number_of_characters_to_truncate) && 
			    FIXNUM_LE(number_of_characters_to_truncate,
			    maximum_characters_that_can_be_truncated)) {
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  if (FIXNUM_GE(number_of_characters_to_truncate,
					  FIXNUM_SUB1(maximum_characters_that_can_be_truncated))) 
					      {
				      gensym_sprintf_float(number_string,
					      FIX((SI_Long)1L),number);
				      twrite_number_string_suppressing_fraction_entirely(number_string);
				  }
				  else {
				      gensym_sprintf_float(number_string,
					      FIXNUM_MINUS(number_of_decimal_places_before_truncation,
					      number_of_characters_to_truncate),
					      number);
				      twrite_number_string_as_is(number_string);
				  }
				  truncated_non_exponential_qm = 
					  copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else
			truncated_non_exponential_qm = Nil;
		}
		else
		    truncated_non_exponential_qm = Nil;
		if (truncated_non_exponential_qm) {
		    temp = 
			    length_of_null_terminated_text_string(truncated_non_exponential_qm);
		    if (temp);
		    else
			temp = 
				text_string_length(truncated_non_exponential_qm);
		    temp_1 = NUM_LE(temp,field_width);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    SAVE_VALUES(twrite_general_string(truncated_non_exponential_qm));
		else {
		    magnitude_less_than_one_p = NUM_LT(number,
			    float_constant_1) ? (NUM_GT(number,
			    float_constant_2) ? T : Nil) : Qnil;
		    if (magnitude_less_than_one_p &&  
			    !TRUEP(use_exponential_notation_p) &&  
			    !TRUEP(force_small_number_into_exponential_p)) {
			if (IFIX(fixed_field_width) >= (SI_Long)3L) {
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      twrite_general_string(string_constant_20);
				      ab_loop_repeat_ = 
					      IFIX(fixed_field_width) - 
					      (IFIX(fraction_size) + 
					      (SI_Long)3L);
				    next_loop_2:
				      if ( !((SI_Long)0L < ab_loop_repeat_))
					  goto end_loop_2;
				      ab_loop_repeat_ = ab_loop_repeat_ - 
					      (SI_Long)1L;
				      if (EQ(Current_twriting_output_type,
					      Qwide_string)) {
					  thing = (SI_Long)48L;
					  twrite_wide_character(CHARACTERP(FIX(thing)) 
						  ? CHAR_CODE(FIX(thing)) :
						   FIX(thing));
				      }
				      else {
					  if ( 
						  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
						  Total_length_of_current_gensym_string))
					      extend_current_gensym_string(0);
					  temp_2 = Current_gensym_string;
					  schar_arg_2 = 
						  Fill_pointer_for_current_gensym_string;
					  thing = (SI_Long)48L;
					  schar_new_value = 
						  CODE_CHAR(CHARACTERP(FIX(thing)) 
						  ? CHAR_CODE(FIX(thing)) :
						   FIX(thing));
					  SET_SCHAR(temp_2,schar_arg_2,
						  schar_new_value);
					  temp_2 = 
						  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
					  Fill_pointer_for_current_gensym_string 
						  = temp_2;
				      }
				      goto next_loop_2;
				    end_loop_2:;
				      too_small_number_qm = 
					      copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			else {
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      ab_loop_repeat_ = 
					      IFIX(fixed_field_width);
				    next_loop_3:
				      if ( !((SI_Long)0L < ab_loop_repeat_))
					  goto end_loop_3;
				      ab_loop_repeat_ = ab_loop_repeat_ - 
					      (SI_Long)1L;
				      if (EQ(Current_twriting_output_type,
					      Qwide_string)) {
					  thing_1 = over_or_underflow_char;
					  twrite_wide_character(CHARACTERP(thing_1) 
						  ? CHAR_CODE(thing_1) : 
						  thing_1);
				      }
				      else {
					  if ( 
						  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
						  Total_length_of_current_gensym_string))
					      extend_current_gensym_string(0);
					  temp_2 = Current_gensym_string;
					  schar_arg_2 = 
						  Fill_pointer_for_current_gensym_string;
					  thing_1 = over_or_underflow_char;
					  schar_new_value = 
						  CODE_CHAR(CHARACTERP(thing_1) 
						  ? CHAR_CODE(thing_1) : 
						  thing_1);
					  SET_SCHAR(temp_2,schar_arg_2,
						  schar_new_value);
					  temp_2 = 
						  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
					  Fill_pointer_for_current_gensym_string 
						  = temp_2;
				      }
				      goto next_loop_3;
				    end_loop_3:;
				      too_small_number_qm = 
					      copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
		    }
		    else
			too_small_number_qm = Nil;
		    if (too_small_number_qm) {
			temp = 
				length_of_null_terminated_text_string(too_small_number_qm);
			if (temp);
			else
			    temp = text_string_length(too_small_number_qm);
			temp_1 = NUM_LE(temp,field_width);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			SAVE_VALUES(twrite_general_string(too_small_number_qm));
		    else {
			if ( !TRUEP(use_exponential_notation_p) && 
				(magnitude_less_than_one_p ? 
				TRUEP(force_small_number_into_exponential_p) 
				: TRUEP(T))) {
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      gensym_sprintf_exponential(number_string,
					      fraction_size,number);
				      twrite_number_string_as_is(number_string);
				      exponential_notation_unasked_qm = 
					      copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			else
			    exponential_notation_unasked_qm = Nil;
			if (exponential_notation_unasked_qm) {
			    temp = 
				    length_of_null_terminated_text_string(exponential_notation_unasked_qm);
			    if (temp);
			    else
				temp = 
					text_string_length(exponential_notation_unasked_qm);
			    temp_1 = NUM_LE(temp,field_width);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    SAVE_VALUES(twrite_general_string(exponential_notation_unasked_qm));
			else {
			    temp = exponential_notation_unasked_qm;
			    if (temp);
			    else
				temp = suppressed_trailing_zeros_unasked_qm;
			    if (temp);
			    else
				temp = number_string_before_heuristics;
			    exponential_number_string = temp;
			    temp = 
				    length_of_null_terminated_text_string(exponential_number_string);
			    if (temp);
			    else
				temp = 
					text_string_length(exponential_number_string);
			    length_of_exponential_number_string = temp;
			    i = (SI_Long)0L;
			    ab_loop_bind_ = 
				    IFIX(length_of_exponential_number_string);
			  next_loop_4:
			    if (i >= ab_loop_bind_)
				goto end_loop_4;
			    if (UBYTE_16_ISAREF_1(exponential_number_string,
				    i) == (SI_Long)46L)
				goto end_loop_4;
			    i = i + (SI_Long)1L;
			    goto next_loop_4;
			  end_loop_4:
			    index_of_decimal_point = FIX(i);
			    goto end_3;
			    index_of_decimal_point = Qnil;
			  end_3:;
			    i = IFIX(FIXNUM_ADD1(index_of_decimal_point));
			    ab_loop_bind_ = 
				    IFIX(length_of_exponential_number_string);
			  next_loop_5:
			    if (i >= ab_loop_bind_)
				goto end_loop_5;
			    if (UBYTE_16_ISAREF_1(exponential_number_string,
				    i) == (SI_Long)101L)
				goto end_loop_5;
			    i = i + (SI_Long)1L;
			    goto next_loop_5;
			  end_loop_5:
			    index_of_exponent_marker = FIX(i);
			    goto end_4;
			    index_of_exponent_marker = Qnil;
			  end_4:;
			    number_of_decimal_places_before_truncation = 
				    FIXNUM_SUB1(FIXNUM_MINUS(index_of_exponent_marker,
				    index_of_decimal_point));
			    maximum_characters_that_can_be_truncated = 
				    FIXNUM_MINUS(index_of_exponent_marker,
				    index_of_decimal_point);
			    number_of_characters_to_truncate = 
				    FIXNUM_MINUS(length_of_exponential_number_string,
				    fixed_field_width);
			    if (plusp(number_of_characters_to_truncate) && 
				    FIXNUM_LE(number_of_characters_to_truncate,
				    maximum_characters_that_can_be_truncated)) 
					{
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  if (FIXNUM_GE(number_of_characters_to_truncate,
						  FIXNUM_SUB1(maximum_characters_that_can_be_truncated)))
					      gensym_sprintf_minimal_exponential(number_string,
						      number);
					  else
					      gensym_sprintf_exponential(number_string,
						      FIXNUM_MINUS(number_of_decimal_places_before_truncation,
						      number_of_characters_to_truncate),
						      number);
					  twrite_number_string_as_is(number_string);
					  truncated_exponential_qm = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			    }
			    else
				truncated_exponential_qm = Nil;
			    if (truncated_exponential_qm) {
				temp = 
					length_of_null_terminated_text_string(truncated_exponential_qm);
				if (temp);
				else
				    temp = 
					    text_string_length(truncated_exponential_qm);
				temp_1 = NUM_LE(temp,field_width);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				SAVE_VALUES(twrite_general_string(truncated_exponential_qm));
			    else {
				over_or_underflow_char_1 = 
					over_or_underflow_char;
				ab_loop_repeat_ = IFIX(field_width);
			      next_loop_6:
				if ( !((SI_Long)0L < ab_loop_repeat_))
				    goto end_loop_6;
				ab_loop_repeat_ = ab_loop_repeat_ - 
					(SI_Long)1L;
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing_1 = over_or_underflow_char_1;
				    twrite_wide_character(CHARACTERP(thing_1) 
					    ? CHAR_CODE(thing_1) : thing_1);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    schar_arg_2 = 
					    Fill_pointer_for_current_gensym_string;
				    thing_1 = over_or_underflow_char_1;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing_1) ?
					     CHAR_CODE(thing_1) : thing_1);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
				goto next_loop_6;
			      end_loop_6:
				SAVE_VALUES(VALUES_1(Qnil));
			    }
			}
		    }
		}
	    }
	}
    }
    POP_UNWIND_PROTECT(0);
    if (truncated_exponential_qm) {
	if ( !EQ(truncated_exponential_qm,Qunbound_in_protected_let))
	    reclaim_text_string(truncated_exponential_qm);
    }
    if (exponential_notation_unasked_qm) {
	if ( !EQ(exponential_notation_unasked_qm,Qunbound_in_protected_let))
	    reclaim_text_string(exponential_notation_unasked_qm);
    }
    if (too_small_number_qm) {
	if ( !EQ(too_small_number_qm,Qunbound_in_protected_let))
	    reclaim_text_string(too_small_number_qm);
    }
    if (truncated_non_exponential_qm) {
	if ( !EQ(truncated_non_exponential_qm,Qunbound_in_protected_let))
	    reclaim_text_string(truncated_non_exponential_qm);
    }
    if (suppressed_trailing_zeros_unasked_qm) {
	if ( !EQ(suppressed_trailing_zeros_unasked_qm,
		Qunbound_in_protected_let))
	    reclaim_text_string(suppressed_trailing_zeros_unasked_qm);
    }
    if (number_string_before_heuristics) {
	if ( !EQ(number_string_before_heuristics,Qunbound_in_protected_let))
	    reclaim_text_string(number_string_before_heuristics);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PAD-EXPONENT-TO-FIXED-WIDTH */
Object pad_exponent_to_fixed_width varargs_1(int, n)
{
    Object fixed_exponent_subfield_width;
    Object plus_sign_char;
    volatile Object string_for_storing_exponent;
    Object this_char, number_of_exponent_digits, exponent_char;
    Object ab_loop_iter_flag_, temp, number_of_zeros_for_exponent_pad;
    Object schar_new_value;
    SI_Long index_1, ab_loop_bind_, next_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, exponent_digits_start, from_index, to_index;
    SI_Long new_exponent_digits_start, pad_index;
    char minus_exponent_p;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(26,234);
    INIT_ARGS_nonrelocating();
    fixed_exponent_subfield_width = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    plus_sign_char = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : CHR('0');
    END_ARGS_nonrelocating();
    string_for_storing_exponent = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	string_for_storing_exponent = obtain_adjustable_gensym_string();
	SET_FILL_POINTER(string_for_storing_exponent,FIX((SI_Long)0L));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(Size_of_string_for_returning_floats));
	this_char = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	this_char = CHR(ISCHAR(String_for_returning_floats,index_1));
	if (CHAR_EQ(this_char,Null_char))
	    goto end_loop;
	if (CHAR_EQ(this_char,CHR('e'))) {
	    next_index = index_1 + (SI_Long)1L;
	    minus_exponent_p = 
		    CHAR_EQ(CHR(ISCHAR(String_for_returning_floats,
		    next_index)),CHR('-'));
	    gensymed_symbol = index_1;
	    gensymed_symbol_1 = minus_exponent_p ? (SI_Long)2L : (SI_Long)1L;
	    exponent_digits_start = gensymed_symbol + gensymed_symbol_1;
	    number_of_exponent_digits = FIX((SI_Long)0L);
	    from_index = exponent_digits_start;
	    exponent_char = Nil;
	    to_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if (from_index >= IFIX(Size_of_string_for_returning_floats))
		goto end_loop_1;
	    exponent_char = CHR(ISCHAR(String_for_returning_floats,
		    from_index));
	    if ( !TRUEP(ab_loop_iter_flag_))
		to_index = to_index + (SI_Long)1L;
	    if (CHAR_EQ(exponent_char,Null_char))
		goto end_loop_1;
	    SET_ICHAR(string_for_storing_exponent,to_index,
		    ICHAR_CODE(exponent_char));
	    ab_loop_iter_flag_ = Nil;
	    from_index = from_index + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    number_of_exponent_digits = FIX(to_index);
	    temp = Null_char;
	    SET_ICHAR(string_for_storing_exponent,to_index,ICHAR_CODE(temp));
	    number_of_zeros_for_exponent_pad = 
		    FIXNUM_SUB1(FIXNUM_MINUS(fixed_exponent_subfield_width,
		    number_of_exponent_digits));
	    new_exponent_digits_start = minus_exponent_p ? 
		    exponent_digits_start : exponent_digits_start + 
		    (SI_Long)1L;
	    if ( !FIXNUM_MINUSP(number_of_zeros_for_exponent_pad)) {
		if ( !minus_exponent_p) {
		    temp = String_for_returning_floats;
		    SET_ISCHAR(temp,next_index,ICHAR_CODE(plus_sign_char));
		}
		pad_index = (SI_Long)0L;
		ab_loop_bind_ = IFIX(number_of_zeros_for_exponent_pad);
		to_index = new_exponent_digits_start;
		ab_loop_iter_flag_ = T;
	      next_loop_2:
		if (pad_index >= ab_loop_bind_)
		    goto end_loop_2;
		if ( !TRUEP(ab_loop_iter_flag_))
		    to_index = to_index + (SI_Long)1L;
		temp = String_for_returning_floats;
		SET_ISCHAR(temp,to_index,'0');
		ab_loop_iter_flag_ = Nil;
		pad_index = pad_index + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
		to_index = new_exponent_digits_start + 
			IFIX(number_of_zeros_for_exponent_pad);
		from_index = (SI_Long)0L;
		exponent_char = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop_3:
		if (to_index >= IFIX(Size_of_string_for_returning_floats))
		    goto end_loop_3;
		if ( !TRUEP(ab_loop_iter_flag_))
		    from_index = from_index + (SI_Long)1L;
		exponent_char = CHR(ICHAR(string_for_storing_exponent,
			from_index));
		if (CHAR_EQ(exponent_char,Null_char))
		    goto end_loop_3;
		temp = String_for_returning_floats;
		SET_ISCHAR(temp,to_index,ICHAR_CODE(exponent_char));
		ab_loop_iter_flag_ = Nil;
		to_index = to_index + (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:
		temp = String_for_returning_floats;
		schar_new_value = Null_char;
		SET_ISCHAR(temp,to_index,ICHAR_CODE(schar_new_value));
	    }
	    goto end_loop;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	SAVE_VALUES(VALUES_1(Qnil));
    }
    POP_UNWIND_PROTECT(0);
    if (string_for_storing_exponent) {
	if ( !EQ(string_for_storing_exponent,Qunbound_in_protected_let))
	    reclaim_gensym_string(string_for_storing_exponent);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_significant_decimal_digits_in_gensym_float, Qmaximum_significant_decimal_digits_in_gensym_float);

DEFINE_VARIABLE_WITH_SYMBOL(Write_floats_accurately_p, Qwrite_floats_accurately_p);

static Object Qwrite_floating_point_number;  /* write-floating-point-number */

static Object string_constant_21;  /* "NaN" */

static Object string_constant_22;  /* "+Inf" */

static Object string_constant_23;  /* "-Inf" */

/* WRITE-FLOATING-POINT-NUMBER */
Object write_floating_point_number varargs_1(int, n)
{
    Object number;
    Object integral_size, fraction_size, suppress_trailing_zeros_p;
    Object force_any_number_into_exponential_p;
    Object force_small_number_into_exponential_p;
    Object fixed_exponent_subfield_width_qm, fixed_field_width_qm;
    Object over_or_underflow_char, supplied_fraction_size_p;
    Object zero_fraction_size_p, tag_temp, use_exponential_notation_p, temp_1;
    Object use_exact_float_p;
    SI_Long temp;
    double arg, arg_1, temp_2, absolute_value_of_number;
    Declare_varargs_nonrelocating;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(26,235);
    INIT_ARGS_nonrelocating();
    number = REQUIRED_ARG_nonrelocating();
    integral_size = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)5L);
    fraction_size = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    suppress_trailing_zeros_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    force_any_number_into_exponential_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    force_small_number_into_exponential_p = OPTIONAL_ARG_P_nonrelocating() 
	    ? OPTIONAL_ARG_nonrelocating() : T;
    fixed_exponent_subfield_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    fixed_field_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    over_or_underflow_char = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)35L);
    supplied_fraction_size_p = Nil;
    zero_fraction_size_p = Nil;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qwrite_floating_point_number);
    if (PUSH_CATCH(tag_temp,0)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    number = managed_float_p_function(number) ? 
		    managed_float_value_function(number) : lfloat(number,
		    float_constant);
	    if (nanp(number)) {
		twrite_general_string(string_constant_21);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (positive_infinity_p(number)) {
		twrite_general_string(string_constant_22);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (negative_infinity_p(number)) {
		twrite_general_string(string_constant_23);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    supplied_fraction_size_p =  ! !TRUEP(fraction_size) ? T : Nil;
	    if ( !TRUEP(fraction_size))
		fraction_size = FIX((SI_Long)3L);
	    zero_fraction_size_p = zerop(fraction_size);
	    integral_size = 
		    FIXNUM_MIN(Maximum_significant_decimal_digits_in_gensym_float,
		    integral_size);
	    temp = 
		    IFIX(FIXNUM_MIN(Maximum_significant_decimal_digits_in_gensym_float,
		    fraction_size));
	    fraction_size = FIX(MAX(temp,(SI_Long)1L));
	    use_exponential_notation_p = force_any_number_into_exponential_p;
	    if (use_exponential_notation_p);
	    else {
		arg = DOUBLE_FLOAT_TO_DOUBLE(number);
		arg_1 = 0.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    use_exponential_notation_p = Nil;
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(number);
		    arg_1 = 0.0;
		    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(number);
			temp_1 = ISVREF(New_decade_table,IFIX(integral_size));
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			use_exponential_notation_p = arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) ? ( 
				!inline_nanp_for_comparison(arg_1) ? T : 
				Nil) : Qnil;
			if (use_exponential_notation_p);
			else if (force_small_number_into_exponential_p) {
			    arg = DOUBLE_FLOAT_TO_DOUBLE(number);
			    temp_1 = ISVREF(New_fractional_decade_table,
				    IFIX(fraction_size));
			    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			    use_exponential_notation_p = arg < arg_1 &&  
				    !inline_nanp_for_comparison(arg) ? ( 
				    !inline_nanp_for_comparison(arg_1) ? T 
				    : Nil) : Qnil;
			}
			else
			    use_exponential_notation_p = Nil;
		    }
		    else {
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(number);
			absolute_value_of_number =  - temp_2;
			arg = absolute_value_of_number;
			temp_1 = ISVREF(New_decade_table,IFIX(integral_size));
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			use_exponential_notation_p = arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) ? ( 
				!inline_nanp_for_comparison(arg_1) ? T : 
				Nil) : Qnil;
			if (use_exponential_notation_p);
			else if (force_small_number_into_exponential_p) {
			    arg = absolute_value_of_number;
			    temp_1 = ISVREF(New_fractional_decade_table,
				    IFIX(fraction_size));
			    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			    use_exponential_notation_p = arg < arg_1 &&  
				    !inline_nanp_for_comparison(arg) ? ( 
				    !inline_nanp_for_comparison(arg_1) ? T 
				    : Nil) : Qnil;
			}
			else
			    use_exponential_notation_p = Nil;
		    }
		}
	    }
	    use_exact_float_p = Write_floats_accurately_p &&  
		    !TRUEP(supplied_fraction_size_p) ? ( 
		    !TRUEP(force_any_number_into_exponential_p) ? T : Nil) 
		    : Qnil;
	    if (use_exact_float_p)
		c_write_exact_float_from_c(String_for_returning_floats,number);
	    else if (use_exponential_notation_p)
		gensym_sprintf_exponential(String_for_returning_floats,
			fraction_size,number);
	    else
		gensym_sprintf_float(String_for_returning_floats,
			fraction_size,number);
	    if (use_exponential_notation_p && fixed_exponent_subfield_width_qm)
		pad_exponent_to_fixed_width(1,
			fixed_exponent_subfield_width_qm);
	    if (use_exact_float_p ||  !TRUEP(suppress_trailing_zeros_p) && 
		     !TRUEP(fixed_field_width_qm))
		result = twrite_number_string_as_is(String_for_returning_floats);
	    else if ( !TRUEP(fixed_field_width_qm))
		result = twrite_number_string_suppressing_trailing_zeros(String_for_returning_floats,
			use_exponential_notation_p);
	    else
		result = twrite_number_string_in_fixed_field(number,
			String_for_returning_floats,fixed_field_width_qm,
			fraction_size,use_exponential_notation_p,
			force_small_number_into_exponential_p,
			suppress_trailing_zeros_p,over_or_underflow_char,
			zero_fraction_size_p);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_float_to_text_format, Qdefault_float_to_text_format);

static Object Qwrite_floating_point_number_simple_c_format;  /* write-floating-point-number-simple-c-format */

static Object Qdefault;            /* default */

static Object Qexponent;           /* exponent */

static Object Qbest;               /* best */

static Object Qforce_zero;         /* force-zero */

static Object string_constant_24;  /* "####" */

/* WRITE-FLOATING-POINT-NUMBER-SIMPLE-C-FORMAT */
Object write_floating_point_number_simple_c_format varargs_1(int, n)
{
    Object number;
    Object precision, output_format, minimum_width_qm;
    Object suppress_trailing_zeros_p, tag_temp;
    Object length_of_string_for_returning_floats_qm, number_of_zeros_to_remove;
    SI_Long temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(26,236);
    INIT_ARGS_nonrelocating();
    number = REQUIRED_ARG_nonrelocating();
    precision = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : 
	    float_to_text_default_precision_from_system_table();
    if (OPTIONAL_ARG_P_nonrelocating())
	output_format = OPTIONAL_ARG_nonrelocating();
    else {
	output_format = Default_float_to_text_format;
	if (output_format);
	else
	    output_format = float_to_text_default_format_from_system_table();
    }
    minimum_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    suppress_trailing_zeros_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qwrite_floating_point_number_simple_c_format);
    if (PUSH_CATCH(tag_temp,0)) {
	if (EQ(output_format,Qdefault)) {
	    write_floating_point_number(1,number);
	    result = VALUES_1(Nil);
	    THROW(tag_temp,result);
	}
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    number = managed_float_p_function(number) ? 
		    managed_float_value_function(number) : lfloat(number,
		    float_constant);
	    if (minimum_width_qm) {
		temp = MAX(IFIX(minimum_width_qm),(SI_Long)1L);
		temp_1 = IFIX(Maximum_length_for_user_gensym_strings);
		minimum_width_qm = FIX(MIN(temp,temp_1));
	    }
	    if (nanp(number)) {
		if (minimum_width_qm)
		    twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)3L));
		twrite_general_string(string_constant_21);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (positive_infinity_p(number)) {
		if (minimum_width_qm)
		    twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		twrite_general_string(string_constant_22);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (negative_infinity_p(number)) {
		if (minimum_width_qm)
		    twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		twrite_general_string(string_constant_23);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    temp_1 = MIN((SI_Long)16L,IFIX(precision));
	    precision = FIX(MAX(temp_1,(SI_Long)0L));
	    if (EQ(output_format,Qfloat))
		gensym_sprintf_float(String_for_returning_floats,precision,
			number);
	    else if (EQ(output_format,Qexponent))
		gensym_sprintf_exponential(String_for_returning_floats,
			precision,number);
	    else if (EQ(output_format,Qbest))
		gensym_sprintf_float_or_exponential(String_for_returning_floats,
			precision,number);
	    else if (EQ(output_format,Qforce_zero))
		c_write_exact_float_from_c(String_for_returning_floats,number);
	    else {
		if (minimum_width_qm)
		    twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		twrite_general_string(string_constant_24);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    if (suppress_trailing_zeros_p &&  !EQ(output_format,Qbest) &&  
		    !EQ(output_format,Qforce_zero) && (EQ(output_format,
		    Qexponent) || IFIX(precision) != (SI_Long)0L)) {
		if (minimum_width_qm) {
		    length_of_string_for_returning_floats_qm = 
			    length_of_null_terminated_string(String_for_returning_floats);
		    number_of_zeros_to_remove = 
			    count_of_number_string_trailing_zeros(String_for_returning_floats,
			    EQ(output_format,Qexponent) ? T : Nil);
		    if (length_of_string_for_returning_floats_qm)
			twrite_spaces_if_necessary(minimum_width_qm,
				FIXNUM_MINUS(length_of_string_for_returning_floats_qm,
				number_of_zeros_to_remove));
		}
		result = twrite_number_string_suppressing_trailing_zeros(String_for_returning_floats,
			EQ(output_format,Qexponent) ? T : Nil);
	    }
	    else {
		if (minimum_width_qm) {
		    length_of_string_for_returning_floats_qm = 
			    length_of_null_terminated_string(String_for_returning_floats);
		    if (length_of_string_for_returning_floats_qm)
			twrite_spaces_if_necessary(minimum_width_qm,
				length_of_string_for_returning_floats_qm);
		}
		result = twrite_number_string_as_is(String_for_returning_floats);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object string_constant_25;  /* "th" */

static Object string_constant_26;  /* "st" */

static Object string_constant_27;  /* "d" */

/* SUPPLY-ORDINAL-SUFFIX */
Object supply_ordinal_suffix(count_1)
    Object count_1;
{
    Object temp;

    x_note_fn_call(26,237);
    temp = mod(count_1,FIX((SI_Long)100L));
    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
	    FIXNUM_LE(temp,FIX((SI_Long)127L)))) {
	temp = mod(count_1,FIX((SI_Long)10L));
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    temp = string_constant_25;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 1:
		temp = string_constant_26;
		break;
	      case 2:
		temp = string_constant_27;
		break;
	      case 3:
		temp = string_constant_27;
		break;
	      default:
		temp = string_constant_25;
		break;
	    }
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 11:
	  case 12:
	  case 13:
	    temp = string_constant_25;
	    break;
	  default:
	    temp = mod(count_1,FIX((SI_Long)10L));
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		temp = string_constant_25;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    temp = string_constant_26;
		    break;
		  case 2:
		    temp = string_constant_27;
		    break;
		  case 3:
		    temp = string_constant_27;
		    break;
		  default:
		    temp = string_constant_25;
		    break;
		}
	    break;
	}
    return VALUES_1(temp);
}

void unicode_INIT()
{
    Object named_dynamic_extent_description, temp;
    Object reclaim_structure_for_gensym_string_stream_1, table;
    Object svref_new_value;
    SI_Long i, ab_loop_bind_;
    Object AB_package, Qsize_of_string_for_returning_floats, float_constant_32;
    Object float_constant_31, float_constant_30, float_constant_29;
    Object float_constant_28, float_constant_27, float_constant_26;
    Object float_constant_25, float_constant_24, float_constant_23;
    Object float_constant_22, float_constant_21, float_constant_20;
    Object float_constant_19, float_constant_18, float_constant_17;
    Object float_constant_16, float_constant_15, float_constant_14;
    Object float_constant_13, float_constant_12, float_constant_11;
    Object float_constant_10, float_constant_9, float_constant_8;
    Object float_constant_7, float_constant_6, float_constant_5;
    Object float_constant_4, float_constant_3, Qnew_decade_table_size;
    Object Qlength_of_wide_twrite_fixnum_buffer, list_constant_54;
    Object Qmake_wide_string_function, Kfuncall, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_30, list_constant_32, list_constant_34;
    Object list_constant_33, list_constant_31, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object Qtl_tl, Qtl_bs, Qab_and, Qpct, Qdol, Qab_or_1, Qex, Qqm, Qsc;
    Object list_constant_6, Qcol, Qcol_col, Qcm, Qcbt, Qobt, Qcp, Qop, Qct;
    Object list_constant_5, Qplus_, list_constant_4, list_constant_3;
    Object list_constant_2, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, Qread_character_code, Qgensym_string_stream;
    Object Qreclaim_structure, Qoutstanding_gensym_string_stream_count;
    Object Qgensym_string_stream_structure_memory_usage, Qutilities2;
    Object string_constant_32, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_31, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_30;
    Object string_constant_29, Qwide_string_list_maximum_length;
    Object Qnamed_dynamic_extent_description, Qutilities1, string_constant_28;

    x_note_fn_call(26,238);
    SET_PACKAGE("AB");
    if (Print_wide_string_max_length == UNBOUND)
	Print_wide_string_max_length = FIX((SI_Long)200L);
    if (Abbreviate_wide_strings_for_legibility == UNBOUND)
	Abbreviate_wide_strings_for_legibility = T;
    string_constant = STATIC_STRING("Byte-vector-16 ");
    string_constant_1 = STATIC_STRING("(");
    string_constant_2 = STATIC_STRING(")");
    string_constant_3 = STATIC_STRING("[");
    string_constant_4 = STATIC_STRING("|");
    string_constant_5 = STATIC_STRING("]");
    string_constant_6 = STATIC_STRING("\"");
    string_constant_7 = STATIC_STRING("...");
    string_constant_8 = STATIC_STRING("#w\"");
    AB_package = STATIC_PACKAGE("AB");
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    if (Lisp_highest_printable_character_code == UNBOUND)
	Lisp_highest_printable_character_code = FIX((SI_Long)255L);
    string_constant_9 = STATIC_STRING("UNSPECIFIED");
    Qstringw_should_not_cons_p = STATIC_SYMBOL("STRINGW-SHOULD-NOT-CONS-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstringw_should_not_cons_p,
	    Stringw_should_not_cons_p);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    record_system_variable(Qstringw_should_not_cons_p,Qunicode,T,Qt,Qnil,
	    Qnil,Qnil);
    Stringw_should_not_cons_p = Nil;
    string_constant_28 = STATIC_STRING("OUTPUTTING-TO-WIDE-STRING");
    if (Outputting_to_wide_string == UNBOUND)
	Outputting_to_wide_string = make_recursive_lock(2,Kname,
		string_constant_28);
    Qoutputting_to_wide_string = STATIC_SYMBOL("OUTPUTTING-TO-WIDE-STRING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutputting_to_wide_string,
	    Outputting_to_wide_string);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qoutputting_to_wide_string,
	    Qutilities1,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qoutputting_to_wide_string,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qwide_string_list_maximum_length = 
	    STATIC_SYMBOL("WIDE-STRING-LIST-MAXIMUM-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qwide_string_list_maximum_length,FIX((SI_Long)1024L));
    string_constant_29 = 
	    STATIC_STRING("Trying to write a string longer than 2MB!");
    Extend_current_text_string_error_message = string_constant_29;
    Qhandle_extend_current_text_string_error = 
	    STATIC_SYMBOL("HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR",
	    AB_package);
    Maximum_suggested_length_for_wide_strings = FIX((SI_Long)2048L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Knone = STATIC_SYMBOL("NONE",Pkeyword);
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    Qsymbol_name_wide_string = STATIC_SYMBOL("SYMBOL-NAME-WIDE-STRING",
	    AB_package);
    Symbol_name_wide_string_prop = Qsymbol_name_wide_string;
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qescape = STATIC_SYMBOL("ESCAPE",AB_package);
    Qunicode_u = STATIC_SYMBOL("UNICODE-U",AB_package);
    Maximum_text_string_length = FIX((SI_Long)1048576L);
    string_constant_30 = 
	    STATIC_STRING("Attempting to allocate ~a element string, ~\n   which is beyond the established maximum of ~a.");
    Maximum_text_string_length_exceeded_message = string_constant_30;
    Qlength_when_written_parsably = 
	    STATIC_SYMBOL("LENGTH-WHEN-WRITTEN-PARSABLY",AB_package);
    Length_when_written_parsably_prop = Qlength_when_written_parsably;
    Qcount_of_interned_text_strings = 
	    STATIC_SYMBOL("COUNT-OF-INTERNED-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_interned_text_strings,
	    Count_of_interned_text_strings);
    record_system_variable(Qcount_of_interned_text_strings,Qunicode,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qmemory_used_for_interned_text_strings = 
	    STATIC_SYMBOL("MEMORY-USED-FOR-INTERNED-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmemory_used_for_interned_text_strings,
	    Memory_used_for_interned_text_strings);
    record_system_variable(Qmemory_used_for_interned_text_strings,Qunicode,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_string_stream_g2_struct = 
	    STATIC_SYMBOL("GENSYM-STRING-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgensym_string_stream = STATIC_SYMBOL("GENSYM-STRING-STREAM",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    Qgensym_string_stream,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgensym_string_stream,
	    Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gensym_string_stream == UNBOUND)
	The_type_description_of_gensym_string_stream = Nil;
    string_constant_31 = 
	    STATIC_STRING("43Dy8m83hvy1n83hvy8n8k1l8n0000001l1n8y83-4*y0krk0k0");
    temp = The_type_description_of_gensym_string_stream;
    The_type_description_of_gensym_string_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_31));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    The_type_description_of_gensym_string_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgensym_string_stream,
	    The_type_description_of_gensym_string_stream,
	    Qtype_description_of_type);
    Qoutstanding_gensym_string_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-GENSYM-STRING-STREAM-COUNT",AB_package);
    Qgensym_string_stream_structure_memory_usage = 
	    STATIC_SYMBOL("GENSYM-STRING-STREAM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_32 = STATIC_STRING("1q83hvy8s83-WIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gensym_string_stream_count);
    push_optimized_constant(Qgensym_string_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_32));
    Qchain_of_available_gensym_string_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-STRING-STREAMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gensym_string_streams,
	    Chain_of_available_gensym_string_streams);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gensym_string_streams,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgensym_string_stream_count = 
	    STATIC_SYMBOL("GENSYM-STRING-STREAM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_string_stream_count,
	    Gensym_string_stream_count);
    record_system_variable(Qgensym_string_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gensym_string_streams_vector == UNBOUND)
	Chain_of_available_gensym_string_streams_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgensym_string_stream_structure_memory_usage,
	    STATIC_FUNCTION(gensym_string_stream_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_string_stream_count,
	    STATIC_FUNCTION(outstanding_gensym_string_stream_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gensym_string_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gensym_string_stream,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qgensym_string_stream,
	    reclaim_structure_for_gensym_string_stream_1);
    Qread_character_code = STATIC_SYMBOL("READ-CHARACTER-CODE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_character_code,
	    STATIC_FUNCTION(read_character_code,NIL,FALSE,1,1));
    string_constant_33 = STATIC_STRING("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (Base_36_digits_string == UNBOUND)
	Base_36_digits_string = stringw(string_constant_33);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qalpha = STATIC_SYMBOL("ALPHA",AB_package);
    Qbeta = STATIC_SYMBOL("BETA",AB_package);
    Qrev_dot = STATIC_SYMBOL("REV.",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qinteger,Qfloat);
    string_constant_34 = STATIC_STRING("It is empty.");
    if (Message_illegal_symbol_text_string_empty == UNBOUND)
	Message_illegal_symbol_text_string_empty = stringw(string_constant_34);
    string_constant_35 = STATIC_STRING("It contains a newline character.");
    if (Message_illegal_symbol_text_string_contains_a_newline == UNBOUND)
	Message_illegal_symbol_text_string_contains_a_newline = 
		stringw(string_constant_35);
    string_constant_36 = 
	    STATIC_STRING("It contains the illegal character whose code is (hex) FFFF");
    if (Message_illegal_symbol_text_string_contains_ffff == UNBOUND)
	Message_illegal_symbol_text_string_contains_ffff = 
		stringw(string_constant_36);
    string_constant_37 = 
	    STATIC_STRING("It contains the illegal character whose code is (hex) FFFE");
    if (Message_illegal_symbol_text_string_contains_fffe == UNBOUND)
	Message_illegal_symbol_text_string_contains_fffe = 
		stringw(string_constant_37);
    string_constant_38 = 
	    STATIC_STRING("It is longer than the maximum length for symbols, 65533.");
    if (Message_illegal_symbol_text_string_too_long == UNBOUND)
	Message_illegal_symbol_text_string_too_long = 
		stringw(string_constant_38);
    list_constant_2 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)61L),Qnum_le);
    list_constant_7 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)60L),Qnum_lt,
	    list_constant_2);
    list_constant_3 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)61L),Qnum_ge);
    list_constant_8 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)62L),Qnum_gt,
	    list_constant_3);
    list_constant_4 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)61L),Qnum_ne);
    list_constant_9 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)47L),Qslash,
	    list_constant_4);
    list_constant_10 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)61L),Qnum_eq);
    Qplus_ = STATIC_SYMBOL("+-",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)45L),Qplus_);
    list_constant_11 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)43L),Qplus,
	    list_constant_5);
    list_constant_12 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)42L),Qstar);
    Qct = STATIC_SYMBOL("^",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)94L),Qct);
    Qop = STATIC_SYMBOL("(",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)40L),Qop);
    Qcp = STATIC_SYMBOL(")",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)41L),Qcp);
    Qobt = STATIC_SYMBOL("[",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)91L),Qobt);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)93L),Qcbt);
    Qcm = STATIC_SYMBOL(",",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)44L),Qcm);
    Qcol = STATIC_SYMBOL(":",AB_package);
    Qcol_col = STATIC_SYMBOL("::",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)58L),Qcol_col);
    list_constant_19 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)58L),Qcol,
	    list_constant_6);
    Qsc = STATIC_SYMBOL(";",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)59L),Qsc);
    Qqm = STATIC_SYMBOL("\?",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)63L),Qqm);
    Qex = STATIC_SYMBOL("!",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)33L),Qex);
    Qab_or_1 = STATIC_SYMBOL("|",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)124L),Qab_or_1);
    Qdol = STATIC_SYMBOL("$",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)36L),Qdol);
    Qpct = STATIC_SYMBOL("%",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)37L),Qpct);
    Qab_and = STATIC_SYMBOL("&",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)38L),Qab_and);
    Qtl_bs = STATIC_SYMBOL("~\\",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)92L),Qtl_bs);
    Qtl_tl = STATIC_SYMBOL("~~",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)126L),Qtl_tl);
    list_constant_29 = STATIC_LIST((SI_Long)22L,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14,list_constant_15,list_constant_16,
	    list_constant_17,list_constant_18,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23,list_constant_24,list_constant_25,
	    list_constant_26,list_constant_27,list_constant_28);
    Punctuation_alist = list_constant_29;
    Qpunctuation_mark_p = STATIC_SYMBOL("PUNCTUATION-MARK-P",AB_package);
    note_punctuation_marks_as_such(Punctuation_alist);
    list_constant_30 = STATIC_CONS(Qt,Qnil);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)4L,Qnil,Qnil,Qt,
	    list_constant_30);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)32L),Qnil,
	    Qnil,list_constant_31);
    list_constant_32 = STATIC_LIST_STAR((SI_Long)3L,Qt,Qt,list_constant_31);
    list_constant_36 = STATIC_CONS(FIX((SI_Long)47L),list_constant_32);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qt,Qnil);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)41L),Qt,
	    Qnil,Qclose,FIX((SI_Long)40L),list_constant_33);
    list_constant_34 = STATIC_CONS(Qnil,list_constant_30);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)40L),Qnil,
	    Qt,Qopen,FIX((SI_Long)41L),list_constant_34);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)93L),Qt,
	    Qnil,Qclose,FIX((SI_Long)93L),list_constant_33);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)91L),Qnil,
	    Qt,Qopen,FIX((SI_Long)93L),list_constant_34);
    list_constant_41 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)125L),Qt,
	    Qnil,Qclose,FIX((SI_Long)123L),list_constant_33);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)6L,FIX((SI_Long)123L),
	    Qnil,Qt,Qopen,FIX((SI_Long)125L),list_constant_34);
    list_constant_43 = STATIC_CONS(FIX((SI_Long)33L),list_constant_30);
    list_constant_44 = STATIC_CONS(FIX((SI_Long)44L),list_constant_30);
    list_constant_45 = STATIC_CONS(FIX((SI_Long)58L),list_constant_30);
    list_constant_46 = STATIC_CONS(FIX((SI_Long)59L),list_constant_30);
    list_constant_47 = STATIC_CONS(FIX((SI_Long)63L),list_constant_30);
    list_constant_48 = STATIC_CONS(FIX((SI_Long)92L),list_constant_32);
    list_constant_49 = STATIC_CONS(FIX((SI_Long)161L),list_constant_30);
    list_constant_50 = STATIC_CONS(FIX((SI_Long)8482L),list_constant_30);
    list_constant_51 = STATIC_CONS(FIX((SI_Long)174L),list_constant_30);
    list_constant_52 = STATIC_CONS(FIX((SI_Long)191L),list_constant_30);
    list_constant_53 = STATIC_LIST((SI_Long)18L,list_constant_35,
	    list_constant_36,list_constant_37,list_constant_38,
	    list_constant_39,list_constant_40,list_constant_41,
	    list_constant_42,list_constant_43,list_constant_44,
	    list_constant_45,list_constant_46,list_constant_47,
	    list_constant_48,list_constant_49,list_constant_50,
	    list_constant_51,list_constant_52);
    Standard_character_syntax_table = list_constant_53;
    if (Current_character_syntax_table == UNBOUND)
	Current_character_syntax_table = Standard_character_syntax_table;
    Ellipsis_text_string = stringw(string_constant_7);
    Ellipsis_text_string_length = FIX((SI_Long)3L);
    Punctuation_mark_p_prop = Qpunctuation_mark_p;
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    Type_of_syntactic_anomaly_prop = Qtype_of_syntactic_anomaly;
    string_constant_10 = STATIC_STRING("A ");
    string_constant_11 = STATIC_STRING("a ");
    string_constant_12 = STATIC_STRING("An ");
    string_constant_13 = STATIC_STRING("an ");
    Qwide_twrite_fixnum_buffer = STATIC_SYMBOL("WIDE-TWRITE-FIXNUM-BUFFER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwide_twrite_fixnum_buffer,
	    Wide_twrite_fixnum_buffer);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_wide_string_function = STATIC_SYMBOL("MAKE-WIDE-STRING-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_wide_string_function,
	    STATIC_FUNCTION(make_wide_string_function,NIL,FALSE,1,1));
    list_constant_54 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qmake_wide_string_function,FIX((SI_Long)24L));
    record_system_variable(Qwide_twrite_fixnum_buffer,Qunicode,
	    list_constant_54,Qnil,Qt,Qnil,Qnil);
    Qlength_of_wide_twrite_fixnum_buffer = 
	    STATIC_SYMBOL("LENGTH-OF-WIDE-TWRITE-FIXNUM-BUFFER",AB_package);
    SET_SYMBOL_VALUE(Qlength_of_wide_twrite_fixnum_buffer,FIX((SI_Long)24L));
    if (Most_negative_fixnum_as_string == UNBOUND)
	Most_negative_fixnum_as_string = format((SI_Long)3L,Nil,"~D",
		Most_negative_fixnum);
    if (Length_of_most_negative_fixnum_as_string == UNBOUND)
	Length_of_most_negative_fixnum_as_string = 
		length(Most_negative_fixnum_as_string);
    if (Twrite_fixnum_buffer == UNBOUND)
	Twrite_fixnum_buffer = make_string(1,FIX((SI_Long)24L));
    string_constant_14 = STATIC_STRING("-9223372036854775808");
    string_constant_15 = STATIC_STRING("L");
    Smallest_order_of_magnitude = FIX((SI_Long)-307L);
    float_constant_3 = STATIC_FLOAT(10.0);
    Float_with_smallest_order_of_magnitude = expt(float_constant_3,
	    Smallest_order_of_magnitude);
    Order_of_largest_fixnum_power_of_ten = 
	    lfloor(llog(Most_positive_fixnum,FIX((SI_Long)10L)),_);
    table = make_array(1,add1(Order_of_largest_fixnum_power_of_ten));
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Order_of_largest_fixnum_power_of_ten);
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    svref_new_value = expt(FIX((SI_Long)10L),FIX(i));
    ISVREF(table,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    Integer_decade_table = table;
    goto end_1;
    Integer_decade_table = Qnil;
  end_1:;
    string_constant_16 = STATIC_STRING("~x");
    Qnew_decade_table_size = STATIC_SYMBOL("NEW-DECADE-TABLE-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qnew_decade_table_size,FIX((SI_Long)16L));
    float_constant_1 = STATIC_FLOAT(1.0);
    float_constant_4 = STATIC_FLOAT(100.0);
    float_constant_5 = STATIC_FLOAT(1000.0);
    float_constant_6 = STATIC_FLOAT(10000.0);
    float_constant_7 = STATIC_FLOAT(100000.0);
    float_constant_8 = STATIC_FLOAT(1000000.0);
    float_constant_9 = STATIC_FLOAT(1.0E+7);
    float_constant_10 = STATIC_FLOAT(1.0E+8);
    float_constant_11 = STATIC_FLOAT(1.0E+9);
    float_constant_12 = STATIC_FLOAT(1.0E+10);
    float_constant_13 = STATIC_FLOAT(1.0E+11);
    float_constant_14 = STATIC_FLOAT(1.0E+12);
    float_constant_15 = STATIC_FLOAT(1.0E+13);
    float_constant_16 = STATIC_FLOAT(1.0E+14);
    float_constant_17 = STATIC_FLOAT(1.0E+15);
    table = make_array(1,FIX((SI_Long)16L));
    SVREF(table,FIX((SI_Long)0L)) = float_constant_1;
    SVREF(table,FIX((SI_Long)1L)) = float_constant_3;
    SVREF(table,FIX((SI_Long)2L)) = float_constant_4;
    SVREF(table,FIX((SI_Long)3L)) = float_constant_5;
    SVREF(table,FIX((SI_Long)4L)) = float_constant_6;
    SVREF(table,FIX((SI_Long)5L)) = float_constant_7;
    SVREF(table,FIX((SI_Long)6L)) = float_constant_8;
    SVREF(table,FIX((SI_Long)7L)) = float_constant_9;
    SVREF(table,FIX((SI_Long)8L)) = float_constant_10;
    SVREF(table,FIX((SI_Long)9L)) = float_constant_11;
    SVREF(table,FIX((SI_Long)10L)) = float_constant_12;
    SVREF(table,FIX((SI_Long)11L)) = float_constant_13;
    SVREF(table,FIX((SI_Long)12L)) = float_constant_14;
    SVREF(table,FIX((SI_Long)13L)) = float_constant_15;
    SVREF(table,FIX((SI_Long)14L)) = float_constant_16;
    SVREF(table,FIX((SI_Long)15L)) = float_constant_17;
    New_decade_table = table;
    float_constant_18 = STATIC_FLOAT(0.1);
    float_constant_19 = STATIC_FLOAT(0.01);
    float_constant_20 = STATIC_FLOAT(0.001);
    float_constant_21 = STATIC_FLOAT(1.0E-4);
    float_constant_22 = STATIC_FLOAT(1.0E-5);
    float_constant_23 = STATIC_FLOAT(1.0E-6);
    float_constant_24 = STATIC_FLOAT(1.0E-7);
    float_constant_25 = STATIC_FLOAT(1.0E-8);
    float_constant_26 = STATIC_FLOAT(1.0E-9);
    float_constant_27 = STATIC_FLOAT(1.0E-10);
    float_constant_28 = STATIC_FLOAT(1.0E-11);
    float_constant_29 = STATIC_FLOAT(1.0E-12);
    float_constant_30 = STATIC_FLOAT(1.0E-13);
    float_constant_31 = STATIC_FLOAT(1.0E-14);
    float_constant_32 = STATIC_FLOAT(1.0E-15);
    table = make_array(1,FIX((SI_Long)16L));
    SVREF(table,FIX((SI_Long)0L)) = float_constant_1;
    SVREF(table,FIX((SI_Long)1L)) = float_constant_18;
    SVREF(table,FIX((SI_Long)2L)) = float_constant_19;
    SVREF(table,FIX((SI_Long)3L)) = float_constant_20;
    SVREF(table,FIX((SI_Long)4L)) = float_constant_21;
    SVREF(table,FIX((SI_Long)5L)) = float_constant_22;
    SVREF(table,FIX((SI_Long)6L)) = float_constant_23;
    SVREF(table,FIX((SI_Long)7L)) = float_constant_24;
    SVREF(table,FIX((SI_Long)8L)) = float_constant_25;
    SVREF(table,FIX((SI_Long)9L)) = float_constant_26;
    SVREF(table,FIX((SI_Long)10L)) = float_constant_27;
    SVREF(table,FIX((SI_Long)11L)) = float_constant_28;
    SVREF(table,FIX((SI_Long)12L)) = float_constant_29;
    SVREF(table,FIX((SI_Long)13L)) = float_constant_30;
    SVREF(table,FIX((SI_Long)14L)) = float_constant_31;
    SVREF(table,FIX((SI_Long)15L)) = float_constant_32;
    New_fractional_decade_table = table;
    Qsize_of_string_for_returning_floats = 
	    STATIC_SYMBOL("SIZE-OF-STRING-FOR-RETURNING-FLOATS",AB_package);
    SET_SYMBOL_VALUE(Qsize_of_string_for_returning_floats,FIX((SI_Long)100L));
    if (String_for_returning_floats == UNBOUND)
	String_for_returning_floats = make_string(1,
		Size_of_string_for_returning_floats);
    if (Null_char == UNBOUND)
	Null_char = CODE_CHAR(FIX((SI_Long)0L));
    string_constant_17 = STATIC_STRING("%.*f");
    string_constant_18 = STATIC_STRING("%.*g");
    string_constant_19 = STATIC_STRING("%.*e");
    float_constant = STATIC_FLOAT(0.0);
    float_constant_2 = STATIC_FLOAT(-1.0);
    string_constant_20 = STATIC_STRING("0.0");
    if (Maximum_significant_decimal_digits_in_gensym_float == UNBOUND)
	Maximum_significant_decimal_digits_in_gensym_float = FIX((SI_Long)15L);
    if (Write_floats_accurately_p == UNBOUND)
	Write_floats_accurately_p = Nil;
    Qwrite_floating_point_number = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER",AB_package);
    string_constant_21 = STATIC_STRING("NaN");
    string_constant_22 = STATIC_STRING("+Inf");
    string_constant_23 = STATIC_STRING("-Inf");
    SET_SYMBOL_FUNCTION(Qwrite_floating_point_number,
	    STATIC_FUNCTION(write_floating_point_number,NIL,TRUE,1,10));
    if (Default_float_to_text_format == UNBOUND)
	Default_float_to_text_format = Nil;
    Qwrite_floating_point_number_simple_c_format = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER-SIMPLE-C-FORMAT",
	    AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qexponent = STATIC_SYMBOL("EXPONENT",AB_package);
    Qbest = STATIC_SYMBOL("BEST",AB_package);
    Qforce_zero = STATIC_SYMBOL("FORCE-ZERO",AB_package);
    string_constant_24 = STATIC_STRING("####");
    SET_SYMBOL_FUNCTION(Qwrite_floating_point_number_simple_c_format,
	    STATIC_FUNCTION(write_floating_point_number_simple_c_format,
	    NIL,TRUE,1,5));
    string_constant_25 = STATIC_STRING("th");
    string_constant_26 = STATIC_STRING("st");
    string_constant_27 = STATIC_STRING("d");
}
