/* alphbt.c
 * Input file:  alphabet.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "alphbt.h"


/* GENSYM-SET-DIFFERENCE-USING-EQUAL */
Object gensym_set_difference_using_equal(list1,list2)
    Object list1, list2;
{
    Object element1, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object element2, ab_loop_list__1, ab_loop_it_, temp_1;
    char temp;

    x_note_fn_call(30,0);
    element1 = Nil;
    ab_loop_list_ = list1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element2 = Nil;
    ab_loop_list__1 = list2;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    element2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQUAL(element1,element2) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	ab_loopvar__2 = gensym_cons_1(element1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* GENSYM-INTERSECTION-USING-EQUAL */
Object gensym_intersection_using_equal(list1,list2)
    Object list1, list2;
{
    Object element1, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object element2, ab_loop_list__1, ab_loop_it_, temp_1;
    char temp;

    x_note_fn_call(30,1);
    element1 = Nil;
    ab_loop_list_ = list1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element2 = Nil;
    ab_loop_list__1 = list2;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    element2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQUAL(element1,element2) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	ab_loopvar__2 = gensym_cons_1(element1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* GENSYM-SET-DIFFERENCE-USING-EQUAL-NON-EMPTY-P */
Object gensym_set_difference_using_equal_non_empty_p(list1,list2)
    Object list1, list2;
{
    Object element1, ab_loop_list_, element2, ab_loop_list__1, ab_loop_it_;
    Object temp_1;
    char temp;

    x_note_fn_call(30,2);
    element1 = Nil;
    ab_loop_list_ = list1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element2 = Nil;
    ab_loop_list__1 = list2;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    element2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQUAL(element1,element2) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	temp_1 = T;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* GENSYM-INTERSECTION-USING-EQUAL-NON-EMPTY-P */
Object gensym_intersection_using_equal_non_empty_p(list1,list2)
    Object list1, list2;
{
    Object element1, ab_loop_list_, element2, ab_loop_list__1, ab_loop_it_;
    Object temp_1;
    char temp;

    x_note_fn_call(30,3);
    element1 = Nil;
    ab_loop_list_ = list1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element2 = Nil;
    ab_loop_list__1 = list2;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    element2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQUAL(element1,element2) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	temp_1 = T;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

static Object Qdisjoint;           /* disjoint */

static Object Qequiv;              /* equiv */

static Object Qab_sub1;            /* sub1 */

static Object Qsub2;               /* sub2 */

static Object Qrange_overlap;      /* range-overlap */

/* CHARACTER-CLASS-RELATIONSHIP */
Object character_class_relationship(args1,args2)
    Object args1, args2;
{
    Object args1_only, args2_only, intersection_1, temp;

    x_note_fn_call(30,4);
    args1_only = gensym_set_difference_using_equal_non_empty_p(args1,args2);
    args2_only = gensym_set_difference_using_equal_non_empty_p(args2,args1);
    intersection_1 = gensym_intersection_using_equal_non_empty_p(args1,args2);
    if ( !TRUEP(intersection_1))
	temp = Qdisjoint;
    else if ( !TRUEP(args1_only))
	temp =  !TRUEP(args2_only) ? Qequiv : Qab_sub1;
    else if ( !TRUEP(args2_only))
	temp = Qsub2;
    else
	temp = Qrange_overlap;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Valid_token_actions, Qvalid_token_actions);

/* NO-VALUE */
Object no_value(string_1,start,end_1)
    Object string_1, start, end_1;
{
    x_note_fn_call(30,5);
    return VALUES_1(Nil);
}

static Object Qoverflow;           /* overflow */

static Object array_constant;      /* # */

static Object Qunderflow;          /* underflow */

static Object array_constant_1;    /* # */

static Object Qlong;               /* long */

/* NUMERIC-RETURN-VALUE */
Object numeric_return_value(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object wide_string_bv16, result_1, gensymed_symbol, gensymed_symbol_2;
    Object number_string, value_or_error_string, type_of_number, value, temp;
    SI_Long part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(30,6);
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
    gensymed_symbol = string_1;
    gensymed_symbol_1 = IFIX(start);
    gensymed_symbol_2 = result_1;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_4 = part_length;
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    number_string = result_1;
    value_or_error_string = Nil;
    type_of_number = Nil;
    value = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = tokenize_number_from_user(number_string,FIX((SI_Long)0L),
		text_string_length(number_string));
	MVS_2(result,value,type_of_number);
	if (EQ(value,Qoverflow))
	    value_or_error_string = array_constant;
	else if (EQ(value,Qunderflow))
	    value_or_error_string = array_constant_1;
	else if (EQ(type_of_number,Qfloat))
	    value_or_error_string = make_runtime_float_for_tokenizer(value);
	else if (EQ(type_of_number,Qlong))
	    value_or_error_string = make_runtime_long_for_tokenizer(value);
	else
	    value_or_error_string = value;
	reclaim_wide_string(number_string);
	temp = value_or_error_string;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

Object Alphabet_min_character = UNBOUND;

Object Alphabet_max_character = UNBOUND;

Object Alphabet_min_code = UNBOUND;

Object Alphabet_max_code = UNBOUND;

Object Alphabet_cardinality = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_standard_state_transition_tests, Qalphabet_standard_state_transition_tests);

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_count_of_standard_state_transition_tests, Qalphabet_count_of_standard_state_transition_tests);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_already_defined_tokenizer_matching_tests, Qlist_of_already_defined_tokenizer_matching_tests);

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_canonical_element_st_test, Qalphabet_canonical_element_st_test);

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_equality_st_test, Qalphabet_equality_st_test);

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_character_class_st_test, Qalphabet_character_class_st_test);

Object Alphabet_preds_with_card_gt_2 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_subset_function, Qalphabet_subset_function);

Object Alphabet_valid_subset_responses = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Alphabet_members, Qalphabet_members);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* ALPHABET-SUBSTRING-FOR-SYMBOL-FUNCTION */
Object alphabet_substring_for_symbol_function(string_1,start,end_1,normalize_p)
    Object string_1, start, end_1, normalize_p;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object end_2, char_1, char_to_write_qm, code, temp, temp_1, aref_arg_2_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(5);

    x_note_fn_call(30,7);
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
	      end_2 = end_1;
	      i = IFIX(start);
	      char_1 = Nil;
	      char_to_write_qm = Nil;
	    next_loop:
	      if ( !(i < IFIX(end_2)))
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
	      if (IFIX(char_1) == (SI_Long)64L) {
		  i = i + (SI_Long)1L;
		  char_to_write_qm =  !(i == IFIX(end_1)) ? 
			  FIX(UBYTE_16_ISAREF_1(string_1,i)) : Nil;
	      }
	      else if (normalize_p) {
		  code = char_1;
		  if (IFIX(code) < (SI_Long)127L)
		      char_to_write_qm = (SI_Long)97L <= IFIX(code) && 
			      IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) 
			      + (SI_Long)-32L) : code;
		  else {
		      temp = unicode_uppercase_if_lowercase(code);
		      if (temp);
		      else
			  temp = code;
		      char_to_write_qm = temp;
		  }
	      }
	      else
		  char_to_write_qm = char_1;
	      if (char_to_write_qm) {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp_1 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),
			  IFIX(char_to_write_qm));
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp_1;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qgensym_string;      /* gensym-string */

static Object Knil;                /* :nil */

static Object Qnumeric;            /* numeric */

static Object Qtype_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

/* ALPHABET-NORMALIZED-SYMBOL-FROM-TEXT-STRING */
Object alphabet_normalized_symbol_from_text_string(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object number_parsing_state, possibly_numeric_p, index_1, next_char;
    Object using_string_buffer_p, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object end_2, char_1, char_to_write_qm, code, temp, code_1, temp_2, temp_3;
    Object wide_character_code, extended_code, unicode, row;
    Object gensym_character_code_qm, gensym_character_code, extended_code_qm;
    Object simple_gensym_character_code, character_or_character_code;
    Object escape_character_qm, thing, schar_new_value, kanji_code, octet_1_qm;
    Object quotient, remainder_1, simple_or_wide_character, gensymed_symbol_2;
    Object result_1;
    SI_Long i, gensym_full_row, gensymed_symbol, gensymed_symbol_1, octet_2;
    SI_Long octet_3, thing_1, simple_or_wide_character_1;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(30,8);
    number_parsing_state = Nil;
    possibly_numeric_p = T;
    index_1 = FIX((SI_Long)0L);
    next_char = Nil;
    using_string_buffer_p = T;
    current_gensym_string = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    4);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      3);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		2);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  1);
	    end_2 = end_1;
	    i = IFIX(start);
	    char_1 = Nil;
	    char_to_write_qm = Nil;
	  next_loop:
	    if ( !(i < IFIX(end_2)))
		goto end_loop;
	    char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
	    if (IFIX(char_1) == (SI_Long)64L) {
		i = i + (SI_Long)1L;
		char_to_write_qm =  !(i == IFIX(end_1)) ? 
			FIX(UBYTE_16_ISAREF_1(string_1,i)) : Nil;
	    }
	    else {
		code = char_1;
		if (IFIX(code) < (SI_Long)127L)
		    char_to_write_qm = (SI_Long)97L <= IFIX(code) && 
			    IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) + 
			    (SI_Long)-32L) : code;
		else {
		    temp = unicode_uppercase_if_lowercase(code);
		    if (temp);
		    else
			temp = code;
		    char_to_write_qm = temp;
		}
	    }
	    if (char_to_write_qm) {
		next_char = char_to_write_qm;
		if (using_string_buffer_p && FIXNUM_LT(index_1,
			Intern_string_buffer_length)) {
		    code_1 = next_char;
		    temp_1 = IFIX(code_1) < (SI_Long)127L ?  
			    !((SI_Long)64L == IFIX(code_1) || 
			    (SI_Long)126L == IFIX(code_1) || (SI_Long)92L 
			    == IFIX(code_1)) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp_2 = Intern_string_buffer;
		    temp_3 = CODE_CHAR(next_char);
		    SET_CHAR(temp_2,index_1,temp_3);
		}
		else {
		    if (using_string_buffer_p) {
			using_string_buffer_p = Nil;
			Current_gensym_string = 
				obtain_simple_gensym_string(FIX((SI_Long)2048L));
			twrite_intern_string_buffer_as_gensym_characters(index_1);
		    }
		    wide_character_code = next_char;
		    code = Nil;
		    extended_code = Nil;
		    unicode = wide_character_code;
		    extended_code = Nil;
		    code_1 = unicode;
		    if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == 
			    IFIX(code_1) || (SI_Long)126L == IFIX(code_1) 
			    || (SI_Long)92L == IFIX(code_1))) {
			code = unicode;
			temp = code;
		    }
		    else {
			row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
			PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			  gensym_full_row = 
				  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				  IFIX(Row));
			  if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			      gensymed_symbol = gensym_full_row << (SI_Long)8L;
			      gensymed_symbol_1 = (SI_Long)255L & 
				      IFIX(unicode);
			      gensym_character_code_qm = 
				      FIX(gensymed_symbol + gensymed_symbol_1);
			  }
			  else
			      gensym_character_code_qm = Nil;
			POP_SPECIAL();
			if (gensym_character_code_qm) {
			    temp_1 = IFIX(gensym_character_code_qm) < 
				    (SI_Long)256L ? 
				    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(gensym_character_code_qm))) : 
				    TRUEP(Nil);
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
				temp_1 = (SI_Long)8192L <= 
					IFIX(gensym_character_code_qm) ? 
					IFIX(gensym_character_code_qm) <= 
					(SI_Long)8447L : TRUEP(Qnil);
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
			    code = 
				    map_unicode_to_gensym_han_character_code(unicode);
			    temp = code;
			    if (temp);
			    else {
				row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
				PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				  gensym_full_row = 
					  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
					  IFIX(Row));
				  if ( !(gensym_full_row == 
					  IFIX(Invalid_gensym_full_row))) {
				      gensymed_symbol = gensym_full_row << 
					      (SI_Long)8L;
				      gensymed_symbol_1 = (SI_Long)255L & 
					      IFIX(unicode);
				      code = FIX(gensymed_symbol + 
					      gensymed_symbol_1);
				  }
				  else
				      code = Nil;
				POP_SPECIAL();
				temp = code;
				if (temp);
				else {
				    gensymed_symbol = (SI_Long)63488L;
				    gensymed_symbol_1 = (SI_Long)255L & 
					    IFIX(unicode);
				    extended_code = FIX(gensymed_symbol + 
					    gensymed_symbol_1);
				    code = FIX((SI_Long)63232L + 
					    (IFIX(unicode) >>  -  - 
					    (SI_Long)8L));
				    temp = code;
				}
			    }
			}
		    }
		    result = VALUES_2(temp,extended_code);
		    MVS_2(result,gensym_character_code,extended_code_qm);
		    char_1 = Nil;
		    if (FIXNUM_EQ(gensym_character_code,
			    Gensym_code_for_linebreak))
			result = VALUES_2(Gensym_char_or_code_for_linebreak,
				Gensym_esc_for_linebreak_qm);
		    else if (FIXNUM_EQ(gensym_character_code,
			    Gensym_code_for_paragraph_break))
			result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				Gensym_esc_for_paragraph_break_qm);
		    else {
			if ((SI_Long)32L <= IFIX(gensym_character_code) && 
				IFIX(gensym_character_code) <= (SI_Long)126L) {
			    simple_gensym_character_code = 
				    gensym_character_code;
			    temp_1 =  
				    !(FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)64L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)126L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)92L)));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = CODE_CHAR(gensym_character_code);
			    result = VALUES_2(temp,Nil);
			}
			else {
			    temp = IFIX(gensym_character_code) < 
				    (SI_Long)256L ? 
				    ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(gensym_character_code)) : Nil;
			    if (temp);
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_capital_ligature_oe))
				temp = CHR('W');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_small_ligature_oe))
				temp = CHR('w');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_bullet))
				temp = CHR('*');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_small_letter_f_with_hook))
				temp = CHR('&');
			    else if (FIXNUM_EQ(gensym_character_code,
				    Gensym_code_for_trade_mark_sign))
				temp = CHR(':');
			    else
				temp = Qnil;
			    char_1 = temp;
			    if (char_1)
				result = VALUES_2(char_1,CHR('~'));
			    else
				result = VALUES_2(gensym_character_code,
					CHR('\\'));
			}
		    }
		    MVS_2(result,character_or_character_code,
			    escape_character_qm);
		    if ( !TRUEP(escape_character_qm)) {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
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
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = (SI_Long)92L;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			code_1 = kanji_code;
			result = chestnut_floorf_function(FIX(IFIX(code_1) 
				& (SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  
				- (SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
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
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = escape_character_qm;
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
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
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
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    if (extended_code_qm) {
			char_1 = Nil;
			if (FIXNUM_EQ(extended_code_qm,
				Gensym_code_for_linebreak))
			    result = VALUES_2(Gensym_char_or_code_for_linebreak,
				    Gensym_esc_for_linebreak_qm);
			else if (FIXNUM_EQ(extended_code_qm,
				Gensym_code_for_paragraph_break))
			    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				    Gensym_esc_for_paragraph_break_qm);
			else {
			    if ((SI_Long)32L <= IFIX(extended_code_qm) && 
				    IFIX(extended_code_qm) <= (SI_Long)126L) {
				simple_gensym_character_code = 
					extended_code_qm;
				temp_1 =  
					!(FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)64L)) || 
					FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)126L)) || 
					FIXNUM_EQ(simple_gensym_character_code,
					FIX((SI_Long)92L)));
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1) {
				temp = CODE_CHAR(extended_code_qm);
				result = VALUES_2(temp,Nil);
			    }
			    else {
				temp = IFIX(extended_code_qm) < 
					(SI_Long)256L ? 
					ISVREF(Iso_latin1_special_character_code_map,
					IFIX(extended_code_qm)) : Nil;
				if (temp);
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_capital_ligature_oe))
				    temp = CHR('W');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_small_ligature_oe))
				    temp = CHR('w');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_bullet))
				    temp = CHR('*');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_small_letter_f_with_hook))
				    temp = CHR('&');
				else if (FIXNUM_EQ(extended_code_qm,
					Gensym_code_for_trade_mark_sign))
				    temp = CHR(':');
				else
				    temp = Qnil;
				char_1 = temp;
				if (char_1)
				    result = VALUES_2(char_1,CHR('~'));
				else
				    result = VALUES_2(extended_code_qm,
					    CHR('\\'));
			    }
			}
			MVS_2(result,character_or_character_code,
				escape_character_qm);
			if ( !TRUEP(escape_character_qm)) {
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = character_or_character_code;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = character_or_character_code;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			    kanji_code = character_or_character_code;
			    octet_1_qm = Nil;
			    octet_2 = (SI_Long)0L;
			    octet_3 = (SI_Long)0L;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = (SI_Long)92L;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = (SI_Long)92L;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    code_1 = kanji_code;
			    result = chestnut_floorf_function(FIX(IFIX(code_1) 
				    & (SI_Long)8191L),FIX((SI_Long)95L));
			    MVS_2(result,quotient,remainder_1);
			    octet_2 = IFIX(quotient) + (SI_Long)40L;
			    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			    octet_1_qm =  !(IFIX(code_1) >>  -  - 
				    (SI_Long)13L == (SI_Long)1L) ? 
				    FIX((IFIX(code_1) >>  -  - 
				    (SI_Long)13L) + (SI_Long)32L) : Nil;
			    if (octet_1_qm) {
				simple_or_wide_character = octet_1_qm;
				if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				    thing = simple_or_wide_character;
				    twrite_wide_character(CHARACTERP(thing) 
					    ? CHAR_CODE(thing) : thing);
				}
				else {
				    if ( 
					    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					    Total_length_of_current_gensym_string))
					extend_current_gensym_string(0);
				    temp_2 = Current_gensym_string;
				    temp_3 = 
					    Fill_pointer_for_current_gensym_string;
				    thing = simple_or_wide_character;
				    schar_new_value = 
					    CODE_CHAR(CHARACTERP(thing) ? 
					    CHAR_CODE(thing) : thing);
				    SET_SCHAR(temp_2,temp_3,schar_new_value);
				    temp_2 = 
					    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				    Fill_pointer_for_current_gensym_string 
					    = temp_2;
				}
			    }
			    simple_or_wide_character_1 = octet_2;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = simple_or_wide_character_1;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = simple_or_wide_character_1;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    simple_or_wide_character_1 = octet_3;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing_1 = simple_or_wide_character_1;
				twrite_wide_character(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing_1 = simple_or_wide_character_1;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(FIX(thing_1)) 
					? CHAR_CODE(FIX(thing_1)) : 
					FIX(thing_1));
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			else {
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = escape_character_qm;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = escape_character_qm;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = character_or_character_code;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = character_or_character_code;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
		    }
		}
		index_1 = FIXNUM_ADD1(index_1);
		if (possibly_numeric_p) {
		    gensymed_symbol = IFIX(char_to_write_qm);
		    if ((SI_Long)48L <= gensymed_symbol && gensymed_symbol 
			    <= (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
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
			if (EQ(char_to_write_qm,FIX((SI_Long)45L)))
			    number_parsing_state = FIX((SI_Long)1L);
			else if (EQ(char_to_write_qm,FIX((SI_Long)46L)))
			    number_parsing_state = FIX((SI_Long)3L);
			else
			    number_parsing_state = Qnil;
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)1L)))
			number_parsing_state = EQ(char_to_write_qm,
				FIX((SI_Long)46L)) ? FIX((SI_Long)3L) : Nil;
		    else if (EQ(number_parsing_state,FIX((SI_Long)2L))) {
			if (EQ(char_to_write_qm,FIX((SI_Long)46L)))
			    number_parsing_state = FIX((SI_Long)4L);
			else if ( !TRUEP(Nil) && (IFIX(char_to_write_qm) 
				== (SI_Long)101L || IFIX(char_to_write_qm) 
				== (SI_Long)69L))
			    number_parsing_state = FIX((SI_Long)5L);
			else if (EQ(char_to_write_qm,FIX((SI_Long)45L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)39L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_to_write_qm;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qinteger;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)4L))) {
			if ( !TRUEP(Nil) && (IFIX(char_to_write_qm) == 
				(SI_Long)101L || IFIX(char_to_write_qm) == 
				(SI_Long)69L))
			    number_parsing_state = FIX((SI_Long)5L);
			else if (EQ(char_to_write_qm,FIX((SI_Long)46L)))
			    number_parsing_state = Nil;
			else if (EQ(char_to_write_qm,FIX((SI_Long)45L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)39L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_to_write_qm;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qfloat;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else if (EQ(number_parsing_state,FIX((SI_Long)5L)))
			number_parsing_state = EQ(char_to_write_qm,
				FIX((SI_Long)43L)) || EQ(char_to_write_qm,
				FIX((SI_Long)45L)) ? FIX((SI_Long)6L) : Nil;
		    else if (EQ(number_parsing_state,FIX((SI_Long)7L))) {
			if (EQ(char_to_write_qm,FIX((SI_Long)46L)))
			    number_parsing_state = Nil;
			else if (EQ(char_to_write_qm,FIX((SI_Long)45L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)39L)) || 
				EQ(char_to_write_qm,FIX((SI_Long)95L)))
			    number_parsing_state = Nil;
			else {
			    gensymed_symbol_2 = char_to_write_qm;
			    if ( !((SI_Long)97L <= IFIX(gensymed_symbol_2) 
				    && IFIX(gensymed_symbol_2) <= 
				    (SI_Long)122L || (SI_Long)65L <= 
				    IFIX(gensymed_symbol_2) && 
				    IFIX(gensymed_symbol_2) <= (SI_Long)90L))
				number_parsing_state = Qfloat;
			    else
				number_parsing_state = Qnil;
			}
		    }
		    else
			number_parsing_state = Qnil;
		    possibly_numeric_p = FIXNUMP(number_parsing_state) ? T 
			    : Nil;
		}
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    result_1 = using_string_buffer_p ? 
		    intern_using_string_buffer(Intern_string_buffer,
		    index_1,Nil) : intern_gensym_string(2,
		    copy_out_current_gensym_string(),Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (result_1);
    else
	result_1 = Knil;
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
	    temp_1 = TRUEP(Qinteger);
	else if (EQ(number_parsing_state,Qfloat))
	    temp_1 = TRUEP(Qfloat);
	else
	    temp_1 = TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	mutate_global_property(result_1,Qnumeric,Qtype_of_syntactic_anomaly);
    return VALUES_1(result_1);
}

/* ALPHABET-CASE-SENSITIVE-SYMBOL-FROM-TEXT-STRING */
Object alphabet_case_sensitive_symbol_from_text_string(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object end_2, temp, char_1, char_to_write_qm, temp_1, code, temp_2;
    Object aref_arg_2_1, result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(5);

    x_note_fn_call(30,9);
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
	      end_2 = end_1;
	      if (end_2);
	      else {
		  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		  end_2 = FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
			  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L));
	      }
	      temp = start;
	      if (temp);
	      else
		  temp = FIX((SI_Long)0L);
	      i = IFIX(temp);
	      char_1 = Nil;
	      char_to_write_qm = Nil;
	    next_loop:
	      if ( !(i < IFIX(end_2)))
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
	      if (IFIX(char_1) == (SI_Long)64L) {
		  i = i + (SI_Long)1L;
		  temp_1 = FIX(i);
		  temp = end_1;
		  if (temp);
		  else {
		      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		      temp = FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
			      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		  }
		  char_to_write_qm =  !NUM_EQ(temp_1,temp) ? 
			  FIX(UBYTE_16_ISAREF_1(string_1,i)) : Nil;
	      }
	      else if (Nil) {
		  code = char_1;
		  if (IFIX(code) < (SI_Long)127L)
		      char_to_write_qm = (SI_Long)97L <= IFIX(code) && 
			      IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) 
			      + (SI_Long)-32L) : code;
		  else {
		      temp = unicode_uppercase_if_lowercase(code);
		      if (temp);
		      else
			  temp = code;
		      char_to_write_qm = temp;
		  }
	      }
	      else
		  char_to_write_qm = char_1;
	      if (char_to_write_qm) {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp_2 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),
			  IFIX(char_to_write_qm));
		  temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp_2;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    result_1 = intern_wide_string(1,temp);
    if (result_1);
    else
	result_1 = Knil;
    if (syntactically_numeric_p(symbol_name_text_string(result_1)))
	mutate_global_property(result_1,Qnumeric,Qtype_of_syntactic_anomaly);
    return VALUES_1(result_1);
}

/* ALPHABET-STRIP-DELIMITORS-OFF-STRING */
Object alphabet_strip_delimitors_off_string(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object i, char_1, temp_1, aref_arg_2, temp_2;
    SI_Long bv16_length, temp, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(30,10);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      i = FIXNUM_ADD1(start);
	      char_1 = Nil;
	    next_loop:
	      if (FIXNUM_GE(i,FIXNUM_SUB1(end_1)))
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(i)));
	      if (IFIX(char_1) == (SI_Long)64L) {
		  i = FIXNUM_ADD1(i);
		  if ( !FIXNUM_EQ(i,FIXNUM_SUB1(end_1))) {
		      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			      Total_length_of_current_wide_string))
			  extend_current_wide_string(Fill_pointer_for_current_wide_string);
		      temp_1 = Current_wide_string;
		      aref_arg_2 = Fill_pointer_for_current_wide_string;
		      temp = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		      UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),temp);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		      Fill_pointer_for_current_wide_string = temp_1;
		  }
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp_1 = Current_wide_string;
		  aref_arg_2 = Fill_pointer_for_current_wide_string;
		  UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),IFIX(char_1));
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp_1;
	      }
	      i = FIXNUM_ADD1(i);
	      goto next_loop;
	    end_loop:;
	      temp_2 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_2);
}

/* ALPHABET-SUBSTRING-FUNCTION */
Object alphabet_substring_function(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object wide_string_bv16, result_1, gensymed_symbol, gensymed_symbol_2;
    SI_Long part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(30,11);
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
    gensymed_symbol = string_1;
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

Object Alphabet_not_character_code_error_message = UNBOUND;

Object Alphabet_escape_character = UNBOUND;

Object Alphabet_character_class_open = UNBOUND;

Object Alphabet_character_class_close = UNBOUND;

Object Alphabet_character_class_range = UNBOUND;

Object Alphabet_dollar_sign = UNBOUND;

Object Alphabet_less_than_sign = UNBOUND;

Object Alphabet_alphabetic_chars = UNBOUND;

Object Alphabet_numeric_chars = UNBOUND;

Object Alphabet_hexadecimal_chars = UNBOUND;

Object Alphabet_g2symbol_chars = UNBOUND;

Object Alphabet_alphanumeric_chars = UNBOUND;

Object Alphabet_whitespace_chars = UNBOUND;

Object Alphabet_double_quote_chars = UNBOUND;

Object Alphabet_left_bracket_chars = UNBOUND;

Object Alphabet_right_bracket_chars = UNBOUND;

Object Alphabet_editor_legal_whitespace_chars = UNBOUND;

Object Alphabet_zero_width_characters = UNBOUND;

Object Alphabet_whitespace_characters = UNBOUND;

Object Alphabet_punctuation_characters = UNBOUND;

Object Sentence_end_punctuation_characters = UNBOUND;

Object Characters_not_allowed_in_symbols_in_g2_50r0 = UNBOUND;

Object Alphabet_nonsymbol_character_codes_sorted_by_encoding = UNBOUND;

Object Alphabet_illegal_codes_character_class = UNBOUND;

Object Alphabet_symbol_character_class = UNBOUND;

Object Generally_ambiguous_characters_in_g2_tokenization = UNBOUND;

Object G2_standard_tokens_head = UNBOUND;

Object G2_standard_tokens_middle_strings = UNBOUND;

Object G2_standard_tokens_middle_1 = UNBOUND;

Object G2_standard_tokens_tail = UNBOUND;

Object G2_standard_tokens = UNBOUND;

Object G2_comment_recognizing_tokens = UNBOUND;

Object G2_simple_tokens = UNBOUND;

Object Load_kb_tokens = UNBOUND;

Object G2_symbol_tokens = UNBOUND;

Object Tokenizer_tokens = UNBOUND;

Object Regular_expression_tokens = UNBOUND;

Object Regexp_macro_tokens = UNBOUND;

Object Module_search_path_tokens = UNBOUND;

Object Tabular_view_row_selection_tokens = UNBOUND;

void alphabet_INIT()
{
    Object temp, push_arg, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object character_constant_name, ab_loop_list_, temp_1, first_char;
    Object result_1, number1, number2, diff, temp_2;
    SI_Long i;
    Object list_constant_229, list_constant_228, list_constant_227;
    Object list_constant_219, list_constant_100, list_constant_226;
    Object list_constant_225, Qab_plus, list_constant_224, Qinverted_class;
    Object list_constant_212, list_constant_6, list_constant_73;
    Object list_constant_223, Qunsigned_integer, list_constant_144, AB_package;
    Object list_constant_222, list_constant_221, list_constant_220;
    Object list_constant_152, list_constant_218, Qunquoted_path;
    Object list_constant_217, list_constant_62, list_constant_216;
    Object Qquoted_path, list_constant_213, list_constant_215, Qseq;
    Object list_constant_214, Qkleene, Qdo_nothing, list_constant_211;
    Object list_constant_210, list_constant_209, list_constant_208;
    Object list_constant_207, Qcharacter_class, list_constant_101;
    Object list_constant_206, list_constant_205, list_constant_204;
    Object list_constant_187, Qeither, list_constant_203, list_constant_191;
    Object list_constant_202, list_constant_201, list_constant_200;
    Object list_constant_199, list_constant_198, list_constant_197;
    Object list_constant_196, Qbuilt_in, list_constant_195, list_constant_194;
    Object list_constant_193, list_constant_192, list_constant_190;
    Object list_constant_189, list_constant_181, list_constant_182;
    Object list_constant_180, list_constant_179, list_constant_176;
    Object list_constant_175, list_constant_178, list_constant_177;
    Object list_constant_172, list_constant_174, list_constant_173;
    Object list_constant_188, Qregexp_character, list_constant_186;
    Object list_constant_30, list_constant_185, list_constant_184;
    Object list_constant_183, list_constant_171, list_constant_153;
    Object list_constant_170, list_constant_169, list_constant_54;
    Object list_constant_168, list_constant_167, Qquoted_character, Qcaret;
    Object list_constant_32, Qhyphen, Qright_curly_brace, Qleft_curly_brace;
    Object Qright_paren, Qleft_paren, Qquestion_mark, Qkleene_star;
    Object Qalternative, list_constant_166, Qab_dot, list_constant_14;
    Object Qdouble_quote, list_constant_165, list_constant_164, Qsymbol_char;
    Object list_constant_163, list_constant_118, list_constant_92;
    Object list_constant_162, list_constant_161, list_constant_160;
    Object list_constant_113, Qdouble_colon, list_constant_84;
    Object list_constant_72, list_constant_159, list_constant_148;
    Object list_constant_127, list_constant_158, list_constant_46;
    Object list_constant_45, list_constant_142, list_constant_50;
    Object list_constant_48, list_constant_47, list_constant_157;
    Object list_constant_156, list_constant_155, list_constant_154;
    Object list_constant_119, list_constant_151;
    Object Qself_terminating_punctuation_mark, Qalphabet_substring_function;
    Object list_constant_150, list_constant_20, list_constant_149;
    Object list_constant_147, list_constant_129, list_constant_146;
    Object list_constant_42, list_constant_145, Qdigit, list_constant_31;
    Object list_constant_135, list_constant_134, list_constant_143;
    Object list_constant_49, list_constant_141, Qab_string_char;
    Object list_constant_140, list_constant_139, list_constant_138;
    Object list_constant_137, Qg2_comment, list_constant_136;
    Object list_constant_128, list_constant_133, Qdisambiguated_token;
    Object list_constant_132, list_constant_131, list_constant_106;
    Object list_constant_130, list_constant_126, list_constant_103;
    Object list_constant_125, list_constant_98, list_constant_96;
    Object list_constant_124, Qwhitespace_char, Qpattern, Qillegal_character;
    Object list_constant_123, list_constant_122, list_constant_121;
    Object list_constant_120, list_constant_117, list_constant_116;
    Object Qpunctuation_mark, list_constant_115, list_constant_114;
    Object list_constant_108, list_constant_112, list_constant_111;
    Object list_constant_110, list_constant_109, list_constant_107;
    Object list_constant_105, Qcomment, list_constant_104, list_constant_102;
    Object list_constant_99, Qsingle_line_comment, list_constant_97;
    Object list_constant_95, Qwhole_string, list_constant_94, list_constant_58;
    Object list_constant_93, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_88, list_constant_87;
    Object list_constant_86, list_constant_85, list_constant_39;
    Object list_constant_70, Qlong_mark, list_constant_83, list_constant_82;
    Object list_constant_81, list_constant_80, list_constant_79;
    Object list_constant_78, list_constant_77, list_constant_75, Qmaybe;
    Object list_constant_76, list_constant_36, list_constant_74;
    Object Qexponent_part, Qnumeric_return_value, list_constant_71;
    Object Qoptional_unary_minus, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_65, Qright_string;
    Object list_constant_63, list_constant_64, Qmiddle_string;
    Object list_constant_60, Qclose_bracket_character, list_constant_61;
    Object Qleft_string, Qalphabet_strip_delimitors_off_string;
    Object list_constant_59, Qopen_bracket_character, list_constant_57;
    Object list_constant_56, list_constant_55, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_16;
    Object list_constant_15, list_constant_44, list_constant_43;
    Object list_constant_41, list_constant_40, list_constant_38;
    Object list_constant_37, Qoptional_sign, list_constant_35;
    Object list_constant_34, list_constant_33, list_constant_7;
    Object list_constant_29, list_constant_28, list_constant_27, Qcbt;
    Object list_constant_26, list_constant_25, Qpct_bq, Qpct_no;
    Object Qpct_inverted_question_mark;
    Object Qpct_left_pointing_double_angle_quotation_mark;
    Object Qpct_right_pointing_double_angle_quotation_mark, Qpct_yen_sign;
    Object Qpct_pound_sign, Qpct_cent_sign, Qpct_inverted_exclamation_point;
    Object Qpct_latin_small_letter_f_with_hook, Qpct_bullet;
    Object Qpct_trade_mark_sign, Qpct_registered_sign, Qpct_copyright_sign;
    Object list_constant_24, list_constant_23, Qpct_cb, Qpct_or, Qpct_ob;
    Object Qpct_ct, Qpct_cbt, Qpct_bs, Qpct_obt, Qpct_at, Qpct_qm, Qpct_gt;
    Object Qpct_eq, Qpct_lt, Qpct_sc, Qpct_col, Qpct_sl, Qpct_cm, Qpct_plus;
    Object Qpct_star, Qpct_cp, Qpct_op, Qpct_and, Qpct_pct, Qpct_dol, Qpct_dq;
    Object Qpct_ex, Qpct_paragraph_separator, Qpct_line_separator, Qpct_space;
    Object Qpct_tab, Qpct_tl, list_constant_22, list_constant_21;
    Object list_constant_19, Qalphabet_whitespace_characters, list_constant_18;
    Object Qalphabet_zero_width_characters, list_constant_17;
    Object Qalphabet_editor_legal_whitespace_chars, list_constant_13;
    Object list_constant_12, list_constant_5, list_constant_11;
    Object list_constant_4, list_constant_3, list_constant_10, list_constant_9;
    Object list_constant_8, Qalphabet_case_sensitive_symbol_from_text_string;
    Object Qalphabet_normalized_symbol_from_text_string, list_constant_2;
    Object Qalphabet_valid_subset_responses, Qoverlap;
    Object Qalphabet_transition_relationship, list_constant_1;
    Object Qgraphic_char_pw_function, Qlower_case_pw_function;
    Object Qupper_case_pw_function, Qstandard_char_pw_function;
    Object Qstring_char_pw_function, Qdecimal_digit_char_pw_function;
    Object Qhexadecimal_digit_char_pw_function, Qalpha_char_pw_function;
    Object Qalphanumericpw_function, Qwide_character_p;
    Object Qwide_character_p_function, Qcharacter_class_member_p;
    Object Qalphabet_character_class, Qchar_eq_w, Qalphabet_equality;
    Object Qalphabet_canonical_element, list_constant;

    x_note_fn_call(30,12);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdisjoint = STATIC_SYMBOL("DISJOINT",AB_package);
    Qequiv = STATIC_SYMBOL("EQUIV",AB_package);
    Qab_sub1 = STATIC_SYMBOL("SUB1",AB_package);
    Qsub2 = STATIC_SYMBOL("SUB2",AB_package);
    Qrange_overlap = STATIC_SYMBOL("RANGE-OVERLAP",AB_package);
    if (Valid_token_actions == UNBOUND)
	Valid_token_actions = Qnil;
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qno_value,STATIC_FUNCTION(no_value,NIL,FALSE,3,3));
    temp = CONS(Qno_value,Valid_token_actions);
    Valid_token_actions = temp;
    Qoverflow = STATIC_SYMBOL("OVERFLOW",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qunderflow = STATIC_SYMBOL("UNDERFLOW",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qnumeric_return_value = STATIC_SYMBOL("NUMERIC-RETURN-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qnumeric_return_value,
	    STATIC_FUNCTION(numeric_return_value,NIL,FALSE,3,3));
    temp = CONS(Qnumeric_return_value,Valid_token_actions);
    Valid_token_actions = temp;
    Alphabet_min_character = FIX((SI_Long)0L);
    Alphabet_max_character = FIX((SI_Long)65535L);
    Alphabet_min_code = Alphabet_min_character;
    Alphabet_max_code = Alphabet_max_character;
    Alphabet_cardinality = FIXNUM_MINUS(Alphabet_max_code,Alphabet_min_code);
    if (Alphabet_standard_state_transition_tests == UNBOUND)
	Alphabet_standard_state_transition_tests = Qnil;
    if (Alphabet_count_of_standard_state_transition_tests == UNBOUND)
	Alphabet_count_of_standard_state_transition_tests = FIX((SI_Long)0L);
    if (List_of_already_defined_tokenizer_matching_tests == UNBOUND)
	List_of_already_defined_tokenizer_matching_tests = Qnil;
    Qalphabet_canonical_element = 
	    STATIC_SYMBOL("ALPHABET-CANONICAL-ELEMENT",AB_package);
    Qwide_character_p = STATIC_SYMBOL("WIDE-CHARACTER-P",AB_package);
    if ( !TRUEP(member_eql(Qalphabet_canonical_element,
	    List_of_already_defined_tokenizer_matching_tests))) {
	push_arg = 
		LIST_3(Alphabet_count_of_standard_state_transition_tests,
		Qwide_character_p,FIX((SI_Long)1L));
	temp = CONS(push_arg,Alphabet_standard_state_transition_tests);
	Alphabet_standard_state_transition_tests = temp;
	temp = FIXNUM_ADD1(Alphabet_count_of_standard_state_transition_tests);
	Alphabet_count_of_standard_state_transition_tests = temp;
	temp = CONS(Qalphabet_canonical_element,
		List_of_already_defined_tokenizer_matching_tests);
	List_of_already_defined_tokenizer_matching_tests = temp;
    }
    if (Alphabet_canonical_element_st_test == UNBOUND)
	Alphabet_canonical_element_st_test = Qwide_character_p;
    Qalphabet_equality = STATIC_SYMBOL("ALPHABET-EQUALITY",AB_package);
    Qchar_eq_w = STATIC_SYMBOL("CHAR=W",AB_package);
    if ( !TRUEP(member_eql(Qalphabet_equality,
	    List_of_already_defined_tokenizer_matching_tests))) {
	push_arg = 
		LIST_3(Alphabet_count_of_standard_state_transition_tests,
		Qchar_eq_w,FIX((SI_Long)2L));
	temp = CONS(push_arg,Alphabet_standard_state_transition_tests);
	Alphabet_standard_state_transition_tests = temp;
	temp = FIXNUM_ADD1(Alphabet_count_of_standard_state_transition_tests);
	Alphabet_count_of_standard_state_transition_tests = temp;
	temp = CONS(Qalphabet_equality,
		List_of_already_defined_tokenizer_matching_tests);
	List_of_already_defined_tokenizer_matching_tests = temp;
    }
    if (Alphabet_equality_st_test == UNBOUND)
	Alphabet_equality_st_test = Qchar_eq_w;
    Qalphabet_character_class = STATIC_SYMBOL("ALPHABET-CHARACTER-CLASS",
	    AB_package);
    Qcharacter_class_member_p = STATIC_SYMBOL("CHARACTER-CLASS-MEMBER-P",
	    AB_package);
    if ( !TRUEP(member_eql(Qalphabet_character_class,
	    List_of_already_defined_tokenizer_matching_tests))) {
	push_arg = 
		LIST_3(Alphabet_count_of_standard_state_transition_tests,
		Qcharacter_class_member_p,FIX((SI_Long)2L));
	temp = CONS(push_arg,Alphabet_standard_state_transition_tests);
	Alphabet_standard_state_transition_tests = temp;
	temp = FIXNUM_ADD1(Alphabet_count_of_standard_state_transition_tests);
	Alphabet_count_of_standard_state_transition_tests = temp;
	temp = CONS(Qalphabet_character_class,
		List_of_already_defined_tokenizer_matching_tests);
	List_of_already_defined_tokenizer_matching_tests = temp;
    }
    if (Alphabet_character_class_st_test == UNBOUND)
	Alphabet_character_class_st_test = Qcharacter_class_member_p;
    Qwide_character_p_function = STATIC_SYMBOL("WIDE-CHARACTER-P-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwide_character_p_function,
	    STATIC_FUNCTION(wide_character_p_function,NIL,FALSE,1,1));
    Qalphanumericpw_function = STATIC_SYMBOL("ALPHANUMERICPW-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qalphanumericpw_function,
	    STATIC_FUNCTION(alphanumericpw_function,NIL,FALSE,1,1));
    Qalpha_char_pw_function = STATIC_SYMBOL("ALPHA-CHAR-PW-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qalpha_char_pw_function,
	    STATIC_FUNCTION(alpha_char_pw_function,NIL,FALSE,1,1));
    Qhexadecimal_digit_char_pw_function = 
	    STATIC_SYMBOL("HEXADECIMAL-DIGIT-CHAR-PW-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qhexadecimal_digit_char_pw_function,
	    STATIC_FUNCTION(hexadecimal_digit_char_pw_function,NIL,FALSE,1,1));
    Qdecimal_digit_char_pw_function = 
	    STATIC_SYMBOL("DECIMAL-DIGIT-CHAR-PW-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qdecimal_digit_char_pw_function,
	    STATIC_FUNCTION(decimal_digit_char_pw_function,NIL,FALSE,1,1));
    Qstring_char_pw_function = STATIC_SYMBOL("STRING-CHAR-PW-FUNCTION",
	    AB_package);
    Qstandard_char_pw_function = STATIC_SYMBOL("STANDARD-CHAR-PW-FUNCTION",
	    AB_package);
    Qupper_case_pw_function = STATIC_SYMBOL("UPPER-CASE-PW-FUNCTION",
	    AB_package);
    Qlower_case_pw_function = STATIC_SYMBOL("LOWER-CASE-PW-FUNCTION",
	    AB_package);
    Qgraphic_char_pw_function = STATIC_SYMBOL("GRAPHIC-CHAR-PW-FUNCTION",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)11L,Qwide_character_p_function,
	    Qwide_character_p,Qalphanumericpw_function,
	    Qalpha_char_pw_function,Qhexadecimal_digit_char_pw_function,
	    Qdecimal_digit_char_pw_function,Qstring_char_pw_function,
	    Qstandard_char_pw_function,Qupper_case_pw_function,
	    Qlower_case_pw_function,Qgraphic_char_pw_function);
    Alphabet_preds_with_card_gt_2 = list_constant_1;
    Qalphabet_transition_relationship = 
	    STATIC_SYMBOL("ALPHABET-TRANSITION-RELATIONSHIP",AB_package);
    if (Alphabet_subset_function == UNBOUND)
	Alphabet_subset_function = Qalphabet_transition_relationship;
    Qalphabet_valid_subset_responses = 
	    STATIC_SYMBOL("ALPHABET-VALID-SUBSET-RESPONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalphabet_valid_subset_responses,
	    Alphabet_valid_subset_responses);
    Qoverlap = STATIC_SYMBOL("OVERLAP",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)6L,Qequiv,Qab_sub1,Qsub2,
	    Qdisjoint,Qoverlap,Qrange_overlap);
    SET_SYMBOL_VALUE(Qalphabet_valid_subset_responses,list_constant_2);
    if (Alphabet_members == UNBOUND) {
	i = IFIX(Alphabet_min_code);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i > (SI_Long)127L)
	    goto end_loop;
	ab_loopvar__2 = LIST_1(FIX(i));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	Alphabet_members = ab_loopvar_;
	goto end_1;
	Alphabet_members = Qnil;
      end_1:;
    }
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    Qalphabet_normalized_symbol_from_text_string = 
	    STATIC_SYMBOL("ALPHABET-NORMALIZED-SYMBOL-FROM-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qalphabet_normalized_symbol_from_text_string,
	    STATIC_FUNCTION(alphabet_normalized_symbol_from_text_string,
	    NIL,FALSE,3,3));
    temp = CONS(Qalphabet_normalized_symbol_from_text_string,
	    Valid_token_actions);
    Valid_token_actions = temp;
    Qalphabet_case_sensitive_symbol_from_text_string = 
	    STATIC_SYMBOL("ALPHABET-CASE-SENSITIVE-SYMBOL-FROM-TEXT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qalphabet_case_sensitive_symbol_from_text_string,
	    STATIC_FUNCTION(alphabet_case_sensitive_symbol_from_text_string,
	    NIL,FALSE,3,3));
    temp = CONS(Qalphabet_case_sensitive_symbol_from_text_string,
	    Valid_token_actions);
    Valid_token_actions = temp;
    Qalphabet_strip_delimitors_off_string = 
	    STATIC_SYMBOL("ALPHABET-STRIP-DELIMITORS-OFF-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qalphabet_strip_delimitors_off_string,
	    STATIC_FUNCTION(alphabet_strip_delimitors_off_string,NIL,FALSE,
	    3,3));
    temp = CONS(Qalphabet_strip_delimitors_off_string,Valid_token_actions);
    Valid_token_actions = temp;
    Qalphabet_substring_function = 
	    STATIC_SYMBOL("ALPHABET-SUBSTRING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qalphabet_substring_function,
	    STATIC_FUNCTION(alphabet_substring_function,NIL,FALSE,3,3));
    temp = CONS(Qalphabet_substring_function,Valid_token_actions);
    Valid_token_actions = temp;
    Alphabet_not_character_code_error_message = format((SI_Long)4L,Nil,
	    "Character codes must be fixnums between ~d and ~d inclusive.",
	    Alphabet_min_code,Alphabet_max_code);
    Alphabet_escape_character = FIX((SI_Long)92L);
    Alphabet_character_class_open = FIX((SI_Long)123L);
    Alphabet_character_class_close = FIX((SI_Long)125L);
    Alphabet_character_class_range = FIX((SI_Long)45L);
    Alphabet_dollar_sign = FIX((SI_Long)36L);
    Alphabet_less_than_sign = FIX((SI_Long)60L);
    list_constant_3 = STATIC_CONS(FIX((SI_Long)97L),FIX((SI_Long)122L));
    list_constant_4 = STATIC_CONS(FIX((SI_Long)65L),FIX((SI_Long)90L));
    list_constant_5 = STATIC_LIST((SI_Long)2L,list_constant_3,list_constant_4);
    Alphabet_alphabetic_chars = list_constant_5;
    list_constant_6 = STATIC_CONS(FIX((SI_Long)48L),FIX((SI_Long)57L));
    list_constant_7 = STATIC_CONS(list_constant_6,Qnil);
    Alphabet_numeric_chars = list_constant_7;
    list_constant_8 = STATIC_CONS(FIX((SI_Long)97L),FIX((SI_Long)102L));
    list_constant_9 = STATIC_CONS(FIX((SI_Long)65L),FIX((SI_Long)70L));
    list_constant_10 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_8,list_constant_9);
    Alphabet_hexadecimal_chars = list_constant_10;
    list_constant_11 = STATIC_LIST((SI_Long)7L,list_constant_6,
	    list_constant_3,list_constant_4,FIX((SI_Long)45L),
	    FIX((SI_Long)95L),FIX((SI_Long)39L),FIX((SI_Long)46L));
    Alphabet_g2symbol_chars = list_constant_11;
    list_constant_12 = STATIC_CONS(list_constant_6,list_constant_5);
    Alphabet_alphanumeric_chars = list_constant_12;
    list_constant_13 = STATIC_LIST((SI_Long)7L,FIX((SI_Long)8232L),
	    FIX((SI_Long)32L),FIX((SI_Long)10L),FIX((SI_Long)13L),
	    FIX((SI_Long)10L),FIX((SI_Long)8233L),FIX((SI_Long)9L));
    Alphabet_whitespace_chars = list_constant_13;
    list_constant_14 = STATIC_CONS(FIX((SI_Long)34L),Qnil);
    Alphabet_double_quote_chars = list_constant_14;
    list_constant_15 = STATIC_CONS(FIX((SI_Long)91L),Qnil);
    Alphabet_left_bracket_chars = list_constant_15;
    list_constant_16 = STATIC_CONS(FIX((SI_Long)93L),Qnil);
    Alphabet_right_bracket_chars = list_constant_16;
    Qalphabet_editor_legal_whitespace_chars = 
	    STATIC_SYMBOL("ALPHABET-EDITOR-LEGAL-WHITESPACE-CHARS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalphabet_editor_legal_whitespace_chars,
	    Alphabet_editor_legal_whitespace_chars);
    list_constant_17 = STATIC_LIST((SI_Long)8L,FIX((SI_Long)8232L),
	    FIX((SI_Long)13L),FIX((SI_Long)10L),FIX((SI_Long)8202L),
	    FIX((SI_Long)9L),FIX((SI_Long)8201L),FIX((SI_Long)8194L),
	    FIX((SI_Long)8193L));
    SET_SYMBOL_VALUE(Qalphabet_editor_legal_whitespace_chars,list_constant_17);
    Qalphabet_zero_width_characters = 
	    STATIC_SYMBOL("ALPHABET-ZERO-WIDTH-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalphabet_zero_width_characters,
	    Alphabet_zero_width_characters);
    list_constant_18 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)8203L),
	    FIX((SI_Long)8205L));
    SET_SYMBOL_VALUE(Qalphabet_zero_width_characters,list_constant_18);
    Qalphabet_whitespace_characters = 
	    STATIC_SYMBOL("ALPHABET-WHITESPACE-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalphabet_whitespace_characters,
	    Alphabet_whitespace_characters);
    list_constant_19 = STATIC_LIST((SI_Long)12L,FIX((SI_Long)8232L),
	    FIX((SI_Long)13L),FIX((SI_Long)10L),FIX((SI_Long)8202L),
	    FIX((SI_Long)9L),FIX((SI_Long)8201L),FIX((SI_Long)8194L),
	    FIX((SI_Long)8193L),FIX((SI_Long)8203L),FIX((SI_Long)8205L),
	    FIX((SI_Long)8233L),FIX((SI_Long)32L));
    SET_SYMBOL_VALUE(Qalphabet_whitespace_characters,list_constant_19);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)126L),Qnil);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)32L,FIX((SI_Long)60L),
	    FIX((SI_Long)62L),FIX((SI_Long)47L),FIX((SI_Long)43L),
	    FIX((SI_Long)58L),FIX((SI_Long)123L),FIX((SI_Long)125L),
	    FIX((SI_Long)34L),FIX((SI_Long)33L),FIX((SI_Long)35L),
	    FIX((SI_Long)36L),FIX((SI_Long)37L),FIX((SI_Long)38L),
	    FIX((SI_Long)39L),FIX((SI_Long)40L),FIX((SI_Long)41L),
	    FIX((SI_Long)42L),FIX((SI_Long)44L),FIX((SI_Long)45L),
	    FIX((SI_Long)46L),FIX((SI_Long)59L),FIX((SI_Long)61L),
	    FIX((SI_Long)63L),FIX((SI_Long)64L),FIX((SI_Long)91L),
	    FIX((SI_Long)92L),FIX((SI_Long)93L),FIX((SI_Long)94L),
	    FIX((SI_Long)95L),FIX((SI_Long)96L),FIX((SI_Long)124L),
	    list_constant_20);
    Alphabet_punctuation_characters = list_constant_21;
    list_constant_22 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)63L),
	    FIX((SI_Long)46L),FIX((SI_Long)33L));
    Sentence_end_punctuation_characters = list_constant_22;
    Qpct_tab = STATIC_SYMBOL("%TAB",AB_package);
    Qpct_space = STATIC_SYMBOL("%SPACE",AB_package);
    Qpct_line_separator = STATIC_SYMBOL("%LINE-SEPARATOR",AB_package);
    Qpct_paragraph_separator = STATIC_SYMBOL("%PARAGRAPH-SEPARATOR",
	    AB_package);
    Qpct_ex = STATIC_SYMBOL("%!",AB_package);
    Qpct_dq = STATIC_SYMBOL("%\"",AB_package);
    Qpct_no = STATIC_SYMBOL("%#",AB_package);
    Qpct_dol = STATIC_SYMBOL("%$",AB_package);
    Qpct_pct = STATIC_SYMBOL("%%",AB_package);
    Qpct_and = STATIC_SYMBOL("%&",AB_package);
    Qpct_op = STATIC_SYMBOL("%(",AB_package);
    Qpct_cp = STATIC_SYMBOL("%)",AB_package);
    Qpct_star = STATIC_SYMBOL("%*",AB_package);
    Qpct_plus = STATIC_SYMBOL("%+",AB_package);
    Qpct_cm = STATIC_SYMBOL("%,",AB_package);
    Qpct_sl = STATIC_SYMBOL("%/",AB_package);
    Qpct_col = STATIC_SYMBOL("%:",AB_package);
    Qpct_sc = STATIC_SYMBOL("%;",AB_package);
    Qpct_lt = STATIC_SYMBOL("%<",AB_package);
    Qpct_eq = STATIC_SYMBOL("%=",AB_package);
    Qpct_gt = STATIC_SYMBOL("%>",AB_package);
    Qpct_qm = STATIC_SYMBOL("%\?",AB_package);
    Qpct_at = STATIC_SYMBOL("%@",AB_package);
    Qpct_obt = STATIC_SYMBOL("%[",AB_package);
    Qpct_bs = STATIC_SYMBOL("%\\",AB_package);
    Qpct_cbt = STATIC_SYMBOL("%]",AB_package);
    Qpct_ct = STATIC_SYMBOL("%^",AB_package);
    Qpct_bq = STATIC_SYMBOL("%`",AB_package);
    Qpct_ob = STATIC_SYMBOL("%{",AB_package);
    Qpct_or = STATIC_SYMBOL("%|",AB_package);
    Qpct_cb = STATIC_SYMBOL("%}",AB_package);
    Qpct_tl = STATIC_SYMBOL("%~",AB_package);
    Qpct_copyright_sign = STATIC_SYMBOL("%COPYRIGHT-SIGN",AB_package);
    Qpct_registered_sign = STATIC_SYMBOL("%REGISTERED-SIGN",AB_package);
    Qpct_trade_mark_sign = STATIC_SYMBOL("%TRADE-MARK-SIGN",AB_package);
    Qpct_bullet = STATIC_SYMBOL("%BULLET",AB_package);
    Qpct_latin_small_letter_f_with_hook = 
	    STATIC_SYMBOL("%LATIN-SMALL-LETTER-F-WITH-HOOK",AB_package);
    Qpct_inverted_exclamation_point = 
	    STATIC_SYMBOL("%INVERTED-EXCLAMATION-POINT",AB_package);
    Qpct_cent_sign = STATIC_SYMBOL("%CENT-SIGN",AB_package);
    Qpct_pound_sign = STATIC_SYMBOL("%POUND-SIGN",AB_package);
    Qpct_yen_sign = STATIC_SYMBOL("%YEN-SIGN",AB_package);
    Qpct_right_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%RIGHT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    Qpct_left_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%LEFT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    Qpct_inverted_question_mark = STATIC_SYMBOL("%INVERTED-QUESTION-MARK",
	    AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)13L,Qpct_tl,
	    Qpct_copyright_sign,Qpct_registered_sign,Qpct_trade_mark_sign,
	    Qpct_bullet,Qpct_latin_small_letter_f_with_hook,
	    Qpct_inverted_exclamation_point,Qpct_cent_sign,Qpct_pound_sign,
	    Qpct_yen_sign,Qpct_right_pointing_double_angle_quotation_mark,
	    Qpct_left_pointing_double_angle_quotation_mark,
	    Qpct_inverted_question_mark);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)32L,Qpct_tab,Qpct_space,
	    Qpct_line_separator,Qpct_paragraph_separator,Qpct_ex,Qpct_dq,
	    Qpct_no,Qpct_dol,Qpct_pct,Qpct_and,Qpct_op,Qpct_cp,Qpct_star,
	    Qpct_plus,Qpct_cm,Qpct_sl,Qpct_col,Qpct_sc,Qpct_lt,Qpct_eq,
	    Qpct_gt,Qpct_qm,Qpct_at,Qpct_obt,Qpct_bs,Qpct_cbt,Qpct_ct,
	    Qpct_bq,Qpct_ob,Qpct_or,Qpct_cb,list_constant_23);
    Characters_not_allowed_in_symbols_in_g2_50r0 = list_constant_24;
    character_constant_name = Nil;
    ab_loop_list_ = Characters_not_allowed_in_symbols_in_g2_50r0;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    character_constant_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = LIST_1(SYMBOL_VALUE(character_constant_name));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    Alphabet_nonsymbol_character_codes_sorted_by_encoding = sort(2,temp_1,
	    SYMBOL_FUNCTION(Qnum_lt));
    list_constant_25 = STATIC_LIST((SI_Long)12L,Qpct_copyright_sign,
	    Qpct_registered_sign,Qpct_trade_mark_sign,Qpct_bullet,
	    Qpct_latin_small_letter_f_with_hook,
	    Qpct_inverted_exclamation_point,Qpct_cent_sign,Qpct_pound_sign,
	    Qpct_yen_sign,Qpct_right_pointing_double_angle_quotation_mark,
	    Qpct_left_pointing_double_angle_quotation_mark,
	    Qpct_inverted_question_mark);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Qpct_no,Qpct_bq,
	    list_constant_25);
    character_constant_name = Nil;
    ab_loop_list_ = list_constant_26;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    character_constant_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = LIST_1(SYMBOL_VALUE(character_constant_name));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_2;
  end_loop_2:
    temp_1 = ab_loopvar_;
    goto end_3;
    temp_1 = Qnil;
  end_3:;
    Alphabet_illegal_codes_character_class = sort(2,temp_1,
	    SYMBOL_FUNCTION(Qnum_lt));
    first_char = CAR(Alphabet_nonsymbol_character_codes_sorted_by_encoding);
    if (FIXNUM_EQ(Alphabet_min_code,first_char))
	result_1 = Qnil;
    else {
	temp_1 = FIXNUM_SUB1(first_char);
	result_1 = LIST_1(CONS(Alphabet_min_code,temp_1));
    }
    number1 = Nil;
    number2 = Nil;
    ab_loop_list_ = Alphabet_nonsymbol_character_codes_sorted_by_encoding;
    diff = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    number1 = CAR(ab_loop_list_);
    temp_1 = CDR(ab_loop_list_);
    number2 = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(number2))
	goto end_loop_3;
    diff = FIXNUM_MINUS(number2,number1);
    if (IFIX(diff) > (SI_Long)1L) {
	temp_2 = FIXNUM_ADD1(number1);
	temp_1 = FIXNUM_SUB1(number2);
	push_arg = CONS(temp_2,temp_1);
	result_1 = CONS(push_arg,result_1);
    }
    goto next_loop_3;
  end_loop_3:
    if (FIXNUM_NE(number1,Alphabet_max_code)) {
	temp_1 = FIXNUM_ADD1(number1);
	push_arg = CONS(temp_1,Alphabet_max_code);
	result_1 = CONS(push_arg,result_1);
    }
    Alphabet_symbol_character_class = nreverse(result_1);
    goto end_4;
    Alphabet_symbol_character_class = Qnil;
  end_4:;
    Qright_string = STATIC_SYMBOL("RIGHT-STRING",AB_package);
    Qself_terminating_punctuation_mark = 
	    STATIC_SYMBOL("SELF-TERMINATING-PUNCTUATION-MARK",AB_package);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,
	    Qself_terminating_punctuation_mark,Qcbt);
    list_constant_28 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)93L),
	    Qright_string,list_constant_27);
    list_constant_29 = STATIC_CONS(list_constant_28,Qnil);
    Generally_ambiguous_characters_in_g2_tokenization = list_constant_29;
    Qsymbol_char = STATIC_SYMBOL("SYMBOL-CHAR",AB_package);
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    Qseq = STATIC_SYMBOL("SEQ",AB_package);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    list_constant_30 = STATIC_CONS(Qab_dot,Qnil);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)64L),
	    list_constant_30);
    Qcharacter_class = STATIC_SYMBOL("CHARACTER-CLASS",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qcharacter_class,
	    list_constant_7);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qdigit_char,list_constant_31);
    Qoptional_unary_minus = STATIC_SYMBOL("OPTIONAL-UNARY-MINUS",AB_package);
    Qmaybe = STATIC_SYMBOL("MAYBE",AB_package);
    list_constant_32 = STATIC_CONS(FIX((SI_Long)45L),Qnil);
    list_constant_33 = STATIC_CONS(Qmaybe,list_constant_32);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qoptional_unary_minus,
	    list_constant_33);
    Qoptional_sign = STATIC_SYMBOL("OPTIONAL-SIGN",AB_package);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    FIX((SI_Long)43L),list_constant_32);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qmaybe,list_constant_34);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qoptional_sign,
	    list_constant_35);
    Qexponent_part = STATIC_SYMBOL("EXPONENT-PART",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qeither,FIX((SI_Long)69L),
	    FIX((SI_Long)101L));
    Qpattern = STATIC_SYMBOL("PATTERN",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qpattern,Qoptional_sign);
    Qab_plus = STATIC_SYMBOL("PLUS",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qpattern,Qdigit_char);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_36);
    list_constant_40 = STATIC_LIST((SI_Long)4L,Qseq,list_constant_37,
	    list_constant_38,list_constant_39);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qexponent_part,
	    list_constant_40);
    Qlong_mark = STATIC_SYMBOL("LONG-MARK",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qlong_mark,FIX((SI_Long)76L));
    Qwhitespace_char = STATIC_SYMBOL("WHITESPACE-CHAR",AB_package);
    list_constant_41 = STATIC_CONS(FIX((SI_Long)9L),Qnil);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)8L,Qeither,
	    FIX((SI_Long)13L),FIX((SI_Long)10L),FIX((SI_Long)10L),
	    FIX((SI_Long)8232L),FIX((SI_Long)8233L),FIX((SI_Long)32L),
	    list_constant_41);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qwhitespace_char,
	    list_constant_42);
    Qab_string_char = STATIC_SYMBOL("STRING-CHAR",AB_package);
    Qinverted_class = STATIC_SYMBOL("INVERTED-CLASS",AB_package);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)34L),
	    FIX((SI_Long)64L),list_constant_15);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_43);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qab_string_char,
	    list_constant_44);
    Qopen_bracket_character = STATIC_SYMBOL("OPEN-BRACKET-CHARACTER",
	    AB_package);
    list_constant_52 = STATIC_CONS(Qopen_bracket_character,list_constant_15);
    Qclose_bracket_character = STATIC_SYMBOL("CLOSE-BRACKET-CHARACTER",
	    AB_package);
    list_constant_53 = STATIC_CONS(Qclose_bracket_character,list_constant_16);
    list_constant_55 = STATIC_LIST((SI_Long)9L,list_constant_45,
	    list_constant_46,list_constant_47,list_constant_48,
	    list_constant_49,list_constant_50,list_constant_51,
	    list_constant_52,list_constant_53);
    temp_1 = LIST_2(Qsymbol_char,LIST_3(Qeither,list_constant_54,
	    LIST_2(Qcharacter_class,Alphabet_symbol_character_class)));
    G2_standard_tokens_head = LIST_1(CONS(temp_1,list_constant_55));
    Qleft_string = STATIC_SYMBOL("LEFT-STRING",AB_package);
    Qkleene = STATIC_SYMBOL("KLEENE",AB_package);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qpattern,Qab_string_char);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_54,
	    list_constant_56);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_57);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qopen_bracket_character);
    list_constant_60 = STATIC_LIST((SI_Long)2L,list_constant_58,
	    list_constant_59);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,Qseq,FIX((SI_Long)34L),
	    list_constant_60);
    list_constant_62 = STATIC_CONS(Qalphabet_strip_delimitors_off_string,Qnil);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,Qleft_string,
	    list_constant_61,list_constant_62);
    Qmiddle_string = STATIC_SYMBOL("MIDDLE-STRING",AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qclose_bracket_character);
    list_constant_64 = STATIC_LIST_STAR((SI_Long)3L,Qseq,list_constant_63,
	    list_constant_60);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)3L,Qmiddle_string,
	    list_constant_64,list_constant_62);
    list_constant_65 = STATIC_LIST_STAR((SI_Long)4L,Qseq,list_constant_63,
	    list_constant_58,list_constant_14);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)3L,Qright_string,
	    list_constant_65,list_constant_62);
    list_constant_69 = STATIC_LIST((SI_Long)3L,list_constant_66,
	    list_constant_67,list_constant_68);
    G2_standard_tokens_middle_strings = list_constant_69;
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qpattern,Qoptional_unary_minus);
    list_constant_71 = STATIC_CONS(list_constant_39,Qnil);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)3L,Qseq,list_constant_70,
	    list_constant_71);
    list_constant_73 = STATIC_CONS(Qnumeric_return_value,Qnil);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)3L,Qinteger,
	    list_constant_72,list_constant_73);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qpattern,Qexponent_part);
    list_constant_75 = STATIC_CONS(list_constant_74,Qnil);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)3L,Qseq,list_constant_39,
	    list_constant_75);
    list_constant_76 = STATIC_CONS(list_constant_36,Qnil);
    list_constant_78 = STATIC_CONS(Qkleene,list_constant_76);
    list_constant_77 = STATIC_CONS(Qmaybe,list_constant_75);
    list_constant_79 = STATIC_CONS(list_constant_77,Qnil);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)5L,Qseq,list_constant_39,
	    FIX((SI_Long)46L),list_constant_78,list_constant_79);
    list_constant_82 = STATIC_LIST_STAR((SI_Long)4L,Qseq,FIX((SI_Long)46L),
	    list_constant_39,list_constant_79);
    list_constant_83 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_80,
	    list_constant_81,list_constant_82);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qseq,list_constant_70,
	    list_constant_83);
    list_constant_90 = STATIC_LIST_STAR((SI_Long)3L,Qfloat,
	    list_constant_84,list_constant_73);
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qpattern,Qlong_mark);
    list_constant_86 = STATIC_LIST((SI_Long)4L,Qseq,list_constant_70,
	    list_constant_39,list_constant_85);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)3L,Qlong,list_constant_86,
	    list_constant_73);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qpattern,Qsymbol_char);
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_87);
    list_constant_92 = STATIC_LIST((SI_Long)2L,Qsymbol,list_constant_88);
    list_constant_93 = STATIC_LIST((SI_Long)4L,list_constant_89,
	    list_constant_90,list_constant_91,list_constant_92);
    G2_standard_tokens_middle_1 = list_constant_93;
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    list_constant_94 = STATIC_CONS(list_constant_58,list_constant_14);
    list_constant_95 = STATIC_LIST_STAR((SI_Long)3L,Qseq,FIX((SI_Long)34L),
	    list_constant_94);
    list_constant_116 = STATIC_LIST_STAR((SI_Long)3L,Qwhole_string,
	    list_constant_95,list_constant_62);
    Qsingle_line_comment = STATIC_SYMBOL("SINGLE-LINE-COMMENT",AB_package);
    list_constant_96 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)13L),
	    FIX((SI_Long)10L),FIX((SI_Long)10L),FIX((SI_Long)8232L),
	    FIX((SI_Long)8233L));
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_96);
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_97);
    list_constant_99 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)47L),list_constant_98);
    list_constant_100 = STATIC_CONS(Qno_value,Qnil);
    list_constant_117 = STATIC_LIST_STAR((SI_Long)3L,Qsingle_line_comment,
	    list_constant_99,list_constant_100);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    list_constant_101 = STATIC_CONS(FIX((SI_Long)125L),Qnil);
    list_constant_102 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_101);
    list_constant_103 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_102);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qseq,list_constant_103);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)123L),
	    list_constant_104);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)3L,Qcomment,
	    list_constant_105,list_constant_100);
    Qquoted_character = STATIC_SYMBOL("QUOTED-CHARACTER",AB_package);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)3L,Qquoted_character,
	    FIX((SI_Long)64L),list_constant_100);
    Qpunctuation_mark = STATIC_SYMBOL("PUNCTUATION-MARK",AB_package);
    list_constant_106 = STATIC_CONS(FIX((SI_Long)61L),Qnil);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)60L),list_constant_106);
    list_constant_110 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)62L),list_constant_106);
    list_constant_111 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)47L),list_constant_106);
    list_constant_107 = STATIC_CONS(FIX((SI_Long)43L),list_constant_32);
    list_constant_112 = STATIC_CONS(Qseq,list_constant_107);
    list_constant_108 = STATIC_CONS(FIX((SI_Long)58L),Qnil);
    list_constant_113 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)58L),list_constant_108);
    list_constant_114 = STATIC_LIST_STAR((SI_Long)11L,Qeither,
	    list_constant_109,list_constant_110,list_constant_111,
	    list_constant_112,list_constant_113,FIX((SI_Long)60L),
	    FIX((SI_Long)62L),FIX((SI_Long)47L),FIX((SI_Long)43L),
	    list_constant_108);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qpunctuation_mark,
	    list_constant_114);
    list_constant_115 = STATIC_LIST((SI_Long)16L,Qeither,FIX((SI_Long)61L),
	    FIX((SI_Long)42L),FIX((SI_Long)94L),FIX((SI_Long)40L),
	    FIX((SI_Long)41L),FIX((SI_Long)91L),FIX((SI_Long)93L),
	    FIX((SI_Long)44L),FIX((SI_Long)59L),FIX((SI_Long)63L),
	    FIX((SI_Long)33L),FIX((SI_Long)124L),FIX((SI_Long)36L),
	    FIX((SI_Long)37L),FIX((SI_Long)38L));
    list_constant_121 = STATIC_LIST((SI_Long)2L,
	    Qself_terminating_punctuation_mark,list_constant_115);
    list_constant_122 = STATIC_LIST((SI_Long)2L,Qpunctuation_mark,
	    FIX((SI_Long)92L));
    list_constant_123 = STATIC_CONS(Qpunctuation_mark,list_constant_20);
    Qillegal_character = STATIC_SYMBOL("ILLEGAL-CHARACTER",AB_package);
    G2_standard_tokens_tail = list(9,list_constant_116,list_constant_117,
	    list_constant_118,list_constant_119,list_constant_120,
	    list_constant_121,list_constant_122,list_constant_123,
	    LIST_2(Qillegal_character,LIST_2(Qcharacter_class,
	    Alphabet_illegal_codes_character_class)));
    Qdo_nothing = STATIC_SYMBOL("DO-NOTHING",AB_package);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qpattern,Qwhitespace_char);
    list_constant_127 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_124);
    list_constant_125 = STATIC_CONS(Qeither,list_constant_96);
    list_constant_128 = STATIC_LIST((SI_Long)5L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)47L),list_constant_98,list_constant_125);
    list_constant_126 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_103,list_constant_101);
    list_constant_129 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)123L),
	    list_constant_126);
    list_constant_130 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_127,
	    list_constant_128,list_constant_129);
    list_constant_134 = STATIC_LIST((SI_Long)2L,Qdo_nothing,list_constant_130);
    Qdisambiguated_token = STATIC_SYMBOL("DISAMBIGUATED-TOKEN",AB_package);
    list_constant_131 = STATIC_CONS(FIX((SI_Long)47L),list_constant_106);
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_131);
    list_constant_133 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)47L),
	    list_constant_132);
    list_constant_135 = STATIC_LIST((SI_Long)2L,Qdisambiguated_token,
	    list_constant_133);
    G2_standard_tokens = append2(G2_standard_tokens_head,list_star(3,
	    list_constant_134,list_constant_135,
	    append2(G2_standard_tokens_middle_1,
	    append2(G2_standard_tokens_middle_strings,
	    G2_standard_tokens_tail))));
    Qg2_comment = STATIC_SYMBOL("G2-COMMENT",AB_package);
    list_constant_136 = STATIC_LIST((SI_Long)2L,list_constant_128,
	    list_constant_129);
    list_constant_137 = STATIC_CONS(Qeither,list_constant_136);
    list_constant_138 = STATIC_LIST((SI_Long)3L,Qg2_comment,
	    list_constant_137,Qalphabet_substring_function);
    list_constant_139 = STATIC_LIST((SI_Long)2L,Qdo_nothing,list_constant_127);
    temp_1 = append2(G2_standard_tokens_middle_1,
	    append2(G2_standard_tokens_middle_strings,
	    CONS(list_constant_138,G2_standard_tokens_tail)));
    G2_comment_recognizing_tokens = append2(G2_standard_tokens_head,
	    CONS(list_constant_139,temp_1));
    list_constant_140 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)34L),
	    FIX((SI_Long)64L));
    list_constant_141 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_140);
    list_constant_142 = STATIC_LIST((SI_Long)2L,Qab_string_char,
	    list_constant_141);
    list_constant_143 = STATIC_LIST((SI_Long)7L,list_constant_45,
	    list_constant_46,list_constant_49,list_constant_47,
	    list_constant_48,list_constant_50,list_constant_142);
    temp_1 = LIST_2(Qsymbol_char,LIST_3(Qeither,list_constant_54,
	    LIST_2(Qcharacter_class,Alphabet_symbol_character_class)));
    G2_simple_tokens = list_star(4,CONS(temp_1,list_constant_143),
	    list_constant_134,list_constant_135,
	    append2(G2_standard_tokens_middle_1,G2_standard_tokens_tail));
    Qdigit = STATIC_SYMBOL("DIGIT",AB_package);
    list_constant_144 = STATIC_CONS(list_constant_31,Qnil);
    list_constant_145 = STATIC_CONS(Qdigit,list_constant_144);
    list_constant_156 = STATIC_CONS(list_constant_145,Qnil);
    list_constant_146 = STATIC_CONS(list_constant_42,Qnil);
    list_constant_147 = STATIC_CONS(Qab_plus,list_constant_146);
    list_constant_148 = STATIC_CONS(list_constant_129,Qnil);
    list_constant_149 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    list_constant_147,list_constant_148);
    list_constant_153 = STATIC_LIST((SI_Long)2L,Qdo_nothing,list_constant_149);
    list_constant_150 = STATIC_LIST_STAR((SI_Long)14L,Qeither,
	    FIX((SI_Long)47L),FIX((SI_Long)58L),FIX((SI_Long)36L),
	    FIX((SI_Long)59L),FIX((SI_Long)60L),FIX((SI_Long)62L),
	    FIX((SI_Long)91L),FIX((SI_Long)93L),FIX((SI_Long)42L),
	    FIX((SI_Long)63L),FIX((SI_Long)33L),FIX((SI_Long)92L),
	    list_constant_20);
    list_constant_154 = STATIC_LIST((SI_Long)2L,
	    Qself_terminating_punctuation_mark,list_constant_150);
    list_constant_151 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    FIX((SI_Long)123L),list_constant_101);
    list_constant_152 = STATIC_CONS(Qalphabet_substring_function,Qnil);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)3L,
	    Qself_terminating_punctuation_mark,list_constant_151,
	    list_constant_152);
    list_constant_157 = STATIC_LIST((SI_Long)5L,list_constant_153,
	    list_constant_92,list_constant_119,list_constant_154,
	    list_constant_155);
    temp_1 = LIST_2(Qsymbol_char,LIST_5(Qeither,list_constant_54,
	    FIX((SI_Long)40L),FIX((SI_Long)41L),LIST_2(Qcharacter_class,
	    Alphabet_symbol_character_class)));
    temp_1 = CONS(temp_1,list_constant_156);
    Load_kb_tokens = CONS(temp_1,list_constant_157);
    list_constant_158 = STATIC_LIST((SI_Long)4L,list_constant_47,
	    list_constant_48,list_constant_50,list_constant_142);
    list_constant_164 = STATIC_LIST_STAR((SI_Long)3L,list_constant_45,
	    list_constant_46,list_constant_158);
    list_constant_159 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    list_constant_127,list_constant_148);
    list_constant_160 = STATIC_LIST((SI_Long)2L,Qdo_nothing,list_constant_159);
    list_constant_161 = STATIC_LIST_STAR((SI_Long)3L,Qinteger,
	    list_constant_72,list_constant_100);
    list_constant_162 = STATIC_LIST_STAR((SI_Long)3L,Qfloat,
	    list_constant_84,list_constant_100);
    Qdouble_colon = STATIC_SYMBOL("DOUBLE-COLON",AB_package);
    list_constant_163 = STATIC_LIST((SI_Long)2L,Qdouble_colon,
	    list_constant_113);
    list_constant_165 = STATIC_LIST((SI_Long)6L,list_constant_160,
	    list_constant_161,list_constant_162,list_constant_92,
	    list_constant_118,list_constant_163);
    temp_1 = LIST_2(Qsymbol_char,LIST_3(Qeither,list_constant_54,
	    LIST_2(Qcharacter_class,Alphabet_symbol_character_class)));
    temp_1 = CONS(temp_1,list_constant_164);
    G2_symbol_tokens = CONS(temp_1,list_constant_165);
    Qdouble_quote = STATIC_SYMBOL("DOUBLE-QUOTE",AB_package);
    list_constant_171 = STATIC_CONS(Qdouble_quote,list_constant_14);
    list_constant_166 = STATIC_CONS(FIX((SI_Long)46L),Qnil);
    list_constant_172 = STATIC_CONS(Qab_dot,list_constant_166);
    Qalternative = STATIC_SYMBOL("ALTERNATIVE",AB_package);
    list_constant_173 = STATIC_LIST((SI_Long)2L,Qalternative,
	    FIX((SI_Long)124L));
    Qkleene_star = STATIC_SYMBOL("KLEENE-STAR",AB_package);
    list_constant_174 = STATIC_LIST((SI_Long)2L,Qkleene_star,
	    FIX((SI_Long)42L));
    Qquestion_mark = STATIC_SYMBOL("QUESTION-MARK",AB_package);
    list_constant_175 = STATIC_LIST((SI_Long)2L,Qquestion_mark,
	    FIX((SI_Long)63L));
    list_constant_176 = STATIC_LIST((SI_Long)2L,Qab_plus,FIX((SI_Long)43L));
    Qleft_paren = STATIC_SYMBOL("LEFT-PAREN",AB_package);
    list_constant_177 = STATIC_LIST((SI_Long)2L,Qleft_paren,FIX((SI_Long)40L));
    Qright_paren = STATIC_SYMBOL("RIGHT-PAREN",AB_package);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qright_paren,
	    FIX((SI_Long)41L));
    Qleft_curly_brace = STATIC_SYMBOL("LEFT-CURLY-BRACE",AB_package);
    list_constant_179 = STATIC_LIST((SI_Long)2L,Qleft_curly_brace,
	    FIX((SI_Long)123L));
    Qright_curly_brace = STATIC_SYMBOL("RIGHT-CURLY-BRACE",AB_package);
    list_constant_180 = STATIC_CONS(Qright_curly_brace,list_constant_101);
    Qhyphen = STATIC_SYMBOL("HYPHEN",AB_package);
    list_constant_181 = STATIC_CONS(Qhyphen,list_constant_32);
    Qcaret = STATIC_SYMBOL("CARET",AB_package);
    list_constant_182 = STATIC_LIST((SI_Long)2L,Qcaret,FIX((SI_Long)94L));
    list_constant_167 = STATIC_CONS(FIX((SI_Long)64L),Qnil);
    list_constant_183 = STATIC_CONS(Qquoted_character,list_constant_167);
    Qregexp_character = STATIC_SYMBOL("REGEXP-CHARACTER",AB_package);
    list_constant_168 = STATIC_LIST_STAR((SI_Long)12L,FIX((SI_Long)46L),
	    FIX((SI_Long)124L),FIX((SI_Long)42L),FIX((SI_Long)63L),
	    FIX((SI_Long)43L),FIX((SI_Long)40L),FIX((SI_Long)41L),
	    FIX((SI_Long)123L),FIX((SI_Long)125L),FIX((SI_Long)45L),
	    FIX((SI_Long)94L),list_constant_167);
    list_constant_169 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_168);
    list_constant_170 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_54,
	    list_constant_169);
    list_constant_184 = STATIC_LIST((SI_Long)2L,Qregexp_character,
	    list_constant_170);
    list_constant_185 = STATIC_LIST((SI_Long)16L,Qnil,list_constant_153,
	    list_constant_171,list_constant_172,list_constant_173,
	    list_constant_174,list_constant_175,list_constant_176,
	    list_constant_177,list_constant_178,list_constant_179,
	    list_constant_180,list_constant_181,list_constant_182,
	    list_constant_183,list_constant_184);
    Tokenizer_tokens = list_constant_185;
    list_constant_186 = STATIC_CONS(list_constant_30,Qnil);
    list_constant_187 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)92L),list_constant_186);
    list_constant_188 = STATIC_LIST_STAR((SI_Long)3L,Qeither,
	    list_constant_187,list_constant_186);
    list_constant_189 = STATIC_LIST((SI_Long)2L,Qregexp_character,
	    list_constant_188);
    list_constant_190 = STATIC_LIST((SI_Long)13L,Qnil,list_constant_173,
	    list_constant_174,list_constant_172,list_constant_177,
	    list_constant_178,list_constant_175,list_constant_176,
	    list_constant_179,list_constant_180,list_constant_182,
	    list_constant_181,list_constant_189);
    Regular_expression_tokens = list_constant_190;
    Qbuilt_in = STATIC_SYMBOL("BUILT-IN",AB_package);
    list_constant_191 = STATIC_CONS(FIX((SI_Long)92L),Qnil);
    list_constant_192 = STATIC_CONS(FIX((SI_Long)62L),list_constant_191);
    list_constant_193 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_192);
    list_constant_194 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_187,
	    list_constant_193);
    list_constant_195 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_194);
    list_constant_196 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)60L),
	    list_constant_195,FIX((SI_Long)62L));
    list_constant_208 = STATIC_LIST((SI_Long)2L,Qbuilt_in,list_constant_196);
    list_constant_197 = STATIC_CONS(FIX((SI_Long)41L),list_constant_191);
    list_constant_198 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_197);
    list_constant_199 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_187,
	    list_constant_198);
    list_constant_200 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_199);
    list_constant_201 = STATIC_CONS(FIX((SI_Long)41L),Qnil);
    list_constant_202 = STATIC_LIST_STAR((SI_Long)5L,Qseq,
	    FIX((SI_Long)36L),FIX((SI_Long)40L),list_constant_200,
	    list_constant_201);
    list_constant_209 = STATIC_LIST((SI_Long)2L,Qvariable,list_constant_202);
    list_constant_203 = STATIC_CONS(FIX((SI_Long)125L),list_constant_191);
    list_constant_204 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_203);
    list_constant_205 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_187,
	    list_constant_204);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_205);
    list_constant_207 = STATIC_LIST_STAR((SI_Long)4L,Qseq,
	    FIX((SI_Long)123L),list_constant_206,list_constant_101);
    list_constant_210 = STATIC_LIST((SI_Long)2L,Qcharacter_class,
	    list_constant_207);
    list_constant_211 = STATIC_LIST((SI_Long)4L,Qnil,list_constant_208,
	    list_constant_209,list_constant_210);
    Regexp_macro_tokens = list_constant_211;
    list_constant_212 = STATIC_CONS(FIX((SI_Long)32L),Qnil);
    list_constant_219 = STATIC_CONS(Qdo_nothing,list_constant_212);
    Qquoted_path = STATIC_SYMBOL("QUOTED-PATH",AB_package);
    list_constant_213 = STATIC_CONS(FIX((SI_Long)39L),Qnil);
    list_constant_214 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_213);
    list_constant_215 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_214);
    list_constant_216 = STATIC_LIST_STAR((SI_Long)4L,Qseq,
	    FIX((SI_Long)39L),list_constant_215,list_constant_213);
    list_constant_220 = STATIC_LIST_STAR((SI_Long)3L,Qquoted_path,
	    list_constant_216,list_constant_62);
    Qunquoted_path = STATIC_SYMBOL("UNQUOTED-PATH",AB_package);
    list_constant_217 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_212);
    list_constant_218 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_217);
    list_constant_221 = STATIC_LIST_STAR((SI_Long)3L,Qunquoted_path,
	    list_constant_218,list_constant_152);
    list_constant_222 = STATIC_LIST((SI_Long)4L,Qnil,list_constant_219,
	    list_constant_220,list_constant_221);
    Module_search_path_tokens = list_constant_222;
    Qunsigned_integer = STATIC_SYMBOL("UNSIGNED-INTEGER",AB_package);
    list_constant_223 = STATIC_CONS(Qab_plus,list_constant_144);
    list_constant_227 = STATIC_LIST_STAR((SI_Long)3L,Qunsigned_integer,
	    list_constant_223,list_constant_73);
    list_constant_224 = STATIC_CONS(list_constant_6,list_constant_212);
    list_constant_225 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_224);
    list_constant_226 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_225);
    list_constant_228 = STATIC_LIST_STAR((SI_Long)3L,Qerror,
	    list_constant_226,list_constant_100);
    list_constant_229 = STATIC_LIST((SI_Long)4L,Qnil,list_constant_219,
	    list_constant_227,list_constant_228);
    Tabular_view_row_selection_tokens = list_constant_229;
}
