/* flprse.c
 * Input file:  file-parse.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "flprse.h"


Object G2int_filename_special_character_registry = UNBOUND;

Object G2int_ltend_of_sequencegt = UNBOUND;

Object G2int_ltcolongt = UNBOUND;

Object G2int_ltslashgt = UNBOUND;

Object G2int_ltdotgt = UNBOUND;

Object G2int_lttildegt = UNBOUND;

Object G2int_ltasteriskgt = UNBOUND;

Object G2int_ltleft_bracketgt = UNBOUND;

Object G2int_ltright_bracketgt = UNBOUND;

Object G2int_ltsemicolongt = UNBOUND;

Object G2int_ltdouble_quotegt = UNBOUND;

Object G2int_ltspacegt = UNBOUND;

Object G2int_lthyphengt = UNBOUND;

Object G2int_ltleft_angle_bracketgt = UNBOUND;

Object G2int_ltright_angle_bracketgt = UNBOUND;

Object G2int_ltsharp_signgt = UNBOUND;

Object G2int_ltexclamationgt = UNBOUND;

Object G2int_ltcommagt = UNBOUND;

Object G2int_ltbackslashgt = UNBOUND;

static Object Kcase_sensitive;     /* :case-sensitive */

static Object Kall_uppercase;      /* :all-uppercase */

static Object Kall_lowercase;      /* :all-lowercase */

static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

static Object Qg2int_ltend_of_sequencegt;  /* <end-of-sequence> */

/* TOKENIZE-FILENAME */
Object g2int_tokenize_filename varargs_1(int, n)
{
    Object filename, special_characters;
    Object character_case_mode, text_string_copy, private_filename;
    Object tokenized_filename, entry, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, special_character_registry, char_1;
    Object accumulated_chars, special_character_entry;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object accumulated_char, thing, temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long index_1, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(33,0);
    INIT_ARGS_nonrelocating();
    filename = REQUIRED_ARG_nonrelocating();
    special_characters = REQUIRED_ARG_nonrelocating();
    character_case_mode = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Kcase_sensitive;
    END_ARGS_nonrelocating();
    text_string_copy = g2int_copy_text_string(filename);
    if (EQ(character_case_mode,Kcase_sensitive))
	private_filename = text_string_copy;
    else if (EQ(character_case_mode,Kall_uppercase))
	private_filename = g2int_nstring_upcasew(text_string_copy);
    else if (EQ(character_case_mode,Kall_lowercase))
	private_filename = g2int_nstring_downcasew(text_string_copy);
    else
	private_filename = Qnil;
    tokenized_filename = Nil;
    entry = Nil;
    ab_loop_list_ = G2int_filename_special_character_registry;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (g2int_wide_character_member(CAR(entry),special_characters)) {
	ab_loopvar__2 = g2int_gensym_cons_1(entry,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    special_character_registry = ab_loopvar_;
    goto end;
    special_character_registry = Qnil;
  end:;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(g2int_lengthw(private_filename));
    char_1 = Nil;
    accumulated_chars = Nil;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    char_1 = FIX(UBYTE_16_ISAREF_1(private_filename,index_1));
    special_character_entry = g2int_wide_character_rassoc(char_1,
	    special_character_registry);
    if (special_character_entry) {
	if (accumulated_chars) {
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
		      accumulated_char = Nil;
		      accumulated_chars = nreverse(accumulated_chars);
		      ab_loop_list_ = accumulated_chars;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      accumulated_char = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (EQ(G2int_current_twriting_output_type,
			      Qg2int_wide_string)) {
			  thing = accumulated_char;
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
			  thing = accumulated_char;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			  G2int_fill_pointer_for_current_gensym_string = temp;
		      }
		      goto next_loop_2;
		    end_loop_2:;
		      temp_1 = g2int_copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    tokenized_filename = g2int_gensym_cons_1(temp_1,
		    tokenized_filename);
	    g2int_reclaim_gensym_list_1(accumulated_chars);
	    accumulated_chars = Nil;
	}
	tokenized_filename = 
		g2int_gensym_cons_1(CAR(special_character_entry),
		tokenized_filename);
    }
    else
	accumulated_chars = g2int_gensym_cons_1(char_1,accumulated_chars);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    if (accumulated_chars) {
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
		  accumulated_char = Nil;
		  accumulated_chars = nreverse(accumulated_chars);
		  ab_loop_list_ = accumulated_chars;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  accumulated_char = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (EQ(G2int_current_twriting_output_type,
			  Qg2int_wide_string)) {
		      thing = accumulated_char;
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
		      thing = accumulated_char;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		      G2int_fill_pointer_for_current_gensym_string = temp;
		  }
		  goto next_loop_3;
		end_loop_3:;
		  temp_1 = g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	tokenized_filename = g2int_gensym_cons_1(temp_1,tokenized_filename);
	g2int_reclaim_gensym_list_1(accumulated_chars);
    }
    g2int_reclaim_gensym_list_1(special_character_registry);
    g2int_reclaim_text_string(private_filename);
    return nreverse(g2int_gensym_cons_1(Qg2int_ltend_of_sequencegt,
	    tokenized_filename));
    return VALUES_1(Qnil);
}

Object G2int_trace_filename_parsing_p = UNBOUND;

Object G2int_the_type_description_of_filename_parser_information = UNBOUND;

Object G2int_chain_of_available_filename_parser_informations = UNBOUND;

Object G2int_filename_parser_information_count = UNBOUND;

/* RECLAIM-FILENAME-PARSER-INFORMATION-INTERNAL-1 */
Object g2int_reclaim_filename_parser_information_internal_1(filename_parser_information)
    Object filename_parser_information;
{
    Object svref_new_value;

    x_note_fn_call(33,1);
    inline_note_reclaim_cons(filename_parser_information,Nil);
    svref_new_value = G2int_chain_of_available_filename_parser_informations;
    SVREF(filename_parser_information,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_filename_parser_informations = 
	    filename_parser_information;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FILENAME-PARSER-INFORMATION */
Object g2int_reclaim_structure_for_filename_parser_information(filename_parser_information)
    Object filename_parser_information;
{
    x_note_fn_call(33,2);
    return g2int_reclaim_filename_parser_information_internal_1(filename_parser_information);
}

static Object Qg2_defstruct_structure_name_filename_parser_information_g2_struct;  /* g2-defstruct-structure-name::filename-parser-information-g2-struct */

/* MAKE-PERMANENT-FILENAME-PARSER-INFORMATION-STRUCTURE-INTERNAL */
Object g2int_make_permanent_filename_parser_information_structure_internal()
{
    Object def_structure_filename_parser_information_variable;
    Object filename_parser_information_count_new_value;
    Object defstruct_g2_filename_parser_information_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,3);
    def_structure_filename_parser_information_variable = Nil;
    filename_parser_information_count_new_value = 
	    FIXNUM_ADD1(G2int_filename_parser_information_count);
    G2int_filename_parser_information_count = 
	    filename_parser_information_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_filename_parser_information_variable = Nil;
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
	defstruct_g2_filename_parser_information_variable = the_array;
	SVREF(defstruct_g2_filename_parser_information_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_filename_parser_information_g2_struct;
	def_structure_filename_parser_information_variable = 
		defstruct_g2_filename_parser_information_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_filename_parser_information_variable);
}

/* MAKE-FILENAME-PARSER-INFORMATION-1 */
Object g2int_make_filename_parser_information_1()
{
    Object def_structure_filename_parser_information_variable;

    x_note_fn_call(33,4);
    def_structure_filename_parser_information_variable = 
	    G2int_chain_of_available_filename_parser_informations;
    if (def_structure_filename_parser_information_variable) {
	G2int_chain_of_available_filename_parser_informations = 
		ISVREF(def_structure_filename_parser_information_variable,
		(SI_Long)0L);
	SVREF(def_structure_filename_parser_information_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_filename_parser_information_g2_struct;
    }
    else
	def_structure_filename_parser_information_variable = 
		g2int_make_permanent_filename_parser_information_structure_internal();
    inline_note_allocate_cons(def_structure_filename_parser_information_variable,
	    Nil);
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_filename_parser_information_variable,
	    FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_filename_parser_information_variable);
}

/* RECLAIM-FILENAME-PARSER-INFORMATION */
Object g2int_reclaim_filename_parser_information(parser_info)
    Object parser_info;
{
    Object previous_stack, entry, ab_loop_list_, token;

    x_note_fn_call(33,5);
    g2int_reclaim_gensym_list_1(ISVREF(parser_info,(SI_Long)2L));
    previous_stack = ISVREF(parser_info,(SI_Long)4L);
    entry = Nil;
    ab_loop_list_ = previous_stack;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_gensym_list_1(THIRD(entry));
    g2int_reclaim_gensym_list_1(entry);
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(previous_stack);
    token = Nil;
    ab_loop_list_ = ISVREF(parser_info,(SI_Long)1L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    token = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (g2int_text_string_p(token))
	g2int_reclaim_text_string(token);
    goto next_loop_1;
  end_loop_1:
    g2int_reclaim_gensym_list_1(ISVREF(parser_info,(SI_Long)1L));
    return g2int_reclaim_filename_parser_information_internal_1(parser_info);
}

/* COALESCE-FILENAME-TOKENS-1 */
Object g2int_coalesce_filename_tokens_1(words_and_punct)
    Object words_and_punct;
{
    Object entry, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;
    Object section, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(33,6);
    if (SYMBOLP(words_and_punct)) {
	entry = assoc_eql(words_and_punct,
		G2int_filename_special_character_registry);
	if (entry) {
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
		      simple_or_wide_character = CDR(entry);
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
		      result = g2int_copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(words_and_punct);
    }
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
		  section = Nil;
		  ab_loop_list_ = words_and_punct;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  section = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (g2int_text_string_p(section) || STRINGP(section))
		      g2int_twrite_general_string(section);
		  else if (EQ(Qg2int_ltend_of_sequencegt,section));
		  else {
		      entry = assoc_eql(section,
			      G2int_filename_special_character_registry);
		      if (entry) {
			  simple_or_wide_character = CDR(entry);
			  if (EQ(G2int_current_twriting_output_type,
				  Qg2int_wide_string)) {
			      thing = simple_or_wide_character;
			      g2int_twrite_wide_character(CHARACTERP(thing) 
				      ? CHAR_CODE(thing) : thing);
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
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			      G2int_fill_pointer_for_current_gensym_string 
				      = temp;
			  }
		      }
		  }
		  goto next_loop;
		end_loop:;
		  result = g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* COALESCE-FILENAME-SUBLISTS-1 */
Object g2int_coalesce_filename_sublists_1(sublists)
    Object sublists;
{
    Object sublists_in_order, sublist_item, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(33,7);
    if (sublists) {
	sublists_in_order = nreverse(sublists);
	sublist_item = Nil;
	ab_loop_list_ = sublists_in_order;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sublist_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_coalesce_filename_tokens_1(sublist_item),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if (CONSP(sublist_item))
	    g2int_reclaim_gensym_list_1(sublist_item);
	goto next_loop;
      end_loop:
	g2int_reclaim_gensym_list_1(sublists_in_order);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COALESCE-REVERSED-FILENAME-LIST-1 */
Object g2int_coalesce_reversed_filename_list_1(reversed_list)
    Object reversed_list;
{
    Object list_in_order, temp;

    x_note_fn_call(33,8);
    list_in_order = nreverse(reversed_list);
    temp = g2int_coalesce_filename_tokens_1(list_in_order);
    g2int_reclaim_gensym_list_1(list_in_order);
    return VALUES_1(temp);
}

/* COALESCE-FILENAME-ITEMS-1 */
Object g2int_coalesce_filename_items_1(item_list)
    Object item_list;
{
    Object temp;

    x_note_fn_call(33,9);
    temp = g2int_coalesce_filename_tokens_1(item_list);
    g2int_reclaim_gensym_list_1(item_list);
    return VALUES_1(temp);
}

/* COALESCE-REMAINDER-OF-FILENAME-SEQUENCE-1 */
Object g2int_coalesce_remainder_of_filename_sequence_1(parser_info)
    Object parser_info;
{
    x_note_fn_call(33,10);
    return g2int_coalesce_filename_tokens_1(nthcdr(ISVREF(parser_info,
	    (SI_Long)7L),ISVREF(parser_info,(SI_Long)2L)));
}

/* CHANGE-FILENAME-SEQUENCE-TO-1 */
Object g2int_change_filename_sequence_to_1(new_sequence,parser_info,increment)
    Object new_sequence, parser_info, increment;
{
    Object end_of_sequence_list, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object temp, copy_of_new_sequence;

    x_note_fn_call(33,11);
    end_of_sequence_list = g2int_gensym_cons_1(Qg2int_ltend_of_sequencegt,Nil);
    gensym_push_modify_macro_arg = 
	    g2int_gensym_list_3(FIXNUM_ADD(ISVREF(parser_info,(SI_Long)7L),
	    increment),ISVREF(parser_info,(SI_Long)3L),ISVREF(parser_info,
	    (SI_Long)2L));
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(parser_info,(SI_Long)4L);
    temp = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(parser_info,FIX((SI_Long)4L)) = temp;
    temp = FIXNUM_NEGATE(increment);
    SVREF(parser_info,FIX((SI_Long)7L)) = temp;
    temp = add1(length(new_sequence));
    SVREF(parser_info,FIX((SI_Long)3L)) = temp;
    if (new_sequence) {
	copy_of_new_sequence = 
		g2int_copy_list_using_gensym_conses_1(new_sequence);
	temp = last(copy_of_new_sequence,_);
	M_CDR(temp) = end_of_sequence_list;
	SVREF(parser_info,FIX((SI_Long)2L)) = copy_of_new_sequence;
    }
    else
	SVREF(parser_info,FIX((SI_Long)2L)) = end_of_sequence_list;
    return VALUES_1(Nil);
}

static Object Qg2int_gensym;       /* gensym */

/* RESUME-PREVIOUS-FILENAME-SEQUENCE-1 */
Object g2int_resume_previous_filename_sequence_1(parser_info)
    Object parser_info;
{
    Object gensym_pop_store, cons_1, next_cons, temp, previous_info;

    x_note_fn_call(33,12);
    gensym_pop_store = Nil;
    cons_1 = ISVREF(parser_info,(SI_Long)4L);
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(cons_1) = temp;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    SVREF(parser_info,FIX((SI_Long)4L)) = next_cons;
    previous_info = gensym_pop_store;
    g2int_reclaim_gensym_list_1(ISVREF(parser_info,(SI_Long)2L));
    temp = FIRST(previous_info);
    SVREF(parser_info,FIX((SI_Long)7L)) = temp;
    temp = SECOND(previous_info);
    SVREF(parser_info,FIX((SI_Long)3L)) = temp;
    temp = THIRD(previous_info);
    SVREF(parser_info,FIX((SI_Long)2L)) = temp;
    return g2int_reclaim_gensym_list_1(previous_info);
}

/* ERROR-IN-FILENAME-PARSE-1 */
Object g2int_error_in_filename_parse_1(string_1,parser_info)
    Object string_1, parser_info;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(33,13);
    gensymed_symbol = ISVREF(parser_info,(SI_Long)6L);
    gensymed_symbol_1 = parser_info;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

Object G2int_filename_parser_of_file_system_prop = UNBOUND;

Object G2int_namestring_generator_of_file_system_prop = UNBOUND;

Object G2int_all_known_file_systems = UNBOUND;

Object G2int_accept_any_version_component_p = UNBOUND;

Object G2int_nodes_for_unix_filename_parser = UNBOUND;

static Object Qg2int_catcher_for_filename_parse_error;  /* catcher-for-filename-parse-error */

/* ERROR-IN-UNIX-FILENAME-PARSER */
Object g2int_error_in_unix_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(33,14);
    g2int_reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qg2int_catcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qg2int_unix;         /* unix */

static Object Qg2int_filename_parser_of_file_system;  /* filename-parser-of-file-system */

static Object Qg2int_namestring_generator_of_file_system;  /* namestring-generator-of-file-system */

/* FINAL-UNIX-PARSER-NODE */
Object g2int_final_unix_parser_node(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(33,15);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = 
		g2int_make_gensym_pathname_structure_function(host,device,
		directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qg2int_unix;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_unix),
		Qg2int_filename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_unix),
		Qg2int_namestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    g2int_reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-UNIX-FILENAME-NODE-100 */
Object g2int_parse_unix_filename_node_100(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(33,16);
    next_node = Nil;
    device = Kunspecific;
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)9L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object Kabsolute;           /* :absolute */

static Object array_constant;      /* # */

/* PARSE-UNIX-FILENAME-NODE-101 */
Object g2int_parse_unix_filename_node_101(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, match_3, lt_word_gt;
    Object svref_new_value_1;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,17);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_3 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt) && 
		EQ(match_2,G2int_ltslashgt)) {
	    lt_word_gt = match_0;
	    host = g2int_copy_text_string(lt_word_gt);
	    directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_3 = nth(match_pointer,filename_sequence);
    if (match_3) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt) && 
		g2int_stringeqw(array_constant,match_2) && EQ(match_3,
		G2int_ltslashgt)) {
	    lt_word_gt = match_0;
	    host = g2int_copy_text_string(lt_word_gt);
	    directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltslashgt)) {
	directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)8L);
	goto parser_traverse;
    }
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

static Object Krelative;           /* :relative */

/* PARSE-UNIX-FILENAME-NODE-102 */
Object g2int_parse_unix_filename_node_102(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(33,18);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltslashgt)) {
	directory_item = nreverse(directory_item);
	g2int_change_filename_sequence_to_1(directory_item,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)7L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	directory_1 = g2int_coalesce_filename_sublists_1(directory_list);
	if (directory_1) {
	    if ( !TRUEP(g2int_memq_function(CAR(directory_1),list_constant)))
		directory_1 = g2int_gensym_cons_1(Krelative,directory_1);
	}
	name_type_version_list = nreverse(directory_item);
	g2int_change_filename_sequence_to_1(name_type_version_list,
		parser_info,FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)5L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	directory_item = g2int_gensym_cons_1(lt_anything_gt,directory_item);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)8L);
	goto parser_traverse;
    }
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object Khome;               /* :home */

/* PARSE-UNIX-FILENAME-NODE-103 */
Object g2int_parse_unix_filename_node_103(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, svref_new_value;
    SI_Long svref_new_value_1;

    x_note_fn_call(33,19);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)6L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_lttildegt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Khome,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		    G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Krelative,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,G2int_ltdotgt) && 
		EQ(match_2,G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Kup,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Kwild,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    directory_list = 
	    g2int_gensym_cons_1(g2int_copy_list_using_gensym_conses_1(directory_item),
	    directory_list);
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-104 */
Object g2int_parse_unix_filename_node_104(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(33,20);
    next_node = Nil;
    g2int_reclaim_gensym_list_1(directory_item);
    directory_item = Nil;
    g2int_resume_previous_filename_sequence_1(parser_info);
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-105 */
Object g2int_parse_unix_filename_node_105(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, temp;
    Object new_directory_component;
    SI_Long svref_new_value;

    x_note_fn_call(33,21);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	temp = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = temp;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		    G2int_ltend_of_sequencegt)) {
	    new_directory_component = g2int_gensym_cons_1(Krelative,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,G2int_ltdotgt) && 
		EQ(match_2,G2int_ltend_of_sequencegt)) {
	    new_directory_component = g2int_gensym_cons_1(Kup,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_lttildegt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,G2int_ltdotgt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)3L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)4L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-106 */
Object g2int_parse_unix_filename_node_106(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, svref_new_value_1, lt_anything_gt;
    SI_Long svref_new_value;

    x_note_fn_call(33,22);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_lttildegt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    name = g2int_coalesce_reversed_filename_list_1(name_list);
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltdotgt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)3L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	name_list = g2int_gensym_cons_1(lt_anything_gt,name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)4L);
	goto parser_traverse;
    }
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-108 */
Object g2int_parse_unix_filename_node_108(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(33,23);
    next_node = Nil;
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)2L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-109 */
Object g2int_parse_unix_filename_node_109(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,24);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)1L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "." */

/* PARSE-UNIX-FILENAME-NODE-110 */
Object g2int_parse_unix_filename_node_110(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, svref_new_value_1, lt_anything_gt;
    SI_Long svref_new_value;

    x_note_fn_call(33,25);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_lttildegt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    type = g2int_coalesce_reversed_filename_list_1(type_list);
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	if (name)
	    type = g2int_coalesce_reversed_filename_list_1(type_list);
	else
	    name = 
		    g2int_coalesce_reversed_filename_list_1(nconc2(type_list,
		    g2int_gensym_cons_1(string_constant,Nil)));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltdotgt)) {
	type_list = nconc2(type_list,name ? 
		g2int_gensym_list_2(string_constant,name) : 
		g2int_gensym_cons_1(string_constant,Nil));
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	type_list = Nil;
	if (name)
	    g2int_reclaim_text_string(name);
	name = type;
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)1L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	type_list = g2int_gensym_cons_1(lt_anything_gt,type_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)1L);
	goto parser_traverse;
    }
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-111 */
Object g2int_parse_unix_filename_node_111(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(33,26);
    next_node = Nil;
    g2int_reclaim_gensym_list_1(name_type_version_list);
    next_node = ISVREF(G2int_nodes_for_unix_filename_parser,(SI_Long)12L);
    goto parser_traverse;
    g2int_error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

/* PARSE-UNIX-FILENAME */
Object g2int_parse_unix_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(33,27);
    if (PUSH_CATCH(Qg2int_catcher_for_filename_parse_error,0)) {
	parser_info = g2int_make_filename_parser_information_1();
	svref_new_value = g2int_tokenize_filename(3,filename,
		list_constant_1,Kcase_sensitive);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = 
		g2int_copy_list_using_gensym_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = ISVREF(G2int_nodes_for_unix_filename_parser,
		(SI_Long)11L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = g2int_parse_unix_filename_node_100(parser_info,Nil,Nil,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

Object G2int_vms_directory_filenames_can_dangle_p = UNBOUND;

/* RECLAIM-NASCENT-VMS-DIRECTORY */
Object g2int_reclaim_nascent_vms_directory(directory_list,directory_item_qm)
    Object directory_list, directory_item_qm;
{
    Object component, ab_loop_list_;

    x_note_fn_call(33,28);
    component = Nil;
    ab_loop_list_ = directory_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(component))
	g2int_reclaim_gensym_list_1(component);
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(directory_list);
    g2int_reclaim_gensym_list_1(directory_item_qm);
    return VALUES_1(Nil);
}

Object G2int_nodes_for_vms_filename_parser = UNBOUND;

/* ERROR-IN-VMS-FILENAME-PARSER */
Object g2int_error_in_vms_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(33,29);
    g2int_reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qg2int_catcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qg2int_vms;          /* vms */

/* FINAL-VMS-PARSER-NODE */
Object g2int_final_vms_parser_node(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(33,30);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = 
		g2int_make_gensym_pathname_structure_function(host,device,
		directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qg2int_vms;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_vms),
		Qg2int_filename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_vms),
		Qg2int_namestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    g2int_reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-VMS-FILENAME-NODE-101 */
Object g2int_parse_vms_filename_node_101(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, match_3, match_4, match_5;
    Object match_6, match_7, lt_word_gt, lt_word_gt_0, lt_word_gt_1;
    Object lt_word_gt_2, gensymed_symbol, gensymed_symbol_1, car_new_value;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,31);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_3 = Nil;
    match_4 = Nil;
    match_5 = Nil;
    match_6 = Nil;
    match_7 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt) && 
		EQ(match_2,G2int_ltcolongt)) {
	    lt_word_gt = match_0;
	    host = g2int_copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)12L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_3 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_3);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_4 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_4);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_5 = nth(match_pointer,filename_sequence);
    if (match_5) {
	if (g2int_text_string_p(match_0) && EQ(match_1,
		G2int_ltdouble_quotegt) && g2int_text_string_p(match_2) && 
		EQ(match_3,G2int_ltdouble_quotegt) && EQ(match_4,
		G2int_ltcolongt) && EQ(match_5,G2int_ltcolongt)) {
	    lt_word_gt_0 = match_0;
	    lt_word_gt_1 = match_2;
	    host = 
		    g2int_coalesce_filename_items_1(g2int_gensym_list_4(lt_word_gt_0,
		    G2int_ltdouble_quotegt,lt_word_gt_1,
		    G2int_ltdouble_quotegt));
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)6L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)12L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_6 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_6);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_7 = nth(match_pointer,filename_sequence);
    if (match_7) {
	if (g2int_text_string_p(match_0) && EQ(match_1,
		G2int_ltdouble_quotegt) && g2int_text_string_p(match_2) && 
		EQ(match_3,G2int_ltspacegt) && 
		g2int_text_string_p(match_4) && EQ(match_5,
		G2int_ltdouble_quotegt) && EQ(match_6,G2int_ltcolongt) && 
		EQ(match_7,G2int_ltcolongt)) {
	    lt_word_gt_0 = match_0;
	    lt_word_gt_1 = match_2;
	    lt_word_gt_2 = match_4;
	    gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)6L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = lt_word_gt_0;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = G2int_ltdouble_quotegt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = lt_word_gt_1;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = G2int_ltspacegt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = lt_word_gt_2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = G2int_ltdouble_quotegt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    host = g2int_coalesce_filename_items_1(gensymed_symbol);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)8L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)12L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)12L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-102 */
Object g2int_parse_vms_filename_node_102(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, lt_word_gt;
    SI_Long svref_new_value;

    x_note_fn_call(33,32);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt)) {
	    lt_word_gt = match_0;
	    device = g2int_copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)11L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)11L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object array_constant_1;    /* # */

static Object string_constant_1;   /* "empty relative VMS pathname" */

static Object string_constant_2;   /* "VMS directory not supplied after [" */

/* PARSE-VMS-FILENAME-NODE-103 */
Object g2int_parse_vms_filename_node_103(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, match_3, match_4, match_5;
    Object svref_new_value_1;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,33);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_3 = Nil;
    match_4 = Nil;
    match_5 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_2 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_3 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_3);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_4 = nth(match_pointer,filename_sequence);
    if (match_4) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,
		G2int_ltdotgt) && EQ(match_2,G2int_ltdotgt) && EQ(match_3,
		G2int_ltdotgt) && EQ(match_4,G2int_ltright_bracketgt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = g2int_gensym_list_2(Krelative,Kwild_inferiors);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)5L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,
		G2int_ltright_bracketgt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = g2int_gensym_cons_1(Krelative,Nil);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && 
		g2int_stringeqw(array_constant_1,match_1) && EQ(match_2,
		G2int_ltright_bracketgt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = g2int_gensym_cons_1(Kabsolute,Nil);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_5 = nth(match_pointer,filename_sequence);
    if (match_5) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && 
		g2int_stringeqw(array_constant_1,match_1) && EQ(match_2,
		G2int_ltdotgt) && EQ(match_3,G2int_ltdotgt) && EQ(match_4,
		G2int_ltdotgt) && EQ(match_5,G2int_ltright_bracketgt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = g2int_gensym_list_2(Kabsolute,Kwild_inferiors);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)6L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && 
		g2int_stringeqw(array_constant_1,match_1) && EQ(match_2,
		G2int_ltdotgt)) {
	    directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,
		G2int_lthyphengt) && EQ(match_2,G2int_ltdotgt)) {
	    directory_list = g2int_gensym_cons_1(Krelative,directory_list);
	    dual_directory_impossible_p = T;
	    directory_list = g2int_gensym_cons_1(Kup,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,
		G2int_ltdotgt) && EQ(match_2,G2int_ltright_bracketgt)) {
	    g2int_error_in_filename_parse_1(string_constant_1,parser_info);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,G2int_ltdotgt)) {
	    directory_list = g2int_gensym_cons_1(Krelative,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltleft_bracketgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    if (G2int_vms_directory_filenames_can_dangle_p)
		directory_1 = g2int_gensym_cons_1(Krelative,Nil);
	    else {
		g2int_reclaim_pathname_components(2,host,device);
		g2int_error_in_filename_parse_1(string_constant_2,parser_info);
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltleft_bracketgt)) {
	directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)10L);
	goto parser_traverse;
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object string_constant_3;   /* "second directory spec can't have initial :up marker" */

static Object string_constant_4;   /* "dual directory syntax not permited in this context" */

static Object string_constant_5;   /* "dual directory syntax can't be cascaded" */

static Object string_constant_6;   /* "second directory spec cannot be empty" */

static Object string_constant_7;   /* "VMS directory not terminated with ]" */

/* PARSE-VMS-FILENAME-NODE-104 */
Object g2int_parse_vms_filename_node_104(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, match_3;
    Object svref_new_value_1, lt_anything_gt;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,34);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_3 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_2 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_3 = nth(match_pointer,filename_sequence);
    if (match_3) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,G2int_ltdotgt) && 
		EQ(match_2,G2int_ltdotgt) && EQ(match_3,
		G2int_ltright_bracketgt)) {
	    directory_list = g2int_gensym_cons_1(Kwild_inferiors,
		    directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (match_3) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		G2int_ltright_bracketgt) && EQ(match_2,
		G2int_ltleft_bracketgt) && EQ(match_3,G2int_lthyphengt)) {
	    g2int_reclaim_pathname_components(2,host,device);
	    g2int_reclaim_nascent_vms_directory(directory_list,
		    directory_item_qm);
	    g2int_error_in_filename_parse_1(string_constant_3,parser_info);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		G2int_ltright_bracketgt) && EQ(match_2,
		    G2int_ltleft_bracketgt)) {
	    if (dual_directory_impossible_p) {
		g2int_reclaim_pathname_components(2,host,device);
		g2int_reclaim_nascent_vms_directory(directory_list,
			directory_item_qm);
		g2int_error_in_filename_parse_1(string_constant_4,parser_info);
	    }
	    else if (doing_dual_directory_p) {
		g2int_reclaim_pathname_components(2,host,device);
		g2int_reclaim_nascent_vms_directory(directory_list,
			directory_item_qm);
		g2int_error_in_filename_parse_1(string_constant_5,parser_info);
	    }
	    else {
		directory_item_qm = nreverse(directory_item_qm);
		doing_dual_directory_p = T;
		g2int_change_filename_sequence_to_1(directory_item_qm,
			parser_info,FIX((SI_Long)3L));
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)9L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltright_bracketgt)) {
	final_directory_item_p = T;
	directory_item_qm = nreverse(directory_item_qm);
	if ( !TRUEP(directory_item_qm) && doing_dual_directory_p) {
	    g2int_reclaim_pathname_components(2,host,device);
	    g2int_reclaim_nascent_vms_directory(directory_list,
		    directory_item_qm);
	    g2int_error_in_filename_parse_1(string_constant_6,parser_info);
	}
	else
	    g2int_change_filename_sequence_to_1(directory_item_qm,
		    parser_info,FIX((SI_Long)1L));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)9L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltdotgt)) {
	directory_item_qm = nreverse(directory_item_qm);
	g2int_change_filename_sequence_to_1(directory_item_qm,parser_info,
		FIX((SI_Long)1L));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)9L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltleft_bracketgt)) {
	g2int_reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltcolongt)) {
	g2int_reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	if (G2int_vms_directory_filenames_can_dangle_p) {
	    if (directory_item_qm) {
		directory_item_qm = nreverse(directory_item_qm);
		directory_list = 
			g2int_gensym_cons_1(g2int_copy_list_using_gensym_conses_1(directory_item_qm),
			directory_list);
		g2int_reclaim_gensym_list_1(directory_item_qm);
	    }
	    directory_1 = g2int_coalesce_filename_sublists_1(directory_list);
	}
	else {
	    g2int_reclaim_nascent_vms_directory(directory_list,
		    directory_item_qm);
	    g2int_error_in_filename_parse_1(string_constant_7,parser_info);
	}
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	directory_item_qm = g2int_gensym_cons_1(lt_anything_gt,
		directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)10L);
	goto parser_traverse;
    }
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-105 */
Object g2int_parse_vms_filename_node_105(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,35);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_lthyphengt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    if ( !TRUEP(doing_dual_directory_p))
		dual_directory_impossible_p = T;
	    directory_list = g2int_gensym_cons_1(Kup,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Kwild,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (directory_item_qm)
	directory_list = 
		g2int_gensym_cons_1(g2int_copy_list_using_gensym_conses_1(directory_item_qm),
		directory_list);
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-106 */
Object g2int_parse_vms_filename_node_106(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(33,36);
    next_node = Nil;
    g2int_reclaim_gensym_list_1(directory_item_qm);
    directory_item_qm = Nil;
    g2int_resume_previous_filename_sequence_1(parser_info);
    if (final_directory_item_p)
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)7L);
    else
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)10L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-107 */
Object g2int_parse_vms_filename_node_107(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(33,37);
    next_node = Nil;
    directory_1 = g2int_coalesce_filename_sublists_1(directory_list);
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-108 */
Object g2int_parse_vms_filename_node_108(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,38);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,G2int_ltdotgt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)4L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)5L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-109 */
Object g2int_parse_vms_filename_node_109(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(33,39);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltdotgt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)4L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltsemicolongt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltleft_bracketgt)) {
	g2int_reclaim_gensym_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltright_bracketgt)) {
	g2int_reclaim_gensym_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltcolongt)) {
	g2int_reclaim_gensym_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	name_list = g2int_gensym_cons_1(lt_anything_gt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)5L);
	goto parser_traverse;
    }
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-110 */
Object g2int_parse_vms_filename_node_110(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,40);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,G2int_ltdotgt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)2L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		    G2int_ltsemicolongt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)2L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)3L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-111 */
Object g2int_parse_vms_filename_node_111(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(33,41);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltdotgt)) {
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltsemicolongt)) {
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltleft_bracketgt)) {
	g2int_reclaim_gensym_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltright_bracketgt)) {
	g2int_reclaim_gensym_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltcolongt)) {
	g2int_reclaim_gensym_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	type_list = g2int_gensym_cons_1(lt_anything_gt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)3L);
	goto parser_traverse;
    }
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* PARSE-VMS-FILENAME-NODE-112 */
Object g2int_parse_vms_filename_node_112(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, svref_new_value_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,42);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    version = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_lthyphengt) && 
		g2int_stringeqw(array_constant_2,match_1) && EQ(match_2,
		G2int_ltend_of_sequencegt)) {
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (g2int_stringeqw(array_constant_3,match_0) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    version = Knewest;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	version = Knewest;
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)1L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object string_constant_8;   /* "non-numeric version" */

/* PARSE-VMS-FILENAME-NODE-113 */
Object g2int_parse_vms_filename_node_113(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, lt_word_gt;
    SI_Long svref_new_value;

    x_note_fn_call(33,43);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (g2int_text_string_p(match_0) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    lt_word_gt = match_0;
	    version = g2int_read_positive_fixnum_from_string(lt_word_gt,
		    FIX((SI_Long)0L),g2int_text_string_length(lt_word_gt));
	    if ( !TRUEP(version)) {
		if (G2int_accept_any_version_component_p)
		    version = 
			    g2int_coalesce_remainder_of_filename_sequence_1(parser_info);
		else {
		    g2int_reclaim_pathname_components(5,host,device,
			    directory_1,name,type);
		    g2int_error_in_filename_parse_1(string_constant_8,
			    parser_info);
		}
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_lthyphengt) && g2int_text_string_p(match_1) 
		&& EQ(match_2,G2int_ltend_of_sequencegt)) {
	    lt_word_gt = match_1;
	    version = g2int_read_positive_fixnum_from_string(lt_word_gt,
		    FIX((SI_Long)0L),g2int_text_string_length(lt_word_gt));
	    if ( !TRUEP(version)) {
		if (G2int_accept_any_version_component_p)
		    version = 
			    g2int_coalesce_remainder_of_filename_sequence_1(parser_info);
		else {
		    g2int_reclaim_pathname_components(5,host,device,
			    directory_1,name,type);
		    g2int_error_in_filename_parse_1(string_constant_8,
			    parser_info);
		}
	    }
	    else
		version = negate(version);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,
		    (SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (G2int_accept_any_version_component_p)
	version = g2int_coalesce_remainder_of_filename_sequence_1(parser_info);
    else {
	g2int_reclaim_pathname_components(5,host,device,directory_1,name,type);
	g2int_error_in_filename_parse_1(string_constant_8,parser_info);
    }
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object string_constant_9;   /* "bad constituent char" */

/* PARSE-VMS-FILENAME-NODE-114 */
Object g2int_parse_vms_filename_node_114(parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(33,44);
    next_node = Nil;
    g2int_reclaim_pathname_components(4,host,device,directory_1,name);
    g2int_error_in_filename_parse_1(string_constant_9,parser_info);
    next_node = ISVREF(G2int_nodes_for_vms_filename_parser,(SI_Long)15L);
    goto parser_traverse;
    g2int_error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object list_constant_2;     /* # */

/* PARSE-VMS-FILENAME */
Object g2int_parse_vms_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(33,45);
    if (PUSH_CATCH(Qg2int_catcher_for_filename_parse_error,0)) {
	parser_info = g2int_make_filename_parser_information_1();
	svref_new_value = g2int_tokenize_filename(3,filename,
		list_constant_2,Kall_uppercase);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = 
		g2int_copy_list_using_gensym_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = ISVREF(G2int_nodes_for_vms_filename_parser,
		(SI_Long)14L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = g2int_parse_vms_filename_node_101(parser_info,Nil,Nil,Nil,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

Object G2int_limit_dos_filename_component_lengths_p = UNBOUND;

Object G2int_allow_extensionless_dos_filenames_p = UNBOUND;

Object G2int_character_case_mode_for_generalized_dos = UNBOUND;

Object G2int_nodes_for_generalized_dos_filename_parser = UNBOUND;

/* ERROR-IN-GENERALIZED-DOS-FILENAME-PARSER */
Object g2int_error_in_generalized_dos_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(33,46);
    g2int_reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qg2int_catcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qg2int_generalized_dos;  /* generalized-dos */

/* FINAL-GENERALIZED-DOS-PARSER-NODE */
Object g2int_final_generalized_dos_parser_node(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(33,47);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = 
		g2int_make_gensym_pathname_structure_function(host,device,
		directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qg2int_generalized_dos;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_generalized_dos),
		Qg2int_filename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_generalized_dos),
		Qg2int_namestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    g2int_reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-100 */
Object g2int_parse_generalized_dos_filename_node_100(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, lt_word_gt;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,48);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_ltbackslashgt) && EQ(match_1,
		G2int_ltbackslashgt) && g2int_text_string_p(match_2)) {
	    lt_word_gt = match_2;
	    host = g2int_copy_text_string(lt_word_gt);
	    version = Kunspecific;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    host = Kunspecific;
    version = Kunspecific;
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)8L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_10;  /* "device must only have one letter" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-101 */
Object g2int_parse_generalized_dos_filename_node_101(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, lt_word_gt;
    Object svref_new_value_1;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(33,49);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length)) {
	match_1 = nth(match_pointer,filename_sequence);
	temp = TRUEP(match_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	match_pointer = FIXNUM_ADD1(match_pointer);
	temp = FIXNUM_LT(match_pointer,sequence_length);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt) && 
		EQ(match_2,G2int_ltend_of_sequencegt)) {
	    lt_word_gt = match_0;
	    if (G2int_limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(g2int_text_string_length(lt_word_gt)) == 
			(SI_Long)1L))
		    g2int_error_in_filename_parse_1(string_constant_10,
			    parser_info);
	    }
	    device = g2int_copy_text_string(lt_word_gt);
	    directory_1 = g2int_gensym_cons_1(Krelative,directory_1);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt) && 
		EQ(match_2,G2int_ltbackslashgt)) {
	    lt_word_gt = match_0;
	    if (G2int_limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(g2int_text_string_length(lt_word_gt)) == 
			(SI_Long)1L))
		    g2int_error_in_filename_parse_1(string_constant_10,
			    parser_info);
	    }
	    device = g2int_copy_text_string(lt_word_gt);
	    directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (g2int_text_string_p(match_0) && EQ(match_1,G2int_ltcolongt)) {
	    lt_word_gt = match_0;
	    if (G2int_limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(g2int_text_string_length(lt_word_gt)) == 
			(SI_Long)1L))
		    g2int_error_in_filename_parse_1(string_constant_10,
			    parser_info);
	    }
	    device = g2int_copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,G2int_ltbackslashgt)) {
	directory_list = g2int_gensym_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)7L);
	goto parser_traverse;
    }
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)7L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_11;  /* "no wildcards allowed in directory" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-102 */
Object g2int_parse_generalized_dos_filename_node_102(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(33,50);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltbackslashgt)) {
	if (wildcard_encountered_p) {
	    if (directory_item)
		g2int_reclaim_gensym_list_1(directory_item);
	    if (directory_list)
		g2int_reclaim_gensym_tree_1(directory_list);
	    g2int_error_in_filename_parse_1(string_constant_11,parser_info);
	}
	directory_item = nreverse(directory_item);
	g2int_change_filename_sequence_to_1(directory_item,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)6L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	directory_1 = g2int_coalesce_filename_sublists_1(directory_list);
	if (directory_1) {
	    if ( !TRUEP(g2int_memq_function(CAR(directory_1),list_constant)))
		directory_1 = g2int_gensym_cons_1(Krelative,directory_1);
	}
	name_and_type_list = nreverse(directory_item);
	g2int_change_filename_sequence_to_1(name_and_type_list,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)4L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qg2int_ltend_of_sequencegt,lt_anything_gt)) {
	directory_item = g2int_gensym_cons_1(lt_anything_gt,directory_item);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)7L);
	goto parser_traverse;
    }
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-103 */
Object g2int_parse_generalized_dos_filename_node_103(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, svref_new_value;
    SI_Long svref_new_value_1;

    x_note_fn_call(33,51);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)5L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		    G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Krelative,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,G2int_ltdotgt) && 
		EQ(match_2,G2int_ltend_of_sequencegt)) {
	    directory_list = g2int_gensym_cons_1(Kup,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    wildcard_encountered_p = T;
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    directory_list = 
	    g2int_gensym_cons_1(g2int_copy_list_using_gensym_conses_1(directory_item),
	    directory_list);
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)5L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-104 */
Object g2int_parse_generalized_dos_filename_node_104(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node;

    x_note_fn_call(33,52);
    next_node = Nil;
    g2int_reclaim_gensym_list_1(directory_item);
    directory_item = Nil;
    g2int_resume_previous_filename_sequence_1(parser_info);
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)7L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-105 */
Object g2int_parse_generalized_dos_filename_node_105(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, temp;
    Object new_directory_component;
    SI_Long svref_new_value;

    x_note_fn_call(33,53);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	temp = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = temp;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,
		    G2int_ltend_of_sequencegt)) {
	    new_directory_component = g2int_gensym_cons_1(Krelative,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,G2int_ltdotgt) && EQ(match_1,G2int_ltdotgt) && 
		EQ(match_2,G2int_ltend_of_sequencegt)) {
	    new_directory_component = g2int_gensym_cons_1(Kup,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,G2int_ltdotgt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)2L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)3L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_12;  /* "file type required" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-106 */
Object g2int_parse_generalized_dos_filename_node_106(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, svref_new_value, lt_word_gt;

    x_note_fn_call(33,54);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	if (G2int_allow_extensionless_dos_filenames_p)
	    name = g2int_coalesce_reversed_filename_list_1(name_list);
	else {
	    if (name_list)
		g2int_reclaim_gensym_tree_1(name_list);
	    g2int_error_in_filename_parse_1(string_constant_12,parser_info);
	}
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltdotgt)) {
	name = g2int_coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)2L);
	goto parser_traverse;
    }
    lt_word_gt = current_token;
    if (g2int_text_string_p(lt_word_gt)) {
	name_list = g2int_gensym_cons_1(lt_word_gt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)3L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltasteriskgt)) {
	name_list = g2int_gensym_cons_1(G2int_ltasteriskgt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)3L);
	goto parser_traverse;
    }
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-108 */
Object g2int_parse_generalized_dos_filename_node_108(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(33,55);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,G2int_ltasteriskgt) && EQ(match_1,
		G2int_ltend_of_sequencegt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = 
		    ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)1L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-110 */
Object g2int_parse_generalized_dos_filename_node_110(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, temp, svref_new_value, lt_word_gt;

    x_note_fn_call(33,56);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,G2int_ltend_of_sequencegt)) {
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	if (G2int_limit_dos_filename_component_lengths_p && 
		IFIX(g2int_text_string_length(type)) > (SI_Long)3L) {
	    temp = g2int_text_string_substring(type,FIX((SI_Long)0L),
		    FIX((SI_Long)3L));
	    g2int_reclaim_text_string(type);
	    type = temp;
	}
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltdotgt)) {
	type_list = nconc2(type_list,name ? 
		g2int_gensym_list_2(string_constant,name) : 
		g2int_gensym_cons_1(string_constant,Nil));
	type = g2int_coalesce_reversed_filename_list_1(type_list);
	type_list = Nil;
	if (name)
	    g2int_reclaim_text_string(name);
	name = type;
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    lt_word_gt = current_token;
    if (g2int_text_string_p(lt_word_gt)) {
	type_list = g2int_gensym_cons_1(lt_word_gt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    if (EQ(current_token,G2int_ltasteriskgt)) {
	type_list = g2int_gensym_cons_1(G2int_ltasteriskgt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "over 63 characters in filename" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-111 */
Object g2int_parse_generalized_dos_filename_node_111(parser_info,host,
	    device,directory_1,name,type,version,directory_item,
	    directory_list,wildcard_encountered_p,name_and_type_list,
	    name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, directory_element, ab_loop_list_, incff_1_arg, element;
    SI_Long count_of_characters_in_filename;

    x_note_fn_call(33,57);
    next_node = Nil;
    g2int_reclaim_gensym_list_1(name_and_type_list);
    if (G2int_limit_dos_filename_component_lengths_p) {
	count_of_characters_in_filename = (SI_Long)0L;
	if (device)
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)2L;
	if (EQ(CAR(directory_1),Kabsolute))
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	directory_element = Nil;
	ab_loop_list_ = CDR(directory_1);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	directory_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(directory_element,Krelative))
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	else if (EQ(directory_element,Kup))
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)2L;
	else {
	    incff_1_arg = 
		    FIXNUM_ADD1(g2int_text_string_length(directory_element));
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	goto next_loop;
      end_loop:;
	if (g2int_text_string_p(name)) {
	    incff_1_arg = g2int_text_string_length(name);
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	else
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (name)
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (g2int_text_string_p(type)) {
	    incff_1_arg = g2int_text_string_length(type);
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	else
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (count_of_characters_in_filename > (SI_Long)63L) {
	    if (g2int_text_string_p(device))
		g2int_reclaim_text_string(device);
	    if (directory_1) {
		element = Nil;
		ab_loop_list_ = directory_1;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (g2int_text_string_p(element))
		    g2int_reclaim_text_string(element);
		goto next_loop_1;
	      end_loop_1:
		g2int_reclaim_gensym_list_1(directory_1);
	    }
	    if (g2int_text_string_p(name))
		g2int_reclaim_text_string(name);
	    if (g2int_text_string_p(type))
		g2int_reclaim_text_string(type);
	    g2int_error_in_filename_parse_1(string_constant_13,parser_info);
	}
    }
    next_node = ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
	    (SI_Long)11L);
    goto parser_traverse;
    g2int_error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* PARSE-GENERALIZED-DOS-FILENAME */
Object g2int_parse_generalized_dos_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(33,58);
    if (PUSH_CATCH(Qg2int_catcher_for_filename_parse_error,0)) {
	parser_info = g2int_make_filename_parser_information_1();
	svref_new_value = g2int_tokenize_filename(3,filename,
		list_constant_3,G2int_character_case_mode_for_generalized_dos);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = 
		g2int_copy_list_using_gensym_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = 
		ISVREF(G2int_nodes_for_generalized_dos_filename_parser,
		(SI_Long)10L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = g2int_parse_generalized_dos_filename_node_100(parser_info,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_dos;          /* dos */

static Object Qg2int_parse_dos_filename;  /* parse-dos-filename */

static Object Qg2int_generate_dos_namestring;  /* generate-dos-namestring */

/* PARSE-DOS-FILENAME */
Object g2int_parse_dos_filename(filename)
    Object filename;
{
    Object limit_dos_filename_component_lengths_p;
    Object allow_extensionless_dos_filenames_p;
    Object character_case_mode_for_generalized_dos, result_pathname_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(33,59);
    limit_dos_filename_component_lengths_p = T;
    PUSH_SPECIAL(G2int_limit_dos_filename_component_lengths_p,limit_dos_filename_component_lengths_p,
	    2);
      allow_extensionless_dos_filenames_p = T;
      PUSH_SPECIAL(G2int_allow_extensionless_dos_filenames_p,allow_extensionless_dos_filenames_p,
	      1);
	character_case_mode_for_generalized_dos = Kall_uppercase;
	PUSH_SPECIAL(G2int_character_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
		0);
	  result_pathname_qm = g2int_parse_generalized_dos_filename(filename);
	  if (result_pathname_qm) {
	      SVREF(result_pathname_qm,FIX((SI_Long)8L)) = Qg2int_dos;
	      SVREF(result_pathname_qm,FIX((SI_Long)9L)) = 
		      Qg2int_parse_dos_filename;
	      SVREF(result_pathname_qm,FIX((SI_Long)10L)) = 
		      Qg2int_generate_dos_namestring;
	  }
	  result = VALUES_1(result_pathname_qm);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_win32;        /* win32 */

static Object Qg2int_parse_win32_filename;  /* parse-win32-filename */

static Object Qg2int_generate_win32_namestring;  /* generate-win32-namestring */

/* PARSE-WIN32-FILENAME */
Object g2int_parse_win32_filename(filename)
    Object filename;
{
    Object limit_dos_filename_component_lengths_p;
    Object allow_extensionless_dos_filenames_p;
    Object character_case_mode_for_generalized_dos, result_pathname_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(33,60);
    limit_dos_filename_component_lengths_p = Nil;
    PUSH_SPECIAL(G2int_limit_dos_filename_component_lengths_p,limit_dos_filename_component_lengths_p,
	    2);
      allow_extensionless_dos_filenames_p = T;
      PUSH_SPECIAL(G2int_allow_extensionless_dos_filenames_p,allow_extensionless_dos_filenames_p,
	      1);
	character_case_mode_for_generalized_dos = Kcase_sensitive;
	PUSH_SPECIAL(G2int_character_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
		0);
	  result_pathname_qm = g2int_parse_generalized_dos_filename(filename);
	  if (result_pathname_qm) {
	      SVREF(result_pathname_qm,FIX((SI_Long)8L)) = Qg2int_win32;
	      SVREF(result_pathname_qm,FIX((SI_Long)9L)) = 
		      Qg2int_parse_win32_filename;
	      SVREF(result_pathname_qm,FIX((SI_Long)10L)) = 
		      Qg2int_generate_win32_namestring;
	  }
	  result = VALUES_1(result_pathname_qm);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_last_deletable_token_in_namestring = UNBOUND;

/* WRITE-KNOWN-SPECIAL-CHARACTER-FOR-NAMESTRING */
Object g2int_write_known_special_character_for_namestring(special_character_description)
    Object special_character_description;
{
    Object special_character_entry, simple_or_wide_character, thing, temp;
    Object schar_arg_2, schar_new_value;

    x_note_fn_call(33,61);
    special_character_entry = assoc_eql(special_character_description,
	    G2int_filename_special_character_registry);
    if (special_character_entry) {
	simple_or_wide_character = CDR(special_character_entry);
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
    else
	return VALUES_1(Nil);
}

static Object Qg2int_exdeleteex;   /* !delete! */

static Object Qg2int_exdeletableex;  /* !deletable! */

/* WRITE-SPECIAL-CHARACTER-FOR-NAMESTRING */
Object g2int_write_special_character_for_namestring(special_character_description)
    Object special_character_description;
{
    x_note_fn_call(33,62);
    if (EQ(special_character_description,Qg2int_exdeleteex)) {
	G2int_last_deletable_token_in_namestring = Nil;
	return VALUES_1(G2int_last_deletable_token_in_namestring);
    }
    else {
	if (G2int_last_deletable_token_in_namestring) {
	    g2int_write_known_special_character_for_namestring(G2int_last_deletable_token_in_namestring);
	    G2int_last_deletable_token_in_namestring = Nil;
	}
	if (g2int_text_string_p(special_character_description))
	    return g2int_twrite_general_string(special_character_description);
	else if (CONSP(special_character_description) && 
		EQ(FIRST(special_character_description),
		    Qg2int_exdeletableex)) {
	    G2int_last_deletable_token_in_namestring = 
		    SECOND(special_character_description);
	    return VALUES_1(G2int_last_deletable_token_in_namestring);
	}
	else
	    return g2int_write_known_special_character_for_namestring(special_character_description);
    }
}

/* WRITE-SPECIAL-CHARACTERS-FOR-NAMESTRING */
Object g2int_write_special_characters_for_namestring(special_character_description)
    Object special_character_description;
{
    Object special_character_subdescription, ab_loop_list_;

    x_note_fn_call(33,63);
    if (g2int_text_string_p(special_character_description)) {
	if (G2int_last_deletable_token_in_namestring) {
	    g2int_write_known_special_character_for_namestring(G2int_last_deletable_token_in_namestring);
	    G2int_last_deletable_token_in_namestring = Nil;
	}
	return g2int_twrite_general_string(special_character_description);
    }
    else if (CONSP(special_character_description) && 
	    EQ(FIRST(special_character_description),Qg2int_exdeletableex)) {
	G2int_last_deletable_token_in_namestring = 
		SECOND(special_character_description);
	return VALUES_1(G2int_last_deletable_token_in_namestring);
    }
    else if (CONSP(special_character_description)) {
	special_character_subdescription = Nil;
	ab_loop_list_ = special_character_description;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	special_character_subdescription = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_special_character_for_namestring(special_character_subdescription);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return g2int_write_special_character_for_namestring(special_character_description);
}

static Object Kcomponent;          /* :component */

/* WRITE-MONOLITHIC-COMPONENT-FOR-NAMESTRING */
Object g2int_write_monolithic_component_for_namestring(component,
	    component_template,special_symbol_plist,convert_to_uppercase_p)
    Object component, component_template, special_symbol_plist;
    Object convert_to_uppercase_p;
{
    Object template_item, ab_loop_list_, special_symbol_entry;
    Object uppercase_component;

    x_note_fn_call(33,64);
    if ( !TRUEP(component) || EQ(Kunspecific,component)) {
	if (G2int_last_deletable_token_in_namestring) {
	    g2int_write_known_special_character_for_namestring(G2int_last_deletable_token_in_namestring);
	    G2int_last_deletable_token_in_namestring = Nil;
	    return VALUES_1(G2int_last_deletable_token_in_namestring);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	template_item = Nil;
	ab_loop_list_ = component_template;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	template_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(template_item,Kcomponent)) {
	    special_symbol_entry = getf(special_symbol_plist,component,_);
	    if (special_symbol_entry)
		g2int_write_special_characters_for_namestring(special_symbol_entry);
	    else if (g2int_text_string_p(component) && 
			convert_to_uppercase_p) {
		uppercase_component = 
			g2int_nstring_upcasew(g2int_copy_text_string(component));
		g2int_twrite(uppercase_component);
		g2int_reclaim_text_string(uppercase_component);
	    }
	    else {
		if (G2int_last_deletable_token_in_namestring) {
		    g2int_write_known_special_character_for_namestring(G2int_last_deletable_token_in_namestring);
		    G2int_last_deletable_token_in_namestring = Nil;
		}
		g2int_twrite(component);
	    }
	}
	else
	    g2int_write_special_character_for_namestring(template_item);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Kleading_items;      /* :leading-items */

static Object Klast_item;          /* :last-item */

static Object Kcompound;           /* :compound */

/* WRITE-COMPOUND-COMPONENT-FOR-NAMESTRING */
Object g2int_write_compound_component_for_namestring(component,
	    component_template,sequence_template,heterogeneous_sequence_p,
	    special_symbol_plist,prologue_qm,convert_to_uppercase_p)
    Object component, component_template, sequence_template;
    Object heterogeneous_sequence_p, special_symbol_plist, prologue_qm;
    Object convert_to_uppercase_p;
{
    Object inner_component_template, last_component_template, sequence_item;
    Object ab_loop_list_, component_item, ab_loop_list__1, component_cons;
    Object last_component_template_qm, ab_loop_iter_flag_, temp, temp_1;

    x_note_fn_call(33,65);
    if ( !TRUEP(component) &&  !TRUEP(prologue_qm)) {
	if (G2int_last_deletable_token_in_namestring) {
	    g2int_write_known_special_character_for_namestring(G2int_last_deletable_token_in_namestring);
	    G2int_last_deletable_token_in_namestring = Nil;
	    return VALUES_1(G2int_last_deletable_token_in_namestring);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	inner_component_template = Nil;
	last_component_template = Nil;
	if (heterogeneous_sequence_p) {
	    inner_component_template = getf(component_template,
		    Kleading_items,_);
	    last_component_template = getf(component_template,Klast_item,_);
	}
	sequence_item = Nil;
	ab_loop_list_ = sequence_template;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sequence_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(sequence_item,Kcompound)) {
	    component_item = Nil;
	    ab_loop_list__1 = component;
	    component_cons = component;
	    last_component_template_qm = Nil;
	    ab_loop_iter_flag_ = T;
	    if (prologue_qm)
		g2int_write_special_characters_for_namestring(prologue_qm);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    component_item = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_iter_flag_))
		component_cons = M_CDR(component_cons);
	    if ( !TRUEP(component_cons))
		goto end_loop_1;
	    last_component_template_qm =  !TRUEP(CDR(component_cons)) ? 
		    last_component_template : Qnil;
	    if (heterogeneous_sequence_p) {
		temp = component_item;
		temp_1 = last_component_template_qm;
		if (temp_1);
		else
		    temp_1 = inner_component_template;
		g2int_write_monolithic_component_for_namestring(temp,
			temp_1,special_symbol_plist,convert_to_uppercase_p);
	    }
	    else
		g2int_write_monolithic_component_for_namestring(component_item,
			component_template,special_symbol_plist,
			convert_to_uppercase_p);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else
	    g2int_write_special_character_for_namestring(sequence_item);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

/* GENERATE-UNIX-NAMESTRING */
Object g2int_generate_unix_namestring(pathname_1)
    Object pathname_1;
{
    Object gensym_pathname_host, gensym_pathname_directory;
    Object gensym_pathname_name, gensym_pathname_type, gensym_pathname_version;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(33,66);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
    gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
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
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_4,Qnil,Nil);
	      g2int_write_compound_component_for_namestring(gensym_pathname_directory,
		      list_constant_5,list_constant_6,Nil,list_constant_7,
		      Nil,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_version,
		      list_constant_8,list_constant_11,Nil);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object array_constant_4;    /* # */

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

/* GENERATE-VMS-NAMESTRING */
Object g2int_generate_vms_namestring(pathname_1)
    Object pathname_1;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object directory_length, match_1, match_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(33,67);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
    gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
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
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_12,Qnil,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_device,
		      list_constant_4,Qnil,Nil);
	      directory_length = length(gensym_pathname_directory);
	      match_1 = (SI_Long)0L < IFIX(directory_length) ? 
		      FIRST(gensym_pathname_directory) : Nil;
	      match_2 = (SI_Long)1L < IFIX(directory_length) ? 
		      SECOND(gensym_pathname_directory) : Nil;
	      if (IFIX(directory_length) >= (SI_Long)2L && EQ(Krelative,
		      match_1) && EQ(Kup,match_2))
		  g2int_write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  list_constant_16,Nil);
	      else if (IFIX(directory_length) == (SI_Long)1L && 
		      EQ(Kabsolute,match_1))
		  g2int_write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  array_constant_1,Nil);
	      else if (IFIX(directory_length) >= (SI_Long)2L && 
		      EQ(Kabsolute,match_1) && EQ(Kwild_inferiors,match_2))
		  g2int_write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  list_constant_17,Nil);
	      else if (IFIX(directory_length) >= (SI_Long)1L && 
		      EQ(Kabsolute,match_1))
		  g2int_write_compound_component_for_namestring(nthcdr(FIX((SI_Long)1L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  array_constant_4,Nil);
	      else
		  g2int_write_compound_component_for_namestring(gensym_pathname_directory,
			  list_constant_13,list_constant_14,T,
			  list_constant_15,Nil,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_version,
		      list_constant_18,list_constant_19,Nil);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

/* GENERATE-GENERALIZED-DOS-NAMESTRING */
Object g2int_generate_generalized_dos_namestring(pathname_1)
    Object pathname_1;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(33,68);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
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
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_20,Qnil,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_device,
		      list_constant_4,Qnil,Nil);
	      g2int_write_compound_component_for_namestring(gensym_pathname_directory,
		      list_constant_21,list_constant_6,Nil,
		      list_constant_22,Nil,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      g2int_write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GENERATE-DOS-NAMESTRING */
Object g2int_generate_dos_namestring(pathname_1)
    Object pathname_1;
{
    Object character_case_mode_for_generalized_dos;
    Declare_special(1);
    Object result;

    x_note_fn_call(33,69);
    character_case_mode_for_generalized_dos = Kall_uppercase;
    PUSH_SPECIAL(G2int_character_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
	    0);
      result = g2int_generate_generalized_dos_namestring(pathname_1);
    POP_SPECIAL();
    return result;
}

/* GENERATE-WIN32-NAMESTRING */
Object g2int_generate_win32_namestring(pathname_1)
    Object pathname_1;
{
    Object character_case_mode_for_generalized_dos;
    Declare_special(1);
    Object result;

    x_note_fn_call(33,70);
    character_case_mode_for_generalized_dos = Kcase_sensitive;
    PUSH_SPECIAL(G2int_character_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
	    0);
      result = g2int_generate_generalized_dos_namestring(pathname_1);
    POP_SPECIAL();
    return result;
}

void file_parse_INIT()
{
    Object temp, pushnew_arg_1, pushnew_arg_3;
    Object filename_special_character_registry_new_value;
    Object reclaim_structure_for_filename_parser_information;
    Object Qg2int_convert_file_strings_to_uppercase_p;
    Object Qg2int_generate_generalized_dos_namestring, list_constant_25;
    Object Qg2int_ltdotgt, Qg2int_ltbackslashgt, AB_package;
    Object Qg2int_generate_vms_namestring, array_constant_6, list_constant_23;
    Object Qg2int_ltsemicolongt, list_constant_28, Qg2int_lthyphengt;
    Object Qg2int_ltasteriskgt, Qg2int_ltright_bracketgt;
    Object Qg2int_ltleft_bracketgt, list_constant_29, list_constant_27;
    Object Qg2int_ltcolongt, Qg2int_generate_unix_namestring, array_constant_5;
    Object Qg2int_lttildegt, list_constant_26, Qg2int_ltslashgt;
    Object Qg2int_final_generalized_dos_parser_node;
    Object Qg2int_error_in_generalized_dos_filename_parser;
    Object Qg2int_parse_generalized_dos_filename_node_100;
    Object Qg2int_parse_generalized_dos_filename_node_101;
    Object Qg2int_parse_generalized_dos_filename_node_102;
    Object Qg2int_parse_generalized_dos_filename_node_103;
    Object Qg2int_parse_generalized_dos_filename_node_104;
    Object Qg2int_parse_generalized_dos_filename_node_105;
    Object Qg2int_parse_generalized_dos_filename_node_106;
    Object Qg2int_parse_generalized_dos_filename_node_108;
    Object Qg2int_parse_generalized_dos_filename_node_110;
    Object Qg2int_parse_generalized_dos_filename_node_111;
    Object Qg2int_parse_generalized_dos_filename, list_constant_24;
    Object Qg2int_final_vms_parser_node, Qg2int_error_in_vms_filename_parser;
    Object Qg2int_parse_vms_filename_node_101;
    Object Qg2int_parse_vms_filename_node_102;
    Object Qg2int_parse_vms_filename_node_103;
    Object Qg2int_parse_vms_filename_node_104;
    Object Qg2int_parse_vms_filename_node_105;
    Object Qg2int_parse_vms_filename_node_106;
    Object Qg2int_parse_vms_filename_node_107;
    Object Qg2int_parse_vms_filename_node_108;
    Object Qg2int_parse_vms_filename_node_109;
    Object Qg2int_parse_vms_filename_node_110;
    Object Qg2int_parse_vms_filename_node_111;
    Object Qg2int_parse_vms_filename_node_112;
    Object Qg2int_parse_vms_filename_node_113;
    Object Qg2int_parse_vms_filename_node_114, Qg2int_parse_vms_filename;
    Object Qg2int_ltspacegt, Qg2int_ltdouble_quotegt;
    Object Qg2int_final_unix_parser_node, Qg2int_error_in_unix_filename_parser;
    Object Qg2int_parse_unix_filename_node_100;
    Object Qg2int_parse_unix_filename_node_101;
    Object Qg2int_parse_unix_filename_node_102;
    Object Qg2int_parse_unix_filename_node_103;
    Object Qg2int_parse_unix_filename_node_104;
    Object Qg2int_parse_unix_filename_node_105;
    Object Qg2int_parse_unix_filename_node_106;
    Object Qg2int_parse_unix_filename_node_108;
    Object Qg2int_parse_unix_filename_node_109;
    Object Qg2int_parse_unix_filename_node_110;
    Object Qg2int_parse_unix_filename_node_111, Qg2int_parse_unix_filename;
    Object Qg2int_file_parse, Qg2int_accept_any_version_component_p;
    Object Qg2int_filename_parser_information, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_filename_parser_information_count;
    Object Qg2int_chain_of_available_filename_parser_informations;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_14, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_equalw;
    Object Qg2int_ltcommagt, Qg2int_ltexclamationgt, Qg2int_ltsharp_signgt;
    Object Qg2int_ltright_angle_bracketgt, Qg2int_ltleft_angle_bracketgt;

    x_note_fn_call(33,71);
    SET_PACKAGE("AB");
    if (G2int_filename_special_character_registry == UNBOUND)
	G2int_filename_special_character_registry = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_ltend_of_sequencegt = STATIC_SYMBOL("<END-OF-SEQUENCE>",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltend_of_sequencegt,
	    G2int_ltend_of_sequencegt);
    if (G2int_ltend_of_sequencegt == UNBOUND)
	G2int_ltend_of_sequencegt = Qg2int_ltend_of_sequencegt;
    Qg2int_ltcolongt = STATIC_SYMBOL("<COLON>",AB_package);
    Qg2int_equalw = STATIC_SYMBOL("EQUALW",AB_package);
    temp = FIX((SI_Long)58L);
    pushnew_arg_1 = CONS(Qg2int_ltcolongt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltcolongt,G2int_ltcolongt);
    if (G2int_ltcolongt == UNBOUND)
	G2int_ltcolongt = Qg2int_ltcolongt;
    Qg2int_ltslashgt = STATIC_SYMBOL("<SLASH>",AB_package);
    temp = FIX((SI_Long)47L);
    pushnew_arg_1 = CONS(Qg2int_ltslashgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltslashgt,G2int_ltslashgt);
    if (G2int_ltslashgt == UNBOUND)
	G2int_ltslashgt = Qg2int_ltslashgt;
    Qg2int_ltdotgt = STATIC_SYMBOL("<DOT>",AB_package);
    temp = FIX((SI_Long)46L);
    pushnew_arg_1 = CONS(Qg2int_ltdotgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltdotgt,G2int_ltdotgt);
    if (G2int_ltdotgt == UNBOUND)
	G2int_ltdotgt = Qg2int_ltdotgt;
    Qg2int_lttildegt = STATIC_SYMBOL("<TILDE>",AB_package);
    temp = FIX((SI_Long)126L);
    pushnew_arg_1 = CONS(Qg2int_lttildegt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_lttildegt,G2int_lttildegt);
    if (G2int_lttildegt == UNBOUND)
	G2int_lttildegt = Qg2int_lttildegt;
    Qg2int_ltasteriskgt = STATIC_SYMBOL("<ASTERISK>",AB_package);
    temp = FIX((SI_Long)42L);
    pushnew_arg_1 = CONS(Qg2int_ltasteriskgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltasteriskgt,G2int_ltasteriskgt);
    if (G2int_ltasteriskgt == UNBOUND)
	G2int_ltasteriskgt = Qg2int_ltasteriskgt;
    Qg2int_ltleft_bracketgt = STATIC_SYMBOL("<LEFT-BRACKET>",AB_package);
    temp = FIX((SI_Long)91L);
    pushnew_arg_1 = CONS(Qg2int_ltleft_bracketgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltleft_bracketgt,G2int_ltleft_bracketgt);
    if (G2int_ltleft_bracketgt == UNBOUND)
	G2int_ltleft_bracketgt = Qg2int_ltleft_bracketgt;
    Qg2int_ltright_bracketgt = STATIC_SYMBOL("<RIGHT-BRACKET>",AB_package);
    temp = FIX((SI_Long)93L);
    pushnew_arg_1 = CONS(Qg2int_ltright_bracketgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltright_bracketgt,
	    G2int_ltright_bracketgt);
    if (G2int_ltright_bracketgt == UNBOUND)
	G2int_ltright_bracketgt = Qg2int_ltright_bracketgt;
    Qg2int_ltsemicolongt = STATIC_SYMBOL("<SEMICOLON>",AB_package);
    temp = FIX((SI_Long)59L);
    pushnew_arg_1 = CONS(Qg2int_ltsemicolongt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltsemicolongt,G2int_ltsemicolongt);
    if (G2int_ltsemicolongt == UNBOUND)
	G2int_ltsemicolongt = Qg2int_ltsemicolongt;
    Qg2int_ltdouble_quotegt = STATIC_SYMBOL("<DOUBLE-QUOTE>",AB_package);
    temp = FIX((SI_Long)34L);
    pushnew_arg_1 = CONS(Qg2int_ltdouble_quotegt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltdouble_quotegt,G2int_ltdouble_quotegt);
    if (G2int_ltdouble_quotegt == UNBOUND)
	G2int_ltdouble_quotegt = Qg2int_ltdouble_quotegt;
    Qg2int_ltspacegt = STATIC_SYMBOL("<SPACE>",AB_package);
    temp = FIX((SI_Long)32L);
    pushnew_arg_1 = CONS(Qg2int_ltspacegt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltspacegt,G2int_ltspacegt);
    if (G2int_ltspacegt == UNBOUND)
	G2int_ltspacegt = Qg2int_ltspacegt;
    Qg2int_lthyphengt = STATIC_SYMBOL("<HYPHEN>",AB_package);
    temp = FIX((SI_Long)45L);
    pushnew_arg_1 = CONS(Qg2int_lthyphengt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_lthyphengt,G2int_lthyphengt);
    if (G2int_lthyphengt == UNBOUND)
	G2int_lthyphengt = Qg2int_lthyphengt;
    Qg2int_ltleft_angle_bracketgt = STATIC_SYMBOL("<LEFT-ANGLE-BRACKET>",
	    AB_package);
    temp = FIX((SI_Long)60L);
    pushnew_arg_1 = CONS(Qg2int_ltleft_angle_bracketgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltleft_angle_bracketgt,
	    G2int_ltleft_angle_bracketgt);
    if (G2int_ltleft_angle_bracketgt == UNBOUND)
	G2int_ltleft_angle_bracketgt = Qg2int_ltleft_angle_bracketgt;
    Qg2int_ltright_angle_bracketgt = STATIC_SYMBOL("<RIGHT-ANGLE-BRACKET>",
	    AB_package);
    temp = FIX((SI_Long)62L);
    pushnew_arg_1 = CONS(Qg2int_ltright_angle_bracketgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltright_angle_bracketgt,
	    G2int_ltright_angle_bracketgt);
    if (G2int_ltright_angle_bracketgt == UNBOUND)
	G2int_ltright_angle_bracketgt = Qg2int_ltright_angle_bracketgt;
    Qg2int_ltsharp_signgt = STATIC_SYMBOL("<SHARP-SIGN>",AB_package);
    temp = FIX((SI_Long)35L);
    pushnew_arg_1 = CONS(Qg2int_ltsharp_signgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltsharp_signgt,G2int_ltsharp_signgt);
    if (G2int_ltsharp_signgt == UNBOUND)
	G2int_ltsharp_signgt = Qg2int_ltsharp_signgt;
    Qg2int_ltexclamationgt = STATIC_SYMBOL("<EXCLAMATION>",AB_package);
    temp = FIX((SI_Long)33L);
    pushnew_arg_1 = CONS(Qg2int_ltexclamationgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltexclamationgt,G2int_ltexclamationgt);
    if (G2int_ltexclamationgt == UNBOUND)
	G2int_ltexclamationgt = Qg2int_ltexclamationgt;
    Qg2int_ltcommagt = STATIC_SYMBOL("<COMMA>",AB_package);
    temp = FIX((SI_Long)44L);
    pushnew_arg_1 = CONS(Qg2int_ltcommagt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltcommagt,G2int_ltcommagt);
    if (G2int_ltcommagt == UNBOUND)
	G2int_ltcommagt = Qg2int_ltcommagt;
    Qg2int_ltbackslashgt = STATIC_SYMBOL("<BACKSLASH>",AB_package);
    temp = FIX((SI_Long)92L);
    pushnew_arg_1 = CONS(Qg2int_ltbackslashgt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    G2int_filename_special_character_registry,Ktest,pushnew_arg_3);
    G2int_filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ltbackslashgt,G2int_ltbackslashgt);
    if (G2int_ltbackslashgt == UNBOUND)
	G2int_ltbackslashgt = Qg2int_ltbackslashgt;
    Kcase_sensitive = STATIC_SYMBOL("CASE-SENSITIVE",Pkeyword);
    Kall_uppercase = STATIC_SYMBOL("ALL-UPPERCASE",Pkeyword);
    Kall_lowercase = STATIC_SYMBOL("ALL-LOWERCASE",Pkeyword);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    if (G2int_trace_filename_parsing_p == UNBOUND)
	G2int_trace_filename_parsing_p = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_filename_parser_information_g2_struct = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_filename_parser_information = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    Qg2int_filename_parser_information,
	    Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_filename_parser_information,
	    Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_filename_parser_information == UNBOUND)
	G2int_the_type_description_of_filename_parser_information = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8l83--y1n83--y8m8k1l8m0000001m1n8n83*my01m8p8308ykuk0k0");
    temp = G2int_the_type_description_of_filename_parser_information;
    G2int_the_type_description_of_filename_parser_information = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_14));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    G2int_the_type_description_of_filename_parser_information,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_filename_parser_information,
	    G2int_the_type_description_of_filename_parser_information,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_filename_parser_informations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FILENAME-PARSER-INFORMATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_filename_parser_informations,
	    G2int_chain_of_available_filename_parser_informations);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_filename_parser_informations,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_filename_parser_information_count = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_filename_parser_information_count,
	    G2int_filename_parser_information_count);
    g2int_record_system_variable(Qg2int_filename_parser_information_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_filename_parser_information = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_filename_parser_information,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_filename_parser_information,
	    reclaim_structure_for_filename_parser_information);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_filename_parser_of_file_system = 
	    STATIC_SYMBOL("FILENAME-PARSER-OF-FILE-SYSTEM",AB_package);
    G2int_filename_parser_of_file_system_prop = 
	    Qg2int_filename_parser_of_file_system;
    Qg2int_namestring_generator_of_file_system = 
	    STATIC_SYMBOL("NAMESTRING-GENERATOR-OF-FILE-SYSTEM",AB_package);
    G2int_namestring_generator_of_file_system_prop = 
	    Qg2int_namestring_generator_of_file_system;
    if (G2int_all_known_file_systems == UNBOUND)
	G2int_all_known_file_systems = Nil;
    Qg2int_accept_any_version_component_p = 
	    STATIC_SYMBOL("ACCEPT-ANY-VERSION-COMPONENT-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_accept_any_version_component_p,
	    G2int_accept_any_version_component_p);
    Qg2int_file_parse = STATIC_SYMBOL("FILE-PARSE",AB_package);
    g2int_record_system_variable(Qg2int_accept_any_version_component_p,
	    Qg2int_file_parse,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_parse_unix_filename = STATIC_SYMBOL("PARSE-UNIX-FILENAME",
	    AB_package);
    Qg2int_convert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    g2int_mutate_global_property(Qg2int_parse_unix_filename,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    Qg2int_unix = STATIC_SYMBOL("UNIX",AB_package);
    g2int_mutate_global_property(Qg2int_unix,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_unix,Qg2int_parse_unix_filename,
	    Qg2int_filename_parser_of_file_system);
    if (G2int_nodes_for_unix_filename_parser == UNBOUND)
	G2int_nodes_for_unix_filename_parser = Nil;
    Qg2int_catcher_for_filename_parse_error = 
	    STATIC_SYMBOL("CATCHER-FOR-FILENAME-PARSE-ERROR",AB_package);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    Khome = STATIC_SYMBOL("HOME",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)4L,Krelative,Kabsolute,Khome,Kup);
    string_constant = STATIC_STRING(".");
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qg2int_ltdotgt,
	    Qg2int_lttildegt,Qg2int_ltslashgt,Qg2int_ltcolongt,
	    Qg2int_ltasteriskgt);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename,
	    STATIC_FUNCTION(g2int_parse_unix_filename,NIL,FALSE,1,1));
    Qg2int_parse_unix_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-111",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_111,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_111,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-110",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_110,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_110,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_109 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-109",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_109,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_109,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-108",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_108,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_108,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-106",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_106,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_106,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-105",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_105,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_105,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-104",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_104,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_104,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-103",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_103,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_103,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-102",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_102,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_102,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-101",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_101,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_101,NIL,FALSE,
	    12,12));
    Qg2int_parse_unix_filename_node_100 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-100",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_100,
	    STATIC_FUNCTION(g2int_parse_unix_filename_node_100,NIL,FALSE,
	    12,12));
    Qg2int_error_in_unix_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-UNIX-FILENAME-PARSER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_error_in_unix_filename_parser,
	    STATIC_FUNCTION(g2int_error_in_unix_filename_parser,NIL,FALSE,
	    1,1));
    Qg2int_final_unix_parser_node = STATIC_SYMBOL("FINAL-UNIX-PARSER-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_final_unix_parser_node,
	    STATIC_FUNCTION(g2int_final_unix_parser_node,NIL,FALSE,12,12));
    G2int_nodes_for_unix_filename_parser = make_array(5,FIX((SI_Long)13L),
	    Kelement_type,T,Kinitial_contents,list(13,
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_111),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_110),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_109),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_108),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_106),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_105),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_104),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_103),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_102),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_101),
	    SYMBOL_FUNCTION(Qg2int_parse_unix_filename_node_100),
	    SYMBOL_FUNCTION(Qg2int_error_in_unix_filename_parser),
	    SYMBOL_FUNCTION(Qg2int_final_unix_parser_node)));
    if (G2int_vms_directory_filenames_can_dangle_p == UNBOUND)
	G2int_vms_directory_filenames_can_dangle_p = Nil;
    Qg2int_parse_vms_filename = STATIC_SYMBOL("PARSE-VMS-FILENAME",AB_package);
    g2int_mutate_global_property(Qg2int_parse_vms_filename,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    Qg2int_vms = STATIC_SYMBOL("VMS",AB_package);
    g2int_mutate_global_property(Qg2int_vms,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_vms,Qg2int_parse_vms_filename,
	    Qg2int_filename_parser_of_file_system);
    if (G2int_nodes_for_vms_filename_parser == UNBOUND)
	G2int_nodes_for_vms_filename_parser = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING("empty relative VMS pathname");
    string_constant_2 = STATIC_STRING("VMS directory not supplied after [");
    string_constant_3 = 
	    STATIC_STRING("second directory spec can\'t have initial :up marker");
    string_constant_4 = 
	    STATIC_STRING("dual directory syntax not permited in this context");
    string_constant_5 = 
	    STATIC_STRING("dual directory syntax can\'t be cascaded");
    string_constant_6 = STATIC_STRING("second directory spec cannot be empty");
    string_constant_7 = STATIC_STRING("VMS directory not terminated with ]");
    array_constant_2 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING("non-numeric version");
    string_constant_9 = STATIC_STRING("bad constituent char");
    list_constant_2 = STATIC_LIST((SI_Long)9L,Qg2int_ltcolongt,
	    Qg2int_ltdotgt,Qg2int_ltasteriskgt,Qg2int_ltleft_bracketgt,
	    Qg2int_ltright_bracketgt,Qg2int_ltsemicolongt,
	    Qg2int_ltdouble_quotegt,Qg2int_ltspacegt,Qg2int_lthyphengt);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename,
	    STATIC_FUNCTION(g2int_parse_vms_filename,NIL,FALSE,1,1));
    Qg2int_parse_vms_filename_node_114 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-114",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_114,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_114,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_113 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-113",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_113,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_113,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_112 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-112",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_112,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_112,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-111",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_111,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_111,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-110",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_110,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_110,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_109 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-109",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_109,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_109,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-108",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_108,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_108,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_107 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-107",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_107,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_107,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-106",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_106,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_106,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-105",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_105,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_105,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-104",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_104,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_104,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-103",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_103,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_103,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-102",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_102,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_102,NIL,FALSE,14,
	    14));
    Qg2int_parse_vms_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-101",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_101,
	    STATIC_FUNCTION(g2int_parse_vms_filename_node_101,NIL,FALSE,14,
	    14));
    Qg2int_error_in_vms_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-VMS-FILENAME-PARSER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_error_in_vms_filename_parser,
	    STATIC_FUNCTION(g2int_error_in_vms_filename_parser,NIL,FALSE,1,1));
    Qg2int_final_vms_parser_node = STATIC_SYMBOL("FINAL-VMS-PARSER-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_final_vms_parser_node,
	    STATIC_FUNCTION(g2int_final_vms_parser_node,NIL,FALSE,14,14));
    G2int_nodes_for_vms_filename_parser = make_array(5,FIX((SI_Long)16L),
	    Kelement_type,T,Kinitial_contents,list(16,
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_114),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_113),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_112),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_111),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_110),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_109),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_108),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_107),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_106),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_105),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_104),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_103),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_102),
	    SYMBOL_FUNCTION(Qg2int_parse_vms_filename_node_101),
	    SYMBOL_FUNCTION(Qg2int_error_in_vms_filename_parser),
	    SYMBOL_FUNCTION(Qg2int_final_vms_parser_node)));
    Qg2int_parse_generalized_dos_filename = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME",AB_package);
    g2int_mutate_global_property(Qg2int_parse_generalized_dos_filename,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    Qg2int_generalized_dos = STATIC_SYMBOL("GENERALIZED-DOS",AB_package);
    g2int_mutate_global_property(Qg2int_generalized_dos,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_generalized_dos,
	    Qg2int_parse_generalized_dos_filename,
	    Qg2int_filename_parser_of_file_system);
    if (G2int_nodes_for_generalized_dos_filename_parser == UNBOUND)
	G2int_nodes_for_generalized_dos_filename_parser = Nil;
    string_constant_10 = STATIC_STRING("device must only have one letter");
    string_constant_11 = STATIC_STRING("no wildcards allowed in directory");
    string_constant_12 = STATIC_STRING("file type required");
    string_constant_13 = STATIC_STRING("over 63 characters in filename");
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qg2int_ltcolongt,
	    Qg2int_ltasteriskgt);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qg2int_ltdotgt,
	    Qg2int_ltbackslashgt,list_constant_24);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename,NIL,FALSE,
	    1,1));
    Qg2int_parse_generalized_dos_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-111",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_111,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_111,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-110",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_110,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_110,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-108",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_108,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_108,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-106",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_106,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_106,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-105",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_105,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_105,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-104",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_104,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_104,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-103",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_103,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_103,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-102",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_102,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_102,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-101",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_101,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_101,
	    NIL,FALSE,13,13));
    Qg2int_parse_generalized_dos_filename_node_100 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-100",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_100,
	    STATIC_FUNCTION(g2int_parse_generalized_dos_filename_node_100,
	    NIL,FALSE,13,13));
    Qg2int_error_in_generalized_dos_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-GENERALIZED-DOS-FILENAME-PARSER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_error_in_generalized_dos_filename_parser,
	    STATIC_FUNCTION(g2int_error_in_generalized_dos_filename_parser,
	    NIL,FALSE,1,1));
    Qg2int_final_generalized_dos_parser_node = 
	    STATIC_SYMBOL("FINAL-GENERALIZED-DOS-PARSER-NODE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_final_generalized_dos_parser_node,
	    STATIC_FUNCTION(g2int_final_generalized_dos_parser_node,NIL,
	    FALSE,13,13));
    G2int_nodes_for_generalized_dos_filename_parser = make_array(5,
	    FIX((SI_Long)12L),Kelement_type,T,Kinitial_contents,list(12,
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_111),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_110),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_108),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_106),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_105),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_104),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_103),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_102),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_101),
	    SYMBOL_FUNCTION(Qg2int_parse_generalized_dos_filename_node_100),
	    SYMBOL_FUNCTION(Qg2int_error_in_generalized_dos_filename_parser),
	    SYMBOL_FUNCTION(Qg2int_final_generalized_dos_parser_node)));
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
    Qg2int_parse_dos_filename = STATIC_SYMBOL("PARSE-DOS-FILENAME",AB_package);
    Qg2int_generate_dos_namestring = 
	    STATIC_SYMBOL("GENERATE-DOS-NAMESTRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_dos_filename,
	    STATIC_FUNCTION(g2int_parse_dos_filename,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_dos,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_parse_dos_filename,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_dos,Qg2int_parse_dos_filename,
	    Qg2int_filename_parser_of_file_system);
    Qg2int_win32 = STATIC_SYMBOL("WIN32",AB_package);
    Qg2int_parse_win32_filename = STATIC_SYMBOL("PARSE-WIN32-FILENAME",
	    AB_package);
    Qg2int_generate_win32_namestring = 
	    STATIC_SYMBOL("GENERATE-WIN32-NAMESTRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_parse_win32_filename,
	    STATIC_FUNCTION(g2int_parse_win32_filename,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_win32,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_parse_win32_filename,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_win32,Qg2int_parse_win32_filename,
	    Qg2int_filename_parser_of_file_system);
    if (G2int_last_deletable_token_in_namestring == UNBOUND)
	G2int_last_deletable_token_in_namestring = Nil;
    Qg2int_exdeleteex = STATIC_SYMBOL("!DELETE!",AB_package);
    Qg2int_exdeletableex = STATIC_SYMBOL("!DELETABLE!",AB_package);
    Kcomponent = STATIC_SYMBOL("COMPONENT",Pkeyword);
    Kleading_items = STATIC_SYMBOL("LEADING-ITEMS",Pkeyword);
    Klast_item = STATIC_SYMBOL("LAST-ITEM",Pkeyword);
    Kcompound = STATIC_SYMBOL("COMPOUND",Pkeyword);
    Qg2int_generate_unix_namestring = 
	    STATIC_SYMBOL("GENERATE-UNIX-NAMESTRING",AB_package);
    g2int_mutate_global_property(Qg2int_generate_unix_namestring,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_unix,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_unix,
	    Qg2int_generate_unix_namestring,
	    Qg2int_namestring_generator_of_file_system);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kcomponent,Qg2int_ltcolongt);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kcomponent,Qg2int_ltslashgt);
    list_constant_6 = STATIC_CONS(Kcompound,Qnil);
    array_constant_4 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qg2int_ltdotgt,Qg2int_ltdotgt);
    list_constant_7 = STATIC_LIST((SI_Long)10L,Kabsolute,array_constant_4,
	    Krelative,Qg2int_ltdotgt,Kup,list_constant_25,Kwild,
	    Qg2int_ltasteriskgt,Khome,Qg2int_lttildegt);
    list_constant_8 = STATIC_CONS(Kcomponent,Qnil);
    list_constant_26 = STATIC_CONS(Qg2int_ltasteriskgt,Qnil);
    list_constant_9 = STATIC_CONS(Kwild,list_constant_26);
    list_constant_10 = STATIC_CONS(Qg2int_ltdotgt,list_constant_8);
    array_constant_5 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    list_constant_11 = STATIC_LIST((SI_Long)6L,Kprevious,Qg2int_lttildegt,
	    Knewest,array_constant_4,Kwild,array_constant_5);
    SET_SYMBOL_FUNCTION(Qg2int_generate_unix_namestring,
	    STATIC_FUNCTION(g2int_generate_unix_namestring,NIL,FALSE,1,1));
    Qg2int_generate_vms_namestring = 
	    STATIC_SYMBOL("GENERATE-VMS-NAMESTRING",AB_package);
    g2int_mutate_global_property(Qg2int_generate_vms_namestring,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_vms,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_vms,Qg2int_generate_vms_namestring,
	    Qg2int_namestring_generator_of_file_system);
    list_constant_27 = STATIC_CONS(Qg2int_ltcolongt,Qnil);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)3L,Kcomponent,
	    Qg2int_ltcolongt,list_constant_27);
    list_constant_28 = STATIC_CONS(Qg2int_ltdotgt,Qnil);
    list_constant_29 = STATIC_CONS(Kcomponent,list_constant_28);
    list_constant_13 = STATIC_LIST((SI_Long)4L,Kleading_items,
	    list_constant_29,Klast_item,list_constant_8);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qg2int_ltleft_bracketgt,
	    Kcompound,Qg2int_ltright_bracketgt);
    list_constant_15 = STATIC_LIST((SI_Long)8L,Kup,Qg2int_lthyphengt,Kwild,
	    Qg2int_ltasteriskgt,Kwild_inferiors,list_constant_25,Krelative,
	    array_constant_4);
    list_constant_16 = STATIC_CONS(Qg2int_lthyphengt,list_constant_28);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,array_constant_1,
	    Qg2int_ltdotgt,list_constant_25);
    list_constant_18 = STATIC_CONS(Qg2int_ltsemicolongt,list_constant_8);
    array_constant_6 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    list_constant_19 = STATIC_LIST_STAR((SI_Long)5L,Kprevious,
	    array_constant_6,Knewest,array_constant_3,list_constant_9);
    SET_SYMBOL_FUNCTION(Qg2int_generate_vms_namestring,
	    STATIC_FUNCTION(g2int_generate_vms_namestring,NIL,FALSE,1,1));
    Qg2int_generate_generalized_dos_namestring = 
	    STATIC_SYMBOL("GENERATE-GENERALIZED-DOS-NAMESTRING",AB_package);
    g2int_mutate_global_property(Qg2int_generate_generalized_dos_namestring,
	    Nil,Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_generalized_dos,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_generalized_dos,
	    Qg2int_generate_generalized_dos_namestring,
	    Qg2int_namestring_generator_of_file_system);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)3L,Qg2int_ltbackslashgt,
	    Qg2int_ltbackslashgt,list_constant_8);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Kcomponent,
	    Qg2int_ltbackslashgt);
    list_constant_22 = STATIC_LIST((SI_Long)6L,Kabsolute,array_constant_4,
	    Krelative,Qg2int_ltdotgt,Kup,list_constant_25);
    SET_SYMBOL_FUNCTION(Qg2int_generate_generalized_dos_namestring,
	    STATIC_FUNCTION(g2int_generate_generalized_dos_namestring,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2int_generate_dos_namestring,
	    STATIC_FUNCTION(g2int_generate_dos_namestring,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_generate_dos_namestring,T,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_dos,Qg2int_generate_dos_namestring,
	    Qg2int_namestring_generator_of_file_system);
    SET_SYMBOL_FUNCTION(Qg2int_generate_win32_namestring,
	    STATIC_FUNCTION(g2int_generate_win32_namestring,NIL,FALSE,1,1));
    g2int_mutate_global_property(Qg2int_generate_win32_namestring,Nil,
	    Qg2int_convert_file_strings_to_uppercase_p);
    g2int_mutate_global_property(Qg2int_win32,
	    Qg2int_generate_win32_namestring,
	    Qg2int_namestring_generator_of_file_system);
}
