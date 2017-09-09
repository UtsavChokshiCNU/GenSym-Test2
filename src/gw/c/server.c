/* server.c
 * Input file:  server.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "server.h"


Object G2int_no_such_built_in_argument = UNBOUND;

static Object Qg2int_gensym_string;  /* gensym-string */

static Object Qg2int_wide_string;  /* wide-string */

/* COERCE-WWW-FORM-URLENCODED-TO-ASCII-TEXT */
Object g2int_coerce_www_form_urlencoded_to_ascii_text(string_1)
    Object string_1;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object length_1, i, simple_or_wide_character, temp_1, thing, temp_3;
    Object schar_arg_2, schar_new_value;
    SI_Long temp_2;
    char temp, c;
    Declare_special(4);
    Object result;

    x_note_fn_call(59,0);
    current_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    length_1 = length(string_1);
	    i = FIX((SI_Long)0L);
	  next_loop:
	    if (NUM_LE(length_1,i))
		goto end;
	    else {
		temp = CHARACTER_TO_CHAR(CHAR(string_1,i));
		i = FIXNUM_ADD1(i);
		c = temp;
	    }
	    if (EQ(CHAR_TO_CHARACTER(c),CHR('+')))
		simple_or_wide_character = CHR(' ');
	    else if (EQ(CHAR_TO_CHARACTER(c),CHR('%'))) {
		if (NUM_LE(length_1,i))
		    goto end;
		else {
		    temp = CHARACTER_TO_CHAR(CHAR(string_1,i));
		    i = FIXNUM_ADD1(i);
		    temp_1 = CHAR_TO_CHARACTER(temp);
		}
		temp_2 = (SI_Long)16L * IFIX(digit_char_p(temp_1,
			FIX((SI_Long)16L)));
		if (NUM_LE(length_1,i))
		    goto end;
		else {
		    temp = CHARACTER_TO_CHAR(CHAR(string_1,i));
		    i = FIXNUM_ADD1(i);
		    temp_1 = CHAR_TO_CHARACTER(temp);
		}
		simple_or_wide_character = CODE_CHAR(FIX(temp_2 + 
			IFIX(digit_char_p(temp_1,FIX((SI_Long)16L)))));
	    }
	    else
		simple_or_wide_character = CHAR_TO_CHARACTER(c);
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
		temp_3 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_3;
	    }
	    goto next_loop;
	  end_loop:
	  end:;
	    g2int_reclaim_gensym_string(string_1);
	    result = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_base64_encoding_vector = UNBOUND;

/* CONVERT-TEXT-TO-BASE64-ENCODING */
Object g2int_convert_text_to_base64_encoding(text)
    Object text;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object length_1, c1, c2, c3, w, simple_or_wide_character, thing, temp;
    Object schar_arg_2, schar_new_value;
    SI_Long ab_loop_bind_, i, temp_1;
    char thing_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(59,1);
    current_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    length_1 = length(text);
	    ab_loop_bind_ = IFIX(length_1) - (SI_Long)2L;
	    i = (SI_Long)0L;
	    c1 = Nil;
	    c2 = Nil;
	    c3 = Nil;
	    w = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    c1 = CHAR_CODE(CHR(ICHAR(text,i)));
	    c2 = CHAR_CODE(CHR(ICHAR(text,i + (SI_Long)1L)));
	    c3 = CHAR_CODE(CHR(ICHAR(text,i + (SI_Long)2L)));
	    w = FIX((IFIX(c1) << (SI_Long)16L) + (IFIX(c2) << (SI_Long)8L) 
		    + IFIX(c3));
	    simple_or_wide_character = CHAR(G2int_base64_encoding_vector,
		    logand(FIX((SI_Long)63L),ash(w,FIX((SI_Long)-18L))));
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
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    simple_or_wide_character = CHAR(G2int_base64_encoding_vector,
		    logand(FIX((SI_Long)63L),ash(w,FIX((SI_Long)-12L))));
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
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    simple_or_wide_character = CHAR(G2int_base64_encoding_vector,
		    logand(FIX((SI_Long)63L),ash(w,FIX((SI_Long)-6L))));
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
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    simple_or_wide_character = CHAR(G2int_base64_encoding_vector,
		    logand(FIX((SI_Long)63L),ash(w,FIX((SI_Long)0L))));
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
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    i = i + (SI_Long)3L;
	    goto next_loop;
	  end_loop:
	    temp_1 = IFIX(length_1) - i;
	    if (! !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
		switch ((char)temp_1) {
		  case 0:
		    break;
		  case 1:
		    w = FIX(IFIX(CHAR_CODE(CHR(ICHAR(text,i)))) << 
			    (SI_Long)16L);
		    simple_or_wide_character = 
			    CHAR(G2int_base64_encoding_vector,
			    logand(FIX((SI_Long)63L),ash(w,
			    FIX((SI_Long)-18L))));
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = simple_or_wide_character;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = simple_or_wide_character;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    simple_or_wide_character = 
			    CHAR(G2int_base64_encoding_vector,
			    logand(FIX((SI_Long)63L),ash(w,
			    FIX((SI_Long)-12L))));
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = simple_or_wide_character;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = simple_or_wide_character;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = '=';
			g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) 
				? CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing_1 = '=';
			schar_new_value = 
				CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
				CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = '=';
			g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) 
				? CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing_1 = '=';
			schar_new_value = 
				CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
				CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    break;
		  case 2:
		    w = FIX((IFIX(CHAR_CODE(CHR(ICHAR(text,i)))) << 
			    (SI_Long)16L) + (IFIX(CHAR_CODE(CHR(ICHAR(text,
			    i + (SI_Long)1L)))) << (SI_Long)8L));
		    simple_or_wide_character = 
			    CHAR(G2int_base64_encoding_vector,
			    logand(FIX((SI_Long)63L),ash(w,
			    FIX((SI_Long)-18L))));
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = simple_or_wide_character;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = simple_or_wide_character;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    simple_or_wide_character = 
			    CHAR(G2int_base64_encoding_vector,
			    logand(FIX((SI_Long)63L),ash(w,
			    FIX((SI_Long)-12L))));
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = simple_or_wide_character;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = simple_or_wide_character;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    simple_or_wide_character = 
			    CHAR(G2int_base64_encoding_vector,
			    logand(FIX((SI_Long)63L),ash(w,
			    FIX((SI_Long)-6L))));
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = simple_or_wide_character;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing = simple_or_wide_character;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = '=';
			g2int_twrite_wide_character(CHARACTERP(CHR(thing_1)) 
				? CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp = G2int_current_gensym_string;
			schar_arg_2 = 
				G2int_fill_pointer_for_current_gensym_string;
			thing_1 = '=';
			schar_new_value = 
				CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
				CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
			SET_SCHAR(temp,schar_arg_2,schar_new_value);
			temp = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp;
		    }
		    break;
		  default:
		    break;
		}
	    result = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_alist_of_resources_tendered_by_g2 = UNBOUND;

/* INSTALL-TENDER-OF-RESOURCE */
Object g2int_install_tender_of_resource(index_1,pattern,method)
    Object index_1, pattern, method;
{
    Object compiled_method_qm, compiled_method, tail, entry, rest_1, i, i2;
    Object temp, new_entry;

    x_note_fn_call(59,2);
    pattern = g2int_copy_gensym_string(pattern);
    compiled_method_qm = g2int_compile_resource_method(method);
    if (compiled_method_qm)
	compiled_method = compiled_method_qm;
    else
	return VALUES_1(FIX((SI_Long)-1L));
    if ( !TRUEP(G2int_alist_of_resources_tendered_by_g2) || 
	    FIXNUM_LT(index_1,CAAR(G2int_alist_of_resources_tendered_by_g2)))
	G2int_alist_of_resources_tendered_by_g2 = 
		g2int_gensym_cons_1(g2int_gensym_list_3(index_1,pattern,
		compiled_method),G2int_alist_of_resources_tendered_by_g2);
    else if (G2int_alist_of_resources_tendered_by_g2) {
	tail = G2int_alist_of_resources_tendered_by_g2;
	entry = Nil;
	rest_1 = Nil;
	i = Nil;
	i2 = Nil;
      next_loop:
	if ( !TRUEP(tail))
	    goto end_loop;
	entry = CAR(tail);
	rest_1 = CDR(tail);
	i = CAR(entry);
	temp = CAR(rest_1);
	i2 = CAR(temp);
	if (FIXNUM_EQ(index_1,i)) {
	    g2int_reclaim_gensym_string(SECOND(entry));
	    g2int_reclaim_plist_tree_of_resource_buffer(THIRD(entry));
	    M_SECOND(entry) = pattern;
	    M_THIRD(entry) = compiled_method;
	    goto end;
	}
	if ( !TRUEP(rest_1) || FIXNUM_LT(index_1,i2)) {
	    new_entry = g2int_gensym_cons_1(g2int_gensym_list_3(index_1,
		    pattern,compiled_method),rest_1);
	    M_CDR(tail) = new_entry;
	    goto end;
	}
	tail = M_CDR(tail);
	goto next_loop;
      end_loop:
      end:;
    }
    return VALUES_1(FIX((SI_Long)0L));
}

static Object string_constant;     /* "call" */

static Object string_constant_1;   /* "cgi" */

static Object Kcgi;                /* :cgi */

static Object string_constant_2;   /* "url" */

static Object Kurl;                /* :url */

static Object string_constant_3;   /* "(" */

static Object string_constant_4;   /* ")" */

static Object Qg2int_handle_url_via_call_back_to_g2_function;  /* handle-url-via-call-back-to-g2-function */

static Object string_constant_5;   /* "serve from file system:" */

static Object Qg2int_handle_url_via_file_system;  /* handle-url-via-file-system */

static Object string_constant_6;   /* "serve internal status pages" */

static Object Qg2int_handle_url_via_internal_pages;  /* handle-url-via-internal-pages */

static Object string_constant_7;   /* "forward to proxy server" */

static Object Qg2int_handle_url_via_proxy_server;  /* handle-url-via-proxy-server */

/* COMPILE-RESOURCE-METHOD */
Object g2int_compile_resource_method(method)
    Object method;
{
    Object m, result_1, style, mark, current_left_of_parsing;
    Object current_right_of_parsing, routine_name, signature, filename_root;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp_1;
    char temp;
    Declare_special(6);

    x_note_fn_call(59,3);
    m = g2int_make_mark_into_new_empty_resource_buffer();
    result_1 = Nil;
    style = Nil;
    g2int_insert_text_at_mark(m,method);
    g2int_mark_tab(m,FIX((SI_Long)0L));
    mark = m;
    current_left_of_parsing = g2int_mark_copy(mark);
    PUSH_SPECIAL(G2int_current_left_of_parsing,current_left_of_parsing,5);
      current_right_of_parsing = g2int_mark_copy(mark);
      PUSH_SPECIAL(G2int_current_right_of_parsing,current_right_of_parsing,4);
	routine_name = Nil;
	signature = Nil;
	if (g2int_scan_text(string_constant) && 
		g2int_scan_one_or_more_spaces_and_tabs()) {
	    if (g2int_scan_text(string_constant_1))
		style = Kcgi;
	    else if (g2int_scan_text(string_constant_2))
		style = Kurl;
	    else
		style = Nil;
	    temp = TRUEP(style);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(g2int_scan_one_or_more_spaces_and_tabs()) : 
		TRUEP(Nil)) {
	    routine_name = g2int_scan_symbol();
	    temp = TRUEP(routine_name);
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? TRUEP(g2int_scan_zero_or_more_spaces_and_tabs()) : 
		TRUEP(Nil)) ? TRUEP(g2int_scan_text(string_constant_3)) : 
		TRUEP(Nil)) {
	    signature = g2int_scan_method_args(routine_name);
	    temp = TRUEP(signature);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(g2int_scan_text(string_constant_4)) : TRUEP(Nil)) {
	    result_1 = 
		    g2int_gensym_list_2(Qg2int_handle_url_via_call_back_to_g2_function,
		    g2int_gensym_list_2(Qquote,signature));
	    g2int_lgsi_rpc_declare_remote(routine_name,
		    FIXNUM_SUB1(length(signature)),FIX((SI_Long)0L));
	    POP_SPECIAL();
	    POP_SPECIAL();
	    goto end_done;
	}
	if (g2int_scan_text(string_constant_5)) {
	    g2int_scan_zero_or_more_spaces_and_tabs();
	    g2int_scan_over_filename();
	    filename_root = g2int_get_simple_text_from_last_scan();
	    current_gensym_string = 
		    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
	    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
	      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		      2);
		total_length_of_current_gensym_string = FIX((SI_Long)2048L);
		PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
			1);
		  current_twriting_output_type = Qg2int_gensym_string;
		  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			  0);
		    g2int_twrite_text_gensym_pt_to_i_ascii(filename_root);
		    temp_1 = g2int_copy_out_current_gensym_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    result_1 = 
		    g2int_gensym_list_2(Qg2int_handle_url_via_file_system,
		    temp_1);
	    g2int_reclaim_gensym_string(filename_root);
	    POP_SPECIAL();
	    POP_SPECIAL();
	    goto end_done;
	}
	if (g2int_scan_text(string_constant_6)) {
	    result_1 = 
		    g2int_gensym_cons_1(Qg2int_handle_url_via_internal_pages,
		    Nil);
	    POP_SPECIAL();
	    POP_SPECIAL();
	    goto end_done;
	}
	if (g2int_scan_text(string_constant_7))
	    result_1 = 
		    g2int_gensym_cons_1(Qg2int_handle_url_via_proxy_server,
		    Nil);
	g2int_mark_kill(G2int_current_left_of_parsing);
	g2int_mark_kill(G2int_current_right_of_parsing);
      POP_SPECIAL();
    POP_SPECIAL();
  end_done:
    g2int_reclaim_resource_buffer_of_mark(m);
    return VALUES_1(result_1);
}

static Object string_constant_8;   /* ":" */

static Object list_constant;       /* # */

static Object string_constant_9;   /* "," */

/* SCAN-METHOD-ARGS */
Object g2int_scan_method_args(routine_name)
    Object routine_name;
{
    Object result_1, arg_name, arg_type;

    x_note_fn_call(59,4);
    result_1 = g2int_gensym_cons_1(routine_name,Nil);
    arg_name = Nil;
    arg_type = Nil;
  next_loop:
    arg_name = Nil;
    arg_type = Nil;
    g2int_scan_zero_or_more_spaces_and_tabs();
    arg_name = g2int_scan_symbol();
    g2int_scan_zero_or_more_spaces_and_tabs();
    g2int_scan_text(string_constant_8);
    g2int_scan_zero_or_more_spaces_and_tabs();
    arg_type = g2int_scan_symbol();
    g2int_scan_zero_or_more_spaces_and_tabs();
    if ( !(arg_name && g2int_memq_function(arg_type,list_constant))) {
	g2int_reclaim_gensym_tree_1(result_1);
	return VALUES_1(Nil);
    }
    result_1 = g2int_gensym_cons_1(g2int_gensym_list_2(arg_name,arg_type),
	    result_1);
    if ( !TRUEP(g2int_scan_text(string_constant_9)))
	return nreverse(result_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MATCH-URL-AGAINST-TENDERED-RESOURCES */
Object g2int_match_url_against_tendered_resources(url_details)
    Object url_details;
{
    Object index_1, pattern, method, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(59,5);
    index_1 = Nil;
    pattern = Nil;
    method = Nil;
    ab_loop_list_ = G2int_alist_of_resources_tendered_by_g2;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    index_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    pattern = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    method = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (g2int_string_prefixeq(pattern,url_details))
	return VALUES_1(method);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STRING-PREFIX= */
Object g2int_string_prefixeq(prefix,string_1)
    Object prefix, string_1;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(59,6);
    if (FIXNUM_LE(length(prefix),length(string_1))) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(prefix));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !CHAR_EQ(CHR(ICHAR(prefix,i)),CHR(ICHAR(string_1,i))))
	    return VALUES_1(Nil);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_listener_socket = UNBOUND;

Object G2int_chain_of_available_listener_sockets = UNBOUND;

Object G2int_listener_socket_count = UNBOUND;

/* RECLAIM-LISTENER-SOCKET-1 */
Object g2int_reclaim_listener_socket_1(listener_socket)
    Object listener_socket;
{
    Object svref_new_value;

    x_note_fn_call(59,7);
    inline_note_reclaim_cons(listener_socket,Nil);
    svref_new_value = G2int_chain_of_available_listener_sockets;
    SVREF(listener_socket,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_listener_sockets = listener_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LISTENER-SOCKET */
Object g2int_reclaim_structure_for_listener_socket(listener_socket)
    Object listener_socket;
{
    x_note_fn_call(59,8);
    return g2int_reclaim_listener_socket_1(listener_socket);
}

static Object Qg2_defstruct_structure_name_listener_socket_g2_struct;  /* g2-defstruct-structure-name::listener-socket-g2-struct */

/* MAKE-PERMANENT-LISTENER-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_listener_socket_structure_internal()
{
    Object def_structure_listener_socket_variable;
    Object listener_socket_count_new_value;
    Object defstruct_g2_listener_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(59,9);
    def_structure_listener_socket_variable = Nil;
    listener_socket_count_new_value = FIXNUM_ADD1(G2int_listener_socket_count);
    G2int_listener_socket_count = listener_socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_listener_socket_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_listener_socket_variable = the_array;
	SVREF(defstruct_g2_listener_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_listener_socket_g2_struct;
	SVREF(defstruct_g2_listener_socket_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_listener_socket_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_listener_socket_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_listener_socket_variable,FIX((SI_Long)4L)) = Nil;
	def_structure_listener_socket_variable = 
		defstruct_g2_listener_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_listener_socket_variable);
}

static Object Kborn;               /* :born */

/* MAKE-LISTENER-SOCKET-1 */
Object g2int_make_listener_socket_1(port_number_of_listener)
    Object port_number_of_listener;
{
    Object def_structure_listener_socket_variable, svref_new_value;

    x_note_fn_call(59,10);
    def_structure_listener_socket_variable = 
	    G2int_chain_of_available_listener_sockets;
    if (def_structure_listener_socket_variable) {
	G2int_chain_of_available_listener_sockets = 
		ISVREF(def_structure_listener_socket_variable,(SI_Long)0L);
	SVREF(def_structure_listener_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_listener_socket_g2_struct;
    }
    else
	def_structure_listener_socket_variable = 
		g2int_make_permanent_listener_socket_structure_internal();
    inline_note_allocate_cons(def_structure_listener_socket_variable,Nil);
    SVREF(def_structure_listener_socket_variable,FIX((SI_Long)5L)) = 
	    port_number_of_listener;
    svref_new_value = G2int_current_thread;
    SVREF(def_structure_listener_socket_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_listener_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_listener_socket_variable,FIX((SI_Long)3L)) = Kborn;
    ISVREF(def_structure_listener_socket_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_listener_socket_variable);
}

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

static Object Qg2int_socket_listen;  /* socket-listen */

/* SOCKET-LISTEN */
Object g2int_socket_listen(listener_socket)
    Object listener_socket;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(59,11);
    gensymed_symbol = ISVREF(listener_socket,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_socket_listen,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_2(method,next_path,listener_socket);
}

/* M-SOCKET-LISTEN-LISTENER-SOCKET-1 */
Object g2int_m_socket_listen_listener_socket_1(path,listener_socket)
    Object path, listener_socket;
{
    int result_1;

    x_note_fn_call(59,12);
    result_1 = g2pvt_tcpip_listen(IFIX(ISVREF(listener_socket,(SI_Long)5L)));
    if (result_1 <= (SI_Long)0L)
	g2int_note_issue_with_socket(listener_socket,INT_TO_INTEGER(result_1));
    else
	g2int_socket_install(listener_socket,INT_TO_INTEGER(result_1));
    return VALUES_1(listener_socket);
}

/* SOCKET-ACCEPT? */
Object g2int_socket_acceptqm(listener_socket)
    Object listener_socket;
{
    Object client_socket;
    int result_1;

    x_note_fn_call(59,13);
    result_1 = g2ext_tcpip_accept_internals(IFIX(ISVREF(listener_socket,
	    (SI_Long)2L)));
    if ((SI_Long)0L < result_1) {
	client_socket = g2int_make_client_socket_1();
	g2int_socket_install(client_socket,INT_TO_INTEGER(result_1));
	return VALUES_1(client_socket);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_server_thread = UNBOUND;

Object G2int_chain_of_available_server_threads = UNBOUND;

Object G2int_server_thread_count = UNBOUND;

/* RECLAIM-SERVER-THREAD-1 */
Object g2int_reclaim_server_thread_1(server_thread)
    Object server_thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(59,14);
    inline_note_reclaim_cons(server_thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = server_thread;
    g2int_reclaim_sockets(ISVREF(server_thread,(SI_Long)11L));
    SVREF(server_thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(server_thread,(SI_Long)12L));
    SVREF(server_thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_server_threads;
    SVREF(server_thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_server_threads = server_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SERVER-THREAD */
Object g2int_reclaim_structure_for_server_thread(server_thread)
    Object server_thread;
{
    x_note_fn_call(59,15);
    return g2int_reclaim_server_thread_1(server_thread);
}

static Object Qg2_defstruct_structure_name_server_thread_g2_struct;  /* g2-defstruct-structure-name::server-thread-g2-struct */

/* MAKE-PERMANENT-SERVER-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_server_thread_structure_internal()
{
    Object def_structure_server_thread_variable, temp;
    Object defstruct_g2_server_thread_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(59,16);
    def_structure_server_thread_variable = Nil;
    temp = FIXNUM_ADD1(G2int_server_thread_count);
    G2int_server_thread_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_server_thread_variable = Nil;
	gensymed_symbol_1 = (SI_Long)19L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_server_thread_variable = the_array;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_server_thread_g2_struct;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_server_thread_variable,FIX((SI_Long)16L)) = Nil;
	def_structure_server_thread_variable = 
		defstruct_g2_server_thread_variable;
	SVREF(def_structure_server_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_server_thread_variable,FIX((SI_Long)5L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_server_threads;
	SVREF(def_structure_server_thread_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_server_threads = 
		def_structure_server_thread_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_server_thread_variable);
}

static Object Knew;                /* :new */

static Object Kallocated;          /* :allocated */

static Object Qg2int_null_thread_contour_wrapper;  /* null-thread-contour-wrapper */

/* MAKE-SERVER-THREAD-1 */
Object g2int_make_server_thread_1()
{
    Object def_structure_server_thread_variable, svref_new_value;

    x_note_fn_call(59,17);
    def_structure_server_thread_variable = 
	    G2int_chain_of_available_server_threads;
    if (def_structure_server_thread_variable) {
	G2int_chain_of_available_server_threads = 
		ISVREF(def_structure_server_thread_variable,(SI_Long)0L);
	SVREF(def_structure_server_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_server_thread_g2_struct;
    }
    else
	def_structure_server_thread_variable = 
		g2int_make_permanent_server_thread_structure_internal();
    inline_note_allocate_cons(def_structure_server_thread_variable,Nil);
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)8L)) = Kallocated;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_server_thread_variable,(SI_Long)10L) = 
	    FIX((SI_Long)100L);
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)14L)) = 
	    svref_new_value;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_server_thread_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_server_thread_variable);
}

/* M-THREAD-FEED-TRACE-SERVER-THREAD-1 */
Object g2int_m_thread_feed_trace_server_thread_1(path,server_thread)
    Object path, server_thread;
{
    x_note_fn_call(59,18);
    return format((SI_Long)5L,T,"~&Feeding the server at ~S (~S clients)",
	    server_thread,ISVREF(server_thread,(SI_Long)17L),
	    length(ISVREF(server_thread,(SI_Long)6L)));
}

Object G2int_the_http_server_threadqm = UNBOUND;

static Object string_constant_10;  /* "Launching new HTTP server at ~D." */

static Object string_constant_11;  /* "but first shutting down old HTTP server." */

static Object Qg2int_http_server;  /* http-server */

static Object Krunnable;           /* :runnable */

static Object Kinitializing;       /* :initializing */

static Object Kstarted;            /* :started */

/* STARTUP-HTTP-SERVER */
Object g2int_startup_http_server(port_number)
    Object port_number;
{
    Object new_thread_instance, svref_new_value, thread, current_thread;
    Declare_special(1);

    x_note_fn_call(59,19);
    g2int_notify_user_at_console(2,string_constant_10,port_number);
    if (G2int_the_http_server_threadqm) {
	g2int_notify_user_at_console(1,string_constant_11);
	g2int_thread_kill(G2int_the_http_server_threadqm);
    }
    new_thread_instance = g2int_make_server_thread_1();
    SVREF(new_thread_instance,FIX((SI_Long)2L)) = Qg2int_http_server;
    SVREF(new_thread_instance,FIX((SI_Long)17L)) = port_number;
    svref_new_value = G2int_current_icp_socket;
    SVREF(new_thread_instance,FIX((SI_Long)18L)) = svref_new_value;
    G2int_the_http_server_threadqm = new_thread_instance;
    thread = new_thread_instance;
    g2int_thread_initialize(thread);
    current_thread = thread;
    PUSH_SPECIAL(G2int_current_thread,current_thread,0);
      g2int_listen_for_server_requests(Nil);
      SVREF(thread,FIX((SI_Long)7L)) = Krunnable;
      SVREF(thread,FIX((SI_Long)8L)) = Kinitializing;
      g2int_give_thread_quantum();
      if (EQ(ISVREF(thread,(SI_Long)7L),Krunnable)) {
	  SVREF(thread,FIX((SI_Long)7L)) = Krunnable;
	  SVREF(thread,FIX((SI_Long)8L)) = Kstarted;
      }
    POP_SPECIAL();
    return VALUES_1(thread);
}

static Object Kquantum_in_progress;  /* :quantum-in-progress */

static Object Kinitialize;         /* :initialize */

static Object string_constant_12;  /* "Started HTTP server (port ~D)." */

static Object Kcontinuation_taken_care_of;  /* :continuation-taken-care-of */

static Object Knot_runnable;       /* :not-runnable */

static Object Kio_wait;            /* :io-wait */

static Object Kcheck_for_clients;  /* :check-for-clients */

static Object Kcleanup;            /* :cleanup */

static Object string_constant_13;  /* "Shutdown HTTP Server (port ~D)." */

static Object Kshutdown_server;    /* :shutdown-server */

static Object Krunning;            /* :running */

static Object string_constant_14;  /* "Problem with HTTP Server (issue: ~S)" */

/* MT-LISTEN-FOR-SERVER-REQUESTS */
Object g2int_mt_listen_for_server_requests()
{
    Object program_counter, pending_continuation, frame, listener_socket;
    Object svref_arg_1, client_socket;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(59,20);
    if (PUSH_AREA(Dynamic_area,0)) {
	program_counter = ISVREF(G2int_current_thread,(SI_Long)16L);
	pending_continuation = Nil;
	frame = ISVREF(G2int_current_thread,(SI_Long)13L);
	listener_socket = ISVREF(frame,(SI_Long)5L);
	svref_arg_1 = G2int_current_thread;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kquantum_in_progress;
	if (EQ(program_counter,Kinitialize)) {
	    g2int_notify_user_at_console(2,string_constant_12,
		    ISVREF(G2int_current_thread,(SI_Long)17L));
	    G2int_alist_of_resources_tendered_by_g2 = Nil;
	    listener_socket = 
		    g2int_socket_listen(g2int_make_listener_socket_1(ISVREF(G2int_current_thread,
		    (SI_Long)17L)));
	    if (ISVREF(listener_socket,(SI_Long)3L)) {
		pending_continuation = Kcontinuation_taken_care_of;
		g2int_thread_exit_1();
	    }
	    else {
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)7L)) = Knot_runnable;
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = Kio_wait;
		pending_continuation = Kcheck_for_clients;
	    }
	}
	else if (EQ(program_counter,Kcleanup)) {
	    g2int_notify_user_at_console(2,string_constant_13,
		    ISVREF(G2int_current_thread,(SI_Long)17L));
	    G2int_alist_of_resources_tendered_by_g2 = Nil;
	    if (listener_socket) {
		g2int_socket_close_it(listener_socket);
		g2int_reclaim_listener_socket_1(listener_socket);
	    }
	    G2int_the_http_server_threadqm = Nil;
	}
	else if (EQ(program_counter,Kcheck_for_clients)) {
	    if (ISVREF(listener_socket,(SI_Long)3L))
		pending_continuation = Kshutdown_server;
	    else if (EQ(Krunning,G2int_the_state_of_g2)) {
		client_socket = Nil;
	      next_loop:
		client_socket = g2int_socket_acceptqm(listener_socket);
		if ( !TRUEP(client_socket))
		    goto end_loop;
		g2int_launch_http_client(client_socket);
		goto next_loop;
	      end_loop:;
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)7L)) = Knot_runnable;
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = Kio_wait;
		pending_continuation = Kcheck_for_clients;
	    }
	    else {
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)7L)) = Knot_runnable;
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = Kio_wait;
		pending_continuation = Kcheck_for_clients;
	    }
	}
	else if (EQ(program_counter,Kshutdown_server)) {
	    if (ISVREF(listener_socket,(SI_Long)3L))
		g2int_notify_user_at_console(2,string_constant_14,
			ISVREF(listener_socket,(SI_Long)3L));
	    pending_continuation = Kcontinuation_taken_care_of;
	    g2int_thread_exit_1();
	}
	else
	    error((SI_Long)1L,"No handler for this continuation.");
	SVREF(frame,FIX((SI_Long)5L)) = listener_socket;
	if ( !TRUEP(pending_continuation) &&  !EQ(Kcleanup,program_counter))
	    error((SI_Long)1L,"No continuation.");
	if ( !EQ(Kcontinuation_taken_care_of,pending_continuation)) {
	    svref_arg_1 = G2int_current_thread;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    pending_continuation);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_AREA(0);
    return result;
}

static Object Qg2int_mt_listen_for_server_requests;  /* mt-listen-for-server-requests */

/* LISTEN-FOR-SERVER-REQUESTS */
Object g2int_listen_for_server_requests(return_continuation)
    Object return_continuation;
{
    Object frame, listener_socket;

    x_note_fn_call(59,21);
    frame = g2int_prolog_thread_function(return_continuation,
	    SYMBOL_FUNCTION(Qg2int_mt_listen_for_server_requests),
	    FIX((SI_Long)6L));
    listener_socket = Nil;
    return VALUES_1(SVREF(frame,FIX((SI_Long)5L)) = listener_socket);
}

Object G2int_charset_name_to_http_header_charset = UNBOUND;

/* MAP-CHARSET-NAME-TO-CHARSET-STRING */
Object g2int_map_charset_name_to_charset_string(charset_name)
    Object charset_name;
{
    Object temp, l, ab_loop_list_;

    x_note_fn_call(59,22);
    if (SYMBOLP(charset_name)) {
	temp = g2int_assq_function(charset_name,
		G2int_charset_name_to_http_header_charset);
	return VALUES_1(SECOND(temp));
    }
    else {
	l = Nil;
	ab_loop_list_ = G2int_charset_name_to_http_header_charset;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	l = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_equal(2,SECOND(l),charset_name))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(SECOND(l));
	return VALUES_1(Qnil);
    }
}

/* MAP-CHARSET-NAME-TO-TRANSCODING-PURPOSE */
Object g2int_map_charset_name_to_transcoding_purpose(charset_name)
    Object charset_name;
{
    Object temp, l, ab_loop_list_;

    x_note_fn_call(59,23);
    if (SYMBOLP(charset_name)) {
	temp = g2int_assq_function(charset_name,
		G2int_charset_name_to_http_header_charset);
	return VALUES_1(THIRD(temp));
    }
    else {
	l = Nil;
	ab_loop_list_ = G2int_charset_name_to_http_header_charset;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	l = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_equal(2,SECOND(l),charset_name))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(THIRD(l));
	return VALUES_1(Qnil);
    }
}

static Object Qg2int_invalid_charset_name;  /* invalid-charset-name */

static Object string_constant_15;  /* "Unrecognized charset name." */

/* MAP-AND-VALIDATE-CHARSET-NAME */
Object g2int_map_and_validate_charset_name(charset_name)
    Object charset_name;
{
    Object temp;

    x_note_fn_call(59,24);
    temp = g2int_map_charset_name_to_charset_string(charset_name);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_signal_from_rpc(Qg2int_invalid_charset_name,
		string_constant_15);
}

Object G2int_default_default_http_header_charset_name = UNBOUND;

Object G2int_default_http_header_charset_name = UNBOUND;

static Object Qg2int_default;      /* default */

static Object string_constant_16;  /* "Note: ~A is not valid for the -default-charset option. ~
				    *                ~%Legal charset names are: ~(~L,-~)."
				    */

static Object string_constant_17;  /* "Default charset for Gensym Weblink: ~a" */

/* COMMAND-LINE-PROCESS-DEFAULT-CHARSET */
Object g2int_command_line_process_default_charset(value_qm)
    Object value_qm;
{
    Object name_maybe, name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, names;

    x_note_fn_call(59,25);
    if (value_qm) {
	if (SYMBOLP(value_qm))
	    name_maybe = value_qm;
	else if (STRINGP(value_qm))
	    name_maybe = g2int_intern_gensym_string(1,string_upcase(1,
		    value_qm));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value_qm) != (SI_Long)0L)
	    name_maybe = g2int_intern_text_string(1,
		    g2int_string_upcasew(value_qm));
	else
	    name_maybe = Qnil;
	if (EQ(name_maybe,Qg2int_default))
	    name_maybe = G2int_default_default_http_header_charset_name;
	else if ( 
		    !TRUEP(g2int_map_charset_name_to_charset_string(name_maybe))) {
	    name = Nil;
	    ab_loop_list_ = G2int_charset_name_to_http_header_charset;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = g2int_gensym_cons_1(name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    names = ab_loopvar_;
	    goto end;
	    names = Qnil;
	  end:;
	    g2int_notify_user_at_console(3,string_constant_16,name_maybe,
		    names);
	    g2int_reclaim_gensym_list_1(names);
	    name_maybe = G2int_default_default_http_header_charset_name;
	}
	G2int_default_http_header_charset_name = name_maybe;
	g2int_notify_user_at_console(2,string_constant_17,
		G2int_default_http_header_charset_name);
	return VALUES_1(name_maybe);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qg2int_default_charset;  /* default-charset */

static Object Qg2int_command_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEFAULT-CHARSET */
Object g2int_get_command_line_plist_element_for_default_charset()
{
    Object value_qm, temp;

    x_note_fn_call(59,26);
    value_qm = g2int_get_command_line_keyword_argument(1,array_constant);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_default_charset),
	    Qg2int_command_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

Object G2int_the_type_description_of_http_client_thread = UNBOUND;

Object G2int_chain_of_available_http_client_threads = UNBOUND;

Object G2int_http_client_thread_count = UNBOUND;

/* RECLAIM-HTTP-CLIENT-THREAD-1 */
Object g2int_reclaim_http_client_thread_1(http_client_thread)
    Object http_client_thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(59,27);
    inline_note_reclaim_cons(http_client_thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = http_client_thread;
    g2int_reclaim_sockets(ISVREF(http_client_thread,(SI_Long)11L));
    SVREF(http_client_thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(http_client_thread,(SI_Long)12L));
    SVREF(http_client_thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_http_client_threads;
    SVREF(http_client_thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_http_client_threads = http_client_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-HTTP-CLIENT-THREAD */
Object g2int_reclaim_structure_for_http_client_thread(http_client_thread)
    Object http_client_thread;
{
    x_note_fn_call(59,28);
    return g2int_reclaim_http_client_thread_1(http_client_thread);
}

static Object Qg2_defstruct_structure_name_http_client_thread_g2_struct;  /* g2-defstruct-structure-name::http-client-thread-g2-struct */

/* MAKE-PERMANENT-HTTP-CLIENT-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_http_client_thread_structure_internal()
{
    Object def_structure_http_client_thread_variable, temp;
    Object defstruct_g2_http_client_thread_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(59,29);
    def_structure_http_client_thread_variable = Nil;
    temp = FIXNUM_ADD1(G2int_http_client_thread_count);
    G2int_http_client_thread_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_http_client_thread_variable = Nil;
	gensymed_symbol_1 = (SI_Long)24L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_http_client_thread_variable = the_array;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_http_client_thread_g2_struct;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)10L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)11L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)12L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)13L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)14L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)15L)) 
		= Nil;
	SVREF(defstruct_g2_http_client_thread_variable,FIX((SI_Long)16L)) 
		= Nil;
	def_structure_http_client_thread_variable = 
		defstruct_g2_http_client_thread_variable;
	SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)5L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_http_client_threads;
	SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)0L)) 
		= temp;
	G2int_chain_of_available_http_client_threads = 
		def_structure_http_client_thread_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_http_client_thread_variable);
}

static Object Kpending;            /* :pending */

/* MAKE-HTTP-CLIENT-THREAD-1-1 */
Object g2int_make_http_client_thread_1_1()
{
    Object def_structure_http_client_thread_variable, svref_new_value;

    x_note_fn_call(59,30);
    def_structure_http_client_thread_variable = 
	    G2int_chain_of_available_http_client_threads;
    if (def_structure_http_client_thread_variable) {
	G2int_chain_of_available_http_client_threads = 
		ISVREF(def_structure_http_client_thread_variable,(SI_Long)0L);
	SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_http_client_thread_g2_struct;
    }
    else
	def_structure_http_client_thread_variable = 
		g2int_make_permanent_http_client_thread_structure_internal();
    inline_note_allocate_cons(def_structure_http_client_thread_variable,Nil);
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)8L)) = 
	    Kallocated;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_http_client_thread_variable,(SI_Long)10L) = 
	    FIX((SI_Long)100L);
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)14L)) = 
	    svref_new_value;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)20L)) = 
	    Kpending;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)22L)) = Nil;
    svref_new_value = G2int_default_http_header_charset_name;
    SVREF(def_structure_http_client_thread_variable,FIX((SI_Long)23L)) = 
	    svref_new_value;
    return VALUES_1(def_structure_http_client_thread_variable);
}

static Object string_constant_18;  /* "MIME-version" */

static Object string_constant_19;  /* "1.0" */

/* MAKE-HTTP-CLIENT-THREAD */
Object g2int_make_http_client_thread()
{
    Object thread;

    x_note_fn_call(59,31);
    thread = g2int_make_http_client_thread_1_1();
    g2int_add_message_header_field(thread,string_constant_18,
	    string_constant_19);
    return VALUES_1(thread);
}

/* M-THREAD-FEED-TRACE-HTTP-CLIENT-THREAD-1 */
Object g2int_m_thread_feed_trace_http_client_thread_1(path,http_client_thread)
    Object path, http_client_thread;
{
    x_note_fn_call(59,32);
    return format((SI_Long)3L,T,"~&Feeding the http client ~S",
	    http_client_thread);
}

static Object Kcollect_first_line_of_query;  /* :collect-first-line-of-query */

static Object Kbad;                /* :bad */

static Object string_constant_20;  /* "Ignoring malformed request." */

static Object Kwrap_up;            /* :wrap-up */

static Object Kcollect_remainder_of_query;  /* :collect-remainder-of-query */

static Object string_constant_21;  /* "Incomplete request." */

static Object Kdone;               /* :done */

static Object Kexecute_query;      /* :execute-query */

static Object Kmalformed_request;  /* :malformed-request */

static Object Kbackward;           /* :backward */

static Object Kfail;               /* :fail */

static Object Kfinishing_passing_data;  /* :finishing-passing-data */

static Object Keval_form;          /* :eval-form */

/* MT-SERVE-HTTP-CLIENT */
Object g2int_mt_serve_http_client()
{
    Object program_counter, pending_continuation, frame, input_mark;
    Object output_mark, reply_insert_mark, reply_send_mark, parse_state;
    Object url_qm, svref_arg_1, status, first_line_status, temp, client_socket;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(59,33);
    if (PUSH_AREA(Dynamic_area,0)) {
	program_counter = ISVREF(G2int_current_thread,(SI_Long)16L);
	pending_continuation = Nil;
	frame = ISVREF(G2int_current_thread,(SI_Long)13L);
	input_mark = ISVREF(frame,(SI_Long)5L);
	output_mark = ISVREF(frame,(SI_Long)6L);
	reply_insert_mark = ISVREF(frame,(SI_Long)7L);
	reply_send_mark = ISVREF(frame,(SI_Long)8L);
	parse_state = ISVREF(frame,(SI_Long)9L);
	url_qm = ISVREF(frame,(SI_Long)10L);
	svref_arg_1 = G2int_current_thread;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kquantum_in_progress;
	if (EQ(program_counter,Kinitialize)) {
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)18L)) = input_mark;
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)19L)) = output_mark;
	    pending_continuation = Kcollect_first_line_of_query;
	}
	else if (EQ(program_counter,Kcleanup)) {
	    g2int_reclaim_resource_buffer_of_mark(input_mark);
	    g2int_socket_close_it(ISVREF(G2int_current_thread,(SI_Long)17L));
	    g2int_reclaim_client_socket_1(ISVREF(G2int_current_thread,
		    (SI_Long)17L));
	    g2int_reclaim_gensym_tree_with_text_strings(ISVREF(G2int_current_thread,
		    (SI_Long)22L));
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)22L)) = Nil;
	    if (url_qm)
		g2int_reclaim_gensym_string(url_qm);
	}
	else if (EQ(program_counter,Kcollect_first_line_of_query)) {
	    status = g2int_read_query_from_current_socket(input_mark);
	    first_line_status =  !((SI_Long)0L == IFIX(status)) ? 
		    g2int_status_of_first_line_of_query(output_mark) : Nil;
	    if (EQ(first_line_status,Kbad)) {
		g2int_notify_user_at_console(1,string_constant_20);
		pending_continuation = Kwrap_up;
	    }
	    else if (EQ(first_line_status,T)) {
		parse_state = g2int_advance_http_query_parsing(output_mark,
			parse_state);
		pending_continuation = Kcollect_remainder_of_query;
	    }
	    else if (EQ(status,FIX((SI_Long)-1L))) {
		g2int_notify_user_at_console(1,string_constant_21);
		pending_continuation = Kwrap_up;
	    }
	    else if (EQ(first_line_status,Nil))
		pending_continuation = Kcollect_first_line_of_query;
	}
	else if (EQ(program_counter,Kcollect_remainder_of_query)) {
	    status = g2int_read_query_from_current_socket(input_mark);
	    if ((SI_Long)0L < IFIX(status))
		parse_state = g2int_advance_http_query_parsing(output_mark,
			parse_state);
	    if (EQ(parse_state,Kdone) || (SI_Long)-1L == IFIX(status))
		pending_continuation = Kexecute_query;
	    else if (EQ(parse_state,Kmalformed_request)) {
		g2int_notify_user_at_console(1,string_constant_20);
		pending_continuation = Kwrap_up;
	    }
	    else
		pending_continuation = Kcollect_remainder_of_query;
	}
	else if (EQ(program_counter,Kexecute_query)) {
	    reply_insert_mark = g2int_mark_copy(input_mark);
	    reply_send_mark = g2int_mark_copy(input_mark);
	    g2int_mark_direction(reply_send_mark,Kbackward);
	    temp = g2int_setup_to_do_query(reply_insert_mark);
	    if (EQ(temp,Kfail))
		pending_continuation = Kfinishing_passing_data;
	    else if (EQ(temp,Keval_form)) {
		g2int_eval_form_to_obtain_url(Kfinishing_passing_data);
		pending_continuation = Kcontinuation_taken_care_of;
	    }
	    else
		pending_continuation = Kwrap_up;
	}
	else if (EQ(program_counter,Kfinishing_passing_data)) {
	    client_socket = ISVREF(G2int_current_thread,(SI_Long)17L);
	    if ( !(ISVREF(client_socket,(SI_Long)3L) || 
		    g2int_mark_eq(output_mark,input_mark)))
		g2int_socket_write_region(client_socket,output_mark,
			input_mark);
	    g2int_socket_poll_status(ISVREF(G2int_current_thread,
		    (SI_Long)17L));
	    if (ISVREF(client_socket,(SI_Long)3L) || 
		    g2int_mark_eq(output_mark,input_mark))
		pending_continuation = Kwrap_up;
	    else
		pending_continuation = Kfinishing_passing_data;
	}
	else if (EQ(program_counter,Kwrap_up)) {
	    pending_continuation = Kcontinuation_taken_care_of;
	    g2int_thread_exit_1();
	}
	else
	    error((SI_Long)1L,"No handler for this continuation.");
	SVREF(frame,FIX((SI_Long)5L)) = input_mark;
	SVREF(frame,FIX((SI_Long)6L)) = output_mark;
	SVREF(frame,FIX((SI_Long)7L)) = reply_insert_mark;
	SVREF(frame,FIX((SI_Long)8L)) = reply_send_mark;
	SVREF(frame,FIX((SI_Long)9L)) = parse_state;
	SVREF(frame,FIX((SI_Long)10L)) = url_qm;
	if ( !TRUEP(pending_continuation) &&  !EQ(Kcleanup,program_counter))
	    error((SI_Long)1L,"No continuation.");
	if ( !EQ(Kcontinuation_taken_care_of,pending_continuation)) {
	    svref_arg_1 = G2int_current_thread;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    pending_continuation);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_AREA(0);
    return result;
}

static Object Qg2int_mt_serve_http_client;  /* mt-serve-http-client */

/* SERVE-HTTP-CLIENT */
Object g2int_serve_http_client(return_continuation)
    Object return_continuation;
{
    Object frame, input_mark, output_mark_1, output_mark, reply_insert_mark;
    Object reply_send_mark, parse_state, url_qm;

    x_note_fn_call(59,34);
    frame = g2int_prolog_thread_function(return_continuation,
	    SYMBOL_FUNCTION(Qg2int_mt_serve_http_client),FIX((SI_Long)11L));
    input_mark = g2int_make_mark_into_new_empty_resource_buffer();
    output_mark_1 = g2int_mark_copy(input_mark);
    output_mark = g2int_mark_direction(output_mark_1,Kbackward);
    reply_insert_mark = Nil;
    reply_send_mark = Nil;
    parse_state = Kstart;
    url_qm = Nil;
    SVREF(frame,FIX((SI_Long)5L)) = input_mark;
    SVREF(frame,FIX((SI_Long)6L)) = output_mark;
    SVREF(frame,FIX((SI_Long)7L)) = reply_insert_mark;
    SVREF(frame,FIX((SI_Long)8L)) = reply_send_mark;
    SVREF(frame,FIX((SI_Long)9L)) = parse_state;
    return VALUES_1(SVREF(frame,FIX((SI_Long)10L)) = url_qm);
}

static Object Keof;                /* :eof */

/* READ-QUERY-FROM-CURRENT-SOCKET */
Object g2int_read_query_from_current_socket(input_mark)
    Object input_mark;
{
    Object socket_1, result_1, data_or_eof;

    x_note_fn_call(59,35);
    socket_1 = ISVREF(G2int_current_thread,(SI_Long)17L);
    result_1 = FIX((SI_Long)0L);
    if (g2int_socket_data_available_p(socket_1)) {
	data_or_eof = g2int_socket_read_string(socket_1);
	if (EQ(data_or_eof,Keof))
	    result_1 = FIX((SI_Long)-1L);
	else {
	    g2int_insert_text_at_mark(input_mark,data_or_eof);
	    result_1 = length(data_or_eof);
	    g2int_reclaim_gensym_string(data_or_eof);
	}
    }
    return VALUES_1(result_1);
}

Object G2int_count_of_number_of_http_clients = UNBOUND;

static Object Qg2int_http_client;  /* http-client */

/* LAUNCH-HTTP-CLIENT */
Object g2int_launch_http_client(client_socket)
    Object client_socket;
{
    Object count_of_number_of_http_clients_new_value, thread, current_thread;
    Declare_special(1);

    x_note_fn_call(59,36);
    count_of_number_of_http_clients_new_value = 
	    FIXNUM_ADD1(G2int_count_of_number_of_http_clients);
    G2int_count_of_number_of_http_clients = 
	    count_of_number_of_http_clients_new_value;
    thread = g2int_make_http_client_thread();
    SVREF(thread,FIX((SI_Long)2L)) = Qg2int_http_client;
    SVREF(thread,FIX((SI_Long)17L)) = client_socket;
    g2int_thread_initialize(thread);
    current_thread = thread;
    PUSH_SPECIAL(G2int_current_thread,current_thread,0);
      g2int_serve_http_client(Nil);
      SVREF(thread,FIX((SI_Long)7L)) = Krunnable;
      SVREF(thread,FIX((SI_Long)8L)) = Kinitializing;
      g2int_give_thread_quantum();
      if (EQ(ISVREF(thread,(SI_Long)7L),Krunnable)) {
	  SVREF(thread,FIX((SI_Long)7L)) = Krunnable;
	  SVREF(thread,FIX((SI_Long)8L)) = Kstarted;
      }
    POP_SPECIAL();
    return VALUES_1(thread);
}

static Object string_constant_22;  /* " ??" */

/* STATUS-OF-FIRST-LINE-OF-QUERY */
Object g2int_status_of_first_line_of_query(parsing_mark)
    Object parsing_mark;
{
    Object mark, current_left_of_parsing, current_right_of_parsing, temp;
    Object next_break_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(59,37);
    mark = parsing_mark;
    current_left_of_parsing = g2int_mark_copy(mark);
    PUSH_SPECIAL(G2int_current_left_of_parsing,current_left_of_parsing,1);
      current_right_of_parsing = g2int_mark_copy(mark);
      PUSH_SPECIAL(G2int_current_right_of_parsing,current_right_of_parsing,0);
	if ( !(g2int_scan_upto_character(CHR(' ')) && 
		g2int_scan_one_or_more_spaces_and_tabs() && 
		g2int_scan_upto_character(CHR(' ')) && 
		g2int_scan_one_or_more_spaces_and_tabs())) {
	    temp = Nil;
	    goto end_validate;
	}
	next_break_qm = g2int_scan_upto_member_of_bag(string_constant_22);
	if (EQ(next_break_qm,CHR('\r'))) {
	    temp = T;
	    goto end_validate;
	}
	else if ( !TRUEP(next_break_qm)) {
	    temp = Nil;
	    goto end_validate;
	}
	else {
	    temp = Kbad;
	    goto end_validate;
	}
      end_validate:
	g2int_mark_kill(G2int_current_left_of_parsing);
	g2int_mark_kill(G2int_current_right_of_parsing);
	result = VALUES_1(temp);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ADVANCE-HTTP-QUERY-PARSING */
Object g2int_advance_http_query_parsing(parsing_mark,parse_state)
    Object parsing_mark, parse_state;
{
    Object from_state, next_state;

    x_note_fn_call(59,38);
    from_state = parse_state;
    next_state = Nil;
  next_loop:
    next_state = g2int_advance_http_query_parsing_1(parsing_mark,from_state);
    if (EQ(Kdone,next_state) || EQ(from_state,next_state) || 
	    EQ(Kmalformed_request,next_state))
	goto end_loop;
    from_state = next_state;
    goto next_loop;
  end_loop:
    return VALUES_1(next_state);
    return VALUES_1(Qnil);
}

static Object Qg2int_left_edge_of_mime_headers;  /* left-edge-of-mime-headers */

static Object Qg2int_right_edge_of_mime_headers;  /* right-edge-of-mime-headers */

static Object string_constant_23;  /* "/" */

static Object string_constant_24;  /* "HTTP/" */

static Object string_constant_25;  /* "." */

static Object Qg2int_url_details_of_request;  /* url-details-of-request */

static Object Qg2int_verb_of_request;  /* verb-of-request */

static Object Qg2int_protocol_of_request;  /* protocol-of-request */

static Object Krequest_header_fields;  /* :request-header-fields */

/* ADVANCE-HTTP-QUERY-PARSING-1 */
Object g2int_advance_http_query_parsing_1(parsing_mark,parse_state)
    Object parsing_mark, parse_state;
{
    Object mark, current_left_of_parsing, current_right_of_parsing, verb;
    Object url_details, major_protocol_version, minor_protocol_version, i_qm;
    Object temp;
    Declare_special(2);

    x_note_fn_call(59,39);
    mark = parsing_mark;
    current_left_of_parsing = g2int_mark_copy(mark);
    PUSH_SPECIAL(G2int_current_left_of_parsing,current_left_of_parsing,1);
      current_right_of_parsing = g2int_mark_copy(mark);
      PUSH_SPECIAL(G2int_current_right_of_parsing,current_right_of_parsing,0);
	if (EQ(parse_state,Kstart)) {
	    g2int_set_property_of_buffer(parsing_mark,
		    Qg2int_left_edge_of_mime_headers,
		    g2int_mark_copy(parsing_mark));
	    g2int_set_property_of_buffer(parsing_mark,
		    Qg2int_right_edge_of_mime_headers,
		    g2int_mark_copy(parsing_mark));
	    verb = Nil;
	    url_details = Nil;
	    major_protocol_version = FIX((SI_Long)0L);
	    minor_protocol_version = FIX((SI_Long)9L);
	    if ( !TRUEP(g2int_scan_upto_character(CHR(' ')))) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    verb = g2int_get_simple_text_from_last_scan();
	    if ( !TRUEP(g2int_scan_one_or_more_spaces_and_tabs())) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    if ( !TRUEP(g2int_scan_text(string_constant_23))) {
		if (IFIX(g2int_characters_available_for_parsing()) < 
			(SI_Long)1L) {
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_giveup;
		}
		else {
		    parse_state = Kmalformed_request;
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_giveup;
		}
	    }
	    if ( !TRUEP(g2int_scan_upto_character(CHR(' ')))) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    url_details = g2int_get_simple_text_from_last_scan();
	    if ( !TRUEP(g2int_scan_one_or_more_spaces_and_tabs())) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    if ( !TRUEP(g2int_scan_text(string_constant_24))) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    i_qm = g2int_scan_integer();
	    if ( !TRUEP(i_qm)) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    major_protocol_version = i_qm;
	    if ( !TRUEP(g2int_scan_text(string_constant_25))) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    i_qm = g2int_scan_integer();
	    if ( !TRUEP(i_qm)) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    minor_protocol_version = i_qm;
	    g2int_set_property_of_buffer(parsing_mark,
		    Qg2int_url_details_of_request,url_details);
	    g2int_set_property_of_buffer(parsing_mark,
		    Qg2int_verb_of_request,verb);
	    g2int_set_property_of_buffer(parsing_mark,
		    Qg2int_protocol_of_request,FIX((SI_Long)1000L * 
		    IFIX(major_protocol_version) + 
		    IFIX(minor_protocol_version)));
	    if ( !TRUEP(g2int_scan_to_beginning_of_next_line())) {
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_giveup;
	    }
	    g2int_mark_set(parsing_mark,G2int_current_right_of_parsing);
	    g2int_mark_set(g2int_get_property_of_buffer(parsing_mark,
		    Qg2int_left_edge_of_mime_headers),parsing_mark);
	    g2int_mark_set(g2int_get_property_of_buffer(parsing_mark,
		    Qg2int_right_edge_of_mime_headers),parsing_mark);
	    if (EQ(major_protocol_version,FIX((SI_Long)0L)))
		parse_state = Kdone;
	    else
		parse_state = Krequest_header_fields;
	}
	else if (EQ(parse_state,Krequest_header_fields)) {
	  next_loop:
	    if ( !TRUEP(g2int_scan_to_end_of_line())) {
		parse_state = Krequest_header_fields;
		goto end;
	    }
	    else {
		temp = g2int_get_property_of_buffer(parsing_mark,
			Qg2int_right_edge_of_mime_headers);
		g2int_mark_set(temp,G2int_current_right_of_parsing);
		g2int_undo_last_scan();
		if ( !TRUEP(g2int_scan_header_line(parsing_mark))) {
		    if (g2int_scan_blank_line()) {
			parse_state = Kdone;
			goto end;
		    }
		    else {
			parse_state = Krequest_header_fields;
			goto end;
		    }
		}
	    }
	    goto next_loop;
	  end_loop:
	    parse_state = Qnil;
	  end:
	    g2int_mark_tab(parsing_mark,g2int_point_max(parsing_mark));
	}
	g2int_mark_kill(G2int_current_left_of_parsing);
	g2int_mark_kill(G2int_current_right_of_parsing);
      POP_SPECIAL();
    POP_SPECIAL();
  end_giveup:
    return VALUES_1(parse_state);
}

/* COMMAND-LINE-PROCESS-ENABLE-HOSTNAME-LOOKUPS */
Object g2int_command_line_process_enable_hostname_lookups(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(59,40);
    return VALUES_1(arg_qm);
}

static Object array_constant_1;    /* # */

static Object Qg2int_enable_hostname_lookups;  /* enable-hostname-lookups */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ENABLE-HOSTNAME-LOOKUPS */
Object g2int_get_command_line_plist_element_for_enable_hostname_lookups()
{
    Object arg_qm, temp;

    x_note_fn_call(59,41);
    arg_qm = g2int_get_command_line_flag_argument(2,array_constant_1,T);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_enable_hostname_lookups),
	    Qg2int_command_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object string_constant_26;  /* "GET" */

static Object string_constant_27;  /* "The verb ~A is not supported." */

static Object Qg2int_form_for_resource_generation;  /* form-for-resource-generation */

static Object Qg2int_http_client_host_name;  /* http-client-host-name */

static Object Qg2int_http_client_host_address;  /* http-client-host-address */

static Object Qg2int_fetch_id;     /* fetch-id */

static Object string_constant_28;  /* ", handling" */

static Object string_constant_29;  /* ", malformed?" */

static Object string_constant_30;  /* ", Huh?" */

static Object string_constant_31;  /* "HTTP: ~A ~A \"~A\"~A" */

/* SETUP-TO-DO-QUERY */
Object g2int_setup_to_do_query(resource_buffer)
    Object resource_buffer;
{
    Object verb, url_details, result_1, form_qm, client_addr, client_name;
    Object temp;

    x_note_fn_call(59,42);
    verb = g2int_get_property_of_buffer(resource_buffer,
	    Qg2int_verb_of_request);
    url_details = g2int_get_property_of_buffer(resource_buffer,
	    Qg2int_url_details_of_request);
    if ( !TRUEP(string_eq(2,string_constant_26,verb))) {
	g2int_generate_error_response(resource_buffer,
		g2int_tformat_gensym_string(2,string_constant_27,verb));
	result_1 = Kfail;
	goto end_done;
    }
    form_qm = g2int_match_url_against_tendered_resources(url_details);
    if (form_qm) {
	g2int_set_property_of_buffer(resource_buffer,
		Qg2int_form_for_resource_generation,
		g2int_copy_resource_plist_value(form_qm));
	result_1 = Keval_form;
	goto end_done;
    }
    result_1 = Kfail;
    goto end_done;
  end_done:
    client_addr = 
	    g2int_peer_address_string_of_socket(ISVREF(G2int_current_thread,
	    (SI_Long)17L));
    client_name = getf(G2int_command_line_arguments,
	    Qg2int_enable_hostname_lookups,_) ? 
	    g2int_peer_name_of_socket(ISVREF(G2int_current_thread,
	    (SI_Long)17L)) : g2int_copy_gensym_string(client_addr);
    g2int_set_property_of_buffer(resource_buffer,
	    Qg2int_http_client_host_name,client_name);
    g2int_set_property_of_buffer(resource_buffer,
	    Qg2int_http_client_host_address,client_addr);
    g2int_set_property_of_buffer(resource_buffer,Qg2int_fetch_id,
	    ISVREF(G2int_current_thread,(SI_Long)1L));
    if (EQ(result_1,Keval_form))
	temp = string_constant_28;
    else if (EQ(result_1,Qnil))
	temp = string_constant_29;
    else
	temp = string_constant_30;
    g2int_notify_user_at_console(5,string_constant_31,client_name,verb,
	    url_details,temp);
    return VALUES_1(result_1);
}

static Object string_constant_32;  /* "<" */

static Object string_constant_33;  /* "HTML" */

static Object string_constant_34;  /* ">" */

static Object string_constant_35;  /* "HEADER" */

static Object string_constant_36;  /* "TITLE" */

static Object string_constant_37;  /* "Error" */

static Object string_constant_38;  /* "</" */

static Object string_constant_39;  /* "BODY" */

static Object string_constant_40;  /* "?
				    * "
				    */

static Object string_constant_41;  /* "<P>" */

static Object string_constant_42;  /* "The server was unable to handle your request for \"" */

static Object string_constant_43;  /* "\"." */

/* GENERATE-ERROR-RESPONSE */
Object g2int_generate_error_response(insert_mark,text_string)
    Object insert_mark, text_string;
{
    Object url_details, current_html_insert_mark;
    Declare_special(1);

    x_note_fn_call(59,43);
    url_details = g2int_get_property_of_buffer(insert_mark,
	    Qg2int_url_details_of_request);
    current_html_insert_mark = insert_mark;
    PUSH_SPECIAL(G2int_current_html_insert_mark,current_html_insert_mark,0);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_33);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_35);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_36);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_37);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_36);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_35);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_39);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_41);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_42);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,url_details);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_43);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_41);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,text_string);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_39);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_33);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
    POP_SPECIAL();
    return g2int_reclaim_gensym_string(text_string);
}

static Object string_constant_44;  /* "Unknown request for server data" */

/* HANDLE-URL-VIA-INTERNAL-PAGES */
Object g2int_handle_url_via_internal_pages()
{
    Object insert_mark;

    x_note_fn_call(59,44);
    insert_mark = ISVREF(G2int_current_thread,(SI_Long)18L);
    if (T)
	return g2int_generate_error_response(insert_mark,
		g2int_copy_gensym_string(string_constant_44));
    else
	return VALUES_1(Nil);
}

Object G2int_current_fetch_ids = UNBOUND;

static Object Qg2int_invalid_url_request_number;  /* invalid-url-request-number */

static Object string_constant_45;  /* "The URL request number does not denote a currently active request." */

/* VALIDATE-FETCH-ID */
Object g2int_validate_fetch_id(fetch_id)
    Object fetch_id;
{
    Object temp, thread_qm;

    x_note_fn_call(59,45);
    temp = g2int_assq_function(fetch_id,G2int_current_fetch_ids);
    thread_qm = CDR(temp);
    if ( !TRUEP(thread_qm))
	g2int_signal_from_rpc(Qg2int_invalid_url_request_number,
		string_constant_45);
    return VALUES_1(thread_qm);
}

/* SEARCH-CASE-INSENSITIVELY */
Object g2int_search_case_insensitively(string1,string2)
    Object string1, string2;
{
    Object firstchar, len1, len2, temp;
    SI_Long ab_loop_bind_, i, temp_1;

    x_note_fn_call(59,46);
    ab_loop_bind_ = IFIX(length(string2));
    i = (SI_Long)0L;
    firstchar = SCHAR(string1,FIX((SI_Long)0L));
    len1 = SIMPLE_ARRAY_ANY_1_LENGTH(string1);
    len2 = SIMPLE_ARRAY_ANY_1_LENGTH(string2);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    temp = CHR(ISCHAR(string2,i));
    if (CHAR_EQUAL(temp,firstchar)) {
	temp_1 = IFIX(len1) + i;
	if (string_equal(6,string1,string2,Kstart2,FIX(i),Kend2,
		FIX(MIN(IFIX(len2),temp_1))))
	    return VALUES_1(FIX(i));
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_46;  /* "Content-type" */

static Object string_constant_47;  /* "charset=" */

/* ADD-MESSAGE-HEADER-FIELD */
Object g2int_add_message_header_field(thread,header,data)
    Object thread, header, data;
{
    Object charset_qm, temp, pos_qm, new_item, old_item;
    Object gensym_push_modify_macro_arg, car_1, cdr_1;

    x_note_fn_call(59,47);
    if (string_equal(2,header,string_constant_46)) {
	charset_qm = g2int_search_case_insensitively(string_constant_47,data);
	if (charset_qm) {
	    temp = subseq(data,add(charset_qm,FIX((SI_Long)8L)),_);
	    SVREF(thread,FIX((SI_Long)23L)) = temp;
	    data = subseq(data,sub1(charset_qm),_);
	}
    }
    pos_qm = position(6,header,ISVREF(thread,(SI_Long)22L),Ktest,
	    SYMBOL_FUNCTION(Qstring_equal),Kkey,SYMBOL_FUNCTION(Qcar));
    new_item = g2int_gensym_cons_1(g2int_copy_gensym_string(header),
	    g2int_copy_gensym_string(data));
    if (pos_qm) {
	old_item = nth(pos_qm,ISVREF(thread,(SI_Long)22L));
	temp = ISVREF(thread,(SI_Long)22L);
	M_NTH(pos_qm,temp) = new_item;
	return g2int_reclaim_gensym_tree_with_text_strings(old_item);
    }
    else {
	gensym_push_modify_macro_arg = new_item;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(thread,(SI_Long)22L);
	temp = g2int_gensym_cons_1(car_1,cdr_1);
	return VALUES_1(SVREF(thread,FIX((SI_Long)22L)) = temp);
    }
}

static Object Kadd_data;           /* :add-data */

static Object string_constant_48;  /* "200 OK" */

/* ENQUEUE-TEXT-INTO-REPLY */
Object g2int_enqueue_text_into_reply(thread,datum)
    Object thread, datum;
{
    Object input_mark;

    x_note_fn_call(59,48);
    g2int_thread_enqueue_event(thread,Kadd_data);
    input_mark = ISVREF(thread,(SI_Long)18L);
    if ( !TRUEP(ISVREF(thread,(SI_Long)21L)))
	g2int_emit_headers_of_response(thread,string_constant_48);
    return g2int_insert_text_at_mark(input_mark,datum);
}

/* ENCODE-WEBLINK-HTML-TEXT */
Object g2int_encode_weblink_html_text(gensym_string,http_client_thread)
    Object gensym_string, http_client_thread;
{
    Object text_string, encoded_string, temp;

    x_note_fn_call(59,49);
    text_string = g2int_gensym_string_to_wide_string(gensym_string);
    encoded_string = g2int_export_text_string(2,text_string,
	    g2int_map_charset_name_to_transcoding_purpose(ISVREF(http_client_thread,
	    (SI_Long)23L)));
    temp = encoded_string;
    g2int_reclaim_text_string(text_string);
    return VALUES_1(temp);
}

static Object Kend_data;           /* :end-data */

/* ENQUEUE-FINISH-INTO-REPLY */
Object g2int_enqueue_finish_into_reply(thread)
    Object thread;
{
    x_note_fn_call(59,50);
    return g2int_thread_enqueue_event(thread,Kend_data);
}

static Object Kservice_the_reply_q;  /* :service-the-reply-q */

static Object Ksocket_issue;       /* :socket-issue */

static Object string_constant_49;  /* "ignoring event ~A" */

static Object Kreturn;             /* :return */

/* MT-EVAL-FORM-TO-OBTAIN-URL */
Object g2int_mt_eval_form_to_obtain_url()
{
    Object program_counter, pending_continuation, frame, header_mode;
    Object svref_arg_1, entry, input_mark, output_mark, event_qm;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(59,51);
    if (PUSH_AREA(Dynamic_area,0)) {
	program_counter = ISVREF(G2int_current_thread,(SI_Long)16L);
	pending_continuation = Nil;
	frame = ISVREF(G2int_current_thread,(SI_Long)13L);
	header_mode = ISVREF(frame,(SI_Long)5L);
	svref_arg_1 = G2int_current_thread;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kquantum_in_progress;
	if (EQ(program_counter,Kinitialize)) {
	    G2int_current_fetch_ids = 
		    g2int_gensym_cons_1(g2int_gensym_cons_1(ISVREF(G2int_current_thread,
		    (SI_Long)1L),G2int_current_thread),
		    G2int_current_fetch_ids);
	    g2int_eval_resource_generation_method(g2int_get_property_of_buffer(ISVREF(G2int_current_thread,
		    (SI_Long)18L),Qg2int_form_for_resource_generation));
	    pending_continuation = Kservice_the_reply_q;
	}
	else if (EQ(program_counter,Kcleanup)) {
	    entry = g2int_assq_function(ISVREF(G2int_current_thread,
		    (SI_Long)1L),G2int_current_fetch_ids);
	    if (entry) {
		G2int_current_fetch_ids = 
			g2int_delete_gensym_element_1(entry,
			G2int_current_fetch_ids);
		g2int_reclaim_gensym_cons_1(entry);
	    }
	}
	else if (EQ(program_counter,Kservice_the_reply_q)) {
	    input_mark = ISVREF(G2int_current_thread,(SI_Long)18L);
	    output_mark = ISVREF(G2int_current_thread,(SI_Long)19L);
	    event_qm = g2int_thread_dequeue_event(G2int_current_thread);
	    if (EQ(event_qm,Kend_data)) {
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)20L)) = Kdone;
	    }
	    if (EQ(event_qm,Kadd_data) || EQ(event_qm,Kend_data) || 
		    EQ(event_qm,Qnil)) {
		if ( !TRUEP(g2int_mark_eq(input_mark,output_mark)))
		    g2int_socket_write_region(ISVREF(G2int_current_thread,
			    (SI_Long)17L),output_mark,input_mark);
	    }
	    else if (EQ(event_qm,Ksocket_issue)) {
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)20L)) = Ksocket_issue;
	    }
	    else
		g2int_notify_user_at_console(2,string_constant_49,event_qm);
	    if (EQ(Kpending,ISVREF(G2int_current_thread,(SI_Long)20L)))
		pending_continuation = Kservice_the_reply_q;
	    else
		pending_continuation = Kreturn;
	}
	else
	    error((SI_Long)1L,"No handler for this continuation.");
	SVREF(frame,FIX((SI_Long)5L)) = header_mode;
	if ( !TRUEP(pending_continuation) &&  !EQ(Kcleanup,program_counter))
	    error((SI_Long)1L,"No continuation.");
	if ( !EQ(Kcontinuation_taken_care_of,pending_continuation)) {
	    svref_arg_1 = G2int_current_thread;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    pending_continuation);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_AREA(0);
    return result;
}

static Object Qg2int_mt_eval_form_to_obtain_url;  /* mt-eval-form-to-obtain-url */

static Object Ksending_data;       /* :sending-data */

/* EVAL-FORM-TO-OBTAIN-URL */
Object g2int_eval_form_to_obtain_url(return_continuation)
    Object return_continuation;
{
    Object frame, header_mode;

    x_note_fn_call(59,52);
    frame = g2int_prolog_thread_function(return_continuation,
	    SYMBOL_FUNCTION(Qg2int_mt_eval_form_to_obtain_url),
	    FIX((SI_Long)6L));
    header_mode = Ksending_data;
    return VALUES_1(SVREF(frame,FIX((SI_Long)5L)) = header_mode);
}

/* EVAL-RESOURCE-GENERATION-METHOD */
Object g2int_eval_resource_generation_method(form)
    Object form;
{
    Object fetch_id, temp, signature;

    x_note_fn_call(59,53);
    fetch_id = ISVREF(G2int_current_thread,(SI_Long)1L);
    if (CONSP(form)) {
	temp = CAR(form);
	if (EQ(temp,Qg2int_handle_url_via_call_back_to_g2_function)) {
	    temp = SECOND(form);
	    signature = SECOND(temp);
	    return g2int_handle_url_via_call_back_to_g2_function(fetch_id,
		    g2int_get_property_of_buffer(ISVREF(G2int_current_thread,
		    (SI_Long)18L),Qg2int_url_details_of_request),signature);
	}
	else if (EQ(temp,Qg2int_handle_url_via_file_system)) {
	    temp = SECOND(form);
	    return g2int_handle_url_via_file_system(fetch_id,temp,
		    g2int_get_property_of_buffer(ISVREF(G2int_current_thread,
		    (SI_Long)18L),Qg2int_url_details_of_request));
	}
	else if (EQ(temp,Qg2int_handle_url_via_internal_pages))
	    return g2int_handle_url_via_internal_pages();
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_50;  /* "Malformed CGI arguments." */

static Object string_constant_51;  /* "?" */

static Object string_constant_52;  /* "=" */

static Object string_constant_53;  /* "&" */

static Object Qg2int_cgi_arguments;  /* cgi-arguments */

static Object Qg2int_search_part;  /* search-part */

static Object Qg2int_cgi_routine_name;  /* cgi-routine-name */

static Object Qg2int_text;         /* text */

/* HANDLE-URL-VIA-CALL-BACK-TO-G2-FUNCTION */
Object g2int_handle_url_via_call_back_to_g2_function(fetch_id,url_details,
	    signature)
    Object fetch_id, url_details, signature;
{
    Object signature_old_value, temp, routine_name, argument_alist;
    Object argument_list, bailout_qm, bailout_apology, m, mark;
    Object current_left_of_parsing, current_right_of_parsing;
    Object right_edge_of_search_part, args, key, value, call_site;
    Object argument_name, type, ab_loop_list_, arg_entry_qm, argument_value;
    Object ab_loop_desetq_, argument_text, text_string, arg_qm, result_1;
    Object current_icp_socket;
    Declare_special(3);

    x_note_fn_call(59,54);
    signature_old_value = signature;
    temp = FIRST(signature_old_value);
    signature = REST(signature_old_value);
    routine_name = temp;
    argument_alist = Nil;
    argument_list = Nil;
    bailout_qm = Nil;
    bailout_apology = string_constant_50;
    m = g2int_make_mark_into_new_empty_resource_buffer();
    g2int_insert_text_at_mark(m,url_details);
    g2int_mark_tab(m,FIX((SI_Long)0L));
    mark = m;
    current_left_of_parsing = g2int_mark_copy(mark);
    PUSH_SPECIAL(G2int_current_left_of_parsing,current_left_of_parsing,2);
      current_right_of_parsing = g2int_mark_copy(mark);
      PUSH_SPECIAL(G2int_current_right_of_parsing,current_right_of_parsing,1);
	g2int_scan_upto_character(CHR('\?'));
	g2int_scan_text(string_constant_51);
	right_edge_of_search_part = 
		g2int_mark_copy(G2int_current_right_of_parsing);
	args = Nil;
	key = Nil;
	value = Nil;
      next_loop:
	key = Nil;
	value = Nil;
	key = g2int_scan_symbol();
	g2int_scan_text(string_constant_52);
	if ( !TRUEP(g2int_scan_upto_character(CHR('&'))))
	    g2int_scan_upto_end();
	value = 
		g2int_coerce_www_form_urlencoded_to_ascii_text(g2int_get_simple_text_from_last_scan());
	args = g2int_gensym_cons_1(g2int_gensym_cons_1(key,value),args);
	if ( !TRUEP(g2int_scan_text(string_constant_53))) {
	    argument_alist = args;
	    goto end;
	}
	goto next_loop;
      end_loop:
	argument_alist = Qnil;
      end:;
	g2int_set_property_of_buffer(ISVREF(G2int_current_thread,
		(SI_Long)18L),Qg2int_cgi_arguments,argument_alist);
	temp = ISVREF(G2int_current_thread,(SI_Long)18L);
	g2int_set_property_of_buffer(temp,Qg2int_search_part,
		g2int_copy_text_between_marks(right_edge_of_search_part,
		G2int_current_right_of_parsing));
	g2int_set_property_of_buffer(ISVREF(G2int_current_thread,
		(SI_Long)18L),Qg2int_cgi_routine_name,
		g2int_copy_gensym_string(SYMBOL_NAME(routine_name)));
	g2int_mark_kill(right_edge_of_search_part);
	call_site = Nil;
	argument_name = Nil;
	type = Nil;
	ab_loop_list_ = signature;
	arg_entry_qm = Nil;
	argument_value = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	argument_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	type = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	arg_entry_qm = g2int_assq_function(argument_name,argument_alist);
	if (arg_entry_qm) {
	    argument_text = CDR(arg_entry_qm);
	    if (EQ(type,Qsymbol))
		argument_value = 
			g2int_intern_internet_text_for_g2(argument_text);
	    else if (EQ(type,Qinteger)) {
		text_string = g2int_copy_text_string(argument_text);
		temp = 
			g2int_text_string_parse_integer_function(text_string,
			FIX((SI_Long)0L),Nil,Nil);
		g2int_reclaim_text_string(text_string);
		arg_qm = temp;
		if (arg_qm)
		    argument_value = arg_qm;
		else {
		    bailout_qm = T;
		    argument_value = FIX((SI_Long)0L);
		}
	    }
	    else if (EQ(type,Qg2int_text))
		argument_value = 
			g2int_prep_internet_text_for_g2(argument_text);
	    else
		argument_value = Qnil;
	}
	else {
	    if (EQ(Qg2int_fetch_id,argument_name))
		result_1 = fetch_id;
	    else {
		temp = g2int_assq_function(fetch_id,G2int_current_fetch_ids);
		result_1 = g2int_built_in_argument_nameqm(ISVREF(CDR(temp),
			(SI_Long)19L),argument_name);
	    }
	    if (EQ(result_1,G2int_no_such_built_in_argument)) {
		result_1 = FIX((SI_Long)1L);
		bailout_qm = T;
	    }
	    argument_value = result_1;
	}
	call_site = g2int_gensym_cons_1(argument_value,call_site);
	goto next_loop_1;
      end_loop_1:
	argument_list = nreverse(call_site);
	goto end_1;
	argument_list = Qnil;
      end_1:;
	if (bailout_qm)
	    g2int_decline_to_serve(fetch_id,bailout_apology);
	else {
	    current_icp_socket = ISVREF(ISVREF(G2int_current_thread,
		    (SI_Long)5L),(SI_Long)18L);
	    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
	      g2int_apply_rpc_imported_g2(routine_name,argument_list);
	    POP_SPECIAL();
	}
	temp = g2int_reclaim_gensym_list_1(argument_list);
	g2int_mark_kill(G2int_current_left_of_parsing);
	g2int_mark_kill(G2int_current_right_of_parsing);
      POP_SPECIAL();
    POP_SPECIAL();
    g2int_reclaim_resource_buffer_of_mark(m);
    return VALUES_1(temp);
}

Object G2int_the_server_name = UNBOUND;

static Object list_constant_1;     /* # */

static Object Qg2int_buffer_property;  /* buffer-property */

static Object Qg2int_buffer_propertyqm;  /* buffer-property? */

static Object string_constant_54;  /* "" */

static Object Qg2int_integer_buffer_property;  /* integer-buffer-property */

static Object string_constant_55;  /* "~D" */

static Object Qg2int_server_name;  /* server-name */

static Object Qg2int_request_mime_headers;  /* request-mime-headers */

static Object Qg2int_server_port;  /* server-port */

static Object Qg2int_remap;        /* remap */

static Object Qg2int_constant;     /* constant */

static Object Qg2int_content_type;  /* content-type */

static Object string_constant_56;  /* "HEAD" */

static Object string_constant_57;  /* "NOT-IMPLEMENTED" */

static Object Qg2int_tbd;          /* tbd */

static Object string_constant_58;  /* "UNKNOWN_METHOD_FOR_BUILDIN" */

static Object string_constant_59;  /* "HTTP-" */

static Object Qg2int_mimi_headers_from_server;  /* mimi-headers-from-server */

/* BUILT-IN-ARGUMENT-NAME? */
Object g2int_built_in_argument_nameqm(request_mark,argument_name_or_symbol)
    Object request_mark, argument_name_or_symbol;
{
    Object argument_name, key, method, details, ab_loop_list_, ab_loop_desetq_;
    Object temp, raw_text, verb, key2, value;
    char sloppy_qm;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(59,55);
    if (PUSH_AREA(Dynamic_area,0)) {
	argument_name = SYMBOLP(argument_name_or_symbol) ? 
		SYMBOL_NAME(argument_name_or_symbol) : argument_name_or_symbol;
	key = Nil;
	method = Nil;
	details = Nil;
	ab_loop_list_ = list_constant_1;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	key = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	method = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	details = CDR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_equal(2,argument_name,key)) {
	    if (EQ(method,Qg2int_buffer_property))
		result = g2int_get_property_of_buffer(request_mark,
			CAR(details));
	    else if (EQ(method,Qg2int_buffer_propertyqm)) {
		temp = g2int_get_property_of_buffer(request_mark,CAR(details));
		if (temp)
		    result = VALUES_1(temp);
		else
		    result = VALUES_1(string_constant_54);
	    }
	    else if (EQ(method,Qg2int_integer_buffer_property))
		result = g2int_thread_format(2,string_constant_55,
			g2int_get_property_of_buffer(request_mark,
			CAR(details)));
	    else if (EQ(method,Qg2int_server_name))
		result = VALUES_1(G2int_the_server_name);
	    else if (EQ(method,Qg2int_request_mime_headers)) {
		temp = g2int_get_property_of_buffer(request_mark,
			Qg2int_left_edge_of_mime_headers);
		raw_text = g2int_copy_text_between_marks(temp,
			g2int_get_property_of_buffer(request_mark,
			Qg2int_right_edge_of_mime_headers));
		temp = g2int_copy_for_thread_tree(raw_text);
		g2int_reclaim_gensym_string(raw_text);
		result = VALUES_1(temp);
	    }
	    else if (EQ(method,Qg2int_server_port))
		result = g2int_thread_format(2,string_constant_55,
			ISVREF(G2int_the_http_server_threadqm,(SI_Long)17L));
	    else if (EQ(method,Qg2int_remap))
		result = g2int_built_in_argument_nameqm(request_mark,
			CAR(details));
	    else if (EQ(method,Qg2int_constant))
		result = VALUES_1(CAR(details));
	    else if (EQ(method,Qg2int_content_type)) {
		verb = g2int_get_property_of_buffer(request_mark,CAR(details));
		if (string_equal(2,string_constant_56,verb))
		    result = VALUES_1(string_constant_57);
		else
		    result = VALUES_1(string_constant_54);
	    }
	    else if (EQ(method,Qg2int_tbd))
		result = VALUES_1(string_constant_57);
	    else
		result = VALUES_1(string_constant_58);
	    goto end;
	}
	goto next_loop;
      end_loop:
	if ( !TRUEP(g2int_string_prefixeq(string_constant_59,argument_name))) {
	    result = VALUES_1(G2int_no_such_built_in_argument);
	    goto end;
	}
	else {
	    sloppy_qm = SYMBOLP(argument_name_or_symbol);
	    key = g2int_thread_string_substring(argument_name,
		    FIX((SI_Long)5L),Nil);
	    key2 = Nil;
	    value = Nil;
	    ab_loop_list_ = g2int_get_property_of_buffer(request_mark,
		    Qg2int_mimi_headers_from_server);
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    key2 = CAR(ab_loop_desetq_);
	    value = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (sloppy_qm ? TRUEP(string_equal(2,key,key2)) : 
		    TRUEP(string_eq(2,key,key2))) {
		temp = value;
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_1:;
	    if (temp)
		result = VALUES_1(temp);
	    else
		result = VALUES_1(G2int_no_such_built_in_argument);
	    goto end;
	}
	result = VALUES_1(Qnil);
      end:;
    }
    POP_AREA(0);
    return result;
}

static Object Qg2int_no_such_built_in_argument;  /* no-such-built-in-argument */

static Object string_constant_60;  /* "There is no such built in argument" */

/* BUILT-IN-ARGUMENT-OF-FETCH-ID */
Object g2int_built_in_argument_of_fetch_id(fetch_id,argument_name)
    Object fetch_id, argument_name;
{
    Object thread_of_fetch, resource_mark, first_try, result_in_latin1;
    Object fetch_id_as_string, name, value, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(59,56);
    thread_of_fetch = g2int_validate_fetch_id(fetch_id);
    resource_mark = ISVREF(thread_of_fetch,(SI_Long)19L);
    first_try = g2int_built_in_argument_nameqm(resource_mark,argument_name);
    if ( !EQ(first_try,G2int_no_such_built_in_argument)) {
	result_in_latin1 = first_try;
	goto end;
    }
    if (EQ(Qg2int_fetch_id,argument_name)) {
	fetch_id_as_string = g2int_thread_format(2,string_constant_55,
		fetch_id);
	result_in_latin1 = fetch_id_as_string;
	goto end;
    }
    name = Nil;
    value = Nil;
    ab_loop_list_ = g2int_get_property_of_buffer(resource_mark,
	    Qg2int_cgi_arguments);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    value = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_equal(2,SYMBOL_NAME(name),argument_name)) {
	result_in_latin1 = value;
	goto end;
    }
    goto next_loop;
  end_loop:;
    result_in_latin1 = 
	    g2int_signal_from_rpc(Qg2int_no_such_built_in_argument,
	    string_constant_60);
  end:
    return g2int_prep_internet_text_for_g2(result_in_latin1);
}

static Object Qg2int_utf_g_gensym_string;  /* utf-g-gensym-string */

/* PREP-INTERNET-TEXT-FOR-G2 */
Object g2int_prep_internet_text_for_g2(internet_text)
    Object internet_text;
{
    Object text_string, utf_g_gensym_string, temp;

    x_note_fn_call(59,57);
    text_string = g2int_import_text_string(2,internet_text,
	    g2int_map_charset_name_to_transcoding_purpose(G2int_default_http_header_charset_name));
    utf_g_gensym_string = g2int_export_text_string(2,text_string,
	    Qg2int_utf_g_gensym_string);
    temp = g2int_copy_for_thread_tree(utf_g_gensym_string);
    g2int_reclaim_text_string(text_string);
    g2int_reclaim_gensym_string(utf_g_gensym_string);
    return VALUES_1(temp);
}

static Object Knil;                /* :nil */

/* INTERN-INTERNET-TEXT-FOR-G2 */
Object g2int_intern_internet_text_for_g2(internet_text)
    Object internet_text;
{
    Object text_string, temp, prepped_text_string, result_symbol;

    x_note_fn_call(59,58);
    text_string = g2int_import_text_string(2,internet_text,
	    g2int_map_charset_name_to_transcoding_purpose(G2int_default_http_header_charset_name));
    temp = g2int_prep_internet_text_string_for_g2_symbol(text_string);
    g2int_reclaim_text_string(text_string);
    prepped_text_string = temp;
    result_symbol = g2int_intern_text_string(1,prepped_text_string);
    if (result_symbol);
    else
	result_symbol = Knil;
    return VALUES_1(result_symbol);
}

static Object Qg2int_do_not_use;   /* do-not-use */

/* PREP-INTERNET-TEXT-STRING-FOR-G2-SYMBOL */
Object g2int_prep_internet_text_string_for_g2_symbol(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_1, output_length, code, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, start;
    SI_Long ab_loop_bind_, end, i;
    Declare_special(5);
    Object result;

    x_note_fn_call(59,59);
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
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
	      length_1 = UBYTE_16_ISAREF_1(text_string,length_1 - 
		      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(text_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L);
	      start = (SI_Long)0L;
	      ab_loop_bind_ = length_1;
	      character_1 = Nil;
	    next_loop:
	      if (start >= ab_loop_bind_)
		  goto end_loop;
	      character_1 = FIX(UBYTE_16_ISAREF_1(text_string,start));
	      if ( !TRUEP(g2int_blank_p(character_1)))
		  goto end_loop;
	      start = start + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      end = length_1;
	      ab_loop_bind_ = start;
	      character_1 = Nil;
	    next_loop_1:
	      if (end <= ab_loop_bind_)
		  goto end_loop_1;
	      character_1 = FIX(UBYTE_16_ISAREF_1(text_string,end - 
		      (SI_Long)1L));
	      if ( !TRUEP(g2int_blank_p(character_1)))
		  goto end_loop_1;
	      end = end - (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      output_length = FIX((SI_Long)0L);
	      i = start;
	      ab_loop_bind_ = end;
	      character_1 = Nil;
	    next_loop_2:
	      if (i >= ab_loop_bind_)
		  goto end_loop_2;
	      character_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
	      if ( !FIXNUM_LT(output_length,
		      G2int_maximum_length_for_user_symbols))
		  goto end_loop_2;
	      if ( !(IFIX(character_1) == (SI_Long)65535L || 
		      IFIX(character_1) == (SI_Long)65534L)) {
		  code = character_1;
		  if (IFIX(code) < (SI_Long)127L)
		      temp = (SI_Long)97L <= IFIX(code) && IFIX(code) <= 
			      (SI_Long)122L ? FIX(IFIX(code) + 
			      (SI_Long)-32L) : code;
		  else {
		      temp = g2int_unicode_uppercase_if_lowercase(code);
		      if (temp);
		      else
			  temp = code;
		  }
		  g2int_twrite_wide_character(temp);
		  output_length = FIXNUM_ADD1(output_length);
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:;
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_default_file_type_to_mime_type_coersions = UNBOUND;

Object G2int_newline_string = UNBOUND;

static Object Qg2int_dos;          /* dos */

static Object Qg2int_win32;        /* win32 */

static Object string_constant_61;  /* "~A~A" */

static Object Qg2int_unbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object string_constant_62;  /* "text/plain" */

static Object string_constant_63;  /* "<H1>Error encountered generating URL<H1>
				    * "
				    */

static Object string_constant_64;  /* "Not found: ~S" */

static Object string_constant_65;  /* "Resource not found." */

/* HANDLE-URL-VIA-FILE-SYSTEM */
Object g2int_handle_url_via_file_system(fetch_id,root_pathname,details)
    Object fetch_id, root_pathname, details;
{
    Object result_1, munged_details, namestring_1, input_mark, temp;
    Object thread_of_request;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Object pn, file_type_qm, narrow_type_qm, key, value, ab_loop_list_;
    Object ab_loop_desetq_, temp_1, count_qm;
    SI_Long i, ab_loop_bind_;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(59,60);
    SAVE_STACK();
    if (EQ(G2int_local_file_system,Qg2int_dos) || 
	    EQ(G2int_local_file_system,Qg2int_win32)) {
	result_1 = g2int_copy_gensym_string(details);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(result_1));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (CHAR_EQ(CHR('/'),CHR(ICHAR(result_1,i))))
	    SET_ICHAR(result_1,i,'\\');
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	munged_details = result_1;
    }
    else
	munged_details = g2int_copy_gensym_string(details);
    namestring_1 = g2int_tformat_gensym_string(3,string_constant_61,
	    root_pathname,munged_details);
    input_mark = ISVREF(G2int_current_thread,(SI_Long)18L);
    temp = g2int_assq_function(fetch_id,G2int_current_fetch_ids);
    thread_of_request = CDR(temp);
    g2int_reclaim_gensym_string(munged_details);
    pathname_used_p = Qg2int_unbound_in_protected_let;
    namestring_2 = Qg2int_unbound_in_protected_let;
    stream = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
		(EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		T : Nil) : Qnil;
	namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
		EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		g2int_gensym_namestring(1,namestring_1) : namestring_1;
	stream = 
		g2int_g2_stream_open_for_random_access_binary_input(namestring_2);
	if (stream) {
	    temp = G2int_current_thread;
	    pn = g2int_gensym_pathname(namestring_1);
	    file_type_qm = ISVREF(pn,(SI_Long)5L);
	    narrow_type_qm = file_type_qm ? 
		    g2int_wide_string_to_gensym_string(file_type_qm) : Qnil;
	    key = Nil;
	    value = Nil;
	    ab_loop_list_ = G2int_default_file_type_to_mime_type_coersions;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    key = CAR(ab_loop_desetq_);
	    temp_1 = CDR(ab_loop_desetq_);
	    value = CAR(temp_1);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (narrow_type_qm && string_equal(2,narrow_type_qm,key)) {
		temp_1 = value;
		goto end;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = string_constant_62;
	    goto end;
	    temp_1 = Qnil;
	  end:;
	    if (narrow_type_qm)
		g2int_reclaim_gensym_string(narrow_type_qm);
	    g2int_reclaim_gensym_pathname(pn);
	    g2int_add_message_header_field(temp,string_constant_46,temp_1);
	    g2int_emit_headers_of_response(G2int_current_thread,
		    string_constant_48);
	    count_qm = Nil;
	  next_loop_2:
	    count_qm = 
		    g2int_g2_stream_read_into_buffer(G2int_current_foreign_string_pad,
		    G2int_max_of_foreign_string_pad,stream);
	    if ( !TRUEP(count_qm)) {
		g2int_enqueue_text_into_reply(thread_of_request,
			string_constant_63);
		goto end_1;
	    }
	    else if (IFIX(count_qm) == (SI_Long)0L)
		goto end_1;
	    else
		g2int_insert_subtext_at_mark(input_mark,
			G2int_current_foreign_string_pad,FIX((SI_Long)0L),
			count_qm);
	    goto next_loop_2;
	  end_loop_2:
	  end_1:;
	}
	else {
	    g2int_notify_user_at_console(2,string_constant_64,namestring_1);
	    g2int_decline_to_serve(fetch_id,string_constant_65);
	}
    }
    POP_UNWIND_PROTECT(0);
    if (stream) {
	if ( !EQ(stream,Qg2int_unbound_in_protected_let))
	    g2int_g2_stream_close(stream);
    }
    if (namestring_2) {
	if ( !EQ(namestring_2,Qg2int_unbound_in_protected_let)) {
	    if (pathname_used_p)
		g2int_reclaim_text_string(namestring_2);
	}
    }
    CONTINUE_UNWINDING(0);
    g2int_enqueue_finish_into_reply(thread_of_request);
    result = g2int_reclaim_gensym_string(namestring_1);
    RESTORE_STACK();
    return result;
}

static Object string_constant_66;  /* "HTTP/1.0 " */

static Object string_constant_67;  /* ": " */

static Object string_constant_68;  /* ";charset=" */

static Object string_constant_69;  /* "Content-type: text/html;charset=" */

/* EMIT-HEADERS-OF-RESPONSE */
Object g2int_emit_headers_of_response(thread,error_code_text)
    Object thread, error_code_text;
{
    Object input_mark, saw_content_type, text, header, ab_loop_list_;

    x_note_fn_call(59,61);
    if ( !TRUEP(ISVREF(thread,(SI_Long)21L))) {
	input_mark = ISVREF(thread,(SI_Long)18L);
	saw_content_type = Nil;
	SVREF(thread,FIX((SI_Long)21L)) = T;
	if ((SI_Long)1000L <= IFIX(g2int_get_property_of_buffer(input_mark,
		Qg2int_protocol_of_request))) {
	    text = string_constant_66;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    text = error_code_text;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    text = G2int_newline_string;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    header = Nil;
	    ab_loop_list_ = ISVREF(thread,(SI_Long)22L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    header = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    text = CAR(header);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    text = string_constant_67;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    if (string_equal(2,CAR(header),string_constant_46)) {
		text = CDR(header);
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = string_constant_68;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = 
			g2int_map_charset_name_to_charset_string(ISVREF(thread,
			(SI_Long)23L));
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = G2int_newline_string;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		saw_content_type = T;
	    }
	    else {
		text = CDR(header);
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = G2int_newline_string;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
	    }
	    goto next_loop;
	  end_loop:;
	    if ( !TRUEP(saw_content_type)) {
		text = string_constant_69;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = 
			g2int_map_charset_name_to_charset_string(ISVREF(thread,
			(SI_Long)23L));
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
		text = G2int_newline_string;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		    text = g2int_prep_internet_text_for_g2(text);
		g2int_insert_subtext_at_mark(input_mark,text,
			FIX((SI_Long)0L),length(text));
	    }
	    text = string_constant_54;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    g2int_insert_subtext_at_mark(input_mark,text,FIX((SI_Long)0L),
		    length(text));
	    text = G2int_newline_string;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text) != (SI_Long)0L)
		text = g2int_prep_internet_text_for_g2(text);
	    return g2int_insert_subtext_at_mark(input_mark,text,
		    FIX((SI_Long)0L),length(text));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_70;  /* "404 Not Found" */

static Object string_constant_71;  /* "<H1>Unable to provide URL</H1>
				    * "
				    */

/* DECLINE-TO-SERVE */
Object g2int_decline_to_serve(fetch_id,apology_qm)
    Object fetch_id, apology_qm;
{
    Object temp, thread_of_request;

    x_note_fn_call(59,62);
    temp = g2int_assq_function(fetch_id,G2int_current_fetch_ids);
    thread_of_request = CDR(temp);
    g2int_emit_headers_of_response(thread_of_request,string_constant_70);
    g2int_enqueue_text_into_reply(thread_of_request,string_constant_71);
    if (apology_qm)
	g2int_enqueue_text_into_reply(thread_of_request,apology_qm);
    return g2int_enqueue_finish_into_reply(thread_of_request);
}

Object G2int_server_pages = UNBOUND;

Object G2int_statistic_counters = UNBOUND;

static Object string_constant_72;  /* "Overview of Server Status" */

static Object string_constant_73;  /* "H1" */

static Object string_constant_74;  /* "GSI-Web The G2/Internet Bridge" */

static Object string_constant_75;  /* "H2" */

static Object string_constant_76;  /* "Version Information" */

static Object string_constant_77;  /* "~S " */

static Object string_constant_78;  /* "Thread Information" */

static Object string_constant_79;  /* "UL" */

static Object string_constant_80;  /* "Statistics" */

static Object string_constant_81;  /* "<LI>" */

/* GENERATE-OVERVIEW-HTML */
Object g2int_generate_overview_html(insert_mark)
    Object insert_mark;
{
    Object current_html_insert_mark, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object i, ab_loop_list_, text, name, format_1, ab_loop_desetq_, temp, txt;
    Declare_special(5);
    Object result;

    x_note_fn_call(59,63);
    current_html_insert_mark = insert_mark;
    PUSH_SPECIAL(G2int_current_html_insert_mark,current_html_insert_mark,4);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_33);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_35);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_36);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_72);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_36);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_35);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_39);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_73);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_74);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_73);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_76);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_41);
      current_gensym_string = 
	      g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
      PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
	fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		2);
	  total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	  PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		  1);
	    current_twriting_output_type = Qg2int_gensym_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      i = Nil;
	      ab_loop_list_ = 
		      G2int_system_version_of_current_gensym_product_line;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      i = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      g2int_tformat(2,string_constant_77,i);
	      goto next_loop;
	    end_loop:;
	      text = g2int_copy_out_current_gensym_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,text);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      G2int_build_identification_string);
      g2int_reclaim_gensym_string(text);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_40);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_78);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_79);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_generate_thread_tree_html(G2int_root_thread);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_79);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_80);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_75);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_32);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_79);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      name = Nil;
      format_1 = Nil;
      ab_loop_list_ = G2int_statistic_counters;
      ab_loop_desetq_ = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      name = CAR(ab_loop_desetq_);
      temp = CDR(ab_loop_desetq_);
      format_1 = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_81);
      txt = g2int_tformat_text_string(2,format_1,SYMBOL_VALUE(name));
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,txt);
      g2int_reclaim_text_string(txt);
      goto next_loop_1;
    end_loop_1:;
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_79);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_39);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_38);
      g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_33);
      result = g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	      string_constant_34);
    POP_SPECIAL();
    return result;
}

static Object string_constant_82;  /* "~S/~S ~S ~S" */

/* GENERATE-THREAD-TREE-HTML */
Object g2int_generate_thread_tree_html(thread)
    Object thread;
{
    Object txt, c, ab_loop_list_;

    x_note_fn_call(59,64);
    g2int_insert_text_at_mark(G2int_current_html_insert_mark,
	    string_constant_81);
    txt = g2int_tformat_text_string(5,string_constant_82,ISVREF(thread,
	    (SI_Long)7L),ISVREF(thread,(SI_Long)8L),ISVREF(thread,
	    (SI_Long)2L),ISVREF(thread,(SI_Long)1L));
    g2int_insert_text_at_mark(G2int_current_html_insert_mark,txt);
    g2int_reclaim_text_string(txt);
    if (ISVREF(thread,(SI_Long)6L)) {
	g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_32);
	g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_79);
	g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_34);
	c = Nil;
	ab_loop_list_ = ISVREF(thread,(SI_Long)6L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	c = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_generate_thread_tree_html(c);
	goto next_loop;
      end_loop:;
	g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_38);
	g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_79);
	return g2int_insert_text_at_mark(G2int_current_html_insert_mark,
		string_constant_34);
    }
    else
	return VALUES_1(Nil);
}

void server_INIT()
{
    Object temp, reclaim_structure_for_listener_socket;
    Object reclaim_structure_for_server_thread;
    Object all_known_command_line_plist_elements_new_value;
    Object reclaim_structure_for_http_client_thread;
    Object Qg2int_generate_overview_html, list_constant_93, list_constant_92;
    Object string_constant_171, Qg2int_count_of_number_of_http_clients;
    Object AB_package, list_constant_91, list_constant_90, string_constant_170;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_89;
    Object list_constant_88, list_constant_87, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_82, list_constant_81, list_constant_80;
    Object list_constant_79, list_constant_78, list_constant_77;
    Object list_constant_76, list_constant_75, list_constant_74;
    Object list_constant_73, list_constant_72, list_constant_71;
    Object list_constant_70, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_65;
    Object list_constant_64, list_constant_63, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_59;
    Object list_constant_58, list_constant_57, string_constant_169;
    Object string_constant_168, list_constant_46, string_constant_167;
    Object list_constant_56, string_constant_166, string_constant_165;
    Object string_constant_164, string_constant_163, list_constant_54;
    Object string_constant_162, string_constant_161, string_constant_160;
    Object string_constant_159, list_constant_55, string_constant_158;
    Object string_constant_157, string_constant_156, string_constant_155;
    Object string_constant_154, string_constant_153, string_constant_152;
    Object string_constant_151, Qg2int_7bit, list_constant_53;
    Object string_constant_150, string_constant_149, list_constant_48;
    Object string_constant_148, list_constant_52, string_constant_147;
    Object string_constant_146, string_constant_145, list_constant_51;
    Object string_constant_144, string_constant_143, string_constant_142;
    Object string_constant_141, string_constant_140, string_constant_139;
    Object list_constant_50, string_constant_138, string_constant_137;
    Object string_constant_136, list_constant_49, string_constant_135;
    Object string_constant_134, string_constant_133, Qg2int_8bit;
    Object list_constant_47, string_constant_132, string_constant_131;
    Object string_constant_130, string_constant_129, string_constant_128;
    Object string_constant_127, string_constant_126, Qg2int_binary;
    Object list_constant_45, list_constant_44, list_constant_43;
    Object list_constant_42, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_38, list_constant_37;
    Object list_constant_36, list_constant_35, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object list_constant_30, list_constant_29, list_constant_28;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object string_constant_125, list_constant_22, string_constant_124;
    Object string_constant_123, string_constant_122, list_constant_24;
    Object string_constant_121, string_constant_120, string_constant_119;
    Object string_constant_118, string_constant_117, string_constant_116;
    Object string_constant_115, Qg2int_path_translatedqm, string_constant_114;
    Object list_constant_21, string_constant_113, string_constant_112;
    Object string_constant_111, string_constant_110, string_constant_109;
    Object list_constant_23, string_constant_108, string_constant_107;
    Object string_constant_106, string_constant_105, string_constant_104;
    Object string_constant_103, string_constant_102, Qg2int_server;
    Object Qg2int_current_fetch_ids, list_constant_20;
    Object Qg2int_command_line_plist_element_getter;
    Object Qg2int_get_command_line_plist_element_for_enable_hostname_lookups;
    Object list_constant_18;
    Object Qg2int_command_line_process_enable_hostname_lookups;
    Object Qg2int_m_thread_feed_trace_http_client_thread_1;
    Object Qg2int_http_client_thread, Qg2int_thread_feed_trace;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_http_client_thread_count;
    Object Qg2int_chain_of_available_http_client_threads;
    Object Qg2int_type_description_of_type, string_constant_101;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type, list_constant_19;
    Object Qg2int_get_command_line_plist_element_for_default_charset;
    Object Qg2int_command_line_process_default_charset, Qg2int_unicode_utf_8;
    Object Qg2int_default_http_header_charset_name;
    Object Qg2int_default_default_http_header_charset_name, list_constant_17;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object list_constant_6, list_constant_5, list_constant_4, list_constant_3;
    Object list_constant_2, Qg2int_ks_euc_gensym_string_with_crlf;
    Object string_constant_100, Qg2int_ksc_euc;
    Object Qg2int_shift_jis_gensym_string_with_crlf, string_constant_99;
    Object Qg2int_shift_jis, Qg2int_jis_euc_gensym_string_with_crlf;
    Object string_constant_98, Qg2int_jis_euc;
    Object Qg2int_iso_8859_10_gensym_string_with_crlf, string_constant_97;
    Object Qg2int_latin_6, Qg2int_iso_8859_9_gensym_string_with_crlf;
    Object string_constant_96, Qg2int_latin_5;
    Object Qg2int_iso_8859_8_gensym_string_with_crlf, string_constant_95;
    Object Qg2int_latin_hebrew, Qg2int_iso_8859_7_gensym_string_with_crlf;
    Object string_constant_94, Qg2int_latin_greek;
    Object Qg2int_iso_8859_6_gensym_string_with_crlf, string_constant_93;
    Object Qg2int_latin_arabic, Qg2int_iso_8859_5_gensym_string_with_crlf;
    Object string_constant_92, Qg2int_latin_cyrillic;
    Object Qg2int_iso_8859_4_gensym_string_with_crlf, string_constant_91;
    Object Qg2int_latin_4, Qg2int_iso_8859_3_gensym_string_with_crlf;
    Object string_constant_90, Qg2int_latin_3;
    Object Qg2int_iso_8859_2_gensym_string_with_crlf, string_constant_89;
    Object Qg2int_latin_2, Qg2int_iso_8859_1_gensym_string_with_crlf;
    Object string_constant_88, Qg2int_latin_1;
    Object Qg2int_us_ascii_gensym_string_with_crlf, string_constant_87;
    Object Qg2int_us_ascii, Qg2int_utf_8_gensym_string_with_crlf;
    Object string_constant_86, Qg2int_m_thread_feed_trace_server_thread_1;
    Object Qg2int_server_thread, Qg2int_server_thread_count;
    Object Qg2int_chain_of_available_server_threads, string_constant_85;
    Object Qg2int_m_socket_listen_listener_socket_1, Qg2int_listener_socket;
    Object Qg2int_listener_socket_count;
    Object Qg2int_chain_of_available_listener_sockets, string_constant_84;
    Object string_constant_83, Qg2int_base64_encoding_vector;
    Object Kno_such_built_in_argument;

    x_note_fn_call(59,65);
    SET_PACKAGE("AB");
    Kno_such_built_in_argument = STATIC_SYMBOL("NO-SUCH-BUILT-IN-ARGUMENT",
	    Pkeyword);
    G2int_no_such_built_in_argument = Kno_such_built_in_argument;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_base64_encoding_vector = STATIC_SYMBOL("BASE64-ENCODING-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_base64_encoding_vector,
	    G2int_base64_encoding_vector);
    string_constant_83 = 
	    STATIC_STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    SET_SYMBOL_VALUE(Qg2int_base64_encoding_vector,string_constant_83);
    if (G2int_alist_of_resources_tendered_by_g2 == UNBOUND)
	G2int_alist_of_resources_tendered_by_g2 = Nil;
    string_constant = STATIC_STRING("call");
    string_constant_1 = STATIC_STRING("cgi");
    Kcgi = STATIC_SYMBOL("CGI",Pkeyword);
    string_constant_2 = STATIC_STRING("url");
    Kurl = STATIC_SYMBOL("URL",Pkeyword);
    string_constant_3 = STATIC_STRING("(");
    string_constant_4 = STATIC_STRING(")");
    Qg2int_handle_url_via_call_back_to_g2_function = 
	    STATIC_SYMBOL("HANDLE-URL-VIA-CALL-BACK-TO-G2-FUNCTION",
	    AB_package);
    string_constant_5 = STATIC_STRING("serve from file system:");
    Qg2int_handle_url_via_file_system = 
	    STATIC_SYMBOL("HANDLE-URL-VIA-FILE-SYSTEM",AB_package);
    string_constant_6 = STATIC_STRING("serve internal status pages");
    Qg2int_handle_url_via_internal_pages = 
	    STATIC_SYMBOL("HANDLE-URL-VIA-INTERNAL-PAGES",AB_package);
    string_constant_7 = STATIC_STRING("forward to proxy server");
    Qg2int_handle_url_via_proxy_server = 
	    STATIC_SYMBOL("HANDLE-URL-VIA-PROXY-SERVER",AB_package);
    string_constant_8 = STATIC_STRING(":");
    Qg2int_text = STATIC_SYMBOL("TEXT",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qinteger,Qsymbol,Qg2int_text);
    string_constant_9 = STATIC_STRING(",");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_listener_socket_g2_struct = 
	    STATIC_SYMBOL("LISTENER-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_listener_socket = STATIC_SYMBOL("LISTENER-SOCKET",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_listener_socket_g2_struct,
	    Qg2int_listener_socket,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_listener_socket,
	    Qg2_defstruct_structure_name_listener_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_listener_socket == UNBOUND)
	G2int_the_type_description_of_listener_socket = Nil;
    string_constant_84 = 
	    STATIC_STRING("43Dy8l83My1o83My83Ly8m8k1l83Ly0000001m1m8o83Ly1n8n83=6y1l83=sykqk0k0");
    temp = G2int_the_type_description_of_listener_socket;
    G2int_the_type_description_of_listener_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_84));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_listener_socket_g2_struct,
	    G2int_the_type_description_of_listener_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_listener_socket,
	    G2int_the_type_description_of_listener_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_listener_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LISTENER-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_listener_sockets,
	    G2int_chain_of_available_listener_sockets);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_listener_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_listener_socket_count = STATIC_SYMBOL("LISTENER-SOCKET-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_listener_socket_count,
	    G2int_listener_socket_count);
    g2int_record_system_variable(Qg2int_listener_socket_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_listener_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_listener_socket,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_listener_socket,reclaim_structure_for_listener_socket);
    Kborn = STATIC_SYMBOL("BORN",Pkeyword);
    Qg2int_socket_listen = STATIC_SYMBOL("SOCKET-LISTEN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_socket_listen,
	    STATIC_FUNCTION(g2int_socket_listen,NIL,FALSE,1,1));
    Qg2int_m_socket_listen_listener_socket_1 = 
	    STATIC_SYMBOL("M-SOCKET-LISTEN-LISTENER-SOCKET-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_socket_listen_listener_socket_1,
	    STATIC_FUNCTION(g2int_m_socket_listen_listener_socket_1,NIL,
	    FALSE,2,2));
    set_get(Qg2int_socket_listen,Qg2int_listener_socket,
	    Qg2int_m_socket_listen_listener_socket_1);
    Qg2_defstruct_structure_name_server_thread_g2_struct = 
	    STATIC_SYMBOL("SERVER-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_server_thread = STATIC_SYMBOL("SERVER-THREAD",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_server_thread_g2_struct,
	    Qg2int_server_thread,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_server_thread,
	    Qg2_defstruct_structure_name_server_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_server_thread == UNBOUND)
	G2int_the_type_description_of_server_thread = Nil;
    string_constant_85 = 
	    STATIC_STRING("43Dy8l830oy1o830oy83Cy8m8k1l83Cy0000001m1m8o83Cy1n8n83=Ny0k3Fyk0k0");
    temp = G2int_the_type_description_of_server_thread;
    G2int_the_type_description_of_server_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_85));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_server_thread_g2_struct,
	    G2int_the_type_description_of_server_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_server_thread,
	    G2int_the_type_description_of_server_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_server_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SERVER-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_server_threads,
	    G2int_chain_of_available_server_threads);
    g2int_record_system_variable(Qg2int_chain_of_available_server_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_server_thread_count = STATIC_SYMBOL("SERVER-THREAD-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_server_thread_count,
	    G2int_server_thread_count);
    g2int_record_system_variable(Qg2int_server_thread_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_server_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_server_thread,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_server_thread,reclaim_structure_for_server_thread);
    Knew = STATIC_SYMBOL("NEW",Pkeyword);
    Kallocated = STATIC_SYMBOL("ALLOCATED",Pkeyword);
    Qg2int_null_thread_contour_wrapper = 
	    STATIC_SYMBOL("NULL-THREAD-CONTOUR-WRAPPER",AB_package);
    Qg2int_thread_feed_trace = STATIC_SYMBOL("THREAD-FEED-TRACE",AB_package);
    Qg2int_m_thread_feed_trace_server_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-FEED-TRACE-SERVER-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_feed_trace_server_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_feed_trace_server_thread_1,NIL,
	    FALSE,2,2));
    set_get(Qg2int_thread_feed_trace,Qg2int_server_thread,
	    Qg2int_m_thread_feed_trace_server_thread_1);
    if (G2int_the_http_server_threadqm == UNBOUND)
	G2int_the_http_server_threadqm = Nil;
    string_constant_10 = STATIC_STRING("Launching new HTTP server at ~D.");
    string_constant_11 = 
	    STATIC_STRING("but first shutting down old HTTP server.");
    Qg2int_http_server = STATIC_SYMBOL("HTTP-SERVER",AB_package);
    Krunnable = STATIC_SYMBOL("RUNNABLE",Pkeyword);
    Kinitializing = STATIC_SYMBOL("INITIALIZING",Pkeyword);
    Kstarted = STATIC_SYMBOL("STARTED",Pkeyword);
    Kquantum_in_progress = STATIC_SYMBOL("QUANTUM-IN-PROGRESS",Pkeyword);
    Kinitialize = STATIC_SYMBOL("INITIALIZE",Pkeyword);
    string_constant_12 = STATIC_STRING("Started HTTP server (port ~D).");
    Kcontinuation_taken_care_of = 
	    STATIC_SYMBOL("CONTINUATION-TAKEN-CARE-OF",Pkeyword);
    Knot_runnable = STATIC_SYMBOL("NOT-RUNNABLE",Pkeyword);
    Kio_wait = STATIC_SYMBOL("IO-WAIT",Pkeyword);
    Kcheck_for_clients = STATIC_SYMBOL("CHECK-FOR-CLIENTS",Pkeyword);
    Kcleanup = STATIC_SYMBOL("CLEANUP",Pkeyword);
    string_constant_13 = STATIC_STRING("Shutdown HTTP Server (port ~D).");
    Kshutdown_server = STATIC_SYMBOL("SHUTDOWN-SERVER",Pkeyword);
    Krunning = STATIC_SYMBOL("RUNNING",Pkeyword);
    string_constant_14 = STATIC_STRING("Problem with HTTP Server (issue: ~S)");
    Qg2int_mt_listen_for_server_requests = 
	    STATIC_SYMBOL("MT-LISTEN-FOR-SERVER-REQUESTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mt_listen_for_server_requests,
	    STATIC_FUNCTION(g2int_mt_listen_for_server_requests,NIL,FALSE,
	    0,0));
    Qg2int_unicode_utf_8 = STATIC_SYMBOL("UNICODE-UTF-8",AB_package);
    string_constant_86 = STATIC_STRING("utf-8");
    Qg2int_utf_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qg2int_unicode_utf_8,
	    string_constant_86,Qg2int_utf_8_gensym_string_with_crlf);
    Qg2int_us_ascii = STATIC_SYMBOL("US-ASCII",AB_package);
    string_constant_87 = STATIC_STRING("us-ascii");
    Qg2int_us_ascii_gensym_string_with_crlf = 
	    STATIC_SYMBOL("US-ASCII-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qg2int_us_ascii,
	    string_constant_87,Qg2int_us_ascii_gensym_string_with_crlf);
    Qg2int_latin_1 = STATIC_SYMBOL("LATIN-1",AB_package);
    string_constant_88 = STATIC_STRING("iso-8859-1");
    Qg2int_iso_8859_1_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qg2int_latin_1,
	    string_constant_88,Qg2int_iso_8859_1_gensym_string_with_crlf);
    Qg2int_latin_2 = STATIC_SYMBOL("LATIN-2",AB_package);
    string_constant_89 = STATIC_STRING("iso-8859-2");
    Qg2int_iso_8859_2_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-2-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qg2int_latin_2,
	    string_constant_89,Qg2int_iso_8859_2_gensym_string_with_crlf);
    Qg2int_latin_3 = STATIC_SYMBOL("LATIN-3",AB_package);
    string_constant_90 = STATIC_STRING("iso-8859-3");
    Qg2int_iso_8859_3_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-3-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qg2int_latin_3,
	    string_constant_90,Qg2int_iso_8859_3_gensym_string_with_crlf);
    Qg2int_latin_4 = STATIC_SYMBOL("LATIN-4",AB_package);
    string_constant_91 = STATIC_STRING("iso-8859-4");
    Qg2int_iso_8859_4_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-4-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qg2int_latin_4,
	    string_constant_91,Qg2int_iso_8859_4_gensym_string_with_crlf);
    Qg2int_latin_cyrillic = STATIC_SYMBOL("LATIN-CYRILLIC",AB_package);
    string_constant_92 = STATIC_STRING("iso-8859-5");
    Qg2int_iso_8859_5_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-5-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qg2int_latin_cyrillic,
	    string_constant_92,Qg2int_iso_8859_5_gensym_string_with_crlf);
    Qg2int_latin_arabic = STATIC_SYMBOL("LATIN-ARABIC",AB_package);
    string_constant_93 = STATIC_STRING("iso-8859-6");
    Qg2int_iso_8859_6_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-6-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qg2int_latin_arabic,
	    string_constant_93,Qg2int_iso_8859_6_gensym_string_with_crlf);
    Qg2int_latin_greek = STATIC_SYMBOL("LATIN-GREEK",AB_package);
    string_constant_94 = STATIC_STRING("iso-8859-7");
    Qg2int_iso_8859_7_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-7-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qg2int_latin_greek,
	    string_constant_94,Qg2int_iso_8859_7_gensym_string_with_crlf);
    Qg2int_latin_hebrew = STATIC_SYMBOL("LATIN-HEBREW",AB_package);
    string_constant_95 = STATIC_STRING("iso-8859-8");
    Qg2int_iso_8859_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-8-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qg2int_latin_hebrew,
	    string_constant_95,Qg2int_iso_8859_8_gensym_string_with_crlf);
    Qg2int_latin_5 = STATIC_SYMBOL("LATIN-5",AB_package);
    string_constant_96 = STATIC_STRING("iso-8859-9");
    Qg2int_iso_8859_9_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-9-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qg2int_latin_5,
	    string_constant_96,Qg2int_iso_8859_9_gensym_string_with_crlf);
    Qg2int_latin_6 = STATIC_SYMBOL("LATIN-6",AB_package);
    string_constant_97 = STATIC_STRING("iso-8859-10");
    Qg2int_iso_8859_10_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-10-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qg2int_latin_6,
	    string_constant_97,Qg2int_iso_8859_10_gensym_string_with_crlf);
    Qg2int_jis_euc = STATIC_SYMBOL("JIS-EUC",AB_package);
    string_constant_98 = STATIC_STRING("x-euc-jp");
    Qg2int_jis_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("JIS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qg2int_jis_euc,
	    string_constant_98,Qg2int_jis_euc_gensym_string_with_crlf);
    Qg2int_shift_jis = STATIC_SYMBOL("SHIFT-JIS",AB_package);
    string_constant_99 = STATIC_STRING("x-sjis");
    Qg2int_shift_jis_gensym_string_with_crlf = 
	    STATIC_SYMBOL("SHIFT-JIS-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qg2int_shift_jis,
	    string_constant_99,Qg2int_shift_jis_gensym_string_with_crlf);
    Qg2int_ksc_euc = STATIC_SYMBOL("KSC-EUC",AB_package);
    string_constant_100 = STATIC_STRING("euc-kr");
    Qg2int_ks_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("KS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qg2int_ksc_euc,
	    string_constant_100,Qg2int_ks_euc_gensym_string_with_crlf);
    list_constant_17 = STATIC_LIST((SI_Long)15L,list_constant_2,
	    list_constant_3,list_constant_4,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_8,
	    list_constant_9,list_constant_10,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16);
    if (G2int_charset_name_to_http_header_charset == UNBOUND)
	G2int_charset_name_to_http_header_charset = list_constant_17;
    Qg2int_invalid_charset_name = STATIC_SYMBOL("INVALID-CHARSET-NAME",
	    AB_package);
    string_constant_15 = STATIC_STRING("Unrecognized charset name.");
    Qg2int_default_default_http_header_charset_name = 
	    STATIC_SYMBOL("DEFAULT-DEFAULT-HTTP-HEADER-CHARSET-NAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_default_default_http_header_charset_name,
	    G2int_default_default_http_header_charset_name);
    SET_SYMBOL_VALUE(Qg2int_default_default_http_header_charset_name,
	    Qg2int_unicode_utf_8);
    Qg2int_default_http_header_charset_name = 
	    STATIC_SYMBOL("DEFAULT-HTTP-HEADER-CHARSET-NAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_default_http_header_charset_name,
	    G2int_default_http_header_charset_name);
    Qg2int_server = STATIC_SYMBOL("SERVER",AB_package);
    g2int_record_system_variable(Qg2int_default_http_header_charset_name,
	    Qg2int_server,Qg2int_unicode_utf_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_default = STATIC_SYMBOL("DEFAULT",AB_package);
    string_constant_16 = 
	    STATIC_STRING("Note: ~A is not valid for the -default-charset option. ~\n               ~%Legal charset names are: ~(~L,-~).");
    string_constant_17 = 
	    STATIC_STRING("Default charset for Gensym Weblink: ~a");
    Qg2int_command_line_process_default_charset = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DEFAULT-CHARSET",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_default_charset,
	    STATIC_FUNCTION(g2int_command_line_process_default_charset,NIL,
	    FALSE,1,1));
    Qg2int_default_charset = STATIC_SYMBOL("DEFAULT-CHARSET",AB_package);
    Qg2int_command_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    g2int_mutate_global_property(Qg2int_default_charset,
	    Qg2int_command_line_process_default_charset,
	    Qg2int_command_line_argument_processor);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qg2int_get_command_line_plist_element_for_default_charset = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEFAULT-CHARSET",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_default_charset,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_default_charset,
	    NIL,FALSE,0,0));
    Qg2int_command_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    g2int_mutate_global_property(Qg2int_default_charset,
	    Qg2int_get_command_line_plist_element_for_default_charset,
	    Qg2int_command_line_plist_element_getter);
    list_constant_19 = STATIC_CONS(Qg2int_default_charset,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_19,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2_defstruct_structure_name_http_client_thread_g2_struct = 
	    STATIC_SYMBOL("HTTP-CLIENT-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_http_client_thread = STATIC_SYMBOL("HTTP-CLIENT-THREAD",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_http_client_thread_g2_struct,
	    Qg2int_http_client_thread,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_http_client_thread,
	    Qg2_defstruct_structure_name_http_client_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_http_client_thread == UNBOUND)
	G2int_the_type_description_of_http_client_thread = Nil;
    string_constant_101 = 
	    STATIC_STRING("43Dy8l83-fy1o83-fy83Cy8m8k1l83Cy0000001m1m8o83Cy1n8n83=+y0k3Kyk0k0");
    temp = G2int_the_type_description_of_http_client_thread;
    G2int_the_type_description_of_http_client_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_101));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_http_client_thread_g2_struct,
	    G2int_the_type_description_of_http_client_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_http_client_thread,
	    G2int_the_type_description_of_http_client_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_http_client_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-HTTP-CLIENT-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_http_client_threads,
	    G2int_chain_of_available_http_client_threads);
    g2int_record_system_variable(Qg2int_chain_of_available_http_client_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_http_client_thread_count = 
	    STATIC_SYMBOL("HTTP-CLIENT-THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_http_client_thread_count,
	    G2int_http_client_thread_count);
    g2int_record_system_variable(Qg2int_http_client_thread_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_http_client_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_http_client_thread,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_http_client_thread,
	    reclaim_structure_for_http_client_thread);
    Kpending = STATIC_SYMBOL("PENDING",Pkeyword);
    string_constant_18 = STATIC_STRING("MIME-version");
    string_constant_19 = STATIC_STRING("1.0");
    Qg2int_m_thread_feed_trace_http_client_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-FEED-TRACE-HTTP-CLIENT-THREAD-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_feed_trace_http_client_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_feed_trace_http_client_thread_1,
	    NIL,FALSE,2,2));
    set_get(Qg2int_thread_feed_trace,Qg2int_http_client_thread,
	    Qg2int_m_thread_feed_trace_http_client_thread_1);
    Kcollect_first_line_of_query = 
	    STATIC_SYMBOL("COLLECT-FIRST-LINE-OF-QUERY",Pkeyword);
    Kbad = STATIC_SYMBOL("BAD",Pkeyword);
    string_constant_20 = STATIC_STRING("Ignoring malformed request.");
    Kwrap_up = STATIC_SYMBOL("WRAP-UP",Pkeyword);
    Kcollect_remainder_of_query = 
	    STATIC_SYMBOL("COLLECT-REMAINDER-OF-QUERY",Pkeyword);
    string_constant_21 = STATIC_STRING("Incomplete request.");
    Kdone = STATIC_SYMBOL("DONE",Pkeyword);
    Kexecute_query = STATIC_SYMBOL("EXECUTE-QUERY",Pkeyword);
    Kmalformed_request = STATIC_SYMBOL("MALFORMED-REQUEST",Pkeyword);
    Kbackward = STATIC_SYMBOL("BACKWARD",Pkeyword);
    Kfail = STATIC_SYMBOL("FAIL",Pkeyword);
    Kfinishing_passing_data = STATIC_SYMBOL("FINISHING-PASSING-DATA",Pkeyword);
    Keval_form = STATIC_SYMBOL("EVAL-FORM",Pkeyword);
    Qg2int_mt_serve_http_client = STATIC_SYMBOL("MT-SERVE-HTTP-CLIENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mt_serve_http_client,
	    STATIC_FUNCTION(g2int_mt_serve_http_client,NIL,FALSE,0,0));
    Keof = STATIC_SYMBOL("EOF",Pkeyword);
    if (G2int_count_of_number_of_http_clients == UNBOUND)
	G2int_count_of_number_of_http_clients = FIX((SI_Long)0L);
    Qg2int_http_client = STATIC_SYMBOL("HTTP-CLIENT",AB_package);
    string_constant_22 = STATIC_STRING(" \t\r");
    Qg2int_left_edge_of_mime_headers = 
	    STATIC_SYMBOL("LEFT-EDGE-OF-MIME-HEADERS",AB_package);
    Qg2int_right_edge_of_mime_headers = 
	    STATIC_SYMBOL("RIGHT-EDGE-OF-MIME-HEADERS",AB_package);
    string_constant_23 = STATIC_STRING("/");
    string_constant_24 = STATIC_STRING("HTTP/");
    string_constant_25 = STATIC_STRING(".");
    Qg2int_url_details_of_request = STATIC_SYMBOL("URL-DETAILS-OF-REQUEST",
	    AB_package);
    Qg2int_verb_of_request = STATIC_SYMBOL("VERB-OF-REQUEST",AB_package);
    Qg2int_protocol_of_request = STATIC_SYMBOL("PROTOCOL-OF-REQUEST",
	    AB_package);
    Krequest_header_fields = STATIC_SYMBOL("REQUEST-HEADER-FIELDS",Pkeyword);
    Qg2int_command_line_process_enable_hostname_lookups = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-ENABLE-HOSTNAME-LOOKUPS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_enable_hostname_lookups,
	    STATIC_FUNCTION(g2int_command_line_process_enable_hostname_lookups,
	    NIL,FALSE,1,1));
    Qg2int_enable_hostname_lookups = 
	    STATIC_SYMBOL("ENABLE-HOSTNAME-LOOKUPS",AB_package);
    g2int_mutate_global_property(Qg2int_enable_hostname_lookups,
	    Qg2int_command_line_process_enable_hostname_lookups,
	    Qg2int_command_line_argument_processor);
    array_constant_1 = STATIC_ARRAY(list_constant_18,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    Qg2int_get_command_line_plist_element_for_enable_hostname_lookups = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ENABLE-HOSTNAME-LOOKUPS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_enable_hostname_lookups,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_enable_hostname_lookups,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_enable_hostname_lookups,
	    Qg2int_get_command_line_plist_element_for_enable_hostname_lookups,
	    Qg2int_command_line_plist_element_getter);
    list_constant_20 = STATIC_CONS(Qg2int_enable_hostname_lookups,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_20,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    string_constant_26 = STATIC_STRING("GET");
    string_constant_27 = STATIC_STRING("The verb ~A is not supported.");
    Qg2int_form_for_resource_generation = 
	    STATIC_SYMBOL("FORM-FOR-RESOURCE-GENERATION",AB_package);
    Qg2int_http_client_host_name = STATIC_SYMBOL("HTTP-CLIENT-HOST-NAME",
	    AB_package);
    Qg2int_http_client_host_address = 
	    STATIC_SYMBOL("HTTP-CLIENT-HOST-ADDRESS",AB_package);
    Qg2int_fetch_id = STATIC_SYMBOL("FETCH-ID",AB_package);
    string_constant_28 = STATIC_STRING(", handling");
    string_constant_29 = STATIC_STRING(", malformed\?");
    string_constant_30 = STATIC_STRING(", Huh\?");
    string_constant_31 = STATIC_STRING("HTTP: ~A ~A \"~A\"~A");
    string_constant_32 = STATIC_STRING("<");
    string_constant_33 = STATIC_STRING("HTML");
    string_constant_34 = STATIC_STRING(">");
    string_constant_35 = STATIC_STRING("HEADER");
    string_constant_36 = STATIC_STRING("TITLE");
    string_constant_37 = STATIC_STRING("Error");
    string_constant_38 = STATIC_STRING("</");
    string_constant_39 = STATIC_STRING("BODY");
    string_constant_40 = STATIC_STRING("\r\n");
    string_constant_41 = STATIC_STRING("<P>");
    string_constant_42 = 
	    STATIC_STRING("The server was unable to handle your request for \"");
    string_constant_43 = STATIC_STRING("\".");
    string_constant_44 = STATIC_STRING("Unknown request for server data");
    SET_SYMBOL_FUNCTION(Qg2int_handle_url_via_internal_pages,
	    STATIC_FUNCTION(g2int_handle_url_via_internal_pages,NIL,FALSE,
	    0,0));
    Qg2int_current_fetch_ids = STATIC_SYMBOL("CURRENT-FETCH-IDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_fetch_ids,
	    G2int_current_fetch_ids);
    g2int_record_system_variable(Qg2int_current_fetch_ids,Qg2int_server,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_invalid_url_request_number = 
	    STATIC_SYMBOL("INVALID-URL-REQUEST-NUMBER",AB_package);
    string_constant_45 = 
	    STATIC_STRING("The URL request number does not denote a currently active request.");
    string_constant_46 = STATIC_STRING("Content-type");
    string_constant_47 = STATIC_STRING("charset=");
    Kadd_data = STATIC_SYMBOL("ADD-DATA",Pkeyword);
    string_constant_48 = STATIC_STRING("200 OK");
    Kend_data = STATIC_SYMBOL("END-DATA",Pkeyword);
    Kservice_the_reply_q = STATIC_SYMBOL("SERVICE-THE-REPLY-Q",Pkeyword);
    Ksocket_issue = STATIC_SYMBOL("SOCKET-ISSUE",Pkeyword);
    string_constant_49 = STATIC_STRING("ignoring event ~A");
    Kreturn = STATIC_SYMBOL("RETURN",Pkeyword);
    Qg2int_mt_eval_form_to_obtain_url = 
	    STATIC_SYMBOL("MT-EVAL-FORM-TO-OBTAIN-URL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mt_eval_form_to_obtain_url,
	    STATIC_FUNCTION(g2int_mt_eval_form_to_obtain_url,NIL,FALSE,0,0));
    Ksending_data = STATIC_SYMBOL("SENDING-DATA",Pkeyword);
    string_constant_50 = STATIC_STRING("Malformed CGI arguments.");
    string_constant_51 = STATIC_STRING("\?");
    string_constant_52 = STATIC_STRING("=");
    string_constant_53 = STATIC_STRING("&");
    Qg2int_cgi_arguments = STATIC_SYMBOL("CGI-ARGUMENTS",AB_package);
    Qg2int_search_part = STATIC_SYMBOL("SEARCH-PART",AB_package);
    Qg2int_cgi_routine_name = STATIC_SYMBOL("CGI-ROUTINE-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_url_via_call_back_to_g2_function,
	    STATIC_FUNCTION(g2int_handle_url_via_call_back_to_g2_function,
	    NIL,FALSE,3,3));
    string_constant_102 = STATIC_STRING("G2 WebLink");
    G2int_the_server_name = string_constant_102;
    string_constant_103 = STATIC_STRING("url-details");
    Qg2int_buffer_property = STATIC_SYMBOL("BUFFER-PROPERTY",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qg2int_buffer_property,
	    Qg2int_url_details_of_request);
    list_constant_25 = STATIC_CONS(string_constant_103,list_constant_21);
    string_constant_104 = STATIC_STRING("auth-type");
    Qg2int_tbd = STATIC_SYMBOL("TBD",AB_package);
    list_constant_22 = STATIC_CONS(Qg2int_tbd,Qnil);
    list_constant_26 = STATIC_CONS(string_constant_104,list_constant_22);
    string_constant_105 = STATIC_STRING("http-client-host-name");
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qg2int_buffer_property,
	    Qg2int_http_client_host_name);
    list_constant_27 = STATIC_CONS(string_constant_105,list_constant_23);
    string_constant_106 = STATIC_STRING("fetch-id");
    Qg2int_integer_buffer_property = 
	    STATIC_SYMBOL("INTEGER-BUFFER-PROPERTY",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)3L,string_constant_106,
	    Qg2int_integer_buffer_property,Qg2int_fetch_id);
    string_constant_107 = STATIC_STRING("remote-addr");
    list_constant_29 = STATIC_LIST((SI_Long)3L,string_constant_107,
	    Qg2int_buffer_property,Qg2int_http_client_host_address);
    string_constant_108 = STATIC_STRING("remote-host");
    list_constant_30 = STATIC_CONS(string_constant_108,list_constant_23);
    string_constant_109 = STATIC_STRING("remote-ident");
    list_constant_31 = STATIC_CONS(string_constant_109,list_constant_22);
    string_constant_110 = STATIC_STRING("remote-user");
    list_constant_32 = STATIC_CONS(string_constant_110,list_constant_22);
    string_constant_111 = STATIC_STRING("request-method");
    list_constant_33 = STATIC_LIST((SI_Long)3L,string_constant_111,
	    Qg2int_buffer_property,Qg2int_verb_of_request);
    string_constant_112 = STATIC_STRING("request-mime-headers");
    Qg2int_request_mime_headers = STATIC_SYMBOL("REQUEST-MIME-HEADERS",
	    AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,string_constant_112,
	    Qg2int_request_mime_headers);
    string_constant_113 = STATIC_STRING("path-info");
    list_constant_35 = STATIC_CONS(string_constant_113,list_constant_21);
    string_constant_114 = STATIC_STRING("path-translated");
    Qg2int_buffer_propertyqm = STATIC_SYMBOL("BUFFER-PROPERTY\?",AB_package);
    Qg2int_path_translatedqm = STATIC_SYMBOL("PATH-TRANSLATED\?",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)3L,string_constant_114,
	    Qg2int_buffer_propertyqm,Qg2int_path_translatedqm);
    string_constant_115 = STATIC_STRING("query-string");
    list_constant_37 = STATIC_LIST((SI_Long)3L,string_constant_115,
	    Qg2int_buffer_propertyqm,Qg2int_search_part);
    string_constant_116 = STATIC_STRING("script-name");
    list_constant_38 = STATIC_LIST((SI_Long)3L,string_constant_116,
	    Qg2int_buffer_propertyqm,Qg2int_cgi_routine_name);
    string_constant_117 = STATIC_STRING("server-name");
    Qg2int_server_name = STATIC_SYMBOL("SERVER-NAME",AB_package);
    list_constant_24 = STATIC_CONS(Qg2int_server_name,Qnil);
    list_constant_39 = STATIC_CONS(string_constant_117,list_constant_24);
    string_constant_118 = STATIC_STRING("server-port");
    Qg2int_server_port = STATIC_SYMBOL("SERVER-PORT",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,string_constant_118,
	    Qg2int_server_port);
    string_constant_119 = STATIC_STRING("server-protocol");
    Qg2int_constant = STATIC_SYMBOL("CONSTANT",AB_package);
    string_constant_120 = STATIC_STRING("HTTP/1.0");
    list_constant_41 = STATIC_LIST((SI_Long)3L,string_constant_119,
	    Qg2int_constant,string_constant_120);
    string_constant_121 = STATIC_STRING("server-software");
    list_constant_42 = STATIC_CONS(string_constant_121,list_constant_24);
    string_constant_122 = STATIC_STRING("gateway-interface");
    string_constant_123 = STATIC_STRING("CGI/1.1");
    list_constant_43 = STATIC_LIST((SI_Long)3L,string_constant_122,
	    Qg2int_constant,string_constant_123);
    string_constant_124 = STATIC_STRING("content-length");
    list_constant_44 = STATIC_CONS(string_constant_124,list_constant_22);
    string_constant_125 = STATIC_STRING("content-type");
    Qg2int_content_type = STATIC_SYMBOL("CONTENT-TYPE",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)2L,string_constant_125,
	    Qg2int_content_type);
    list_constant_1 = STATIC_LIST((SI_Long)21L,list_constant_25,
	    list_constant_26,list_constant_27,list_constant_28,
	    list_constant_29,list_constant_30,list_constant_31,
	    list_constant_32,list_constant_33,list_constant_34,
	    list_constant_35,list_constant_36,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44,list_constant_45);
    string_constant_54 = STATIC_STRING("");
    string_constant_55 = STATIC_STRING("~D");
    Qg2int_remap = STATIC_SYMBOL("REMAP",AB_package);
    string_constant_56 = STATIC_STRING("HEAD");
    string_constant_57 = STATIC_STRING("NOT-IMPLEMENTED");
    string_constant_58 = STATIC_STRING("UNKNOWN_METHOD_FOR_BUILDIN");
    string_constant_59 = STATIC_STRING("HTTP-");
    Qg2int_mimi_headers_from_server = 
	    STATIC_SYMBOL("MIMI-HEADERS-FROM-SERVER",AB_package);
    Qg2int_no_such_built_in_argument = 
	    STATIC_SYMBOL("NO-SUCH-BUILT-IN-ARGUMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_no_such_built_in_argument,
	    G2int_no_such_built_in_argument);
    string_constant_60 = STATIC_STRING("There is no such built in argument");
    Qg2int_utf_g_gensym_string = STATIC_SYMBOL("UTF-G-GENSYM-STRING",
	    AB_package);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_126 = STATIC_STRING("bin");
    string_constant_127 = STATIC_STRING("application/octet-stream");
    Qg2int_binary = STATIC_SYMBOL("BINARY",AB_package);
    list_constant_46 = STATIC_CONS(Qg2int_binary,Qnil);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)3L,string_constant_126,
	    string_constant_127,list_constant_46);
    string_constant_128 = STATIC_STRING("pdf");
    string_constant_129 = STATIC_STRING("application/pdf");
    list_constant_59 = STATIC_LIST_STAR((SI_Long)3L,string_constant_128,
	    string_constant_129,list_constant_46);
    string_constant_131 = STATIC_STRING("class");
    string_constant_130 = STATIC_STRING("application/java");
    list_constant_47 = STATIC_CONS(string_constant_130,list_constant_46);
    list_constant_60 = STATIC_CONS(string_constant_131,list_constant_47);
    string_constant_132 = STATIC_STRING("cla");
    list_constant_61 = STATIC_CONS(string_constant_132,list_constant_47);
    string_constant_134 = STATIC_STRING("ps");
    string_constant_133 = STATIC_STRING("application/postscript");
    Qg2int_8bit = STATIC_SYMBOL("8BIT",AB_package);
    list_constant_48 = STATIC_CONS(Qg2int_8bit,Qnil);
    list_constant_49 = STATIC_CONS(string_constant_133,list_constant_48);
    list_constant_62 = STATIC_CONS(string_constant_134,list_constant_49);
    string_constant_135 = STATIC_STRING("eps");
    list_constant_63 = STATIC_CONS(string_constant_135,list_constant_49);
    string_constant_137 = STATIC_STRING("snd");
    string_constant_136 = STATIC_STRING("audio/basic");
    list_constant_50 = STATIC_CONS(string_constant_136,list_constant_46);
    list_constant_64 = STATIC_CONS(string_constant_137,list_constant_50);
    string_constant_138 = STATIC_STRING("au");
    list_constant_65 = STATIC_CONS(string_constant_138,list_constant_50);
    string_constant_139 = STATIC_STRING("gif");
    string_constant_140 = STATIC_STRING("image/gif");
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,string_constant_139,
	    string_constant_140,list_constant_46);
    string_constant_142 = STATIC_STRING("jpg");
    string_constant_141 = STATIC_STRING("image/jpeg");
    list_constant_51 = STATIC_CONS(string_constant_141,list_constant_46);
    list_constant_67 = STATIC_CONS(string_constant_142,list_constant_51);
    string_constant_143 = STATIC_STRING("jpe");
    list_constant_68 = STATIC_CONS(string_constant_143,list_constant_51);
    string_constant_144 = STATIC_STRING("jpeg");
    list_constant_69 = STATIC_CONS(string_constant_144,list_constant_51);
    string_constant_146 = STATIC_STRING("tif");
    string_constant_145 = STATIC_STRING("image/tiff");
    list_constant_52 = STATIC_CONS(string_constant_145,list_constant_46);
    list_constant_70 = STATIC_CONS(string_constant_146,list_constant_52);
    string_constant_147 = STATIC_STRING("tiff");
    list_constant_71 = STATIC_CONS(string_constant_147,list_constant_52);
    string_constant_149 = STATIC_STRING("html");
    string_constant_148 = STATIC_STRING("text/html");
    list_constant_53 = STATIC_CONS(string_constant_148,list_constant_48);
    list_constant_72 = STATIC_CONS(string_constant_149,list_constant_53);
    string_constant_150 = STATIC_STRING("htm");
    list_constant_73 = STATIC_CONS(string_constant_150,list_constant_53);
    string_constant_151 = STATIC_STRING("c");
    string_constant_62 = STATIC_STRING("text/plain");
    Qg2int_7bit = STATIC_SYMBOL("7BIT",AB_package);
    list_constant_54 = STATIC_CONS(Qg2int_7bit,Qnil);
    list_constant_55 = STATIC_CONS(string_constant_62,list_constant_54);
    list_constant_74 = STATIC_CONS(string_constant_151,list_constant_55);
    string_constant_152 = STATIC_STRING("h");
    list_constant_75 = STATIC_CONS(string_constant_152,list_constant_55);
    string_constant_153 = STATIC_STRING("C");
    list_constant_76 = STATIC_CONS(string_constant_153,list_constant_55);
    string_constant_154 = STATIC_STRING("cc");
    list_constant_77 = STATIC_CONS(string_constant_154,list_constant_55);
    string_constant_155 = STATIC_STRING("hh");
    list_constant_78 = STATIC_CONS(string_constant_155,list_constant_55);
    string_constant_156 = STATIC_STRING("m");
    list_constant_79 = STATIC_CONS(string_constant_156,list_constant_55);
    string_constant_157 = STATIC_STRING("f90");
    list_constant_80 = STATIC_CONS(string_constant_157,list_constant_55);
    string_constant_158 = STATIC_STRING("txt");
    list_constant_81 = STATIC_CONS(string_constant_158,list_constant_55);
    string_constant_159 = STATIC_STRING("rtx");
    string_constant_160 = STATIC_STRING("text/richtext");
    list_constant_82 = STATIC_LIST_STAR((SI_Long)3L,string_constant_159,
	    string_constant_160,list_constant_54);
    string_constant_161 = STATIC_STRING("tsv");
    string_constant_162 = STATIC_STRING("text/tab-separated-values");
    list_constant_83 = STATIC_LIST_STAR((SI_Long)3L,string_constant_161,
	    string_constant_162,list_constant_54);
    string_constant_164 = STATIC_STRING("mpg");
    string_constant_163 = STATIC_STRING("video/mpeg");
    list_constant_56 = STATIC_CONS(string_constant_163,list_constant_46);
    list_constant_84 = STATIC_CONS(string_constant_164,list_constant_56);
    string_constant_165 = STATIC_STRING("mpe");
    list_constant_85 = STATIC_CONS(string_constant_165,list_constant_56);
    string_constant_166 = STATIC_STRING("mpeg");
    list_constant_86 = STATIC_CONS(string_constant_166,list_constant_56);
    string_constant_168 = STATIC_STRING("qt");
    string_constant_167 = STATIC_STRING("video/quicktime");
    list_constant_57 = STATIC_CONS(string_constant_167,list_constant_46);
    list_constant_87 = STATIC_CONS(string_constant_168,list_constant_57);
    string_constant_169 = STATIC_STRING("mov");
    list_constant_88 = STATIC_CONS(string_constant_169,list_constant_57);
    list_constant_89 = STATIC_LIST((SI_Long)31L,list_constant_58,
	    list_constant_59,list_constant_60,list_constant_61,
	    list_constant_62,list_constant_63,list_constant_64,
	    list_constant_65,list_constant_66,list_constant_67,
	    list_constant_68,list_constant_69,list_constant_70,
	    list_constant_71,list_constant_72,list_constant_73,
	    list_constant_74,list_constant_75,list_constant_76,
	    list_constant_77,list_constant_78,list_constant_79,
	    list_constant_80,list_constant_81,list_constant_82,
	    list_constant_83,list_constant_84,list_constant_85,
	    list_constant_86,list_constant_87,list_constant_88);
    G2int_default_file_type_to_mime_type_coersions = list_constant_89;
    G2int_newline_string = string_constant_40;
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
    Qg2int_win32 = STATIC_SYMBOL("WIN32",AB_package);
    string_constant_61 = STATIC_STRING("~A~A");
    Qg2int_unbound_in_protected_let = 
	    STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",AB_package);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_63 = 
	    STATIC_STRING("<H1>Error encountered generating URL<H1>\n");
    string_constant_64 = STATIC_STRING("Not found: ~S");
    string_constant_65 = STATIC_STRING("Resource not found.");
    SET_SYMBOL_FUNCTION(Qg2int_handle_url_via_file_system,
	    STATIC_FUNCTION(g2int_handle_url_via_file_system,NIL,FALSE,3,3));
    string_constant_66 = STATIC_STRING("HTTP/1.0 ");
    string_constant_67 = STATIC_STRING(": ");
    string_constant_68 = STATIC_STRING(";charset=");
    string_constant_69 = STATIC_STRING("Content-type: text/html;charset=");
    string_constant_70 = STATIC_STRING("404 Not Found");
    string_constant_71 = STATIC_STRING("<H1>Unable to provide URL</H1>\n");
    string_constant_170 = STATIC_STRING("overview.html");
    Qg2int_generate_overview_html = STATIC_SYMBOL("GENERATE-OVERVIEW-HTML",
	    AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)2L,string_constant_170,
	    Qg2int_generate_overview_html);
    list_constant_91 = STATIC_CONS(list_constant_90,Qnil);
    G2int_server_pages = list_constant_91;
    Qg2int_count_of_number_of_http_clients = 
	    STATIC_SYMBOL("COUNT-OF-NUMBER-OF-HTTP-CLIENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_number_of_http_clients,
	    G2int_count_of_number_of_http_clients);
    string_constant_171 = STATIC_STRING("~D HTTP Client requests");
    list_constant_92 = STATIC_LIST((SI_Long)2L,
	    Qg2int_count_of_number_of_http_clients,string_constant_171);
    list_constant_93 = STATIC_CONS(list_constant_92,Qnil);
    if (G2int_statistic_counters == UNBOUND)
	G2int_statistic_counters = list_constant_93;
    string_constant_72 = STATIC_STRING("Overview of Server Status");
    string_constant_73 = STATIC_STRING("H1");
    string_constant_74 = STATIC_STRING("GSI-Web The G2/Internet Bridge");
    string_constant_75 = STATIC_STRING("H2");
    string_constant_76 = STATIC_STRING("Version Information");
    string_constant_77 = STATIC_STRING("~S ");
    string_constant_78 = STATIC_STRING("Thread Information");
    string_constant_79 = STATIC_STRING("UL");
    string_constant_80 = STATIC_STRING("Statistics");
    string_constant_81 = STATIC_STRING("<LI>");
    SET_SYMBOL_FUNCTION(Qg2int_generate_overview_html,
	    STATIC_FUNCTION(g2int_generate_overview_html,NIL,FALSE,1,1));
    string_constant_82 = STATIC_STRING("~S/~S ~S ~S");
}
