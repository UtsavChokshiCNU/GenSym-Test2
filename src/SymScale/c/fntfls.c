/* fntfls.c
 * Input file:  font-files.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "fntfls.h"


Object Asian_font_reading_information = UNBOUND;

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object list_constant;       /* # */

/* GET-FONT-FILE-DIRECTORY-PATHNAME */
Object get_font_file_directory_pathname()
{
    Object thing, filename_from_launch_environment_qm, pathname_1;

    x_note_fn_call(138,0);
    thing = get_command_line_keyword_argument(1,array_constant);
    filename_from_launch_environment_qm = 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    copy_text_string(thing) : thing;
    if (filename_from_launch_environment_qm);
    else
	filename_from_launch_environment_qm = 
		get_gensym_environment_variable(array_constant_1);
    if (filename_from_launch_environment_qm) {
	pathname_1 = 
		get_new_directory_pathname_dwim(filename_from_launch_environment_qm);
	if (pathname_1);
	else
	    pathname_1 = make_empty_gensym_pathname();
    }
    else
	pathname_1 = gensym_make_pathname_with_copied_components(Nil,Nil,
		list_constant,Nil,Nil,Nil,Nil);
    if (filename_from_launch_environment_qm)
	reclaim_text_string(filename_from_launch_environment_qm);
    return VALUES_1(pathname_1);
}

static Object Kall;                /* :all */

/* GET-ASIAN-FONT-FILE-NAME */
Object get_asian_font_file_name(asian_font_name)
    Object asian_font_name;
{
    Object temp, gensymed_symbol, default_filename_variable, keyword;
    Object keyword_as_uppercase_string;

    x_note_fn_call(138,1);
    temp = assq_function(asian_font_name,Asian_font_reading_information);
    gensymed_symbol = CDR(temp);
    default_filename_variable = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    keyword = CAR(gensymed_symbol);
    temp = get_command_line_keyword_argument(1,keyword);
    if (temp);
    else {
	keyword_as_uppercase_string = 
		copy_text_string_with_case_conversion(keyword,Kall);
	temp = get_gensym_environment_variable(keyword_as_uppercase_string);
	reclaim_text_string(keyword_as_uppercase_string);
    }
    if (temp);
    else
	temp = SYMBOL_VALUE(default_filename_variable);
    temp = get_font_file_name(temp);
    return VALUES_1(temp);
}

static Object string_constant;     /* "~(~a~).ttf" */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* GET-FONT-FILE-NAME */
Object get_font_file_name(basic_font_file_name)
    Object basic_font_file_name;
{
    Object basic_namestring, font_file_directory_pathname_qm, temp, temp_1;
    Object series, thing, ab_loop_list_, gensym_pathname_1;

    x_note_fn_call(138,2);
    basic_namestring = SYMBOLP(basic_font_file_name) ? 
	    tformat_text_string(2,string_constant,basic_font_file_name) : 
	    copy_text_string(basic_font_file_name);
    font_file_directory_pathname_qm = get_font_file_directory_pathname();
    temp = gensym_cons_1(basic_namestring,Nil);
    temp_1 = font_file_directory_pathname_qm ? 
	    gensym_cons_1(font_file_directory_pathname_qm,Nil) : Nil;
    series = nconc2(temp,nconc2(temp_1,Process_specific_system_pathname ? 
	    gensym_cons_1(copy_gensym_pathname(Process_specific_system_pathname),
	    Nil) : Nil));
    temp_1 = merge_series_of_pathnames(series);
    thing = Nil;
    ab_loop_list_ = series;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    thing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	reclaim_gensym_pathname(thing);
    else if (text_string_p(thing))
	reclaim_text_string(thing);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(series);
    gensym_pathname_1 = temp_1;
    temp_1 = gensym_namestring(1,gensym_pathname_1);
    reclaim_gensym_pathname(gensym_pathname_1);
    return VALUES_1(temp_1);
}

Object Kanji16_font_filename = UNBOUND;

Object Kanji24_font_filename = UNBOUND;

Object Kanji_star_font_filename = UNBOUND;

Object Minm_star_font_filename = UNBOUND;

Object Hangul16_font_filename = UNBOUND;

Object Hangul24_font_filename = UNBOUND;

Object Hangul_star_font_filename = UNBOUND;

Object Hangulttf_font_filename = UNBOUND;

Object Chinesettf_font_filename = UNBOUND;

void font_files_INIT()
{
    Object string_constant_17, Qchinesettf_font_filename, string_constant_16;
    Object Qhangulttf_font_filename, string_constant_12;
    Object Qhangul_star_font_filename, string_constant_15;
    Object Qhangul24_font_filename, string_constant_14;
    Object Qhangul16_font_filename, string_constant_13;
    Object Qminm_star_font_filename, Qkanji_star_font_filename;
    Object string_constant_11, Qkanji24_font_filename, string_constant_10;
    Object Qkanji16_font_filename, Qget_font_file_name, AB_package;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qget_asian_font_file_name;
    Object Krelative, list_constant_14, list_constant_13, list_constant_12;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_8, list_constant_7, list_constant_6, list_constant_5;
    Object list_constant_4, list_constant_2, Qminm, string_constant_9, Qkanji;
    Object string_constant_8, Qkanji24, string_constant_7, Qkanji16;
    Object string_constant_6, Qchinese, string_constant_5, Qchinesettf;
    Object list_constant_3, string_constant_4, Qhangulttf, string_constant_3;
    Object Qhangul, list_constant_1, string_constant_2, Qhangul24;
    Object string_constant_1, Qhangul16, Qksc_to_gensym_ksc;

    x_note_fn_call(138,3);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhangul16 = STATIC_SYMBOL("HANGUL16",AB_package);
    Qhangul16_font_filename = STATIC_SYMBOL("HANGUL16-FONT-FILENAME",
	    AB_package);
    string_constant_1 = STATIC_STRING("hangul16-font");
    Qkanji16 = STATIC_SYMBOL("KANJI16",AB_package);
    Qksc_to_gensym_ksc = STATIC_SYMBOL("KSC-TO-GENSYM-KSC",AB_package);
    SET_SYMBOL_FUNCTION(Qksc_to_gensym_ksc,
	    STATIC_FUNCTION(ksc_to_gensym_ksc,NIL,FALSE,1,1));
    list_constant_1 = STATIC_CONS(Qksc_to_gensym_ksc,Qnil);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)5L,Qhangul16,
	    Qhangul16_font_filename,string_constant_1,Qkanji16,
	    list_constant_1);
    Qhangul24 = STATIC_SYMBOL("HANGUL24",AB_package);
    Qhangul24_font_filename = STATIC_SYMBOL("HANGUL24-FONT-FILENAME",
	    AB_package);
    string_constant_2 = STATIC_STRING("hangul24-font");
    Qkanji24 = STATIC_SYMBOL("KANJI24",AB_package);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)5L,Qhangul24,
	    Qhangul24_font_filename,string_constant_2,Qkanji24,
	    list_constant_1);
    Qhangul = STATIC_SYMBOL("HANGUL",AB_package);
    Qhangul_star_font_filename = STATIC_SYMBOL("HANGUL_*-FONT-FILENAME",
	    AB_package);
    string_constant_3 = STATIC_STRING("hangul_fontfile");
    list_constant_2 = STATIC_CONS(Qnil,Qnil);
    list_constant_3 = STATIC_CONS(Qhangul,list_constant_2);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)4L,Qhangul,
	    Qhangul_star_font_filename,string_constant_3,list_constant_3);
    Qhangulttf = STATIC_SYMBOL("HANGULTTF",AB_package);
    Qhangulttf_font_filename = STATIC_SYMBOL("HANGULTTF-FONT-FILENAME",
	    AB_package);
    string_constant_4 = STATIC_STRING("hangulttf_fontfile");
    list_constant_7 = STATIC_LIST_STAR((SI_Long)4L,Qhangulttf,
	    Qhangulttf_font_filename,string_constant_4,list_constant_3);
    Qchinesettf = STATIC_SYMBOL("CHINESETTF",AB_package);
    Qchinesettf_font_filename = STATIC_SYMBOL("CHINESETTF-FONT-FILENAME",
	    AB_package);
    string_constant_5 = STATIC_STRING("chinesettf_fontfile");
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)5L,Qchinesettf,
	    Qchinesettf_font_filename,string_constant_5,Qchinese,
	    list_constant_2);
    Qkanji16_font_filename = STATIC_SYMBOL("KANJI16-FONT-FILENAME",AB_package);
    string_constant_6 = STATIC_STRING("kanji16-font");
    list_constant_9 = STATIC_LIST_STAR((SI_Long)5L,Qkanji16,
	    Qkanji16_font_filename,string_constant_6,Qkanji16,list_constant_2);
    Qkanji24_font_filename = STATIC_SYMBOL("KANJI24-FONT-FILENAME",AB_package);
    string_constant_7 = STATIC_STRING("kanji24-font");
    list_constant_10 = STATIC_LIST_STAR((SI_Long)5L,Qkanji24,
	    Qkanji24_font_filename,string_constant_7,Qkanji24,list_constant_2);
    Qkanji = STATIC_SYMBOL("KANJI",AB_package);
    Qkanji_star_font_filename = STATIC_SYMBOL("KANJI_*-FONT-FILENAME",
	    AB_package);
    string_constant_8 = STATIC_STRING("kanji_fontfile");
    list_constant_11 = STATIC_LIST_STAR((SI_Long)5L,Qkanji,
	    Qkanji_star_font_filename,string_constant_8,Qkanji,
	    list_constant_2);
    Qminm = STATIC_SYMBOL("MINM",AB_package);
    Qminm_star_font_filename = STATIC_SYMBOL("MINM_*-FONT-FILENAME",
	    AB_package);
    string_constant_9 = STATIC_STRING("minm_fontfile");
    list_constant_12 = STATIC_LIST_STAR((SI_Long)5L,Qminm,
	    Qminm_star_font_filename,string_constant_9,Qminm,list_constant_2);
    list_constant_13 = STATIC_LIST((SI_Long)9L,list_constant_4,
	    list_constant_5,list_constant_6,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12);
    Asian_font_reading_information = list_constant_13;
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,Krelative,array_constant);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qget_asian_font_file_name = STATIC_SYMBOL("GET-ASIAN-FONT-FILE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_asian_font_file_name,
	    STATIC_FUNCTION(get_asian_font_file_name,NIL,FALSE,1,1));
    string_constant = STATIC_STRING("~(~a~).ttf");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qget_font_file_name = STATIC_SYMBOL("GET-FONT-FILE-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qget_font_file_name,
	    STATIC_FUNCTION(get_font_file_name,NIL,FALSE,1,1));
    SET_SYMBOL_VALUE_LOCATION(Qkanji16_font_filename,Kanji16_font_filename);
    string_constant_10 = STATIC_STRING("kanji16.gf");
    Kanji16_font_filename = string_constant_10;
    SET_SYMBOL_VALUE_LOCATION(Qkanji24_font_filename,Kanji24_font_filename);
    string_constant_11 = STATIC_STRING("kanji24.gf");
    Kanji24_font_filename = string_constant_11;
    SET_SYMBOL_VALUE_LOCATION(Qkanji_star_font_filename,
	    Kanji_star_font_filename);
    string_constant_12 = STATIC_STRING("*.gb");
    Kanji_star_font_filename = string_constant_12;
    SET_SYMBOL_VALUE_LOCATION(Qminm_star_font_filename,
	    Minm_star_font_filename);
    string_constant_13 = STATIC_STRING("*.spd");
    Minm_star_font_filename = string_constant_13;
    SET_SYMBOL_VALUE_LOCATION(Qhangul16_font_filename,Hangul16_font_filename);
    string_constant_14 = STATIC_STRING("hangul16.gf");
    Hangul16_font_filename = string_constant_14;
    SET_SYMBOL_VALUE_LOCATION(Qhangul24_font_filename,Hangul24_font_filename);
    string_constant_15 = STATIC_STRING("hangul24.gf");
    Hangul24_font_filename = string_constant_15;
    SET_SYMBOL_VALUE_LOCATION(Qhangul_star_font_filename,
	    Hangul_star_font_filename);
    Hangul_star_font_filename = string_constant_12;
    SET_SYMBOL_VALUE_LOCATION(Qhangulttf_font_filename,
	    Hangulttf_font_filename);
    string_constant_16 = STATIC_STRING("hangul.ttf");
    Hangulttf_font_filename = string_constant_16;
    SET_SYMBOL_VALUE_LOCATION(Qchinesettf_font_filename,
	    Chinesettf_font_filename);
    string_constant_17 = STATIC_STRING("chinese.ttf");
    Chinesettf_font_filename = string_constant_17;
}
