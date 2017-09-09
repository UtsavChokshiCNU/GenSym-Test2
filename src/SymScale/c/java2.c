/* java2.c
 * Input file:  java2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "java2.h"


DEFINE_VARIABLE_WITH_SYMBOL(Java_grammar_stream_qm, Qjava_grammar_stream_qm);

static Object string_constant;     /* "~" */

static Object string_constant_1;   /* "~~" */

/* INTERN-FOR-JAVA-GRAMMAR */
Object intern_for_java_grammar(gensym_string)
    Object gensym_string;
{
    Object temp;

    x_note_fn_call(250,0);
    temp = EQUAL(gensym_string,string_constant) ? intern(string_constant_1,
	    _) : intern(gensym_string,_);
    return VALUES_1(temp);
}

Object Java_reserved_word_p_prop = UNBOUND;

static Object Qjava_reserved_word_p;  /* java-reserved-word-p */

static Object Qreserved_java_word;  /* reserved-java-word */

static Object Qidentifier;         /* identifier */

/* UNRESERVED-JAVA-IDENTIFIER? */
Object unreserved_java_identifier_qm(symbol,pattern)
    Object symbol, pattern;
{
    Object temp;

    x_note_fn_call(250,1);
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qjava_reserved_word_p))
	return VALUES_2(Bad_phrase,Qreserved_java_word);
    else {
	temp = phrase_list_2(Qidentifier,symbol);
	return VALUES_2(temp,Nil);
    }
}

/* MAKE-CHARACTER-RANGE-FROM-SORTED-LIST-OF-CHARACTER-CODES */
Object make_character_range_from_sorted_list_of_character_codes(char_codes)
    Object char_codes;
{
    Object this_min, this_max, char_code_1, ab_loop_list_, accum, temp;
    Object push_arg;

    x_note_fn_call(250,2);
    this_min = CAR(char_codes);
    this_max = this_min;
    char_code_1 = Nil;
    ab_loop_list_ = CDR(char_codes);
    accum = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    char_code_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = add1(this_max);
    if (NUM_EQ(char_code_1,temp))
	this_max = char_code_1;
    else {
	push_arg = CONS(this_min,this_max);
	accum = CONS(push_arg,accum);
	this_min = char_code_1;
	this_max = char_code_1;
    }
    goto next_loop;
  end_loop:
    temp = CONS(this_min,this_max);
    return reverse(CONS(temp,accum));
    return VALUES_1(Qnil);
}

Object Must_quote_g2_symbol_character_class = UNBOUND;

Object Unicode_letter_or_digit_possibly_undefined_character_class = UNBOUND;

Object Unicode_digit_possibly_undefined_character_class = UNBOUND;

/* CHARACTER-CLASS-DIFFERENCE */
Object character_class_difference(character_class_1,character_class_2)
    Object character_class_1, character_class_2;
{
    Object accum, character_class_1_old_value, temp, ab_loop_destructure_;
    Object min_1_qm, max_1, character_class_2_old_value, min_2_qm, max_2;
    Object gensymed_symbol, push_arg;

    x_note_fn_call(250,3);
    accum = Nil;
    character_class_1_old_value = character_class_1;
    temp = FIRST(character_class_1_old_value);
    character_class_1 = REST(character_class_1_old_value);
    ab_loop_destructure_ = temp;
    min_1_qm = Nil;
    max_1 = Nil;
    min_1_qm = CAR(ab_loop_destructure_);
    max_1 = CDR(ab_loop_destructure_);
    character_class_2_old_value = character_class_2;
    temp = FIRST(character_class_2_old_value);
    character_class_2 = REST(character_class_2_old_value);
    ab_loop_destructure_ = temp;
    min_2_qm = Nil;
    max_2 = Nil;
    min_2_qm = CAR(ab_loop_destructure_);
    max_2 = CDR(ab_loop_destructure_);
  next_loop:
    if ( !(min_1_qm && min_2_qm))
	goto end_loop;
    if (NUM_GT(min_1_qm,max_2)) {
	character_class_2_old_value = character_class_2;
	temp = FIRST(character_class_2_old_value);
	character_class_2 = REST(character_class_2_old_value);
	gensymed_symbol = temp;
	min_2_qm = CAR(gensymed_symbol);
	max_2 = CDR(gensymed_symbol);
    }
    else if (NUM_LT(max_1,min_2_qm)) {
	push_arg = CONS(min_1_qm,max_1);
	accum = CONS(push_arg,accum);
	character_class_1_old_value = character_class_1;
	temp = FIRST(character_class_1_old_value);
	character_class_1 = REST(character_class_1_old_value);
	gensymed_symbol = temp;
	min_1_qm = CAR(gensymed_symbol);
	max_1 = CDR(gensymed_symbol);
    }
    else if (NUM_LT(min_1_qm,min_2_qm) && NUM_GT(max_1,max_2)) {
	temp = sub1(min_2_qm);
	push_arg = CONS(min_1_qm,temp);
	accum = CONS(push_arg,accum);
	min_1_qm = add1(max_2);
	character_class_2_old_value = character_class_2;
	temp = FIRST(character_class_2_old_value);
	character_class_2 = REST(character_class_2_old_value);
	gensymed_symbol = temp;
	min_2_qm = CAR(gensymed_symbol);
	max_2 = CDR(gensymed_symbol);
    }
    else if (NUM_GT(max_1,max_2)) {
	min_1_qm = add1(max_2);
	character_class_2_old_value = character_class_2;
	temp = FIRST(character_class_2_old_value);
	character_class_2 = REST(character_class_2_old_value);
	gensymed_symbol = temp;
	min_2_qm = CAR(gensymed_symbol);
	max_2 = CDR(gensymed_symbol);
    }
    else if (NUM_LT(min_1_qm,min_2_qm)) {
	temp = sub1(min_2_qm);
	push_arg = CONS(min_1_qm,temp);
	accum = CONS(push_arg,accum);
	character_class_1_old_value = character_class_1;
	temp = FIRST(character_class_1_old_value);
	character_class_1 = REST(character_class_1_old_value);
	gensymed_symbol = temp;
	min_1_qm = CAR(gensymed_symbol);
	max_1 = CDR(gensymed_symbol);
    }
    else {
	character_class_1_old_value = character_class_1;
	temp = FIRST(character_class_1_old_value);
	character_class_1 = REST(character_class_1_old_value);
	gensymed_symbol = temp;
	min_1_qm = CAR(gensymed_symbol);
	max_1 = CDR(gensymed_symbol);
    }
    goto next_loop;
  end_loop:
    temp = append2(reverse(accum),append2(min_1_qm ? LIST_1(CONS(min_1_qm,
	    max_1)) : Qnil,character_class_1));
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Java_identifier_start_character_class = UNBOUND;

Object Java_identifier_quote_free_start_character_class = UNBOUND;

Object Java_identifier_part_character_class = UNBOUND;

Object Java_identifier_quote_free_part_character_class = UNBOUND;

static Object list_constant;       /* # */

static Object Qseq;                /* seq */

/* CONVERT-JAVA-SEPARATORS-OR-OPERATORS-TO-SEQ-TOKENS */
Object convert_java_separators_or_operators_to_seq_tokens(string_of_operators)
    Object string_of_operators;
{
    Object this_char, operators, operator_qm, component_char, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, thing, temp, push_arg;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(250,4);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(string_of_operators));
    this_char = Nil;
    operators = Nil;
    operator_qm = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    this_char = CHR(ICHAR(string_of_operators,index_1));
    if (member_equal(this_char,list_constant)) {
	if (operator_qm) {
	    component_char = Nil;
	    ab_loop_list_ = reverse(operator_qm);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    component_char = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    thing = component_char;
	    ab_loopvar__2 = LIST_1(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    push_arg = CONS(Qseq,temp);
	    operators = CONS(push_arg,operators);
	    operator_qm = Nil;
	}
    }
    else {
	push_arg = this_char;
	operator_qm = CONS(push_arg,operator_qm);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (operator_qm) {
	component_char = Nil;
	ab_loop_list_ = reverse(operator_qm);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	component_char = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	thing = component_char;
	ab_loopvar__2 = LIST_1(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	temp = CONS(Qseq,temp);
	temp = CONS(temp,operators);
    }
    else
	temp = operators;
    return reverse(temp);
    return VALUES_1(Qnil);
}

Object Java_separators_as_conglomerated_string = UNBOUND;

Object Java_single_character_constituent_operators_as_string = UNBOUND;

Object Java_single_character_nonconstituent_operators_as_string = UNBOUND;

Object Java_single_character_operators_as_conglomerated_string = UNBOUND;

Object Java_multi_character_operators_as_conglomerated_string = UNBOUND;

Object Newline_chars_for_java_tokens = UNBOUND;

Object Java_escape_character_literal_alist = UNBOUND;

Object Java_octal_character_literal_alist = UNBOUND;

static Object Qcharacter_literal;  /* character-literal */

static Object Qescape;             /* escape */

static Object Qbad_character_literal;  /* bad-character-literal */

static Object Qoctal;              /* octal */

static Object Qsimple;             /* simple */

/* TOKENIZE-JAVA-CHARACTER-LITERAL */
Object tokenize_java_character_literal(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object escape_char, name, ab_loop_list_, ab_loop_it_, ab_loop_desetq_;
    Object temp, this_char, char_code_1, octal_char, value, value_qm;
    SI_Long first_char, second_char, index_1, ab_loop_bind_;
    char escape_p;

    x_note_fn_call(250,5);
    first_char = UBYTE_16_ISAREF_1(string_1,IFIX(FIXNUM_ADD1(start)));
    second_char = UBYTE_16_ISAREF_1(string_1,IFIX(start) + (SI_Long)2L);
    escape_p = first_char == (SI_Long)92L;
    if (escape_p) {
	escape_char = Nil;
	name = Nil;
	ab_loop_list_ = Java_escape_character_literal_alist;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	escape_char = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	name = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = IFIX(escape_char) == second_char ? 
		phrase_list_3(Qcharacter_literal,Qescape,name) : Qnil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    if (temp);
    else if (escape_p) {
	index_1 = (SI_Long)2L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(end_1));
	this_char = Nil;
	char_code_1 = FIX((SI_Long)0L);
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	this_char = FIX(UBYTE_16_ISAREF_1(string_1,index_1));
	octal_char = Nil;
	value = Nil;
	ab_loop_list_ = Java_octal_character_literal_alist;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	octal_char = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	value = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = FIXNUM_EQ(octal_char,this_char) ? value : Qnil;
	if (ab_loop_it_) {
	    value_qm = ab_loop_it_;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	value_qm = Qnil;
      end_3:;
	if (value_qm)
	    char_code_1 = FIX(IFIX(char_code_1) * (SI_Long)8L + 
		    IFIX(value_qm));
	else {
	    temp = phrase_cons(Qbad_character_literal,Nil);
	    goto end_4;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = phrase_list_3(Qcharacter_literal,Qoctal,char_code_1);
	goto end_4;
	temp = Qnil;
      end_4:;
    }
    else
	temp = phrase_list_3(Qcharacter_literal,Qsimple,FIX(second_char));
    return VALUES_1(temp);
}

/* TOKENIZE-BAD-JAVA-CHARACTER-LITERAL */
Object tokenize_bad_java_character_literal(string_1,start,end_1)
    Object string_1, start, end_1;
{
    Object temp;

    x_note_fn_call(250,6);
    temp = phrase_cons(Qbad_character_literal,Nil);
    return VALUES_1(temp);
}

Object Java_half_octal_characters = UNBOUND;

Object Java_tokens = UNBOUND;

Object Java_reserved_words_as_uppercase_symbols = UNBOUND;

Object Java_reserved_words_as_string = UNBOUND;

/* INTERN-JAVA-RESERVED-WORD-AS-CATEGORY */
Object intern_java_reserved_word_as_category(reserved_word)
    Object reserved_word;
{
    Object reserved_word_as_lowercase_category;

    x_note_fn_call(250,7);
    reserved_word_as_lowercase_category = 
	    intern_for_java_grammar(string_downcase(1,
	    SYMBOL_NAME(reserved_word)));
    mutate_global_property(reserved_word_as_lowercase_category,T,
	    Qjava_reserved_word_p);
    return VALUES_1(reserved_word_as_lowercase_category);
}

Object Java_reserved_words_as_lowercase_categories = UNBOUND;

Object Java_reserved_expressions_as_lowercase_categories = UNBOUND;

Object Java_reserved_expressions_as_string = UNBOUND;

static Object Qgensym_string;      /* gensym-string */

/* CONVERT-JAVA-SEPARATORS-OR-OPERATORS-TO-SYMBOLS */
Object convert_java_separators_or_operators_to_symbols(string_of_operators)
    Object string_of_operators;
{
    Object this_char, operators, operator_qm, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object component_char, ab_loop_list_, temp, push_arg;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(4);

    x_note_fn_call(250,8);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(string_of_operators));
    this_char = Nil;
    operators = Nil;
    operator_qm = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    this_char = CHR(ICHAR(string_of_operators,index_1));
    if (member_equal(this_char,list_constant)) {
	if (operator_qm) {
	    current_gensym_string = 
		    obtain_simple_gensym_string(FIX((SI_Long)2048L));
	    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		    3);
	      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		      2);
		total_length_of_current_gensym_string = FIX((SI_Long)2048L);
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
			1);
		  current_twriting_output_type = Qgensym_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    component_char = Nil;
		    ab_loop_list_ = reverse(operator_qm);
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    component_char = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    twrite_character(component_char);
		    goto next_loop_1;
		  end_loop_1:;
		    temp = copy_out_current_gensym_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    push_arg = intern_for_java_grammar(temp);
	    operators = CONS(push_arg,operators);
	    operator_qm = Nil;
	}
    }
    else {
	push_arg = this_char;
	operator_qm = CONS(push_arg,operator_qm);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (operator_qm) {
	current_gensym_string = 
		obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		component_char = Nil;
		ab_loop_list_ = reverse(operator_qm);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		component_char = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		twrite_character(component_char);
		goto next_loop_2;
	      end_loop_2:;
		temp = copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = intern_for_java_grammar(temp);
	temp = CONS(temp,operators);
    }
    else
	temp = operators;
    temp = reverse(temp);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Java_separators_as_categories = UNBOUND;

Object Java_operators_as_categories = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Java_editing_categories, Qjava_editing_categories);

/* JAVA-EDITING-CATEGORY-P */
Object java_editing_category_p(category)
    Object category;
{
    Object temp;

    x_note_fn_call(250,9);
    temp = memq_function(category,Java_editing_categories);
    return VALUES_1(temp);
}

static Object Qtl_tl;              /* ~~ */

static Object array_constant;      /* # */

/* COPY-SYMBOL-NAME-OF-POSSIBLE-JAVA-RESERVED-WORD */
Object copy_symbol_name_of_possible_java_reserved_word(symbol,
	    do_not_downcase_qm)
    Object symbol, do_not_downcase_qm;
{
    Object temp;

    x_note_fn_call(250,10);
    temp = ISVREF(Current_edit_state,(SI_Long)9L);
    temp = java_editing_category_p(CADR(temp)) ? (EQ(symbol,Qtl_tl) ? 
	    copy_wide_string(array_constant) : copy_symbol_name(2,symbol,
	    Nil)) : copy_symbol_name_parsably(symbol,do_not_downcase_qm);
    return VALUES_1(temp);
}

static Object Qcopy_symbol_name_of_possible_java_reserved_word;  /* copy-symbol-name-of-possible-java-reserved-word */

/* SET-TOKEN-MENU-STRING-TO-DISPLAY-FOR-JAVA-RESERVED-WORDS */
Object set_token_menu_string_to_display_for_java_reserved_words()
{
    Object category, ab_loop_list_;

    x_note_fn_call(250,11);
    category = Nil;
    ab_loop_list_ = append2(Java_reserved_words_as_lowercase_categories,
	    append2(Java_reserved_expressions_as_lowercase_categories,
	    append2(Java_separators_as_categories,
	    Java_operators_as_categories)));
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_token_menu_string_to_display_function(category,
	    SYMBOL_FUNCTION(Qcopy_symbol_name_of_possible_java_reserved_word));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* JAVA-CLASS-AND-INTERFACE-NAMES-EVALUATION-GETTER */
Object java_class_and_interface_names_evaluation_getter(slot_value_qm,
	    frame,slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object class_or_interface_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(250,12);
    class_or_interface_name = Nil;
    ab_loop_list_ = slot_value_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_or_interface_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    eval_cons_1(copy_as_wide_string(class_or_interface_name),Nil);
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
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object Qtwrite;             /* twrite */

static Object string_constant_2;   /* ", " */

/* WRITE-JAVA-CLASS-AND-INTERFACE-NAMES-FROM-SLOT */
Object write_java_class_and_interface_names_from_slot(slot_value,
	    gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(250,13);
    return twrite_list_function(slot_value,SYMBOL_FUNCTION(Qtwrite),Nil,
	    string_constant_2,string_constant_2);
}

/* JAVA-READ-ONLY-PACKAGE-DECLARATION-EVALUATION-GETTER */
Object java_read_only_package_declaration_evaluation_getter(slot_value_qm,
	    frame,slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object component, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(250,14);
    component = Nil;
    ab_loop_list_ = slot_value_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(copy_as_wide_string(component),Nil);
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
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

/* TWRITE-JAVA-QUALIFIED-NAME */
Object twrite_java_qualified_name(components)
    Object components;
{
    Object component, ab_loop_list_, component_cons, ab_loop_iter_flag_;

    x_note_fn_call(250,15);
    component = Nil;
    ab_loop_list_ = components;
    component_cons = components;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	component_cons = M_CDR(component_cons);
    if ( !TRUEP(component_cons))
	goto end_loop;
    twrite_general_string(component);
    if (CDR(component_cons))
	twrite_character(CHR('.'));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

/* WRITE-JAVA-READ-ONLY-PACKAGE-DECLARATION-FROM-SLOT */
Object write_java_read_only_package_declaration_from_slot(slot_value_qm,
	    gensymed_symbol)
    Object slot_value_qm, gensymed_symbol;
{
    x_note_fn_call(250,16);
    if (slot_value_qm) {
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)8L));
	twrite_java_qualified_name(slot_value_qm);
	return twrite_character(CHR(';'));
    }
    else
	return VALUES_1(Nil);
}

/* JAVA-READ-ONLY-IMPORT-DECLARATIONS-EVALUATION-GETTER */
Object java_read_only_import_declarations_evaluation_getter(slot_value_qm,
	    frame,slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object each_import, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, component, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4, temp;

    x_note_fn_call(250,17);
    each_import = Nil;
    ab_loop_list_ = slot_value_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    each_import = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    component = Nil;
    ab_loop_list__1 = each_import;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    component = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__4 = eval_cons_1(copy_as_wide_string(component),Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar__2;
    goto end_1;
    temp = Qnil;
  end_1:;
    ab_loopvar__2 = eval_cons_1(allocate_evaluation_sequence(temp),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object array_constant_2;    /* # */

/* WRITE-JAVA-READ-ONLY-IMPORT-DECLARATIONS-FROM-SLOT */
Object write_java_read_only_import_declarations_from_slot(slot_value_qm,
	    gensymed_symbol)
    Object slot_value_qm, gensymed_symbol;
{
    Object import_1, ab_loop_list_, import_cons, ab_loop_iter_flag_;

    x_note_fn_call(250,18);
    import_1 = Nil;
    ab_loop_list_ = slot_value_qm;
    import_cons = slot_value_qm;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    import_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	import_cons = M_CDR(import_cons);
    if ( !TRUEP(import_cons))
	goto end_loop;
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)7L));
    twrite_java_qualified_name(import_1);
    twrite_character(CHR(';'));
    if (CDR(import_cons))
	twrite_line_break();
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

static Object Qtext;               /* text */

static Object array_constant_3;    /* # */

static Object Qjava_compilation_unit_or_none;  /* java-compilation-unit-or-none */

/* JAVA-COMPILATION-UNIT-OR-NONE-EVALUATION-SETTER */
Object java_compilation_unit_or_none_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(250,19);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,Qtext,
			      Value_at_type_failure,Type_at_type_failure,
			      Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_java_compilation_unit_or_none_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant_3;
    result = parse_text_string(3,temp_1,Qjava_compilation_unit_or_none,frame);
  end_java_compilation_unit_or_none_evaluation_setter:
    return result;
}

/* JAVA-COMPILATION-UNIT-OR-NONE-EVALUATION-GETTER */
Object java_compilation_unit_or_none_evaluation_getter(text_qm,frame,
	    slot_description)
    Object text_qm, frame, slot_description;
{
    x_note_fn_call(250,20);
    GENSYM_RETURN_ONE(text_qm ? convert_text_to_text_string(1,text_qm) : 
	    copy_constant_wide_string_given_length(array_constant_3,
	    FIX((SI_Long)0L)));
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "Information lost when loading 5.0 beta KB.~%~
				    *          Please re-enter the following into the main text body of ~NF:~%~A"
				    */

/* PRESERVE-INFORMATION-FROM-FORMER-JAVA-TEXT-SLOT */
Object preserve_information_from_former_java_text_slot(external_java_class,
	    old_text_value)
    Object external_java_class, old_text_value;
{
    Object old_text_string;

    x_note_fn_call(250,21);
    old_text_string = convert_text_to_text_string(1,old_text_value);
    if ( !(IFIX(text_string_length(old_text_string)) == (SI_Long)0L))
	notify_user(3,string_constant_3,external_java_class,old_text_string);
    reclaim_text_string(old_text_string);
    reclaim_slot_value(old_text_value);
    return VALUES_1(Nil);
}

static Object Qlost_spaces;        /* lost-spaces */

static Object list_constant_2;     /* # */

/* PROBABLE-TEXT-P */
Object probable_text_p(maybe_text)
    Object maybe_text;
{
    Object maybe_text_element, ab_loop_list_, ab_loop_it_, temp;

    x_note_fn_call(250,22);
    maybe_text_element = Nil;
    ab_loop_list_ = maybe_text;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    maybe_text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CONSP(maybe_text_element) && EQ(M_CAR(maybe_text_element),
	    Qlost_spaces) ? M_CDR(maybe_text_element) : Nil;
    if (temp);
    else
	temp = CONSP(maybe_text_element) ? 
		memq_function(CAR(maybe_text_element),list_constant_2) : Qnil;
    ab_loop_it_ = temp;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qab_slot_value;      /* slot-value */

static Object Qpackage_declaration;  /* package-declaration */

/* PUT-PACKAGE-DECLARATION */
Object put_package_declaration(external_java_class,new_value_qm,initializing_p)
    Object external_java_class, new_value_qm, initializing_p;
{
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object correct_value;

    x_note_fn_call(250,23);
    if (initializing_p && Loading_kb_p && CONSP(new_value_qm) && 
	    probable_text_p(CDR(new_value_qm))) {
	slot_value_pop_store = Nil;
	cons_1 = new_value_qm;
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	new_value_qm = next_cons;
	correct_value = slot_value_pop_store;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_java_class,Qpackage_declaration);
	temp = get_package_declaration_components_if_any(correct_value);
	SVREF(external_java_class,FIX((SI_Long)22L)) = temp;
	if (new_value_qm)
	    return preserve_information_from_former_java_text_slot(external_java_class,
		    new_value_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_java_class,Qpackage_declaration);
	return VALUES_1(SVREF(external_java_class,FIX((SI_Long)22L)) = 
		new_value_qm);
    }
}

static Object Qimport_declarations;  /* import-declarations */

static Object Qtype_import_on_demand;  /* type-import-on-demand */

static Object Qsingle_type_import;  /* single-type-import */

/* PUT-IMPORT-DECLARATIONS */
Object put_import_declarations(external_java_class,new_value_qm,initializing_p)
    Object external_java_class, new_value_qm, initializing_p;
{
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object correct_value, singleton_p, temp_1, flattened_imports_tree;
    Object import_declarations;

    x_note_fn_call(250,24);
    if (initializing_p && Loading_kb_p && CONSP(new_value_qm) && 
	    probable_text_p(CDR(new_value_qm))) {
	slot_value_pop_store = Nil;
	cons_1 = new_value_qm;
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	new_value_qm = next_cons;
	correct_value = slot_value_pop_store;
	singleton_p = Nil;
	if (CONSP(correct_value)) {
	    temp_1 = CAR(correct_value);
	    if (EQ(temp_1,Qimport_declarations))
		flattened_imports_tree = CDR(correct_value);
	    else if (EQ(temp_1,Qtype_import_on_demand) || EQ(temp_1,
		    Qsingle_type_import)) {
		singleton_p = T;
		flattened_imports_tree = slot_value_cons_1(correct_value,Nil);
	    }
	    else
		flattened_imports_tree = Nil;
	}
	else
	    flattened_imports_tree = Nil;
	import_declarations = 
		get_import_declarations_if_any(flattened_imports_tree);
	if (singleton_p)
	    reclaim_slot_value_list_1(flattened_imports_tree);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_java_class,Qimport_declarations);
	SVREF(external_java_class,FIX((SI_Long)23L)) = import_declarations;
	if (new_value_qm)
	    return preserve_information_from_former_java_text_slot(external_java_class,
		    new_value_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_java_class,Qimport_declarations);
	return VALUES_1(SVREF(external_java_class,FIX((SI_Long)23L)) = 
		new_value_qm);
    }
}

static Object Qnone;               /* none */

static Object Qcompilation_unit;   /* compilation-unit */

/* PUT-COMPILATION-UNIT */
Object put_compilation_unit(external_java_class,new_value,gensymed_symbol)
    Object external_java_class, new_value, gensymed_symbol;
{
    Object none_text, cdr_new_value;

    x_note_fn_call(250,25);
    if (CONSP(new_value) && EQ(CAR(new_value),Qnone)) {
	none_text = CDR(new_value);
	reclaim_text(none_text);
	cdr_new_value = make_empty_text();
	M_CDR(new_value) = cdr_new_value;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(external_java_class,Qcompilation_unit);
    return VALUES_1(SVREF(external_java_class,FIX((SI_Long)24L)) = new_value);
}

/* PUT-TYPE-DECLARATIONS-WHERE-SLOT-IS-ABSENT */
Object put_type_declarations_where_slot_is_absent(external_java_class,
	    type_declarations)
    Object external_java_class, type_declarations;
{
    x_note_fn_call(250,26);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(external_java_class,Qcompilation_unit);
    SVREF(external_java_class,FIX((SI_Long)24L)) = type_declarations;
    return VALUES_1(Nil);
}

/* COMPILE-JAVA-COMPILATION-UNIT-OR-NONE-FOR-SLOT */
Object compile_java_compilation_unit_or_none_for_slot varargs_1(int, n)
{
    Object java_syntax_tree, external_java_class, gensymed_symbol;
    Object class_name_symbols, package_components_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(250,27);
    INIT_ARGS_nonrelocating();
    java_syntax_tree = REQUIRED_ARG_nonrelocating();
    external_java_class = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    update_package_declaration_for_external_java_class(external_java_class,
	    java_syntax_tree);
    update_import_declarations_for_external_java_class(external_java_class,
	    java_syntax_tree);
    class_name_symbols = 
	    get_class_name_symbols_for_external_java_class(java_syntax_tree);
    package_components_qm = ISVREF(external_java_class,(SI_Long)22L);
    update_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm);
    reclaim_slot_value_list_1(class_name_symbols);
    return VALUES_1(java_syntax_tree);
}

/* GET-CANONICAL-JAVA-NAME-AS-NEW-SLOT-VALUE */
Object get_canonical_java_name_as_new_slot_value(internal_name)
    Object internal_name;
{
    Object components, component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;
    char singleton_p;

    x_note_fn_call(250,28);
    singleton_p = EQ(FIRST(internal_name),Qidentifier);
    components = singleton_p ? slot_value_cons_1(internal_name,Nil) : 
	    CDR(internal_name);
    component = Nil;
    ab_loop_list_ = components;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    component = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    slot_value_cons_1(copy_text_string(symbol_name_text_string(component)),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    if (singleton_p)
	reclaim_slot_value_list_1(components);
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-PACKAGE-DECLARATION-COMPONENTS-IF-ANY */
Object get_package_declaration_components_if_any(package_declaration)
    Object package_declaration;
{
    Object gensymed_symbol, internal_name, temp;

    x_note_fn_call(250,29);
    if (CONSP(package_declaration)) {
	gensymed_symbol = package_declaration;
	gensymed_symbol = CDR(gensymed_symbol);
	internal_name = CAR(gensymed_symbol);
	temp = CONSP(internal_name) ? 
		get_canonical_java_name_as_new_slot_value(internal_name) : 
		Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* UPDATE-PACKAGE-DECLARATION-FOR-EXTERNAL-JAVA-CLASS */
Object update_package_declaration_for_external_java_class(external_java_class,
	    compilation_unit_syntax_tree)
    Object external_java_class, compilation_unit_syntax_tree;
{
    Object temp, thing, ab_loop_list_, ab_loop_it_, package_syntax_tree;
    Object package_declaration;

    x_note_fn_call(250,30);
    if (CONSP(compilation_unit_syntax_tree)) {
	temp = CAR(compilation_unit_syntax_tree);
	if (EQ(temp,Qcompilation_unit)) {
	    thing = Nil;
	    ab_loop_list_ = CDR(compilation_unit_syntax_tree);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    thing = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = CONSP(thing) && EQ(CAR(thing),Qpackage_type) ? 
		    thing : Qnil;
	    if (ab_loop_it_) {
		package_syntax_tree = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    package_syntax_tree = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qpackage_type))
	    package_syntax_tree = compilation_unit_syntax_tree;
	else
	    package_syntax_tree = Nil;
    }
    else
	package_syntax_tree = Nil;
    package_declaration = 
	    get_package_declaration_components_if_any(package_syntax_tree);
    change_slot_value(3,external_java_class,Qpackage_declaration,
	    package_declaration);
    return VALUES_1(Nil);
}

static Object array_constant_4;    /* # */

/* GET-IMPORT-DECLARATIONS-IF-ANY */
Object get_import_declarations_if_any(flattened_imports_tree)
    Object flattened_imports_tree;
{
    Object internal_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp, import_declarations, type;
    Object canonical_list, ab_loop_list__1, cdr_arg, cdr_new_value;

    x_note_fn_call(250,31);
    internal_name = Nil;
    ab_loop_list_ = flattened_imports_tree;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    internal_name = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    slot_value_cons_1(get_canonical_java_name_as_new_slot_value(internal_name),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    import_declarations = ab_loopvar_;
    goto end_1;
    import_declarations = Qnil;
  end_1:;
    type = Nil;
    ab_loop_list_ = flattened_imports_tree;
    canonical_list = Nil;
    ab_loop_list__1 = import_declarations;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    canonical_list = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(type,Qtype_import_on_demand)) {
	cdr_arg = last(canonical_list,_);
	cdr_new_value = 
		slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_4,
		FIX((SI_Long)1L)),Nil);
	M_CDR(cdr_arg) = cdr_new_value;
    }
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(import_declarations);
}

/* UPDATE-IMPORT-DECLARATIONS-FOR-EXTERNAL-JAVA-CLASS */
Object update_import_declarations_for_external_java_class(external_java_class,
	    compilation_unit_syntax_tree)
    Object external_java_class, compilation_unit_syntax_tree;
{
    Object singleton_p, temp, thing, ab_loop_list_, flattened_imports_tree;
    Object import_declarations;

    x_note_fn_call(250,32);
    singleton_p = Nil;
    if (CONSP(compilation_unit_syntax_tree)) {
	temp = CAR(compilation_unit_syntax_tree);
	if (EQ(temp,Qcompilation_unit)) {
	    thing = Nil;
	    ab_loop_list_ = compilation_unit_syntax_tree;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    thing = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(thing)) {
		temp = CAR(thing);
		if (EQ(temp,Qimport_declarations)) {
		    flattened_imports_tree = CDR(thing);
		    goto end_1;
		}
		else if (EQ(temp,Qtype_import_on_demand) || EQ(temp,
			Qsingle_type_import)) {
		    singleton_p = T;
		    flattened_imports_tree = slot_value_cons_1(thing,Nil);
		    goto end_1;
		}
	    }
	    goto next_loop;
	  end_loop:
	    flattened_imports_tree = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qimport_declarations))
	    flattened_imports_tree = CDR(compilation_unit_syntax_tree);
	else if (EQ(temp,Qtype_import_on_demand) || EQ(temp,
		Qsingle_type_import)) {
	    singleton_p = T;
	    flattened_imports_tree = 
		    slot_value_cons_1(compilation_unit_syntax_tree,Nil);
	}
	else
	    flattened_imports_tree = Nil;
    }
    else
	flattened_imports_tree = Nil;
    import_declarations = 
	    get_import_declarations_if_any(flattened_imports_tree);
    if (singleton_p)
	reclaim_slot_value_list_1(flattened_imports_tree);
    change_slot_value(3,external_java_class,Qimport_declarations,
	    import_declarations);
    return VALUES_1(Nil);
}

/* UPPER-CASE-ALPHA-CHAR-PW */
Object upper_case_alpha_char_pw(char_1)
    Object char_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(250,33);
    gensymed_symbol = char_1;
    if ((SI_Long)97L <= IFIX(gensymed_symbol) && IFIX(gensymed_symbol) <= 
	    (SI_Long)122L || (SI_Long)65L <= IFIX(gensymed_symbol) && 
	    IFIX(gensymed_symbol) <= (SI_Long)90L) {
	gensymed_symbol = char_1;
	temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		(IFIX(gensymed_symbol) <= (SI_Long)90L ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* LOWER-CASE-ALPHA-CHAR-PW */
Object lower_case_alpha_char_pw(char_1)
    Object char_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(250,34);
    gensymed_symbol = char_1;
    temp = (SI_Long)97L <= IFIX(gensymed_symbol) && IFIX(gensymed_symbol) 
	    <= (SI_Long)122L || (SI_Long)65L <= IFIX(gensymed_symbol) && 
	    IFIX(gensymed_symbol) <= (SI_Long)90L ? lower_case_pw(char_1) :
	     Nil;
    return VALUES_1(temp);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* CONVERT-MIXED-CASE-TEXT-TO-HYPHENATED-SYMBOL */
Object convert_mixed_case_text_to_hyphenated_symbol(mixed_case_text)
    Object mixed_case_text;
{
    Object previous_char_qm, this_char, this_subsequence_qm, all_subsequences;
    Object ab_loop_iter_flag_, temp, char_before_previous_char_qm;
    Object initial_upcased_char, acronym_subsequence, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object subsequence, ab_loop_list_, subsequence_cons, last_subsequence_p;
    Object char_1, ab_loop_list__1, code, simple_or_wide_character, thing;
    Object temp_2, schar_arg_2, schar_new_value;
    SI_Long index_1, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    char temp_1;
    char thing_1;
    Declare_special(5);

    x_note_fn_call(250,35);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(mixed_case_text));
    previous_char_qm = Nil;
    this_char = Nil;
    this_subsequence_qm = Nil;
    all_subsequences = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	previous_char_qm = this_char;
    this_char = FIX(UBYTE_16_ISAREF_1(mixed_case_text,index_1));
    if (upper_case_alpha_char_pw(this_char) && previous_char_qm && 
	    lower_case_alpha_char_pw(previous_char_qm)) {
	temp = nreverse(this_subsequence_qm);
	all_subsequences = token_cons_1(temp,all_subsequences);
	this_subsequence_qm = token_cons_1(this_char,Nil);
    }
    else {
	if (lower_case_alpha_char_pw(this_char) && previous_char_qm && 
		upper_case_alpha_char_pw(previous_char_qm)) {
	    char_before_previous_char_qm = SECOND(this_subsequence_qm);
	    temp_1 = char_before_previous_char_qm ? 
		    TRUEP(upper_case_alpha_char_pw(char_before_previous_char_qm)) 
		    : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    initial_upcased_char = CAR(this_subsequence_qm);
	    acronym_subsequence = CDR(this_subsequence_qm);
	    reclaim_token_cons_1(this_subsequence_qm);
	    temp = nreverse(acronym_subsequence);
	    all_subsequences = token_cons_1(temp,all_subsequences);
	    this_subsequence_qm = token_list_2(this_char,initial_upcased_char);
	}
	else
	    this_subsequence_qm = token_cons_1(this_char,this_subsequence_qm);
    }
    ab_loop_iter_flag_ = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (this_subsequence_qm) {
	temp = nreverse(this_subsequence_qm);
	all_subsequences = token_cons_1(temp,all_subsequences);
    }
    all_subsequences = nreverse(all_subsequences);
    reclaim_text_string(mixed_case_text);
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
	      subsequence = Nil;
	      ab_loop_list_ = all_subsequences;
	      subsequence_cons = all_subsequences;
	      last_subsequence_p = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      subsequence = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_iter_flag_))
		  subsequence_cons = M_CDR(subsequence_cons);
	      if ( !TRUEP(subsequence_cons))
		  goto end_loop_1;
	      last_subsequence_p =  !TRUEP(CDR(subsequence_cons)) ? T : Nil;
	      char_1 = Nil;
	      ab_loop_list__1 = subsequence;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_2;
	      char_1 = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      code = char_1;
	      if (IFIX(code) < (SI_Long)127L)
		  simple_or_wide_character = (SI_Long)97L <= IFIX(code) && 
			  IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) + 
			  (SI_Long)-32L) : code;
	      else {
		  simple_or_wide_character = 
			  unicode_uppercase_if_lowercase(code);
		  if (simple_or_wide_character);
		  else
		      simple_or_wide_character = code;
	      }
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_2 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		  temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_2;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      if ( !TRUEP(last_subsequence_p)) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing_1 = '-';
		      twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			      CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_2 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing_1 = '-';
		      schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) 
			      ? CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		      SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		      temp_2 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_2;
		  }
	      }
	      reclaim_token_list_1(subsequence);
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_token_list_1(all_subsequences);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return intern_text_string(1,temp);
    return VALUES_1(Qnil);
}

/* MAKE-G2-NAME-FOR-JAVA-CLASS */
Object make_g2_name_for_java_class(java_class_name,package_components)
    Object java_class_name, package_components;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object component, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(250,36);
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
	      component = Nil;
	      ab_loop_list_ = package_components;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      component = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      twrite_symbol(2,
		      convert_mixed_case_text_to_hyphenated_symbol(copy_text_string(component)),
		      T);
	      twrite_character(CHR('.'));
	      goto next_loop;
	    end_loop:;
	      twrite_symbol(2,
		      convert_mixed_case_text_to_hyphenated_symbol(copy_text_string(symbol_name_text_string(java_class_name))),
		      T);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = intern_text_string(1,temp);
    return VALUES_1(temp);
}

static Object list_constant_3;     /* # */

static Object Qtype_declarations;  /* type-declarations */

/* GET-CLASS-NAME-SYMBOLS-FOR-EXTERNAL-JAVA-CLASS */
Object get_class_name_symbols_for_external_java_class(java_syntax_tree)
    Object java_syntax_tree;
{
    Object temp, flattened_list_of_class_subtrees, subtree, ab_loop_list_;
    Object ab_loop_it_, accum, class_info, ab_loop_list__1, java_class_name_qm;

    x_note_fn_call(250,37);
    if (EQ(java_syntax_tree,Bad_phrase) || EQ(java_syntax_tree,Qnone))
	temp = Nil;
    else if (CONSP(java_syntax_tree)) {
	if (memq_function(CAR(java_syntax_tree),list_constant_3))
	    flattened_list_of_class_subtrees = 
		    phrase_cons(java_syntax_tree,Nil);
	else if (EQ(CAR(java_syntax_tree),Qtype_declarations))
	    flattened_list_of_class_subtrees = CDR(java_syntax_tree);
	else {
	    subtree = Nil;
	    ab_loop_list_ = java_syntax_tree;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    subtree = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = CONSP(subtree) && EQ(CAR(subtree),
		    Qtype_declarations) ? CDR(subtree) : Qnil;
	    if (ab_loop_it_) {
		flattened_list_of_class_subtrees = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    flattened_list_of_class_subtrees = Qnil;
	  end_1:;
	}
	subtree = Nil;
	ab_loop_list_ = flattened_list_of_class_subtrees;
	accum = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	subtree = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(subtree) && memq_function(CAR(subtree),list_constant_3)) {
	    class_info = Nil;
	    ab_loop_list__1 = subtree;
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    class_info = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = CONSP(class_info) && EQ(CAR(class_info),
		    Qidentifier) ? CADR(class_info) : Qnil;
	    if (ab_loop_it_) {
		java_class_name_qm = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    java_class_name_qm = Qnil;
	  end_2:;
	    if (java_class_name_qm)
		accum = slot_value_cons_1(java_class_name_qm,accum);
	}
	goto next_loop_1;
      end_loop_1:
	temp = nreverse(accum);
	goto end_3;
	temp = Qnil;
      end_3:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* UPDATE-G2-SIDE-NAMES-FOR-EXTERNAL-JAVA-CLASS */
Object update_g2_side_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm)
    Object external_java_class, class_name_symbols, package_components_qm;
{
    Object java_class_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_names;

    x_note_fn_call(250,38);
    if (ISVREF(external_java_class,(SI_Long)20L)) {
	if ( !TRUEP(class_name_symbols) || CDR(class_name_symbols)) {
	    java_class_name = Nil;
	    ab_loop_list_ = class_name_symbols;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    java_class_name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    slot_value_cons_1(make_g2_name_for_java_class(java_class_name,
		    package_components_qm),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    new_names = ab_loopvar_;
	    goto end_1;
	    new_names = Qnil;
	  end_1:;
	    change_slot_value(3,external_java_class,
		    Qname_or_names_for_frame,new_names);
	}
	else
	    change_slot_value(3,external_java_class,
		    Qname_or_names_for_frame,
		    make_g2_name_for_java_class(CAR(class_name_symbols),
		    package_components_qm));
    }
    return VALUES_1(Nil);
}

static Object Qjava_class_and_interface_names;  /* java-class-and-interface-names */

/* UPDATE-JAVA-SIDE-NAMES-FOR-EXTERNAL-JAVA-CLASS */
Object update_java_side_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm)
    Object external_java_class, class_name_symbols, package_components_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object component, ab_loop_list_, package_prefix_qm, java_class_name;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object java_class_or_interface_names;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(250,39);
    if (package_components_qm) {
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
		  component = Nil;
		  ab_loop_list_ = package_components_qm;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  component = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  twrite_general_string(component);
		  twrite_character(CHR('.'));
		  goto next_loop;
		end_loop:;
		  package_prefix_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	package_prefix_qm = Nil;
    java_class_name = Nil;
    ab_loop_list_ = class_name_symbols;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    java_class_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
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
	      if (package_prefix_qm)
		  twrite_general_string(package_prefix_qm);
	      twrite_symbol(2,java_class_name,T);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = slot_value_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    java_class_or_interface_names = ab_loopvar_;
    goto end_1;
    java_class_or_interface_names = Qnil;
  end_1:;
    change_slot_value(3,external_java_class,
	    Qjava_class_and_interface_names,java_class_or_interface_names);
    if (package_prefix_qm)
	reclaim_text_string(package_prefix_qm);
    return VALUES_1(Nil);
}

/* UPDATE-NAMES-FOR-EXTERNAL-JAVA-CLASS */
Object update_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm)
    Object external_java_class, class_name_symbols, package_components_qm;
{
    x_note_fn_call(250,40);
    update_g2_side_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm);
    update_java_side_names_for_external_java_class(external_java_class,
	    class_name_symbols,package_components_qm);
    return VALUES_1(Nil);
}

static Object Qprocedure;          /* procedure */

static Object Qg2_new_secret_entity;  /* g2-new-secret-entity */

static Object list_constant_4;     /* # */

/* INSTANTIABLE-SECRET-JAVA-CLASS-P */
Object instantiable_secret_java_class_p(class_1)
    Object class_1;
{
    Object temp;

    x_note_fn_call(250,41);
    temp = get_instance_with_name_if_any(Qprocedure,Qg2_new_secret_entity) 
	    ? memq_function(class_1,list_constant_4) : Qnil;
    return VALUES_1(temp);
}

Object Caret_replacement_for_javac_problem = UNBOUND;

/* NEWLINE-TEXT-STRING-CHARACTER-P */
Object newline_text_string_character_p(wchar)
    Object wchar;
{
    Object temp;

    x_note_fn_call(250,42);
    temp = IFIX(wchar) == (SI_Long)13L ? T : Nil;
    if (temp);
    else
	temp = IFIX(wchar) == (SI_Long)10L ? T : Nil;
    if (temp);
    else
	temp = IFIX(wchar) == (SI_Long)10L ? T : Nil;
    if (temp);
    else
	temp = IFIX(wchar) == (SI_Long)8232L ? T : Nil;
    return VALUES_1(temp);
}

/* WHITESPACE-TEXT-STRING-CHARACTER-P */
Object whitespace_text_string_character_p(wchar)
    Object wchar;
{
    Object temp;

    x_note_fn_call(250,43);
    temp = newline_text_string_character_p(wchar);
    if (temp);
    else
	temp = IFIX(wchar) == (SI_Long)32L ? T : Nil;
    if (temp);
    else
	temp = IFIX(wchar) == (SI_Long)9L ? T : Nil;
    return VALUES_1(temp);
}

static Object array_constant_5;    /* # */

/* PROBLEM-HEADER-IN-JAVAC-PROBLEM-P */
Object problem_header_in_javac_problem_p(line)
    Object line;
{
    Object temp;

    x_note_fn_call(250,44);
    temp = gensym_search_simple(array_constant_5,line);
    return VALUES_1(temp);
}

/* CARET-POSITION-IN-JAVAC-PROBLEM-LINE-IF-ANY */
Object caret_position_in_javac_problem_line_if_any(line)
    Object line;
{
    Object this_wchar, position_qm, temp;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(250,45);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(line));
    this_wchar = Nil;
    position_qm = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    this_wchar = FIX(UBYTE_16_ISAREF_1(line,index_1));
    if (IFIX(this_wchar) == (SI_Long)32L);
    else if (IFIX(this_wchar) == (SI_Long)94L)
	position_qm = FIX(index_1);
    else {
	temp = Nil;
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = position_qm;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qjava;               /* java */

/* GET-NEXT-JAVAC-PROBLEM-IF-ANY */
Object get_next_javac_problem_if_any(problems_text_string,
	    inclusive_start_index)
    Object problems_text_string, inclusive_start_index;
{
    Object length_1, lines_for_this_problem_qm, previous_newline_index;
    Object this_newline_index_qm, no_more_lines_p, this_line;
    Object caret_position_in_this_line_qm, source_line_qm, caret_index_qm;
    Object next_inclusive_start_index_qm, coalesce_p, this_wchar, temp, temp_1;
    Object java_pop_store, cons_1, next_cons, temp_2, svref_arg_2;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object line, ab_loop_list_, before, after;
    SI_Long line_index, ab_loop_bind_, index_1, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_2;
    char temp_3;
    Declare_special(5);

    x_note_fn_call(250,46);
    length_1 = text_string_length(problems_text_string);
    lines_for_this_problem_qm = Nil;
    previous_newline_index = inclusive_start_index;
    this_newline_index_qm = Nil;
    no_more_lines_p = Nil;
    this_line = Nil;
    caret_position_in_this_line_qm = Nil;
    source_line_qm = Nil;
    caret_index_qm = Nil;
    next_inclusive_start_index_qm = Nil;
    coalesce_p = Nil;
  next_loop:
    line_index = IFIX(previous_newline_index);
    ab_loop_bind_ = IFIX(length_1);
    this_wchar = Nil;
  next_loop_1:
    if (line_index >= ab_loop_bind_)
	goto end_loop;
    this_wchar = FIX(UBYTE_16_ISAREF_1(problems_text_string,line_index));
    if (newline_text_string_character_p(this_wchar)) {
	this_newline_index_qm = FIX(line_index);
	goto end_1;
    }
    line_index = line_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop:
    this_newline_index_qm = Nil;
    goto end_1;
    this_newline_index_qm = Qnil;
  end_1:;
    no_more_lines_p =  !TRUEP(this_newline_index_qm) ? T : Nil;
    temp = previous_newline_index;
    temp_1 = this_newline_index_qm;
    if (temp_1);
    else
	temp_1 = length_1;
    this_line = text_string_substring(problems_text_string,temp,temp_1);
    caret_position_in_this_line_qm = 
	    caret_position_in_javac_problem_line_if_any(this_line);
    coalesce_p = Nil;
    if (caret_position_in_this_line_qm) {
	if ( !(IFIX(caret_position_in_this_line_qm) == (SI_Long)0L)) {
	    caret_index_qm = caret_position_in_this_line_qm;
	    java_pop_store = Nil;
	    cons_1 = lines_for_this_problem_qm;
	    if (cons_1) {
		java_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qjava);
		if (ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_java_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = cons_1;
		    temp_2 = Available_java_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		else {
		    temp_2 = Available_java_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		    temp_2 = Available_java_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    lines_for_this_problem_qm = next_cons;
	    source_line_qm = java_pop_store;
	}
	if (no_more_lines_p)
	    coalesce_p = lines_for_this_problem_qm ? T : Qnil;
	reclaim_text_string(this_line);
    }
    else if (problem_header_in_javac_problem_p(this_line)) {
	if (lines_for_this_problem_qm) {
	    reclaim_text_string(this_line);
	    coalesce_p = T;
	    if ( !TRUEP(no_more_lines_p)) {
		if (FIXNUM_LT(previous_newline_index,length_1))
		    next_inclusive_start_index_qm = previous_newline_index;
	    }
	}
	else {
	    lines_for_this_problem_qm = java_cons_1(this_line,
		    lines_for_this_problem_qm);
	    if (no_more_lines_p)
		coalesce_p = T;
	}
    }
    else if (lines_for_this_problem_qm) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(text_string_length(this_line));
	this_wchar = Nil;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	this_wchar = FIX(UBYTE_16_ISAREF_1(this_line,index_1));
	if ( !TRUEP(whitespace_text_string_character_p(this_wchar))) {
	    temp_3 = TRUEP(Nil);
	    goto end_2;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_1:
	temp_3 = TRUEP(T);
	goto end_2;
	temp_3 = TRUEP(Qnil);
      end_2:;
	if ( !temp_3)
	    lines_for_this_problem_qm = java_cons_1(this_line,
		    lines_for_this_problem_qm);
	if (no_more_lines_p)
	    coalesce_p = T;
    }
    else
	reclaim_text_string(this_line);
    if (coalesce_p) {
	lines_for_this_problem_qm = nreverse(lines_for_this_problem_qm);
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  line = Nil;
		  ab_loop_list_ = lines_for_this_problem_qm;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  line = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if ( !(IFIX(text_string_length(line)) == (SI_Long)0L)) {
		      twrite_general_string(line);
		      twrite_line_break();
		  }
		  reclaim_text_string(line);
		  goto next_loop_3;
		end_loop_2:
		  reclaim_java_list_1(lines_for_this_problem_qm);
		  if (caret_index_qm && source_line_qm) {
		      before = text_string_substring(source_line_qm,
			      FIX((SI_Long)0L),caret_index_qm);
		      temp = source_line_qm;
		      temp_1 = caret_index_qm;
		      after = text_string_substring(temp,temp_1,
			      text_string_length(source_line_qm));
		      twrite_general_string(before);
		      twrite_general_string(Caret_replacement_for_javac_problem);
		      twrite_general_string(after);
		      reclaim_text_string(before);
		      reclaim_text_string(after);
		      reclaim_text_string(source_line_qm);
		  }
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return VALUES_2(temp_1,next_inclusive_start_index_qm);
    }
    else if (no_more_lines_p)
	return VALUES_2(Nil,Nil);
    previous_newline_index = FIXNUM_ADD1(this_newline_index_qm);
    goto next_loop;
  end_loop_3:
    return VALUES_1(Qnil);
}

static Object Qexternal_java_class;  /* external-java-class */

static Object Qreplace_javac_frame_notes;  /* replace-javac-frame-notes */

static Object Qadd_javac_frame_notes;  /* add-javac-frame-notes */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qdelete_javac_frame_notes;  /* delete-javac-frame-notes */

static Object Qjava_compilation_problems;  /* java-compilation-problems */

static Object Qdelete_frame_note_if_any;  /* delete-frame-note-if-any */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* OPERATE-ON-JAVAC-FRAME-NOTES */
Object operate_on_javac_frame_notes(java_instance,type_of_operation,
	    operation_info)
    Object java_instance, type_of_operation, operation_info;
{
    Object succeeded_p, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, x2, current_computation_frame;
    Object current_computation_flags, next_index_qm, problem_qm;
    Object at_least_one_p, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(250,47);
    succeeded_p = Nil;
    gensymed_symbol = ISVREF(java_instance,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qexternal_java_class,
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
    if (temp);
    else
	goto exit_point;
    if (EQ(type_of_operation,Qreplace_javac_frame_notes) || 
	    EQ(type_of_operation,Qadd_javac_frame_notes)) {
	if (text_string_p(operation_info));
	else {
	    if (SIMPLE_VECTOR_P(operation_info) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(operation_info)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(operation_info,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(operation_info,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(operation_info,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_parameter_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		current_computation_frame = operation_info;
		current_computation_flags = Current_computation_flags;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  0);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)4L);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)256L);
		    operation_info = 
			    get_current_evaluation_value(operation_info,Nil);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		goto exit_point;
	}
    }
    else if (EQ(type_of_operation,Qdelete_javac_frame_notes));
    else
	goto exit_point;
    if (EQ(type_of_operation,Qreplace_javac_frame_notes) || 
	    EQ(type_of_operation,Qdelete_javac_frame_notes)) {
	delete_frame_note_if_any(Qjava_compilation_problems,java_instance);
	if (EQ(type_of_operation,Qdelete_javac_frame_notes))
	    succeeded_p = T;
    }
    if (EQ(type_of_operation,Qreplace_javac_frame_notes) || 
	    EQ(type_of_operation,Qadd_javac_frame_notes)) {
	next_index_qm = FIX((SI_Long)0L);
	problem_qm = Nil;
	at_least_one_p = Nil;
      next_loop:
	if ( !TRUEP(next_index_qm))
	    goto end_loop;
	result = get_next_javac_problem_if_any(operation_info,next_index_qm);
	MVS_2(result,problem_qm,next_index_qm);
	if ( !TRUEP(problem_qm))
	    goto end_loop;
	add_to_frame_note_particulars_list_if_necessary(problem_qm,
		Qjava_compilation_problems,java_instance);
	at_least_one_p = T;
	goto next_loop;
      end_loop:
	if (at_least_one_p)
	    succeeded_p = T;
    }
    goto exit_point;
  exit_point:
    if (EQ(type_of_operation,Qreplace_javac_frame_notes) || 
	    EQ(type_of_operation,Qadd_javac_frame_notes)) {
	if (text_string_p(operation_info))
	    reclaim_text_string(operation_info);
    }
    else if (EQ(type_of_operation,Qdelete_frame_note_if_any)) {
	gensymed_symbol = operation_info;
	temp = FIXNUMP(gensymed_symbol);
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state);
	    if (temp);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_1:
		if (level < ab_loop_bind_)
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_3;
	      end_loop_2:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_1;
		goto next_loop_2;
	      end_loop_3:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    reclaim_evaluation_value(operation_info);
    }
    if (succeeded_p)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
    return VALUES_1(Qnil);
}

static Object array_constant_6;    /* # */

static Object string_constant_4;   /* "(~A) " */

static Object array_constant_7;    /* # */

/* WRITE-JAVA-COMPILATION-PROBLEMS-NOTE */
Object write_java_compilation_problems_note(compilation_problems,
	    gensymed_symbol)
    Object compilation_problems, gensymed_symbol;
{
    Object compilation_problem, ab_loop_list_, compilation_problem_cons;
    Object ab_loop_iter_flag_, temp;
    SI_Long index_1;

    x_note_fn_call(250,48);
    if (CDR(compilation_problems)) {
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)60L));
	twrite_line_break();
	compilation_problem = Nil;
	ab_loop_list_ = compilation_problems;
	compilation_problem_cons = compilation_problems;
	index_1 = IFIX(Frame_note_index);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	compilation_problem = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    compilation_problem_cons = M_CDR(compilation_problem_cons);
	if ( !TRUEP(compilation_problem_cons))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 + (SI_Long)1L;
	tformat(2,string_constant_4,FIX(index_1));
	twrite_general_string(compilation_problem);
	if (CDR(compilation_problem_cons))
	    twrite_line_break();
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	Frame_note_index = FIX(index_1 + (SI_Long)1L);
	temp = Qnil;
    }
    else {
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)46L));
	twrite_line_break();
	temp = twrite_general_string(CAR(compilation_problems));
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

void java2_INIT()
{
    Object list0, result_1, last_1, entry, thing, temp, temp_1, new_last;
    Object valid_token_actions_new_value, temp_2, temp_3, temp_4, temp_5;
    Object temp_6, temp_7, temp_8, temp_9, temp_10, x, symbol, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, reserved_expression;
    Object java_class_and_interface_names_evaluation_getter_1;
    Object java_read_only_package_declaration_evaluation_getter_1;
    Object java_read_only_import_declarations_evaluation_getter_1;
    Object java_compilation_unit_or_none_evaluation_setter_1;
    Object java_compilation_unit_or_none_evaluation_getter_1, gensymed_symbol;
    Object write_java_compilation_problems_note_1;
    Object Qframe_note_writer_1, list_constant_178, AB_package;
    Object Qoperate_on_javac_frame_notes, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qfunction_keeps_procedure_environment_valid_qm, string_constant_182;
    Object Qexport_definition, Qexternal_method, Qexternal_method_declaration;
    Object Qexternal_procedure, Qinterface, Qab_class;
    Object Qconvert_mixed_case_text_to_hyphenated_symbol;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler;
    Object Qcompile_java_compilation_unit_or_none_for_slot;
    Object Qabsent_slot_putter, Qput_type_declarations_where_slot_is_absent;
    Object Qslot_putter, Qput_compilation_unit, Qput_import_declarations;
    Object Qput_package_declaration, Qline_width;
    Object Qtext_category_slot_access_extracter, Qcategory_extracter_function;
    Object Qtext_category_slot_access_committer, Qcategory_committer_function;
    Object Qnamed, Qtype_specification_simple_expansion, Qslot_value_writer;
    Object Qwrite_java_read_only_import_declarations_from_slot;
    Object Qjava_read_only_import_declarations, list_constant_182;
    Object list_constant_180, list_constant_181, list_constant_179;
    Object Qwrite_java_read_only_package_declaration_from_slot;
    Object Qjava_read_only_package_declaration;
    Object Qwrite_java_class_and_interface_names_from_slot, QNONE;
    Object string_constant_181, string_constant_180, list_constant_177;
    Object Qjava_class_body_declarations_or_none, list_constant_176, QNULL;
    Object QFALSE, QTRUE, list_constant_175, list_constant_174, Qprivate, Qnew;
    Object Qnative, Qlong, Qint, Qinstanceof, Qimplements, Qab_if, Qgoto, Qfor;
    Object Qfinally, Qfinal, Qextends, Qelse, Qdouble, Qdefault, Qab_continue;
    Object Qconst, Qab_catch, Qboolean, Qabstract, Qwhile, Qvolatile, Qvoid;
    Object Qtry, Qtransient, Qthrows, Qthis, Qsynchronized, Qswitch, Qsuper;
    Object Qstatic, Qshort, Qpublic, Qprotected, Qeither;
    Object Qself_terminating_punctuation_mark, list_constant_173;
    Object list_constant_172, list_constant_171, list_constant_170;
    Object list_constant_169, list_constant_168, list_constant_167;
    Object list_constant_166, list_constant_165, list_constant_164;
    Object Qjava_symbol, list_constant_163, Qinverted_class;
    Object Qchar_within_single_line_comment, Qcharacter_class, Qnewline_char;
    Object Qbad_octal_character_literal, list_constant_162, list_constant_161;
    Object Qbad_escape_character_literal, Qhalf_octal_character_literal;
    Object Qoctal_character_literal, Qescape_character_literal, Qjava_digit;
    Object Qjava_letter_or_digit_quote_free, Qjava_letter_or_digit;
    Object Qjava_letter_quote_free, Qjava_letter;
    Object Qtokenize_bad_java_character_literal, list_constant_160;
    Object Qbad_java_character_literal, list_constant_159, list_constant_158;
    Object list_constant_157, list_constant_156, list_constant_155;
    Object list_constant_154, list_constant_153, list_constant_152;
    Object list_constant_151, list_constant_150, list_constant_146;
    Object list_constant_133, list_constant_135, list_constant_134;
    Object list_constant_149, list_constant_148, list_constant_147, Qpattern;
    Object list_constant_132, list_constant_139, list_constant_145;
    Object list_constant_143, Qtokenize_java_character_literal;
    Object list_constant_144, Qjava_character_literal, list_constant_142;
    Object list_constant_141, list_constant_140, list_constant_138;
    Object list_constant_137, list_constant_136, Qsimple_character_literal;
    Object Qalphabet_strip_delimitors_off_string, list_constant_131;
    Object Qwhole_string, list_constant_130, list_constant_129, Qkleene;
    Object list_constant_128, list_constant_127, Qab_string_char;
    Object list_constant_126, Qab_dot, list_constant_110, list_constant_125;
    Object list_constant_124, list_constant_123, list_constant_122, Qmaybe;
    Object list_constant_121, list_constant_120, list_constant_119;
    Object list_constant_118, list_constant_104, list_constant_117;
    Object list_constant_116, list_constant_115, list_constant_100;
    Object list_constant_114, list_constant_113, list_constant_112;
    Object list_constant_111, list_constant_109, Qnumeric_return_value;
    Object list_constant_108, list_constant_107, list_constant_106;
    Object list_constant_105, list_constant_103, list_constant_102;
    Object list_constant_101, Qab_plus, Qhex_digit_char, list_constant_99;
    Object list_constant_98, Qdisambiguated_token, list_constant_97;
    Object list_constant_96, list_constant_95, Qcomment, list_constant_94;
    Object list_constant_93, list_constant_88, list_constant_79;
    Object list_constant_92, Qdo_nothing, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_82, list_constant_87;
    Object list_constant_86, list_constant_85, list_constant_84;
    Object list_constant_83, list_constant_81, list_constant_80;
    Object list_constant_76, list_constant_78, list_constant_77;
    Object Qalphabet_case_sensitive_symbol_from_text_string, list_constant_75;
    Object list_constant_74, list_constant_73, list_constant_72;
    Object list_constant_71, list_constant_70, list_constant_69;
    Object list_constant_68, list_constant_67, list_constant_66;
    Object list_constant_65, list_constant_64, list_constant_63;
    Object list_constant_62, list_constant_61, list_constant_6;
    Object list_constant_60, list_constant_59, list_constant_56;
    Object list_constant_58, list_constant_57, list_constant_55;
    Object list_constant_54, list_constant_53, list_constant_52;
    Object list_constant_51, list_constant_50, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_46;
    Object list_constant_45, list_constant_44, list_constant_43;
    Object list_constant_42, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_38, list_constant_37, Qbackslash;
    Object Qsingle_quote, Qdouble_quote, Qr, Qf, Qn, Qb, list_constant_36;
    Object string_constant_179, string_constant_178, string_constant_177;
    Object string_constant_176, string_constant_175, list_constant_35;
    Object list_constant_17, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object list_constant_5, string_constant_174, string_constant_173;
    Object string_constant_172, string_constant_171, string_constant_170;
    Object Qunreserved_java_identifier_qm, string_constant_169;
    Object string_constant_168, string_constant_167, string_constant_166;
    Object string_constant_165, string_constant_164, string_constant_163;
    Object string_constant_162, string_constant_161, string_constant_160;
    Object string_constant_159, string_constant_158, string_constant_157;
    Object string_constant_156, string_constant_155, string_constant_154;
    Object string_constant_153, string_constant_152, string_constant_151;
    Object string_constant_150, string_constant_149, string_constant_148;
    Object string_constant_147, string_constant_146, string_constant_145;
    Object string_constant_144, string_constant_143, string_constant_142;
    Object string_constant_141, string_constant_140, string_constant_139;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object string_constant_111, string_constant_110, string_constant_109;
    Object string_constant_108, string_constant_107, string_constant_106;
    Object string_constant_105, string_constant_104, string_constant_103;
    Object string_constant_102, string_constant_101, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_59, string_constant_92;
    Object string_constant_91, string_constant_90, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object string_constant_85, string_constant_84, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object Qsimplify_associative_operation, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5;

    x_note_fn_call(250,49);
    SET_PACKAGE("AB");
    if (Java_grammar_stream_qm == UNBOUND)
	Java_grammar_stream_qm = Nil;
    string_constant = STATIC_STRING("~");
    string_constant_1 = STATIC_STRING("~~");
    string_constant_5 = 
	    STATIC_STRING("1q1m83-1=y83-0ry1m83-1=y83-0hy1m83-1=y83-0Fy1m83-1=y83-bHy1m83-1=y83-1Fy1m83-1=y83-16y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_5));
    string_constant_6 = STATIC_STRING("1m1m8379y83DIy1m8379y83jwy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_6));
    string_constant_7 = STATIC_STRING("1m1m83DIy83-17y1m83DIy1m9k83*+Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_7));
    string_constant_8 = STATIC_STRING("1m1m83-17y83-0sy1m83-17y83-0iy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_8));
    string_constant_9 = 
	    STATIC_STRING("1p1m83-0sy1m9k83*+Cy1m83-0sy1m9k83*+by1m83-0sy1m9k83*+Ry1m83-0sy1m9k83*+Ty1m83-0sy1m9k83*+Fy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_9));
    string_constant_10 = 
	    STATIC_STRING("1m1m83-0iy1m9k83*+Ny1m83-0iy1m9k83*+Jy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_10));
    string_constant_11 = STATIC_STRING("1m1m83jwy83DEy1m83jwy83-0Cy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_11));
    string_constant_12 = STATIC_STRING("1l1m83DEy831ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_12));
    string_constant_13 = STATIC_STRING("1l1m83DFy83DEy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_13));
    string_constant_14 = STATIC_STRING("1l1m83jly83DEy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_14));
    string_constant_15 = 
	    STATIC_STRING("1n1m83-0Cy1n83DIy1m9k832sy1m9k832ty1m83-0Cy1n831ey1m9k832sy1m9k832ty1m83-0Cy1n83-0Cy1m9k832sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_15));
    string_constant_16 = STATIC_STRING("1m1n831ey83jxyl1n831ey83-19yl");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_16));
    string_constant_17 = STATIC_STRING("1l1n83jxy831Myl");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_17));
    AB_package = STATIC_PACKAGE("AB");
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_18 = 
	    STATIC_STRING("1l1o83-19y1n831ey1m9k836Wy831My1n83-kjyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_18));
    string_constant_19 = 
	    STATIC_STRING("1r1n83-0Ny83-1Qyl1n83-0Ny83-0pyl1n83-0Ny1m83-0py83-1Qy1n83BKylm1n83-0Ny83-18yl1n83-0Ny1m83-18y83-1Qy1n83BKylm1n83-0Ny1m83-18y83-");
    string_constant_20 = 
	    STATIC_STRING("0py1n83BKylm1n83-0Ny1n83-18y83-0py83-1Qy1o83BKylmn");
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_19,
	    string_constant_20)));
    string_constant_21 = 
	    STATIC_STRING("1m1n83-0py83-0oyl1o83-0py1m83-0py83-0oy1n83Cqylm9k");
    clear_optimized_constants();
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_21));
    string_constant_22 = 
	    STATIC_STRING("1m1n83-1Qy83-1Pyl1o83-1Qy1m83-1Qy83-1Py1n83-uZylm9k");
    clear_optimized_constants();
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_22));
    string_constant_23 = 
	    STATIC_STRING("1l1n83-18y1n1m9k83*+Wy831ey1m9k83-Zy1m839cym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_23));
    string_constant_24 = STATIC_STRING("1m1n83-0oy83-1Dyl1n83-0oy83-1Ryl");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_24));
    string_constant_25 = 
	    STATIC_STRING("1l1n83-1Dy1n1m9k83-I-y831ey1m9k83-Zy1m83-q-ym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_25));
    string_constant_26 = 
	    STATIC_STRING("1l1n83-1Ry1p1m9k83-I-y831ey1m9k836Wy1m9k9l1m9k83-Zy1m83-ubym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qstar);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_26));
    string_constant_27 = 
	    STATIC_STRING("1n1n83-1Py83DDyl1n83-1Py83T2yl1m83-1Py1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    string_constant_28 = STATIC_STRING("1m1m835Yy83-14y1m835Yy1m835Yy83-14y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    string_constant_29 = 
	    STATIC_STRING("1u1m83-14y1m9k83*+Zy1m83-14y1m9k83*+Yy1m83-14y1m9k83*+Xy1m83-14y1m9k83-IAy1m83-14y1m9k83*+9y1m83-14y1m9k83*+Ly1m83-14y1m9k83*+Uy");
    string_constant_30 = 
	    STATIC_STRING("1m83-14y1m9k83-ICy1m83-14y1m9k83*+fy1m83-14y1m9k83*+iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_29,
	    string_constant_30)));
    string_constant_31 = 
	    STATIC_STRING("1s1n83DDy1n1m9k83-Hfy831My83jXy1m83-Gym1n83DDy1o1m9k83-Hfy831My83-0xy83jXy1m83-Gym1n83DDy1o1m9k83-Hfy831My83-1Gy83jXy1m83-Gym1n8");
    string_constant_32 = 
	    STATIC_STRING("3DDy1p1m9k83-Hfy831My83-1Gy83-0xy83jXy1m83-Gym1n83DDy1o835Yy1m9k83-Hfy831My83jXy1m83-Gyn1n83DDy1p835Yy1m9k83-Hfy831My83-0xy83jXy");
    string_constant_33 = 
	    STATIC_STRING("1m83-Gyn1n83DDy1p835Yy1m9k83-Hfy831My83-1Gy83jXy1m83-Gyn1n83DDy1q835Yy1m9k83-Hfy831My83-1Gy83-0xy83jXy1m83-Gyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_31,
	    string_constant_32,string_constant_33)));
    string_constant_34 = STATIC_STRING("1l1m83-1Gy1m1m9k83-Hoy83DFy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_34));
    string_constant_35 = STATIC_STRING("1l1m83-0xy1m1m9k83*+Py83-0wy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_35));
    string_constant_36 = 
	    STATIC_STRING("1m1m83-0wy83jly1m83-0wy1n83-0wy1m9k83vy83jly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_36));
    string_constant_37 = 
	    STATIC_STRING("1m1m83jXy1m1m9k83AZy1m9k83Aay1m83jXy1n1m9k83AZy83jYy1m9k83Aay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_37));
    string_constant_38 = STATIC_STRING("1m1m83jYy83-0Ky1m83jYy1m83jYy83-0Ky");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_38));
    string_constant_39 = 
	    STATIC_STRING("1o1m83-0Ky83-0Ly1m83-0Ky83-1Ey1m83-0Ky83-0Uy1m83-0Ky834Iy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_39));
    string_constant_40 = 
	    STATIC_STRING("1o1m83-0Ly83jgy1m83-0Ly83-12y1m83-0Ly83DDy1m83-0Ly83T2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_40));
    string_constant_41 = 
	    STATIC_STRING("1m1m83jgy1n8379y83k3y1m9k83-Zy1m83jgy1o835Yy8379y83k3y1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_41));
    string_constant_42 = 
	    STATIC_STRING("1m1m83k3y83-1Sy1m83k3y1n83k3y1m9k83vy83-1Sy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_42));
    string_constant_43 = 
	    STATIC_STRING("1m1m83-1Sy83k2y1m83-1Sy1n83k2y1m9k9l83k4y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_43));
    string_constant_44 = 
	    STATIC_STRING("1m1m83k2y831My1m83k2y1n83k2y1m9k832sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_44));
    string_constant_45 = STATIC_STRING("1m1m83k4y83=Sy1m83k4y83jTy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_45));
    string_constant_46 = STATIC_STRING("1l1m83-12y1m83joy83-11y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_46));
    string_constant_47 = 
	    STATIC_STRING("1s1m83joy1m8379y83-13y1m83joy1n8379y83-13y83k0y1m83joy1n835Yy8379y83-13y1m83joy1o835Yy8379y83-13y83k0y1m83joy1m1m9k83-IKy83-13y1");
    string_constant_48 = 
	    STATIC_STRING("m83joy1n1m9k83-IKy83-13y83k0y1m83joy1n835Yy1m9k83-IKy83-13y1m83joy1o835Yy1m9k83-IKy83-13y83k0y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_47,
	    string_constant_48)));
    string_constant_49 = 
	    STATIC_STRING("1n1m83-13y1n831My1m9k83-9y1m9k83-Ay1m83-13y1o831My1m9k83-9y83jky1m9k83-Ay1m83-13y1n83-13y1m9k832sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_49));
    string_constant_50 = 
	    STATIC_STRING("1m1m83jky83jjy1m83jky1n83jky1m9k83vy83jjy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_50));
    string_constant_51 = 
	    STATIC_STRING("1m1m83jjy1m8379y83k2y1m83jjy1n835Yy8379y83k2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_51));
    string_constant_52 = STATIC_STRING("1l1m83k0y1m1m9k83*+ey83-0My");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_52));
    string_constant_53 = 
	    STATIC_STRING("1m1m83-0My83DFy1m83-0My1n83-0My1m9k83vy83DFy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_53));
    string_constant_54 = STATIC_STRING("1m1m83-11y834Iy1m83-11y1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_54));
    string_constant_55 = STATIC_STRING("1l1m83-1Ey1m1m9k83-IAy834Iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_55));
    string_constant_56 = 
	    STATIC_STRING("1o1m83-0Uy1m83-0Vy83-0Ty1m83-0Uy1n83-0Vy83k0y83-0Ty1m83-0Uy1n835Yy83-0Vy83-0Ty1m83-0Uy1o835Yy83-0Vy83k0y83-0Ty");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_56));
    string_constant_57 = 
	    STATIC_STRING("1m1m83-0Vy1n83jxy1m9k83-9y1m9k83-Ay1m83-0Vy1o83jxy1m9k83-9y83jky1m9k83-Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_57));
    string_constant_58 = 
	    STATIC_STRING("1o1m83-0Ty1m1m9k83AZy1m9k83Aay1m83-0Ty1n1m9k83AZy83T0y1m9k83Aay1m83-0Ty1n1m9k83AZy83-0dy1m9k83Aay1m83-0Ty1o1m9k83AZy83-0dy83T0y1");
    string_constant_59 = STATIC_STRING("m9k83Aay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_58,
	    string_constant_59)));
    string_constant_60 = 
	    STATIC_STRING("1q1m83-0dy1n1m9k83-IDy1m9k83-9y1m9k83-Ay1m83-0dy1o1m9k83-IDy1m9k83-9y83T=y1m9k83-Ay1m83-0dy1n1m9k83ony1m9k83-9y1m9k83-Ay1m83-0dy");
    string_constant_61 = 
	    STATIC_STRING("1o1m9k83ony1m9k83-9y83T=y1m9k83-Ay1m83-0dy1p83jvy1m9k836Wy1m9k83ony1m9k83-9y1m9k83-Ay1m83-0dy1q83jvy1m9k836Wy1m9k83ony1m9k83-9y8");
    string_constant_62 = STATIC_STRING("3T=y1m9k83-Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_60,
	    string_constant_61,string_constant_62)));
    string_constant_63 = 
	    STATIC_STRING("1o1n83T2y1n1m9k83*+Sy831My83-0ty1m83D0ym1n83T2y1o1m9k83*+Sy831My83-0fy83-0ty1m83D0ym1n83T2y1o835Yy1m9k83*+Sy831My83-0ty1m83D0yn1");
    string_constant_64 = 
	    STATIC_STRING("n83T2y1p835Yy1m9k83*+Sy831My83-0fy83-0ty1m83D0yn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_63,
	    string_constant_64)));
    string_constant_65 = 
	    STATIC_STRING("1m1m83-0fy1m1m9k83-Hoy83jly1m83-0fy1n83-0fy1m9k83vy83jly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_65));
    string_constant_66 = 
	    STATIC_STRING("1m1m83-0ty1m1m9k83AZy1m9k83Aay1m83-0ty1n1m9k83AZy83-0vy1m9k83Aay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_66));
    string_constant_67 = 
	    STATIC_STRING("1m1m83-0vy83-0uy1m83-0vy1m83-0vy83-0uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_67));
    string_constant_68 = 
	    STATIC_STRING("1o1m83-0uy83-0Ry1m83-0uy83-08y1m83-0uy83DDy1m83-0uy83T2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_68));
    string_constant_69 = STATIC_STRING("1l1m83-0Ry83jgy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_69));
    string_constant_70 = STATIC_STRING("1l1m83-08y1m83joy1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    string_constant_71 = 
	    STATIC_STRING("1o1m83jTy1m1m9k83AZy1m9k83Aay1m83jTy1n1m9k83AZy1m9k83vy1m9k83Aay1m83jTy1n1m9k83AZy83-1Ty1m9k83Aay1m83jTy1o1m9k83AZy83-1Ty1m9k83v");
    string_constant_72 = STATIC_STRING("y1m9k83Aay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_71,
	    string_constant_72)));
    string_constant_73 = 
	    STATIC_STRING("1m1m83-1Ty83k4y1m83-1Ty1n83-1Ty1m9k83vy83k4y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_73));
    string_constant_74 = 
	    STATIC_STRING("1m1m834Iy1m1m9k83AZy1m9k83Aay1m834Iy1n1m9k83AZy83T0y1m9k83Aay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_74));
    string_constant_75 = STATIC_STRING("1m1m83T0y83-0Ey1m83T0y1m83T0y83-0Ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_75));
    string_constant_76 = 
	    STATIC_STRING("1n1m83-0Ey83-10y1m83-0Ey835Zy1m83-0Ey83DDy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_76));
    string_constant_77 = STATIC_STRING("1l1m83-10y1m83jmy1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_77));
    string_constant_78 = 
	    STATIC_STRING("1m1m83jmy1m8379y83k3y1m83jmy1n835Yy8379y83k3y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_78));
    string_constant_79 = 
	    STATIC_STRING("1q1m835Zy83k*y1m835Zy83-1+y1m835Zy83-0ny1m835Zy83-0ly1m835Zy83-1Uy1m835Zy83-0jy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_79));
    string_constant_80 = 
	    STATIC_STRING("1p1m839Ay83k*y1m839Ay83-1-y1m839Ay83-0my1m839Ay83-1Vy1m839Ay83-0ky");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_80));
    string_constant_81 = 
	    STATIC_STRING("1v1m83k*y834Iy1m83k*y83-0ay1m83k*y83-0ey1m83k*y83-1Ly1m83k*y83-0Zy1m83k*y83-0Gy1m83k*y83-0Wy1m83k*y83-1By1m83k*y83-1My1m83k*y83-");
    string_constant_82 = STATIC_STRING("1Ny1m83k*y83-1Oy");
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_81,
	    string_constant_82)));
    string_constant_83 = STATIC_STRING("1l1m83-0ay1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_83));
    string_constant_84 = STATIC_STRING("1l1m83-1+y1n831My1m9k83-Py835Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_84));
    string_constant_85 = STATIC_STRING("1l1m83-1-y1n831My1m9k83-Py839Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    string_constant_86 = STATIC_STRING("1l1m83-0ey1m83k+y1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_86));
    string_constant_87 = 
	    STATIC_STRING("1r1m83k+y83jUy1m83k+y83jty1m83k+y83jsy1m83k+y83jry1m83k+y83jqy1m83k+y83jpy1m83k+y83jZy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_87));
    string_constant_88 = 
	    STATIC_STRING("1l1m83-0ny1p1m9k83omy1m9k83-9y83=Sy1m9k83-Ay835Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_88));
    string_constant_89 = 
	    STATIC_STRING("1l1m83-0ly1r1m9k83omy1m9k83-9y83=Sy1m9k83-Ay839Ay1m9k83-Hmy835Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_89));
    string_constant_90 = 
	    STATIC_STRING("1l1m83-0my1r1m9k83omy1m9k83-9y83=Sy1m9k83-Ay839Ay1m9k83-Hmy839Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_90));
    string_constant_91 = 
	    STATIC_STRING("1l1m83-1Ly1p1m9k83*+cy1m9k83-9y83=Sy1m9k83-Ay83-1Hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_91));
    string_constant_92 = 
	    STATIC_STRING("1o1m83-1Hy1m1m9k83AZy1m9k83Aay1m83-1Hy1n1m9k83AZy83k=y1m9k83Aay1m83-1Hy1n1m9k83AZy83-1Jy1m9k83Aay1m83-1Hy1o1m9k83AZy83-1Jy83k=y1");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_92,
	    string_constant_59)));
    string_constant_93 = 
	    STATIC_STRING("1m1m83-1Jy83-1Iy1m83-1Jy1m83-1Jy83-1Iy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_93));
    string_constant_94 = STATIC_STRING("1l1m83-1Iy1m83k=y83T0y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_94));
    string_constant_95 = STATIC_STRING("1m1m83k=y83-1Ky1m83k=y1m83k=y83-1Ky");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_95));
    string_constant_96 = 
	    STATIC_STRING("1m1m83-1Ky1n1m9k83*+Dy83-0Sy1m9k83-Py1m83-1Ky1m1m9k83*+Hy1m9k83-Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_96));
    string_constant_97 = 
	    STATIC_STRING("1l1m83-1Uy1p1m9k83ooy1m9k83-9y83=Sy1m9k83-Ay835Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_97));
    string_constant_98 = 
	    STATIC_STRING("1l1m83-1Vy1p1m9k83ooy1m9k83-9y83=Sy1m9k83-Ay839Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_98));
    string_constant_99 = 
	    STATIC_STRING("1l1m83-0Zy1r1m9k83*+Iy835Zy1m9k83ooy1m9k83-9y83=Sy1m9k83-Ay1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_99));
    string_constant_100 = 
	    STATIC_STRING("1s1m83-0jy1q1m9k83-Hqy1m9k83-9y1m9k83-Zy1m9k83-Zy1m9k83-Ay835Zy1m83-0jy1r1m9k83-Hqy1m9k83-9y1m9k83-Zy1m9k83-Zy83jiy1m9k83-Ay835Z");
    string_constant_101 = 
	    STATIC_STRING("y1m83-0jy1r1m9k83-Hqy1m9k83-9y1m9k83-Zy83=Sy1m9k83-Zy1m9k83-Ay835Zy1m83-0jy1s1m9k83-Hqy1m9k83-9y1m9k83-Zy83=Sy1m9k83-Zy83jiy1m9k");
    string_constant_102 = 
	    STATIC_STRING("83-Ay835Zy1m83-0jy1r1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy1m9k83-Zy1m9k83-Ay835Zy1m83-0jy1s1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy1m9k83-Zy");
    string_constant_103 = 
	    STATIC_STRING("83jiy1m9k83-Ay835Zy1m83-0jy1s1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy83=Sy1m9k83-Zy1m9k83-Ay835Zy1m83-0jy1t1m9k83-Hqy1m9k83-9y83jhy1m9k");
    string_constant_104 = 
	    STATIC_STRING("83-Zy83=Sy1m9k83-Zy83jiy1m9k83-Ay835Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_100,
	    string_constant_101,string_constant_102,string_constant_103,
	    string_constant_104)));
    string_constant_105 = 
	    STATIC_STRING("1s1m83-0ky1q1m9k83-Hqy1m9k83-9y1m9k83-Zy1m9k83-Zy1m9k83-Ay839Ay1m83-0ky1r1m9k83-Hqy1m9k83-9y1m9k83-Zy1m9k83-Zy83jiy1m9k83-Ay839A");
    string_constant_106 = 
	    STATIC_STRING("y1m83-0ky1r1m9k83-Hqy1m9k83-9y1m9k83-Zy83=Sy1m9k83-Zy1m9k83-Ay839Ay1m83-0ky1s1m9k83-Hqy1m9k83-9y1m9k83-Zy83=Sy1m9k83-Zy83jiy1m9k");
    string_constant_107 = 
	    STATIC_STRING("83-Ay839Ay1m83-0ky1r1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy1m9k83-Zy1m9k83-Ay839Ay1m83-0ky1s1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy1m9k83-Zy");
    string_constant_108 = 
	    STATIC_STRING("83jiy1m9k83-Ay839Ay1m83-0ky1s1m9k83-Hqy1m9k83-9y83jhy1m9k83-Zy83=Sy1m9k83-Zy1m9k83-Ay839Ay1m83-0ky1t1m9k83-Hqy1m9k83-9y83jhy1m9k");
    string_constant_109 = 
	    STATIC_STRING("83-Zy83=Sy1m9k83-Zy83jiy1m9k83-Ay839Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_105,
	    string_constant_106,string_constant_107,string_constant_108,
	    string_constant_109)));
    string_constant_110 = STATIC_STRING("1m1m83jhy83k-y1m83jhy83jmy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_110));
    string_constant_111 = STATIC_STRING("1l1m83jiy83k-y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_111));
    string_constant_112 = 
	    STATIC_STRING("1m1m83k-y83k+y1m83k-y1n83k-y1m9k83vy83k+y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_112));
    string_constant_113 = 
	    STATIC_STRING("1m1m83-0Gy1m1m9k83*+By1m9k83-Zy1m83-0Gy1n1m9k83*+By831My1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_113));
    string_constant_114 = 
	    STATIC_STRING("1m1m83-0Wy1m1m9k83*+Gy1m9k83-Zy1m83-0Wy1n1m9k83*+Gy831My1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_114));
    string_constant_115 = 
	    STATIC_STRING("1m1m83-1By1m1m9k83*+ay1m9k83-Zy1m83-1By1n1m9k83*+ay83=Sy1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_115));
    string_constant_116 = 
	    STATIC_STRING("1l1m83-1Ny1n1m9k83*+dy83=Sy1m9k83-Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_116));
    string_constant_117 = 
	    STATIC_STRING("1l1m83-1My1p1m9k83-ICy1m9k83-9y83=Sy1m9k83-Ay834Iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_117));
    string_constant_118 = 
	    STATIC_STRING("1n1m83-1Oy1n1m9k83*+hy834Iy83-0Jy1m83-1Oy1n1m9k83*+hy834Iy83-0gy1m83-1Oy1o1m9k83*+hy834Iy83-0Jy83-0gy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_118));
    string_constant_119 = 
	    STATIC_STRING("1m1m83-0Jy83-0Iy1m83-0Jy1m83-0Jy83-0Iy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_119));
    string_constant_120 = 
	    STATIC_STRING("1l1m83-0Iy1p1m9k83*+Ey1m9k83-9y83jjy1m9k83-Ay834Iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_120));
    string_constant_121 = STATIC_STRING("1l1m83-0gy1m1m9k83*+My834Iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_121));
    string_constant_122 = STATIC_STRING("1m1m83DHy83juy1m83DHy83-0By");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_122));
    string_constant_123 = 
	    STATIC_STRING("1u1m83juy83-1=y1m83juy1m9k83-IDy1m83juy1n1m9k83-9y83=Sy1m9k83-Ay1m83juy83jZy1m83juy83jfy1m83juy83jpy1m83juy83jSy1m83juy1n83DFy1m");
    string_constant_124 = 
	    STATIC_STRING("9k836Wy1m9k83-IDy1m83juy1n8379y1m9k836Wy1m9k83-Hfy1m83juy1n1m9k83-IKy1m9k836Wy1m9k83-Hfy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_123,
	    string_constant_124)));
    string_constant_125 = 
	    STATIC_STRING("1s1m83jZy1o1m9k83-I*y83DFy1m9k83-9y1m9k83-Ay1m83jZy1p1m9k83-I*y83DFy1m9k83-9y1m9k83-Ay83jXy1m83jZy1p1m9k83-I*y83DFy1m9k83-9y83T=");
    string_constant_126 = 
	    STATIC_STRING("y1m9k83-Ay1m83jZy1q1m9k83-I*y83DFy1m9k83-9y83T=y1m9k83-Ay83jXy1m83jZy1q83jvy1m9k836Wy1m9k83-I*y831My1m9k83-9y1m9k83-Ay1m83jZy1r8");
    string_constant_127 = 
	    STATIC_STRING("3jvy1m9k836Wy1m9k83-I*y831My1m9k83-9y1m9k83-Ay83jXy1m83jZy1r83jvy1m9k836Wy1m9k83-I*y831My1m9k83-9y83T=y1m9k83-Ay1m83jZy1s83jvy1m");
    string_constant_128 = 
	    STATIC_STRING("9k836Wy1m9k83-I*y831My1m9k83-9y83T=y1m9k83-Ay83jXy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_125,
	    string_constant_126,string_constant_127,string_constant_128)));
    string_constant_129 = STATIC_STRING("1m1m83jvy83DHy1m83jvy831ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_129));
    string_constant_130 = 
	    STATIC_STRING("1m1m83T=y83=Sy1m83T=y1n83T=y1m9k83vy83=Sy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_130));
    string_constant_131 = 
	    STATIC_STRING("1p1m83-0By1n1m9k83-I*y83DIy83-0Yy1m83-0By1o1m9k83-I*y83DIy83-0Yy83jdy1m83-0By1n1m9k83-I*y83DEy83-0Yy1m83-0By1o1m9k83-I*y83DEy83-");
    string_constant_132 = 
	    STATIC_STRING("0Yy83jdy1m83-0By1o1m9k83-I*y8379y83jdy83jTy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_131,
	    string_constant_132)));
    string_constant_133 = 
	    STATIC_STRING("1m1m83-0Yy83-0Xy1m83-0Yy1m83-0Yy83-0Xy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_133));
    string_constant_134 = STATIC_STRING("1l1m83-0Xy1n1m9k832sy83=Sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_134));
    string_constant_135 = 
	    STATIC_STRING("1m1m83jdy1m1m9k832sy1m9k832ty1m83jdy1n83jdy1m9k832sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_135));
    string_constant_136 = 
	    STATIC_STRING("1m1m83jfy1n83DHy1m9k836Wy831My1m83jfy1n1m9k83ony1m9k836Wy831My");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_136));
    string_constant_137 = 
	    STATIC_STRING("1q1m83jpy1n831ey1m9k83-9y1m9k83-Ay1m83jpy1o831ey1m9k83-9y83T=y1m9k83-Ay1m83jpy1p83DHy1m9k836Wy831My1m9k83-9y1m9k83-Ay1m83jpy1q83");
    string_constant_138 = 
	    STATIC_STRING("DHy1m9k836Wy831My1m9k83-9y83T=y1m9k83-Ay1m83jpy1p1m9k83ony1m9k836Wy831My1m9k83-9y1m9k83-Ay1m83jpy1q1m9k83ony1m9k836Wy831My1m9k83");
    string_constant_139 = STATIC_STRING("-9y83T=y1m9k83-Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_137,
	    string_constant_138,string_constant_139)));
    string_constant_140 = 
	    STATIC_STRING("1m1m83jSy1o831ey1m9k832sy83=Sy1m9k832ty1m83jSy1o83juy1m9k832sy83=Sy1m9k832ty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_140));
    string_constant_141 = 
	    STATIC_STRING("1o1m83T3y83DHy1m83T3y831ey1m83T3y83jry1m83T3y83jqy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_141));
    string_constant_142 = STATIC_STRING("1l1m83jry1m83T3y1m9k83oqy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_142));
    string_constant_143 = STATIC_STRING("1l1m83jqy1m83T3y1m9k83ory");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_143));
    string_constant_144 = 
	    STATIC_STRING("1p1m839By83jty1m839By83jsy1m839By1m1m9k9l839By1m839By1m1m9k9m839By1m839By83k1y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qminus);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_144));
    string_constant_145 = STATIC_STRING("1l1m83jty1m1m9k83oqy839By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_145));
    string_constant_146 = STATIC_STRING("1l1m83jsy1m1m9k83ory839By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_146));
    string_constant_147 = 
	    STATIC_STRING("1o1m83k1y83T3y1m83k1y1m1m9k83*+my839By1m83k1y1m1m9k83-IMy839By1m83k1y83-0Hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_147));
    string_constant_148 = 
	    STATIC_STRING("1o1m83-0Hy1o1m9k83-9y83DIy1m9k83-Ay839By1m83-0Hy1p1m9k83-9y83DIy83jdy1m9k83-Ay839By1m83-0Hy1o1m9k83-9y83=Sy1m9k83-Ay83k1y1m83-0H");
    string_constant_149 = 
	    STATIC_STRING("y1p1m9k83-9y831ey83jdy1m9k83-Ay83k1y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_148,
	    string_constant_149)));
    string_constant_150 = 
	    STATIC_STRING("1o1m83-15y839By1m83-15y1n83-15y1m9k9l839By1m83-15y1n83-15y1m9k9m839By1m83-15y1n83-15y1m9k83-IOy839By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qstar);
    push_optimized_constant(Qslash);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_150));
    string_constant_151 = 
	    STATIC_STRING("1n1m83-09y83-15y1m83-09y1n83-09y1m9k9l83-15y1m83-09y1n83-09y1m9k9m83-15y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qminus);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_151));
    string_constant_152 = 
	    STATIC_STRING("1o1m83-1Cy83-09y1m83-1Cy1n83-1Cy1m9k83-Iay83-09y1m83-1Cy1n83-1Cy1m9k83-Imy83-09y1m83-1Cy1n83-1Cy1m9k83-Ioy83-09y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_152));
    string_constant_153 = 
	    STATIC_STRING("1q1m83-1Ay83-1Cy1m83-1Ay1n83-1Ay1m9k9l83-1Cy1m83-1Ay1n83-1Ay1m9k9m83-1Cy1m83-1Ay1n83-1Ay1m9k9n83-1Cy1m83-1Ay1n83-1Ay1m9k9o83-1Cy");
    string_constant_154 = STATIC_STRING("1m83-1Ay1n83-1Ay1m9k83*+Qy83jwy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_lt);
    push_optimized_constant(Qnum_gt);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qnum_ge);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_153,
	    string_constant_154)));
    string_constant_155 = 
	    STATIC_STRING("1n1m83-0by83-1Ay1m83-0by1n83-0by1m9k83-Ily83-1Ay1m83-0by1n83-0by1m9k83-INy83-1Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_155));
    string_constant_156 = 
	    STATIC_STRING("1m1m83-0Ay83-0by1m83-0Ay1n83-0Ay1m9k83-IQy83-0by");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_156));
    string_constant_157 = 
	    STATIC_STRING("1m1m83-0cy83-0Ay1m83-0cy1n83-0cy1m9k83evy83-0Ay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_157));
    string_constant_158 = 
	    STATIC_STRING("1m1m83-0qy83-0cy1m83-0qy1n83-0qy1m9k83*+jy83-0cy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_158));
    string_constant_159 = 
	    STATIC_STRING("1m1m83-0Oy83-0qy1m83-0Oy1n83-0Oy1m9k83-IRy83-0qy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_159));
    string_constant_160 = 
	    STATIC_STRING("1m1m83-0Qy83-0Oy1m83-0Qy1n83-0Qy1m9k83*+ly83-0Oy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_160));
    string_constant_161 = 
	    STATIC_STRING("1m1m83-0Py83-0Qy1m83-0Py1p83-0Qy1m9k83-Iqy83=Sy1m9k83-Py83-0Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_161));
    string_constant_162 = STATIC_STRING("1m1m83jVy83-0Py1m83jVy83jUy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_162));
    string_constant_163 = STATIC_STRING("1l1m83jUy1n83-1*y83-0Dy83jVy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    string_constant_164 = 
	    STATIC_STRING("1n1m83-1*y831ey1m83-1*y83jfy1m83-1*y83jSy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_164));
    string_constant_165 = 
	    STATIC_STRING("1w1m83-0Dy1m9k9l1m83-0Dy1m9k83-ITy1m83-0Dy1m9k9m1m83-0Dy1m9k83-IPy1m83-0Dy1m9k83-IVy1m83-0Dy1m9k83-IWy1m83-0Dy1m9k83-Iby1m83-0Dy");
    string_constant_166 = 
	    STATIC_STRING("1m9k83-Iny1m83-0Dy1m9k83-Ipy1m83-0Dy1m9k83-ISy1m83-0Dy1m9k83*+8y1m83-0Dy1m9k83*+ky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qnum_ne);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_165,
	    string_constant_166)));
    string_constant_167 = STATIC_STRING("1l1m83=Sy83jVy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_167));
    string_constant_168 = STATIC_STRING("1l1m83-0Sy83=Sy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_168));
    Qunreserved_java_identifier_qm = 
	    STATIC_SYMBOL("UNRESERVED-JAVA-IDENTIFIER\?",AB_package);
    string_constant_169 = STATIC_STRING("1l1o831My83T6yl1m9kl");
    clear_optimized_constants();
    push_optimized_constant(Qunreserved_java_identifier_qm);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_169));
    Qjava_reserved_word_p = STATIC_SYMBOL("JAVA-RESERVED-WORD-P",AB_package);
    Java_reserved_word_p_prop = Qjava_reserved_word_p;
    Qreserved_java_word = STATIC_SYMBOL("RESERVED-JAVA-WORD",AB_package);
    Qidentifier = STATIC_SYMBOL("IDENTIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qunreserved_java_identifier_qm,
	    STATIC_FUNCTION(unreserved_java_identifier_qm,NIL,FALSE,2,2));
    set_grammar_transform_can_return_bad_phrase_p(Qunreserved_java_identifier_qm);
    string_constant_170 = STATIC_STRING("1l1n83-0ry83Sy1m83Syl");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_170));
    string_constant_171 = STATIC_STRING("1l1n83-0hy9k1m9kl");
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_171));
    string_constant_172 = 
	    STATIC_STRING("1m1n83-0Fy1m9k83*+gy1m832Uy83=Oy1n83-0Fy1m9k83*+Ky1m832Uy832Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_172));
    string_constant_173 = STATIC_STRING("1l1n83-1Fy83-Uy1m9kl");
    clear_optimized_constants();
    push_optimized_constant(Qstring);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_173));
    string_constant_174 = STATIC_STRING("1l1n83-16y1m9k83*+Vy1l83-bVy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_174));
    Must_quote_g2_symbol_character_class = 
	    make_character_range_from_sorted_list_of_character_codes(Alphabet_nonsymbol_character_codes_sorted_by_encoding);
    list_constant_5 = STATIC_CONS(FIX((SI_Long)36L),FIX((SI_Long)36L));
    list_constant_6 = STATIC_CONS(FIX((SI_Long)48L),FIX((SI_Long)57L));
    list_constant_7 = STATIC_CONS(FIX((SI_Long)65L),FIX((SI_Long)90L));
    list_constant_8 = STATIC_CONS(FIX((SI_Long)95L),FIX((SI_Long)95L));
    list_constant_9 = STATIC_CONS(FIX((SI_Long)97L),FIX((SI_Long)122L));
    list_constant_10 = STATIC_CONS(FIX((SI_Long)192L),FIX((SI_Long)214L));
    list_constant_11 = STATIC_CONS(FIX((SI_Long)216L),FIX((SI_Long)246L));
    list_constant_12 = STATIC_CONS(FIX((SI_Long)248L),FIX((SI_Long)255L));
    list_constant_13 = STATIC_CONS(FIX((SI_Long)256L),FIX((SI_Long)8191L));
    list_constant_14 = STATIC_CONS(FIX((SI_Long)12352L),FIX((SI_Long)40959L));
    list_constant_15 = STATIC_CONS(FIX((SI_Long)63744L),FIX((SI_Long)65023L));
    list_constant_16 = STATIC_CONS(FIX((SI_Long)65136L),FIX((SI_Long)65278L));
    list_constant_17 = STATIC_CONS(FIX((SI_Long)65296L),FIX((SI_Long)65305L));
    list_constant_18 = STATIC_CONS(FIX((SI_Long)65313L),FIX((SI_Long)65338L));
    list_constant_19 = STATIC_CONS(FIX((SI_Long)65345L),FIX((SI_Long)65370L));
    list_constant_20 = STATIC_CONS(FIX((SI_Long)65382L),FIX((SI_Long)65500L));
    list_constant_21 = STATIC_LIST((SI_Long)16L,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_8,
	    list_constant_9,list_constant_10,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20);
    list0 = list_constant_21;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	entry = CAR(list0);
	thing = CAR(entry);
	temp = CHARACTERP(thing) ? CHAR_CODE(thing) : thing;
	thing = CDR(entry);
	temp_1 = CHARACTERP(thing) ? CHAR_CODE(thing) : thing;
	temp_1 = CONS(temp,temp_1);
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    Unicode_letter_or_digit_possibly_undefined_character_class = result_1;
    list_constant_22 = STATIC_CONS(FIX((SI_Long)1632L),FIX((SI_Long)1641L));
    list_constant_23 = STATIC_CONS(FIX((SI_Long)1776L),FIX((SI_Long)1785L));
    list_constant_24 = STATIC_CONS(FIX((SI_Long)2406L),FIX((SI_Long)2415L));
    list_constant_25 = STATIC_CONS(FIX((SI_Long)2534L),FIX((SI_Long)2543L));
    list_constant_26 = STATIC_CONS(FIX((SI_Long)2662L),FIX((SI_Long)2671L));
    list_constant_27 = STATIC_CONS(FIX((SI_Long)2790L),FIX((SI_Long)2799L));
    list_constant_28 = STATIC_CONS(FIX((SI_Long)2918L),FIX((SI_Long)2927L));
    list_constant_29 = STATIC_CONS(FIX((SI_Long)3047L),FIX((SI_Long)3055L));
    list_constant_30 = STATIC_CONS(FIX((SI_Long)3174L),FIX((SI_Long)3183L));
    list_constant_31 = STATIC_CONS(FIX((SI_Long)3302L),FIX((SI_Long)3311L));
    list_constant_32 = STATIC_CONS(FIX((SI_Long)3430L),FIX((SI_Long)3439L));
    list_constant_33 = STATIC_CONS(FIX((SI_Long)3664L),FIX((SI_Long)3673L));
    list_constant_34 = STATIC_CONS(FIX((SI_Long)3792L),FIX((SI_Long)3801L));
    list_constant_35 = STATIC_LIST((SI_Long)15L,list_constant_6,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25,list_constant_26,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30,
	    list_constant_31,list_constant_32,list_constant_33,
	    list_constant_34,list_constant_17);
    list0 = list_constant_35;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	entry = CAR(list0);
	thing = CAR(entry);
	temp = CHARACTERP(thing) ? CHAR_CODE(thing) : thing;
	thing = CDR(entry);
	temp_1 = CHARACTERP(thing) ? CHAR_CODE(thing) : thing;
	temp_1 = CONS(temp,temp_1);
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    Unicode_digit_possibly_undefined_character_class = result_1;
    Java_identifier_start_character_class = 
	    character_class_difference(Unicode_letter_or_digit_possibly_undefined_character_class,
	    Unicode_digit_possibly_undefined_character_class);
    Java_identifier_quote_free_start_character_class = 
	    character_class_difference(Java_identifier_start_character_class,
	    Must_quote_g2_symbol_character_class);
    Java_identifier_part_character_class = 
	    Unicode_letter_or_digit_possibly_undefined_character_class;
    Java_identifier_quote_free_part_character_class = 
	    character_class_difference(Java_identifier_part_character_class,
	    Must_quote_g2_symbol_character_class);
    list_constant = STATIC_LIST((SI_Long)3L,CHR(' '),CHR('\t'),CHR('\n'));
    Qseq = STATIC_SYMBOL("SEQ",AB_package);
    string_constant_175 = STATIC_STRING("( ) { } [ ] ; , .");
    Java_separators_as_conglomerated_string = string_constant_175;
    string_constant_176 = STATIC_STRING("= > < ! + - * / & | ^ %");
    Java_single_character_constituent_operators_as_string = 
	    string_constant_176;
    string_constant_177 = STATIC_STRING("~ \? :");
    Java_single_character_nonconstituent_operators_as_string = 
	    string_constant_177;
    string_constant_178 = STATIC_STRING("= > < ! ~ \? : + - * / & | ^ %");
    Java_single_character_operators_as_conglomerated_string = 
	    string_constant_178;
    string_constant_179 = 
	    STATIC_STRING("==  <=  >=  != && || ++ -- <<  >>  >>>\n   +=  -=  *=  /= &= |=  ^= %= <<= >>= >>>=");
    Java_multi_character_operators_as_conglomerated_string = 
	    string_constant_179;
    list_constant_36 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)13L),
	    FIX((SI_Long)10L),FIX((SI_Long)10L),FIX((SI_Long)8232L));
    Newline_chars_for_java_tokens = 
	    make_character_range_from_sorted_list_of_character_codes(sort(2,
	    remove_duplicates(3,list_constant_36,Ktest,
	    SYMBOL_FUNCTION(Qnum_eq)),SYMBOL_FUNCTION(Qnum_lt)));
    Qb = STATIC_SYMBOL("B",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)98L),Qb);
    list_constant_38 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)116L),Qt);
    Qn = STATIC_SYMBOL("N",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)110L),Qn);
    Qf = STATIC_SYMBOL("F",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)102L),Qf);
    Qr = STATIC_SYMBOL("R",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)114L),Qr);
    Qdouble_quote = STATIC_SYMBOL("DOUBLE-QUOTE",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)34L),
	    Qdouble_quote);
    Qsingle_quote = STATIC_SYMBOL("SINGLE-QUOTE",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)39L),
	    Qsingle_quote);
    Qbackslash = STATIC_SYMBOL("BACKSLASH",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)92L),Qbackslash);
    list_constant_45 = STATIC_LIST((SI_Long)8L,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44);
    Java_escape_character_literal_alist = list_constant_45;
    list_constant_46 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)48L),
	    FIX((SI_Long)0L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)49L),
	    FIX((SI_Long)1L));
    list_constant_48 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)50L),
	    FIX((SI_Long)2L));
    list_constant_49 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)51L),
	    FIX((SI_Long)3L));
    list_constant_50 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)52L),
	    FIX((SI_Long)4L));
    list_constant_51 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)53L),
	    FIX((SI_Long)5L));
    list_constant_52 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)54L),
	    FIX((SI_Long)6L));
    list_constant_53 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)55L),
	    FIX((SI_Long)7L));
    list_constant_54 = STATIC_LIST((SI_Long)8L,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49,
	    list_constant_50,list_constant_51,list_constant_52,
	    list_constant_53);
    Java_octal_character_literal_alist = list_constant_54;
    Qcharacter_literal = STATIC_SYMBOL("CHARACTER-LITERAL",AB_package);
    Qescape = STATIC_SYMBOL("ESCAPE",AB_package);
    Qbad_character_literal = STATIC_SYMBOL("BAD-CHARACTER-LITERAL",AB_package);
    Qoctal = STATIC_SYMBOL("OCTAL",AB_package);
    Qsimple = STATIC_SYMBOL("SIMPLE",AB_package);
    Qtokenize_java_character_literal = 
	    STATIC_SYMBOL("TOKENIZE-JAVA-CHARACTER-LITERAL",AB_package);
    SET_SYMBOL_FUNCTION(Qtokenize_java_character_literal,
	    STATIC_FUNCTION(tokenize_java_character_literal,NIL,FALSE,3,3));
    valid_token_actions_new_value = CONS(Qtokenize_java_character_literal,
	    Valid_token_actions);
    Valid_token_actions = valid_token_actions_new_value;
    Qtokenize_bad_java_character_literal = 
	    STATIC_SYMBOL("TOKENIZE-BAD-JAVA-CHARACTER-LITERAL",AB_package);
    SET_SYMBOL_FUNCTION(Qtokenize_bad_java_character_literal,
	    STATIC_FUNCTION(tokenize_bad_java_character_literal,NIL,FALSE,
	    3,3));
    valid_token_actions_new_value = 
	    CONS(Qtokenize_bad_java_character_literal,Valid_token_actions);
    Valid_token_actions = valid_token_actions_new_value;
    list_constant_55 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)48L),
	    FIX((SI_Long)49L),FIX((SI_Long)50L),FIX((SI_Long)51L));
    Java_half_octal_characters = list_constant_55;
    Qjava_letter = STATIC_SYMBOL("JAVA-LETTER",AB_package);
    Qcharacter_class = STATIC_SYMBOL("CHARACTER-CLASS",AB_package);
    Qjava_letter_quote_free = STATIC_SYMBOL("JAVA-LETTER-QUOTE-FREE",
	    AB_package);
    Qjava_letter_or_digit = STATIC_SYMBOL("JAVA-LETTER-OR-DIGIT",AB_package);
    Qjava_letter_or_digit_quote_free = 
	    STATIC_SYMBOL("JAVA-LETTER-OR-DIGIT-QUOTE-FREE",AB_package);
    Qjava_digit = STATIC_SYMBOL("JAVA-DIGIT",AB_package);
    Qescape_character_literal = STATIC_SYMBOL("ESCAPE-CHARACTER-LITERAL",
	    AB_package);
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    Qoctal_character_literal = STATIC_SYMBOL("OCTAL-CHARACTER-LITERAL",
	    AB_package);
    Qhalf_octal_character_literal = 
	    STATIC_SYMBOL("HALF-OCTAL-CHARACTER-LITERAL",AB_package);
    Qbad_escape_character_literal = 
	    STATIC_SYMBOL("BAD-ESCAPE-CHARACTER-LITERAL",AB_package);
    Qinverted_class = STATIC_SYMBOL("INVERTED-CLASS",AB_package);
    Qab_string_char = STATIC_SYMBOL("STRING-CHAR",AB_package);
    list_constant_56 = STATIC_CONS(FIX((SI_Long)92L),Qnil);
    list_constant_57 = STATIC_CONS(FIX((SI_Long)34L),list_constant_56);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_57);
    list_constant_161 = STATIC_LIST((SI_Long)2L,Qab_string_char,
	    list_constant_58);
    Qsimple_character_literal = STATIC_SYMBOL("SIMPLE-CHARACTER-LITERAL",
	    AB_package);
    list_constant_59 = STATIC_CONS(FIX((SI_Long)39L),list_constant_56);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_59);
    list_constant_162 = STATIC_LIST((SI_Long)2L,Qsimple_character_literal,
	    list_constant_60);
    Qbad_octal_character_literal = 
	    STATIC_SYMBOL("BAD-OCTAL-CHARACTER-LITERAL",AB_package);
    Qnewline_char = STATIC_SYMBOL("NEWLINE-CHAR",AB_package);
    Qchar_within_single_line_comment = 
	    STATIC_SYMBOL("CHAR-WITHIN-SINGLE-LINE-COMMENT",AB_package);
    Qhex_digit_char = STATIC_SYMBOL("HEX-DIGIT-CHAR",AB_package);
    list_constant_61 = STATIC_CONS(FIX((SI_Long)65L),FIX((SI_Long)70L));
    list_constant_62 = STATIC_CONS(FIX((SI_Long)97L),FIX((SI_Long)102L));
    list_constant_63 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_61,list_constant_62);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qcharacter_class,
	    list_constant_63);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qhex_digit_char,
	    list_constant_64);
    list_constant_163 = STATIC_CONS(list_constant_65,Qnil);
    Qjava_symbol = STATIC_SYMBOL("JAVA-SYMBOL",AB_package);
    Qab_plus = STATIC_SYMBOL("PLUS",AB_package);
    Qpattern = STATIC_SYMBOL("PATTERN",AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qjava_letter_quote_free);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qpattern,Qjava_letter);
    list_constant_68 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)64L),
	    list_constant_66);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_67,
	    list_constant_68);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_69);
    Qkleene = STATIC_SYMBOL("KLEENE",AB_package);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qjava_letter_or_digit_quote_free);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qpattern,Qjava_letter_or_digit);
    list_constant_72 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)64L),
	    list_constant_70);
    list_constant_73 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_71,
	    list_constant_72);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_73);
    list_constant_164 = STATIC_LIST((SI_Long)3L,Qseq,list_constant_74,
	    list_constant_75);
    Qalphabet_case_sensitive_symbol_from_text_string = 
	    STATIC_SYMBOL("ALPHABET-CASE-SENSITIVE-SYMBOL-FROM-TEXT-STRING",
	    AB_package);
    list_constant_165 = 
	    STATIC_CONS(Qalphabet_case_sensitive_symbol_from_text_string,Qnil);
    Qdo_nothing = STATIC_SYMBOL("DO-NOTHING",AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qpattern,Qnewline_char);
    list_constant_77 = STATIC_LIST((SI_Long)5L,Qeither,list_constant_76,
	    FIX((SI_Long)8233L),FIX((SI_Long)32L),FIX((SI_Long)9L));
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_77);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qchar_within_single_line_comment);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_78);
    list_constant_90 = STATIC_LIST((SI_Long)5L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)47L),list_constant_79,list_constant_76);
    list_constant_80 = STATIC_CONS(FIX((SI_Long)42L),Qnil);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_80);
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_81);
    Qmaybe = STATIC_SYMBOL("MAYBE",AB_package);
    list_constant_82 = STATIC_CONS(FIX((SI_Long)47L),Qnil);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_82);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)42L),
	    list_constant_83);
    list_constant_86 = STATIC_LIST((SI_Long)2L,Qmaybe,list_constant_84);
    list_constant_87 = STATIC_LIST((SI_Long)3L,Qseq,list_constant_85,
	    list_constant_86);
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_87);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)6L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)42L),list_constant_88,FIX((SI_Long)42L),
	    list_constant_82);
    list_constant_92 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_89,
	    list_constant_90,list_constant_91);
    list_constant_166 = STATIC_LIST((SI_Long)2L,Qdo_nothing,list_constant_92);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    list_constant_93 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)47L),list_constant_79);
    list_constant_94 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)47L),
	    FIX((SI_Long)42L),list_constant_88);
    list_constant_95 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_93,
	    list_constant_94);
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    list_constant_167 = STATIC_LIST((SI_Long)3L,Qcomment,list_constant_95,
	    Qno_value);
    Qdisambiguated_token = STATIC_SYMBOL("DISAMBIGUATED-TOKEN",AB_package);
    list_constant_96 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)47L),
	    FIX((SI_Long)42L),FIX((SI_Long)61L));
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_96);
    list_constant_98 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)47L),
	    list_constant_97);
    list_constant_168 = STATIC_LIST((SI_Long)2L,Qdisambiguated_token,
	    list_constant_98);
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qpattern,Qjava_digit);
    list_constant_100 = STATIC_CONS(list_constant_99,Qnil);
    list_constant_104 = STATIC_CONS(Qab_plus,list_constant_100);
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qeither,FIX((SI_Long)120L),
	    FIX((SI_Long)88L));
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qpattern,Qhex_digit_char);
    list_constant_103 = STATIC_LIST((SI_Long)2L,Qab_plus,list_constant_101);
    list_constant_105 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)48L),
	    list_constant_102,list_constant_103);
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_104,
	    list_constant_105);
    list_constant_106 = STATIC_LIST((SI_Long)3L,Qeither,FIX((SI_Long)76L),
	    FIX((SI_Long)108L));
    list_constant_108 = STATIC_LIST((SI_Long)2L,Qmaybe,list_constant_106);
    list_constant_109 = STATIC_LIST((SI_Long)3L,Qseq,list_constant_107,
	    list_constant_108);
    Qnumeric_return_value = STATIC_SYMBOL("NUMERIC-RETURN-VALUE",AB_package);
    list_constant_110 = STATIC_CONS(Qnumeric_return_value,Qnil);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)3L,Qinteger,
	    list_constant_109,list_constant_110);
    list_constant_112 = STATIC_LIST((SI_Long)3L,Qeither,FIX((SI_Long)69L),
	    FIX((SI_Long)101L));
    list_constant_111 = STATIC_LIST((SI_Long)3L,Qeither,FIX((SI_Long)43L),
	    FIX((SI_Long)45L));
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qmaybe,list_constant_111);
    list_constant_114 = STATIC_LIST((SI_Long)4L,Qseq,list_constant_112,
	    list_constant_113,list_constant_104);
    list_constant_115 = STATIC_CONS(list_constant_114,Qnil);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_104,list_constant_115);
    list_constant_117 = STATIC_CONS(Qkleene,list_constant_100);
    list_constant_116 = STATIC_CONS(Qmaybe,list_constant_115);
    list_constant_118 = STATIC_CONS(list_constant_116,Qnil);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)5L,Qseq,
	    list_constant_104,FIX((SI_Long)46L),list_constant_117,
	    list_constant_118);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)4L,Qseq,
	    FIX((SI_Long)46L),list_constant_104,list_constant_118);
    list_constant_123 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_119,
	    list_constant_120,list_constant_121);
    list_constant_122 = STATIC_LIST((SI_Long)5L,Qeither,FIX((SI_Long)70L),
	    FIX((SI_Long)102L),FIX((SI_Long)68L),FIX((SI_Long)100L));
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qmaybe,list_constant_122);
    list_constant_125 = STATIC_LIST((SI_Long)3L,Qseq,list_constant_123,
	    list_constant_124);
    list_constant_170 = STATIC_LIST_STAR((SI_Long)3L,Qfloat,
	    list_constant_125,list_constant_110);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    list_constant_126 = STATIC_CONS(Qab_dot,Qnil);
    list_constant_127 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)92L),
	    list_constant_126);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qpattern,Qab_string_char);
    list_constant_129 = STATIC_LIST((SI_Long)3L,Qeither,list_constant_127,
	    list_constant_128);
    list_constant_130 = STATIC_LIST((SI_Long)2L,Qkleene,list_constant_129);
    list_constant_131 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)34L),
	    list_constant_130,FIX((SI_Long)34L));
    Qalphabet_strip_delimitors_off_string = 
	    STATIC_SYMBOL("ALPHABET-STRIP-DELIMITORS-OFF-STRING",AB_package);
    list_constant_171 = STATIC_LIST((SI_Long)3L,Qwhole_string,
	    list_constant_131,Qalphabet_strip_delimitors_off_string);
    Qjava_character_literal = STATIC_SYMBOL("JAVA-CHARACTER-LITERAL",
	    AB_package);
    list_constant_139 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qsimple_character_literal);
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qescape_character_literal);
    list_constant_140 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)92L),
	    list_constant_132);
    list_constant_133 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qoctal_character_literal);
    list_constant_134 = STATIC_LIST((SI_Long)2L,list_constant_133,
	    list_constant_133);
    list_constant_136 = STATIC_CONS(Qseq,list_constant_134);
    list_constant_135 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qhalf_octal_character_literal);
    list_constant_137 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_135,list_constant_134);
    list_constant_138 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_133,
	    list_constant_136,list_constant_137);
    list_constant_141 = STATIC_LIST((SI_Long)3L,Qseq,FIX((SI_Long)92L),
	    list_constant_138);
    list_constant_142 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_139,
	    list_constant_140,list_constant_141);
    list_constant_143 = STATIC_CONS(FIX((SI_Long)39L),Qnil);
    list_constant_144 = STATIC_LIST_STAR((SI_Long)4L,Qseq,
	    FIX((SI_Long)39L),list_constant_142,list_constant_143);
    list_constant_172 = STATIC_LIST((SI_Long)3L,Qjava_character_literal,
	    list_constant_144,Qtokenize_java_character_literal);
    Qbad_java_character_literal = 
	    STATIC_SYMBOL("BAD-JAVA-CHARACTER-LITERAL",AB_package);
    list_constant_157 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    FIX((SI_Long)39L),list_constant_143);
    list_constant_145 = STATIC_LIST((SI_Long)2L,Qinverted_class,
	    list_constant_143);
    list_constant_146 = STATIC_CONS(list_constant_145,Qnil);
    list_constant_158 = STATIC_LIST_STAR((SI_Long)4L,Qseq,
	    FIX((SI_Long)39L),list_constant_139,list_constant_146);
    list_constant_150 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qbad_escape_character_literal);
    list_constant_151 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_132,list_constant_146);
    list_constant_147 = STATIC_LIST((SI_Long)2L,Qpattern,
	    Qbad_octal_character_literal);
    list_constant_148 = STATIC_LIST((SI_Long)2L,list_constant_133,
	    list_constant_147);
    list_constant_152 = STATIC_CONS(Qseq,list_constant_148);
    list_constant_153 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_133,list_constant_148);
    list_constant_149 = STATIC_LIST((SI_Long)5L,Qeither,FIX((SI_Long)52L),
	    FIX((SI_Long)53L),FIX((SI_Long)54L),FIX((SI_Long)55L));
    list_constant_154 = STATIC_LIST_STAR((SI_Long)3L,Qseq,
	    list_constant_149,list_constant_134);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)5L,Qseq,
	    list_constant_135,list_constant_133,list_constant_133,
	    list_constant_146);
    list_constant_156 = STATIC_LIST((SI_Long)7L,Qeither,list_constant_150,
	    list_constant_151,list_constant_152,list_constant_153,
	    list_constant_154,list_constant_155);
    list_constant_159 = STATIC_LIST((SI_Long)4L,Qseq,FIX((SI_Long)39L),
	    FIX((SI_Long)92L),list_constant_156);
    list_constant_160 = STATIC_LIST((SI_Long)4L,Qeither,list_constant_157,
	    list_constant_158,list_constant_159);
    list_constant_173 = STATIC_LIST((SI_Long)3L,
	    Qbad_java_character_literal,list_constant_160,
	    Qtokenize_bad_java_character_literal);
    Qself_terminating_punctuation_mark = 
	    STATIC_SYMBOL("SELF-TERMINATING-PUNCTUATION-MARK",AB_package);
    temp_2 = LIST_2(Qjava_letter,LIST_2(Qcharacter_class,
	    Java_identifier_start_character_class));
    temp_3 = LIST_2(Qjava_letter_quote_free,LIST_2(Qcharacter_class,
	    Java_identifier_quote_free_start_character_class));
    temp_4 = LIST_2(Qjava_letter_or_digit,LIST_2(Qcharacter_class,
	    Java_identifier_part_character_class));
    temp_5 = LIST_2(Qjava_letter_or_digit_quote_free,
	    LIST_2(Qcharacter_class,
	    Java_identifier_quote_free_part_character_class));
    temp_6 = LIST_2(Qjava_digit,LIST_2(Qcharacter_class,
	    Unicode_digit_possibly_undefined_character_class));
    list0 = Java_escape_character_literal_alist;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp_1 = CAR(list0);
	temp_1 = CAR(temp_1);
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    temp_1 = result_1;
    temp_7 = LIST_2(Qescape_character_literal,CONS(Qeither,temp_1));
    list0 = Java_octal_character_literal_alist;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp_1 = CAR(list0);
	temp_1 = CAR(temp_1);
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    temp_1 = result_1;
    temp_8 = LIST_2(Qoctal_character_literal,CONS(Qeither,temp_1));
    temp_9 = LIST_2(Qhalf_octal_character_literal,CONS(Qeither,
	    Java_half_octal_characters));
    list0 = Java_escape_character_literal_alist;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp_1 = CAR(list0);
	temp_1 = CAR(temp_1);
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    temp_1 = result_1;
    list0 = Java_octal_character_literal_alist;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp = CAR(list0);
	temp = CAR(temp);
	new_last = CONS(temp,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    temp = result_1;
    temp = LIST_2(Qbad_escape_character_literal,LIST_2(Qinverted_class,
	    append2(temp_1,temp)));
    temp_1 = FIX((SI_Long)39L);
    list0 = Java_octal_character_literal_alist;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp_10 = CAR(list0);
	temp_10 = CAR(temp_10);
	new_last = CONS(temp_10,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    temp_10 = result_1;
    temp_9 = list_star(15,temp_2,temp_3,temp_4,temp_5,temp_6,
	    list_constant_161,list_constant_162,temp_7,temp_8,temp_9,temp,
	    LIST_2(Qbad_octal_character_literal,LIST_2(Qinverted_class,
	    CONS(temp_1,temp_10))),LIST_2(Qnewline_char,
	    LIST_2(Qcharacter_class,Newline_chars_for_java_tokens)),
	    LIST_2(Qchar_within_single_line_comment,LIST_2(Qinverted_class,
	    Newline_chars_for_java_tokens)),list_constant_163);
    temp_1 = 
	    convert_java_separators_or_operators_to_seq_tokens(Java_single_character_constituent_operators_as_string);
    temp = list_star(3,Qjava_symbol,list_star(3,Qeither,list_constant_164,
	    append2(temp_1,
	    convert_java_separators_or_operators_to_seq_tokens(Java_multi_character_operators_as_conglomerated_string))),
	    list_constant_165);
    temp_1 = 
	    convert_java_separators_or_operators_to_seq_tokens(Java_separators_as_conglomerated_string);
    temp_1 = append2(temp_1,
	    convert_java_separators_or_operators_to_seq_tokens(Java_single_character_nonconstituent_operators_as_string));
    Java_tokens = list(11,temp_9,list_constant_166,list_constant_167,
	    list_constant_168,list_constant_169,list_constant_170,temp,
	    list_constant_171,list_constant_172,list_constant_173,
	    LIST_2(Qself_terminating_punctuation_mark,CONS(Qeither,temp_1)));
    Java_tokenizer = compile_permanent_lexing_table(Java_tokens);
    Qabstract = STATIC_SYMBOL("ABSTRACT",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qab_catch = STATIC_SYMBOL("CATCH",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qconst = STATIC_SYMBOL("CONST",AB_package);
    Qab_continue = STATIC_SYMBOL("CONTINUE",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qdouble = STATIC_SYMBOL("DOUBLE",AB_package);
    Qelse = STATIC_SYMBOL("ELSE",AB_package);
    Qextends = STATIC_SYMBOL("EXTENDS",AB_package);
    Qfinal = STATIC_SYMBOL("FINAL",AB_package);
    Qfinally = STATIC_SYMBOL("FINALLY",AB_package);
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qgoto = STATIC_SYMBOL("GOTO",AB_package);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qimplements = STATIC_SYMBOL("IMPLEMENTS",AB_package);
    Qinstanceof = STATIC_SYMBOL("INSTANCEOF",AB_package);
    Qint = STATIC_SYMBOL("INT",AB_package);
    Qinterface = STATIC_SYMBOL("INTERFACE",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    Qnew = STATIC_SYMBOL("NEW",AB_package);
    Qprivate = STATIC_SYMBOL("PRIVATE",AB_package);
    Qprotected = STATIC_SYMBOL("PROTECTED",AB_package);
    Qpublic = STATIC_SYMBOL("PUBLIC",AB_package);
    Qshort = STATIC_SYMBOL("SHORT",AB_package);
    Qstatic = STATIC_SYMBOL("STATIC",AB_package);
    Qsuper = STATIC_SYMBOL("SUPER",AB_package);
    Qswitch = STATIC_SYMBOL("SWITCH",AB_package);
    Qsynchronized = STATIC_SYMBOL("SYNCHRONIZED",AB_package);
    Qthis = STATIC_SYMBOL("THIS",AB_package);
    Qthrows = STATIC_SYMBOL("THROWS",AB_package);
    Qtransient = STATIC_SYMBOL("TRANSIENT",AB_package);
    Qtry = STATIC_SYMBOL("TRY",AB_package);
    Qvoid = STATIC_SYMBOL("VOID",AB_package);
    Qvolatile = STATIC_SYMBOL("VOLATILE",AB_package);
    Qwhile = STATIC_SYMBOL("WHILE",AB_package);
    list_constant_174 = STATIC_LIST((SI_Long)16L,Qprotected,Qpublic,
	    Qreturn,Qshort,Qstatic,Qsuper,Qswitch,Qsynchronized,Qthis,
	    Qthrow,Qthrows,Qtransient,Qtry,Qvoid,Qvolatile,Qwhile);
    list_constant_175 = STATIC_LIST_STAR((SI_Long)32L,Qabstract,Qboolean,
	    Qbreak,Qbyte,Qcase,Qab_catch,Qchar,Qab_class,Qconst,
	    Qab_continue,Qdefault,Qdo,Qdouble,Qelse,Qextends,Qfinal,
	    Qfinally,Qfloat,Qfor,Qgoto,Qab_if,Qimplements,Qimport,
	    Qinstanceof,Qint,Qinterface,Qlong,Qnative,Qnew,Qpackage_type,
	    Qprivate,list_constant_174);
    Java_reserved_words_as_uppercase_symbols = list_constant_175;
    list0 = Java_reserved_words_as_uppercase_symbols;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	x = CAR(list0);
	temp_1 = string_downcase(1,SYMBOL_NAME(x));
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    Java_reserved_words_as_string = result_1;
    symbol = Nil;
    ab_loop_list_ = Java_reserved_words_as_uppercase_symbols;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = LIST_1(intern_java_reserved_word_as_category(symbol));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    Java_reserved_words_as_lowercase_categories = ab_loopvar_;
    goto end_1;
    Java_reserved_words_as_lowercase_categories = Qnil;
  end_1:;
    QTRUE = STATIC_SYMBOL("true",AB_package);
    QFALSE = STATIC_SYMBOL("false",AB_package);
    QNULL = STATIC_SYMBOL("null",AB_package);
    list_constant_176 = STATIC_LIST((SI_Long)3L,QTRUE,QFALSE,QNULL);
    Java_reserved_expressions_as_lowercase_categories = list_constant_176;
    reserved_expression = Nil;
    ab_loop_list_ = Java_reserved_expressions_as_lowercase_categories;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    reserved_expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(reserved_expression,T,Qjava_reserved_word_p);
    goto next_loop_1;
  end_loop_1:;
    list0 = Java_reserved_expressions_as_lowercase_categories;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp_1 = SYMBOL_NAME(CAR(list0));
	new_last = CONS(temp_1,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    Java_reserved_expressions_as_string = result_1;
    intern_java_reserved_word_as_category(Qstar);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    Java_separators_as_categories = 
	    convert_java_separators_or_operators_to_symbols(Java_separators_as_conglomerated_string);
    temp_1 = 
	    convert_java_separators_or_operators_to_symbols(Java_single_character_operators_as_conglomerated_string);
    Java_operators_as_categories = append2(temp_1,
	    convert_java_separators_or_operators_to_symbols(Java_multi_character_operators_as_conglomerated_string));
    Qjava_compilation_unit_or_none = 
	    STATIC_SYMBOL("JAVA-COMPILATION-UNIT-OR-NONE",AB_package);
    Qjava_class_body_declarations_or_none = 
	    STATIC_SYMBOL("JAVA-CLASS-BODY-DECLARATIONS-OR-NONE",AB_package);
    list_constant_177 = STATIC_LIST((SI_Long)2L,
	    Qjava_compilation_unit_or_none,
	    Qjava_class_body_declarations_or_none);
    if (Java_editing_categories == UNBOUND)
	Java_editing_categories = list_constant_177;
    Qtl_tl = STATIC_SYMBOL("~~",AB_package);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qcopy_symbol_name_of_possible_java_reserved_word = 
	    STATIC_SYMBOL("COPY-SYMBOL-NAME-OF-POSSIBLE-JAVA-RESERVED-WORD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_symbol_name_of_possible_java_reserved_word,
	    STATIC_FUNCTION(copy_symbol_name_of_possible_java_reserved_word,
	    NIL,FALSE,2,2));
    set_token_menu_string_to_display_for_java_reserved_words();
    string_constant_180 = 
	    STATIC_STRING("1m1n83DGy83-0Nyl1n83DGy1m9k83-I=y83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_180));
    string_constant_181 = 
	    STATIC_STRING("1m1n83DCy83jYyl1n83DCy1m9k83-I=y83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_181));
    QNONE = STATIC_SYMBOL("none",AB_package);
    set_token_menu_string_to_display_function(QNONE,
	    SYMBOL_FUNCTION(Qcopy_symbol_name_of_possible_java_reserved_word));
    Qjava_class_and_interface_names = 
	    STATIC_SYMBOL("JAVA-CLASS-AND-INTERFACE-NAMES",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    list_constant_179 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qjava_class_and_interface_names),
	    Qtype_specification_simple_expansion,list_constant_179);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_180 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_181 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qtext,
	    list_constant_180);
    define_type_specification_explicit_complex_type(Qjava_class_and_interface_names,
	    list_constant_181);
    java_class_and_interface_names_evaluation_getter_1 = 
	    STATIC_FUNCTION(java_class_and_interface_names_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qjava_class_and_interface_names,
	    java_class_and_interface_names_evaluation_getter_1);
    Qtwrite = STATIC_SYMBOL("TWRITE",AB_package);
    string_constant_2 = STATIC_STRING(", ");
    Qwrite_java_class_and_interface_names_from_slot = 
	    STATIC_SYMBOL("WRITE-JAVA-CLASS-AND-INTERFACE-NAMES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_java_class_and_interface_names_from_slot,
	    STATIC_FUNCTION(write_java_class_and_interface_names_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qjava_class_and_interface_names,
	    SYMBOL_FUNCTION(Qwrite_java_class_and_interface_names_from_slot),
	    Qslot_value_writer);
    Qjava_read_only_package_declaration = 
	    STATIC_SYMBOL("JAVA-READ-ONLY-PACKAGE-DECLARATION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qjava_read_only_package_declaration),
	    Qtype_specification_simple_expansion,list_constant_179);
    define_type_specification_explicit_complex_type(Qjava_read_only_package_declaration,
	    list_constant_181);
    java_read_only_package_declaration_evaluation_getter_1 = 
	    STATIC_FUNCTION(java_read_only_package_declaration_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qjava_read_only_package_declaration,
	    java_read_only_package_declaration_evaluation_getter_1);
    array_constant_1 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_java_read_only_package_declaration_from_slot = 
	    STATIC_SYMBOL("WRITE-JAVA-READ-ONLY-PACKAGE-DECLARATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_java_read_only_package_declaration_from_slot,
	    STATIC_FUNCTION(write_java_read_only_package_declaration_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qjava_read_only_package_declaration,
	    SYMBOL_FUNCTION(Qwrite_java_read_only_package_declaration_from_slot),
	    Qslot_value_writer);
    Qjava_read_only_import_declarations = 
	    STATIC_SYMBOL("JAVA-READ-ONLY-IMPORT-DECLARATIONS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qjava_read_only_import_declarations),
	    Qtype_specification_simple_expansion,list_constant_179);
    list_constant_182 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_181,list_constant_180);
    define_type_specification_explicit_complex_type(Qjava_read_only_import_declarations,
	    list_constant_182);
    java_read_only_import_declarations_evaluation_getter_1 = 
	    STATIC_FUNCTION(java_read_only_import_declarations_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qjava_read_only_import_declarations,
	    java_read_only_import_declarations_evaluation_getter_1);
    array_constant_2 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_java_read_only_import_declarations_from_slot = 
	    STATIC_SYMBOL("WRITE-JAVA-READ-ONLY-IMPORT-DECLARATIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_java_read_only_import_declarations_from_slot,
	    STATIC_FUNCTION(write_java_read_only_import_declarations_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qjava_read_only_import_declarations,
	    SYMBOL_FUNCTION(Qwrite_java_read_only_import_declarations_from_slot),
	    Qslot_value_writer);
    note_text_category_evaluator_interface(Qjava_compilation_unit_or_none);
    set_property_value_function(get_symbol_properties_function(Qjava_compilation_unit_or_none),
	    Qtype_specification_simple_expansion,Qtext);
    define_type_specification_explicit_complex_type(Qjava_compilation_unit_or_none,
	    Qtext);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qjava_compilation_unit_or_none);
    array_constant_3 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    java_compilation_unit_or_none_evaluation_setter_1 = 
	    STATIC_FUNCTION(java_compilation_unit_or_none_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qjava_compilation_unit_or_none,
	    java_compilation_unit_or_none_evaluation_setter_1);
    java_compilation_unit_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(java_compilation_unit_or_none_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qjava_compilation_unit_or_none,
	    java_compilation_unit_or_none_evaluation_getter_1);
    Qcategory_committer_function = 
	    STATIC_SYMBOL("CATEGORY-COMMITTER-FUNCTION",AB_package);
    Qtext_category_slot_access_committer = 
	    STATIC_SYMBOL("TEXT-CATEGORY-SLOT-ACCESS-COMMITTER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qjava_compilation_unit_or_none),
	    Qcategory_committer_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_committer));
    Qcategory_extracter_function = 
	    STATIC_SYMBOL("CATEGORY-EXTRACTER-FUNCTION",AB_package);
    Qtext_category_slot_access_extracter = 
	    STATIC_SYMBOL("TEXT-CATEGORY-SLOT-ACCESS-EXTRACTER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qjava_compilation_unit_or_none),
	    Qcategory_extracter_function,
	    SYMBOL_FUNCTION(Qtext_category_slot_access_extracter));
    Qcompilation_unit = STATIC_SYMBOL("COMPILATION-UNIT",AB_package);
    Qexternal_java_class = STATIC_SYMBOL("EXTERNAL-JAVA-CLASS",AB_package);
    alias_slot_name(3,Qcompilation_unit,Qtext,Qexternal_java_class);
    string_constant_3 = 
	    STATIC_STRING("Information lost when loading 5.0 beta KB.~%~\n         Please re-enter the following into the main text body of ~NF:~%~A");
    Qlost_spaces = STATIC_SYMBOL("LOST-SPACES",AB_package);
    Qline_width = STATIC_SYMBOL("LINE-WIDTH",AB_package);
    list_constant_2 = STATIC_CONS(Qline_width,Qnil);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qpackage_declaration = STATIC_SYMBOL("PACKAGE-DECLARATION",AB_package);
    Qput_package_declaration = STATIC_SYMBOL("PUT-PACKAGE-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_package_declaration,
	    STATIC_FUNCTION(put_package_declaration,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qpackage_declaration,
	    SYMBOL_FUNCTION(Qput_package_declaration),Qslot_putter);
    Qimport_declarations = STATIC_SYMBOL("IMPORT-DECLARATIONS",AB_package);
    Qtype_import_on_demand = STATIC_SYMBOL("TYPE-IMPORT-ON-DEMAND",AB_package);
    Qsingle_type_import = STATIC_SYMBOL("SINGLE-TYPE-IMPORT",AB_package);
    Qput_import_declarations = STATIC_SYMBOL("PUT-IMPORT-DECLARATIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_import_declarations,
	    STATIC_FUNCTION(put_import_declarations,NIL,FALSE,3,3));
    mutate_global_property(Qimport_declarations,
	    SYMBOL_FUNCTION(Qput_import_declarations),Qslot_putter);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qput_compilation_unit = STATIC_SYMBOL("PUT-COMPILATION-UNIT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_compilation_unit,
	    STATIC_FUNCTION(put_compilation_unit,NIL,FALSE,3,3));
    mutate_global_property(Qcompilation_unit,
	    SYMBOL_FUNCTION(Qput_compilation_unit),Qslot_putter);
    Qtype_declarations = STATIC_SYMBOL("TYPE-DECLARATIONS",AB_package);
    Qput_type_declarations_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TYPE-DECLARATIONS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_type_declarations_where_slot_is_absent,
	    STATIC_FUNCTION(put_type_declarations_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qtype_declarations,
	    SYMBOL_FUNCTION(Qput_type_declarations_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcompile_java_compilation_unit_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-JAVA-COMPILATION-UNIT-OR-NONE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_java_compilation_unit_or_none_for_slot,
	    STATIC_FUNCTION(compile_java_compilation_unit_or_none_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qjava_compilation_unit_or_none,
	    SYMBOL_FUNCTION(Qcompile_java_compilation_unit_or_none_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qjava_compilation_unit_or_none,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_4 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qconvert_mixed_case_text_to_hyphenated_symbol = 
	    STATIC_SYMBOL("CONVERT-MIXED-CASE-TEXT-TO-HYPHENATED-SYMBOL",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qconvert_mixed_case_text_to_hyphenated_symbol,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_mixed_case_text_to_hyphenated_symbol,
	    STATIC_FUNCTION(convert_mixed_case_text_to_hyphenated_symbol,
	    NIL,FALSE,1,1));
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qab_class,Qinterface);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qg2_new_secret_entity = STATIC_SYMBOL("G2-NEW-SECRET-ENTITY",AB_package);
    Qexternal_procedure = STATIC_SYMBOL("EXTERNAL-PROCEDURE",AB_package);
    Qexternal_method_declaration = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-DECLARATION",AB_package);
    Qexternal_method = STATIC_SYMBOL("EXTERNAL-METHOD",AB_package);
    Qexport_definition = STATIC_SYMBOL("EXPORT-DEFINITION",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)5L,Qexternal_java_class,
	    Qexternal_procedure,Qexternal_method_declaration,
	    Qexternal_method,Qexport_definition);
    string_constant_182 = STATIC_STRING("<!>");
    Caret_replacement_for_javac_problem = string_constant_182;
    array_constant_5 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qjava = STATIC_SYMBOL("JAVA",AB_package);
    Qoperate_on_javac_frame_notes = 
	    STATIC_SYMBOL("OPERATE-ON-JAVAC-FRAME-NOTES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qoperate_on_javac_frame_notes,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qreplace_javac_frame_notes = STATIC_SYMBOL("REPLACE-JAVAC-FRAME-NOTES",
	    AB_package);
    Qadd_javac_frame_notes = STATIC_SYMBOL("ADD-JAVAC-FRAME-NOTES",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdelete_javac_frame_notes = STATIC_SYMBOL("DELETE-JAVAC-FRAME-NOTES",
	    AB_package);
    Qjava_compilation_problems = STATIC_SYMBOL("JAVA-COMPILATION-PROBLEMS",
	    AB_package);
    Qdelete_frame_note_if_any = STATIC_SYMBOL("DELETE-FRAME-NOTE-IF-ANY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_frame_note_if_any,
	    STATIC_FUNCTION(delete_frame_note_if_any,NIL,FALSE,2,2));
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qoperate_on_javac_frame_notes,
	    STATIC_FUNCTION(operate_on_javac_frame_notes,NIL,FALSE,3,3));
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)43L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)45L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)49L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)50L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)52L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)53L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)56L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)57L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)58L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)59L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)62L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)63L,(SI_Long)57344L);
    string_constant_4 = STATIC_STRING("(~A) ");
    array_constant_7 = STATIC_ARRAY(list_constant_178,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)42L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)44L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)54L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)55L,(SI_Long)57344L);
    write_java_compilation_problems_note_1 = 
	    STATIC_FUNCTION(write_java_compilation_problems_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qjava_compilation_problems,
	    write_java_compilation_problems_note_1,Qframe_note_writer_1);
}
