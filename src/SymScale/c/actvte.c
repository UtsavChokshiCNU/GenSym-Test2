/* actvte.c
 * Input file:  activate.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "actvte.h"


static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-KB-FRAME */
Object note_ancestor_manually_enabled_for_kb_frame(kb_frame)
    Object kb_frame;
{
    Object gensymed_symbol, gensymed_symbol_1, class_description;
    Object ab_loop_list_, gensymed_symbol_2, x2;

    x_note_fn_call(181,0);
    gensymed_symbol = kb_frame;
    gensymed_symbol_1 = Nil;
    class_description = ISVREF(gensymed_symbol,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(gensymed_symbol_1,(SI_Long)8L)) {
	gensymed_symbol_2 = get_slot_description_value(gensymed_symbol,
		gensymed_symbol_1);
	if (SIMPLE_VECTOR_P(gensymed_symbol_2) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_2)) > 
		(SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	    gensymed_symbol_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_1 = Nil;
	if (gensymed_symbol_1 && ISVREF(gensymed_symbol_1,(SI_Long)16L)) {
	    gensymed_symbol_1 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)54L),(SI_Long)1L);
	    inline_funcall_1(gensymed_symbol_1,gensymed_symbol_2);
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qkb_workspace;       /* kb-workspace */

/* NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-KB-WORKSPACE */
Object note_ancestor_manually_enabled_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, gensymed_symbol_1;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(181,1);
    frame = kb_workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)54L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
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
    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
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
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subblock,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)54L),(SI_Long)1L);
    gensymed_symbol_1 = subblock;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qparent_frame;       /* parent-frame */

/* SUPERIOR-FRAME */
Object superior_frame(frame)
    Object frame;
{
    Object class_description, sub_class_bit_vector, gensymed_symbol_3, temp_1;
    Object connection_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(181,2);
    class_description = ISVREF(frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	temp_1 = gensymed_symbol_3;
	if (temp_1);
	else
	    temp_1 = get_lookup_slot_value_given_default(frame,
		    Qparent_frame,Nil);
	if (temp_1);
	else {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		temp_1 = ISVREF(frame,(SI_Long)18L);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
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
		if (temp) {
		    connection_qm = ISVREF(frame,(SI_Long)21L);
		    if (connection_qm) {
			gensymed_symbol_3 = 
				ACCESS_ONCE(ISVREF(ISVREF(connection_qm,
				(SI_Long)3L),(SI_Long)14L));
			gensymed_symbol_3 = gensymed_symbol_3 ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol_3,
				(SI_Long)5L)) : Nil;
			temp_1 = gensymed_symbol_3;
		    }
		    else
			temp_1 = Nil;
		}
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Simulation_subtable_class_description,
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
			temp_1 = ISVREF(frame,(SI_Long)22L);
		    else
			temp_1 = Qnil;
		}
	    }
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* ANCESTOR-P */
Object ancestor_p(frame1,frame2)
    Object frame1, frame2;
{
    Object frame_qm, temp;

    x_note_fn_call(181,3);
    frame_qm = superior_frame(frame2);
  next_loop:
    if ( !TRUEP(frame_qm)) {
	temp = Nil;
	goto end_1;
    }
    else if (EQ(frame_qm,frame1)) {
	temp = T;
	goto end_1;
    }
    frame_qm = superior_frame(frame_qm);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SUSPEND-ACTIVATION */
Object suspend_activation(item)
    Object item;
{
    Object in_suspend_resume_p, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(181,4);
    in_suspend_resume_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_suspend_resume_p,Qin_suspend_resume_p,in_suspend_resume_p,
	    0);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
      gensymed_symbol_1 = item;
      gensymed_symbol_2 = Nil;
      result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	      gensymed_symbol_2);
    POP_SPECIAL();
    return result;
}

/* RESUME-ACTIVATION */
Object resume_activation(item)
    Object item;
{
    Object in_suspend_resume_p, gensymed_symbol, gensymed_symbol_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(181,5);
    in_suspend_resume_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_suspend_resume_p,Qin_suspend_resume_p,in_suspend_resume_p,
	    0);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
      gensymed_symbol_1 = item;
      result = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Existence_classes_already_checked, Qexistence_classes_already_checked);

/* EXISTENCE-DEPENDS-ON-P */
Object existence_depends_on_p(possible_dependent_frame,frame)
    Object possible_dependent_frame, frame;
{
    Object result_1, last_1, next_qm, temp, temp_1, svref_new_value;

    x_note_fn_call(181,6);
    Existence_classes_already_checked = Nil;
    result_1 = existence_depends_on_p_1(possible_dependent_frame,frame);
    if (Existence_classes_already_checked) {
	last_1 = Existence_classes_already_checked;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    temp_1 = Existence_classes_already_checked;
	    M_CDR(temp) = temp_1;
	    temp = Available_eval_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = Existence_classes_already_checked;
	    SVREF(temp,temp_1) = svref_new_value;
	    temp = Available_eval_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    Existence_classes_already_checked = Nil;
    return VALUES_1(result_1);
}

/* EXISTENCE-DEPENDS-ON-P-1 */
Object existence_depends_on_p_1(possible_dependent_frame,frame)
    Object possible_dependent_frame, frame;
{
    Object temp, superior_qm;

    x_note_fn_call(181,7);
    temp = EQ(possible_dependent_frame,frame) ? T : Nil;
    if (temp);
    else {
	superior_qm = superior_frame(possible_dependent_frame);
	temp = superior_qm ? existence_depends_on_p_1(superior_qm,frame) : 
		Qnil;
    }
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(possible_dependent_frame,
		(SI_Long)4L)) & (SI_Long)131072L) ? 
		frame_class_existence_depends_on_p_1(possible_dependent_frame,
		frame) : Qnil;
    return VALUES_1(temp);
}

static Object Qclass_definition;   /* class-definition */

/* FRAME-CLASS-EXISTENCE-DEPENDS-ON-P-1 */
Object frame_class_existence_depends_on_p_1(possible_dependent_frame,frame)
    Object possible_dependent_frame, frame;
{
    Object class_1, class_description, ab_loop_list_;
    Object class_definition_frame_qm, temp;

    x_note_fn_call(181,8);
    class_1 = Nil;
    class_description = ISVREF(possible_dependent_frame,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(class_1,Existence_classes_already_checked))) {
	Existence_classes_already_checked = eval_cons_1(class_1,
		Existence_classes_already_checked);
	class_definition_frame_qm = 
		get_instance_with_name_if_any(Qclass_definition,class_1);
	if ( !TRUEP(class_definition_frame_qm)) {
	    temp = Nil;
	    goto end_1;
	}
	if (existence_depends_on_p_1(class_definition_frame_qm,frame)) {
	    temp = T;
	    goto end_1;
	}
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qkb_frame;           /* kb-frame */

static Object Qframe_flags;        /* frame-flags */

static Object Qmanually_disabled_qm;  /* manually-disabled? */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qis_disabled;        /* is-disabled */

/* MANUALLY-DISABLE-FOR-KB-FRAME */
Object manually_disable_for_kb_frame(kb_frame)
    Object kb_frame;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long index_1, ab_loop_bind_, svref_new_value;
    char gensymed_symbol_2;

    x_note_fn_call(181,9);
    frame = kb_frame;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)47L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_frame)) {
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
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_frame,Qframe_flags);
    svref_new_value = IFIX(ISVREF(kb_frame,(SI_Long)4L)) | (SI_Long)8192L;
    ISVREF(kb_frame,(SI_Long)4L) = FIX(svref_new_value);
    if (G2_has_v5_mode_windows_p && ISVREF(ISVREF(kb_frame,(SI_Long)1L),
	    (SI_Long)16L))
	send_ws_representations_item_virtual_attribute_change(kb_frame,
		get_property_value_function(3,
		get_symbol_properties_function(Qmanually_disabled_qm),
		Qvirtual_attribute,Nil),Nil);
    if ( !(System_is_running || System_has_paused)) {
	if (ISVREF(kb_frame,(SI_Long)9L))
	    update_representations_of_slot_value(2,kb_frame,
		    Qframe_status_and_notes);
    }
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(kb_frame,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
    gensymed_symbol_1 = kb_frame;
    gensymed_symbol_2 = (SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)5L)) 
	    & (SI_Long)256L);
    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2 ? 
	    T : Nil);
    return schedule_task_to_invoke_existential_rules(kb_frame,Qis_disabled);
}

static Object Qactivatable_subworkspace;  /* activatable-subworkspace */

static Object Qis_enabled;         /* is-enabled */

/* MANUALLY-ENABLE-FOR-KB-FRAME */
Object manually_enable_for_kb_frame(kb_frame)
    Object kb_frame;
{
    Object frame, sub_vector_qm, method_function_qm, superior_frame_1;
    Object sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long index_1, ab_loop_bind_, svref_new_value, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp, gensymed_symbol_5;

    x_note_fn_call(181,10);
    frame = kb_frame;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)48L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_frame)) {
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
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_frame,Qframe_flags);
    svref_new_value = IFIX(ISVREF(kb_frame,(SI_Long)4L)) &  ~(SI_Long)8192L;
    ISVREF(kb_frame,(SI_Long)4L) = FIX(svref_new_value);
    if (G2_has_v5_mode_windows_p && ISVREF(ISVREF(kb_frame,(SI_Long)1L),
	    (SI_Long)16L))
	send_ws_representations_item_virtual_attribute_change(kb_frame,
		get_property_value_function(3,
		get_symbol_properties_function(Qmanually_disabled_qm),
		Qvirtual_attribute,Nil),Nil);
    if ( !(System_is_running || System_has_paused)) {
	if (ISVREF(kb_frame,(SI_Long)9L))
	    update_representations_of_slot_value(2,kb_frame,
		    Qframe_status_and_notes);
    }
    superior_frame_1 = superior_frame(kb_frame);
    temp =  !TRUEP(superior_frame_1) ? System_is_running || 
	    System_has_paused : TRUEP(Qnil);
    if (temp);
    else if (superior_frame_1 && (SI_Long)0L != 
	    (IFIX(ISVREF(superior_frame_1,(SI_Long)5L)) & (SI_Long)1L)) {
	sub_class_bit_vector = ISVREF(ISVREF(kb_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	temp = (temp ? TRUEP(ISVREF(kb_frame,(SI_Long)18L)) : TRUEP(Nil)) ?
		  
		!TRUEP(get_property_value_in_object_configuration(superior_frame_1,
		Qactivatable_subworkspace,Nil)) : TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(kb_frame,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_4 = kb_frame;
	inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
	return schedule_task_to_invoke_existential_rules(kb_frame,Qis_enabled);
    }
    else {
	gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(kb_frame,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_4 = kb_frame;
	gensymed_symbol_5 = (SI_Long)0L != (IFIX(ISVREF(kb_frame,
		(SI_Long)5L)) & (SI_Long)256L);
	inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5 ? T : Nil);
	gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(kb_frame,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)54L),(SI_Long)1L);
	gensymed_symbol_4 = kb_frame;
	return inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Items_needing_initialization, Qitems_needing_initialization);

/* ACTIVATE-IN-NEW-ACTIVATION-UNIT */
Object activate_in_new_activation_unit(item)
    Object item;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, frame;
    Object sub_vector_qm, function_qm, temp;
    SI_Long method_index;

    x_note_fn_call(181,11);
    gensymed_symbol = Items_needing_initialization;
    if (EQ(gensymed_symbol,T)) {
      next_loop:
	gensymed_symbol_1 = Items_needing_initialization;
	gensymed_symbol_2 = Nil;
	if (CAS_SYMBOL(Qitems_needing_initialization,gensymed_symbol_1,
		gensymed_symbol_2))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:;
    }
    method_index = (SI_Long)6L;
    frame = item;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    temp = function_qm ? inline_funcall_1(function_qm,frame) : Nil;
    if (EQ(gensymed_symbol,T))
	initialize_items_needing_initialization();
    return VALUES_1(temp);
}

static Object Qlookup;             /* lookup */

/* MAKE-ITEMS-NEEDING-INITIALIZATION-TREE-FUNCTION */
Object make_items_needing_initialization_tree_function()
{
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(181,12);
    tail = 
	    make_items_needing_initialization_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_items_needing_initialization_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qitems_needing_initialization;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    return VALUES_1(gensymed_symbol);
}

static Object Qinitial_value;      /* initial-value */

static Object Qnever;              /* never */

static Object Qcomputation;        /* computation */

static Object Qg2_defstruct_structure_name_data_server_g2_struct;  /* g2-defstruct-structure-name::data-server-g2-struct */

/* INITIALIZE-ITEMS-NEEDING-INITIALIZATION */
Object initialize_items_needing_initialization()
{
    Object current_computation_frame, current_computation_instance;
    Object initializing_items_needing_initialization, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object frame_serial_number, item, ab_less_than_branch_qm_, xa, ya;
    Object sub_class_bit_vector, initial_value_qm, interval_qm, source_or_map;
    Object server_qm, data_server_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(181,13);
    current_computation_frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    3);
      current_computation_instance = Qinitial_value;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
	      2);
	initializing_items_needing_initialization = T;
	PUSH_SPECIAL_WITH_SYMBOL(Initializing_items_needing_initialization,Qinitializing_items_needing_initialization,initializing_items_needing_initialization,
		1);
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = Items_needing_initialization_tree;
	  ab_binary_tree_form_ = Items_needing_initialization_tree;
	  gensymed_symbol = CDR(Items_needing_initialization_tree);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  frame_serial_number = Nil;
	  item = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = M_CDR(ab_binary_tree_form_);
	  next_loop:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
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
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
		}
		else
		    ab_current_node_ = Nil;
	    }
	    else {
		if (ab_next_node_) {
		    ab_current_node_ = ab_next_node_;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_1:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_1;
		  end_loop:;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_1;
	    frame_serial_number = CAR(ab_entry_cons_);
	    item = CDR(ab_entry_cons_);
	    gensymed_symbol = ISVREF(item,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		Current_computation_frame = item;
		initialize_g2_array(item);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = Items_needing_initialization_tree;
	  ab_binary_tree_form_ = Items_needing_initialization_tree;
	  gensymed_symbol = CDR(Items_needing_initialization_tree);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  frame_serial_number = Nil;
	  item = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
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
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
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
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    frame_serial_number = CAR(ab_entry_cons_);
	    item = CDR(ab_entry_cons_);
	    gensymed_symbol = ISVREF(item,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if (temp_1);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    }
	    if ( !temp_1) {
		Current_computation_frame = item;
		initial_value_qm = ISVREF(item,(SI_Long)22L);
		if (initial_value_qm &&  !TRUEP(Warmbooting_qm)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value_qm)) 
			    == (SI_Long)1L)
			put_initial_float_value(item,initial_value_qm);
		    else if (INLINE_LONG_VECTOR_P(initial_value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value_qm)) 
			    == (SI_Long)1L)
			put_initial_long_value(item,initial_value_qm);
		    else {
			temp = item;
			put_current_value(6,temp,initial_value_qm,
				data_type_of_variable_or_parameter_datum(initial_value_qm,
				item),Qnever,Nil,Nil);
		    }
		}
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		interval_qm = temp_1 ? ISVREF(item,(SI_Long)32L) : Nil;
		if (interval_qm) {
		    source_or_map = ISVREF(item,(SI_Long)31L);
		    server_qm = ATOM(source_or_map) ? 
			    lookup_kb_specific_property_value(source_or_map,
			    Data_server_or_alias_qm_kbprop) : Nil;
		    data_server_qm = server_qm ? server_qm : 
			    warn_of_undefined_data_server(item,source_or_map);
		    if (data_server_qm) {
			if (EQ(data_server_qm,Qcomputation))
			    begin_collecting_data_for_inference_engine(item,
				    interval_qm);
			else if (SIMPLE_VECTOR_P(data_server_qm) && 
				EQ(ISVREF(data_server_qm,(SI_Long)0L),
				Qg2_defstruct_structure_name_data_server_g2_struct)) 
				    {
			    temp = SYMBOL_FUNCTION(ISVREF(data_server_qm,
				    (SI_Long)3L));
			    FUNCALL_2(temp,item,interval_qm);
			}
		    }
		}
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
	  clean_up_items_needing_initialization();
	  result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant;     /* "Cannot conclude initial value for ~NF: ~a" */

/* PUT-INITIAL-FLOAT-VALUE */
Object put_initial_float_value(variable_or_parameter,initial_value_float)
    Object variable_or_parameter, initial_value_float;
{
    Object new_value, problem_string_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(181,14);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_value = copy_managed_float(initial_value_float);
	problem_string_qm = 
		put_current_evaluation_value(variable_or_parameter,
		new_value,Qnever,Nil,Nil);
	if (problem_string_qm) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)1L),string_constant,
			variable_or_parameter,problem_string_qm);
	    Suppress_warning_message_header_qm = Nil;
	    reclaim_text_string(problem_string_qm);
	    reclaim_managed_simple_float_array_of_length_1(new_value);
	}
	result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* PUT-INITIAL-LONG-VALUE */
Object put_initial_long_value(variable_or_parameter,initial_value_long)
    Object variable_or_parameter, initial_value_long;
{
    Object new_value, problem_string_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(181,15);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_value = copy_managed_long(initial_value_long);
	problem_string_qm = 
		put_current_evaluation_value(variable_or_parameter,
		new_value,Qnever,Nil,Nil);
	if (problem_string_qm) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)1L),string_constant,
			variable_or_parameter,problem_string_qm);
	    Suppress_warning_message_header_qm = Nil;
	    reclaim_text_string(problem_string_qm);
	    reclaim_managed_simple_long_array_of_length_1(new_value);
	}
	result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* CLEAN-UP-ITEMS-NEEDING-INITIALIZATION */
Object clean_up_items_needing_initialization()
{
    Object gensymed_symbol, gensymed_symbol_1;
    char temp;

    x_note_fn_call(181,16);
    if ( !TRUEP(ACCESS_ONCE(Items_needing_initialization)))
	clear_items_needing_initialization_tree(Items_needing_initialization_tree);
  next_loop:
    gensymed_symbol = Items_needing_initialization;
    gensymed_symbol_1 = T;
    if (CAS_SYMBOL(Qitems_needing_initialization,gensymed_symbol,
	    gensymed_symbol_1)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:
    return VALUES_1( !temp ? T : Nil);
}

static Object Qitem_active;        /* item-active */

static Object Qis_activated;       /* is-activated */

/* ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-KB-FRAME */
Object activate_if_possible_and_propagate_for_kb_frame(kb_frame)
    Object kb_frame;
{
    Object collecting_updates_to_sensor_attributes_p;
    Object collected_updates_to_sensor_attributes, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, frame, sub_vector_qm;
    Object function_qm, class_description, ab_loop_list_, gensymed_symbol_3;
    Object x2, temp, gensymed_symbol_4;
    SI_Long svref_new_value, method_index;
    Declare_special(2);
    Object result;

    x_note_fn_call(181,17);
    if ( !((SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)5L)) & 
		(SI_Long)1L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(kb_frame);
	collecting_updates_to_sensor_attributes_p = T;
	collected_updates_to_sensor_attributes = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Collected_updates_to_sensor_attributes,Qcollected_updates_to_sensor_attributes,collected_updates_to_sensor_attributes,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p,Qcollecting_updates_to_sensor_attributes_p,collecting_updates_to_sensor_attributes_p,
		  0);
	    gensymed_symbol = Items_needing_initialization;
	    if (EQ(gensymed_symbol,T)) {
	      next_loop:
		gensymed_symbol_1 = Items_needing_initialization;
		gensymed_symbol_2 = Nil;
		if (CAS_SYMBOL(Qitems_needing_initialization,
			gensymed_symbol_1,gensymed_symbol_2))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    svref_new_value = IFIX(ISVREF(kb_frame,(SI_Long)5L)) &  
		    ~(SI_Long)256L;
	    ISVREF(kb_frame,(SI_Long)5L) = FIX(svref_new_value);
	    if (frame_not_bad_p(kb_frame) &&  !((SI_Long)0L != 
		    (IFIX(ISVREF(kb_frame,(SI_Long)4L)) & (SI_Long)8192L))) {
		method_index = (SI_Long)6L;
		frame = kb_frame;
		sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)11L),method_index);
		function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
			(SI_Long)1L) : Nil;
		if (function_qm)
		    inline_funcall_1(function_qm,frame);
		if ((SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)5L)) & 
			(SI_Long)64L))
		    put_parent_for_its_indexed_attributes(1,kb_frame);
		gensymed_symbol_1 = kb_frame;
		svref_new_value = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)5L)) | (SI_Long)1L;
		ISVREF(gensymed_symbol_1,(SI_Long)5L) = FIX(svref_new_value);
		update_subscriptions_from_virtual_attribute_change(gensymed_symbol_1,
			get_property_value_function(3,
			get_symbol_properties_function(Qitem_active),
			Qvirtual_attribute,Nil),Nil);
		if (ISVREF(gensymed_symbol_1,(SI_Long)9L))
		    update_representations_of_slot_value(2,
			    gensymed_symbol_1,Qframe_status_and_notes);
		if ( !TRUEP(Warmbooting_qm))
		    schedule_task_to_invoke_existential_rules(kb_frame,
			    Qis_activated);
		gensymed_symbol_1 = kb_frame;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
				(SI_Long)1L);
			inline_funcall_1(gensymed_symbol_2,gensymed_symbol_3);
		    }
		}
		goto next_loop_1;
	      end_loop_1:
		temp = Qnil;
	    }
	    else {
		gensymed_symbol_1 = kb_frame;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
				(SI_Long)1L);
			gensymed_symbol_4 = T;
			inline_funcall_2(gensymed_symbol_2,
				gensymed_symbol_3,gensymed_symbol_4);
		    }
		}
		goto next_loop_2;
	      end_loop_2:
		temp = Qnil;
	    }
	    if (EQ(gensymed_symbol,T))
		initialize_items_needing_initialization();
	    handle_collected_updates_to_sensor_attributes();
	    result = VALUES_1(temp);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qis_deactivated;     /* is-deactivated */

/* DEACTIVATE-AND-PROPAGATE-FOR-KB-FRAME */
Object deactivate_and_propagate_for_kb_frame(kb_frame,
	    ancestor_not_activatable_qm)
    Object kb_frame, ancestor_not_activatable_qm;
{
    Object frame, sub_vector_qm, function_qm, parent_qm, temp;
    Object sub_class_bit_vector, gensymed_symbol_3;
    Object this_frame_is_not_activatable_qm, gensymed_symbol_4;
    Object class_description, ab_loop_list_, gensymed_symbol_5, x2;
    Object gensymed_symbol_6;
    SI_Long svref_new_value, method_index, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(181,18);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(kb_frame);
    if (ancestor_not_activatable_qm) {
	svref_new_value = IFIX(ISVREF(kb_frame,(SI_Long)5L)) | (SI_Long)256L;
	ISVREF(kb_frame,(SI_Long)5L) = FIX(svref_new_value);
	method_index = (SI_Long)53L;
	frame = kb_frame;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
    }
    else {
	svref_new_value = IFIX(ISVREF(kb_frame,(SI_Long)5L)) &  ~(SI_Long)256L;
	ISVREF(kb_frame,(SI_Long)5L) = FIX(svref_new_value);
    }
    parent_qm = get_lookup_slot_value_given_default(kb_frame,Qparent_frame,
	    Nil);
    if (parent_qm && (SI_Long)0L != (IFIX(ISVREF(parent_qm,(SI_Long)5L)) & 
	    (SI_Long)64L)) {
	temp = get_pretty_slot_name_for_parent_attribute_if_any(kb_frame);
	remove_parent_if_indexed_attribute(temp,
		get_defining_class_for_parent_attribute_if_any(kb_frame),
		kb_frame,parent_qm);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)5L)) & (SI_Long)64L))
	remove_parent_for_its_indexed_attributes(kb_frame);
    if ((SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)5L)) & (SI_Long)1L)) {
	if ( !TRUEP(In_suspend_resume_p)) {
	    if (ISVREF(kb_frame,(SI_Long)13L)) {
		sub_class_bit_vector = ISVREF(ISVREF(kb_frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		temp_1 =  !temp_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		remove_element_from_all_g2_lists(kb_frame,T);
	}
	if (ISVREF(kb_frame,(SI_Long)15L))
	    trigger_and_clear_event_detectors(kb_frame);
	if ( !TRUEP(Warmbooting_qm))
	    schedule_task_to_invoke_existential_rules(kb_frame,
		    Qis_deactivated);
	method_index = (SI_Long)7L;
	frame = kb_frame;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
	gensymed_symbol_3 = kb_frame;
	svref_new_value = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)5L)) &  
		~(SI_Long)1L;
	ISVREF(gensymed_symbol_3,(SI_Long)5L) = FIX(svref_new_value);
	update_subscriptions_from_virtual_attribute_change(gensymed_symbol_3,
		get_property_value_function(3,
		get_symbol_properties_function(Qitem_active),
		Qvirtual_attribute,Nil),Nil);
	if (ISVREF(gensymed_symbol_3,(SI_Long)9L))
	    update_representations_of_slot_value(2,gensymed_symbol_3,
		    Qframe_status_and_notes);
    }
    this_frame_is_not_activatable_qm = (SI_Long)0L != 
	    (IFIX(ISVREF(kb_frame,(SI_Long)5L)) & (SI_Long)256L) ? T : Nil;
    if (this_frame_is_not_activatable_qm);
    else
	this_frame_is_not_activatable_qm = (SI_Long)0L != 
		(IFIX(ISVREF(kb_frame,(SI_Long)4L)) & (SI_Long)8192L) ? T :
		 Nil;
    if (this_frame_is_not_activatable_qm);
    else {
	temp = ISVREF(kb_frame,(SI_Long)8L);
	this_frame_is_not_activatable_qm = CAR(temp);
    }
    gensymed_symbol_3 = kb_frame;
    gensymed_symbol_4 = Nil;
    class_description = ISVREF(gensymed_symbol_3,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol_4 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(gensymed_symbol_4,(SI_Long)8L)) {
	gensymed_symbol_5 = get_slot_description_value(gensymed_symbol_3,
		gensymed_symbol_4);
	if (SIMPLE_VECTOR_P(gensymed_symbol_5) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_5)) > 
		(SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gensymed_symbol_5,(SI_Long)1L);
	    gensymed_symbol_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_4 = Nil;
	if (gensymed_symbol_4 && ISVREF(gensymed_symbol_4,(SI_Long)16L)) {
	    gensymed_symbol_4 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_5,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_6 = this_frame_is_not_activatable_qm;
	    inline_funcall_2(gensymed_symbol_4,gensymed_symbol_5,
		    gensymed_symbol_6);
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-KB-WORKSPACE */
Object activate_if_possible_and_propagate_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object collecting_updates_to_sensor_attributes_p;
    Object collected_updates_to_sensor_attributes, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, ab_queue_form_;
    Object ab_next_queue_element_, subblock, within_activate_for_kb_workspace;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object connection_frame_or_class, temp, ab_less_than_branch_qm_;
    Object class_description, ab_loop_list_, gensymed_symbol_3, x2;
    Object gensymed_symbol_4;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(181,19);
    if ( !((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & 
	    (SI_Long)1L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(kb_workspace);
	collecting_updates_to_sensor_attributes_p = T;
	collected_updates_to_sensor_attributes = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Collected_updates_to_sensor_attributes,Qcollected_updates_to_sensor_attributes,collected_updates_to_sensor_attributes,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p,Qcollecting_updates_to_sensor_attributes_p,collecting_updates_to_sensor_attributes_p,
		  2);
	    gensymed_symbol = Items_needing_initialization;
	    if (EQ(gensymed_symbol,T)) {
	      next_loop:
		gensymed_symbol_1 = Items_needing_initialization;
		gensymed_symbol_2 = Nil;
		if (CAS_SYMBOL(Qitems_needing_initialization,
			gensymed_symbol_1,gensymed_symbol_2))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)5L)) &  
		    ~(SI_Long)256L;
	    ISVREF(kb_workspace,(SI_Long)5L) = FIX(svref_new_value);
	    if (frame_not_bad_p(kb_workspace) &&  !((SI_Long)0L != 
		    (IFIX(ISVREF(kb_workspace,(SI_Long)4L)) & 
			(SI_Long)8192L))) {
		gensymed_symbol_1 = ACCESS_ONCE(ISVREF(kb_workspace,
			(SI_Long)14L));
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)4L)) 
			: Nil;
		ab_queue_form_ = gensymed_symbol_1;
		ab_next_queue_element_ = Nil;
		subblock = Nil;
		within_activate_for_kb_workspace = T;
		PUSH_SPECIAL_WITH_SYMBOL(Within_activate_for_kb_workspace,Qwithin_activate_for_kb_workspace,within_activate_for_kb_workspace,
			1);
		  if (ab_queue_form_)
		      ab_next_queue_element_ = 
			      constant_queue_next(ISVREF(ab_queue_form_,
			      (SI_Long)2L),ab_queue_form_);
		next_loop_1:
		  if ( !TRUEP(ab_next_queue_element_))
		      goto end_loop_1;
		  subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		  ab_next_queue_element_ = 
			  constant_queue_next(ab_next_queue_element_,
			  ab_queue_form_);
		  gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
			  (SI_Long)1L);
		  gensymed_symbol_2 = subblock;
		  inline_funcall_1(gensymed_symbol_1,gensymed_symbol_2);
		  gensymed_symbol_1 = ACCESS_ONCE(ISVREF(subblock,
			  (SI_Long)14L));
		  gensymed_symbol_1 = gensymed_symbol_1 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			  (SI_Long)6L)) : Nil;
		  if (gensymed_symbol_1) {
		      scope_conses = Scope_conses;
		      ab_node_stack_ = Nil;
		      ab_current_node_ = Nil;
		      gensymed_symbol_1 = ACCESS_ONCE(ISVREF(subblock,
			      (SI_Long)14L));
		      gensymed_symbol_1 = gensymed_symbol_1 ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			      (SI_Long)6L)) : Nil;
		      ab_skip_list_form_ = gensymed_symbol_1;
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
			connection_frame_or_class = Nil;
			gensymed_symbol_1 = CDR(ab_skip_list_form_);
			if (CONSP(gensymed_symbol_1)) {
			    temp = M_CAR(gensymed_symbol_1);
			    temp_1 = SIMPLE_VECTOR_P(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = M_CDR(gensymed_symbol_1);
			    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
		      next_loop_2:
		      next_loop_3:
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
				ab_connection_ = ISVREF(ab_current_node_,
					(SI_Long)2L);
				ab_connection_item_ = 
					ISVREF(ab_current_node_,(SI_Long)3L);
			    }
			    else
				ab_current_node_ = Nil;
			}
			else {
			    if (ab_next_node_) {
				ab_current_node_ = ab_next_node_;
				ab_less_than_branch_qm_ = Nil;
			      next_loop_4:
				ab_less_than_branch_qm_ = 
					ISVREF(ab_current_node_,(SI_Long)1L);
				if ( !TRUEP(ab_less_than_branch_qm_))
				    goto end_loop_2;
				ab_node_stack_ = 
					scope_cons(ab_current_node_,
					ab_node_stack_);
				ab_current_node_ = ab_less_than_branch_qm_;
				goto next_loop_4;
			      end_loop_2:;
			    }
			    else if (ab_node_stack_) {
				ab_next_node_ = ab_node_stack_;
				ab_current_node_ = M_CAR(ab_node_stack_);
				ab_node_stack_ = M_CDR(ab_node_stack_);
			    }
			    else
				ab_current_node_ = Nil;
			    if (ab_current_node_) {
				ab_next_node_ = ISVREF(ab_current_node_,
					(SI_Long)2L);
				ab_current_alist_ = 
					ISVREF(ab_current_node_,(SI_Long)3L);
				ab_entry_cons_ = M_CAR(ab_current_alist_);
				ab_connection_ = M_CAR(ab_entry_cons_);
				ab_connection_item_ = M_CDR(ab_entry_cons_);
				ab_current_alist_ = M_CDR(ab_current_alist_);
			    }
			}
			if ( !TRUEP(ab_current_node_) || ab_current_node_ 
				&& ab_connection_ && 
				EQ(ISVREF(ab_connection_,(SI_Long)3L),
				subblock))
			    goto end_2;
			goto next_loop_3;
		      end_loop_3:
		      end_2:
			if ( !TRUEP(ab_current_node_))
			    goto end_loop_4;
			connection = ab_connection_;
			connection_frame_or_class = ISVREF(connection,
				(SI_Long)1L);
			if ( !SYMBOLP(connection_frame_or_class)) {
			    gensymed_symbol_1 = 
				    ISVREF(ISVREF(ISVREF(ISVREF(connection_frame_or_class,
				    (SI_Long)1L),(SI_Long)11L),
				    (SI_Long)30L),(SI_Long)1L);
			    gensymed_symbol_2 = connection_frame_or_class;
			    inline_funcall_1(gensymed_symbol_1,
				    gensymed_symbol_2);
			}
			goto next_loop_2;
		      end_loop_4:;
		      POP_SPECIAL();
		  }
		  goto next_loop_1;
		end_loop_1:;
		POP_SPECIAL();
		gensymed_symbol_1 = kb_workspace;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
				(SI_Long)1L);
			inline_funcall_1(gensymed_symbol_2,gensymed_symbol_3);
		    }
		}
		goto next_loop_5;
	      end_loop_5:;
		activate_for_kb_workspace(kb_workspace);
		if ((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) 
			& (SI_Long)64L))
		    put_parent_for_its_indexed_attributes(1,kb_workspace);
		gensymed_symbol_1 = kb_workspace;
		svref_new_value = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)5L)) | (SI_Long)1L;
		ISVREF(gensymed_symbol_1,(SI_Long)5L) = FIX(svref_new_value);
		update_subscriptions_from_virtual_attribute_change(gensymed_symbol_1,
			get_property_value_function(3,
			get_symbol_properties_function(Qitem_active),
			Qvirtual_attribute,Nil),Nil);
		if (ISVREF(gensymed_symbol_1,(SI_Long)9L))
		    update_representations_of_slot_value(2,
			    gensymed_symbol_1,Qframe_status_and_notes);
		temp =  !TRUEP(Warmbooting_qm) ? 
			schedule_task_to_invoke_existential_rules(kb_workspace,
			Qis_activated) : Nil;
	    }
	    else {
		gensymed_symbol_1 = ACCESS_ONCE(ISVREF(kb_workspace,
			(SI_Long)14L));
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)4L)) 
			: Nil;
		ab_queue_form_ = gensymed_symbol_1;
		ab_next_queue_element_ = Nil;
		subblock = Nil;
		if (ab_queue_form_)
		    ab_next_queue_element_ = 
			    constant_queue_next(ISVREF(ab_queue_form_,
			    (SI_Long)2L),ab_queue_form_);
	      next_loop_6:
		if ( !TRUEP(ab_next_queue_element_))
		    goto end_loop_6;
		subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		ab_next_queue_element_ = 
			constant_queue_next(ab_next_queue_element_,
			ab_queue_form_);
		gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(subblock,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
		gensymed_symbol_2 = subblock;
		gensymed_symbol_3 = T;
		inline_funcall_2(gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3);
		gensymed_symbol_1 = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) 
			: Nil;
		if (gensymed_symbol_1) {
		    scope_conses = Scope_conses;
		    ab_node_stack_ = Nil;
		    ab_current_node_ = Nil;
		    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(subblock,
			    (SI_Long)14L));
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			    (SI_Long)6L)) : Nil;
		    ab_skip_list_form_ = gensymed_symbol_1;
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
		      connection_frame_or_class = Nil;
		      gensymed_symbol_1 = CDR(ab_skip_list_form_);
		      if (CONSP(gensymed_symbol_1)) {
			  temp = M_CAR(gensymed_symbol_1);
			  temp_1 = SIMPLE_VECTOR_P(temp);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1) {
			  temp = M_CDR(gensymed_symbol_1);
			  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
		    next_loop_7:
		    next_loop_8:
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
			      ab_connection_ = ISVREF(ab_current_node_,
				      (SI_Long)2L);
			      ab_connection_item_ = 
				      ISVREF(ab_current_node_,(SI_Long)3L);
			  }
			  else
			      ab_current_node_ = Nil;
		      }
		      else {
			  if (ab_next_node_) {
			      ab_current_node_ = ab_next_node_;
			      ab_less_than_branch_qm_ = Nil;
			    next_loop_9:
			      ab_less_than_branch_qm_ = 
				      ISVREF(ab_current_node_,(SI_Long)1L);
			      if ( !TRUEP(ab_less_than_branch_qm_))
				  goto end_loop_7;
			      ab_node_stack_ = scope_cons(ab_current_node_,
				      ab_node_stack_);
			      ab_current_node_ = ab_less_than_branch_qm_;
			      goto next_loop_9;
			    end_loop_7:;
			  }
			  else if (ab_node_stack_) {
			      ab_next_node_ = ab_node_stack_;
			      ab_current_node_ = M_CAR(ab_node_stack_);
			      ab_node_stack_ = M_CDR(ab_node_stack_);
			  }
			  else
			      ab_current_node_ = Nil;
			  if (ab_current_node_) {
			      ab_next_node_ = ISVREF(ab_current_node_,
				      (SI_Long)2L);
			      ab_current_alist_ = ISVREF(ab_current_node_,
				      (SI_Long)3L);
			      ab_entry_cons_ = M_CAR(ab_current_alist_);
			      ab_connection_ = M_CAR(ab_entry_cons_);
			      ab_connection_item_ = M_CDR(ab_entry_cons_);
			      ab_current_alist_ = M_CDR(ab_current_alist_);
			  }
		      }
		      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
			      ab_connection_ && EQ(ISVREF(ab_connection_,
			      (SI_Long)3L),subblock))
			  goto end_3;
		      goto next_loop_8;
		    end_loop_8:
		    end_3:
		      if ( !TRUEP(ab_current_node_))
			  goto end_loop_9;
		      connection = ab_connection_;
		      connection_frame_or_class = ISVREF(connection,
			      (SI_Long)1L);
		      if ( !SYMBOLP(connection_frame_or_class)) {
			  gensymed_symbol_1 = 
				  ISVREF(ISVREF(ISVREF(ISVREF(connection_frame_or_class,
				  (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
				  (SI_Long)1L);
			  gensymed_symbol_2 = connection_frame_or_class;
			  gensymed_symbol_3 = T;
			  inline_funcall_2(gensymed_symbol_1,
				  gensymed_symbol_2,gensymed_symbol_3);
		      }
		      goto next_loop_7;
		    end_loop_9:;
		    POP_SPECIAL();
		}
		goto next_loop_6;
	      end_loop_6:;
		gensymed_symbol_1 = kb_workspace;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_10:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_10;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
				(SI_Long)1L);
			gensymed_symbol_4 = T;
			inline_funcall_2(gensymed_symbol_2,
				gensymed_symbol_3,gensymed_symbol_4);
		    }
		}
		goto next_loop_10;
	      end_loop_10:
		temp = Qnil;
	    }
	    if (EQ(gensymed_symbol,T))
		initialize_items_needing_initialization();
	    handle_collected_updates_to_sensor_attributes();
	    result = VALUES_1(temp);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-AND-PROPAGATE-FOR-KB-WORKSPACE */
Object deactivate_and_propagate_for_kb_workspace(kb_workspace,
	    ancestor_not_activatable_qm)
    Object kb_workspace, ancestor_not_activatable_qm;
{
    Object parent_qm, temp, sub_class_bit_vector, gensymed_symbol_3;
    Object this_frame_is_not_activatable_qm, ab_queue_form_;
    Object ab_next_queue_element_, subblock, gensymed_symbol_4;
    Object gensymed_symbol_5, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class;
    Object ab_less_than_branch_qm_, class_description, ab_loop_list_, x2;
    Object gensymed_symbol_6;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(181,20);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(kb_workspace);
    if (ancestor_not_activatable_qm) {
	svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)5L)) | 
		(SI_Long)256L;
	ISVREF(kb_workspace,(SI_Long)5L) = FIX(svref_new_value);
    }
    else {
	svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)5L)) &  
		~(SI_Long)256L;
	ISVREF(kb_workspace,(SI_Long)5L) = FIX(svref_new_value);
    }
    parent_qm = get_lookup_slot_value_given_default(kb_workspace,
	    Qparent_frame,Nil);
    if (parent_qm && (SI_Long)0L != (IFIX(ISVREF(parent_qm,(SI_Long)5L)) & 
	    (SI_Long)64L)) {
	temp = get_pretty_slot_name_for_parent_attribute_if_any(kb_workspace);
	remove_parent_if_indexed_attribute(temp,
		get_defining_class_for_parent_attribute_if_any(kb_workspace),
		kb_workspace,parent_qm);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & (SI_Long)64L))
	remove_parent_for_its_indexed_attributes(kb_workspace);
    if ((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & 
		(SI_Long)1L)) {
	if ( !TRUEP(In_suspend_resume_p)) {
	    if (ISVREF(kb_workspace,(SI_Long)13L)) {
		sub_class_bit_vector = ISVREF(ISVREF(kb_workspace,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		temp_1 =  !temp_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		remove_element_from_all_g2_lists(kb_workspace,T);
	}
	if (ISVREF(kb_workspace,(SI_Long)15L))
	    trigger_and_clear_event_detectors(kb_workspace);
	if ( !TRUEP(Warmbooting_qm))
	    schedule_task_to_invoke_existential_rules(kb_workspace,
		    Qis_deactivated);
	deactivate_for_kb_workspace(kb_workspace);
	gensymed_symbol_3 = kb_workspace;
	svref_new_value = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)5L)) &  
		~(SI_Long)1L;
	ISVREF(gensymed_symbol_3,(SI_Long)5L) = FIX(svref_new_value);
	update_subscriptions_from_virtual_attribute_change(gensymed_symbol_3,
		get_property_value_function(3,
		get_symbol_properties_function(Qitem_active),
		Qvirtual_attribute,Nil),Nil);
	if (ISVREF(gensymed_symbol_3,(SI_Long)9L))
	    update_representations_of_slot_value(2,gensymed_symbol_3,
		    Qframe_status_and_notes);
    }
    this_frame_is_not_activatable_qm = (SI_Long)0L != 
	    (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & (SI_Long)256L) ? T : Nil;
    if (this_frame_is_not_activatable_qm);
    else
	this_frame_is_not_activatable_qm = (SI_Long)0L != 
		(IFIX(ISVREF(kb_workspace,(SI_Long)4L)) & (SI_Long)8192L) ?
		 T : Nil;
    if (this_frame_is_not_activatable_qm);
    else {
	temp = ISVREF(kb_workspace,(SI_Long)8L);
	this_frame_is_not_activatable_qm = CAR(temp);
    }
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol_3;
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
    gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(subblock,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
    gensymed_symbol_4 = subblock;
    gensymed_symbol_5 = this_frame_is_not_activatable_qm;
    inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
    if (gensymed_symbol_3) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
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
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_or_class = Nil;
	  gensymed_symbol_3 = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol_3)) {
	      temp = M_CAR(gensymed_symbol_3);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol_3);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
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
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
		  ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),
		  subblock))
	      goto end_1;
	  goto next_loop_2;
	end_loop_2:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  connection = ab_connection_;
	  connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	  if ( !SYMBOLP(connection_frame_or_class)) {
	      gensymed_symbol_3 = 
		      ISVREF(ISVREF(ISVREF(ISVREF(connection_frame_or_class,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	      gensymed_symbol_4 = connection_frame_or_class;
	      gensymed_symbol_5 = this_frame_is_not_activatable_qm;
	      inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
		      gensymed_symbol_5);
	  }
	  goto next_loop_1;
	end_loop_3:;
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:;
    gensymed_symbol_3 = kb_workspace;
    gensymed_symbol_4 = Nil;
    class_description = ISVREF(gensymed_symbol_3,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    gensymed_symbol_4 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(gensymed_symbol_4,(SI_Long)8L)) {
	gensymed_symbol_5 = get_slot_description_value(gensymed_symbol_3,
		gensymed_symbol_4);
	if (SIMPLE_VECTOR_P(gensymed_symbol_5) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_5)) > 
		(SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gensymed_symbol_5,(SI_Long)1L);
	    gensymed_symbol_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_4 = Nil;
	if (gensymed_symbol_4 && ISVREF(gensymed_symbol_4,(SI_Long)16L)) {
	    gensymed_symbol_4 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_5,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_6 = this_frame_is_not_activatable_qm;
	    inline_funcall_2(gensymed_symbol_4,gensymed_symbol_5,
		    gensymed_symbol_6);
	}
    }
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

static Object Qsimulation_details;  /* simulation-details */

/* ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-ENTITY */
Object activate_if_possible_and_propagate_for_entity(entity)
    Object entity;
{
    Object collecting_updates_to_sensor_attributes_p;
    Object collected_updates_to_sensor_attributes, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, subworkspace_list, frame;
    Object sub_vector_qm, function_qm, subworkspace, ab_loop_list_;
    Object class_description, gensymed_symbol_3, x2, sub_class_bit_vector;
    Object simulation_details, temp_1, gensymed_symbol_7;
    SI_Long svref_new_value, method_index, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(181,21);
    if ( !((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & (SI_Long)1L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(entity);
	collecting_updates_to_sensor_attributes_p = T;
	collected_updates_to_sensor_attributes = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Collected_updates_to_sensor_attributes,Qcollected_updates_to_sensor_attributes,collected_updates_to_sensor_attributes,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p,Qcollecting_updates_to_sensor_attributes_p,collecting_updates_to_sensor_attributes_p,
		  0);
	    gensymed_symbol = Items_needing_initialization;
	    if (EQ(gensymed_symbol,T)) {
	      next_loop:
		gensymed_symbol_1 = Items_needing_initialization;
		gensymed_symbol_2 = Nil;
		if (CAS_SYMBOL(Qitems_needing_initialization,
			gensymed_symbol_1,gensymed_symbol_2))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    subworkspace_list = ISVREF(entity,(SI_Long)18L);
	    svref_new_value = IFIX(ISVREF(entity,(SI_Long)5L)) &  
		    ~(SI_Long)256L;
	    ISVREF(entity,(SI_Long)5L) = FIX(svref_new_value);
	    if (frame_not_bad_p(entity) &&  !((SI_Long)0L != 
		    (IFIX(ISVREF(entity,(SI_Long)4L)) & (SI_Long)8192L))) {
		method_index = (SI_Long)6L;
		frame = entity;
		sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)11L),method_index);
		function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
			(SI_Long)1L) : Nil;
		if (function_qm)
		    inline_funcall_1(function_qm,frame);
		if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
			(SI_Long)64L))
		    put_parent_for_its_indexed_attributes(1,entity);
		gensymed_symbol_1 = entity;
		svref_new_value = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)5L)) | (SI_Long)1L;
		ISVREF(gensymed_symbol_1,(SI_Long)5L) = FIX(svref_new_value);
		update_subscriptions_from_virtual_attribute_change(gensymed_symbol_1,
			get_property_value_function(3,
			get_symbol_properties_function(Qitem_active),
			Qvirtual_attribute,Nil),Nil);
		if (ISVREF(gensymed_symbol_1,(SI_Long)9L))
		    update_representations_of_slot_value(2,
			    gensymed_symbol_1,Qframe_status_and_notes);
		if ( !TRUEP(Warmbooting_qm))
		    schedule_task_to_invoke_existential_rules(entity,
			    Qis_activated);
		if (subworkspace_list) {
		    if ( 
			    !TRUEP(get_property_value_in_object_configuration(entity,
			    Qactivatable_subworkspace,Nil))) {
			subworkspace = Nil;
			ab_loop_list_ = subworkspace_list;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			subworkspace = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			gensymed_symbol_1 = 
				ISVREF(ISVREF(ISVREF(ISVREF(subworkspace,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
				(SI_Long)1L);
			gensymed_symbol_2 = subworkspace;
			inline_funcall_1(gensymed_symbol_1,gensymed_symbol_2);
			goto next_loop_1;
		      end_loop_1:;
		    }
		    else if (Warmbooting_qm) {
			subworkspace = Nil;
			ab_loop_list_ = subworkspace_list;
		      next_loop_2:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_2;
			subworkspace = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if ((SI_Long)0L != (IFIX(ISVREF(subworkspace,
				(SI_Long)5L)) & (SI_Long)32L)) {
			    svref_new_value = IFIX(ISVREF(subworkspace,
				    (SI_Long)5L)) &  ~(SI_Long)32L;
			    ISVREF(subworkspace,(SI_Long)5L) = 
				    FIX(svref_new_value);
			    gensymed_symbol_1 = 
				    ISVREF(ISVREF(ISVREF(ISVREF(subworkspace,
				    (SI_Long)1L),(SI_Long)11L),
				    (SI_Long)30L),(SI_Long)1L);
			    gensymed_symbol_2 = subworkspace;
			    inline_funcall_1(gensymed_symbol_1,
				    gensymed_symbol_2);
			}
			goto next_loop_2;
		      end_loop_2:;
		    }
		}
		gensymed_symbol_1 = entity;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
				(SI_Long)1L);
			inline_funcall_1(gensymed_symbol_2,gensymed_symbol_3);
		    }
		}
		goto next_loop_3;
	      end_loop_3:;
		sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_4 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_5 = (SI_Long)1L;
		    gensymed_symbol_6 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_5 = gensymed_symbol_5 << gensymed_symbol_6;
		    gensymed_symbol_4 = gensymed_symbol_4 & gensymed_symbol_5;
		    temp = (SI_Long)0L < gensymed_symbol_4;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    simulation_details = get_lookup_slot_value(entity,
			    Qsimulation_details);
		    temp_1 = simulation_details ? 
			    activate_if_possible_and_propagate_for_kb_frame(simulation_details) 
			    : Nil;
		}
		else
		    temp_1 = Nil;
	    }
	    else {
		subworkspace = Nil;
		ab_loop_list_ = subworkspace_list;
	      next_loop_4:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_4;
		subworkspace = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol_1 = 
			ISVREF(ISVREF(ISVREF(ISVREF(subworkspace,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
		gensymed_symbol_2 = subworkspace;
		gensymed_symbol_3 = Nil;
		inline_funcall_2(gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3);
		goto next_loop_4;
	      end_loop_4:;
		gensymed_symbol_1 = entity;
		gensymed_symbol_2 = Nil;
		class_description = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		gensymed_symbol_2 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(gensymed_symbol_2,(SI_Long)8L)) {
		    gensymed_symbol_3 = 
			    get_slot_description_value(gensymed_symbol_1,
			    gensymed_symbol_2);
		    if (SIMPLE_VECTOR_P(gensymed_symbol_3) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_3,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
			gensymed_symbol_2 = SIMPLE_VECTOR_P(x2) && 
				EQ(ISVREF(x2,(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? x2 : Qnil;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if (gensymed_symbol_2 && ISVREF(gensymed_symbol_2,
			    (SI_Long)16L)) {
			gensymed_symbol_2 = 
				ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
				(SI_Long)1L);
			gensymed_symbol_7 = T;
			inline_funcall_2(gensymed_symbol_2,
				gensymed_symbol_3,gensymed_symbol_7);
		    }
		}
		goto next_loop_5;
	      end_loop_5:
		temp_1 = Qnil;
	    }
	    if (EQ(gensymed_symbol,T))
		initialize_items_needing_initialization();
	    handle_collected_updates_to_sensor_attributes();
	    result = VALUES_1(temp_1);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-AND-PROPAGATE-FOR-ENTITY */
Object deactivate_and_propagate_for_entity(entity,ancestor_not_activatable_qm)
    Object entity, ancestor_not_activatable_qm;
{
    Object frame, sub_vector_qm, function_qm, parent_qm, temp;
    Object sub_class_bit_vector, gensymed_symbol_3;
    Object this_frame_is_not_activatable_qm, subworkspace, ab_loop_list_, x2;
    Object gensymed_symbol_4, gensymed_symbol_5, simulation_details;
    Object class_description, gensymed_symbol_6;
    SI_Long svref_new_value, method_index, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(181,22);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(entity);
    if (ancestor_not_activatable_qm) {
	svref_new_value = IFIX(ISVREF(entity,(SI_Long)5L)) | (SI_Long)256L;
	ISVREF(entity,(SI_Long)5L) = FIX(svref_new_value);
	method_index = (SI_Long)53L;
	frame = entity;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
    }
    else {
	svref_new_value = IFIX(ISVREF(entity,(SI_Long)5L)) &  ~(SI_Long)256L;
	ISVREF(entity,(SI_Long)5L) = FIX(svref_new_value);
    }
    parent_qm = get_lookup_slot_value_given_default(entity,Qparent_frame,Nil);
    if (parent_qm && (SI_Long)0L != (IFIX(ISVREF(parent_qm,(SI_Long)5L)) & 
	    (SI_Long)64L)) {
	temp = get_pretty_slot_name_for_parent_attribute_if_any(entity);
	remove_parent_if_indexed_attribute(temp,
		get_defining_class_for_parent_attribute_if_any(entity),
		entity,parent_qm);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & (SI_Long)64L))
	remove_parent_for_its_indexed_attributes(entity);
    if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & (SI_Long)1L)) {
	if ( !TRUEP(In_suspend_resume_p)) {
	    if (ISVREF(entity,(SI_Long)13L)) {
		sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		temp_1 =  !temp_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		remove_element_from_all_g2_lists(entity,T);
	}
	if (ISVREF(entity,(SI_Long)15L))
	    trigger_and_clear_event_detectors(entity);
	if ( !TRUEP(Warmbooting_qm))
	    schedule_task_to_invoke_existential_rules(entity,Qis_deactivated);
	method_index = (SI_Long)7L;
	frame = entity;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_1(function_qm,frame);
	gensymed_symbol_3 = entity;
	svref_new_value = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)5L)) &  
		~(SI_Long)1L;
	ISVREF(gensymed_symbol_3,(SI_Long)5L) = FIX(svref_new_value);
	update_subscriptions_from_virtual_attribute_change(gensymed_symbol_3,
		get_property_value_function(3,
		get_symbol_properties_function(Qitem_active),
		Qvirtual_attribute,Nil),Nil);
	if (ISVREF(gensymed_symbol_3,(SI_Long)9L))
	    update_representations_of_slot_value(2,gensymed_symbol_3,
		    Qframe_status_and_notes);
    }
    this_frame_is_not_activatable_qm = (SI_Long)0L != (IFIX(ISVREF(entity,
	    (SI_Long)5L)) & (SI_Long)256L) ? T : Nil;
    if (this_frame_is_not_activatable_qm);
    else
	this_frame_is_not_activatable_qm = (SI_Long)0L != 
		(IFIX(ISVREF(entity,(SI_Long)4L)) & (SI_Long)8192L) ? T : Nil;
    if (this_frame_is_not_activatable_qm);
    else {
	temp = ISVREF(entity,(SI_Long)8L);
	this_frame_is_not_activatable_qm = CAR(temp);
    }
    subworkspace = Nil;
    ab_loop_list_ = ISVREF(entity,(SI_Long)18L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subworkspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(subworkspace) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subworkspace)) > (SI_Long)2L && 
	     !EQ(ISVREF(subworkspace,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(subworkspace,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(subworkspace,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_4 = subworkspace;
	gensymed_symbol_5 = this_frame_is_not_activatable_qm;
	inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5);
    }
    goto next_loop;
  end_loop:;
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
	temp_1 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	simulation_details = get_lookup_slot_value(entity,Qsimulation_details);
	if (SIMPLE_VECTOR_P(simulation_details) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simulation_details)) > 
		(SI_Long)2L &&  !EQ(ISVREF(simulation_details,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(simulation_details,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    deactivate_and_propagate_for_kb_frame(simulation_details,
		    this_frame_is_not_activatable_qm);
    }
    gensymed_symbol_3 = entity;
    gensymed_symbol_4 = Nil;
    class_description = ISVREF(gensymed_symbol_3,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    gensymed_symbol_4 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(gensymed_symbol_4,(SI_Long)8L)) {
	gensymed_symbol_5 = get_slot_description_value(gensymed_symbol_3,
		gensymed_symbol_4);
	if (SIMPLE_VECTOR_P(gensymed_symbol_5) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_5)) > 
		(SI_Long)2L &&  !EQ(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gensymed_symbol_5,(SI_Long)1L);
	    gensymed_symbol_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_4 = Nil;
	if (gensymed_symbol_4 && ISVREF(gensymed_symbol_4,(SI_Long)16L)) {
	    gensymed_symbol_4 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(gensymed_symbol_5,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_6 = this_frame_is_not_activatable_qm;
	    inline_funcall_2(gensymed_symbol_4,gensymed_symbol_5,
		    gensymed_symbol_6);
	}
    }
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qentity;             /* entity */

/* ACTIVATE-FOR-ENTITY */
Object activate_for_entity(entity)
    Object entity;
{
    Object frame, sub_vector_qm, method_function_qm, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;

    x_note_fn_call(181,23);
    if ( !((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & (SI_Long)1L))) {
	frame = entity;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qentity)) {
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
	if ( !TRUEP(In_suspend_resume_p)) {
	    method_index = (SI_Long)14L;
	    frame = entity;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		return VALUES_1(inline_funcall_1(function_qm,frame));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-ENTITY */
Object deactivate_for_entity(entity)
    Object entity;
{
    Object frame, sub_vector_qm, method_function_qm, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;

    x_note_fn_call(181,24);
    if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & (SI_Long)1L)) {
	if ( !TRUEP(In_suspend_resume_p))
	    decache_connection_roles(entity);
	frame = entity;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)7L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qentity)) {
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
	if ( !TRUEP(In_suspend_resume_p)) {
	    method_index = (SI_Long)13L;
	    frame = entity;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		return VALUES_1(inline_funcall_1(function_qm,frame));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qreclaim_frame_serial_number;  /* reclaim-frame-serial-number */

static Object Qschedule_initial_rules_from_activated_kb_workspace;  /* schedule-initial-rules-from-activated-kb-workspace */

/* ACTIVATE-FOR-KB-WORKSPACE */
Object activate_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;
    Object sub_class_bit_vector, gensymed_symbol_4, gensymed_symbol_5;
    Object ab_loop_it_, structure_being_reclaimed, temp_1, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q, frame, sub_vector_qm, method_function_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, index_1;
    SI_Long ab_loop_bind_;
    char temp, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(181,25);
    if ( !TRUEP(In_suspend_resume_p)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & 
		(SI_Long)1L))) {
	    if (Warmbooting_qm) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,
			(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		ab_queue_form_ = gensymed_symbol;
		ab_next_queue_element_ = Nil;
		block = Nil;
		if (ab_queue_form_)
		    ab_next_queue_element_ = 
			    constant_queue_next(ISVREF(ab_queue_form_,
			    (SI_Long)2L),ab_queue_form_);
	      next_loop:
		if ( !TRUEP(ab_next_queue_element_))
		    goto end_loop;
		block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		ab_next_queue_element_ = 
			constant_queue_next(ab_next_queue_element_,
			ab_queue_form_);
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		if (((temp ? (SI_Long)0L != (IFIX(ISVREF(block,
			(SI_Long)4L)) & (SI_Long)2048L) : TRUEP(Nil)) ? 
			(SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			(SI_Long)1L) : TRUEP(Nil)) ?  !((SI_Long)0L != 
			(IFIX(ISVREF(block,(SI_Long)4L)) & 
			(SI_Long)16777216L)) : TRUEP(Nil)) {
		    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
			    (SI_Long)1L);
		    gensymed_symbol_4 = block;
		    gensymed_symbol_5 = Nil;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		goto next_loop;
	      end_loop:;
	    }
	    else {
		gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,
			(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		ab_queue_form_ = gensymed_symbol;
		ab_next_queue_element_ = Nil;
		block = Nil;
		ab_loop_it_ = Nil;
		if (ab_queue_form_)
		    ab_next_queue_element_ = 
			    constant_queue_next(ISVREF(ab_queue_form_,
			    (SI_Long)2L),ab_queue_form_);
	      next_loop_1:
		if ( !TRUEP(ab_next_queue_element_))
		    goto end_loop_1;
		block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		ab_next_queue_element_ = 
			constant_queue_next(ab_next_queue_element_,
			ab_queue_form_);
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		ab_loop_it_ = (temp ? (SI_Long)0L != (IFIX(ISVREF(block,
			(SI_Long)4L)) & (SI_Long)2048L) : TRUEP(Nil)) ? 
			((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			(SI_Long)1L) ? T : Nil) : Nil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop_1;
	      end_loop_1:
		temp = TRUEP(Qnil);
	      end_1:;
		if (temp) {
		    if (Nil) {
			if (EQ(Nil,Current_schedule_task))
			    Current_schedule_task = Nil;
			if (ISVREF(Nil,(SI_Long)6L))
			    cancel_and_reclaim_scheduled_queue_element_1(Nil);
			inline_note_reclaim_cons(Nil,Nil);
			structure_being_reclaimed = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
			  SVREF(Nil,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_1 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(Nil,FIX((SI_Long)0L)) = temp_1;
			temp_1 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    def_structure_schedule_task_variable = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    if (def_structure_schedule_task_variable) {
			temp_1 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = 
				ISVREF(def_structure_schedule_task_variable,
				(SI_Long)0L);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			SVREF(def_structure_schedule_task_variable,
				FIX((SI_Long)0L)) = 
				Qg2_defstruct_structure_name_schedule_task_g2_struct;
		    }
		    else
			def_structure_schedule_task_variable = 
				make_permanent_schedule_task_structure_internal();
		    inline_note_allocate_cons(def_structure_schedule_task_variable,
			    Nil);
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)2L)) = T;
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)9L)) = Nil;
		    task = def_structure_schedule_task_variable;
		    temp_1 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = -1.0;
		    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
		    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
		    SVREF(task,FIX((SI_Long)5L)) = Nil;
		    temp_1 = gensym_list_2(Nil,Qreclaim_frame_serial_number);
		    SVREF(task,FIX((SI_Long)9L)) = temp_1;
		    SVREF(task,FIX((SI_Long)10L)) = Nil;
		    g2_p =  !TRUEP(Nil);
		    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		    temp_1 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
			    Current_g2_time : Current_real_time,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		    SVREF(task,FIX((SI_Long)7L)) = 
			    Qschedule_initial_rules_from_activated_kb_workspace;
		    temp_1 = 
			    SYMBOL_FUNCTION(Qschedule_initial_rules_from_activated_kb_workspace);
		    SVREF(task,FIX((SI_Long)8L)) = temp_1;
		    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
		    SVREF(task,FIX((SI_Long)13L)) = kb_workspace;
		    temp_1 = copy_frame_serial_number(ISVREF(kb_workspace,
			    (SI_Long)3L));
		    SVREF(task,FIX((SI_Long)14L)) = temp_1;
		    temp_1 = Window_instigating_this_rule_instance_qm;
		    SVREF(task,FIX((SI_Long)15L)) = temp_1;
		    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		    if (ctask);
		    else
			ctask = System_is_running;
		    p = ISVREF(task,(SI_Long)4L);
		    v = ctask ? Current_task_queue_vector : 
			    Deferred_task_queue_vector;
		    q = ISVREF(v,IFIX(p));
		    SVREF(task,FIX((SI_Long)11L)) = q;
		    temp_1 = constant_queue_push_right(q,task);
		    SVREF(task,FIX((SI_Long)6L)) = temp_1;
		    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
			Priority_of_next_task = p;
		}
		else
		    schedule_scanned_rules(kb_workspace);
	    }
	}
	frame = kb_workspace;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
	    method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	    goto end_2;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop_2;
      end_loop_2:
	method_function_qm = Qnil;
      end_2:;
	if (method_function_qm)
	    return inline_funcall_1(method_function_qm,frame);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinitializing;       /* initializing */

/* SCHEDULE-INITIAL-RULES-FROM-ACTIVATED-KB-WORKSPACE */
Object schedule_initial_rules_from_activated_kb_workspace(workspace,
	    frame_serial_number,instigating_window_qm)
    Object workspace, frame_serial_number, instigating_window_qm;
{
    Object gensymed_symbol, xa, ya, window_instigating_this_rule_instance_qm;
    Object ab_queue_form_, ab_next_queue_element_, block, sub_class_bit_vector;
    Object incff_1_arg;
    SI_Long new_rule_count, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(181,26);
    gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	new_rule_count = (SI_Long)0L;
	window_instigating_this_rule_instance_qm = instigating_window_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Window_instigating_this_rule_instance_qm,Qwindow_instigating_this_rule_instance_qm,window_instigating_this_rule_instance_qm,
		0);
	  gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	  ab_queue_form_ = gensymed_symbol;
	  ab_next_queue_element_ = Nil;
	  block = Nil;
	  if (ab_queue_form_)
	      ab_next_queue_element_ = 
		      constant_queue_next(ISVREF(ab_queue_form_,
		      (SI_Long)2L),ab_queue_form_);
	next_loop:
	  if ( !TRUEP(ab_next_queue_element_))
	      goto end_loop;
	  block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	  ab_next_queue_element_ = 
		  constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	  sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	  if (((temp ? (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		  (SI_Long)2048L) : TRUEP(Nil)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)1L) : 
		  TRUEP(Nil)) ?  !((SI_Long)0L != (IFIX(ISVREF(block,
		  (SI_Long)4L)) & (SI_Long)16777216L)) : TRUEP(Nil)) {
	      incff_1_arg = generate_and_schedule_rule_instances(block,Nil,
		      Nil,Nil,Qinitializing,Nil,ISVREF(block,(SI_Long)26L),
		      Nil);
	      new_rule_count = new_rule_count + IFIX(incff_1_arg);
	  }
	  goto next_loop;
	end_loop:
	  if (new_rule_count == (SI_Long)0L)
	      schedule_scanned_rules(workspace);
	  else
	      ISVREF(workspace,(SI_Long)28L) = FIX(new_rule_count);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qcomplete_initial_rules;  /* complete-initial-rules */

/* HANDLE-COMPLETION-OF-INITIAL-RULE */
Object handle_completion_of_initial_rule(rule_instance)
    Object rule_instance;
{
    Object block, kb_workspace_qm, residue, structure_being_reclaimed, temp;
    Object svref_arg_2, def_structure_schedule_task_variable, svref_new_value;
    Object task, ctask, p, v, q;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(181,27);
    block = ISVREF(rule_instance,(SI_Long)8L);
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
	    (SI_Long)16777216L))) {
	kb_workspace_qm = ISVREF(rule_instance,(SI_Long)25L);
	if (kb_workspace_qm) {
	    residue = FIXNUM_SUB1(ISVREF(kb_workspace_qm,(SI_Long)28L));
	    ISVREF(kb_workspace_qm,(SI_Long)28L) = residue;
	    if (IFIX(residue) == (SI_Long)0L) {
		if (Nil) {
		    if (EQ(Nil,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(Nil,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(Nil);
		    inline_note_reclaim_cons(Nil,Nil);
		    structure_being_reclaimed = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(Nil,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_schedule_task_g2_struct;
		}
		else
		    def_structure_schedule_task_variable = 
			    make_permanent_schedule_task_structure_internal();
		inline_note_allocate_cons(def_structure_schedule_task_variable,
			Nil);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = T;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
		ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		g2_p =  !TRUEP(Nil);
		SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
			Current_real_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		SVREF(task,FIX((SI_Long)7L)) = Qcomplete_initial_rules;
		temp = SYMBOL_FUNCTION(Qcomplete_initial_rules);
		SVREF(task,FIX((SI_Long)8L)) = temp;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)13L)) = kb_workspace_qm;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp;
		if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		    Priority_of_next_task = p;
	    }
	}
    }
    return VALUES_1(Nil);
}

/* COMPLETE-INITIAL-RULES */
Object complete_initial_rules(kb_workspace)
    Object kb_workspace;
{
    x_note_fn_call(181,28);
    deactivate_initial_rules(kb_workspace);
    schedule_scanned_rules(kb_workspace);
    return VALUES_1(Nil);
}

static Object Qinvoke_rule_universally;  /* invoke-rule-universally */

/* SCHEDULE-SCANNED-RULES */
Object schedule_scanned_rules(kb_workspace)
    Object kb_workspace;
{
    Object distribution_list, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, block, sub_class_bit_vector, scan_interval;
    Object sublist, temp_1, floored_scan_interval, rules, ab_loop_list_;
    Object how_many, ab_loop_desetq_, rule, ab_loop_list__1;
    Object ab_loop_iter_flag_, old, new_1;
    Object def_structure_schedule_task_variable, svref_arg_2, svref_new_value;
    Object task, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, k, temp_3;
    char temp, svref_new_value_1;
    double temp_2, aref_new_value;
    Declare_special(1);

    x_note_fn_call(181,29);
    distribution_list = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
    if (temp ? (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) {
	scan_interval = ISVREF(block,(SI_Long)20L);
	if (scan_interval) {
	    gensymed_symbol_1 = FIXNUMP(scan_interval) ? 
		    IFIX(scan_interval) : 
		    inline_floor_1(DFLOAT_ISAREF_1(scan_interval,(SI_Long)0L));
	    gensymed_symbol_2 = (SI_Long)1L;
	    scan_interval = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
	    sublist = assq_function(scan_interval,distribution_list);
	    if (sublist) {
		temp_1 = gensym_cons_1(block,CDR(sublist));
		M_CDR(sublist) = temp_1;
	    }
	    else
		distribution_list = 
			gensym_cons_1(gensym_list_2(scan_interval,block),
			distribution_list);
	}
    }
    goto next_loop;
  end_loop:
    floored_scan_interval = Nil;
    rules = Nil;
    ab_loop_list_ = distribution_list;
    how_many = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    floored_scan_interval = CAR(ab_loop_desetq_);
    rules = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    how_many = length(rules);
    rule = Nil;
    ab_loop_list__1 = rules;
    scan_interval = Nil;
    k = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    rule = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    scan_interval = ISVREF(rule,(SI_Long)20L);
    if ( !TRUEP(ab_loop_iter_flag_))
	k = k + (SI_Long)1L;
    old = Nil;
    new_1 = Nil;
  next_loop_3:
    old = ISVREF(rule,(SI_Long)21L);
    def_structure_schedule_task_variable = 
	    ISVREF(Chain_of_available_schedule_tasks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_schedule_task_variable) {
	temp_1 = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_schedule_task_variable,
		(SI_Long)0L);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
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
    temp_1 = ISVREF(task,(SI_Long)1L);
    temp_2 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
    temp_3 = k * IFIX(floored_scan_interval) / IFIX(how_many);
    aref_new_value = temp_2 + (double)temp_3;
    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
    temp_1 = ISVREF(task,(SI_Long)1L);
    aref_new_value = FIXNUMP(scan_interval) ? (double)IFIX(scan_interval) :
	     DFLOAT_ISAREF_1(scan_interval,(SI_Long)0L);
    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
    svref_new_value_1 =  !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) 
	    & (SI_Long)16777216L));
    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
    temp_1 = ISVREF(rule,(SI_Long)26L);
    SVREF(task,FIX((SI_Long)4L)) = temp_1;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = Nil;
    SVREF(task,FIX((SI_Long)7L)) = Qinvoke_rule_universally;
    temp_1 = SYMBOL_FUNCTION(Qinvoke_rule_universally);
    SVREF(task,FIX((SI_Long)8L)) = temp_1;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)13L)) = rule;
    new_1 = task;
    if (CAS_SVREF(rule,(SI_Long)21L,old,new_1)) {
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(old,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = old;
	}
	future_task_schedule_2(new_1);
	goto end_1;
    }
    else {
	inline_note_reclaim_cons(new_1,Nil);
	structure_being_reclaimed = new_1;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
	temp_1 = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = new_1;
    }
    goto next_loop_3;
  end_loop_3:
  end_1:;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_2;
  end_loop_2:;
    goto next_loop_1;
  end_loop_1:;
    reclaim_gensym_tree_1(distribution_list);
    return VALUES_1(Qnil);
}

/* DEACTIVATE-INITIAL-RULES */
Object deactivate_initial_rules(kb_workspace)
    Object kb_workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(181,30);
    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)2048L) 
	    && (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1L) &&  !((SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)4L)) & (SI_Long)16777216L))) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_1 = block;
	gensymed_symbol_2 = Nil;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DEACTIVATE-FOR-KB-WORKSPACE */
Object deactivate_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(181,31);
    frame = kb_workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
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
    return VALUES_1(Nil);
}

/* SCHEDULE-ALL-CYCLIC-RULES */
Object schedule_all_cyclic_rules()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ws, gensymed_symbol;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(181,32);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ws = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qkb_workspace);
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
      ws = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(ws,(SI_Long)5L)) & (SI_Long)1L)) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  temp =  !TRUEP(gensymed_symbol);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  schedule_all_cyclic_rules_1(ws);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SCHEDULE-ALL-CYCLIC-RULES-1 */
Object schedule_all_cyclic_rules_1(kb_workspace)
    Object kb_workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object subworkspace_qm, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(181,33);
    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    subworkspace_qm = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    if ((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & (SI_Long)1L)) {
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	temp_1 = ISVREF(subblock,(SI_Long)18L);
	subworkspace_qm = CAR(temp_1);
    }
    else
	subworkspace_qm = Nil;
    if (subworkspace_qm && (SI_Long)0L != (IFIX(ISVREF(subworkspace_qm,
	    (SI_Long)5L)) & (SI_Long)1L))
	schedule_all_cyclic_rules_1(subworkspace_qm);
    goto next_loop;
  end_loop:;
    return schedule_scanned_rules(kb_workspace);
}

void activate_INIT()
{
    Object temp, temp_1;
    Object Qclasses_which_define, Qdeactivate, Qdeactivate_for_kb_workspace;
    Object AB_package, Qactivate, Qactivate_for_kb_workspace;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qdeactivate_for_entity;
    Object Qactivate_for_entity, Qdeactivate_and_propagate;
    Object Qdeactivate_and_propagate_for_entity;
    Object Qactivate_if_possible_and_propagate;
    Object Qactivate_if_possible_and_propagate_for_entity;
    Object Qdeactivate_and_propagate_for_kb_workspace;
    Object Qactivate_if_possible_and_propagate_for_kb_workspace;
    Object Qdeactivate_and_propagate_for_kb_frame;
    Object Qactivate_if_possible_and_propagate_for_kb_frame;
    Object Qclean_up_items_needing_initialization, list_constant_4;
    Object Qmake_items_needing_initialization_tree_function, Kfuncall;
    Object Qmanually_enable, Qmanually_enable_for_kb_frame, Qmanually_disable;
    Object Qmanually_disable_for_kb_frame, Qnote_ancestor_manually_enabled;
    Object Qnote_ancestor_manually_enabled_for_kb_workspace;
    Object Qnote_ancestor_manually_enabled_for_kb_frame;
    Object Qgeneric_method_lambda_list, list_constant, list_constant_3;
    Object Qnote_ancestor_not_activatable, list_constant_2;
    Object Qdeactivate_subclass_of_entity, Qactivate_subclass_of_entity;
    Object list_constant_1, Qancestor_not_ok_qm;

    x_note_fn_call(181,34);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    list_constant = STATIC_CONS(Qkb_frame,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qactivate,list_constant,
	    Qgeneric_method_lambda_list);
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    mutate_global_property(Qdeactivate,list_constant,
	    Qgeneric_method_lambda_list);
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    mutate_global_property(Qmanually_disable,list_constant,
	    Qgeneric_method_lambda_list);
    Qmanually_enable = STATIC_SYMBOL("MANUALLY-ENABLE",AB_package);
    mutate_global_property(Qmanually_enable,list_constant,
	    Qgeneric_method_lambda_list);
    Qactivate_if_possible_and_propagate = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE",AB_package);
    mutate_global_property(Qactivate_if_possible_and_propagate,
	    list_constant,Qgeneric_method_lambda_list);
    Qdeactivate_and_propagate = STATIC_SYMBOL("DEACTIVATE-AND-PROPAGATE",
	    AB_package);
    Qancestor_not_ok_qm = STATIC_SYMBOL("ANCESTOR-NOT-OK\?",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qkb_frame,Qancestor_not_ok_qm);
    mutate_global_property(Qdeactivate_and_propagate,list_constant_1,
	    Qgeneric_method_lambda_list);
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    list_constant_2 = STATIC_CONS(Qblock,Qnil);
    mutate_global_property(Qactivate_subclass_of_entity,list_constant_2,
	    Qgeneric_method_lambda_list);
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    mutate_global_property(Qdeactivate_subclass_of_entity,list_constant_2,
	    Qgeneric_method_lambda_list);
    Qnote_ancestor_not_activatable = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-NOT-ACTIVATABLE",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_3 = STATIC_CONS(Qentity,Qnil);
    mutate_global_property(Qnote_ancestor_not_activatable,list_constant_3,
	    Qgeneric_method_lambda_list);
    Qnote_ancestor_manually_enabled = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED",AB_package);
    mutate_global_property(Qnote_ancestor_manually_enabled,list_constant,
	    Qgeneric_method_lambda_list);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnote_ancestor_manually_enabled_for_kb_frame = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-KB-FRAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_kb_frame,
	    STATIC_FUNCTION(note_ancestor_manually_enabled_for_kb_frame,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_kb_frame);
    set_get(Qkb_frame,Qnote_ancestor_manually_enabled,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_ancestor_manually_enabled),
	    Qclasses_which_define);
    temp = CONS(Qkb_frame,temp_1);
    mutate_global_property(Qnote_ancestor_manually_enabled,temp,
	    Qclasses_which_define);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qnote_ancestor_manually_enabled_for_kb_workspace = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_kb_workspace,
	    STATIC_FUNCTION(note_ancestor_manually_enabled_for_kb_workspace,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_kb_workspace);
    set_get(Qkb_workspace,Qnote_ancestor_manually_enabled,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_ancestor_manually_enabled),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qnote_ancestor_manually_enabled,temp,
	    Qclasses_which_define);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qin_suspend_resume_p = STATIC_SYMBOL("IN-SUSPEND-RESUME-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qin_suspend_resume_p,In_suspend_resume_p);
    record_system_variable(Qin_suspend_resume_p,Qactivate,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qexistence_classes_already_checked = 
	    STATIC_SYMBOL("EXISTENCE-CLASSES-ALREADY-CHECKED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexistence_classes_already_checked,
	    Existence_classes_already_checked);
    record_system_variable(Qexistence_classes_already_checked,Qactivate,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qmanually_disabled_qm = STATIC_SYMBOL("MANUALLY-DISABLED\?",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qis_disabled = STATIC_SYMBOL("IS-DISABLED",AB_package);
    Qmanually_disable_for_kb_frame = 
	    STATIC_SYMBOL("MANUALLY-DISABLE-FOR-KB-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_disable_for_kb_frame,
	    STATIC_FUNCTION(manually_disable_for_kb_frame,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qmanually_disable_for_kb_frame);
    set_get(Qkb_frame,Qmanually_disable,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_disable),
	    Qclasses_which_define);
    temp = CONS(Qkb_frame,temp_1);
    mutate_global_property(Qmanually_disable,temp,Qclasses_which_define);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qis_enabled = STATIC_SYMBOL("IS-ENABLED",AB_package);
    Qmanually_enable_for_kb_frame = 
	    STATIC_SYMBOL("MANUALLY-ENABLE-FOR-KB-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_enable_for_kb_frame,
	    STATIC_FUNCTION(manually_enable_for_kb_frame,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qmanually_enable_for_kb_frame);
    set_get(Qkb_frame,Qmanually_enable,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_enable),
	    Qclasses_which_define);
    temp = CONS(Qkb_frame,temp_1);
    mutate_global_property(Qmanually_enable,temp,Qclasses_which_define);
    Qitems_needing_initialization = 
	    STATIC_SYMBOL("ITEMS-NEEDING-INITIALIZATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitems_needing_initialization,
	    Items_needing_initialization);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qitems_needing_initialization_tree = 
	    STATIC_SYMBOL("ITEMS-NEEDING-INITIALIZATION-TREE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitems_needing_initialization_tree,
	    Items_needing_initialization_tree);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_items_needing_initialization_tree_function = 
	    STATIC_SYMBOL("MAKE-ITEMS-NEEDING-INITIALIZATION-TREE-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_items_needing_initialization_tree_function,
	    STATIC_FUNCTION(make_items_needing_initialization_tree_function,
	    NIL,FALSE,0,0));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_items_needing_initialization_tree_function);
    record_system_variable(Qitems_needing_initialization_tree,Qactivate,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    record_system_variable(Qitems_needing_initialization,Qactivate,T,Qnil,
	    Qnil,Qnil,Qnil);
    if (Initializing_items_needing_initialization == UNBOUND)
	Initializing_items_needing_initialization = Nil;
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    Qg2_defstruct_structure_name_data_server_g2_struct = 
	    STATIC_SYMBOL("DATA-SERVER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant = 
	    STATIC_STRING("Cannot conclude initial value for ~NF: ~a");
    Qclean_up_items_needing_initialization = 
	    STATIC_SYMBOL("CLEAN-UP-ITEMS-NEEDING-INITIALIZATION",AB_package);
    SET_SYMBOL_FUNCTION(Qclean_up_items_needing_initialization,
	    STATIC_FUNCTION(clean_up_items_needing_initialization,NIL,
	    FALSE,0,0));
    def_bombout_clean_up_function(Qclean_up_items_needing_initialization);
    Qitem_active = STATIC_SYMBOL("ITEM-ACTIVE",AB_package);
    Qis_activated = STATIC_SYMBOL("IS-ACTIVATED",AB_package);
    Qactivate_if_possible_and_propagate_for_kb_frame = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-KB-FRAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_kb_frame,
	    STATIC_FUNCTION(activate_if_possible_and_propagate_for_kb_frame,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_kb_frame);
    set_get(Qkb_frame,Qactivate_if_possible_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_if_possible_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qkb_frame,temp_1);
    mutate_global_property(Qactivate_if_possible_and_propagate,temp,
	    Qclasses_which_define);
    Qis_deactivated = STATIC_SYMBOL("IS-DEACTIVATED",AB_package);
    Qdeactivate_and_propagate_for_kb_frame = 
	    STATIC_SYMBOL("DEACTIVATE-AND-PROPAGATE-FOR-KB-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_kb_frame,
	    STATIC_FUNCTION(deactivate_and_propagate_for_kb_frame,NIL,
	    FALSE,2,2));
    temp = SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_kb_frame);
    set_get(Qkb_frame,Qdeactivate_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qkb_frame,temp_1);
    mutate_global_property(Qdeactivate_and_propagate,temp,
	    Qclasses_which_define);
    Qactivate_if_possible_and_propagate_for_kb_workspace = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_kb_workspace,
	    STATIC_FUNCTION(activate_if_possible_and_propagate_for_kb_workspace,
	    NIL,FALSE,1,1));
    temp = 
	    SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_kb_workspace);
    set_get(Qkb_workspace,Qactivate_if_possible_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_if_possible_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qactivate_if_possible_and_propagate,temp,
	    Qclasses_which_define);
    Qdeactivate_and_propagate_for_kb_workspace = 
	    STATIC_SYMBOL("DEACTIVATE-AND-PROPAGATE-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_kb_workspace,
	    STATIC_FUNCTION(deactivate_and_propagate_for_kb_workspace,NIL,
	    FALSE,2,2));
    temp = SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_kb_workspace);
    set_get(Qkb_workspace,Qdeactivate_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qdeactivate_and_propagate,temp,
	    Qclasses_which_define);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qactivate_if_possible_and_propagate_for_entity = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-ENTITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_entity,
	    STATIC_FUNCTION(activate_if_possible_and_propagate_for_entity,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_entity);
    set_get(Qentity,Qactivate_if_possible_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_if_possible_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qactivate_if_possible_and_propagate,temp,
	    Qclasses_which_define);
    Qdeactivate_and_propagate_for_entity = 
	    STATIC_SYMBOL("DEACTIVATE-AND-PROPAGATE-FOR-ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_entity,
	    STATIC_FUNCTION(deactivate_and_propagate_for_entity,NIL,FALSE,
	    2,2));
    temp = SYMBOL_FUNCTION(Qdeactivate_and_propagate_for_entity);
    set_get(Qentity,Qdeactivate_and_propagate,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_and_propagate),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qdeactivate_and_propagate,temp,
	    Qclasses_which_define);
    Qactivate_for_entity = STATIC_SYMBOL("ACTIVATE-FOR-ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_entity,
	    STATIC_FUNCTION(activate_for_entity,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qactivate_for_entity);
    set_get(Qentity,Qactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qactivate,temp,Qclasses_which_define);
    Qdeactivate_for_entity = STATIC_SYMBOL("DEACTIVATE-FOR-ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_entity,
	    STATIC_FUNCTION(deactivate_for_entity,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qdeactivate_for_entity);
    set_get(Qentity,Qdeactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qdeactivate,temp,Qclasses_which_define);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    Qschedule_initial_rules_from_activated_kb_workspace = 
	    STATIC_SYMBOL("SCHEDULE-INITIAL-RULES-FROM-ACTIVATED-KB-WORKSPACE",
	    AB_package);
    Qactivate_for_kb_workspace = STATIC_SYMBOL("ACTIVATE-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_kb_workspace,
	    STATIC_FUNCTION(activate_for_kb_workspace,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qactivate_for_kb_workspace);
    set_get(Qkb_workspace,Qactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qactivate,temp,Qclasses_which_define);
    Qinitializing = STATIC_SYMBOL("INITIALIZING",AB_package);
    SET_SYMBOL_FUNCTION(Qschedule_initial_rules_from_activated_kb_workspace,
	    STATIC_FUNCTION(schedule_initial_rules_from_activated_kb_workspace,
	    NIL,FALSE,3,3));
    Qcomplete_initial_rules = STATIC_SYMBOL("COMPLETE-INITIAL-RULES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcomplete_initial_rules,
	    STATIC_FUNCTION(complete_initial_rules,NIL,FALSE,1,1));
    Qinvoke_rule_universally = STATIC_SYMBOL("INVOKE-RULE-UNIVERSALLY",
	    AB_package);
    Qdeactivate_for_kb_workspace = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-KB-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_kb_workspace,
	    STATIC_FUNCTION(deactivate_for_kb_workspace,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qdeactivate_for_kb_workspace);
    set_get(Qkb_workspace,Qdeactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qdeactivate,temp,Qclasses_which_define);
}
