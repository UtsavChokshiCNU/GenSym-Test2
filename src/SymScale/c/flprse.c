/* flprse.c
 * Input file:  file-parse.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "flprse.h"


DEFINE_VARIABLE_WITH_SYMBOL(Filename_special_character_registry, Qfilename_special_character_registry);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_end_of_sequence_gt, Qlt_end_of_sequence_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_colon_gt, Qlt_colon_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_slash_gt, Qlt_slash_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_dot_gt, Qlt_dot_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_tilde_gt, Qlt_tilde_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_asterisk_gt, Qlt_asterisk_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_left_bracket_gt, Qlt_left_bracket_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_right_bracket_gt, Qlt_right_bracket_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_semicolon_gt, Qlt_semicolon_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_double_quote_gt, Qlt_double_quote_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_space_gt, Qlt_space_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_hyphen_gt, Qlt_hyphen_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_left_angle_bracket_gt, Qlt_left_angle_bracket_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_right_angle_bracket_gt, Qlt_right_angle_bracket_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_sharp_sign_gt, Qlt_sharp_sign_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_exclamation_gt, Qlt_exclamation_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_comma_gt, Qlt_comma_gt);

DEFINE_VARIABLE_WITH_SYMBOL(Lt_backslash_gt, Qlt_backslash_gt);

static Object Kcase_sensitive;     /* :case-sensitive */

static Object Kall_uppercase;      /* :all-uppercase */

static Object Kall_lowercase;      /* :all-lowercase */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* TOKENIZE-FILENAME */
Object tokenize_filename varargs_1(int, n)
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

    x_note_fn_call(40,0);
    INIT_ARGS_nonrelocating();
    filename = REQUIRED_ARG_nonrelocating();
    special_characters = REQUIRED_ARG_nonrelocating();
    character_case_mode = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Kcase_sensitive;
    END_ARGS_nonrelocating();
    text_string_copy = copy_text_string(filename);
    if (EQ(character_case_mode,Kcase_sensitive))
	private_filename = text_string_copy;
    else if (EQ(character_case_mode,Kall_uppercase))
	private_filename = nstring_upcasew(text_string_copy);
    else if (EQ(character_case_mode,Kall_lowercase))
	private_filename = nstring_downcasew(text_string_copy);
    else
	private_filename = Qnil;
    tokenized_filename = Nil;
    entry = Nil;
    ab_loop_list_ = Filename_special_character_registry;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (wide_character_member(CAR(entry),special_characters)) {
	ab_loopvar__2 = path_cons_1(entry,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    special_character_registry = ab_loopvar_;
    goto end_1;
    special_character_registry = Qnil;
  end_1:;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(private_filename));
    char_1 = Nil;
    accumulated_chars = Nil;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    char_1 = FIX(UBYTE_16_ISAREF_1(private_filename,index_1));
    special_character_entry = wide_character_rassoc(char_1,
	    special_character_registry);
    if (special_character_entry) {
	if (accumulated_chars) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      accumulated_char = Nil;
		      accumulated_chars = nreverse(accumulated_chars);
		      ab_loop_list_ = accumulated_chars;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      accumulated_char = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = accumulated_char;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = accumulated_char;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      goto next_loop_2;
		    end_loop_2:;
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    tokenized_filename = path_cons_1(temp_1,tokenized_filename);
	    reclaim_path_list_1(accumulated_chars);
	    accumulated_chars = Nil;
	}
	tokenized_filename = path_cons_1(CAR(special_character_entry),
		tokenized_filename);
    }
    else
	accumulated_chars = path_cons_1(char_1,accumulated_chars);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    if (accumulated_chars) {
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
		  accumulated_char = Nil;
		  accumulated_chars = nreverse(accumulated_chars);
		  ab_loop_list_ = accumulated_chars;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  accumulated_char = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = accumulated_char;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = accumulated_char;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  goto next_loop_3;
		end_loop_3:;
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	tokenized_filename = path_cons_1(temp_1,tokenized_filename);
	reclaim_path_list_1(accumulated_chars);
    }
    reclaim_path_list_1(special_character_registry);
    reclaim_text_string(private_filename);
    return nreverse(path_cons_1(Qlt_end_of_sequence_gt,tokenized_filename));
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trace_filename_parsing_p, Qtrace_filename_parsing_p);

Object The_type_description_of_filename_parser_information = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_filename_parser_informations, Qchain_of_available_filename_parser_informations);

DEFINE_VARIABLE_WITH_SYMBOL(Filename_parser_information_count, Qfilename_parser_information_count);

Object Chain_of_available_filename_parser_informations_vector = UNBOUND;

/* FILENAME-PARSER-INFORMATION-STRUCTURE-MEMORY-USAGE */
Object filename_parser_information_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(40,1);
    temp = Filename_parser_information_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FILENAME-PARSER-INFORMATION-COUNT */
Object outstanding_filename_parser_information_count()
{
    Object def_structure_filename_parser_information_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(40,2);
    gensymed_symbol = IFIX(Filename_parser_information_count);
    def_structure_filename_parser_information_variable = 
	    Chain_of_available_filename_parser_informations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_filename_parser_information_variable))
	goto end_loop;
    def_structure_filename_parser_information_variable = 
	    ISVREF(def_structure_filename_parser_information_variable,
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

/* RECLAIM-FILENAME-PARSER-INFORMATION-INTERNAL-1 */
Object reclaim_filename_parser_information_internal_1(filename_parser_information)
    Object filename_parser_information;
{
    Object temp, svref_arg_2;

    x_note_fn_call(40,3);
    inline_note_reclaim_cons(filename_parser_information,Nil);
    temp = ISVREF(Chain_of_available_filename_parser_informations_vector,
	    IFIX(Current_thread_index));
    SVREF(filename_parser_information,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_filename_parser_informations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = filename_parser_information;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FILENAME-PARSER-INFORMATION */
Object reclaim_structure_for_filename_parser_information(filename_parser_information)
    Object filename_parser_information;
{
    x_note_fn_call(40,4);
    return reclaim_filename_parser_information_internal_1(filename_parser_information);
}

static Object Qg2_defstruct_structure_name_filename_parser_information_g2_struct;  /* g2-defstruct-structure-name::filename-parser-information-g2-struct */

/* MAKE-PERMANENT-FILENAME-PARSER-INFORMATION-STRUCTURE-INTERNAL */
Object make_permanent_filename_parser_information_structure_internal()
{
    Object def_structure_filename_parser_information_variable;
    Object defstruct_g2_filename_parser_information_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(40,5);
    def_structure_filename_parser_information_variable = Nil;
    atomic_incff_symval(Qfilename_parser_information_count,FIX((SI_Long)1L));
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
Object make_filename_parser_information_1()
{
    Object def_structure_filename_parser_information_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(40,6);
    def_structure_filename_parser_information_variable = 
	    ISVREF(Chain_of_available_filename_parser_informations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_filename_parser_information_variable) {
	svref_arg_1 = Chain_of_available_filename_parser_informations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_filename_parser_information_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_filename_parser_information_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_filename_parser_information_g2_struct;
    }
    else
	def_structure_filename_parser_information_variable = 
		make_permanent_filename_parser_information_structure_internal();
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
Object reclaim_filename_parser_information(parser_info)
    Object parser_info;
{
    Object previous_stack, entry, ab_loop_list_, token;

    x_note_fn_call(40,7);
    reclaim_path_list_1(ISVREF(parser_info,(SI_Long)2L));
    previous_stack = ISVREF(parser_info,(SI_Long)4L);
    entry = Nil;
    ab_loop_list_ = previous_stack;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_path_list_1(THIRD(entry));
    reclaim_path_list_1(entry);
    goto next_loop;
  end_loop:
    reclaim_path_list_1(previous_stack);
    token = Nil;
    ab_loop_list_ = ISVREF(parser_info,(SI_Long)1L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    token = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (text_string_p(token))
	reclaim_text_string(token);
    goto next_loop_1;
  end_loop_1:
    reclaim_path_list_1(ISVREF(parser_info,(SI_Long)1L));
    return reclaim_filename_parser_information_internal_1(parser_info);
}

/* COALESCE-FILENAME-TOKENS-1 */
Object coalesce_filename_tokens_1(words_and_punct)
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

    x_note_fn_call(40,8);
    if (SYMBOLP(words_and_punct)) {
	entry = assoc_eql(words_and_punct,Filename_special_character_registry);
	if (entry) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      simple_or_wide_character = CDR(entry);
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
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = simple_or_wide_character;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      result = copy_out_current_wide_string();
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
		  section = Nil;
		  ab_loop_list_ = words_and_punct;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  section = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (text_string_p(section) || STRINGP(section))
		      twrite_general_string(section);
		  else if (EQ(Qlt_end_of_sequence_gt,section));
		  else {
		      entry = assoc_eql(section,
			      Filename_special_character_registry);
		      if (entry) {
			  simple_or_wide_character = CDR(entry);
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
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = simple_or_wide_character;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
		      }
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
}

/* COALESCE-FILENAME-SUBLISTS-1 */
Object coalesce_filename_sublists_1(sublists)
    Object sublists;
{
    Object sublists_in_order, sublist_item, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(40,9);
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
		path_cons_1(coalesce_filename_tokens_1(sublist_item),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if (CONSP(sublist_item))
	    reclaim_path_list_1(sublist_item);
	goto next_loop;
      end_loop:
	reclaim_path_list_1(sublists_in_order);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COALESCE-REVERSED-FILENAME-LIST-1 */
Object coalesce_reversed_filename_list_1(reversed_list)
    Object reversed_list;
{
    Object list_in_order, temp;

    x_note_fn_call(40,10);
    list_in_order = nreverse(reversed_list);
    temp = coalesce_filename_tokens_1(list_in_order);
    reclaim_path_list_1(list_in_order);
    return VALUES_1(temp);
}

/* COALESCE-FILENAME-ITEMS-1 */
Object coalesce_filename_items_1(item_list)
    Object item_list;
{
    Object temp;

    x_note_fn_call(40,11);
    temp = coalesce_filename_tokens_1(item_list);
    reclaim_path_list_1(item_list);
    return VALUES_1(temp);
}

/* COALESCE-REMAINDER-OF-FILENAME-SEQUENCE-1 */
Object coalesce_remainder_of_filename_sequence_1(parser_info)
    Object parser_info;
{
    x_note_fn_call(40,12);
    return coalesce_filename_tokens_1(nthcdr(ISVREF(parser_info,
	    (SI_Long)7L),ISVREF(parser_info,(SI_Long)2L)));
}

/* CHANGE-FILENAME-SEQUENCE-TO-1 */
Object change_filename_sequence_to_1(new_sequence,parser_info,increment)
    Object new_sequence, parser_info, increment;
{
    Object end_of_sequence_list, path_push_modify_macro_arg, car_1, cdr_1;
    Object temp, copy_of_new_sequence;

    x_note_fn_call(40,13);
    end_of_sequence_list = path_cons_1(Qlt_end_of_sequence_gt,Nil);
    path_push_modify_macro_arg = path_list_3(FIXNUM_ADD(ISVREF(parser_info,
	    (SI_Long)7L),increment),ISVREF(parser_info,(SI_Long)3L),
	    ISVREF(parser_info,(SI_Long)2L));
    car_1 = path_push_modify_macro_arg;
    cdr_1 = ISVREF(parser_info,(SI_Long)4L);
    temp = path_cons_1(car_1,cdr_1);
    SVREF(parser_info,FIX((SI_Long)4L)) = temp;
    temp = FIXNUM_NEGATE(increment);
    SVREF(parser_info,FIX((SI_Long)7L)) = temp;
    temp = add1(length(new_sequence));
    SVREF(parser_info,FIX((SI_Long)3L)) = temp;
    if (new_sequence) {
	copy_of_new_sequence = copy_list_using_path_conses_1(new_sequence);
	temp = last(copy_of_new_sequence,_);
	M_CDR(temp) = end_of_sequence_list;
	SVREF(parser_info,FIX((SI_Long)2L)) = copy_of_new_sequence;
    }
    else
	SVREF(parser_info,FIX((SI_Long)2L)) = end_of_sequence_list;
    return VALUES_1(Nil);
}

static Object Qpath;               /* path */

/* RESUME-PREVIOUS-FILENAME-SEQUENCE-1 */
Object resume_previous_filename_sequence_1(parser_info)
    Object parser_info;
{
    Object path_pop_store, cons_1, next_cons, temp, svref_arg_2, previous_info;

    x_note_fn_call(40,14);
    path_pop_store = Nil;
    cons_1 = ISVREF(parser_info,(SI_Long)4L);
    if (cons_1) {
	path_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpath);
	if (ISVREF(Available_path_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    SVREF(parser_info,FIX((SI_Long)4L)) = next_cons;
    previous_info = path_pop_store;
    reclaim_path_list_1(ISVREF(parser_info,(SI_Long)2L));
    temp = FIRST(previous_info);
    SVREF(parser_info,FIX((SI_Long)7L)) = temp;
    temp = SECOND(previous_info);
    SVREF(parser_info,FIX((SI_Long)3L)) = temp;
    temp = THIRD(previous_info);
    SVREF(parser_info,FIX((SI_Long)2L)) = temp;
    return reclaim_path_list_1(previous_info);
}

/* ERROR-IN-FILENAME-PARSE-1 */
Object error_in_filename_parse_1(string_1,parser_info)
    Object string_1, parser_info;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(40,15);
    gensymed_symbol = ISVREF(parser_info,(SI_Long)6L);
    gensymed_symbol_1 = parser_info;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

Object Filename_parser_of_file_system_prop = UNBOUND;

Object Namestring_generator_of_file_system_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_known_file_systems, Qall_known_file_systems);

DEFINE_VARIABLE_WITH_SYMBOL(Accept_any_version_component_p, Qaccept_any_version_component_p);

DEFINE_VARIABLE_WITH_SYMBOL(Nodes_for_unix_filename_parser, Qnodes_for_unix_filename_parser);

static Object Qcatcher_for_filename_parse_error;  /* catcher-for-filename-parse-error */

/* ERROR-IN-UNIX-FILENAME-PARSER */
Object error_in_unix_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(40,16);
    reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qcatcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qunix;               /* unix */

static Object Qfilename_parser_of_file_system;  /* filename-parser-of-file-system */

static Object Qnamestring_generator_of_file_system;  /* namestring-generator-of-file-system */

/* FINAL-UNIX-PARSER-NODE */
Object final_unix_parser_node(parser_info,host,device,directory_1,name,
	    type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(40,17);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = make_gensym_pathname_structure_function(host,
		device,directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qunix;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunix),
		Qfilename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunix),
		Qnamestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-UNIX-FILENAME-NODE-100 */
Object parse_unix_filename_node_100(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(40,18);
    next_node = Nil;
    device = Kunspecific;
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)9L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object Kabsolute;           /* :absolute */

static Object array_constant;      /* # */

/* PARSE-UNIX-FILENAME-NODE-101 */
Object parse_unix_filename_node_101(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
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

    x_note_fn_call(40,19);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt) && 
		EQ(match_2,Lt_slash_gt)) {
	    lt_word_gt = match_0;
	    host = copy_text_string(lt_word_gt);
	    directory_list = path_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_3 = nth(match_pointer,filename_sequence);
    if (match_3) {
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt) && 
		string_eq_w(array_constant,match_2) && EQ(match_3,
		    Lt_slash_gt)) {
	    lt_word_gt = match_0;
	    host = copy_text_string(lt_word_gt);
	    directory_list = path_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_slash_gt)) {
	directory_list = path_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
	goto parser_traverse;
    }
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

static Object Krelative;           /* :relative */

/* PARSE-UNIX-FILENAME-NODE-102 */
Object parse_unix_filename_node_102(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(40,20);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_slash_gt)) {
	directory_item = nreverse(directory_item);
	change_filename_sequence_to_1(directory_item,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)7L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	directory_1 = coalesce_filename_sublists_1(directory_list);
	if (directory_1) {
	    if ( !TRUEP(memq_function(CAR(directory_1),list_constant)))
		directory_1 = path_cons_1(Krelative,directory_1);
	}
	name_type_version_list = nreverse(directory_item);
	change_filename_sequence_to_1(name_type_version_list,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)5L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	directory_item = path_cons_1(lt_anything_gt,directory_item);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
	goto parser_traverse;
    }
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object Khome;               /* :home */

/* PARSE-UNIX-FILENAME-NODE-103 */
Object parse_unix_filename_node_103(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, svref_new_value;
    SI_Long svref_new_value_1;

    x_note_fn_call(40,21);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,Lt_tilde_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Khome,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Krelative,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_dot_gt) && EQ(match_2,
		Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Kup,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Kwild,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    directory_list = 
	    path_cons_1(copy_list_using_path_conses_1(directory_item),
	    directory_list);
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-104 */
Object parse_unix_filename_node_104(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(40,22);
    next_node = Nil;
    reclaim_path_list_1(directory_item);
    directory_item = Nil;
    resume_previous_filename_sequence_1(parser_info);
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-105 */
Object parse_unix_filename_node_105(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, temp;
    Object new_directory_component;
    SI_Long svref_new_value;

    x_note_fn_call(40,23);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	temp = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = temp;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    new_directory_component = path_cons_1(Krelative,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_dot_gt) && EQ(match_2,
		Lt_end_of_sequence_gt)) {
	    new_directory_component = path_cons_1(Kup,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_tilde_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_dot_gt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)3L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)4L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-106 */
Object parse_unix_filename_node_106(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, svref_new_value_1, lt_anything_gt;
    SI_Long svref_new_value;

    x_note_fn_call(40,24);
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
	if (EQ(match_0,Lt_tilde_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    name = coalesce_reversed_filename_list_1(name_list);
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_dot_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)3L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	name_list = path_cons_1(lt_anything_gt,name_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)4L);
	goto parser_traverse;
    }
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-108 */
Object parse_unix_filename_node_108(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(40,25);
    next_node = Nil;
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)2L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-109 */
Object parse_unix_filename_node_109(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(40,26);
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
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)1L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "." */

/* PARSE-UNIX-FILENAME-NODE-110 */
Object parse_unix_filename_node_110(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, svref_new_value_1, lt_anything_gt;
    SI_Long svref_new_value;

    x_note_fn_call(40,27);
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
	if (EQ(match_0,Lt_tilde_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    type = coalesce_reversed_filename_list_1(type_list);
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	if (name)
	    type = coalesce_reversed_filename_list_1(type_list);
	else
	    name = coalesce_reversed_filename_list_1(nconc2(type_list,
		    path_cons_1(string_constant,Nil)));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_dot_gt)) {
	type_list = nconc2(type_list,name ? path_list_2(string_constant,
		name) : path_cons_1(string_constant,Nil));
	type = coalesce_reversed_filename_list_1(type_list);
	type_list = Nil;
	if (name)
	    reclaim_text_string(name);
	name = type;
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)1L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	type_list = path_cons_1(lt_anything_gt,type_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)1L);
	goto parser_traverse;
    }
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-UNIX-FILENAME-NODE-111 */
Object parse_unix_filename_node_111(parser_info,host,device,directory_1,
	    name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, name_type_version_list, name_list;
    Object type_list;
{
    Object next_node;

    x_note_fn_call(40,28);
    next_node = Nil;
    reclaim_path_list_1(name_type_version_list);
    next_node = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)12L);
    goto parser_traverse;
    error_in_unix_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_12(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    name_type_version_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

/* PARSE-UNIX-FILENAME */
Object parse_unix_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(40,29);
    if (PUSH_CATCH(Qcatcher_for_filename_parse_error,0)) {
	parser_info = make_filename_parser_information_1();
	svref_new_value = tokenize_filename(3,filename,list_constant_1,
		Kcase_sensitive);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = copy_list_using_path_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = ISVREF(Nodes_for_unix_filename_parser,(SI_Long)11L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = parse_unix_filename_node_100(parser_info,Nil,Nil,Nil,Nil,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Vms_directory_filenames_can_dangle_p, Qvms_directory_filenames_can_dangle_p);

/* RECLAIM-NASCENT-VMS-DIRECTORY */
Object reclaim_nascent_vms_directory(directory_list,directory_item_qm)
    Object directory_list, directory_item_qm;
{
    Object component, ab_loop_list_;

    x_note_fn_call(40,30);
    component = Nil;
    ab_loop_list_ = directory_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(component))
	reclaim_path_list_1(component);
    goto next_loop;
  end_loop:
    reclaim_path_list_1(directory_list);
    reclaim_path_list_1(directory_item_qm);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Nodes_for_vms_filename_parser, Qnodes_for_vms_filename_parser);

/* ERROR-IN-VMS-FILENAME-PARSER */
Object error_in_vms_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(40,31);
    reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qcatcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qvms;                /* vms */

/* FINAL-VMS-PARSER-NODE */
Object final_vms_parser_node(parser_info,host,device,directory_1,name,type,
	    version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(40,32);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = make_gensym_pathname_structure_function(host,
		device,directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qvms;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvms),
		Qfilename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvms),
		Qnamestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-VMS-FILENAME-NODE-101 */
Object parse_vms_filename_node_101(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,33);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt) && 
		EQ(match_2,Lt_colon_gt)) {
	    lt_word_gt = match_0;
	    host = copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)12L);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_double_quote_gt) && 
		text_string_p(match_2) && EQ(match_3,Lt_double_quote_gt) 
		&& EQ(match_4,Lt_colon_gt) && EQ(match_5,Lt_colon_gt)) {
	    lt_word_gt_0 = match_0;
	    lt_word_gt_1 = match_2;
	    host = coalesce_filename_items_1(path_list_4(lt_word_gt_0,
		    Lt_double_quote_gt,lt_word_gt_1,Lt_double_quote_gt));
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)6L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)12L);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_double_quote_gt) && 
		text_string_p(match_2) && EQ(match_3,Lt_space_gt) && 
		text_string_p(match_4) && EQ(match_5,Lt_double_quote_gt) 
		&& EQ(match_6,Lt_colon_gt) && EQ(match_7,Lt_colon_gt)) {
	    lt_word_gt_0 = match_0;
	    lt_word_gt_1 = match_2;
	    lt_word_gt_2 = match_4;
	    gensymed_symbol = make_path_list_1(FIX((SI_Long)6L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = lt_word_gt_0;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = Lt_double_quote_gt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = lt_word_gt_1;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = Lt_space_gt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = lt_word_gt_2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = Lt_double_quote_gt;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    host = coalesce_filename_items_1(gensymed_symbol);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)8L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)12L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)12L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-102 */
Object parse_vms_filename_node_102(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,34);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt)) {
	    lt_word_gt = match_0;
	    device = copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)11L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)11L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
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
Object parse_vms_filename_node_103(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,35);
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
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,Lt_dot_gt) && 
		EQ(match_2,Lt_dot_gt) && EQ(match_3,Lt_dot_gt) && 
		EQ(match_4,Lt_right_bracket_gt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = path_list_2(Krelative,Kwild_inferiors);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)5L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,
		    Lt_right_bracket_gt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = path_cons_1(Krelative,Nil);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,Lt_left_bracket_gt) && string_eq_w(array_constant_1,
		match_1) && EQ(match_2,Lt_right_bracket_gt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = path_cons_1(Kabsolute,Nil);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_5 = nth(match_pointer,filename_sequence);
    if (match_5) {
	if (EQ(match_0,Lt_left_bracket_gt) && string_eq_w(array_constant_1,
		match_1) && EQ(match_2,Lt_dot_gt) && EQ(match_3,Lt_dot_gt) 
		&& EQ(match_4,Lt_dot_gt) && EQ(match_5,Lt_right_bracket_gt)) {
	    dual_directory_impossible_p = T;
	    directory_1 = path_list_2(Kabsolute,Kwild_inferiors);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)6L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,Lt_left_bracket_gt) && string_eq_w(array_constant_1,
		match_1) && EQ(match_2,Lt_dot_gt)) {
	    directory_list = path_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,Lt_hyphen_gt) && 
		EQ(match_2,Lt_dot_gt)) {
	    directory_list = path_cons_1(Krelative,directory_list);
	    dual_directory_impossible_p = T;
	    directory_list = path_cons_1(Kup,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,Lt_dot_gt) && 
		EQ(match_2,Lt_right_bracket_gt)) {
	    error_in_filename_parse_1(string_constant_1,parser_info);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,Lt_dot_gt)) {
	    directory_list = path_cons_1(Krelative,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_left_bracket_gt) && EQ(match_1,
		Lt_end_of_sequence_gt)) {
	    if (Vms_directory_filenames_can_dangle_p)
		directory_1 = path_cons_1(Krelative,Nil);
	    else {
		reclaim_pathname_components(2,host,device);
		error_in_filename_parse_1(string_constant_2,parser_info);
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_left_bracket_gt)) {
	directory_list = path_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
	goto parser_traverse;
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
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
Object parse_vms_filename_node_104(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,36);
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
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_dot_gt) && EQ(match_2,
		Lt_dot_gt) && EQ(match_3,Lt_right_bracket_gt)) {
	    directory_list = path_cons_1(Kwild_inferiors,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (match_3) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_right_bracket_gt) && 
		EQ(match_2,Lt_left_bracket_gt) && EQ(match_3,Lt_hyphen_gt)) {
	    reclaim_pathname_components(2,host,device);
	    reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	    error_in_filename_parse_1(string_constant_3,parser_info);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)4L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_right_bracket_gt) && 
		EQ(match_2,Lt_left_bracket_gt)) {
	    if (dual_directory_impossible_p) {
		reclaim_pathname_components(2,host,device);
		reclaim_nascent_vms_directory(directory_list,
			directory_item_qm);
		error_in_filename_parse_1(string_constant_4,parser_info);
	    }
	    else if (doing_dual_directory_p) {
		reclaim_pathname_components(2,host,device);
		reclaim_nascent_vms_directory(directory_list,
			directory_item_qm);
		error_in_filename_parse_1(string_constant_5,parser_info);
	    }
	    else {
		directory_item_qm = nreverse(directory_item_qm);
		doing_dual_directory_p = T;
		change_filename_sequence_to_1(directory_item_qm,
			parser_info,FIX((SI_Long)3L));
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)9L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_right_bracket_gt)) {
	final_directory_item_p = T;
	directory_item_qm = nreverse(directory_item_qm);
	if ( !TRUEP(directory_item_qm) && doing_dual_directory_p) {
	    reclaim_pathname_components(2,host,device);
	    reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	    error_in_filename_parse_1(string_constant_6,parser_info);
	}
	else
	    change_filename_sequence_to_1(directory_item_qm,parser_info,
		    FIX((SI_Long)1L));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)9L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_dot_gt)) {
	directory_item_qm = nreverse(directory_item_qm);
	change_filename_sequence_to_1(directory_item_qm,parser_info,
		FIX((SI_Long)1L));
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)9L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_left_bracket_gt)) {
	reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_colon_gt)) {
	reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	if (Vms_directory_filenames_can_dangle_p) {
	    if (directory_item_qm) {
		directory_item_qm = nreverse(directory_item_qm);
		directory_list = 
			path_cons_1(copy_list_using_path_conses_1(directory_item_qm),
			directory_list);
		reclaim_path_list_1(directory_item_qm);
	    }
	    directory_1 = coalesce_filename_sublists_1(directory_list);
	}
	else {
	    reclaim_nascent_vms_directory(directory_list,directory_item_qm);
	    error_in_filename_parse_1(string_constant_7,parser_info);
	}
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	directory_item_qm = path_cons_1(lt_anything_gt,directory_item_qm);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
	goto parser_traverse;
    }
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-105 */
Object parse_vms_filename_node_105(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,37);
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
	if (EQ(match_0,Lt_hyphen_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    if ( !TRUEP(doing_dual_directory_p))
		dual_directory_impossible_p = T;
	    directory_list = path_cons_1(Kup,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Kwild,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)8L);
	    goto parser_traverse;
	}
    }
    if (directory_item_qm)
	directory_list = 
		path_cons_1(copy_list_using_path_conses_1(directory_item_qm),
		directory_list);
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-106 */
Object parse_vms_filename_node_106(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(40,38);
    next_node = Nil;
    reclaim_path_list_1(directory_item_qm);
    directory_item_qm = Nil;
    resume_previous_filename_sequence_1(parser_info);
    if (final_directory_item_p)
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)7L);
    else
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)10L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-107 */
Object parse_vms_filename_node_107(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(40,39);
    next_node = Nil;
    directory_1 = coalesce_filename_sublists_1(directory_list);
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)6L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-108 */
Object parse_vms_filename_node_108(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,40);
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
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_dot_gt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)4L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)5L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-109 */
Object parse_vms_filename_node_109(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(40,41);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_dot_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)4L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_semicolon_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_left_bracket_gt)) {
	reclaim_path_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_right_bracket_gt)) {
	reclaim_path_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_colon_gt)) {
	reclaim_path_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	name_list = path_cons_1(lt_anything_gt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)5L);
	goto parser_traverse;
    }
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-110 */
Object parse_vms_filename_node_110(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,42);
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
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_dot_gt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)2L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_semicolon_gt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)2L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)3L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

/* PARSE-VMS-FILENAME-NODE-111 */
Object parse_vms_filename_node_111(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(40,43);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_dot_gt)) {
	type = coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_semicolon_gt)) {
	type = coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)2L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	type = coalesce_reversed_filename_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_left_bracket_gt)) {
	reclaim_path_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_right_bracket_gt)) {
	reclaim_path_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_colon_gt)) {
	reclaim_path_list_1(type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)0L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	type_list = path_cons_1(lt_anything_gt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)3L);
	goto parser_traverse;
    }
    error_in_vms_filename_parser(parser_info);
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
Object parse_vms_filename_node_112(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,44);
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
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    version = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_hyphen_gt) && string_eq_w(array_constant_2,
		match_1) && EQ(match_2,Lt_end_of_sequence_gt)) {
	    version = Kprevious;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (string_eq_w(array_constant_3,match_0) && EQ(match_1,
		Lt_end_of_sequence_gt)) {
	    version = Knewest;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	version = Knewest;
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	goto parser_traverse;
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)1L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object string_constant_8;   /* "non-numeric version" */

/* PARSE-VMS-FILENAME-NODE-113 */
Object parse_vms_filename_node_113(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
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

    x_note_fn_call(40,45);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    lt_word_gt = match_0;
	    version = read_positive_fixnum_from_string(lt_word_gt,
		    FIX((SI_Long)0L),text_string_length(lt_word_gt));
	    if ( !TRUEP(version)) {
		if (Accept_any_version_component_p)
		    version = 
			    coalesce_remainder_of_filename_sequence_1(parser_info);
		else {
		    reclaim_pathname_components(5,host,device,directory_1,
			    name,type);
		    error_in_filename_parse_1(string_constant_8,parser_info);
		}
	    }
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_hyphen_gt) && text_string_p(match_1) && 
		EQ(match_2,Lt_end_of_sequence_gt)) {
	    lt_word_gt = match_1;
	    version = read_positive_fixnum_from_string(lt_word_gt,
		    FIX((SI_Long)0L),text_string_length(lt_word_gt));
	    if ( !TRUEP(version)) {
		if (Accept_any_version_component_p)
		    version = 
			    coalesce_remainder_of_filename_sequence_1(parser_info);
		else {
		    reclaim_pathname_components(5,host,device,directory_1,
			    name,type);
		    error_in_filename_parse_1(string_constant_8,parser_info);
		}
	    }
	    else
		version = negate(version);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
	    goto parser_traverse;
	}
    }
    if (Accept_any_version_component_p)
	version = coalesce_remainder_of_filename_sequence_1(parser_info);
    else {
	reclaim_pathname_components(5,host,device,directory_1,name,type);
	error_in_filename_parse_1(string_constant_8,parser_info);
    }
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object string_constant_9;   /* "bad constituent char" */

/* PARSE-VMS-FILENAME-NODE-114 */
Object parse_vms_filename_node_114(parser_info,host,device,directory_1,
	    name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_list, directory_item_qm, final_directory_item_p;
    Object name_list, type_list, dual_directory_impossible_p;
    Object doing_dual_directory_p;
{
    Object next_node;

    x_note_fn_call(40,46);
    next_node = Nil;
    reclaim_pathname_components(4,host,device,directory_1,name);
    error_in_filename_parse_1(string_constant_9,parser_info);
    next_node = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)15L);
    goto parser_traverse;
    error_in_vms_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_14(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_list,directory_item_qm,
	    final_directory_item_p,name_list,type_list,
	    dual_directory_impossible_p,doing_dual_directory_p));
    return VALUES_1(Qnil);
}

static Object list_constant_2;     /* # */

/* PARSE-VMS-FILENAME */
Object parse_vms_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(40,47);
    if (PUSH_CATCH(Qcatcher_for_filename_parse_error,0)) {
	parser_info = make_filename_parser_information_1();
	svref_new_value = tokenize_filename(3,filename,list_constant_2,
		Kall_uppercase);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = copy_list_using_path_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = ISVREF(Nodes_for_vms_filename_parser,(SI_Long)14L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = parse_vms_filename_node_101(parser_info,Nil,Nil,Nil,Nil,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Limit_dos_filename_component_lengths_p, Qlimit_dos_filename_component_lengths_p);

DEFINE_VARIABLE_WITH_SYMBOL(Allow_extensionless_dos_filenames_p, Qallow_extensionless_dos_filenames_p);

DEFINE_VARIABLE_WITH_SYMBOL(Character_case_mode_for_generalized_dos, Qcharacter_case_mode_for_generalized_dos);

DEFINE_VARIABLE_WITH_SYMBOL(Nodes_for_generalized_dos_filename_parser, Qnodes_for_generalized_dos_filename_parser);

/* ERROR-IN-GENERALIZED-DOS-FILENAME-PARSER */
Object error_in_generalized_dos_filename_parser(parser_info)
    Object parser_info;
{
    Object result;

    x_note_fn_call(40,48);
    reclaim_filename_parser_information(parser_info);
    result = VALUES_1(Nil);
    THROW(Qcatcher_for_filename_parse_error,result);
    return VALUES_1(Qnil);
}

static Object Qgeneralized_dos;    /* generalized-dos */

/* FINAL-GENERALIZED-DOS-PARSER-NODE */
Object final_generalized_dos_parser_node(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object temp, result_pathname, svref_new_value;

    x_note_fn_call(40,49);
    if (ISVREF(parser_info,(SI_Long)5L))
	temp = Nil;
    else {
	result_pathname = make_gensym_pathname_structure_function(host,
		device,directory_1,name,type,version);
	SVREF(result_pathname,FIX((SI_Long)8L)) = Qgeneralized_dos;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgeneralized_dos),
		Qfilename_parser_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgeneralized_dos),
		Qnamestring_generator_of_file_system);
	SVREF(result_pathname,FIX((SI_Long)10L)) = svref_new_value;
	temp = result_pathname;
    }
    reclaim_filename_parser_information(parser_info);
    return VALUES_1(temp);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-100 */
Object parse_generalized_dos_filename_node_100(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, lt_word_gt;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(40,50);
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
	if (EQ(match_0,Lt_backslash_gt) && EQ(match_1,Lt_backslash_gt) && 
		text_string_p(match_2)) {
	    lt_word_gt = match_2;
	    host = copy_text_string(lt_word_gt);
	    version = Kunspecific;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)8L);
	    goto parser_traverse;
	}
    }
    host = Kunspecific;
    version = Kunspecific;
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)8L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_10;  /* "device must only have one letter" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-101 */
Object parse_generalized_dos_filename_node_101(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, lt_word_gt;
    Object svref_new_value_1;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(40,51);
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
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt) && 
		EQ(match_2,Lt_end_of_sequence_gt)) {
	    lt_word_gt = match_0;
	    if (Limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(text_string_length(lt_word_gt)) == (SI_Long)1L))
		    error_in_filename_parse_1(string_constant_10,parser_info);
	    }
	    device = copy_text_string(lt_word_gt);
	    directory_1 = path_cons_1(Krelative,directory_1);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_2) {
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt) && 
		EQ(match_2,Lt_backslash_gt)) {
	    lt_word_gt = match_0;
	    if (Limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(text_string_length(lt_word_gt)) == (SI_Long)1L))
		    error_in_filename_parse_1(string_constant_10,parser_info);
	    }
	    device = copy_text_string(lt_word_gt);
	    directory_list = path_cons_1(Kabsolute,directory_list);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (text_string_p(match_0) && EQ(match_1,Lt_colon_gt)) {
	    lt_word_gt = match_0;
	    if (Limit_dos_filename_component_lengths_p) {
		if ( !(IFIX(text_string_length(lt_word_gt)) == (SI_Long)1L))
		    error_in_filename_parse_1(string_constant_10,parser_info);
	    }
	    device = copy_text_string(lt_word_gt);
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)7L);
	    goto parser_traverse;
	}
    }
    if (EQ(current_token,Lt_backslash_gt)) {
	directory_list = path_cons_1(Kabsolute,directory_list);
	svref_new_value_1 = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value_1;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)7L);
	goto parser_traverse;
    }
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)7L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_11;  /* "no wildcards allowed in directory" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-102 */
Object parse_generalized_dos_filename_node_102(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, svref_new_value, lt_anything_gt;

    x_note_fn_call(40,52);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_backslash_gt)) {
	if (wildcard_encountered_p) {
	    if (directory_item)
		reclaim_path_list_1(directory_item);
	    if (directory_list)
		reclaim_path_tree_1(directory_list);
	    error_in_filename_parse_1(string_constant_11,parser_info);
	}
	directory_item = nreverse(directory_item);
	change_filename_sequence_to_1(directory_item,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)6L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	directory_1 = coalesce_filename_sublists_1(directory_list);
	if (directory_1) {
	    if ( !TRUEP(memq_function(CAR(directory_1),list_constant)))
		directory_1 = path_cons_1(Krelative,directory_1);
	}
	name_and_type_list = nreverse(directory_item);
	change_filename_sequence_to_1(name_and_type_list,parser_info,
		FIX((SI_Long)1L));
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)4L);
	goto parser_traverse;
    }
    lt_anything_gt = current_token;
    if ( !EQ(Qlt_end_of_sequence_gt,lt_anything_gt)) {
	directory_item = path_cons_1(lt_anything_gt,directory_item);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)7L);
	goto parser_traverse;
    }
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-103 */
Object parse_generalized_dos_filename_node_103(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, svref_new_value;
    SI_Long svref_new_value_1;

    x_note_fn_call(40,53);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)5L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Krelative,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_dot_gt) && EQ(match_2,
		Lt_end_of_sequence_gt)) {
	    directory_list = path_cons_1(Kup,directory_list);
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    wildcard_encountered_p = T;
	    svref_new_value_1 = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value_1);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)5L);
	    goto parser_traverse;
	}
    }
    directory_list = 
	    path_cons_1(copy_list_using_path_conses_1(directory_item),
	    directory_list);
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)5L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-104 */
Object parse_generalized_dos_filename_node_104(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node;

    x_note_fn_call(40,54);
    next_node = Nil;
    reclaim_path_list_1(directory_item);
    directory_item = Nil;
    resume_previous_filename_sequence_1(parser_info);
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)7L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-105 */
Object parse_generalized_dos_filename_node_105(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1, match_2, temp;
    Object new_directory_component;
    SI_Long svref_new_value;

    x_note_fn_call(40,55);
    next_node = Nil;
    filename_sequence = ISVREF(parser_info,(SI_Long)2L);
    sequence_length = ISVREF(parser_info,(SI_Long)3L);
    match_pointer = ISVREF(parser_info,(SI_Long)7L);
    current_token = nth(match_pointer,filename_sequence);
    match_0 = current_token;
    match_1 = Nil;
    match_2 = Nil;
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	temp = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = temp;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_1 = nth(match_pointer,filename_sequence);
    if (match_1) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    new_directory_component = path_cons_1(Krelative,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    match_pointer = FIXNUM_ADD1(match_pointer);
    if (FIXNUM_LT(match_pointer,sequence_length))
	match_2 = nth(match_pointer,filename_sequence);
    if (match_2) {
	if (EQ(match_0,Lt_dot_gt) && EQ(match_1,Lt_dot_gt) && EQ(match_2,
		Lt_end_of_sequence_gt)) {
	    new_directory_component = path_cons_1(Kup,Nil);
	    if (directory_1) {
		temp = last(directory_1,_);
		M_CDR(temp) = new_directory_component;
	    }
	    else
		directory_1 = new_directory_component;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)3L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    if (match_1) {
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_dot_gt)) {
	    name = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)2L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)3L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_12;  /* "file type required" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-106 */
Object parse_generalized_dos_filename_node_106(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, svref_new_value, lt_word_gt;

    x_note_fn_call(40,56);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	if (Allow_extensionless_dos_filenames_p)
	    name = coalesce_reversed_filename_list_1(name_list);
	else {
	    if (name_list)
		reclaim_gensym_tree_1(name_list);
	    error_in_filename_parse_1(string_constant_12,parser_info);
	}
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_dot_gt)) {
	name = coalesce_reversed_filename_list_1(name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)2L);
	goto parser_traverse;
    }
    lt_word_gt = current_token;
    if (text_string_p(lt_word_gt)) {
	name_list = path_cons_1(lt_word_gt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)3L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_asterisk_gt)) {
	name_list = path_cons_1(Lt_asterisk_gt,name_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)3L);
	goto parser_traverse;
    }
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-108 */
Object parse_generalized_dos_filename_node_108(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, filename_sequence, sequence_length, match_pointer;
    Object current_token, match_0, match_1;
    SI_Long svref_new_value;

    x_note_fn_call(40,57);
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
	if (EQ(match_0,Lt_asterisk_gt) && EQ(match_1,Lt_end_of_sequence_gt)) {
	    type = Kwild;
	    svref_new_value = IFIX(ISVREF(parser_info,(SI_Long)7L)) + 
		    (SI_Long)2L;
	    ISVREF(parser_info,(SI_Long)7L) = FIX(svref_new_value);
	    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		    (SI_Long)0L);
	    goto parser_traverse;
	}
    }
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)1L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-110 */
Object parse_generalized_dos_filename_node_110(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, current_token, temp, svref_new_value, lt_word_gt;

    x_note_fn_call(40,58);
    next_node = Nil;
    current_token = nth(ISVREF(parser_info,(SI_Long)7L),ISVREF(parser_info,
	    (SI_Long)2L));
    if (EQ(current_token,Lt_end_of_sequence_gt)) {
	type = coalesce_reversed_filename_list_1(type_list);
	if (Limit_dos_filename_component_lengths_p && 
		IFIX(text_string_length(type)) > (SI_Long)3L) {
	    temp = text_string_substring(type,FIX((SI_Long)0L),
		    FIX((SI_Long)3L));
	    reclaim_text_string(type);
	    type = temp;
	}
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)0L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_dot_gt)) {
	type_list = nconc2(type_list,name ? path_list_2(string_constant,
		name) : path_cons_1(string_constant,Nil));
	type = coalesce_reversed_filename_list_1(type_list);
	type_list = Nil;
	if (name)
	    reclaim_text_string(name);
	name = type;
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    lt_word_gt = current_token;
    if (text_string_p(lt_word_gt)) {
	type_list = path_cons_1(lt_word_gt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    if (EQ(current_token,Lt_asterisk_gt)) {
	type_list = path_cons_1(Lt_asterisk_gt,type_list);
	svref_new_value = FIXNUM_ADD1(ISVREF(parser_info,(SI_Long)7L));
	SVREF(parser_info,FIX((SI_Long)7L)) = svref_new_value;
	next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)1L);
	goto parser_traverse;
    }
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "over 63 characters in filename" */

/* PARSE-GENERALIZED-DOS-FILENAME-NODE-111 */
Object parse_generalized_dos_filename_node_111(parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list)
    Object parser_info, host, device, directory_1, name, type, version;
    Object directory_item, directory_list, wildcard_encountered_p;
    Object name_and_type_list, name_list, type_list;
{
    Object next_node, directory_element, ab_loop_list_, incff_1_arg, element;
    SI_Long count_of_characters_in_filename;

    x_note_fn_call(40,59);
    next_node = Nil;
    reclaim_path_list_1(name_and_type_list);
    if (Limit_dos_filename_component_lengths_p) {
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
	    incff_1_arg = FIXNUM_ADD1(text_string_length(directory_element));
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	goto next_loop;
      end_loop:;
	if (text_string_p(name)) {
	    incff_1_arg = text_string_length(name);
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	else
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (name)
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (text_string_p(type)) {
	    incff_1_arg = text_string_length(type);
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + IFIX(incff_1_arg);
	}
	else
	    count_of_characters_in_filename = 
		    count_of_characters_in_filename + (SI_Long)1L;
	if (count_of_characters_in_filename > (SI_Long)63L) {
	    if (text_string_p(device))
		reclaim_text_string(device);
	    if (directory_1) {
		element = Nil;
		ab_loop_list_ = directory_1;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (text_string_p(element))
		    reclaim_text_string(element);
		goto next_loop_1;
	      end_loop_1:
		reclaim_path_list_1(directory_1);
	    }
	    if (text_string_p(name))
		reclaim_text_string(name);
	    if (text_string_p(type))
		reclaim_text_string(type);
	    error_in_filename_parse_1(string_constant_13,parser_info);
	}
    }
    next_node = ISVREF(Nodes_for_generalized_dos_filename_parser,(SI_Long)11L);
    goto parser_traverse;
    error_in_generalized_dos_filename_parser(parser_info);
  parser_traverse:
    return VALUES_1(inline_funcall_13(next_node,parser_info,host,device,
	    directory_1,name,type,version,directory_item,directory_list,
	    wildcard_encountered_p,name_and_type_list,name_list,type_list));
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* PARSE-GENERALIZED-DOS-FILENAME */
Object parse_generalized_dos_filename(filename)
    Object filename;
{
    Object parser_info, svref_new_value;
    Declare_catch(1);
    Object result;

    x_note_fn_call(40,60);
    if (PUSH_CATCH(Qcatcher_for_filename_parse_error,0)) {
	parser_info = make_filename_parser_information_1();
	svref_new_value = tokenize_filename(3,filename,list_constant_3,
		Character_case_mode_for_generalized_dos);
	SVREF(parser_info,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = copy_list_using_path_conses_1(ISVREF(parser_info,
		(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = length(ISVREF(parser_info,(SI_Long)1L));
	SVREF(parser_info,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(parser_info,FIX((SI_Long)4L)) = Nil;
	SVREF(parser_info,FIX((SI_Long)5L)) = Nil;
	ISVREF(parser_info,(SI_Long)7L) = FIX((SI_Long)0L);
	SVREF(parser_info,FIX((SI_Long)8L)) = Nil;
	svref_new_value = ISVREF(Nodes_for_generalized_dos_filename_parser,
		(SI_Long)10L);
	SVREF(parser_info,FIX((SI_Long)6L)) = svref_new_value;
	result = parse_generalized_dos_filename_node_100(parser_info,Nil,
		Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qdos;                /* dos */

static Object Qparse_dos_filename;  /* parse-dos-filename */

static Object Qgenerate_dos_namestring;  /* generate-dos-namestring */

/* PARSE-DOS-FILENAME */
Object parse_dos_filename(filename)
    Object filename;
{
    Object limit_dos_filename_component_lengths_p;
    Object allow_extensionless_dos_filenames_p;
    Object character_case_mode_for_generalized_dos, result_pathname_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(40,61);
    limit_dos_filename_component_lengths_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Limit_dos_filename_component_lengths_p,Qlimit_dos_filename_component_lengths_p,limit_dos_filename_component_lengths_p,
	    2);
      allow_extensionless_dos_filenames_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(Allow_extensionless_dos_filenames_p,Qallow_extensionless_dos_filenames_p,allow_extensionless_dos_filenames_p,
	      1);
	character_case_mode_for_generalized_dos = Kall_uppercase;
	PUSH_SPECIAL_WITH_SYMBOL(Character_case_mode_for_generalized_dos,Qcharacter_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
		0);
	  result_pathname_qm = parse_generalized_dos_filename(filename);
	  if (result_pathname_qm) {
	      SVREF(result_pathname_qm,FIX((SI_Long)8L)) = Qdos;
	      SVREF(result_pathname_qm,FIX((SI_Long)9L)) = Qparse_dos_filename;
	      SVREF(result_pathname_qm,FIX((SI_Long)10L)) = 
		      Qgenerate_dos_namestring;
	  }
	  result = VALUES_1(result_pathname_qm);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qwin32;              /* win32 */

static Object Qparse_win32_filename;  /* parse-win32-filename */

static Object Qgenerate_win32_namestring;  /* generate-win32-namestring */

/* PARSE-WIN32-FILENAME */
Object parse_win32_filename(filename)
    Object filename;
{
    Object limit_dos_filename_component_lengths_p;
    Object allow_extensionless_dos_filenames_p;
    Object character_case_mode_for_generalized_dos, result_pathname_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(40,62);
    limit_dos_filename_component_lengths_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Limit_dos_filename_component_lengths_p,Qlimit_dos_filename_component_lengths_p,limit_dos_filename_component_lengths_p,
	    2);
      allow_extensionless_dos_filenames_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(Allow_extensionless_dos_filenames_p,Qallow_extensionless_dos_filenames_p,allow_extensionless_dos_filenames_p,
	      1);
	character_case_mode_for_generalized_dos = Kcase_sensitive;
	PUSH_SPECIAL_WITH_SYMBOL(Character_case_mode_for_generalized_dos,Qcharacter_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
		0);
	  result_pathname_qm = parse_generalized_dos_filename(filename);
	  if (result_pathname_qm) {
	      SVREF(result_pathname_qm,FIX((SI_Long)8L)) = Qwin32;
	      SVREF(result_pathname_qm,FIX((SI_Long)9L)) = 
		      Qparse_win32_filename;
	      SVREF(result_pathname_qm,FIX((SI_Long)10L)) = 
		      Qgenerate_win32_namestring;
	  }
	  result = VALUES_1(result_pathname_qm);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_deletable_token_in_namestring, Qlast_deletable_token_in_namestring);

/* WRITE-KNOWN-SPECIAL-CHARACTER-FOR-NAMESTRING */
Object write_known_special_character_for_namestring(special_character_description)
    Object special_character_description;
{
    Object special_character_entry, simple_or_wide_character, thing, temp;
    Object schar_arg_2, schar_new_value;

    x_note_fn_call(40,63);
    special_character_entry = assoc_eql(special_character_description,
	    Filename_special_character_registry);
    if (special_character_entry) {
	simple_or_wide_character = CDR(special_character_entry);
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
    else
	return VALUES_1(Nil);
}

static Object Qex_delete_ex;       /* !delete! */

static Object Qex_deletable_ex;    /* !deletable! */

/* WRITE-SPECIAL-CHARACTER-FOR-NAMESTRING */
Object write_special_character_for_namestring(special_character_description)
    Object special_character_description;
{
    x_note_fn_call(40,64);
    if (EQ(special_character_description,Qex_delete_ex)) {
	Last_deletable_token_in_namestring = Nil;
	return VALUES_1(Last_deletable_token_in_namestring);
    }
    else {
	if (Last_deletable_token_in_namestring) {
	    write_known_special_character_for_namestring(Last_deletable_token_in_namestring);
	    Last_deletable_token_in_namestring = Nil;
	}
	if (text_string_p(special_character_description))
	    return twrite_general_string(special_character_description);
	else if (CONSP(special_character_description) && 
		EQ(FIRST(special_character_description),Qex_deletable_ex)) {
	    Last_deletable_token_in_namestring = 
		    SECOND(special_character_description);
	    return VALUES_1(Last_deletable_token_in_namestring);
	}
	else
	    return write_known_special_character_for_namestring(special_character_description);
    }
}

/* WRITE-SPECIAL-CHARACTERS-FOR-NAMESTRING */
Object write_special_characters_for_namestring(special_character_description)
    Object special_character_description;
{
    Object special_character_subdescription, ab_loop_list_;

    x_note_fn_call(40,65);
    if (text_string_p(special_character_description)) {
	if (Last_deletable_token_in_namestring) {
	    write_known_special_character_for_namestring(Last_deletable_token_in_namestring);
	    Last_deletable_token_in_namestring = Nil;
	}
	return twrite_general_string(special_character_description);
    }
    else if (CONSP(special_character_description) && 
	    EQ(FIRST(special_character_description),Qex_deletable_ex)) {
	Last_deletable_token_in_namestring = 
		SECOND(special_character_description);
	return VALUES_1(Last_deletable_token_in_namestring);
    }
    else if (CONSP(special_character_description)) {
	special_character_subdescription = Nil;
	ab_loop_list_ = special_character_description;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	special_character_subdescription = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_special_character_for_namestring(special_character_subdescription);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return write_special_character_for_namestring(special_character_description);
}

static Object Kcomponent;          /* :component */

/* WRITE-MONOLITHIC-COMPONENT-FOR-NAMESTRING */
Object write_monolithic_component_for_namestring(component,
	    component_template,special_symbol_plist,convert_to_uppercase_p)
    Object component, component_template, special_symbol_plist;
    Object convert_to_uppercase_p;
{
    Object template_item, ab_loop_list_, special_symbol_entry;
    Object uppercase_component;

    x_note_fn_call(40,66);
    if ( !TRUEP(component) || EQ(Kunspecific,component)) {
	if (Last_deletable_token_in_namestring) {
	    write_known_special_character_for_namestring(Last_deletable_token_in_namestring);
	    Last_deletable_token_in_namestring = Nil;
	    return VALUES_1(Last_deletable_token_in_namestring);
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
		write_special_characters_for_namestring(special_symbol_entry);
	    else if (text_string_p(component) && convert_to_uppercase_p) {
		uppercase_component = 
			nstring_upcasew(copy_text_string(component));
		twrite(uppercase_component);
		reclaim_text_string(uppercase_component);
	    }
	    else {
		if (Last_deletable_token_in_namestring) {
		    write_known_special_character_for_namestring(Last_deletable_token_in_namestring);
		    Last_deletable_token_in_namestring = Nil;
		}
		twrite(component);
	    }
	}
	else
	    write_special_character_for_namestring(template_item);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Kleading_items;      /* :leading-items */

static Object Klast_item;          /* :last-item */

static Object Kcompound;           /* :compound */

/* WRITE-COMPOUND-COMPONENT-FOR-NAMESTRING */
Object write_compound_component_for_namestring(component,
	    component_template,sequence_template,heterogeneous_sequence_p,
	    special_symbol_plist,prologue_qm,convert_to_uppercase_p)
    Object component, component_template, sequence_template;
    Object heterogeneous_sequence_p, special_symbol_plist, prologue_qm;
    Object convert_to_uppercase_p;
{
    Object inner_component_template, last_component_template, sequence_item;
    Object ab_loop_list_, component_item, ab_loop_list__1, component_cons;
    Object last_component_template_qm, ab_loop_iter_flag_, temp, temp_1;

    x_note_fn_call(40,67);
    if ( !TRUEP(component) &&  !TRUEP(prologue_qm)) {
	if (Last_deletable_token_in_namestring) {
	    write_known_special_character_for_namestring(Last_deletable_token_in_namestring);
	    Last_deletable_token_in_namestring = Nil;
	    return VALUES_1(Last_deletable_token_in_namestring);
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
		write_special_characters_for_namestring(prologue_qm);
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
		write_monolithic_component_for_namestring(temp,temp_1,
			special_symbol_plist,convert_to_uppercase_p);
	    }
	    else
		write_monolithic_component_for_namestring(component_item,
			component_template,special_symbol_plist,
			convert_to_uppercase_p);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else
	    write_special_character_for_namestring(sequence_item);
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
Object generate_unix_namestring(pathname_1)
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

    x_note_fn_call(40,68);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
    gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
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
	      write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_4,Qnil,Nil);
	      write_compound_component_for_namestring(gensym_pathname_directory,
		      list_constant_5,list_constant_6,Nil,list_constant_7,
		      Nil,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_version,
		      list_constant_8,list_constant_11,Nil);
	      result = copy_out_current_wide_string();
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
Object generate_vms_namestring(pathname_1)
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

    x_note_fn_call(40,69);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
    gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
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
	      write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_12,Qnil,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_device,
		      list_constant_4,Qnil,Nil);
	      directory_length = length(gensym_pathname_directory);
	      match_1 = (SI_Long)0L < IFIX(directory_length) ? 
		      FIRST(gensym_pathname_directory) : Nil;
	      match_2 = (SI_Long)1L < IFIX(directory_length) ? 
		      SECOND(gensym_pathname_directory) : Nil;
	      if (IFIX(directory_length) >= (SI_Long)2L && EQ(Krelative,
		      match_1) && EQ(Kup,match_2))
		  write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  list_constant_16,Nil);
	      else if (IFIX(directory_length) == (SI_Long)1L && 
		      EQ(Kabsolute,match_1))
		  write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  array_constant_1,Nil);
	      else if (IFIX(directory_length) >= (SI_Long)2L && 
		      EQ(Kabsolute,match_1) && EQ(Kwild_inferiors,match_2))
		  write_compound_component_for_namestring(nthcdr(FIX((SI_Long)2L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  list_constant_17,Nil);
	      else if (IFIX(directory_length) >= (SI_Long)1L && 
		      EQ(Kabsolute,match_1))
		  write_compound_component_for_namestring(nthcdr(FIX((SI_Long)1L),
			  gensym_pathname_directory),list_constant_13,
			  list_constant_14,T,list_constant_15,
			  array_constant_4,Nil);
	      else
		  write_compound_component_for_namestring(gensym_pathname_directory,
			  list_constant_13,list_constant_14,T,
			  list_constant_15,Nil,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_version,
		      list_constant_18,list_constant_19,Nil);
	      result = copy_out_current_wide_string();
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
Object generate_generalized_dos_namestring(pathname_1)
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

    x_note_fn_call(40,70);
    gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
    gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
    gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
    gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
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
	      write_monolithic_component_for_namestring(gensym_pathname_host,
		      list_constant_20,Qnil,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_device,
		      list_constant_4,Qnil,Nil);
	      write_compound_component_for_namestring(gensym_pathname_directory,
		      list_constant_21,list_constant_6,Nil,
		      list_constant_22,Nil,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_name,
		      list_constant_8,list_constant_9,Nil);
	      write_monolithic_component_for_namestring(gensym_pathname_type,
		      list_constant_10,list_constant_9,Nil);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GENERATE-DOS-NAMESTRING */
Object generate_dos_namestring(pathname_1)
    Object pathname_1;
{
    Object character_case_mode_for_generalized_dos;
    Declare_special(1);
    Object result;

    x_note_fn_call(40,71);
    character_case_mode_for_generalized_dos = Kall_uppercase;
    PUSH_SPECIAL_WITH_SYMBOL(Character_case_mode_for_generalized_dos,Qcharacter_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
	    0);
      result = generate_generalized_dos_namestring(pathname_1);
    POP_SPECIAL();
    return result;
}

/* GENERATE-WIN32-NAMESTRING */
Object generate_win32_namestring(pathname_1)
    Object pathname_1;
{
    Object character_case_mode_for_generalized_dos;
    Declare_special(1);
    Object result;

    x_note_fn_call(40,72);
    character_case_mode_for_generalized_dos = Kcase_sensitive;
    PUSH_SPECIAL_WITH_SYMBOL(Character_case_mode_for_generalized_dos,Qcharacter_case_mode_for_generalized_dos,character_case_mode_for_generalized_dos,
	    0);
      result = generate_generalized_dos_namestring(pathname_1);
    POP_SPECIAL();
    return result;
}

void file_parse_INIT()
{
    Object temp, pushnew_arg_1, pushnew_arg_3;
    Object filename_special_character_registry_new_value;
    Object reclaim_structure_for_filename_parser_information_1;
    Object Qgenerate_generalized_dos_namestring, list_constant_25, AB_package;
    Object Qgenerate_vms_namestring, array_constant_6, list_constant_23;
    Object list_constant_28, list_constant_29, list_constant_27;
    Object Qgenerate_unix_namestring, array_constant_5, list_constant_26;
    Object Qfinal_generalized_dos_parser_node;
    Object Qerror_in_generalized_dos_filename_parser;
    Object Qparse_generalized_dos_filename_node_100;
    Object Qparse_generalized_dos_filename_node_101;
    Object Qparse_generalized_dos_filename_node_102;
    Object Qparse_generalized_dos_filename_node_103;
    Object Qparse_generalized_dos_filename_node_104;
    Object Qparse_generalized_dos_filename_node_105;
    Object Qparse_generalized_dos_filename_node_106;
    Object Qparse_generalized_dos_filename_node_108;
    Object Qparse_generalized_dos_filename_node_110;
    Object Qparse_generalized_dos_filename_node_111;
    Object Qparse_generalized_dos_filename, list_constant_24;
    Object Qfinal_vms_parser_node, Qerror_in_vms_filename_parser;
    Object Qparse_vms_filename_node_101, Qparse_vms_filename_node_102;
    Object Qparse_vms_filename_node_103, Qparse_vms_filename_node_104;
    Object Qparse_vms_filename_node_105, Qparse_vms_filename_node_106;
    Object Qparse_vms_filename_node_107, Qparse_vms_filename_node_108;
    Object Qparse_vms_filename_node_109, Qparse_vms_filename_node_110;
    Object Qparse_vms_filename_node_111, Qparse_vms_filename_node_112;
    Object Qparse_vms_filename_node_113, Qparse_vms_filename_node_114;
    Object Qparse_vms_filename, Qfinal_unix_parser_node;
    Object Qerror_in_unix_filename_parser, Qparse_unix_filename_node_100;
    Object Qparse_unix_filename_node_101, Qparse_unix_filename_node_102;
    Object Qparse_unix_filename_node_103, Qparse_unix_filename_node_104;
    Object Qparse_unix_filename_node_105, Qparse_unix_filename_node_106;
    Object Qparse_unix_filename_node_108, Qparse_unix_filename_node_109;
    Object Qparse_unix_filename_node_110, Qparse_unix_filename_node_111;
    Object Qparse_unix_filename, Qfile_parse, Qfilename_parser_information;
    Object Qreclaim_structure, Qoutstanding_filename_parser_information_count;
    Object Qfilename_parser_information_structure_memory_usage, Qutilities2;
    Object string_constant_15, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_14, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qequalw;

    x_note_fn_call(40,73);
    SET_PACKAGE("AB");
    if (Filename_special_character_registry == UNBOUND)
	Filename_special_character_registry = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qlt_end_of_sequence_gt = STATIC_SYMBOL("<END-OF-SEQUENCE>",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlt_end_of_sequence_gt,Lt_end_of_sequence_gt);
    if (Lt_end_of_sequence_gt == UNBOUND)
	Lt_end_of_sequence_gt = Qlt_end_of_sequence_gt;
    Qlt_colon_gt = STATIC_SYMBOL("<COLON>",AB_package);
    Qequalw = STATIC_SYMBOL("EQUALW",AB_package);
    temp = FIX((SI_Long)58L);
    pushnew_arg_1 = CONS(Qlt_colon_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_colon_gt,Lt_colon_gt);
    if (Lt_colon_gt == UNBOUND)
	Lt_colon_gt = Qlt_colon_gt;
    Qlt_slash_gt = STATIC_SYMBOL("<SLASH>",AB_package);
    temp = FIX((SI_Long)47L);
    pushnew_arg_1 = CONS(Qlt_slash_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_slash_gt,Lt_slash_gt);
    if (Lt_slash_gt == UNBOUND)
	Lt_slash_gt = Qlt_slash_gt;
    Qlt_dot_gt = STATIC_SYMBOL("<DOT>",AB_package);
    temp = FIX((SI_Long)46L);
    pushnew_arg_1 = CONS(Qlt_dot_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_dot_gt,Lt_dot_gt);
    if (Lt_dot_gt == UNBOUND)
	Lt_dot_gt = Qlt_dot_gt;
    Qlt_tilde_gt = STATIC_SYMBOL("<TILDE>",AB_package);
    temp = FIX((SI_Long)126L);
    pushnew_arg_1 = CONS(Qlt_tilde_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_tilde_gt,Lt_tilde_gt);
    if (Lt_tilde_gt == UNBOUND)
	Lt_tilde_gt = Qlt_tilde_gt;
    Qlt_asterisk_gt = STATIC_SYMBOL("<ASTERISK>",AB_package);
    temp = FIX((SI_Long)42L);
    pushnew_arg_1 = CONS(Qlt_asterisk_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_asterisk_gt,Lt_asterisk_gt);
    if (Lt_asterisk_gt == UNBOUND)
	Lt_asterisk_gt = Qlt_asterisk_gt;
    Qlt_left_bracket_gt = STATIC_SYMBOL("<LEFT-BRACKET>",AB_package);
    temp = FIX((SI_Long)91L);
    pushnew_arg_1 = CONS(Qlt_left_bracket_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_left_bracket_gt,Lt_left_bracket_gt);
    if (Lt_left_bracket_gt == UNBOUND)
	Lt_left_bracket_gt = Qlt_left_bracket_gt;
    Qlt_right_bracket_gt = STATIC_SYMBOL("<RIGHT-BRACKET>",AB_package);
    temp = FIX((SI_Long)93L);
    pushnew_arg_1 = CONS(Qlt_right_bracket_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_right_bracket_gt,Lt_right_bracket_gt);
    if (Lt_right_bracket_gt == UNBOUND)
	Lt_right_bracket_gt = Qlt_right_bracket_gt;
    Qlt_semicolon_gt = STATIC_SYMBOL("<SEMICOLON>",AB_package);
    temp = FIX((SI_Long)59L);
    pushnew_arg_1 = CONS(Qlt_semicolon_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_semicolon_gt,Lt_semicolon_gt);
    if (Lt_semicolon_gt == UNBOUND)
	Lt_semicolon_gt = Qlt_semicolon_gt;
    Qlt_double_quote_gt = STATIC_SYMBOL("<DOUBLE-QUOTE>",AB_package);
    temp = FIX((SI_Long)34L);
    pushnew_arg_1 = CONS(Qlt_double_quote_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_double_quote_gt,Lt_double_quote_gt);
    if (Lt_double_quote_gt == UNBOUND)
	Lt_double_quote_gt = Qlt_double_quote_gt;
    Qlt_space_gt = STATIC_SYMBOL("<SPACE>",AB_package);
    temp = FIX((SI_Long)32L);
    pushnew_arg_1 = CONS(Qlt_space_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_space_gt,Lt_space_gt);
    if (Lt_space_gt == UNBOUND)
	Lt_space_gt = Qlt_space_gt;
    Qlt_hyphen_gt = STATIC_SYMBOL("<HYPHEN>",AB_package);
    temp = FIX((SI_Long)45L);
    pushnew_arg_1 = CONS(Qlt_hyphen_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_hyphen_gt,Lt_hyphen_gt);
    if (Lt_hyphen_gt == UNBOUND)
	Lt_hyphen_gt = Qlt_hyphen_gt;
    Qlt_left_angle_bracket_gt = STATIC_SYMBOL("<LEFT-ANGLE-BRACKET>",
	    AB_package);
    temp = FIX((SI_Long)60L);
    pushnew_arg_1 = CONS(Qlt_left_angle_bracket_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_left_angle_bracket_gt,
	    Lt_left_angle_bracket_gt);
    if (Lt_left_angle_bracket_gt == UNBOUND)
	Lt_left_angle_bracket_gt = Qlt_left_angle_bracket_gt;
    Qlt_right_angle_bracket_gt = STATIC_SYMBOL("<RIGHT-ANGLE-BRACKET>",
	    AB_package);
    temp = FIX((SI_Long)62L);
    pushnew_arg_1 = CONS(Qlt_right_angle_bracket_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_right_angle_bracket_gt,
	    Lt_right_angle_bracket_gt);
    if (Lt_right_angle_bracket_gt == UNBOUND)
	Lt_right_angle_bracket_gt = Qlt_right_angle_bracket_gt;
    Qlt_sharp_sign_gt = STATIC_SYMBOL("<SHARP-SIGN>",AB_package);
    temp = FIX((SI_Long)35L);
    pushnew_arg_1 = CONS(Qlt_sharp_sign_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_sharp_sign_gt,Lt_sharp_sign_gt);
    if (Lt_sharp_sign_gt == UNBOUND)
	Lt_sharp_sign_gt = Qlt_sharp_sign_gt;
    Qlt_exclamation_gt = STATIC_SYMBOL("<EXCLAMATION>",AB_package);
    temp = FIX((SI_Long)33L);
    pushnew_arg_1 = CONS(Qlt_exclamation_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_exclamation_gt,Lt_exclamation_gt);
    if (Lt_exclamation_gt == UNBOUND)
	Lt_exclamation_gt = Qlt_exclamation_gt;
    Qlt_comma_gt = STATIC_SYMBOL("<COMMA>",AB_package);
    temp = FIX((SI_Long)44L);
    pushnew_arg_1 = CONS(Qlt_comma_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_comma_gt,Lt_comma_gt);
    if (Lt_comma_gt == UNBOUND)
	Lt_comma_gt = Qlt_comma_gt;
    Qlt_backslash_gt = STATIC_SYMBOL("<BACKSLASH>",AB_package);
    temp = FIX((SI_Long)92L);
    pushnew_arg_1 = CONS(Qlt_backslash_gt,temp);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    filename_special_character_registry_new_value = adjoin(4,pushnew_arg_1,
	    Filename_special_character_registry,Ktest,pushnew_arg_3);
    Filename_special_character_registry = 
	    filename_special_character_registry_new_value;
    SET_SYMBOL_VALUE_LOCATION(Qlt_backslash_gt,Lt_backslash_gt);
    if (Lt_backslash_gt == UNBOUND)
	Lt_backslash_gt = Qlt_backslash_gt;
    Kcase_sensitive = STATIC_SYMBOL("CASE-SENSITIVE",Pkeyword);
    Kall_uppercase = STATIC_SYMBOL("ALL-UPPERCASE",Pkeyword);
    Kall_lowercase = STATIC_SYMBOL("ALL-LOWERCASE",Pkeyword);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    if (Trace_filename_parsing_p == UNBOUND)
	Trace_filename_parsing_p = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_filename_parser_information_g2_struct = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfilename_parser_information = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    Qfilename_parser_information,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qfilename_parser_information,
	    Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_filename_parser_information == UNBOUND)
	The_type_description_of_filename_parser_information = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83hHy1n83hHy8n8k1l8n0000001m1n8y83-3dy01m83My83-ACykuk0k0");
    temp = The_type_description_of_filename_parser_information;
    The_type_description_of_filename_parser_information = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_filename_parser_information_g2_struct,
	    The_type_description_of_filename_parser_information,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qfilename_parser_information,
	    The_type_description_of_filename_parser_information,
	    Qtype_description_of_type);
    Qoutstanding_filename_parser_information_count = 
	    STATIC_SYMBOL("OUTSTANDING-FILENAME-PARSER-INFORMATION-COUNT",
	    AB_package);
    Qfilename_parser_information_structure_memory_usage = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_15 = STATIC_STRING("1q83hHy8s83-Tvy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_filename_parser_information_count);
    push_optimized_constant(Qfilename_parser_information_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_filename_parser_informations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FILENAME-PARSER-INFORMATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_filename_parser_informations,
	    Chain_of_available_filename_parser_informations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_filename_parser_informations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qfilename_parser_information_count = 
	    STATIC_SYMBOL("FILENAME-PARSER-INFORMATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfilename_parser_information_count,
	    Filename_parser_information_count);
    record_system_variable(Qfilename_parser_information_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_filename_parser_informations_vector == UNBOUND)
	Chain_of_available_filename_parser_informations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qfilename_parser_information_structure_memory_usage,
	    STATIC_FUNCTION(filename_parser_information_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_filename_parser_information_count,
	    STATIC_FUNCTION(outstanding_filename_parser_information_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_filename_parser_information_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_filename_parser_information,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qfilename_parser_information,
	    reclaim_structure_for_filename_parser_information_1);
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    Qfilename_parser_of_file_system = 
	    STATIC_SYMBOL("FILENAME-PARSER-OF-FILE-SYSTEM",AB_package);
    Filename_parser_of_file_system_prop = Qfilename_parser_of_file_system;
    Qnamestring_generator_of_file_system = 
	    STATIC_SYMBOL("NAMESTRING-GENERATOR-OF-FILE-SYSTEM",AB_package);
    Namestring_generator_of_file_system_prop = 
	    Qnamestring_generator_of_file_system;
    if (All_known_file_systems == UNBOUND)
	All_known_file_systems = Nil;
    Qaccept_any_version_component_p = 
	    STATIC_SYMBOL("ACCEPT-ANY-VERSION-COMPONENT-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaccept_any_version_component_p,
	    Accept_any_version_component_p);
    Qfile_parse = STATIC_SYMBOL("FILE-PARSE",AB_package);
    record_system_variable(Qaccept_any_version_component_p,Qfile_parse,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qparse_unix_filename = STATIC_SYMBOL("PARSE-UNIX-FILENAME",AB_package);
    Qconvert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    mutate_global_property(Qparse_unix_filename,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    mutate_global_property(Qunix,Nil,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qunix,Qparse_unix_filename,
	    Qfilename_parser_of_file_system);
    if (Nodes_for_unix_filename_parser == UNBOUND)
	Nodes_for_unix_filename_parser = Nil;
    Qcatcher_for_filename_parse_error = 
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
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qlt_dot_gt,Qlt_tilde_gt,
	    Qlt_slash_gt,Qlt_colon_gt,Qlt_asterisk_gt);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename,
	    STATIC_FUNCTION(parse_unix_filename,NIL,FALSE,1,1));
    Qparse_unix_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-111",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_111,
	    STATIC_FUNCTION(parse_unix_filename_node_111,NIL,FALSE,12,12));
    Qparse_unix_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-110",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_110,
	    STATIC_FUNCTION(parse_unix_filename_node_110,NIL,FALSE,12,12));
    Qparse_unix_filename_node_109 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-109",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_109,
	    STATIC_FUNCTION(parse_unix_filename_node_109,NIL,FALSE,12,12));
    Qparse_unix_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-108",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_108,
	    STATIC_FUNCTION(parse_unix_filename_node_108,NIL,FALSE,12,12));
    Qparse_unix_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-106",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_106,
	    STATIC_FUNCTION(parse_unix_filename_node_106,NIL,FALSE,12,12));
    Qparse_unix_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-105",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_105,
	    STATIC_FUNCTION(parse_unix_filename_node_105,NIL,FALSE,12,12));
    Qparse_unix_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-104",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_104,
	    STATIC_FUNCTION(parse_unix_filename_node_104,NIL,FALSE,12,12));
    Qparse_unix_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-103",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_103,
	    STATIC_FUNCTION(parse_unix_filename_node_103,NIL,FALSE,12,12));
    Qparse_unix_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-102",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_102,
	    STATIC_FUNCTION(parse_unix_filename_node_102,NIL,FALSE,12,12));
    Qparse_unix_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-101",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_101,
	    STATIC_FUNCTION(parse_unix_filename_node_101,NIL,FALSE,12,12));
    Qparse_unix_filename_node_100 = 
	    STATIC_SYMBOL("PARSE-UNIX-FILENAME-NODE-100",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_unix_filename_node_100,
	    STATIC_FUNCTION(parse_unix_filename_node_100,NIL,FALSE,12,12));
    Qerror_in_unix_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-UNIX-FILENAME-PARSER",AB_package);
    SET_SYMBOL_FUNCTION(Qerror_in_unix_filename_parser,
	    STATIC_FUNCTION(error_in_unix_filename_parser,NIL,FALSE,1,1));
    Qfinal_unix_parser_node = STATIC_SYMBOL("FINAL-UNIX-PARSER-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfinal_unix_parser_node,
	    STATIC_FUNCTION(final_unix_parser_node,NIL,FALSE,12,12));
    Nodes_for_unix_filename_parser = make_array(5,FIX((SI_Long)13L),
	    Kelement_type,T,Kinitial_contents,list(13,
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_111),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_110),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_109),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_108),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_106),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_105),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_104),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_103),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_102),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_101),
	    SYMBOL_FUNCTION(Qparse_unix_filename_node_100),
	    SYMBOL_FUNCTION(Qerror_in_unix_filename_parser),
	    SYMBOL_FUNCTION(Qfinal_unix_parser_node)));
    if (Vms_directory_filenames_can_dangle_p == UNBOUND)
	Vms_directory_filenames_can_dangle_p = Nil;
    Qparse_vms_filename = STATIC_SYMBOL("PARSE-VMS-FILENAME",AB_package);
    mutate_global_property(Qparse_vms_filename,T,
	    Qconvert_file_strings_to_uppercase_p);
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    mutate_global_property(Qvms,T,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qvms,Qparse_vms_filename,
	    Qfilename_parser_of_file_system);
    if (Nodes_for_vms_filename_parser == UNBOUND)
	Nodes_for_vms_filename_parser = Nil;
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
    list_constant_2 = STATIC_LIST((SI_Long)9L,Qlt_colon_gt,Qlt_dot_gt,
	    Qlt_asterisk_gt,Qlt_left_bracket_gt,Qlt_right_bracket_gt,
	    Qlt_semicolon_gt,Qlt_double_quote_gt,Qlt_space_gt,Qlt_hyphen_gt);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename,
	    STATIC_FUNCTION(parse_vms_filename,NIL,FALSE,1,1));
    Qparse_vms_filename_node_114 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-114",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_114,
	    STATIC_FUNCTION(parse_vms_filename_node_114,NIL,FALSE,14,14));
    Qparse_vms_filename_node_113 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-113",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_113,
	    STATIC_FUNCTION(parse_vms_filename_node_113,NIL,FALSE,14,14));
    Qparse_vms_filename_node_112 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-112",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_112,
	    STATIC_FUNCTION(parse_vms_filename_node_112,NIL,FALSE,14,14));
    Qparse_vms_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-111",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_111,
	    STATIC_FUNCTION(parse_vms_filename_node_111,NIL,FALSE,14,14));
    Qparse_vms_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-110",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_110,
	    STATIC_FUNCTION(parse_vms_filename_node_110,NIL,FALSE,14,14));
    Qparse_vms_filename_node_109 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-109",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_109,
	    STATIC_FUNCTION(parse_vms_filename_node_109,NIL,FALSE,14,14));
    Qparse_vms_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-108",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_108,
	    STATIC_FUNCTION(parse_vms_filename_node_108,NIL,FALSE,14,14));
    Qparse_vms_filename_node_107 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-107",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_107,
	    STATIC_FUNCTION(parse_vms_filename_node_107,NIL,FALSE,14,14));
    Qparse_vms_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-106",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_106,
	    STATIC_FUNCTION(parse_vms_filename_node_106,NIL,FALSE,14,14));
    Qparse_vms_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-105",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_105,
	    STATIC_FUNCTION(parse_vms_filename_node_105,NIL,FALSE,14,14));
    Qparse_vms_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-104",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_104,
	    STATIC_FUNCTION(parse_vms_filename_node_104,NIL,FALSE,14,14));
    Qparse_vms_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-103",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_103,
	    STATIC_FUNCTION(parse_vms_filename_node_103,NIL,FALSE,14,14));
    Qparse_vms_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-102",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_102,
	    STATIC_FUNCTION(parse_vms_filename_node_102,NIL,FALSE,14,14));
    Qparse_vms_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-VMS-FILENAME-NODE-101",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_vms_filename_node_101,
	    STATIC_FUNCTION(parse_vms_filename_node_101,NIL,FALSE,14,14));
    Qerror_in_vms_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-VMS-FILENAME-PARSER",AB_package);
    SET_SYMBOL_FUNCTION(Qerror_in_vms_filename_parser,
	    STATIC_FUNCTION(error_in_vms_filename_parser,NIL,FALSE,1,1));
    Qfinal_vms_parser_node = STATIC_SYMBOL("FINAL-VMS-PARSER-NODE",AB_package);
    SET_SYMBOL_FUNCTION(Qfinal_vms_parser_node,
	    STATIC_FUNCTION(final_vms_parser_node,NIL,FALSE,14,14));
    Nodes_for_vms_filename_parser = make_array(5,FIX((SI_Long)16L),
	    Kelement_type,T,Kinitial_contents,list(16,
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_114),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_113),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_112),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_111),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_110),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_109),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_108),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_107),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_106),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_105),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_104),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_103),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_102),
	    SYMBOL_FUNCTION(Qparse_vms_filename_node_101),
	    SYMBOL_FUNCTION(Qerror_in_vms_filename_parser),
	    SYMBOL_FUNCTION(Qfinal_vms_parser_node)));
    Qparse_generalized_dos_filename = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME",AB_package);
    mutate_global_property(Qparse_generalized_dos_filename,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    Qgeneralized_dos = STATIC_SYMBOL("GENERALIZED-DOS",AB_package);
    mutate_global_property(Qgeneralized_dos,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qgeneralized_dos,
	    Qparse_generalized_dos_filename,Qfilename_parser_of_file_system);
    if (Nodes_for_generalized_dos_filename_parser == UNBOUND)
	Nodes_for_generalized_dos_filename_parser = Nil;
    string_constant_10 = STATIC_STRING("device must only have one letter");
    string_constant_11 = STATIC_STRING("no wildcards allowed in directory");
    string_constant_12 = STATIC_STRING("file type required");
    string_constant_13 = STATIC_STRING("over 63 characters in filename");
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qlt_colon_gt,Qlt_asterisk_gt);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qlt_dot_gt,
	    Qlt_backslash_gt,list_constant_24);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename,
	    STATIC_FUNCTION(parse_generalized_dos_filename,NIL,FALSE,1,1));
    Qparse_generalized_dos_filename_node_111 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-111",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_111,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_111,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_110 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-110",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_110,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_110,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_108 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-108",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_108,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_108,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_106 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-106",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_106,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_106,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_105 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-105",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_105,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_105,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_104 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-104",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_104,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_104,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_103 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-103",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_103,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_103,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_102 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-102",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_102,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_102,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_101 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-101",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_101,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_101,NIL,
	    FALSE,13,13));
    Qparse_generalized_dos_filename_node_100 = 
	    STATIC_SYMBOL("PARSE-GENERALIZED-DOS-FILENAME-NODE-100",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_100,
	    STATIC_FUNCTION(parse_generalized_dos_filename_node_100,NIL,
	    FALSE,13,13));
    Qerror_in_generalized_dos_filename_parser = 
	    STATIC_SYMBOL("ERROR-IN-GENERALIZED-DOS-FILENAME-PARSER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qerror_in_generalized_dos_filename_parser,
	    STATIC_FUNCTION(error_in_generalized_dos_filename_parser,NIL,
	    FALSE,1,1));
    Qfinal_generalized_dos_parser_node = 
	    STATIC_SYMBOL("FINAL-GENERALIZED-DOS-PARSER-NODE",AB_package);
    SET_SYMBOL_FUNCTION(Qfinal_generalized_dos_parser_node,
	    STATIC_FUNCTION(final_generalized_dos_parser_node,NIL,FALSE,13,
	    13));
    Nodes_for_generalized_dos_filename_parser = make_array(5,
	    FIX((SI_Long)12L),Kelement_type,T,Kinitial_contents,list(12,
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_111),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_110),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_108),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_106),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_105),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_104),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_103),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_102),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_101),
	    SYMBOL_FUNCTION(Qparse_generalized_dos_filename_node_100),
	    SYMBOL_FUNCTION(Qerror_in_generalized_dos_filename_parser),
	    SYMBOL_FUNCTION(Qfinal_generalized_dos_parser_node)));
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    Qparse_dos_filename = STATIC_SYMBOL("PARSE-DOS-FILENAME",AB_package);
    Qgenerate_dos_namestring = STATIC_SYMBOL("GENERATE-DOS-NAMESTRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_dos_filename,
	    STATIC_FUNCTION(parse_dos_filename,NIL,FALSE,1,1));
    mutate_global_property(Qdos,T,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qparse_dos_filename,T,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qdos,Qparse_dos_filename,
	    Qfilename_parser_of_file_system);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    Qparse_win32_filename = STATIC_SYMBOL("PARSE-WIN32-FILENAME",AB_package);
    Qgenerate_win32_namestring = STATIC_SYMBOL("GENERATE-WIN32-NAMESTRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qparse_win32_filename,
	    STATIC_FUNCTION(parse_win32_filename,NIL,FALSE,1,1));
    mutate_global_property(Qwin32,Nil,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qparse_win32_filename,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qwin32,Qparse_win32_filename,
	    Qfilename_parser_of_file_system);
    if (Last_deletable_token_in_namestring == UNBOUND)
	Last_deletable_token_in_namestring = Nil;
    Qex_delete_ex = STATIC_SYMBOL("!DELETE!",AB_package);
    Qex_deletable_ex = STATIC_SYMBOL("!DELETABLE!",AB_package);
    Kcomponent = STATIC_SYMBOL("COMPONENT",Pkeyword);
    Kleading_items = STATIC_SYMBOL("LEADING-ITEMS",Pkeyword);
    Klast_item = STATIC_SYMBOL("LAST-ITEM",Pkeyword);
    Kcompound = STATIC_SYMBOL("COMPOUND",Pkeyword);
    Qgenerate_unix_namestring = STATIC_SYMBOL("GENERATE-UNIX-NAMESTRING",
	    AB_package);
    mutate_global_property(Qgenerate_unix_namestring,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qunix,Nil,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qunix,Qgenerate_unix_namestring,
	    Qnamestring_generator_of_file_system);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kcomponent,Qlt_colon_gt);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kcomponent,Qlt_slash_gt);
    list_constant_6 = STATIC_CONS(Kcompound,Qnil);
    array_constant_4 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qlt_dot_gt,Qlt_dot_gt);
    list_constant_7 = STATIC_LIST((SI_Long)10L,Kabsolute,array_constant_4,
	    Krelative,Qlt_dot_gt,Kup,list_constant_25,Kwild,
	    Qlt_asterisk_gt,Khome,Qlt_tilde_gt);
    list_constant_8 = STATIC_CONS(Kcomponent,Qnil);
    list_constant_26 = STATIC_CONS(Qlt_asterisk_gt,Qnil);
    list_constant_9 = STATIC_CONS(Kwild,list_constant_26);
    list_constant_10 = STATIC_CONS(Qlt_dot_gt,list_constant_8);
    array_constant_5 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    list_constant_11 = STATIC_LIST((SI_Long)6L,Kprevious,Qlt_tilde_gt,
	    Knewest,array_constant_4,Kwild,array_constant_5);
    SET_SYMBOL_FUNCTION(Qgenerate_unix_namestring,
	    STATIC_FUNCTION(generate_unix_namestring,NIL,FALSE,1,1));
    Qgenerate_vms_namestring = STATIC_SYMBOL("GENERATE-VMS-NAMESTRING",
	    AB_package);
    mutate_global_property(Qgenerate_vms_namestring,T,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qvms,T,Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qvms,Qgenerate_vms_namestring,
	    Qnamestring_generator_of_file_system);
    list_constant_27 = STATIC_CONS(Qlt_colon_gt,Qnil);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)3L,Kcomponent,
	    Qlt_colon_gt,list_constant_27);
    list_constant_28 = STATIC_CONS(Qlt_dot_gt,Qnil);
    list_constant_29 = STATIC_CONS(Kcomponent,list_constant_28);
    list_constant_13 = STATIC_LIST((SI_Long)4L,Kleading_items,
	    list_constant_29,Klast_item,list_constant_8);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qlt_left_bracket_gt,
	    Kcompound,Qlt_right_bracket_gt);
    list_constant_15 = STATIC_LIST((SI_Long)8L,Kup,Qlt_hyphen_gt,Kwild,
	    Qlt_asterisk_gt,Kwild_inferiors,list_constant_25,Krelative,
	    array_constant_4);
    list_constant_16 = STATIC_CONS(Qlt_hyphen_gt,list_constant_28);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,array_constant_1,
	    Qlt_dot_gt,list_constant_25);
    list_constant_18 = STATIC_CONS(Qlt_semicolon_gt,list_constant_8);
    array_constant_6 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    list_constant_19 = STATIC_LIST_STAR((SI_Long)5L,Kprevious,
	    array_constant_6,Knewest,array_constant_3,list_constant_9);
    SET_SYMBOL_FUNCTION(Qgenerate_vms_namestring,
	    STATIC_FUNCTION(generate_vms_namestring,NIL,FALSE,1,1));
    Qgenerate_generalized_dos_namestring = 
	    STATIC_SYMBOL("GENERATE-GENERALIZED-DOS-NAMESTRING",AB_package);
    mutate_global_property(Qgenerate_generalized_dos_namestring,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qgeneralized_dos,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qgeneralized_dos,
	    Qgenerate_generalized_dos_namestring,
	    Qnamestring_generator_of_file_system);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)3L,Qlt_backslash_gt,
	    Qlt_backslash_gt,list_constant_8);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Kcomponent,Qlt_backslash_gt);
    list_constant_22 = STATIC_LIST((SI_Long)6L,Kabsolute,array_constant_4,
	    Krelative,Qlt_dot_gt,Kup,list_constant_25);
    SET_SYMBOL_FUNCTION(Qgenerate_generalized_dos_namestring,
	    STATIC_FUNCTION(generate_generalized_dos_namestring,NIL,FALSE,
	    1,1));
    SET_SYMBOL_FUNCTION(Qgenerate_dos_namestring,
	    STATIC_FUNCTION(generate_dos_namestring,NIL,FALSE,1,1));
    mutate_global_property(Qgenerate_dos_namestring,T,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qdos,Qgenerate_dos_namestring,
	    Qnamestring_generator_of_file_system);
    SET_SYMBOL_FUNCTION(Qgenerate_win32_namestring,
	    STATIC_FUNCTION(generate_win32_namestring,NIL,FALSE,1,1));
    mutate_global_property(Qgenerate_win32_namestring,Nil,
	    Qconvert_file_strings_to_uppercase_p);
    mutate_global_property(Qwin32,Qgenerate_win32_namestring,
	    Qnamestring_generator_of_file_system);
}
