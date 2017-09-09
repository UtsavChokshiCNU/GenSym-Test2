/* ps.c
 * Input file:  postscript.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ps.h"


Object Postscript_transparent_color_value = UNBOUND;

Object Postscript_header_array = UNBOUND;

Object Postscript_header_token_encodings = UNBOUND;

/* POSTSCRIPT-DECOMPRESS-HEADER-TOKEN */
Object postscript_decompress_header_token(letter)
    Object letter;
{
    x_note_fn_call(42,0);
    return VALUES_1(ISVREF(Postscript_header_token_encodings,
	    IFIX(FIXNUM_MINUS(CHAR_CODE(letter),FIX((SI_Long)65L)))));
}

DEFINE_VARIABLE_WITH_SYMBOL(Emit_postscript_line_length, Qemit_postscript_line_length);

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* POSTSCRIPT-DECODE-TEXT-INTO-GENSYM-STREAM */
Object postscript_decode_text_into_gensym_stream(text,gensym_stream)
    Object text, gensym_stream;
{
    Object delimeter_must_follow, emitting_vanilla_token, c, decoded_text;
    Object emit_postscript_line_length_new_value, incf_arg;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(42,1);
    delimeter_must_follow = Nil;
    emitting_vanilla_token = Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(text));
    c = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    c = CHR(ICHAR(text,i));
    if (UPPER_CASE_P(c)) {
	decoded_text = postscript_decompress_header_token(c);
	if (delimeter_must_follow &&  
		!TRUEP(emit_postscript_reserve_space(FIXNUM_ADD1(length(decoded_text)),
		gensym_stream))) {
	    emit_postscript_line_length_new_value = 
		    add1(Emit_postscript_line_length);
	    Emit_postscript_line_length = 
		    emit_postscript_line_length_new_value;
	    g2_stream_write_char(CHR(' '),gensym_stream);
	}
	incf_arg = length(decoded_text);
	emit_postscript_line_length_new_value = 
		add(Emit_postscript_line_length,incf_arg);
	Emit_postscript_line_length = emit_postscript_line_length_new_value;
	g2_stream_write_string(decoded_text,gensym_stream);
	emitting_vanilla_token = Nil;
	delimeter_must_follow = T;
    }
    else if (EQ(c,CHR('/'))) {
	emit_postscript_reserve_space(FIX((SI_Long)12L),gensym_stream);
	emit_postscript_line_length_new_value = 
		add1(Emit_postscript_line_length);
	Emit_postscript_line_length = emit_postscript_line_length_new_value;
	g2_stream_write_char(c,gensym_stream);
	emitting_vanilla_token = T;
	delimeter_must_follow = Nil;
    }
    else if (memq_function(c,list_constant)) {
	emit_postscript_reserve_space(FIX((SI_Long)1L),gensym_stream);
	emit_postscript_line_length_new_value = 
		add1(Emit_postscript_line_length);
	Emit_postscript_line_length = emit_postscript_line_length_new_value;
	g2_stream_write_char(c,gensym_stream);
	emitting_vanilla_token = Nil;
	delimeter_must_follow = Nil;
    }
    else if (EQ(c,CHR('\n'))) {
	emit_postscript_line_length_new_value = 
		add1(Emit_postscript_line_length);
	Emit_postscript_line_length = emit_postscript_line_length_new_value;
	g2_stream_write_char(CHR(' '),gensym_stream);
    }
    else if (memq_function(c,list_constant_1)) {
	if ( !TRUEP(emit_postscript_reserve_space(FIX((SI_Long)1L),
		gensym_stream))) {
	    emit_postscript_line_length_new_value = 
		    add1(Emit_postscript_line_length);
	    Emit_postscript_line_length = 
		    emit_postscript_line_length_new_value;
	    g2_stream_write_char(c,gensym_stream);
	}
	emitting_vanilla_token = Nil;
	delimeter_must_follow = Nil;
    }
    else {
	if (EQ(CHR('@'),c)) {
	    i = i + (SI_Long)1L;
	    c = CHR(ICHAR(text,i));
	}
	if ( !TRUEP(emitting_vanilla_token) && delimeter_must_follow &&  
		!TRUEP(emit_postscript_reserve_space(FIX((SI_Long)1L),
		gensym_stream))) {
	    emit_postscript_line_length_new_value = 
		    add1(Emit_postscript_line_length);
	    Emit_postscript_line_length = 
		    emit_postscript_line_length_new_value;
	    g2_stream_write_char(CHR(' '),gensym_stream);
	}
	emit_postscript_line_length_new_value = 
		add1(Emit_postscript_line_length);
	Emit_postscript_line_length = emit_postscript_line_length_new_value;
	g2_stream_write_char(c,gensym_stream);
	emitting_vanilla_token = T;
	delimeter_must_follow = T;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Printing_stream, Qprinting_stream);

static Object string_constant;     /* "%%BeginProlog" */

static Object string_constant_1;   /* "%%BeginResource: procset ab-header-3-0" */

static Object string_constant_2;   /* "/ab-dict 495 dict def ab-dict begin" */

static Object string_constant_3;   /* "end" */

static Object string_constant_4;   /* "%%EndResource: procset ab-header-3-0" */

static Object string_constant_5;   /* "%%EndProlog" */

static Object string_constant_6;   /* "~%%%BeginSetup" */

static Object string_constant_7;   /* "~%%%IncludeResource: font Helvetica" */

static Object string_constant_8;   /* "~%ab-dict begin~%" */

static Object string_constant_9;   /* "~%setup-blob-font~%" */

/* EMIT-POSTSCRIPT-PROLOG */
Object emit_postscript_prolog(paper_size,eps_qm)
    Object paper_size, eps_qm;
{
    Object encoded_text;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(42,2);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Postscript_header_array));
    encoded_text = Nil;
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant,Printing_stream);
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant_1,Printing_stream);
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant_2,Printing_stream);
    Emit_postscript_line_length = FIX((SI_Long)0L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    encoded_text = aref1(Postscript_header_array,FIX(i));
    if ( !TRUEP(encoded_text))
	goto end_loop;
    postscript_decode_text_into_gensym_stream(encoded_text,Printing_stream);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    emit_printing_color_map();
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant_3,Printing_stream);
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant_4,Printing_stream);
    g2_stream_terpri(Printing_stream);
    g2_stream_write_string(string_constant_5,Printing_stream);
    if ( !TRUEP(eps_qm))
	emit_paper_tray(paper_size);
    g2_stream_terpri(Printing_stream);
    pformat(1,string_constant_6);
    pformat(1,string_constant_7);
    pformat(1,string_constant_8);
    return pformat(1,string_constant_9);
}

static Object string_constant_10;  /* "~%~%statusdict begin~%" */

static Object string_constant_11;  /* "~({~atray} stopped {{~a} stopped pop} if~)~%" */

static Object string_constant_12;  /* "end~%" */

/* EMIT-PAPER-TRAY */
Object emit_paper_tray(paper_size)
    Object paper_size;
{
    x_note_fn_call(42,3);
    pformat(1,string_constant_10);
    pformat(3,string_constant_11,paper_size,paper_size);
    return pformat(1,string_constant_12);
}

Object Postscript_macro_function_prop = UNBOUND;

void postscript_INIT()
{
    Object Qpostscript_macro_function, AB_package, array_constant;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13;

    x_note_fn_call(42,4);
    SET_PACKAGE("AB");
    Postscript_transparent_color_value = FIX((SI_Long)-1L);
    Postscript_header_array = make_array(1,FIX((SI_Long)100L));
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)25L));
    string_constant_13 = STATIC_STRING("$bv");
    string_constant_14 = STATIC_STRING("def");
    string_constant_15 = STATIC_STRING("$ec");
    string_constant_16 = STATIC_STRING("$bm");
    string_constant_17 = STATIC_STRING("$q");
    string_constant_18 = STATIC_STRING("$o");
    string_constant_19 = STATIC_STRING("$bh");
    string_constant_20 = STATIC_STRING("$bj");
    string_constant_21 = STATIC_STRING("lineto");
    string_constant_22 = STATIC_STRING("$bg");
    string_constant_23 = STATIC_STRING("$bi");
    string_constant_24 = STATIC_STRING("mul");
    string_constant_25 = STATIC_STRING("$ct");
    string_constant_26 = STATIC_STRING("$ch");
    string_constant_27 = STATIC_STRING("$f");
    string_constant_28 = STATIC_STRING("$i");
    string_constant_29 = STATIC_STRING("moveto");
    string_constant_30 = STATIC_STRING("$eh");
    string_constant_31 = STATIC_STRING("translate");
    string_constant_32 = STATIC_STRING("$j");
    string_constant_33 = STATIC_STRING("$t");
    string_constant_34 = STATIC_STRING("scalefont");
    string_constant_35 = STATIC_STRING("_x1");
    string_constant_36 = STATIC_STRING("$a");
    string_constant_37 = STATIC_STRING("$di");
    ISASET_1(array_constant,(SI_Long)0L,string_constant_13);
    ISASET_1(array_constant,(SI_Long)1L,string_constant_14);
    ISASET_1(array_constant,(SI_Long)2L,string_constant_15);
    ISASET_1(array_constant,(SI_Long)3L,string_constant_16);
    ISASET_1(array_constant,(SI_Long)4L,string_constant_17);
    ISASET_1(array_constant,(SI_Long)5L,string_constant_18);
    ISASET_1(array_constant,(SI_Long)6L,string_constant_19);
    ISASET_1(array_constant,(SI_Long)7L,string_constant_20);
    ISASET_1(array_constant,(SI_Long)8L,string_constant_21);
    ISASET_1(array_constant,(SI_Long)9L,string_constant_22);
    ISASET_1(array_constant,(SI_Long)10L,string_constant_23);
    ISASET_1(array_constant,(SI_Long)11L,string_constant_24);
    ISASET_1(array_constant,(SI_Long)12L,string_constant_25);
    ISASET_1(array_constant,(SI_Long)13L,string_constant_26);
    ISASET_1(array_constant,(SI_Long)14L,string_constant_27);
    ISASET_1(array_constant,(SI_Long)15L,string_constant_28);
    ISASET_1(array_constant,(SI_Long)16L,string_constant_29);
    ISASET_1(array_constant,(SI_Long)17L,string_constant_30);
    ISASET_1(array_constant,(SI_Long)18L,string_constant_31);
    ISASET_1(array_constant,(SI_Long)19L,string_constant_32);
    ISASET_1(array_constant,(SI_Long)20L,string_constant_33);
    ISASET_1(array_constant,(SI_Long)21L,string_constant_34);
    ISASET_1(array_constant,(SI_Long)22L,string_constant_35);
    ISASET_1(array_constant,(SI_Long)23L,string_constant_36);
    ISASET_1(array_constant,(SI_Long)24L,string_constant_37);
    Postscript_header_token_encodings = array_constant;
    list_constant = STATIC_LIST((SI_Long)3L,CHR('{'),CHR('}'),CHR('/'));
    list_constant_1 = STATIC_LIST((SI_Long)2L,CHR(' '),CHR('\t'));
    string_constant = STATIC_STRING("%%BeginProlog");
    string_constant_1 = 
	    STATIC_STRING("%%BeginResource: procset ab-header-3-0");
    string_constant_2 = STATIC_STRING("/ab-dict 495 dict def ab-dict begin");
    string_constant_3 = STATIC_STRING("end");
    string_constant_4 = STATIC_STRING("%%EndResource: procset ab-header-3-0");
    string_constant_5 = STATIC_STRING("%%EndProlog");
    string_constant_6 = STATIC_STRING("~%%%BeginSetup");
    string_constant_7 = STATIC_STRING("~%%%IncludeResource: font Helvetica");
    string_constant_8 = STATIC_STRING("~%ab-dict begin~%");
    string_constant_9 = STATIC_STRING("~%setup-blob-font~%");
    string_constant_10 = STATIC_STRING("~%~%statusdict begin~%");
    string_constant_11 = 
	    STATIC_STRING("~({~atray} stopped {{~a} stopped pop} if~)~%");
    string_constant_12 = STATIC_STRING("end~%");
    AB_package = STATIC_PACKAGE("AB");
    Qpostscript_macro_function = STATIC_SYMBOL("POSTSCRIPT-MACRO-FUNCTION",
	    AB_package);
    Postscript_macro_function_prop = Qpostscript_macro_function;
}
