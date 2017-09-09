/* sqncs3.c
 * Input file:  sequences3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sqncs3.h"


DEFINE_VARIABLE_WITH_SYMBOL(Package_preparation_mode, Qpackage_preparation_mode);

static Object Qpackage_preparation_mode_changed;  /* package-preparation-mode-changed */

/* SET-PACKAGE-PREPARATION-MODE */
Object set_package_preparation_mode(new_state)
    Object new_state;
{
    Object temp;

    x_note_fn_call(108,0);
    Package_preparation_mode = new_state;
    temp = 
	    inform_ui_client_interfaces_of_general_update(Qpackage_preparation_mode_changed,
	    new_state ? Evaluation_true_value : Evaluation_false_value);
    return VALUES_1(temp);
}

static Object string_constant;     /* "Entering Package Preparation mode.  To exit this mode, select ~
				    *                 \"Leave Package Preparation Mode\" from the Main Menu ~
				    *                 Miscellany menu."
				    */

/* ENTER-PACKAGE-PREPARATION-MODE */
Object enter_package_preparation_mode()
{
    x_note_fn_call(108,1);
    notify_user(1,string_constant);
    return set_package_preparation_mode(T);
}

static Object string_constant_1;   /* "Leaving Package Preparation mode." */

/* LEAVE-PACKAGE-PREPARATION-MODE */
Object leave_package_preparation_mode()
{
    x_note_fn_call(108,2);
    notify_user(1,string_constant_1);
    return set_package_preparation_mode(Nil);
}

static Object list_constant;       /* # */

/* STRIP-CHOICE-OBTAINS-P */
Object strip_choice_obtains_p(kb_frame,choice_symbol)
    Object kb_frame, choice_symbol;
{
    Object stripping_inherited_p_1, temp, pattern, c1, c2, c3, d1, d2, d3;
    char strip_text_p, do_not_strip_text_p;

    x_note_fn_call(108,3);
    if (Package_preparation_mode && ISVREF(ISVREF(kb_frame,(SI_Long)1L),
	    (SI_Long)16L)) {
	stripping_inherited_p_1 = stripping_inherited_p(kb_frame);
	strip_text_p = (SI_Long)0L != (IFIX(ISVREF(kb_frame,(SI_Long)4L)) 
		& (SI_Long)2097152L);
	do_not_strip_text_p = (SI_Long)0L != (IFIX(ISVREF(kb_frame,
		(SI_Long)4L)) & (SI_Long)4194304L);
	temp = assq_function(choice_symbol,list_constant);
	pattern = CDR(temp);
	c1 = FIRST(pattern);
	c2 = SECOND(pattern);
	c3 = THIRD(pattern);
	d1 = FOURTH(pattern);
	d2 = FIFTH(pattern);
	d3 = SIXTH(pattern);
	temp = g2_equiv(IFIX(c1) == (SI_Long)1L ? T : Nil,
		stripping_inherited_p_1) && g2_equiv(IFIX(c2) == 
		(SI_Long)1L ? T : Nil,strip_text_p ? T : Nil) ? 
		g2_equiv(IFIX(c3) == (SI_Long)1L ? T : Nil,
		do_not_strip_text_p ? T : Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if (d1 && g2_equiv(IFIX(d1) == (SI_Long)1L ? T : Nil,
		stripping_inherited_p_1) && g2_equiv(IFIX(d2) == 
		(SI_Long)1L ? T : Nil,strip_text_p ? T : Nil))
	    return g2_equiv(IFIX(d3) == (SI_Long)1L ? T : Nil,
		    do_not_strip_text_p ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qframe_flags;        /* frame-flags */

static Object Qstrip_text_mark;    /* strip-text-mark */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qdo_not_strip_text_mark;  /* do-not-strip-text-mark */

/* SET-STRIPPING-FLAGS-AS-SPECIFIED */
Object set_stripping_flags_as_specified(item,r1,r2)
    Object item, r1, r2;
{
    SI_Long svref_new_value;
    char old_strip_text_mark, old_do_not_strip_text_mark;

    x_note_fn_call(108,4);
    old_strip_text_mark = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)2097152L);
    old_do_not_strip_text_mark = (SI_Long)0L != (IFIX(ISVREF(item,
	    (SI_Long)4L)) & (SI_Long)4194304L);
    if (IFIX(r1) == (SI_Long)1L) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qframe_flags);
	svref_new_value = IFIX(ISVREF(item,(SI_Long)4L)) | (SI_Long)2097152L;
	ISVREF(item,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qframe_flags);
	svref_new_value = IFIX(ISVREF(item,(SI_Long)4L)) &  ~(SI_Long)2097152L;
	ISVREF(item,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (IFIX(r2) == (SI_Long)1L) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qframe_flags);
	svref_new_value = IFIX(ISVREF(item,(SI_Long)4L)) | (SI_Long)4194304L;
	ISVREF(item,(SI_Long)4L) = FIX(svref_new_value);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qframe_flags);
	svref_new_value = IFIX(ISVREF(item,(SI_Long)4L)) &  ~(SI_Long)4194304L;
	ISVREF(item,(SI_Long)4L) = FIX(svref_new_value);
    }
    if ( !EQ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)2097152L) ? T : Nil,old_strip_text_mark ? T : Nil))
	update_subscriptions_from_virtual_attribute_change(item,
		get_property_value_function(3,
		get_symbol_properties_function(Qstrip_text_mark),
		Qvirtual_attribute,Nil),Nil);
    if ( !EQ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)4194304L) ? T : Nil,old_do_not_strip_text_mark ? T : Nil))
	return update_subscriptions_from_virtual_attribute_change(item,
		get_property_value_function(3,
		get_symbol_properties_function(Qdo_not_strip_text_mark),
		Qvirtual_attribute,Nil),Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_2;   /* "You cannot strip texts while the system is running.  ~
				    *         No texts were stripped."
				    */

static Object string_constant_3;   /* "Stripping texts now!" */

static Object Qkb_workspace;       /* kb-workspace */

static Object string_constant_4;   /* "Finished stripping texts." */

/* STRIP-ALL-TEXTS */
Object strip_all_texts()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(108,5);
    if (System_is_running)
	return notify_user(1,string_constant_2);
    else {
	notify_user(1,string_constant_3);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	block = Nil;
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
	  block = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  if ( !TRUEP(gensymed_symbol) ?  !TRUEP(ISVREF(block,
		  (SI_Long)18L)) : TRUEP(Nil)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),(SI_Long)1L);
	      gensymed_symbol_1 = block;
	      gensymed_symbol_2 = Nil;
	      inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2);
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	return notify_user(1,string_constant_4);
    }
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsimulation_details;  /* simulation-details */

/* STRIP-TEXT-FOR-BLOCK */
Object strip_text_for_block(block,stripping_inherited_qm)
    Object block, stripping_inherited_qm;
{
    Object strip_item_qm, gensymed_symbol, gensymed_symbol_1;
    Object class_description, ab_loop_list_, gensymed_symbol_2, x2;
    Object gensymed_symbol_3, sub_class_bit_vector, temp_1, subworkspace_qm;
    Object ab_queue_form_, ab_next_queue_element_, subblock, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object connection_frame_or_class, ab_less_than_branch_qm_;
    Object simulation_details;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    char old_strip_text_mark_qm, old_do_not_strip_text_mark_qm, temp;
    Declare_special(1);

    x_note_fn_call(108,6);
    old_strip_text_mark_qm = (SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)4L)) & (SI_Long)2097152L);
    old_do_not_strip_text_mark_qm = (SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)4L)) & (SI_Long)4194304L);
    strip_item_qm = old_strip_text_mark_qm ? T : Nil;
    if (strip_item_qm);
    else
	strip_item_qm = stripping_inherited_qm ? ( !((SI_Long)0L != 
		(IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)4194304L)) ? T 
		: Nil) : Qnil;
    if (strip_item_qm)
	strip_texts_from_item(block);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qframe_flags);
    svref_new_value = IFIX(ISVREF(block,(SI_Long)4L)) &  ~(SI_Long)2097152L;
    ISVREF(block,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qframe_flags);
    svref_new_value = IFIX(ISVREF(block,(SI_Long)4L)) &  ~(SI_Long)4194304L;
    ISVREF(block,(SI_Long)4L) = FIX(svref_new_value);
    if ( !EQ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
	    (SI_Long)2097152L) ? T : Nil,old_strip_text_mark_qm ? T : Nil))
	update_subscriptions_from_virtual_attribute_change(block,
		get_property_value_function(3,
		get_symbol_properties_function(Qstrip_text_mark),
		Qvirtual_attribute,Nil),Nil);
    if ( !EQ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
	    (SI_Long)4194304L) ? T : Nil,old_do_not_strip_text_mark_qm ? T 
	    : Nil))
	update_subscriptions_from_virtual_attribute_change(block,
		get_property_value_function(3,
		get_symbol_properties_function(Qdo_not_strip_text_mark),
		Qvirtual_attribute,Nil),Nil);
    gensymed_symbol = block;
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
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),(SI_Long)1L);
	    gensymed_symbol_3 = strip_item_qm;
	    inline_funcall_2(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	}
    }
    goto next_loop;
  end_loop:;
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_4 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_5 = (SI_Long)1L;
	gensymed_symbol_6 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_5 = gensymed_symbol_5 << gensymed_symbol_6;
	gensymed_symbol_4 = gensymed_symbol_4 & gensymed_symbol_5;
	temp = (SI_Long)0L < gensymed_symbol_4;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(block,(SI_Long)18L);
	subworkspace_qm = CAR(temp_1);
	if (subworkspace_qm) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subworkspace_qm,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),(SI_Long)1L);
	    gensymed_symbol_1 = subworkspace_qm;
	    gensymed_symbol_2 = strip_item_qm;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
    }
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_4 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_5 = (SI_Long)1L;
	gensymed_symbol_6 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_5 = gensymed_symbol_5 << gensymed_symbol_6;
	gensymed_symbol_4 = gensymed_symbol_4 & gensymed_symbol_5;
	temp = (SI_Long)0L < gensymed_symbol_4;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)16L)) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subblock,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),(SI_Long)1L);
	    gensymed_symbol_1 = subblock;
	    gensymed_symbol_2 = strip_item_qm;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol;
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
	      gensymed_symbol = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol)) {
		  temp_1 = M_CAR(gensymed_symbol);
		  temp = SIMPLE_VECTOR_P(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp_1 = M_CDR(gensymed_symbol);
		  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
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
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
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
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_ && EQ(ISVREF(ab_connection_,
		      (SI_Long)3L),subblock))
		  goto end_1;
	      goto next_loop_3;
	    end_loop_3:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      connection = ab_connection_;
	      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(connection_frame_or_class,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),
			  (SI_Long)1L);
		  gensymed_symbol_1 = connection_frame_or_class;
		  gensymed_symbol_2 = strip_item_qm;
		  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2);
	      }
	      goto next_loop_2;
	    end_loop_4:;
	    POP_SPECIAL();
	}
	goto next_loop_1;
      end_loop_1:;
    }
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_4 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_5 = (SI_Long)1L;
	gensymed_symbol_6 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_5 = gensymed_symbol_5 << gensymed_symbol_6;
	gensymed_symbol_4 = gensymed_symbol_4 & gensymed_symbol_5;
	temp = (SI_Long)0L < gensymed_symbol_4;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	simulation_details = get_slot_value_function(block,
		Qsimulation_details,Nil);
	if (simulation_details) {
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(simulation_details,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)40L),(SI_Long)1L);
	    gensymed_symbol_1 = simulation_details;
	    gensymed_symbol_2 = strip_item_qm;
	    return inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_updating_of_self_representations_qm, Qsuppress_updating_of_self_representations_qm);

static Object Qtext;               /* text */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* STRIP-TEXTS-FROM-ITEM */
Object strip_texts_from_item(item)
    Object item;
{
    Object class_1, class_description, slot_descriptions, slot_description;
    Object ab_loop_list_, slot_name, type_of_slot_qm, value_qm;
    Object current_drawing_priority, cdr_new_value;
    Object suppress_updating_of_self_representations_qm;
    Declare_special(1);

    x_note_fn_call(108,7);
    class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    class_description = ISVREF(item,(SI_Long)1L);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_name = Nil;
    type_of_slot_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = ISVREF(slot_description,(SI_Long)1L);
    type_of_slot_qm = type_of_slot_if_editable(2,class_1,slot_name);
    if (type_of_slot_qm && memq_function(Qtext,CDDR(type_of_slot_qm))) {
	value_qm = get_slot_value_function(item,slot_name,Nil);
	if (value_qm) {
	    current_drawing_priority = Kdraw_as_late_as_possible;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		    0);
	      if (T)
		  update_images_of_block(item,T,Nil);
	      reclaim_text(CDR(value_qm));
	      cdr_new_value = make_new_stripped_text();
	      M_CDR(value_qm) = cdr_new_value;
	      if (EQ(slot_name,Qbox_translation_and_text))
		  reformat_text_box_in_place(1,item);
	      if (T)
		  update_images_of_block(item,Nil,Nil);
	    POP_SPECIAL();
	    suppress_updating_of_self_representations_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_self_representations_qm,Qsuppress_updating_of_self_representations_qm,suppress_updating_of_self_representations_qm,
		    0);
	      update_representations_of_slot_value(2,item,slot_name);
	    POP_SPECIAL();
	}
    }
    goto next_loop;
  end_loop:;
    return clean_out_annotation_lookup_structure(item);
}

/* STRIPPING-INHERITED-P */
Object stripping_inherited_p(item)
    Object item;
{
    Object superior_qm;

    x_note_fn_call(108,8);
    superior_qm = superior_frame(item);
  next_loop:
    if ( !TRUEP(superior_qm))
	goto end_loop;
    if ((SI_Long)0L != (IFIX(ISVREF(superior_qm,(SI_Long)4L)) & 
	    (SI_Long)2097152L))
	return VALUES_1(T);
    else if ((SI_Long)0L != (IFIX(ISVREF(superior_qm,(SI_Long)4L)) & 
	    (SI_Long)4194304L))
	return VALUES_1(Nil);
    superior_qm = superior_frame(superior_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant;      /* # */

/* MAKE-NEW-STRIPPED-TEXT */
Object make_new_stripped_text()
{
    x_note_fn_call(108,9);
    return convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)4L)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Archtypal_stripped_text, Qarchtypal_stripped_text);

/* STRIPPED-TEXT-P */
Object stripped_text_p(text)
    Object text;
{
    x_note_fn_call(108,10);
    return equalw(Archtypal_stripped_text,text);
}

/* TEXT-SLOTS-IN-FRAME-HAVE-BEEN-STRIPPED-P */
Object text_slots_in_frame_have_been_stripped_p(frame)
    Object frame;
{
    Object class_1, class_description, slot_descriptions, slot_description;
    Object ab_loop_list_, slot_name, type_of_slot_qm, ab_loop_it_, value_qm;

    x_note_fn_call(108,11);
    class_1 = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    class_description = ISVREF(frame,(SI_Long)1L);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_name = Nil;
    type_of_slot_qm = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = ISVREF(slot_description,(SI_Long)1L);
    type_of_slot_qm = type_of_slot_if_editable(2,class_1,slot_name);
    if (type_of_slot_qm && memq_function(Qtext,CDDR(type_of_slot_qm))) {
	value_qm = get_slot_value_function(frame,slot_name,Nil);
	ab_loop_it_ = value_qm ? stripped_text_p(CDR(value_qm)) : Qnil;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

void sequences3_INIT()
{
    Object temp, temp_1;
    Object Qreclaim_text, list_constant_17, Qsequences3, AB_package;
    Object Qmake_new_stripped_text, Kfuncall, list_constant_16;
    Object Qclasses_which_define, Qstrip_text, Qstrip_text_for_block;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qgeneric_method_lambda_list;
    Object list_constant_15, Qstripping_inherited_qm, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object list_constant_2, Qremove_do_not_strip_text_mark, list_constant_3;
    Object Qremove_do_not_strip_text_mark_star, list_constant_5;
    Object Qmark_not_to_strip_text, list_constant_6;
    Object Qmark_not_to_strip_text_star, Qremove_strip_text_mark_star;
    Object list_constant_4, Qremove_strip_text_mark, Qmark_to_strip_text_star;
    Object list_constant_1, Qmark_to_strip_text;

    x_note_fn_call(108,12);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qpackage_preparation_mode = STATIC_SYMBOL("PACKAGE-PREPARATION-MODE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpackage_preparation_mode,
	    Package_preparation_mode);
    Qsequences3 = STATIC_SYMBOL("SEQUENCES3",AB_package);
    record_system_variable(Qpackage_preparation_mode,Qsequences3,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qpackage_preparation_mode_changed = 
	    STATIC_SYMBOL("PACKAGE-PREPARATION-MODE-CHANGED",AB_package);
    string_constant = 
	    STATIC_STRING("Entering Package Preparation mode.  To exit this mode, select ~\n                \"Leave Package Preparation Mode\" from the Main Menu ~\n                Miscellany menu.");
    string_constant_1 = STATIC_STRING("Leaving Package Preparation mode.");
    Qmark_to_strip_text = STATIC_SYMBOL("MARK-TO-STRIP-TEXT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)1L));
    list_constant_2 = STATIC_CONS(FIX((SI_Long)0L),list_constant_1);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)5L,Qmark_to_strip_text,
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)0L),
	    list_constant_2);
    Qmark_to_strip_text_star = STATIC_SYMBOL("MARK-TO-STRIP-TEXT-*",
	    AB_package);
    list_constant_3 = STATIC_CONS(FIX((SI_Long)1L),list_constant_1);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)5L,
	    Qmark_to_strip_text_star,FIX((SI_Long)1L),FIX((SI_Long)0L),
	    FIX((SI_Long)0L),list_constant_3);
    Qremove_strip_text_mark = STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1L),
	    FIX((SI_Long)0L));
    list_constant_5 = STATIC_CONS(FIX((SI_Long)0L),list_constant_4);
    list_constant_9 = STATIC_CONS(Qremove_strip_text_mark,list_constant_5);
    Qremove_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK-*",AB_package);
    list_constant_6 = STATIC_CONS(FIX((SI_Long)1L),list_constant_4);
    list_constant_10 = STATIC_CONS(Qremove_strip_text_mark_star,
	    list_constant_6);
    Qmark_not_to_strip_text_star = 
	    STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT-*",AB_package);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)5L,
	    Qmark_not_to_strip_text_star,FIX((SI_Long)1L),FIX((SI_Long)0L),
	    FIX((SI_Long)0L),list_constant_6);
    Qmark_not_to_strip_text = STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT",
	    AB_package);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)5L,
	    Qmark_not_to_strip_text,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    FIX((SI_Long)0L),list_constant_5);
    Qremove_do_not_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK-*",AB_package);
    list_constant_13 = STATIC_CONS(Qremove_do_not_strip_text_mark_star,
	    list_constant_3);
    Qremove_do_not_strip_text_mark = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK",AB_package);
    list_constant_14 = STATIC_CONS(Qremove_do_not_strip_text_mark,
	    list_constant_2);
    list_constant = STATIC_LIST((SI_Long)8L,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qstrip_text_mark = STATIC_SYMBOL("STRIP-TEXT-MARK",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qdo_not_strip_text_mark = STATIC_SYMBOL("DO-NOT-STRIP-TEXT-MARK",
	    AB_package);
    Qstrip_text = STATIC_SYMBOL("STRIP-TEXT",AB_package);
    Qstripping_inherited_qm = STATIC_SYMBOL("STRIPPING-INHERITED\?",
	    AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qblock,Qstripping_inherited_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qstrip_text,list_constant_15,
	    Qgeneric_method_lambda_list);
    string_constant_2 = 
	    STATIC_STRING("You cannot strip texts while the system is running.  ~\n        No texts were stripped.");
    string_constant_3 = STATIC_STRING("Stripping texts now!");
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    string_constant_4 = STATIC_STRING("Finished stripping texts.");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qstrip_text_for_block = STATIC_SYMBOL("STRIP-TEXT-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qstrip_text_for_block,
	    STATIC_FUNCTION(strip_text_for_block,NIL,FALSE,2,2));
    temp = SYMBOL_FUNCTION(Qstrip_text_for_block);
    set_get(Qblock,Qstrip_text,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstrip_text),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qstrip_text,temp,Qclasses_which_define);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qarchtypal_stripped_text = STATIC_SYMBOL("ARCHTYPAL-STRIPPED-TEXT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qarchtypal_stripped_text,
	    Archtypal_stripped_text);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_new_stripped_text = STATIC_SYMBOL("MAKE-NEW-STRIPPED-TEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_new_stripped_text,
	    STATIC_FUNCTION(make_new_stripped_text,NIL,FALSE,0,0));
    list_constant_17 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_new_stripped_text);
    Qreclaim_text = STATIC_SYMBOL("RECLAIM-TEXT",AB_package);
    record_system_variable(Qarchtypal_stripped_text,Qsequences3,
	    list_constant_17,Qnil,Qnil,Qreclaim_text,Qt);
}
