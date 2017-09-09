/* frmts.c
 * Input file:  formats.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frmts.h"


/* PUT-LIST-OF-PROCEDURE-INSTANCES-FOR-ENTITY-WHERE-SLOT-IS-ABSENT */
Object put_list_of_procedure_instances_for_entity_where_slot_is_absent(format_frame,
	    list_of_procedure_instances_for_entity)
    Object format_frame, list_of_procedure_instances_for_entity;
{
    x_note_fn_call(105,0);
    return VALUES_1(Nil);
}

Object Format_description_prop = UNBOUND;

static Object Qformat_frame;       /* format-frame */

/* GET-OR-MAKE-FORMAT-FRAME-FUNCTION */
Object get_or_make_format_frame_function(format_name)
    Object format_name;
{
    Object temp;

    x_note_fn_call(105,1);
    temp = get_instance_with_name_if_any(Qformat_frame,format_name);
    if (temp)
	return VALUES_1(temp);
    else
	return make_format_frame(format_name);
}

static Object Qformat_description;  /* format-description */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qformat_change_qm;   /* format-change? */

static Object list_constant;       /* # */

/* CHANGE-STANDARD-FORMAT-FRAME-SLOT */
Object change_standard_format_frame_slot(format_name,slot_name,new_value)
    Object format_name, slot_name, new_value;
{
    Object old_format_frame_qm, temp, new_format_frame, ab_loopvar_;
    Object old_format_frame, ab_loop_it_, denotations_of_differing_slots;
    Object slot_denotation, ab_loop_list_;
    char temp_1;

    x_note_fn_call(105,2);
    old_format_frame_qm = get_instance_with_name_if_any(Qformat_frame,
	    format_name);
    if (old_format_frame_qm) {
	temp = get_slot_value_function(old_format_frame_qm,slot_name,Nil);
	temp_1 = EQL(temp,new_value);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(old_format_frame_qm);
    else {
	if ( !TRUEP(old_format_frame_qm)) {
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name),
		    Qformat_description);
	    temp = getf(CDR(temp),slot_name,_);
	    temp_1 = EQL(temp,new_value);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(Nil);
	else {
	    if (old_format_frame_qm) {
		change_slot_value(3,old_format_frame_qm,
			Qname_or_names_for_frame,Nil);
		change_slot_value(3,old_format_frame_qm,Qformat_change_qm,
			format_name);
	    }
	    new_format_frame = get_instance_with_name_if_any(Qformat_frame,
		    format_name);
	    if (new_format_frame);
	    else
		new_format_frame = make_format_frame(format_name);
	    change_slot_value(3,new_format_frame,slot_name,new_value);
	    ab_loopvar_ = 
		    lookup_kb_specific_property_value(ISVREF(ISVREF(new_format_frame,
		    (SI_Long)1L),(SI_Long)1L),
		    Instances_specific_to_this_class_kbprop);
	    old_format_frame = Nil;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop;
	    old_format_frame = ab_loopvar_;
	    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
	    if ( !EQ(old_format_frame,new_format_frame) &&  
		    !TRUEP(get_lookup_slot_value_given_default(old_format_frame,
		    Qname_or_names_for_frame,Nil)) && 
		    EQ(get_lookup_slot_value_given_default(old_format_frame,
		    Qformat_change_qm,Nil),format_name)) {
		denotations_of_differing_slots = 
			find_differences_in_frames_if_any(2,
			old_format_frame,new_format_frame);
		slot_denotation = Nil;
		ab_loop_list_ = denotations_of_differing_slots;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		slot_denotation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(memq_function(CONSP(slot_denotation) ? 
			M_CAR(M_CDR(M_CDR(slot_denotation))) : 
			slot_denotation,list_constant))) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		goto next_loop_1;
	      end_loop_1:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
		if (temp_1) {
		    delete_frame(new_format_frame);
		    change_slot_value(3,old_format_frame,
			    Qname_or_names_for_frame,format_name);
		    change_slot_value(3,old_format_frame,Qformat_change_qm,
			    Nil);
		    temp = old_format_frame;
		}
		else
		    temp = Nil;
		reclaim_slot_value(denotations_of_differing_slots);
		ab_loop_it_ = temp;
		if (ab_loop_it_) {
		    temp = ab_loop_it_;
		    goto end_2;
		}
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_2:;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(new_format_frame);
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_to_delete_after_reading_kb, Qblocks_to_delete_after_reading_kb);

/* FIND-EXISTING-EQUIVALENT-FORMAT-FRAME */
Object find_existing_equivalent_format_frame(format_frame)
    Object format_frame;
{
    Object ab_loopvar_, old_format_frame;

    x_note_fn_call(105,3);
    ab_loopvar_ = 
	    lookup_kb_specific_property_value(ISVREF(ISVREF(format_frame,
	    (SI_Long)1L),(SI_Long)1L),Instances_specific_to_this_class_kbprop);
    old_format_frame = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    old_format_frame = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    if ( !EQ(old_format_frame,format_frame) &&  
	    !TRUEP(get_lookup_slot_value_given_default(old_format_frame,
	    Qname_or_names_for_frame,Nil)) && ( !TRUEP(Reading_kb_p) ||  
	    !TRUEP(memq_function(old_format_frame,
	    Blocks_to_delete_after_reading_kb))) &&  
	    !TRUEP(find_differences_in_frames_if_any(3,format_frame,
	    old_format_frame,T)))
	return VALUES_1(old_format_frame);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qframe_flags;        /* frame-flags */

/* MAKE-FORMAT-FRAME */
Object make_format_frame(format_name)
    Object format_name;
{
    Object format_description, format_frame, slot_name, slot_init_form;
    Object ab_loop_list_, temp, new_value;
    SI_Long svref_new_value;

    x_note_fn_call(105,4);
    format_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name),
	    Qformat_description);
    if (format_description);
    else
	format_description = error((SI_Long)2L,
		"No format description found for ~a",format_name);
    format_frame = make_frame(CAR(format_description));
    put_name_or_names_for_frame(format_frame,format_name,T);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(format_frame,Qframe_flags);
    svref_new_value = IFIX(ISVREF(format_frame,(SI_Long)4L)) | (SI_Long)1L;
    ISVREF(format_frame,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p) {
	svref_new_value = IFIX(ISVREF(format_frame,(SI_Long)5L)) | (SI_Long)4L;
	ISVREF(format_frame,(SI_Long)5L) = FIX(svref_new_value);
    }
    slot_name = Nil;
    slot_init_form = Nil;
    ab_loop_list_ = CDR(format_description);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    slot_name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    slot_init_form = CAR(temp);
    new_value = copy_for_slot_value(slot_init_form);
    initialize_slot_description_value(format_frame,
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(format_frame,(SI_Long)1L),Nil),new_value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return VALUES_1(format_frame);
}

DEFINE_VARIABLE_WITH_SYMBOL(Fonts, Qfonts);

/* WRITE-FONT-NAME-FROM-SLOT */
Object write_font_name_from_slot(form,gensymed_symbol)
    Object form, gensymed_symbol;
{
    x_note_fn_call(105,5);
    return twrite(form);
}

Object Corresponding_small_font_format_name_prop = UNBOUND;

Object Corresponding_extra_large_font_format_name_prop = UNBOUND;

/* CHOOSE-FONT-FORMAT-PER-FONTS-TABLE */
Object choose_font_format_per_fonts_table(large_font_format_name,
	    fonts_slot_name)
    Object large_font_format_name, fonts_slot_name;
{
    x_note_fn_call(105,6);
    return choose_font_format_per_font_size(large_font_format_name,
	    get_slot_value_function(Fonts,fonts_slot_name,Nil));
}

static Object Qnew_class_format;   /* new-class-format */

static Object Qclass_format;       /* class-format */

static Object Qfont_for_attribute_tables;  /* font-for-attribute-tables */

/* PARAMETERIZED-ATTRIBUTE-TABLE-HEADER-FORMAT */
Object parameterized_attribute_table_header_format()
{
    x_note_fn_call(105,7);
    if (New_g2_classic_ui_p)
	return VALUES_1(Qnew_class_format);
    else
	return choose_font_format_per_fonts_table(Qclass_format,
		Qfont_for_attribute_tables);
}

static Object Qnew_attribute_description_format;  /* new-attribute-description-format */

static Object Qattribute_description_format;  /* attribute-description-format */

/* PARAMETERIZED-ATTRIBUTE-DESCRIPTION-FORMAT */
Object parameterized_attribute_description_format()
{
    x_note_fn_call(105,8);
    if (New_g2_classic_ui_p)
	return VALUES_1(Qnew_attribute_description_format);
    else
	return choose_font_format_per_fonts_table(Qattribute_description_format,
		Qfont_for_attribute_tables);
}

static Object Qnew_attribute_value_format;  /* new-attribute-value-format */

static Object Qattribute_value_format;  /* attribute-value-format */

/* PARAMETERIZED-ATTRIBUTE-VALUE-FORMAT */
Object parameterized_attribute_value_format()
{
    x_note_fn_call(105,9);
    if (New_g2_classic_ui_p)
	return VALUES_1(Qnew_attribute_value_format);
    else
	return choose_font_format_per_fonts_table(Qattribute_value_format,
		Qfont_for_attribute_tables);
}

static Object Qsmall;              /* small */

static Object Qcorresponding_small_font_format_name;  /* corresponding-small-font-format-name */

static Object Qextra_large;        /* extra-large */

static Object Qcorresponding_extra_large_font_format_name;  /* corresponding-extra-large-font-format-name */

/* CHOOSE-FONT-FORMAT-PER-FONT-SIZE */
Object choose_font_format_per_font_size(large_font_format_name,font_size_qm)
    Object large_font_format_name, font_size_qm;
{
    Object temp;

    x_note_fn_call(105,10);
    if (font_size_qm) {
	if (EQ(font_size_qm,Qsmall))
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(large_font_format_name),
		    Qcorresponding_small_font_format_name);
	else if (EQ(font_size_qm,Qextra_large))
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(large_font_format_name),
		    Qcorresponding_extra_large_font_format_name);
	else
	    temp = Qnil;
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(large_font_format_name);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qlarge;              /* large */

/* DETERMINE-FONT-SIZE-PER-FORMAT */
Object determine_font_size_per_format(format_name_or_format_frame,
	    large_font_format_name)
    Object format_name_or_format_frame, large_font_format_name;
{
    Object format_name, x2, font_name, temp_1;
    char temp;

    x_note_fn_call(105,11);
    format_name = SYMBOLP(format_name_or_format_frame) ? 
	    format_name_or_format_frame : 
	    get_lookup_slot_value_given_default(format_name_or_format_frame,
	    Qname_or_names_for_frame,Nil);
    if ( !TRUEP(format_name)) {
	if (SIMPLE_VECTOR_P(format_name_or_format_frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(format_name_or_format_frame)) 
		> (SI_Long)2L &&  !EQ(ISVREF(format_name_or_format_frame,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(format_name_or_format_frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	font_name = text_cell_first_font(format_name_or_format_frame);
	format_name = 
		choose_font_format_per_font_size(large_font_format_name,
		Qextra_large);
	temp_1 = get_instance_with_name_if_any(Qformat_frame,format_name);
	if (temp_1);
	else
	    temp_1 = make_format_frame(format_name);
	if (EQ(font_name,text_cell_first_font(temp_1)))
	    temp_1 = Qextra_large;
	else {
	    format_name = 
		    choose_font_format_per_font_size(large_font_format_name,
		    Qsmall);
	    temp_1 = get_instance_with_name_if_any(Qformat_frame,format_name);
	    if (temp_1);
	    else
		temp_1 = make_format_frame(format_name);
	    if (EQ(font_name,text_cell_first_font(temp_1)))
		temp_1 = Qsmall;
	    else {
		format_name = 
			choose_font_format_per_font_size(large_font_format_name,
			Qlarge);
		temp_1 = get_instance_with_name_if_any(Qformat_frame,
			format_name);
		if (temp_1);
		else
		    temp_1 = make_format_frame(format_name);
		if (EQ(font_name,text_cell_first_font(temp_1)))
		    temp_1 = Qlarge;
		else
		    temp_1 = Qnil;
	    }
	}
    }
    else if (EQ(format_name,
	    choose_font_format_per_font_size(large_font_format_name,
	    Qextra_large)))
	temp_1 = Qextra_large;
    else if (EQ(format_name,
	    choose_font_format_per_font_size(large_font_format_name,Qsmall)))
	temp_1 = Qsmall;
    else if (EQ(format_name,
	    choose_font_format_per_font_size(large_font_format_name,Qlarge)))
	temp_1 = Qlarge;
    else
	temp_1 = Qnil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(Qlarge);
}

/* RECLAIM-FRAME-DESCRIPTION-REFERENCE-OF-FRAME-STYLE-DEFINITION?-VALUE */
Object reclaim_frame_description_reference_of_frame_style_definition_qm_value(frame_description_reference_qm,
	    frame_style_definition)
    Object frame_description_reference_qm, frame_style_definition;
{
    Object svref_new_value;

    x_note_fn_call(105,12);
    if (frame_description_reference_qm) {
	SVREF(frame_description_reference_qm,FIX((SI_Long)3L)) = T;
	svref_new_value = 
		release_frame_description_reference_if_any(frame_description_reference_qm);
	ISVREF(frame_style_definition,(SI_Long)21L) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qframe_style_definition;  /* frame-style-definition */

/* INITIALIZE-FOR-FRAME-STYLE-DEFINITION */
Object initialize_for_frame_style_definition(frame_style_definition)
    Object frame_style_definition;
{
    Object frame, sub_vector_qm, method_function_qm, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;

    x_note_fn_call(105,13);
    frame = frame_style_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qframe_style_definition)) {
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
    method_index = (SI_Long)19L;
    frame = frame_style_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    if (function_qm)
	return inline_funcall_1(function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qdescription_of_frame;  /* description-of-frame */

/* CLEANUP-FOR-FRAME-STYLE-DEFINITION */
Object cleanup_for_frame_style_definition(frame_style_definition)
    Object frame_style_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(105,14);
    frame = frame_style_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qframe_style_definition)) {
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
    if (ISVREF(frame_style_definition,(SI_Long)20L))
	return change_slot_value(4,frame_style_definition,
		Qdescription_of_frame,Nil,Qframe_style_definition);
    else
	return VALUES_1(Nil);
}

/* PUT-ALWAYS-DISPLAY-ENTIRE-ITEM-INSIDE-FRAME-WHERE-SLOT-IS-ABSENT */
Object put_always_display_entire_item_inside_frame_where_slot_is_absent(frame_style_definition,
	    boolean_1)
    Object frame_style_definition, boolean_1;
{
    x_note_fn_call(105,15);
    return VALUES_1(Nil);
}

static Object string_constant;     /* "the description of frame is missing." */

/* WRITE-FRAME-STYLE-DEFINITION-IS-EMPTY-NOTE */
Object write_frame_style_definition_is_empty_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(105,16);
    GENSYM_RETURN_ONE(tformat(1,string_constant));
    return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qframe_style_definition_is_empty;  /* frame-style-definition-is-empty */

static Object Qincomplete;         /* incomplete */

/* UPDATE-FRAME-STATUS-AND-NOTES-FOR-FRAME-STYLE-DEFINITION */
Object update_frame_status_and_notes_for_frame_style_definition(frame_style_definition)
    Object frame_style_definition;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object frame, sub_vector_qm, method_function_qm, frame_status_qm, temp_1;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long index_1, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(105,17);
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(frame_style_definition,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = 
		nconc2(stack_change_list_2(frame_style_definition,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
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
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = frame_style_definition;
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
      frame = frame_style_definition;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)19L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qframe_style_definition)) {
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
      frame_status_qm = Nil;
      delete_frame_note_if_any(Qframe_style_definition_is_empty,
	      frame_style_definition);
      if ( !TRUEP(ISVREF(frame_style_definition,(SI_Long)20L))) {
	  add_frame_note(5,Qframe_style_definition_is_empty,
		  frame_style_definition,T,T,Nil);
	  frame_status_qm = Qincomplete;
      }
      temp_1 = update_frame_status(frame_style_definition,frame_status_qm,Nil);
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
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
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(frame_style_definition,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_2 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(frame_style_definition,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(frame_style_definition);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
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
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    return result;
}

/* PUT-DESCRIPTION-OF-FRAME */
Object put_description_of_frame(frame_style_definition,new_value,
	    gensymed_symbol)
    Object frame_style_definition, new_value, gensymed_symbol;
{
    Object temp, old_frame_description_reference_qm;
    Object creating_dirty_references_qm, gensymed_symbol_1, temp_1;
    Object frame_style_reference, svref_new_value, names_sic, name, item;
    Object ab_loop_list_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_2;

    x_note_fn_call(105,18);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame_style_definition,Qdescription_of_frame);
    temp = SVREF(frame_style_definition,FIX((SI_Long)20L)) = new_value;
    old_frame_description_reference_qm = ISVREF(frame_style_definition,
	    (SI_Long)21L);
    creating_dirty_references_qm = old_frame_description_reference_qm ? 
	    ((SI_Long)1L < IFIX(ISVREF(old_frame_description_reference_qm,
	    (SI_Long)1L)) ? T : Nil) : Qnil;
    if (old_frame_description_reference_qm)
	reclaim_frame_description_reference_of_frame_style_definition_qm_value(ISVREF(frame_style_definition,
		(SI_Long)21L),frame_style_definition);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame_style_definition,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)19L),(SI_Long)1L);
    gensymed_symbol_1 = frame_style_definition;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    temp_1 = ISVREF(frame_style_definition,(SI_Long)8L);
    if ( !TRUEP(CAR(temp_1))) {
	frame_style_reference = 
		create_frame_description_reference(copy_tree_using_graphics_conses_1(new_value));
	svref_new_value = FIXNUM_ADD1(ISVREF(frame_style_reference,
		(SI_Long)1L));
	SVREF(frame_style_reference,FIX((SI_Long)1L)) = svref_new_value;
	ISVREF(frame_style_definition,(SI_Long)21L) = frame_style_reference;
    }
    if ( !TRUEP(old_frame_description_reference_qm) && 
	    get_lookup_slot_value_given_default(frame_style_definition,
	    Qname_or_names_for_frame,Nil)) {
	names_sic = 
		get_lookup_slot_value_given_default(frame_style_definition,
		Qname_or_names_for_frame,Nil);
	name = Nil;
      next_loop:
	name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
	if ( !TRUEP(name))
	    goto end_loop;
	item = Nil;
	ab_loop_list_ = compiled_items_referring_to_this_name_function(name);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	    temp_2 = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    reconsider_formatting(item);
	goto next_loop_1;
      end_loop_1:;
	names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
	goto next_loop;
      end_loop:;
    }
    if (creating_dirty_references_qm)
	clean_frame_description_references();
    return VALUES_1(temp);
}

/* LOOKUP-FRAME-DESCRIPTION-REFERENCE-FROM-FRAME-STYLE-DEFINITION? */
Object lookup_frame_description_reference_from_frame_style_definition_qm(frame_style)
    Object frame_style;
{
    Object frame_style_description_qm, temp;
    char temp_1;

    x_note_fn_call(105,19);
    frame_style_description_qm = 
	    get_instance_with_name_if_any(Qframe_style_definition,frame_style);
    if (frame_style_description_qm) {
	temp = ISVREF(frame_style_description_qm,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(ISVREF(frame_style_description_qm,(SI_Long)21L));
    else
	return VALUES_1(Nil);
}

void formats_INIT()
{
    Object temp, temp_1, temp_2, write_frame_style_definition_is_empty_note_1;
    Object Qslot_putter, Qput_description_of_frame, AB_package;
    Object Qclasses_which_define, Qupdate_frame_status_and_notes;
    Object Qupdate_frame_status_and_notes_for_frame_style_definition;
    Object Qframe_note_writer_1, Qabsent_slot_putter;
    Object Qput_always_display_entire_item_inside_frame_where_slot_is_absent;
    Object Qalways_display_entire_item_inside_frame, Qcleanup;
    Object Qcleanup_for_frame_style_definition, Qinitialize;
    Object Qinitialize_for_frame_style_definition, Qslot_value_reclaimer;
    Object Qreclaim_frame_description_reference_of_frame_style_definition_qm_value;
    Object Qframe_description_reference_of_frame_style_definition_qm;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object list_constant_3, Qcreate_icon_description, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, list_constant_1, Qitem;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_value_writer;
    Object Qwrite_font_name_from_slot, Qfont_name, string_constant_11;
    Object Ksystem_frame, Qformats, string_constant_10, string_constant_9;
    Object list_constant_2, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, Qsystem_table;
    Object string_constant_4, string_constant_3, string_constant_2;
    Object string_constant_1, Qentity;
    Object Qput_list_of_procedure_instances_for_entity_where_slot_is_absent;
    Object Qlist_of_procedure_instances_for_entity;

    x_note_fn_call(105,20);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qlist_of_procedure_instances_for_entity = 
	    STATIC_SYMBOL("LIST-OF-PROCEDURE-INSTANCES-FOR-ENTITY",AB_package);
    Qput_list_of_procedure_instances_for_entity_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-LIST-OF-PROCEDURE-INSTANCES-FOR-ENTITY-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_list_of_procedure_instances_for_entity_where_slot_is_absent,
	    STATIC_FUNCTION(put_list_of_procedure_instances_for_entity_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qlist_of_procedure_instances_for_entity,
	    SYMBOL_FUNCTION(Qput_list_of_procedure_instances_for_entity_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_1 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qformat_frame,list_constant_1);
    string_constant_1 = STATIC_STRING("1l1l8t");
    string_constant_2 = 
	    STATIC_STRING("1n4z8r83Lvy83Lvy831Fy831Fy00001n1l83Ey1l8l1l83Cy000004z8r83W=y83W=y831Fy831Fy00001n1l8l1l8o1l83Hy000004z8r83W*y83W*y831Fy831Fy00");
    string_constant_3 = STATIC_STRING("001n1l8l1l8o1l83Hy00000");
    string_constant_4 = 
	    STATIC_STRING("1p8q1n831Fy1l83-+y8t1p83Lvy083Ey8l83Cy1o83W=y08o83Hy1o83W*y08o83Hy");
    temp = regenerate_optimized_constant(string_constant_1);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_2,
	    string_constant_3));
    add_class_to_environment(9,Qformat_frame,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_4),Nil);
    Format_frame_class_description = 
	    lookup_global_or_kb_specific_property_value(Qformat_frame,
	    Class_description_gkbprop);
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    Format_description_prop = Qformat_description;
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qformat_change_qm = STATIC_SYMBOL("FORMAT-CHANGE\?",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qname_or_names_for_frame,
	    Qformat_change_qm);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qfonts = STATIC_SYMBOL("FONTS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_2 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qfonts,list_constant_2);
    string_constant_5 = STATIC_STRING("1l1l83ey");
    string_constant_6 = 
	    STATIC_STRING("1q4z8r83Lly83Lly83Lqy83Lqy083=Ay001n1l8l1l8o1m8p838Oy000004z8r83Lky83Lky83Lqy83Lqy083-Vy001n1l8l1l83Ey1m8p838Oy000004z8r83Lpy83L");
    string_constant_7 = 
	    STATIC_STRING("py83Lqy83Lqy083=Ay001n1l8l1l8o1m8p838Oy000004z8r83Loy83Loy83Lqy83Lqy083=Ay001n1l8l1l8o1m8p838Oy000004z8r83Lny83Lny83Lqy83Lqy083=");
    string_constant_8 = 
	    STATIC_STRING("Ay001n1l8l1l8o1m8p838Oy000004z8r83Lmy83Lmy83Lqy83Lqy083-Vy001n1l8l1l8o1m8p838Oy00000");
    string_constant_9 = 
	    STATIC_STRING("1s8q1n83Lqy1l83-sy83ey1p83Lly83=Ay8l8o1m8p838Oy1p83Lky83-Vy8l83Ey1m8p838Oy1p83Lpy83=Ay8l8o1m8p838Oy1p83Loy83=Ay8l8o1m8p838Oy1p83");
    string_constant_10 = 
	    STATIC_STRING("Lny83=Ay8l8o1m8p838Oy1p83Lmy83-Vy8l8o1m8p838Oy");
    temp = regenerate_optimized_constant(string_constant_5);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_6,
	    string_constant_7,string_constant_8));
    add_class_to_environment(9,Qfonts,list_constant_2,Nil,temp,Nil,temp_1,
	    list_constant_2,
	    regenerate_optimized_constant(LIST_2(string_constant_9,
	    string_constant_10)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qfonts,Fonts);
    Qformats = STATIC_SYMBOL("FORMATS",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qfonts,Qformats,Ksystem_frame,Qnil,Qnil,Qnil,Qt);
    string_constant_11 = 
	    STATIC_STRING("1n1m838Oy1m9k83=Ay1m838Oy1m9k83-Vy1m838Oy1m9k83C0y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_11));
    Qfont_name = STATIC_SYMBOL("FONT-NAME",AB_package);
    Qwrite_font_name_from_slot = STATIC_SYMBOL("WRITE-FONT-NAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_font_name_from_slot,
	    STATIC_FUNCTION(write_font_name_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qfont_name,
	    SYMBOL_FUNCTION(Qwrite_font_name_from_slot),Qslot_value_writer);
    Qcorresponding_small_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-SMALL-FONT-FORMAT-NAME",AB_package);
    Corresponding_small_font_format_name_prop = 
	    Qcorresponding_small_font_format_name;
    Qcorresponding_extra_large_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-EXTRA-LARGE-FONT-FORMAT-NAME",
	    AB_package);
    Corresponding_extra_large_font_format_name_prop = 
	    Qcorresponding_extra_large_font_format_name;
    Qnew_class_format = STATIC_SYMBOL("NEW-CLASS-FORMAT",AB_package);
    Qclass_format = STATIC_SYMBOL("CLASS-FORMAT",AB_package);
    Qfont_for_attribute_tables = STATIC_SYMBOL("FONT-FOR-ATTRIBUTE-TABLES",
	    AB_package);
    Qnew_attribute_description_format = 
	    STATIC_SYMBOL("NEW-ATTRIBUTE-DESCRIPTION-FORMAT",AB_package);
    Qattribute_description_format = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTION-FORMAT",AB_package);
    Qnew_attribute_value_format = 
	    STATIC_SYMBOL("NEW-ATTRIBUTE-VALUE-FORMAT",AB_package);
    Qattribute_value_format = STATIC_SYMBOL("ATTRIBUTE-VALUE-FORMAT",
	    AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qframe_style_definition = STATIC_SYMBOL("FRAME-STYLE-DEFINITION",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_3 = STATIC_CONS(Qitem,list_constant_1);
    check_if_superior_classes_are_defined(Qframe_style_definition,
	    list_constant_3);
    string_constant_12 = STATIC_STRING("1l1m8v836ry");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_13 = 
	    STATIC_STRING("1p4z8r83--y83--y836ry836ry00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_14 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_15 = 
	    STATIC_STRING("0004z8r83-0y83-0y836ry836ry00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_16 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u836ry836ry01p8w9k3ky3ky1o1p83Jy1mkk1mk3jy1m3jy3jy1m3jyk1p83Jy1m3dyr1m3hyr1m3hy3cy1m3d");
    string_constant_17 = 
	    STATIC_STRING("y3cy1p83Jy1mm3ey1m3by3ey1m3by3hy1mm3hy1n83jy1mpm1m3hyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r8");
    string_constant_18 = 
	    STATIC_STRING("3Bly83Bly836ry836ry00001q1l8o1l8l1l8z1l83Cy1m8p838Qy1m83Dy73=Hy3-=y3-ny3-ky3-ky3-Xy3-gy3-my3-ey3-ry3ey3Sy3-my3-ay3-Xy3Sy3-hy3-gy");
    string_constant_19 = 
	    STATIC_STRING("3-ey3-ry3Sy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3Sy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy3-W");
    string_constant_20 = 
	    STATIC_STRING("y3Sy3-by3-ly3Sy3-Yy3-ky3-Ty3-fy3-Xy3fy3-Uy3-hy3-ky3-Wy3-Xy3-ky3fy3-ly3-by3-sy3-Xy3gy3Sy3-wyut3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy");
    string_constant_21 = 
	    STATIC_STRING("3vy3Sy3-my3-ky3-ny3-Xy3ey3Sy3-my3-ry3-iy3-Xy3Sy3vy3Sy3-iy3-hy3-ly3-by3-my3-by3-oy3-Xy3fy3-by3-gy3-my3-Xy3-Zy3-Xy3-ky3gy3Sy3-Gy3-");
    string_constant_22 = 
	    STATIC_STRING("ay3-by3-ly3Sy3-by3-ly3Sy3-gy3-hy3-my3Sy3-ly3-ay3-hy3-py3-gy3Sy3-by3-gy3Sy3-Ty3-ny3-my3-hy3-Wy3-hy3-Vy3Sy3-wyu3-ly3-hy3Sy3-by3-ly");
    string_constant_23 = 
	    STATIC_STRING("3Sy3-gy3-hy3-my3Sy3-by3-fy3-iy3-ey3-Xy3-fy3-Xy3-gy3-my3-Xy3-Wy3Sy3-my3-ay3-ky3-hy3-ny3-Zy3-ay3Sy3-Ty3-gy3Sy3-Ty3-my3-my3-ky3-by3");
    string_constant_24 = 
	    STATIC_STRING("-Uy3-ny3-my3-Xy3fy3-fy3-by3-fy3-by3-Vy3gy3Sy3-5y3-gy3-oy3-Xy3-ly3-my3-by3-Zy3-Ty3-my3-Xy3xy3xy3xy000004z8r83M9y83M9y836ry836ry00");
    string_constant_25 = STATIC_STRING("001m1l8o1l8l00000");
    string_constant_26 = 
	    STATIC_STRING("1r8q1n836ry1m83Ry83-+y1m8v836ry1n83--y01m8p83-*y1n83-0y01m8p83-0y1m8u1p8w9k3ky3ky1o1p83Jy1mkk1mk3jy1m3jy3jy1m3jyk1p83Jy1m3dyr1m3");
    string_constant_27 = 
	    STATIC_STRING("hyr1m3hy3cy1m3dy3cy1p83Jy1mm3ey1m3by3ey1m3by3hy1mm3hy1n83jy1mpm1m3hyp1s83Bly08o8l8z83Cy1m8p838Qy1m83Dy73=Hy3-=y3-ny3-ky3-ky3-Xy3");
    string_constant_28 = 
	    STATIC_STRING("-gy3-my3-ey3-ry3ey3Sy3-my3-ay3-Xy3Sy3-hy3-gy3-ey3-ry3Sy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3Sy3-Ty3-my3-my3-ky3-by3-Uy3-");
    string_constant_29 = 
	    STATIC_STRING("ny3-my3-Xy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3Sy3-by3-ly3Sy3-Yy3-ky3-Ty3-fy3-Xy3fy3-Uy3-hy3-ky3-Wy3-Xy3-ky3fy3-ly3-by3-sy3-Xy3gy");
    string_constant_30 = 
	    STATIC_STRING("3Sy3-wyut3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3-ny3-Xy3ey3Sy3-my3-ry3-iy3-Xy3Sy3vy3Sy3-iy3-hy3-ly3-by3-my3-by3-oy3-X");
    string_constant_31 = 
	    STATIC_STRING("y3fy3-by3-gy3-my3-Xy3-Zy3-Xy3-ky3gy3Sy3-Gy3-ay3-by3-ly3Sy3-by3-ly3Sy3-gy3-hy3-my3Sy3-ly3-ay3-hy3-py3-gy3Sy3-by3-gy3Sy3-Ty3-ny3-m");
    string_constant_32 = 
	    STATIC_STRING("y3-hy3-Wy3-hy3-Vy3Sy3-wyu3-ly3-hy3Sy3-by3-ly3Sy3-gy3-hy3-my3Sy3-by3-fy3-iy3-ey3-Xy3-fy3-Xy3-gy3-my3-Xy3-Wy3Sy3-my3-ay3-ky3-hy3-n");
    string_constant_33 = 
	    STATIC_STRING("y3-Zy3-ay3Sy3-Ty3-gy3Sy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3fy3-fy3-by3-fy3-by3-Vy3gy3Sy3-5y3-gy3-oy3-Xy3-ly3-my3-by3-Zy3-Ty3-my");
    string_constant_34 = STATIC_STRING("3-Xy3xy3xy3xy1o83M9y08o8l");
    temp = regenerate_optimized_constant(string_constant_12);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_13,
	    string_constant_14,string_constant_15,string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qframe_style_definition,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(list(9,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33,string_constant_34)),Nil);
    Qframe_description_reference_of_frame_style_definition_qm = 
	    STATIC_SYMBOL("FRAME-DESCRIPTION-REFERENCE-OF-FRAME-STYLE-DEFINITION\?",
	    AB_package);
    Qreclaim_frame_description_reference_of_frame_style_definition_qm_value 
	    = 
	    STATIC_SYMBOL("RECLAIM-FRAME-DESCRIPTION-REFERENCE-OF-FRAME-STYLE-DEFINITION\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_description_reference_of_frame_style_definition_qm_value,
	    STATIC_FUNCTION(reclaim_frame_description_reference_of_frame_style_definition_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qframe_description_reference_of_frame_style_definition_qm,
	    SYMBOL_FUNCTION(Qreclaim_frame_description_reference_of_frame_style_definition_qm_value),
	    Qslot_value_reclaimer);
    Qinitialize_for_frame_style_definition = 
	    STATIC_SYMBOL("INITIALIZE-FOR-FRAME-STYLE-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_frame_style_definition,
	    STATIC_FUNCTION(initialize_for_frame_style_definition,NIL,
	    FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_frame_style_definition);
    set_get(Qframe_style_definition,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qframe_style_definition,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qdescription_of_frame = STATIC_SYMBOL("DESCRIPTION-OF-FRAME",AB_package);
    Qcleanup_for_frame_style_definition = 
	    STATIC_SYMBOL("CLEANUP-FOR-FRAME-STYLE-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_frame_style_definition,
	    STATIC_FUNCTION(cleanup_for_frame_style_definition,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_frame_style_definition);
    set_get(Qframe_style_definition,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qframe_style_definition,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qalways_display_entire_item_inside_frame = 
	    STATIC_SYMBOL("ALWAYS-DISPLAY-ENTIRE-ITEM-INSIDE-FRAME",
	    AB_package);
    Qput_always_display_entire_item_inside_frame_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-ALWAYS-DISPLAY-ENTIRE-ITEM-INSIDE-FRAME-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_always_display_entire_item_inside_frame_where_slot_is_absent,
	    STATIC_FUNCTION(put_always_display_entire_item_inside_frame_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qalways_display_entire_item_inside_frame,
	    SYMBOL_FUNCTION(Qput_always_display_entire_item_inside_frame_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qframe_style_definition_is_empty = 
	    STATIC_SYMBOL("FRAME-STYLE-DEFINITION-IS-EMPTY",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant = STATIC_STRING("the description of frame is missing.");
    write_frame_style_definition_is_empty_note_1 = 
	    STATIC_FUNCTION(write_frame_style_definition_is_empty_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qframe_style_definition_is_empty,
	    write_frame_style_definition_is_empty_note_1,Qframe_note_writer_1);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qupdate_frame_status_and_notes_for_frame_style_definition = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES-FOR-FRAME-STYLE-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_frame_style_definition,
	    STATIC_FUNCTION(update_frame_status_and_notes_for_frame_style_definition,
	    NIL,FALSE,1,1));
    Qupdate_frame_status_and_notes = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_frame_style_definition);
    set_get(Qframe_style_definition,Qupdate_frame_status_and_notes,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_frame_status_and_notes),
	    Qclasses_which_define);
    temp_2 = CONS(Qframe_style_definition,temp);
    mutate_global_property(Qupdate_frame_status_and_notes,temp_2,
	    Qclasses_which_define);
    Qput_description_of_frame = STATIC_SYMBOL("PUT-DESCRIPTION-OF-FRAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_description_of_frame,
	    STATIC_FUNCTION(put_description_of_frame,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qdescription_of_frame,
	    SYMBOL_FUNCTION(Qput_description_of_frame),Qslot_putter);
}
