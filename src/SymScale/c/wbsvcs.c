/* wbsvcs.c
 * Input file:  web-services.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "wbsvcs.h"


Object The_type_description_of_uri_reference = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_uri_references, Qchain_of_available_uri_references);

DEFINE_VARIABLE_WITH_SYMBOL(Uri_reference_count, Quri_reference_count);

Object Chain_of_available_uri_references_vector = UNBOUND;

/* URI-REFERENCE-STRUCTURE-MEMORY-USAGE */
Object uri_reference_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(242,0);
    temp = Uri_reference_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-URI-REFERENCE-COUNT */
Object outstanding_uri_reference_count()
{
    Object def_structure_uri_reference_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(242,1);
    gensymed_symbol = IFIX(Uri_reference_count);
    def_structure_uri_reference_variable = Chain_of_available_uri_references;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_uri_reference_variable))
	goto end_loop;
    def_structure_uri_reference_variable = 
	    ISVREF(def_structure_uri_reference_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-URI-REFERENCE-1 */
Object reclaim_uri_reference_1(uri_reference)
    Object uri_reference;
{
    Object structure_being_reclaimed, thing, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(242,2);
    inline_note_reclaim_cons(uri_reference,Nil);
    structure_being_reclaimed = uri_reference;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      thing = ISVREF(uri_reference,(SI_Long)2L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(uri_reference,FIX((SI_Long)2L)) = Nil;
      thing = ISVREF(uri_reference,(SI_Long)3L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(uri_reference,FIX((SI_Long)3L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(uri_reference,(SI_Long)5L));
      SVREF(uri_reference,FIX((SI_Long)5L)) = Nil;
      thing = ISVREF(uri_reference,(SI_Long)6L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(uri_reference,FIX((SI_Long)6L)) = Nil;
      thing = ISVREF(uri_reference,(SI_Long)7L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(uri_reference,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_uri_references_vector,
	    IFIX(Current_thread_index));
    SVREF(uri_reference,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_uri_references_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = uri_reference;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-URI-REFERENCE */
Object reclaim_structure_for_uri_reference(uri_reference)
    Object uri_reference;
{
    x_note_fn_call(242,3);
    return reclaim_uri_reference_1(uri_reference);
}

static Object Qg2_defstruct_structure_name_uri_reference_g2_struct;  /* g2-defstruct-structure-name::uri-reference-g2-struct */

/* MAKE-PERMANENT-URI-REFERENCE-STRUCTURE-INTERNAL */
Object make_permanent_uri_reference_structure_internal()
{
    Object def_structure_uri_reference_variable;
    Object defstruct_g2_uri_reference_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(242,4);
    def_structure_uri_reference_variable = Nil;
    atomic_incff_symval(Quri_reference_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_uri_reference_variable = Nil;
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
	defstruct_g2_uri_reference_variable = the_array;
	SVREF(defstruct_g2_uri_reference_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uri_reference_g2_struct;
	def_structure_uri_reference_variable = 
		defstruct_g2_uri_reference_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_uri_reference_variable);
}

/* MAKE-URI-REFERENCE-1 */
Object make_uri_reference_1(uri_scheme,uri_userinfo,uri_host,uri_port,
	    uri_path,uri_query,uri_fragment)
    Object uri_scheme, uri_userinfo, uri_host, uri_port, uri_path, uri_query;
    Object uri_fragment;
{
    Object def_structure_uri_reference_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(242,5);
    def_structure_uri_reference_variable = 
	    ISVREF(Chain_of_available_uri_references_vector,
	    IFIX(Current_thread_index));
    if (def_structure_uri_reference_variable) {
	svref_arg_1 = Chain_of_available_uri_references_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_uri_reference_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_uri_reference_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uri_reference_g2_struct;
    }
    else
	def_structure_uri_reference_variable = 
		make_permanent_uri_reference_structure_internal();
    inline_note_allocate_cons(def_structure_uri_reference_variable,Nil);
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)1L)) = uri_scheme;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)2L)) = 
	    uri_userinfo;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)3L)) = uri_host;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)4L)) = uri_port;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)5L)) = uri_path;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)6L)) = uri_query;
    SVREF(def_structure_uri_reference_variable,FIX((SI_Long)7L)) = 
	    uri_fragment;
    return VALUES_1(def_structure_uri_reference_variable);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* PARSE-URI */
Object parse_uri(string_1)
    Object string_1;
{
    Object uri, mark, point, end_1, char_1, scheme_string, temp_1;
    Object ab_loop_iter_flag_, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object d1, d2, simple_or_wide_character, thing, schar_arg_2;
    Object schar_new_value, host_and_port_end, port, factor, digit, temp_3;
    Object more_segments_p, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long i, j, temp_2, bv16_length, aref_new_value, length_1, ab_loop_bind_;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(242,6);
    uri = make_uri_reference_1(Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    mark = FIX((SI_Long)0L);
    point = FIX((SI_Long)0L);
    end_1 = text_string_length(string_1);
    char_1 = Nil;
    point = mark;
  next_loop:
    if ( !FIXNUM_LT(point,end_1))
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(point)));
    if (position_in_text_string(char_1,array_constant)) {
	temp = TRUEP(T);
	goto end_2;
    }
    if (position_in_text_string(char_1,array_constant_1)) {
	temp = TRUEP(Nil);
	goto end_2;
    }
    point = FIXNUM_ADD1(point);
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_2:;
    if (temp) {
	if ( !TRUEP(zerop(point))) {
	    scheme_string = text_string_substring(string_1,mark,point);
	    upcase_text_string_in_place(scheme_string);
	    temp_1 = intern_text_string(1,scheme_string);
	    SVREF(uri,FIX((SI_Long)1L)) = temp_1;
	    mark = FIXNUM_ADD1(point);
	}
    }
    if ( !(IFIX(FIXNUM_MINUS(end_1,mark)) < (SI_Long)2L)) {
	i = (SI_Long)0L;
	j = IFIX(mark);
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (i >= (SI_Long)2L)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	if ( !(UBYTE_16_ISAREF_1(array_constant_2,i) == 
		UBYTE_16_ISAREF_1(string_1,j))) {
	    temp = TRUEP(Nil);
	    goto end_3;
	}
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = IFIX(mark) + (SI_Long)2L;
	mark = FIX(temp_2);
	temp = TRUEP(T);
	goto end_3;
	temp = TRUEP(Qnil);
      end_3:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	char_1 = Nil;
	point = mark;
      next_loop_2:
	if ( !FIXNUM_LT(point,end_1))
	    goto end_loop_2;
	char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(point)));
	if (position_in_text_string(char_1,array_constant_3)) {
	    temp = TRUEP(T);
	    goto end_4;
	}
	if (position_in_text_string(char_1,array_constant_1)) {
	    temp = TRUEP(Nil);
	    goto end_4;
	}
	point = FIXNUM_ADD1(point);
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(Qnil);
      end_4:;
	if (temp) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
		      (SI_Long)3L));
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      temp_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
	      temp_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
		      i = IFIX(mark);
		      ab_loop_bind_ = IFIX(point);
		      char_1 = Nil;
		    next_loop_3:
		      if (i >= ab_loop_bind_)
			  goto end_loop_3;
		      char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
		      if (IFIX(char_1) == (SI_Long)37L && IFIX(point) - i 
			      >= (SI_Long)2L) {
			  d1 = 
				  digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
				  i + (SI_Long)1L)),FIX((SI_Long)16L));
			  d2 = 
				  digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
				  i + (SI_Long)2L)),FIX((SI_Long)16L));
			  if (d1 && d2) {
			      i = i + (SI_Long)2L;
			      simple_or_wide_character = FIX((IFIX(d1) << 
				      (SI_Long)4L) + IFIX(d2));
			  }
			  else
			      simple_or_wide_character = Nil;
		      }
		      else
			  simple_or_wide_character = Nil;
		      if (simple_or_wide_character);
		      else
			  simple_or_wide_character = char_1;
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
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = simple_or_wide_character;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      i = i + (SI_Long)1L;
		      goto next_loop_3;
		    end_loop_3:
		      mark = point;
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SVREF(uri,FIX((SI_Long)2L)) = temp_1;
	    mark = FIXNUM_ADD1(mark);
	}
	char_1 = Nil;
	point = mark;
      next_loop_4:
	if ( !FIXNUM_LT(point,end_1))
	    goto end_loop_4;
	char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(point)));
	if (position_in_text_string(char_1,array_constant_1))
	    goto end_5;
	if (position_in_text_string(char_1,array_constant_4))
	    goto end_5;
	point = FIXNUM_ADD1(point);
	goto next_loop_4;
      end_loop_4:
      end_5:;
	host_and_port_end = point;
	port = Nil;
	factor = FIX((SI_Long)1L);
	i = IFIX(FIXNUM_SUB1(point));
	ab_loop_bind_ = IFIX(mark);
	char_1 = Nil;
	digit = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_5:
	if (IFIX(factor) > (SI_Long)100000L)
	    goto end_loop_5;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i - (SI_Long)1L;
	if (i < ab_loop_bind_)
	    goto end_loop_5;
	char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
	if (IFIX(char_1) == (SI_Long)58L) {
	    SVREF(uri,FIX((SI_Long)4L)) = port;
	    point = FIX(i);
	    goto end_loop_5;
	}
	gensymed_symbol = IFIX(char_1);
	digit = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
	if ( !TRUEP(digit))
	    goto end_loop_5;
	ab_loop_iter_flag_ = Nil;
	temp_3 = port;
	if (temp_3);
	else
	    temp_3 = FIX((SI_Long)0L);
	gensymed_symbol = IFIX(temp_3);
	gensymed_symbol_1 = IFIX(FIXNUM_TIMES(digit,factor));
	port = FIX(gensymed_symbol + gensymed_symbol_1);
	factor = FIX(IFIX(factor) * (SI_Long)10L);
	goto next_loop_5;
      end_loop_5:;
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
	  temp_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
		  i = IFIX(mark);
		  ab_loop_bind_ = IFIX(point);
		  char_1 = Nil;
		next_loop_6:
		  if (i >= ab_loop_bind_)
		      goto end_loop_6;
		  char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
		  if (IFIX(char_1) == (SI_Long)37L && IFIX(point) - i >= 
			  (SI_Long)2L) {
		      d1 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)1L)),FIX((SI_Long)16L));
		      d2 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)2L)),FIX((SI_Long)16L));
		      if (d1 && d2) {
			  i = i + (SI_Long)2L;
			  simple_or_wide_character = FIX((IFIX(d1) << 
				  (SI_Long)4L) + IFIX(d2));
		      }
		      else
			  simple_or_wide_character = Nil;
		  }
		  else
		      simple_or_wide_character = Nil;
		  if (simple_or_wide_character);
		  else
		      simple_or_wide_character = char_1;
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
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop_6;
		end_loop_6:
		  mark = point;
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SVREF(uri,FIX((SI_Long)3L)) = temp_1;
	mark = host_and_port_end;
    }
    more_segments_p = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_7:
    char_1 = Nil;
    point = mark;
  next_loop_8:
    if ( !FIXNUM_LT(point,end_1))
	goto end_loop_7;
    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(point)));
    if (position_in_text_string(char_1,array_constant_5)) {
	more_segments_p = T;
	goto end_6;
    }
    if (position_in_text_string(char_1,array_constant_6)) {
	more_segments_p = Nil;
	goto end_6;
    }
    point = FIXNUM_ADD1(point);
    goto next_loop_8;
  end_loop_7:
    more_segments_p = Qnil;
  end_6:;
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
      temp_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
	      i = IFIX(mark);
	      ab_loop_bind_ = IFIX(point);
	      char_1 = Nil;
	    next_loop_9:
	      if (i >= ab_loop_bind_)
		  goto end_loop_8;
	      char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
	      if (IFIX(char_1) == (SI_Long)37L && IFIX(point) - i >= 
		      (SI_Long)2L) {
		  d1 = 
			  digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			  i + (SI_Long)1L)),FIX((SI_Long)16L));
		  d2 = 
			  digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			  i + (SI_Long)2L)),FIX((SI_Long)16L));
		  if (d1 && d2) {
		      i = i + (SI_Long)2L;
		      simple_or_wide_character = FIX((IFIX(d1) << 
			      (SI_Long)4L) + IFIX(d2));
		  }
		  else
		      simple_or_wide_character = Nil;
	      }
	      else
		  simple_or_wide_character = Nil;
	      if (simple_or_wide_character);
	      else
		  simple_or_wide_character = char_1;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(thing) ? 
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
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_9;
	    end_loop_8:
	      mark = point;
	      temp_3 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = gensym_cons_1(temp_3,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if ( !TRUEP(more_segments_p))
	goto end_loop_9;
    mark = FIXNUM_ADD1(mark);
    goto next_loop_7;
  end_loop_9:
    goto end_7;
    ab_loopvar_ = Qnil;
  end_7:;
    SVREF(uri,FIX((SI_Long)5L)) = ab_loopvar_;
    if ( !(IFIX(FIXNUM_MINUS(end_1,mark)) < (SI_Long)1L)) {
	i = (SI_Long)0L;
	j = IFIX(mark);
	ab_loop_iter_flag_ = T;
      next_loop_10:
	if (i >= (SI_Long)1L)
	    goto end_loop_10;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	if ( !(UBYTE_16_ISAREF_1(array_constant_7,i) == 
		UBYTE_16_ISAREF_1(string_1,j))) {
	    temp = TRUEP(Nil);
	    goto end_8;
	}
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_10;
      end_loop_10:
	mark = FIXNUM_ADD1(mark);
	temp = TRUEP(T);
	goto end_8;
	temp = TRUEP(Qnil);
      end_8:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	char_1 = Nil;
	point = mark;
      next_loop_11:
	if ( !FIXNUM_LT(point,end_1))
	    goto end_loop_11;
	char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(point)));
	if (position_in_text_string(char_1,array_constant_8))
	    goto end_9;
	if (position_in_text_string(char_1,array_constant_4))
	    goto end_9;
	point = FIXNUM_ADD1(point);
	goto next_loop_11;
      end_loop_11:
      end_9:;
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
	  temp_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
		  i = IFIX(mark);
		  ab_loop_bind_ = IFIX(point);
		  char_1 = Nil;
		next_loop_12:
		  if (i >= ab_loop_bind_)
		      goto end_loop_12;
		  char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
		  if (IFIX(char_1) == (SI_Long)37L && IFIX(point) - i >= 
			  (SI_Long)2L) {
		      d1 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)1L)),FIX((SI_Long)16L));
		      d2 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)2L)),FIX((SI_Long)16L));
		      if (d1 && d2) {
			  i = i + (SI_Long)2L;
			  simple_or_wide_character = FIX((IFIX(d1) << 
				  (SI_Long)4L) + IFIX(d2));
		      }
		      else
			  simple_or_wide_character = Nil;
		  }
		  else
		      simple_or_wide_character = Nil;
		  if (simple_or_wide_character);
		  else
		      simple_or_wide_character = char_1;
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
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop_12;
		end_loop_12:
		  mark = point;
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SVREF(uri,FIX((SI_Long)6L)) = temp_1;
    }
    if ( !(IFIX(FIXNUM_MINUS(end_1,mark)) < (SI_Long)1L)) {
	i = (SI_Long)0L;
	j = IFIX(mark);
	ab_loop_iter_flag_ = T;
      next_loop_13:
	if (i >= (SI_Long)1L)
	    goto end_loop_13;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	if ( !(UBYTE_16_ISAREF_1(array_constant_8,i) == 
		UBYTE_16_ISAREF_1(string_1,j))) {
	    temp = TRUEP(Nil);
	    goto end_10;
	}
	ab_loop_iter_flag_ = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_13;
      end_loop_13:
	mark = FIXNUM_ADD1(mark);
	temp = TRUEP(T);
	goto end_10;
	temp = TRUEP(Qnil);
      end_10:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	point = end_1;
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
	  temp_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
		  i = IFIX(mark);
		  ab_loop_bind_ = IFIX(point);
		  char_1 = Nil;
		next_loop_14:
		  if (i >= ab_loop_bind_)
		      goto end_loop_14;
		  char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
		  if (IFIX(char_1) == (SI_Long)37L && IFIX(point) - i >= 
			  (SI_Long)2L) {
		      d1 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)1L)),FIX((SI_Long)16L));
		      d2 = 
			      digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,
			      i + (SI_Long)2L)),FIX((SI_Long)16L));
		      if (d1 && d2) {
			  i = i + (SI_Long)2L;
			  simple_or_wide_character = FIX((IFIX(d1) << 
				  (SI_Long)4L) + IFIX(d2));
		      }
		      else
			  simple_or_wide_character = Nil;
		  }
		  else
		      simple_or_wide_character = Nil;
		  if (simple_or_wide_character);
		  else
		      simple_or_wide_character = char_1;
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
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop_14;
		end_loop_14:
		  mark = point;
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SVREF(uri,FIX((SI_Long)7L)) = temp_1;
    }
    return VALUES_1(uri);
}

/* URI-PATH-IS-EMPTY-P */
Object uri_path_is_empty_p(uri)
    Object uri;
{
    Object temp;

    x_note_fn_call(242,7);
    temp = ISVREF(uri,(SI_Long)5L);
    if ( !TRUEP(CDR(temp))) {
	temp = ISVREF(uri,(SI_Long)5L);
	temp = (SI_Long)0L == IFIX(text_string_length(CAR(temp))) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TWRITE-PERCENT-ENCODED-WIDE-CHARACTER */
Object twrite_percent_encoded_wide_character(char_1)
    Object char_1;
{
    Object hex1, hex2, temp, schar_arg_2, schar_new_value;
    Object simple_or_wide_character, thing_1;
    char thing;
    Object result;

    x_note_fn_call(242,8);
    result = chestnut_floorf_function(char_1,FIX((SI_Long)16L));
    MVS_2(result,hex1,hex2);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = '%';
	twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = '%';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    simple_or_wide_character = digit_char(hex1,FIX((SI_Long)16L),_);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) : 
		thing_1);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    simple_or_wide_character = digit_char(hex2,FIX((SI_Long)16L),_);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) : 
		thing_1);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    return VALUES_1(Nil);
}

/* TWRITE-URI-PATH */
Object twrite_uri_path(path)
    Object path;
{
    Object segment, ab_loop_list_, slash_p, ab_loop_iter_flag_, s, char_1;
    Object temp, gensymed_symbol, thing, temp_1, schar_arg_2, schar_new_value;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(242,9);
    segment = Nil;
    ab_loop_list_ = path;
    slash_p = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    segment = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	slash_p = T;
    if (slash_p)
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)1L));
    s = segment;
    ab_loop_bind_ = IFIX(text_string_length(s));
    i = (SI_Long)0L;
    char_1 = Nil;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
    temp = char_1;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	gensymed_symbol = char_1;
	temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) : Qnil;
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 45:
	  case 46:
	  case 95:
	  case 126:
	  case 33:
	  case 36:
	  case 38:
	  case 39:
	  case 40:
	  case 41:
	  case 42:
	  case 43:
	  case 44:
	  case 59:
	  case 61:
	  case 58:
	  case 64:
	    temp = T;
	    break;
	  default:
	    gensymed_symbol = char_1;
	    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) :
			 Qnil;
	    if (temp);
	    else
		temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) :
			 Qnil;
	    break;
	}
    if (temp) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = char_1;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = char_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    else
	twrite_percent_encoded_wide_character(char_1);
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object string_constant;     /* "~(~a~):" */

static Object string_constant_1;   /* ":~d" */

/* TWRITE-URI */
Object twrite_uri(uri)
    Object uri;
{
    Object s, char_1, temp, gensymed_symbol, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(242,10);
    if (ISVREF(uri,(SI_Long)1L))
	tformat(2,string_constant,ISVREF(uri,(SI_Long)1L));
    if (ISVREF(uri,(SI_Long)3L)) {
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
	if (ISVREF(uri,(SI_Long)2L)) {
	    s = ISVREF(uri,(SI_Long)2L);
	    ab_loop_bind_ = IFIX(text_string_length(s));
	    i = (SI_Long)0L;
	    char_1 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
	    temp = char_1;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		gensymed_symbol = char_1;
		temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) 
			: Qnil;
		if (temp);
		else
		    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : 
			    Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : 
			    Nil) : Qnil;
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 45:
		  case 46:
		  case 95:
		  case 126:
		  case 33:
		  case 36:
		  case 38:
		  case 39:
		  case 40:
		  case 41:
		  case 42:
		  case 43:
		  case 44:
		  case 59:
		  case 61:
		  case 58:
		    temp = T;
		    break;
		  default:
		    gensymed_symbol = char_1;
		    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : 
			    Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
				(IFIX(gensymed_symbol) <= (SI_Long)90L ? T 
				: Nil) : Qnil;
		    if (temp);
		    else
			temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
				(IFIX(gensymed_symbol) <= (SI_Long)57L ? T 
				: Nil) : Qnil;
		    break;
		}
	    if (temp) {
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = char_1;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
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
	    else
		twrite_percent_encoded_wide_character(char_1);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)1L));
	}
	s = ISVREF(uri,(SI_Long)3L);
	ab_loop_bind_ = IFIX(text_string_length(s));
	i = (SI_Long)0L;
	char_1 = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
	temp = char_1;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L)))) {
	    gensymed_symbol = char_1;
	    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) :
			 Qnil;
	    if (temp);
	    else
		temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) :
			 Qnil;
	}
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 45:
	      case 46:
	      case 95:
	      case 126:
	      case 33:
	      case 36:
	      case 38:
	      case 39:
	      case 40:
	      case 41:
	      case 42:
	      case 43:
	      case 44:
	      case 59:
	      case 61:
		temp = T;
		break;
	      default:
		gensymed_symbol = char_1;
		temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) 
			: Qnil;
		if (temp);
		else
		    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : 
			    Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : 
			    Nil) : Qnil;
		break;
	    }
	if (temp) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = char_1;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = char_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
	    }
	}
	else
	    twrite_percent_encoded_wide_character(char_1);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	if (ISVREF(uri,(SI_Long)4L))
	    tformat(2,string_constant_1,ISVREF(uri,(SI_Long)4L));
    }
    twrite_uri_path(ISVREF(uri,(SI_Long)5L));
    if (ISVREF(uri,(SI_Long)6L)) {
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)1L));
	s = ISVREF(uri,(SI_Long)6L);
	ab_loop_bind_ = IFIX(text_string_length(s));
	i = (SI_Long)0L;
	char_1 = Nil;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
	temp = char_1;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L)))) {
	    gensymed_symbol = char_1;
	    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) :
			 Qnil;
	    if (temp);
	    else
		temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) :
			 Qnil;
	}
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 45:
	      case 46:
	      case 95:
	      case 126:
	      case 33:
	      case 36:
	      case 38:
	      case 39:
	      case 40:
	      case 41:
	      case 42:
	      case 43:
	      case 44:
	      case 59:
	      case 61:
	      case 58:
	      case 64:
	      case 47:
	      case 63:
		temp = T;
		break;
	      default:
		gensymed_symbol = char_1;
		temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) 
			: Qnil;
		if (temp);
		else
		    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : 
			    Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : 
			    Nil) : Qnil;
		break;
	    }
	if (temp) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = char_1;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = char_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
	    }
	}
	else
	    twrite_percent_encoded_wide_character(char_1);
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    if (ISVREF(uri,(SI_Long)7L)) {
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)1L));
	s = ISVREF(uri,(SI_Long)7L);
	ab_loop_bind_ = IFIX(text_string_length(s));
	i = (SI_Long)0L;
	char_1 = Nil;
      next_loop_3:
	if (i >= ab_loop_bind_)
	    goto end_loop_3;
	char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
	temp = char_1;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L)))) {
	    gensymed_symbol = char_1;
	    temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) :
			 Qnil;
	    if (temp);
	    else
		temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) :
			 Qnil;
	}
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 45:
	      case 46:
	      case 95:
	      case 126:
	      case 33:
	      case 36:
	      case 38:
	      case 39:
	      case 40:
	      case 41:
	      case 42:
	      case 43:
	      case 44:
	      case 59:
	      case 61:
	      case 58:
	      case 64:
	      case 47:
	      case 63:
		temp = T;
		break;
	      default:
		gensymed_symbol = char_1;
		temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) 
			: Qnil;
		if (temp);
		else
		    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : 
			    Nil) : Qnil;
		if (temp);
		else
		    temp = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : 
			    Nil) : Qnil;
		break;
	    }
	if (temp) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = char_1;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = char_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
	    }
	}
	else
	    twrite_percent_encoded_wide_character(char_1);
	i = i + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
    }
    return VALUES_1(Nil);
}

/* WRITE-URI-FROM-SLOT */
Object write_uri_from_slot(uri,gensymed_symbol)
    Object uri, gensymed_symbol;
{
    Object write_strings_parsably_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(242,11);
    if (uri) {
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  result = twrite_general_string(uri);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* TWRITE-URLENCODED-TEXT-STRING */
Object twrite_urlencoded_text_string(string_1)
    Object string_1;
{
    Object char_1, temp, schar_arg_2, schar_new_value, temp_1, gensymed_symbol;
    Object thing_1;
    SI_Long ab_loop_bind_, i;
    char thing;

    x_note_fn_call(242,12);
    ab_loop_bind_ = IFIX(text_string_length(string_1));
    i = (SI_Long)0L;
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
    if (IFIX(char_1) == (SI_Long)32L) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = '+';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = '+';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    else {
	temp_1 = char_1;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    gensymed_symbol = char_1;
	    temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		    (IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) : Qnil;
	    if (temp_1);
	    else
		temp_1 = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) :
			 Qnil;
	    if (temp_1);
	    else
		temp_1 = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)57L ? T : Nil) :
			 Qnil;
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 45:
	      case 46:
	      case 95:
	      case 126:
	      case 33:
	      case 36:
	      case 38:
	      case 39:
	      case 40:
	      case 41:
	      case 42:
	      case 43:
	      case 44:
	      case 59:
	      case 61:
		temp_1 = T;
		break;
	      default:
		gensymed_symbol = char_1;
		temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			(IFIX(gensymed_symbol) <= (SI_Long)122L ? T : Nil) 
			: Qnil;
		if (temp_1);
		else
		    temp_1 = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)90L ? T : 
			    Nil) : Qnil;
		if (temp_1);
		else
		    temp_1 = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
			    (IFIX(gensymed_symbol) <= (SI_Long)57L ? T : 
			    Nil) : Qnil;
		break;
	    }
	if (temp_1) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = char_1;
		twrite_wide_character(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = char_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	else if (IFIX(char_1) == (SI_Long)8232L) {
	    twrite_percent_encoded_wide_character(FIX((SI_Long)13L));
	    twrite_percent_encoded_wide_character(FIX((SI_Long)10L));
	}
	else
	    twrite_percent_encoded_wide_character(char_1);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* URLENCODE-WWW-FORM */
Object urlencode_www_form(data_set)
    Object data_set;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object first_1, gensymed_symbol, held_vector, name, attribute_value, value;
    Object temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, next_index;
    SI_Long length_2, gensymed_symbol_1;
    char thing;
    Declare_special(5);

    x_note_fn_call(242,13);
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
	      first_1 = T;
	      gensymed_symbol = data_set;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_2 = (SI_Long)0L;
	      name = Nil;
	      attribute_value = Nil;
	      value = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop:
	      if (next_index >= length_2)
		  goto end_loop;
	      name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      gensymed_symbol_1 = next_index + (SI_Long)1L;
	      attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		      (SI_Long)1023L);
	      value = validate_item_or_evaluation_value(attribute_value,
		      Nil,Nil);
	      next_index = next_index + (SI_Long)2L;
	      if ( !TRUEP(first_1)) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = '&';
		      twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = '&';
		      schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
	      }
	      twrite_urlencoded_text_string(symbol_name_text_string(name));
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = '=';
		  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = '=';
		  schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      twrite_urlencoded_text_string(value);
	      first_1 = Nil;
	      goto next_loop;
	    end_loop:;
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* TWRITE-CRLF */
Object twrite_crlf()
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(242,14);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)13L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)13L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)10L;
	return twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)10L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
	return VALUES_1(Fill_pointer_for_current_gensym_string);
    }
}

static Object string_constant_2;   /* "~a~a" */

static Object string_constant_3;   /* "0" */

static Object string_constant_4;   /* "" */

/* TWRITE-TWO-DIGIT-FIXNUM */
Object twrite_two_digit_fixnum(n_1)
    Object n_1;
{
    x_note_fn_call(242,15);
    tformat(3,string_constant_2,IFIX(n_1) < (SI_Long)10L ? 
	    string_constant_3 : string_constant_4,n_1);
    return VALUES_1(Nil);
}

static Object string_constant_5;   /* "~a, " */

static Object string_constant_6;   /* " ~a ~a " */

static Object string_constant_7;   /* ":" */

static Object string_constant_8;   /* " GMT" */

/* TWRITE-HTTP-DATE */
Object twrite_http_date()
{
    Object adjustment_in_hours, gmt_time_in_seconds, second_1, minute, hour;
    Object date, month, year, day;
    SI_Long daylight_saving_zero;
    double local_time_in_seconds;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(242,16);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	local_time_in_seconds = g2ext_unix_time_as_float();
	daylight_saving_zero = g2ext_time_zone((SI_Long)1L);
	adjustment_in_hours = daylight_saving_zero != (SI_Long)0L ? 
		FIXNUM_SUB1(time_zone_in_hours()) : time_zone_in_hours();
	gmt_time_in_seconds = 
		add(DOUBLE_TO_DOUBLE_FLOAT(local_time_in_seconds),timesn(3,
		FIX((SI_Long)60L),FIX((SI_Long)60L),adjustment_in_hours));
	result = gensym_decode_unix_time(gmt_time_in_seconds);
	MVS_7(result,second_1,minute,hour,date,month,year,day);
	tformat(2,string_constant_5,select_day_of_week_string(day));
	twrite_two_digit_fixnum(date);
	tformat(3,string_constant_6,select_month_string(month),year);
	twrite_two_digit_fixnum(hour);
	tformat(1,string_constant_7);
	twrite_two_digit_fixnum(minute);
	tformat(1,string_constant_7);
	twrite_two_digit_fixnum(second_1);
	tformat(1,string_constant_8);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object string_constant_9;   /* "Unknown Status Code" */

static Object string_constant_10;  /* "Continue" */

static Object string_constant_11;  /* "Switching Protocols" */

static Object string_constant_12;  /* "OK" */

static Object string_constant_13;  /* "Created" */

static Object string_constant_14;  /* "Accepted" */

static Object string_constant_15;  /* "Non-Authoritative Information" */

static Object string_constant_16;  /* "No Content" */

static Object string_constant_17;  /* "Reset Content" */

static Object string_constant_18;  /* "Partial Content" */

static Object string_constant_19;  /* "Multiple Choices" */

static Object string_constant_20;  /* "Moved Permanently" */

static Object string_constant_21;  /* "Found" */

static Object string_constant_22;  /* "See Other" */

static Object string_constant_23;  /* "Not Modified" */

static Object string_constant_24;  /* "Use Proxy" */

static Object string_constant_25;  /* "Temporary Redirect" */

static Object string_constant_26;  /* "Bad Request" */

static Object string_constant_27;  /* "Unauthorized" */

static Object string_constant_28;  /* "Payment Required" */

static Object string_constant_29;  /* "Forbidden" */

static Object string_constant_30;  /* "Not Found" */

static Object string_constant_31;  /* "Method Not Allowed" */

static Object string_constant_32;  /* "Not Acceptable" */

static Object string_constant_33;  /* "Proxy Authentication Required" */

static Object string_constant_34;  /* "Request Time-out" */

static Object string_constant_35;  /* "Conflict" */

static Object string_constant_36;  /* "Gone" */

static Object string_constant_37;  /* "Length Required" */

static Object string_constant_38;  /* "Precondition Failed" */

static Object string_constant_39;  /* "Request Entity Too Large" */

static Object string_constant_40;  /* "Request-URI Too Large" */

static Object string_constant_41;  /* "Unsupported Media Type" */

static Object string_constant_42;  /* "Requested range not satisfiable" */

static Object string_constant_43;  /* "Expectation Failed" */

static Object string_constant_44;  /* "Internal Server Error" */

static Object string_constant_45;  /* "Not Implemented" */

static Object string_constant_46;  /* "Bad Gateway" */

static Object string_constant_47;  /* "Service Unavailable" */

static Object string_constant_48;  /* "Gateway Time-out" */

static Object string_constant_49;  /* "HTTP Version not supported" */

/* REASON-PHRASE-FOR-HTTP-STATUS-CODE */
Object reason_phrase_for_http_status_code(code)
    Object code;
{
    Object temp;

    x_note_fn_call(242,17);
    temp = code;
    if ( !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)32767L))))
	temp = string_constant_9;
    else
	switch (INTEGER_TO_SHORT(temp)) {
	  case 100:
	    temp = string_constant_10;
	    break;
	  case 101:
	    temp = string_constant_11;
	    break;
	  case 200:
	    temp = string_constant_12;
	    break;
	  case 201:
	    temp = string_constant_13;
	    break;
	  case 202:
	    temp = string_constant_14;
	    break;
	  case 203:
	    temp = string_constant_15;
	    break;
	  case 204:
	    temp = string_constant_16;
	    break;
	  case 205:
	    temp = string_constant_17;
	    break;
	  case 206:
	    temp = string_constant_18;
	    break;
	  case 300:
	    temp = string_constant_19;
	    break;
	  case 301:
	    temp = string_constant_20;
	    break;
	  case 302:
	    temp = string_constant_21;
	    break;
	  case 303:
	    temp = string_constant_22;
	    break;
	  case 304:
	    temp = string_constant_23;
	    break;
	  case 305:
	    temp = string_constant_24;
	    break;
	  case 307:
	    temp = string_constant_25;
	    break;
	  case 400:
	    temp = string_constant_26;
	    break;
	  case 401:
	    temp = string_constant_27;
	    break;
	  case 402:
	    temp = string_constant_28;
	    break;
	  case 403:
	    temp = string_constant_29;
	    break;
	  case 404:
	    temp = string_constant_30;
	    break;
	  case 405:
	    temp = string_constant_31;
	    break;
	  case 406:
	    temp = string_constant_32;
	    break;
	  case 407:
	    temp = string_constant_33;
	    break;
	  case 408:
	    temp = string_constant_34;
	    break;
	  case 409:
	    temp = string_constant_35;
	    break;
	  case 410:
	    temp = string_constant_36;
	    break;
	  case 411:
	    temp = string_constant_37;
	    break;
	  case 412:
	    temp = string_constant_38;
	    break;
	  case 413:
	    temp = string_constant_39;
	    break;
	  case 414:
	    temp = string_constant_40;
	    break;
	  case 415:
	    temp = string_constant_41;
	    break;
	  case 416:
	    temp = string_constant_42;
	    break;
	  case 417:
	    temp = string_constant_43;
	    break;
	  case 500:
	    temp = string_constant_44;
	    break;
	  case 501:
	    temp = string_constant_45;
	    break;
	  case 502:
	    temp = string_constant_46;
	    break;
	  case 503:
	    temp = string_constant_47;
	    break;
	  case 504:
	    temp = string_constant_48;
	    break;
	  case 505:
	    temp = string_constant_49;
	    break;
	  default:
	    temp = string_constant_9;
	    break;
	}
    return VALUES_1(temp);
}

Object Http_request_type = UNBOUND;

static Object Qab_method;          /* method */

static Object Qheaders;            /* headers */

static Object Qentity;             /* entity */

static Object Qab_structure;       /* structure */

static Object Qpost;               /* post */

static Object string_constant_50;  /* "application/x-www-form-urlencoded" */

static Object Qscheme;             /* scheme */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qhost;               /* host */

static Object Qport;               /* port */

static Object Qmessage;            /* message */

static Object string_constant_51;  /* "~a " */

static Object string_constant_52;  /* "?~a" */

static Object string_constant_53;  /* " HTTP/1.1" */

static Object string_constant_54;  /* "Connection: close" */

static Object string_constant_55;  /* "Host: ~a" */

static Object string_constant_56;  /* ":~a" */

static Object string_constant_57;  /* "Content-Length: ~a" */

static Object string_constant_58;  /* "Content-Type: ~a" */

static Object string_constant_59;  /* "~a: ~a" */

/* FORMAT-HTTP-REQUEST */
Object format_http_request(address,request)
    Object address, request;
{
    Object method, headers_qm, entity_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object s, char_1, temp_1, gensymed_symbol, thing, temp_2, temp_3;
    Object schar_new_value, query_qm, content_type_qm, message_body_qm;
    Object item_or_value, x2, gensymed_symbol_2, held_vector, name;
    Object attribute_value, value;
    SI_Long bv16_length, temp, aref_new_value, length_1, ab_loop_bind_, i;
    SI_Long gensymed_symbol_1, next_index, length_2;
    char temp_4;
    Declare_special(5);

    x_note_fn_call(242,18);
    check_type_or_stack_error(2,request,Http_request_type);
    method = estructure_slot(request,Qab_method,Qget);
    headers_qm = estructure_slot(request,Qheaders,Nil);
    entity_qm = estructure_slot(request,Qentity,Nil);
    if (ISVREF(address,(SI_Long)6L)) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		  s = ISVREF(address,(SI_Long)6L);
		  ab_loop_bind_ = IFIX(text_string_length(s));
		  i = (SI_Long)0L;
		  char_1 = Nil;
		next_loop:
		  if (i >= ab_loop_bind_)
		      goto end_loop;
		  char_1 = FIX(UBYTE_16_ISAREF_1(s,i));
		  temp_1 = char_1;
		  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			  FIXNUM_LE(temp_1,FIX((SI_Long)127L)))) {
		      gensymed_symbol = char_1;
		      temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
			      (IFIX(gensymed_symbol) <= (SI_Long)122L ? T :
			       Nil) : Qnil;
		      if (temp_1);
		      else
			  temp_1 = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
				  (IFIX(gensymed_symbol) <= (SI_Long)90L ? 
				  T : Nil) : Qnil;
		      if (temp_1);
		      else
			  temp_1 = (SI_Long)48L <= IFIX(gensymed_symbol) ? 
				  (IFIX(gensymed_symbol) <= (SI_Long)57L ? 
				  T : Nil) : Qnil;
		  }
		  else
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 45:
			case 46:
			case 95:
			case 126:
			case 33:
			case 36:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 59:
			case 61:
			  temp_1 = T;
			  break;
			default:
			  gensymed_symbol = char_1;
			  temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
				  (IFIX(gensymed_symbol) <= (SI_Long)122L ?
				   T : Nil) : Qnil;
			  if (temp_1);
			  else
			      temp_1 = (SI_Long)65L <= 
				      IFIX(gensymed_symbol) ? 
				      (IFIX(gensymed_symbol) <= 
				      (SI_Long)90L ? T : Nil) : Qnil;
			  if (temp_1);
			  else
			      temp_1 = (SI_Long)48L <= 
				      IFIX(gensymed_symbol) ? 
				      (IFIX(gensymed_symbol) <= 
				      (SI_Long)57L ? T : Nil) : Qnil;
			  break;
		      }
		  if (temp_1) {
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
			  temp_2 = Current_gensym_string;
			  temp_3 = Fill_pointer_for_current_gensym_string;
			  thing = char_1;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp_2,temp_3,schar_new_value);
			  temp_2 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_2;
		      }
		  }
		  else
		      twrite_percent_encoded_wide_character(char_1);
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  query_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	query_qm = Nil;
    content_type_qm = Nil;
    message_body_qm = Nil;
    if (EQ(method,Qget)) {
	if (CONSP(entity_qm) && EQ(M_CDR(entity_qm),Qab_structure)) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(query_qm) != (SI_Long)0L)
		reclaim_wide_string(query_qm);
	    query_qm = urlencode_www_form(entity_qm);
	}
    }
    else if (EQ(method,Qpost)) {
	if (CONSP(entity_qm) && EQ(M_CDR(entity_qm),Qab_structure)) {
	    message_body_qm = urlencode_www_form(entity_qm);
	    content_type_qm = string_constant_50;
	}
	else {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
		      (SI_Long)3L));
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      temp = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	      temp = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		      if (entity_qm)
			  twrite(entity_qm);
		      message_body_qm = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,temp) = FIX((SI_Long)1L);
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_2,temp) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qscheme;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)1L)) = Qscheme;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(address,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_2 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(address,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_2,FIX((SI_Long)2L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhost;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)3L)) = Qhost;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = copy_as_wide_string(ISVREF(address,(SI_Long)3L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_2 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = copy_as_wide_string(ISVREF(address,(SI_Long)3L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_2,FIX((SI_Long)4L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qport;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)5L)) = Qport;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(address,(SI_Long)4L);
	if (item_or_value);
	else
	    item_or_value = FIX((SI_Long)80L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_2 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(address,(SI_Long)4L);
	if (item_or_value);
	else
	    item_or_value = FIX((SI_Long)80L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_2,FIX((SI_Long)6L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qmessage;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)7L)) = Qmessage;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		  tformat(2,string_constant_51,method);
		  if (uri_path_is_empty_p(address))
		      twrite_beginning_of_wide_string(array_constant_5,
			      FIX((SI_Long)1L));
		  else
		      twrite_uri_path(ISVREF(address,(SI_Long)5L));
		  if (query_qm) {
		      tformat(2,string_constant_52,query_qm);
		      reclaim_text_string(query_qm);
		  }
		  tformat(1,string_constant_53);
		  twrite_crlf();
		  tformat(1,string_constant_54);
		  twrite_crlf();
		  tformat(2,string_constant_55,ISVREF(address,(SI_Long)3L));
		  if (ISVREF(address,(SI_Long)4L))
		      tformat(2,string_constant_56,ISVREF(address,
			      (SI_Long)4L));
		  twrite_crlf();
		  if (message_body_qm) {
		      tformat(2,string_constant_57,
			      text_string_length(message_body_qm));
		      twrite_crlf();
		  }
		  if (content_type_qm) {
		      tformat(2,string_constant_58,content_type_qm);
		      twrite_crlf();
		  }
		  if (headers_qm) {
		      gensymed_symbol_2 = headers_qm;
		      held_vector = Nil;
		      next_index = (SI_Long)1L;
		      length_2 = (SI_Long)0L;
		      name = Nil;
		      attribute_value = Nil;
		      value = Nil;
		      held_vector = M_CAR(gensymed_symbol_2);
		      length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		    next_loop_1:
		      if (next_index >= length_2)
			  goto end_loop_1;
		      name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			      Maximum_in_place_array_size) ? 
			      ISVREF(held_vector,next_index + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(held_vector,(next_index >>  -  
			      - (SI_Long)10L) + (SI_Long)2L),next_index & 
			      (SI_Long)1023L);
		      gensymed_symbol_1 = next_index + (SI_Long)1L;
		      attribute_value = FIXNUM_LE(ISVREF(held_vector,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(held_vector,gensymed_symbol_1 + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      gensymed_symbol_1 & (SI_Long)1023L);
		      value = 
			      validate_item_or_evaluation_value(attribute_value,
			      Nil,Nil);
		      next_index = next_index + (SI_Long)2L;
		      tformat(3,string_constant_59,name,value);
		      twrite_crlf();
		      goto next_loop_1;
		    end_loop_1:;
		  }
		  twrite_crlf();
		  if (message_body_qm) {
		      twrite(message_body_qm);
		      reclaim_text_string(message_body_qm);
		  }
		  item_or_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_2 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		  tformat(2,string_constant_51,method);
		  if (uri_path_is_empty_p(address))
		      twrite_beginning_of_wide_string(array_constant_5,
			      FIX((SI_Long)1L));
		  else
		      twrite_uri_path(ISVREF(address,(SI_Long)5L));
		  if (query_qm) {
		      tformat(2,string_constant_52,query_qm);
		      reclaim_text_string(query_qm);
		  }
		  tformat(1,string_constant_53);
		  twrite_crlf();
		  tformat(1,string_constant_54);
		  twrite_crlf();
		  tformat(2,string_constant_55,ISVREF(address,(SI_Long)3L));
		  if (ISVREF(address,(SI_Long)4L))
		      tformat(2,string_constant_56,ISVREF(address,
			      (SI_Long)4L));
		  twrite_crlf();
		  if (message_body_qm) {
		      tformat(2,string_constant_57,
			      text_string_length(message_body_qm));
		      twrite_crlf();
		  }
		  if (content_type_qm) {
		      tformat(2,string_constant_58,content_type_qm);
		      twrite_crlf();
		  }
		  if (headers_qm) {
		      gensymed_symbol_2 = headers_qm;
		      held_vector = Nil;
		      next_index = (SI_Long)1L;
		      length_2 = (SI_Long)0L;
		      name = Nil;
		      attribute_value = Nil;
		      value = Nil;
		      held_vector = M_CAR(gensymed_symbol_2);
		      length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		    next_loop_2:
		      if (next_index >= length_2)
			  goto end_loop_2;
		      name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			      Maximum_in_place_array_size) ? 
			      ISVREF(held_vector,next_index + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(held_vector,(next_index >>  -  
			      - (SI_Long)10L) + (SI_Long)2L),next_index & 
			      (SI_Long)1023L);
		      gensymed_symbol_1 = next_index + (SI_Long)1L;
		      attribute_value = FIXNUM_LE(ISVREF(held_vector,
			      (SI_Long)1L),Maximum_in_place_array_size) ? 
			      ISVREF(held_vector,gensymed_symbol_1 + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L),
			      gensymed_symbol_1 & (SI_Long)1023L);
		      value = 
			      validate_item_or_evaluation_value(attribute_value,
			      Nil,Nil);
		      next_index = next_index + (SI_Long)2L;
		      tformat(3,string_constant_59,name,value);
		      twrite_crlf();
		      goto next_loop_2;
		    end_loop_2:;
		  }
		  twrite_crlf();
		  if (message_body_qm) {
		      twrite(message_body_qm);
		      reclaim_text_string(message_body_qm);
		  }
		  item_or_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_2,FIX((SI_Long)8L)) = temp_3;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

Object Http_response_type = UNBOUND;

static Object Qstatus_code;        /* status-code */

static Object Qreason_phrase;      /* reason-phrase */

static Object string_constant_60;  /* "HTTP/1.1 ~a ~a" */

static Object string_constant_61;  /* "Date: " */

/* G2-FORMAT-HTTP-RESPONSE */
Object g2_format_http_response(response_as_evaluation_value)
    Object response_as_evaluation_value;
{
    Object response, value_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object status_code_qm, status_code, reason_phrase_qm, reason_phrase;
    Object headers_qm, entity_qm, gensymed_symbol, held_vector, name;
    Object attribute_value, value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, next_index;
    SI_Long length_2, gensymed_symbol_1;
    Declare_special(5);

    x_note_fn_call(242,19);
    response = IDENTITY(response_as_evaluation_value);
    value_1 = Nil;
    check_type_or_stack_error(2,response,Http_response_type);
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
	      status_code_qm = estructure_slot(response,Qstatus_code,Nil);
	      status_code = status_code_qm ? status_code_qm : 
		      FIX((SI_Long)200L);
	      reason_phrase_qm = estructure_slot(response,Qreason_phrase,Nil);
	      reason_phrase = reason_phrase_qm ? reason_phrase_qm : 
		      reason_phrase_for_http_status_code(status_code);
	      headers_qm = estructure_slot(response,Qheaders,Nil);
	      entity_qm = estructure_slot(response,Qentity,Nil);
	      tformat(3,string_constant_60,status_code,reason_phrase);
	      twrite_crlf();
	      tformat(1,string_constant_54);
	      twrite_crlf();
	      tformat(1,string_constant_61);
	      twrite_http_date();
	      twrite_crlf();
	      if (headers_qm) {
		  gensymed_symbol = headers_qm;
		  held_vector = Nil;
		  next_index = (SI_Long)1L;
		  length_2 = (SI_Long)0L;
		  name = Nil;
		  attribute_value = Nil;
		  value = Nil;
		  held_vector = M_CAR(gensymed_symbol);
		  length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		next_loop:
		  if (next_index >= length_2)
		      goto end_loop;
		  name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			  Maximum_in_place_array_size) ? 
			  ISVREF(held_vector,next_index + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),next_index & 
			  (SI_Long)1023L);
		  gensymed_symbol_1 = next_index + (SI_Long)1L;
		  attribute_value = FIXNUM_LE(ISVREF(held_vector,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(held_vector,gensymed_symbol_1 + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  
			  -  - (SI_Long)10L) + (SI_Long)2L),
			  gensymed_symbol_1 & (SI_Long)1023L);
		  value = 
			  validate_item_or_evaluation_value(attribute_value,
			  Nil,Nil);
		  next_index = next_index + (SI_Long)2L;
		  tformat(3,string_constant_59,name,value);
		  twrite_crlf();
		  goto next_loop;
		end_loop:;
	      }
	      twrite_crlf();
	      if (entity_qm)
		  twrite(entity_qm);
	      reclaim_evaluation_structure(response);
	      value_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    IDENTITY(response_as_evaluation_value);
    return VALUES_1(value_1);
}

/* PARSE-HTTP-REQUEST-LINE */
Object parse_http_request_line(line)
    Object line;
{
    Object sp1_qm, method, sp2_qm, uri, version, temp;

    x_note_fn_call(242,20);
    sp1_qm = position_in_text_string(FIX((SI_Long)32L),line);
    method = text_string_substring(line,FIX((SI_Long)0L),sp1_qm);
    sp2_qm = sp1_qm ? position_in_text_string_tail(FIX((SI_Long)32L),line,
	    FIXNUM_ADD1(sp1_qm)) : Nil;
    uri = sp1_qm ? text_string_substring(line,FIXNUM_ADD1(sp1_qm),sp2_qm) :
	     copy_text_string(string_constant_4);
    version = sp2_qm ? text_string_substring(line,FIXNUM_ADD1(sp2_qm),Nil) 
	    : copy_text_string(string_constant_4);
    upcase_text_string_in_place(method);
    temp = intern_text_string(1,method);
    return VALUES_3(temp,uri,version);
}

/* PARSE-HTTP-STATUS-LINE */
Object parse_http_status_line(line)
    Object line;
{
    Object sp1_qm, version, sp2_qm, temp, temp_1, status_code, reason_phrase;

    x_note_fn_call(242,21);
    sp1_qm = position_in_text_string(FIX((SI_Long)32L),line);
    version = text_string_substring(line,FIX((SI_Long)0L),sp1_qm);
    sp2_qm = sp1_qm ? position_in_text_string_tail(FIX((SI_Long)32L),line,
	    FIXNUM_ADD1(sp1_qm)) : Nil;
    if (sp1_qm) {
	temp = FIXNUM_ADD1(sp1_qm);
	temp_1 = sp2_qm;
	if (temp_1);
	else
	    temp_1 = text_string_length(line);
	status_code = read_positive_fixnum_from_string(line,temp,temp_1);
    }
    else
	status_code = Nil;
    if (status_code);
    else
	status_code = FIX((SI_Long)-1L);
    reason_phrase = sp2_qm ? text_string_substring(line,
	    FIXNUM_ADD1(sp2_qm),Nil) : copy_text_string(string_constant_4);
    return VALUES_3(version,status_code,reason_phrase);
}

static Object list_constant;       /* # */

static Object string_constant_62;  /* "~a ~a" */

/* PARSE-HTTP-MESSAGE-HEADER */
Object parse_http_message_header(line,headers)
    Object line, headers;
{
    Object left, right, car_new_value, separator, field_name, field_value;
    Object temp;
    SI_Long first_char;

    x_note_fn_call(242,22);
    first_char = UBYTE_16_ISAREF_1(line,(SI_Long)0L);
    if (first_char == (SI_Long)32L || first_char == (SI_Long)9L) {
	if (headers) {
	    left = CAR(headers);
	    right = text_string_trim(list_constant,line);
	    car_new_value = tformat_text_string(3,string_constant_62,left,
		    right);
	    M_CAR(headers) = car_new_value;
	    reclaim_text_string(left);
	    reclaim_text_string(right);
	}
	return VALUES_1(headers);
    }
    separator = position_in_text_string(FIX((SI_Long)58L),line);
    if ( !TRUEP(separator))
	return VALUES_1(headers);
    field_name = text_string_substring(line,FIX((SI_Long)0L),separator);
    field_value = text_string_substring(line,FIXNUM_ADD1(separator),Nil);
    upcase_text_string_in_place(field_name);
    temp = text_string_trim(list_constant,field_value);
    reclaim_text_string(field_value);
    return VALUES_1(nconc2(eval_list_2(temp,intern_text_string(1,
	    field_name)),headers));
}

/* PARSE-HTTP-MESSAGE-HEADERS */
Object parse_http_message_headers(header_lines)
    Object header_lines;
{
    Object line, headers;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(242,23);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(header_lines),(SI_Long)1L)));
    line = Nil;
    headers = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    line = evaluation_sequence_aref(header_lines,FIX(i));
    headers = parse_http_message_header(line,headers);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return allocate_evaluation_structure(nreverse(headers));
    return VALUES_1(Qnil);
}

static Object Qcontent_length;     /* content-length */

/* HTTP-MESSAGE-LENGTH */
Object http_message_length(headers)
    Object headers;
{
    Object length_text_qm, length_1, temp;

    x_note_fn_call(242,24);
    length_text_qm = estructure_slot(headers,Qcontent_length,Nil);
    if (length_text_qm) {
	length_1 = length_text_qm;
	temp = read_positive_fixnum_from_string(length_1,FIX((SI_Long)0L),
		text_string_length(length_1));
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)-1L));
}

static Object Qrequest_uri;        /* request-uri */

static Object Qhttp_version;       /* http-version */

static Object Qpath;               /* path */

static Object Qquery;              /* query */

static Object Qtransfer_length;    /* transfer-length */

/* G2-PARSE-HTTP-REQUEST */
Object g2_parse_http_request(start_line_as_evaluation_value,
	    header_lines_as_evaluation_value)
    Object start_line_as_evaluation_value, header_lines_as_evaluation_value;
{
    Object start_line, header_lines, value_1, method, request_uri;
    Object http_version, uri, headers, gensymed_symbol, gensymed_symbol_1;
    Object segment, temp, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, car_new_value;
    Object result;

    x_note_fn_call(242,25);
    start_line = start_line_as_evaluation_value;
    header_lines = IDENTITY(header_lines_as_evaluation_value);
    value_1 = Nil;
    result = parse_http_request_line(start_line);
    MVS_3(result,method,request_uri,http_version);
    uri = parse_uri(request_uri);
    headers = parse_http_message_headers(header_lines);
    reclaim_evaluation_sequence(header_lines);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qab_method;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = method;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qrequest_uri;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = request_uri;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qhttp_version;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = http_version;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qpath;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    segment = Nil;
    temp = ISVREF(uri,(SI_Long)5L);
    ab_loop_list_ = CDR(temp);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    segment = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(copy_as_wide_string(segment),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    car_new_value = allocate_evaluation_sequence(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    temp = ISVREF(uri,(SI_Long)6L) ? eval_list_2(Qquery,
	    copy_as_wide_string(ISVREF(uri,(SI_Long)6L))) : Nil;
    reclaim_uri_reference_1(uri);
    value_1 = allocate_evaluation_structure(nconc2(gensymed_symbol,
	    nconc2(temp,eval_list_4(Qheaders,headers,Qtransfer_length,
	    http_message_length(headers)))));
    reclaim_text_string(start_line_as_evaluation_value);
    IDENTITY(header_lines_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* G2-PARSE-HTTP-RESPONSE */
Object g2_parse_http_response(start_line_as_evaluation_value,
	    header_lines_as_evaluation_value)
    Object start_line_as_evaluation_value, header_lines_as_evaluation_value;
{
    Object start_line, header_lines, value_1, version, code, reason, headers;
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Object result;

    x_note_fn_call(242,26);
    start_line = start_line_as_evaluation_value;
    header_lines = IDENTITY(header_lines_as_evaluation_value);
    value_1 = Nil;
    result = parse_http_status_line(start_line);
    MVS_3(result,version,code,reason);
    headers = parse_http_message_headers(header_lines);
    reclaim_evaluation_sequence(header_lines);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
	    (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qhttp_version;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qhttp_version;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = version;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = version;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qstatus_code;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qstatus_code;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = code;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = code;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qreason_phrase;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qreason_phrase;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = reason;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = reason;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qheaders;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qheaders;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = headers;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = headers;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qtransfer_length;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qtransfer_length;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = http_message_length(headers);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = http_message_length(headers);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
    }
    value_1 = eval_cons_1(gensymed_symbol,Qab_structure);
    reclaim_text_string(start_line_as_evaluation_value);
    IDENTITY(header_lines_as_evaluation_value);
    temp_2 = IDENTITY(value_1);
    return VALUES_1(temp_2);
}

Object Most_positive_fixnum_floor_16 = UNBOUND;

/* READ-POSITIVE-HEXADECIMAL-FIXNUM-FROM-STRING */
Object read_positive_hexadecimal_fixnum_from_string(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object num, digit;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(242,27);
    num = FIX((SI_Long)0L);
    i = IFIX(start);
    ab_loop_bind_ = IFIX(end_1);
    digit = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    digit = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,i)),
	    FIX((SI_Long)16L));
    if ( !TRUEP(digit))
	goto end_loop;
    if (FIXNUM_GT(num,Most_positive_fixnum_floor_16))
	return VALUES_2(Nil,FIX(i));
    num = FIX(IFIX(num) * (SI_Long)16L + IFIX(digit));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_2(num,FIX(i));
    return VALUES_1(Qnil);
}

static Object string_constant_63;  /* "HTTP chunk size is too large in header: ~a" */

static Object string_constant_64;  /* "Failed to parse HTTP chunk header: ~a" */

/* G2-PARSE-HTTP-CHUNK-HEADER */
Object g2_parse_http_chunk_header(header_as_evaluation_value)
    Object header_as_evaluation_value;
{
    Object header, value_1, value_2, len, size, i, top_of_stack, message_1;
    Object temp, temp_1;
    Object result;

    x_note_fn_call(242,28);
    header = header_as_evaluation_value;
    value_1 = Nil;
    value_2 = Nil;
    len = text_string_length(header);
    result = read_positive_hexadecimal_fixnum_from_string(header,
	    FIX((SI_Long)0L),len);
    MVS_2(result,size,i);
    if ( !TRUEP(size)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_63,
		header);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !(FIXNUM_EQ(i,len) || IFIX(i) > (SI_Long)0L && 
	    UBYTE_16_ISAREF_1(header,IFIX(i)) == (SI_Long)59L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_64,
		header);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    temp = allocate_evaluation_structure(Nil);
    result = VALUES_2(size,temp);
    MVS_2(result,value_1,value_2);
    reclaim_text_string(header_as_evaluation_value);
    temp_1 = value_1;
    temp = IDENTITY(value_2);
    return VALUES_2(temp_1,temp);
}

static Object Qnone;               /* none */

/* WRITE-HTTP-SERVER-PORT-FROM-SLOT */
Object write_http_server_port_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(242,29);
    temp = value;
    if (temp);
    else
	temp = Qnone;
    return twrite(temp);
}

/* HTTP-SERVER-PORT-EVALUATION-GETTER */
Object http_server_port_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(242,30);
    GENSYM_RETURN_ONE(slot_value ? slot_value : Nil);
    return VALUES_1(Nil);
}

static Object Qhttp_server;        /* http-server */

static Object Qhttp_server_port;   /* http-server-port */

static Object Qhttp_server_listener;  /* http-server-listener */

static Object Qhttp_server_invocation;  /* http-server-invocation */

/* NOTIFY-HTTP-SERVERS-OF-G2-RESET */
Object notify_http_servers_of_g2_reset()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, server;
    char temp;
    Declare_special(1);

    x_note_fn_call(242,31);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    server = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qhttp_server);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      server = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      change_slot_value(3,server,Qhttp_server_port,Nil);
      change_slot_value(3,server,Qhttp_server_listener,Nil);
      change_slot_value(3,server,Qhttp_server_invocation,Nil);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* G2-HTTP-LISTEN */
Object g2_http_listen(server_as_evaluation_value,port_as_evaluation_value,
	    socket_as_evaluation_value,invocation_as_evaluation_value)
    Object server_as_evaluation_value, port_as_evaluation_value;
    Object socket_as_evaluation_value, invocation_as_evaluation_value;
{
    Object server, port, socket_1, invocation;

    x_note_fn_call(242,32);
    server = IDENTITY(server_as_evaluation_value);
    port = port_as_evaluation_value;
    socket_1 = IDENTITY(socket_as_evaluation_value);
    invocation = IDENTITY(invocation_as_evaluation_value);
    change_slot_value(3,server,Qhttp_server_port,port);
    change_slot_value(3,server,Qhttp_server_listener,socket_1);
    change_slot_value(3,server,Qhttp_server_invocation,invocation);
    IDENTITY(server_as_evaluation_value);
    IDENTITY(socket_as_evaluation_value);
    IDENTITY(invocation_as_evaluation_value);
    return VALUES_0();
}

/* G2-SHUTDOWN-HTTP-SERVER */
Object g2_shutdown_http_server(server_as_evaluation_value)
    Object server_as_evaluation_value;
{
    Object server, value_1, value_2, temp, temp_1;
    Object result;

    x_note_fn_call(242,33);
    server = IDENTITY(server_as_evaluation_value);
    value_1 = Nil;
    value_2 = Nil;
    change_slot_value(3,server,Qhttp_server_port,Nil);
    temp = get_lookup_slot_value_given_default(server,
	    Qhttp_server_listener,Nil);
    temp_1 = get_lookup_slot_value_given_default(server,
	    Qhttp_server_invocation,Nil);
    result = VALUES_2(temp,temp_1);
    MVS_2(result,value_1,value_2);
    IDENTITY(server_as_evaluation_value);
    temp = IDENTITY(value_1);
    temp_1 = IDENTITY(value_2);
    return VALUES_2(temp,temp_1);
}

static Object Qhttp;               /* http */

static Object string_constant_65;  /* "URL has no scheme: ~a" */

static Object string_constant_66;  /* "Unknown URL scheme: ~a" */

/* G2-FORMAT-WEB-REQUEST */
Object g2_format_web_request(url_as_evaluation_value,
	    request_as_evaluation_value)
    Object url_as_evaluation_value, request_as_evaluation_value;
{
    Object url, request, value_1, address, temp, top_of_stack, message_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(242,34);
    SAVE_STACK();
    url = url_as_evaluation_value;
    request = IDENTITY(request_as_evaluation_value);
    value_1 = Nil;
    address = parse_uri(url);
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = ISVREF(address,(SI_Long)1L);
	if (EQ(temp,Qhttp))
	    temp = format_http_request(address,request);
	else if (EQ(temp,Qnil)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_65,url);
	    temp = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_66,ISVREF(address,(SI_Long)1L));
	    temp = raw_stack_error_named_error(top_of_stack,message_1);
	}
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    reclaim_uri_reference_1(address);
    reclaim_evaluation_structure(request);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    value_1 = result;
    reclaim_text_string(url_as_evaluation_value);
    IDENTITY(request_as_evaluation_value);
    temp = IDENTITY(value_1);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object Qtag_name;           /* tag-name */

static Object Qns_prefix;          /* ns-prefix */

static Object Qns_uri;             /* ns-uri */

static Object Qattributes;         /* attributes */

static Object Qchildren;           /* children */

/* MAKE-XML-ELEMENT-EVALUATION-VALUE */
Object make_xml_element_evaluation_value(tag_name,ns_prefix,ns_uri,
	    attributes,children)
    Object tag_name, ns_prefix, ns_uri, attributes, children;
{
    Object temp, temp_1, temp_2, temp_3;

    x_note_fn_call(242,35);
    temp = eval_list_2(Qtag_name,tag_name);
    temp_1 = ns_prefix ? eval_list_2(Qns_prefix,ns_prefix) : Nil;
    temp_2 = ns_uri ? eval_list_2(Qns_uri,ns_uri) : Nil;
    temp_3 = attributes ? eval_list_2(Qattributes,
	    allocate_evaluation_structure(attributes)) : Nil;
    temp_3 = allocate_evaluation_structure(nconc2(temp,nconc2(temp_1,
	    nconc2(temp_2,nconc2(temp_3,children ? eval_list_2(Qchildren,
	    allocate_evaluation_sequence(children)) : Nil)))));
    return VALUES_1(temp_3);
}

/* XML-EVALUATION-VALUE-P */
Object xml_evaluation_value_p(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,36);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L ? T : Nil;
    if (temp);
    else
	temp = xml_element_evaluation_value_p(value);
    return VALUES_1(temp);
}

/* EVALUATION-SEQUENCE-OF-XML-EVALUATION-VALUES-P */
Object evaluation_sequence_of_xml_evaluation_values_p(seq)
    Object seq;
{
    Object gensymed_symbol, held_vector, x, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(242,37);
    if (CONSP(seq) && EQ(M_CDR(seq),Qsequence)) {
	gensymed_symbol = seq;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	x = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	x = validated_elt;
	if ( !TRUEP(xml_evaluation_value_p(x))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-P */
Object xml_element_evaluation_value_p(value)
    Object value;
{
    Object thing, prefix, uri, attrs, children, temp_1;
    char temp;

    x_note_fn_call(242,38);
    if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	thing = xml_element_evaluation_value_name(value);
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	prefix = xml_element_evaluation_value_ns_prefix(value);
	temp =  !TRUEP(prefix);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	uri = xml_element_evaluation_value_ns_uri(value);
	temp =  !TRUEP(uri);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(uri) != (SI_Long)0L;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	attrs = xml_element_evaluation_value_attributes(value);
	temp =  !TRUEP(attrs);
	if (temp);
	else
	    temp = TRUEP(xml_attributes_evaluation_value_p(attrs));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	children = xml_element_evaluation_value_children(value);
	temp_1 =  !TRUEP(children) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = evaluation_sequence_of_xml_evaluation_values_p(children);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* XML-ATTRIBUTES-EVALUATION-VALUE-P */
Object xml_attributes_evaluation_value_p(attrs)
    Object attrs;
{
    Object gensymed_symbol, held_vector, name, attribute_value, value, temp;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(242,39);
    if (CONSP(attrs) && EQ(M_CDR(attrs),Qab_structure)) {
	gensymed_symbol = attrs;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	attribute_value = Nil;
	value = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L)) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EVALUATION-SEQUENCE-OF-XML-ELEMENT-EVALUATION-VALUES-P */
Object evaluation_sequence_of_xml_element_evaluation_values_p(seq)
    Object seq;
{
    Object gensymed_symbol, held_vector, x, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(242,40);
    if (CONSP(seq) && EQ(M_CDR(seq),Qsequence)) {
	gensymed_symbol = seq;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	x = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	x = validated_elt;
	if ( !TRUEP(xml_element_evaluation_value_p(x))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* XML-EVALUATION-VALUE-IS-ELEMENT-P */
Object xml_evaluation_value_is_element_p(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,41);
    temp = CONSP(value) ? (EQ(M_CDR(value),Qab_structure) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-NAME */
Object xml_element_evaluation_value_name(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,42);
    temp = estructure_slot(value,Qtag_name,Nil);
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-NS-PREFIX */
Object xml_element_evaluation_value_ns_prefix(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,43);
    temp = estructure_slot(value,Qns_prefix,Nil);
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-NS-URI */
Object xml_element_evaluation_value_ns_uri(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,44);
    temp = estructure_slot(value,Qns_uri,Nil);
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-ATTRIBUTES */
Object xml_element_evaluation_value_attributes(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,45);
    temp = estructure_slot(value,Qattributes,Nil);
    return VALUES_1(temp);
}

/* XML-ELEMENT-EVALUATION-VALUE-CHILDREN */
Object xml_element_evaluation_value_children(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,46);
    temp = estructure_slot(value,Qchildren,Nil);
    return VALUES_1(temp);
}

/* XML-EVALUATION-VALUE-GET-CONTENT */
Object xml_evaluation_value_get_content(value)
    Object value;
{
    Object temp, text, child, ab_value_, ab_children_, ab_index_, ab_len_;

    x_note_fn_call(242,47);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L)
	temp = copy_wide_string(value);
    else {
	text = array_constant_4;
	child = Nil;
	ab_value_ = value;
	ab_children_ = Nil;
	ab_index_ = Nil;
	ab_len_ = Nil;
	ab_children_ = xml_element_evaluation_value_children(ab_value_);
	ab_index_ = FIX((SI_Long)0L);
	ab_len_ = ab_children_ ? FIXNUM_SUB1(ISVREF(M_CAR(ab_children_),
		(SI_Long)1L)) : FIX((SI_Long)0L);
      next_loop:
	if (FIXNUM_GE(ab_index_,ab_len_))
	    goto end_loop;
	child = evaluation_sequence_aref(ab_children_,ab_index_);
	ab_index_ = FIXNUM_ADD1(ab_index_);
	temp = text;
	text = concatenate_text_strings(temp,
		xml_evaluation_value_get_content(child));
	goto next_loop;
      end_loop:
	temp = text;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* XML-NODE-QNAME */
Object xml_node_qname(node)
    Object node;
{
    Object local_name, prefix, ns_uri, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char thing;
    Declare_special(5);
    Object result;

    x_note_fn_call(242,48);
    result = xml_node_name(node);
    MVS_3(result,local_name,prefix,ns_uri);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(ns_uri) != (SI_Long)0L)
	reclaim_wide_string(ns_uri);
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
	      if (prefix) {
		  twrite_general_string(prefix);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = ':';
		      twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = ':';
		      schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  reclaim_text_string(prefix);
	      }
	      twrite_general_string(local_name);
	      reclaim_text_string(local_name);
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* MAKE-XML-ELEMENT-EVALUATION-VALUE-FROM-XML-ELEMENT */
Object make_xml_element_evaluation_value_from_xml_element(element)
    Object element;
{
    Object local_name, prefix, ns_uri, attr, ab_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, temp_1, child;
    Object result;

    x_note_fn_call(242,49);
    result = xml_node_name(element);
    MVS_3(result,local_name,prefix,ns_uri);
    attr = Nil;
    ab_list_ = xml_node_attributes(element);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop;
    attr = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(attr))
	goto end_loop;
    temp = convert_xml_name_to_symbol_and_reclaim(xml_node_qname(attr));
    ab_loopvar__2 = eval_list_2(temp,xml_node_get_content(attr));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    attr = xml_node_next_sibling(attr);
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    child = Nil;
    ab_list_ = xml_node_child_nodes(element);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop_1;
    child = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop_1;
    ab_loopvar__2 = 
	    eval_cons_1(make_xml_evaluation_value_from_xml_node(child),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    child = xml_node_next_sibling(child);
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    temp = make_xml_element_evaluation_value(local_name,prefix,ns_uri,
	    temp_1,temp);
    return VALUES_1(temp);
}

static Object Qxml_element_node;   /* xml-element-node */

static Object Qxml_text_node;      /* xml-text-node */

/* MAKE-XML-EVALUATION-VALUE-FROM-XML-NODE */
Object make_xml_evaluation_value_from_xml_node(node)
    Object node;
{
    Object type_symbol, temp;

    x_note_fn_call(242,50);
    type_symbol = xml_node_type_symbol(node);
    if (EQ(type_symbol,Qxml_element_node))
	temp = make_xml_element_evaluation_value_from_xml_element(node);
    else if (EQ(type_symbol,Qxml_text_node))
	temp = xml_node_get_content(node);
    else
	temp = type_symbol;
    return VALUES_1(temp);
}

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* XML-NODE-NEW-CHILD-FROM-XML-ELEMENT-EVALUATION-VALUE */
Object xml_node_new_child_from_xml_element_evaluation_value(node,element)
    Object node, element;
{
    Object prefix_qm, attrs, local_name, child, gensymed_symbol, held_vector;
    Object name_symbol, attribute_value, value, name, end1, end2;
    Object ab_loop_iter_flag_, prefix, x, ab_value_, ab_children_, ab_index_;
    Object ab_len_;
    SI_Long next_index, length_1, gensymed_symbol_1, length1, length2, index1;
    SI_Long ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;

    x_note_fn_call(242,51);
    prefix_qm = xml_element_evaluation_value_ns_prefix(element);
    attrs = xml_element_evaluation_value_attributes(element);
    local_name = xml_element_evaluation_value_name(element);
    child = xml_node_new_child(2,node,local_name);
    if (attrs) {
	gensymed_symbol = attrs;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name_symbol = Nil;
	attribute_value = Nil;
	value = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name_symbol = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	name = convert_symbol_to_xml_name(name_symbol);
	end1 = text_string_length(name);
	end2 = text_string_length(array_constant_9);
	length1 = IFIX(end1) - (SI_Long)0L;
	length2 = IFIX(end2) - (SI_Long)0L;
	if (length1 == length2) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(end1);
	    index2 = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(end2);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if (index1 >= ab_loop_bind_)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index2 = index2 + (SI_Long)1L;
	    if (index2 >= ab_loop_bind__1)
		goto end_loop_1;
	    if ( !(UBYTE_16_ISAREF_1(name,index1) == 
		    UBYTE_16_ISAREF_1(array_constant_9,index2))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    xml_element_new_namespace(2,child,value);
	else {
	    end2 = text_string_length(array_constant_10);
	    length1 = (SI_Long)6L - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		index2 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop_2:
		if (index1 >= (SI_Long)6L)
		    goto end_loop_2;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind_)
		    goto end_loop_2;
		if ( !(UBYTE_16_ISAREF_1(name,index1) == 
			UBYTE_16_ISAREF_1(array_constant_10,index2))) {
		    temp = TRUEP(Nil);
		    goto end_2;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(T);
		goto end_2;
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		prefix = text_string_substring(name,FIX((SI_Long)6L),Nil);
		xml_element_new_namespace(3,child,value,prefix);
		reclaim_text_string(prefix);
	    }
	    else
		xml_element_set_attribute(3,child,name,value);
	}
	reclaim_text_string(name);
	goto next_loop;
      end_loop:;
    }
    xml_node_set_namespace(child,xml_node_lookup_namespace(child,prefix_qm));
    x = Nil;
    ab_value_ = element;
    ab_children_ = Nil;
    ab_index_ = Nil;
    ab_len_ = Nil;
    ab_children_ = xml_element_evaluation_value_children(ab_value_);
    ab_index_ = FIX((SI_Long)0L);
    ab_len_ = ab_children_ ? FIXNUM_SUB1(ISVREF(M_CAR(ab_children_),
	    (SI_Long)1L)) : FIX((SI_Long)0L);
  next_loop_3:
    if (FIXNUM_GE(ab_index_,ab_len_))
	goto end_loop_3;
    x = evaluation_sequence_aref(ab_children_,ab_index_);
    ab_index_ = FIXNUM_ADD1(ab_index_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(x) != (SI_Long)0L)
	xml_node_add_content(child,x);
    else
	xml_node_new_child_from_xml_element_evaluation_value(child,x);
    goto next_loop_3;
  end_loop_3:;
    return VALUES_1(child);
}

/* MAKE-XML-DOCUMENT-FROM-XML-ELEMENT-EVALUATION-VALUE */
Object make_xml_document_from_xml_element_evaluation_value(value)
    Object value;
{
    Object document;

    x_note_fn_call(242,52);
    document = xml_create_document();
    xml_node_new_child_from_xml_element_evaluation_value(document,value);
    return VALUES_1(document);
}

/* MAKE-XML-DOCUMENT-FROM-XML-ELEMENT-EVALUATION-VALUE-AND-RECLAIM */
Object make_xml_document_from_xml_element_evaluation_value_and_reclaim(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,53);
    temp = make_xml_document_from_xml_element_evaluation_value(value);
    reclaim_evaluation_value(value);
    return VALUES_1(temp);
}

Object Soap_xml_namespace_uri = UNBOUND;

Object Soap_xml_namespace_prefix = UNBOUND;

Object Soap12_xml_namespace_uri = UNBOUND;

Object Soap12_xml_namespace_prefix = UNBOUND;

Object Xsi_xml_namespace_uri = UNBOUND;

Object Xsi_xml_namespace_prefix = UNBOUND;

Object Xsd_xml_namespace_uri = UNBOUND;

Object Xsd_xml_namespace_prefix = UNBOUND;

static Object array_constant_11;   /* # */

static Object Qxmlns_col_soap;     /* XMLNS\:SOAP */

static Object Qxmlns_col_soap12;   /* XMLNS\:SOAP12 */

static Object Qxmlns_col_xsd;      /* XMLNS\:XSD */

static Object Qxmlns_col_xsi;      /* XMLNS\:XSI */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* MAKE-SOAP-MESSAGE */
Object make_soap_message(namespaces,header_entries,body_entries)
    Object namespaces, header_entries, body_entries;
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6;
    Object gensymed_symbol, held_vector, prefix, attribute_value, uri;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_7, entry, elt_1;
    Object validated_elt, temp_8;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(242,54);
    temp = copy_as_wide_string(array_constant_11);
    temp_1 = copy_as_wide_string(Soap_xml_namespace_prefix);
    temp_2 = copy_as_wide_string(Soap_xml_namespace_uri);
    temp_3 = eval_list_2(Qxmlns_col_soap,
	    copy_as_wide_string(Soap_xml_namespace_uri));
    temp_4 = eval_list_2(Qxmlns_col_soap12,
	    copy_as_wide_string(Soap12_xml_namespace_uri));
    temp_5 = eval_list_2(Qxmlns_col_xsd,
	    copy_as_wide_string(Xsd_xml_namespace_uri));
    temp_6 = eval_list_2(Qxmlns_col_xsi,
	    copy_as_wide_string(Xsi_xml_namespace_uri));
    if (namespaces) {
	gensymed_symbol = namespaces;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	prefix = Nil;
	attribute_value = Nil;
	uri = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	prefix = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	uri = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	temp_7 = prefix;
	ab_loopvar__2 = eval_list_2(temp_7,copy_as_wide_string(uri));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	temp_7 = ab_loopvar_;
	goto end_1;
	temp_7 = Qnil;
      end_1:;
    }
    else
	temp_7 = Nil;
    temp_3 = nconc2(temp_3,nconc2(temp_4,nconc2(temp_5,nconc2(temp_6,
	    temp_7))));
    if (header_entries) {
	temp_4 = copy_as_wide_string(array_constant_12);
	temp_5 = copy_as_wide_string(Soap_xml_namespace_prefix);
	temp_6 = copy_as_wide_string(Soap_xml_namespace_uri);
	gensymed_symbol = header_entries;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	entry = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	entry = validated_elt;
	ab_loopvar__2 = eval_cons_1(FIXNUMP(entry) || entry && 
		SYMBOLP(entry) ? entry : copy_evaluation_value_1(entry),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp_7 = ab_loopvar_;
	goto end_2;
	temp_7 = Qnil;
      end_2:;
	temp_8 = eval_cons_1(make_xml_element_evaluation_value(temp_4,
		temp_5,temp_6,Nil,temp_7),Nil);
    }
    else
	temp_8 = Nil;
    temp_4 = copy_as_wide_string(array_constant_13);
    temp_5 = copy_as_wide_string(Soap_xml_namespace_prefix);
    temp_6 = copy_as_wide_string(Soap_xml_namespace_uri);
    gensymed_symbol = body_entries;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    entry = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop_2:
    if (next_index >= length_1)
	goto end_loop_2;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    entry = validated_elt;
    ab_loopvar__2 = eval_cons_1(FIXNUMP(entry) || entry && SYMBOLP(entry) ?
	     entry : copy_evaluation_value_1(entry),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_2;
  end_loop_2:
    temp_7 = ab_loopvar_;
    goto end_3;
    temp_7 = Qnil;
  end_3:;
    temp_7 = 
	    make_xml_document_from_xml_element_evaluation_value_and_reclaim(make_xml_element_evaluation_value(temp,
	    temp_1,temp_2,temp_3,nconc2(temp_8,
	    eval_cons_1(make_xml_element_evaluation_value(temp_4,temp_5,
	    temp_6,Nil,temp_7),Nil))));
    return VALUES_1(temp_7);
}

/* SOAP-MESSAGE-GET-ENVELOPE */
Object soap_message_get_envelope(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,55);
    temp = xml_node_get_child_by_name(3,message_1,array_constant_11,
	    Soap_xml_namespace_uri);
    return VALUES_1(temp);
}

/* SOAP-MESSAGE-GET-HEADER */
Object soap_message_get_header(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,56);
    temp = soap_message_get_envelope(message_1);
    temp = xml_node_get_child_by_name(3,temp,array_constant_12,
	    Soap_xml_namespace_uri);
    return VALUES_1(temp);
}

/* SOAP-MESSAGE-GET-BODY */
Object soap_message_get_body(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,57);
    temp = soap_message_get_envelope(message_1);
    temp = xml_node_get_child_by_name(3,temp,array_constant_13,
	    Soap_xml_namespace_uri);
    return VALUES_1(temp);
}

/* SOAP12-MESSAGE-GET-ENVELOPE */
Object soap12_message_get_envelope(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,58);
    temp = xml_node_get_child_by_name(3,message_1,array_constant_11,
	    Soap12_xml_namespace_uri);
    return VALUES_1(temp);
}

/* SOAP12-MESSAGE-GET-HEADER */
Object soap12_message_get_header(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,59);
    temp = soap_message_get_envelope(message_1);
    temp = xml_node_get_child_by_name(3,temp,array_constant_12,
	    Soap12_xml_namespace_uri);
    return VALUES_1(temp);
}

/* SOAP12-MESSAGE-GET-BODY */
Object soap12_message_get_body(message_1)
    Object message_1;
{
    Object temp;

    x_note_fn_call(242,60);
    temp = soap_message_get_envelope(message_1);
    temp = xml_node_get_child_by_name(3,temp,array_constant_13,
	    Soap12_xml_namespace_uri);
    return VALUES_1(temp);
}

static Object Qnamespaces;         /* namespaces */

static Object Qheader_entries;     /* header-entries */

static Object Qbody_entries;       /* body-entries */

/* SOAP-MESSAGE-EVALUATION-STRUCTURE-P */
Object soap_message_evaluation_structure_p(struct_1)
    Object struct_1;
{
    Object namespaces, header_entries, body_entries;

    x_note_fn_call(242,61);
    if (CONSP(struct_1) && EQ(M_CDR(struct_1),Qab_structure)) {
	namespaces = estructure_slot(struct_1,Qnamespaces,Nil);
	header_entries = estructure_slot(struct_1,Qheader_entries,Nil);
	body_entries = estructure_slot(struct_1,Qbody_entries,Nil);
	if (( !TRUEP(namespaces) || 
		xml_attributes_evaluation_value_p(namespaces)) && ( 
		!TRUEP(header_entries) || 
		evaluation_sequence_of_xml_element_evaluation_values_p(header_entries)))
	    return evaluation_sequence_of_xml_element_evaluation_values_p(body_entries);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-SOAP-MESSAGE-FROM-EVALUATION-STRUCTURE */
Object make_soap_message_from_evaluation_structure(struct_1)
    Object struct_1;
{
    Object temp, temp_1;

    x_note_fn_call(242,62);
    temp = estructure_slot(struct_1,Qnamespaces,Nil);
    temp_1 = estructure_slot(struct_1,Qheader_entries,Nil);
    return make_soap_message(temp,temp_1,estructure_slot(struct_1,
	    Qbody_entries,Nil));
}

static Object string_constant_67;  /* "xmlns:~a" */

/* MAKE-EVALUATION-STRUCTURE-FROM-SOAP-MESSAGE */
Object make_evaluation_structure_from_soap_message(message_1)
    Object message_1;
{
    Object temp, soap12_qm, header, entry, ab_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_node_, header_entries;
    Object namespace_list, ns_entry, namespaces, message_body, body_entries;
    Object temp_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(242,63);
    temp = xml_document_root_element(message_1);
    soap12_qm = xml_node_namespace_uri_equals_p(temp,Soap12_xml_namespace_uri);
    header = soap12_qm ? soap12_message_get_header(message_1) : 
	    soap_message_get_header(message_1);
    if (header) {
	entry = Nil;
	ab_list_ = xml_node_child_nodes(header);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	if ( !TRUEP(ab_list_))
	    goto end_loop;
	ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
      next_loop:
	if ( !TRUEP(ab_node_))
	    goto end_loop_1;
	if (xml_element_p(ab_node_))
	    goto end_loop_1;
	ab_node_ = xml_node_next_sibling(ab_node_);
	goto next_loop;
      end_loop_1:
	entry = ab_node_;
	goto end_1;
	entry = Qnil;
      end_1:;
      next_loop_1:
	if ( !TRUEP(entry))
	    goto end_loop;
	ab_loopvar__2 = 
		eval_cons_1(make_xml_element_evaluation_value_from_xml_element(entry),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_node_ = xml_node_next_sibling(entry);
      next_loop_2:
	if ( !TRUEP(ab_node_))
	    goto end_loop_2;
	if (xml_element_p(ab_node_))
	    goto end_loop_2;
	ab_node_ = xml_node_next_sibling(ab_node_);
	goto next_loop_2;
      end_loop_2:
	entry = ab_node_;
	goto end_2;
	entry = Qnil;
      end_2:;
	goto next_loop_1;
      end_loop:
	header_entries = ab_loopvar_;
	goto end_3;
	header_entries = Qnil;
      end_3:;
    }
    else
	header_entries = Nil;
    namespace_list = xml_element_get_namespace_list(message_1,
	    xml_document_root_element(message_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(xml_namespace_list_length(namespace_list));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    ns_entry = xml_namespace_list_item(namespace_list,FIX(i));
    temp = convert_xml_name_to_symbol_and_reclaim(tformat_text_string(2,
	    string_constant_67,xml_namespace_get_prefix(ns_entry)));
    ab_loopvar__2 = eval_list_2(temp,
	    copy_as_wide_string(xml_namespace_get_uri(ns_entry)));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:
    namespaces = ab_loopvar_;
    goto end_4;
    namespaces = Qnil;
  end_4:;
    message_body = soap12_qm ? soap12_message_get_body(message_1) : 
	    soap_message_get_body(message_1);
    entry = Nil;
    ab_list_ = xml_node_child_nodes(message_body);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop_4;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop_4:
    if ( !TRUEP(ab_node_))
	goto end_loop_5;
    if (xml_element_p(ab_node_))
	goto end_loop_5;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_4;
  end_loop_5:
    entry = ab_node_;
    goto end_5;
    entry = Qnil;
  end_5:;
  next_loop_5:
    if ( !TRUEP(entry))
	goto end_loop_4;
    ab_loopvar__2 = 
	    eval_cons_1(make_xml_element_evaluation_value_from_xml_element(entry),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_node_ = xml_node_next_sibling(entry);
  next_loop_6:
    if ( !TRUEP(ab_node_))
	goto end_loop_6;
    if (xml_element_p(ab_node_))
	goto end_loop_6;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_6;
  end_loop_6:
    entry = ab_node_;
    goto end_6;
    entry = Qnil;
  end_6:;
    goto next_loop_5;
  end_loop_4:
    body_entries = ab_loopvar_;
    goto end_7;
    body_entries = Qnil;
  end_7:;
    temp_1 = namespaces ? eval_list_2(Qnamespaces,
	    allocate_evaluation_structure(namespaces)) : Nil;
    temp = header_entries ? eval_list_2(Qheader_entries,
	    allocate_evaluation_sequence(header_entries)) : Nil;
    return allocate_evaluation_structure(nconc2(temp_1,nconc2(temp,
	    eval_list_2(Qbody_entries,
	    allocate_evaluation_sequence(body_entries)))));
}

Object Soap_request_type = UNBOUND;

Object Soap_response_type = UNBOUND;

static Object string_constant_68;  /* "Not a well-formed SOAP message structure: ~NV" */

static Object Qaction;             /* action */

static Object Qcontent_type;       /* content-type */

static Object array_constant_14;   /* # */

static Object Qsoapaction;         /* soapaction */

static Object string_constant_69;  /* "~s" */

/* G2-MAKE-WEB-REQUEST-FROM-SOAP-MESSAGE */
Object g2_make_web_request_from_soap_message(message_as_evaluation_value)
    Object message_as_evaluation_value;
{
    Object message_1, value_1, top_of_stack, message_2, action_qm;
    Object gensymed_symbol, temp, item_or_value, x2, temp_2, gensymed_symbol_2;
    Object svref_new_value, current_xml_structures, temp_3;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(242,64);
    SAVE_STACK();
    message_1 = IDENTITY(message_as_evaluation_value);
    value_1 = Nil;
    check_type_or_stack_error(2,message_1,Soap_request_type);
    if ( !TRUEP(soap_message_evaluation_structure_p(message_1))) {
	top_of_stack = Cached_top_of_stack;
	message_2 = tformat_stack_error_text_string(2,string_constant_68,
		message_1);
	raw_stack_error_named_error(top_of_stack,message_2);
    }
    action_qm = estructure_slot(message_1,Qaction,Nil);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qab_method;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qab_method;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qpost;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qpost;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qheaders;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qheaders;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qcontent_type;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qcontent_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = copy_as_wide_string(array_constant_14);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = copy_as_wide_string(array_constant_14);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qsoapaction;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qsoapaction;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = action_qm ? tformat_text_string(2,
		    string_constant_69,action_qm) : 
		    copy_as_wide_string(array_constant_4);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = action_qm ? tformat_text_string(2,
		    string_constant_69,action_qm) : 
		    copy_as_wide_string(array_constant_4);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	}
	item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qcontent_type;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)1L)) = Qcontent_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = copy_as_wide_string(array_constant_14);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = copy_as_wide_string(array_constant_14);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qsoapaction;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)3L)) = Qsoapaction;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = action_qm ? tformat_text_string(2,
		    string_constant_69,action_qm) : 
		    copy_as_wide_string(array_constant_4);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = action_qm ? tformat_text_string(2,
		    string_constant_69,action_qm) : 
		    copy_as_wide_string(array_constant_4);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
	}
	item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qentity;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qentity;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	LOCK(Xml_structures_extent);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_xml_structures = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		    0);
	      temp_3 = 
		      xml_write_text_string(make_soap_message_from_evaluation_structure(message_1));
	      reclaim_xml_structures(1,Current_xml_structures);
	      reclaim_gensym_list_1(Current_xml_structures);
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp_3));
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Xml_structures_extent);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	item_or_value = result;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	LOCK(Xml_structures_extent);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_xml_structures = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		    0);
	      temp_3 = 
		      xml_write_text_string(make_soap_message_from_evaluation_structure(message_1));
	      reclaim_xml_structures(1,Current_xml_structures);
	      reclaim_gensym_list_1(Current_xml_structures);
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp_3));
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Xml_structures_extent);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	item_or_value = result;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_2;
    }
    temp_3 = eval_cons_1(gensymed_symbol,Qab_structure);
    reclaim_evaluation_structure(message_1);
    value_1 = temp_3;
    IDENTITY(message_as_evaluation_value);
    temp_3 = IDENTITY(value_1);
    result = VALUES_1(temp_3);
    RESTORE_STACK();
    return result;
}

static Object string_constant_70;  /* "Web error in SOAP response: ~a ~a" */

static Object string_constant_71;  /* "SOAP response contains no entity." */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_72;  /* "Failed to parse SOAP response message:~%" */

static Object string_constant_73;  /* "SOAP response is empty or malformed." */

/* G2-MAKE-SOAP-MESSAGE-FROM-WEB-RESPONSE */
Object g2_make_soap_message_from_web_response(response_as_evaluation_value)
    Object response_as_evaluation_value;
{
    Object response, value_1, temp, top_of_stack, message_1, entity_qm;
    Object current_xml_structures, message_2, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(8);
    Object result;

    x_note_fn_call(242,65);
    SAVE_STACK();
    response = IDENTITY(response_as_evaluation_value);
    value_1 = Nil;
    temp = estructure_slot(response,Qstatus_code,Nil);
    if ( !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)32767L)))) {
	top_of_stack = Cached_top_of_stack;
	temp = estructure_slot(response,Qstatus_code,Nil);
	message_1 = tformat_stack_error_text_string(3,string_constant_70,
		temp,estructure_slot(response,Qreason_phrase,Nil));
	value_1 = raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	switch (INTEGER_TO_SHORT(temp)) {
	  case 200:
	  case 500:
	    entity_qm = estructure_slot(response,Qentity,Nil);
	    if ( !TRUEP(entity_qm)) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_71);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    LOCK(Xml_structures_extent);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_xml_structures = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
			7);
		  message_2 = xml_read_string(entity_qm);
		  if ( !TRUEP(message_2)) {
		      top_of_stack = Cached_top_of_stack;
		      text_string = Nil;
		      snapshots = Nil;
		      snapshots_of_related_blocks = Nil;
		      note_blocks_in_tformat = 
			      SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		      PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			      6);
			PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				5);
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
				    tformat(1,string_constant_72);
				    error_1 = Nil;
				    ab_loop_list_ = xml_get_errors();
				  next_loop:
				    if ( !TRUEP(ab_loop_list_))
					goto end_loop;
				    error_1 = M_CAR(ab_loop_list_);
				    ab_loop_list_ = M_CDR(ab_loop_list_);
				    twrite_general_string(error_1);
				    goto next_loop;
				  end_loop:;
				    text_string = 
					    copy_out_current_wide_string();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			  snapshots = Snapshots_of_related_blocks;
			  Snapshots_of_related_blocks = Nil;
			  if (Snapshots_of_related_blocks) {
			      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			      Snapshots_of_related_blocks = Nil;
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		      message_1 = make_error_text(text_string,snapshots);
		      raw_stack_error_named_error(top_of_stack,message_1);
		  }
		  temp = 
			  make_evaluation_structure_from_soap_message(message_2);
		  reclaim_evaluation_structure(response);
		  reclaim_xml_structures(1,Current_xml_structures);
		  reclaim_gensym_list_1(Current_xml_structures);
		POP_SPECIAL();
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Xml_structures_extent);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    value_1 = result;
	    break;
	  case -1:
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_73);
	    value_1 = raw_stack_error_named_error(top_of_stack,message_1);
	    break;
	  default:
	    top_of_stack = Cached_top_of_stack;
	    temp = estructure_slot(response,Qstatus_code,Nil);
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_70,temp,estructure_slot(response,
		    Qreason_phrase,Nil));
	    value_1 = raw_stack_error_named_error(top_of_stack,message_1);
	    break;
	}
    IDENTITY(response_as_evaluation_value);
    temp = IDENTITY(value_1);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object string_constant_74;  /* "SOAP request contains no entity." */

static Object string_constant_75;  /* "Failed to parse SOAP request message:~%" */

/* G2-MAKE-SOAP-MESSAGE-FROM-HTTP-REQUEST */
Object g2_make_soap_message_from_http_request(request_as_evaluation_value)
    Object request_as_evaluation_value;
{
    Object request, value_1, entity_qm, headers, action_qm, top_of_stack;
    Object message_1, current_xml_structures, msg, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_, msg_struct, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(8);
    Object result;

    x_note_fn_call(242,66);
    SAVE_STACK();
    request = IDENTITY(request_as_evaluation_value);
    value_1 = Nil;
    entity_qm = estructure_slot(request,Qentity,Nil);
    headers = estructure_slot(request,Qheaders,Nil);
    action_qm = estructure_slot(headers,Qsoapaction,Nil);
    if ( !TRUEP(entity_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_74);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    LOCK(Xml_structures_extent);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_xml_structures = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		7);
	  msg = xml_read_string(entity_qm);
	  if ( !TRUEP(msg)) {
	      top_of_stack = Cached_top_of_stack;
	      text_string = Nil;
	      snapshots = Nil;
	      snapshots_of_related_blocks = Nil;
	      note_blocks_in_tformat = 
		      SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	      PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		      6);
		PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			5);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    tformat(1,string_constant_75);
			    error_1 = Nil;
			    ab_loop_list_ = xml_get_errors();
			  next_loop:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop;
			    error_1 = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    twrite_general_string(error_1);
			    goto next_loop;
			  end_loop:;
			    text_string = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  snapshots = Snapshots_of_related_blocks;
		  Snapshots_of_related_blocks = Nil;
		  if (Snapshots_of_related_blocks) {
		      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		      Snapshots_of_related_blocks = Nil;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	      message_1 = make_error_text(text_string,snapshots);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  msg_struct = make_evaluation_structure_from_soap_message(msg);
	  if (action_qm)
	      set_evaluation_structure_slot(msg_struct,Qaction,
		      copy_wide_string(action_qm));
	  reclaim_evaluation_structure(request);
	  temp = msg_struct;
	  reclaim_xml_structures(1,Current_xml_structures);
	  reclaim_gensym_list_1(Current_xml_structures);
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Xml_structures_extent);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    value_1 = result;
    IDENTITY(request_as_evaluation_value);
    temp = IDENTITY(value_1);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object array_constant_15;   /* # */

/* G2-MAKE-HTTP-RESPONSE-FROM-SOAP-MESSAGE */
Object g2_make_http_response_from_soap_message(msg_struct_as_evaluation_value)
    Object msg_struct_as_evaluation_value;
{
    Object msg_struct, value_1, top_of_stack, message_1;
    Object current_xml_structures, msg, entry, ab_list_, ab_loop_it_, ab_node_;
    Object fault_p, temp, gensymed_symbol, temp_1, item_or_value, x2;
    Object svref_new_value, temp_3;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(242,67);
    SAVE_STACK();
    msg_struct = IDENTITY(msg_struct_as_evaluation_value);
    value_1 = Nil;
    check_type_or_stack_error(2,msg_struct,Soap_response_type);
    if ( !TRUEP(soap_message_evaluation_structure_p(msg_struct))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_68,
		msg_struct);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    LOCK(Xml_structures_extent);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_xml_structures = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		0);
	  msg = make_soap_message_from_evaluation_structure(msg_struct);
	  entry = Nil;
	  ab_list_ = xml_node_child_nodes(soap_message_get_body(msg));
	  ab_loop_it_ = Nil;
	  if ( !TRUEP(ab_list_))
	      goto end_loop;
	  ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
	next_loop:
	  if ( !TRUEP(ab_node_))
	      goto end_loop_1;
	  if (xml_element_p(ab_node_))
	      goto end_loop_1;
	  ab_node_ = xml_node_next_sibling(ab_node_);
	  goto next_loop;
	end_loop_1:
	  entry = ab_node_;
	  goto end_1;
	  entry = Qnil;
	end_1:;
	next_loop_1:
	  if ( !TRUEP(entry))
	      goto end_loop;
	  ab_loop_it_ = xml_node_name_equals_p(3,entry,array_constant_15,
		  Soap_xml_namespace_uri);
	  if (ab_loop_it_) {
	      fault_p = ab_loop_it_;
	      goto end_2;
	  }
	  ab_node_ = xml_node_next_sibling(entry);
	next_loop_2:
	  if ( !TRUEP(ab_node_))
	      goto end_loop_2;
	  if (xml_element_p(ab_node_))
	      goto end_loop_2;
	  ab_node_ = xml_node_next_sibling(ab_node_);
	  goto next_loop_2;
	end_loop_2:
	  entry = ab_node_;
	  goto end_3;
	  entry = Qnil;
	end_3:;
	  goto next_loop_1;
	end_loop:
	  fault_p = Qnil;
	end_2:;
	  temp = fault_p ? eval_list_2(Qstatus_code,FIX((SI_Long)500L)) : Nil;
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
	      ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  else {
	      temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	      ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qcontent_type;
	  else {
	      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp_1,FIX((SI_Long)1L)) = Qcontent_type;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = copy_as_wide_string(array_constant_14);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	  }
	  else {
	      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = copy_as_wide_string(array_constant_14);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      svref_new_value = temp_2 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  temp_3 = eval_cons_1(gensymed_symbol,Qab_structure);
	  temp_3 = allocate_evaluation_structure(nconc2(temp,
		  eval_list_4(Qheaders,temp_3,Qentity,
		  xml_write_text_string(msg))));
	  reclaim_evaluation_structure(msg_struct);
	  reclaim_xml_structures(1,Current_xml_structures);
	  reclaim_gensym_list_1(Current_xml_structures);
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp_3));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Xml_structures_extent);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    value_1 = result;
    IDENTITY(msg_struct_as_evaluation_value);
    temp_3 = IDENTITY(value_1);
    result = VALUES_1(temp_3);
    RESTORE_STACK();
    return result;
}

/* GET-INSTANCE-WITH-SLOT-VALUE-IF-ANY */
Object get_instance_with_slot_value_if_any(class_1,name,value)
    Object class_1, name, value;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(242,68);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(class_1);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (slot_value_equal_p(get_slot_value_function(item,name,Nil),value)) {
	  temp_1 = item;
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp_1 = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* GET-INSTANCE-WITH-SLOT-VALUE-ON-SUBWORKSPACE-IF-ANY */
Object get_instance_with_slot_value_on_subworkspace_if_any(class_1,name,
	    value,block)
    Object class_1, name, value, block;
{
    Object workspace, ab_loop_list_, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, item, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(242,69);
    workspace = Nil;
    ab_loop_list_ = ISVREF(block,(SI_Long)18L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    item = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_1:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_1;
    item = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    gensymed_symbol = lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(slot_value_equal_p(get_slot_value_function(item,name,
	    Nil),value)) : TRUEP(Nil)) {
	temp_1 = item;
	goto end_outer;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_outer:;
    return VALUES_1(temp_1);
}

static Object Qweb_service_interface_operation;  /* web-service-interface-operation */

static Object Qweb_service_interface_operation_name;  /* web-service-interface-operation-name */

/* WEB-SERVICE-INTERFACE-OPERATION */
Object web_service_interface_operation(interface_1,operation_name)
    Object interface_1, operation_name;
{
    Object temp;

    x_note_fn_call(242,70);
    temp = 
	    get_instance_with_slot_value_on_subworkspace_if_any(Qweb_service_interface_operation,
	    Qweb_service_interface_operation_name,operation_name,interface_1);
    return VALUES_1(temp);
}

/* WRITE-XML-NCNAME-FROM-SLOT */
Object write_xml_ncname_from_slot(name,gensymed_symbol)
    Object name, gensymed_symbol;
{
    x_note_fn_call(242,71);
    if (name)
	return tformat(2,string_constant_69,name);
    else
	return VALUES_1(Nil);
}

static Object string_constant_76;  /* " ~s" */

/* WRITE-WEB-SERVICE-INTERFACE-MESSAGE-REFERENCE-FROM-SLOT */
Object write_web_service_interface_message_reference_from_slot(msg_ref,
	    gensymed_symbol)
    Object msg_ref, gensymed_symbol;
{
    Object name, ns_qm;

    x_note_fn_call(242,72);
    if (msg_ref) {
	gensymed_symbol = msg_ref;
	name = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	ns_qm = CAR(gensymed_symbol);
	tformat(2,string_constant_69,name);
	if (ns_qm)
	    return tformat(2,string_constant_76,ns_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-WEB-SERVICE-INTERFACE-NAME-FROM-SLOT */
Object write_web_service_interface_name_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(242,73);
    if (value)
	return tformat(2,string_constant_69,value);
    else
	return VALUES_1(Nil);
}

static Object Qweb_service_interface;  /* web-service-interface */

static Object Qweb_service_interface_name;  /* web-service-interface-name */

/* WEB-SERVICE-BINDING-INTERFACE */
Object web_service_binding_interface(binding)
    Object binding;
{
    x_note_fn_call(242,74);
    return get_instance_with_slot_value_if_any(Qweb_service_interface,
	    Qweb_service_interface_name,
	    get_lookup_slot_value_given_default(binding,
	    Qweb_service_interface,Nil));
}

static Object Qweb_service_binding_operation;  /* web-service-binding-operation */

static Object Qweb_service_binding_operation_name;  /* web-service-binding-operation-name */

/* WEB-SERVICE-BINDING-OPERATION */
Object web_service_binding_operation(binding,operation_name)
    Object binding, operation_name;
{
    x_note_fn_call(242,75);
    return get_instance_with_slot_value_on_subworkspace_if_any(Qweb_service_binding_operation,
	    Qweb_service_binding_operation_name,operation_name,binding);
}

static Object string_constant_77;  /* "~a" */

/* WRITE-HTTP-METHOD-FROM-SLOT */
Object write_http_method_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(242,76);
    return tformat(2,string_constant_77,value);
}

/* WRITE-WEB-SERVICE-BINDING-NAME-FROM-SLOT */
Object write_web_service_binding_name_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(242,77);
    if (value)
	return tformat(2,string_constant_77,value);
    else
	return VALUES_1(Nil);
}

static Object Qendpoint_name;      /* endpoint-name */

static Object Qweb_service_endpoint;  /* web-service-endpoint */

static Object Qweb_service_endpoint_name;  /* web-service-endpoint-name */

/* GET-ENDPOINT-FROM-WEB-SERVICE-ENDPOINT-REFERENCE */
Object get_endpoint_from_web_service_endpoint_reference(ref)
    Object ref;
{
    Object service, endpoint_name, temp;

    x_note_fn_call(242,78);
    service = get_service_from_web_service_endpoint_reference(ref);
    endpoint_name = estructure_slot(ref,Qendpoint_name,Nil);
    temp = service && endpoint_name ? 
	    get_instance_with_slot_value_on_subworkspace_if_any(Qweb_service_endpoint,
	    Qweb_service_endpoint_name,endpoint_name,service) : Nil;
    return VALUES_1(temp);
}

static Object Qservice_name;       /* service-name */

static Object Qservice_namespace;  /* service-namespace */

static Object Qweb_service_description;  /* web-service-description */

static Object Qweb_service_xml_namespace;  /* web-service-xml-namespace */

static Object Qweb_service;        /* web-service */

static Object Qweb_service_name;   /* web-service-name */

/* GET-SERVICE-FROM-WEB-SERVICE-ENDPOINT-REFERENCE */
Object get_service_from_web_service_endpoint_reference(ref)
    Object ref;
{
    Object service_name, service_namespace, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, desc, service, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(242,79);
    service_name = estructure_slot(ref,Qservice_name,Nil);
    service_namespace = estructure_slot(ref,Qservice_namespace,Nil);
    if (service_name) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	desc = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qweb_service_description);
	next_loop:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop;
	      goto next_loop_1;
	    end_loop:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_1;
	  desc = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (slot_value_equal_p(get_lookup_slot_value_given_default(desc,
		  Qweb_service_xml_namespace,Nil),service_namespace)) {
	      service = 
		      get_instance_with_slot_value_on_subworkspace_if_any(Qweb_service,
		      Qweb_service_name,service_name,desc);
	      if (service) {
		  temp_1 = service;
		  goto end_1;
	      }
	  }
	  goto next_loop;
	end_loop_1:
	  temp_1 = Qnil;
	end_1:;
	POP_SPECIAL();
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* WEB-SERVICE-MESSAGE-P */
Object web_service_message_p(value)
    Object value;
{
    Object gensymed_symbol, held_vector, name, attribute_value, temp;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(242,80);
    if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	gensymed_symbol = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	attribute_value = Nil;
	value = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	if ( !TRUEP(web_service_message_part_value_p(value))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* WEB-SERVICE-MESSAGE-PART-VALUE-P */
Object web_service_message_part_value_p(value)
    Object value;
{
    Object temp;

    x_note_fn_call(242,81);
    temp = xml_evaluation_value_p(value);
    if (temp);
    else
	temp = evaluation_sequence_of_xml_evaluation_values_p(value);
    return VALUES_1(temp);
}

static Object array_constant_16;   /* # */

static Object Qxmlns;              /* xmlns */

/* MAKE-XML-ELEMENT-EVALUATION-VALUE-FROM-WEB-SERVICE-MESSAGE */
Object make_xml_element_evaluation_value_from_web_service_message(message_1,
	    msg_ref,ns_prefix)
    Object message_1, msg_ref, ns_prefix;
{
    Object gensymed_symbol, name, ns_uri, temp, temp_1, temp_2, temp_3, temp_4;
    Object held_vector, attribute_value, value, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(242,82);
    gensymed_symbol = msg_ref;
    name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    ns_uri = CAR(gensymed_symbol);
    temp = copy_as_wide_string(name);
    temp_1 = copy_as_wide_string(ns_prefix ? ns_prefix : array_constant_16);
    temp_2 = copy_as_wide_string(ns_uri);
    temp_3 = ns_prefix ? convert_xml_name_to_symbol(tformat_text_string(2,
	    string_constant_67,ns_prefix)) : Qxmlns;
    temp_4 = eval_list_2(temp_3,copy_as_wide_string(ns_uri));
    gensymed_symbol = message_1;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    ab_loopvar__2 = 
	    eval_cons_1(make_xml_element_evaluation_value_from_web_service_message_part(name,
	    value,ns_prefix,ns_uri),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_3 = ab_loopvar_;
    goto end_1;
    temp_3 = Qnil;
  end_1:;
    temp_3 = make_xml_element_evaluation_value(temp,temp_1,temp_2,temp_4,
	    temp_3);
    return VALUES_1(temp_3);
}

/* MAKE-XML-ELEMENT-EVALUATION-VALUE-FROM-WEB-SERVICE-MESSAGE-PART */
Object make_xml_element_evaluation_value_from_web_service_message_part(name,
	    value,ns_prefix,ns_uri)
    Object name, value, ns_prefix, ns_uri;
{
    Object xml_qname, local_name, prefix, temp, temp_1, temp_2;
    Object gensymed_symbol, held_vector, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Object result;

    x_note_fn_call(242,83);
    xml_qname = convert_symbol_to_xml_name(name);
    result = xml_qname_expand(xml_qname);
    MVS_2(result,local_name,prefix);
    if (ns_prefix) {
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
	    reclaim_wide_string(prefix);
    }
    temp = ns_prefix ? copy_as_wide_string(ns_prefix) : prefix;
    temp_1 = ns_uri ? copy_as_wide_string(ns_uri) : Nil;
    if (xml_evaluation_value_p(value))
	temp_2 = eval_cons_1(FIXNUMP(value) || value && SYMBOLP(value) ? 
		value : copy_evaluation_value_1(value),Nil);
    else {
	gensymed_symbol = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	value = validated_elt;
	ab_loopvar__2 = eval_cons_1(FIXNUMP(value) || value && 
		SYMBOLP(value) ? value : copy_evaluation_value_1(value),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
    }
    temp_2 = make_xml_element_evaluation_value(local_name,temp,temp_1,Nil,
	    temp_2);
    return VALUES_1(temp_2);
}

/* MAKE-URLENCODED-HTTP-ENTITY-FROM-WEB-SERVICE-MESSAGE */
Object make_urlencoded_http_entity_from_web_service_message(message_1)
    Object message_1;
{
    Object gensymed_symbol, held_vector, name, attribute_value, value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, field_name, temp;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(242,84);
    gensymed_symbol = message_1;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    field_name = convert_symbol_to_xml_name(name);
    upcase_text_string_in_place(field_name);
    ab_loopvar__2 = eval_cons_1(intern_text_string(1,field_name),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = eval_cons_1(copy_wide_string(value),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = allocate_evaluation_structure(temp);
    return VALUES_1(temp);
}

/* MAKE-WEB-SERVICE-MESSAGE-FROM-XML-ELEMENT-EVALUATION-VALUE */
Object make_web_service_message_from_xml_element_evaluation_value(value)
    Object value;
{
    Object child, ab_value_, ab_children_, ab_index_, ab_len_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(242,85);
    child = Nil;
    ab_value_ = value;
    ab_children_ = Nil;
    ab_index_ = Nil;
    ab_len_ = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_children_ = xml_element_evaluation_value_children(ab_value_);
    ab_index_ = FIX((SI_Long)0L);
    ab_len_ = ab_children_ ? FIXNUM_SUB1(ISVREF(M_CAR(ab_children_),
	    (SI_Long)1L)) : FIX((SI_Long)0L);
  next_loop:
    if (FIXNUM_GE(ab_index_,ab_len_))
	goto end_loop;
    child = evaluation_sequence_aref(ab_children_,ab_index_);
    ab_index_ = FIXNUM_ADD1(ab_index_);
    if (xml_evaluation_value_is_element_p(child)) {
	ab_loopvar__2 = 
		make_web_service_message_part_from_xml_element_evaluation_value(child);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = allocate_evaluation_structure(temp);
    return VALUES_1(temp);
}

/* MAKE-WEB-SERVICE-MESSAGE-PART-FROM-XML-ELEMENT-EVALUATION-VALUE */
Object make_web_service_message_part_from_xml_element_evaluation_value(value)
    Object value;
{
    Object child, ab_value_, ab_children_, ab_index_, ab_len_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, children, temp, temp_1;

    x_note_fn_call(242,86);
    child = Nil;
    ab_value_ = value;
    ab_children_ = Nil;
    ab_index_ = Nil;
    ab_len_ = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_children_ = xml_element_evaluation_value_children(ab_value_);
    ab_index_ = FIX((SI_Long)0L);
    ab_len_ = ab_children_ ? FIXNUM_SUB1(ISVREF(M_CAR(ab_children_),
	    (SI_Long)1L)) : FIX((SI_Long)0L);
  next_loop:
    if (FIXNUM_GE(ab_index_,ab_len_))
	goto end_loop;
    child = evaluation_sequence_aref(ab_children_,ab_index_);
    ab_index_ = FIXNUM_ADD1(ab_index_);
    ab_loopvar__2 = eval_cons_1(FIXNUMP(child) || child && SYMBOLP(child) ?
	     child : copy_evaluation_value_1(child),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    children = ab_loopvar_;
    goto end_1;
    children = Qnil;
  end_1:;
    temp = 
	    convert_xml_name_to_symbol(xml_element_evaluation_value_name(value));
    if ( !TRUEP(children))
	temp_1 = copy_as_wide_string(array_constant_4);
    else if ( !TRUEP(CDR(children))) {
	temp_1 = CAR(children);
	reclaim_eval_list_1(children);
    }
    else
	temp_1 = allocate_evaluation_sequence(children);
    temp = eval_list_2(temp,temp_1);
    return VALUES_1(temp);
}

/* MAKE-WEB-SERVICE-MESSAGE-FROM-XML-HTTP-ENTITY */
Object make_web_service_message_from_xml_http_entity(entity)
    Object entity;
{
    Object current_xml_structures, temp, xml_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(242,87);
    SAVE_STACK();
    LOCK(Xml_structures_extent);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_xml_structures = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		0);
	  temp = 
		  make_xml_element_evaluation_value_from_xml_element(xml_document_root_element(xml_read_string_or_stack_error(entity)));
	  reclaim_xml_structures(1,Current_xml_structures);
	  reclaim_gensym_list_1(Current_xml_structures);
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Xml_structures_extent);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    xml_value = result;
    temp = 
	    allocate_evaluation_structure(make_web_service_message_part_from_xml_element_evaluation_value(xml_value));
    reclaim_evaluation_value(xml_value);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object string_constant_78;  /* "Input message ~NV is malformed." */

static Object string_constant_79;  /* "An endpoint cannot be determined from the endpoint reference ~NV." */

static Object Qweb_service_endpoint_binding;  /* web-service-endpoint-binding */

static Object Qweb_service_binding;  /* web-service-binding */

static Object Qweb_service_binding_name;  /* web-service-binding-name */

static Object Qweb_service_endpoint_address;  /* web-service-endpoint-address */

static Object string_constant_80;  /* "Endpoint ~NF has no binding." */

static Object string_constant_81;  /* "The binding ~a of endpoint ~NF does not exist." */

static Object string_constant_82;  /* "Endpoint ~NF has no address." */

static Object Qweb_service_http_binding;  /* web-service-http-binding */

static Object Qweb_service_soap_binding;  /* web-service-soap-binding */

static Object string_constant_83;  /* "Binding ~NF is of unknown type ~NF." */

/* G2-MAKE-WEB-SERVICE-OPERATION-INVOCATION */
Object g2_make_web_service_operation_invocation(endpoint_reference_as_evaluation_value,
	    operation_name_as_evaluation_value,
	    input_message_as_evaluation_value)
    Object endpoint_reference_as_evaluation_value;
    Object operation_name_as_evaluation_value;
    Object input_message_as_evaluation_value;
{
    Object endpoint_reference, operation_name, input_message, value_1;
    Object top_of_stack, message_1, endpoint, binding_name, binding, address;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(242,88);
    endpoint_reference = IDENTITY(endpoint_reference_as_evaluation_value);
    operation_name = operation_name_as_evaluation_value;
    input_message = IDENTITY(input_message_as_evaluation_value);
    value_1 = Nil;
    if ( !TRUEP(web_service_message_p(input_message))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_78,
		input_message);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    endpoint = 
	    get_endpoint_from_web_service_endpoint_reference(endpoint_reference);
    if ( !TRUEP(endpoint)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_79,
		endpoint_reference);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    binding_name = get_lookup_slot_value_given_default(endpoint,
	    Qweb_service_endpoint_binding,Nil);
    binding = get_instance_with_slot_value_if_any(Qweb_service_binding,
	    Qweb_service_binding_name,binding_name);
    address = get_lookup_slot_value_given_default(endpoint,
	    Qweb_service_endpoint_address,Nil);
    if ( !TRUEP(binding_name)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_80,
		endpoint);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(binding)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_81,
		binding_name,endpoint);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(address)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_82,
		endpoint);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    gensymed_symbol = ISVREF(binding,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qweb_service_http_binding,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = make_http_web_service_operation_invocation(binding,
		operation_name,address,input_message);
    else {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qweb_service_soap_binding,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    temp_1 = make_soap_web_service_operation_invocation(binding,
		    operation_name,address,input_message);
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_83,binding,ISVREF(ISVREF(binding,
		    (SI_Long)1L),(SI_Long)1L));
	    temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    reclaim_evaluation_structure(input_message);
    value_1 = temp_1;
    IDENTITY(endpoint_reference_as_evaluation_value);
    reclaim_text_string(operation_name_as_evaluation_value);
    IDENTITY(input_message_as_evaluation_value);
    temp_1 = IDENTITY(value_1);
    return VALUES_1(temp_1);
}

static Object string_constant_84;  /* "Input message part ~a is not a text: ~NV" */

static Object Qweb_service_http_method;  /* web-service-http-method */

static Object string_constant_85;  /* "Binding ~NF has no operation ~a." */

static Object Qweb_service_http_operation_location;  /* web-service-http-operation-location */

static Object Qsys_proc_name;      /* sys-proc-name */

static Object Qg2_send_web_request;  /* g2-send-web-request */

static Object Qurl;                /* url */

static Object Qrequest;            /* request */

/* MAKE-HTTP-WEB-SERVICE-OPERATION-INVOCATION */
Object make_http_web_service_operation_invocation(binding,operation_name,
	    address,input_message)
    Object binding, operation_name, address, input_message;
{
    Object gensymed_symbol, held_vector, name, attribute_value, value;
    Object top_of_stack, message_1, method, operation, location_qm, temp;
    Object item_or_value, x2, temp_2, gensymed_symbol_2, svref_new_value;
    SI_Long next_index, length_1, gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(242,89);
    gensymed_symbol = input_message;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    name = Nil;
    attribute_value = Nil;
    value = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_84,
		name,value);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    goto next_loop;
  end_loop:;
    method = get_lookup_slot_value(binding,Qweb_service_http_method);
    operation = web_service_binding_operation(binding,operation_name);
    if ( !TRUEP(operation)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_85,
		binding,operation_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    location_qm = get_lookup_slot_value_given_default(operation,
	    Qweb_service_http_operation_location,Nil);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qsys_proc_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qsys_proc_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qg2_send_web_request;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qg2_send_web_request;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qurl;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qurl;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = location_qm ? concatenate_text_strings(address,
		location_qm) : copy_text_string(address);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = location_qm ? concatenate_text_strings(address,
		location_qm) : copy_text_string(address);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qrequest;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qrequest;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qab_method;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qab_method;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = method;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = method;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qentity;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qentity;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    make_urlencoded_http_entity_from_web_service_message(input_message);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = 
		    make_urlencoded_http_entity_from_web_service_message(input_message);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	}
	item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qab_method;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)1L)) = Qab_method;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = method;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = method;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qentity;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)3L)) = Qentity;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    make_urlencoded_http_entity_from_web_service_message(input_message);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = 
		    make_urlencoded_http_entity_from_web_service_message(input_message);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
	}
	item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_2;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object string_constant_86;  /* "Interface ~a of binding ~NF does not exist." */

static Object Qweb_service_soap_operation_action;  /* web-service-soap-operation-action */

static Object string_constant_87;  /* "tns" */

static Object Qweb_service_input_message;  /* web-service-input-message */

static Object string_constant_88;  /* "Interface ~NF has no operation ~a." */

static Object Qg2_send_soap_request;  /* g2-send-soap-request */

/* MAKE-SOAP-WEB-SERVICE-OPERATION-INVOCATION */
Object make_soap_web_service_operation_invocation(binding,operation_name,
	    address,input_message)
    Object binding, operation_name, address, input_message;
{
    Object local_operation_name, prefix, operation, interface_1, top_of_stack;
    Object message_1, interface_operation, action_qm, ns_prefix, msg_ref;
    Object gensymed_symbol, input_message_name, ns_uri, temp, item_or_value;
    Object x2, temp_2, temp_3, gensymed_symbol_2, temp_4, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Object result;

    x_note_fn_call(242,90);
    result = xml_qname_expand(copy_text_string(operation_name));
    MVS_2(result,local_operation_name,prefix);
    operation = web_service_binding_operation(binding,local_operation_name);
    interface_1 = web_service_binding_interface(binding);
    if ( !TRUEP(operation)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_85,
		binding,local_operation_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(interface_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_86,
		get_lookup_slot_value_given_default(binding,
		Qweb_service_interface,Nil),binding);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    interface_operation = web_service_interface_operation(interface_1,
	    local_operation_name);
    action_qm = get_lookup_slot_value_given_default(operation,
	    Qweb_service_soap_operation_action,Nil);
    ns_prefix = prefix ? tformat_text_string(2,string_constant_77,prefix) :
	     tformat_text_string(1,string_constant_87);
    msg_ref = get_lookup_slot_value_given_default(interface_operation,
	    Qweb_service_input_message,Nil);
    if ( !TRUEP(interface_operation)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_88,
		interface_1,local_operation_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    gensymed_symbol = msg_ref;
    input_message_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    ns_uri = CAR(gensymed_symbol);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qsys_proc_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qsys_proc_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qg2_send_soap_request;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qg2_send_soap_request;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qurl;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qurl;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = copy_as_wide_string(address);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = copy_as_wide_string(address);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qrequest;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qrequest;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp_3 = action_qm ? eval_list_2(Qaction,
		copy_as_wide_string(action_qm)) : Nil;
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = 
		    convert_xml_name_to_symbol_and_reclaim(tformat_text_string(2,
		    string_constant_67,ns_prefix));
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    temp_2 = 
		    convert_xml_name_to_symbol_and_reclaim(tformat_text_string(2,
		    string_constant_67,ns_prefix));
	    SVREF(temp,FIX((SI_Long)1L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = copy_as_wide_string(ns_uri);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = copy_as_wide_string(ns_uri);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	}
	temp_4 = eval_list_2(Qnamespaces,eval_cons_1(gensymed_symbol_2,
		Qab_structure));
	item_or_value = allocate_evaluation_structure(nconc2(temp_3,
		nconc2(temp_4,eval_list_2(Qbody_entries,
		allocate_evaluation_sequence(eval_cons_1(make_xml_element_evaluation_value_from_web_service_message(input_message,
		get_lookup_slot_value_given_default(interface_operation,
		Qweb_service_input_message,Nil),prefix),Nil))))));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	temp_3 = action_qm ? eval_list_2(Qaction,
		copy_as_wide_string(action_qm)) : Nil;
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_2 = 
		    convert_xml_name_to_symbol_and_reclaim(tformat_text_string(2,
		    string_constant_67,ns_prefix));
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    svref_new_value = 
		    convert_xml_name_to_symbol_and_reclaim(tformat_text_string(2,
		    string_constant_67,ns_prefix));
	    SVREF(temp_2,FIX((SI_Long)1L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = copy_as_wide_string(ns_uri);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = copy_as_wide_string(ns_uri);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp_4 = eval_list_2(Qnamespaces,eval_cons_1(gensymed_symbol_2,
		Qab_structure));
	item_or_value = allocate_evaluation_structure(nconc2(temp_3,
		nconc2(temp_4,eval_list_2(Qbody_entries,
		allocate_evaluation_sequence(eval_cons_1(make_xml_element_evaluation_value_from_web_service_message(input_message,
		get_lookup_slot_value_given_default(interface_operation,
		Qweb_service_input_message,Nil),prefix),Nil))))));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_2;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* G2-GET-MESSAGE-FROM-WEB-SERVICE-OPERATION-RESPONSE */
Object g2_get_message_from_web_service_operation_response(invocation_as_evaluation_value,
	    response_as_evaluation_value)
    Object invocation_as_evaluation_value, response_as_evaluation_value;
{
    Object invocation, response, value_1, temp;

    x_note_fn_call(242,91);
    invocation = IDENTITY(invocation_as_evaluation_value);
    response = IDENTITY(response_as_evaluation_value);
    value_1 = Nil;
    temp = estructure_slot(invocation,Qsys_proc_name,Nil);
    if (EQ(temp,Qg2_send_web_request))
	temp = get_message_from_http_web_service_operation_response(response);
    else if (EQ(temp,Qg2_send_soap_request))
	temp = get_message_from_soap_web_service_operation_response(response);
    else
	temp = Qnil;
    reclaim_evaluation_structure(invocation);
    reclaim_evaluation_structure(response);
    value_1 = temp;
    IDENTITY(invocation_as_evaluation_value);
    IDENTITY(response_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* GET-MESSAGE-FROM-HTTP-WEB-SERVICE-OPERATION-RESPONSE */
Object get_message_from_http_web_service_operation_response(response)
    Object response;
{
    x_note_fn_call(242,92);
    return make_web_service_message_from_xml_http_entity(estructure_slot(response,
	    Qentity,Nil));
}

/* GET-MESSAGE-FROM-SOAP-WEB-SERVICE-OPERATION-RESPONSE */
Object get_message_from_soap_web_service_operation_response(response)
    Object response;
{
    x_note_fn_call(242,93);
    return make_web_service_message_from_xml_element_evaluation_value(evaluation_sequence_aref(estructure_slot(response,
	    Qbody_entries,Nil),FIX((SI_Long)0L)));
}

Object Wsdl_xml_namespace_uri = UNBOUND;

Object Wsdl_soap_xml_namespace_uri = UNBOUND;

Object Wsdl_soap12_xml_namespace_uri = UNBOUND;

Object Wsdl_http_xml_namespace_uri = UNBOUND;

static Object Qkb_workspace;       /* kb-workspace */

/* ADD-ITEMS-TO-WEB-SERVICE-SUBWORKSPACE */
Object add_items_to_web_service_subworkspace(items,ws_object)
    Object items, ws_object;
{
    Object subworkspace, item, ab_loop_list_, ab_loop_iter_flag_, temp;
    SI_Long y;

    x_note_fn_call(242,94);
    subworkspace = make_workspace(1,Qkb_workspace);
    add_subworkspace(subworkspace,ws_object);
    item = Nil;
    ab_loop_list_ = items;
    y = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    if (ab_loop_iter_flag_)
	item = M_CAR(ab_loop_list_);
    else {
	temp = M_CAR(ab_loop_list_);
	y = y - (SI_Long)100L;
	item = temp;
    }
    ab_loop_list_ = M_CDR(ab_loop_list_);
    transfer_item(4,item,subworkspace,FIX((SI_Long)0L),FIX(y));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(items);
}

static Object array_constant_17;   /* # */

static Object string_constant_89;  /* "name" */

/* IMPORT-WEB-SERVICE-MESSAGE */
Object import_web_service_message(description,name)
    Object description, name;
{
    Object message_1, ab_list_, ab_node_, msg_name, temp;

    x_note_fn_call(242,95);
    message_1 = Nil;
    ab_list_ = xml_node_child_nodes(description);
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    message_1 = ab_node_;
    goto end_1;
    message_1 = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(message_1))
	goto end_loop;
    if (xml_node_name_equals_p(3,message_1,array_constant_17,
	    Wsdl_xml_namespace_uri)) {
	msg_name = xml_element_get_attribute(2,message_1,string_constant_89);
	temp = equalw(msg_name,name);
	reclaim_text_string(msg_name);
	if (temp)
	    return VALUES_1(message_1);
    }
    ab_node_ = xml_node_next_sibling(message_1);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    message_1 = ab_node_;
    goto end_2;
    message_1 = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_90;  /* "message" */

static Object array_constant_18;   /* # */

static Object string_constant_91;  /* "element" */

/* IMPORT-WEB-SERVICE-INTERFACE-MESSAGE-REFERENCE */
Object import_web_service_interface_message_reference(element)
    Object element;
{
    Object msg_name, prefix, msg_ns, operation, interface_1, description;
    Object message_1, first_part, elt_name, elt_ns, temp;
    Object result;

    x_note_fn_call(242,96);
    result = xml_element_get_attribute_qname(2,element,string_constant_90);
    MVS_3(result,msg_name,prefix,msg_ns);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
	reclaim_wide_string(prefix);
    if (msg_name) {
	operation = xml_node_parent_node(element);
	interface_1 = xml_node_parent_node(operation);
	description = xml_node_parent_node(interface_1);
	message_1 = import_web_service_message(description,msg_name);
	first_part = xml_node_get_child_by_name(3,message_1,
		array_constant_18,Wsdl_xml_namespace_uri);
	if (first_part) {
	    result = xml_element_get_attribute_qname(2,first_part,
		    string_constant_91);
	    MVS_3(result,elt_name,prefix,elt_ns);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
		reclaim_wide_string(prefix);
	    if (elt_name) {
		reclaim_text_string(msg_name);
		temp = xml_namespace_get_uri(elt_ns);
		return VALUES_2(elt_name,temp);
	    }
	    else {
		temp = xml_namespace_get_uri(msg_ns);
		return VALUES_2(msg_name,temp);
	    }
	}
	else {
	    temp = xml_namespace_get_uri(msg_ns);
	    return VALUES_2(msg_name,temp);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object Qweb_service_output_message;  /* web-service-output-message */

/* IMPORT-WEB-SERVICE-INTERFACE-OPERATION */
Object import_web_service_interface_operation(element)
    Object element;
{
    Object operation, child, ab_list_, ab_node_, input_p, output_p, name, ns;
    Object result;

    x_note_fn_call(242,97);
    operation = make_entity(1,Qweb_service_interface_operation);
    set_frame_name_from_xml_element(operation,element);
    change_slot_value(3,operation,Qweb_service_interface_operation_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    child = Nil;
    ab_list_ = xml_node_child_nodes(element);
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    child = ab_node_;
    goto end_1;
    child = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop;
    input_p = xml_node_name_equals_p(3,child,array_constant_19,
	    Wsdl_xml_namespace_uri);
    output_p = xml_node_name_equals_p(3,child,array_constant_20,
	    Wsdl_xml_namespace_uri);
    if (input_p || output_p) {
	result = import_web_service_interface_message_reference(child);
	MVS_2(result,name,ns);
	if (name)
	    change_slot_value(3,operation,input_p ? 
		    Qweb_service_input_message : 
		    Qweb_service_output_message,ns ? 
		    slot_value_list_2(name,ns) : slot_value_cons_1(name,Nil));
    }
    ab_node_ = xml_node_next_sibling(child);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    child = ab_node_;
    goto end_2;
    child = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:;
    return VALUES_1(operation);
}

static Object array_constant_21;   /* # */

/* IMPORT-WEB-SERVICE-INTERFACE */
Object import_web_service_interface(element)
    Object element;
{
    Object interface_1, child, ab_list_, operations, ab_loopvar_;
    Object ab_loopvar__1, ab_node_;

    x_note_fn_call(242,98);
    interface_1 = make_entity(1,Qweb_service_interface);
    set_frame_name_from_xml_element(interface_1,element);
    change_slot_value(3,interface_1,Qweb_service_interface_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    child = Nil;
    ab_list_ = xml_node_child_nodes(element);
    operations = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    child = ab_node_;
    goto end_1;
    child = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop;
    if (xml_node_name_equals_p(3,child,array_constant_21,
	    Wsdl_xml_namespace_uri)) {
	ab_loopvar__1 = 
		gensym_cons_1(import_web_service_interface_operation(child),
		Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    operations = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    ab_node_ = xml_node_next_sibling(child);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    child = ab_node_;
    goto end_2;
    child = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:
    add_items_to_web_service_subworkspace(operations,interface_1);
    return VALUES_1(interface_1);
}

static Object array_constant_22;   /* # */

static Object Qsoap;               /* soap */

static Object Qsoap12;             /* soap12 */

/* IMPORT-WEB-SERVICE-BINDING-TYPE */
Object import_web_service_binding_type(element)
    Object element;
{
    x_note_fn_call(242,99);
    if (xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_soap_xml_namespace_uri))
	return VALUES_1(Qsoap);
    else if (xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_soap12_xml_namespace_uri))
	return VALUES_1(Qsoap12);
    else if (xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_http_xml_namespace_uri))
	return VALUES_1(Qhttp);
    else
	return VALUES_1(Qnil);
}

static Object Qweb_service_soap_operation;  /* web-service-soap-operation */

static Object string_constant_92;  /* "soapAction" */

/* IMPORT-WEB-SERVICE-SOAP-OPERATION */
Object import_web_service_soap_operation(element)
    Object element;
{
    Object operation;

    x_note_fn_call(242,100);
    operation = make_entity(1,Qweb_service_soap_operation);
    change_slot_value(3,operation,Qweb_service_soap_operation_action,
	    xml_element_get_attribute(2,element,string_constant_92));
    return VALUES_1(operation);
}

static Object Qweb_service_http_operation;  /* web-service-http-operation */

static Object string_constant_93;  /* "location" */

/* IMPORT-WEB-SERVICE-HTTP-OPERATION */
Object import_web_service_http_operation(element)
    Object element;
{
    Object operation;

    x_note_fn_call(242,101);
    operation = make_entity(1,Qweb_service_http_operation);
    change_slot_value(3,operation,Qweb_service_http_operation_location,
	    xml_element_get_attribute(2,element,string_constant_93));
    return VALUES_1(operation);
}

/* IMPORT-WEB-SERVICE-BINDING-OPERATION */
Object import_web_service_binding_operation(element,type)
    Object element, type;
{
    Object temp, operation_element, operation;

    x_note_fn_call(242,102);
    if (EQ(type,Qsoap))
	temp = Wsdl_soap_xml_namespace_uri;
    else if (EQ(type,Qsoap12))
	temp = Wsdl_soap12_xml_namespace_uri;
    else if (EQ(type,Qhttp))
	temp = Wsdl_http_xml_namespace_uri;
    else
	temp = Qnil;
    operation_element = xml_node_get_child_by_name(3,element,
	    array_constant_21,temp);
    if (EQ(type,Qsoap))
	operation = import_web_service_soap_operation(operation_element);
    else if (EQ(type,Qsoap12))
	operation = import_web_service_soap_operation(operation_element);
    else if (EQ(type,Qhttp))
	operation = import_web_service_http_operation(operation_element);
    else
	operation = Qnil;
    set_frame_name_from_xml_element(operation,element);
    change_slot_value(3,operation,Qweb_service_binding_operation_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    return VALUES_1(operation);
}

/* IMPORT-WEB-SERVICE-SOAP-BINDING-ATTRIBUTES */
Object import_web_service_soap_binding_attributes(binding,element)
    Object binding, element;
{
    x_note_fn_call(242,103);
    xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_soap_xml_namespace_uri);
    return VALUES_1(Nil);
}

/* IMPORT-WEB-SERVICE-SOAP12-BINDING-ATTRIBUTES */
Object import_web_service_soap12_binding_attributes(binding,element)
    Object binding, element;
{
    x_note_fn_call(242,104);
    xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_soap12_xml_namespace_uri);
    return VALUES_1(Nil);
}

static Object string_constant_94;  /* "verb" */

/* IMPORT-WEB-SERVICE-HTTP-BINDING-ATTRIBUTES */
Object import_web_service_http_binding_attributes(binding,element)
    Object binding, element;
{
    Object method;

    x_note_fn_call(242,105);
    element = xml_node_get_child_by_name(3,element,array_constant_22,
	    Wsdl_http_xml_namespace_uri);
    method = xml_element_get_attribute(2,element,string_constant_94);
    if (method) {
	upcase_text_string_in_place(method);
	return change_slot_value(3,binding,Qweb_service_http_method,
		intern_text_string(1,method));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_95;  /* "type" */

/* IMPORT-WEB-SERVICE-BINDING */
Object import_web_service_binding(element)
    Object element;
{
    Object type, temp, binding, interface_name, prefix, child, ab_list_;
    Object operations, ab_loopvar_, ab_loopvar__1, ab_node_;
    Object result;

    x_note_fn_call(242,106);
    type = import_web_service_binding_type(element);
    if (type) {
	if (EQ(type,Qsoap))
	    temp = Qweb_service_soap_binding;
	else if (EQ(type,Qsoap12))
	    temp = Qweb_service_soap_binding;
	else if (EQ(type,Qhttp))
	    temp = Qweb_service_http_binding;
	else
	    temp = Qnil;
	binding = make_entity(1,temp);
	set_frame_name_from_xml_element(binding,element);
	change_slot_value(3,binding,Qweb_service_binding_name,
		xml_element_get_attribute(2,element,string_constant_89));
	result = xml_element_get_attribute_qname(2,element,string_constant_95);
	MVS_2(result,interface_name,prefix);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
	    reclaim_wide_string(prefix);
	change_slot_value(3,binding,Qweb_service_interface,interface_name);
	child = Nil;
	ab_list_ = xml_node_child_nodes(element);
	operations = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	if ( !TRUEP(ab_list_))
	    goto end_loop;
	ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
      next_loop:
	if ( !TRUEP(ab_node_))
	    goto end_loop_1;
	if (xml_element_p(ab_node_))
	    goto end_loop_1;
	ab_node_ = xml_node_next_sibling(ab_node_);
	goto next_loop;
      end_loop_1:
	child = ab_node_;
	goto end_1;
	child = Qnil;
      end_1:;
      next_loop_1:
	if ( !TRUEP(child))
	    goto end_loop;
	if (xml_node_name_equals_p(3,child,array_constant_21,
		Wsdl_xml_namespace_uri)) {
	    ab_loopvar__1 = 
		    gensym_cons_1(import_web_service_binding_operation(child,
		    type),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		operations = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	ab_node_ = xml_node_next_sibling(child);
      next_loop_2:
	if ( !TRUEP(ab_node_))
	    goto end_loop_2;
	if (xml_element_p(ab_node_))
	    goto end_loop_2;
	ab_node_ = xml_node_next_sibling(ab_node_);
	goto next_loop_2;
      end_loop_2:
	child = ab_node_;
	goto end_2;
	child = Qnil;
      end_2:;
	goto next_loop_1;
      end_loop:
	add_items_to_web_service_subworkspace(operations,binding);
	if (EQ(type,Qsoap))
	    import_web_service_soap_binding_attributes(binding,element);
	else if (EQ(type,Qsoap12))
	    import_web_service_soap12_binding_attributes(binding,element);
	else if (EQ(type,Qhttp))
	    import_web_service_http_binding_attributes(binding,element);
	return VALUES_1(binding);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_96;  /* "binding" */

static Object array_constant_23;   /* # */

/* IMPORT-WEB-SERVICE-ENDPOINT */
Object import_web_service_endpoint(element)
    Object element;
{
    Object endpoint, binding_name, prefix, address_element;
    Object result;

    x_note_fn_call(242,107);
    endpoint = make_entity(1,Qweb_service_endpoint);
    set_frame_name_from_xml_element(endpoint,element);
    change_slot_value(3,endpoint,Qweb_service_endpoint_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    result = xml_element_get_attribute_qname(2,element,string_constant_96);
    MVS_2(result,binding_name,prefix);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
	reclaim_wide_string(prefix);
    change_slot_value(3,endpoint,Qweb_service_endpoint_binding,binding_name);
    address_element = xml_node_get_child_by_name(3,element,
	    array_constant_23,Wsdl_soap_xml_namespace_uri);
    if (address_element);
    else
	address_element = xml_node_get_child_by_name(3,element,
		array_constant_23,Wsdl_soap12_xml_namespace_uri);
    if (address_element);
    else
	address_element = xml_node_get_child_by_name(3,element,
		array_constant_23,Wsdl_http_xml_namespace_uri);
    if (address_element)
	change_slot_value(3,endpoint,Qweb_service_endpoint_address,
		xml_element_get_attribute(2,address_element,
		string_constant_93));
    return VALUES_1(endpoint);
}

static Object array_constant_24;   /* # */

/* IMPORT-WEB-SERVICE */
Object import_web_service(element)
    Object element;
{
    Object service, child, ab_list_, endpoints, ab_loopvar_, ab_loopvar__1;
    Object ab_node_;

    x_note_fn_call(242,108);
    service = make_entity(1,Qweb_service);
    set_frame_name_from_xml_element(service,element);
    change_slot_value(3,service,Qweb_service_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    child = Nil;
    ab_list_ = xml_node_child_nodes(element);
    endpoints = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    child = ab_node_;
    goto end_1;
    child = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop;
    if (xml_node_name_equals_p(3,child,array_constant_24,
	    Wsdl_xml_namespace_uri)) {
	ab_loopvar__1 = gensym_cons_1(import_web_service_endpoint(child),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    endpoints = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    ab_node_ = xml_node_next_sibling(child);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    child = ab_node_;
    goto end_2;
    child = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:
    add_items_to_web_service_subworkspace(endpoints,service);
    return VALUES_1(service);
}

static Object Qab_documentation;   /* documentation */

static Object Qtypes;              /* types */

static Object Qport_type;          /* port-type */

static Object Qbinding;            /* binding */

static Object Qservice;            /* service */

/* IMPORT-WEB-SERVICE-DESCRIPTION-CHILD */
Object import_web_service_description_child(element)
    Object element;
{
    Object gensymed_symbol, temp, gensymed_symbol_1;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(242,109);
    SAVE_STACK();
    result = xml_node_name_symbols(element);
    MVS_3(result,gensymed_symbol,temp,gensymed_symbol_1);
    if (equalw(gensymed_symbol_1,Wsdl_xml_namespace_uri)) {
	if (EQ(gensymed_symbol,Qab_documentation))
	    SAVE_VALUES(make_free_text_box_with_text(1,
		    convert_text_string_to_text(xml_node_get_content(element))));
	else if (EQ(gensymed_symbol,Qimport))
	    SAVE_VALUES(VALUES_1(Nil));
	else if (EQ(gensymed_symbol,Qtypes))
	    SAVE_VALUES(VALUES_1(Nil));
	else if (EQ(gensymed_symbol,Qmessage))
	    SAVE_VALUES(VALUES_1(Nil));
	else if (EQ(gensymed_symbol,Qport_type))
	    SAVE_VALUES(import_web_service_interface(element));
	else if (EQ(gensymed_symbol,Qbinding))
	    SAVE_VALUES(import_web_service_binding(element));
	else if (EQ(gensymed_symbol,Qservice))
	    SAVE_VALUES(import_web_service(element));
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    else
	SAVE_VALUES(VALUES_1(Qnil));
    if (gensymed_symbol_1)
	reclaim_text_string(gensymed_symbol_1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qweb_service_description_name;  /* web-service-description-name */

static Object string_constant_97;  /* "targetNamespace" */

/* IMPORT-WEB-SERVICE-DESCRIPTION */
Object import_web_service_description(element)
    Object element;
{
    Object description, child, ab_list_, item, items, ab_loopvar_;
    Object ab_loopvar__1, ab_node_;

    x_note_fn_call(242,110);
    description = make_entity(1,Qweb_service_description);
    set_frame_name_from_xml_element(description,element);
    change_slot_value(3,description,Qweb_service_description_name,
	    xml_element_get_attribute(2,element,string_constant_89));
    change_slot_value(3,description,Qweb_service_xml_namespace,
	    xml_element_get_attribute(2,element,string_constant_97));
    child = Nil;
    ab_list_ = xml_node_child_nodes(element);
    item = Nil;
    items = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    child = ab_node_;
    goto end_1;
    child = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop;
    item = import_web_service_description_child(child);
    if (item) {
	ab_loopvar__1 = gensym_cons_1(item,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    items = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    ab_node_ = xml_node_next_sibling(child);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    child = ab_node_;
    goto end_2;
    child = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:
    add_items_to_web_service_subworkspace(items,description);
    return VALUES_1(description);
}

static Object Qdefinitions;        /* definitions */

/* IMPORT-WEB-SERVICE-DESCRIPTION-FROM-DOCUMENT */
Object import_web_service_description_from_document(document)
    Object document;
{
    Object root, gensymed_symbol, temp, gensymed_symbol_1;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(242,111);
    SAVE_STACK();
    root = xml_document_root_element(document);
    if (root) {
	result = xml_node_name_symbols(root);
	MVS_3(result,gensymed_symbol,temp,gensymed_symbol_1);
	if (equalw(gensymed_symbol_1,Wsdl_xml_namespace_uri)) {
	    if (EQ(gensymed_symbol,Qdefinitions))
		SAVE_VALUES(import_web_service_description(root));
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
	if (gensymed_symbol_1)
	    reclaim_text_string(gensymed_symbol_1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object string_constant_98;  /* "Invalid WSDL." */

/* G2-IMPORT-WEB-SERVICE-DESCRIPTION-FROM-XML-TEXT */
Object g2_import_web_service_description_from_xml_text(document_text_as_evaluation_value)
    Object document_text_as_evaluation_value;
{
    Object document_text, value_1, current_xml_structures, document, errors;
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_, message_1, temp, description;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(8);
    Object result;

    x_note_fn_call(242,112);
    SAVE_STACK();
    document_text = document_text_as_evaluation_value;
    value_1 = Nil;
    LOCK(Xml_structures_extent);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_xml_structures = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_xml_structures,Qcurrent_xml_structures,current_xml_structures,
		7);
	  document = xml_read_string(document_text);
	  errors = xml_get_errors();
	  if ( !TRUEP(document)) {
	      top_of_stack = Cached_top_of_stack;
	      text_string = Nil;
	      snapshots = Nil;
	      snapshots_of_related_blocks = Nil;
	      note_blocks_in_tformat = 
		      SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	      PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		      6);
		PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			5);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    error_1 = Nil;
			    ab_loop_list_ = errors;
			  next_loop:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop;
			    error_1 = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    twrite_general_string(error_1);
			    goto next_loop;
			  end_loop:;
			    reclaim_gensym_tree_with_text_strings(errors);
			    text_string = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  snapshots = Snapshots_of_related_blocks;
		  Snapshots_of_related_blocks = Nil;
		  if (Snapshots_of_related_blocks) {
		      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		      Snapshots_of_related_blocks = Nil;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	      message_1 = make_error_text(text_string,snapshots);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  if (errors) {
	      snapshots_of_related_blocks = Nil;
	      note_blocks_in_tformat = 
		      SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	      PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		      6);
		PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			5);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    error_1 = Nil;
			    ab_loop_list_ = errors;
			  next_loop_1:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_1;
			    error_1 = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    twrite_general_string(error_1);
			    goto next_loop_1;
			  end_loop_1:;
			    reclaim_gensym_tree_with_text_strings(errors);
			    temp = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  notify_user_1(temp);
		  if (Snapshots_of_related_blocks) {
		      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		      Snapshots_of_related_blocks = Nil;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  description = import_web_service_description_from_document(document);
	  if ( !TRUEP(description)) {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(1,
		      string_constant_98);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  set_transient_and_propagate(description,Nil);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(description,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	  gensymed_symbol_1 = description;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	  temp = description;
	  reclaim_xml_structures(1,Current_xml_structures);
	  reclaim_gensym_list_1(Current_xml_structures);
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Xml_structures_extent);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    value_1 = result;
    reclaim_text_string(document_text_as_evaluation_value);
    temp = IDENTITY(value_1);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

void web_services_INIT()
{
    Object temp, reclaim_structure_for_uri_reference_1, gensymed_symbol;
    Object temp_1, http_server_port_evaluation_getter_1;
    Object Qg2_import_web_service_description_from_xml_text;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object list_constant_1, array_constant_36, Qwsdl_http_xml_namespace_uri;
    Object array_constant_35, Qwsdl_soap12_xml_namespace_uri;
    Object array_constant_34, Qwsdl_soap_xml_namespace_uri, array_constant_33;
    Object Qwsdl_xml_namespace_uri;
    Object Qg2_get_message_from_web_service_operation_response;
    Object Qg2_make_web_service_operation_invocation, string_constant_134;
    Object list_constant_35, string_constant_133, Qslot_value_writer;
    Object Qwrite_web_service_binding_name_from_slot, string_constant_132;
    Object string_constant_131, string_constant_130, string_constant_129;
    Object string_constant_128, string_constant_127, string_constant_126;
    Object list_constant_37, string_constant_125, string_constant_124;
    Object list_constant_36, string_constant_123, string_constant_122;
    Object Qwrite_http_method_from_slot, Qhttp_method, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, Qwrite_web_service_interface_name_from_slot;
    Object string_constant_116, string_constant_115, string_constant_114;
    Object string_constant_106;
    Object Qwrite_web_service_interface_message_reference_from_slot;
    Object Qweb_service_interface_message_reference;
    Object Qwrite_xml_ncname_from_slot, Qxml_ncname, string_constant_113;
    Object string_constant_112, string_constant_111, string_constant_110;
    Object string_constant_109, string_constant_108, Qweb_service_object;
    Object string_constant_107, list_constant_20;
    Object Qg2_make_http_response_from_soap_message;
    Object Qg2_make_soap_message_from_http_request;
    Object Qg2_make_soap_message_from_web_response;
    Object Qg2_make_web_request_from_soap_message, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_31;
    Object list_constant_30, list_constant_26, list_constant_25;
    Object list_constant_24, list_constant_4, list_constant_11;
    Object array_constant_32, array_constant_31, array_constant_30;
    Object array_constant_29, array_constant_28, array_constant_27;
    Object array_constant_26, array_constant_25, Qg2_format_web_request;
    Object Qg2_shutdown_http_server, Qg2_http_listen, list_constant_23;
    Object Qtype_specification_simple_expansion, list_constant_22;
    Object list_constant_21, Qab_or, Qno_item;
    Object Qwrite_http_server_port_from_slot, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object Qobject, Qg2_parse_http_chunk_header;
    Object Qmost_positive_fixnum_floor_16, Qg2_parse_http_response;
    Object Qg2_parse_http_request, Qg2_format_http_response, list_constant_19;
    Object list_constant_18, list_constant_17, list_constant_16;
    Object list_constant_15, list_constant_7, list_constant_14;
    Object list_constant_13, Qitem_or_datum, Quser_data, list_constant_12;
    Object Qentity_producer, Qprocedure, Qab_class, Qtext;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_10;
    Object list_constant_9, list_constant_8, list_constant_6, list_constant_5;
    Object list_constant_3, list_constant_2, Qwrite_uri_from_slot, Quri;
    Object string_constant_101, Quri_reference, Qreclaim_structure;
    Object Qoutstanding_uri_reference_count;
    Object Quri_reference_structure_memory_usage, Qutilities2;
    Object string_constant_100, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_99, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;

    x_note_fn_call(242,113);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_uri_reference_g2_struct = 
	    STATIC_SYMBOL("URI-REFERENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Quri_reference = STATIC_SYMBOL("URI-REFERENCE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_uri_reference_g2_struct,
	    Quri_reference,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Quri_reference,
	    Qg2_defstruct_structure_name_uri_reference_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_uri_reference == UNBOUND)
	The_type_description_of_uri_reference = Nil;
    string_constant_99 = 
	    STATIC_STRING("43Dy8m83oGy1n83oGy8n8k1l8n0000001l1n8y83-6Ey1r83-G*y83-G=y83-Fwy83-G+y83-Fxy83-G-y83-Fvyksk0k0");
    temp = The_type_description_of_uri_reference;
    The_type_description_of_uri_reference = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_99));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_uri_reference_g2_struct,
	    The_type_description_of_uri_reference,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Quri_reference,
	    The_type_description_of_uri_reference,Qtype_description_of_type);
    Qoutstanding_uri_reference_count = 
	    STATIC_SYMBOL("OUTSTANDING-URI-REFERENCE-COUNT",AB_package);
    Quri_reference_structure_memory_usage = 
	    STATIC_SYMBOL("URI-REFERENCE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_100 = STATIC_STRING("1q83oGy8s83-vby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_uri_reference_count);
    push_optimized_constant(Quri_reference_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_100));
    Qchain_of_available_uri_references = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-URI-REFERENCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_uri_references,
	    Chain_of_available_uri_references);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_uri_references,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Quri_reference_count = STATIC_SYMBOL("URI-REFERENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quri_reference_count,Uri_reference_count);
    record_system_variable(Quri_reference_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_uri_references_vector == UNBOUND)
	Chain_of_available_uri_references_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Quri_reference_structure_memory_usage,
	    STATIC_FUNCTION(uri_reference_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_uri_reference_count,
	    STATIC_FUNCTION(outstanding_uri_reference_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_uri_reference_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_uri_reference,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Quri_reference,
	    reclaim_structure_for_uri_reference_1);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING("~(~a~):");
    string_constant_1 = STATIC_STRING(":~d");
    string_constant_101 = STATIC_STRING("1l1m83=4y83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_101));
    Quri = STATIC_SYMBOL("URI",AB_package);
    Qwrite_uri_from_slot = STATIC_SYMBOL("WRITE-URI-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_uri_from_slot,
	    STATIC_FUNCTION(write_uri_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Quri,SYMBOL_FUNCTION(Qwrite_uri_from_slot),
	    Qslot_value_writer);
    string_constant_2 = STATIC_STRING("~a~a");
    string_constant_3 = STATIC_STRING("0");
    string_constant_4 = STATIC_STRING("");
    string_constant_5 = STATIC_STRING("~a, ");
    string_constant_6 = STATIC_STRING(" ~a ~a ");
    string_constant_7 = STATIC_STRING(":");
    string_constant_8 = STATIC_STRING(" GMT");
    string_constant_9 = STATIC_STRING("Unknown Status Code");
    string_constant_10 = STATIC_STRING("Continue");
    string_constant_11 = STATIC_STRING("Switching Protocols");
    string_constant_12 = STATIC_STRING("OK");
    string_constant_13 = STATIC_STRING("Created");
    string_constant_14 = STATIC_STRING("Accepted");
    string_constant_15 = STATIC_STRING("Non-Authoritative Information");
    string_constant_16 = STATIC_STRING("No Content");
    string_constant_17 = STATIC_STRING("Reset Content");
    string_constant_18 = STATIC_STRING("Partial Content");
    string_constant_19 = STATIC_STRING("Multiple Choices");
    string_constant_20 = STATIC_STRING("Moved Permanently");
    string_constant_21 = STATIC_STRING("Found");
    string_constant_22 = STATIC_STRING("See Other");
    string_constant_23 = STATIC_STRING("Not Modified");
    string_constant_24 = STATIC_STRING("Use Proxy");
    string_constant_25 = STATIC_STRING("Temporary Redirect");
    string_constant_26 = STATIC_STRING("Bad Request");
    string_constant_27 = STATIC_STRING("Unauthorized");
    string_constant_28 = STATIC_STRING("Payment Required");
    string_constant_29 = STATIC_STRING("Forbidden");
    string_constant_30 = STATIC_STRING("Not Found");
    string_constant_31 = STATIC_STRING("Method Not Allowed");
    string_constant_32 = STATIC_STRING("Not Acceptable");
    string_constant_33 = STATIC_STRING("Proxy Authentication Required");
    string_constant_34 = STATIC_STRING("Request Time-out");
    string_constant_35 = STATIC_STRING("Conflict");
    string_constant_36 = STATIC_STRING("Gone");
    string_constant_37 = STATIC_STRING("Length Required");
    string_constant_38 = STATIC_STRING("Precondition Failed");
    string_constant_39 = STATIC_STRING("Request Entity Too Large");
    string_constant_40 = STATIC_STRING("Request-URI Too Large");
    string_constant_41 = STATIC_STRING("Unsupported Media Type");
    string_constant_42 = STATIC_STRING("Requested range not satisfiable");
    string_constant_43 = STATIC_STRING("Expectation Failed");
    string_constant_44 = STATIC_STRING("Internal Server Error");
    string_constant_45 = STATIC_STRING("Not Implemented");
    string_constant_46 = STATIC_STRING("Bad Gateway");
    string_constant_47 = STATIC_STRING("Service Unavailable");
    string_constant_48 = STATIC_STRING("Gateway Time-out");
    string_constant_49 = STATIC_STRING("HTTP Version not supported");
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    Qpost = STATIC_SYMBOL("POST",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qmember,Qget,Qpost);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_method,list_constant_2);
    Qheaders = STATIC_SYMBOL("HEADERS",AB_package);
    list_constant_3 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_4 = STATIC_CONS(list_constant_3,Qnil);
    list_constant_7 = STATIC_CONS(Qheaders,list_constant_4);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_4);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qentity,list_constant_5);
    list_constant_9 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_7,list_constant_8);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_9);
    Http_request_type = list_constant_10;
    string_constant_50 = STATIC_STRING("application/x-www-form-urlencoded");
    Qscheme = STATIC_SYMBOL("SCHEME",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhost = STATIC_SYMBOL("HOST",AB_package);
    Qport = STATIC_SYMBOL("PORT",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_51 = STATIC_STRING("~a ");
    string_constant_52 = STATIC_STRING("\?~a");
    string_constant_53 = STATIC_STRING(" HTTP/1.1");
    string_constant_54 = STATIC_STRING("Connection: close");
    string_constant_55 = STATIC_STRING("Host: ~a");
    string_constant_56 = STATIC_STRING(":~a");
    string_constant_57 = STATIC_STRING("Content-Length: ~a");
    string_constant_58 = STATIC_STRING("Content-Type: ~a");
    string_constant_59 = STATIC_STRING("~a: ~a");
    Qstatus_code = STATIC_SYMBOL("STATUS-CODE",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qstatus_code,Qinteger);
    Qreason_phrase = STATIC_SYMBOL("REASON-PHRASE",AB_package);
    list_constant_11 = STATIC_CONS(Qtext,Qnil);
    list_constant_14 = STATIC_CONS(Qreason_phrase,list_constant_11);
    list_constant_15 = STATIC_CONS(Qentity,list_constant_11);
    Qentity_producer = STATIC_SYMBOL("ENTITY-PRODUCER",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qentity_producer,
	    list_constant_12);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Quser_data,Qitem_or_datum);
    list_constant_18 = STATIC_LIST((SI_Long)6L,list_constant_13,
	    list_constant_14,list_constant_7,list_constant_15,
	    list_constant_16,list_constant_17);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_18);
    Http_response_type = list_constant_19;
    Qg2_format_http_response = STATIC_SYMBOL("G2-FORMAT-HTTP-RESPONSE",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_format_http_response,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_60 = STATIC_STRING("HTTP/1.1 ~a ~a");
    string_constant_61 = STATIC_STRING("Date: ");
    SET_SYMBOL_FUNCTION(Qg2_format_http_response,
	    STATIC_FUNCTION(g2_format_http_response,NIL,FALSE,1,1));
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L));
    string_constant_62 = STATIC_STRING("~a ~a");
    Qcontent_length = STATIC_SYMBOL("CONTENT-LENGTH",AB_package);
    Qg2_parse_http_request = STATIC_SYMBOL("G2-PARSE-HTTP-REQUEST",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parse_http_request,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qrequest_uri = STATIC_SYMBOL("REQUEST-URI",AB_package);
    Qhttp_version = STATIC_SYMBOL("HTTP-VERSION",AB_package);
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    Qquery = STATIC_SYMBOL("QUERY",AB_package);
    Qtransfer_length = STATIC_SYMBOL("TRANSFER-LENGTH",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_parse_http_request,
	    STATIC_FUNCTION(g2_parse_http_request,NIL,FALSE,2,2));
    Qg2_parse_http_response = STATIC_SYMBOL("G2-PARSE-HTTP-RESPONSE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parse_http_response,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_parse_http_response,
	    STATIC_FUNCTION(g2_parse_http_response,NIL,FALSE,2,2));
    Qmost_positive_fixnum_floor_16 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-FLOOR-16",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_floor_16,
	    Most_positive_fixnum_floor_16);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_floor_16,
	    chestnut_floorf_function(Most_positive_fixnum,FIX((SI_Long)16L)));
    Qg2_parse_http_chunk_header = 
	    STATIC_SYMBOL("G2-PARSE-HTTP-CHUNK-HEADER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parse_http_chunk_header,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_63 = 
	    STATIC_STRING("HTTP chunk size is too large in header: ~a");
    string_constant_64 = 
	    STATIC_STRING("Failed to parse HTTP chunk header: ~a");
    SET_SYMBOL_FUNCTION(Qg2_parse_http_chunk_header,
	    STATIC_FUNCTION(g2_parse_http_chunk_header,NIL,FALSE,1,1));
    Qhttp_server = STATIC_SYMBOL("HTTP-SERVER",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_20 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qhttp_server,list_constant_20);
    string_constant_102 = 
	    STATIC_STRING("1o4z8r83Chy83Chy83Rby83Rby00001o1l8l1m8p83Chy1l83Fy1l83Hy000004z8r83Rcy83Rcy83Rby83Rby00001m1l8l1m8p8306y000004z8r83Rey83Rey83Rb");
    string_constant_103 = 
	    STATIC_STRING("y83Rby00001n1l8l1l83Fy1l83Hy000004z8r83Rdy83Rdy83Rby83Rby00001n1l8l1l83Fy1l83Hy00000");
    string_constant_104 = 
	    STATIC_STRING("1q8q1m83Rby1l83-Oy1p83Chy01m8p83Chy83Fy83Hy1n83Rcy01m8p8306y1o83Rey083Fy83Hy1o83Rdy083Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_102,
	    string_constant_103));
    add_class_to_environment(9,Qhttp_server,list_constant_20,Nil,temp,Nil,
	    temp_1,list_constant_20,
	    regenerate_optimized_constant(string_constant_104),Nil);
    string_constant_105 = STATIC_STRING("1m1n83Chy1m9k83Zy01m83Chy83-ey");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_105));
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qhttp_server_port = STATIC_SYMBOL("HTTP-SERVER-PORT",AB_package);
    Qwrite_http_server_port_from_slot = 
	    STATIC_SYMBOL("WRITE-HTTP-SERVER-PORT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_http_server_port_from_slot,
	    STATIC_FUNCTION(write_http_server_port_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qhttp_server_port,
	    SYMBOL_FUNCTION(Qwrite_http_server_port_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_21 = STATIC_CONS(Qno_item,Qnil);
    list_constant_22 = STATIC_CONS(Qinteger,Qnil);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_21,list_constant_22);
    set_property_value_function(get_symbol_properties_function(Qhttp_server_port),
	    Qtype_specification_simple_expansion,list_constant_23);
    define_type_specification_explicit_complex_type(Qhttp_server_port,
	    list_constant_23);
    http_server_port_evaluation_getter_1 = 
	    STATIC_FUNCTION(http_server_port_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qhttp_server_port,
	    http_server_port_evaluation_getter_1);
    Qhttp_server_listener = STATIC_SYMBOL("HTTP-SERVER-LISTENER",AB_package);
    Qhttp_server_invocation = STATIC_SYMBOL("HTTP-SERVER-INVOCATION",
	    AB_package);
    Qg2_http_listen = STATIC_SYMBOL("G2-HTTP-LISTEN",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_http_listen,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_http_listen,STATIC_FUNCTION(g2_http_listen,NIL,
	    FALSE,4,4));
    Qg2_shutdown_http_server = STATIC_SYMBOL("G2-SHUTDOWN-HTTP-SERVER",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_shutdown_http_server,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_shutdown_http_server,
	    STATIC_FUNCTION(g2_shutdown_http_server,NIL,FALSE,1,1));
    Qg2_format_web_request = STATIC_SYMBOL("G2-FORMAT-WEB-REQUEST",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_format_web_request,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qhttp = STATIC_SYMBOL("HTTP",AB_package);
    string_constant_65 = STATIC_STRING("URL has no scheme: ~a");
    string_constant_66 = STATIC_STRING("Unknown URL scheme: ~a");
    SET_SYMBOL_FUNCTION(Qg2_format_web_request,
	    STATIC_FUNCTION(g2_format_web_request,NIL,FALSE,2,2));
    Qtag_name = STATIC_SYMBOL("TAG-NAME",AB_package);
    Qns_prefix = STATIC_SYMBOL("NS-PREFIX",AB_package);
    Qns_uri = STATIC_SYMBOL("NS-URI",AB_package);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    Qchildren = STATIC_SYMBOL("CHILDREN",AB_package);
    Qxml_element_node = STATIC_SYMBOL("XML-ELEMENT-NODE",AB_package);
    Qxml_text_node = STATIC_SYMBOL("XML-TEXT-NODE",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)31L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)36L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)38L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)40L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)47L,(SI_Long)57344L);
    Soap_xml_namespace_uri = array_constant_25;
    array_constant_26 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)57344L);
    Soap_xml_namespace_prefix = array_constant_26;
    array_constant_27 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)24L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)25L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)29L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)33L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)35L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)47L,(SI_Long)57344L);
    Soap12_xml_namespace_uri = array_constant_27;
    array_constant_28 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)57344L);
    Soap12_xml_namespace_prefix = array_constant_28;
    array_constant_29 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)17L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)18L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)19L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)20L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)21L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)24L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)25L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)26L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)32L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)39L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)47L,(SI_Long)57344L);
    Xsi_xml_namespace_uri = array_constant_29;
    array_constant_30 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)57344L);
    Xsi_xml_namespace_prefix = array_constant_30;
    array_constant_31 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)19L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)20L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)21L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)24L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)25L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)26L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)39L,(SI_Long)57344L);
    Xsd_xml_namespace_uri = array_constant_31;
    array_constant_32 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)57344L);
    Xsd_xml_namespace_prefix = array_constant_32;
    array_constant_11 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    Qxmlns_col_soap = STATIC_SYMBOL("XMLNS:SOAP",AB_package);
    Qxmlns_col_soap12 = STATIC_SYMBOL("XMLNS:SOAP12",AB_package);
    Qxmlns_col_xsd = STATIC_SYMBOL("XMLNS:XSD",AB_package);
    Qxmlns_col_xsi = STATIC_SYMBOL("XMLNS:XSI",AB_package);
    array_constant_12 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Qnamespaces = STATIC_SYMBOL("NAMESPACES",AB_package);
    Qheader_entries = STATIC_SYMBOL("HEADER-ENTRIES",AB_package);
    Qbody_entries = STATIC_SYMBOL("BODY-ENTRIES",AB_package);
    string_constant_67 = STATIC_STRING("xmlns:~a");
    Qaction = STATIC_SYMBOL("ACTION",AB_package);
    list_constant_26 = STATIC_CONS(Qaction,list_constant_11);
    list_constant_27 = STATIC_CONS(Qnamespaces,list_constant_4);
    list_constant_24 = STATIC_CONS(Qsequence,Qnil);
    list_constant_25 = STATIC_CONS(list_constant_24,Qnil);
    list_constant_28 = STATIC_CONS(Qheader_entries,list_constant_25);
    list_constant_29 = STATIC_CONS(Qbody_entries,list_constant_25);
    list_constant_30 = STATIC_LIST((SI_Long)4L,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_30,Qbody_entries);
    Soap_request_type = list_constant_31;
    list_constant_32 = STATIC_LIST((SI_Long)3L,list_constant_27,
	    list_constant_28,list_constant_29);
    list_constant_33 = STATIC_CONS(Qbody_entries,Qnil);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_32,list_constant_33);
    Soap_response_type = list_constant_34;
    Qg2_make_web_request_from_soap_message = 
	    STATIC_SYMBOL("G2-MAKE-WEB-REQUEST-FROM-SOAP-MESSAGE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_web_request_from_soap_message,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_68 = 
	    STATIC_STRING("Not a well-formed SOAP message structure: ~NV");
    Qcontent_type = STATIC_SYMBOL("CONTENT-TYPE",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    Qsoapaction = STATIC_SYMBOL("SOAPACTION",AB_package);
    string_constant_69 = STATIC_STRING("~s");
    SET_SYMBOL_FUNCTION(Qg2_make_web_request_from_soap_message,
	    STATIC_FUNCTION(g2_make_web_request_from_soap_message,NIL,
	    FALSE,1,1));
    Qg2_make_soap_message_from_web_response = 
	    STATIC_SYMBOL("G2-MAKE-SOAP-MESSAGE-FROM-WEB-RESPONSE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_soap_message_from_web_response,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_70 = STATIC_STRING("Web error in SOAP response: ~a ~a");
    string_constant_71 = STATIC_STRING("SOAP response contains no entity.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_72 = 
	    STATIC_STRING("Failed to parse SOAP response message:~%");
    string_constant_73 = STATIC_STRING("SOAP response is empty or malformed.");
    SET_SYMBOL_FUNCTION(Qg2_make_soap_message_from_web_response,
	    STATIC_FUNCTION(g2_make_soap_message_from_web_response,NIL,
	    FALSE,1,1));
    Qg2_make_soap_message_from_http_request = 
	    STATIC_SYMBOL("G2-MAKE-SOAP-MESSAGE-FROM-HTTP-REQUEST",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_soap_message_from_http_request,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_74 = STATIC_STRING("SOAP request contains no entity.");
    string_constant_75 = 
	    STATIC_STRING("Failed to parse SOAP request message:~%");
    SET_SYMBOL_FUNCTION(Qg2_make_soap_message_from_http_request,
	    STATIC_FUNCTION(g2_make_soap_message_from_http_request,NIL,
	    FALSE,1,1));
    Qg2_make_http_response_from_soap_message = 
	    STATIC_SYMBOL("G2-MAKE-HTTP-RESPONSE-FROM-SOAP-MESSAGE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_http_response_from_soap_message,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_15 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_make_http_response_from_soap_message,
	    STATIC_FUNCTION(g2_make_http_response_from_soap_message,NIL,
	    FALSE,1,1));
    Qweb_service_object = STATIC_SYMBOL("WEB-SERVICE-OBJECT",AB_package);
    check_if_superior_classes_are_defined(Qweb_service_object,
	    list_constant_20);
    string_constant_106 = STATIC_STRING("1l1l83Iy");
    string_constant_107 = STATIC_STRING("1m8q1n831+y1l83-Oy83Iy");
    temp = regenerate_optimized_constant(string_constant_106);
    temp_1 = regenerate_optimized_constant(string_constant_3);
    add_class_to_environment(9,Qweb_service_object,list_constant_20,Nil,
	    temp,Nil,temp_1,list_constant_20,
	    regenerate_optimized_constant(string_constant_107),Nil);
    Qweb_service_interface = STATIC_SYMBOL("WEB-SERVICE-INTERFACE",AB_package);
    list_constant_35 = STATIC_CONS(Qweb_service_object,Qnil);
    check_if_superior_classes_are_defined(Qweb_service_interface,
	    list_constant_35);
    string_constant_108 = 
	    STATIC_STRING("1l4z8r834qy834qy836Ty836Ty00001m1l8l1m8p83*Vy00000");
    string_constant_109 = STATIC_STRING("1n8q1m836Ty1l831+y1n834qy01m8p83*Vy");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_108);
    add_class_to_environment(9,Qweb_service_interface,list_constant_35,Nil,
	    temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_109),Nil);
    Qweb_service_interface_operation = 
	    STATIC_SYMBOL("WEB-SERVICE-INTERFACE-OPERATION",AB_package);
    Qweb_service_interface_operation_name = 
	    STATIC_SYMBOL("WEB-SERVICE-INTERFACE-OPERATION-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qweb_service_interface_operation,
	    STATIC_FUNCTION(web_service_interface_operation,NIL,FALSE,2,2));
    check_if_superior_classes_are_defined(Qweb_service_interface_operation,
	    list_constant_35);
    string_constant_110 = 
	    STATIC_STRING("1n4z8r83eHy83eHy9k9k00001m1l8l1m8p83*Vy000004z8r83eGy83eGy9k9k00001m1l8l1m8p83Fsy000004z8r83eJy83eJy9k9k00001m1l8l1m8p83Fsy00000");
    string_constant_111 = 
	    STATIC_STRING("1p8q1m9k1l831+y1n83eHy01m8p83*Vy1n83eGy01m8p83Fsy1n83eJy01m8p83Fsy");
    temp = regenerate_optimized_constant(string_constant_3);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_interface_operation);
    temp_1 = regenerate_optimized_constant(string_constant_110);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_interface_operation);
    add_class_to_environment(9,Qweb_service_interface_operation,
	    list_constant_35,Nil,temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_111),Nil);
    string_constant_112 = 
	    STATIC_STRING("1m1n83Fsy83*Vy1ll1n83Fsy1m83*Vy83=4y1mlm");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_112));
    string_constant_113 = STATIC_STRING("1l1m83*Vy83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_113));
    Qxml_ncname = STATIC_SYMBOL("XML-NCNAME",AB_package);
    Qwrite_xml_ncname_from_slot = 
	    STATIC_SYMBOL("WRITE-XML-NCNAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_xml_ncname_from_slot,
	    STATIC_FUNCTION(write_xml_ncname_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qxml_ncname,
	    SYMBOL_FUNCTION(Qwrite_xml_ncname_from_slot),Qslot_value_writer);
    string_constant_76 = STATIC_STRING(" ~s");
    Qweb_service_interface_message_reference = 
	    STATIC_SYMBOL("WEB-SERVICE-INTERFACE-MESSAGE-REFERENCE",
	    AB_package);
    Qwrite_web_service_interface_message_reference_from_slot = 
	    STATIC_SYMBOL("WRITE-WEB-SERVICE-INTERFACE-MESSAGE-REFERENCE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_web_service_interface_message_reference_from_slot,
	    STATIC_FUNCTION(write_web_service_interface_message_reference_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qweb_service_interface_message_reference,
	    SYMBOL_FUNCTION(Qwrite_web_service_interface_message_reference_from_slot),
	    Qslot_value_writer);
    Qweb_service_binding = STATIC_SYMBOL("WEB-SERVICE-BINDING",AB_package);
    check_if_superior_classes_are_defined(Qweb_service_binding,
	    list_constant_35);
    string_constant_114 = 
	    STATIC_STRING("1m4z8r834py834py836Sy836Sy00001m1l8l1m8p83*Vy000004z8r836Ty836Ty836Sy836Sy00001m1l8l1m8p834qy00000");
    string_constant_115 = 
	    STATIC_STRING("1o8q1n836Sy1l831+y83Iy1n834py01m8p83*Vy1n836Ty01m8p834qy");
    temp = regenerate_optimized_constant(string_constant_106);
    temp_1 = regenerate_optimized_constant(string_constant_114);
    add_class_to_environment(9,Qweb_service_binding,list_constant_35,Nil,
	    temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_115),Nil);
    string_constant_116 = STATIC_STRING("1l1m834qy83*Vy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_116));
    Qweb_service_interface_name = 
	    STATIC_SYMBOL("WEB-SERVICE-INTERFACE-NAME",AB_package);
    Qwrite_web_service_interface_name_from_slot = 
	    STATIC_SYMBOL("WRITE-WEB-SERVICE-INTERFACE-NAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_web_service_interface_name_from_slot,
	    STATIC_FUNCTION(write_web_service_interface_name_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qweb_service_interface_name,
	    SYMBOL_FUNCTION(Qwrite_web_service_interface_name_from_slot),
	    Qslot_value_writer);
    Qweb_service_binding_operation = 
	    STATIC_SYMBOL("WEB-SERVICE-BINDING-OPERATION",AB_package);
    check_if_superior_classes_are_defined(Qweb_service_binding_operation,
	    list_constant_35);
    string_constant_117 = 
	    STATIC_STRING("1l4z8r83e5y83e5y9k9k00001m1l8l1m8p83*Vy00000");
    string_constant_118 = STATIC_STRING("1n8q1m9k1l831+y1n83e5y01m8p83*Vy");
    temp = regenerate_optimized_constant(string_constant_3);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_binding_operation);
    temp_1 = regenerate_optimized_constant(string_constant_117);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_binding_operation);
    add_class_to_environment(9,Qweb_service_binding_operation,
	    list_constant_35,Nil,temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_118),Nil);
    Qweb_service_binding_operation_name = 
	    STATIC_SYMBOL("WEB-SERVICE-BINDING-OPERATION-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qweb_service_binding_operation,
	    STATIC_FUNCTION(web_service_binding_operation,NIL,FALSE,2,2));
    Qweb_service_http_binding = STATIC_SYMBOL("WEB-SERVICE-HTTP-BINDING",
	    AB_package);
    list_constant_36 = STATIC_CONS(Qweb_service_binding,Qnil);
    check_if_superior_classes_are_defined(Qweb_service_http_binding,
	    list_constant_36);
    string_constant_119 = 
	    STATIC_STRING("1l4z8r83eDy83eDy83eCy83eCy09k001m1l8l1m8p83Cgy00000");
    string_constant_120 = 
	    STATIC_STRING("1n8q1m83eCy1l836Sy1n83eDy9k1m8p83Cgy");
    temp = regenerate_optimized_constant(string_constant_3);
    clear_optimized_constants();
    push_optimized_constant(Qget);
    temp_1 = regenerate_optimized_constant(string_constant_119);
    clear_optimized_constants();
    push_optimized_constant(Qget);
    add_class_to_environment(9,Qweb_service_http_binding,list_constant_36,
	    Nil,temp,Nil,temp_1,list_constant_36,
	    regenerate_optimized_constant(string_constant_120),Nil);
    string_constant_121 = STATIC_STRING("1m1m83Cgy1m9k9l1m83Cgy1m9k83-97y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qget);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_121));
    string_constant_77 = STATIC_STRING("~a");
    Qhttp_method = STATIC_SYMBOL("HTTP-METHOD",AB_package);
    Qwrite_http_method_from_slot = 
	    STATIC_SYMBOL("WRITE-HTTP-METHOD-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_http_method_from_slot,
	    STATIC_FUNCTION(write_http_method_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qhttp_method,
	    SYMBOL_FUNCTION(Qwrite_http_method_from_slot),Qslot_value_writer);
    Qweb_service_http_operation = 
	    STATIC_SYMBOL("WEB-SERVICE-HTTP-OPERATION",AB_package);
    list_constant_37 = STATIC_CONS(Qweb_service_binding_operation,Qnil);
    check_if_superior_classes_are_defined(Qweb_service_http_operation,
	    list_constant_37);
    string_constant_122 = 
	    STATIC_STRING("1l4z8r83eFy83eFy83eEy83eEy00001m1l8l1m8p83=4y00000");
    string_constant_123 = STATIC_STRING("1n8q1m83eEy1l9k1n83eFy01m8p83=4y");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_122);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_binding_operation);
    add_class_to_environment(9,Qweb_service_http_operation,
	    list_constant_37,Nil,temp,Nil,temp_1,list_constant_37,
	    regenerate_optimized_constant(string_constant_123),Nil);
    Qweb_service_soap_binding = STATIC_SYMBOL("WEB-SERVICE-SOAP-BINDING",
	    AB_package);
    check_if_superior_classes_are_defined(Qweb_service_soap_binding,
	    list_constant_36);
    string_constant_124 = STATIC_STRING("1m8q1m83-Gfy1l836Sy");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_3);
    add_class_to_environment(9,Qweb_service_soap_binding,list_constant_36,
	    Nil,temp,Nil,temp_1,list_constant_36,
	    regenerate_optimized_constant(string_constant_124),Nil);
    Qweb_service_soap_operation = 
	    STATIC_SYMBOL("WEB-SERVICE-SOAP-OPERATION",AB_package);
    check_if_superior_classes_are_defined(Qweb_service_soap_operation,
	    list_constant_37);
    string_constant_125 = 
	    STATIC_STRING("1l4z8r83eLy83eLy83eKy83eKy00001m1l8l1m8p83=4y00000");
    string_constant_126 = STATIC_STRING("1n8q1m83eKy1l9k1n83eLy01m8p83=4y");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_125);
    clear_optimized_constants();
    push_optimized_constant(Qweb_service_binding_operation);
    add_class_to_environment(9,Qweb_service_soap_operation,
	    list_constant_37,Nil,temp,Nil,temp_1,list_constant_37,
	    regenerate_optimized_constant(string_constant_126),Nil);
    Qweb_service = STATIC_SYMBOL("WEB-SERVICE",AB_package);
    check_if_superior_classes_are_defined(Qweb_service,list_constant_35);
    string_constant_127 = 
	    STATIC_STRING("1l4z8r83eIy83eIy83e4y83e4y00001m1l8l1m8p83*Vy00000");
    string_constant_128 = STATIC_STRING("1n8q1m83e4y1l831+y1n83eIy01m8p83*Vy");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_127);
    add_class_to_environment(9,Qweb_service,list_constant_35,Nil,temp,Nil,
	    temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_128),Nil);
    Qweb_service_endpoint = STATIC_SYMBOL("WEB-SERVICE-ENDPOINT",AB_package);
    check_if_superior_classes_are_defined(Qweb_service_endpoint,
	    list_constant_35);
    string_constant_129 = 
	    STATIC_STRING("1n4z8r83eBy83eBy83e8y83e8y00001m1l8l1m8p83*Vy000004z8r83eAy83eAy83e8y83e8y00001m1l8l1m8p834py000004z8r83e9y83e9y83e8y83e8y00001m");
    string_constant_130 = STATIC_STRING("1l8l1m8p83=4y00000");
    string_constant_131 = 
	    STATIC_STRING("1p8q1m83e8y1l831+y1n83eBy01m8p83*Vy1n83eAy01m8p834py1n83e9y01m8p83=4y");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_129,
	    string_constant_130));
    add_class_to_environment(9,Qweb_service_endpoint,list_constant_35,Nil,
	    temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_131),Nil);
    string_constant_132 = STATIC_STRING("1l1m834py83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_132));
    Qweb_service_binding_name = STATIC_SYMBOL("WEB-SERVICE-BINDING-NAME",
	    AB_package);
    Qwrite_web_service_binding_name_from_slot = 
	    STATIC_SYMBOL("WRITE-WEB-SERVICE-BINDING-NAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_web_service_binding_name_from_slot,
	    STATIC_FUNCTION(write_web_service_binding_name_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qweb_service_binding_name,
	    SYMBOL_FUNCTION(Qwrite_web_service_binding_name_from_slot),
	    Qslot_value_writer);
    Qweb_service_description = STATIC_SYMBOL("WEB-SERVICE-DESCRIPTION",
	    AB_package);
    check_if_superior_classes_are_defined(Qweb_service_description,
	    list_constant_35);
    string_constant_133 = 
	    STATIC_STRING("1m4z8r83e7y83e7y83e6y83e6y00001m1l8l1m8p83*Vy000004z8r83eMy83eMy83e6y83e6y00001m1l8l1m8p83=4y00000");
    string_constant_134 = 
	    STATIC_STRING("1o8q1m83e6y1l831+y1n83e7y01m8p83*Vy1n83eMy01m8p83=4y");
    temp = regenerate_optimized_constant(string_constant_3);
    temp_1 = regenerate_optimized_constant(string_constant_133);
    add_class_to_environment(9,Qweb_service_description,list_constant_35,
	    Nil,temp,Nil,temp_1,list_constant_35,
	    regenerate_optimized_constant(string_constant_134),Nil);
    Qendpoint_name = STATIC_SYMBOL("ENDPOINT-NAME",AB_package);
    Qweb_service_endpoint_name = STATIC_SYMBOL("WEB-SERVICE-ENDPOINT-NAME",
	    AB_package);
    Qservice_name = STATIC_SYMBOL("SERVICE-NAME",AB_package);
    Qservice_namespace = STATIC_SYMBOL("SERVICE-NAMESPACE",AB_package);
    Qweb_service_xml_namespace = STATIC_SYMBOL("WEB-SERVICE-XML-NAMESPACE",
	    AB_package);
    Qweb_service_name = STATIC_SYMBOL("WEB-SERVICE-NAME",AB_package);
    array_constant_16 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    Qxmlns = STATIC_SYMBOL("XMLNS",AB_package);
    Qg2_make_web_service_operation_invocation = 
	    STATIC_SYMBOL("G2-MAKE-WEB-SERVICE-OPERATION-INVOCATION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_web_service_operation_invocation,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_78 = STATIC_STRING("Input message ~NV is malformed.");
    string_constant_79 = 
	    STATIC_STRING("An endpoint cannot be determined from the endpoint reference ~NV.");
    Qweb_service_endpoint_binding = 
	    STATIC_SYMBOL("WEB-SERVICE-ENDPOINT-BINDING",AB_package);
    Qweb_service_endpoint_address = 
	    STATIC_SYMBOL("WEB-SERVICE-ENDPOINT-ADDRESS",AB_package);
    string_constant_80 = STATIC_STRING("Endpoint ~NF has no binding.");
    string_constant_81 = 
	    STATIC_STRING("The binding ~a of endpoint ~NF does not exist.");
    string_constant_82 = STATIC_STRING("Endpoint ~NF has no address.");
    string_constant_83 = STATIC_STRING("Binding ~NF is of unknown type ~NF.");
    SET_SYMBOL_FUNCTION(Qg2_make_web_service_operation_invocation,
	    STATIC_FUNCTION(g2_make_web_service_operation_invocation,NIL,
	    FALSE,3,3));
    string_constant_84 = 
	    STATIC_STRING("Input message part ~a is not a text: ~NV");
    Qweb_service_http_method = STATIC_SYMBOL("WEB-SERVICE-HTTP-METHOD",
	    AB_package);
    string_constant_85 = STATIC_STRING("Binding ~NF has no operation ~a.");
    Qweb_service_http_operation_location = 
	    STATIC_SYMBOL("WEB-SERVICE-HTTP-OPERATION-LOCATION",AB_package);
    Qsys_proc_name = STATIC_SYMBOL("SYS-PROC-NAME",AB_package);
    Qg2_send_web_request = STATIC_SYMBOL("G2-SEND-WEB-REQUEST",AB_package);
    Qurl = STATIC_SYMBOL("URL",AB_package);
    Qrequest = STATIC_SYMBOL("REQUEST",AB_package);
    string_constant_86 = 
	    STATIC_STRING("Interface ~a of binding ~NF does not exist.");
    Qweb_service_soap_operation_action = 
	    STATIC_SYMBOL("WEB-SERVICE-SOAP-OPERATION-ACTION",AB_package);
    string_constant_87 = STATIC_STRING("tns");
    Qweb_service_input_message = STATIC_SYMBOL("WEB-SERVICE-INPUT-MESSAGE",
	    AB_package);
    string_constant_88 = STATIC_STRING("Interface ~NF has no operation ~a.");
    Qg2_send_soap_request = STATIC_SYMBOL("G2-SEND-SOAP-REQUEST",AB_package);
    Qg2_get_message_from_web_service_operation_response = 
	    STATIC_SYMBOL("G2-GET-MESSAGE-FROM-WEB-SERVICE-OPERATION-RESPONSE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_message_from_web_service_operation_response,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_message_from_web_service_operation_response,
	    STATIC_FUNCTION(g2_get_message_from_web_service_operation_response,
	    NIL,FALSE,2,2));
    Qwsdl_xml_namespace_uri = STATIC_SYMBOL("WSDL-XML-NAMESPACE-URI",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwsdl_xml_namespace_uri,Wsdl_xml_namespace_uri);
    array_constant_33 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)26L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)31L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)39L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qwsdl_xml_namespace_uri,array_constant_33);
    Qwsdl_soap_xml_namespace_uri = 
	    STATIC_SYMBOL("WSDL-SOAP-XML-NAMESPACE-URI",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwsdl_soap_xml_namespace_uri,
	    Wsdl_soap_xml_namespace_uri);
    array_constant_34 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)26L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)31L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)35L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)36L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)39L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qwsdl_soap_xml_namespace_uri,array_constant_34);
    Qwsdl_soap12_xml_namespace_uri = 
	    STATIC_SYMBOL("WSDL-SOAP12-XML-NAMESPACE-URI",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwsdl_soap12_xml_namespace_uri,
	    Wsdl_soap12_xml_namespace_uri);
    array_constant_35 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)26L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)31L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)35L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)36L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)37L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)38L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)47L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qwsdl_soap12_xml_namespace_uri,array_constant_35);
    Qwsdl_http_xml_namespace_uri = 
	    STATIC_SYMBOL("WSDL-HTTP-XML-NAMESPACE-URI",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwsdl_http_xml_namespace_uri,
	    Wsdl_http_xml_namespace_uri);
    array_constant_36 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)26L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)31L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)32L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)35L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)36L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)39L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qwsdl_http_xml_namespace_uri,array_constant_36);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    array_constant_17 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    string_constant_89 = STATIC_STRING("name");
    string_constant_90 = STATIC_STRING("message");
    array_constant_18 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    string_constant_91 = STATIC_STRING("element");
    array_constant_19 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    Qweb_service_output_message = 
	    STATIC_SYMBOL("WEB-SERVICE-OUTPUT-MESSAGE",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)57344L);
    Qsoap = STATIC_SYMBOL("SOAP",AB_package);
    Qsoap12 = STATIC_SYMBOL("SOAP12",AB_package);
    string_constant_92 = STATIC_STRING("soapAction");
    string_constant_93 = STATIC_STRING("location");
    string_constant_94 = STATIC_STRING("verb");
    string_constant_95 = STATIC_STRING("type");
    string_constant_96 = STATIC_STRING("binding");
    array_constant_23 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)57344L);
    Qab_documentation = STATIC_SYMBOL("DOCUMENTATION",AB_package);
    Qtypes = STATIC_SYMBOL("TYPES",AB_package);
    Qport_type = STATIC_SYMBOL("PORT-TYPE",AB_package);
    Qbinding = STATIC_SYMBOL("BINDING",AB_package);
    Qservice = STATIC_SYMBOL("SERVICE",AB_package);
    Qweb_service_description_name = 
	    STATIC_SYMBOL("WEB-SERVICE-DESCRIPTION-NAME",AB_package);
    string_constant_97 = STATIC_STRING("targetNamespace");
    Qdefinitions = STATIC_SYMBOL("DEFINITIONS",AB_package);
    Qg2_import_web_service_description_from_xml_text = 
	    STATIC_SYMBOL("G2-IMPORT-WEB-SERVICE-DESCRIPTION-FROM-XML-TEXT",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_import_web_service_description_from_xml_text,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_98 = STATIC_STRING("Invalid WSDL.");
    SET_SYMBOL_FUNCTION(Qg2_import_web_service_description_from_xml_text,
	    STATIC_FUNCTION(g2_import_web_service_description_from_xml_text,
	    NIL,FALSE,1,1));
}
