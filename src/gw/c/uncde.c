/* uncde.c
 * Input file:  unicode.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "uncde.h"


/* UNICODE-UPPERCASE-IF-LOWERCASE */
Object g2int_unicode_uppercase_if_lowercase(code_init)
    Object code_init;
{
    Object temp;
    SI_Long code;

    x_note_fn_call(24,0);
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
Object g2int_unicode_lowercase_if_uppercase(code_init)
    Object code_init;
{
    Object temp;
    SI_Long code;

    x_note_fn_call(24,1);
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
Object g2int_valid_wide_string_length_bv16(wide_string_bv16)
    Object wide_string_bv16;
{
    Object temp_1;
    SI_Long bv16_length, length_1;
    char temp;

    x_note_fn_call(24,2);
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    if (bv16_length >= IFIX(G2int_extra_wide_string_bv16_elements)) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = bv16_length - IFIX(G2int_extra_wide_string_bv16_elements) 
		>= UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? ((UBYTE_16_ISAREF_1(wide_string_bv16,bv16_length - 
	    (SI_Long)1L) & (SI_Long)57344L) == (SI_Long)57344L ? T : Nil) :
	     Nil;
    return VALUES_1(temp_1);
}

/* FILL-WIDE-STRING-1 */
Object g2int_fill_wide_string_1(wide_string,wide_character,start_init,end_init)
    Object wide_string, wide_character, start_init, end_init;
{
    SI_Long start, end, code, i, ab_loop_bind_;

    x_note_fn_call(24,3);
    start = IFIX(start_init);
    end = IFIX(end_init);
    code = IFIX(wide_character);
    i = start;
    ab_loop_bind_ = end;
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
Object g2int_make_wide_string_function(length_1)
    Object length_1;
{
    Object wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(24,4);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
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
Object g2int_reclaim_wide_string(wide_string)
    Object wide_string;
{
    x_note_fn_call(24,5);
    g2int_reclaim_byte_vector_16(wide_string);
    return VALUES_1(Nil);
}

/* CHARW-FUNCTION */
Object g2int_charw_function(wide_string,index_1)
    Object wide_string, index_1;
{
    Object temp;

    x_note_fn_call(24,6);
    temp = FIX(UBYTE_16_ISAREF_1(wide_string,IFIX(index_1)));
    return VALUES_1(temp);
}

/* SET-CHARW-FUNCTION */
Object g2int_set_charw_function(wide_string,index_1,wide_character)
    Object wide_string, index_1, wide_character;
{
    Object temp;

    x_note_fn_call(24,7);
    temp = FIX(UBYTE_16_ISASET_1(wide_string,IFIX(index_1),
	    IFIX(wide_character)));
    return VALUES_1(temp);
}

Object G2int_starprint_wide_string_max_lengthstar = UNBOUND;

Object G2int_starabbreviate_wide_strings_for_legibilitystar = UNBOUND;

/* PRINT-WIDE-STRING */
Object g2int_print_wide_string(wide_string,stream,print_depth)
    Object wide_string, stream, print_depth;
{
    x_note_fn_call(24,8);
    if (g2int_valid_wide_string_length_bv16(wide_string))
	return g2int_print_valid_wide_string(wide_string,stream);
    else
	return g2int_print_random_byte_vector_16(wide_string,stream);
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
Object g2int_print_random_byte_vector_16(byte_vector_16,stream)
    Object byte_vector_16, stream;
{
    Object dot_object_dot, dot_stream_dot, bv16_length;
    SI_Long physical_length_limit, i, ab_loop_bind_;

    x_note_fn_call(24,9);
    dot_object_dot = byte_vector_16;
    dot_stream_dot = stream;
    g2int_print_random_object_prefix_for_gsi(dot_object_dot,dot_stream_dot);
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
    g2int_print_wide_character_readably_in_string(FIX(UBYTE_16_ISAREF_1(byte_vector_16,
	    i)),stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (i < physical_length_limit)
	write_string(2,string_constant_7,stream);
    write_string(1,string_constant_6);
    return g2int_print_random_object_suffix_for_gsi(dot_object_dot,
	    dot_stream_dot);
}

/* PRINT-VALID-WIDE-STRING */
Object g2int_print_valid_wide_string(wide_string,stream)
    Object wide_string, stream;
{
    Object dot_object_dot, dot_stream_dot;
    SI_Long length_1;

    x_note_fn_call(24,10);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    length_1 = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    if (G2int_starabbreviate_wide_strings_for_legibilitystar && 
	    IFIX(G2int_starprint_wide_string_max_lengthstar) < length_1) {
	if (Print_escape) {
	    dot_object_dot = wide_string;
	    dot_stream_dot = stream;
	    g2int_print_random_object_prefix_for_gsi(dot_object_dot,
		    dot_stream_dot);
	    g2int_print_valid_wide_string_1(wide_string,stream,
		    FIX((SI_Long)0L),
		    G2int_starprint_wide_string_max_lengthstar,T);
	    return g2int_print_random_object_suffix_for_gsi(dot_object_dot,
		    dot_stream_dot);
	}
	else
	    return g2int_print_valid_wide_string_1(wide_string,stream,
		    FIX((SI_Long)0L),
		    G2int_starprint_wide_string_max_lengthstar,T);
    }
    else
	return g2int_print_valid_wide_string_1(wide_string,stream,
		FIX((SI_Long)0L),FIX(length_1),Nil);
}

static Object string_constant_8;   /* "#w\"" */

/* PRINT-VALID-WIDE-STRING-1 */
Object g2int_print_valid_wide_string_1(wide_string,stream,start,end,
	    print_ellipsis_p)
    Object wide_string, stream, start, end, print_ellipsis_p;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(24,11);
    if (Print_escape)
	write_string(2,string_constant_8,stream);
    i = IFIX(start);
    ab_loop_bind_ = IFIX(end);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    g2int_print_wide_character_readably_in_string(FIX(UBYTE_16_ISAREF_1(wide_string,
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
Object g2int_print_wide_character_readably_in_string(wide_character,stream)
    Object wide_character, stream;
{
    Object code, character_1;

    x_note_fn_call(24,12);
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
	return g2int_write_in_hex_to_lisp_stream(stream,code);
    }
}

/* PRETTY-PRINT-WIDE-CHARACTER-IN-STRING */
Object g2int_pretty_print_wide_character_in_string(wide_character,stream)
    Object wide_character, stream;
{
    x_note_fn_call(24,13);
    if (IFIX(wide_character) == (SI_Long)8232L)
	return write_char(CHR('\n'),stream);
    else
	return g2int_print_wide_character_readably_in_string(wide_character,
		stream);
}

/* PRETTY-PRINT-WIDE-STRING-TO-STREAM */
Object g2int_pretty_print_wide_string_to_stream(wide_string,stream)
    Object wide_string, stream;
{
    SI_Long i, length_1, ab_loop_bind_;

    x_note_fn_call(24,14);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    g2int_pretty_print_wide_character_in_string(FIX(UBYTE_16_ISAREF_1(wide_string,
	    i)),stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return write_char(CHR('\n'),stream);
}

/* PRETTY-PRINT-WIDE-STRING */
Object g2int_pretty_print_wide_string(wide_string)
    Object wide_string;
{
    x_note_fn_call(24,15);
    g2int_pretty_print_wide_string_to_stream(wide_string,Standard_output);
    return VALUES_0();
}

static Object Qg2int_wide_string;  /* wide-string */

/* TWRITE-WIDE-CHARACTER-READABLY */
Object g2int_twrite_wide_character_readably(wide_character)
    Object wide_character;
{
    Object code, character_1, temp, schar_arg_2, schar_new_value, thing_1;
    char thing;

    x_note_fn_call(24,16);
    code = wide_character;
    if ((SI_Long)0L <= IFIX(code) && IFIX(code) <= (SI_Long)255L) {
	character_1 = CODE_CHAR(code);
	if (Print_escape && (CHAR_EQ(character_1,CHR('\\')) || 
		CHAR_EQ(character_1,CHR('\"')))) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = '\\';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = '\\';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = character_1;
	    return g2int_twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
	}
    }
    else {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = '\\';
	    g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = '\\';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = 'u';
	    g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = 'u';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	if (IFIX(code) <= (SI_Long)4095L) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = '0';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (IFIX(code) <= (SI_Long)255L) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = '0';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	}
	if (IFIX(code) <= (SI_Long)15L) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = '0';
		g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = '0';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	}
	return g2int_twrite_positive_fixnum_in_radix(code,FIX((SI_Long)16L));
    }
}

Object G2int_lisp_highest_printable_character_code = UNBOUND;

/* PRINT-WIDE-CHARACTER */
Object g2int_print_wide_character varargs_1(int, n)
{
    Object wide_character;
    Object stream, code, character_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,17);
    INIT_ARGS_nonrelocating();
    wide_character = REQUIRED_ARG_nonrelocating();
    stream = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(stream))
	stream = Standard_output;
    code = wide_character;
    if ((SI_Long)0L <= IFIX(code) && FIXNUM_LE(code,
	    G2int_lisp_highest_printable_character_code)) {
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
	return g2int_write_in_hex_to_lisp_stream(stream,code);
    }
}

/* WRITE-IN-HEX-TO-LISP-STREAM */
Object g2int_write_in_hex_to_lisp_stream(stream,non_negative_fixnum)
    Object stream, non_negative_fixnum;
{
    SI_Long radix, temp, quotient, remainder_1;

    x_note_fn_call(24,18);
    radix = (SI_Long)16L;
    if (IFIX(non_negative_fixnum) >= radix) {
	temp = IFIX(non_negative_fixnum) / radix;
	quotient = temp;
	temp = IFIX(non_negative_fixnum) % radix;
	remainder_1 = temp;
	g2int_write_in_hex_to_lisp_stream(stream,FIX(quotient));
	write_char(digit_char(FIX(remainder_1),FIX(radix),_),stream);
    }
    else
	write_char(digit_char(non_negative_fixnum,FIX(radix),_),stream);
    return VALUES_1(Nil);
}

/* MAKE-STRINGW-FUNCTION */
Object g2int_make_stringw_function(length_1,initial_element)
    Object length_1, initial_element;
{
    Object wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(24,19);
    if (initial_element) {
	wide_string_bv16 = 
		g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
		(SI_Long)3L));
	g2int_fill_wide_string_1(wide_string_bv16,initial_element,
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
	wide_string_bv16 = 
		g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
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
Object g2int_lengthw(real_sequence_or_wide_string)
    Object real_sequence_or_wide_string;
{
    Object temp;
    SI_Long length_1;

    x_note_fn_call(24,20);
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
Object g2int_eltw(real_sequence_or_wide_string,i)
    Object real_sequence_or_wide_string, i;
{
    Object temp;

    x_note_fn_call(24,21);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(real_sequence_or_wide_string) 
	    != (SI_Long)0L ? 
	    FIX(UBYTE_16_ISAREF_1(real_sequence_or_wide_string,IFIX(i))) : 
	    elt(real_sequence_or_wide_string,i);
    return VALUES_1(temp);
}

/* CHAR=W-FUNCTION */
Object g2int_chareqw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object temp;

    x_note_fn_call(24,22);
    temp = FIXNUM_EQ(wide_character_1,wide_character_2) ? T : Nil;
    return VALUES_1(temp);
}

/* CHAR/=W-FUNCTION */
Object g2int_charsleqw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object temp;

    x_note_fn_call(24,23);
    temp = FIXNUM_NE(wide_character_1,wide_character_2) ? T : Nil;
    return VALUES_1(temp);
}

/* CHAR-EQUALW-FUNCTION */
Object g2int_char_equalw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object code, temp, temp_1;

    x_note_fn_call(24,24);
    code = wide_character_1;
    if (IFIX(code) < (SI_Long)127L)
	temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ? 
		FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp = g2int_unicode_lowercase_if_uppercase(code);
	if (temp);
	else
	    temp = code;
    }
    code = wide_character_2;
    if (IFIX(code) < (SI_Long)127L)
	temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_1 = g2int_unicode_lowercase_if_uppercase(code);
	if (temp_1);
	else
	    temp_1 = code;
    }
    temp_1 = NUM_EQ(temp,temp_1) ? T : Nil;
    return VALUES_1(temp_1);
}

/* CHAR-LESSPW-FUNCTION */
Object g2int_char_lesspw_function(wide_character_1,wide_character_2)
    Object wide_character_1, wide_character_2;
{
    Object code, temp, temp_1;

    x_note_fn_call(24,25);
    code = wide_character_1;
    if (IFIX(code) < (SI_Long)127L)
	temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ? 
		FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp = g2int_unicode_lowercase_if_uppercase(code);
	if (temp);
	else
	    temp = code;
    }
    code = wide_character_2;
    if (IFIX(code) < (SI_Long)127L)
	temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= (SI_Long)90L ?
		 FIX(IFIX(code) + (SI_Long)32L) : code;
    else {
	temp_1 = g2int_unicode_lowercase_if_uppercase(code);
	if (temp_1);
	else
	    temp_1 = code;
    }
    temp_1 = NUM_LT(temp,temp_1) ? T : Nil;
    return VALUES_1(temp_1);
}

/* LOWER-CASE-PW */
Object g2int_lower_case_pw(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,26);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)97L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)122L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHA-CHAR-PW-FUNCTION */
Object g2int_alpha_char_pw_function(wide_character)
    Object wide_character;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(24,27);
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
Object g2int_alphanumericpw_function(wide_character)
    Object wide_character;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(24,28);
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
Object g2int_digit_char_pw_function(wide_char_init,radix_init)
    Object wide_char_init, radix_init;
{
    Object temp;
    SI_Long wide_char, radix, char_code_1, arg, arg_1, arg_2;

    x_note_fn_call(24,29);
    wide_char = IFIX(wide_char_init);
    radix = IFIX(radix_init);
    char_code_1 = wide_char;
    arg = IFIX(G2int_pct0);
    arg_1 = char_code_1;
    arg_2 = radix < (SI_Long)10L ? IFIX(G2int_pct0) + (radix - 
	    (SI_Long)1L) : IFIX(G2int_pct9);
    if (arg <= arg_1 && arg_1 <= arg_2)
	temp = FIX(char_code_1 - IFIX(G2int_pct0));
    else if (radix <= (SI_Long)10L)
	temp = Nil;
    else {
	arg = IFIX(G2int_pcta);
	arg_1 = char_code_1;
	arg_2 = IFIX(G2int_pcta) + (radix - (SI_Long)10L - (SI_Long)1L);
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = FIX(char_code_1 - IFIX(FIXNUM_MINUS(G2int_pcta,
		    FIX((SI_Long)10L))));
	else {
	    arg = IFIX(ab_G2int_pcta);
	    arg_1 = char_code_1;
	    arg_2 = IFIX(ab_G2int_pcta) + (radix - (SI_Long)10L - (SI_Long)1L);
	    if (arg <= arg_1 && arg_1 <= arg_2)
		temp = FIX(char_code_1 - IFIX(FIXNUM_MINUS(ab_G2int_pcta,
			FIX((SI_Long)10L))));
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* DECIMAL-DIGIT-CHAR-PW-FUNCTION */
Object g2int_decimal_digit_char_pw_function(wide_character)
    Object wide_character;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(24,30);
    gensymed_symbol = IFIX(wide_character);
    return VALUES_1((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil);
}

/* HEXADECIMAL-DIGIT-CHAR-PW-FUNCTION */
Object g2int_hexadecimal_digit_char_pw_function(wide_character)
    Object wide_character;
{
    Object temp;

    x_note_fn_call(24,31);
    temp = g2int_digit_char_pw_function(wide_character,FIX((SI_Long)16L));
    return VALUES_1(temp);
}

static Object string_constant_9;   /* "UNSPECIFIED" */

/* STRINGW */
Object g2int_stringw(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(24,32);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	temp = thing;
    else if (FIXNUMP(thing))
	temp = g2int_make_stringw_function(FIX((SI_Long)1L),thing);
    else if (SYMBOLP(thing))
	temp = g2int_symbol_namew(thing);
    else if (STRINGP(thing))
	temp = g2int_copy_as_wide_string(thing);
    else
	temp = g2int_copy_as_wide_string(string_constant_9);
    return VALUES_1(temp);
}

Object G2int_stringw_should_not_cons_p = UNBOUND;

/* STRING-GREATERPW */
Object g2int_string_greaterpw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,33);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    temp = IFIX(result_1) > (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING>W */
Object g2int_stringgtw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,34);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    temp = IFIX(result_1) > (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING-LESSPW */
Object g2int_string_lesspw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,35);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    temp = IFIX(result_1) < (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING<W */
Object g2int_stringltw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,36);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    temp = IFIX(result_1) < (SI_Long)0L ? 
	    FIXNUM_SUB1(FIXNUM_ABS(result_1)) : Nil;
    return VALUES_1(temp);
}

/* STRING-NOT-EQUALW */
Object g2int_string_not_equalw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,37);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,T,Nil);
    temp =  !(IFIX(result_1) == (SI_Long)0L) ? FIXNUM_SUB1(result_1) : Nil;
    return VALUES_1(temp);
}

/* STRING/=W */
Object g2int_stringsleqw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp;

    x_note_fn_call(24,38);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,T,T);
    temp =  !(IFIX(result_1) == (SI_Long)0L) ? FIXNUM_SUB1(result_1) : Nil;
    return VALUES_1(temp);
}

/* STRING-NOT-GREATERPW */
Object g2int_string_not_greaterpw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(24,39);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    if (IFIX(result_1) < (SI_Long)0L)
	temp = FIXNUM_SUB1(FIXNUM_ABS(result_1));
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = g2int_stringw(wide_string_1);
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
Object g2int_stringlteqw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(24,40);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    if (IFIX(result_1) < (SI_Long)0L)
	temp = FIXNUM_SUB1(FIXNUM_ABS(result_1));
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = g2int_stringw(wide_string_1);
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
Object g2int_string_not_lesspw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(24,41);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,Nil);
    if (IFIX(result_1) > (SI_Long)0L)
	temp = FIXNUM_SUB1(result_1);
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = g2int_stringw(wide_string_1);
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
Object g2int_stringgteqw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object result_1, temp, wide_string_bv16;
    SI_Long length_1;

    x_note_fn_call(24,42);
    result_1 = g2int_wide_string_compare(wide_string_1,wide_string_2,Nil,T);
    if (IFIX(result_1) > (SI_Long)0L)
	temp = FIXNUM_SUB1(result_1);
    else if (IFIX(result_1) == (SI_Long)0L) {
	wide_string_bv16 = g2int_stringw(wide_string_1);
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
Object g2int_string_equalw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;

    x_note_fn_call(24,43);
    temp = IFIX(g2int_wide_string_compare(wide_string_1,wide_string_2,T,
	    Nil)) == (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* STRING=W */
Object g2int_stringeqw(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;

    x_note_fn_call(24,44);
    temp = EQ(wide_string_1,wide_string_2) ? T : Nil;
    if (temp);
    else
	temp = IFIX(g2int_wide_string_compare(wide_string_1,wide_string_2,
		T,T)) == (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* WIDE-STRING-COMPARE */
Object g2int_wide_string_compare(wide_string_1,wide_string_2,
	    just_check_equality_qm,consider_case_qm)
    Object wide_string_1, wide_string_2, just_check_equality_qm;
    Object consider_case_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, temp_1, downcase_code_qm;
    SI_Long length_1, length_1_1, length_2, gensymed_symbol_2, index_1, code_1;
    SI_Long code_2, code;
    char temp;

    x_note_fn_call(24,45);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(wide_string_1) != (SI_Long)0L);
    else if (FIXNUMP(wide_string_1))
	wide_string_1 = g2int_make_stringw_function(FIX((SI_Long)1L),
		wide_string_1);
    else if (SYMBOLP(wide_string_1))
	wide_string_1 = g2int_symbol_namew(wide_string_1);
    else if (STRINGP(wide_string_1))
	wide_string_1 = g2int_copy_as_wide_string(wide_string_1);
    else
	wide_string_1 = g2int_copy_as_wide_string(string_constant_9);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(wide_string_2) != (SI_Long)0L);
    else if (FIXNUMP(wide_string_2))
	wide_string_2 = g2int_make_stringw_function(FIX((SI_Long)1L),
		wide_string_2);
    else if (SYMBOLP(wide_string_2))
	wide_string_2 = g2int_symbol_namew(wide_string_2);
    else if (STRINGP(wide_string_2))
	wide_string_2 = g2int_copy_as_wide_string(wide_string_2);
    else
	wide_string_2 = g2int_copy_as_wide_string(string_constant_9);
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
	    goto end;
	}
	else if (index_1 >= length_2) {
	    temp_1 = FIX(index_1 + (SI_Long)1L);
	    goto end;
	}
	code_1 = UBYTE_16_ISAREF_1(wide_string_1,index_1);
	code_2 = UBYTE_16_ISAREF_1(wide_string_2,index_1);
	index_1 = index_1 + (SI_Long)1L;
	if ( !(code_1 == code_2)) {
	    temp_1 = just_check_equality_qm || code_1 > code_2 ? 
		    FIX(index_1) : FIX( - index_1);
	    goto end;
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end:;
    }
    else {
	index_1 = (SI_Long)0L;
	code_1 = (SI_Long)0L;
	code_2 = (SI_Long)0L;
      next_loop_1:
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
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp_1 = Qnil;
      end_1:;
    }
    return VALUES_1(temp_1);
}

/* COPY-WIDE-STRING-GIVEN-LENGTH */
Object g2int_copy_wide_string_given_length(wide_string_to_copy,length_1)
    Object wide_string_to_copy, length_1;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(24,46);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
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
Object g2int_copy_wide_string(wide_string_to_copy)
    Object wide_string_to_copy;
{
    Object wide_string_bv16, new_wide_string, binary_p, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, bv16_length, aref_arg_2, aref_new_value, length_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(24,47);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_to_copy));
    length_1 = UBYTE_16_ISAREF_1(wide_string_to_copy,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_to_copy,
	    length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_1 + 
	    (SI_Long)3L));
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
Object g2int_copy_constant_wide_string_given_length(wide_string_to_copy,
	    length_1)
    Object wide_string_to_copy, length_1;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(24,48);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
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
Object g2int_copy_as_wide_string(wide_string_or_lisp_string)
    Object wide_string_or_lisp_string;
{
    Object string_length, wide_string_bv16, result_1, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(24,49);
    if (STRINGP(wide_string_or_lisp_string)) {
	string_length = length(wide_string_or_lisp_string);
	wide_string_bv16 = 
		g2int_allocate_byte_vector_16(FIX(IFIX(string_length) + 
		(SI_Long)3L));
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
	g2int_copy_portion_of_string_into_text_string(wide_string_or_lisp_string,
		FIX((SI_Long)0L),string_length,result_1,FIX((SI_Long)0L));
	temp = result_1;
    }
    else
	temp = g2int_copy_wide_string(wide_string_or_lisp_string);
    return VALUES_1(temp);
}

/* COPY-PARTIAL-WIDE-STRING */
Object g2int_copy_partial_wide_string(wide_string_or_lisp_string,part_length)
    Object wide_string_or_lisp_string, part_length;
{
    Object wide_string_bv16, result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(24,50);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(IFIX(part_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(part_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(part_length) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(part_length),(SI_Long)0L);
    result_1 = wide_string_bv16;
    g2int_copy_portion_of_string_into_text_string(wide_string_or_lisp_string,
	    FIX((SI_Long)0L),part_length,result_1,FIX((SI_Long)0L));
    return VALUES_1(result_1);
}

/* WIDE-STRING-SUBSTRING */
Object g2int_wide_string_substring(wide_string,start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object start, end, wide_string_bv16, result_1, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(24,51);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end = end_qm;
    if (end);
    else {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	end = FIX(UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L));
    }
    part_length = IFIX(FIXNUM_MINUS(end,start));
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(part_length + 
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
Object g2int_equalw(a,b)
    Object a, b;
{
    Object temp;

    x_note_fn_call(24,52);
    if (CONSP(a) && CONSP(b))
	temp = g2int_equalw(CAR(a),CAR(b)) ? g2int_equalw(CDR(a),CDR(b)) : 
		Qnil;
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(a) != (SI_Long)0L && 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(b) != (SI_Long)0L)
	temp = g2int_stringeqw(a,b);
    else
	temp = EQUAL(a,b) ? T : Nil;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-MEMBER */
Object g2int_wide_character_member(item,list_1)
    Object item, list_1;
{
    Object items, temp;

    x_note_fn_call(24,53);
    items = list_1;
  next_loop:
    if ( !TRUEP(items))
	goto end_loop;
    temp = FIRST(items);
    if (EQL(item,temp)) {
	temp = items;
	goto end;
    }
    items = M_CDR(items);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-ASSOC */
Object g2int_wide_character_assoc(item,a_list)
    Object item, a_list;
{
    Object sublist, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(24,54);
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
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* WIDE-CHARACTER-RASSOC */
Object g2int_wide_character_rassoc(item,a_list)
    Object item, a_list;
{
    Object sublist, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(24,55);
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
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* POSITION-IN-WIDE-STRING */
Object g2int_position_in_wide_string(wide_character_init,wide_string)
    Object wide_character_init, wide_string;
{
    Object temp;
    SI_Long wide_character, i, length_1, ab_loop_bind_;

    x_note_fn_call(24,56);
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
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* REMOVE-CHARACTER-FROM-WIDE-STRING */
Object g2int_remove_character_from_wide_string(wide_character_init,wide_string)
    Object wide_character_init, wide_string;
{
    Object count_1, wide_string_bv16, new_string, j;
    SI_Long wide_character, i, length_1, ab_loop_bind_, ab_loopvar_;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2, bv16_length, temp;
    SI_Long aref_new_value;

    x_note_fn_call(24,57);
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
    goto end;
    count_1 = Qnil;
  end:;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    gensymed_symbol = UBYTE_16_ISAREF_1(wide_string,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    gensymed_symbol_1 = IFIX(count_1);
    length_2 = gensymed_symbol - gensymed_symbol_1;
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_2 + 
	    (SI_Long)3L));
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
Object g2int_search_wide_string varargs_1(int, n)
{
    Object pattern, wide_string, start_qm, end_qm;
    Object skip_quoted_portions_qm, patlen, end, escape, quoted, temp, ch;
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long i, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_3, temp_1;
    SI_Long gensymed_symbol_4;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,58);
    INIT_ARGS_nonrelocating();
    pattern = REQUIRED_ARG_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    start_qm = REQUIRED_ARG_nonrelocating();
    end_qm = REQUIRED_ARG_nonrelocating();
    skip_quoted_portions_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    patlen = g2int_lengthw(pattern);
    end = end_qm;
    if (end);
    else
	end = g2int_lengthw(wide_string);
    escape = Nil;
    quoted = Nil;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    ab_loop_bind_ = IFIX(FIXNUM_MINUS(end,patlen));
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
	temp_1 = IFIX(end) - i;
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
Object g2int_string_upcasew(wide_string)
    Object wide_string;
{
    Object new_string, aref_new_value, temp;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(24,59);
    new_string = g2int_copy_wide_string(wide_string);
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
	aref_new_value = g2int_unicode_uppercase_if_lowercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(new_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_string;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* STRING-DOWNCASEW */
Object g2int_string_downcasew(wide_string)
    Object wide_string;
{
    Object new_string, aref_new_value, temp;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(24,60);
    new_string = g2int_copy_wide_string(wide_string);
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
	aref_new_value = g2int_unicode_lowercase_if_uppercase(FIX(code));
	if (aref_new_value);
	else
	    aref_new_value = FIX(code);
    }
    UBYTE_16_ISASET_1(new_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_string;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* NSTRING-UPCASEW */
Object g2int_nstring_upcasew(wide_string)
    Object wide_string;
{
    Object aref_new_value;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(24,61);
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
	aref_new_value = g2int_unicode_uppercase_if_lowercase(FIX(code));
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
Object g2int_nstring_downcasew(wide_string)
    Object wide_string;
{
    Object aref_new_value;
    SI_Long i, length_1, ab_loop_bind_, wide_character, code;

    x_note_fn_call(24,62);
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
	aref_new_value = g2int_unicode_lowercase_if_uppercase(FIX(code));
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
Object g2int_simple_symbol_wide_character_p(wide_character)
    Object wide_character;
{
    Object code, temp;

    x_note_fn_call(24,63);
    code = wide_character;
    temp = IFIX(code) <= (SI_Long)127L ? 
	    g2int_simple_symbol_character_p(wide_character) : Nil;
    return VALUES_1(temp);
}

/* SIMPLE-PATHNAME-WIDE-CHARACTER-P */
Object g2int_simple_pathname_wide_character_p(wide_character)
    Object wide_character;
{
    Object code, character_qm, temp;

    x_note_fn_call(24,64);
    code = wide_character;
    character_qm = IFIX(code) <= (SI_Long)127L ? CODE_CHAR(code) : Nil;
    temp = character_qm ? g2int_simple_pathname_character_p(character_qm) :
	     Qnil;
    return VALUES_1(temp);
}

Object G2int_current_wide_string = UNBOUND;

Object G2int_fill_pointer_for_current_wide_string = UNBOUND;

Object G2int_total_length_of_current_wide_string = UNBOUND;

Object G2int_current_wide_string_list = UNBOUND;

Object G2int_extend_current_text_string_error_message = UNBOUND;

static Object Qg2int_handle_extend_current_text_string_error;  /* handle-extend-current-text-string-error */

/* EXTEND-CURRENT-WIDE-STRING */
Object g2int_extend_current_wide_string(minimum_new_total_length)
    Object minimum_new_total_length;
{
    Object new_string_length, wide_string_bv16, new_wide_string, aref_arg_1;
    Object aref_arg_2_1, temp, temp_2, new_total_length, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, temp_1, arg, arg_1, arg_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp_3;

    x_note_fn_call(24,65);
    if (FIXNUM_GT(minimum_new_total_length,G2int_maximum_wide_string_length)) {
	if (fboundp(Qg2int_handle_extend_current_text_string_error))
	    g2int_handle_extend_current_text_string_error();
	else
	    error((SI_Long)1L,"Trying to write a string longer than 2MB!");
    }
    if (CONSP(G2int_current_wide_string_list)) {
	new_string_length = FIXNUM_MAX(minimum_new_total_length,
		G2int_wide_string_list_maximum_length);
	wide_string_bv16 = 
		g2int_allocate_byte_vector_16(FIX(IFIX(new_string_length) 
		+ (SI_Long)3L));
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
	aref_arg_1 = G2int_current_wide_string;
	aref_arg_2_1 = G2int_fill_pointer_for_current_wide_string;
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(aref_arg_1));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(aref_arg_1,IFIX(aref_arg_2_1),(SI_Long)0L);
	nconc2(G2int_current_wide_string_list,
		g2int_gensym_cons_1(new_wide_string,Nil));
	G2int_fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	G2int_current_wide_string = new_wide_string;
	G2int_total_length_of_current_wide_string = new_string_length;
    }
    else {
	temp = G2int_maximum_wide_string_length;
	temp_1 = IFIX(G2int_total_length_of_current_wide_string) * 
		(SI_Long)3L / (SI_Long)2L;
	temp_2 = FIX(temp_1);
	temp_2 = FIXNUM_MAX(temp_2,minimum_new_total_length);
	new_total_length = FIXNUM_MIN(temp,temp_2);
	wide_string_bv16 = 
		g2int_allocate_byte_vector_16(FIX(IFIX(new_total_length) + 
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
	if (EQ(G2int_current_wide_string,new_wide_string)) {
	    if ((SI_Long)0L == 
		    IFIX(G2int_fill_pointer_for_current_wide_string))
		temp_3 = TRUEP(T);
	    else {
		temp_3 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
			IFIX(G2int_fill_pointer_for_current_wide_string) : 
			TRUEP(Qnil);
		if (temp_3);
		else {
		    arg = (SI_Long)0L;
		    arg_1 = (SI_Long)0L;
		    arg_2 = (SI_Long)0L + 
			    (IFIX(G2int_fill_pointer_for_current_wide_string) 
			    - (SI_Long)0L);
		    temp_3 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		}
		if (temp_3) {
		    g2int_copy_byte_vector_16_portion_carefully(G2int_current_wide_string,
			    FIX((SI_Long)0L),new_wide_string,
			    FIX((SI_Long)0L),
			    FIX(IFIX(G2int_fill_pointer_for_current_wide_string) 
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
	    gensymed_symbol = G2int_current_wide_string;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = new_wide_string;
	    gensymed_symbol_3 = (SI_Long)0L;
	    gensymed_symbol_4 = 
		    IFIX(G2int_fill_pointer_for_current_wide_string) - 
		    (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		    gensymed_symbol_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	g2int_reclaim_wide_string(G2int_current_wide_string);
	G2int_current_wide_string = new_wide_string;
	G2int_total_length_of_current_wide_string = new_total_length;
    }
    return VALUES_1(Nil);
}

/* TWRITING-ACCUMULATED-LENGTH */
Object g2int_twriting_accumulated_length()
{
    Object string_cons, next_cons, wide_string_bv16, temp;
    SI_Long ab_loopvar_, length_1, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,66);
    if (CONSP(G2int_current_wide_string_list)) {
	string_cons = G2int_current_wide_string_list;
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
	goto end;
	gensymed_symbol = IFIX(Qnil);
      end:;
	gensymed_symbol_1 = IFIX(G2int_fill_pointer_for_current_wide_string);
	temp = FIX(gensymed_symbol + gensymed_symbol_1);
    }
    else
	temp = G2int_fill_pointer_for_current_wide_string;
    return VALUES_1(temp);
}

/* COPY-CURRENT-WIDE-STRING */
Object g2int_copy_current_wide_string()
{
    Object new_wide_string, gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(24,67);
    new_wide_string = 
	    g2int_make_stringw_function(G2int_fill_pointer_for_current_wide_string,
	    Nil);
    if (EQ(G2int_current_wide_string,new_wide_string)) {
	if ((SI_Long)0L == IFIX(G2int_fill_pointer_for_current_wide_string))
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
		    IFIX(G2int_fill_pointer_for_current_wide_string) : 
		    TRUEP(Qnil);
	    if (temp);
	    else {
		arg = (SI_Long)0L;
		arg_1 = (SI_Long)0L;
		arg_2 = (SI_Long)0L + 
			(IFIX(G2int_fill_pointer_for_current_wide_string) 
			- (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		g2int_copy_byte_vector_16_portion_carefully(G2int_current_wide_string,
			FIX((SI_Long)0L),new_wide_string,FIX((SI_Long)0L),
			FIX(IFIX(G2int_fill_pointer_for_current_wide_string) 
			- (SI_Long)0L));
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
	gensymed_symbol = G2int_current_wide_string;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = new_wide_string;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = 
		IFIX(G2int_fill_pointer_for_current_wide_string) - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    return VALUES_1(new_wide_string);
}

/* COPY-OUT-CURRENT-WIDE-STRING */
Object g2int_copy_out_current_wide_string()
{
    Object temp;

    x_note_fn_call(24,68);
    temp = g2int_copy_current_wide_string();
    g2int_reclaim_wide_string(G2int_current_wide_string);
    return VALUES_1(temp);
}

Object G2int_maximum_suggested_length_for_wide_strings = UNBOUND;

static Object Qg2int_do_not_use;   /* do-not-use */

/* TFORMAT-WIDE-STRING */
Object g2int_tformat_wide_string varargs_1(int, n)
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

    x_note_fn_call(24,69);
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
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,
		      arg6,arg7,arg8,arg9);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Kall;                /* :all */

static Object Kfirst;              /* :first */

/* TWRITE-STRING-AS-ATTRIBUTE-NAME */
Object g2int_twrite_string_as_attribute_name(string_1,
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

    x_note_fn_call(24,70);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    string_length = UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    new_wide_string = 
	    g2int_make_stringw_function(character_to_add_at_end_qm ? 
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
		indices_of_word_delimiters = g2int_gensym_cons_1(i,
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
		aref_new_value = g2int_unicode_lowercase_if_uppercase(code);
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
		indices_of_word_delimiters = g2int_gensym_cons_1(i,
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
		    indices_of_word_delimiters = g2int_gensym_cons_1(i,
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
		    aref_new_value = 
			    g2int_unicode_lowercase_if_uppercase(code);
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
	indices_of_word_delimiters = 
		g2int_gensym_cons_1(FIX(string_length),
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
		temp = g2int_unicode_uppercase_if_lowercase(FIX(code_1));
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
		temp_1 = g2int_unicode_uppercase_if_lowercase(FIX(code_1));
		if (temp_1);
		else
		    temp_1 = FIX(code_1);
	    }
	    if ( !EQL(temp,temp_1)) {
		temp_2 = TRUEP(Nil);
		goto end;
	    }
	    word_i = word_i + (SI_Long)1L;
	    acronym_i = acronym_i + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp_2 = TRUEP(T);
	    goto end;
	    temp_2 = TRUEP(Qnil);
	  end:;
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
		aref_new_value = 
			g2int_unicode_uppercase_if_lowercase(FIX(code_1));
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
	g2int_reclaim_gensym_list_1(indices_of_word_delimiters);
    }
    g2int_twrite_general_string(new_wide_string);
    g2int_reclaim_wide_string(new_wide_string);
    return VALUES_1(Qnil);
}

Object G2int_symbol_name_wide_string_prop = UNBOUND;

static Object Qg2int_symbol_name_wide_string;  /* symbol-name-wide-string */

/* GET-OR-MAKE-SYMBOL-NAME-WIDE-STRING */
Object g2int_get_or_make_symbol_name_wide_string(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(24,71);
    temp = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_symbol_name_wide_string);
    if (temp);
    else
	temp = g2int_mutate_global_property(symbol,
		g2int_make_symbol_name_wide_string(symbol),
		Qg2int_symbol_name_wide_string);
    return VALUES_1(temp);
}

/* SYMBOL-NAMEW */
Object g2int_symbol_namew(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(24,72);
    temp = g2int_get_or_make_symbol_name_wide_string(symbol);
    return VALUES_1(temp);
}

/* MAKE-SYMBOL-NAME-WIDE-STRING */
Object g2int_make_symbol_name_wide_string(symbol)
    Object symbol;
{
    Object gensym_string, temp;

    x_note_fn_call(24,73);
    gensym_string = g2int_gensym_symbol_name(symbol);
    temp = g2int_gensym_string_to_wide_string(gensym_string);
    g2int_reclaim_gensym_string(gensym_string);
    return VALUES_1(temp);
}

/* TWRITE-WIDE-CHARACTER */
Object g2int_twrite_wide_character(wide_character)
    Object wide_character;
{
    Object temp, aref_arg_2;

    x_note_fn_call(24,74);
    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
	    G2int_total_length_of_current_wide_string))
	g2int_extend_current_wide_string(G2int_fill_pointer_for_current_wide_string);
    temp = G2int_current_wide_string;
    aref_arg_2 = G2int_fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),IFIX(wide_character));
    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
    G2int_fill_pointer_for_current_wide_string = temp;
    return VALUES_1(Nil);
}

static Object Qg2int_normal;       /* normal */

static Object Qg2int_escape;       /* escape */

static Object Qg2int_unicode_u;    /* unicode-u */

static Object Qg2int_unicode;      /* unicode */

/* READ-WIDE-STRING */
Object g2int_read_wide_string(stream,subchar,arg)
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

    x_note_fn_call(24,75);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      if ( !CHAR_EQ(read_char(stream,T,Nil,T),CHR('\"')))
		  error((SI_Long)1L,"#w syntax error");
	      state_1 = Qg2int_normal;
	      unicode_digit_count = FIX((SI_Long)0L);
	      unicode_value = FIX((SI_Long)0L);
	      ch = Nil;
	    next_loop:
	      ch = read_char(stream,T,Nil,T);
	      if (EQ(state_1,Qg2int_normal)) {
		  if (CHAR_EQ(ch,CHR('\\')))
		      state_1 = Qg2int_escape;
		  else if (CHAR_EQ(ch,CHR('\"')))
		      goto end;
		  else
		      g2int_twrite_wide_character(CHAR_CODE(ch));
	      }
	      else if (EQ(state_1,Qg2int_escape)) {
		  if (CHAR_EQ(ch,CHR('U')) || CHAR_EQ(ch,CHR('u'))) {
		      state_1 = Qg2int_unicode_u;
		      unicode_digit_count = FIX((SI_Long)0L);
		      unicode_value = FIX((SI_Long)0L);
		  }
		  else {
		      g2int_twrite_wide_character(CHAR_CODE(ch));
		      state_1 = Qg2int_normal;
		  }
	      }
	      else if (EQ(state_1,Qg2int_unicode) || EQ(state_1,
		      Qg2int_unicode_u)) {
		  if (EQ(state_1,Qg2int_unicode_u)) {
		      if (CHAR_EQ(ch,CHR('U')) || CHAR_EQ(ch,CHR('u')))
			  temp = TRUEP(T);
		      else {
			  state_1 = Qg2int_unicode;
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
			  g2int_twrite_wide_character(unicode_value);
			  state_1 = Qg2int_normal;
		      }
		  }
	      }
	      goto next_loop;
	    end_loop:
	    end:;
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* HASH-WIDE-STRING */
Object g2int_hash_wide_string(wide_string)
    Object wide_string;
{
    Object temp;
    SI_Long accumulator, index_1, length_1, ab_loop_bind_;

    x_note_fn_call(24,76);
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
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* SXHASHW */
Object g2int_sxhashw(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(24,77);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    g2int_hash_wide_string(thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    return VALUES_1(temp);
}

/* OBTAIN-SIMPLE-TEXT-STRING */
Object g2int_obtain_simple_text_string(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(24,78);
    temp = g2int_make_stringw_function(length_1,Nil);
    return VALUES_1(temp);
}

/* RECLAIM-SIMPLE-TEXT-STRING */
Object g2int_reclaim_simple_text_string(simple_text_string)
    Object simple_text_string;
{
    x_note_fn_call(24,79);
    g2int_reclaim_wide_string(simple_text_string);
    return VALUES_1(Nil);
}

Object G2int_maximum_text_string_length = UNBOUND;

Object G2int_maximum_text_string_length_exceeded_message = UNBOUND;

/* MAXIMUM-TEXT-STRING-LENGTH-ERROR */
Object g2int_maximum_text_string_length_error(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(24,80);
    temp = g2int_signal_gsi_maximum_gensym_string_length_error(length_1,
	    G2int_maximum_gensym_string_length);
    return VALUES_1(temp);
}

/* OBTAIN-TEXT-STRING */
Object g2int_obtain_text_string(length_1)
    Object length_1;
{
    x_note_fn_call(24,81);
    return g2int_make_stringw_function(length_1,Nil);
}

/* RECLAIM-TEXT-STRING */
Object g2int_reclaim_text_string(text_string)
    Object text_string;
{
    x_note_fn_call(24,82);
    g2int_reclaim_wide_string(text_string);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-TEXT-STRING-FUNCTION */
Object g2int_reclaim_if_text_string_function(thing)
    Object thing;
{
    x_note_fn_call(24,83);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return g2int_reclaim_wide_string(thing);
    else
	return VALUES_1(Nil);
}

/* COPY-TEXT-STRING */
Object g2int_copy_text_string(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(24,84);
    temp = g2int_copy_as_wide_string(string_1);
    return VALUES_1(temp);
}

/* COPY-PARTIAL-TEXT-STRING */
Object g2int_copy_partial_text_string(string_1,part_length)
    Object string_1, part_length;
{
    Object temp;

    x_note_fn_call(24,85);
    temp = g2int_copy_partial_wide_string(string_1,part_length);
    return VALUES_1(temp);
}

/* COPY-PORTION-OF-STRING-INTO-SIMPLE-TEXT-STRING */
Object g2int_copy_portion_of_string_into_simple_text_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    x_note_fn_call(24,86);
    return g2int_copy_portion_of_string_into_text_string(source_string,
	    source_start,source_end,destination_string,destination_start);
}

/* COPY-PORTION-OF-STRING-INTO-TEXT-STRING */
Object g2int_copy_portion_of_string_into_text_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(24,87);
    if (STRINGP(source_string))
	g2int_copy_portion_of_gensym_string_into_wide_string(source_string,
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
		    g2int_copy_byte_vector_16_portion_carefully(source_string,
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
Object g2int_copy_portion_of_text_string_into_text_string_given_count(source_string,
	    source_start,destination_string,destination_start,
	    count_of_chars_to_copy)
    Object source_string, source_start, destination_string, destination_start;
    Object count_of_chars_to_copy;
{
    Object new_source_string, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(24,88);
    if (EQ(source_string,destination_string)) {
	new_source_string = g2int_copy_text_string(source_string);
	gensymed_symbol = new_source_string;
	gensymed_symbol_1 = IFIX(source_start);
	gensymed_symbol_2 = destination_string;
	gensymed_symbol_3 = IFIX(destination_start);
	gensymed_symbol_4 = IFIX(count_of_chars_to_copy);
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	g2int_reclaim_text_string(new_source_string);
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
Object g2int_copy_portion_of_gensym_string_into_wide_string(source_string,
	    source_start,source_end,destination_string,destination_start)
    Object source_string, source_start, source_end, destination_string;
    Object destination_start;
{
    Object ab_loop_iter_flag_, aref_new_value;
    SI_Long i, ab_loop_bind_, j;

    x_note_fn_call(24,89);
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

/* CAPITALIZE-TEXT-STRING-IN-PLACE */
Object g2int_capitalize_text_string_in_place(text_string)
    Object text_string;
{
    Object aref_new_value;
    SI_Long wide_character, code;

    x_note_fn_call(24,90);
    if (IFIX(g2int_lengthw(text_string)) > (SI_Long)0L) {
	wide_character = UBYTE_16_ISAREF_1(text_string,(SI_Long)0L);
	code = wide_character;
	if (code < (SI_Long)127L)
	    aref_new_value = (SI_Long)97L <= code && code <= (SI_Long)122L 
		    ? FIX(code + (SI_Long)-32L) : FIX(code);
	else {
	    aref_new_value = g2int_unicode_uppercase_if_lowercase(FIX(code));
	    if (aref_new_value);
	    else
		aref_new_value = FIX(code);
	}
	UBYTE_16_ISASET_1(text_string,(SI_Long)0L,IFIX(aref_new_value));
    }
    return VALUES_1(Nil);
}

/* DOWNCASE-TEXT-STRING-IN-PLACE */
Object g2int_downcase_text_string_in_place(text_string)
    Object text_string;
{
    Object character_1, code, aref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(24,91);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(g2int_lengthw(text_string));
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
	aref_new_value = g2int_unicode_lowercase_if_uppercase(code);
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
Object g2int_upcase_text_string_in_place(text_string)
    Object text_string;
{
    Object character_1, code, aref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(24,92);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(g2int_lengthw(text_string));
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
	aref_new_value = g2int_unicode_uppercase_if_lowercase(code);
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

Object G2int_length_when_written_parsably_prop = UNBOUND;

/* TFORMAT-TEXT-STRING */
Object g2int_tformat_text_string varargs_1(int, n)
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

    x_note_fn_call(24,93);
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
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,
		      arg6,arg7,arg8,arg9);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TEXT-STRING-SUBSTRING */
Object g2int_text_string_substring(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object start, end, temp;

    x_note_fn_call(24,94);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end = end_qm;
    if (end);
    else
	end = STRINGP(string_1) ? g2int_gensym_string_length(string_1) : 
		g2int_text_string_length(string_1);
    temp = g2int_copy_text_string_portion(string_1,start,end);
    return VALUES_1(temp);
}

/* COPY-TEXT-STRING-PORTION */
Object g2int_copy_text_string_portion(string_1,start,end)
    Object string_1, start, end;
{
    Object part_length, new_text_string;

    x_note_fn_call(24,95);
    part_length = FIXNUM_MINUS(end,start);
    new_text_string = g2int_obtain_text_string(part_length);
    g2int_copy_portion_of_string_into_text_string(string_1,start,end,
	    new_text_string,FIX((SI_Long)0L));
    return VALUES_1(new_text_string);
}

/* TWRITE-ASCII-FROM-TEXT-STRING */
Object g2int_twrite_ascii_from_text_string(text_string)
    Object text_string;
{
    x_note_fn_call(24,96);
    g2int_twrite_ascii_from_wide_string(text_string);
    return VALUES_1(Nil);
}

/* CONVERT-TEXT-STRING-TO-ASCII-AS-MUCH-AS-POSSIBLE */
Object g2int_convert_text_string_to_ascii_as_much_as_possible(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(24,97);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_twrite_ascii_from_text_string(text_string);
	      temp = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CONVERT-TEXT-STRING-TO-ASCII-FILENAME-AS-MUCH-AS-POSSIBLE */
Object g2int_convert_text_string_to_ascii_filename_as_much_as_possible(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(24,98);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_twrite_ascii_from_text_string(text_string);
	      temp = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* COPY-NULL-TERMINATED-STRING-AS-TEXT-STRING */
Object g2int_copy_null_terminated_string_as_text_string(string_1)
    Object string_1;
{
    Object length_if_null_terminated_qm;

    x_note_fn_call(24,99);
    length_if_null_terminated_qm = 
	    g2int_length_of_null_terminated_string(string_1);
    if (length_if_null_terminated_qm)
	return g2int_text_string_substring(string_1,FIX((SI_Long)0L),
		length_if_null_terminated_qm);
    else
	return g2int_copy_text_string(string_1);
}

/* LENGTH-OF-NULL-TERMINATED-TEXT-STRING */
Object g2int_length_of_null_terminated_text_string(string_1)
    Object string_1;
{
    Object string_length, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(24,100);
    string_length = g2int_text_string_length(string_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(string_length);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(string_1,i) == (SI_Long)0L) {
	temp = FIX(i);
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* COPY-NULL-TERMINATED-TEXT-STRING */
Object g2int_copy_null_terminated_text_string varargs_1(int, n)
{
    Object source_string;
    Object target_string_qm, target_string;
    SI_Long length_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,101);
    INIT_ARGS_nonrelocating();
    source_string = REQUIRED_ARG_nonrelocating();
    target_string_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length_1 = g2int_text_string_p(source_string) ? 
	    IFIX(g2int_length_of_null_terminated_text_string(source_string)) 
	    : IFIX(g2int_length_of_null_terminated_string(source_string));
    target_string = target_string_qm;
    if (target_string);
    else
	target_string = g2int_obtain_text_string(FIX(length_1));
    g2int_copy_portion_of_string_into_text_string(source_string,
	    FIX((SI_Long)0L),FIX(length_1),target_string,FIX((SI_Long)0L));
    if (target_string_qm)
	UBYTE_16_ISASET_1(target_string,length_1,(SI_Long)0L);
    return VALUES_1(target_string);
}

Object G2int_count_of_interned_text_strings = UNBOUND;

Object G2int_memory_used_for_interned_text_strings = UNBOUND;

/* INTERN-TEXT-STRING */
Object g2int_intern_text_string varargs_1(int, n)
{
    Object text_string;
    Object package_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,102);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return g2int_intern_wide_string(2,text_string,package_qm);
}

/* INTERN-TEXT-STRING-NO-RECLAIM */
Object g2int_intern_text_string_no_reclaim varargs_1(int, n)
{
    Object text_string;
    Object package_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,103);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return g2int_intern_wide_string_no_reclaim(2,text_string,package_qm);
}

/* TEXT-STRING-P */
Object g2int_text_string_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(24,104);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* SYMBOL-NAME-TEXT-STRING */
Object g2int_symbol_name_text_string(symbol_name_1)
    Object symbol_name_1;
{
    Object temp;

    x_note_fn_call(24,105);
    temp = g2int_get_or_make_symbol_name_wide_string(symbol_name_1);
    return VALUES_1(temp);
}

/* TEXT-STRING-LENGTH */
Object g2int_text_string_length(text_string)
    Object text_string;
{
    Object temp;
    SI_Long length_1;

    x_note_fn_call(24,106);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
    temp = FIX(UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L));
    return VALUES_1(temp);
}

/* GENSYM-STRING-LENGTH */
Object g2int_gensym_string_length(gensym_string)
    Object gensym_string;
{
    Object temp;

    x_note_fn_call(24,107);
    temp = length(gensym_string);
    return VALUES_1(temp);
}

/* ORDINARY-SPACE-P */
Object g2int_ordinary_space_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character;

    x_note_fn_call(24,108);
    wide_character = IFIX(wide_character_init);
    return VALUES_1(wide_character == (SI_Long)32L ? T : Nil);
}

/* NEWLINE-P */
Object g2int_newline_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,109);
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
Object g2int_horizontal_space_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,110);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)32L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)9L ? T : Nil;
    return VALUES_1(temp);
}

/* TEXT-BREAK-P */
Object g2int_text_break_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,111);
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
Object g2int_blank_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,112);
    wide_character = IFIX(wide_character_init);
    temp = g2int_newline_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_horizontal_space_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* GRAPHIC-WORD-SEPARATOR-P */
Object g2int_graphic_word_separator_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,113);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)45L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)95L ? T : Nil;
    return VALUES_1(temp);
}

/* WORD-SEPARATOR-P */
Object g2int_word_separator_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,114);
    wide_character = IFIX(wide_character_init);
    temp = g2int_blank_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_graphic_word_separator_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* NON-GRAPHIC-CHARACTER-P */
Object g2int_non_graphic_character_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,115);
    wide_character = IFIX(wide_character_init);
    temp = g2int_newline_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* NON-SPACING-MARK-P */
Object g2int_non_spacing_mark_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,116);
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
Object g2int_alphabetic_p(wide_character_init)
    Object wide_character_init;
{
    Object temp, temp_1;
    SI_Long wide_character, code, arg, arg_1, arg_2;

    x_note_fn_call(24,117);
    wide_character = IFIX(wide_character_init);
    code = wide_character;
    if (code < (SI_Long)127L)
	temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code + 
		(SI_Long)32L) : FIX(code);
    else {
	temp = g2int_unicode_lowercase_if_uppercase(FIX(code));
	if (temp);
	else
	    temp = FIX(code);
    }
    code = wide_character;
    if (code < (SI_Long)127L)
	temp_1 = (SI_Long)97L <= code && code <= (SI_Long)122L ? FIX(code 
		+ (SI_Long)-32L) : FIX(code);
    else {
	temp_1 = g2int_unicode_uppercase_if_lowercase(FIX(code));
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
Object g2int_numeric_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,118);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)48L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)57L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* ALPHA-NUMERIC-P */
Object g2int_alpha_numeric_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,119);
    wide_character = IFIX(wide_character_init);
    temp = g2int_alphabetic_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_numeric_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* CJK-UNIFIED-IDEOGRAPH-P */
Object g2int_cjk_unified_ideograph_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,120);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)19968L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)40959L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-SYLLABLE-P */
Object g2int_hangul_syllable_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,121);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)44032L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)55203L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* OBSOLETE-HANGUL-SYLLABLE-P */
Object g2int_obsolete_hangul_syllable_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,122);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)13312L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)15663L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-JAMO-P */
Object g2int_hangul_jamo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,123);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)4352L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)4607L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HANGUL-COMPATIBILITY-JAMO-P */
Object g2int_hangul_compatibility_jamo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,124);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12593L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12676L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* HIRAGANA-P */
Object g2int_hiragana_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,125);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12353L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12435L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* KATAKANA-P */
Object g2int_katakana_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,126);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12449L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12538L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* BOPOMOFO-P */
Object g2int_bopomofo_p(wide_character_init)
    Object wide_character_init;
{
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,127);
    wide_character = IFIX(wide_character_init);
    arg = (SI_Long)12549L;
    arg_1 = wide_character;
    arg_2 = (SI_Long)12588L;
    return VALUES_1(arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil);
}

/* READABLE-SYMBOLIC-P */
Object g2int_readable_symbolic_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,128);
    wide_character = IFIX(wide_character_init);
    temp = g2int_numeric_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_alphabetic_p(FIX(wide_character));
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
	temp = g2int_cjk_unified_ideograph_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_hangul_syllable_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_obsolete_hangul_syllable_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_hangul_jamo_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_hangul_compatibility_jamo_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_hiragana_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_katakana_p(FIX(wide_character));
    if (temp);
    else
	temp = g2int_bopomofo_p(FIX(wide_character));
    return VALUES_1(temp);
}

/* G2-EXPONENT-MARKER-P */
Object g2int_g2_exponent_marker_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,129);
    wide_character = IFIX(wide_character_init);
    temp = wide_character == (SI_Long)101L ? T : Nil;
    if (temp);
    else
	temp = wide_character == (SI_Long)69L ? T : Nil;
    return VALUES_1(temp);
}

/* WORD-DELIMITING-CHARACTER-P */
Object g2int_word_delimiting_character_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character;

    x_note_fn_call(24,130);
    wide_character = IFIX(wide_character_init);
    temp =  !TRUEP(g2int_alpha_numeric_p(FIX(wide_character))) ? ( 
	    !TRUEP(g2int_chinese_or_hangul_or_kana_p(FIX(wide_character))) 
	    ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* CHINESE-OR-HANGUL-OR-KANA-P */
Object g2int_chinese_or_hangul_or_kana_p(wide_character_init)
    Object wide_character_init;
{
    Object temp;
    SI_Long wide_character, arg, arg_1, arg_2;

    x_note_fn_call(24,131);
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

Object G2int_the_type_description_of_gensym_string_stream = UNBOUND;

Object G2int_chain_of_available_gensym_string_streams = UNBOUND;

Object G2int_gensym_string_stream_count = UNBOUND;

/* RECLAIM-GENSYM-STRING-STREAM-1 */
Object g2int_reclaim_gensym_string_stream_1(gensym_string_stream)
    Object gensym_string_stream;
{
    Object svref_new_value;

    x_note_fn_call(24,132);
    inline_note_reclaim_cons(gensym_string_stream,Nil);
    svref_new_value = G2int_chain_of_available_gensym_string_streams;
    SVREF(gensym_string_stream,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gensym_string_streams = gensym_string_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-STRING-STREAM */
Object g2int_reclaim_structure_for_gensym_string_stream(gensym_string_stream)
    Object gensym_string_stream;
{
    x_note_fn_call(24,133);
    return g2int_reclaim_gensym_string_stream_1(gensym_string_stream);
}

static Object Qg2_defstruct_structure_name_gensym_string_stream_g2_struct;  /* g2-defstruct-structure-name::gensym-string-stream-g2-struct */

/* MAKE-PERMANENT-GENSYM-STRING-STREAM-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gensym_string_stream_structure_internal()
{
    Object def_structure_gensym_string_stream_variable;
    Object gensym_string_stream_count_new_value;
    Object defstruct_g2_gensym_string_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,134);
    def_structure_gensym_string_stream_variable = Nil;
    gensym_string_stream_count_new_value = 
	    FIXNUM_ADD1(G2int_gensym_string_stream_count);
    G2int_gensym_string_stream_count = gensym_string_stream_count_new_value;
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
Object g2int_make_gensym_string_stream_internal_1()
{
    Object def_structure_gensym_string_stream_variable;

    x_note_fn_call(24,135);
    def_structure_gensym_string_stream_variable = 
	    G2int_chain_of_available_gensym_string_streams;
    if (def_structure_gensym_string_stream_variable) {
	G2int_chain_of_available_gensym_string_streams = 
		ISVREF(def_structure_gensym_string_stream_variable,
		(SI_Long)0L);
	SVREF(def_structure_gensym_string_stream_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_string_stream_g2_struct;
    }
    else
	def_structure_gensym_string_stream_variable = 
		g2int_make_permanent_gensym_string_stream_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_string_stream_variable,Nil);
    ISVREF(def_structure_gensym_string_stream_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_string_stream_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gensym_string_stream_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_gensym_string_stream_variable);
}

/* MAKE-GENSYM-STRING-STREAM */
Object g2int_make_gensym_string_stream(gensym_string)
    Object gensym_string;
{
    Object stream, string_is_simple_qm;
    SI_Long svref_new_value_1;
    char svref_new_value;

    x_note_fn_call(24,136);
    stream = g2int_make_gensym_string_stream_internal_1();
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
Object g2int_read_character_code(gensym_string_stream)
    Object gensym_string_stream;
{
    Object local_character_index, escape_character_qm;
    Object character_or_character_code, gensym_string;
    Object gensym_string_is_simple_qm, temp_1, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long ascii_code, temp_2;
    char temp, character_1;

    x_note_fn_call(24,137);
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
			ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
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
			    temp_1 = G2int_gensym_code_for_capital_ligature_oe;
			    break;
			  case 119:
			    temp_1 = G2int_gensym_code_for_small_ligature_oe;
			    break;
			  case 42:
			    temp_1 = G2int_gensym_code_for_bullet;
			    break;
			  case 38:
			    temp_1 = 
				    G2int_gensym_code_for_small_letter_f_with_hook;
			    break;
			  case 58:
			    temp_1 = G2int_gensym_code_for_trade_mark_sign;
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
		    !TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
		    CHAR_EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_linebreak) : 
		    EQL(character_or_character_code,
		    G2int_gensym_char_or_code_for_linebreak) && 
		    EQL(escape_character_qm,G2int_gensym_esc_for_linebreakqm))
		return VALUES_1(G2int_gensym_code_for_linebreak);
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
		    CHAR_EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_paragraph_break) : 
		    EQL(character_or_character_code,
		    G2int_gensym_char_or_code_for_paragraph_break) && 
		    EQL(escape_character_qm,
		    G2int_gensym_esc_for_paragraph_breakqm))
		return VALUES_1(G2int_gensym_code_for_paragraph_break);
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
Object g2int_unread_character_code(gensym_string_stream,character_code)
    Object gensym_string_stream, character_code;
{
    Object svref_new_value;

    x_note_fn_call(24,138);
    svref_new_value = ISVREF(gensym_string_stream,(SI_Long)5L);
    SVREF(gensym_string_stream,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PEEK-CHARACTER-CODE */
Object g2int_peek_character_code(gensym_string_stream)
    Object gensym_string_stream;
{
    Object character_code_qm;

    x_note_fn_call(24,139);
    character_code_qm = g2int_read_character_code(gensym_string_stream);
    if (character_code_qm)
	g2int_unread_character_code(gensym_string_stream,character_code_qm);
    return VALUES_1(character_code_qm);
}

/* STRING-TO-WIDE-STRING */
Object g2int_string_to_wide_string(string_1)
    Object string_1;
{
    Object wide_string;
    SI_Long length_1;

    x_note_fn_call(24,140);
    length_1 = IFIX(length(string_1));
    wide_string = g2int_make_stringw_function(length(string_1),Nil);
    g2int_copy_portion_of_gensym_string_into_wide_string(string_1,
	    FIX((SI_Long)0L),FIX(length_1),wide_string,FIX((SI_Long)0L));
    return VALUES_1(wide_string);
}

/* WIDE-STRING-TO-STRING */
Object g2int_wide_string_to_string(wide_string)
    Object wide_string;
{
    Object string_1;
    SI_Long length_1;

    x_note_fn_call(24,141);
    length_1 = IFIX(g2int_lengthw(wide_string));
    string_1 = g2int_obtain_simple_gensym_string(g2int_lengthw(wide_string));
    g2int_copy_portion_of_wide_string_octets_into_simple_gensym_string(wide_string,
	    FIX((SI_Long)0L),FIX(length_1),string_1,FIX((SI_Long)0L));
    return VALUES_1(string_1);
}

/* REMOVE-DUPLICATES-IN-TEXT-STRING */
Object g2int_remove_duplicates_in_text_string(text_string)
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

    x_note_fn_call(24,142);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      length_2 = g2int_text_string_length(text_string);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_2);
	      char_1 = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
	      j = (SI_Long)0L;
	      ab_loop_bind__1 = 
		      IFIX(G2int_fill_pointer_for_current_wide_string);
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if (j >= ab_loop_bind__1)
		  goto end_loop_1;
	      ab_loop_it_ = IFIX(char_1) == 
		      UBYTE_16_ISAREF_1(G2int_current_wide_string,j) ? T : Nil;
	      if (ab_loop_it_) {
		  temp = TRUEP(ab_loop_it_);
		  goto end;
	      }
	      j = j + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      temp = TRUEP(Qnil);
	    end:;
	      if ( !temp) {
		  if (EQ(G2int_current_twriting_output_type,
			  Qg2int_wide_string)) {
		      thing = char_1;
		      g2int_twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			      G2int_total_length_of_current_gensym_string))
			  g2int_extend_current_gensym_string(0);
		      temp_1 = G2int_current_gensym_string;
		      schar_arg_2 = 
			      G2int_fill_pointer_for_current_gensym_string;
		      thing = char_1;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		      G2int_fill_pointer_for_current_gensym_string = temp_1;
		  }
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      result = g2int_copy_current_wide_string();
	      MVS_6(result,gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3,
		      gensymed_symbol_4,gensymed_symbol_5);
	      g2int_reclaim_wide_string(G2int_current_wide_string);
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
Object g2int_concatenate_text_strings(text_string_1,text_string_2)
    Object text_string_1, text_string_2;
{
    Object wide_string_bv16, new_wide_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long length_1, length_1_1, length_2, length_3, bv16_length, aref_arg_2;
    SI_Long aref_new_value, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;

    x_note_fn_call(24,143);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string_1));
    length_1_1 = UBYTE_16_ISAREF_1(text_string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string_2));
    length_2 = UBYTE_16_ISAREF_1(text_string_2,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string_2,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    length_3 = length_1_1 + length_2;
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_3 + 
	    (SI_Long)3L));
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

Object G2int_base_36_digits_string = UNBOUND;

/* RECLAIM-GENSYM-STRING-OR-WIDE-STRING */
Object g2int_reclaim_gensym_string_or_wide_string(gensym_string_or_wide_string)
    Object gensym_string_or_wide_string;
{
    x_note_fn_call(24,144);
    if (STRINGP(gensym_string_or_wide_string))
	return g2int_reclaim_gensym_string(gensym_string_or_wide_string);
    else
	return g2int_reclaim_wide_string(gensym_string_or_wide_string);
}

/* GENSYM-STRING-OR-WIDE-STRING-P */
Object g2int_gensym_string_or_wide_string_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(24,145);
    temp = STRINGP(thing) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		(SI_Long)0L ? T : Nil);
}

/* RECLAIM-IF-GENSYM-STRING-OR-WIDE-STRING */
Object g2int_reclaim_if_gensym_string_or_wide_string(thing)
    Object thing;
{
    x_note_fn_call(24,146);
    if (g2int_gensym_string_or_wide_string_p(thing))
	return g2int_reclaim_gensym_string_or_wide_string(thing);
    else
	return VALUES_1(Nil);
}

/* TWRITE-LINE-SEPARATOR */
Object g2int_twrite_line_separator()
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;
    char thing_1;

    x_note_fn_call(24,147);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = (SI_Long)8232L;
	    return g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)8232L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
	}
    }
    else if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing_1 = '\n';
	return g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
		CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing_1 = '\n';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
		CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
	return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
    }
}

/* COPY-FOREIGN-STRING-ARG-IF-APPROPRIATE */
Object g2int_copy_foreign_string_arg_if_appropriate(gensym_string_or_wide_string)
    Object gensym_string_or_wide_string;
{
    Object string_1, length_2;
    SI_Long length_1;

    x_note_fn_call(24,148);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensym_string_or_wide_string) != 
	    (SI_Long)0L) {
	length_1 = 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string_or_wide_string));
	length_1 = UBYTE_16_ISAREF_1(gensym_string_or_wide_string,length_1 
		- (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(gensym_string_or_wide_string,length_1 
		- (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	string_1 = 
		g2int_obtain_simple_gensym_string_of_quantized_length(FIX(length_1));
	g2int_copy_portion_of_wide_string_octets_into_simple_gensym_string(gensym_string_or_wide_string,
		FIX((SI_Long)0L),FIX(length_1),string_1,FIX((SI_Long)0L));
	return VALUES_1(string_1);
    }
    else if ( ! !ARRAY_HAS_FILL_POINTER_P(gensym_string_or_wide_string)) {
	length_2 = length(gensym_string_or_wide_string);
	string_1 = 
		g2int_obtain_simple_gensym_string_of_quantized_length(length_2);
	g2int_copy_portion_of_string_into_simple_gensym_string(gensym_string_or_wide_string,
		FIX((SI_Long)0L),length_2,string_1,FIX((SI_Long)0L));
	return VALUES_1(string_1);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-PORTION-OF-WIDE-STRING-OCTETS-INTO-SIMPLE-GENSYM-STRING */
Object g2int_copy_portion_of_wide_string_octets_into_simple_gensym_string(source_string,
	    source_start_init,source_end_init,destination_string,
	    destination_start_init)
    Object source_string, source_start_init, source_end_init;
    Object destination_string, destination_start_init;
{
    Object char_1, ab_loop_iter_flag_;
    SI_Long source_start, source_end, destination_start, i, ab_loop_bind_, j;
    SI_Long gensymed_symbol;
    char schar_new_value;

    x_note_fn_call(24,149);
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

Object G2int_message_illegal_symbol_text_string_empty = UNBOUND;

Object G2int_message_illegal_symbol_text_string_contains_a_newline = UNBOUND;

Object G2int_message_illegal_symbol_text_string_contains_ffff = UNBOUND;

Object G2int_message_illegal_symbol_text_string_contains_fffe = UNBOUND;

Object G2int_message_illegal_symbol_text_string_too_long = UNBOUND;

/* NON-VALID-SYMBOL-TEXT-STRING-P */
Object g2int_non_valid_symbol_text_string_p(printed_representation_text_string)
    Object printed_representation_text_string;
{
    Object length_1, temp;
    SI_Long character_1, i, ab_loop_bind_;

    x_note_fn_call(24,150);
    character_1 = (SI_Long)0L;
    length_1 = g2int_lengthw(printed_representation_text_string);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    if (IFIX(length_1) == (SI_Long)0L) {
	temp = G2int_message_illegal_symbol_text_string_empty;
	goto end;
    }
    if (FIXNUM_GT(length_1,G2int_maximum_length_for_user_symbols)) {
	temp = G2int_message_illegal_symbol_text_string_too_long;
	goto end;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = UBYTE_16_ISAREF_1(printed_representation_text_string,i);
    if (character_1 >= (SI_Long)65534L) {
	temp = character_1 == (SI_Long)65535L ? 
		G2int_message_illegal_symbol_text_string_contains_ffff : 
		G2int_message_illegal_symbol_text_string_contains_fffe;
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* SIMPLE-SYMBOL-CHARACTER-P */
Object g2int_simple_symbol_character_p(wide_character)
    Object wide_character;
{
    x_note_fn_call(24,151);
    return VALUES_1(g2int_simple_symbol_character_p_4dot0(wide_character) ?
	     ( !(IFIX(wide_character) == (SI_Long)9L) ? T : Nil) : Qnil);
}

/* SIMPLE-SYMBOL-CHARACTER-P-4.0 */
Object g2int_simple_symbol_character_p_4dot0(wide_character)
    Object wide_character;
{
    Object unicode, code, extended_code, unicode_1, code_1, temp;
    Object gensym_character_code_qm, character_code, char_1;
    Object simple_gensym_character_code, character_or_character_code_qm;
    Object escape_qm;
    SI_Long row, gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Object result;

    x_note_fn_call(24,152);
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
	row = IFIX(unicode_1) >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
	    gensym_character_code_qm = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    gensym_character_code_qm = Nil;
	if (gensym_character_code_qm) {
	    temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
		    TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code_qm))) : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp_1 = 'W';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_ligature_oe))
		temp_1 = 'w';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_bullet))
		temp_1 = '*';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp_1 = '&';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_trade_mark_sign))
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
	    code = g2int_map_unicode_to_gensym_han_character_code(unicode_1);
	    temp = code;
	    if (temp);
	    else {
		row = IFIX(unicode_1) >>  -  - (SI_Long)8L;
		gensym_full_row = 
			UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
			row);
		if ( !(gensym_full_row == 
			    IFIX(G2int_invalid_gensym_full_row))) {
		    gensymed_symbol = gensym_full_row << (SI_Long)8L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		    code = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else
		    code = Nil;
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
    if (FIXNUM_EQ(character_code,G2int_gensym_code_for_linebreak))
	result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
		G2int_gensym_esc_for_linebreakqm);
    else if (FIXNUM_EQ(character_code,G2int_gensym_code_for_paragraph_break))
	result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
		G2int_gensym_esc_for_paragraph_breakqm);
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
		    ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(character_code)) : Nil;
	    if (temp);
	    else if (FIXNUM_EQ(character_code,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (FIXNUM_EQ(character_code,
		    G2int_gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (FIXNUM_EQ(character_code,G2int_gensym_code_for_bullet))
		temp = CHR('*');
	    else if (FIXNUM_EQ(character_code,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (FIXNUM_EQ(character_code,
		    G2int_gensym_code_for_trade_mark_sign))
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
Object g2int_simple_pathname_character_p(character_1)
    Object character_1;
{
    Object temp;

    x_note_fn_call(24,153);
    temp = g2int_simple_symbol_character_p(character_1);
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

Object G2int_punctuation_alist = UNBOUND;

/* NOTE-PUNCTUATION-MARKS-AS-SUCH */
Object g2int_note_punctuation_marks_as_such(punctuation_alist_1)
    Object punctuation_alist_1;
{
    x_note_fn_call(24,154);
    return VALUES_1(Nil);
}

Object G2int_standard_character_syntax_table = UNBOUND;

Object G2int_ellipsis_text_string = UNBOUND;

Object G2int_ellipsis_text_string_length = UNBOUND;

Object G2int_punctuation_mark_p_prop = UNBOUND;

Object G2int_type_of_syntactic_anomaly_prop = UNBOUND;

/* TWRITE-SYMBOL */
Object g2int_twrite_symbol varargs_1(int, n)
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

    x_note_fn_call(24,155);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    do_not_downcase_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    which_characters_not_to_downcase_qm = do_not_downcase_qm ? Kall : Nil;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	return g2int_twrite_symbol_into_text_string(2,symbol,
		which_characters_not_to_downcase_qm);
    else {
	current_wide_string_list = Qg2int_do_not_use;
	PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = 
		  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L));
	      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qg2int_wide_string;
		PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			0);
		  g2int_twrite_symbol_into_text_string(2,symbol,
			  which_characters_not_to_downcase_qm);
		  temporary_text_string = g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temporary_gensym_string = 
		g2int_wide_string_to_gensym_string(temporary_text_string);
	g2int_twrite_portion_of_gensym_string_unparsably(temporary_gensym_string,
		Nil,Nil);
	g2int_reclaim_text_string(temporary_text_string);
	return g2int_reclaim_gensym_string(temporary_gensym_string);
    }
}

static Object Qg2int_punctuation_mark_p;  /* punctuation-mark-p */

static Object Qg2int_type_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

static Object Kfirst_of_each_word;  /* :first-of-each-word */

static Object Knone;               /* :none */

/* TWRITE-SYMBOL-INTO-TEXT-STRING */
Object g2int_twrite_symbol_into_text_string varargs_1(int, n)
{
    Object symbol;
    Object which_characters_not_to_downcase_qm, string_1, string_length;
    Object symbol_name_text_string, symbol_name_length, this_char, ab_loop_it_;
    Object class_qualified_symbol_qm, ellipsis_parsing_state;
    Object quote_characters_as_appropriate_qm, i_1, character_1;
    Object previous_character_qm, temp, temp_1, schar_arg_2, schar_new_value;
    Object simple_or_wide_character, code, thing_1;
    SI_Long i, ab_loop_bind_, thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,156);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    which_characters_not_to_downcase_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    string_1 = g2int_symbol_name_text_string(symbol);
    string_length = g2int_text_string_length(string_1);
    if (EQ(SYMBOL_PACKAGE(symbol),G2int_keyword_package_1)) {
	symbol_name_text_string = g2int_symbol_name_text_string(symbol);
	symbol_name_length = g2int_text_string_length(symbol_name_text_string);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(symbol_name_length);
	this_char = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	this_char = FIX(UBYTE_16_ISAREF_1(symbol_name_text_string,i));
	ab_loop_it_ = IFIX(this_char) == (SI_Long)58L && i + (SI_Long)1L < 
		IFIX(symbol_name_length) ? 
		(UBYTE_16_ISAREF_1(symbol_name_text_string,i + 
		(SI_Long)1L) == (SI_Long)58L ? T : Nil) : Qnil;
	if (ab_loop_it_) {
	    class_qualified_symbol_qm = ab_loop_it_;
	    goto end;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	class_qualified_symbol_qm = Qnil;
      end:;
    }
    else
	class_qualified_symbol_qm = Nil;
    ellipsis_parsing_state = FIX((SI_Long)0L);
    quote_characters_as_appropriate_qm = G2int_write_symbols_parsablyqm ? 
	    ( !TRUEP(class_qualified_symbol_qm) ? ( 
	    !TRUEP(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2int_punctuation_mark_p)) ? T : Nil) : Nil) : Nil;
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
		G2int_ellipsis_text_string_length) && IFIX(character_1) == 
		UBYTE_16_ISAREF_1(G2int_ellipsis_text_string,
		IFIX(ellipsis_parsing_state)) ? 
		FIXNUM_ADD1(ellipsis_parsing_state) : FIX((SI_Long)0L);
	if (quote_characters_as_appropriate_qm && ( 
		!TRUEP(g2int_simple_symbol_character_p(character_1)) || 
		g2int_lower_case_pw(character_1) || 
		FIXNUM_EQ(ellipsis_parsing_state,
		G2int_ellipsis_text_string_length) || (IFIX(i_1) == 
		(SI_Long)1L ? 
		TRUEP(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qg2int_type_of_syntactic_anomaly)) : TRUEP(Nil)))) {
	    if (FIXNUM_EQ(ellipsis_parsing_state,
		    G2int_ellipsis_text_string_length))
		ellipsis_parsing_state = FIX((SI_Long)1L);
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = (SI_Long)64L;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_1 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = (SI_Long)64L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_1;
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
		temp = g2int_word_separator_p(previous_character_qm);
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
			g2int_unicode_lowercase_if_uppercase(code);
		if (simple_or_wide_character);
		else
		    simple_or_wide_character = code;
	    }
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
	previous_character_qm = character_1;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return g2int_twrite_portion_of_wide_string_unparsably(string_1,
		FIX((SI_Long)0L),string_length);
}

/* TWRITE-GENERAL-STRING */
Object g2int_twrite_general_string(string_1)
    Object string_1;
{
    x_note_fn_call(24,157);
    if (G2int_write_strings_parsablyqm)
	g2int_twrite_portion_of_string_parsably(string_1,Nil,Nil);
    else
	g2int_twrite_portion_of_string_unparsably(string_1,Nil,Nil);
    return VALUES_1(Nil);
}

/* TWRITE-BEGINNING-OF-WIDE-STRING */
Object g2int_twrite_beginning_of_wide_string(wide_string,first_n_characters)
    Object wide_string, first_n_characters;
{
    x_note_fn_call(24,158);
    if (G2int_write_strings_parsablyqm) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	    g2int_twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
		    FIX((SI_Long)0L),first_n_characters);
	else
	    g2int_twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
		    FIX((SI_Long)0L),first_n_characters);
    }
    else if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	g2int_twrite_beginning_of_wide_string_unparsably_to_current_wide_string(wide_string,
		first_n_characters);
    else
	g2int_twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
		FIX((SI_Long)0L),first_n_characters);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-STRING-PARSABLY */
Object g2int_twrite_portion_of_string_parsably(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    x_note_fn_call(24,159);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	g2int_twrite_portion_of_wide_string_parsably(string_1,start_qm,end_qm);
    else
	g2int_twrite_portion_of_gensym_string_parsably(string_1,start_qm,
		end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY */
Object g2int_twrite_portion_of_wide_string_parsably(wide_string,start_qm,
	    end_qm)
    Object wide_string, start_qm, end_qm;
{
    x_note_fn_call(24,160);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	g2int_twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
		start_qm,end_qm);
    else
	g2int_twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
		start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY-TO-CURRENT-WIDE-STRING */
Object g2int_twrite_portion_of_wide_string_parsably_to_current_wide_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, temp_1, aref_arg_2, gensymed_symbol, gensymed_symbol_2;
    SI_Long wide_character, start, end, i, j, ab_loop_bind_, arg, arg_1, arg_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long incff_1_arg, fill_pointer_for_current_wide_string_new_value;
    char temp_2;

    x_note_fn_call(24,161);
    wide_character = (SI_Long)0L;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = g2int_lengthw(wide_string);
    end = IFIX(temp);
    i = start;
    if ( !(IFIX(G2int_fill_pointer_for_current_wide_string) + (end - 
	    start) + (SI_Long)2L < 
	    IFIX(G2int_total_length_of_current_wide_string)))
	g2int_extend_current_wide_string(FIX(IFIX(G2int_fill_pointer_for_current_wide_string) 
		+ (end - start) + (SI_Long)2L));
    temp_1 = G2int_current_wide_string;
    aref_arg_2 = G2int_fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)34L);
    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
    G2int_fill_pointer_for_current_wide_string = temp_1;
  next_loop:
    if ( !(i < end))
	goto end_loop;
    j = i;
    ab_loop_bind_ = end;
  next_loop_1:
    if (j >= ab_loop_bind_)
	goto end_loop_1;
    wide_character = UBYTE_16_ISAREF_1(wide_string,j);
    if (wide_character == (SI_Long)64L || wide_character == (SI_Long)34L) {
	if ( !(i == j)) {
	    if (EQ(wide_string,G2int_current_wide_string)) {
		if (i == j)
		    temp_2 = TRUEP(T);
		else {
		    temp_2 = i < 
			    IFIX(G2int_fill_pointer_for_current_wide_string) 
			    ? 
			    IFIX(G2int_fill_pointer_for_current_wide_string) 
			    < j : TRUEP(Qnil);
		    if (temp_2);
		    else {
			arg = IFIX(G2int_fill_pointer_for_current_wide_string);
			arg_1 = i;
			arg_2 = 
				IFIX(G2int_fill_pointer_for_current_wide_string) 
				+ (j - i);
			temp_2 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		    }
		    if (temp_2) {
			g2int_copy_byte_vector_16_portion_carefully(wide_string,
				FIX(i),G2int_current_wide_string,
				G2int_fill_pointer_for_current_wide_string,
				FIX(j - i));
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
		gensymed_symbol_2 = G2int_current_wide_string;
		gensymed_symbol_3 = 
			IFIX(G2int_fill_pointer_for_current_wide_string);
		gensymed_symbol_4 = j - i;
		INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			gensymed_symbol_1,
			UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			gensymed_symbol_3,gensymed_symbol_4);
	    }
	    incff_1_arg = j - i;
	    fill_pointer_for_current_wide_string_new_value = 
		    IFIX(G2int_fill_pointer_for_current_wide_string) + 
		    incff_1_arg;
	    G2int_fill_pointer_for_current_wide_string = 
		    FIX(fill_pointer_for_current_wide_string_new_value);
	}
	if ( !(IFIX(G2int_fill_pointer_for_current_wide_string) + (end - 
		j) + (SI_Long)2L < 
		IFIX(G2int_total_length_of_current_wide_string)))
	    g2int_extend_current_wide_string(FIX(IFIX(G2int_fill_pointer_for_current_wide_string) 
		    + (end - j) + (SI_Long)2L));
	temp_1 = G2int_current_wide_string;
	aref_arg_2 = G2int_fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)64L);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
	G2int_fill_pointer_for_current_wide_string = temp_1;
	temp_1 = G2int_current_wide_string;
	aref_arg_2 = G2int_fill_pointer_for_current_wide_string;
	UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),wide_character);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
	G2int_fill_pointer_for_current_wide_string = temp_1;
	i = j + (SI_Long)1L;
	goto end_1;
    }
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    if (EQ(wide_string,G2int_current_wide_string)) {
	if (i == end)
	    temp_2 = TRUEP(T);
	else {
	    temp_2 = i < IFIX(G2int_fill_pointer_for_current_wide_string) ?
		     IFIX(G2int_fill_pointer_for_current_wide_string) < 
		    end : TRUEP(Qnil);
	    if (temp_2);
	    else {
		arg = IFIX(G2int_fill_pointer_for_current_wide_string);
		arg_1 = i;
		arg_2 = IFIX(G2int_fill_pointer_for_current_wide_string) + 
			(end - i);
		temp_2 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp_2) {
		g2int_copy_byte_vector_16_portion_carefully(wide_string,
			FIX(i),G2int_current_wide_string,
			G2int_fill_pointer_for_current_wide_string,FIX(end 
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
	gensymed_symbol_2 = G2int_current_wide_string;
	gensymed_symbol_3 = IFIX(G2int_fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = end - i;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = end - i;
    fill_pointer_for_current_wide_string_new_value = 
	    IFIX(G2int_fill_pointer_for_current_wide_string) + incff_1_arg;
    G2int_fill_pointer_for_current_wide_string = 
	    FIX(fill_pointer_for_current_wide_string_new_value);
    i = end;
  end_1:;
    goto next_loop;
  end_loop:
    temp_1 = G2int_current_wide_string;
    aref_arg_2 = G2int_fill_pointer_for_current_wide_string;
    UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)34L);
    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_wide_string);
    G2int_fill_pointer_for_current_wide_string = temp_1;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-PARSABLY-TO-CURRENT-GENSYM-STRING */
Object g2int_twrite_portion_of_wide_string_parsably_to_current_gensym_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long wide_character, start, end, i, ab_loop_bind_, thing;

    x_note_fn_call(24,162);
    wide_character = (SI_Long)0L;
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = g2int_lengthw(wide_string);
    end = IFIX(temp);
    i = start;
    ab_loop_bind_ = end;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)34L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)34L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = UBYTE_16_ISAREF_1(wide_string,i);
    if (wide_character == (SI_Long)64L || wide_character == (SI_Long)91L 
	    || wide_character == (SI_Long)96L || wide_character == 
	    (SI_Long)34L) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = (SI_Long)64L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)64L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = wide_character;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = (SI_Long)34L;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = (SI_Long)34L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-GENSYM-STRING-PARSABLY */
Object g2int_twrite_portion_of_gensym_string_parsably(gensym_string,
	    start_qm,end_qm)
    Object gensym_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long start, end, i, ab_loop_bind_;
    char character_1;
    char simple_qm;
    char thing;
    char thing_1;

    x_note_fn_call(24,163);
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
    end = IFIX(temp);
    i = start;
    ab_loop_bind_ = end;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = '\"';
	g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = '\"';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = simple_qm ? ISCHAR(gensym_string,i) : ICHAR(gensym_string,i);
    if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('@')) || 
	    CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\"'))) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = '@';
	    g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = '@';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing_1 = character_1;
	g2int_twrite_wide_character(CHARACTERP(CHAR_TO_CHARACTER(thing_1)) 
		? CHAR_CODE(CHAR_TO_CHARACTER(thing_1)) : 
		CHAR_TO_CHARACTER(thing_1));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing_1 = character_1;
	schar_new_value = CODE_CHAR(CHARACTERP(CHAR_TO_CHARACTER(thing_1)) 
		? CHAR_CODE(CHAR_TO_CHARACTER(thing_1)) : 
		CHAR_TO_CHARACTER(thing_1));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = '\"';
	g2int_twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = '\"';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-STRING-UNPARSABLY */
Object g2int_twrite_portion_of_string_unparsably(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    x_note_fn_call(24,164);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	g2int_twrite_portion_of_wide_string_unparsably(string_1,start_qm,
		end_qm);
    else
	g2int_twrite_portion_of_gensym_string_unparsably(string_1,start_qm,
		end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY */
Object g2int_twrite_portion_of_wide_string_unparsably(wide_string,start_qm,
	    end_qm)
    Object wide_string, start_qm, end_qm;
{
    x_note_fn_call(24,165);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	g2int_twrite_portion_of_wide_string_unparsably_to_current_wide_string(wide_string,
		start_qm,end_qm);
    else
	g2int_twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
		start_qm,end_qm);
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-WIDE-STRING */
Object g2int_twrite_portion_of_wide_string_unparsably_to_current_wide_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object start, end, gensymed_symbol, gensymed_symbol_2, incff_1_arg;
    Object fill_pointer_for_current_wide_string_new_value;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(24,166);
    start = start_qm;
    if (start);
    else
	start = FIX((SI_Long)0L);
    end = end_qm;
    if (end);
    else
	end = g2int_lengthw(wide_string);
    if ( !FIXNUM_LT(FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,
	    FIXNUM_MINUS(end,start)),
	    G2int_total_length_of_current_wide_string))
	g2int_extend_current_wide_string(FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,
		FIXNUM_MINUS(end,start)));
    if (EQ(wide_string,G2int_current_wide_string)) {
	if (FIXNUM_EQ(start,end))
	    temp = TRUEP(T);
	else {
	    temp = FIXNUM_LT(start,
		    G2int_fill_pointer_for_current_wide_string) ? 
		    FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
		    end) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = IFIX(G2int_fill_pointer_for_current_wide_string);
		arg_1 = IFIX(start);
		arg_2 = 
			IFIX(FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,
			FIXNUM_MINUS(end,start)));
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		g2int_copy_byte_vector_16_portion_carefully(wide_string,
			start,G2int_current_wide_string,
			G2int_fill_pointer_for_current_wide_string,
			FIXNUM_MINUS(end,start));
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
	gensymed_symbol_2 = G2int_current_wide_string;
	gensymed_symbol_3 = IFIX(G2int_fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = IFIX(FIXNUM_MINUS(end,start));
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = FIXNUM_MINUS(end,start);
    fill_pointer_for_current_wide_string_new_value = 
	    FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,incff_1_arg);
    G2int_fill_pointer_for_current_wide_string = 
	    fill_pointer_for_current_wide_string_new_value;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-GENSYM-STRING */
Object g2int_twrite_portion_of_wide_string_unparsably_to_current_gensym_string(wide_string,
	    start_qm,end_qm)
    Object wide_string, start_qm, end_qm;
{
    Object temp, char_1, simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long start, end, i, ab_loop_bind_;

    x_note_fn_call(24,167);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    start = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = g2int_lengthw(wide_string);
    end = IFIX(temp);
    i = start;
    ab_loop_bind_ = end;
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    simple_or_wide_character = IFIX(char_1) == (SI_Long)8232L ? CHR('\n') :
	     char_1;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = simple_or_wide_character;
	g2int_twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* TWRITE-PORTION-OF-GENSYM-STRING-UNPARSABLY */
Object g2int_twrite_portion_of_gensym_string_unparsably(gensym_string,
	    start_qm,end_qm)
    Object gensym_string, start_qm, end_qm;
{
    Object temp, temp_1, schar_arg_2, schar_new_value;
    SI_Long start, end, i, ab_loop_bind_;
    char simple_qm;
    char simple_or_wide_character, thing;

    x_note_fn_call(24,168);
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
    end = IFIX(temp);
    i = start;
    ab_loop_bind_ = end;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    simple_or_wide_character = simple_qm ? ISCHAR(gensym_string,i) : 
	    ICHAR(gensym_string,i);
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = simple_or_wide_character;
	g2int_twrite_wide_character(CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
		CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
		CHAR_TO_CHARACTER(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(CHAR_TO_CHARACTER(thing)) ? 
		CHAR_CODE(CHAR_TO_CHARACTER(thing)) : 
		CHAR_TO_CHARACTER(thing));
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* TWRITE-BEGINNING-OF-WIDE-STRING-UNPARSABLY-TO-CURRENT-WIDE-STRING */
Object g2int_twrite_beginning_of_wide_string_unparsably_to_current_wide_string(wide_string,
	    first_n_characters)
    Object wide_string, first_n_characters;
{
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, incff_1_arg;
    SI_Long fill_pointer_for_current_wide_string_new_value;
    char temp;

    x_note_fn_call(24,169);
    if ( !FIXNUM_LT(FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,
	    first_n_characters),G2int_total_length_of_current_wide_string))
	g2int_extend_current_wide_string(FIXNUM_ADD(G2int_fill_pointer_for_current_wide_string,
		first_n_characters));
    if (EQ(wide_string,G2int_current_wide_string)) {
	if ((SI_Long)0L == IFIX(first_n_characters))
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < 
		    IFIX(G2int_fill_pointer_for_current_wide_string) ? 
		    FIXNUM_LT(G2int_fill_pointer_for_current_wide_string,
		    first_n_characters) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = IFIX(G2int_fill_pointer_for_current_wide_string);
		arg_1 = (SI_Long)0L;
		arg_2 = IFIX(G2int_fill_pointer_for_current_wide_string) + 
			(IFIX(first_n_characters) - (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		g2int_copy_byte_vector_16_portion_carefully(wide_string,
			FIX((SI_Long)0L),G2int_current_wide_string,
			G2int_fill_pointer_for_current_wide_string,
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
	gensymed_symbol_2 = G2int_current_wide_string;
	gensymed_symbol_3 = IFIX(G2int_fill_pointer_for_current_wide_string);
	gensymed_symbol_4 = IFIX(first_n_characters) - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    incff_1_arg = IFIX(first_n_characters) - (SI_Long)0L;
    fill_pointer_for_current_wide_string_new_value = 
	    IFIX(G2int_fill_pointer_for_current_wide_string) + incff_1_arg;
    G2int_fill_pointer_for_current_wide_string = 
	    FIX(fill_pointer_for_current_wide_string_new_value);
    return VALUES_1(Nil);
}

Object G2int_wide_twrite_fixnum_buffer = UNBOUND;

Object G2int_most_negative_fixnum_as_string = UNBOUND;

Object G2int_length_of_most_negative_fixnum_as_string = UNBOUND;

/* TWRITE-FIXNUM-INTO-WIDE-STRING */
Object g2int_twrite_fixnum_into_wide_string(fixnum_to_write_init,
	    wide_string,start_index_init)
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

    x_note_fn_call(24,170);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    start_index = IFIX(start_index_init);
    if (fixnum_to_write == IFIX(Most_negative_fixnum)) {
	current_wide_string_list = Qg2int_do_not_use;
	PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		5);
	  wide_string_bv16 = 
		  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,4);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    3);
	      length_1 = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L));
	      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		      2);
		current_twriting_output_type = Qg2int_wide_string;
		PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			1);
		  write_strings_parsably_qm = Nil;
		  PUSH_SPECIAL(G2int_write_strings_parsablyqm,write_strings_parsably_qm,
			  0);
		    result_length = 
			    G2int_length_of_most_negative_fixnum_as_string;
		    g2int_twrite_general_string(G2int_most_negative_fixnum_as_string);
		    gensymed_symbol = G2int_current_wide_string;
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
	buffer = G2int_wide_twrite_fixnum_buffer;
	last_index = 
		IFIX(FIXNUM_SUB1(G2int_length_of_wide_twrite_fixnum_buffer));
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
	source_start = IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		digit_count;
	result_length_1 = digit_count;
	if (fixnum_to_write < (SI_Long)0L) {
	    UBYTE_16_ISASET_1(wide_string,start_index,(SI_Long)45L);
	    start_index = start_index + (SI_Long)1L;
	    result_length_1 = result_length_1 + (SI_Long)1L;
	}
	gensymed_symbol = G2int_wide_twrite_fixnum_buffer;
	gensymed_symbol_1 = source_start;
	gensymed_symbol_2 = wide_string;
	gensymed_symbol_3 = start_index;
	gensymed_symbol_4 = 
		IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - source_start;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	temp = FIX(result_length_1);
    }
    return VALUES_1(temp);
}

/* TWRITE-FIXNUM */
Object g2int_twrite_fixnum(fixnum_to_write_init)
    Object fixnum_to_write_init;
{
    Object write_strings_parsably_qm, temp, schar_arg_2, temp_1, buffer;
    SI_Long fixnum_to_write, positive_fixnum, last_index, digit_count, number;
    SI_Long next, digit, temp_2, aref_arg_2, gensymed_symbol;
    Declare_special(1);

    x_note_fn_call(24,171);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    if (fixnum_to_write == IFIX(Most_negative_fixnum)) {
	write_strings_parsably_qm = Nil;
	PUSH_SPECIAL(G2int_write_strings_parsablyqm,write_strings_parsably_qm,
		0);
	  g2int_twrite_general_string(G2int_most_negative_fixnum_as_string);
	POP_SPECIAL();
    }
    else {
	if (fixnum_to_write < (SI_Long)0L) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
		g2int_twrite_wide_character(FIX((SI_Long)45L));
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		temp_1 = CHR('-');
		SET_SCHAR(temp,schar_arg_2,temp_1);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    positive_fixnum =  - fixnum_to_write;
	}
	else
	    positive_fixnum = fixnum_to_write;
	buffer = G2int_wide_twrite_fixnum_buffer;
	last_index = 
		IFIX(FIXNUM_SUB1(G2int_length_of_wide_twrite_fixnum_buffer));
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
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	    g2int_twrite_portion_of_wide_string_unparsably_to_current_wide_string(G2int_wide_twrite_fixnum_buffer,
		    FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		    digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
	else
	    g2int_twrite_portion_of_string_unparsably(G2int_wide_twrite_fixnum_buffer,
		    FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		    digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
    }
    return VALUES_1(Nil);
}

Object G2int_twrite_fixnum_buffer = UNBOUND;

/* TWRITE-POSITIVE-FIXNUM */
Object g2int_twrite_positive_fixnum(fixnum_to_write_init)
    Object fixnum_to_write_init;
{
    Object buffer, aref_new_value;
    SI_Long fixnum_to_write, last_index, digit_count, number, next, digit;
    SI_Long temp, aref_arg_2, gensymed_symbol;

    x_note_fn_call(24,172);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    buffer = G2int_wide_twrite_fixnum_buffer;
    last_index = IFIX(FIXNUM_SUB1(G2int_length_of_wide_twrite_fixnum_buffer));
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
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	g2int_twrite_portion_of_wide_string_unparsably_to_current_wide_string(G2int_wide_twrite_fixnum_buffer,
		FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
    else
	g2int_twrite_portion_of_string_unparsably(G2int_wide_twrite_fixnum_buffer,
		FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
    return VALUES_1(Nil);
}

/* TWRITE-POSITIVE-FIXNUM-IN-RADIX */
Object g2int_twrite_positive_fixnum_in_radix(fixnum_to_write_init,radix_init)
    Object fixnum_to_write_init, radix_init;
{
    Object buffer;
    SI_Long fixnum_to_write, radix, last_index, digit_count, number, next;
    SI_Long digit, temp, aref_arg_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long aref_new_value;

    x_note_fn_call(24,173);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    radix = IFIX(radix_init);
    buffer = G2int_wide_twrite_fixnum_buffer;
    last_index = IFIX(FIXNUM_SUB1(G2int_length_of_wide_twrite_fixnum_buffer));
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
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
	g2int_twrite_portion_of_wide_string_unparsably_to_current_wide_string(G2int_wide_twrite_fixnum_buffer,
		FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
    else
	g2int_twrite_portion_of_string_unparsably(G2int_wide_twrite_fixnum_buffer,
		FIX(IFIX(G2int_length_of_wide_twrite_fixnum_buffer) - 
		digit_count),G2int_length_of_wide_twrite_fixnum_buffer);
    return VALUES_1(Nil);
}

/* TWRITE-POSITIVE-BIGNUM-IN-RADIX */
Object g2int_twrite_positive_bignum_in_radix(positive_bignum,radix_init)
    Object positive_bignum, radix_init;
{
    Object quotient, remainder_1, simple_or_wide_character, thing, temp;
    Object schar_arg_2, schar_new_value, rem_2;
    SI_Long radix, rem_1;
    Object result;

    x_note_fn_call(24,174);
    radix = IFIX(radix_init);
    if (NUM_GE(positive_bignum,FIX(radix))) {
	result = lfloor(positive_bignum,FIX(radix));
	MVS_2(result,quotient,remainder_1);
	rem_1 = IFIX(g2int_coerce_number_to_fixnum(remainder_1));
	if (NUM_LE(quotient,Most_positive_fixnum))
	    g2int_twrite_positive_fixnum_in_radix(quotient,FIX(radix));
	else
	    g2int_twrite_positive_bignum_in_radix(quotient,FIX(radix));
	simple_or_wide_character = digit_char(FIX(rem_1),FIX(radix),_);
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    return g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
	}
    }
    else {
	rem_2 = g2int_coerce_number_to_fixnum(positive_bignum);
	simple_or_wide_character = digit_char(rem_2,FIX(radix),_);
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    return g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
	}
    }
}

/* TWRITE-N-DIGIT-NUMBER-WITH-0-PAD */
Object g2int_twrite_n_digit_number_with_0_pad(n_1,number)
    Object n_1, number;
{
    Object num, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp, digits, digit, ab_loop_list_, simple_or_wide_character, thing;
    Object temp_1, schar_arg_2, schar_new_value;
    SI_Long i, ab_loop_bind_, gensymed_symbol;

    x_note_fn_call(24,175);
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
	num = g2int_chestnut_floorf_function(num,FIX((SI_Long)10L));
    ab_loopvar__2 = g2int_gensym_cons_1(g2int_chestnut_modf_function(num,
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
    goto end;
    temp = Qnil;
  end:;
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
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = simple_or_wide_character;
	g2int_twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp_1 = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp_1;
    }
    goto next_loop_1;
  end_loop_1:
    g2int_reclaim_gensym_list_1(digits);
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* "-9223372036854775808" */

/* TWRITE-LONG-FUNCTION */
Object g2int_twrite_long_function(long_to_write)
    Object long_to_write;
{
    Object write_strings_parsably_qm, temp, temp_1, schar_arg_2;
    SI_int64 positive_long;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(24,176);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (NUM_EQ(long_to_write,G2int_most_negative_int64)) {
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL(G2int_write_strings_parsablyqm,write_strings_parsably_qm,
		    0);
	      g2int_twrite_general_string(string_constant_10);
	    POP_SPECIAL();
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(long_to_write,temp)) {
		if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
		    g2int_twrite_wide_character(FIX((SI_Long)45L));
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_1 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    temp = CHR('-');
		    SET_SCHAR(temp_1,schar_arg_2,temp);
		    temp_1 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_1;
		}
		temp = negate(long_to_write);
		positive_long = INTEGER_TO_INT64(temp);
	    }
	    else
		positive_long = INTEGER_TO_INT64(long_to_write);
	    g2int_twrite_positive_bignum_in_radix(INT64_TO_INTEGER(positive_long),
		    FIX((SI_Long)10L));
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "L" */

/* TWRITE-LONG */
Object g2int_twrite_long(long_to_write)
    Object long_to_write;
{
    Object write_strings_parsably_qm, temp, temp_1, schar_arg_2;
    SI_int64 positive_long;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(24,177);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (NUM_EQ(long_to_write,G2int_most_negative_int64)) {
	    write_strings_parsably_qm = Nil;
	    PUSH_SPECIAL(G2int_write_strings_parsablyqm,write_strings_parsably_qm,
		    0);
	      g2int_twrite_general_string(string_constant_10);
	    POP_SPECIAL();
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(long_to_write,temp)) {
		if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string))
		    g2int_twrite_wide_character(FIX((SI_Long)45L));
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_1 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    temp = CHR('-');
		    SET_SCHAR(temp_1,schar_arg_2,temp);
		    temp_1 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_1;
		}
		temp = negate(long_to_write);
		positive_long = INTEGER_TO_INT64(temp);
	    }
	    else
		positive_long = INTEGER_TO_INT64(long_to_write);
	    g2int_twrite_positive_bignum_in_radix(INT64_TO_INTEGER(positive_long),
		    FIX((SI_Long)10L));
	}
	g2int_twrite_general_string(string_constant_11);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

Object G2int_smallest_order_of_magnitude = UNBOUND;

Object G2int_float_with_smallest_order_of_magnitude = UNBOUND;

Object G2int_order_of_largest_fixnum_power_of_ten = UNBOUND;

Object G2int_integer_decade_table = UNBOUND;

static Object string_constant_12;  /* "~x" */

/* TWRITE-RGB-AS-PADDED-HEX */
Object g2int_twrite_rgb_as_padded_hex(r_value,g_value,b_value)
    Object r_value, g_value, b_value;
{
    Object substitute_value;

    x_note_fn_call(24,178);
    if (IFIX(r_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(r_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = r_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	g2int_twrite_character(FIX((SI_Long)48L));
    g2int_tformat(2,string_constant_12,substitute_value);
    if (IFIX(g_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(g_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = g_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	g2int_twrite_character(FIX((SI_Long)48L));
    g2int_tformat(2,string_constant_12,substitute_value);
    if (IFIX(b_value) < (SI_Long)0L)
	substitute_value = FIX((SI_Long)0L);
    else if (IFIX(b_value) > (SI_Long)255L)
	substitute_value = FIX((SI_Long)255L);
    else
	substitute_value = b_value;
    if (IFIX(substitute_value) < (SI_Long)16L)
	g2int_twrite_character(FIX((SI_Long)48L));
    return g2int_tformat(2,string_constant_12,substitute_value);
}

/* C-WRITE-FLOAT-FROM-C */
Object g2int_c_write_float_from_c(return_string,format_string,precision,
	    double_1)
    Object return_string, format_string, precision, double_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1, *temp_2;
    double temp_3;

    x_note_fn_call(24,179);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(return_string);
    gensymed_symbol_1 = 
	    g2int_copy_foreign_string_arg_if_appropriate(format_string);
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
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(Nil);
}

Object G2int_new_decade_table = UNBOUND;

Object G2int_new_fractional_decade_table = UNBOUND;

Object G2int_string_for_returning_floats = UNBOUND;

Object G2int_null_char = UNBOUND;

static Object string_constant_13;  /* "%.*f" */

/* GENSYM-SPRINTF-FLOAT */
Object g2int_gensym_sprintf_float(string_to_write_into,precision,
	    number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    x_note_fn_call(24,180);
    return g2int_c_write_float_from_c(string_to_write_into,
	    string_constant_13,precision,number_to_write);
}

static Object string_constant_14;  /* "%.*g" */

/* GENSYM-SPRINTF-FLOAT-OR-EXPONENTIAL */
Object g2int_gensym_sprintf_float_or_exponential(string_to_write_into,
	    precision,number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    x_note_fn_call(24,181);
    return g2int_c_write_float_from_c(string_to_write_into,
	    string_constant_14,precision,number_to_write);
}

static Object string_constant_15;  /* "%.*e" */

/* GENSYM-SPRINTF-EXPONENTIAL */
Object g2int_gensym_sprintf_exponential(string_to_write_into,precision,
	    number_to_write)
    Object string_to_write_into, precision, number_to_write;
{
    Object i, this_char, index_delta, exponent_marker_encountered_p;
    Object at_least_one_nonzero_exponent_digit_written_p, schar_arg_2;
    Object schar_new_value, index_of_zero_exponent, temp;

    x_note_fn_call(24,182);
    g2int_c_write_float_from_c(string_to_write_into,string_constant_15,
	    precision,number_to_write);
    i = FIX((SI_Long)0L);
    this_char = Nil;
    index_delta = FIX((SI_Long)0L);
    exponent_marker_encountered_p = Nil;
    at_least_one_nonzero_exponent_digit_written_p = Nil;
  next_loop:
    this_char = SCHAR(string_to_write_into,i);
    if (EQL(this_char,G2int_null_char))
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
	schar_new_value = G2int_null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    else {
	index_of_zero_exponent = FIXNUM_MINUS(i,index_delta);
	temp = CHR('0');
	SET_SCHAR(string_to_write_into,index_of_zero_exponent,temp);
	schar_arg_2 = FIXNUM_ADD1(index_of_zero_exponent);
	schar_new_value = G2int_null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    return VALUES_1(Qnil);
}

/* GENSYM-SPRINTF-MINIMAL-EXPONENTIAL */
Object g2int_gensym_sprintf_minimal_exponential(string_to_write_into,
	    number_to_write)
    Object string_to_write_into, number_to_write;
{
    Object i, this_char, index_delta, exponent_marker_encountered_p;
    Object at_least_one_nonzero_exponent_digit_written_p, schar_arg_2;
    Object schar_new_value, index_of_zero_exponent, temp;

    x_note_fn_call(24,183);
    g2int_c_write_float_from_c(string_to_write_into,string_constant_15,
	    FIX((SI_Long)0L),number_to_write);
    i = FIX((SI_Long)0L);
    this_char = Nil;
    index_delta = FIX((SI_Long)0L);
    exponent_marker_encountered_p = Nil;
    at_least_one_nonzero_exponent_digit_written_p = Nil;
  next_loop:
    this_char = SCHAR(string_to_write_into,i);
    if (CHAR_EQ(this_char,G2int_null_char))
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
	schar_new_value = G2int_null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    else {
	index_of_zero_exponent = FIXNUM_MINUS(i,index_delta);
	temp = CHR('0');
	SET_SCHAR(string_to_write_into,index_of_zero_exponent,temp);
	schar_arg_2 = FIXNUM_ADD1(index_of_zero_exponent);
	schar_new_value = G2int_null_char;
	SET_SCHAR(string_to_write_into,schar_arg_2,schar_new_value);
    }
    return VALUES_1(Qnil);
}

/* TWRITE-NUMBER-STRING-AS-IS */
Object g2int_twrite_number_string_as_is(number_string)
    Object number_string;
{
    Object this_char, thing, temp, schar_arg_2, schar_new_value;
    SI_Long i;

    x_note_fn_call(24,184);
    i = (SI_Long)0L;
    this_char = Nil;
  next_loop:
    if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	goto end_loop;
    this_char = CHR(ISCHAR(number_string,i));
    if (CHAR_EQ(G2int_null_char,this_char))
	goto end_loop;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = this_char;
	g2int_twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = this_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TWRITE-NUMBER-STRING-SUPPRESSING-FRACTION-ENTIRELY */
Object g2int_twrite_number_string_suppressing_fraction_entirely(number_string)
    Object number_string;
{
    Object this_char, thing, temp, schar_arg_2, schar_new_value;
    SI_Long i;

    x_note_fn_call(24,185);
    i = (SI_Long)0L;
    this_char = Nil;
  next_loop:
    if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	goto end_loop;
    this_char = CHR(ISCHAR(number_string,i));
    if (CHAR_EQ(this_char,G2int_null_char) || CHAR_EQ(this_char,CHR('.')))
	goto end_loop;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = this_char;
	g2int_twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = this_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COUNT-OF-NUMBER-STRING-TRAILING-ZEROS */
Object g2int_count_of_number_string_trailing_zeros(number_string,
	    use_exponential_notation_p)
    Object number_string, use_exponential_notation_p;
{
    Object index_of_final_trailing_digit, this_char;
    Object index_of_final_nonzero_trailing_digit;
    SI_Long i;

    x_note_fn_call(24,186);
    if (use_exponential_notation_p) {
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	    goto end_loop;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),CHR('e')))
	    goto end_loop;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end;
	index_of_final_trailing_digit = Qnil;
      end:;
    }
    else {
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),G2int_null_char))
	    goto end_loop_1;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_1;
	index_of_final_trailing_digit = Qnil;
      end_1:;
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
	goto end_2;
    }
    else {
	index_of_final_nonzero_trailing_digit = FIX(i);
	goto end_2;
    }
    index_of_final_nonzero_trailing_digit = Qnil;
  end_2:;
    return VALUES_1(FIXNUM_MINUS(index_of_final_trailing_digit,
	    index_of_final_nonzero_trailing_digit));
}

/* TWRITE-NUMBER-STRING-SUPPRESSING-TRAILING-ZEROS */
Object g2int_twrite_number_string_suppressing_trailing_zeros(number_string,
	    use_exponential_notation_p)
    Object number_string, use_exponential_notation_p;
{
    Object index_of_exponent_marker_qm, index_of_final_trailing_digit;
    Object this_char, index_of_final_nonzero_trailing_digit, i_1;
    SI_Long i;

    x_note_fn_call(24,187);
    index_of_exponent_marker_qm = Nil;
    if (use_exponential_notation_p) {
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	    goto end_loop;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),CHR('e')))
	    goto end_loop;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	index_of_exponent_marker_qm = FIX(i);
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end;
	index_of_final_trailing_digit = Qnil;
      end:;
    }
    else {
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= IFIX(G2int_size_of_string_for_returning_floats))
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ISCHAR(number_string,i)),G2int_null_char))
	    goto end_loop_1;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	index_of_final_trailing_digit = FIX(i - (SI_Long)1L);
	goto end_1;
	index_of_final_trailing_digit = Qnil;
      end_1:;
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
	goto end_2;
    }
    else {
	index_of_final_nonzero_trailing_digit = FIX(i);
	goto end_2;
    }
    index_of_final_nonzero_trailing_digit = Qnil;
  end_2:;
    i_1 = FIX((SI_Long)0L);
    this_char = Nil;
  next_loop_3:
    this_char = SCHAR(number_string,i_1);
    if (FIXNUM_GE(i_1,G2int_size_of_string_for_returning_floats) || 
	    CHAR_EQ(this_char,G2int_null_char))
	goto end_loop_3;
    g2int_twrite(this_char);
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

static Object Qg2int_unbound_in_protected_let;  /* unbound-in-protected-let */

static Object float_constant_1;    /* 1.0 */

static Object float_constant_2;    /* -1.0 */

static Object string_constant_16;  /* "0.0" */

/* TWRITE-NUMBER-STRING-IN-FIXED-FIELD */
Object g2int_twrite_number_string_in_fixed_field(number,number_string,
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

    x_note_fn_call(24,188);
    SAVE_STACK();
    if (zero_fraction_size_p)
	number = lfloat(l_round(number,_),float_constant);
    field_width = fixed_field_width;
    number_string_before_heuristics = Qg2int_unbound_in_protected_let;
    suppressed_trailing_zeros_unasked_qm = Qg2int_unbound_in_protected_let;
    truncated_non_exponential_qm = Qg2int_unbound_in_protected_let;
    magnitude_less_than_one_p = Qg2int_unbound_in_protected_let;
    too_small_number_qm = Qg2int_unbound_in_protected_let;
    exponential_notation_unasked_qm = Qg2int_unbound_in_protected_let;
    exponential_number_string = Qg2int_unbound_in_protected_let;
    length_of_exponential_number_string = Qg2int_unbound_in_protected_let;
    index_of_decimal_point = Qg2int_unbound_in_protected_let;
    index_of_exponent_marker = Qg2int_unbound_in_protected_let;
    number_of_decimal_places_before_truncation = 
	    Qg2int_unbound_in_protected_let;
    maximum_characters_that_can_be_truncated = Qg2int_unbound_in_protected_let;
    number_of_characters_to_truncate = Qg2int_unbound_in_protected_let;
    truncated_exponential_qm = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	current_wide_string_list = Qg2int_do_not_use;
	PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = 
		  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L));
	      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qg2int_wide_string;
		PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			0);
		  if (suppress_trailing_zeros_p)
		      g2int_twrite_number_string_suppressing_trailing_zeros(number_string,
			      use_exponential_notation_p);
		  else
		      g2int_twrite_number_string_as_is(number_string);
		  number_string_before_heuristics = 
			  g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (number_string_before_heuristics) {
	    temp = 
		    g2int_length_of_null_terminated_text_string(number_string_before_heuristics);
	    if (temp);
	    else
		temp = 
			g2int_text_string_length(number_string_before_heuristics);
	    temp_1 = NUM_LE(temp,field_width);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    SAVE_VALUES(g2int_twrite_general_string(number_string_before_heuristics));
	else {
	    if ( !TRUEP(suppress_trailing_zeros_p)) {
		current_wide_string_list = Qg2int_do_not_use;
		PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
		  current_wide_string = wide_string_bv16;
		  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
			  3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qg2int_wide_string;
			PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
				0);
			  g2int_twrite_number_string_suppressing_trailing_zeros(number_string,
				  use_exponential_notation_p);
			  suppressed_trailing_zeros_unasked_qm = 
				  g2int_copy_out_current_wide_string();
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
			g2int_length_of_null_terminated_text_string(suppressed_trailing_zeros_unasked_qm);
		if (temp);
		else
		    temp = 
			    g2int_text_string_length(suppressed_trailing_zeros_unasked_qm);
		temp_1 = NUM_LE(temp,field_width);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		SAVE_VALUES(g2int_twrite_general_string(suppressed_trailing_zeros_unasked_qm));
	    else {
		if ( !TRUEP(use_exponential_notation_p)) {
		    length_of_number_string = 
			    g2int_length_of_null_terminated_string(number_string);
		    if (length_of_number_string);
		    else
			length_of_number_string = 
				g2int_text_string_length(number_string_before_heuristics);
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
		    goto end;
		    index_of_decimal_point = Qnil;
		  end:;
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
			    goto end_1;
			}
			else {
			    index_of_final_nonzero_trailing_digit_qm = FIX(i);
			    goto end_1;
			}
			index_of_final_nonzero_trailing_digit_qm = Qnil;
		      end_1:;
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
			current_wide_string_list = Qg2int_do_not_use;
			PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
			  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = 
					Qg2int_wide_string;
				PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
					0);
				  if (FIXNUM_GE(number_of_characters_to_truncate,
					  FIXNUM_SUB1(maximum_characters_that_can_be_truncated))) 
					      {
				      g2int_gensym_sprintf_float(number_string,
					      FIX((SI_Long)1L),number);
				      g2int_twrite_number_string_suppressing_fraction_entirely(number_string);
				  }
				  else {
				      g2int_gensym_sprintf_float(number_string,
					      FIXNUM_MINUS(number_of_decimal_places_before_truncation,
					      number_of_characters_to_truncate),
					      number);
				      g2int_twrite_number_string_as_is(number_string);
				  }
				  truncated_non_exponential_qm = 
					  g2int_copy_out_current_wide_string();
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
			    g2int_length_of_null_terminated_text_string(truncated_non_exponential_qm);
		    if (temp);
		    else
			temp = 
				g2int_text_string_length(truncated_non_exponential_qm);
		    temp_1 = NUM_LE(temp,field_width);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    SAVE_VALUES(g2int_twrite_general_string(truncated_non_exponential_qm));
		else {
		    magnitude_less_than_one_p = NUM_LT(number,
			    float_constant_1) ? (NUM_GT(number,
			    float_constant_2) ? T : Nil) : Qnil;
		    if (magnitude_less_than_one_p &&  
			    !TRUEP(use_exponential_notation_p) &&  
			    !TRUEP(force_small_number_into_exponential_p)) {
			if (IFIX(fixed_field_width) >= (SI_Long)3L) {
			    current_wide_string_list = Qg2int_do_not_use;
			    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
			      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qg2int_wide_string;
				    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
					    0);
				      g2int_twrite_general_string(string_constant_16);
				      ab_loop_repeat_ = 
					      IFIX(fixed_field_width) - 
					      (IFIX(fraction_size) + 
					      (SI_Long)3L);
				    next_loop_2:
				      if ( !((SI_Long)0L < ab_loop_repeat_))
					  goto end_loop_2;
				      ab_loop_repeat_ = ab_loop_repeat_ - 
					      (SI_Long)1L;
				      if (EQ(G2int_current_twriting_output_type,
					      Qg2int_wide_string)) {
					  thing = (SI_Long)48L;
					  g2int_twrite_wide_character(CHARACTERP(FIX(thing)) 
						  ? CHAR_CODE(FIX(thing)) :
						   FIX(thing));
				      }
				      else {
					  if ( 
						  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
						  G2int_total_length_of_current_gensym_string))
					      g2int_extend_current_gensym_string(0);
					  temp_2 = G2int_current_gensym_string;
					  schar_arg_2 = 
						  G2int_fill_pointer_for_current_gensym_string;
					  thing = (SI_Long)48L;
					  schar_new_value = 
						  CODE_CHAR(CHARACTERP(FIX(thing)) 
						  ? CHAR_CODE(FIX(thing)) :
						   FIX(thing));
					  SET_SCHAR(temp_2,schar_arg_2,
						  schar_new_value);
					  temp_2 = 
						  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
					  G2int_fill_pointer_for_current_gensym_string 
						  = temp_2;
				      }
				      goto next_loop_2;
				    end_loop_2:;
				      too_small_number_qm = 
					      g2int_copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			else {
			    current_wide_string_list = Qg2int_do_not_use;
			    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
			      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qg2int_wide_string;
				    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
					    0);
				      ab_loop_repeat_ = 
					      IFIX(fixed_field_width);
				    next_loop_3:
				      if ( !((SI_Long)0L < ab_loop_repeat_))
					  goto end_loop_3;
				      ab_loop_repeat_ = ab_loop_repeat_ - 
					      (SI_Long)1L;
				      if (EQ(G2int_current_twriting_output_type,
					      Qg2int_wide_string)) {
					  thing_1 = over_or_underflow_char;
					  g2int_twrite_wide_character(CHARACTERP(thing_1) 
						  ? CHAR_CODE(thing_1) : 
						  thing_1);
				      }
				      else {
					  if ( 
						  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
						  G2int_total_length_of_current_gensym_string))
					      g2int_extend_current_gensym_string(0);
					  temp_2 = G2int_current_gensym_string;
					  schar_arg_2 = 
						  G2int_fill_pointer_for_current_gensym_string;
					  thing_1 = over_or_underflow_char;
					  schar_new_value = 
						  CODE_CHAR(CHARACTERP(thing_1) 
						  ? CHAR_CODE(thing_1) : 
						  thing_1);
					  SET_SCHAR(temp_2,schar_arg_2,
						  schar_new_value);
					  temp_2 = 
						  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
					  G2int_fill_pointer_for_current_gensym_string 
						  = temp_2;
				      }
				      goto next_loop_3;
				    end_loop_3:;
				      too_small_number_qm = 
					      g2int_copy_out_current_wide_string();
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
				g2int_length_of_null_terminated_text_string(too_small_number_qm);
			if (temp);
			else
			    temp = 
				    g2int_text_string_length(too_small_number_qm);
			temp_1 = NUM_LE(temp,field_width);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			SAVE_VALUES(g2int_twrite_general_string(too_small_number_qm));
		    else {
			if ( !TRUEP(use_exponential_notation_p) && 
				(magnitude_less_than_one_p ? 
				TRUEP(force_small_number_into_exponential_p) 
				: TRUEP(T))) {
			    current_wide_string_list = Qg2int_do_not_use;
			    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
			      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qg2int_wide_string;
				    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
					    0);
				      g2int_gensym_sprintf_exponential(number_string,
					      fraction_size,number);
				      g2int_twrite_number_string_as_is(number_string);
				      exponential_notation_unasked_qm = 
					      g2int_copy_out_current_wide_string();
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
				    g2int_length_of_null_terminated_text_string(exponential_notation_unasked_qm);
			    if (temp);
			    else
				temp = 
					g2int_text_string_length(exponential_notation_unasked_qm);
			    temp_1 = NUM_LE(temp,field_width);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    SAVE_VALUES(g2int_twrite_general_string(exponential_notation_unasked_qm));
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
				    g2int_length_of_null_terminated_text_string(exponential_number_string);
			    if (temp);
			    else
				temp = 
					g2int_text_string_length(exponential_number_string);
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
			    goto end_2;
			    index_of_decimal_point = Qnil;
			  end_2:;
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
			    goto end_3;
			    index_of_exponent_marker = Qnil;
			  end_3:;
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
				current_wide_string_list = Qg2int_do_not_use;
				PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
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
				  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qg2int_wide_string;
					PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
						0);
					  if (FIXNUM_GE(number_of_characters_to_truncate,
						  FIXNUM_SUB1(maximum_characters_that_can_be_truncated)))
					      g2int_gensym_sprintf_minimal_exponential(number_string,
						      number);
					  else
					      g2int_gensym_sprintf_exponential(number_string,
						      FIXNUM_MINUS(number_of_decimal_places_before_truncation,
						      number_of_characters_to_truncate),
						      number);
					  g2int_twrite_number_string_as_is(number_string);
					  truncated_exponential_qm = 
						  g2int_copy_out_current_wide_string();
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
					g2int_length_of_null_terminated_text_string(truncated_exponential_qm);
				if (temp);
				else
				    temp = 
					    g2int_text_string_length(truncated_exponential_qm);
				temp_1 = NUM_LE(temp,field_width);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				SAVE_VALUES(g2int_twrite_general_string(truncated_exponential_qm));
			    else {
				over_or_underflow_char_1 = 
					over_or_underflow_char;
				ab_loop_repeat_ = IFIX(field_width);
			      next_loop_6:
				if ( !((SI_Long)0L < ab_loop_repeat_))
				    goto end_loop_6;
				ab_loop_repeat_ = ab_loop_repeat_ - 
					(SI_Long)1L;
				if (EQ(G2int_current_twriting_output_type,
					Qg2int_wide_string)) {
				    thing_1 = over_or_underflow_char_1;
				    g2int_twrite_wide_character(CHARACTERP(thing_1) 
					    ? CHAR_CODE(thing_1) : thing_1);
				}
				else {
				    if ( 
					    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
					    G2int_total_length_of_current_gensym_string))
					g2int_extend_current_gensym_string(0);
				    temp_2 = G2int_current_gensym_string;
				    schar_arg_2 = 
					    G2int_fill_pointer_for_current_gensym_string;
				    thing_1 = over_or_underflow_char_1;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing_1) ?
					     CHAR_CODE(thing_1) : thing_1);
				    SET_SCHAR(temp_2,schar_arg_2,
					    schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
				    G2int_fill_pointer_for_current_gensym_string 
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
	if ( !EQ(truncated_exponential_qm,Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(truncated_exponential_qm);
    }
    if (exponential_notation_unasked_qm) {
	if ( !EQ(exponential_notation_unasked_qm,
		Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(exponential_notation_unasked_qm);
    }
    if (too_small_number_qm) {
	if ( !EQ(too_small_number_qm,Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(too_small_number_qm);
    }
    if (truncated_non_exponential_qm) {
	if ( !EQ(truncated_non_exponential_qm,Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(truncated_non_exponential_qm);
    }
    if (suppressed_trailing_zeros_unasked_qm) {
	if ( !EQ(suppressed_trailing_zeros_unasked_qm,
		Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(suppressed_trailing_zeros_unasked_qm);
    }
    if (number_string_before_heuristics) {
	if ( !EQ(number_string_before_heuristics,
		Qg2int_unbound_in_protected_let))
	    g2int_reclaim_text_string(number_string_before_heuristics);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PAD-EXPONENT-TO-FIXED-WIDTH */
Object g2int_pad_exponent_to_fixed_width varargs_1(int, n)
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

    x_note_fn_call(24,189);
    INIT_ARGS_nonrelocating();
    fixed_exponent_subfield_width = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    plus_sign_char = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : CHR('0');
    END_ARGS_nonrelocating();
    string_for_storing_exponent = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	string_for_storing_exponent = g2int_obtain_adjustable_gensym_string();
	SET_FILL_POINTER(string_for_storing_exponent,FIX((SI_Long)0L));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = 
		IFIX(FIXNUM_SUB1(G2int_size_of_string_for_returning_floats));
	this_char = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	this_char = CHR(ISCHAR(G2int_string_for_returning_floats,index_1));
	if (CHAR_EQ(this_char,G2int_null_char))
	    goto end_loop;
	if (CHAR_EQ(this_char,CHR('e'))) {
	    next_index = index_1 + (SI_Long)1L;
	    minus_exponent_p = 
		    CHAR_EQ(CHR(ISCHAR(G2int_string_for_returning_floats,
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
	    if (from_index >= IFIX(G2int_size_of_string_for_returning_floats))
		goto end_loop_1;
	    exponent_char = CHR(ISCHAR(G2int_string_for_returning_floats,
		    from_index));
	    if ( !TRUEP(ab_loop_iter_flag_))
		to_index = to_index + (SI_Long)1L;
	    if (CHAR_EQ(exponent_char,G2int_null_char))
		goto end_loop_1;
	    SET_ICHAR(string_for_storing_exponent,to_index,
		    ICHAR_CODE(exponent_char));
	    ab_loop_iter_flag_ = Nil;
	    from_index = from_index + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    number_of_exponent_digits = FIX(to_index);
	    temp = G2int_null_char;
	    SET_ICHAR(string_for_storing_exponent,to_index,ICHAR_CODE(temp));
	    number_of_zeros_for_exponent_pad = 
		    FIXNUM_SUB1(FIXNUM_MINUS(fixed_exponent_subfield_width,
		    number_of_exponent_digits));
	    new_exponent_digits_start = minus_exponent_p ? 
		    exponent_digits_start : exponent_digits_start + 
		    (SI_Long)1L;
	    if ( !FIXNUM_MINUSP(number_of_zeros_for_exponent_pad)) {
		if ( !minus_exponent_p) {
		    temp = G2int_string_for_returning_floats;
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
		temp = G2int_string_for_returning_floats;
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
		if (to_index >= 
			IFIX(G2int_size_of_string_for_returning_floats))
		    goto end_loop_3;
		if ( !TRUEP(ab_loop_iter_flag_))
		    from_index = from_index + (SI_Long)1L;
		exponent_char = CHR(ICHAR(string_for_storing_exponent,
			from_index));
		if (CHAR_EQ(exponent_char,G2int_null_char))
		    goto end_loop_3;
		temp = G2int_string_for_returning_floats;
		SET_ISCHAR(temp,to_index,ICHAR_CODE(exponent_char));
		ab_loop_iter_flag_ = Nil;
		to_index = to_index + (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:
		temp = G2int_string_for_returning_floats;
		schar_new_value = G2int_null_char;
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
	if ( !EQ(string_for_storing_exponent,Qg2int_unbound_in_protected_let))
	    g2int_reclaim_gensym_string(string_for_storing_exponent);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object G2int_maximum_significant_decimal_digits_in_gensym_float = UNBOUND;

Object G2int_write_floats_accurately_p = UNBOUND;

static Object Qg2int_write_floating_point_number;  /* write-floating-point-number */

static Object string_constant_17;  /* "NaN" */

static Object string_constant_18;  /* "+Inf" */

static Object string_constant_19;  /* "-Inf" */

/* WRITE-FLOATING-POINT-NUMBER */
Object g2int_write_floating_point_number varargs_1(int, n)
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

    x_note_fn_call(24,190);
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
    tag_temp = UNIQUE_TAG(Qg2int_write_floating_point_number);
    if (PUSH_CATCH(tag_temp,0)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    number = g2int_managed_float_p_function(number) ? 
		    g2int_managed_float_value_function(number) : 
		    lfloat(number,float_constant);
	    if (g2int_nanp(number)) {
		g2int_twrite_general_string(string_constant_17);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (g2int_positive_infinity_p(number)) {
		g2int_twrite_general_string(string_constant_18);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (g2int_negative_infinity_p(number)) {
		g2int_twrite_general_string(string_constant_19);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    supplied_fraction_size_p =  ! !TRUEP(fraction_size) ? T : Nil;
	    if ( !TRUEP(fraction_size))
		fraction_size = FIX((SI_Long)3L);
	    zero_fraction_size_p = zerop(fraction_size);
	    integral_size = 
		    FIXNUM_MIN(G2int_maximum_significant_decimal_digits_in_gensym_float,
		    integral_size);
	    temp = 
		    IFIX(FIXNUM_MIN(G2int_maximum_significant_decimal_digits_in_gensym_float,
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
			temp_1 = ISVREF(G2int_new_decade_table,
				IFIX(integral_size));
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			use_exponential_notation_p = arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) ? ( 
				!inline_nanp_for_comparison(arg_1) ? T : 
				Nil) : Qnil;
			if (use_exponential_notation_p);
			else if (force_small_number_into_exponential_p) {
			    arg = DOUBLE_FLOAT_TO_DOUBLE(number);
			    temp_1 = 
				    ISVREF(G2int_new_fractional_decade_table,
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
			temp_1 = ISVREF(G2int_new_decade_table,
				IFIX(integral_size));
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			use_exponential_notation_p = arg >= arg_1 &&  
				!inline_nanp_for_comparison(arg) ? ( 
				!inline_nanp_for_comparison(arg_1) ? T : 
				Nil) : Qnil;
			if (use_exponential_notation_p);
			else if (force_small_number_into_exponential_p) {
			    arg = absolute_value_of_number;
			    temp_1 = 
				    ISVREF(G2int_new_fractional_decade_table,
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
	    use_exact_float_p = Nil;
	    if (use_exact_float_p);
	    else if (use_exponential_notation_p)
		g2int_gensym_sprintf_exponential(G2int_string_for_returning_floats,
			fraction_size,number);
	    else
		g2int_gensym_sprintf_float(G2int_string_for_returning_floats,
			fraction_size,number);
	    if (use_exponential_notation_p && fixed_exponent_subfield_width_qm)
		g2int_pad_exponent_to_fixed_width(1,
			fixed_exponent_subfield_width_qm);
	    if (use_exact_float_p ||  !TRUEP(suppress_trailing_zeros_p) && 
		     !TRUEP(fixed_field_width_qm))
		result = g2int_twrite_number_string_as_is(G2int_string_for_returning_floats);
	    else if ( !TRUEP(fixed_field_width_qm))
		result = g2int_twrite_number_string_suppressing_trailing_zeros(G2int_string_for_returning_floats,
			use_exponential_notation_p);
	    else
		result = g2int_twrite_number_string_in_fixed_field(number,
			G2int_string_for_returning_floats,
			fixed_field_width_qm,fraction_size,
			use_exponential_notation_p,
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

Object G2int_default_float_to_text_format = UNBOUND;

static Object Qg2int_default;      /* default */

static Object Qg2int_write_floating_point_number_simple_c_format;  /* write-floating-point-number-simple-c-format */

static Object Qg2int_exponent;     /* exponent */

static Object Qg2int_best;         /* best */

static Object Qg2int_force_zero;   /* force-zero */

static Object string_constant_20;  /* "####" */

/* WRITE-FLOATING-POINT-NUMBER-SIMPLE-C-FORMAT */
Object g2int_write_floating_point_number_simple_c_format varargs_1(int, n)
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

    x_note_fn_call(24,191);
    INIT_ARGS_nonrelocating();
    number = REQUIRED_ARG_nonrelocating();
    precision = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)3L);
    output_format = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Qg2int_default;
    minimum_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    suppress_trailing_zeros_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qg2int_write_floating_point_number_simple_c_format);
    if (PUSH_CATCH(tag_temp,0)) {
	if (EQ(output_format,Qg2int_default)) {
	    g2int_write_floating_point_number(1,number);
	    result = VALUES_1(Nil);
	    THROW(tag_temp,result);
	}
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    number = g2int_managed_float_p_function(number) ? 
		    g2int_managed_float_value_function(number) : 
		    lfloat(number,float_constant);
	    if (minimum_width_qm) {
		temp = MAX(IFIX(minimum_width_qm),(SI_Long)1L);
		temp_1 = IFIX(G2int_maximum_length_for_user_gensym_strings);
		minimum_width_qm = FIX(MIN(temp,temp_1));
	    }
	    if (g2int_nanp(number)) {
		if (minimum_width_qm)
		    g2int_twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)3L));
		g2int_twrite_general_string(string_constant_17);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (g2int_positive_infinity_p(number)) {
		if (minimum_width_qm)
		    g2int_twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		g2int_twrite_general_string(string_constant_18);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    else if (g2int_negative_infinity_p(number)) {
		if (minimum_width_qm)
		    g2int_twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		g2int_twrite_general_string(string_constant_19);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    temp_1 = MIN((SI_Long)16L,IFIX(precision));
	    precision = FIX(MAX(temp_1,(SI_Long)0L));
	    if (EQ(output_format,Qfloat))
		g2int_gensym_sprintf_float(G2int_string_for_returning_floats,
			precision,number);
	    else if (EQ(output_format,Qg2int_exponent))
		g2int_gensym_sprintf_exponential(G2int_string_for_returning_floats,
			precision,number);
	    else if (EQ(output_format,Qg2int_best))
		g2int_gensym_sprintf_float_or_exponential(G2int_string_for_returning_floats,
			precision,number);
	    else if (EQ(output_format,Qg2int_force_zero));
	    else {
		if (minimum_width_qm)
		    g2int_twrite_spaces_if_necessary(minimum_width_qm,
			    FIX((SI_Long)4L));
		g2int_twrite_general_string(string_constant_20);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    if (suppress_trailing_zeros_p &&  !EQ(output_format,
		    Qg2int_best) &&  !EQ(output_format,Qg2int_force_zero) 
		    && (EQ(output_format,Qg2int_exponent) || 
		    IFIX(precision) != (SI_Long)0L)) {
		if (minimum_width_qm) {
		    length_of_string_for_returning_floats_qm = 
			    g2int_length_of_null_terminated_string(G2int_string_for_returning_floats);
		    number_of_zeros_to_remove = 
			    g2int_count_of_number_string_trailing_zeros(G2int_string_for_returning_floats,
			    EQ(output_format,Qg2int_exponent) ? T : Nil);
		    if (length_of_string_for_returning_floats_qm)
			g2int_twrite_spaces_if_necessary(minimum_width_qm,
				FIXNUM_MINUS(length_of_string_for_returning_floats_qm,
				number_of_zeros_to_remove));
		}
		result = g2int_twrite_number_string_suppressing_trailing_zeros(G2int_string_for_returning_floats,
			EQ(output_format,Qg2int_exponent) ? T : Nil);
	    }
	    else {
		if (minimum_width_qm) {
		    length_of_string_for_returning_floats_qm = 
			    g2int_length_of_null_terminated_string(G2int_string_for_returning_floats);
		    if (length_of_string_for_returning_floats_qm)
			g2int_twrite_spaces_if_necessary(minimum_width_qm,
				length_of_string_for_returning_floats_qm);
		}
		result = g2int_twrite_number_string_as_is(G2int_string_for_returning_floats);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

void unicode_INIT()
{
    Object named_dynamic_extent_description, temp;
    Object reclaim_structure_for_gensym_string_stream, table;
    Object AB_package, Qg2int_size_of_string_for_returning_floats;
    Object float_constant_32, float_constant_31, float_constant_30;
    Object float_constant_29, float_constant_28, float_constant_27;
    Object float_constant_26, float_constant_25, float_constant_24;
    Object float_constant_23, float_constant_22, float_constant_21;
    Object float_constant_20, float_constant_19, float_constant_18;
    Object float_constant_17, float_constant_16, float_constant_15;
    Object float_constant_14, float_constant_13, float_constant_12;
    Object float_constant_11, float_constant_10, float_constant_9;
    Object float_constant_8, float_constant_7, float_constant_6;
    Object float_constant_5, float_constant_4, float_constant_3;
    Object Qg2int_new_decade_table_size;
    Object Qg2int_length_of_wide_twrite_fixnum_buffer, list_constant;
    Object Qg2int_wide_twrite_fixnum_buffer, Qg2int_make_wide_string_function;
    Object Kfuncall, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, Qg2int_read_character_code;
    Object Qg2int_gensym_string_stream, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_gensym_string_stream_count;
    Object Qg2int_chain_of_available_gensym_string_streams;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_23, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2int_memory_used_for_interned_text_strings;
    Object Qg2int_count_of_interned_text_strings;
    Object Qg2int_length_when_written_parsably, string_constant_22;
    Object string_constant_21, Qg2int_wide_string_list_maximum_length;
    Object Qg2int_named_dynamic_extent_description;
    Object Qg2int_outputting_to_wide_string, Qg2int_utilities1;
    Object Qg2int_stringw_should_not_cons_p;

    x_note_fn_call(24,192);
    SET_PACKAGE("AB");
    if (G2int_starprint_wide_string_max_lengthstar == UNBOUND)
	G2int_starprint_wide_string_max_lengthstar = FIX((SI_Long)200L);
    if (G2int_starabbreviate_wide_strings_for_legibilitystar == UNBOUND)
	G2int_starabbreviate_wide_strings_for_legibilitystar = T;
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
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    if (G2int_lisp_highest_printable_character_code == UNBOUND)
	G2int_lisp_highest_printable_character_code = FIX((SI_Long)255L);
    string_constant_9 = STATIC_STRING("UNSPECIFIED");
    Qg2int_stringw_should_not_cons_p = 
	    STATIC_SYMBOL("STRINGW-SHOULD-NOT-CONS-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_stringw_should_not_cons_p,
	    G2int_stringw_should_not_cons_p);
    Qg2int_unicode = STATIC_SYMBOL("UNICODE",AB_package);
    g2int_record_system_variable(Qg2int_stringw_should_not_cons_p,
	    Qg2int_unicode,T,Qt,Qnil,Qnil,Qnil);
    G2int_stringw_should_not_cons_p = Nil;
    Qg2int_outputting_to_wide_string = 
	    STATIC_SYMBOL("OUTPUTTING-TO-WIDE-STRING",AB_package);
    Qg2int_utilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    Qg2int_named_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    g2int_make_named_dynamic_extent_description(Qg2int_outputting_to_wide_string,
	    Qg2int_utilities1,Nil,Qnil,Qnil,Qnil,Nil);
    g2int_mutate_global_property(Qg2int_outputting_to_wide_string,
	    named_dynamic_extent_description,
	    Qg2int_named_dynamic_extent_description);
    Qg2int_wide_string_list_maximum_length = 
	    STATIC_SYMBOL("WIDE-STRING-LIST-MAXIMUM-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_wide_string_list_maximum_length,
	    FIX((SI_Long)1024L));
    string_constant_21 = 
	    STATIC_STRING("Trying to write a string longer than 2MB!");
    G2int_extend_current_text_string_error_message = string_constant_21;
    Qg2int_handle_extend_current_text_string_error = 
	    STATIC_SYMBOL("HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR",
	    AB_package);
    G2int_maximum_suggested_length_for_wide_strings = FIX((SI_Long)2048L);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    Qg2int_symbol_name_wide_string = 
	    STATIC_SYMBOL("SYMBOL-NAME-WIDE-STRING",AB_package);
    G2int_symbol_name_wide_string_prop = Qg2int_symbol_name_wide_string;
    Qg2int_normal = STATIC_SYMBOL("NORMAL",AB_package);
    Qg2int_escape = STATIC_SYMBOL("ESCAPE",AB_package);
    Qg2int_unicode_u = STATIC_SYMBOL("UNICODE-U",AB_package);
    G2int_maximum_text_string_length = FIX((SI_Long)1048576L);
    string_constant_22 = 
	    STATIC_STRING("Attempting to allocate ~a element string, ~\n   which is beyond the established maximum of ~a.");
    G2int_maximum_text_string_length_exceeded_message = string_constant_22;
    Qg2int_length_when_written_parsably = 
	    STATIC_SYMBOL("LENGTH-WHEN-WRITTEN-PARSABLY",AB_package);
    G2int_length_when_written_parsably_prop = 
	    Qg2int_length_when_written_parsably;
    Qg2int_count_of_interned_text_strings = 
	    STATIC_SYMBOL("COUNT-OF-INTERNED-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_interned_text_strings,
	    G2int_count_of_interned_text_strings);
    g2int_record_system_variable(Qg2int_count_of_interned_text_strings,
	    Qg2int_unicode,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_memory_used_for_interned_text_strings = 
	    STATIC_SYMBOL("MEMORY-USED-FOR-INTERNED-TEXT-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_memory_used_for_interned_text_strings,
	    G2int_memory_used_for_interned_text_strings);
    g2int_record_system_variable(Qg2int_memory_used_for_interned_text_strings,
	    Qg2int_unicode,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_string_stream_g2_struct = 
	    STATIC_SYMBOL("GENSYM-STRING-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gensym_string_stream = STATIC_SYMBOL("GENSYM-STRING-STREAM",
	    AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    Qg2int_gensym_string_stream,
	    Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_gensym_string_stream,
	    Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gensym_string_stream == UNBOUND)
	G2int_the_type_description_of_gensym_string_stream = Nil;
    string_constant_23 = 
	    STATIC_STRING("43Dy8l83-Cy1n83-Cy8m8k1l8m0000001l1n8n83*qy0krk0k0");
    temp = G2int_the_type_description_of_gensym_string_stream;
    G2int_the_type_description_of_gensym_string_stream = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_23));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_string_stream_g2_struct,
	    G2int_the_type_description_of_gensym_string_stream,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_gensym_string_stream,
	    G2int_the_type_description_of_gensym_string_stream,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gensym_string_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-STRING-STREAMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gensym_string_streams,
	    G2int_chain_of_available_gensym_string_streams);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_gensym_string_streams,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym_string_stream_count = 
	    STATIC_SYMBOL("GENSYM-STRING-STREAM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_string_stream_count,
	    G2int_gensym_string_stream_count);
    g2int_record_system_variable(Qg2int_gensym_string_stream_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gensym_string_stream = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gensym_string_stream,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gensym_string_stream,
	    reclaim_structure_for_gensym_string_stream);
    Qg2int_read_character_code = STATIC_SYMBOL("READ-CHARACTER-CODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_character_code,
	    STATIC_FUNCTION(g2int_read_character_code,NIL,FALSE,1,1));
    string_constant_24 = STATIC_STRING("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (G2int_base_36_digits_string == UNBOUND)
	G2int_base_36_digits_string = g2int_stringw(string_constant_24);
    string_constant_25 = STATIC_STRING("It is empty.");
    if (G2int_message_illegal_symbol_text_string_empty == UNBOUND)
	G2int_message_illegal_symbol_text_string_empty = 
		g2int_stringw(string_constant_25);
    string_constant_26 = STATIC_STRING("It contains a newline character.");
    if (G2int_message_illegal_symbol_text_string_contains_a_newline == UNBOUND)
	G2int_message_illegal_symbol_text_string_contains_a_newline = 
		g2int_stringw(string_constant_26);
    string_constant_27 = 
	    STATIC_STRING("It contains the illegal character whose code is (hex) FFFF");
    if (G2int_message_illegal_symbol_text_string_contains_ffff == UNBOUND)
	G2int_message_illegal_symbol_text_string_contains_ffff = 
		g2int_stringw(string_constant_27);
    string_constant_28 = 
	    STATIC_STRING("It contains the illegal character whose code is (hex) FFFE");
    if (G2int_message_illegal_symbol_text_string_contains_fffe == UNBOUND)
	G2int_message_illegal_symbol_text_string_contains_fffe = 
		g2int_stringw(string_constant_28);
    string_constant_29 = 
	    STATIC_STRING("It is longer than the maximum length for symbols, 65533.");
    if (G2int_message_illegal_symbol_text_string_too_long == UNBOUND)
	G2int_message_illegal_symbol_text_string_too_long = 
		g2int_stringw(string_constant_29);
    G2int_punctuation_alist = Nil;
    g2int_note_punctuation_marks_as_such(G2int_punctuation_alist);
    G2int_standard_character_syntax_table = Nil;
    G2int_ellipsis_text_string = g2int_stringw(string_constant_7);
    G2int_ellipsis_text_string_length = FIX((SI_Long)3L);
    Qg2int_punctuation_mark_p = STATIC_SYMBOL("PUNCTUATION-MARK-P",AB_package);
    G2int_punctuation_mark_p_prop = Qg2int_punctuation_mark_p;
    Qg2int_type_of_syntactic_anomaly = 
	    STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",AB_package);
    G2int_type_of_syntactic_anomaly_prop = Qg2int_type_of_syntactic_anomaly;
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Knone = STATIC_SYMBOL("NONE",Pkeyword);
    Qg2int_wide_twrite_fixnum_buffer = 
	    STATIC_SYMBOL("WIDE-TWRITE-FIXNUM-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_wide_twrite_fixnum_buffer,
	    G2int_wide_twrite_fixnum_buffer);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_make_wide_string_function = 
	    STATIC_SYMBOL("MAKE-WIDE-STRING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_wide_string_function,
	    STATIC_FUNCTION(g2int_make_wide_string_function,NIL,FALSE,1,1));
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_make_wide_string_function,FIX((SI_Long)24L));
    g2int_record_system_variable(Qg2int_wide_twrite_fixnum_buffer,
	    Qg2int_unicode,list_constant,Qnil,Qt,Qnil,Qnil);
    Qg2int_length_of_wide_twrite_fixnum_buffer = 
	    STATIC_SYMBOL("LENGTH-OF-WIDE-TWRITE-FIXNUM-BUFFER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_length_of_wide_twrite_fixnum_buffer,
	    FIX((SI_Long)24L));
    if (G2int_most_negative_fixnum_as_string == UNBOUND)
	G2int_most_negative_fixnum_as_string = format((SI_Long)3L,Nil,"~D",
		Most_negative_fixnum);
    if (G2int_length_of_most_negative_fixnum_as_string == UNBOUND)
	G2int_length_of_most_negative_fixnum_as_string = 
		length(G2int_most_negative_fixnum_as_string);
    if (G2int_twrite_fixnum_buffer == UNBOUND)
	G2int_twrite_fixnum_buffer = make_string(1,FIX((SI_Long)24L));
    string_constant_10 = STATIC_STRING("-9223372036854775808");
    string_constant_11 = STATIC_STRING("L");
    G2int_smallest_order_of_magnitude = FIX((SI_Long)-307L);
    G2int_float_with_smallest_order_of_magnitude = Nil;
    G2int_order_of_largest_fixnum_power_of_ten = Nil;
    G2int_integer_decade_table = Nil;
    string_constant_12 = STATIC_STRING("~x");
    Qg2int_new_decade_table_size = STATIC_SYMBOL("NEW-DECADE-TABLE-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_new_decade_table_size,FIX((SI_Long)16L));
    float_constant_1 = STATIC_FLOAT(1.0);
    float_constant_3 = STATIC_FLOAT(10.0);
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
    G2int_new_decade_table = table;
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
    G2int_new_fractional_decade_table = table;
    Qg2int_size_of_string_for_returning_floats = 
	    STATIC_SYMBOL("SIZE-OF-STRING-FOR-RETURNING-FLOATS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_of_string_for_returning_floats,
	    FIX((SI_Long)100L));
    if (G2int_string_for_returning_floats == UNBOUND)
	G2int_string_for_returning_floats = make_string(1,
		G2int_size_of_string_for_returning_floats);
    if (G2int_null_char == UNBOUND)
	G2int_null_char = CODE_CHAR(FIX((SI_Long)0L));
    string_constant_13 = STATIC_STRING("%.*f");
    string_constant_14 = STATIC_STRING("%.*g");
    string_constant_15 = STATIC_STRING("%.*e");
    float_constant = STATIC_FLOAT(0.0);
    Qg2int_unbound_in_protected_let = 
	    STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",AB_package);
    float_constant_2 = STATIC_FLOAT(-1.0);
    string_constant_16 = STATIC_STRING("0.0");
    if (G2int_maximum_significant_decimal_digits_in_gensym_float == UNBOUND)
	G2int_maximum_significant_decimal_digits_in_gensym_float = 
		FIX((SI_Long)15L);
    if (G2int_write_floats_accurately_p == UNBOUND)
	G2int_write_floats_accurately_p = Nil;
    Qg2int_write_floating_point_number = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER",AB_package);
    string_constant_17 = STATIC_STRING("NaN");
    string_constant_18 = STATIC_STRING("+Inf");
    string_constant_19 = STATIC_STRING("-Inf");
    SET_SYMBOL_FUNCTION(Qg2int_write_floating_point_number,
	    STATIC_FUNCTION(g2int_write_floating_point_number,NIL,TRUE,1,10));
    if (G2int_default_float_to_text_format == UNBOUND)
	G2int_default_float_to_text_format = Nil;
    Qg2int_default = STATIC_SYMBOL("DEFAULT",AB_package);
    Qg2int_write_floating_point_number_simple_c_format = 
	    STATIC_SYMBOL("WRITE-FLOATING-POINT-NUMBER-SIMPLE-C-FORMAT",
	    AB_package);
    Qg2int_exponent = STATIC_SYMBOL("EXPONENT",AB_package);
    Qg2int_best = STATIC_SYMBOL("BEST",AB_package);
    Qg2int_force_zero = STATIC_SYMBOL("FORCE-ZERO",AB_package);
    string_constant_20 = STATIC_STRING("####");
    SET_SYMBOL_FUNCTION(Qg2int_write_floating_point_number_simple_c_format,
	    STATIC_FUNCTION(g2int_write_floating_point_number_simple_c_format,
	    NIL,TRUE,1,5));
}
