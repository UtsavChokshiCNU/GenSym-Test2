/* edit2.c
 * Input file:  edit2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "edit2.h"


DEFINE_VARIABLE_WITH_SYMBOL(Time_of_frame_edit_base_time, Qtime_of_frame_edit_base_time);

DEFINE_VARIABLE_WITH_SYMBOL(Text_time_stamp_seconds, Qtext_time_stamp_seconds);

Object Time_of_last_allowable_frame_edit_time = UNBOUND;

/* GET-CURRENT-FRAME-EDIT-TIMESTAMP */
Object get_current_frame_edit_timestamp()
{
    double temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(126,0);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = g2ext_unix_time_as_float();
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Time_of_frame_edit_base_time);
	result = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp - temp_1),
		FIX((SI_Long)60L));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* TWRITE-FRAME-EDIT-TIMESTAMP */
Object twrite_frame_edit_timestamp(frame_edit_timestamp)
    Object frame_edit_timestamp;
{
    Object temp, minutes, hours, date, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(126,1);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = gensym_decode_unix_time(add(Time_of_frame_edit_base_time,
		ltimes(frame_edit_timestamp,FIX((SI_Long)60L))));
	MVS_6(result,temp,minutes,hours,date,month,year);
	result = print_decoded_time(Nil,minutes,hours,date,month,year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qyear;               /* year */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qmonth;              /* month */

static Object Qdate;               /* date */

static Object Qhours;              /* hours */

static Object Qminutes;            /* minutes */

static Object Qab_structure;       /* structure */

/* EVALUATION-STRUCTURE-FOR-FRAME-EDIT-TIMESTAMP */
Object evaluation_structure_for_frame_edit_timestamp(frame_edit_timestamp)
    Object frame_edit_timestamp;
{
    Object temp, minutes, hours, date, month, year, gensymed_symbol, temp_1;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(126,2);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = gensym_decode_unix_time(add(Time_of_frame_edit_base_time,
		ltimes(frame_edit_timestamp,FIX((SI_Long)60L))));
	MVS_6(result,temp,minutes,hours,date,month,year);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qyear;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qyear;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = year;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
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
	    item_or_value = year;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qmonth;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qmonth;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = month;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = month;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qdate;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qdate;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = date;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = date;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qhours;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)7L)) = Qhours;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = hours;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = hours;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)8L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qminutes;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)9L)) = Qminutes;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = minutes;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = minutes;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)10L)) = svref_new_value;
	}
	result = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qunknown;            /* unknown */

static Object Kall;                /* :all */

static Object Knil;                /* :nil */

/* GET-CURRENT-USER-NAME-IF-ANY-CASE-INSENSITIVE */
Object get_current_user_name_if_any_case_insensitive()
{
    Object name, made_up_qm, temp;
    Object result;

    x_note_fn_call(126,3);
    result = get_current_user_name();
    MVS_2(result,name,made_up_qm);
    if (made_up_qm)
	temp = Qunknown;
    else {
	temp = intern_text_string(1,
		copy_text_string_with_case_conversion(symbol_name_text_string(name),
		Kall));
	if (temp);
	else
	    temp = Knil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_update_frame_authors_qm, Qdo_not_update_frame_authors_qm);

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

/* UPDATE-AUTHORS-AND-TIME-OF-FRAME-EDIT */
Object update_authors_and_time_of_frame_edit(frame_being_edited,
	    slot_description)
    Object frame_being_edited, slot_description;
{
    Object authors_slot_enabled_p, update_authors_p, author_qm;
    Object last_edit_timestamp;

    x_note_fn_call(126,4);
    if ( !TRUEP(Do_not_update_frame_authors_qm)) {
	authors_slot_enabled_p = type_of_slot_if_editable(2,
		ISVREF(ISVREF(frame_being_edited,(SI_Long)1L),(SI_Long)1L),
		Qframe_author_or_authors);
	update_authors_p = ISVREF(Editor_parameters,(SI_Long)32L) && 
		authors_slot_enabled_p ? ( !EQ(ISVREF(slot_description,
		(SI_Long)2L),Qframe_author_or_authors) ? T : Nil) : Qnil;
	if (update_authors_p) {
	    author_qm = Servicing_workstation_qm ? 
		    ISVREF(Current_workstation,(SI_Long)20L) : Nil;
	    if (author_qm);
	    else
		author_qm = get_current_user_name_if_any_case_insensitive();
	    last_edit_timestamp = get_current_frame_edit_timestamp();
	    if (update_authors_p)
		return update_authors_attribute(frame_being_edited,
			slot_description,author_qm,last_edit_timestamp);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DECODE-FRAME-AUTHOR-OR-AUTHORS-1 */
Object decode_frame_author_or_authors_1(author_or_authors)
    Object author_or_authors;
{
    Object temp;

    x_note_fn_call(126,5);
    if (CONSP(author_or_authors)) {
	temp = CAR(author_or_authors);
	if (CONSP(temp))
	    return VALUES_3(CAAR(author_or_authors),
		    CDAR(author_or_authors),CDR(author_or_authors));
	else {
	    temp = CDR(author_or_authors);
	    if (LISTP(temp))
		return VALUES_3(CAR(author_or_authors),Nil,
			CDR(author_or_authors));
	    else
		return VALUES_3(CAR(author_or_authors),
			CDR(author_or_authors),Nil);
	}
    }
    else
	return VALUES_3(author_or_authors,Nil,Nil);
}

/* DECODE-FRAME-AUTHOR-OR-AUTHORS */
Object decode_frame_author_or_authors(author_or_authors,author_to_skip)
    Object author_or_authors, author_to_skip;
{
    Object author, timestamp, previous_author_or_authors;
    Object result;

    x_note_fn_call(126,6);
  next_loop:
    result = decode_frame_author_or_authors_1(author_or_authors);
    MVS_3(result,author,timestamp,previous_author_or_authors);
    if (timestamp &&  !TRUEP(author))
	author = Qunknown;
    if ( !TRUEP(author) &&  !TRUEP(timestamp) &&  
	    !TRUEP(previous_author_or_authors))
	return VALUES_3(Nil,Nil,Nil);
    else if ( !TRUEP(author) || author_to_skip && (CONSP(author_to_skip) ? 
	    TRUEP(memq_function(author,author_to_skip)) : EQ(author,
	    author_to_skip)))
	author_or_authors = previous_author_or_authors;
    else
	return VALUES_3(author,timestamp,previous_author_or_authors);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COPY-FRAME-AUTHOR-OR-AUTHORS */
Object copy_frame_author_or_authors(author_or_authors,author_to_skip)
    Object author_or_authors, author_to_skip;
{
    Object author, temp, previous_author_or_authors;
    Object result;

    x_note_fn_call(126,7);
    result = decode_frame_author_or_authors(author_or_authors,author_to_skip);
    MVS_3(result,author,temp,previous_author_or_authors);
    if ( !TRUEP(author))
	return VALUES_1(Nil);
    else
	return slot_value_cons_1(author,
		copy_frame_author_or_authors(previous_author_or_authors,
		author_to_skip));
}

/* UPDATE-AUTHORS-ATTRIBUTE */
Object update_authors_attribute(frame_being_edited,slot_description,
	    author_qm,last_edit_timestamp)
    Object frame_being_edited, slot_description, author_qm;
    Object last_edit_timestamp;
{
    Object new_entry, old_author_or_authors, new_value;

    x_note_fn_call(126,8);
    new_entry = slot_value_cons_1(author_qm,last_edit_timestamp);
    old_author_or_authors = 
	    get_lookup_slot_value_given_default(frame_being_edited,
	    Qframe_author_or_authors,Nil);
    new_value =  
	    !TRUEP(decode_frame_author_or_authors(old_author_or_authors,
	    author_qm)) ? new_entry : slot_value_cons_1(new_entry,
	    copy_frame_author_or_authors(old_author_or_authors,author_qm));
    return change_slot_value(3,frame_being_edited,Qframe_author_or_authors,
	    new_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Fixup_authors_to_skip, Qfixup_authors_to_skip);

/* FIXUP-AUTHOR-OR-AUTHORS-VALUE */
Object fixup_author_or_authors_value(author_or_authors)
    Object author_or_authors;
{
    Object temp, tail, a_plus_t, others, a, author, timestamp;
    Object previous_author_or_authors, fixup_authors_to_skip, temp_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,9);
    if (CONSP(author_or_authors)) {
	temp = CDR(author_or_authors);
	temp_1 = CONSP(temp);
	if (temp_1);
	else
	    temp_1 =  !TRUEP(CAR(author_or_authors));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_1 = TRUEP(memq_function(Nil,author_or_authors));
	if (temp_1);
	else {
	    tail = author_or_authors;
	    a_plus_t = Nil;
	    others = Nil;
	    a = Nil;
	  next_loop:
	    if ( !TRUEP(tail))
		goto end_loop;
	    a_plus_t = CAR(tail);
	    others = CDR(tail);
	    a = CONSP(a_plus_t) ? CAR(a_plus_t) : a_plus_t;
	    if (others && memq_function(a,others)) {
		temp_1 = TRUEP(T);
		goto end_1;
	    }
	    tail = M_CDR(tail);
	    goto next_loop;
	  end_loop:
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	result = decode_frame_author_or_authors(author_or_authors,Nil);
	MVS_3(result,author,timestamp,previous_author_or_authors);
	if ( !TRUEP(author) &&  !TRUEP(timestamp) &&  
		!TRUEP(previous_author_or_authors))
	    temp = Nil;
	else {
	    if (timestamp) {
		temp = author;
		if (temp);
		else
		    temp = Qunknown;
		temp = slot_value_cons_1(temp,timestamp);
	    }
	    else {
		temp = author;
		if (temp);
		else
		    temp = Qunknown;
	    }
	    fixup_authors_to_skip = gensym_cons_1(author,Nil);
	    PUSH_SPECIAL_WITH_SYMBOL(Fixup_authors_to_skip,Qfixup_authors_to_skip,fixup_authors_to_skip,
		    0);
	      temp_2 = 
		      fixup_frame_author_or_authors_tail(previous_author_or_authors);
	      reclaim_gensym_list_1(Fixup_authors_to_skip);
	    POP_SPECIAL();
	    temp = slot_value_cons_1(temp,temp_2);
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FIXUP-FRAME-AUTHOR-OR-AUTHORS-TAIL */
Object fixup_frame_author_or_authors_tail(author_or_authors)
    Object author_or_authors;
{
    Object author, temp, previous_author_or_authors;
    Object result;

    x_note_fn_call(126,10);
    result = decode_frame_author_or_authors(author_or_authors,
	    Fixup_authors_to_skip);
    MVS_3(result,author,temp,previous_author_or_authors);
    if ( !TRUEP(author))
	return VALUES_1(Nil);
    else {
	if (previous_author_or_authors) {
	    Fixup_authors_to_skip = gensym_cons_1(author,
		    Fixup_authors_to_skip);
	    temp = 
		    fixup_frame_author_or_authors_tail(previous_author_or_authors);
	}
	else
	    temp = Nil;
	return slot_value_cons_1(author,temp);
    }
}

/* UNDO-OR-REDO-EDIT-POSSIBLE-P */
Object undo_or_redo_edit_possible_p(redo_case_qm)
    Object redo_case_qm;
{
    Object edit_state;

    x_note_fn_call(126,11);
    edit_state = Current_edit_state ? Current_edit_state : 
	    Specific_structure_for_current_workstation_context;
    if (redo_case_qm)
	return VALUES_1(ISVREF(edit_state,(SI_Long)35L));
    else
	return VALUES_1(ISVREF(edit_state,(SI_Long)34L));
}

static Object Qautomatic;          /* automatic */

static Object Qkfep_conversion;    /* kfep-conversion */

/* UNDO-OR-REDO-EDIT */
Object undo_or_redo_edit(redo_case_qm)
    Object redo_case_qm;
{
    Object l, next_l, edit_box_change, svref_arg_1, svref_new_value;
    Object special_type_of_edit_box_change_qm;

    x_note_fn_call(126,12);
    if ( !TRUEP(redo_case_qm) && FIXNUM_GT(ISVREF(Current_edit_state,
	    (SI_Long)44L),ISVREF(Editor_parameters,(SI_Long)26L)))
	prune_edit_undo_stack();
    l = redo_case_qm ? ISVREF(Current_edit_state,(SI_Long)35L) : 
	    ISVREF(Current_edit_state,(SI_Long)34L);
    next_l = Nil;
    edit_box_change = Nil;
  next_loop:
    next_l = CDR(l);
    edit_box_change = CAR(l);
    if ( !TRUEP(l))
	goto end_loop;
    reclaim_gensym_cons_1(l);
    if (redo_case_qm) {
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)35L)) = next_l;
    }
    else {
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)34L)) = next_l;
	svref_arg_1 = Current_edit_state;
	svref_new_value = FIXNUM_SUB1(ISVREF(svref_arg_1,(SI_Long)44L));
	SVREF(svref_arg_1,FIX((SI_Long)44L)) = svref_new_value;
    }
    special_type_of_edit_box_change_qm = ISVREF(redo_case_qm && next_l ? 
	    CAR(next_l) : edit_box_change,(SI_Long)1L);
    if ( !(EQ(special_type_of_edit_box_change_qm,Qautomatic) || (Nil ? 
	    EQ(special_type_of_edit_box_change_qm,Qkfep_conversion) : 
	    TRUEP(Nil))))
	next_l = Nil;
    change_edit_box(12,Nil,ISVREF(edit_box_change,(SI_Long)3L),
	    ISVREF(edit_box_change,(SI_Long)4L),Nil,Nil,Nil,Nil,Nil,next_l,
	    ISVREF(edit_box_change,(SI_Long)1L),edit_box_change,redo_case_qm);
    SVREF(edit_box_change,FIX((SI_Long)7L)) = Nil;
    reclaim_edit_box_change_1(edit_box_change);
    l = next_l;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PRUNE-EDIT-UNDO-STACK */
Object prune_edit_undo_stack()
{
    Object gensymed_symbol, gensymed_symbol_1, temp, new_last_cons;
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(126,13);
    if (IFIX(ISVREF(Editor_parameters,(SI_Long)26L)) <= (SI_Long)0L) {
      next_loop:
	gensymed_symbol = ISVREF(Current_edit_state,(SI_Long)34L);
	gensymed_symbol_1 = Nil;
	if (CAS_SVREF(Current_edit_state,(SI_Long)34L,gensymed_symbol,
		gensymed_symbol_1)) {
	    temp = gensymed_symbol;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:
	reclaim_edit_undo_or_redo_stack(temp);
    }
    else {
	new_last_cons = nthcdr(FIXNUM_SUB1(ISVREF(Editor_parameters,
		(SI_Long)26L)),ISVREF(Current_edit_state,(SI_Long)34L));
	reclaim_edit_undo_or_redo_stack(CDR(new_last_cons));
	M_CDR(new_last_cons) = Nil;
    }
    svref_arg_1 = Current_edit_state;
    svref_new_value = ISVREF(Editor_parameters,(SI_Long)26L);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)44L)) = svref_new_value);
}

/* PENDING-ROMAJI-CHARACTER-IN-TEXT-P */
Object pending_romaji_character_in_text_p()
{
    x_note_fn_call(126,14);
    return VALUES_1(Nil);
}

Object Kfep_conversion_text_region_expansion_limit = UNBOUND;

Object Default_kanji_conversion_text_region_highlight_color = UNBOUND;

static Object Qpathname_component_conversion;  /* pathname-component-conversion */

static Object Qminimum_width_of_text_box;  /* minimum-width-of-text-box */

static Object Qword_spacing;       /* word-spacing */

static Object Qy_offset_for_text;  /* y-offset-for-text */

static Object Qline_index_of_first_fully_visible_line;  /* line-index-of-first-fully-visible-line */

static Object Qnumber_of_fully_visible_lines;  /* number-of-fully-visible-lines */

static Object Qminimum_height_of_text_box;  /* minimum-height-of-text-box */

static Object Qframe_transforms_of_block;  /* frame-transforms-of-block */

static Object Qno_autocompletion;  /* no-autocompletion */

static Object Qundo;               /* undo */

static Object Qredo;               /* redo */

/* CHANGE-EDIT-BOX */
Object change_edit_box varargs_1(int, n)
{
    Object text_tail_qm, line_index_of_change_qm, character_index_of_change_qm;
    Object line_index_past_deletion_qm, character_index_past_deletion_qm;
    Object text_line_to_insert_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object no_parsing_or_ellipsis_deletion_qm;
    Object special_type_of_edit_box_change_qm, edit_box_change_qm;
    Object redo_case_qm, change_text_qm, edit_box, edit_box_format;
    Object text_being_edited, gensymed_symbol, new_cursor_line_index_qm;
    Object new_cursor_character_index_qm, new_text_tail_for_cursor_qm;
    Object new_cursor_x_in_workspace, new_cursor_y_in_workspace;
    Object new_width_for_text, new_text_segment, old_text_segment;
    Object text_tail_past_old_text_segment_qm;
    Object line_index_of_old_and_new_text_segment;
    Object line_index_past_new_text_segment, line_index_past_old_text_segment;
    Object line_index_in_old_and_new_text, text_tail_in_old_text;
    Object text_tail_in_new_text, next_text_tail_in_old_text_qm;
    Object next_text_tail_in_new_text_qm, old_text_line;
    Object length_of_old_text_line, character_index_where_difference_starts_qm;
    Object distance_from_left_to_where_difference_starts_qm;
    Object new_text_has_same_height_as_old_qm, text_tail_past_text_segment_qm;
    Object scroll_edit_box_qm;
    Object line_index_for_beginning_of_kfep_conversion_text_region_qm;
    Object character_index_for_beginning_of_kfep_conversion_text_region_qm;
    Object line_index_for_end_of_kfep_conversion_text_region_qm;
    Object character_index_for_end_of_kfep_conversion_text_region_qm;
    Object try_to_expand_kfep_conversion_text_region_qm;
    Object restore_kana_conversion_mode_qm, first_time_qm;
    Object line_index_for_end_of_token, character_index_after_token;
    Object token_self_terminating_qm, ab_loop_desetq_, temp, temp_1;
    Object svref_new_value, text_region, temp_3, temp_4, temp_5, new_text_line;
    Object length_of_new_text_line, lost_space_at_end_of_old_text_line;
    Object lost_space_at_end_of_new_text_line, temp_6, gensymed_symbol_3;
    Object gensymed_symbol_4, temp_7, indentation, word_spacing, text_element;
    Object ab_loop_list_, kfep_conversion_text_region_qm;
    Object old_beginning_line_index, old_beginning_character_index;
    Object new_line_index_qm, new_character_index_qm, text_position;
    Object text_cell_plist, line_index_of_first_fully_visible_line_qm, l;
    Object edit_box_change, text_tail, line_width, temp_9, temp_10;
    Object new_right_edge_qm, top_edge_of_block, minimum_height_of_text_box;
    Object text_box_top_border_width, text, text_cell_plist_for_text_box;
    Object height_for_text, text_box_bottom_border_width, new_bottom_edge_qm;
    Object move_kfep_conversion_choices_qm, frame_transform, count_1;
    Object line_index_1, character_index, line_index_qm, character_index_qm;
    Object character_qm, escape_character_qm, line_index_at_end;
    Object character_index_at_end, decff_1_arg, j;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, old_width_for_text, arg;
    SI_Long arg_1, arg_2, gensymed_symbol_5, gensymed_symbol_6, temp_8;
    SI_Long line_index, gensymed_symbol_7, i, ab_loop_bind_;
    char just_moving_cursor_qm, temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,15);
    INIT_ARGS_nonrelocating();
    text_tail_qm = REQUIRED_ARG_nonrelocating();
    line_index_of_change_qm = REQUIRED_ARG_nonrelocating();
    character_index_of_change_qm = REQUIRED_ARG_nonrelocating();
    line_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_past_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_line_to_insert_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_in_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    y_in_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    no_parsing_or_ellipsis_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    special_type_of_edit_box_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    edit_box_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    redo_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    change_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(special_type_of_edit_box_change_qm,
		Qpathname_component_conversion)) {
	if (do_pathname_component_conversion_if_necessary(text_tail_qm,
		text_line_to_insert_qm))
	    return VALUES_1(Nil);
	else
	    special_type_of_edit_box_change_qm = Nil;
    }
    if ( !TRUEP(text_tail_qm) && line_index_of_change_qm)
	text_tail_qm = find_text_tail_for_line(ISVREF(Current_edit_state,
		(SI_Long)15L),line_index_of_change_qm);
    just_moving_cursor_qm =  !(line_index_past_deletion_qm || 
	    text_line_to_insert_qm || edit_box_change_qm);
    edit_box = ISVREF(Current_edit_state,(SI_Long)13L);
    edit_box_format = ISVREF(edit_box,(SI_Long)17L);
    text_being_edited = ISVREF(Current_edit_state,(SI_Long)15L);
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = 
	    IFIX(FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ADD(ISVREF(edit_box_format,
	    (SI_Long)44L),ISVREF(edit_box_format,(SI_Long)27L)),
	    ISVREF(edit_box_format,(SI_Long)29L)),ISVREF(edit_box_format,
	    (SI_Long)46L)));
    old_width_for_text = gensymed_symbol_1 - gensymed_symbol_2;
    new_cursor_line_index_qm = Nil;
    new_cursor_character_index_qm = Nil;
    new_text_tail_for_cursor_qm = Nil;
    new_cursor_x_in_workspace = Nil;
    new_cursor_y_in_workspace = Nil;
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
    distance_from_left_to_where_difference_starts_qm = Nil;
    new_text_has_same_height_as_old_qm = T;
    text_tail_past_text_segment_qm = Nil;
    scroll_edit_box_qm = Nil;
    line_index_for_beginning_of_kfep_conversion_text_region_qm = Nil;
    character_index_for_beginning_of_kfep_conversion_text_region_qm = Nil;
    line_index_for_end_of_kfep_conversion_text_region_qm = Nil;
    character_index_for_end_of_kfep_conversion_text_region_qm = Nil;
    try_to_expand_kfep_conversion_text_region_qm = Nil;
    restore_kana_conversion_mode_qm = Nil;
    if (just_moving_cursor_qm) {
	result = find_position_in_text(10,ISVREF(Current_edit_state,
		(SI_Long)13L),Nil,Nil,Nil,T,x_in_workspace_qm,
		y_in_workspace_qm,line_index_of_change_qm,
		character_index_of_change_qm,text_tail_qm);
	MVS_5(result,new_cursor_line_index_qm,
		new_cursor_character_index_qm,new_text_tail_for_cursor_qm,
		new_cursor_x_in_workspace,new_cursor_y_in_workspace);
	line_index_of_change_qm = new_cursor_line_index_qm;
	character_index_of_change_qm = new_cursor_character_index_qm;
    }
    first_time_qm = T;
    line_index_for_end_of_token = Nil;
    character_index_after_token = Nil;
    token_self_terminating_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    temp = ISVREF(Current_edit_state,(SI_Long)29L);
    ab_loop_desetq_ = CAR(temp);
    line_index_for_end_of_token = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    character_index_after_token = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    token_self_terminating_qm = CDR(temp);
    if ( !(FIXNUM_LT(line_index_of_change_qm,line_index_for_end_of_token) 
	    || FIXNUM_EQ(line_index_of_change_qm,
	    line_index_for_end_of_token) && (token_self_terminating_qm ? 
	    FIXNUM_LT(character_index_of_change_qm,
	    character_index_after_token) : 
	    FIXNUM_LE(character_index_of_change_qm,
	    character_index_after_token))))
	goto end_loop;
    if (first_time_qm) {
	erase_any_temporary_information_on_edit_workspace(1,Nil);
	temp_1 = Current_edit_state;
	SVREF(temp_1,FIX((SI_Long)27L)) = Nil;
    }
    pop_for_token();
    first_time_qm = Nil;
    goto next_loop;
  end_loop:
    if ( !TRUEP(first_time_qm)) {
	temp_1 = Current_edit_state;
	svref_new_value = Nil ? ISVREF(Current_edit_state,(SI_Long)26L) : 
		find_text_tail_for_line(text_being_edited,
		line_index_for_end_of_token);
	SVREF(temp_1,FIX((SI_Long)28L)) = svref_new_value;
    }
    if (ISVREF(Current_edit_state,(SI_Long)46L)) {
	text_region = ISVREF(Current_edit_state,(SI_Long)46L);
	if (FIXNUM_LT(line_index_of_change_qm,ISVREF(text_region,
		(SI_Long)16L)) || FIXNUM_EQ(line_index_of_change_qm,
		ISVREF(text_region,(SI_Long)16L)) && 
		FIXNUM_LT(character_index_of_change_qm,ISVREF(text_region,
		(SI_Long)17L))) {
	    if ( !EQ(special_type_of_edit_box_change_qm,Qautomatic)) {
		delete_kfep_conversion_text_region_if_any(0);
		restore_kana_conversion_mode_qm = T;
	    }
	}
	else if (FIXNUM_LT(line_index_of_change_qm,ISVREF(text_region,
		(SI_Long)18L)) || FIXNUM_EQ(line_index_of_change_qm,
		ISVREF(text_region,(SI_Long)18L)) && 
		FIXNUM_LT(character_index_of_change_qm,ISVREF(text_region,
		(SI_Long)19L))) {
	    if ( !(EQ(special_type_of_edit_box_change_qm,Qkfep_conversion) 
		    || EQ(special_type_of_edit_box_change_qm,Qautomatic)))
		update_kfep_conversion_choices_as_appropriate(3,Nil,
			line_index_of_change_qm,character_index_of_change_qm);
	}
	else {
	    if (just_moving_cursor_qm) {
		arg = IFIX(new_cursor_line_index_qm);
		arg_1 = IFIX(ISVREF(Current_edit_state,(SI_Long)24L));
		arg_2 = IFIX(ISVREF(text_region,(SI_Long)18L));
		temp_2 = arg == arg_1 ? arg_1 == arg_2 : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if ((temp_2 ? FIXNUM_GT(new_cursor_character_index_qm,
		    ISVREF(Current_edit_state,(SI_Long)25L)) : TRUEP(Nil)) 
		    ? FIXNUM_LE(new_cursor_character_index_qm,
		    FIXNUM_ADD(ISVREF(text_region,(SI_Long)19L),
		    Kfep_conversion_text_region_expansion_limit)) : TRUEP(Nil))
		try_to_expand_kfep_conversion_text_region_qm = T;
	}
    }
    if ( !just_moving_cursor_qm) {
	delete_any_text_regions(6,edit_box,Nil,Nil,Nil,Nil,
		ISVREF(Current_edit_state,(SI_Long)46L));
	if (edit_box_change_qm) {
	    line_index_of_old_and_new_text_segment = 
		    ISVREF(edit_box_change_qm,(SI_Long)2L);
	    line_index_past_new_text_segment = ISVREF(edit_box_change_qm,
		    (SI_Long)5L);
	    line_index_past_old_text_segment = ISVREF(edit_box_change_qm,
		    (SI_Long)6L);
	    new_text_segment = ISVREF(edit_box_change_qm,(SI_Long)7L);
	    new_width_for_text = ISVREF(edit_box_change_qm,(SI_Long)8L);
	    old_text_segment = find_text_tail_for_line(text_being_edited,
		    line_index_of_old_and_new_text_segment);
	    text_tail_past_old_text_segment_qm = 
		    find_text_tail_for_line(text_being_edited,
		    line_index_past_old_text_segment);
	}
	else {
	    temp_3 = text_tail_qm;
	    temp_4 = line_index_of_change_qm;
	    temp_5 = character_index_of_change_qm;
	    temp = get_lookup_slot_value(ISVREF(Current_edit_state,
		    (SI_Long)13L),Qminimum_width_of_text_box);
	    result = reformat_text(12,text_being_edited,edit_box_format,
		    Nil,T,temp_3,temp_4,temp_5,line_index_past_deletion_qm,
		    character_index_past_deletion_qm,
		    text_line_to_insert_qm,temp,ISVREF(edit_box,(SI_Long)18L));
	    MVS_7(result,new_text_segment,new_width_for_text,
		    old_text_segment,text_tail_past_old_text_segment_qm,
		    line_index_of_old_and_new_text_segment,
		    line_index_past_new_text_segment,
		    line_index_past_old_text_segment);
	}
	text_tail_in_old_text = old_text_segment;
	text_tail_in_new_text = new_text_segment;
	line_index_in_old_and_new_text = 
		line_index_of_old_and_new_text_segment;
	new_text_line = Nil;
	length_of_new_text_line = Nil;
	lost_space_at_end_of_old_text_line = Nil;
	lost_space_at_end_of_new_text_line = Nil;
      next_loop_1:
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
	if (FIXNUM_EQ(line_index_in_old_and_new_text,
		    line_index_of_change_qm)) {
	    if ( !TRUEP(next_text_tail_in_new_text_qm) &&  
		    !TRUEP(next_text_tail_in_old_text_qm)) {
		temp = FIXNUM_MIN(character_index_of_change_qm,
			length_of_old_text_line);
		character_index_where_difference_starts_qm = 
			FIXNUM_MIN(temp,length_of_new_text_line);
	    }
	    else if (FIXNUM_LT(character_index_of_change_qm,
		    length_of_old_text_line))
		character_index_where_difference_starts_qm = 
			FIXNUM_MIN(character_index_of_change_qm,
			length_of_new_text_line);
	    else if (FIXNUM_LT(character_index_of_change_qm,
		    length_of_new_text_line))
		character_index_where_difference_starts_qm = 
			length_of_old_text_line;
	    else
		character_index_where_difference_starts_qm = Nil;
	    goto end_1;
	}
	else if ( !FIXNUM_EQ(length_of_new_text_line,
		    length_of_old_text_line)) {
	    character_index_where_difference_starts_qm = 
		    FIXNUM_MIN(length_of_new_text_line,
		    length_of_old_text_line);
	    goto end_1;
	}
	else if (IFIX(length_of_old_text_line) > (SI_Long)0L &&  
		!(UBYTE_16_ISAREF_1(old_text_line,
		IFIX(FIXNUM_SUB1(length_of_old_text_line))) == 
		UBYTE_16_ISAREF_1(new_text_line,
		IFIX(FIXNUM_SUB1(length_of_new_text_line))))) {
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
	text_tail_in_old_text = next_text_tail_in_old_text_qm;
	text_tail_in_new_text = next_text_tail_in_new_text_qm;
	line_index_in_old_and_new_text = 
		FIXNUM_ADD1(line_index_in_old_and_new_text);
	goto next_loop_1;
      end_loop_1:
	character_index_where_difference_starts_qm = Qnil;
      end_1:;
	if (character_index_where_difference_starts_qm) {
	    indentation = FIX((SI_Long)0L);
	    word_spacing = ISVREF(edit_box_format,(SI_Long)34L);
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
	    gensymed_symbol_1 = IFIX(ISVREF(edit_box_format,(SI_Long)44L));
	    gensymed_symbol_2 = IFIX(ISVREF(edit_box_format,(SI_Long)27L));
	    gensymed_symbol_5 = 
		    IFIX(character_index_where_difference_starts_qm) == 
		    (SI_Long)0L ? (SI_Long)0L : IFIX(indentation);
	    gensymed_symbol_6 = 
		    IFIX(compute_minimum_left_edge_of_character_in_line_of_text(old_text_line,
		    character_index_where_difference_starts_qm,
		    ISVREF(edit_box_format,(SI_Long)22L),word_spacing));
	    distance_from_left_to_where_difference_starts_qm = 
		    FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
		    gensymed_symbol_5 + gensymed_symbol_6);
	    goto end_2;
	    distance_from_left_to_where_difference_starts_qm = Qnil;
	  end_2:;
	}
	new_text_has_same_height_as_old_qm = 
		FIXNUM_EQ(line_index_past_new_text_segment,
		line_index_past_old_text_segment) ? T : Nil;
	text_tail_past_text_segment_qm = 
		new_text_has_same_height_as_old_qm ? 
		text_tail_past_old_text_segment_qm : Nil;
	if (text_tail_past_old_text_segment_qm) {
	    nconc2(text_tail_in_new_text,text_tail_past_old_text_segment_qm);
	    if ( !TRUEP(next_text_tail_in_new_text_qm))
		next_text_tail_in_new_text_qm = 
			text_tail_past_old_text_segment_qm;
	}
	if (edit_box_change_qm) {
	    new_cursor_line_index_qm = ISVREF(edit_box_change_qm,(SI_Long)9L);
	    new_cursor_character_index_qm = ISVREF(edit_box_change_qm,
		    (SI_Long)10L);
	    if (ISVREF(edit_box_change_qm,(SI_Long)11L)) {
		kfep_conversion_text_region_qm = ISVREF(Current_edit_state,
			(SI_Long)46L);
		temp = ISVREF(edit_box_change_qm,(SI_Long)11L);
		old_beginning_line_index = CAR(temp);
		temp = ISVREF(edit_box_change_qm,(SI_Long)11L);
		old_beginning_character_index = CDR(temp);
		if ( !(EQ(special_type_of_edit_box_change_qm,
			Qkfep_conversion) || 
			kfep_conversion_text_region_qm && 
			FIXNUM_EQ(ISVREF(kfep_conversion_text_region_qm,
			(SI_Long)16L),old_beginning_line_index) && 
			FIXNUM_EQ(ISVREF(kfep_conversion_text_region_qm,
			(SI_Long)17L),old_beginning_character_index) && 
			(FIXNUM_LT(ISVREF(kfep_conversion_text_region_qm,
			(SI_Long)18L),line_index_in_old_and_new_text) || 
			FIXNUM_EQ(ISVREF(kfep_conversion_text_region_qm,
			(SI_Long)18L),line_index_in_old_and_new_text) && 
			FIXNUM_LT(ISVREF(kfep_conversion_text_region_qm,
			(SI_Long)19L),
			character_index_where_difference_starts_qm)))) {
		    line_index_for_beginning_of_kfep_conversion_text_region_qm 
			    = old_beginning_line_index;
		    character_index_for_beginning_of_kfep_conversion_text_region_qm 
			    = old_beginning_character_index;
		}
	    }
	    else if (ISVREF(Current_edit_state,(SI_Long)46L))
		exit_kfep_mode_if_necessary(0);
	}
	else {
	    result = determine_corrected_text_position_if_necessary(13,
		    ISVREF(Current_edit_state,(SI_Long)24L),
		    ISVREF(Current_edit_state,(SI_Long)25L),
		    new_text_segment,old_text_segment,
		    line_index_of_old_and_new_text_segment,
		    line_index_in_old_and_new_text,
		    character_index_where_difference_starts_qm,T,
		    line_index_of_change_qm,character_index_of_change_qm,
		    line_index_past_deletion_qm,
		    character_index_past_deletion_qm,text_line_to_insert_qm);
	    MVS_3(result,new_cursor_line_index_qm,
		    new_cursor_character_index_qm,new_text_tail_for_cursor_qm);
	    if (ISVREF(Current_edit_state,(SI_Long)46L)) {
		text_region = ISVREF(Current_edit_state,(SI_Long)46L);
		if ( !TRUEP(special_type_of_edit_box_change_qm) && 
			FIXNUM_EQ(line_index_in_old_and_new_text,
			ISVREF(text_region,(SI_Long)18L)) && ( 
			!TRUEP(character_index_where_difference_starts_qm) 
			|| 
			FIXNUM_LE(character_index_where_difference_starts_qm,
			FIXNUM_ADD(ISVREF(text_region,(SI_Long)19L),
			Kfep_conversion_text_region_expansion_limit))) && 
			new_cursor_line_index_qm &&  
			!(FIXNUM_EQ(new_cursor_line_index_qm,
			line_index_in_old_and_new_text) && 
			character_index_where_difference_starts_qm && 
			FIXNUM_EQ(new_cursor_character_index_qm,
			character_index_where_difference_starts_qm))) {
		    if ( !TRUEP(pending_romaji_character_in_text_p()))
			try_to_expand_kfep_conversion_text_region_qm = T;
		}
		result = determine_corrected_text_position_if_necessary(13,
			ISVREF(text_region,(SI_Long)18L),
			ISVREF(text_region,(SI_Long)19L),new_text_segment,
			old_text_segment,
			line_index_of_old_and_new_text_segment,
			line_index_in_old_and_new_text,
			character_index_where_difference_starts_qm,Nil,
			line_index_of_change_qm,
			character_index_of_change_qm,
			line_index_past_deletion_qm,
			character_index_past_deletion_qm,
			text_line_to_insert_qm);
		MVS_2(result,
			line_index_for_end_of_kfep_conversion_text_region_qm,
			character_index_for_end_of_kfep_conversion_text_region_qm);
		if (line_index_for_end_of_kfep_conversion_text_region_qm) {
		    result = determine_corrected_text_position_if_necessary(13,
			    ISVREF(text_region,(SI_Long)16L),
			    ISVREF(text_region,(SI_Long)17L),
			    new_text_segment,old_text_segment,
			    line_index_of_old_and_new_text_segment,
			    line_index_in_old_and_new_text,
			    character_index_where_difference_starts_qm,
			    EQ(special_type_of_edit_box_change_qm,
			    Qautomatic) ? T : Nil,line_index_of_change_qm,
			    character_index_of_change_qm,
			    line_index_past_deletion_qm,
			    character_index_past_deletion_qm,
			    text_line_to_insert_qm);
		    MVS_2(result,
			    line_index_for_beginning_of_kfep_conversion_text_region_qm,
			    character_index_for_beginning_of_kfep_conversion_text_region_qm);
		    update_text_region(3,ISVREF(Current_edit_state,
			    (SI_Long)46L),
			    line_index_for_beginning_of_kfep_conversion_text_region_qm 
			    ? ISVREF(text_region,(SI_Long)16L) : 
			    line_index_in_old_and_new_text,
			    line_index_for_beginning_of_kfep_conversion_text_region_qm 
			    ? ISVREF(text_region,(SI_Long)17L) : 
			    character_index_where_difference_starts_qm);
		}
	    }
	}
	if (FIXNUM_LT(line_index_of_old_and_new_text_segment,
		line_index_of_change_qm) || T) {
	    new_line_index_qm = Nil;
	    new_character_index_qm = Nil;
	    text_position = Nil;
	    ab_loop_list_ = ISVREF(Current_edit_state,(SI_Long)29L);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    text_position = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result = determine_corrected_text_position_if_necessary(7,
		    CAR(text_position),CADR(text_position),
		    new_text_segment,old_text_segment,
		    line_index_of_old_and_new_text_segment,
		    line_index_in_old_and_new_text,
		    character_index_where_difference_starts_qm);
	    MVS_2(result,new_line_index_qm,new_character_index_qm);
	    if ( !TRUEP(new_line_index_qm))
		goto end_loop_3;
	    M_CAR(text_position) = new_line_index_qm;
	    M_CADR(text_position) = new_character_index_qm;
	    goto next_loop_3;
	  end_loop_3:;
	}
    }
    if (new_cursor_line_index_qm)
	stop_blinker(ISVREF(Current_edit_state,(SI_Long)14L),Nil);
    if (new_cursor_line_index_qm) {
	text_cell_plist = ISVREF(edit_box,(SI_Long)18L);
	line_index_of_first_fully_visible_line_qm = getf(text_cell_plist,
		Qy_offset_for_text,_) ? getf(text_cell_plist,
		Qline_index_of_first_fully_visible_line,_) : Nil;
	if (line_index_of_first_fully_visible_line_qm ? 
		FIXNUM_LT(new_cursor_line_index_qm,
		line_index_of_first_fully_visible_line_qm) || 
		FIXNUM_GE(new_cursor_line_index_qm,
		FIXNUM_ADD(line_index_of_first_fully_visible_line_qm,
		getf(text_cell_plist,Qnumber_of_fully_visible_lines,_))) : 
		TRUEP(Nil)) {
	    scroll_edit_box_qm = T;
	    temp_8 = 
		    IFIX(FIXNUM_SUB1(line_index_of_first_fully_visible_line_qm));
	    line_index = MAX(temp_8,(SI_Long)1L);
	    update_text_in_edit_box(T,
		    find_text_tail_for_line(text_being_edited,
		    FIX(line_index)),Nil,Nil,FIX(line_index),Nil,edit_box);
	}
    }
    if (Special_variable_for_use_value_macro)
	Special_variable_for_use_value_macro = scroll_edit_box_qm;
    if ( !just_moving_cursor_qm)
	update_text_in_edit_box(T,text_tail_in_old_text,
		next_text_tail_in_old_text_qm,
		text_tail_past_text_segment_qm,
		line_index_in_old_and_new_text,
		distance_from_left_to_where_difference_starts_qm,edit_box);
    if ( !just_moving_cursor_qm) {
	if (text_tail_past_old_text_segment_qm) {
	    l = text_tail_in_old_text;
	  next_loop_4:
	    if ( !TRUEP(l))
		goto end_loop_4;
	    if (EQ(CDR(l),text_tail_past_old_text_segment_qm))
		goto end_loop_4;
	    l = M_CDR(l);
	    goto next_loop_4;
	  end_loop_4:
	    M_CDR(l) = Nil;
	}
	temp = CAR(text_tail_in_new_text);
	temp_1 = CAR(text_tail_in_old_text);
	M_CAR(text_tail_in_new_text) = temp_1;
	M_CAR(text_tail_in_old_text) = temp;
	temp = CDR(text_tail_in_new_text);
	temp_1 = CDR(text_tail_in_old_text);
	M_CDR(text_tail_in_new_text) = temp_1;
	M_CDR(text_tail_in_old_text) = temp;
	temp = text_tail_in_new_text;
	text_tail_in_new_text = text_tail_in_old_text;
	text_tail_in_old_text = temp;
	if (edit_box_change_qm)
	    new_text_tail_for_cursor_qm = 
		    find_text_tail_for_line(text_being_edited,
		    new_cursor_line_index_qm);
	else if (EQ(new_text_tail_for_cursor_qm,text_tail_in_old_text))
	    new_text_tail_for_cursor_qm = text_tail_in_new_text;
	if (new_cursor_line_index_qm) {
	    result = find_position_in_text(10,ISVREF(Current_edit_state,
		    (SI_Long)13L),Nil,Nil,Nil,Nil,Nil,Nil,
		    new_cursor_line_index_qm,new_cursor_character_index_qm,
		    new_text_tail_for_cursor_qm);
	    MVS_5(result,new_cursor_line_index_qm,
		    new_cursor_character_index_qm,
		    new_text_tail_for_cursor_qm,new_cursor_x_in_workspace,
		    new_cursor_y_in_workspace);
	}
	temp_3 = special_type_of_edit_box_change_qm;
	temp_4 = line_index_of_old_and_new_text_segment;
	temp_5 = line_index_in_old_and_new_text;
	temp = character_index_where_difference_starts_qm;
	if (temp);
	else
	    temp = length_of_old_text_line;
	edit_box_change = make_edit_box_change_1(temp_3,temp_4,temp_5,temp,
		line_index_past_old_text_segment,
		line_index_past_new_text_segment,new_text_segment,
		FIX(old_width_for_text),ISVREF(Current_edit_state,
		(SI_Long)24L),ISVREF(Current_edit_state,(SI_Long)25L),
		ISVREF(Current_edit_state,(SI_Long)46L) ? 
		gensym_cons_1(ISVREF(ISVREF(Current_edit_state,
		(SI_Long)46L),(SI_Long)16L),
		ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),
		(SI_Long)17L)) : Nil);
	if ( !TRUEP(edit_box_change_qm) || redo_case_qm) {
	    if ( !TRUEP(edit_box_change_qm)) {
		if (ISVREF(Current_edit_state,(SI_Long)35L)) {
		    reclaim_edit_undo_or_redo_stack(ISVREF(Current_edit_state,
			    (SI_Long)35L));
		    temp_1 = Current_edit_state;
		    SVREF(temp_1,FIX((SI_Long)35L)) = Nil;
		}
	    }
	    temp_1 = Current_edit_state;
	    svref_new_value = gensym_cons_1(edit_box_change,
		    ISVREF(Current_edit_state,(SI_Long)34L));
	    SVREF(temp_1,FIX((SI_Long)34L)) = svref_new_value;
	    temp_1 = Current_edit_state;
	    svref_new_value = FIXNUM_ADD1(ISVREF(temp_1,(SI_Long)44L));
	    SVREF(temp_1,FIX((SI_Long)44L)) = svref_new_value;
	    if (IFIX(ISVREF(Current_edit_state,(SI_Long)44L)) > 
		    IFIX(ISVREF(Editor_parameters,(SI_Long)26L)) + 
		    (SI_Long)10L)
		prune_edit_undo_stack();
	}
	else {
	    temp_1 = Current_edit_state;
	    svref_new_value = gensym_cons_1(edit_box_change,
		    ISVREF(Current_edit_state,(SI_Long)35L));
	    SVREF(temp_1,FIX((SI_Long)35L)) = svref_new_value;
	}
    }
    if (new_cursor_line_index_qm) {
	gensymed_symbol_1 = IFIX(new_width_for_text);
	gensymed_symbol_2 = IFIX(new_cursor_x_in_workspace);
	gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol);
	gensymed_symbol_6 = IFIX(ISVREF(edit_box_format,(SI_Long)44L));
	gensymed_symbol_7 = IFIX(ISVREF(edit_box_format,(SI_Long)27L));
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_5 - 
		gensymed_symbol_6 - gensymed_symbol_7;
	new_width_for_text = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
    }
    if ( !EQ(old_text_segment,text_being_edited) &&  
	    !TRUEP(edit_box_change_qm)) {
	text_tail = text_being_edited;
	line_width = Nil;
      next_loop_5:
	result = get_next_text_line(text_tail);
	MVS_6(result,gensymed_symbol,temp,temp,gensymed_symbol_3,temp,
		gensymed_symbol_4);
	line_width = gensymed_symbol_4;
	text_tail = gensymed_symbol_3;
	if (FIXNUM_GT(line_width,new_width_for_text))
	    new_width_for_text = line_width;
	if (EQ(text_tail,old_text_segment))
	    goto end_loop_5;
	goto next_loop_5;
      end_loop_5:;
    }
    if (text_tail_past_old_text_segment_qm &&  !TRUEP(edit_box_change_qm)) {
	text_tail_qm = text_tail_past_old_text_segment_qm;
	line_width = Nil;
      next_loop_6:
	result = get_next_text_line(text_tail_qm);
	MVS_6(result,gensymed_symbol,temp,temp,gensymed_symbol_3,temp,
		gensymed_symbol_4);
	line_width = gensymed_symbol_4;
	text_tail_qm = gensymed_symbol_3;
	if (FIXNUM_GT(line_width,new_width_for_text))
	    new_width_for_text = line_width;
	if ( !TRUEP(text_tail_qm))
	    goto end_loop_6;
	goto next_loop_6;
      end_loop_6:;
    }
    if ( !TRUEP(ISVREF(Current_edit_state,(SI_Long)68L))) {
	if ( !(IFIX(new_width_for_text) == old_width_for_text)) {
	    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(get_lookup_slot_value(edit_box,
		    Qminimum_width_of_text_box));
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_5 = IFIX(new_width_for_text) - old_width_for_text;
	    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_5;
	    new_right_edge_qm = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
	}
	else
	    new_right_edge_qm = Nil;
	gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	top_edge_of_block = gensymed_symbol;
	minimum_height_of_text_box = get_lookup_slot_value(edit_box,
		Qminimum_height_of_text_box);
	text_box_top_border_width = ISVREF(edit_box_format,(SI_Long)45L);
	temp = ISVREF(edit_box,(SI_Long)16L);
	text = CDR(temp);
	text_cell_plist_for_text_box = ISVREF(edit_box,(SI_Long)18L);
	height_for_text = compute_height_for_text(text,edit_box_format,
		text_cell_plist_for_text_box);
	text_box_bottom_border_width = ISVREF(edit_box_format,(SI_Long)47L);
	if ( !TRUEP(new_text_has_same_height_as_old_qm)) {
	    temp_5 = FIXNUM_ADD(top_edge_of_block,minimum_height_of_text_box);
	    temp = FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ADD(top_edge_of_block,
		    text_box_top_border_width),height_for_text),
		    text_box_bottom_border_width);
	    new_bottom_edge_qm = FIXNUM_MAX(temp_5,temp);
	}
	else
	    new_bottom_edge_qm = Nil;
	if (new_right_edge_qm) {
	    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_2 = FIXNUM_NE(new_right_edge_qm,gensymed_symbol);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2);
	else if (new_bottom_edge_qm) {
	    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp_2 = FIXNUM_NE(new_bottom_edge_qm,gensymed_symbol);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    move_kfep_conversion_choices_qm = new_bottom_edge_qm && 
		    ISVREF(Current_edit_state,(SI_Long)46L) ? 
		    ISVREF(Current_edit_state,(SI_Long)47L) : Qnil;
	    if (move_kfep_conversion_choices_qm)
		erase_any_kfep_conversion_choices();
	    if (new_bottom_edge_qm)
		erase_any_temporary_information_on_edit_workspace(1,Nil);
	    update_border_of_text_box(edit_box,Nil,Nil,new_right_edge_qm,
		    new_bottom_edge_qm);
	    if (move_kfep_conversion_choices_qm)
		put_up_kfep_conversion_choices(T);
	    if (new_bottom_edge_qm && (ISVREF(Current_edit_state,
		    (SI_Long)58L) || ISVREF(Current_edit_state,(SI_Long)16L)))
		shrink_wrap_workspace(Current_edit_workspace);
	}
    }
    if ( !just_moving_cursor_qm)
	update_text_in_edit_box(Nil,text_tail_in_new_text,
		next_text_tail_in_new_text_qm,
		text_tail_past_text_segment_qm,
		line_index_in_old_and_new_text,
		distance_from_left_to_where_difference_starts_qm,edit_box);
    if (new_cursor_line_index_qm) {
	move_edit_cursor(ISVREF(Current_edit_state,(SI_Long)14L),
		new_cursor_x_in_workspace,new_cursor_y_in_workspace);
	temp_1 = Current_edit_state;
	SVREF(temp_1,FIX((SI_Long)24L)) = new_cursor_line_index_qm;
	temp_1 = Current_edit_state;
	SVREF(temp_1,FIX((SI_Long)25L)) = new_cursor_character_index_qm;
	temp_1 = Current_edit_state;
	SVREF(temp_1,FIX((SI_Long)26L)) = new_text_tail_for_cursor_qm;
    }
    if (ISVREF(Current_edit_state,(SI_Long)68L)) {
	frame_transform = Nil;
	ab_loop_list_ = get_lookup_slot_value_given_default(edit_box,
		Qframe_transforms_of_block,Nil);
	ab_loop_desetq_ = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	frame_transform = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	scroll_text_into_view(frame_transform,ISVREF(Current_edit_state,
		(SI_Long)24L),ISVREF(Current_edit_state,(SI_Long)25L));
	goto next_loop_7;
      end_loop_7:;
    }
    if (restore_kana_conversion_mode_qm)
	enter_kana_conversion_mode(ISVREF(Current_edit_state,(SI_Long)50L));
    if (line_index_for_beginning_of_kfep_conversion_text_region_qm || 
	    line_index_for_end_of_kfep_conversion_text_region_qm) {
	if ( !TRUEP(line_index_for_end_of_kfep_conversion_text_region_qm))
	    set_up_kfep_conversion_text_region(3,
		    line_index_for_beginning_of_kfep_conversion_text_region_qm,
		    character_index_for_beginning_of_kfep_conversion_text_region_qm,
		    T);
	else {
	    if (line_index_for_beginning_of_kfep_conversion_text_region_qm) {
		delete_frame(ISVREF(Current_edit_state,(SI_Long)46L));
		temp_1 = Current_edit_state;
		svref_new_value = 
			make_kfep_conversion_text_region(line_index_for_beginning_of_kfep_conversion_text_region_qm,
			character_index_for_beginning_of_kfep_conversion_text_region_qm,
			Default_kanji_conversion_text_region_highlight_color);
		SVREF(temp_1,FIX((SI_Long)46L)) = svref_new_value;
	    }
	    update_text_region(3,ISVREF(Current_edit_state,(SI_Long)46L),
		    line_index_for_end_of_kfep_conversion_text_region_qm,
		    character_index_for_end_of_kfep_conversion_text_region_qm);
	}
    }
    if (try_to_expand_kfep_conversion_text_region_qm)
	update_kfep_conversion_choices_as_appropriate(1,T);
    else if (ISVREF(Current_edit_state,(SI_Long)46L))
	update_kfep_buttons();
    temp_1 = Current_edit_state;
    temp = ISVREF(Current_edit_state,(SI_Long)29L);
    temp = CAR(temp);
    svref_new_value = find_text_tail_for_line(text_being_edited,CAR(temp));
    SVREF(temp_1,FIX((SI_Long)28L)) = svref_new_value;
    if ( !TRUEP(text_line_to_insert_qm) &&  
	    !TRUEP(no_parsing_or_ellipsis_deletion_qm)) {
	count_1 = FIX((SI_Long)1L);
	line_index_1 = ISVREF(Current_edit_state,(SI_Long)24L);
	character_index = ISVREF(Current_edit_state,(SI_Long)25L);
	text_tail = ISVREF(Current_edit_state,(SI_Long)26L);
	line_index_qm = Nil;
	character_index_qm = Nil;
	text_tail_qm = Nil;
	character_qm = Nil;
	escape_character_qm = Nil;
	line_index_at_end = Nil;
	character_index_at_end = Nil;
	if (T) {
	    i = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(Ellipsis_text_string_length);
	  next_loop_8:
	    if (i > ab_loop_bind_)
		goto end_loop_8;
	    result = find_next_character_if_any(line_index_1,
		    character_index,text_tail);
	    MVS_3(result,line_index_qm,character_index_qm,text_tail_qm);
	    if ( !TRUEP(line_index_qm))
		goto end_loop_8;
	    line_index_1 = line_index_qm;
	    character_index = character_index_qm;
	    text_tail = text_tail_qm;
	    count_1 = FIXNUM_ADD1(count_1);
	    i = i + (SI_Long)1L;
	    goto next_loop_8;
	  end_loop_8:;
	}
	if (Nil) {
	    decff_1_arg = Ellipsis_text_string_length;
	    count_1 = FIXNUM_MINUS(count_1,decff_1_arg);
	}
	if (IFIX(Ellipsis_text_string_length) > (SI_Long)0L) {
	    i = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(count_1);
	  next_loop_9:
	    if (i > ab_loop_bind_)
		goto end_loop_9;
	    line_index_at_end = line_index_1;
	    line_index_qm = line_index_at_end;
	    character_index_at_end = character_index;
	    character_index_qm = character_index_at_end;
	    text_tail_qm = text_tail;
	    j = Ellipsis_text_string_length;
	  next_loop_10:
	    result = find_previous_character_if_any(line_index_qm,
		    character_index_qm,text_tail_qm,text_being_edited);
	    MVS_5(result,line_index_qm,character_index_qm,text_tail_qm,
		    character_qm,escape_character_qm);
	    if ( !TRUEP(line_index_qm))
		goto end_loop_10;
	    if (FIXNUM_EQ(j,Ellipsis_text_string_length)) {
		line_index_1 = line_index_qm;
		character_index = character_index_qm;
		text_tail = text_tail_qm;
	    }
	    j = FIXNUM_SUB1(j);
	    temp = FIX(UBYTE_16_ISAREF_1(Ellipsis_text_string,IFIX(j)));
	    if ( !EQ(character_qm,temp)) {
		temp_2 = TRUEP(T);
		goto end_3;
	    }
	    else if (IFIX(j) == (SI_Long)0L) {
		if ( !TRUEP(edit_box_change_qm))
		    change_edit_box(5,text_tail_qm,line_index_qm,
			    character_index_qm,line_index_at_end,
			    character_index_at_end);
		temp_2 = TRUEP(Nil);
		goto end_3;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    temp_2 = TRUEP(Qnil);
	  end_3:;
	    if ( !temp_2)
		goto end_loop_9;
	    i = i + (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	}
    }
    if ( !TRUEP(no_parsing_or_ellipsis_deletion_qm)) {
	if ( !TRUEP(Servicing_workstation_qm) ||  
		!EQ(Specific_structure_for_current_workstation_context,
		Current_edit_state)) {
	    temp_1 = Current_edit_state;
	    SVREF(temp_1,FIX((SI_Long)27L)) = T;
	}
	else
	    extend_parsing_as_appropriate(4, 
		    !TRUEP(text_line_to_insert_qm) ? Qno_autocompletion : 
		    T,Nil,Nil,change_text_qm);
    }
    if (ISVREF(Current_edit_state,(SI_Long)43L)) {
	update_edit_operation_subcommands(ISVREF(Current_edit_state,
		(SI_Long)43L));
	temp = ISVREF(Current_edit_state,(SI_Long)43L);
	enable_or_disable_subcommand(3,temp,Qundo, 
		!TRUEP(undo_or_redo_edit_possible_p(Nil)) ? T : Nil);
	temp = ISVREF(Current_edit_state,(SI_Long)43L);
	enable_or_disable_subcommand(3,temp,Qredo, 
		!TRUEP(undo_or_redo_edit_possible_p(T)) ? T : Nil);
    }
    if (ISVREF(Current_edit_state,(SI_Long)23L)) {
	temp = SYMBOL_FUNCTION(ISVREF(Current_edit_state,(SI_Long)23L));
	return FUNCALL_1(temp,text_being_edited);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-DISTANCE-OF-TEXT-LINE-FROM-TOP */
Object compute_distance_of_text_line_from_top(line_index,text_box_format)
    Object line_index, text_box_format;
{
    x_note_fn_call(126,16);
    return VALUES_1(FIXNUM_TIMES(FIXNUM_SUB1(line_index),
	    FIXNUM_ADD(ISVREF(text_box_format,(SI_Long)31L),
	    ISVREF(text_box_format,(SI_Long)33L))));
}

static Object Kno_bleeding;        /* :no-bleeding */

static Object Qdraw_text_segment_in_text_box;  /* draw-text-segment-in-text-box */

/* UPDATE-TEXT-IN-EDIT-BOX */
Object update_text_in_edit_box(erase_qm,text_segment,
	    text_tail_past_partial_line_update_qm,
	    text_tail_past_text_segment_qm,line_index,
	    distance_from_left_to_where_difference_starts_qm,edit_box)
    Object erase_qm, text_segment, text_tail_past_partial_line_update_qm;
    Object text_tail_past_text_segment_qm, line_index;
    Object distance_from_left_to_where_difference_starts_qm, edit_box;
{
    Object gensymed_symbol, region_invalidation_is_preferred, text_box_format;
    Object line_spacing, line_height, baseline_to_baseline_distance;
    Object sub_class_bit_vector, text_cell_top_margin;
    Object distance_of_text_segment_from_top, text_segment_qm;
    Object line_index_of_second_segment;
    Object distance_of_start_of_text_segment_from_top;
    Object vertical_delta_to_end_of_text_segment;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_text_area;
    SI_Long right_edge_of_text_area, extra_diacritic_height;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    SI_Long top_of_first_line_of_first_update_area, top_of_first_update_area;
    SI_Long bottom_of_first_update_area;
    SI_Long top_of_first_line_of_second_update_area, top_of_second_update_area;
    SI_Long bottom_of_second_update_area;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,17);
    gensymed_symbol = ACCESS_ONCE(ISVREF(edit_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    if (gensymed_symbol) {
	region_invalidation_is_preferred = T;
	PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		0);
	  text_box_format = ISVREF(edit_box,(SI_Long)17L);
	  gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
	  left_edge_of_text_area = gensymed_symbol_1 + gensymed_symbol_2;
	  if (get_lookup_slot_value_given_default(edit_box,
		  Qframe_transforms_of_block,Nil))
	      right_edge_of_text_area = 
		      IFIX(Most_positive_workspace_coordinate);
	  else {
	      gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
	      right_edge_of_text_area = gensymed_symbol_1 - gensymed_symbol_2;
	  }
	  line_spacing = ISVREF(text_box_format,(SI_Long)33L);
	  line_height = ISVREF(text_box_format,(SI_Long)31L);
	  baseline_to_baseline_distance = FIXNUM_ADD(line_height,line_spacing);
	  extra_diacritic_height = IFIX(ISVREF(text_box_format,
		  (SI_Long)31L)) >>  -  - (SI_Long)2L;
	  sub_class_bit_vector = ISVREF(ISVREF(edit_box,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Slider_readout_class_description,(SI_Long)18L));
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
	  text_cell_top_margin = temp ? FIX(IFIX(ISVREF(text_box_format,
		  (SI_Long)28L)) - (SI_Long)2L) : ISVREF(text_box_format,
		  (SI_Long)28L);
	  if (distance_from_left_to_where_difference_starts_qm) {
	      distance_of_text_segment_from_top = 
		      compute_distance_of_text_line_from_top(line_index,
		      text_box_format);
	      gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
	      gensymed_symbol_3 = IFIX(text_cell_top_margin);
	      gensymed_symbol_4 = IFIX(distance_of_text_segment_from_top);
	      top_of_first_line_of_first_update_area = gensymed_symbol_1 + 
		      gensymed_symbol_2 + gensymed_symbol_3 + 
		      gensymed_symbol_4;
	      top_of_first_update_area = 
		      top_of_first_line_of_first_update_area - 
		      extra_diacritic_height;
	      bottom_of_first_update_area = 
		      top_of_first_line_of_first_update_area + 
		      IFIX(baseline_to_baseline_distance);
	      gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = 
		      IFIX(distance_from_left_to_where_difference_starts_qm);
	      update_images(13,erase_qm,edit_box,edit_box,
		      FIX(gensymed_symbol_1 + gensymed_symbol_2),
		      FIX(top_of_first_update_area),
		      FIX(right_edge_of_text_area),
		      FIX(bottom_of_first_update_area),Kno_bleeding,
		      Qdraw_text_segment_in_text_box,text_segment,
		      text_tail_past_partial_line_update_qm,
		      distance_of_text_segment_from_top,edit_box);
	  }
	  text_segment_qm = 
		  distance_from_left_to_where_difference_starts_qm ? 
		  text_tail_past_partial_line_update_qm : text_segment;
	  if ( !EQ(text_segment_qm,text_tail_past_text_segment_qm)) {
	      line_index_of_second_segment = 
		      distance_from_left_to_where_difference_starts_qm ? 
		      FIXNUM_ADD1(line_index) : line_index;
	      distance_of_start_of_text_segment_from_top = 
		      compute_distance_of_text_line_from_top(line_index_of_second_segment,
		      text_box_format);
	      vertical_delta_to_end_of_text_segment = 
		      FIXNUM_TIMES(FIXNUM_MINUS(find_line_index_for_text_tail(text_segment,
		      text_tail_past_text_segment_qm,line_index),
		      line_index_of_second_segment),
		      baseline_to_baseline_distance);
	      gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
	      gensymed_symbol_3 = IFIX(text_cell_top_margin);
	      gensymed_symbol_4 = 
		      IFIX(distance_of_start_of_text_segment_from_top);
	      top_of_first_line_of_second_update_area = gensymed_symbol_1 
		      + gensymed_symbol_2 + gensymed_symbol_3 + 
		      gensymed_symbol_4;
	      top_of_second_update_area = 
		      top_of_first_line_of_second_update_area - 
		      extra_diacritic_height;
	      bottom_of_second_update_area = 
		      top_of_first_line_of_second_update_area + 
		      IFIX(vertical_delta_to_end_of_text_segment);
	      result = update_images(13,erase_qm,edit_box,edit_box,
		      FIX(left_edge_of_text_area),
		      FIX(top_of_second_update_area),
		      FIX(right_edge_of_text_area),
		      FIX(bottom_of_second_update_area),Kno_bleeding,
		      Qdraw_text_segment_in_text_box,text_segment_qm,
		      text_tail_past_text_segment_qm,
		      distance_of_start_of_text_segment_from_top,edit_box);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* SCRAP-TEXT-REGION */
Object scrap_text_region varargs_1(int, n)
{
    Object text_region, text_box_format_for_scrap_qm, add_to_scrapbook_qm;
    Object replace_fragments_on_sides_qm, handle_spaces_intelligently_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,18);
    INIT_ARGS_nonrelocating();
    text_region = REQUIRED_ARG_nonrelocating();
    text_box_format_for_scrap_qm = REQUIRED_ARG_nonrelocating();
    add_to_scrapbook_qm = REQUIRED_ARG_nonrelocating();
    replace_fragments_on_sides_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    handle_spaces_intelligently_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return scrap_text(5,
	    convert_text_string_to_text(convert_text_region_to_text_string(1,
	    text_region)),text_box_format_for_scrap_qm,add_to_scrapbook_qm,
	    replace_fragments_on_sides_qm,handle_spaces_intelligently_qm);
}

static Object Qscrap;              /* scrap */

static Object Qreplace_fragments_on_sides_qm;  /* replace-fragments-on-sides? */

static Object Qhandle_spaces_intelligently_qm;  /* handle-spaces-intelligently? */

static Object Qtext_box_format;    /* text-box-format */

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

static Object Qformat_frame;       /* format-frame */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qscrapbook;          /* scrapbook */

static Object Qnon_kb_workspace;   /* non-kb-workspace */

/* SCRAP-TEXT */
Object scrap_text varargs_1(int, n)
{
    Object text, text_box_format_for_scrap_qm, add_to_scrapbook_qm;
    Object replace_fragments_on_sides_qm, handle_spaces_intelligently_qm;
    Object scrap, svref_new_value, format_name, scrapbook, workspace_margin;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object x2, sub_class_bit_vector, name_box_qm, top_scrap_qm, temp_1, temp_2;
    SI_Long spacing, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,19);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    text_box_format_for_scrap_qm = REQUIRED_ARG_nonrelocating();
    add_to_scrapbook_qm = REQUIRED_ARG_nonrelocating();
    replace_fragments_on_sides_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    handle_spaces_intelligently_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    scrap = make_frame(Qscrap);
    change_slot_value(3,scrap,Qreplace_fragments_on_sides_qm,
	    replace_fragments_on_sides_qm);
    change_slot_value(3,scrap,Qhandle_spaces_intelligently_qm,
	    handle_spaces_intelligently_qm);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(scrap,Qtext_box_format);
    svref_new_value = text_box_format_for_scrap_qm;
    if (svref_new_value);
    else {
	format_name = get_lookup_slot_value(scrap,
		Qdefault_text_box_format_name);
	svref_new_value = get_instance_with_name_if_any(Qformat_frame,
		format_name);
	if (svref_new_value);
	else
	    svref_new_value = make_format_frame(format_name);
    }
    SVREF(scrap,FIX((SI_Long)17L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(scrap,Qbox_translation_and_text);
    svref_new_value = slot_value_cons_1(No_value,text);
    SVREF(scrap,FIX((SI_Long)16L)) = svref_new_value;
    reformat_text_box_in_place(1,scrap);
    if (add_to_scrapbook_qm) {
	scrapbook = get_workspace(Qscrapbook);
	if (scrapbook);
	else
	    scrapbook = make_workspace(7,Qnon_kb_workspace,Qscrapbook,Nil,
		    Nil,Nil,Nil,Current_workstation);
	workspace_margin = ISVREF(scrapbook,(SI_Long)17L);
	spacing = (SI_Long)10L;
	gensymed_symbol = ACCESS_ONCE(ISVREF(scrapbook,(SI_Long)14L));
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
	if (SIMPLE_VECTOR_P(subblock) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subblock)) > (SI_Long)2L && 
		 !EQ(ISVREF(subblock,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(subblock,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_name_box_class_description,
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
	    name_box_qm = subblock;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	name_box_qm = Qnil;
      end_1:;
	top_scrap_qm = get_scrap_if_any();
	if (top_scrap_qm) {
	    gensymed_symbol = ISVREF(top_scrap_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	}
	else {
	    gensymed_symbol = ISVREF(scrapbook,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(workspace_margin);
	    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	if (top_scrap_qm) {
	    gensymed_symbol = ISVREF(top_scrap_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = spacing;
	    gensymed_symbol = ISVREF(scrap,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(scrap,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2 - 
		    gensymed_symbol_3);
	}
	else {
	    gensymed_symbol = ISVREF(scrapbook,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(workspace_margin);
	    temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	add_to_workspace(6,scrap,scrapbook,temp_1,temp_2,T,T);
	if (name_box_qm) {
	    update_images_of_block(name_box_qm,T,T);
	    gensymed_symbol = ISVREF(scrap,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol = ISVREF(scrap,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = spacing;
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2 - 
		    gensymed_symbol_3;
	    gensymed_symbol = ISVREF(name_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    shift_block(name_box_qm,temp_1,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    enlarge_workspace_for_block_rectangle_if_necessary(name_box_qm,
		    scrapbook);
	    update_images_of_block(name_box_qm,Nil,T);
	}
	delete_excess_scraps_if_any(scrapbook);
    }
    return VALUES_1(scrap);
}

static Object Qmaximum_number_of_scraps_to_keep;  /* maximum-number-of-scraps-to-keep */

/* DELETE-EXCESS-SCRAPS-IF-ANY */
Object delete_excess_scraps_if_any(scrapbook)
    Object scrapbook;
{
    Object maximum_number_of_scraps_to_keep, number_of_scraps_seen_so_far;
    Object gensymed_symbol, constant_queue, head, queue_element, subblock;
    Object next_queue_element, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,20);
    maximum_number_of_scraps_to_keep = 
	    get_lookup_slot_value_given_default(Editor_parameters,
	    Qmaximum_number_of_scraps_to_keep,FIX((SI_Long)50L));
    number_of_scraps_seen_so_far = FIX((SI_Long)0L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(scrapbook,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    constant_queue = gensymed_symbol;
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = constant_queue_next(head,constant_queue);
    subblock = Nil;
    next_queue_element = Nil;
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    subblock = ISVREF(queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(queue_element,constant_queue);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
    if (temp)
	number_of_scraps_seen_so_far = 
		FIXNUM_ADD1(number_of_scraps_seen_so_far);
    if (FIXNUM_GT(number_of_scraps_seen_so_far,
	    maximum_number_of_scraps_to_keep)) {
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
	if (temp) {
	    delete_frame(subblock);
	    constant_queue_delete(2,queue_element,constant_queue);
	}
    }
    queue_element = next_queue_element;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* THERE-IS-A-SCRAP-P */
Object there_is_a_scrap_p()
{
    Object scrapbook_qm, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, ab_loop_it_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(126,21);
    scrapbook_qm = get_workspace(Qscrapbook);
    if (scrapbook_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(scrapbook_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	ab_loop_it_ = Nil;
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
	superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
	    ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-SCRAP-IF-ANY */
Object get_scrap_if_any()
{
    Object scrapbook_qm, gensymed_symbol, top_edge_so_far, top_choice_qm;
    Object ab_queue_form_, ab_next_queue_element_, subblock, top_edge;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,22);
    scrapbook_qm = get_workspace(Qscrapbook);
    if (scrapbook_qm) {
	gensymed_symbol = ISVREF(scrapbook_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	top_edge_so_far = gensymed_symbol;
	top_choice_qm = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(scrapbook_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	top_edge = Nil;
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
	gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	top_edge = gensymed_symbol;
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
	if (temp ? FIXNUM_LT(top_edge,top_edge_so_far) : TRUEP(Nil)) {
	    top_choice_qm = subblock;
	    top_edge_so_far = top_edge;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(top_choice_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COERCE-SCRAP-TO-TEXT-STRING */
Object coerce_scrap_to_text_string varargs_1(int, n)
{
    Object scrap, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,23);
    INIT_ARGS_nonrelocating();
    scrap = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     get_scrap_if_any();
    END_ARGS_nonrelocating();
    temp = ISVREF(scrap,(SI_Long)16L);
    return convert_text_to_text_string(1,CDR(temp));
}

/* CHANGE-EDIT-BOX-CURSOR-POSITION */
Object change_edit_box_cursor_position varargs_1(int, n)
{
    Object line_index, character_index;
    Object no_parsing_or_ellipsis_deletion_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,24);
    INIT_ARGS_nonrelocating();
    line_index = REQUIRED_ARG_nonrelocating();
    character_index = REQUIRED_ARG_nonrelocating();
    no_parsing_or_ellipsis_deletion_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return change_edit_box(9,Nil,line_index,character_index,Nil,Nil,Nil,
	    Nil,Nil,no_parsing_or_ellipsis_deletion_qm);
}

Object The_type_description_of_text_inserter_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_text_inserter_spots, Qchain_of_available_text_inserter_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Text_inserter_spot_count, Qtext_inserter_spot_count);

Object Chain_of_available_text_inserter_spots_vector = UNBOUND;

/* TEXT-INSERTER-SPOT-STRUCTURE-MEMORY-USAGE */
Object text_inserter_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(126,25);
    temp = Text_inserter_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEXT-INSERTER-SPOT-COUNT */
Object outstanding_text_inserter_spot_count()
{
    Object def_structure_text_inserter_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,26);
    gensymed_symbol = IFIX(Text_inserter_spot_count);
    def_structure_text_inserter_spot_variable = 
	    Chain_of_available_text_inserter_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_text_inserter_spot_variable))
	goto end_loop;
    def_structure_text_inserter_spot_variable = 
	    ISVREF(def_structure_text_inserter_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEXT-INSERTER-SPOT-1 */
Object reclaim_text_inserter_spot_1(text_inserter_spot)
    Object text_inserter_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(126,27);
    inline_note_reclaim_cons(text_inserter_spot,Nil);
    structure_being_reclaimed = text_inserter_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(text_inserter_spot,(SI_Long)2L));
      SVREF(text_inserter_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_text_inserter_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(text_inserter_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_text_inserter_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = text_inserter_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-INSERTER-SPOT */
Object reclaim_structure_for_text_inserter_spot(text_inserter_spot)
    Object text_inserter_spot;
{
    x_note_fn_call(126,28);
    return reclaim_text_inserter_spot_1(text_inserter_spot);
}

static Object Qg2_defstruct_structure_name_text_inserter_spot_g2_struct;  /* g2-defstruct-structure-name::text-inserter-spot-g2-struct */

/* MAKE-PERMANENT-TEXT-INSERTER-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_text_inserter_spot_structure_internal()
{
    Object def_structure_text_inserter_spot_variable;
    Object defstruct_g2_text_inserter_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(126,29);
    def_structure_text_inserter_spot_variable = Nil;
    atomic_incff_symval(Qtext_inserter_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_text_inserter_spot_variable = Nil;
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
	defstruct_g2_text_inserter_spot_variable = the_array;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_inserter_spot_g2_struct;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_text_inserter_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_text_inserter_spot_variable = 
		defstruct_g2_text_inserter_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_text_inserter_spot_variable);
}

/* MAKE-TEXT-INSERTER-SPOT-1 */
Object make_text_inserter_spot_1()
{
    Object def_structure_text_inserter_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(126,30);
    def_structure_text_inserter_spot_variable = 
	    ISVREF(Chain_of_available_text_inserter_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_text_inserter_spot_variable) {
	svref_arg_1 = Chain_of_available_text_inserter_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_text_inserter_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_text_inserter_spot_g2_struct;
    }
    else
	def_structure_text_inserter_spot_variable = 
		make_permanent_text_inserter_spot_structure_internal();
    inline_note_allocate_cons(def_structure_text_inserter_spot_variable,Nil);
    SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_text_inserter_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_text_inserter_spot_variable);
}

/* GENERATE-SPOT-FOR-SCRAP */
Object generate_spot_for_scrap(scrap,mouse_pointer)
    Object scrap, mouse_pointer;
{
    x_note_fn_call(126,31);
    return push_last_spot(mouse_pointer,make_text_inserter_spot_1(),scrap);
}

static Object Qword_inserter;      /* word-inserter */

static Object Qcharacter_sequence_inserter;  /* character-sequence-inserter */

static Object Qcharacter_inserter;  /* character-inserter */

static Object Qend;                /* end */

/* SELECT-TEXT-REGION-IN-SCRAP */
Object select_text_region_in_scrap(scrap,x_in_workspace,y_in_workspace)
    Object scrap, x_in_workspace, y_in_workspace;
{
    Object temp, text, selected_line_index, selected_character_index;
    Object text_tail, beginning_line_index, beginning_character_index;
    Object end_or_end_line_index, end_character_index, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, character_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Object result;

    x_note_fn_call(126,32);
    temp = ISVREF(scrap,(SI_Long)16L);
    text = CDR(temp);
    selected_line_index = Nil;
    selected_character_index = Nil;
    text_tail = Nil;
    beginning_line_index = Nil;
    beginning_character_index = Nil;
    end_or_end_line_index = Nil;
    end_character_index = Nil;
    result = find_position_in_text(12,scrap,Nil,Nil,Nil,T,x_in_workspace,
	    y_in_workspace,Nil,Nil,Nil,Nil,T);
    MVS_3(result,selected_line_index,selected_character_index,text_tail);
    gensymed_symbol = ISVREF(scrap,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qword_inserter,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qcharacter_sequence_inserter,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    if (temp_1) {
	result = find_next_character_if_any(selected_line_index,
		selected_character_index,text_tail);
	character_qm = NTH_VALUE((SI_Long)3L, result);
	if ( !( !TRUEP(character_qm) || blank_p(character_qm))) {
	    result = find_word_boundary_in_text(selected_line_index,
		    selected_character_index,text,text_tail,T);
	    MVS_2(result,beginning_line_index,beginning_character_index);
	    result = find_word_boundary_in_text(selected_line_index,
		    selected_character_index,text,text_tail,Nil);
	    MVS_2(result,end_or_end_line_index,end_character_index);
	    temp = T;
	}
	else
	    temp = Nil;
    }
    else {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qcharacter_inserter,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    result = find_next_character_if_any(selected_line_index,
		    selected_character_index,text_tail);
	    MVS_2(result,end_or_end_line_index,end_character_index);
	    if (end_or_end_line_index) {
		beginning_line_index = selected_line_index;
		beginning_character_index = selected_character_index;
		temp = T;
	    }
	    else
		temp = Nil;
	}
	else {
	    beginning_line_index = FIX((SI_Long)1L);
	    beginning_character_index = FIX((SI_Long)0L);
	    end_or_end_line_index = Qend;
	    temp = T;
	}
    }
    if (temp)
	return make_text_region(6,scrap,Nil,beginning_line_index,
		beginning_character_index,end_or_end_line_index,
		end_character_index);
    else
	return VALUES_1(Nil);
}

/* FIND-WORD-BOUNDARY-IN-TEXT */
Object find_word_boundary_in_text(selected_line_index,
	    selected_character_index,text,selected_text_tail,backwards_qm)
    Object selected_line_index, selected_character_index, text;
    Object selected_text_tail, backwards_qm;
{
    Object adjacent_character_qm, line_index_away_from_cursor_qm;
    Object character_index_away_from_cursor_qm, text_tail_qm, line_index;
    Object character_index, text_tail;
    Object result;

    x_note_fn_call(126,33);
    adjacent_character_qm = Nil;
    line_index_away_from_cursor_qm = Nil;
    character_index_away_from_cursor_qm = Nil;
    text_tail_qm = Nil;
    line_index = selected_line_index;
    character_index = selected_character_index;
    text_tail = selected_text_tail;
  next_loop:
    if (backwards_qm)
	result = find_previous_character_if_any(line_index,character_index,
		text_tail,text);
    else
	result = find_next_character_if_any(line_index,character_index,
		text_tail);
    MVS_4(result,line_index_away_from_cursor_qm,
	    character_index_away_from_cursor_qm,text_tail_qm,
	    adjacent_character_qm);
    if ( !TRUEP(line_index_away_from_cursor_qm) || adjacent_character_qm 
	    && blank_p(adjacent_character_qm))
	return VALUES_3(line_index,character_index,text_tail);
    line_index = line_index_away_from_cursor_qm;
    character_index = character_index_away_from_cursor_qm;
    text_tail = text_tail_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-SELECTED-TEXT-REGION-FOR-EDIT-BOX */
Object get_selected_text_region_for_edit_box()
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,34);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(Current_edit_state,
	    (SI_Long)13L),(SI_Long)14L));
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
    superior_class_bit_number = IFIX(ISVREF(Text_region_class_description,
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
    if (temp ?  !EQ(subblock,ISVREF(Current_edit_state,(SI_Long)46L)) : 
	    TRUEP(Nil))
	return VALUES_1(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qpaste_from_current_scrap_if_any;  /* paste-from-current-scrap-if-any */

/* PASTE-FROM-CURRENT-SCRAP-IF-ANY */
Object paste_from_current_scrap_if_any()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, scrap_qm;
    Object text_string, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,35);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qpaste_from_current_scrap_if_any;
      }
      scrap_qm = get_scrap_if_any();
      if (scrap_qm) {
	  text_string = coerce_scrap_to_text_string(1,scrap_qm);
	  temp_1 = get_lookup_slot_value(scrap_qm,
		  Qreplace_fragments_on_sides_qm);
	  paste_text_string(3,text_string,temp_1,
		  get_lookup_slot_value(scrap_qm,
		  Qhandle_spaces_intelligently_qm));
	  reclaim_text_string(text_string);
	  result = VALUES_1(T);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qpaste_text_string;  /* paste-text-string */

static Object Qinsert_text_string_in_text_being_edited;  /* insert-text-string-in-text-being-edited */

static Object Qinsert_text_string_at_cursor;  /* insert-text-string-at-cursor */

/* PASTE-TEXT-STRING */
Object paste_text_string varargs_1(int, n)
{
    Object text_string;
    Object replace_fragments_on_sides_qm, handle_spaces_intelligently_qm;
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, text_region_qm;
    Object text_tail, start_line_index, start_character_index, end_line_index;
    Object end_character_index;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(126,36);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    replace_fragments_on_sides_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    handle_spaces_intelligently_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    1);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qpaste_text_string;
      }
      text_region_qm = get_selected_text_region_for_edit_box();
      if (text_region_qm) {
	  result = get_text_region_position(1,text_region_qm);
	  MVS_5(result,text_tail,start_line_index,start_character_index,
		  end_line_index,end_character_index);
	  delete_frame(text_region_qm);
	  change_edit_box_cursor_position(3,end_line_index,
		  end_character_index,T);
	  index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	  PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		  0);
	    if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		    Size_of_basic_backtrace_information),
		    Maximum_index_in_backtrace_stack_for_internal_error)) {
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = Nil;
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = 
			Qinsert_text_string_in_text_being_edited;
	    }
	    result = insert_text_string_in_text_being_edited(8,text_string,
		    replace_fragments_on_sides_qm,
		    handle_spaces_intelligently_qm,start_line_index,
		    start_character_index,text_tail,end_line_index,
		    end_character_index);
	  POP_SPECIAL();
      }
      else {
	  index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	  PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		  0);
	    if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		    Size_of_basic_backtrace_information),
		    Maximum_index_in_backtrace_stack_for_internal_error)) {
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = Nil;
		temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		Index_of_top_of_backtrace_stack = temp;
		temp = Backtrace_stack_for_internal_error;
		svref_arg_2 = Index_of_top_of_backtrace_stack;
		SVREF(temp,svref_arg_2) = Qinsert_text_string_at_cursor;
	    }
	    result = insert_text_string_at_cursor(3,text_string,
		    replace_fragments_on_sides_qm,
		    handle_spaces_intelligently_qm);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

static Object Qscrap_format;       /* scrap-format */

static Object Qpaste;              /* paste */

/* COERCE-TEXT-REGION-TO-SCRAP */
Object coerce_text_region_to_scrap(text_region)
    Object text_region;
{
    Object replace_fragments_on_sides_qm, handle_spaces_intelligently_qm, temp;
    Object svref_arg_1;

    x_note_fn_call(126,37);
    replace_fragments_on_sides_qm = Nil;
    handle_spaces_intelligently_qm = 
	    handle_spaces_intelligently_p(text_region);
    temp = get_instance_with_name_if_any(Qformat_frame,Qscrap_format);
    if (temp);
    else
	temp = make_format_frame(Qscrap_format);
    scrap_text_region(5,text_region,temp,T,replace_fragments_on_sides_qm,
	    handle_spaces_intelligently_qm);
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)45L)) = T;
    if (ISVREF(Current_edit_state,(SI_Long)43L))
	enable_or_disable_subcommand(3,ISVREF(Current_edit_state,
		(SI_Long)43L),Qpaste,Nil);
    return copy_text_region_to_cut_buffer_if_appropriate(text_region);
}

static Object Qno_native_clipboard;  /* no-native-clipboard */

/* COPY-TEXT-REGION-TO-CUT-BUFFER-IF-APPROPRIATE */
Object copy_text_region_to_cut_buffer_if_appropriate(text_region)
    Object text_region;
{
    Object text_string;

    x_note_fn_call(126,38);
    if (Servicing_workstation_qm) {
	if (FIXNUM_LT(Icp_window_protocol_supports_native_cut_and_paste,
		ISVREF(Current_workstation_window,(SI_Long)11L)) &&  
		!TRUEP(get_gensym_window_parameter(Current_workstation_window,
		Qno_native_clipboard))) {
	    text_string = convert_text_region_to_text_string(1,text_region);
	    copy_text_string_to_cut_buffer(Current_workstation_window,
		    text_string);
	    reclaim_text_string(text_string);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtruth_value;        /* truth-value */

/* G2-COPY-TEXT-TO-CLIPBOARD */
Object g2_copy_text_to_clipboard(text_string_as_evaluation_value,
	    g2_window_as_evaluation_value)
    Object text_string_as_evaluation_value, g2_window_as_evaluation_value;
{
    Object text_string, g2_window, value_1, workstation, window, x2;
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,39);
    text_string = text_string_as_evaluation_value;
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    value_1 = Nil;
    workstation = Nil;
    window = Nil;
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	workstation = ISVREF(g2_window,(SI_Long)20L);
	temp = TRUEP(workstation);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	window = ISVREF(workstation,(SI_Long)1L);
	temp = TRUEP(window);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? FIXNUM_LT(Icp_window_protocol_supports_native_cut_and_paste,
	    ISVREF(window,(SI_Long)11L)) &&  
	    !TRUEP(get_gensym_window_parameter(window,
	    Qno_native_clipboard)) : TRUEP(Nil)) {
	copy_text_string_to_cut_buffer(window,text_string);
	value_1 = Truth;
    }
    else
	value_1 = Falsity;
    reclaim_text_string(text_string_as_evaluation_value);
    IDENTITY(g2_window_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp_1 = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp_1 = Evaluation_false_value;
    else
	temp_1 = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp_1);
}

/* OBTAIN-PASTE-REQUEST-ID-FOR-EDITOR */
Object obtain_paste_request_id_for_editor(workstation)
    Object workstation;
{
    Object temp, temp_1;

    x_note_fn_call(126,40);
    temp = Current_edit_state;
    temp_1 = ISVREF(workstation,(SI_Long)44L);
    SVREF(temp,FIX((SI_Long)89L)) = temp_1;
    temp = FIXNUM_ADD1(ISVREF(workstation,(SI_Long)44L));
    SVREF(workstation,FIX((SI_Long)44L)) = temp;
    return VALUES_1(temp_1);
}

/* REQUEST-PASTE-FOR-EDITOR */
Object request_paste_for_editor()
{
    Object temp;

    x_note_fn_call(126,41);
    if (Servicing_workstation_qm) {
	temp = Current_workstation_window;
	request_paste_of_cut_buffer_text(temp,
		obtain_paste_request_id_for_editor(Current_workstation));
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* REQUEST-PASTE-AVAILABILITY-FOR-EDITOR */
Object request_paste_availability_for_editor()
{
    Object temp;

    x_note_fn_call(126,42);
    if (Servicing_workstation_qm) {
	temp = Current_workstation_window;
	request_paste_availability_status(temp,
		obtain_paste_request_id_for_editor(Current_workstation));
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLE-PASTE-EVENT-IN-G2 */
Object handle_paste_event_in_g2(gensym_window,text_string,request_id,
	    timestamp_qm)
    Object gensym_window, text_string, request_id, timestamp_qm;
{
    Object workstation, x, y, timestamp, pane_qm, image_plane_qm;
    SI_Long event_code;
    Object result;

    x_note_fn_call(126,43);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    x = ISVREF(workstation,(SI_Long)5L);
    y = ISVREF(workstation,(SI_Long)6L);
    timestamp = timestamp_qm;
    if (timestamp);
    else
	timestamp = 
		FIXNUM_ADD(Additional_time_for_synthetic_paste_event_timestamps,
		ISVREF(ISVREF(workstation,(SI_Long)11L),(SI_Long)7L));
    event_code = (SI_Long)786L;
    result = decode_window_position(gensym_window,x,y);
    MVS_2(result,pane_qm,image_plane_qm);
    return enqueue_workstation_event(9,workstation,FIX(event_code),x,y,
	    timestamp,gensym_window,pane_qm,image_plane_qm,
	    gensym_list_2(request_id,copy_text_string(text_string)));
}

/* HANDLE-PASTE-AVAILABILITY-EVENT-IN-G2 */
Object handle_paste_availability_event_in_g2(gensym_window,status,timestamp_qm)
    Object gensym_window, status, timestamp_qm;
{
    Object workstation, x, y, timestamp, pane_qm, image_plane_qm;
    SI_Long event_code;
    Object result;

    x_note_fn_call(126,44);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    SVREF(workstation,FIX((SI_Long)45L)) = status;
    x = ISVREF(workstation,(SI_Long)5L);
    y = ISVREF(workstation,(SI_Long)6L);
    event_code = (SI_Long)787L;
    timestamp = timestamp_qm;
    if (timestamp);
    else
	timestamp = 
		FIXNUM_ADD(Additional_time_for_synthetic_paste_event_timestamps,
		ISVREF(ISVREF(workstation,(SI_Long)11L),(SI_Long)7L));
    result = decode_window_position(gensym_window,x,y);
    MVS_2(result,pane_qm,image_plane_qm);
    return enqueue_workstation_event(8,workstation,FIX(event_code),x,y,
	    timestamp,gensym_window,pane_qm,image_plane_qm);
}

/* TEXT-STRING-MATCHES-CURRENT-SCRAP-P */
Object text_string_matches_current_scrap_p(text_string)
    Object text_string;
{
    Object scrap_qm, text_string_from_scrap, temp;

    x_note_fn_call(126,45);
    scrap_qm = get_scrap_if_any();
    if (scrap_qm) {
	text_string_from_scrap = coerce_scrap_to_text_string(1,scrap_qm);
	temp = string_eq_w(text_string,text_string_from_scrap);
	reclaim_text_string(text_string_from_scrap);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* EDITOR-HAS-NON-EMPTY-TEXT-REGION-P */
Object editor_has_non_empty_text_region_p()
{
    Object text_region_qm;

    x_note_fn_call(126,46);
    text_region_qm = get_selected_text_region_for_edit_box();
    if (text_region_qm)
	return VALUES_1( !TRUEP(empty_text_region_p(text_region_qm)) ? T : 
		Nil);
    else
	return VALUES_1(Nil);
}

/* TEXT-CAN-BE-TRANSFERRED-WITHIN-EDITOR-P */
Object text_can_be_transferred_within_editor_p()
{
    Object text_region_qm;

    x_note_fn_call(126,47);
    text_region_qm = get_selected_text_region_for_edit_box();
    if (text_region_qm)
	return within_text_region_p(text_region_qm,
		ISVREF(Current_edit_state,(SI_Long)24L),
		ISVREF(Current_edit_state,(SI_Long)25L));
    else
	return VALUES_1(Nil);
}

/* TEXT-CAN-BE-CUT-WITHIN-EDITOR-P */
Object text_can_be_cut_within_editor_p()
{
    x_note_fn_call(126,48);
    return editor_has_non_empty_text_region_p();
}

/* TEXT-CAN-BE-COPIED-WITHIN-EDITOR-P */
Object text_can_be_copied_within_editor_p()
{
    x_note_fn_call(126,49);
    return editor_has_non_empty_text_region_p();
}

/* TEXT-CAN-BE-PASTED-IN-CURRENT-WORKSTATION-P */
Object text_can_be_pasted_in_current_workstation_p()
{
    x_note_fn_call(126,50);
    if (FIXNUM_LT(Icp_window_protocol_supports_native_cut_and_paste,
	    ISVREF(Current_workstation_window,(SI_Long)11L)) &&  
	    !TRUEP(get_gensym_window_parameter(Current_workstation_window,
	    Qno_native_clipboard)))
	return VALUES_1(ISVREF(Current_workstation,(SI_Long)45L));
    else
	return there_is_a_scrap_p();
}

/* TEXT-CAN-BE-DELETED-WITHIN-EDITOR-P */
Object text_can_be_deleted_within_editor_p()
{
    x_note_fn_call(126,51);
    return editor_has_non_empty_text_region_p();
}

static Object string_constant;     /* "This has been revealed because of a parsing problem: ~A" */

static Object string_constant_1;   /* "~A" */

/* HANDLE-PARSING-OR-COMPILATION-PROBLEM */
Object handle_parsing_or_compilation_problem varargs_1(int, n)
{
    Object problem_string;
    Object line_index_qm, character_index_qm, temp, temp_1, svref_new_value;
    char edit_workspace_hidden_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,52);
    INIT_ARGS_nonrelocating();
    problem_string = REQUIRED_ARG_nonrelocating();
    line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    edit_workspace_hidden_qm =  !TRUEP(ISVREF(Current_edit_workspace,
	    (SI_Long)16L));
    temp = ISVREF(Current_edit_state,(SI_Long)42L);
    if (temp);
    else {
	temp_1 = Current_edit_state;
	temp = gensym_list_4(Nil,Nil,Nil,Nil);
	SVREF(temp_1,FIX((SI_Long)42L)) = temp;
    }
    if ( !TRUEP(CADDDR(temp))) {
	svref_new_value = ISVREF(Current_edit_state,(SI_Long)42L);
	if (svref_new_value);
	else {
	    temp_1 = Current_edit_state;
	    svref_new_value = gensym_list_4(Nil,Nil,Nil,Nil);
	    SVREF(temp_1,FIX((SI_Long)42L)) = svref_new_value;
	}
	temp_1 = copy_text_string(problem_string);
	M_CADDDR(svref_new_value) = temp_1;
	svref_new_value = ISVREF(Current_edit_state,(SI_Long)42L);
	if (svref_new_value);
	else {
	    temp_1 = Current_edit_state;
	    svref_new_value = gensym_list_4(Nil,Nil,Nil,Nil);
	    SVREF(temp_1,FIX((SI_Long)42L)) = svref_new_value;
	}
	M_CADR(svref_new_value) = line_index_qm;
	svref_new_value = ISVREF(Current_edit_state,(SI_Long)42L);
	if (svref_new_value);
	else {
	    temp_1 = Current_edit_state;
	    svref_new_value = gensym_list_4(Nil,Nil,Nil,Nil);
	    SVREF(temp_1,FIX((SI_Long)42L)) = svref_new_value;
	}
	M_CADDR(svref_new_value) = character_index_qm;
    }
    display_editor_notification_1(tformat_text_string(2,
	    edit_workspace_hidden_qm ? string_constant : string_constant_1,
	    problem_string));
    if (edit_workspace_hidden_qm &&  
	    !TRUEP(Keep_edit_workspace_hidden_no_matter_what_qm))
	return put_up_edit_workspace(2,Current_edit_workspace,
		Current_workstation);
    else
	return VALUES_1(Nil);
}

static Object Qkanji_code_entry;   /* kanji-code-entry */

static Object Qkorean;             /* korean */

static Object Qcheck_hangul_code_entry_text;  /* check-hangul-code-entry-text */

static Object Qcheck_kanji_code_entry_text;  /* check-kanji-code-entry-text */

static Object Qhangul_code_entry;  /* hangul-code-entry */

static Object Qcyrillic_code_entry;  /* cyrillic-code-entry */

static Object Qcheck_cyrillic_code_entry_text;  /* check-cyrillic-code-entry-text */

static Object Qsearch_for_text_in_editor;  /* search-for-text-in-editor */

static Object Qsearch_forward_incrementally_for_text_in_editor;  /* search-forward-incrementally-for-text-in-editor */

static Object Qinsertion_of_symbol;  /* insertion-of-symbol */

static Object Qcheck_insertion_of_symbol_entry_text;  /* check-insertion-of-symbol-entry-text */

static Object Qcheck_special_character_entry_text;  /* check-special-character-entry-text */

static Object Qkanji_characters;   /* kanji-characters */

static Object Qhangul_characters;  /* hangul-characters */

static Object Qspecial_characters;  /* special-characters */

static Object Qworkspace;          /* workspace */

static Object Qdefault_workspace_frame_style;  /* default-workspace-frame-style */

static Object Qbelow;              /* below */

static Object Qdelete_image_plane;  /* delete-image-plane */

/* ENTER-ESCAPE-CONTEXT */
Object enter_escape_context varargs_1(int, n)
{
    Object special_entry_context;
    Object dont_have_riding_image_plane_qm, temp, temp_1, gensymed_symbol;
    Object temp_2, temp_3, temp_4, temp_5, temp_6, characters_workspace_qm;
    Object image_plane_qm, special_entry_workspace;
    Object image_plane_for_special_special_entry_workspace, svref_arg_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,53);
    INIT_ARGS_nonrelocating();
    special_entry_context = REQUIRED_ARG_nonrelocating();
    dont_have_riding_image_plane_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp =  !TRUEP(dont_have_riding_image_plane_qm) ? 
	    find_image_plane_for_workspace_in_pane(Current_edit_workspace,
	    Current_workstation_detail_pane) : Nil;
    temp_1 = ISVREF(Current_edit_state,(SI_Long)13L);
    gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)14L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)-8L;
    temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)14L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)14L;
    temp_3 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)14L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)-8L;
    temp_4 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)14L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)14L;
    temp_5 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    if (EQ(special_entry_context,Qkanji_code_entry)) {
	temp_6 = get_language_for_current_workstation_if_any();
	if (temp_6);
	else
	    temp_6 = Language_parameters ? ISVREF(Language_parameters,
		    (SI_Long)22L) : Qnil;
	if (temp_6);
	else
	    temp_6 = Default_language;
	temp_6 = EQ(temp_6,Qkorean) ? Qcheck_hangul_code_entry_text : 
		Qcheck_kanji_code_entry_text;
    }
    else if (EQ(special_entry_context,Qhangul_code_entry))
	temp_6 = Qcheck_hangul_code_entry_text;
    else if (EQ(special_entry_context,Qcyrillic_code_entry))
	temp_6 = Qcheck_cyrillic_code_entry_text;
    else if (EQ(special_entry_context,Qsearch_for_text_in_editor))
	temp_6 = Qsearch_forward_incrementally_for_text_in_editor;
    else if (EQ(special_entry_context,Qinsertion_of_symbol))
	temp_6 = Qcheck_insertion_of_symbol_entry_text;
    else
	temp_6 = Qcheck_special_character_entry_text;
    enter_editing_context(18,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,temp,temp_1,
	    temp_2,temp_3,temp_4,temp_5,Nil,special_entry_context,temp_6,T);
    if (EQ(special_entry_context,Qkanji_code_entry))
	temp = Qkanji_characters;
    else if (EQ(special_entry_context,Qhangul_code_entry))
	temp = Qhangul_characters;
    else
	temp = Qspecial_characters;
    characters_workspace_qm = get_instance_with_name_if_any(Qworkspace,temp);
    if (characters_workspace_qm) {
	image_plane_qm = 
		find_image_plane_for_workspace_in_pane(characters_workspace_qm,
		Current_workstation_detail_pane);
	special_entry_workspace = 
		ISVREF(Specific_structure_for_current_workstation_context,
		(SI_Long)12L);
	image_plane_for_special_special_entry_workspace = 
		find_image_plane_for_workspace_in_pane(special_entry_workspace,
		Current_workstation_detail_pane);
	if (T) {
	    temp = Current_workstation_detail_pane;
	    image_plane_qm = new_get_available_image_plane(temp,
		    lookup_frame_description_reference_of_frame_style(Qdefault_workspace_frame_style,
		    Qdefault_workspace_frame_style),Qbelow,
		    image_plane_for_special_special_entry_workspace);
	    svref_arg_1 = Current_workstation_context;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = image_plane_qm;
	    svref_arg_1 = Current_workstation_context;
	    SVREF(svref_arg_1,FIX((SI_Long)6L)) = Qdelete_image_plane;
	    temp_3 = image_plane_qm;
	    temp_2 = get_default_image_x_scale(image_plane_qm);
	    temp_1 = get_default_image_y_scale(image_plane_qm);
	    gensymed_symbol = ISVREF(characters_workspace_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	    gensymed_symbol = ISVREF(characters_workspace_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    return transform_image(10,temp_3,characters_workspace_qm,
		    temp_2,temp_1,Nil,Nil,temp,gensymed_symbol,
		    ISVREF(image_plane_for_special_special_entry_workspace,
		    (SI_Long)17L),
		    ISVREF(image_plane_for_special_special_entry_workspace,
		    (SI_Long)18L));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qhangul;             /* hangul */

/* CHECK-HANGUL-CODE-ENTRY-TEXT */
Object check_hangul_code_entry_text varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,54);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return check_kanji_code_entry_text(3,text_being_edited,special_case_qm,
	    Qhangul);
}

static Object Qcyrillic;           /* cyrillic */

/* CHECK-CYRILLIC-CODE-ENTRY-TEXT */
Object check_cyrillic_code_entry_text varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,55);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return check_kanji_code_entry_text(3,text_being_edited,special_case_qm,
	    Qcyrillic);
}

static Object string_constant_2;   /* "Hangul (KS C 5601)" */

static Object string_constant_3;   /* "Cyrillic (ISO 8859-5)" */

static Object Qunicode;            /* unicode */

static Object string_constant_4;   /* "Unicode 2.0" */

static Object string_constant_5;   /* "Kanji (JIS)" */

static Object Qrubout_on_blank_text;  /* rubout-on-blank-text */

static Object string_constant_6;   /* "Please enter a ~d-digit ~a hex code" */

static Object Qjapanese;           /* japanese */

static Object string_constant_7;   /* "~c" */

static Object string_constant_8;   /* "This is an invalid ~a code" */

static Object string_constant_9;   /* "Too many digits" */

/* CHECK-KANJI-CODE-ENTRY-TEXT */
Object check_kanji_code_entry_text varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm, other_script_case_qm, text_line, line_length;
    Object lost_space_at_end_of_line, next_text_tail_qm, charset_name;
    Object force_hexadecimal_qm, effective_line_length, kanji_code;
    Object hex_digit_value, current_edit_state, current_edit_workspace;
    Object gensymed_symbol, x, y, xa, ya, han_interpretation_mode, temp_1;
    Object gensym_character_code, row, text_string_to_insert;
    SI_Long code_digit_length, first_char, start_index, i, ab_loop_bind_;
    SI_Long unicode_full_row, gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(126,56);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    other_script_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = get_next_text_line(text_being_edited);
    MVS_4(result,text_line,line_length,lost_space_at_end_of_line,
	    next_text_tail_qm);
    if (EQ(other_script_case_qm,Qhangul))
	charset_name = string_constant_2;
    else if (EQ(other_script_case_qm,Qcyrillic))
	charset_name = string_constant_3;
    else if (EQ(other_script_case_qm,Qunicode))
	charset_name = string_constant_4;
    else
	charset_name = string_constant_5;
    code_digit_length = EQ(other_script_case_qm,Qcyrillic) ? (SI_Long)2L : 
	    (SI_Long)4L;
    if (IFIX(line_length) > (SI_Long)0L) {
	first_char = UBYTE_16_ISAREF_1(text_line,(SI_Long)0L);
	force_hexadecimal_qm = first_char == (SI_Long)120L ? T : Nil;
	if (force_hexadecimal_qm);
	else
	    force_hexadecimal_qm = first_char == (SI_Long)88L ? T : Nil;
    }
    else
	force_hexadecimal_qm = Nil;
    effective_line_length = force_hexadecimal_qm ? 
	    FIXNUM_SUB1(line_length) : line_length;
    start_index = force_hexadecimal_qm ? (SI_Long)1L : (SI_Long)0L;
    if (EQ(special_case_qm,Qrubout_on_blank_text))
	return return_from_current_workstation_context(1,
		Type_of_current_workstation_context);
    else {
	temp = TRUEP(special_case_qm);
	if (temp);
	else
	    temp = TRUEP(next_text_tail_qm);
	if (temp);
	else
	    temp =  !EQ(lost_space_at_end_of_line,FIX((SI_Long)0L));
	if (temp);
	else
	    temp = IFIX(effective_line_length) > code_digit_length;
	if (temp);
	else {
	    i = start_index;
	    ab_loop_bind_ = IFIX(line_length);
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( 
		    !TRUEP(digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_line,
		    i)),FIX((SI_Long)16L)))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	    temp =  !temp;
	}
	if (temp) {
	    display_editor_notification_1(tformat_text_string(3,
		    string_constant_6,FIX(code_digit_length),charset_name));
	    return VALUES_1(T);
	}
	else if (code_digit_length == IFIX(effective_line_length)) {
	    kanji_code = FIX((SI_Long)0L);
	    i = start_index;
	    ab_loop_bind_ = IFIX(line_length);
	    hex_digit_value = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    hex_digit_value = 
		    digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_line,
		    i)),FIX((SI_Long)16L));
	    kanji_code = FIX((SI_Long)16L * IFIX(kanji_code) + 
		    IFIX(hex_digit_value));
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    if (EQ(other_script_case_qm,Qhangul))
		kanji_code = ksc_to_gensym_ksc(kanji_code);
	    else if (EQ(other_script_case_qm,Qcyrillic))
		kanji_code = iso_8859_5_to_gensym_cyrillic(kanji_code);
	    if (EQ(other_script_case_qm,Qunicode) ? TRUEP(T) :  
		    !(IFIX(kanji_code) == (SI_Long)0L)) {
		if (EQ(other_script_case_qm,Qhangul))
		    temp = 
			    TRUEP(legal_gensym_ksc_character_code_p(kanji_code));
		else if (EQ(other_script_case_qm,Qcyrillic))
		    temp = (SI_Long)8192L <= IFIX(kanji_code) ? 
			    IFIX(kanji_code) <= (SI_Long)8447L : TRUEP(Qnil);
		else if (EQ(other_script_case_qm,Qunicode))
		    temp = TRUEP(T);
		else
		    temp = 
			    TRUEP(legal_gensym_jis_character_code_p(kanji_code));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		return_from_current_workstation_context(1,
			Type_of_current_workstation_context);
		current_edit_state = 
			Specific_structure_for_current_workstation_context;
		PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			3);
		  current_edit_workspace = ISVREF(Current_edit_state,
			  (SI_Long)12L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
			  2);
		    gensymed_symbol = ISVREF(ISVREF(Current_edit_state,
			    (SI_Long)12L),(SI_Long)3L);
		    x = ISVREF(Current_edit_state,(SI_Long)12L);
		    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else {
			x = gensymed_symbol;
			y = ISVREF(Current_edit_state,(SI_Long)2L);
			if (FIXNUMP(y))
			    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
			else if (FIXNUMP(x))
			    temp = TRUEP(Nil);
			else {
			    xa = M_CAR(y);
			    ya = M_CAR(x);
			    temp = FIXNUM_LT(xa,ya);
			    if (temp);
			    else
				temp = FIXNUM_EQ(xa,ya) ? 
					FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
					TRUEP(Qnil);
			}
		    }
		    if ( !temp) {
			han_interpretation_mode = EQ(other_script_case_qm,
				Qhangul) ? Qkorean : Qjapanese;
			PUSH_SPECIAL_WITH_SYMBOL(Han_interpretation_mode,Qhan_interpretation_mode,han_interpretation_mode,
				1);
			  if (EQ(other_script_case_qm,Qunicode))
			      temp_1 = kanji_code;
			  else {
			      if ( !'\\')
				  gensym_character_code = 
					  CHAR_CODE(kanji_code);
			      else {
				  if (CHAR_EQ(CHR('\\'),CHR('~'))) {
				      gensym_character_code = 
					      ISVREF(Reverse_iso_latin1_special_character_code_map,
					      IFIX(CHAR_CODE(kanji_code)));
				      if (gensym_character_code);
				      else {
					  temp_1 = CHAR_CODE(kanji_code);
					  if ( 
						  !(FIXNUM_LE(FIX((SI_Long)-128L),
						  temp_1) && 
						  FIXNUM_LE(temp_1,
						  FIX((SI_Long)127L))))
					      gensym_character_code = Nil;
					  else
					      switch (INTEGER_TO_CHAR(temp_1)) 
							  {
						case 87:
						  gensym_character_code = 
							  Gensym_code_for_capital_ligature_oe;
						  break;
						case 119:
						  gensym_character_code = 
							  Gensym_code_for_small_ligature_oe;
						  break;
						case 42:
						  gensym_character_code = 
							  Gensym_code_for_bullet;
						  break;
						case 38:
						  gensym_character_code = 
							  Gensym_code_for_small_letter_f_with_hook;
						  break;
						case 58:
						  gensym_character_code = 
							  Gensym_code_for_trade_mark_sign;
						  break;
						default:
						  gensym_character_code = Nil;
						  break;
					      }
				      }
				  }
				  else
				      gensym_character_code = Nil;
				  if (gensym_character_code);
				  else if ( !'\\' &&  
					  !TRUEP(Gensym_esc_for_linebreak_qm) 
					  ? CHAR_EQ(kanji_code,
					  Gensym_char_or_code_for_linebreak) 
					  : EQL(kanji_code,
					  Gensym_char_or_code_for_linebreak) 
					  && EQ(CHR('\\'),
					  Gensym_esc_for_linebreak_qm))
				      gensym_character_code = 
					      Gensym_code_for_linebreak;
				  else if ( !'\\' &&  
					  !TRUEP(Gensym_esc_for_paragraph_break_qm) 
					  ? CHAR_EQ(kanji_code,
					  Gensym_char_or_code_for_paragraph_break) 
					  : EQL(kanji_code,
					  Gensym_char_or_code_for_paragraph_break) 
					  && EQ(CHR('\\'),
					  Gensym_esc_for_paragraph_break_qm))
				      gensym_character_code = 
					      Gensym_code_for_paragraph_break;
				  else {
				      gensym_character_code =  
					      !EQ(CHR('\\'),CHR('\\')) ? 
					      FIX((SI_Long)65535L) : Nil;
				      if (gensym_character_code);
				      else
					  gensym_character_code = kanji_code;
				  }
			      }
			      temp = IFIX(gensym_character_code) < 
				      (SI_Long)256L ? 
				      TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				      IFIX(gensym_character_code))) : 
				      TRUEP(Nil);
			      if (temp);
			      else if (FIXNUM_EQ(gensym_character_code,
				      Gensym_code_for_capital_ligature_oe))
				  temp = 'W';
			      else if (FIXNUM_EQ(gensym_character_code,
				      Gensym_code_for_small_ligature_oe))
				  temp = 'w';
			      else if (FIXNUM_EQ(gensym_character_code,
				      Gensym_code_for_bullet))
				  temp = '*';
			      else if (FIXNUM_EQ(gensym_character_code,
				      Gensym_code_for_small_letter_f_with_hook))
				  temp = '&';
			      else if (FIXNUM_EQ(gensym_character_code,
				      Gensym_code_for_trade_mark_sign))
				  temp = ':';
			      else
				  temp = TRUEP(Qnil);
			      if (temp) {
				  row = FIX(IFIX(gensym_character_code) >> 
					   -  - (SI_Long)8L);
				  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				    unicode_full_row = 
					    UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					    IFIX(Row));
				    if ( !(unicode_full_row == 
					    IFIX(Invalid_unicode_full_row))) {
					gensymed_symbol_1 = 
						unicode_full_row << 
						(SI_Long)8L;
					gensymed_symbol_2 = (SI_Long)255L 
						& IFIX(gensym_character_code);
					temp_1 = FIX(gensymed_symbol_1 + 
						gensymed_symbol_2);
				    }
				    else
					temp_1 = Nil;
				  POP_SPECIAL();
			      }
			      else if ((SI_Long)8192L <= 
				      IFIX(gensym_character_code) && 
				      IFIX(gensym_character_code) <= 
				      (SI_Long)8447L) {
				  row = FIX(IFIX(gensym_character_code) >> 
					   -  - (SI_Long)8L);
				  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				    unicode_full_row = 
					    UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					    IFIX(Row));
				    if ( !(unicode_full_row == 
					    IFIX(Invalid_unicode_full_row))) {
					gensymed_symbol_1 = 
						unicode_full_row << 
						(SI_Long)8L;
					gensymed_symbol_2 = (SI_Long)255L 
						& IFIX(gensym_character_code);
					temp_1 = FIX(gensymed_symbol_1 + 
						gensymed_symbol_2);
				    }
				    else
					temp_1 = Nil;
				  POP_SPECIAL();
			      }
			      else {
				  temp_1 = 
					  map_gensym_han_character_code_to_unicode(gensym_character_code);
				  if (temp_1);
				  else {
				      row = 
					      FIX(IFIX(gensym_character_code) 
					      >>  -  - (SI_Long)8L);
				      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
					unicode_full_row = 
						UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
						IFIX(Row));
					if ( !(unicode_full_row == 
						IFIX(Invalid_unicode_full_row))) 
						    {
					    gensymed_symbol_1 = 
						    unicode_full_row << 
						    (SI_Long)8L;
					    gensymed_symbol_2 = 
						    (SI_Long)255L & 
						    IFIX(gensym_character_code);
					    temp_1 = FIX(gensymed_symbol_1 
						    + gensymed_symbol_2);
					}
					else
					    temp_1 = Nil;
				      POP_SPECIAL();
				      if (temp_1);
				      else if (Current_extended_utf_g_low_half_character_qm)
					  temp_1 = 
						  map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
						  gensym_character_code);
				      else
					  temp_1 = FIX((SI_Long)65535L);
				  }
			      }
			  }
			  text_string_to_insert = tformat_text_string(2,
				  string_constant_7,temp_1);
			  insert_text_string_at_cursor(3,
				  text_string_to_insert,Nil,Nil);
			  reclaim_text_string(text_string_to_insert);
			POP_SPECIAL();
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
		return VALUES_1(T);
	    }
	    else
		display_editor_notification_1(tformat_text_string(2,
			string_constant_8,charset_name));
	    return VALUES_1(Qnil);
	}
	else if (code_digit_length < IFIX(effective_line_length))
	    return display_editor_notification_1(tformat_text_string(1,
		    string_constant_9));
	else if (code_digit_length > IFIX(effective_line_length)) {
	    erase_any_temporary_information_on_edit_workspace(2,Nil,T);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qrussian;            /* russian */

static Object Qkanji;              /* kanji */

/* CHECK-INSERTION-OF-SYMBOL-ENTRY-TEXT */
Object check_insertion_of_symbol_entry_text varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,57);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = check_special_character_entry_text(3,text_being_edited,
	    special_case_qm,T);
    if (temp)
	return VALUES_1(temp);
    else {
	temp = get_language_for_current_workstation_if_any();
	if (temp);
	else
	    temp = Language_parameters ? ISVREF(Language_parameters,
		    (SI_Long)22L) : Qnil;
	if (temp);
	else
	    temp = Default_language;
	if (EQ(temp,Qkorean))
	    temp = Qhangul;
	else if (EQ(temp,Qrussian))
	    temp = Qcyrillic;
	else if (EQ(temp,Qjapanese))
	    temp = Qkanji;
	else
	    temp = Qunicode;
	return check_kanji_code_entry_text(3,text_being_edited,
		special_case_qm,temp);
    }
}

Object Editor_special_character_alist = UNBOUND;

/* MAP-EDITOR-SPECIAL-CHARACTER-TYPE-IN */
Object map_editor_special_character_type_in(typed_character,
	    previous_base_character_qm)
    Object typed_character, previous_base_character_qm;
{
    Object presentation_character, lowercase_qm, base_qm, type_ins;
    Object ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(126,58);
    presentation_character = Nil;
    lowercase_qm = Nil;
    base_qm = Nil;
    type_ins = Nil;
    ab_loop_list_ = Editor_special_character_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    presentation_character = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    lowercase_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    base_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    type_ins = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ((previous_base_character_qm ||  !TRUEP(base_qm)) && 
	    (LISTP(type_ins) ? TRUEP(wide_character_member(typed_character,
	    type_ins)) : FIXNUM_EQ(type_ins,typed_character)) && ( 
	    !TRUEP(base_qm) || FIXNUM_EQ(base_qm,previous_base_character_qm)))
	return VALUES_2(presentation_character,base_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAP-COMPOSED-CHARACTER-TO-BASE-CHARACTER-FOR-EDITOR */
Object map_composed_character_to_base_character_for_editor(character_1)
    Object character_1;
{
    Object temp;

    x_note_fn_call(126,59);
    temp = wide_character_assoc(character_1,Editor_special_character_alist);
    temp = THIRD(temp);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(character_1);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object string_constant_10;  /* "Please enter one character" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_11;  /* "Previous character (~c) cannot take this accent" */

static Object string_constant_12;  /* "This has no corresponding special character" */

/* CHECK-SPECIAL-CHARACTER-ENTRY-TEXT */
Object check_special_character_entry_text varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm, general_insertion_of_symbol_case_qm;
    volatile Object text_line;
    Object line_length, superior_edit_state, temp, typed_character;
    Object previous_base_character_qm, previous_line_index;
    Object previous_character_index, previous_text_tail, previous_character_qm;
    Object presentation_character_qm, base_qm, current_edit_state;
    Object current_edit_workspace, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object thing, temp_1, schar_arg_2, schar_new_value, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5;
    SI_Long wide_character, code, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(126,60);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    general_insertion_of_symbol_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_line = Qunbound_in_protected_let;
    line_length = Qunbound_in_protected_let;
    superior_edit_state = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	text_line = convert_text_to_text_string(1,text_being_edited);
	line_length = text_string_length(text_line);
	temp = ISVREF(Current_workstation,(SI_Long)17L);
	superior_edit_state = ISVREF(SECOND(temp),(SI_Long)2L);
	if (EQ(special_case_qm,Qrubout_on_blank_text))
	    SAVE_VALUES(VALUES_1(Nil));
	else if (special_case_qm || IFIX(line_length) > (SI_Long)1L) {
	    if ( !TRUEP(general_insertion_of_symbol_case_qm)) {
		display_editor_notification_1(tformat_text_string(1,
			string_constant_10));
		SAVE_VALUES(VALUES_1(T));
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	else if (IFIX(line_length) > (SI_Long)0L) {
	    wide_character = UBYTE_16_ISAREF_1(text_line,
		    IFIX(FIXNUM_SUB1(line_length)));
	    code = wide_character;
	    if (code < (SI_Long)127L)
		typed_character = (SI_Long)65L <= code && code <= 
			(SI_Long)90L ? FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		typed_character = unicode_lowercase_if_uppercase(FIX(code));
		if (typed_character);
		else
		    typed_character = FIX(code);
	    }
	    previous_base_character_qm = Nil;
	    result = find_previous_character_if_any(ISVREF(superior_edit_state,
		    (SI_Long)24L),ISVREF(superior_edit_state,(SI_Long)25L),
		    ISVREF(superior_edit_state,(SI_Long)26L),
		    ISVREF(superior_edit_state,(SI_Long)15L));
	    MVS_4(result,previous_line_index,previous_character_index,
		    previous_text_tail,previous_character_qm);
	    if (previous_character_qm)
		previous_base_character_qm = 
			map_composed_character_to_base_character_for_editor(previous_character_qm);
	    result = map_editor_special_character_type_in(typed_character,
		    previous_base_character_qm);
	    MVS_2(result,presentation_character_qm,base_qm);
	    if ( !TRUEP(presentation_character_qm) && 
		    previous_base_character_qm && IFIX(typed_character) == 
		    (SI_Long)32L) {
		presentation_character_qm = previous_base_character_qm;
		base_qm = previous_base_character_qm;
	    }
	    if (presentation_character_qm) {
		if ( !TRUEP(base_qm)) {
		    return_from_current_workstation_context(1,
			    Type_of_current_workstation_context);
		    insert_character_at_cursor_from_outside(1,
			    presentation_character_qm);
		    SAVE_VALUES(VALUES_1(T));
		}
		else if (previous_base_character_qm) {
		    return_from_current_workstation_context(1,
			    Type_of_current_workstation_context);
		    current_edit_state = 
			    Specific_structure_for_current_workstation_context;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			    6);
		      current_edit_workspace = ISVREF(Current_edit_state,
			      (SI_Long)12L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
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
				  if (EQ(Current_twriting_output_type,
					  Qwide_string)) {
				      thing = presentation_character_qm;
				      twrite_wide_character(CHARACTERP(thing) 
					      ? CHAR_CODE(thing) : thing);
				  }
				  else {
				      if ( 
					      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					      Total_length_of_current_gensym_string))
					  extend_current_gensym_string(0);
				      temp_1 = Current_gensym_string;
				      schar_arg_2 = 
					      Fill_pointer_for_current_gensym_string;
				      thing = presentation_character_qm;
				      schar_new_value = 
					      CODE_CHAR(CHARACTERP(thing) ?
					       CHAR_CODE(thing) : thing);
				      SET_SCHAR(temp_1,schar_arg_2,
					      schar_new_value);
				      temp_1 = 
					      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				      Fill_pointer_for_current_gensym_string 
					      = temp_1;
				  }
				  temp_1 = Current_wide_string;
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)1L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(temp_1,aref_arg_2,
					  aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)1L >>  -  - (SI_Long)16L;
				  UBYTE_16_ISASET_1(temp_1,aref_arg_2,
					  aref_new_value);
				  aref_arg_2 = (SI_Long)1L;
				  UBYTE_16_ISASET_1(temp_1,aref_arg_2,
					  (SI_Long)0L);
				  result = change_edit_box(6,
					  previous_text_tail,
					  previous_line_index,
					  previous_character_index,
					  ISVREF(Current_edit_state,
					  (SI_Long)24L),
					  ISVREF(Current_edit_state,
					  (SI_Long)25L),Current_wide_string);
				  MVS_6(result,gensymed_symbol,
					  gensymed_symbol_1,
					  gensymed_symbol_2,
					  gensymed_symbol_3,
					  gensymed_symbol_4,gensymed_symbol_5);
				  reclaim_wide_string(Current_wide_string);
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(VALUES_1(T));
		}
		else
		    SAVE_VALUES(VALUES_1(Qnil));
	    }
	    else {
		if ( !TRUEP(general_insertion_of_symbol_case_qm))
		    display_editor_notification_1(tformat_text_string(2,
			    previous_base_character_qm ? 
			    string_constant_11 : string_constant_12,
			    previous_base_character_qm));
		SAVE_VALUES(VALUES_1(Nil));
	    }
	}
	else {
	    erase_any_temporary_information_on_edit_workspace(2,Nil,T);
	    SAVE_VALUES(VALUES_1(Nil));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (text_line) {
	if ( !EQ(text_line,Qunbound_in_protected_let))
	    reclaim_text_string(text_line);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Kforward;            /* :forward */

/* SEARCH-FORWARD-INCREMENTALLY-FOR-TEXT-IN-EDITOR */
Object search_forward_incrementally_for_text_in_editor varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,61);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return search_incrementally_for_text_in_editor(text_being_edited,
	    special_case_qm,Kforward);
}

static Object Kbackward;           /* :backward */

/* SEARCH-BACKWARD-INCREMENTALLY-FOR-TEXT-IN-EDITOR */
Object search_backward_incrementally_for_text_in_editor varargs_1(int, n)
{
    Object text_being_edited;
    Object special_case_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,62);
    INIT_ARGS_nonrelocating();
    text_being_edited = REQUIRED_ARG_nonrelocating();
    special_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return search_incrementally_for_text_in_editor(text_being_edited,
	    special_case_qm,Kbackward);
}

static Object Qend_editing;        /* end-editing */

/* SEARCH-INCREMENTALLY-FOR-TEXT-IN-EDITOR */
Object search_incrementally_for_text_in_editor(text_being_edited,
	    special_case_qm,direction)
    Object text_being_edited, special_case_qm, direction;
{
    volatile Object text_line;
    Object line_length, superior_edit_state, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(126,63);
    SAVE_STACK();
    text_line = Qunbound_in_protected_let;
    line_length = Qunbound_in_protected_let;
    superior_edit_state = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	text_line = convert_text_to_text_string(1,text_being_edited);
	line_length = text_string_length(text_line);
	temp = ISVREF(Current_workstation,(SI_Long)17L);
	superior_edit_state = ISVREF(SECOND(temp),(SI_Long)2L);
	if (EQ(special_case_qm,Qend_editing)) {
	    temp = Type_of_current_workstation_context;
	    SAVE_VALUES(return_from_current_workstation_context(2,temp,
		    first_text_region_in_edit_state(superior_edit_state)));
	}
	else if (EQ(special_case_qm,Qrubout_on_blank_text)) {
	    if (IFIX(line_length) == (SI_Long)0L)
		SAVE_VALUES(return_from_current_workstation_context(1,
			Type_of_current_workstation_context));
	    else {
		move_or_delete_from_cursor(3,T,T,Nil);
		SAVE_VALUES(erase_any_temporary_information_on_edit_workspace(2,
			Nil,T));
	    }
	}
	else if (IFIX(line_length) > (SI_Long)0L) {
	    erase_any_temporary_information_on_edit_workspace(2,Nil,T);
	    find_search_string_in_superior_editor(3,superior_edit_state,
		    Nil,direction);
	    SAVE_VALUES(shrink_wrap_workspace(Current_edit_workspace));
	}
	else {
	    erase_any_temporary_information_on_edit_workspace(2,Nil,T);
	    delete_any_text_regions(6,ISVREF(superior_edit_state,
		    (SI_Long)13L),Nil,Nil,Nil,Nil,
		    ISVREF(superior_edit_state,(SI_Long)46L));
	    SAVE_VALUES(VALUES_1(Nil));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (text_line) {
	if ( !EQ(text_line,Qunbound_in_protected_let))
	    reclaim_text_string(text_line);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_13;  /* "no match" */

/* FIND-SEARCH-STRING-IN-SUPERIOR-EDITOR */
Object find_search_string_in_superior_editor varargs_1(int, n)
{
    Object superior_edit_state_qm, ongoing_region_qm, direction_qm;
    Object reversal_of_direction_qm, superior_edit_state, temp, direction;
    Object text_string, previous_region_qm, extension_sl_contraction_qm;
    Object line_index, character_index, start_line_index_qm;
    Object start_character_index, end_line_index, end_character_index, temp_1;
    Object image_plane, frame_transform, ab_loop_list_, ab_loop_desetq_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,64);
    INIT_ARGS_nonrelocating();
    superior_edit_state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    ongoing_region_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    reversal_of_direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    superior_edit_state = superior_edit_state_qm;
    if (superior_edit_state);
    else {
	temp = ISVREF(Current_workstation,(SI_Long)17L);
	superior_edit_state = ISVREF(SECOND(temp),(SI_Long)2L);
    }
    direction = direction_qm;
    if (direction);
    else
	direction = Kforward;
    text_string = convert_text_to_text_string(1,ISVREF(Current_edit_state,
	    (SI_Long)15L));
    previous_region_qm = ongoing_region_qm;
    if (previous_region_qm);
    else
	previous_region_qm = 
		first_text_region_in_edit_state(superior_edit_state);
    if (ongoing_region_qm) {
	temp = lengthw(text_string);
	extension_sl_contraction_qm =  !FIXNUM_EQ(temp,
		length_of_text_in_region(ongoing_region_qm)) ? T : Nil;
    }
    else if (reversal_of_direction_qm)
	extension_sl_contraction_qm = Nil;
    else
	extension_sl_contraction_qm = T;
    if (ongoing_region_qm)
	line_index = ISVREF(ongoing_region_qm,(SI_Long)18L);
    else {
	line_index = ISVREF(superior_edit_state,(SI_Long)87L);
	if (line_index);
	else
	    line_index = ISVREF(superior_edit_state,(SI_Long)24L);
    }
    if (ongoing_region_qm)
	character_index = ISVREF(ongoing_region_qm,(SI_Long)19L);
    else {
	character_index = ISVREF(superior_edit_state,(SI_Long)88L);
	if (character_index);
	else
	    character_index = ISVREF(superior_edit_state,(SI_Long)25L);
    }
    if (EQ(direction,Kforward))
	result = find_string_in_text(10,text_string,
		ISVREF(superior_edit_state,(SI_Long)15L),Nil,Nil,Nil,Nil,
		Nil,Nil,line_index,character_index);
    else if (EQ(direction,Kbackward))
	result = find_string_in_text_prior_to_bounds(4,text_string,
		ISVREF(superior_edit_state,(SI_Long)15L),line_index,
		character_index);
    else
	result = VALUES_1(Qnil);
    MVS_4(result,start_line_index_qm,start_character_index,end_line_index,
	    end_character_index);
    reclaim_text_string(text_string);
    if (start_line_index_qm) {
	if (extension_sl_contraction_qm) {
	    if (previous_region_qm) {
		if (FIXNUM_EQ(line_index,start_line_index_qm) && 
			FIXNUM_EQ(character_index,start_character_index))
		    update_text_region(3,previous_region_qm,end_line_index,
			    end_character_index);
		else {
		    delete_frame(previous_region_qm);
		    if ( !EQ(direction,Kforward)) {
			temp_1 = start_line_index_qm;
			start_line_index_qm = end_line_index;
			end_line_index = temp_1;
			temp_1 = start_character_index;
			start_character_index = end_character_index;
			end_character_index = temp_1;
		    }
		    make_text_region(6,ISVREF(superior_edit_state,
			    (SI_Long)13L),Nil,start_line_index_qm,
			    start_character_index,end_line_index,
			    end_character_index);
		}
	    }
	    else
		make_text_region(6,ISVREF(superior_edit_state,
			(SI_Long)13L),Nil,start_line_index_qm,
			start_character_index,end_line_index,
			end_character_index);
	}
	else {
	    if (previous_region_qm)
		delete_frame(previous_region_qm);
	    if ( !EQ(direction,Kforward)) {
		temp_1 = start_line_index_qm;
		start_line_index_qm = end_line_index;
		end_line_index = temp_1;
		temp_1 = start_character_index;
		start_character_index = end_character_index;
		end_character_index = temp_1;
	    }
	    make_text_region(6,ISVREF(superior_edit_state,(SI_Long)13L),
		    Nil,start_line_index_qm,start_character_index,
		    end_line_index,end_character_index);
	}
	if (ongoing_region_qm) {
	    SVREF(superior_edit_state,FIX((SI_Long)87L)) = start_line_index_qm;
	    SVREF(superior_edit_state,FIX((SI_Long)88L)) = 
		    start_character_index;
	}
    }
    else if (previous_region_qm)
	display_editor_notification_1(tformat_text_string(1,
		string_constant_13));
    else
	display_editor_notification_1(tformat_text_string(1,
		string_constant_13));
    if (start_line_index_qm) {
	image_plane = Nil;
	frame_transform = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(ISVREF(superior_edit_state,
		(SI_Long)13L),Qframe_transforms_of_block,Nil);
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	image_plane = CAR(ab_loop_desetq_);
	frame_transform = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	scroll_text_into_view(frame_transform,end_line_index,
		end_character_index);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FIRST-TEXT-REGION-IN-EDIT-STATE */
Object first_text_region_in_edit_state(edit_state)
    Object edit_state;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,65);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(edit_state,(SI_Long)13L),
	    (SI_Long)14L));
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
    superior_class_bit_number = IFIX(ISVREF(Text_region_class_description,
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
    if (temp ?  !EQ(subblock,ISVREF(edit_state,(SI_Long)46L)) : TRUEP(Nil)) {
	temp_1 = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* FIND-NEXT-INSTANCE-OF-SEARCH-STRING */
Object find_next_instance_of_search_string varargs_1(int, n)
{
    Object direction_qm, direction, temp, superior_edit_state, region_qm;
    Object this_is_a_reversal_of_the_ongoing_direction_qm, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,66);
    INIT_ARGS_nonrelocating();
    direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    direction = direction_qm;
    if (direction);
    else
	direction =  !TRUEP(ISVREF(Current_edit_state,(SI_Long)23L)) || 
		EQ(ISVREF(Current_edit_state,(SI_Long)23L),
		Qsearch_forward_incrementally_for_text_in_editor) ? 
		Kforward : Kbackward;
    temp = ISVREF(Current_workstation,(SI_Long)17L);
    superior_edit_state = ISVREF(SECOND(temp),(SI_Long)2L);
    region_qm = first_text_region_in_edit_state(superior_edit_state);
    this_is_a_reversal_of_the_ongoing_direction_qm = Nil;
    erase_any_temporary_information_on_edit_workspace(2,Nil,T);
    if (region_qm) {
	if ( !(EQ(direction,Kforward) ? 
		TRUEP(text_region_oriented_forward_p(region_qm)) : 
		TRUEP(text_region_oriented_backward_p(region_qm)))) {
	    this_is_a_reversal_of_the_ongoing_direction_qm = T;
	    reverse_text_region(region_qm);
	}
	svref_new_value = ISVREF(region_qm,(SI_Long)16L);
	SVREF(superior_edit_state,FIX((SI_Long)87L)) = svref_new_value;
	svref_new_value = ISVREF(region_qm,(SI_Long)17L);
	SVREF(superior_edit_state,FIX((SI_Long)88L)) = svref_new_value;
    }
    if (this_is_a_reversal_of_the_ongoing_direction_qm)
	return find_search_string_in_superior_editor(4,superior_edit_state,
		Nil,direction,T);
    else {
	temp = text_empty_p(ISVREF(Current_edit_state,(SI_Long)15L));
	if (temp)
	    return VALUES_1(temp);
	else
	    return find_search_string_in_superior_editor(3,
		    superior_edit_state,region_qm,direction);
    }
}

static Object Qno_room;            /* no-room */

/* FIND-STRING-IN-TEXT-PRIOR-TO-BOUNDS */
Object find_string_in_text_prior_to_bounds varargs_1(int, n)
{
    Object string_1, text, stop_line_index, stop_character_index;
    Object case_sensitive_qm, length_of_string;
    Object character_index_for_search_start, line_index_for_search_start;
    Object max_index_of_string, first_character_in_string;
    Object char_index_just_after_first_character_in_string;
    Object length_of_line_of_text, character_to_check, text_tail, line_of_text;
    Object temp, temp_1, code, text_element, text_tail_old_value;
    Object character_index, index_of_line_being_checked;
    Object line_of_text_being_checked, length_of_line_being_checked;
    Object ab_loop_iter_flag_, text_tail_qm, checking_text_element;
    Object text_tail_qm_old_value;
    SI_Long line_index, i, ab_loop_bind_, index_of_character_being_checked;
    SI_Long code_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,67);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    stop_line_index = REQUIRED_ARG_nonrelocating();
    stop_character_index = REQUIRED_ARG_nonrelocating();
    case_sensitive_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length_of_string = lengthw(string_1);
    result = calculate_rightmost_start_position_for_bounded_reverse_search(stop_character_index,
	    stop_line_index,text,length_of_string);
    MVS_2(result,character_index_for_search_start,line_index_for_search_start);
    if (EQ(character_index_for_search_start,Qno_room))
	return VALUES_1(Nil);
    else {
	max_index_of_string = sub1(length_of_string);
	first_character_in_string = Nil;
	char_index_just_after_first_character_in_string = Nil;
	length_of_line_of_text = Nil;
	character_to_check = Nil;
	line_index = IFIX(line_index_for_search_start);
	text_tail = Nil;
	line_of_text = Nil;
	temp = FIX(UBYTE_16_ISAREF_1(string_1,(SI_Long)0L));
	temp_1 = FIX((SI_Long)0L + (SI_Long)1L);
	first_character_in_string = temp;
	char_index_just_after_first_character_in_string = temp_1;
	if ( !TRUEP(case_sensitive_qm)) {
	    code = first_character_in_string;
	    if (IFIX(code) < (SI_Long)127L)
		first_character_in_string = (SI_Long)65L <= IFIX(code) && 
			IFIX(code) <= (SI_Long)90L ? FIX(IFIX(code) + 
			(SI_Long)32L) : code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
		first_character_in_string = temp;
	    }
	}
      next_loop:
	if (line_index <= (SI_Long)0L)
	    goto end_loop;
	text_tail = find_text_tail_for_line(text,FIX(line_index));
	text_element = Nil;
      next_loop_1:
	text_tail_old_value = text_tail;
	temp = FIRST(text_tail_old_value);
	text_tail = REST(text_tail_old_value);
	text_element = temp;
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	    length_of_line_of_text = text_string_length(text_element);
	    line_of_text = text_element;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	line_of_text = Qnil;
      end_1:;
	character_index = line_index == IFIX(stop_line_index) ? 
		character_index_for_search_start : length_of_line_of_text;
      next_loop_2:
	temp = FIX((SI_Long)0L);
	if ( !NUM_GE(character_index,temp))
	    goto end_loop_2;
	character_to_check = FIX(UBYTE_16_ISAREF_1(line_of_text,
		IFIX(character_index)));
	if ( !TRUEP(case_sensitive_qm)) {
	    code = character_to_check;
	    if (IFIX(code) < (SI_Long)127L)
		character_to_check = (SI_Long)65L <= IFIX(code) && 
			IFIX(code) <= (SI_Long)90L ? FIX(IFIX(code) + 
			(SI_Long)32L) : code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
		character_to_check = temp;
	    }
	}
	if (FIXNUM_EQ(character_to_check,first_character_in_string)) {
	    if (IFIX(length_of_string) == (SI_Long)1L) {
		temp = FIXNUM_ADD1(character_index);
		return VALUES_4(FIX(line_index),character_index,
			FIX(line_index),temp);
	    }
	    index_of_line_being_checked = FIX(line_index);
	    line_of_text_being_checked = line_of_text;
	    length_of_line_being_checked = length_of_line_of_text;
	    i = IFIX(char_index_just_after_first_character_in_string);
	    ab_loop_bind_ = IFIX(length_of_string);
	    index_of_character_being_checked = IFIX(add1(character_index));
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if (i > ab_loop_bind_)
		goto end_loop_3;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_of_character_being_checked = 
			index_of_character_being_checked + (SI_Long)1L;
	    if (index_of_character_being_checked == 
		    IFIX(length_of_line_being_checked)) {
		index_of_line_being_checked = 
			add1(index_of_line_being_checked);
		text_tail_qm = find_text_tail_for_line(text,
			index_of_line_being_checked);
		if ( !TRUEP(text_tail_qm))
		    goto end_loop_3;
		index_of_character_being_checked = (SI_Long)0L;
		checking_text_element = Nil;
	      next_loop_4:
		text_tail_qm_old_value = text_tail_qm;
		temp = FIRST(text_tail_qm_old_value);
		text_tail_qm = REST(text_tail_qm_old_value);
		checking_text_element = temp;
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(checking_text_element) 
			!= (SI_Long)0L) {
		    length_of_line_being_checked = 
			    lengthw(checking_text_element);
		    line_of_text_being_checked = checking_text_element;
		    goto end_2;
		}
		goto next_loop_4;
	      end_loop_4:
		line_of_text_being_checked = Qnil;
	      end_2:;
	    }
	    if (case_sensitive_qm)
		temp_2 = UBYTE_16_ISAREF_1(string_1,i) == 
			UBYTE_16_ISAREF_1(line_of_text_being_checked,
			index_of_character_being_checked);
	    else {
		code_1 = UBYTE_16_ISAREF_1(string_1,i);
		if (code_1 < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code_1 && code_1 <= 
			    (SI_Long)90L ? FIX(code_1 + (SI_Long)32L) : 
			    FIX(code_1);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code_1));
		    if (temp_1);
		    else
			temp_1 = FIX(code_1);
		}
		code_1 = UBYTE_16_ISAREF_1(line_of_text_being_checked,
			index_of_character_being_checked);
		if (code_1 < (SI_Long)127L)
		    temp = (SI_Long)65L <= code_1 && code_1 <= 
			    (SI_Long)90L ? FIX(code_1 + (SI_Long)32L) : 
			    FIX(code_1);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code_1));
		    if (temp);
		    else
			temp = FIX(code_1);
		}
		temp_2 = NUM_EQ(temp_1,temp);
	    }
	    if ( !temp_2)
		goto end_3;
	    if (i == IFIX(max_index_of_string))
		return VALUES_4(FIX(line_index),character_index,
			index_of_line_being_checked,
			FIX(index_of_character_being_checked + (SI_Long)1L));
	    ab_loop_iter_flag_ = Nil;
	    i = i + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    goto end_3;
	  end_3:;
	}
	character_index = FIXNUM_SUB1(character_index);
	goto next_loop_2;
      end_loop_2:;
	line_index = line_index - (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* CALCULATE-RIGHTMOST-START-POSITION-FOR-BOUNDED-REVERSE-SEARCH */
Object calculate_rightmost_start_position_for_bounded_reverse_search(stop_character_index,
	    stop_line_index,text,length_of_string)
    Object stop_character_index, stop_line_index, text, length_of_string;
{
    Object spill_over, prior_text_tail, text_element;
    Object prior_text_tail_old_value, temp, length_of_prior_line, temp_1;

    x_note_fn_call(126,68);
    if (NUM_GT(length_of_string,stop_character_index)) {
	if ((SI_Long)1L == IFIX(stop_line_index))
	    return VALUES_2(Qno_room,Nil);
	else {
	    spill_over = FIXNUM_MINUS(length_of_string,
		    FIXNUM_SUB1(stop_character_index));
	    prior_text_tail = find_text_tail_for_line(text,
		    FIXNUM_SUB1(stop_line_index));
	    text_element = Nil;
	  next_loop:
	    prior_text_tail_old_value = prior_text_tail;
	    temp = FIRST(prior_text_tail_old_value);
	    prior_text_tail = REST(prior_text_tail_old_value);
	    text_element = temp;
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != 
			(SI_Long)0L) {
		length_of_prior_line = text_string_length(text_element);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    length_of_prior_line = Qnil;
	  end_1:;
	    temp_1 = FIXNUM_MINUS(length_of_prior_line,spill_over);
	    temp = FIXNUM_SUB1(stop_line_index);
	    return VALUES_2(temp_1,temp);
	}
    }
    else {
	temp = FIXNUM_MINUS(stop_character_index,length_of_string);
	return VALUES_2(temp,stop_line_index);
    }
}

static Object Qfree;               /* free */

static Object Qfree_text_attribute;  /* free-text-attribute */

static Object Qtext;               /* text */

static Object Qediting;            /* editing */

/* PARSE-TEXT-FOR-SLOT */
Object parse_text_for_slot varargs_1(int, n)
{
    Object text, frame, slot_description;
    Object runtime_change_qm, type_of_slot_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, make_reason_for_failure_p;
    Object type_of_slot, temp, do_not_note_permanent_changes_p;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, current_workstation_context;
    Object type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Object keep_edit_workspace_hidden_no_matter_what_qm, current_edit_state;
    Object current_edit_workspace, svref_arg_1, editing_context;
    Object note_as_kb_state_change_qm, edit_state_qm, reason_for_failure_qm;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(15);
    Object result;

    x_note_fn_call(126,69);
    INIT_ARGS_nonrelocating();
    text = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_description = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    runtime_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    type_of_slot_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    make_reason_for_failure_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    type_of_slot = type_of_slot_qm;
    if (type_of_slot);
    else
	type_of_slot = assq_function(Qtype,ISVREF(slot_description,
		(SI_Long)9L));
    if ((EQ(CADR(type_of_slot),Qfree) || EQ(CADR(type_of_slot),
	    Qfree_text_attribute)) && memq_function(Qtext,
		CDDR(type_of_slot))) {
	temp = Do_not_note_permanent_changes_p;
	if (temp);
	else
	    temp = runtime_change_qm;
	do_not_note_permanent_changes_p = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		0);
	  if (runtime_change_qm)
	      note_kb_state_change_to_slot_by_saving_text(frame,
		      slot_description);
	  result = change_slot_description_value_function(frame,
		  slot_description,slot_value_cons_1(No_value,text),Nil,Nil);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = Servicing_workstation_qm ? Current_workstation : Nil;
	    if (temp);
	    else {
		temp = last(Workstations_in_service,_);
		temp = CAR(temp);
	    }
	    current_workstation_1 = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    14);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      13);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			12);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  11);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    10);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      9);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				8);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  7);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    6);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      5);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					4);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  3);
				    keep_edit_workspace_hidden_no_matter_what_qm 
					    = T;
				    PUSH_SPECIAL_WITH_SYMBOL(Keep_edit_workspace_hidden_no_matter_what_qm,Qkeep_edit_workspace_hidden_no_matter_what_qm,keep_edit_workspace_hidden_no_matter_what_qm,
					    2);
				      enter_editing_context(21,frame,
					      denote_slot_using_slot_value_conses(slot_description,
					      ISVREF(frame,(SI_Long)1L)),
					      text,T,Nil,Nil,Nil,Nil,Nil,
					      Nil,Nil,Nil,Nil,Nil,Nil,Nil,
					      Nil,T,T,
					      slot_component_name_qm,
					      slot_component_indicator_qm);
				      current_edit_state = 
					      Specific_structure_for_current_workstation_context;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
					      1);
					current_edit_workspace = 
						ISVREF(Current_edit_state,
						(SI_Long)12L);
					PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
						0);
					  svref_arg_1 = Current_edit_state;
					  SVREF(svref_arg_1,
						  FIX((SI_Long)57L)) = 
						  runtime_change_qm;
					POP_SPECIAL();
				      POP_SPECIAL();
				      editing_context = 
					      Current_workstation_context;
				      PUSH_SPECIAL_WITH_SYMBOL(Editing_context,Qediting_context,editing_context,
					      1);
					temp = runtime_change_qm;
					if (temp);
					else
					    temp = Note_as_kb_state_change_qm;
					note_as_kb_state_change_qm = temp;
					PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
						0);
					  finish_parsing_insofar_as_possible();
					  if (EQ(Current_workstation_context,
						  Editing_context)) {
					      edit_state_qm = 
						      ISVREF(Editing_context,
						      (SI_Long)2L);
					      reason_for_failure_qm = 
						      make_reason_for_failure_p 
						      && edit_state_qm ? 
						      generate_reason_for_parsing_failure(edit_state_qm) 
						      : Qnil;
					      return_from_current_workstation_context(1,
						      Qediting);
					      SAVE_VALUES(VALUES_2(Nil,
						      reason_for_failure_qm));
					  }
					  else
					      SAVE_VALUES(VALUES_1(T));
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
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

static Object string_constant_14;  /* "An error, \"~a\", was reported at line ~d, \"~a\"" */

static Object string_constant_15;  /* "An error, \"~a\", was reported." */

/* GENERATE-REASON-FOR-PARSING-FAILURE */
Object generate_reason_for_parsing_failure(edit_state)
    Object edit_state;
{
    Object temp, reason_for_bad_parse_qm, line_index_qm, location_string_qm;

    x_note_fn_call(126,70);
    temp = ISVREF(edit_state,(SI_Long)42L);
    if (temp);
    else {
	temp = gensym_list_4(Nil,Nil,Nil,Nil);
	SVREF(edit_state,FIX((SI_Long)42L)) = temp;
    }
    reason_for_bad_parse_qm = CADDDR(temp);
    if (reason_for_bad_parse_qm) {
	temp = ISVREF(edit_state,(SI_Long)42L);
	if (temp);
	else {
	    temp = gensym_list_4(Nil,Nil,Nil,Nil);
	    SVREF(edit_state,FIX((SI_Long)42L)) = temp;
	}
	line_index_qm = CADR(temp);
	location_string_qm = line_index_qm ? 
		get_next_text_line(find_text_tail_for_line(ISVREF(edit_state,
		(SI_Long)15L),line_index_qm)) : Qnil;
	if (location_string_qm) {
	    temp = ISVREF(edit_state,(SI_Long)42L);
	    if (temp);
	    else {
		temp = gensym_list_4(Nil,Nil,Nil,Nil);
		SVREF(edit_state,FIX((SI_Long)42L)) = temp;
	    }
	    return tformat_text_string(4,string_constant_14,
		    reason_for_bad_parse_qm,CADR(temp),location_string_qm);
	}
	else
	    return tformat_text_string(2,string_constant_15,
		    reason_for_bad_parse_qm);
    }
    else
	return VALUES_1(Nil);
}

/* CHANGE-THE-TEXT-OF */
Object change_the_text_of varargs_1(int, n)
{
    Object frame, slot_name, text_string;
    Object class_qualifier_qm, runtime_change_qm, type_of_slot_qm;
    Object slot_component_name_qm, slot_component_indicator_qm;
    Object make_reason_for_failure_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,71);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    runtime_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    type_of_slot_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    make_reason_for_failure_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = convert_text_string_to_text(text_string);
    return parse_text_for_slot(8,temp,frame,
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(frame,(SI_Long)1L),class_qualifier_qm),
	    runtime_change_qm,type_of_slot_qm,slot_component_name_qm,
	    slot_component_indicator_qm,make_reason_for_failure_p);
}

/* RECOMPILE-ITEM */
Object recompile_item(frame)
    Object frame;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(126,72);
    SAVE_STACK();
    if (Servicing_workstation_qm) {
	result = recompile_item_1(frame);
	RESTORE_STACK();
	return result;
    }
    else {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = CAR(Workstations_in_service);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    SAVE_VALUES(recompile_item_1(frame));
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
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

static Object Qformula_qm;         /* formula? */

static Object Qprocedure_definition;  /* procedure-definition */

static Object Qnupec_extra_actions;  /* nupec-extra-actions */

static Object Qtranslation_and_text_of_embedded_rule;  /* translation-and-text-of-embedded-rule */

static Object Qcondition_for_using_user_menu_choice_qm;  /* condition-for-using-user-menu-choice? */

static Object Qaction_for_user_menu_choice_qm;  /* action-for-user-menu-choice? */

static Object Qtrend_chart;        /* trend-chart */

static Object Qtrend_chart_plots;  /* trend-chart-plots */

static Object Qexpressions_to_display;  /* expressions-to-display */

static Object Qsimulation_formulas_qm;  /* simulation-formulas? */

static Object Qtokenizer;          /* tokenizer */

static Object Qpatterns_definition;  /* patterns-definition */

static Object Qtokens_definition;  /* tokens-definition */

/* RECOMPILE-ITEM-1 */
Object recompile_item_1(frame)
    Object frame;
{
    Object in_recompile_item_p, gensymed_symbol, sub_class_bit_vector, code;
    Object gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,73);
    in_recompile_item_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_recompile_item_p,Qin_recompile_item_p,in_recompile_item_p,
	    0);
      gensymed_symbol = ISVREF(frame,(SI_Long)1L);
      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Item_list_class_description,
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
      if (temp)
	  result = VALUES_1(Nil);
      else {
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	  if (temp)
	      result = recompile_slot_of_frame_1(2,frame,Qformula_qm);
	  else {
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  result = recompile_slot_of_frame_1(2,frame,
			  Qprocedure_definition);
	      else {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      if ( !TRUEP(embedded_rule_p(frame))) {
			  recompile_slot_of_frame_1(2,frame,
				  Qbox_translation_and_text);
			  code = M_CAR(M_CDR(Journal_shutout_scan_p));
			  if (FIXNUMP(code) && (IFIX(code) & 
				  (SI_Long)256L) != (SI_Long)0L ? 
				  TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) 
				  : TRUEP(Nil))
			      result = recompile_slot_of_frame_1(2,frame,
				      Qnupec_extra_actions);
			  else
			      result = VALUES_1(Nil);
		      }
		      else
			  result = VALUES_1(Nil);
		  }
		  else {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Action_button_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
		      if (temp)
			  result = recompile_slot_of_frame_1(2,frame,
				  Qtranslation_and_text_of_embedded_rule);
		      else {
			  sub_class_bit_vector = ISVREF(gensymed_symbol,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(User_menu_choice_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol_1 = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_2 = (SI_Long)1L;
			      gensymed_symbol_3 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_2 = gensymed_symbol_2 << 
				      gensymed_symbol_3;
			      gensymed_symbol_1 = gensymed_symbol_1 & 
				      gensymed_symbol_2;
			      temp = (SI_Long)0L < gensymed_symbol_1;
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp) {
			      recompile_slot_of_frame_1(2,frame,
				      Qcondition_for_using_user_menu_choice_qm);
			      result = recompile_slot_of_frame_1(2,frame,
				      Qaction_for_user_menu_choice_qm);
			  }
			  else {
			      gensymed_symbol_4 = 
				      lookup_global_or_kb_specific_property_value(Qtrend_chart,
				      Class_description_gkbprop);
			      if (gensymed_symbol_4) {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(gensymed_symbol_4,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
				  if (sub_class_vector_index < 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					      {
				      gensymed_symbol_1 = 
					      UBYTE_8_ISAREF_1(sub_class_bit_vector,
					      sub_class_vector_index);
				      gensymed_symbol_2 = (SI_Long)1L;
				      gensymed_symbol_3 = 
					      superior_class_bit_number & 
					      (SI_Long)7L;
				      gensymed_symbol_2 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_3;
				      gensymed_symbol_1 = 
					      gensymed_symbol_1 & 
					      gensymed_symbol_2;
				      temp = (SI_Long)0L < gensymed_symbol_1;
				  }
				  else
				      temp = TRUEP(Nil);
			      }
			      else
				  temp = TRUEP(Nil);
			      if (temp)
				  result = recompile_slot_of_frame_1(2,
					  frame,Qtrend_chart_plots);
			      else {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(Readout_table_class_description,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
				  if (sub_class_vector_index < 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					      {
				      gensymed_symbol_1 = 
					      UBYTE_8_ISAREF_1(sub_class_bit_vector,
					      sub_class_vector_index);
				      gensymed_symbol_2 = (SI_Long)1L;
				      gensymed_symbol_3 = 
					      superior_class_bit_number & 
					      (SI_Long)7L;
				      gensymed_symbol_2 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_3;
				      gensymed_symbol_1 = 
					      gensymed_symbol_1 & 
					      gensymed_symbol_2;
				      temp = (SI_Long)0L < gensymed_symbol_1;
				  }
				  else
				      temp = TRUEP(Nil);
				  if (temp);
				  else {
				      sub_class_bit_vector = 
					      ISVREF(gensymed_symbol,
					      (SI_Long)19L);
				      superior_class_bit_number = 
					      IFIX(ISVREF(Dial_class_description,
					      (SI_Long)18L));
				      sub_class_vector_index = 
					      superior_class_bit_number >> 
					       -  - (SI_Long)3L;
				      if (sub_class_vector_index < 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						  {
					  gensymed_symbol_1 = 
						  UBYTE_8_ISAREF_1(sub_class_bit_vector,
						  sub_class_vector_index);
					  gensymed_symbol_2 = (SI_Long)1L;
					  gensymed_symbol_3 = 
						  superior_class_bit_number 
						  & (SI_Long)7L;
					  gensymed_symbol_2 = 
						  gensymed_symbol_2 << 
						  gensymed_symbol_3;
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 & 
						  gensymed_symbol_2;
					  temp = (SI_Long)0L < 
						  gensymed_symbol_1;
				      }
				      else
					  temp = TRUEP(Nil);
				  }
				  if (temp);
				  else {
				      sub_class_bit_vector = 
					      ISVREF(gensymed_symbol,
					      (SI_Long)19L);
				      superior_class_bit_number = 
					      IFIX(ISVREF(Meter_class_description,
					      (SI_Long)18L));
				      sub_class_vector_index = 
					      superior_class_bit_number >> 
					       -  - (SI_Long)3L;
				      if (sub_class_vector_index < 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						  {
					  gensymed_symbol_1 = 
						  UBYTE_8_ISAREF_1(sub_class_bit_vector,
						  sub_class_vector_index);
					  gensymed_symbol_2 = (SI_Long)1L;
					  gensymed_symbol_3 = 
						  superior_class_bit_number 
						  & (SI_Long)7L;
					  gensymed_symbol_2 = 
						  gensymed_symbol_2 << 
						  gensymed_symbol_3;
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 & 
						  gensymed_symbol_2;
					  temp = (SI_Long)0L < 
						  gensymed_symbol_1;
				      }
				      else
					  temp = TRUEP(Nil);
				  }
				  if (temp)
				      result = recompile_slot_of_frame_1(2,
					      frame,Qexpressions_to_display);
				  else {
				      sub_class_bit_vector = 
					      ISVREF(gensymed_symbol,
					      (SI_Long)19L);
				      superior_class_bit_number = 
					      IFIX(ISVREF(Simulation_subtable_class_description,
					      (SI_Long)18L));
				      sub_class_vector_index = 
					      superior_class_bit_number >> 
					       -  - (SI_Long)3L;
				      if (sub_class_vector_index < 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						  {
					  gensymed_symbol_1 = 
						  UBYTE_8_ISAREF_1(sub_class_bit_vector,
						  sub_class_vector_index);
					  gensymed_symbol_2 = (SI_Long)1L;
					  gensymed_symbol_3 = 
						  superior_class_bit_number 
						  & (SI_Long)7L;
					  gensymed_symbol_2 = 
						  gensymed_symbol_2 << 
						  gensymed_symbol_3;
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 & 
						  gensymed_symbol_2;
					  temp = (SI_Long)0L < 
						  gensymed_symbol_1;
				      }
				      else
					  temp = TRUEP(Nil);
				      if (temp)
					  result = recompile_slot_of_frame_1(2,
						  frame,
						  Qsimulation_formulas_qm);
				      else {
					  sub_class_bit_vector = 
						  ISVREF(gensymed_symbol,
						  (SI_Long)19L);
					  superior_class_bit_number = 
						  IFIX(ISVREF(Statement_class_description,
						  (SI_Long)18L));
					  sub_class_vector_index = 
						  superior_class_bit_number 
						  >>  -  - (SI_Long)3L;
					  if (sub_class_vector_index < 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						      {
					      gensymed_symbol_1 = 
						      UBYTE_8_ISAREF_1(sub_class_bit_vector,
						      sub_class_vector_index);
					      gensymed_symbol_2 = (SI_Long)1L;
					      gensymed_symbol_3 = 
						      superior_class_bit_number 
						      & (SI_Long)7L;
					      gensymed_symbol_2 = 
						      gensymed_symbol_2 << 
						      gensymed_symbol_3;
					      gensymed_symbol_1 = 
						      gensymed_symbol_1 & 
						      gensymed_symbol_2;
					      temp = (SI_Long)0L < 
						      gensymed_symbol_1;
					  }
					  else
					      temp = TRUEP(Nil);
					  if (temp)
					      result = recompile_slot_of_frame_1(2,
						      frame,
						      Qbox_translation_and_text);
					  else {
					      gensymed_symbol_4 = 
						      lookup_global_or_kb_specific_property_value(Qtokenizer,
						      Class_description_gkbprop);
					      if (gensymed_symbol_4) {
						  sub_class_bit_vector = 
							  ISVREF(gensymed_symbol,
							  (SI_Long)19L);
						  superior_class_bit_number 
							  = 
							  IFIX(ISVREF(gensymed_symbol_4,
							  (SI_Long)18L));
						  sub_class_vector_index = 
							  superior_class_bit_number 
							  >>  -  - (SI_Long)3L;
						  if (sub_class_vector_index 
							  < 
							  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							      {
						      gensymed_symbol_1 = 
							      UBYTE_8_ISAREF_1(sub_class_bit_vector,
							      sub_class_vector_index);
						      gensymed_symbol_2 = 
							      (SI_Long)1L;
						      gensymed_symbol_3 = 
							      superior_class_bit_number 
							      & (SI_Long)7L;
						      gensymed_symbol_2 = 
							      gensymed_symbol_2 
							      << 
							      gensymed_symbol_3;
						      gensymed_symbol_1 = 
							      gensymed_symbol_1 
							      & 
							      gensymed_symbol_2;
						      temp = (SI_Long)0L < 
							      gensymed_symbol_1;
						  }
						  else
						      temp = TRUEP(Nil);
					      }
					      else
						  temp = TRUEP(Nil);
					      if (temp) {
						  if ( 
							  !TRUEP(recompile_slot_of_frame_1(2,
							  frame,
							  Qpatterns_definition)))
						      result = recompile_slot_of_frame_1(2,
							      frame,
							      Qtokens_definition);
						  else
						      result = VALUES_1(Nil);
					      }
					      else {
						  gensymed_symbol_4 = 
							  lookup_global_or_kb_specific_property_value(Qnew_table,
							  Class_description_gkbprop);
						  if (gensymed_symbol_4) {
						      sub_class_bit_vector 
							      = 
							      ISVREF(gensymed_symbol,
							      (SI_Long)19L);
						      superior_class_bit_number 
							      = 
							      IFIX(ISVREF(gensymed_symbol_4,
							      (SI_Long)18L));
						      sub_class_vector_index 
							      = 
							      superior_class_bit_number 
							      >>  -  - 
							      (SI_Long)3L;
						      if (sub_class_vector_index 
							      < 
							      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								  {
							  gensymed_symbol_1 
								  = 
								  UBYTE_8_ISAREF_1(sub_class_bit_vector,
								  sub_class_vector_index);
							  gensymed_symbol_2 
								  = 
								  (SI_Long)1L;
							  gensymed_symbol_3 
								  = 
								  superior_class_bit_number 
								  & 
								  (SI_Long)7L;
							  gensymed_symbol_2 
								  = 
								  gensymed_symbol_2 
								  << 
								  gensymed_symbol_3;
							  gensymed_symbol_1 
								  = 
								  gensymed_symbol_1 
								  & 
								  gensymed_symbol_2;
							  temp = 
								  (SI_Long)0L 
								  < gensymed_symbol_1;
						      }
						      else
							  temp = TRUEP(Nil);
						  }
						  else
						      temp = TRUEP(Nil);
						  if (temp) {
						      recompile_cell_array(frame);
						      result = update_frame_status(frame,
							      Nil,Nil);
						  }
						  else
						      result = VALUES_1(Qnil);
					      }
					  }
				      }
				  }
			      }
			  }
		      }
		  }
	      }
	  }
      }
    POP_SPECIAL();
    return result;
}

/* RECOMPILE-SLOT-OF-FRAME-1 */
Object recompile_slot_of_frame_1 varargs_1(int, n)
{
    Object frame, slot_name_qm;
    Object class_qualifier_qm, slot_value_qm, temp_1, editing_context;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,74);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name_qm = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (slot_name_qm) {
	slot_value_qm = get_slot_value_function(frame,slot_name_qm,
		class_qualifier_qm);
	temp = slot_value_qm && CONSP(slot_value_qm) ?  
		!TRUEP(stripped_text_p(CDR(slot_value_qm))) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = 
		get_slot_description_of_class_description_function(slot_name_qm,
		ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
	enter_editing_context(4,frame,
		denote_slot_using_slot_value_conses(temp_1,ISVREF(frame,
		(SI_Long)1L)),Nil,T);
	editing_context = Current_workstation_context;
	PUSH_SPECIAL_WITH_SYMBOL(Editing_context,Qediting_context,editing_context,
		0);
	  finish_parsing_insofar_as_possible();
	  if (Keep_edit_workspace_hidden_no_matter_what_qm && 
		  EQ(Current_workstation_context,Editing_context))
	      result = return_from_current_workstation_context(1,Qediting);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qfull_editor;        /* full-editor */

static Object Qoption_buttons_for_edit_in_place;  /* option-buttons-for-edit-in-place */

static Object Qmenus_for_edit_in_place;  /* menus-for-edit-in-place */

static Object Qdo_not_clear_text_for_edit_in_place;  /* do-not-clear-text-for-edit-in-place */

/* ENTER-EDITING-CONTEXT-ON-TEXT-BOX */
Object enter_editing_context_on_text_box varargs_1(int, n)
{
    Object text_box, image_plane;
    Object x_in_window_qm, y_in_window_qm, cursor_line_index_qm;
    Object cursor_character_index_qm, type_of_slot_qm, full_editor_qm;
    Object buttons_visible_qm, menus_visible_qm, clear_before_edit_qm;
    Object initial_text_or_edit_box_qm;
    char in_place_editing_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,75);
    INIT_ARGS_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    y_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    type_of_slot_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    full_editor_qm = non_menu_choice_permitted_p(Qfull_editor,text_box);
    in_place_editing_qm =  !TRUEP(full_editor_qm);
    buttons_visible_qm = full_editor_qm;
    if (buttons_visible_qm);
    else
	buttons_visible_qm = 
		non_menu_choice_permitted_p(Qoption_buttons_for_edit_in_place,
		text_box);
    menus_visible_qm = 
	    non_menu_choice_permitted_p(Qmenus_for_edit_in_place,text_box);
    clear_before_edit_qm =  !TRUEP(full_editor_qm) ? ( 
	    !TRUEP(non_menu_choice_permitted_p(Qdo_not_clear_text_for_edit_in_place,
	    text_box)) ? T : Nil) : Qnil;
    initial_text_or_edit_box_qm = clear_before_edit_qm ? make_empty_text() 
	    : Nil;
    if (clear_before_edit_qm) {
	cursor_line_index_qm = Nil;
	cursor_character_index_qm = Nil;
    }
    else if (cursor_line_index_qm);
    else if (x_in_window_qm && y_in_window_qm) {
	result = find_position_in_text_given_image_plane(9,text_box,
		text_box,Nil,Nil,Nil,Nil,image_plane,x_in_window_qm,
		y_in_window_qm);
	MVS_2(result,cursor_line_index_qm,cursor_character_index_qm);
    }
    return enter_editing_context(19,text_box,Qbox_translation_and_text,
	    initial_text_or_edit_box_qm,Nil,Nil,Nil,cursor_line_index_qm,
	    cursor_character_index_qm,in_place_editing_qm ? image_plane : 
	    Nil,in_place_editing_qm ? text_box : Nil,Nil,Nil,Nil,Nil,
	    type_of_slot_qm,Nil,Nil, !TRUEP(buttons_visible_qm) ? T : Nil, 
	    !TRUEP(menus_visible_qm) ? T : Nil);
}

static Object Qab_font;            /* ab-font */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Ktight;              /* :tight */

static Object Qlost_spaces;        /* lost-spaces */

static Object Qleading;            /* leading */

/* FIND-POSITION-IN-TEXT */
Object find_position_in_text varargs_1(int, n)
{
    Object text_box_qm, text_cell_qm, left_edge_of_cell_qm;
    Object top_edge_of_cell_qm, look_in_lost_spaces_too_qm, x_in_workspace_qm;
    Object y_in_workspace_qm;
    Object line_index_qm, character_index_qm, only_if_in_text_qm;
    Object find_character_instead_of_position_between_qm, tab_width_qm;
    Object text_box_format, text_cell_plist, temp, gensymed_symbol, ab_font;
    Object x_magnification_qm, y_magnification_qm, x_in_text_qm, y_in_text_qm;
    Object baseline_to_baseline_distance, distance_to_next_baseline_from_top;
    Object word_spacing, word_spacing_for_next_line_qm, lost_spaces;
    Object line_index, indentation, text, above_bottom_of_line_qm;
    Object midline_x_from_left, ok_to_return_position_qm, lost_spaces_value_qm;
    Object l, text_element, line_width_a, line_width_b, line_length;
    Object width_of_initial_spaces_qm, i, preceding_i, unicode_wide_character;
    Object character_width, i_1, offset, incff_1_arg, a, b, tab_width;
    Object next_tab_position, indentation_offset_text_width, temp_2, temp_3;
    Object temp_4;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_text;
    SI_Long gensymed_symbol_3, top_edge_of_text;
    SI_Long distance_from_baseline_to_bottom_of_line, end_1, position_1;
    SI_Long gensymed_symbol_4, incff_1_arg_1, line_width_a_new_value;
    SI_Long indentation_offset;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,76);
    INIT_ARGS_nonrelocating();
    text_box_qm = REQUIRED_ARG_nonrelocating();
    text_cell_qm = REQUIRED_ARG_nonrelocating();
    left_edge_of_cell_qm = REQUIRED_ARG_nonrelocating();
    top_edge_of_cell_qm = REQUIRED_ARG_nonrelocating();
    look_in_lost_spaces_too_qm = REQUIRED_ARG_nonrelocating();
    x_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    y_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    only_if_in_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    find_character_instead_of_position_between_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    tab_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_box_format = text_box_qm ? ISVREF(text_box_qm,(SI_Long)17L) : 
	    CAR(text_cell_qm);
    text_cell_plist = text_box_qm ? ISVREF(text_box_qm,(SI_Long)18L) : 
	    CADR(text_cell_qm);
    temp = ISVREF(text_box_format,(SI_Long)22L);
    gensymed_symbol = CAR(temp);
    ab_font = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qab_font);
    if (text_box_qm) {
	gensymed_symbol = ISVREF(text_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    }
    else
	gensymed_symbol_1 = IFIX(left_edge_of_cell_qm);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)27L));
    left_edge_of_text = gensymed_symbol_1 + gensymed_symbol_2;
    if (text_box_qm) {
	gensymed_symbol = ISVREF(text_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    }
    else
	gensymed_symbol_1 = IFIX(top_edge_of_cell_qm);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)28L));
    temp = text_cell_plist ? getfq_function_no_default(text_cell_plist,
	    Qy_offset_for_text) : Nil;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(temp);
    top_edge_of_text = gensymed_symbol_1 + gensymed_symbol_2 + 
	    gensymed_symbol_3;
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
    x_in_text_qm = x_in_workspace_qm ? (x_magnification_qm ? 
	    inverse_magnify(FIX(IFIX(x_in_workspace_qm) - 
	    left_edge_of_text),x_magnification_qm) : 
	    FIX(IFIX(x_in_workspace_qm) - left_edge_of_text)) : Nil;
    y_in_text_qm = y_in_workspace_qm ? (y_magnification_qm ? 
	    inverse_magnify(FIX(IFIX(y_in_workspace_qm) - 
	    top_edge_of_text),y_magnification_qm) : 
	    FIX(IFIX(y_in_workspace_qm) - top_edge_of_text)) : Nil;
    baseline_to_baseline_distance = FIXNUM_ADD(ISVREF(text_box_format,
	    (SI_Long)31L),ISVREF(text_box_format,(SI_Long)33L));
    distance_from_baseline_to_bottom_of_line = EQ(only_if_in_text_qm,
	    Ktight) ? (SI_Long)2L : 
	    IFIX(FIXNUM_MINUS(ISVREF(text_box_format,(SI_Long)31L),
	    ISVREF(text_box_format,(SI_Long)32L))) + 
	    (IFIX(ISVREF(text_box_format,(SI_Long)33L)) >>  -  - (SI_Long)1L);
    distance_to_next_baseline_from_top = ISVREF(text_box_format,(SI_Long)32L);
    word_spacing = ISVREF(text_box_format,(SI_Long)34L);
    word_spacing_for_next_line_qm = Nil;
    lost_spaces = FIX((SI_Long)1L);
    line_index = FIX((SI_Long)1L);
    indentation = FIX((SI_Long)0L);
    if (text_box_qm) {
	temp = ISVREF(text_box_qm,(SI_Long)16L);
	text = CDR(temp);
    }
    else
	text = CDDDR(text_cell_qm);
    above_bottom_of_line_qm = Nil;
    midline_x_from_left = Nil;
    ok_to_return_position_qm = Nil;
    lost_spaces_value_qm = Nil;
    l = text;
    text_element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    text_element = CAR(l);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(text_element) != (SI_Long)0L) {
	above_bottom_of_line_qm = x_in_text_qm ? (IFIX(y_in_text_qm) <= 
		IFIX(distance_to_next_baseline_from_top) + 
		distance_from_baseline_to_bottom_of_line ? T : Nil) : Nil;
	if (x_in_text_qm) {
	    if (above_bottom_of_line_qm) {
		temp_1 =  !TRUEP(only_if_in_text_qm);
		if (temp_1);
		else
		    temp_1 = IFIX(line_index) > (SI_Long)1L;
		if (temp_1);
		else {
		    gensymed_symbol_1 = 
			    IFIX(distance_to_next_baseline_from_top);
		    gensymed_symbol_2 = EQ(only_if_in_text_qm,Ktight) ? 
			    IFIX(ISVREF(text_box_format,(SI_Long)32L)) + 
			    (SI_Long)2L : 
			    IFIX(baseline_to_baseline_distance) - 
			    distance_from_baseline_to_bottom_of_line;
		    temp_1 = FIXNUM_GE(y_in_text_qm,FIX(gensymed_symbol_1 
			    - gensymed_symbol_2));
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(only_if_in_text_qm) ?  !TRUEP(CDR(l)) : 
			TRUEP(Nil);
	}
	else
	    temp_1 = FIXNUM_EQ(line_index,line_index_qm);
	if (temp_1) {
	    line_index_qm = line_index;
	    line_width_a = Nil;
	    line_width_b = Nil;
	    line_length = text_string_length(text_element);
	    gensymed_symbol_1 = IFIX(line_length);
	    gensymed_symbol_2 = character_index_qm || 
		    look_in_lost_spaces_too_qm ? (FIXNUMP(lost_spaces) ? 
		    IFIX(lost_spaces) : 
		    IFIX(text_string_length(lost_spaces))) : (SI_Long)0L;
	    end_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    width_of_initial_spaces_qm = Nil;
	    i = FIX((SI_Long)0L);
	    preceding_i = Nil;
	    unicode_wide_character = Nil;
	    character_width = Nil;
	    line_width_a = FIX((SI_Long)0L);
	    line_width_b = FIX((SI_Long)128L);
	  next_loop_1:
	    preceding_i = i;
	    if ( !(IFIX(preceding_i) < end_1))
		goto end_loop_1;
	    if (FIXNUM_LT(i,line_length)) {
		temp = FIX(UBYTE_16_ISAREF_1(text_element,IFIX(i)));
		i = FIXNUM_ADD1(i);
		unicode_wide_character = temp;
	    }
	    else if (FIXNUMP(lost_spaces)) {
		i = FIXNUM_ADD1(i);
		unicode_wide_character = FIX((SI_Long)32L);
	    }
	    else {
		i_1 = FIXNUM_MINUS(i,line_length);
		offset = FIXNUM_NEGATE(i_1);
		temp = FIX(UBYTE_16_ISAREF_1(lost_spaces,IFIX(i_1)));
		i_1 = FIXNUM_ADD1(i_1);
		incff_1_arg = FIXNUM_ADD(i_1,offset);
		i = FIXNUM_ADD(i,incff_1_arg);
		unicode_wide_character = temp;
	    }
	    if (IFIX(unicode_wide_character) == (SI_Long)9L) {
		a = line_width_a;
		b = line_width_b;
		position_1 = (IFIX(a) << (SI_Long)8L) + IFIX(b) + 
			(SI_Long)-128L;
		tab_width = tab_width_qm;
		if (tab_width);
		else
		    tab_width = FIX((SI_Long)9600L);
		next_tab_position = add(minus(FIX(position_1),
			mod(FIX(position_1),tab_width)),tab_width);
		character_width = FIX(IFIX(next_tab_position) - position_1);
	    }
	    else if (ordinary_space_p(unicode_wide_character)) {
		temp = word_spacing_for_next_line_qm;
		if (temp);
		else
		    temp = word_spacing;
		character_width = temp;
	    }
	    else
		character_width = 
			get_unicode_set_width_as_text_width(unicode_wide_character,
			ab_font);
	    if ( !TRUEP(width_of_initial_spaces_qm) &&  
		    !TRUEP(text_break_p(unicode_wide_character)))
		width_of_initial_spaces_qm = line_width_a;
	    if (x_in_text_qm) {
		if (IFIX(character_width) > (SI_Long)0L) {
		    gensymed_symbol_1 = IFIX(indentation);
		    gensymed_symbol_2 = IFIX(line_width_a);
		    gensymed_symbol_3 = IFIX(line_width_b);
		    gensymed_symbol_4 = 
			    find_character_instead_of_position_between_qm ?
			     IFIX(character_width) : IFIX(character_width) 
			    >>  -  - (SI_Long)1L;
		    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
		    gensymed_symbol_4 = (SI_Long)8L;
		    gensymed_symbol_3 = gensymed_symbol_3 >>  -  - 
			    gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		    temp_1 = FIXNUM_GT(FIX(gensymed_symbol_1 + 
			    gensymed_symbol_2),x_in_text_qm);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = FIXNUM_EQ(preceding_i,character_index_qm);
	    if (temp_1)
		goto end_loop_1;
	    gensymed_symbol = FIXNUM_ADD(line_width_b,character_width);
	    incff_1_arg_1 = IFIX(gensymed_symbol) >>  -  - (SI_Long)8L;
	    line_width_a_new_value = IFIX(line_width_a) + incff_1_arg_1;
	    line_width_a = FIX(line_width_a_new_value);
	    gensymed_symbol_1 = IFIX(gensymed_symbol) & (SI_Long)255L;
	    line_width_b = FIX(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    character_index_qm = preceding_i;
	    midline_x_from_left = FIXNUM_ADD(indentation,line_width_a);
	    temp =  !TRUEP(x_in_text_qm) ? T : Nil;
	    if (temp);
	    else
		temp =  !TRUEP(only_if_in_text_qm) ? T : Nil;
	    if (temp);
	    else {
		if (width_of_initial_spaces_qm) {
		    indentation_offset = EQ(only_if_in_text_qm,Ktight) ? 
			    (SI_Long)2L : IFIX(word_spacing) + 
			    (SI_Long)128L >>  -  - (SI_Long)8L;
		    temp_1 = IFIX(x_in_text_qm) >= 
			    IFIX(FIXNUM_ADD(indentation,
			    width_of_initial_spaces_qm)) - indentation_offset;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp = FIXNUM_LT(preceding_i,line_length) ? T : Nil;
		    if (temp);
		    else {
			indentation_offset_text_width = 
				EQ(only_if_in_text_qm,Ktight) ? 
				FIX((SI_Long)512L) : word_spacing;
			temp = IFIX(x_in_text_qm) <= IFIX(indentation) + 
				(IFIX(line_width_a) + 
				(IFIX(FIXNUM_ADD(line_width_b,
				indentation_offset_text_width)) >>  -  - 
				(SI_Long)8L)) ? T : Nil;
		    }
		}
		else
		    temp = Nil;
	    }
	    ok_to_return_position_qm = temp;
	    if (ok_to_return_position_qm) {
		temp_2 = line_index_qm;
		temp_3 = character_index_qm;
		temp_4 = find_text_tail_for_line(text,line_index_qm);
		gensymed_symbol_1 = left_edge_of_text;
		gensymed_symbol_2 = x_magnification_qm ? 
			IFIX(FIXNUM_TIMES(midline_x_from_left,
			x_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L : IFIX(midline_x_from_left);
		temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
		gensymed_symbol_1 = top_edge_of_text;
		gensymed_symbol_2 = y_magnification_qm ? 
			IFIX(FIXNUM_TIMES(distance_to_next_baseline_from_top,
			y_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L : IFIX(distance_to_next_baseline_from_top);
		return VALUES_5(temp_2,temp_3,temp_4,temp,
			FIX(gensymed_symbol_1 + gensymed_symbol_2));
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (above_bottom_of_line_qm)
	    return VALUES_1(Nil);
	line_index = FIXNUM_ADD1(line_index);
	distance_to_next_baseline_from_top = 
		FIXNUM_ADD(distance_to_next_baseline_from_top,
		baseline_to_baseline_distance);
	word_spacing_for_next_line_qm = Nil;
	lost_spaces = FIX((SI_Long)1L);
    }
    else if (FIXNUMP(text_element))
	indentation = text_element;
    else {
	lost_spaces_value_qm = CONSP(text_element) && 
		EQ(M_CAR(text_element),Qlost_spaces) ? M_CDR(text_element) 
		: Nil;
	if (lost_spaces_value_qm)
	    lost_spaces = lost_spaces_value_qm;
	else if (SYMBOLP(text_element));
	else if (EQ(CAR(text_element),Qleading))
	    distance_to_next_baseline_from_top = 
		    FIXNUM_ADD(distance_to_next_baseline_from_top,
		    CDR(text_element));
	else if (EQ(CAR(text_element),Qword_spacing))
	    word_spacing_for_next_line_qm = CDR(text_element);
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-POSITION-IN-TEXT-GIVEN-IMAGE-PLANE */
Object find_position_in_text_given_image_plane varargs_1(int, n)
{
    Object block_enclosing_text, text_box_qm, text_cell_qm;
    Object left_edge_of_cell_qm, top_edge_of_cell_qm;
    Object look_in_lost_spaces_too_qm, image_plane, x_in_window, y_in_window;
    Object line_index_qm, character_index_qm, text_tail_qm, only_if_in_text_qm;
    Object find_character_instead_of_position_between_qm, x_in_workspace;
    Object y_in_workspace, current_image_plane, gensym_window;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, enclosing_block;
    Object frame_transforms_of_block_qm, frame_transforms_of_enclosing_block;
    Object gensymed_symbol, frame_transform, value, incff_1_arg, temp_1;
    Object scale_1;
    SI_Long gensymed_symbol_1, scale, gensymed_symbol_2, unshifted_result;
    SI_Long x_offset, y_offset, temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(29);

    x_note_fn_call(126,77);
    INIT_ARGS_nonrelocating();
    block_enclosing_text = REQUIRED_ARG_nonrelocating();
    text_box_qm = REQUIRED_ARG_nonrelocating();
    text_cell_qm = REQUIRED_ARG_nonrelocating();
    left_edge_of_cell_qm = REQUIRED_ARG_nonrelocating();
    top_edge_of_cell_qm = REQUIRED_ARG_nonrelocating();
    look_in_lost_spaces_too_qm = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_tail_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    only_if_in_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    find_character_instead_of_position_between_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    x_in_workspace = Nil;
    y_in_workspace = Nil;
    current_image_plane = image_plane;
    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
	    28);
      gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
      left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
      top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
      right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
      bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	      27);
	PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		26);
	  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		  25);
	    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		    24);
	      current_image_x_scale = FIX((SI_Long)4096L);
	      current_image_y_scale = FIX((SI_Long)4096L);
	      current_x_origin_of_drawing = FIX((SI_Long)0L);
	      current_y_origin_of_drawing = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		      23);
		PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			22);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			  21);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			    20);
		      left_edge_of_draw_area = Left_edge_of_draw_area;
		      top_edge_of_draw_area = Top_edge_of_draw_area;
		      right_edge_of_draw_area = Right_edge_of_draw_area;
		      bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			      19);
			PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
				18);
			  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				  17);
			    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				    16);
			      temp = ISVREF(image_plane,(SI_Long)6L);
			      Left_edge_of_draw_area = FIXNUM_MAX(temp,
				      Left_edge_of_draw_area);
			      temp = ISVREF(image_plane,(SI_Long)7L);
			      Top_edge_of_draw_area = FIXNUM_MAX(temp,
				      Top_edge_of_draw_area);
			      temp = ISVREF(image_plane,(SI_Long)8L);
			      Right_edge_of_draw_area = FIXNUM_MIN(temp,
				      Right_edge_of_draw_area);
			      temp = ISVREF(image_plane,(SI_Long)9L);
			      Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				      Bottom_edge_of_draw_area);
			      if (FIXNUM_LT(Left_edge_of_draw_area,
				      Right_edge_of_draw_area) && 
				      FIXNUM_LT(Top_edge_of_draw_area,
				      Bottom_edge_of_draw_area)) {
				  left_edge_of_draw_area = 
					  Left_edge_of_draw_area;
				  top_edge_of_draw_area = 
					  Top_edge_of_draw_area;
				  right_edge_of_draw_area = 
					  Right_edge_of_draw_area;
				  bottom_edge_of_draw_area = 
					  Bottom_edge_of_draw_area;
				  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
					  15);
				    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
					    14);
				      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					      13);
					PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
						12);
					  temp = ISVREF(image_plane,
						  (SI_Long)19L);
					  Left_edge_of_draw_area = 
						  FIXNUM_MAX(temp,
						  Left_edge_of_draw_area);
					  temp = ISVREF(image_plane,
						  (SI_Long)20L);
					  Top_edge_of_draw_area = 
						  FIXNUM_MAX(temp,
						  Top_edge_of_draw_area);
					  temp = ISVREF(image_plane,
						  (SI_Long)21L);
					  Right_edge_of_draw_area = 
						  FIXNUM_MIN(temp,
						  Right_edge_of_draw_area);
					  temp = ISVREF(image_plane,
						  (SI_Long)22L);
					  Bottom_edge_of_draw_area = 
						  FIXNUM_MIN(temp,
						  Bottom_edge_of_draw_area);
					  if (FIXNUM_LT(Left_edge_of_draw_area,
						  Right_edge_of_draw_area) 
						  && 
						  FIXNUM_LT(Top_edge_of_draw_area,
						  Bottom_edge_of_draw_area)) {
					      current_frame_transform_qm = Nil;
					      current_image_x_scale = 
						      ISVREF(image_plane,
						      (SI_Long)11L);
					      current_image_y_scale = 
						      ISVREF(image_plane,
						      (SI_Long)12L);
					      current_x_origin_of_drawing 
						      = ISVREF(image_plane,
						      (SI_Long)13L);
					      current_y_origin_of_drawing 
						      = ISVREF(image_plane,
						      (SI_Long)14L);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
						      11);
						PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
							10);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
							  9);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
							    8);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
							      7);
							left_edge_of_draw_area 
								= 
								Left_edge_of_draw_area;
							top_edge_of_draw_area 
								= 
								Top_edge_of_draw_area;
							right_edge_of_draw_area 
								= 
								Right_edge_of_draw_area;
							bottom_edge_of_draw_area 
								= 
								Bottom_edge_of_draw_area;
							PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
								6);
							  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
								  5);
							    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
								    4);
							      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
								      3);
								current_frame_transform_qm 
									= 
									Current_frame_transform_qm;
								current_x_origin_of_drawing 
									= 
									Current_x_origin_of_drawing;
								current_y_origin_of_drawing 
									= 
									Current_y_origin_of_drawing;
								PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									2);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
									  1);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
									    0);
								      if ((SI_Long)0L 
									      != 
									      (IFIX(ISVREF(block_enclosing_text,
									      (SI_Long)5L)) 
									      & 
									      (SI_Long)32768L)) 
										  {
									  enclosing_block 
										  = 
										  block_enclosing_text;
									  frame_transforms_of_block_qm 
										  = 
										  Nil;
									next_loop:
									  frame_transforms_of_block_qm 
										  = 
										  get_lookup_slot_value_given_default(enclosing_block,
										  Qframe_transforms_of_block,
										  Nil);
									  if (frame_transforms_of_block_qm) 
										      {
									      frame_transforms_of_enclosing_block 
										      = 
										      frame_transforms_of_block_qm;
									      goto end_1;
									  }
									  gensymed_symbol 
										  = 
										  ACCESS_ONCE(ISVREF(enclosing_block,
										  (SI_Long)14L));
									  gensymed_symbol 
										  = 
										  gensymed_symbol 
										  ?
										   
										  ACCESS_ONCE(ISVREF(gensymed_symbol,
										  (SI_Long)5L)) 
										  :
										   
										  Nil;
									  enclosing_block 
										  = 
										  gensymed_symbol;
									  goto next_loop;
									end_loop:
									  frame_transforms_of_enclosing_block 
										  = 
										  Qnil;
									end_1:;
									  temp 
										  = 
										  assq_function(Current_image_plane,
										  frame_transforms_of_enclosing_block);
									  frame_transform 
										  = 
										  CDR(temp);
									  if ( 
										  !EQ(Current_frame_transform_qm,
										  frame_transform)) 
										      {
									      nest_draw_area_for_frame_1(frame_transform);
									      Current_frame_transform_qm 
										      = 
										      frame_transform;
									      gensymed_symbol_1 
										      = 
										      IFIX(ISVREF(frame_transform,
										      (SI_Long)10L));
									      scale 
										      = 
										      (SI_Long)4096L;
									      value 
										      = 
										      ISVREF(frame_transform,
										      (SI_Long)6L);
									      if (scale 
										      == 
										      (SI_Long)4096L)
										  gensymed_symbol_2 
											  = 
											  IFIX(value);
									      else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
										      < 
										      scale 
										      && 
										      scale 
										      < 
										      IFIX(Isqrt_of_most_positive_fixnum) 
										      && 
										      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										      value) 
										      && 
										      FIXNUM_LT(value,
										      Isqrt_of_most_positive_fixnum)) 
											  {
										  unshifted_result 
											  = 
											  scale 
											  * 
											  IFIX(value) 
											  + 
											  (SI_Long)2048L;
										  gensymed_symbol_2 
											  = 
											  unshifted_result 
											  >> 
											   
											  - 
											   
											  - 
											  (SI_Long)12L;
									      }
									      else
										  gensymed_symbol_2 
											  = 
											  IFIX(scalef_function(FIX(scale),
											  value));
									      x_offset 
										      = 
										      gensymed_symbol_1 
										      + 
										      gensymed_symbol_2;
									      if ( 
										      !((SI_Long)0L 
										      == 
										      x_offset)) 
											  {
										  if (IFIX(Current_image_x_scale) 
											  == 
											  (SI_Long)4096L)
										      incff_1_arg 
											      = 
											      FIX(x_offset);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  Current_image_x_scale) 
											  && 
											  FIXNUM_LT(Current_image_x_scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  x_offset 
											  && 
											  x_offset 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(Current_image_x_scale) 
											      * 
											      x_offset 
											      + 
											      (SI_Long)2048L;
										      incff_1_arg 
											      = 
											      FIX(unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L);
										  }
										  else
										      incff_1_arg 
											      = 
											      scalef_function(Current_image_x_scale,
											      FIX(x_offset));
										  temp_1 
											  = 
											  FIXNUM_ADD(Current_x_origin_of_drawing,
											  incff_1_arg);
										  Current_x_origin_of_drawing 
											  = 
											  temp_1;
									      }
									      gensymed_symbol_1 
										      = 
										      IFIX(ISVREF(frame_transform,
										      (SI_Long)11L));
									      scale 
										      = 
										      (SI_Long)4096L;
									      value 
										      = 
										      ISVREF(frame_transform,
										      (SI_Long)7L);
									      if (scale 
										      == 
										      (SI_Long)4096L)
										  gensymed_symbol_2 
											  = 
											  IFIX(value);
									      else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
										      < 
										      scale 
										      && 
										      scale 
										      < 
										      IFIX(Isqrt_of_most_positive_fixnum) 
										      && 
										      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										      value) 
										      && 
										      FIXNUM_LT(value,
										      Isqrt_of_most_positive_fixnum)) 
											  {
										  unshifted_result 
											  = 
											  scale 
											  * 
											  IFIX(value) 
											  + 
											  (SI_Long)2048L;
										  gensymed_symbol_2 
											  = 
											  unshifted_result 
											  >> 
											   
											  - 
											   
											  - 
											  (SI_Long)12L;
									      }
									      else
										  gensymed_symbol_2 
											  = 
											  IFIX(scalef_function(FIX(scale),
											  value));
									      y_offset 
										      = 
										      gensymed_symbol_1 
										      + 
										      gensymed_symbol_2;
									      if ( 
										      !((SI_Long)0L 
										      == 
										      y_offset)) 
											  {
										  if (IFIX(Current_image_y_scale) 
											  == 
											  (SI_Long)4096L)
										      incff_1_arg 
											      = 
											      FIX(y_offset);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  Current_image_y_scale) 
											  && 
											  FIXNUM_LT(Current_image_y_scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  y_offset 
											  && 
											  y_offset 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(Current_image_y_scale) 
											      * 
											      y_offset 
											      + 
											      (SI_Long)2048L;
										      incff_1_arg 
											      = 
											      FIX(unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L);
										  }
										  else
										      incff_1_arg 
											      = 
											      scalef_function(Current_image_y_scale,
											      FIX(y_offset));
										  temp_1 
											  = 
											  FIXNUM_ADD(Current_y_origin_of_drawing,
											  incff_1_arg);
										  Current_y_origin_of_drawing 
											  = 
											  temp_1;
									      }
									  }
								      }
								      scale_1 
									      = 
									      Current_image_x_scale;
								      value 
									      = 
									      FIXNUM_MINUS(x_in_window,
									      Current_x_origin_of_drawing);
								      if (IFIX(scale_1) 
									      == 
									      (SI_Long)4096L)
									  x_in_workspace 
										  = 
										  value;
								      else if ( 
									      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									      value) 
									      && 
									      FIXNUM_LT(value,
									      Isqrt_of_most_positive_fixnum)))
									  x_in_workspace 
										  = 
										  inverse_scalef_function(scale_1,
										  value);
								      else if (IFIX(value) 
									      >= 
									      (SI_Long)0L) 
										  {
									  temp 
										  = 
										  FIX(((IFIX(value) 
										  << 
										  (SI_Long)12L) 
										  + 
										  (IFIX(scale_1) 
										  >> 
										   
										  - 
										   
										  - 
										  (SI_Long)1L)) 
										  / 
										  IFIX(scale_1));
									  x_in_workspace 
										  = 
										  temp;
								      }
								      else {
									  temp_2 
										  = 
										  ((IFIX(FIXNUM_NEGATE(value)) 
										  << 
										  (SI_Long)12L) 
										  + 
										  (IFIX(scale_1) 
										  >> 
										   
										  - 
										   
										  - 
										  (SI_Long)1L)) 
										  / 
										  IFIX(scale_1);
									  temp 
										  = 
										  FIXNUM_NEGATE(FIX(temp_2));
									  x_in_workspace 
										  = 
										  temp;
								      }
								      scale_1 
									      = 
									      Current_image_y_scale;
								      value 
									      = 
									      FIXNUM_MINUS(y_in_window,
									      Current_y_origin_of_drawing);
								      if (IFIX(scale_1) 
									      == 
									      (SI_Long)4096L)
									  y_in_workspace 
										  = 
										  value;
								      else if ( 
									      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									      value) 
									      && 
									      FIXNUM_LT(value,
									      Isqrt_of_most_positive_fixnum)))
									  y_in_workspace 
										  = 
										  inverse_scalef_function(scale_1,
										  value);
								      else if (IFIX(value) 
									      >= 
									      (SI_Long)0L) 
										  {
									  temp 
										  = 
										  FIX(((IFIX(value) 
										  << 
										  (SI_Long)12L) 
										  + 
										  (IFIX(scale_1) 
										  >> 
										   
										  - 
										   
										  - 
										  (SI_Long)1L)) 
										  / 
										  IFIX(scale_1));
									  y_in_workspace 
										  = 
										  temp;
								      }
								      else {
									  temp_2 
										  = 
										  ((IFIX(FIXNUM_NEGATE(value)) 
										  << 
										  (SI_Long)12L) 
										  + 
										  (IFIX(scale_1) 
										  >> 
										   
										  - 
										   
										  - 
										  (SI_Long)1L)) 
										  / 
										  IFIX(scale_1);
									  temp 
										  = 
										  FIXNUM_NEGATE(FIX(temp_2));
									  y_in_workspace 
										  = 
										  temp;
								      }
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
					  }
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
			      }
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
    return find_position_in_text(12,text_box_qm,text_cell_qm,
	    left_edge_of_cell_qm,top_edge_of_cell_qm,
	    look_in_lost_spaces_too_qm,x_in_workspace,y_in_workspace,
	    line_index_qm,character_index_qm,text_tail_qm,
	    only_if_in_text_qm,find_character_instead_of_position_between_qm);
}

/* RECLAIM-SUBCOMMAND-FUNCTION-ARGLIST?-VALUE */
Object reclaim_subcommand_function_arglist_qm_value(arglist,subcommand_menu_1)
    Object arglist, subcommand_menu_1;
{
    Object reclaimer_function_qm;

    x_note_fn_call(126,78);
    reclaimer_function_qm = ISVREF(subcommand_menu_1,(SI_Long)29L);
    if (reclaimer_function_qm)
	inline_funcall_1(reclaimer_function_qm,arglist);
    return VALUES_1(Nil);
}

/* GENERATE-SPOT-FOR-SUBCOMMAND-MENU */
Object generate_spot_for_subcommand_menu(subcommand_menu_1,mouse_pointer)
    Object subcommand_menu_1, mouse_pointer;
{
    x_note_fn_call(126,79);
    return generate_spot_for_button_menu(make_subcommand_menu_button_spot_1(),
	    subcommand_menu_1,mouse_pointer);
}

Object Background_color_for_enabled_subcommands = UNBOUND;

Object Text_color_for_enabled_subcommands = UNBOUND;

Object Background_color_for_disabled_subcommands = UNBOUND;

Object Text_color_for_disabled_subcommands = UNBOUND;

Object Highlight_color_for_enabled_pending_subcommands = UNBOUND;

Object Highlight_color_for_enabled_non_pending_subcommands = UNBOUND;

Object Highlight_color_for_disabled_pending_subcommands = UNBOUND;

Object Highlight_color_for_disabled_non_pending_subcommands = UNBOUND;

Object Highlight_color_for_pending_on_radio_button_subcommands = UNBOUND;

Object Highlight_color_for_non_pending_on_radio_button_subcommands = UNBOUND;

Object Highlight_color_for_pending_off_radio_button_subcommands = UNBOUND;

Object Highlight_color_for_non_pending_off_radio_button_subcommands = UNBOUND;

static Object Qbutton_label;       /* button-label */

static Object Kfirst;              /* :first */

static Object string_constant_16;  /* " ~a " */

static Object Qsubcommand_menu_item_format;  /* subcommand-menu-item-format */

static Object Qspecial_case_qm;    /* special-case? */

static Object Qbackground_color;   /* background-color */

static Object Qline_color;         /* line-color */

static Object Qsubcommand_menu_table_format;  /* subcommand-menu-table-format */

static Object Qsubcommand_menu;    /* subcommand-menu */

/* MAKE-SUBCOMMAND-MENU */
Object make_subcommand_menu varargs_1(int, n)
{
    Object subcommands;
    Object font_size_qm, subcommand, ab_loop_list_, subcommand_symbol;
    Object translation_qm, final_string, final_strings, ab_loopvar_;
    Object ab_loopvar__1, temp, current_localization_purpose_qm, width;
    Object ab_loop_list__1, cell, ab_loopvar__2, text_cell;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(126,80);
    INIT_ARGS_nonrelocating();
    subcommands = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    font_size_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    subcommand = Nil;
    ab_loop_list_ = subcommands;
    subcommand_symbol = Nil;
    translation_qm = Nil;
    final_string = Nil;
    final_strings = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subcommand = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    subcommand_symbol = CONSP(subcommand) ? CAR(subcommand) : subcommand;
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = Current_localization_purpose_qm;
	if (temp);
	else
	    temp = Qbutton_label;
	current_localization_purpose_qm = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
		0);
	  temp = translation_for_symbol_qm(1,subcommand_symbol);
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    translation_qm = result;
    final_string = translation_qm ? copy_text_string(translation_qm) : 
	    CONSP(subcommand) ? copy_text_string(CDR(subcommand)) : 
	    copy_symbol_name(2,subcommand_symbol,Kfirst);
    ab_loopvar__1 = gensym_cons_1(final_string,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	final_strings = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    width = 
	    get_overall_minimum_width_for_subcommand_menu_column(final_strings);
    subcommand = Nil;
    ab_loop_list_ = subcommands;
    subcommand_symbol = Nil;
    final_string = Nil;
    ab_loop_list__1 = final_strings;
    cell = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      subcommand = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      subcommand_symbol = CONSP(subcommand) ? CAR(subcommand) : subcommand;
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      final_string = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (New_g2_classic_ui_p)
	  Cell = make_icon_cell_for_entity(make_editor_subcommand_button(3,
		  final_string,subcommand_symbol,width),FIX((SI_Long)2L),
		  FIX((SI_Long)0L),FIX((SI_Long)2L),FIX((SI_Long)0L));
      else {
	  temp = convert_text_string_to_text(tformat_text_string(2,
		  string_constant_16,final_string));
	  reclaim_text_string(final_string);
	  text_cell = make_text_cell(2,temp,
		  choose_font_format_per_font_size(Qsubcommand_menu_item_format,
		  font_size_qm));
	  choose_font_format_per_font_size(Qsubcommand_menu_item_format,
		  font_size_qm);
	  change_text_cell_property(text_cell,Qspecial_case_qm,
		  subcommand_symbol);
	  change_text_cell_property(text_cell,Qbackground_color,
		  Background_color_for_disabled_subcommands);
	  change_text_cell_property(text_cell,Qline_color,
		  Text_color_for_disabled_subcommands);
	  Cell = text_cell;
      }
      ab_loopvar__2 = slot_value_cons_1(slot_value_cons_1(Cell,Nil),Nil);
      if (ab_loopvar__2) {
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = last(ab_loopvar__2,_);
      }
      goto next_loop_1;
    end_loop_1:
      temp = ab_loopvar_;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    reclaim_gensym_list_1(final_strings);
    goto end_2;
    temp = Qnil;
  end_2:;
    temp = make_or_reformat_table(5,temp,Qsubcommand_menu_table_format,Nil,
	    Qsubcommand_menu,T);
    reclaim_slot_value(subcommands);
    RESTORE_STACK();
    return VALUES_1(temp);
}

static Object Qeditor_subcommand_button;  /* editor-subcommand-button */

static Object Qeditor_subcommand_disabled_p;  /* editor-subcommand-disabled-p */

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

/* SUBCOMMAND-ENABLED-P */
Object subcommand_enabled_p(subcommand_cell,subcommand_menu_1)
    Object subcommand_cell, subcommand_menu_1;
{
    Object s, gensymed_symbol, sub_class_bit_vector, subcommand_text_cell;
    Object text_cell_plist, text_cell_format, background_color_qm, temp_1;
    Object text_color_qm, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(126,81);
    if (ATOM(subcommand_cell)) {
	s = first_subblock(subcommand_cell);
	if (s) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qeditor_subcommand_button,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(s,(SI_Long)1L),
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1( !TRUEP(get_slot_value_function(s,
		    Qeditor_subcommand_disabled_p,Nil)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else {
	subcommand_text_cell = subcommand_cell;
	text_cell_plist = CADR(subcommand_text_cell);
	text_cell_format = CAR(subcommand_text_cell);
	background_color_qm = getfq_function_no_default(text_cell_plist,
		Qbackground_color);
	if (background_color_qm);
	else
	    background_color_qm = ISVREF(text_cell_format,(SI_Long)24L);
	if (background_color_qm);
	else
	    background_color_qm = ISVREF(ISVREF(subcommand_menu_1,
		    (SI_Long)16L),(SI_Long)23L);
	temp_1 = background_color_qm;
	if (temp_1);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(subcommand_menu_1,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)21L);
	    if (temp_1);
	    else
		temp_1 = Qwhite;
	}
	text_color_qm = getfq_function_no_default(text_cell_plist,Qline_color);
	if (text_color_qm);
	else
	    text_color_qm = ISVREF(text_cell_format,(SI_Long)23L);
	if (text_color_qm);
	else
	    text_color_qm = ISVREF(ISVREF(subcommand_menu_1,(SI_Long)16L),
		    (SI_Long)22L);
	temp_2 = text_color_qm;
	if (temp_2);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(subcommand_menu_1,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)22L);
	    if (temp_2);
	    else
		temp_2 = Qblack;
	}
	return VALUES_1( !EQ(temp_1,temp_2) ? T : Nil);
    }
}

static Object Qenable_or_disable_subcommand;  /* enable-or-disable-subcommand */

static Object Qeditor_subcommand_name;  /* editor-subcommand-name */

static Object Qsubcommand_button_radio_button_status;  /* subcommand-button-radio-button-status */

static Object Kno_change;          /* :no-change */

static Object Qradio_button_status;  /* radio-button-status */

/* ENABLE-OR-DISABLE-SUBCOMMAND */
Object enable_or_disable_subcommand varargs_1(int, n)
{
    Object subcommand_menu_1, subcommand, disable_case_qm;
    Object status_as_radio_button_qm, index_of_top_of_backtrace_stack, temp;
    Object svref_arg_2, table_row, ab_loop_list_, ab_loop_iter_flag_, cell_qm;
    Object ab_loop_list__1, editor_subcommand_button, text_cell, list_1;
    Object background_color, line_color, text_cell_plist;
    SI_Long row_index, column_index;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,82);
    INIT_ARGS_nonrelocating();
    subcommand_menu_1 = REQUIRED_ARG_nonrelocating();
    subcommand = REQUIRED_ARG_nonrelocating();
    disable_case_qm = REQUIRED_ARG_nonrelocating();
    status_as_radio_button_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qenable_or_disable_subcommand;
      }
      if (Keep_edit_workspace_hidden_no_matter_what_qm) {
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_enable_or_disable_subcommand;
      }
      table_row = Nil;
      ab_loop_list_ = ISVREF(subcommand_menu_1,(SI_Long)19L);
      row_index = (SI_Long)0L;
      ab_loop_iter_flag_ = T;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      table_row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  row_index = row_index + (SI_Long)1L;
      cell_qm = Nil;
      ab_loop_list__1 = table_row;
      column_index = (SI_Long)0L;
      ab_loop_iter_flag_ = T;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_qm = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if ( !TRUEP(ab_loop_iter_flag_))
	  column_index = column_index + (SI_Long)1L;
      if ( !TRUEP(cell_qm));
      else if (ATOM(cell_qm)) {
	  editor_subcommand_button = first_subblock(cell_qm);
	  if (EQ(get_slot_value_function(editor_subcommand_button,
		  Qeditor_subcommand_name,Nil),subcommand)) {
	      enable_or_disable_editor_subcommand_button(editor_subcommand_button,
		      disable_case_qm);
	      if (status_as_radio_button_qm) {
		  change_slot_value(3,editor_subcommand_button,
			  Qsubcommand_button_radio_button_status,
			  status_as_radio_button_qm);
		  indicate_editor_subcommand_button_pending_state(editor_subcommand_button,
			  Nil,Nil);
	      }
	      temp_1 = TRUEP(T);
	      goto end_1;
	  }
      }
      else {
	  text_cell = cell_qm;
	  list_1 = CADR(text_cell);
	next_loop_2:
	  if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qspecial_case_qm))
	      goto end_loop_2;
	  list_1 = M_CDR(M_CDR(list_1));
	  goto next_loop_2;
	end_loop_2:;
	  if (EQ(list_1 ? M_CAR(M_CDR(list_1)) : Nil,subcommand)) {
	      indicate_subcommand_pending_state(6,subcommand_menu_1,
		      text_cell,Nil,T,FIX(row_index),FIX(column_index));
	      background_color = disable_case_qm ? 
		      Background_color_for_disabled_subcommands : 
		      Background_color_for_enabled_subcommands;
	      line_color = disable_case_qm ? 
		      Text_color_for_disabled_subcommands : 
		      Text_color_for_enabled_subcommands;
	      text_cell_plist = CADR(text_cell);
	      list_1 = text_cell_plist;
	    next_loop_3:
	      if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qbackground_color))
		  goto end_loop_3;
	      list_1 = M_CDR(M_CDR(list_1));
	      goto next_loop_3;
	    end_loop_3:;
	      if (EQ(list_1 ? M_CAR(M_CDR(list_1)) : Nil,background_color)) {
		  list_1 = text_cell_plist;
		next_loop_4:
		  if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qline_color))
		      goto end_loop_4;
		  list_1 = M_CDR(M_CDR(list_1));
		  goto next_loop_4;
		end_loop_4:;
		  temp_1 = EQ(list_1 ? M_CAR(M_CDR(list_1)) : Nil,line_color);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if ( !temp_1)
		  change_color_of_text_cell(6,subcommand_menu_1,text_cell,
			  Nil,background_color,Kno_change,line_color);
	      if (status_as_radio_button_qm) {
		  change_text_cell_property(text_cell,Qradio_button_status,
			  status_as_radio_button_qm);
		  indicate_subcommand_pending_state(6,subcommand_menu_1,
			  text_cell,Nil,Nil,FIX(row_index),FIX(column_index));
	      }
	      temp_1 = TRUEP(T);
	      goto end_1;
	  }
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop_1;
    end_loop_1:
      temp_1 = TRUEP(Qnil);
    end_1:;
      if (temp_1)
	  goto end_loop;
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
  end_enable_or_disable_subcommand:
    return result;
}

static Object Qoff;                /* off */

static Object Qon;                 /* on */

/* ENABLE-OR-DISABLE-RADIO-BUTTON-SUBCOMMAND */
Object enable_or_disable_radio_button_subcommand(subcommand_menu_1,
	    subcommand,disable_case_qm)
    Object subcommand_menu_1, subcommand, disable_case_qm;
{
    Object table_row, ab_loop_list_, ab_loop_iter_flag_, cell_qm;
    Object ab_loop_list__1, list_1;
    SI_Long row_index, column_index;
    char temp;

    x_note_fn_call(126,83);
    table_row = Nil;
    ab_loop_list_ = ISVREF(subcommand_menu_1,(SI_Long)19L);
    row_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    table_row = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	row_index = row_index + (SI_Long)1L;
    cell_qm = Nil;
    ab_loop_list__1 = table_row;
    column_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    cell_qm = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_iter_flag_))
	column_index = column_index + (SI_Long)1L;
    if (cell_qm) {
	if (ATOM(cell_qm))
	    temp = 
		    EQ(editor_subcommand_name_function(first_subblock(cell_qm)),
		    subcommand);
	else {
	    list_1 = CADR(cell_qm);
	  next_loop_2:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qspecial_case_qm))
		goto end_loop_2;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop_2;
	  end_loop_2:;
	    temp = EQ(list_1 ? M_CAR(M_CDR(list_1)) : Nil,subcommand);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (ATOM(cell_qm)) {
	    change_slot_value(3,first_subblock(cell_qm),
		    Qsubcommand_button_radio_button_status,disable_case_qm 
		    ? Qoff : Qon);
	    indicate_subcommand_pending_state(6,subcommand_menu_1,cell_qm,
		    Nil,Nil,FIX(row_index),FIX(column_index));
	}
	else {
	    change_text_cell_property(cell_qm,Qradio_button_status,
		    disable_case_qm ? Qoff : Qon);
	    indicate_subcommand_pending_state(6,subcommand_menu_1,cell_qm,
		    Nil,Nil,FIX(row_index),FIX(column_index));
	}
	temp = TRUEP(T);
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp)
	goto end_loop;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qindicate_subcommand_pending_state;  /* indicate-subcommand-pending-state */

/* INDICATE-SUBCOMMAND-PENDING-STATE */
Object indicate_subcommand_pending_state varargs_1(int, n)
{
    Object subcommand_menu_1, cell, pending_qm;
    Object just_remove_indicator_qm, row_index_if_known_qm;
    Object column_index_if_known_qm, index_of_top_of_backtrace_stack, temp;
    Object svref_arg_2, row_index, column_index;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(126,84);
    INIT_ARGS_nonrelocating();
    subcommand_menu_1 = REQUIRED_ARG_nonrelocating();
    cell = REQUIRED_ARG_nonrelocating();
    pending_qm = REQUIRED_ARG_nonrelocating();
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,1);
      just_remove_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      row_index_if_known_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      column_index_if_known_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      END_ARGS_nonrelocating();
      index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	      0);
	if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		Size_of_basic_backtrace_information),
		Maximum_index_in_backtrace_stack_for_internal_error)) {
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = Nil;
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = Qindicate_subcommand_pending_state;
	}
	row_index = row_index_if_known_qm;
	column_index = column_index_if_known_qm;
	if ( !(row_index_if_known_qm && column_index_if_known_qm)) {
	    result = get_table_cell_indices(subcommand_menu_1,Cell);
	    MVS_2(result,row_index,column_index);
	}
	if (ATOM(Cell))
	    result = indicate_subcommand_pending_state_for_block_cell(Cell,
		    subcommand_menu_1,pending_qm,just_remove_indicator_qm,
		    row_index,column_index);
	else
	    result = indicate_subcommand_pending_state_for_text_cell(Cell,
		    subcommand_menu_1,pending_qm,just_remove_indicator_qm,
		    row_index,column_index);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INDICATE-SUBCOMMAND-PENDING-STATE-FOR-TEXT-CELL */
Object indicate_subcommand_pending_state_for_text_cell(text_cell,
	    subcommand_menu_1,pending_qm,just_remove_indicator_qm,
	    row_index,column_index)
    Object text_cell, subcommand_menu_1, pending_qm, just_remove_indicator_qm;
    Object row_index, column_index;
{
    Object list_1, temp, color, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector, text_region;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(126,85);
    list_1 = CADR(text_cell);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qradio_button_status))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    temp = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (EQ(temp,Qnil))
	color = pending_qm ? 
		Highlight_color_for_enabled_pending_subcommands : 
		Highlight_color_for_enabled_non_pending_subcommands;
    else if (EQ(temp,Qoff))
	color = pending_qm ? 
		Highlight_color_for_pending_off_radio_button_subcommands : 
		Highlight_color_for_non_pending_off_radio_button_subcommands;
    else if (EQ(temp,Qon))
	color = pending_qm ? 
		Highlight_color_for_pending_on_radio_button_subcommands : 
		Highlight_color_for_non_pending_on_radio_button_subcommands;
    else
	color = Qnil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(subcommand_menu_1,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_1:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_1;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_region_class_description,
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
	temp_1 = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if ((temp_1 ? FIXNUM_EQ(ISVREF(subblock,(SI_Long)20L),row_index) : 
	    TRUEP(Nil)) ? FIXNUM_EQ(ISVREF(subblock,(SI_Long)21L),
	    column_index) : TRUEP(Nil)) {
	text_region = subblock;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    text_region = Qnil;
  end_1:;
    if (text_region);
    else
	text_region =  !TRUEP(just_remove_indicator_qm) ? 
		make_text_region(7,subcommand_menu_1,text_cell,
		FIX((SI_Long)1L),FIX((SI_Long)0L),Qend,Nil,color) : Nil;
    if (just_remove_indicator_qm) {
	if (text_region)
	    return delete_frame(text_region);
	else
	    return VALUES_1(Nil);
    }
    else
	return change_color_of_text_region(text_region,color);
}

/* INDICATE-SUBCOMMAND-PENDING-STATE-FOR-BLOCK-CELL */
Object indicate_subcommand_pending_state_for_block_cell(cell,
	    subcommand_menu_1,pending_qm,just_remove_indicator_qm,
	    row_index,column_index)
    Object cell, subcommand_menu_1, pending_qm, just_remove_indicator_qm;
    Object row_index, column_index;
{
    Object gensymed_symbol, sub_class_bit_vector, first_icon_cell_subblock_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,86);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      gensymed_symbol = ISVREF(Cell,(SI_Long)1L);
      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Icon_cell_class_description,
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
	  first_icon_cell_subblock_qm = first_subblock(Cell);
	  if (first_icon_cell_subblock_qm) {
	      sub_class_bit_vector = 
		      ISVREF(ISVREF(first_icon_cell_subblock_qm,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Button_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
	  if (temp)
	      result = indicate_editor_subcommand_button_pending_state(first_icon_cell_subblock_qm,
		      pending_qm,just_remove_indicator_qm);
	  else
	      result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_subcommand_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_subcommand_states, Qchain_of_available_subcommand_states);

DEFINE_VARIABLE_WITH_SYMBOL(Subcommand_state_count, Qsubcommand_state_count);

Object Chain_of_available_subcommand_states_vector = UNBOUND;

/* SUBCOMMAND-STATE-STRUCTURE-MEMORY-USAGE */
Object subcommand_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(126,87);
    temp = Subcommand_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SUBCOMMAND-STATE-COUNT */
Object outstanding_subcommand_state_count()
{
    Object def_structure_subcommand_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,88);
    gensymed_symbol = IFIX(Subcommand_state_count);
    def_structure_subcommand_state_variable = 
	    Chain_of_available_subcommand_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_subcommand_state_variable))
	goto end_loop;
    def_structure_subcommand_state_variable = 
	    ISVREF(def_structure_subcommand_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SUBCOMMAND-STATE-1 */
Object reclaim_subcommand_state_1(subcommand_state)
    Object subcommand_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(126,89);
    inline_note_reclaim_cons(subcommand_state,Nil);
    structure_being_reclaimed = subcommand_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(subcommand_state,(SI_Long)1L));
      SVREF(subcommand_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(subcommand_state,(SI_Long)2L));
      SVREF(subcommand_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_subcommand_states_vector,
	    IFIX(Current_thread_index));
    SVREF(subcommand_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_subcommand_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = subcommand_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SUBCOMMAND-STATE */
Object reclaim_structure_for_subcommand_state(subcommand_state)
    Object subcommand_state;
{
    x_note_fn_call(126,90);
    return reclaim_subcommand_state_1(subcommand_state);
}

static Object Qg2_defstruct_structure_name_subcommand_state_g2_struct;  /* g2-defstruct-structure-name::subcommand-state-g2-struct */

/* MAKE-PERMANENT-SUBCOMMAND-STATE-STRUCTURE-INTERNAL */
Object make_permanent_subcommand_state_structure_internal()
{
    Object def_structure_subcommand_state_variable;
    Object defstruct_g2_subcommand_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(126,91);
    def_structure_subcommand_state_variable = Nil;
    atomic_incff_symval(Qsubcommand_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_subcommand_state_variable = Nil;
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
	defstruct_g2_subcommand_state_variable = the_array;
	SVREF(defstruct_g2_subcommand_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_subcommand_state_g2_struct;
	SVREF(defstruct_g2_subcommand_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_subcommand_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_subcommand_state_variable = 
		defstruct_g2_subcommand_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_subcommand_state_variable);
}

/* MAKE-SUBCOMMAND-STATE-1 */
Object make_subcommand_state_1(subcommand_menu_for_subcommand_state,
	    specific_image_plane_for_subcommand,selected_subcommand_menu_cell)
    Object subcommand_menu_for_subcommand_state;
    Object specific_image_plane_for_subcommand, selected_subcommand_menu_cell;
{
    Object def_structure_subcommand_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(126,92);
    def_structure_subcommand_state_variable = 
	    ISVREF(Chain_of_available_subcommand_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_subcommand_state_variable) {
	temp = Chain_of_available_subcommand_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_subcommand_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_subcommand_state_g2_struct;
    }
    else
	def_structure_subcommand_state_variable = 
		make_permanent_subcommand_state_structure_internal();
    inline_note_allocate_cons(def_structure_subcommand_state_variable,Nil);
    SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)3L)) = 
	    subcommand_menu_for_subcommand_state;
    SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)4L)) = 
	    specific_image_plane_for_subcommand;
    SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)5L)) = 
	    selected_subcommand_menu_cell;
    SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_subcommand_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_subcommand_state_variable);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-SUBCOMMAND-STATE */
Object valid_workstation_context_p_for_subcommand_state(subcommand_state)
    Object subcommand_state;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(126,93);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_subcommand_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = subcommand_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(ISVREF(subcommand_state,(SI_Long)3L),
		(SI_Long)3L);
	x = ISVREF(subcommand_state,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(subcommand_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-SUBCOMMAND-STATE */
Object clean_up_workstation_context_for_subcommand_state(subcommand_state)
    Object subcommand_state;
{
    Object subcommand_menu_1, subcommand_text_cell, gensymed_symbol, x, y, xa;
    Object ya, gensymed_symbol_1;
    char temp;

    x_note_fn_call(126,94);
    subcommand_menu_1 = ISVREF(subcommand_state,(SI_Long)3L);
    subcommand_text_cell = ISVREF(subcommand_state,(SI_Long)5L);
    gensymed_symbol = ISVREF(ISVREF(subcommand_state,(SI_Long)3L),(SI_Long)3L);
    x = ISVREF(subcommand_state,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(subcommand_state,(SI_Long)2L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp ? TRUEP(subcommand_enabled_p(subcommand_text_cell,
	    subcommand_menu_1)) : TRUEP(Nil))
	indicate_subcommand_pending_state(3,subcommand_menu_1,
		subcommand_text_cell,Nil);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_subcommand_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = subcommand_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qsubcommand;         /* subcommand */

/* ENTER-SUBCOMMAND-CONTEXT */
Object enter_subcommand_context(mouse_pointer)
    Object mouse_pointer;
{
    Object subcommand_menu_button_spot, subcommand_cell, subcommand_menu_1;
    Object image_plane;

    x_note_fn_call(126,95);
    subcommand_menu_button_spot = 
	    innermost_spot_blackboard_function(mouse_pointer);
    subcommand_cell = cell_of_table_blackboard_function(mouse_pointer);
    subcommand_menu_1 = 
	    block_showing_representation_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (subcommand_menu_button_spot && subcommand_cell && 
	    subcommand_menu_1 && image_plane) {
	enter_context_in_current_workstation(2,Qsubcommand,
		make_subcommand_state_1(subcommand_menu_1,image_plane,
		subcommand_cell));
	return indicate_subcommand_pending_state(3,subcommand_menu_1,
		subcommand_cell,T);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-MOTION-IN-SUBCOMMAND-STATE */
Object mouse_motion_in_subcommand_state(mouse_pointer)
    Object mouse_pointer;
{
    Object subcommand_state, table_cell_qm, subcommand_menu_1;
    Object subcommand_menu_cell;

    x_note_fn_call(126,96);
    subcommand_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    table_cell_qm = cell_of_table_blackboard_function(mouse_pointer);
    if (subcommand_state) {
	subcommand_menu_1 = ISVREF(subcommand_state,(SI_Long)3L);
	subcommand_menu_cell = ISVREF(subcommand_state,(SI_Long)5L);
	return indicate_subcommand_pending_state(3,subcommand_menu_1,
		subcommand_menu_cell,EQ(table_cell_qm,
		subcommand_menu_cell) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-UP-IN-SUBCOMMAND-STATE */
Object mouse_up_in_subcommand_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, subcommand_state, table_cell_qm;
    Object text_cell_of_button_qm, subcommand_menu_1, subcommand_menu_cell;
    Object do_it_qm, command_function_qm, function_arglist_qm, button_info;
    Object sub_class_bit_vector, s, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(126,97);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    subcommand_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    table_cell_qm = cell_of_table_blackboard_function(mouse_pointer);
    text_cell_of_button_qm = 
	    text_cell_of_table_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && subcommand_state) {
	mouse_motion_in_subcommand_state(mouse_pointer_1);
	subcommand_menu_1 = ISVREF(subcommand_state,(SI_Long)3L);
	subcommand_menu_cell = ISVREF(subcommand_state,(SI_Long)5L);
	do_it_qm = text_cell_of_button_qm ? (EQ(text_cell_of_button_qm,
		subcommand_menu_cell) ? T : Nil) : EQ(table_cell_qm,
		subcommand_menu_cell) ? T : Nil;
	command_function_qm = ISVREF(subcommand_menu_1,(SI_Long)27L);
	function_arglist_qm = ISVREF(subcommand_menu_1,(SI_Long)28L);
	if (text_cell_of_button_qm)
	    button_info = getf(CADR(text_cell_of_button_qm),
		    Qspecial_case_qm,_);
	else {
	    if (table_cell_qm && ATOM(table_cell_qm)) {
		sub_class_bit_vector = ISVREF(ISVREF(table_cell_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Icon_cell_class_description,(SI_Long)18L));
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
	    if (temp) {
		s = first_subblock(table_cell_qm);
		if (s) {
		    gensymed_symbol_3 = 
			    lookup_global_or_kb_specific_property_value(Qeditor_subcommand_button,
			    Class_description_gkbprop);
		    if (gensymed_symbol_3) {
			sub_class_bit_vector = ISVREF(ISVREF(s,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		button_info = temp ? get_slot_value_function(s,
			Qeditor_subcommand_name,Nil) : Nil;
	    }
	    else
		button_info = Nil;
	}
	if (do_it_qm) {
	    return_from_current_workstation_context(3,Qsubcommand,
		    subcommand_menu_1,button_info);
	    if (command_function_qm)
		return APPLY_3(command_function_qm,subcommand_menu_1,
			button_info,function_arglist_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return abort_current_workstation_context(Qsubcommand);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-EDIT-SUBCOMMAND-MENU */
Object make_edit_subcommand_menu()
{
    Object temp, temp_1, temp_2, choices;

    x_note_fn_call(126,98);
    temp = get_edit_subcommand_menu_core_choices();
    temp_1 = get_kfep_edit_subcomand_choices_if_appropriate();
    temp_2 = get_hfep_edit_subcomand_choices_if_appropriate();
    choices = nconc2(temp,nconc2(temp_1,nconc2(temp_2,
	    get_cfep_edit_subcomand_choices_if_appropriate())));
    return make_subcommand_menu(2,choices,ISVREF(Fonts,(SI_Long)25L));
}

Object Edit_operation_subcommand_names = UNBOUND;

Object Edit_operation_subcommand_names_after_removals = UNBOUND;

Object Basic_core_edit_subcommand_choices = UNBOUND;

Object Core_edit_subcommand_choices = UNBOUND;

Object Core_edit_subcommand_choices_after_removals = UNBOUND;

/* GET-EDIT-SUBCOMMAND-MENU-CORE-CHOICES */
Object get_edit_subcommand_menu_core_choices()
{
    x_note_fn_call(126,99);
    return copy_and_translate_subcommand_choice_symbol_list(ISVREF(Editor_parameters,
	    (SI_Long)35L) ? Core_edit_subcommand_choices : 
	    Core_edit_subcommand_choices_after_removals);
}

Object Kfep_edit_subcommand_choices = UNBOUND;

/* GET-KFEP-EDIT-SUBCOMAND-CHOICES-IF-APPROPRIATE */
Object get_kfep_edit_subcomand_choices_if_appropriate()
{
    x_note_fn_call(126,100);
    if (EQ(ISVREF(Current_edit_state,(SI_Long)45L),Qjapanese))
	return copy_and_translate_subcommand_choice_symbol_list(Kfep_edit_subcommand_choices);
    else
	return VALUES_1(Nil);
}

Object Hfep_edit_subcommand_choices = UNBOUND;

/* GET-HFEP-EDIT-SUBCOMAND-CHOICES-IF-APPROPRIATE */
Object get_hfep_edit_subcomand_choices_if_appropriate()
{
    x_note_fn_call(126,101);
    if (EQ(ISVREF(Current_edit_state,(SI_Long)45L),Qkorean))
	return copy_and_translate_subcommand_choice_symbol_list(Hfep_edit_subcommand_choices);
    else
	return VALUES_1(Nil);
}

Object Cfep_edit_subcommand_choices = UNBOUND;

/* GET-CFEP-EDIT-SUBCOMAND-CHOICES-IF-APPROPRIATE */
Object get_cfep_edit_subcomand_choices_if_appropriate()
{
    x_note_fn_call(126,102);
    if (EQ(ISVREF(Current_edit_state,(SI_Long)45L),Qrussian))
	return copy_and_translate_subcommand_choice_symbol_list(Cfep_edit_subcommand_choices);
    else
	return VALUES_1(Nil);
}

/* COPY-AND-TRANSLATE-SUBCOMMAND-CHOICE-SYMBOL-LIST */
Object copy_and_translate_subcommand_choice_symbol_list(choice_symbol_list)
    Object choice_symbol_list;
{
    Object choice, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(126,103);
    choice = Nil;
    ab_loop_list_ = choice_symbol_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    slot_value_cons_1(translate_subcommand_menu_choice_as_appropriate(choice,
	    ISVREF(Current_edit_state,(SI_Long)45L)),Nil);
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

Object Built_in_subcommand_menu_choice_translations = UNBOUND;

/* TRANSLATE-SUBCOMMAND-MENU-CHOICE */
Object translate_subcommand_menu_choice(choice,language)
    Object choice, language;
{
    Object temp, current_localization_purpose_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(126,104);
    SAVE_STACK();
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = Current_localization_purpose_qm;
	if (temp);
	else
	    temp = Qbutton_label;
	current_localization_purpose_qm = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
		0);
	  SAVE_VALUES(translation_for_symbol_qm(2,choice,language));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* USE-BUILT-IN-SUBCOMMAND-MENU-CHOICE-TRANSLATION */
Object use_built_in_subcommand_menu_choice_translation(choice,language)
    Object choice, language;
{
    Object temp;

    x_note_fn_call(126,105);
    temp = assq_function(language,
	    Built_in_subcommand_menu_choice_translations);
    temp = assq_function(choice,CDR(temp));
    return VALUES_1(CDR(temp));
}

Object Include_original_choice_in_subcommand_menu_choice_translation_qm = UNBOUND;

static Object string_constant_17;  /* "~a ~a" */

/* TRANSLATE-SUBCOMMAND-MENU-CHOICE-AS-APPROPRIATE */
Object translate_subcommand_menu_choice_as_appropriate(choice,language_qm)
    Object choice, language_qm;
{
    Object translation_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temporary_text_string, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(126,106);
    if (language_qm) {
	translation_qm = translate_subcommand_menu_choice(choice,language_qm);
	if (translation_qm);
	else
	    translation_qm = 
		    use_built_in_subcommand_menu_choice_translation(choice,
		    language_qm);
    }
    else
	translation_qm = Nil;
    if (translation_qm) {
	if (Include_original_choice_in_subcommand_menu_choice_translation_qm) {
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
		      temporary_text_string = copy_symbol_name(2,choice,
			      Kfirst);
		      tformat(3,string_constant_17,temporary_text_string,
			      translation_qm);
		      reclaim_text_string(temporary_text_string);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = copy_text_string(translation_qm);
	return slot_value_cons_1(choice,temp);
    }
    else
	return VALUES_1(choice);
}

static Object Qcut;                /* cut */

static Object Qcopy;               /* copy */

static Object list_constant;       /* # */

/* UPDATE-EDIT-OPERATION-SUBCOMMANDS */
Object update_edit_operation_subcommands(edit_subcommand_menu)
    Object edit_subcommand_menu;
{
    Object command, ab_loop_list_;
    char cannot_transfer;

    x_note_fn_call(126,107);
    if ( !TRUEP(Keep_edit_workspace_hidden_no_matter_what_qm)) {
	enable_or_disable_subcommand(3,edit_subcommand_menu,Qcut, 
		!TRUEP(text_can_be_cut_within_editor_p()) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu,Qcopy, 
		!TRUEP(text_can_be_copied_within_editor_p()) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu,Qpaste, 
		!TRUEP(text_can_be_pasted_in_current_workstation_p()) ? T :
		 Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu,Qdelete, 
		!TRUEP(text_can_be_deleted_within_editor_p()) ? T : Nil);
	cannot_transfer =  !TRUEP(text_can_be_transferred_within_editor_p());
	command = Nil;
	ab_loop_list_ = list_constant;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	command = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	enable_or_disable_subcommand(3,edit_subcommand_menu,command,
		cannot_transfer ? T : Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-EDIT-OPERATION-SUBCOMMANDS-IN-CURRENT-EDITOR */
Object update_edit_operation_subcommands_in_current_editor()
{
    Object edit_subcommand_menu_qm;

    x_note_fn_call(126,108);
    edit_subcommand_menu_qm = ISVREF(Current_edit_state,(SI_Long)43L);
    if (edit_subcommand_menu_qm)
	update_edit_operation_subcommands(edit_subcommand_menu_qm);
    return VALUES_1(Nil);
}

/* DISABLE-TEXT-REGION-OPERATION-SUBCOMMANDS-IN-CURRENT-EDITOR */
Object disable_text_region_operation_subcommands_in_current_editor()
{
    Object edit_subcommand_menu_qm, command, ab_loop_list_;

    x_note_fn_call(126,109);
    edit_subcommand_menu_qm = ISVREF(Current_edit_state,(SI_Long)43L);
    if (edit_subcommand_menu_qm) {
	command = Nil;
	ab_loop_list_ = Edit_operation_subcommand_names;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	command = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(command,Qpaste))
	    enable_or_disable_subcommand(3,edit_subcommand_menu_qm,command,T);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcancel;             /* cancel */

static Object Qkatakana;           /* katakana */

static Object Qhiragana;           /* hiragana */

static Object Qenglish;            /* english */

/* INITIALIZE-EDIT-SUBCOMMAND-MENU */
Object initialize_edit_subcommand_menu(edit_subcommand_menu)
    Object edit_subcommand_menu;
{
    x_note_fn_call(126,110);
    enable_or_disable_subcommand(3,edit_subcommand_menu,Qcancel,Nil);
    if ( !TRUEP(use_return_key_as_end_key_in_current_editor_p()))
	enable_or_disable_subcommand(3,edit_subcommand_menu,Qend,Nil);
    update_edit_operation_subcommands(edit_subcommand_menu);
    enable_or_disable_subcommand(3,edit_subcommand_menu,Qundo, 
	    !TRUEP(undo_or_redo_edit_possible_p(Nil)) ? T : Nil);
    enable_or_disable_subcommand(3,edit_subcommand_menu,Qredo, 
	    !TRUEP(undo_or_redo_edit_possible_p(T)) ? T : Nil);
    if (Kfep_capability_qm) {
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qkanji,Nil,Qoff);
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qkatakana,Nil,
		Qoff);
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qhiragana,Nil,
		Qoff);
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qenglish,Nil,Qon);
    }
    if (Hfep_capability_qm) {
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qenglish,Nil,Qon);
	enable_or_disable_subcommand(4,edit_subcommand_menu,Qhangul,Nil,Qoff);
    }
    enable_or_disable_subcommand(4,edit_subcommand_menu,Qenglish,Nil,Qon);
    return enable_or_disable_subcommand(4,edit_subcommand_menu,Qcyrillic,
	    Nil,Qoff);
}

static Object Qupdate;             /* update */

/* ENABLE-OR-DISABLE-EDIT-END-AND-UPDATE-BUTTONS */
Object enable_or_disable_edit_end_and_update_buttons(disable_case_qm)
    Object disable_case_qm;
{
    Object subcommand_menu_qm;

    x_note_fn_call(126,111);
    if ( !TRUEP(Keep_edit_workspace_hidden_no_matter_what_qm)) {
	subcommand_menu_qm = ISVREF(Current_edit_state,(SI_Long)43L);
	if (subcommand_menu_qm) {
	    if (use_return_key_as_end_key_in_current_editor_p())
		enable_or_disable_subcommand(3,subcommand_menu_qm,Qend,
			disable_case_qm);
	    if ( !TRUEP(ISVREF(Current_workstation_context,(SI_Long)3L)) 
		    &&  !TRUEP(ISVREF(Current_edit_state,(SI_Long)59L)))
		return enable_or_disable_subcommand(3,subcommand_menu_qm,
			Qupdate,disable_case_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qend_exit;           /* end-exit */

static Object Qinsert;             /* insert */

static Object Qmove;               /* move */

static Object Qcut_and_insert;     /* cut-and-insert */

static Object Qconvert;            /* convert */

static Object Qnext;               /* next */

static Object Qprevious;           /* previous */

static Object Qskip;               /* skip */

static Object Qaccept;             /* accept */

static Object Qexpand;             /* expand */

static Object Qshrink;             /* shrink */

/* DO-EDIT-SUBCOMMAND */
Object do_edit_subcommand(edit_context)
    Object edit_context;
{
    Object subcommand_menu_or_abort_flag, subcommand, current_edit_state;
    Object current_edit_workspace, svref_arg_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(126,112);
    subcommand_menu_or_abort_flag = ISVREF(Current_workstation,(SI_Long)33L);
    subcommand = ISVREF(Current_workstation,(SI_Long)34L);
    if ( !EQ(subcommand_menu_or_abort_flag,Kabort)) {
	current_edit_state = 
		Specific_structure_for_current_workstation_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		  0);
	    if (EQ(subcommand,Kabort))
		result = VALUES_1(Nil);
	    else if (EQ(subcommand,Qend) || EQ(subcommand,Qupdate)) {
		svref_arg_1 = Current_edit_state;
		SVREF(svref_arg_1,FIX((SI_Long)60L)) = Qend_exit;
		result = extend_parsing_as_appropriate(3,Qend,Nil,
			EQ(subcommand,Qupdate) ? T : Nil);
	    }
	    else if (EQ(subcommand,Qundo) || EQ(subcommand,Qredo))
		result = undo_or_redo_edit(EQ(subcommand,Qredo) ? T : Nil);
	    else if (EQ(subcommand,Qcancel))
		result = cancel_editing();
	    else if (EQ(subcommand,Qpaste))
		result = do_paste_within_editor();
	    else if (EQ(subcommand,Qcut))
		result = do_cut_within_editor(0);
	    else if (EQ(subcommand,Qcopy))
		result = do_copy_within_editor();
	    else if (EQ(subcommand,Qdelete))
		result = do_delete_within_editor();
	    else if (EQ(subcommand,Qinsert))
		result = do_insert_within_editor();
	    else if (EQ(subcommand,Qmove))
		result = do_move_within_editor();
	    else if (EQ(subcommand,Qcut_and_insert))
		result = do_cut_and_insert_within_editor();
	    else if (EQ(subcommand,Qkanji))
		result = enter_kana_conversion_mode(Nil);
	    else if (EQ(subcommand,Qkatakana))
		result = enter_kana_conversion_mode(Qkatakana);
	    else if (EQ(subcommand,Qhiragana))
		result = enter_kana_conversion_mode(Qhiragana);
	    else if (EQ(subcommand,Qenglish)) {
		exit_kfep_mode_if_necessary(0);
		exit_hangul_input_mode();
		result = exit_cyrillic_input_mode();
	    }
	    else if (EQ(subcommand,Qhangul))
		result = enter_hangul_input_mode();
	    else if (EQ(subcommand,Qcyrillic))
		result = enter_cyrillic_input_mode();
	    else if (EQ(subcommand,Qconvert) || EQ(subcommand,Qnext))
		result = do_trial_kfep_conversion(1,Nil);
	    else if (EQ(subcommand,Qprevious))
		result = do_trial_kfep_conversion(1,T);
	    else if (EQ(subcommand,Qskip))
		result = skip_kfep_conversion();
	    else if (EQ(subcommand,Qaccept))
		result = accept_kfep_conversion();
	    else if (EQ(subcommand,Qexpand))
		result = expand_or_shrink_kfep_conversion_text_region(T);
	    else if (EQ(subcommand,Qshrink))
		result = expand_or_shrink_kfep_conversion_text_region(Nil);
	    else
		result = VALUES_1(Qnil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_search_limit_1, Qkfep_search_limit_1);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_search_limit_2, Qkfep_search_limit_2);

/* ENTER-KANA-CONVERSION-MODE */
Object enter_kana_conversion_mode(kana_conversion_mode_qm)
    Object kana_conversion_mode_qm;
{
    Object svref_arg_1;

    x_note_fn_call(126,113);
    if ( !TRUEP(Ascii_to_kana_map) ||  !TRUEP(kana_conversion_mode_qm) &&  
	    !TRUEP(Kfep_converters_have_been_initialized_qm))
	initialize_kana_to_kanji_converters();
    if (kana_conversion_mode_qm || Kfep_converters_have_been_initialized_qm) {
	delete_kfep_conversion_text_region_if_any(1,T);
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)50L)) = kana_conversion_mode_qm;
	set_up_kfep_conversion_text_region(5,ISVREF(Current_edit_state,
		(SI_Long)24L),ISVREF(Current_edit_state,(SI_Long)25L),Nil,
		Nil,T);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* EXIT-KFEP-MODE-IF-NECESSARY */
Object exit_kfep_mode_if_necessary varargs_1(int, n)
{
    Object do_not_extend_parsing_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,114);
    INIT_ARGS_nonrelocating();
    do_not_extend_parsing_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    delete_kfep_conversion_text_region_if_any(1,T);
    update_kfep_buttons();
    if ( !TRUEP(do_not_extend_parsing_qm))
	return extend_parsing_as_appropriate(1,T);
    else
	return VALUES_1(Nil);
}

/* DO-TRIAL-KFEP-CONVERSION */
Object do_trial_kfep_conversion varargs_1(int, n)
{
    Object previous_case_qm;
    Object arrow_direction_qm, text_region, choices, number_of_choices;
    Object choice_index_qm, new_choice_index_qm, delta_index_qm, svref_arg_1;
    Object svref_new_value;
    SI_Long temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,115);
    INIT_ARGS_nonrelocating();
    previous_case_qm = REQUIRED_ARG_nonrelocating();
    arrow_direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_region = ISVREF(Current_edit_state,(SI_Long)46L);
    choices = ISVREF(Current_edit_state,(SI_Long)47L);
    number_of_choices = length(choices);
    choice_index_qm = ISVREF(Current_edit_state,(SI_Long)48L);
    if ( !TRUEP(choice_index_qm))
	new_choice_index_qm = FIX((SI_Long)0L);
    else if (arrow_direction_qm) {
	delta_index_qm = 
		get_kfep_conversion_choice_index_delta_for_arrow(arrow_direction_qm);
	if (delta_index_qm) {
	    temp = IFIX(FIXNUM_ADD(choice_index_qm,delta_index_qm));
	    new_choice_index_qm = FIX(MAX((SI_Long)0L,temp));
	}
	else
	    new_choice_index_qm = Nil;
    }
    else if (previous_case_qm) {
	temp = IFIX(FIXNUM_SUB1(choice_index_qm));
	new_choice_index_qm = FIX(MAX(temp,(SI_Long)0L));
    }
    else
	new_choice_index_qm = FIXNUM_ADD1(choice_index_qm);
    if (new_choice_index_qm) {
	if (EQ(CADR(choices),T))
	    update_kfep_conversion_choices_as_appropriate(4,Nil,
		    ISVREF(text_region,(SI_Long)18L),ISVREF(text_region,
		    (SI_Long)19L),T);
	if (choice_index_qm)
	    highlight_or_unhighlight_kfep_conversion_choice(chestnut_modf_function(choice_index_qm,
		    number_of_choices),T);
	highlight_or_unhighlight_kfep_conversion_choice(chestnut_modf_function(new_choice_index_qm,
		number_of_choices),Nil);
	if ( !TRUEP(choice_index_qm)) {
	    svref_arg_1 = Current_edit_state;
	    svref_new_value = convert_text_region_to_text_string(1,
		    text_region);
	    SVREF(svref_arg_1,FIX((SI_Long)49L)) = svref_new_value;
	}
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)48L)) = new_choice_index_qm;
	do_kfep_conversion_edit(nth(chestnut_modf_function(new_choice_index_qm,
		number_of_choices),choices));
	return update_kfep_buttons();
    }
    else
	return VALUES_1(Nil);
}

/* SKIP-KFEP-CONVERSION */
Object skip_kfep_conversion()
{
    Object text_region;

    x_note_fn_call(126,116);
    text_region = ISVREF(Current_edit_state,(SI_Long)46L);
    return set_up_kfep_conversion_text_region(4,ISVREF(text_region,
	    (SI_Long)18L),ISVREF(text_region,(SI_Long)19L),T,
	    FIXNUM_EQ(ISVREF(text_region,(SI_Long)18L),ISVREF(text_region,
	    (SI_Long)16L)) ? (FIXNUM_EQ(ISVREF(text_region,(SI_Long)19L),
	    ISVREF(text_region,(SI_Long)17L)) ? T : Nil) : Qnil);
}

static Object string_constant_18;  /* "foo" */

/* ACCEPT-KFEP-CONVERSION */
Object accept_kfep_conversion()
{
    x_note_fn_call(126,117);
    note_kfep_conversion_choice(string_constant_18,
	    ISVREF(Current_edit_state,(SI_Long)47L),
	    ISVREF(Current_edit_state,(SI_Long)48L));
    return set_up_kfep_conversion_text_region(3,
	    ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),(SI_Long)18L),
	    ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),(SI_Long)19L),T);
}

/* EXPAND-OR-SHRINK-KFEP-CONVERSION-TEXT-REGION */
Object expand_or_shrink_kfep_conversion_text_region(expand_case_qm)
    Object expand_case_qm;
{
    Object svref_arg_1;

    x_note_fn_call(126,118);
    if (ISVREF(Current_edit_state,(SI_Long)48L)) {
	do_kfep_conversion_edit(ISVREF(Current_edit_state,(SI_Long)49L));
	highlight_or_unhighlight_kfep_conversion_choice(chestnut_modf_function(ISVREF(Current_edit_state,
		(SI_Long)48L),length(ISVREF(Current_edit_state,
		(SI_Long)47L))),T);
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)48L)) = Nil;
	update_kfep_buttons();
    }
    return update_kfep_conversion_choices_as_appropriate(1,expand_case_qm);
}

/* UNCONVERT-KFEP-CONVERSION-TEXT-REGION */
Object unconvert_kfep_conversion_text_region()
{
    Object svref_arg_1;

    x_note_fn_call(126,119);
    if (ISVREF(Current_edit_state,(SI_Long)48L)) {
	do_kfep_conversion_edit(ISVREF(Current_edit_state,(SI_Long)49L));
	highlight_or_unhighlight_kfep_conversion_choice(chestnut_modf_function(ISVREF(Current_edit_state,
		(SI_Long)48L),length(ISVREF(Current_edit_state,
		(SI_Long)47L))),T);
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)48L)) = Nil;
	update_kfep_buttons();
    }
    return update_kfep_conversion_choices_as_appropriate(3,Nil,
	    ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),(SI_Long)18L),
	    ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),(SI_Long)19L));
}

/* UPDATE-KFEP-BUTTONS */
Object update_kfep_buttons()
{
    Object edit_subcommand_menu_qm, kfep_conversion_text_region_qm;
    Object kana_conversion_mode_qm, kfep_conversion_choices_qm;
    Object kfep_conversion_choice_index_qm, adjacent_line_index_qm;
    Object adjacent_character_index_qm;
    char temp;
    Object result;

    x_note_fn_call(126,120);
    edit_subcommand_menu_qm = ISVREF(Current_edit_state,(SI_Long)43L);
    kfep_conversion_text_region_qm = ISVREF(Current_edit_state,(SI_Long)46L);
    kana_conversion_mode_qm = ISVREF(Current_edit_state,(SI_Long)50L);
    kfep_conversion_choices_qm = ISVREF(Current_edit_state,(SI_Long)47L);
    kfep_conversion_choice_index_qm = ISVREF(Current_edit_state,(SI_Long)48L);
    if (Kfep_capability_qm && edit_subcommand_menu_qm) {
	enable_or_disable_radio_button_subcommand(edit_subcommand_menu_qm,
		Qkanji, !(kfep_conversion_text_region_qm ?  
		!TRUEP(kana_conversion_mode_qm) : TRUEP(Nil)) ? T : Nil);
	enable_or_disable_radio_button_subcommand(edit_subcommand_menu_qm,
		Qkatakana, !(kfep_conversion_text_region_qm ? 
		EQ(kana_conversion_mode_qm,Qkatakana) : TRUEP(Nil)) ? T : Nil);
	enable_or_disable_radio_button_subcommand(edit_subcommand_menu_qm,
		Qhiragana, !(kfep_conversion_text_region_qm ? 
		EQ(kana_conversion_mode_qm,Qhiragana) : TRUEP(Nil)) ? T : Nil);
	enable_or_disable_radio_button_subcommand(edit_subcommand_menu_qm,
		Qenglish, ! !TRUEP(kfep_conversion_text_region_qm) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qconvert, 
		!(kfep_conversion_text_region_qm ? 
		kfep_conversion_choices_qm &&  
		!TRUEP(kfep_conversion_choice_index_qm) : TRUEP(Nil)) ? T :
		 Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qnext, 
		!(kfep_conversion_text_region_qm ? 
		kfep_conversion_choices_qm && 
		kfep_conversion_choice_index_qm : TRUEP(Nil)) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qprevious, 
		!(kfep_conversion_text_region_qm ? 
		kfep_conversion_choices_qm && 
		kfep_conversion_choice_index_qm &&  
		!(IFIX(kfep_conversion_choice_index_qm) == (SI_Long)0L) : 
		TRUEP(Nil)) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qskip, 
		!(kfep_conversion_text_region_qm ?  
		!TRUEP(kana_conversion_mode_qm) &&  
		!(kfep_conversion_choices_qm && 
		kfep_conversion_choice_index_qm) &&  
		!(FIXNUM_EQ(ISVREF(Current_edit_state,(SI_Long)24L),
		ISVREF(kfep_conversion_text_region_qm,(SI_Long)16L)) && 
		FIXNUM_EQ(ISVREF(Current_edit_state,(SI_Long)25L),
		ISVREF(kfep_conversion_text_region_qm,(SI_Long)17L))) : 
		TRUEP(Nil)) ? T : Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qaccept, 
		!(kfep_conversion_text_region_qm ? 
		kfep_conversion_choices_qm && 
		kfep_conversion_choice_index_qm : TRUEP(Nil)) ? T : Nil);
	if (kfep_conversion_text_region_qm) {
	    if (kfep_conversion_choices_qm) {
		result = find_position_adjacent_to_end_of_kfep_conversion_text_region(Nil);
		MVS_2(result,adjacent_line_index_qm,
			adjacent_character_index_qm);
		temp = adjacent_line_index_qm ?  
			!(FIXNUM_LT(ISVREF(Current_edit_state,
			(SI_Long)24L),adjacent_line_index_qm) || 
			FIXNUM_EQ(ISVREF(Current_edit_state,(SI_Long)24L),
			adjacent_line_index_qm) && 
			FIXNUM_LT(ISVREF(Current_edit_state,(SI_Long)25L),
			adjacent_character_index_qm)) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	enable_or_disable_subcommand(3,edit_subcommand_menu_qm,Qexpand, 
		!temp ? T : Nil);
	return enable_or_disable_subcommand(3,edit_subcommand_menu_qm,
		Qshrink, !(kfep_conversion_text_region_qm ? 
		TRUEP(kfep_conversion_choices_qm) : TRUEP(Nil)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SET-UP-KFEP-CONVERSION-TEXT-REGION */
Object set_up_kfep_conversion_text_region varargs_1(int, n)
{
    Object beginning_line_index, beginning_character_index;
    Object try_to_expand_qm, start_past_first_character_qm;
    Object do_not_update_kfep_conversion_choices_qm, line_index_qm;
    Object character_index_qm, character_qm, text_tail_qm, gensymed_symbol;
    Object svref_arg_1, svref_new_value;
    SI_Long arg, arg_1, arg_2;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,121);
    INIT_ARGS_nonrelocating();
    beginning_line_index = REQUIRED_ARG_nonrelocating();
    beginning_character_index = REQUIRED_ARG_nonrelocating();
    try_to_expand_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_past_first_character_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_update_kfep_conversion_choices_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    line_index_qm = Nil;
    character_index_qm = Nil;
    character_qm = Nil;
    text_tail_qm = find_text_tail_for_line(ISVREF(Current_edit_state,
	    (SI_Long)15L),beginning_line_index);
  next_loop:
    result = find_next_character_if_any(beginning_line_index,
	    beginning_character_index,text_tail_qm);
    MVS_4(result,line_index_qm,character_index_qm,text_tail_qm,character_qm);
    if (line_index_qm ?  !(FIXNUM_LT(ISVREF(Current_edit_state,
	    (SI_Long)24L),line_index_qm) || 
	    FIXNUM_EQ(ISVREF(Current_edit_state,(SI_Long)24L),
	    line_index_qm) && FIXNUM_LT(ISVREF(Current_edit_state,
	    (SI_Long)25L),character_index_qm)) : TRUEP(Nil)) {
	gensymed_symbol = character_qm;
	temp = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		IFIX(gensymed_symbol) <= (SI_Long)122L : TRUEP(Qnil);
	if (temp);
	else
	    temp = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		    IFIX(gensymed_symbol) <= (SI_Long)90L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(wide_character_member(character_qm,
		    Allowable_non_alpha_characters_in_kfep_conversions));
	if (temp);
	else {
	    arg = (SI_Long)12449L;
	    arg_1 = IFIX(character_qm);
	    arg_2 = (SI_Long)12534L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	if (temp);
	else {
	    arg = (SI_Long)12353L;
	    arg_1 = IFIX(character_qm);
	    arg_2 = (SI_Long)12435L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	temp =  !temp;
	if (temp);
	else
	    temp = TRUEP(start_past_first_character_qm);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	goto end_loop;
    beginning_line_index = line_index_qm;
    beginning_character_index = character_index_qm;
    start_past_first_character_qm = Nil;
    goto next_loop;
  end_loop:;
    if (ISVREF(Current_edit_state,(SI_Long)46L))
	delete_frame(ISVREF(Current_edit_state,(SI_Long)46L));
    if ( !TRUEP(do_not_update_kfep_conversion_choices_qm))
	erase_any_kfep_conversion_choices();
    if (ISVREF(Current_edit_state,(SI_Long)47L)) {
	reclaim_slot_value(ISVREF(Current_edit_state,(SI_Long)47L));
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)47L)) = Nil;
	if (ISVREF(Current_edit_state,(SI_Long)48L)) {
	    svref_arg_1 = Current_edit_state;
	    SVREF(svref_arg_1,FIX((SI_Long)48L)) = Nil;
	    reclaim_slot_value(ISVREF(Current_edit_state,(SI_Long)49L));
	    svref_arg_1 = Current_edit_state;
	    SVREF(svref_arg_1,FIX((SI_Long)49L)) = Nil;
	}
    }
    svref_arg_1 = Current_edit_state;
    svref_new_value = 
	    make_kfep_conversion_text_region(beginning_line_index,
	    beginning_character_index,
	    Default_kanji_conversion_text_region_highlight_color);
    SVREF(svref_arg_1,FIX((SI_Long)46L)) = svref_new_value;
    if ( !TRUEP(do_not_update_kfep_conversion_choices_qm))
	return update_kfep_conversion_choices_as_appropriate(1,
		try_to_expand_qm);
    else
	return update_kfep_buttons();
}

/* MAKE-KFEP-CONVERSION-TEXT-REGION */
Object make_kfep_conversion_text_region(beginning_line_index,
	    beginning_character_index,text_highlight_bar_color_qm)
    Object beginning_line_index, beginning_character_index;
    Object text_highlight_bar_color_qm;
{
    x_note_fn_call(126,122);
    return make_text_region(7,ISVREF(Current_edit_state,(SI_Long)13L),Nil,
	    beginning_line_index,beginning_character_index,Nil,Nil,
	    text_highlight_bar_color_qm);
}

/* DELETE-KFEP-CONVERSION-TEXT-REGION-IF-ANY */
Object delete_kfep_conversion_text_region_if_any varargs_1(int, n)
{
    Object do_not_update_menus_qm, svref_arg_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,123);
    INIT_ARGS_nonrelocating();
    do_not_update_menus_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(Current_edit_state,(SI_Long)46L)) {
	update_kfep_conversion_choices_as_appropriate(5,Nil,
		ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),
		(SI_Long)16L),ISVREF(ISVREF(Current_edit_state,
		(SI_Long)46L),(SI_Long)17L),Nil,do_not_update_menus_qm);
	delete_frame(ISVREF(Current_edit_state,(SI_Long)46L));
	svref_arg_1 = Current_edit_state;
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)46L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-KFEP-CONVERSION-CHOICES-AS-APPROPRIATE */
Object update_kfep_conversion_choices_as_appropriate varargs_1(int, n)
{
    Object try_to_expand_qm, end_line_index_qm, end_character_index_qm;
    Object must_compute_all_choices_qm, do_not_update_menus_or_buttons_qm;
    Object text_region, end_line_index, end_character_index;
    Object line_index_for_new_choices_qm, character_index_for_new_choices_qm;
    Object new_choices, minimum_number_of_gensym_characters_to_convert;
    Object line_index, character_index, text_tail, line_index_qm;
    Object character_index_qm, text_tail_qm, text_string_qm, choices;
    Object number_of_gensym_characters_to_convert_qm, old_choices_qm;
    Object svref_arg_1;
    SI_Long i, ab_loop_repeat_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(126,124);
    INIT_ARGS_nonrelocating();
    try_to_expand_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    must_compute_all_choices_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_update_menus_or_buttons_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_region = ISVREF(Current_edit_state,(SI_Long)46L);
    if (try_to_expand_qm && FIXNUM_EQ(ISVREF(text_region,(SI_Long)18L),
	    ISVREF(text_region,(SI_Long)16L)) && 
	    FIXNUM_EQ(ISVREF(text_region,(SI_Long)19L),ISVREF(text_region,
	    (SI_Long)17L)))
	set_up_kfep_conversion_text_region(5,ISVREF(text_region,
		(SI_Long)16L),ISVREF(text_region,(SI_Long)17L),T,Nil,T);
    text_region = ISVREF(Current_edit_state,(SI_Long)46L);
    end_line_index = end_line_index_qm;
    if (end_line_index);
    else
	end_line_index = ISVREF(text_region,(SI_Long)18L);
    end_character_index = end_character_index_qm;
    if (end_character_index);
    else
	end_character_index = ISVREF(text_region,(SI_Long)19L);
    line_index_for_new_choices_qm = Nil;
    character_index_for_new_choices_qm = Nil;
    new_choices = Nil;
    minimum_number_of_gensym_characters_to_convert = FIX((SI_Long)1L);
    line_index = ISVREF(text_region,(SI_Long)16L);
    character_index = ISVREF(text_region,(SI_Long)17L);
    text_tail = find_text_tail_for_line(ISVREF(Current_edit_state,
	    (SI_Long)15L),line_index);
    if (try_to_expand_qm) {
	line_index_qm = Nil;
	character_index_qm = Nil;
	text_tail_qm = Nil;
	i = (SI_Long)1L;
      next_loop:
	result = find_next_character_if_any(line_index,character_index,
		text_tail);
	MVS_3(result,line_index_qm,character_index_qm,text_tail_qm);
	if ( !(line_index_qm ?  !(FIXNUM_LT(ISVREF(Current_edit_state,
		(SI_Long)24L),line_index_qm) || 
		FIXNUM_EQ(ISVREF(Current_edit_state,(SI_Long)24L),
		line_index_qm) && FIXNUM_LT(ISVREF(Current_edit_state,
		(SI_Long)25L),character_index_qm)) : TRUEP(Nil)))
	    goto end_loop;
	if (FIXNUM_LT(end_line_index,line_index_qm) || 
		FIXNUM_EQ(end_line_index,line_index_qm) && 
		FIXNUM_LT(end_character_index,character_index_qm)) {
	    if (i > IFIX(Kfep_search_limit_1))
		goto end_loop;
	}
	else
	    minimum_number_of_gensym_characters_to_convert = 
		    FIXNUM_ADD1(minimum_number_of_gensym_characters_to_convert);
	line_index = line_index_qm;
	character_index = character_index_qm;
	text_tail = text_tail_qm;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else if ( !(FIXNUM_EQ(end_line_index,line_index) && 
	    FIXNUM_EQ(end_character_index,character_index))) {
	line_index = end_line_index;
	character_index = end_character_index;
	text_tail = find_text_tail_for_line(ISVREF(Current_edit_state,
		(SI_Long)15L),line_index);
	if ( !TRUEP(end_line_index_qm)) {
	    result = find_previous_character_if_any(line_index,
		    character_index,text_tail,ISVREF(Current_edit_state,
		    (SI_Long)15L));
	    MVS_3(result,line_index,character_index,text_tail);
	}
    }
    if ( !(FIXNUM_EQ(line_index,ISVREF(text_region,(SI_Long)16L)) && 
	    FIXNUM_EQ(character_index,ISVREF(text_region,(SI_Long)17L)))) {
	text_string_qm =  !TRUEP(ISVREF(Current_edit_state,(SI_Long)50L)) ?
		 convert_text_region_to_text_string(3,text_region,
		line_index,character_index) : Nil;
	if (text_string_qm)
	    result = search_for_longest_prefix_with_kfep_word_choices(3,
		    text_string_qm,
		    minimum_number_of_gensym_characters_to_convert, 
		    !TRUEP(must_compute_all_choices_qm) ? T : Nil);
	else
	    result = VALUES_1(Nil);
	MVS_2(result,choices,number_of_gensym_characters_to_convert_qm);
	if (choices) {
	    new_choices = choices;
	    line_index_for_new_choices_qm = ISVREF(text_region,(SI_Long)16L);
	    character_index_for_new_choices_qm = ISVREF(text_region,
		    (SI_Long)17L);
	    text_tail = find_text_tail_for_line(ISVREF(Current_edit_state,
		    (SI_Long)15L),line_index_for_new_choices_qm);
	    ab_loop_repeat_ = IFIX(number_of_gensym_characters_to_convert_qm);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    result = find_next_character_if_any(line_index_for_new_choices_qm,
		    character_index_for_new_choices_qm,text_tail);
	    MVS_3(result,line_index_for_new_choices_qm,
		    character_index_for_new_choices_qm,text_tail);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if (text_string_qm)
	    reclaim_text_string(text_string_qm);
    }
    if ( !TRUEP(new_choices) &&  !TRUEP(try_to_expand_qm) && 
		end_line_index_qm) {
	line_index_for_new_choices_qm = ISVREF(text_region,(SI_Long)16L);
	character_index_for_new_choices_qm = ISVREF(text_region,(SI_Long)17L);
    }
    if (line_index_for_new_choices_qm) {
	old_choices_qm = ISVREF(Current_edit_state,(SI_Long)47L);
	update_text_region(3,text_region,line_index_for_new_choices_qm,
		character_index_for_new_choices_qm);
	if (old_choices_qm) {
	    erase_any_kfep_conversion_choices();
	    reclaim_slot_value(old_choices_qm);
	    if (ISVREF(Current_edit_state,(SI_Long)48L)) {
		svref_arg_1 = Current_edit_state;
		SVREF(svref_arg_1,FIX((SI_Long)48L)) = Nil;
		reclaim_slot_value(ISVREF(Current_edit_state,(SI_Long)49L));
		svref_arg_1 = Current_edit_state;
		SVREF(svref_arg_1,FIX((SI_Long)49L)) = Nil;
	    }
	}
	svref_arg_1 = Current_edit_state;
	SVREF(svref_arg_1,FIX((SI_Long)47L)) = new_choices;
	put_up_kfep_conversion_choices(old_choices_qm);
    }
    if ( !TRUEP(do_not_update_menus_or_buttons_qm))
	return update_kfep_buttons();
    else
	return VALUES_1(Nil);
}

/* PUT-UP-KFEP-CONVERSION-CHOICES */
Object put_up_kfep_conversion_choices(old_choices_qm)
    Object old_choices_qm;
{
    Object kfep_conversion_choices_qm;
    Object temporary_information_on_edit_workspace_qm;
    Object move_temporary_information_qm, kfep_conversion_choice_menu, temp;
    Object gensymed_symbol, temp_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(126,125);
    kfep_conversion_choices_qm = ISVREF(Current_edit_state,(SI_Long)47L);
    temporary_information_on_edit_workspace_qm = ISVREF(Current_edit_state,
	    (SI_Long)33L);
    move_temporary_information_qm = 
	    temporary_information_on_edit_workspace_qm ? ( 
	    !TRUEP(old_choices_qm) ? kfep_conversion_choices_qm :  
	    !TRUEP(kfep_conversion_choices_qm) ? T : Nil) : Qnil;
    if (move_temporary_information_qm)
	erase_any_temporary_information_on_edit_workspace(1,Nil);
    if (kfep_conversion_choices_qm &&  
		!EQ(CADR(kfep_conversion_choices_qm),T)) {
	kfep_conversion_choice_menu = 
		make_kfep_conversion_choice_menu(kfep_conversion_choices_qm);
	temp = ISVREF(Current_edit_state,(SI_Long)12L);
	gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)13L),
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(Current_edit_workspace,(SI_Long)17L));
	temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(ISVREF(Current_edit_state,(SI_Long)13L),
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(Current_edit_workspace,(SI_Long)17L));
	temp_2 = ISVREF(Current_edit_state,(SI_Long)70L);
	if (temp_2);
	else
	    temp_2 = FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(temp_2);
	add_to_workspace(6,kfep_conversion_choice_menu,temp,temp_1,
		FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
		gensymed_symbol_3),T,T);
	if (ISVREF(Current_edit_state,(SI_Long)48L))
	    highlight_or_unhighlight_kfep_conversion_choice(chestnut_modf_function(ISVREF(Current_edit_state,
		    (SI_Long)48L),length(ISVREF(Current_edit_state,
		    (SI_Long)47L))),Nil);
    }
    if (move_temporary_information_qm)
	return extend_parsing_as_appropriate(1,T);
    else
	return VALUES_1(Nil);
}

static Object Qkfep_conversion_choice_menu;  /* kfep-conversion-choice-menu */

/* MAKE-KFEP-CONVERSION-CHOICE-MENU */
Object make_kfep_conversion_choice_menu(kfep_conversion_choices)
    Object kfep_conversion_choices;
{
    Object remaining_choices, total_number_of_choices, format_name;
    Object token_menu_item_format, table_rows, ab_loopvar_, ab_loopvar__1;
    Object choice_string, ab_loop_list_, ab_loopvar__2, ab_loopvar__3, temp_1;
    SI_Long ideal_number_of_choices_per_row, temp, number_of_choices_per_row;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(126,126);
    remaining_choices = kfep_conversion_choices;
    ideal_number_of_choices_per_row = (SI_Long)7L;
    total_number_of_choices = length(kfep_conversion_choices);
    temp = IFIX(ceiling(total_number_of_choices,FIX((SI_Long)3L)));
    temp = MAX(ideal_number_of_choices_per_row,temp);
    number_of_choices_per_row = MIN(IFIX(total_number_of_choices),temp);
    format_name = choose_token_menu_item_format_per_system_tables(1,Nil);
    token_menu_item_format = get_instance_with_name_if_any(Qformat_frame,
	    format_name);
    if (token_menu_item_format);
    else
	token_menu_item_format = make_format_frame(format_name);
    table_rows = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    choice_string = Nil;
    ab_loop_list_ = remaining_choices;
    ab_loop_repeat_ = number_of_choices_per_row;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    ab_loopvar__3 = slot_value_cons_1(make_text_cell(2,
	    convert_text_string_to_text(copy_text_string(choice_string)),
	    token_menu_item_format),Nil);
    if (ab_loopvar__2)
	M_CDR(ab_loopvar__2) = ab_loopvar__3;
    else
	ab_loopvar__1 = ab_loopvar__3;
    ab_loopvar__2 = ab_loopvar__3;
    goto next_loop_1;
  end_loop:
    temp_1 = ab_loopvar__1;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    ab_loopvar__1 = slot_value_cons_1(temp_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	table_rows = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    remaining_choices = nthcdr(FIX(number_of_choices_per_row),
	    remaining_choices);
    if ( !TRUEP(remaining_choices))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    temp_1 = table_rows;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return make_or_reformat_table(4,temp_1,Qsubcommand_menu_table_format,
	    Nil,Qkfep_conversion_choice_menu);
}

static Object Qforeground;         /* foreground */

static Object Qtext_region;        /* text-region */

/* HIGHLIGHT-OR-UNHIGHLIGHT-KFEP-CONVERSION-CHOICE */
Object highlight_or_unhighlight_kfep_conversion_choice(index_1,
	    unhighlight_case_qm)
    Object index_1, unhighlight_case_qm;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, kfep_conversion_choice_menu_qm;
    Object choice_index_so_far, row, ab_loop_list_, ab_loop_it_, cell;
    Object ab_loop_list__1, cell_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(2);

    x_note_fn_call(126,127);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(Current_edit_state,
	    (SI_Long)12L),(SI_Long)14L));
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
    superior_class_bit_number = 
	    IFIX(ISVREF(Kfep_conversion_choice_menu_class_description,
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
	kfep_conversion_choice_menu_qm = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    kfep_conversion_choice_menu_qm = Qnil;
  end_1:;
    if (kfep_conversion_choice_menu_qm) {
	choice_index_so_far = FIX((SI_Long)0L);
	row = Nil;
	ab_loop_list_ = ISVREF(kfep_conversion_choice_menu_qm,(SI_Long)19L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,1);
	  ab_loop_it_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  Row = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  cell = Nil;
	  ab_loop_list__1 = Row;
	  PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    Cell = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (FIXNUM_EQ(index_1,choice_index_so_far)) {
		ab_loop_it_ = Cell;
		goto end_2;
	    }
	    choice_index_so_far = FIXNUM_ADD1(choice_index_so_far);
	    goto next_loop_2;
	  end_loop_2:
	    ab_loop_it_ = Qnil;
	  end_2:;
	  POP_SPECIAL();
	  if (ab_loop_it_) {
	      cell_qm = ab_loop_it_;
	      goto end_3;
	  }
	  goto next_loop_1;
	end_loop_1:
	  cell_qm = Qnil;
	end_3:;
	POP_SPECIAL();
	if (cell_qm)
	    return highlight_or_unhighlight_cell(5,cell_qm,
		    kfep_conversion_choice_menu_qm,Qforeground,
		    unhighlight_case_qm,Qtext_region);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qup;                 /* up */

static Object Qdown;               /* down */

static Object Qleft;               /* left */

static Object Qright;              /* right */

/* GET-KFEP-CONVERSION-CHOICE-INDEX-DELTA-FOR-ARROW */
Object get_kfep_conversion_choice_index_delta_for_arrow(arrow_direction)
    Object arrow_direction;
{
    Object previous_index, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector;
    Object kfep_conversion_choice_menu_qm, table_rows, number_of_rows;
    Object number_of_cells_per_row, row_index, column_index;
    Object number_of_cells_in_last_row;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(126,128);
    previous_index = chestnut_modf_function(ISVREF(Current_edit_state,
	    (SI_Long)48L),length(ISVREF(Current_edit_state,(SI_Long)47L)));
    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(Current_edit_state,
	    (SI_Long)12L),(SI_Long)14L));
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
    superior_class_bit_number = 
	    IFIX(ISVREF(Kfep_conversion_choice_menu_class_description,
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
	kfep_conversion_choice_menu_qm = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    kfep_conversion_choice_menu_qm = Qnil;
  end_1:;
    if (kfep_conversion_choice_menu_qm) {
	table_rows = ISVREF(kfep_conversion_choice_menu_qm,(SI_Long)19L);
	number_of_rows = length(table_rows);
	number_of_cells_per_row = length(CAR(table_rows));
	result = ltruncate(previous_index,number_of_cells_per_row);
	MVS_2(result,row_index,column_index);
	if (EQ(arrow_direction,Qup)) {
	    if ( !(IFIX(row_index) == (SI_Long)0L))
		return VALUES_1(FIXNUM_NEGATE(number_of_cells_per_row));
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(arrow_direction,Qdown)) {
	    if ( !FIXNUM_EQ(row_index,FIXNUM_SUB1(number_of_rows))) {
		if (IFIX(row_index) == IFIX(number_of_rows) - (SI_Long)2L) {
		    number_of_cells_in_last_row = 
			    length(nth(FIXNUM_SUB1(number_of_rows),
			    table_rows));
		    if (FIXNUM_GT(column_index,
			    FIXNUM_SUB1(number_of_cells_in_last_row)))
			return VALUES_1(FIXNUM_ADD(FIXNUM_MINUS(number_of_cells_per_row,
				column_index),
				FIXNUM_SUB1(number_of_cells_in_last_row)));
		    else
			return VALUES_1(number_of_cells_per_row);
		}
		else
		    return VALUES_1(number_of_cells_per_row);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(arrow_direction,Qleft)) {
	    if ( !(IFIX(row_index) == (SI_Long)0L && IFIX(column_index) == 
		    (SI_Long)0L))
		return VALUES_1(FIX((SI_Long)-1L));
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(arrow_direction,Qright)) {
	    if ( !(FIXNUM_EQ(row_index,FIXNUM_SUB1(number_of_rows)) && 
		    FIXNUM_EQ(column_index,
		    FIXNUM_SUB1(length(nth(row_index,table_rows))))))
		return VALUES_1(FIX((SI_Long)1L));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ERASE-ANY-KFEP-CONVERSION-CHOICES */
Object erase_any_kfep_conversion_choices()
{
    x_note_fn_call(126,129);
    if (ISVREF(Current_edit_state,(SI_Long)47L))
	return delete_subblocks_of_class(Current_edit_workspace,
		Qkfep_conversion_choice_menu);
    else
	return VALUES_1(Nil);
}

/* DO-KFEP-CONVERSION-EDIT */
Object do_kfep_conversion_edit(choice_string)
    Object choice_string;
{
    Object text_region;

    x_note_fn_call(126,130);
    text_region = ISVREF(Current_edit_state,(SI_Long)46L);
    return change_edit_box(10,Nil,ISVREF(text_region,(SI_Long)16L),
	    ISVREF(text_region,(SI_Long)17L),ISVREF(text_region,
	    (SI_Long)18L),ISVREF(text_region,(SI_Long)19L),choice_string,
	    Nil,Nil,Nil,Qkfep_conversion);
}

/* DO-KFEP-CONVERSION-EDIT-FROM-OUTSIDE */
Object do_kfep_conversion_edit_from_outside(choice_string)
    Object choice_string;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(126,131);
    current_edit_state = Specific_structure_for_current_workstation_context;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    1);
      current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
	      0);
	do_kfep_conversion_edit(choice_string);
	result = accept_kfep_conversion();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* FIND-POSITION-ADJACENT-TO-END-OF-KFEP-CONVERSION-TEXT-REGION */
Object find_position_adjacent_to_end_of_kfep_conversion_text_region(backwards_case_qm)
    Object backwards_case_qm;
{
    Object line_index, character_index, text_tail;

    x_note_fn_call(126,132);
    line_index = ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),(SI_Long)18L);
    character_index = ISVREF(ISVREF(Current_edit_state,(SI_Long)46L),
	    (SI_Long)19L);
    text_tail = find_text_tail_for_line(ISVREF(Current_edit_state,
	    (SI_Long)15L),line_index);
    if (backwards_case_qm)
	return find_previous_character_if_any(line_index,character_index,
		text_tail,ISVREF(Current_edit_state,(SI_Long)15L));
    else
	return find_next_character_if_any(line_index,character_index,
		text_tail);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trace_parsing_context_p, Qtrace_parsing_context_p);

DEFINE_VARIABLE_WITH_SYMBOL(Trace_parsing_context_tokenizing_p, Qtrace_parsing_context_tokenizing_p);

Object The_type_description_of_parsing_token = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_parsing_tokens, Qchain_of_available_parsing_tokens);

DEFINE_VARIABLE_WITH_SYMBOL(Parsing_token_count, Qparsing_token_count);

Object Chain_of_available_parsing_tokens_vector = UNBOUND;

/* PARSING-TOKEN-STRUCTURE-MEMORY-USAGE */
Object parsing_token_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(126,133);
    temp = Parsing_token_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PARSING-TOKEN-COUNT */
Object outstanding_parsing_token_count()
{
    Object def_structure_parsing_token_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,134);
    gensymed_symbol = IFIX(Parsing_token_count);
    def_structure_parsing_token_variable = Chain_of_available_parsing_tokens;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_parsing_token_variable))
	goto end_loop;
    def_structure_parsing_token_variable = 
	    ISVREF(def_structure_parsing_token_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PARSING-TOKEN-1 */
Object reclaim_parsing_token_1(parsing_token)
    Object parsing_token;
{
    Object temp, svref_arg_2;

    x_note_fn_call(126,135);
    inline_note_reclaim_cons(parsing_token,Nil);
    temp = ISVREF(Chain_of_available_parsing_tokens_vector,
	    IFIX(Current_thread_index));
    SVREF(parsing_token,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_parsing_tokens_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = parsing_token;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PARSING-TOKEN */
Object reclaim_structure_for_parsing_token(parsing_token)
    Object parsing_token;
{
    x_note_fn_call(126,136);
    return reclaim_parsing_token_1(parsing_token);
}

static Object Qg2_defstruct_structure_name_parsing_token_g2_struct;  /* g2-defstruct-structure-name::parsing-token-g2-struct */

/* MAKE-PERMANENT-PARSING-TOKEN-STRUCTURE-INTERNAL */
Object make_permanent_parsing_token_structure_internal()
{
    Object def_structure_parsing_token_variable;
    Object defstruct_g2_parsing_token_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(126,137);
    def_structure_parsing_token_variable = Nil;
    atomic_incff_symval(Qparsing_token_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_parsing_token_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_parsing_token_variable = the_array;
	SVREF(defstruct_g2_parsing_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parsing_token_g2_struct;
	def_structure_parsing_token_variable = 
		defstruct_g2_parsing_token_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_parsing_token_variable);
}

/* MAKE-PARSING-TOKEN-1 */
Object make_parsing_token_1()
{
    Object def_structure_parsing_token_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(126,138);
    def_structure_parsing_token_variable = 
	    ISVREF(Chain_of_available_parsing_tokens_vector,
	    IFIX(Current_thread_index));
    if (def_structure_parsing_token_variable) {
	svref_arg_1 = Chain_of_available_parsing_tokens_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_parsing_token_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_parsing_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parsing_token_g2_struct;
    }
    else
	def_structure_parsing_token_variable = 
		make_permanent_parsing_token_structure_internal();
    inline_note_allocate_cons(def_structure_parsing_token_variable,Nil);
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_parsing_token_variable,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_parsing_token_variable);
}

/* PARSING-TOKEN-INCOMPLETE-P */
Object parsing_token_incomplete_p(parsing_token)
    Object parsing_token;
{
    Object temp;

    x_note_fn_call(126,139);
    if ( !TRUEP(ISVREF(parsing_token,(SI_Long)3L)) &&  
	    !TRUEP(ISVREF(parsing_token,(SI_Long)4L)))
	return VALUES_1( !TRUEP(ISVREF(parsing_token,(SI_Long)5L)) ? T : Nil);
    else if (ISVREF(parsing_token,(SI_Long)6L))
	return VALUES_1(Nil);
    else {
	temp = text_string_p(ISVREF(parsing_token,(SI_Long)4L));
	if (temp);
	else
	    temp =  !TRUEP(ISVREF(parsing_token,(SI_Long)5L)) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1( 
		    !TRUEP(unambiguous_parsing_token_p(parsing_token)) ? T 
		    : Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_parsing_context_text, Qcurrent_parsing_context_text);

DEFINE_VARIABLE_WITH_SYMBOL(Current_parsing_context_text_length, Qcurrent_parsing_context_text_length);

DEFINE_VARIABLE_WITH_SYMBOL(Current_parsing_context_line, Qcurrent_parsing_context_line);

DEFINE_VARIABLE_WITH_SYMBOL(Current_parsing_context_character, Qcurrent_parsing_context_character);

Object The_type_description_of_parsing_context = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_parsing_contexts, Qchain_of_available_parsing_contexts);

DEFINE_VARIABLE_WITH_SYMBOL(Parsing_context_count, Qparsing_context_count);

Object Chain_of_available_parsing_contexts_vector = UNBOUND;

/* PARSING-CONTEXT-STRUCTURE-MEMORY-USAGE */
Object parsing_context_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(126,140);
    temp = Parsing_context_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)111L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PARSING-CONTEXT-COUNT */
Object outstanding_parsing_context_count()
{
    Object def_structure_parsing_context_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,141);
    gensymed_symbol = IFIX(Parsing_context_count);
    def_structure_parsing_context_variable = 
	    Chain_of_available_parsing_contexts;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_parsing_context_variable))
	goto end_loop;
    def_structure_parsing_context_variable = 
	    ISVREF(def_structure_parsing_context_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PARSING-CONTEXT-1-1 */
Object reclaim_parsing_context_1_1(parsing_context)
    Object parsing_context;
{
    Object structure_being_reclaimed, thing, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(126,142);
    inline_note_reclaim_cons(parsing_context,Nil);
    structure_being_reclaimed = parsing_context;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(parsing_context,(SI_Long)1L));
      SVREF(parsing_context,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(parsing_context,(SI_Long)2L));
      SVREF(parsing_context,FIX((SI_Long)2L)) = Nil;
      reclaim_frame_serial_number(ISVREF(parsing_context,(SI_Long)4L));
      SVREF(parsing_context,FIX((SI_Long)4L)) = Nil;
      reclaim_edit_undo_or_redo_stack(ISVREF(parsing_context,(SI_Long)34L));
      SVREF(parsing_context,FIX((SI_Long)34L)) = Nil;
      reclaim_edit_undo_or_redo_stack(ISVREF(parsing_context,(SI_Long)35L));
      SVREF(parsing_context,FIX((SI_Long)35L)) = Nil;
      reclaim_chain_of_incomplete_phrases(ISVREF(parsing_context,
	      (SI_Long)36L));
      SVREF(parsing_context,FIX((SI_Long)36L)) = Nil;
      reclaim_vectors_for_phrase_conses(ISVREF(parsing_context,(SI_Long)37L));
      SVREF(parsing_context,FIX((SI_Long)37L)) = Nil;
      reclaim_text_strings_in_phrases(ISVREF(parsing_context,(SI_Long)39L));
      SVREF(parsing_context,FIX((SI_Long)39L)) = Nil;
      reclaim_managed_floats_in_phrases(ISVREF(parsing_context,(SI_Long)40L));
      SVREF(parsing_context,FIX((SI_Long)40L)) = Nil;
      reclaim_managed_longs_in_phrases(ISVREF(parsing_context,(SI_Long)41L));
      SVREF(parsing_context,FIX((SI_Long)41L)) = Nil;
      reclaim_most_recent_reason_for_bad_parse_qm(ISVREF(parsing_context,
	      (SI_Long)42L));
      SVREF(parsing_context,FIX((SI_Long)42L)) = Nil;
      reclaim_gensym_list_if_list(ISVREF(parsing_context,(SI_Long)43L));
      SVREF(parsing_context,FIX((SI_Long)43L)) = Nil;
      reclaim_slot_value(ISVREF(parsing_context,(SI_Long)47L));
      SVREF(parsing_context,FIX((SI_Long)47L)) = Nil;
      reclaim_slot_value(ISVREF(parsing_context,(SI_Long)49L));
      SVREF(parsing_context,FIX((SI_Long)49L)) = Nil;
      reclaim_hfep_hanc_type_function(ISVREF(parsing_context,(SI_Long)62L));
      SVREF(parsing_context,FIX((SI_Long)62L)) = Nil;
      reclaim_hfep_hanc_type_function(ISVREF(parsing_context,(SI_Long)63L));
      SVREF(parsing_context,FIX((SI_Long)63L)) = Nil;
      reclaim_gensym_tree_function(ISVREF(parsing_context,(SI_Long)74L));
      SVREF(parsing_context,FIX((SI_Long)74L)) = Nil;
      reclaim_sexp_annotation_hash_qm(ISVREF(parsing_context,(SI_Long)90L));
      SVREF(parsing_context,FIX((SI_Long)90L)) = Nil;
      reclaim_pending_procedure_signature_workspaces(ISVREF(parsing_context,
	      (SI_Long)91L));
      SVREF(parsing_context,FIX((SI_Long)91L)) = Nil;
      reclaim_frame_serial_number(ISVREF(parsing_context,(SI_Long)93L));
      SVREF(parsing_context,FIX((SI_Long)93L)) = Nil;
      reclaim_gensym_tree_function(ISVREF(parsing_context,(SI_Long)99L));
      SVREF(parsing_context,FIX((SI_Long)99L)) = Nil;
      thing = ISVREF(parsing_context,(SI_Long)100L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(parsing_context,FIX((SI_Long)100L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_parsing_contexts_vector,
	    IFIX(Current_thread_index));
    SVREF(parsing_context,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_parsing_contexts_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = parsing_context;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PARSING-CONTEXT */
Object reclaim_structure_for_parsing_context(parsing_context)
    Object parsing_context;
{
    x_note_fn_call(126,143);
    return reclaim_parsing_context_1_1(parsing_context);
}

static Object Qg2_defstruct_structure_name_parsing_context_g2_struct;  /* g2-defstruct-structure-name::parsing-context-g2-struct */

/* MAKE-PERMANENT-PARSING-CONTEXT-STRUCTURE-INTERNAL */
Object make_permanent_parsing_context_structure_internal()
{
    Object def_structure_parsing_context_variable;
    Object defstruct_g2_parsing_context_variable, the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(126,144);
    def_structure_parsing_context_variable = Nil;
    atomic_incff_symval(Qparsing_context_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_parsing_context_variable = Nil;
	gensymed_symbol_1 = (SI_Long)111L;
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
	defstruct_g2_parsing_context_variable = the_array;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parsing_context_g2_struct;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)21L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)22L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)23L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)24L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)25L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)26L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)27L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)28L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)29L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)30L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)31L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)32L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)33L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)34L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)35L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)36L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)37L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)38L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)39L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)40L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)41L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)42L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)43L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)44L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)45L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)46L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)47L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)48L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)49L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)50L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)51L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)52L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)53L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)54L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)55L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)56L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)57L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)58L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)59L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)60L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)61L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)62L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)63L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)64L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)65L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)66L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)67L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)68L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)69L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)70L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)71L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)72L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)73L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)74L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)75L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)76L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)77L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)78L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)79L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)80L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)81L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)82L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)83L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)84L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)85L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)86L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)87L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)88L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)89L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)90L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)91L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)92L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)93L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)94L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)95L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)96L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)97L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)98L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)99L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)100L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)101L)) = Nil;
	SVREF(defstruct_g2_parsing_context_variable,FIX((SI_Long)102L)) = Nil;
	def_structure_parsing_context_variable = 
		defstruct_g2_parsing_context_variable;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)19L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)20L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)21L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)22L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)23L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)24L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)25L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)26L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)28L)) = Nil;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)48L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_parsing_contexts_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_parsing_contexts_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_parsing_context_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_parsing_context_variable);
}

static Object array_constant;      /* # */

/* MAKE-PARSING-CONTEXT-1 */
Object make_parsing_context_1()
{
    Object def_structure_parsing_context_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(126,145);
    def_structure_parsing_context_variable = 
	    ISVREF(Chain_of_available_parsing_contexts_vector,
	    IFIX(Current_thread_index));
    if (def_structure_parsing_context_variable) {
	temp = Chain_of_available_parsing_contexts_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_parsing_context_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_parsing_context_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parsing_context_g2_struct;
    }
    else
	def_structure_parsing_context_variable = 
		make_permanent_parsing_context_structure_internal();
    inline_note_allocate_cons(def_structure_parsing_context_variable,Nil);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)29L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)33L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)37L)) = Nil;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)38L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)41L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)42L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)43L)) = Nil;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)44L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)46L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)49L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)50L)) = Nil;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)51L) = 
	    FIX((SI_Long)95L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)54L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)55L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)56L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)57L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)58L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)59L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)60L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)61L)) = Nil;
    temp = make_hfep_hanc_type_function();
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)62L)) = temp;
    temp = make_hfep_hanc_type_function();
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)63L)) = temp;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)64L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_parsing_context_variable,(SI_Long)65L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)66L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)67L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)68L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)69L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)70L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)71L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)72L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)73L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)74L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)75L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)76L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)77L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)78L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)79L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)80L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)81L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)82L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)83L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)84L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)85L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)86L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)87L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)88L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)89L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)90L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)91L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)92L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)93L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)94L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)95L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)96L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)97L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)98L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)99L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)100L)) = Nil;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)101L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)102L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)103L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)104L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)105L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)106L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)107L)) = Nil;
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)108L)) = Nil;
    ISVREF(def_structure_parsing_context_variable,(SI_Long)109L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_parsing_context_variable,FIX((SI_Long)110L)) = 
	    array_constant;
    return VALUES_1(def_structure_parsing_context_variable);
}

/* PARSING-CONTEXT-CURSOR-TOKEN-FUNCTION */
Object parsing_context_cursor_token_function(pc)
    Object pc;
{
    x_note_fn_call(126,146);
    return VALUES_1(ISVREF(pc,(SI_Long)105L));
}

/* PARSING-TOKEN-INCOMPLETE-PHRASES-FUNCTION */
Object parsing_token_incomplete_phrases_function(pt)
    Object pt;
{
    x_note_fn_call(126,147);
    return VALUES_1(ISVREF(pt,(SI_Long)6L));
}

/* INCOMPLETE-PHRASES-FOR-PREVIOUS-TOKEN */
Object incomplete_phrases_for_previous_token()
{
    Object temp;

    x_note_fn_call(126,148);
    if (SIMPLE_VECTOR_P(Current_edit_state) && 
	    EQ(ISVREF(Current_edit_state,(SI_Long)0L),
	    Qg2_defstruct_structure_name_parsing_context_g2_struct))
	temp = ISVREF(ISVREF(Current_edit_state,(SI_Long)105L),(SI_Long)6L);
    else {
	temp = ISVREF(Current_edit_state,(SI_Long)31L);
	temp = CAR(temp);
    }
    return VALUES_1(temp);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* DELETE-PARSING-CONTEXT */
Object delete_parsing_context(parsing_context)
    Object parsing_context;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,149);
    gensymed_symbol = ISVREF(parsing_context,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)1L);
    gensymed_symbol_1 = parsing_context;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-PARSING-CONTEXT */
Object clean_up_workstation_context_for_parsing_context(parsing_context)
    Object parsing_context;
{
    Object current_edit_state, first_token_incomplete_phrases, gensymed_symbol;
    Object gensymed_symbol_1;
    Declare_special(1);

    x_note_fn_call(126,150);
    current_edit_state = parsing_context;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      first_token_incomplete_phrases = ISVREF(ISVREF(parsing_context,
	      (SI_Long)103L),(SI_Long)6L);
      if (first_token_incomplete_phrases)
	  reclaim_phrase_rule_completions(ISVREF(CAR(first_token_incomplete_phrases),
		  (SI_Long)1L));
    next_loop:
      if ( !TRUEP(ISVREF(parsing_context,(SI_Long)105L)))
	  goto end_loop;
      remove_token_from_parsing_context(parsing_context);
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_parsing_context,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = parsing_context;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-PARSING-CONTEXT */
Object reclaim_parsing_context(parsing_context)
    Object parsing_context;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(126,151);
    if ( !TRUEP(string_equalw(ISVREF(parsing_context,(SI_Long)110L),
	    array_constant)))
	reclaim_text_string(ISVREF(parsing_context,(SI_Long)110L));
    gensymed_symbol = ISVREF(parsing_context,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)1L);
    gensymed_symbol_1 = parsing_context;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* PARSING-CONTEXT-P-FUNCTION */
Object parsing_context_p_function(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(126,152);
    temp = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_parsing_context_g2_struct) ? T : 
	    Nil) : Qnil;
    return VALUES_1(temp);
}

/* ADD-TOKEN-TO-PARSING-CONTEXT */
Object add_token_to_parsing_context(new_token,pc)
    Object new_token, pc;
{
    Object cursor_token, new_index, svref_new_value;

    x_note_fn_call(126,153);
    if (ISVREF(pc,(SI_Long)103L)) {
	cursor_token = ISVREF(pc,(SI_Long)105L);
	new_index = FIXNUM_ADD1(ISVREF(pc,(SI_Long)109L));
	SVREF(pc,FIX((SI_Long)109L)) = new_index;
	SVREF(cursor_token,FIX((SI_Long)1L)) = new_token;
	SVREF(new_token,FIX((SI_Long)2L)) = cursor_token;
	SVREF(new_token,FIX((SI_Long)12L)) = new_index;
	return VALUES_1(SVREF(pc,FIX((SI_Long)105L)) = new_token);
    }
    else {
	svref_new_value = ISVREF(pc,(SI_Long)109L);
	SVREF(pc,FIX((SI_Long)12L)) = svref_new_value;
	SVREF(pc,FIX((SI_Long)103L)) = new_token;
	return VALUES_1(SVREF(pc,FIX((SI_Long)105L)) = new_token);
    }
}

/* REMOVE-TOKEN-FROM-PARSING-CONTEXT */
Object remove_token_from_parsing_context(pc)
    Object pc;
{
    Object cursor_token_qm, previous_token;

    x_note_fn_call(126,154);
    cursor_token_qm = ISVREF(pc,(SI_Long)105L);
    if (cursor_token_qm) {
	previous_token = ISVREF(cursor_token_qm,(SI_Long)2L);
	if (previous_token)
	    SVREF(previous_token,FIX((SI_Long)1L)) = Nil;
	SVREF(pc,FIX((SI_Long)105L)) = previous_token;
	return reclaim_parsing_token_and_accompanying_data(cursor_token_qm);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PARSING-TOKEN-AND-ACCOMPANYING-DATA */
Object reclaim_parsing_token_and_accompanying_data(token)
    Object token;
{
    x_note_fn_call(126,155);
    if (ISVREF(token,(SI_Long)9L))
	reclaim_text_string(ISVREF(token,(SI_Long)9L));
    if (ISVREF(token,(SI_Long)10L))
	reclaim_grammar_tree_1(ISVREF(token,(SI_Long)10L));
    SVREF(token,FIX((SI_Long)10L)) = Nil;
    return reclaim_parsing_token_1(token);
}

/* CLEAR-PARSING-TOKENS */
Object clear_parsing_tokens(pc)
    Object pc;
{
    Object start_token, token;

    x_note_fn_call(126,156);
    if ( !TRUEP(ISVREF(pc,(SI_Long)11L))) {
	start_token = ISVREF(pc,(SI_Long)103L);
	token = ISVREF(start_token,(SI_Long)1L);
      next_loop:
	if ( !TRUEP(token))
	    goto end_loop;
	reclaim_parsing_token_and_accompanying_data(token);
	token = ISVREF(token,(SI_Long)1L);
	goto next_loop;
      end_loop:;
	SVREF(pc,FIX((SI_Long)105L)) = start_token;
	ISVREF(pc,(SI_Long)108L) = FIX((SI_Long)0L);
	ISVREF(pc,(SI_Long)109L) = FIX((SI_Long)0L);
	SVREF(pc,FIX((SI_Long)107L)) = Nil;
	return VALUES_1(SVREF(start_token,FIX((SI_Long)1L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-PARSING-CONTEXT */
Object clear_parsing_context(pc)
    Object pc;
{
    x_note_fn_call(126,157);
    clear_parsing_tokens(pc);
    if ( !TRUEP(string_equalw(ISVREF(pc,(SI_Long)110L),array_constant)))
	reclaim_text_string(ISVREF(pc,(SI_Long)110L));
    return VALUES_1(SVREF(pc,FIX((SI_Long)110L)) = array_constant);
}

static Object list_constant_1;     /* # */

/* CREATE-PARSING-CONTEXT */
Object create_parsing_context varargs_1(int, n)
{
    Object class_qm, slot_name_qm, type_of_slot_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, class_description_qm;
    Object slot_description_qm, type_of_slot, es, svref_new_value, edit_state;
    Object current_edit_state;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,158);
    INIT_ARGS_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    type_of_slot_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !(type_of_slot_qm || class_qm && slot_name_qm))
	return VALUES_1(Nil);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_qm,
	    Class_description_gkbprop);
    slot_description_qm = class_description_qm && slot_name_qm ? 
	    get_slot_description_of_class_description_function(slot_name_qm,
	    class_description_qm,Nil) : Qnil;
    type_of_slot = type_of_slot_qm;
    if (type_of_slot);
    else
	type_of_slot = class_description_qm ? assq_function(Qtype,
		slot_component_name_qm ? 
		get_slot_component_features(slot_name_qm,Nil,
		slot_component_name_qm) : ISVREF(slot_description_qm,
		(SI_Long)9L)) : list_constant_1;
    es = make_parsing_context_1();
    SVREF(es,FIX((SI_Long)6L)) = Nil;
    SVREF(es,FIX((SI_Long)5L)) = slot_name_qm;
    SVREF(es,FIX((SI_Long)9L)) = type_of_slot;
    SVREF(es,FIX((SI_Long)7L)) = slot_component_name_qm;
    SVREF(es,FIX((SI_Long)8L)) = slot_component_indicator_qm;
    svref_new_value = EQ(CADR(type_of_slot),Qfree) ? T : Nil;
    if (svref_new_value);
    else
	svref_new_value = EQ(CADR(type_of_slot),Qfree_text_attribute) ? T :
		 Nil;
    SVREF(es,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = 
	    get_natural_language_for_editor(Editor_specific_natural_language_override_qm);
    SVREF(es,FIX((SI_Long)78L)) = svref_new_value;
    svref_new_value = Editor_specific_natural_language_override_qm;
    if (svref_new_value);
    else
	svref_new_value = current_natural_language_for_editor();
    SVREF(es,FIX((SI_Long)45L)) = svref_new_value;
    edit_state = es;
    current_edit_state = edit_state;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      if (ISVREF(Current_edit_state,(SI_Long)11L))
	  initialize_parser_state_for_free_text();
      else
	  initialize_parser_state_for_current_parsing_context(type_of_slot);
      result = VALUES_1(edit_state);
    POP_SPECIAL();
    return result;
}

static Object Qirrelevant;         /* irrelevant */

/* INITIALIZE-PARSER-STATE-FOR-CURRENT-PARSING-CONTEXT */
Object initialize_parser_state_for_current_parsing_context(type_of_slot)
    Object type_of_slot;
{
    Object current_grammar, current_indicator_for_category_of_this_name;
    Object current_indicator_for_category_of_symbol_token, irrelevant_category;
    Object initial_token, temp, svref_new_value, temp_1;
    Declare_special(3);

    x_note_fn_call(126,159);
    current_grammar = Global_grammar;
    PUSH_SPECIAL_WITH_SYMBOL(Current_grammar,Qcurrent_grammar,current_grammar,
	    2);
      current_indicator_for_category_of_this_name = ISVREF(Current_grammar,
	      (SI_Long)3L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_this_name,Qcurrent_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
	      1);
	current_indicator_for_category_of_symbol_token = 
		ISVREF(Current_grammar,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_symbol_token,Qcurrent_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
		0);
	  irrelevant_category = 
		  get_or_make_category_for_category_symbol(Qirrelevant);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    initial_token = make_parsing_token_1();
    temp = Current_edit_state;
    svref_new_value = 
	    grammar_cons_1(make_phrase_rule_completion_1(irrelevant_category,
	    irrelevant_category,Nil),Nil);
    SVREF(temp,FIX((SI_Long)30L)) = svref_new_value;
    temp = Current_edit_state;
    ISVREF(temp,(SI_Long)109L) = FIX((SI_Long)0L);
    SVREF(initial_token,FIX((SI_Long)5L)) = T;
    ISVREF(initial_token,(SI_Long)7L) = FIX((SI_Long)0L);
    ISVREF(initial_token,(SI_Long)8L) = FIX((SI_Long)0L);
    ISVREF(initial_token,(SI_Long)12L) = FIX((SI_Long)0L);
    temp = Current_edit_state;
    current_grammar = Global_grammar;
    PUSH_SPECIAL_WITH_SYMBOL(Current_grammar,Qcurrent_grammar,current_grammar,
	    2);
      current_indicator_for_category_of_this_name = ISVREF(Current_grammar,
	      (SI_Long)3L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_this_name,Qcurrent_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
	      1);
	current_indicator_for_category_of_symbol_token = 
		ISVREF(Current_grammar,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_symbol_token,Qcurrent_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
		0);
	  temp_1 = 
		  get_or_make_category_for_category_symbol(SECOND(type_of_slot));
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    svref_new_value = 
	    make_incomplete_phrase_structure_1(grammar_cons_1(make_phrase_rule_completion_1(irrelevant_category,
	    temp_1,ISVREF(Current_edit_state,(SI_Long)30L)),Nil),Nil,Nil,
	    ISVREF(Current_edit_state,(SI_Long)36L));
    temp = phrase_cons(SVREF(temp,FIX((SI_Long)36L)) = svref_new_value,Nil);
    SVREF(initial_token,FIX((SI_Long)6L)) = temp;
    temp = Current_edit_state;
    ISVREF(temp,(SI_Long)108L) = FIX((SI_Long)0L);
    temp = Current_edit_state;
    SVREF(temp,FIX((SI_Long)110L)) = array_constant;
    return add_token_to_parsing_context(initial_token,Current_edit_state);
}

/* INITIALIZE-PARSER-STATE-FOR-FREE-TEXT */
Object initialize_parser_state_for_free_text()
{
    Object svref_arg_1;

    x_note_fn_call(126,160);
    svref_arg_1 = Current_edit_state;
    ISVREF(svref_arg_1,(SI_Long)108L) = FIX((SI_Long)0L);
    svref_arg_1 = Current_edit_state;
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)110L)) = array_constant);
}

static Object Qframe_is_null_or_reprocessed;  /* frame-is-null-or-reprocessed */

static Object Qparse_is_bad;       /* parse-is-bad */

static Object Qtext_is_incomplete;  /* text-is-incomplete */

static Object Qparse_is_incomplete;  /* parse-is-incomplete */

static Object Qambiguous_phrase;   /* ambiguous-phrase */

static Object Qparse_is_ambiguous;  /* parse-is-ambiguous */

/* END-EDITORLESS-PARSING */
Object end_editorless_parsing(pc,frame,editing_for_runtime_change_p)
    Object pc, frame, editing_for_runtime_change_p;
{
    Object x2, gensymed_symbol, current_edit_state, editing_free_text_qm;
    Object parse_result_or_marker, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value, text_of_definition_being_compiled;
    Object new_value_or_bad_phrase;
    Object explanatory_text_string_if_does_not_compile_qm;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(126,161);
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(frame,(SI_Long)3L);
	temp =  ! !(FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Qframe_is_null_or_reprocessed);
    else if (ISVREF(pc,(SI_Long)107L))
	return VALUES_1(Qparse_is_bad);
    else {
	current_edit_state = pc;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  editing_free_text_qm = ISVREF(pc,(SI_Long)11L);
	  parse_result_or_marker =  !TRUEP(editing_free_text_qm) ? 
		  extract_parse_result(pc) : Nil;
	  if (EQ(parse_result_or_marker,Qtext_is_incomplete))
	      result = VALUES_1(Qparse_is_incomplete);
	  else if (EQ(parse_result_or_marker,Qambiguous_phrase))
	      result = VALUES_1(Qparse_is_ambiguous);
	  else {
	      SVREF(pc,FIX((SI_Long)3L)) = frame;
	      frame_serial_number_setf_arg = ISVREF(frame,(SI_Long)3L);
	      old = ISVREF(pc,(SI_Long)4L);
	      new_1 = frame_serial_number_setf_arg;
	      svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		      (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		      frame_serial_number_setf_helper_1(old,new_1);
	      SVREF(pc,FIX((SI_Long)4L)) = svref_new_value;
	      SVREF(pc,FIX((SI_Long)57L)) = editing_for_runtime_change_p;
	      svref_new_value = 
		      convert_text_string_to_text(copy_text_string(ISVREF(pc,
		      (SI_Long)110L)));
	      SVREF(pc,FIX((SI_Long)15L)) = svref_new_value;
	      text_of_definition_being_compiled = ISVREF(pc,(SI_Long)15L);
	      new_value_or_bad_phrase = Nil;
	      explanatory_text_string_if_does_not_compile_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Text_of_definition_being_compiled,Qtext_of_definition_being_compiled,text_of_definition_being_compiled,
		      0);
		if ( !TRUEP(editing_free_text_qm)) {
		    result = compile_for_current_edit_state(parse_result_or_marker,
			    get_slot_value_compiler_for_current_edit_state_if_any(),
			    Nil);
		    MVS_2(result,new_value_or_bad_phrase,
			    explanatory_text_string_if_does_not_compile_qm);
		}
		if (EQ(new_value_or_bad_phrase,Bad_phrase) &&  
			!TRUEP(text_being_edited_may_have_no_value_p()))
		    result = VALUES_1(explanatory_text_string_if_does_not_compile_qm);
		else
		    result = install_current_edit_state_compiled_result(EQ(new_value_or_bad_phrase,
			    Bad_phrase) || editing_free_text_qm ? No_value 
			    : copy_for_slot_value(new_value_or_bad_phrase),
			    Nil,T);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	return result;
    }
}

/* ADVANCE-PARSING-CONTEXT-INDEX */
Object advance_parsing_context_index(pc,new_cursor_position)
    Object pc, new_cursor_position;
{
    x_note_fn_call(126,162);
    return advance_parsing_context(pc,text_string_substring(ISVREF(pc,
	    (SI_Long)110L),ISVREF(pc,(SI_Long)108L),new_cursor_position));
}

static Object array_constant_1;    /* # */

static Object Qafter_error;        /* after-error */

static Object list_constant_2;     /* # */

/* ADVANCE-PARSING-CONTEXT */
Object advance_parsing_context(pc,string_1)
    Object pc, string_1;
{
    Object current_edit_state, string_to_tokenize, text_start_index;
    Object cursor_token, prefix_string, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object decff_1_arg, svref_new_value, temp, current_parsing_context_text;
    Object current_parsing_context_text_length, current_parsing_context_line;
    Object current_parsing_context_character, parse_status_qm, problem_string;
    Object incff_1_arg;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(126,163);
    current_edit_state = pc;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    5);
      string_to_tokenize = Nil;
      text_start_index = ISVREF(pc,(SI_Long)108L);
      if (ISVREF(pc,(SI_Long)103L) && parsing_token_incomplete_p(ISVREF(pc,
	      (SI_Long)105L))) {
	  cursor_token = ISVREF(pc,(SI_Long)105L);
	  prefix_string = ISVREF(cursor_token,(SI_Long)9L);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
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
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		    3);
	      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		      2);
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    twrite(prefix_string);
		    twrite(string_1);
		    string_to_tokenize = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  decff_1_arg = text_string_length(prefix_string);
	  text_start_index = FIXNUM_MINUS(text_start_index,decff_1_arg);
	  decff_1_arg = text_string_length(prefix_string);
	  svref_new_value = FIXNUM_MINUS(ISVREF(pc,(SI_Long)108L),decff_1_arg);
	  SVREF(pc,FIX((SI_Long)108L)) = svref_new_value;
	  if (ISVREF(pc,(SI_Long)107L) && FIXNUM_LT(text_start_index,
		  ISVREF(pc,(SI_Long)107L)))
	      SVREF(pc,FIX((SI_Long)107L)) = Nil;
	  reclaim_text_string(string_1);
	  remove_token_from_parsing_context(pc);
      }
      else
	  string_to_tokenize = string_1;
      if (ISVREF(pc,(SI_Long)107L)) {
	  temp = copy_constant_wide_string_given_length(array_constant_1,
		  FIX((SI_Long)32L));
	  result = VALUES_2(Qafter_error,temp);
	  POP_SPECIAL();
	  goto end_advance_parsing_context;
      }
      current_parsing_context_text = slot_value_cons_1(string_to_tokenize,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_text,Qcurrent_parsing_context_text,current_parsing_context_text,
	      3);
	current_parsing_context_text_length = text_start_index;
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_text_length,Qcurrent_parsing_context_text_length,current_parsing_context_text_length,
		2);
	  current_parsing_context_line = FIX((SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_line,Qcurrent_parsing_context_line,current_parsing_context_line,
		  1);
	    current_parsing_context_character = 
		    memq_function(FIX(UBYTE_16_ISAREF_1(string_to_tokenize,
		    (SI_Long)0L)),Alphabet_whitespace_chars) ? 
		    relative_index_of_first_non_whitespace_character(string_to_tokenize,
		    FIX((SI_Long)0L)) : FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_character,Qcurrent_parsing_context_character,current_parsing_context_character,
		    0);
	      result = extend_parsing_context(1,Qend);
	      MVS_2(result,parse_status_qm,problem_string);
	      if ( !TRUEP(memq_function(parse_status_qm,list_constant_2))) {
		  svref_new_value = ISVREF(ISVREF(pc,(SI_Long)105L),
			  (SI_Long)8L);
		  SVREF(pc,FIX((SI_Long)107L)) = svref_new_value;
	      }
	      incff_1_arg = text_string_length(string_to_tokenize);
	      svref_new_value = FIXNUM_ADD(ISVREF(pc,(SI_Long)108L),
		      incff_1_arg);
	      SVREF(pc,FIX((SI_Long)108L)) = svref_new_value;
	      reclaim_slot_value_cons_1(Current_parsing_context_text);
	      if ( !(ISVREF(pc,(SI_Long)103L) && 
		      parsing_token_incomplete_p(ISVREF(pc,(SI_Long)105L)))) {
		  reclaim_text_string(string_1);
		  remove_token_from_parsing_context(Current_parsing_context_qm);
	      }
	      result = VALUES_2(parse_status_qm,problem_string);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
  end_advance_parsing_context:
    return result;
}

/* RELATIVE-INDEX-OF-FIRST-NON-WHITESPACE-CHARACTER */
Object relative_index_of_first_non_whitespace_character(string_1,initial_value)
    Object string_1, initial_value;
{
    Object indexed_character, ab_loop_iter_flag_;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(126,164);
    index_1 = IFIX(initial_value);
    ab_loop_bind_ = IFIX(FIXNUM_ADD(initial_value,lengthw(string_1)));
    indexed_character = FIX(UBYTE_16_ISAREF_1(string_1,index_1));
    ab_loop_iter_flag_ = T;
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	indexed_character = FIX(UBYTE_16_ISAREF_1(string_1,index_1));
    if ( !TRUEP(memq_function(indexed_character,Alphabet_whitespace_chars)))
	return VALUES_1(FIX(index_1));
    ab_loop_iter_flag_ = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(initial_value);
    return VALUES_1(Qnil);
}

/* RETREAT-PARSING-CONTEXT */
Object retreat_parsing_context(pc,index_1)
    Object pc, index_1;
{
    Object cursor_token, svref_new_value, parse_status, gripe;
    Object result;

    x_note_fn_call(126,165);
    if (ISVREF(pc,(SI_Long)107L) && FIXNUM_LT(index_1,ISVREF(pc,
	    (SI_Long)107L)))
	SVREF(pc,FIX((SI_Long)107L)) = Nil;
    if (IFIX(index_1) <= (SI_Long)0L)
	return clear_parsing_tokens(pc);
    else {
	cursor_token = ISVREF(pc,(SI_Long)105L);
      next_loop:
	if (FIXNUM_GT(index_1,ISVREF(cursor_token,(SI_Long)8L))) {
	    svref_new_value = ISVREF(cursor_token,(SI_Long)8L);
	    SVREF(pc,FIX((SI_Long)108L)) = svref_new_value;
	    goto end_loop;
	}
	else if (FIXNUM_LE(index_1,ISVREF(cursor_token,(SI_Long)8L))) {
	    remove_token_from_parsing_context(pc);
	    cursor_token = ISVREF(pc,(SI_Long)105L);
	}
	goto next_loop;
      end_loop:;
	result = advance_parsing_context_index(pc,index_1);
	MVS_2(result,parse_status,gripe);
	return VALUES_2(parse_status,gripe);
    }
}

/* ADVANCE-PARSING-CONTEXT-TOKEN-STREAM */
Object advance_parsing_context_token_stream()
{
    Object temp, temp_1, token_or_other_type_of_result_qm;
    Object type_of_token_or_prefix_token_string_qm;
    Object line_index_for_end_of_token, character_index_after_token;
    Object token_self_terminating_qm, parsing_token, svref_new_value_1;
    Object substring, start_index, original_string_qm, new_incomplete_text;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;
    char temp_2;
    Object result;

    x_note_fn_call(126,166);
    temp = G2_comment_tokenizer;
    temp_1 = text_string_length(CAR(Current_parsing_context_text));
    result = get_next_token_from_text_if_available(9,temp,FIX((SI_Long)1L),
	    temp_1,Current_parsing_context_line,
	    Current_parsing_context_character,Current_parsing_context_text,
	    T,Nil,Nil);
    MVS_6(result,token_or_other_type_of_result_qm,
	    type_of_token_or_prefix_token_string_qm,
	    line_index_for_end_of_token,character_index_after_token,temp_1,
	    token_self_terminating_qm);
    parsing_token = make_parsing_token_1();
    SVREF(parsing_token,FIX((SI_Long)3L)) = token_or_other_type_of_result_qm;
    SVREF(parsing_token,FIX((SI_Long)4L)) = 
	    type_of_token_or_prefix_token_string_qm;
    SVREF(parsing_token,FIX((SI_Long)5L)) = token_self_terminating_qm;
    gensymed_symbol = IFIX(Current_parsing_context_text_length);
    gensymed_symbol_1 =  !TRUEP(token_or_other_type_of_result_qm) ? 
	    IFIX(Current_parsing_context_character) : 
	    IFIX(relative_index_of_first_non_whitespace_character(CAR(Current_parsing_context_text),
	    Current_parsing_context_character));
    svref_new_value = gensymed_symbol + gensymed_symbol_1;
    ISVREF(parsing_token,(SI_Long)7L) = FIX(svref_new_value);
    gensymed_symbol = IFIX(Current_parsing_context_text_length);
    temp_1 = character_index_after_token;
    if (temp_1);
    else
	temp_1 = Current_parsing_context_character;
    gensymed_symbol_1 = IFIX(temp_1);
    svref_new_value = gensymed_symbol + gensymed_symbol_1;
    ISVREF(parsing_token,(SI_Long)8L) = FIX(svref_new_value);
    if ( !(token_self_terminating_qm && 
	    SYMBOLP(type_of_token_or_prefix_token_string_qm))) {
	if (text_string_p(type_of_token_or_prefix_token_string_qm) || 
		text_string_p(token_or_other_type_of_result_qm) ||  
		!TRUEP(token_or_other_type_of_result_qm) &&  
		!TRUEP(type_of_token_or_prefix_token_string_qm) || 
		CONSP(type_of_token_or_prefix_token_string_qm) && 
		(memq_function(Qsymbol,
		type_of_token_or_prefix_token_string_qm) || 
		CDR(type_of_token_or_prefix_token_string_qm))) {
	    svref_new_value_1 = 
		    text_string_substring(CAR(Current_parsing_context_text),
		    Current_parsing_context_character,
		    character_index_after_token);
	    SVREF(parsing_token,FIX((SI_Long)9L)) = svref_new_value_1;
	}
    }
    if (parsing_token_incomplete_p(parsing_token)) {
	if ( !TRUEP(equalw(array_constant,ISVREF(parsing_token,
		    (SI_Long)9L)))) {
	    substring = CAR(Current_parsing_context_text);
	    start_index = 
		    relative_index_of_first_non_whitespace_character(substring,
		    Current_parsing_context_character);
	    original_string_qm = ISVREF(parsing_token,(SI_Long)9L);
	    new_incomplete_text = text_string_substring(substring,
		    start_index,character_index_after_token);
	    SVREF(parsing_token,FIX((SI_Long)9L)) = new_incomplete_text;
	    if ( !TRUEP(token_or_other_type_of_result_qm)) {
		temp_1 = lengthw(new_incomplete_text);
		temp_2 = FIXNUM_NE(temp_1,
			FIXNUM_MINUS(ISVREF(parsing_token,(SI_Long)8L),
			ISVREF(parsing_token,(SI_Long)7L)));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = ISVREF(parsing_token,(SI_Long)7L);
		svref_new_value_1 = FIXNUM_ADD(temp_1,
			lengthw(new_incomplete_text));
		SVREF(parsing_token,FIX((SI_Long)8L)) = svref_new_value_1;
		svref_new_value_1 = ISVREF(parsing_token,(SI_Long)8L);
		SVREF(parsing_token,FIX((SI_Long)7L)) = svref_new_value_1;
	    }
	    if (original_string_qm)
		reclaim_text_string(original_string_qm);
	}
    }
    Current_parsing_context_line = line_index_for_end_of_token;
    Current_parsing_context_character = character_index_after_token;
    add_token_to_parsing_context(parsing_token,Current_edit_state);
    if (Current_parsing_context_character) {
	temp_1 = lengthw(CAR(Current_parsing_context_text));
	temp = FIXNUM_EQ(temp_1,Current_parsing_context_character) ? T : Nil;
    }
    else
	temp = T;
    temp_1 = parsing_token_incomplete_p(parsing_token);
    return VALUES_8(token_or_other_type_of_result_qm,
	    type_of_token_or_prefix_token_string_qm,
	    line_index_for_end_of_token,character_index_after_token,
	    token_self_terminating_qm,parsing_token,temp,temp_1);
}

static Object Qg2_comment;         /* g2-comment */

static Object list_constant_3;     /* # */

/* COMMENT-TOKEN-P */
Object comment_token_p(token)
    Object token;
{
    Object temp;

    x_note_fn_call(126,167);
    temp = EQ(ISVREF(token,(SI_Long)4L),Qg2_comment) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = ISVREF(token,(SI_Long)4L);
	return VALUES_1(EQUAL(temp,list_constant_3) ? T : Nil);
    }
}

/* MAYBE-SKIP-COMMENT-TOKENS */
Object maybe_skip_comment_tokens(token)
    Object token;
{
    x_note_fn_call(126,168);
  next_loop:
    if ( !TRUEP(comment_token_p(token)))
	goto end_loop;
    token = ISVREF(token,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(token);
}

static Object Qparsing_context_complete_status;  /* parsing-context-complete-status */

static Object Qso_far_so_good_2;   /* so-far-so-good-2 */

static Object Qso_far_so_good_3;   /* so-far-so-good-3 */

static Object array_constant_2;    /* # */

static Object Qproblem_token;      /* problem-token */

static Object array_constant_3;    /* # */

static Object Qincomplete_token;   /* incomplete-token */

static Object Qcomment;            /* comment */

static Object array_constant_4;    /* # */

static Object Qin_comment;         /* in-comment */

static Object Qquoted_character;   /* quoted-character */

static Object array_constant_5;    /* # */

static Object Qunknown_token_type;  /* unknown-token-type */

static Object Qellipsis;           /* ellipsis */

static Object array_constant_6;    /* # */

static Object Qfound_ellipsis;     /* found-ellipsis */

/* EXTEND-PARSING-CONTEXT */
Object extend_parsing_context varargs_1(int, n)
{
    Object parsing_extension_mode;
    Object do_not_suspend_qm, svref_arg_1, current_grammar;
    Object current_indicator_for_category_of_this_name;
    Object current_indicator_for_category_of_symbol_token;
    Object token_or_other_type_of_result_qm;
    Object type_of_token_or_prefix_token_string_qm;
    Object current_line_index_for_end_of_token;
    Object current_character_index_after_token, token_self_terminating_qm;
    Object incomplete_phrases_after_token;
    Object incomplete_phrases_for_previous_token_1, stop_after_p;
    Object incomplete_token_p, parsing_token, prior_cursor_token, temp;
    Object problem_string;
    SI_Long starting_time;
    char try_to_end_editing_qm;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(126,169);
    INIT_ARGS_nonrelocating();
    parsing_extension_mode = REQUIRED_ARG_nonrelocating();
    do_not_suspend_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    svref_arg_1 = Current_edit_state;
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = Nil;
    if ( !TRUEP(ISVREF(Current_edit_state,(SI_Long)11L))) {
	current_grammar = Global_grammar;
	PUSH_SPECIAL_WITH_SYMBOL(Current_grammar,Qcurrent_grammar,current_grammar,
		4);
	  current_indicator_for_category_of_this_name = 
		  ISVREF(Current_grammar,(SI_Long)3L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_this_name,Qcurrent_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
		  3);
	    current_indicator_for_category_of_symbol_token = 
		    ISVREF(Current_grammar,(SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_indicator_for_category_of_symbol_token,Qcurrent_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
		    2);
	      try_to_end_editing_qm = EQ(parsing_extension_mode,Qend);
	      token_or_other_type_of_result_qm = Nil;
	      type_of_token_or_prefix_token_string_qm = Nil;
	      current_line_index_for_end_of_token = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_line_index_for_end_of_token,Qcurrent_line_index_for_end_of_token,current_line_index_for_end_of_token,
		      1);
		current_character_index_after_token = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Current_character_index_after_token,Qcurrent_character_index_after_token,current_character_index_after_token,
			0);
		  token_self_terminating_qm = Nil;
		  starting_time = (SI_Long)0L;
		  incomplete_phrases_after_token = Nil;
		  incomplete_phrases_for_previous_token_1 = Nil;
		  stop_after_p = Nil;
		  incomplete_token_p = Nil;
		  parsing_token = Nil;
		  prior_cursor_token = Nil;
		next_loop:
		  prior_cursor_token = 
			  maybe_skip_comment_tokens(ISVREF(Current_edit_state,
			  (SI_Long)105L));
		  incomplete_phrases_for_previous_token_1 = 
			  ISVREF(prior_cursor_token,(SI_Long)6L);
		  incomplete_phrases_after_token = Nil;
		  result = advance_parsing_context_token_stream();
		  MVS_8(result,token_or_other_type_of_result_qm,
			  type_of_token_or_prefix_token_string_qm,
			  Current_line_index_for_end_of_token,
			  Current_character_index_after_token,
			  token_self_terminating_qm,parsing_token,
			  stop_after_p,incomplete_token_p);
		  if ( !TRUEP(parsing_token) ||  
			  !TRUEP(type_of_token_or_prefix_token_string_qm))
		      goto end_loop;
		  if ( !SYMBOLP(type_of_token_or_prefix_token_string_qm))
		      goto end_loop;
		  if (stop_after_p && incomplete_token_p)
		      goto end_loop;
		  if ( !EQ(type_of_token_or_prefix_token_string_qm,
			  Qg2_comment)) {
		      incomplete_phrases_after_token = 
			      advance_parsing_for_token(token_or_other_type_of_result_qm,
			      type_of_token_or_prefix_token_string_qm,
			      incomplete_phrases_for_previous_token_1);
		      SVREF(parsing_token,FIX((SI_Long)6L)) = 
			      incomplete_phrases_after_token;
		      if ( !TRUEP(incomplete_phrases_after_token) || 
			      stop_after_p)
			  goto end_loop;
		      SVREF(parsing_token,FIX((SI_Long)6L)) = 
			      incomplete_phrases_after_token;
		  }
		  if (Nil && FIX(starting_time) && try_to_end_editing_qm 
			  && do_not_suspend_qm) {
		      svref_arg_1 = Current_edit_state;
		      SVREF(svref_arg_1,FIX((SI_Long)27L)) = 
			      parsing_extension_mode;
		      result = VALUES_1(Nil);
		      goto end_1;
		  }
		  goto next_loop;
		end_loop:
		  if ( !TRUEP(type_of_token_or_prefix_token_string_qm) &&  
			  !TRUEP(token_or_other_type_of_result_qm)) {
		      update_parsing_context_completions_as_appropriate(3,
			      parsing_token,Nil,Nil);
		      if (ISVREF(parsing_token,(SI_Long)2L))
			  update_parsing_context_completions_as_appropriate(3,
				  ISVREF(parsing_token,(SI_Long)2L),Nil,Nil);
		      result = VALUES_1(Qparsing_context_complete_status);
		  }
		  else if (incomplete_phrases_after_token) {
		      update_parsing_context_completions_as_appropriate(3,
			      parsing_token,Nil,Nil);
		      result = VALUES_1(Qso_far_so_good_2);
		  }
		  else if (parsing_token_incomplete_p(parsing_token) && 
			  stop_after_p) {
		      compute_prompts_for_incomplete_token(parsing_token);
		      result = VALUES_1(Qso_far_so_good_3);
		  }
		  else if (type_of_token_or_prefix_token_string_qm && 
			  SYMBOLP(type_of_token_or_prefix_token_string_qm) 
			  || text_string_p(token_or_other_type_of_result_qm)) {
		      temp = ISVREF(Current_edit_state,(SI_Long)42L);
		      if (temp);
		      else {
			  svref_arg_1 = Current_edit_state;
			  temp = gensym_list_4(Nil,Nil,Nil,Nil);
			  SVREF(svref_arg_1,FIX((SI_Long)42L)) = temp;
		      }
		      if (CAR(temp)) {
			  temp = ISVREF(Current_edit_state,(SI_Long)42L);
			  if (temp);
			  else {
			      svref_arg_1 = Current_edit_state;
			      temp = gensym_list_4(Nil,Nil,Nil,Nil);
			      SVREF(svref_arg_1,FIX((SI_Long)42L)) = temp;
			  }
			  temp = reason_for_bad_parse_as_string(CAR(temp));
		      }
		      else
			  temp = array_constant_2;
		      problem_string = copy_text_string(temp);
		      result = VALUES_2(Qproblem_token,problem_string);
		  }
		  else if (text_string_p(type_of_token_or_prefix_token_string_qm)) 
			      {
		      if (update_parsing_context_completions_as_appropriate(4,
			      ISVREF(parsing_token,(SI_Long)2L),
			      token_or_other_type_of_result_qm,
			      type_of_token_or_prefix_token_string_qm,
			      parsing_token))
			  result = VALUES_1(Qso_far_so_good_3);
		      else {
			  temp = copy_text_string(array_constant_3);
			  result = VALUES_2(Qincomplete_token,temp);
		      }
		  }
		  else if (EQ(token_or_other_type_of_result_qm,Qcomment)) {
		      temp = copy_text_string(array_constant_4);
		      result = VALUES_2(Qin_comment,temp);
		  }
		  else if (EQ(token_or_other_type_of_result_qm,
			  Qquoted_character)) {
		      temp = copy_text_string(array_constant_5);
		      result = VALUES_2(Qunknown_token_type,temp);
		  }
		  else if (EQ(token_or_other_type_of_result_qm,Qellipsis)) {
		      temp = copy_text_string(array_constant_6);
		      result = VALUES_2(Qfound_ellipsis,temp);
		  }
		  else
		      result = VALUES_1(Qnil);
		  goto end_1;
		  result = VALUES_1(Qnil);
		end_1:;
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

/* EXTRACT-PARSE-RESULT */
Object extract_parse_result(parsing_context)
    Object parsing_context;
{
    Object parse_result, parse_trees, current_edit_state, cursor_token;
    Object final_token, incomplete_phrase, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;
    Declare_special(1);

    x_note_fn_call(126,170);
    parse_result = Nil;
    parse_trees = Nil;
    if (EQ(ISVREF(parsing_context,(SI_Long)105L),ISVREF(parsing_context,
	    (SI_Long)103L)))
	return VALUES_1(Qtext_is_incomplete);
    current_edit_state = parsing_context;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      cursor_token = ISVREF(parsing_context,(SI_Long)105L);
      final_token = FIXNUM_EQ(ISVREF(cursor_token,(SI_Long)7L),
	      ISVREF(cursor_token,(SI_Long)8L)) ? ISVREF(cursor_token,
	      (SI_Long)2L) : cursor_token;
      incomplete_phrase = Nil;
      ab_loop_list_ = ISVREF(final_token,(SI_Long)6L);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      incomplete_phrase = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (EQ(ISVREF(incomplete_phrase,(SI_Long)1L),ISVREF(parsing_context,
	      (SI_Long)30L))) {
	  temp = ISVREF(incomplete_phrase,(SI_Long)2L);
	  ab_loopvar__2 = phrase_cons(CAR(temp),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop:
      parse_trees = ab_loopvar_;
      goto end_1;
      parse_trees = Qnil;
    end_1:;
    POP_SPECIAL();
    if ( !TRUEP(parse_trees))
	parse_result = Qtext_is_incomplete;
    else if ( !TRUEP(CDR(parse_trees)))
	parse_result = copy_for_phrase(CAR(parse_trees));
    else
	parse_result = Qambiguous_phrase;
    return VALUES_1(parse_result);
}

/* UPDATE-PARSING-CONTEXT-COMPLETIONS-AS-APPROPRIATE */
Object update_parsing_context_completions_as_appropriate varargs_1(int, n)
{
    Object parsing_token, potential_token_types_qm, prefix_simple_string_qm;
    Object incomplete_token_qm, full_caps_string;
    Object menu_content_structure_for_token_position, temp, temp_1, temp_2;
    Object category_instance_menus;
    Object menu_content_structure_for_character_position, menus;
    char endable_here_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(126,171);
    INIT_ARGS_nonrelocating();
    parsing_token = REQUIRED_ARG_nonrelocating();
    potential_token_types_qm = REQUIRED_ARG_nonrelocating();
    prefix_simple_string_qm = REQUIRED_ARG_nonrelocating();
    incomplete_token_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Keep_edit_workspace_hidden_no_matter_what_qm)) {
	if (prefix_simple_string_qm) {
	    full_caps_string = string_upcasew(prefix_simple_string_qm);
	    prefix_simple_string_qm = full_caps_string;
	}
	parsing_token = maybe_skip_comment_tokens(parsing_token);
	menu_content_structure_for_token_position = 
		get_or_make_menu_content_structure_for_parsing_token(parsing_token);
	temp = EQ(CAR(menu_content_structure_for_token_position),Qend) ? 
		CADR(menu_content_structure_for_token_position) : 
		CAR(menu_content_structure_for_token_position);
	temp_1 = prefix_simple_string_qm;
	temp_2 = ISVREF(Current_edit_state,(SI_Long)71L);
	if (temp_2);
	else
	    temp_2 = ISVREF(Editor_parameters,(SI_Long)22L);
	category_instance_menus = make_category_instance_menus(temp,temp_1,
		temp_2);
	if (potential_token_types_qm)
	    temp_2 = 
		    make_menu_content_structure_for_character_position(menu_content_structure_for_token_position,
		    potential_token_types_qm,prefix_simple_string_qm);
	else if (category_instance_menus)
	    temp_2 = 
		    copy_list_using_grammar_conses_1(menu_content_structure_for_token_position);
	else
	    temp_2 = menu_content_structure_for_token_position;
	menu_content_structure_for_character_position = nconc2(temp_2,
		category_instance_menus);
	endable_here_qm = 
		EQ(CAR(menu_content_structure_for_character_position),Qend);
	menus = endable_here_qm ? 
		CDR(menu_content_structure_for_character_position) : 
		menu_content_structure_for_character_position;
	if (incomplete_token_qm)
	    SVREF(incomplete_token_qm,FIX((SI_Long)10L)) = menus;
	if (prefix_simple_string_qm)
	    reclaim_text_string(prefix_simple_string_qm);
	temp_2 = CAR(menus);
	if (temp_2)
	    return VALUES_1(temp_2);
	else
	    return VALUES_1(CDR(menus));
    }
    else
	return VALUES_1(Nil);
}

/* GET-OR-MAKE-MENU-CONTENT-STRUCTURE-FOR-PARSING-TOKEN */
Object get_or_make_menu_content_structure_for_parsing_token(parsing_token)
    Object parsing_token;
{
    Object temp, svref_new_value;

    x_note_fn_call(126,172);
    temp = ISVREF(parsing_token,(SI_Long)10L);
    if (temp)
	return VALUES_1(temp);
    else {
	svref_new_value = 
		make_menu_content_structure_for_token_position(ISVREF(parsing_token,
		(SI_Long)6L),ISVREF(Current_edit_state,(SI_Long)30L));
	return VALUES_1(SVREF(parsing_token,FIX((SI_Long)10L)) = 
		svref_new_value);
    }
}

/* COMPUTE-PROMPTS-FOR-INCOMPLETE-TOKEN */
Object compute_prompts_for_incomplete_token(incomplete_token)
    Object incomplete_token;
{
    Object prior_token_qm, potential_token_types_qm, token_type_as_list_qm;
    Object temp;

    x_note_fn_call(126,173);
    prior_token_qm = maybe_skip_comment_tokens(ISVREF(incomplete_token,
	    (SI_Long)2L));
    potential_token_types_qm =  
	    !TRUEP(text_string_p(ISVREF(incomplete_token,(SI_Long)4L))) ? 
	    ISVREF(incomplete_token,(SI_Long)4L) : Nil;
    token_type_as_list_qm = potential_token_types_qm ? 
	    (SYMBOLP(potential_token_types_qm) ? 
	    gensym_cons_1(potential_token_types_qm,Nil) : Nil) : Nil;
    if (prior_token_qm) {
	temp = token_type_as_list_qm;
	if (temp);
	else
	    temp = potential_token_types_qm;
	update_parsing_context_completions_as_appropriate(4,prior_token_qm,
		temp,ISVREF(incomplete_token,(SI_Long)9L),incomplete_token);
    }
    if (token_type_as_list_qm)
	return reclaim_gensym_list_1(token_type_as_list_qm);
    else
	return VALUES_1(Nil);
}

static Object string_constant_19;  /* "any ~(~a~)" */

/* COMPUTE-PARSING-CONTEXT-PROMPTS */
Object compute_parsing_context_prompts(parsing_token)
    Object parsing_token;
{
    Object menus, can_end_qm, categories, completions, prompts, choice;
    Object ab_loop_list_, temp, category_prompts, choice_list, ab_loop_list__1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object write_symbols_parsably_qm, write_symbols_in_lower_case_qm, tail;
    Object temp_1, schar_arg_2, schar_new_value, completion_prompts;
    Object longest_common_completion, master_string, pos, completion_string;
    Object match_length, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char thing;
    Declare_special(7);

    x_note_fn_call(126,174);
    menus = ISVREF(parsing_token,(SI_Long)10L);
    if (EQ(CAR(menus),Qend)) {
	menus = CDR(menus);
	can_end_qm = menus;
    }
    else
	can_end_qm = Nil;
    categories = CAR(menus);
    completions = CDR(menus);
    if (categories) {
	prompts = Nil;
	choice = Nil;
	ab_loop_list_ = categories;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	choice = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = tformat_text_string(2,string_constant_19,choice);
	prompts = slot_value_cons_1(temp,prompts);
	goto next_loop;
      end_loop:
	category_prompts = nreverse(prompts);
	goto end_1;
	category_prompts = Qnil;
      end_1:;
    }
    else
	category_prompts = Nil;
    if (completions) {
	prompts = Nil;
	choice_list = Nil;
	ab_loop_list_ = completions;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	choice_list = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	choice = Nil;
	ab_loop_list__1 = choice_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	choice = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		6);
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
		  5);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    4);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      3);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			2);
		  write_symbols_parsably_qm = T;
		  write_symbols_in_lower_case_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			    0);
		      if (ATOM(choice))
			  twrite(choice);
		      else {
			  tail = choice;
			next_loop_3:
			  if ( !TRUEP(tail))
			      goto end_loop_3;
			  twrite(CAR(tail));
			  if (CDR(tail)) {
			      if (EQ(Current_twriting_output_type,
				      Qwide_string)) {
				  thing = ' ';
				  twrite_wide_character(CHARACTERP(CHR(thing)) 
					  ? CHAR_CODE(CHR(thing)) : 
					  CHR(thing));
			      }
			      else {
				  if ( 
					  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					  Total_length_of_current_gensym_string))
				      extend_current_gensym_string(0);
				  temp_1 = Current_gensym_string;
				  schar_arg_2 = 
					  Fill_pointer_for_current_gensym_string;
				  thing = ' ';
				  schar_new_value = 
					  CODE_CHAR(CHARACTERP(CHR(thing)) 
					  ? CHAR_CODE(CHR(thing)) : 
					  CHR(thing));
				  SET_SCHAR(temp_1,schar_arg_2,
					  schar_new_value);
				  temp_1 = 
					  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				  Fill_pointer_for_current_gensym_string = 
					  temp_1;
			      }
			  }
			  tail = M_CDR(tail);
			  goto next_loop_3;
			end_loop_3:;
		      }
		    POP_SPECIAL();
		  POP_SPECIAL();
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	prompts = slot_value_cons_1(temp,prompts);
	goto next_loop_2;
      end_loop_2:;
	goto next_loop_1;
      end_loop_1:
	completion_prompts = nreverse(prompts);
	goto end_2;
	completion_prompts = Qnil;
      end_2:;
    }
    else
	completion_prompts = Nil;
    if ( !TRUEP(completion_prompts))
	longest_common_completion = Nil;
    else {
	master_string = CAR(completion_prompts);
	pos = text_string_length(master_string);
	completion_string = Nil;
	ab_loop_list_ = CDR(completion_prompts);
	match_length = Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	completion_string = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_2 = pos;
	temp = common_text_string_length(master_string,completion_string);
	match_length = FIXNUM_MIN(temp_2,temp);
	pos = match_length;
	if (IFIX(pos) == (SI_Long)0L)
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	longest_common_completion = IFIX(pos) == (SI_Long)0L ? Nil : 
		text_string_substring(master_string,FIX((SI_Long)0L),pos);
	goto end_3;
	longest_common_completion = Qnil;
      end_3:;
    }
    return VALUES_4(category_prompts,completion_prompts,
	    longest_common_completion,can_end_qm);
}

/* COMMON-TEXT-STRING-LENGTH */
Object common_text_string_length(ts1,ts2)
    Object ts1, ts2;
{
    Object index_past_difference, index_past_difference_or_zero;

    x_note_fn_call(126,175);
    index_past_difference = wide_string_compare(ts1,ts2,T,Nil);
    index_past_difference_or_zero = IFIX(index_past_difference) < 
	    (SI_Long)0L ? FIX((SI_Long)0L) : index_past_difference;
    if (IFIX(index_past_difference_or_zero) == (SI_Long)0L)
	return text_string_length(ts1);
    else
	return VALUES_1(FIXNUM_SUB1(index_past_difference_or_zero));
}

/* SHIFT-CURSOR-TOKEN */
Object shift_cursor_token(pc,new_position)
    Object pc, new_position;
{
    Object current_position, current_edit_state, parse_status, copy_of_gripe;
    Declare_special(1);
    Object result;

    x_note_fn_call(126,176);
    current_position = ISVREF(pc,(SI_Long)108L);
    current_edit_state = pc;
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      if (FIXNUM_GT(new_position,current_position)) {
	  result = advance_parsing_context_index(pc,new_position);
	  MVS_2(result,parse_status,copy_of_gripe);
	  result = VALUES_2(parse_status,copy_of_gripe);
      }
      else if (FIXNUM_LE(new_position,current_position))
	  result = retreat_parsing_context(pc,new_position);
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* COMPLETE-AND-EXTEND-FINAL-TOKEN-IF-NECESSARY */
Object complete_and_extend_final_token_if_necessary(pc)
    Object pc;
{
    Object current_edit_state, final, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object end_1, wide_string_bv16_1, temp, char_1, char_to_write_qm, temp_1;
    Object code, temp_2, aref_arg_2_1, next_parser_state;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(6);
    Object result;

    x_note_fn_call(126,177);
    if ( !TRUEP(ISVREF(pc,(SI_Long)11L))) {
	current_edit_state = pc;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		5);
	  final = determine_final_token(pc);
	  if (final && parsing_token_incomplete_p(final) && 
		  unambiguous_parsing_token_p(final) && 
		  incomplete_token_can_be_construed_as_complete(final) && 
		  ISVREF(final,(SI_Long)3L)) {
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
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    1);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			end_1 = Nil;
			if (end_1);
			else {
			    wide_string_bv16_1 = ISVREF(final,(SI_Long)3L);
			    length_1 = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
			    end_1 = 
				    FIX(UBYTE_16_ISAREF_1(wide_string_bv16_1,
				    length_1 - (SI_Long)2L) + 
				    ((UBYTE_16_ISAREF_1(wide_string_bv16_1,
				    length_1 - (SI_Long)1L) & 
				    (SI_Long)8191L) << (SI_Long)16L));
			}
			temp = Nil;
			if (temp);
			else
			    temp = FIX((SI_Long)0L);
			i = IFIX(temp);
			char_1 = Nil;
			char_to_write_qm = Nil;
		      next_loop:
			if ( !(i < IFIX(end_1)))
			    goto end_loop;
			char_1 = FIX(UBYTE_16_ISAREF_1(ISVREF(final,
				(SI_Long)3L),i));
			if (IFIX(char_1) == (SI_Long)64L) {
			    i = i + (SI_Long)1L;
			    temp_1 = FIX(i);
			    temp = Nil;
			    if (temp);
			    else {
				wide_string_bv16_1 = ISVREF(final,(SI_Long)3L);
				length_1 = 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
				temp = 
					FIX(UBYTE_16_ISAREF_1(wide_string_bv16_1,
					length_1 - (SI_Long)2L) + 
					((UBYTE_16_ISAREF_1(wide_string_bv16_1,
					length_1 - (SI_Long)1L) & 
					(SI_Long)8191L) << (SI_Long)16L));
			    }
			    char_to_write_qm =  !NUM_EQ(temp_1,temp) ? 
				    FIX(UBYTE_16_ISAREF_1(ISVREF(final,
				    (SI_Long)3L),i)) : Nil;
			}
			else {
			    code = char_1;
			    if (IFIX(code) < (SI_Long)127L)
				char_to_write_qm = (SI_Long)97L <= 
					IFIX(code) && IFIX(code) <= 
					(SI_Long)122L ? FIX(IFIX(code) + 
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
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_wide_string,
				    Total_length_of_current_wide_string))
				extend_current_wide_string(Fill_pointer_for_current_wide_string);
			    temp_2 = Current_wide_string;
			    aref_arg_2_1 = 
				    Fill_pointer_for_current_wide_string;
			    UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),
				    IFIX(char_to_write_qm));
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
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
	      temp = intern_wide_string(1,temp);
	      temp_1 = ISVREF(final,(SI_Long)4L);
	      if (CONSP(temp_1)) {
		  temp_1 = ISVREF(final,(SI_Long)4L);
		  temp_1 = FIRST(temp_1);
	      }
	      else
		  temp_1 = ISVREF(final,(SI_Long)4L);
	      next_parser_state = advance_parsing_for_token(temp,temp_1,
		      ISVREF(maybe_skip_comment_tokens(ISVREF(final,
		      (SI_Long)2L)),(SI_Long)6L));
	      if (next_parser_state)
		  result = VALUES_1(SVREF(final,FIX((SI_Long)6L)) = 
			  next_parser_state);
	      else
		  result = VALUES_1(Nil);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DETERMINE-FINAL-TOKEN */
Object determine_final_token(parsing_context)
    Object parsing_context;
{
    Object cursor_token;

    x_note_fn_call(126,178);
    cursor_token = ISVREF(parsing_context,(SI_Long)105L);
    if (FIXNUM_EQ(ISVREF(cursor_token,(SI_Long)7L),ISVREF(cursor_token,
	    (SI_Long)8L)))
	return VALUES_1(ISVREF(cursor_token,(SI_Long)2L));
    else
	return VALUES_1(cursor_token);
}

/* INCOMPLETE-TOKEN-CAN-BE-CONSTRUED-AS-COMPLETE */
Object incomplete_token_can_be_construed_as_complete(token)
    Object token;
{
    Object completion_choices, token_string, prediction_string, ab_loop_list_;
    Object ab_loop_it_;
    Object result;

    x_note_fn_call(126,179);
    result = compute_parsing_context_prompts(token);
    completion_choices = NTH_VALUE((SI_Long)1L, result);
    token_string = ISVREF(token,(SI_Long)9L);
    prediction_string = Nil;
    ab_loop_list_ = completion_choices;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    prediction_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = INLINE_UNSIGNED_BYTE_16_VECTOR_P(token_string) != 
	    (SI_Long)0L ? string_eq_w(prediction_string,token_string) : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* UNAMBIGUOUS-PARSING-TOKEN-P */
Object unambiguous_parsing_token_p(token)
    Object token;
{
    Object type_field, temp;

    x_note_fn_call(126,180);
    type_field = ISVREF(token,(SI_Long)4L);
    temp = SYMBOLP(type_field) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(type_field))
	return VALUES_1( !TRUEP(CDR(type_field)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

void edit2_INIT()
{
    Object temp, temp_3, reclaim_structure_for_text_inserter_spot_1;
    Object type_description, temp_4, gensymed_symbol_2;
    Object reclaim_structure_for_subcommand_state_1;
    Object valid_workstation_context_p_for_subcommand_state_1;
    Object clean_up_workstation_context_for_subcommand_state_1;
    Object reclaim_structure_for_parsing_token_1;
    Object reclaim_structure_for_parsing_context_1;
    Object clean_up_workstation_context_for_parsing_context_1;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1, temp_1;
    double temp_2;
    Object AB_package, list_constant_138, Qparsing_context;
    Object Qclean_up_workstation_context, Qreclaim_structure;
    Object Qoutstanding_parsing_context_count;
    Object Qparsing_context_structure_memory_usage, Qutilities2;
    Object string_constant_88, Qtype_description_of_type, string_constant_87;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qparsing_token;
    Object Qoutstanding_parsing_token_count;
    Object Qparsing_token_structure_memory_usage, string_constant_86;
    Object string_constant_85, Qskip_kfep_conversion, Qdo_edit_subcommand;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object string_constant_81, string_constant_80, string_constant_79;
    Object string_constant_78, string_constant_77, string_constant_76;
    Object string_constant_75, string_constant_74, string_constant_73;
    Object string_constant_72, string_constant_71, string_constant_70;
    Object list_constant_137, list_constant_136, list_constant_135;
    Object list_constant_134, list_constant_133, list_constant_132;
    Object Qmouse_up_in_subcommand_state, Qnew_style_event_handler;
    Object Qmouse_motion_in_subcommand_state, Qenter_subcommand_context;
    Object Qsubcommand_state, Qvalid_workstation_context_p, Qinternal;
    Object string_constant_69, Qabort_workstation_context;
    Object Qselection_style_of_workstation_context_type;
    Object Qtop_level_with_mouse_tracking_is_selection_style;
    Object Qoutstanding_subcommand_state_count;
    Object Qsubcommand_state_structure_memory_usage, string_constant_68;
    Object string_constant_67, Qtransparent, Qbackground, Qformat_description;
    Object string_constant_66, Qany_token_menu_format;
    Object Qcorresponding_small_font_format_name;
    Object Qsmall_token_menu_item_format, Qtoken_menu_item_format;
    Object string_constant_65, string_constant_64;
    Object Qsmall_any_token_menu_item_format, Qany_token_menu_item_format;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object Qcorresponding_extra_large_font_format_name;
    Object Qextra_large_subcommand_menu_item_format;
    Object Qsmall_subcommand_menu_item_format, string_constant_60;
    Object string_constant_59, string_constant_58, Qclasses_which_define;
    Object Qgenerate_spot, Qgenerate_spot_for_subcommand_menu;
    Object Qslot_value_reclaimer;
    Object Qreclaim_subcommand_function_arglist_qm_value;
    Object Qsubcommand_function_arglist_qm, string_constant_57;
    Object list_constant_131, Qmenu, string_constant_56, string_constant_55;
    Object string_constant_20;
    Object Qsearch_backward_incrementally_for_text_in_editor;
    Object list_constant_130, list_constant_129, list_constant_128;
    Object list_constant_127, list_constant_126, list_constant_125;
    Object list_constant_124, list_constant_123, list_constant_122;
    Object list_constant_121, list_constant_120, list_constant_119;
    Object list_constant_118, list_constant_117, list_constant_116;
    Object list_constant_115, list_constant_114, list_constant_113;
    Object list_constant_112, list_constant_111, list_constant_110;
    Object list_constant_109, list_constant_108, list_constant_107;
    Object list_constant_106, list_constant_105, list_constant_104;
    Object list_constant_103, list_constant_102, list_constant_101;
    Object list_constant_100, list_constant_99, list_constant_98;
    Object list_constant_97, list_constant_96, list_constant_95;
    Object list_constant_94, list_constant_93, list_constant_92;
    Object list_constant_91, list_constant_90, list_constant_89;
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
    Object list_constant_58, list_constant_57, list_constant_56;
    Object list_constant_55, list_constant_54, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_34, list_constant_33, list_constant_32;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_10;
    Object list_constant_16, list_constant_20, list_constant_19;
    Object list_constant_9, list_constant_18, list_constant_11;
    Object list_constant_13, list_constant_8, list_constant_12;
    Object list_constant_17, list_constant_15, list_constant_14;
    Object list_constant_7, Qg2_copy_text_to_clipboard;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qextra_large_scrap_format, string_constant_54, string_constant_53;
    Object Qsmall_scrap_format, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object Qhk_format, Qgenerate_spot_for_scrap, Qtype_of_frame_represented;
    Object Qabstract_type, Qimage_plane_spot, Qenclosing_spot_type;
    Object Qinnermost_spot_p, Qtext_inserter_spot;
    Object Qoutstanding_text_inserter_spot_count;
    Object Qtext_inserter_spot_structure_memory_usage, string_constant_47;
    Object string_constant_46, string_constant_45, list_constant_6;
    Object string_constant_41, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, Qtext_inserter;
    Object string_constant_36, list_constant_5, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32, Qitem;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, list_constant_4;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object Qtext_box, Qlight_gray, float_constant_1, float_constant;

    x_note_fn_call(126,181);
    SET_PACKAGE("AB");
    if (Time_of_frame_edit_base_time == UNBOUND) {
	unix_time = g2ext_get_encoded_unix_time((SI_Long)0L,(SI_Long)0L,
		(SI_Long)0L,(SI_Long)1L,(SI_Long)9L,(SI_Long)1993L);
	arg = unix_time;
	arg_1 = -1.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = encode_unix_time_after_failure(FIX((SI_Long)0L),
		    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)1L),
		    FIX((SI_Long)9L),FIX((SI_Long)1993L));
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else
	    gensymed_symbol = unix_time;
	gensymed_symbol_1 = (double)((SI_Long)60L * 
		IFIX(Global_daylight_saving_time_adjustment));
	Time_of_frame_edit_base_time = 
		DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol - gensymed_symbol_1);
    }
    float_constant = STATIC_FLOAT(0.0);
    if (Text_time_stamp_seconds == UNBOUND)
	Text_time_stamp_seconds = float_constant;
    float_constant_1 = STATIC_FLOAT(1.0);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Time_of_frame_edit_base_time);
    temp = lfloat(timesn(3,FIX((SI_Long)24L),FIX((SI_Long)60L),
	    FIX((SI_Long)60L)),float_constant_1);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    Time_of_last_allowable_frame_edit_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 
	    + (double)IFIX(Most_positive_fixnum) * 60.0 - temp_2);
    AB_package = STATIC_PACKAGE("AB");
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    Qdate = STATIC_SYMBOL("DATE",AB_package);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    if (Fixup_authors_to_skip == UNBOUND)
	Fixup_authors_to_skip = Nil;
    Qautomatic = STATIC_SYMBOL("AUTOMATIC",AB_package);
    Qkfep_conversion = STATIC_SYMBOL("KFEP-CONVERSION",AB_package);
    Kfep_conversion_text_region_expansion_limit = FIX((SI_Long)1024L);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Default_kanji_conversion_text_region_highlight_color = Qlight_gray;
    Qpathname_component_conversion = 
	    STATIC_SYMBOL("PATHNAME-COMPONENT-CONVERSION",AB_package);
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qword_spacing = STATIC_SYMBOL("WORD-SPACING",AB_package);
    Qy_offset_for_text = STATIC_SYMBOL("Y-OFFSET-FOR-TEXT",AB_package);
    Qline_index_of_first_fully_visible_line = 
	    STATIC_SYMBOL("LINE-INDEX-OF-FIRST-FULLY-VISIBLE-LINE",AB_package);
    Qnumber_of_fully_visible_lines = 
	    STATIC_SYMBOL("NUMBER-OF-FULLY-VISIBLE-LINES",AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    Qno_autocompletion = STATIC_SYMBOL("NO-AUTOCOMPLETION",AB_package);
    Qundo = STATIC_SYMBOL("UNDO",AB_package);
    Qredo = STATIC_SYMBOL("REDO",AB_package);
    Kno_bleeding = STATIC_SYMBOL("NO-BLEEDING",Pkeyword);
    Qdraw_text_segment_in_text_box = 
	    STATIC_SYMBOL("DRAW-TEXT-SEGMENT-IN-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_text_segment_in_text_box,
	    STATIC_FUNCTION(draw_text_segment_in_text_box,NIL,FALSE,4,4));
    Qscrap = STATIC_SYMBOL("SCRAP",AB_package);
    Qreplace_fragments_on_sides_qm = 
	    STATIC_SYMBOL("REPLACE-FRAGMENTS-ON-SIDES\?",AB_package);
    Qhandle_spaces_intelligently_qm = 
	    STATIC_SYMBOL("HANDLE-SPACES-INTELLIGENTLY\?",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qscrapbook = STATIC_SYMBOL("SCRAPBOOK",AB_package);
    Qnon_kb_workspace = STATIC_SYMBOL("NON-KB-WORKSPACE",AB_package);
    Qmaximum_number_of_scraps_to_keep = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-SCRAPS-TO-KEEP",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_4 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qscrap,list_constant_4);
    string_constant_20 = STATIC_STRING("0");
    string_constant_21 = 
	    STATIC_STRING("1p4z8r83ry83ry839vy839vy00001o1l8l1n8p83-dy83Gy1l8o1l83-3y000004z8r83xy83xy839vy839vy083Zly001n1l8l1m83Dy73-9y3-1y3-qy3-iy3-hy3-");
    string_constant_22 = 
	    STATIC_STRING("ky3-my3Sy3-my3-Xy3-qy3-my3fy3-Yy3-hy3-ky3-fy3-Ty3-my3fy3-gy3-Ty3-fy3-Xy3ey3Sy3-ly3-Xy3-iy3-Ty3-ky3-Ty3-my3-Xy3Sy3-fy3-Xy3-Vy3-ay");
    string_constant_23 = 
	    STATIC_STRING("3-Ty3-gy3-by3-ly3-fy3Sy3-Yy3-hy3-ky3Sy3-iy3-Ty3-ky3-my3Sy3-Vy3-hy3-iy3-ry3Sy3-hy3-Yy3Sy3-gy3-Ty3-fy3-Xy3-Wy3Sy3-wyu3Syt3-Yy3-hy3");
    string_constant_24 = 
	    STATIC_STRING("-ky3-fy3-Ty3-my1l83Ey000004z8r83=2y83=2y839vy839vy08k001n1l83Ey1l8l1m83Dy53SyExport boolean, writable = false000004z8r83==y83==y");
    string_constant_25 = 
	    STATIC_STRING("839vy839vy08k001n1l83Ey1l8l1m83Dy53SyExport boolean, writable = false000004z8r83=iy83=iy839vy839vy00001n1l83Ey1l8l1m83Dy53SyExpo");
    string_constant_26 = STATIC_STRING("rt boolean, writable = false00000");
    string_constant_27 = 
	    STATIC_STRING("1r8q1m839vy1l83-ly1n83ry01n8p83-dy83Gy1n83xy83Zly1m83Dy73-9y3-1y3-qy3-iy3-hy3-ky3-my3Sy3-my3-Xy3-qy3-my3fy3-Yy3-hy3-ky3-fy3-Ty3-");
    string_constant_28 = 
	    STATIC_STRING("my3fy3-gy3-Ty3-fy3-Xy3ey3Sy3-ly3-Xy3-iy3-Ty3-ky3-Ty3-my3-Xy3Sy3-fy3-Xy3-Vy3-ay3-Ty3-gy3-by3-ly3-fy3Sy3-Yy3-hy3-ky3Sy3-iy3-Ty3-ky");
    string_constant_29 = 
	    STATIC_STRING("3-my3Sy3-Vy3-hy3-iy3-ry3Sy3-hy3-Yy3Sy3-gy3-Ty3-fy3-Xy3-Wy3Sy3-wyu3Syt3-Yy3-hy3-ky3-fy3-Ty3-my1p83=2y8k83Ey8l1m83Dy53SyExport boo");
    string_constant_30 = 
	    STATIC_STRING("lean, writable = false1p83==y8k83Ey8l1m83Dy53SyExport boolean, writable = false1p83=iy083Ey8l1m83Dy53SyExport boolean, writable ");
    string_constant_31 = STATIC_STRING("= false");
    temp = regenerate_optimized_constant(string_constant_20);
    temp_3 = regenerate_optimized_constant(list(6,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26));
    add_class_to_environment(9,Qscrap,list_constant_4,Nil,temp,Nil,temp_3,
	    list_constant_4,
	    regenerate_optimized_constant(LIST_5(string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31)),Nil);
    Scrap_class_description = 
	    lookup_global_or_kb_specific_property_value(Qscrap,
	    Class_description_gkbprop);
    Qtext_inserter = STATIC_SYMBOL("TEXT-INSERTER",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qitem,Qscrap);
    check_if_superior_classes_are_defined(Qtext_inserter,list_constant_5);
    string_constant_32 = STATIC_STRING("1l1m8v832Ry");
    string_constant_33 = 
	    STATIC_STRING("1l4z8r83=ky83=ky832Ry832Ry00001p1l8l1l8z1l8o1l83Cy1m83Dy53=cyThese values map to text-cell-plist-for-text-box.<br> ~\n<li>magnifi");
    string_constant_34 = 
	    STATIC_STRING("cation: [x-magnification: number, y-magnification: number], ~\n<li>highlight-color: color-symbol, ~\n<li>border-color: color-symbo");
    string_constant_35 = 
	    STATIC_STRING("l, ~\n<li>line-color: color-symbol, <br>00000");
    string_constant_36 = 
	    STATIC_STRING("1n8q1n832Ry1m83Ry839vy1m8v832Ry1n83=ky08z");
    temp = regenerate_optimized_constant(string_constant_32);
    temp_3 = regenerate_optimized_constant(LIST_3(string_constant_33,
	    string_constant_34,string_constant_35));
    add_class_to_environment(9,Qtext_inserter,list_constant_5,Nil,temp,Nil,
	    temp_3,list_constant_5,
	    regenerate_optimized_constant(string_constant_36),Nil);
    Qword_inserter = STATIC_SYMBOL("WORD-INSERTER",AB_package);
    list_constant_6 = STATIC_CONS(Qtext_inserter,Qnil);
    check_if_superior_classes_are_defined(Qword_inserter,list_constant_6);
    string_constant_37 = STATIC_STRING("1l1m8v83eSy");
    string_constant_38 = STATIC_STRING("1m8q1n83eSy1l832Ry1m8v83eSy");
    temp = regenerate_optimized_constant(string_constant_37);
    temp_3 = regenerate_optimized_constant(string_constant_20);
    add_class_to_environment(9,Qword_inserter,list_constant_6,Nil,temp,Nil,
	    temp_3,list_constant_6,
	    regenerate_optimized_constant(string_constant_38),Nil);
    Qcharacter_inserter = STATIC_SYMBOL("CHARACTER-INSERTER",AB_package);
    check_if_superior_classes_are_defined(Qcharacter_inserter,list_constant_6);
    string_constant_39 = STATIC_STRING("1l1m8v837ty");
    string_constant_40 = 
	    STATIC_STRING("1m4z8r83=2y83=2y837ty837ty00001n1l8l1l83Ey1m83Dy53SyExport boolean, writable = false000004z8r83==y83==y837ty837ty00001n1l8l1l83E");
    string_constant_41 = 
	    STATIC_STRING("y1m83Dy53SyExport boolean, writable = false00000");
    string_constant_42 = 
	    STATIC_STRING("1o8q1n837ty1l832Ry1m8v837ty1m83=2y01m83==y0");
    temp = regenerate_optimized_constant(string_constant_39);
    temp_3 = regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_41));
    add_class_to_environment(9,Qcharacter_inserter,list_constant_6,Nil,
	    temp,Nil,temp_3,list_constant_6,
	    regenerate_optimized_constant(string_constant_42),Nil);
    Qcharacter_sequence_inserter = 
	    STATIC_SYMBOL("CHARACTER-SEQUENCE-INSERTER",AB_package);
    check_if_superior_classes_are_defined(Qcharacter_sequence_inserter,
	    list_constant_6);
    string_constant_43 = STATIC_STRING("1l1m8v837uy");
    string_constant_44 = 
	    STATIC_STRING("1m4z8r83=2y83=2y837uy837uy00001n1l8l1l83Ey1m83Dy53SyExport boolean, writable = false000004z8r83==y83==y837uy837uy00001n1l8l1l83E");
    string_constant_45 = 
	    STATIC_STRING("1o8q1n837uy1l832Ry1m8v837uy1m83=2y01m83==y0");
    temp = regenerate_optimized_constant(string_constant_43);
    temp_3 = regenerate_optimized_constant(LIST_2(string_constant_44,
	    string_constant_41));
    add_class_to_environment(9,Qcharacter_sequence_inserter,
	    list_constant_6,Nil,temp,Nil,temp_3,list_constant_6,
	    regenerate_optimized_constant(string_constant_45),Nil);
    Qg2_defstruct_structure_name_text_inserter_spot_g2_struct = 
	    STATIC_SYMBOL("TEXT-INSERTER-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_inserter_spot = STATIC_SYMBOL("TEXT-INSERTER-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_inserter_spot_g2_struct,
	    Qtext_inserter_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtext_inserter_spot,
	    Qg2_defstruct_structure_name_text_inserter_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_text_inserter_spot == UNBOUND)
	The_type_description_of_text_inserter_spot = Nil;
    string_constant_46 = 
	    STATIC_STRING("43Dy8m83nky1o83nky83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_text_inserter_spot;
    The_type_description_of_text_inserter_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_46));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_inserter_spot_g2_struct,
	    The_type_description_of_text_inserter_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtext_inserter_spot,
	    The_type_description_of_text_inserter_spot,
	    Qtype_description_of_type);
    Qoutstanding_text_inserter_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEXT-INSERTER-SPOT-COUNT",AB_package);
    Qtext_inserter_spot_structure_memory_usage = 
	    STATIC_SYMBOL("TEXT-INSERTER-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_47 = STATIC_STRING("1q83nky8s83-sWy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_text_inserter_spot_count);
    push_optimized_constant(Qtext_inserter_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_47));
    Qchain_of_available_text_inserter_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-INSERTER-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_text_inserter_spots,
	    Chain_of_available_text_inserter_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_text_inserter_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtext_inserter_spot_count = STATIC_SYMBOL("TEXT-INSERTER-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_inserter_spot_count,
	    Text_inserter_spot_count);
    record_system_variable(Qtext_inserter_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_text_inserter_spots_vector == UNBOUND)
	Chain_of_available_text_inserter_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtext_inserter_spot_structure_memory_usage,
	    STATIC_FUNCTION(text_inserter_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_text_inserter_spot_count,
	    STATIC_FUNCTION(outstanding_text_inserter_spot_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_text_inserter_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_text_inserter_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtext_inserter_spot,
	    reclaim_structure_for_text_inserter_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_inserter_spot),
	    Qtype_description_of_type);
    temp_4 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qscrap),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_4;
    Qgenerate_spot_for_scrap = STATIC_SYMBOL("GENERATE-SPOT-FOR-SCRAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_scrap,
	    STATIC_FUNCTION(generate_spot_for_scrap,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_4 = SYMBOL_FUNCTION(Qgenerate_spot_for_scrap);
    set_get(Qscrap,Qgenerate_spot,temp_4);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_4 = CONS(Qscrap,temp);
    mutate_global_property(Qgenerate_spot,temp_4,Qclasses_which_define);
    Qhk_format = STATIC_SYMBOL("HK-FORMAT",AB_package);
    string_constant_48 = STATIC_STRING("1r83-Qy83kyk83-=yk83iy38Sy");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qhk_format,
	    regenerate_optimized_constant(string_constant_48),
	    Qformat_description);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qscrap_format = STATIC_SYMBOL("SCRAP-FORMAT",AB_package);
    string_constant_49 = 
	    STATIC_STRING("13by83-My83ny1l83-uy83ty3Fy83syy83uyn83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yk83-By083-Ny83fy83*ky83fy83*=yl83*1yl83*0yl83**yl83byw");
    string_constant_50 = STATIC_STRING("83ays83Wyw83cyo");
    mutate_global_property(Qscrap_format,
	    regenerate_optimized_constant(LIST_2(string_constant_49,
	    string_constant_50)),Qformat_description);
    Qsmall_scrap_format = STATIC_SYMBOL("SMALL-SCRAP-FORMAT",AB_package);
    string_constant_51 = 
	    STATIC_STRING("13by83-My83ny1l83-ry83tyz83syx83uym83-7y3F+y83*3y3C+y83*+y3i+y83kyk83-=yk83-By083-Ny83fy83*ky83fy83*=yl83*1yl83*0yl83**yl83bys83");
    string_constant_52 = STATIC_STRING("ayo83Wys83cyo");
    mutate_global_property(Qsmall_scrap_format,
	    regenerate_optimized_constant(LIST_2(string_constant_51,
	    string_constant_52)),Qformat_description);
    Qcorresponding_small_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-SMALL-FONT-FORMAT-NAME",AB_package);
    mutate_global_property(Qscrap_format,Qsmall_scrap_format,
	    Qcorresponding_small_font_format_name);
    Qextra_large_scrap_format = STATIC_SYMBOL("EXTRA-LARGE-SCRAP-FORMAT",
	    AB_package);
    string_constant_53 = 
	    STATIC_STRING("13by83-My83ny1l8311y83ty3My83sy3Fy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83kyk83-=yk83-By083-Ny83fy83*ky83fy83*=yl83*1yl83*0yl83**yl83");
    string_constant_54 = STATIC_STRING("byz83ayv83Wyz83cyu");
    mutate_global_property(Qextra_large_scrap_format,
	    regenerate_optimized_constant(LIST_2(string_constant_53,
	    string_constant_54)),Qformat_description);
    Qcorresponding_extra_large_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-EXTRA-LARGE-FONT-FORMAT-NAME",
	    AB_package);
    mutate_global_property(Qscrap_format,Qextra_large_scrap_format,
	    Qcorresponding_extra_large_font_format_name);
    Qpaste_from_current_scrap_if_any = 
	    STATIC_SYMBOL("PASTE-FROM-CURRENT-SCRAP-IF-ANY",AB_package);
    SET_SYMBOL_FUNCTION(Qpaste_from_current_scrap_if_any,
	    STATIC_FUNCTION(paste_from_current_scrap_if_any,NIL,FALSE,0,0));
    Qpaste_text_string = STATIC_SYMBOL("PASTE-TEXT-STRING",AB_package);
    Qinsert_text_string_in_text_being_edited = 
	    STATIC_SYMBOL("INSERT-TEXT-STRING-IN-TEXT-BEING-EDITED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinsert_text_string_in_text_being_edited,
	    STATIC_FUNCTION(insert_text_string_in_text_being_edited,NIL,
	    TRUE,6,11));
    Qinsert_text_string_at_cursor = 
	    STATIC_SYMBOL("INSERT-TEXT-STRING-AT-CURSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinsert_text_string_at_cursor,
	    STATIC_FUNCTION(insert_text_string_at_cursor,NIL,TRUE,3,6));
    SET_SYMBOL_FUNCTION(Qpaste_text_string,
	    STATIC_FUNCTION(paste_text_string,NIL,TRUE,1,3));
    Qpaste = STATIC_SYMBOL("PASTE",AB_package);
    Qno_native_clipboard = STATIC_SYMBOL("NO-NATIVE-CLIPBOARD",AB_package);
    Qg2_copy_text_to_clipboard = STATIC_SYMBOL("G2-COPY-TEXT-TO-CLIPBOARD",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol_2 = Nil;
    mutate_global_property(Qg2_copy_text_to_clipboard,gensymed_symbol_2,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_copy_text_to_clipboard,
	    STATIC_FUNCTION(g2_copy_text_to_clipboard,NIL,FALSE,2,2));
    string_constant = 
	    STATIC_STRING("This has been revealed because of a parsing problem: ~A");
    string_constant_1 = STATIC_STRING("~A");
    Qkanji_code_entry = STATIC_SYMBOL("KANJI-CODE-ENTRY",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qcheck_hangul_code_entry_text = 
	    STATIC_SYMBOL("CHECK-HANGUL-CODE-ENTRY-TEXT",AB_package);
    Qcheck_kanji_code_entry_text = 
	    STATIC_SYMBOL("CHECK-KANJI-CODE-ENTRY-TEXT",AB_package);
    Qhangul_code_entry = STATIC_SYMBOL("HANGUL-CODE-ENTRY",AB_package);
    Qcyrillic_code_entry = STATIC_SYMBOL("CYRILLIC-CODE-ENTRY",AB_package);
    Qcheck_cyrillic_code_entry_text = 
	    STATIC_SYMBOL("CHECK-CYRILLIC-CODE-ENTRY-TEXT",AB_package);
    Qsearch_for_text_in_editor = STATIC_SYMBOL("SEARCH-FOR-TEXT-IN-EDITOR",
	    AB_package);
    Qsearch_forward_incrementally_for_text_in_editor = 
	    STATIC_SYMBOL("SEARCH-FORWARD-INCREMENTALLY-FOR-TEXT-IN-EDITOR",
	    AB_package);
    Qinsertion_of_symbol = STATIC_SYMBOL("INSERTION-OF-SYMBOL",AB_package);
    Qcheck_insertion_of_symbol_entry_text = 
	    STATIC_SYMBOL("CHECK-INSERTION-OF-SYMBOL-ENTRY-TEXT",AB_package);
    Qcheck_special_character_entry_text = 
	    STATIC_SYMBOL("CHECK-SPECIAL-CHARACTER-ENTRY-TEXT",AB_package);
    Qkanji_characters = STATIC_SYMBOL("KANJI-CHARACTERS",AB_package);
    Qhangul_characters = STATIC_SYMBOL("HANGUL-CHARACTERS",AB_package);
    Qspecial_characters = STATIC_SYMBOL("SPECIAL-CHARACTERS",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qdefault_workspace_frame_style = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-FRAME-STYLE",AB_package);
    Qbelow = STATIC_SYMBOL("BELOW",AB_package);
    Qdelete_image_plane = STATIC_SYMBOL("DELETE-IMAGE-PLANE",AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_image_plane,
	    STATIC_FUNCTION(delete_image_plane,NIL,FALSE,1,1));
    Qhangul = STATIC_SYMBOL("HANGUL",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_hangul_code_entry_text,
	    STATIC_FUNCTION(check_hangul_code_entry_text,NIL,TRUE,1,2));
    Qcyrillic = STATIC_SYMBOL("CYRILLIC",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_cyrillic_code_entry_text,
	    STATIC_FUNCTION(check_cyrillic_code_entry_text,NIL,TRUE,1,2));
    string_constant_2 = STATIC_STRING("Hangul (KS C 5601)");
    string_constant_3 = STATIC_STRING("Cyrillic (ISO 8859-5)");
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    string_constant_4 = STATIC_STRING("Unicode 2.0");
    string_constant_5 = STATIC_STRING("Kanji (JIS)");
    Qrubout_on_blank_text = STATIC_SYMBOL("RUBOUT-ON-BLANK-TEXT",AB_package);
    string_constant_6 = STATIC_STRING("Please enter a ~d-digit ~a hex code");
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    string_constant_7 = STATIC_STRING("~c");
    string_constant_8 = STATIC_STRING("This is an invalid ~a code");
    string_constant_9 = STATIC_STRING("Too many digits");
    SET_SYMBOL_FUNCTION(Qcheck_kanji_code_entry_text,
	    STATIC_FUNCTION(check_kanji_code_entry_text,NIL,TRUE,1,3));
    Qrussian = STATIC_SYMBOL("RUSSIAN",AB_package);
    Qkanji = STATIC_SYMBOL("KANJI",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_insertion_of_symbol_entry_text,
	    STATIC_FUNCTION(check_insertion_of_symbol_entry_text,NIL,TRUE,
	    1,2));
    list_constant_7 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)58L),
	    FIX((SI_Long)34L));
    list_constant_8 = STATIC_CONS(list_constant_7,Qnil);
    list_constant_98 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)228L),
	    Qnil,FIX((SI_Long)97L),list_constant_8);
    list_constant_99 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)196L),
	    FIX((SI_Long)228L),FIX((SI_Long)65L),list_constant_8);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)39L),Qnil);
    list_constant_100 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)225L),
	    Qnil,FIX((SI_Long)97L),list_constant_9);
    list_constant_101 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)193L),
	    FIX((SI_Long)225L),FIX((SI_Long)65L),list_constant_9);
    list_constant_10 = STATIC_CONS(FIX((SI_Long)44L),Qnil);
    list_constant_102 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)231L),
	    Qnil,FIX((SI_Long)99L),list_constant_10);
    list_constant_103 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)199L),
	    FIX((SI_Long)231L),FIX((SI_Long)67L),list_constant_10);
    list_constant_11 = STATIC_CONS(FIX((SI_Long)94L),Qnil);
    list_constant_104 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)226L),
	    Qnil,FIX((SI_Long)97L),list_constant_11);
    list_constant_105 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)194L),
	    FIX((SI_Long)226L),FIX((SI_Long)65L),list_constant_11);
    list_constant_106 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)233L),
	    Qnil,FIX((SI_Long)101L),list_constant_9);
    list_constant_107 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)201L),
	    FIX((SI_Long)233L),FIX((SI_Long)69L),list_constant_9);
    list_constant_108 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)234L),
	    Qnil,FIX((SI_Long)101L),list_constant_11);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)202L),
	    FIX((SI_Long)234L),FIX((SI_Long)69L),list_constant_11);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)96L),Qnil);
    list_constant_110 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)232L),
	    Qnil,FIX((SI_Long)101L),list_constant_12);
    list_constant_111 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)200L),
	    FIX((SI_Long)232L),FIX((SI_Long)69L),list_constant_12);
    list_constant_112 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)236L),
	    Qnil,FIX((SI_Long)105L),list_constant_12);
    list_constant_113 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)204L),
	    FIX((SI_Long)236L),FIX((SI_Long)73L),list_constant_12);
    list_constant_114 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)237L),
	    Qnil,FIX((SI_Long)105L),list_constant_9);
    list_constant_115 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)205L),
	    FIX((SI_Long)237L),FIX((SI_Long)73L),list_constant_9);
    list_constant_116 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)238L),
	    Qnil,FIX((SI_Long)105L),list_constant_11);
    list_constant_117 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)206L),
	    FIX((SI_Long)238L),FIX((SI_Long)73L),list_constant_11);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)224L),
	    Qnil,FIX((SI_Long)97L),list_constant_12);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)192L),
	    FIX((SI_Long)224L),FIX((SI_Long)65L),list_constant_12);
    list_constant_13 = STATIC_CONS(FIX((SI_Long)126L),Qnil);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)241L),
	    Qnil,FIX((SI_Long)110L),list_constant_13);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)209L),
	    FIX((SI_Long)241L),FIX((SI_Long)78L),list_constant_13);
    list_constant_122 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)246L),
	    Qnil,FIX((SI_Long)111L),list_constant_8);
    list_constant_123 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)214L),
	    FIX((SI_Long)246L),FIX((SI_Long)79L),list_constant_8);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)243L),
	    Qnil,FIX((SI_Long)111L),list_constant_9);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)211L),
	    FIX((SI_Long)243L),FIX((SI_Long)79L),list_constant_9);
    list_constant_126 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)244L),
	    Qnil,FIX((SI_Long)111L),list_constant_11);
    list_constant_127 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)212L),
	    FIX((SI_Long)244L),FIX((SI_Long)79L),list_constant_11);
    list_constant_14 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)111L),
	    FIX((SI_Long)79L),FIX((SI_Long)48L));
    list_constant_15 = STATIC_CONS(list_constant_14,Qnil);
    list_constant_128 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)229L),
	    Qnil,FIX((SI_Long)97L),list_constant_15);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)197L),
	    FIX((SI_Long)229L),FIX((SI_Long)65L),list_constant_15);
    list_constant_67 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)223L),Qnil,
	    Qnil,FIX((SI_Long)115L));
    list_constant_16 = STATIC_CONS(FIX((SI_Long)47L),Qnil);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)248L),
	    Qnil,FIX((SI_Long)111L),list_constant_16);
    list_constant_69 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)216L),
	    FIX((SI_Long)248L),FIX((SI_Long)79L),list_constant_16);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)252L),
	    Qnil,FIX((SI_Long)117L),list_constant_8);
    list_constant_71 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)220L),
	    FIX((SI_Long)252L),FIX((SI_Long)85L),list_constant_8);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)250L),
	    Qnil,FIX((SI_Long)117L),list_constant_9);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)218L),
	    FIX((SI_Long)250L),FIX((SI_Long)85L),list_constant_9);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)101L),Qnil);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)339L),
	    Qnil,FIX((SI_Long)111L),list_constant_17);
    list_constant_75 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)338L),
	    FIX((SI_Long)339L),FIX((SI_Long)79L),list_constant_17);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)230L),
	    Qnil,FIX((SI_Long)97L),list_constant_17);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)198L),
	    FIX((SI_Long)230L),FIX((SI_Long)65L),list_constant_17);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)242L),
	    Qnil,FIX((SI_Long)111L),list_constant_12);
    list_constant_79 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)210L),
	    FIX((SI_Long)242L),FIX((SI_Long)79L),list_constant_12);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)249L),
	    Qnil,FIX((SI_Long)117L),list_constant_12);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)217L),
	    FIX((SI_Long)249L),FIX((SI_Long)85L),list_constant_12);
    list_constant_82 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)235L),
	    Qnil,FIX((SI_Long)101L),list_constant_8);
    list_constant_83 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)203L),
	    FIX((SI_Long)235L),FIX((SI_Long)69L),list_constant_8);
    list_constant_84 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)239L),
	    Qnil,FIX((SI_Long)105L),list_constant_8);
    list_constant_85 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)207L),
	    FIX((SI_Long)239L),FIX((SI_Long)73L),list_constant_8);
    list_constant_86 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)227L),
	    Qnil,FIX((SI_Long)97L),list_constant_13);
    list_constant_87 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)195L),
	    FIX((SI_Long)227L),FIX((SI_Long)65L),list_constant_13);
    list_constant_88 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)245L),
	    Qnil,FIX((SI_Long)111L),list_constant_13);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)213L),
	    FIX((SI_Long)245L),FIX((SI_Long)79L),list_constant_13);
    list_constant_90 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)251L),
	    Qnil,FIX((SI_Long)117L),list_constant_11);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)219L),
	    FIX((SI_Long)251L),FIX((SI_Long)85L),list_constant_11);
    list_constant_92 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)162L),
	    Qnil,FIX((SI_Long)99L),list_constant_16);
    list_constant_93 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)162L),
	    Qnil,FIX((SI_Long)67L),list_constant_16);
    list_constant_94 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)169L),Qnil,
	    Qnil,FIX((SI_Long)99L));
    list_constant_95 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)8482L),Qnil,
	    Qnil,FIX((SI_Long)116L));
    list_constant_96 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)174L),Qnil,
	    Qnil,FIX((SI_Long)114L));
    list_constant_34 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)191L),Qnil,
	    Qnil,FIX((SI_Long)63L));
    list_constant_35 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)161L),Qnil,
	    Qnil,FIX((SI_Long)33L));
    list_constant_36 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)171L),Qnil,
	    Qnil,FIX((SI_Long)60L));
    list_constant_37 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)187L),Qnil,
	    Qnil,FIX((SI_Long)62L));
    list_constant_38 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)163L),Qnil,
	    Qnil,FIX((SI_Long)108L));
    list_constant_39 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)165L),Qnil,
	    Qnil,FIX((SI_Long)121L));
    list_constant_40 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)402L),Qnil,
	    Qnil,FIX((SI_Long)102L));
    list_constant_41 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)8226L),Qnil,
	    Qnil,FIX((SI_Long)42L));
    list_constant_18 = STATIC_CONS(FIX((SI_Long)40L),Qnil);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)261L),
	    Qnil,FIX((SI_Long)97L),list_constant_18);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)260L),
	    FIX((SI_Long)261L),FIX((SI_Long)65L),list_constant_18);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)263L),
	    Qnil,FIX((SI_Long)99L),list_constant_9);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)262L),
	    FIX((SI_Long)263L),FIX((SI_Long)67L),list_constant_9);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)281L),
	    Qnil,FIX((SI_Long)101L),list_constant_18);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)280L),
	    FIX((SI_Long)281L),FIX((SI_Long)69L),list_constant_18);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)324L),
	    Qnil,FIX((SI_Long)110L),list_constant_9);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)323L),
	    FIX((SI_Long)324L),FIX((SI_Long)78L),list_constant_9);
    list_constant_50 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)347L),
	    Qnil,FIX((SI_Long)115L),list_constant_9);
    list_constant_51 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)346L),
	    FIX((SI_Long)347L),FIX((SI_Long)83L),list_constant_9);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)384L),
	    Qnil,FIX((SI_Long)122L),list_constant_9);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)377L),
	    FIX((SI_Long)384L),FIX((SI_Long)90L),list_constant_9);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)46L),Qnil);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)386L),
	    Qnil,FIX((SI_Long)122L),list_constant_19);
    list_constant_55 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)385L),
	    FIX((SI_Long)386L),FIX((SI_Long)90L),list_constant_19);
    list_constant_56 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)322L),
	    Qnil,FIX((SI_Long)108L),list_constant_16);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)321L),
	    FIX((SI_Long)322L),FIX((SI_Long)76L),list_constant_16);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)61L),Qnil);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)337L),
	    Qnil,FIX((SI_Long)111L),list_constant_20);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)336L),
	    FIX((SI_Long)337L),FIX((SI_Long)79L),list_constant_20);
    list_constant_60 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)369L),
	    Qnil,FIX((SI_Long)117L),list_constant_20);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)368L),
	    FIX((SI_Long)369L),FIX((SI_Long)85L),list_constant_20);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)8362L),
	    Qnil,FIX((SI_Long)115L),list_constant_16);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)8355L),
	    Qnil,FIX((SI_Long)102L),list_constant_16);
    list_constant_64 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)8362L),
	    Qnil,FIX((SI_Long)83L),list_constant_16);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)8355L),
	    Qnil,FIX((SI_Long)70L),list_constant_16);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)351L),
	    Qnil,FIX((SI_Long)115L),list_constant_10);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)350L),
	    FIX((SI_Long)351L),FIX((SI_Long)83L),list_constant_10);
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)117L),
	    FIX((SI_Long)85L));
    list_constant_22 = STATIC_CONS(list_constant_21,Qnil);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)287L),
	    Qnil,FIX((SI_Long)103L),list_constant_22);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)286L),
	    FIX((SI_Long)351L),FIX((SI_Long)71L),list_constant_22);
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)105L),
	    FIX((SI_Long)73L));
    list_constant_24 = STATIC_CONS(list_constant_23,Qnil);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)305L),
	    Qnil,FIX((SI_Long)105L),list_constant_24);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)304L),
	    FIX((SI_Long)304L),FIX((SI_Long)73L),list_constant_24);
    list_constant_32 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)8364L),Qnil,
	    Qnil,FIX((SI_Long)36L));
    list_constant_33 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)9L),Qnil,Qnil,
	    FIX((SI_Long)9L));
    list_constant_65 = STATIC_LIST((SI_Long)9L,list_constant_25,
	    list_constant_26,list_constant_27,list_constant_28,
	    list_constant_29,list_constant_30,list_constant_31,
	    list_constant_32,list_constant_33);
    list_constant_97 = STATIC_LIST_STAR((SI_Long)32L,list_constant_34,
	    list_constant_35,list_constant_36,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44,list_constant_45,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49,
	    list_constant_50,list_constant_51,list_constant_52,
	    list_constant_53,list_constant_54,list_constant_55,
	    list_constant_56,list_constant_57,list_constant_58,
	    list_constant_59,list_constant_60,list_constant_61,
	    list_constant_62,list_constant_63,list_constant_64,
	    list_constant_65);
    list_constant_129 = STATIC_LIST_STAR((SI_Long)32L,list_constant_66,
	    list_constant_67,list_constant_68,list_constant_69,
	    list_constant_70,list_constant_71,list_constant_72,
	    list_constant_73,list_constant_74,list_constant_75,
	    list_constant_76,list_constant_77,list_constant_78,
	    list_constant_79,list_constant_80,list_constant_81,
	    list_constant_82,list_constant_83,list_constant_84,
	    list_constant_85,list_constant_86,list_constant_87,
	    list_constant_88,list_constant_89,list_constant_90,
	    list_constant_91,list_constant_92,list_constant_93,
	    list_constant_94,list_constant_95,list_constant_96,
	    list_constant_97);
    list_constant_130 = STATIC_LIST_STAR((SI_Long)32L,list_constant_98,
	    list_constant_99,list_constant_100,list_constant_101,
	    list_constant_102,list_constant_103,list_constant_104,
	    list_constant_105,list_constant_106,list_constant_107,
	    list_constant_108,list_constant_109,list_constant_110,
	    list_constant_111,list_constant_112,list_constant_113,
	    list_constant_114,list_constant_115,list_constant_116,
	    list_constant_117,list_constant_118,list_constant_119,
	    list_constant_120,list_constant_121,list_constant_122,
	    list_constant_123,list_constant_124,list_constant_125,
	    list_constant_126,list_constant_127,list_constant_128,
	    list_constant_129);
    Editor_special_character_alist = list_constant_130;
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    string_constant_10 = STATIC_STRING("Please enter one character");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_11 = 
	    STATIC_STRING("Previous character (~c) cannot take this accent");
    string_constant_12 = 
	    STATIC_STRING("This has no corresponding special character");
    SET_SYMBOL_FUNCTION(Qcheck_special_character_entry_text,
	    STATIC_FUNCTION(check_special_character_entry_text,NIL,TRUE,1,3));
    Kforward = STATIC_SYMBOL("FORWARD",Pkeyword);
    SET_SYMBOL_FUNCTION(Qsearch_forward_incrementally_for_text_in_editor,
	    STATIC_FUNCTION(search_forward_incrementally_for_text_in_editor,
	    NIL,TRUE,1,2));
    Kbackward = STATIC_SYMBOL("BACKWARD",Pkeyword);
    Qsearch_backward_incrementally_for_text_in_editor = 
	    STATIC_SYMBOL("SEARCH-BACKWARD-INCREMENTALLY-FOR-TEXT-IN-EDITOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsearch_backward_incrementally_for_text_in_editor,
	    STATIC_FUNCTION(search_backward_incrementally_for_text_in_editor,
	    NIL,TRUE,1,2));
    Qend_editing = STATIC_SYMBOL("END-EDITING",AB_package);
    string_constant_13 = STATIC_STRING("no match");
    Qno_room = STATIC_SYMBOL("NO-ROOM",AB_package);
    Qfree = STATIC_SYMBOL("FREE",AB_package);
    Qfree_text_attribute = STATIC_SYMBOL("FREE-TEXT-ATTRIBUTE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    string_constant_14 = 
	    STATIC_STRING("An error, \"~a\", was reported at line ~d, \"~a\"");
    string_constant_15 = STATIC_STRING("An error, \"~a\", was reported.");
    if (In_recompile_item_p == UNBOUND)
	In_recompile_item_p = Nil;
    Qformula_qm = STATIC_SYMBOL("FORMULA\?",AB_package);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qnupec_extra_actions = STATIC_SYMBOL("NUPEC-EXTRA-ACTIONS",AB_package);
    Qtranslation_and_text_of_embedded_rule = 
	    STATIC_SYMBOL("TRANSLATION-AND-TEXT-OF-EMBEDDED-RULE",AB_package);
    Qcondition_for_using_user_menu_choice_qm = 
	    STATIC_SYMBOL("CONDITION-FOR-USING-USER-MENU-CHOICE\?",AB_package);
    Qaction_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("ACTION-FOR-USER-MENU-CHOICE\?",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qtrend_chart_plots = STATIC_SYMBOL("TREND-CHART-PLOTS",AB_package);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    Qsimulation_formulas_qm = STATIC_SYMBOL("SIMULATION-FORMULAS\?",
	    AB_package);
    Qtokenizer = STATIC_SYMBOL("TOKENIZER",AB_package);
    Qpatterns_definition = STATIC_SYMBOL("PATTERNS-DEFINITION",AB_package);
    Qtokens_definition = STATIC_SYMBOL("TOKENS-DEFINITION",AB_package);
    Qnew_table = STATIC_SYMBOL("NEW-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_table,New_table);
    Qfull_editor = STATIC_SYMBOL("FULL-EDITOR",AB_package);
    Qoption_buttons_for_edit_in_place = 
	    STATIC_SYMBOL("OPTION-BUTTONS-FOR-EDIT-IN-PLACE",AB_package);
    Qmenus_for_edit_in_place = STATIC_SYMBOL("MENUS-FOR-EDIT-IN-PLACE",
	    AB_package);
    Qdo_not_clear_text_for_edit_in_place = 
	    STATIC_SYMBOL("DO-NOT-CLEAR-TEXT-FOR-EDIT-IN-PLACE",AB_package);
    Qab_font = STATIC_SYMBOL("AB-FONT",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Ktight = STATIC_SYMBOL("TIGHT",Pkeyword);
    Qlost_spaces = STATIC_SYMBOL("LOST-SPACES",AB_package);
    Qleading = STATIC_SYMBOL("LEADING",AB_package);
    Qsubcommand_menu = STATIC_SYMBOL("SUBCOMMAND-MENU",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    list_constant_131 = STATIC_CONS(Qmenu,Qnil);
    check_if_superior_classes_are_defined(Qsubcommand_menu,list_constant_131);
    string_constant_55 = 
	    STATIC_STRING("1n4z8r83b1y83b1y9k9k00001n1l8l1l8o1l83Fy000004z8r83b0y83b0y9k9k00001n1l8l1l8o1l83Fy000004z8r83b=y83b=y9k9k00001n1l8l1l8o1l83Fy00");
    string_constant_56 = STATIC_STRING("000");
    string_constant_57 = 
	    STATIC_STRING("1p8q1m9k1l9l1p83b1y08l8o83Fy1p83b0y08l8o83Fy1p83b=y08l8o83Fy");
    temp = regenerate_optimized_constant(string_constant_20);
    clear_optimized_constants();
    push_optimized_constant(Qsubcommand_menu);
    temp_3 = regenerate_optimized_constant(LIST_2(string_constant_55,
	    string_constant_56));
    clear_optimized_constants();
    push_optimized_constant(Qsubcommand_menu);
    push_optimized_constant(Qmenu);
    add_class_to_environment(9,Qsubcommand_menu,list_constant_131,Nil,temp,
	    Nil,temp_3,list_constant_131,
	    regenerate_optimized_constant(string_constant_57),Nil);
    Qsubcommand_function_arglist_qm = 
	    STATIC_SYMBOL("SUBCOMMAND-FUNCTION-ARGLIST\?",AB_package);
    Qreclaim_subcommand_function_arglist_qm_value = 
	    STATIC_SYMBOL("RECLAIM-SUBCOMMAND-FUNCTION-ARGLIST\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_subcommand_function_arglist_qm_value,
	    STATIC_FUNCTION(reclaim_subcommand_function_arglist_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qsubcommand_function_arglist_qm,
	    SYMBOL_FUNCTION(Qreclaim_subcommand_function_arglist_qm_value),
	    Qslot_value_reclaimer);
    Qgenerate_spot_for_subcommand_menu = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-SUBCOMMAND-MENU",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_subcommand_menu,
	    STATIC_FUNCTION(generate_spot_for_subcommand_menu,NIL,FALSE,2,2));
    temp_4 = SYMBOL_FUNCTION(Qgenerate_spot_for_subcommand_menu);
    set_get(Qsubcommand_menu,Qgenerate_spot,temp_4);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_4 = CONS(Qsubcommand_menu,temp);
    mutate_global_property(Qgenerate_spot,temp_4,Qclasses_which_define);
    Qsubcommand_menu_item_format = 
	    STATIC_SYMBOL("SUBCOMMAND-MENU-ITEM-FORMAT",AB_package);
    string_constant_58 = 
	    STATIC_STRING("13Ly83-My83*Ky83*2y83-Ny83fy83byl83ayo83Wyl83cyo83ny1l83-uy83ty3Iy83sy3Dy83uyk83wy83-cy83iy32Cy");
    mutate_global_property(Qsubcommand_menu_item_format,
	    regenerate_optimized_constant(string_constant_58),
	    Qformat_description);
    Qsmall_subcommand_menu_item_format = 
	    STATIC_SYMBOL("SMALL-SUBCOMMAND-MENU-ITEM-FORMAT",AB_package);
    string_constant_59 = 
	    STATIC_STRING("13Ly83-My83*Ky83*2y83-Ny83fy83byl83ayn83Wyl83cyn83ny1l83-ry83ty3Dy83syz83uym83wy83-cy83iy31Qy");
    mutate_global_property(Qsmall_subcommand_menu_item_format,
	    regenerate_optimized_constant(string_constant_59),
	    Qformat_description);
    Qextra_large_subcommand_menu_item_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-SUBCOMMAND-MENU-ITEM-FORMAT",
	    AB_package);
    string_constant_60 = 
	    STATIC_STRING("13Ry83-My83*Ky83*2y83-Ny83fy83-7y3V+y83*3y3O+y83*+y3-G+y83byl83ayo83Wyl83cyo83ny1l8311y83ty3Oy83sy3Hy83uyk83wy83-cy83iy32Cy");
    mutate_global_property(Qextra_large_subcommand_menu_item_format,
	    regenerate_optimized_constant(string_constant_60),
	    Qformat_description);
    mutate_global_property(Qsubcommand_menu_item_format,
	    Qsmall_subcommand_menu_item_format,
	    Qcorresponding_small_font_format_name);
    mutate_global_property(Qsubcommand_menu_item_format,
	    Qextra_large_subcommand_menu_item_format,
	    Qcorresponding_extra_large_font_format_name);
    Qsubcommand_menu_table_format = 
	    STATIC_SYMBOL("SUBCOMMAND-MENU-TABLE-FORMAT",AB_package);
    string_constant_61 = 
	    STATIC_STRING("13Hy83*ny83=wy832py836Ky832py836Jy832py832Py832py8308ym830Aym8309ym8307ym83=Dyl83=Nyl");
    mutate_global_property(Qsubcommand_menu_table_format,
	    regenerate_optimized_constant(string_constant_61),
	    Qformat_description);
    Qany_token_menu_item_format = 
	    STATIC_SYMBOL("ANY-TOKEN-MENU-ITEM-FORMAT",AB_package);
    string_constant_62 = 
	    STATIC_STRING("13Ly83-My83*Ky83*2y83-Ny83fy83byr83ayn83Wyr83cyn83ny1l83-uy83ty3Gy83syz83uyk83wy83-cy83iy32Cy");
    mutate_global_property(Qany_token_menu_item_format,
	    regenerate_optimized_constant(string_constant_62),
	    Qformat_description);
    Qsmall_any_token_menu_item_format = 
	    STATIC_SYMBOL("SMALL-ANY-TOKEN-MENU-ITEM-FORMAT",AB_package);
    string_constant_63 = 
	    STATIC_STRING("13Ny83-My83*Ky83*2y83-Ny83fy83byq83aym83aym83Wyq83cym83ny1l83-ry83tyz83syx83uym83wy83-cy83iy31Qy");
    mutate_global_property(Qsmall_any_token_menu_item_format,
	    regenerate_optimized_constant(string_constant_63),
	    Qformat_description);
    mutate_global_property(Qany_token_menu_item_format,
	    Qsmall_any_token_menu_item_format,
	    Qcorresponding_small_font_format_name);
    Qtoken_menu_item_format = STATIC_SYMBOL("TOKEN-MENU-ITEM-FORMAT",
	    AB_package);
    string_constant_64 = 
	    STATIC_STRING("13Jy83-My83byr83ayn83Wyr83cyn83ny1l83-uy83ty3Gy83syz83uyk83wy83-cy83iy32Cy832cy3uy");
    mutate_global_property(Qtoken_menu_item_format,
	    regenerate_optimized_constant(string_constant_64),
	    Qformat_description);
    Qsmall_token_menu_item_format = 
	    STATIC_SYMBOL("SMALL-TOKEN-MENU-ITEM-FORMAT",AB_package);
    string_constant_65 = 
	    STATIC_STRING("13Hy83-My83byq83aym83Wyq83cym83ny1l83-ry83tyz83syx83uym83wy83-cy83iy31Qy");
    mutate_global_property(Qsmall_token_menu_item_format,
	    regenerate_optimized_constant(string_constant_65),
	    Qformat_description);
    mutate_global_property(Qtoken_menu_item_format,
	    Qsmall_token_menu_item_format,
	    Qcorresponding_small_font_format_name);
    Qany_token_menu_format = STATIC_SYMBOL("ANY-TOKEN-MENU-FORMAT",AB_package);
    string_constant_66 = 
	    STATIC_STRING("1z83*ny83=wy83*2y83=Dyk83=Nyk8308yk830Ayk8309yk8307yk");
    mutate_global_property(Qany_token_menu_format,
	    regenerate_optimized_constant(string_constant_66),
	    Qformat_description);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Background_color_for_enabled_subcommands = Qforeground;
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Text_color_for_enabled_subcommands = Qbackground;
    Background_color_for_disabled_subcommands = Qbackground;
    Text_color_for_disabled_subcommands = Qbackground;
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Highlight_color_for_enabled_pending_subcommands = Qtransparent;
    Highlight_color_for_enabled_non_pending_subcommands = Qforeground;
    Highlight_color_for_disabled_pending_subcommands = Qtransparent;
    Highlight_color_for_disabled_non_pending_subcommands = Qtransparent;
    Highlight_color_for_pending_on_radio_button_subcommands = Qforeground;
    Highlight_color_for_non_pending_on_radio_button_subcommands = Qtransparent;
    Highlight_color_for_pending_off_radio_button_subcommands = Qtransparent;
    Highlight_color_for_non_pending_off_radio_button_subcommands = Qforeground;
    Qbutton_label = STATIC_SYMBOL("BUTTON-LABEL",AB_package);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    string_constant_16 = STATIC_STRING(" ~a ");
    Qspecial_case_qm = STATIC_SYMBOL("SPECIAL-CASE\?",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qeditor_subcommand_button = STATIC_SYMBOL("EDITOR-SUBCOMMAND-BUTTON",
	    AB_package);
    Qeditor_subcommand_disabled_p = 
	    STATIC_SYMBOL("EDITOR-SUBCOMMAND-DISABLED-P",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qenable_or_disable_subcommand = 
	    STATIC_SYMBOL("ENABLE-OR-DISABLE-SUBCOMMAND",AB_package);
    Qeditor_subcommand_name = STATIC_SYMBOL("EDITOR-SUBCOMMAND-NAME",
	    AB_package);
    Qsubcommand_button_radio_button_status = 
	    STATIC_SYMBOL("SUBCOMMAND-BUTTON-RADIO-BUTTON-STATUS",AB_package);
    Kno_change = STATIC_SYMBOL("NO-CHANGE",Pkeyword);
    Qradio_button_status = STATIC_SYMBOL("RADIO-BUTTON-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qenable_or_disable_subcommand,
	    STATIC_FUNCTION(enable_or_disable_subcommand,NIL,TRUE,3,4));
    Qoff = STATIC_SYMBOL("OFF",AB_package);
    Qon = STATIC_SYMBOL("ON",AB_package);
    Qindicate_subcommand_pending_state = 
	    STATIC_SYMBOL("INDICATE-SUBCOMMAND-PENDING-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qindicate_subcommand_pending_state,
	    STATIC_FUNCTION(indicate_subcommand_pending_state,NIL,TRUE,3,6));
    Qg2_defstruct_structure_name_subcommand_state_g2_struct = 
	    STATIC_SYMBOL("SUBCOMMAND-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsubcommand_state = STATIC_SYMBOL("SUBCOMMAND-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_subcommand_state_g2_struct,
	    Qsubcommand_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsubcommand_state,
	    Qg2_defstruct_structure_name_subcommand_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_subcommand_state == UNBOUND)
	The_type_description_of_subcommand_state = Nil;
    string_constant_67 = 
	    STATIC_STRING("43Dy8m83nUy1o83nUy83-Sy8n8k1l83-Sy0000001m1n8y83-6*y1n83-Dwy83-DXy83-CWy1m8x83-Sykqk0k0");
    temp = The_type_description_of_subcommand_state;
    The_type_description_of_subcommand_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_67));
    mutate_global_property(Qg2_defstruct_structure_name_subcommand_state_g2_struct,
	    The_type_description_of_subcommand_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsubcommand_state,
	    The_type_description_of_subcommand_state,
	    Qtype_description_of_type);
    Qoutstanding_subcommand_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-SUBCOMMAND-STATE-COUNT",AB_package);
    Qsubcommand_state_structure_memory_usage = 
	    STATIC_SYMBOL("SUBCOMMAND-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_68 = STATIC_STRING("1q83nUy8s83-rMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_subcommand_state_count);
    push_optimized_constant(Qsubcommand_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qchain_of_available_subcommand_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SUBCOMMAND-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_subcommand_states,
	    Chain_of_available_subcommand_states);
    record_system_variable(Qchain_of_available_subcommand_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsubcommand_state_count = STATIC_SYMBOL("SUBCOMMAND-STATE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubcommand_state_count,Subcommand_state_count);
    record_system_variable(Qsubcommand_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_subcommand_states_vector == UNBOUND)
	Chain_of_available_subcommand_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsubcommand_state_structure_memory_usage,
	    STATIC_FUNCTION(subcommand_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_subcommand_state_count,
	    STATIC_FUNCTION(outstanding_subcommand_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_subcommand_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_subcommand_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsubcommand_state,
	    reclaim_structure_for_subcommand_state_1);
    Qtop_level_with_mouse_tracking_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qsubcommand_state,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qsubcommand = STATIC_SYMBOL("SUBCOMMAND",AB_package);
    make_context_description(Qsubcommand,Qnil,Qt,Qnil);
    Qmouse_up_in_subcommand_state = 
	    STATIC_SYMBOL("MOUSE-UP-IN-SUBCOMMAND-STATE",AB_package);
    Qmouse_motion_in_subcommand_state = 
	    STATIC_SYMBOL("MOUSE-MOTION-IN-SUBCOMMAND-STATE",AB_package);
    Qabort_workstation_context = STATIC_SYMBOL("ABORT-WORKSTATION-CONTEXT",
	    AB_package);
    string_constant_69 = STATIC_STRING("1n1n830-y8k9k1n830+y8k9l1n831-y8k9m");
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qmouse_up_in_subcommand_state);
    push_optimized_constant(Qmouse_motion_in_subcommand_state);
    push_optimized_constant(Qabort_workstation_context);
    make_keymap(Qsubcommand,Qsubcommand,
	    regenerate_optimized_constant(string_constant_69),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qsubcommand,Qsubcommand);
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    valid_workstation_context_p_for_subcommand_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_subcommand_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qsubcommand_state,
	    valid_workstation_context_p_for_subcommand_state_1);
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_subcommand_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_subcommand_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qsubcommand_state,
	    clean_up_workstation_context_for_subcommand_state_1);
    Qenter_subcommand_context = STATIC_SYMBOL("ENTER-SUBCOMMAND-CONTEXT",
	    AB_package);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qenter_subcommand_context,
	    Qenter_subcommand_context,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qenter_subcommand_context,
	    STATIC_FUNCTION(enter_subcommand_context,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_motion_in_subcommand_state,
	    Qmouse_motion_in_subcommand_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_subcommand_state,
	    STATIC_FUNCTION(mouse_motion_in_subcommand_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_up_in_subcommand_state,
	    Qmouse_up_in_subcommand_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_up_in_subcommand_state,
	    STATIC_FUNCTION(mouse_up_in_subcommand_state,NIL,FALSE,1,1));
    Qcut = STATIC_SYMBOL("CUT",AB_package);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qinsert = STATIC_SYMBOL("INSERT",AB_package);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qcut_and_insert = STATIC_SYMBOL("CUT-AND-INSERT",AB_package);
    list_constant_132 = STATIC_LIST((SI_Long)7L,Qcut,Qcopy,Qpaste,Qdelete,
	    Qinsert,Qmove,Qcut_and_insert);
    Edit_operation_subcommand_names = list_constant_132;
    list_constant_133 = STATIC_CONS(Qpaste,Qnil);
    Edit_operation_subcommand_names_after_removals = list_constant_133;
    Qcancel = STATIC_SYMBOL("CANCEL",AB_package);
    Qupdate = STATIC_SYMBOL("UPDATE",AB_package);
    list_constant_134 = STATIC_LIST((SI_Long)5L,Qcancel,Qundo,Qredo,Qend,
	    Qupdate);
    Basic_core_edit_subcommand_choices = list_constant_134;
    Core_edit_subcommand_choices = 
	    nconc2(copy_list(Basic_core_edit_subcommand_choices),
	    Edit_operation_subcommand_names);
    Core_edit_subcommand_choices_after_removals = 
	    nconc2(copy_list(Basic_core_edit_subcommand_choices),
	    Edit_operation_subcommand_names_after_removals);
    Qkatakana = STATIC_SYMBOL("KATAKANA",AB_package);
    Qhiragana = STATIC_SYMBOL("HIRAGANA",AB_package);
    Qenglish = STATIC_SYMBOL("ENGLISH",AB_package);
    Qconvert = STATIC_SYMBOL("CONVERT",AB_package);
    Qnext = STATIC_SYMBOL("NEXT",AB_package);
    Qprevious = STATIC_SYMBOL("PREVIOUS",AB_package);
    Qskip = STATIC_SYMBOL("SKIP",AB_package);
    Qaccept = STATIC_SYMBOL("ACCEPT",AB_package);
    Qexpand = STATIC_SYMBOL("EXPAND",AB_package);
    Qshrink = STATIC_SYMBOL("SHRINK",AB_package);
    list_constant_135 = STATIC_LIST((SI_Long)11L,Qkanji,Qkatakana,
	    Qhiragana,Qenglish,Qconvert,Qnext,Qprevious,Qskip,Qaccept,
	    Qexpand,Qshrink);
    Kfep_edit_subcommand_choices = list_constant_135;
    list_constant_136 = STATIC_LIST((SI_Long)2L,Qenglish,Qhangul);
    Hfep_edit_subcommand_choices = list_constant_136;
    list_constant_137 = STATIC_LIST((SI_Long)2L,Qenglish,Qcyrillic);
    Cfep_edit_subcommand_choices = list_constant_137;
    string_constant_70 = 
	    STATIC_STRING("1n13Ky8378y2l83-LSy+3Cy3=*ay3==3y3=*Vy3=*xy30qfy32fUykkkkkkkkq3A++y2l83dOy+3Cy32F9y30vOy31BIy3=*6y32o4y3=-Jykkkkkkkkq3A++y2l83m4");
    string_constant_71 = 
	    STATIC_STRING("y+s32F9y30vOy3129y31gRy34T8ykp3A++y2l9k+3Cy3=*ay3==3y3=*Vy3=*xy33n*y30s2ykkkkkkkkq3A++y2l837cy+s32Nmy32Iiykkkkm3A++y2l83gSy+s3=*");
    string_constant_72 = 
	    STATIC_STRING("dy3===y3==4ykkkn3A++y2l83Ipy+s3=*ly3==Gy3==uykkkn3A++y2l83lSy+s3==My3==uy3=*ry3==4ykko3A++y2l9l+s3156y35LWykkkkm3A++y2l83-=by+s3");
    string_constant_73 = 
	    STATIC_STRING("28xy311Xykkkkm3A++y2l83*py+s33Zty317Hykkkkm3A++y2l83-Pby+3Cy3=*dy3===y3==4y3Bu2y328xy311Xykkkkkkkkq3A++y2l83-bky+s32uUy31fJykkkk");
    string_constant_74 = 
	    STATIC_STRING("m3A++y2l83-bmy+s3=*dy3=*xy3=*dy3==6ykko3A++y2l83-Y4y+s3=-ky3=*5y3=-8y3=-cykko3A++y2l83vYy+s347jy34cQykkkkm3A++y2l83-Oey+s31W5y32");
    string_constant_75 = 
	    STATIC_STRING("BNykkkkm3A++y2l837Fy+s32eTy31+Ly34VOykkkn3A++y2l83-jYy+s3159y31+Ly34VOykkkn3A++y2l83-q=y+s3=*ry3=*fy3===y3==Jykko3A++y2l83-J2y+s");
    string_constant_76 = 
	    STATIC_STRING("3=*Uy3=*hy3=*ty3==Jy3==4ykp3A++y2l83-TIy+3Cy31W5y32BNy33h0y31Nky327Ty31unykkkkkkkkq3A++y2l83-pBy+3Cy31W5y32BNy33h0y31Nky33qgy31i");
    string_constant_77 = 
	    STATIC_STRING("Bykkkkkkkkq3A++y1z83kDy2l83-LSy+s38pay3828ykkkkm3A++y2l83dOy+s37lny36neykkkkm3A++y2l83m4y+s38Qey387Oy37B0ykkkn3A++y2l9k+s37-Pykk");
    string_constant_78 = 
	    STATIC_STRING("kkkl3A++y2l837cy+s384Ky38SHykkkkm3A++y2l83gSy+s38KWy37SWy37DCy36qiykko3A++y2l83Ipy+s37kSy37-uy36qiykkkn3A++y2l83lSy+s37oLy38Pmy3");
    string_constant_79 = 
	    STATIC_STRING("6qiykkkn3A++y2l9l+s38Z+y38Miy36qiykkkn3A++y2l83-=by+s37-uy38Miy36qiykkkn3A++y2l83*py+3Cy3988y37*my38Imy3Sy38Kgy36qiy36qiykkkkkkk");
    string_constant_80 = 
	    STATIC_STRING("r3A++y2l83-Pby+3Cy386Wy39-ey37Qby39HKy37bmy380Oy3Sy37-uy38N8y370Vy36qiykkkv3A++y2l83vYy+s38K-y37eqykkkkm3A++y2l83-Xey+s39HOy36q+");
    string_constant_81 = 
	    STATIC_STRING("ykkkkm3A++y1t83-C8y2l83-LSy+3Cy3CQy3D*y3Cuy3Cny3Cvy3Cqy3D*y3D8ykkkkkks3A++y2l9k+3Cy3CJy3Ciy3Csy3Cwy3Cvy3D3y3Cqy3D*y3D8ykkkkkt3A+");
    string_constant_82 = 
	    STATIC_STRING("+y2l83lSy+3Cy3CEy3D-y3D*y3Ciy3Cky3Cqy3D*y3D8ykkkkkks3A++y2l83m4y+3Cy3CEy3Cwy3D-y3D-y3D*y3Ciy3Cvy3Cwy3Cky3Cqy3D*y3D8ykkw3A++y2l83");
    string_constant_83 = 
	    STATIC_STRING("dOy+s3CQy3D*y3Csy3Ciy3D*ykp3A++y2l837cy+3Cy3CQy3Cjy3Cvy3Cwy3Cky3Cqy3D*y3D8ykkkkkks3A++y2l83vYy+3Cy3CCy3Cvy3Cly3Cty3Cqy3Cry3D-y3C");
    string_constant_84 = 
	    STATIC_STRING("sy3Cqy3Crykkkku3A++y2l83-Phy+3Cy3CMy3Cqy3D+y3Cqy3Cty3Cty3Cqy3D2y3Ciykkkkkt3A++y");
    clear_optimized_constants();
    push_optimized_constant(Qend);
    push_optimized_constant(Qdelete);
    Built_in_subcommand_menu_choice_translations = 
	    regenerate_optimized_constant(list(15,string_constant_70,
	    string_constant_71,string_constant_72,string_constant_73,
	    string_constant_74,string_constant_75,string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79,
	    string_constant_80,string_constant_81,string_constant_82,
	    string_constant_83,string_constant_84));
    Include_original_choice_in_subcommand_menu_choice_translation_qm = Nil;
    string_constant_17 = STATIC_STRING("~a ~a");
    list_constant = STATIC_LIST((SI_Long)3L,Qinsert,Qmove,Qcut_and_insert);
    Qend_exit = STATIC_SYMBOL("END-EXIT",AB_package);
    Qdo_edit_subcommand = STATIC_SYMBOL("DO-EDIT-SUBCOMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qdo_edit_subcommand,
	    STATIC_FUNCTION(do_edit_subcommand,NIL,FALSE,1,1));
    if (Kfep_search_limit_1 == UNBOUND)
	Kfep_search_limit_1 = FIX((SI_Long)50L);
    if (Kfep_search_limit_2 == UNBOUND)
	Kfep_search_limit_2 = FIX((SI_Long)100L);
    Qskip_kfep_conversion = STATIC_SYMBOL("SKIP-KFEP-CONVERSION",AB_package);
    SET_SYMBOL_FUNCTION(Qskip_kfep_conversion,
	    STATIC_FUNCTION(skip_kfep_conversion,NIL,FALSE,0,0));
    string_constant_18 = STATIC_STRING("foo");
    Qkfep_conversion_choice_menu = 
	    STATIC_SYMBOL("KFEP-CONVERSION-CHOICE-MENU",AB_package);
    Qtext_region = STATIC_SYMBOL("TEXT-REGION",AB_package);
    Qup = STATIC_SYMBOL("UP",AB_package);
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    if (Trace_parsing_context_p == UNBOUND)
	Trace_parsing_context_p = Nil;
    if (Trace_parsing_context_tokenizing_p == UNBOUND)
	Trace_parsing_context_tokenizing_p = Nil;
    Qg2_defstruct_structure_name_parsing_token_g2_struct = 
	    STATIC_SYMBOL("PARSING-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparsing_token = STATIC_SYMBOL("PARSING-TOKEN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_parsing_token_g2_struct,
	    Qparsing_token,Qab_name_of_unique_structure_type);
    mutate_global_property(Qparsing_token,
	    Qg2_defstruct_structure_name_parsing_token_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_parsing_token == UNBOUND)
	The_type_description_of_parsing_token = Nil;
    string_constant_85 = 
	    STATIC_STRING("43Dy8m83lQy1n83lQy8n8k1l8n0000000kxk0k0");
    temp = The_type_description_of_parsing_token;
    The_type_description_of_parsing_token = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_85));
    mutate_global_property(Qg2_defstruct_structure_name_parsing_token_g2_struct,
	    The_type_description_of_parsing_token,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qparsing_token,
	    The_type_description_of_parsing_token,Qtype_description_of_type);
    Qoutstanding_parsing_token_count = 
	    STATIC_SYMBOL("OUTSTANDING-PARSING-TOKEN-COUNT",AB_package);
    Qparsing_token_structure_memory_usage = 
	    STATIC_SYMBOL("PARSING-TOKEN-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_86 = STATIC_STRING("1q83lQy8s83-iOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_parsing_token_count);
    push_optimized_constant(Qparsing_token_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_86));
    Qchain_of_available_parsing_tokens = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PARSING-TOKENS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_parsing_tokens,
	    Chain_of_available_parsing_tokens);
    record_system_variable(Qchain_of_available_parsing_tokens,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qparsing_token_count = STATIC_SYMBOL("PARSING-TOKEN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qparsing_token_count,Parsing_token_count);
    record_system_variable(Qparsing_token_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_parsing_tokens_vector == UNBOUND)
	Chain_of_available_parsing_tokens_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qparsing_token_structure_memory_usage,
	    STATIC_FUNCTION(parsing_token_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_parsing_token_count,
	    STATIC_FUNCTION(outstanding_parsing_token_count,NIL,FALSE,0,0));
    reclaim_structure_for_parsing_token_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_parsing_token,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qparsing_token,
	    reclaim_structure_for_parsing_token_1);
    if (Current_parsing_context_text == UNBOUND)
	Current_parsing_context_text = Nil;
    if (Current_parsing_context_text_length == UNBOUND)
	Current_parsing_context_text_length = Nil;
    if (Current_parsing_context_line == UNBOUND)
	Current_parsing_context_line = Nil;
    if (Current_parsing_context_character == UNBOUND)
	Current_parsing_context_character = Nil;
    Qg2_defstruct_structure_name_parsing_context_g2_struct = 
	    STATIC_SYMBOL("PARSING-CONTEXT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparsing_context = STATIC_SYMBOL("PARSING-CONTEXT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_parsing_context_g2_struct,
	    Qparsing_context,Qab_name_of_unique_structure_type);
    mutate_global_property(Qparsing_context,
	    Qg2_defstruct_structure_name_parsing_context_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_parsing_context == UNBOUND)
	The_type_description_of_parsing_context = Nil;
    string_constant_87 = 
	    STATIC_STRING("43Dy8m83lPy1p83lPy83Bsy83-Sy8n8k1l83Bsy0000001m1m8x83Bsy1m83My83-Aiyk3-hyk0k0");
    temp = The_type_description_of_parsing_context;
    The_type_description_of_parsing_context = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_87));
    mutate_global_property(Qg2_defstruct_structure_name_parsing_context_g2_struct,
	    The_type_description_of_parsing_context,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qparsing_context,
	    The_type_description_of_parsing_context,Qtype_description_of_type);
    Qoutstanding_parsing_context_count = 
	    STATIC_SYMBOL("OUTSTANDING-PARSING-CONTEXT-COUNT",AB_package);
    Qparsing_context_structure_memory_usage = 
	    STATIC_SYMBOL("PARSING-CONTEXT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_88 = STATIC_STRING("1q83lPy8s83-iNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_parsing_context_count);
    push_optimized_constant(Qparsing_context_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_88));
    Qchain_of_available_parsing_contexts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PARSING-CONTEXTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_parsing_contexts,
	    Chain_of_available_parsing_contexts);
    record_system_variable(Qchain_of_available_parsing_contexts,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qparsing_context_count = STATIC_SYMBOL("PARSING-CONTEXT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qparsing_context_count,Parsing_context_count);
    record_system_variable(Qparsing_context_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_parsing_contexts_vector == UNBOUND)
	Chain_of_available_parsing_contexts_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qparsing_context_structure_memory_usage,
	    STATIC_FUNCTION(parsing_context_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_parsing_context_count,
	    STATIC_FUNCTION(outstanding_parsing_context_count,NIL,FALSE,0,0));
    reclaim_structure_for_parsing_context_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_parsing_context,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qparsing_context,
	    reclaim_structure_for_parsing_context_1);
    list_constant_138 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    clean_up_workstation_context_for_parsing_context_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_parsing_context,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qparsing_context,
	    clean_up_workstation_context_for_parsing_context_1);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qtype,Qfree,Qtext);
    Qirrelevant = STATIC_SYMBOL("IRRELEVANT",AB_package);
    Qframe_is_null_or_reprocessed = 
	    STATIC_SYMBOL("FRAME-IS-NULL-OR-REPROCESSED",AB_package);
    Qparse_is_bad = STATIC_SYMBOL("PARSE-IS-BAD",AB_package);
    Qtext_is_incomplete = STATIC_SYMBOL("TEXT-IS-INCOMPLETE",AB_package);
    Qparse_is_incomplete = STATIC_SYMBOL("PARSE-IS-INCOMPLETE",AB_package);
    Qambiguous_phrase = STATIC_SYMBOL("AMBIGUOUS-PHRASE",AB_package);
    Qparse_is_ambiguous = STATIC_SYMBOL("PARSE-IS-AMBIGUOUS",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)57344L);
    Qafter_error = STATIC_SYMBOL("AFTER-ERROR",AB_package);
    Qparsing_context_complete_status = 
	    STATIC_SYMBOL("PARSING-CONTEXT-COMPLETE-STATUS",AB_package);
    Qso_far_so_good_2 = STATIC_SYMBOL("SO-FAR-SO-GOOD-2",AB_package);
    Qso_far_so_good_3 = STATIC_SYMBOL("SO-FAR-SO-GOOD-3",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,
	    Qparsing_context_complete_status,Qso_far_so_good_2,
	    Qso_far_so_good_3);
    Qg2_comment = STATIC_SYMBOL("G2-COMMENT",AB_package);
    list_constant_3 = STATIC_CONS(Qg2_comment,Qnil);
    array_constant_2 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    Qproblem_token = STATIC_SYMBOL("PROBLEM-TOKEN",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    Qincomplete_token = STATIC_SYMBOL("INCOMPLETE-TOKEN",AB_package);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    Qin_comment = STATIC_SYMBOL("IN-COMMENT",AB_package);
    Qquoted_character = STATIC_SYMBOL("QUOTED-CHARACTER",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    Qunknown_token_type = STATIC_SYMBOL("UNKNOWN-TOKEN-TYPE",AB_package);
    Qellipsis = STATIC_SYMBOL("ELLIPSIS",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_138,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    Qfound_ellipsis = STATIC_SYMBOL("FOUND-ELLIPSIS",AB_package);
    string_constant_19 = STATIC_STRING("any ~(~a~)");
}
