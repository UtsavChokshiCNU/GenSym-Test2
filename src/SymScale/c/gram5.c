/* gram5.c
 * Input file:  grammar5.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram5.h"


/* WRITE-ATTRIBUTE-FROM-SLOT */
Object write_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    x_note_fn_call(199,0);
    return write_attribute(attribute);
}

static Object array_constant;      /* # */

static Object string_constant;     /* "~s" */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object array_constant_1;    /* # */

/* WRITE-ATTRIBUTE */
Object write_attribute(attribute)
    Object attribute;
{
    Object temp, car_1, cdr_1, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(199,1);
    Leave_text_representation_as_a_single_line_qm = T;
    if ( !TRUEP(attribute))
	temp = twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(attribute) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute)) == (SI_Long)1L)
	temp = print_constant(2,attribute,Qnumber);
    else if (slot_value_number_p(attribute))
	temp = print_constant(2,attribute,Qnumber);
    else if (SYMBOLP(attribute))
	temp = print_constant(2,attribute,Qsymbol);
    else if (text_string_p(attribute)) {
	Leave_text_representation_as_a_single_line_qm = Nil;
	temp = tformat(2,string_constant,attribute);
    }
    else {
	if (CONSP(attribute)) {
	    car_1 = M_CAR(attribute);
	    cdr_1 = M_CDR(attribute);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = print_constant(2,M_CAR(attribute),M_CAR(M_CDR(attribute)));
	else {
	    gensymed_symbol = attribute;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp = write_evaluation_value(1,attribute);
	    else {
		if (SIMPLE_VECTOR_P(attribute) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute)) > 
			(SI_Long)2L &&  !EQ(ISVREF(attribute,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(attribute,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if ( !temp_1)
		    temp = 
			    twrite_beginning_of_wide_string(array_constant_1,
			    FIX((SI_Long)26L));
		else
		    temp = write_entity_in_slot(attribute);
	    }
	}
    }
    return VALUES_1(temp);
}

/* WRITE-ITEM-OR-DATUM-OR-NO-ITEM-ATTRIBUTE-FROM-SLOT */
Object write_item_or_datum_or_no_item_attribute_from_slot(attribute,
	    gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    Object car_1, cdr_1, temp, slot_value, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_2, entry_hash;
    Object in_text_for_item_or_value_p, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,2);
    Leave_text_representation_as_a_single_line_qm = T;
    if ( !TRUEP(attribute))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (slot_value_number_p(attribute))
	return print_constant(2,attribute,Qnumber);
    else if (SYMBOLP(attribute))
	return print_constant(2,attribute,Qsymbol);
    else if (text_string_p(attribute)) {
	Leave_text_representation_as_a_single_line_qm = Nil;
	return tformat(2,string_constant,attribute);
    }
    else {
	if (CONSP(attribute)) {
	    car_1 = M_CAR(attribute);
	    cdr_1 = M_CDR(attribute);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    slot_value = FIRST(attribute);
	    if (text_string_p(slot_value)) {
		Leave_text_representation_as_a_single_line_qm = Nil;
		return tformat(2,string_constant,slot_value);
	    }
	    else
		return print_constant(2,M_CAR(attribute),
			M_CAR(M_CDR(attribute)));
	}
	else {
	    gensymed_symbol = attribute;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		in_text_for_item_or_value_p = T;
		PUSH_SPECIAL_WITH_SYMBOL(In_text_for_item_or_value_p,Qin_text_for_item_or_value_p,in_text_for_item_or_value_p,
			0);
		  result = write_evaluation_value(1,attribute);
		POP_SPECIAL();
		return result;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(attribute,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return write_entity_in_slot(attribute);
		else
		    return twrite_beginning_of_wide_string(array_constant_1,
			    FIX((SI_Long)26L));
	    }
	}
    }
}

/* WRITE-ITEM-OR-DATUM-ATTRIBUTE-FROM-SLOT */
Object write_item_or_datum_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    Object car_1, cdr_1, temp, slot_value, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_2, entry_hash;
    Object in_text_for_item_or_value_p, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,3);
    Leave_text_representation_as_a_single_line_qm = T;
    if ( !TRUEP(attribute))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (slot_value_number_p(attribute))
	return print_constant(2,attribute,Qnumber);
    else if (SYMBOLP(attribute))
	return print_constant(2,attribute,Qsymbol);
    else if (text_string_p(attribute)) {
	Leave_text_representation_as_a_single_line_qm = Nil;
	return tformat(2,string_constant,attribute);
    }
    else {
	if (CONSP(attribute)) {
	    car_1 = M_CAR(attribute);
	    cdr_1 = M_CDR(attribute);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    slot_value = FIRST(attribute);
	    if (text_string_p(slot_value)) {
		Leave_text_representation_as_a_single_line_qm = Nil;
		return tformat(2,string_constant,slot_value);
	    }
	    else
		return print_constant(2,M_CAR(attribute),
			M_CAR(M_CDR(attribute)));
	}
	else {
	    gensymed_symbol = attribute;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		in_text_for_item_or_value_p = T;
		PUSH_SPECIAL_WITH_SYMBOL(In_text_for_item_or_value_p,Qin_text_for_item_or_value_p,in_text_for_item_or_value_p,
			0);
		  result = write_evaluation_value(1,attribute);
		POP_SPECIAL();
		return result;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(attribute,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return write_entity_in_slot(attribute);
		else
		    return twrite_beginning_of_wide_string(array_constant_1,
			    FIX((SI_Long)26L));
	    }
	}
    }
}

/* WRITE-DATUM-ATTRIBUTE-FROM-SLOT */
Object write_datum_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    Object car_1, cdr_1, temp, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, in_text_for_item_or_value_p;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,4);
    Leave_text_representation_as_a_single_line_qm = T;
    if ( !TRUEP(attribute))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (slot_value_number_p(attribute))
	return print_constant(2,attribute,Qnumber);
    else if (SYMBOLP(attribute))
	return print_constant(2,attribute,Qsymbol);
    else if (text_string_p(attribute)) {
	Leave_text_representation_as_a_single_line_qm = Nil;
	return tformat(2,string_constant,attribute);
    }
    else {
	if (CONSP(attribute)) {
	    car_1 = M_CAR(attribute);
	    cdr_1 = M_CDR(attribute);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(attribute),M_CAR(M_CDR(attribute)));
	else {
	    gensymed_symbol = attribute;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		in_text_for_item_or_value_p = T;
		PUSH_SPECIAL_WITH_SYMBOL(In_text_for_item_or_value_p,Qin_text_for_item_or_value_p,in_text_for_item_or_value_p,
			0);
		  result = write_evaluation_value(1,attribute);
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* WRITE-STRUCTURE-ATTRIBUTE-FROM-SLOT */
Object write_structure_attribute_from_slot(structure,gensymed_symbol)
    Object structure, gensymed_symbol;
{
    Object in_text_for_item_or_value_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,5);
    in_text_for_item_or_value_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_text_for_item_or_value_p,Qin_text_for_item_or_value_p,in_text_for_item_or_value_p,
	    0);
      result = write_evaluation_structure(structure);
    POP_SPECIAL();
    return result;
}

/* WRITE-SEQUENCE-ATTRIBUTE-FROM-SLOT */
Object write_sequence_attribute_from_slot(sequence,gensymed_symbol)
    Object sequence, gensymed_symbol;
{
    Object in_text_for_item_or_value_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,6);
    in_text_for_item_or_value_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_text_for_item_or_value_p,Qin_text_for_item_or_value_p,in_text_for_item_or_value_p,
	    0);
      result = write_evaluation_sequence(sequence);
    POP_SPECIAL();
    return result;
}

/* WRITE-NUMBER-ATTRIBUTE-FROM-SLOT */
Object write_number_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,7);
    if (slot_value_number_p(number))
	return print_constant(2,number,Qnumber);
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(number),M_CAR(M_CDR(number)));
	else
	    return VALUES_1(Qt);
    }
}

/* WRITE-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,8);
    if (slot_value_number_p(number))
	return print_constant(2,number,Qnumber);
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(number),M_CAR(M_CDR(number)));
	else
	    return VALUES_1(Qt);
    }
}

/* WRITE-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,9);
    if (slot_value_number_p(number))
	return print_constant(2,number,Qnumber);
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(number),M_CAR(M_CDR(number)));
	else
	    return VALUES_1(Qt);
    }
}

static Object Qseconds;            /* seconds */

/* WRITE-GENERAL-INTERVAL-ATTRIBUTE */
Object write_general_interval_attribute(number)
    Object number;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,10);
    if (slot_value_number_p(number))
	return print_constant(2,number,Qseconds);
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(number),Qseconds);
	else
	    return VALUES_1(Qt);
    }
}

/* COMPILE-INTERVAL-ATTRIBUTE-FOR-SLOT */
Object compile_interval_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,11);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(CAR(parse_result));
}

/* COMPILE-INTERVAL-INTEGER-ATTRIBUTE-FOR-SLOT */
Object compile_interval_integer_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,12);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(CAR(parse_result));
}

/* COMPILE-INTERVAL-FLOAT-ATTRIBUTE-FOR-SLOT */
Object compile_interval_float_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,13);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return coerce_phrase_number_to_float(CAR(parse_result));
}

/* WRITE-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_interval_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,14);
    return write_general_interval_attribute(number);
}

/* WRITE-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_interval_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,15);
    return write_general_interval_attribute(number);
}

/* WRITE-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_interval_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,16);
    return write_general_interval_attribute(number);
}

static Object Qtime_stamp;         /* time-stamp */

/* WRITE-GENERAL-TIME-STAMP-ATTRIBUTE */
Object write_general_time_stamp_attribute(number)
    Object number;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,17);
    if (slot_value_number_p(number))
	return print_constant(2,number,Qtime_stamp);
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return print_constant(2,M_CAR(number),Qtime_stamp);
	else
	    return VALUES_1(Qt);
    }
}

/* WRITE-TIME-STAMP-ATTRIBUTE-FROM-SLOT */
Object write_time_stamp_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,18);
    return write_general_time_stamp_attribute(number);
}

/* WRITE-TIME-STAMP-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_time_stamp_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,19);
    return write_general_time_stamp_attribute(number);
}

/* WRITE-TIME-STAMP-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_time_stamp_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,20);
    return write_general_time_stamp_attribute(number);
}

/* WRITE-GENERAL-DDD.DDDD-FORMAT-ATTRIBUTE */
Object write_general_ddd_dot_dddd_format_attribute(number)
    Object number;
{
    Object value, car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(199,21);
    if (slot_value_number_p(number))
	value = number;
    else {
	if (CONSP(number)) {
	    car_1 = M_CAR(number);
	    cdr_1 = M_CDR(number);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	value = temp_1 ? M_CAR(number) : Nil;
    }
    if (value) {
	if (Current_ddd_dot_dddd_format_qm) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		temp = aref1(value,FIX((SI_Long)0L));
	    else
		temp = value;
	    return twrite_number_per_format(temp,
		    Current_ddd_dot_dddd_format_qm);
	}
	else
	    return print_constant(2,value,Qnumber);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-DDD.DDDD-FORMAT-ATTRIBUTE-FROM-SLOT */
Object write_ddd_dot_dddd_format_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,22);
    return write_general_ddd_dot_dddd_format_attribute(number);
}

/* WRITE-DDD.DDDD-FORMAT-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_ddd_dot_dddd_format_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,23);
    return write_general_ddd_dot_dddd_format_attribute(number);
}

/* WRITE-DDD.DDDD-FORMAT-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_ddd_dot_dddd_format_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,24);
    return write_general_ddd_dot_dddd_format_attribute(number);
}

Object The_type_description_of_date_format = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_date_formats, Qchain_of_available_date_formats);

DEFINE_VARIABLE_WITH_SYMBOL(Date_format_count, Qdate_format_count);

Object Chain_of_available_date_formats_vector = UNBOUND;

/* DATE-FORMAT-STRUCTURE-MEMORY-USAGE */
Object date_format_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(199,25);
    temp = Date_format_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DATE-FORMAT-COUNT */
Object outstanding_date_format_count()
{
    Object def_structure_date_format_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(199,26);
    gensymed_symbol = IFIX(Date_format_count);
    def_structure_date_format_variable = Chain_of_available_date_formats;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_date_format_variable))
	goto end_loop;
    def_structure_date_format_variable = 
	    ISVREF(def_structure_date_format_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DATE-FORMAT-1 */
Object reclaim_date_format_1(date_format)
    Object date_format;
{
    Object temp, svref_arg_2;

    x_note_fn_call(199,27);
    inline_note_reclaim_cons(date_format,Nil);
    temp = ISVREF(Chain_of_available_date_formats_vector,
	    IFIX(Current_thread_index));
    SVREF(date_format,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_date_formats_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = date_format;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DATE-FORMAT */
Object reclaim_structure_for_date_format(date_format)
    Object date_format;
{
    x_note_fn_call(199,28);
    return reclaim_date_format_1(date_format);
}

static Object Qg2_defstruct_structure_name_date_format_g2_struct;  /* g2-defstruct-structure-name::date-format-g2-struct */

/* MAKE-PERMANENT-DATE-FORMAT-STRUCTURE-INTERNAL */
Object make_permanent_date_format_structure_internal()
{
    Object def_structure_date_format_variable;
    Object defstruct_g2_date_format_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(199,29);
    def_structure_date_format_variable = Nil;
    atomic_incff_symval(Qdate_format_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_date_format_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_date_format_variable = the_array;
	SVREF(defstruct_g2_date_format_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_date_format_g2_struct;
	def_structure_date_format_variable = defstruct_g2_date_format_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_date_format_variable);
}

/* MAKE-DATE-FORMAT-1 */
Object make_date_format_1(date_format_quantity_attribute,
	    date_format_integer_attribute,date_format_float_attribute,
	    date_format_name_string)
    Object date_format_quantity_attribute, date_format_integer_attribute;
    Object date_format_float_attribute, date_format_name_string;
{
    Object def_structure_date_format_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(199,30);
    def_structure_date_format_variable = 
	    ISVREF(Chain_of_available_date_formats_vector,
	    IFIX(Current_thread_index));
    if (def_structure_date_format_variable) {
	svref_arg_1 = Chain_of_available_date_formats_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_date_format_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_date_format_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_date_format_g2_struct;
    }
    else
	def_structure_date_format_variable = 
		make_permanent_date_format_structure_internal();
    inline_note_allocate_cons(def_structure_date_format_variable,Nil);
    SVREF(def_structure_date_format_variable,FIX((SI_Long)1L)) = 
	    date_format_quantity_attribute;
    SVREF(def_structure_date_format_variable,FIX((SI_Long)2L)) = 
	    date_format_integer_attribute;
    SVREF(def_structure_date_format_variable,FIX((SI_Long)3L)) = 
	    date_format_float_attribute;
    SVREF(def_structure_date_format_variable,FIX((SI_Long)4L)) = 
	    date_format_name_string;
    return VALUES_1(def_structure_date_format_variable);
}

/* DATE-FORMAT-QUANTITY-ATTRIBUTE-FUNCTION */
Object date_format_quantity_attribute_function(date_format)
    Object date_format;
{
    x_note_fn_call(199,31);
    return VALUES_1(ISVREF(date_format,(SI_Long)1L));
}

/* DATE-FORMAT-INTEGER-ATTRIBUTE-FUNCTION */
Object date_format_integer_attribute_function(date_format)
    Object date_format;
{
    x_note_fn_call(199,32);
    return VALUES_1(ISVREF(date_format,(SI_Long)2L));
}

/* DATE-FORMAT-FLOAT-ATTRIBUTE-FUNCTION */
Object date_format_float_attribute_function(date_format)
    Object date_format;
{
    x_note_fn_call(199,33);
    return VALUES_1(ISVREF(date_format,(SI_Long)3L));
}

static Object float_constant;      /* 0.0 */

/* DECODE-CURRENT-TIME */
Object decode_current_time(time_1)
    Object time_1;
{
    Object temp_1;
    char temp_2;
    double unix_time, temp, arg, arg_1;

    x_note_fn_call(199,34);
    if (FIXNUMP(time_1))
	unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		(double)IFIX(time_1);
    else if (FLOATP(time_1)) {
	temp = DOUBLE_FLOAT_TO_DOUBLE(time_1);
	unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + temp;
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L)
	unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(time_1,(SI_Long)0L);
    else if (INTEGERP(time_1)) {
	temp_1 = lfloat(time_1,float_constant);
	temp = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	unix_time = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + temp;
    }
    else
	unix_time = 0.0;
    arg = unix_time;
    arg_1 = -2.147483648E+9;
    temp_2 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_2);
    else {
	arg = unix_time;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
	temp_2 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_2)
	return VALUES_1(Nil);
    else
	return gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(unix_time));
}

static Object string_constant_1;   /* "Seconds must be between 0 and 59" */

static Object string_constant_2;   /* "Minutes must be between 0 and 59" */

static Object string_constant_3;   /* "Hours must be between 0 and 24" */

/* TRANSFORM-AND-FILTER-DAY-AND-TIME-INTERVAL */
Object transform_and_filter_day_and_time_interval(phrase)
    Object phrase;
{
    Object seconds, minutes, hours, days, total, temp_1, incff_1_arg;
    SI_Long incff_1_arg_1, total_new_value;
    char temp;

    x_note_fn_call(199,35);
    seconds = FIRST(phrase);
    minutes = SECOND(phrase);
    hours = THIRD(phrase);
    days = FOURTH(phrase);
    total = FIX((SI_Long)0L);
    temp =  !TRUEP(seconds);
    if (temp);
    else
	temp = (SI_Long)0L <= IFIX(seconds) ? IFIX(seconds) <= 
		(SI_Long)59L : TRUEP(Qnil);
    if (temp);
    else if ( !TRUEP(minutes)) {
	temp_1 = FIX((SI_Long)0L);
	temp = NUM_LE(temp_1,seconds);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_2(Bad_phrase,string_constant_1);
    if (seconds) {
	incff_1_arg = seconds;
	total = FIXNUM_ADD(total,incff_1_arg);
    }
    temp =  !TRUEP(minutes);
    if (temp);
    else
	temp = (SI_Long)0L <= IFIX(minutes) ? IFIX(minutes) <= 
		(SI_Long)59L : TRUEP(Qnil);
    if (temp);
    else if ( !TRUEP(hours)) {
	temp_1 = FIX((SI_Long)0L);
	temp = NUM_LE(temp_1,minutes);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_2(Bad_phrase,string_constant_2);
    if (minutes) {
	incff_1_arg_1 = IFIX(minutes) * (SI_Long)60L;
	total_new_value = IFIX(total) + incff_1_arg_1;
	total = FIX(total_new_value);
    }
    temp =  !TRUEP(hours);
    if (temp);
    else
	temp = (SI_Long)0L <= IFIX(hours) ? IFIX(hours) <= (SI_Long)24L : 
		TRUEP(Qnil);
    if (temp);
    else if ( !TRUEP(days)) {
	temp_1 = FIX((SI_Long)0L);
	temp = NUM_LE(temp_1,hours);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_2(Bad_phrase,string_constant_3);
    if (hours) {
	incff_1_arg_1 = IFIX(hours) * (SI_Long)3600L;
	total_new_value = IFIX(total) + incff_1_arg_1;
	total = FIX(total_new_value);
    }
    if (days) {
	incff_1_arg_1 = IFIX(days) * (SI_Long)86400L;
	total_new_value = IFIX(total) + incff_1_arg_1;
	total = FIX(total_new_value);
    }
    return VALUES_1(total);
}

static Object string_constant_4;   /* "~S:~A~S:~A~S:~A~S" */

static Object string_constant_5;   /* "0" */

static Object string_constant_6;   /* "" */

/* WRITE-DD-HH-MM-SS-AS-INTERVAL-ATTRIBUTE */
Object write_dd_hh_mm_ss_as_interval_attribute(value)
    Object value;
{
    Object number, seconds, integer_time, s, minutes, m, hours, h, days;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,36);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	seconds = number;
	if (FIXNUMP(seconds))
	    integer_time = seconds;
	else if (FLOATP(seconds))
	    integer_time = lfloor(seconds,_);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
	    integer_time = 
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
		    (SI_Long)0L)),_);
	else
	    integer_time = Qnil;
	s = chestnut_modf_function(integer_time,FIX((SI_Long)60L));
	minutes = chestnut_floorf_function(integer_time,FIX((SI_Long)60L));
	m = chestnut_modf_function(minutes,FIX((SI_Long)60L));
	hours = chestnut_floorf_function(minutes,FIX((SI_Long)60L));
	h = chestnut_floorf_function(hours,FIX((SI_Long)24L));
	days = chestnut_modf_function(hours,FIX((SI_Long)24L));
	result = tformat(8,string_constant_4,days,IFIX(h) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,h,IFIX(m) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,m,
		IFIX(s) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,s);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-HH-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_dd_hh_mm_ss_as_interval_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,37);
    return write_dd_hh_mm_ss_as_interval_attribute(number);
}

/* WRITE-DD-HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_hh_mm_ss_as_interval_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,38);
    return write_dd_hh_mm_ss_as_interval_attribute(number);
}

/* WRITE-DD-HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_hh_mm_ss_as_interval_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,39);
    return write_dd_hh_mm_ss_as_interval_attribute(number);
}

static Object string_constant_7;   /* "~S:~A~S:~A~S" */

/* WRITE-HH-MM-SS-AS-INTERVAL-ATTRIBUTE */
Object write_hh_mm_ss_as_interval_attribute(value)
    Object value;
{
    Object number, seconds, integer_time, s, minutes, m, hours;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,40);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	seconds = number;
	if (FIXNUMP(seconds))
	    integer_time = seconds;
	else if (FLOATP(seconds))
	    integer_time = lfloor(seconds,_);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
	    integer_time = 
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
		    (SI_Long)0L)),_);
	else
	    integer_time = Qnil;
	s = chestnut_modf_function(integer_time,FIX((SI_Long)60L));
	minutes = chestnut_floorf_function(integer_time,FIX((SI_Long)60L));
	m = chestnut_modf_function(minutes,FIX((SI_Long)60L));
	hours = chestnut_floorf_function(minutes,FIX((SI_Long)60L));
	result = tformat(6,string_constant_7,hours,IFIX(m) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,m,IFIX(s) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,s);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-HH-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_ss_as_interval_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,41);
    return write_hh_mm_ss_as_interval_attribute(number);
}

/* WRITE-HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_ss_as_interval_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,42);
    return write_hh_mm_ss_as_interval_attribute(number);
}

/* WRITE-HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_ss_as_interval_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,43);
    return write_hh_mm_ss_as_interval_attribute(number);
}

static Object string_constant_8;   /* "~S:~A~S" */

/* WRITE-HH-MM-AS-INTERVAL-ATTRIBUTE */
Object write_hh_mm_as_interval_attribute(value)
    Object value;
{
    Object number, seconds, integer_time, minutes, m, hours;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,44);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	seconds = number;
	if (FIXNUMP(seconds))
	    integer_time = seconds;
	else if (FLOATP(seconds))
	    integer_time = lfloor(seconds,_);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
	    integer_time = 
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
		    (SI_Long)0L)),_);
	else
	    integer_time = Qnil;
	minutes = chestnut_floorf_function(integer_time,FIX((SI_Long)60L));
	m = chestnut_modf_function(minutes,FIX((SI_Long)60L));
	hours = chestnut_floorf_function(minutes,FIX((SI_Long)60L));
	result = tformat(4,string_constant_8,hours,IFIX(m) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,m);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-HH-MM-AS-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_as_interval_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,45);
    return write_hh_mm_as_interval_attribute(number);
}

/* WRITE-HH-MM-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_as_interval_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,46);
    return write_hh_mm_as_interval_attribute(number);
}

/* WRITE-HH-MM-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_hh_mm_as_interval_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,47);
    return write_hh_mm_as_interval_attribute(number);
}

static Object Qfloat_array;        /* float-array */

/* CONVERT-TO-SECONDS */
Object convert_to_seconds(seconds_phrase)
    Object seconds_phrase;
{
    Object seconds, value, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float;
    double temp_2, aref_new_value;

    x_note_fn_call(199,48);
    seconds = CAR(seconds_phrase);
    value = INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L ? 
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,(SI_Long)0L)) : 
	    seconds;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(value);
    aref_new_value = 3600.0 * temp_2;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return note_use_of_managed_float_in_phrase(new_float);
}

static Object string_constant_9;   /* "~S.~A~S" */

/* WRITE-HH.HH-AS-INTERVAL-ATTRIBUTE */
Object write_hh_dot_hh_as_interval_attribute(value)
    Object value;
{
    Object number, seconds, integer_time, hundredths, h, hours;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,49);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	seconds = number;
	if (FIXNUMP(seconds))
	    integer_time = seconds;
	else if (FLOATP(seconds))
	    integer_time = lfloor(seconds,_);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
	    integer_time = 
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
		    (SI_Long)0L)),_);
	else
	    integer_time = Qnil;
	hundredths = chestnut_floorf_function(integer_time,FIX((SI_Long)36L));
	h = chestnut_modf_function(hundredths,FIX((SI_Long)100L));
	hours = chestnut_floorf_function(hundredths,FIX((SI_Long)100L));
	result = tformat(4,string_constant_9,hours,IFIX(h) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,h);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-HH.HH-AS-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_hh_dot_hh_as_interval_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,50);
    return write_hh_dot_hh_as_interval_attribute(number);
}

/* WRITE-HH.HH-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_hh_dot_hh_as_interval_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,51);
    return write_hh_dot_hh_as_interval_attribute(number);
}

/* WRITE-HH.HH-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_hh_dot_hh_as_interval_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,52);
    return write_hh_dot_hh_as_interval_attribute(number);
}

/* WRITE-MM-SS-AS-INTERVAL-ATTRIBUTE */
Object write_mm_ss_as_interval_attribute(value)
    Object value;
{
    Object number, seconds, integer_time, s, minutes;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,53);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	seconds = number;
	if (FIXNUMP(seconds))
	    integer_time = seconds;
	else if (FLOATP(seconds))
	    integer_time = lfloor(seconds,_);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds)) == (SI_Long)1L)
	    integer_time = 
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(seconds,
		    (SI_Long)0L)),_);
	else
	    integer_time = Qnil;
	s = chestnut_modf_function(integer_time,FIX((SI_Long)60L));
	minutes = chestnut_floorf_function(integer_time,FIX((SI_Long)60L));
	result = tformat(4,string_constant_8,minutes,IFIX(s) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,s);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT */
Object write_mm_ss_as_interval_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,54);
    return write_mm_ss_as_interval_attribute(number);
}

/* WRITE-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_ss_as_interval_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,55);
    return write_mm_ss_as_interval_attribute(number);
}

/* WRITE-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_ss_as_interval_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,56);
    return write_mm_ss_as_interval_attribute(number);
}

static Object string_constant_10;  /* "~A~S/~A~S/~S" */

static Object string_constant_11;  /* " ~A~S:~A~S:~A~S" */

/* WRITE-MM-DD-YYYY-HH-MM-SS-ATTRIBUTE */
Object write_mm_dd_yyyy_hh_mm_ss_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,57);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day,year);
	result = tformat(7,string_constant_11,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes,IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,58);
    return write_mm_dd_yyyy_hh_mm_ss_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,59);
    return write_mm_dd_yyyy_hh_mm_ss_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,60);
    return write_mm_dd_yyyy_hh_mm_ss_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-ATTRIBUTE */
Object write_dd_mm_yyyy_hh_mm_ss_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,61);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(day) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,day,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		year);
	result = tformat(7,string_constant_11,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes,IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,62);
    return write_dd_mm_yyyy_hh_mm_ss_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,63);
    return write_dd_mm_yyyy_hh_mm_ss_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,64);
    return write_dd_mm_yyyy_hh_mm_ss_attribute(number);
}

static Object string_constant_12;  /* "~S/~A~S/~A~S" */

/* WRITE-YYYY-MM-DD-HH-MM-SS-ATTRIBUTE */
Object write_yyyy_mm_dd_hh_mm_ss_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,65);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_12,year,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day);
	result = tformat(7,string_constant_11,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes,IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,66);
    return write_yyyy_mm_dd_hh_mm_ss_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,67);
    return write_yyyy_mm_dd_hh_mm_ss_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,68);
    return write_yyyy_mm_dd_hh_mm_ss_attribute(number);
}

static Object string_constant_13;  /* " ~S:~A~S:~A~S ~A" */

static Object string_constant_14;  /* "a.m." */

static Object string_constant_15;  /* "p.m." */

/* WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE */
Object write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,69);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day,year);
	result = tformat(7,string_constant_13,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,
		IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds,IFIX(hours) <= (SI_Long)11L ? 
		string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,70);
    return write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,71);
    return write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,72);
    return write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE */
Object write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,73);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(day) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,day,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		year);
	result = tformat(7,string_constant_13,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,
		IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds,IFIX(hours) <= (SI_Long)11L ? 
		string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,74);
    return write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,75);
    return write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,76);
    return write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-ATTRIBUTE */
Object write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,77);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_12,year,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day);
	result = tformat(7,string_constant_13,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,
		IFIX(seconds) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,seconds,IFIX(hours) <= (SI_Long)11L ? 
		string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,78);
    return write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,79);
    return write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,80);
    return write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute(number);
}

static Object string_constant_16;  /* " ~S:~A~S ~A" */

/* WRITE-MM-DD-YYYY-HH-MM-AM-PM-ATTRIBUTE */
Object write_mm_dd_yyyy_hh_mm_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,81);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day,year);
	result = tformat(5,string_constant_16,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,IFIX(hours) 
		<= (SI_Long)11L ? string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-DD-YYYY-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,82);
    return write_mm_dd_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,83);
    return write_mm_dd_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,84);
    return write_mm_dd_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-AM-PM-ATTRIBUTE */
Object write_dd_mm_yyyy_hh_mm_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,85);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(day) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,day,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		year);
	result = tformat(5,string_constant_16,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,IFIX(hours) 
		<= (SI_Long)11L ? string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-MM-YYYY-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,86);
    return write_dd_mm_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,87);
    return write_dd_mm_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,88);
    return write_dd_mm_yyyy_hh_mm_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-AM-PM-ATTRIBUTE */
Object write_yyyy_mm_dd_hh_mm_am_pm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,89);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_12,year,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day);
	result = tformat(5,string_constant_16,EQ(hours,FIX((SI_Long)0L)) 
		|| EQ(hours,FIX((SI_Long)12L)) ? FIX((SI_Long)12L) : 
		mod(hours,FIX((SI_Long)12L)),IFIX(minutes) < (SI_Long)10L ?
		 string_constant_5 : string_constant_6,minutes,IFIX(hours) 
		<= (SI_Long)11L ? string_constant_14 : string_constant_15);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-DD-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,90);
    return write_yyyy_mm_dd_hh_mm_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,91);
    return write_yyyy_mm_dd_hh_mm_am_pm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,92);
    return write_yyyy_mm_dd_hh_mm_am_pm_attribute(number);
}

static Object string_constant_17;  /* " ~A~S:~A~S" */

/* WRITE-MM-DD-YYYY-HH-MM-ATTRIBUTE */
Object write_mm_dd_yyyy_hh_mm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,93);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day,year);
	result = tformat(5,string_constant_17,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-DD-YYYY-HH-MM-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,94);
    return write_mm_dd_yyyy_hh_mm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,95);
    return write_mm_dd_yyyy_hh_mm_attribute(number);
}

/* WRITE-MM-DD-YYYY-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_hh_mm_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,96);
    return write_mm_dd_yyyy_hh_mm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-ATTRIBUTE */
Object write_dd_mm_yyyy_hh_mm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,97);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_10,IFIX(day) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,day,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		year);
	result = tformat(5,string_constant_17,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-MM-YYYY-HH-MM-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,98);
    return write_dd_mm_yyyy_hh_mm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,99);
    return write_dd_mm_yyyy_hh_mm_attribute(number);
}

/* WRITE-DD-MM-YYYY-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_hh_mm_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,100);
    return write_dd_mm_yyyy_hh_mm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-ATTRIBUTE */
Object write_yyyy_mm_dd_hh_mm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,101);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	tformat(6,string_constant_12,year,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day);
	result = tformat(5,string_constant_17,IFIX(hours) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,hours,IFIX(minutes) 
		< (SI_Long)10L ? string_constant_5 : string_constant_6,
		minutes);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-DD-HH-MM-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,102);
    return write_yyyy_mm_dd_hh_mm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_integer_attribute_from_slot(number,
	    gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,103);
    return write_yyyy_mm_dd_hh_mm_attribute(number);
}

/* WRITE-YYYY-MM-DD-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_hh_mm_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,104);
    return write_yyyy_mm_dd_hh_mm_attribute(number);
}

/* ADD-ZERO-TIME-TO-DATE */
Object add_zero_time_to_date(date)
    Object date;
{
    x_note_fn_call(199,105);
    return phrase_cons(date,phrase_cons(FIX((SI_Long)0L),Nil));
}

/* ADD-ZERO-TIME-TO-DATE-LIST */
Object add_zero_time_to_date_list(date_list)
    Object date_list;
{
    x_note_fn_call(199,106);
    return VALUES_1(RPLACD(date_list,phrase_cons(FIX((SI_Long)0L),Nil)));
}

/* WRITE-YYYY-MM-DD-ATTRIBUTE */
Object write_yyyy_mm_dd_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,107);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	result = tformat(6,string_constant_12,year,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		IFIX(day) < (SI_Long)10L ? string_constant_5 : 
		string_constant_6,day);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-DD-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,108);
    return write_yyyy_mm_dd_attribute(number);
}

/* WRITE-YYYY-MM-DD-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,109);
    return write_yyyy_mm_dd_attribute(number);
}

/* WRITE-YYYY-MM-DD-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_dd_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,110);
    return write_yyyy_mm_dd_attribute(number);
}

/* WRITE-MM-DD-YYYY-ATTRIBUTE */
Object write_mm_dd_yyyy_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,111);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	result = tformat(6,string_constant_10,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,IFIX(day) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,day,year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-DD-YYYY-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,112);
    return write_mm_dd_yyyy_attribute(number);
}

/* WRITE-MM-DD-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,113);
    return write_mm_dd_yyyy_attribute(number);
}

/* WRITE-MM-DD-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_dd_yyyy_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,114);
    return write_mm_dd_yyyy_attribute(number);
}

/* WRITE-DD-MM-YYYY-ATTRIBUTE */
Object write_dd_mm_yyyy_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,115);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	result = tformat(6,string_constant_10,IFIX(day) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,day,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month,
		year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-DD-MM-YYYY-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,116);
    return write_dd_mm_yyyy_attribute(number);
}

/* WRITE-DD-MM-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,117);
    return write_dd_mm_yyyy_attribute(number);
}

/* WRITE-DD-MM-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_dd_mm_yyyy_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,118);
    return write_dd_mm_yyyy_attribute(number);
}

/* SET-DAY-OF-DATE-TO-1 */
Object set_day_of_date_to_1(date_phrase)
    Object date_phrase;
{
    x_note_fn_call(199,119);
    return VALUES_1(RPLACA(date_phrase,FIX((SI_Long)1L)));
}

static Object string_constant_18;  /* "~A~S/~S" */

/* WRITE-MM-YYYY-ATTRIBUTE */
Object write_mm_yyyy_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,120);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	result = tformat(4,string_constant_18,IFIX(month) < (SI_Long)10L ? 
		string_constant_5 : string_constant_6,month,year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-MM-YYYY-ATTRIBUTE-FROM-SLOT */
Object write_mm_yyyy_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,121);
    return write_mm_yyyy_attribute(number);
}

/* WRITE-MM-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_mm_yyyy_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,122);
    return write_mm_yyyy_attribute(number);
}

/* WRITE-MM-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_mm_yyyy_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,123);
    return write_mm_yyyy_attribute(number);
}

static Object string_constant_19;  /* "~S/~A~S" */

/* WRITE-YYYY-MM-ATTRIBUTE */
Object write_yyyy_mm_attribute(value)
    Object value;
{
    Object number, seconds, minutes, hours, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,124);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number = slot_value_number_p(value) ? value : M_CAR(value);
	result = decode_current_time(number);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	result = tformat(4,string_constant_19,year,IFIX(month) < 
		(SI_Long)10L ? string_constant_5 : string_constant_6,month);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-YYYY-MM-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,125);
    return write_yyyy_mm_attribute(number);
}

/* WRITE-YYYY-MM-INTEGER-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_integer_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,126);
    return write_yyyy_mm_attribute(number);
}

/* WRITE-YYYY-MM-FLOAT-ATTRIBUTE-FROM-SLOT */
Object write_yyyy_mm_float_attribute_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,127);
    return write_yyyy_mm_attribute(number);
}

/* WRITE-TRUTH-VALUE-ATTRIBUTE-FROM-SLOT */
Object write_truth_value_attribute_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,128);
    return print_constant(2,M_CAR(value),M_CAR(M_CDR(value)));
}

/* WRITE-SYMBOL-ATTRIBUTE-FROM-SLOT */
Object write_symbol_attribute_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,129);
    if (SYMBOLP(value))
	return print_constant(2,value,Qsymbol);
    else
	return VALUES_1(Qt);
}

/* WRITE-TEXT-ATTRIBUTE-FROM-SLOT */
Object write_text_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    Object car_1, cdr_1, temp, write_strings_parsably_qm;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,130);
    if (CONSP(attribute)) {
	car_1 = M_CAR(attribute);
	cdr_1 = M_CDR(attribute);
	if (CONSP(cdr_1)) {
	    temp = M_CAR(cdr_1);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return print_constant(2,M_CAR(attribute),M_CAR(M_CDR(attribute)));
    else {
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  Leave_text_representation_as_a_single_line_qm = Nil;
	  result = twrite_general_string(attribute);
	POP_SPECIAL();
	return result;
    }
}

/* WRITE-FREE-TEXT-ATTRIBUTE-FROM-SLOT */
Object write_free_text_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    Object car_1, cdr_1, temp, write_strings_parsably_qm;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,131);
    if (CONSP(attribute)) {
	car_1 = M_CAR(attribute);
	cdr_1 = M_CDR(attribute);
	if (CONSP(cdr_1)) {
	    temp = M_CAR(cdr_1);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return print_constant(3,M_CAR(attribute),M_CAR(M_CDR(attribute)),T);
    else {
	write_strings_parsably_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  Leave_text_representation_as_a_single_line_qm = Nil;
	  result = twrite_general_string(attribute);
	POP_SPECIAL();
	return result;
    }
}

static Object Qtext;               /* text */

static Object string_constant_20;  /* "****" */

static Object Qnever;              /* never */

static Object string_constant_21;  /* " *" */

static Object string_constant_22;  /* "the ~(~A~) " */

/* WRITE-ENTITY-IN-SLOT */
Object write_entity_in_slot(entity)
    Object entity;
{
    Object sub_class_bit_vector, managed_number_or_value, value, expiration;
    Object type, name_qm, class_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,132);
    sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    managed_number_or_value = ISVREF(entity,(SI_Long)23L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else
		value = managed_number_or_value;
	    expiration = ISVREF(entity,(SI_Long)26L);
	    type = ISVREF(entity,(SI_Long)20L);
	    if (EQ(type,Qtext))
		Leave_text_representation_as_a_single_line_qm = Nil;
	    if ( !TRUEP(value))
		result = twrite(string_constant_20);
	    else if (EQ(expiration,Qnever))
		result = print_constant(2,value,type);
	    else if (FIXNUM_EQ(expiration,Some_time_ago))
		result = twrite(string_constant_20);
	    else if (FIXNUM_LT(expiration,Gensym_time)) {
		print_constant(2,value,type);
		result = twrite(string_constant_21);
	    }
	    else {
		print_constant(2,value,type);
		result = schedule_update_for_variable_expiration(entity);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	if (temp) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		managed_number_or_value = ISVREF(entity,(SI_Long)23L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    value = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else
		    value = managed_number_or_value;
		type = ISVREF(entity,(SI_Long)20L);
		if (EQ(type,Qtext))
		    Leave_text_representation_as_a_single_line_qm = Nil;
		if ( !TRUEP(value))
		    result = twrite(string_constant_20);
		else
		    result = print_constant(2,value,type);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else {
	    name_qm = get_primary_name_for_frame_if_any(entity);
	    class_1 = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L);
	    if (name_qm) {
		tformat(2,string_constant_22,class_1);
		return twrite_symbol(2,name_qm,T);
	    }
	    else
		return write_symbol_with_a_or_an(1,class_1);
	}
    }
}

static Object string_constant_23;  /* "A UUID (as represented internally) must be a text ~D characters long, but ~
				    *        this is ~D characters long"
				    */

/* MAKE-ILLEGAL-LENGTH-UUID-STRING-MESSAGE */
Object make_illegal_length_uuid_string_message(wide_string,length_1)
    Object wide_string, length_1;
{
    x_note_fn_call(199,133);
    return tformat_text_string(3,string_constant_23,Uuid_string_length,
	    length_1);
}

static Object list_constant;       /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* UUID-EVALUATION-SETTER */
Object uuid_evaluation_setter(evaluation_text,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_text, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,134);
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
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_text,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_text,Qtext,
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
		      goto end_uuid_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !FIXNUM_EQ(lengthw(evaluation_text),Uuid_string_length)) {
	temp = Bad_phrase;
	temp_1 = make_illegal_length_uuid_string_message(evaluation_text,
		lengthw(evaluation_text));
	result = VALUES_2(temp,temp_1);
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
		  twrite_uuid_printed_representation(evaluation_text);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = note_use_of_text_string_in_phrase(temp_1);
    }
  end_uuid_evaluation_setter:
    return result;
}

/* UUID-EVALUATION-GETTER */
Object uuid_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(199,135);
    if (slot_value)
	temp = evaluation_item_reference_uuid(slot_value);
    else if (frame)
	temp = error((SI_Long)1L,"Internal error getting a UUID");
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

static Object string_constant_24;  /* "no simulation formula yet" */

static Object string_constant_25;  /* ", but has specific subtable" */

static Object Qnon_default_initial_simulated_value_qm;  /* non-default-initial-simulated-value? */

static Object list_constant_1;     /* # */

static Object string_constant_26;  /* ", with initial value " */

static Object Quse_initial_value_expression_in_generic_simulation_formula;  /* use-initial-value-expression-in-generic-simulation-formula */

static Object string_constant_27;  /* "given by an expression" */

static Object string_constant_28;  /* ", and has specific subtable" */

/* WRITE-SIMULATION-FRAME?-FROM-SLOT */
Object write_simulation_frame_qm_from_slot(simulation_frame_qm,variable)
    Object simulation_frame_qm, variable;
{
    Object simulation_info_qm, simulation_category_qm, slot_value_number;
    Object initial_simulated_value_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,136);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    simulation_category_qm = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)2L) : Nil;
    if ( !TRUEP(simulation_category_qm)) {
	twrite(string_constant_24);
	if (simulation_frame_qm)
	    return twrite(string_constant_25);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    slot_value_number = 
		    get_lookup_slot_value_given_default(variable,
		    Qnon_default_initial_simulated_value_qm,Nil);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		initial_simulated_value_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		initial_simulated_value_qm = aref1(slot_value_number,
			FIX((SI_Long)0L));
	    else
		initial_simulated_value_qm = slot_value_number;
	    if (initial_simulated_value_qm);
	    else {
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		initial_simulated_value_qm = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)3L) : Nil;
	    }
	    twrite(simulation_category_qm);
	    if (initial_simulated_value_qm && 
		    memq_function(simulation_category_qm,list_constant_1)) {
		twrite(string_constant_26);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_simulated_value_qm) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_simulated_value_qm)) 
			== (SI_Long)1L)
		    twrite(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(initial_simulated_value_qm,
			    (SI_Long)0L)));
		else if (CONSP(initial_simulated_value_qm) || 
			EQ(initial_simulated_value_qm,
			Quse_initial_value_expression_in_generic_simulation_formula))
		    twrite(string_constant_27);
		else
		    twrite(initial_simulated_value_qm);
	    }
	    if (simulation_frame_qm)
		result = twrite(string_constant_28);
	    else
		result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* COMPILE-NON-DEFAULT-NUMBER?-FOR-SLOT */
Object compile_non_default_number_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,137);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (phrase_number_p(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

static Object string_constant_29;  /* "default" */

/* WRITE-NON-DEFAULT-NUMBER?-FROM-SLOT */
Object write_non_default_number_qm_from_slot(number_qm,gensymed_symbol)
    Object number_qm, gensymed_symbol;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,138);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_qm)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = write_floating_point_number_simple_c_format(1,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_qm,
		    (SI_Long)0L)));
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (number_qm)
	return twrite(number_qm);
    else
	return twrite(string_constant_29);
}

/* COMPILE-ATTRIBUTE-FOR-SLOT */
Object compile_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object defining_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,139);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_item_or_datum_or_no_item_attribute_for_slot(4,
	    parse_result,frame,slot_name,defining_class);
}

static Object Qattribute;          /* attribute */

static Object Qslot_value_compiler;  /* slot-value-compiler */

/* COMPILE-READ-ONLY-ATTRIBUTE-FOR-SLOT */
Object compile_read_only_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object defining_class, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,140);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute),
	    Qslot_value_compiler);
    return FUNCALL_4(temp,parse_result,frame,slot_name,defining_class);
}

static Object Qnone;               /* none */

static Object Qab_structure;       /* structure */

/* COPY-EVALUATION-VALUE-TO-PHRASE */
Object copy_evaluation_value_to_phrase(evaluation_value)
    Object evaluation_value;
{
    Object gensymed_symbol, held_vector, name, attribute_value, value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp, elt_1;
    Object validated_elt, x2;
    SI_Long next_index, length_1, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(199,141);
    if ( !TRUEP(evaluation_value))
	return VALUES_1(Qnone);
    else if (SYMBOLP(evaluation_value))
	return VALUES_1(evaluation_value);
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value))
	return phrase_cons(M_CAR(evaluation_value),Qtruth_value);
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qab_structure)) {
	gensymed_symbol = evaluation_value;
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
	temp = name;
	ab_loopvar__2 = phrase_list_2(temp,
		copy_evaluation_value_to_phrase(value));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	return phrase_cons(temp,Phrase_structure_marker);
    }
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qsequence)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	value = Nil;
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
	value = validated_elt;
	ab_loopvar__2 = phrase_cons(copy_evaluation_value_to_phrase(value),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	return phrase_cons(temp,Phrase_sequence_marker);
    }
    else {
	if (SIMPLE_VECTOR_P(evaluation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(evaluation_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(evaluation_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return phrase_cons(evaluation_value,Phrase_item_marker);
	else
	    return copy_for_phrase(evaluation_value);
    }
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

/* ATTRIBUTE-EVALUATION-SETTER */
Object attribute_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,142);
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
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_attribute_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value))
	result = VALUES_1(Qnone);
    else
	result = copy_evaluation_value_to_phrase(evaluation_value);
  end_attribute_evaluation_setter:
    return result;
}

/* ATTRIBUTE-EVALUATION-GETTER */
Object attribute_evaluation_getter(slot_value,frame_qm,slot_description)
    Object slot_value, frame_qm, slot_description;
{
    x_note_fn_call(199,143);
    GENSYM_RETURN_ONE(get_evaluation_value_for_attribute(slot_value,frame_qm));
    return VALUES_1(Nil);
}

/* WRITE-READ-ONLY-ATTRIBUTE-FROM-SLOT */
Object write_read_only_attribute_from_slot(attribute,gensymed_symbol)
    Object attribute, gensymed_symbol;
{
    x_note_fn_call(199,144);
    return write_attribute(attribute);
}

/* READ-ONLY-ATTRIBUTE-EVALUATION-GETTER */
Object read_only_attribute_evaluation_getter(slot_value,frame_qm,
	    slot_description)
    Object slot_value, frame_qm, slot_description;
{
    x_note_fn_call(199,145);
    GENSYM_RETURN_ONE(get_evaluation_value_for_attribute(slot_value,frame_qm));
    return VALUES_1(Nil);
}

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* GET-EVALUATION-VALUE-FOR-ATTRIBUTE */
Object get_evaluation_value_for_attribute(slot_value,frame_qm)
    Object slot_value, frame_qm;
{
    Object temp, car_1, cdr_1, managed_value;
    char temp_1;

    x_note_fn_call(199,146);
    if ( !TRUEP(slot_value))
	temp = 
		get_allow_no_value_of_variable_or_parameter_from_frame(frame_qm) 
		? Nil : Qnone;
    else if (text_string_p(slot_value))
	temp = copy_as_wide_string(slot_value);
    else {
	if (CONSP(slot_value)) {
	    car_1 = M_CAR(slot_value);
	    cdr_1 = M_CDR(slot_value);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    managed_value = M_CAR(slot_value);
	    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(slot_value))),
		    Qtruth_value)) {
		if (FIXNUM_EQ(managed_value,Truth))
		    temp = Evaluation_true_value;
		else if (FIXNUM_EQ(managed_value,Falsity))
		    temp = Evaluation_false_value;
		else
		    temp = eval_cons_1(managed_value,Qtruth_value);
	    }
	    else
		temp = FIXNUMP(managed_value) || SYMBOLP(managed_value) ? 
			managed_value : copy_evaluation_value_1(managed_value);
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L)
	    temp = copy_managed_float(slot_value);
	else if (EQ(Qtruth_value,
		get_data_type_of_variable_or_parameter_from_frame(1,
		    frame_qm))) {
	    if (EQ(slot_value,Qtrue))
		temp = T ? Evaluation_true_value : Evaluation_false_value;
	    else if (EQ(slot_value,Qfalse))
		temp = Nil ? Evaluation_true_value : Evaluation_false_value;
	    else
		temp = FIXNUMP(slot_value) || slot_value && 
			SYMBOLP(slot_value) || SIMPLE_VECTOR_P(slot_value) 
			? slot_value : copy_if_evaluation_value_1(slot_value);
	}
	else
	    temp = FIXNUMP(slot_value) || slot_value && 
		    SYMBOLP(slot_value) || SIMPLE_VECTOR_P(slot_value) ? 
		    slot_value : copy_if_evaluation_value_1(slot_value);
    }
    return VALUES_1(temp);
}

/* COMPILE-ITEM-OR-DATUM-OR-NO-ITEM-ATTRIBUTE-FOR-SLOT */
Object compile_item_or_datum_or_no_item_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object defining_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,147);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return compile_item_or_datum_attribute_for_slot(4,parse_result,
		frame,slot_name,defining_class);
}

/* COMPILE-ITEM-OR-DATUM-ATTRIBUTE-FOR-SLOT */
Object compile_item_or_datum_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object defining_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,148);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_datum_attribute_for_slot(4,parse_result,frame,slot_name,
	    defining_class);
}

/* COMPILE-DATUM-ATTRIBUTE-FOR-SLOT */
Object compile_datum_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cdr_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,149);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Bad_phrase);
    else if (truth_value_phrase_p(parse_result)) {
	cdr_new_value = phrase_cons(CDR(parse_result),Nil);
	M_CDR(parse_result) = cdr_new_value;
	return VALUES_1(parse_result);
    }
    else if (phrase_number_p(parse_result))
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else if (SYMBOLP(parse_result) || text_string_p(parse_result) || 
	    CONSP(parse_result) && EQ(M_CDR(parse_result),
	    Phrase_sequence_marker) || CONSP(parse_result) && 
	    EQ(M_CDR(parse_result),Phrase_structure_marker) || 
	    CONSP(parse_result) && EQ(M_CDR(parse_result),
	    Phrase_item_denotation_marker))
	return VALUES_1(parse_result);
    else if (phrase_number_p(CAR(parse_result))) {
	cdr_new_value = phrase_cons(CDR(parse_result),Nil);
	M_CDR(parse_result) = cdr_new_value;
	return VALUES_1(parse_result);
    }
    else
	return VALUES_1(Qnil);
}

/* COMPILE-NUMBER-ATTRIBUTE-FOR-SLOT */
Object compile_number_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,150);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (phrase_number_p(parse_result))
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-FLOAT-ATTRIBUTE-FOR-SLOT */
Object compile_float_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,151);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == (SI_Long)1L)
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-INTEGER-ATTRIBUTE-FOR-SLOT */
Object compile_integer_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,152);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (FIXNUMP(parse_result))
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-SYMBOL-ATTRIBUTE-FOR-SLOT */
Object compile_symbol_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,153);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (SYMBOLP(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-TEXT-ATTRIBUTE-FOR-SLOT */
Object compile_text_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,154);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (text_string_p(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-FREE-TEXT-ATTRIBUTE-FOR-SLOT */
Object compile_free_text_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,155);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (text_string_p(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-TRUTH-VALUE-ATTRIBUTE-FOR-SLOT */
Object compile_truth_value_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object cdr_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,156);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (truth_value_phrase_p(parse_result)) {
	cdr_new_value = phrase_cons(CDR(parse_result),Nil);
	M_CDR(parse_result) = cdr_new_value;
	return VALUES_1(parse_result);
    }
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-STRUCTURE-ATTRIBUTE-FOR-SLOT */
Object compile_structure_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,157);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse_result) && EQ(M_CDR(parse_result),Phrase_structure_marker))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-SEQUENCE-ATTRIBUTE-FOR-SLOT */
Object compile_sequence_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,158);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse_result) && EQ(M_CDR(parse_result),Phrase_sequence_marker))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-EVALUATION-VALUE-CONSTANT-ALLOWING-ITEMS-FOR-SLOT */
Object compile_evaluation_value_constant_allowing_items_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object defining_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,159);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return compile_item_or_datum_attribute_for_slot(4,parse_result,
		frame,slot_name,defining_class);
}

/* COMPILE-DDD.DDDD-FORMAT-ATTRIBUTE-FOR-SLOT */
Object compile_ddd_dot_dddd_format_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,160);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (phrase_number_p(parse_result))
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-DDD.DDDD-FORMAT-FLOAT-ATTRIBUTE-FOR-SLOT */
Object compile_ddd_dot_dddd_format_float_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,161);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == (SI_Long)1L)
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

/* COMPILE-DDD.DDDD-FORMAT-INTEGER-ATTRIBUTE-FOR-SLOT */
Object compile_ddd_dot_dddd_format_integer_attribute_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,162);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (FIXNUMP(parse_result))
	return make_slot_constant_using_phrase_conses(parse_result,Qnumber);
    else
	return VALUES_1(Bad_phrase);
}

static Object list_constant_4;     /* # */

/* SYMBOL-EVALUATION-SETTER */
Object symbol_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,163);
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
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_symbol_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_symbol_evaluation_setter:
    return result;
}

/* SYMBOL-EVALUATION-GETTER */
Object symbol_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,164);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* READ-ONLY-SYMBOL-DATA-TYPE-EVALUATION-GETTER */
Object read_only_symbol_data_type_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,165);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* READ-ONLY-TEXT-DATA-TYPE-EVALUATION-GETTER */
Object read_only_text_data_type_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,166);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* READ-ONLY-TRUTH-VALUE-DATA-TYPE-EVALUATION-GETTER */
Object read_only_truth_value_data_type_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,167);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qneutral_unit_of_measure;  /* neutral-unit-of-measure */

static Object Qplural_unit_of_measure;  /* plural-unit-of-measure */

static Object string_constant_30;  /* "You must use an appropriate G2-defined type or a KB-defined unit of measure." */

/* FLOAT-DATA-TYPE-EVALUATION-SETTER */
Object float_data_type_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,168);
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
		      goto end_float_data_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qfloat))
	result = VALUES_1(Qfloat);
    else if (EQ(evaluation_value,Qtime_stamp))
	result = VALUES_1(Qtime_stamp);
    else if ( !(memq_function(Qneutral_unit_of_measure,
	    lookup_kb_specific_property_value(evaluation_value,
	    Category_symbols_for_symbol_token_kbprop)) || 
	    memq_function(Qplural_unit_of_measure,
	    lookup_kb_specific_property_value(evaluation_value,
	    Category_symbols_for_symbol_token_kbprop)))) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_30);
	result = VALUES_2(temp,temp_1);
    }
    else
	result = VALUES_1(evaluation_value);
  end_float_data_type_evaluation_setter:
    return result;
}

/* FLOAT-DATA-TYPE-EVALUATION-GETTER */
Object float_data_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,169);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qinterval;           /* interval */

/* INTEGER-DATA-TYPE-EVALUATION-SETTER */
Object integer_data_type_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,170);
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
		      goto end_integer_data_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qinterval))
	result = VALUES_1(Qseconds);
    else if (EQ(evaluation_value,Qinteger))
	result = VALUES_1(Qinteger);
    else if ( !(memq_function(Qneutral_unit_of_measure,
	    lookup_kb_specific_property_value(evaluation_value,
	    Category_symbols_for_symbol_token_kbprop)) || 
	    memq_function(Qplural_unit_of_measure,
	    lookup_kb_specific_property_value(evaluation_value,
	    Category_symbols_for_symbol_token_kbprop)))) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_30);
	result = VALUES_2(temp,temp_1);
    }
    else
	result = VALUES_1(evaluation_value);
  end_integer_data_type_evaluation_setter:
    return result;
}

/* INTEGER-DATA-TYPE-EVALUATION-GETTER */
Object integer_data_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,171);
    GENSYM_RETURN_ONE(EQ(slot_value,Qseconds) ? Qinterval : slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object Qlong;               /* long */

static Object string_constant_31;  /* "int 64 data type is experimental and does not support units of measure" */

/* LONG-DATA-TYPE-EVALUATION-SETTER */
Object long_data_type_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,172);
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
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_long_data_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qlong))
	result = VALUES_1(Qlong);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_31);
	result = VALUES_2(temp,temp_1);
    }
  end_long_data_type_evaluation_setter:
    return result;
}

/* LONG-DATA-TYPE-EVALUATION-GETTER */
Object long_data_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,173);
    GENSYM_RETURN_ONE(EQ(slot_value,Qseconds) ? Qinterval : slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object Qquantity;           /* quantity */

static Object Qinteger_data_type;  /* integer-data-type */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* QUANTITATIVE-DATA-TYPE-EVALUATION-SETTER */
Object quantitative_data_type_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,174);
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
			  list_constant_11))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_12,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_quantitative_data_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qquantity))
	result = VALUES_1(Qnumber);
    else if (EQ(evaluation_value,Qfloat))
	result = VALUES_1(Qfloat);
    else if (EQ(evaluation_value,Qtime_stamp))
	result = VALUES_1(Qtime_stamp);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger_data_type),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_quantitative_data_type_evaluation_setter:
    return result;
}

/* QUANTITATIVE-DATA-TYPE-EVALUATION-GETTER */
Object quantitative_data_type_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(199,175);
    if (EQ(slot_value,Qnumber))
	temp = Qquantity;
    else if (EQ(slot_value,Qquantity) || EQ(slot_value,Qfloat) || 
	    EQ(slot_value,Qtime_stamp))
	temp = slot_value;
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger_data_type),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_13;    /* # */

static Object list_constant_14;    /* # */

static Object Qvalue;              /* value */

static Object Qdatum;              /* datum */

static Object Qquantitative_data_type;  /* quantitative-data-type */

/* DATA-TYPE-EVALUATION-SETTER */
Object data_type_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,176);
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
			  list_constant_13))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_14,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_data_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qvalue))
	result = VALUES_1(Qdatum);
    else if (EQ(evaluation_value,Qsymbol))
	result = VALUES_1(Qsymbol);
    else if (EQ(evaluation_value,Qtext))
	result = VALUES_1(Qtext);
    else if (EQ(evaluation_value,Qtruth_value))
	result = VALUES_1(Qtruth_value);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantitative_data_type),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_data_type_evaluation_setter:
    return result;
}

/* DATA-TYPE-EVALUATION-GETTER */
Object data_type_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(199,177);
    if (EQ(slot_value,Qdatum))
	temp = Qvalue;
    else if (EQ(slot_value,Qvalue) || EQ(slot_value,Qsymbol) || 
	    EQ(slot_value,Qtext) || EQ(slot_value,Qtruth_value))
	temp = slot_value;
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantitative_data_type),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* FIX-DATA-TYPE */
Object fix_data_type(parse_result)
    Object parse_result;
{
    Object temp;

    x_note_fn_call(199,178);
    if (EQ(parse_result,Qquantity))
	temp = Qnumber;
    else if (EQ(parse_result,Qinterval))
	temp = Qseconds;
    else if (EQ(parse_result,Qvalue))
	temp = Qdatum;
    else
	temp = parse_result;
    return VALUES_1(temp);
}

static Object Qinitial_value_of_variable_or_parameter;  /* initial-value-of-variable-or-parameter */

/* COMPILE-DATA-TYPE-FOR-SLOT */
Object compile_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Object fixed_value, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,179);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    fixed_value = fix_data_type(parse_result);
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
    if (temp ?  !EQ(fixed_value,ISVREF(frame,(SI_Long)20L)) : TRUEP(Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_parameter_class_description,(SI_Long)18L));
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
	    if ( !FIXNUMP(ISVREF(frame,(SI_Long)22L)))
		set_slot_value_and_update_representations(3,frame,
			Qinitial_value_of_variable_or_parameter,
			FIX((SI_Long)0L));
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantitative_parameter_class_description,
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
	    if (temp)
		set_slot_value_and_update_representations(3,frame,
			Qinitial_value_of_variable_or_parameter,
			float_constant);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		if (temp)
		    set_slot_value_and_update_representations(3,frame,
			    Qinitial_value_of_variable_or_parameter,Nil);
	    }
	}
    }
    return VALUES_1(fixed_value);
}

/* WRITE-DATA-TYPE-FROM-SLOT */
Object write_data_type_from_slot(data_type,gensymed_symbol)
    Object data_type, gensymed_symbol;
{
    x_note_fn_call(199,180);
    return twrite_data_type(data_type);
}

/* COMPILE-QUANTITATIVE-DATA-TYPE-FOR-SLOT */
Object compile_quantitative_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,181);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_data_type_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-FLOAT-DATA-TYPE-FOR-SLOT */
Object compile_float_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,182);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_data_type_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-INTEGER-DATA-TYPE-FOR-SLOT */
Object compile_integer_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,183);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_data_type_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-LONG-DATA-TYPE-FOR-SLOT */
Object compile_long_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,184);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_data_type_for_slot(3,parse_result,frame,Nil);
}

/* WRITE-READ-ONLY-SYMBOL-DATA-TYPE-FROM-SLOT */
Object write_read_only_symbol_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,185);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-READ-ONLY-TEXT-DATA-TYPE-FROM-SLOT */
Object write_read_only_text_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,186);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-READ-ONLY-TRUTH-VALUE-DATA-TYPE-FROM-SLOT */
Object write_read_only_truth_value_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,187);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-QUANTITATIVE-DATA-TYPE-FROM-SLOT */
Object write_quantitative_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,188);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-INTEGER-DATA-TYPE-FROM-SLOT */
Object write_integer_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,189);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-LONG-DATA-TYPE-FROM-SLOT */
Object write_long_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,190);
    return write_data_type_from_slot(data_type,frame);
}

/* WRITE-FLOAT-DATA-TYPE-FROM-SLOT */
Object write_float_data_type_from_slot(data_type,frame)
    Object data_type, frame;
{
    x_note_fn_call(199,191);
    return write_data_type_from_slot(data_type,frame);
}

static Object string_constant_32;  /* "no value" */

static Object string_constant_33;  /* ", valid indefinitely" */

static Object string_constant_34;  /* ", expired " */

static Object string_constant_35;  /* ", expires " */

/* WRITE-SUPPLIED-VALUE-FROM-SLOT */
Object write_supplied_value_from_slot(value,variable_or_parameter)
    Object value, variable_or_parameter;
{
    Object sub_class_bit_vector, type, expiration;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,192);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	if (temp) {
	    type = ISVREF(variable_or_parameter,(SI_Long)20L);
	    expiration = ISVREF(variable_or_parameter,(SI_Long)26L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		value = aref1(value,FIX((SI_Long)0L));
	    else;
	    if ( !EQ(type,Qtext))
		Leave_text_representation_as_a_single_line_qm = T;
	    if ( !TRUEP(value) ||  !TRUEP(type) || NUMBERP(expiration) && 
		    FIXNUM_EQ(expiration,Some_time_ago))
		result = twrite(string_constant_32);
	    else if (EQ(expiration,Qnever)) {
		print_constant(2,value,type);
		result = twrite(string_constant_33);
	    }
	    else if (FIXNUM_LT(expiration,Gensym_time)) {
		print_constant(2,value,type);
		twrite(string_constant_34);
		result = write_date_and_time(expiration);
	    }
	    else {
		print_constant(2,value,type);
		twrite(string_constant_35);
		write_date_and_time(expiration);
		result = schedule_update_for_variable_expiration(variable_or_parameter);
	    }
	}
	else {
	    type = ISVREF(variable_or_parameter,(SI_Long)20L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		value = aref1(value,FIX((SI_Long)0L));
	    else;
	    if ( !EQ(type,Qtext))
		Leave_text_representation_as_a_single_line_qm = T;
	    if ( !TRUEP(value))
		result = twrite(string_constant_32);
	    else
		result = print_constant(2,value,type);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

/* VALIDITY-INTERVAL-EVALUATION-SETTER */
Object validity_interval_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,193);
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
			  list_constant_15))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_16,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_validity_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_validity_interval_evaluation_setter:
    return result;
}

/* VALIDITY-INTERVAL-EVALUATION-GETTER */
Object validity_interval_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,194);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-VALIDITY-INTERVAL-FOR-SLOT */
Object compile_validity_interval_for_slot varargs_1(int, n)
{
    Object parse_result, variable, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,195);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse_result))
	return VALUES_1(CAR(parse_result));
    else
	return VALUES_1(parse_result);
}

/* WRITE-VALIDITY-INTERVAL-FROM-SLOT */
Object write_validity_interval_from_slot(validity_interval,gensymed_symbol)
    Object validity_interval, gensymed_symbol;
{
    x_note_fn_call(199,196);
    if (SYMBOLP(validity_interval))
	return twrite_symbol(1,validity_interval);
    else if (NUMBERP(validity_interval))
	return print_constant(2,validity_interval,Qseconds);
    else
	return VALUES_1(Qnil);
}

/* COMPILE-SENSOR-VALIDITY-INTERVAL-FOR-SLOT */
Object compile_sensor_validity_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,197);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse_result))
	return VALUES_1(CAR(parse_result));
    else
	return VALUES_1(parse_result);
}

/* WRITE-SENSOR-VALIDITY-INTERVAL-FROM-SLOT */
Object write_sensor_validity_interval_from_slot(validity_interval,
	    gensymed_symbol)
    Object validity_interval, gensymed_symbol;
{
    x_note_fn_call(199,198);
    if (SYMBOLP(validity_interval))
	return twrite_symbol(1,validity_interval);
    else if (NUMBERP(validity_interval))
	return print_constant(2,validity_interval,Qseconds);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

/* SENSOR-VALIDITY-INTERVAL-EVALUATION-SETTER */
Object sensor_validity_interval_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,199);
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
			  list_constant_17))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_18,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_sensor_validity_interval_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_sensor_validity_interval_evaluation_setter:
    return result;
}

/* SENSOR-VALIDITY-INTERVAL-EVALUATION-GETTER */
Object sensor_validity_interval_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,200);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-INTERVAL?-FOR-SLOT */
Object compile_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,201);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(CAR(parse_result));
}

/* WRITE-INTERVAL?-FROM-SLOT */
Object write_interval_qm_from_slot(interval_qm,gensymed_symbol)
    Object interval_qm, gensymed_symbol;
{
    x_note_fn_call(199,202);
    if ( !TRUEP(interval_qm))
	return twrite_symbol(1,Qnone);
    else if (NUMBERP(interval_qm))
	return print_constant(2,interval_qm,Qseconds);
    else
	return VALUES_1(Qnil);
}

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

/* POSITIVE-QUANTITY-INTERVAL?-EVALUATION-SETTER */
Object positive_quantity_interval_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,203);
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
			  list_constant_19))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_20,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_positive_quantity_interval_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	value = evaluation_value_value(evaluation_value);
	if (FIXNUMP(value))
	    temp_1 = value;
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp_1 = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    temp_1 = note_use_of_managed_float_in_phrase(new_float);
	}
	result = phrase_cons(temp_1,Qseconds);
    }
    else
	result = VALUES_1(Qnone);
  end_positive_quantity_interval_qm_evaluation_setter:
    return result;
}

/* POSITIVE-QUANTITY-INTERVAL?-EVALUATION-GETTER */
Object positive_quantity_interval_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,204);
    GENSYM_RETURN_ONE(slot_value ? 
	    (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L ? 
	    copy_managed_float(slot_value) : slot_value) : Nil);
    return VALUES_1(Nil);
}

/* COMPILE-INTERVAL-FOR-SLOT */
Object compile_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,205);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(CAR(parse_result));
}

/* WRITE-INTERVAL-FROM-SLOT */
Object write_interval_from_slot(interval,gensymed_symbol)
    Object interval, gensymed_symbol;
{
    x_note_fn_call(199,206);
    return print_constant(2,interval,Qseconds);
}

static Object array_constant_2;    /* # */

/* COMPILE-POSITIVE-INTERVAL?-FOR-SLOT */
Object compile_positive_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,207);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (IFIX(CAR(parse_result)) <= (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)39L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

/* WRITE-POSITIVE-INTERVAL?-FROM-SLOT */
Object write_positive_interval_qm_from_slot(positive_interval_qm,
	    gensymed_symbol)
    Object positive_interval_qm, gensymed_symbol;
{
    x_note_fn_call(199,208);
    if ( !TRUEP(positive_interval_qm))
	return twrite_symbol(1,Qnone);
    else if (FIXNUMP(positive_interval_qm))
	return print_constant(2,positive_interval_qm,Qseconds);
    else
	return VALUES_1(Qnil);
}

static Object array_constant_3;    /* # */

/* COMPILE-EXECUTION-INTERVAL?-FOR-SLOT */
Object compile_execution_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,209);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (IFIX(CAR(parse_result)) <= (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)39L));
	return VALUES_2(temp,temp_1);
    }
    else if (IFIX(CAR(parse_result)) > (SI_Long)86400L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_3,
		FIX((SI_Long)43L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

static Object Qpositive_interval_qm;  /* positive-interval? */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_36;  /* "[deleted attribute]" */

/* WRITE-EXECUTION-INTERVAL?-FROM-SLOT */
Object write_execution_interval_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(199,210);
    slot_value_writer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_interval_qm),
	    Qslot_value_writer);
    if (slot_value_writer_qm) {
	write_symbols_in_lower_case_qm = T;
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		  0);
	    result = VALUES_1(inline_funcall_2(slot_value_writer_qm,value,
		    Nil));
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return twrite(string_constant_36);
}

/* COMPILE-QUANTITY-INTERVAL-FOR-SLOT */
Object compile_quantity_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,211);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(CAR(parse_result));
}

/* WRITE-QUANTITY-INTERVAL-FROM-SLOT */
Object write_quantity_interval_from_slot(quantity_interval,gensymed_symbol)
    Object quantity_interval, gensymed_symbol;
{
    x_note_fn_call(199,212);
    return print_constant(2,quantity_interval,Qseconds);
}

/* COMPILE-POSITIVE-QUANTITY-INTERVAL?-FOR-SLOT */
Object compile_positive_quantity_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object number, temp, temp_1;
    char temp_2;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,213);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone) || EQ(parse_result,Nil))
	return VALUES_1(Nil);
    else {
	number = M_CAR(parse_result);
	if (FIXNUMP(number)) {
	    if (FIXNUM_PLUSP(number))
		return VALUES_1(number);
	    else {
		temp = Bad_phrase;
		temp_1 = 
			copy_constant_wide_string_given_length(array_constant_2,
			FIX((SI_Long)39L));
		return VALUES_2(temp,temp_1);
	    }
	}
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		arg = DFLOAT_ISAREF_1(number,(SI_Long)0L);
		arg_1 = 0.0;
		temp_2 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    if (temp_2)
		return VALUES_1(number);
	    else {
		temp = Bad_phrase;
		temp_1 = 
			copy_constant_wide_string_given_length(array_constant_2,
			FIX((SI_Long)39L));
		return VALUES_2(temp,temp_1);
	    }
	}
    }
}

/* COMPILE-POSITIVE-QUANTITY-INTERVAL-FOR-SLOT */
Object compile_positive_quantity_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object number, temp, temp_1;
    char temp_2;
    double arg, arg_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,214);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    number = M_CAR(parse_result);
    if (FIXNUMP(number)) {
	if (FIXNUM_PLUSP(number))
	    return VALUES_1(number);
	else {
	    temp = Bad_phrase;
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_2,
		    FIX((SI_Long)39L));
	    return VALUES_2(temp,temp_1);
	}
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    arg = DFLOAT_ISAREF_1(number,(SI_Long)0L);
	    arg_1 = 0.0;
	    temp_2 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (temp_2)
	    return VALUES_1(number);
	else {
	    temp = Bad_phrase;
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_2,
		    FIX((SI_Long)39L));
	    return VALUES_2(temp,temp_1);
	}
    }
}

/* WRITE-POSITIVE-QUANTITY-INTERVAL?-FROM-SLOT */
Object write_positive_quantity_interval_qm_from_slot(number_qm,gensymed_symbol)
    Object number_qm, gensymed_symbol;
{
    x_note_fn_call(199,215);
    if (number_qm)
	return print_constant(2,number_qm,Qseconds);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object Qdefault;            /* default */

static Object array_constant_4;    /* # */

/* COMPILE-INTERVAL?-OR-DEFAULT-FOR-SLOT */
Object compile_interval_qm_or_default_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,216);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qdefault))
	return VALUES_1(parse_result);
    else if (IFIX(CAR(parse_result)) == (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_4,
		FIX((SI_Long)30L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

static Object Quse_default;        /* use-default */

/* INTERVAL?-OR-DEFAULT-EVALUATION-SETTER */
Object interval_qm_or_default_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,217);
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
			  list_constant_21))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_22,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_interval_qm_or_default_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value))
	result = phrase_cons(evaluation_value,Qseconds);
    else if (EQ(evaluation_value,Quse_default))
	result = VALUES_1(Qdefault);
    else
	result = VALUES_1(Qnone);
  end_interval_qm_or_default_evaluation_setter:
    return result;
}

/* INTERVAL?-OR-DEFAULT-EVALUATION-GETTER */
Object interval_qm_or_default_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,218);
    GENSYM_RETURN_ONE(EQ(slot_value,Qdefault) ? Quse_default : slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_37;  /* "use default" */

/* WRITE-INTERVAL?-OR-DEFAULT-FROM-SLOT */
Object write_interval_qm_or_default_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,219);
    if ( !TRUEP(value))
	return twrite_symbol(1,Qnone);
    else if (EQ(value,Qdefault))
	return twrite(string_constant_37);
    else if (NUMBERP(value))
	return print_constant(2,value,Qseconds);
    else
	return VALUES_1(Qnil);
}

/* COMPILE-POSITIVE-INTERVAL?-OR-DEFAULT-FOR-SLOT */
Object compile_positive_interval_qm_or_default_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,220);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qdefault))
	return VALUES_1(parse_result);
    else if (IFIX(CAR(parse_result)) <= (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)39L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

/* WRITE-POSITIVE-INTERVAL?-OR-DEFAULT-FROM-SLOT */
Object write_positive_interval_qm_or_default_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,221);
    if ( !TRUEP(value))
	return twrite_symbol(1,Qnone);
    else if (EQ(value,Qdefault))
	return twrite(string_constant_37);
    else if (FIXNUMP(value))
	return print_constant(2,value,Qseconds);
    else
	return VALUES_1(Qnil);
}

/* COMPILE-EXECUTION-INTERVAL?-OR-DEFAULT-FOR-SLOT */
Object compile_execution_interval_qm_or_default_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,222);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (EQ(parse_result,Qdefault))
	return VALUES_1(parse_result);
    else if (IFIX(CAR(parse_result)) <= (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)39L));
	return VALUES_2(temp,temp_1);
    }
    else if (IFIX(CAR(parse_result)) > (SI_Long)86400L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_3,
		FIX((SI_Long)43L));
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

static Object list_constant_23;    /* # */

/* EXECUTION-INTERVAL?-OR-DEFAULT-EVALUATION-SETTER */
Object execution_interval_qm_or_default_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,223);
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
			  list_constant_23))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_22,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_execution_interval_qm_or_default_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	if (EQ(evaluation_value,Quse_default))
	    result = VALUES_1(Qdefault);
	else
	    result = phrase_cons(evaluation_value,Qseconds);
    }
    else
	result = VALUES_1(Qnone);
  end_execution_interval_qm_or_default_evaluation_setter:
    return result;
}

/* EXECUTION-INTERVAL?-OR-DEFAULT-EVALUATION-GETTER */
Object execution_interval_qm_or_default_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,224);
    GENSYM_RETURN_ONE(EQ(slot_value,Qdefault) ? Quse_default : slot_value);
    return VALUES_1(Nil);
}

static Object Qpositive_interval_qm_or_default;  /* positive-interval?-or-default */

/* WRITE-EXECUTION-INTERVAL?-OR-DEFAULT-FROM-SLOT */
Object write_execution_interval_qm_or_default_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(199,225);
    slot_value_writer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_interval_qm_or_default),
	    Qslot_value_writer);
    if (slot_value_writer_qm) {
	write_symbols_in_lower_case_qm = T;
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		  0);
	    result = VALUES_1(inline_funcall_2(slot_value_writer_qm,value,
		    Nil));
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return twrite(string_constant_36);
}

static Object Qdependent;          /* dependent */

static Object Qbad;                /* bad */

static Object Qsimulation_subtable_byte_code_body;  /* simulation-subtable-byte-code-body */

static Object list_constant_24;    /* # */

static Object Qsimulation_subtable_initial_value_byte_code_body;  /* simulation-subtable-initial-value-byte-code-body */

/* COMPILE-SPECIFIC-SIMULATION-FORMULA?-FOR-SLOT */
Object compile_specific_simulation_formula_qm_for_slot varargs_1(int, n)
{
    Object parse_result, simulation_subtable, slot_name;
    Object current_computation_frame, form_to_return, compiled_expression_qm;
    Object simulation_category, compiled_initial_value_qm;
    Object current_computation_component_particulars, byte_code_body;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(199,226);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    simulation_subtable = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    update_frame_status(simulation_subtable,Nil,Nil);
    current_computation_frame = simulation_subtable;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      if (EQ(parse_result,Qnone))
	  form_to_return = phrase_list_3(Nil,compile_expression(Nil,Nil,
		  Nil),Nil);
      else if (ATOM(parse_result) ||  
	      !TRUEP(memq_function(CAR(parse_result),list_constant_1))) {
	  compiled_expression_qm = compile_expression(parse_result,Nil,Nil);
	  if (compiled_expression_qm)
	      form_to_return = phrase_list_3(Qdependent,
		      compiled_expression_qm,Nil);
	  else {
	      update_frame_status(simulation_subtable,Qbad,Nil);
	      form_to_return = phrase_list_3(Qdependent,Nil,Nil);
	  }
      }
      else {
	  compiled_expression_qm = compile_expression(SECOND(parse_result),
		  Nil,Nil);
	  simulation_category = CAR(parse_result);
	  compiled_initial_value_qm = Nil;
	  if ( !TRUEP(compiled_expression_qm)) {
	      update_frame_status(simulation_subtable,Qbad,Nil);
	      form_to_return = phrase_list_3(simulation_category,Nil,Nil);
	  }
	  else {
	      compiled_initial_value_qm = 
		      compile_expression(THIRD(parse_result),Nil,Nil);
	      if ( !TRUEP(compiled_initial_value_qm)) {
		  update_frame_status(simulation_subtable,Qbad,Nil);
		  form_to_return = phrase_list_3(simulation_category,Nil,Nil);
	      }
	      else
		  form_to_return = phrase_list_3(simulation_category,
			  compiled_expression_qm,compiled_initial_value_qm);
	  }
      }
      if (THIRD(form_to_return)) {
	  change_slot_value(3,simulation_subtable,
		  Qsimulation_subtable_byte_code_body,Nil);
	  current_computation_component_particulars = list_constant_24;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		  0);
	    byte_code_body = 
		    compile_simulation_formula_for_stack(THIRD(form_to_return),
		    Nil,Nil,T);
	    change_slot_value(3,simulation_subtable,
		    Qsimulation_subtable_initial_value_byte_code_body,
		    byte_code_body);
	  POP_SPECIAL();
      }
      else
	  change_slot_value(3,simulation_subtable,
		  Qsimulation_subtable_initial_value_byte_code_body,Nil);
      if (SECOND(form_to_return)) {
	  byte_code_body = 
		  compile_simulation_formula_for_stack(SECOND(form_to_return),
		  Nil,Nil,Nil);
	  change_slot_value(3,simulation_subtable,
		  Qsimulation_subtable_byte_code_body,byte_code_body);
      }
      result = VALUES_1(form_to_return);
    POP_SPECIAL();
    return result;
}

/* WRITE-WHOLE-STRING?-FROM-SLOT */
Object write_whole_string_qm_from_slot(whole_string_qm,gensymed_symbol)
    Object whole_string_qm, gensymed_symbol;
{
    Object write_strings_parsably_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,227);
    if (whole_string_qm) {
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  result = twrite_general_string(whole_string_qm);
	POP_SPECIAL();
	return result;
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

/* COMPILE-WHOLE-STRING?-FOR-SLOT */
Object compile_whole_string_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,228);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (text_string_p(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

/* WRITE-READ-ONLY-WHOLE-STRING?-FROM-SLOT */
Object write_read_only_whole_string_qm_from_slot(whole_string_qm,
	    gensymed_symbol)
    Object whole_string_qm, gensymed_symbol;
{
    Object write_strings_parsably_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,229);
    if (whole_string_qm) {
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  result = twrite_general_string(whole_string_qm);
	POP_SPECIAL();
	return result;
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object list_constant_25;    /* # */

/* TRUTH-VALUE-EVALUATION-SETTER */
Object truth_value_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,230);
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
			  list_constant_25))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qtruth_value,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_truth_value_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = M_CAR(evaluation_value);
    if ( !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-32768L),temp_1) && 
	    FIXNUM_LE(temp_1,FIX((SI_Long)32767L)))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = make_slot_constant_using_phrase_conses(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(CAR(evaluation_value)) 
		    / 1000.0),Qtruth_value);
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	switch (INTEGER_TO_SHORT(temp_1)) {
	  case 1000:
	    result = VALUES_1(Qtrue);
	    break;
	  case -1000:
	    result = VALUES_1(Qfalse);
	    break;
	  default:
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		result = make_slot_constant_using_phrase_conses(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(CAR(evaluation_value)) 
			/ 1000.0),Qtruth_value);
	    POP_LOCAL_ALLOCATION(0,0);
	    break;
	}
  end_truth_value_evaluation_setter:
    return result;
}

/* TRUTH-VALUE-EVALUATION-GETTER */
Object truth_value_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(199,231);
    if (FIXNUM_EQ(slot_value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(slot_value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(slot_value,Qtruth_value);
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

/* TRUTH-VALUE?-EVALUATION-SETTER */
Object truth_value_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,232);
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
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_27,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_truth_value_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtruth_value),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_truth_value_qm_evaluation_setter:
    return result;
}

/* TRUTH-VALUE?-EVALUATION-GETTER */
Object truth_value_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,233);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtruth_value),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_28;    /* # */

/* NON-NEGATIVE-INTEGER-EVALUATION-SETTER */
Object non_negative_integer_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,234);
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
			  list_constant_28))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_non_negative_integer_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_non_negative_integer_evaluation_setter:
    return result;
}

/* NON-NEGATIVE-INTEGER-EVALUATION-GETTER */
Object non_negative_integer_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,235);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_29;    /* # */

/* INTEGER-EVALUATION-SETTER */
Object integer_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,236);
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
			  list_constant_29))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_integer_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_integer_evaluation_setter:
    return result;
}

/* INTEGER-EVALUATION-GETTER */
Object integer_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,237);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_30;    /* # */

static Object list_constant_31;    /* # */

/* INTEGER?-EVALUATION-SETTER */
Object integer_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,238);
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
			  list_constant_30))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_31,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_integer_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_integer_qm_evaluation_setter:
    return result;
}

/* INTEGER?-EVALUATION-GETTER */
Object integer_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,239);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_32;    /* # */

/* QUANTITY-EVALUATION-SETTER */
Object quantity_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,240);
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
			  list_constant_32))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qnumber,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_quantity_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    value = evaluation_value_value(evaluation_value);
    if (FIXNUMP(value))
	result = VALUES_1(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value = INTEGER_TO_INT64(value);
	set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	result = note_use_of_managed_long_in_phrase(new_long);
    }
    else {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	result = note_use_of_managed_float_in_phrase(new_float);
    }
  end_quantity_evaluation_setter:
    return result;
}

/* QUANTITY-EVALUATION-GETTER */
Object quantity_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object thing, temp;

    x_note_fn_call(199,241);
    if (CONSP(slot_value)) {
	thing = M_CAR(slot_value);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L ? 
		copy_managed_float(M_CAR(slot_value)) : M_CAR(slot_value);
    }
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L 
		? copy_managed_float(slot_value) : slot_value;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_33;    /* # */

static Object list_constant_34;    /* # */

/* QUANTITY?-EVALUATION-SETTER */
Object quantity_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,242);
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
			  list_constant_33))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_34,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_quantity_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantity),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_quantity_qm_evaluation_setter:
    return result;
}

/* QUANTITY?-EVALUATION-GETTER */
Object quantity_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,243);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qquantity),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_35;    /* # */

/* INITIAL-VALUE-FLOAT-EVALUATION-SETTER */
Object initial_value_float_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,244);
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
			  list_constant_35))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qfloat,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_value_float_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    value = evaluation_value_value(evaluation_value);
    if (FIXNUMP(value))
	result = VALUES_1(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value = INTEGER_TO_INT64(value);
	set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
	result = note_use_of_managed_long_in_phrase(new_long);
    }
    else {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	result = note_use_of_managed_float_in_phrase(new_float);
    }
  end_initial_value_float_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-FLOAT-EVALUATION-GETTER */
Object initial_value_float_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,245);
    GENSYM_RETURN_ONE(copy_managed_float(slot_value));
    return VALUES_1(Nil);
}

static Object list_constant_36;    /* # */

static Object list_constant_37;    /* # */

static Object Qinitial_value_float;  /* initial-value-float */

/* INITIAL-VALUE-FLOAT?-EVALUATION-SETTER */
Object initial_value_float_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,246);
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
			  list_constant_36))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_37,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_value_float_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_float),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_initial_value_float_qm_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-FLOAT?-EVALUATION-GETTER */
Object initial_value_float_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,247);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_float),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_38;    /* # */

/* INITIAL-VALUE-INTEGER-EVALUATION-SETTER */
Object initial_value_integer_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,248);
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
			  list_constant_38))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_value_integer_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_initial_value_integer_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-INTEGER-EVALUATION-GETTER */
Object initial_value_integer_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,249);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_39;    /* # */

/* INITIAL-VALUE-LONG-EVALUATION-SETTER */
Object initial_value_long_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,250);
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
			  list_constant_39))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,Qlong,
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
		      goto end_initial_value_long_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_initial_value_long_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-LONG-EVALUATION-GETTER */
Object initial_value_long_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,251);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_40;    /* # */

static Object list_constant_41;    /* # */

static Object Qinitial_value_long;  /* initial-value-long */

/* INITIAL-VALUE-LONG?-EVALUATION-SETTER */
Object initial_value_long_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,252);
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
			  list_constant_40))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_41,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_value_long_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_long),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_initial_value_long_qm_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-LONG?-EVALUATION-GETTER */
Object initial_value_long_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,253);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_long),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_42;    /* # */

static Object list_constant_43;    /* # */

static Object Qinitial_value_integer;  /* initial-value-integer */

/* INITIAL-VALUE-INTEGER?-EVALUATION-SETTER */
Object initial_value_integer_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,254);
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
			  list_constant_42))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_43,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_value_integer_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_integer),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_initial_value_integer_qm_evaluation_setter:
    return result;
}

/* INITIAL-VALUE-INTEGER?-EVALUATION-GETTER */
Object initial_value_integer_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,255);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitial_value_integer),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_44;    /* # */

/* STANDARD-OR-CLASS-QUALIFIED-SYMBOL-EVALUATION-SETTER */
Object standard_or_class_qualified_symbol_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,256);
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
			  list_constant_44))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_standard_or_class_qualified_symbol_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_standard_or_class_qualified_symbol_evaluation_setter:
    return result;
}

/* STANDARD-OR-CLASS-QUALIFIED-SYMBOL-EVALUATION-GETTER */
Object standard_or_class_qualified_symbol_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,257);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_45;    /* # */

static Object list_constant_46;    /* # */

static Object Qstandard_or_class_qualified_symbol;  /* standard-or-class-qualified-symbol */

/* STANDARD-OR-CLASS-QUALIFIED-SYMBOL?-EVALUATION-SETTER */
Object standard_or_class_qualified_symbol_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,258);
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
			  list_constant_45))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_46,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_standard_or_class_qualified_symbol_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstandard_or_class_qualified_symbol),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_standard_or_class_qualified_symbol_qm_evaluation_setter:
    return result;
}

/* STANDARD-OR-CLASS-QUALIFIED-SYMBOL?-EVALUATION-GETTER */
Object standard_or_class_qualified_symbol_qm_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,259);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstandard_or_class_qualified_symbol),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_47;    /* # */

/* WHOLE-STRING-EVALUATION-SETTER */
Object whole_string_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,260);
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
			  list_constant_47))) {
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
		      goto end_whole_string_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = copy_for_phrase(evaluation_value);
  end_whole_string_evaluation_setter:
    return result;
}

/* WHOLE-STRING-EVALUATION-GETTER */
Object whole_string_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,261);
    GENSYM_RETURN_ONE(copy_as_wide_string(slot_value));
    return VALUES_1(Nil);
}

static Object list_constant_48;    /* # */

static Object list_constant_49;    /* # */

static Object Qwhole_string;       /* whole-string */

/* WHOLE-STRING?-EVALUATION-SETTER */
Object whole_string_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,262);
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
			  list_constant_48))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_49,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_whole_string_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_whole_string_qm_evaluation_setter:
    return result;
}

/* WHOLE-STRING?-EVALUATION-GETTER */
Object whole_string_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,263);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* READ-ONLY-WHOLE-STRING?-EVALUATION-GETTER */
Object read_only_whole_string_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,264);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_50;    /* # */

/* POSITIVE-INTEGER-EVALUATION-SETTER */
Object positive_integer_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,265);
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
			  list_constant_50))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qinteger,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_positive_integer_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_positive_integer_evaluation_setter:
    return result;
}

/* POSITIVE-INTEGER-EVALUATION-GETTER */
Object positive_integer_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,266);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* READ-ONLY-POSITIVE-INTEGER-EVALUATION-GETTER */
Object read_only_positive_integer_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,267);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-READ-ONLY-POSITIVE-INTEGER-FROM-SLOT */
Object write_read_only_positive_integer_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(199,268);
    return write_attribute(integer);
}

/* READ-ONLY-INTEGER-EVALUATION-GETTER */
Object read_only_integer_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,269);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-READ-ONLY-INTEGER-FROM-SLOT */
Object write_read_only_integer_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(199,270);
    return write_attribute(integer);
}

static Object list_constant_51;    /* # */

static Object list_constant_52;    /* # */

static Object Qpositive_integer;   /* positive-integer */

/* POSITIVE-INTEGER?-EVALUATION-SETTER */
Object positive_integer_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,271);
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
			  list_constant_51))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_52,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_positive_integer_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(Qnone);
  end_positive_integer_qm_evaluation_setter:
    return result;
}

/* POSITIVE-INTEGER?-EVALUATION-GETTER */
Object positive_integer_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,272);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-READ-ONLY-POSITIVE-INTEGER?-FROM-SLOT */
Object write_read_only_positive_integer_qm_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(199,273);
    return write_attribute(integer);
}

/* READ-ONLY-POSITIVE-INTEGER?-EVALUATION-GETTER */
Object read_only_positive_integer_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,274);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_53;    /* # */

/* DATA-TYPE-OF-INITIAL-SENSOR-VALUE */
Object data_type_of_initial_sensor_value(parse_result)
    Object parse_result;
{
    x_note_fn_call(199,275);
    if (memq_function(parse_result,list_constant_53))
	return VALUES_1(Qtruth_value);
    else if (phrase_number_p(parse_result))
	return VALUES_1(Qnumber);
    else if (text_string_p(parse_result))
	return VALUES_1(Qtext);
    else if (SYMBOLP(parse_result))
	return VALUES_1(Qsymbol);
    else
	return VALUES_1(CDR(parse_result));
}

static Object list_constant_54;    /* # */

static Object string_constant_38;  /* "The initial value must be compatible with the type of the variable." */

/* COMPILE-INITIAL-SENSOR-VALUE?-FOR-SLOT */
Object compile_initial_sensor_value_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame_qm, gensymed_symbol;
    Object incoming_type, type1, type2, temp_1, temp_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,276);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame_qm = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    incoming_type = data_type_of_initial_sensor_value(parse_result);
    temp =  !TRUEP(frame_qm);
    if (temp);
    else {
	type1 = incoming_type;
	type2 = ISVREF(frame_qm,(SI_Long)20L);
	temp = EQ(type1,type2);
	if (temp);
	else
	    temp = EQ(type1,Qnumber) ? EQ(type2,Qnumber) || EQ(type2,
		    Qinteger) || EQ(type2,Qfloat) || EQ(type2,Qlong) || 
		    lookup_global_or_kb_specific_property_value(type2,
		    Numeric_data_type_gkbprop) : TRUEP(Qnil);
	if (temp);
	else
	    temp = EQ(type2,Qnumber) ? EQ(type1,Qnumber) || EQ(type1,
		    Qinteger) || EQ(type1,Qfloat) || EQ(type1,Qlong) || 
		    lookup_global_or_kb_specific_property_value(type1,
		    Numeric_data_type_gkbprop) : TRUEP(Qnil);
	if (temp);
	else
	    temp = EQ(type1,Qinteger) || memq_function(type1,
		    list_constant_54) ? EQ(type2,Qinteger) || 
		    memq_function(type2,list_constant_54) : TRUEP(Qnil);
    }
    if (temp);
    else
	temp = EQ(parse_result,Qnone);
    if (temp) {
	if (EQ(parse_result,Qnone))
	    return VALUES_1(Nil);
	else if (EQ(parse_result,Qtrue))
	    return phrase_list_2(Truth,Qtruth_value);
	else if (EQ(parse_result,Qfalse))
	    return phrase_list_2(Falsity,Qtruth_value);
	else if (ATOM(parse_result))
	    return VALUES_1(parse_result);
	else if (EQ(CDR(parse_result),Qtruth_value))
	    return l_round(ltimes(Truth,CAR(parse_result)),_);
	else if (phrase_number_p(CAR(parse_result)))
	    return VALUES_1(CAR(parse_result));
	else
	    return VALUES_1(Qnil);
    }
    else {
	temp_1 = Bad_phrase;
	temp_2 = copy_text_string(string_constant_38);
	return VALUES_2(temp_1,temp_2);
    }
}

/* WRITE-INITIAL-SENSOR-VALUE?-FROM-SLOT */
Object write_initial_sensor_value_qm_from_slot(value,frame_qm)
    Object value, frame_qm;
{
    Object car_1, cdr_1, temp, x2;
    char temp_1;

    x_note_fn_call(199,277);
    if (CONSP(value)) {
	car_1 = M_CAR(value);
	cdr_1 = M_CDR(value);
	if (CONSP(cdr_1)) {
	    temp = M_CAR(cdr_1);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return print_constant(2,M_CAR(value),M_CAR(M_CDR(value)));
    else if (value) {
	if (SIMPLE_VECTOR_P(frame_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L && 
		 !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_qm,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	return print_constant(2,value,temp_1 ? ISVREF(frame_qm,
		(SI_Long)20L) : evaluation_value_type(value));
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object list_constant_55;    /* # */

static Object list_constant_56;    /* # */

/* INITIAL-SENSOR-VALUE?-EVALUATION-SETTER */
Object initial_sensor_value_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,278);
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
			  list_constant_55))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_56,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_initial_sensor_value_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value))
	result = VALUES_1(Qnone);
    else
	result = copy_evaluation_value_to_phrase(evaluation_value);
  end_initial_sensor_value_qm_evaluation_setter:
    return result;
}

/* INITIAL-SENSOR-VALUE?-EVALUATION-GETTER */
Object initial_sensor_value_qm_evaluation_getter(slot_value,frame_qm,
	    slot_description)
    Object slot_value, frame_qm, slot_description;
{
    x_note_fn_call(199,279);
    GENSYM_RETURN_ONE(get_evaluation_value_for_attribute(slot_value,frame_qm));
    return VALUES_1(Nil);
}

static Object string_constant_39;  /* "Must be \"none\" or an integer from 1 through 60000." */

/* COMPILE-DELAY-MILLISECOND-TIME?-FOR-SLOT */
Object compile_delay_millisecond_time_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,280);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else {
	if (INTEGERP(parse_result)) {
	    temp = FIX((SI_Long)0L);
	    temp_1 = NUM_GT(parse_result,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = FIX((SI_Long)60000L);
	    temp_1 = NUM_LE(parse_result,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(parse_result);
	else {
	    temp_2 = Bad_phrase;
	    temp = copy_text_string(string_constant_39);
	    return VALUES_2(temp_2,temp);
	}
    }
}

static Object list_constant_57;    /* # */

static Object Qinteger_qm;         /* integer? */

/* DELAY-MILLISECOND-TIME?-EVALUATION-SETTER */
Object delay_millisecond_time_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,281);
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
			  list_constant_57))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_30,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_delay_millisecond_time_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_delay_millisecond_time_qm_evaluation_setter:
    return result;
}

/* DELAY-MILLISECOND-TIME?-EVALUATION-GETTER */
Object delay_millisecond_time_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,282);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinteger_qm),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-DELAY-MILLISECOND-TIME?-FROM-SLOT */
Object write_delay_millisecond_time_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,283);
    return write_integer_qm_from_slot(value,Nil);
}

static Object list_constant_58;    /* # */

static Object list_constant_59;    /* # */

/* TRACE-FILE-PATHNAME-EVALUATION-SETTER */
Object trace_file_pathname_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,284);
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
			  list_constant_58))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_59,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_trace_file_pathname_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qnone))
	result = VALUES_1(Nil);
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
  end_trace_file_pathname_evaluation_setter:
    return result;
}

/* TRACE-FILE-PATHNAME-EVALUATION-GETTER */
Object trace_file_pathname_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(199,285);
    if (slot_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = Qnone;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_40;  /* "none" */

/* WRITE-NUMBER?-FROM-SLOT */
Object write_number_qm_from_slot(number_qm,frame)
    Object number_qm, frame;
{
    x_note_fn_call(199,286);
    if ( !TRUEP(number_qm))
	return twrite(string_constant_40);
    else
	return write_number_from_slot(number_qm,frame);
}

/* COMPILE-QUANTITY-FOR-SLOT */
Object compile_quantity_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,287);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* WRITE-QUANTITY-FROM-SLOT */
Object write_quantity_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(199,288);
    return write_initial_sensor_value_qm_from_slot(value,frame);
}

/* COMPILE-QUANTITY?-FOR-SLOT */
Object compile_quantity_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,289);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* WRITE-QUANTITY?-FROM-SLOT */
Object write_quantity_qm_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(199,290);
    return write_initial_sensor_value_qm_from_slot(value,frame);
}

/* COMPILE-NUMBER?-FOR-SLOT */
Object compile_number_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,291);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (slot_value_number_p(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

static Object list_constant_60;    /* # */

static Object list_constant_61;    /* # */

/* NUMBER?-EVALUATION-SETTER */
Object number_qm_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,292);
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
			  list_constant_60))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_61,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_number_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	value = evaluation_value_value(evaluation_value);
	if (FIXNUMP(value))
	    result = VALUES_1(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    result = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    result = note_use_of_managed_float_in_phrase(new_float);
	}
    }
    else
	result = VALUES_1(Qnone);
  end_number_qm_evaluation_setter:
    return result;
}

/* NUMBER?-EVALUATION-GETTER */
Object number_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,293);
    GENSYM_RETURN_ONE(slot_value ? 
	    (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L ? 
	    copy_managed_float(slot_value) : slot_value) : Nil);
    return VALUES_1(Nil);
}

/* WRITE-NUMBER-FROM-SLOT */
Object write_number_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    Object number_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,294);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L)
	    number_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L)
	    number_value = aref1(number,FIX((SI_Long)0L));
	else
	    number_value = number;
	if (FLOATP(number_value))
	    result = write_floating_point_number_simple_c_format(1,
		    number_value);
	else if (INLINE_LONG_P(number_value) != (SI_Long)0L)
	    result = twrite_long(number_value);
	else
	    result = twrite(number_value);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-INTEGER-FROM-SLOT */
Object write_integer_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(199,295);
    return twrite(integer);
}

/* WRITE-INITIAL-VALUE-INTEGER-FROM-SLOT */
Object write_initial_value_integer_from_slot(integer,frame)
    Object integer, frame;
{
    x_note_fn_call(199,296);
    return write_initial_sensor_value_qm_from_slot(integer,frame);
}

/* WRITE-LONG-FROM-SLOT */
Object write_long_from_slot(long_1,gensymed_symbol)
    Object long_1, gensymed_symbol;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,297);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = twrite_long(long_1);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-INITIAL-VALUE-LONG-FROM-SLOT */
Object write_initial_value_long_from_slot(i64,frame)
    Object i64, frame;
{
    x_note_fn_call(199,298);
    return write_initial_sensor_value_qm_from_slot(i64,frame);
}

/* WRITE-FLOAT-FROM-SLOT */
Object write_float_from_slot(slot_value_or_gensym_float,gensymed_symbol)
    Object slot_value_or_gensym_float, gensymed_symbol;
{
    Object temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,299);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_or_gensym_float) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_or_gensym_float)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_or_gensym_float,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_or_gensym_float) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_or_gensym_float)) 
		== (SI_Long)1L)
	    temp = aref1(slot_value_or_gensym_float,FIX((SI_Long)0L));
	else
	    temp = slot_value_or_gensym_float;
	result = write_floating_point_number_simple_c_format(1,temp);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-INITIAL-VALUE-FLOAT-FROM-SLOT */
Object write_initial_value_float_from_slot(slot_value_or_gensym_float,frame)
    Object slot_value_or_gensym_float, frame;
{
    x_note_fn_call(199,300);
    return write_initial_sensor_value_qm_from_slot(slot_value_or_gensym_float,
	    frame);
}

/* WRITE-FLOAT?-FROM-SLOT */
Object write_float_qm_from_slot(slot_value_float_or_nil,gensymed_symbol)
    Object slot_value_float_or_nil, gensymed_symbol;
{
    x_note_fn_call(199,301);
    if ( !TRUEP(slot_value_float_or_nil))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else
	return write_float_from_slot(slot_value_float_or_nil,Nil);
}

/* WRITE-INITIAL-VALUE-FLOAT?-FROM-SLOT */
Object write_initial_value_float_qm_from_slot(slot_value_float_or_nil,frame)
    Object slot_value_float_or_nil, frame;
{
    x_note_fn_call(199,302);
    return write_initial_sensor_value_qm_from_slot(slot_value_float_or_nil,
	    frame);
}

/* WRITE-INTEGER?-FROM-SLOT */
Object write_integer_qm_from_slot(integer_qm,gensymed_symbol)
    Object integer_qm, gensymed_symbol;
{
    x_note_fn_call(199,303);
    if (integer_qm)
	return twrite(integer_qm);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

/* WRITE-INITIAL-VALUE-INTEGER?-FROM-SLOT */
Object write_initial_value_integer_qm_from_slot(integer_qm,frame)
    Object integer_qm, frame;
{
    x_note_fn_call(199,304);
    return write_initial_sensor_value_qm_from_slot(integer_qm,frame);
}

/* WRITE-INITIAL-VALUE-LONG?-FROM-SLOT */
Object write_initial_value_long_qm_from_slot(i64_qm,frame)
    Object i64_qm, frame;
{
    x_note_fn_call(199,305);
    return write_initial_sensor_value_qm_from_slot(i64_qm,frame);
}

/* COMPILE-INITIAL-VALUE-LONG?-FOR-SLOT */
Object compile_initial_value_long_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,306);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-INITIAL-VALUE-LONG-FOR-SLOT */
Object compile_initial_value_long_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,307);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-INTEGER?-FOR-SLOT */
Object compile_integer_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,308);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (INTEGERP(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

/* COMPILE-INITIAL-VALUE-INTEGER?-FOR-SLOT */
Object compile_initial_value_integer_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,309);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-FLOAT?-FOR-SLOT */
Object compile_float_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,310);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* COMPILE-INITIAL-VALUE-FLOAT?-FOR-SLOT */
Object compile_initial_value_float_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,311);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-INITIAL-VALUE-INTEGER-FOR-SLOT */
Object compile_initial_value_integer_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,312);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-INITIAL-VALUE-FLOAT-FOR-SLOT */
Object compile_initial_value_float_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,313);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_initial_sensor_value_qm_for_slot(3,parse_result,frame,Nil);
}

/* COMPILE-SYMBOL?-FOR-SLOT */
Object compile_symbol_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,314);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* COMPILE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL?-FOR-SLOT */
Object compile_standard_or_class_qualified_symbol_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,315);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL?-FROM-SLOT */
Object write_standard_or_class_qualified_symbol_qm_from_slot(symbol_qm,
	    gensymed_symbol)
    Object symbol_qm, gensymed_symbol;
{
    x_note_fn_call(199,316);
    if ( !TRUEP(symbol_qm))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else
	return print_constant(2,symbol_qm,Qsymbol);
}

/* COMPILE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL-FOR-SLOT */
Object compile_standard_or_class_qualified_symbol_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,317);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(parse_result);
}

/* WRITE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL-FROM-SLOT */
Object write_standard_or_class_qualified_symbol_from_slot(symbol,
	    gensymed_symbol)
    Object symbol, gensymed_symbol;
{
    x_note_fn_call(199,318);
    return print_constant(2,symbol,Qsymbol);
}

/* WRITE-WHOLE-STRING-FROM-SLOT */
Object write_whole_string_from_slot(whole_string,gensymed_symbol)
    Object whole_string, gensymed_symbol;
{
    Object write_strings_parsably_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(199,319);
    write_strings_parsably_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
	    0);
      result = twrite_general_string(whole_string);
    POP_SPECIAL();
    return result;
}

/* COMPILE-TRUTH-VALUE-FOR-SLOT */
Object compile_truth_value_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,320);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_truth_value_parse_result(parse_result);
}

/* COMPILE-TRUTH-VALUE?-FOR-SLOT */
Object compile_truth_value_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,321);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return compile_truth_value_parse_result(parse_result);
}

/* COMPILE-TRUTH-VALUE-PARSE-RESULT */
Object compile_truth_value_parse_result(parse_result)
    Object parse_result;
{
    Object thing;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,322);
    if (EQ(parse_result,Qtrue))
	return VALUES_1(Truth);
    else if (EQ(parse_result,Qfalse))
	return VALUES_1(Falsity);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    thing = CAR(parse_result);
	    result = l_round(ltimes(Truth,
		    INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L ?
		     
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CAR(parse_result),
		    (SI_Long)0L)) : CAR(parse_result)),_);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* WRITE-TRUTH-VALUE-FROM-SLOT */
Object write_truth_value_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,323);
    return print_constant(2,value,Qtruth_value);
}

/* WRITE-TRUTH-VALUE?-FROM-SLOT */
Object write_truth_value_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,324);
    if (value)
	return print_constant(2,value,Qtruth_value);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object list_constant_62;    /* # */

static Object list_constant_63;    /* # */

static Object Qforward_chain;      /* forward-chain */

static Object Qforward_chain_flag;  /* forward-chain-flag */

static Object Qforward;            /* forward */

static Object Qchain;              /* chain */

static Object Qforward_chain_even_for_same_value;  /* forward-chain-even-for-same-value */

static Object Qalways_forward_chain_if_possible_flag;  /* always-forward-chain-if-possible-flag */

static Object Qdont_always_forward_chain_if_possible_flag;  /* dont-always-forward-chain-if-possible-flag */

static Object Qbackward_chain;     /* backward-chain */

static Object Qdo_not_seek_data;   /* do-not-seek-data */

static Object Qpassive_flag;       /* passive-flag */

static Object Qdo_not_backward_chain;  /* do-not-backward-chain */

static Object Qdont_backward_chain_flag;  /* dont-backward-chain-flag */

static Object Qdepth_first;        /* depth-first */

static Object Qdepth_first_flag;   /* depth-first-flag */

static Object Qbreadth;            /* breadth */

static Object Qbackward;           /* backward */

static Object Qexplanation_data;   /* explanation-data */

static Object Qcache_data_for_explanation_flag;  /* cache-data-for-explanation-flag */

/* VARIABLE-FRAME-FLAGS-EVALUATION-SETTER */
Object variable_frame_flags_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object forward_chaining_phrase, for_same_value_phrase;
    Object backward_chaining_phrase, explanation_phrase;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,325);
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
			  list_constant_62))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_63,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_variable_frame_flags_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qforward_chain,Nil);
    forward_chaining_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qforward_chain,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qforward_chain,Nil)),Truth) ? Qforward_chain_flag : 
	    phrase_list_4(Qdo,Qnot,Qforward,Qchain);
    temp_1 = estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil);
    for_same_value_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil)),Qtruth_value) && 
	    EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil)),Truth) ? 
	    Qalways_forward_chain_if_possible_flag : 
	    Qdont_always_forward_chain_if_possible_flag;
    temp_1 = estructure_slot(gensymed_symbol,Qbackward_chain,Nil);
    if (EQ(temp_1,Qdo_not_seek_data))
	backward_chaining_phrase = Qpassive_flag;
    else if (EQ(temp_1,Qdo_not_backward_chain))
	backward_chaining_phrase = Qdont_backward_chain_flag;
    else if (EQ(temp_1,Qdepth_first))
	backward_chaining_phrase = Qdepth_first_flag;
    else
	backward_chaining_phrase = phrase_list_4(Qbreadth,Qfirst,Qbackward,
		Qchain);
    temp_1 = estructure_slot(gensymed_symbol,Qexplanation_data,Nil);
    explanation_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qexplanation_data,
	    Nil)),Qtruth_value) && 
	    EQ(M_CAR(estructure_slot(gensymed_symbol,Qexplanation_data,
	    Nil)),Truth) ? Qcache_data_for_explanation_flag : Nil;
    result = phrase_list_4(forward_chaining_phrase,for_same_value_phrase,
	    backward_chaining_phrase,explanation_phrase);
  end_variable_frame_flags_evaluation_setter:
    return result;
}

static Object Qbreadth_first;      /* breadth-first */

/* VARIABLE-FRAME-FLAGS-EVALUATION-GETTER */
Object variable_frame_flags_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, backward_chaining_info;

    x_note_fn_call(199,326);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)16L))
	backward_chaining_info = Qdo_not_seek_data;
    else if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)32768L))
	backward_chaining_info = Qdo_not_backward_chain;
    else if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)8L))
	backward_chaining_info = Qdepth_first;
    else
	backward_chaining_info = Qbreadth_first;
    set_evaluation_structure_slot(gensymed_symbol,Qforward_chain,
	    (SI_Long)0L != (IFIX(slot_value) & (SI_Long)2L) ? 
	    Evaluation_true_value : Evaluation_false_value);
    set_evaluation_structure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,(SI_Long)0L != 
	    (IFIX(slot_value) & (SI_Long)32L) ? Evaluation_true_value : 
	    Evaluation_false_value);
    set_evaluation_structure_slot(gensymed_symbol,Qbackward_chain,
	    backward_chaining_info);
    if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)1048576L))
	set_evaluation_structure_slot(gensymed_symbol,Qexplanation_data,T ?
		 Evaluation_true_value : Evaluation_false_value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qframe_flags;        /* frame-flags */

static Object Qg2_internal_cached_explanation;  /* g2-internal-cached-explanation */

/* COMPILE-VARIABLE-FRAME-FLAGS-FOR-SLOT */
Object compile_variable_frame_flags_for_slot varargs_1(int, n)
{
    Object parse_result, variable, gensymed_symbol;
    Object temp, cached_explanation_qm;
    SI_Long svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,327);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(FIRST(parse_result),Qforward_chain_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)2L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  ~(SI_Long)2L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (EQ(SECOND(parse_result),Qalways_forward_chain_if_possible_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)32L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  ~(SI_Long)32L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qframe_flags);
    svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  ~(SI_Long)16L;
    ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qframe_flags);
    svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  ~(SI_Long)32768L;
    ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qframe_flags);
    svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  ~(SI_Long)8L;
    ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    temp = THIRD(parse_result);
    if (EQ(temp,Qpassive_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)16L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)32768L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    else if (EQ(temp,Qdont_backward_chain_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)32768L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    else if (EQ(temp,Qdepth_first_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | (SI_Long)8L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (EQ(FOURTH(parse_result),Qcache_data_for_explanation_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) | 
		(SI_Long)1048576L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	cached_explanation_qm = 
		get_lookup_slot_value_given_default(variable,
		Qg2_internal_cached_explanation,Nil);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable,Qframe_flags);
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)4L)) &  
		~(SI_Long)1048576L;
	ISVREF(variable,(SI_Long)4L) = FIX(svref_new_value);
	if (cached_explanation_qm) {
	    reclaim_cached_explanation(cached_explanation_qm);
	    set_non_savable_lookup_slot_value(variable,
		    Qg2_internal_cached_explanation,Nil);
	}
    }
    return VALUES_1(ISVREF(variable,(SI_Long)4L));
}

/* COMPILE-PARAMETER-FRAME-FLAGS-FOR-SLOT */
Object compile_parameter_frame_flags_for_slot varargs_1(int, n)
{
    Object parse_result, parameter, gensymed_symbol;
    Object cached_explanation_qm;
    SI_Long svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,328);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    parameter = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(FIRST(parse_result),Qforward_chain_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) | (SI_Long)2L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) &  ~(SI_Long)2L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (EQ(SECOND(parse_result),Qalways_forward_chain_if_possible_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) | (SI_Long)32L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) &  ~(SI_Long)32L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(parameter,Qframe_flags);
    svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) &  ~(SI_Long)8L;
    ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(parameter,Qframe_flags);
    svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) | (SI_Long)16L;
    ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(parameter,Qframe_flags);
    svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) | (SI_Long)32768L;
    ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    if (EQ(FOURTH(parse_result),Qcache_data_for_explanation_flag)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) | 
		(SI_Long)1048576L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	cached_explanation_qm = 
		get_lookup_slot_value_given_default(parameter,
		Qg2_internal_cached_explanation,Nil);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parameter,Qframe_flags);
	svref_new_value = IFIX(ISVREF(parameter,(SI_Long)4L)) &  
		~(SI_Long)1048576L;
	ISVREF(parameter,(SI_Long)4L) = FIX(svref_new_value);
	if (cached_explanation_qm) {
	    reclaim_cached_explanation(cached_explanation_qm);
	    set_non_savable_lookup_slot_value(parameter,
		    Qg2_internal_cached_explanation,Nil);
	}
    }
    return VALUES_1(ISVREF(parameter,(SI_Long)4L));
}

static Object list_constant_64;    /* # */

static Object list_constant_65;    /* # */

/* PARAMETER-FRAME-FLAGS-EVALUATION-SETTER */
Object parameter_frame_flags_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object forward_chaining_phrase, for_same_value_phrase, explanation_phrase;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,329);
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
			  list_constant_64))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_65,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_parameter_frame_flags_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qforward_chain,Nil);
    forward_chaining_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qforward_chain,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qforward_chain,Nil)),Truth) ? Qforward_chain_flag : 
	    phrase_list_4(Qdo,Qnot,Qforward,Qchain);
    temp_1 = estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil);
    for_same_value_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil)),Qtruth_value) && 
	    EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,Nil)),Truth) ? 
	    Qalways_forward_chain_if_possible_flag : 
	    Qdont_always_forward_chain_if_possible_flag;
    temp_1 = estructure_slot(gensymed_symbol,Qexplanation_data,Nil);
    explanation_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qexplanation_data,
	    Nil)),Qtruth_value) && 
	    EQ(M_CAR(estructure_slot(gensymed_symbol,Qexplanation_data,
	    Nil)),Truth) ? Qcache_data_for_explanation_flag : Nil;
    result = phrase_list_4(forward_chaining_phrase,for_same_value_phrase,
	    Qpassive_flag,explanation_phrase);
  end_parameter_frame_flags_evaluation_setter:
    return result;
}

/* PARAMETER-FRAME-FLAGS-EVALUATION-GETTER */
Object parameter_frame_flags_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(199,330);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qforward_chain,
	    (SI_Long)0L != (IFIX(slot_value) & (SI_Long)2L) ? 
	    Evaluation_true_value : Evaluation_false_value);
    set_evaluation_structure_slot(gensymed_symbol,
	    Qforward_chain_even_for_same_value,(SI_Long)0L != 
	    (IFIX(slot_value) & (SI_Long)32L) ? Evaluation_true_value : 
	    Evaluation_false_value);
    if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)1048576L))
	set_evaluation_structure_slot(gensymed_symbol,Qexplanation_data,T ?
		 Evaluation_true_value : Evaluation_false_value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

/* SET-APPROPRIATE-INSTANCE-FRAME-FLAGS-FOR-UPDATE-SLOT-DESCRIPTION */
Object set_appropriate_instance_frame_flags_for_update_slot_description(class_1,
	    unchanged_slot_init_form,new_slot_init_form,
	    unchanged_class_level_slot_description)
    Object class_1, unchanged_slot_init_form, new_slot_init_form;
    Object unchanged_class_level_slot_description;
{
    Object ab_loopvar_, instance, old_slot_value, vector_slot_index_qm;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm, class_description, cached_explanation_qm;
    SI_Long max_i, i, ab_loop_bind_, svref_new_value;

    x_note_fn_call(199,331);
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    old_slot_value = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    vector_slot_index_qm = ISVREF(unchanged_class_level_slot_description,
	    (SI_Long)7L);
    if (vector_slot_index_qm)
	old_slot_value = ISVREF(instance,IFIX(vector_slot_index_qm));
    else {
	user_vector_slot_index_qm = 
		ISVREF(unchanged_class_level_slot_description,(SI_Long)8L);
	if (user_vector_slot_index_qm)
	    old_slot_value = ISVREF(ISVREF(instance,(SI_Long)0L),
		    IFIX(user_vector_slot_index_qm));
	else {
	    slot_name = ISVREF(unchanged_class_level_slot_description,
		    (SI_Long)1L);
	    lookup_structure_qm = ISVREF(instance,(SI_Long)0L);
	    if (lookup_structure_qm) {
		max_i = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		max_i = max_i - (SI_Long)1L;
		i = IFIX(ISVREF(ISVREF(instance,(SI_Long)1L),(SI_Long)15L));
		ab_loop_bind_ = max_i;
	      next_loop_1:
		if (i >= ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
		    slot_index_qm = FIX(i + (SI_Long)1L);
		    goto end_1;
		}
		i = i + (SI_Long)2L;
		goto next_loop_1;
	      end_loop_1:
		slot_index_qm = Qnil;
	      end_1:;
		old_slot_value = slot_index_qm ? 
			ISVREF(lookup_structure_qm,IFIX(slot_index_qm)) : 
			ISVREF(unchanged_class_level_slot_description,
			(SI_Long)6L);
	    }
	    else
		old_slot_value = 
			ISVREF(unchanged_class_level_slot_description,
			(SI_Long)6L);
	}
    }
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (memq_function(Qvariable,ISVREF(class_description,(SI_Long)2L))) {
	if (EQ((SI_Long)0L != (IFIX(unchanged_slot_init_form) & 
		(SI_Long)16L) ? T : Nil,(SI_Long)0L != 
		(IFIX(ISVREF(instance,(SI_Long)4L)) & (SI_Long)16L) ? T : 
		Nil) && EQ((SI_Long)0L != (IFIX(unchanged_slot_init_form) 
		& (SI_Long)32768L) ? T : Nil,(SI_Long)0L != 
		(IFIX(ISVREF(instance,(SI_Long)4L)) & (SI_Long)32768L) ? T 
		: Nil) && EQ((SI_Long)0L != 
		(IFIX(unchanged_slot_init_form) & (SI_Long)8L) ? T : Nil,
		(SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
		(SI_Long)8L) ? T : Nil) && EQ((SI_Long)0L != 
		(IFIX(unchanged_slot_init_form) & (SI_Long)2L) ? T : Nil,
		(SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
		(SI_Long)2L) ? T : Nil) && EQ((SI_Long)0L != 
		(IFIX(unchanged_slot_init_form) & (SI_Long)32L) ? T : Nil,
		(SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
		(SI_Long)32L) ? T : Nil) && EQ((SI_Long)0L != 
		(IFIX(unchanged_slot_init_form) & (SI_Long)1048576L) ? T : 
		Nil,(SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
		(SI_Long)1048576L) ? T : Nil)) {
	    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)2L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)2L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
			~(SI_Long)2L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)32L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)32L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
			~(SI_Long)32L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		    ~(SI_Long)16L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		    ~(SI_Long)32768L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		    ~(SI_Long)8L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)16L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)16L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)32768L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)32768L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)32768L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)8L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(instance,Qframe_flags);
		svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
			(SI_Long)8L;
		ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	    }
	}
    }
    else if (EQ((SI_Long)0L != (IFIX(unchanged_slot_init_form) & 
	    (SI_Long)2L) ? T : Nil,(SI_Long)0L != (IFIX(ISVREF(instance,
	    (SI_Long)4L)) & (SI_Long)2L) ? T : Nil)) {
	if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)2L)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | (SI_Long)2L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	}
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		    ~(SI_Long)2L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	}
	if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)32L)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
		    (SI_Long)32L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	}
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(instance,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		    ~(SI_Long)32L;
	    ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(instance,Qframe_flags);
	svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  ~(SI_Long)8L;
	ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(instance,Qframe_flags);
	svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | (SI_Long)16L;
	ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(instance,Qframe_flags);
	svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | (SI_Long)32768L;
	ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
    }
    if ((SI_Long)0L != (IFIX(new_slot_init_form) & (SI_Long)1048576L)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(instance,Qframe_flags);
	svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) | 
		(SI_Long)1048576L;
	ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	cached_explanation_qm = 
		get_lookup_slot_value_given_default(instance,
		Qg2_internal_cached_explanation,Nil);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(instance,Qframe_flags);
	svref_new_value = IFIX(ISVREF(instance,(SI_Long)4L)) &  
		~(SI_Long)1048576L;
	ISVREF(instance,(SI_Long)4L) = FIX(svref_new_value);
	if (cached_explanation_qm) {
	    reclaim_cached_explanation(cached_explanation_qm);
	    set_non_savable_lookup_slot_value(instance,
		    Qg2_internal_cached_explanation,Nil);
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_41;  /* "do forward chain even for same value, " */

static Object string_constant_42;  /* "do forward chain, " */

static Object string_constant_43;  /* "do not forward chain, " */

static Object string_constant_44;  /* "do not seek data" */

static Object string_constant_45;  /* "do not backward chain" */

static Object string_constant_46;  /* "depth first backward chain" */

static Object string_constant_47;  /* "breadth first backward chain" */

static Object string_constant_48;  /* ", cache data for explanation" */

static Object string_constant_49;  /* ", do not cache data for explanation" */

/* WRITE-VARIABLE-FRAME-FLAGS-FROM-SLOT */
Object write_variable_frame_flags_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(199,332);
    twrite((SI_Long)0L != (IFIX(value) & (SI_Long)2L) ? ((SI_Long)0L != 
	    (IFIX(value) & (SI_Long)32L) ? string_constant_41 : 
	    string_constant_42) : string_constant_43);
    if ((SI_Long)0L != (IFIX(value) & (SI_Long)16L))
	temp = string_constant_44;
    else if ((SI_Long)0L != (IFIX(value) & (SI_Long)32768L))
	temp = string_constant_45;
    else if ((SI_Long)0L != (IFIX(value) & (SI_Long)8L))
	temp = string_constant_46;
    else
	temp = string_constant_47;
    twrite(temp);
    if (explanation_related_features_enabled_func_qm() || (SI_Long)0L != 
	    (IFIX(value) & (SI_Long)1048576L))
	return twrite((SI_Long)0L != (IFIX(value) & (SI_Long)1048576L) ? 
		string_constant_48 : string_constant_49);
    else
	return VALUES_1(Nil);
}

static Object string_constant_50;  /* "do forward chain even for same value" */

static Object string_constant_51;  /* "do forward chain" */

static Object string_constant_52;  /* "do not forward chain" */

/* WRITE-PARAMETER-FRAME-FLAGS-FROM-SLOT */
Object write_parameter_frame_flags_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(199,333);
    twrite((SI_Long)0L != IFIX(logand(value,Forward_chain_flag)) ? 
	    ((SI_Long)0L != (IFIX(value) & (SI_Long)32L) ? 
	    string_constant_50 : string_constant_51) : string_constant_52);
    if (explanation_related_features_enabled_func_qm() || (SI_Long)0L != 
	    (IFIX(value) & (SI_Long)1048576L))
	return twrite((SI_Long)0L != (IFIX(value) & (SI_Long)1048576L) ? 
		string_constant_48 : string_constant_49);
    else
	return VALUES_1(Nil);
}

static Object string_constant_53;  /* "Time increment is too small;  must be at least ~f seconds" */

/* COMPILE-SIMULATION-TIME-INCREMENT?-FOR-SLOT */
Object compile_simulation_time_increment_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,334);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(parse_result,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(parse_result) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == 
		    (SI_Long)1L)
		temp = aref1(parse_result,FIX((SI_Long)0L));
	    else
		temp = parse_result;
	    temp_1 = NUM_LT(temp,Minimum_simulation_time_increment);
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (temp_1) {
	    temp_2 = Bad_phrase;
	    temp = tformat_text_string(2,string_constant_53,
		    Minimum_simulation_time_increment);
	    return VALUES_2(temp_2,temp);
	}
	else
	    return VALUES_1(parse_result);
    }
}

static Object list_constant_66;    /* # */

/* SIMULATION-TIME-INCREMENT?-EVALUATION-SETTER */
Object simulation_time_increment_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,335);
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
			  list_constant_66))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_61,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_simulation_time_increment_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L) {
	    value = evaluation_value_value(evaluation_value);
	    if (FIXNUMP(value))
		result = VALUES_1(value);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
		new_long = allocate_managed_long_box();
		aref_new_value = INTEGER_TO_INT64(value);
		set_aref1(new_long,FIX((SI_Long)0L),
			INT64_TO_INTEGER(aref_new_value));
		result = note_use_of_managed_long_in_phrase(new_long);
	    }
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    M_CDR(amf_available_array_cons_qm) = Nil;
		    amf_result = amf_array;
		}
		else {
		    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			    FIX((SI_Long)1L));
		    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		    amf_result = generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
		result = note_use_of_managed_float_in_phrase(new_float);
	    }
	}
	else
	    result = VALUES_1(evaluation_value);
    }
    else
	result = VALUES_1(Qnone);
  end_simulation_time_increment_qm_evaluation_setter:
    return result;
}

/* SIMULATION-TIME-INCREMENT?-EVALUATION-GETTER */
Object simulation_time_increment_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,336);
    GENSYM_RETURN_ONE(slot_value ? 
	    (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L ? 
	    copy_managed_float(slot_value) : slot_value) : Nil);
    return VALUES_1(Nil);
}

static Object list_constant_67;    /* # */

/* SIMULATION-TIME-INCREMENT-EVALUATION-SETTER */
Object simulation_time_increment_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value, new_long;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_int64 aref_new_value;
    double aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,337);
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
			  list_constant_67))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qnumber,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_simulation_time_increment_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == (SI_Long)1L) {
	value = evaluation_value_value(evaluation_value);
	if (FIXNUMP(value))
	    result = VALUES_1(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    result = note_use_of_managed_long_in_phrase(new_long);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	    result = note_use_of_managed_float_in_phrase(new_float);
	}
    }
    else
	result = VALUES_1(evaluation_value);
  end_simulation_time_increment_evaluation_setter:
    return result;
}

/* SIMULATION-TIME-INCREMENT-EVALUATION-GETTER */
Object simulation_time_increment_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,338);
    GENSYM_RETURN_ONE(INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == 
	    (SI_Long)1L ? copy_managed_float(slot_value) : slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-SIMULATION-TIME-INCREMENT-FOR-SLOT */
Object compile_simulation_time_increment_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,339);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(parse_result,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(parse_result) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == (SI_Long)1L)
	    temp = aref1(parse_result,FIX((SI_Long)0L));
	else
	    temp = parse_result;
	temp_1 = NUM_LT(temp,Minimum_simulation_time_increment);
    }
    POP_LOCAL_ALLOCATION(0,0);
    if (temp_1) {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_53,
		Minimum_simulation_time_increment);
	return VALUES_2(temp_2,temp);
    }
    else
	return VALUES_1(parse_result);
}

static Object string_constant_54;  /* "~f" */

/* WRITE-SIMULATION-TIME-INCREMENT?-FROM-SLOT */
Object write_simulation_time_increment_qm_from_slot(simulation_time_increment_qm,
	    gensymed_symbol)
    Object simulation_time_increment_qm, gensymed_symbol;
{
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,340);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(simulation_time_increment_qm) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simulation_time_increment_qm)) 
	    == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    tformat(2,string_constant_54,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(simulation_time_increment_qm,
		    (SI_Long)0L)));
	POP_LOCAL_ALLOCATION(0,0);
	return print_second_or_seconds(simulation_time_increment_qm);
    }
    else if (simulation_time_increment_qm) {
	twrite(simulation_time_increment_qm);
	return print_second_or_seconds(simulation_time_increment_qm);
    }
    else
	return twrite(string_constant_40);
}

/* WRITE-SIMULATION-TIME-INCREMENT-FROM-SLOT */
Object write_simulation_time_increment_from_slot(simulation_time_increment,
	    gensymed_symbol)
    Object simulation_time_increment, gensymed_symbol;
{
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(199,341);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(simulation_time_increment) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simulation_time_increment)) == 
	    (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    tformat(2,string_constant_54,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(simulation_time_increment,
		    (SI_Long)0L)));
	POP_LOCAL_ALLOCATION(0,0);
	return print_second_or_seconds(simulation_time_increment);
    }
    else {
	twrite(simulation_time_increment);
	return print_second_or_seconds(simulation_time_increment);
    }
}

static Object string_constant_55;  /* " second" */

static Object string_constant_56;  /* " seconds" */

/* PRINT-SECOND-OR-SECONDS */
Object print_second_or_seconds(time_increment)
    Object time_increment;
{
    Object temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,342);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_increment) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_increment)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_increment,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(time_increment) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_increment)) == (SI_Long)1L)
	    temp = aref1(time_increment,FIX((SI_Long)0L));
	else
	    temp = time_increment;
	temp_1 = FIX((SI_Long)1L);
	if (NUM_EQ(temp,temp_1))
	    result = twrite(string_constant_55);
	else
	    result = twrite(string_constant_56);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qeuler;              /* euler */

static Object string_constant_57;  /* "Euler" */

static Object string_constant_58;  /* "Fourth-order Runge-Kutta" */

/* WRITE-INTEGRATION-ALGORITHM-SPECIFICATION-FROM-SLOT */
Object write_integration_algorithm_specification_from_slot(integration_algorithm_specification,
	    gensymed_symbol)
    Object integration_algorithm_specification, gensymed_symbol;
{
    x_note_fn_call(199,343);
    if (EQ(integration_algorithm_specification,Qeuler))
	return twrite(string_constant_57);
    else
	return twrite(string_constant_58);
}

static Object list_constant_68;    /* # */

static Object list_constant_69;    /* # */

static Object Qrunga_kutta_4;      /* runga-kutta-4 */

static Object Qrk4;                /* rk4 */

/* INTEGRATION-ALGORITHM-SPECIFICATION-EVALUATION-SETTER */
Object integration_algorithm_specification_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,344);
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
			  list_constant_68))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_69,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_integration_algorithm_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qeuler))
	result = VALUES_1(Qeuler);
    else if (EQ(evaluation_value,Qrunga_kutta_4))
	result = VALUES_1(Qrk4);
    else
	result = VALUES_1(Qnil);
  end_integration_algorithm_specification_evaluation_setter:
    return result;
}

/* INTEGRATION-ALGORITHM-SPECIFICATION-EVALUATION-GETTER */
Object integration_algorithm_specification_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(199,345);
    if (EQ(slot_value,Qeuler))
	temp = Qeuler;
    else if (EQ(slot_value,Qrk4))
	temp = Qrunga_kutta_4;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qsynchronously;      /* synchronously */

static Object string_constant_59;  /* "run synchronously" */

static Object string_constant_60;  /* "run as fast as possible" */

static Object string_constant_61;  /* ", without incrementing simulation time" */

static Object string_constant_62;  /* ", without waiting for simulation procedure or gspan external simulation cycle to finish" */

/* WRITE-SIMULATION-CONTROL-SPECIFICATION-FROM-SLOT */
Object write_simulation_control_specification_from_slot(simulation_control_specification,
	    gensymed_symbol)
    Object simulation_control_specification, gensymed_symbol;
{
    x_note_fn_call(199,346);
    if (EQ(CAR(simulation_control_specification),Qsynchronously))
	twrite(string_constant_59);
    else
	twrite(string_constant_60);
    if (SECOND(simulation_control_specification))
	twrite(string_constant_61);
    if (THIRD(simulation_control_specification))
	return twrite(string_constant_62);
    else
	return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

/* COMPILE-SIMULATION-CONTROL-SPECIFICATION-FOR-SLOT */
Object compile_simulation_control_specification_for_slot varargs_1(int, n)
{
    Object parse_result, model_definition, gensymed_symbol;
    Object sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,347);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    model_definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    sub_class_bit_vector = ISVREF(ISVREF(model_definition,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
    if (temp);
    else
	temp =  !TRUEP(model_running_or_paused_qm(model_definition));
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = copy_constant_wide_string_given_length(array_constant_5,
		FIX((SI_Long)88L));
	return VALUES_2(temp_1,temp_2);
    }
}

static Object list_constant_70;    /* # */

static Object list_constant_71;    /* # */

static Object Qsynchronization_mode;  /* synchronization-mode */

static Object Qrun_synchronously;  /* run-synchronously */

static Object Qrun_as_fast_as_possible;  /* run-as-fast-as-possible */

static Object Qas_fast_as_possible;  /* as-fast-as-possible */

static Object Qwithout_incrementing_simulation_time;  /* without-incrementing-simulation-time */

static Object Qwithout_waiting_for_external_simulation_cycle;  /* without-waiting-for-external-simulation-cycle */

/* SIMULATION-CONTROL-SPECIFICATION-EVALUATION-SETTER */
Object simulation_control_specification_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, value;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,348);
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
			  list_constant_70))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_71,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_simulation_control_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = estructure_slot(evaluation_value,Qsynchronization_mode,Nil);
    if (EQ(temp_1,Qrun_synchronously))
	temp = Qsynchronously;
    else if (EQ(temp_1,Qrun_as_fast_as_possible))
	temp = Qas_fast_as_possible;
    else
	temp = Qnil;
    value = estructure_slot(evaluation_value,
	    Qwithout_incrementing_simulation_time,Nil);
    temp_1 = CONSP(value) && EQ(M_CDR(value),Qtruth_value) ? (CONSP(value) 
	    && EQ(M_CDR(value),Qtruth_value) ? (EQ(M_CAR(value),Truth) ? T 
	    : Nil) : Qnil) : Qnil;
    value = estructure_slot(evaluation_value,
	    Qwithout_waiting_for_external_simulation_cycle,Nil);
    result = phrase_list_3(temp,temp_1,CONSP(value) && EQ(M_CDR(value),
	    Qtruth_value) ? (CONSP(value) && EQ(M_CDR(value),Qtruth_value) 
	    ? (EQ(M_CAR(value),Truth) ? T : Nil) : Qnil) : Qnil);
  end_simulation_control_specification_evaluation_setter:
    return result;
}

/* SIMULATION-CONTROL-SPECIFICATION-EVALUATION-GETTER */
Object simulation_control_specification_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(199,349);
    temp = eval_list_2(Qsynchronization_mode,EQ(CAR(slot_value),
	    Qsynchronously) ? Qrun_synchronously : Qrun_as_fast_as_possible);
    GENSYM_RETURN_ONE(allocate_evaluation_structure(nconc2(temp,
	    nconc2(SECOND(slot_value) ? 
	    eval_list_2(Qwithout_incrementing_simulation_time,T ? 
	    Evaluation_true_value : Evaluation_false_value) : Nil,
	    THIRD(slot_value) ? 
	    eval_list_2(Qwithout_waiting_for_external_simulation_cycle,T ? 
	    Evaluation_true_value : Evaluation_false_value) : Nil))));
    return VALUES_1(Nil);
}

static Object array_constant_6;    /* # */

/* COMPILE-POSITIVE-INTEGER-FOR-SLOT */
Object compile_positive_integer_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,350);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (IFIX(parse_result) > (SI_Long)0L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_6,
		FIX((SI_Long)38L));
	return VALUES_2(temp,temp_1);
    }
}

/* WRITE-POSITIVE-INTEGER-FROM-SLOT */
Object write_positive_integer_from_slot(n_1,gensymed_symbol)
    Object n_1, gensymed_symbol;
{
    x_note_fn_call(199,351);
    return twrite(n_1);
}

/* COMPILE-POSITIVE-INTEGER?-FOR-SLOT */
Object compile_positive_integer_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,352);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (IFIX(parse_result) > (SI_Long)0L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_6,
		FIX((SI_Long)38L));
	return VALUES_2(temp,temp_1);
    }
}

/* COMPILE-READ-ONLY-POSITIVE-INTEGER?-FOR-SLOT */
Object compile_read_only_positive_integer_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,353);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (IFIX(parse_result) > (SI_Long)0L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_6,
		FIX((SI_Long)38L));
	return VALUES_2(temp,temp_1);
    }
}

/* WRITE-POSITIVE-INTEGER?-FROM-SLOT */
Object write_positive_integer_qm_from_slot(n_1,gensymed_symbol)
    Object n_1, gensymed_symbol;
{
    x_note_fn_call(199,354);
    if ( !TRUEP(n_1))
	return twrite(Qnone);
    else
	return twrite(n_1);
}

static Object array_constant_7;    /* # */

/* COMPILE-PRIORITY-FOR-SLOT */
Object compile_priority_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,355);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ((SI_Long)1L <= IFIX(parse_result) && IFIX(parse_result) <= 
	    (SI_Long)10L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_7,
		FIX((SI_Long)48L));
	return VALUES_2(temp,temp_1);
    }
}

/* WRITE-PRIORITY-FROM-SLOT */
Object write_priority_from_slot(n_1,gensymed_symbol)
    Object n_1, gensymed_symbol;
{
    x_note_fn_call(199,356);
    return twrite(n_1);
}

static Object list_constant_72;    /* # */

static Object list_constant_73;    /* # */

/* PRIORITY-EVALUATION-SETTER */
Object priority_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,357);
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
			  list_constant_72))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_73,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_priority_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_priority_evaluation_setter:
    return result;
}

/* PRIORITY-EVALUATION-GETTER */
Object priority_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(199,358);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object array_constant_8;    /* # */

/* COMPILE-NON-NEGATIVE-INTEGER-FOR-SLOT */
Object compile_non_negative_integer_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,359);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (IFIX(parse_result) >= (SI_Long)0L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_8,
		FIX((SI_Long)42L));
	return VALUES_2(temp,temp_1);
    }
}

/* WRITE-NON-NEGATIVE-INTEGER-FROM-SLOT */
Object write_non_negative_integer_from_slot(n_1,gensymed_symbol)
    Object n_1, gensymed_symbol;
{
    x_note_fn_call(199,360);
    return twrite(n_1);
}

static Object array_constant_9;    /* # */

/* COMPILE-NON-NEGATIVE-NUMBER-FOR-SLOT */
Object compile_non_negative_number_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp_1, temp_2;
    char temp;
    double arg, arg_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,361);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    temp = FIXNUMP(parse_result) ? IFIX(parse_result) >= (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(parse_result) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parse_result)) == (SI_Long)1L) {
	arg = DFLOAT_ISAREF_1(parse_result,(SI_Long)0L);
	arg_1 = 0.0;
	temp = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(parse_result);
    else {
	temp_1 = Bad_phrase;
	temp_2 = copy_constant_wide_string_given_length(array_constant_9,
		FIX((SI_Long)41L));
	return VALUES_2(temp_1,temp_2);
    }
}

/* WRITE-NON-NEGATIVE-NUMBER-FROM-SLOT */
Object write_non_negative_number_from_slot(number,gensymed_symbol)
    Object number, gensymed_symbol;
{
    x_note_fn_call(199,362);
    return print_constant(2,number,Qnumber);
}

static Object string_constant_63;  /* "This formula cannot be computed for this variable." */

/* COMPILE-INSTANCE-FORMULA-FOR-SLOT */
Object compile_instance_formula_for_slot varargs_1(int, n)
{
    Object parse_result, variable, gensymed_symbol;
    Object compiler_result_qm, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,363);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    compiler_result_qm = compile_instance_formula(parse_result,variable);
    if (EQ(compiler_result_qm,Bad_phrase)) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_63);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(compiler_result_qm);
}

static Object Qcell_array;         /* cell-array */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qg2_cell_array;      /* g2-cell-array */

static Object Qpart_stack;         /* part-stack */

static Object Qmark;               /* mark */

static Object Qempty_expression_cell;  /* empty-expression-cell */

/* COMPILE-INSTANCE-FORMULA */
Object compile_instance_formula(parse_result,variable)
    Object parse_result, variable;
{
    Object current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_style, current_block_of_dependent_frame;
    Object cell_array_qm, expression_cell_qm, expression_qm, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object temp_1, old_current_part_description, formula_type;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, stack_change_pop_store;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,364);
    current_computation_frame = variable;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    4);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      3);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		2);
	  current_block_of_dependent_frame = variable;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		  1);
	    cell_array_qm = get_lookup_slot_value_given_default(variable,
		    Qcell_array,Nil);
	    expression_cell_qm = cell_array_qm ? 
		    (FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),(SI_Long)0L + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)2L),(SI_Long)0L)) : Nil;
	    expression_qm = EQ(parse_result,Qnone) ? Nil : parse_result;
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(variable,(SI_Long)1L),Nil);
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_1 = nconc2(stack_change_list_2(variable,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_1) = variable;
		M_CDR(gensymed_symbol_1) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    temp = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    0);
	      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
		      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = variable;
		  gensymed_symbol_2 = Nil;
		  gensymed_symbol_3 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
		  svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) | 
			  (SI_Long)16777216L;
		  ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
	      }
	      if (expression_qm) {
		  if ( !(cell_array_qm && expression_cell_qm)) {
		      cell_array_qm = make_frame(Qg2_cell_array);
		      change_slot_value(3,variable,Qcell_array,cell_array_qm);
		      make_empty_expression_cell(cell_array_qm);
		      expression_cell_qm = 
			      FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,
			      (SI_Long)3L),(SI_Long)1L),
			      Maximum_in_place_array_size) ? 
			      ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
			      (SI_Long)0L + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(ISVREF(cell_array_qm,
			      (SI_Long)3L),(SI_Long)2L),(SI_Long)0L);
		      temp_1 = ISVREF(variable,(SI_Long)8L);
		      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(variable,(SI_Long)5L)) & 
			      (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
			      && (SI_Long)0L != (IFIX(ISVREF(variable,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != (IFIX(ISVREF(variable,
			      (SI_Long)4L)) & (SI_Long)8192L))))
			  activate_g2_cell_array(cell_array_qm);
		  }
		  old_current_part_description = Current_part_description;
		  Current_part_description = 
			  get_default_computation_style_of_class();
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      new_cons = ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  temp = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_part_stack_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
			  }
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_part_stack_cons_pool();
		      temp = Current_part_description;
		      M_CAR(gensymed_symbol) = temp;
		      temp = Stack_of_current_part_descriptions;
		      M_CDR(gensymed_symbol) = temp;
		      inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		      Stack_of_current_part_descriptions = gensymed_symbol;
		  }
		  new_cons = ISVREF(Available_part_stack_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp = Available_part_stack_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_part_stack_cons_pool();
		  M_CAR(gensymed_symbol) = Qmark;
		  temp = Part_feature_recall_stack;
		  M_CDR(gensymed_symbol) = temp;
		  inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		  Part_feature_recall_stack = gensymed_symbol;
		  enter_part_description(Current_part_description);
		  formula_type = 
			  type_specification_held_in_variable_or_parameter(variable);
		  register_expression_cell_during_compilation(5,
			  cell_array_qm,FIX((SI_Long)0L),T,expression_qm,
			  formula_type);
		  if ( !EQ(ISVREF(expression_cell_qm,(SI_Long)2L),
			  Qempty_expression_cell)) {
		      update_frame_status(variable,Nil,Nil);
		      temp_1 = T;
		  }
		  else
		      temp_1 = Bad_phrase;
		  part_feature_index = Nil;
		  exit_feature_handler = Nil;
		next_loop:
		  part_stack_pop_store = Nil;
		  cons_1 = Part_feature_recall_stack;
		  if (cons_1) {
		      part_stack_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qpart_stack);
		      if (ISVREF(Available_part_stack_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = 
				  ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = cons_1;
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
		      }
		      else {
			  temp = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Part_feature_recall_stack = next_cons;
		  part_feature_index = part_stack_pop_store;
		  if (EQ(part_feature_index,Qmark))
		      goto end_loop;
		  exit_feature_handler = ISVREF(Part_feature_exit_methods,
			  IFIX(part_feature_index));
		  inline_funcall_0(exit_feature_handler);
		  goto next_loop;
		end_loop:;
		  Current_part_description = old_current_part_description;
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      part_stack_pop_store = Nil;
		      cons_1 = Stack_of_current_part_descriptions;
		      if (cons_1) {
			  part_stack_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qpart_stack);
			  if (ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_part_stack_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp) = cons_1;
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  else {
			      temp = Available_part_stack_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      Stack_of_current_part_descriptions = next_cons;
		  }
		  result_1 = temp_1;
	      }
	      else {
		  if (cell_array_qm) {
		      temp_1 = ISVREF(variable,(SI_Long)8L);
		      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(variable,(SI_Long)5L)) & 
			      (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
			      && (SI_Long)0L != (IFIX(ISVREF(variable,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != (IFIX(ISVREF(variable,
			      (SI_Long)4L)) & (SI_Long)8192L))))
			  deactivate_g2_cell_array(cell_array_qm);
		      change_slot_value(3,variable,Qcell_array,Nil);
		  }
		  remove_compiler_error_and_warning_frame_notes();
		  update_frame_status(variable,Nil,Nil);
		  result_1 = Nil;
	      }
	      if ( !TRUEP(current_flag_state_qm)) {
		  svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) & 
			   ~(SI_Long)16777216L;
		  ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = variable;
		  gensymed_symbol_2 = T;
		  gensymed_symbol_3 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
	      }
	      temp_2 = 
		      TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp_2);
	      else if (M_CDR(Stack_of_slot_value_changes)) {
		  frame_and_slot_or_atom = Nil;
		  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		  ab_loop_it_ = Nil;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ATOM(frame_and_slot_or_atom))
		      goto end_loop_1;
		  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp_2);
		  else {
		      temp_1 = M_CDR(frame_and_slot_or_atom);
		      temp_2 = CONSP(temp_1) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp_2 ? (EQ(variable,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp_2 = TRUEP(ab_loop_it_);
		      goto end_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp_2 = TRUEP(Qnil);
		end_1:;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ( !temp_2)
		  update_all_representations_of_slot(variable,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(variable);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = 
			      ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  else {
		      temp = Available_stack_change_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		      temp = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_stack_change_tree_1(stack_change_pop_store);
	      if (Stack_of_slot_value_changes) {
		  temp_1 = M_CAR(Stack_of_slot_value_changes);
		  temp_2 = ATOM(temp_1);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	    result = VALUES_1(result_1);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPILE-LOGICAL-INSTANCE-FORMULA-FOR-SLOT */
Object compile_logical_instance_formula_for_slot varargs_1(int, n)
{
    Object parse_result, variable, gensymed_symbol;
    Object compiler_result_qm, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(199,365);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    compiler_result_qm = compile_instance_formula(parse_result,variable);
    if (EQ(compiler_result_qm,Bad_phrase)) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_63);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(compiler_result_qm);
}

/* TRANSLATE-GENERIC-FORMULA */
Object translate_generic_formula(phrase)
    Object phrase;
{
    Object left_side_of_formula, rest_of_formula;

    x_note_fn_call(199,366);
    left_side_of_formula = CAR(phrase);
    rest_of_formula = CDR(phrase);
    return phrase_cons(FIRST(left_side_of_formula),
	    phrase_cons(SECOND(left_side_of_formula),rest_of_formula));
}

/* IS-GENERIC-FORUMULA-EXECUTABLE? */
Object is_generic_forumula_executable_qm(generic_formula)
    Object generic_formula;
{
    Object cell_array_qm, cell_array_index, expression_cell_qm;

    x_note_fn_call(199,367);
    cell_array_qm = get_lookup_slot_value_given_default(generic_formula,
	    Qcell_array,Nil);
    cell_array_index = 
	    expression_cell_element_for_generic_formula(generic_formula);
    expression_cell_qm = cell_array_qm ? 
	    (FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(cell_array_index,Managed_array_index_offset))) 
	    : ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
	    (IFIX(cell_array_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(cell_array_index) & (SI_Long)1023L)) : Nil;
    if (expression_cell_qm)
	return VALUES_1( !EQ(ISVREF(expression_cell_qm,(SI_Long)2L),
		Qempty_expression_cell) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qg2_lambda;          /* g2-lambda */

static Object list_constant_74;    /* # */

/* COMPILE-GENERIC-FORMULA-FOR-SLOT */
Object compile_generic_formula_for_slot varargs_1(int, n)
{
    Object parse_result, generic_formula, gensymed_symbol;
    Object current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_style, current_block_of_dependent_frame;
    Object cell_array, cell_array_index, expression_cell, attribute;
    Object simple_attribute_role, attribute_class_qualifier, domain;
    Object class_name, raw_body, argument_and_type_list, temp, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object old_current_part_description, part_feature_index;
    Object exit_feature_handler, part_stack_pop_store, cons_1, next_cons;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(199,368);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    generic_formula = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    current_computation_frame = generic_formula;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    4);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      3);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		2);
	  current_block_of_dependent_frame = generic_formula;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		  1);
	    cell_array = 
		    get_lookup_slot_value_given_default(generic_formula,
		    Qcell_array,Nil);
	    cell_array_index = 
		    expression_cell_element_for_generic_formula(generic_formula);
	    expression_cell = cell_array ? 
		    (FIXNUM_LE(ISVREF(ISVREF(cell_array,(SI_Long)3L),
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(ISVREF(cell_array,(SI_Long)3L),
		    IFIX(FIXNUM_ADD(cell_array_index,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(ISVREF(cell_array,(SI_Long)3L),
		    (IFIX(cell_array_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(cell_array_index) & (SI_Long)1023L)) 
		    : Nil;
	    attribute = FIRST(parse_result);
	    simple_attribute_role = simple_role_of_role(attribute);
	    attribute_class_qualifier = CONSP(simple_attribute_role) ? 
		    M_CAR(M_CDR(simple_attribute_role)) : Nil;
	    domain = SECOND(parse_result);
	    class_name = atomic_naming_element_of_role(domain);
	    raw_body = THIRD(parse_result);
	    argument_and_type_list = phrase_cons(phrase_list_2(class_name,
		    make_class_type_specification(class_name)),Nil);
	    if ( !(cell_array && expression_cell)) {
		cell_array = make_frame(Qg2_cell_array);
		change_slot_value(3,generic_formula,Qcell_array,cell_array);
		make_empty_expression_cell(cell_array);
		expression_cell = FIXNUM_LE(ISVREF(ISVREF(cell_array,
			(SI_Long)3L),(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(ISVREF(cell_array,(SI_Long)3L),
			IFIX(FIXNUM_ADD(cell_array_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(ISVREF(cell_array,(SI_Long)3L),
			(IFIX(cell_array_index) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(cell_array_index) & (SI_Long)1023L);
		temp = ISVREF(generic_formula,(SI_Long)8L);
		if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			(IFIX(ISVREF(generic_formula,(SI_Long)5L)) & 
			(SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) && 
			(SI_Long)0L != (IFIX(ISVREF(generic_formula,
			(SI_Long)4L)) & (SI_Long)16777216L) &&  
			!((SI_Long)0L != (IFIX(ISVREF(generic_formula,
			(SI_Long)4L)) & (SI_Long)8192L))))
		    activate_g2_cell_array(cell_array);
	    }
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(generic_formula,(SI_Long)1L),Nil);
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_1 = 
			nconc2(stack_change_list_2(generic_formula,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_1) = generic_formula;
		M_CDR(gensymed_symbol_1) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    temp_1 = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp_1;
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    0);
	      current_flag_state_qm = (SI_Long)0L != 
		      (IFIX(ISVREF(generic_formula,(SI_Long)5L)) & 
		      (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(generic_formula,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = generic_formula;
		  gensymed_symbol_2 = Nil;
		  gensymed_symbol_3 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
		  svref_new_value_1 = IFIX(ISVREF(generic_formula,
			  (SI_Long)5L)) | (SI_Long)16777216L;
		  ISVREF(generic_formula,(SI_Long)5L) = FIX(svref_new_value_1);
	      }
	      if (raw_body) {
		  old_current_part_description = Current_part_description;
		  Current_part_description = 
			  get_default_computation_style_of_class();
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      new_cons = ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  temp_1 = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp_1,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_part_stack_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = Nil;
			  }
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_part_stack_cons_pool();
		      temp_1 = Current_part_description;
		      M_CAR(gensymed_symbol) = temp_1;
		      temp_1 = Stack_of_current_part_descriptions;
		      M_CDR(gensymed_symbol) = temp_1;
		      inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		      Stack_of_current_part_descriptions = gensymed_symbol;
		  }
		  new_cons = ISVREF(Available_part_stack_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp_1 = Available_part_stack_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp_1,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_part_stack_cons_pool();
		  M_CAR(gensymed_symbol) = Qmark;
		  temp_1 = Part_feature_recall_stack;
		  M_CDR(gensymed_symbol) = temp_1;
		  inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		  Part_feature_recall_stack = gensymed_symbol;
		  enter_part_description(Current_part_description);
		  register_expression_cell_during_compilation(7,cell_array,
			  cell_array_index,T,phrase_list_3(Qg2_lambda,
			  argument_and_type_list,raw_body),
			  list_constant_74,domain,attribute);
		  if ( !EQ(ISVREF(expression_cell,(SI_Long)2L),
			  Qempty_expression_cell) && 
			      attribute_class_qualifier) {
		      temp = CONSP(simple_attribute_role) ? 
			      M_CAR(M_CDR(M_CDR(simple_attribute_role))) : 
			      simple_attribute_role;
		      temp = phrase_list_3(temp,
			      atomic_naming_element_of_role(domain),
			      attribute_class_qualifier);
		  }
		  else if ( !EQ(ISVREF(expression_cell,(SI_Long)2L),
			  Qempty_expression_cell)) {
		      temp = CONSP(simple_attribute_role) ? 
			      M_CAR(M_CDR(M_CDR(simple_attribute_role))) : 
			      simple_attribute_role;
		      temp = phrase_list_2(temp,
			      atomic_naming_element_of_role(domain));
		  }
		  else {
		      update_frame_status(generic_formula,Qbad,Nil);
		      temp = Nil;
		  }
		  part_feature_index = Nil;
		  exit_feature_handler = Nil;
		next_loop:
		  part_stack_pop_store = Nil;
		  cons_1 = Part_feature_recall_stack;
		  if (cons_1) {
		      part_stack_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qpart_stack);
		      if (ISVREF(Available_part_stack_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_1 = 
				  ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = cons_1;
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      else {
			  temp_1 = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
			  temp_1 = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Part_feature_recall_stack = next_cons;
		  part_feature_index = part_stack_pop_store;
		  if (EQ(part_feature_index,Qmark))
		      goto end_loop;
		  exit_feature_handler = ISVREF(Part_feature_exit_methods,
			  IFIX(part_feature_index));
		  inline_funcall_0(exit_feature_handler);
		  goto next_loop;
		end_loop:;
		  Current_part_description = old_current_part_description;
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      part_stack_pop_store = Nil;
		      cons_1 = Stack_of_current_part_descriptions;
		      if (cons_1) {
			  part_stack_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qpart_stack);
			  if (ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_1 = 
				      ISVREF(Available_part_stack_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_1) = cons_1;
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			  }
			  else {
			      temp_1 = Available_part_stack_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			      temp_1 = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      Stack_of_current_part_descriptions = next_cons;
		  }
		  result_1 = temp;
	      }
	      else {
		  temp = ISVREF(generic_formula,(SI_Long)8L);
		  if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			  (IFIX(ISVREF(generic_formula,(SI_Long)5L)) & 
			  (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) && 
			  (SI_Long)0L != (IFIX(ISVREF(generic_formula,
			  (SI_Long)4L)) & (SI_Long)16777216L) &&  
			  !((SI_Long)0L != (IFIX(ISVREF(generic_formula,
			  (SI_Long)4L)) & (SI_Long)8192L))))
		      deactivate_g2_cell_array(cell_array);
		  change_slot_value(3,generic_formula,Qcell_array,Nil);
		  update_frame_status(generic_formula,Qbad,Nil);
		  result_1 = Nil;
	      }
	      if ( !TRUEP(current_flag_state_qm)) {
		  svref_new_value_1 = IFIX(ISVREF(generic_formula,
			  (SI_Long)5L)) &  ~(SI_Long)16777216L;
		  ISVREF(generic_formula,(SI_Long)5L) = FIX(svref_new_value_1);
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(generic_formula,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = generic_formula;
		  gensymed_symbol_2 = T;
		  gensymed_symbol_3 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
	      }
	      temp_2 = 
		      TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp_2);
	      else if (M_CDR(Stack_of_slot_value_changes)) {
		  frame_and_slot_or_atom = Nil;
		  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		  ab_loop_it_ = Nil;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ATOM(frame_and_slot_or_atom))
		      goto end_loop_1;
		  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp_2);
		  else {
		      temp = M_CDR(frame_and_slot_or_atom);
		      temp_2 = CONSP(temp) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp_2 ? (EQ(generic_formula,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp_2 = TRUEP(ab_loop_it_);
		      goto end_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp_2 = TRUEP(Qnil);
		end_1:;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ( !temp_2)
		  update_all_representations_of_slot(generic_formula,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(generic_formula);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = 
			      ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		  }
		  else {
		      temp_1 = Available_stack_change_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_stack_change_tree_1(stack_change_pop_store);
	      if (Stack_of_slot_value_changes) {
		  temp = M_CAR(Stack_of_slot_value_changes);
		  temp_2 = ATOM(temp);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	    result = VALUES_1(result_1);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TRANSLATE-GENERIC-SIMULATION-FORMULA */
Object translate_generic_simulation_formula(phrase)
    Object phrase;
{
    Object left_side_of_formula, rest_of_formula, temp;

    x_note_fn_call(199,369);
    left_side_of_formula = CAR(phrase);
    rest_of_formula = CDR(phrase);
    temp = get_first_role_of_left_side_designation(left_side_of_formula);
    temp = phrase_cons(temp,
	    phrase_cons(get_main_class_or_item_of_left_side_designation(left_side_of_formula),
	    rest_of_formula));
    return VALUES_1(nconc2(temp,
	    phrase_cons(copy_tree_using_phrase_conses(left_side_of_formula),
	    Nil)));
}

/* GET-FIRST-ROLE-OF-LEFT-SIDE-DESIGNATION */
Object get_first_role_of_left_side_designation(left_side_designation)
    Object left_side_designation;
{
    x_note_fn_call(199,370);
    if (CONSP(left_side_designation) && EQ(CAR(left_side_designation),Qthe))
	return VALUES_1(SECOND(left_side_designation));
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

/* GET-MAIN-CLASS-OR-ITEM-OF-LEFT-SIDE-DESIGNATION */
Object get_main_class_or_item_of_left_side_designation(left_side_designation)
    Object left_side_designation;
{
    Object current_designation;

    x_note_fn_call(199,371);
    current_designation = left_side_designation;
  next_loop:
    if (SYMBOLP(current_designation))
	return phrase_list_2(Qitem,current_designation);
    else if ( !TRUEP(THIRD(current_designation)))
	return VALUES_1(SECOND(current_designation));
    current_designation = THIRD(current_designation);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qgeneric_simulation_formula_byte_code_body;  /* generic-simulation-formula-byte-code-body */

static Object Qgeneric_simulation_initial_value_byte_code_body;  /* generic-simulation-initial-value-byte-code-body */

/* COMPILE-GENERIC-SIMULATION-FORMULA-FOR-SLOT */
Object compile_generic_simulation_formula_for_slot varargs_1(int, n)
{
    Object parse_result, generic_simulation_formula, gensymed_symbol;
    Object current_computation_frame, phrase_number, time_increment_qm, temp_1;
    Object temp_2, simulation_expression, initial_value_expression_qm;
    Object simulation_class_or_item, compiled_simulation_expression;
    Object compiled_initial_value_expression_qm;
    Object current_computation_component_particulars, byte_code_body;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(199,372);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    generic_simulation_formula = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    current_computation_frame = generic_simulation_formula;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  phrase_number = SIXTH(parse_result);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L 
		  && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		  (SI_Long)1L)
	      time_increment_qm = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == 
		  (SI_Long)1L)
	      time_increment_qm = aref1(phrase_number,FIX((SI_Long)0L));
	  else
	      time_increment_qm = phrase_number;
	  temp = time_increment_qm ? NUM_LT(time_increment_qm,
		  Minimum_simulation_time_increment) : TRUEP(Qnil);
      }
      POP_LOCAL_ALLOCATION(0,0);
      if (temp) {
	  temp_1 = Bad_phrase;
	  temp_2 = tformat_text_string(2,string_constant_53,
		  Minimum_simulation_time_increment);
	  result = VALUES_2(temp_1,temp_2);
      }
      else {
	  update_frame_status(generic_simulation_formula,Nil,Nil);
	  simulation_expression = THIRD(parse_result);
	  initial_value_expression_qm = FIFTH(parse_result);
	  simulation_class_or_item = 
		  simulation_class_or_item_without_local_name(SECOND(parse_result));
	  compiled_simulation_expression = 
		  compile_generic_simulation_formula(simulation_expression,
		  simulation_class_or_item,SEVENTH(parse_result),
		  generic_simulation_formula,Nil);
	  compiled_initial_value_expression_qm = Nil;
	  if ( !TRUEP(compiled_simulation_expression)) {
	      M_THIRD(parse_result) = Nil;
	      M_FIFTH(parse_result) = Nil;
	      strip_out_local_names_if_any(parse_result);
	      result = VALUES_1(parse_result);
	  }
	  else {
	      compiled_initial_value_expression_qm = 
		      compile_initial_value_expression_qm(initial_value_expression_qm) 
		      ? 
		      compile_generic_simulation_formula(initial_value_expression_qm,
		      simulation_class_or_item,SEVENTH(parse_result),
		      generic_simulation_formula,T) : 
		      initial_value_expression_qm;
	      strip_out_local_names_if_any(parse_result);
	      if (initial_value_expression_qm &&  
		      !TRUEP(compiled_initial_value_expression_qm)) {
		  M_THIRD(parse_result) = Nil;
		  M_FIFTH(parse_result) = Nil;
		  result = VALUES_1(parse_result);
	      }
	      else {
		  M_THIRD(parse_result) = compiled_simulation_expression;
		  M_FIFTH(parse_result) = compiled_initial_value_expression_qm;
		  if (compile_initial_value_expression_qm(compiled_initial_value_expression_qm)) 
			      {
		      change_slot_value(3,generic_simulation_formula,
			      Qgeneric_simulation_formula_byte_code_body,Nil);
		      current_computation_component_particulars = 
			      list_constant_24;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			      0);
			byte_code_body = SYMBOLP(simulation_class_or_item) 
				? 
				compile_simulation_formula_for_stack(FIFTH(parse_result),
				simulation_class_or_item,
				simulation_class_or_item,T) : 
				compile_simulation_formula_for_stack(FIFTH(parse_result),
				Nil,Nil,T);
			change_slot_value(3,generic_simulation_formula,
				Qgeneric_simulation_initial_value_byte_code_body,
				byte_code_body);
		      POP_SPECIAL();
		  }
		  else
		      change_slot_value(3,generic_simulation_formula,
			      Qgeneric_simulation_initial_value_byte_code_body,
			      Nil);
		  byte_code_body = SYMBOLP(simulation_class_or_item) ? 
			  compile_simulation_formula_for_stack(THIRD(parse_result),
			  simulation_class_or_item,
			  simulation_class_or_item,Nil) : 
			  compile_simulation_formula_for_stack(THIRD(parse_result),
			  Nil,Nil,Nil);
		  change_slot_value(3,generic_simulation_formula,
			  Qgeneric_simulation_formula_byte_code_body,
			  byte_code_body);
		  result = VALUES_1(parse_result);
	      }
	  }
      }
    POP_SPECIAL();
    return result;
}

static Object Qcurrent_parameter_value;  /* current-parameter-value */

/* USE-CURRENT-PARAMETER-VALUE? */
Object use_current_parameter_value_qm(initial_value_expression_qm)
    Object initial_value_expression_qm;
{
    x_note_fn_call(199,373);
    if (CONSP(initial_value_expression_qm))
	return VALUES_1(EQ(CAR(initial_value_expression_qm),
		Qcurrent_parameter_value) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* COMPILE-INITIAL-VALUE-EXPRESSION? */
Object compile_initial_value_expression_qm(initial_value_expression_qm)
    Object initial_value_expression_qm;
{
    x_note_fn_call(199,374);
    if (initial_value_expression_qm)
	return VALUES_1( 
		!TRUEP(use_current_parameter_value_qm(initial_value_expression_qm)) 
		? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qany;                /* any */

/* STRIP-OUT-LOCAL-NAMES-IF-ANY */
Object strip_out_local_names_if_any(translation)
    Object translation;
{
    Object temp, current_designation;

    x_note_fn_call(199,375);
    temp = atomic_naming_element_of_role(FIRST(translation));
    M_FIRST(translation) = temp;
    temp = simulation_class_or_item_without_local_name(SECOND(translation));
    M_SECOND(translation) = temp;
    current_designation = SEVENTH(translation);
  next_loop:
    if (ATOM(current_designation))
	goto end_loop;
    temp = simple_role_of_role(SECOND(current_designation));
    M_SECOND(current_designation) = temp;
    if (EQ(CAR(current_designation),Qany))
	M_CAR(current_designation) = Qthe;
    current_designation = THIRD(current_designation);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SIMULATION-CLASS-OR-ITEM-WITHOUT-LOCAL-NAME */
Object simulation_class_or_item_without_local_name(simulation_class_or_item)
    Object simulation_class_or_item;
{
    x_note_fn_call(199,376);
    if ( !(CONSP(simulation_class_or_item) && 
	    EQ(CAR(simulation_class_or_item),Qitem)))
	return atomic_naming_element_of_role(simulation_class_or_item);
    else
	return VALUES_1(simulation_class_or_item);
}

void grammar5_INIT()
{
    Object temp, reclaim_structure_for_date_format_1, uuid_evaluation_setter_1;
    Object uuid_evaluation_getter_1, attribute_evaluation_setter_1;
    Object attribute_evaluation_getter_1;
    Object read_only_attribute_evaluation_getter_1, symbol_evaluation_setter_1;
    Object symbol_evaluation_getter_1;
    Object read_only_symbol_data_type_evaluation_getter_1;
    Object read_only_text_data_type_evaluation_getter_1;
    Object read_only_truth_value_data_type_evaluation_getter_1;
    Object float_data_type_evaluation_setter_1;
    Object float_data_type_evaluation_getter_1;
    Object integer_data_type_evaluation_setter_1;
    Object integer_data_type_evaluation_getter_1;
    Object long_data_type_evaluation_setter_1;
    Object long_data_type_evaluation_getter_1;
    Object quantitative_data_type_evaluation_setter_1;
    Object quantitative_data_type_evaluation_getter_1;
    Object data_type_evaluation_setter_1, data_type_evaluation_getter_1;
    Object validity_interval_evaluation_setter_1;
    Object validity_interval_evaluation_getter_1;
    Object sensor_validity_interval_evaluation_setter_1;
    Object sensor_validity_interval_evaluation_getter_1;
    Object positive_quantity_interval_qm_evaluation_setter_1;
    Object positive_quantity_interval_qm_evaluation_getter_1;
    Object interval_qm_or_default_evaluation_setter_1;
    Object interval_qm_or_default_evaluation_getter_1;
    Object execution_interval_qm_or_default_evaluation_setter_1;
    Object execution_interval_qm_or_default_evaluation_getter_1;
    Object truth_value_evaluation_setter_1, truth_value_evaluation_getter_1;
    Object truth_value_qm_evaluation_setter_1;
    Object truth_value_qm_evaluation_getter_1;
    Object non_negative_integer_evaluation_setter_1;
    Object non_negative_integer_evaluation_getter_1;
    Object integer_evaluation_setter_1, integer_evaluation_getter_1;
    Object integer_qm_evaluation_setter_1, integer_qm_evaluation_getter_1;
    Object quantity_evaluation_setter_1, quantity_evaluation_getter_1;
    Object quantity_qm_evaluation_setter_1, quantity_qm_evaluation_getter_1;
    Object initial_value_float_evaluation_setter_1;
    Object initial_value_float_evaluation_getter_1;
    Object initial_value_float_qm_evaluation_setter_1;
    Object initial_value_float_qm_evaluation_getter_1;
    Object initial_value_integer_evaluation_setter_1;
    Object initial_value_integer_evaluation_getter_1;
    Object initial_value_long_evaluation_setter_1;
    Object initial_value_long_evaluation_getter_1;
    Object initial_value_long_qm_evaluation_setter_1;
    Object initial_value_long_qm_evaluation_getter_1;
    Object initial_value_integer_qm_evaluation_setter_1;
    Object initial_value_integer_qm_evaluation_getter_1;
    Object standard_or_class_qualified_symbol_evaluation_setter_1;
    Object standard_or_class_qualified_symbol_evaluation_getter_1;
    Object standard_or_class_qualified_symbol_qm_evaluation_setter_1;
    Object standard_or_class_qualified_symbol_qm_evaluation_getter_1;
    Object whole_string_evaluation_setter_1, whole_string_evaluation_getter_1;
    Object whole_string_qm_evaluation_setter_1;
    Object whole_string_qm_evaluation_getter_1;
    Object read_only_whole_string_qm_evaluation_getter_1;
    Object positive_integer_evaluation_setter_1;
    Object positive_integer_evaluation_getter_1;
    Object read_only_positive_integer_evaluation_getter_1;
    Object read_only_integer_evaluation_getter_1;
    Object positive_integer_qm_evaluation_setter_1;
    Object positive_integer_qm_evaluation_getter_1;
    Object read_only_positive_integer_qm_evaluation_getter_1;
    Object initial_sensor_value_qm_evaluation_setter_1;
    Object initial_sensor_value_qm_evaluation_getter_1;
    Object delay_millisecond_time_qm_evaluation_setter_1;
    Object delay_millisecond_time_qm_evaluation_getter_1;
    Object trace_file_pathname_evaluation_setter_1;
    Object trace_file_pathname_evaluation_getter_1;
    Object number_qm_evaluation_setter_1, number_qm_evaluation_getter_1;
    Object variable_frame_flags_evaluation_setter_1;
    Object variable_frame_flags_evaluation_getter_1;
    Object parameter_frame_flags_evaluation_setter_1;
    Object parameter_frame_flags_evaluation_getter_1;
    Object simulation_time_increment_qm_evaluation_setter_1;
    Object simulation_time_increment_qm_evaluation_getter_1;
    Object simulation_time_increment_evaluation_setter_1;
    Object simulation_time_increment_evaluation_getter_1;
    Object integration_algorithm_specification_evaluation_setter_1;
    Object integration_algorithm_specification_evaluation_getter_1;
    Object simulation_control_specification_evaluation_setter_1;
    Object simulation_control_specification_evaluation_getter_1;
    Object priority_evaluation_setter_1, priority_evaluation_getter_1;
    Object AB_package, Quse_slot_value_compiler_for_default_overrides_p;
    Object Qgeneric_simulation_formula;
    Object Qcompile_generic_simulation_formula_for_slot, string_constant_219;
    Object string_constant_218, string_constant_217, string_constant_216;
    Object string_constant_215, string_constant_214, string_constant_213;
    Object string_constant_212, string_constant_211;
    Object Qtranslate_role_local_name_and_preposition;
    Object Qtranslate_role_and_preposition, Qsimplify_associative_operation;
    Object Qtranslate_generic_simulation_formula, Qgeneric_formula;
    Object Qcompile_generic_formula_for_slot, list_constant_126, Qab_or;
    Object Qunknown_datum, Qtranslate_generic_formula, string_constant_210;
    Object string_constant_209, string_constant_208, string_constant_207;
    Object string_constant_206, Qwrite_symbol_from_slot;
    Object Qlogical_instance_formula;
    Object Qcompile_logical_instance_formula_for_slot, string_constant_205;
    Object Qinstance_formula, Qcompile_instance_formula_for_slot;
    Object string_constant_204, Qwrite_non_negative_number_from_slot;
    Object Qnon_negative_number, Qcompile_non_negative_number_for_slot;
    Object list_constant_75, Qwrite_non_negative_integer_from_slot;
    Object Qnon_negative_integer, Qcompile_non_negative_integer_for_slot;
    Object string_constant_203, Qpriority, Qnamed;
    Object Qtype_specification_simple_expansion, Qwrite_priority_from_slot;
    Object Qcompile_priority_for_slot, string_constant_202;
    Object Qwrite_positive_integer_qm_from_slot, Qpositive_integer_qm;
    Object Qread_only_positive_integer_qm;
    Object Qcompile_read_only_positive_integer_qm_for_slot;
    Object Qcompile_positive_integer_qm_for_slot, string_constant_201;
    Object Qwrite_positive_integer_from_slot;
    Object Qcompile_positive_integer_for_slot, string_constant_200;
    Object Qsimulation_control_specification, list_constant_125;
    Object list_constant_124, list_constant_123, list_constant_122;
    Object list_constant_121, list_constant_93, list_constant_120;
    Object list_constant_78;
    Object Qcompile_simulation_control_specification_for_slot;
    Object Qwrite_simulation_control_specification_from_slot;
    Object Qintegration_algorithm_specification;
    Object Qwrite_integration_algorithm_specification_from_slot;
    Object string_constant_199, string_constant_198, string_constant_197;
    Object string_constant_196, Qwrite_simulation_time_increment_from_slot;
    Object Qsimulation_time_increment;
    Object Qwrite_simulation_time_increment_qm_from_slot;
    Object Qsimulation_time_increment_qm;
    Object Qcompile_simulation_time_increment_for_slot;
    Object Qcompile_simulation_time_increment_qm_for_slot, string_constant_195;
    Object Qwrite_parameter_frame_flags_from_slot, Qparameter_frame_flags;
    Object Qwrite_variable_frame_flags_from_slot, Qvariable_frame_flags;
    Object list_constant_119, list_constant_118, list_constant_117;
    Object list_constant_112, list_constant_111, list_constant_114;
    Object Qcompile_parameter_frame_flags_for_slot;
    Object Qcompile_variable_frame_flags_for_slot, list_constant_116;
    Object list_constant_115, list_constant_113, list_constant_110;
    Object string_constant_194, string_constant_193, string_constant_192;
    Object string_constant_191, string_constant_190, string_constant_189;
    Object string_constant_188, Qwrite_truth_value_qm_from_slot;
    Object Qtruth_value_qm, Qwrite_truth_value_from_slot;
    Object Qcompile_truth_value_qm_for_slot, Qcompile_truth_value_for_slot;
    Object Qwrite_whole_string_from_slot, Qsymbol_qm;
    Object Qwrite_standard_or_class_qualified_symbol_from_slot;
    Object Qcompile_standard_or_class_qualified_symbol_for_slot;
    Object Qwrite_standard_or_class_qualified_symbol_qm_from_slot;
    Object Qstandard_or_class_qualified_symbol_qm;
    Object Qcompile_standard_or_class_qualified_symbol_qm_for_slot;
    Object Qcompile_symbol_qm_for_slot, Qcompile_initial_value_float_for_slot;
    Object Qcompile_initial_value_integer_for_slot, Qinitial_value_float_qm;
    Object Qcompile_initial_value_float_qm_for_slot, Qfloat_qm;
    Object Qcompile_float_qm_for_slot, Qinitial_value_integer_qm;
    Object Qcompile_initial_value_integer_qm_for_slot;
    Object Qcompile_integer_qm_for_slot, Qcompile_initial_value_long_for_slot;
    Object Qinitial_value_long_qm, Qcompile_initial_value_long_qm_for_slot;
    Object Qwrite_initial_value_long_qm_from_slot;
    Object Qwrite_initial_value_integer_qm_from_slot;
    Object Qwrite_integer_qm_from_slot;
    Object Qwrite_initial_value_float_qm_from_slot, Qwrite_float_qm_from_slot;
    Object Qwrite_initial_value_float_from_slot, Qwrite_float_from_slot;
    Object Qwrite_initial_value_long_from_slot, Qwrite_long_from_slot;
    Object Qwrite_initial_value_integer_from_slot, Qwrite_integer_from_slot;
    Object Qwrite_number_from_slot, Qnumber_qm, list_constant_76;
    Object Qcompile_number_qm_for_slot, Qwrite_quantity_qm_from_slot;
    Object Qquantity_qm, Qcompile_quantity_qm_for_slot;
    Object Qwrite_quantity_from_slot, Qcompile_quantity_for_slot;
    Object Qwrite_number_qm_from_slot, Qtrace_file_pathname, list_constant_109;
    Object list_constant_108, list_constant_102;
    Object Qwrite_delay_millisecond_time_qm_from_slot;
    Object Qdelay_millisecond_time_qm;
    Object Qcompile_delay_millisecond_time_qm_for_slot;
    Object Qinitial_sensor_value_qm, Qwrite_initial_sensor_value_qm_from_slot;
    Object Qcompile_initial_sensor_value_qm_for_slot, list_constant_87;
    Object list_constant_107, list_constant_106, list_constant_105;
    Object string_constant_187, string_constant_186, string_constant_185;
    Object Qconvert_singular_constant, list_constant_103;
    Object Qwrite_read_only_positive_integer_qm_from_slot;
    Object Qwrite_read_only_integer_from_slot, Qread_only_integer;
    Object Qwrite_read_only_positive_integer_from_slot;
    Object Qread_only_positive_integer, Qread_only_whole_string_qm;
    Object Qwhole_string_qm, list_constant_79, list_constant_104;
    Object list_constant_97, string_constant_184, string_constant_183;
    Object string_constant_182, Qcheck_range_of_element;
    Object Qwrite_read_only_whole_string_qm_from_slot;
    Object Qcompile_whole_string_qm_for_slot, Qwrite_whole_string_qm_from_slot;
    Object Qspecific_simulation_formula_qm;
    Object Qcompile_specific_simulation_formula_qm_for_slot;
    Object Qsimulation_initial_value, string_constant_181, string_constant_180;
    Object string_constant_179;
    Object Qwrite_execution_interval_qm_or_default_from_slot;
    Object Qexecution_interval_qm_or_default, list_constant_100;
    Object Qcompile_execution_interval_qm_or_default_for_slot;
    Object Qwrite_positive_interval_qm_or_default_from_slot;
    Object Qcompile_positive_interval_qm_or_default_for_slot;
    Object Qwrite_interval_qm_or_default_from_slot, Qinterval_qm_or_default;
    Object list_constant_101, list_constant_99;
    Object Qcompile_interval_qm_or_default_for_slot, string_constant_178;
    Object string_constant_177, Qwrite_positive_quantity_interval_qm_from_slot;
    Object Qpositive_quantity_interval_qm, Qpositive_quantity_interval;
    Object Qcompile_positive_quantity_interval_for_slot;
    Object Qcompile_positive_quantity_interval_qm_for_slot;
    Object Qwrite_quantity_interval_from_slot, Qquantity_interval;
    Object Qcompile_quantity_interval_for_slot;
    Object Qwrite_execution_interval_qm_from_slot, Qexecution_interval_qm;
    Object Qcompile_execution_interval_qm_for_slot;
    Object Qwrite_positive_interval_qm_from_slot;
    Object Qcompile_positive_interval_qm_for_slot, Qwrite_interval_from_slot;
    Object Qcompile_interval_for_slot, Qwrite_interval_qm_from_slot;
    Object Qinterval_qm, Qcompile_interval_qm_for_slot, string_constant_176;
    Object Qsensor_validity_interval, list_constant_98, Qsupplied, Qindefinite;
    Object list_constant_95, Qwrite_sensor_validity_interval_from_slot;
    Object Qcompile_sensor_validity_interval_for_slot, string_constant_175;
    Object Qwrite_validity_interval_from_slot, Qvalidity_interval;
    Object Qcompile_validity_interval_for_slot, list_constant_96;
    Object string_constant_174, Qwrite_supplied_value_from_slot;
    Object Qsupplied_value, string_constant_173, string_constant_172;
    Object string_constant_171, string_constant_170;
    Object Qwrite_float_data_type_from_slot, Qfloat_data_type;
    Object Qwrite_long_data_type_from_slot, Qlong_data_type;
    Object Qwrite_integer_data_type_from_slot;
    Object Qwrite_quantitative_data_type_from_slot;
    Object Qwrite_read_only_truth_value_data_type_from_slot;
    Object Qread_only_truth_value_data_type;
    Object Qwrite_read_only_text_data_type_from_slot;
    Object Qread_only_text_data_type;
    Object Qwrite_read_only_symbol_data_type_from_slot;
    Object Qread_only_symbol_data_type, Qcompile_long_data_type_for_slot;
    Object Qcompile_integer_data_type_for_slot;
    Object Qcompile_float_data_type_for_slot;
    Object Qcompile_quantitative_data_type_for_slot;
    Object Qwrite_data_type_from_slot, Qdata_type, Qcompile_data_type_for_slot;
    Object list_constant_94, list_constant_92, list_constant_91;
    Object list_constant_90, list_constant_89, list_constant_88;
    Object list_constant_84, list_constant_86, list_constant_85;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object list_constant_80, string_constant_169, string_constant_168;
    Object string_constant_167, string_constant_166;
    Object Qddd_dot_dddd_format_integer_attribute;
    Object Qcompile_ddd_dot_dddd_format_integer_attribute_for_slot;
    Object Qddd_dot_dddd_format_float_attribute;
    Object Qcompile_ddd_dot_dddd_format_float_attribute_for_slot;
    Object Qddd_dot_dddd_format_attribute;
    Object Qcompile_ddd_dot_dddd_format_attribute_for_slot;
    Object Qevaluation_value_constant_allowing_items;
    Object Qcompile_evaluation_value_constant_allowing_items_for_slot;
    Object Qsequence_attribute, Qcompile_sequence_attribute_for_slot;
    Object Qstructure_attribute, Qcompile_structure_attribute_for_slot;
    Object Qtruth_value_attribute, Qcompile_truth_value_attribute_for_slot;
    Object Qfree_text_attribute, Qcompile_free_text_attribute_for_slot;
    Object Qtext_attribute, Qcompile_text_attribute_for_slot;
    Object Qsymbol_attribute, Qcompile_symbol_attribute_for_slot;
    Object Qinteger_attribute, Qcompile_integer_attribute_for_slot;
    Object Qfloat_attribute, Qcompile_float_attribute_for_slot;
    Object Qnumber_attribute, Qcompile_number_attribute_for_slot;
    Object Qdatum_attribute, Qcompile_datum_attribute_for_slot;
    Object Qitem_or_datum_attribute, Qcompile_item_or_datum_attribute_for_slot;
    Object Qitem_or_datum_or_no_item_attribute;
    Object Qcompile_item_or_datum_or_no_item_attribute_for_slot;
    Object Qread_only_attribute, Qwrite_read_only_attribute_from_slot;
    Object list_constant_77, Qno_item, Qcompile_read_only_attribute_for_slot;
    Object Qcompile_attribute_for_slot, Qwrite_non_default_number_qm_from_slot;
    Object Qnon_default_number_qm, Qcompile_non_default_number_qm_for_slot;
    Object Qwrite_simulation_frame_qm_from_slot, Qsimulation_frame_qm;
    Object Qcontinuous_state, Qdiscrete_state, string_constant_165;
    Object string_constant_164, Qreject_truth_value_as_symbol, Quuid;
    Object string_constant_163, string_constant_162;
    Object Qwrite_free_text_attribute_from_slot;
    Object Qwrite_text_attribute_from_slot, Qwrite_symbol_attribute_from_slot;
    Object Qwrite_truth_value_attribute_from_slot;
    Object Qwrite_yyyy_mm_float_attribute_from_slot, Qyyyy_mm_float_attribute;
    Object Qwrite_yyyy_mm_integer_attribute_from_slot;
    Object Qyyyy_mm_integer_attribute, Qwrite_yyyy_mm_attribute_from_slot;
    Object Qyyyy_mm_attribute, string_constant_161;
    Object Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp;
    Object Qadd_zero_time_to_date, Qtransform_input_phrase_into_universal_date;
    Object Qset_day_of_date_to_1, string_constant_160;
    Object Qcoerce_phrase_number_to_float, string_constant_159;
    Object Qdate_format_description, string_constant_158, Qyyyy_mm;
    Object Qwrite_mm_yyyy_float_attribute_from_slot, Qmm_yyyy_float_attribute;
    Object Qwrite_mm_yyyy_integer_attribute_from_slot;
    Object Qmm_yyyy_integer_attribute, Qwrite_mm_yyyy_attribute_from_slot;
    Object Qmm_yyyy_attribute, string_constant_157, string_constant_156;
    Object string_constant_155, string_constant_154, Qmm_yyyy;
    Object Qwrite_dd_mm_yyyy_float_attribute_from_slot;
    Object Qdd_mm_yyyy_float_attribute;
    Object Qwrite_dd_mm_yyyy_integer_attribute_from_slot;
    Object Qdd_mm_yyyy_integer_attribute;
    Object Qwrite_dd_mm_yyyy_attribute_from_slot, Qdd_mm_yyyy_attribute;
    Object string_constant_153, Qadd_zero_time_to_date_list;
    Object string_constant_152, string_constant_151, string_constant_150;
    Object Qdd_mm_yyyy, Qwrite_mm_dd_yyyy_float_attribute_from_slot;
    Object Qmm_dd_yyyy_float_attribute;
    Object Qwrite_mm_dd_yyyy_integer_attribute_from_slot;
    Object Qmm_dd_yyyy_integer_attribute;
    Object Qwrite_mm_dd_yyyy_attribute_from_slot, Qmm_dd_yyyy_attribute;
    Object string_constant_149, string_constant_148, string_constant_147;
    Object string_constant_146, Qmm_dd_yyyy;
    Object Qwrite_yyyy_mm_dd_float_attribute_from_slot;
    Object Qyyyy_mm_dd_float_attribute;
    Object Qwrite_yyyy_mm_dd_integer_attribute_from_slot;
    Object Qyyyy_mm_dd_integer_attribute;
    Object Qwrite_yyyy_mm_dd_attribute_from_slot, Qyyyy_mm_dd_attribute;
    Object string_constant_145, string_constant_144, string_constant_143;
    Object string_constant_142, Qyyyy_mm_dd;
    Object Qwrite_yyyy_mm_dd_hh_mm_float_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_float_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_integer_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_integer_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_attribute, string_constant_141;
    Object string_constant_140, string_constant_139, string_constant_138;
    Object Qyyyy_mm_dd_hh_mm;
    Object Qwrite_dd_mm_yyyy_hh_mm_float_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_float_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_integer_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_integer_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_attribute, string_constant_137;
    Object string_constant_136, string_constant_135, string_constant_134;
    Object Qdd_mm_yyyy_hh_mm;
    Object Qwrite_mm_dd_yyyy_hh_mm_float_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_float_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_integer_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_integer_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_attribute, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object Qmm_dd_yyyy_hh_mm;
    Object Qwrite_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_am_pm_float_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_am_pm_integer_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_am_pm_attribute, string_constant_129;
    Object string_constant_128, string_constant_127, string_constant_126;
    Object Qyyyy_mm_dd_hh_mm_am_pm;
    Object Qwrite_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_am_pm_float_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_am_pm_integer_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_am_pm_attribute, string_constant_125;
    Object string_constant_124, string_constant_123, string_constant_122;
    Object Qdd_mm_yyyy_hh_mm_am_pm;
    Object Qwrite_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_am_pm_float_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_am_pm_integer_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_am_pm_attribute, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object Qmm_dd_yyyy_hh_mm_am_pm;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_am_pm_float_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_am_pm_attribute, string_constant_117;
    Object string_constant_116, string_constant_115, string_constant_114;
    Object Qyyyy_mm_dd_hh_mm_ss_am_pm;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_am_pm_float_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_am_pm_attribute, string_constant_113;
    Object string_constant_112, string_constant_111, string_constant_110;
    Object Qdd_mm_yyyy_hh_mm_ss_am_pm;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_am_pm_float_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_am_pm_attribute, string_constant_109;
    Object string_constant_108, string_constant_107, string_constant_106;
    Object Qmm_dd_yyyy_hh_mm_ss_am_pm;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_float_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_integer_attribute;
    Object Qwrite_yyyy_mm_dd_hh_mm_ss_attribute_from_slot;
    Object Qyyyy_mm_dd_hh_mm_ss_attribute, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object Qyyyy_mm_dd_hh_mm_ss;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_float_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_integer_attribute;
    Object Qwrite_dd_mm_yyyy_hh_mm_ss_attribute_from_slot;
    Object Qdd_mm_yyyy_hh_mm_ss_attribute, string_constant_101;
    Object string_constant_100, string_constant_99, string_constant_98;
    Object Qdd_mm_yyyy_hh_mm_ss;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_float_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_integer_attribute;
    Object Qwrite_mm_dd_yyyy_hh_mm_ss_attribute_from_slot;
    Object Qmm_dd_yyyy_hh_mm_ss_attribute, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object Qmm_dd_yyyy_hh_mm_ss, string_constant_93, string_constant_92;
    Object string_constant_91, Qfilter_and_normalize_time_of_day;
    Object Qwrite_mm_ss_as_interval_float_attribute_from_slot;
    Object Qmm_ss_as_interval_float_attribute;
    Object Qwrite_mm_ss_as_interval_integer_attribute_from_slot;
    Object Qmm_ss_as_interval_integer_attribute;
    Object Qwrite_mm_ss_as_interval_attribute_from_slot;
    Object Qmm_ss_as_interval_attribute, string_constant_90;
    Object Qtransform_and_filter_day_and_time_interval, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object Qmm_ss_as_interval;
    Object Qwrite_hh_dot_hh_as_interval_float_attribute_from_slot;
    Object Qhh_dot_hh_as_interval_float_attribute;
    Object Qwrite_hh_dot_hh_as_interval_integer_attribute_from_slot;
    Object Qhh_dot_hh_as_interval_integer_attribute;
    Object Qwrite_hh_dot_hh_as_interval_attribute_from_slot;
    Object Qhh_dot_hh_as_interval_attribute, string_constant_85;
    Object Qconvert_to_seconds, string_constant_84, string_constant_83;
    Object string_constant_82, string_constant_81, Qhh_dot_hh_as_interval;
    Object Qwrite_hh_mm_as_interval_float_attribute_from_slot;
    Object Qhh_mm_as_interval_float_attribute;
    Object Qwrite_hh_mm_as_interval_integer_attribute_from_slot;
    Object Qhh_mm_as_interval_integer_attribute;
    Object Qwrite_hh_mm_as_interval_attribute_from_slot;
    Object Qhh_mm_as_interval_attribute, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, Qhh_mm_as_interval;
    Object Qwrite_hh_mm_ss_as_interval_float_attribute_from_slot;
    Object Qhh_mm_ss_as_interval_float_attribute;
    Object Qwrite_hh_mm_ss_as_interval_integer_attribute_from_slot;
    Object Qhh_mm_ss_as_interval_integer_attribute;
    Object Qwrite_hh_mm_ss_as_interval_attribute_from_slot;
    Object Qhh_mm_ss_as_interval_attribute, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, Qhh_mm_ss_as_interval;
    Object Qwrite_dd_hh_mm_ss_as_interval_float_attribute_from_slot;
    Object Qdd_hh_mm_ss_as_interval_float_attribute;
    Object Qwrite_dd_hh_mm_ss_as_interval_integer_attribute_from_slot;
    Object Qdd_hh_mm_ss_as_interval_integer_attribute;
    Object Qwrite_dd_hh_mm_ss_as_interval_attribute_from_slot;
    Object Qdd_hh_mm_ss_as_interval_attribute, string_constant_70;
    Object string_constant_69, string_constant_68, string_constant_67;
    Object string_constant_66, Qdd_hh_mm_ss_as_interval, Qdate_format;
    Object Qreclaim_structure, Qoutstanding_date_format_count;
    Object Qdate_format_structure_memory_usage, Qutilities2;
    Object string_constant_65, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_64, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qwrite_ddd_dot_dddd_format_integer_attribute_from_slot;
    Object Qwrite_ddd_dot_dddd_format_float_attribute_from_slot;
    Object Qwrite_ddd_dot_dddd_format_attribute_from_slot;
    Object Qwrite_time_stamp_float_attribute_from_slot;
    Object Qtime_stamp_float_attribute;
    Object Qwrite_time_stamp_integer_attribute_from_slot;
    Object Qtime_stamp_integer_attribute;
    Object Qwrite_time_stamp_attribute_from_slot, Qtime_stamp_attribute;
    Object Qwrite_interval_float_attribute_from_slot;
    Object Qinterval_float_attribute;
    Object Qwrite_interval_integer_attribute_from_slot;
    Object Qinterval_integer_attribute, Qwrite_interval_attribute_from_slot;
    Object Qinterval_attribute, Qcompile_interval_float_attribute_for_slot;
    Object Qcompile_interval_integer_attribute_for_slot;
    Object Qcompile_interval_attribute_for_slot;
    Object Qwrite_integer_attribute_from_slot;
    Object Qwrite_float_attribute_from_slot, Qwrite_number_attribute_from_slot;
    Object Qwrite_sequence_attribute_from_slot;
    Object Qwrite_structure_attribute_from_slot;
    Object Qwrite_datum_attribute_from_slot;
    Object Qwrite_item_or_datum_attribute_from_slot;
    Object Qwrite_item_or_datum_or_no_item_attribute_from_slot;
    Object Qwrite_attribute_from_slot;

    x_note_fn_call(199,377);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qwrite_attribute_from_slot = STATIC_SYMBOL("WRITE-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_attribute_from_slot,
	    STATIC_FUNCTION(write_attribute_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qattribute,
	    SYMBOL_FUNCTION(Qwrite_attribute_from_slot),Qslot_value_writer);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING("~s");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_1 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    Qitem_or_datum_or_no_item_attribute = 
	    STATIC_SYMBOL("ITEM-OR-DATUM-OR-NO-ITEM-ATTRIBUTE",AB_package);
    Qwrite_item_or_datum_or_no_item_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-ITEM-OR-DATUM-OR-NO-ITEM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_item_or_datum_or_no_item_attribute_from_slot,
	    STATIC_FUNCTION(write_item_or_datum_or_no_item_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qitem_or_datum_or_no_item_attribute,
	    SYMBOL_FUNCTION(Qwrite_item_or_datum_or_no_item_attribute_from_slot),
	    Qslot_value_writer);
    Qitem_or_datum_attribute = STATIC_SYMBOL("ITEM-OR-DATUM-ATTRIBUTE",
	    AB_package);
    Qwrite_item_or_datum_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-ITEM-OR-DATUM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_item_or_datum_attribute_from_slot,
	    STATIC_FUNCTION(write_item_or_datum_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qitem_or_datum_attribute,
	    SYMBOL_FUNCTION(Qwrite_item_or_datum_attribute_from_slot),
	    Qslot_value_writer);
    Qdatum_attribute = STATIC_SYMBOL("DATUM-ATTRIBUTE",AB_package);
    Qwrite_datum_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DATUM-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_datum_attribute_from_slot,
	    STATIC_FUNCTION(write_datum_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qdatum_attribute,
	    SYMBOL_FUNCTION(Qwrite_datum_attribute_from_slot),
	    Qslot_value_writer);
    Qstructure_attribute = STATIC_SYMBOL("STRUCTURE-ATTRIBUTE",AB_package);
    Qwrite_structure_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-STRUCTURE-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_structure_attribute_from_slot,
	    STATIC_FUNCTION(write_structure_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qstructure_attribute,
	    SYMBOL_FUNCTION(Qwrite_structure_attribute_from_slot),
	    Qslot_value_writer);
    Qsequence_attribute = STATIC_SYMBOL("SEQUENCE-ATTRIBUTE",AB_package);
    Qwrite_sequence_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-SEQUENCE-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_sequence_attribute_from_slot,
	    STATIC_FUNCTION(write_sequence_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsequence_attribute,
	    SYMBOL_FUNCTION(Qwrite_sequence_attribute_from_slot),
	    Qslot_value_writer);
    Qnumber_attribute = STATIC_SYMBOL("NUMBER-ATTRIBUTE",AB_package);
    Qwrite_number_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-NUMBER-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_attribute_from_slot,
	    STATIC_FUNCTION(write_number_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qnumber_attribute,
	    SYMBOL_FUNCTION(Qwrite_number_attribute_from_slot),
	    Qslot_value_writer);
    Qfloat_attribute = STATIC_SYMBOL("FLOAT-ATTRIBUTE",AB_package);
    Qwrite_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-FLOAT-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_float_attribute_from_slot,
	    STATIC_FUNCTION(write_float_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfloat_attribute,
	    SYMBOL_FUNCTION(Qwrite_float_attribute_from_slot),
	    Qslot_value_writer);
    Qinteger_attribute = STATIC_SYMBOL("INTEGER-ATTRIBUTE",AB_package);
    Qwrite_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-INTEGER-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_integer_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinteger_attribute,
	    SYMBOL_FUNCTION(Qwrite_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qinterval_attribute = STATIC_SYMBOL("INTERVAL-ATTRIBUTE",AB_package);
    Qcompile_interval_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_attribute_for_slot,
	    STATIC_FUNCTION(compile_interval_attribute_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qinterval_attribute,
	    SYMBOL_FUNCTION(Qcompile_interval_attribute_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qinterval_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinterval_integer_attribute = 
	    STATIC_SYMBOL("INTERVAL-INTEGER-ATTRIBUTE",AB_package);
    Qcompile_interval_integer_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL-INTEGER-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_integer_attribute_for_slot,
	    STATIC_FUNCTION(compile_interval_integer_attribute_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qinterval_integer_attribute,
	    SYMBOL_FUNCTION(Qcompile_interval_integer_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinterval_integer_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinterval_float_attribute = STATIC_SYMBOL("INTERVAL-FLOAT-ATTRIBUTE",
	    AB_package);
    Qcompile_interval_float_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL-FLOAT-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_float_attribute_for_slot,
	    STATIC_FUNCTION(compile_interval_float_attribute_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinterval_float_attribute,
	    SYMBOL_FUNCTION(Qcompile_interval_float_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinterval_float_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_interval_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinterval_attribute,
	    SYMBOL_FUNCTION(Qwrite_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_interval_integer_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinterval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_interval_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinterval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    Qtime_stamp_attribute = STATIC_SYMBOL("TIME-STAMP-ATTRIBUTE",AB_package);
    Qwrite_time_stamp_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-TIME-STAMP-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_time_stamp_attribute_from_slot,
	    STATIC_FUNCTION(write_time_stamp_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qtime_stamp_attribute,
	    SYMBOL_FUNCTION(Qwrite_time_stamp_attribute_from_slot),
	    Qslot_value_writer);
    Qtime_stamp_integer_attribute = 
	    STATIC_SYMBOL("TIME-STAMP-INTEGER-ATTRIBUTE",AB_package);
    Qwrite_time_stamp_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-TIME-STAMP-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_time_stamp_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_time_stamp_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtime_stamp_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_time_stamp_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qtime_stamp_float_attribute = 
	    STATIC_SYMBOL("TIME-STAMP-FLOAT-ATTRIBUTE",AB_package);
    Qwrite_time_stamp_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-TIME-STAMP-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_time_stamp_float_attribute_from_slot,
	    STATIC_FUNCTION(write_time_stamp_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtime_stamp_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_time_stamp_float_attribute_from_slot),
	    Qslot_value_writer);
    if (Current_ddd_dot_dddd_format_qm == UNBOUND)
	Current_ddd_dot_dddd_format_qm = Nil;
    Qddd_dot_dddd_format_attribute = 
	    STATIC_SYMBOL("DDD.DDDD-FORMAT-ATTRIBUTE",AB_package);
    Qwrite_ddd_dot_dddd_format_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DDD.DDDD-FORMAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_attribute_from_slot,
	    STATIC_FUNCTION(write_ddd_dot_dddd_format_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qddd_dot_dddd_format_attribute,
	    SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_attribute_from_slot),
	    Qslot_value_writer);
    Qddd_dot_dddd_format_float_attribute = 
	    STATIC_SYMBOL("DDD.DDDD-FORMAT-FLOAT-ATTRIBUTE",AB_package);
    Qwrite_ddd_dot_dddd_format_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DDD.DDDD-FORMAT-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_float_attribute_from_slot,
	    STATIC_FUNCTION(write_ddd_dot_dddd_format_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qddd_dot_dddd_format_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_float_attribute_from_slot),
	    Qslot_value_writer);
    Qddd_dot_dddd_format_integer_attribute = 
	    STATIC_SYMBOL("DDD.DDDD-FORMAT-INTEGER-ATTRIBUTE",AB_package);
    Qwrite_ddd_dot_dddd_format_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DDD.DDDD-FORMAT-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_ddd_dot_dddd_format_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qddd_dot_dddd_format_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_ddd_dot_dddd_format_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qg2_defstruct_structure_name_date_format_g2_struct = 
	    STATIC_SYMBOL("DATE-FORMAT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdate_format = STATIC_SYMBOL("DATE-FORMAT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_date_format_g2_struct,
	    Qdate_format,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qdate_format,
	    Qg2_defstruct_structure_name_date_format_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_date_format == UNBOUND)
	The_type_description_of_date_format = Nil;
    string_constant_64 = 
	    STATIC_STRING("43Dy8m83gUy1n83gUy8n8k1l8n0000001l1n8y83-3Ny1o83ucy83uay83uZy83ubykpk0k0");
    temp = The_type_description_of_date_format;
    The_type_description_of_date_format = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_64));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_date_format_g2_struct,
	    The_type_description_of_date_format,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qdate_format,
	    The_type_description_of_date_format,Qtype_description_of_type);
    Qoutstanding_date_format_count = 
	    STATIC_SYMBOL("OUTSTANDING-DATE-FORMAT-COUNT",AB_package);
    Qdate_format_structure_memory_usage = 
	    STATIC_SYMBOL("DATE-FORMAT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_65 = STATIC_STRING("1q83gUy8s83-Q+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_date_format_count);
    push_optimized_constant(Qdate_format_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_65));
    Qchain_of_available_date_formats = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DATE-FORMATS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_date_formats,
	    Chain_of_available_date_formats);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_date_formats,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qdate_format_count = STATIC_SYMBOL("DATE-FORMAT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdate_format_count,Date_format_count);
    record_system_variable(Qdate_format_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_date_formats_vector == UNBOUND)
	Chain_of_available_date_formats_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdate_format_structure_memory_usage,
	    STATIC_FUNCTION(date_format_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_date_format_count,
	    STATIC_FUNCTION(outstanding_date_format_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_date_format_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_date_format,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdate_format,
	    reclaim_structure_for_date_format_1);
    float_constant = STATIC_FLOAT(0.0);
    string_constant_1 = STATIC_STRING("Seconds must be between 0 and 59");
    string_constant_2 = STATIC_STRING("Minutes must be between 0 and 59");
    string_constant_3 = STATIC_STRING("Hours must be between 0 and 24");
    Qdd_hh_mm_ss_as_interval = STATIC_SYMBOL("DD-HH-MM-SS-AS-INTERVAL",
	    AB_package);
    Qdd_hh_mm_ss_as_interval_attribute = 
	    STATIC_SYMBOL("DD-HH-MM-SS-AS-INTERVAL-ATTRIBUTE",AB_package);
    Qdd_hh_mm_ss_as_interval_integer_attribute = 
	    STATIC_SYMBOL("DD-HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE",
	    AB_package);
    Qdd_hh_mm_ss_as_interval_float_attribute = 
	    STATIC_SYMBOL("DD-HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_66 = STATIC_STRING("dd-hh-mm-ss as an interval");
    Qdate_format_description = STATIC_SYMBOL("DATE-FORMAT-DESCRIPTION",
	    AB_package);
    mutate_global_property(Qdd_hh_mm_ss_as_interval,
	    make_date_format_1(Qdd_hh_mm_ss_as_interval_attribute,
	    Qdd_hh_mm_ss_as_interval_integer_attribute,
	    Qdd_hh_mm_ss_as_interval_float_attribute,string_constant_66),
	    Qdate_format_description);
    string_constant_67 = 
	    STATIC_STRING("1m1n83=5y1q1m9k83=7y1m9k83*5y1m9k83-Q4y1m9k83*5y1m9k83=ay1m9k83-oy1m83=6y83-Q5y1n83*Wy1o1m9k83-Q4y1m9k83*5y1m9k83=ay1m9k83-oy83-");
    string_constant_68 = STATIC_STRING("Q5y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_67,
	    string_constant_68)));
    Qcoerce_phrase_number_to_float = 
	    STATIC_SYMBOL("COERCE-PHRASE-NUMBER-TO-FLOAT",AB_package);
    string_constant_69 = 
	    STATIC_STRING("1m1o83-Q7y83ufy1ll9k1p83-Q6y83ufy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_69));
    Qtransform_and_filter_day_and_time_interval = 
	    STATIC_SYMBOL("TRANSFORM-AND-FILTER-DAY-AND-TIME-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtransform_and_filter_day_and_time_interval,
	    STATIC_FUNCTION(transform_and_filter_day_and_time_interval,NIL,
	    FALSE,1,1));
    string_constant_70 = 
	    STATIC_STRING("1l1o83ufy1r83Sy1m9k83-Py83*7y1m9k83-Py83*7y1m9k83-Py83*7y1orpnl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_and_filter_day_and_time_interval);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    string_constant_4 = STATIC_STRING("~S:~A~S:~A~S:~A~S");
    string_constant_5 = STATIC_STRING("0");
    string_constant_6 = STATIC_STRING("");
    Qwrite_dd_hh_mm_ss_as_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-HH-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_hh_mm_ss_as_interval_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_hh_mm_ss_as_interval_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_hh_mm_ss_as_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_hh_mm_ss_as_interval_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_hh_mm_ss_as_interval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_hh_mm_ss_as_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_hh_mm_ss_as_interval_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_hh_mm_ss_as_interval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_hh_mm_ss_as_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qhh_mm_ss_as_interval = STATIC_SYMBOL("HH-MM-SS-AS-INTERVAL",AB_package);
    Qhh_mm_ss_as_interval_attribute = 
	    STATIC_SYMBOL("HH-MM-SS-AS-INTERVAL-ATTRIBUTE",AB_package);
    Qhh_mm_ss_as_interval_integer_attribute = 
	    STATIC_SYMBOL("HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE",AB_package);
    Qhh_mm_ss_as_interval_float_attribute = 
	    STATIC_SYMBOL("HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE",AB_package);
    string_constant_71 = STATIC_STRING("hh-mm-ss as an interval");
    mutate_global_property(Qhh_mm_ss_as_interval,
	    make_date_format_1(Qhh_mm_ss_as_interval_attribute,
	    Qhh_mm_ss_as_interval_integer_attribute,
	    Qhh_mm_ss_as_interval_float_attribute,string_constant_71),
	    Qdate_format_description);
    string_constant_72 = 
	    STATIC_STRING("1m1n83=5y1q1m9k83=7y1m9k83*5y1m9k83-*By1m9k83*5y1m9k83=ay1m9k83-oy1m83=6y83-Xqy1n83*Wy1o1m9k83-*By1m9k83*5y1m9k83=ay1m9k83-oy83-");
    string_constant_73 = STATIC_STRING("Xqy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_72,
	    string_constant_73)));
    string_constant_74 = 
	    STATIC_STRING("1m1o83-Xsy83-*Cy1ll9k1p83-Xry83-*Cy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_74));
    string_constant_75 = 
	    STATIC_STRING("1l1o83-*Cy1p83Sy1m9k83-Py83*7y1m9k83-Py83*7y1npnl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_and_filter_day_and_time_interval);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_75));
    string_constant_7 = STATIC_STRING("~S:~A~S:~A~S");
    Qwrite_hh_mm_ss_as_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_ss_as_interval_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_ss_as_interval_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_mm_ss_as_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_ss_as_interval_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_ss_as_interval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_mm_ss_as_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_ss_as_interval_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_ss_as_interval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_ss_as_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qhh_mm_as_interval = STATIC_SYMBOL("HH-MM-AS-INTERVAL",AB_package);
    Qhh_mm_as_interval_attribute = 
	    STATIC_SYMBOL("HH-MM-AS-INTERVAL-ATTRIBUTE",AB_package);
    Qhh_mm_as_interval_integer_attribute = 
	    STATIC_SYMBOL("HH-MM-AS-INTERVAL-INTEGER-ATTRIBUTE",AB_package);
    Qhh_mm_as_interval_float_attribute = 
	    STATIC_SYMBOL("HH-MM-AS-INTERVAL-FLOAT-ATTRIBUTE",AB_package);
    string_constant_76 = STATIC_STRING("hh-mm as an interval");
    mutate_global_property(Qhh_mm_as_interval,
	    make_date_format_1(Qhh_mm_as_interval_attribute,
	    Qhh_mm_as_interval_integer_attribute,
	    Qhh_mm_as_interval_float_attribute,string_constant_76),
	    Qdate_format_description);
    string_constant_77 = 
	    STATIC_STRING("1m1n83=5y1q1m9k83=7y1m9k83*5y1m9k83-*9y1m9k83*5y1m9k83=ay1m9k83-oy1m83=6y83-Xly1n83*Wy1o1m9k83-*9y1m9k83*5y1m9k83=ay1m9k83-oy83-");
    string_constant_78 = STATIC_STRING("Xly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_77,
	    string_constant_78)));
    string_constant_79 = 
	    STATIC_STRING("1m1o83-Xny83-*Ay1ll9k1p83-Xmy83-*Ay1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_79));
    string_constant_80 = 
	    STATIC_STRING("1l1o83-*Ay1n83Sy1m9k83-Py83*7y1n0nl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_and_filter_day_and_time_interval);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_80));
    string_constant_8 = STATIC_STRING("~S:~A~S");
    Qwrite_hh_mm_as_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-AS-INTERVAL-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_as_interval_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_as_interval_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_mm_as_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_as_interval_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_as_interval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_mm_as_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH-MM-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_mm_as_interval_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_mm_as_interval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_mm_as_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qhh_dot_hh_as_interval = STATIC_SYMBOL("HH.HH-AS-INTERVAL",AB_package);
    Qhh_dot_hh_as_interval_attribute = 
	    STATIC_SYMBOL("HH.HH-AS-INTERVAL-ATTRIBUTE",AB_package);
    Qhh_dot_hh_as_interval_integer_attribute = 
	    STATIC_SYMBOL("HH.HH-AS-INTERVAL-INTEGER-ATTRIBUTE",AB_package);
    Qhh_dot_hh_as_interval_float_attribute = 
	    STATIC_SYMBOL("HH.HH-AS-INTERVAL-FLOAT-ATTRIBUTE",AB_package);
    string_constant_81 = STATIC_STRING("hh.hh as an interval");
    mutate_global_property(Qhh_dot_hh_as_interval,
	    make_date_format_1(Qhh_dot_hh_as_interval_attribute,
	    Qhh_dot_hh_as_interval_integer_attribute,
	    Qhh_dot_hh_as_interval_float_attribute,string_constant_81),
	    Qdate_format_description);
    string_constant_82 = 
	    STATIC_STRING("1m1n83=5y1q1m9k83=7y1m9k83*5y1m9k83-*Dy1m9k83*5y1m9k83=ay1m9k83-oy1m83=6y83-Xuy1n83*Wy1o1m9k83-*Dy1m9k83*5y1m9k83=ay1m9k83-oy83-");
    string_constant_83 = STATIC_STRING("Xuy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_82,
	    string_constant_83)));
    string_constant_84 = 
	    STATIC_STRING("1m1o83-Xwy83-*Ey1ll9k1p83-Xvy83-*Ey1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_84));
    Qconvert_to_seconds = STATIC_SYMBOL("CONVERT-TO-SECONDS",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_to_seconds,
	    STATIC_FUNCTION(convert_to_seconds,NIL,FALSE,1,1));
    string_constant_85 = STATIC_STRING("1l1o83-*Ey9k1ll9l");
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(Qconvert_to_seconds);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    string_constant_9 = STATIC_STRING("~S.~A~S");
    Qwrite_hh_dot_hh_as_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH.HH-AS-INTERVAL-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_dot_hh_as_interval_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_dot_hh_as_interval_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_dot_hh_as_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH.HH-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_dot_hh_as_interval_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_dot_hh_as_interval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_hh_dot_hh_as_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-HH.HH-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_hh_dot_hh_as_interval_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhh_dot_hh_as_interval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_hh_dot_hh_as_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_ss_as_interval = STATIC_SYMBOL("MM-SS-AS-INTERVAL",AB_package);
    Qmm_ss_as_interval_attribute = 
	    STATIC_SYMBOL("MM-SS-AS-INTERVAL-ATTRIBUTE",AB_package);
    Qmm_ss_as_interval_integer_attribute = 
	    STATIC_SYMBOL("MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE",AB_package);
    Qmm_ss_as_interval_float_attribute = 
	    STATIC_SYMBOL("MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE",AB_package);
    string_constant_86 = STATIC_STRING("mm-ss as an interval");
    mutate_global_property(Qmm_ss_as_interval,
	    make_date_format_1(Qmm_ss_as_interval_attribute,
	    Qmm_ss_as_interval_integer_attribute,
	    Qmm_ss_as_interval_float_attribute,string_constant_86),
	    Qdate_format_description);
    string_constant_87 = 
	    STATIC_STRING("1m1n83=5y1q1m9k83=7y1m9k83*5y1m9k83-6sy1m9k83*5y1m9k83=ay1m9k83-oy1m83=6y83-f7y1n83*Wy1o1m9k83-6sy1m9k83*5y1m9k83=ay1m9k83-oy83-");
    string_constant_88 = STATIC_STRING("f7y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_87,
	    string_constant_88)));
    string_constant_89 = 
	    STATIC_STRING("1m1o83-f9y83-6ty1ll9k1p83-f8y83-6ty1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_89));
    string_constant_90 = 
	    STATIC_STRING("1l1o83-6ty1n83-ey1m9k83-Py83-ey1mnl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_and_filter_day_and_time_interval);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_90));
    Qwrite_mm_ss_as_interval_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-SS-AS-INTERVAL-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_ss_as_interval_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_ss_as_interval_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_ss_as_interval_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-SS-AS-INTERVAL-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_ss_as_interval_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_ss_as_interval_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_ss_as_interval_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-SS-AS-INTERVAL-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_ss_as_interval_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_ss_as_interval_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_ss_as_interval_float_attribute_from_slot),
	    Qslot_value_writer);
    Qtransform_input_phrase_into_universal_date = 
	    STATIC_SYMBOL("TRANSFORM-INPUT-PHRASE-INTO-UNIVERSAL-DATE",
	    AB_package);
    Qfilter_and_normalize_time_of_day = 
	    STATIC_SYMBOL("FILTER-AND-NORMALIZE-TIME-OF-DAY",AB_package);
    string_constant_91 = 
	    STATIC_STRING("1p1o839Ny1p83W1y1m9k9l833+y1m9k9l836Vy1nnlp9m1o8384y1p833+y1m9k9l83W1y1m9k9l836Vy1nlnp9m1o83AXy1p836Vy1m9k9l83W1y1m9k9l833+y1npn");
    string_constant_92 = 
	    STATIC_STRING("l9m1o83bwy1p833Oy1m9k83-Py833Ty1m9k83-Py9n1pln0p8k9o1o83bxy1n833Oy1m9k83-Py833Ty1pln008k9o");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qtransform_input_phrase_into_universal_date);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qfilter_and_normalize_time_of_day);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_91,
	    string_constant_92)));
    string_constant_93 = STATIC_STRING("1l1m83W1y83-ey");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_93));
    Qmm_dd_yyyy_hh_mm_ss = STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS",AB_package);
    Qmm_dd_yyyy_hh_mm_ss_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_ss_integer_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_ss_float_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE",AB_package);
    string_constant_94 = STATIC_STRING("mm-dd-yyyy-hh-mm-ss");
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss,
	    make_date_format_1(Qmm_dd_yyyy_hh_mm_ss_attribute,
	    Qmm_dd_yyyy_hh_mm_ss_integer_attribute,
	    Qmm_dd_yyyy_hh_mm_ss_float_attribute,string_constant_94),
	    Qdate_format_description);
    string_constant_95 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-f0y1m83=6y83-f0y1n83*Wy1m9k83-f0y83-f0y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_95));
    string_constant_96 = 
	    STATIC_STRING("1m1o83-f5y83-6ry1ll9k1p83-f4y83-6ry1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_96));
    Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp = 
	    STATIC_SYMBOL("TRANSFORM-DATE-PHRASE-AND-TIME-OF-DAY-INTO-G2-TIME-STAMP",
	    AB_package);
    string_constant_97 = STATIC_STRING("1l1o83-6ry1m839Ny83bwy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_97));
    string_constant_10 = STATIC_STRING("~A~S/~A~S/~S");
    string_constant_11 = STATIC_STRING(" ~A~S:~A~S:~A~S");
    Qwrite_mm_dd_yyyy_hh_mm_ss_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_float_attribute_from_slot),
	    Qslot_value_writer);
    Qdd_mm_yyyy_hh_mm_ss = STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS",AB_package);
    Qdd_mm_yyyy_hh_mm_ss_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_ss_integer_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_ss_float_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE",AB_package);
    string_constant_98 = STATIC_STRING("dd-mm-yyyy-hh-mm-ss");
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss,
	    make_date_format_1(Qdd_mm_yyyy_hh_mm_ss_attribute,
	    Qdd_mm_yyyy_hh_mm_ss_integer_attribute,
	    Qdd_mm_yyyy_hh_mm_ss_float_attribute,string_constant_98),
	    Qdate_format_description);
    string_constant_99 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-QHy1m83=6y83-QHy1n83*Wy1m9k83-QHy83-QHy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_99));
    string_constant_100 = 
	    STATIC_STRING("1m1o83-QMy83uky1ll9k1p83-QLy83uky1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_100));
    string_constant_101 = STATIC_STRING("1l1o83uky1m8384y83bwy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_101));
    Qwrite_dd_mm_yyyy_hh_mm_ss_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm_dd_hh_mm_ss = STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS",AB_package);
    Qyyyy_mm_dd_hh_mm_ss_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_ss_integer_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-INTEGER-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_ss_float_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-FLOAT-ATTRIBUTE",AB_package);
    string_constant_102 = STATIC_STRING("yyyy-mm-dd-hh-mm-ss");
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss,
	    make_date_format_1(Qyyyy_mm_dd_hh_mm_ss_attribute,
	    Qyyyy_mm_dd_hh_mm_ss_integer_attribute,
	    Qyyyy_mm_dd_hh_mm_ss_float_attribute,string_constant_102),
	    Qdate_format_description);
    string_constant_103 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83*+=y1m83=6y83*+=y1n83*Wy1m9k83*+=y83*+=y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_103));
    string_constant_104 = 
	    STATIC_STRING("1m1o83*+4y83-HOy1ll9k1p83*+3y83-HOy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_104));
    string_constant_105 = STATIC_STRING("1l1o83-HOy1m83AXy83bwy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_105));
    string_constant_12 = STATIC_STRING("~S/~A~S/~A~S");
    Qwrite_yyyy_mm_dd_hh_mm_ss_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_dd_yyyy_hh_mm_ss_am_pm = STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-AM-PM",
	    AB_package);
    Qmm_dd_yyyy_hh_mm_ss_am_pm_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qmm_dd_yyyy_hh_mm_ss_am_pm_float_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_106 = STATIC_STRING("mm-dd-yyyy-hh-mm-ss-am-pm");
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_am_pm,
	    make_date_format_1(Qmm_dd_yyyy_hh_mm_ss_am_pm_attribute,
	    Qmm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute,
	    Qmm_dd_yyyy_hh_mm_ss_am_pm_float_attribute,
	    string_constant_106),Qdate_format_description);
    string_constant_107 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-f1y1m83=6y83-f1y1n83*Wy1m9k83-f1y83-f1y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_107));
    string_constant_108 = 
	    STATIC_STRING("1m1o83-f3y83-6qy1ll9k1p83-f2y83-6qy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_108));
    string_constant_109 = STATIC_STRING("1l1o83-6qy1m839Ny83ADy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_109));
    string_constant_13 = STATIC_STRING(" ~S:~A~S:~A~S ~A");
    string_constant_14 = STATIC_STRING("a.m.");
    string_constant_15 = STATIC_STRING("p.m.");
    Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_ss_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qdd_mm_yyyy_hh_mm_ss_am_pm = STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-AM-PM",
	    AB_package);
    Qdd_mm_yyyy_hh_mm_ss_am_pm_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qdd_mm_yyyy_hh_mm_ss_am_pm_float_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_110 = STATIC_STRING("dd-mm-yyyy-hh-mm-ss-am-pm");
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_am_pm,
	    make_date_format_1(Qdd_mm_yyyy_hh_mm_ss_am_pm_attribute,
	    Qdd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute,
	    Qdd_mm_yyyy_hh_mm_ss_am_pm_float_attribute,
	    string_constant_110),Qdate_format_description);
    string_constant_111 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-QIy1m83=6y83-QIy1n83*Wy1m9k83-QIy83-QIy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_111));
    string_constant_112 = 
	    STATIC_STRING("1m1o83-QKy83ujy1ll9k1p83-QJy83ujy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_112));
    string_constant_113 = STATIC_STRING("1l1o83ujy1m8384y83ADy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_113));
    Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_ss_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_ss_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm_dd_hh_mm_ss_am_pm = STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-AM-PM",
	    AB_package);
    Qyyyy_mm_dd_hh_mm_ss_am_pm_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-AM-PM-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qyyyy_mm_dd_hh_mm_ss_am_pm_float_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_114 = STATIC_STRING("yyyy-mm-dd-hh-mm-ss-am-pm");
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_am_pm,
	    make_date_format_1(Qyyyy_mm_dd_hh_mm_ss_am_pm_attribute,
	    Qyyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute,
	    Qyyyy_mm_dd_hh_mm_ss_am_pm_float_attribute,
	    string_constant_114),Qdate_format_description);
    string_constant_115 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83*+0y1m83=6y83*+0y1n83*Wy1m9k83*+0y83*+0y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_115));
    string_constant_116 = 
	    STATIC_STRING("1m1o83*+2y83-HNy1ll9k1p83*+1y83-HNy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_116));
    string_constant_117 = STATIC_STRING("1l1o83-HNy1m83AXy83ADy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_117));
    Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-SS-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_ss_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_ss_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_dd_yyyy_hh_mm_am_pm = STATIC_SYMBOL("MM-DD-YYYY-HH-MM-AM-PM",
	    AB_package);
    Qmm_dd_yyyy_hh_mm_am_pm_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-AM-PM-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_am_pm_integer_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qmm_dd_yyyy_hh_mm_am_pm_float_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_118 = STATIC_STRING("mm-dd-yyyy-hh-mm-am-pm");
    mutate_global_property(Qmm_dd_yyyy_hh_mm_am_pm,
	    make_date_format_1(Qmm_dd_yyyy_hh_mm_am_pm_attribute,
	    Qmm_dd_yyyy_hh_mm_am_pm_integer_attribute,
	    Qmm_dd_yyyy_hh_mm_am_pm_float_attribute,string_constant_118),
	    Qdate_format_description);
    string_constant_119 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-exy1m83=6y83-exy1n83*Wy1m9k83-exy83-exy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_119));
    string_constant_120 = 
	    STATIC_STRING("1m1o83-f-y83-6oy1ll9k1p83-f+y83-6oy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_120));
    string_constant_121 = STATIC_STRING("1l1o83-6oy1m839Ny83ACy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_121));
    string_constant_16 = STATIC_STRING(" ~S:~A~S ~A");
    Qwrite_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qdd_mm_yyyy_hh_mm_am_pm = STATIC_SYMBOL("DD-MM-YYYY-HH-MM-AM-PM",
	    AB_package);
    Qdd_mm_yyyy_hh_mm_am_pm_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-AM-PM-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_am_pm_integer_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qdd_mm_yyyy_hh_mm_am_pm_float_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_122 = STATIC_STRING("dd-mm-yyyy-hh-mm-am-pm");
    mutate_global_property(Qdd_mm_yyyy_hh_mm_am_pm,
	    make_date_format_1(Qdd_mm_yyyy_hh_mm_am_pm_attribute,
	    Qdd_mm_yyyy_hh_mm_am_pm_integer_attribute,
	    Qdd_mm_yyyy_hh_mm_am_pm_float_attribute,string_constant_122),
	    Qdate_format_description);
    string_constant_123 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-QCy1m83=6y83-QCy1n83*Wy1m9k83-QCy83-QCy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_123));
    string_constant_124 = 
	    STATIC_STRING("1m1o83-QEy83uhy1ll9k1p83-QDy83uhy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_124));
    string_constant_125 = STATIC_STRING("1l1o83uhy1m8384y83ACy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_125));
    Qwrite_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm_dd_hh_mm_am_pm = STATIC_SYMBOL("YYYY-MM-DD-HH-MM-AM-PM",
	    AB_package);
    Qyyyy_mm_dd_hh_mm_am_pm_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-AM-PM-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_am_pm_integer_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-AM-PM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qyyyy_mm_dd_hh_mm_am_pm_float_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-AM-PM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_126 = STATIC_STRING("yyyy-mm-dd-hh-mm-am-pm");
    mutate_global_property(Qyyyy_mm_dd_hh_mm_am_pm,
	    make_date_format_1(Qyyyy_mm_dd_hh_mm_am_pm_attribute,
	    Qyyyy_mm_dd_hh_mm_am_pm_integer_attribute,
	    Qyyyy_mm_dd_hh_mm_am_pm_float_attribute,string_constant_126),
	    Qdate_format_description);
    string_constant_127 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-xwy1m83=6y83-xwy1n83*Wy1m9k83-xwy83-xwy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_127));
    string_constant_128 = 
	    STATIC_STRING("1m1o83*++y83-HLy1ll9k1p83-xxy83-HLy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_128));
    string_constant_129 = STATIC_STRING("1l1o83-HLy1m83AXy83ACy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_129));
    Qwrite_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-AM-PM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_am_pm_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-AM-PM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_am_pm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-AM-PM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_am_pm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_am_pm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_dd_yyyy_hh_mm = STATIC_SYMBOL("MM-DD-YYYY-HH-MM",AB_package);
    Qmm_dd_yyyy_hh_mm_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_integer_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-INTEGER-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_hh_mm_float_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-HH-MM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_130 = STATIC_STRING("mm-dd-yyyy-hh-mm");
    mutate_global_property(Qmm_dd_yyyy_hh_mm,
	    make_date_format_1(Qmm_dd_yyyy_hh_mm_attribute,
	    Qmm_dd_yyyy_hh_mm_integer_attribute,
	    Qmm_dd_yyyy_hh_mm_float_attribute,string_constant_130),
	    Qdate_format_description);
    string_constant_131 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-ewy1m83=6y83-ewy1n83*Wy1m9k83-ewy83-ewy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_131));
    string_constant_132 = 
	    STATIC_STRING("1m1o83-f=y83-6py1ll9k1p83-f*y83-6py1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_132));
    string_constant_133 = STATIC_STRING("1l1o83-6py1m839Ny83bxy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_133));
    string_constant_17 = STATIC_STRING(" ~A~S:~A~S");
    Qwrite_mm_dd_yyyy_hh_mm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_hh_mm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_hh_mm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_hh_mm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_hh_mm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qdd_mm_yyyy_hh_mm = STATIC_SYMBOL("DD-MM-YYYY-HH-MM",AB_package);
    Qdd_mm_yyyy_hh_mm_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_integer_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-INTEGER-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_hh_mm_float_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-HH-MM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_134 = STATIC_STRING("dd-mm-yyyy-hh-mm");
    mutate_global_property(Qdd_mm_yyyy_hh_mm,
	    make_date_format_1(Qdd_mm_yyyy_hh_mm_attribute,
	    Qdd_mm_yyyy_hh_mm_integer_attribute,
	    Qdd_mm_yyyy_hh_mm_float_attribute,string_constant_134),
	    Qdate_format_description);
    string_constant_135 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-QBy1m83=6y83-QBy1n83*Wy1m9k83-QBy83-QBy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_135));
    string_constant_136 = 
	    STATIC_STRING("1m1o83-QGy83uiy1ll9k1p83-QFy83uiy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_136));
    string_constant_137 = STATIC_STRING("1l1o83uiy1m8384y83bxy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_137));
    Qwrite_dd_mm_yyyy_hh_mm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_hh_mm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_hh_mm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_hh_mm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_hh_mm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm_dd_hh_mm = STATIC_SYMBOL("YYYY-MM-DD-HH-MM",AB_package);
    Qyyyy_mm_dd_hh_mm_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_integer_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-INTEGER-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_hh_mm_float_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-HH-MM-FLOAT-ATTRIBUTE",AB_package);
    string_constant_138 = STATIC_STRING("yyyy-mm-dd-hh-mm");
    mutate_global_property(Qyyyy_mm_dd_hh_mm,
	    make_date_format_1(Qyyyy_mm_dd_hh_mm_attribute,
	    Qyyyy_mm_dd_hh_mm_integer_attribute,
	    Qyyyy_mm_dd_hh_mm_float_attribute,string_constant_138),
	    Qdate_format_description);
    string_constant_139 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-xvy1m83=6y83-xvy1n83*Wy1m9k83-xvy83-xvy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_139));
    string_constant_140 = 
	    STATIC_STRING("1m1o83*+*y83-HMy1ll9k1p83*+-y83-HMy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_140));
    string_constant_141 = STATIC_STRING("1l1o83-HMy1m83AXy83bxy1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_141));
    Qwrite_yyyy_mm_dd_hh_mm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_hh_mm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-HH-MM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_hh_mm_float_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_hh_mm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_hh_mm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm_dd = STATIC_SYMBOL("YYYY-MM-DD",AB_package);
    Qyyyy_mm_dd_attribute = STATIC_SYMBOL("YYYY-MM-DD-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_integer_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-INTEGER-ATTRIBUTE",AB_package);
    Qyyyy_mm_dd_float_attribute = 
	    STATIC_SYMBOL("YYYY-MM-DD-FLOAT-ATTRIBUTE",AB_package);
    string_constant_142 = STATIC_STRING("yyyy-mm-dd");
    mutate_global_property(Qyyyy_mm_dd,
	    make_date_format_1(Qyyyy_mm_dd_attribute,
	    Qyyyy_mm_dd_integer_attribute,Qyyyy_mm_dd_float_attribute,
	    string_constant_142),Qdate_format_description);
    string_constant_143 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-xty1m83=6y83-xty1n83*Wy1m9k83-xty83-xty");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_143));
    string_constant_144 = 
	    STATIC_STRING("1m1o83*+5y83-HKy1ll9k1p83-xuy83-HKy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_144));
    Qadd_zero_time_to_date_list = 
	    STATIC_SYMBOL("ADD-ZERO-TIME-TO-DATE-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qadd_zero_time_to_date_list,
	    STATIC_FUNCTION(add_zero_time_to_date_list,NIL,FALSE,1,1));
    string_constant_145 = STATIC_STRING("1l1p83-HKy83AXy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qadd_zero_time_to_date_list);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_145));
    Qwrite_yyyy_mm_dd_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qyyyy_mm_dd_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_dd_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-DD-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_dd_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qyyyy_mm_dd_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_dd_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_dd_yyyy = STATIC_SYMBOL("MM-DD-YYYY",AB_package);
    Qmm_dd_yyyy_attribute = STATIC_SYMBOL("MM-DD-YYYY-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_integer_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-INTEGER-ATTRIBUTE",AB_package);
    Qmm_dd_yyyy_float_attribute = 
	    STATIC_SYMBOL("MM-DD-YYYY-FLOAT-ATTRIBUTE",AB_package);
    string_constant_146 = STATIC_STRING("mm-dd-yyyy");
    mutate_global_property(Qmm_dd_yyyy,
	    make_date_format_1(Qmm_dd_yyyy_attribute,
	    Qmm_dd_yyyy_integer_attribute,Qmm_dd_yyyy_float_attribute,
	    string_constant_146),Qdate_format_description);
    string_constant_147 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-euy1m83=6y83-euy1n83*Wy1m9k83-euy83-euy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_147));
    string_constant_148 = 
	    STATIC_STRING("1m1o83-f6y83-6ny1ll9k1p83-evy83-6ny1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_148));
    string_constant_149 = STATIC_STRING("1l1p83-6ny839Ny1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qadd_zero_time_to_date_list);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_149));
    Qwrite_mm_dd_yyyy_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qmm_dd_yyyy_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_dd_yyyy_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-DD-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_dd_yyyy_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmm_dd_yyyy_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_dd_yyyy_float_attribute_from_slot),
	    Qslot_value_writer);
    Qdd_mm_yyyy = STATIC_SYMBOL("DD-MM-YYYY",AB_package);
    Qdd_mm_yyyy_attribute = STATIC_SYMBOL("DD-MM-YYYY-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_integer_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-INTEGER-ATTRIBUTE",AB_package);
    Qdd_mm_yyyy_float_attribute = 
	    STATIC_SYMBOL("DD-MM-YYYY-FLOAT-ATTRIBUTE",AB_package);
    string_constant_150 = STATIC_STRING("dd-mm-yyyy");
    mutate_global_property(Qdd_mm_yyyy,
	    make_date_format_1(Qdd_mm_yyyy_attribute,
	    Qdd_mm_yyyy_integer_attribute,Qdd_mm_yyyy_float_attribute,
	    string_constant_150),Qdate_format_description);
    string_constant_151 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-Q9y1m83=6y83-Q9y1n83*Wy1m9k83-Q9y83-Q9y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_151));
    string_constant_152 = 
	    STATIC_STRING("1m1o83-QNy83ugy1ll9k1p83-QAy83ugy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_152));
    string_constant_153 = STATIC_STRING("1l1p83ugy8384y1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qadd_zero_time_to_date_list);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_153));
    Qwrite_dd_mm_yyyy_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qdd_mm_yyyy_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_integer_attribute_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_dd_mm_yyyy_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-DD-MM-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_float_attribute_from_slot,
	    STATIC_FUNCTION(write_dd_mm_yyyy_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdd_mm_yyyy_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_dd_mm_yyyy_float_attribute_from_slot),
	    Qslot_value_writer);
    Qmm_yyyy = STATIC_SYMBOL("MM-YYYY",AB_package);
    Qmm_yyyy_attribute = STATIC_SYMBOL("MM-YYYY-ATTRIBUTE",AB_package);
    Qmm_yyyy_integer_attribute = STATIC_SYMBOL("MM-YYYY-INTEGER-ATTRIBUTE",
	    AB_package);
    Qmm_yyyy_float_attribute = STATIC_SYMBOL("MM-YYYY-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_154 = STATIC_STRING("mm-yyyy");
    mutate_global_property(Qmm_yyyy,make_date_format_1(Qmm_yyyy_attribute,
	    Qmm_yyyy_integer_attribute,Qmm_yyyy_float_attribute,
	    string_constant_154),Qdate_format_description);
    string_constant_155 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-fCy1m83=6y83-fCy1n83*Wy1m9k83-fCy83-fCy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_155));
    string_constant_156 = 
	    STATIC_STRING("1m1o83-fEy83-6uy1ll9k1p83-fDy83-6uy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_156));
    Qset_day_of_date_to_1 = STATIC_SYMBOL("SET-DAY-OF-DATE-TO-1",AB_package);
    SET_SYMBOL_FUNCTION(Qset_day_of_date_to_1,
	    STATIC_FUNCTION(set_day_of_date_to_1,NIL,FALSE,1,1));
    Qadd_zero_time_to_date = STATIC_SYMBOL("ADD-ZERO-TIME-TO-DATE",AB_package);
    SET_SYMBOL_FUNCTION(Qadd_zero_time_to_date,
	    STATIC_FUNCTION(add_zero_time_to_date,NIL,FALSE,1,1));
    string_constant_157 = 
	    STATIC_STRING("1l1r83-6uy1n83W1y1m9k9l836Vy1n833+yln9m9n9o9p");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qset_day_of_date_to_1);
    push_optimized_constant(Qtransform_input_phrase_into_universal_date);
    push_optimized_constant(Qadd_zero_time_to_date);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_157));
    string_constant_18 = STATIC_STRING("~A~S/~S");
    Qwrite_mm_yyyy_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-YYYY-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_yyyy_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_yyyy_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmm_yyyy_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_yyyy_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_yyyy_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-YYYY-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_yyyy_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_yyyy_integer_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmm_yyyy_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_yyyy_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_mm_yyyy_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-MM-YYYY-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_mm_yyyy_float_attribute_from_slot,
	    STATIC_FUNCTION(write_mm_yyyy_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmm_yyyy_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_mm_yyyy_float_attribute_from_slot),
	    Qslot_value_writer);
    Qyyyy_mm = STATIC_SYMBOL("YYYY-MM",AB_package);
    Qyyyy_mm_attribute = STATIC_SYMBOL("YYYY-MM-ATTRIBUTE",AB_package);
    Qyyyy_mm_integer_attribute = STATIC_SYMBOL("YYYY-MM-INTEGER-ATTRIBUTE",
	    AB_package);
    Qyyyy_mm_float_attribute = STATIC_SYMBOL("YYYY-MM-FLOAT-ATTRIBUTE",
	    AB_package);
    string_constant_158 = STATIC_STRING("yyyy-mm");
    mutate_global_property(Qyyyy_mm,make_date_format_1(Qyyyy_mm_attribute,
	    Qyyyy_mm_integer_attribute,Qyyyy_mm_float_attribute,
	    string_constant_158),Qdate_format_description);
    string_constant_159 = 
	    STATIC_STRING("1m1n83=5y1n1m9k83=7y1m9k83*5y1m9k83-xsy1m83=6y83-xsy1n83*Wy1m9k83-xsy83-xsy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_159));
    string_constant_160 = 
	    STATIC_STRING("1m1o83*+7y83-HJy1ll9k1p83*+6y83-HJy1ll9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qcar);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_160));
    string_constant_161 = 
	    STATIC_STRING("1l1r83-HJy1n836Vy1m9k9l83W1y1n833+ynl9m9n9o9p");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qset_day_of_date_to_1);
    push_optimized_constant(Qtransform_input_phrase_into_universal_date);
    push_optimized_constant(Qadd_zero_time_to_date);
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_161));
    string_constant_19 = STATIC_STRING("~S/~A~S");
    Qwrite_yyyy_mm_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qyyyy_mm_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_integer_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-INTEGER-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_integer_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_integer_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qyyyy_mm_integer_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_integer_attribute_from_slot),
	    Qslot_value_writer);
    Qwrite_yyyy_mm_float_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-YYYY-MM-FLOAT-ATTRIBUTE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_yyyy_mm_float_attribute_from_slot,
	    STATIC_FUNCTION(write_yyyy_mm_float_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qyyyy_mm_float_attribute,
	    SYMBOL_FUNCTION(Qwrite_yyyy_mm_float_attribute_from_slot),
	    Qslot_value_writer);
    Qtruth_value_attribute = STATIC_SYMBOL("TRUTH-VALUE-ATTRIBUTE",AB_package);
    Qwrite_truth_value_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-TRUTH-VALUE-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_truth_value_attribute_from_slot,
	    STATIC_FUNCTION(write_truth_value_attribute_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtruth_value_attribute,
	    SYMBOL_FUNCTION(Qwrite_truth_value_attribute_from_slot),
	    Qslot_value_writer);
    Qsymbol_attribute = STATIC_SYMBOL("SYMBOL-ATTRIBUTE",AB_package);
    Qwrite_symbol_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-SYMBOL-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_symbol_attribute_from_slot,
	    STATIC_FUNCTION(write_symbol_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsymbol_attribute,
	    SYMBOL_FUNCTION(Qwrite_symbol_attribute_from_slot),
	    Qslot_value_writer);
    Qtext_attribute = STATIC_SYMBOL("TEXT-ATTRIBUTE",AB_package);
    Qwrite_text_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-TEXT-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_text_attribute_from_slot,
	    STATIC_FUNCTION(write_text_attribute_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qtext_attribute,
	    SYMBOL_FUNCTION(Qwrite_text_attribute_from_slot),
	    Qslot_value_writer);
    Qfree_text_attribute = STATIC_SYMBOL("FREE-TEXT-ATTRIBUTE",AB_package);
    Qwrite_free_text_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-FREE-TEXT-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_free_text_attribute_from_slot,
	    STATIC_FUNCTION(write_free_text_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qfree_text_attribute,
	    SYMBOL_FUNCTION(Qwrite_free_text_attribute_from_slot),
	    Qslot_value_writer);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_20 = STATIC_STRING("****");
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    string_constant_21 = STATIC_STRING(" *");
    string_constant_22 = STATIC_STRING("the ~(~A~) ");
    string_constant_162 = 
	    STATIC_STRING("1p1m83-qy83-0=y1m83*iy83-qy1m83*my83-6y1m83E1y1m9k83Py1m83E1y83-Hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_162));
    string_constant_163 = STATIC_STRING("1l1m83AQy83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    string_constant_23 = 
	    STATIC_STRING("A UUID (as represented internally) must be a text ~D characters long, but ~\n       this is ~D characters long");
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Quuid),
	    Qtype_specification_simple_expansion,Qtext);
    define_type_specification_explicit_complex_type(Quuid,Qtext);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Quuid);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    uuid_evaluation_setter_1 = STATIC_FUNCTION(uuid_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Quuid,uuid_evaluation_setter_1);
    uuid_evaluation_getter_1 = STATIC_FUNCTION(uuid_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quuid,
	    uuid_evaluation_getter_1);
    Qreject_truth_value_as_symbol = 
	    STATIC_SYMBOL("REJECT-TRUTH-VALUE-AS-SYMBOL",AB_package);
    string_constant_164 = 
	    STATIC_STRING("13Fy1m83-bBy83t*y1o83-bBy830Tyl9k1m83-0=y1m9l83Zy1m83-0=y83-bBy1m83-Q*y83-bBy1m83-h9y83-Hy1m83-UEy9m1m83-aGy83Sy1m83-rYy830Ty1m8");
    string_constant_165 = 
	    STATIC_STRING("3-sQy83-Uy1m83-aUy831Ny1m83-aVy831Ny1m83-aWy83-oy1m83-tDy83-F0y1m83-tEy83-F1y1m83-tFy832ny1m83-QPy830my1m83-QQy9m1m83-QRy83Sy");
    clear_optimized_constants();
    push_optimized_constant(Qreject_truth_value_as_symbol);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_164,
	    string_constant_165)));
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    string_constant_24 = STATIC_STRING("no simulation formula yet");
    string_constant_25 = STATIC_STRING(", but has specific subtable");
    Qnon_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",AB_package);
    Qdiscrete_state = STATIC_SYMBOL("DISCRETE-STATE",AB_package);
    Qcontinuous_state = STATIC_SYMBOL("CONTINUOUS-STATE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qdiscrete_state,
	    Qcontinuous_state);
    string_constant_26 = STATIC_STRING(", with initial value ");
    Quse_initial_value_expression_in_generic_simulation_formula = 
	    STATIC_SYMBOL("USE-INITIAL-VALUE-EXPRESSION-IN-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    string_constant_27 = STATIC_STRING("given by an expression");
    string_constant_28 = STATIC_STRING(", and has specific subtable");
    Qsimulation_frame_qm = STATIC_SYMBOL("SIMULATION-FRAME\?",AB_package);
    Qwrite_simulation_frame_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATION-FRAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulation_frame_qm_from_slot,
	    STATIC_FUNCTION(write_simulation_frame_qm_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qsimulation_frame_qm,
	    SYMBOL_FUNCTION(Qwrite_simulation_frame_qm_from_slot),
	    Qslot_value_writer);
    Qnon_default_number_qm = STATIC_SYMBOL("NON-DEFAULT-NUMBER\?",AB_package);
    Qcompile_non_default_number_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-NON-DEFAULT-NUMBER\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_non_default_number_qm_for_slot,
	    STATIC_FUNCTION(compile_non_default_number_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qnon_default_number_qm,
	    SYMBOL_FUNCTION(Qcompile_non_default_number_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnon_default_number_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_29 = STATIC_STRING("default");
    Qwrite_non_default_number_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-NON-DEFAULT-NUMBER\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_non_default_number_qm_from_slot,
	    STATIC_FUNCTION(write_non_default_number_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qnon_default_number_qm,
	    SYMBOL_FUNCTION(Qwrite_non_default_number_qm_from_slot),
	    Qslot_value_writer);
    Qcompile_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_attribute_for_slot,
	    STATIC_FUNCTION(compile_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qattribute,
	    SYMBOL_FUNCTION(Qcompile_attribute_for_slot),Qslot_value_compiler);
    mutate_global_property(Qattribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qread_only_attribute = STATIC_SYMBOL("READ-ONLY-ATTRIBUTE",AB_package);
    Qcompile_read_only_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-READ-ONLY-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_read_only_attribute_for_slot,
	    STATIC_FUNCTION(compile_read_only_attribute_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qread_only_attribute,
	    SYMBOL_FUNCTION(Qcompile_read_only_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qread_only_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_76 = STATIC_CONS(Qno_item,Qnil);
    list_constant_77 = STATIC_CONS(Qsequence,Qnil);
    list_constant_78 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_3 = STATIC_LIST((SI_Long)8L,Qab_or,list_constant_76,
	    Qsymbol,Qtruth_value,Qnumber,Qtext,list_constant_77,
	    list_constant_78);
    set_property_value_function(get_symbol_properties_function(Qattribute),
	    Qtype_specification_simple_expansion,list_constant_3);
    define_type_specification_explicit_complex_type(Qattribute,
	    list_constant_3);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qattribute);
    attribute_evaluation_setter_1 = 
	    STATIC_FUNCTION(attribute_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qattribute,
	    attribute_evaluation_setter_1);
    attribute_evaluation_getter_1 = 
	    STATIC_FUNCTION(attribute_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qattribute,
	    attribute_evaluation_getter_1);
    Qwrite_read_only_attribute_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-ATTRIBUTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_attribute_from_slot,
	    STATIC_FUNCTION(write_read_only_attribute_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qread_only_attribute,
	    SYMBOL_FUNCTION(Qwrite_read_only_attribute_from_slot),
	    Qslot_value_writer);
    list_constant_56 = STATIC_LIST((SI_Long)6L,Qab_or,list_constant_76,
	    Qsymbol,Qtruth_value,Qnumber,Qtext);
    set_property_value_function(get_symbol_properties_function(Qread_only_attribute),
	    Qtype_specification_simple_expansion,list_constant_56);
    define_type_specification_explicit_complex_type(Qread_only_attribute,
	    list_constant_56);
    read_only_attribute_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_attribute_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_attribute,
	    read_only_attribute_evaluation_getter_1);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    Qcompile_item_or_datum_or_no_item_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-ITEM-OR-DATUM-OR-NO-ITEM-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_item_or_datum_or_no_item_attribute_for_slot,
	    STATIC_FUNCTION(compile_item_or_datum_or_no_item_attribute_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qitem_or_datum_or_no_item_attribute,
	    SYMBOL_FUNCTION(Qcompile_item_or_datum_or_no_item_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qitem_or_datum_or_no_item_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_item_or_datum_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-ITEM-OR-DATUM-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_item_or_datum_attribute_for_slot,
	    STATIC_FUNCTION(compile_item_or_datum_attribute_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qitem_or_datum_attribute,
	    SYMBOL_FUNCTION(Qcompile_item_or_datum_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qitem_or_datum_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_datum_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-DATUM-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_datum_attribute_for_slot,
	    STATIC_FUNCTION(compile_datum_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qdatum_attribute,
	    SYMBOL_FUNCTION(Qcompile_datum_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdatum_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_number_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-NUMBER-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_number_attribute_for_slot,
	    STATIC_FUNCTION(compile_number_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qnumber_attribute,
	    SYMBOL_FUNCTION(Qcompile_number_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnumber_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_float_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-FLOAT-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_float_attribute_for_slot,
	    STATIC_FUNCTION(compile_float_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfloat_attribute,
	    SYMBOL_FUNCTION(Qcompile_float_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfloat_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_integer_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTEGER-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_integer_attribute_for_slot,
	    STATIC_FUNCTION(compile_integer_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinteger_attribute,
	    SYMBOL_FUNCTION(Qcompile_integer_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinteger_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_symbol_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-SYMBOL-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_symbol_attribute_for_slot,
	    STATIC_FUNCTION(compile_symbol_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qsymbol_attribute,
	    SYMBOL_FUNCTION(Qcompile_symbol_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsymbol_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_text_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-TEXT-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_text_attribute_for_slot,
	    STATIC_FUNCTION(compile_text_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qtext_attribute,
	    SYMBOL_FUNCTION(Qcompile_text_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtext_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_free_text_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-FREE-TEXT-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_free_text_attribute_for_slot,
	    STATIC_FUNCTION(compile_free_text_attribute_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qfree_text_attribute,
	    SYMBOL_FUNCTION(Qcompile_free_text_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfree_text_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_truth_value_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-TRUTH-VALUE-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_truth_value_attribute_for_slot,
	    STATIC_FUNCTION(compile_truth_value_attribute_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qtruth_value_attribute,
	    SYMBOL_FUNCTION(Qcompile_truth_value_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtruth_value_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_structure_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-STRUCTURE-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_structure_attribute_for_slot,
	    STATIC_FUNCTION(compile_structure_attribute_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qstructure_attribute,
	    SYMBOL_FUNCTION(Qcompile_structure_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qstructure_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_sequence_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-SEQUENCE-ATTRIBUTE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_sequence_attribute_for_slot,
	    STATIC_FUNCTION(compile_sequence_attribute_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qsequence_attribute,
	    SYMBOL_FUNCTION(Qcompile_sequence_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsequence_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qevaluation_value_constant_allowing_items = 
	    STATIC_SYMBOL("EVALUATION-VALUE-CONSTANT-ALLOWING-ITEMS",
	    AB_package);
    Qcompile_evaluation_value_constant_allowing_items_for_slot = 
	    STATIC_SYMBOL("COMPILE-EVALUATION-VALUE-CONSTANT-ALLOWING-ITEMS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_evaluation_value_constant_allowing_items_for_slot,
	    STATIC_FUNCTION(compile_evaluation_value_constant_allowing_items_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qevaluation_value_constant_allowing_items,
	    SYMBOL_FUNCTION(Qcompile_evaluation_value_constant_allowing_items_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qevaluation_value_constant_allowing_items,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_ddd_dot_dddd_format_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-DDD.DDDD-FORMAT-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_attribute_for_slot,
	    STATIC_FUNCTION(compile_ddd_dot_dddd_format_attribute_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qddd_dot_dddd_format_attribute,
	    SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qddd_dot_dddd_format_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_ddd_dot_dddd_format_float_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-DDD.DDDD-FORMAT-FLOAT-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_float_attribute_for_slot,
	    STATIC_FUNCTION(compile_ddd_dot_dddd_format_float_attribute_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qddd_dot_dddd_format_float_attribute,
	    SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_float_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qddd_dot_dddd_format_float_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_ddd_dot_dddd_format_integer_attribute_for_slot = 
	    STATIC_SYMBOL("COMPILE-DDD.DDDD-FORMAT-INTEGER-ATTRIBUTE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_integer_attribute_for_slot,
	    STATIC_FUNCTION(compile_ddd_dot_dddd_format_integer_attribute_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qddd_dot_dddd_format_integer_attribute,
	    SYMBOL_FUNCTION(Qcompile_ddd_dot_dddd_format_integer_attribute_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qddd_dot_dddd_format_integer_attribute,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_166 = 
	    STATIC_STRING("13Hy1n831ry1m9k83-oy832Ky1n831ry1m1m9k831Ay1m9k83A*y832ny1n831ry1m1m9k83o=y1m9k83*ly83-hy1m831ry1m9k83-2y1m831ry1m9k83Gy1m831ry1");
    string_constant_167 = 
	    STATIC_STRING("m9k83Sy1m831ry1m9k83=By1m831ry1m9k9l1n831ry1m1m9k83-9by1m9k83-Hy83-9cy1n831ry1m9k830my83-Hy1m831ry839Ty1m831ry839hy1n83-QWy1m1m9");
    string_constant_168 = 
	    STATIC_STRING("k831Ay1m9k83A*y832ny1n83-QWy1m1m9k83o=y1m9k83*ly83-hy1m83-QWy1m9k83-2y1m83-QWy1m9k83Gy1m83-QWy1m9k83Sy1m83-QWy1m9k83=By1m83-QWy1");
    string_constant_169 = 
	    STATIC_STRING("m9k9l1n83-QWy1m1m9k83-9by1m9k83-Hy83-9cy1n83-QWy1m9k830my83-Hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_166,
	    string_constant_167,string_constant_168,string_constant_169)));
    set_property_value_function(get_symbol_properties_function(Qsymbol),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qsymbol,Qsymbol);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,Qsymbol);
    symbol_evaluation_setter_1 = STATIC_FUNCTION(symbol_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsymbol,
	    symbol_evaluation_setter_1);
    symbol_evaluation_getter_1 = STATIC_FUNCTION(symbol_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsymbol,
	    symbol_evaluation_getter_1);
    Qread_only_symbol_data_type = 
	    STATIC_SYMBOL("READ-ONLY-SYMBOL-DATA-TYPE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qread_only_symbol_data_type),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_79 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_80 = STATIC_CONS(Qmember,list_constant_79);
    define_type_specification_explicit_complex_type(Qread_only_symbol_data_type,
	    list_constant_80);
    read_only_symbol_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_symbol_data_type_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_symbol_data_type,
	    read_only_symbol_data_type_evaluation_getter_1);
    Qread_only_text_data_type = STATIC_SYMBOL("READ-ONLY-TEXT-DATA-TYPE",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qread_only_text_data_type),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_81 = STATIC_CONS(Qtext,Qnil);
    list_constant_82 = STATIC_CONS(Qmember,list_constant_81);
    define_type_specification_explicit_complex_type(Qread_only_text_data_type,
	    list_constant_82);
    read_only_text_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_text_data_type_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_text_data_type,
	    read_only_text_data_type_evaluation_getter_1);
    Qread_only_truth_value_data_type = 
	    STATIC_SYMBOL("READ-ONLY-TRUTH-VALUE-DATA-TYPE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qread_only_truth_value_data_type),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qmember,Qtruth_value);
    define_type_specification_explicit_complex_type(Qread_only_truth_value_data_type,
	    list_constant_83);
    read_only_truth_value_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_truth_value_data_type_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_truth_value_data_type,
	    read_only_truth_value_data_type_evaluation_getter_1);
    Qfloat_data_type = STATIC_SYMBOL("FLOAT-DATA-TYPE",AB_package);
    list_constant_84 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_79);
    set_property_value_function(get_symbol_properties_function(Qfloat_data_type),
	    Qtype_specification_simple_expansion,list_constant_84);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Qmember,Qfloat,Qtime_stamp);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_85,
	    list_constant_79);
    define_type_specification_explicit_complex_type(Qfloat_data_type,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,Qfloat_data_type);
    Qneutral_unit_of_measure = STATIC_SYMBOL("NEUTRAL-UNIT-OF-MEASURE",
	    AB_package);
    Qplural_unit_of_measure = STATIC_SYMBOL("PLURAL-UNIT-OF-MEASURE",
	    AB_package);
    string_constant_30 = 
	    STATIC_STRING("You must use an appropriate G2-defined type or a KB-defined unit of measure.");
    float_data_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(float_data_type_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfloat_data_type,
	    float_data_type_evaluation_setter_1);
    float_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(float_data_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfloat_data_type,
	    float_data_type_evaluation_getter_1);
    Qinteger_data_type = STATIC_SYMBOL("INTEGER-DATA-TYPE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinteger_data_type),
	    Qtype_specification_simple_expansion,list_constant_84);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant_86 = STATIC_LIST((SI_Long)3L,Qmember,Qinteger,Qinterval);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_86,
	    list_constant_79);
    define_type_specification_explicit_complex_type(Qinteger_data_type,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qinteger_data_type);
    integer_data_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(integer_data_type_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinteger_data_type,
	    integer_data_type_evaluation_setter_1);
    integer_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(integer_data_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinteger_data_type,
	    integer_data_type_evaluation_getter_1);
    Qlong_data_type = STATIC_SYMBOL("LONG-DATA-TYPE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlong_data_type),
	    Qtype_specification_simple_expansion,list_constant_84);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    list_constant_87 = STATIC_CONS(Qinterval,Qnil);
    list_constant_88 = STATIC_LIST_STAR((SI_Long)3L,Qmember,Qlong,
	    list_constant_87);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_88,list_constant_79);
    define_type_specification_explicit_complex_type(Qlong_data_type,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qlong_data_type);
    string_constant_31 = 
	    STATIC_STRING("int 64 data type is experimental and does not support units of measure");
    long_data_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(long_data_type_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlong_data_type,
	    long_data_type_evaluation_setter_1);
    long_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(long_data_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlong_data_type,
	    long_data_type_evaluation_getter_1);
    Qquantitative_data_type = STATIC_SYMBOL("QUANTITATIVE-DATA-TYPE",
	    AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)4L,Qab_or,Qnil,Qnil,Qnil);
    set_property_value_function(get_symbol_properties_function(Qquantitative_data_type),
	    Qtype_specification_simple_expansion,list_constant_89);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qmember,Qquantity);
    list_constant_12 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_90,
	    list_constant_5,list_constant_7);
    define_type_specification_explicit_complex_type(Qquantitative_data_type,
	    list_constant_12);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnamed,Qquantitative_data_type);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    quantitative_data_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(quantitative_data_type_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qquantitative_data_type,
	    quantitative_data_type_evaluation_setter_1);
    quantitative_data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(quantitative_data_type_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qquantitative_data_type,
	    quantitative_data_type_evaluation_getter_1);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    list_constant_91 = STATIC_LIST((SI_Long)2L,Qnil,Qnil);
    list_constant_92 = STATIC_CONS(Qab_or,list_constant_91);
    set_property_value_function(get_symbol_properties_function(Qdata_type),
	    Qtype_specification_simple_expansion,list_constant_92);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_93 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_94 = STATIC_LIST_STAR((SI_Long)5L,Qmember,Qvalue,Qsymbol,
	    Qtext,list_constant_93);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_11,
	    list_constant_94);
    define_type_specification_explicit_complex_type(Qdata_type,
	    list_constant_14);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qnamed,Qdata_type);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    data_type_evaluation_setter_1 = 
	    STATIC_FUNCTION(data_type_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdata_type,
	    data_type_evaluation_setter_1);
    data_type_evaluation_getter_1 = 
	    STATIC_FUNCTION(data_type_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdata_type,
	    data_type_evaluation_getter_1);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qcompile_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-DATA-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_data_type_for_slot,
	    STATIC_FUNCTION(compile_data_type_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qdata_type,
	    SYMBOL_FUNCTION(Qcompile_data_type_for_slot),Qslot_value_compiler);
    mutate_global_property(Qdata_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_data_type_from_slot = STATIC_SYMBOL("WRITE-DATA-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_data_type_from_slot,
	    STATIC_FUNCTION(write_data_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qdata_type,
	    SYMBOL_FUNCTION(Qwrite_data_type_from_slot),Qslot_value_writer);
    Qcompile_quantitative_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUANTITATIVE-DATA-TYPE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quantitative_data_type_for_slot,
	    STATIC_FUNCTION(compile_quantitative_data_type_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qquantitative_data_type,
	    SYMBOL_FUNCTION(Qcompile_quantitative_data_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qquantitative_data_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_float_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-FLOAT-DATA-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_float_data_type_for_slot,
	    STATIC_FUNCTION(compile_float_data_type_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfloat_data_type,
	    SYMBOL_FUNCTION(Qcompile_float_data_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfloat_data_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_integer_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTEGER-DATA-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_integer_data_type_for_slot,
	    STATIC_FUNCTION(compile_integer_data_type_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinteger_data_type,
	    SYMBOL_FUNCTION(Qcompile_integer_data_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinteger_data_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_long_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-LONG-DATA-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_long_data_type_for_slot,
	    STATIC_FUNCTION(compile_long_data_type_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlong_data_type,
	    SYMBOL_FUNCTION(Qcompile_long_data_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlong_data_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_read_only_symbol_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-SYMBOL-DATA-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_symbol_data_type_from_slot,
	    STATIC_FUNCTION(write_read_only_symbol_data_type_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qread_only_symbol_data_type,
	    SYMBOL_FUNCTION(Qwrite_read_only_symbol_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_read_only_text_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-TEXT-DATA-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_text_data_type_from_slot,
	    STATIC_FUNCTION(write_read_only_text_data_type_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qread_only_text_data_type,
	    SYMBOL_FUNCTION(Qwrite_read_only_text_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_read_only_truth_value_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-TRUTH-VALUE-DATA-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_truth_value_data_type_from_slot,
	    STATIC_FUNCTION(write_read_only_truth_value_data_type_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qread_only_truth_value_data_type,
	    SYMBOL_FUNCTION(Qwrite_read_only_truth_value_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_quantitative_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-QUANTITATIVE-DATA-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quantitative_data_type_from_slot,
	    STATIC_FUNCTION(write_quantitative_data_type_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qquantitative_data_type,
	    SYMBOL_FUNCTION(Qwrite_quantitative_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_integer_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-INTEGER-DATA-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integer_data_type_from_slot,
	    STATIC_FUNCTION(write_integer_data_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinteger_data_type,
	    SYMBOL_FUNCTION(Qwrite_integer_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_long_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-LONG-DATA-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_long_data_type_from_slot,
	    STATIC_FUNCTION(write_long_data_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlong_data_type,
	    SYMBOL_FUNCTION(Qwrite_long_data_type_from_slot),
	    Qslot_value_writer);
    Qwrite_float_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-FLOAT-DATA-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_float_data_type_from_slot,
	    STATIC_FUNCTION(write_float_data_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfloat_data_type,
	    SYMBOL_FUNCTION(Qwrite_float_data_type_from_slot),
	    Qslot_value_writer);
    string_constant_170 = 
	    STATIC_STRING("13Iy1n832Fy1m9k83-oy832Ky1n832Fy1m1m9k831Ay1m9k83A*y832ny1n832Fy1m1m9k83-9by1m9k83-Hy83-9cy1n832Fy1m9k830my83-Hy1m832Fy839Ty1m83");
    string_constant_171 = 
	    STATIC_STRING("2Fy839hy1m832Fy1m9k9l1m832Fy1m9k83Sy1n834Cy1m9k83-oy832Ky1n834Cy1m1m9k83-9by1m9k83-Hy83-9cy1m834Cy1m9k83Sy1m834Ly1m9k83=By1m834C");
    string_constant_172 = 
	    STATIC_STRING("y839Ty1m834Cy839hy1n833xy1m1m9k831Ay1m9k83A*y832ny1n833xy1m1m9k83-9by1m9k83-Hy83-9cy1m833xy1m9k9l1m833xy839Ty1m833xy839hy1n83-QX");
    string_constant_173 = 
	    STATIC_STRING("y1m1m9k831Ay1m9k83A*y832ny1n83-QXy1m1m9k83-9by1m9k83-Hy83-9cy1n83-QXy1m9k830my83-Hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_170,
	    string_constant_171,string_constant_172,string_constant_173)));
    string_constant_32 = STATIC_STRING("no value");
    string_constant_33 = STATIC_STRING(", valid indefinitely");
    string_constant_34 = STATIC_STRING(", expired ");
    string_constant_35 = STATIC_STRING(", expires ");
    Qsupplied_value = STATIC_SYMBOL("SUPPLIED-VALUE",AB_package);
    Qwrite_supplied_value_from_slot = 
	    STATIC_SYMBOL("WRITE-SUPPLIED-VALUE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_supplied_value_from_slot,
	    STATIC_FUNCTION(write_supplied_value_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qsupplied_value,
	    SYMBOL_FUNCTION(Qwrite_supplied_value_from_slot),
	    Qslot_value_writer);
    string_constant_174 = 
	    STATIC_STRING("1n1m830uy1m9k83A3y1m830uy1m9k832by1m830uy83-oy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_174));
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    list_constant_95 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qinteger);
    set_property_value_function(get_symbol_properties_function(Qvalidity_interval),
	    Qtype_specification_simple_expansion,list_constant_95);
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    Qindefinite = STATIC_SYMBOL("INDEFINITE",AB_package);
    list_constant_96 = STATIC_LIST((SI_Long)3L,Qmember,Qsupplied,Qindefinite);
    list_constant_97 = STATIC_CONS(Qinteger,Qnil);
    list_constant_16 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_96,list_constant_97);
    define_type_specification_explicit_complex_type(Qvalidity_interval,
	    list_constant_16);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qnamed,Qvalidity_interval);
    validity_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(validity_interval_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qvalidity_interval,
	    validity_interval_evaluation_setter_1);
    validity_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(validity_interval_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qvalidity_interval,
	    validity_interval_evaluation_getter_1);
    Qcompile_validity_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-VALIDITY-INTERVAL-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_validity_interval_for_slot,
	    STATIC_FUNCTION(compile_validity_interval_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qvalidity_interval,
	    SYMBOL_FUNCTION(Qcompile_validity_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qvalidity_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_validity_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-VALIDITY-INTERVAL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_validity_interval_from_slot,
	    STATIC_FUNCTION(write_validity_interval_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qvalidity_interval,
	    SYMBOL_FUNCTION(Qwrite_validity_interval_from_slot),
	    Qslot_value_writer);
    string_constant_175 = STATIC_STRING("1m1m834by1m9k832by1m834by83-oy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_175));
    Qsensor_validity_interval = STATIC_SYMBOL("SENSOR-VALIDITY-INTERVAL",
	    AB_package);
    Qcompile_sensor_validity_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-SENSOR-VALIDITY-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_sensor_validity_interval_for_slot,
	    STATIC_FUNCTION(compile_sensor_validity_interval_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qsensor_validity_interval,
	    SYMBOL_FUNCTION(Qcompile_sensor_validity_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsensor_validity_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_sensor_validity_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-SENSOR-VALIDITY-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_sensor_validity_interval_from_slot,
	    STATIC_FUNCTION(write_sensor_validity_interval_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsensor_validity_interval,
	    SYMBOL_FUNCTION(Qwrite_sensor_validity_interval_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qsensor_validity_interval),
	    Qtype_specification_simple_expansion,list_constant_95);
    list_constant_98 = STATIC_LIST((SI_Long)3L,Qmember,Qindefinite,Qsupplied);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_98,list_constant_97);
    define_type_specification_explicit_complex_type(Qsensor_validity_interval,
	    list_constant_18);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsensor_validity_interval);
    sensor_validity_interval_evaluation_setter_1 = 
	    STATIC_FUNCTION(sensor_validity_interval_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qsensor_validity_interval,
	    sensor_validity_interval_evaluation_setter_1);
    sensor_validity_interval_evaluation_getter_1 = 
	    STATIC_FUNCTION(sensor_validity_interval_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsensor_validity_interval,
	    sensor_validity_interval_evaluation_getter_1);
    string_constant_176 = 
	    STATIC_STRING("1t1m8376y83-oy1m8376y1m9k83Zy1m83-96y83-oy1m83-96y1m9k83Zy1m83Bwy83-oy1m83Bwy1m9k83Zy1m832gy831Ny1m832gy1m9k83Zy1m83lcy831Ny");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_176));
    Qinterval_qm = STATIC_SYMBOL("INTERVAL\?",AB_package);
    Qcompile_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_interval_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinterval_qm,
	    SYMBOL_FUNCTION(Qcompile_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinterval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_qm_from_slot,
	    STATIC_FUNCTION(write_interval_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinterval_qm,
	    SYMBOL_FUNCTION(Qwrite_interval_qm_from_slot),Qslot_value_writer);
    Qpositive_quantity_interval_qm = 
	    STATIC_SYMBOL("POSITIVE-QUANTITY-INTERVAL\?",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_76);
    set_property_value_function(get_symbol_properties_function(Qpositive_quantity_interval_qm),
	    Qtype_specification_simple_expansion,list_constant_20);
    define_type_specification_explicit_complex_type(Qpositive_quantity_interval_qm,
	    list_constant_20);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qpositive_quantity_interval_qm);
    positive_quantity_interval_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(positive_quantity_interval_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpositive_quantity_interval_qm,
	    positive_quantity_interval_qm_evaluation_setter_1);
    positive_quantity_interval_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(positive_quantity_interval_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpositive_quantity_interval_qm,
	    positive_quantity_interval_qm_evaluation_getter_1);
    Qcompile_interval_for_slot = STATIC_SYMBOL("COMPILE-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_for_slot,
	    STATIC_FUNCTION(compile_interval_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinterval,
	    SYMBOL_FUNCTION(Qcompile_interval_for_slot),Qslot_value_compiler);
    mutate_global_property(Qinterval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_interval_from_slot = STATIC_SYMBOL("WRITE-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_from_slot,
	    STATIC_FUNCTION(write_interval_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinterval,
	    SYMBOL_FUNCTION(Qwrite_interval_from_slot),Qslot_value_writer);
    array_constant_2 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)57344L);
    Qpositive_interval_qm = STATIC_SYMBOL("POSITIVE-INTERVAL\?",AB_package);
    Qcompile_positive_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-INTERVAL\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_positive_interval_qm_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qpositive_interval_qm,
	    SYMBOL_FUNCTION(Qcompile_positive_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_interval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_positive_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-POSITIVE-INTERVAL\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_positive_interval_qm_from_slot,
	    STATIC_FUNCTION(write_positive_interval_qm_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qpositive_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_positive_interval_qm_from_slot),
	    Qslot_value_writer);
    array_constant_3 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)57344L);
    Qexecution_interval_qm = STATIC_SYMBOL("EXECUTION-INTERVAL\?",AB_package);
    Qcompile_execution_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-EXECUTION-INTERVAL\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_execution_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_execution_interval_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qexecution_interval_qm,
	    SYMBOL_FUNCTION(Qcompile_execution_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qexecution_interval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_36 = STATIC_STRING("[deleted attribute]");
    Qwrite_execution_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-EXECUTION-INTERVAL\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_execution_interval_qm_from_slot,
	    STATIC_FUNCTION(write_execution_interval_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qexecution_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_execution_interval_qm_from_slot),
	    Qslot_value_writer);
    Qquantity_interval = STATIC_SYMBOL("QUANTITY-INTERVAL",AB_package);
    Qcompile_quantity_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUANTITY-INTERVAL-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quantity_interval_for_slot,
	    STATIC_FUNCTION(compile_quantity_interval_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qquantity_interval,
	    SYMBOL_FUNCTION(Qcompile_quantity_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qquantity_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_quantity_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-QUANTITY-INTERVAL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quantity_interval_from_slot,
	    STATIC_FUNCTION(write_quantity_interval_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qquantity_interval,
	    SYMBOL_FUNCTION(Qwrite_quantity_interval_from_slot),
	    Qslot_value_writer);
    Qcompile_positive_quantity_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-QUANTITY-INTERVAL\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_quantity_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_positive_quantity_interval_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qpositive_quantity_interval_qm,
	    SYMBOL_FUNCTION(Qcompile_positive_quantity_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_quantity_interval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qpositive_quantity_interval = 
	    STATIC_SYMBOL("POSITIVE-QUANTITY-INTERVAL",AB_package);
    Qcompile_positive_quantity_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-QUANTITY-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_quantity_interval_for_slot,
	    STATIC_FUNCTION(compile_positive_quantity_interval_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qpositive_quantity_interval,
	    SYMBOL_FUNCTION(Qcompile_positive_quantity_interval_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_quantity_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_positive_quantity_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-POSITIVE-QUANTITY-INTERVAL\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_positive_quantity_interval_qm_from_slot,
	    STATIC_FUNCTION(write_positive_quantity_interval_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpositive_quantity_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_positive_quantity_interval_qm_from_slot),
	    Qslot_value_writer);
    string_constant_177 = 
	    STATIC_STRING("1q1m8398y8376y1n8398y1m1m9k83AMy1m9k83Py83Py1m83-jSy83-96y1n83-jSy1m1m9k83AMy1m9k83Py83Py1m838Gy83-96y1n838Gy1m1m9k83AMy1m9k83Py");
    string_constant_178 = STATIC_STRING("83Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_177,
	    string_constant_178)));
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)57344L);
    Qinterval_qm_or_default = STATIC_SYMBOL("INTERVAL\?-OR-DEFAULT",
	    AB_package);
    Qcompile_interval_qm_or_default_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL\?-OR-DEFAULT-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_qm_or_default_for_slot,
	    STATIC_FUNCTION(compile_interval_qm_or_default_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinterval_qm_or_default,
	    SYMBOL_FUNCTION(Qcompile_interval_qm_or_default_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinterval_qm_or_default,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_99 = STATIC_CONS(Qnil,list_constant_97);
    list_constant_100 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_76,list_constant_99);
    set_property_value_function(get_symbol_properties_function(Qinterval_qm_or_default),
	    Qtype_specification_simple_expansion,list_constant_100);
    Quse_default = STATIC_SYMBOL("USE-DEFAULT",AB_package);
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qmember,Quse_default);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_76,list_constant_101,list_constant_97);
    define_type_specification_explicit_complex_type(Qinterval_qm_or_default,
	    list_constant_22);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qnamed,Qinterval_qm_or_default);
    interval_qm_or_default_evaluation_setter_1 = 
	    STATIC_FUNCTION(interval_qm_or_default_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinterval_qm_or_default,
	    interval_qm_or_default_evaluation_setter_1);
    interval_qm_or_default_evaluation_getter_1 = 
	    STATIC_FUNCTION(interval_qm_or_default_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinterval_qm_or_default,
	    interval_qm_or_default_evaluation_getter_1);
    string_constant_37 = STATIC_STRING("use default");
    Qwrite_interval_qm_or_default_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL\?-OR-DEFAULT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_qm_or_default_from_slot,
	    STATIC_FUNCTION(write_interval_qm_or_default_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinterval_qm_or_default,
	    SYMBOL_FUNCTION(Qwrite_interval_qm_or_default_from_slot),
	    Qslot_value_writer);
    Qpositive_interval_qm_or_default = 
	    STATIC_SYMBOL("POSITIVE-INTERVAL\?-OR-DEFAULT",AB_package);
    Qcompile_positive_interval_qm_or_default_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-INTERVAL\?-OR-DEFAULT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_interval_qm_or_default_for_slot,
	    STATIC_FUNCTION(compile_positive_interval_qm_or_default_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qpositive_interval_qm_or_default,
	    SYMBOL_FUNCTION(Qcompile_positive_interval_qm_or_default_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_interval_qm_or_default,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_positive_interval_qm_or_default_from_slot = 
	    STATIC_SYMBOL("WRITE-POSITIVE-INTERVAL\?-OR-DEFAULT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_positive_interval_qm_or_default_from_slot,
	    STATIC_FUNCTION(write_positive_interval_qm_or_default_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpositive_interval_qm_or_default,
	    SYMBOL_FUNCTION(Qwrite_positive_interval_qm_or_default_from_slot),
	    Qslot_value_writer);
    Qexecution_interval_qm_or_default = 
	    STATIC_SYMBOL("EXECUTION-INTERVAL\?-OR-DEFAULT",AB_package);
    Qcompile_execution_interval_qm_or_default_for_slot = 
	    STATIC_SYMBOL("COMPILE-EXECUTION-INTERVAL\?-OR-DEFAULT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_execution_interval_qm_or_default_for_slot,
	    STATIC_FUNCTION(compile_execution_interval_qm_or_default_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qexecution_interval_qm_or_default,
	    SYMBOL_FUNCTION(Qcompile_execution_interval_qm_or_default_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qexecution_interval_qm_or_default,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qexecution_interval_qm_or_default),
	    Qtype_specification_simple_expansion,list_constant_100);
    define_type_specification_explicit_complex_type(Qexecution_interval_qm_or_default,
	    list_constant_22);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qexecution_interval_qm_or_default);
    execution_interval_qm_or_default_evaluation_setter_1 = 
	    STATIC_FUNCTION(execution_interval_qm_or_default_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qexecution_interval_qm_or_default,
	    execution_interval_qm_or_default_evaluation_setter_1);
    execution_interval_qm_or_default_evaluation_getter_1 = 
	    STATIC_FUNCTION(execution_interval_qm_or_default_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qexecution_interval_qm_or_default,
	    execution_interval_qm_or_default_evaluation_getter_1);
    Qwrite_execution_interval_qm_or_default_from_slot = 
	    STATIC_SYMBOL("WRITE-EXECUTION-INTERVAL\?-OR-DEFAULT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_execution_interval_qm_or_default_from_slot,
	    STATIC_FUNCTION(write_execution_interval_qm_or_default_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qexecution_interval_qm_or_default,
	    SYMBOL_FUNCTION(Qwrite_execution_interval_qm_or_default_from_slot),
	    Qslot_value_writer);
    string_constant_179 = 
	    STATIC_STRING("1q1m83F7y1m9k83Zy1m83F7y83-qqy1m83F7y83-Qsy1m83-Qsy836Ey1n83-qqy1x1m9k83nOy1m9k83*dy1m9k83-Py1m9k83uVy1m9k9l1m9k83vOy1m9k9m836Ey");
    string_constant_180 = 
	    STATIC_STRING("1m9k83vy1m9k83=Fy1m9k83Cxy1m9k83*ly836Ey1n83gJysx1n83-qqy1w1m9k83nOy1m9k83*dy1m9k83-Py1m9k837Fy1m9k83*ly1m9k9m836Ey1m9k83vy1m9k8");
    string_constant_181 = 
	    STATIC_STRING("3=Fy1m9k83Cxy1m9k83*ly836Ey1n83glyrw");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_179,
	    string_constant_180,string_constant_181)));
    Qdependent = STATIC_SYMBOL("DEPENDENT",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qsimulation_subtable_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-BYTE-CODE-BODY",AB_package);
    Qsimulation_initial_value = STATIC_SYMBOL("SIMULATION-INITIAL-VALUE",
	    AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qsimulation_initial_value,
	    Qcurrent_computation_frame);
    Qsimulation_subtable_initial_value_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qspecific_simulation_formula_qm = 
	    STATIC_SYMBOL("SPECIFIC-SIMULATION-FORMULA\?",AB_package);
    Qcompile_specific_simulation_formula_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-SPECIFIC-SIMULATION-FORMULA\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_specific_simulation_formula_qm_for_slot,
	    STATIC_FUNCTION(compile_specific_simulation_formula_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qspecific_simulation_formula_qm,
	    SYMBOL_FUNCTION(Qcompile_specific_simulation_formula_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qspecific_simulation_formula_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwhole_string_qm = STATIC_SYMBOL("WHOLE-STRING\?",AB_package);
    Qwrite_whole_string_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-WHOLE-STRING\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_whole_string_qm_from_slot,
	    STATIC_FUNCTION(write_whole_string_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qwhole_string_qm,
	    SYMBOL_FUNCTION(Qwrite_whole_string_qm_from_slot),
	    Qslot_value_writer);
    Qcompile_whole_string_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-WHOLE-STRING\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_whole_string_qm_for_slot,
	    STATIC_FUNCTION(compile_whole_string_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qwhole_string_qm,
	    SYMBOL_FUNCTION(Qcompile_whole_string_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qwhole_string_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qread_only_whole_string_qm = STATIC_SYMBOL("READ-ONLY-WHOLE-STRING\?",
	    AB_package);
    Qwrite_read_only_whole_string_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-WHOLE-STRING\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_whole_string_qm_from_slot,
	    STATIC_FUNCTION(write_read_only_whole_string_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qread_only_whole_string_qm,
	    SYMBOL_FUNCTION(Qwrite_read_only_whole_string_qm_from_slot),
	    Qslot_value_writer);
    Qcheck_range_of_element = STATIC_SYMBOL("CHECK-RANGE-OF-ELEMENT",
	    AB_package);
    Qconvert_singular_constant = STATIC_SYMBOL("CONVERT-SINGULAR-CONSTANT",
	    AB_package);
    string_constant_182 = 
	    STATIC_STRING("13Iy1m837Gy1m9k83Zy1m837Gy83-Hy1m830iy1m9k83Zy1m830iy83Sy1m83wRy1m9k83Zy1m83wRy9l1m83-xy1m9k83Zy1m83-xy83-Uy1m83A4y1m9k83Zy1m83A");
    string_constant_183 = 
	    STATIC_STRING("4y83-2y1m83-hy1m9k83=Oy1m83-hy1m9k832Zy1o83-hy1m83-Hy1m9k83=Oy2ll83-hy1o9mljl1m836Ny1m9k83Zy1m836Ny83-hy1m830my83-Hy1m830my83-oy");
    string_constant_184 = 
	    STATIC_STRING("1o830my1m83-Hy83aKy2llm9n1n830my1m83-Hy839hy2llm1n830my1m83-Hy839Ty2llm1m837Iy830my1m837Iy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    push_optimized_constant(Qcheck_range_of_element);
    push_optimized_constant(Qconvert_singular_constant);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_182,
	    string_constant_183,string_constant_184)));
    set_property_value_function(get_symbol_properties_function(Qtruth_value),
	    Qtype_specification_simple_expansion,Qtruth_value);
    define_type_specification_explicit_complex_type(Qtruth_value,Qtruth_value);
    list_constant_25 = STATIC_CONS(Qnamed,list_constant_93);
    truth_value_evaluation_setter_1 = 
	    STATIC_FUNCTION(truth_value_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtruth_value,
	    truth_value_evaluation_setter_1);
    truth_value_evaluation_getter_1 = 
	    STATIC_FUNCTION(truth_value_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtruth_value,
	    truth_value_evaluation_getter_1);
    Qtruth_value_qm = STATIC_SYMBOL("TRUTH-VALUE\?",AB_package);
    list_constant_102 = STATIC_CONS(Qnil,Qnil);
    list_constant_103 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_76,list_constant_102);
    set_property_value_function(get_symbol_properties_function(Qtruth_value_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_25);
    define_type_specification_explicit_complex_type(Qtruth_value_qm,
	    list_constant_27);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value_qm);
    truth_value_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(truth_value_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtruth_value_qm,
	    truth_value_qm_evaluation_setter_1);
    truth_value_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(truth_value_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtruth_value_qm,
	    truth_value_qm_evaluation_getter_1);
    Qnon_negative_integer = STATIC_SYMBOL("NON-NEGATIVE-INTEGER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qnon_negative_integer),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qnon_negative_integer,
	    Qinteger);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnamed,Qnon_negative_integer);
    non_negative_integer_evaluation_setter_1 = 
	    STATIC_FUNCTION(non_negative_integer_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qnon_negative_integer,
	    non_negative_integer_evaluation_setter_1);
    non_negative_integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(non_negative_integer_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qnon_negative_integer,
	    non_negative_integer_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qinteger),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qinteger,Qinteger);
    list_constant_29 = STATIC_CONS(Qnamed,list_constant_97);
    integer_evaluation_setter_1 = 
	    STATIC_FUNCTION(integer_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinteger,
	    integer_evaluation_setter_1);
    integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(integer_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinteger,
	    integer_evaluation_getter_1);
    Qinteger_qm = STATIC_SYMBOL("INTEGER\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinteger_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_29);
    define_type_specification_explicit_complex_type(Qinteger_qm,
	    list_constant_31);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qnamed,Qinteger_qm);
    integer_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(integer_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qinteger_qm,
	    integer_qm_evaluation_setter_1);
    integer_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(integer_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinteger_qm,
	    integer_qm_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qquantity),
	    Qtype_specification_simple_expansion,Qnumber);
    define_type_specification_explicit_complex_type(Qquantity,Qnumber);
    list_constant_104 = STATIC_CONS(Qquantity,Qnil);
    list_constant_32 = STATIC_CONS(Qnamed,list_constant_104);
    quantity_evaluation_setter_1 = 
	    STATIC_FUNCTION(quantity_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qquantity,
	    quantity_evaluation_setter_1);
    quantity_evaluation_getter_1 = 
	    STATIC_FUNCTION(quantity_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qquantity,
	    quantity_evaluation_getter_1);
    Qquantity_qm = STATIC_SYMBOL("QUANTITY\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qquantity_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_32);
    define_type_specification_explicit_complex_type(Qquantity_qm,
	    list_constant_34);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qnamed,Qquantity_qm);
    quantity_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(quantity_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qquantity_qm,
	    quantity_qm_evaluation_setter_1);
    quantity_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(quantity_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qquantity_qm,
	    quantity_qm_evaluation_getter_1);
    Qinitial_value_float = STATIC_SYMBOL("INITIAL-VALUE-FLOAT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_float),
	    Qtype_specification_simple_expansion,Qfloat);
    define_type_specification_explicit_complex_type(Qinitial_value_float,
	    Qfloat);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_float);
    initial_value_float_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_float_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_value_float,
	    initial_value_float_evaluation_setter_1);
    initial_value_float_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_float_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_float,
	    initial_value_float_evaluation_getter_1);
    Qinitial_value_float_qm = STATIC_SYMBOL("INITIAL-VALUE-FLOAT\?",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_float_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_35);
    define_type_specification_explicit_complex_type(Qinitial_value_float_qm,
	    list_constant_37);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_float_qm);
    initial_value_float_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_float_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_value_float_qm,
	    initial_value_float_qm_evaluation_setter_1);
    initial_value_float_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_float_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_float_qm,
	    initial_value_float_qm_evaluation_getter_1);
    Qinitial_value_integer = STATIC_SYMBOL("INITIAL-VALUE-INTEGER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_integer),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qinitial_value_integer,
	    Qinteger);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_integer);
    initial_value_integer_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_integer_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_value_integer,
	    initial_value_integer_evaluation_setter_1);
    initial_value_integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_integer_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_integer,
	    initial_value_integer_evaluation_getter_1);
    Qinitial_value_long = STATIC_SYMBOL("INITIAL-VALUE-LONG",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_long),
	    Qtype_specification_simple_expansion,Qlong);
    define_type_specification_explicit_complex_type(Qinitial_value_long,Qlong);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_long);
    initial_value_long_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_long_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qinitial_value_long,
	    initial_value_long_evaluation_setter_1);
    initial_value_long_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_long_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_long,
	    initial_value_long_evaluation_getter_1);
    Qinitial_value_long_qm = STATIC_SYMBOL("INITIAL-VALUE-LONG\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_long_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_41 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_39);
    define_type_specification_explicit_complex_type(Qinitial_value_long_qm,
	    list_constant_41);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qnamed,Qinitial_value_long_qm);
    initial_value_long_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_long_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_value_long_qm,
	    initial_value_long_qm_evaluation_setter_1);
    initial_value_long_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_long_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_long_qm,
	    initial_value_long_qm_evaluation_getter_1);
    Qinitial_value_integer_qm = STATIC_SYMBOL("INITIAL-VALUE-INTEGER\?",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qinitial_value_integer_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_43 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_38);
    define_type_specification_explicit_complex_type(Qinitial_value_integer_qm,
	    list_constant_43);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinitial_value_integer_qm);
    initial_value_integer_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_value_integer_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_value_integer_qm,
	    initial_value_integer_qm_evaluation_setter_1);
    initial_value_integer_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_value_integer_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_value_integer_qm,
	    initial_value_integer_qm_evaluation_getter_1);
    Qstandard_or_class_qualified_symbol = 
	    STATIC_SYMBOL("STANDARD-OR-CLASS-QUALIFIED-SYMBOL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qstandard_or_class_qualified_symbol),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qstandard_or_class_qualified_symbol,
	    Qsymbol);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qstandard_or_class_qualified_symbol);
    standard_or_class_qualified_symbol_evaluation_setter_1 = 
	    STATIC_FUNCTION(standard_or_class_qualified_symbol_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qstandard_or_class_qualified_symbol,
	    standard_or_class_qualified_symbol_evaluation_setter_1);
    standard_or_class_qualified_symbol_evaluation_getter_1 = 
	    STATIC_FUNCTION(standard_or_class_qualified_symbol_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstandard_or_class_qualified_symbol,
	    standard_or_class_qualified_symbol_evaluation_getter_1);
    Qstandard_or_class_qualified_symbol_qm = 
	    STATIC_SYMBOL("STANDARD-OR-CLASS-QUALIFIED-SYMBOL\?",AB_package);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_76,list_constant_79);
    set_property_value_function(get_symbol_properties_function(Qstandard_or_class_qualified_symbol_qm),
	    Qtype_specification_simple_expansion,list_constant_46);
    define_type_specification_explicit_complex_type(Qstandard_or_class_qualified_symbol_qm,
	    list_constant_46);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qstandard_or_class_qualified_symbol_qm);
    standard_or_class_qualified_symbol_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(standard_or_class_qualified_symbol_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qstandard_or_class_qualified_symbol_qm,
	    standard_or_class_qualified_symbol_qm_evaluation_setter_1);
    standard_or_class_qualified_symbol_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(standard_or_class_qualified_symbol_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstandard_or_class_qualified_symbol_qm,
	    standard_or_class_qualified_symbol_qm_evaluation_getter_1);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    set_property_value_function(get_symbol_properties_function(Qwhole_string),
	    Qtype_specification_simple_expansion,Qtext);
    define_type_specification_explicit_complex_type(Qwhole_string,Qtext);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string);
    whole_string_evaluation_setter_1 = 
	    STATIC_FUNCTION(whole_string_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qwhole_string,
	    whole_string_evaluation_setter_1);
    whole_string_evaluation_getter_1 = 
	    STATIC_FUNCTION(whole_string_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qwhole_string,
	    whole_string_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qwhole_string_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_47);
    define_type_specification_explicit_complex_type(Qwhole_string_qm,
	    list_constant_49);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string_qm);
    whole_string_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(whole_string_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qwhole_string_qm,
	    whole_string_qm_evaluation_setter_1);
    whole_string_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(whole_string_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qwhole_string_qm,
	    whole_string_qm_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qread_only_whole_string_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    define_type_specification_explicit_complex_type(Qread_only_whole_string_qm,
	    list_constant_49);
    read_only_whole_string_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_whole_string_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_whole_string_qm,
	    read_only_whole_string_qm_evaluation_getter_1);
    Qpositive_integer = STATIC_SYMBOL("POSITIVE-INTEGER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpositive_integer),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qpositive_integer,
	    Qinteger);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qnamed,Qpositive_integer);
    positive_integer_evaluation_setter_1 = 
	    STATIC_FUNCTION(positive_integer_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpositive_integer,
	    positive_integer_evaluation_setter_1);
    positive_integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(positive_integer_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpositive_integer,
	    positive_integer_evaluation_getter_1);
    Qread_only_positive_integer = 
	    STATIC_SYMBOL("READ-ONLY-POSITIVE-INTEGER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qread_only_positive_integer),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qread_only_positive_integer,
	    Qinteger);
    read_only_positive_integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_positive_integer_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_positive_integer,
	    read_only_positive_integer_evaluation_getter_1);
    Qwrite_read_only_positive_integer_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-POSITIVE-INTEGER-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_positive_integer_from_slot,
	    STATIC_FUNCTION(write_read_only_positive_integer_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qread_only_positive_integer,
	    SYMBOL_FUNCTION(Qwrite_read_only_positive_integer_from_slot),
	    Qslot_value_writer);
    Qread_only_integer = STATIC_SYMBOL("READ-ONLY-INTEGER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qread_only_integer),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qread_only_integer,
	    Qinteger);
    read_only_integer_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_integer_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_integer,
	    read_only_integer_evaluation_getter_1);
    Qwrite_read_only_integer_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-INTEGER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_integer_from_slot,
	    STATIC_FUNCTION(write_read_only_integer_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qread_only_integer,
	    SYMBOL_FUNCTION(Qwrite_read_only_integer_from_slot),
	    Qslot_value_writer);
    Qpositive_integer_qm = STATIC_SYMBOL("POSITIVE-INTEGER\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpositive_integer_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    list_constant_52 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    list_constant_50);
    define_type_specification_explicit_complex_type(Qpositive_integer_qm,
	    list_constant_52);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qnamed,Qpositive_integer_qm);
    positive_integer_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(positive_integer_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qpositive_integer_qm,
	    positive_integer_qm_evaluation_setter_1);
    positive_integer_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(positive_integer_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpositive_integer_qm,
	    positive_integer_qm_evaluation_getter_1);
    Qread_only_positive_integer_qm = 
	    STATIC_SYMBOL("READ-ONLY-POSITIVE-INTEGER\?",AB_package);
    Qwrite_read_only_positive_integer_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-POSITIVE-INTEGER\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_positive_integer_qm_from_slot,
	    STATIC_FUNCTION(write_read_only_positive_integer_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qread_only_positive_integer_qm,
	    SYMBOL_FUNCTION(Qwrite_read_only_positive_integer_qm_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qread_only_positive_integer_qm),
	    Qtype_specification_simple_expansion,list_constant_103);
    define_type_specification_explicit_complex_type(Qread_only_positive_integer_qm,
	    list_constant_52);
    read_only_positive_integer_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(read_only_positive_integer_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qread_only_positive_integer_qm,
	    read_only_positive_integer_qm_evaluation_getter_1);
    string_constant_185 = 
	    STATIC_STRING("13Cy1m8371y83Sy1m8371y83-oy1o8371y1m83Sy83aKy2llm9k1n8371y1m83Sy839hy2llm1n8371y1m83Sy839Ty2llm1m8372y8371y1m8372y1m9l83Zy1m8373");
    string_constant_186 = 
	    STATIC_STRING("y83=By1m8374y8373y1m8374y1m9l83Zy1m837=y9m1o837=y1m9m83aKy2llm9k1n837=y1m9m839hy2llm1n837=y1m9m839Ty2llm1m8370y837=y1m8370y1m9l8");
    string_constant_187 = STATIC_STRING("3Zy");
    clear_optimized_constants();
    push_optimized_constant(Qconvert_singular_constant);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_185,
	    string_constant_186,string_constant_187)));
    Qdelay_millisecond_time_qm = STATIC_SYMBOL("DELAY-MILLISECOND-TIME\?",
	    AB_package);
    list_constant_105 = STATIC_CONS(Qinteger_qm,Qnil);
    list_constant_106 = STATIC_CONS(Qdelay_millisecond_time_qm,
	    list_constant_105);
    list_constant_107 = STATIC_CONS(list_constant_106,Qnil);
    add_grammar_rules_function(list_constant_107);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qtrue,Qfalse);
    list_constant_54 = STATIC_CONS(Qseconds,list_constant_87);
    string_constant_38 = 
	    STATIC_STRING("The initial value must be compatible with the type of the variable.");
    Qinitial_sensor_value_qm = STATIC_SYMBOL("INITIAL-SENSOR-VALUE\?",
	    AB_package);
    Qcompile_initial_sensor_value_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-SENSOR-VALUE\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_sensor_value_qm_for_slot,
	    STATIC_FUNCTION(compile_initial_sensor_value_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinitial_sensor_value_qm,
	    SYMBOL_FUNCTION(Qcompile_initial_sensor_value_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_sensor_value_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_initial_sensor_value_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-SENSOR-VALUE\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_sensor_value_qm_from_slot,
	    STATIC_FUNCTION(write_initial_sensor_value_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinitial_sensor_value_qm,
	    SYMBOL_FUNCTION(Qwrite_initial_sensor_value_qm_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qinitial_sensor_value_qm),
	    Qtype_specification_simple_expansion,list_constant_56);
    define_type_specification_explicit_complex_type(Qinitial_sensor_value_qm,
	    list_constant_56);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qinitial_sensor_value_qm);
    initial_sensor_value_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(initial_sensor_value_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qinitial_sensor_value_qm,
	    initial_sensor_value_qm_evaluation_setter_1);
    initial_sensor_value_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(initial_sensor_value_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qinitial_sensor_value_qm,
	    initial_sensor_value_qm_evaluation_getter_1);
    string_constant_39 = 
	    STATIC_STRING("Must be \"none\" or an integer from 1 through 60000.");
    Qcompile_delay_millisecond_time_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-DELAY-MILLISECOND-TIME\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_delay_millisecond_time_qm_for_slot,
	    STATIC_FUNCTION(compile_delay_millisecond_time_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qdelay_millisecond_time_qm,
	    SYMBOL_FUNCTION(Qcompile_delay_millisecond_time_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdelay_millisecond_time_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qdelay_millisecond_time_qm),
	    Qtype_specification_simple_expansion,Qnil);
    define_type_specification_explicit_complex_type(Qdelay_millisecond_time_qm,
	    list_constant_30);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdelay_millisecond_time_qm);
    delay_millisecond_time_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(delay_millisecond_time_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qdelay_millisecond_time_qm,
	    delay_millisecond_time_qm_evaluation_setter_1);
    delay_millisecond_time_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(delay_millisecond_time_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdelay_millisecond_time_qm,
	    delay_millisecond_time_qm_evaluation_getter_1);
    Qwrite_delay_millisecond_time_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-DELAY-MILLISECOND-TIME\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_delay_millisecond_time_qm_from_slot,
	    STATIC_FUNCTION(write_delay_millisecond_time_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdelay_millisecond_time_qm,
	    SYMBOL_FUNCTION(Qwrite_delay_millisecond_time_qm_from_slot),
	    Qslot_value_writer);
    Qtrace_file_pathname = STATIC_SYMBOL("TRACE-FILE-PATHNAME",AB_package);
    list_constant_108 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_102);
    set_property_value_function(get_symbol_properties_function(Qtrace_file_pathname),
	    Qtype_specification_simple_expansion,list_constant_108);
    list_constant_109 = STATIC_CONS(list_constant_47,Qnil);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_109);
    define_type_specification_explicit_complex_type(Qtrace_file_pathname,
	    list_constant_59);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qnamed,Qtrace_file_pathname);
    trace_file_pathname_evaluation_setter_1 = 
	    STATIC_FUNCTION(trace_file_pathname_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtrace_file_pathname,
	    trace_file_pathname_evaluation_setter_1);
    trace_file_pathname_evaluation_getter_1 = 
	    STATIC_FUNCTION(trace_file_pathname_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtrace_file_pathname,
	    trace_file_pathname_evaluation_getter_1);
    string_constant_40 = STATIC_STRING("none");
    Qnumber_qm = STATIC_SYMBOL("NUMBER\?",AB_package);
    Qwrite_number_qm_from_slot = STATIC_SYMBOL("WRITE-NUMBER\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_qm_from_slot,
	    STATIC_FUNCTION(write_number_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qnumber_qm,
	    SYMBOL_FUNCTION(Qwrite_number_qm_from_slot),Qslot_value_writer);
    Qcompile_quantity_for_slot = STATIC_SYMBOL("COMPILE-QUANTITY-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quantity_for_slot,
	    STATIC_FUNCTION(compile_quantity_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qquantity,
	    SYMBOL_FUNCTION(Qcompile_quantity_for_slot),Qslot_value_compiler);
    mutate_global_property(Qquantity,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_quantity_from_slot = STATIC_SYMBOL("WRITE-QUANTITY-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quantity_from_slot,
	    STATIC_FUNCTION(write_quantity_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qquantity,
	    SYMBOL_FUNCTION(Qwrite_quantity_from_slot),Qslot_value_writer);
    Qcompile_quantity_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUANTITY\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_quantity_qm_for_slot,
	    STATIC_FUNCTION(compile_quantity_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qquantity_qm,
	    SYMBOL_FUNCTION(Qcompile_quantity_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qquantity_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_quantity_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-QUANTITY\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_quantity_qm_from_slot,
	    STATIC_FUNCTION(write_quantity_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qquantity_qm,
	    SYMBOL_FUNCTION(Qwrite_quantity_qm_from_slot),Qslot_value_writer);
    Qcompile_number_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-NUMBER\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_number_qm_for_slot,
	    STATIC_FUNCTION(compile_number_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qnumber_qm,
	    SYMBOL_FUNCTION(Qcompile_number_qm_for_slot),Qslot_value_compiler);
    mutate_global_property(Qnumber_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_61 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_76,
	    Qnumber);
    set_property_value_function(get_symbol_properties_function(Qnumber_qm),
	    Qtype_specification_simple_expansion,list_constant_61);
    define_type_specification_explicit_complex_type(Qnumber_qm,
	    list_constant_61);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qnamed,Qnumber_qm);
    number_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(number_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qnumber_qm,
	    number_qm_evaluation_setter_1);
    number_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(number_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qnumber_qm,
	    number_qm_evaluation_getter_1);
    Qwrite_number_from_slot = STATIC_SYMBOL("WRITE-NUMBER-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_from_slot,
	    STATIC_FUNCTION(write_number_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qnumber,
	    SYMBOL_FUNCTION(Qwrite_number_from_slot),Qslot_value_writer);
    Qwrite_integer_from_slot = STATIC_SYMBOL("WRITE-INTEGER-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integer_from_slot,
	    STATIC_FUNCTION(write_integer_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinteger,
	    SYMBOL_FUNCTION(Qwrite_integer_from_slot),Qslot_value_writer);
    Qwrite_initial_value_integer_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-INTEGER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_integer_from_slot,
	    STATIC_FUNCTION(write_initial_value_integer_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinitial_value_integer,
	    SYMBOL_FUNCTION(Qwrite_initial_value_integer_from_slot),
	    Qslot_value_writer);
    Qwrite_long_from_slot = STATIC_SYMBOL("WRITE-LONG-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_long_from_slot,
	    STATIC_FUNCTION(write_long_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlong,SYMBOL_FUNCTION(Qwrite_long_from_slot),
	    Qslot_value_writer);
    Qwrite_initial_value_long_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-LONG-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_long_from_slot,
	    STATIC_FUNCTION(write_initial_value_long_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinitial_value_long,
	    SYMBOL_FUNCTION(Qwrite_initial_value_long_from_slot),
	    Qslot_value_writer);
    Qwrite_float_from_slot = STATIC_SYMBOL("WRITE-FLOAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_float_from_slot,
	    STATIC_FUNCTION(write_float_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfloat,SYMBOL_FUNCTION(Qwrite_float_from_slot),
	    Qslot_value_writer);
    Qwrite_initial_value_float_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-FLOAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_float_from_slot,
	    STATIC_FUNCTION(write_initial_value_float_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qinitial_value_float,
	    SYMBOL_FUNCTION(Qwrite_initial_value_float_from_slot),
	    Qslot_value_writer);
    Qfloat_qm = STATIC_SYMBOL("FLOAT\?",AB_package);
    Qwrite_float_qm_from_slot = STATIC_SYMBOL("WRITE-FLOAT\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_float_qm_from_slot,
	    STATIC_FUNCTION(write_float_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qfloat_qm,
	    SYMBOL_FUNCTION(Qwrite_float_qm_from_slot),Qslot_value_writer);
    Qwrite_initial_value_float_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-FLOAT\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_float_qm_from_slot,
	    STATIC_FUNCTION(write_initial_value_float_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinitial_value_float_qm,
	    SYMBOL_FUNCTION(Qwrite_initial_value_float_qm_from_slot),
	    Qslot_value_writer);
    Qwrite_integer_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INTEGER\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integer_qm_from_slot,
	    STATIC_FUNCTION(write_integer_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinteger_qm,
	    SYMBOL_FUNCTION(Qwrite_integer_qm_from_slot),Qslot_value_writer);
    Qwrite_initial_value_integer_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-INTEGER\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_integer_qm_from_slot,
	    STATIC_FUNCTION(write_initial_value_integer_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinitial_value_integer_qm,
	    SYMBOL_FUNCTION(Qwrite_initial_value_integer_qm_from_slot),
	    Qslot_value_writer);
    Qwrite_initial_value_long_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-INITIAL-VALUE-LONG\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_initial_value_long_qm_from_slot,
	    STATIC_FUNCTION(write_initial_value_long_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qinitial_value_long_qm,
	    SYMBOL_FUNCTION(Qwrite_initial_value_long_qm_from_slot),
	    Qslot_value_writer);
    Qcompile_initial_value_long_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-LONG\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_long_qm_for_slot,
	    STATIC_FUNCTION(compile_initial_value_long_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinitial_value_long_qm,
	    SYMBOL_FUNCTION(Qcompile_initial_value_long_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_long_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_initial_value_long_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-LONG-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_long_for_slot,
	    STATIC_FUNCTION(compile_initial_value_long_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinitial_value_long,
	    SYMBOL_FUNCTION(Qcompile_initial_value_long_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_long,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_integer_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTEGER\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_integer_qm_for_slot,
	    STATIC_FUNCTION(compile_integer_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinteger_qm,
	    SYMBOL_FUNCTION(Qcompile_integer_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinteger_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_initial_value_integer_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-INTEGER\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_integer_qm_for_slot,
	    STATIC_FUNCTION(compile_initial_value_integer_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinitial_value_integer_qm,
	    SYMBOL_FUNCTION(Qcompile_initial_value_integer_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_integer_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_float_qm_for_slot = STATIC_SYMBOL("COMPILE-FLOAT\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_float_qm_for_slot,
	    STATIC_FUNCTION(compile_float_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfloat_qm,
	    SYMBOL_FUNCTION(Qcompile_float_qm_for_slot),Qslot_value_compiler);
    mutate_global_property(Qfloat_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_initial_value_float_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-FLOAT\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_float_qm_for_slot,
	    STATIC_FUNCTION(compile_initial_value_float_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinitial_value_float_qm,
	    SYMBOL_FUNCTION(Qcompile_initial_value_float_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_float_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_initial_value_integer_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-INTEGER-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_integer_for_slot,
	    STATIC_FUNCTION(compile_initial_value_integer_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qinitial_value_integer,
	    SYMBOL_FUNCTION(Qcompile_initial_value_integer_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_integer,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_initial_value_float_for_slot = 
	    STATIC_SYMBOL("COMPILE-INITIAL-VALUE-FLOAT-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_initial_value_float_for_slot,
	    STATIC_FUNCTION(compile_initial_value_float_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qinitial_value_float,
	    SYMBOL_FUNCTION(Qcompile_initial_value_float_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinitial_value_float,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qsymbol,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qsymbol_qm = STATIC_SYMBOL("SYMBOL\?",AB_package);
    Qcompile_symbol_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-SYMBOL\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_symbol_qm_for_slot,
	    STATIC_FUNCTION(compile_symbol_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qsymbol_qm,
	    SYMBOL_FUNCTION(Qcompile_symbol_qm_for_slot),Qslot_value_compiler);
    mutate_global_property(Qsymbol_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_standard_or_class_qualified_symbol_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_standard_or_class_qualified_symbol_qm_for_slot,
	    STATIC_FUNCTION(compile_standard_or_class_qualified_symbol_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qstandard_or_class_qualified_symbol_qm,
	    SYMBOL_FUNCTION(Qcompile_standard_or_class_qualified_symbol_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qstandard_or_class_qualified_symbol_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_standard_or_class_qualified_symbol_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_standard_or_class_qualified_symbol_qm_from_slot,
	    STATIC_FUNCTION(write_standard_or_class_qualified_symbol_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qstandard_or_class_qualified_symbol_qm,
	    SYMBOL_FUNCTION(Qwrite_standard_or_class_qualified_symbol_qm_from_slot),
	    Qslot_value_writer);
    Qcompile_standard_or_class_qualified_symbol_for_slot = 
	    STATIC_SYMBOL("COMPILE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_standard_or_class_qualified_symbol_for_slot,
	    STATIC_FUNCTION(compile_standard_or_class_qualified_symbol_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qstandard_or_class_qualified_symbol,
	    SYMBOL_FUNCTION(Qcompile_standard_or_class_qualified_symbol_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qstandard_or_class_qualified_symbol,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_standard_or_class_qualified_symbol_from_slot = 
	    STATIC_SYMBOL("WRITE-STANDARD-OR-CLASS-QUALIFIED-SYMBOL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_standard_or_class_qualified_symbol_from_slot,
	    STATIC_FUNCTION(write_standard_or_class_qualified_symbol_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qstandard_or_class_qualified_symbol,
	    SYMBOL_FUNCTION(Qwrite_standard_or_class_qualified_symbol_from_slot),
	    Qslot_value_writer);
    mutate_global_property(Qsymbol_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qwrite_whole_string_from_slot = 
	    STATIC_SYMBOL("WRITE-WHOLE-STRING-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_whole_string_from_slot,
	    STATIC_FUNCTION(write_whole_string_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qwhole_string,
	    SYMBOL_FUNCTION(Qwrite_whole_string_from_slot),Qslot_value_writer);
    Qcompile_truth_value_for_slot = 
	    STATIC_SYMBOL("COMPILE-TRUTH-VALUE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_truth_value_for_slot,
	    STATIC_FUNCTION(compile_truth_value_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qtruth_value,
	    SYMBOL_FUNCTION(Qcompile_truth_value_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtruth_value,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_truth_value_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-TRUTH-VALUE\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_truth_value_qm_for_slot,
	    STATIC_FUNCTION(compile_truth_value_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qtruth_value_qm,
	    SYMBOL_FUNCTION(Qcompile_truth_value_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtruth_value_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_truth_value_from_slot = 
	    STATIC_SYMBOL("WRITE-TRUTH-VALUE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_truth_value_from_slot,
	    STATIC_FUNCTION(write_truth_value_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qtruth_value,
	    SYMBOL_FUNCTION(Qwrite_truth_value_from_slot),Qslot_value_writer);
    Qwrite_truth_value_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-TRUTH-VALUE\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_truth_value_qm_from_slot,
	    STATIC_FUNCTION(write_truth_value_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qtruth_value_qm,
	    SYMBOL_FUNCTION(Qwrite_truth_value_qm_from_slot),
	    Qslot_value_writer);
    string_constant_188 = 
	    STATIC_STRING("13Dy1n83*Ey1n83-wEy1m9k83vy83-wCy1nl83-Royn1n83*Ey1p83-wEy1m9k83vy83-wCy1m9k83vy83rLy1ol83-Roynp1n83*Ey1o83-wEy83-wBy1m9k83vy83-");
    string_constant_189 = 
	    STATIC_STRING("wCy1nlmo1n83*Ey1q83-wEy83-wBy1m9k83vy83-wCy1m9k83vy83rLy1olmoq1n83-wEy1n1m9k830Iy1m9k83hRy1m9k83-Lry83-Uqy1m83-wEy1o1m9k830Iy1m9");
    string_constant_190 = 
	    STATIC_STRING("k9l1m9k83hRy1m9k83-Lry1n83-wBy1o1m9k83-T2y1m9k83=Iy1m9k83Euy1m9k83*ly83-Jey1n83-wCy1o1m9k830Iy1m9k9l1m9k83-nuy1m9k831Dy83-iVy1n8");
    string_constant_191 = 
	    STATIC_STRING("3-wCy1o1m9k830Iy1m9k9l1m9k83fIy1m9k83-Lry83-Rpy1n83-wCy1o1m9k83-Qty1m9k9m1m9k83fIy1m9k83-Lry83-Qvy1m83-wCy1o1m9k83-L*y1m9k9m1m9k");
    string_constant_192 = 
	    STATIC_STRING("83fIy1m9k83-Lry1n83rLy1o1m9k83-LFy1m9k831Dy1m9k83=Iy1m9k838Hy83-LGy1m83rLy1q1m9k830Iy1m9k9l1m9k83-LFy1m9k831Dy1m9k83=Iy1m9k838Hy");
    string_constant_193 = 
	    STATIC_STRING("1n83=Cy83-wEy1nl83-Roy83-iVy1n83=Cy1n83-wEy1m9k83vy83rLy1ol83-Roy83-iVyn1n83=Cy1m83-wEy83-wBy1nlm83-iVy1n83=Cy1o83-wEy83-wBy1m9k");
    string_constant_194 = STATIC_STRING("83vy83rLy1olm83-iVyo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qfirst);
    add_grammar_rules_function(regenerate_optimized_constant(list(7,
	    string_constant_188,string_constant_189,string_constant_190,
	    string_constant_191,string_constant_192,string_constant_193,
	    string_constant_194)));
    Qvariable_frame_flags = STATIC_SYMBOL("VARIABLE-FRAME-FLAGS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qvariable_frame_flags),
	    Qtype_specification_simple_expansion,list_constant_78);
    Qforward_chain = STATIC_SYMBOL("FORWARD-CHAIN",AB_package);
    list_constant_111 = STATIC_CONS(Qforward_chain,list_constant_93);
    Qforward_chain_even_for_same_value = 
	    STATIC_SYMBOL("FORWARD-CHAIN-EVEN-FOR-SAME-VALUE",AB_package);
    list_constant_112 = STATIC_CONS(Qforward_chain_even_for_same_value,
	    list_constant_93);
    Qbackward_chain = STATIC_SYMBOL("BACKWARD-CHAIN",AB_package);
    Qbreadth_first = STATIC_SYMBOL("BREADTH-FIRST",AB_package);
    Qdepth_first = STATIC_SYMBOL("DEPTH-FIRST",AB_package);
    Qdo_not_backward_chain = STATIC_SYMBOL("DO-NOT-BACKWARD-CHAIN",AB_package);
    Qdo_not_seek_data = STATIC_SYMBOL("DO-NOT-SEEK-DATA",AB_package);
    list_constant_110 = STATIC_LIST((SI_Long)5L,Qmember,Qbreadth_first,
	    Qdepth_first,Qdo_not_backward_chain,Qdo_not_seek_data);
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qbackward_chain,
	    list_constant_110);
    Qexplanation_data = STATIC_SYMBOL("EXPLANATION-DATA",AB_package);
    list_constant_114 = STATIC_CONS(Qexplanation_data,list_constant_93);
    list_constant_115 = STATIC_LIST((SI_Long)4L,list_constant_111,
	    list_constant_112,list_constant_113,list_constant_114);
    list_constant_116 = STATIC_LIST((SI_Long)3L,Qand,Qforward_chain,
	    Qbackward_chain);
    list_constant_63 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_115,list_constant_116);
    define_type_specification_explicit_complex_type(Qvariable_frame_flags,
	    list_constant_63);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qnamed,Qvariable_frame_flags);
    Qforward_chain_flag = STATIC_SYMBOL("FORWARD-CHAIN-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforward_chain_flag,Forward_chain_flag);
    Qforward = STATIC_SYMBOL("FORWARD",AB_package);
    Qchain = STATIC_SYMBOL("CHAIN",AB_package);
    Qalways_forward_chain_if_possible_flag = 
	    STATIC_SYMBOL("ALWAYS-FORWARD-CHAIN-IF-POSSIBLE-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalways_forward_chain_if_possible_flag,
	    Always_forward_chain_if_possible_flag);
    Qdont_always_forward_chain_if_possible_flag = 
	    STATIC_SYMBOL("DONT-ALWAYS-FORWARD-CHAIN-IF-POSSIBLE-FLAG",
	    AB_package);
    Qpassive_flag = STATIC_SYMBOL("PASSIVE-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpassive_flag,Passive_flag);
    Qdont_backward_chain_flag = STATIC_SYMBOL("DONT-BACKWARD-CHAIN-FLAG",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdont_backward_chain_flag,
	    Dont_backward_chain_flag);
    Qdepth_first_flag = STATIC_SYMBOL("DEPTH-FIRST-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdepth_first_flag,Depth_first_flag);
    Qbreadth = STATIC_SYMBOL("BREADTH",AB_package);
    Qbackward = STATIC_SYMBOL("BACKWARD",AB_package);
    Qcache_data_for_explanation_flag = 
	    STATIC_SYMBOL("CACHE-DATA-FOR-EXPLANATION-FLAG",AB_package);
    variable_frame_flags_evaluation_setter_1 = 
	    STATIC_FUNCTION(variable_frame_flags_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qvariable_frame_flags,
	    variable_frame_flags_evaluation_setter_1);
    variable_frame_flags_evaluation_getter_1 = 
	    STATIC_FUNCTION(variable_frame_flags_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qvariable_frame_flags,
	    variable_frame_flags_evaluation_getter_1);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qg2_internal_cached_explanation = 
	    STATIC_SYMBOL("G2-INTERNAL-CACHED-EXPLANATION",AB_package);
    Qcompile_variable_frame_flags_for_slot = 
	    STATIC_SYMBOL("COMPILE-VARIABLE-FRAME-FLAGS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_variable_frame_flags_for_slot,
	    STATIC_FUNCTION(compile_variable_frame_flags_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qvariable_frame_flags,
	    SYMBOL_FUNCTION(Qcompile_variable_frame_flags_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qvariable_frame_flags,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qparameter_frame_flags = STATIC_SYMBOL("PARAMETER-FRAME-FLAGS",AB_package);
    Qcompile_parameter_frame_flags_for_slot = 
	    STATIC_SYMBOL("COMPILE-PARAMETER-FRAME-FLAGS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_parameter_frame_flags_for_slot,
	    STATIC_FUNCTION(compile_parameter_frame_flags_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qparameter_frame_flags,
	    SYMBOL_FUNCTION(Qcompile_parameter_frame_flags_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qparameter_frame_flags,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qparameter_frame_flags),
	    Qtype_specification_simple_expansion,list_constant_78);
    list_constant_117 = STATIC_CONS(list_constant_114,Qnil);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)3L,list_constant_111,
	    list_constant_112,list_constant_117);
    list_constant_119 = STATIC_LIST((SI_Long)2L,Qand,Qforward_chain);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_118,list_constant_119);
    define_type_specification_explicit_complex_type(Qparameter_frame_flags,
	    list_constant_65);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qnamed,Qparameter_frame_flags);
    parameter_frame_flags_evaluation_setter_1 = 
	    STATIC_FUNCTION(parameter_frame_flags_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qparameter_frame_flags,
	    parameter_frame_flags_evaluation_setter_1);
    parameter_frame_flags_evaluation_getter_1 = 
	    STATIC_FUNCTION(parameter_frame_flags_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qparameter_frame_flags,
	    parameter_frame_flags_evaluation_getter_1);
    string_constant_41 = 
	    STATIC_STRING("do forward chain even for same value, ");
    string_constant_42 = STATIC_STRING("do forward chain, ");
    string_constant_43 = STATIC_STRING("do not forward chain, ");
    string_constant_44 = STATIC_STRING("do not seek data");
    string_constant_45 = STATIC_STRING("do not backward chain");
    string_constant_46 = STATIC_STRING("depth first backward chain");
    string_constant_47 = STATIC_STRING("breadth first backward chain");
    string_constant_48 = STATIC_STRING(", cache data for explanation");
    string_constant_49 = STATIC_STRING(", do not cache data for explanation");
    Qwrite_variable_frame_flags_from_slot = 
	    STATIC_SYMBOL("WRITE-VARIABLE-FRAME-FLAGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_variable_frame_flags_from_slot,
	    STATIC_FUNCTION(write_variable_frame_flags_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qvariable_frame_flags,
	    SYMBOL_FUNCTION(Qwrite_variable_frame_flags_from_slot),
	    Qslot_value_writer);
    string_constant_50 = STATIC_STRING("do forward chain even for same value");
    string_constant_51 = STATIC_STRING("do forward chain");
    string_constant_52 = STATIC_STRING("do not forward chain");
    Qwrite_parameter_frame_flags_from_slot = 
	    STATIC_SYMBOL("WRITE-PARAMETER-FRAME-FLAGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_parameter_frame_flags_from_slot,
	    STATIC_FUNCTION(write_parameter_frame_flags_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qparameter_frame_flags,
	    SYMBOL_FUNCTION(Qwrite_parameter_frame_flags_from_slot),
	    Qslot_value_writer);
    string_constant_195 = 
	    STATIC_STRING("1n1n832iy1m83-Hy83-CSyl1n83A+y1m83-Hy83-CSyl1m83A+y1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_195));
    string_constant_53 = 
	    STATIC_STRING("Time increment is too small;  must be at least ~f seconds");
    Qsimulation_time_increment_qm = 
	    STATIC_SYMBOL("SIMULATION-TIME-INCREMENT\?",AB_package);
    Qcompile_simulation_time_increment_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-SIMULATION-TIME-INCREMENT\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_simulation_time_increment_qm_for_slot,
	    STATIC_FUNCTION(compile_simulation_time_increment_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qsimulation_time_increment_qm,
	    SYMBOL_FUNCTION(Qcompile_simulation_time_increment_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsimulation_time_increment_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qsimulation_time_increment_qm),
	    Qtype_specification_simple_expansion,list_constant_61);
    define_type_specification_explicit_complex_type(Qsimulation_time_increment_qm,
	    list_constant_61);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsimulation_time_increment_qm);
    simulation_time_increment_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(simulation_time_increment_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsimulation_time_increment_qm,
	    simulation_time_increment_qm_evaluation_setter_1);
    simulation_time_increment_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(simulation_time_increment_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsimulation_time_increment_qm,
	    simulation_time_increment_qm_evaluation_getter_1);
    Qsimulation_time_increment = STATIC_SYMBOL("SIMULATION-TIME-INCREMENT",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qsimulation_time_increment),
	    Qtype_specification_simple_expansion,Qnumber);
    define_type_specification_explicit_complex_type(Qsimulation_time_increment,
	    Qnumber);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsimulation_time_increment);
    simulation_time_increment_evaluation_setter_1 = 
	    STATIC_FUNCTION(simulation_time_increment_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsimulation_time_increment,
	    simulation_time_increment_evaluation_setter_1);
    simulation_time_increment_evaluation_getter_1 = 
	    STATIC_FUNCTION(simulation_time_increment_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsimulation_time_increment,
	    simulation_time_increment_evaluation_getter_1);
    Qcompile_simulation_time_increment_for_slot = 
	    STATIC_SYMBOL("COMPILE-SIMULATION-TIME-INCREMENT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_simulation_time_increment_for_slot,
	    STATIC_FUNCTION(compile_simulation_time_increment_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qsimulation_time_increment,
	    SYMBOL_FUNCTION(Qcompile_simulation_time_increment_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsimulation_time_increment,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_54 = STATIC_STRING("~f");
    Qwrite_simulation_time_increment_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATION-TIME-INCREMENT\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulation_time_increment_qm_from_slot,
	    STATIC_FUNCTION(write_simulation_time_increment_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_time_increment_qm,
	    SYMBOL_FUNCTION(Qwrite_simulation_time_increment_qm_from_slot),
	    Qslot_value_writer);
    Qwrite_simulation_time_increment_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATION-TIME-INCREMENT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulation_time_increment_from_slot,
	    STATIC_FUNCTION(write_simulation_time_increment_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsimulation_time_increment,
	    SYMBOL_FUNCTION(Qwrite_simulation_time_increment_from_slot),
	    Qslot_value_writer);
    string_constant_55 = STATIC_STRING(" second");
    string_constant_56 = STATIC_STRING(" seconds");
    string_constant_196 = 
	    STATIC_STRING("1u1m833Py1m9k833uy1n833Py1m1m9k83-Uvy1m9k83-nPy83-n9y1n839xy83-rey1ll1n839xy1m83-rey83-xIy1mlm1n839xy1m83-rey83-xJy1nl0m1n839xy1");
    string_constant_197 = 
	    STATIC_STRING("n83-rey83-xIy83-xJy1nlmn1n83-rey1m1m9k83-nNy1m9k83-riy83-riy1n83-rey1p1m9k83-nNy1m9k83*5y1m9k83hGy1m9k83*5y1m9k83ldy83-Jpy1n83-x");
    string_constant_198 = 
	    STATIC_STRING("Iy1p1m9k83vy1m9k83AUy1m9k83-Zey1m9k83n4y1m9k831Ay8k1n83-xJy1x1m9k83vy1m9k83AUy1m9k83-wly1m9k83=Iy1m9k83n4y1m9k83=Vy1m9k83=Uy1m9k");
    string_constant_199 = 
	    STATIC_STRING("83-XYy1m9k83w1y1m9k83n4y1m9k83-Pfy1m9k83=3y1m9k83-U5y8k");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_196,
	    string_constant_197,string_constant_198,string_constant_199)));
    Qeuler = STATIC_SYMBOL("EULER",AB_package);
    string_constant_57 = STATIC_STRING("Euler");
    string_constant_58 = STATIC_STRING("Fourth-order Runge-Kutta");
    Qintegration_algorithm_specification = 
	    STATIC_SYMBOL("INTEGRATION-ALGORITHM-SPECIFICATION",AB_package);
    Qwrite_integration_algorithm_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-INTEGRATION-ALGORITHM-SPECIFICATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_integration_algorithm_specification_from_slot,
	    STATIC_FUNCTION(write_integration_algorithm_specification_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qintegration_algorithm_specification,
	    SYMBOL_FUNCTION(Qwrite_integration_algorithm_specification_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qintegration_algorithm_specification),
	    Qtype_specification_simple_expansion,Qnil);
    Qrunga_kutta_4 = STATIC_SYMBOL("RUNGA-KUTTA-4",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qmember,Qeuler,Qrunga_kutta_4);
    define_type_specification_explicit_complex_type(Qintegration_algorithm_specification,
	    list_constant_69);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qintegration_algorithm_specification);
    Qrk4 = STATIC_SYMBOL("RK4",AB_package);
    integration_algorithm_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(integration_algorithm_specification_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qintegration_algorithm_specification,
	    integration_algorithm_specification_evaluation_setter_1);
    integration_algorithm_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(integration_algorithm_specification_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qintegration_algorithm_specification,
	    integration_algorithm_specification_evaluation_getter_1);
    Qsynchronously = STATIC_SYMBOL("SYNCHRONOUSLY",AB_package);
    string_constant_59 = STATIC_STRING("run synchronously");
    string_constant_60 = STATIC_STRING("run as fast as possible");
    string_constant_61 = 
	    STATIC_STRING(", without incrementing simulation time");
    string_constant_62 = 
	    STATIC_STRING(", without waiting for simulation procedure or gspan external simulation cycle to finish");
    Qsimulation_control_specification = 
	    STATIC_SYMBOL("SIMULATION-CONTROL-SPECIFICATION",AB_package);
    Qwrite_simulation_control_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATION-CONTROL-SPECIFICATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulation_control_specification_from_slot,
	    STATIC_FUNCTION(write_simulation_control_specification_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_control_specification,
	    SYMBOL_FUNCTION(Qwrite_simulation_control_specification_from_slot),
	    Qslot_value_writer);
    array_constant_5 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)36L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)41L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)46L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)49L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)51L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)52L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)54L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)57L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)58L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)59L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)60L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)61L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)62L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)63L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)64L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)65L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)66L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)67L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)68L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)69L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)70L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)71L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)72L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)73L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)74L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)75L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)76L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)77L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)78L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)79L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)80L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)81L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)82L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)83L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)84L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)85L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)86L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)87L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)94L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)95L,(SI_Long)57344L);
    Qcompile_simulation_control_specification_for_slot = 
	    STATIC_SYMBOL("COMPILE-SIMULATION-CONTROL-SPECIFICATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_simulation_control_specification_for_slot,
	    STATIC_FUNCTION(compile_simulation_control_specification_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qsimulation_control_specification,
	    SYMBOL_FUNCTION(Qcompile_simulation_control_specification_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsimulation_control_specification,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qsimulation_control_specification),
	    Qtype_specification_simple_expansion,list_constant_78);
    Qsynchronization_mode = STATIC_SYMBOL("SYNCHRONIZATION-MODE",AB_package);
    Qrun_synchronously = STATIC_SYMBOL("RUN-SYNCHRONOUSLY",AB_package);
    Qrun_as_fast_as_possible = STATIC_SYMBOL("RUN-AS-FAST-AS-POSSIBLE",
	    AB_package);
    list_constant_120 = STATIC_LIST((SI_Long)3L,Qmember,Qrun_synchronously,
	    Qrun_as_fast_as_possible);
    list_constant_121 = STATIC_LIST((SI_Long)2L,Qsynchronization_mode,
	    list_constant_120);
    Qwithout_incrementing_simulation_time = 
	    STATIC_SYMBOL("WITHOUT-INCREMENTING-SIMULATION-TIME",AB_package);
    list_constant_122 = STATIC_CONS(Qwithout_incrementing_simulation_time,
	    list_constant_93);
    Qwithout_waiting_for_external_simulation_cycle = 
	    STATIC_SYMBOL("WITHOUT-WAITING-FOR-EXTERNAL-SIMULATION-CYCLE",
	    AB_package);
    list_constant_123 = 
	    STATIC_CONS(Qwithout_waiting_for_external_simulation_cycle,
	    list_constant_93);
    list_constant_124 = STATIC_LIST((SI_Long)3L,list_constant_121,
	    list_constant_122,list_constant_123);
    list_constant_125 = STATIC_LIST((SI_Long)2L,Qand,Qsynchronization_mode);
    list_constant_71 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_124,list_constant_125);
    define_type_specification_explicit_complex_type(Qsimulation_control_specification,
	    list_constant_71);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsimulation_control_specification);
    Qas_fast_as_possible = STATIC_SYMBOL("AS-FAST-AS-POSSIBLE",AB_package);
    simulation_control_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(simulation_control_specification_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsimulation_control_specification,
	    simulation_control_specification_evaluation_setter_1);
    simulation_control_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(simulation_control_specification_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsimulation_control_specification,
	    simulation_control_specification_evaluation_getter_1);
    string_constant_200 = STATIC_STRING("1l1m83-ey83Sy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_200));
    array_constant_6 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_positive_integer_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-INTEGER-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_integer_for_slot,
	    STATIC_FUNCTION(compile_positive_integer_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qpositive_integer,
	    SYMBOL_FUNCTION(Qcompile_positive_integer_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_integer,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_positive_integer_from_slot = 
	    STATIC_SYMBOL("WRITE-POSITIVE-INTEGER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_positive_integer_from_slot,
	    STATIC_FUNCTION(write_positive_integer_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qpositive_integer,
	    SYMBOL_FUNCTION(Qwrite_positive_integer_from_slot),
	    Qslot_value_writer);
    string_constant_201 = STATIC_STRING("1m1m832fy1m9k83Zy1m832fy83Sy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_201));
    Qcompile_positive_integer_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-POSITIVE-INTEGER\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_positive_integer_qm_for_slot,
	    STATIC_FUNCTION(compile_positive_integer_qm_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qpositive_integer_qm,
	    SYMBOL_FUNCTION(Qcompile_positive_integer_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qpositive_integer_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_read_only_positive_integer_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-READ-ONLY-POSITIVE-INTEGER\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_read_only_positive_integer_qm_for_slot,
	    STATIC_FUNCTION(compile_read_only_positive_integer_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qread_only_positive_integer_qm,
	    SYMBOL_FUNCTION(Qcompile_read_only_positive_integer_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qread_only_positive_integer_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_positive_integer_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-POSITIVE-INTEGER\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_positive_integer_qm_from_slot,
	    STATIC_FUNCTION(write_positive_integer_qm_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qpositive_integer_qm,
	    SYMBOL_FUNCTION(Qwrite_positive_integer_qm_from_slot),
	    Qslot_value_writer);
    string_constant_202 = STATIC_STRING("1l1m83-Yy83Sy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_202));
    array_constant_7 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)41L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)42L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)43L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)45L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)54L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)55L,(SI_Long)57344L);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qcompile_priority_for_slot = STATIC_SYMBOL("COMPILE-PRIORITY-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_priority_for_slot,
	    STATIC_FUNCTION(compile_priority_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qpriority,
	    SYMBOL_FUNCTION(Qcompile_priority_for_slot),Qslot_value_compiler);
    mutate_global_property(Qpriority,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_priority_from_slot = STATIC_SYMBOL("WRITE-PRIORITY-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_priority_from_slot,
	    STATIC_FUNCTION(write_priority_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qpriority,
	    SYMBOL_FUNCTION(Qwrite_priority_from_slot),Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qpriority),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_73 = STATIC_LIST((SI_Long)11L,Qmember,FIX((SI_Long)1L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),FIX((SI_Long)6L),FIX((SI_Long)7L),
	    FIX((SI_Long)8L),FIX((SI_Long)9L),FIX((SI_Long)10L));
    define_type_specification_explicit_complex_type(Qpriority,
	    list_constant_73);
    list_constant_72 = STATIC_LIST((SI_Long)2L,Qnamed,Qpriority);
    priority_evaluation_setter_1 = 
	    STATIC_FUNCTION(priority_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpriority,
	    priority_evaluation_setter_1);
    priority_evaluation_getter_1 = 
	    STATIC_FUNCTION(priority_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpriority,
	    priority_evaluation_getter_1);
    string_constant_203 = STATIC_STRING("1m1m83*7y83Sy1m83-7Wy83-Hy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_203));
    array_constant_8 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_non_negative_integer_for_slot = 
	    STATIC_SYMBOL("COMPILE-NON-NEGATIVE-INTEGER-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_non_negative_integer_for_slot,
	    STATIC_FUNCTION(compile_non_negative_integer_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qnon_negative_integer,
	    SYMBOL_FUNCTION(Qcompile_non_negative_integer_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnon_negative_integer,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_non_negative_integer_from_slot = 
	    STATIC_SYMBOL("WRITE-NON-NEGATIVE-INTEGER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_non_negative_integer_from_slot,
	    STATIC_FUNCTION(write_non_negative_integer_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qnon_negative_integer,
	    SYMBOL_FUNCTION(Qwrite_non_negative_integer_from_slot),
	    Qslot_value_writer);
    array_constant_9 = STATIC_ARRAY(list_constant_75,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)40L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    Qnon_negative_number = STATIC_SYMBOL("NON-NEGATIVE-NUMBER",AB_package);
    Qcompile_non_negative_number_for_slot = 
	    STATIC_SYMBOL("COMPILE-NON-NEGATIVE-NUMBER-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_non_negative_number_for_slot,
	    STATIC_FUNCTION(compile_non_negative_number_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qnon_negative_number,
	    SYMBOL_FUNCTION(Qcompile_non_negative_number_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnon_negative_number,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_non_negative_number_from_slot = 
	    STATIC_SYMBOL("WRITE-NON-NEGATIVE-NUMBER-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_non_negative_number_from_slot,
	    STATIC_FUNCTION(write_non_negative_number_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qnon_negative_number,
	    SYMBOL_FUNCTION(Qwrite_non_negative_number_from_slot),
	    Qslot_value_writer);
    string_constant_204 = STATIC_STRING("1m1m83D-y83=xy1m83D-y1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_204));
    string_constant_63 = 
	    STATIC_STRING("This formula cannot be computed for this variable.");
    Qinstance_formula = STATIC_SYMBOL("INSTANCE-FORMULA",AB_package);
    Qcompile_instance_formula_for_slot = 
	    STATIC_SYMBOL("COMPILE-INSTANCE-FORMULA-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_instance_formula_for_slot,
	    STATIC_FUNCTION(compile_instance_formula_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinstance_formula,
	    SYMBOL_FUNCTION(Qcompile_instance_formula_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinstance_formula,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    mutate_global_property(Qinstance_formula,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    string_constant_205 = STATIC_STRING("1m1m83DXy831Py1m83DXy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_205));
    Qlogical_instance_formula = STATIC_SYMBOL("LOGICAL-INSTANCE-FORMULA",
	    AB_package);
    Qcompile_logical_instance_formula_for_slot = 
	    STATIC_SYMBOL("COMPILE-LOGICAL-INSTANCE-FORMULA-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_logical_instance_formula_for_slot,
	    STATIC_FUNCTION(compile_logical_instance_formula_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qlogical_instance_formula,
	    SYMBOL_FUNCTION(Qcompile_logical_instance_formula_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlogical_instance_formula,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    mutate_global_property(Qlogical_instance_formula,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qtranslate_generic_formula = STATIC_SYMBOL("TRANSLATE-GENERIC-FORMULA",
	    AB_package);
    string_constant_206 = 
	    STATIC_STRING("1u1o836wy1o1m9k83-cYy83-cQy1m9k9l83=xy1mmo9m1o836wy1o1m9k83-cYy83-cQy1m9k9l831Py1mmo9m1n83-cQy1p1m9k9n83*my1m9k83-Ty1m9k83=by83-");
    string_constant_207 = 
	    STATIC_STRING("Gy1mmp1n83-cQy1q1m9k9n83*my83*Zy1m9k83-Ty1m9k83=by83-Gy1m2lmnq1n83-cQy1q1m9k9n83*my1m9k83-Ty1m9k83=by83-Gy83*Zy1mm2lpq1n83-cQy1r");
    string_constant_208 = 
	    STATIC_STRING("1m9k9n83*my83*Zy1m9k83-Ty1m9k83=by83-Gy83*Zy1m2lmn2lqr1n83-cQy1r1m9k9n83-Gy1m9k83=my83*my1m9k83-Ty1m9k83=by83-Gy1m1n830=ymor1n83");
    string_constant_209 = 
	    STATIC_STRING("-cQy1s1m9k9n83-Gy1m9k83=my83*my83*Zy1m9k83-Ty1m9k83=by83-Gy1m2l1n830=ymops1n83-cQy1s1m9k9n83-Gy1m9k83=my83*my1m9k83-Ty1m9k83=by8");
    string_constant_210 = 
	    STATIC_STRING("3-Gy83*Zy1m1n830=ymo2lrs1n83-cQy1t1m9k9n83-Gy1m9k83=my83*my83*Zy1m9k83-Ty1m9k83=by83-Gy83*Zy1m2l1n830=ymop2lst");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qtranslate_generic_formula);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_206,
	    string_constant_207,string_constant_208,string_constant_209,
	    string_constant_210)));
    SET_SYMBOL_FUNCTION(Qtranslate_generic_formula,
	    STATIC_FUNCTION(translate_generic_formula,NIL,FALSE,1,1));
    Qg2_lambda = STATIC_SYMBOL("G2-LAMBDA",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_126 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant_74 = STATIC_LIST((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_126);
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    Qcompile_generic_formula_for_slot = 
	    STATIC_SYMBOL("COMPILE-GENERIC-FORMULA-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_generic_formula_for_slot,
	    STATIC_FUNCTION(compile_generic_formula_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qgeneric_formula,
	    SYMBOL_FUNCTION(Qcompile_generic_formula_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgeneric_formula,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qtranslate_generic_simulation_formula = 
	    STATIC_SYMBOL("TRANSLATE-GENERIC-SIMULATION-FORMULA",AB_package);
    SET_SYMBOL_FUNCTION(Qtranslate_generic_simulation_formula,
	    STATIC_FUNCTION(translate_generic_simulation_formula,NIL,FALSE,
	    1,1));
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qtranslate_role_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-AND-PREPOSITION",AB_package);
    Qtranslate_role_local_name_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-LOCAL-NAME-AND-PREPOSITION",
	    AB_package);
    string_constant_211 = 
	    STATIC_STRING("13My1m835Ty83-qoy1m835Ty83-Qry1o83-Qry1n83-cRy1m9k9l83-WCy1pln83uxy009m1o83-Qry1n83-cRy1m9k9l83n8y1pln83uxy009m1o83-Qry1s83-cRy1");
    string_constant_212 = 
	    STATIC_STRING("m9k9l83-WCy1m9k83vy1m9k83=Fy1m9k831Ay1m9k83-Zdy832iy1pln83uxy0s9m1o83-qoy1w1m9k83nOy1m9k83*dy1m9k83-Py1m9k83uVy1m9k9n1m9k83vOy1m");
    string_constant_213 = 
	    STATIC_STRING("9k83-9y83-cRy1m9k83-Ay1m9k9l83-WCy83-qpy2nsv83gJyw9m1o83-qoy1u1m9k83nOy1m9k83*dy1m9k83-Py1m9k837Fy1m9k83*ly1m9k83-Ty83-cRy1m9k9l");
    string_constant_214 = 
	    STATIC_STRING("83-WCy83-qpy2nrt83glyu9m1n83-qpy1p1m9k83vy1m9k83=Fy1m9k83Cxy1m9k83*ly83-piy1mp01n83-qpy1v1m9k83vy1m9k83=Fy1m9k83Cxy1m9k83*ly83-p");
    string_constant_215 = 
	    STATIC_STRING("iy1m9k83vy1m9k83-ty1m9k83=Fy1m9k831Ay1m9k83-Zdy832iy1mpv1m83-piy836Ey1n83-piy1o1m9k9o1m9k831Sy1m9k83=vy1m9k83*ly1l83-PVy1m83-WCy");
    string_constant_216 = 
	    STATIC_STRING("836Ey1m83-cxy836Ey1o83-cxy1n836Ey1m9k83vy83-cxy1nmln9p1m83-cRy834Hy1m83-cRy1n1m9k9o83gFy83-cRy1m83-cRy1n1m9k9o83-cPy83-cRy1m83-c");
    string_constant_217 = 
	    STATIC_STRING("Ry1n1m9k9o83-cPy83-cOy1m83-cOy1m1m9k83=by83-Gy1n83-cOy1n1m9k83=by83-Gy83*Zy1m83=by2lmn1o83-cPy1m83-Gy83t=y1mlm9q1o83-cPy1m83*my1");
    string_constant_218 = 
	    STATIC_STRING("m9k83-Ty1mlm9q1o83-cPy1o83-Gy1m9k83=my83*my1m9k83-Ty1m1n830=ylno9q1o83-cPy1n83-Gy83*Zy83t=y1nlmn9r1o83-cPy1n83*my83*Zy1m9k83-Ty1");
    string_constant_219 = 
	    STATIC_STRING("nlmn9r1o83-cPy1p83-Gy1m9k83=my83*my83*Zy1m9k83-Ty1n1n830=ylnop9r");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qtranslate_generic_simulation_formula);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qtranslate_role_and_preposition);
    push_optimized_constant(Qtranslate_role_local_name_and_preposition);
    add_grammar_rules_function(regenerate_optimized_constant(list(9,
	    string_constant_211,string_constant_212,string_constant_213,
	    string_constant_214,string_constant_215,string_constant_216,
	    string_constant_217,string_constant_218,string_constant_219)));
    Qgeneric_simulation_formula_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA-BYTE-CODE-BODY",
	    AB_package);
    Qgeneric_simulation_initial_value_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qcompile_generic_simulation_formula_for_slot = 
	    STATIC_SYMBOL("COMPILE-GENERIC-SIMULATION-FORMULA-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_generic_simulation_formula_for_slot,
	    STATIC_FUNCTION(compile_generic_simulation_formula_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qgeneric_simulation_formula,
	    SYMBOL_FUNCTION(Qcompile_generic_simulation_formula_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgeneric_simulation_formula,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcurrent_parameter_value = STATIC_SYMBOL("CURRENT-PARAMETER-VALUE",
	    AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
}
