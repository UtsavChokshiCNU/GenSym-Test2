/* slots.c
 * Input file:  slots.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "slots.h"


static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

static Object Qab_gensym;          /* gensym */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qrelation_instance_tree;  /* relation-instance-tree */

static Object Qconnection_item_table;  /* connection-item-table */

static Object Qdefined_evaluation_type_copier;  /* defined-evaluation-type-copier */

/* COPY-FOR-SLOT-VALUE */
Object copy_for_slot_value(value_for_slot)
    Object value_for_slot;
{
    Object length_1, new_array, value_to_copy, temp, svref_new_value;
    Object amf_available_array_cons_qm, amf_array, amf_result, incff_1_arg;
    Object new_float, new_long, x2, gensymed_symbol, sub_class_bit_vector;
    Object gensymed_symbol_4, cdr_of_cons, car_of_cons, element, ab_loop_list_;
    Object contents, ab_loopvar_, ab_loopvar__1, property_list;
    Object gensymed_symbol_5, next_cdr, temp_2, new_list, cons_to_copy;
    Object new_cons, car_to_copy;
    SI_Long index_1, ab_loop_bind_, svref_arg_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, ab_loopvar__2;
    SI_int64 aref_new_value_1;
    char temp_1;
    double aref_new_value;

    x_note_fn_call(83,0);
    if ( !TRUEP(value_for_slot) || FIXNUMP(value_for_slot) || 
	    SYMBOLP(value_for_slot) || EQ(value_for_slot,No_value))
	return VALUES_1(value_for_slot);
    else if (SIMPLE_VECTOR_P(value_for_slot) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_for_slot)) == (SI_Long)3L 
	    && EQ(ISVREF(value_for_slot,(SI_Long)2L),Constant_queue_marker))
	return VALUES_1(Nil);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_for_slot) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_for_slot)) == (SI_Long)1L)
	return copy_managed_float(value_for_slot);
    else if (INLINE_LONG_VECTOR_P(value_for_slot) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_for_slot)) == (SI_Long)1L)
	return copy_managed_long(value_for_slot);
    else if (STRINGP(value_for_slot) || text_string_p(value_for_slot))
	return copy_text_string(value_for_slot);
    else if (SIMPLE_VECTOR_P(value_for_slot) && EQ(ISVREF(value_for_slot,
	    (SI_Long)0L),Managed_float_array_unique_marker))
	return copy_managed_float_array(value_for_slot);
    else if (SIMPLE_VECTOR_P(value_for_slot) && EQ(ISVREF(value_for_slot,
	    (SI_Long)0L),Managed_array_unique_marker)) {
	length_1 = ISVREF(value_for_slot,(SI_Long)1L);
	new_array = allocate_managed_array(1,length_1);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length_1);
	value_to_copy = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value_to_copy = FIXNUM_LE(ISVREF(value_for_slot,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(value_for_slot,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(value_for_slot,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(new_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    temp = value_to_copy ? copy_for_slot_value(value_to_copy) : Nil;
	    ISVREF(new_array,svref_arg_2) = temp;
	}
	else {
	    temp = ISVREF(new_array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    svref_new_value = value_to_copy ? 
		    copy_for_slot_value(value_to_copy) : Nil;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(new_array);
	return VALUES_1(Qnil);
    }
    else if (SIMPLE_VECTOR_P(value_for_slot) && EQ(ISVREF(value_for_slot,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_byte_code_body_g2_struct))
	return copy_byte_code_body(value_for_slot);
    else if (FLOATP(value_for_slot)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value_for_slot);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (INLINE_LONG_P(value_for_slot) != (SI_Long)0L) {
	new_long = allocate_managed_long_box();
	aref_new_value_1 = INTEGER_TO_INT64(value_for_slot);
	set_aref1(new_long,FIX((SI_Long)0L),
		INT64_TO_INTEGER(aref_new_value_1));
	return VALUES_1(new_long);
    }
    else {
	if (SIMPLE_VECTOR_P(value_for_slot) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_for_slot)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_for_slot,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_for_slot,(SI_Long)1L);
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
		    IFIX(ISVREF(Dependent_frame_class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(value_for_slot,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)17L),(SI_Long)1L);
	    gensymed_symbol_4 = value_for_slot;
	    return inline_funcall_1(gensymed_symbol,gensymed_symbol_4);
	}
	else if (CONSP(value_for_slot) && EQ(CAR(value_for_slot),
		Qrelation_instance_tree))
	    return VALUES_1(Nil);
	else if (CONSP(value_for_slot) && EQ(CAR(value_for_slot),
		Qconnection_item_table))
	    return VALUES_1(Nil);
	else if (CONSP(value_for_slot)) {
	    cdr_of_cons = CDR(value_for_slot);
	    if ( !TRUEP(cdr_of_cons)) {
		car_of_cons = CAR(value_for_slot);
		return gensym_cons_1( !TRUEP(car_of_cons) || 
			SYMBOLP(car_of_cons) || FIXNUMP(car_of_cons) ? 
			car_of_cons : copy_for_slot_value(car_of_cons),Nil);
	    }
	    else if (EQ(cdr_of_cons,Phrase_sequence_marker)) {
		element = Nil;
		ab_loop_list_ = M_CAR(value_for_slot);
		contents = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__1 = gensym_cons_1(copy_for_slot_value(element),
			Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    contents = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop_1;
	      end_loop_1:
		return allocate_evaluation_sequence(contents);
		return VALUES_1(Qnil);
	    }
	    else if (EQ(cdr_of_cons,Phrase_structure_marker)) {
		element = Nil;
		ab_loop_list_ = M_CAR(value_for_slot);
		property_list = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__1 = gensym_cons_1(copy_for_slot_value(element),
			Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    property_list = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop_2;
	      end_loop_2:
		return allocate_evaluation_structure(property_list);
		return VALUES_1(Qnil);
	    }
	    else if (EQ(cdr_of_cons,Phrase_item_denotation_marker))
		return find_frame_for_denotation(1,M_CAR(value_for_slot));
	    else if (EQ(cdr_of_cons,Phrase_item_marker))
		return VALUES_1(M_CAR(value_for_slot));
	    else {
		if (SYMBOLP(cdr_of_cons)) {
		    gensymed_symbol = CDR(Defined_evaluation_value_types);
		    gensymed_symbol_4 = cdr_of_cons;
		    gensymed_symbol_1 = SXHASH_SYMBOL_1(cdr_of_cons) & 
			    IFIX(Most_positive_fixnum);
		    gensymed_symbol_2 = (SI_Long)0L;
		  next_loop_3:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_3;
		    gensymed_symbol_2 = IFIX(ISVREF(gensymed_symbol,
			    (SI_Long)0L));
		    if (gensymed_symbol_1 < gensymed_symbol_2)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else if (gensymed_symbol_1 > gensymed_symbol_2)
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		    else {
			gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
			gensymed_symbol_5 = Nil;
		      next_loop_4:
			if ( !TRUEP(gensymed_symbol))
			    goto end_loop_4;
			gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol));
			if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
			    temp_1 = TRUEP(M_CDR(M_CAR(gensymed_symbol)));
			    goto end_1;
			}
			gensymed_symbol = M_CDR(gensymed_symbol);
			goto next_loop_4;
		      end_loop_4:
			temp_1 = TRUEP(Qnil);
		      end_1:;
			goto end_2;
		    }
		    goto next_loop_3;
		  end_loop_3:
		    temp_1 = TRUEP(Qnil);
		  end_2:;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    gensymed_symbol = get_property_value_function(3,
			    get_symbol_properties_function(cdr_of_cons),
			    Qdefined_evaluation_type_copier,Nil);
		    gensymed_symbol_4 = value_for_slot;
		    return VALUES_1(inline_funcall_1(gensymed_symbol,
			    gensymed_symbol_4));
		}
		else {
		    next_cdr = cdr_of_cons;
		    ab_loopvar__2 = (SI_Long)0L;
		  next_loop_5:
		    ab_loopvar__2 = ab_loopvar__2 + (SI_Long)1L;
		    if (ATOM(next_cdr))
			goto end_loop_5;
		    next_cdr = CDR(next_cdr);
		    goto next_loop_5;
		  end_loop_5:
		    temp_2 = FIX(ab_loopvar__2);
		    goto end_3;
		    temp_2 = Qnil;
		  end_3:;
		    new_list = make_gensym_list_1(temp_2);
		    cons_to_copy = value_for_slot;
		    new_cons = new_list;
		    car_to_copy = Nil;
		  next_loop_6:
		    car_to_copy = CAR(cons_to_copy);
		    temp =  !TRUEP(car_to_copy) || SYMBOLP(car_to_copy) || 
			    FIXNUMP(car_to_copy) || EQ(value_for_slot,
			    No_value) ? car_to_copy : 
			    copy_for_slot_value(car_to_copy);
		    M_CAR(new_cons) = temp;
		    if ( !TRUEP(CDR(new_cons))) {
			if (CDR(cons_to_copy)) {
			    temp = copy_for_slot_value(CDR(cons_to_copy));
			    M_CDR(new_cons) = temp;
			}
			return VALUES_1(new_list);
		    }
		    cons_to_copy = CDR(cons_to_copy);
		    new_cons = CDR(new_cons);
		    goto next_loop_6;
		  end_loop_6:
		    return VALUES_1(Qnil);
		}
	    }
	}
	else
	    return VALUES_1(value_for_slot);
    }
}

void slots_INIT()
{
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(83,1);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrelation_instance_tree = STATIC_SYMBOL("RELATION-INSTANCE-TREE",
	    AB_package);
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qdefined_evaluation_type_copier = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COPIER",AB_package);
}
