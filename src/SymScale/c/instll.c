/* instll.c
 * Input file:  install.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "instll.h"


/* GET-NEW-TRANSLATION-OF-TEXT-SLOT */
Object get_new_translation_of_text_slot(translation_and_text)
    Object translation_and_text;
{
    Object new_translation;

    x_note_fn_call(179,0);
    if (CONSP(translation_and_text)) {
	new_translation = CAR(translation_and_text);
	if (new_translation &&  !EQ(new_translation,No_value))
	    return VALUES_1(CAR(new_translation));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qold_rule;           /* old-rule */

static Object Qframe_flags;        /* frame-flags */

static Object Qwhenever;           /* whenever */

static Object Qrule_scan_interval;  /* rule-scan-interval */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qbad;                /* bad */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qincomplete;         /* incomplete */

static Object Qrule_byte_code_body;  /* rule-byte-code-body */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-RULE */
Object put_box_translation_and_text_slot_value_for_rule(rule,
	    box_translation_and_text,initializing_qm)
    Object rule, box_translation_and_text, initializing_qm;
{
    Object car_new_value, new_translation_qm, temp, was_runnable_qm;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long svref_new_value;

    x_note_fn_call(179,1);
    if (initializing_qm &&  !TRUEP(compilations_up_to_date_p(rule)) && 
	    Loading_kb_p) {
	delete_frame_note_if_any(Qold_rule,rule);
	reclaim_slot_value(CAR(box_translation_and_text));
	car_new_value = No_value;
	M_CAR(box_translation_and_text) = car_new_value;
	note_frame_with_compilation_removed(rule);
    }
    if (Loading_kb_p && initializing_qm &&  !(IFIX(Kb_flags) >= (SI_Long)7L)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) | (SI_Long)8L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) | (SI_Long)2L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
    }
    new_translation_qm = 
	    get_new_translation_of_text_slot(box_translation_and_text);
    temp = ISVREF(rule,(SI_Long)8L);
    if ( !TRUEP(CAR(temp))) {
	was_runnable_qm = (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)5L)) & 
		(SI_Long)1L) ? T : Nil;
	if (was_runnable_qm);
	else
	    was_runnable_qm =  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L 
		    != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		    (SI_Long)16777216L) ? ( !((SI_Long)0L != 
		    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)8192L)) ? T 
		    : Nil) : Qnil;
    }
    else
	was_runnable_qm = Nil;
    if (was_runnable_qm) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(rule,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_1 = rule;
	gensymed_symbol_2 = Nil;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    if ( !TRUEP(initializing_qm) && ((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)2048L) || EQ(ISVREF(rule,
	    (SI_Long)32L),Qwhenever)) && ISVREF(rule,(SI_Long)20L))
	set_slot_value_and_update_representations(3,rule,
		Qrule_scan_interval,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qbox_translation_and_text);
    SVREF(rule,FIX((SI_Long)16L)) = box_translation_and_text;
    temp = ISVREF(rule,(SI_Long)8L);
    if (EQ(CAR(temp),Qbad));
    else if (new_translation_qm) {
	update_frame_status(rule,Nil,T);
	if (was_runnable_qm) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(rule,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	    gensymed_symbol_1 = rule;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
	if ( !TRUEP(initializing_qm))
	    update_representations_of_slot_value(2,rule,
		    Qframe_status_and_notes);
    }
    else {
	update_frame_status(rule,Qincomplete,initializing_qm);
	change_slot_value(3,rule,Qrule_byte_code_body,Nil);
    }
    return VALUES_2(box_translation_and_text,Nil);
}

Object Rules_of_this_category_kbprop = UNBOUND;

Object Rules_of_this_class_or_object_name_kbprop = UNBOUND;

static Object Qfocal_class;        /* focal-class */

static Object Qfocal_classes;      /* focal-classes */

/* PUT-FOCAL-CLASSES */
Object put_focal_classes(rule,value,initializing_qm)
    Object rule, value, initializing_qm;
{
    Object old_value, name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2, temp_1, new_cons;
    Object svref_new_value;

    x_note_fn_call(179,2);
    old_value = initializing_qm ? Nil : ISVREF(rule,(SI_Long)22L);
    name = Nil;
    ab_loop_list_ = old_value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qfocal_class);
    gensymed_symbol = rule;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_class_or_object_name_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    name = Nil;
    ab_loop_list_ = value;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_directory_of_names(name,Qfocal_class);
    gensymed_symbol = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
    gensymed_symbol_1 = rule;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	temp_1 = name;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		Rules_of_this_class_or_object_name_kbprop);
    }
    goto next_loop_2;
  end_loop_2:;
    if ( !TRUEP(initializing_qm)) {
	name = Nil;
	ab_loop_list_ = ISVREF(rule,(SI_Long)23L);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = lookup_kb_specific_property_value(name,
		Rules_of_this_class_or_object_name_kbprop);
	gensymed_symbol_1 = rule;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = name;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	    mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		    Rules_of_this_class_or_object_name_kbprop);
	}
	goto next_loop_3;
      end_loop_3:;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qfocal_classes);
    SVREF(rule,FIX((SI_Long)22L)) = value;
    if ( !(initializing_qm || embedded_rule_p(rule)))
	recompile_item(rule);
    return VALUES_1(value);
}

/* RECLAIM-FOCAL-CLASSES-VALUE */
Object reclaim_focal_classes_value(value,frame)
    Object value, frame;
{
    Object name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2;

    x_note_fn_call(179,3);
    name = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qfocal_class);
    gensymed_symbol = frame;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_class_or_object_name_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qfocal_classes);
    SVREF(frame,FIX((SI_Long)22L)) = Nil;
    return VALUES_1(Nil);
}

static Object Qfocal_object_name;  /* focal-object-name */

static Object Qfocal_objects;      /* focal-objects */

/* PUT-FOCAL-OBJECTS */
Object put_focal_objects(rule,value,making_frame_qm)
    Object rule, value, making_frame_qm;
{
    Object old_value, name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2, temp_1, new_cons;
    Object svref_new_value;

    x_note_fn_call(179,4);
    old_value = making_frame_qm ? Nil : ISVREF(rule,(SI_Long)23L);
    name = Nil;
    ab_loop_list_ = old_value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qfocal_object_name);
    gensymed_symbol = rule;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_class_or_object_name_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    name = Nil;
    ab_loop_list_ = value;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_directory_of_names(name,Qfocal_object_name);
    gensymed_symbol = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
    gensymed_symbol_1 = rule;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	temp_1 = name;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		Rules_of_this_class_or_object_name_kbprop);
    }
    goto next_loop_2;
  end_loop_2:;
    if ( !TRUEP(making_frame_qm)) {
	name = Nil;
	ab_loop_list_ = ISVREF(rule,(SI_Long)22L);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = lookup_kb_specific_property_value(name,
		Rules_of_this_class_or_object_name_kbprop);
	gensymed_symbol_1 = rule;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = name;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	    mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		    Rules_of_this_class_or_object_name_kbprop);
	}
	goto next_loop_3;
      end_loop_3:;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qfocal_objects);
    SVREF(rule,FIX((SI_Long)23L)) = value;
    return VALUES_1(value);
}

/* RECLAIM-FOCAL-OBJECTS-VALUE */
Object reclaim_focal_objects_value(value,frame)
    Object value, frame;
{
    Object name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2;

    x_note_fn_call(179,5);
    name = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qfocal_object_name);
    gensymed_symbol = frame;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_class_or_object_name_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_class_or_object_name_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qfocal_objects);
    SVREF(frame,FIX((SI_Long)23L)) = Nil;
    return VALUES_1(Nil);
}

static Object Qrule_category_name;  /* rule-category-name */

static Object Qrule_categories;    /* rule-categories */

/* PUT-RULE-CATEGORIES */
Object put_rule_categories(rule,value,making_frame_qm)
    Object rule, value, making_frame_qm;
{
    Object old_value, name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2, temp_1, new_cons;
    Object svref_new_value;

    x_note_fn_call(179,6);
    old_value = making_frame_qm ? Nil : ISVREF(rule,(SI_Long)24L);
    name = Nil;
    ab_loop_list_ = old_value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qrule_category_name);
    gensymed_symbol = rule;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_category_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_category_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    name = Nil;
    ab_loop_list_ = value;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_directory_of_names(name,Qrule_category_name);
    gensymed_symbol = lookup_kb_specific_property_value(name,
	    Rules_of_this_category_kbprop);
    gensymed_symbol_1 = rule;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	temp_1 = name;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		Rules_of_this_category_kbprop);
    }
    goto next_loop_2;
  end_loop_2:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_categories);
    SVREF(rule,FIX((SI_Long)24L)) = value;
    return VALUES_1(value);
}

/* RECLAIM-RULE-CATEGORIES-VALUE */
Object reclaim_rule_categories_value(value,frame)
    Object value, frame;
{
    Object name, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2;

    x_note_fn_call(179,7);
    name = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(name,Qrule_category_name);
    gensymed_symbol = frame;
    gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = lookup_kb_specific_property_value(name,
	    Rules_of_this_category_kbprop);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop_1;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp;
	}
	else
	    mutate_kb_specific_property_value(name,CDR(gensymed_symbol_2),
		    Rules_of_this_category_kbprop);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	goto end_1;
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qrule_categories);
    SVREF(frame,FIX((SI_Long)24L)) = Nil;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_parameters, Qsimulation_parameters);

/* PUT-HANDLE-ORDERING-LOOPS?-WHERE-SLOT-IS-ABSENT */
Object put_handle_ordering_loops_qm_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(179,8);
    return VALUES_1(Nil);
}

static Object Qsimulator_on_qm;    /* simulator-on? */

/* INITIALIZE-FOR-SIMULATION-PARAMETERS */
Object initialize_for_simulation_parameters(simulation_parameters)
    Object simulation_parameters;
{
    Object frame, sub_vector_qm, method_function_qm, code, svref_arg_1;
    SI_Long index_1, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,9);
    PUSH_SPECIAL_WITH_SYMBOL(Simulation_parameters,Qsimulation_parameters,simulation_parameters,
	    0);
      frame = Simulation_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qsimulation_parameters)) {
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
      if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
	  code = M_CAR(M_CDR(Edit_type_alias_mapping));
	  temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
		  (SI_Long)0L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Simulation_parameters,Qsimulator_on_qm);
	  svref_arg_1 = Simulation_parameters;
	  result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)24L)) = Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* EXPRESSION-CELL-ELEMENT-FOR-GENERIC-FORMULA */
Object expression_cell_element_for_generic_formula(generic_formula)
    Object generic_formula;
{
    x_note_fn_call(179,10);
    return VALUES_1(FIX((SI_Long)0L));
}

static Object Qstack_change;       /* stack-change */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-GENERIC-FORMULA */
Object put_box_translation_and_text_slot_value_for_generic_formula(generic_formula,
	    box_translation_and_text,initializing_qm)
    Object generic_formula, box_translation_and_text, initializing_qm;
{
    Object recompiling_qm, temp, old_box_translation_and_text;
    Object old_translation_qm, new_translation, new_role_name, old_role_name;
    Object old_class_qualifier, new_class_qualifier, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, svref_arg_2, temp_1, result_1;
    Object current_flag_state_qm, slot_description, new_cons, svref_new_value;
    Object stack_of_slot_value_changes, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(179,11);
    recompiling_qm = initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(generic_formula)) ? 
	    Loading_kb_p : Qnil;
    if (recompiling_qm) {
	reclaim_slot_value(CAR(box_translation_and_text));
	temp = No_value;
	M_CAR(box_translation_and_text) = temp;
	note_frame_with_compilation_removed(generic_formula);
    }
    old_box_translation_and_text = ISVREF(generic_formula,(SI_Long)16L);
    old_translation_qm =  !(initializing_qm ||  
	    !TRUEP(old_box_translation_and_text) || 
	    EQ(CAR(old_box_translation_and_text),No_value)) ? 
	    CAR(old_box_translation_and_text) : Nil;
    new_translation = CONSP(box_translation_and_text) &&  
	    !EQ(CAR(box_translation_and_text),No_value) ? 
	    CAR(box_translation_and_text) : Nil;
    new_role_name = new_translation ? FIRST(new_translation) : Nil;
    old_role_name = old_translation_qm ? FIRST(old_translation_qm) : Nil;
    old_class_qualifier = old_translation_qm ? THIRD(old_translation_qm) : Nil;
    new_class_qualifier = new_translation ? THIRD(new_translation) : Nil;
    if (old_role_name) {
	gensymed_symbol = generic_formula;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = 
		lookup_kb_specific_property_value(old_role_name,
		Formulas_for_this_role_kbprop);
      next_loop:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else
		mutate_kb_specific_property_value(old_role_name,
			CDR(gensymed_symbol_2),Formulas_for_this_role_kbprop);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    goto end_1;
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop;
      end_loop:
      end_1:;
	reconcile_formulas_for_role_and_class(old_role_name,
		SECOND(old_translation_qm),old_class_qualifier);
    }
    if (new_translation)
	temp_1 = Nil;
    else if (old_translation_qm &&  !TRUEP(recompiling_qm))
	temp_1 = Qbad;
    else
	temp_1 = Qincomplete;
    update_frame_status(generic_formula,temp_1,initializing_qm);
    if (initializing_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(generic_formula,Qbox_translation_and_text);
	SVREF(generic_formula,FIX((SI_Long)16L)) = box_translation_and_text;
    }
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(generic_formula,(SI_Long)1L),Nil);
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
	    gensymed_symbol_1 = nconc2(stack_change_list_2(generic_formula,
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
	    M_CAR(gensymed_symbol_1) = generic_formula;
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
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(generic_formula,
		      Qbox_translation_and_text);
	  result_1 = SVREF(generic_formula,FIX((SI_Long)16L)) = 
		  box_translation_and_text;
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
		  temp_1 = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp_1) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(generic_formula,
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
	      temp_1 = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp_1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
    }
    if (new_role_name) {
	gensymed_symbol = lookup_kb_specific_property_value(new_role_name,
		Formulas_for_this_role_kbprop);
	gensymed_symbol_1 = generic_formula;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	    mutate_kb_specific_property_value(new_role_name,
		    gensymed_symbol_2,Formulas_for_this_role_kbprop);
	}
	reconcile_formulas_for_role_and_class(new_role_name,
		SECOND(new_translation),new_class_qualifier);
    }
    if ( !TRUEP(is_generic_forumula_executable_qm(generic_formula)) &&  
	    !TRUEP(recompiling_qm))
	update_frame_status(generic_formula,Qbad,Nil);
    return VALUES_2(box_translation_and_text,Nil);
}

static Object string_constant;     /* "this is not the only generic formula for the ~(~A~) of a ~(~A~)" */

/* WRITE-MULTIPLE-GENERIC-FORMULAS-NOTE */
Object write_multiple_generic_formulas_note(role,generic_formula)
    Object role, generic_formula;
{
    Object temp, class_1;

    x_note_fn_call(179,12);
    temp = ISVREF(generic_formula,(SI_Long)16L);
    temp = CAR(temp);
    class_1 = SECOND(temp);
    GENSYM_RETURN_ONE(tformat(3,string_constant,role,class_1));
    return VALUES_1(Nil);
}

static Object Qmultiple_generic_formulas;  /* multiple-generic-formulas */

/* RECONCILE-FORMULAS-FOR-ROLE-AND-CLASS */
Object reconcile_formulas_for_role_and_class(role,class_1,class_qualifier)
    Object role, class_1, class_qualifier;
{
    Object formulas, first_found_qm, multiple_qm, formula, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(179,13);
    formulas = lookup_kb_specific_property_value(role,
	    Formulas_for_this_role_kbprop);
    first_found_qm = Nil;
    multiple_qm = Nil;
    formula = Nil;
    ab_loop_list_ = formulas;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    formula = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(first_found_qm)) {
	temp = ISVREF(formula,(SI_Long)16L);
	temp = CAR(temp);
	if (EQ(SECOND(temp),class_1) ? TRUEP(frame_not_bad_p(formula)) : 
		TRUEP(Nil))
	    first_found_qm = T;
    }
    else {
	temp = ISVREF(formula,(SI_Long)16L);
	temp = CAR(temp);
	if (EQ(SECOND(temp),class_1) ? TRUEP(frame_not_bad_p(formula)) : 
		TRUEP(Nil)) {
	    temp_1 =  !TRUEP(class_qualifier);
	    if (temp_1);
	    else {
		temp = ISVREF(formula,(SI_Long)16L);
		if (IFIX(length(CAR(temp))) > (SI_Long)2L) {
		    temp = ISVREF(formula,(SI_Long)16L);
		    temp = CAR(temp);
		    temp = THIRD(temp);
		}
		else
		    temp = Nil;
		temp_1 = EQ(temp,class_qualifier);
	    }
	    if (temp_1);
	    else
		temp_1 = EQ(class_1,class_qualifier);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    multiple_qm = T;
    }
    goto next_loop;
  end_loop:
    formula = Nil;
    ab_loop_list_ = formulas;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    formula = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(formula,(SI_Long)16L);
    temp = CAR(temp);
    if (EQ(SECOND(temp),class_1)) {
	if (multiple_qm)
	    add_frame_note(5,Qmultiple_generic_formulas,formula,role,T,Nil);
	else
	    delete_frame_note_if_any(Qmultiple_generic_formulas,formula);
    }
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(Qnil);
}

/* PUT-ATTRIBUTE-VALUE */
Object put_attribute_value varargs_1(int, n)
{
    Object frame, unique_or_pretty_slot_name, new_attribute_value;
    Object initializing_qm;
    Object class_if_specific_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(179,14);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    new_attribute_value = REQUIRED_ARG_nonrelocating();
    initializing_qm = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = put_attribute_description_value(frame,
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm),
	    new_attribute_value,initializing_qm);
    return VALUES_2(temp,T);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qparent_attribute_name;  /* parent-attribute-name */

static Object Qparent_frame;       /* parent-frame */

static Object Qab_slot_value;      /* slot-value */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qnote_slot_changes;  /* note-slot-changes */

/* PUT-ATTRIBUTE-DESCRIPTION-VALUE */
Object put_attribute_description_value(frame,slot_description,
	    new_attribute_value,retaining_old_frame_or_initializing_qm)
    Object frame, slot_description, new_attribute_value;
    Object retaining_old_frame_or_initializing_qm;
{
    Object old_attribute_value, x2, new_value_is_frame_p;
    Object current_computation_frame, sub_class_bit_vector, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_1, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, temp_2, slot_features;
    Object parent_pretty_slot_name, class_description;
    Object parent_slot_defining_class_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,15);
    old_attribute_value = get_slot_description_value(frame,slot_description);
    if (SIMPLE_VECTOR_P(new_attribute_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_attribute_value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(new_attribute_value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(new_attribute_value,(SI_Long)1L);
	new_value_is_frame_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	new_value_is_frame_p = Nil;
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    current_computation_frame = temp ? Current_computation_frame : frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if ( !(Do_not_note_permanent_changes_p || 
	      slot_value_equal_p(old_attribute_value,new_attribute_value)))
	  note_permanent_change(frame,slot_description);
      if ( !TRUEP(retaining_old_frame_or_initializing_qm)) {
	  if (SIMPLE_VECTOR_P(old_attribute_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_attribute_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(old_attribute_value,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(old_attribute_value,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(old_attribute_value,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_or_parameter_class_description,
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
		  remove_variable_from_simulation(old_attribute_value);
	      if ((SI_Long)0L != (IFIX(ISVREF(old_attribute_value,
		      (SI_Long)5L)) & (SI_Long)1L)) {
		  gensymed_symbol_3 = 
			  ISVREF(ISVREF(ISVREF(ISVREF(old_attribute_value,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
			  (SI_Long)1L);
		  gensymed_symbol_4 = old_attribute_value;
		  gensymed_symbol_5 = Nil;
		  inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
			  gensymed_symbol_5);
	      }
	      gensymed_symbol_3 = 
		      get_lookup_slot_value_given_default(old_attribute_value,
		      Qparent_attribute_name,Nil);
	      set_non_savable_lookup_slot_value(old_attribute_value,
		      Qparent_frame,Nil);
	      gensymed_symbol_3 = 
		      get_lookup_slot_value_given_default(old_attribute_value,
		      Qparent_attribute_name,Nil);
	      temp_1 = old_attribute_value;
	      if (Nil) {
		  new_cons = ISVREF(Available_slot_value_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      svref_arg_1 = Available_slot_value_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_slot_value_conses_vector,
			      IFIX(Current_thread_index)))) {
			  svref_arg_1 = 
				  Available_slot_value_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(svref_arg_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol_4 = new_cons;
		  }
		  else
		      gensymed_symbol_4 = Nil;
		  if ( !TRUEP(gensymed_symbol_4))
		      gensymed_symbol_4 = replenish_slot_value_cons_pool();
		  M_CAR(gensymed_symbol_4) = Nil;
		  M_CDR(gensymed_symbol_4) = Nil;
		  inline_note_allocate_cons(gensymed_symbol_4,Qab_slot_value);
		  temp_2 = gensymed_symbol_4;
	      }
	      else
		  temp_2 = Nil;
	      set_non_savable_lookup_slot_value(temp_1,
		      Qparent_attribute_name,temp_2);
	      reclaim_slot_value(gensymed_symbol_3);
	      delete_frame(old_attribute_value);
	      old_attribute_value = Nil;
	  }
      }
      if (Noting_changes_to_kb_p) {
	  slot_features = ISVREF(slot_description,(SI_Long)9L);
	  temp = assq_function(Qtype,slot_features) ?  
		  !TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		  TRUEP(assq_function(Qsave,slot_features));
	  if (temp);
	  else
	      temp = TRUEP(assq_function(Qnote_slot_changes,
		      ISVREF(slot_description,(SI_Long)9L)));
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	      note_change_to_block_1(frame,ISVREF(slot_description,
		      (SI_Long)2L));
	  else
	      note_change_to_dependent_frame_1();
      }
      set_slot_description_value_without_noting(frame,slot_description,
	      new_attribute_value);
      if (new_value_is_frame_p) {
	  add_as_inferior_block(new_attribute_value,frame);
	  parent_pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	  class_description = ISVREF(frame,(SI_Long)1L);
	  if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	      temp_1 = ISVREF(slot_description,(SI_Long)3L);
	      temp =  !EQ(temp_1,
		      ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		      (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	  }
	  else
	      temp = TRUEP(Nil);
	  parent_slot_defining_class_qm = temp ? ISVREF(slot_description,
		  (SI_Long)3L) : Nil;
	  gensymed_symbol_3 = 
		  get_lookup_slot_value_given_default(new_attribute_value,
		  Qparent_attribute_name,Nil);
	  set_non_savable_lookup_slot_value(new_attribute_value,
		  Qparent_frame,frame);
	  gensymed_symbol_3 = 
		  get_lookup_slot_value_given_default(new_attribute_value,
		  Qparent_attribute_name,Nil);
	  if (parent_slot_defining_class_qm) {
	      new_cons = ISVREF(Available_slot_value_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  svref_arg_1 = Available_slot_value_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			  IFIX(Current_thread_index)))) {
		      svref_arg_1 = Available_slot_value_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(svref_arg_1,svref_arg_2) = Nil;
		  }
		  gensymed_symbol_4 = new_cons;
	      }
	      else
		  gensymed_symbol_4 = Nil;
	      if ( !TRUEP(gensymed_symbol_4))
		  gensymed_symbol_4 = replenish_slot_value_cons_pool();
	      M_CAR(gensymed_symbol_4) = parent_pretty_slot_name;
	      M_CDR(gensymed_symbol_4) = parent_slot_defining_class_qm;
	      inline_note_allocate_cons(gensymed_symbol_4,Qab_slot_value);
	      temp_1 = gensymed_symbol_4;
	  }
	  else
	      temp_1 = parent_pretty_slot_name;
	  set_non_savable_lookup_slot_value(new_attribute_value,
		  Qparent_attribute_name,temp_1);
	  reclaim_slot_value(gensymed_symbol_3);
	  if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)1L)) {
	      gensymed_symbol_3 = 
		      ISVREF(ISVREF(ISVREF(ISVREF(new_attribute_value,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	      gensymed_symbol_4 = new_attribute_value;
	      inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
	  }
	  else {
	      temp = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
		      (SI_Long)8192L);
	      if (temp);
	      else
		  temp = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
			  (SI_Long)256L);
	      if (temp);
	      else {
		  temp_1 = ISVREF(frame,(SI_Long)8L);
		  temp = TRUEP(CAR(temp_1));
	      }
	      if (temp) {
		  gensymed_symbol_3 = 
			  ISVREF(ISVREF(ISVREF(ISVREF(new_attribute_value,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
			  (SI_Long)1L);
		  gensymed_symbol_4 = new_attribute_value;
		  gensymed_symbol_5 = T;
		  inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
			  gensymed_symbol_5);
	      }
	  }
      }
      if ( !(Loading_kb_p ||  !TRUEP(Generic_simulation_formulas_used_p) 
	      || Class_is_undergoing_inheritance_change_qm)) {
	  if (new_value_is_frame_p) {
	      sub_class_bit_vector = ISVREF(ISVREF(new_attribute_value,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_or_parameter_class_description,
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      update_generic_simulation_formula_for_variable_or_parameter(new_attribute_value);
	  else {
	      if (new_value_is_frame_p) {
		  sub_class_bit_vector = ISVREF(ISVREF(new_attribute_value,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
	      if (temp)
		  update_runtime_structures_according_to_edit(1,
			  new_attribute_value);
	  }
	  update_runtime_structures_according_to_edit(1,frame);
      }
      if ( !TRUEP(retaining_old_frame_or_initializing_qm)) {
	  if (new_value_is_frame_p) {
	      sub_class_bit_vector = ISVREF(ISVREF(new_attribute_value,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_or_parameter_class_description,
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      install_externally_simulated_variable(new_attribute_value);
      }
      invoke_rules_for_attribute_change_chaining(frame,
	      ISVREF(slot_description,(SI_Long)2L),old_attribute_value,
	      ISVREF(slot_description,(SI_Long)3L));
      if ( !TRUEP(retaining_old_frame_or_initializing_qm) && 
	      old_attribute_value) {
	  if ( !EQ(old_attribute_value,ISVREF(slot_description,(SI_Long)6L)))
	      reclaim_slot_value(old_attribute_value);
      }
      temp_1 = new_attribute_value;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* UPDATE-SIMULATOR-INFORMATION-FOR-ATTRIBUTE-NAME-CHANGE */
Object update_simulator_information_for_attribute_name_change(parent_entity,
	    variable_in_slot,old_attribute_name,new_attribute_name)
    Object parent_entity, variable_in_slot, old_attribute_name;
    Object new_attribute_name;
{
    x_note_fn_call(179,16);
    if ( !(Loading_kb_p ||  !TRUEP(Generic_simulation_formulas_used_p)))
	return update_generic_simulation_formula_for_variable_or_parameter(variable_in_slot);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_edit_cache = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_edit_caches, Qchain_of_available_edit_caches);

DEFINE_VARIABLE_WITH_SYMBOL(Edit_cache_count, Qedit_cache_count);

Object Chain_of_available_edit_caches_vector = UNBOUND;

/* EDIT-CACHE-STRUCTURE-MEMORY-USAGE */
Object edit_cache_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(179,17);
    temp = Edit_cache_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EDIT-CACHE-COUNT */
Object outstanding_edit_cache_count()
{
    Object def_structure_edit_cache_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(179,18);
    gensymed_symbol = IFIX(Edit_cache_count);
    def_structure_edit_cache_variable = Chain_of_available_edit_caches;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_edit_cache_variable))
	goto end_loop;
    def_structure_edit_cache_variable = 
	    ISVREF(def_structure_edit_cache_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EDIT-CACHE-INTERNAL-1 */
Object reclaim_edit_cache_internal_1(edit_cache)
    Object edit_cache;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(179,19);
    inline_note_reclaim_cons(edit_cache,Nil);
    structure_being_reclaimed = edit_cache;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(edit_cache,(SI_Long)1L));
      SVREF(edit_cache,FIX((SI_Long)1L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_edit_caches_vector,
	    IFIX(Current_thread_index));
    SVREF(edit_cache,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_edit_caches_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = edit_cache;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EDIT-CACHE */
Object reclaim_structure_for_edit_cache(edit_cache)
    Object edit_cache;
{
    x_note_fn_call(179,20);
    return reclaim_edit_cache_internal_1(edit_cache);
}

static Object Qg2_defstruct_structure_name_edit_cache_g2_struct;  /* g2-defstruct-structure-name::edit-cache-g2-struct */

/* MAKE-PERMANENT-EDIT-CACHE-STRUCTURE-INTERNAL */
Object make_permanent_edit_cache_structure_internal()
{
    Object def_structure_edit_cache_variable, defstruct_g2_edit_cache_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(179,21);
    def_structure_edit_cache_variable = Nil;
    atomic_incff_symval(Qedit_cache_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_edit_cache_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_edit_cache_variable = the_array;
	SVREF(defstruct_g2_edit_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_cache_g2_struct;
	def_structure_edit_cache_variable = defstruct_g2_edit_cache_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_edit_cache_variable);
}

/* MAKE-EDIT-CACHE-1 */
Object make_edit_cache_1()
{
    Object def_structure_edit_cache_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(179,22);
    def_structure_edit_cache_variable = 
	    ISVREF(Chain_of_available_edit_caches_vector,
	    IFIX(Current_thread_index));
    if (def_structure_edit_cache_variable) {
	svref_arg_1 = Chain_of_available_edit_caches_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_edit_cache_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_edit_cache_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_cache_g2_struct;
    }
    else
	def_structure_edit_cache_variable = 
		make_permanent_edit_cache_structure_internal();
    inline_note_allocate_cons(def_structure_edit_cache_variable,Nil);
    SVREF(def_structure_edit_cache_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_edit_cache_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_edit_cache_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_edit_cache_variable);
}

/* RECLAIM-EDIT-CACHE */
Object reclaim_edit_cache(edit_cache)
    Object edit_cache;
{
    x_note_fn_call(179,23);
    reclaim_eval_list_1(ISVREF(edit_cache,(SI_Long)2L));
    reclaim_eval_list_1(ISVREF(edit_cache,(SI_Long)3L));
    return reclaim_edit_cache_internal_1(edit_cache);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qsimulation_info_qm;  /* simulation-info? */

/* UPDATE-RUNTIME-STRUCTURES-ACCORDING-TO-EDIT */
Object update_runtime_structures_according_to_edit varargs_1(int, n)
{
    Object thing_that_was_edited;
    Object do_not_reinstall_qm, x2, sub_class_bit_vector, temp_1, edit_cache;
    Object connection, frame_serial_number_for_cache, runtime_structure;
    Object ab_loop_list_, gensymed_symbol_3, xa, ya, simulation_info_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(179,24);
    INIT_ARGS_nonrelocating();
    thing_that_was_edited = REQUIRED_ARG_nonrelocating();
    do_not_reinstall_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !(Loading_kb_p ||  !TRUEP(Generic_simulation_formulas_used_p))) {
	if (SIMPLE_VECTOR_P(thing_that_was_edited) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing_that_was_edited)) > 
		(SI_Long)2L &&  !EQ(ISVREF(thing_that_was_edited,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing_that_was_edited,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(thing_that_was_edited,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		temp_1 = ISVREF(thing_that_was_edited,(SI_Long)19L);
		ISVREF(thing_that_was_edited,(SI_Long)19L) = Nil;
		edit_cache = temp_1;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing_that_was_edited,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Statement_class_description,(SI_Long)18L));
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
		if (temp) {
		    temp_1 = ISVREF(thing_that_was_edited,(SI_Long)19L);
		    ISVREF(thing_that_was_edited,(SI_Long)19L) = Nil;
		    edit_cache = temp_1;
		}
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(thing_that_was_edited,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_class_description,
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
		    if (temp) {
			connection = ISVREF(thing_that_was_edited,
				(SI_Long)21L);
			temp_1 = ISVREF(connection,(SI_Long)8L);
			SVREF(connection,FIX((SI_Long)8L)) = Nil;
			edit_cache = temp_1;
		    }
		    else
			edit_cache = Qnil;
		}
	    }
	}
	else if (SIMPLE_VECTOR_P(thing_that_was_edited) && 
		EQ(ISVREF(thing_that_was_edited,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct)) {
	    temp_1 = ISVREF(thing_that_was_edited,(SI_Long)8L);
	    SVREF(thing_that_was_edited,FIX((SI_Long)8L)) = Nil;
	    edit_cache = temp_1;
	}
	else
	    edit_cache = Qnil;
	if (edit_cache) {
	    frame_serial_number_for_cache = ISVREF(edit_cache,(SI_Long)1L);
	    if ( !TRUEP(do_not_reinstall_qm)) {
		if (any_models_running_function_qm()) {
		    runtime_structure = Nil;
		    ab_loop_list_ = ISVREF(edit_cache,(SI_Long)2L);
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    runtime_structure = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (SIMPLE_VECTOR_P(runtime_structure) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(runtime_structure)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(runtime_structure,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(runtime_structure,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(runtime_structure,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Variable_or_parameter_class_description,
				(SI_Long)18L));
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
		    if (temp) {
			gensymed_symbol_3 = ISVREF(runtime_structure,
				(SI_Long)3L);
			temp = SIMPLE_VECTOR_P(runtime_structure) ? 
				EQ(ISVREF(runtime_structure,(SI_Long)1L),
				Qavailable_frame_vector) : TRUEP(Qnil);
			if (temp);
			else
			    temp = FIXNUMP(gensymed_symbol_3) ? 
				    IFIX(gensymed_symbol_3) == 
				    (SI_Long)-1L : TRUEP(Nil);
			if (temp);
			else if (FIXNUMP(frame_serial_number_for_cache))
			    temp = FIXNUMP(gensymed_symbol_3) ? 
				    FIXNUM_LT(frame_serial_number_for_cache,
				    gensymed_symbol_3) : TRUEP(T);
			else if (FIXNUMP(gensymed_symbol_3))
			    temp = TRUEP(Nil);
			else {
			    xa = M_CAR(frame_serial_number_for_cache);
			    ya = M_CAR(gensymed_symbol_3);
			    temp = FIXNUM_LT(xa,ya);
			    if (temp);
			    else
				temp = FIXNUM_EQ(xa,ya) ? 
					FIXNUM_LT(M_CDR(frame_serial_number_for_cache),
					M_CDR(gensymed_symbol_3)) : 
					TRUEP(Qnil);
			}
			temp =  !temp;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			simulation_info_qm = 
				get_lookup_slot_value_given_default(runtime_structure,
				Qsimulation_info_qm,Nil);
			temp = simulation_info_qm ? 
				TRUEP(ISVREF(simulation_info_qm,
				(SI_Long)1L)) : TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			add_to_variables_to_be_rederived(runtime_structure);
		    goto next_loop;
		  end_loop:;
		}
		runtime_structure = Nil;
		ab_loop_list_ = ISVREF(edit_cache,(SI_Long)3L);
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		runtime_structure = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (SIMPLE_VECTOR_P(runtime_structure) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(runtime_structure)) 
			> (SI_Long)2L &&  !EQ(ISVREF(runtime_structure,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(runtime_structure,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(runtime_structure,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol_3 = ISVREF(runtime_structure,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(runtime_structure) ? 
			    EQ(ISVREF(runtime_structure,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol_3) ? 
				IFIX(gensymed_symbol_3) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(frame_serial_number_for_cache))
			temp = FIXNUMP(gensymed_symbol_3) ? 
				FIXNUM_LT(frame_serial_number_for_cache,
				gensymed_symbol_3) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol_3))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(frame_serial_number_for_cache);
			ya = M_CAR(gensymed_symbol_3);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(frame_serial_number_for_cache),
				    M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
		    }
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    update_generic_simulation_formula_for_variable_or_parameter(runtime_structure);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    return reclaim_edit_cache(edit_cache);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* VALIDATE-KB-AFTER-RUNTIME-DEFINITION-CHANGE */
Object validate_kb_after_runtime_definition_change(class_1,old_class_qm,
	    change_may_have_affected_class_hierarchy_of_class_qm)
    Object class_1, old_class_qm;
    Object change_may_have_affected_class_hierarchy_of_class_qm;
{
    x_note_fn_call(179,25);
    validate_executing_statements_and_procedures();
    validate_internal_data_structures_containing_items();
    if ( !TRUEP(Currently_automatically_resolving_class_name_conflicts_qm)) {
	if (change_may_have_affected_class_hierarchy_of_class_qm)
	    return validate_user_data_structures_containing_items(class_1,
		    old_class_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* VALIDATE-EXECUTING-STATEMENTS-AND-PROCEDURES */
Object validate_executing_statements_and_procedures()
{
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(179,26);
    SAVE_STACK();
    LOCK(Procedure_invocations_lock);
    if (PUSH_UNWIND_PROTECT(0))
	validate_all_procedure_invocations_1();
    POP_UNWIND_PROTECT(0);
    UNLOCK(Procedure_invocations_lock);
    CONTINUE_UNWINDING(0);
    validate_all_rule_instances();
    validate_all_generic_formula_invocations();
    validate_all_simulation_formula_invocations();
    RESTORE_STACK();
    return VALUES_1(Nil);
}

static Object Qvariable_or_parameter;  /* variable-or-parameter */

static Object Qgeneric_simulation_formula;  /* generic-simulation-formula */

/* VALIDATE-ALL-SIMULATION-FORMULA-INVOCATIONS */
Object validate_all_simulation_formula_invocations()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, variable_or_parameter;
    Object generic_simulation_formula;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,27);
    if (Generic_simulation_formulas_used_p) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	variable_or_parameter = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qvariable_or_parameter);
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
	  variable_or_parameter = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  update_runtime_structures_according_to_edit(2,
		  variable_or_parameter,Nil);
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	generic_simulation_formula = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qgeneric_simulation_formula);
	next_loop_2:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_3:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_2;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_2;
	      goto next_loop_3;
	    end_loop_2:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_3;
	  generic_simulation_formula = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  update_runtime_structures_according_to_edit(2,
		  generic_simulation_formula,Nil);
	  goto next_loop_2;
	end_loop_3:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* VALIDATE-INTERNAL-DATA-STRUCTURES-CONTAINING-ITEMS */
Object validate_internal_data_structures_containing_items()
{
    x_note_fn_call(179,28);
    validate_role_service();
    return VALUES_1(Nil);
}

/* VALIDATE-USER-DATA-STRUCTURES-CONTAINING-ITEMS */
Object validate_user_data_structures_containing_items(class_1,old_class_qm)
    Object class_1, old_class_qm;
{
    Object class_description_qm, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object thing, ab_loop_it_;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,29);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L))) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	thing = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
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
	  thing = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  ab_loop_it_ = thing;
	  if (ab_loop_it_) {
	      temp = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop_1:
	  temp = TRUEP(Qnil);
	end_1:;
	POP_SPECIAL();
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	validate_all_item_lists(class_1,old_class_qm);
	validate_all_item_arrays(class_1,old_class_qm);
	validate_items_in_all_relations(class_1,old_class_qm);
    }
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qsimulation;         /* simulation */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object string_constant_1;   /* " has problems" */

static Object string_constant_2;   /* " have problems" */

static Object string_constant_3;   /* ", " */

static Object string_constant_4;   /* ", and " */

static Object string_constant_5;   /* " and " */

/* WRITE-PROBLEM-WITH-SUB-FRAME-OF-VARIABLE-NOTE */
Object write_problem_with_sub_frame_of_variable_note(sub_frame_types,
	    gensymed_symbol)
    Object sub_frame_types, gensymed_symbol;
{
    Object ab_loop_destructure_, sub_frame_type, rest_of_types, temp;

    x_note_fn_call(179,30);
    ab_loop_destructure_ = sub_frame_types;
    sub_frame_type = Nil;
    rest_of_types = Nil;
    sub_frame_type = CAR(ab_loop_destructure_);
    rest_of_types = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)4L));
    twrite(sub_frame_type);
    if (EQ(sub_frame_type,Qsimulation))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)9L));
    else
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)6L));
    if ( !TRUEP(rest_of_types)) {
	temp = twrite_general_string( !TRUEP(CDR(sub_frame_types)) ? 
		string_constant_1 : string_constant_2);
	goto end_1;
    }
    if (CDR(rest_of_types))
	temp = string_constant_3;
    else if (CDDR(sub_frame_types))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    sub_frame_type = CAR(rest_of_types);
    rest_of_types = CDR(rest_of_types);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qvalidity_interval_of_sensor_variable_is_supplied;  /* validity-interval-of-sensor-variable-is-supplied */

static Object array_constant_3;    /* # */

static Object Qmissing_validity_interval;  /* missing-validity-interval */

static Object array_constant_4;    /* # */

/* WRITE-PROBLEM-WITH-VALIDITY-INTERVAL-OF-VARIABLE-NOTE */
Object write_problem_with_validity_interval_of_variable_note(problem,
	    gensymed_symbol)
    Object problem, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(179,31);
    if (EQ(problem,Qvalidity_interval_of_sensor_variable_is_supplied))
	temp = twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)66L));
    else if (EQ(problem,Qmissing_validity_interval))
	temp = twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)29L));
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qmissing_initial_value;  /* missing-initial-value */

static Object array_constant_5;    /* # */

static Object Qunused_initial_value;  /* unused-initial-value */

static Object array_constant_6;    /* # */

/* WRITE-PROBLEM-WITH-INITIAL-VALUE-FOR-SIMULATION-NOTE */
Object write_problem_with_initial_value_for_simulation_note(problem,
	    gensymed_symbol)
    Object problem, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(179,32);
    if (EQ(problem,Qmissing_initial_value))
	temp = twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)53L));
    else if (EQ(problem,Qunused_initial_value))
	temp = twrite_beginning_of_wide_string(array_constant_6,
		FIX((SI_Long)31L));
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

/* WRITE-PROBLEM-WITH-SIMULATION-FORMULA-NOTE */
Object write_problem_with_simulation_formula_note(foo,gensymed_symbol)
    Object foo, gensymed_symbol;
{
    x_note_fn_call(179,33);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_7,
	    FIX((SI_Long)41L)));
    return VALUES_1(Nil);
}

static Object array_constant_8;    /* # */

/* WRITE-PROBLEM-WITH-SUB-FRAME-OF-SIMULATION-FRAME-NOTE */
Object write_problem_with_sub_frame_of_simulation_frame_note(sub_frame_types,
	    gensymed_symbol)
    Object sub_frame_types, gensymed_symbol;
{
    Object ab_loop_destructure_, sub_frame_type, rest_of_types, temp;

    x_note_fn_call(179,34);
    ab_loop_destructure_ = sub_frame_types;
    sub_frame_type = Nil;
    rest_of_types = Nil;
    sub_frame_type = CAR(ab_loop_destructure_);
    rest_of_types = CDR(ab_loop_destructure_);
  next_loop:
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)4L));
    twrite(sub_frame_type);
    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)7L));
    if ( !TRUEP(rest_of_types)) {
	temp = twrite_general_string( !TRUEP(CDR(sub_frame_types)) ? 
		string_constant_1 : string_constant_2);
	goto end_1;
    }
    if (CDR(rest_of_types))
	temp = string_constant_3;
    else if (CDDR(sub_frame_types))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    sub_frame_type = CAR(rest_of_types);
    rest_of_types = CDR(rest_of_types);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qmissing_simulation_class;  /* missing-simulation-class */

static Object array_constant_9;    /* # */

/* WRITE-PROBLEM-WITH-SIMULATION-CLASS-NOTE */
Object write_problem_with_simulation_class_note(problem,gensymed_symbol)
    Object problem, gensymed_symbol;
{
    x_note_fn_call(179,35);
    GENSYM_RETURN_ONE(EQ(problem,Qmissing_simulation_class) ? 
	    twrite_beginning_of_wide_string(array_constant_9,
	    FIX((SI_Long)38L)) : Nil);
    return VALUES_1(Nil);
}

static Object Qvalidity_interval;  /* validity-interval */

/* PUT-VALIDITY-INTERVAL */
Object put_validity_interval(variable,validity_interval,initializing_qm)
    Object variable, validity_interval, initializing_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object result_1, current_flag_state_qm, slot_description, new_cons;
    Object svref_new_value_1, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_2, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,36);
    if ( !TRUEP(initializing_qm)) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(variable,(SI_Long)30L);
	if (CAS_SVREF(variable,(SI_Long)30L,gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
	ISVREF(variable,(SI_Long)29L) = Nil;
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) &  ~(SI_Long)32L;
	ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
    }
    if (Changing_validity_interval_invalidates_current_value_p) {
	temp = Some_time_ago;
	ISVREF(variable,(SI_Long)26L) = temp;
    }
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
	svref_new_value_1 = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value_1;
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
	    svref_new_value_1 = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value_1;
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
	  svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(variable,Qvalidity_interval);
      result_1 = SVREF(variable,FIX((SI_Long)27L)) = validity_interval;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = variable;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
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
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(variable,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_1 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(variable,slot_description,Nil,
		  Nil);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(result_1);
}

static Object Qbackground_collection_interval_qm;  /* background-collection-interval? */

static Object Qg2_defstruct_structure_name_data_server_g2_struct;  /* g2-defstruct-structure-name::data-server-g2-struct */

static Object Qcomputation;        /* computation */

/* PUT-BACKGROUND-COLLECTION-INTERVAL? */
Object put_background_collection_interval_qm(variable,interval_qm,
	    gensymed_symbol)
    Object variable, interval_qm, gensymed_symbol;
{
    Object old_interval_qm, source_or_map, server_qm, data_server_qm, temp;

    x_note_fn_call(179,37);
    old_interval_qm = ISVREF(variable,(SI_Long)32L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qbackground_collection_interval_qm);
    SVREF(variable,FIX((SI_Long)32L)) = interval_qm;
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & (SI_Long)1L)) {
	source_or_map = ISVREF(variable,(SI_Long)31L);
	server_qm = ATOM(source_or_map) ? 
		lookup_kb_specific_property_value(source_or_map,
		Data_server_or_alias_qm_kbprop) : Nil;
	data_server_qm = server_qm ? server_qm : 
		warn_of_undefined_data_server(variable,source_or_map);
	if (SIMPLE_VECTOR_P(data_server_qm) && EQ(ISVREF(data_server_qm,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct)) {
	    if (interval_qm) {
		temp = SYMBOL_FUNCTION(ISVREF(data_server_qm,(SI_Long)3L));
		FUNCALL_2(temp,variable,interval_qm);
	    }
	    else if (old_interval_qm) {
		temp = SYMBOL_FUNCTION(ISVREF(data_server_qm,(SI_Long)4L));
		FUNCALL_1(temp,variable);
	    }
	}
	else if (EQ(data_server_qm,Qcomputation)) {
	    if (interval_qm)
		begin_collecting_data_for_inference_engine(variable,
			interval_qm);
	    else
		stop_collecting_data_for_inference_engine(variable);
	}
    }
    return VALUES_1(interval_qm);
}

static Object Qproblem_with_sub_frame_of_variable;  /* problem-with-sub-frame-of-variable */

static Object Qsimulation_details;  /* simulation-details */

static Object Qproblem_with_validity_interval_of_variable;  /* problem-with-validity-interval-of-variable */

/* VARIABLE-FRAME-STATUS-GIVEN-FRAME-NOTE */
Object variable_frame_status_given_frame_note(frame_note_type,particulars,
	    variable)
    Object frame_note_type, particulars, variable;
{
    Object temp, simulation_subtable_status;

    x_note_fn_call(179,38);
    if (EQ(frame_note_type,Qproblem_with_sub_frame_of_variable)) {
	if (memq_function(Qsimulation,particulars)) {
	    temp = ISVREF(get_lookup_slot_value(variable,
		    Qsimulation_details),(SI_Long)8L);
	    simulation_subtable_status = CAR(temp);
	}
	else
	    simulation_subtable_status = Nil;
	if (EQ(simulation_subtable_status,Qbad))
	    return VALUES_1(Qbad);
	else
	    return VALUES_1(simulation_subtable_status);
    }
    else if (EQ(frame_note_type,Qproblem_with_validity_interval_of_variable)) {
	if (EQ(particulars,Qvalidity_interval_of_sensor_variable_is_supplied))
	    return VALUES_1(Qbad);
	else if (EQ(particulars,Qmissing_validity_interval))
	    return VALUES_1(Qincomplete);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qproblem_with_initial_value_for_simulation;  /* problem-with-initial-value-for-simulation */

static Object Qunused_intial_value;  /* unused-intial-value */

static Object Qproblem_with_simulation_formula;  /* problem-with-simulation-formula */

/* SIMULATION-SUBTABLE-STATUS-GIVEN-FRAME-NOTE */
Object simulation_subtable_status_given_frame_note(frame_note_type,
	    particulars,simulation_subtable)
    Object frame_note_type, particulars, simulation_subtable;
{
    x_note_fn_call(179,39);
    if (EQ(frame_note_type,Qproblem_with_initial_value_for_simulation)) {
	if (EQ(particulars,Qmissing_initial_value))
	    return VALUES_1(Qincomplete);
	else if (EQ(particulars,Qunused_intial_value))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(frame_note_type,Qproblem_with_simulation_formula))
	return VALUES_1(Qincomplete);
    else
	return VALUES_1(Qnil);
}

static Object Qexpressions_to_display;  /* expressions-to-display */

static Object Qsc;                 /* \; */

static Object Qlist_of_plots;      /* list-of-plots */

static Object Qcell_array;         /* cell-array */

static Object Qdisplay_update_priority;  /* display-update-priority */

/* PUT-EXPRESSIONS-TO-DISPLAY */
Object put_expressions_to_display(display_frame,new_expressions,
	    initializing_qm)
    Object display_frame, new_expressions, initializing_qm;
{
    Object sub_class_bit_vector, temp_1, result_1, current_flag_state_qm;
    Object slot_description, new_cons, svref_arg_2, svref_new_value;
    Object gensymed_symbol_3, gensymed_symbol_4, stack_of_slot_value_changes;
    Object gensymed_symbol_5, gensymed_symbol_6, temp_2, graph_grid_qm;
    Object display_expressions_1, graph_expression_without_info, plot_color_qm;
    Object plot_pattern_qm, plot_min_and_max_qm, graph_expression;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object redraw_as_well_as_reformat_p, frame_and_slot_or_atom, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons, cell_array_qm;
    Object priority_of_current_task, gensymed_symbol_7;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(179,40);
    if (initializing_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(display_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if ((temp ?  !TRUEP(compilations_up_to_date_p(display_frame)) : 
	    TRUEP(Nil)) ? TRUEP(Loading_kb_p) : TRUEP(Nil)) {
	if (CONSP(new_expressions)) {
	    reclaim_slot_value(CAR(new_expressions));
	    temp_1 = No_value;
	    M_CAR(new_expressions) = temp_1;
	}
	note_frame_with_compilation_removed(display_frame);
	update_frame_status(display_frame,Qincomplete,initializing_qm);
    }
    sub_class_bit_vector = ISVREF(ISVREF(display_frame,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	if (initializing_qm) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(display_frame,Qexpressions_to_display);
	    set_lookup_slot_value_1(display_frame,Qexpressions_to_display,
		    new_expressions);
	}
	else {
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(display_frame,(SI_Long)1L),Nil);
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
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_4 = 
			nconc2(stack_change_list_2(display_frame,
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
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_4) = display_frame;
		M_CDR(gensymed_symbol_4) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_4,Qstack_change);
	    }
	    M_CAR(gensymed_symbol_3) = gensymed_symbol_4;
	    temp_1 = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol_3) = temp_1;
	    inline_note_allocate_cons(gensymed_symbol_3,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol_3;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    1);
	      current_flag_state_qm = (SI_Long)0L != 
		      (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
		      (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol_3 = 
			  ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_4 = display_frame;
		  gensymed_symbol_5 = Nil;
		  gensymed_symbol_6 = T;
		  inline_funcall_3(gensymed_symbol_3,gensymed_symbol_4,
			  gensymed_symbol_5,gensymed_symbol_6);
		  svref_new_value_1 = IFIX(ISVREF(display_frame,
			  (SI_Long)5L)) | (SI_Long)16777216L;
		  ISVREF(display_frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      }
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(display_frame,
			  Qexpressions_to_display);
	      set_lookup_slot_value_1(display_frame,
		      Qexpressions_to_display,new_expressions);
	      temp_2 = ISVREF(display_frame,(SI_Long)19L);
	      temp_2 = FIRST(temp_2);
	      graph_grid_qm = FIRST(temp_2);
	      display_expressions_1 = CAR(new_expressions);
	      if ( !TRUEP(initializing_qm) && graph_grid_qm) {
		  if (display_expressions_1) {
		      if (CONSP(display_expressions_1) && 
			      EQ(CAR(display_expressions_1),Qsc)) {
			  graph_expression_without_info = Nil;
			  plot_color_qm = Nil;
			  plot_pattern_qm = Nil;
			  plot_min_and_max_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
				  0);
			    graph_expression = Nil;
			    ab_loop_list_ = CDR(display_expressions_1);
			    ab_loopvar_ = Nil;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			  next_loop:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop;
			    graph_expression = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    result = parse_graph_expression_with_info(graph_expression);
			    MVS_4(result,graph_expression_without_info,
				    plot_color_qm,plot_pattern_qm,
				    Plot_min_and_max_qm);
			    ab_loopvar__2 = 
				    slot_value_cons_1(make_plot(graph_expression_without_info,
				    plot_color_qm,plot_pattern_qm,
				    Plot_min_and_max_qm,graph_grid_qm),Nil);
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
			  POP_SPECIAL();
		      }
		      else {
			  result = parse_graph_expression_with_info(display_expressions_1);
			  MVS_4(result,graph_expression_without_info,
				  plot_color_qm,plot_pattern_qm,
				  plot_min_and_max_qm);
			  PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
				  0);
			    temp_2 = 
				    slot_value_cons_1(make_plot(graph_expression_without_info,
				    plot_color_qm,plot_pattern_qm,
				    Plot_min_and_max_qm,graph_grid_qm),Nil);
			  POP_SPECIAL();
		      }
		  }
		  else
		      temp_2 = Nil;
		  change_slot_value(3,graph_grid_qm,Qlist_of_plots,temp_2);
	      }
	      if (graph_grid_qm) {
		  redraw_as_well_as_reformat_p = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
			  0);
		    result_1 = make_or_reformat_graph_grid(5,Nil,
			    graph_grid_qm,ISVREF(display_frame,
			    (SI_Long)22L),T,T);
		  POP_SPECIAL();
	      }
	      else
		  result_1 = Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  svref_new_value_1 = IFIX(ISVREF(display_frame,
			  (SI_Long)5L)) &  ~(SI_Long)16777216L;
		  ISVREF(display_frame,(SI_Long)5L) = FIX(svref_new_value_1);
		  gensymed_symbol_3 = 
			  ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_4 = display_frame;
		  gensymed_symbol_5 = T;
		  gensymed_symbol_6 = Nil;
		  inline_funcall_3(gensymed_symbol_3,gensymed_symbol_4,
			  gensymed_symbol_5,gensymed_symbol_6);
	      }
	      temp = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp);
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
		  temp = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp);
		  else {
		      temp_2 = M_CDR(frame_and_slot_or_atom);
		      temp = CONSP(temp_2) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp ? (EQ(display_frame,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_2;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp = TRUEP(Qnil);
		end_2:;
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp)
		  update_all_representations_of_slot(display_frame,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(display_frame);
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
		  temp_2 = M_CAR(Stack_of_slot_value_changes);
		  temp = ATOM(temp_2);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	}
    }
    else if (kind_of_cell_based_display_p(display_frame)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(display_frame,Qexpressions_to_display);
	set_lookup_slot_value_1(display_frame,Qexpressions_to_display,
		new_expressions);
	if ( !TRUEP(initializing_qm)) {
	    cell_array_qm = 
		    get_lookup_slot_value_given_default(display_frame,
		    Qcell_array,Nil);
	    if (cell_array_qm)
		register_expression_cell_during_slot_putter(cell_array_qm,
			FIX((SI_Long)0L),T);
	}
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(display_frame,Qexpressions_to_display);
	set_lookup_slot_value_1(display_frame,Qexpressions_to_display,
		new_expressions);
	if ( !TRUEP(initializing_qm)) {
	    priority_of_current_task = get_lookup_slot_value(display_frame,
		    Qdisplay_update_priority);
	    PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		    0);
	      gensymed_symbol_3 = 
		      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	      gensymed_symbol_4 = display_frame;
	      gensymed_symbol_5 = Nil;
	      gensymed_symbol_6 = Nil;
	      gensymed_symbol_7 = Nil;
	      inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	    POP_SPECIAL();
	}
    }
    return VALUES_1(new_expressions);
}

static Object Qcm;                 /* \, */

/* PARSE-GRAPH-EXPRESSION-WITH-INFO */
Object parse_graph_expression_with_info(graph_expression_with_info)
    Object graph_expression_with_info;
{
    Object temp, temp_1, temp_2, min_and_max_qm, temp_3;

    x_note_fn_call(179,41);
    if (CONSP(graph_expression_with_info)) {
	if (EQ(CAR(graph_expression_with_info),Qcm)) {
	    temp = 
		    copy_tree_using_slot_value_conses_1(SECOND(graph_expression_with_info));
	    temp_1 = THIRD(graph_expression_with_info);
	    temp_2 = 
		    copy_tree_using_slot_value_conses_1(FOURTH(graph_expression_with_info));
	    min_and_max_qm = FIFTH(graph_expression_with_info);
	    temp_3 = min_and_max_qm ? 
		    slot_value_cons_1(copy_for_slot_value(CAR(min_and_max_qm)),
		    copy_for_slot_value(CDR(min_and_max_qm))) : Nil;
	    return VALUES_4(temp,temp_1,temp_2,temp_3);
	}
	else {
	    temp_3 = 
		    copy_tree_using_slot_value_conses_1(graph_expression_with_info);
	    return VALUES_4(temp_3,Nil,Nil,Nil);
	}
    }
    else
	return VALUES_4(graph_expression_with_info,Nil,Nil,Nil);
}

static Object Qlabel_to_display;   /* label-to-display */

/* PUT-LABEL-TO-DISPLAY */
Object put_label_to_display(display_frame,new_label,initializing_qm)
    Object display_frame, new_label, initializing_qm;
{
    x_note_fn_call(179,42);
    if ( !TRUEP(initializing_qm)) {
	if ( !TRUEP(text_blank_p(new_label)) && 
		text_blank_p(get_lookup_slot_value_given_default(display_frame,
		Qlabel_to_display,Nil)))
	    revise_cell_for_label_to_display(display_frame,Nil);
	else if (text_blank_p(new_label) &&  
		!TRUEP(text_blank_p(get_lookup_slot_value_given_default(display_frame,
		Qlabel_to_display,Nil))))
	    revise_cell_for_label_to_display(display_frame,T);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display_frame,Qlabel_to_display);
    return set_lookup_slot_value_1(display_frame,Qlabel_to_display,new_label);
}

/* REVISE-CELL-FOR-LABEL-TO-DISPLAY */
Object revise_cell_for_label_to_display(display_frame,new_label_blank_qm)
    Object display_frame, new_label_blank_qm;
{
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    Object changing_colors_of_graphic_elements_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,43);
    sub_class_bit_vector = ISVREF(ISVREF(display_frame,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Readout_table_class_description,(SI_Long)18L));
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
	update_images_of_block(display_frame,T,T);
	temp_1 = ISVREF(display_frame,(SI_Long)19L);
	temp_1 = CAAR(temp_1);
	reclaim_text(CDDDR(temp_1));
	temp_2 = ISVREF(display_frame,(SI_Long)19L);
	temp_3 = make_readout_table_expression_text(display_frame,
		new_label_blank_qm ? Qexpressions_to_display : 
		Qlabel_to_display,Nil);
	M_CAAR(temp_2) = temp_3;
	reformat_table_in_place(1,display_frame);
	update_images_of_block(display_frame,Nil,T);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(display_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	    changing_colors_of_graphic_elements_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
		    0);
	      update_images_of_block(display_frame,T,T);
	    POP_SPECIAL();
	    temp_1 = ISVREF(display_frame,(SI_Long)19L);
	    temp_1 = SECOND(temp_1);
	    temp_1 = CAR(temp_1);
	    reclaim_text(CDDDR(temp_1));
	    temp_1 = ISVREF(display_frame,(SI_Long)19L);
	    temp_2 = SECOND(temp_1);
	    temp_3 = 
		    make_horizontal_axis_graph_heading_text_1(display_frame,
		    new_label_blank_qm ? Qexpressions_to_display : 
		    Qlabel_to_display,Nil);
	    M_CAR(temp_2) = temp_3;
	    reformat_table_in_place(1,display_frame);
	    changing_colors_of_graphic_elements_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
		    0);
	      update_images_of_block(display_frame,Nil,T);
	    POP_SPECIAL();
	}
    }
    if (new_label_blank_qm)
	return change_slot_value(3,display_frame,Qexpressions_to_display,
		get_lookup_slot_value_given_default(display_frame,
		Qexpressions_to_display,Nil));
    else
	return VALUES_1(Nil);
}

static Object Qformat_for_readout_table;  /* format-for-readout-table */

/* PUT-FORMAT-FOR-READOUT-TABLE */
Object put_format_for_readout_table(display_frame,new_value,initializing_qm)
    Object display_frame, new_value, initializing_qm;
{
    Object priority_of_current_task, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(1);

    x_note_fn_call(179,44);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display_frame,Qformat_for_readout_table);
    set_lookup_slot_value_1(display_frame,Qformat_for_readout_table,new_value);
    if ( !TRUEP(initializing_qm)) {
	priority_of_current_task = get_lookup_slot_value(display_frame,
		Qdisplay_update_priority);
	PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		0);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	  gensymed_symbol_1 = display_frame;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  gensymed_symbol_4 = Nil;
	  inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	POP_SPECIAL();
	return VALUES_2(new_value,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdisplay_evaluation_should_use_simulated_values_qm;  /* display-evaluation-should-use-simulated-values? */

/* PUT-DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES? */
Object put_display_evaluation_should_use_simulated_values_qm(display_frame,
	    new_value,initializing_qm)
    Object display_frame, new_value, initializing_qm;
{
    Object sub_class_bit_vector, priority_of_current_task, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,45);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display_frame,
		Qdisplay_evaluation_should_use_simulated_values_qm);
    set_lookup_slot_value_1(display_frame,
	    Qdisplay_evaluation_should_use_simulated_values_qm,new_value);
    if ( !TRUEP(initializing_qm)) {
	sub_class_bit_vector = ISVREF(ISVREF(display_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	    return reformat_graph_based_on_edit_if_necessary(display_frame,
		    initializing_qm);
	else if (kind_of_cell_based_display_p(display_frame))
	    return update_cell_based_display_computation_style(1,
		    display_frame);
	else {
	    priority_of_current_task = get_lookup_slot_value(display_frame,
		    Qdisplay_update_priority);
	    PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		    0);
	      gensymed_symbol_3 = 
		      ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	      gensymed_symbol_4 = display_frame;
	      gensymed_symbol_5 = Nil;
	      gensymed_symbol_6 = Nil;
	      gensymed_symbol_7 = Nil;
	      inline_funcall_4(gensymed_symbol_3,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6,gensymed_symbol_7);
	    POP_SPECIAL();
	    return VALUES_2(new_value,Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qlow_value_for_dial_ruling;  /* low-value-for-dial-ruling */

/* PUT-LOW-VALUE-FOR-DIAL-RULING */
Object put_low_value_for_dial_ruling(dial,new_value,initializing_qm)
    Object dial, new_value, initializing_qm;
{
    x_note_fn_call(179,46);
    return put_slot_value_for_dial_ruling_parameter(dial,
	    Qlow_value_for_dial_ruling,new_value,initializing_qm);
}

static Object Qhigh_value_for_dial_ruling;  /* high-value-for-dial-ruling */

/* PUT-HIGH-VALUE-FOR-DIAL-RULING */
Object put_high_value_for_dial_ruling(dial,new_value,initializing_qm)
    Object dial, new_value, initializing_qm;
{
    x_note_fn_call(179,47);
    return put_slot_value_for_dial_ruling_parameter(dial,
	    Qhigh_value_for_dial_ruling,new_value,initializing_qm);
}

static Object Qincrement_per_dial_ruling;  /* increment-per-dial-ruling */

/* PUT-INCREMENT-PER-DIAL-RULING */
Object put_increment_per_dial_ruling(dial,new_value,initializing_qm)
    Object dial, new_value, initializing_qm;
{
    x_note_fn_call(179,48);
    return put_slot_value_for_dial_ruling_parameter(dial,
	    Qincrement_per_dial_ruling,new_value,initializing_qm);
}

static Object Qlow_value_for_meter_ruling;  /* low-value-for-meter-ruling */

/* PUT-LOW-VALUE-FOR-METER-RULING */
Object put_low_value_for_meter_ruling(meter,new_value,initializing_qm)
    Object meter, new_value, initializing_qm;
{
    x_note_fn_call(179,49);
    return put_slot_value_for_meter_ruling_parameter(meter,
	    Qlow_value_for_meter_ruling,new_value,initializing_qm);
}

static Object Qhigh_value_for_meter_ruling;  /* high-value-for-meter-ruling */

/* PUT-HIGH-VALUE-FOR-METER-RULING */
Object put_high_value_for_meter_ruling(meter,new_value,initializing_qm)
    Object meter, new_value, initializing_qm;
{
    x_note_fn_call(179,50);
    return put_slot_value_for_meter_ruling_parameter(meter,
	    Qhigh_value_for_meter_ruling,new_value,initializing_qm);
}

static Object Qincrement_per_meter_ruling;  /* increment-per-meter-ruling */

/* PUT-INCREMENT-PER-METER-RULING */
Object put_increment_per_meter_ruling(meter,new_value,initializing_qm)
    Object meter, new_value, initializing_qm;
{
    x_note_fn_call(179,51);
    return put_slot_value_for_meter_ruling_parameter(meter,
	    Qincrement_per_meter_ruling,new_value,initializing_qm);
}

/* PUT-SLOT-VALUE-FOR-DIAL-RULING-PARAMETER */
Object put_slot_value_for_dial_ruling_parameter(dial,slot_name,new_value,
	    initializing_qm)
    Object dial, slot_name, new_value, initializing_qm;
{
    Object dial_ruling, priority_of_current_task, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;
    Declare_special(1);

    x_note_fn_call(179,52);
    set_slot_value_function(dial,slot_name,new_value,Nil);
    if ( !TRUEP(initializing_qm)) {
	dial_ruling = get_ruling_for_dial(dial);
	update_images_of_block(dial_ruling,T,T);
	make_or_reformat_ruling_for_dial(dial_ruling,dial);
	update_images_of_block(dial_ruling,Nil,T);
	priority_of_current_task = get_lookup_slot_value(dial,
		Qdisplay_update_priority);
	PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		0);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(dial,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	  gensymed_symbol_1 = dial;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  gensymed_symbol_4 = Nil;
	  inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	POP_SPECIAL();
	return VALUES_2(new_value,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-SLOT-VALUE-FOR-METER-RULING-PARAMETER */
Object put_slot_value_for_meter_ruling_parameter(meter,slot_name,new_value,
	    initializing_qm)
    Object meter, slot_name, new_value, initializing_qm;
{
    Object meter_ruling, priority_of_current_task, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;
    Declare_special(1);

    x_note_fn_call(179,53);
    set_slot_value_function(meter,slot_name,new_value,Nil);
    if ( !TRUEP(initializing_qm)) {
	meter_ruling = get_ruling_for_meter(meter);
	update_images_of_block(meter_ruling,T,T);
	make_or_reformat_ruling_for_meter(meter_ruling,meter);
	update_images_of_block(meter_ruling,Nil,T);
	priority_of_current_task = get_lookup_slot_value(meter,
		Qdisplay_update_priority);
	PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		0);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(meter,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	  gensymed_symbol_1 = meter;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = Nil;
	  gensymed_symbol_4 = Nil;
	  inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	POP_SPECIAL();
	return VALUES_2(new_value,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qwithout_tickmark_labels;  /* without-tickmark-labels */

/* WITHOUT-TICKMARK-LABELS-STATE-CHANGED-P */
Object without_tickmark_labels_state_changed_p(new_value,old_value)
    Object new_value, old_value;
{
    x_note_fn_call(179,54);
    return g2_xor(CONSP(new_value) ? (EQ(CAR(new_value),
	    Qwithout_tickmark_labels) ? T : Nil) : Qnil,CONSP(old_value) ? 
	    (EQ(CAR(old_value),Qwithout_tickmark_labels) ? T : Nil) : Qnil);
}

static Object Qdesired_range_for_horizontal_axis_qm;  /* desired-range-for-horizontal-axis? */

/* PUT-DESIRED-RANGE-FOR-HORIZONTAL-AXIS? */
Object put_desired_range_for_horizontal_axis_qm(graph,new_value,
	    initializing_qm)
    Object graph, new_value, initializing_qm;
{
    Object temp, changing_graph_margins_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,55);
    temp = Changing_graph_margins_qm;
    if (temp);
    else
	temp = without_tickmark_labels_state_changed_p(new_value,
		ISVREF(graph,(SI_Long)23L));
    changing_graph_margins_qm = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Changing_graph_margins_qm,Qchanging_graph_margins_qm,changing_graph_margins_qm,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(graph,Qdesired_range_for_horizontal_axis_qm);
      SVREF(graph,FIX((SI_Long)23L)) = new_value;
      result = reformat_graph_based_on_edit_if_necessary(graph,
	      initializing_qm);
    POP_SPECIAL();
    return result;
}

static Object Qdesired_range_for_vertical_axis_qm;  /* desired-range-for-vertical-axis? */

/* PUT-DESIRED-RANGE-FOR-VERTICAL-AXIS? */
Object put_desired_range_for_vertical_axis_qm(graph,new_value,initializing_qm)
    Object graph, new_value, initializing_qm;
{
    Object temp, changing_graph_margins_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,56);
    temp = Changing_graph_margins_qm;
    if (temp);
    else
	temp = without_tickmark_labels_state_changed_p(new_value,
		ISVREF(graph,(SI_Long)24L));
    changing_graph_margins_qm = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Changing_graph_margins_qm,Qchanging_graph_margins_qm,changing_graph_margins_qm,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(graph,Qdesired_range_for_vertical_axis_qm);
      SVREF(graph,FIX((SI_Long)24L)) = new_value;
      result = reformat_graph_based_on_edit_if_necessary(graph,
	      initializing_qm);
    POP_SPECIAL();
    return result;
}

static Object Qinterval_between_horizontal_grid_lines_qm;  /* interval-between-horizontal-grid-lines? */

/* PUT-INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES? */
Object put_interval_between_horizontal_grid_lines_qm(graph,new_value,
	    initializing_qm)
    Object graph, new_value, initializing_qm;
{
    x_note_fn_call(179,57);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(graph,
		Qinterval_between_horizontal_grid_lines_qm);
    SVREF(graph,FIX((SI_Long)28L)) = new_value;
    return reformat_graph_based_on_edit_if_necessary(graph,initializing_qm);
}

static Object Qscroll_continuously_qm;  /* scroll-continuously? */

/* PUT-SCROLL-CONTINUOUSLY? */
Object put_scroll_continuously_qm(graph,new_value,initializing_qm)
    Object graph, new_value, initializing_qm;
{
    x_note_fn_call(179,58);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(graph,Qscroll_continuously_qm);
    SVREF(graph,FIX((SI_Long)25L)) = new_value;
    return reformat_graph_based_on_edit_if_necessary(graph,initializing_qm);
}

static Object Qshow_grid_lines_qm;  /* show-grid-lines? */

/* PUT-SHOW-GRID-LINES? */
Object put_show_grid_lines_qm(graph,new_value,initializing_qm)
    Object graph, new_value, initializing_qm;
{
    x_note_fn_call(179,59);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(graph,Qshow_grid_lines_qm);
    SVREF(graph,FIX((SI_Long)27L)) = new_value;
    return reformat_graph_based_on_edit_if_necessary(graph,initializing_qm);
}

static Object Qextra_grid_lines_qm;  /* extra-grid-lines? */

/* PUT-EXTRA-GRID-LINES? */
Object put_extra_grid_lines_qm(graph,new_value,initializing_qm)
    Object graph, new_value, initializing_qm;
{
    x_note_fn_call(179,60);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(graph,Qextra_grid_lines_qm);
    SVREF(graph,FIX((SI_Long)29L)) = new_value;
    return reformat_graph_based_on_edit_if_necessary(graph,initializing_qm);
}

static Object Qbackground_colors;  /* background-colors */

/* PUT-BACKGROUND-COLORS */
Object put_background_colors(graph,new_value,initializing_qm)
    Object graph, new_value, initializing_qm;
{
    x_note_fn_call(179,61);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(graph,Qbackground_colors);
    set_lookup_slot_value_1(graph,Qbackground_colors,new_value);
    return reformat_graph_based_on_edit_if_necessary(graph,initializing_qm);
}

/* REFORMAT-GRAPH-BASED-ON-EDIT-IF-NECESSARY */
Object reformat_graph_based_on_edit_if_necessary(graph,initializing_qm)
    Object graph, initializing_qm;
{
    Object redraw_as_well_as_reformat_p, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,62);
    if ( !TRUEP(initializing_qm)) {
	redraw_as_well_as_reformat_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		0);
	  temp = ISVREF(graph,(SI_Long)19L);
	  temp = FIRST(temp);
	  result = make_or_reformat_graph_grid(5,Nil,FIRST(temp),
		  ISVREF(graph,(SI_Long)22L),T,T);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qdisplay_update_interval;  /* display-update-interval */

/* PUT-DISPLAY-UPDATE-INTERVAL */
Object put_display_update_interval(display,new_value,initializing_qm)
    Object display, new_value, initializing_qm;
{
    x_note_fn_call(179,63);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display,Qdisplay_update_interval);
    set_lookup_slot_value_1(display,Qdisplay_update_interval,new_value);
    if (kind_of_cell_based_display_p(display)) {
	if ( !TRUEP(initializing_qm))
	    update_cell_based_display_computation_style(1,display);
    }
    else
	reschedule_display_update(display,initializing_qm);
    return VALUES_1(new_value);
}

static Object Qdisplay_wait_interval;  /* display-wait-interval */

/* PUT-DISPLAY-WAIT-INTERVAL */
Object put_display_wait_interval(display,new_value,initializing_qm)
    Object display, new_value, initializing_qm;
{
    x_note_fn_call(179,64);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display,Qdisplay_wait_interval);
    set_lookup_slot_value_1(display,Qdisplay_wait_interval,new_value);
    if (kind_of_cell_based_display_p(display)) {
	if ( !TRUEP(initializing_qm))
	    update_cell_based_display_computation_style(1,display);
    }
    else
	reschedule_display_update(display,initializing_qm);
    return VALUES_1(new_value);
}

/* PUT-DISPLAY-UPDATE-PRIORITY */
Object put_display_update_priority(display,new_value,initializing_qm)
    Object display, new_value, initializing_qm;
{
    x_note_fn_call(179,65);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(display,Qdisplay_update_priority);
    set_lookup_slot_value_1(display,Qdisplay_update_priority,new_value);
    if (kind_of_cell_based_display_p(display)) {
	if ( !TRUEP(initializing_qm))
	    update_cell_based_display_computation_style(1,display);
    }
    else
	reschedule_display_update(display,initializing_qm);
    return VALUES_1(new_value);
}

/* SCHEDULED-DISPLAY-UPDATE */
Object scheduled_display_update(display)
    Object display;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(179,66);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(display,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
    gensymed_symbol_1 = display;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = Nil;
    gensymed_symbol_4 = Nil;
    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qscheduled_display_update;  /* scheduled-display-update */

/* RESCHEDULE-DISPLAY-UPDATE */
Object reschedule_display_update(display,initializing_qm)
    Object display, initializing_qm;
{
    Object temp, wait_1, update, old, new_1;
    Object def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    char temp_1, svref_new_value_1;
    double gensymed_symbol, gensymed_symbol_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(179,67);
    if ( !TRUEP(initializing_qm)) {
	temp = ISVREF(display,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != (IFIX(ISVREF(display,
		(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(display,(SI_Long)4L)) & (SI_Long)16777216L) 
		&&  !((SI_Long)0L != (IFIX(ISVREF(display,(SI_Long)4L)) & 
		(SI_Long)8192L)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	wait_1 = get_lookup_slot_value(display,Qdisplay_wait_interval);
	update = get_lookup_slot_value(display,Qdisplay_update_interval);
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(display,(SI_Long)20L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_2 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp_2 = ISVREF(task,(SI_Long)1L);
	gensymed_symbol = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	gensymed_symbol_1 = FIXNUMP(wait_1) ? (double)IFIX(wait_1) : 
		DFLOAT_ISAREF_1(wait_1,(SI_Long)0L);
	aref_new_value = gensymed_symbol + gensymed_symbol_1;
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
	temp_2 = ISVREF(task,(SI_Long)1L);
	aref_new_value = FIXNUMP(update) ? (double)IFIX(update) : 
		DFLOAT_ISAREF_1(update,(SI_Long)0L);
	DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	temp_2 = get_lookup_slot_value(display,Qdisplay_update_priority);
	SVREF(task,FIX((SI_Long)4L)) = temp_2;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qscheduled_display_update;
	temp_2 = SYMBOL_FUNCTION(Qscheduled_display_update);
	SVREF(task,FIX((SI_Long)8L)) = temp_2;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = display;
	new_1 = task;
	if (CAS_SVREF(display,(SI_Long)20L,old,new_1)) {
	    if (old) {
		if (EQ(old,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(old,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(old);
		inline_note_reclaim_cons(old,Nil);
		structure_being_reclaimed = old;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    return VALUES_1(new_1);
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
	    temp_2 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_stored_history_specification_qm;  /* simulation-stored-history-specification? */

/* SET-SIMULATION-STORED-HISTORY-SPEC-FOR-UPDATE-SLOT-DESCRIPTION */
Object set_simulation_stored_history_spec_for_update_slot_description(class_1,
	    unchanged_slot_init_form,new_slot_init_form_qm)
    Object class_1, unchanged_slot_init_form, new_slot_init_form_qm;
{
    Object ab_loopvar_, instance, simulation_details, temp;
    char temp_1;

    x_note_fn_call(179,68);
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    simulation_details = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    simulation_details = get_lookup_slot_value(instance,Qsimulation_details);
    if (simulation_details) {
	temp = ISVREF(simulation_details,(SI_Long)21L);
	temp_1 = EQUAL(temp,unchanged_slot_init_form);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	change_slot_value(3,simulation_details,
		Qsimulation_stored_history_specification_qm,
		copy_for_slot_value(new_slot_init_form_qm));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qvariable_or_parameter_history_specification_qm;  /* variable-or-parameter-history-specification? */

/* PUT-VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION? */
Object put_variable_or_parameter_history_specification_qm(variable,
	    new_value,initializing_qm)
    Object variable, new_value, initializing_qm;
{
    Object svref_new_value;

    x_note_fn_call(179,69);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,
		Qvariable_or_parameter_history_specification_qm);
    SVREF(variable,FIX((SI_Long)25L)) = new_value;
    if ( !TRUEP(initializing_qm)) {
	svref_new_value = reformat_history_based_on_edit(ISVREF(variable,
		(SI_Long)24L),new_value);
	return VALUES_1(ISVREF(variable,(SI_Long)24L) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-SIMULATION-STORED-HISTORY-SPECIFICATION? */
Object put_simulation_stored_history_specification_qm(simulation_subtable,
	    new_value,initializing_qm)
    Object simulation_subtable, new_value, initializing_qm;
{
    Object svref_new_value;

    x_note_fn_call(179,70);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_subtable,
		Qsimulation_stored_history_specification_qm);
    SVREF(simulation_subtable,FIX((SI_Long)21L)) = new_value;
    if ( !TRUEP(initializing_qm)) {
	svref_new_value = 
		reformat_history_based_on_edit(ISVREF(simulation_subtable,
		(SI_Long)20L),new_value);
	return VALUES_1(ISVREF(simulation_subtable,(SI_Long)20L) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* REFORMAT-HISTORY-BASED-ON-EDIT */
Object reformat_history_based_on_edit(value_history_cascaded_ring_buffer_qm,
	    new_value)
    Object value_history_cascaded_ring_buffer_qm, new_value;
{
    Object maximum_number_of_data_points_qm, maximum_age_of_data_points_qm;
    Object temp, gensymed_symbol, ab_loop_list_;

    x_note_fn_call(179,71);
    maximum_number_of_data_points_qm = SECOND(new_value);
    maximum_age_of_data_points_qm = THIRD(new_value);
    if (value_history_cascaded_ring_buffer_qm) {
	if (maximum_number_of_data_points_qm || 
		    maximum_age_of_data_points_qm) {
	    temp = 
		    make_or_reformat_cascaded_ring_buffer(value_history_cascaded_ring_buffer_qm,
		    SECOND(new_value),THIRD(new_value),FOURTH(new_value));
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(value_history_cascaded_ring_buffer_qm,
		    (SI_Long)11L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	    goto next_loop;
	  end_loop:;
	    return VALUES_1(temp);
	}
	else {
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(value_history_cascaded_ring_buffer_qm,
		    (SI_Long)11L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:;
	    reclaim_history_buffer(value_history_cascaded_ring_buffer_qm);
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

Object Generic_simulation_formulas_for_this_role_kbprop = UNBOUND;

/* ADD-FORMULA-TO-GENERIC-SIMULATION-FORMULAS-FOR-THIS-ROLE */
Object add_formula_to_generic_simulation_formulas_for_this_role(role,
	    class_or_item,new_generic_simulation_formula)
    Object role, class_or_item, new_generic_simulation_formula;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, temp_1, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_2;

    x_note_fn_call(179,72);
    temp = 
	    compute_key_from_role_class_or_item(atomic_naming_element_of_role(role),
	    class_or_item);
    gensymed_symbol = lookup_kb_specific_property_value(temp,
	    Generic_simulation_formulas_for_this_role_kbprop);
    gensymed_symbol_1 = new_generic_simulation_formula;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	temp = gensymed_symbol_1;
	temp_1 = 
		compute_key_from_role_class_or_item(atomic_naming_element_of_role(role),
		class_or_item);
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		Generic_simulation_formulas_for_this_role_kbprop);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FORMULA-FROM-GENERIC-SIMULATION-FORMULAS-FOR-THIS-ROLE */
Object delete_formula_from_generic_simulation_formulas_for_this_role(role,
	    class_or_item,generic_simulation_formula_to_delete)
    Object role, class_or_item, generic_simulation_formula_to_delete;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, gensymed_symbol_2, temp_1;
    Object svref_arg_2;

    x_note_fn_call(179,73);
    gensymed_symbol = generic_simulation_formula_to_delete;
    gensymed_symbol_1 = Nil;
    temp = compute_key_from_role_class_or_item(role,class_or_item);
    gensymed_symbol_2 = lookup_kb_specific_property_value(temp,
	    Generic_simulation_formulas_for_this_role_kbprop);
  next_loop:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop;
    if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	if (gensymed_symbol_1) {
	    temp_1 = CDR(gensymed_symbol_2);
	    M_CDR(gensymed_symbol_1) = temp_1;
	}
	else {
	    temp = compute_key_from_role_class_or_item(role,class_or_item);
	    mutate_kb_specific_property_value(temp,CDR(gensymed_symbol_2),
		    Generic_simulation_formulas_for_this_role_kbprop);
	}
	temp = CAR(gensymed_symbol_2);
	inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = gensymed_symbol_2;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
	return VALUES_1(temp);
    }
    gensymed_symbol_1 = gensymed_symbol_2;
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COMPUTE-KEY-FROM-ROLE-CLASS-OR-ITEM */
Object compute_key_from_role_class_or_item(role,class_or_item)
    Object role, class_or_item;
{
    Object temp;

    x_note_fn_call(179,74);
    temp = role;
    if (temp)
	return VALUES_1(temp);
    else
	return get_simulation_formula_class_or_item_name(class_or_item);
}

/* GET-SIMULATION-FORMULA-CLASS-OR-ITEM-NAME */
Object get_simulation_formula_class_or_item_name(class_or_item)
    Object class_or_item;
{
    x_note_fn_call(179,75);
    if (SYMBOLP(class_or_item))
	return VALUES_1(class_or_item);
    else
	return VALUES_1(SECOND(class_or_item));
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_analyzer_warning_notes_for_generic_simulation_formulas_qm, Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm);

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-GENERIC-SIMULATION-FORMULA */
Object put_box_translation_and_text_slot_value_for_generic_simulation_formula(generic_simulation_formula,
	    box_translation_and_text,initializing_qm)
    Object generic_simulation_formula, box_translation_and_text;
    Object initializing_qm;
{
    Object temp;
    Object post_analyzer_warning_notes_for_generic_simulation_formulas_qm;
    Object result_1, current_flag_state_qm, slot_description, new_cons;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object temp_2, old_translation_qm, new_translation, new_role_name;
    Object old_role_name, new_class_or_item, old_class_or_item, new_left_side;
    Object old_left_side, frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(179,76);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(generic_simulation_formula)) 
	    && Loading_kb_p) {
	reclaim_slot_value(CAR(box_translation_and_text));
	temp = No_value;
	M_CAR(box_translation_and_text) = temp;
	note_frame_with_compilation_removed(generic_simulation_formula);
    }
    post_analyzer_warning_notes_for_generic_simulation_formulas_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Post_analyzer_warning_notes_for_generic_simulation_formulas_qm,Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm,post_analyzer_warning_notes_for_generic_simulation_formulas_qm,
	    1);
      result_1 = Nil;
      current_flag_state_qm = Nil;
      slot_description = 
	      get_slot_description_of_class_description_function(Qframe_status_and_notes,
	      ISVREF(generic_simulation_formula,(SI_Long)1L),Nil);
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
		  nconc2(stack_change_list_2(generic_simulation_formula,
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
	  M_CAR(gensymed_symbol_1) = generic_simulation_formula;
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
	current_flag_state_qm = (SI_Long)0L != 
		(IFIX(ISVREF(generic_simulation_formula,(SI_Long)5L)) & 
		(SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = generic_simulation_formula;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = T;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		    (SI_Long)5L)) | (SI_Long)16777216L;
	    ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		    FIX(svref_new_value_1);
	}
	temp_1 = TRUEP(initializing_qm);
	if (temp_1);
	else
	    temp_1 =  !TRUEP(ISVREF(generic_simulation_formula,(SI_Long)16L));
	if (temp_1);
	else {
	    temp_2 = ISVREF(generic_simulation_formula,(SI_Long)16L);
	    temp_1 = EQ(CAR(temp_2),No_value);
	}
	if ( !temp_1) {
	    temp_2 = ISVREF(generic_simulation_formula,(SI_Long)16L);
	    old_translation_qm = CAR(temp_2);
	}
	else
	    old_translation_qm = Nil;
	new_translation = CONSP(box_translation_and_text) &&  
		!EQ(CAR(box_translation_and_text),No_value) ? 
		CAR(box_translation_and_text) : Nil;
	new_role_name = Nil;
	old_role_name = Nil;
	new_class_or_item = Nil;
	old_class_or_item = Nil;
	new_left_side = Nil;
	old_left_side = Nil;
	if (new_translation) {
	    new_role_name = FIRST(new_translation);
	    new_class_or_item = SECOND(new_translation);
	    new_left_side = SEVENTH(new_translation);
	}
	if (old_translation_qm) {
	    old_role_name = FIRST(old_translation_qm);
	    old_class_or_item = SECOND(old_translation_qm);
	    old_left_side = SEVENTH(old_translation_qm);
	}
	if (old_translation_qm) {
	    delete_formula_from_generic_simulation_formulas_for_this_role(old_role_name,
		    old_class_or_item,generic_simulation_formula);
	    forward_install_variables_for_generic_simulation_formula(old_left_side,
		    old_class_or_item,generic_simulation_formula);
	}
	if ((ISVREF(generic_simulation_formula,(SI_Long)20L) || 
		Loading_kb_p) && THIRD(new_translation))
	    temp_2 = Nil;
	else if (compiler_errors_qm(generic_simulation_formula) ||  
		!TRUEP(Loading_kb_p) && THIRD(new_translation) &&  
		!TRUEP(ISVREF(generic_simulation_formula,(SI_Long)20L)) || 
		old_translation_qm)
	    temp_2 = Qbad;
	else
	    temp_2 = Qincomplete;
	update_frame_status(generic_simulation_formula,temp_2,initializing_qm);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(generic_simulation_formula,
		    Qbox_translation_and_text);
	SVREF(generic_simulation_formula,FIX((SI_Long)16L)) = 
		box_translation_and_text;
	if (new_translation) {
	    add_formula_to_generic_simulation_formulas_for_this_role(new_role_name,
		    new_class_or_item,generic_simulation_formula);
	    forward_install_variables_for_generic_simulation_formula(new_left_side,
		    new_class_or_item,generic_simulation_formula);
	}
	update_runtime_structures_according_to_edit(1,
		generic_simulation_formula);
	result_1 = update_generic_simulation_formulas_used_p();
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		    (SI_Long)5L)) &  ~(SI_Long)16777216L;
	    ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		    FIX(svref_new_value_1);
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = generic_simulation_formula;
	    gensymed_symbol_2 = T;
	    gensymed_symbol_3 = Nil;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	if (temp_1);
	else if (M_CDR(Stack_of_slot_value_changes)) {
	    frame_and_slot_or_atom = Nil;
	    ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ATOM(frame_and_slot_or_atom))
		goto end_loop;
	    temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	    if (temp_1);
	    else {
		temp_2 = M_CDR(frame_and_slot_or_atom);
		temp_1 = CONSP(temp_2) ? EQ(slot_description,
			SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	    }
	    ab_loop_it_ = temp_1 ? (EQ(generic_simulation_formula,
		    M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1)
	    update_all_representations_of_slot(generic_simulation_formula,
		    slot_description,Nil,Nil);
	if (ISVREF(slot_description,(SI_Long)14L))
	    update_frame_name_references(generic_simulation_formula);
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
	    temp_2 = M_CAR(Stack_of_slot_value_changes);
	    temp_1 = ATOM(temp_2);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  
		!TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		TRUEP(Nil))
	    do_deferred_updates_to_representations_in_tables();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(box_translation_and_text,Nil);
}

/* UPDATE-GENERIC-SIMULATION-FORMULAS-USED-P */
Object update_generic_simulation_formulas_used_p()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, formula, ab_loop_it_;
    char temp;
    Declare_special(1);

    x_note_fn_call(179,77);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    formula = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qgeneric_simulation_formula);
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
      formula = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ = formula;
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if (temp) {
	Generic_simulation_formulas_used_p = T;
	return VALUES_1(Generic_simulation_formulas_used_p);
    }
    else {
	Generic_simulation_formulas_used_p = Nil;
	return VALUES_1(Generic_simulation_formulas_used_p);
    }
}

static Object Qgeneric_simulation_formula_byte_code_body;  /* generic-simulation-formula-byte-code-body */

/* PUT-GENERIC-SIMULATION-FORMULA-BYTE-CODE-BODY */
Object put_generic_simulation_formula_byte_code_body(generic_simulation_formula,
	    new_byte_code_body,initializing_qm)
    Object generic_simulation_formula, new_byte_code_body, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,78);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(generic_simulation_formula)) 
	    && Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(generic_simulation_formula);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(generic_simulation_formula,(SI_Long)1L),Nil);
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
		nconc2(stack_change_list_2(generic_simulation_formula,
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
	M_CAR(gensymed_symbol_1) = generic_simulation_formula;
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
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(generic_simulation_formula,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_simulation_formula;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(generic_simulation_formula,
		  Qgeneric_simulation_formula_byte_code_body);
      result_1 = SVREF(generic_simulation_formula,FIX((SI_Long)20L)) = 
	      new_byte_code_body;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_simulation_formula;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(generic_simulation_formula,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(generic_simulation_formula,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(generic_simulation_formula);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_byte_code_body);
}

static Object Qgeneric_simulation_initial_value_byte_code_body;  /* generic-simulation-initial-value-byte-code-body */

/* PUT-GENERIC-SIMULATION-INITIAL-VALUE-BYTE-CODE-BODY */
Object put_generic_simulation_initial_value_byte_code_body(generic_simulation_formula,
	    new_byte_code_body,initializing_qm)
    Object generic_simulation_formula, new_byte_code_body, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,79);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(generic_simulation_formula)) 
	    && Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(generic_simulation_formula);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(generic_simulation_formula,(SI_Long)1L),Nil);
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
		nconc2(stack_change_list_2(generic_simulation_formula,
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
	M_CAR(gensymed_symbol_1) = generic_simulation_formula;
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
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(generic_simulation_formula,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_simulation_formula;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(generic_simulation_formula,
		  Qgeneric_simulation_initial_value_byte_code_body);
      result_1 = SVREF(generic_simulation_formula,FIX((SI_Long)21L)) = 
	      new_byte_code_body;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(generic_simulation_formula,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(generic_simulation_formula,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_simulation_formula;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(generic_simulation_formula,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(generic_simulation_formula,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(generic_simulation_formula);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_byte_code_body);
}

/* CLEANUP-FOR-GENERIC-SIMULATION-FORMULA */
Object cleanup_for_generic_simulation_formula(generic_simulation_formula)
    Object generic_simulation_formula;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(179,80);
    frame = generic_simulation_formula;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgeneric_simulation_formula)) {
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
    change_slot_value(3,generic_simulation_formula,
	    Qgeneric_simulation_formula_byte_code_body,Nil);
    change_slot_value(3,generic_simulation_formula,
	    Qgeneric_simulation_initial_value_byte_code_body,Nil);
    return change_slot_value(3,generic_simulation_formula,
	    Qbox_translation_and_text,Nil);
}

/* FORWARD-INSTALL-VARIABLES-FOR-GENERIC-SIMULATION-FORMULA */
Object forward_install_variables_for_generic_simulation_formula(left_side_designation,
	    class_or_item,generic_simulation_formula)
    Object left_side_designation, class_or_item, generic_simulation_formula;
{
    Object alist, current_computation_frame, current_computation_flags;
    Object designated_item, scope_conses, ab_loopvar_, ab_loopvar__1, item, x2;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(179,81);
    if ( !TRUEP(Loading_kb_p)) {
	if (SYMBOLP(class_or_item)) {
	    alist = gensym_cons_1(gensym_cons_1(class_or_item,Nil),Nil);
	    current_computation_frame = generic_simulation_formula;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    2);
	      current_computation_flags = Current_computation_flags;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		      1);
		designated_item = Nil;
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
		  ab_loopvar_ = collect_subclasses(class_or_item);
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
		  M_CDAR(alist) = item;
		  designated_item = 
			  evaluate_designation(left_side_designation,alist);
		  if (SIMPLE_VECTOR_P(designated_item) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(designated_item)) 
			  > (SI_Long)2L &&  !EQ(ISVREF(designated_item,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(designated_item,(SI_Long)1L);
		      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
			      EQ(ISVREF(x2,(SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      gensymed_symbol = Nil;
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Variable_or_parameter_class_description,
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
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      update_generic_simulation_formula_for_variable_or_parameter(designated_item);
		  goto next_loop;
		end_loop_1:
		  reclaim_gensym_tree_1(alist);
		  result = VALUES_1(Qnil);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    1);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	      current_computation_frame = generic_simulation_formula;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		designated_item = 
			evaluate_designation(left_side_designation,Nil);
		if (SIMPLE_VECTOR_P(designated_item) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(designated_item)) > 
			(SI_Long)2L &&  !EQ(ISVREF(designated_item,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(designated_item,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    result = update_generic_simulation_formula_for_variable_or_parameter(designated_item);
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* GENERIC-SIMULATION-FORMULA-FOR-VARIABLE-OR-PARAMETER */
Object generic_simulation_formula_for_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object formula, focal_entity_qm, name_or_names, name, ab_loop_list_;
    Object parent_entity, slot_name;
    Object result;

    x_note_fn_call(179,82);
    formula = Nil;
    focal_entity_qm = Nil;
    name_or_names = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qname_or_names_for_frame,Nil);
    if (CONSP(name_or_names)) {
	name = Nil;
	ab_loop_list_ = name_or_names;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = generic_simulation_formula_for_variable_or_parameter_1(variable_or_parameter,
		name);
	MVS_2(result,formula,focal_entity_qm);
	if (formula)
	    return VALUES_2(formula,focal_entity_qm);
	goto next_loop;
      end_loop:;
    }
    else {
	result = generic_simulation_formula_for_variable_or_parameter_1(variable_or_parameter,
		name_or_names);
	MVS_2(result,formula,focal_entity_qm);
	if (formula)
	    return VALUES_2(formula,focal_entity_qm);
    }
    result = generic_simulation_formula_for_variable_or_parameter_1(variable_or_parameter,
	    ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),(SI_Long)1L));
    MVS_2(result,formula,focal_entity_qm);
    if (formula)
	return VALUES_2(formula,focal_entity_qm);
    result = get_kb_parent_information(variable_or_parameter);
    MVS_2(result,parent_entity,slot_name);
    if (parent_entity)
	return generic_simulation_formula_for_variable_or_parameter_1(variable_or_parameter,
		slot_name);
    else
	return VALUES_1(Nil);
}

/* GENERIC-SIMULATION-FORMULA-FOR-VARIABLE-OR-PARAMETER-1 */
Object generic_simulation_formula_for_variable_or_parameter_1(variable_or_parameter,
	    role_or_other_key)
    Object variable_or_parameter, role_or_other_key;
{
    Object most_specific_formula, most_specific_class_qm, focal_entity_qm;
    Object gensymed_symbol, old_star_current_computation_frame_star;
    Object old_note_things_encountered_during_role_service_qm;
    Object old_things_that_affect_this_formula, old_current_computation_flags;
    Object simulation_formula, ab_loop_list_, temp, class_or_item;
    Object old_get_focal_entity_for_simulation_formula_qm;
    Object old_focal_entity_for_simulation_formula;
    char temp_1;

    x_note_fn_call(179,83);
    if (role_or_other_key) {
	most_specific_formula = Nil;
	most_specific_class_qm = Nil;
	focal_entity_qm = Nil;
	gensymed_symbol = Nil;
	old_star_current_computation_frame_star = Current_computation_frame;
	old_note_things_encountered_during_role_service_qm = 
		Note_things_encountered_during_role_service_qm;
	old_things_that_affect_this_formula = Things_that_affect_this_formula;
	old_current_computation_flags = Current_computation_flags;
	Current_computation_frame = variable_or_parameter;
	Note_things_encountered_during_role_service_qm = T;
	Things_that_affect_this_formula = Nil;
	Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
		(SI_Long)16L);
	simulation_formula = Nil;
	ab_loop_list_ = 
		lookup_kb_specific_property_value(role_or_other_key,
		Generic_simulation_formulas_for_this_role_kbprop);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	simulation_formula = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = ISVREF(simulation_formula,(SI_Long)8L);
	if ( !TRUEP(CAR(temp))) {
	    temp = ISVREF(simulation_formula,(SI_Long)16L);
	    temp = CAR(temp);
	    class_or_item = SECOND(temp);
	    if (SYMBOLP(class_or_item)) {
		temp_1 =  !TRUEP(most_specific_class_qm);
		if (temp_1);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(most_specific_class_qm,
			    Class_description_gkbprop);
		    temp_1 =  !(gensymed_symbol ? 
			    TRUEP(memq_function(class_or_item,
			    ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			    TRUEP(Nil));
		}
		if (temp_1) {
		    gensymed_symbol = Nil;
		    old_get_focal_entity_for_simulation_formula_qm = 
			    Get_focal_entity_for_simulation_formula_qm;
		    old_focal_entity_for_simulation_formula = 
			    Focal_entity_for_simulation_formula;
		    Get_focal_entity_for_simulation_formula_qm = T;
		    Focal_entity_for_simulation_formula = Nil;
		    if (generic_simulation_formula_applies_to_this_variable_qm(simulation_formula,
			    variable_or_parameter)) {
			most_specific_class_qm = class_or_item;
			most_specific_formula = simulation_formula;
			focal_entity_qm = Focal_entity_for_simulation_formula;
			gensymed_symbol = focal_entity_qm;
		    }
		    else
			gensymed_symbol = Nil;
		    Get_focal_entity_for_simulation_formula_qm = 
			    old_get_focal_entity_for_simulation_formula_qm;
		    Focal_entity_for_simulation_formula = 
			    old_focal_entity_for_simulation_formula;
		}
	    }
	    else if (generic_simulation_formula_applies_to_this_variable_qm(simulation_formula,
		    variable_or_parameter)) {
		note_runtime_structure_in_things_that_affect_it(variable_or_parameter,
			Things_that_affect_this_formula,T);
		reclaim_eval_list_1(Things_that_affect_this_formula);
		most_specific_formula = simulation_formula;
		gensymed_symbol = Nil;
		goto end_1;
	    }
	}
	goto next_loop;
      end_loop:
	note_runtime_structure_in_things_that_affect_it(variable_or_parameter,
		Things_that_affect_this_formula,T);
	reclaim_eval_list_1(Things_that_affect_this_formula);
	gensymed_symbol = Qnil;
      end_1:;
	Current_computation_frame = old_star_current_computation_frame_star;
	Note_things_encountered_during_role_service_qm = 
		old_note_things_encountered_during_role_service_qm;
	Things_that_affect_this_formula = old_things_that_affect_this_formula;
	Current_computation_flags = old_current_computation_flags;
	return VALUES_2(most_specific_formula,focal_entity_qm);
    }
    else
	return VALUES_1(Nil);
}

/* GENERIC-SIMULATION-FORMULA-APPLIES-TO-THIS-VARIABLE? */
Object generic_simulation_formula_applies_to_this_variable_qm(generic_simulation_formula,
	    variable_or_parameter)
    Object generic_simulation_formula, variable_or_parameter;
{
    Object temp;

    x_note_fn_call(179,84);
    temp = ISVREF(generic_simulation_formula,(SI_Long)16L);
    return designation_denotes_item_p(SEVENTH(CAR(temp)),
	    variable_or_parameter);
}

/* PUT-SIMULATION-DETAILS */
Object put_simulation_details(variable,simulation_details,initializing_qm)
    Object variable, simulation_details, initializing_qm;
{
    x_note_fn_call(179,85);
    body_of_put_for_simulation_frame(variable,simulation_details,
	    initializing_qm);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qsimulation_details);
    return set_lookup_slot_value_1(variable,Qsimulation_details,
	    simulation_details);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qhistory_specification_for_simulation_subtables_qm;  /* history-specification-for-simulation-subtables? */

static Object Qparent_variable;    /* parent-variable */

/* BODY-OF-PUT-FOR-SIMULATION-FRAME */
Object body_of_put_for_simulation_frame(variable,simulation_details,
	    initializing_qm)
    Object variable, simulation_details, initializing_qm;
{
    Object old_value_qm, symbol, property_name, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, class_history_spec_for_simulation_subtables_qm, x2;
    Object simulation_info_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Object result;

    x_note_fn_call(179,86);
    if (simulation_details && ISVREF(simulation_details,(SI_Long)8L))
	add_to_frame_note_particulars_list_if_necessary(Qsimulation,
		Qproblem_with_sub_frame_of_variable,variable);
    else
	delete_from_frame_note_particulars_list(Qsimulation,
		Qproblem_with_sub_frame_of_variable,variable);
    if ( !TRUEP(Loading_kb_p) && simulation_details)
	add_as_inferior_block(simulation_details,variable);
    old_value_qm =  !TRUEP(initializing_qm) ? 
	    get_lookup_slot_value(variable,Qsimulation_details) : Nil;
    if ( !TRUEP(old_value_qm)) {
	if (simulation_details) {
	    symbol = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)1L);
	    property_name = Class_description_gkbprop;
	    skip_list = CDR(Symbol_properties_table);
	    key_value = symbol;
	    key_hash_value = SXHASH_SYMBOL_1(symbol) & 
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = symbol;
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
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
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
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = property_name;
		key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		key_value = property_name;
		key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    class_history_spec_for_simulation_subtables_qm = 
		    ISVREF(get_slot_description_of_class_description_function(Qhistory_specification_for_simulation_subtables_qm,
		    gensymed_symbol,Nil),(SI_Long)6L);
	    if (class_history_spec_for_simulation_subtables_qm)
		put_simulation_stored_history_specification_qm(simulation_details,
			copy_for_slot_value(class_history_spec_for_simulation_subtables_qm),
			T);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(simulation_details,Qparent_variable);
	    SVREF(simulation_details,FIX((SI_Long)22L)) = variable;
	}
    }
    else if ( !TRUEP(simulation_details)) {
	if (SIMPLE_VECTOR_P(old_value_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(old_value_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(old_value_qm,(SI_Long)1L);
	    temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3)
	    delete_frame(old_value_qm);
    }
    if (simulation_details && (SI_Long)0L != (IFIX(ISVREF(variable,
	    (SI_Long)5L)) & (SI_Long)1L)) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(simulation_details,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = simulation_details;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	temp_2 = simulation_details ? T : Nil;
	SVREF(simulation_info_qm,FIX((SI_Long)15L)) = temp_2;
    }
    return VALUES_1(simulation_details);
}

static Object Qsimulation_subtable_byte_code_body;  /* simulation-subtable-byte-code-body */

/* PUT-SIMULATION-SUBTABLE-BYTE-CODE-BODY */
Object put_simulation_subtable_byte_code_body(simulation_subtable,
	    new_byte_code_body,initializing_qm)
    Object simulation_subtable, new_byte_code_body, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,87);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(simulation_subtable)) && 
	    Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(simulation_subtable);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(simulation_subtable,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = nconc2(stack_change_list_2(simulation_subtable,
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
	M_CAR(gensymed_symbol_1) = simulation_subtable;
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
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(simulation_subtable,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(simulation_subtable,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = simulation_subtable;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(simulation_subtable,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(simulation_subtable,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(simulation_subtable,
		  Qsimulation_subtable_byte_code_body);
      result_1 = SVREF(simulation_subtable,FIX((SI_Long)23L)) = 
	      new_byte_code_body;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(simulation_subtable,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(simulation_subtable,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(simulation_subtable,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = simulation_subtable;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(simulation_subtable,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(simulation_subtable,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(simulation_subtable);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_byte_code_body);
}

static Object Qsimulation_subtable_initial_value_byte_code_body;  /* simulation-subtable-initial-value-byte-code-body */

/* PUT-SIMULATION-SUBTABLE-INITIAL-VALUE-BYTE-CODE-BODY */
Object put_simulation_subtable_initial_value_byte_code_body(simulation_subtable,
	    new_byte_code_body,initializing_qm)
    Object simulation_subtable, new_byte_code_body, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,88);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(simulation_subtable)) && 
	    Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(simulation_subtable);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(simulation_subtable,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = nconc2(stack_change_list_2(simulation_subtable,
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
	M_CAR(gensymed_symbol_1) = simulation_subtable;
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
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(simulation_subtable,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(simulation_subtable,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = simulation_subtable;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(simulation_subtable,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(simulation_subtable,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(simulation_subtable,
		  Qsimulation_subtable_initial_value_byte_code_body);
      result_1 = SVREF(simulation_subtable,FIX((SI_Long)24L)) = 
	      new_byte_code_body;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(simulation_subtable,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(simulation_subtable,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(simulation_subtable,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = simulation_subtable;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(simulation_subtable,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(simulation_subtable,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(simulation_subtable);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_byte_code_body);
}

/* VALID-SIMULATION-FORMULA-P */
Object valid_simulation_formula_p(simulation_formula)
    Object simulation_formula;
{
    Object info_without_text;

    x_note_fn_call(179,89);
    if (simulation_formula) {
	info_without_text = CAR(simulation_formula);
	if (info_without_text)
	    return VALUES_1( !EQ(info_without_text,No_value) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_subtable;  /* simulation-subtable */

static Object Qsimulation_formulas_qm;  /* simulation-formulas? */

/* CLEANUP-FOR-SIMULATION-SUBTABLE */
Object cleanup_for_simulation_subtable(simulation_subtable)
    Object simulation_subtable;
{
    Object frame, sub_vector_qm, method_function_qm, variable;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(179,90);
    frame = simulation_subtable;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qsimulation_subtable)) {
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
    variable = ISVREF(simulation_subtable,(SI_Long)22L);
    if (variable &&  !((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) 
	    & (SI_Long)512L))) {
	put_specific_simulation_formula_into_variable_or_parameter(variable,
		Nil);
	change_slot_value(3,variable,Qsimulation_details,Nil);
    }
    change_slot_value(3,simulation_subtable,Qsimulation_formulas_qm,Nil);
    change_slot_value(3,simulation_subtable,
	    Qsimulation_stored_history_specification_qm,Nil);
    change_slot_value(3,simulation_subtable,
	    Qsimulation_subtable_byte_code_body,Nil);
    return change_slot_value(3,simulation_subtable,
	    Qsimulation_subtable_initial_value_byte_code_body,Nil);
}

/* RECLAIM-SIMULATION-DETAILS-VALUE */
Object reclaim_simulation_details_value(simulation_subtable_qm,gensymed_symbol)
    Object simulation_subtable_qm, gensymed_symbol;
{
    x_note_fn_call(179,91);
    delete_frame(simulation_subtable_qm);
    return VALUES_1(Nil);
}

static Object Qnon_default_initial_simulated_value_qm;  /* non-default-initial-simulated-value? */

/* PUT-NON-DEFAULT-INITIAL-SIMULATED-VALUE? */
Object put_non_default_initial_simulated_value_qm(variable,
	    initial_simulated_value_qm,initializing_qm)
    Object variable, initial_simulated_value_qm, initializing_qm;
{
    x_note_fn_call(179,92);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,
		Qnon_default_initial_simulated_value_qm);
    set_lookup_slot_value_1(variable,
	    Qnon_default_initial_simulated_value_qm,
	    initial_simulated_value_qm);
    if ( !TRUEP(initializing_qm))
	change_slot_value(3,variable,Qsimulation_details,
		get_lookup_slot_value(variable,Qsimulation_details));
    return VALUES_1(initial_simulated_value_qm);
}

/* UPDATE-GENERIC-SIMULATION-FORMULA-FOR-VARIABLE-OR-PARAMETER */
Object update_generic_simulation_formula_for_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object formula_qm, focal_entity_qm;
    Object result;

    x_note_fn_call(179,93);
    result = generic_simulation_formula_for_variable_or_parameter(variable_or_parameter);
    MVS_2(result,formula_qm,focal_entity_qm);
    return put_generic_simulation_formula_into_variable_or_parameter(variable_or_parameter,
	    formula_qm,focal_entity_qm);
}

/* GET-OR-MAKE-SIMULATION-INFO */
Object get_or_make_simulation_info(variable_or_parameter,make_new_qm)
    Object variable_or_parameter, make_new_qm;
{
    Object temp, new_simulation_info, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(179,94);
    temp = get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    if (temp)
	return VALUES_1(temp);
    else if (make_new_qm) {
	new_simulation_info = make_simulation_info_1();
	SVREF(new_simulation_info,FIX((SI_Long)11L)) = variable_or_parameter;
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? TRUEP(get_lookup_slot_value(variable_or_parameter,
		Qsimulation_details)) : TRUEP(Nil))
	    SVREF(new_simulation_info,FIX((SI_Long)15L)) = T;
	return VALUES_1(new_simulation_info);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_model_install_qm, Qinhibit_model_install_qm);

/* PUT-GENERIC-SIMULATION-FORMULA-INTO-VARIABLE-OR-PARAMETER */
Object put_generic_simulation_formula_into_variable_or_parameter(variable_or_parameter,
	    generic_simulation_formula_qm,focal_entity_qm)
    Object variable_or_parameter, generic_simulation_formula_qm;
    Object focal_entity_qm;
{
    Object simulation_info_qm;

    x_note_fn_call(179,95);
    simulation_info_qm = get_or_make_simulation_info(variable_or_parameter,
	    generic_simulation_formula_qm);
    if (simulation_info_qm) {
	SVREF(simulation_info_qm,FIX((SI_Long)5L)) = 
		generic_simulation_formula_qm;
	SVREF(simulation_info_qm,FIX((SI_Long)14L)) = focal_entity_qm;
	change_slot_value(3,variable_or_parameter,Qsimulation_info_qm,
		simulation_info_qm);
	if ( !TRUEP(Inhibit_model_install_qm))
	    return install_item_in_model_if_models_used(variable_or_parameter);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-SPECIFIC-SIMULATION-FORMULA-INTO-VARIABLE-OR-PARAMETER */
Object put_specific_simulation_formula_into_variable_or_parameter(variable_or_parameter,
	    simulation_subtable_qm)
    Object variable_or_parameter, simulation_subtable_qm;
{
    Object simulation_info_qm;

    x_note_fn_call(179,96);
    simulation_info_qm = get_or_make_simulation_info(variable_or_parameter,
	    simulation_subtable_qm);
    if (simulation_info_qm) {
	SVREF(simulation_info_qm,FIX((SI_Long)6L)) = simulation_subtable_qm;
	change_slot_value(3,variable_or_parameter,Qsimulation_info_qm,
		simulation_info_qm);
	return install_item_in_model_if_models_used(variable_or_parameter);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-EXTERNAL-SIMULATION-FORMULA-INTO-VARIABLE-OR-PARAMETER */
Object put_external_simulation_formula_into_variable_or_parameter(variable_or_parameter,
	    external_simulation_definition_qm)
    Object variable_or_parameter, external_simulation_definition_qm;
{
    Object simulation_info_qm;

    x_note_fn_call(179,97);
    simulation_info_qm = get_or_make_simulation_info(variable_or_parameter,
	    external_simulation_definition_qm);
    if (simulation_info_qm) {
	SVREF(simulation_info_qm,FIX((SI_Long)7L)) = 
		external_simulation_definition_qm;
	change_slot_value(3,variable_or_parameter,Qsimulation_info_qm,
		simulation_info_qm);
	return install_item_in_model_if_models_used(variable_or_parameter);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmore_than_one_simulation_specifier_for_variable;  /* more-than-one-simulation-specifier-for-variable */

static Object string_constant_6;   /* "Installation problem:  variable-or-parameter ~NF has more than one simulation specifier" */

/* PUT-SIMULATION-INFO? */
Object put_simulation_info_qm(variable_or_parameter,simulation_info_qm,
	    initializing_qm)
    Object variable_or_parameter, simulation_info_qm, initializing_qm;
{
    Object old_simulation_info_qm, category, initial_value_qm;
    Object time_increment_qm, svref_new_value, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(179,98);
    old_simulation_info_qm =  !TRUEP(initializing_qm) ? 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil) : Nil;
    delete_frame_note_if_any(Qmore_than_one_simulation_specifier_for_variable,
	    variable_or_parameter);
    if ( !((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)5L)) 
	    & (SI_Long)512L)))
	update_frame_status(variable_or_parameter,Nil,Nil);
    if (simulation_info_qm) {
	if (ISVREF(simulation_info_qm,(SI_Long)5L) && 
		ISVREF(simulation_info_qm,(SI_Long)7L)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_6,
			variable_or_parameter);
	    Suppress_warning_message_header_qm = Nil;
	    add_to_frame_note_particulars_list_if_necessary(Nil,
		    Qmore_than_one_simulation_specifier_for_variable,
		    variable_or_parameter);
	    update_frame_status(variable_or_parameter,Qbad,Nil);
	}
	result = get_category_info_given_simulation_info(simulation_info_qm);
	MVS_3(result,category,initial_value_qm,time_increment_qm);
	if (category) {
	    reclaim_slot_value(ISVREF(simulation_info_qm,(SI_Long)4L));
	    reclaim_slot_value(ISVREF(simulation_info_qm,(SI_Long)3L));
	    set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qsimulation_info_qm,simulation_info_qm);
	    SVREF(simulation_info_qm,FIX((SI_Long)2L)) = category;
	    svref_new_value = copy_for_slot_value(initial_value_qm);
	    SVREF(simulation_info_qm,FIX((SI_Long)3L)) = svref_new_value;
	    svref_new_value = copy_for_slot_value(time_increment_qm);
	    SVREF(simulation_info_qm,FIX((SI_Long)4L)) = svref_new_value;
	    remove_variable_from_simulation(variable_or_parameter);
	    add_variable_to_simulation(variable_or_parameter);
	}
	else if (old_simulation_info_qm)
	    remove_simulation_info_from_variable_or_parameter(variable_or_parameter);
    }
    else if (old_simulation_info_qm)
	remove_simulation_info_from_variable_or_parameter(variable_or_parameter);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
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
    if (temp)
	change_slot_value(3,variable_or_parameter,Qsimulation_details,
		get_lookup_slot_value(variable_or_parameter,
		Qsimulation_details));
    return VALUES_2(Nil,T);
}

/* REMOVE-SIMULATION-INFO-FROM-VARIABLE-OR-PARAMETER */
Object remove_simulation_info_from_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object simulation_info_qm;

    x_note_fn_call(179,99);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	remove_variable_from_simulation(variable_or_parameter);
	reclaim_simulation_info_1(simulation_info_qm);
	return set_non_savable_lookup_slot_value(variable_or_parameter,
		Qsimulation_info_qm,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_10;   /* # */

/* WRITE-MORE-THAN-ONE-SIMULATION-SPECIFIER-FOR-VARIABLE-NOTE */
Object write_more_than_one_simulation_specifier_for_variable_note(dummy_for_particulars,
	    gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(179,100);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_10,
	    FIX((SI_Long)52L)));
    return VALUES_1(Nil);
}

static Object Quse_initial_value_expression_in_generic_simulation_formula;  /* use-initial-value-expression-in-generic-simulation-formula */

static Object Qexternal;           /* external */

/* GET-CATEGORY-INFO-GIVEN-SIMULATION-INFO */
Object get_category_info_given_simulation_info(simulation_info)
    Object simulation_info;
{
    Object simulation_subtable, temp, info_without_text, category;
    Object initial_value_qm, time_increment_qm, generic_formula_qm;

    x_note_fn_call(179,101);
    if (ISVREF(simulation_info,(SI_Long)6L)) {
	simulation_subtable = ISVREF(simulation_info,(SI_Long)6L);
	temp = ISVREF(simulation_subtable,(SI_Long)17L);
	info_without_text = CAR(temp);
	category = FIRST(info_without_text);
	initial_value_qm = THIRD(info_without_text);
	time_increment_qm = ISVREF(simulation_subtable,(SI_Long)16L);
	return VALUES_3(category,initial_value_qm,time_increment_qm);
    }
    else if (ISVREF(simulation_info,(SI_Long)5L)) {
	generic_formula_qm = ISVREF(simulation_info,(SI_Long)5L);
	temp = ISVREF(generic_formula_qm,(SI_Long)16L);
	initial_value_qm = FIFTH(CAR(temp));
	temp = ISVREF(generic_formula_qm,(SI_Long)16L);
	time_increment_qm = SIXTH(CAR(temp));
	temp = ISVREF(generic_formula_qm,(SI_Long)16L);
	temp = CAR(temp);
	return VALUES_3(FOURTH(temp),CONSP(initial_value_qm) ? 
		Quse_initial_value_expression_in_generic_simulation_formula 
		: initial_value_qm,time_increment_qm);
    }
    else if (ISVREF(simulation_info,(SI_Long)7L))
	return VALUES_3(Qexternal,Nil,Nil);
    else
	return VALUES_1(Qnil);
}

/* GET-SIMULATION-SPECIFIER-TO-USE */
Object get_simulation_specifier_to_use(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(179,102);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	temp = ISVREF(simulation_info_qm,(SI_Long)6L);
	if (temp);
	else
	    temp = ISVREF(simulation_info_qm,(SI_Long)5L);
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(ISVREF(simulation_info_qm,(SI_Long)7L));
    }
    else
	return VALUES_1(Nil);
}

/* GET-FORMULA-FOCAL-ENTITY-FOR-VARIABLE */
Object get_formula_focal_entity_for_variable(variable)
    Object variable;
{
    Object simulation_info_qm;

    x_note_fn_call(179,103);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm)
	return VALUES_1(ISVREF(simulation_info_qm,(SI_Long)14L));
    else
	return VALUES_1(Nil);
}

/* PUT-SIMULATION-FORMULAS? */
Object put_simulation_formulas_qm(simulation_subtable,formulas_and_info_qm,
	    initializing_qm)
    Object simulation_subtable, formulas_and_info_qm, initializing_qm;
{
    Object car_new_value, variable_qm, info_without_text;
    Object simulation_expression_qm;

    x_note_fn_call(179,104);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(simulation_subtable)) && 
	    Loading_kb_p) {
	reclaim_slot_value(CAR(formulas_and_info_qm));
	car_new_value = No_value;
	M_CAR(formulas_and_info_qm) = car_new_value;
	note_frame_with_compilation_removed(simulation_subtable);
	update_frame_status(simulation_subtable,Qincomplete,initializing_qm);
    }
    variable_qm = ISVREF(simulation_subtable,(SI_Long)22L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_subtable,Qsimulation_formulas_qm);
    SVREF(simulation_subtable,FIX((SI_Long)17L)) = formulas_and_info_qm;
    info_without_text = CAR(formulas_and_info_qm);
    simulation_expression_qm = SECOND(info_without_text);
    if (variable_qm) {
	if ( !TRUEP(simulation_expression_qm))
	    put_specific_simulation_formula_into_variable_or_parameter(variable_qm,
		    Nil);
	else
	    put_specific_simulation_formula_into_variable_or_parameter(variable_qm,
		    simulation_subtable);
	update_runtime_structures_according_to_edit(1,variable_qm);
    }
    return VALUES_1(ISVREF(simulation_subtable,(SI_Long)17L));
}

/* PUT-PARENT-VARIABLE */
Object put_parent_variable(simulation_subtable,parent_variable,gensymed_symbol)
    Object simulation_subtable, parent_variable, gensymed_symbol;
{
    x_note_fn_call(179,105);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_subtable,Qparent_variable);
    SVREF(simulation_subtable,FIX((SI_Long)22L)) = parent_variable;
    return change_slot_value(3,simulation_subtable,Qsimulation_formulas_qm,
	    ISVREF(simulation_subtable,(SI_Long)17L));
}

static Object Qconnection_style;   /* connection-style */

static Object Qorthogonal;         /* orthogonal */

static Object Qws_representation;  /* ws-representation */

static Object Qsocket;             /* socket */

static Object Qattribute_name;     /* attribute-name */

static Object Qnew_value;          /* new-value */

static Object Qitem_change;        /* item-change */

static Object Qab_structure;       /* structure */

/* PUT-CONNECTION-STYLE */
Object put_connection_style(connection,value,initializing_qm)
    Object connection, value, initializing_qm;
{
    Object connection_for_connection_frame, output_end_object_qm;
    Object gensymed_symbol, workspace_qm, notification_data_version_map, x2;
    Object sub_class_bit_vector, connection_qm, temp_1, any_body_evaluated_p;
    Object frame_list, class_name, new_list, frame, ab_loop_list_;
    Object representations, current_frame_serial_number_on_entry;
    Object representation, xa, ya, version_for_current, evaluatedp, address;
    Object socket_1, representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_2, item_or_value;
    Object svref_new_value, arg_lists, arg_list, ab_loop_list__1;
    Object arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,106);
    SAVE_STACK();
    set_non_savable_lookup_slot_value(connection,Qconnection_style,value);
    if ( !TRUEP(initializing_qm)) {
	connection_for_connection_frame = ISVREF(connection,(SI_Long)21L);
	output_end_object_qm = ISVREF(connection_for_connection_frame,
		(SI_Long)2L);
	if (output_end_object_qm) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object_qm,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    workspace_qm = gensymed_symbol;
	}
	else
	    workspace_qm = Nil;
	update_connection_images(T,workspace_qm,
		connection_for_connection_frame);
	if (EQ(value,Qorthogonal))
	    change_connection_attribute(connection_for_connection_frame,
		    Qconnection_style,Nil);
	else
	    change_connection_attribute(connection_for_connection_frame,
		    Qconnection_style,value);
	if (G2_has_v5_mode_windows_p &&  
		!TRUEP(Ws_protocol_handle_moves_from_edge_change_p)) {
	    LOCK(Javalink_notification_versions);
	    if (PUSH_UNWIND_PROTECT(1)) {
		notification_data_version_map = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
			1);
		  if (SIMPLE_VECTOR_P(connection_for_connection_frame) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_for_connection_frame)) 
			  > (SI_Long)2L &&  
			  !EQ(ISVREF(connection_for_connection_frame,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(connection_for_connection_frame,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(connection_for_connection_frame,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
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
		      if (temp) {
			  connection_qm = 
				  ISVREF(connection_for_connection_frame,
				  (SI_Long)21L);
			  temp_1 = workspace_of_connection_qm(connection_qm);
		      }
		      else
			  temp_1 = 
				  get_workspace_if_any(connection_for_connection_frame);
		  }
		  else if (SIMPLE_VECTOR_P(connection_for_connection_frame) 
			  && EQ(ISVREF(connection_for_connection_frame,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_connection_g2_struct))
		      temp_1 = 
			      workspace_of_connection_qm(connection_for_connection_frame);
		  else
		      temp_1 = Qnil;
		  if (temp_1) {
		      if (SIMPLE_VECTOR_P(connection_for_connection_frame) 
			      && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_for_connection_frame)) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(connection_for_connection_frame,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(connection_for_connection_frame,
				  (SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  sub_class_bit_vector = 
				  ISVREF(ISVREF(connection_for_connection_frame,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Connection_class_description,
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
			      connection_qm = 
				      ISVREF(connection_for_connection_frame,
				      (SI_Long)21L);
			      temp_1 = 
				      workspace_of_connection_qm(connection_qm);
			  }
			  else
			      temp_1 = 
				      get_workspace_if_any(connection_for_connection_frame);
		      }
		      else if (SIMPLE_VECTOR_P(connection_for_connection_frame) 
			      && EQ(ISVREF(connection_for_connection_frame,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_connection_g2_struct))
			  temp_1 = 
				  workspace_of_connection_qm(connection_for_connection_frame);
		      else
			  temp_1 = Qnil;
		      temp = TRUEP(v5_tw_item_like_p(temp_1));
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      any_body_evaluated_p = Nil;
		      if (SIMPLE_VECTOR_P(connection_for_connection_frame) 
			      && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_for_connection_frame)) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(connection_for_connection_frame,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(connection_for_connection_frame,
				  (SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  sub_class_bit_vector = 
				  ISVREF(ISVREF(connection_for_connection_frame,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Connection_class_description,
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
			      connection_qm = 
				      ISVREF(connection_for_connection_frame,
				      (SI_Long)21L);
			      temp_1 = 
				      workspace_of_connection_qm(connection_qm);
			  }
			  else
			      temp_1 = 
				      get_workspace_if_any(connection_for_connection_frame);
		      }
		      else if (SIMPLE_VECTOR_P(connection_for_connection_frame) 
			      && EQ(ISVREF(connection_for_connection_frame,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_connection_g2_struct))
			  temp_1 = 
				  workspace_of_connection_qm(connection_for_connection_frame);
		      else
			  temp_1 = Qnil;
		      frame_list = ISVREF(temp_1,(SI_Long)9L);
		      class_name = Qws_representation;
		      new_list = Qnil;
		      frame = Nil;
		      ab_loop_list_ = frame_list;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      frame = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      gensymed_symbol = 
			      lookup_global_or_kb_specific_property_value(class_name,
			      Class_description_gkbprop);
		      if (gensymed_symbol) {
			  sub_class_bit_vector = ISVREF(ISVREF(frame,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  new_list = gensym_cons_1(frame,new_list);
		      goto next_loop;
		    end_loop:
		      representations = new_list;
		      goto end_1;
		      representations = Qnil;
		    end_1:;
		      current_frame_serial_number_on_entry = 
			      copy_frame_serial_number(Current_frame_serial_number);
		      representation = Nil;
		      ab_loop_list_ = representations;
		    next_loop_1:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_1;
		      representation = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		      temp = SIMPLE_VECTOR_P(representation) ? 
			      EQ(ISVREF(representation,(SI_Long)1L),
			      Qavailable_frame_vector) : TRUEP(Qnil);
		      if (temp);
		      else
			  temp = FIXNUMP(gensymed_symbol) ? 
				  IFIX(gensymed_symbol) == (SI_Long)-1L : 
				  TRUEP(Nil);
		      if (temp);
		      else if (FIXNUMP(current_frame_serial_number_on_entry))
			  temp = FIXNUMP(gensymed_symbol) ? 
				  FIXNUM_LT(current_frame_serial_number_on_entry,
				  gensymed_symbol) : TRUEP(T);
		      else if (FIXNUMP(gensymed_symbol))
			  temp = TRUEP(Nil);
		      else {
			  xa = M_CAR(current_frame_serial_number_on_entry);
			  ya = M_CAR(gensymed_symbol);
			  temp = FIXNUM_LT(xa,ya);
			  if (temp);
			  else
			      temp = FIXNUM_EQ(xa,ya) ? 
				      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
				      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		      }
		      if ( !temp ? 
			      TRUEP(representation_address_valid_p(representation)) 
			      : TRUEP(Nil)) {
			  if ( !TRUEP(Notification_data_version_map))
			      Notification_data_version_map = 
				      gensym_cons_1(T,Nil);
			  version_for_current = Nil;
			  evaluatedp = Nil;
			  address = ISVREF(representation,(SI_Long)8L);
			  socket_1 = getf(address,Qsocket,_);
			  representation_version = 
				  remote_icp_protocol_version(socket_1);
			  subscription_handle = ISVREF(representation,
				  (SI_Long)12L);
			  current_list = Notification_data_version_map;
			  version_or_data = Nil;
			next_loop_2:
			  version_or_data = CAR(current_list);
			  if ( !TRUEP(version_or_data))
			      goto end_2;
			  version_for_current = 
				  javalink_versioned_call_data_get_version(version_or_data);
			  evaluatedp = 
				  javalink_versioned_call_data_evaluated_p(version_or_data);
			  if (EQ(version_for_current,T) || 
				  FIXNUM_GE(representation_version,
				  version_for_current)) {
			      if ( !TRUEP(evaluatedp)) {
				  LOCK(Javalink_notification_versions);
				  if (PUSH_UNWIND_PROTECT(0)) {
				      current_lookup_data = 
					      make_javalink_versioned_data(version_or_data);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
					      0);
					gensymed_symbol = 
						allocate_managed_array(1,
						FIX((SI_Long)4L + 
						(SI_Long)1L));
					gensymed_symbol_1 = (SI_Long)0L;
					if (FIXNUM_LE(ISVREF(gensymed_symbol,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    svref_arg_2 = 
						    gensymed_symbol_1 + 
						    IFIX(Managed_array_index_offset);
					    ISVREF(gensymed_symbol,
						    svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol,
						    (gensymed_symbol_1 >>  
						    -  - (SI_Long)10L) + 
						    (SI_Long)2L);
					    svref_arg_2 = 
						    gensymed_symbol_1 & 
						    (SI_Long)1023L;
					    ISVREF(temp_2,svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol,
						(SI_Long)1L),
						Maximum_in_place_array_size))
					    SVREF(gensymed_symbol,
						    FIX((SI_Long)3L)) = 
						    Qattribute_name;
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)2L);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = Qattribute_name;
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    item_or_value = Qconnection_style;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    temp_2 = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(gensymed_symbol,
						    FIX((SI_Long)4L)) = temp_2;
					}
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)2L);
					    item_or_value = Qconnection_style;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    svref_new_value = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(temp_2,FIX((SI_Long)2L)) 
						    = svref_new_value;
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol,
						(SI_Long)1L),
						Maximum_in_place_array_size))
					    SVREF(gensymed_symbol,
						    FIX((SI_Long)5L)) = 
						    Qnew_value;
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)2L);
					    SVREF(temp_2,FIX((SI_Long)3L)) 
						    = Qnew_value;
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    item_or_value = value;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    temp_2 = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(gensymed_symbol,
						    FIX((SI_Long)6L)) = temp_2;
					}
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)2L);
					    item_or_value = value;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    svref_new_value = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(temp_2,FIX((SI_Long)4L)) 
						    = svref_new_value;
					}
					send_versioned_ws_notification_internal(Qitem_change,
						connection_for_connection_frame,
						eval_cons_1(gensymed_symbol,
						Qab_structure));
					temp_1 = Current_lookup_data;
				      POP_SPECIAL();
				      SAVE_VALUES(VALUES_1(temp_1));
				  }
				  POP_UNWIND_PROTECT(0);
				  UNLOCK(Javalink_notification_versions);
				  CONTINUE_UNWINDING(0);
				  result = RESTORE_VALUES();
				  version_or_data = result;
				  M_CAR(current_list) = version_or_data;
			      }
			      if (javalink_versioned_call_data_sendp(version_or_data)) 
					  {
				  arg_lists = ISVREF(version_or_data,
					  (SI_Long)2L);
				  arg_list = Nil;
				  ab_loop_list__1 = arg_lists;
				  arg_list_to_send = Nil;
				next_loop_3:
				  if ( !TRUEP(ab_loop_list__1))
				      goto end_loop_2;
				  arg_list = M_CAR(ab_loop_list__1);
				  ab_loop_list__1 = M_CDR(ab_loop_list__1);
				  arg_list_to_send = 
					  javalink_versioning_make_arg_list_copy(arg_list,
					  subscription_handle);
				  callback_representation_fire_callback(representation,
					  socket_1,arg_list_to_send);
				  goto next_loop_3;
				end_loop_2:;
			      }
			      goto end_2;
			  }
			  current_list = CDR(current_list);
			  goto next_loop_2;
			end_loop_3:
			end_2:;
		      }
		      goto next_loop_1;
		    end_loop_1:
		      reclaim_gensym_list_1(representations);
		      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
		      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
		      goto end_3;
		    end_3:;
		  }
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(1);
	    UNLOCK(Javalink_notification_versions);
	    CONTINUE_UNWINDING(1);
	    send_ws_representations_connection_moved(connection_for_connection_frame);
	}
	update_connection_images(Nil,workspace_qm,
		connection_for_connection_frame);
    }
    RESTORE_STACK();
    return VALUES_1(value);
}

/* ADD-OR-DELETE-SUBWORKSPACE-CONNECTION-POST */
Object add_or_delete_subworkspace_connection_post(connection_post_set,
	    connection_post,delete_instead_qm)
    Object connection_post_set, connection_post, delete_instead_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    Object svref_arg_2, new_cons, svref_new_value;

    x_note_fn_call(179,107);
    if (delete_instead_qm) {
	gensymed_symbol = connection_post;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = connection_post_set;
      next_loop:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else
		connection_post_set = CDR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    goto end_1;
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop;
      end_loop:
      end_1:;
    }
    else {
	gensymed_symbol = connection_post_set;
	gensymed_symbol_1 = connection_post;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_slot_value_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qab_slot_value);
	    connection_post_set = gensymed_symbol_2;
	}
    }
    return VALUES_1(connection_post_set);
}

static Object Qconnection_post;    /* connection-post */

/* INSTALL-CONNECTION-POSTS-AFTER-LOADING-1 */
Object install_connection_posts_after_loading_1()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, connection_post;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,108);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    connection_post = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qconnection_post);
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
      connection_post = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      handle_connection_post_addition_or_removal_as_subblock_1(connection_post,
	      Nil);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_kb_loading_consistency_analysis, Qpost_kb_loading_consistency_analysis);

static Object Qinstallation;       /* installation */

/* RECLAIM-INSTALLATION-LIST-FUNCTION */
Object reclaim_installation_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, temp, svref_arg_2;

    x_note_fn_call(179,109);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qinstallation);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qinstallation);
	if (ISVREF(Available_installation_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = list_1;
	    temp = Available_installation_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
	    temp = Available_installation_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Compiled_items_referring_to_this_name_kbprop = UNBOUND;

/* COMPILED-ITEMS-REFERRING-TO-THIS-NAME-FUNCTION */
Object compiled_items_referring_to_this_name_function(name)
    Object name;
{
    x_note_fn_call(179,110);
    return lookup_kb_specific_property_value(name,
	    Compiled_items_referring_to_this_name_kbprop);
}

static Object Qundefined_classes;  /* undefined-classes */

/* DO-CONSISTENCY-ANALYSIS-WORK-ON-SUBFRAME-OVERRIDES */
Object do_consistency_analysis_work_on_subframe_overrides(class_definition,
	    class_of_subframe)
    Object class_definition, class_of_subframe;
{
    Object gensymed_symbol, gensymed_symbol_1, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_2;

    x_note_fn_call(179,111);
    gensymed_symbol = lookup_kb_specific_property_value(class_of_subframe,
	    Compiled_items_referring_to_this_name_kbprop);
    gensymed_symbol_1 = class_definition;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_installation_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qinstallation);
	mutate_kb_specific_property_value(class_of_subframe,
		gensymed_symbol_2,
		Compiled_items_referring_to_this_name_kbprop);
    }
    return add_to_frame_note_particulars_list_if_necessary(class_of_subframe,
	    Qundefined_classes,class_definition);
}

DEFINE_VARIABLE_WITH_SYMBOL(Analyze_for_consistency_in_progress, Qanalyze_for_consistency_in_progress);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_types_to_be_analyzed, Qlist_of_types_to_be_analyzed);

Object Stack_compiler_frame_note_type_p_prop = UNBOUND;

Object List_of_stack_compiler_frame_note_types = UNBOUND;

Object Consistency_analysis_frame_note_type_p_prop = UNBOUND;

Object List_of_consistency_analysis_frame_note_types = UNBOUND;

/* DELETE-ALL-CONSISTENCY-ANALYSIS-FRAME-NOTES */
Object delete_all_consistency_analysis_frame_notes varargs_1(int, n)
{
    Object compiled_item;
    Object delete_only_from_component_particulars_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(179,112);
    INIT_ARGS_nonrelocating();
    compiled_item = REQUIRED_ARG_nonrelocating();
    delete_only_from_component_particulars_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    return delete_frame_notes_of_types_in_list(compiled_item,
	    List_of_consistency_analysis_frame_note_types,
	    delete_only_from_component_particulars_qm);
}

/* POST-ANALYZER-WARNING-NOTE-FOR-GENERIC-SIMULATION-FORMULA */
Object post_analyzer_warning_note_for_generic_simulation_formula(generic_simulation_formula)
    Object generic_simulation_formula;
{
    Object add_as_item_referring_to_name_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,113);
    if (Post_analyzer_warning_notes_for_generic_simulation_formulas_qm) {
	add_as_item_referring_to_name_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
		0);
	  result = post_analyzer_warning_note_if_necessary(generic_simulation_formula);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qstack_compiler_frame_note_type_p;  /* stack-compiler-frame-note-type-p */

static Object Qconsistency_analysis_frame_note_type_p;  /* consistency-analysis-frame-note-type-p */

/* SCAN-COMPONENT-FRAME-NOTES-FOR-WARNING-CRITERIA */
Object scan_component_frame_notes_for_warning_criteria(component_structure)
    Object component_structure;
{
    Object compiler_error_qm, analyzer_warning_qm, key, frame_status_and_notes;
    Object ab_loop_list_, ab_loop_desetq_, temp, note_type, particulars;
    Object ab_loop_list__1;
    char temp_1;

    x_note_fn_call(179,114);
    compiler_error_qm = Nil;
    analyzer_warning_qm = Nil;
    key = Nil;
    frame_status_and_notes = Nil;
    ab_loop_list_ = component_structure;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    frame_status_and_notes = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    note_type = Nil;
    particulars = Nil;
    ab_loop_list__1 = CDR(frame_status_and_notes);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
  next_loop_1:
    note_type = CAR(ab_loop_list__1);
    temp = CDR(ab_loop_list__1);
    particulars = CAR(temp);
    if ( !TRUEP(compiler_error_qm)) {
	if (EQ(note_type,Qcompiler_errors)) {
	    compiler_error_qm = T;
	    if (analyzer_warning_qm)
		goto end_component_notes_scan;
	    temp_1 = TRUEP(T);
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1) {
	if ( !TRUEP(analyzer_warning_qm)) {
	    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(note_type),
		    Qstack_compiler_frame_note_type_p) || 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(note_type),
		    Qconsistency_analysis_frame_note_type_p)) {
		analyzer_warning_qm = T;
		if (compiler_error_qm)
		    goto end_component_notes_scan;
	    }
	}
    }
    ab_loop_list__1 = CDDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
  end_component_notes_scan:
    return VALUES_2(compiler_error_qm,analyzer_warning_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_analyzer_warning_note_qm, Qpost_analyzer_warning_note_qm);

static Object Qframe_notes_for_component_particulars;  /* frame-notes-for-component-particulars */

/* POST-ANALYZER-WARNING-NOTE-IF-NECESSARY */
Object post_analyzer_warning_note_if_necessary(compiled_item)
    Object compiled_item;
{
    Object temp, compiler_error_qm, analyzer_warning_qm, note_type;
    Object particulars, ab_loop_list_, current_computation_frame;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,115);
    if (Add_as_item_referring_to_name_qm) {
	temp = ISVREF(compiled_item,(SI_Long)8L);
	temp_1 = TRUEP(CDR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(Suppress_consistency_analysis_warnings_notes_qm) :
	     TRUEP(Nil)) {
	compiler_error_qm = Nil;
	analyzer_warning_qm = Nil;
	note_type = Nil;
	particulars = Nil;
	temp = ISVREF(compiled_item,(SI_Long)8L);
	ab_loop_list_ = CDR(temp);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	note_type = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	particulars = CAR(temp);
	if (EQ(note_type,Qframe_notes_for_component_particulars)) {
	    result = scan_component_frame_notes_for_warning_criteria(particulars);
	    MVS_2(result,compiler_error_qm,analyzer_warning_qm);
	    if (compiler_error_qm && analyzer_warning_qm)
		goto end_1;
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1) {
	    if ( !TRUEP(compiler_error_qm)) {
		if (EQ(note_type,Qcompiler_errors)) {
		    compiler_error_qm = T;
		    if (analyzer_warning_qm)
			goto end_look_for_notes_that_prompt_a_warning;
		    temp_1 = TRUEP(T);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		if ( !TRUEP(analyzer_warning_qm)) {
		    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(note_type),
			    Qstack_compiler_frame_note_type_p) || 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(note_type),
			    Qconsistency_analysis_frame_note_type_p)) {
			analyzer_warning_qm = T;
			if (compiler_error_qm)
			    goto end_look_for_notes_that_prompt_a_warning;
		    }
		}
	    }
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
      end_1:;
      end_look_for_notes_that_prompt_a_warning:
	if (compiler_error_qm && analyzer_warning_qm)
	    post_compiler_and_analyzer_warning_note(compiled_item);
	else if (compiler_error_qm) {
	    current_computation_frame = compiled_item;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    0);
	      post_compiler_warning_note();
	    POP_SPECIAL();
	}
	else if (analyzer_warning_qm) {
	    if (Collecting_procedures_to_warn_about_p) {
		temp = gensym_cons_1(compiled_item,
			copy_frame_serial_number(ISVREF(compiled_item,
			(SI_Long)3L)));
		Procedures_to_warn_about_p = gensym_cons_1(temp,
			Procedures_to_warn_about_p);
	    }
	    else
		post_analyzer_warning_note(compiled_item);
	}
    }
    return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qcompiler_and_analyzer;  /* compiler-and-analyzer */

static Object string_constant_7;   /* "There were problems compiling the following-items, which have inconsistencies: " */

static Object Qanalyzer;           /* analyzer */

static Object string_constant_8;   /* "Inconsistencies were detected in the following items: " */

static Object Qcompiler;           /* compiler */

static Object string_constant_9;   /* "There were problems compiling the following items: " */

static Object Qstring_lt_w;        /* string<w */

static Object Qget_or_make_up_designation_for_block;  /* get-or-make-up-designation-for-block */

static Object string_constant_10;  /* "~NF" */

static Object string_constant_11;  /* "; see their notes for details." */

/* POST-COLLECTED-WARNINGS */
Object post_collected_warnings(collected_items_with_warnings_alist)
    Object collected_items_with_warnings_alist;
{
    Object a, ab_loop_list_, message_type, item_list;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, length_2, firstp, item, ab_loop_list__1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    Declare_special(8);
    Object result;

    x_note_fn_call(179,116);
    PUSH_SPECIAL_WITH_SYMBOL(Collected_items_with_warnings_alist,Qcollected_items_with_warnings_alist,collected_items_with_warnings_alist,
	    7);
      a = Nil;
      ab_loop_list_ = Collected_items_with_warnings_alist;
      message_type = Nil;
      item_list = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      a = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      message_type = CAR(a);
      item_list = CDR(a);
      if ( !TRUEP(CDR(item_list)))
	  post_warning_note(CAR(item_list),message_type);
      else {
	  snapshots_of_related_blocks = Nil;
	  note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			if (EQ(message_type,Qcompiler_and_analyzer))
			    temp = string_constant_7;
			else if (EQ(message_type,Qanalyzer))
			    temp = string_constant_8;
			else if (EQ(message_type,Qcompiler))
			    temp = string_constant_9;
			else
			    temp = Qnil;
			tformat(1,temp);
			item_list = sort_list(item_list,
				SYMBOL_FUNCTION(Qstring_lt_w),
				SYMBOL_FUNCTION(Qget_or_make_up_designation_for_block));
			M_CDR(a) = item_list;
			length_2 = length(item_list);
			firstp = T;
			i = (SI_Long)1L;
			item = Nil;
			ab_loop_list__1 = item_list;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_1;
			item = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			if ( !TRUEP(firstp)) {
			    if (i < IFIX(length_2))
				tformat(1,string_constant_3);
			    else if (IFIX(length_2) == (SI_Long)2L)
				tformat(1,string_constant_5);
			    else
				tformat(1,string_constant_4);
			}
			tformat(2,string_constant_10,item);
			firstp = Nil;
			i = i + (SI_Long)1L;
			goto next_loop_1;
		      end_loop_1:;
			tformat(1,string_constant_11);
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
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_12;  /* "There were problems compiling ~NF, and it has inconsistencies" */

static Object string_constant_13;  /* "Inconsistencies were detected in ~NF" */

static Object string_constant_14;  /* "There were problems compiling ~NF" */

static Object string_constant_15;  /* ": " */

static Object string_constant_16;  /* "; see its notes for details." */

/* DO-TW-NOTIFICATION */
Object do_tw_notification(compiled_item,message_type)
    Object compiled_item, message_type;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(179,117);
    SAVE_STACK();
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
	      5);
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
		  if (EQ(message_type,Qcompiler_and_analyzer))
		      temp = string_constant_12;
		  else if (EQ(message_type,Qanalyzer))
		      temp = string_constant_13;
		  else if (EQ(message_type,Qcompiler))
		      temp = string_constant_14;
		  else
		      temp = Qnil;
		  tformat(2,temp,compiled_item);
		  if (Send_logbook_messages_to_console_p || 
			  Current_computation_instance) {
		      tformat(1,string_constant_15);
		      twrite_frame_notes(compiled_item,T);
		  }
		  else
		      tformat(1,string_constant_16);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SAVE_VALUES(notify_user_1(temp));
	if (Snapshots_of_related_blocks) {
	    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	    Snapshots_of_related_blocks = Nil;
	}
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* POST-WARNING-NOTE */
Object post_warning_note(compiled_item,message_type)
    Object compiled_item, message_type;
{
    x_note_fn_call(179,118);
    if (Collecting_warnings_p &&  !TRUEP(Send_logbook_messages_to_console_p))
	return collect_warning(compiled_item,message_type);
    else
	return do_tw_notification(compiled_item,message_type);
}

/* POST-COMPILER-AND-ANALYZER-WARNING-NOTE */
Object post_compiler_and_analyzer_warning_note(compiled_item)
    Object compiled_item;
{
    x_note_fn_call(179,119);
    if (Post_analyzer_warning_note_qm || Post_compiler_warning_note_qm)
	return post_warning_note(compiled_item,Qcompiler_and_analyzer);
    else
	return VALUES_1(Nil);
}

/* POST-ANALYZER-WARNING-NOTE */
Object post_analyzer_warning_note(compiled_item)
    Object compiled_item;
{
    x_note_fn_call(179,120);
    if (Post_analyzer_warning_note_qm)
	return post_warning_note(compiled_item,Qanalyzer);
    else
	return VALUES_1(Nil);
}

/* POST-COMPILER-WARNING-NOTE */
Object post_compiler_warning_note()
{
    x_note_fn_call(179,121);
    if (Post_compiler_warning_note_qm)
	return post_warning_note(Current_computation_frame,Qcompiler);
    else
	return VALUES_1(Nil);
}

static Object string_constant_17;  /* "the item " */

static Object string_constant_18;  /* "the items " */

static Object string_constant_19;  /* " does not exist" */

static Object string_constant_20;  /* " do not exist" */

/* WRITE-NON-EXISTENT-INSTANCES-NOTE */
Object write_non_existent_instances_note(non_existent_instance_names,
	    gensymed_symbol)
    Object non_existent_instance_names, gensymed_symbol;
{
    x_note_fn_call(179,122);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(non_existent_instance_names,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20));
    return VALUES_1(Nil);
}

static Object string_constant_21;  /* "the class " */

static Object string_constant_22;  /* "the classes " */

static Object string_constant_23;  /* " is not defined" */

static Object string_constant_24;  /* " are not defined" */

/* WRITE-UNDEFINED-CLASSES-NOTE */
Object write_undefined_classes_note(undefined_classes,gensymed_symbol)
    Object undefined_classes, gensymed_symbol;
{
    x_note_fn_call(179,123);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(undefined_classes,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24));
    return VALUES_1(Nil);
}

Object Frame_note_for_superseded_attributes_1 = UNBOUND;

static Object string_constant_25;  /* "the attribute " */

static Object string_constant_26;  /* "the attributes " */

/* WRITE-UNDEFINED-ATTRIBUTES-NOTE */
Object write_undefined_attributes_note(undefined_attributes,gensymed_symbol)
    Object undefined_attributes, gensymed_symbol;
{
    x_note_fn_call(179,124);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(undefined_attributes,
	    string_constant_25,string_constant_26,string_constant_23,
	    string_constant_24));
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

/* WRITE-UNDEFINED-ATTRIBUTES-OF-CLASSES-NOTE */
Object write_undefined_attributes_of_classes_note(undefined_attributes_and_classes,
	    gensymed_symbol)
    Object undefined_attributes_and_classes, gensymed_symbol;
{
    Object ab_loop_destructure_, class_and_attributes, rest_of_class_entries;
    Object temp;

    x_note_fn_call(179,125);
    ab_loop_destructure_ = undefined_attributes_and_classes;
    class_and_attributes = Nil;
    rest_of_class_entries = Nil;
    class_and_attributes = CAR(ab_loop_destructure_);
    rest_of_class_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(CDR(class_and_attributes),
	    string_constant_25,string_constant_26,string_constant_23,
	    string_constant_24);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)15L));
    twrite(CAR(class_and_attributes));
    if ( !TRUEP(rest_of_class_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)2L));
    class_and_attributes = CAR(rest_of_class_entries);
    rest_of_class_entries = CDR(rest_of_class_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_27;  /* "the method " */

static Object string_constant_28;  /* "the methods" */

/* WRITE-UNDEFINED-METHODS-OF-CLASSES-NOTE */
Object write_undefined_methods_of_classes_note(undefined_methods_and_classes,
	    gensymed_symbol)
    Object undefined_methods_and_classes, gensymed_symbol;
{
    Object ab_loop_destructure_, class_and_methods, rest_of_class_entries;
    Object temp;

    x_note_fn_call(179,126);
    ab_loop_destructure_ = undefined_methods_and_classes;
    class_and_methods = Nil;
    rest_of_class_entries = Nil;
    class_and_methods = CAR(ab_loop_destructure_);
    rest_of_class_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(CDR(class_and_methods),string_constant_27,
	    string_constant_28,string_constant_23,string_constant_24);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)15L));
    twrite(CAR(class_and_methods));
    if ( !TRUEP(rest_of_class_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)2L));
    class_and_methods = CAR(rest_of_class_entries);
    rest_of_class_entries = CDR(rest_of_class_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_29;  /* "the name " */

static Object string_constant_30;  /* "the names " */

static Object string_constant_31;  /* " does not exist as an instance of the class " */

static Object string_constant_32;  /* " do not exist as instances of the class " */

/* WRITE-NON-EXISTENT-INSTANCES-OF-CLASS-NOTE */
Object write_non_existent_instances_of_class_note(undefined_instances_of_classes,
	    gensymed_symbol)
    Object undefined_instances_of_classes, gensymed_symbol;
{
    Object ab_loop_destructure_, class_1, names, rest_of_entries, temp;

    x_note_fn_call(179,127);
    ab_loop_destructure_ = undefined_instances_of_classes;
    class_1 = Nil;
    names = Nil;
    rest_of_entries = Nil;
    temp = CAR(ab_loop_destructure_);
    class_1 = CAR(temp);
    temp = CAR(ab_loop_destructure_);
    names = CDR(temp);
    rest_of_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(names,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32);
    twrite(class_1);
    if ( !TRUEP(rest_of_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)2L));
    temp = CAR(rest_of_entries);
    class_1 = CAR(temp);
    temp = CAR(rest_of_entries);
    names = CDR(temp);
    rest_of_entries = CDR(rest_of_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_33;  /* " does not exist as an instance of the type " */

static Object string_constant_34;  /* " do not exist as instances of the type " */

/* WRITE-NON-EXISTENT-INSTANCES-OF-TYPE-NOTE */
Object write_non_existent_instances_of_type_note(undefined_instances_of_types,
	    gensymed_symbol)
    Object undefined_instances_of_types, gensymed_symbol;
{
    Object ab_loop_destructure_, type, names, rest_of_entries, temp;

    x_note_fn_call(179,128);
    ab_loop_destructure_ = undefined_instances_of_types;
    type = Nil;
    names = Nil;
    rest_of_entries = Nil;
    temp = CAR(ab_loop_destructure_);
    type = CAR(temp);
    temp = CAR(ab_loop_destructure_);
    names = CDR(temp);
    rest_of_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(names,string_constant_29,
	    string_constant_30,string_constant_33,string_constant_34);
    write_type_specification(type);
    if ( !TRUEP(rest_of_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)2L));
    temp = CAR(rest_of_entries);
    type = CAR(temp);
    temp = CAR(rest_of_entries);
    names = CDR(temp);
    rest_of_entries = CDR(rest_of_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant_13;   /* # */

/* WRITE-NON-EXISTENT-PROCEDURE-METHOD-NOTE */
Object write_non_existent_procedure_method_note(dummy_for_particulars,
	    gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(179,129);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_13,
	    FIX((SI_Long)53L)));
    return VALUES_1(Nil);
}

static Object string_constant_35;  /* "there is more than one method defined for the ~
				    *           class ~a and that has ~a ~a"
				    */

static Object string_constant_36;  /* "arguments" */

static Object string_constant_37;  /* "argument" */

static Object string_constant_38;  /* "there is more than one method defined with the ~
				    *            same class for the first argument and with the same number of ~
				    *            arguments"
				    */

/* WRITE-SPECIFIC-METHOD-ARGUMENT-CONFLICT-NOTE */
Object write_specific_method_argument_conflict_note(dummy_for_particulars,
	    specific_method)
    Object dummy_for_particulars, specific_method;
{
    Object method_class_qm, arg_count_qm;

    x_note_fn_call(179,130);
    method_class_qm = ISVREF(specific_method,(SI_Long)31L);
    arg_count_qm = ISVREF(specific_method,(SI_Long)23L);
    GENSYM_RETURN_ONE(method_class_qm && arg_count_qm ? tformat(4,
	    string_constant_35,method_class_qm,arg_count_qm,
	    IFIX(arg_count_qm) > (SI_Long)1L ? string_constant_36 : 
	    string_constant_37) : tformat(1,string_constant_38));
    return VALUES_1(Nil);
}

static Object string_constant_39;  /* "the methods " */

static Object string_constant_40;  /* " is being called with no arguments" */

static Object string_constant_41;  /* " are being called with no arguments" */

/* WRITE-NO-ARG-FOR-METHOD-CALL-NOTE */
Object write_no_arg_for_method_call_note(names,gensymed_symbol)
    Object names, gensymed_symbol;
{
    x_note_fn_call(179,131);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(names,string_constant_27,
	    string_constant_39,string_constant_40,string_constant_41));
    return VALUES_1(Nil);
}

static Object string_constant_42;  /* "the method ~NN requires a first argument of class item, but ~
				    *        is being given "
				    */

static Object string_constant_43;  /* "a first argument of type ~NT" */

static Object array_constant_14;   /* # */

static Object string_constant_44;  /* "and" */

static Object string_constant_45;  /* "~NT" */

static Object array_constant_15;   /* # */

/* WRITE-NO-ITEM-ARG-FOR-METHOD-CALL-NOTE */
Object write_no_item_arg_for_method_call_note(method_and_first_arg_types_list,
	    gensymed_symbol)
    Object method_and_first_arg_types_list, gensymed_symbol;
{
    Object ab_loop_destructure_, method, first_arg_types, rest_of_entries;
    Object temp;

    x_note_fn_call(179,132);
    ab_loop_destructure_ = method_and_first_arg_types_list;
    method = Nil;
    first_arg_types = Nil;
    rest_of_entries = Nil;
    temp = CAR(ab_loop_destructure_);
    method = CAR(temp);
    temp = CAR(ab_loop_destructure_);
    first_arg_types = CDR(temp);
    rest_of_entries = CDR(ab_loop_destructure_);
  next_loop:
    tformat(2,string_constant_42,method);
    if ( !TRUEP(M_CDR(first_arg_types)))
	tformat(2,string_constant_43,M_CAR(first_arg_types));
    else {
	twrite_beginning_of_wide_string(array_constant_14,FIX((SI_Long)24L));
	write_list_in_chicago_style_given_format(first_arg_types,
		string_constant_44,string_constant_45);
    }
    if ( !TRUEP(rest_of_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)2L));
    temp = CAR(rest_of_entries);
    method = CAR(temp);
    temp = CAR(rest_of_entries);
    first_arg_types = CDR(temp);
    rest_of_entries = CDR(rest_of_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_46;  /* "the method~a " */

static Object string_constant_47;  /* "" */

static Object string_constant_48;  /* "s" */

static Object string_constant_49;  /* ", with ~a argument~a," */

static Object string_constant_50;  /* " ~a not defined for the class ~NN" */

static Object string_constant_51;  /* "is" */

static Object string_constant_52;  /* "are" */

/* WRITE-NO-METHOD-FOR-ARG-COUNT-NOTE */
Object write_no_method_for_arg_count_note(method_info,gensymed_symbol)
    Object method_info, gensymed_symbol;
{
    Object class_1, arg_count, method_list, rest_of_list, ab_loop_list_, temp;

    x_note_fn_call(179,133);
    class_1 = Nil;
    arg_count = Nil;
    method_list = Nil;
    rest_of_list = Nil;
    ab_loop_list_ = method_info;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    temp = CAR(temp);
    class_1 = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CAR(temp);
    arg_count = CDR(temp);
    temp = CAR(ab_loop_list_);
    method_list = CDR(temp);
    rest_of_list = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(2,string_constant_46, !TRUEP(M_CDR(method_list)) ? 
	    string_constant_47 : string_constant_48);
    write_list_in_chicago_style_given_format(method_list,
	    string_constant_44,string_constant_45);
    tformat(3,string_constant_49,arg_count,IFIX(arg_count) == (SI_Long)1L ?
	     string_constant_47 : string_constant_48);
    tformat(3,string_constant_50, !TRUEP(M_CDR(method_list)) ? 
	    string_constant_51 : string_constant_52,class_1);
    if ( !TRUEP(rest_of_list)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_53;  /* " is not defined for the class " */

static Object string_constant_54;  /* " are not defined for the class " */

/* WRITE-NO-METHOD-FOR-CLASS-NOTE */
Object write_no_method_for_class_note(class_and_methods_list,gensymed_symbol)
    Object class_and_methods_list, gensymed_symbol;
{
    Object ab_loop_destructure_, class_1, methods, rest_of_entries, temp;

    x_note_fn_call(179,134);
    ab_loop_destructure_ = class_and_methods_list;
    class_1 = Nil;
    methods = Nil;
    rest_of_entries = Nil;
    temp = CAR(ab_loop_destructure_);
    class_1 = CAR(temp);
    temp = CAR(ab_loop_destructure_);
    methods = CDR(temp);
    rest_of_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(methods,string_constant_27,
	    string_constant_39,string_constant_53,string_constant_54);
    twrite(class_1);
    if ( !TRUEP(rest_of_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)2L));
    temp = CAR(rest_of_entries);
    class_1 = CAR(temp);
    temp = CAR(rest_of_entries);
    methods = CDR(temp);
    rest_of_entries = CDR(rest_of_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_55;  /* " defined for the class " */

static Object string_constant_56;  /* "~a is not OK" */

static Object string_constant_57;  /* "~a are not OK" */

/* WRITE-METHOD-FOR-CLASS-NOT-OKAY-NOTE */
Object write_method_for_class_not_okay_note(class_and_methods_list,
	    gensymed_symbol)
    Object class_and_methods_list, gensymed_symbol;
{
    Object ab_loop_destructure_, class_1, methods, rest_of_entries, temp;

    x_note_fn_call(179,135);
    ab_loop_destructure_ = class_and_methods_list;
    class_1 = Nil;
    methods = Nil;
    rest_of_entries = Nil;
    temp = CAR(ab_loop_destructure_);
    class_1 = CAR(temp);
    temp = CAR(ab_loop_destructure_);
    methods = CDR(temp);
    rest_of_entries = CDR(ab_loop_destructure_);
  next_loop:
    write_frame_notes_for_names(methods,string_constant_27,
	    string_constant_39,string_constant_55,string_constant_55);
    if ( !TRUEP(M_CDR(methods)))
	tformat(2,string_constant_56,class_1);
    else
	tformat(2,string_constant_57,class_1);
    if ( !TRUEP(rest_of_entries)) {
	temp = Nil;
	goto end_1;
    }
    else
	twrite_beginning_of_wide_string(array_constant_15,FIX((SI_Long)2L));
    temp = CAR(rest_of_entries);
    class_1 = CAR(temp);
    temp = CAR(rest_of_entries);
    methods = CDR(temp);
    rest_of_entries = CDR(rest_of_entries);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object array_constant_16;   /* # */

/* WRITE-FRAME-NOTES-FOR-NAMES */
Object write_frame_notes_for_names(names,preamble_singular_string,
	    preamble_plural_string,singular_string,plural_string)
    Object names, preamble_singular_string, preamble_plural_string;
    Object singular_string, plural_string;
{
    Object ab_loop_destructure_, name, rest_of_names, temp;
    SI_Long limit, index_1, ab_loop_bind_;
    char singular_qm;

    x_note_fn_call(179,136);
    singular_qm =  !TRUEP(CDR(names));
    twrite_general_string(singular_qm ? preamble_singular_string : 
	    preamble_plural_string);
    limit = Abbreviate_frame_notes_p ? (SI_Long)3L : 
	    IFIX(Most_positive_fixnum);
    ab_loop_destructure_ = names;
    name = Nil;
    rest_of_names = Nil;
    name = CAR(ab_loop_destructure_);
    rest_of_names = CDR(ab_loop_destructure_);
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = limit;
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    if (CONSP(name) && EQ(M_CAR(name),Qclass_qualified_name))
	write_name_or_class_qualified_name(name);
    else
	twrite(name);
    if ( !TRUEP(rest_of_names) || index_1 == limit) {
	if (rest_of_names)
	    twrite_beginning_of_wide_string(array_constant_16,
		    FIX((SI_Long)22L));
	twrite_general_string(singular_qm ? singular_string : plural_string);
	return VALUES_1(Nil);
    }
    if (CDR(rest_of_names) && index_1 < limit - (SI_Long)1L)
	temp = string_constant_3;
    else if (CDDR(names))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    name = CAR(rest_of_names);
    rest_of_names = CDR(rest_of_names);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-ARG-COUNT-MISMATCH-NOTE */
Object write_arg_count_mismatch_note(names_and_counts,gensymed_symbol)
    Object names_and_counts, gensymed_symbol;
{
    x_note_fn_call(179,137);
    GENSYM_RETURN_ONE(twrite_count_mismatch(names_and_counts,T));
    return VALUES_1(Nil);
}

/* WRITE-RETURN-COUNT-MISMATCH-NOTE */
Object write_return_count_mismatch_note(names_and_counts,gensymed_symbol)
    Object names_and_counts, gensymed_symbol;
{
    x_note_fn_call(179,138);
    GENSYM_RETURN_ONE(twrite_count_mismatch(names_and_counts,Nil));
    return VALUES_1(Nil);
}

static Object string_constant_58;  /* "~a requires ~a argument~a but was given " */

static Object string_constant_59;  /* "~a returns ~a value~a but was expected to return " */

static Object string_constant_60;  /* " argument~a" */

static Object string_constant_61;  /* " value~a" */

/* TWRITE-COUNT-MISMATCH */
Object twrite_count_mismatch(names_and_counts,args_qm)
    Object names_and_counts, args_qm;
{
    Object name, defined_count, supplied_count_list, rest_of_list;
    Object ab_loop_list_, temp;

    x_note_fn_call(179,139);
    name = Nil;
    defined_count = Nil;
    supplied_count_list = Nil;
    rest_of_list = Nil;
    ab_loop_list_ = names_and_counts;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    name = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    defined_count = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    supplied_count_list = CDR(temp);
    rest_of_list = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(4,args_qm ? string_constant_58 : string_constant_59,name,
	    defined_count,IFIX(defined_count) == (SI_Long)1L ? 
	    string_constant_47 : string_constant_48);
    write_list_in_chicago_style(2,supplied_count_list,string_constant_44);
    tformat(2,args_qm ? string_constant_60 : string_constant_61,
	    IFIX(length(supplied_count_list)) == (SI_Long)1L && 
	    IFIX(FIRST(supplied_count_list)) == (SI_Long)1L ? 
	    string_constant_47 : string_constant_48);
    if ( !TRUEP(rest_of_list))
	goto end_loop;
    if (CDR(rest_of_list))
	temp = string_constant_3;
    else if (CDDR(names_and_counts))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_62;  /* "the class~a " */

static Object string_constant_63;  /* "es" */

static Object string_constant_64;  /* "~a" */

static Object string_constant_65;  /* "~a, with ~a argument~a, " */

static Object string_constant_66;  /* " ~NN depends upon a stable heirarchy which is no longer stable " */

/* WRITE-ITEM-DEPENDS-ON-UNSTABLE-HEIRARCHY-NOTE */
Object write_item_depends_on_unstable_heirarchy_note(stability_info_list,
	    gensymed_symbol)
    Object stability_info_list, gensymed_symbol;
{
    Object class_stability_items, method_stability_items, info_item;
    Object ab_loop_list_, class_name, rest_of_list, temp, method_name;
    Object focus_class, arg_count;

    x_note_fn_call(179,140);
    class_stability_items = Nil;
    method_stability_items = Nil;
    info_item = Nil;
    ab_loop_list_ = stability_info_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(M_CDR(info_item)))
	class_stability_items = installation_cons_1(info_item,
		class_stability_items);
    else
	method_stability_items = installation_cons_1(info_item,
		method_stability_items);
    goto next_loop;
  end_loop:;
    if (class_stability_items) {
	tformat(2,string_constant_62, !TRUEP(M_CDR(class_stability_items)) 
		? string_constant_47 : string_constant_63);
	class_name = Nil;
	rest_of_list = Nil;
	ab_loop_list_ = class_stability_items;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	temp = CAR(ab_loop_list_);
	class_name = CAR(temp);
	rest_of_list = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	tformat(2,string_constant_64,class_name);
	if ( !TRUEP(rest_of_list))
	    goto end_1;
	else
	    twrite_beginning_of_wide_string(array_constant_15,
		    FIX((SI_Long)2L));
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    if (method_stability_items) {
	tformat(2,string_constant_46, 
		!TRUEP(M_CDR(method_stability_items)) ? string_constant_47 
		: string_constant_48);
	method_name = Nil;
	focus_class = Nil;
	arg_count = Nil;
	rest_of_list = Nil;
	ab_loop_list_ = method_stability_items;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	temp = CAR(ab_loop_list_);
	method_name = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	focus_class = CAR(temp);
	temp = CAR(ab_loop_list_);
	temp = CDR(temp);
	temp = CDR(temp);
	arg_count = CAR(temp);
	rest_of_list = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (arg_count)
	    tformat(4,string_constant_65,method_name,arg_count,
		    IFIX(arg_count) == (SI_Long)1L ? string_constant_47 : 
		    string_constant_48);
	else
	    tformat(2,string_constant_64,method_name);
	tformat(2,string_constant_66,focus_class);
	if ( !TRUEP(rest_of_list)) {
	    temp = Nil;
	    goto end_2;
	}
	else
	    twrite_beginning_of_wide_string(array_constant_15,
		    FIX((SI_Long)2L));
	goto next_loop_2;
      end_loop_2:
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_67;  /* "the procedure~a " */

static Object string_constant_68;  /* "the methods and procedures " */

static Object Kcross_module_violation;  /* :cross-module-violation */

static Object string_constant_69;  /* " can't be inlined because of a cross-module violation " */

static Object string_constant_70;  /* " is no longer the same as what was inlined " */

/* WRITE-ITEM-DEPENDS-ON-INVALID-INLINING-NOTE */
Object write_item_depends_on_invalid_inlining_note(stability_info_list,
	    gensymed_symbol)
    Object stability_info_list, gensymed_symbol;
{
    Object plural_string, focus_class_qm, ab_loop_list_, ab_loop_desetq_;
    Object method_name, arg_count, reason, rest_of_list, temp_1;
    char temp;

    x_note_fn_call(179,141);
    if (stability_info_list) {
	plural_string =  !TRUEP(M_CDR(stability_info_list)) ? 
		string_constant_47 : string_constant_48;
	focus_class_qm = Nil;
	ab_loop_list_ = stability_info_list;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	focus_class_qm = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(focus_class_qm)) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	if (temp)
	    tformat(2,string_constant_46,plural_string);
	else {
	    focus_class_qm = Nil;
	    ab_loop_list_ = stability_info_list;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    focus_class_qm = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (focus_class_qm) {
		temp = TRUEP(Nil);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(T);
	    goto end_2;
	    temp = TRUEP(Qnil);
	  end_2:;
	    if (temp)
		tformat(2,string_constant_67,plural_string);
	    else
		tformat(1,string_constant_68);
	}
	focus_class_qm = Nil;
	method_name = Nil;
	arg_count = Nil;
	reason = Nil;
	rest_of_list = Nil;
	ab_loop_list_ = stability_info_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	temp_1 = CAR(ab_loop_list_);
	focus_class_qm = CAR(temp_1);
	temp_1 = CAR(ab_loop_list_);
	temp_1 = CDR(temp_1);
	method_name = CAR(temp_1);
	temp_1 = CAR(ab_loop_list_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	arg_count = CAR(temp_1);
	temp_1 = CAR(ab_loop_list_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	reason = CAR(temp_1);
	rest_of_list = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_name_denotation_components(method_name,focus_class_qm);
	if (arg_count)
	    tformat(3,string_constant_49,arg_count,IFIX(arg_count) == 
		    (SI_Long)1L ? string_constant_47 : string_constant_48);
	twrite_general_string(EQ(reason,Kcross_module_violation) ? 
		string_constant_69 : string_constant_70);
	if ( !TRUEP(rest_of_list)) {
	    temp_1 = Nil;
	    goto end_3;
	}
	else
	    twrite_beginning_of_wide_string(array_constant_15,
		    FIX((SI_Long)2L));
	goto next_loop_2;
      end_loop_2:
	temp_1 = Qnil;
      end_3:;
    }
    else
	temp_1 = Nil;
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object array_constant_17;   /* # */

/* WRITE-ITEM-INLINEABLE-BUT-HAS-NO-PARSE-NOTE */
Object write_item_inlineable_but_has_no_parse_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(179,142);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_17,
	    FIX((SI_Long)69L)));
    return VALUES_1(Nil);
}

static Object string_constant_71;  /* " is not OK" */

static Object string_constant_72;  /* " are not OK" */

/* WRITE-ITEM-NOT-OK-NOTE */
Object write_item_not_ok_note(names,gensymed_symbol)
    Object names, gensymed_symbol;
{
    x_note_fn_call(179,143);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(names,string_constant_17,
	    string_constant_18,string_constant_71,string_constant_72));
    return VALUES_1(Nil);
}

/* WRITE-ARG-TYPE-MISMATCH-NOTE */
Object write_arg_type_mismatch_note(names_and_types,gensymed_symbol)
    Object names_and_types, gensymed_symbol;
{
    x_note_fn_call(179,144);
    GENSYM_RETURN_ONE(twrite_type_mismatch(names_and_types,T));
    return VALUES_1(Nil);
}

/* WRITE-RETURN-TYPE-MISMATCH-NOTE */
Object write_return_type_mismatch_note(names_and_types,gensymed_symbol)
    Object names_and_types, gensymed_symbol;
{
    x_note_fn_call(179,145);
    GENSYM_RETURN_ONE(twrite_type_mismatch(names_and_types,Nil));
    return VALUES_1(Nil);
}

static Object string_constant_73;  /* "argument ~a of ~a requires values of type ~NT but was given values ~
				    *            of type~a "
				    */

static Object string_constant_74;  /* "return value ~a of ~a provides values of type ~NT but was expected ~
				    *            to provide values of type~a "
				    */

/* TWRITE-TYPE-MISMATCH */
Object twrite_type_mismatch(names_and_types,args_qm)
    Object names_and_types, args_qm;
{
    Object name, which, defined_type, supplied_type_list, rest_of_list;
    Object ab_loop_list_, temp;

    x_note_fn_call(179,146);
    name = Nil;
    which = Nil;
    defined_type = Nil;
    supplied_type_list = Nil;
    rest_of_list = Nil;
    ab_loop_list_ = names_and_types;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    temp = CAR(temp);
    name = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CAR(temp);
    which = CDR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    defined_type = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    supplied_type_list = CDR(temp);
    rest_of_list = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(5,args_qm ? string_constant_73 : string_constant_74,which,name,
	    defined_type,IFIX(length(supplied_type_list)) == (SI_Long)1L ? 
	    string_constant_47 : string_constant_48);
    write_list_in_chicago_style_given_format(supplied_type_list,
	    string_constant_44,string_constant_45);
    if ( !TRUEP(rest_of_list))
	goto end_loop;
    if (CDR(rest_of_list))
	temp = string_constant_3;
    else if (CDDR(names_and_types))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    twrite_general_string(temp);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_18;   /* # */

/* WRITE-ITEM-NO-LONGER-DEPENDENT-NOTE */
Object write_item_no_longer_dependent_note(dummy_for_particulars,
	    gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(179,147);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_18,
	    FIX((SI_Long)66L)));
    return VALUES_1(Nil);
}

static Object string_constant_75;  /* "this item needs to be recompiled because it depends on the stable item " */

static Object string_constant_76;  /* "this item needs to be recompiled because it depends on the stable items " */

static Object string_constant_77;  /* " which has been modified" */

static Object string_constant_78;  /* " which have been modified" */

/* WRITE-ITEM-DEPENDS-ON-MODIFIED-STABLE-ITEM-NOTE */
Object write_item_depends_on_modified_stable_item_note(names,gensymed_symbol)
    Object names, gensymed_symbol;
{
    x_note_fn_call(179,148);
    GENSYM_RETURN_ONE(write_frame_notes_for_names(names,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78));
    return VALUES_1(Nil);
}

/* ANALYZE-COMPILED-ITEMS-AFTER-LOADING-1 */
Object analyze_compiled_items_after_loading_1()
{
    Object post_analyzer_warning_notes_for_generic_simulation_formulas_qm;
    Object post_kb_loading_consistency_analysis, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, item, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(179,149);
    post_analyzer_warning_notes_for_generic_simulation_formulas_qm = T;
    post_kb_loading_consistency_analysis = T;
    PUSH_SPECIAL_WITH_SYMBOL(Post_kb_loading_consistency_analysis,Qpost_kb_loading_consistency_analysis,post_kb_loading_consistency_analysis,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Post_analyzer_warning_notes_for_generic_simulation_formulas_qm,Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm,post_analyzer_warning_notes_for_generic_simulation_formulas_qm,
	      1);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	item = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qblock);
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
	  if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		  (SI_Long)16777216L))) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = item;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ANALYZE-COMPILED-ITEMS-FOR-CONSISTENCY */
Object analyze_compiled_items_for_consistency(name)
    Object name;
{
    Object compiled_items_referring_to_this_name, item, ab_loop_list_;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(179,150);
    if ( !TRUEP(Loading_kb_p)) {
	compiled_items_referring_to_this_name = 
		lookup_kb_specific_property_value(name,
		Compiled_items_referring_to_this_name_kbprop);
	item = Nil;
	ab_loop_list_ = compiled_items_referring_to_this_name;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(item,(SI_Long)3L);
	if ( !(FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil))) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = item;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qobject_configuration;  /* object-configuration */

static Object Qcheck_undefined_instances_of_class;  /* check-undefined-instances-of-class */

/* ANALYZE-FOR-CONSISTENCY-FOR-BLOCK */
Object analyze_for_consistency_for_block(block,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object block, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, object_configuration_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,151);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(block);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,block);
		    compiled_item_being_analyzed = block;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    0);
		      object_configuration_qm = 
			      get_lookup_slot_value(block,
			      Qobject_configuration);
		      if (object_configuration_qm)
			  map_over_external_names_in_object_configuration(SYMBOL_FUNCTION(Qcheck_undefined_instances_of_class),
				  object_configuration_qm);
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(block));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qstubs_for_class;    /* stubs-for-class */

static Object Qcar_eq;             /* car-eq */

static Object Qicon_description_for_class_qm;  /* icon-description-for-class? */

static Object Qimage;              /* image */

static Object Qimage_definition;   /* image-definition */

static Object Qicon_background_images;  /* icon-background-images */

static Object Qinitial_value_class_incompatible_with_type;  /* initial-value-class-incompatible-with-type */

static Object Qdata_server_map;    /* data-server-map */

static Object Qg2_variable;        /* g2-variable */

static Object Qsupplied;           /* supplied */

static Object Qincompatible_validity_interval_and_data_server;  /* incompatible-validity-interval-and-data-server */

static Object Qoverride_value_is_not_compatible;  /* override-value-is-not-compatible */

/* ANALYZE-FOR-CONSISTENCY-FOR-CLASS-DEFINITION */
Object analyze_for_consistency_for_class_definition(class_definition,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object class_definition, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, class_name_qm, class_description_qm;
    Object default_overrides, sub_class_bit_vector, connections_qm, temp_1;
    Object stubs_for_class_override_qm, icon_description_qm, stub_spec;
    Object ab_loop_list_, connection_class, any_qm, default_variables;
    Object drawing_element, image_name_qm, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, background_layer;
    Object attribute_description, attribute_name;
    Object attribute_type_specification_1, class_type_specification_qm;
    Object class_type_qm, attribute_initial_type, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, gensymed_symbol_3;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cons_holding_validity_interval_override_qm;
    Object cons_holding_data_server_map_override_qm;
    Object real_or_implied_validity_interval_value, slot_description_qm;
    Object real_or_implied_data_server_map_value, override;
    Object class_to_instantiate_qm, name_denotation, pretty_slot_name;
    Object defining_class;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(179,152);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      5);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(class_definition);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    class_definition);
		    compiled_item_being_analyzed = class_definition;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    4);
		      class_name_qm = ISVREF(class_definition,(SI_Long)20L);
		      class_description_qm = 
			      lookup_global_or_kb_specific_property_value(class_name_qm,
			      Class_description_gkbprop);
		      default_overrides = ISVREF(class_definition,
			      (SI_Long)27L);
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(class_definition,(SI_Long)1L),
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Object_definition_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  connections_qm = ISVREF(class_definition,
				  (SI_Long)30L);
		      else {
			  temp_1 = member(4,Qstubs_for_class,
				  default_overrides,Ktest,Qcar_eq);
			  stubs_for_class_override_qm = CAR(temp_1);
			  connections_qm = stubs_for_class_override_qm ? 
				  M_CAR(M_CDR(stubs_for_class_override_qm)) 
				  : Qnil;
		      }
		      icon_description_qm = 
			      get_lookup_slot_value_given_default(class_definition,
			      Qicon_description_for_class_qm,Nil);
		      if ( !SYMBOLP(connections_qm)) {
			  stub_spec = Nil;
			  ab_loop_list_ = CDR(connections_qm);
			  connection_class = Nil;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  stub_spec = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  connection_class = SECOND(stub_spec);
			  check_for_undefined_class(connection_class);
			  goto next_loop;
			end_loop:;
		      }
		      any_qm = Nil;
		      temp_1 = 
			      get_variable_specification_if_any(icon_description_qm);
		      default_variables = CDR(temp_1);
		      drawing_element = Nil;
		      ab_loop_list_ = CDDR(icon_description_qm);
		      image_name_qm = Nil;
		    next_loop_1:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_1;
		      drawing_element = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (CONSP(drawing_element) && 
			      EQ(FIRST(drawing_element),Qimage)) {
			  current_icon_untransformed_width = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
				  3);
			    current_icon_untransformed_height = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
				    2);
			      current_icon_variables_plist = default_variables;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
				      1);
				current_icon_variables_override_plist = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
					0);
				  image_name_qm = 
					  simple_eval_for_icon(SECOND(drawing_element));
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		      else
			  image_name_qm = Nil;
		      if (image_name_qm && SYMBOLP(image_name_qm)) {
			  check_undefined_instances_of_class(image_name_qm,
				  Qimage_definition);
			  any_qm = T;
		      }
		      goto next_loop_1;
		    end_loop_1:
		      if (any_qm)
			  flush_icon_caches_and_redraw_instances(class_definition);
		      background_layer = 
			      get_lookup_slot_value_given_default(class_definition,
			      Qicon_background_images,Nil);
		      image_name_qm = CONSP(background_layer) && 
			      EQ(FIRST(background_layer),Qimage) ? 
			      SECOND(background_layer) : Qnil;
		      if (image_name_qm)
			  check_undefined_instances_of_class(image_name_qm,
				  Qimage_definition);
		      if (image_name_qm && 
			      (Post_kb_loading_consistency_analysis ||  
			      !TRUEP(Add_as_item_referring_to_name_qm) &&  
			      !TRUEP(Delete_as_item_referring_to_name_qm)) 
			      &&  !((SI_Long)0L != 
			      (IFIX(ISVREF(class_definition,(SI_Long)5L)) 
			      & (SI_Long)512L)))
			  flush_icon_caches_and_redraw_instances(class_definition);
		      attribute_description = Nil;
		      ab_loop_list_ = ISVREF(class_definition,(SI_Long)22L);
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      attribute_description = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      temp_1 = CDDR(attribute_description);
		      if (slot_init_form_needs_evaluation_qm(CAR(temp_1))) {
			  attribute_name = CAR(attribute_description);
			  attribute_type_specification_1 = 
				  attribute_type_specification(attribute_description);
			  class_type_specification_qm = 
				  class_type_specification_p(attribute_type_specification_1);
			  class_type_qm = class_type_specification_qm ? 
				  type_specification_class_function(attribute_type_specification_1) 
				  : Qnil;
			  temp_1 = CDDDR(attribute_description);
			  attribute_initial_type = CAR(temp_1);
			  if (class_type_qm) {
			      check_for_undefined_class(class_type_qm);
			      if (SYMBOLP(class_type_qm)) {
				  skip_list = CDR(Symbol_properties_table);
				  key_value = class_type_qm;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(class_type_qm) & 
					  IFIX(Most_positive_fixnum);
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
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_4:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_5:
				  if ( !TRUEP(marked))
				      goto end_loop_4;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_5;
				end_loop_4:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_1;
				  goto next_loop_4;
				end_loop_5:
				end_1:
				  level = level - (SI_Long)1L;
				  goto next_loop_3;
				end_loop_3:;
				  gensymed_symbol_3 = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if ( !TRUEP(gensymed_symbol_3)) {
				      gensymed_symbol_3 = class_type_qm;
				      temp_2 = Symbol_properties_table;
				      temp_1 = 
					      FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					      & IFIX(Most_positive_fixnum));
				      tail = 
					      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					      Nil);
				      head = 
					      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					      tail);
				      new_cons = 
					      ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  svref_arg_1 = 
						  Available_lookup_conses_vector;
					  svref_arg_2 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(svref_arg_1,svref_arg_2) = 
						  svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      svref_arg_1 = 
						      Available_lookup_conses_tail_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      SVREF(svref_arg_1,
						      svref_arg_2) = Nil;
					  }
					  gensymed_symbol_4 = new_cons;
				      }
				      else
					  gensymed_symbol_4 = Nil;
				      if ( !TRUEP(gensymed_symbol_4))
					  gensymed_symbol_4 = 
						  replenish_lookup_cons_pool();
				      M_CAR(gensymed_symbol_4) = 
					      Qsymbol_properties_hash_table;
				      new_cons = 
					      ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  svref_arg_1 = 
						  Available_lookup_conses_vector;
					  svref_arg_2 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(svref_arg_1,svref_arg_2) = 
						  svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      svref_arg_1 = 
						      Available_lookup_conses_tail_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      SVREF(svref_arg_1,
						      svref_arg_2) = Nil;
					  }
					  gensymed_symbol_5 = new_cons;
				      }
				      else
					  gensymed_symbol_5 = Nil;
				      if ( !TRUEP(gensymed_symbol_5))
					  gensymed_symbol_5 = 
						  replenish_lookup_cons_pool();
				      M_CAR(gensymed_symbol_5) = head;
				      M_CDR(gensymed_symbol_5) = tail;
				      inline_note_allocate_cons(gensymed_symbol_5,
					      Qlookup);
				      M_CDR(gensymed_symbol_4) = 
					      gensymed_symbol_5;
				      inline_note_allocate_cons(gensymed_symbol_4,
					      Qlookup);
				      gensymed_symbol_3 = 
					      set_skip_list_entry(temp_2,
					      FIX((SI_Long)31L),Qeq,Nil,T,
					      gensymed_symbol_3,temp_1,
					      gensymed_symbol_4);
				  }
				  global_properties = gensymed_symbol_3;
				  skip_list = CDR(global_properties);
				  key_value = 
					  Current_kb_specific_property_list_property_name;
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
				next_loop_6:
				  if (level < ab_loop_bind_)
				      goto end_loop_6;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_7:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_8:
				  if ( !TRUEP(marked))
				      goto end_loop_7;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_8;
				end_loop_7:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_2;
				  goto next_loop_7;
				end_loop_8:
				end_2:
				  level = level - (SI_Long)1L;
				  goto next_loop_6;
				end_loop_6:;
				  kb_properties = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_properties);
				  else
				      kb_properties = Nil;
				  if (kb_properties) {
				      skip_list = CDR(kb_properties);
				      key_value = Class_description_gkbprop;
				      key_hash_value = 
					      SXHASH_SYMBOL_1(Class_description_gkbprop) 
					      & IFIX(Most_positive_fixnum);
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
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_10:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_11:
				      if ( !TRUEP(marked))
					  goto end_loop_10;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_11;
				    end_loop_10:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_3;
				      goto next_loop_10;
				    end_loop_11:
				    end_3:
				      level = level - (SI_Long)1L;
				      goto next_loop_9;
				    end_loop_9:;
				      kb_specific_value = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
				      if (kb_specific_value);
				      else
					  kb_specific_value = 
						  No_specific_property_value;
				  }
				  else
				      kb_specific_value = 
					      No_specific_property_value;
				  if ( !EQ(kb_specific_value,
					  No_specific_property_value))
				      resulting_value = kb_specific_value;
				  else {
				      skip_list = CDR(global_properties);
				      key_value = Class_description_gkbprop;
				      key_hash_value = 
					      SXHASH_SYMBOL_1(Class_description_gkbprop) 
					      & IFIX(Most_positive_fixnum);
				      bottom_level = (SI_Long)0L;
				      marked = Nil;
				      pred = M_CAR(skip_list);
				      curr = Nil;
				      succ = Nil;
				      level = (SI_Long)31L;
				      ab_loop_bind_ = bottom_level;
				    next_loop_12:
				      if (level < ab_loop_bind_)
					  goto end_loop_12;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_13:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_14:
				      if ( !TRUEP(marked))
					  goto end_loop_13;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_14;
				    end_loop_13:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_4;
				      goto next_loop_13;
				    end_loop_14:
				    end_4:
				      level = level - (SI_Long)1L;
				      goto next_loop_12;
				    end_loop_12:;
				      resulting_value = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
				      if (resulting_value);
				      else
					  resulting_value = Nil;
				  }
				  temp = TRUEP(resulting_value);
			      }
			      else
				  temp = TRUEP(Nil);
			      if (temp) {
				  if (SYMBOLP(attribute_initial_type)) {
				      skip_list = CDR(Symbol_properties_table);
				      key_value = attribute_initial_type;
				      key_hash_value = 
					      SXHASH_SYMBOL_1(attribute_initial_type) 
					      & IFIX(Most_positive_fixnum);
				      bottom_level = (SI_Long)0L;
				      marked = Nil;
				      pred = M_CAR(skip_list);
				      curr = Nil;
				      succ = Nil;
				      level = (SI_Long)31L;
				      ab_loop_bind_ = bottom_level;
				    next_loop_15:
				      if (level < ab_loop_bind_)
					  goto end_loop_15;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_16:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_17:
				      if ( !TRUEP(marked))
					  goto end_loop_16;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_17;
				    end_loop_16:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_5;
				      goto next_loop_16;
				    end_loop_17:
				    end_5:
				      level = level - (SI_Long)1L;
				      goto next_loop_15;
				    end_loop_15:;
				      gensymed_symbol_3 = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
				      if ( !TRUEP(gensymed_symbol_3)) {
					  gensymed_symbol_3 = 
						  attribute_initial_type;
					  temp_2 = Symbol_properties_table;
					  temp_1 = 
						  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
						  & 
						  IFIX(Most_positive_fixnum));
					  tail = 
						  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
						  Nil);
					  head = 
						  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
						  tail);
					  new_cons = 
						  ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      svref_arg_1 = 
						      Available_lookup_conses_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(svref_arg_1,
						      svref_arg_2) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_lookup_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  svref_arg_1 = 
							  Available_lookup_conses_tail_vector;
						  svref_arg_2 = 
							  Current_thread_index;
						  SVREF(svref_arg_1,
							  svref_arg_2) = Nil;
					      }
					      gensymed_symbol_4 = new_cons;
					  }
					  else
					      gensymed_symbol_4 = Nil;
					  if ( !TRUEP(gensymed_symbol_4))
					      gensymed_symbol_4 = 
						      replenish_lookup_cons_pool();
					  M_CAR(gensymed_symbol_4) = 
						  Qsymbol_properties_hash_table;
					  new_cons = 
						  ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      svref_arg_1 = 
						      Available_lookup_conses_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(svref_arg_1,
						      svref_arg_2) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_lookup_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  svref_arg_1 = 
							  Available_lookup_conses_tail_vector;
						  svref_arg_2 = 
							  Current_thread_index;
						  SVREF(svref_arg_1,
							  svref_arg_2) = Nil;
					      }
					      gensymed_symbol_5 = new_cons;
					  }
					  else
					      gensymed_symbol_5 = Nil;
					  if ( !TRUEP(gensymed_symbol_5))
					      gensymed_symbol_5 = 
						      replenish_lookup_cons_pool();
					  M_CAR(gensymed_symbol_5) = head;
					  M_CDR(gensymed_symbol_5) = tail;
					  inline_note_allocate_cons(gensymed_symbol_5,
						  Qlookup);
					  M_CDR(gensymed_symbol_4) = 
						  gensymed_symbol_5;
					  inline_note_allocate_cons(gensymed_symbol_4,
						  Qlookup);
					  gensymed_symbol_3 = 
						  set_skip_list_entry(temp_2,
						  FIX((SI_Long)31L),Qeq,
						  Nil,T,gensymed_symbol_3,
						  temp_1,gensymed_symbol_4);
				      }
				      global_properties = gensymed_symbol_3;
				      skip_list = CDR(global_properties);
				      key_value = 
					      Current_kb_specific_property_list_property_name;
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
				    next_loop_18:
				      if (level < ab_loop_bind_)
					  goto end_loop_18;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_19:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_20:
				      if ( !TRUEP(marked))
					  goto end_loop_19;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_2 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_2,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_20;
				    end_loop_19:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_6;
				      goto next_loop_19;
				    end_loop_20:
				    end_6:
				      level = level - (SI_Long)1L;
				      goto next_loop_18;
				    end_loop_18:;
				      kb_properties = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
				      if (kb_properties);
				      else
					  kb_properties = Nil;
				      if (kb_properties) {
					  skip_list = CDR(kb_properties);
					  key_value = 
						  Class_description_gkbprop;
					  key_hash_value = 
						  SXHASH_SYMBOL_1(Class_description_gkbprop) 
						  & IFIX(Most_positive_fixnum);
					  bottom_level = (SI_Long)0L;
					  marked = Nil;
					  pred = M_CAR(skip_list);
					  curr = Nil;
					  succ = Nil;
					  level = (SI_Long)31L;
					  ab_loop_bind_ = bottom_level;
					next_loop_21:
					  if (level < ab_loop_bind_)
					      goto end_loop_21;
					  curr = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						  (SI_Long)0L),level));
					next_loop_22:
					  reference = ISVREF(ISVREF(curr,
						  (SI_Long)0L),level);
					  temp_2 = 
						  ATOMIC_REF_OBJECT(reference);
					  temp_1 = (SI_Long)355L == 
						  ATOMIC_REF_STAMP(reference) 
						  ? T : Nil;
					  result = VALUES_2(temp_2,temp_1);
					  MVS_2(result,succ,marked);
					next_loop_23:
					  if ( !TRUEP(marked))
					      goto end_loop_22;
					  curr = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						  (SI_Long)0L),level));
					  reference = ISVREF(ISVREF(curr,
						  (SI_Long)0L),level);
					  temp_2 = 
						  ATOMIC_REF_OBJECT(reference);
					  temp_1 = (SI_Long)355L == 
						  ATOMIC_REF_STAMP(reference) 
						  ? T : Nil;
					  result = VALUES_2(temp_2,temp_1);
					  MVS_2(result,succ,marked);
					  goto next_loop_23;
					end_loop_22:
					  entry_hash = ISVREF(curr,
						  (SI_Long)1L);
					  if (IFIX(entry_hash) < 
						  key_hash_value || 
						  IFIX(entry_hash) == 
						  key_hash_value &&  
						  !EQ(key_value,
						  ISVREF(curr,(SI_Long)2L))) {
					      pred = curr;
					      curr = succ;
					  }
					  else
					      goto end_7;
					  goto next_loop_22;
					end_loop_23:
					end_7:
					  level = level - (SI_Long)1L;
					  goto next_loop_21;
					end_loop_21:;
					  kb_specific_value = 
						  IFIX(ISVREF(curr,
						  (SI_Long)1L)) == 
						  key_hash_value ? 
						  (EQ(key_value,
						  ISVREF(curr,
						  (SI_Long)2L)) ? 
						  ISVREF(curr,(SI_Long)3L) 
						  : Nil) : Nil;
					  if (kb_specific_value);
					  else
					      kb_specific_value = 
						      No_specific_property_value;
				      }
				      else
					  kb_specific_value = 
						  No_specific_property_value;
				      if ( !EQ(kb_specific_value,
					      No_specific_property_value))
					  resulting_value = kb_specific_value;
				      else {
					  skip_list = CDR(global_properties);
					  key_value = 
						  Class_description_gkbprop;
					  key_hash_value = 
						  SXHASH_SYMBOL_1(Class_description_gkbprop) 
						  & IFIX(Most_positive_fixnum);
					  bottom_level = (SI_Long)0L;
					  marked = Nil;
					  pred = M_CAR(skip_list);
					  curr = Nil;
					  succ = Nil;
					  level = (SI_Long)31L;
					  ab_loop_bind_ = bottom_level;
					next_loop_24:
					  if (level < ab_loop_bind_)
					      goto end_loop_24;
					  curr = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						  (SI_Long)0L),level));
					next_loop_25:
					  reference = ISVREF(ISVREF(curr,
						  (SI_Long)0L),level);
					  temp_2 = 
						  ATOMIC_REF_OBJECT(reference);
					  temp_1 = (SI_Long)355L == 
						  ATOMIC_REF_STAMP(reference) 
						  ? T : Nil;
					  result = VALUES_2(temp_2,temp_1);
					  MVS_2(result,succ,marked);
					next_loop_26:
					  if ( !TRUEP(marked))
					      goto end_loop_25;
					  curr = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						  (SI_Long)0L),level));
					  reference = ISVREF(ISVREF(curr,
						  (SI_Long)0L),level);
					  temp_2 = 
						  ATOMIC_REF_OBJECT(reference);
					  temp_1 = (SI_Long)355L == 
						  ATOMIC_REF_STAMP(reference) 
						  ? T : Nil;
					  result = VALUES_2(temp_2,temp_1);
					  MVS_2(result,succ,marked);
					  goto next_loop_26;
					end_loop_25:
					  entry_hash = ISVREF(curr,
						  (SI_Long)1L);
					  if (IFIX(entry_hash) < 
						  key_hash_value || 
						  IFIX(entry_hash) == 
						  key_hash_value &&  
						  !EQ(key_value,
						  ISVREF(curr,(SI_Long)2L))) {
					      pred = curr;
					      curr = succ;
					  }
					  else
					      goto end_8;
					  goto next_loop_25;
					end_loop_26:
					end_8:
					  level = level - (SI_Long)1L;
					  goto next_loop_24;
					end_loop_24:;
					  resulting_value = 
						  IFIX(ISVREF(curr,
						  (SI_Long)1L)) == 
						  key_hash_value ? 
						  (EQ(key_value,
						  ISVREF(curr,
						  (SI_Long)2L)) ? 
						  ISVREF(curr,(SI_Long)3L) 
						  : Nil) : Nil;
					  if (resulting_value);
					  else
					      resulting_value = Nil;
				      }
				      temp = TRUEP(resulting_value);
				  }
				  else
				      temp = TRUEP(Nil);
			      }
			      else
				  temp = TRUEP(Nil);
			      if (temp) {
				  gensymed_symbol_3 = 
					  lookup_global_or_kb_specific_property_value(attribute_initial_type,
					  Class_description_gkbprop);
				  if (gensymed_symbol_3 ? 
					  TRUEP(memq_function(class_type_qm,
					  ISVREF(gensymed_symbol_3,
					  (SI_Long)2L))) : TRUEP(Nil))
				      delete_from_frame_note_particulars_list(attribute_name,
					      Qinitial_value_class_incompatible_with_type,
					      class_definition);
				  else
				      add_to_frame_note_particulars_list_if_necessary(attribute_name,
					      Qinitial_value_class_incompatible_with_type,
					      class_definition);
			      }
			  }
			  check_for_undefined_class(attribute_initial_type);
		      }
		      goto next_loop_2;
		    end_loop_2:;
		      cons_holding_validity_interval_override_qm = 
			      member(4,Qvalidity_interval,
			      default_overrides,Ktest,Qcar_eq);
		      cons_holding_data_server_map_override_qm = member(4,
			      Qdata_server_map,default_overrides,Ktest,
			      Qcar_eq);
		      if (cons_holding_validity_interval_override_qm || 
			      cons_holding_data_server_map_override_qm) {
			  if (cons_holding_validity_interval_override_qm) {
			      temp_1 = 
				      CAR(cons_holding_validity_interval_override_qm);
			      real_or_implied_validity_interval_value = 
				      SECOND(temp_1);
			  }
			  else if (class_description_qm) {
			      skip_list = CDR(Symbol_properties_table);
			      key_value = class_name_qm;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(class_name_qm) & 
				      IFIX(Most_positive_fixnum);
			      bottom_level = (SI_Long)0L;
			      marked = Nil;
			      pred = M_CAR(skip_list);
			      curr = Nil;
			      succ = Nil;
			      level = (SI_Long)31L;
			      ab_loop_bind_ = bottom_level;
			    next_loop_27:
			      if (level < ab_loop_bind_)
				  goto end_loop_27;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_28:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_29:
			      if ( !TRUEP(marked))
				  goto end_loop_28;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_29;
			    end_loop_28:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_9;
			      goto next_loop_28;
			    end_loop_29:
			    end_9:
			      level = level - (SI_Long)1L;
			      goto next_loop_27;
			    end_loop_27:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = class_name_qm;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			    next_loop_30:
			      if (level < ab_loop_bind_)
				  goto end_loop_30;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_31:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_32:
			      if ( !TRUEP(marked))
				  goto end_loop_31;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_32;
			    end_loop_31:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_10;
			      goto next_loop_31;
			    end_loop_32:
			    end_10:
			      level = level - (SI_Long)1L;
			      goto next_loop_30;
			    end_loop_30:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_33:
				  if (level < ab_loop_bind_)
				      goto end_loop_33;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_34:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_35:
				  if ( !TRUEP(marked))
				      goto end_loop_34;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_35;
				end_loop_34:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_11;
				  goto next_loop_34;
				end_loop_35:
				end_11:
				  level = level - (SI_Long)1L;
				  goto next_loop_33;
				end_loop_33:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_36:
				  if (level < ab_loop_bind_)
				      goto end_loop_36;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_37:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_38:
				  if ( !TRUEP(marked))
				      goto end_loop_37;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_38;
				end_loop_37:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_12;
				  goto next_loop_37;
				end_loop_38:
				end_12:
				  level = level - (SI_Long)1L;
				  goto next_loop_36;
				end_loop_36:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      gensymed_symbol_3 = resulting_value;
			      slot_description_qm = 
				      get_slot_description_of_class_description_function(Qvalidity_interval,
				      gensymed_symbol_3,Nil);
			      real_or_implied_validity_interval_value = 
				      slot_description_qm ? 
				      ISVREF(slot_description_qm,
				      (SI_Long)6L) : Qnil;
			  }
			  else {
			      skip_list = CDR(Symbol_properties_table);
			      key_value = Qg2_variable;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(Qg2_variable) & 
				      IFIX(Most_positive_fixnum);
			      bottom_level = (SI_Long)0L;
			      marked = Nil;
			      pred = M_CAR(skip_list);
			      curr = Nil;
			      succ = Nil;
			      level = (SI_Long)31L;
			      ab_loop_bind_ = bottom_level;
			    next_loop_39:
			      if (level < ab_loop_bind_)
				  goto end_loop_39;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_40:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_41:
			      if ( !TRUEP(marked))
				  goto end_loop_40;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_41;
			    end_loop_40:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_13;
			      goto next_loop_40;
			    end_loop_41:
			    end_13:
			      level = level - (SI_Long)1L;
			      goto next_loop_39;
			    end_loop_39:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = Qg2_variable;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			    next_loop_42:
			      if (level < ab_loop_bind_)
				  goto end_loop_42;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_43:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_44:
			      if ( !TRUEP(marked))
				  goto end_loop_43;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_44;
			    end_loop_43:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_14;
			      goto next_loop_43;
			    end_loop_44:
			    end_14:
			      level = level - (SI_Long)1L;
			      goto next_loop_42;
			    end_loop_42:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_45:
				  if (level < ab_loop_bind_)
				      goto end_loop_45;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_46:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_47:
				  if ( !TRUEP(marked))
				      goto end_loop_46;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_47;
				end_loop_46:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_15;
				  goto next_loop_46;
				end_loop_47:
				end_15:
				  level = level - (SI_Long)1L;
				  goto next_loop_45;
				end_loop_45:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_48:
				  if (level < ab_loop_bind_)
				      goto end_loop_48;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_49:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_50:
				  if ( !TRUEP(marked))
				      goto end_loop_49;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_50;
				end_loop_49:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_16;
				  goto next_loop_49;
				end_loop_50:
				end_16:
				  level = level - (SI_Long)1L;
				  goto next_loop_48;
				end_loop_48:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      gensymed_symbol_3 = resulting_value;
			      real_or_implied_validity_interval_value = 
				      ISVREF(get_slot_description_of_class_description_function(Qvalidity_interval,
				      gensymed_symbol_3,Nil),(SI_Long)6L);
			  }
			  if (cons_holding_data_server_map_override_qm) {
			      temp_1 = 
				      CAR(cons_holding_data_server_map_override_qm);
			      real_or_implied_data_server_map_value = 
				      SECOND(temp_1);
			  }
			  else if (class_description_qm) {
			      skip_list = CDR(Symbol_properties_table);
			      key_value = class_name_qm;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(class_name_qm) & 
				      IFIX(Most_positive_fixnum);
			      bottom_level = (SI_Long)0L;
			      marked = Nil;
			      pred = M_CAR(skip_list);
			      curr = Nil;
			      succ = Nil;
			      level = (SI_Long)31L;
			      ab_loop_bind_ = bottom_level;
			    next_loop_51:
			      if (level < ab_loop_bind_)
				  goto end_loop_51;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_52:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_53:
			      if ( !TRUEP(marked))
				  goto end_loop_52;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_53;
			    end_loop_52:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_17;
			      goto next_loop_52;
			    end_loop_53:
			    end_17:
			      level = level - (SI_Long)1L;
			      goto next_loop_51;
			    end_loop_51:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = class_name_qm;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			    next_loop_54:
			      if (level < ab_loop_bind_)
				  goto end_loop_54;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_55:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_56:
			      if ( !TRUEP(marked))
				  goto end_loop_55;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_56;
			    end_loop_55:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_18;
			      goto next_loop_55;
			    end_loop_56:
			    end_18:
			      level = level - (SI_Long)1L;
			      goto next_loop_54;
			    end_loop_54:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_57:
				  if (level < ab_loop_bind_)
				      goto end_loop_57;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_58:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_59:
				  if ( !TRUEP(marked))
				      goto end_loop_58;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_59;
				end_loop_58:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_19;
				  goto next_loop_58;
				end_loop_59:
				end_19:
				  level = level - (SI_Long)1L;
				  goto next_loop_57;
				end_loop_57:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_60:
				  if (level < ab_loop_bind_)
				      goto end_loop_60;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_61:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_62:
				  if ( !TRUEP(marked))
				      goto end_loop_61;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_62;
				end_loop_61:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_20;
				  goto next_loop_61;
				end_loop_62:
				end_20:
				  level = level - (SI_Long)1L;
				  goto next_loop_60;
				end_loop_60:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      gensymed_symbol_3 = resulting_value;
			      slot_description_qm = 
				      get_slot_description_of_class_description_function(Qdata_server_map,
				      gensymed_symbol_3,Nil);
			      real_or_implied_data_server_map_value = 
				      slot_description_qm ? 
				      ISVREF(slot_description_qm,
				      (SI_Long)6L) : Qnil;
			  }
			  else {
			      skip_list = CDR(Symbol_properties_table);
			      key_value = Qg2_variable;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(Qg2_variable) & 
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
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_64:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_65:
			      if ( !TRUEP(marked))
				  goto end_loop_64;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_65;
			    end_loop_64:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_21;
			      goto next_loop_64;
			    end_loop_65:
			    end_21:
			      level = level - (SI_Long)1L;
			      goto next_loop_63;
			    end_loop_63:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = Qg2_variable;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_67:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_68:
			      if ( !TRUEP(marked))
				  goto end_loop_67;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_68;
			    end_loop_67:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_22;
			      goto next_loop_67;
			    end_loop_68:
			    end_22:
			      level = level - (SI_Long)1L;
			      goto next_loop_66;
			    end_loop_66:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
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
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_70:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_71:
				  if ( !TRUEP(marked))
				      goto end_loop_70;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_71;
				end_loop_70:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_23;
				  goto next_loop_70;
				end_loop_71:
				end_23:
				  level = level - (SI_Long)1L;
				  goto next_loop_69;
				end_loop_69:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
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
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_73:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_74:
				  if ( !TRUEP(marked))
				      goto end_loop_73;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_74;
				end_loop_73:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_24;
				  goto next_loop_73;
				end_loop_74:
				end_24:
				  level = level - (SI_Long)1L;
				  goto next_loop_72;
				end_loop_72:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      gensymed_symbol_3 = resulting_value;
			      real_or_implied_data_server_map_value = 
				      ISVREF(get_slot_description_of_class_description_function(Qdata_server_map,
				      gensymed_symbol_3,Nil),(SI_Long)6L);
			  }
			  if (EQ(real_or_implied_validity_interval_value,
				  Qsupplied)) {
			      if ( 
				      !EQ(real_or_implied_data_server_map_value,
				      Qcomputation))
				  add_frame_note(2,
					  Qincompatible_validity_interval_and_data_server,
					  class_definition);
			  }
		      }
		      override = Nil;
		      ab_loop_list_ = default_overrides;
		      class_to_instantiate_qm = Nil;
		    next_loop_75:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_75;
		      override = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      class_to_instantiate_qm = 
			      class_to_instantiate_for_override(override);
		      if (class_to_instantiate_qm) {
			  check_for_undefined_class(class_to_instantiate_qm);
			  if (SYMBOLP(class_to_instantiate_qm)) {
			      skip_list = CDR(Symbol_properties_table);
			      key_value = class_to_instantiate_qm;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(class_to_instantiate_qm) 
				      & IFIX(Most_positive_fixnum);
			      bottom_level = (SI_Long)0L;
			      marked = Nil;
			      pred = M_CAR(skip_list);
			      curr = Nil;
			      succ = Nil;
			      level = (SI_Long)31L;
			      ab_loop_bind_ = bottom_level;
			    next_loop_76:
			      if (level < ab_loop_bind_)
				  goto end_loop_76;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_77:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_78:
			      if ( !TRUEP(marked))
				  goto end_loop_77;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_78;
			    end_loop_77:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_25;
			      goto next_loop_77;
			    end_loop_78:
			    end_25:
			      level = level - (SI_Long)1L;
			      goto next_loop_76;
			    end_loop_76:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = class_to_instantiate_qm;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			    next_loop_79:
			      if (level < ab_loop_bind_)
				  goto end_loop_79;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_80:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_81:
			      if ( !TRUEP(marked))
				  goto end_loop_80;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_81;
			    end_loop_80:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_26;
			      goto next_loop_80;
			    end_loop_81:
			    end_26:
			      level = level - (SI_Long)1L;
			      goto next_loop_79;
			    end_loop_79:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_82:
				  if (level < ab_loop_bind_)
				      goto end_loop_82;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_83:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_84:
				  if ( !TRUEP(marked))
				      goto end_loop_83;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_84;
				end_loop_83:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_27;
				  goto next_loop_83;
				end_loop_84:
				end_27:
				  level = level - (SI_Long)1L;
				  goto next_loop_82;
				end_loop_82:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_85:
				  if (level < ab_loop_bind_)
				      goto end_loop_85;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_86:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_87:
				  if ( !TRUEP(marked))
				      goto end_loop_86;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_87;
				end_loop_86:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_28;
				  goto next_loop_86;
				end_loop_87:
				end_28:
				  level = level - (SI_Long)1L;
				  goto next_loop_85;
				end_loop_85:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      temp = TRUEP(resulting_value);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp ? TRUEP(class_description_qm) : 
				      TRUEP(Nil)) {
			      name_denotation = M_CAR(override);
			      pretty_slot_name = CONSP(name_denotation) ? 
				      M_CAR(M_CDR(M_CDR(name_denotation))) 
				      : name_denotation;
			      defining_class = CONSP(name_denotation) ? 
				      M_CAR(M_CDR(name_denotation)) : Nil;
			      skip_list = CDR(Symbol_properties_table);
			      key_value = class_name_qm;
			      key_hash_value = 
				      SXHASH_SYMBOL_1(class_name_qm) & 
				      IFIX(Most_positive_fixnum);
			      bottom_level = (SI_Long)0L;
			      marked = Nil;
			      pred = M_CAR(skip_list);
			      curr = Nil;
			      succ = Nil;
			      level = (SI_Long)31L;
			      ab_loop_bind_ = bottom_level;
			    next_loop_88:
			      if (level < ab_loop_bind_)
				  goto end_loop_88;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_89:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_90:
			      if ( !TRUEP(marked))
				  goto end_loop_89;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_90;
			    end_loop_89:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_29;
			      goto next_loop_89;
			    end_loop_90:
			    end_29:
			      level = level - (SI_Long)1L;
			      goto next_loop_88;
			    end_loop_88:;
			      gensymed_symbol_3 = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if ( !TRUEP(gensymed_symbol_3)) {
				  gensymed_symbol_3 = class_name_qm;
				  temp_2 = Symbol_properties_table;
				  temp_1 = 
					  FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
					  & IFIX(Most_positive_fixnum));
				  tail = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					  Nil);
				  head = 
					  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					  tail);
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_4 = new_cons;
				  }
				  else
				      gensymed_symbol_4 = Nil;
				  if ( !TRUEP(gensymed_symbol_4))
				      gensymed_symbol_4 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_4) = 
					  Qsymbol_properties_hash_table;
				  new_cons = 
					  ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      svref_arg_1 = 
					      Available_lookup_conses_vector;
				      svref_arg_2 = Current_thread_index;
				      svref_new_value = M_CDR(new_cons);
				      SVREF(svref_arg_1,svref_arg_2) = 
					      svref_new_value;
				      if ( 
					      !TRUEP(ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index)))) {
					  svref_arg_1 = 
						  Available_lookup_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(svref_arg_1,svref_arg_2) = Nil;
				      }
				      gensymed_symbol_5 = new_cons;
				  }
				  else
				      gensymed_symbol_5 = Nil;
				  if ( !TRUEP(gensymed_symbol_5))
				      gensymed_symbol_5 = 
					      replenish_lookup_cons_pool();
				  M_CAR(gensymed_symbol_5) = head;
				  M_CDR(gensymed_symbol_5) = tail;
				  inline_note_allocate_cons(gensymed_symbol_5,
					  Qlookup);
				  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				  inline_note_allocate_cons(gensymed_symbol_4,
					  Qlookup);
				  gensymed_symbol_3 = 
					  set_skip_list_entry(temp_2,
					  FIX((SI_Long)31L),Qeq,Nil,T,
					  gensymed_symbol_3,temp_1,
					  gensymed_symbol_4);
			      }
			      global_properties = gensymed_symbol_3;
			      skip_list = CDR(global_properties);
			      key_value = 
				      Current_kb_specific_property_list_property_name;
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
			    next_loop_91:
			      if (level < ab_loop_bind_)
				  goto end_loop_91;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_92:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_93:
			      if ( !TRUEP(marked))
				  goto end_loop_92;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_93;
			    end_loop_92:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_30;
			      goto next_loop_92;
			    end_loop_93:
			    end_30:
			      level = level - (SI_Long)1L;
			      goto next_loop_91;
			    end_loop_91:;
			      kb_properties = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_properties);
			      else
				  kb_properties = Nil;
			      if (kb_properties) {
				  skip_list = CDR(kb_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_94:
				  if (level < ab_loop_bind_)
				      goto end_loop_94;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_95:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_96:
				  if ( !TRUEP(marked))
				      goto end_loop_95;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_96;
				end_loop_95:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_31;
				  goto next_loop_95;
				end_loop_96:
				end_31:
				  level = level - (SI_Long)1L;
				  goto next_loop_94;
				end_loop_94:;
				  kb_specific_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (kb_specific_value);
				  else
				      kb_specific_value = 
					      No_specific_property_value;
			      }
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			      if ( !EQ(kb_specific_value,
				      No_specific_property_value))
				  resulting_value = kb_specific_value;
			      else {
				  skip_list = CDR(global_properties);
				  key_value = Class_description_gkbprop;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(Class_description_gkbprop) 
					  & IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_97:
				  if (level < ab_loop_bind_)
				      goto end_loop_97;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_98:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_99:
				  if ( !TRUEP(marked))
				      goto end_loop_98;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_99;
				end_loop_98:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_32;
				  goto next_loop_98;
				end_loop_99:
				end_32:
				  level = level - (SI_Long)1L;
				  goto next_loop_97;
				end_loop_97:;
				  resulting_value = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if (resulting_value);
				  else
				      resulting_value = Nil;
			      }
			      gensymed_symbol_3 = resulting_value;
			      slot_description_qm = 
				      get_slot_description_of_class_description_function(pretty_slot_name,
				      gensymed_symbol_3,defining_class);
			      if (slot_description_qm) {
				  if (class_in_attribute_conforms_to_type_p(4,
					  slot_description_qm,
					  class_name_qm,T,
					  ISVREF(slot_description_qm,
					  (SI_Long)6L)))
				      delete_from_frame_note_particulars_list(name_denotation,
					      Qoverride_value_is_not_compatible,
					      class_definition);
				  else
				      add_to_frame_note_particulars_list_if_necessary(copy_for_slot_value(name_denotation),
					      Qoverride_value_is_not_compatible,
					      class_definition);
			      }
			  }
		      }
		      goto next_loop_75;
		    end_loop_75:;
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(class_definition));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-DRAWING-PARAMETERS */
Object analyze_for_consistency_for_drawing_parameters(drawing_parameters,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object drawing_parameters, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object image_palette, image_name_qm, compiled_item_being_analyzed;
    Object object_configuration_qm, frame, sub_vector_qm, function_qm;
    SI_Long method_index;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,153);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
		1);
	  if (Defer_consistency_analysis_qm &&  
		  !TRUEP(Add_as_item_referring_to_name_qm) &&  
		  !TRUEP(Delete_as_item_referring_to_name_qm))
	      result = defer_consistency_analysis_of_item(Drawing_parameters);
	  else {
	      LOCK(Analyze_for_consistency_in_progress);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  if ( !TRUEP(Loading_kb_p)) {
		      image_palette = ISVREF(Drawing_parameters,(SI_Long)24L);
		      image_name_qm = CONSP(image_palette) ? 
			      SECOND(image_palette) : Qnil;
		      delete_all_consistency_analysis_frame_notes(1,
			      Drawing_parameters);
		      compiled_item_being_analyzed = Drawing_parameters;
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			      0);
			object_configuration_qm = 
				get_lookup_slot_value(Drawing_parameters,
				Qobject_configuration);
			if (object_configuration_qm)
			    map_over_external_names_in_object_configuration(SYMBOL_FUNCTION(Qcheck_undefined_instances_of_class),
				    object_configuration_qm);
			if (image_name_qm)
			    check_undefined_instances_of_class(image_name_qm,
				    Qimage_definition);
		      POP_SPECIAL();
		      if (system_table_installed_p(Drawing_parameters) && 
			      (Add_as_item_referring_to_name_qm ||  
			      !TRUEP(Add_as_item_referring_to_name_qm) &&  
			      !TRUEP(Delete_as_item_referring_to_name_qm)) 
			      &&  !((SI_Long)0L != 
			      (IFIX(ISVREF(Drawing_parameters,
			      (SI_Long)5L)) & (SI_Long)512L))) {
			  method_index = (SI_Long)19L;
			  frame = Drawing_parameters;
			  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,
				  (SI_Long)1L),(SI_Long)11L),method_index);
			  function_qm = sub_vector_qm ? 
				  ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
			  if (function_qm)
			      inline_funcall_1(function_qm,frame);
			  if (Post_kb_loading_consistency_analysis)
			      post_analyzer_warning_note_if_necessary(Drawing_parameters);
			  if ( !TRUEP(Loading_kb_p))
			      SAVE_VALUES(propagate_image_palette_to_all_gensym_windows(image_palette));
			  else
			      SAVE_VALUES(VALUES_1(Nil));
		      }
		      else
			  SAVE_VALUES(VALUES_1(Nil));
		  }
		  else
		      SAVE_VALUES(VALUES_1(Nil));
	      }
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Analyze_for_consistency_in_progress);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	  }
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qframe_style;        /* frame-style */

static Object Qframe_style_definition;  /* frame-style-definition */

/* ANALYZE-FOR-CONSISTENCY-FOR-KB-WORKSPACE */
Object analyze_for_consistency_for_kb_workspace(kb_workspace,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object kb_workspace, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, object_configuration_qm, image_name;
    Object ab_loop_list_, ab_loop_desetq_;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,154);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(kb_workspace);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    kb_workspace);
		    compiled_item_being_analyzed = kb_workspace;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    0);
		      object_configuration_qm = 
			      get_lookup_slot_value(kb_workspace,
			      Qobject_configuration);
		      if (object_configuration_qm)
			  map_over_external_names_in_object_configuration(SYMBOL_FUNCTION(Qcheck_undefined_instances_of_class),
				  object_configuration_qm);
		      image_name = Nil;
		      ab_loop_list_ = 
			      workspace_background_images(kb_workspace);
		      ab_loop_desetq_ = Nil;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      ab_loop_desetq_ = M_CAR(ab_loop_list_);
		      image_name = CAR(ab_loop_desetq_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      check_undefined_instances_of_class(image_name,
			      Qimage_definition);
		      goto next_loop;
		    end_loop:;
		      if (get_lookup_slot_value(kb_workspace,Qframe_style))
			  check_undefined_instances_of_class(get_lookup_slot_value(kb_workspace,
				  Qframe_style),Qframe_style_definition);
		    POP_SPECIAL();
		    post_analyzer_warning_note_if_necessary(kb_workspace);
		    if ((Post_kb_loading_consistency_analysis ||  
			    !TRUEP(Add_as_item_referring_to_name_qm) &&  
			    !TRUEP(Delete_as_item_referring_to_name_qm)) 
			    &&  !((SI_Long)0L != (IFIX(ISVREF(kb_workspace,
			    (SI_Long)5L)) & (SI_Long)512L))) {
			reconsider_formatting(kb_workspace);
			SAVE_VALUES(refresh_background_images(kb_workspace));
		    }
		    else
			SAVE_VALUES(VALUES_1(Nil));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-GENERIC-FORMULA */
Object analyze_for_consistency_for_generic_formula(generic_formula,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object generic_formula, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object temp, temp_1;
    char formula_is_incomplete_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,155);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(generic_formula);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = ISVREF(generic_formula,(SI_Long)16L);
		formula_is_incomplete_qm = EQ(CAR(temp),No_value);
		if ( !formula_is_incomplete_qm) {
		    temp = ISVREF(generic_formula,(SI_Long)16L);
		    temp = CAR(temp);
		    temp_1 = SECOND(temp);
		}
		else
		    temp_1 = Nil;
		if ( !formula_is_incomplete_qm) {
		    temp = ISVREF(generic_formula,(SI_Long)16L);
		    temp = CAR(temp);
		    temp = FIRST(temp);
		}
		else
		    temp = Nil;
		SAVE_VALUES(analyze_formula_for_consistency(generic_formula,
			temp_1,temp,Nil,Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_79;  /* "a validity interval of \"supplied\" (the default value) is only valid ~
				    *      when the data server is \"inference engine\""
				    */

/* WRITE-INCOMPATIBLE-VALIDITY-INTERVAL-AND-DATA-SERVER-NOTE */
Object write_incompatible_validity_interval_and_data_server_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(179,156);
    GENSYM_RETURN_ONE(tformat(1,string_constant_79));
    return VALUES_1(Nil);
}

/* ANALYZE-FOR-CONSISTENCY-FOR-VARIABLE */
Object analyze_for_consistency_for_variable(variable,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object variable, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object current_computation_component_particulars;
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    Object cell_array_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,157);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(variable);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    current_computation_component_particulars = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			    0);
		      delete_all_consistency_analysis_frame_notes(1,variable);
		      delete_all_consistency_analysis_frame_notes(2,
			      variable,T);
		    POP_SPECIAL();
		    compiled_item_being_analyzed = variable;
		    compiled_item_being_analyzed_started_out_incomplete_qm 
			    = frame_incomplete_p(variable);
		    cell_array_qm = 
			    get_lookup_slot_value_given_default(variable,
			    Qcell_array,Nil);
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			      0);
			if (cell_array_qm) {
			    if ( 
				    !TRUEP(Delete_as_item_referring_to_name_qm) 
				    && frame_incomplete_p(variable) && 
				    g2_cell_array_expression_cells_have_byte_code_bodies_p(cell_array_qm))
				update_frame_status(variable,Nil,Nil);
			    analyze_g2_cell_array_for_consistency(cell_array_qm);
			}
			if (EQ(ISVREF(variable,(SI_Long)27L),Qsupplied)) {
			    if ( !EQ(ISVREF(variable,(SI_Long)31L),
				    Qcomputation))
				add_frame_note(2,
					Qincompatible_validity_interval_and_data_server,
					variable);
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(variable));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-GENERIC-SIMULATION-FORMULA */
Object analyze_for_consistency_for_generic_simulation_formula(generic_simulation_formula,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object generic_simulation_formula, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object temp, temp_1, temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,158);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(generic_simulation_formula);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = ISVREF(generic_simulation_formula,(SI_Long)16L);
		temp_1 = CAR(temp);
		temp = ISVREF(generic_simulation_formula,(SI_Long)16L);
		temp_2 = CAR(temp);
		temp = ISVREF(generic_simulation_formula,(SI_Long)16L);
		SAVE_VALUES(analyze_formula_for_consistency(generic_simulation_formula,
			SECOND(temp_1),FIRST(temp_2),Nil,SEVENTH(CAR(temp))));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* INITIALIZE-AFTER-READING-FOR-GENERIC-SIMULATION-FORMULA */
Object initialize_after_reading_for_generic_simulation_formula(generic_simulation_formula)
    Object generic_simulation_formula;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(179,159);
    frame = generic_simulation_formula;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgeneric_simulation_formula)) {
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
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(ISVREF(generic_simulation_formula,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)16L),(SI_Long)1L);
    gensymed_symbol_1 = generic_simulation_formula;
    gensymed_symbol_2 = ISVREF(generic_simulation_formula,(SI_Long)16L);
    gensymed_symbol_3 = Nil;
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

static Object list_constant;       /* # */

static Object Qcell_array_element;  /* cell-array-element */

/* ANALYZE-FORMULA-FOR-CONSISTENCY */
Object analyze_formula_for_consistency(formula,formula_class_or_item,
	    formula_role,form_to_analyze,left_side_of_formula_qm)
    Object formula, formula_class_or_item, formula_role, form_to_analyze;
    Object left_side_of_formula_qm;
{
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm, temp;
    Object item_needs_recompile_qm, alist, byte_code_body_qm;
    Object initial_value_byte_code_body_qm;
    Object initial_value_component_particulars_qm, cell_array_qm;
    Object sub_class_bit_vector, current_computation_component_particulars;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char formula_class_case_qm, temp_1;
    Declare_special(3);

    x_note_fn_call(179,160);
    if ( !TRUEP(Loading_kb_p)) {
	delete_all_consistency_analysis_frame_notes(1,formula);
	delete_all_consistency_analysis_frame_notes(2,formula,T);
	compiled_item_being_analyzed = formula;
	PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
		2);
	  compiled_item_being_analyzed_started_out_incomplete_qm = 
		  frame_incomplete_p(formula);
	  PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
		  1);
	    if (Compiled_item_being_analyzed_started_out_incomplete_qm) {
		temp = ISVREF(formula,(SI_Long)16L);
		item_needs_recompile_qm = EQ(CAR(temp),No_value) ? T : Nil;
	    }
	    else
		item_needs_recompile_qm = Nil;
	    formula_class_case_qm = SYMBOLP(formula_class_or_item);
	    alist = formula_class_case_qm ? 
		    installation_cons_1(installation_cons_1(formula_class_or_item,
		    formula_class_or_item),Nil) : Nil;
	    byte_code_body_qm = Nil;
	    initial_value_byte_code_body_qm = Nil;
	    initial_value_component_particulars_qm = Nil;
	    cell_array_qm = Nil;
	    sub_class_bit_vector = ISVREF(ISVREF(formula,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_simulation_formula_class_description,
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
	    if (temp_1) {
		byte_code_body_qm = ISVREF(formula,(SI_Long)20L);
		initial_value_byte_code_body_qm = ISVREF(formula,(SI_Long)21L);
		initial_value_component_particulars_qm = list_constant;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(formula,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_formula_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    cell_array_qm = 
			    get_lookup_slot_value_given_default(formula,
			    Qcell_array,Nil);
	    }
	    if (left_side_of_formula_qm) {
		analyze_compiled_form(left_side_of_formula_qm,alist,Nil);
		if (formula_class_case_qm && formula_class_or_item)
		    check_for_undefined_class(formula_class_or_item);
	    }
	    else if (formula_class_case_qm && formula_class_or_item && 
		    formula_role) {
		current_computation_component_particulars = 
			slot_value_list_2(Qcell_array_element,
			expression_cell_element_for_generic_formula(formula));
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			0);
		  check_for_undefined_class(formula_class_or_item);
		  check_for_undefined_attribute_of_class(formula_role,
			  formula_class_or_item);
		  reclaim_slot_value_list_1(Current_computation_component_particulars);
		POP_SPECIAL();
	    }
	    if (form_to_analyze)
		analyze_compiled_form(form_to_analyze,alist,Nil);
	    if (alist)
		reclaim_installation_tree_1(alist);
	    if (byte_code_body_qm) {
		if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
			!TRUEP(item_needs_recompile_qm) && 
			frame_incomplete_p(formula))
		    update_frame_status(formula,Nil,Nil);
		analyze_byte_code_body_for_free_reference_consistency(byte_code_body_qm);
	    }
	    if (initial_value_byte_code_body_qm) {
		current_computation_component_particulars = 
			initial_value_component_particulars_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			0);
		  analyze_byte_code_body_for_free_reference_consistency(initial_value_byte_code_body_qm);
		POP_SPECIAL();
	    }
	    if (cell_array_qm) {
		if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
			!TRUEP(item_needs_recompile_qm) && 
			frame_incomplete_p(formula) && 
			g2_cell_array_expression_cells_have_byte_code_bodies_p(cell_array_qm))
		    update_frame_status(formula,Nil,Nil);
		analyze_g2_cell_array_for_consistency(cell_array_qm);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	if ( !TRUEP(left_side_of_formula_qm))
	    return post_analyzer_warning_note_if_necessary(formula);
	else
	    return post_analyzer_warning_note_for_generic_simulation_formula(formula);
    }
    else
	return VALUES_1(Nil);
}

/* ANALYZE-FOR-CONSISTENCY-FOR-FUNCTION-DEFINITION */
Object analyze_for_consistency_for_function_definition(function_definition,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object function_definition, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    Object byte_code_body_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,161);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(function_definition);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    function_definition);
		    compiled_item_being_analyzed = function_definition;
		    compiled_item_being_analyzed_started_out_incomplete_qm 
			    = frame_incomplete_p(function_definition);
		    byte_code_body_qm = ISVREF(function_definition,
			    (SI_Long)20L);
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			      0);
			if (byte_code_body_qm) {
			    if ( 
				    !TRUEP(Delete_as_item_referring_to_name_qm) 
				    && frame_incomplete_p(function_definition))
				update_frame_status(function_definition,
					Nil,Nil);
			    analyze_byte_code_body_for_free_reference_consistency(byte_code_body_qm);
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(function_definition));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-READOUT-TABLE */
Object analyze_for_consistency_for_readout_table(readout_table,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object readout_table, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,162);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(readout_table);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_display_for_consistency(readout_table));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-DIAL */
Object analyze_for_consistency_for_dial(dial,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object dial, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,163);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(dial);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_display_for_consistency(dial));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-METER */
Object analyze_for_consistency_for_meter(meter,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object meter, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,164);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(meter);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_display_for_consistency(meter));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-DISPLAY-FOR-CONSISTENCY */
Object analyze_display_for_consistency(display)
    Object display;
{
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    Object cell_array_qm;
    Declare_special(2);

    x_note_fn_call(179,165);
    if ( !TRUEP(Loading_kb_p)) {
	delete_all_consistency_analysis_frame_notes(2,display,T);
	delete_all_consistency_analysis_frame_notes(1,display);
	compiled_item_being_analyzed = display;
	compiled_item_being_analyzed_started_out_incomplete_qm = 
		frame_incomplete_p(display);
	cell_array_qm = get_lookup_slot_value_given_default(display,
		Qcell_array,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
		  0);
	    if (cell_array_qm) {
		if ( !TRUEP(Delete_as_item_referring_to_name_qm) && 
			frame_incomplete_p(display) && 
			g2_cell_array_expression_cells_have_byte_code_bodies_p(cell_array_qm))
		    update_frame_status(display,Nil,Nil);
		analyze_g2_cell_array_for_consistency(cell_array_qm);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	return post_analyzer_warning_note_if_necessary(display);
    }
    else
	return VALUES_1(Nil);
}

static Object Qslot_component;     /* slot-component */

static Object Qtrend_chart_point_formats;  /* trend-chart-point-formats */

static Object Qpoint_style;        /* point-style */

static Object Qcustom;             /* custom */

static Object Qicon_class;         /* icon-class */

/* ANALYZE-FOR-CONSISTENCY-FOR-TREND-CHART */
Object analyze_for_consistency_for_trend_chart(trend_chart,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object trend_chart, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, temp, ab_loopvar_, point_format;
    Object indicator, current_computation_component_particulars, marker_style;
    Object value_in_instance;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,166);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(trend_chart);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		analyze_display_for_consistency(trend_chart);
		compiled_item_being_analyzed = trend_chart;
		PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			1);
		  temp = ISVREF(trend_chart,(SI_Long)20L);
		  ab_loopvar_ = CDDR(temp);
		  point_format = Nil;
		  indicator = Nil;
		  current_computation_component_particulars = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			  0);
		    marker_style = Nil;
		  next_loop:
		    if ( !TRUEP(ab_loopvar_))
			goto end_loop;
		    point_format = M_CAR(ab_loopvar_);
		    ab_loopvar_ = M_CDR(ab_loopvar_);
		    indicator = CAR(point_format);
		    Current_computation_component_particulars = 
			    slot_value_list_4(Qslot_component,
			    Qtrend_chart_point_formats,Nil,indicator);
		    value_in_instance = getfq_function(CDDR(point_format),
			    Qpoint_style,Compound_type_slot_not_present);
		    marker_style = EQ(value_in_instance,
			    Compound_type_slot_not_present) ? 
			    get_default_slot_component_value_from_master_slot(point_format,
			    Qpoint_style) : value_in_instance;
		    if (EQ(CAR(marker_style),Qcustom))
			check_for_undefined_class(getf(CDDR(marker_style),
				Qicon_class,_));
		    reclaim_slot_value_list_1(Current_computation_component_particulars);
		    goto next_loop;
		  end_loop:
		    SAVE_VALUES(VALUES_1(Qnil));
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qgraph_expression;   /* graph-expression */

/* ANALYZE-FOR-CONSISTENCY-FOR-GRAPH */
Object analyze_for_consistency_for_graph(graph,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object graph, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object temp, display_expressions, compiled_item_being_analyzed;
    Object current_computation_component_particulars, graph_expression;
    Object ab_loop_list_, ab_loop_iter_flag_, cdr_arg, temp_1;
    Object graph_expression_without_info, plot_pattern_qm, plot_min_and_max_qm;
    Object temp_2;
    SI_Long expression_index;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(179,167);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      3);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(graph);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = get_lookup_slot_value_given_default(graph,
			Qexpressions_to_display,Nil);
		display_expressions = CAR(temp);
		if ( !TRUEP(Loading_kb_p) && display_expressions) {
		    delete_all_consistency_analysis_frame_notes(2,graph,T);
		    compiled_item_being_analyzed = graph;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    2);
		      if (CONSP(display_expressions) && 
			      EQ(CAR(display_expressions),Qsc)) {
			  current_computation_component_particulars = 
				  slot_value_cons_1(Qgraph_expression,
				  FIX((SI_Long)1L));
			  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
				  1);
			    graph_expression = Nil;
			    ab_loop_list_ = CDR(display_expressions);
			    expression_index = (SI_Long)1L;
			    ab_loop_iter_flag_ = T;
			  next_loop:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop;
			    graph_expression = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    if ( !TRUEP(ab_loop_iter_flag_))
				expression_index = expression_index + 
					(SI_Long)1L;
			    cdr_arg = 
				    Current_computation_component_particulars;
			    M_CDR(cdr_arg) = FIX(expression_index);
			    result = parse_graph_expression_with_info(graph_expression);
			    MVS_4(result,graph_expression_without_info,
				    temp,plot_pattern_qm,plot_min_and_max_qm);
			    PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
				    0);
			      analyze_compiled_form(graph_expression_without_info,
				      Nil,Nil);
			      reclaim_slot_value_tree_1(graph_expression_without_info);
			      if (CONSP(plot_pattern_qm))
				  reclaim_slot_value_tree_1(plot_pattern_qm);
			      if (CONSP(Plot_min_and_max_qm))
				  reclaim_slot_value(Plot_min_and_max_qm);
			    POP_SPECIAL();
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop;
			  end_loop:
			    reclaim_slot_value_cons_1(Current_computation_component_particulars);
			  POP_SPECIAL();
		      }
		      else {
			  current_computation_component_particulars = 
				  slot_value_cons_1(Qgraph_expression,
				  FIX((SI_Long)1L));
			  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
				  1);
			    result = parse_graph_expression_with_info(display_expressions);
			    MVS_4(result,graph_expression_without_info,
				    temp,plot_pattern_qm,plot_min_and_max_qm);
			    PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
				    0);
			      analyze_compiled_form(graph_expression_without_info,
				      Nil,Nil);
			      reclaim_slot_value_tree_1(graph_expression_without_info);
			      if (CONSP(plot_pattern_qm))
				  reclaim_slot_value_tree_1(plot_pattern_qm);
			      if (CONSP(Plot_min_and_max_qm))
				  reclaim_slot_value(Plot_min_and_max_qm);
			      reclaim_slot_value_cons_1(Current_computation_component_particulars);
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		    POP_SPECIAL();
		}
		SAVE_VALUES(post_analyzer_warning_note_if_necessary(graph));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-CHART */
Object analyze_for_consistency_for_chart(chart,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object chart, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object current_computation_component_particulars;
    Object compiled_item_being_analyzed, data_series, a_data_series;
    Object ab_loop_list_, designation_1, designation_2, data_series_index;
    Object ab_loop_iter_flag_, second_arg, second_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(179,168);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      5);
	PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,4);
	  if (Defer_consistency_analysis_qm &&  
		  !TRUEP(Add_as_item_referring_to_name_qm) &&  
		  !TRUEP(Delete_as_item_referring_to_name_qm))
	      result = defer_consistency_analysis_of_item(Chart);
	  else {
	      LOCK(Analyze_for_consistency_in_progress);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  if ( !TRUEP(Loading_kb_p)) {
		      current_computation_component_particulars = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			      0);
			delete_all_consistency_analysis_frame_notes(2,Chart,T);
			delete_all_consistency_analysis_frame_notes(1,Chart);
		      POP_SPECIAL();
		      compiled_item_being_analyzed = Chart;
		      data_series = ISVREF(Chart,(SI_Long)20L);
		      PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,
			      3);
			PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
				2);
			  current_computation_component_particulars = 
				  slot_value_list_2(Qdata_series,
				  FIX((SI_Long)0L));
			  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
				  1);
			    a_data_series = Nil;
			    ab_loop_list_ = Data_series;
			    designation_1 = Nil;
			    designation_2 = Nil;
			    data_series_index = FIX((SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
				    0);
			      ab_loop_iter_flag_ = T;
			    next_loop:
			      if ( !TRUEP(ab_loop_list_))
				  goto end_loop;
			      a_data_series = M_CAR(ab_loop_list_);
			      ab_loop_list_ = M_CDR(ab_loop_list_);
			      designation_1 = 
				      get_simple_part_feature(a_data_series,
				      Qdata_series_info_1);
			      designation_2 = 
				      get_simple_part_feature(a_data_series,
				      Qdata_series_info_2);
			      if ( !TRUEP(ab_loop_iter_flag_))
				  Data_series_index = 
					  FIXNUM_ADD1(Data_series_index);
			      second_arg = 
				      Current_computation_component_particulars;
			      second_new_value = Data_series_index;
			      M_SECOND(second_arg) = second_new_value;
			      if ( 
				      !TRUEP(get_simple_part_feature(a_data_series,
				      Qdata_series_failed_to_compile))) {
				  if (designation_1)
				      analyze_compiled_form(designation_1,
					      Nil,Nil);
				  if (designation_2)
				      analyze_compiled_form(designation_2,
					      Nil,Nil);
			      }
			      ab_loop_iter_flag_ = Nil;
			      goto next_loop;
			    end_loop:
			      reclaim_slot_value_list_1(Current_computation_component_particulars);
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		      SAVE_VALUES(post_analyzer_warning_note_if_necessary(Chart));
		  }
		  else
		      SAVE_VALUES(VALUES_1(Nil));
	      }
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Analyze_for_consistency_in_progress);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	  }
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-NEW-TABLE */
Object analyze_for_consistency_for_new_table(new_table,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object new_table, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,169);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
	  if (Defer_consistency_analysis_qm &&  
		  !TRUEP(Add_as_item_referring_to_name_qm) &&  
		  !TRUEP(Delete_as_item_referring_to_name_qm))
	      result = defer_consistency_analysis_of_item(New_table);
	  else {
	      LOCK(Analyze_for_consistency_in_progress);
	      if (PUSH_UNWIND_PROTECT(0))
		  SAVE_VALUES(analyze_for_consistency_block_with_only_cell_array(New_table));
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Analyze_for_consistency_in_progress);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	  }
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-INTER-G2-DATA-REQUEST-HOLDER */
Object analyze_for_consistency_for_inter_g2_data_request_holder(inter_g2_data_request_holder,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object inter_g2_data_request_holder, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,170);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(inter_g2_data_request_holder);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_for_consistency_block_with_only_cell_array(inter_g2_data_request_holder));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-KB-SEARCH-STATE */
Object analyze_for_consistency_for_kb_search_state(kb_search_state,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object kb_search_state, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,171);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(kb_search_state);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_for_consistency_block_with_only_cell_array(kb_search_state));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-USER-MENU-CHOICE */
Object analyze_for_consistency_for_user_menu_choice(user_menu_choice,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object user_menu_choice, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(179,172);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      0);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(user_menu_choice);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0))
		SAVE_VALUES(analyze_for_consistency_block_with_only_cell_array(user_menu_choice));
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-PROCEDURE */
Object analyze_for_consistency_for_procedure(procedure,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object procedure, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,173);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(procedure);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,procedure);
		    compiled_item_being_analyzed = procedure;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    0);
		      analyze_procedure_for_free_reference_consistency(procedure);
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(procedure));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qmd5_identifier_qm;  /* md5-identifier? */

static Object Qparse_results_qm;   /* parse-results? */

static Object Qitem_inlineable_but_has_no_parse;  /* item-inlineable-but-has-no-parse */

/* ANALYZE-PROCEDURE-FOR-FREE-REFERENCE-CONSISTENCY */
Object analyze_procedure_for_free_reference_consistency(procedure)
    Object procedure;
{
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm, temp;
    Object first_code_body_qm, first_byte_code_body_qm;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(179,174);
    compiled_item_being_analyzed = procedure;
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
	    1);
      compiled_item_being_analyzed_started_out_incomplete_qm = 
	      frame_incomplete_p(procedure);
      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
	      0);
	temp = ISVREF(procedure,(SI_Long)28L);
	first_code_body_qm = CAR(temp);
	first_byte_code_body_qm = first_code_body_qm ? 
		ISVREF(first_code_body_qm,(SI_Long)8L) : Nil;
	if (first_byte_code_body_qm) {
	    if ( !TRUEP(Delete_as_item_referring_to_name_qm) && 
		    frame_incomplete_p(procedure))
		update_frame_status(procedure,Nil,Nil);
	    analyze_byte_code_body_for_free_reference_consistency(first_byte_code_body_qm);
	    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
		temp = ISVREF(procedure,(SI_Long)8L);
		temp_1 =  !TRUEP(CAR(temp));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ((temp_1 ? TRUEP(block_can_be_inlined_p(procedure)) : 
		    TRUEP(Nil)) ?  
		    !TRUEP(get_lookup_slot_value_given_default(procedure,
		    Qmd5_identifier_qm,Nil)) ||  
		    !TRUEP(get_lookup_slot_value_given_default(procedure,
		    Qparse_results_qm,Nil)) : TRUEP(Nil))
		result = add_frame_note(2,
			Qitem_inlineable_but_has_no_parse,procedure);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-RULE */
Object analyze_for_consistency_for_rule(rule,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object rule, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object parent_qm, sub_class_bit_vector, parent_of_embedded_rule_qm;
    Object status_of_embedded_rule_parent_qm, compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    Object byte_code_body_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,175);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(rule);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    parent_qm = get_lookup_slot_value_given_default(rule,
			    Qparent_frame,Nil);
		    if (parent_qm) {
			sub_class_bit_vector = ISVREF(ISVREF(parent_qm,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Action_button_class_description,
				(SI_Long)18L));
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
			if (temp);
			else {
			    sub_class_bit_vector = ISVREF(ISVREF(parent_qm,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(User_menu_choice_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    parent_of_embedded_rule_qm = temp ? parent_qm : Nil;
		    status_of_embedded_rule_parent_qm = 
			    parent_of_embedded_rule_qm ? 
			    button_frame_status(parent_of_embedded_rule_qm) 
			    : Nil;
		    delete_all_consistency_analysis_frame_notes(1,rule);
		    compiled_item_being_analyzed = rule;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    1);
		      compiled_item_being_analyzed_started_out_incomplete_qm 
			      = frame_incomplete_p(rule);
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
			      0);
			byte_code_body_qm = ISVREF(rule,(SI_Long)31L);
			if (byte_code_body_qm) {
			    if ( 
				    !TRUEP(Delete_as_item_referring_to_name_qm) 
				    && frame_incomplete_p(rule)) {
				if ( !TRUEP(parent_of_embedded_rule_qm))
				    update_frame_status(rule,Nil,Nil);
				else if ( 
					!TRUEP(status_of_embedded_rule_parent_qm))
				    update_frame_status(rule,Nil,Nil);
			    }
			    analyze_byte_code_body_for_free_reference_consistency(byte_code_body_qm);
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(rule));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* ANALYZE-FOR-CONSISTENCY-FOR-SIMULATION-SUBTABLE */
Object analyze_for_consistency_for_simulation_subtable(simulation_subtable,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object simulation_subtable, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    Object byte_code_body_qm, initial_value_byte_code_body_qm;
    Object current_computation_component_particulars;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(179,176);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      3);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(simulation_subtable);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    simulation_subtable);
		    compiled_item_being_analyzed = simulation_subtable;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    2);
		      compiled_item_being_analyzed_started_out_incomplete_qm 
			      = frame_incomplete_p(simulation_subtable);
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
			      1);
			byte_code_body_qm = ISVREF(simulation_subtable,
				(SI_Long)23L);
			initial_value_byte_code_body_qm = 
				ISVREF(simulation_subtable,(SI_Long)24L);
			if (byte_code_body_qm) {
			    if ( 
				    !TRUEP(Delete_as_item_referring_to_name_qm) 
				    && frame_incomplete_p(simulation_subtable))
				update_frame_status(simulation_subtable,
					Nil,Nil);
			    analyze_byte_code_body_for_free_reference_consistency(byte_code_body_qm);
			}
			if (initial_value_byte_code_body_qm) {
			    current_computation_component_particulars = 
				    list_constant;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
				    0);
			      analyze_byte_code_body_for_free_reference_consistency(initial_value_byte_code_body_qm);
			    POP_SPECIAL();
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(simulation_subtable));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qtype_in_box_variable_or_parameter;  /* type-in-box-variable-or-parameter */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* ANALYZE-FOR-CONSISTENCY-FOR-NON-ACTION-BUTTON */
Object analyze_for_consistency_for_non_action_button(non_action_button,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object non_action_button, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, designation_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,177);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(non_action_button);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    non_action_button);
		    compiled_item_being_analyzed = non_action_button;
		    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			    0);
		      designation_qm = 
			      associated_variable_designation_function_qm(non_action_button);
		      if (designation_qm) {
			  if (G2_has_v5_mode_windows_p) {
			      sub_class_bit_vector = 
				      ISVREF(ISVREF(non_action_button,
				      (SI_Long)1L),(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Type_in_box_class_description,
				      (SI_Long)18L));
			      sub_class_vector_index = 
				      superior_class_bit_number >>  -  - 
				      (SI_Long)3L;
			      if (sub_class_vector_index < 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					  {
				  gensymed_symbol = 
					  UBYTE_8_ISAREF_1(sub_class_bit_vector,
					  sub_class_vector_index);
				  gensymed_symbol_1 = (SI_Long)1L;
				  gensymed_symbol_2 = 
					  superior_class_bit_number & 
					  (SI_Long)7L;
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
			  if (temp)
			      send_ws_representations_item_virtual_attribute_change(non_action_button,
				      get_property_value_function(3,
				      get_symbol_properties_function(Qtype_in_box_variable_or_parameter),
				      Qvirtual_attribute,Nil),Nil);
			  analyze_compiled_form(designation_qm,Nil,Nil);
		      }
		    POP_SPECIAL();
		    SAVE_VALUES(post_analyzer_warning_note_if_necessary(non_action_button));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qab_class;           /* class */

/* ANALYZE-FOR-CONSISTENCY-FOR-G2-ARRAY */
Object analyze_for_consistency_for_g2_array(g2_array,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object g2_array, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object element_type, sub_class_bit_vector, compiled_item_being_analyzed;
    Object initial_values_qm, element_type_spec, temp_1;
    Object item_designation_or_value, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(179,178);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(g2_array);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    element_type = ISVREF(g2_array,(SI_Long)21L);
		    sub_class_bit_vector = ISVREF(ISVREF(g2_array,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Value_array_class_description,
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
		    if ( !temp ? 
			    TRUEP(g2_list_or_array_element_type_may_contain_item_p(element_type)) 
			    : TRUEP(Nil)) {
			compiled_item_being_analyzed = g2_array;
			initial_values_qm = ISVREF(g2_array,(SI_Long)22L);
			element_type_spec = EQ(element_type,
				Qitem_or_datum) ? element_type : 
				gensym_list_2(Qab_class,element_type);
			PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
				0);
			  delete_all_consistency_analysis_frame_notes(1,
				  g2_array);
			  if (SYMBOLP(element_type) &&  !EQ(element_type,
				  Qitem_or_datum)) {
			      if (lookup_global_or_kb_specific_property_value(element_type,
				      Class_description_gkbprop)) {
				  temp_1 = 
					  lookup_global_or_kb_specific_property_value(element_type,
					  Class_definition_gkbprop);
				  temp = CONSP(temp_1);
			      }
			      else
				  temp = TRUEP(Nil);
			      temp =  !temp;
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      check_for_undefined_class(element_type);
			  item_designation_or_value = Nil;
			  ab_loop_list_ = initial_values_qm;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  item_designation_or_value = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if (ATOM(item_designation_or_value) ? 
				  item_designation_or_value && 
				  SYMBOLP(item_designation_or_value) : 
				  TRUEP(designation_operator_or_giver_of_value_p(CAR(item_designation_or_value)))) 
				      {
			      if (SYMBOLP(item_designation_or_value))
				  check_undefined_instances_of_type(item_designation_or_value,
					  element_type_spec);
			      else
				  analyze_compiled_form(item_designation_or_value,
					  Nil,Nil);
			  }
			  goto next_loop;
			end_loop:;
			  if (CONSP(element_type_spec)) {
			      reclaim_gensym_list_1(element_type_spec);
			      element_type_spec = Nil;
			  }
			  SAVE_VALUES(post_analyzer_warning_note_if_necessary(g2_array));
			POP_SPECIAL();
		    }
		    else
			SAVE_VALUES(VALUES_1(Nil));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qtext_conversion_style;  /* text-conversion-style */

/* ANALYZE-FOR-CONSISTENCY-FOR-LANGUAGE-PARAMETERS */
Object analyze_for_consistency_for_language_parameters(language_parameters,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object language_parameters, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed, text_conversion_style_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(179,179);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	PUSH_SPECIAL_WITH_SYMBOL(Language_parameters,Qlanguage_parameters,language_parameters,
		1);
	  if (Defer_consistency_analysis_qm &&  
		  !TRUEP(Add_as_item_referring_to_name_qm) &&  
		  !TRUEP(Delete_as_item_referring_to_name_qm))
	      result = defer_consistency_analysis_of_item(Language_parameters);
	  else {
	      LOCK(Analyze_for_consistency_in_progress);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  if ( !TRUEP(Loading_kb_p)) {
		      compiled_item_being_analyzed = Language_parameters;
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			      0);
			delete_all_consistency_analysis_frame_notes(1,
				Language_parameters);
			text_conversion_style_qm = 
				get_lookup_slot_value_given_default(Language_parameters,
				Qtext_conversion_style,Nil);
			if (text_conversion_style_qm)
			    SAVE_VALUES(check_undefined_instances_of_class(text_conversion_style_qm,
				    Qtext_conversion_style));
			else
			    SAVE_VALUES(VALUES_1(Nil));
		      POP_SPECIAL();
		  }
		  else
		      SAVE_VALUES(VALUES_1(Nil));
	      }
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Analyze_for_consistency_in_progress);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	  }
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qreserved_word_p;    /* reserved-word-p */

static Object Qgiver_of_value;     /* giver-of-value */

static Object Qsimulation_variable_cache;  /* simulation-variable-cache */

static Object list_constant_1;     /* # */

/* ANALYZE-COMPILED-FORM */
Object analyze_compiled_form(form,alist,constraints)
    Object form, alist, constraints;
{
    Object temp, operator_1;

    x_note_fn_call(179,180);
    if (NUMBERP(form))
	return VALUES_1(T);
    else if ( !TRUEP(form))
	return VALUES_1(T);
    else if (SYMBOLP(form)) {
	if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(form),
		Qreserved_word_p)))
	    return analyze_instance_or_local_name(form,alist);
	else
	    return VALUES_1(Nil);
    }
    else if (text_string_p(form))
	return VALUES_1(T);
    else {
	temp = CAR(form);
	if (NUMBERP(temp))
	    return VALUES_1(T);
	else if (EQ(CAR(form),Qquote))
	    return VALUES_1(T);
	else {
	    operator_1 = CAR(form);
	    if (EQ(operator_1,Qthe))
		return analyze_the_form(form,alist,constraints);
	    else if (EQ(operator_1,Qgiver_of_value))
		return analyze_giver_of_value_form(form,alist,constraints);
	    else if (EQ(operator_1,Qsimulation_variable_cache))
		return VALUES_1(T);
	    else if (memq_function(operator_1,list_constant_1))
		return analyze_let_form(form,alist,constraints);
	    else
		return analyze_form_according_to_template(form,
			lookup_function_template(operator_1),alist,
			constraints);
	}
    }
}

/* NAME-IS-CLASS? */
Object name_is_class_qm(name,alist)
    Object name, alist;
{
    Object temp, alist_info;

    x_note_fn_call(179,181);
    temp = assq_function(name,alist);
    alist_info = CDR(temp);
    if (alist_info &&  !EQ(alist_info,T))
	return VALUES_1(alist_info);
    else
	return VALUES_1(Nil);
}

/* ANALYZE-THE-FORM */
Object analyze_the_form(form,alist,constraints)
    Object form, alist, constraints;
{
    Object temp;

    x_note_fn_call(179,182);
    temp = simple_role_of_role(SECOND(form));
    return analyze_role(temp,THIRD(form),alist);
}

/* ANALYZE-GIVER-OF-VALUE-FORM */
Object analyze_giver_of_value_form(form,alist,constraints)
    Object form, alist, constraints;
{
    x_note_fn_call(179,183);
    check_for_undefined_class(SECOND(form));
    return analyze_compiled_form(THIRD(form),alist,Nil);
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

/* ANALYZE-ROLE */
Object analyze_role(role,domain_qm,alist)
    Object role, domain_qm, alist;
{
    Object name_is_class_qm_1, constraint_info, temp, class_of_role;

    x_note_fn_call(179,184);
    if (SYMBOLP(role)) {
	if (domain_qm) {
	    if (SYMBOLP(domain_qm)) {
		analyze_compiled_form(domain_qm,alist,Nil);
		name_is_class_qm_1 = name_is_class_qm(domain_qm,alist);
		if (name_is_class_qm_1)
		    check_for_undefined_attribute_of_class(role,
			    name_is_class_qm_1);
		else
		    check_for_undefined_attribute(role);
	    }
	    else {
		constraint_info = analyze_compiled_form(domain_qm,alist,Nil);
		if (SYMBOLP(constraint_info) &&  !EQ(constraint_info,T))
		    check_for_undefined_attribute_of_class(role,
			    constraint_info);
		else
		    check_for_undefined_attribute(role);
	    }
	}
	temp = name_is_class_qm(role,alist);
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(T);
    }
    else if (EQ(CAR(role),Qclass_qualified_name)) {
	class_of_role = CONSP(role) ? M_CAR(M_CDR(role)) : Nil;
	check_for_undefined_class(class_of_role);
	return VALUES_1(class_of_role);
    }
    else if (memq_function(CAR(role),list_constant_2) || 
	    memq_function(CAR(role),list_constant_3) && 
	    memq_function(SECOND(role),
	    Internal_g2_element_types_that_can_contain_datum)) {
	analyze_compiled_form(domain_qm,alist,Nil);
	return VALUES_1(T);
    }
    else {
	analyze_compiled_form(domain_qm,alist,Nil);
	temp = last(role,_);
	class_of_role = CAR(temp);
	check_for_undefined_class(class_of_role);
	return VALUES_1(class_of_role);
    }
}

/* ANALYZE-LET-FORM */
Object analyze_let_form(form,alist,constraints)
    Object form, alist, constraints;
{
    Object binding_list, binding_count, binding, ab_loop_list_, local_name;
    Object binding_form, binding_form_constraint_info, temp;
    SI_Long i, ab_loop_bind_;
    Object result;

    x_note_fn_call(179,185);
    binding_list = SECOND(form);
    binding_count = FIX((SI_Long)0L);
    binding = Nil;
    ab_loop_list_ = binding_list;
    local_name = Nil;
    binding_form = Nil;
    binding_form_constraint_info = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    binding = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    local_name = FIRST(binding);
    binding_form = SECOND(binding);
    binding_form_constraint_info = analyze_compiled_form(binding_form,
	    alist,Nil);
    alist = installation_cons_1(installation_cons_1(local_name,
	    binding_form_constraint_info),alist);
    binding_count = FIXNUM_ADD1(binding_count);
    goto next_loop;
  end_loop:
    result = VALUES_2(alist,binding_count);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
    MVS_2(result,alist,binding_count);
    analyze_compiled_form(THIRD(form),alist,constraints);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(binding_count);
  next_loop_1:
    if (i > ab_loop_bind_)
	goto end_loop_1;
    temp = CDR(alist);
    reclaim_installation_cons_1(CAR(alist));
    reclaim_installation_cons_1(alist);
    alist = temp;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    return VALUES_1(T);
}

static Object Qrule_let;           /* rule-let */

/* ANALYZE-RULE-BODY */
Object analyze_rule_body(rule_body,alist,constraints)
    Object rule_body, alist, constraints;
{
    Object inner_body, binding_list, binding_count, binding, ab_loop_list_;
    Object local_name, binding_form, binding_form_constraint_info, temp;
    SI_Long i, ab_loop_bind_;
    char rule_has_non_context_bindings_qm;
    Object result;

    x_note_fn_call(179,186);
    rule_has_non_context_bindings_qm = EQ(CAR(rule_body),Qrule_let);
    inner_body = rule_has_non_context_bindings_qm ? THIRD(rule_body) : 
	    rule_body;
    if (rule_has_non_context_bindings_qm) {
	binding_list = SECOND(rule_body);
	binding_count = FIX((SI_Long)0L);
	binding = Nil;
	ab_loop_list_ = binding_list;
	local_name = Nil;
	binding_form = Nil;
	binding_form_constraint_info = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	binding = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	local_name = FIRST(binding);
	binding_form = SECOND(binding);
	binding_form_constraint_info = analyze_compiled_form(binding_form,
		alist,Nil);
	alist = installation_cons_1(installation_cons_1(local_name,
		binding_form_constraint_info),alist);
	binding_count = FIXNUM_ADD1(binding_count);
	goto next_loop;
      end_loop:
	result = VALUES_2(alist,binding_count);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    else
	result = VALUES_2(alist,FIX((SI_Long)0L));
    MVS_2(result,alist,binding_count);
    analyze_compiled_form(SECOND(inner_body),alist,constraints);
    analyze_rule_actions(THIRD(inner_body),alist,constraints);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(binding_count);
  next_loop_1:
    if (i > ab_loop_bind_)
	goto end_loop_1;
    temp = CDR(alist);
    reclaim_installation_cons_1(CAR(alist));
    reclaim_installation_cons_1(alist);
    alist = temp;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(alist);
    return VALUES_1(Qnil);
}

/* ANALYZE-RULE-ACTIONS */
Object analyze_rule_actions(actions,alist,constraints)
    Object actions, alist, constraints;
{
    Object action, ab_loop_list_;

    x_note_fn_call(179,187);
    action = Nil;
    ab_loop_list_ = CDR(actions);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    action = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    analyze_rule_action(action,alist,constraints);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qlet_action;         /* let-action */

static Object Qchange_icon_color;  /* change-icon-color */

static Object Qchange_color_pattern;  /* change-color-pattern */

/* ANALYZE-RULE-ACTION */
Object analyze_rule_action(action,alist,constraints)
    Object action, alist, constraints;
{
    Object action_operator;

    x_note_fn_call(179,188);
    action_operator = CAR(action);
    if (EQ(action_operator,Qlet_action))
	return analyze_let_action(action,alist,constraints);
    else if (EQ(action_operator,Qevery))
	return analyze_every_action(action,alist,constraints);
    else if (EQ(action_operator,Qchange_icon_color) || EQ(action_operator,
	    Qchange_color_pattern))
	return VALUES_1(T);
    else
	return analyze_form_according_to_template(action,
		lookup_action_template(action_operator),alist,constraints);
}

/* ANALYZE-LET-ACTION */
Object analyze_let_action(action,alist,constraints)
    Object action, alist, constraints;
{
    Object binding_list, binding_count, binding, ab_loop_list_, local_name;
    Object binding_form, binding_form_constraint_info, temp;
    SI_Long i, ab_loop_bind_;
    Object result;

    x_note_fn_call(179,189);
    binding_list = SECOND(action);
    binding_count = FIX((SI_Long)0L);
    binding = Nil;
    ab_loop_list_ = binding_list;
    local_name = Nil;
    binding_form = Nil;
    binding_form_constraint_info = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    binding = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    local_name = FIRST(binding);
    binding_form = SECOND(binding);
    binding_form_constraint_info = analyze_compiled_form(binding_form,
	    alist,Nil);
    alist = installation_cons_1(installation_cons_1(local_name,
	    binding_form_constraint_info),alist);
    binding_count = FIXNUM_ADD1(binding_count);
    goto next_loop;
  end_loop:
    result = VALUES_2(alist,binding_count);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
    MVS_2(result,alist,binding_count);
    analyze_rule_action(THIRD(action),alist,constraints);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(binding_count);
  next_loop_1:
    if (i > ab_loop_bind_)
	goto end_loop_1;
    temp = CDR(alist);
    reclaim_installation_cons_1(CAR(alist));
    reclaim_installation_cons_1(alist);
    alist = temp;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    return VALUES_1(T);
}

/* ANALYZE-EVERY-ACTION */
Object analyze_every_action(action,alist,constraints)
    Object action, alist, constraints;
{
    Object scope, role, local_name, domain_qm, binding_constraint_info;

    x_note_fn_call(179,190);
    scope = SECOND(action);
    role = FIRST(scope);
    local_name = SECOND(scope);
    domain_qm = THIRD(scope);
    binding_constraint_info = analyze_role(role,domain_qm,alist);
    alist = installation_cons_1(installation_cons_1(local_name,
	    binding_constraint_info),alist);
    analyze_rule_action(THIRD(action),alist,constraints);
    reclaim_installation_cons_1(CAR(alist));
    reclaim_installation_cons_1(alist);
    return VALUES_1(T);
}

/* ANALYZE-FORM-ACCORDING-TO-SCOPE */
Object analyze_form_according_to_scope(scope,rest_of_forms,alist,constraints)
    Object scope, rest_of_forms, alist, constraints;
{
    Object role, local_name, domain_qm, binding_constraint_info, form;
    Object ab_loop_list_;

    x_note_fn_call(179,191);
    role = FIRST(scope);
    local_name = SECOND(scope);
    domain_qm = THIRD(scope);
    binding_constraint_info = analyze_role(role,domain_qm,alist);
    alist = installation_cons_1(installation_cons_1(local_name,
	    binding_constraint_info),alist);
    form = Nil;
    ab_loop_list_ = rest_of_forms;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    analyze_compiled_form(form,alist,constraints);
    goto next_loop;
  end_loop:;
    reclaim_installation_cons_1(CAR(alist));
    reclaim_installation_cons_1(alist);
    return VALUES_1(T);
}

static Object Qexpression;         /* expression */

static Object Qother;              /* other */

static Object Qcreate_connection_spec;  /* create-connection-spec */

static Object Qexpression_list;    /* expression-list */

static Object Qdesignation_list;   /* designation-list */

static Object Qcolor_changes;      /* color-changes */

static Object Qmessage_designation;  /* message-designation */

static Object list_constant_4;     /* # */

static Object Qscope;              /* scope */

static Object Qshow_or_hide_argument_list;  /* show-or-hide-argument-list */

static Object Qin;                 /* in */

/* ANALYZE-FORM-ACCORDING-TO-TEMPLATE */
Object analyze_form_according_to_template(form,template_qm,alist,constraints)
    Object form, template_qm, alist, constraints;
{
    Object rest_of_template, template_symbol, rest_of_sub_forms, sub_form;
    Object expression, ab_loop_list_, expression1, expression2;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(179,192);
    rest_of_template = CDR(template_qm);
    template_symbol = template_qm ? CAR(rest_of_template) : Qexpression;
    rest_of_sub_forms = CDR(form);
    sub_form = Nil;
  next_loop:
    sub_form = CAR(rest_of_sub_forms);
    if ( !TRUEP(rest_of_sub_forms))
	goto end_loop;
    if (EQ(template_symbol,Qother));
    else if (EQ(template_symbol,Qcreate_connection_spec));
    else if (EQ(template_symbol,Qexpression_list) || EQ(template_symbol,
	    Qdesignation_list)) {
	expression = Nil;
	ab_loop_list_ = sub_form;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	analyze_compiled_form(expression,alist,constraints);
	goto next_loop_1;
      end_loop_1:;
    }
    else if (EQ(template_symbol,Qcolor_changes)) {
	expression1 = Nil;
	expression2 = Nil;
	ab_loop_list_ = rest_of_sub_forms;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	expression1 = CAR(ab_loop_desetq_);
	expression2 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	analyze_compiled_form(expression1,alist,constraints);
	analyze_compiled_form(expression2,alist,constraints);
	goto next_loop_2;
      end_loop_2:;
	rest_of_sub_forms = Nil;
    }
    else if (EQ(template_symbol,Qmessage_designation)) {
	if ( !TRUEP(memq_function(sub_form,list_constant_4)))
	    analyze_compiled_form(sub_form,alist,constraints);
    }
    else if (EQ(template_symbol,Qscope)) {
	analyze_form_according_to_scope(CAR(rest_of_sub_forms),
		CDR(rest_of_sub_forms),alist,constraints);
	rest_of_sub_forms = Nil;
    }
    else if (EQ(template_symbol,Qshow_or_hide_argument_list)) {
	if (EQ(CAR(sub_form),Qin))
	    analyze_compiled_form(SECOND(sub_form),alist,constraints);
    }
    else
	analyze_compiled_form(sub_form,alist,constraints);
    if (template_qm) {
	temp = CDR(rest_of_template);
	if (SYMBOLP(temp))
	    template_symbol = CDR(rest_of_template);
	else {
	    rest_of_template = CDR(rest_of_template);
	    template_symbol = CAR(rest_of_template);
	}
    }
    rest_of_sub_forms = CDR(rest_of_sub_forms);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ANALYZE-FOR-CONSISTENCY-BLOCK-WITH-ONLY-CELL-ARRAY */
Object analyze_for_consistency_block_with_only_cell_array(block)
    Object block;
{
    Object cell_array_qm, sub_class_bit_vector, user_menu_choice_qm;
    Object user_menu_choice_status_qm;
    Object current_computation_component_particulars;
    Object compiled_item_being_analyzed;
    Object compiled_item_being_analyzed_started_out_incomplete_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(179,193);
    if ( !TRUEP(Loading_kb_p)) {
	cell_array_qm = get_lookup_slot_value_given_default(block,
		Qcell_array,Nil);
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(User_menu_choice_class_description,(SI_Long)18L));
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
	    user_menu_choice_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    user_menu_choice_qm = Nil;
	user_menu_choice_status_qm = user_menu_choice_qm ? 
		button_frame_status(block) : Nil;
	current_computation_component_particulars = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		0);
	  delete_all_consistency_analysis_frame_notes(2,block,T);
	  delete_all_consistency_analysis_frame_notes(1,block);
	POP_SPECIAL();
	compiled_item_being_analyzed = block;
	compiled_item_being_analyzed_started_out_incomplete_qm = 
		frame_incomplete_p(block);
	PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed_started_out_incomplete_qm,Qcompiled_item_being_analyzed_started_out_incomplete_qm,compiled_item_being_analyzed_started_out_incomplete_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
		  0);
	    if (cell_array_qm) {
		if ( !TRUEP(Delete_as_item_referring_to_name_qm) && 
			frame_incomplete_p(block)) {
		    if (( !TRUEP(user_menu_choice_qm) ||  
			    !TRUEP(user_menu_choice_status_qm)) && 
			    g2_cell_array_expression_cells_have_byte_code_bodies_p(cell_array_qm))
			update_frame_status(block,Nil,Nil);
		}
		analyze_g2_cell_array_for_consistency(get_lookup_slot_value_given_default(block,
			Qcell_array,Nil));
	    }
	    result = post_analyzer_warning_note_if_necessary(block);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* ADD-OR-DELETE-AS-ITEM-REFERRING-TO-NAME */
Object add_or_delete_as_item_referring_to_name(name)
    Object name;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp, temp_1;
    Object svref_arg_2, new_cons, svref_new_value;

    x_note_fn_call(179,194);
    if (Delete_as_item_referring_to_name_qm) {
	gensymed_symbol = Compiled_item_being_analyzed;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = lookup_kb_specific_property_value(name,
		Compiled_items_referring_to_this_name_kbprop);
      next_loop:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else
		mutate_kb_specific_property_value(name,
			CDR(gensymed_symbol_2),
			Compiled_items_referring_to_this_name_kbprop);
	    temp_1 = CAR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qinstallation);
	    if (ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_installation_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
		temp = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    return VALUES_1(temp_1);
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (Add_as_item_referring_to_name_qm) {
	gensymed_symbol = lookup_kb_specific_property_value(name,
		Compiled_items_referring_to_this_name_kbprop);
	gensymed_symbol_1 = Compiled_item_being_analyzed;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = gensymed_symbol_1;
	    new_cons = ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_installation_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_installation_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_installation_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qinstallation);
	    mutate_kb_specific_property_value(name,gensymed_symbol_2,
		    Compiled_items_referring_to_this_name_kbprop);
	    return VALUES_1(temp_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* CHECK-FOR-UNDEFINED-CLASS */
Object check_for_undefined_class(class_1)
    Object class_1;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(179,195);
    add_or_delete_as_item_referring_to_name(class_1);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	temp_2 =  !(gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return add_to_frame_note_particulars_list_if_necessary(class_1,
		Qundefined_classes,Compiled_item_being_analyzed);
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

static Object Qmessage_board;      /* message-board */

static Object Qnon_existent_instances;  /* non-existent-instances */

static Object Qnon_existent_instances_of_class;  /* non-existent-instances-of-class */

/* CHECK-UNDEFINED-INSTANCES-OF-CLASS */
Object check_undefined_instances_of_class(name,class_1)
    Object name, class_1;
{
    Object instance, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(179,196);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	instance = get_instance_with_name_if_any(Qitem,name);
	if ( !TRUEP(instance) &&  !EQ(name,Qmessage_board))
	    return add_to_frame_note_particulars_list_if_necessary(name,
		    Qnon_existent_instances,Compiled_item_being_analyzed);
	else {
	    if (instance) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(instance,
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
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else if (EQ(name,Qmessage_board)) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qmessage_board,
			Class_description_gkbprop);
		temp =  !(gensymed_symbol ? TRUEP(memq_function(class_1,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return add_to_frame_note_particular_pairs_as_necessary(Qnon_existent_instances_of_class,
			class_1,name,Nil);
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object Qnon_existent_instances_of_type;  /* non-existent-instances-of-type */

/* CHECK-UNDEFINED-INSTANCES-OF-TYPE */
Object check_undefined_instances_of_type(name,type)
    Object name, type;
{
    Object instance;

    x_note_fn_call(179,197);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	instance = get_instance_with_name_if_any(Qitem,name);
	if ( !TRUEP(instance) &&  !EQ(name,Qmessage_board))
	    return add_to_frame_note_particulars_list_if_necessary(name,
		    Qnon_existent_instances,Compiled_item_being_analyzed);
	else if (instance &&  !TRUEP(type_specification_type_p(instance,
		type)) || EQ(name,Qmessage_board) &&  
		!TRUEP(type_specification_subtype_p(list_constant_5,type)))
	    return add_to_frame_note_particular_pairs_as_necessary(Qnon_existent_instances_of_type,
		    type,name,T);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNDEFINED-INSTANCE-NAME */
Object check_for_undefined_instance_name(name)
    Object name;
{
    x_note_fn_call(179,198);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
	    !TRUEP(get_instance_with_name_if_any(Qitem,name)) &&  !EQ(name,
	    Qmessage_board))
	return add_to_frame_note_particulars_list_if_necessary(name,
		Qnon_existent_instances,Compiled_item_being_analyzed);
    else
	return VALUES_1(Nil);
}

static Object Qmethod_declaration;  /* method-declaration */

static Object Qnon_existent_procedure_method;  /* non-existent-procedure-method */

static Object Qspecific_method_argument_conflict;  /* specific-method-argument-conflict */

/* CHECK-FOR-VALID-METHOD */
Object check_for_valid_method(name)
    Object name;
{
    Object argument_count_qm, method_class_qm;

    x_note_fn_call(179,199);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	if ( !TRUEP(get_instance_with_name_if_any(Qmethod_declaration,name)))
	    add_frame_note(2,Qnon_existent_procedure_method,
		    Compiled_item_being_analyzed);
	argument_count_qm = ISVREF(Compiled_item_being_analyzed,(SI_Long)23L);
	method_class_qm = ISVREF(Compiled_item_being_analyzed,(SI_Long)31L);
	if (argument_count_qm && method_class_qm && 
		duplicate_specific_methods_p(name,method_class_qm,
		argument_count_qm))
	    return add_frame_note(2,Qspecific_method_argument_conflict,
		    Compiled_item_being_analyzed);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Cached_name_cons_marker = UNBOUND;

/* CHECK-FOR-CACHED-NAME-UNDEFINED-INSTANCE */
Object check_for_cached_name_undefined_instance(name,index_1)
    Object name, index_1;
{
    Object byte_code_body_qm, constant_vector_qm, instance_qm;
    Object old_constant_value_qm, svref_new_value;

    x_note_fn_call(179,200);
    byte_code_body_qm = 
	    get_byte_code_body_if_any(Compiled_item_being_analyzed,
	    Current_computation_component_particulars);
    constant_vector_qm = byte_code_body_qm ? ISVREF(byte_code_body_qm,
	    (SI_Long)3L) : Qnil;
    instance_qm = get_instance_with_name_if_any(Qitem,name);
    if (constant_vector_qm && FIXNUM_LT(index_1,length(constant_vector_qm))) {
	old_constant_value_qm = ISVREF(constant_vector_qm,IFIX(index_1));
	if (instance_qm) {
	    if (old_constant_value_qm && CONSP(old_constant_value_qm))
		reclaim_slot_value_cons_1(old_constant_value_qm);
	    SVREF(constant_vector_qm,index_1) = instance_qm;
	}
	else if (old_constant_value_qm && CONSP(old_constant_value_qm))
	    M_CAR(old_constant_value_qm) = name;
	else {
	    svref_new_value = slot_value_cons_1(name,Cached_name_cons_marker);
	    SVREF(constant_vector_qm,index_1) = svref_new_value;
	}
    }
    return check_for_undefined_instance_name(name);
}

/* CHECK-FOR-CACHED-ATTRIBUTE */
Object check_for_cached_attribute(attribute_name,item_name_qm,class_qm,
	    class_specific_attribute_class_qm,constant_index)
    Object attribute_name, item_name_qm, class_qm;
    Object class_specific_attribute_class_qm, constant_index;
{
    Object item_qm, item_class_qm, byte_code_body_qm, constant_vector_qm;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, class_description_qm;
    Object slot_description_qm, attribute_index_qm, old_constant_value_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(179,201);
    item_qm = item_name_qm ? get_instance_with_name_if_any(Qitem,
	    item_name_qm) : Qnil;
    item_class_qm = item_qm ? ISVREF(ISVREF(item_qm,(SI_Long)1L),
	    (SI_Long)1L) : Qnil;
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	byte_code_body_qm = 
		get_byte_code_body_if_any(Compiled_item_being_analyzed,
		Current_computation_component_particulars);
	constant_vector_qm = byte_code_body_qm ? ISVREF(byte_code_body_qm,
		(SI_Long)3L) : Nil;
	if ( !EQ(class_qm,Qitem)) {
	    if (SYMBOLP(class_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_qm) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_qm;
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		  next_loop_6:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		class_description_qm = resulting_value;
	    }
	    else
		class_description_qm = Nil;
	}
	else
	    class_description_qm = Nil;
	if (EQ(attribute_name,Qab_class))
	    slot_description_qm = Nil;
	else if (item_class_qm)
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(attribute_name,
		    ISVREF(item_qm,(SI_Long)1L),
		    class_specific_attribute_class_qm);
	else if (class_description_qm)
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(attribute_name,
		    class_description_qm,class_specific_attribute_class_qm);
	else
	    slot_description_qm = Nil;
	attribute_index_qm = slot_description_qm ? 
		ISVREF(slot_description_qm,(SI_Long)8L) : Nil;
	if (attribute_index_qm &&  !TRUEP(item_qm) && class_qm && 
		user_vector_slot_location_differs_in_subclass_p(3,
		attribute_name,class_qm,class_specific_attribute_class_qm))
	    attribute_index_qm = Nil;
	if (constant_vector_qm && FIXNUM_LT(constant_index,
		length(constant_vector_qm))) {
	    old_constant_value_qm = ISVREF(constant_vector_qm,
		    IFIX(constant_index));
	    if (attribute_index_qm) {
		if (old_constant_value_qm && LISTP(old_constant_value_qm))
		    reclaim_slot_value_list_1(old_constant_value_qm);
		SVREF(constant_vector_qm,constant_index) = attribute_index_qm;
	    }
	    else if (old_constant_value_qm && LISTP(old_constant_value_qm))
		M_CAR(old_constant_value_qm) = attribute_name;
	    else {
		gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = attribute_name;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = item_name_qm;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = class_qm;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = class_specific_attribute_class_qm;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Cached_attribute_cons_marker;
		SVREF(constant_vector_qm,constant_index) = gensymed_symbol;
	    }
	}
    }
    if (class_specific_attribute_class_qm)
	return check_for_undefined_class_qualified_attribute_of_class(attribute_name,
		class_specific_attribute_class_qm,class_qm);
    else {
	if (item_class_qm) {
	    temp_2 =  !TRUEP(class_qm);
	    if (temp_2);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(item_class_qm,
			Class_description_gkbprop);
		temp_2 = gensymed_symbol ? TRUEP(memq_function(class_qm,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	    }
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    check_for_undefined_attribute_of_class(attribute_name,
		    item_class_qm);
	    if (class_qm)
		return add_or_delete_as_item_referring_to_name(class_qm);
	    else
		return VALUES_1(Nil);
	}
	else if (class_qm) {
	    check_for_undefined_attribute_of_class(attribute_name,class_qm);
	    return add_or_delete_as_item_referring_to_name(class_qm);
	}
	else
	    return add_or_delete_as_item_referring_to_name(attribute_name);
    }
}

/* ANALYZE-ATTRIBUTES-OF-SUBCLASSES-FOR-CONSISTENCY */
Object analyze_attributes_of_subclasses_for_consistency(user_class,
	    analyze_inherited_attributes_also_qm)
    Object user_class, analyze_inherited_attributes_also_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, scope_conses, ab_loopvar_;
    Object subclass;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(179,202);
    if (SYMBOLP(user_class)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = user_class;
	key_hash_value = SXHASH_SYMBOL_1(user_class) & 
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = user_class;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if ( !TRUEP(analyze_inherited_attributes_also_qm)) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = user_class;
	    subclass = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop_12:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_12;
	      temp_1 = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      subclass = temp_1;
	      analyze_class_attributes_for_consistency(subclass,Nil);
	      goto next_loop_12;
	    end_loop_12:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	    return result;
	}
	else {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = user_class;
	    subclass = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop_13:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_13;
	      temp_1 = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      subclass = temp_1;
	      if ( 
		      !TRUEP(lookup_global_or_kb_specific_property_value(subclass,
		      Inferior_classes_gkbprop)))
		  analyze_class_attributes_for_consistency(subclass,T);
	      goto next_loop_13;
	    end_loop_13:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

/* ANALYZE-CLASS-ATTRIBUTES-FOR-CONSISTENCY */
Object analyze_class_attributes_for_consistency(user_class,
	    analyze_inherited_attributes_also_qm)
    Object user_class, analyze_inherited_attributes_also_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, class_description_qm;
    Object slot_descriptions_qm, slot_description, ab_loop_list_, slot_name;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(179,203);
    if (SYMBOLP(user_class)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = user_class;
	key_hash_value = SXHASH_SYMBOL_1(user_class) & 
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = user_class;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(user_class,
		Class_description_gkbprop);
	slot_descriptions_qm = class_description_qm ? 
		ISVREF(class_description_qm,(SI_Long)6L) : Qnil;
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions_qm;
	slot_name = Nil;
      next_loop_12:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_12;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_name = ISVREF(slot_description,(SI_Long)2L);
	if (ISVREF(slot_description,(SI_Long)8L) && 
		(analyze_inherited_attributes_also_qm || 
		EQ(ISVREF(slot_description,(SI_Long)3L),user_class)))
	    analyze_compiled_items_for_consistency(slot_name);
	goto next_loop_12;
      end_loop_12:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qundefined_attributes;  /* undefined-attributes */

/* CHECK-FOR-UNDEFINED-ATTRIBUTE */
Object check_for_undefined_attribute(attribute)
    Object attribute;
{
    x_note_fn_call(179,204);
    add_or_delete_as_item_referring_to_name(attribute);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
	    !TRUEP(attribute_of_class_or_subclass_p(attribute,Qitem)) &&  
	    !TRUEP(exported_attribute_of_class_or_subclass_p(attribute,
	    Qitem)) &&  !TRUEP(get_property_value_function(3,
	    get_symbol_properties_function(attribute),Qvirtual_attribute,Nil)))
	return add_to_frame_note_particulars_list_if_necessary(attribute,
		Qundefined_attributes,Compiled_item_being_analyzed);
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNDEFINED-ATTRIBUTE-OF-CLASS */
Object check_for_undefined_attribute_of_class(attribute,class_1)
    Object attribute, class_1;
{
    x_note_fn_call(179,205);
    add_or_delete_as_item_referring_to_name(attribute);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
	    !TRUEP(attribute_of_class_or_subclass_p(attribute,class_1)) && 
	     !TRUEP(exported_attribute_of_class_or_subclass_p(attribute,
	    class_1)) &&  !TRUEP(get_property_value_function(3,
	    get_symbol_properties_function(attribute),Qvirtual_attribute,Nil)))
	return add_to_undefined_attribute_of_class(class_1,attribute,
		Compiled_item_being_analyzed);
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNDEFINED-METHOD-OF-CLASS */
Object check_for_undefined_method_of_class(method,class_1)
    Object method, class_1;
{
    x_note_fn_call(179,206);
    add_or_delete_as_item_referring_to_name(method);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm) &&  
	    !TRUEP(method_of_class_or_subclass_p(method,class_1)))
	return add_to_undefined_method_of_class(class_1,method,
		Compiled_item_being_analyzed);
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-UNDEFINED-CLASS-QUALIFIED-ATTRIBUTE */
Object check_for_undefined_class_qualified_attribute(attribute_name,
	    class_qualifier)
    Object attribute_name, class_qualifier;
{
    x_note_fn_call(179,207);
    check_for_undefined_class(class_qualifier);
    check_for_undefined_attribute_of_class(attribute_name,class_qualifier);
    return VALUES_1(Nil);
}

/* CHECK-FOR-UNDEFINED-CLASS-QUALIFIED-METHOD */
Object check_for_undefined_class_qualified_method(method_name,class_qualifier)
    Object method_name, class_qualifier;
{
    x_note_fn_call(179,208);
    check_for_undefined_class(class_qualifier);
    check_for_undefined_method_of_class(method_name,class_qualifier);
    return VALUES_1(Nil);
}

static Object Qundefined_attributes_of_classes;  /* undefined-attributes-of-classes */

/* CHECK-FOR-UNDEFINED-CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS */
Object check_for_undefined_class_qualified_attribute_of_class(attribute_name,
	    class_qualifier,class_qm)
    Object attribute_name, class_qualifier, class_qm;
{
    Object gensymed_symbol, slot_name_denotation_qm, temp_1;
    char temp;

    x_note_fn_call(179,209);
    check_for_undefined_class(class_qualifier);
    check_for_undefined_attribute_of_class(attribute_name,class_qualifier);
    if (class_qualifier && class_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_qm,
		Class_description_gkbprop);
	temp =  !(gensymed_symbol ? TRUEP(memq_function(class_qualifier,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_qualifier,
		Class_description_gkbprop);
	temp =  !(gensymed_symbol ? TRUEP(memq_function(class_qm,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	slot_name_denotation_qm = class_qualifier ? 
		slot_value_cons_1(Qclass_qualified_name,
		slot_value_cons_1(class_qualifier,
		slot_value_cons_1(attribute_name,Nil))) : attribute_name;
	add_to_frame_note_particular_pairs_as_necessary(Qundefined_attributes_of_classes,
		class_qm,slot_name_denotation_qm,T);
	reclaim_slot_value_list_1(slot_name_denotation_qm);
    }
    if (class_qm) {
	if (lookup_global_or_kb_specific_property_value(class_qm,
		Class_description_gkbprop)) {
	    temp_1 = lookup_global_or_kb_specific_property_value(class_qm,
		    Class_definition_gkbprop);
	    temp = CONSP(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	add_or_delete_as_item_referring_to_name(class_qm);
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

/* ANALYZE-INSTANCE-OR-LOCAL-NAME */
Object analyze_instance_or_local_name(name,alist)
    Object name, alist;
{
    Object temp, alist_info;

    x_note_fn_call(179,210);
    temp = assq_function(name,alist);
    alist_info = CDR(temp);
    if (alist_info);
    else if (memq_function(name,list_constant_6));
    else
	check_for_undefined_instance_name(name);
    return VALUES_1(T);
}

/* ADD-TO-UNDEFINED-ATTRIBUTE-OF-CLASS */
Object add_to_undefined_attribute_of_class(class_1,attribute,
	    compiled_item_being_analyzed)
    Object class_1, attribute, compiled_item_being_analyzed;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(179,211);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
	    0);
      result = add_to_frame_note_particular_pairs_as_necessary(Qundefined_attributes_of_classes,
	      class_1,attribute,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qundefined_methods_of_classes;  /* undefined-methods-of-classes */

/* ADD-TO-UNDEFINED-METHOD-OF-CLASS */
Object add_to_undefined_method_of_class(class_1,method,
	    compiled_item_being_analyzed)
    Object class_1, method, compiled_item_being_analyzed;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(179,212);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
	    0);
      result = add_to_frame_note_particular_pairs_as_necessary(Qundefined_methods_of_classes,
	      class_1,method,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qprocedure_call;     /* procedure-call */

static Object Qstable_procedure_call;  /* stable-procedure-call */

static Object Qprocedure;          /* procedure */

static Object Qitem_not_ok;        /* item-not-ok */

static Object list_constant_7;     /* # */

static Object Qarg_count;          /* arg-count */

static Object Qremote_procedure_call;  /* remote-procedure-call */

static Object Qstable_remote_procedure_call;  /* stable-remote-procedure-call */

static Object Qremote_procedure_declaration;  /* remote-procedure-declaration */

static Object Kgeneral_description;  /* :general-description */

static Object Kall_remaining;      /* :all-remaining */

static Object Kkind;               /* :kind */

static Object Qno_arg_for_method_call;  /* no-arg-for-method-call */

static Object Qno_item_arg_for_method_call;  /* no-item-arg-for-method-call */

static Object Qno_method_for_class;  /* no-method-for-class */

static Object Qno_method_for_arg_count;  /* no-method-for-arg-count */

static Object Qmethod_for_class_not_okay;  /* method-for-class-not-okay */

static Object Qarg_count_mismatch;  /* arg-count-mismatch */

static Object Qreturn_count_mismatch;  /* return-count-mismatch */

static Object Qhandle;             /* handle */

/* CHECK-FOR-VALID-PROCEDURE-CALL */
Object check_for_valid_procedure_call(type_of_call,name,arg_types,
	    return_types,stable_procedure_call_qm,procedure_to_analyze_qm)
    Object type_of_call, name, arg_types, return_types;
    Object stable_procedure_call_qm, procedure_to_analyze_qm;
{
    Object valid_procedure_call_qm, instance_qm, formal_arg_types;
    Object formal_arg_restp_index, formal_arg_kinds, formal_return_types;
    Object formal_return_restp_index, method_first_arg_class_qm;
    Object method_error_no_arg_qm, method_error_first_arg_type_not_class_qm;
    Object method_error_no_method_for_arg_count_qm;
    Object method_error_no_method_for_class_qm;
    Object method_error_method_for_class_not_ok_qm, temp, sub_class_bit_vector;
    Object method_list_qm, first_arg_type_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, gensymed_symbol_3;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, method;
    Object ab_loop_list_, arg_count, method_found_qm, var_count_1;
    Object description_vector, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object description, frame_key, arg_type, restp, formal_arg_types_tail;
    Object formal_arg_type, formal_arg_kinds_tail, kind, as_handle_p;
    Object ab_loop_iter_flag_, required_type, formal_return_types_tail;
    Object formal_return_type;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_, index_1, arg_number, return_number;
    char temp_1;
    Object result;

    x_note_fn_call(179,213);
    valid_procedure_call_qm = T;
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	instance_qm = Nil;
	formal_arg_types = Nil;
	formal_arg_restp_index = Nil;
	formal_arg_kinds = Nil;
	formal_return_types = Nil;
	formal_return_restp_index = Nil;
	method_first_arg_class_qm = Nil;
	method_error_no_arg_qm = Nil;
	method_error_first_arg_type_not_class_qm = Nil;
	method_error_no_method_for_arg_count_qm = Nil;
	method_error_no_method_for_class_qm = Nil;
	method_error_method_for_class_not_ok_qm = Nil;
	if (EQ(type_of_call,Qprocedure_call) || EQ(type_of_call,
		Qstable_procedure_call)) {
	    temp = procedure_to_analyze_qm;
	    if (temp);
	    else
		temp = get_instance_with_name_if_any(Qitem,name);
	    instance_qm = temp;
	    if ( !TRUEP(instance_qm)) {
		valid_procedure_call_qm = Nil;
		add_to_frame_note_particulars_list_if_necessary(name,
			Qnon_existent_instances,Compiled_item_being_analyzed);
	    }
	    else {
		if (instance_qm) {
		    sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Procedure_class_description,
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
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp_1 =  !temp_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    valid_procedure_call_qm = Nil;
		    add_to_frame_note_particular_pairs_as_necessary(Qnon_existent_instances_of_class,
			    Qprocedure,name,Nil);
		    instance_qm = Nil;
		}
		else {
		    if (instance_qm) {
			temp = ISVREF(instance_qm,(SI_Long)8L);
			temp_1 =  ! !TRUEP(CAR(temp));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			if ( !TRUEP(stable_procedure_call_qm))
			    valid_procedure_call_qm = Nil;
			add_to_frame_note_particulars_list_if_necessary(name,
				Qitem_not_ok,Compiled_item_being_analyzed);
			instance_qm = Nil;
		    }
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Method_declaration_class_description,
				(SI_Long)18L));
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
			    temp_1 = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    method_list_qm = Nil;
			    first_arg_type_qm = arg_types ? 
				    M_CAR(arg_types) : Nil;
			    if ( !TRUEP(first_arg_type_qm))
				method_first_arg_class_qm = Nil;
			    else if (class_type_specification_p(first_arg_type_qm))
				method_first_arg_class_qm = 
					M_CAR(M_CDR(first_arg_type_qm));
			    else if (type_specifications_could_intersect_p(first_arg_type_qm,
				    list_constant_7))
				method_first_arg_class_qm = Qitem;
			    else
				method_first_arg_class_qm = Nil;
			    if ( !TRUEP(first_arg_type_qm))
				method_error_no_arg_qm = T;
			    else if ( !TRUEP(method_first_arg_class_qm))
				method_error_first_arg_type_not_class_qm = 
					first_arg_type_qm;
			    else {
				if (SYMBOLP(method_first_arg_class_qm)) {
				    skip_list = CDR(Symbol_properties_table);
				    key_value = method_first_arg_class_qm;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(method_first_arg_class_qm) 
					    & IFIX(Most_positive_fixnum);
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
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_1:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_2 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_2,temp);
				    MVS_2(result,succ,marked);
				  next_loop_2:
				    if ( !TRUEP(marked))
					goto end_loop_1;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_2 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_2,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_2;
				  end_loop_1:
				    entry_hash = ISVREF(curr,(SI_Long)1L);
				    if (IFIX(entry_hash) < key_hash_value 
					    || IFIX(entry_hash) == 
					    key_hash_value &&  
					    !EQ(key_value,ISVREF(curr,
					    (SI_Long)2L))) {
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
				    gensymed_symbol_3 = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if ( !TRUEP(gensymed_symbol_3)) {
					gensymed_symbol_3 = 
						method_first_arg_class_qm;
					temp_2 = Symbol_properties_table;
					temp = 
						FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
						& IFIX(Most_positive_fixnum));
					tail = 
						make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
						Nil);
					head = 
						make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
						tail);
					new_cons = 
						ISVREF(Available_lookup_conses_vector,
						IFIX(Current_thread_index));
					if (new_cons) {
					    svref_arg_1 = 
						    Available_lookup_conses_vector;
					    svref_arg_2 = Current_thread_index;
					    svref_new_value = M_CDR(new_cons);
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
					    }
					    gensymed_symbol_4 = new_cons;
					}
					else
					    gensymed_symbol_4 = Nil;
					if ( !TRUEP(gensymed_symbol_4))
					    gensymed_symbol_4 = 
						    replenish_lookup_cons_pool();
					M_CAR(gensymed_symbol_4) = 
						Qsymbol_properties_hash_table;
					new_cons = 
						ISVREF(Available_lookup_conses_vector,
						IFIX(Current_thread_index));
					if (new_cons) {
					    svref_arg_1 = 
						    Available_lookup_conses_vector;
					    svref_arg_2 = Current_thread_index;
					    svref_new_value = M_CDR(new_cons);
					    SVREF(svref_arg_1,svref_arg_2) 
						    = svref_new_value;
					    if ( 
						    !TRUEP(ISVREF(Available_lookup_conses_vector,
						    IFIX(Current_thread_index)))) 
							{
						svref_arg_1 = 
							Available_lookup_conses_tail_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(svref_arg_1,
							svref_arg_2) = Nil;
					    }
					    gensymed_symbol_5 = new_cons;
					}
					else
					    gensymed_symbol_5 = Nil;
					if ( !TRUEP(gensymed_symbol_5))
					    gensymed_symbol_5 = 
						    replenish_lookup_cons_pool();
					M_CAR(gensymed_symbol_5) = head;
					M_CDR(gensymed_symbol_5) = tail;
					inline_note_allocate_cons(gensymed_symbol_5,
						Qlookup);
					M_CDR(gensymed_symbol_4) = 
						gensymed_symbol_5;
					inline_note_allocate_cons(gensymed_symbol_4,
						Qlookup);
					gensymed_symbol_3 = 
						set_skip_list_entry(temp_2,
						FIX((SI_Long)31L),Qeq,Nil,
						T,gensymed_symbol_3,temp,
						gensymed_symbol_4);
				    }
				    global_properties = gensymed_symbol_3;
				    skip_list = CDR(global_properties);
				    key_value = 
					    Current_kb_specific_property_list_property_name;
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
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_4:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_2 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_2,temp);
				    MVS_2(result,succ,marked);
				  next_loop_5:
				    if ( !TRUEP(marked))
					goto end_loop_4;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_2 = ATOMIC_REF_OBJECT(reference);
				    temp = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_2,temp);
				    MVS_2(result,succ,marked);
				    goto next_loop_5;
				  end_loop_4:
				    entry_hash = ISVREF(curr,(SI_Long)1L);
				    if (IFIX(entry_hash) < key_hash_value 
					    || IFIX(entry_hash) == 
					    key_hash_value &&  
					    !EQ(key_value,ISVREF(curr,
					    (SI_Long)2L))) {
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
				    kb_properties = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if (kb_properties);
				    else
					kb_properties = Nil;
				    if (kb_properties) {
					skip_list = CDR(kb_properties);
					key_value = Class_description_gkbprop;
					key_hash_value = 
						SXHASH_SYMBOL_1(Class_description_gkbprop) 
						& IFIX(Most_positive_fixnum);
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
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_7:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_2 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_2,temp);
					MVS_2(result,succ,marked);
				      next_loop_8:
					if ( !TRUEP(marked))
					    goto end_loop_7;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_2 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_2,temp);
					MVS_2(result,succ,marked);
					goto next_loop_8;
				      end_loop_7:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
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
					kb_specific_value = 
						IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if (kb_specific_value);
					else
					    kb_specific_value = 
						    No_specific_property_value;
				    }
				    else
					kb_specific_value = 
						No_specific_property_value;
				    if ( !EQ(kb_specific_value,
					    No_specific_property_value))
					resulting_value = kb_specific_value;
				    else {
					skip_list = CDR(global_properties);
					key_value = Class_description_gkbprop;
					key_hash_value = 
						SXHASH_SYMBOL_1(Class_description_gkbprop) 
						& IFIX(Most_positive_fixnum);
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
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
				      next_loop_10:
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_2 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_2,temp);
					MVS_2(result,succ,marked);
				      next_loop_11:
					if ( !TRUEP(marked))
					    goto end_loop_10;
					curr = 
						ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
						(SI_Long)0L),level));
					reference = ISVREF(ISVREF(curr,
						(SI_Long)0L),level);
					temp_2 = ATOMIC_REF_OBJECT(reference);
					temp = (SI_Long)355L == 
						ATOMIC_REF_STAMP(reference) 
						? T : Nil;
					result = VALUES_2(temp_2,temp);
					MVS_2(result,succ,marked);
					goto next_loop_11;
				      end_loop_10:
					entry_hash = ISVREF(curr,(SI_Long)1L);
					if (IFIX(entry_hash) < 
						key_hash_value || 
						IFIX(entry_hash) == 
						key_hash_value &&  
						!EQ(key_value,ISVREF(curr,
						(SI_Long)2L))) {
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
					resulting_value = IFIX(ISVREF(curr,
						(SI_Long)1L)) == 
						key_hash_value ? 
						(EQ(key_value,ISVREF(curr,
						(SI_Long)2L)) ? 
						ISVREF(curr,(SI_Long)3L) : 
						Nil) : Nil;
					if (resulting_value);
					else
					    resulting_value = Nil;
				    }
				    temp_1 = TRUEP(resulting_value);
				}
				else
				    temp_1 = TRUEP(Nil);
				if ( !temp_1) {
				    method_list_qm = 
					    get_specific_methods_for_class_or_superior_class(name,
					    method_first_arg_class_qm);
				    if ( !TRUEP(method_list_qm))
					method_error_no_method_for_class_qm 
						= T;
				    else {
					method = Nil;
					ab_loop_list_ = method_list_qm;
					arg_count = length(arg_types);
					method_found_qm = Nil;
				      next_loop_12:
					if ( !TRUEP(ab_loop_list_))
					    goto end_loop_12;
					method = M_CAR(ab_loop_list_);
					ab_loop_list_ = M_CDR(ab_loop_list_);
					if (FIXNUM_EQ(ISVREF(method,
						(SI_Long)23L),arg_count))
					    method_found_qm = T;
					if (method_found_qm)
					    goto end_loop_12;
					goto next_loop_12;
				      end_loop_12:
					if ( !TRUEP(method_found_qm))
					    method_error_no_method_for_arg_count_qm 
						    = T;
				    }
				}
				else {
				    temp = 
					    check_valid_method_definition_of_existing_class(name,
					    method_first_arg_class_qm,
					    arg_types);
				    if (EQ(temp,Qarg_count))
					method_error_no_method_for_arg_count_qm 
						= T;
				    else if (EQ(temp,Qab_class))
					method_error_no_method_for_class_qm 
						= T;
				}
			    }
			}
			else {
			    formal_arg_types = 
				    collect_types_into_list_using_gensym_conses(ISVREF(instance_qm,
				    (SI_Long)24L));
			    var_count_1 = var_count(ISVREF(instance_qm,
				    (SI_Long)24L));
			    formal_arg_kinds = make_gensym_list_1(var_count_1);
			    formal_return_types = 
				    collect_types_into_list_using_gensym_conses(ISVREF(instance_qm,
				    (SI_Long)25L));
			}
		    }
		}
	    }
	}
	else if (EQ(type_of_call,Qremote_procedure_call) || 
		EQ(type_of_call,Qstable_remote_procedure_call)) {
	    temp = procedure_to_analyze_qm;
	    if (temp);
	    else
		temp = get_instance_with_name_if_any(Qitem,name);
	    instance_qm = temp;
	    if ( !TRUEP(instance_qm)) {
		valid_procedure_call_qm = Nil;
		add_to_frame_note_particulars_list_if_necessary(name,
			Qnon_existent_instances,Compiled_item_being_analyzed);
	    }
	    else {
		if (instance_qm) {
		    sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Remote_procedure_declaration_class_description,
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
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp_1 =  !temp_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    valid_procedure_call_qm = Nil;
		    add_to_frame_note_particular_pairs_as_necessary(Qnon_existent_instances_of_class,
			    Qremote_procedure_declaration,name,Nil);
		    instance_qm = Nil;
		}
		else {
		    if (instance_qm) {
			temp = ISVREF(instance_qm,(SI_Long)8L);
			temp_1 =  ! !TRUEP(CAR(temp));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			if ( !TRUEP(stable_procedure_call_qm))
			    valid_procedure_call_qm = Nil;
			add_to_frame_note_particulars_list_if_necessary(name,
				Qitem_not_ok,Compiled_item_being_analyzed);
			instance_qm = Nil;
		    }
		    else {
			description_vector = ISVREF(instance_qm,(SI_Long)24L);
			index_1 = (SI_Long)0L;
			ab_loop_bind_ = IFIX(var_count(description_vector));
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_13:
			if (index_1 >= ab_loop_bind_)
			    goto end_loop_13;
			gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
			gensymed_symbol_3 = 
				FIXNUM_LE(ISVREF(description_vector,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(description_vector,gensymed_symbol 
				+ IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(description_vector,
				(gensymed_symbol >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
			if (CONSP(gensymed_symbol_3) && 
				EQ(CAR(gensymed_symbol_3),
				Kgeneral_description))
			    gensymed_symbol_3 = 
				    getfq_function_no_default(CDR(gensymed_symbol_3),
				    Ktype);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			index_1 = index_1 + (SI_Long)1L;
			goto next_loop_13;
		      end_loop_13:
			formal_arg_types = ab_loopvar_;
			goto end_5;
			formal_arg_types = Qnil;
		      end_5:;
			description_vector = ISVREF(instance_qm,(SI_Long)24L);
			index_1 = (SI_Long)0L;
			ab_loop_bind_ = IFIX(var_count(description_vector));
			description = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_14:
			if (index_1 >= ab_loop_bind_)
			    goto end_loop_14;
			gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
			gensymed_symbol_3 = 
				FIXNUM_LE(ISVREF(description_vector,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(description_vector,gensymed_symbol 
				+ IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(description_vector,
				(gensymed_symbol >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
			if (CONSP(gensymed_symbol_3) && 
				EQ(CAR(gensymed_symbol_3),
				Kgeneral_description)) {
			    gensymed_symbol_3 = CDR(gensymed_symbol_3);
			    description = gensymed_symbol_3;
			}
			else
			    description = Nil;
			if (getf(description,Kall_remaining,_))
			    formal_arg_restp_index = FIX(index_1);
			ab_loopvar__2 = gensym_cons_1(getf(description,
				Kkind,_),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			index_1 = index_1 + (SI_Long)1L;
			goto next_loop_14;
		      end_loop_14:
			formal_arg_kinds = ab_loopvar_;
			goto end_6;
			formal_arg_kinds = Qnil;
		      end_6:;
			description_vector = ISVREF(instance_qm,(SI_Long)25L);
			index_1 = (SI_Long)0L;
			ab_loop_bind_ = IFIX(var_count(description_vector));
			description = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_15:
			if (index_1 >= ab_loop_bind_)
			    goto end_loop_15;
			gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
			gensymed_symbol_3 = 
				FIXNUM_LE(ISVREF(description_vector,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(description_vector,gensymed_symbol 
				+ IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(description_vector,
				(gensymed_symbol >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
			if (CONSP(gensymed_symbol_3) && 
				EQ(CAR(gensymed_symbol_3),
				Kgeneral_description)) {
			    gensymed_symbol_3 = CDR(gensymed_symbol_3);
			    description = gensymed_symbol_3;
			}
			else
			    description = Nil;
			if (getf(description,Kall_remaining,_))
			    formal_return_restp_index = FIX(index_1);
			gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
			gensymed_symbol_3 = 
				FIXNUM_LE(ISVREF(description_vector,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(description_vector,gensymed_symbol 
				+ IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(description_vector,
				(gensymed_symbol >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
			if (CONSP(gensymed_symbol_3) && 
				EQ(CAR(gensymed_symbol_3),
				Kgeneral_description))
			    gensymed_symbol_3 = 
				    getfq_function_no_default(CDR(gensymed_symbol_3),
				    Ktype);
			ab_loopvar__2 = gensym_cons_1(gensymed_symbol_3,Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			index_1 = index_1 + (SI_Long)1L;
			goto next_loop_15;
		      end_loop_15:
			formal_return_types = ab_loopvar_;
			goto end_7;
			formal_return_types = Qnil;
		      end_7:;
		    }
		}
	    }
	}
	if (instance_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(instance_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_declaration_class_description,
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
	    if (temp_1) {
		if (method_error_no_arg_qm)
		    add_to_frame_note_particulars_list_if_necessary(name,
			    Qno_arg_for_method_call,
			    Compiled_item_being_analyzed);
		else if (method_error_first_arg_type_not_class_qm)
		    add_to_frame_note_particular_pairs_as_necessary(Qno_item_arg_for_method_call,
			    name,method_error_first_arg_type_not_class_qm,T);
		else if (method_error_no_method_for_class_qm)
		    add_to_frame_note_particular_pairs_as_necessary(Qno_method_for_class,
			    method_first_arg_class_qm,name,T);
		else if (method_error_no_method_for_arg_count_qm) {
		    frame_key = gensym_cons_1(method_first_arg_class_qm,
			    length(arg_types));
		    add_to_frame_note_particular_pairs_as_necessary(Qno_method_for_arg_count,
			    frame_key,name,T);
		    reclaim_gensym_cons_1(frame_key);
		}
		else if (method_error_method_for_class_not_ok_qm)
		    add_to_frame_note_particular_pairs_as_necessary(Qmethod_for_class_not_okay,
			    method_first_arg_class_qm,name,T);
		else;
	    }
	    else if (formal_arg_restp_index ? FIXNUM_LT(length(arg_types),
		    FIXNUM_SUB1(length(formal_arg_types))) : 
		    FIXNUM_NE(length(arg_types),length(formal_arg_types))) {
		valid_procedure_call_qm = Nil;
		add_to_frame_note_particulars_for_counts(Qarg_count_mismatch,
			name,length(formal_arg_types),length(arg_types));
	    }
	    else if (formal_return_restp_index ? 
		    FIXNUM_LT(length(return_types),
		    FIXNUM_SUB1(length(formal_return_types))) : 
		    FIXNUM_GT(length(return_types),
		    length(formal_return_types))) {
		valid_procedure_call_qm = Nil;
		add_to_frame_note_particulars_for_counts(Qreturn_count_mismatch,
			name,length(formal_return_types),length(return_types));
	    }
	    else if (stable_procedure_call_qm) {
		arg_type = Nil;
		ab_loop_list_ = arg_types;
		index_1 = (SI_Long)0L;
		restp = EQ(FIX(index_1),formal_arg_restp_index) ? T : Nil;
		formal_arg_types_tail = formal_arg_types;
		formal_arg_type = Nil;
		formal_arg_kinds_tail = formal_arg_kinds;
		kind = Nil;
		as_handle_p = Nil;
		arg_number = (SI_Long)1L;
		ab_loop_iter_flag_ = T;
	      next_loop_16:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_16;
		arg_type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_)) {
		    index_1 = index_1 + (SI_Long)1L;
		    temp = restp;
		    if (temp);
		    else
			temp = EQ(FIX(index_1),formal_arg_restp_index) ? T 
				: Nil;
		    restp = temp;
		    formal_arg_types_tail = restp ? formal_arg_types_tail :
			     CDR(formal_arg_types_tail);
		}
		formal_arg_type = CAR(formal_arg_types_tail);
		if ( !TRUEP(ab_loop_iter_flag_))
		    formal_arg_kinds_tail = restp ? formal_arg_kinds_tail :
			     CDR(formal_arg_kinds_tail);
		kind = CAR(formal_arg_kinds_tail);
		as_handle_p = EQ(Qhandle,kind) ? T : Nil;
		if ( !TRUEP(ab_loop_iter_flag_))
		    arg_number = arg_number + (SI_Long)1L;
		if (stable_procedure_call_qm &&  !EQUAL(arg_type,
			formal_arg_type))
		    valid_procedure_call_qm = Nil;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_16;
	      end_loop_16:;
		required_type = Nil;
		ab_loop_list_ = return_types;
		index_1 = (SI_Long)0L;
		restp = EQ(FIX(index_1),formal_return_restp_index) ? T : Nil;
		formal_return_types_tail = formal_return_types;
		formal_return_type = Nil;
		return_number = (SI_Long)1L;
		ab_loop_iter_flag_ = T;
	      next_loop_17:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_17;
		required_type = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_)) {
		    index_1 = index_1 + (SI_Long)1L;
		    temp = restp;
		    if (temp);
		    else
			temp = EQ(FIX(index_1),formal_return_restp_index) ?
				 T : Nil;
		    restp = temp;
		    formal_return_types_tail = restp ? 
			    formal_return_types_tail : 
			    CDR(formal_return_types_tail);
		}
		formal_return_type = CAR(formal_return_types_tail);
		if ( !TRUEP(ab_loop_iter_flag_))
		    return_number = return_number + (SI_Long)1L;
		if (stable_procedure_call_qm &&  !EQUAL(required_type,
			formal_return_type))
		    valid_procedure_call_qm = Nil;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_17;
	      end_loop_17:;
	    }
	    else if ( !(check_for_argument_type_mismatch(name,arg_types,
		    formal_arg_types,formal_arg_kinds,
		    formal_arg_restp_index) && 
		    check_for_return_type_mismatch(name,return_types,
		    formal_return_types)))
		valid_procedure_call_qm = Nil;
	}
	reclaim_gensym_list_1(formal_arg_types);
	reclaim_gensym_list_1(formal_arg_kinds);
	reclaim_gensym_list_1(formal_return_types);
    }
    return VALUES_1(valid_procedure_call_qm);
}

/* CHECK-VALID-METHOD-DEFINITION-OF-EXISTING-CLASS */
Object check_valid_method_definition_of_existing_class(name,
	    method_first_arg_class_qm,arg_types)
    Object name, method_first_arg_class_qm, arg_types;
{
    Object arg_count, temp, trial_class, class_description_of_trial_class;
    Object unique_method_or_string_qm, scope_conses, ab_loopvar_, class_1, x2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(179,214);
    arg_count = length(arg_types);
    temp = lookup_kb_specific_property_value(name,
	    Classes_of_procedure_method_kbprop);
    trial_class = CAAR(temp);
    if (trial_class);
    else
	return VALUES_1(Qab_class);
    class_description_of_trial_class = 
	    lookup_global_or_kb_specific_property_value(trial_class,
	    Class_description_gkbprop);
    unique_method_or_string_qm = get_specific_method(name,
	    class_description_of_trial_class && 
	    (EQ(method_first_arg_class_qm,Qitem) || 
	    memq_function(method_first_arg_class_qm,
	    ISVREF(class_description_of_trial_class,(SI_Long)2L))) ? 
	    class_description_of_trial_class : 
	    lookup_global_or_kb_specific_property_value(method_first_arg_class_qm,
	    Class_description_gkbprop),arg_count,Nil,Nil,Nil);
    if ( !(unique_method_or_string_qm &&  
	    !TRUEP(text_string_p(unique_method_or_string_qm)))) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = method_first_arg_class_qm;
	class_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  temp = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  class_1 = temp;
	  unique_method_or_string_qm =  
		  !TRUEP(lookup_global_or_kb_specific_property_value(class_1,
		  Inferior_classes_gkbprop)) ? get_specific_method(name,
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop),arg_count,Nil,Nil,Nil) : Nil;
	  if (unique_method_or_string_qm &&  
		  !TRUEP(text_string_p(unique_method_or_string_qm)))
	      goto end_loop;
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
    }
    if (text_string_p(unique_method_or_string_qm)) {
	if (get_specific_methods_for_class_or_superior_class(name,
		method_first_arg_class_qm))
	    return VALUES_1(Qarg_count);
	else
	    return VALUES_1(Qab_class);
    }
    else {
	temp_1 =  !TRUEP(unique_method_or_string_qm);
	if (temp_1);
	else {
	    if (SIMPLE_VECTOR_P(unique_method_or_string_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(unique_method_or_string_qm)) 
		    > (SI_Long)2L &&  
		    !EQ(ISVREF(unique_method_or_string_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(unique_method_or_string_qm,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 =  !temp_1;
	}
	if (temp_1)
	    return VALUES_1(Qab_class);
	else
	    return VALUES_1(Nil);
    }
}

static Object Qdatum;              /* datum */

static Object Qarg_type_mismatch;  /* arg-type-mismatch */

/* CHECK-FOR-ARGUMENT-TYPE-MISMATCH */
Object check_for_argument_type_mismatch(name,arg_types,formal_arg_types,
	    formal_arg_kinds,formal_arg_restp_index)
    Object name, arg_types, formal_arg_types, formal_arg_kinds;
    Object formal_arg_restp_index;
{
    Object valid_procedure_call_qm, arg_type, ab_loop_list_;
    Object formal_arg_types_tail, formal_arg_type, formal_arg_kinds_tail, kind;
    Object as_handle_p, restp, ab_loop_iter_flag_, temp, sub_class_bit_vector;
    Object arg_key;
    SI_Long index_1, arg_number, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(179,215);
    valid_procedure_call_qm = T;
    arg_type = Nil;
    ab_loop_list_ = arg_types;
    index_1 = (SI_Long)0L;
    formal_arg_types_tail = formal_arg_types;
    formal_arg_type = Nil;
    formal_arg_kinds_tail = formal_arg_kinds;
    kind = Nil;
    as_handle_p = Nil;
    restp = EQ(FIX(index_1),formal_arg_restp_index) ? T : Nil;
    arg_number = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	index_1 = index_1 + (SI_Long)1L;
	formal_arg_types_tail = restp ? formal_arg_types_tail : 
		CDR(formal_arg_types_tail);
    }
    formal_arg_type = CAR(formal_arg_types_tail);
    if ( !TRUEP(ab_loop_iter_flag_))
	formal_arg_kinds_tail = restp ? formal_arg_kinds_tail : 
		CDR(formal_arg_kinds_tail);
    kind = CAR(formal_arg_kinds_tail);
    as_handle_p = EQ(Qhandle,kind) ? T : Nil;
    if ( !TRUEP(ab_loop_iter_flag_)) {
	temp = restp;
	if (temp);
	else
	    temp = EQ(FIX(index_1),formal_arg_restp_index) ? T : Nil;
	restp = temp;
	arg_number = arg_number + (SI_Long)1L;
    }
    temp_1 = TRUEP(type_specifications_could_intersect_p(arg_type,
	    formal_arg_type));
    if (temp_1);
    else if (type_specification_subtype_p(formal_arg_type,Qdatum)) {
	temp = arg_type;
	sub_class_bit_vector = ISVREF(ISVREF(Compiled_item_being_analyzed,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	temp_1 = TRUEP(type_specifications_could_intersect_p(temp,temp_1 ? 
		type_specification_returning_datum_type(1,formal_arg_type) 
		: type_specification_returning_datum_type_or_unknown(1,
		formal_arg_type)));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else
	temp_1 = TRUEP(type_specifications_could_be_coerced_p(arg_type,
		formal_arg_type));
    if (temp_1);
    else
	temp_1 = 
		TRUEP(datum_type_specifications_could_be_coerced_p(arg_type,
		formal_arg_type));
    if (temp_1);
    else
	temp_1 = class_type_specification_p(formal_arg_type) && 
		as_handle_p ? EQ(arg_type,Qinteger) : TRUEP(Qnil);
    if ( !temp_1) {
	arg_key = gensym_cons_1(name,FIX(arg_number));
	valid_procedure_call_qm = Nil;
	add_to_frame_note_particulars_for_counts(Qarg_type_mismatch,
		arg_key,formal_arg_type,arg_type);
	reclaim_gensym_cons_1(arg_key);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(valid_procedure_call_qm);
    return VALUES_1(Qnil);
}

static Object Qreturn_type_mismatch;  /* return-type-mismatch */

/* CHECK-FOR-RETURN-TYPE-MISMATCH */
Object check_for_return_type_mismatch(name,return_types,formal_return_types)
    Object name, return_types, formal_return_types;
{
    Object valid_procedure_call_qm, required_type, ab_loop_list_, formal_type;
    Object ab_loop_list__1, ab_loop_iter_flag_, temp_1, sub_class_bit_vector;
    Object return_key;
    SI_Long return_number, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(179,216);
    valid_procedure_call_qm = T;
    required_type = Nil;
    ab_loop_list_ = return_types;
    formal_type = Nil;
    ab_loop_list__1 = formal_return_types;
    return_number = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    required_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    formal_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_iter_flag_))
	return_number = return_number + (SI_Long)1L;
    temp = TRUEP(type_specifications_could_intersect_p(formal_type,
	    required_type));
    if (temp);
    else if (type_specification_subtype_p(required_type,Qdatum)) {
	temp_1 = formal_type;
	sub_class_bit_vector = ISVREF(ISVREF(Compiled_item_being_analyzed,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	temp = TRUEP(type_specifications_could_intersect_p(temp_1,temp ? 
		type_specification_returning_datum_type(1,required_type) : 
		type_specification_returning_datum_type_or_unknown(1,
		required_type)));
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else
	temp = TRUEP(type_specifications_could_be_coerced_p(formal_type,
		required_type));
    if (temp);
    else
	temp = 
		TRUEP(datum_type_specifications_could_be_coerced_p(formal_type,
		required_type));
    if ( !temp) {
	return_key = gensym_cons_1(name,FIX(return_number));
	valid_procedure_call_qm = Nil;
	add_to_frame_note_particulars_for_counts(Qreturn_type_mismatch,
		return_key,formal_type,required_type);
	reclaim_gensym_cons_1(return_key);
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(valid_procedure_call_qm);
    return VALUES_1(Qnil);
}

/* CHECK-FOR-VALID-STABLE-COMPILE-TIME-SELECTED-METHOD */
Object check_for_valid_stable_compile_time_selected_method(selected_class,
	    method_name,first_arg_class,arg_types,return_types)
    Object selected_class, method_name, first_arg_class, arg_types;
    Object return_types;
{
    Object first_arg_class_description_qm, method_qm, name;
    Object valid_stable_procedure_call_qm;

    x_note_fn_call(179,217);
    add_or_delete_as_item_referring_to_name(method_name);
    add_or_delete_as_item_referring_to_name(first_arg_class);
    add_or_delete_as_item_referring_to_name(selected_class);
    if ( !TRUEP(block_can_be_dependent_p(Compiled_item_being_analyzed))) {
	if ( !TRUEP(Delete_as_item_referring_to_name_qm))
	    return note_independent_item_in_stable_free_reference(Compiled_item_being_analyzed);
	else
	    return VALUES_1(Nil);
    }
    else {
	first_arg_class_description_qm = 
		lookup_global_or_kb_specific_property_value(first_arg_class,
		Class_description_gkbprop);
	method_qm = first_arg_class_description_qm ? 
		compile_time_selected_method_p(method_name,
		first_arg_class_description_qm,length(arg_types)) : Qnil;
	if ( !TRUEP(method_qm) ||  !EQ(ISVREF(method_qm,(SI_Long)31L),
		selected_class)) {
	    if ( !TRUEP(Delete_as_item_referring_to_name_qm))
		return note_invalid_stable_hierarchy(Compiled_item_being_analyzed,
			slot_value_list_3(method_name,first_arg_class,
			length(arg_types)));
	    else
		return VALUES_1(Nil);
	}
	else {
	    name = get_primary_name_for_frame_if_any(method_qm);
	    valid_stable_procedure_call_qm = 
		    check_for_valid_procedure_call(Qstable_procedure_call,
		    name,arg_types,return_types,T,method_qm);
	    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
		if ( !TRUEP(valid_stable_procedure_call_qm))
		    return note_invalid_stable_free_reference(Compiled_item_being_analyzed,
			    name);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
}

static Object Qfunction_definition;  /* function-definition */

/* CHECK-FOR-VALID-FUNCTION-CALL */
Object check_for_valid_function_call(name,arg_types)
    Object name, arg_types;
{
    Object instance_qm, formal_arg_count_qm, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(179,218);
    add_or_delete_as_item_referring_to_name(name);
    if ( !TRUEP(Delete_as_item_referring_to_name_qm)) {
	instance_qm = Nil;
	formal_arg_count_qm = Nil;
	instance_qm = get_instance_with_name_if_any(Qitem,name);
	if ( !TRUEP(instance_qm))
	    add_to_frame_note_particulars_list_if_necessary(name,
		    Qnon_existent_instances,Compiled_item_being_analyzed);
	else {
	    if (instance_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Function_definition_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Tabular_function_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Foreign_function_declaration_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		add_to_frame_note_particular_pairs_as_necessary(Qnon_existent_instances_of_class,
			Qfunction_definition,name,Nil);
		instance_qm = Nil;
	    }
	    else {
		if (instance_qm) {
		    temp_1 = ISVREF(instance_qm,(SI_Long)8L);
		    temp =  ! !TRUEP(CAR(temp_1));
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    add_to_frame_note_particulars_list_if_necessary(name,
			    Qitem_not_ok,Compiled_item_being_analyzed);
		    instance_qm = Nil;
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(instance_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Tabular_function_of_1_arg_class_description,
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
		    if (temp)
			formal_arg_count_qm = FIX((SI_Long)1L);
		    else
			formal_arg_count_qm = 
				lookup_global_or_kb_specific_property_value(name,
				Argument_range_gkbprop);
		}
	    }
	}
	if (instance_qm && formal_arg_count_qm && 
		FIXNUM_NE(length(arg_types),formal_arg_count_qm))
	    return add_to_frame_note_particulars_for_counts(Qarg_count_mismatch,
		    name,formal_arg_count_qm,length(arg_types));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-TO-FRAME-NOTE-PARTICULAR-PAIRS-AS-NECESSARY */
Object add_to_frame_note_particular_pairs_as_necessary(frame_note,pair_key,
	    pair_value,copy_pair_key_and_value_qm)
    Object frame_note, pair_key, pair_value, copy_pair_key_and_value_qm;
{
    Object existing_particulars_alist, temp, entry_for_key_qm;
    Object trigger_update_of_representations_qm;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, rest_new_value;

    x_note_fn_call(179,219);
    if (Current_computation_component_particulars)
	existing_particulars_alist = 
		get_particulars_of_frame_note_from_component_particulars(frame_note,
		Compiled_item_being_analyzed,
		Current_computation_component_particulars);
    else {
	temp = ISVREF(Compiled_item_being_analyzed,(SI_Long)8L);
	existing_particulars_alist = getfq_function_no_default(CDR(temp),
		frame_note);
    }
    entry_for_key_qm = ab_assoc_equal(pair_key,existing_particulars_alist);
    if ( !TRUEP(existing_particulars_alist)) {
	add_to_frame_note_particulars_list_if_necessary(slot_value_list_2(copy_pair_key_and_value_qm 
		? copy_for_slot_value(pair_key) : pair_key,
		copy_pair_key_and_value_qm ? 
		copy_for_slot_value(pair_value) : pair_value),frame_note,
		Compiled_item_being_analyzed);
	trigger_update_of_representations_qm = Nil;
    }
    else if ( !TRUEP(entry_for_key_qm)) {
	nconc2(existing_particulars_alist,
		slot_value_cons_1(slot_value_list_2(copy_pair_key_and_value_qm 
		? copy_for_slot_value(pair_key) : pair_key,
		copy_pair_key_and_value_qm ? 
		copy_for_slot_value(pair_value) : pair_value),Nil));
	trigger_update_of_representations_qm = T;
    }
    else if ( !TRUEP(ab_member_equal(pair_value,REST(entry_for_key_qm)))) {
	slot_value_push_modify_macro_arg = copy_pair_key_and_value_qm ? 
		copy_for_slot_value(pair_value) : pair_value;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = REST(entry_for_key_qm);
	rest_new_value = slot_value_cons_1(car_1,cdr_1);
	M_REST(entry_for_key_qm) = rest_new_value;
	trigger_update_of_representations_qm = T;
    }
    else
	trigger_update_of_representations_qm = Qnil;
    if (trigger_update_of_representations_qm)
	return add_frame_note(5,frame_note,Compiled_item_being_analyzed,
		existing_particulars_alist,Nil,Nil);
    else
	return VALUES_1(Nil);
}

/* ADD-TO-FRAME-NOTE-PARTICULARS-FOR-COUNTS */
Object add_to_frame_note_particulars_for_counts(frame_note,key,
	    associated_slot_value,listed_slot_value)
    Object frame_note, key, associated_slot_value, listed_slot_value;
{
    Object existing_particulars_alist, temp, entry_for_key_qm;
    Object trigger_update_of_representations_qm, cdr_arg, cdr_new_value;

    x_note_fn_call(179,220);
    if (Current_computation_component_particulars)
	existing_particulars_alist = 
		get_particulars_of_frame_note_from_component_particulars(frame_note,
		Compiled_item_being_analyzed,
		Current_computation_component_particulars);
    else {
	temp = ISVREF(Compiled_item_being_analyzed,(SI_Long)8L);
	existing_particulars_alist = getfq_function_no_default(CDR(temp),
		frame_note);
    }
    entry_for_key_qm = ab_assoc_equal(key,existing_particulars_alist);
    if ( !TRUEP(existing_particulars_alist)) {
	add_to_frame_note_particulars_list_if_necessary(slot_value_list_3(copy_for_slot_value(key),
		copy_for_slot_value(associated_slot_value),
		copy_for_slot_value(listed_slot_value)),frame_note,
		Compiled_item_being_analyzed);
	trigger_update_of_representations_qm = Nil;
    }
    else if ( !TRUEP(entry_for_key_qm)) {
	nconc2(existing_particulars_alist,
		slot_value_cons_1(slot_value_list_3(copy_for_slot_value(key),
		copy_for_slot_value(associated_slot_value),
		copy_for_slot_value(listed_slot_value)),Nil));
	trigger_update_of_representations_qm = T;
    }
    else if ( !TRUEP(ab_member_equal(listed_slot_value,
	    CDDR(entry_for_key_qm)))) {
	cdr_arg = last(entry_for_key_qm,_);
	cdr_new_value = 
		slot_value_cons_1(copy_for_slot_value(listed_slot_value),Nil);
	M_CDR(cdr_arg) = cdr_new_value;
	trigger_update_of_representations_qm = T;
    }
    else
	trigger_update_of_representations_qm = Qnil;
    if (trigger_update_of_representations_qm)
	return add_frame_note(5,frame_note,Compiled_item_being_analyzed,
		existing_particulars_alist,Nil,Nil);
    else
	return VALUES_1(Nil);
}

void install_INIT()
{
    Object temp, temp_1, temp_2, write_multiple_generic_formulas_note_1;
    Object reclaim_structure_for_edit_cache_1;
    Object write_problem_with_sub_frame_of_variable_note_1;
    Object write_problem_with_validity_interval_of_variable_note_1;
    Object write_problem_with_initial_value_for_simulation_note_1;
    Object write_problem_with_simulation_formula_note_1;
    Object write_problem_with_sub_frame_of_simulation_frame_note_1;
    Object write_problem_with_simulation_class_note_1;
    Object write_more_than_one_simulation_specifier_for_variable_note_1;
    Object named_dynamic_extent_description, note, ab_loop_list_;
    Object write_non_existent_instances_note_1, write_undefined_classes_note_1;
    Object write_undefined_attributes_note_1;
    Object write_undefined_attributes_of_classes_note_1;
    Object write_undefined_methods_of_classes_note_1;
    Object write_non_existent_instances_of_class_note_1;
    Object write_non_existent_instances_of_type_note_1;
    Object write_non_existent_procedure_method_note_1;
    Object write_specific_method_argument_conflict_note_1;
    Object write_no_arg_for_method_call_note_1;
    Object write_no_item_arg_for_method_call_note_1;
    Object write_no_method_for_arg_count_note_1;
    Object write_no_method_for_class_note_1;
    Object write_method_for_class_not_okay_note_1;
    Object write_arg_count_mismatch_note_1, write_return_count_mismatch_note_1;
    Object write_item_depends_on_unstable_heirarchy_note_1;
    Object write_item_depends_on_invalid_inlining_note_1;
    Object write_item_inlineable_but_has_no_parse_note_1;
    Object write_item_not_ok_note_1, write_arg_type_mismatch_note_1;
    Object write_return_type_mismatch_note_1;
    Object write_item_no_longer_dependent_note_1;
    Object write_item_depends_on_modified_stable_item_note_1;
    Object write_incompatible_validity_interval_and_data_server_note_1;
    Object AB_package, QCACHED_ITEM_NAME, Qcached_name_cons_marker, Qme;
    Object Qoperator, Qnext_to_last_of_list, Qlast_of_list, Qsecond_of_list;
    Object Qfirst_of_list, Qlist_iterator, Qnth_element, Qsystem_attribute;
    Object Qsubworkspace, Qitem_color, Qrole_server, Qab_let;
    Object Qclasses_which_define, Qanalyze_for_consistency;
    Object Qanalyze_for_consistency_for_language_parameters, Qg2_array;
    Object Qanalyze_for_consistency_for_g2_array, Qnon_action_button;
    Object Qanalyze_for_consistency_for_non_action_button;
    Object Qanalyze_for_consistency_for_simulation_subtable, Qrule;
    Object Qanalyze_for_consistency_for_rule;
    Object Qanalyze_for_consistency_for_procedure, Quser_menu_choice;
    Object Qanalyze_for_consistency_for_user_menu_choice, Qkb_search_state;
    Object Qanalyze_for_consistency_for_kb_search_state;
    Object Qinter_g2_data_request_holder;
    Object Qanalyze_for_consistency_for_inter_g2_data_request_holder;
    Object Qanalyze_for_consistency_for_new_table;
    Object Qanalyze_for_consistency_for_chart, Qgraph;
    Object Qanalyze_for_consistency_for_graph, Qtrend_chart;
    Object Qanalyze_for_consistency_for_trend_chart, Qmeter;
    Object Qanalyze_for_consistency_for_meter, Qdial;
    Object Qanalyze_for_consistency_for_dial, Qreadout_table;
    Object Qanalyze_for_consistency_for_readout_table;
    Object Qanalyze_for_consistency_for_function_definition;
    Object Qsimulation_initial_value, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_generic_simulation_formula;
    Object Qanalyze_for_consistency_for_generic_simulation_formula;
    Object Qanalyze_for_consistency_for_variable, Qframe_note_writer_1;
    Object Qgeneric_formula, Qanalyze_for_consistency_for_generic_formula;
    Object Qkb_workspace, Qanalyze_for_consistency_for_kb_workspace;
    Object Qanalyze_for_consistency_for_drawing_parameters, Qclass_definition;
    Object Qanalyze_for_consistency_for_class_definition;
    Object Qanalyze_for_consistency_for_block;
    Object Qitem_depends_on_modified_stable_item, Qitem_no_longer_dependent;
    Object list_constant_9, Qitem_depends_on_invalid_inlining;
    Object Qitem_depends_on_unstable_heirarchy, string_constant_93;
    Object string_constant_92, string_constant_91, list_constant_12;
    Object Qduplicate_class_export, Qnonexistent_static_methods_for_export;
    Object Qnonexistent_classes_for_export, Qsuperseded_attributes;
    Object list_constant_11, Qnamed_dynamic_extent_description, Qinstall;
    Object string_constant_90, Qgeneric_method_lambda_list, list_constant_10;
    Object Qcompiled_items_referring_to_this_name;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_installation_list_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, Qslot_putter;
    Object Qput_connection_style, Qput_parent_variable;
    Object Qput_simulation_formulas_qm, Qput_simulation_info_qm;
    Object Qput_non_default_initial_simulated_value_qm, Qslot_value_reclaimer;
    Object Qreclaim_simulation_details_value, Qcleanup;
    Object Qcleanup_for_simulation_subtable;
    Object Qput_simulation_subtable_initial_value_byte_code_body;
    Object Qput_simulation_subtable_byte_code_body, Qput_simulation_details;
    Object Qcleanup_for_generic_simulation_formula;
    Object Qput_generic_simulation_initial_value_byte_code_body;
    Object Qput_generic_simulation_formula_byte_code_body;
    Object Qput_box_translation_and_text_slot_value;
    Object Qput_box_translation_and_text_slot_value_for_generic_simulation_formula;
    Object Qgeneric_simulation_formulas_for_this_role;
    Object Qput_simulation_stored_history_specification_qm;
    Object Qput_variable_or_parameter_history_specification_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qput_display_update_priority;
    Object Qput_display_wait_interval, Qput_display_update_interval;
    Object Qput_background_colors, Qput_extra_grid_lines_qm;
    Object Qput_show_grid_lines_qm, Qput_scroll_continuously_qm;
    Object Qput_interval_between_horizontal_grid_lines_qm;
    Object Qput_desired_range_for_vertical_axis_qm;
    Object Qput_desired_range_for_horizontal_axis_qm;
    Object Qput_increment_per_meter_ruling, Qput_high_value_for_meter_ruling;
    Object Qput_low_value_for_meter_ruling, Qput_increment_per_dial_ruling;
    Object Qput_high_value_for_dial_ruling, Qput_low_value_for_dial_ruling;
    Object Qput_display_evaluation_should_use_simulated_values_qm;
    Object Qput_format_for_readout_table, Qput_label_to_display;
    Object Qput_expressions_to_display, Qformat_description;
    Object string_constant_89, Qrule_display_text_cell_format;
    Object Qput_background_collection_interval_qm, Qput_validity_interval;
    Object Qproblem_with_simulation_class;
    Object Qproblem_with_sub_frame_of_simulation_frame, Qedit_cache;
    Object Qreclaim_structure, Qoutstanding_edit_cache_count;
    Object Qedit_cache_structure_memory_usage, Qutilities2, string_constant_88;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_87, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qput_attribute_value, Qsimulate5;
    Object Qput_box_translation_and_text_slot_value_for_generic_formula;
    Object Qinitialize, Qinitialize_for_simulation_parameters;
    Object Qabsent_slot_putter;
    Object Qput_handle_ordering_loops_qm_where_slot_is_absent;
    Object Qhandle_ordering_loops_qm, Qsimulator_on, Ksystem_frame, Qsimulate1;
    Object string_constant_86, string_constant_85, list_constant_8;
    Object float_constant, string_constant_84, string_constant_83;
    Object string_constant_82, string_constant_81, array_constant_19;
    Object string_constant_80, Qsystem_table, Qreclaim_rule_categories_value;
    Object Qput_rule_categories, Qreclaim_focal_objects_value;
    Object Qput_focal_objects, Qreclaim_focal_classes_value;
    Object Qput_focal_classes, Qrules_of_this_class_or_object_name;
    Object Qrules_of_this_category;
    Object Qput_box_translation_and_text_slot_value_for_rule;

    x_note_fn_call(179,221);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qold_rule = STATIC_SYMBOL("OLD-RULE",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qwhenever = STATIC_SYMBOL("WHENEVER",AB_package);
    Qrule_scan_interval = STATIC_SYMBOL("RULE-SCAN-INTERVAL",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qrule_byte_code_body = STATIC_SYMBOL("RULE-BYTE-CODE-BODY",AB_package);
    Qput_box_translation_and_text_slot_value_for_rule = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-RULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_rule,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_rule,
	    NIL,FALSE,3,3));
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_rule);
    set_get(Qrule,Qput_box_translation_and_text_slot_value,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp = CONS(Qrule,temp_1);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp,
	    Qclasses_which_define);
    Qrules_of_this_category = STATIC_SYMBOL("RULES-OF-THIS-CATEGORY",
	    AB_package);
    Kb_specific_property_names = CONS(Qrules_of_this_category,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qrules_of_this_category,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Rules_of_this_category_kbprop = Qrules_of_this_category;
    Qrules_of_this_class_or_object_name = 
	    STATIC_SYMBOL("RULES-OF-THIS-CLASS-OR-OBJECT-NAME",AB_package);
    Kb_specific_property_names = CONS(Qrules_of_this_class_or_object_name,
	    Kb_specific_property_names);
    mutate_global_property(Qrules_of_this_class_or_object_name,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Rules_of_this_class_or_object_name_kbprop = 
	    Qrules_of_this_class_or_object_name;
    Qfocal_class = STATIC_SYMBOL("FOCAL-CLASS",AB_package);
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    Qput_focal_classes = STATIC_SYMBOL("PUT-FOCAL-CLASSES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_focal_classes,
	    STATIC_FUNCTION(put_focal_classes,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qfocal_classes,
	    SYMBOL_FUNCTION(Qput_focal_classes),Qslot_putter);
    Qreclaim_focal_classes_value = 
	    STATIC_SYMBOL("RECLAIM-FOCAL-CLASSES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_focal_classes_value,
	    STATIC_FUNCTION(reclaim_focal_classes_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qfocal_classes,
	    SYMBOL_FUNCTION(Qreclaim_focal_classes_value),
	    Qslot_value_reclaimer);
    Qfocal_object_name = STATIC_SYMBOL("FOCAL-OBJECT-NAME",AB_package);
    Qfocal_objects = STATIC_SYMBOL("FOCAL-OBJECTS",AB_package);
    Qput_focal_objects = STATIC_SYMBOL("PUT-FOCAL-OBJECTS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_focal_objects,
	    STATIC_FUNCTION(put_focal_objects,NIL,FALSE,3,3));
    mutate_global_property(Qfocal_objects,
	    SYMBOL_FUNCTION(Qput_focal_objects),Qslot_putter);
    Qreclaim_focal_objects_value = 
	    STATIC_SYMBOL("RECLAIM-FOCAL-OBJECTS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_focal_objects_value,
	    STATIC_FUNCTION(reclaim_focal_objects_value,NIL,FALSE,2,2));
    mutate_global_property(Qfocal_objects,
	    SYMBOL_FUNCTION(Qreclaim_focal_objects_value),
	    Qslot_value_reclaimer);
    Qrule_category_name = STATIC_SYMBOL("RULE-CATEGORY-NAME",AB_package);
    Qrule_categories = STATIC_SYMBOL("RULE-CATEGORIES",AB_package);
    Qput_rule_categories = STATIC_SYMBOL("PUT-RULE-CATEGORIES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_categories,
	    STATIC_FUNCTION(put_rule_categories,NIL,FALSE,3,3));
    mutate_global_property(Qrule_categories,
	    SYMBOL_FUNCTION(Qput_rule_categories),Qslot_putter);
    Qreclaim_rule_categories_value = 
	    STATIC_SYMBOL("RECLAIM-RULE-CATEGORIES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_rule_categories_value,
	    STATIC_FUNCTION(reclaim_rule_categories_value,NIL,FALSE,2,2));
    mutate_global_property(Qrule_categories,
	    SYMBOL_FUNCTION(Qreclaim_rule_categories_value),
	    Qslot_value_reclaimer);
    Qsimulation_parameters = STATIC_SYMBOL("SIMULATION-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_8 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qsimulation_parameters,
	    list_constant_8);
    string_constant_80 = STATIC_STRING("1l1l83ey");
    array_constant_19 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_19,(SI_Long)0L,0.5);
    string_constant_81 = 
	    STATIC_STRING("1t4z8r83Bfy83Bfy83aCy83aCy09k001n1l8l1m8p832iy1l8o000004z8r83D*y83D*y83aCy83aCy0833uy001n1l8l1m8p833Py1l8o000004z8r83aIy83aIy83a");
    string_constant_82 = 
	    STATIC_STRING("Cy83aCy00001n1l8l1m8p83Ky1l8o000004z8r83Zay83Zay83aCy83aCy00001m1l8l1l8o000004z8r83L3y83L3y83aCy83aCy00001n1l8l1n8p834vy83Gy1l8o");
    string_constant_83 = 
	    STATIC_STRING("000004z8r83F3y83F3y83aCy83aCy00001n1l8l1m8p8306y1l8o000004z8r83Zpy83Zpy83aCy83aCy00001n1l8l1m8p83Ky1l8o000004z8r83dpy83dpy83aCy8");
    string_constant_84 = 
	    STATIC_STRING("3aCy00001m1l8l1l8o000004z8r83dty83dty83aCy83aCy00001m1l8l1l8o00000");
    float_constant = STATIC_FLOAT(0.5);
    string_constant_85 = 
	    STATIC_STRING("1v8q1n83aCy1l83-sy83ey1p83Bfy9k8l1m8p832iy8o1p83D*y833uy8l1m8p833Py8o1p83aIy08l1m8p83Ky8o1o83Zay08l8o1p83L3y08l1n8p834vy83Gy8o1p");
    string_constant_86 = 
	    STATIC_STRING("83F3y08l1m8p8306y8o1p83Zpy08l1m8p83Ky8o1o83dpy08l8o1o83dty08l8o");
    temp_1 = regenerate_optimized_constant(string_constant_80);
    clear_optimized_constants();
    push_optimized_constant(array_constant_19);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_81,
	    string_constant_82,string_constant_83,string_constant_84));
    clear_optimized_constants();
    push_optimized_constant(float_constant);
    add_class_to_environment(9,Qsimulation_parameters,list_constant_8,Nil,
	    temp_1,Nil,temp_2,list_constant_8,
	    regenerate_optimized_constant(LIST_2(string_constant_85,
	    string_constant_86)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_parameters,Simulation_parameters);
    Qsimulate1 = STATIC_SYMBOL("SIMULATE1",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qsimulation_parameters,Qsimulate1,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qsimulator_on_qm = STATIC_SYMBOL("SIMULATOR-ON\?",AB_package);
    Qsimulator_on = STATIC_SYMBOL("SIMULATOR-ON",AB_package);
    alias_slot_name(3,Qsimulator_on_qm,Qsimulator_on,Qnil);
    Qhandle_ordering_loops_qm = STATIC_SYMBOL("HANDLE-ORDERING-LOOPS\?",
	    AB_package);
    Qput_handle_ordering_loops_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-HANDLE-ORDERING-LOOPS\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_handle_ordering_loops_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_handle_ordering_loops_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qhandle_ordering_loops_qm,
	    SYMBOL_FUNCTION(Qput_handle_ordering_loops_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitialize_for_simulation_parameters = 
	    STATIC_SYMBOL("INITIALIZE-FOR-SIMULATION-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_simulation_parameters,
	    STATIC_FUNCTION(initialize_for_simulation_parameters,NIL,FALSE,
	    1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_for_simulation_parameters);
    set_get(Qsimulation_parameters,Qinitialize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp = CONS(Qsimulation_parameters,temp_1);
    mutate_global_property(Qinitialize,temp,Qclasses_which_define);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qput_box_translation_and_text_slot_value_for_generic_formula = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-GENERIC-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_generic_formula,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_generic_formula,
	    NIL,FALSE,3,3));
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    temp = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_generic_formula);
    set_get(Qgeneric_formula,Qput_box_translation_and_text_slot_value,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_formula,temp_1);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp,
	    Qclasses_which_define);
    Qmultiple_generic_formulas = STATIC_SYMBOL("MULTIPLE-GENERIC-FORMULAS",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant = 
	    STATIC_STRING("this is not the only generic formula for the ~(~A~) of a ~(~A~)");
    write_multiple_generic_formulas_note_1 = 
	    STATIC_FUNCTION(write_multiple_generic_formulas_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmultiple_generic_formulas,
	    write_multiple_generic_formulas_note_1,Qframe_note_writer_1);
    Qgeneric_simulation_formulas_used_p = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULAS-USED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgeneric_simulation_formulas_used_p,
	    Generic_simulation_formulas_used_p);
    Qsimulate5 = STATIC_SYMBOL("SIMULATE5",AB_package);
    record_system_variable(Qgeneric_simulation_formulas_used_p,Qsimulate5,
	    Nil,Qnil,Qt,Qnil,Qt);
    Qput_attribute_value = STATIC_SYMBOL("PUT-ATTRIBUTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_attribute_value,
	    STATIC_FUNCTION(put_attribute_value,NIL,TRUE,4,5));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qg2_defstruct_structure_name_edit_cache_g2_struct = 
	    STATIC_SYMBOL("EDIT-CACHE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qedit_cache = STATIC_SYMBOL("EDIT-CACHE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_edit_cache_g2_struct,
	    Qedit_cache,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qedit_cache,
	    Qg2_defstruct_structure_name_edit_cache_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_edit_cache == UNBOUND)
	The_type_description_of_edit_cache = Nil;
    string_constant_87 = 
	    STATIC_STRING("43Dy8m83gvy1n83gvy8n8k1l8n0000001l1m83My83-AAykok0k0");
    temp_1 = The_type_description_of_edit_cache;
    The_type_description_of_edit_cache = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_87));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_edit_cache_g2_struct,
	    The_type_description_of_edit_cache,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qedit_cache,The_type_description_of_edit_cache,
	    Qtype_description_of_type);
    Qoutstanding_edit_cache_count = 
	    STATIC_SYMBOL("OUTSTANDING-EDIT-CACHE-COUNT",AB_package);
    Qedit_cache_structure_memory_usage = 
	    STATIC_SYMBOL("EDIT-CACHE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_88 = STATIC_STRING("1q83gvy8s83-SFy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_edit_cache_count);
    push_optimized_constant(Qedit_cache_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_88));
    Qchain_of_available_edit_caches = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EDIT-CACHES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_edit_caches,
	    Chain_of_available_edit_caches);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_edit_caches,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qedit_cache_count = STATIC_SYMBOL("EDIT-CACHE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qedit_cache_count,Edit_cache_count);
    record_system_variable(Qedit_cache_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_edit_caches_vector == UNBOUND)
	Chain_of_available_edit_caches_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qedit_cache_structure_memory_usage,
	    STATIC_FUNCTION(edit_cache_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_edit_cache_count,
	    STATIC_FUNCTION(outstanding_edit_cache_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_edit_cache_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_edit_cache,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qedit_cache,
	    reclaim_structure_for_edit_cache_1);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qproblem_with_sub_frame_of_variable = 
	    STATIC_SYMBOL("PROBLEM-WITH-SUB-FRAME-OF-VARIABLE",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qsimulation = STATIC_SYMBOL("SIMULATION",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING(" has problems");
    string_constant_2 = STATIC_STRING(" have problems");
    string_constant_3 = STATIC_STRING(", ");
    string_constant_4 = STATIC_STRING(", and ");
    string_constant_5 = STATIC_STRING(" and ");
    write_problem_with_sub_frame_of_variable_note_1 = 
	    STATIC_FUNCTION(write_problem_with_sub_frame_of_variable_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qproblem_with_sub_frame_of_variable,
	    write_problem_with_sub_frame_of_variable_note_1,
	    Qframe_note_writer_1);
    Qproblem_with_validity_interval_of_variable = 
	    STATIC_SYMBOL("PROBLEM-WITH-VALIDITY-INTERVAL-OF-VARIABLE",
	    AB_package);
    Qvalidity_interval_of_sensor_variable_is_supplied = 
	    STATIC_SYMBOL("VALIDITY-INTERVAL-OF-SENSOR-VARIABLE-IS-SUPPLIED",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)44L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)45L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)48L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)50L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)51L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)52L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)54L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)57L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)58L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)59L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)60L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)61L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)62L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)63L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)64L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)65L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)78L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)79L,(SI_Long)57344L);
    Qmissing_validity_interval = STATIC_SYMBOL("MISSING-VALIDITY-INTERVAL",
	    AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    write_problem_with_validity_interval_of_variable_note_1 = 
	    STATIC_FUNCTION(write_problem_with_validity_interval_of_variable_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qproblem_with_validity_interval_of_variable,
	    write_problem_with_validity_interval_of_variable_note_1,
	    Qframe_note_writer_1);
    Qproblem_with_initial_value_for_simulation = 
	    STATIC_SYMBOL("PROBLEM-WITH-INITIAL-VALUE-FOR-SIMULATION",
	    AB_package);
    Qmissing_initial_value = STATIC_SYMBOL("MISSING-INITIAL-VALUE",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)43L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)45L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)46L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)48L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)49L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)50L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)51L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)54L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)55L,(SI_Long)57344L);
    Qunused_initial_value = STATIC_SYMBOL("UNUSED-INITIAL-VALUE",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    write_problem_with_initial_value_for_simulation_note_1 = 
	    STATIC_FUNCTION(write_problem_with_initial_value_for_simulation_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qproblem_with_initial_value_for_simulation,
	    write_problem_with_initial_value_for_simulation_note_1,
	    Qframe_note_writer_1);
    Qproblem_with_simulation_formula = 
	    STATIC_SYMBOL("PROBLEM-WITH-SIMULATION-FORMULA",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)40L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    write_problem_with_simulation_formula_note_1 = 
	    STATIC_FUNCTION(write_problem_with_simulation_formula_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qproblem_with_simulation_formula,
	    write_problem_with_simulation_formula_note_1,Qframe_note_writer_1);
    Qproblem_with_sub_frame_of_simulation_frame = 
	    STATIC_SYMBOL("PROBLEM-WITH-SUB-FRAME-OF-SIMULATION-FRAME",
	    AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    write_problem_with_sub_frame_of_simulation_frame_note_1 = 
	    STATIC_FUNCTION(write_problem_with_sub_frame_of_simulation_frame_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qproblem_with_sub_frame_of_simulation_frame,
	    write_problem_with_sub_frame_of_simulation_frame_note_1,
	    Qframe_note_writer_1);
    Qproblem_with_simulation_class = 
	    STATIC_SYMBOL("PROBLEM-WITH-SIMULATION-CLASS",AB_package);
    Qmissing_simulation_class = STATIC_SYMBOL("MISSING-SIMULATION-CLASS",
	    AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    write_problem_with_simulation_class_note_1 = 
	    STATIC_FUNCTION(write_problem_with_simulation_class_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qproblem_with_simulation_class,
	    write_problem_with_simulation_class_note_1,Qframe_note_writer_1);
    if (Changing_validity_interval_invalidates_current_value_p == UNBOUND)
	Changing_validity_interval_invalidates_current_value_p = T;
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    Qput_validity_interval = STATIC_SYMBOL("PUT-VALIDITY-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_validity_interval,
	    STATIC_FUNCTION(put_validity_interval,NIL,FALSE,3,3));
    mutate_global_property(Qvalidity_interval,
	    SYMBOL_FUNCTION(Qput_validity_interval),Qslot_putter);
    Qbackground_collection_interval_qm = 
	    STATIC_SYMBOL("BACKGROUND-COLLECTION-INTERVAL\?",AB_package);
    Qg2_defstruct_structure_name_data_server_g2_struct = 
	    STATIC_SYMBOL("DATA-SERVER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    Qput_background_collection_interval_qm = 
	    STATIC_SYMBOL("PUT-BACKGROUND-COLLECTION-INTERVAL\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_background_collection_interval_qm,
	    STATIC_FUNCTION(put_background_collection_interval_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qbackground_collection_interval_qm,
	    SYMBOL_FUNCTION(Qput_background_collection_interval_qm),
	    Qslot_putter);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qunused_intial_value = STATIC_SYMBOL("UNUSED-INTIAL-VALUE",AB_package);
    Qrule_display_text_cell_format = 
	    STATIC_SYMBOL("RULE-DISPLAY-TEXT-CELL-FORMAT",AB_package);
    string_constant_89 = STATIC_STRING("1r83-Qy83kyk83uys83iy33my");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qrule_display_text_cell_format,
	    regenerate_optimized_constant(string_constant_89),
	    Qformat_description);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qlist_of_plots = STATIC_SYMBOL("LIST-OF-PLOTS",AB_package);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qput_expressions_to_display = 
	    STATIC_SYMBOL("PUT-EXPRESSIONS-TO-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_expressions_to_display,
	    STATIC_FUNCTION(put_expressions_to_display,NIL,FALSE,3,3));
    mutate_global_property(Qexpressions_to_display,
	    SYMBOL_FUNCTION(Qput_expressions_to_display),Qslot_putter);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qlabel_to_display = STATIC_SYMBOL("LABEL-TO-DISPLAY",AB_package);
    Qput_label_to_display = STATIC_SYMBOL("PUT-LABEL-TO-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_label_to_display,
	    STATIC_FUNCTION(put_label_to_display,NIL,FALSE,3,3));
    mutate_global_property(Qlabel_to_display,
	    SYMBOL_FUNCTION(Qput_label_to_display),Qslot_putter);
    Qformat_for_readout_table = STATIC_SYMBOL("FORMAT-FOR-READOUT-TABLE",
	    AB_package);
    Qput_format_for_readout_table = 
	    STATIC_SYMBOL("PUT-FORMAT-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_format_for_readout_table,
	    STATIC_FUNCTION(put_format_for_readout_table,NIL,FALSE,3,3));
    mutate_global_property(Qformat_for_readout_table,
	    SYMBOL_FUNCTION(Qput_format_for_readout_table),Qslot_putter);
    Qdisplay_evaluation_should_use_simulated_values_qm = 
	    STATIC_SYMBOL("DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES\?",
	    AB_package);
    Qput_display_evaluation_should_use_simulated_values_qm = 
	    STATIC_SYMBOL("PUT-DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_display_evaluation_should_use_simulated_values_qm,
	    STATIC_FUNCTION(put_display_evaluation_should_use_simulated_values_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qdisplay_evaluation_should_use_simulated_values_qm,
	    SYMBOL_FUNCTION(Qput_display_evaluation_should_use_simulated_values_qm),
	    Qslot_putter);
    Qlow_value_for_dial_ruling = STATIC_SYMBOL("LOW-VALUE-FOR-DIAL-RULING",
	    AB_package);
    Qput_low_value_for_dial_ruling = 
	    STATIC_SYMBOL("PUT-LOW-VALUE-FOR-DIAL-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_low_value_for_dial_ruling,
	    STATIC_FUNCTION(put_low_value_for_dial_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qlow_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qput_low_value_for_dial_ruling),Qslot_putter);
    Qhigh_value_for_dial_ruling = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-DIAL-RULING",AB_package);
    Qput_high_value_for_dial_ruling = 
	    STATIC_SYMBOL("PUT-HIGH-VALUE-FOR-DIAL-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_high_value_for_dial_ruling,
	    STATIC_FUNCTION(put_high_value_for_dial_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qhigh_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qput_high_value_for_dial_ruling),Qslot_putter);
    Qincrement_per_dial_ruling = STATIC_SYMBOL("INCREMENT-PER-DIAL-RULING",
	    AB_package);
    Qput_increment_per_dial_ruling = 
	    STATIC_SYMBOL("PUT-INCREMENT-PER-DIAL-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_increment_per_dial_ruling,
	    STATIC_FUNCTION(put_increment_per_dial_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qincrement_per_dial_ruling,
	    SYMBOL_FUNCTION(Qput_increment_per_dial_ruling),Qslot_putter);
    Qlow_value_for_meter_ruling = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-METER-RULING",AB_package);
    Qput_low_value_for_meter_ruling = 
	    STATIC_SYMBOL("PUT-LOW-VALUE-FOR-METER-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_low_value_for_meter_ruling,
	    STATIC_FUNCTION(put_low_value_for_meter_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qlow_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qput_low_value_for_meter_ruling),Qslot_putter);
    Qhigh_value_for_meter_ruling = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-METER-RULING",AB_package);
    Qput_high_value_for_meter_ruling = 
	    STATIC_SYMBOL("PUT-HIGH-VALUE-FOR-METER-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_high_value_for_meter_ruling,
	    STATIC_FUNCTION(put_high_value_for_meter_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qhigh_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qput_high_value_for_meter_ruling),Qslot_putter);
    Qincrement_per_meter_ruling = 
	    STATIC_SYMBOL("INCREMENT-PER-METER-RULING",AB_package);
    Qput_increment_per_meter_ruling = 
	    STATIC_SYMBOL("PUT-INCREMENT-PER-METER-RULING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_increment_per_meter_ruling,
	    STATIC_FUNCTION(put_increment_per_meter_ruling,NIL,FALSE,3,3));
    mutate_global_property(Qincrement_per_meter_ruling,
	    SYMBOL_FUNCTION(Qput_increment_per_meter_ruling),Qslot_putter);
    Qwithout_tickmark_labels = STATIC_SYMBOL("WITHOUT-TICKMARK-LABELS",
	    AB_package);
    Qdesired_range_for_horizontal_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-HORIZONTAL-AXIS\?",AB_package);
    Qput_desired_range_for_horizontal_axis_qm = 
	    STATIC_SYMBOL("PUT-DESIRED-RANGE-FOR-HORIZONTAL-AXIS\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_desired_range_for_horizontal_axis_qm,
	    STATIC_FUNCTION(put_desired_range_for_horizontal_axis_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qdesired_range_for_horizontal_axis_qm,
	    SYMBOL_FUNCTION(Qput_desired_range_for_horizontal_axis_qm),
	    Qslot_putter);
    Qdesired_range_for_vertical_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-VERTICAL-AXIS\?",AB_package);
    Qput_desired_range_for_vertical_axis_qm = 
	    STATIC_SYMBOL("PUT-DESIRED-RANGE-FOR-VERTICAL-AXIS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_desired_range_for_vertical_axis_qm,
	    STATIC_FUNCTION(put_desired_range_for_vertical_axis_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qdesired_range_for_vertical_axis_qm,
	    SYMBOL_FUNCTION(Qput_desired_range_for_vertical_axis_qm),
	    Qslot_putter);
    Qinterval_between_horizontal_grid_lines_qm = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES\?",
	    AB_package);
    Qput_interval_between_horizontal_grid_lines_qm = 
	    STATIC_SYMBOL("PUT-INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_interval_between_horizontal_grid_lines_qm,
	    STATIC_FUNCTION(put_interval_between_horizontal_grid_lines_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qinterval_between_horizontal_grid_lines_qm,
	    SYMBOL_FUNCTION(Qput_interval_between_horizontal_grid_lines_qm),
	    Qslot_putter);
    Qscroll_continuously_qm = STATIC_SYMBOL("SCROLL-CONTINUOUSLY\?",
	    AB_package);
    Qput_scroll_continuously_qm = 
	    STATIC_SYMBOL("PUT-SCROLL-CONTINUOUSLY\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_scroll_continuously_qm,
	    STATIC_FUNCTION(put_scroll_continuously_qm,NIL,FALSE,3,3));
    mutate_global_property(Qscroll_continuously_qm,
	    SYMBOL_FUNCTION(Qput_scroll_continuously_qm),Qslot_putter);
    Qshow_grid_lines_qm = STATIC_SYMBOL("SHOW-GRID-LINES\?",AB_package);
    Qput_show_grid_lines_qm = STATIC_SYMBOL("PUT-SHOW-GRID-LINES\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_show_grid_lines_qm,
	    STATIC_FUNCTION(put_show_grid_lines_qm,NIL,FALSE,3,3));
    mutate_global_property(Qshow_grid_lines_qm,
	    SYMBOL_FUNCTION(Qput_show_grid_lines_qm),Qslot_putter);
    Qextra_grid_lines_qm = STATIC_SYMBOL("EXTRA-GRID-LINES\?",AB_package);
    Qput_extra_grid_lines_qm = STATIC_SYMBOL("PUT-EXTRA-GRID-LINES\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_extra_grid_lines_qm,
	    STATIC_FUNCTION(put_extra_grid_lines_qm,NIL,FALSE,3,3));
    mutate_global_property(Qextra_grid_lines_qm,
	    SYMBOL_FUNCTION(Qput_extra_grid_lines_qm),Qslot_putter);
    Qbackground_colors = STATIC_SYMBOL("BACKGROUND-COLORS",AB_package);
    Qput_background_colors = STATIC_SYMBOL("PUT-BACKGROUND-COLORS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_background_colors,
	    STATIC_FUNCTION(put_background_colors,NIL,FALSE,3,3));
    mutate_global_property(Qbackground_colors,
	    SYMBOL_FUNCTION(Qput_background_colors),Qslot_putter);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    Qput_display_update_interval = 
	    STATIC_SYMBOL("PUT-DISPLAY-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_display_update_interval,
	    STATIC_FUNCTION(put_display_update_interval,NIL,FALSE,3,3));
    mutate_global_property(Qdisplay_update_interval,
	    SYMBOL_FUNCTION(Qput_display_update_interval),Qslot_putter);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qput_display_wait_interval = STATIC_SYMBOL("PUT-DISPLAY-WAIT-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_display_wait_interval,
	    STATIC_FUNCTION(put_display_wait_interval,NIL,FALSE,3,3));
    mutate_global_property(Qdisplay_wait_interval,
	    SYMBOL_FUNCTION(Qput_display_wait_interval),Qslot_putter);
    Qput_display_update_priority = 
	    STATIC_SYMBOL("PUT-DISPLAY-UPDATE-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_display_update_priority,
	    STATIC_FUNCTION(put_display_update_priority,NIL,FALSE,3,3));
    mutate_global_property(Qdisplay_update_priority,
	    SYMBOL_FUNCTION(Qput_display_update_priority),Qslot_putter);
    Qscheduled_display_update = STATIC_SYMBOL("SCHEDULED-DISPLAY-UPDATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qscheduled_display_update,
	    STATIC_FUNCTION(scheduled_display_update,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_stored_history_specification_qm = 
	    STATIC_SYMBOL("SIMULATION-STORED-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qvariable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qput_variable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("PUT-VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_variable_or_parameter_history_specification_qm,
	    STATIC_FUNCTION(put_variable_or_parameter_history_specification_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qvariable_or_parameter_history_specification_qm,
	    SYMBOL_FUNCTION(Qput_variable_or_parameter_history_specification_qm),
	    Qslot_putter);
    Qput_simulation_stored_history_specification_qm = 
	    STATIC_SYMBOL("PUT-SIMULATION-STORED-HISTORY-SPECIFICATION\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_stored_history_specification_qm,
	    STATIC_FUNCTION(put_simulation_stored_history_specification_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_stored_history_specification_qm,
	    SYMBOL_FUNCTION(Qput_simulation_stored_history_specification_qm),
	    Qslot_putter);
    Qgeneric_simulation_formulas_for_this_role = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULAS-FOR-THIS-ROLE",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qgeneric_simulation_formulas_for_this_role,
	    Kb_specific_property_names);
    mutate_global_property(Qgeneric_simulation_formulas_for_this_role,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Generic_simulation_formulas_for_this_role_kbprop = 
	    Qgeneric_simulation_formulas_for_this_role;
    Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm = 
	    STATIC_SYMBOL("POST-ANALYZER-WARNING-NOTES-FOR-GENERIC-SIMULATION-FORMULAS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm,
	    Post_analyzer_warning_notes_for_generic_simulation_formulas_qm);
    Qinstall = STATIC_SYMBOL("INSTALL",AB_package);
    record_system_variable(Qpost_analyzer_warning_notes_for_generic_simulation_formulas_qm,
	    Qinstall,Nil,Qnil,Qnil,Qnil,Qnil);
    Qput_box_translation_and_text_slot_value_for_generic_simulation_formula 
	    = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_generic_simulation_formula,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_generic_simulation_formula,
	    NIL,FALSE,3,3));
    temp = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_generic_simulation_formula);
    set_get(Qgeneric_simulation_formula,
	    Qput_box_translation_and_text_slot_value,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_simulation_formula,temp_1);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp,
	    Qclasses_which_define);
    Qgeneric_simulation_formula_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA-BYTE-CODE-BODY",
	    AB_package);
    Qput_generic_simulation_formula_byte_code_body = 
	    STATIC_SYMBOL("PUT-GENERIC-SIMULATION-FORMULA-BYTE-CODE-BODY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_generic_simulation_formula_byte_code_body,
	    STATIC_FUNCTION(put_generic_simulation_formula_byte_code_body,
	    NIL,FALSE,3,3));
    mutate_global_property(Qgeneric_simulation_formula_byte_code_body,
	    SYMBOL_FUNCTION(Qput_generic_simulation_formula_byte_code_body),
	    Qslot_putter);
    Qgeneric_simulation_initial_value_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qput_generic_simulation_initial_value_byte_code_body = 
	    STATIC_SYMBOL("PUT-GENERIC-SIMULATION-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_generic_simulation_initial_value_byte_code_body,
	    STATIC_FUNCTION(put_generic_simulation_initial_value_byte_code_body,
	    NIL,FALSE,3,3));
    mutate_global_property(Qgeneric_simulation_initial_value_byte_code_body,
	    SYMBOL_FUNCTION(Qput_generic_simulation_initial_value_byte_code_body),
	    Qslot_putter);
    Qcleanup_for_generic_simulation_formula = 
	    STATIC_SYMBOL("CLEANUP-FOR-GENERIC-SIMULATION-FORMULA",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_generic_simulation_formula,
	    STATIC_FUNCTION(cleanup_for_generic_simulation_formula,NIL,
	    FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp = SYMBOL_FUNCTION(Qcleanup_for_generic_simulation_formula);
    set_get(Qgeneric_simulation_formula,Qcleanup,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_simulation_formula,temp_1);
    mutate_global_property(Qcleanup,temp,Qclasses_which_define);
    Qfocal_entity_for_simulation_formula = 
	    STATIC_SYMBOL("FOCAL-ENTITY-FOR-SIMULATION-FORMULA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfocal_entity_for_simulation_formula,
	    Focal_entity_for_simulation_formula);
    record_system_variable(Qfocal_entity_for_simulation_formula,Qinstall,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qget_focal_entity_for_simulation_formula_qm = 
	    STATIC_SYMBOL("GET-FOCAL-ENTITY-FOR-SIMULATION-FORMULA\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qget_focal_entity_for_simulation_formula_qm,
	    Get_focal_entity_for_simulation_formula_qm);
    record_system_variable(Qget_focal_entity_for_simulation_formula_qm,
	    Qinstall,Nil,Qnil,Qnil,Qnil,Qnil);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qput_simulation_details = STATIC_SYMBOL("PUT-SIMULATION-DETAILS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_details,
	    STATIC_FUNCTION(put_simulation_details,NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_details,
	    SYMBOL_FUNCTION(Qput_simulation_details),Qslot_putter);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qhistory_specification_for_simulation_subtables_qm = 
	    STATIC_SYMBOL("HISTORY-SPECIFICATION-FOR-SIMULATION-SUBTABLES\?",
	    AB_package);
    Qparent_variable = STATIC_SYMBOL("PARENT-VARIABLE",AB_package);
    Qsimulation_subtable_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-BYTE-CODE-BODY",AB_package);
    Qput_simulation_subtable_byte_code_body = 
	    STATIC_SYMBOL("PUT-SIMULATION-SUBTABLE-BYTE-CODE-BODY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_subtable_byte_code_body,
	    STATIC_FUNCTION(put_simulation_subtable_byte_code_body,NIL,
	    FALSE,3,3));
    mutate_global_property(Qsimulation_subtable_byte_code_body,
	    SYMBOL_FUNCTION(Qput_simulation_subtable_byte_code_body),
	    Qslot_putter);
    Qsimulation_subtable_initial_value_byte_code_body = 
	    STATIC_SYMBOL("SIMULATION-SUBTABLE-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    Qput_simulation_subtable_initial_value_byte_code_body = 
	    STATIC_SYMBOL("PUT-SIMULATION-SUBTABLE-INITIAL-VALUE-BYTE-CODE-BODY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_subtable_initial_value_byte_code_body,
	    STATIC_FUNCTION(put_simulation_subtable_initial_value_byte_code_body,
	    NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_subtable_initial_value_byte_code_body,
	    SYMBOL_FUNCTION(Qput_simulation_subtable_initial_value_byte_code_body),
	    Qslot_putter);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    Qsimulation_formulas_qm = STATIC_SYMBOL("SIMULATION-FORMULAS\?",
	    AB_package);
    Qcleanup_for_simulation_subtable = 
	    STATIC_SYMBOL("CLEANUP-FOR-SIMULATION-SUBTABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_simulation_subtable,
	    STATIC_FUNCTION(cleanup_for_simulation_subtable,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qcleanup_for_simulation_subtable);
    set_get(Qsimulation_subtable,Qcleanup,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp = CONS(Qsimulation_subtable,temp_1);
    mutate_global_property(Qcleanup,temp,Qclasses_which_define);
    Qreclaim_simulation_details_value = 
	    STATIC_SYMBOL("RECLAIM-SIMULATION-DETAILS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_simulation_details_value,
	    STATIC_FUNCTION(reclaim_simulation_details_value,NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_details,
	    SYMBOL_FUNCTION(Qreclaim_simulation_details_value),
	    Qslot_value_reclaimer);
    Qnon_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",AB_package);
    Qput_non_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("PUT-NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_non_default_initial_simulated_value_qm,
	    STATIC_FUNCTION(put_non_default_initial_simulated_value_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qnon_default_initial_simulated_value_qm,
	    SYMBOL_FUNCTION(Qput_non_default_initial_simulated_value_qm),
	    Qslot_putter);
    Qinhibit_model_install_qm = STATIC_SYMBOL("INHIBIT-MODEL-INSTALL\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinhibit_model_install_qm,
	    Inhibit_model_install_qm);
    record_system_variable(Qinhibit_model_install_qm,Qinstall,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qmore_than_one_simulation_specifier_for_variable = 
	    STATIC_SYMBOL("MORE-THAN-ONE-SIMULATION-SPECIFIER-FOR-VARIABLE",
	    AB_package);
    string_constant_6 = 
	    STATIC_STRING("Installation problem:  variable-or-parameter ~NF has more than one simulation specifier");
    Qput_simulation_info_qm = STATIC_SYMBOL("PUT-SIMULATION-INFO\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_info_qm,
	    STATIC_FUNCTION(put_simulation_info_qm,NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_info_qm,
	    SYMBOL_FUNCTION(Qput_simulation_info_qm),Qslot_putter);
    array_constant_10 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)34L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)36L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)44L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)46L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)48L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)49L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)51L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)54L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)55L,(SI_Long)57344L);
    write_more_than_one_simulation_specifier_for_variable_note_1 = 
	    STATIC_FUNCTION(write_more_than_one_simulation_specifier_for_variable_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmore_than_one_simulation_specifier_for_variable,
	    write_more_than_one_simulation_specifier_for_variable_note_1,
	    Qframe_note_writer_1);
    Quse_initial_value_expression_in_generic_simulation_formula = 
	    STATIC_SYMBOL("USE-INITIAL-VALUE-EXPRESSION-IN-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    Qexternal = STATIC_SYMBOL("EXTERNAL",AB_package);
    Qput_simulation_formulas_qm = 
	    STATIC_SYMBOL("PUT-SIMULATION-FORMULAS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_formulas_qm,
	    STATIC_FUNCTION(put_simulation_formulas_qm,NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_formulas_qm,
	    SYMBOL_FUNCTION(Qput_simulation_formulas_qm),Qslot_putter);
    Qput_parent_variable = STATIC_SYMBOL("PUT-PARENT-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_parent_variable,
	    STATIC_FUNCTION(put_parent_variable,NIL,FALSE,3,3));
    mutate_global_property(Qparent_variable,
	    SYMBOL_FUNCTION(Qput_parent_variable),Qslot_putter);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    Qws_representation = STATIC_SYMBOL("WS-REPRESENTATION",AB_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    Qitem_change = STATIC_SYMBOL("ITEM-CHANGE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qput_connection_style = STATIC_SYMBOL("PUT-CONNECTION-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_connection_style,
	    STATIC_FUNCTION(put_connection_style,NIL,FALSE,3,3));
    mutate_global_property(Qconnection_style,
	    SYMBOL_FUNCTION(Qput_connection_style),Qslot_putter);
    Qconnection_post = STATIC_SYMBOL("CONNECTION-POST",AB_package);
    if (Post_kb_loading_consistency_analysis == UNBOUND)
	Post_kb_loading_consistency_analysis = Nil;
    Qinstallation = STATIC_SYMBOL("INSTALLATION",AB_package);
    Qcompiled_items_referring_to_this_name = 
	    STATIC_SYMBOL("COMPILED-ITEMS-REFERRING-TO-THIS-NAME",AB_package);
    Kb_specific_property_names = 
	    CONS(Qcompiled_items_referring_to_this_name,
	    Kb_specific_property_names);
    mutate_global_property(Qcompiled_items_referring_to_this_name,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_installation_list_function = 
	    STATIC_SYMBOL("RECLAIM-INSTALLATION-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_installation_list_function,
	    STATIC_FUNCTION(reclaim_installation_list_function,NIL,FALSE,1,1));
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qcompiled_items_referring_to_this_name,
	    Qreclaim_installation_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Compiled_items_referring_to_this_name_kbprop = 
	    Qcompiled_items_referring_to_this_name;
    Qundefined_classes = STATIC_SYMBOL("UNDEFINED-CLASSES",AB_package);
    Qanalyze_for_consistency = STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY",
	    AB_package);
    Qadd_as_item_referring_to_name_qm = 
	    STATIC_SYMBOL("ADD-AS-ITEM-REFERRING-TO-NAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qadd_as_item_referring_to_name_qm,
	    Add_as_item_referring_to_name_qm);
    Qdelete_as_item_referring_to_name_qm = 
	    STATIC_SYMBOL("DELETE-AS-ITEM-REFERRING-TO-NAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdelete_as_item_referring_to_name_qm,
	    Delete_as_item_referring_to_name_qm);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qblock,
	    Qadd_as_item_referring_to_name_qm,
	    Qdelete_as_item_referring_to_name_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qanalyze_for_consistency,list_constant_10,
	    Qgeneric_method_lambda_list);
    string_constant_90 = STATIC_STRING("ANALYZE-FOR-CONSISTENCY-IN-PROGRESS");
    if (Analyze_for_consistency_in_progress == UNBOUND)
	Analyze_for_consistency_in_progress = make_recursive_lock(2,Kname,
		string_constant_90);
    Qanalyze_for_consistency_in_progress = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-IN-PROGRESS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qanalyze_for_consistency_in_progress,
	    Analyze_for_consistency_in_progress);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qanalyze_for_consistency_in_progress,
	    Qinstall,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qanalyze_for_consistency_in_progress,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (List_of_types_to_be_analyzed == UNBOUND)
	List_of_types_to_be_analyzed = Nil;
    Qstack_compiler_frame_note_type_p = 
	    STATIC_SYMBOL("STACK-COMPILER-FRAME-NOTE-TYPE-P",AB_package);
    Stack_compiler_frame_note_type_p_prop = Qstack_compiler_frame_note_type_p;
    Qcompiler_errors = STATIC_SYMBOL("COMPILER-ERRORS",AB_package);
    Qcompiler_warnings = STATIC_SYMBOL("COMPILER-WARNINGS",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qcompiler_errors,
	    Qcompiler_warnings);
    List_of_stack_compiler_frame_note_types = list_constant_11;
    note = Nil;
    ab_loop_list_ = List_of_stack_compiler_frame_note_types;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    note = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(note,T,Qstack_compiler_frame_note_type_p);
    goto next_loop;
  end_loop:;
    Qconsistency_analysis_frame_note_type_p = 
	    STATIC_SYMBOL("CONSISTENCY-ANALYSIS-FRAME-NOTE-TYPE-P",AB_package);
    Consistency_analysis_frame_note_type_p_prop = 
	    Qconsistency_analysis_frame_note_type_p;
    Qsuperseded_attributes = STATIC_SYMBOL("SUPERSEDED-ATTRIBUTES",AB_package);
    Qnon_existent_instances = STATIC_SYMBOL("NON-EXISTENT-INSTANCES",
	    AB_package);
    Qundefined_attributes = STATIC_SYMBOL("UNDEFINED-ATTRIBUTES",AB_package);
    Qundefined_attributes_of_classes = 
	    STATIC_SYMBOL("UNDEFINED-ATTRIBUTES-OF-CLASSES",AB_package);
    Qundefined_methods_of_classes = 
	    STATIC_SYMBOL("UNDEFINED-METHODS-OF-CLASSES",AB_package);
    Qnon_existent_instances_of_class = 
	    STATIC_SYMBOL("NON-EXISTENT-INSTANCES-OF-CLASS",AB_package);
    Qnon_existent_instances_of_type = 
	    STATIC_SYMBOL("NON-EXISTENT-INSTANCES-OF-TYPE",AB_package);
    Qarg_count_mismatch = STATIC_SYMBOL("ARG-COUNT-MISMATCH",AB_package);
    Qreturn_count_mismatch = STATIC_SYMBOL("RETURN-COUNT-MISMATCH",AB_package);
    Qitem_not_ok = STATIC_SYMBOL("ITEM-NOT-OK",AB_package);
    Qarg_type_mismatch = STATIC_SYMBOL("ARG-TYPE-MISMATCH",AB_package);
    Qreturn_type_mismatch = STATIC_SYMBOL("RETURN-TYPE-MISMATCH",AB_package);
    Qnon_existent_procedure_method = 
	    STATIC_SYMBOL("NON-EXISTENT-PROCEDURE-METHOD",AB_package);
    Qspecific_method_argument_conflict = 
	    STATIC_SYMBOL("SPECIFIC-METHOD-ARGUMENT-CONFLICT",AB_package);
    Qno_arg_for_method_call = STATIC_SYMBOL("NO-ARG-FOR-METHOD-CALL",
	    AB_package);
    Qno_item_arg_for_method_call = 
	    STATIC_SYMBOL("NO-ITEM-ARG-FOR-METHOD-CALL",AB_package);
    Qno_method_for_arg_count = STATIC_SYMBOL("NO-METHOD-FOR-ARG-COUNT",
	    AB_package);
    Qno_method_for_class = STATIC_SYMBOL("NO-METHOD-FOR-CLASS",AB_package);
    Qmethod_for_class_not_okay = STATIC_SYMBOL("METHOD-FOR-CLASS-NOT-OKAY",
	    AB_package);
    Qitem_no_longer_dependent = STATIC_SYMBOL("ITEM-NO-LONGER-DEPENDENT",
	    AB_package);
    Qitem_depends_on_modified_stable_item = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-MODIFIED-STABLE-ITEM",AB_package);
    Qincompatible_validity_interval_and_data_server = 
	    STATIC_SYMBOL("INCOMPATIBLE-VALIDITY-INTERVAL-AND-DATA-SERVER",
	    AB_package);
    Qitem_depends_on_unstable_heirarchy = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-UNSTABLE-HEIRARCHY",AB_package);
    Qitem_depends_on_invalid_inlining = 
	    STATIC_SYMBOL("ITEM-DEPENDS-ON-INVALID-INLINING",AB_package);
    Qitem_inlineable_but_has_no_parse = 
	    STATIC_SYMBOL("ITEM-INLINEABLE-BUT-HAS-NO-PARSE",AB_package);
    Qnonexistent_classes_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-CLASSES-FOR-EXPORT",AB_package);
    Qnonexistent_static_methods_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-STATIC-METHODS-FOR-EXPORT",AB_package);
    Qduplicate_class_export = STATIC_SYMBOL("DUPLICATE-CLASS-EXPORT",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)29L,Qsuperseded_attributes,
	    Qnon_existent_instances,Qundefined_classes,
	    Qundefined_attributes,Qundefined_attributes_of_classes,
	    Qundefined_methods_of_classes,Qnon_existent_instances_of_class,
	    Qnon_existent_instances_of_type,Qarg_count_mismatch,
	    Qreturn_count_mismatch,Qitem_not_ok,Qarg_type_mismatch,
	    Qreturn_type_mismatch,Qnon_existent_procedure_method,
	    Qspecific_method_argument_conflict,Qno_arg_for_method_call,
	    Qno_item_arg_for_method_call,Qno_method_for_arg_count,
	    Qno_method_for_class,Qmethod_for_class_not_okay,
	    Qitem_no_longer_dependent,
	    Qitem_depends_on_modified_stable_item,
	    Qincompatible_validity_interval_and_data_server,
	    Qitem_depends_on_unstable_heirarchy,
	    Qitem_depends_on_invalid_inlining,
	    Qitem_inlineable_but_has_no_parse,
	    Qnonexistent_classes_for_export,
	    Qnonexistent_static_methods_for_export,Qduplicate_class_export);
    List_of_consistency_analysis_frame_note_types = list_constant_12;
    note = Nil;
    ab_loop_list_ = List_of_consistency_analysis_frame_note_types;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    note = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(note,T,Qconsistency_analysis_frame_note_type_p);
    goto next_loop_1;
  end_loop_1:;
    if (Post_analyzer_warning_note_qm == UNBOUND)
	Post_analyzer_warning_note_qm = T;
    Qframe_notes_for_component_particulars = 
	    STATIC_SYMBOL("FRAME-NOTES-FOR-COMPONENT-PARTICULARS",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qcompiler_and_analyzer = STATIC_SYMBOL("COMPILER-AND-ANALYZER",AB_package);
    string_constant_7 = 
	    STATIC_STRING("There were problems compiling the following-items, which have inconsistencies: ");
    Qanalyzer = STATIC_SYMBOL("ANALYZER",AB_package);
    string_constant_8 = 
	    STATIC_STRING("Inconsistencies were detected in the following items: ");
    Qcompiler = STATIC_SYMBOL("COMPILER",AB_package);
    string_constant_9 = 
	    STATIC_STRING("There were problems compiling the following items: ");
    Qstring_lt_w = STATIC_SYMBOL("STRING<W",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_lt_w,STATIC_FUNCTION(string_lt_w,NIL,FALSE,
	    2,2));
    Qget_or_make_up_designation_for_block = 
	    STATIC_SYMBOL("GET-OR-MAKE-UP-DESIGNATION-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qget_or_make_up_designation_for_block,
	    STATIC_FUNCTION(get_or_make_up_designation_for_block,NIL,FALSE,
	    1,1));
    string_constant_10 = STATIC_STRING("~NF");
    string_constant_11 = STATIC_STRING("; see their notes for details.");
    string_constant_12 = 
	    STATIC_STRING("There were problems compiling ~NF, and it has inconsistencies");
    string_constant_13 = STATIC_STRING("Inconsistencies were detected in ~NF");
    string_constant_14 = STATIC_STRING("There were problems compiling ~NF");
    string_constant_15 = STATIC_STRING(": ");
    string_constant_16 = STATIC_STRING("; see its notes for details.");
    string_constant_17 = STATIC_STRING("the item ");
    string_constant_18 = STATIC_STRING("the items ");
    string_constant_19 = STATIC_STRING(" does not exist");
    string_constant_20 = STATIC_STRING(" do not exist");
    write_non_existent_instances_note_1 = 
	    STATIC_FUNCTION(write_non_existent_instances_note,NIL,FALSE,2,2);
    mutate_global_property(Qnon_existent_instances,
	    write_non_existent_instances_note_1,Qframe_note_writer_1);
    string_constant_21 = STATIC_STRING("the class ");
    string_constant_22 = STATIC_STRING("the classes ");
    string_constant_23 = STATIC_STRING(" is not defined");
    string_constant_24 = STATIC_STRING(" are not defined");
    write_undefined_classes_note_1 = 
	    STATIC_FUNCTION(write_undefined_classes_note,NIL,FALSE,2,2);
    mutate_global_property(Qundefined_classes,
	    write_undefined_classes_note_1,Qframe_note_writer_1);
    string_constant_91 = 
	    STATIC_STRING(" has been superseded.  G2 will automatically process the statement containing its reference, but the ");
    string_constant_92 = 
	    STATIC_STRING("result should be examined and the statement should be brought up to date before further kb development.  ");
    string_constant_93 = STATIC_STRING("Please see the release notes.");
    Frame_note_for_superseded_attributes_1 = concatenate(4,Qstring,
	    string_constant_91,string_constant_92,string_constant_93);
    string_constant_25 = STATIC_STRING("the attribute ");
    string_constant_26 = STATIC_STRING("the attributes ");
    write_undefined_attributes_note_1 = 
	    STATIC_FUNCTION(write_undefined_attributes_note,NIL,FALSE,2,2);
    mutate_global_property(Qundefined_attributes,
	    write_undefined_attributes_note_1,Qframe_note_writer_1);
    array_constant_11 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    write_undefined_attributes_of_classes_note_1 = 
	    STATIC_FUNCTION(write_undefined_attributes_of_classes_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qundefined_attributes_of_classes,
	    write_undefined_attributes_of_classes_note_1,Qframe_note_writer_1);
    string_constant_27 = STATIC_STRING("the method ");
    string_constant_28 = STATIC_STRING("the methods");
    write_undefined_methods_of_classes_note_1 = 
	    STATIC_FUNCTION(write_undefined_methods_of_classes_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qundefined_methods_of_classes,
	    write_undefined_methods_of_classes_note_1,Qframe_note_writer_1);
    string_constant_29 = STATIC_STRING("the name ");
    string_constant_30 = STATIC_STRING("the names ");
    string_constant_31 = 
	    STATIC_STRING(" does not exist as an instance of the class ");
    string_constant_32 = 
	    STATIC_STRING(" do not exist as instances of the class ");
    write_non_existent_instances_of_class_note_1 = 
	    STATIC_FUNCTION(write_non_existent_instances_of_class_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnon_existent_instances_of_class,
	    write_non_existent_instances_of_class_note_1,Qframe_note_writer_1);
    string_constant_33 = 
	    STATIC_STRING(" does not exist as an instance of the type ");
    string_constant_34 = 
	    STATIC_STRING(" do not exist as instances of the type ");
    write_non_existent_instances_of_type_note_1 = 
	    STATIC_FUNCTION(write_non_existent_instances_of_type_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnon_existent_instances_of_type,
	    write_non_existent_instances_of_type_note_1,Qframe_note_writer_1);
    array_constant_13 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)33L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)37L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)39L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)42L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)45L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)46L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)47L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)50L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)51L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)54L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)55L,(SI_Long)57344L);
    write_non_existent_procedure_method_note_1 = 
	    STATIC_FUNCTION(write_non_existent_procedure_method_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnon_existent_procedure_method,
	    write_non_existent_procedure_method_note_1,Qframe_note_writer_1);
    string_constant_35 = 
	    STATIC_STRING("there is more than one method defined for the ~\n          class ~a and that has ~a ~a");
    string_constant_36 = STATIC_STRING("arguments");
    string_constant_37 = STATIC_STRING("argument");
    string_constant_38 = 
	    STATIC_STRING("there is more than one method defined with the ~\n           same class for the first argument and with the same number of ~\n           arguments");
    write_specific_method_argument_conflict_note_1 = 
	    STATIC_FUNCTION(write_specific_method_argument_conflict_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qspecific_method_argument_conflict,
	    write_specific_method_argument_conflict_note_1,
	    Qframe_note_writer_1);
    string_constant_39 = STATIC_STRING("the methods ");
    string_constant_40 = STATIC_STRING(" is being called with no arguments");
    string_constant_41 = STATIC_STRING(" are being called with no arguments");
    write_no_arg_for_method_call_note_1 = 
	    STATIC_FUNCTION(write_no_arg_for_method_call_note,NIL,FALSE,2,2);
    mutate_global_property(Qno_arg_for_method_call,
	    write_no_arg_for_method_call_note_1,Qframe_note_writer_1);
    string_constant_42 = 
	    STATIC_STRING("the method ~NN requires a first argument of class item, but ~\n       is being given ");
    string_constant_43 = STATIC_STRING("a first argument of type ~NT");
    array_constant_14 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    string_constant_44 = STATIC_STRING("and");
    string_constant_45 = STATIC_STRING("~NT");
    array_constant_15 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    write_no_item_arg_for_method_call_note_1 = 
	    STATIC_FUNCTION(write_no_item_arg_for_method_call_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qno_item_arg_for_method_call,
	    write_no_item_arg_for_method_call_note_1,Qframe_note_writer_1);
    string_constant_46 = STATIC_STRING("the method~a ");
    string_constant_47 = STATIC_STRING("");
    string_constant_48 = STATIC_STRING("s");
    string_constant_49 = STATIC_STRING(", with ~a argument~a,");
    string_constant_50 = STATIC_STRING(" ~a not defined for the class ~NN");
    string_constant_51 = STATIC_STRING("is");
    string_constant_52 = STATIC_STRING("are");
    write_no_method_for_arg_count_note_1 = 
	    STATIC_FUNCTION(write_no_method_for_arg_count_note,NIL,FALSE,2,2);
    mutate_global_property(Qno_method_for_arg_count,
	    write_no_method_for_arg_count_note_1,Qframe_note_writer_1);
    string_constant_53 = STATIC_STRING(" is not defined for the class ");
    string_constant_54 = STATIC_STRING(" are not defined for the class ");
    write_no_method_for_class_note_1 = 
	    STATIC_FUNCTION(write_no_method_for_class_note,NIL,FALSE,2,2);
    mutate_global_property(Qno_method_for_class,
	    write_no_method_for_class_note_1,Qframe_note_writer_1);
    string_constant_55 = STATIC_STRING(" defined for the class ");
    string_constant_56 = STATIC_STRING("~a is not OK");
    string_constant_57 = STATIC_STRING("~a are not OK");
    write_method_for_class_not_okay_note_1 = 
	    STATIC_FUNCTION(write_method_for_class_not_okay_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qmethod_for_class_not_okay,
	    write_method_for_class_not_okay_note_1,Qframe_note_writer_1);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    array_constant_16 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)21L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)31L,(SI_Long)57344L);
    write_arg_count_mismatch_note_1 = 
	    STATIC_FUNCTION(write_arg_count_mismatch_note,NIL,FALSE,2,2);
    mutate_global_property(Qarg_count_mismatch,
	    write_arg_count_mismatch_note_1,Qframe_note_writer_1);
    write_return_count_mismatch_note_1 = 
	    STATIC_FUNCTION(write_return_count_mismatch_note,NIL,FALSE,2,2);
    mutate_global_property(Qreturn_count_mismatch,
	    write_return_count_mismatch_note_1,Qframe_note_writer_1);
    string_constant_58 = 
	    STATIC_STRING("~a requires ~a argument~a but was given ");
    string_constant_59 = 
	    STATIC_STRING("~a returns ~a value~a but was expected to return ");
    string_constant_60 = STATIC_STRING(" argument~a");
    string_constant_61 = STATIC_STRING(" value~a");
    string_constant_62 = STATIC_STRING("the class~a ");
    string_constant_63 = STATIC_STRING("es");
    string_constant_64 = STATIC_STRING("~a");
    string_constant_65 = STATIC_STRING("~a, with ~a argument~a, ");
    string_constant_66 = 
	    STATIC_STRING(" ~NN depends upon a stable heirarchy which is no longer stable ");
    write_item_depends_on_unstable_heirarchy_note_1 = 
	    STATIC_FUNCTION(write_item_depends_on_unstable_heirarchy_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qitem_depends_on_unstable_heirarchy,
	    write_item_depends_on_unstable_heirarchy_note_1,
	    Qframe_note_writer_1);
    string_constant_67 = STATIC_STRING("the procedure~a ");
    string_constant_68 = STATIC_STRING("the methods and procedures ");
    Kcross_module_violation = STATIC_SYMBOL("CROSS-MODULE-VIOLATION",Pkeyword);
    string_constant_69 = 
	    STATIC_STRING(" can\'t be inlined because of a cross-module violation ");
    string_constant_70 = 
	    STATIC_STRING(" is no longer the same as what was inlined ");
    write_item_depends_on_invalid_inlining_note_1 = 
	    STATIC_FUNCTION(write_item_depends_on_invalid_inlining_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qitem_depends_on_invalid_inlining,
	    write_item_depends_on_invalid_inlining_note_1,
	    Qframe_note_writer_1);
    array_constant_17 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)42L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)48L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)50L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)51L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)52L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)53L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)55L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)57L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)58L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)59L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)60L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)62L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)63L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)64L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)65L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)66L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)67L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)68L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)78L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)79L,(SI_Long)57344L);
    write_item_inlineable_but_has_no_parse_note_1 = 
	    STATIC_FUNCTION(write_item_inlineable_but_has_no_parse_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qitem_inlineable_but_has_no_parse,
	    write_item_inlineable_but_has_no_parse_note_1,
	    Qframe_note_writer_1);
    string_constant_71 = STATIC_STRING(" is not OK");
    string_constant_72 = STATIC_STRING(" are not OK");
    write_item_not_ok_note_1 = STATIC_FUNCTION(write_item_not_ok_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_not_ok,write_item_not_ok_note_1,
	    Qframe_note_writer_1);
    write_arg_type_mismatch_note_1 = 
	    STATIC_FUNCTION(write_arg_type_mismatch_note,NIL,FALSE,2,2);
    mutate_global_property(Qarg_type_mismatch,
	    write_arg_type_mismatch_note_1,Qframe_note_writer_1);
    write_return_type_mismatch_note_1 = 
	    STATIC_FUNCTION(write_return_type_mismatch_note,NIL,FALSE,2,2);
    mutate_global_property(Qreturn_type_mismatch,
	    write_return_type_mismatch_note_1,Qframe_note_writer_1);
    string_constant_73 = 
	    STATIC_STRING("argument ~a of ~a requires values of type ~NT but was given values ~\n           of type~a ");
    string_constant_74 = 
	    STATIC_STRING("return value ~a of ~a provides values of type ~NT but was expected ~\n           to provide values of type~a ");
    array_constant_18 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)26L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)27L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)33L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)35L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)37L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)42L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)47L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)50L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)51L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)53L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)54L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)55L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)56L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)57L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)58L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)59L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)60L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)61L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)62L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)63L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)64L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)65L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)78L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)79L,(SI_Long)57344L);
    write_item_no_longer_dependent_note_1 = 
	    STATIC_FUNCTION(write_item_no_longer_dependent_note,NIL,FALSE,2,2);
    mutate_global_property(Qitem_no_longer_dependent,
	    write_item_no_longer_dependent_note_1,Qframe_note_writer_1);
    string_constant_75 = 
	    STATIC_STRING("this item needs to be recompiled because it depends on the stable item ");
    string_constant_76 = 
	    STATIC_STRING("this item needs to be recompiled because it depends on the stable items ");
    string_constant_77 = STATIC_STRING(" which has been modified");
    string_constant_78 = STATIC_STRING(" which have been modified");
    write_item_depends_on_modified_stable_item_note_1 = 
	    STATIC_FUNCTION(write_item_depends_on_modified_stable_item_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qitem_depends_on_modified_stable_item,
	    write_item_depends_on_modified_stable_item_note_1,
	    Qframe_note_writer_1);
    temp = adjoin(2,Qblock,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qcheck_undefined_instances_of_class = 
	    STATIC_SYMBOL("CHECK-UNDEFINED-INSTANCES-OF-CLASS",AB_package);
    Qanalyze_for_consistency_for_block = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_block,
	    STATIC_FUNCTION(analyze_for_consistency_for_block,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_block);
    set_get(Qblock,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    temp = adjoin(2,Qclass_definition,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qstubs_for_class = STATIC_SYMBOL("STUBS-FOR-CLASS",AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qicon_background_images = STATIC_SYMBOL("ICON-BACKGROUND-IMAGES",
	    AB_package);
    Qinitial_value_class_incompatible_with_type = 
	    STATIC_SYMBOL("INITIAL-VALUE-CLASS-INCOMPATIBLE-WITH-TYPE",
	    AB_package);
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    Qg2_variable = STATIC_SYMBOL("G2-VARIABLE",AB_package);
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    Qoverride_value_is_not_compatible = 
	    STATIC_SYMBOL("OVERRIDE-VALUE-IS-NOT-COMPATIBLE",AB_package);
    Qanalyze_for_consistency_for_class_definition = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-CLASS-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_class_definition,
	    STATIC_FUNCTION(analyze_for_consistency_for_class_definition,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_class_definition);
    set_get(Qclass_definition,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qclass_definition,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qdrawing_parameters = STATIC_SYMBOL("DRAWING-PARAMETERS",AB_package);
    temp = adjoin(2,Qdrawing_parameters,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_drawing_parameters = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-DRAWING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_drawing_parameters,
	    STATIC_FUNCTION(analyze_for_consistency_for_drawing_parameters,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qdrawing_parameters,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    temp = adjoin(2,Qkb_workspace,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qframe_style = STATIC_SYMBOL("FRAME-STYLE",AB_package);
    Qframe_style_definition = STATIC_SYMBOL("FRAME-STYLE-DEFINITION",
	    AB_package);
    Qanalyze_for_consistency_for_kb_workspace = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_kb_workspace,
	    STATIC_FUNCTION(analyze_for_consistency_for_kb_workspace,NIL,
	    FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_kb_workspace);
    set_get(Qkb_workspace,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    temp = adjoin(2,Qgeneric_formula,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_generic_formula = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-GENERIC-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_generic_formula,
	    STATIC_FUNCTION(analyze_for_consistency_for_generic_formula,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_generic_formula);
    set_get(Qgeneric_formula,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_formula,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    string_constant_79 = 
	    STATIC_STRING("a validity interval of \"supplied\" (the default value) is only valid ~\n     when the data server is \"inference engine\"");
    write_incompatible_validity_interval_and_data_server_note_1 = 
	    STATIC_FUNCTION(write_incompatible_validity_interval_and_data_server_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qincompatible_validity_interval_and_data_server,
	    write_incompatible_validity_interval_and_data_server_note_1,
	    Qframe_note_writer_1);
    temp = adjoin(2,Qvariable,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_variable = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_variable,
	    STATIC_FUNCTION(analyze_for_consistency_for_variable,NIL,FALSE,
	    3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_variable);
    set_get(Qvariable,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qvariable,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    temp = adjoin(2,Qgeneric_simulation_formula,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_generic_simulation_formula = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_generic_simulation_formula,
	    STATIC_FUNCTION(analyze_for_consistency_for_generic_simulation_formula,
	    NIL,FALSE,3,3));
    temp = 
	    SYMBOL_FUNCTION(Qanalyze_for_consistency_for_generic_simulation_formula);
    set_get(Qgeneric_simulation_formula,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_simulation_formula,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qinitialize_after_reading_for_generic_simulation_formula = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_generic_simulation_formula,
	    STATIC_FUNCTION(initialize_after_reading_for_generic_simulation_formula,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_generic_simulation_formula);
    set_get(Qgeneric_simulation_formula,Qinitialize_after_reading,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp = CONS(Qgeneric_simulation_formula,temp_1);
    mutate_global_property(Qinitialize_after_reading,temp,
	    Qclasses_which_define);
    Qsimulation_initial_value = STATIC_SYMBOL("SIMULATION-INITIAL-VALUE",
	    AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qsimulation_initial_value,
	    Qcurrent_computation_frame);
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    temp = adjoin(2,Qfunction_definition,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_function_definition = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-FUNCTION-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_function_definition,
	    STATIC_FUNCTION(analyze_for_consistency_for_function_definition,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_function_definition);
    set_get(Qfunction_definition,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qfunction_definition,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    temp = adjoin(2,Qreadout_table,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_readout_table = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_readout_table,
	    STATIC_FUNCTION(analyze_for_consistency_for_readout_table,NIL,
	    FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_readout_table);
    set_get(Qreadout_table,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qreadout_table,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    temp = adjoin(2,Qdial,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_dial = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_dial,
	    STATIC_FUNCTION(analyze_for_consistency_for_dial,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_dial);
    set_get(Qdial,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qdial,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    temp = adjoin(2,Qmeter,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_meter = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_meter,
	    STATIC_FUNCTION(analyze_for_consistency_for_meter,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_meter);
    set_get(Qmeter,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qmeter,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    temp = adjoin(2,Qtrend_chart,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qslot_component = STATIC_SYMBOL("SLOT-COMPONENT",AB_package);
    Qtrend_chart_point_formats = STATIC_SYMBOL("TREND-CHART-POINT-FORMATS",
	    AB_package);
    Qpoint_style = STATIC_SYMBOL("POINT-STYLE",AB_package);
    Qcustom = STATIC_SYMBOL("CUSTOM",AB_package);
    Qicon_class = STATIC_SYMBOL("ICON-CLASS",AB_package);
    Qanalyze_for_consistency_for_trend_chart = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-TREND-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_trend_chart,
	    STATIC_FUNCTION(analyze_for_consistency_for_trend_chart,NIL,
	    FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_trend_chart);
    set_get(Qtrend_chart,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qtrend_chart,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    temp = adjoin(2,Qgraph,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qgraph_expression = STATIC_SYMBOL("GRAPH-EXPRESSION",AB_package);
    Qanalyze_for_consistency_for_graph = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_graph,
	    STATIC_FUNCTION(analyze_for_consistency_for_graph,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_graph);
    set_get(Qgraph,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    temp = adjoin(2,Qchart,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qdata_series = STATIC_SYMBOL("DATA-SERIES",AB_package);
    Qdata_series_info_1 = STATIC_SYMBOL("DATA-SERIES-INFO-1",AB_package);
    Qdata_series_info_2 = STATIC_SYMBOL("DATA-SERIES-INFO-2",AB_package);
    Qdata_series_failed_to_compile = 
	    STATIC_SYMBOL("DATA-SERIES-FAILED-TO-COMPILE",AB_package);
    Qanalyze_for_consistency_for_chart = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_chart,
	    STATIC_FUNCTION(analyze_for_consistency_for_chart,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_chart);
    set_get(Qchart,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qnew_table = STATIC_SYMBOL("NEW-TABLE",AB_package);
    temp = adjoin(2,Qnew_table,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_new_table = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_new_table,
	    STATIC_FUNCTION(analyze_for_consistency_for_new_table,NIL,
	    FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_new_table);
    set_get(Qnew_table,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qnew_table,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qinter_g2_data_request_holder = 
	    STATIC_SYMBOL("INTER-G2-DATA-REQUEST-HOLDER",AB_package);
    temp = adjoin(2,Qinter_g2_data_request_holder,
	    List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_inter_g2_data_request_holder = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-INTER-G2-DATA-REQUEST-HOLDER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_inter_g2_data_request_holder,
	    STATIC_FUNCTION(analyze_for_consistency_for_inter_g2_data_request_holder,
	    NIL,FALSE,3,3));
    temp = 
	    SYMBOL_FUNCTION(Qanalyze_for_consistency_for_inter_g2_data_request_holder);
    set_get(Qinter_g2_data_request_holder,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qinter_g2_data_request_holder,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qkb_search_state = STATIC_SYMBOL("KB-SEARCH-STATE",AB_package);
    temp = adjoin(2,Qkb_search_state,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_kb_search_state = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-KB-SEARCH-STATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_kb_search_state,
	    STATIC_FUNCTION(analyze_for_consistency_for_kb_search_state,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_kb_search_state);
    set_get(Qkb_search_state,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qkb_search_state,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    temp = adjoin(2,Quser_menu_choice,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_user_menu_choice = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_user_menu_choice,
	    STATIC_FUNCTION(analyze_for_consistency_for_user_menu_choice,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_user_menu_choice);
    set_get(Quser_menu_choice,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Quser_menu_choice,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    temp = adjoin(2,Qprocedure,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_procedure = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_procedure,
	    STATIC_FUNCTION(analyze_for_consistency_for_procedure,NIL,
	    FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_procedure);
    set_get(Qprocedure,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qprocedure,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qmd5_identifier_qm = STATIC_SYMBOL("MD5-IDENTIFIER\?",AB_package);
    Qparse_results_qm = STATIC_SYMBOL("PARSE-RESULTS\?",AB_package);
    temp = adjoin(2,Qrule,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_rule = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_rule,
	    STATIC_FUNCTION(analyze_for_consistency_for_rule,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_rule);
    set_get(Qrule,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qrule,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    temp = adjoin(2,Qsimulation_subtable,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qanalyze_for_consistency_for_simulation_subtable = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-SIMULATION-SUBTABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_simulation_subtable,
	    STATIC_FUNCTION(analyze_for_consistency_for_simulation_subtable,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_simulation_subtable);
    set_get(Qsimulation_subtable,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qsimulation_subtable,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qnon_action_button = STATIC_SYMBOL("NON-ACTION-BUTTON",AB_package);
    temp = adjoin(2,Qnon_action_button,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qtype_in_box_variable_or_parameter = 
	    STATIC_SYMBOL("TYPE-IN-BOX-VARIABLE-OR-PARAMETER",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qanalyze_for_consistency_for_non_action_button = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-NON-ACTION-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_non_action_button,
	    STATIC_FUNCTION(analyze_for_consistency_for_non_action_button,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_non_action_button);
    set_get(Qnon_action_button,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qnon_action_button,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    temp = adjoin(2,Qg2_array,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qanalyze_for_consistency_for_g2_array = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-G2-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_g2_array,
	    STATIC_FUNCTION(analyze_for_consistency_for_g2_array,NIL,FALSE,
	    3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_g2_array);
    set_get(Qg2_array,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qg2_array,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qlanguage_parameters = STATIC_SYMBOL("LANGUAGE-PARAMETERS",AB_package);
    temp = adjoin(2,Qlanguage_parameters,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    Qanalyze_for_consistency_for_language_parameters = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-LANGUAGE-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_language_parameters,
	    STATIC_FUNCTION(analyze_for_consistency_for_language_parameters,
	    NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_language_parameters);
    set_get(Qlanguage_parameters,Qanalyze_for_consistency,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qlanguage_parameters,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    Qgiver_of_value = STATIC_SYMBOL("GIVER-OF-VALUE",AB_package);
    Qsimulation_variable_cache = STATIC_SYMBOL("SIMULATION-VARIABLE-CACHE",
	    AB_package);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qrule_let = STATIC_SYMBOL("RULE-LET",AB_package);
    Qlet_action = STATIC_SYMBOL("LET-ACTION",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_let,Qrule_let,Qlet_action);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qitem_color = STATIC_SYMBOL("ITEM-COLOR",AB_package);
    Qsubworkspace = STATIC_SYMBOL("SUBWORKSPACE",AB_package);
    Qsystem_attribute = STATIC_SYMBOL("SYSTEM-ATTRIBUTE",AB_package);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)5L,Qrole_server,Qitem_color,
	    Qsubworkspace,Qsystem_attribute,Qnth_element);
    Qlist_iterator = STATIC_SYMBOL("LIST-ITERATOR",AB_package);
    Qfirst_of_list = STATIC_SYMBOL("FIRST-OF-LIST",AB_package);
    Qsecond_of_list = STATIC_SYMBOL("SECOND-OF-LIST",AB_package);
    Qlast_of_list = STATIC_SYMBOL("LAST-OF-LIST",AB_package);
    Qnext_to_last_of_list = STATIC_SYMBOL("NEXT-TO-LAST-OF-LIST",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)5L,Qlist_iterator,
	    Qfirst_of_list,Qsecond_of_list,Qlast_of_list,
	    Qnext_to_last_of_list);
    Qchange_icon_color = STATIC_SYMBOL("CHANGE-ICON-COLOR",AB_package);
    Qchange_color_pattern = STATIC_SYMBOL("CHANGE-COLOR-PATTERN",AB_package);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    Qcreate_connection_spec = STATIC_SYMBOL("CREATE-CONNECTION-SPEC",
	    AB_package);
    Qexpression_list = STATIC_SYMBOL("EXPRESSION-LIST",AB_package);
    Qdesignation_list = STATIC_SYMBOL("DESIGNATION-LIST",AB_package);
    Qcolor_changes = STATIC_SYMBOL("COLOR-CHANGES",AB_package);
    Qmessage_designation = STATIC_SYMBOL("MESSAGE-DESIGNATION",AB_package);
    Qoperator = STATIC_SYMBOL("OPERATOR",AB_package);
    Qme = STATIC_SYMBOL("ME",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qoperator,Qme);
    Qscope = STATIC_SYMBOL("SCOPE",AB_package);
    Qshow_or_hide_argument_list = 
	    STATIC_SYMBOL("SHOW-OR-HIDE-ARGUMENT-LIST",AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_undefined_instances_of_class,
	    STATIC_FUNCTION(check_undefined_instances_of_class,NIL,FALSE,2,2));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qab_class,Qmessage_board);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    Qcached_name_cons_marker = STATIC_SYMBOL("CACHED-NAME-CONS-MARKER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_name_cons_marker,
	    Cached_name_cons_marker);
    QCACHED_ITEM_NAME = STATIC_SYMBOL("cached-item-name",AB_package);
    SET_SYMBOL_VALUE(Qcached_name_cons_marker,QCACHED_ITEM_NAME);
    list_constant_6 = STATIC_CONS(Qmessage_board,Qnil);
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    Qstable_procedure_call = STATIC_SYMBOL("STABLE-PROCEDURE-CALL",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qarg_count = STATIC_SYMBOL("ARG-COUNT",AB_package);
    Qremote_procedure_call = STATIC_SYMBOL("REMOTE-PROCEDURE-CALL",AB_package);
    Qstable_remote_procedure_call = 
	    STATIC_SYMBOL("STABLE-REMOTE-PROCEDURE-CALL",AB_package);
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Kall_remaining = STATIC_SYMBOL("ALL-REMAINING",Pkeyword);
    Kkind = STATIC_SYMBOL("KIND",Pkeyword);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
}
