/* boxes.c
 * Input file:  boxes.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "boxes.h"


static Object Qlost_spaces;        /* lost-spaces */

/* MAKE-LOST-SPACES-TEXT-ELEMENT */
Object make_lost_spaces_text_element(integer_or_text_string)
    Object integer_or_text_string;
{
    Object temp;

    x_note_fn_call(109,0);
    temp = slot_value_cons_1(Qlost_spaces,integer_or_text_string);
    return VALUES_1(temp);
}

/* MAKE-LOST-SPACES-PHRASE-TEXT-ELEMENT */
Object make_lost_spaces_phrase_text_element(integer_or_text_string)
    Object integer_or_text_string;
{
    Object temp;

    x_note_fn_call(109,1);
    temp = phrase_cons(Qlost_spaces,integer_or_text_string);
    return VALUES_1(temp);
}

/* TEXT-LINE-P-FUNCTION */
Object text_line_p_function(text_element)
    Object text_element;
{
    x_note_fn_call(109,2);
    return VALUES_1(INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != 
	    (SI_Long)0L ? T : Nil);
}

/* MAKE-EMPTY-TEXT */
Object make_empty_text()
{
    Object temp;

    x_note_fn_call(109,3);
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    return slot_value_list_2(temp,obtain_simple_text_string(FIX((SI_Long)0L)));
}

/* TEXT-BLANK-P */
Object text_blank_p(text)
    Object text;
{
    Object text_element, ab_loop_list_;

    x_note_fn_call(109,4);
    text_element = Nil;
    ab_loop_list_ = text;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L && 
	    IFIX(text_string_length(text_element)) > (SI_Long)0L &&  
	    !(IFIX(text_string_length(text_element)) == (SI_Long)1L && 
	    newline_p(FIX(UBYTE_16_ISAREF_1(text_element,(SI_Long)0L)))))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* TEXT-EMPTY-P */
Object text_empty_p(text)
    Object text;
{
    Object text_element, ab_loop_list_;

    x_note_fn_call(109,5);
    text_element = Nil;
    ab_loop_list_ = text;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	if ((SI_Long)0L == IFIX(text_string_length(text_element)))
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-TEXT */
Object reclaim_text(text)
    Object text;
{
    x_note_fn_call(109,6);
    reclaim_slot_value(text);
    return VALUES_1(Nil);
}

/* MAKE-INCOMPLETE-BOX-TRANSLATION-AND-TEXT */
Object make_incomplete_box_translation_and_text()
{
    Object temp;

    x_note_fn_call(109,7);
    temp = No_value;
    return slot_value_cons_1(temp,
	    convert_text_string_to_text(copy_text_string(Ellipsis_text_string)));
}

static Object Qparagraph;          /* paragraph */

static Object Qnewline;            /* newline */

static Object Qlinefeed;           /* linefeed */

/* TEXT-INCOMPLETE-P */
Object text_incomplete_p(text)
    Object text;
{
    Object ellipsis_char, temp, ab_end_line_index_qm;
    Object ab_end_character_index_qm, ab_suppress_lost_spaces_at_end_qm;
    Object ab_text_line, ab_lost_space_at_end_of_line, ab_next_text_tail_qm;
    Object ab_explicit_paragraph_or_newline_qm, ab_text_, ab_this_text_tail_qm;
    Object indentation_if_new_qm, character_1;
    SI_Long i, text_char, ab_line_index, ab_character_index, ab_line_length;
    SI_Long ab_current_indentation, temp_1, temp_2, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char temp_3;
    Object result;

    x_note_fn_call(109,8);
    ellipsis_char = Nil;
    i = (SI_Long)0L;
    text_char = (SI_Long)0L;
    temp = Nil;
    if (temp);
    else
	temp = FIX((SI_Long)1L);
    ab_line_index = IFIX(temp);
    temp = Nil;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    ab_character_index = IFIX(temp);
    ab_end_line_index_qm = Nil;
    if (ab_end_line_index_qm);
    else
	ab_end_line_index_qm = Nil;
    ab_end_character_index_qm = Nil;
    if (ab_end_character_index_qm);
    else
	ab_end_character_index_qm = Nil;
    ab_suppress_lost_spaces_at_end_qm = Nil;
    if (ab_suppress_lost_spaces_at_end_qm);
    else
	ab_suppress_lost_spaces_at_end_qm = Nil;
    ab_text_line = Nil;
    ab_line_length = (SI_Long)0L;
    ab_lost_space_at_end_of_line = Nil;
    ab_next_text_tail_qm = Nil;
    ab_current_indentation = (SI_Long)0L;
    ab_explicit_paragraph_or_newline_qm = Nil;
    ab_text_ = text;
    ab_this_text_tail_qm = Nil;
    if ( !TRUEP(ab_this_text_tail_qm))
	ab_this_text_tail_qm = find_text_tail_for_line(ab_text_,
		FIX(ab_line_index));
    result = get_next_text_line(ab_this_text_tail_qm);
    MVS_4(result,ab_text_line,temp,ab_lost_space_at_end_of_line,
	    ab_next_text_tail_qm);
    ab_line_length = IFIX(temp);
  next_loop:
    if (ab_end_line_index_qm && ab_line_index == 
	    IFIX(ab_end_line_index_qm) ||  !TRUEP(ab_next_text_tail_qm)) {
	temp_1 = ab_character_index;
	if (ab_suppress_lost_spaces_at_end_qm)
	    temp_2 = ab_line_length;
	else {
	    gensymed_symbol = ab_line_length;
	    gensymed_symbol_1 = FIXNUMP(ab_lost_space_at_end_of_line) ? 
		    IFIX(ab_lost_space_at_end_of_line) : 
		    IFIX(text_string_length(ab_lost_space_at_end_of_line));
	    temp_2 = gensymed_symbol + gensymed_symbol_1;
	}
	temp_3 = temp_1 >= temp_2;
	if (temp_3);
	else
	    temp_3 = ab_end_character_index_qm ? ab_character_index >= 
		    IFIX(ab_end_character_index_qm) : TRUEP(Qnil);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3)
	goto end_loop;
    indentation_if_new_qm = Nil;
    character_1 = Nil;
  next_loop_1:
    if (ab_character_index >= ab_line_length) {
	temp_2 = ab_character_index - ab_line_length;
	if (temp_2 < (FIXNUMP(ab_lost_space_at_end_of_line) ? 
		IFIX(ab_lost_space_at_end_of_line) : 
		IFIX(text_string_length(ab_lost_space_at_end_of_line)))) {
	    character_1 = FIXNUMP(ab_lost_space_at_end_of_line) ? 
		    FIX((SI_Long)32L) : 
		    FIX(UBYTE_16_ISAREF_1(ab_lost_space_at_end_of_line,
		    ab_character_index - ab_line_length));
	    ab_character_index = ab_character_index + (SI_Long)1L;
	    goto end_loop_1;
	}
	if ( !TRUEP(ab_next_text_tail_qm)) {
	    ab_explicit_paragraph_or_newline_qm = Nil;
	    character_1 = Nil;
	    text_char = IFIX(character_1);
	    goto end_1;
	}
	ab_this_text_tail_qm = ab_next_text_tail_qm;
	ab_line_index = ab_line_index + (SI_Long)1L;
	ab_character_index = (SI_Long)0L;
	result = get_next_text_line(ab_next_text_tail_qm);
	MVS_5(result,ab_text_line,temp,ab_lost_space_at_end_of_line,
		ab_next_text_tail_qm,indentation_if_new_qm);
	ab_line_length = IFIX(temp);
	if (indentation_if_new_qm)
	    ab_current_indentation = IFIX(indentation_if_new_qm);
    }
    else {
	temp = FIX(UBYTE_16_ISAREF_1(ab_text_line,ab_character_index));
	ab_character_index = ab_character_index + (SI_Long)1L;
	character_1 = temp;
	goto end_loop_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = character_1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)32767L))))
	switch (INTEGER_TO_SHORT(temp)) {
	  case 8233:
	    ab_explicit_paragraph_or_newline_qm = Qparagraph;
	    break;
	  case 8232:
	    ab_explicit_paragraph_or_newline_qm = Qnewline;
	    break;
	  case 13:
	    ab_explicit_paragraph_or_newline_qm = Qreturn;
	    break;
	  case 10:
	    ab_explicit_paragraph_or_newline_qm = Qlinefeed;
	    break;
	  default:
	    break;
	}
    text_char = IFIX(character_1);
    goto end_1;
    text_char = IFIX(Qnil);
  end_1:;
    if ( !(i < IFIX(Ellipsis_text_string_length)))
	return VALUES_1(Nil);
    ellipsis_char = FIX(UBYTE_16_ISAREF_1(Ellipsis_text_string,i));
    if (IFIX(ellipsis_char) != text_char)
	return VALUES_1(Nil);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(i == IFIX(Ellipsis_text_string_length) ? T : Nil);
    return VALUES_1(Qnil);
}

static Object Qintercepted;        /* intercepted */

/* ADD-INTERCEPTED-TOKEN-TO-TEXT */
Object add_intercepted_token_to_text(text)
    Object text;
{
    Object temp;

    x_note_fn_call(109,9);
    temp = slot_value_cons_1(slot_value_cons_1(Qintercepted,Nil),text);
    return VALUES_1(temp);
}

/* INTERCEPTED-TEXT-P */
Object intercepted_text_p(text)
    Object text;
{
    Object token, ab_loop_it_, text_old_value, temp;

    x_note_fn_call(109,10);
    token = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if (ATOM(text))
	goto end_loop;
    text_old_value = text;
    temp = FIRST(text_old_value);
    text = REST(text_old_value);
    token = temp;
    ab_loop_it_ = CONSP(token) ? (EQ(CAR(token),Qintercepted) ? T : Nil) : 
	    Qnil;
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

/* TEXTS-EQUAL-P */
Object texts_equal_p(text1,text2)
    Object text1, text2;
{
    Object text_string_1, text_string_2, end1, end2, ab_loop_iter_flag_;
    Object equal_p;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;

    x_note_fn_call(109,11);
    text_string_1 = convert_text_to_text_string(1,text1);
    text_string_2 = convert_text_to_text_string(1,text2);
    end1 = text_string_length(text_string_1);
    end2 = text_string_length(text_string_2);
    length1 = IFIX(end1) - (SI_Long)0L;
    length2 = IFIX(end2) - (SI_Long)0L;
    if (length1 == length2) {
	index1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(end1);
	index2 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(end2);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index2 = index2 + (SI_Long)1L;
	if (index2 >= ab_loop_bind__1)
	    goto end_loop;
	if ( !(UBYTE_16_ISAREF_1(text_string_1,index1) == 
		UBYTE_16_ISAREF_1(text_string_2,index2))) {
	    equal_p = Nil;
	    goto end_1;
	}
	ab_loop_iter_flag_ = Nil;
	index1 = index1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	equal_p = T;
	goto end_1;
	equal_p = Qnil;
      end_1:;
    }
    else
	equal_p = Nil;
    reclaim_text_string(text_string_1);
    reclaim_text_string(text_string_2);
    return VALUES_1(equal_p);
}

Object The_type_description_of_text_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_text_spots, Qchain_of_available_text_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Text_spot_count, Qtext_spot_count);

Object Chain_of_available_text_spots_vector = UNBOUND;

/* TEXT-SPOT-STRUCTURE-MEMORY-USAGE */
Object text_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(109,12);
    temp = Text_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEXT-SPOT-COUNT */
Object outstanding_text_spot_count()
{
    Object def_structure_text_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,13);
    gensymed_symbol = IFIX(Text_spot_count);
    def_structure_text_spot_variable = Chain_of_available_text_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_text_spot_variable))
	goto end_loop;
    def_structure_text_spot_variable = 
	    ISVREF(def_structure_text_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEXT-SPOT-1 */
Object reclaim_text_spot_1(text_spot)
    Object text_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(109,14);
    inline_note_reclaim_cons(text_spot,Nil);
    structure_being_reclaimed = text_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(text_spot,(SI_Long)2L));
      SVREF(text_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_text_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(text_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_text_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = text_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-SPOT */
Object reclaim_structure_for_text_spot(text_spot)
    Object text_spot;
{
    x_note_fn_call(109,15);
    return reclaim_text_spot_1(text_spot);
}

static Object Qg2_defstruct_structure_name_text_spot_g2_struct;  /* g2-defstruct-structure-name::text-spot-g2-struct */

/* MAKE-PERMANENT-TEXT-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_text_spot_structure_internal()
{
    Object def_structure_text_spot_variable, defstruct_g2_text_spot_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(109,16);
    def_structure_text_spot_variable = Nil;
    atomic_incff_symval(Qtext_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_text_spot_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_text_spot_variable = the_array;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_spot_g2_struct;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_text_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_text_spot_variable = defstruct_g2_text_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_text_spot_variable);
}

static Object Kunknown;            /* :unknown */

/* MAKE-TEXT-SPOT-1 */
Object make_text_spot_1()
{
    Object def_structure_text_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(109,17);
    def_structure_text_spot_variable = 
	    ISVREF(Chain_of_available_text_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_text_spot_variable) {
	svref_arg_1 = Chain_of_available_text_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_text_spot_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_text_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_spot_g2_struct;
    }
    else
	def_structure_text_spot_variable = 
		make_permanent_text_spot_structure_internal();
    inline_note_allocate_cons(def_structure_text_spot_variable,Nil);
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_text_spot_variable,(SI_Long)6L) = FIX((SI_Long)1000L);
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)8L)) = Kunknown;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_text_spot_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_text_spot_variable);
}

Object The_type_description_of_table_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_table_spots, Qchain_of_available_table_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Table_spot_count, Qtable_spot_count);

Object Chain_of_available_table_spots_vector = UNBOUND;

/* TABLE-SPOT-STRUCTURE-MEMORY-USAGE */
Object table_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(109,18);
    temp = Table_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)23L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TABLE-SPOT-COUNT */
Object outstanding_table_spot_count()
{
    Object def_structure_table_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,19);
    gensymed_symbol = IFIX(Table_spot_count);
    def_structure_table_spot_variable = Chain_of_available_table_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_table_spot_variable))
	goto end_loop;
    def_structure_table_spot_variable = 
	    ISVREF(def_structure_table_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TABLE-SPOT-1 */
Object reclaim_table_spot_1(table_spot)
    Object table_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(109,20);
    inline_note_reclaim_cons(table_spot,Nil);
    structure_being_reclaimed = table_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(table_spot,(SI_Long)2L));
      SVREF(table_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_table_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(table_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_table_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = table_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TABLE-SPOT */
Object reclaim_structure_for_table_spot(table_spot)
    Object table_spot;
{
    x_note_fn_call(109,21);
    return reclaim_table_spot_1(table_spot);
}

static Object Qg2_defstruct_structure_name_table_spot_g2_struct;  /* g2-defstruct-structure-name::table-spot-g2-struct */

/* MAKE-PERMANENT-TABLE-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_table_spot_structure_internal()
{
    Object def_structure_table_spot_variable, defstruct_g2_table_spot_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(109,22);
    def_structure_table_spot_variable = Nil;
    atomic_incff_symval(Qtable_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_table_spot_variable = Nil;
	gensymed_symbol = (SI_Long)23L;
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
	defstruct_g2_table_spot_variable = the_array;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_table_spot_g2_struct;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_table_spot_variable,FIX((SI_Long)15L)) = Nil;
	def_structure_table_spot_variable = defstruct_g2_table_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_table_spot_variable);
}

/* MAKE-TABLE-SPOT-1 */
Object make_table_spot_1()
{
    Object def_structure_table_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(109,23);
    def_structure_table_spot_variable = 
	    ISVREF(Chain_of_available_table_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_table_spot_variable) {
	svref_arg_1 = Chain_of_available_table_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_table_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_table_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_table_spot_g2_struct;
    }
    else
	def_structure_table_spot_variable = 
		make_permanent_table_spot_structure_internal();
    inline_note_allocate_cons(def_structure_table_spot_variable,Nil);
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_table_spot_variable,(SI_Long)6L) = 
	    FIX((SI_Long)1000L);
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)8L)) = Kunknown;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_table_spot_variable,FIX((SI_Long)22L)) = Nil;
    return VALUES_1(def_structure_table_spot_variable);
}

static Object Qimage_plane;        /* image-plane */

static Object Qx_in_window;        /* x-in-window */

static Object Qy_in_window;        /* y-in-window */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Ktight;              /* :tight */

/* FILL-OUT-TEXT-SPOT */
Object fill_out_text_spot(text_spot,text_box_or_table,mouse_pointer,text,
	    format_frame,format_plist)
    Object text_spot, text_box_or_table, mouse_pointer, text, format_frame;
    Object format_plist;
{
    Object image_plane_qm, text_box_qm, text_cell_qm, left_edge_of_cell_qm;
    Object top_edge_of_cell_qm, sub_class_bit_vector, svref_new_value;
    Object x_in_window, y_in_window, tightness, ab_loop_list_, tightness_arg;
    Object ab_loop_list__1, lost_spaces_arg, ab_loop_list__2, line_index_qm;
    Object character_index_qm, temp_1, x_of_cursor_in_text_qm;
    Object y_of_cursor_in_text_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(109,24);
    image_plane_qm = blackboard_argument_of_mouse_pointer(mouse_pointer,
	    Qimage_plane);
    text_box_qm = Nil;
    text_cell_qm = Nil;
    left_edge_of_cell_qm = Nil;
    top_edge_of_cell_qm = Nil;
    SVREF(text_spot,FIX((SI_Long)13L)) = text;
    SVREF(text_spot,FIX((SI_Long)14L)) = format_frame;
    SVREF(text_spot,FIX((SI_Long)15L)) = format_plist;
    sub_class_bit_vector = ISVREF(ISVREF(text_box_or_table,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	text_box_qm = text_box_or_table;
	temp = TRUEP(image_plane_qm);
    }
    else {
	text_cell_qm = ISVREF(text_spot,(SI_Long)18L);
	left_edge_of_cell_qm = ISVREF(text_spot,(SI_Long)19L);
	top_edge_of_cell_qm = ISVREF(text_spot,(SI_Long)20L);
	svref_new_value = table_visible_in_image_plane_p(text_box_or_table,
		text_cell_qm,image_plane_qm);
	SVREF(text_spot,FIX((SI_Long)7L)) = svref_new_value;
	temp = TRUEP(T);
    }
    if (temp) {
	x_in_window = blackboard_argument_of_mouse_pointer(mouse_pointer,
		Qx_in_window);
	y_in_window = blackboard_argument_of_mouse_pointer(mouse_pointer,
		Qy_in_window);
	tightness = Nil;
	ab_loop_list_ = list_constant;
	tightness_arg = Nil;
	ab_loop_list__1 = list_constant_1;
	lost_spaces_arg = Nil;
	ab_loop_list__2 = list_constant_2;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	tightness = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	tightness_arg = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop;
	lost_spaces_arg = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	result = find_position_in_text_given_image_plane(14,
		text_box_or_table,text_box_qm,text_cell_qm,
		left_edge_of_cell_qm,top_edge_of_cell_qm,lost_spaces_arg,
		image_plane_qm,x_in_window,y_in_window,Nil,Nil,Nil,
		tightness_arg,Nil);
	MVS_5(result,line_index_qm,character_index_qm,temp_1,
		x_of_cursor_in_text_qm,y_of_cursor_in_text_qm);
	if (line_index_qm) {
	    SVREF(text_spot,FIX((SI_Long)6L)) = tightness;
	    SVREF(text_spot,FIX((SI_Long)9L)) = line_index_qm;
	    SVREF(text_spot,FIX((SI_Long)10L)) = character_index_qm;
	    SVREF(text_spot,FIX((SI_Long)11L)) = x_of_cursor_in_text_qm;
	    SVREF(text_spot,FIX((SI_Long)12L)) = y_of_cursor_in_text_qm;
	    sub_class_bit_vector = ISVREF(ISVREF(text_box_or_table,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if ((temp ?  !TRUEP(ISVREF(text_spot,(SI_Long)7L)) : 
		    TRUEP(Nil)) ? EQ(tightness_arg,Ktight) : TRUEP(Nil))
		SVREF(text_spot,FIX((SI_Long)7L)) = T;
	    return VALUES_1(Nil);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* BOX-TRANSLATION-AND-TEXT-FUNCTION */
Object box_translation_and_text_function(text_box)
    Object text_box;
{
    x_note_fn_call(109,25);
    return VALUES_1(ISVREF(text_box,(SI_Long)16L));
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

/* COLOR-OR-METACOLOR-EVALUATION-SETTER */
Object color_or_metacolor_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(109,26);
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
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_color_or_metacolor_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_color_or_metacolor_evaluation_setter:
    return result;
}

/* COLOR-OR-METACOLOR-EVALUATION-GETTER */
Object color_or_metacolor_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(109,27);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

/* FONT-NAME-EVALUATION-SETTER */
Object font_name_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(109,28);
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
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_font_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_font_name_evaluation_setter:
    return result;
}

/* FONT-NAME-EVALUATION-GETTER */
Object font_name_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(109,29);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qnone;               /* none */

/* COMPILE-TEXT-CELL-COLORS-FOR-SLOT */
Object compile_text_cell_colors_for_slot varargs_1(int, n)
{
    Object parse, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,30);
    INIT_ARGS_nonrelocating();
    parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qregion;             /* region */

static Object Qcolor;              /* color */

/* TEXT-CELL-COLORS-EVALUATION-SETTER */
Object text_cell_colors_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object text_cell_color_info, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(109,31);
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
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_text_cell_colors_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	text_cell_color_info = Nil;
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
	text_cell_color_info = validated_elt;
	gensymed_symbol = text_cell_color_info;
	temp_1 = estructure_slot(gensymed_symbol,Qregion,Nil);
	ab_loopvar__2 = phrase_cons(phrase_cons(temp_1,
		estructure_slot(gensymed_symbol,Qcolor,Nil)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    else
	result = VALUES_1(Qnone);
  end_text_cell_colors_evaluation_setter:
    return result;
}

/* TEXT-CELL-COLORS-EVALUATION-GETTER */
Object text_cell_colors_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object text_cell_color_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, temp;

    x_note_fn_call(109,32);
    if (slot_value) {
	text_cell_color_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	text_cell_color_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(gensymed_symbol_1,Qregion,
		M_CAR(text_cell_color_info));
	set_evaluation_structure_slot(gensymed_symbol_1,Qcolor,
		M_CDR(text_cell_color_info));
	ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant;     /* "none" */

static Object string_constant_1;   /* "~(~a is ~a~)" */

static Object Qline_color;         /* line-color */

static Object Qtext_color;         /* text-color */

static Object string_constant_2;   /* "; " */

/* WRITE-TEXT-CELL-COLORS-FROM-SLOT */
Object write_text_cell_colors_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object property_1, rest_1, ab_loop_list_, region, color;

    x_note_fn_call(109,33);
    if ( !TRUEP(value))
	return twrite(string_constant);
    else {
	property_1 = Nil;
	rest_1 = Nil;
	ab_loop_list_ = value;
	region = Nil;
	color = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	property_1 = CAR(ab_loop_list_);
	rest_1 = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	region = CAR(property_1);
	color = CDR(property_1);
	tformat(3,string_constant_1,EQ(region,Qline_color) ? Qtext_color : 
		region,color);
	if (rest_1)
	    twrite(string_constant_2);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qdefault_text_box_colors_for_class;  /* default-text-box-colors-for-class */

/* UPDATE-DEFAULT-TEXT-BOX-COLORS-FOR-CLASS */
Object update_default_text_box_colors_for_class(text_box_class,new_value)
    Object text_box_class, new_value;
{
    Object scope_conses, ab_loopvar_, class_1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,34);
    change_class_slot_description_value(Qdefault_text_box_colors_for_class,
	    text_box_class,new_value);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = text_box_class;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      process_default_text_box_colors(class_1,Nil);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qborder_color;       /* border-color */

static Object Qbackground_color;   /* background-color */

static Object Qtext_box;           /* text-box */

static Object Qtext_cell_plist_for_text_box;  /* text-cell-plist-for-text-box */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

/* PROCESS-DEFAULT-TEXT-BOX-COLORS */
Object process_default_text_box_colors(class_1,
	    called_from_alter_inheritance_qm)
    Object class_1, called_from_alter_inheritance_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, default_text_box_colors;
    Object class_description, class_inheritance_path;
    Object specified_border_color_qm, specified_text_color_qm;
    Object specified_background_color_qm, superior, ab_loop_list_;
    Object class_description_qm, sub_class_bit_vector;
    Object superior_specified_border_color_qm, temp_3;
    Object superior_specified_text_color_qm, temp_4;
    Object superior_specified_background_color_qm, plist_init_form_qm;
    Object plist_slot_description_from_text_box_class, new_slot_description;
    Object current_drawing_priority, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object instance, plist_slot_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(109,35);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_1;
    key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)31L;
    ab_loop_bind_ = bottom_level;
  next_loop:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_1;
    goto next_loop_1;
  end_loop_2:
  end_1:
    level = level - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	tail = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		tail);
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_2) = head;
	M_CDR(gensymed_symbol_2) = tail;
	inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    skip_list = CDR(global_properties);
    key_value = Current_kb_specific_property_list_property_name;
    key_hash_value = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)31L;
    ab_loop_bind_ = bottom_level;
  next_loop_3:
    if (level < ab_loop_bind_)
	goto end_loop_3;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_4:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_4;
  end_loop_5:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_6:
	if (level < ab_loop_bind_)
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_7:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_7;
      end_loop_8:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
	kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	skip_list = CDR(global_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_9:
	if (level < ab_loop_bind_)
	    goto end_loop_9;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_10:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_10;
      end_loop_11:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_9;
      end_loop_9:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    default_text_box_colors = 
	    ISVREF(get_slot_description_of_class_description_function(Qdefault_text_box_colors_for_class,
	    gensymed_symbol,Nil),(SI_Long)6L);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
    temp_1 = assq_function(Qborder_color,default_text_box_colors);
    specified_border_color_qm = CDR(temp_1);
    temp_1 = assq_function(Qline_color,default_text_box_colors);
    specified_text_color_qm = CDR(temp_1);
    temp_1 = assq_function(Qbackground_color,default_text_box_colors);
    specified_background_color_qm = CDR(temp_1);
    if (specified_border_color_qm)
	temp = frame_list_2(Qborder_color,specified_border_color_qm);
    else {
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path);
      next_loop_12:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_12;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_13:
	    if (level < ab_loop_bind_)
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_14:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_15:
	    if ( !TRUEP(marked))
		goto end_loop_14;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_15;
	  end_loop_14:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_14;
	  end_loop_15:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_13;
	  end_loop_13:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_16:
	    if (level < ab_loop_bind_)
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_17:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_18:
	    if ( !TRUEP(marked))
		goto end_loop_17;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_18;
	  end_loop_17:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_17;
	  end_loop_18:
	  end_6:
	    level = level - (SI_Long)1L;
	    goto next_loop_16;
	  end_loop_16:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_19:
		if (level < ab_loop_bind_)
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_20:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_21:
		if ( !TRUEP(marked))
		    goto end_loop_20;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_21;
	      end_loop_20:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_20;
	      end_loop_21:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_19;
	      end_loop_19:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_22:
		if (level < ab_loop_bind_)
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_23:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_24:
		if ( !TRUEP(marked))
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_24;
	      end_loop_23:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_23;
	      end_loop_24:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_22;
	      end_loop_22:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_25:
	    if (level < ab_loop_bind_)
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_26:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_27:
	    if ( !TRUEP(marked))
		goto end_loop_26;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_27;
	  end_loop_26:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_26;
	  end_loop_27:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_25;
	  end_loop_25:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_28:
	    if (level < ab_loop_bind_)
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_29:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_30:
	    if ( !TRUEP(marked))
		goto end_loop_29;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_30;
	  end_loop_29:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_10;
	    goto next_loop_29;
	  end_loop_30:
	  end_10:
	    level = level - (SI_Long)1L;
	    goto next_loop_28;
	  end_loop_28:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_31:
		if (level < ab_loop_bind_)
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_32:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_33:
		if ( !TRUEP(marked))
		    goto end_loop_32;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_33;
	      end_loop_32:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_32;
	      end_loop_33:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_31;
	      end_loop_31:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_34:
		if (level < ab_loop_bind_)
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_35:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_36:
		if ( !TRUEP(marked))
		    goto end_loop_35;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_36;
	      end_loop_35:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_12;
		goto next_loop_35;
	      end_loop_36:
	      end_12:
		level = level - (SI_Long)1L;
		goto next_loop_34;
	      end_loop_34:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = assq_function(Qborder_color,
		    ISVREF(get_slot_description_of_class_description_function(Qdefault_text_box_colors_for_class,
		    gensymed_symbol,Nil),(SI_Long)6L));
	    superior_specified_border_color_qm = CDR(temp_1);
	    if (superior_specified_border_color_qm) {
		temp = frame_list_2(Qborder_color,
			superior_specified_border_color_qm);
		goto end_13;
	    }
	}
	goto next_loop_12;
      end_loop_12:
	temp = Qnil;
      end_13:;
    }
    if (specified_text_color_qm)
	temp_3 = frame_list_2(Qline_color,specified_text_color_qm);
    else {
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path);
      next_loop_37:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_37;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_38:
	    if (level < ab_loop_bind_)
		goto end_loop_38;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_39:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_40:
	    if ( !TRUEP(marked))
		goto end_loop_39;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_40;
	  end_loop_39:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_14;
	    goto next_loop_39;
	  end_loop_40:
	  end_14:
	    level = level - (SI_Long)1L;
	    goto next_loop_38;
	  end_loop_38:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp_3 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_3,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_41:
	    if (level < ab_loop_bind_)
		goto end_loop_41;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_42:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_43:
	    if ( !TRUEP(marked))
		goto end_loop_42;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_43;
	  end_loop_42:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_15;
	    goto next_loop_42;
	  end_loop_43:
	  end_15:
	    level = level - (SI_Long)1L;
	    goto next_loop_41;
	  end_loop_41:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_44:
		if (level < ab_loop_bind_)
		    goto end_loop_44;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_45:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_46:
		if ( !TRUEP(marked))
		    goto end_loop_45;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_46;
	      end_loop_45:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_16;
		goto next_loop_45;
	      end_loop_46:
	      end_16:
		level = level - (SI_Long)1L;
		goto next_loop_44;
	      end_loop_44:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_47:
		if (level < ab_loop_bind_)
		    goto end_loop_47;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_48:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_49:
		if ( !TRUEP(marked))
		    goto end_loop_48;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_49;
	      end_loop_48:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_17;
		goto next_loop_48;
	      end_loop_49:
	      end_17:
		level = level - (SI_Long)1L;
		goto next_loop_47;
	      end_loop_47:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_50:
	    if (level < ab_loop_bind_)
		goto end_loop_50;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_51:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_52:
	    if ( !TRUEP(marked))
		goto end_loop_51;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_52;
	  end_loop_51:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_18;
	    goto next_loop_51;
	  end_loop_52:
	  end_18:
	    level = level - (SI_Long)1L;
	    goto next_loop_50;
	  end_loop_50:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp_3 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_3,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_53:
	    if (level < ab_loop_bind_)
		goto end_loop_53;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_54:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_55:
	    if ( !TRUEP(marked))
		goto end_loop_54;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_55;
	  end_loop_54:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_19;
	    goto next_loop_54;
	  end_loop_55:
	  end_19:
	    level = level - (SI_Long)1L;
	    goto next_loop_53;
	  end_loop_53:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_56:
		if (level < ab_loop_bind_)
		    goto end_loop_56;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_57:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_58:
		if ( !TRUEP(marked))
		    goto end_loop_57;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_58;
	      end_loop_57:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_20;
		goto next_loop_57;
	      end_loop_58:
	      end_20:
		level = level - (SI_Long)1L;
		goto next_loop_56;
	      end_loop_56:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_59:
		if (level < ab_loop_bind_)
		    goto end_loop_59;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_60:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_61:
		if ( !TRUEP(marked))
		    goto end_loop_60;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_61;
	      end_loop_60:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_21;
		goto next_loop_60;
	      end_loop_61:
	      end_21:
		level = level - (SI_Long)1L;
		goto next_loop_59;
	      end_loop_59:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = assq_function(Qline_color,
		    ISVREF(get_slot_description_of_class_description_function(Qdefault_text_box_colors_for_class,
		    gensymed_symbol,Nil),(SI_Long)6L));
	    superior_specified_text_color_qm = CDR(temp_1);
	    if (superior_specified_text_color_qm) {
		temp_3 = frame_list_2(Qline_color,
			superior_specified_text_color_qm);
		goto end_22;
	    }
	}
	goto next_loop_37;
      end_loop_37:
	temp_3 = Qnil;
      end_22:;
    }
    if (specified_background_color_qm)
	temp_1 = frame_list_2(Qbackground_color,specified_background_color_qm);
    else {
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path);
      next_loop_62:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_62;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_63:
	    if (level < ab_loop_bind_)
		goto end_loop_63;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_64:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_65:
	    if ( !TRUEP(marked))
		goto end_loop_64;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_65;
	  end_loop_64:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_23;
	    goto next_loop_64;
	  end_loop_65:
	  end_23:
	    level = level - (SI_Long)1L;
	    goto next_loop_63;
	  end_loop_63:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp_4 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_4,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_66:
	    if (level < ab_loop_bind_)
		goto end_loop_66;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_67:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_68:
	    if ( !TRUEP(marked))
		goto end_loop_67;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_68;
	  end_loop_67:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_24;
	    goto next_loop_67;
	  end_loop_68:
	  end_24:
	    level = level - (SI_Long)1L;
	    goto next_loop_66;
	  end_loop_66:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_69:
		if (level < ab_loop_bind_)
		    goto end_loop_69;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_70:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_71:
		if ( !TRUEP(marked))
		    goto end_loop_70;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_71;
	      end_loop_70:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_25;
		goto next_loop_70;
	      end_loop_71:
	      end_25:
		level = level - (SI_Long)1L;
		goto next_loop_69;
	      end_loop_69:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_72:
		if (level < ab_loop_bind_)
		    goto end_loop_72;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_73:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_74:
		if ( !TRUEP(marked))
		    goto end_loop_73;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_74;
	      end_loop_73:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_26;
		goto next_loop_73;
	      end_loop_74:
	      end_26:
		level = level - (SI_Long)1L;
		goto next_loop_72;
	      end_loop_72:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_75:
	    if (level < ab_loop_bind_)
		goto end_loop_75;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_76:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_77:
	    if ( !TRUEP(marked))
		goto end_loop_76;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_77;
	  end_loop_76:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_27;
	    goto next_loop_76;
	  end_loop_77:
	  end_27:
	    level = level - (SI_Long)1L;
	    goto next_loop_75;
	  end_loop_75:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp_4 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_4,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_78:
	    if (level < ab_loop_bind_)
		goto end_loop_78;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_79:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_80:
	    if ( !TRUEP(marked))
		goto end_loop_79;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_80;
	  end_loop_79:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_28;
	    goto next_loop_79;
	  end_loop_80:
	  end_28:
	    level = level - (SI_Long)1L;
	    goto next_loop_78;
	  end_loop_78:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_81:
		if (level < ab_loop_bind_)
		    goto end_loop_81;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_82:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_83:
		if ( !TRUEP(marked))
		    goto end_loop_82;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_83;
	      end_loop_82:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_29;
		goto next_loop_82;
	      end_loop_83:
	      end_29:
		level = level - (SI_Long)1L;
		goto next_loop_81;
	      end_loop_81:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_84:
		if (level < ab_loop_bind_)
		    goto end_loop_84;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_85:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_86:
		if ( !TRUEP(marked))
		    goto end_loop_85;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_86;
	      end_loop_85:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_30;
		goto next_loop_85;
	      end_loop_86:
	      end_30:
		level = level - (SI_Long)1L;
		goto next_loop_84;
	      end_loop_84:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = assq_function(Qbackground_color,
		    ISVREF(get_slot_description_of_class_description_function(Qdefault_text_box_colors_for_class,
		    gensymed_symbol,Nil),(SI_Long)6L));
	    superior_specified_background_color_qm = CDR(temp_1);
	    if (superior_specified_background_color_qm) {
		temp_1 = frame_list_2(Qbackground_color,
			superior_specified_background_color_qm);
		goto end_31;
	    }
	}
	goto next_loop_62;
      end_loop_62:
	temp_1 = Qnil;
      end_31:;
    }
    plist_init_form_qm = nconc2(temp,nconc2(temp_3,temp_1));
    if (plist_init_form_qm) {
	if (called_from_alter_inheritance_qm) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = Qtext_box;
	    key_hash_value = SXHASH_SYMBOL_1(Qtext_box) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_87:
	    if (level < ab_loop_bind_)
		goto end_loop_87;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_88:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_89:
	    if ( !TRUEP(marked))
		goto end_loop_88;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_89;
	  end_loop_88:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_32;
	    goto next_loop_88;
	  end_loop_89:
	  end_32:
	    level = level - (SI_Long)1L;
	    goto next_loop_87;
	  end_loop_87:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qtext_box;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_90:
	    if (level < ab_loop_bind_)
		goto end_loop_90;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_91:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_92:
	    if ( !TRUEP(marked))
		goto end_loop_91;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_92;
	  end_loop_91:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_33;
	    goto next_loop_91;
	  end_loop_92:
	  end_33:
	    level = level - (SI_Long)1L;
	    goto next_loop_90;
	  end_loop_90:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_93:
		if (level < ab_loop_bind_)
		    goto end_loop_93;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_94:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_95:
		if ( !TRUEP(marked))
		    goto end_loop_94;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_95;
	      end_loop_94:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_34;
		goto next_loop_94;
	      end_loop_95:
	      end_34:
		level = level - (SI_Long)1L;
		goto next_loop_93;
	      end_loop_93:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_96:
		if (level < ab_loop_bind_)
		    goto end_loop_96;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_97:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_98:
		if ( !TRUEP(marked))
		    goto end_loop_97;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_98;
	      end_loop_97:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_35;
		goto next_loop_97;
	      end_loop_98:
	      end_35:
		level = level - (SI_Long)1L;
		goto next_loop_96;
	      end_loop_96:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    plist_slot_description_from_text_box_class = 
		    get_slot_description_of_class_description_function(Qtext_cell_plist_for_text_box,
		    gensymed_symbol,Nil);
	    new_slot_description = make_slot_description(8,
		    Qtext_cell_plist_for_text_box,Qtext_box,class_1,Nil,
		    plist_init_form_qm,
		    ISVREF(plist_slot_description_from_text_box_class,
		    (SI_Long)7L),Nil,
		    ISVREF(plist_slot_description_from_text_box_class,
		    (SI_Long)9L));
	    reclaim_frame_list_1(plist_init_form_qm);
	    return VALUES_1(new_slot_description);
	}
	else {
	    current_drawing_priority = Kdraw_as_late_as_possible;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		    1);
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      instance = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		ab_loopvar_ = collect_subclasses(class_1);
	      next_loop_99:
		if ( !TRUEP(ab_loopvar__1)) {
		  next_loop_100:
		    if ( !TRUEP(ab_loopvar_))
			goto end_loop_99;
		    ab_loopvar__1 = 
			    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			    Instances_specific_to_this_class_kbprop);
		    ab_loopvar_ = M_CDR(ab_loopvar_);
		    if (ab_loopvar__1)
			goto end_loop_99;
		    goto next_loop_100;
		  end_loop_99:
		    temp_2 =  !TRUEP(ab_loopvar__1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    goto end_loop_100;
		instance = ab_loopvar__1;
		ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		update_images_of_block(instance,T,T);
		goto next_loop_99;
	      end_loop_100:;
	      POP_SPECIAL();
	      plist_slot_description = get_slot_description(2,
		      Qtext_cell_plist_for_text_box,
		      ISVREF(class_description,(SI_Long)6L));
	      temp_1 = ISVREF(plist_slot_description,(SI_Long)6L);
	      if ( !EQUAL(plist_init_form_qm,temp_1))
		  update_slot_description(class_1,plist_slot_description,
			  Nil,plist_init_form_qm,
			  ISVREF(plist_slot_description,(SI_Long)9L),Nil,Nil);
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      instance = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		ab_loopvar_ = collect_subclasses(class_1);
	      next_loop_101:
		if ( !TRUEP(ab_loopvar__1)) {
		  next_loop_102:
		    if ( !TRUEP(ab_loopvar_))
			goto end_loop_101;
		    ab_loopvar__1 = 
			    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			    Instances_specific_to_this_class_kbprop);
		    ab_loopvar_ = M_CDR(ab_loopvar_);
		    if (ab_loopvar__1)
			goto end_loop_101;
		    goto next_loop_102;
		  end_loop_101:
		    temp_2 =  !TRUEP(ab_loopvar__1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    goto end_loop_102;
		instance = ab_loopvar__1;
		ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		update_images_of_block(instance,Nil,T);
		goto next_loop_101;
	      end_loop_102:;
	      POP_SPECIAL();
	      result = reclaim_frame_list_1(plist_init_form_qm);
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-FOR-TEXT-BOX */
Object initialize_for_text_box(text_box)
    Object text_box;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(109,36);
    frame = text_box;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtext_box)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    if (ISVREF(text_box,(SI_Long)16L))
	return reformat_text_box_in_place(1,text_box);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_text_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_text_box_spots, Qchain_of_available_text_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Text_box_spot_count, Qtext_box_spot_count);

Object Chain_of_available_text_box_spots_vector = UNBOUND;

/* TEXT-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object text_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(109,37);
    temp = Text_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEXT-BOX-SPOT-COUNT */
Object outstanding_text_box_spot_count()
{
    Object def_structure_text_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,38);
    gensymed_symbol = IFIX(Text_box_spot_count);
    def_structure_text_box_spot_variable = Chain_of_available_text_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_text_box_spot_variable))
	goto end_loop;
    def_structure_text_box_spot_variable = 
	    ISVREF(def_structure_text_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEXT-BOX-SPOT-1 */
Object reclaim_text_box_spot_1(text_box_spot)
    Object text_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(109,39);
    inline_note_reclaim_cons(text_box_spot,Nil);
    structure_being_reclaimed = text_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(text_box_spot,(SI_Long)2L));
      SVREF(text_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_text_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(text_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_text_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = text_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-BOX-SPOT */
Object reclaim_structure_for_text_box_spot(text_box_spot)
    Object text_box_spot;
{
    x_note_fn_call(109,40);
    return reclaim_text_box_spot_1(text_box_spot);
}

static Object Qg2_defstruct_structure_name_text_box_spot_g2_struct;  /* g2-defstruct-structure-name::text-box-spot-g2-struct */

/* MAKE-PERMANENT-TEXT-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_text_box_spot_structure_internal()
{
    Object def_structure_text_box_spot_variable;
    Object defstruct_g2_text_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(109,41);
    def_structure_text_box_spot_variable = Nil;
    atomic_incff_symval(Qtext_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_text_box_spot_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_text_box_spot_variable = the_array;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_box_spot_g2_struct;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_text_box_spot_variable,FIX((SI_Long)15L)) = Nil;
	def_structure_text_box_spot_variable = 
		defstruct_g2_text_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_text_box_spot_variable);
}

/* MAKE-TEXT-BOX-SPOT-1 */
Object make_text_box_spot_1()
{
    Object def_structure_text_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(109,42);
    def_structure_text_box_spot_variable = 
	    ISVREF(Chain_of_available_text_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_text_box_spot_variable) {
	svref_arg_1 = Chain_of_available_text_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_text_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_box_spot_g2_struct;
    }
    else
	def_structure_text_box_spot_variable = 
		make_permanent_text_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_text_box_spot_variable,Nil);
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_text_box_spot_variable,(SI_Long)6L) = 
	    FIX((SI_Long)1000L);
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)8L)) = Kunknown;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_text_box_spot_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_text_box_spot_variable);
}

/* GENERATE-SPOT-FOR-TEXT-BOX */
Object generate_spot_for_text_box(text_box,mouse_pointer)
    Object text_box, mouse_pointer;
{
    x_note_fn_call(109,43);
    return generate_text_box_spot(text_box,mouse_pointer,
	    make_text_box_spot_1());
}

/* GENERATE-TEXT-BOX-SPOT */
Object generate_text_box_spot(text_box,mouse_pointer,text_box_spot)
    Object text_box, mouse_pointer, text_box_spot;
{
    Object temp;

    x_note_fn_call(109,44);
    temp = ISVREF(text_box,(SI_Long)16L);
    fill_out_text_spot(text_box_spot,text_box,mouse_pointer,CDR(temp),
	    ISVREF(text_box,(SI_Long)17L),ISVREF(text_box,(SI_Long)18L));
    return push_last_spot(mouse_pointer,text_box_spot,text_box);
}

/* PUT-BOX-TRANSLATION-AND-TEXT */
Object put_box_translation_and_text(text_box,box_translation_and_text,
	    initializing_qm)
    Object text_box, box_translation_and_text, initializing_qm;
{
    Object gensymed_symbol, subblocks, confine_updating_to_block_rectangle_qm;
    Object stored_value, do_not_reclaim_old_value_qm, condition;
    Object current_drawing_priority, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,45);
    gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    if ( !(subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks)))) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	confine_updating_to_block_rectangle_qm =  !TRUEP(gensymed_symbol) ?
		 T : Nil;
    }
    else
	confine_updating_to_block_rectangle_qm = Nil;
    stored_value = Nil;
    do_not_reclaim_old_value_qm = Nil;
    if ( !TRUEP(initializing_qm)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	condition = gensymed_symbol;
    }
    else
	condition = Nil;
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    0);
      if (condition)
	  update_images_of_block(text_box,T,
		  confine_updating_to_block_rectangle_qm);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(text_box,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)16L),(SI_Long)1L);
      gensymed_symbol_1 = text_box;
      gensymed_symbol_2 = box_translation_and_text;
      gensymed_symbol_3 = initializing_qm;
      result = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	      gensymed_symbol_2,gensymed_symbol_3);
      MVS_2(result,stored_value,do_not_reclaim_old_value_qm);
      if ( !TRUEP(initializing_qm))
	  reformat_text_box_in_place(1,text_box);
      if (condition)
	  update_images_of_block(text_box,Nil,
		  confine_updating_to_block_rectangle_qm);
    POP_SPECIAL();
    return VALUES_2(stored_value,do_not_reclaim_old_value_qm);
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-TEXT-BOX */
Object put_box_translation_and_text_slot_value_for_text_box(text_box,
	    box_translation_and_text,initializing_qm)
    Object text_box, box_translation_and_text, initializing_qm;
{
    x_note_fn_call(109,46);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_box,Qbox_translation_and_text);
    return VALUES_2(SVREF(text_box,FIX((SI_Long)16L)) = 
	    box_translation_and_text,Nil);
}

static Object Qhighlight_color;    /* highlight-color */

/* PUT-TEXT-CELL-PLIST-FOR-TEXT-BOX */
Object put_text_cell_plist_for_text_box(text_box,value,initializing_qm)
    Object text_box, value, initializing_qm;
{
    x_note_fn_call(109,47);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_box,Qtext_cell_plist_for_text_box);
    SVREF(text_box,FIX((SI_Long)18L)) = value;
    if (initializing_qm)
	change_text_box_property(text_box,Qhighlight_color,Nil);
    return VALUES_1(ISVREF(text_box,(SI_Long)18L));
}

/* CHANGE-TEXT-BOX-PROPERTY */
Object change_text_box_property(text_box,indicator,value_qm)
    Object text_box, indicator, value_qm;
{
    Object class_description, slot_description, slot_init_form;
    Object text_cell_plist_for_text_box, l_trailer_qm, l, temp;

    x_note_fn_call(109,48);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_box,Qtext_cell_plist_for_text_box);
    class_description = ISVREF(text_box,(SI_Long)1L);
    slot_description = 
	    get_slot_description_of_class_description_function(Qtext_cell_plist_for_text_box,
	    class_description,Nil);
    slot_init_form = ISVREF(slot_description,(SI_Long)6L);
    text_cell_plist_for_text_box = ISVREF(text_box,(SI_Long)18L);
    if (text_cell_plist_for_text_box && EQ(slot_init_form,
	    text_cell_plist_for_text_box)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(text_box,Qtext_cell_plist_for_text_box);
	text_cell_plist_for_text_box = 
		copy_for_slot_value(text_cell_plist_for_text_box);
	SVREF(text_box,FIX((SI_Long)18L)) = text_cell_plist_for_text_box;
    }
    l_trailer_qm = Nil;
    l = text_cell_plist_for_text_box;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (EQ(CAR(l),indicator)) {
	if (value_qm)
	    M_CADR(l) = value_qm;
	else {
	    if (l_trailer_qm) {
		temp = CDDR(l);
		M_CDR(l_trailer_qm) = temp;
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(text_box,
			    Qtext_cell_plist_for_text_box);
		temp = CDDR(l);
		SVREF(text_box,FIX((SI_Long)18L)) = temp;
	    }
	    M_CDDR(l) = Nil;
	    reclaim_slot_value_list_1(l);
	}
	return VALUES_1(value_qm);
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop;
  end_loop:
    if (value_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(text_box,Qtext_cell_plist_for_text_box);
	temp = slot_value_cons_1(indicator,slot_value_cons_1(value_qm,
		ISVREF(text_box,(SI_Long)18L)));
	SVREF(text_box,FIX((SI_Long)18L)) = temp;
    }
    return VALUES_1(value_qm);
    return VALUES_1(Qnil);
}

/* TEXT-CELL-LINE-HEIGHT-FUNCTION */
Object text_cell_line_height_function(format_1)
    Object format_1;
{
    Object temp;

    x_note_fn_call(109,49);
    temp = ISVREF(format_1,(SI_Long)31L);
    return VALUES_1(temp);
}

/* RECLAIM-TEXT-CELL-FONT-MAP-VALUE */
Object reclaim_text_cell_font_map_value(value,frame)
    Object value, frame;
{
    Object icp_port, index_1, ab_loop_list_, temp, index_space, vector_1;
    SI_Long index_2;

    x_note_fn_call(109,50);
    icp_port = Nil;
    index_1 = Nil;
    ab_loop_list_ = 
	    getf(Plist_of_corresponding_icp_object_maps_for_font_maps, 
	    !TRUEP(CDR(value)) ? CAR(value) : value,_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    icp_port = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    index_1 = CAR(temp);
    index_space = ISVREF(icp_port,(SI_Long)8L);
    vector_1 = ISVREF(index_space,(SI_Long)2L);
    index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil;
    index_2 = IFIX(index_1) & (SI_Long)1023L;
    if (EQ(value,vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil)) {
	reclaim_icp_object_map_for_font_map(value);
	goto end_1;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
  end_1:;
    reclaim_slot_value(value);
    return VALUES_1(Nil);
}

/* TEXT-CELL-FIRST-FONT */
Object text_cell_first_font(text_box_format)
    Object text_box_format;
{
    Object temp;

    x_note_fn_call(109,51);
    temp = ISVREF(text_box_format,(SI_Long)22L);
    return VALUES_1(FIRST(temp));
}

static Object Qtext_alignment;     /* text-alignment */

static Object Qleft;               /* left */

static Object Qjustified;          /* justified */

/* GET-TEXT-CELL-LINE-JUSTIFICATION */
Object get_text_cell_line_justification(text_box_format,text_cell_plist)
    Object text_box_format, text_cell_plist;
{
    Object list_1, alignment_override_qm, temp;

    x_note_fn_call(109,52);
    list_1 = text_cell_plist;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qtext_alignment))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    alignment_override_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (alignment_override_qm)
	temp = EQ(alignment_override_qm,Qleft) ? Nil : alignment_override_qm;
    else {
	temp = ISVREF(text_box_format,(SI_Long)39L);
	if (temp);
	else
	    temp = ISVREF(text_box_format,(SI_Long)40L) ? Qjustified : Nil;
    }
    return VALUES_1(temp);
}

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

static Object Qformat_description;  /* format-description */

static Object Qtext_cell_line_quadding_qm;  /* text-cell-line-quadding? */

static Object Qtext_cell_lines_justified_qm;  /* text-cell-lines-justified? */

/* GET-BACKING-STORE-DEFAULT-TEXT-CELL-LINE-JUSTIFICATION */
Object get_backing_store_default_text_cell_line_justification(text_box_subclass)
    Object text_box_subclass;
{
    Object format_name, format_description, temp;

    x_note_fn_call(109,53);
    format_name = get_slot_init_form(2,Qdefault_text_box_format_name,
	    text_box_subclass);
    format_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name),
	    Qformat_description);
    temp = getfq_function_no_default(format_description,
	    Qtext_cell_line_quadding_qm);
    if (temp);
    else
	temp = getfq_function_no_default(format_description,
		Qtext_cell_lines_justified_qm) ? Qjustified : Nil;
    return VALUES_1(temp);
}

/* GET-DEFAULT-TEXT-CELL-LINE-JUSTIFICATION */
Object get_default_text_cell_line_justification(text_box_subclass)
    Object text_box_subclass;
{
    Object init_form, temp;

    x_note_fn_call(109,54);
    init_form = get_slot_init_form(2,text_box_subclass,
	    Qtext_cell_plist_for_text_box);
    temp = init_form ? getfq_function_no_default(init_form,
	    Qtext_alignment) : Nil;
    if (temp);
    else
	temp = 
		get_backing_store_default_text_cell_line_justification(text_box_subclass);
    return VALUES_1(temp);
}

static Object list_constant_9;     /* # */

static Object string_constant_3;   /* "The obsolete font ~A, used in the just-read kb, has been changed to ~A.  ~
				    *                     Do a save to make this change permanent."
				    */

static Object Qformat_change_qm;   /* format-change? */

static Object Qtext_cell_font_map;  /* text-cell-font-map */

/* PUT-TEXT-CELL-FONT-MAP */
Object put_text_cell_font_map(text_box_format,font_map,gensymed_symbol)
    Object text_box_format, font_map, gensymed_symbol;
{
    Object l, substitute_ab_font_name_qm, temp;

    x_note_fn_call(109,55);
    if (Loading_kb_p) {
	l = font_map;
	substitute_ab_font_name_qm = Nil;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	temp = assq_function(CAR(l),list_constant_9);
	substitute_ab_font_name_qm = CDR(temp);
	if (substitute_ab_font_name_qm) {
	    notify_user(3,string_constant_3,CAR(l),substitute_ab_font_name_qm);
	    M_CAR(l) = substitute_ab_font_name_qm;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(text_box_format,Qformat_change_qm);
	    set_lookup_slot_value_1(text_box_format,Qformat_change_qm,
		    FIX((SI_Long)0L));
	}
	l = M_CDR(l);
	goto next_loop;
      end_loop:;
    }
    return set_slot_value_function(text_box_format,Qtext_cell_font_map,
	    font_map,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_draw_methods_for_text_box_formats, Qpost_draw_methods_for_text_box_formats);

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

/* TEXT-VISIBLE-P */
Object text_visible_p(text_box_format,text_cell_plist,x_scale,y_scale)
    Object text_box_format, text_cell_plist, x_scale, y_scale;
{
    Object x_magnification_qm, y_magnification_qm, magnified_x_scale;
    Object magnified_y_scale, scale, value, temp_1, temp_2;
    SI_Long unshifted_result;
    char temp;

    x_note_fn_call(109,56);
    temp = TRUEP(Nil);
    if (temp);
    else {
	x_magnification_qm = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,
		Qx_magnification) : Nil;
	if (x_magnification_qm);
	else
	    x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
	y_magnification_qm = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,
		Qy_magnification) : Nil;
	if (y_magnification_qm);
	else
	    y_magnification_qm = ISVREF(text_box_format,(SI_Long)26L);
	magnified_x_scale = x_magnification_qm ? 
		FIX(IFIX(FIXNUM_TIMES(x_scale,x_magnification_qm)) + 
		(SI_Long)128L >>  -  - (SI_Long)8L) : x_scale;
	magnified_y_scale = y_magnification_qm ? 
		FIX(IFIX(FIXNUM_TIMES(y_scale,y_magnification_qm)) + 
		(SI_Long)128L >>  -  - (SI_Long)8L) : y_scale;
	scale = FIXNUM_MIN(magnified_x_scale,magnified_y_scale);
	value = ISVREF(text_box_format,(SI_Long)31L);
	if (IFIX(scale) == (SI_Long)4096L)
	    temp_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(scale,value);
	temp_2 = FIX((SI_Long)6L);
	temp = NUM_LT(temp_1,temp_2);
    }
    return VALUES_1( !temp ? T : Nil);
}

static Object Kwithout_text;       /* :without-text */

static Object Qworkspace;          /* workspace */

static Object Kjust_text;          /* :just-text */

/* TEXT-BOX-VISIBLE-P */
Object text_box_visible_p(text_box,x_scale,y_scale)
    Object text_box, x_scale, y_scale;
{
    Object text_box_format, text_cell_plist, text_visible_qm, gensymed_symbol;
    Object frame, symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(109,57);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
    text_visible_qm = text_visible_p(text_box_format,text_cell_plist,
	    x_scale,y_scale);
    if (IFIX(ISVREF(text_box_format,(SI_Long)44L)) > (SI_Long)0L || 
	    IFIX(ISVREF(text_box_format,(SI_Long)45L)) > (SI_Long)0L || 
	    IFIX(ISVREF(text_box_format,(SI_Long)46L)) > (SI_Long)0L || 
	    IFIX(ISVREF(text_box_format,(SI_Long)47L)) > (SI_Long)0L || 
	    ISVREF(text_box_format,(SI_Long)24L) || getf(text_cell_plist,
	    Qbackground_color,_) || getf(text_cell_plist,Qhighlight_color,_)) {
	if (text_visible_qm)
	    return VALUES_1(T);
	else
	    return VALUES_1(Kwithout_text);
    }
    else {
	temp = TRUEP(text_visible_qm);
	if (temp);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp =  !TRUEP(gensymed_symbol);
	    if (temp);
	    else {
		gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		frame = gensymed_symbol;
		symbol = Qworkspace;
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	}
	if (temp)
	    return VALUES_1(Kjust_text);
	else
	    return VALUES_1(Nil);
    }
}

/* TEXT-BOX-HAS-BORDER-P */
Object text_box_has_border_p(text_box)
    Object text_box;
{
    Object text_box_format, temp;

    x_note_fn_call(109,58);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    temp = IFIX(ISVREF(text_box_format,(SI_Long)44L)) > (SI_Long)0L ? T : Nil;
    if (temp);
    else
	temp = IFIX(ISVREF(text_box_format,(SI_Long)45L)) > (SI_Long)0L ? 
		T : Nil;
    if (temp);
    else
	temp = IFIX(ISVREF(text_box_format,(SI_Long)46L)) > (SI_Long)0L ? 
		T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(IFIX(ISVREF(text_box_format,(SI_Long)47L)) > 
		(SI_Long)0L ? T : Nil);
}

Object Minimum_magnification_for_text_boxes = UNBOUND;

Object Maximum_magnification_for_text_boxes = UNBOUND;

Object Maximum_text_box_width_or_height = UNBOUND;

static Object Qline_width;         /* line-width */

static Object Qword_spacing;       /* word-spacing */

/* COMPUTE-WIDTH-OF-LONGEST-LINE */
Object compute_width_of_longest_line varargs_1(int, n)
{
    Object text_segment, text_box_format, text_cell_plist;
    Object put_in_indentations_and_widths_qm;
    Object text_tail_past_text_segment_qm, word_spacing, x_magnification_qm;
    Object width_of_longest_line_so_far, indentation, line_width_qm;
    Object indentation_qm, l, next_l, text_element, line_width, temp;
    Object unmagnified_line_width, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,59);
    INIT_ARGS_nonrelocating();
    text_segment = REQUIRED_ARG_nonrelocating();
    text_box_format = REQUIRED_ARG_nonrelocating();
    text_cell_plist = REQUIRED_ARG_nonrelocating();
    put_in_indentations_and_widths_qm = REQUIRED_ARG_nonrelocating();
    text_tail_past_text_segment_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    word_spacing = ISVREF(text_box_format,(SI_Long)34L);
    x_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qx_magnification) : Nil;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
    width_of_longest_line_so_far = FIX((SI_Long)0L);
    indentation = FIX((SI_Long)0L);
    line_width_qm = Nil;
    indentation_qm = Nil;
    l = text_segment;
    next_l = Nil;
    text_element = Nil;
  next_loop:
    next_l = CDR(l);
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	line_width = line_width_qm;
	if (line_width);
	else {
	    temp = indentation;
	    unmagnified_line_width = FIXNUM_ADD(temp,
		    compute_width_of_text_line(5,text_element,Nil,Nil,
		    ISVREF(text_box_format,(SI_Long)22L),word_spacing));
	    line_width = x_magnification_qm ? 
		    FIX(IFIX(FIXNUM_TIMES(unmagnified_line_width,
		    x_magnification_qm)) + (SI_Long)128L >>  -  - 
		    (SI_Long)8L) : unmagnified_line_width;
	}
	if (FIXNUM_GT(line_width,width_of_longest_line_so_far))
	    width_of_longest_line_so_far = line_width;
	if (line_width_qm)
	    line_width_qm = Nil;
	else if (put_in_indentations_and_widths_qm) {
	    temp_1 = slot_value_cons_1(text_element,CDR(l));
	    M_CDR(l) = temp_1;
	    temp_1 = slot_value_cons_1(Qline_width,line_width);
	    M_CAR(l) = temp_1;
	}
	if (indentation_qm)
	    indentation_qm = Nil;
	else if (put_in_indentations_and_widths_qm) {
	    temp_1 = slot_value_cons_1(CAR(l),CDR(l));
	    M_CDR(l) = temp_1;
	    M_CAR(l) = indentation;
	}
    }
    else if (FIXNUMP(text_element)) {
	indentation_qm = text_element;
	indentation = indentation_qm;
    }
    else if (CONSP(text_element)) {
	temp = CAR(text_element);
	if (EQ(temp,Qline_width))
	    line_width_qm = CDR(text_element);
	else if (EQ(temp,Qword_spacing))
	    word_spacing = CDR(text_element);
    }
    if ( !TRUEP(next_l) || EQ(next_l,text_tail_past_text_segment_qm))
	goto end_loop;
    l = next_l;
    goto next_loop;
  end_loop:
    return VALUES_1(width_of_longest_line_so_far);
    return VALUES_1(Qnil);
}

/* COMPUTE-HEIGHT-FOR-TEXT */
Object compute_height_for_text(text,text_box_format,text_cell_plist)
    Object text, text_box_format, text_cell_plist;
{
    Object temp;

    x_note_fn_call(109,60);
    temp = ISVREF(text_box_format,(SI_Long)28L);
    temp = FIXNUM_ADD(temp,compute_height_for_text_without_margins(text,
	    text_box_format,text_cell_plist));
    temp = FIXNUM_ADD(temp,ISVREF(text_box_format,(SI_Long)30L));
    return VALUES_1(temp);
}

static Object Qleading;            /* leading */

/* COMPUTE-HEIGHT-FOR-TEXT-WITHOUT-MARGINS */
Object compute_height_for_text_without_margins(text,text_box_format,
	    text_cell_plist)
    Object text, text_box_format, text_cell_plist;
{
    Object y_magnification_qm, line_height, line_spacing;
    Object height_of_text_so_far, first_line_qm, text_element, ab_loop_list_;
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,61);
    y_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qy_magnification) : Nil;
    if (y_magnification_qm);
    else
	y_magnification_qm = ISVREF(text_box_format,(SI_Long)26L);
    line_height = ISVREF(text_box_format,(SI_Long)31L);
    line_spacing = ISVREF(text_box_format,(SI_Long)33L);
    height_of_text_so_far = FIX((SI_Long)0L);
    first_line_qm = T;
    text_element = Nil;
    ab_loop_list_ = text;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	gensymed_symbol = IFIX(height_of_text_so_far);
	gensymed_symbol_1 = first_line_qm ? IFIX(line_height) : 
		IFIX(FIXNUM_ADD(line_height,line_spacing));
	height_of_text_so_far = FIX(gensymed_symbol + gensymed_symbol_1);
	first_line_qm = Nil;
    }
    else if (CONSP(text_element) && EQ(CAR(text_element),Qleading))
	height_of_text_so_far = FIXNUM_ADD(height_of_text_so_far,
		CDR(text_element));
    goto next_loop;
  end_loop:
    temp = y_magnification_qm ? 
	    FIX(IFIX(FIXNUM_TIMES(height_of_text_so_far,
	    y_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) : 
	    height_of_text_so_far;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-EXTENT-OF-TEXT-STRING-AFTER-FORMATTING */
Object get_extent_of_text_string_after_formatting(text_string,
	    text_cell_format,text_cell_plist,format_width_override_qm)
    Object text_string, text_cell_format, text_cell_plist;
    Object format_width_override_qm;
{
    Object text;

    x_note_fn_call(109,62);
    text = convert_text_string_to_text(copy_text_string(text_string));
    return get_extent_of_text_after_formatting(text,text_cell_format,
	    text_cell_plist,format_width_override_qm);
}

/* GET-EXTENT-OF-TEXT-AFTER-FORMATTING */
Object get_extent_of_text_after_formatting(text,text_cell_format,
	    text_cell_plist,format_width_override_qm)
    Object text, text_cell_format, text_cell_plist, format_width_override_qm;
{
    x_note_fn_call(109,63);
    return get_extent_of_text(text,text_cell_format,text_cell_plist,
	    format_width_override_qm,Nil);
}

/* GET-EXTENT-OF-FORMATTED-TEXT */
Object get_extent_of_formatted_text(text,text_cell_format,text_cell_plist,
	    format_width_override_qm)
    Object text, text_cell_format, text_cell_plist, format_width_override_qm;
{
    x_note_fn_call(109,64);
    return get_extent_of_text(text,text_cell_format,text_cell_plist,
	    format_width_override_qm,T);
}

/* GET-EXTENT-OF-TEXT */
Object get_extent_of_text(text,text_cell_format,text_cell_plist,
	    format_width_override_qm,do_not_reformat_text_qm)
    Object text, text_cell_format, text_cell_plist, format_width_override_qm;
    Object do_not_reformat_text_qm;
{
    Object formatted_text, width, height;
    Object result;

    x_note_fn_call(109,65);
    result = format_text(12,text,text_cell_format,text_cell_plist,Nil,
	    do_not_reformat_text_qm,Nil,Nil,Nil,Nil,Nil,
	    format_width_override_qm,Nil);
    MVS_2(result,formatted_text,width);
    height = compute_height_for_text_without_margins(formatted_text,
	    text_cell_format,text_cell_plist);
    reclaim_text(formatted_text);
    return VALUES_2(width,height);
}

/* TRUNCATE-STRING-AS-NECESSARY-TO-FIT */
Object truncate_string_as_necessary_to_fit(string_1,maximum_width,font_map,
	    word_spacing,truncated_string_suffix_qm)
    Object string_1, maximum_width, font_map, word_spacing;
    Object truncated_string_suffix_qm;
{
    Object width_of_string, temp, text_x_a, text_x_b, width_so_far, i, next_i;
    Object gensymed_symbol, new_string, gensymed_symbol_2, source_string;
    Object source_end, destination_string, destination_start;
    SI_Long incff_1_arg, text_x_a_new_value, gensymed_symbol_1, arg, arg_1;
    SI_Long arg_2, gensymed_symbol_3, gensymed_symbol_4, source_start;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,66);
    PUSH_SPECIAL_WITH_SYMBOL(Maximum_width,Qmaximum_width,maximum_width,0);
      width_of_string = compute_width_of_text_line(5,string_1,Nil,Nil,
	      font_map,word_spacing);
      if (FIXNUM_LE(width_of_string,Maximum_width)) {
	  temp = copy_text_string(string_1);
	  result = VALUES_2(temp,width_of_string);
      }
      else {
	  text_x_a = Nil;
	  text_x_b = Nil;
	  width_so_far = Nil;
	  i = FIX((SI_Long)0L);
	  next_i = Nil;
	  text_x_a = FIX((SI_Long)0L);
	  text_x_b = FIX((SI_Long)128L);
	  if (truncated_string_suffix_qm) {
	      temp = text_x_b;
	      gensymed_symbol = FIXNUM_ADD(temp,
		      compute_width_of_text_line(6,
		      truncated_string_suffix_qm,Nil,Nil,font_map,
		      word_spacing,T));
	      incff_1_arg = IFIX(gensymed_symbol) >>  -  - (SI_Long)8L;
	      text_x_a_new_value = IFIX(text_x_a) + incff_1_arg;
	      text_x_a = FIX(text_x_a_new_value);
	      gensymed_symbol_1 = IFIX(gensymed_symbol) & (SI_Long)255L;
	      text_x_b = FIX(gensymed_symbol_1);
	  }
	next_loop:
	  next_i = i;
	  width_so_far = text_x_a;
	  next_i = FIXNUM_ADD1(next_i);
	  temp = text_x_b;
	  gensymed_symbol = FIXNUM_ADD(temp,compute_width_of_text_line(6,
		  string_1,i,next_i,font_map,word_spacing,T));
	  incff_1_arg = IFIX(gensymed_symbol) >>  -  - (SI_Long)8L;
	  text_x_a_new_value = IFIX(text_x_a) + incff_1_arg;
	  text_x_a = FIX(text_x_a_new_value);
	  gensymed_symbol_1 = IFIX(gensymed_symbol) & (SI_Long)255L;
	  text_x_b = FIX(gensymed_symbol_1);
	  if (FIXNUM_GT(text_x_a,Maximum_width))
	      goto end_loop;
	  i = next_i;
	  goto next_loop;
	end_loop:
	  if (IFIX(i) > (SI_Long)0L) {
	      if (truncated_string_suffix_qm) {
		  temp = i;
		  temp = FIXNUM_ADD(temp,
			  text_string_length(truncated_string_suffix_qm));
	      }
	      else
		  temp = i;
	      new_string = obtain_text_string(temp);
	      if (EQ(string_1,new_string)) {
		  if ((SI_Long)0L == IFIX(i))
		      temp_1 = TRUEP(T);
		  else {
		      temp_1 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
			      IFIX(i) : TRUEP(Qnil);
		      if (temp_1);
		      else {
			  arg = (SI_Long)0L;
			  arg_1 = (SI_Long)0L;
			  arg_2 = (SI_Long)0L + (IFIX(i) - (SI_Long)0L);
			  temp_1 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		      }
		      if (temp_1) {
			  copy_byte_vector_16_portion_carefully(string_1,
				  FIX((SI_Long)0L),new_string,
				  FIX((SI_Long)0L),FIX(IFIX(i) - (SI_Long)0L));
			  temp_1 = TRUEP(T);
		      }
		      else
			  temp_1 = TRUEP(Qnil);
		  }
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1);
	      else {
		  gensymed_symbol = string_1;
		  gensymed_symbol_1 = (SI_Long)0L;
		  gensymed_symbol_2 = new_string;
		  gensymed_symbol_3 = (SI_Long)0L;
		  gensymed_symbol_4 = IFIX(i) - (SI_Long)0L;
		  INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			  gensymed_symbol_1,
			  UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			  gensymed_symbol_3,gensymed_symbol_4);
	      }
	      if (truncated_string_suffix_qm) {
		  source_string = truncated_string_suffix_qm;
		  source_start = (SI_Long)0L;
		  source_end = text_string_length(truncated_string_suffix_qm);
		  destination_string = new_string;
		  destination_start = i;
		  if (EQ(source_string,destination_string)) {
		      if (source_start == IFIX(source_end))
			  temp_1 = TRUEP(T);
		      else {
			  temp_1 = source_start < IFIX(destination_start) ?
				   FIXNUM_LT(destination_start,source_end) 
				  : TRUEP(Qnil);
			  if (temp_1);
			  else {
			      arg = IFIX(destination_start);
			      arg_1 = source_start;
			      arg_2 = IFIX(destination_start) + 
				      (IFIX(source_end) - source_start);
			      temp_1 = arg < arg_1 ? arg_1 < arg_2 : 
				      TRUEP(Qnil);
			  }
			  if (temp_1) {
			      copy_byte_vector_16_portion_carefully(source_string,
				      FIX(source_start),destination_string,
				      destination_start,
				      FIX(IFIX(source_end) - source_start));
			      temp_1 = TRUEP(T);
			  }
			  else
			      temp_1 = TRUEP(Qnil);
		      }
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1);
		  else {
		      gensymed_symbol = source_string;
		      gensymed_symbol_1 = source_start;
		      gensymed_symbol_2 = destination_string;
		      gensymed_symbol_3 = IFIX(destination_start);
		      gensymed_symbol_4 = IFIX(source_end) - source_start;
		      INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			      gensymed_symbol_1,
			      UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			      gensymed_symbol_3,gensymed_symbol_4);
		  }
	      }
	      result = VALUES_2(new_string,width_so_far);
	  }
	  else
	      result = VALUES_1(Nil);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
      }
    POP_SPECIAL();
    return result;
}

static Object Qminimum_width_of_text_box;  /* minimum-width-of-text-box */

static Object Qmaximum_width_of_text_box_qm;  /* maximum-width-of-text-box? */

static Object Qminimum_height_of_text_box;  /* minimum-height-of-text-box */

static Object Qmaximum_height_of_text_box;  /* maximum-height-of-text-box */

/* REFORMAT-TEXT-BOX-IN-PLACE */
Object reformat_text_box_in_place varargs_1(int, n)
{
    Object text_box;
    Object put_in_indentations_and_widths_qm, do_not_reformat_text_qm;
    Object cursor_line_index_qm, cursor_character_index_qm;
    Object do_not_enlarge_workspace_qm, gensymed_symbol, subblocks;
    Object text_box_format, temp, text_qm, formatted_text;
    Object width_of_longest_line, new_cursor_line_index_qm;
    Object new_cursor_character_index_qm, cdr_arg, new_right_qm, new_bottom_qm;
    Object temp_1, new_width_for_text_cell_1, new_width_for_text_cell;
    Object new_width_for_text_box_1, new_width_for_text_box, top_edge_of_block;
    Object minimum_height_of_text_box, maximum_height_of_text_box;
    Object text_box_top_border_width, minimum_height_for_text_cell;
    Object height_for_text, text_box_bottom_border_width, x;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,67);
    INIT_ARGS_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    put_in_indentations_and_widths_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_reformat_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_enlarge_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks)))
	delete_any_text_regions(1,text_box);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    temp = ISVREF(text_box,(SI_Long)16L);
    text_qm = CDR(temp);
    if (text_qm && text_box_format) {
	temp = ISVREF(text_box,(SI_Long)18L);
	result = format_text(11,text_qm,text_box_format,temp,Nil,
		do_not_reformat_text_qm,Nil,
		put_in_indentations_and_widths_qm,Nil,cursor_line_index_qm,
		cursor_character_index_qm,get_lookup_slot_value(text_box,
		Qminimum_width_of_text_box));
	MVS_4(result,formatted_text,width_of_longest_line,
		new_cursor_line_index_qm,new_cursor_character_index_qm);
	cdr_arg = ISVREF(text_box,(SI_Long)16L);
	M_CDR(cdr_arg) = formatted_text;
	new_right_qm = Nil;
	new_bottom_qm = Nil;
	temp_1 = ISVREF(text_box_format,(SI_Long)49L);
	temp = FIXNUM_ADD(FIXNUM_ADD(ISVREF(text_box_format,(SI_Long)27L),
		width_of_longest_line),ISVREF(text_box_format,(SI_Long)29L));
	new_width_for_text_cell_1 = FIXNUM_MAX(temp_1,temp);
	new_width_for_text_cell = Nil ? FIXNUM_MAX(Nil,
		new_width_for_text_cell_1) : new_width_for_text_cell_1;
	temp_1 = get_lookup_slot_value(text_box,Qminimum_width_of_text_box);
	temp = FIXNUM_ADD(FIXNUM_ADD(ISVREF(text_box_format,(SI_Long)44L),
		new_width_for_text_cell),ISVREF(text_box_format,(SI_Long)46L));
	new_width_for_text_box_1 = FIXNUM_MAX(temp_1,temp);
	if (get_lookup_slot_value_given_default(text_box,
		Qmaximum_width_of_text_box_qm,Nil)) {
	    temp = get_lookup_slot_value_given_default(text_box,
		    Qmaximum_width_of_text_box_qm,Nil);
	    new_width_for_text_box = FIXNUM_MIN(temp,new_width_for_text_box_1);
	}
	else
	    new_width_for_text_box = new_width_for_text_box_1;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(new_width_for_text_box);
	new_right_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	top_edge_of_block = gensymed_symbol;
	minimum_height_of_text_box = get_lookup_slot_value(text_box,
		Qminimum_height_of_text_box);
	maximum_height_of_text_box = 
		get_lookup_slot_value_given_default(text_box,
		Qmaximum_height_of_text_box,FIX((SI_Long)4194303L));
	text_box_top_border_width = ISVREF(text_box_format,(SI_Long)45L);
	minimum_height_for_text_cell = ISVREF(text_box_format,(SI_Long)50L);
	height_for_text = compute_height_for_text(formatted_text,
		text_box_format,ISVREF(text_box,(SI_Long)18L));
	text_box_bottom_border_width = ISVREF(text_box_format,(SI_Long)47L);
	gensymed_symbol_1 = IFIX(top_edge_of_block);
	x = FIXNUM_ADD(FIXNUM_ADD(text_box_top_border_width,
		FIXNUM_MAX(minimum_height_for_text_cell,height_for_text)),
		text_box_bottom_border_width);
	gensymed_symbol_2 = FIXNUM_LE(x,minimum_height_of_text_box) ? 
		IFIX(minimum_height_of_text_box) : 
		FIXNUM_LE(maximum_height_of_text_box,x) ? 
		IFIX(maximum_height_of_text_box) : IFIX(x);
	new_bottom_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	change_edges_of_block(text_box,Nil,Nil,new_right_qm,new_bottom_qm);
	if ( !TRUEP(do_not_enlarge_workspace_qm))
	    enlarge_workspace_for_block_rectangle_if_necessary(text_box,Nil);
	return VALUES_3(text_box,new_cursor_line_index_qm,
		new_cursor_character_index_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Kxor;                /* :xor */

/* UPDATE-BORDER-OF-TEXT-BOX */
Object update_border_of_text_box(text_box,new_left_edge_qm,new_top_edge_qm,
	    new_right_edge_qm,new_bottom_edge_qm)
    Object text_box, new_left_edge_qm, new_top_edge_qm, new_right_edge_qm;
    Object new_bottom_edge_qm;
{
    Object text_box_format, count_1, number_of_edges_changing, gensymed_symbol;
    Object old_left_edge, old_top_edge, old_right_edge, old_bottom_edge;
    Object new_left_edge, new_top_edge, new_right_edge, new_bottom_edge;
    Object left_edge_of_update_area, top_edge_of_update_area;
    Object right_edge_of_update_area, bottom_edge_of_update_area;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3, temp_4, temp_5;
    Object current_draw_document_p;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(109,68);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    count_1 = FIX((SI_Long)0L);
    if (new_left_edge_qm)
	count_1 = FIXNUM_ADD1(count_1);
    if (new_top_edge_qm)
	count_1 = FIXNUM_ADD1(count_1);
    if (new_right_edge_qm)
	count_1 = FIXNUM_ADD1(count_1);
    if (new_bottom_edge_qm)
	count_1 = FIXNUM_ADD1(count_1);
    number_of_edges_changing = count_1;
    if ( !((SI_Long)0L == IFIX(number_of_edges_changing))) {
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	old_left_edge = gensymed_symbol;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	old_top_edge = gensymed_symbol;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	old_right_edge = gensymed_symbol;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	old_bottom_edge = gensymed_symbol;
	new_left_edge = new_left_edge_qm;
	if (new_left_edge);
	else
	    new_left_edge = old_left_edge;
	new_top_edge = new_top_edge_qm;
	if (new_top_edge);
	else
	    new_top_edge = old_top_edge;
	new_right_edge = new_right_edge_qm;
	if (new_right_edge);
	else
	    new_right_edge = old_right_edge;
	new_bottom_edge = new_bottom_edge_qm;
	if (new_bottom_edge);
	else
	    new_bottom_edge = old_bottom_edge;
	left_edge_of_update_area = FIXNUM_MIN(new_left_edge,old_left_edge);
	top_edge_of_update_area = FIXNUM_MIN(new_top_edge,old_top_edge);
	right_edge_of_update_area = FIXNUM_MAX(new_right_edge,old_right_edge);
	bottom_edge_of_update_area = FIXNUM_MAX(new_bottom_edge,
		old_bottom_edge);
	if ((SI_Long)1L == IFIX(number_of_edges_changing)) {
	    if (new_right_edge_qm) {
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_right_edge_qm);
		gensymed_symbol_1 = MIN(gensymed_symbol_1,gensymed_symbol_2);
		gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
		left_edge_of_update_area = FIX(gensymed_symbol_1 - 
			gensymed_symbol_2);
	    }
	    else if (new_bottom_edge_qm) {
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_bottom_edge_qm);
		gensymed_symbol_1 = MIN(gensymed_symbol_1,gensymed_symbol_2);
		gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
		top_edge_of_update_area = FIX(gensymed_symbol_1 - 
			gensymed_symbol_2);
	    }
	    else if (new_left_edge_qm) {
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_left_edge_qm);
		gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
		gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
		right_edge_of_update_area = FIX(gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	    else if (new_top_edge_qm) {
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_top_edge_qm);
		gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
		gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
		bottom_edge_of_update_area = FIX(gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	}
	update_images_of_border_of_text_box(text_box,T,
		left_edge_of_update_area,top_edge_of_update_area,
		right_edge_of_update_area,bottom_edge_of_update_area);
	gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Text_region_class_description,(SI_Long)18L));
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
	if (temp) {
	    temp_1 = subblock;
	    if (new_left_edge_qm) {
		gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_left_edge_qm);
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    }
	    else
		temp_2 = Nil;
	    if (new_top_edge_qm) {
		gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_top_edge_qm);
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		temp_3 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    }
	    else
		temp_3 = Nil;
	    if (new_right_edge_qm) {
		gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_right_edge_qm);
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		temp_4 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    }
	    else
		temp_4 = Nil;
	    if (new_bottom_edge_qm) {
		gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(new_bottom_edge_qm);
		gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		temp_5 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    }
	    else
		temp_5 = Nil;
	    change_edges_of_block(temp_1,temp_2,temp_3,temp_4,temp_5);
	}
	goto next_loop;
      end_loop:;
	change_edges_of_block(text_box,new_left_edge_qm,new_top_edge_qm,
		new_right_edge_qm,new_bottom_edge_qm);
	current_draw_document_p = EQ(Current_drawing_transfer_mode,Kxor) ? 
		Nil : Current_draw_document_p;
	PUSH_SPECIAL_WITH_SYMBOL(Current_draw_document_p,Qcurrent_draw_document_p,current_draw_document_p,
		0);
	  enlarge_workspace_for_block_rectangle_if_necessary(text_box,Nil);
	POP_SPECIAL();
	return update_images_of_border_of_text_box(text_box,Nil,
		left_edge_of_update_area,top_edge_of_update_area,
		right_edge_of_update_area,bottom_edge_of_update_area);
    }
    else
	return VALUES_1(Nil);
}

static Object Kbleeding_on_all_sides;  /* :bleeding-on-all-sides */

static Object Qdraw_or_change_color_of_text_box;  /* draw-or-change-color-of-text-box */

static Object Qdraw_only_borders;  /* draw-only-borders */

/* UPDATE-IMAGES-OF-BORDER-OF-TEXT-BOX */
Object update_images_of_border_of_text_box(text_box,erase_qm,
	    left_edge_of_update_area_qm,top_edge_of_update_area_qm,
	    right_edge_of_update_area_qm,bottom_edge_of_update_area_qm)
    Object text_box, erase_qm, left_edge_of_update_area_qm;
    Object top_edge_of_update_area_qm, right_edge_of_update_area_qm;
    Object bottom_edge_of_update_area_qm;
{
    Object temp, gensymed_symbol, temp_1, temp_2, temp_3;

    x_note_fn_call(109,69);
    temp = left_edge_of_update_area_qm;
    if (temp);
    else {
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
    }
    temp_1 = top_edge_of_update_area_qm;
    if (temp_1);
    else {
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp_1 = gensymed_symbol;
    }
    temp_2 = right_edge_of_update_area_qm;
    if (temp_2);
    else {
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp_2 = gensymed_symbol;
    }
    temp_3 = bottom_edge_of_update_area_qm;
    if (temp_3);
    else {
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp_3 = gensymed_symbol;
    }
    return update_images(15,erase_qm,text_box,text_box,temp,temp_1,temp_2,
	    temp_3,Kbleeding_on_all_sides,
	    Qdraw_or_change_color_of_text_box,text_box,Qdraw_only_borders,
	    Nil,Nil,Nil,Nil);
}

static Object Qfree;               /* free */

static Object Qfree_text_attribute;  /* free-text-attribute */

/* INCOMPLETE-BOX-TRANSLATION-AND-TEXT-P */
Object incomplete_box_translation_and_text_p(text_box)
    Object text_box;
{
    Object temp, text, type_of_slot;

    x_note_fn_call(109,70);
    temp = ISVREF(text_box,(SI_Long)16L);
    text = CDR(temp);
    type_of_slot = assq_function(Qtype,
	    ISVREF(get_slot_description_of_class_description_function(Qbox_translation_and_text,
	    ISVREF(text_box,(SI_Long)1L),Nil),(SI_Long)9L));
    if (EQ(CADR(type_of_slot),Qfree) || EQ(CADR(type_of_slot),
	    Qfree_text_attribute)) {
	temp = text_incomplete_p(text);
	if (temp)
	    return VALUES_1(temp);
	else
	    return text_empty_p(text);
    }
    else
	return text_incomplete_p(text);
}

Object Default_text_cell_background_color = UNBOUND;

static Object Qforeground;         /* foreground */

static Object Qtext_highlight_bar_color;  /* text-highlight-bar-color */

static Object Qend;                /* end */

static Object Kno_change;          /* :no-change */

static Object Qhighlight;          /* highlight */

/* HIGHLIGHT-OR-UNHIGHLIGHT-TEXT-BOX */
Object highlight_or_unhighlight_text_box varargs_1(int, n)
{
    Object text_box, highlight_color_qm, unhighlight_case_qm;
    Object text_region_class_qm, highlight_color, text_cell_plist;
    Object text_cell_format, table, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector;
    Object old_highlight_color_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,71);
    INIT_ARGS_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    highlight_color_qm = REQUIRED_ARG_nonrelocating();
    unhighlight_case_qm = REQUIRED_ARG_nonrelocating();
    text_region_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    highlight_color = highlight_color_qm;
    if (highlight_color);
    else {
	text_cell_plist = ISVREF(text_box,(SI_Long)18L);
	text_cell_format = ISVREF(text_box,(SI_Long)17L);
	table = Nil;
	highlight_color = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,Qline_color) : Nil;
	if (highlight_color);
	else
	    highlight_color = ISVREF(text_cell_format,(SI_Long)23L);
	if (highlight_color);
	else
	    highlight_color = Qforeground;
    }
    if (text_region_class_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(text_region_class_qm,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
		    (SI_Long)18L));
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
	if (temp) {
	    if (unhighlight_case_qm) {
		delete_frame(subblock);
		return VALUES_1(T);
	    }
	    else if (EQ(get_slot_value_function(subblock,
		    Qtext_highlight_bar_color,Nil),highlight_color))
		return VALUES_1(Nil);
	    else {
		delete_frame(subblock);
		goto end_loop;
	    }
	}
	goto next_loop;
      end_loop:
	if ( !TRUEP(unhighlight_case_qm))
	    return make_text_region(8,text_box,Nil,FIX((SI_Long)1L),
		    FIX((SI_Long)0L),Qend,Nil,Nil,text_region_class_qm);
	return VALUES_1(Qnil);
    }
    else {
	old_highlight_color_qm = getf(ISVREF(text_box,(SI_Long)18L),
		Qhighlight_color,_);
	if (unhighlight_case_qm ? TRUEP(old_highlight_color_qm) :  
		!EQ(old_highlight_color_qm,highlight_color))
	    return change_color_of_text_box(6,text_box,Nil, 
		    !TRUEP(unhighlight_case_qm) ? highlight_color : Nil,
		    Kno_change,Kno_change,Qhighlight);
	else
	    return VALUES_1(Nil);
    }
}

Object Scheduled_text_highlighting = UNBOUND;

static Object Qblack;              /* black */

static Object Qtransparent;        /* transparent */

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qtext_box_color_pattern;  /* text-box-color-pattern */

static Object Qbackground;         /* background */

static Object Qtext;               /* text */

static Object Qborder;             /* border */

/* CHANGE-COLOR-OF-TEXT-BOX */
Object change_color_of_text_box varargs_1(int, n)
{
    Object text_box, note_as_kb_state_change_qm, new_background_color_qm;
    Object new_border_color_qm, new_text_color_qm;
    Object color_change_case_qm, do_not_note_permanent_changes_p, workspace_qm;
    Object text_box_format, text_cell_plist, text_cell_format, table_qm;
    Object ignore_state_of_highlighting, old_background_color;
    Object new_background_color, new_background_color_really, table;
    Object old_border_color, new_border_color, old_text_color, new_text_color;
    Object becoming_transparent_qm, x2, temp_1, changed_regions;
    Object sub_class_bit_vector, changing_colors_of_graphic_elements_qm;
    Object current_drawing_transfer_mode, this_block, superblock_qm;
    Object gensymed_symbol_3, left, top, right, bottom, region;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, edge_overflow_if_any;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(109,72);
    INIT_ARGS_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    note_as_kb_state_change_qm = REQUIRED_ARG_nonrelocating();
    new_background_color_qm = REQUIRED_ARG_nonrelocating();
    new_border_color_qm = REQUIRED_ARG_nonrelocating();
    new_text_color_qm = REQUIRED_ARG_nonrelocating();
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    3);
      color_change_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : T;
      END_ARGS_nonrelocating();
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      2);
	workspace_qm = get_workspace_if_any(text_box);
	text_box_format = ISVREF(text_box,(SI_Long)17L);
	text_cell_plist = ISVREF(text_box,(SI_Long)18L);
	text_cell_format = ISVREF(text_box,(SI_Long)17L);
	table_qm = Nil;
	ignore_state_of_highlighting = Nil;
	if (text_cell_plist) {
	    old_background_color =  !TRUEP(ignore_state_of_highlighting) ? 
		    getfq_function_no_default(text_cell_plist,
		    Qhighlight_color) : Qnil;
	    if (old_background_color);
	    else
		old_background_color = 
			getfq_function_no_default(text_cell_plist,
			Qbackground_color);
	}
	else
	    old_background_color = Nil;
	if (old_background_color);
	else
	    old_background_color = ISVREF(text_cell_format,(SI_Long)24L);
	if (old_background_color);
	else
	    old_background_color = table_qm ? 
		    table_background_color(table_qm) : Nil;
	if (old_background_color);
	else
	    old_background_color = Default_text_cell_background_color;
	if (EQ(color_change_case_qm,Qhighlight))
	    new_background_color = new_background_color_qm;
	else if (EQ(new_background_color_qm,Kno_change))
	    new_background_color = Nil;
	else {
	    new_background_color = new_background_color_qm;
	    if (new_background_color);
	    else
		new_background_color = getf(ISVREF(text_box,(SI_Long)18L),
			Qhighlight_color,_);
	    if (new_background_color);
	    else
		new_background_color = ISVREF(text_box_format,(SI_Long)24L);
	    if (new_background_color);
	    else
		new_background_color = Default_text_cell_background_color;
	}
	new_background_color_really = new_background_color;
	if (new_background_color_really);
	else if (EQ(color_change_case_qm,Qhighlight)) {
	    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
	    text_cell_format = ISVREF(text_box,(SI_Long)17L);
	    table_qm = Nil;
	    ignore_state_of_highlighting = T;
	    if (text_cell_plist) {
		new_background_color_really =  
			!TRUEP(ignore_state_of_highlighting) ? 
			getfq_function_no_default(text_cell_plist,
			Qhighlight_color) : Qnil;
		if (new_background_color_really);
		else
		    new_background_color_really = 
			    getfq_function_no_default(text_cell_plist,
			    Qbackground_color);
	    }
	    else
		new_background_color_really = Nil;
	    if (new_background_color_really);
	    else
		new_background_color_really = ISVREF(text_cell_format,
			(SI_Long)24L);
	    if (new_background_color_really);
	    else
		new_background_color_really = table_qm ? 
			table_background_color(table_qm) : Nil;
	    if (new_background_color_really);
	    else
		new_background_color_really = 
			Default_text_cell_background_color;
	}
	else if (EQ(new_background_color_qm,Kno_change))
	    new_background_color_really = old_background_color;
	else
	    new_background_color_really = Qnil;
	text_cell_plist = ISVREF(text_box,(SI_Long)18L);
	text_cell_format = ISVREF(text_box,(SI_Long)17L);
	table = Nil;
	old_border_color = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,Qborder_color) : Nil;
	if (old_border_color);
	else
	    old_border_color = ISVREF(text_cell_format,(SI_Long)48L);
	if (old_border_color);
	else
	    old_border_color = Qforeground;
	if ( !EQ(new_border_color_qm,Kno_change)) {
	    new_border_color = new_border_color_qm;
	    if (new_border_color);
	    else
		new_border_color = ISVREF(text_box_format,(SI_Long)48L);
	    if (new_border_color);
	    else
		new_border_color = workspace_qm ? ISVREF(workspace_qm,
			(SI_Long)22L) : Nil;
	    if (new_border_color);
	    else
		new_border_color = Qblack;
	}
	else
	    new_border_color = Nil;
	text_cell_plist = ISVREF(text_box,(SI_Long)18L);
	text_cell_format = ISVREF(text_box,(SI_Long)17L);
	table = Nil;
	old_text_color = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,Qline_color) : Nil;
	if (old_text_color);
	else
	    old_text_color = ISVREF(text_cell_format,(SI_Long)23L);
	if (old_text_color);
	else
	    old_text_color = Qforeground;
	if ( !EQ(new_text_color_qm,Kno_change)) {
	    new_text_color = new_text_color_qm;
	    if (new_text_color);
	    else
		new_text_color = ISVREF(text_box_format,(SI_Long)23L);
	    if (new_text_color);
	    else
		new_text_color = workspace_qm ? ISVREF(workspace_qm,
			(SI_Long)22L) : Nil;
	    if (new_text_color);
	    else
		new_text_color = Qblack;
	}
	else
	    new_text_color = Nil;
	becoming_transparent_qm =  !EQ(new_background_color_qm,Kno_change) 
		&&  !EQ(new_background_color,old_background_color) ? 
		(EQ(new_background_color_really,Qtransparent) ? T : Nil) : 
		Qnil;
	if (becoming_transparent_qm);
	else
	    becoming_transparent_qm =  !EQ(new_border_color_qm,Kno_change) 
		    &&  !EQ(new_border_color,old_border_color) ? 
		    (EQ(new_border_color,Qtransparent) ? T : Nil) : Qnil;
	if (becoming_transparent_qm);
	else
	    becoming_transparent_qm =  !EQ(new_text_color_qm,Kno_change) 
		    &&  !EQ(new_text_color,old_text_color) ? 
		    (EQ(new_text_color,Qtransparent) ? T : Nil) : Qnil;
	if (EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) && 
		EQ(Current_drawing_priority,Kdraw_as_late_as_possible) &&  
		!TRUEP(becoming_transparent_qm)) {
	    if (SIMPLE_VECTOR_P(text_box) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(text_box,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !(temp ? (SI_Long)0L != (IFIX(ISVREF(text_box,
		    (SI_Long)5L)) & (SI_Long)1024L) : 
		    TRUEP(render_connection_in_xor_overlay_p_function(text_box)));
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? Scheduled_text_highlighting ||  
		!EQ(color_change_case_qm,Qhighlight) : TRUEP(Nil)) {
	    if (EQ(color_change_case_qm,Qhighlight))
		change_text_box_property(text_box,Qhighlight_color,
			new_background_color_qm);
	    else {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(text_box,Qtext_box_color_pattern);
		if (new_background_color)
		    change_text_box_property(text_box,Qbackground_color,
			    new_background_color_qm);
		if (new_border_color)
		    change_text_box_property(text_box,Qborder_color,
			    new_border_color_qm);
		if (new_text_color)
		    change_text_box_property(text_box,Qline_color,
			    new_text_color_qm);
	    }
	    if (workspace_qm) {
		temp_1 =  !EQ(new_background_color_qm,Kno_change) ? 
			gensym_cons_1(Qbackground,Nil) : Nil;
		changed_regions = nconc2(temp_1,nconc2( 
			!EQ(new_text_color_qm,Kno_change) ? 
			gensym_cons_1(Qtext,Nil) : Nil, 
			!EQ(new_border_color_qm,Kno_change) ? 
			gensym_cons_1(Qborder,Nil) : Nil));
		invalidate_color_of_block(workspace_qm,text_box,
			changed_regions);
		result = reclaim_gensym_list_1(changed_regions);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else if (EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) 
		&& becoming_transparent_qm) {
	    if (SIMPLE_VECTOR_P(text_box) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(text_box,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		redraw_transfer_representations_of_block(text_box,T);
	    if (EQ(color_change_case_qm,Qhighlight))
		temp_1 = change_text_box_property(text_box,
			Qhighlight_color,new_background_color_qm);
	    else {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(text_box,Qtext_box_color_pattern);
		if (new_background_color)
		    change_text_box_property(text_box,Qbackground_color,
			    new_background_color_qm);
		if (new_border_color)
		    change_text_box_property(text_box,Qborder_color,
			    new_border_color_qm);
		temp_1 = new_text_color ? 
			change_text_box_property(text_box,Qline_color,
			new_text_color_qm) : Nil;
	    }
	    if (SIMPLE_VECTOR_P(text_box) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(text_box,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		redraw_transfer_representations_of_block(text_box,Nil);
	    invalidate_region_for_block_or_connection(text_box);
	    result = VALUES_1(temp_1);
	}
	else {
	    if (SIMPLE_VECTOR_P(text_box) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(text_box,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(text_box,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    edge_overflow_if_any = temp ? (SI_Long)1L : (SI_Long)0L;
	    changing_colors_of_graphic_elements_qm = T;
	    current_drawing_transfer_mode = Current_drawing_transfer_mode;
	    if (SIMPLE_VECTOR_P(text_box) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(text_box,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		this_block = text_box;
		superblock_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(this_block,
			(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) 
			: Nil;
		superblock_qm = gensymed_symbol_3;
		if ( !TRUEP(superblock_qm)) {
		    sub_class_bit_vector = ISVREF(ISVREF(this_block,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Workspace_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    workspace_qm = temp ? this_block : Nil;
		    goto end_1;
		}
		this_block = superblock_qm;
		goto next_loop;
	      end_loop:
		workspace_qm = Qnil;
	      end_1:;
	    }
	    else
		workspace_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
		      0);
		if (SIMPLE_VECTOR_P(text_box) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
			(SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(text_box,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? (SI_Long)0L != (IFIX(ISVREF(text_box,
			(SI_Long)5L)) & (SI_Long)1024L) : 
			TRUEP(render_connection_in_xor_overlay_p_function(text_box)))
		    Current_drawing_transfer_mode = Kxor;
		result = local_edges_of_block_or_connection(text_box);
		MVS_4(result,left,top,right,bottom);
		update_images(15,Nil,text_box,text_box,left,top,
			FIX(IFIX(right) + edge_overflow_if_any),
			FIX(IFIX(bottom) + edge_overflow_if_any),Nil,
			Qdraw_or_change_color_of_text_box,text_box,Nil,
			color_change_case_qm,new_background_color,
			new_text_color,new_border_color);
		if (SIMPLE_VECTOR_P(text_box) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
			(SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(text_box,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    redraw_transfer_representations_of_block(text_box,T);
		if (EQ(color_change_case_qm,Qhighlight))
		    change_text_box_property(text_box,Qhighlight_color,
			    new_background_color_qm);
		else {
		    if (Note_as_kb_state_change_qm)
			note_kb_state_change(text_box,Qtext_box_color_pattern);
		    if (new_background_color)
			change_text_box_property(text_box,
				Qbackground_color,new_background_color_qm);
		    if (new_border_color)
			change_text_box_property(text_box,Qborder_color,
				new_border_color_qm);
		    if (new_text_color)
			change_text_box_property(text_box,Qline_color,
				new_text_color_qm);
		}
		if (SIMPLE_VECTOR_P(text_box) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
			(SI_Long)2L &&  !EQ(ISVREF(text_box,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(text_box,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    redraw_transfer_representations_of_block(text_box,Nil);
		if ( !EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor)) {
		    if (SIMPLE_VECTOR_P(text_box) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_box)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(text_box,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(text_box,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(text_box,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? TRUEP(workspace_qm) : TRUEP(Nil)) {
		    region = 
			    bounding_region_of_block_or_connection(get_ruling_for_meter(text_box));
		    invalidate_region_of_workspace(2,workspace_qm,region);
		    result = reclaim_region(region);
		}
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qselective_redraw;   /* selective-redraw */

/* DRAW-SELECTED-REGIONS-OF-TEXT-BOX */
Object draw_selected_regions_of_text_box(text_box,changed_regions)
    Object text_box, changed_regions;
{
    Object text_cell_plist, text_cell_format, table_qm;
    Object ignore_state_of_highlighting, background_color, table, border_color;
    Object text_color, gensymed_symbol, temp_1, temp_2;
    char temp;

    x_note_fn_call(109,73);
    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
    text_cell_format = ISVREF(text_box,(SI_Long)17L);
    table_qm = Nil;
    ignore_state_of_highlighting = Nil;
    if (text_cell_plist) {
	background_color =  !TRUEP(ignore_state_of_highlighting) ? 
		getfq_function_no_default(text_cell_plist,
		Qhighlight_color) : Qnil;
	if (background_color);
	else
	    background_color = getfq_function_no_default(text_cell_plist,
		    Qbackground_color);
    }
    else
	background_color = Nil;
    if (background_color);
    else
	background_color = ISVREF(text_cell_format,(SI_Long)24L);
    if (background_color);
    else
	background_color = table_qm ? table_background_color(table_qm) : Nil;
    if (background_color);
    else
	background_color = Default_text_cell_background_color;
    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
    text_cell_format = ISVREF(text_box,(SI_Long)17L);
    table = Nil;
    border_color = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qborder_color) : Nil;
    if (border_color);
    else
	border_color = ISVREF(text_cell_format,(SI_Long)48L);
    if (border_color);
    else
	border_color = Qforeground;
    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
    text_cell_format = ISVREF(text_box,(SI_Long)17L);
    table = Nil;
    text_color = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qline_color) : Nil;
    if (text_color);
    else
	text_color = ISVREF(text_cell_format,(SI_Long)23L);
    if (text_color);
    else
	text_color = Qforeground;
    gensymed_symbol = changed_regions;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    if (EQ(M_CAR(gensymed_symbol),Qbackground)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    temp_1 = temp ? background_color : Nil;
    gensymed_symbol = changed_regions;
  next_loop_1:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_1;
    if (EQ(M_CAR(gensymed_symbol),Qbackground)) {
	temp = TRUEP(gensymed_symbol);
	goto end_2;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_2:;
    if (temp);
    else {
	gensymed_symbol = changed_regions;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	if (EQ(M_CAR(gensymed_symbol),Qtext)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(Qnil);
      end_3:;
    }
    temp_2 = temp ? text_color : Nil;
    gensymed_symbol = changed_regions;
  next_loop_3:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_3;
    if (EQ(M_CAR(gensymed_symbol),Qborder)) {
	temp = TRUEP(gensymed_symbol);
	goto end_4;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_3;
  end_loop_3:
    temp = TRUEP(Qnil);
  end_4:;
    return draw_or_change_color_of_text_box(text_box,Nil,Qselective_redraw,
	    temp_1,temp_2,temp ? border_color : Nil);
}

/* DRAW-SELECTED-REGIONS-OF-BLOCK */
Object draw_selected_regions_of_block(block,regions)
    Object block, regions;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(109,74);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return draw_connection(ISVREF(block,(SI_Long)21L),Nil);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return draw_selected_regions_of_text_box(block,regions);
	else
	    return draw_selected_regions_of_icon(block,regions);
    }
}

/* DRAW-TEXT-FUNCTION */
Object draw_text_function(text,left_edge_of_cell_in_window,
	    top_edge_of_cell_in_window,right_edge_of_cell_in_window,
	    bottom_edge_of_cell_in_window)
    Object text, left_edge_of_cell_in_window, top_edge_of_cell_in_window;
    Object right_edge_of_cell_in_window, bottom_edge_of_cell_in_window;
{
    x_note_fn_call(109,75);
    return draw_text_segment_1(text,Nil,FIX((SI_Long)0L),
	    left_edge_of_cell_in_window,top_edge_of_cell_in_window,
	    right_edge_of_cell_in_window,bottom_edge_of_cell_in_window);
}

static Object Qadd_line_of_text;   /* add-line-of-text */

/* DRAW-TEXT-SEGMENT-1 */
Object draw_text_segment_1(text_segment,text_tail_past_text_segment_qm,
	    unmagnified_distance_of_text_segment_from_top,
	    left_edge_of_cell_in_window,top_edge_of_cell_in_window,
	    right_edge_of_cell_in_window,bottom_edge_of_cell_in_window)
    Object text_segment, text_tail_past_text_segment_qm;
    Object unmagnified_distance_of_text_segment_from_top;
    Object left_edge_of_cell_in_window, top_edge_of_cell_in_window;
    Object right_edge_of_cell_in_window, bottom_edge_of_cell_in_window;
{
    Object text_box_format, text_cell_plist, x_magnification_qm;
    Object y_magnification_qm, x_scale, y_scale, magnified_x_scale;
    Object magnified_y_scale, font_map, line_spacing, line_height;
    Object baseline_position, scale, value, left_edge_for_lines_in_window;
    Object distance_to_next_baseline_from_top, baseline_to_baseline_distance;
    Object extra_diacritic_height_in_window, extent_above_baseline_in_window;
    Object word_spacing, word_spacing_for_next_line_qm, baseline_in_window;
    Object text_element, text_segment_old_value, temp, left_edge_in_window;
    Object top_edge_in_window, right_edge_in_window, text_line, word_spacing_1;
    Object color_difference, left_edge_of_line_of_text_in_window;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left_edge_of_text_in_window, top_edge_of_text_in_window;
    SI_Long extra_diacritic_height, value_1, extent_below_baseline_in_window;
    SI_Long temp_1, bottom_edge_in_window, length_1, i, ab_loop_bind_;
    char temp_2;

    x_note_fn_call(109,76);
    text_box_format = Current_text_box_format;
    text_cell_plist = Current_text_cell_plist;
    x_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qx_magnification) : Nil;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
    y_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qy_magnification) : Nil;
    if (y_magnification_qm);
    else
	y_magnification_qm = ISVREF(text_box_format,(SI_Long)26L);
    x_scale = Current_image_x_scale;
    y_scale = Current_image_y_scale;
    magnified_x_scale = x_magnification_qm ? FIX(IFIX(FIXNUM_TIMES(x_scale,
	    x_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) : 
	    x_scale;
    magnified_y_scale = y_magnification_qm ? FIX(IFIX(FIXNUM_TIMES(y_scale,
	    y_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) : 
	    y_scale;
    font_map = ISVREF(text_box_format,(SI_Long)22L);
    line_spacing = ISVREF(text_box_format,(SI_Long)33L);
    line_height = ISVREF(text_box_format,(SI_Long)31L);
    baseline_position = ISVREF(text_box_format,(SI_Long)32L);
    gensymed_symbol = IFIX(left_edge_of_cell_in_window);
    scale = x_scale;
    value = ISVREF(text_box_format,(SI_Long)27L);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    left_edge_of_text_in_window = gensymed_symbol + gensymed_symbol_1;
    left_edge_for_lines_in_window = FIX(left_edge_of_text_in_window);
    gensymed_symbol = IFIX(top_edge_of_cell_in_window);
    scale = y_scale;
    value = ISVREF(text_box_format,(SI_Long)28L);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    top_edge_of_text_in_window = gensymed_symbol + gensymed_symbol_1;
    distance_to_next_baseline_from_top = 
	    FIXNUM_ADD(unmagnified_distance_of_text_segment_from_top,
	    baseline_position);
    baseline_to_baseline_distance = FIXNUM_ADD(line_height,line_spacing);
    extra_diacritic_height = IFIX(ISVREF(text_box_format,(SI_Long)31L)) >> 
	     -  - (SI_Long)2L;
    if (IFIX(magnified_y_scale) == (SI_Long)4096L)
	extra_diacritic_height_in_window = FIX(extra_diacritic_height);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    magnified_y_scale) && FIXNUM_LT(magnified_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    extra_diacritic_height && extra_diacritic_height < 
	    IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(magnified_y_scale) * 
		extra_diacritic_height + (SI_Long)2048L;
	extra_diacritic_height_in_window = FIX(unshifted_result >>  -  - 
		(SI_Long)12L);
    }
    else
	extra_diacritic_height_in_window = 
		scalef_function(magnified_y_scale,FIX(extra_diacritic_height));
    scale = magnified_y_scale;
    value_1 = (IFIX(line_spacing) >>  -  - (SI_Long)1L) + 
	    IFIX(baseline_position);
    if (IFIX(scale) == (SI_Long)4096L)
	extent_above_baseline_in_window = FIX(value_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
	    value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	extent_above_baseline_in_window = FIX(unshifted_result >>  -  - 
		(SI_Long)12L);
    }
    else
	extent_above_baseline_in_window = scalef_function(scale,FIX(value_1));
    if (IFIX(magnified_y_scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(baseline_to_baseline_distance);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    magnified_y_scale) && FIXNUM_LT(magnified_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    baseline_to_baseline_distance) && 
	    FIXNUM_LT(baseline_to_baseline_distance,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(magnified_y_scale,
		baseline_to_baseline_distance)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(magnified_y_scale,
		baseline_to_baseline_distance));
    gensymed_symbol_1 = IFIX(extent_above_baseline_in_window);
    extent_below_baseline_in_window = gensymed_symbol - gensymed_symbol_1;
    word_spacing = ISVREF(text_box_format,(SI_Long)34L);
    word_spacing_for_next_line_qm = Nil;
    baseline_in_window = Nil;
    text_element = Nil;
  next_loop:
    if (EQ(text_segment,text_tail_past_text_segment_qm))
	goto end_loop;
    text_segment_old_value = text_segment;
    temp = FIRST(text_segment_old_value);
    text_segment = REST(text_segment_old_value);
    text_element = temp;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	gensymed_symbol = top_edge_of_text_in_window;
	if (IFIX(magnified_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(distance_to_next_baseline_from_top);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		magnified_y_scale) && FIXNUM_LT(magnified_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		distance_to_next_baseline_from_top) && 
		FIXNUM_LT(distance_to_next_baseline_from_top,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(magnified_y_scale,
		    distance_to_next_baseline_from_top)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(magnified_y_scale,
		    distance_to_next_baseline_from_top));
	baseline_in_window = FIX(gensymed_symbol + gensymed_symbol_1);
	left_edge_in_window = left_edge_of_cell_in_window;
	temp = FIXNUM_MINUS(FIXNUM_MINUS(baseline_in_window,
		extent_above_baseline_in_window),
		extra_diacritic_height_in_window);
	top_edge_in_window = FIXNUM_MAX(temp,top_edge_of_cell_in_window);
	right_edge_in_window = right_edge_of_cell_in_window;
	temp_1 = IFIX(baseline_in_window) + extent_below_baseline_in_window;
	bottom_edge_in_window = MIN(temp_1,
		IFIX(bottom_edge_of_cell_in_window));
	text_line = text_element;
	temp = word_spacing_for_next_line_qm;
	if (temp);
	else
	    temp = word_spacing;
	word_spacing_1 = temp;
	color_difference = FIXNUM_LOGXOR(Current_foreground_color_value,
		Current_background_color_value);
	x_scale = magnified_x_scale;
	y_scale = magnified_y_scale;
	left_edge_of_line_of_text_in_window = left_edge_for_lines_in_window;
	length_1 = IFIX(text_string_length(text_line));
	i = (SI_Long)0L;
	ab_loop_bind_ = length_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (UBYTE_16_ISAREF_1(text_line,i) == (SI_Long)9L) {
	    temp_2 = TRUEP(T);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = TRUEP(Qnil);
      end_1:;
	if (temp_2)
	    draw_line_of_text_with_tabs(left_edge_in_window,
		    top_edge_in_window,right_edge_in_window,
		    FIX(bottom_edge_in_window),text_line,word_spacing_1,
		    font_map,color_difference,x_scale,y_scale,
		    left_edge_of_line_of_text_in_window,baseline_in_window);
	else
	    draw_graphic_element(13,Qadd_line_of_text,left_edge_in_window,
		    top_edge_in_window,right_edge_in_window,
		    FIX(bottom_edge_in_window),text_line,word_spacing_1,
		    font_map,color_difference,x_scale,y_scale,
		    left_edge_of_line_of_text_in_window,baseline_in_window);
	if (IFIX(baseline_in_window) + extent_below_baseline_in_window > 
		IFIX(Bottom_edge_of_draw_area))
	    goto end_loop;
	distance_to_next_baseline_from_top = 
		FIXNUM_ADD(distance_to_next_baseline_from_top,
		baseline_to_baseline_distance);
	word_spacing_for_next_line_qm = Nil;
    }
    else if (FIXNUMP(text_element)) {
	gensymed_symbol = left_edge_of_text_in_window;
	if (IFIX(magnified_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(text_element);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		magnified_x_scale) && FIXNUM_LT(magnified_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		text_element) && FIXNUM_LT(text_element,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(magnified_x_scale,
		    text_element)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(magnified_x_scale,
		    text_element));
	left_edge_for_lines_in_window = FIX(gensymed_symbol + 
		gensymed_symbol_1);
    }
    else if (SYMBOLP(text_element));
    else if (EQ(CAR(text_element),Qleading))
	distance_to_next_baseline_from_top = 
		FIXNUM_ADD(distance_to_next_baseline_from_top,
		CDR(text_element));
    else if (EQ(CAR(text_element),Qword_spacing))
	word_spacing_for_next_line_qm = CDR(text_element);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* DRAW-FOR-TEXT-BOX */
Object draw_for_text_box(text_box)
    Object text_box;
{
    x_note_fn_call(109,77);
    return draw_or_change_color_of_text_box(text_box,Nil,Nil,Nil,Nil,Nil);
}

static Object Qframe_transforms_of_block;  /* frame-transforms-of-block */

static Object list_constant_10;    /* # */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

/* DRAW-OR-CHANGE-COLOR-OF-TEXT-BOX */
Object draw_or_change_color_of_text_box(text_box,suppress_details_qm,
	    color_change_case_qm,highlight_or_new_background_color_qm,
	    new_text_color_qm,new_border_color_qm)
    Object text_box, suppress_details_qm, color_change_case_qm;
    Object highlight_or_new_background_color_qm, new_text_color_qm;
    Object new_border_color_qm;
{
    Object text_box_format, text_cell_plist, temp, text;
    Object ordinary_color_change_qm, text_cell_plist_1, text_cell_format;
    Object table, cell_border_color, existing_border_color, final_border_color;
    Object cell_text_color, left_border_width, top_border_width;
    Object right_border_width, bottom_border_width, suppress_text_drawing_qm;
    Object x_magnification_qm, y_magnification_qm, magnified_x_scale;
    Object magnified_y_scale, scale, value, temp_1, sub_class_bit_vector;
    Object gensymed_symbol_3, force_hairline_border_qm, frame, symbol, block_1;
    Object block_2, block, left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace, superblock_qm;
    Object ab_loop_it_, frame_transform_qm, right_edge_of_cell_in_window;
    Object bottom_edge_of_cell_in_window, image_x_scale_of_table;
    Object image_y_scale_of_table, unmagnified_width_of_text_to_draw_beyond_qm;
    Object color_value_1, color_value_2, border_color_difference;
    Object existing_border_color_value, old_color_value;
    Object current_background_color_value;
    SI_Long unshifted_result, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, left_edge_of_text_box_in_window;
    SI_Long top_edge_of_text_box_in_window, right_edge_of_text_box_in_window;
    SI_Long bottom_edge_of_text_box_in_window, left_edge_of_cell_in_window;
    SI_Long top_edge_of_cell_in_window;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(109,78);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_plist = ISVREF(text_box,(SI_Long)18L);
    temp = ISVREF(text_box,(SI_Long)16L);
    text = CDR(temp);
    ordinary_color_change_qm = EQ(color_change_case_qm,Qt) ? T : Nil;
    if (ordinary_color_change_qm);
    else
	ordinary_color_change_qm = EQ(color_change_case_qm,Qhighlight) ? T 
		: Nil;
    text_cell_plist_1 = ISVREF(text_box,(SI_Long)18L);
    text_cell_format = ISVREF(text_box,(SI_Long)17L);
    table = Nil;
    cell_border_color = text_cell_plist_1 ? 
	    getfq_function_no_default(text_cell_plist_1,Qborder_color) : Nil;
    if (cell_border_color);
    else
	cell_border_color = ISVREF(text_cell_format,(SI_Long)48L);
    if (cell_border_color);
    else
	cell_border_color = Qforeground;
    existing_border_color = ordinary_color_change_qm ? cell_border_color : 
	    Qbackground;
    final_border_color = ordinary_color_change_qm && new_border_color_qm ? 
	    new_border_color_qm : cell_border_color;
    text_cell_plist_1 = ISVREF(text_box,(SI_Long)18L);
    text_cell_format = ISVREF(text_box,(SI_Long)17L);
    table = Nil;
    cell_text_color = text_cell_plist_1 ? 
	    getfq_function_no_default(text_cell_plist_1,Qline_color) : Nil;
    if (cell_text_color);
    else
	cell_text_color = ISVREF(text_cell_format,(SI_Long)23L);
    if (cell_text_color);
    else
	cell_text_color = Qforeground;
    left_border_width = ISVREF(text_box_format,(SI_Long)44L);
    top_border_width = ISVREF(text_box_format,(SI_Long)45L);
    right_border_width = ISVREF(text_box_format,(SI_Long)46L);
    bottom_border_width = ISVREF(text_box_format,(SI_Long)47L);
    suppress_text_drawing_qm = suppress_details_qm;
    if (suppress_text_drawing_qm);
    else
	suppress_text_drawing_qm = Nil;
    if (suppress_text_drawing_qm);
    else {
	x_magnification_qm = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,
		Qx_magnification) : Nil;
	if (x_magnification_qm);
	else
	    x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
	y_magnification_qm = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,
		Qy_magnification) : Nil;
	if (y_magnification_qm);
	else
	    y_magnification_qm = ISVREF(text_box_format,(SI_Long)26L);
	magnified_x_scale = x_magnification_qm ? 
		FIX(IFIX(FIXNUM_TIMES(Current_image_x_scale,
		x_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) 
		: Current_image_x_scale;
	magnified_y_scale = y_magnification_qm ? 
		FIX(IFIX(FIXNUM_TIMES(Current_image_y_scale,
		y_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) 
		: Current_image_y_scale;
	scale = FIXNUM_MIN(magnified_x_scale,magnified_y_scale);
	value = ISVREF(text_box_format,(SI_Long)31L);
	if (IFIX(scale) == (SI_Long)4096L)
	    temp_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(scale,value);
	temp = FIX((SI_Long)6L);
	suppress_text_drawing_qm = NUM_LT(temp_1,temp) ? T : Nil;
    }
    if (suppress_text_drawing_qm);
    else if ((SI_Long)0L != (IFIX(ISVREF(text_box,(SI_Long)5L)) & 
	    (SI_Long)2048L)) {
	sub_class_bit_vector = ISVREF(ISVREF(text_box,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	suppress_text_drawing_qm =  !temp_2 ? T : Nil;
    }
    else
	suppress_text_drawing_qm = Nil;
    if (suppress_text_drawing_qm &&  !EQ(suppress_details_qm,
	    Qdraw_only_borders) && IFIX(left_border_width) == (SI_Long)0L 
	    && IFIX(top_border_width) == (SI_Long)0L && 
	    IFIX(right_border_width) == (SI_Long)0L && 
	    IFIX(bottom_border_width) == (SI_Long)0L) {
	sub_class_bit_vector = ISVREF(ISVREF(text_box,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Edit_box_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	force_hairline_border_qm =  !TRUEP(gensymed_symbol_3) ? T : Nil;
	if (force_hairline_border_qm);
	else {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    frame = gensymed_symbol_3;
	    symbol = Qworkspace;
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    force_hairline_border_qm = (SI_Long)0L < 
			    gensymed_symbol ? T : Nil;
		}
		else
		    force_hairline_border_qm = Nil;
	    }
	    else
		force_hairline_border_qm = Nil;
	}
	if (force_hairline_border_qm);
	else
	    force_hairline_border_qm = (SI_Long)0L != 
		    (IFIX(ISVREF(text_box,(SI_Long)5L)) & (SI_Long)2048L) ?
		     T : Nil;
	if (force_hairline_border_qm);
	else {
	    block_1 = text_box;
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    block_2 = gensymed_symbol_3;
	    block = block_1;
	    gensymed_symbol_3 = ISVREF(block_2,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)0L) : FIX((SI_Long)0L);
	    left_edge_in_workspace = gensymed_symbol_3;
	    gensymed_symbol_3 = ISVREF(block_2,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)1L) : FIX((SI_Long)0L);
	    top_edge_in_workspace = gensymed_symbol_3;
	    gensymed_symbol_3 = ISVREF(block_2,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)2L) : FIX((SI_Long)0L);
	    right_edge_in_workspace = gensymed_symbol_3;
	    gensymed_symbol_3 = ISVREF(block_2,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)3L) : FIX((SI_Long)0L);
	    bottom_edge_in_workspace = gensymed_symbol_3;
	    gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)0L) : FIX((SI_Long)0L);
	    if (FIXNUM_GE(gensymed_symbol_3,left_edge_in_workspace)) {
		gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		temp_2 = FIXNUM_GE(gensymed_symbol_3,top_edge_in_workspace);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		temp_2 = FIXNUM_LE(gensymed_symbol_3,right_edge_in_workspace);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		temp_2 = FIXNUM_LE(gensymed_symbol_3,bottom_edge_in_workspace);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if ( !temp_2) {
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) 
			: Nil;
		superblock_qm = gensymed_symbol_3;
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(superblock_qm))
		    goto end_loop;
		ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(superblock_qm,
			(SI_Long)5L)) & (SI_Long)2048L) ? T : Nil;
		if (ab_loop_it_) {
		    force_hairline_border_qm = ab_loop_it_;
		    goto end_1;
		}
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(superblock_qm,
			(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) 
			: Nil;
		superblock_qm = gensymed_symbol_3;
		goto next_loop;
	      end_loop:
		force_hairline_border_qm = Qnil;
	      end_1:;
	    }
	    else
		force_hairline_border_qm = Nil;
	}
    }
    else
	force_hairline_border_qm = Nil;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_3 = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    value = gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    left_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_3 = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    value = gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    top_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_3 = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    value = gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    right_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_3 = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    value = gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,value));
    bottom_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_1;
    if (get_lookup_slot_value_given_default(text_box,
	    Qframe_transforms_of_block,Nil)) {
	temp = Current_image_plane;
	temp = assq_function(temp,
		get_lookup_slot_value_given_default(text_box,
		Qframe_transforms_of_block,Nil));
	frame_transform_qm = CDR(temp);
    }
    else
	frame_transform_qm = Nil;
    gensymed_symbol = left_edge_of_text_box_in_window;
    if (IFIX(left_border_width) > (SI_Long)0L) {
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(left_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		left_border_width) && FIXNUM_LT(left_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    left_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    left_border_width));
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
    }
    else if (force_hairline_border_qm)
	gensymed_symbol_1 = (SI_Long)1L;
    else
	gensymed_symbol_1 = (SI_Long)0L;
    left_edge_of_cell_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = top_edge_of_text_box_in_window;
    if (IFIX(top_border_width) > (SI_Long)0L) {
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(top_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		top_border_width) && FIXNUM_LT(top_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    top_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    top_border_width));
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
    }
    else if (force_hairline_border_qm)
	gensymed_symbol_1 = (SI_Long)1L;
    else
	gensymed_symbol_1 = (SI_Long)0L;
    top_edge_of_cell_in_window = gensymed_symbol + gensymed_symbol_1;
    if (frame_transform_qm)
	right_edge_of_cell_in_window = Right_edge_of_draw_area;
    else {
	gensymed_symbol = right_edge_of_text_box_in_window;
	if (IFIX(right_border_width) > (SI_Long)0L) {
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(right_border_width);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    right_border_width) && FIXNUM_LT(right_border_width,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			right_border_width)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,
			right_border_width));
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	}
	else if (force_hairline_border_qm)
	    gensymed_symbol_1 = (SI_Long)1L;
	else
	    gensymed_symbol_1 = (SI_Long)0L;
	right_edge_of_cell_in_window = FIX(gensymed_symbol - 
		gensymed_symbol_1);
    }
    if (frame_transform_qm)
	bottom_edge_of_cell_in_window = Bottom_edge_of_draw_area;
    else {
	gensymed_symbol = bottom_edge_of_text_box_in_window;
	if (IFIX(bottom_border_width) > (SI_Long)0L) {
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(bottom_border_width);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom_border_width) && FIXNUM_LT(bottom_border_width,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			bottom_border_width)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,
			bottom_border_width));
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	}
	else if (force_hairline_border_qm)
	    gensymed_symbol_1 = (SI_Long)1L;
	else
	    gensymed_symbol_1 = (SI_Long)0L;
	bottom_edge_of_cell_in_window = FIX(gensymed_symbol - 
		gensymed_symbol_1);
    }
    image_x_scale_of_table = Current_image_x_scale;
    image_y_scale_of_table = Current_image_y_scale;
    unmagnified_width_of_text_to_draw_beyond_qm = Nil;
    draw_or_change_color_in_text_cell_for_block(text_box,
	    image_x_scale_of_table,image_y_scale_of_table,
	    color_change_case_qm,new_text_color_qm,suppress_details_qm,
	    highlight_or_new_background_color_qm,
	    unmagnified_width_of_text_to_draw_beyond_qm,text,
	    text_box_format,text_cell_plist,
	    FIX(left_edge_of_cell_in_window),
	    FIX(top_edge_of_cell_in_window),right_edge_of_cell_in_window,
	    bottom_edge_of_cell_in_window);
    if (suppress_text_drawing_qm &&  !EQ(suppress_details_qm,
	    Qdraw_only_borders)) {
	temp_2 = TRUEP(memq_function(final_border_color,list_constant_10));
	if (temp_2);
	else {
	    temp = Current_background_color_value;
	    if (EQ(final_border_color,Qbackground))
		temp_1 = Current_background_color_value;
	    else if (EQ(final_border_color,Qforeground) || 
		    EQ(final_border_color,Qworkspace_foreground))
		temp_1 = Current_foreground_color_value;
	    else if (EQ(final_border_color,Qtransparent))
		temp_1 = Current_background_color_value;
	    else
		temp_1 = map_to_color_value(final_border_color);
	    temp_2 = NUM_EQ(temp,temp_1);
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	final_border_color = cell_text_color;
    if ( !(EQ(existing_border_color,final_border_color) || 
	    EQ(color_change_case_qm,Qselective_redraw) &&  
	    !TRUEP(new_border_color_qm))) {
	if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
	    if (EQ(final_border_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(final_border_color,Qforeground) || 
		    EQ(final_border_color,Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(final_border_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(final_border_color);
	    if (EQ(existing_border_color,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(existing_border_color,Qforeground) || 
		    EQ(existing_border_color,Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(existing_border_color,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(existing_border_color);
	    border_color_difference = FIXNUM_LOGXOR(color_value_1,
		    color_value_2);
	}
	else if (EQ(final_border_color,existing_border_color))
	    border_color_difference = EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(final_border_color,Qtransparent))
	    border_color_difference = EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(existing_border_color,Qtransparent)) {
	    if (EQ(final_border_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(final_border_color,Qforeground) || 
		    EQ(final_border_color,Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(final_border_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(final_border_color);
	    border_color_difference = FIXNUM_LOGXOR(color_value_1,
		    Current_background_color_value);
	}
	else {
	    if (EQ(final_border_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(final_border_color,Qforeground) || 
		    EQ(final_border_color,Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(final_border_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(final_border_color);
	    if (EQ(existing_border_color,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(existing_border_color,Qforeground) || 
		    EQ(existing_border_color,Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(existing_border_color,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(existing_border_color);
	    border_color_difference = FIXNUM_LOGXOR(color_value_1,
		    color_value_2);
	}
	if (EQ(existing_border_color,Qbackground))
	    existing_border_color_value = Current_background_color_value;
	else if (EQ(existing_border_color,Qforeground) || 
		EQ(existing_border_color,Qworkspace_foreground))
	    existing_border_color_value = Current_foreground_color_value;
	else if (EQ(existing_border_color,Qtransparent))
	    existing_border_color_value = Current_background_color_value;
	else
	    existing_border_color_value = 
		    map_to_color_value(existing_border_color);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(existing_border_color_value);
	  if ( !(top_edge_of_cell_in_window == top_edge_of_text_box_in_window))
	      draw_graphic_element(6,Qadd_solid_rectangle,
		      FIX(left_edge_of_text_box_in_window),
		      FIX(top_edge_of_text_box_in_window),
		      FIX(right_edge_of_text_box_in_window),
		      FIX(top_edge_of_cell_in_window),border_color_difference);
	  if ( !(IFIX(bottom_edge_of_cell_in_window) == 
		  bottom_edge_of_text_box_in_window))
	      draw_graphic_element(6,Qadd_solid_rectangle,
		      FIX(left_edge_of_text_box_in_window),
		      bottom_edge_of_cell_in_window,
		      FIX(right_edge_of_text_box_in_window),
		      FIX(bottom_edge_of_text_box_in_window),
		      border_color_difference);
	  if ( !(left_edge_of_cell_in_window == 
		  left_edge_of_text_box_in_window))
	      draw_graphic_element(6,Qadd_solid_rectangle,
		      FIX(left_edge_of_text_box_in_window),
		      FIX(top_edge_of_cell_in_window),
		      FIX(left_edge_of_cell_in_window),
		      bottom_edge_of_cell_in_window,border_color_difference);
	  if ( !(IFIX(bottom_edge_of_cell_in_window) == 
		  bottom_edge_of_text_box_in_window))
	      draw_graphic_element(6,Qadd_solid_rectangle,
		      right_edge_of_cell_in_window,
		      FIX(top_edge_of_cell_in_window),
		      FIX(right_edge_of_text_box_in_window),
		      bottom_edge_of_cell_in_window,border_color_difference);
	  set_current_background_color_value(old_color_value);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* DRAW-TEXT-SEGMENT-IN-TEXT-BOX */
Object draw_text_segment_in_text_box(text_segment,
	    text_tail_past_text_segment_qm,
	    unmagnified_distance_of_text_segment_from_top,text_box)
    Object text_segment, text_tail_past_text_segment_qm;
    Object unmagnified_distance_of_text_segment_from_top, text_box;
{
    Object current_text_box_format, current_text_cell_plist, temp;
    Object frame_transform_qm, left_border_width, scale, gensymed_symbol_1;
    Object value, top_border_width, right_edge_of_cell_in_window;
    Object right_border_width, bottom_edge_of_cell_in_window;
    Object bottom_border_width, text_cell_background_color_qm;
    Object desired_current_background_color_value, text_cell_line_color_qm;
    Object current_foreground_color_value, temp_1, old_color_value;
    Object current_background_color_value, x_magnification_qm;
    Object y_magnification_qm, magnified_x_scale, magnified_y_scale, temp_3;
    Object block_1, block_2, block, left_edge_in_workspace;
    Object top_edge_in_workspace, right_edge_in_workspace;
    Object bottom_edge_in_workspace, superblock_qm, ab_loop_it_;
    SI_Long gensymed_symbol, gensymed_symbol_2, unshifted_result;
    SI_Long left_edge_of_text_box_in_window, gensymed_symbol_3;
    SI_Long left_edge_of_cell_in_window, top_edge_of_text_box_in_window;
    SI_Long top_edge_of_cell_in_window, right_edge_of_text_box_in_window;
    SI_Long bottom_edge_of_text_box_in_window;
    char temp_2;
    Declare_special(4);

    x_note_fn_call(109,79);
    current_text_box_format = ISVREF(text_box,(SI_Long)17L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
	    3);
      current_text_cell_plist = ISVREF(text_box,(SI_Long)18L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_text_cell_plist,Qcurrent_text_cell_plist,current_text_cell_plist,
	      2);
	if (get_lookup_slot_value_given_default(text_box,
		Qframe_transforms_of_block,Nil)) {
	    temp = Current_image_plane;
	    temp = assq_function(temp,
		    get_lookup_slot_value_given_default(text_box,
		    Qframe_transforms_of_block,Nil));
	    frame_transform_qm = CDR(temp);
	}
	else
	    frame_transform_qm = Nil;
	left_border_width = ISVREF(Current_text_box_format,(SI_Long)44L);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	gensymed_symbol_1 = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	value = gensymed_symbol_1;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	left_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_2;
	gensymed_symbol = left_edge_of_text_box_in_window;
	if (IFIX(left_border_width) == (SI_Long)0L)
	    gensymed_symbol_2 = (SI_Long)0L;
	else {
	    gensymed_symbol_2 = (SI_Long)1L;
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(left_border_width);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    left_border_width) && FIXNUM_LT(left_border_width,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			left_border_width)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_x_scale,
			left_border_width));
	    gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
	}
	left_edge_of_cell_in_window = gensymed_symbol + gensymed_symbol_2;
	top_border_width = ISVREF(Current_text_box_format,(SI_Long)45L);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	gensymed_symbol_1 = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	value = gensymed_symbol_1;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	top_edge_of_text_box_in_window = gensymed_symbol + gensymed_symbol_2;
	gensymed_symbol = top_edge_of_text_box_in_window;
	if (IFIX(top_border_width) == (SI_Long)0L)
	    gensymed_symbol_2 = (SI_Long)0L;
	else {
	    gensymed_symbol_2 = (SI_Long)1L;
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(top_border_width);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    top_border_width) && FIXNUM_LT(top_border_width,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			top_border_width)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_y_scale,
			top_border_width));
	    gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
	}
	top_edge_of_cell_in_window = gensymed_symbol + gensymed_symbol_2;
	if (frame_transform_qm)
	    right_edge_of_cell_in_window = Right_edge_of_draw_area;
	else {
	    right_border_width = ISVREF(Current_text_box_format,(SI_Long)46L);
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    gensymed_symbol_1 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    value = gensymed_symbol_1;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    right_edge_of_text_box_in_window = gensymed_symbol + 
		    gensymed_symbol_2;
	    gensymed_symbol = right_edge_of_text_box_in_window;
	    if (IFIX(right_border_width) == (SI_Long)0L)
		gensymed_symbol_2 = (SI_Long)0L;
	    else {
		gensymed_symbol_2 = (SI_Long)1L;
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		    gensymed_symbol_3 = IFIX(right_border_width);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			right_border_width) && 
			FIXNUM_LT(right_border_width,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_x_scale,
			    right_border_width)) + (SI_Long)2048L;
		    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_3 = 
			    IFIX(scalef_function(Current_image_x_scale,
			    right_border_width));
		gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
	    }
	    right_edge_of_cell_in_window = FIX(gensymed_symbol - 
		    gensymed_symbol_2);
	}
	if (frame_transform_qm)
	    bottom_edge_of_cell_in_window = Bottom_edge_of_draw_area;
	else {
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    gensymed_symbol_1 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    value = gensymed_symbol_1;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    bottom_edge_of_text_box_in_window = gensymed_symbol + 
		    gensymed_symbol_2;
	    bottom_border_width = ISVREF(Current_text_box_format,(SI_Long)47L);
	    gensymed_symbol = bottom_edge_of_text_box_in_window;
	    if (IFIX(bottom_border_width) == (SI_Long)0L)
		gensymed_symbol_2 = (SI_Long)0L;
	    else {
		gensymed_symbol_2 = (SI_Long)1L;
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		    gensymed_symbol_3 = IFIX(bottom_border_width);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			bottom_border_width) && 
			FIXNUM_LT(bottom_border_width,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_y_scale,
			    bottom_border_width)) + (SI_Long)2048L;
		    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_3 = 
			    IFIX(scalef_function(Current_image_y_scale,
			    bottom_border_width));
		gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
	    }
	    bottom_edge_of_cell_in_window = FIX(gensymed_symbol - 
		    gensymed_symbol_2);
	}
	text_cell_background_color_qm = Current_text_cell_plist ? 
		getfq_function_no_default(Current_text_cell_plist,
		Qbackground_color) : Nil;
	if (text_cell_background_color_qm);
	else
	    text_cell_background_color_qm = ISVREF(Current_text_box_format,
		    (SI_Long)24L);
	if (text_cell_background_color_qm) {
	    if (EQ(text_cell_background_color_qm,Qbackground))
		desired_current_background_color_value = 
			Current_background_color_value;
	    else if (EQ(text_cell_background_color_qm,Qforeground) || 
		    EQ(text_cell_background_color_qm,Qworkspace_foreground))
		desired_current_background_color_value = 
			Current_foreground_color_value;
	    else if (EQ(text_cell_background_color_qm,Qtransparent))
		desired_current_background_color_value = 
			Current_background_color_value;
	    else
		desired_current_background_color_value = 
			map_to_color_value(text_cell_background_color_qm);
	}
	else
	    desired_current_background_color_value = 
		    Current_background_color_value;
	text_cell_line_color_qm = Current_text_cell_plist ? 
		getfq_function_no_default(Current_text_cell_plist,
		Qline_color) : Nil;
	if (text_cell_line_color_qm);
	else
	    text_cell_line_color_qm = ISVREF(Current_text_box_format,
		    (SI_Long)23L);
	if (text_cell_line_color_qm) {
	    if (EQ(text_cell_line_color_qm,Qbackground))
		current_foreground_color_value = 
			Current_background_color_value;
	    else if (EQ(text_cell_line_color_qm,Qforeground) || 
		    EQ(text_cell_line_color_qm,Qworkspace_foreground))
		current_foreground_color_value = 
			Current_foreground_color_value;
	    else if (EQ(text_cell_line_color_qm,Qtransparent))
		current_foreground_color_value = 
			Current_background_color_value;
	    else
		current_foreground_color_value = 
			map_to_color_value(text_cell_line_color_qm);
	}
	else
	    current_foreground_color_value = Current_foreground_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
		1);
	  if (getfq_function_no_default(Current_text_cell_plist,
		  Qhighlight_color)) {
	      temp_1 = desired_current_background_color_value;
	      desired_current_background_color_value = 
		      Current_foreground_color_value;
	      Current_foreground_color_value = temp_1;
	  }
	  old_color_value = Current_background_color_value;
	  current_background_color_value = Current_background_color_value;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		  0);
	    set_current_background_color_value(desired_current_background_color_value);
	    temp_2 = TRUEP(Nil);
	    if (temp_2);
	    else {
		x_magnification_qm = Current_text_cell_plist ? 
			getfq_function_no_default(Current_text_cell_plist,
			Qx_magnification) : Nil;
		if (x_magnification_qm);
		else
		    x_magnification_qm = ISVREF(Current_text_box_format,
			    (SI_Long)25L);
		y_magnification_qm = Current_text_cell_plist ? 
			getfq_function_no_default(Current_text_cell_plist,
			Qy_magnification) : Nil;
		if (y_magnification_qm);
		else
		    y_magnification_qm = ISVREF(Current_text_box_format,
			    (SI_Long)26L);
		magnified_x_scale = x_magnification_qm ? 
			FIX(IFIX(FIXNUM_TIMES(Current_image_x_scale,
			x_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L) : Current_image_x_scale;
		magnified_y_scale = y_magnification_qm ? 
			FIX(IFIX(FIXNUM_TIMES(Current_image_y_scale,
			y_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L) : Current_image_y_scale;
		scale = FIXNUM_MIN(magnified_x_scale,magnified_y_scale);
		value = ISVREF(Current_text_box_format,(SI_Long)31L);
		if (IFIX(scale) == (SI_Long)4096L)
		    temp_3 = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_3 = scalef_function(scale,value);
		temp = FIX((SI_Long)6L);
		temp_2 = NUM_LT(temp_3,temp);
	    }
	    if (temp_2);
	    else
		temp_2 = (SI_Long)0L != (IFIX(ISVREF(text_box,
			(SI_Long)5L)) & (SI_Long)2048L);
	    if (temp_2);
	    else {
		block_1 = text_box;
		gensymed_symbol_1 = ACCESS_ONCE(ISVREF(text_box,(SI_Long)14L));
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) 
			: Nil;
		block_2 = gensymed_symbol_1;
		block = block_1;
		gensymed_symbol_1 = ISVREF(block_2,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		left_edge_in_workspace = gensymed_symbol_1;
		gensymed_symbol_1 = ISVREF(block_2,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		top_edge_in_workspace = gensymed_symbol_1;
		gensymed_symbol_1 = ISVREF(block_2,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		right_edge_in_workspace = gensymed_symbol_1;
		gensymed_symbol_1 = ISVREF(block_2,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		bottom_edge_in_workspace = gensymed_symbol_1;
		gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		if (FIXNUM_GE(gensymed_symbol_1,left_edge_in_workspace)) {
		    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    temp_2 = FIXNUM_GE(gensymed_symbol_1,
			    top_edge_in_workspace);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    temp_2 = FIXNUM_LE(gensymed_symbol_1,
			    right_edge_in_workspace);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    temp_2 = FIXNUM_LE(gensymed_symbol_1,
			    bottom_edge_in_workspace);
		}
		else
		    temp_2 = TRUEP(Nil);
		if ( !temp_2) {
		    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(text_box,
			    (SI_Long)14L));
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			    (SI_Long)5L)) : Nil;
		    superblock_qm = gensymed_symbol_1;
		    ab_loop_it_ = Nil;
		  next_loop:
		    if ( !TRUEP(superblock_qm))
			goto end_loop;
		    ab_loop_it_ = (SI_Long)0L != 
			    (IFIX(ISVREF(superblock_qm,(SI_Long)5L)) & 
			    (SI_Long)2048L) ? T : Nil;
		    if (ab_loop_it_) {
			temp_2 = TRUEP(ab_loop_it_);
			goto end_1;
		    }
		    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(superblock_qm,
			    (SI_Long)14L));
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			    (SI_Long)5L)) : Nil;
		    superblock_qm = gensymed_symbol_1;
		    goto next_loop;
		  end_loop:
		    temp_2 = TRUEP(Qnil);
		  end_1:;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    if ( !temp_2)
		draw_text_segment_1(text_segment,
			text_tail_past_text_segment_qm,
			unmagnified_distance_of_text_segment_from_top,
			FIX(left_edge_of_cell_in_window),
			FIX(top_edge_of_cell_in_window),
			right_edge_of_cell_in_window,
			bottom_edge_of_cell_in_window);
	    set_current_background_color_value(old_color_value);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* SCROLL-FRAME-TRANSFORM-OF-TEXT-BOX */
Object scroll_frame_transform_of_text_box(text_box,frame_transform,dx,dy)
    Object text_box, frame_transform, dx, dy;
{
    Object text_box_format, existing_y_offset, requested_y_offset, temp;
    SI_Long text_cell_interline_distance, minimum_y_offset, maximum_y_offset;
    SI_Long temp_1, actual_dy;

    x_note_fn_call(109,80);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_interline_distance = IFIX(FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)33L),ISVREF(text_box_format,(SI_Long)31L)));
    existing_y_offset = ISVREF(frame_transform,(SI_Long)7L);
    requested_y_offset = FIXNUM_ADD(existing_y_offset,dy);
    temp = ISVREF(text_box,(SI_Long)16L);
    minimum_y_offset =  - (text_cell_interline_distance * 
	    IFIX(find_end_of_text(2,CDR(temp),FIX((SI_Long)0L))));
    maximum_y_offset = (SI_Long)0L;
    temp_1 = MIN(maximum_y_offset,IFIX(requested_y_offset));
    actual_dy = MAX(minimum_y_offset,temp_1) - IFIX(existing_y_offset);
    if ( !((SI_Long)0L == IFIX(dx) && (SI_Long)0L == actual_dy)) {
	scroll_frame_transform(frame_transform,dx,FIX(actual_dy));
	return synch_elevator_position_to_frame_transform(frame_transform);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdown;               /* down */

static Object Qright;              /* right */

static Object Qline;               /* line */

static Object Qpage;               /* page */

/* SCROLL-BLOCK-FOR-TEXT-BOX */
Object scroll_block_for_text_box(text_box,image_plane,amount_of_step,
	    direction_of_step)
    Object text_box, image_plane, amount_of_step, direction_of_step;
{
    Object horizontal_p, text_box_format, frame_transform_qm;
    Object gensymed_symbol_2;
    SI_Long sign, text_cell_interline_distance, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long workspace_units_to_move, dx, dy;

    x_note_fn_call(109,81);
    sign = EQ(direction_of_step,Qdown) || EQ(direction_of_step,Qright) ? 
	    (SI_Long)-1L : (SI_Long)1L;
    horizontal_p = EQ(direction_of_step,Qleft) || EQ(direction_of_step,
	    Qright) ? T : Nil;
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_interline_distance = IFIX(FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)33L),ISVREF(text_box_format,(SI_Long)31L)));
    frame_transform_qm = find_frame_transform_if_any(text_box,image_plane);
    gensymed_symbol = sign;
    if (EQ(amount_of_step,Qline))
	gensymed_symbol_1 = horizontal_p ? (SI_Long)30L : 
		text_cell_interline_distance;
    else if (EQ(amount_of_step,Qpage)) {
	if (horizontal_p) {
	    gensymed_symbol_2 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_2 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_3;
	}
	else {
	    gensymed_symbol_1 = text_cell_interline_distance;
	    gensymed_symbol_2 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_2 = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol_2 = gensymed_symbol_2 ? 
		    ISVREF(gensymed_symbol_2,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = text_cell_interline_distance;
	    gensymed_symbol_3 = IFIX(ltruncate(FIX(gensymed_symbol_3),
		    FIX(gensymed_symbol_4)));
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_1 = gensymed_symbol_1 * gensymed_symbol_3;
	}
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    workspace_units_to_move = gensymed_symbol * gensymed_symbol_1;
    dx = horizontal_p ? workspace_units_to_move : (SI_Long)0L;
    dy = horizontal_p ? (SI_Long)0L : workspace_units_to_move;
    if (frame_transform_qm)
	return scroll_frame_transform_of_text_box(text_box,
		frame_transform_qm,FIX(dx),FIX(dy));
    else
	return VALUES_1(Nil);
}

/* SCROLL-LINE-INDEX-TO-TOP */
Object scroll_line_index_to_top(frame_transform,line_index)
    Object frame_transform, line_index;
{
    Object text_box, text_box_format;
    SI_Long text_cell_interline_distance, goal_offset;

    x_note_fn_call(109,82);
    text_box = ISVREF(frame_transform,(SI_Long)4L);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_interline_distance = IFIX(FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)33L),ISVREF(text_box_format,(SI_Long)31L)));
    goal_offset =  - (IFIX(FIXNUM_SUB1(line_index)) * 
	    text_cell_interline_distance);
    return scroll_frame_transform_of_text_box(text_box,frame_transform,
	    FIX((SI_Long)0L),FIX(goal_offset - IFIX(ISVREF(frame_transform,
	    (SI_Long)7L))));
}

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_scrolling_into_view_global_flag_qm, Qsuppress_scrolling_into_view_global_flag_qm);

static Object Qsuppressed;         /* suppressed */

/* SCROLL-TEXT-INTO-VIEW */
Object scroll_text_into_view(frame_transform,line_index,character_index)
    Object frame_transform, line_index, character_index;
{
    Object text_box, temp, x_in_workspace, y_in_workspace, text_box_format;
    Object baseline_to_baseline_distance, gensymed_symbol;
    Object x_offset_in_cell_of_mark, y_offset_in_cell_of_mark;
    Object delta_to_bring_to_top, delta_to_bring_to_left, actual_x_delta;
    Object actual_y_delta;
    SI_Long number_of_lines_of_padding, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long width_of_view_area, height_of_view_area;
    SI_Long vertical_padding_if_we_scroll, temp_1, temp_2;
    SI_Long horizontal_padding_if_we_scroll;
    Object result;

    x_note_fn_call(109,83);
    if (Suppress_scrolling_into_view_global_flag_qm)
	return VALUES_1(Qsuppressed);
    text_box = ISVREF(frame_transform,(SI_Long)4L);
    temp = ISVREF(text_box,(SI_Long)16L);
    result = find_position_in_text(10,text_box,Nil,Nil,Nil,Nil,Nil,Nil,
	    line_index,character_index,CDR(temp));
    MVS_5(result,temp,temp,temp,x_in_workspace,y_in_workspace);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    baseline_to_baseline_distance = FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)33L),ISVREF(text_box_format,(SI_Long)31L));
    number_of_lines_of_padding = (SI_Long)3L;
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    x_offset_in_cell_of_mark = minusn(4,x_in_workspace,gensymed_symbol,
	    ISVREF(text_box_format,(SI_Long)44L),ISVREF(text_box_format,
	    (SI_Long)27L));
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    y_offset_in_cell_of_mark = minusn(5,y_in_workspace,gensymed_symbol,
	    ISVREF(text_box_format,(SI_Long)45L),ISVREF(text_box_format,
	    (SI_Long)28L),ISVREF(text_box_format,(SI_Long)32L));
    delta_to_bring_to_top = 
	    FIXNUM_NEGATE(FIXNUM_ADD(y_offset_in_cell_of_mark,
	    ISVREF(frame_transform,(SI_Long)7L)));
    delta_to_bring_to_left = 
	    FIXNUM_NEGATE(FIXNUM_ADD(x_offset_in_cell_of_mark,
	    ISVREF(frame_transform,(SI_Long)6L)));
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    width_of_view_area = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    height_of_view_area = gensymed_symbol_1 - gensymed_symbol_2;
    vertical_padding_if_we_scroll = number_of_lines_of_padding * 
	    IFIX(baseline_to_baseline_distance);
    temp_1 = IFIX(ltruncate(FIX(width_of_view_area),FIX((SI_Long)5L)));
    temp_2 = (IFIX(ISVREF(text_box_format,(SI_Long)34L)) + (SI_Long)128L 
	    >>  -  - (SI_Long)8L) * (SI_Long)3L;
    horizontal_padding_if_we_scroll = MIN(temp_1,temp_2);
    actual_x_delta = FIX((SI_Long)0L);
    actual_y_delta = FIX((SI_Long)0L);
    if (IFIX(delta_to_bring_to_top) + height_of_view_area < 
	    IFIX(baseline_to_baseline_distance))
	actual_y_delta = FIX(IFIX(delta_to_bring_to_top) + 
		height_of_view_area +  - vertical_padding_if_we_scroll);
    else if ((SI_Long)0L < IFIX(delta_to_bring_to_top))
	actual_y_delta = FIX(IFIX(delta_to_bring_to_top) + 
		IFIX(baseline_to_baseline_distance) * MIN(IFIX(line_index),
		number_of_lines_of_padding));
    if (width_of_view_area - IFIX(ISVREF(text_box_format,(SI_Long)27L)) < 
	    IFIX(FIXNUM_NEGATE(delta_to_bring_to_left)))
	actual_x_delta = FIX(IFIX(delta_to_bring_to_left) + 
		width_of_view_area +  - horizontal_padding_if_we_scroll);
    else if (FIXNUM_LT(FIXNUM_NEGATE(delta_to_bring_to_left),
	    ISVREF(text_box_format,(SI_Long)27L))) {
	actual_x_delta = FIX(IFIX(delta_to_bring_to_left) + 
		horizontal_padding_if_we_scroll);
	if ((SI_Long)0L < IFIX(FIXNUM_ADD(actual_x_delta,
		ISVREF(frame_transform,(SI_Long)6L))))
	    actual_x_delta = FIXNUM_NEGATE(ISVREF(frame_transform,
		    (SI_Long)6L));
    }
    if ( !((SI_Long)0L == IFIX(actual_x_delta) && (SI_Long)0L == 
	    IFIX(actual_y_delta)))
	return scroll_frame_transform_of_text_box(text_box,frame_transform,
		actual_x_delta,actual_y_delta);
    else
	return VALUES_1(Nil);
}

static Object Qposition_of_vertical_elevator;  /* position-of-vertical-elevator */

/* DELTA-POSITION-OF-BLOCK-SCROLL */
Object delta_position_of_block_scroll(text_box,image_plane,
	    horizontal_delta,vertical_delta)
    Object text_box, image_plane, horizontal_delta, vertical_delta;
{
    Object frame_transform, temp, number_of_lines_in_text_box, scale, value;
    Object line_number;
    SI_Long unshifted_result;

    x_note_fn_call(109,84);
    if ( !TRUEP(zerop(vertical_delta))) {
	frame_transform = find_frame_transform_if_any(text_box,image_plane);
	temp = ISVREF(text_box,(SI_Long)16L);
	number_of_lines_in_text_box = find_end_of_text(2,CDR(temp),
		FIX((SI_Long)0L));
	scale = get_lookup_slot_value_given_default(text_box,
		Qposition_of_vertical_elevator,FIX((SI_Long)0L));
	value = number_of_lines_in_text_box;
	if (IFIX(scale) == (SI_Long)4096L)
	    line_number = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    line_number = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    line_number = scalef_function(scale,value);
	return scroll_line_index_to_top(frame_transform,line_number);
    }
    else
	return VALUES_1(Nil);
}

static Object Qposition_of_horizontal_elevator;  /* position-of-horizontal-elevator */

/* SYNCH-ELEVATOR-POSITION-TO-FRAME-TRANSFORM */
Object synch_elevator_position_to_frame_transform(frame_transform)
    Object frame_transform;
{
    Object text_box, temp, number_of_lines_in_text_box, text_box_format;
    Object current_vertical_offset, line_number_of_top_most_line;
    Object new_vertical_position_of_elevator;
    SI_Long text_cell_interline_distance;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(109,85);
    text_box = ISVREF(frame_transform,(SI_Long)4L);
    temp = ISVREF(text_box,(SI_Long)16L);
    number_of_lines_in_text_box = find_end_of_text(2,CDR(temp),
	    FIX((SI_Long)0L));
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_cell_interline_distance = IFIX(FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)33L),ISVREF(text_box_format,(SI_Long)31L)));
    current_vertical_offset = FIXNUM_NEGATE(ISVREF(frame_transform,
	    (SI_Long)7L));
    line_number_of_top_most_line = l_round(current_vertical_offset,
	    FIX(text_cell_interline_distance));
    if ((SI_Long)0L == IFIX(number_of_lines_in_text_box))
	new_vertical_position_of_elevator = FIX((SI_Long)0L);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    new_vertical_position_of_elevator = 
		    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(4096.0 * 
		    ((double)IFIX(line_number_of_top_most_line) / 
		    (double)IFIX(number_of_lines_in_text_box))),_);
	POP_LOCAL_ALLOCATION(0,0);
    }
    if ( !FIXNUM_EQ(new_vertical_position_of_elevator,
	    get_lookup_slot_value_given_default(text_box,
	    Qposition_of_vertical_elevator,FIX((SI_Long)0L))))
	return move_elevator(text_box,
		get_lookup_slot_value_given_default(text_box,
		Qposition_of_horizontal_elevator,FIX((SI_Long)0L)),
		new_vertical_position_of_elevator);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_label_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_label_box_spots, Qchain_of_available_label_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Label_box_spot_count, Qlabel_box_spot_count);

Object Chain_of_available_label_box_spots_vector = UNBOUND;

/* LABEL-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object label_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(109,86);
    temp = Label_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LABEL-BOX-SPOT-COUNT */
Object outstanding_label_box_spot_count()
{
    Object def_structure_label_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,87);
    gensymed_symbol = IFIX(Label_box_spot_count);
    def_structure_label_box_spot_variable = Chain_of_available_label_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_label_box_spot_variable))
	goto end_loop;
    def_structure_label_box_spot_variable = 
	    ISVREF(def_structure_label_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LABEL-BOX-SPOT-1 */
Object reclaim_label_box_spot_1(label_box_spot)
    Object label_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(109,88);
    inline_note_reclaim_cons(label_box_spot,Nil);
    structure_being_reclaimed = label_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(label_box_spot,(SI_Long)2L));
      SVREF(label_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_label_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(label_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_label_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = label_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LABEL-BOX-SPOT */
Object reclaim_structure_for_label_box_spot(label_box_spot)
    Object label_box_spot;
{
    x_note_fn_call(109,89);
    return reclaim_label_box_spot_1(label_box_spot);
}

static Object Qg2_defstruct_structure_name_label_box_spot_g2_struct;  /* g2-defstruct-structure-name::label-box-spot-g2-struct */

/* MAKE-PERMANENT-LABEL-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_label_box_spot_structure_internal()
{
    Object def_structure_label_box_spot_variable;
    Object defstruct_g2_label_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(109,90);
    def_structure_label_box_spot_variable = Nil;
    atomic_incff_symval(Qlabel_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_label_box_spot_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_label_box_spot_variable = the_array;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_label_box_spot_g2_struct;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_label_box_spot_variable,FIX((SI_Long)15L)) = Nil;
	def_structure_label_box_spot_variable = 
		defstruct_g2_label_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_label_box_spot_variable);
}

/* MAKE-LABEL-BOX-SPOT-1 */
Object make_label_box_spot_1()
{
    Object def_structure_label_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(109,91);
    def_structure_label_box_spot_variable = 
	    ISVREF(Chain_of_available_label_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_label_box_spot_variable) {
	svref_arg_1 = Chain_of_available_label_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_label_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_label_box_spot_g2_struct;
    }
    else
	def_structure_label_box_spot_variable = 
		make_permanent_label_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_label_box_spot_variable,Nil);
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_label_box_spot_variable,(SI_Long)6L) = 
	    FIX((SI_Long)1000L);
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)8L)) = Kunknown;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_label_box_spot_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_label_box_spot_variable);
}

/* GENERATE-SPOT-FOR-LABEL-BOX */
Object generate_spot_for_label_box(label_box,mouse_pointer)
    Object label_box, mouse_pointer;
{
    x_note_fn_call(109,92);
    return generate_text_box_spot(label_box,mouse_pointer,
	    make_label_box_spot_1());
}

static Object Qlabel_box;          /* label-box */

/* LABEL-BOX-P */
Object label_box_p(thing)
    Object thing;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(109,93);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qlabel_box,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
		    (SI_Long)18L));
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
		return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_activation_of_name_boxes_p, Qallow_activation_of_name_boxes_p);

static Object Qname_box;           /* name-box */

/* ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-NAME-BOX */
Object activate_if_possible_and_propagate_for_name_box(name_box)
    Object name_box;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(109,94);
    if (Allow_activation_of_name_boxes_p) {
	frame = name_box;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)30L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qname_box)) {
	    method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	method_function_qm = Qnil;
      end_1:;
	if (method_function_qm)
	    return inline_funcall_1(method_function_qm,frame);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_name_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_name_box_spots, Qchain_of_available_name_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Name_box_spot_count, Qname_box_spot_count);

Object Chain_of_available_name_box_spots_vector = UNBOUND;

/* NAME-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object name_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(109,95);
    temp = Name_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NAME-BOX-SPOT-COUNT */
Object outstanding_name_box_spot_count()
{
    Object def_structure_name_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(109,96);
    gensymed_symbol = IFIX(Name_box_spot_count);
    def_structure_name_box_spot_variable = Chain_of_available_name_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_name_box_spot_variable))
	goto end_loop;
    def_structure_name_box_spot_variable = 
	    ISVREF(def_structure_name_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-NAME-BOX-SPOT-1 */
Object reclaim_name_box_spot_1(name_box_spot)
    Object name_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(109,97);
    inline_note_reclaim_cons(name_box_spot,Nil);
    structure_being_reclaimed = name_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(name_box_spot,(SI_Long)2L));
      SVREF(name_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_name_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(name_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_name_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = name_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NAME-BOX-SPOT */
Object reclaim_structure_for_name_box_spot(name_box_spot)
    Object name_box_spot;
{
    x_note_fn_call(109,98);
    return reclaim_name_box_spot_1(name_box_spot);
}

static Object Qg2_defstruct_structure_name_name_box_spot_g2_struct;  /* g2-defstruct-structure-name::name-box-spot-g2-struct */

/* MAKE-PERMANENT-NAME-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_name_box_spot_structure_internal()
{
    Object def_structure_name_box_spot_variable;
    Object defstruct_g2_name_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(109,99);
    def_structure_name_box_spot_variable = Nil;
    atomic_incff_symval(Qname_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_name_box_spot_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_name_box_spot_variable = the_array;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_name_box_spot_g2_struct;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_name_box_spot_variable,FIX((SI_Long)15L)) = Nil;
	def_structure_name_box_spot_variable = 
		defstruct_g2_name_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_name_box_spot_variable);
}

/* MAKE-NAME-BOX-SPOT-1 */
Object make_name_box_spot_1()
{
    Object def_structure_name_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(109,100);
    def_structure_name_box_spot_variable = 
	    ISVREF(Chain_of_available_name_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_name_box_spot_variable) {
	svref_arg_1 = Chain_of_available_name_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_name_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_name_box_spot_g2_struct;
    }
    else
	def_structure_name_box_spot_variable = 
		make_permanent_name_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_name_box_spot_variable,Nil);
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_name_box_spot_variable,(SI_Long)6L) = 
	    FIX((SI_Long)1000L);
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)8L)) = Kunknown;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_name_box_spot_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_name_box_spot_variable);
}

/* GENERATE-SPOT-FOR-NAME-BOX */
Object generate_spot_for_name_box(name_box,mouse_pointer)
    Object name_box, mouse_pointer;
{
    x_note_fn_call(109,101);
    return generate_text_box_spot(name_box,mouse_pointer,
	    make_name_box_spot_1());
}

/* NAME-BOX-P */
Object name_box_p(thing)
    Object thing;
{
    Object x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(109,102);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qworkspace_name_box;  /* workspace-name-box */

static Object Qformat_frame;       /* format-frame */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qtext_box_format;    /* text-box-format */

static Object Qto_left;            /* to-left */

static Object array_constant;      /* # */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

/* MAKE-NAME-BOX */
Object make_name_box varargs_1(int, n)
{
    Object superblock;
    Object positioning_spec_qm, sub_class_bit_vector, workspace_case, name_box;
    Object format_name, name_box_format, height_for_name_box;
    Object gensymed_symbol_3, gensymed_symbol_4, slot_group_qm, temp;
    Object workspace_margin, subblocks, ab_queue_form_, ab_next_queue_element_;
    Object subblock, temp_2, top_clear_qm, right_clear_qm, bottom_clear_qm;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object ab_less_than_branch_qm_, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_for_name_box;
    SI_Long top_edge_for_name_box, bottom_edge_for_name_box;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,103);
    INIT_ARGS_nonrelocating();
    superblock = REQUIRED_ARG_nonrelocating();
    positioning_spec_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	workspace_case = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	workspace_case = Nil;
    name_box = make_frame(workspace_case ? Qworkspace_name_box : Qname_box);
    format_name = get_lookup_slot_value(name_box,
	    Qdefault_text_box_format_name);
    name_box_format = get_instance_with_name_if_any(Qformat_frame,format_name);
    if (name_box_format);
    else
	name_box_format = make_format_frame(format_name);
    height_for_name_box = 
	    FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ADD(ISVREF(name_box_format,
	    (SI_Long)45L),ISVREF(name_box_format,(SI_Long)28L)),
	    ISVREF(name_box_format,(SI_Long)31L)),ISVREF(name_box_format,
	    (SI_Long)30L)),ISVREF(name_box_format,(SI_Long)47L));
    gensymed_symbol_3 = name_box;
    gensymed_symbol_4 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol_3,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol_3,Qslot_group_for_block_qm);
    gensymed_symbol_4 = height_for_name_box;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_4;
    else if ( !EQ(gensymed_symbol_4,FIX((SI_Long)0L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol_3,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol_3,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol_3,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)3L)) = gensymed_symbol_4;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(name_box,Qtext_box_format);
    SVREF(name_box,FIX((SI_Long)17L)) = name_box_format;
    if (workspace_case) {
	workspace_margin = ISVREF(superblock,(SI_Long)17L);
	gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_3);
	gensymed_symbol_1 = IFIX(workspace_margin);
	left_edge_for_name_box = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_3);
	gensymed_symbol_1 = IFIX(workspace_margin);
	top_edge_for_name_box = gensymed_symbol + gensymed_symbol_1;
	bottom_edge_for_name_box = top_edge_for_name_box + 
		IFIX(height_for_name_box);
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol_3;
	temp_1 =  !(subblocks &&  ! 
		!TRUEP(constant_queue_next(ISVREF(subblocks,(SI_Long)2L),
		subblocks)));
	if (temp_1);
	else {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol_3;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    result = determine_extreme_edges_of_block(subblock);
	    gensymed_symbol_3 = NTH_VALUE((SI_Long)1L, result);
	    if (IFIX(gensymed_symbol_3) < bottom_edge_for_name_box) {
		temp_1 = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = TRUEP(T);
	    goto end_1;
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
	if (temp_1)
	    temp_2 = FIX(top_edge_for_name_box);
	else {
	    gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_3);
	    gensymed_symbol_1 = IFIX(height_for_name_box);
	    temp_2 = FIX(gensymed_symbol - gensymed_symbol_1);
	}
	shift_block(name_box,FIX(left_edge_for_name_box),temp_2);
    }
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qg2gl_variable,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else
	    temp_1 = EQ(positioning_spec_qm,Qto_left);
	if (temp_1) {
	    gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_3);
	    gensymed_symbol_3 = ISVREF(name_box,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol_3);
	    gensymed_symbol_3 = ISVREF(name_box,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_3);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	    temp_2 = FIX(gensymed_symbol - gensymed_symbol_1);
	    gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_3);
	    gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol_3);
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(height_for_name_box);
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol_1 = (SI_Long)1L;
	    shift_block_to(name_box,temp_2,FIX(gensymed_symbol >>  -  - 
		    gensymed_symbol_1));
	}
	else {
	    top_clear_qm = T;
	    right_clear_qm = T;
	    bottom_clear_qm = T;
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol_3;
	    ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_connection_ = Nil;
	    ab_connection_item_ = Nil;
	    connection = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      gensymed_symbol_3 = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol_3)) {
		  temp_2 = M_CAR(gensymed_symbol_3);
		  temp_1 = SIMPLE_VECTOR_P(temp_2);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  temp_2 = M_CDR(gensymed_symbol_3);
		  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_2) ? T : Nil;
	      }
	      else
		  ab_skip_list_p_ = Nil;
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = CDR(ab_skip_list_form_);
	    next_loop_1:
	    next_loop_2:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_connection_item_ = ISVREF(ab_current_node_,
			      (SI_Long)3L);
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_3:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_1;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_3;
		    end_loop_1:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_)
		  goto end_2;
	      goto next_loop_2;
	    end_loop_2:
	    end_2:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_3;
	      connection = ab_connection_;
	      if (EQ(ISVREF(connection,(SI_Long)3L),superblock)) {
		  temp_2 = ISVREF(array_constant,IFIX(ISVREF(connection,
			  (SI_Long)5L)) & (SI_Long)3L);
		  if (EQ(temp_2,Qtop))
		      top_clear_qm = Nil;
		  else if (EQ(temp_2,Qright))
		      right_clear_qm = Nil;
		  else if (EQ(temp_2,Qbottom))
		      bottom_clear_qm = Nil;
	      }
	      if (EQ(ISVREF(connection,(SI_Long)2L),superblock)) {
		  temp_2 = ISVREF(array_constant,IFIX(ISVREF(connection,
			  (SI_Long)4L)) & (SI_Long)3L);
		  if (EQ(temp_2,Qtop))
		      top_clear_qm = Nil;
		  else if (EQ(temp_2,Qright))
		      right_clear_qm = Nil;
		  else if (EQ(temp_2,Qbottom))
		      bottom_clear_qm = Nil;
	      }
	      goto next_loop_1;
	    end_loop_3:
	      if (bottom_clear_qm || top_clear_qm) {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		  gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
		  gensymed_symbol_1 = (SI_Long)1L;
		  temp_2 = FIX(gensymed_symbol >>  -  - gensymed_symbol_1);
	      }
	      else {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_1 = (SI_Long)4L;
		  temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	      }
	      if (bottom_clear_qm) {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_1 = (SI_Long)4L;
		  temp_3 = FIX(gensymed_symbol + gensymed_symbol_1);
	      }
	      else if (top_clear_qm) {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_1 = IFIX(height_for_name_box);
		  temp_3 = FIX(gensymed_symbol - gensymed_symbol_1);
	      }
	      else if (right_clear_qm) {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		  gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
		  gensymed_symbol_1 = IFIX(height_for_name_box);
		  gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		  gensymed_symbol_1 = (SI_Long)1L;
		  temp_3 = FIX(gensymed_symbol >>  -  - gensymed_symbol_1);
	      }
	      else {
		  gensymed_symbol_3 = ISVREF(superblock,(SI_Long)14L);
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol = IFIX(gensymed_symbol_3);
		  gensymed_symbol_1 = (SI_Long)4L;
		  temp_3 = FIX(gensymed_symbol + gensymed_symbol_1);
	      }
	      shift_block(name_box,temp_2,temp_3);
	    POP_SPECIAL();
	}
    }
    add_subblock(name_box,superblock);
    return VALUES_1(name_box);
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_name_box_creation, Qallow_name_box_creation);

DEFINE_VARIABLE_WITH_SYMBOL(Allow_name_box_creation_without_workspace, Qallow_name_box_creation_without_workspace);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* UPDATE-NAME-BOX */
Object update_name_box(frame)
    Object frame;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, name_box_qm, new_name_qm, workspace_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, new_text, old_text_slot_value_qm, svref_new_value;
    Object old_right_edge, old_bottom_edge, old_left_edge, old_top_edge;
    Object temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(109,104);
    gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp) {
	name_box_qm = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    name_box_qm = Qnil;
  end_1:;
    new_name_qm = get_primary_name_for_frame_if_any(frame);
    if (name_box_qm) {
	if ( !TRUEP(new_name_qm)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    delete_frame(name_box_qm);
	else
	    update_images_of_block(name_box_qm,T,T);
    }
    if (new_name_qm) {
	if ( !TRUEP(name_box_qm)) {
	    workspace_qm = get_workspace_if_any(frame);
	    if ((workspace_qm || 
		    Allow_name_box_creation_without_workspace) && 
		    Allow_name_box_creation)
		name_box_qm = make_name_box(1,frame);
	}
	if (name_box_qm) {
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
		      twrite_symbol(2,new_name_qm,T);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    new_text = slot_value_cons_1(temp_1,Nil);
	    old_text_slot_value_qm = ISVREF(name_box_qm,(SI_Long)16L);
	    if (old_text_slot_value_qm) {
		reclaim_text(CDR(old_text_slot_value_qm));
		M_CDR(old_text_slot_value_qm) = new_text;
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(name_box_qm,
			    Qbox_translation_and_text);
		svref_new_value = slot_value_cons_1(No_value,new_text);
		SVREF(name_box_qm,FIX((SI_Long)16L)) = svref_new_value;
	    }
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    old_right_edge = gensymed_symbol;
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    old_bottom_edge = gensymed_symbol;
	    reformat_text_box_in_place(6,name_box_qm,Nil,Nil,Nil,Nil,T);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qg2gl_variable,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		old_left_edge = gensymed_symbol;
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		old_top_edge = gensymed_symbol;
		temp_1 = name_box_qm;
		gensymed_symbol = ISVREF(frame,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol = ISVREF(frame,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(frame,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		gensymed_symbol_2 = (SI_Long)1L;
		shift_block_to(temp_1,temp_2,FIX(gensymed_symbol_1 >>  -  
			- gensymed_symbol_2));
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		temp =  !FIXNUM_EQ(old_left_edge,gensymed_symbol);
		if (temp);
		else {
		    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    temp =  !FIXNUM_EQ(old_top_edge,gensymed_symbol);
		}
		if (temp)
		    send_ws_representations_item_moved(name_box_qm,Nil,
			    FIX((SI_Long)0L));
	    }
	    else {
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		temp_1 = gensymed_symbol;
		gensymed_symbol = ISVREF(frame,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		if ( !FIXNUM_GE(temp_1,gensymed_symbol)) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Workspace_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    if (FIXNUM_LE(old_right_edge,gensymed_symbol)) {
			temp_1 = name_box_qm;
			gensymed_symbol_1 = IFIX(old_right_edge);
			gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)2L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol);
			shift_block(temp_1,FIX(gensymed_symbol_1 - 
				gensymed_symbol_2),FIX((SI_Long)0L));
			send_ws_representations_item_moved(name_box_qm,Nil,
				FIX((SI_Long)0L));
		    }
		    else {
			gensymed_symbol = ISVREF(frame,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			temp = FIXNUM_LE(old_bottom_edge,gensymed_symbol);
			if (temp);
			else {
			    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)1L) : 
				    FIX((SI_Long)0L);
			    temp_1 = gensymed_symbol;
			    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)3L) : 
				    FIX((SI_Long)0L);
			    temp = FIXNUM_GE(temp_1,gensymed_symbol);
			}
			if (temp) {
			    temp_1 = name_box_qm;
			    gensymed_symbol_1 = IFIX(old_right_edge);
			    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)2L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_2 = IFIX(gensymed_symbol);
			    gensymed_symbol_1 = gensymed_symbol_1 - 
				    gensymed_symbol_2;
			    gensymed_symbol_2 = (SI_Long)1L;
			    shift_block(temp_1,FIX(gensymed_symbol_1 >>  - 
				     - gensymed_symbol_2),FIX((SI_Long)0L));
			    send_ws_representations_item_moved(name_box_qm,
				    Nil,FIX((SI_Long)0L));
			}
		    }
		}
	    }
	    enlarge_workspace_for_block_rectangle_if_necessary(name_box_qm,
		    Nil);
	    temp_1 = name_box_qm;
	    update_subscriptions_from_virtual_attribute_change(temp_1,
		    get_property_value_function(3,
		    get_symbol_properties_function(Qtext),
		    Qvirtual_attribute,Nil),Nil);
	    return update_images_of_block(name_box_qm,Nil,T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qblinker;            /* blinker */

/* INITIALIZE-FOR-BLINKER */
Object initialize_for_blinker(blinker)
    Object blinker;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(109,105);
    frame = blinker;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qblinker)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    svref_new_value = IFIX(ISVREF(blinker,(SI_Long)5L)) | (SI_Long)1024L;
    return VALUES_1(ISVREF(blinker,(SI_Long)5L) = FIX(svref_new_value));
}

static Object Qdraw_blinker_in_xor;  /* draw-blinker-in-xor */

/* DRAW-FOR-BLINKER */
Object draw_for_blinker(blinker)
    Object blinker;
{
    Object compiled_function, block_or_connection, fun, blk, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp, svref_arg_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object current_drawing_transfer_mode;
    char temp_1, already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,106);
    SAVE_STACK();
    if (ISVREF(blinker,(SI_Long)20L)) {
	if (Currently_working_on_drawing_workspace) {
	    compiled_function = SYMBOL_FUNCTION(Qdraw_blinker_in_xor);
	    block_or_connection = blinker;
	    fun = Nil;
	    blk = Nil;
	    ab_loop_list_ = ISVREF(Current_image_plane,(SI_Long)31L);
	    ab_loop_it_ = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    fun = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    blk = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQ(fun,compiled_function) ? (EQ(blk,
		    block_or_connection) ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    if ( !temp_1) {
		svref_arg_1 = Current_image_plane;
		slot_value_push_modify_macro_arg = 
			slot_value_list_3(SYMBOL_FUNCTION(Qdraw_blinker_in_xor),
			blinker,copy_frame_serial_number(ISVREF(blinker,
			(SI_Long)3L)));
		car_1 = slot_value_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)31L);
		svref_new_value = slot_value_cons_1(car_1,cdr_1);
		RESTORE_STACK();
		return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)31L)) = 
			svref_new_value);
	    }
	    else {
		RESTORE_STACK();
		return VALUES_1(Nil);
	    }
	}
	else {
	    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
	    current_drawing_transfer_mode = Current_drawing_transfer_mode;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
		    0);
	      if ( !already_in_synch) {
		  Current_drawing_transfer_mode = Kxor;
		  synchronize_transfer_mode();
	      }
	      SAVE_VALUES(draw_blinker_in_xor(blinker,ISVREF(blinker,
		      (SI_Long)3L)));
	    POP_SPECIAL();
	    if ( !already_in_synch)
		synchronize_transfer_mode();
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* DRAW-BLINKER-IN-XOR */
Object draw_blinker_in_xor(blinker,reference_frame_serial_number)
    Object blinker, reference_frame_serial_number;
{
    Object gensymed_symbol, xa, ya, left_edge_of_draw_area;
    Object top_edge_of_draw_area, right_edge_of_draw_area;
    Object bottom_edge_of_draw_area, current_frame_transform_qm;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object enclosing_block, frame_transforms_of_block_qm;
    Object frame_transforms_of_enclosing_block, temp_1, frame_transform, value;
    Object incff_1_arg, temp_2;
    SI_Long gensymed_symbol_1, scale, gensymed_symbol_2, unshifted_result;
    SI_Long x_offset, y_offset;
    char temp;
    Declare_special(7);
    Object result;

    x_note_fn_call(109,107);
    gensymed_symbol = ISVREF(blinker,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(blinker) ? EQ(ISVREF(blinker,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_frame_serial_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(ISVREF(blinker,(SI_Long)20L)) : TRUEP(Nil)) {
	left_edge_of_draw_area = Left_edge_of_draw_area;
	top_edge_of_draw_area = Top_edge_of_draw_area;
	right_edge_of_draw_area = Right_edge_of_draw_area;
	bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		  5);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		    4);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		      3);
		current_frame_transform_qm = Current_frame_transform_qm;
		current_x_origin_of_drawing = Current_x_origin_of_drawing;
		current_y_origin_of_drawing = Current_y_origin_of_drawing;
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
			    0);
		      if ((SI_Long)0L != (IFIX(ISVREF(blinker,
			      (SI_Long)5L)) & (SI_Long)32768L)) {
			  enclosing_block = blinker;
			  frame_transforms_of_block_qm = Nil;
			next_loop:
			  frame_transforms_of_block_qm = 
				  get_lookup_slot_value_given_default(enclosing_block,
				  Qframe_transforms_of_block,Nil);
			  if (frame_transforms_of_block_qm) {
			      frame_transforms_of_enclosing_block = 
				      frame_transforms_of_block_qm;
			      goto end_1;
			  }
			  gensymed_symbol = 
				  ACCESS_ONCE(ISVREF(enclosing_block,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  enclosing_block = gensymed_symbol;
			  goto next_loop;
			end_loop:
			  frame_transforms_of_enclosing_block = Qnil;
			end_1:;
			  temp_1 = assq_function(Current_image_plane,
				  frame_transforms_of_enclosing_block);
			  frame_transform = CDR(temp_1);
			  if ( !EQ(Current_frame_transform_qm,
				      frame_transform)) {
			      nest_draw_area_for_frame_1(frame_transform);
			      Current_frame_transform_qm = frame_transform;
			      gensymed_symbol_1 = 
				      IFIX(ISVREF(frame_transform,
				      (SI_Long)10L));
			      scale = (SI_Long)4096L;
			      value = ISVREF(frame_transform,(SI_Long)6L);
			      if (scale == (SI_Long)4096L)
				  gensymed_symbol_2 = IFIX(value);
			      else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < scale && scale < 
				      IFIX(Isqrt_of_most_positive_fixnum) 
				      && 
				      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      value) && FIXNUM_LT(value,
				      Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = scale * IFIX(value) + 
					  (SI_Long)2048L;
				  gensymed_symbol_2 = unshifted_result >>  
					  -  - (SI_Long)12L;
			      }
			      else
				  gensymed_symbol_2 = 
					  IFIX(scalef_function(FIX(scale),
					  value));
			      x_offset = gensymed_symbol_1 + gensymed_symbol_2;
			      if ( !((SI_Long)0L == x_offset)) {
				  if (IFIX(Current_image_x_scale) == 
					  (SI_Long)4096L)
				      incff_1_arg = FIX(x_offset);
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_x_scale) && 
					  FIXNUM_LT(Current_image_x_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
					  < x_offset && x_offset < 
					  IFIX(Isqrt_of_most_positive_fixnum)) 
					      {
				      unshifted_result = 
					      IFIX(Current_image_x_scale) 
					      * x_offset + (SI_Long)2048L;
				      incff_1_arg = FIX(unshifted_result 
					      >>  -  - (SI_Long)12L);
				  }
				  else
				      incff_1_arg = 
					      scalef_function(Current_image_x_scale,
					      FIX(x_offset));
				  temp_2 = 
					  FIXNUM_ADD(Current_x_origin_of_drawing,
					  incff_1_arg);
				  Current_x_origin_of_drawing = temp_2;
			      }
			      gensymed_symbol_1 = 
				      IFIX(ISVREF(frame_transform,
				      (SI_Long)11L));
			      scale = (SI_Long)4096L;
			      value = ISVREF(frame_transform,(SI_Long)7L);
			      if (scale == (SI_Long)4096L)
				  gensymed_symbol_2 = IFIX(value);
			      else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < scale && scale < 
				      IFIX(Isqrt_of_most_positive_fixnum) 
				      && 
				      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      value) && FIXNUM_LT(value,
				      Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = scale * IFIX(value) + 
					  (SI_Long)2048L;
				  gensymed_symbol_2 = unshifted_result >>  
					  -  - (SI_Long)12L;
			      }
			      else
				  gensymed_symbol_2 = 
					  IFIX(scalef_function(FIX(scale),
					  value));
			      y_offset = gensymed_symbol_1 + gensymed_symbol_2;
			      if ( !((SI_Long)0L == y_offset)) {
				  if (IFIX(Current_image_y_scale) == 
					  (SI_Long)4096L)
				      incff_1_arg = FIX(y_offset);
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_y_scale) && 
					  FIXNUM_LT(Current_image_y_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
					  < y_offset && y_offset < 
					  IFIX(Isqrt_of_most_positive_fixnum)) 
					      {
				      unshifted_result = 
					      IFIX(Current_image_y_scale) 
					      * y_offset + (SI_Long)2048L;
				      incff_1_arg = FIX(unshifted_result 
					      >>  -  - (SI_Long)12L);
				  }
				  else
				      incff_1_arg = 
					      scalef_function(Current_image_y_scale,
					      FIX(y_offset));
				  temp_2 = 
					  FIXNUM_ADD(Current_y_origin_of_drawing,
					  incff_1_arg);
				  Current_y_origin_of_drawing = temp_2;
			      }
			  }
		      }
		      result = draw_icon_for_entity(blinker);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* SHIFT-BLINKER */
Object shift_blinker(blinker,delta_x,delta_y)
    Object blinker, delta_x, delta_y;
{
    Object workspace_qm;

    x_note_fn_call(109,108);
    workspace_qm = get_workspace_if_any(blinker);
    if (workspace_qm) {
	if (ISVREF(blinker,(SI_Long)20L))
	    update_images_of_block(blinker,T,T);
	ISVREF(blinker,(SI_Long)20L) = Nil;
	shift_block(blinker,delta_x,delta_y);
	enlarge_workspace_for_block_rectangle_if_necessary(blinker,
		workspace_qm);
	force_workspace_drawing(workspace_qm);
	ISVREF(blinker,(SI_Long)20L) = T;
	return update_images_of_block(blinker,Nil,T);
    }
    else
	return VALUES_1(Nil);
}

/* STOP-BLINKER */
Object stop_blinker(blinker,have_it_be_on_qm)
    Object blinker, have_it_be_on_qm;
{
    Object workspace_qm;

    x_note_fn_call(109,109);
    workspace_qm = get_workspace_if_any(blinker);
    if (workspace_qm) {
	if (have_it_be_on_qm) {
	    if ( !TRUEP(ISVREF(blinker,(SI_Long)20L))) {
		force_workspace_drawing(workspace_qm);
		ISVREF(blinker,(SI_Long)20L) = T;
		return update_images_of_block(blinker,Nil,T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (ISVREF(blinker,(SI_Long)20L)) {
	    force_workspace_drawing(workspace_qm);
	    update_images_of_block(blinker,T,T);
	    return VALUES_1(ISVREF(blinker,(SI_Long)20L) = Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MOVE-EDIT-CURSOR */
Object move_edit_cursor(edit_cursor,midline_x,baseline_y)
    Object edit_cursor, midline_x, baseline_y;
{
    Object gensymed_symbol_1, temp;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(109,110);
    gensymed_symbol = IFIX(midline_x);
    gensymed_symbol_1 = ISVREF(edit_cursor,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_1 = ISVREF(edit_cursor,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)1L;
    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
    temp = FIX(gensymed_symbol - gensymed_symbol_2);
    gensymed_symbol = IFIX(baseline_y);
    gensymed_symbol_1 = ISVREF(edit_cursor,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    return shift_blinker(edit_cursor,temp,FIX(gensymed_symbol - 
	    gensymed_symbol_2));
}

static Object Qstatement;          /* statement */

static Object Qincomplete;         /* incomplete */

/* INITIALIZE-FOR-STATEMENT */
Object initialize_for_statement(statement)
    Object statement;
{
    Object frame, sub_vector_qm, method_function_qm, box_translation_and_text;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(109,111);
    frame = statement;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qstatement)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    box_translation_and_text = ISVREF(statement,(SI_Long)16L);
    if ( !(box_translation_and_text &&  !EQ(box_translation_and_text,
	    No_value)))
	return update_frame_status(statement,Qincomplete,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_4;   /* "~NA had bad magnification information. It's been removed." */

/* INITIALIZE-AFTER-READING-FOR-TEXT-BOX */
Object initialize_after_reading_for_text_box(text_box)
    Object text_box;
{
    Object frame, sub_vector_qm, method_function_qm, plist, x_magnification_qm;
    Object y_magnification_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(109,112);
    frame = text_box;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtext_box)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    if ( 
	    !TRUEP(bad_4_0_beta_magnifications_in_text_boxes_removed_p_function())) 
		{
	plist = ISVREF(text_box,(SI_Long)18L);
	x_magnification_qm = getf(plist,Qx_magnification,_);
	y_magnification_qm = getf(plist,Qy_magnification,_);
	if (x_magnification_qm &&  !INTEGERP(x_magnification_qm) || 
		y_magnification_qm &&  !INTEGERP(y_magnification_qm)) {
	    change_text_box_property(text_box,Qx_magnification,Nil);
	    change_text_box_property(text_box,Qy_magnification,Nil);
	    reformat_text_box_in_place(1,text_box);
	    return notify_user(2,string_constant_4,text_box);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-RUNTIME-STRUCTURES-AFFECTED-BY-THIS-STATEMENT-VALUE */
Object reclaim_runtime_structures_affected_by_this_statement_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(109,113);
    update_runtime_structures_according_to_edit(1,frame);
    return VALUES_1(Nil);
}

static Object Qborderless_free_text;  /* borderless-free-text */

/* MAKE-FREE-TEXT-BOX */
Object make_free_text_box varargs_1(int, n)
{
    Object text_line;
    Object class_qm, text_box_format_name_qm;
    Object maximum_width_to_truncate_after_qm, truncated_string_suffix_qm;
    Object do_not_reformat_qm, length_1, index_1, new_line_position;
    Object next_index, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ch, temp;
    Object format_name, text_box_format;
    SI_Long i, ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,114);
    INIT_ARGS_nonrelocating();
    text_line = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_box_format_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    maximum_width_to_truncate_after_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    truncated_string_suffix_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_reformat_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (do_not_reformat_qm) {
	length_1 = lengthw(text_line);
	index_1 = FIX((SI_Long)0L);
	new_line_position = Nil;
	next_index = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !FIXNUM_LT(index_1,length_1))
	    goto end_loop;
	i = IFIX(FIXNUM_ADD1(index_1));
	ab_loop_bind_ = IFIX(length_1);
	ch = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ch = FIX(UBYTE_16_ISAREF_1(text_line,i));
	if (newline_p(ch)) {
	    new_line_position = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	new_line_position = Qnil;
      end_1:;
	temp = new_line_position;
	if (temp);
	else
	    temp = length_1;
	next_index = temp;
	temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
	ab_loopvar__2 = slot_value_list_2(temp,
		text_string_substring(text_line,index_1,next_index));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	index_1 = next_index;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	reclaim_text_string(text_line);
    }
    else {
	if (maximum_width_to_truncate_after_qm) {
	    format_name = text_box_format_name_qm;
	    if (format_name);
	    else {
		temp = class_qm;
		if (temp);
		else
		    temp = Qborderless_free_text;
		format_name = get_slot_init_form(2,temp,
			Qdefault_text_box_format_name);
	    }
	    text_box_format = get_instance_with_name_if_any(Qformat_frame,
		    format_name);
	    if (text_box_format);
	    else
		text_box_format = make_format_frame(format_name);
	    temp = truncate_string_as_necessary_to_fit(text_line,
		    maximum_width_to_truncate_after_qm,
		    ISVREF(text_box_format,(SI_Long)22L),
		    ISVREF(text_box_format,(SI_Long)34L),
		    truncated_string_suffix_qm);
	    if (temp);
	    else
		temp = obtain_simple_text_string(FIX((SI_Long)0L));
	    reclaim_text_string(text_line);
	}
	else
	    temp = text_line;
	temp = convert_text_string_to_text(temp);
    }
    return make_free_text_box_with_text(4,temp,class_qm,
	    text_box_format_name_qm,do_not_reformat_qm);
}

/* MAKE-FREE-TEXT-BOX-WITH-TEXT */
Object make_free_text_box_with_text varargs_1(int, n)
{
    Object text;
    Object class_qm, text_box_format_name_qm, do_not_reformat_qm, temp;
    Object free_text_box, format_name, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,115);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_box_format_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_reformat_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = class_qm;
    if (temp);
    else
	temp = Qborderless_free_text;
    free_text_box = make_frame(temp);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(free_text_box,Qtext_box_format);
    format_name = text_box_format_name_qm;
    if (format_name);
    else
	format_name = get_lookup_slot_value(free_text_box,
		Qdefault_text_box_format_name);
    svref_new_value = get_instance_with_name_if_any(Qformat_frame,format_name);
    if (svref_new_value);
    else
	svref_new_value = make_format_frame(format_name);
    SVREF(free_text_box,FIX((SI_Long)17L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(free_text_box,Qbox_translation_and_text);
    svref_new_value = slot_value_cons_1(No_value,text);
    SVREF(free_text_box,FIX((SI_Long)16L)) = svref_new_value;
    reformat_text_box_in_place(3,free_text_box,Nil,do_not_reformat_qm);
    return VALUES_1(free_text_box);
}

/* GENERATE-SPOT-FOR-DIALOG-MESSAGE */
Object generate_spot_for_dialog_message(dialog_message,mouse_pointer)
    Object dialog_message, mouse_pointer;
{
    x_note_fn_call(109,116);
    return generate_simple_item_spot(dialog_message,mouse_pointer);
}

/* GENERATE-SPOT-FOR-DIALOG-BUTTON */
Object generate_spot_for_dialog_button(dialog_button,mouse_pointer)
    Object dialog_button, mouse_pointer;
{
    x_note_fn_call(109,117);
    return generate_simple_item_spot(dialog_button,mouse_pointer);
}

static Object Qdialog_message;     /* dialog-message */

/* MAKE-DIALOG-MESSAGE */
Object make_dialog_message(constant_string)
    Object constant_string;
{
    x_note_fn_call(109,118);
    return make_free_text_box(2,copy_text_string(constant_string),
	    Qdialog_message);
}

static Object Qdialog_button;      /* dialog-button */

static Object Qdefault_button_format;  /* default-button-format */

static Object Qnon_default_button_format;  /* non-default-button-format */

/* MAKE-DIALOG-BUTTON */
Object make_dialog_button(constant_string,translation,
	    this_is_the_default_button_qm)
    Object constant_string, translation, this_is_the_default_button_qm;
{
    Object dialog_button, car_arg;

    x_note_fn_call(109,119);
    dialog_button = make_free_text_box(3,copy_text_string(constant_string),
	    Qdialog_button,this_is_the_default_button_qm ? 
	    Qdefault_button_format : Qnon_default_button_format);
    car_arg = ISVREF(dialog_button,(SI_Long)16L);
    M_CAR(car_arg) = translation;
    return VALUES_1(dialog_button);
}

static Object Qcenter;             /* center */

/* FORMAT-TEXT */
Object format_text varargs_1(int, n)
{
    Object text, text_box_format, text_cell_plist, width_for_cell_qm;
    Object do_not_reformat_text_qm, reformatting_with_same_format_qm;
    Object include_indentations_and_widths_qm;
    Object known_to_have_indentations_and_widths_qm;
    Object cursor_line_index_qm, cursor_character_index_qm;
    Object format_width_override_qm, allow_override_below_limit_p;
    Object text_cell_line_justification_qm, width_of_longest_line, old_text;
    Object temp, temp_1, text_element, ab_loop_list_, text_tail_qm, line_width;
    Object this_text_tail, temp_2, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, x_magnification_qm;
    Object width_for_justification_after_magnification;
    Object line_width_after_magnification, adjustment, l, indentation;
    Object l_trailer_qm, next_l_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, width_for_justification, temp_3;
    char temp_4;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,120);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    text_box_format = REQUIRED_ARG_nonrelocating();
    text_cell_plist = REQUIRED_ARG_nonrelocating();
    width_for_cell_qm = REQUIRED_ARG_nonrelocating();
    do_not_reformat_text_qm = REQUIRED_ARG_nonrelocating();
    reformatting_with_same_format_qm = REQUIRED_ARG_nonrelocating();
    include_indentations_and_widths_qm = REQUIRED_ARG_nonrelocating();
    known_to_have_indentations_and_widths_qm = REQUIRED_ARG_nonrelocating();
    cursor_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    format_width_override_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    allow_override_below_limit_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_cell_line_justification_qm = 
	    get_text_cell_line_justification(text_box_format,text_cell_plist);
    width_of_longest_line = FIX((SI_Long)0L);
    if ( !TRUEP(do_not_reformat_text_qm)) {
	old_text = Nil;
	temp = text;
	temp_1 = include_indentations_and_widths_qm;
	if (temp_1);
	else
	    temp_1 = text_cell_line_justification_qm;
	result = reformat_text(13,temp,text_box_format,width_for_cell_qm,
		temp_1,Nil,Nil,Nil,Nil,Nil,Nil,format_width_override_qm,
		text_cell_plist,allow_override_below_limit_p);
	MVS_3(result,text,width_of_longest_line,old_text);
	if (cursor_line_index_qm && cursor_character_index_qm) {
	    result = determine_corrected_text_position_if_necessary(5,
		    cursor_line_index_qm,cursor_character_index_qm,text,
		    old_text,FIX((SI_Long)1L));
	    MVS_2(result,cursor_line_index_qm,cursor_character_index_qm);
	}
	reclaim_text(old_text);
    }
    else if (known_to_have_indentations_and_widths_qm) {
	text_element = Nil;
	ab_loop_list_ = text;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	text_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(text_element) && EQ(CAR(text_element),Qline_width)) {
	    if (FIXNUM_GT(CDR(text_element),width_of_longest_line))
		width_of_longest_line = CDR(text_element);
	}
	goto next_loop;
      end_loop:;
    }
    else {
	temp = text;
	temp_1 = include_indentations_and_widths_qm;
	if (temp_1);
	else
	    temp_1 = text_cell_line_justification_qm;
	width_of_longest_line = compute_width_of_longest_line(4,temp,
		text_box_format,text_cell_plist,temp_1);
    }
    if (text_cell_line_justification_qm) {
	text_tail_qm = text;
	line_width = Nil;
	gensymed_symbol = IFIX(width_of_longest_line);
	temp_1 = format_width_override_qm;
	if (temp_1);
	else
	    temp_1 = width_for_cell_qm;
	if (temp_1);
	else
	    temp_1 = FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(temp_1);
	gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)27L));
	gensymed_symbol_3 = IFIX(ISVREF(text_box_format,(SI_Long)29L));
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3;
	width_for_justification = MAX(gensymed_symbol,gensymed_symbol_1);
	this_text_tail = Nil;
      next_loop_1:
	this_text_tail = text_tail_qm;
	result = get_next_text_line(text_tail_qm);
	MVS_6(result,gensymed_symbol_4,temp_1,temp_1,gensymed_symbol_5,
		temp_1,gensymed_symbol_6);
	line_width = gensymed_symbol_6;
	text_tail_qm = gensymed_symbol_5;
	x_magnification_qm = text_cell_plist ? 
		getfq_function_no_default(text_cell_plist,
		Qx_magnification) : Nil;
	if (x_magnification_qm);
	else
	    x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
	width_for_justification_after_magnification = x_magnification_qm ? 
		inverse_magnify(FIX(width_for_justification),
		x_magnification_qm) : FIX(width_for_justification);
	line_width_after_magnification = x_magnification_qm ? 
		inverse_magnify(line_width,x_magnification_qm) : line_width;
	if (EQ(text_cell_line_justification_qm,Qcenter))
	    adjustment = 
		    FIX(IFIX(FIXNUM_MINUS(width_for_justification_after_magnification,
		    line_width_after_magnification)) >>  -  - (SI_Long)1L);
	else if (EQ(text_cell_line_justification_qm,Qright))
	    adjustment = 
		    FIXNUM_MINUS(width_for_justification_after_magnification,
		    line_width_after_magnification);
	else
	    adjustment = FIX((SI_Long)0L);
	l = this_text_tail;
      next_loop_2:
	if ( !TRUEP(l))
	    goto end_loop_1;
	if (FIXNUMP(CAR(l))) {
	    M_CAR(l) = adjustment;
	    goto end_1;
	}
	l = M_CDR(l);
	goto next_loop_2;
      end_loop_1:
      end_1:;
	if ( !TRUEP(text_tail_qm))
	    goto end_loop_2;
	goto next_loop_1;
      end_loop_2:;
    }
    if ( !TRUEP(include_indentations_and_widths_qm) && 
	    (known_to_have_indentations_and_widths_qm || 
	    text_cell_line_justification_qm)) {
	indentation = FIX((SI_Long)0L);
	l_trailer_qm = Nil;
	l = text;
	text_element = Nil;
	next_l_qm = Nil;
      next_loop_3:
	text_element = CAR(l);
	next_l_qm = CDR(l);
	if (ATOM(text_element)) {
	    if (FIXNUMP(text_element)) {
		temp_1 = text_element;
		temp_3 = IFIX(indentation);
		indentation = text_element;
		temp_4 = FIXNUM_EQ(temp_1,FIX(temp_3));
	    }
	    else
		temp_4 = TRUEP(Nil);
	}
	else
	    temp_4 = EQ(CAR(text_element),Qline_width);
	if (temp_4) {
	    if ( !TRUEP(l_trailer_qm))
		text = next_l_qm;
	    else
		M_CDR(l_trailer_qm) = next_l_qm;
	    M_CDR(l) = Nil;
	    reclaim_slot_value_tree_1(l);
	}
	else
	    l_trailer_qm = l;
	if ( !TRUEP(next_l_qm))
	    goto end_loop_3;
	l = next_l_qm;
	goto next_loop_3;
      end_loop_3:;
    }
    return VALUES_4(text,width_of_longest_line,cursor_line_index_qm,
	    cursor_character_index_qm);
}

/* MAKE-TEXT-LINE-BUFFER */
Object make_text_line_buffer()
{
    x_note_fn_call(109,121);
    return obtain_text_string(get_text_line_buffer_limit());
}

/* GET-TEXT-LINE-BUFFER-LIMIT */
Object get_text_line_buffer_limit()
{
    x_note_fn_call(109,122);
    return VALUES_1(Maximum_suggested_length_for_wide_strings);
}

/* MAKE-BIGGER-LINE-BUFFER */
Object make_bigger_line_buffer(line_buffer,current_length_init,new_length_init)
    Object line_buffer, current_length_init, new_length_init;
{
    Object new_line_buffer, gensymed_symbol, gensymed_symbol_2;
    SI_Long current_length, new_length, arg, arg_1, arg_2, gensymed_symbol_1;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(109,123);
    current_length = IFIX(current_length_init);
    new_length = IFIX(new_length_init);
    new_line_buffer = obtain_text_string(FIX(new_length));
    if (EQ(line_buffer,new_line_buffer)) {
	if ((SI_Long)0L == current_length)
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
		    current_length : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = (SI_Long)0L;
		arg_1 = (SI_Long)0L;
		arg_2 = (SI_Long)0L + (current_length - (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(line_buffer,
			FIX((SI_Long)0L),new_line_buffer,FIX((SI_Long)0L),
			FIX(current_length - (SI_Long)0L));
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
	gensymed_symbol = line_buffer;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = new_line_buffer;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = current_length - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    reclaim_text_string(line_buffer);
    return VALUES_1(new_line_buffer);
}

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_index_of_change_qm, Qstar_line_index_of_change_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_character_index_of_change_qm, Qstar_character_index_of_change_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_index_past_deletion_qm, Qstar_line_index_past_deletion_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_character_index_past_deletion_qm, Qstar_character_index_past_deletion_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_string_to_insert_qm, Qstar_string_to_insert_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_text_string_to_insert_is_simple_qm, Qstar_text_string_to_insert_is_simple_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_character_index_in_string_to_insert_qm, Qstar_character_index_in_string_to_insert_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_buffer, Qstar_line_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_index, Qstar_line_index);

DEFINE_VARIABLE_WITH_SYMBOL(Star_character_index, Qstar_character_index);

DEFINE_VARIABLE_WITH_SYMBOL(Star_text_line, Qstar_text_line);

DEFINE_VARIABLE_WITH_SYMBOL(Star_text_line_is_simple_qm, Qstar_text_line_is_simple_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_length, Qstar_line_length);

DEFINE_VARIABLE_WITH_SYMBOL(Star_lost_space_at_end_of_line, Qstar_lost_space_at_end_of_line);

DEFINE_VARIABLE_WITH_SYMBOL(Star_this_text_tail_qm, Qstar_this_text_tail_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_next_text_tail_qm, Qstar_next_text_tail_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_current_indentation, Qstar_current_indentation);

DEFINE_VARIABLE_WITH_SYMBOL(Star_explicit_paragraph_or_newline_qm, Qstar_explicit_paragraph_or_newline_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_buffer_fill_pointer, Qstar_line_buffer_fill_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Star_line_buffer_limit, Qstar_line_buffer_limit);

/* REFORMAT-TEXT */
Object reformat_text varargs_1(int, n)
{
    Object text, text_box_format;
    Object width_for_cell_qm, put_in_indentations_and_widths_qm;
    Object text_tail_for_reformatting_only_for_change_qm;
    Object line_index_of_change_qm, character_index_of_change_qm;
    Object line_index_past_deletion_qm, character_index_past_deletion_qm;
    Object string_to_insert_qm, format_width_override_qm, text_cell_plist;
    Object allow_override_below_limit_p, star_line_index_of_change_qm;
    Object star_character_index_of_change_qm, star_line_index_past_deletion_qm;
    Object star_character_index_past_deletion_qm, star_string_to_insert_qm;
    Object star_text_string_to_insert_is_simple_qm;
    Object star_character_index_in_string_to_insert_qm, star_line_buffer;
    Object star_line_buffer_fill_pointer, star_line_buffer_limit;
    Object star_line_index, star_character_index, star_this_text_tail_qm;
    Object star_text_line, star_text_line_is_simple_qm, star_line_length;
    Object star_lost_space_at_end_of_line, star_next_text_tail_qm;
    Object star_current_indentation, star_explicit_paragraph_or_newline_qm;
    Declare_varargs_nonrelocating;
    Declare_special(20);
    Object result;

    x_note_fn_call(109,124);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    text_box_format = REQUIRED_ARG_nonrelocating();
    width_for_cell_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    put_in_indentations_and_widths_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_tail_for_reformatting_only_for_change_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    line_index_of_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_of_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    string_to_insert_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    format_width_override_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_cell_plist = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    allow_override_below_limit_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    star_line_index_of_change_qm = line_index_of_change_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Star_line_index_of_change_qm,Qstar_line_index_of_change_qm,star_line_index_of_change_qm,
	    19);
      star_character_index_of_change_qm = character_index_of_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Star_character_index_of_change_qm,Qstar_character_index_of_change_qm,star_character_index_of_change_qm,
	      18);
	star_line_index_past_deletion_qm = line_index_past_deletion_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Star_line_index_past_deletion_qm,Qstar_line_index_past_deletion_qm,star_line_index_past_deletion_qm,
		17);
	  star_character_index_past_deletion_qm = 
		  character_index_past_deletion_qm;
	  PUSH_SPECIAL_WITH_SYMBOL(Star_character_index_past_deletion_qm,Qstar_character_index_past_deletion_qm,star_character_index_past_deletion_qm,
		  16);
	    star_string_to_insert_qm = string_to_insert_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Star_string_to_insert_qm,Qstar_string_to_insert_qm,star_string_to_insert_qm,
		    15);
	      star_text_string_to_insert_is_simple_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Star_text_string_to_insert_is_simple_qm,Qstar_text_string_to_insert_is_simple_qm,star_text_string_to_insert_is_simple_qm,
		      14);
		star_character_index_in_string_to_insert_qm = 
			Star_string_to_insert_qm ? FIX((SI_Long)0L) : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Star_character_index_in_string_to_insert_qm,Qstar_character_index_in_string_to_insert_qm,star_character_index_in_string_to_insert_qm,
			13);
		  star_line_buffer = make_text_line_buffer();
		  PUSH_SPECIAL_WITH_SYMBOL(Star_line_buffer,Qstar_line_buffer,star_line_buffer,
			  12);
		    star_line_buffer_fill_pointer = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Star_line_buffer_fill_pointer,Qstar_line_buffer_fill_pointer,star_line_buffer_fill_pointer,
			    11);
		      star_line_buffer_limit = get_text_line_buffer_limit();
		      PUSH_SPECIAL_WITH_SYMBOL(Star_line_buffer_limit,Qstar_line_buffer_limit,star_line_buffer_limit,
			      10);
			star_line_index = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Star_line_index,Qstar_line_index,star_line_index,
				9);
			  star_character_index = FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Star_character_index,Qstar_character_index,star_character_index,
				  8);
			    star_this_text_tail_qm = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Star_this_text_tail_qm,Qstar_this_text_tail_qm,star_this_text_tail_qm,
				    7);
			      star_text_line = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Star_text_line,Qstar_text_line,star_text_line,
				      6);
				star_text_line_is_simple_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Star_text_line_is_simple_qm,Qstar_text_line_is_simple_qm,star_text_line_is_simple_qm,
					5);
				  star_line_length = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Star_line_length,Qstar_line_length,star_line_length,
					  4);
				    star_lost_space_at_end_of_line = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Star_lost_space_at_end_of_line,Qstar_lost_space_at_end_of_line,star_lost_space_at_end_of_line,
					    3);
				      star_next_text_tail_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Star_next_text_tail_qm,Qstar_next_text_tail_qm,star_next_text_tail_qm,
					      2);
					star_current_indentation = 
						FIX((SI_Long)0L);
					PUSH_SPECIAL_WITH_SYMBOL(Star_current_indentation,Qstar_current_indentation,star_current_indentation,
						1);
					  star_explicit_paragraph_or_newline_qm 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Star_explicit_paragraph_or_newline_qm,Qstar_explicit_paragraph_or_newline_qm,star_explicit_paragraph_or_newline_qm,
						  0);
					    result = reformat_text_1(text,
						    text_box_format,
						    width_for_cell_qm,
						    put_in_indentations_and_widths_qm,
						    text_tail_for_reformatting_only_for_change_qm,
						    format_width_override_qm,
						    text_cell_plist,
						    allow_override_below_limit_p);
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qab_font;            /* ab-font */

static Object array_constant_1;    /* # */

static Object Qimplied_paragraph;  /* implied-paragraph */

static Object list_constant_11;    /* # */

static Object Qcontext_carryover;  /* context-carryover */

static Object Qhyphen_added;       /* hyphen-added */

/* REFORMAT-TEXT-1 */
Object reformat_text_1(text,text_box_format,width_for_cell_qm,
	    put_in_indentations_and_widths_qm,
	    text_tail_for_reformatting_only_for_change_qm,
	    format_width_override_qm,text_cell_plist,
	    allow_override_below_limit_p)
    Object text, text_box_format, width_for_cell_qm;
    Object put_in_indentations_and_widths_qm;
    Object text_tail_for_reformatting_only_for_change_qm;
    Object format_width_override_qm, text_cell_plist;
    Object allow_override_below_limit_p;
{
    Object x_magnification_qm, temp, line_justification_qm, maximum_line_width;
    Object minimum_line_width, font_map, gensymed_symbol_4, ab_font;
    Object default_word_spacing, word_spacing, initial_line_index;
    Object initial_text_tail, reversed_new_text_segment;
    Object width_of_longest_new_line, current_indentation_for_new_lines;
    Object line_index_for_next_new_line;
    Object paragraph_or_newline_for_next_new_line_qm;
    Object indentation_for_next_new_line, indentation_for_turnover_lines;
    Object ok_to_break_qm, context_stack, number_of_adjustable_spaces_so_far;
    Object width_a_of_line_so_far, width_b_of_line_so_far;
    Object character_index_of_last_natural_break_qm;
    Object character_index_after_last_natural_break;
    Object last_natural_break_is_all_ordinary_spaces_qm;
    Object number_of_adjustable_spaces_up_to_last_natural_break;
    Object number_of_adjustable_spaces_through_last_natural_break;
    Object width_a_of_line_up_to_last_natural_break;
    Object width_b_of_line_up_to_last_natural_break;
    Object width_a_of_line_through_last_natural_break;
    Object width_b_of_line_through_last_natural_break;
    Object context_stack_at_last_natural_break_qm, get_character_qm;
    Object character_qm, text_break_case_qm, indentation_if_new_qm;
    Object context_carryover_qm, temp_2, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7, gensymed_symbol_8, gensymed_symbol_9, temp_3, l;
    Object symbol, ab_loop_list_;
    Object number_of_adjustable_spaces_up_to_natural_break;
    Object text_width_a_of_spaces, text_width_b_of_spaces;
    Object width_a_of_extra_indentation, width_b_of_extra_indentation;
    Object accumulating_extra_indentation_qm, a, b, width_of_line_so_far;
    Object incff_1_arg, position_1, next_tab_position, add_hyphen_qm;
    Object number_of_characters_in_natural_break, wide_string_bv16, s;
    Object source_string, source_start, source_end, destination_string;
    Object lost_spaces_element_qm, new_text_line, temp_6, temp_7, line_width;
    Object decff_1_arg, temp_8, aref_new_value_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, temp_1, line_measure;
    SI_Long character_index_of_natural_break, i, ab_loop_bind_, incff_1_arg_1;
    SI_Long temp_4, tab_width, bv16_length, aref_new_value, destination_start;
    SI_Long arg, arg_1, arg_2, decff_1_arg_1;
    char temp_5;
    Object result;

    x_note_fn_call(109,125);
    x_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qx_magnification) : Nil;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
    temp = format_width_override_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    gensymed_symbol = IFIX(temp);
    if (format_width_override_qm && allow_override_below_limit_p) {
	temp = FIXNUM_ADD(ISVREF(text_box_format,(SI_Long)27L),
		ISVREF(text_box_format,(SI_Long)29L));
	gensymed_symbol_1 = IFIX(FIXNUM_MIN(temp,format_width_override_qm));
    }
    else
	gensymed_symbol_1 = IFIX(ISVREF(text_box_format,(SI_Long)41L));
    temp = format_width_override_qm;
    if (temp);
    else
	temp = ISVREF(text_box_format,(SI_Long)42L);
    gensymed_symbol_2 = IFIX(temp);
    temp = width_for_cell_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(temp);
    gensymed_symbol_2 = MIN(gensymed_symbol_2,gensymed_symbol_3);
    temp_1 = MAX(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = MAX(temp_1,gensymed_symbol_2);
    gensymed_symbol_1 = IFIX(Maximum_text_box_width_or_height);
    gensymed_symbol = MIN(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol_1 = IFIX(ISVREF(text_box_format,(SI_Long)27L));
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)29L));
    line_measure = gensymed_symbol - gensymed_symbol_1 - gensymed_symbol_2;
    line_justification_qm = 
	    get_text_cell_line_justification(text_box_format,text_cell_plist);
    maximum_line_width = x_magnification_qm ? 
	    inverse_magnify(FIX(line_measure),x_magnification_qm) : 
	    FIX(line_measure);
    minimum_line_width = EQ(line_justification_qm,Qjustified) ? 
	    maximum_line_width : FIX(IFIX(maximum_line_width) * 
	    (SI_Long)154L + (SI_Long)128L >>  -  - (SI_Long)8L);
    font_map = ISVREF(text_box_format,(SI_Long)22L);
    gensymed_symbol_4 = CAR(font_map);
    ab_font = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_4),
	    Qab_font);
    default_word_spacing = ISVREF(text_box_format,(SI_Long)34L);
    word_spacing = default_word_spacing;
    initial_line_index = Star_line_index_of_change_qm;
    if (initial_line_index);
    else
	initial_line_index = FIX((SI_Long)1L);
    initial_text_tail = text_tail_for_reformatting_only_for_change_qm;
    if (initial_text_tail);
    else
	initial_text_tail = text;
    reversed_new_text_segment = Nil;
    width_of_longest_new_line = FIX((SI_Long)0L);
    current_indentation_for_new_lines = Nil;
    line_index_for_next_new_line = Nil;
    paragraph_or_newline_for_next_new_line_qm = Nil;
    indentation_for_next_new_line = Nil;
    indentation_for_turnover_lines = Nil;
    ok_to_break_qm = Nil;
    context_stack = Nil;
    number_of_adjustable_spaces_so_far = FIX((SI_Long)0L);
    width_a_of_line_so_far = Nil;
    width_b_of_line_so_far = Nil;
    character_index_of_last_natural_break_qm = Nil;
    character_index_after_last_natural_break = Nil;
    last_natural_break_is_all_ordinary_spaces_qm = Nil;
    number_of_adjustable_spaces_up_to_last_natural_break = Nil;
    number_of_adjustable_spaces_through_last_natural_break = Nil;
    width_a_of_line_up_to_last_natural_break = Nil;
    width_b_of_line_up_to_last_natural_break = Nil;
    width_a_of_line_through_last_natural_break = Nil;
    width_b_of_line_through_last_natural_break = Nil;
    context_stack_at_last_natural_break_qm = Nil;
    get_character_qm = T;
    character_qm = Nil;
    text_break_case_qm = Nil;
    indentation_if_new_qm = Nil;
    context_carryover_qm = Nil;
    result = get_next_text_line(initial_text_tail);
    MVS_7(result,gensymed_symbol_4,gensymed_symbol_5,gensymed_symbol_6,
	    gensymed_symbol_7,gensymed_symbol_8,temp,gensymed_symbol_9);
    context_carryover_qm = gensymed_symbol_9;
    indentation_if_new_qm = gensymed_symbol_8;
    Star_next_text_tail_qm = gensymed_symbol_7;
    Star_lost_space_at_end_of_line = gensymed_symbol_6;
    Star_line_length = gensymed_symbol_5;
    Star_text_line = gensymed_symbol_4;
    Star_text_line_is_simple_qm = Nil;
    if (IFIX(initial_line_index) > (SI_Long)1L && 
	    (Star_line_index_past_deletion_qm || (Star_string_to_insert_qm 
	    ? Star_string_to_insert_qm && 
	    string_eq_w(Star_string_to_insert_qm,array_constant_1) : 
	    TRUEP(Nil)))) {
	initial_line_index = FIXNUM_SUB1(initial_line_index);
	initial_text_tail = find_text_tail_for_line(text,initial_line_index);
	result = get_next_text_line(initial_text_tail);
	MVS_7(result,gensymed_symbol_4,gensymed_symbol_5,gensymed_symbol_6,
		gensymed_symbol_7,gensymed_symbol_8,temp,gensymed_symbol_9);
	context_carryover_qm = gensymed_symbol_9;
	indentation_if_new_qm = gensymed_symbol_8;
	Star_next_text_tail_qm = gensymed_symbol_7;
	Star_lost_space_at_end_of_line = gensymed_symbol_6;
	Star_line_length = gensymed_symbol_5;
	Star_text_line = gensymed_symbol_4;
	Star_text_line_is_simple_qm = Nil;
    }
    l = text;
  next_loop:
    if (EQ(l,initial_text_tail))
	goto end_loop;
    if (FIXNUMP(CAR(l)))
	Star_current_indentation = CAR(l);
    l = CDR(l);
    goto next_loop;
  end_loop:;
    current_indentation_for_new_lines = Star_current_indentation;
    if (indentation_if_new_qm)
	Star_current_indentation = indentation_if_new_qm;
    indentation_for_turnover_lines = EQ(line_justification_qm,Qcenter) || 
	    EQ(line_justification_qm,Qright) ? FIX((SI_Long)0L) : 
	    IFIX(initial_line_index) == (SI_Long)1L ? 
	    ISVREF(text_box_format,(SI_Long)38L) : Star_current_indentation;
    if (context_carryover_qm) {
	symbol = Nil;
	ab_loop_list_ = context_carryover_qm;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	context_stack = slot_value_cons_1(symbol,context_stack);
	goto next_loop_1;
      end_loop_1:;
    }
    Star_line_index = initial_line_index;
    Star_this_text_tail_qm = initial_text_tail;
    line_index_for_next_new_line = initial_line_index;
    paragraph_or_newline_for_next_new_line_qm = IFIX(initial_line_index) 
	    == (SI_Long)1L ? Qimplied_paragraph : Nil;
    indentation_for_next_new_line = IFIX(initial_line_index) == 
	    (SI_Long)1L ? (EQ(line_justification_qm,Qcenter) || 
	    EQ(line_justification_qm,Qright) ? FIX((SI_Long)0L) : 
	    ISVREF(text_box_format,(SI_Long)37L)) : 
	    indentation_for_turnover_lines;
    width_a_of_line_so_far = indentation_for_next_new_line;
    width_b_of_line_so_far = FIX((SI_Long)128L);
  next_loop_2:
    if (get_character_qm) {
	character_qm = get_character_if_any_for_running_text();
	text_break_case_qm = character_qm ? text_break_p(character_qm) : Qnil;
    }
    ok_to_break_qm = Nil;
    if ((text_break_case_qm || character_qm && IFIX(character_qm) == 
	    (SI_Long)8205L ||  !TRUEP(character_qm)) && ( 
	    !TRUEP(character_index_of_last_natural_break_qm) || 
	    FIXNUM_LE(width_a_of_line_so_far,maximum_line_width))) {
	gensymed_symbol = IFIX(Star_line_buffer_fill_pointer);
	gensymed_symbol_1 = text_break_case_qm ? (SI_Long)1L : (SI_Long)0L;
	character_index_of_natural_break = gensymed_symbol - gensymed_symbol_1;
	number_of_adjustable_spaces_up_to_natural_break = 
		number_of_adjustable_spaces_so_far;
	text_width_a_of_spaces = Nil;
	text_width_b_of_spaces = Nil;
	width_a_of_extra_indentation = Nil;
	width_b_of_extra_indentation = Nil;
	ok_to_break_qm = T;
	text_width_a_of_spaces = FIX((SI_Long)0L);
	text_width_b_of_spaces = FIX((SI_Long)128L);
	width_a_of_extra_indentation = FIX((SI_Long)0L);
	width_b_of_extra_indentation = FIX((SI_Long)128L);
	if ( !TRUEP(character_qm))
	    goto end_loop_2;
      next_loop_3:
	if ( !TRUEP(character_qm) || ordinary_space_p(character_qm))
	    number_of_adjustable_spaces_so_far = 
		    FIXNUM_ADD1(number_of_adjustable_spaces_so_far);
	else {
	    if (character_qm && IFIX(character_qm) == (SI_Long)8205L)
		ok_to_break_qm = Nil;
	    if (FIXNUM_EQ(number_of_adjustable_spaces_so_far,
		    FIXNUM_SUB1(Star_line_buffer_fill_pointer))) {
		number_of_adjustable_spaces_so_far = FIX((SI_Long)0L);
		number_of_adjustable_spaces_up_to_natural_break = 
			number_of_adjustable_spaces_so_far;
	    }
	}
	if (paragraph_or_newline_for_next_new_line_qm &&  
		!TRUEP(character_index_of_last_natural_break_qm)) {
	    i = EQ(paragraph_or_newline_for_next_new_line_qm,
		    Qimplied_paragraph) ? (SI_Long)0L : (SI_Long)1L;
	    ab_loop_bind_ = IFIX(Star_line_buffer_fill_pointer);
	  next_loop_4:
	    if (i >= ab_loop_bind_)
		goto end_loop_3;
	    if ( 
		    !TRUEP(wide_character_member(FIX(UBYTE_16_ISAREF_1(Star_line_buffer,
		    i)),list_constant_11))) {
		accumulating_extra_indentation_qm = Nil;
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_3:
	    accumulating_extra_indentation_qm = T;
	    goto end_1;
	    accumulating_extra_indentation_qm = Qnil;
	  end_1:;
	}
	else
	    accumulating_extra_indentation_qm = Nil;
	if (character_qm && IFIX(character_qm) == (SI_Long)9L) {
	    a = width_a_of_line_so_far;
	    b = width_b_of_line_so_far;
	    width_of_line_so_far = a;
	    incff_1_arg = text_width_a_of_spaces;
	    a = FIXNUM_ADD(a,incff_1_arg);
	    incff_1_arg_1 = IFIX(text_width_b_of_spaces) - (SI_Long)128L;
	    temp_4 = IFIX(b) + incff_1_arg_1;
	    b = FIX(temp_4);
	    if (IFIX(b) < (SI_Long)0L) {
		temp_4 = IFIX(b) + (SI_Long)256L;
		b = FIX(temp_4);
		a = FIXNUM_SUB1(a);
	    }
	    else if (IFIX(b) >= (SI_Long)256L) {
		temp_4 = IFIX(b) - (SI_Long)256L;
		b = FIX(temp_4);
		a = FIXNUM_ADD1(a);
	    }
	    position_1 = a;
	    tab_width = (SI_Long)9600L + (SI_Long)128L >>  -  - (SI_Long)8L;
	    next_tab_position = add(minus(position_1,mod(position_1,
		    FIX(tab_width))),FIX(tab_width));
	    text_width_a_of_spaces = FIXNUM_MINUS(next_tab_position,
		    width_of_line_so_far);
	    text_width_b_of_spaces = FIX((SI_Long)128L);
	    if (accumulating_extra_indentation_qm) {
		width_a_of_extra_indentation = text_width_a_of_spaces;
		width_b_of_extra_indentation = text_width_b_of_spaces;
	    }
	}
	else {
	    gensymed_symbol = IFIX(text_width_b_of_spaces);
	    if (character_qm && (IFIX(character_qm) == (SI_Long)8203L || 
		    IFIX(character_qm) == (SI_Long)8205L))
		gensymed_symbol_1 = (SI_Long)0L;
	    else if (accumulating_extra_indentation_qm) {
		gensymed_symbol_4 = 
			FIXNUM_ADD(width_b_of_extra_indentation,
			default_word_spacing);
		incff_1_arg_1 = IFIX(gensymed_symbol_4) >>  -  - (SI_Long)8L;
		temp_4 = IFIX(width_a_of_extra_indentation) + incff_1_arg_1;
		width_a_of_extra_indentation = FIX(temp_4);
		gensymed_symbol_1 = IFIX(gensymed_symbol_4) & (SI_Long)255L;
		width_b_of_extra_indentation = FIX(gensymed_symbol_1);
		gensymed_symbol_1 = IFIX(default_word_spacing);
	    }
	    else
		gensymed_symbol_1 = IFIX(word_spacing);
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    incff_1_arg_1 = gensymed_symbol >>  -  - (SI_Long)8L;
	    temp_4 = IFIX(text_width_a_of_spaces) + incff_1_arg_1;
	    text_width_a_of_spaces = FIX(temp_4);
	    gensymed_symbol = gensymed_symbol & (SI_Long)255L;
	    text_width_b_of_spaces = FIX(gensymed_symbol);
	}
	character_qm = get_character_if_any_for_running_text();
	text_break_case_qm = character_qm ? text_break_p(character_qm) : Qnil;
	if ( !(text_break_case_qm || character_qm && IFIX(character_qm) == 
		(SI_Long)8205L))
	    goto end_loop_2;
	goto next_loop_3;
      end_loop_2:
	incff_1_arg = width_a_of_extra_indentation;
	indentation_for_turnover_lines = 
		FIXNUM_ADD(indentation_for_turnover_lines,incff_1_arg);
	if (ok_to_break_qm) {
	    character_index_of_last_natural_break_qm = 
		    FIX(character_index_of_natural_break);
	    character_index_after_last_natural_break =  
		    !TRUEP(character_qm) ? Star_line_buffer_fill_pointer : 
		    FIXNUM_SUB1(Star_line_buffer_fill_pointer);
	    i = character_index_of_natural_break;
	    ab_loop_bind_ = IFIX(character_index_after_last_natural_break);
	  next_loop_5:
	    if (i >= ab_loop_bind_)
		goto end_loop_4;
	    if ( 
		    !TRUEP(ordinary_space_p(FIX(UBYTE_16_ISAREF_1(Star_line_buffer,
		    i))))) {
		last_natural_break_is_all_ordinary_spaces_qm = Nil;
		goto end_2;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_4:
	    last_natural_break_is_all_ordinary_spaces_qm = T;
	    goto end_2;
	    last_natural_break_is_all_ordinary_spaces_qm = Qnil;
	  end_2:;
	    if (FIXNUM_EQ(number_of_adjustable_spaces_so_far,
		    character_index_after_last_natural_break)) {
		number_of_adjustable_spaces_so_far = FIX((SI_Long)0L);
		number_of_adjustable_spaces_up_to_natural_break = 
			number_of_adjustable_spaces_so_far;
	    }
	    number_of_adjustable_spaces_up_to_last_natural_break = 
		    number_of_adjustable_spaces_up_to_natural_break;
	    number_of_adjustable_spaces_through_last_natural_break = 
		    number_of_adjustable_spaces_so_far;
	    width_a_of_line_up_to_last_natural_break = width_a_of_line_so_far;
	    width_b_of_line_up_to_last_natural_break = width_b_of_line_so_far;
	}
	incff_1_arg = text_width_a_of_spaces;
	width_a_of_line_so_far = FIXNUM_ADD(width_a_of_line_so_far,
		incff_1_arg);
	incff_1_arg_1 = IFIX(text_width_b_of_spaces) - (SI_Long)128L;
	temp_4 = IFIX(width_b_of_line_so_far) + incff_1_arg_1;
	width_b_of_line_so_far = FIX(temp_4);
	if (IFIX(width_b_of_line_so_far) < (SI_Long)0L) {
	    temp_4 = IFIX(width_b_of_line_so_far) + (SI_Long)256L;
	    width_b_of_line_so_far = FIX(temp_4);
	    width_a_of_line_so_far = FIXNUM_SUB1(width_a_of_line_so_far);
	}
	else if (IFIX(width_b_of_line_so_far) >= (SI_Long)256L) {
	    temp_4 = IFIX(width_b_of_line_so_far) - (SI_Long)256L;
	    width_b_of_line_so_far = FIX(temp_4);
	    width_a_of_line_so_far = FIXNUM_ADD1(width_a_of_line_so_far);
	}
	if (ok_to_break_qm) {
	    width_a_of_line_through_last_natural_break = 
		    width_a_of_line_so_far;
	    width_b_of_line_through_last_natural_break = 
		    width_b_of_line_so_far;
	    if (context_stack_at_last_natural_break_qm)
		reclaim_slot_value_tree_1(context_stack_at_last_natural_break_qm);
	    if (context_stack)
		context_stack_at_last_natural_break_qm = 
			copy_tree_using_slot_value_conses_1(context_stack);
	}
    }
    if ( !TRUEP(character_qm) && (IFIX(Star_line_buffer_fill_pointer) > 
	    (SI_Long)0L ||  !TRUEP(Star_explicit_paragraph_or_newline_qm) 
	    || IFIX(line_index_for_next_new_line) == (SI_Long)1L) || 
	    FIXNUM_GT(width_a_of_line_so_far,maximum_line_width) && 
	    (ok_to_break_qm || (character_index_of_last_natural_break_qm ? 
	    TRUEP(text_break_case_qm) : TRUEP(Nil)))) {
	add_hyphen_qm =  !TRUEP(character_index_of_last_natural_break_qm) 
		|| IFIX(width_a_of_line_up_to_last_natural_break) + 
		(IFIX(FIXNUM_ADD(width_b_of_line_up_to_last_natural_break,
		FIXNUM_TIMES(FIXNUM_MINUS(ISVREF(text_box_format,
		(SI_Long)36L),word_spacing),
		number_of_adjustable_spaces_up_to_last_natural_break))) >> 
		 -  - (SI_Long)8L) > IFIX(minimum_line_width) ? Nil : Nil;
	if ( !TRUEP(add_hyphen_qm)) {
	    number_of_characters_in_natural_break = 
		    FIXNUM_MINUS(character_index_after_last_natural_break,
		    character_index_of_last_natural_break_qm);
	    if ( !TRUEP(last_natural_break_is_all_ordinary_spaces_qm) ||  
		    !(IFIX(FIXNUM_MINUS(character_index_after_last_natural_break,
		    character_index_of_last_natural_break_qm)) == 
			(SI_Long)1L)) {
		if (last_natural_break_is_all_ordinary_spaces_qm)
		    temp = number_of_characters_in_natural_break;
		else {
		    wide_string_bv16 = 
			    allocate_byte_vector_16(FIX(IFIX(number_of_characters_in_natural_break) 
			    + (SI_Long)3L));
		    bv16_length = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		    temp_4 = bv16_length - (SI_Long)2L;
		    aref_new_value = 
			    IFIX(number_of_characters_in_natural_break) & 
			    (SI_Long)65535L;
		    UBYTE_16_ISASET_1(wide_string_bv16,temp_4,aref_new_value);
		    temp_4 = bv16_length - (SI_Long)1L;
		    aref_new_value = (SI_Long)57344L | 
			    IFIX(number_of_characters_in_natural_break) >> 
			     -  - (SI_Long)16L;
		    UBYTE_16_ISASET_1(wide_string_bv16,temp_4,aref_new_value);
		    UBYTE_16_ISASET_1(wide_string_bv16,
			    IFIX(number_of_characters_in_natural_break),
			    (SI_Long)0L);
		    s = wide_string_bv16;
		    source_string = Star_line_buffer;
		    source_start = character_index_of_last_natural_break_qm;
		    source_end = 
			    FIXNUM_ADD(character_index_of_last_natural_break_qm,
			    number_of_characters_in_natural_break);
		    destination_string = s;
		    destination_start = (SI_Long)0L;
		    if (EQ(source_string,destination_string)) {
			if (FIXNUM_EQ(source_start,source_end))
			    temp_5 = TRUEP(T);
			else {
			    temp_5 = IFIX(source_start) < 
				    destination_start ? destination_start 
				    < IFIX(source_end) : TRUEP(Qnil);
			    if (temp_5);
			    else {
				arg = destination_start;
				arg_1 = IFIX(source_start);
				arg_2 = destination_start + 
					IFIX(FIXNUM_MINUS(source_end,
					source_start));
				temp_5 = arg < arg_1 ? arg_1 < arg_2 : 
					TRUEP(Qnil);
			    }
			    if (temp_5) {
				copy_byte_vector_16_portion_carefully(source_string,
					source_start,destination_string,
					FIX(destination_start),
					FIXNUM_MINUS(source_end,source_start));
				temp_5 = TRUEP(T);
			    }
			    else
				temp_5 = TRUEP(Qnil);
			}
		    }
		    else
			temp_5 = TRUEP(Nil);
		    if (temp_5);
		    else {
			gensymed_symbol_4 = source_string;
			gensymed_symbol = IFIX(source_start);
			gensymed_symbol_5 = destination_string;
			gensymed_symbol_1 = destination_start;
			gensymed_symbol_2 = IFIX(FIXNUM_MINUS(source_end,
				source_start));
			INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
				gensymed_symbol,
				UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
				gensymed_symbol_1,gensymed_symbol_2);
		    }
		    temp = s;
		}
		lost_spaces_element_qm = make_lost_spaces_text_element(temp);
	    }
	    else
		lost_spaces_element_qm = Nil;
	}
	else
	    lost_spaces_element_qm = Nil;
	new_text_line = obtain_text_string(add_hyphen_qm ? 
		FIXNUM_ADD1(character_index_of_last_natural_break_qm) : 
		character_index_of_last_natural_break_qm);
	if (EQ(line_justification_qm,Qjustified)) {
	    temp_6 = ISVREF(text_box_format,(SI_Long)35L);
	    temp_7 = ISVREF(text_box_format,(SI_Long)36L);
	    temp = l_round(FIX((line_measure << (SI_Long)8L) - 
		    ((IFIX(width_a_of_line_up_to_last_natural_break) << 
		    (SI_Long)8L) + 
		    IFIX(width_b_of_line_up_to_last_natural_break) + 
		    (SI_Long)-128L)),number_of_adjustable_spaces_so_far);
	    temp = FIXNUM_MIN(temp_7,temp);
	    word_spacing = FIXNUM_MAX(temp_6,temp);
	}
	else
	    word_spacing = default_word_spacing;
	if (EQ(Star_line_buffer,new_text_line)) {
	    if ((SI_Long)0L == IFIX(character_index_of_last_natural_break_qm))
		temp_5 = TRUEP(T);
	    else {
		temp_5 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
			IFIX(character_index_of_last_natural_break_qm) : 
			TRUEP(Qnil);
		if (temp_5);
		else {
		    arg = (SI_Long)0L;
		    arg_1 = (SI_Long)0L;
		    arg_2 = (SI_Long)0L + 
			    (IFIX(character_index_of_last_natural_break_qm) 
			    - (SI_Long)0L);
		    temp_5 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		}
		if (temp_5) {
		    copy_byte_vector_16_portion_carefully(Star_line_buffer,
			    FIX((SI_Long)0L),new_text_line,
			    FIX((SI_Long)0L),
			    FIX(IFIX(character_index_of_last_natural_break_qm) 
			    - (SI_Long)0L));
		    temp_5 = TRUEP(T);
		}
		else
		    temp_5 = TRUEP(Qnil);
	    }
	}
	else
	    temp_5 = TRUEP(Nil);
	if (temp_5);
	else {
	    gensymed_symbol_4 = Star_line_buffer;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_5 = new_text_line;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = 
		    IFIX(character_index_of_last_natural_break_qm) - 
		    (SI_Long)0L;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	}
	if (add_hyphen_qm)
	    UBYTE_16_ISASET_1(new_text_line,
		    IFIX(character_index_of_last_natural_break_qm),
		    (SI_Long)45L);
	if (put_in_indentations_and_widths_qm ||  
		!FIXNUM_EQ(indentation_for_next_new_line,
		current_indentation_for_new_lines))
	    reversed_new_text_segment = 
		    slot_value_cons_1(indentation_for_next_new_line,
		    reversed_new_text_segment);
	current_indentation_for_new_lines = indentation_for_next_new_line;
	if (context_stack)
	    reversed_new_text_segment = 
		    slot_value_cons_1(slot_value_cons_1(Qcontext_carryover,
		    copy_tree_using_slot_value_conses_1(context_stack)),
		    reversed_new_text_segment);
	if (IFIX(number_of_adjustable_spaces_up_to_last_natural_break) > 
		(SI_Long)0L &&  !FIXNUM_EQ(word_spacing,default_word_spacing))
	    reversed_new_text_segment = 
		    slot_value_cons_1(slot_value_cons_1(Qword_spacing,
		    word_spacing),reversed_new_text_segment);
	if (lost_spaces_element_qm || add_hyphen_qm) {
	    temp = lost_spaces_element_qm;
	    if (temp);
	    else
		temp = slot_value_cons_1(Qhyphen_added,Nil);
	    reversed_new_text_segment = slot_value_cons_1(temp,
		    reversed_new_text_segment);
	}
	line_width = x_magnification_qm ? 
		FIX((IFIX(FIXNUM_TIMES(width_a_of_line_up_to_last_natural_break,
		x_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L) 
		+ (((IFIX(width_b_of_line_up_to_last_natural_break) - 
		(SI_Long)128L) * IFIX(x_magnification_qm) + (SI_Long)128L 
		>>  -  - (SI_Long)8L) + (SI_Long)128L >>  -  - 
		(SI_Long)8L)) : width_a_of_line_up_to_last_natural_break;
	if (FIXNUM_GT(line_width,width_of_longest_new_line))
	    width_of_longest_new_line = line_width;
	if (put_in_indentations_and_widths_qm)
	    reversed_new_text_segment = 
		    slot_value_cons_1(slot_value_cons_1(Qline_width,
		    line_width),reversed_new_text_segment);
	reversed_new_text_segment = slot_value_cons_1(new_text_line,
		reversed_new_text_segment);
	if (EQ(Star_line_buffer,Star_line_buffer)) {
	    if (FIXNUM_EQ(character_index_after_last_natural_break,
		    Star_line_buffer_fill_pointer))
		temp_5 = TRUEP(T);
	    else {
		temp_5 = IFIX(character_index_after_last_natural_break) < 
			(SI_Long)0L ? (SI_Long)0L < 
			IFIX(Star_line_buffer_fill_pointer) : TRUEP(Qnil);
		if (temp_5);
		else {
		    arg = (SI_Long)0L;
		    arg_1 = IFIX(character_index_after_last_natural_break);
		    arg_2 = (SI_Long)0L + 
			    IFIX(FIXNUM_MINUS(Star_line_buffer_fill_pointer,
			    character_index_after_last_natural_break));
		    temp_5 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		}
		if (temp_5) {
		    copy_byte_vector_16_portion_carefully(Star_line_buffer,
			    character_index_after_last_natural_break,
			    Star_line_buffer,FIX((SI_Long)0L),
			    FIXNUM_MINUS(Star_line_buffer_fill_pointer,
			    character_index_after_last_natural_break));
		    temp_5 = TRUEP(T);
		}
		else
		    temp_5 = TRUEP(Qnil);
	    }
	}
	else
	    temp_5 = TRUEP(Nil);
	if (temp_5);
	else {
	    gensymed_symbol_4 = Star_line_buffer;
	    gensymed_symbol = IFIX(character_index_after_last_natural_break);
	    gensymed_symbol_5 = Star_line_buffer;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = 
		    IFIX(FIXNUM_MINUS(Star_line_buffer_fill_pointer,
		    character_index_after_last_natural_break));
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		    gensymed_symbol,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_5),
		    gensymed_symbol_1,gensymed_symbol_2);
	}
	Star_line_buffer_fill_pointer = 
		FIXNUM_MINUS(Star_line_buffer_fill_pointer,
		character_index_after_last_natural_break);
	line_index_for_next_new_line = 
		FIXNUM_ADD1(line_index_for_next_new_line);
	paragraph_or_newline_for_next_new_line_qm = Nil;
	indentation_for_next_new_line = indentation_for_turnover_lines;
	if (text_tail_for_reformatting_only_for_change_qm) {
	    temp_6 = Star_line_index;
	    temp = Star_line_index_past_deletion_qm;
	    if (temp);
	    else
		temp = Star_line_index_of_change_qm;
	    temp_5 = NUM_GT(temp_6,temp);
	}
	else
	    temp_5 = TRUEP(Nil);
	if (temp_5 ?  !TRUEP(character_qm) && 
		Star_explicit_paragraph_or_newline_qm && 
		IFIX(Star_line_buffer_fill_pointer) == (SI_Long)0L || 
		FIXNUM_EQ(indentation_for_next_new_line,
		Star_current_indentation) && character_qm && 
		FIXNUM_EQ(Star_line_buffer_fill_pointer,
		Star_character_index) : TRUEP(Nil))
	    goto end_loop_5;
	decff_1_arg = number_of_adjustable_spaces_through_last_natural_break;
	number_of_adjustable_spaces_so_far = 
		FIXNUM_MINUS(number_of_adjustable_spaces_so_far,decff_1_arg);
	decff_1_arg = width_a_of_line_through_last_natural_break;
	width_a_of_line_so_far = FIXNUM_MINUS(width_a_of_line_so_far,
		decff_1_arg);
	decff_1_arg_1 = IFIX(width_b_of_line_through_last_natural_break) - 
		(SI_Long)128L;
	temp_4 = IFIX(width_b_of_line_so_far) - decff_1_arg_1;
	width_b_of_line_so_far = FIX(temp_4);
	if (IFIX(width_b_of_line_so_far) < (SI_Long)0L) {
	    temp_4 = IFIX(width_b_of_line_so_far) + (SI_Long)256L;
	    width_b_of_line_so_far = FIX(temp_4);
	    width_a_of_line_so_far = FIXNUM_SUB1(width_a_of_line_so_far);
	}
	else if (IFIX(width_b_of_line_so_far) >= (SI_Long)256L) {
	    temp_4 = IFIX(width_b_of_line_so_far) - (SI_Long)256L;
	    width_b_of_line_so_far = FIX(temp_4);
	    width_a_of_line_so_far = FIXNUM_ADD1(width_a_of_line_so_far);
	}
	gensymed_symbol = IFIX(width_b_of_line_so_far) + 
		(IFIX(indentation_for_turnover_lines) << (SI_Long)8L);
	incff_1_arg_1 = gensymed_symbol >>  -  - (SI_Long)8L;
	temp_4 = IFIX(width_a_of_line_so_far) + incff_1_arg_1;
	width_a_of_line_so_far = FIX(temp_4);
	gensymed_symbol = gensymed_symbol & (SI_Long)255L;
	width_b_of_line_so_far = FIX(gensymed_symbol);
	character_index_of_last_natural_break_qm = Nil;
    }
    if ( !TRUEP(character_qm)) {
	character_index_of_last_natural_break_qm = Nil;
	if (IFIX(Star_line_buffer_fill_pointer) > (SI_Long)0L)
	    get_character_qm = Nil;
	else if ( !TRUEP(Star_explicit_paragraph_or_newline_qm)) {
	    Star_this_text_tail_qm = Star_next_text_tail_qm;
	    temp_8 = FIXNUM_ADD1(Star_line_index);
	    Star_line_index = temp_8;
	    goto end_loop_5;
	}
	else {
	    temp_8 = Star_line_buffer;
	    if (EQ(Star_explicit_paragraph_or_newline_qm,Qparagraph))
		aref_new_value_1 = FIX((SI_Long)8233L);
	    else if (EQ(Star_explicit_paragraph_or_newline_qm,Qnewline))
		aref_new_value_1 = FIX((SI_Long)8232L);
	    else if (EQ(Star_explicit_paragraph_or_newline_qm,Qlinefeed))
		aref_new_value_1 = FIX((SI_Long)10L);
	    else
		aref_new_value_1 = FIX((SI_Long)13L);
	    UBYTE_16_ISASET_1(temp_8,(SI_Long)0L,IFIX(aref_new_value_1));
	    Star_line_buffer_fill_pointer = FIX((SI_Long)1L);
	    paragraph_or_newline_for_next_new_line_qm = 
		    Star_explicit_paragraph_or_newline_qm;
	    indentation_for_next_new_line = EQ(line_justification_qm,
		    Qcenter) || EQ(line_justification_qm,Qright) ? 
		    FIX((SI_Long)0L) : 
		    paragraph_or_newline_for_next_new_line_qm ? 
		    (EQ(paragraph_or_newline_for_next_new_line_qm,
		    Qnewline) || 
		    EQ(paragraph_or_newline_for_next_new_line_qm,Qreturn) 
		    || EQ(paragraph_or_newline_for_next_new_line_qm,
		    Qlinefeed) ? FIX((SI_Long)0L) : ISVREF(text_box_format,
		    (SI_Long)37L)) : indentation_for_turnover_lines;
	    indentation_for_turnover_lines = EQ(line_justification_qm,
		    Qcenter) || EQ(line_justification_qm,Qright) ? 
		    FIX((SI_Long)0L) : ISVREF(text_box_format,(SI_Long)38L);
	    width_a_of_line_so_far = indentation_for_next_new_line;
	    width_b_of_line_so_far = FIX((SI_Long)128L);
	    get_character_qm = T;
	}
    }
    else if (text_break_case_qm)
	get_character_qm = Nil;
    else if (newline_p(character_qm))
	get_character_qm = T;
    else if (Nil);
    else {
	if (IFIX(Star_line_buffer_fill_pointer) > (SI_Long)2L && 
		UBYTE_16_ISAREF_1(Star_line_buffer,
		IFIX(Star_line_buffer_fill_pointer) - (SI_Long)2L) == 
		(SI_Long)45L && 
		alpha_numeric_p(FIX(UBYTE_16_ISAREF_1(Star_line_buffer,
		IFIX(Star_line_buffer_fill_pointer) - (SI_Long)3L))) && 
		alpha_numeric_p(character_qm) && ( 
		!TRUEP(character_index_of_last_natural_break_qm) || 
		FIXNUM_LE(width_a_of_line_so_far,maximum_line_width))) {
	    character_index_of_last_natural_break_qm = 
		    FIXNUM_SUB1(Star_line_buffer_fill_pointer);
	    character_index_after_last_natural_break = 
		    character_index_of_last_natural_break_qm;
	    last_natural_break_is_all_ordinary_spaces_qm = T;
	    number_of_adjustable_spaces_up_to_last_natural_break = 
		    number_of_adjustable_spaces_so_far;
	    number_of_adjustable_spaces_through_last_natural_break = 
		    number_of_adjustable_spaces_so_far;
	    width_a_of_line_up_to_last_natural_break = width_a_of_line_so_far;
	    width_b_of_line_up_to_last_natural_break = width_b_of_line_so_far;
	    width_a_of_line_through_last_natural_break = 
		    width_a_of_line_so_far;
	    width_b_of_line_through_last_natural_break = 
		    width_b_of_line_so_far;
	    if (context_stack_at_last_natural_break_qm)
		reclaim_slot_value_tree_1(context_stack_at_last_natural_break_qm);
	    context_stack_at_last_natural_break_qm = 
		    copy_tree_using_slot_value_conses_1(context_stack);
	}
	temp = width_b_of_line_so_far;
	gensymed_symbol_4 = FIXNUM_ADD(temp,
		get_unicode_set_width_as_text_width(character_qm,ab_font));
	incff_1_arg_1 = IFIX(gensymed_symbol_4) >>  -  - (SI_Long)8L;
	temp_4 = IFIX(width_a_of_line_so_far) + incff_1_arg_1;
	width_a_of_line_so_far = FIX(temp_4);
	gensymed_symbol = IFIX(gensymed_symbol_4) & (SI_Long)255L;
	width_b_of_line_so_far = FIX(gensymed_symbol);
	get_character_qm = T;
    }
    goto next_loop_2;
  end_loop_5:
    reclaim_text_string(Star_line_buffer);
    if (context_stack)
	reclaim_slot_value_tree_1(context_stack);
    if (context_stack_at_last_natural_break_qm)
	reclaim_slot_value_tree_1(context_stack_at_last_natural_break_qm);
    temp = nreverse(reversed_new_text_segment);
    return VALUES_7(temp,width_of_longest_new_line,initial_text_tail, 
	    !EQ(Star_this_text_tail_qm,initial_text_tail) ? 
	    Star_this_text_tail_qm : Nil,initial_line_index,
	    line_index_for_next_new_line,Star_line_index);
    return VALUES_1(Qnil);
}

/* CHECK-FOR-HYPHEN-MORE-CLOSELY */
Object check_for_hyphen_more_closely(line_buffer,line_buffer_fill_pointer)
    Object line_buffer, line_buffer_fill_pointer;
{
    Object character_in_string_qm, escape_character_in_string_qm;
    Object next_character_index, previous_character_in_string_qm;
    Object previous_escape_character_in_string_qm, i, temp, temp_1;
    char temp_2;
    Object result;

    x_note_fn_call(109,126);
    character_in_string_qm = Nil;
    escape_character_in_string_qm = Nil;
    next_character_index = Nil;
    previous_character_in_string_qm = Nil;
    previous_escape_character_in_string_qm = Nil;
    i = FIX((SI_Long)0L);
  next_loop:
    if (FIXNUM_LT(i,line_buffer_fill_pointer)) {
	temp = FIX(UBYTE_16_ISAREF_1(line_buffer,IFIX(i)));
	temp_1 = FIXNUM_ADD1(i);
	result = VALUES_2(temp,temp_1);
	MVS_2(result,character_in_string_qm,next_character_index);
	temp_2 = TRUEP(character_in_string_qm);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	goto end_loop;
    if (FIXNUM_EQ(next_character_index,line_buffer_fill_pointer))
	return VALUES_1(EQ(previous_character_in_string_qm,
		FIX((SI_Long)45L)) ? T : Nil);
    previous_character_in_string_qm = character_in_string_qm;
    previous_escape_character_in_string_qm = escape_character_in_string_qm;
    i = next_character_index;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-CHARACTER-IF-ANY-FOR-RUNNING-TEXT */
Object get_character_if_any_for_running_text()
{
    Object indentation_if_new_qm, character_1, temp, temp_2, aref_arg_2;
    char temp_1;
    Object result;

    x_note_fn_call(109,127);
    indentation_if_new_qm = Nil;
    character_1 = Nil;
  next_loop:
    if (Star_line_index_of_change_qm ? FIXNUM_EQ(Star_character_index,
	    Star_character_index_of_change_qm) && 
	    FIXNUM_EQ(Star_line_index,Star_line_index_of_change_qm) : 
	    TRUEP(Nil)) {
	if (Star_character_index_in_string_to_insert_qm) {
	    temp = Star_character_index_in_string_to_insert_qm;
	    temp_1 = FIXNUM_LT(temp,
		    text_string_length(Star_string_to_insert_qm));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = FIX(UBYTE_16_ISAREF_1(Star_string_to_insert_qm,
		    IFIX(Star_character_index_in_string_to_insert_qm)));
	    temp_2 = FIXNUM_ADD1(Star_character_index_in_string_to_insert_qm);
	    Star_character_index_in_string_to_insert_qm = temp_2;
	    character_1 = temp;
	    goto end_loop;
	}
	if (Star_line_index_past_deletion_qm) {
	  next_loop_1:
	    if (FIXNUM_EQ(Star_line_index,Star_line_index_past_deletion_qm))
		goto end_loop_1;
	    result = get_next_text_line(Star_next_text_tail_qm);
	    MVS_5(result,Star_text_line,Star_line_length,
		    Star_lost_space_at_end_of_line,Star_next_text_tail_qm,
		    indentation_if_new_qm);
	    if (indentation_if_new_qm)
		Star_current_indentation = indentation_if_new_qm;
	    temp_2 = FIXNUM_ADD1(Star_line_index);
	    Star_line_index = temp_2;
	    goto next_loop_1;
	  end_loop_1:
	    Star_character_index = Star_character_index_past_deletion_qm;
	}
    }
    if ( !TRUEP(Star_line_length)) {
	Star_explicit_paragraph_or_newline_qm = Nil;
	temp = Star_explicit_paragraph_or_newline_qm;
	goto end_1;
    }
    else if (FIXNUM_GE(Star_character_index,Star_line_length)) {
	temp = FIXNUM_MINUS(Star_character_index,Star_line_length);
	if (FIXNUM_LT(temp,FIXNUMP(Star_lost_space_at_end_of_line) ? 
		Star_lost_space_at_end_of_line : 
		text_string_length(Star_lost_space_at_end_of_line))) {
	    character_1 = FIXNUMP(Star_lost_space_at_end_of_line) ? 
		    FIX((SI_Long)32L) : 
		    FIX(UBYTE_16_ISAREF_1(Star_lost_space_at_end_of_line,
		    IFIX(FIXNUM_MINUS(Star_character_index,
		    Star_line_length))));
	    temp_2 = FIXNUM_ADD1(Star_character_index);
	    Star_character_index = temp_2;
	    goto end_loop;
	}
	if ( !TRUEP(Star_next_text_tail_qm)) {
	    Star_explicit_paragraph_or_newline_qm = Nil;
	    temp = Star_explicit_paragraph_or_newline_qm;
	    goto end_1;
	}
	Star_this_text_tail_qm = Star_next_text_tail_qm;
	temp_2 = FIXNUM_ADD1(Star_line_index);
	Star_line_index = temp_2;
	Star_character_index = FIX((SI_Long)0L);
	result = get_next_text_line(Star_next_text_tail_qm);
	MVS_5(result,Star_text_line,Star_line_length,
		Star_lost_space_at_end_of_line,Star_next_text_tail_qm,
		indentation_if_new_qm);
	Star_text_line_is_simple_qm = Nil;
	if (indentation_if_new_qm)
	    Star_current_indentation = indentation_if_new_qm;
    }
    else {
	temp = FIX(UBYTE_16_ISAREF_1(Star_text_line,
		IFIX(Star_character_index)));
	temp_2 = FIXNUM_ADD1(Star_character_index);
	Star_character_index = temp_2;
	character_1 = temp;
	goto end_loop;
    }
    goto next_loop;
  end_loop:
    temp = character_1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-32768L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)32767L))))
	switch (INTEGER_TO_SHORT(temp)) {
	  case 8233:
	    Star_explicit_paragraph_or_newline_qm = Qparagraph;
	    temp = Nil;
	    goto end_1;
	    break;
	  case 8232:
	    Star_explicit_paragraph_or_newline_qm = Qnewline;
	    temp = Nil;
	    goto end_1;
	    break;
	  case 13:
	    Star_explicit_paragraph_or_newline_qm = Qreturn;
	    temp = Nil;
	    goto end_1;
	    break;
	  case 10:
	    Star_explicit_paragraph_or_newline_qm = Qlinefeed;
	    temp = Nil;
	    goto end_1;
	    break;
	  default:
	    break;
	}
    if (FIXNUM_GE(Star_line_buffer_fill_pointer,Star_line_buffer_limit)) {
	Star_line_buffer_limit = FIX(IFIX(Star_line_buffer_limit) + 
		(SI_Long)100L);
	Star_line_buffer = make_bigger_line_buffer(Star_line_buffer,
		Star_line_buffer_fill_pointer,Star_line_buffer_limit);
    }
    temp_2 = Star_line_buffer;
    aref_arg_2 = Star_line_buffer_fill_pointer;
    UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2),IFIX(character_1));
    temp_2 = FIXNUM_ADD1(Star_line_buffer_fill_pointer);
    Star_line_buffer_fill_pointer = temp_2;
    temp = character_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* DETERMINE-CORRECTED-TEXT-POSITION-IF-NECESSARY */
Object determine_corrected_text_position_if_necessary varargs_1(int, n)
{
    Object old_line_index, old_character_index, new_text_tail, old_text_tail;
    Object line_index_of_tails;
    Object line_index_where_difference_starts_qm;
    Object character_index_where_difference_starts_qm;
    Object choose_right_end_of_insertion_qm, line_index_of_change_qm;
    Object character_index_of_change_qm, line_index_past_deletion_qm;
    Object character_index_past_deletion_qm, string_to_insert_qm;
    Object number_of_characters_passed, text_line, line_length;
    Object lost_space_at_end_of_line, line_index, next_text_tail_qm;
    Object this_text_tail, incff_1_arg, decff_1_arg;
    Object length_of_line_plus_lost_space, next_next_text_tail_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, incff_1_arg_1;
    SI_Long number_of_characters_passed_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,128);
    INIT_ARGS_nonrelocating();
    old_line_index = REQUIRED_ARG_nonrelocating();
    old_character_index = REQUIRED_ARG_nonrelocating();
    new_text_tail = REQUIRED_ARG_nonrelocating();
    old_text_tail = REQUIRED_ARG_nonrelocating();
    line_index_of_tails = REQUIRED_ARG_nonrelocating();
    line_index_where_difference_starts_qm = OPTIONAL_ARG_P_nonrelocating() 
	    ? OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_where_difference_starts_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    choose_right_end_of_insertion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_index_of_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_of_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    string_to_insert_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(line_index_where_difference_starts_qm) || 
	    FIXNUM_GT(old_line_index,
	    line_index_where_difference_starts_qm) || 
	    FIXNUM_EQ(old_line_index,
	    line_index_where_difference_starts_qm) && ( 
	    !TRUEP(character_index_where_difference_starts_qm) || 
	    FIXNUM_GT(old_character_index,
	    character_index_where_difference_starts_qm) || 
	    (choose_right_end_of_insertion_qm && string_to_insert_qm ? 
	    FIXNUM_EQ(old_character_index,
	    character_index_where_difference_starts_qm) : TRUEP(Nil)))) {
	if (line_index_past_deletion_qm && (FIXNUM_GT(old_line_index,
		line_index_of_change_qm) || FIXNUM_EQ(old_line_index,
		line_index_of_change_qm) && FIXNUM_GT(old_character_index,
		character_index_of_change_qm)) &&  
		!(FIXNUM_GT(old_line_index,line_index_past_deletion_qm) || 
		FIXNUM_EQ(old_line_index,line_index_past_deletion_qm) && 
		FIXNUM_GE(old_character_index,
		character_index_past_deletion_qm))) {
	    old_line_index = line_index_of_change_qm;
	    old_character_index = character_index_of_change_qm;
	}
	number_of_characters_passed = FIX((SI_Long)0L);
	text_line = Nil;
	line_length = Nil;
	lost_space_at_end_of_line = Nil;
	line_index = line_index_of_tails;
	next_text_tail_qm = old_text_tail;
	this_text_tail = Nil;
      next_loop:
	if (line_index_of_change_qm && FIXNUM_EQ(line_index,
		line_index_of_change_qm) && (FIXNUM_GT(old_line_index,
		line_index_of_change_qm) || FIXNUM_GT(old_character_index,
		character_index_of_change_qm) || string_to_insert_qm && 
		choose_right_end_of_insertion_qm && 
		FIXNUM_EQ(old_line_index,line_index_of_change_qm) && 
		FIXNUM_EQ(old_character_index,character_index_of_change_qm))) {
	    if (line_index_past_deletion_qm &&  !(string_to_insert_qm && 
		    choose_right_end_of_insertion_qm && 
		    FIXNUM_EQ(old_line_index,line_index_of_change_qm) && 
		    FIXNUM_EQ(old_character_index,
		    character_index_of_change_qm))) {
		incff_1_arg = character_index_of_change_qm;
		number_of_characters_passed = 
			FIXNUM_ADD(number_of_characters_passed,incff_1_arg);
	      next_loop_1:
		if (FIXNUM_EQ(line_index,line_index_past_deletion_qm))
		    goto end_loop;
		result = get_next_text_line(next_text_tail_qm);
		MVS_4(result,text_line,line_length,
			lost_space_at_end_of_line,next_text_tail_qm);
		line_index = FIXNUM_ADD1(line_index);
		goto next_loop_1;
	      end_loop:
		decff_1_arg = character_index_past_deletion_qm;
		number_of_characters_passed = 
			FIXNUM_MINUS(number_of_characters_passed,decff_1_arg);
	    }
	    if (string_to_insert_qm) {
		incff_1_arg = text_string_length(string_to_insert_qm);
		number_of_characters_passed = 
			FIXNUM_ADD(number_of_characters_passed,incff_1_arg);
	    }
	}
	if (FIXNUM_EQ(line_index,old_line_index)) {
	    incff_1_arg = old_character_index;
	    number_of_characters_passed = 
		    FIXNUM_ADD(number_of_characters_passed,incff_1_arg);
	    this_text_tail = new_text_tail;
	    line_index = line_index_of_tails;
	    length_of_line_plus_lost_space = Nil;
	    next_next_text_tail_qm = Nil;
	    result = get_next_text_line(this_text_tail);
	    MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
		    next_text_tail_qm);
	  next_loop_2:
	    gensymed_symbol = IFIX(line_length);
	    gensymed_symbol_1 = FIXNUMP(lost_space_at_end_of_line) ? 
		    IFIX(lost_space_at_end_of_line) : 
		    IFIX(text_string_length(lost_space_at_end_of_line));
	    length_of_line_plus_lost_space = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	    if (FIXNUM_LE(number_of_characters_passed,line_length) || 
		    FIXNUM_LT(number_of_characters_passed,
		    length_of_line_plus_lost_space))
		goto end_loop_1;
	    else if ( !TRUEP(next_text_tail_qm)) {
		if (FIXNUM_GT(number_of_characters_passed,
			length_of_line_plus_lost_space))
		    number_of_characters_passed = 
			    length_of_line_plus_lost_space;
		goto end_loop_1;
	    }
	    result = get_next_text_line(next_text_tail_qm);
	    MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
		    next_next_text_tail_qm);
	    if (FIXNUM_EQ(number_of_characters_passed,
		    length_of_line_plus_lost_space) && IFIX(line_length) 
		    >= (SI_Long)1L && 
		    newline_p(FIX(UBYTE_16_ISAREF_1(text_line,(SI_Long)0L))))
		goto end_loop_1;
	    decff_1_arg = length_of_line_plus_lost_space;
	    number_of_characters_passed = 
		    FIXNUM_MINUS(number_of_characters_passed,decff_1_arg);
	    line_index = FIXNUM_ADD1(line_index);
	    this_text_tail = next_text_tail_qm;
	    next_text_tail_qm = next_next_text_tail_qm;
	    goto next_loop_2;
	  end_loop_1:;
	    return VALUES_3(line_index,number_of_characters_passed,
		    this_text_tail);
	}
	result = get_next_text_line(next_text_tail_qm);
	MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
		next_text_tail_qm);
	if (text_line) {
	    gensymed_symbol = IFIX(line_length);
	    gensymed_symbol_1 = FIXNUMP(lost_space_at_end_of_line) ? 
		    IFIX(lost_space_at_end_of_line) : 
		    IFIX(text_string_length(lost_space_at_end_of_line));
	    incff_1_arg_1 = gensymed_symbol + gensymed_symbol_1;
	    number_of_characters_passed_new_value = 
		    IFIX(number_of_characters_passed) + incff_1_arg_1;
	    number_of_characters_passed = 
		    FIX(number_of_characters_passed_new_value);
	    line_index = FIXNUM_ADD1(line_index);
	}
	if ( !TRUEP(text_line))
	    goto end_loop_2;
	goto next_loop;
      end_loop_2:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-TEXT-TO-TEXT-STRING */
Object convert_text_to_text_string varargs_1(int, n)
{
    Object text_qm;
    Object text_tail_qm, beginning_line_index_qm, beginning_character_index_qm;
    Object end_line_index_qm, end_character_index_qm;
    Object suppress_lost_spaces_at_end, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object beginning_line_index, beginning_character_index, text_tail;
    Object end_character_index, end_line_index, line_index, character_index;
    Object text_line, line_length, lost_space_at_end_of_line, end_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, line_index_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, temp, temp_1;
    SI_Long ab_loop_repeat_;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(109,129);
    INIT_ARGS_nonrelocating();
    text_qm = REQUIRED_ARG_nonrelocating();
    text_tail_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    beginning_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    beginning_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    suppress_lost_spaces_at_end = OPTIONAL_ARG_P_nonrelocating() ? 
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
	      beginning_line_index = beginning_line_index_qm;
	      if (beginning_line_index);
	      else
		  beginning_line_index = FIX((SI_Long)1L);
	      beginning_character_index = beginning_character_index_qm;
	      if (beginning_character_index);
	      else
		  beginning_character_index = FIX((SI_Long)0L);
	      text_tail = text_tail_qm;
	      if (text_tail);
	      else
		  text_tail = find_text_tail_for_line(text_qm,
			  beginning_line_index);
	      end_character_index = end_character_index_qm;
	      end_line_index = end_line_index_qm;
	      if (end_line_index);
	      else {
		  result = find_end_of_text(3,text_tail,
			  beginning_line_index,suppress_lost_spaces_at_end);
		  MVS_2(result,line_index,character_index);
		  end_character_index = end_character_index_qm ? 
			  FIXNUM_MIN(end_character_index_qm,
			  character_index) : character_index;
		  end_line_index = line_index;
	      }
	      line_index_1 = IFIX(beginning_line_index);
	      character_index = beginning_character_index;
	      text_line = Nil;
	      line_length = Nil;
	      lost_space_at_end_of_line = Nil;
	    next_loop:
	      if (line_index_1 == IFIX(end_line_index) && 
		      FIXNUM_GE(character_index,end_character_index) || 
		      line_index_1 > IFIX(end_line_index))
		  goto end_loop;
	      result = get_next_text_line(text_tail);
	      MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
		      text_tail);
	      if (line_index_1 == IFIX(end_line_index))
		  end_1 = end_character_index;
	      else {
		  gensymed_symbol = IFIX(line_length);
		  gensymed_symbol_1 = FIXNUMP(lost_space_at_end_of_line) ? 
			  IFIX(lost_space_at_end_of_line) : 
			  IFIX(text_string_length(lost_space_at_end_of_line));
		  end_1 = FIX(gensymed_symbol + gensymed_symbol_1);
	      }
	      twrite_portion_of_wide_string_unparsably_to_current_wide_string(text_line,
		      FIXNUM_MIN(character_index,line_length),
		      FIXNUM_MIN(end_1,line_length));
	      i = (SI_Long)0L;
	      temp = IFIX(FIXNUM_MINUS(end_1,line_length));
	      temp_1 = IFIX(FIXNUM_MINUS(character_index,line_length));
	      ab_loop_repeat_ = MAX(temp,(SI_Long)0L) - MAX(temp_1,
		      (SI_Long)0L);
	    next_loop_1:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_1;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      twrite_wide_character(text_string_p(lost_space_at_end_of_line) 
		      ? FIX(UBYTE_16_ISAREF_1(lost_space_at_end_of_line,
		      i)) : FIX((SI_Long)32L));
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:;
	      line_index_1 = line_index_1 + (SI_Long)1L;
	      character_index = FIX((SI_Long)0L);
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

/* LINE-BEGINS-WITH-NEWLINE-P */
Object line_begins_with_newline_p(thing)
    Object thing;
{
    Object temp_1, temp_2;
    SI_Long temp;

    x_note_fn_call(109,130);
    if (text_string_p(thing)) {
	temp = UBYTE_16_ISAREF_1(thing,(SI_Long)0L);
	temp_1 = FIX(temp);
	temp_2 = FIX((SI_Long)8232L);
	temp_2 = NUM_EQ(temp_1,temp_2) ? T : Nil;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* COUNT-INITIAL-SPACES */
Object count_initial_spaces(text_string)
    Object text_string;
{
    Object length_1, count_1, character_1, temp;
    SI_Long i, ab_loop_bind_;
    char temp_1;

    x_note_fn_call(109,131);
    length_1 = text_string_length(text_string);
    count_1 = FIX((SI_Long)0L);
    i = IFIX(length_1) > (SI_Long)1L && 
	    line_begins_with_newline_p(text_string) ? (SI_Long)2L : 
	    (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
    character_1 = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    temp = FIX(UBYTE_16_ISAREF_1(text_string,i));
    character_1 = temp;
    if ( !(IFIX(character_1) == (SI_Long)32L))
	temp_1 = TRUEP(count_1);
    else {
	count_1 = FIXNUM_ADD1(count_1);
	temp_1 = TRUEP(Nil);
    }
    if (temp_1)
	goto end_loop;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(count_1);
    return VALUES_1(Qnil);
}

/* CONVERT-TEXT-STRING-TO-TEXT */
Object convert_text_string_to_text(text_string)
    Object text_string;
{
    x_note_fn_call(109,132);
    return slot_value_list_2(make_lost_spaces_text_element(FIX((SI_Long)0L)),
	    text_string);
}

/* CONVERT-TEXT-STRING-LIST-TO-TEXT */
Object convert_text_string_list_to_text(text_string_list)
    Object text_string_list;
{
    Object text_string, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(109,133);
    text_string = Nil;
    ab_loop_list_ = text_string_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    slot_value_cons_1(make_lost_spaces_text_element(FIX((SI_Long)0L)),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = slot_value_cons_1(text_string,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* FIND-TEXT-TAIL-FOR-LINE */
Object find_text_tail_for_line(text,line_index)
    Object text, line_index;
{
    Object text_tail, line_count, l, text_element;

    x_note_fn_call(109,134);
    text_tail = text;
    line_count = FIX((SI_Long)0L);
    l = text;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	line_count = FIXNUM_ADD1(line_count);
	if (FIXNUM_EQ(line_count,line_index))
	    return VALUES_1(text_tail);
	text_tail = CDR(l);
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-CHARACTER-INDEX-PAST-SEPARATOR */
Object get_character_index_past_separator(text_tail)
    Object text_tail;
{
    Object text_element, ab_loop_list_, length_1, temp_1;
    SI_Long char_1;
    char temp;

    x_note_fn_call(109,135);
    text_element = Nil;
    ab_loop_list_ = text_tail;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	length_1 = text_string_length(text_element);
	if (IFIX(length_1) > (SI_Long)0L) {
	    char_1 = UBYTE_16_ISAREF_1(text_element,(SI_Long)0L);
	    temp = char_1 == (SI_Long)8232L;
	    if (temp);
	    else
		temp = char_1 == (SI_Long)8233L;
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = temp ? FIX((SI_Long)1L) : Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    if (temp_1);
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(temp_1);
}

/* FIND-LINE-INDEX-FOR-TEXT-TAIL */
Object find_line_index_for_text_tail(text_tail_to_search,text_tail_to_find,
	    line_index_offset)
    Object text_tail_to_search, text_tail_to_find, line_index_offset;
{
    Object line_count, candidate_text_tail, thing;

    x_note_fn_call(109,136);
    line_count = line_index_offset;
    candidate_text_tail = text_tail_to_search;
  next_loop:
    if ( !TRUEP(candidate_text_tail))
	goto end_loop;
    if (EQ(candidate_text_tail,text_tail_to_find))
	return VALUES_1(line_count);
    thing = CAR(candidate_text_tail);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	line_count = FIXNUM_ADD1(line_count);
    candidate_text_tail = M_CDR(candidate_text_tail);
    goto next_loop;
  end_loop:
    return VALUES_1(line_count);
    return VALUES_1(Qnil);
}

/* FIND-TEXT-TAIL-AND-INDENTATION-FOR-LINE */
Object find_text_tail_and_indentation_for_line(text,line_index)
    Object text, line_index;
{
    Object text_tail, indentation, line_count, l, text_element;

    x_note_fn_call(109,137);
    text_tail = text;
    indentation = FIX((SI_Long)0L);
    line_count = FIX((SI_Long)0L);
    l = text;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	line_count = FIXNUM_ADD1(line_count);
	if (FIXNUM_EQ(line_count,line_index))
	    return VALUES_2(text_tail,indentation);
	text_tail = CDR(l);
    }
    else if (FIXNUMP(text_element))
	indentation = text_element;
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ADVANCE-TEXT-TAIL */
Object advance_text_tail(text_tail,number_of_lines)
    Object text_tail, number_of_lines;
{
    Object line_count, l, text_element;

    x_note_fn_call(109,138);
    line_count = FIX((SI_Long)0L);
    l = text_tail;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	if (FIXNUM_EQ(line_count,number_of_lines))
	    return VALUES_1(text_tail);
	line_count = FIXNUM_ADD1(line_count);
	text_tail = CDR(l);
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-NEXT-TEXT-LINE */
Object get_next_text_line(text_tail)
    Object text_tail;
{
    Object hyphen_added_at_end_of_line_qm, lost_space_at_end_of_line;
    Object context_carryover_qm, explicit_indentation_qm, line_width_qm;
    Object lost_spaces_value_qm, l, text_element, temp, temp_1;

    x_note_fn_call(109,139);
    hyphen_added_at_end_of_line_qm = Nil;
    lost_space_at_end_of_line = FIX((SI_Long)1L);
    context_carryover_qm = Nil;
    explicit_indentation_qm = Nil;
    line_width_qm = Nil;
    lost_spaces_value_qm = Nil;
    l = text_tail;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	temp = text_element;
	temp_1 = hyphen_added_at_end_of_line_qm ? 
		FIXNUM_SUB1(text_string_length(text_element)) : 
		text_string_length(text_element);
	return VALUES_7(temp,temp_1,lost_space_at_end_of_line,CDR(l),
		explicit_indentation_qm,line_width_qm,context_carryover_qm);
    }
    else {
	lost_spaces_value_qm = CONSP(text_element) && 
		EQ(M_CAR(text_element),Qlost_spaces) ? M_CDR(text_element) 
		: Nil;
	if (lost_spaces_value_qm)
	    lost_space_at_end_of_line = lost_spaces_value_qm;
	else if (CONSP(text_element)) {
	    temp_1 = CAR(text_element);
	    if (EQ(temp_1,Qhyphen_added)) {
		hyphen_added_at_end_of_line_qm = T;
		lost_space_at_end_of_line = FIX((SI_Long)0L);
	    }
	    else if (EQ(temp_1,Qline_width))
		line_width_qm = CDR(text_element);
	    else if (EQ(temp_1,Qcontext_carryover))
		context_carryover_qm = CDR(text_element);
	}
	else
	    explicit_indentation_qm = text_element;
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-END-OF-TEXT */
Object find_end_of_text varargs_1(int, n)
{
    Object text_tail, line_index;
    Object suppress_lost_spaces_at_end_qm, line_length;
    Object lost_space_at_end_of_line, next_text_tail_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, line_length_plus_lost_space;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,140);
    INIT_ARGS_nonrelocating();
    text_tail = REQUIRED_ARG_nonrelocating();
    line_index = REQUIRED_ARG_nonrelocating();
    suppress_lost_spaces_at_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    line_length = Nil;
    lost_space_at_end_of_line = Nil;
    next_text_tail_qm = Nil;
  next_loop:
    result = get_next_text_line(text_tail);
    MVS_4(result,gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3);
    next_text_tail_qm = gensymed_symbol_3;
    lost_space_at_end_of_line = gensymed_symbol_2;
    line_length = gensymed_symbol_1;
    if ( !TRUEP(next_text_tail_qm))
	goto end_loop;
    text_tail = next_text_tail_qm;
    line_index = FIXNUM_ADD1(line_index);
    goto next_loop;
  end_loop:
    gensymed_symbol_4 = IFIX(line_length);
    gensymed_symbol_5 = suppress_lost_spaces_at_end_qm ? (SI_Long)0L : 
	    FIXNUMP(lost_space_at_end_of_line) ? 
	    IFIX(lost_space_at_end_of_line) : 
	    IFIX(text_string_length(lost_space_at_end_of_line));
    line_length_plus_lost_space = gensymed_symbol_4 + gensymed_symbol_5;
    return VALUES_3(line_index,FIX(line_length_plus_lost_space),text_tail);
    return VALUES_1(Qnil);
}

/* FIND-END-OF-LINE-OF-TEXT */
Object find_end_of_line_of_text(text_tail,suppress_lost_spaces_at_end_qm)
    Object text_tail, suppress_lost_spaces_at_end_qm;
{
    Object temp, line_length, lost_space_at_end_of_line;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(109,141);
    result = get_next_text_line(text_tail);
    MVS_3(result,temp,line_length,lost_space_at_end_of_line);
    gensymed_symbol = IFIX(line_length);
    gensymed_symbol_1 = suppress_lost_spaces_at_end_qm ? (SI_Long)0L : 
	    FIXNUMP(lost_space_at_end_of_line) ? 
	    IFIX(lost_space_at_end_of_line) : 
	    IFIX(text_string_length(lost_space_at_end_of_line));
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

/* FIND-NEXT-CHARACTER-IF-ANY */
Object find_next_character_if_any(line_index,character_index,text_tail)
    Object line_index, character_index, text_tail;
{
    Object unicode_wide_character_qm, line_index_past_character;
    Object character_index_past_character, text_tail_past_character, text_line;
    Object line_length, lost_space_at_end_of_line, next_text_tail_qm;
    Object line_length_plus_lost_space, temp, i, offset, incff_1_arg;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(109,142);
    unicode_wide_character_qm = Nil;
    line_index_past_character = Nil;
    character_index_past_character = Nil;
    text_tail_past_character = Nil;
    text_line = Nil;
    line_length = Nil;
    lost_space_at_end_of_line = Nil;
    next_text_tail_qm = Nil;
    line_length_plus_lost_space = Nil;
  next_loop:
    result = get_next_text_line(text_tail);
    MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
	    next_text_tail_qm);
    gensymed_symbol = IFIX(line_length);
    gensymed_symbol_1 = FIXNUMP(lost_space_at_end_of_line) ? 
	    IFIX(lost_space_at_end_of_line) : 
	    IFIX(text_string_length(lost_space_at_end_of_line));
    line_length_plus_lost_space = FIX(gensymed_symbol + gensymed_symbol_1);
    if (FIXNUM_LT(character_index,line_length_plus_lost_space)) {
	if (unicode_wide_character_qm) {
	    if ( !(IFIX(line_length) >= (SI_Long)1L && 
		    newline_p(FIX(UBYTE_16_ISAREF_1(text_line,
			(SI_Long)0L))))) {
		line_index_past_character = line_index;
		character_index_past_character = FIX((SI_Long)0L);
		text_tail_past_character = text_tail;
	    }
	    goto end_loop;
	}
	if (FIXNUM_LT(character_index,line_length)) {
	    temp = FIX(UBYTE_16_ISAREF_1(text_line,IFIX(character_index)));
	    character_index = FIXNUM_ADD1(character_index);
	    unicode_wide_character_qm = temp;
	}
	else if (FIXNUMP(lost_space_at_end_of_line)) {
	    character_index = FIXNUM_ADD1(character_index);
	    unicode_wide_character_qm = FIX((SI_Long)32L);
	}
	else {
	    i = FIXNUM_MINUS(character_index,line_length);
	    offset = FIXNUM_NEGATE(i);
	    temp = FIX(UBYTE_16_ISAREF_1(lost_space_at_end_of_line,IFIX(i)));
	    i = FIXNUM_ADD1(i);
	    incff_1_arg = FIXNUM_ADD(i,offset);
	    character_index = FIXNUM_ADD(character_index,incff_1_arg);
	    unicode_wide_character_qm = temp;
	}
	line_index_past_character = line_index;
	character_index_past_character = character_index;
	text_tail_past_character = text_tail;
	if (FIXNUM_LT(character_index,line_length_plus_lost_space) || 
		FIXNUM_EQ(line_length_plus_lost_space,line_length))
	    goto end_loop;
    }
    if ( !TRUEP(next_text_tail_qm))
	goto end_loop;
    text_tail = next_text_tail_qm;
    line_index = FIXNUM_ADD1(line_index);
    character_index = FIX((SI_Long)0L);
    goto next_loop;
  end_loop:
    if (unicode_wide_character_qm)
	return VALUES_4(line_index_past_character,
		character_index_past_character,text_tail_past_character,
		unicode_wide_character_qm);
    return VALUES_1(Qnil);
}

/* FIND-PREVIOUS-CHARACTER-IF-ANY */
Object find_previous_character_if_any(line_index,character_index,text_tail,
	    text)
    Object line_index, character_index, text_tail, text;
{
    Object unicode_wide_character_qm, line_index_past_character;
    Object character_index_past_character, text_tail_past_character, text_line;
    Object line_length, lost_space_at_end_of_line, previous_character_index;
    Object temp, i, offset, incff_1_arg;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(109,143);
    unicode_wide_character_qm = Nil;
    line_index_past_character = Nil;
    character_index_past_character = Nil;
    text_tail_past_character = Nil;
    text_line = Nil;
    line_length = Nil;
    lost_space_at_end_of_line = Nil;
    previous_character_index = Nil;
    if (IFIX(character_index) > (SI_Long)0L) {
	result = get_next_text_line(text_tail);
	MVS_3(result,text_line,line_length,lost_space_at_end_of_line);
    }
  next_loop:
    if (IFIX(character_index) > (SI_Long)0L) {
	if (unicode_wide_character_qm) {
	    if (newline_p(unicode_wide_character_qm) || 
		    EQ(lost_space_at_end_of_line,FIX((SI_Long)0L))) {
		line_index_past_character = line_index;
		character_index_past_character = character_index;
		text_tail_past_character = text_tail;
	    }
	    goto end_loop;
	}
	previous_character_index = FIXNUM_SUB1(character_index);
	character_index = previous_character_index;
	if (FIXNUM_LT(character_index,line_length)) {
	    temp = FIX(UBYTE_16_ISAREF_1(text_line,IFIX(character_index)));
	    character_index = FIXNUM_ADD1(character_index);
	    unicode_wide_character_qm = temp;
	}
	else if (FIXNUMP(lost_space_at_end_of_line)) {
	    character_index = FIXNUM_ADD1(character_index);
	    unicode_wide_character_qm = FIX((SI_Long)32L);
	}
	else {
	    i = FIXNUM_MINUS(character_index,line_length);
	    offset = FIXNUM_NEGATE(i);
	    temp = FIX(UBYTE_16_ISAREF_1(lost_space_at_end_of_line,IFIX(i)));
	    i = FIXNUM_ADD1(i);
	    incff_1_arg = FIXNUM_ADD(i,offset);
	    character_index = FIXNUM_ADD(character_index,incff_1_arg);
	    unicode_wide_character_qm = temp;
	}
	character_index = previous_character_index;
	line_index_past_character = line_index;
	character_index_past_character = character_index;
	text_tail_past_character = text_tail;
	if (IFIX(character_index) > (SI_Long)0L)
	    goto end_loop;
    }
    if (IFIX(line_index) == (SI_Long)1L)
	goto end_loop;
    line_index = FIXNUM_SUB1(line_index);
    text_tail = find_text_tail_for_line(text,line_index);
    result = get_next_text_line(text_tail);
    MVS_3(result,text_line,line_length,lost_space_at_end_of_line);
    gensymed_symbol = IFIX(line_length);
    gensymed_symbol_1 = FIXNUMP(lost_space_at_end_of_line) ? 
	    IFIX(lost_space_at_end_of_line) : 
	    IFIX(text_string_length(lost_space_at_end_of_line));
    character_index = FIX(gensymed_symbol + gensymed_symbol_1);
    goto next_loop;
  end_loop:
    if (unicode_wide_character_qm)
	return VALUES_4(line_index_past_character,
		character_index_past_character,text_tail_past_character,
		unicode_wide_character_qm);
    return VALUES_1(Qnil);
}

/* CONVERT-TO-NON-WORD-WRAPPED-TEXT-POSITION */
Object convert_to_non_word_wrapped_text_position(text,line_index,
	    character_index)
    Object text, line_index, character_index;
{
    Object non_word_wrapped_text, new_line_index, new_character_index;
    Object new_character_index_past_linebreak;
    Object result;

    x_note_fn_call(109,144);
    result = convert_to_non_word_wrapped_text(3,text,line_index,
	    character_index);
    MVS_4(result,non_word_wrapped_text,new_line_index,new_character_index,
	    new_character_index_past_linebreak);
    reclaim_text(non_word_wrapped_text);
    return VALUES_3(new_line_index,new_character_index,
	    new_character_index_past_linebreak);
}

static Object Qnon_word_wrapped_dummy_text_box_format;  /* non-word-wrapped-dummy-text-box-format */

/* CONVERT-TO-NON-WORD-WRAPPED-TEXT */
Object convert_to_non_word_wrapped_text varargs_1(int, n)
{
    Object text;
    Object line_index_qm, character_index_qm, dummy_text_box_format;
    Object copy_of_text, non_word_wrapped_text, temp, new_line_index_qm;
    Object new_character_index_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,145);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    dummy_text_box_format = get_instance_with_name_if_any(Qformat_frame,
	    Qnon_word_wrapped_dummy_text_box_format);
    if (dummy_text_box_format);
    else
	dummy_text_box_format = 
		make_format_frame(Qnon_word_wrapped_dummy_text_box_format);
    copy_of_text = copy_text(text);
    result = format_text(11,copy_of_text,dummy_text_box_format,Nil,Nil,Nil,
	    Nil,Nil,Nil,line_index_qm,character_index_qm,Nil);
    MVS_4(result,non_word_wrapped_text,temp,new_line_index_qm,
	    new_character_index_qm);
    temp = line_index_qm ? 
	    get_character_index_past_separator(find_text_tail_for_line(non_word_wrapped_text,
	    new_line_index_qm)) : Nil;
    return VALUES_4(non_word_wrapped_text,new_line_index_qm,
	    new_character_index_qm,temp);
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

/* FIND-STRING-IN-TEXT-FOR-INSPECT */
Object find_string_in_text_for_inspect varargs_1(int, n)
{
    Object string_1, text, observance_of_word_boundary_qm;
    Object start_line_index, start_character_index;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,146);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    observance_of_word_boundary_qm = REQUIRED_ARG_nonrelocating();
    start_line_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    start_character_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    END_ARGS_nonrelocating();
    if ( !(IFIX(text_string_length(string_1)) == (SI_Long)0L)) {
	if (observance_of_word_boundary_qm)
	    return find_string_in_text(10,string_1,text,Nil,Nil,Nil,T,T,
		    EQ(observance_of_word_boundary_qm,Qsymbol) ? 
		    list_constant_12 : list_constant_13,start_line_index,
		    start_character_index);
	else
	    return find_string_in_text(10,string_1,text,Nil,T,T,Nil,Nil,
		    Nil,start_line_index,start_character_index);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

/* FIND-STRING-IN-TEXT */
Object find_string_in_text varargs_1(int, n)
{
    Object string_1, text;
    Object case_sensitive_qm, treat_space_equivalents_in_text_as_spaces_qm;
    Object ignore_extra_spaces_in_text_qm;
    Object touching_alphabetic_characters_disallowed_qm;
    Object touching_digits_disallowed_qm, disallowed_touching_characters;
    Object start_line_index, start_character_index;
    Object no_match_at_start_position_qm, string_length, first_character;
    Object character_index_past_first_character;
    Object some_touching_characters_disallowed_qm, start_line_text_tail_qm;
    Object saved_start_character_index, start_character;
    Object start_character_escape_character_qm, preceding_character_qm;
    Object preceding_character_escape_character_qm, line_index;
    Object character_index, start_line_length, start_line_lost_space_length;
    Object start_line_lost_space_string_qm, start_line, temp, temp_1, code;
    Object hyphen_added_at_end_of_line_qm, lost_spaces_value_qm, text_element;
    Object start_line_text_tail_qm_old_value, ab_loop_it_, lost_spaces, i;
    Object offset, incff_1_arg, i_1, next_i, next_character, text_tail_qm;
    Object text_line, line_length, lost_space_string_qm, lost_space_length;
    Object previous_character_was_a_space_qm, lost_space_at_end_of_line;
    Object character_1;
    SI_Long temp_3, character_2;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,147);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    case_sensitive_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    treat_space_equivalents_in_text_as_spaces_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    ignore_extra_spaces_in_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    touching_alphabetic_characters_disallowed_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    touching_digits_disallowed_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    disallowed_touching_characters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_line_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    start_character_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    no_match_at_start_position_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    string_length = text_string_length(string_1);
    first_character = Nil;
    character_index_past_first_character = Nil;
    some_touching_characters_disallowed_qm = 
	    touching_alphabetic_characters_disallowed_qm;
    if (some_touching_characters_disallowed_qm);
    else
	some_touching_characters_disallowed_qm = touching_digits_disallowed_qm;
    if (some_touching_characters_disallowed_qm);
    else
	some_touching_characters_disallowed_qm = 
		disallowed_touching_characters;
    start_line_text_tail_qm = find_text_tail_for_line(text,start_line_index);
    saved_start_character_index = Nil;
    start_character = Nil;
    start_character_escape_character_qm = Nil;
    preceding_character_qm = Nil;
    preceding_character_escape_character_qm = Nil;
    line_index = Nil;
    character_index = Nil;
    start_line_length = Nil;
    start_line_lost_space_length = Nil;
    start_line_lost_space_string_qm = Nil;
    start_line = Nil;
    temp = FIX(UBYTE_16_ISAREF_1(string_1,(SI_Long)0L));
    temp_1 = FIX((SI_Long)0L + (SI_Long)1L);
    first_character = temp;
    character_index_past_first_character = temp_1;
    if ( !TRUEP(case_sensitive_qm)) {
	code = first_character;
	if (IFIX(code) < (SI_Long)127L)
	    first_character = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    temp = unicode_lowercase_if_uppercase(code);
	    if (temp);
	    else
		temp = code;
	    first_character = temp;
	}
    }
  next_loop:
    start_line_lost_space_length = FIX((SI_Long)1L);
    start_line_lost_space_string_qm = Nil;
    hyphen_added_at_end_of_line_qm = Nil;
    lost_spaces_value_qm = Nil;
    text_element = Nil;
  next_loop_1:
    start_line_text_tail_qm_old_value = start_line_text_tail_qm;
    temp = FIRST(start_line_text_tail_qm_old_value);
    start_line_text_tail_qm = REST(start_line_text_tail_qm_old_value);
    text_element = temp;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	start_line_length = hyphen_added_at_end_of_line_qm ? 
		FIXNUM_SUB1(text_string_length(text_element)) : 
		text_string_length(text_element);
	start_line = text_element;
	goto end_1;
    }
    else {
	lost_spaces_value_qm = CONSP(text_element) && 
		EQ(M_CAR(text_element),Qlost_spaces) ? M_CDR(text_element) 
		: Nil;
	if (lost_spaces_value_qm) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(lost_spaces_value_qm) != 
		    (SI_Long)0L) {
		start_line_lost_space_string_qm = lost_spaces_value_qm;
		start_line_lost_space_length = 
			text_string_length(start_line_lost_space_string_qm);
	    }
	    else
		start_line_lost_space_length = lost_spaces_value_qm;
	}
	else if (CONSP(text_element)) {
	    temp = CAR(text_element);
	    if (EQ(temp,Qhyphen_added)) {
		hyphen_added_at_end_of_line_qm = T;
		start_line_lost_space_length = FIX((SI_Long)0L);
	    }
	}
    }
    goto next_loop_1;
  end_loop:
    start_line = Qnil;
  end_1:;
    ab_loop_it_ = Nil;
  next_loop_2:
    saved_start_character_index = start_character_index;
    start_character_escape_character_qm = Nil;
    if ( !FIXNUM_LT(start_character_index,FIXNUM_ADD(start_line_length,
	    start_line_lost_space_length)))
	goto end_loop_1;
    lost_spaces = start_line_lost_space_string_qm;
    if (lost_spaces);
    else
	lost_spaces = start_line_lost_space_length;
    if (FIXNUM_LT(start_character_index,start_line_length)) {
	temp = FIX(UBYTE_16_ISAREF_1(start_line,IFIX(start_character_index)));
	start_character_index = FIXNUM_ADD1(start_character_index);
	start_character = temp;
    }
    else if (FIXNUMP(lost_spaces)) {
	start_character_index = FIXNUM_ADD1(start_character_index);
	start_character = FIX((SI_Long)32L);
    }
    else {
	i = FIXNUM_MINUS(start_character_index,start_line_length);
	offset = FIXNUM_NEGATE(i);
	temp = FIX(UBYTE_16_ISAREF_1(lost_spaces,IFIX(i)));
	i = FIXNUM_ADD1(i);
	incff_1_arg = FIXNUM_ADD(i,offset);
	start_character_index = FIXNUM_ADD(start_character_index,incff_1_arg);
	start_character = temp;
    }
    if ( !TRUEP(case_sensitive_qm)) {
	code = start_character;
	if (IFIX(code) < (SI_Long)127L)
	    start_character = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    temp = unicode_lowercase_if_uppercase(code);
	    if (temp);
	    else
		temp = code;
	    start_character = temp;
	}
    }
    if (treat_space_equivalents_in_text_as_spaces_qm && 
	    IFIX(first_character) == (SI_Long)32L && 
	    wide_character_member(start_character,list_constant_14)) {
	start_character = FIX((SI_Long)32L);
	start_character_escape_character_qm = Nil;
    }
    if (FIXNUM_EQ(start_character,first_character)) {
	if ( !TRUEP(preceding_character_qm))
	    temp_2 = TRUEP(no_match_at_start_position_qm);
	else if (some_touching_characters_disallowed_qm) {
	    if (alphabetic_p(preceding_character_qm))
		temp_2 = TRUEP(touching_alphabetic_characters_disallowed_qm);
	    else if (numeric_p(preceding_character_qm))
		temp_2 = TRUEP(touching_digits_disallowed_qm);
	    else if (disallowed_touching_characters)
		temp_2 = 
			TRUEP(wide_character_member(preceding_character_qm,
			disallowed_touching_characters));
	    else
		temp_2 = TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	i_1 = character_index_past_first_character;
	next_i = Nil;
	next_character = Nil;
	text_tail_qm = start_line_text_tail_qm;
	text_line = start_line;
	line_length = start_line_length;
	lost_space_string_qm = start_line_lost_space_string_qm;
	lost_space_length = start_line_lost_space_length;
	previous_character_was_a_space_qm = IFIX(start_character) == 
		(SI_Long)32L ? T : Nil;
	lost_space_at_end_of_line = Nil;
	character_1 = Nil;
	line_index = start_line_index;
	character_index = start_character_index;
      next_loop_3:
      next_loop_4:
	if (FIXNUM_GE(i_1,string_length))
	    goto end_loop_2;
	if ( !FIXNUM_LT(character_index,FIXNUM_ADD(line_length,
		lost_space_length)))
	    goto end_loop_2;
	lost_spaces = lost_space_length;
	if (lost_spaces);
	else
	    lost_spaces = lost_space_string_qm;
	if (FIXNUM_LT(character_index,line_length)) {
	    temp = FIX(UBYTE_16_ISAREF_1(text_line,IFIX(character_index)));
	    character_index = FIXNUM_ADD1(character_index);
	    character_1 = temp;
	}
	else if (FIXNUMP(lost_spaces)) {
	    character_index = FIXNUM_ADD1(character_index);
	    character_1 = FIX((SI_Long)32L);
	}
	else {
	    i = FIXNUM_MINUS(character_index,line_length);
	    offset = FIXNUM_NEGATE(i);
	    temp = FIX(UBYTE_16_ISAREF_1(lost_spaces,IFIX(i)));
	    i = FIXNUM_ADD1(i);
	    incff_1_arg = FIXNUM_ADD(i,offset);
	    character_index = FIXNUM_ADD(character_index,incff_1_arg);
	    character_1 = temp;
	}
	if ( !TRUEP(case_sensitive_qm)) {
	    code = character_1;
	    if (IFIX(code) < (SI_Long)127L)
		character_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
		character_1 = temp;
	    }
	}
	temp = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(i_1)));
	temp_1 = FIXNUM_ADD1(i_1);
	next_character = temp;
	next_i = temp_1;
	if ( !TRUEP(case_sensitive_qm)) {
	    code = next_character;
	    if (IFIX(code) < (SI_Long)127L)
		next_character = (SI_Long)65L <= IFIX(code) && IFIX(code) 
			<= (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : 
			code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
		next_character = temp;
	    }
	}
	if ( !(IFIX(character_1) == (SI_Long)32L))
	    i_1 = next_i;
	else {
	    if (previous_character_was_a_space_qm && 
		    ignore_extra_spaces_in_text_qm &&  
		    !(IFIX(next_character) == (SI_Long)32L))
		next_character = FIX((SI_Long)32L);
	    else
		i_1 = next_i;
	    previous_character_was_a_space_qm = T;
	}
	if ( !EQL(character_1,next_character)) {
	    temp_2 = TRUEP(Nil);
	    goto end_2;
	}
	goto next_loop_4;
      end_loop_2:
	temp_2 = TRUEP(T);
	goto end_2;
	temp_2 = TRUEP(Qnil);
      end_2:
	if ( !temp_2)
	    goto end_loop_3;
	if ( !TRUEP(text_tail_qm) || FIXNUM_EQ(i_1,string_length) && ( 
		!TRUEP(some_touching_characters_disallowed_qm) || 
		FIXNUM_LT(character_index,FIXNUM_ADD(line_length,
		lost_space_length)))) {
	    if (FIXNUM_EQ(i_1,string_length)) {
		if (some_touching_characters_disallowed_qm && 
			FIXNUM_LT(character_index,line_length)) {
		    temp_3 = UBYTE_16_ISAREF_1(text_line,
			    IFIX(character_index));
		    character_2 = temp_3;
		    if (alphabetic_p(FIX(character_2)))
			temp_2 = 
				TRUEP(touching_alphabetic_characters_disallowed_qm);
		    else if (numeric_p(FIX(character_2)))
			temp_2 = TRUEP(touching_digits_disallowed_qm);
		    else if (disallowed_touching_characters)
			temp_2 = 
				TRUEP(wide_character_member(FIX(character_2),
				disallowed_touching_characters));
		    else
			temp_2 = TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		ab_loop_it_ =  !temp_2 ? T : Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	    goto end_3;
	}
	result = get_next_text_line(text_tail_qm);
	MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
		text_tail_qm);
	line_index = FIXNUM_ADD1(line_index);
	character_index = FIX((SI_Long)0L);
	lost_space_string_qm = 
		INLINE_UNSIGNED_BYTE_16_VECTOR_P(lost_space_at_end_of_line) 
		!= (SI_Long)0L ? lost_space_at_end_of_line : Nil;
	lost_space_length = 
		INLINE_UNSIGNED_BYTE_16_VECTOR_P(lost_space_at_end_of_line) 
		!= (SI_Long)0L ? 
		text_string_length(lost_space_at_end_of_line) : 
		lost_space_at_end_of_line;
	goto next_loop_3;
      end_loop_3:
	ab_loop_it_ = Qnil;
      end_3:;
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_4;
	}
    }
    preceding_character_qm = start_character;
    preceding_character_escape_character_qm = 
	    start_character_escape_character_qm;
    goto next_loop_2;
  end_loop_1:
    temp_2 = TRUEP(Qnil);
  end_4:;
    if (temp_2)
	return VALUES_4(start_line_index,saved_start_character_index,
		line_index,character_index);
    if ( !TRUEP(start_line_text_tail_qm))
	goto end_loop_4;
    start_line_index = FIXNUM_ADD1(start_line_index);
    start_character_index = FIX((SI_Long)0L);
    goto next_loop;
  end_loop_4:
    return VALUES_1(Qnil);
}

static Object string_constant_5;   /* "RplcTxtWTxtStr" */

/* REPLACE-TEXT-WITH-TEXT-STRING-IN-TEXT-BOX */
Object replace_text_with_text_string_in_text_box(text_string,text_box)
    Object text_string, text_box;
{
    Object temp, text, current_custom_reclamation_stamp_qm;
    Object box_translation_and_text, translation, new_box_translation_and_text;
    Object end_line_index, end_character_index, end_text_tail;
    Object adjacent_character_qm, next_line_index_qm, next_character_index_qm;
    Object next_text_tail_qm, exhausted_original_text_qm, string_character_qm;
    Object i, length_of_string, temporary_text_string_qm, string_start_index;
    Object line_index, character_index, text_tail, temp_1;
    Object previous_line_index_qm, previous_character_index_qm;
    Object previous_text_tail_qm, i_from_end, string_end_index;
    Object line_index_from_end, character_index_from_end, text_tail_from_end;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,148);
    temp = ISVREF(text_box,(SI_Long)16L);
    text = CDR(temp);
    current_custom_reclamation_stamp_qm = string_constant_5;
    PUSH_SPECIAL_WITH_SYMBOL(Current_custom_reclamation_stamp_qm,Qcurrent_custom_reclamation_stamp_qm,current_custom_reclamation_stamp_qm,
	    0);
      if ( ! !TRUEP(get_text_cell_line_justification(ISVREF(text_box,
	      (SI_Long)17L),ISVREF(text_box,(SI_Long)18L)))) {
	  box_translation_and_text = ISVREF(text_box,(SI_Long)16L);
	  temp = CAR(box_translation_and_text);
	  M_CAR(box_translation_and_text) = Nil;
	  translation = temp;
	  new_box_translation_and_text = slot_value_cons_1(translation,
		  convert_text_string_to_text(copy_text_string(text_string)));
	  change_slot_value(3,text_box,Qbox_translation_and_text,
		  new_box_translation_and_text);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_replace_text_with_text_string_in_text_box;
      }
      result = find_end_of_text(2,text,FIX((SI_Long)1L));
      MVS_3(result,end_line_index,end_character_index,end_text_tail);
      adjacent_character_qm = Nil;
      next_line_index_qm = Nil;
      next_character_index_qm = Nil;
      next_text_tail_qm = Nil;
      exhausted_original_text_qm = Nil;
      string_character_qm = Nil;
      i = FIX((SI_Long)0L);
      length_of_string = text_string_length(text_string);
      temporary_text_string_qm = Nil;
      string_start_index = FIX((SI_Long)0L);
      line_index = FIX((SI_Long)1L);
      character_index = FIX((SI_Long)0L);
      text_tail = text;
    next_loop:
      if (FIXNUM_GE(i,length_of_string))
	  goto end_loop;
      result = find_next_character_if_any(line_index,character_index,
	      text_tail);
      MVS_4(result,next_line_index_qm,next_character_index_qm,
	      next_text_tail_qm,adjacent_character_qm);
      temp = FIX(UBYTE_16_ISAREF_1(text_string,IFIX(i)));
      temp_1 = FIXNUM_ADD1(i);
      string_character_qm = temp;
      i = temp_1;
      if ( !TRUEP(adjacent_character_qm))
	  exhausted_original_text_qm = T;
      if ( !(adjacent_character_qm && string_character_qm && 
	      EQL(adjacent_character_qm,string_character_qm)))
	  goto end_loop;
      string_start_index = i;
      line_index = next_line_index_qm;
      character_index = next_character_index_qm;
      text_tail = next_text_tail_qm;
      goto next_loop;
    end_loop:
      if (T) {
	  if (IFIX(string_start_index) > (SI_Long)0L)
	      temporary_text_string_qm = text_string_substring(text_string,
		      string_start_index,length_of_string);
	  if ( !TRUEP(exhausted_original_text_qm) && 
		  FIXNUM_LT(string_start_index,length_of_string)) {
	      previous_line_index_qm = Nil;
	      previous_character_index_qm = Nil;
	      previous_text_tail_qm = Nil;
	      i_from_end = length_of_string;
	      string_end_index = length_of_string;
	      line_index_from_end = end_line_index;
	      character_index_from_end = end_character_index;
	      text_tail_from_end = end_text_tail;
	    next_loop_1:
	      if (FIXNUM_LE(i_from_end,string_start_index) || 
		      FIXNUM_LE(line_index_from_end,line_index) && 
		      FIXNUM_LE(character_index_from_end,character_index))
		  goto end_loop_1;
	      result = find_previous_character_if_any(line_index_from_end,
		      character_index_from_end,text_tail_from_end,text);
	      MVS_4(result,previous_line_index_qm,
		      previous_character_index_qm,previous_text_tail_qm,
		      adjacent_character_qm);
	      temp = FIX(UBYTE_16_ISAREF_1(text_string,
		      IFIX(FIXNUM_SUB1(i_from_end))));
	      temp_1 = FIXNUM_SUB1(i_from_end);
	      string_character_qm = temp;
	      i_from_end = temp_1;
	      if ( !(adjacent_character_qm && string_character_qm && 
		      EQL(adjacent_character_qm,string_character_qm)))
		  goto end_loop_1;
	      string_end_index = i_from_end;
	      line_index_from_end = previous_line_index_qm;
	      character_index_from_end = previous_character_index_qm;
	      text_tail_from_end = previous_text_tail_qm;
	      goto next_loop_1;
	    end_loop_1:
	      if (FIXNUM_LT(string_end_index,length_of_string)) {
		  if (temporary_text_string_qm)
		      reclaim_text_string(temporary_text_string_qm);
		  temporary_text_string_qm = 
			  text_string_substring(text_string,
			  string_start_index,string_end_index);
	      }
	      end_line_index = line_index_from_end;
	      end_character_index = character_index_from_end;
	      end_character_index = character_index_from_end;
	  }
	  temp = temporary_text_string_qm;
	  if (temp);
	  else
	      temp = text_string;
	  change_text_box(text_box,temp,text_tail,line_index,
		  character_index,end_line_index,end_character_index);
	  if (temporary_text_string_qm)
	      reclaim_text_string(temporary_text_string_qm);
	  if (ISVREF(text_box,(SI_Long)9L))
	      update_representations_of_slot_value(2,text_box,
		      Qbox_translation_and_text);
      }
      result = VALUES_1(Qnil);
    POP_SPECIAL();
  end_replace_text_with_text_string_in_text_box:
    return result;
}

/* REPLACE-TEXT-IN-TEXT-BOX */
Object replace_text_in_text_box varargs_1(int, n)
{
    Object text, text_box;
    Object suppress_lost_spaces_at_end_qm, temporary_text_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,149);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    suppress_lost_spaces_at_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temporary_text_string = convert_text_to_text_string(7,text,Nil,Nil,Nil,
	    Nil,Nil,suppress_lost_spaces_at_end_qm);
    replace_text_with_text_string_in_text_box(temporary_text_string,text_box);
    return reclaim_text_string(temporary_text_string);
}

/* REPLACE-FORMATTED-TEXT-IN-TEXT-BOX */
Object replace_formatted_text_in_text_box(text,text_box)
    Object text, text_box;
{
    Object temp, cdr_arg, temp_1;

    x_note_fn_call(109,150);
    temp = ISVREF(text_box,(SI_Long)16L);
    update_text_in_edit_box(T,CDR(temp),Nil,Nil,FIX((SI_Long)1L),Nil,text_box);
    cdr_arg = ISVREF(text_box,(SI_Long)16L);
    temp = text;
    temp_1 = ISVREF(text_box,(SI_Long)16L);
    reclaim_text(CDR(temp_1));
    M_CDR(cdr_arg) = temp;
    update_text_in_edit_box(Nil,text,Nil,Nil,FIX((SI_Long)1L),Nil,text_box);
    return update_representations_of_slot_value(2,text_box,
	    Qbox_translation_and_text);
}

static Object string_constant_6;   /* "ChgTxtBx" */

/* CHANGE-TEXT-BOX */
Object change_text_box(text_box,string_to_insert,text_tail,
	    line_index_of_change,character_index_of_change,
	    line_index_past_deletion,character_index_past_deletion)
    Object text_box, string_to_insert, text_tail, line_index_of_change;
    Object character_index_of_change, line_index_past_deletion;
    Object character_index_past_deletion;
{
    Object current_custom_reclamation_stamp_qm, text_box_format;
    Object text_cell_plist_for_text_box, x_magnification_qm, temp;
    Object text_being_changed, gensymed_symbol, new_width_for_text;
    Object new_text_segment, old_text_segment;
    Object text_tail_past_old_text_segment_qm;
    Object line_index_of_old_and_new_text_segment;
    Object line_index_past_new_text_segment, line_index_past_old_text_segment;
    Object line_index_in_old_and_new_text, text_tail_in_old_text;
    Object text_tail_in_new_text, next_text_tail_in_old_text_qm;
    Object next_text_tail_in_new_text_qm, old_text_line;
    Object length_of_old_text_line, character_index_where_difference_starts_qm;
    Object magnified_distance_from_left_to_where_difference_starts_qm;
    Object new_text_has_same_height_as_old_qm, text_tail_past_text_segment_qm;
    Object new_text_line, length_of_new_text_line;
    Object lost_space_at_end_of_old_text_line;
    Object lost_space_at_end_of_new_text_line, temp_1, gensymed_symbol_3;
    Object gensymed_symbol_4, temp_2, temp_3, text_to_reclaim, ll, l;
    Object indentation, word_spacing, text_element, ab_loop_list_, temp_5;
    Object new_right_edge_qm, top_edge_of_block, minimum_height_of_text_box;
    Object maximum_height_of_text_box, text_box_top_border_width, text;
    Object height_for_text, text_box_bottom_border_width, x;
    Object new_bottom_edge_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, old_width_for_text;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, magnifiable_distance;
    char temp_4;
    Declare_special(1);
    Object result;

    x_note_fn_call(109,151);
    current_custom_reclamation_stamp_qm = string_constant_6;
    PUSH_SPECIAL_WITH_SYMBOL(Current_custom_reclamation_stamp_qm,Qcurrent_custom_reclamation_stamp_qm,current_custom_reclamation_stamp_qm,
	    0);
      text_box_format = ISVREF(text_box,(SI_Long)17L);
      text_cell_plist_for_text_box = ISVREF(text_box,(SI_Long)18L);
      x_magnification_qm = text_cell_plist_for_text_box ? 
	      getfq_function_no_default(text_cell_plist_for_text_box,
	      Qx_magnification) : Nil;
      if (x_magnification_qm);
      else
	  x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
      temp = ISVREF(text_box,(SI_Long)16L);
      text_being_changed = CDR(temp);
      gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)2L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol);
      gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
      gensymed_symbol_2 = 
	      IFIX(FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ADD(ISVREF(text_box_format,
	      (SI_Long)44L),ISVREF(text_box_format,(SI_Long)27L)),
	      ISVREF(text_box_format,(SI_Long)29L)),ISVREF(text_box_format,
	      (SI_Long)46L)));
      old_width_for_text = gensymed_symbol_1 - gensymed_symbol_2;
      new_width_for_text = FIX((SI_Long)0L);
      new_text_segment = Nil;
      old_text_segment = Nil;
      text_tail_past_old_text_segment_qm = Nil;
      line_index_of_old_and_new_text_segment = Nil;
      line_index_past_new_text_segment = Nil;
      line_index_past_old_text_segment = Nil;
      line_index_in_old_and_new_text = Nil;
      text_tail_in_old_text = Nil;
      text_tail_in_new_text = Nil;
      next_text_tail_in_old_text_qm = Nil;
      next_text_tail_in_new_text_qm = Nil;
      old_text_line = Nil;
      length_of_old_text_line = Nil;
      character_index_where_difference_starts_qm = Nil;
      magnified_distance_from_left_to_where_difference_starts_qm = Nil;
      new_text_has_same_height_as_old_qm = T;
      text_tail_past_text_segment_qm = Nil;
      result = reformat_text(12,text_being_changed,text_box_format,Nil,Nil,
	      text_tail,line_index_of_change,character_index_of_change,
	      line_index_past_deletion,character_index_past_deletion,
	      string_to_insert,get_lookup_slot_value(text_box,
	      Qminimum_width_of_text_box),text_cell_plist_for_text_box);
      MVS_7(result,new_text_segment,new_width_for_text,old_text_segment,
	      text_tail_past_old_text_segment_qm,
	      line_index_of_old_and_new_text_segment,
	      line_index_past_new_text_segment,
	      line_index_past_old_text_segment);
      text_tail_in_old_text = old_text_segment;
      text_tail_in_new_text = new_text_segment;
      line_index_in_old_and_new_text = line_index_of_old_and_new_text_segment;
      new_text_line = Nil;
      length_of_new_text_line = Nil;
      lost_space_at_end_of_old_text_line = Nil;
      lost_space_at_end_of_new_text_line = Nil;
    next_loop:
      result = get_next_text_line(text_tail_in_old_text);
      MVS_4(result,gensymed_symbol,temp,gensymed_symbol_3,gensymed_symbol_4);
      next_text_tail_in_old_text_qm = gensymed_symbol_4;
      lost_space_at_end_of_old_text_line = gensymed_symbol_3;
      old_text_line = gensymed_symbol;
      result = get_next_text_line(text_tail_in_new_text);
      MVS_4(result,gensymed_symbol,temp,gensymed_symbol_3,gensymed_symbol_4);
      next_text_tail_in_new_text_qm = gensymed_symbol_4;
      lost_space_at_end_of_new_text_line = gensymed_symbol_3;
      new_text_line = gensymed_symbol;
      length_of_old_text_line = text_string_length(old_text_line);
      length_of_new_text_line = text_string_length(new_text_line);
      if (FIXNUM_EQ(line_index_in_old_and_new_text,line_index_of_change)) {
	  if ( !TRUEP(next_text_tail_in_new_text_qm) &&  
		  !TRUEP(next_text_tail_in_old_text_qm)) {
	      temp = FIXNUM_MIN(character_index_of_change,
		      length_of_old_text_line);
	      character_index_where_difference_starts_qm = FIXNUM_MIN(temp,
		      length_of_new_text_line);
	  }
	  else if (FIXNUM_LT(character_index_of_change,
		  length_of_old_text_line))
	      character_index_where_difference_starts_qm = 
		      FIXNUM_MIN(character_index_of_change,
		      length_of_new_text_line);
	  else if (FIXNUM_LT(character_index_of_change,
		  length_of_new_text_line))
	      character_index_where_difference_starts_qm = 
		      length_of_old_text_line;
	  else
	      character_index_where_difference_starts_qm = Nil;
	  goto end_1;
      }
      else if ( !FIXNUM_EQ(length_of_new_text_line,length_of_old_text_line)) {
	  character_index_where_difference_starts_qm = 
		  FIXNUM_MIN(length_of_new_text_line,length_of_old_text_line);
	  goto end_1;
      }
      else {
	  if (IFIX(length_of_old_text_line) > (SI_Long)0L) {
	      temp_3 = FIX(UBYTE_16_ISAREF_1(old_text_line,
		      IFIX(FIXNUM_SUB1(length_of_old_text_line))));
	      temp = FIX(UBYTE_16_ISAREF_1(new_text_line,
		      IFIX(FIXNUM_SUB1(length_of_new_text_line))));
	      temp_4 =  !EQ(temp_3,temp);
	  }
	  else
	      temp_4 = TRUEP(Nil);
	  if (temp_4) {
	      character_index_where_difference_starts_qm = 
		      FIXNUM_SUB1(length_of_old_text_line);
	      goto end_1;
	  }
	  else if ( !TRUEP(equalw(lost_space_at_end_of_new_text_line,
		  lost_space_at_end_of_old_text_line))) {
	      character_index_where_difference_starts_qm = 
		      length_of_old_text_line;
	      goto end_1;
	  }
	  else if (EQ(next_text_tail_in_old_text_qm,
		  text_tail_past_old_text_segment_qm) ||  
		  !TRUEP(next_text_tail_in_new_text_qm)) {
	      character_index_where_difference_starts_qm = Nil;
	      goto end_1;
	  }
      }
      text_tail_in_old_text = next_text_tail_in_old_text_qm;
      if (text_tail_in_new_text && next_text_tail_in_new_text_qm &&  
	      !EQ(text_tail_in_new_text,next_text_tail_in_new_text_qm)) {
	  text_to_reclaim = text_tail_in_new_text;
	  ll = Nil;
	  l = text_to_reclaim;
	next_loop_1:
	  if (EQ(l,next_text_tail_in_new_text_qm)) {
	      M_CDR(ll) = Nil;
	      reclaim_text(text_to_reclaim);
	      goto end_2;
	  }
	  ll = l;
	  l = CDR(l);
	  goto next_loop_1;
	end_loop:
	end_2:;
      }
      text_tail_in_new_text = next_text_tail_in_new_text_qm;
      line_index_in_old_and_new_text = 
	      FIXNUM_ADD1(line_index_in_old_and_new_text);
      goto next_loop;
    end_loop_1:
      character_index_where_difference_starts_qm = Qnil;
    end_1:;
      if (character_index_where_difference_starts_qm) {
	  indentation = FIX((SI_Long)0L);
	  word_spacing = ISVREF(text_box_format,(SI_Long)34L);
	  text_element = Nil;
	  ab_loop_list_ = text_tail_in_old_text;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  text_element = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L)
	      goto end_loop_2;
	  if (NUMBERP(text_element))
	      indentation = text_element;
	  else if (SYMBOLP(text_element));
	  else if (EQ(CAR(text_element),Qword_spacing))
	      word_spacing = CDR(text_element);
	  goto next_loop_2;
	end_loop_2:
	  gensymed_symbol_1 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
	  gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)27L));
	  gensymed_symbol_5 = 
		  IFIX(character_index_where_difference_starts_qm) == 
		  (SI_Long)0L ? (SI_Long)0L : IFIX(indentation);
	  gensymed_symbol_6 = 
		  IFIX(compute_minimum_left_edge_of_character_in_line_of_text(old_text_line,
		  character_index_where_difference_starts_qm,
		  ISVREF(text_box_format,(SI_Long)22L),word_spacing));
	  magnifiable_distance = gensymed_symbol_5 + gensymed_symbol_6;
	  gensymed_symbol_5 = x_magnification_qm ? magnifiable_distance * 
		  IFIX(x_magnification_qm) + (SI_Long)128L >>  -  - 
		  (SI_Long)8L : magnifiable_distance;
	  magnified_distance_from_left_to_where_difference_starts_qm = 
		  FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
		  gensymed_symbol_5);
	  goto end_3;
	  magnified_distance_from_left_to_where_difference_starts_qm = Qnil;
	end_3:;
      }
      new_text_has_same_height_as_old_qm = 
	      FIXNUM_EQ(line_index_past_new_text_segment,
	      line_index_past_old_text_segment) ? T : Nil;
      text_tail_past_text_segment_qm = new_text_has_same_height_as_old_qm ?
	       text_tail_past_old_text_segment_qm : Nil;
      if (text_tail_past_old_text_segment_qm) {
	  nconc2(text_tail_in_new_text,text_tail_past_old_text_segment_qm);
	  if ( !TRUEP(next_text_tail_in_new_text_qm))
	      next_text_tail_in_new_text_qm = 
		      text_tail_past_old_text_segment_qm;
      }
      update_text_in_edit_box(T,text_tail_in_old_text,
	      next_text_tail_in_old_text_qm,text_tail_past_text_segment_qm,
	      line_index_in_old_and_new_text,
	      magnified_distance_from_left_to_where_difference_starts_qm,
	      text_box);
      if (text_tail_past_old_text_segment_qm) {
	  l = text_tail_in_old_text;
	next_loop_3:
	  if ( !TRUEP(l))
	      goto end_loop_3;
	  if (EQ(CDR(l),text_tail_past_old_text_segment_qm))
	      goto end_loop_3;
	  l = M_CDR(l);
	  goto next_loop_3;
	end_loop_3:
	  M_CDR(l) = Nil;
      }
      temp = CAR(text_tail_in_new_text);
      temp_5 = CAR(text_tail_in_old_text);
      M_CAR(text_tail_in_new_text) = temp_5;
      M_CAR(text_tail_in_old_text) = temp;
      temp = CDR(text_tail_in_new_text);
      temp_5 = CDR(text_tail_in_old_text);
      M_CDR(text_tail_in_new_text) = temp_5;
      M_CDR(text_tail_in_old_text) = temp;
      temp = text_tail_in_new_text;
      text_tail_in_new_text = text_tail_in_old_text;
      text_tail_in_old_text = temp;
      reclaim_text(text_tail_in_old_text);
      if ( !EQ(old_text_segment,text_being_changed)) {
	  temp_3 = new_width_for_text;
	  temp = compute_width_of_longest_line(5,text_being_changed,
		  text_box_format,text_cell_plist_for_text_box,Nil,
		  old_text_segment);
	  new_width_for_text = FIXNUM_MAX(temp_3,temp);
      }
      if (text_tail_past_old_text_segment_qm) {
	  temp_3 = new_width_for_text;
	  temp = compute_width_of_longest_line(5,
		  text_tail_past_old_text_segment_qm,text_box_format,
		  text_cell_plist_for_text_box,Nil,old_text_segment);
	  new_width_for_text = FIXNUM_MAX(temp_3,temp);
      }
      if ( !(IFIX(new_width_for_text) == old_width_for_text)) {
	  gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = IFIX(get_lookup_slot_value(text_box,
		  Qminimum_width_of_text_box));
	  gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	  gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_5 = IFIX(new_width_for_text) - old_width_for_text;
	  gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_5;
	  new_right_edge_qm = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
      }
      else
	  new_right_edge_qm = Nil;
      gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      top_edge_of_block = gensymed_symbol;
      minimum_height_of_text_box = get_lookup_slot_value(text_box,
	      Qminimum_height_of_text_box);
      maximum_height_of_text_box = 
	      get_lookup_slot_value_given_default(text_box,
	      Qmaximum_height_of_text_box,FIX((SI_Long)4194303L));
      text_box_top_border_width = ISVREF(text_box_format,(SI_Long)45L);
      temp = ISVREF(text_box,(SI_Long)16L);
      text = CDR(temp);
      height_for_text = compute_height_for_text(text,text_box_format,
	      text_cell_plist_for_text_box);
      text_box_bottom_border_width = ISVREF(text_box_format,(SI_Long)47L);
      if ( !TRUEP(new_text_has_same_height_as_old_qm)) {
	  gensymed_symbol_1 = IFIX(top_edge_of_block);
	  x = FIXNUM_ADD(FIXNUM_ADD(text_box_top_border_width,
		  height_for_text),text_box_bottom_border_width);
	  gensymed_symbol_2 = FIXNUM_LE(x,minimum_height_of_text_box) ? 
		  IFIX(minimum_height_of_text_box) : 
		  FIXNUM_LE(maximum_height_of_text_box,x) ? 
		  IFIX(maximum_height_of_text_box) : IFIX(x);
	  new_bottom_edge_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
      }
      else
	  new_bottom_edge_qm = Nil;
      if (new_right_edge_qm) {
	  gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  temp_4 = FIXNUM_NE(new_right_edge_qm,gensymed_symbol);
      }
      else
	  temp_4 = TRUEP(Nil);
      if (temp_4);
      else if (new_bottom_edge_qm) {
	  gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  temp_4 = FIXNUM_NE(new_bottom_edge_qm,gensymed_symbol);
      }
      else
	  temp_4 = TRUEP(Nil);
      if (temp_4)
	  update_border_of_text_box(text_box,Nil,Nil,new_right_edge_qm,
		  new_bottom_edge_qm);
      result = update_text_in_edit_box(Nil,text_tail_in_new_text,
	      next_text_tail_in_new_text_qm,text_tail_past_text_segment_qm,
	      line_index_in_old_and_new_text,
	      magnified_distance_from_left_to_where_difference_starts_qm,
	      text_box);
    POP_SPECIAL();
    return result;
}

static Object Qmessage;            /* message */

static Object Qminimum_format_width_for_text_cell;  /* minimum-format-width-for-text-cell */

/* G2-REFORMAT-TEXT-STRING-TO-FIT-MESSAGE */
Object g2_reformat_text_string_to_fit_message(message_frame,text_string,
	    wrap_flag)
    Object message_frame, text_string, wrap_flag;
{
    Object wrap_p, text_cell_plist_for_text_box, text_box_format;
    Object gensymed_symbol, right_edge, left_edge, top_edge, bottom_edge;
    Object left_margin, right_margin, left_border, right_border, width, height;
    Object class_description, slot_descriptions, slot_description_of_text_slot;
    Object original_minimum_format_width, new_value_to_conclude;
    Object remaining_width, do_not_note_permanent_changes_p;
    Declare_special(1);

    x_note_fn_call(109,152);
    wrap_p = evaluation_truth_value_is_true_p(wrap_flag);
    text_cell_plist_for_text_box = ISVREF(message_frame,(SI_Long)18L);
    text_box_format = ISVREF(message_frame,(SI_Long)17L);
    gensymed_symbol = ISVREF(message_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(message_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(message_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(message_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge = gensymed_symbol;
    left_margin = ISVREF(text_box_format,(SI_Long)27L);
    right_margin = ISVREF(text_box_format,(SI_Long)29L);
    left_border = ISVREF(text_box_format,(SI_Long)44L);
    right_border = ISVREF(text_box_format,(SI_Long)46L);
    width = FIXNUM_MINUS(right_edge,left_edge);
    height = FIXNUM_MINUS(bottom_edge,top_edge);
    class_description = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(message_frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    slot_description_of_text_slot = get_slot_description(3,
	    Qbox_translation_and_text,slot_descriptions,Qmessage);
    original_minimum_format_width = ISVREF(text_box_format,(SI_Long)41L);
    new_value_to_conclude = convert_text_string_to_text_within_region(6,
	    text_string,width,height,text_box_format,wrap_p,
	    text_cell_plist_for_text_box);
    remaining_width = 
	    FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(width,
	    right_margin),left_margin),left_border),right_border);
    if (wrap_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(text_box_format,
		    Qminimum_format_width_for_text_cell);
	SVREF(text_box_format,FIX((SI_Long)41L)) = remaining_width;
    }
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      note_kb_state_change_to_slot_by_saving_text(message_frame,
	      slot_description_of_text_slot);
      replace_text_in_text_box(3,new_value_to_conclude,message_frame,T);
      change_edges_of_block(message_frame,left_edge,top_edge,right_edge,
	      bottom_edge);
    POP_SPECIAL();
    reclaim_slot_value(new_value_to_conclude);
    if (wrap_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(text_box_format,
		    Qminimum_format_width_for_text_cell);
	return VALUES_1(SVREF(text_box_format,FIX((SI_Long)41L)) = 
		original_minimum_format_width);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-TEXT-STRING-TO-TEXT-WITHIN-REGION */
Object convert_text_string_to_text_within_region varargs_1(int, n)
{
    Object text_string, width, height, text_box_format, wrap_p;
    Object text_cell_plist, x_magnification_qm, left_margin, top_margin;
    Object right_margin, bottom_margin, left_border, top_border, right_border;
    Object bottom_border, remaining_width_excluding_margin, remaining_width;
    Object remaining_height, text, formatted_text, new_width, new_height;
    Object line_index, text_tail, text_line, end_line_index;
    Object end_character_index, next_tail_qm, next_line_if_wrapped_qm, temp;
    Object temp_1, temp_2, temp_3, text_line_to_truncate, indentation;
    Object truncated_text_line, new_text_segment, new_width_for_text;
    Object old_text_segment, ll, l;
    SI_Long widest_width;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(109,153);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    width = REQUIRED_ARG_nonrelocating();
    height = REQUIRED_ARG_nonrelocating();
    text_box_format = REQUIRED_ARG_nonrelocating();
    wrap_p = REQUIRED_ARG_nonrelocating();
    text_cell_plist = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    x_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qx_magnification) : Nil;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
    left_margin = ISVREF(text_box_format,(SI_Long)27L);
    top_margin = ISVREF(text_box_format,(SI_Long)28L);
    right_margin = ISVREF(text_box_format,(SI_Long)29L);
    bottom_margin = ISVREF(text_box_format,(SI_Long)30L);
    left_border = ISVREF(text_box_format,(SI_Long)44L);
    top_border = ISVREF(text_box_format,(SI_Long)45L);
    right_border = ISVREF(text_box_format,(SI_Long)46L);
    bottom_border = ISVREF(text_box_format,(SI_Long)47L);
    remaining_width_excluding_margin = FIXNUM_MINUS(FIXNUM_MINUS(width,
	    left_border),right_border);
    remaining_width = 
	    FIXNUM_MINUS(FIXNUM_MINUS(remaining_width_excluding_margin,
	    right_margin),left_margin);
    remaining_height = 
	    FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(height,
	    bottom_margin),top_margin),top_border),bottom_border);
    widest_width = (SI_Long)100000L;
    text = convert_text_string_to_text(text_string);
    formatted_text = Nil;
    new_width = Nil;
    new_height = Nil;
    line_index = Nil;
    text_tail = Nil;
    text_line = Nil;
    end_line_index = Nil;
    end_character_index = Nil;
    result = format_text(12,text,text_box_format,text_cell_plist,Nil,Nil,
	    Nil,Nil,Nil,Nil,Nil,wrap_p ? remaining_width_excluding_margin :
	     FIX(widest_width),wrap_p ? T : Nil);
    MVS_2(result,formatted_text,new_width);
    new_height = compute_height_for_text_without_margins(formatted_text,
	    text_box_format,text_cell_plist);
    if ( !(FIXNUM_LE(new_width,remaining_width) && FIXNUM_LE(new_height,
	    remaining_height))) {
	result = compute_line_index_in_text_below_height(formatted_text,
		text_box_format,text_cell_plist,remaining_height);
	MVS_3(result,line_index,text_tail,text_line);
	next_tail_qm = text_tail ? find_text_tail_for_line(text_tail,
		FIX((SI_Long)2L)) : Nil;
	next_line_if_wrapped_qm = next_tail_qm && 
		IFIX(get_character_index_past_separator(next_tail_qm)) == 
		(SI_Long)0L ? get_next_text_line(next_tail_qm) : Nil;
	if (next_line_if_wrapped_qm) {
	    temp = formatted_text;
	    temp_1 = text_tail;
	    temp_2 = line_index;
	    temp_3 = FIXNUM_ADD1(line_index);
	    text_line_to_truncate = convert_text_to_text_string(7,temp,
		    temp_1,temp_2,FIX((SI_Long)0L),temp_3,
		    text_string_length(next_line_if_wrapped_qm),T);
	}
	else
	    text_line_to_truncate = text_line;
	result = find_text_tail_and_indentation_for_line(formatted_text,
		line_index);
	indentation = NTH_VALUE((SI_Long)1L, result);
	temp_3 = x_magnification_qm ? 
		FIXNUM_MINUS(FIXNUM_MINUS(inverse_magnify(FIXNUM_MINUS(remaining_width_excluding_margin,
		indentation),x_magnification_qm),right_margin),
		left_margin) : FIXNUM_MINUS(remaining_width,indentation);
	truncated_text_line = truncate_text_line_to_fit_width(7,
		text_line_to_truncate,temp_3,ISVREF(text_box_format,
		(SI_Long)22L),ISVREF(text_box_format,(SI_Long)34L),Nil,Nil,T);
	result = find_end_of_text(2,text_tail,line_index);
	MVS_2(result,end_line_index,end_character_index);
	result = reformat_text(13,formatted_text,text_box_format,Nil,Nil,
		Nil,line_index,FIX((SI_Long)0L),end_line_index,
		end_character_index,truncated_text_line,wrap_p ? 
		remaining_width_excluding_margin : FIX(widest_width),
		text_cell_plist,wrap_p ? T : Nil);
	MVS_3(result,new_text_segment,new_width_for_text,old_text_segment);
	if (EQ(old_text_segment,formatted_text)) {
	    reclaim_text(formatted_text);
	    formatted_text = new_text_segment;
	}
	else {
	    ll = Nil;
	    l = formatted_text;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(l,old_text_segment)) {
		M_CDR(ll) = new_text_segment;
		reclaim_text(old_text_segment);
		goto end_1;
	    }
	    ll = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
	reclaim_text_string(truncated_text_line);
	if (next_line_if_wrapped_qm)
	    reclaim_text_string(text_line_to_truncate);
	temp_3 = formatted_text;
	result = truncate_text_to_fit_width(6,temp_3,x_magnification_qm ? 
		inverse_magnify(remaining_width,x_magnification_qm) : 
		remaining_width,text_box_format,Nil,Nil,Nil);
	MVS_2(result,formatted_text,new_width_for_text);
    }
    return VALUES_1(formatted_text);
}

static Object array_constant_2;    /* # */

/* TRUNCATE-TEXT-LINE-TO-FIT-WIDTH */
Object truncate_text_line_to_fit_width varargs_1(int, n)
{
    Object text_string, cutoff_width, font_map, word_spacing;
    Object ellipsis_override_qm, ellipsis_width_override_qm;
    Object always_append_ellipsis_p, ellipsis, ellipsis_width, num_chars;
    Object ellipsis_length, truncated_length, truncated_string, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,154);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    cutoff_width = REQUIRED_ARG_nonrelocating();
    font_map = REQUIRED_ARG_nonrelocating();
    word_spacing = REQUIRED_ARG_nonrelocating();
    ellipsis_override_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    ellipsis_width_override_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    always_append_ellipsis_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    ellipsis = ellipsis_override_qm;
    if (ellipsis);
    else
	ellipsis = Ellipsis_text_string;
    ellipsis_width = ellipsis_width_override_qm;
    if (ellipsis_width);
    else
	ellipsis_width = compute_width_of_text_line(5,array_constant_2,Nil,
		Nil,font_map,word_spacing);
    num_chars = text_string_length(text_string);
    ellipsis_length = text_string_length(ellipsis);
    truncated_length = FIX((SI_Long)0L);
    truncated_string = Nil;
    cutoff_width = FIXNUM_MINUS(cutoff_width,ellipsis_width);
    truncated_length = compute_index_in_text_line_below_width(text_string,
	    Nil,Nil,font_map,word_spacing,cutoff_width);
    if (FIXNUM_EQ(num_chars,truncated_length) &&  
	    !TRUEP(always_append_ellipsis_p))
	return copy_text_string(text_string);
    else if (IFIX(truncated_length) == (SI_Long)0L) {
	truncated_length = compute_index_in_text_line_below_width(ellipsis,
		Nil,Nil,font_map,word_spacing,FIXNUM_ADD(cutoff_width,
		ellipsis_width));
	temp = truncated_length;
	truncated_string = obtain_text_string(truncated_length);
	copy_portion_of_string_into_text_string(ellipsis,FIX((SI_Long)0L),
		temp,truncated_string,FIX((SI_Long)0L));
	return VALUES_1(truncated_string);
    }
    else {
	temp = truncated_length;
	truncated_string = obtain_text_string(FIXNUM_ADD(truncated_length,
		ellipsis_length));
	copy_portion_of_string_into_text_string(text_string,
		FIX((SI_Long)0L),temp,truncated_string,FIX((SI_Long)0L));
	copy_portion_of_string_into_text_string(ellipsis,FIX((SI_Long)0L),
		ellipsis_length,truncated_string,truncated_length);
	return VALUES_1(truncated_string);
    }
}

/* COMPUTE-INDEX-IN-TEXT-LINE-BELOW-WIDTH */
Object compute_index_in_text_line_below_width(text_line,start_qm,end_qm,
	    font_map,word_spacing,max_width)
    Object text_line, start_qm, end_qm, font_map, word_spacing, max_width;
{
    Object gensymed_symbol, ab_font, temp, character_1, next_index, temp_1;
    SI_Long i, end_1, text_x_a, text_x_b, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long incff_1_arg;

    x_note_fn_call(109,155);
    gensymed_symbol = CAR(font_map);
    ab_font = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qab_font);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    i = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = text_string_length(text_line);
    end_1 = IFIX(temp);
    text_x_a = (SI_Long)0L;
    text_x_b = (SI_Long)0L;
    character_1 = Nil;
    next_index = Nil;
    text_x_a = (SI_Long)0L;
    text_x_b = (SI_Long)128L;
  next_loop:
    if ( !(i < end_1))
	goto end_loop;
    temp = FIX(UBYTE_16_ISAREF_1(text_line,i));
    temp_1 = FIX(i + (SI_Long)1L);
    character_1 = temp;
    next_index = temp_1;
    gensymed_symbol_1 = text_x_b;
    gensymed_symbol_2 = IFIX(character_1) == (SI_Long)32L ? 
	    IFIX(word_spacing) : 
	    IFIX(get_unicode_set_width_as_text_width(character_1,ab_font));
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    incff_1_arg = gensymed_symbol_1 >>  -  - (SI_Long)8L;
    text_x_a = text_x_a + incff_1_arg;
    gensymed_symbol_1 = gensymed_symbol_1 & (SI_Long)255L;
    text_x_b = gensymed_symbol_1;
    if (FIXNUM_GT(FIX(text_x_a),max_width))
	goto end_loop;
    else
	i = IFIX(next_index);
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(i));
    return VALUES_1(Qnil);
}

/* COMPUTE-LINE-INDEX-IN-TEXT-BELOW-HEIGHT */
Object compute_line_index_in_text_below_height(text,text_box_format,
	    text_cell_plist,unmagnified_max_height)
    Object text, text_box_format, text_cell_plist, unmagnified_max_height;
{
    Object line_height, line_spacing, line_height_plus_spacing;
    Object y_magnification_qm, height_with_next_line, line_index, text_tail;
    Object last_text_line_qm, l, text_element, incff_1_arg_1;
    SI_Long magnified_line_height_plus_spacing, incff_1_arg;
    SI_Long height_with_next_line_new_value;

    x_note_fn_call(109,156);
    line_height = ISVREF(text_box_format,(SI_Long)31L);
    line_spacing = ISVREF(text_box_format,(SI_Long)33L);
    line_height_plus_spacing = FIXNUM_ADD(line_height,line_spacing);
    y_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qy_magnification) : Nil;
    if (y_magnification_qm);
    else
	y_magnification_qm = ISVREF(text_box_format,(SI_Long)26L);
    magnified_line_height_plus_spacing = y_magnification_qm ? 
	    IFIX(FIXNUM_TIMES(line_height_plus_spacing,
	    y_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L : 
	    IFIX(line_height_plus_spacing);
    height_with_next_line = y_magnification_qm ? 
	    FIX(IFIX(FIXNUM_TIMES(line_height,y_magnification_qm)) + 
	    (SI_Long)128L >>  -  - (SI_Long)8L) : line_height;
    line_index = FIX((SI_Long)1L);
    text_tail = text;
    last_text_line_qm = Nil;
    l = text;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	incff_1_arg = magnified_line_height_plus_spacing;
	height_with_next_line_new_value = IFIX(height_with_next_line) + 
		incff_1_arg;
	height_with_next_line = FIX(height_with_next_line_new_value);
	last_text_line_qm = text_element;
	if (FIXNUM_GT(height_with_next_line,unmagnified_max_height))
	    goto end_loop;
	if (CDR(l)) {
	    text_tail = CDR(l);
	    line_index = FIXNUM_ADD1(line_index);
	}
    }
    else if (CONSP(text_element) && EQ(CAR(text_element),Qleading)) {
	incff_1_arg_1 = CDR(text_element);
	height_with_next_line = FIXNUM_ADD(height_with_next_line,
		incff_1_arg_1);
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_3(line_index,text_tail,last_text_line_qm);
    return VALUES_1(Qnil);
}

/* TRUNCATE-TEXT-TO-FIT-WIDTH */
Object truncate_text_to_fit_width varargs_1(int, n)
{
    Object text_segment, cutoff_width, text_box_format, text_cell_plist;
    Object put_in_indentations_and_widths_qm;
    Object text_tail_past_text_segment_qm, word_spacing, font_map;
    Object x_magnification_qm, width_of_longest_line_so_far, indentation;
    Object line_width_qm, indentation_qm, truncation_happened_p, l, next_l;
    Object text_element, line_width, temp, unmagnified_line_width, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(109,157);
    INIT_ARGS_nonrelocating();
    text_segment = REQUIRED_ARG_nonrelocating();
    cutoff_width = REQUIRED_ARG_nonrelocating();
    text_box_format = REQUIRED_ARG_nonrelocating();
    text_cell_plist = REQUIRED_ARG_nonrelocating();
    put_in_indentations_and_widths_qm = REQUIRED_ARG_nonrelocating();
    text_tail_past_text_segment_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    word_spacing = ISVREF(text_box_format,(SI_Long)34L);
    font_map = ISVREF(text_box_format,(SI_Long)22L);
    x_magnification_qm = text_cell_plist ? 
	    getfq_function_no_default(text_cell_plist,Qx_magnification) : Nil;
    if (x_magnification_qm);
    else
	x_magnification_qm = ISVREF(text_box_format,(SI_Long)25L);
    width_of_longest_line_so_far = FIX((SI_Long)0L);
    indentation = FIX((SI_Long)0L);
    line_width_qm = Nil;
    indentation_qm = Nil;
    truncation_happened_p = Nil;
    l = text_segment;
    next_l = Nil;
    text_element = Nil;
  next_loop:
    next_l = CDR(l);
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	line_width = line_width_qm;
	if (line_width);
	else {
	    temp = indentation;
	    unmagnified_line_width = FIXNUM_ADD(temp,
		    compute_width_of_text_line(5,text_element,Nil,Nil,
		    ISVREF(text_box_format,(SI_Long)22L),word_spacing));
	    line_width = x_magnification_qm ? 
		    FIX(IFIX(FIXNUM_TIMES(unmagnified_line_width,
		    x_magnification_qm)) + (SI_Long)128L >>  -  - 
		    (SI_Long)8L) : unmagnified_line_width;
	}
	if (FIXNUM_GT(line_width,cutoff_width)) {
	    temp = truncate_text_line_to_fit_width(4,text_element,
		    FIXNUM_MINUS(cutoff_width,indentation),font_map,
		    word_spacing);
	    reclaim_text_string(text_element);
	    text_element = temp;
	    M_CAR(l) = text_element;
	    truncation_happened_p = T;
	    temp = indentation;
	    unmagnified_line_width = FIXNUM_ADD(temp,
		    compute_width_of_text_line(5,text_element,Nil,Nil,
		    ISVREF(text_box_format,(SI_Long)22L),word_spacing));
	}
	if (FIXNUM_GT(line_width,width_of_longest_line_so_far))
	    width_of_longest_line_so_far = line_width;
	if (line_width_qm)
	    line_width_qm = Nil;
	else if (put_in_indentations_and_widths_qm) {
	    temp_1 = slot_value_cons_1(text_element,CDR(l));
	    M_CDR(l) = temp_1;
	    temp_1 = slot_value_cons_1(Qline_width,line_width);
	    M_CAR(l) = temp_1;
	}
	if (indentation_qm)
	    indentation_qm = Nil;
	else if (put_in_indentations_and_widths_qm) {
	    temp_1 = slot_value_cons_1(CAR(l),CDR(l));
	    M_CDR(l) = temp_1;
	    M_CAR(l) = indentation;
	}
    }
    else if (FIXNUMP(text_element)) {
	indentation_qm = text_element;
	indentation = indentation_qm;
    }
    else if (CONSP(text_element)) {
	temp = CAR(text_element);
	if (EQ(temp,Qline_width))
	    line_width_qm = CDR(text_element);
	else if (EQ(temp,Qword_spacing))
	    word_spacing = CDR(text_element);
    }
    if ( !TRUEP(next_l) || EQ(next_l,text_tail_past_text_segment_qm))
	goto end_loop;
    l = next_l;
    goto next_loop;
  end_loop:
    return VALUES_3(text_segment,width_of_longest_line_so_far,
	    truncation_happened_p);
    return VALUES_1(Qnil);
}

/* INITIAL-NAME-BOX */
Object initial_name_box(class_1)
    Object class_1;
{
    x_note_fn_call(109,158);
    return VALUES_1(Nil);
}

static Object Qab_structure;       /* structure */

static Object Qx_offset;           /* x-offset */

static Object Qy_offset;           /* y-offset */

/* GET-NAME-BOX */
Object get_name_box(entity)
    Object entity;
{
    Object name_box_qm, gensymed_symbol, temp, gensymed_symbol_2;
    Object text_cell_plist, text_cell_format, table_qm;
    Object ignore_state_of_highlighting, item_or_value, x2, temp_2, table;
    Object svref_new_value, gensymed_symbol_3, temp_3;
    SI_Long gensymed_symbol_1, svref_arg_2, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, item_or_value_1;
    char temp_1;

    x_note_fn_call(109,159);
    name_box_qm = get_name_box_if_any_qm(entity);
    if (name_box_qm) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qcolor;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qcolor;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qbackground_color;
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qbackground_color;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table_qm = Nil;
		ignore_state_of_highlighting = T;
		if (text_cell_plist) {
		    item_or_value =  !TRUEP(ignore_state_of_highlighting) ?
			     getfq_function_no_default(text_cell_plist,
			    Qhighlight_color) : Qnil;
		    if (item_or_value);
		    else
			item_or_value = 
				getfq_function_no_default(text_cell_plist,
				Qbackground_color);
		}
		else
		    item_or_value = Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)24L);
		if (item_or_value);
		else
		    item_or_value = table_qm ? 
			    table_background_color(table_qm) : Nil;
		if (item_or_value);
		else
		    item_or_value = Default_text_cell_background_color;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table_qm = Nil;
		ignore_state_of_highlighting = T;
		if (text_cell_plist) {
		    item_or_value =  !TRUEP(ignore_state_of_highlighting) ?
			     getfq_function_no_default(text_cell_plist,
			    Qhighlight_color) : Qnil;
		    if (item_or_value);
		    else
			item_or_value = 
				getfq_function_no_default(text_cell_plist,
				Qbackground_color);
		}
		else
		    item_or_value = Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)24L);
		if (item_or_value);
		else
		    item_or_value = table_qm ? 
			    table_background_color(table_qm) : Nil;
		if (item_or_value);
		else
		    item_or_value = Default_text_cell_background_color;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qtext_color;
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qtext_color;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table = Nil;
		item_or_value = text_cell_plist ? 
			getfq_function_no_default(text_cell_plist,
			Qline_color) : Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)23L);
		if (item_or_value);
		else
		    item_or_value = Qforeground;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table = Nil;
		item_or_value = text_cell_plist ? 
			getfq_function_no_default(text_cell_plist,
			Qline_color) : Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)23L);
		if (item_or_value);
		else
		    item_or_value = Qforeground;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qbackground_color;
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp_2,FIX((SI_Long)1L)) = Qbackground_color;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table_qm = Nil;
		ignore_state_of_highlighting = T;
		if (text_cell_plist) {
		    item_or_value =  !TRUEP(ignore_state_of_highlighting) ?
			     getfq_function_no_default(text_cell_plist,
			    Qhighlight_color) : Qnil;
		    if (item_or_value);
		    else
			item_or_value = 
				getfq_function_no_default(text_cell_plist,
				Qbackground_color);
		}
		else
		    item_or_value = Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)24L);
		if (item_or_value);
		else
		    item_or_value = table_qm ? 
			    table_background_color(table_qm) : Nil;
		if (item_or_value);
		else
		    item_or_value = Default_text_cell_background_color;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table_qm = Nil;
		ignore_state_of_highlighting = T;
		if (text_cell_plist) {
		    item_or_value =  !TRUEP(ignore_state_of_highlighting) ?
			     getfq_function_no_default(text_cell_plist,
			    Qhighlight_color) : Qnil;
		    if (item_or_value);
		    else
			item_or_value = 
				getfq_function_no_default(text_cell_plist,
				Qbackground_color);
		}
		else
		    item_or_value = Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)24L);
		if (item_or_value);
		else
		    item_or_value = table_qm ? 
			    table_background_color(table_qm) : Nil;
		if (item_or_value);
		else
		    item_or_value = Default_text_cell_background_color;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qtext_color;
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp_2,FIX((SI_Long)3L)) = Qtext_color;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table = Nil;
		item_or_value = text_cell_plist ? 
			getfq_function_no_default(text_cell_plist,
			Qline_color) : Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)23L);
		if (item_or_value);
		else
		    item_or_value = Qforeground;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		text_cell_plist = ISVREF(name_box_qm,(SI_Long)18L);
		text_cell_format = ISVREF(name_box_qm,(SI_Long)17L);
		table = Nil;
		item_or_value = text_cell_plist ? 
			getfq_function_no_default(text_cell_plist,
			Qline_color) : Nil;
		if (item_or_value);
		else
		    item_or_value = ISVREF(text_cell_format,(SI_Long)23L);
		if (item_or_value);
		else
		    item_or_value = Qforeground;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qposition;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qposition;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qx_offset;
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qx_offset;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol_3);
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
		gensymed_symbol_5 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 >>  -  - 
			gensymed_symbol_5;
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol_3);
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
		gensymed_symbol_5 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 >>  -  - 
			gensymed_symbol_5;
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qy_offset;
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qy_offset;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_4;
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_1 = gensymed_symbol_1 >>  -  - 
			gensymed_symbol_4;
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_4;
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_1 = gensymed_symbol_1 >>  -  - 
			gensymed_symbol_4;
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qx_offset;
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp_2,FIX((SI_Long)1L)) = Qx_offset;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol_3);
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
		gensymed_symbol_5 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 >>  -  - 
			gensymed_symbol_5;
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	    }
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol_3);
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
		gensymed_symbol_5 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 >>  -  - 
			gensymed_symbol_5;
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qy_offset;
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		SVREF(temp_2,FIX((SI_Long)3L)) = Qy_offset;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_4;
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_1 = gensymed_symbol_1 >>  -  - 
			gensymed_symbol_4;
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_2;
	    }
	    else {
		temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_4;
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_1 = gensymed_symbol_1 >>  -  - 
			gensymed_symbol_4;
		gensymed_symbol_3 = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol_3);
		item_or_value_1 = gensymed_symbol_1 - gensymed_symbol_4;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	}
	temp_3 = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp_3 = Nil;
    return VALUES_1(temp_3);
}

static Object string_constant_7;   /* "unknown color ~a" */

/* SET-NAME-BOX */
Object set_name_box(entity,evaluation_value)
    Object entity, evaluation_value;
{
    Object name_box_qm, specified_color_qm, temp, position_qm, gensymed_symbol;
    Object new_left_edge, new_top_edge, allow_name_box_creation, color_qm;
    Object needs_update_qm, temp_1, background_color, text_color;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(1);

    x_note_fn_call(109,160);
    name_box_qm = get_name_box_if_any_qm(entity);
    specified_color_qm = evaluation_value ? 
	    estructure_slot(evaluation_value,Qcolor,Nil) : Nil;
    if (specified_color_qm && ( 
	    !TRUEP(color_or_metacolor_p(estructure_slot(specified_color_qm,
	    Qtext_color,Nil))) ||  
	    !TRUEP(color_or_metacolor_p(estructure_slot(specified_color_qm,
	    Qbackground_color,Nil)))))
	temp = color_or_metacolor_p(estructure_slot(specified_color_qm,
		Qtext_color,Nil)) ? tformat_text_string(2,
		string_constant_7,estructure_slot(specified_color_qm,
		Qbackground_color,Nil)) : tformat_text_string(2,
		string_constant_7,estructure_slot(specified_color_qm,
		Qtext_color,Nil));
    else if ( !TRUEP(evaluation_value))
	temp = name_box_qm ? delete_frame(name_box_qm) : Nil;
    else {
	position_qm = estructure_slot(evaluation_value,Qposition,Nil);
	if (CONSP(position_qm) && EQ(M_CDR(position_qm),Qab_structure)) {
	    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(estructure_slot(position_qm,Qx_offset,
		    Nil));
	    new_left_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	else
	    new_left_edge = Nil;
	if (CONSP(position_qm) && EQ(M_CDR(position_qm),Qab_structure)) {
	    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(estructure_slot(position_qm,Qy_offset,
		    Nil));
	    new_top_edge = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    new_top_edge = Nil;
	allow_name_box_creation =  !TRUEP(name_box_qm) ? T : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Allow_name_box_creation,Qallow_name_box_creation,allow_name_box_creation,
		0);
	  update_name_box(entity);
	POP_SPECIAL();
	name_box_qm = get_name_box_if_any_qm(entity);
	if (name_box_qm) {
	    color_qm = specified_color_qm;
	    needs_update_qm = position_qm;
	    if (needs_update_qm);
	    else
		needs_update_qm = color_qm;
	    if (needs_update_qm)
		update_images_of_block(name_box_qm,T,Nil);
	    if (new_left_edge && new_top_edge) {
		temp = name_box_qm;
		gensymed_symbol_1 = IFIX(new_left_edge);
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol_1 = IFIX(new_top_edge);
		gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		shift_block(temp,temp_1,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2));
		enlarge_workspace_for_block_rectangle_if_necessary(name_box_qm,
			Nil);
	    }
	    if (CONSP(color_qm) && EQ(M_CDR(color_qm),Qab_structure)) {
		background_color = estructure_slot(color_qm,
			Qbackground_color,Nil);
		text_color = estructure_slot(color_qm,Qtext_color,Nil);
		change_color_of_text_box(5,name_box_qm,T,background_color,
			Kno_change,text_color);
	    }
	    if (needs_update_qm)
		update_images_of_block(name_box_qm,Nil,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GET-NAME-BOX-IF-ANY? */
Object get_name_box_if_any_qm(frame)
    Object frame;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(109,161);
    gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp) {
	temp_1 = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* INITIAL-TEXT-ALIGNMENT */
Object initial_text_alignment(text_box_subclass)
    Object text_box_subclass;
{
    Object temp;

    x_note_fn_call(109,162);
    temp = get_default_text_cell_line_justification(text_box_subclass);
    if (temp);
    else
	temp = Qleft;
    return VALUES_1(temp);
}

/* GET-TEXT-ALIGNMENT */
Object get_text_alignment(text_box)
    Object text_box;
{
    Object temp;

    x_note_fn_call(109,163);
    temp = get_text_cell_line_justification(ISVREF(text_box,(SI_Long)17L),
	    ISVREF(text_box,(SI_Long)18L));
    if (temp);
    else
	temp = Qleft;
    return VALUES_1(temp);
}

/* SET-TEXT-ALIGNMENT */
Object set_text_alignment(text_box,new_text_alignment)
    Object text_box, new_text_alignment;
{
    x_note_fn_call(109,164);
    update_text_box_alignment_override(text_box,new_text_alignment);
    return VALUES_1(Nil);
}

/* UPDATE-TEXT-BOX-ALIGNMENT-OVERRIDE */
Object update_text_box_alignment_override(text_box,new_text_alignment)
    Object text_box, new_text_alignment;
{
    Object temp, value, old_value, text_box_format, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long inside_left_edge, inside_top_edge, gensymed_symbol_4;
    SI_Long inside_right_edge, inside_bottom_edge;

    x_note_fn_call(109,165);
    temp = 
	    get_backing_store_default_text_cell_line_justification(ISVREF(ISVREF(text_box,
	    (SI_Long)1L),(SI_Long)1L));
    value = EQ(temp,EQ(new_text_alignment,Qleft) ? Nil : 
	    new_text_alignment) ? Nil : new_text_alignment;
    old_value = getfq_function_no_default(ISVREF(text_box,(SI_Long)18L),
	    Qtext_alignment);
    if ( !EQ(old_value,value)) {
	text_box_format = ISVREF(text_box,(SI_Long)17L);
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
	gensymed_symbol_3 = IFIX(ISVREF(text_box_format,(SI_Long)27L));
	inside_left_edge = gensymed_symbol_1 + gensymed_symbol_2 + 
		gensymed_symbol_3;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
	gensymed_symbol_3 = IFIX(ISVREF(text_box_format,(SI_Long)28L));
	inside_top_edge = gensymed_symbol_1 + gensymed_symbol_2 + 
		gensymed_symbol_3;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = (SI_Long)-3L;
	gensymed_symbol_3 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
	gensymed_symbol_4 = IFIX(ISVREF(text_box_format,(SI_Long)29L));
	inside_right_edge = gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = (SI_Long)-3L;
	gensymed_symbol_3 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
	gensymed_symbol_4 = IFIX(ISVREF(text_box_format,(SI_Long)30L));
	inside_bottom_edge = gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3 - gensymed_symbol_4;
	update_images_of_rectangle_of_block(text_box,T,
		FIX(inside_left_edge),FIX(inside_top_edge),
		FIX(inside_right_edge),FIX(inside_bottom_edge));
	change_text_box_property(text_box,Qtext_alignment,value);
	reformat_text_box_in_place(1,text_box);
	update_images_of_rectangle_of_block(text_box,Nil,
		FIX(inside_left_edge),FIX(inside_top_edge),
		FIX(inside_right_edge),FIX(inside_bottom_edge));
	update_subscriptions_from_virtual_attribute_change(text_box,
		get_property_value_function(3,
		get_symbol_properties_function(Qtext_alignment),
		Qvirtual_attribute,Nil),Qtext_box);
    }
    return VALUES_1(Nil);
}

static Object Qtitle_bar_format;   /* title-bar-format */

/* GET-TOTAL-TITLE-BAR-TEXT-WIDTH */
Object get_total_title_bar_text_width(text)
    Object text;
{
    Object text_box_format, text_element, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_maxmin_fl_, temp;

    x_note_fn_call(109,166);
    text_box_format = get_or_make_format_frame_function(get_ui_parameter(1,
	    Qtitle_bar_format));
    text_element = Nil;
    ab_loop_list_ = text;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loopvar__1 = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	ab_loopvar__1 = compute_width_of_text_line(6,text_element,Nil,Nil,
		ISVREF(text_box_format,(SI_Long)22L),
		ISVREF(text_box_format,(SI_Long)34L),Nil);
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    ab_loopvar_ = ab_loopvar__1;
	}
	else
	    ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qsmall;              /* small */

static Object Qleft_aligned_menu_item_format_new_small;  /* left-aligned-menu-item-format-new-small */

static Object Qleft_aligned_menu_item_format_new_large;  /* left-aligned-menu-item-format-new-large */

/* DRAW-TITLE-BAR-TEXT */
Object draw_title_bar_text(text,font_size,left_edge_of_cell_in_window,
	    top_edge_of_cell_in_window,right_edge_of_cell_in_window,
	    bottom_edge_of_cell_in_window)
    Object text, font_size, left_edge_of_cell_in_window;
    Object top_edge_of_cell_in_window, right_edge_of_cell_in_window;
    Object bottom_edge_of_cell_in_window;
{
    Object current_text_box_format, current_text_cell_plist, scale, value;
    Object max_width_in_workspace, temp_1, text_line, font_map, word_spacing;
    Object text_element, ab_loop_list_, width_in_workspace, ab_loopvar_;
    Object ab_loop_maxmin_fl_, text_with_ellipsis;
    SI_Long temp, temp_2;
    Declare_special(2);

    x_note_fn_call(109,167);
    current_text_box_format = 
	    get_or_make_format_frame_function(EQ(font_size,Qsmall) ? 
	    Qleft_aligned_menu_item_format_new_small : 
	    Qleft_aligned_menu_item_format_new_large);
    PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
	    1);
      current_text_cell_plist = Qnil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_text_cell_plist,Qcurrent_text_cell_plist,current_text_cell_plist,
	      0);
	if (EQ(font_size,Qsmall)) {
	    temp = IFIX(left_edge_of_cell_in_window) + (SI_Long)0L;
	    left_edge_of_cell_in_window = FIX(temp);
	    temp = IFIX(top_edge_of_cell_in_window) + (SI_Long)2L;
	    top_edge_of_cell_in_window = FIX(temp);
	    temp = IFIX(right_edge_of_cell_in_window) - (SI_Long)20L;
	    right_edge_of_cell_in_window = FIX(temp);
	    temp = IFIX(bottom_edge_of_cell_in_window) - (SI_Long)2L;
	    bottom_edge_of_cell_in_window = FIX(temp);
	}
	else {
	    left_edge_of_cell_in_window = 
		    FIXNUM_ADD1(left_edge_of_cell_in_window);
	    temp = IFIX(top_edge_of_cell_in_window) + (SI_Long)2L;
	    top_edge_of_cell_in_window = FIX(temp);
	    temp = IFIX(right_edge_of_cell_in_window) - (SI_Long)20L;
	    right_edge_of_cell_in_window = FIX(temp);
	    bottom_edge_of_cell_in_window = 
		    FIXNUM_SUB1(bottom_edge_of_cell_in_window);
	}
	scale = Current_image_x_scale;
	value = FIXNUM_MINUS(right_edge_of_cell_in_window,
		left_edge_of_cell_in_window);
	if (IFIX(scale) == (SI_Long)4096L)
	    max_width_in_workspace = value;
	else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	    max_width_in_workspace = inverse_scalef_function(scale,value);
	else if (IFIX(value) >= (SI_Long)0L) {
	    temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  
		    -  - (SI_Long)1L)) / IFIX(scale));
	    max_width_in_workspace = temp_1;
	}
	else {
	    temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	    temp_1 = FIXNUM_NEGATE(FIX(temp_2));
	    max_width_in_workspace = temp_1;
	}
	text_line = Nil;
	font_map = ISVREF(Current_text_box_format,(SI_Long)22L);
	word_spacing = ISVREF(Current_text_box_format,(SI_Long)34L);
	text_element = Nil;
	ab_loop_list_ = text;
	width_in_workspace = FIX((SI_Long)0L);
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	text_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	    text_line = text_element;
	    ab_loopvar_ = compute_width_of_text_line(6,text_element,Nil,
		    Nil,font_map,word_spacing,Nil);
	    if (ab_loop_maxmin_fl_) {
		ab_loop_maxmin_fl_ = Nil;
		width_in_workspace = ab_loopvar_;
	    }
	    else
		width_in_workspace = lmax(width_in_workspace,ab_loopvar_);
	    goto end_loop;
	}
	goto next_loop;
      end_loop:
	if ( ! !TRUEP(text_line)) {
	    if (IFIX(width_in_workspace) + (SI_Long)4L > 
		    IFIX(max_width_in_workspace)) {
		text_with_ellipsis = 
			convert_text_string_to_text(truncate_text_line_to_fit_width(4,
			text_line,max_width_in_workspace,font_map,
			word_spacing));
		draw_text_function(text_with_ellipsis,
			left_edge_of_cell_in_window,
			top_edge_of_cell_in_window,
			right_edge_of_cell_in_window,
			bottom_edge_of_cell_in_window);
		reclaim_text(text_with_ellipsis);
	    }
	    else
		draw_text_function(text,left_edge_of_cell_in_window,
			top_edge_of_cell_in_window,
			right_edge_of_cell_in_window,
			bottom_edge_of_cell_in_window);
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qsmall_statement_format;  /* small-statement-format */

static Object Qlarge;              /* large */

static Object Qstatement_format;   /* statement-format */

static Object Qextra_large;        /* extra-large */

static Object Qextra_large_statement_format;  /* extra-large-statement-format */

/* ORIENT-AND-SCALE-AND-PAINT-TEXT */
Object orient_and_scale_and_paint_text(description_element,
	    normalized_x_scale_init,normalized_y_scale_init,
	    normalized_width_init,normalized_height_init,
	    icon_reflection_and_rotation,color_value)
    Object description_element, normalized_x_scale_init;
    Object normalized_y_scale_init, normalized_width_init;
    Object normalized_height_init, icon_reflection_and_rotation, color_value;
{
    Object font, text_box_format_name, text_box_format, value, temp, temp_1;
    Object entire_text_line, point;
    Object text_drawing_element_reflection_and_rotation, font_map;
    Object formatted_text, text_element, ab_loop_list_;
    SI_Long normalized_x_scale, normalized_y_scale, normalized_width;
    SI_Long normalized_height, scale, unshifted_result, orientation_code, x, y;
    SI_Long word_spacing, line_spacing, line_height, baseline_position;
    SI_Long baseline_to_baseline_distance, width_of_longest_line, baseline;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(109,168);
    normalized_x_scale = IFIX(normalized_x_scale_init);
    normalized_y_scale = IFIX(normalized_y_scale_init);
    normalized_width = IFIX(normalized_width_init);
    normalized_height = IFIX(normalized_height_init);
    if (printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_oriented_text_in_scratchpad_rasters,
	    ISVREF(Current_window,(SI_Long)11L))) {
	font = simple_eval_for_icon(FOURTH(description_element));
	if (EQ(font,Qsmall))
	    text_box_format_name = Qsmall_statement_format;
	else if (EQ(font,Qlarge))
	    text_box_format_name = Qstatement_format;
	else if (EQ(font,Qextra_large))
	    text_box_format_name = Qextra_large_statement_format;
	else
	    text_box_format_name = Qnil;
	text_box_format = get_instance_with_name_if_any(Qformat_frame,
		text_box_format_name);
	if (text_box_format);
	else
	    text_box_format = make_format_frame(text_box_format_name);
	scale = MIN(normalized_x_scale,normalized_y_scale);
	value = text_cell_line_height_function(text_box_format);
	if (scale == (SI_Long)4096L)
	    temp = value;
	else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < scale && 
		scale < IFIX(Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = scale * IFIX(value) + (SI_Long)2048L;
	    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp = scalef_function(FIX(scale),value);
	temp_1 = FIX((SI_Long)3L);
	if ( !NUM_LT(temp,temp_1)) {
	    entire_text_line = 
		    simple_eval_for_icon(SECOND(description_element));
	    point = THIRD(description_element);
	    text_drawing_element_reflection_and_rotation = 
		    icon_reflection_and_rotation;
	    orientation_code = 
		    IFIX(get_orientation_code(text_drawing_element_reflection_and_rotation));
	    x = FIXNUMP(FIRST(point)) ? IFIX(FIRST(point)) : 
		    IFIX(simple_eval_for_icon(FIRST(point)));
	    y = FIXNUMP(SECOND(point)) ? IFIX(SECOND(point)) : 
		    IFIX(simple_eval_for_icon(SECOND(point)));
	    word_spacing = IFIX(ISVREF(text_box_format,(SI_Long)34L));
	    line_spacing = IFIX(ISVREF(text_box_format,(SI_Long)33L));
	    line_height = IFIX(ISVREF(text_box_format,(SI_Long)31L));
	    baseline_position = IFIX(ISVREF(text_box_format,(SI_Long)32L));
	    font_map = ISVREF(text_box_format,(SI_Long)22L);
	    baseline_to_baseline_distance = IFIX(ISVREF(text_box_format,
		    (SI_Long)31L)) + line_spacing;
	    result = format_text(11,
		    convert_text_string_to_text(copy_text_string(entire_text_line)),
		    text_box_format,Nil,FIX((SI_Long)100000L),Nil,Nil,Nil,
		    Nil,Nil,Nil,FIX((SI_Long)100000L));
	    MVS_2(result,formatted_text,temp);
	    width_of_longest_line = IFIX(temp);
	    baseline = y;
	    text_element = Nil;
	    ab_loop_list_ = formatted_text;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    text_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != 
			(SI_Long)0L) {
		orient_and_scale_and_paint_text_line(text_element,FIX(x),
			FIX(baseline),FIX(width_of_longest_line),
			FIX(normalized_x_scale),FIX(normalized_y_scale),
			FIX(normalized_width),FIX(normalized_height),
			FIX(orientation_code),
			text_drawing_element_reflection_and_rotation,
			icon_reflection_and_rotation,color_value,
			FIX(word_spacing),FIX(line_spacing),
			FIX(line_height),FIX(baseline_position),font_map);
		incff_1_arg = baseline_to_baseline_distance;
		baseline = baseline + incff_1_arg;
	    }
	    goto next_loop;
	  end_loop:;
	    reclaim_text(formatted_text);
	}
    }
    return VALUES_1(Nil);
}

/* ORIENT-AND-SCALE-AND-PAINT-TEXT-LINE */
Object orient_and_scale_and_paint_text_line(text_line,x_init,y_init,
	    width_of_longest_line_init,normalized_x_scale_init,
	    normalized_y_scale_init,normalized_width_init,
	    normalized_height_init,orientation_code_init,
	    orientation_symbol,icon_reflection_and_rotation,color_value,
	    word_spacing_init,line_spacing_init,line_height_init,
	    baseline_position_init,font_map)
    Object text_line, x_init, y_init, width_of_longest_line_init;
    Object normalized_x_scale_init, normalized_y_scale_init;
    Object normalized_width_init, normalized_height_init;
    Object orientation_code_init, orientation_symbol;
    Object icon_reflection_and_rotation, color_value, word_spacing_init;
    Object line_spacing_init, line_height_init, baseline_position_init;
    Object font_map;
{
    SI_Long x, y, width_of_longest_line, normalized_x_scale;
    SI_Long normalized_y_scale, normalized_width, normalized_height;
    SI_Long orientation_code, word_spacing, line_spacing, line_height;
    SI_Long baseline_position, left_edge, baseline, top_of_line, top_edge;
    SI_Long bottom_edge, right_edge, oriented_x_scale, oriented_y_scale;
    SI_Long scaled_baseline_in_window, unshifted_result, scaled_left_edge;
    SI_Long scaled_top_edge, scaled_right_edge, scaled_bottom_edge;
    SI_Long left_edge_of_line_of_text_in_window;

    x_note_fn_call(109,169);
    x = IFIX(x_init);
    y = IFIX(y_init);
    width_of_longest_line = IFIX(width_of_longest_line_init);
    normalized_x_scale = IFIX(normalized_x_scale_init);
    normalized_y_scale = IFIX(normalized_y_scale_init);
    normalized_width = IFIX(normalized_width_init);
    normalized_height = IFIX(normalized_height_init);
    orientation_code = IFIX(orientation_code_init);
    word_spacing = IFIX(word_spacing_init);
    line_spacing = IFIX(line_spacing_init);
    line_height = IFIX(line_height_init);
    baseline_position = IFIX(baseline_position_init);
    left_edge = x;
    baseline = y;
    top_of_line = baseline - baseline_position;
    top_edge = top_of_line - line_spacing;
    bottom_edge = top_of_line + line_height + line_spacing + (SI_Long)4L;
    right_edge = left_edge + width_of_longest_line;
    oriented_x_scale = IFIX(oriented_x_value(FIX(normalized_x_scale),
	    FIX(normalized_y_scale),FIX(orientation_code)));
    oriented_y_scale = IFIX(oriented_y_value(FIX(normalized_x_scale),
	    FIX(normalized_y_scale),FIX(orientation_code)));
    if (oriented_y_scale == (SI_Long)4096L)
	scaled_baseline_in_window = baseline;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    oriented_y_scale && oriented_y_scale < 
	    IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < baseline && 
	    baseline < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = oriented_y_scale * baseline + (SI_Long)2048L;
	scaled_baseline_in_window = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	scaled_baseline_in_window = 
		IFIX(scalef_function(FIX(oriented_y_scale),FIX(baseline)));
    if (oriented_x_scale == (SI_Long)4096L)
	scaled_left_edge = left_edge;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    oriented_x_scale && oriented_x_scale < 
	    IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < left_edge && 
	    left_edge < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = oriented_x_scale * left_edge + (SI_Long)2048L;
	scaled_left_edge = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	scaled_left_edge = IFIX(scalef_function(FIX(oriented_x_scale),
		FIX(left_edge)));
    if (oriented_y_scale == (SI_Long)4096L)
	scaled_top_edge = top_edge;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    oriented_y_scale && oriented_y_scale < 
	    IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < top_edge && 
	    top_edge < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = oriented_y_scale * top_edge + (SI_Long)2048L;
	scaled_top_edge = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	scaled_top_edge = IFIX(scalef_function(FIX(oriented_y_scale),
		FIX(top_edge)));
    if (oriented_x_scale == (SI_Long)4096L)
	scaled_right_edge = right_edge;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    oriented_x_scale && oriented_x_scale < 
	    IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < right_edge && 
	    right_edge < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = oriented_x_scale * right_edge + (SI_Long)2048L;
	scaled_right_edge = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	scaled_right_edge = IFIX(scalef_function(FIX(oriented_x_scale),
		FIX(right_edge)));
    if (oriented_y_scale == (SI_Long)4096L)
	scaled_bottom_edge = bottom_edge;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    oriented_y_scale && oriented_y_scale < 
	    IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < bottom_edge && 
	    bottom_edge < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = oriented_y_scale * bottom_edge + (SI_Long)2048L;
	scaled_bottom_edge = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	scaled_bottom_edge = IFIX(scalef_function(FIX(oriented_y_scale),
		FIX(bottom_edge)));
    left_edge_of_line_of_text_in_window = scaled_left_edge;
    orient_and_paint_line_of_text_to_current_scratchpad_raster(FIX(scaled_left_edge),
	    FIX(scaled_top_edge),FIX(scaled_right_edge),
	    FIX(scaled_bottom_edge),FIX(normalized_width),
	    FIX(normalized_height),text_line,orientation_symbol,
	    icon_reflection_and_rotation,FIX(word_spacing),font_map,
	    color_value,FIX(normalized_x_scale),FIX(normalized_y_scale),
	    FIX(left_edge_of_line_of_text_in_window),
	    FIX(scaled_baseline_in_window));
    return VALUES_1(Nil);
}

/* COMPUTE-EDGES-FOR-TEXT-DRAWING-ELEMENT */
Object compute_edges_for_text_drawing_element(line_drawing_element)
    Object line_drawing_element;
{
    Object entire_text_line, point, font, text_box_format_name;
    Object text_box_format, formatted_text, temp, text_element, ab_loop_list_;
    SI_Long line_spacing, text_line_height, baseline_to_baseline_distance;
    SI_Long text_line_width, width_of_longest_line, ab_loopvar_, temp_1;
    SI_Long number_of_lines, number_of_lines_minus_one;
    SI_Long total_baseline_to_baseline_height, text_cell_baseline_position;
    SI_Long baseline_in_window, font_descent, left, right, top, bottom;
    Object result;

    x_note_fn_call(109,170);
    entire_text_line = simple_eval_for_icon(SECOND(line_drawing_element));
    point = THIRD(line_drawing_element);
    font = simple_eval_for_icon(FOURTH(line_drawing_element));
    if (EQ(font,Qsmall))
	text_box_format_name = Qsmall_statement_format;
    else if (EQ(font,Qlarge))
	text_box_format_name = Qstatement_format;
    else if (EQ(font,Qextra_large))
	text_box_format_name = Qextra_large_statement_format;
    else
	text_box_format_name = Qnil;
    text_box_format = get_instance_with_name_if_any(Qformat_frame,
	    text_box_format_name);
    if (text_box_format);
    else
	text_box_format = make_format_frame(text_box_format_name);
    line_spacing = IFIX(ISVREF(text_box_format,(SI_Long)33L));
    text_line_height = IFIX(ISVREF(text_box_format,(SI_Long)31L));
    baseline_to_baseline_distance = text_line_height + line_spacing;
    text_line_width = (SI_Long)0L;
    result = format_text(11,
	    convert_text_string_to_text(copy_text_string(entire_text_line)),
	    text_box_format,Nil,FIX((SI_Long)100000L),Nil,Nil,Nil,Nil,Nil,
	    Nil,FIX((SI_Long)100000L));
    MVS_2(result,formatted_text,temp);
    width_of_longest_line = IFIX(temp);
    text_line_width = width_of_longest_line;
    text_element = Nil;
    ab_loop_list_ = formatted_text;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L)
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = IFIX(Qnil);
  end_1:;
    reclaim_text(formatted_text);
    number_of_lines = temp_1;
    number_of_lines_minus_one = number_of_lines - (SI_Long)1L;
    total_baseline_to_baseline_height = number_of_lines_minus_one * 
	    baseline_to_baseline_distance;
    text_cell_baseline_position = IFIX(ISVREF(text_box_format,(SI_Long)32L));
    baseline_in_window = FIXNUMP(SECOND(point)) ? IFIX(SECOND(point)) : 
	    IFIX(simple_eval_for_icon(SECOND(point)));
    font_descent = text_line_height - text_cell_baseline_position;
    left = FIXNUMP(FIRST(point)) ? IFIX(FIRST(point)) : 
	    IFIX(simple_eval_for_icon(FIRST(point)));
    right = left + text_line_width;
    top = baseline_in_window - text_cell_baseline_position;
    bottom = baseline_in_window + font_descent + 
	    total_baseline_to_baseline_height;
    return VALUES_4(FIX(left),FIX(top),FIX(right),FIX(bottom));
}

void boxes_INIT()
{
    Object temp, reclaim_structure_for_text_spot_1, type_description, temp_1;
    Object reclaim_structure_for_table_spot_1, temp_2;
    Object color_or_metacolor_evaluation_setter_1;
    Object color_or_metacolor_evaluation_getter_1;
    Object font_name_evaluation_setter_1, font_name_evaluation_getter_1;
    Object text_cell_colors_evaluation_setter_1;
    Object text_cell_colors_evaluation_getter_1;
    Object reclaim_structure_for_text_box_spot_1;
    Object reclaim_structure_for_label_box_spot_1;
    Object reclaim_structure_for_name_box_spot_1, gensymed_symbol;
    Object AB_package, Qset_text_alignment, Qget_text_alignment;
    Object Qinitial_text_alignment, list_constant_66, list_constant_65;
    Object list_constant_64, Kwithin_putter, Kevent_updates, list_constant_33;
    Object Qab_class, Qvirtual_attributes_local_to_class, Qset_name_box;
    Object Qget_name_box, Qinitial_name_box, list_constant_63;
    Object list_constant_62, list_constant_61, list_constant_19, Qab_or;
    Object list_constant_60, list_constant_59, list_constant_58;
    Object list_constant_57, list_constant_56, list_constant_55;
    Object list_constant_54, list_constant_53, list_constant_52;
    Object list_constant_51, list_constant_50, Qat_standard_position;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, Qkb_workspace, list_constant_37;
    Object list_constant_41, Qg2_reformat_text_string_to_fit_message;
    Object Qfunction_keeps_procedure_environment_valid_qm, string_constant_155;
    Object Qclasses_which_define, Qgenerate_spot;
    Object Qgenerate_spot_for_dialog_button, Qgenerate_spot_for_dialog_message;
    Object string_constant_154, string_constant_153, string_constant_52;
    Object string_constant_152, string_constant_151, string_constant_150;
    Object string_constant_149, string_constant_148, string_constant_147;
    Object Qdialog_message_format, string_constant_146;
    Object Qdefault_dialog_box_format, string_constant_145, list_constant_30;
    Object Qdialog_box_format, string_constant_144, string_constant_143;
    Object string_constant_142, string_constant_141, string_constant_129;
    Object string_constant_140, Qwide_caption_format;
    Object Qcorresponding_extra_large_font_format_name;
    Object Qextra_large_scrolling_editor_text_format;
    Object Qscrolling_editor_text_format, string_constant_139;
    Object string_constant_138, Qcorresponding_small_font_format_name;
    Object Qsmall_scrolling_editor_text_format, string_constant_137;
    Object string_constant_136, string_constant_135, string_constant_134;
    Object Qextra_large_borderless_free_text_format;
    Object Qborderless_free_text_format, string_constant_133;
    Object string_constant_132, Qsmall_borderless_free_text_format;
    Object string_constant_131, string_constant_130, string_constant_128;
    Object string_constant_127, list_constant_40, string_constant_126;
    Object string_constant_125, string_constant_115, string_constant_124;
    Object string_constant_123, Qextra_large_free_text_format;
    Object Qfree_text_format, string_constant_122, string_constant_121;
    Object Qsmall_free_text_format, string_constant_120, string_constant_119;
    Object string_constant_118, Qfree_text, string_constant_117;
    Object string_constant_116, string_constant_114, string_constant_113;
    Object Qitem, string_constant_112, string_constant_111;
    Object string_constant_110, Qslot_value_reclaimer;
    Object Qreclaim_runtime_structures_affected_by_this_statement_value;
    Object Qruntime_structures_affected_by_this_statement;
    Object Qinitialize_after_reading, Qinitialize_after_reading_for_text_box;
    Object Qinitialize, Qinitialize_for_statement, string_constant_109;
    Object string_constant_108, string_constant_107, string_constant_106;
    Object string_constant_105, list_constant_39, string_constant_104;
    Object string_constant_103, string_constant_102, string_constant_101;
    Object string_constant_100, string_constant_99;
    Object Qstatement_or_procedure_step, string_constant_98;
    Object string_constant_97, string_constant_96, list_constant_38;
    Object Qsmall_edit_cursor, Qcreate_icon_description, string_constant_93;
    Object string_constant_95, string_constant_94, Qedit_cursor;
    Object string_constant_92, Qdraw, Qdraw_for_blinker;
    Object Qinitialize_for_blinker, string_constant_91, string_constant_90;
    Object Qentity, string_constant_89, Qworkspace_name_box_format;
    Object string_constant_88, Qname_box_format, string_constant_87;
    Object Qlabel_box_format, string_constant_86, list_constant_36;
    Object string_constant_85, string_constant_79, Qgenerate_spot_for_name_box;
    Object Qtype_of_frame_represented, Qabstract_type, Qimage_plane_spot;
    Object Qenclosing_spot_type, Qinnermost_spot_p, Qtype_description_of_type;
    Object Qname_box_spot, Qreclaim_structure;
    Object Qoutstanding_name_box_spot_count;
    Object Qname_box_spot_structure_memory_usage, Qutilities2;
    Object string_constant_84;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_83, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qactivate_if_possible_and_propagate;
    Object Qactivate_if_possible_and_propagate_for_name_box, Qboxes;
    Object string_constant_82, list_constant_35, string_constant_81;
    Object string_constant_80, list_constant_34, Qexported_system_item;
    Object Qgenerate_spot_for_label_box, Qlabel_box_spot;
    Object Qoutstanding_label_box_spot_count;
    Object Qlabel_box_spot_structure_memory_usage, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, Qsubordinate_text_box, string_constant_73;
    Object Qscroll_block, Qscroll_block_for_text_box, Qdraw_for_text_box;
    Object float_constant_1, float_constant, Qslot_putter;
    Object Qput_text_cell_font_map, list_constant_32, list_constant_31, Qhm14;
    Object Qhc14, Qhm24, Qhc24, string_constant_72, Qdefault_text_cell_format;
    Object string_constant_71, Qtext_cell_format;
    Object Qreclaim_text_cell_font_map_value, string_constant_70;
    Object Qdefault_text_box_format, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object list_constant_29, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, Qput_text_cell_plist_for_text_box;
    Object Qput_box_translation_and_text_slot_value;
    Object Qput_box_translation_and_text_slot_value_for_text_box;
    Object Qput_box_translation_and_text, Qgeneric_method_lambda_list;
    Object list_constant_28, Qinitializing_qm, Qframe;
    Object Qgenerate_spot_for_text_box, Qtext_box_spot;
    Object Qoutstanding_text_box_spot_count;
    Object Qtext_box_spot_structure_memory_usage, string_constant_51;
    Object string_constant_50, Qinitialize_for_text_box;
    Object Qclass_slot_description_updater;
    Object Qupdate_default_text_box_colors_for_class, Qslot_value_writer;
    Object Qwrite_text_cell_colors_from_slot, Qtext_cell_colors, Qnamed;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_21, Qtype_specification_simple_expansion;
    Object list_constant_20, Qno_item;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_text_cell_colors_for_slot;
    Object string_constant_49, Qnil_function, Qfont_name, Qcolor_or_metacolor;
    Object list_constant_18, Qmedium_orchid, Qmedium_goldenrod, Qmedium_blue;
    Object Qmedium_aquamarine, Qmaroon, Qmagenta, Qlime_green, Qlight_gray;
    Object Qlight_blue, Qkhaki, Qindian_red, Qgreen_yellow, Qgreen, Qgray;
    Object Qgoldenrod, Qgold, Qforest_green, Qdim_gray, Qdark_slate_blue;
    Object Qdark_gray, Qcyan, Qcoral, Qcadet_blue, Qbrown, Qblue, Qaquamarine;
    Object list_constant_17, Qlight_goldenrod_yellow, Qpale_goldenrod;
    Object Qlight_cyan, Qpale_turquoise, Qpowder_blue, Qlight_steel_blue;
    Object Qlavender, Qazure, Qivory, Qantique_white, Qlinen, Qfloral_white;
    Object Qsmoke, Qyellow, Qwhite, Qwheat, Qviolet_red, Qviolet, Qturquoise;
    Object Qthistle, Qslate_blue, Qsky_blue, Qsienna, Qsalmon, Qred, Qpurple;
    Object Qplum, Qpink, Qpale_green, Qorange, Qextra_light_gray, Qlight_pink;
    Object Qbeige, Qlight_goldenrod, Qlight_yellow, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, list_constant_16, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, list_constant_15, Qtable, Qtable_spot;
    Object Qoutstanding_table_spot_count, Qtable_spot_structure_memory_usage;
    Object string_constant_11, string_constant_10, Qspot, Qtext_spot;
    Object Qoutstanding_text_spot_count, Qtext_spot_structure_memory_usage;
    Object string_constant_9, string_constant_8, Qreclaim_text;

    x_note_fn_call(109,171);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qlost_spaces = STATIC_SYMBOL("LOST-SPACES",AB_package);
    Qreclaim_text = STATIC_SYMBOL("RECLAIM-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_text,STATIC_FUNCTION(reclaim_text,NIL,
	    FALSE,1,1));
    Qparagraph = STATIC_SYMBOL("PARAGRAPH",AB_package);
    Qnewline = STATIC_SYMBOL("NEWLINE",AB_package);
    Qlinefeed = STATIC_SYMBOL("LINEFEED",AB_package);
    Qintercepted = STATIC_SYMBOL("INTERCEPTED",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_text_spot_g2_struct = 
	    STATIC_SYMBOL("TEXT-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_spot = STATIC_SYMBOL("TEXT-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_spot_g2_struct,
	    Qtext_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtext_spot,
	    Qg2_defstruct_structure_name_text_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_text_spot == UNBOUND)
	The_type_description_of_text_spot = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83*Cy1o83*Cy83Qy8n8k1l83Qy0000001l1m8x83Qyk3Cyk0k0");
    temp = The_type_description_of_text_spot;
    The_type_description_of_text_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_spot_g2_struct,
	    The_type_description_of_text_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtext_spot,The_type_description_of_text_spot,
	    Qtype_description_of_type);
    Qoutstanding_text_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEXT-SPOT-COUNT",AB_package);
    Qtext_spot_structure_memory_usage = 
	    STATIC_SYMBOL("TEXT-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_9 = STATIC_STRING("1q83*Cy8s83-say09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_text_spot_count);
    push_optimized_constant(Qtext_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_text_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_text_spots,
	    Chain_of_available_text_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_text_spots,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qtext_spot_count = STATIC_SYMBOL("TEXT-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_spot_count,Text_spot_count);
    record_system_variable(Qtext_spot_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_text_spots_vector == UNBOUND)
	Chain_of_available_text_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtext_spot_structure_memory_usage,
	    STATIC_FUNCTION(text_spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_text_spot_count,
	    STATIC_FUNCTION(outstanding_text_spot_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_text_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_text_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtext_spot,
	    reclaim_structure_for_text_spot_1);
    Kunknown = STATIC_SYMBOL("UNKNOWN",Pkeyword);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qspot),LIST_2(Qabstract_type,Qt),
	    LIST_2(Qtype_of_frame_represented,Qblock),
	    ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_table_spot_g2_struct = 
	    STATIC_SYMBOL("TABLE-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtable_spot = STATIC_SYMBOL("TABLE-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_table_spot_g2_struct,
	    Qtable_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtable_spot,
	    Qg2_defstruct_structure_name_table_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_table_spot == UNBOUND)
	The_type_description_of_table_spot = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83*wy1p83*wy83*Cy83Qy8n8k1l83*Cy0000001l1m8x83*Cyk3Jyk0k0");
    temp = The_type_description_of_table_spot;
    The_type_description_of_table_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_table_spot_g2_struct,
	    The_type_description_of_table_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtable_spot,The_type_description_of_table_spot,
	    Qtype_description_of_type);
    Qoutstanding_table_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-TABLE-SPOT-COUNT",AB_package);
    Qtable_spot_structure_memory_usage = 
	    STATIC_SYMBOL("TABLE-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q83*wy8s83-s4y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_table_spot_count);
    push_optimized_constant(Qtable_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_table_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TABLE-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_table_spots,
	    Chain_of_available_table_spots);
    record_system_variable(Qchain_of_available_table_spots,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qtable_spot_count = STATIC_SYMBOL("TABLE-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtable_spot_count,Table_spot_count);
    record_system_variable(Qtable_spot_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_table_spots_vector == UNBOUND)
	Chain_of_available_table_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtable_spot_structure_memory_usage,
	    STATIC_FUNCTION(table_spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_table_spot_count,
	    STATIC_FUNCTION(outstanding_table_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_table_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_table_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtable_spot,
	    reclaim_structure_for_table_spot_1);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qt),LIST_2(Qtype_of_frame_represented,
	    Qtable),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qimage_plane = STATIC_SYMBOL("IMAGE-PLANE",AB_package);
    Qx_in_window = STATIC_SYMBOL("X-IN-WINDOW",AB_package);
    Qy_in_window = STATIC_SYMBOL("Y-IN-WINDOW",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,FIX((SI_Long)20L),
	    FIX((SI_Long)50L),FIX((SI_Long)100L),FIX((SI_Long)120L));
    Ktight = STATIC_SYMBOL("TIGHT",Pkeyword);
    list_constant_15 = STATIC_CONS(Qnil,Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)4L,Ktight,Qt,Qnil,
	    list_constant_15);
    list_constant_2 = STATIC_LIST_STAR((SI_Long)4L,Qnil,Qnil,Qt,
	    list_constant_15);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_16 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qtext_box,list_constant_16);
    string_constant_12 = 
	    STATIC_STRING("1m1l8t1m83-Cy732Ay3-Gy3-ay3-Xy3-ly3-Xy3Sy3-fy3-ny3-ly3-my3Sy3-Uy3-Xy3Sy3-Wy3-by3-ly3-ly3-Xy3-Vy3-my3-Xy3-Wy3sy3Sy3uy3-Uy3-ky3wy3");
    string_constant_13 = 
	    STATIC_STRING("Sy3-wyut3-my3-Xy3-qy3-my3sy3Sy3-Zy3ky3fy3-my3-Xy3-qy3-my3eytt3-ty3-Yy3-ky3-hy3-fy3Sy3-Uy3-hy3-qy3fy3-my3-ky3-Ty3-gy3-ly3-ey3-Ty3");
    string_constant_14 = 
	    STATIC_STRING("-my3-by3-hy3-gy3fy3-Ty3-gy3-Wy3fy3-my3-Xy3-qy3-my3-vy3Sy3uy3-Uy3-ky3wy3Sy3-wyut3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3fy3-Yy3-hy3-ky3-f");
    string_constant_15 = 
	    STATIC_STRING("y3-Ty3-my3sy3Sy3-my3-Xy3-qy3-my3fy3-Yy3-hy3-ky3-fy3-Ty3-my3fy3-iy3-Ty3-ky3-my3ey3Sy3uy3-Uy3-ky3wyut3-Gy3-ay3-Xy3-ly3-Xy3Sy3-fy3-");
    string_constant_16 = 
	    STATIC_STRING("by3-gy3-ly3Sy3-Ty3-gy3-Wy3Sy3-fy3-Ty3-qy3-Xy3-ly3Sy3-ly3-ay3-hy3-ny3-ey3-Wy3Sy3-Uy3-Xy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3Sy3-py");
    string_constant_17 = 
	    STATIC_STRING("3-by3-my3-ay3Sy3-Ty3Sy3-gy3-Xy3-py3Sy3-Ty3-iy3-by3gy3Sy3-Gy3-ay3-Xy3Sy3-Vy3-ny3-ky3-ky3-Xy3-gy3-my3Sy3-fy3-hy3-Wy3-Xy3-ey3Sy3-by");
    string_constant_18 = 
	    STATIC_STRING("3-ly3Sy3-my3-hy3-hy3Sy3-wyut3-Vy3-hy3-gy3-Yy3-ny3-ly3-by3-gy3-Zy3sy3Sy3-wyut3uy3-ny3-ey3wy3uy3-ey3-by3wy3-fy3-by3-gy3-by3-fy3-ny");
    string_constant_19 = 
	    STATIC_STRING("3-fy3fy3-py3-by3-Wy3-my3-ay3fy3-hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3ey3Sy3Sy3-wyut3uy3-ey3-by3wy3-my3-Xy3-qy3-my3fy3-Vy3-Xy");
    string_constant_20 = 
	    STATIC_STRING("3-ey3-ey3fy3-Wy3-Xy3-ly3-by3-ky3-Xy3-Wy3fy3-fy3-Ty3-qy3-by3-fy3-ny3-fy3fy3-ey3-by3-gy3-Xy3fy3-fy3-Xy3-Ty3-ly3-ny3-ky3-Xy3fy3-Yy3");
    string_constant_21 = 
	    STATIC_STRING("-hy3-ky3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3xy3ey3Sy3-wyut3uy3-ey3-by3wy3-fy3-by3-gy3-by3-fy3-ny3-fy3fy3-ay3-Xy3-by3-Zy3-ay3-my3fy");
    string_constant_22 = 
	    STATIC_STRING("3-hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3ey3Sy3-wyut3uy3-ey3-by3wy3-fy3-Ty3-qy3-by3-fy3-ny3-fy3fy3-ay3-Xy3-by3-Zy3-ay3-my3fy3-");
    string_constant_23 = 
	    STATIC_STRING("hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3uy3hy3-ny3-ey3wy");
    string_constant_24 = 
	    STATIC_STRING("1u4z8r83ry83ry83-ly83-ly00001o1n8p83*ry83Gy1l8o1l8l1l83-3y000004z8r83-My83-My83-ly83-ly00001n1l8o1l8l1l83Cy000004z8r83xy83xy83-l");
    string_constant_25 = 
	    STATIC_STRING("y83-ly00001n1l83Ey1l8l1m83Dy53CyExport, writable000004z8r83=ky83=ky83-ly83-ly00001o1l8o1l8l1l83Cy1m83Dy53=cyThese values map to ");
    string_constant_26 = 
	    STATIC_STRING("text-cell-plist-for-text-box.<br> ~\n<li>magnification: [x-magnification: number, y-magnification: number], ~\n<li>highlight-color");
    string_constant_27 = 
	    STATIC_STRING(": color-symbol, ~\n<li>border-color: color-symbol, ~\n<li>line-color: color-symbol, <br>000004z8r83Bhy83Bhy83-ly83-ly00001u1l83Ey1");
    string_constant_28 = 
	    STATIC_STRING("l8l1l830Yy1l83Hy1m8p83A9y1l83Fy1l83-4y1l83Ny1l8z1m83Dy53CyExport, writable000004z8r8327y8327y83-ly83-ly0k001p1m8p83Sy1l83Ey1l8l1");
    string_constant_29 = 
	    STATIC_STRING("l83Ny1m83Dy5rNew api000004z8r83bhy83bhy83-ly83-ly00001p1m8p830iy1l83Ey1l8l1l83Ny1m83Dy5rNew api000004z8r83V1y83V1y83-ly83-ly0000");
    string_constant_30 = 
	    STATIC_STRING("1o1l83Ey1l8l1l83Ny1m83Dy5rNew api000004z8r8326y8326y83-ly83-ly0k001p1m8p83Sy1l83Ey1l8l1l83Ny1m83Dy5rNew api000004z8r83Uqy83Uqy83");
    string_constant_31 = 
	    STATIC_STRING("-ly83-ly03Bxxxy001p1m8p83Sy1l83Ey1l8l1l83Ny1m83Dy5rNew api00000");
    string_constant_32 = 
	    STATIC_STRING("1w8q1o83-ly1l9k8t1m83-Cy732Ay3-Gy3-ay3-Xy3-ly3-Xy3Sy3-fy3-ny3-ly3-my3Sy3-Uy3-Xy3Sy3-Wy3-by3-ly3-ly3-Xy3-Vy3-my3-Xy3-Wy3sy3Sy3uy3");
    string_constant_33 = 
	    STATIC_STRING("-Uy3-ky3wy3Sy3-wyut3-my3-Xy3-qy3-my3sy3Sy3-Zy3ky3fy3-my3-Xy3-qy3-my3eytt3-ty3-Yy3-ky3-hy3-fy3Sy3-Uy3-hy3-qy3fy3-my3-ky3-Ty3-gy3-");
    string_constant_34 = 
	    STATIC_STRING("ly3-ey3-Ty3-my3-by3-hy3-gy3fy3-Ty3-gy3-Wy3fy3-my3-Xy3-qy3-my3-vy3Sy3uy3-Uy3-ky3wy3Sy3-wyut3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3fy3-Yy");
    string_constant_35 = 
	    STATIC_STRING("3-hy3-ky3-fy3-Ty3-my3sy3Sy3-my3-Xy3-qy3-my3fy3-Yy3-hy3-ky3-fy3-Ty3-my3fy3-iy3-Ty3-ky3-my3ey3Sy3uy3-Uy3-ky3wyut3-Gy3-ay3-Xy3-ly3-");
    string_constant_36 = 
	    STATIC_STRING("Xy3Sy3-fy3-by3-gy3-ly3Sy3-Ty3-gy3-Wy3Sy3-fy3-Ty3-qy3-Xy3-ly3Sy3-ly3-ay3-hy3-ny3-ey3-Wy3Sy3-Uy3-Xy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy");
    string_constant_37 = 
	    STATIC_STRING("3-Wy3Sy3-py3-by3-my3-ay3Sy3-Ty3Sy3-gy3-Xy3-py3Sy3-Ty3-iy3-by3gy3Sy3-Gy3-ay3-Xy3Sy3-Vy3-ny3-ky3-ky3-Xy3-gy3-my3Sy3-fy3-hy3-Wy3-Xy");
    string_constant_38 = 
	    STATIC_STRING("3-ey3Sy3-by3-ly3Sy3-my3-hy3-hy3Sy3-wyut3-Vy3-hy3-gy3-Yy3-ny3-ly3-by3-gy3-Zy3sy3Sy3-wyut3uy3-ny3-ey3wy3uy3-ey3-by3wy3-fy3-by3-gy3");
    string_constant_39 = 
	    STATIC_STRING("-by3-fy3-ny3-fy3fy3-py3-by3-Wy3-my3-ay3fy3-hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3ey3Sy3Sy3-wyut3uy3-ey3-by3wy3-my3-Xy3-qy3-my");
    string_constant_40 = 
	    STATIC_STRING("3fy3-Vy3-Xy3-ey3-ey3fy3-Wy3-Xy3-ly3-by3-ky3-Xy3-Wy3fy3-fy3-Ty3-qy3-by3-fy3-ny3-fy3fy3-ey3-by3-gy3-Xy3fy3-fy3-Xy3-Ty3-ly3-ny3-ky3");
    string_constant_41 = 
	    STATIC_STRING("-Xy3fy3-Yy3-hy3-ky3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3xy3ey3Sy3-wyut3uy3-ey3-by3wy3-fy3-by3-gy3-by3-fy3-ny3-fy3fy3-ay3-Xy3-by3-Zy");
    string_constant_42 = 
	    STATIC_STRING("3-ay3-my3fy3-hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3ey3Sy3-wyut3uy3-ey3-by3wy3-fy3-Ty3-qy3-by3-fy3-ny3-fy3fy3-ay3-Xy3-by3-Zy3-");
    string_constant_43 = 
	    STATIC_STRING("ay3-my3fy3-hy3-Yy3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3uy3hy3-ny3-ey3wy1q83ry01n8p83*ry83Gy8o8l83-3y1p83-My08o8l83Cy1p83xy083Ey8l1m");
    string_constant_44 = 
	    STATIC_STRING("83Dy53CyExport, writable1q83=ky08o8l83Cy1m83Dy53=cyThese values map to text-cell-plist-for-text-box.<br> ~\n<li>magnification: [x");
    string_constant_45 = 
	    STATIC_STRING("-magnification: number, y-magnification: number], ~\n<li>highlight-color: color-symbol, ~\n<li>border-color: color-symbol, ~\n<li>l");
    string_constant_46 = 
	    STATIC_STRING("ine-color: color-symbol, <br>1w83Bhy083Ey8l830Yy83Hy1m8p83A9y83Fy83-4y83Ny8z1m83Dy53CyExport, writable1r8327yk1m8p83Sy83Ey8l83Ny");
    string_constant_47 = 
	    STATIC_STRING("1m83Dy5rNew api1r83bhy01m8p830iy83Ey8l83Ny1m83Dy5rNew api1q83V1y083Ey8l83Ny1m83Dy5rNew api1r8326yk1m8p83Sy83Ey8l83Ny1m83Dy5rNew ");
    string_constant_48 = 
	    STATIC_STRING("api1r83Uqy3Bxxxy1m8p83Sy83Ey8l83Ny1m83Dy5rNew api");
    temp = regenerate_optimized_constant(list(12,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23));
    temp_2 = regenerate_optimized_constant(list(8,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qtext_box,list_constant_16,Nil,temp,Nil,
	    temp_2,list_constant_16,regenerate_optimized_constant(list(17,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37,
	    string_constant_38,string_constant_39,string_constant_40,
	    string_constant_41,string_constant_42,string_constant_43,
	    string_constant_44,string_constant_45,string_constant_46,
	    string_constant_47,string_constant_48)),Nil);
    Text_box_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtext_box,
	    Class_description_gkbprop);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qcolor_or_metacolor),
	    Qtype_specification_simple_expansion,Qnil);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qaquamarine = STATIC_SYMBOL("AQUAMARINE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qblue = STATIC_SYMBOL("BLUE",AB_package);
    Qbrown = STATIC_SYMBOL("BROWN",AB_package);
    Qcadet_blue = STATIC_SYMBOL("CADET-BLUE",AB_package);
    Qcoral = STATIC_SYMBOL("CORAL",AB_package);
    Qcyan = STATIC_SYMBOL("CYAN",AB_package);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    Qdark_slate_blue = STATIC_SYMBOL("DARK-SLATE-BLUE",AB_package);
    Qdim_gray = STATIC_SYMBOL("DIM-GRAY",AB_package);
    Qforest_green = STATIC_SYMBOL("FOREST-GREEN",AB_package);
    Qgold = STATIC_SYMBOL("GOLD",AB_package);
    Qgoldenrod = STATIC_SYMBOL("GOLDENROD",AB_package);
    Qgray = STATIC_SYMBOL("GRAY",AB_package);
    Qgreen = STATIC_SYMBOL("GREEN",AB_package);
    Qgreen_yellow = STATIC_SYMBOL("GREEN-YELLOW",AB_package);
    Qindian_red = STATIC_SYMBOL("INDIAN-RED",AB_package);
    Qkhaki = STATIC_SYMBOL("KHAKI",AB_package);
    Qlight_blue = STATIC_SYMBOL("LIGHT-BLUE",AB_package);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Qlime_green = STATIC_SYMBOL("LIME-GREEN",AB_package);
    Qmagenta = STATIC_SYMBOL("MAGENTA",AB_package);
    Qmaroon = STATIC_SYMBOL("MAROON",AB_package);
    Qmedium_aquamarine = STATIC_SYMBOL("MEDIUM-AQUAMARINE",AB_package);
    Qmedium_blue = STATIC_SYMBOL("MEDIUM-BLUE",AB_package);
    Qmedium_goldenrod = STATIC_SYMBOL("MEDIUM-GOLDENROD",AB_package);
    Qmedium_orchid = STATIC_SYMBOL("MEDIUM-ORCHID",AB_package);
    Qorange = STATIC_SYMBOL("ORANGE",AB_package);
    Qpale_green = STATIC_SYMBOL("PALE-GREEN",AB_package);
    Qpink = STATIC_SYMBOL("PINK",AB_package);
    Qplum = STATIC_SYMBOL("PLUM",AB_package);
    Qpurple = STATIC_SYMBOL("PURPLE",AB_package);
    Qred = STATIC_SYMBOL("RED",AB_package);
    Qsalmon = STATIC_SYMBOL("SALMON",AB_package);
    Qsienna = STATIC_SYMBOL("SIENNA",AB_package);
    Qsky_blue = STATIC_SYMBOL("SKY-BLUE",AB_package);
    Qslate_blue = STATIC_SYMBOL("SLATE-BLUE",AB_package);
    Qthistle = STATIC_SYMBOL("THISTLE",AB_package);
    Qturquoise = STATIC_SYMBOL("TURQUOISE",AB_package);
    Qviolet = STATIC_SYMBOL("VIOLET",AB_package);
    Qviolet_red = STATIC_SYMBOL("VIOLET-RED",AB_package);
    Qwheat = STATIC_SYMBOL("WHEAT",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qyellow = STATIC_SYMBOL("YELLOW",AB_package);
    Qsmoke = STATIC_SYMBOL("SMOKE",AB_package);
    Qfloral_white = STATIC_SYMBOL("FLORAL-WHITE",AB_package);
    Qlinen = STATIC_SYMBOL("LINEN",AB_package);
    Qantique_white = STATIC_SYMBOL("ANTIQUE-WHITE",AB_package);
    Qivory = STATIC_SYMBOL("IVORY",AB_package);
    Qazure = STATIC_SYMBOL("AZURE",AB_package);
    Qlavender = STATIC_SYMBOL("LAVENDER",AB_package);
    Qlight_steel_blue = STATIC_SYMBOL("LIGHT-STEEL-BLUE",AB_package);
    Qpowder_blue = STATIC_SYMBOL("POWDER-BLUE",AB_package);
    Qpale_turquoise = STATIC_SYMBOL("PALE-TURQUOISE",AB_package);
    Qlight_cyan = STATIC_SYMBOL("LIGHT-CYAN",AB_package);
    Qpale_goldenrod = STATIC_SYMBOL("PALE-GOLDENROD",AB_package);
    Qlight_goldenrod_yellow = STATIC_SYMBOL("LIGHT-GOLDENROD-YELLOW",
	    AB_package);
    Qlight_yellow = STATIC_SYMBOL("LIGHT-YELLOW",AB_package);
    Qlight_goldenrod = STATIC_SYMBOL("LIGHT-GOLDENROD",AB_package);
    Qbeige = STATIC_SYMBOL("BEIGE",AB_package);
    Qlight_pink = STATIC_SYMBOL("LIGHT-PINK",AB_package);
    Qextra_light_gray = STATIC_SYMBOL("EXTRA-LIGHT-GRAY",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)5L,Qlight_yellow,
	    Qlight_goldenrod,Qbeige,Qlight_pink,Qextra_light_gray);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)32L,Qorange,Qpale_green,
	    Qpink,Qplum,Qpurple,Qred,Qsalmon,Qsienna,Qsky_blue,Qslate_blue,
	    Qtan,Qthistle,Qturquoise,Qviolet,Qviolet_red,Qwheat,Qwhite,
	    Qyellow,Qsmoke,Qfloral_white,Qlinen,Qantique_white,Qivory,
	    Qazure,Qlavender,Qlight_steel_blue,Qpowder_blue,
	    Qpale_turquoise,Qlight_cyan,Qpale_goldenrod,
	    Qlight_goldenrod_yellow,list_constant_17);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)32L,Qmember,Qforeground,
	    Qbackground,Qtransparent,Qaquamarine,Qblack,Qblue,Qbrown,
	    Qcadet_blue,Qcoral,Qcyan,Qdark_gray,Qdark_slate_blue,Qdim_gray,
	    Qforest_green,Qgold,Qgoldenrod,Qgray,Qgreen,Qgreen_yellow,
	    Qindian_red,Qkhaki,Qlight_blue,Qlight_gray,Qlime_green,
	    Qmagenta,Qmaroon,Qmedium_aquamarine,Qmedium_blue,
	    Qmedium_goldenrod,Qmedium_orchid,list_constant_18);
    define_type_specification_explicit_complex_type(Qcolor_or_metacolor,
	    list_constant_4);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    color_or_metacolor_evaluation_setter_1 = 
	    STATIC_FUNCTION(color_or_metacolor_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qcolor_or_metacolor,
	    color_or_metacolor_evaluation_setter_1);
    color_or_metacolor_evaluation_getter_1 = 
	    STATIC_FUNCTION(color_or_metacolor_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qcolor_or_metacolor,
	    color_or_metacolor_evaluation_getter_1);
    Qfont_name = STATIC_SYMBOL("FONT-NAME",AB_package);
    set_property_value_function(get_symbol_properties_function(Qfont_name),
	    Qtype_specification_simple_expansion,Qnil);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)4L,Qmember,Qsmall,Qlarge,
	    Qextra_large);
    define_type_specification_explicit_complex_type(Qfont_name,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,Qfont_name);
    font_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(font_name_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfont_name,
	    font_name_evaluation_setter_1);
    font_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(font_name_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfont_name,
	    font_name_evaluation_getter_1);
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    string_constant_49 = 
	    STATIC_STRING("1p1o83A9y1m9k83Zy09l1m83A9y83-sVy1n83-sVy83-sUy1ll1n83-sVy1n83-sUy1m9k83-Zy83-sVy2lln1n83-sUy1n83-EZy1m9k83*Iy83*uy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnil_function);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_49));
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qtext_cell_colors = STATIC_SYMBOL("TEXT-CELL-COLORS",AB_package);
    Qcompile_text_cell_colors_for_slot = 
	    STATIC_SYMBOL("COMPILE-TEXT-CELL-COLORS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_text_cell_colors_for_slot,
	    STATIC_FUNCTION(compile_text_cell_colors_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qtext_cell_colors,
	    SYMBOL_FUNCTION(Qcompile_text_cell_colors_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qtext_cell_colors,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_19 = STATIC_CONS(Qno_item,Qnil);
    list_constant_20 = STATIC_CONS(Qsequence,Qnil);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_19,
	    list_constant_20);
    set_property_value_function(get_symbol_properties_function(Qtext_cell_colors),
	    Qtype_specification_simple_expansion,list_constant_21);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qregion = STATIC_SYMBOL("REGION",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)5L,Qmember,Qborder_color,
	    Qbackground_color,Qtext_color,Qline_color);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qregion,list_constant_22);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qcolor,list_constant_3);
    list_constant_25 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_24);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_25);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_26,
	    FIX((SI_Long)1L));
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_19,
	    list_constant_27);
    define_type_specification_explicit_complex_type(Qtext_cell_colors,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qtext_cell_colors);
    text_cell_colors_evaluation_setter_1 = 
	    STATIC_FUNCTION(text_cell_colors_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtext_cell_colors,
	    text_cell_colors_evaluation_setter_1);
    text_cell_colors_evaluation_getter_1 = 
	    STATIC_FUNCTION(text_cell_colors_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtext_cell_colors,
	    text_cell_colors_evaluation_getter_1);
    string_constant = STATIC_STRING("none");
    string_constant_1 = STATIC_STRING("~(~a is ~a~)");
    string_constant_2 = STATIC_STRING("; ");
    Qwrite_text_cell_colors_from_slot = 
	    STATIC_SYMBOL("WRITE-TEXT-CELL-COLORS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_text_cell_colors_from_slot,
	    STATIC_FUNCTION(write_text_cell_colors_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qtext_cell_colors,
	    SYMBOL_FUNCTION(Qwrite_text_cell_colors_from_slot),
	    Qslot_value_writer);
    Qdefault_text_box_colors_for_class = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-COLORS-FOR-CLASS",AB_package);
    Qupdate_default_text_box_colors_for_class = 
	    STATIC_SYMBOL("UPDATE-DEFAULT-TEXT-BOX-COLORS-FOR-CLASS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_default_text_box_colors_for_class,
	    STATIC_FUNCTION(update_default_text_box_colors_for_class,NIL,
	    FALSE,2,2));
    Qclass_slot_description_updater = 
	    STATIC_SYMBOL("CLASS-SLOT-DESCRIPTION-UPDATER",AB_package);
    mutate_global_property(Qdefault_text_box_colors_for_class,
	    SYMBOL_FUNCTION(Qupdate_default_text_box_colors_for_class),
	    Qclass_slot_description_updater);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qinitialize_for_text_box = STATIC_SYMBOL("INITIALIZE-FOR-TEXT-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_text_box,
	    STATIC_FUNCTION(initialize_for_text_box,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_text_box);
    set_get(Qtext_box,Qinitialize,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qg2_defstruct_structure_name_text_box_spot_g2_struct = 
	    STATIC_SYMBOL("TEXT-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_box_spot = STATIC_SYMBOL("TEXT-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_box_spot_g2_struct,
	    Qtext_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtext_box_spot,
	    Qg2_defstruct_structure_name_text_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_text_box_spot == UNBOUND)
	The_type_description_of_text_box_spot = Nil;
    string_constant_50 = 
	    STATIC_STRING("43Dy8m832my1p832my83*Cy83Qy8n8k1l83*Cy0000001l1m8x83*Cyk3Cyk0k0");
    temp = The_type_description_of_text_box_spot;
    The_type_description_of_text_box_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_50));
    mutate_global_property(Qg2_defstruct_structure_name_text_box_spot_g2_struct,
	    The_type_description_of_text_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtext_box_spot,
	    The_type_description_of_text_box_spot,Qtype_description_of_type);
    Qoutstanding_text_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEXT-BOX-SPOT-COUNT",AB_package);
    Qtext_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("TEXT-BOX-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_51 = STATIC_STRING("1q832my8s83-sTy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_text_box_spot_count);
    push_optimized_constant(Qtext_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_51));
    Qchain_of_available_text_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_text_box_spots,
	    Chain_of_available_text_box_spots);
    record_system_variable(Qchain_of_available_text_box_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qtext_box_spot_count = STATIC_SYMBOL("TEXT-BOX-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_box_spot_count,Text_box_spot_count);
    record_system_variable(Qtext_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_text_box_spots_vector == UNBOUND)
	Chain_of_available_text_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtext_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(text_box_spot_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_text_box_spot_count,
	    STATIC_FUNCTION(outstanding_text_box_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_text_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_text_box_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtext_box_spot,
	    reclaim_structure_for_text_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_box_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qtext_box),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qgenerate_spot_for_text_box = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_text_box,
	    STATIC_FUNCTION(generate_spot_for_text_box,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_text_box);
    set_get(Qtext_box,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    alias_slot_name(3,Qbox_translation_and_text,Qtext,Qtext_box);
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qinitializing_qm = STATIC_SYMBOL("INITIALIZING\?",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)3L,Qframe,
	    Qbox_translation_and_text,Qinitializing_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qput_box_translation_and_text_slot_value,
	    list_constant_28,Qgeneric_method_lambda_list);
    Qput_box_translation_and_text = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text,
	    STATIC_FUNCTION(put_box_translation_and_text,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qbox_translation_and_text,
	    SYMBOL_FUNCTION(Qput_box_translation_and_text),Qslot_putter);
    Qput_box_translation_and_text_slot_value_for_text_box = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-TEXT-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_text_box,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_text_box,
	    NIL,FALSE,3,3));
    temp_1 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_text_box);
    set_get(Qtext_box,Qput_box_translation_and_text_slot_value,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_1,
	    Qclasses_which_define);
    Qhighlight_color = STATIC_SYMBOL("HIGHLIGHT-COLOR",AB_package);
    Qput_text_cell_plist_for_text_box = 
	    STATIC_SYMBOL("PUT-TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qput_text_cell_plist_for_text_box,
	    STATIC_FUNCTION(put_text_cell_plist_for_text_box,NIL,FALSE,3,3));
    mutate_global_property(Qtext_cell_plist_for_text_box,
	    SYMBOL_FUNCTION(Qput_text_cell_plist_for_text_box),Qslot_putter);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    list_constant_29 = STATIC_CONS(Qformat_frame,Qnil);
    check_if_superior_classes_are_defined(Qtext_box_format,list_constant_29);
    string_constant_52 = STATIC_STRING("0");
    string_constant_53 = 
	    STATIC_STRING("13Py4z8r83ny83ny83-My83-My01l83-ry001n1m8p831wy1l8o1l8l000004z8r83-Ny83-Ny83-My83-My00001n1m8p83*xy1l8o1l8l000004z8r83*Ky83*Ky83");
    string_constant_54 = 
	    STATIC_STRING("-My83-My00001n1m8p83*xy1l8o1l8l000004z8r837Wy837Wy83-My83-My00001n1m8p83Udy1l8o1l8l000004z8r837Xy837Xy83-My83-My00001n1m8p83Udy1");
    string_constant_55 = 
	    STATIC_STRING("l8o1l8l000004z8r83by83by83-My83-My0w001n1m8p83*4y1l8o1l8l000004z8r83ay83ay83-My83-My0t001n1m8p83*4y1l8o1l8l000004z8r83Wy83Wy83-M");
    string_constant_56 = 
	    STATIC_STRING("y83-My0w001n1m8p83*4y1l8o1l8l000004z8r83cy83cy83-My83-My0s001n1m8p83*4y1l8o1l8l000004z8r83ty83ty83-My83-My0z001n1m8p83*4y1l8o1l8");
    string_constant_57 = 
	    STATIC_STRING("l000004z8r83sy83sy83-My83-My0w001n1m8p83*4y1l8o1l8l000004z8r83uy83uy83-My83-My0p001n1m8p83*4y1l8o1l8l000004z8r83-7y83-7y83-My83-");
    string_constant_58 = 
	    STATIC_STRING("My03K+y001n1m8p83AVy1l8o1l8l000004z8r83*3y83*3y83-My83-My038+y001n1m8p83AVy1l8o1l8l000004z8r83*+y83*+y83-My83-My03q+y001n1m8p83A");
    string_constant_59 = 
	    STATIC_STRING("Vy1l8o1l8l000004z8r83ky83ky83-My83-My03Ky001n1m8p83*4y1l8o1l8l000004z8r83-=y83-=y83-My83-My0k001n1m8p83*4y1l8o1l8l000004z8r83wy8");
    string_constant_60 = 
	    STATIC_STRING("3wy83-My83-My00001n1m8p833Xy1l8o1l8l000004z8r83-By83-By83-My83-My00001n1m8p832Uy1l8o1l8l000004z8r83iy83iy83-My83-My032Cy001n1m8p");
    string_constant_61 = 
	    STATIC_STRING("83*4y1l8o1l8l000004z8r83*ay83*ay83-My83-My03KMSy001n1m8p83*4y1l8o1l8l000004z8r83AAy83AAy83-My83-My00001m1l8o1l8l000004z8r83*=y83");
    string_constant_62 = 
	    STATIC_STRING("*=y83-My83-My0m001n1m8p83*4y1l8o1l8l000004z8r83*1y83*1y83-My83-My0m001n1m8p83*4y1l8o1l8l000004z8r83*0y83*0y83-My83-My0m001n1m8p8");
    string_constant_63 = 
	    STATIC_STRING("3*4y1l8o1l8l000004z8r83**y83**y83-My83-My0m001n1m8p83*4y1l8o1l8l000004z8r83*ky83*ky83-My83-My00001n1m8p83*xy1l8o1l8l000004z8r832");
    string_constant_64 = 
	    STATIC_STRING("cy832cy83-My83-My0k001n1m8p83*4y1l8o1l8l000004z8r83Vey83Vey83-My83-My0k001n1m8p83*4y1l8o1l8l00000");
    string_constant_65 = 
	    STATIC_STRING("13Ry8q1m83-My1l831Fy1p83ny1l83-ry1m8p831wy8o8l1p83-Ny01m8p83*xy8o8l1p83*Ky01m8p83*xy8o8l1p837Wy01m8p83Udy8o8l1p837Xy01m8p83Udy8o");
    string_constant_66 = 
	    STATIC_STRING("8l1p83byw1m8p83*4y8o8l1p83ayt1m8p83*4y8o8l1p83Wyw1m8p83*4y8o8l1p83cys1m8p83*4y8o8l1p83tyz1m8p83*4y8o8l1p83syw1m8p83*4y8o8l1p83uy");
    string_constant_67 = 
	    STATIC_STRING("p1m8p83*4y8o8l1p83-7y3K+y1m8p83AVy8o8l1p83*3y38+y1m8p83AVy8o8l1p83*+y3q+y1m8p83AVy8o8l1p83ky3Ky1m8p83*4y8o8l1p83-=yk1m8p83*4y8o8");
    string_constant_68 = 
	    STATIC_STRING("l1p83wy01m8p833Xy8o8l1p83-By01m8p832Uy8o8l1p83iy32Cy1m8p83*4y8o8l1p83*ay3KMSy1m8p83*4y8o8l1o83AAy08o8l1p83*=ym1m8p83*4y8o8l1p83*");
    string_constant_69 = 
	    STATIC_STRING("1ym1m8p83*4y8o8l1p83*0ym1m8p83*4y8o8l1p83**ym1m8p83*4y8o8l1p83*ky01m8p83*xy8o8l1p832cyk1m8p83*4y8o8l1p83Veyk1m8p83*4y8o8l");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(list(12,string_constant_53,
	    string_constant_54,string_constant_55,string_constant_56,
	    string_constant_57,string_constant_58,string_constant_59,
	    string_constant_60,string_constant_61,string_constant_62,
	    string_constant_63,string_constant_64));
    add_class_to_environment(9,Qtext_box_format,list_constant_29,Nil,temp,
	    Nil,temp_2,list_constant_29,
	    regenerate_optimized_constant(LIST_5(string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69)),Nil);
    Qdefault_text_box_format = STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT",
	    AB_package);
    string_constant_70 = STATIC_STRING("1l83-My");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qdefault_text_box_format,
	    regenerate_optimized_constant(string_constant_70),
	    Qformat_description);
    Qtext_cell_font_map = STATIC_SYMBOL("TEXT-CELL-FONT-MAP",AB_package);
    Qreclaim_text_cell_font_map_value = 
	    STATIC_SYMBOL("RECLAIM-TEXT-CELL-FONT-MAP-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_text_cell_font_map_value,
	    STATIC_FUNCTION(reclaim_text_cell_font_map_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qtext_cell_font_map,
	    SYMBOL_FUNCTION(Qreclaim_text_cell_font_map_value),
	    Qslot_value_reclaimer);
    Qtext_cell_format = STATIC_SYMBOL("TEXT-CELL-FORMAT",AB_package);
    list_constant_30 = STATIC_CONS(Qtext_box_format,Qnil);
    check_if_superior_classes_are_defined(Qtext_cell_format,list_constant_30);
    string_constant_71 = STATIC_STRING("1m8q1m83-Qy1l83-My");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(string_constant_52);
    add_class_to_environment(9,Qtext_cell_format,list_constant_30,Nil,temp,
	    Nil,temp_2,list_constant_30,
	    regenerate_optimized_constant(string_constant_71),Nil);
    Qdefault_text_cell_format = STATIC_SYMBOL("DEFAULT-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_72 = STATIC_STRING("1l83-Qy");
    mutate_global_property(Qdefault_text_cell_format,
	    regenerate_optimized_constant(string_constant_72),
	    Qformat_description);
    Qtext_alignment = STATIC_SYMBOL("TEXT-ALIGNMENT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qjustified = STATIC_SYMBOL("JUSTIFIED",AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qtext_cell_line_quadding_qm = 
	    STATIC_SYMBOL("TEXT-CELL-LINE-QUADDING\?",AB_package);
    Qtext_cell_lines_justified_qm = 
	    STATIC_SYMBOL("TEXT-CELL-LINES-JUSTIFIED\?",AB_package);
    Qhc24 = STATIC_SYMBOL("HC24",AB_package);
    Qhm24 = STATIC_SYMBOL("HM24",AB_package);
    list_constant_31 = STATIC_CONS(Qhc24,Qhm24);
    Qhc14 = STATIC_SYMBOL("HC14",AB_package);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    list_constant_32 = STATIC_CONS(Qhc14,Qhm14);
    list_constant_9 = STATIC_LIST((SI_Long)2L,list_constant_31,
	    list_constant_32);
    string_constant_3 = 
	    STATIC_STRING("The obsolete font ~A, used in the just-read kb, has been changed to ~A.  ~\n                    Do a save to make this change permanent.");
    Qformat_change_qm = STATIC_SYMBOL("FORMAT-CHANGE\?",AB_package);
    Qput_text_cell_font_map = STATIC_SYMBOL("PUT-TEXT-CELL-FONT-MAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_text_cell_font_map,
	    STATIC_FUNCTION(put_text_cell_font_map,NIL,FALSE,3,3));
    mutate_global_property(Qtext_cell_font_map,
	    SYMBOL_FUNCTION(Qput_text_cell_font_map),Qslot_putter);
    if (Post_draw_methods_for_text_box_formats == UNBOUND)
	Post_draw_methods_for_text_box_formats = Qnil;
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Kwithout_text = STATIC_SYMBOL("WITHOUT-TEXT",Pkeyword);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Kjust_text = STATIC_SYMBOL("JUST-TEXT",Pkeyword);
    float_constant = STATIC_FLOAT(0.125);
    Minimum_magnification_for_text_boxes = float_constant;
    float_constant_1 = STATIC_FLOAT(4.0);
    Maximum_magnification_for_text_boxes = float_constant_1;
    Maximum_text_box_width_or_height = FIX((SI_Long)8000L);
    Qline_width = STATIC_SYMBOL("LINE-WIDTH",AB_package);
    Qword_spacing = STATIC_SYMBOL("WORD-SPACING",AB_package);
    Qleading = STATIC_SYMBOL("LEADING",AB_package);
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qmaximum_width_of_text_box_qm = 
	    STATIC_SYMBOL("MAXIMUM-WIDTH-OF-TEXT-BOX\?",AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    Qmaximum_height_of_text_box = 
	    STATIC_SYMBOL("MAXIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Kbleeding_on_all_sides = STATIC_SYMBOL("BLEEDING-ON-ALL-SIDES",Pkeyword);
    Qdraw_or_change_color_of_text_box = 
	    STATIC_SYMBOL("DRAW-OR-CHANGE-COLOR-OF-TEXT-BOX",AB_package);
    Qdraw_only_borders = STATIC_SYMBOL("DRAW-ONLY-BORDERS",AB_package);
    Qfree = STATIC_SYMBOL("FREE",AB_package);
    Qfree_text_attribute = STATIC_SYMBOL("FREE-TEXT-ATTRIBUTE",AB_package);
    Default_text_cell_background_color = Qtransparent;
    Qtext_highlight_bar_color = STATIC_SYMBOL("TEXT-HIGHLIGHT-BAR-COLOR",
	    AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Kno_change = STATIC_SYMBOL("NO-CHANGE",Pkeyword);
    Qhighlight = STATIC_SYMBOL("HIGHLIGHT",AB_package);
    Scheduled_text_highlighting = T;
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_box_color_pattern = STATIC_SYMBOL("TEXT-BOX-COLOR-PATTERN",
	    AB_package);
    Qborder = STATIC_SYMBOL("BORDER",AB_package);
    Qselective_redraw = STATIC_SYMBOL("SELECTIVE-REDRAW",AB_package);
    Qadd_line_of_text = STATIC_SYMBOL("ADD-LINE-OF-TEXT",AB_package);
    Qdraw_for_text_box = STATIC_SYMBOL("DRAW-FOR-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_text_box,
	    STATIC_FUNCTION(draw_for_text_box,NIL,FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdraw_for_text_box);
    set_get(Qtext_box,Qdraw,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qdraw,temp_1,Qclasses_which_define);
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qtransparent,Qbackground);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_or_change_color_of_text_box,
	    STATIC_FUNCTION(draw_or_change_color_of_text_box,NIL,FALSE,6,6));
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    Qpage = STATIC_SYMBOL("PAGE",AB_package);
    Qscroll_block_for_text_box = STATIC_SYMBOL("SCROLL-BLOCK-FOR-TEXT-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qscroll_block_for_text_box,
	    STATIC_FUNCTION(scroll_block_for_text_box,NIL,FALSE,4,4));
    Qscroll_block = STATIC_SYMBOL("SCROLL-BLOCK",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qscroll_block_for_text_box);
    set_get(Qtext_box,Qscroll_block,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qscroll_block),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qscroll_block,temp_1,Qclasses_which_define);
    if (Suppress_scrolling_into_view_global_flag_qm == UNBOUND)
	Suppress_scrolling_into_view_global_flag_qm = Nil;
    Qsuppressed = STATIC_SYMBOL("SUPPRESSED",AB_package);
    Qposition_of_vertical_elevator = 
	    STATIC_SYMBOL("POSITION-OF-VERTICAL-ELEVATOR",AB_package);
    Qposition_of_horizontal_elevator = 
	    STATIC_SYMBOL("POSITION-OF-HORIZONTAL-ELEVATOR",AB_package);
    Qsubordinate_text_box = STATIC_SYMBOL("SUBORDINATE-TEXT-BOX",AB_package);
    list_constant_33 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qsubordinate_text_box,
	    list_constant_33);
    string_constant_73 = STATIC_STRING("1m8q1m83A1y1l83-ly");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(string_constant_52);
    add_class_to_environment(9,Qsubordinate_text_box,list_constant_33,Nil,
	    temp,Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(string_constant_73),Nil);
    Subordinate_text_box_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsubordinate_text_box,
	    Class_description_gkbprop);
    Qlabel_box = STATIC_SYMBOL("LABEL-BOX",AB_package);
    list_constant_34 = STATIC_CONS(Qsubordinate_text_box,Qnil);
    check_if_superior_classes_are_defined(Qlabel_box,list_constant_34);
    string_constant_74 = 
	    STATIC_STRING("1m4z8r83xy83xy83TWy83TWy083TXy001n1l8l1l83Ey1m83Dy53CyExport, writable000004z8r835ky835ky83TWy83TWy01n1l83*py1l9k1l8331y001l1l8l");
    string_constant_75 = STATIC_STRING("00000");
    string_constant_76 = 
	    STATIC_STRING("1o8q1m83TWy1l83A1y1m83xy83TXy1m835ky1n1l83*py1l9k1l8331y");
    temp = regenerate_optimized_constant(string_constant_52);
    clear_optimized_constants();
    push_optimized_constant(Qdelete);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_74,
	    string_constant_75));
    clear_optimized_constants();
    push_optimized_constant(Qdelete);
    add_class_to_environment(9,Qlabel_box,list_constant_34,Nil,temp,Nil,
	    temp_2,list_constant_34,
	    regenerate_optimized_constant(string_constant_76),Nil);
    Qg2_defstruct_structure_name_label_box_spot_g2_struct = 
	    STATIC_SYMBOL("LABEL-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlabel_box_spot = STATIC_SYMBOL("LABEL-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_label_box_spot_g2_struct,
	    Qlabel_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlabel_box_spot,
	    Qg2_defstruct_structure_name_label_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_label_box_spot == UNBOUND)
	The_type_description_of_label_box_spot = Nil;
    string_constant_77 = 
	    STATIC_STRING("43Dy8m83kGy1q83kGy832my83*Cy83Qy8n8k1l832my0000001l1m8x832myk3Cyk0k0");
    temp = The_type_description_of_label_box_spot;
    The_type_description_of_label_box_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_77));
    mutate_global_property(Qg2_defstruct_structure_name_label_box_spot_g2_struct,
	    The_type_description_of_label_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlabel_box_spot,
	    The_type_description_of_label_box_spot,Qtype_description_of_type);
    Qoutstanding_label_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-LABEL-BOX-SPOT-COUNT",AB_package);
    Qlabel_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("LABEL-BOX-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_78 = STATIC_STRING("1q83kGy8s83-cBy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_label_box_spot_count);
    push_optimized_constant(Qlabel_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_78));
    Qchain_of_available_label_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LABEL-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_label_box_spots,
	    Chain_of_available_label_box_spots);
    record_system_variable(Qchain_of_available_label_box_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlabel_box_spot_count = STATIC_SYMBOL("LABEL-BOX-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlabel_box_spot_count,Label_box_spot_count);
    record_system_variable(Qlabel_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_label_box_spots_vector == UNBOUND)
	Chain_of_available_label_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlabel_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(label_box_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_label_box_spot_count,
	    STATIC_FUNCTION(outstanding_label_box_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_label_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_label_box_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qlabel_box_spot,
	    reclaim_structure_for_label_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_box_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qlabel_box),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qgenerate_spot_for_label_box = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-LABEL-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_label_box,
	    STATIC_FUNCTION(generate_spot_for_label_box,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_label_box);
    set_get(Qlabel_box,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qlabel_box,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    Qexported_system_item = STATIC_SYMBOL("EXPORTED-SYSTEM-ITEM",AB_package);
    list_constant_35 = STATIC_CONS(Qexported_system_item,list_constant_34);
    check_if_superior_classes_are_defined(Qname_box,list_constant_35);
    string_constant_79 = STATIC_STRING("1l1l83Iy");
    string_constant_80 = 
	    STATIC_STRING("1m4z8r83xy83xy835ny835ny083W6y001n1l8l1l83Ey1m83Dy53CyExport, writable000004z8r835ky835ky835ny835ny01n1l83*py1m9k+3Cy3-ay3-by3-W");
    string_constant_81 = 
	    STATIC_STRING("y3-Xy3Sy3-gy3-Ty3-fy3-Xykkkkkt3A++y1l8331y001m1l8l1l83-4y00000");
    string_constant_82 = 
	    STATIC_STRING("1o8q1n835ny1m838Iy83A1y83Iy1m83xy83W6y1n835ky1n1l83*py1m9k5thide name1l8331y83-4y");
    temp = regenerate_optimized_constant(string_constant_79);
    clear_optimized_constants();
    push_optimized_constant(Qdelete);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_80,
	    string_constant_81));
    clear_optimized_constants();
    push_optimized_constant(Qdelete);
    add_class_to_environment(9,Qname_box,list_constant_35,Nil,temp,Nil,
	    temp_2,list_constant_35,
	    regenerate_optimized_constant(string_constant_82),Nil);
    Name_box_class_description = 
	    lookup_global_or_kb_specific_property_value(Qname_box,
	    Class_description_gkbprop);
    Qallow_activation_of_name_boxes_p = 
	    STATIC_SYMBOL("ALLOW-ACTIVATION-OF-NAME-BOXES-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qallow_activation_of_name_boxes_p,
	    Allow_activation_of_name_boxes_p);
    Qboxes = STATIC_SYMBOL("BOXES",AB_package);
    record_system_variable(Qallow_activation_of_name_boxes_p,Qboxes,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qactivate_if_possible_and_propagate_for_name_box = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-NAME-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_name_box,
	    STATIC_FUNCTION(activate_if_possible_and_propagate_for_name_box,
	    NIL,FALSE,1,1));
    Qactivate_if_possible_and_propagate = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_name_box);
    set_get(Qname_box,Qactivate_if_possible_and_propagate,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_if_possible_and_propagate),
	    Qclasses_which_define);
    temp_1 = CONS(Qname_box,temp);
    mutate_global_property(Qactivate_if_possible_and_propagate,temp_1,
	    Qclasses_which_define);
    Qg2_defstruct_structure_name_name_box_spot_g2_struct = 
	    STATIC_SYMBOL("NAME-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qname_box_spot = STATIC_SYMBOL("NAME-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_name_box_spot_g2_struct,
	    Qname_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qname_box_spot,
	    Qg2_defstruct_structure_name_name_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_name_box_spot == UNBOUND)
	The_type_description_of_name_box_spot = Nil;
    string_constant_83 = 
	    STATIC_STRING("43Dy8m83kxy1q83kxy832my83*Cy83Qy8n8k1l832my0000001l1m8x832myk3Cyk0k0");
    temp = The_type_description_of_name_box_spot;
    The_type_description_of_name_box_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_83));
    mutate_global_property(Qg2_defstruct_structure_name_name_box_spot_g2_struct,
	    The_type_description_of_name_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qname_box_spot,
	    The_type_description_of_name_box_spot,Qtype_description_of_type);
    Qoutstanding_name_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-NAME-BOX-SPOT-COUNT",AB_package);
    Qname_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("NAME-BOX-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_84 = STATIC_STRING("1q83kxy8s83-g*y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_name_box_spot_count);
    push_optimized_constant(Qname_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_84));
    Qchain_of_available_name_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NAME-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_name_box_spots,
	    Chain_of_available_name_box_spots);
    record_system_variable(Qchain_of_available_name_box_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qname_box_spot_count = STATIC_SYMBOL("NAME-BOX-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qname_box_spot_count,Name_box_spot_count);
    record_system_variable(Qname_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_name_box_spots_vector == UNBOUND)
	Chain_of_available_name_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qname_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(name_box_spot_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_name_box_spot_count,
	    STATIC_FUNCTION(outstanding_name_box_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_name_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_name_box_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qname_box_spot,
	    reclaim_structure_for_name_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qname_box_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qname_box),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qgenerate_spot_for_name_box = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-NAME-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_name_box,
	    STATIC_FUNCTION(generate_spot_for_name_box,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_name_box);
    set_get(Qname_box,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qname_box,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qworkspace_name_box = STATIC_SYMBOL("WORKSPACE-NAME-BOX",AB_package);
    list_constant_36 = STATIC_CONS(Qname_box,Qnil);
    check_if_superior_classes_are_defined(Qworkspace_name_box,
	    list_constant_36);
    string_constant_85 = 
	    STATIC_STRING("1l4z8r83xy83xy83eXy83eXy083eYy001n1l8l1l83Ey1m83Dy53CyExport, writable00000");
    string_constant_86 = STATIC_STRING("1n8q1n83eXy1l835ny83Iy1m83xy83eYy");
    temp = regenerate_optimized_constant(string_constant_79);
    temp_2 = regenerate_optimized_constant(string_constant_85);
    add_class_to_environment(9,Qworkspace_name_box,list_constant_36,Nil,
	    temp,Nil,temp_2,list_constant_36,
	    regenerate_optimized_constant(string_constant_86),Nil);
    Workspace_name_box_class_description = 
	    lookup_global_or_kb_specific_property_value(Qworkspace_name_box,
	    Class_description_gkbprop);
    Qlabel_box_format = STATIC_SYMBOL("LABEL-BOX-FORMAT",AB_package);
    string_constant_87 = 
	    STATIC_STRING("13Jy83-My83kyk83-=yk83ny1l83-uy83*=yk83*1yk83*0yk83**yk83byt83ayq83Wyq83cym");
    mutate_global_property(Qlabel_box_format,
	    regenerate_optimized_constant(string_constant_87),
	    Qformat_description);
    Qname_box_format = STATIC_SYMBOL("NAME-BOX-FORMAT",AB_package);
    string_constant_88 = 
	    STATIC_STRING("13Hy83-My83byw83ayt83Wyw83cys83kyk83-=y3Ky83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qname_box_format,
	    regenerate_optimized_constant(string_constant_88),
	    Qformat_description);
    Qworkspace_name_box_format = STATIC_SYMBOL("WORKSPACE-NAME-BOX-FORMAT",
	    AB_package);
    string_constant_89 = 
	    STATIC_STRING("13Ny83-My83ny1l83-uy83*Ky83fy83-Ny83*2y83byv83ayv83Wyv83cyq83kyk83-=y3Ky83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qworkspace_name_box_format,
	    regenerate_optimized_constant(string_constant_89),
	    Qformat_description);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qg2gl_variable = STATIC_SYMBOL("G2GL-VARIABLE",AB_package);
    Qto_left = STATIC_SYMBOL("TO-LEFT",AB_package);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    if (Allow_name_box_creation == UNBOUND)
	Allow_name_box_creation = T;
    if (Allow_name_box_creation_without_workspace == UNBOUND)
	Allow_name_box_creation_without_workspace = Nil;
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qblinker = STATIC_SYMBOL("BLINKER",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_37 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qblinker,list_constant_37);
    string_constant_90 = 
	    STATIC_STRING("1l4z8r83HDy83HDy8350y8350y00001m1l8o1l8l00000");
    string_constant_91 = STATIC_STRING("1n8q1m8350y1l83-+y1o83HDy08o8l");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(string_constant_90);
    add_class_to_environment(9,Qblinker,list_constant_37,Nil,temp,Nil,
	    temp_2,list_constant_37,
	    regenerate_optimized_constant(string_constant_91),Nil);
    Qinitialize_for_blinker = STATIC_SYMBOL("INITIALIZE-FOR-BLINKER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_blinker,
	    STATIC_FUNCTION(initialize_for_blinker,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_blinker);
    set_get(Qblinker,Qinitialize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qblinker,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qdraw_blinker_in_xor = STATIC_SYMBOL("DRAW-BLINKER-IN-XOR",AB_package);
    Qdraw_for_blinker = STATIC_SYMBOL("DRAW-FOR-BLINKER",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_blinker,STATIC_FUNCTION(draw_for_blinker,
	    NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qdraw_for_blinker);
    set_get(Qblinker,Qdraw,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_1 = CONS(Qblinker,temp);
    mutate_global_property(Qdraw,temp_1,Qclasses_which_define);
    SET_SYMBOL_FUNCTION(Qdraw_blinker_in_xor,
	    STATIC_FUNCTION(draw_blinker_in_xor,NIL,FALSE,2,2));
    Qedit_cursor = STATIC_SYMBOL("EDIT-CURSOR",AB_package);
    list_constant_38 = STATIC_CONS(Qblinker,Qnil);
    check_if_superior_classes_are_defined(Qedit_cursor,list_constant_38);
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_92 = 
	    STATIC_STRING("1l4z8r8u8u83KFy83KFy01p8w9kws1l1q83qy1q1mkq1mpk1muq1msq1mpm1mmq1n1mpk1muq1msq1n1mpm1mkq1mpk1n1mpk1msq1mpm1n1mpm1mmq1mkq001o1l8l1");
    string_constant_93 = 
	    STATIC_STRING("l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_94 = 
	    STATIC_STRING("1n8q1m83KFy1l8350y1m8u1p8w9kws1l1q83qy1q1mkq1mpk1muq1msq1mpm1mmq1n1mpk1muq1msq1n1mpm1mkq1mpk1n1mpk1msq1mpm1n1mpm1mmq1mkq");
    temp = regenerate_optimized_constant(string_constant_52);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_92,
	    string_constant_93));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qedit_cursor,list_constant_38,Nil,temp,Nil,
	    temp_2,list_constant_38,
	    regenerate_optimized_constant(string_constant_94),Nil);
    Qsmall_edit_cursor = STATIC_SYMBOL("SMALL-EDIT-CURSOR",AB_package);
    check_if_superior_classes_are_defined(Qsmall_edit_cursor,list_constant_38);
    string_constant_95 = 
	    STATIC_STRING("1l4z8r8u8u83aRy83aRy01p8w9kso1l1q83qy1q1mko1mok1mso1mro1mol1mlo1n1mok1mso1mro1n1mol1mko1mok1n1mok1mro1mol1n1mol1mlo1mko001o1l8l1");
    string_constant_96 = 
	    STATIC_STRING("1n8q1m83aRy1l8350y1m8u1p8w9kso1l1q83qy1q1mko1mok1mso1mro1mol1mlo1n1mok1mso1mro1n1mol1mko1mok1n1mok1mro1mol1n1mol1mlo1mko");
    temp = regenerate_optimized_constant(string_constant_52);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_95,
	    string_constant_93));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qsmall_edit_cursor,list_constant_38,Nil,
	    temp,Nil,temp_2,list_constant_38,
	    regenerate_optimized_constant(string_constant_96),Nil);
    Qstatement_or_procedure_step = 
	    STATIC_SYMBOL("STATEMENT-OR-PROCEDURE-STEP",AB_package);
    check_if_superior_classes_are_defined(Qstatement_or_procedure_step,
	    list_constant_33);
    string_constant_97 = 
	    STATIC_STRING("1l4z8r83xy83xy83A=y83A=y0830qy001n1l8l1l83Ey1m83Dy53CyExport, writable00000");
    string_constant_98 = STATIC_STRING("1n8q1m83A=y1l83-ly1m83xy830qy");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(string_constant_97);
    add_class_to_environment(9,Qstatement_or_procedure_step,
	    list_constant_33,Nil,temp,Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(string_constant_98),Nil);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qitem,
	    Qstatement_or_procedure_step);
    check_if_superior_classes_are_defined(Qstatement,list_constant_39);
    string_constant_99 = STATIC_STRING("1p1m8v83*ry1l8t1l83-8y1l83Iy1l83Ly");
    string_constant_100 = 
	    STATIC_STRING("1m4z8r83xy83xy83*ry83*ry0830qy001n1l8l1m83Dy73*0y3-Xy3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-Wy3-Xy3-Yy3-Ty3-ny3-ey3-my3fy3-my3-Xy3-");
    string_constant_101 = 
	    STATIC_STRING("qy3-my3fy3-Uy3-hy3-qy3fy3-Yy3-hy3-ky3-fy3-Ty3-my3Sy3-my3-ry3-iy3-Xy3Sy3vy3Sy3-Yy3-hy3-ky3-fy3-Ty3-my3fy3-gy3-Ty3-fy3-Xy3ey3Sy3-T");
    string_constant_102 = 
	    STATIC_STRING("y3Sy3-ly3-ry3-fy3-Uy3-hy3-ey3ey3Sy3-wyut3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3-ny3-Xy3ey3Sy3-ly3-Xy3-iy3-Ty3-ky3-Ty3");
    string_constant_103 = 
	    STATIC_STRING("-my3-Xy3-ey3-ry3Sy3-py3-Xy3Sy3-Vy3-Ty3-gy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3Sy3-iy3-Ty3-ky3-my3Sy3-Vy3-hy3-iy3-by3-Xy3-ly3Sy3-hy3-Yy3Sy");
    string_constant_104 = 
	    STATIC_STRING("3-Yy3-hy3-ky3-fy3-Ty3-my3-ly3gy1l83Ey000004z8r83Zdy83Zdy83*ry83*ry00001n1l8l1l8o1m83Dy5sInternal00000");
    string_constant_105 = 
	    STATIC_STRING("1o8q1r83*ry1m83Ry83A=y1m8v83*ry8t83-8y83Iy83Ly1n83xy830qy1m83Dy73*0y3-Xy3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-Wy3-Xy3-Yy3-Ty3-ny3-");
    string_constant_106 = 
	    STATIC_STRING("ey3-my3fy3-my3-Xy3-qy3-my3fy3-Uy3-hy3-qy3fy3-Yy3-hy3-ky3-fy3-Ty3-my3Sy3-my3-ry3-iy3-Xy3Sy3vy3Sy3-Yy3-hy3-ky3-fy3-Ty3-my3fy3-gy3-");
    string_constant_107 = 
	    STATIC_STRING("Ty3-fy3-Xy3ey3Sy3-Ty3Sy3-ly3-ry3-fy3-Uy3-hy3-ey3ey3Sy3-wyut3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3-ny3-Xy3ey3Sy3-ly3-");
    string_constant_108 = 
	    STATIC_STRING("Xy3-iy3-Ty3-ky3-Ty3-my3-Xy3-ey3-ry3Sy3-py3-Xy3Sy3-Vy3-Ty3-gy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3Sy3-iy3-Ty3-ky3-my3Sy3-Vy3-hy3-iy3-by3-X");
    string_constant_109 = 
	    STATIC_STRING("y3-ly3Sy3-hy3-Yy3Sy3-Yy3-hy3-ky3-fy3-Ty3-my3-ly3gy1p83Zdy08l8o1m83Dy5sInternal");
    temp = regenerate_optimized_constant(string_constant_99);
    temp_2 = regenerate_optimized_constant(LIST_5(string_constant_100,
	    string_constant_101,string_constant_102,string_constant_103,
	    string_constant_104));
    add_class_to_environment(9,Qstatement,list_constant_39,Nil,temp,Nil,
	    temp_2,list_constant_39,
	    regenerate_optimized_constant(LIST_5(string_constant_105,
	    string_constant_106,string_constant_107,string_constant_108,
	    string_constant_109)),Nil);
    Statement_class_description = 
	    lookup_global_or_kb_specific_property_value(Qstatement,
	    Class_description_gkbprop);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qinitialize_for_statement = STATIC_SYMBOL("INITIALIZE-FOR-STATEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_statement,
	    STATIC_FUNCTION(initialize_for_statement,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_statement);
    set_get(Qstatement,Qinitialize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qstatement,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    string_constant_4 = 
	    STATIC_STRING("~NA had bad magnification information. It\'s been removed.");
    Qinitialize_after_reading_for_text_box = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_text_box,
	    STATIC_FUNCTION(initialize_after_reading_for_text_box,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_text_box);
    set_get(Qtext_box,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qtext_box,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qruntime_structures_affected_by_this_statement = 
	    STATIC_SYMBOL("RUNTIME-STRUCTURES-AFFECTED-BY-THIS-STATEMENT",
	    AB_package);
    Qreclaim_runtime_structures_affected_by_this_statement_value = 
	    STATIC_SYMBOL("RECLAIM-RUNTIME-STRUCTURES-AFFECTED-BY-THIS-STATEMENT-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_runtime_structures_affected_by_this_statement_value,
	    STATIC_FUNCTION(reclaim_runtime_structures_affected_by_this_statement_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qruntime_structures_affected_by_this_statement,
	    SYMBOL_FUNCTION(Qreclaim_runtime_structures_affected_by_this_statement_value),
	    Qslot_value_reclaimer);
    Qstatement_format = STATIC_SYMBOL("STATEMENT-FORMAT",AB_package);
    string_constant_110 = 
	    STATIC_STRING("13Jy83-My83ny1l83-uy83ty3Gy83syz83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=y3My83-By083-Ny083*ky0");
    mutate_global_property(Qstatement_format,
	    regenerate_optimized_constant(string_constant_110),
	    Qformat_description);
    Qsmall_statement_format = STATIC_SYMBOL("SMALL-STATEMENT-FORMAT",
	    AB_package);
    string_constant_111 = 
	    STATIC_STRING("13Ty83-My83ny1l83-ry83tyz83syw83uym83-7y3G+y83*3y3C+y83*+y3i+y83kyk83-=y3Gy83bys83ayo83Wys83cyo83-By083-Ny083*ky0");
    mutate_global_property(Qsmall_statement_format,
	    regenerate_optimized_constant(string_constant_111),
	    Qformat_description);
    Qcorresponding_small_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-SMALL-FONT-FORMAT-NAME",AB_package);
    mutate_global_property(Qstatement_format,Qsmall_statement_format,
	    Qcorresponding_small_font_format_name);
    Qextra_large_statement_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-STATEMENT-FORMAT",AB_package);
    string_constant_112 = 
	    STATIC_STRING("13Ty83-My83ny1l8311y83ty3My83sy3Fy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83kyk83-=y3Vy83byz83ayv83Wyz83cyu83-By083-Ny083*ky0");
    mutate_global_property(Qextra_large_statement_format,
	    regenerate_optimized_constant(string_constant_112),
	    Qformat_description);
    Qcorresponding_extra_large_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-EXTRA-LARGE-FONT-FORMAT-NAME",
	    AB_package);
    mutate_global_property(Qstatement_format,Qextra_large_statement_format,
	    Qcorresponding_extra_large_font_format_name);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    list_constant_40 = STATIC_CONS(Qitem,list_constant_33);
    check_if_superior_classes_are_defined(Qfree_text,list_constant_40);
    string_constant_113 = STATIC_STRING("1l1m8v8341y");
    string_constant_114 = 
	    STATIC_STRING("1n4z8r83=ky83=ky8341y8341y00001p1l8l1l8z1l8o1l83Cy1m83Dy53=cyThese values map to text-cell-plist-for-text-box.<br> ~\n<li>magnifi");
    string_constant_115 = 
	    STATIC_STRING("cation: [x-magnification: number, y-magnification: number], ~\n<li>highlight-color: color-symbol, ~\n<li>border-color: color-symbo");
    string_constant_116 = 
	    STATIC_STRING("l, ~\n<li>line-color: color-symbol, <br>000004z8r83ry83ry8341y8341y00001o1l8l1n8p83-dy83Gy1l8o1l83-3y000004z8r83xy83xy8341y8341y0");
    string_constant_117 = 
	    STATIC_STRING("83MOy001n1l8l1l83Ey1m83Dy53CyExport, writable00000");
    string_constant_118 = 
	    STATIC_STRING("1p8q1n8341y1m83Ry83-ly1m8v8341y1n83=ky08z1n83ry01n8p83-dy83Gy1m83xy83MOy");
    temp = regenerate_optimized_constant(string_constant_113);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_114,
	    string_constant_115,string_constant_116,string_constant_117));
    add_class_to_environment(9,Qfree_text,list_constant_40,Nil,temp,Nil,
	    temp_2,list_constant_40,
	    regenerate_optimized_constant(string_constant_118),Nil);
    Qfree_text_format = STATIC_SYMBOL("FREE-TEXT-FORMAT",AB_package);
    string_constant_119 = 
	    STATIC_STRING("13Py83-My83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yk83iy33my83*ay3Bay83-By083-Ny083*ky0");
    mutate_global_property(Qfree_text_format,
	    regenerate_optimized_constant(string_constant_119),
	    Qformat_description);
    Qsmall_free_text_format = STATIC_SYMBOL("SMALL-FREE-TEXT-FORMAT",
	    AB_package);
    string_constant_120 = 
	    STATIC_STRING("13Xy83-My83ny1l83-ry83tyz83syx83uym83-7y3G+y83*3y3C+y83*+y3i+y83kyk83-=yk83iy33my83*ay3Bay83-By083-Ny083*ky083bys83ayo83Wys83cyo");
    mutate_global_property(Qsmall_free_text_format,
	    regenerate_optimized_constant(string_constant_120),
	    Qformat_description);
    mutate_global_property(Qfree_text_format,Qsmall_free_text_format,
	    Qcorresponding_small_font_format_name);
    Qextra_large_free_text_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-FREE-TEXT-FORMAT",AB_package);
    string_constant_121 = 
	    STATIC_STRING("13Xy83-My83ny1l8311y83ty3My83sy3Fy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83kyk83-=yk83*ay35Ky83iy35Ky83byz83ayv83Wyz83cyu83-By083-Ny08");
    string_constant_122 = STATIC_STRING("3*ky0");
    mutate_global_property(Qextra_large_free_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_121,
	    string_constant_122)),Qformat_description);
    mutate_global_property(Qfree_text_format,Qextra_large_free_text_format,
	    Qcorresponding_extra_large_font_format_name);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    check_if_superior_classes_are_defined(Qborderless_free_text,
	    list_constant_40);
    string_constant_123 = STATIC_STRING("1l1m8v837py");
    string_constant_124 = 
	    STATIC_STRING("1n4z8r83=ky83=ky837py837py00001p1l8l1l8z1l8o1l83Cy1m83Dy53=cyThese values map to text-cell-plist-for-text-box.<br> ~\n<li>magnifi");
    string_constant_125 = 
	    STATIC_STRING("l, ~\n<li>line-color: color-symbol, <br>000004z8r83ry83ry837py837py00001o1l8l1n8p83-dy83Gy1l8o1l83-3y000004z8r83xy83xy837py837py0");
    string_constant_126 = 
	    STATIC_STRING("8351y001n1l8l1l83Ey1m83Dy53CyExport, writable00000");
    string_constant_127 = 
	    STATIC_STRING("1p8q1n837py1m83Ry83-ly1m8v837py1n83=ky08z1n83ry01n8p83-dy83Gy1m83xy8351y");
    temp = regenerate_optimized_constant(string_constant_123);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_124,
	    string_constant_115,string_constant_125,string_constant_126));
    add_class_to_environment(9,Qborderless_free_text,list_constant_40,Nil,
	    temp,Nil,temp_2,list_constant_40,
	    regenerate_optimized_constant(string_constant_127),Nil);
    Qborderless_free_text_format = 
	    STATIC_SYMBOL("BORDERLESS-FREE-TEXT-FORMAT",AB_package);
    string_constant_128 = 
	    STATIC_STRING("13fy83-My83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yk83iy33my83*ay3Bay83-By083-Ny083*ky083byq83ayn83Wyq83c");
    string_constant_129 = STATIC_STRING("ym83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qborderless_free_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_128,
	    string_constant_129)),Qformat_description);
    Qsmall_borderless_free_text_format = 
	    STATIC_SYMBOL("SMALL-BORDERLESS-FREE-TEXT-FORMAT",AB_package);
    string_constant_130 = 
	    STATIC_STRING("13fy83-My83ny1l83-ry83tyz83syx83uym83-7y3G+y83*3y3C+y83*+y3i+y83kyk83-=yk83iy33my83*ay3Bay83-By083-Ny083*ky083byp83aym83Wyp83cym");
    string_constant_131 = STATIC_STRING("83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qsmall_borderless_free_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_130,
	    string_constant_131)),Qformat_description);
    mutate_global_property(Qborderless_free_text_format,
	    Qsmall_borderless_free_text_format,
	    Qcorresponding_small_font_format_name);
    Qextra_large_borderless_free_text_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-BORDERLESS-FREE-TEXT-FORMAT",
	    AB_package);
    string_constant_132 = 
	    STATIC_STRING("13fy83-My83ny1l8311y83ty3My83sy3Fy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83kyk83-=yk83*ay35Ky83iy35Ky83bys83ayo83Wys83cyn83-By083-Ny08");
    string_constant_133 = STATIC_STRING("3*ky083*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qextra_large_borderless_free_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_132,
	    string_constant_133)),Qformat_description);
    mutate_global_property(Qborderless_free_text_format,
	    Qextra_large_borderless_free_text_format,
	    Qcorresponding_extra_large_font_format_name);
    Qscrolling_editor_text_format = 
	    STATIC_SYMBOL("SCROLLING-EDITOR-TEXT-FORMAT",AB_package);
    string_constant_134 = 
	    STATIC_STRING("13fy83-My83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=y3My83iy33my83*ay3RCy83-By083-Ny083*ky083byq83ayk83Wyq8");
    string_constant_135 = STATIC_STRING("3cyk83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qscrolling_editor_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_134,
	    string_constant_135)),Qformat_description);
    Qsmall_scrolling_editor_text_format = 
	    STATIC_SYMBOL("SMALL-SCROLLING-EDITOR-TEXT-FORMAT",AB_package);
    string_constant_136 = 
	    STATIC_STRING("13fy83-My83ny1l83-ry83tyz83syw83uym83-7y3G+y83*3y3C+y83*+y3i+y83kyk83-=y3Gy83iy33my83*ay3RCy83-By083-Ny083*ky083byp83ayk83Wyp83c");
    string_constant_137 = STATIC_STRING("yk83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qsmall_scrolling_editor_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_136,
	    string_constant_137)),Qformat_description);
    mutate_global_property(Qscrolling_editor_text_format,
	    Qsmall_scrolling_editor_text_format,
	    Qcorresponding_small_font_format_name);
    Qextra_large_scrolling_editor_text_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-SCROLLING-EDITOR-TEXT-FORMAT",
	    AB_package);
    string_constant_138 = 
	    STATIC_STRING("13fy83-My83ny1l8311y83ty3My83sy3Fy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83kyk83-=y3Vy83iy35Ky83*ay3RCy83bys83ayk83Wys83cyk83-By083-Ny");
    string_constant_139 = STATIC_STRING("083*ky083*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qextra_large_scrolling_editor_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_138,
	    string_constant_139)),Qformat_description);
    mutate_global_property(Qscrolling_editor_text_format,
	    Qextra_large_scrolling_editor_text_format,
	    Qcorresponding_extra_large_font_format_name);
    Qwide_caption_format = STATIC_SYMBOL("WIDE-CAPTION-FORMAT",AB_package);
    string_constant_140 = 
	    STATIC_STRING("13fy83-My83iy36uy83*ay3A0y83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yw83-By083-Ny083*ky083byq83ayn83Wyq83c");
    mutate_global_property(Qwide_caption_format,
	    regenerate_optimized_constant(LIST_2(string_constant_140,
	    string_constant_129)),Qformat_description);
    Qdialog_box_format = STATIC_SYMBOL("DIALOG-BOX-FORMAT",AB_package);
    check_if_superior_classes_are_defined(Qdialog_box_format,list_constant_30);
    string_constant_141 = 
	    STATIC_STRING("1t4z8r83bey83bey832Wy832Wy0k001l1l8l000004z8r83bgy83bgy832Wy832Wy0k001l1l8l000004z8r83bfy83bfy832Wy832Wy0k001l1l8l000004z8r83bdy");
    string_constant_142 = 
	    STATIC_STRING("83bdy832Wy832Wy0k001l1l8l000004z8r83ky83ky832Wy832Wy0k001n1l8l1m8p83*4y1l8o000004z8r83-=y83-=y832Wy832Wy0k001n1l8l1m8p83*4y1l8o0");
    string_constant_143 = 
	    STATIC_STRING("00004z8r83-Ny83-Ny832Wy832Wy00001n1l8l1m8p83*xy1l8o000004z8r83*ky83*ky832Wy832Wy00001n1l8l1m8p83*xy1l8o000004z8r83*Ky83*Ky832Wy8");
    string_constant_144 = STATIC_STRING("32Wy00001n1l8l1m8p83*xy1l8o00000");
    string_constant_145 = 
	    STATIC_STRING("1v8q1m832Wy1l83-My1m83beyk1m83bgyk1m83bfyk1m83bdyk1m83kyk1m83-=yk1m83-Ny01m83*ky01m83*Ky0");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_141,
	    string_constant_142,string_constant_143,string_constant_144));
    add_class_to_environment(9,Qdialog_box_format,list_constant_30,Nil,
	    temp,Nil,temp_2,list_constant_30,
	    regenerate_optimized_constant(string_constant_145),Nil);
    Qdefault_dialog_box_format = STATIC_SYMBOL("DEFAULT-DIALOG-BOX-FORMAT",
	    AB_package);
    string_constant_146 = STATIC_STRING("1l832Wy");
    mutate_global_property(Qdefault_dialog_box_format,
	    regenerate_optimized_constant(string_constant_146),
	    Qformat_description);
    Qdialog_message_format = STATIC_SYMBOL("DIALOG-MESSAGE-FORMAT",AB_package);
    string_constant_147 = STATIC_STRING("1t832Wy83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qdialog_message_format,
	    regenerate_optimized_constant(string_constant_147),
	    Qformat_description);
    Qdefault_button_format = STATIC_SYMBOL("DEFAULT-BUTTON-FORMAT",AB_package);
    string_constant_148 = 
	    STATIC_STRING("1z832Wy83wy83-cy83*=yl83*1yl83*0ys83**ys83iy3ky83*ay3ky");
    mutate_global_property(Qdefault_button_format,
	    regenerate_optimized_constant(string_constant_148),
	    Qformat_description);
    Qnon_default_button_format = STATIC_SYMBOL("NON-DEFAULT-BUTTON-FORMAT",
	    AB_package);
    string_constant_149 = 
	    STATIC_STRING("1z832Wy83wy83-cy83*=yl83*1yl83*0yl83**yl83iy3ky83*ay3ky");
    mutate_global_property(Qnon_default_button_format,
	    regenerate_optimized_constant(string_constant_149),
	    Qformat_description);
    Qdialog_message = STATIC_SYMBOL("DIALOG-MESSAGE",AB_package);
    check_if_superior_classes_are_defined(Qdialog_message,list_constant_33);
    string_constant_150 = 
	    STATIC_STRING("1m4z8r83ry83ry83Jly83Jly00001o1l8l1n8p083Gy1l8o1l83-3y000004z8r83xy83xy83Jly83Jly083Jmy001n1l8l1l83Ey1m83Dy53CyExport, writable0");
    string_constant_151 = STATIC_STRING("0000");
    string_constant_152 = 
	    STATIC_STRING("1o8q1m83Jly1l83-ly1n83ry01n8p083Gy1m83xy83Jmy");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_150,
	    string_constant_151));
    add_class_to_environment(9,Qdialog_message,list_constant_33,Nil,temp,
	    Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(string_constant_152),Nil);
    Qdialog_button = STATIC_SYMBOL("DIALOG-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qdialog_button,list_constant_33);
    string_constant_153 = 
	    STATIC_STRING("1l4z8r83ry83ry83Jjy83Jjy00001o1l8l1n8p083Gy1l8o1l83-3y00000");
    string_constant_154 = STATIC_STRING("1n8q1m83Jjy1l83-ly1n83ry01n8p083Gy");
    temp = regenerate_optimized_constant(string_constant_52);
    temp_2 = regenerate_optimized_constant(string_constant_153);
    add_class_to_environment(9,Qdialog_button,list_constant_33,Nil,temp,
	    Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(string_constant_154),Nil);
    Dialog_button_class_description = 
	    lookup_global_or_kb_specific_property_value(Qdialog_button,
	    Class_description_gkbprop);
    Qgenerate_spot_for_dialog_message = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-DIALOG-MESSAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_dialog_message,
	    STATIC_FUNCTION(generate_spot_for_dialog_message,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_dialog_message);
    set_get(Qdialog_message,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qdialog_message,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qgenerate_spot_for_dialog_button = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-DIALOG-BUTTON",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_dialog_button,
	    STATIC_FUNCTION(generate_spot_for_dialog_button,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_dialog_button);
    set_get(Qdialog_button,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qdialog_button,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qab_font = STATIC_SYMBOL("AB-FONT",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_1 = STATIC_ARRAY(list_constant_41,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qimplied_paragraph = STATIC_SYMBOL("IMPLIED-PARAGRAPH",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L));
    Qcontext_carryover = STATIC_SYMBOL("CONTEXT-CARRYOVER",AB_package);
    Qhyphen_added = STATIC_SYMBOL("HYPHEN-ADDED",AB_package);
    Qnon_word_wrapped_dummy_text_box_format = 
	    STATIC_SYMBOL("NON-WORD-WRAPPED-DUMMY-TEXT-BOX-FORMAT",AB_package);
    string_constant_155 = STATIC_STRING("1p83-My83*ay3=m5+y83iy3=m5+y");
    mutate_global_property(Qnon_word_wrapped_dummy_text_box_format,
	    regenerate_optimized_constant(string_constant_155),
	    Qformat_description);
    list_constant_12 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)39L),
	    FIX((SI_Long)46L),FIX((SI_Long)45L));
    list_constant_13 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)39L),
	    FIX((SI_Long)46L));
    list_constant_14 = STATIC_LIST((SI_Long)7L,FIX((SI_Long)8232L),
	    FIX((SI_Long)10L),FIX((SI_Long)13L),FIX((SI_Long)8202L),
	    FIX((SI_Long)8201L),FIX((SI_Long)8194L),FIX((SI_Long)8193L));
    string_constant_5 = STATIC_STRING("RplcTxtWTxtStr");
    string_constant_6 = STATIC_STRING("ChgTxtBx");
    Qg2_reformat_text_string_to_fit_message = 
	    STATIC_SYMBOL("G2-REFORMAT-TEXT-STRING-TO-FIT-MESSAGE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_reformat_text_string_to_fit_message,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qminimum_format_width_for_text_cell = 
	    STATIC_SYMBOL("MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_reformat_text_string_to_fit_message,
	    STATIC_FUNCTION(g2_reformat_text_string_to_fit_message,NIL,
	    FALSE,3,3));
    array_constant_2 = STATIC_ARRAY(list_constant_41,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    temp_1 = CONS(Qname_box,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    temp_1 = CONS(Qname_box,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_1;
    Qx_offset = STATIC_SYMBOL("X-OFFSET",AB_package);
    Qy_offset = STATIC_SYMBOL("Y-OFFSET",AB_package);
    string_constant_7 = STATIC_STRING("unknown color ~a");
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_42 = STATIC_CONS(Qab_class,list_constant_37);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    list_constant_62 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_42,
	    list_constant_43);
    list_constant_44 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_45 = STATIC_CONS(Qbackground_color,list_constant_44);
    list_constant_46 = STATIC_CONS(Qtext_color,list_constant_44);
    list_constant_47 = STATIC_LIST((SI_Long)2L,list_constant_45,
	    list_constant_46);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qand,Qbackground_color,
	    Qtext_color);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_47,list_constant_48);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qcolor,list_constant_49);
    Qat_standard_position = STATIC_SYMBOL("AT-STANDARD-POSITION",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qmember,Qat_standard_position);
    list_constant_50 = STATIC_CONS(Qinteger,Qnil);
    list_constant_51 = STATIC_CONS(Qx_offset,list_constant_50);
    list_constant_52 = STATIC_CONS(Qy_offset,list_constant_50);
    list_constant_53 = STATIC_LIST((SI_Long)2L,list_constant_51,
	    list_constant_52);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qand,Qx_offset,Qy_offset);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_53,list_constant_54);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_55,
	    list_constant_56);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qposition,list_constant_57);
    list_constant_60 = STATIC_LIST((SI_Long)2L,list_constant_58,
	    list_constant_59);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_60);
    list_constant_63 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_19,
	    list_constant_61);
    Qinitial_name_box = STATIC_SYMBOL("INITIAL-NAME-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_name_box,STATIC_FUNCTION(initial_name_box,
	    NIL,FALSE,1,1));
    Qget_name_box = STATIC_SYMBOL("GET-NAME-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qget_name_box,STATIC_FUNCTION(get_name_box,NIL,
	    FALSE,1,1));
    Qset_name_box = STATIC_SYMBOL("SET-NAME-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qset_name_box,STATIC_FUNCTION(set_name_box,NIL,
	    FALSE,2,2));
    add_virtual_attribute(Qname_box,list_constant_62,list_constant_63,Qnil,
	    SYMBOL_FUNCTION(Qinitial_name_box),
	    SYMBOL_FUNCTION(Qget_name_box),SYMBOL_FUNCTION(Qset_name_box));
    temp_1 = CONS(Qtext_alignment,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_1 = CONS(Qtext_alignment,temp);
    set_property_value_function(get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,temp_1);
    list_constant_64 = STATIC_CONS(Qab_class,list_constant_33);
    list_constant_65 = STATIC_LIST((SI_Long)4L,Qmember,Qleft,Qcenter,Qright);
    Kevent_updates = STATIC_SYMBOL("EVENT-UPDATES",Pkeyword);
    Kwithin_putter = STATIC_SYMBOL("WITHIN-PUTTER",Pkeyword);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Kevent_updates,Kwithin_putter);
    Qinitial_text_alignment = STATIC_SYMBOL("INITIAL-TEXT-ALIGNMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_text_alignment,
	    STATIC_FUNCTION(initial_text_alignment,NIL,FALSE,1,1));
    Qget_text_alignment = STATIC_SYMBOL("GET-TEXT-ALIGNMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_text_alignment,
	    STATIC_FUNCTION(get_text_alignment,NIL,FALSE,1,1));
    Qset_text_alignment = STATIC_SYMBOL("SET-TEXT-ALIGNMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qset_text_alignment,
	    STATIC_FUNCTION(set_text_alignment,NIL,FALSE,2,2));
    add_virtual_attribute(Qtext_alignment,list_constant_64,
	    list_constant_65,list_constant_66,
	    SYMBOL_FUNCTION(Qinitial_text_alignment),
	    SYMBOL_FUNCTION(Qget_text_alignment),
	    SYMBOL_FUNCTION(Qset_text_alignment));
    Qtitle_bar_format = STATIC_SYMBOL("TITLE-BAR-FORMAT",AB_package);
    Qleft_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
}
