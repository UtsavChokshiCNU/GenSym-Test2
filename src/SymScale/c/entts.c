/* entts.c
 * Input file:  entities.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "entts.h"


DEFINE_VARIABLE_WITH_SYMBOL(G2gl_parameters, Qg2gl_parameters);

static Object Qicon_description;   /* icon-description */

static Object Qg2gl_activity;      /* g2gl-activity */

static Object Qg2gl_object_icon_substitutions;  /* g2gl-object-icon-substitutions */

static Object Qg2gl_object;        /* g2gl-object */

/* RECLAIM-ICON-DESCRIPTION-VALUE */
Object reclaim_icon_description_value(icon_description,entity)
    Object icon_description, entity;
{
    Object default_slot_value, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object substitute_class_qm, gensymed_symbol_4;
    Object substitute_icon_description_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,0);
    default_slot_value = get_slot_init_form(2,ISVREF(ISVREF(entity,
	    (SI_Long)1L),(SI_Long)1L),Qicon_description);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qg2gl_activity,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	if (G2gl_parameters) {
	    temp_1 = assq_function(ISVREF(ISVREF(entity,(SI_Long)1L),
		    (SI_Long)1L),get_slot_value_function(G2gl_parameters,
		    Qg2gl_object_icon_substitutions,Nil));
	    substitute_class_qm = CADR(temp_1);
	}
	else
	    substitute_class_qm = Nil;
	if (substitute_class_qm) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(substitute_class_qm,
		    Class_description_gkbprop);
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qg2gl_object,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		substitute_icon_description_qm = 
			get_g2gl_object_icon_description(substitute_class_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
		    substitute_icon_description_qm = get_slot_init_form(2,
			    substitute_class_qm,Qicon_description);
		else
		    substitute_icon_description_qm = Qnil;
	    }
	}
	else
	    substitute_icon_description_qm = Nil;
    }
    else
	substitute_icon_description_qm = Nil;
    if (icon_description &&  !EQ(icon_description,default_slot_value) &&  
	    !TRUEP(substitute_icon_description_qm))
	reclaim_icon_description(icon_description);
    return VALUES_1(Nil);
}

/* RECLAIM-RUNTIME-STRUCTURES-AFFECTED-BY-THIS-ENTITY-VALUE */
Object reclaim_runtime_structures_affected_by_this_entity_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(90,1);
    update_runtime_structures_according_to_edit(1,frame);
    return VALUES_1(Nil);
}

/* PUT-DEBUGGING-SPECIFICATION-WHERE-SLOT-IS-ABSENT */
Object put_debugging_specification_where_slot_is_absent(entity,value)
    Object entity, value;
{
    x_note_fn_call(90,2);
    return VALUES_1(Nil);
}

/* GENERATE-SPOT-FOR-ENTITY */
Object generate_spot_for_entity(entity,mouse_pointer)
    Object entity, mouse_pointer;
{
    x_note_fn_call(90,3);
    return generate_simple_item_spot(entity,mouse_pointer);
}

/* ICON-DESCRIPTION-FUNCTION */
Object icon_description_function(entity)
    Object entity;
{
    x_note_fn_call(90,4);
    return VALUES_1(ISVREF(entity,(SI_Long)16L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Module_information, Qmodule_information);

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object Qparent_of_subworkspace_qm;  /* parent-of-subworkspace? */

static Object Qactivatable_subworkspace;  /* activatable-subworkspace */

static Object Qtop_level_kb_module_qm;  /* top-level-kb-module? */

/* ADD-SUBWORKSPACE */
Object add_subworkspace(workspace,entity)
    Object workspace, entity;
{
    Object sub_class_bit_vector, previously_top_level_workspace_of_module_p;
    Object new_value, old_value, frame, sub_vector_qm, function_qm, temp_1;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, method_index;
    char temp;

    x_note_fn_call(90,5);
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
    previously_top_level_workspace_of_module_p = (temp ?  
	    !TRUEP(ISVREF(workspace,(SI_Long)18L)) : TRUEP(Nil)) ? 
	    get_lookup_slot_value(workspace,Qmodule_this_is_part_of_qm) : Nil;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qparent_of_subworkspace_qm);
    SVREF(workspace,FIX((SI_Long)18L)) = entity;
    if ( !TRUEP(memq_function(workspace,ISVREF(entity,(SI_Long)18L)))) {
	new_value = slot_value_cons_1(workspace,Nil);
	old_value = Nil;
      next_loop:
	old_value = ISVREF(entity,(SI_Long)18L);
	M_CDR(new_value) = old_value;
	if (CAS_SVREF(entity,(SI_Long)18L,old_value,new_value))
	    goto end_loop;
	goto next_loop;
      end_loop:
	goto end_1;
      end_1:;
	if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
		(SI_Long)1L) &&  
		!TRUEP(get_property_value_in_object_configuration(entity,
		Qactivatable_subworkspace,Nil))) {
	    method_index = (SI_Long)30L;
	    frame = workspace;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		inline_funcall_1(function_qm,frame);
	}
	else {
	    temp = (SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)4L)) & 
		    (SI_Long)8192L);
	    if (temp);
	    else
		temp = (SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
			(SI_Long)256L);
	    if (temp);
	    else {
		temp_1 = ISVREF(entity,(SI_Long)8L);
		temp = TRUEP(CAR(temp_1));
	    }
	    if (temp) {
		gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
		gensymed_symbol_4 = workspace;
		gensymed_symbol_5 = T;
		inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
			gensymed_symbol_5);
	    }
	}
    }
    determine_subworkspace_connection_posts(entity);
    add_as_inferior_block(workspace,entity);
    if (previously_top_level_workspace_of_module_p && 
	    get_slot_value_function(Module_information,
	    Qtop_level_kb_module_qm,Nil))
	change_slot_value(3,workspace,Qmodule_this_is_part_of_qm,Nil);
    return VALUES_1(workspace);
}

static Object Qsubworkspaces;      /* subworkspaces */

/* REMOVE-AS-SUBWORKSPACE-IF-NECESSARY */
Object remove_as_subworkspace_if_necessary varargs_1(int, n)
{
    Object workspace;
    Object deactivate_workspace_qm, parent_of_subworkspace_qm, svref_new_value;
    Object frame, sub_vector_qm, function_qm, top_level_kb_module_qm;
    Object sub_class_bit_vector;
    SI_Long method_index, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,6);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    deactivate_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    parent_of_subworkspace_qm = ISVREF(workspace,(SI_Long)18L);
    if (parent_of_subworkspace_qm) {
	remove_as_inferior_block(workspace,parent_of_subworkspace_qm);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qparent_of_subworkspace_qm);
	SVREF(workspace,FIX((SI_Long)18L)) = Nil;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(parent_of_subworkspace_qm,Qsubworkspaces);
	svref_new_value = delete_slot_value_element_1(workspace,
		ISVREF(parent_of_subworkspace_qm,(SI_Long)18L));
	SVREF(parent_of_subworkspace_qm,FIX((SI_Long)18L)) = svref_new_value;
	if (deactivate_workspace_qm) {
	    method_index = (SI_Long)31L;
	    frame = workspace;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		inline_funcall_2(function_qm,frame,Nil);
	}
	flush_all_subworkspace_connection_posts_for_object(parent_of_subworkspace_qm,
		Nil);
    }
    if ( !((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
	    (SI_Long)512L)) &&  !TRUEP(parent_of_subworkspace_qm)) {
	top_level_kb_module_qm = 
		get_slot_value_function(Module_information,
		Qtop_level_kb_module_qm,Nil);
	sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),
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
	if (temp ? TRUEP(top_level_kb_module_qm) : TRUEP(Nil))
	    change_slot_value(3,workspace,Qmodule_this_is_part_of_qm,
		    top_level_kb_module_qm);
    }
    return VALUES_1(workspace);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm, Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm);

/* TRANSFER-SUBWORKSPACE-IF-ANY */
Object transfer_subworkspace_if_any(entity,entity_without_subworkspace)
    Object entity, entity_without_subworkspace;
{
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,7);
    if (ISVREF(entity,(SI_Long)18L)) {
	inhibit_updating_module_related_frame_notes_for_all_workspaces_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		0);
	  temp = ISVREF(entity,(SI_Long)18L);
	  result = add_subworkspace(remove_as_subworkspace_if_necessary(1,
		  FIRST(temp)),entity_without_subworkspace);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qworkspace_does_not_belong_to_any_module;  /* workspace-does-not-belong-to-any-module */

/* REPLACE-SUBWORKSPACE-IF-ANY */
Object replace_subworkspace_if_any(kb_workspace,entity)
    Object kb_workspace, entity;
{
    Object kb_workspace_already_subworkspace_qm, subworkspace_list;
    Object subworkspace, ab_loop_list_;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,8);
    kb_workspace_already_subworkspace_qm = Nil;
    if (ISVREF(entity,(SI_Long)18L)) {
	subworkspace_list = copy_list_using_gensym_conses_1(ISVREF(entity,
		(SI_Long)18L));
	subworkspace = Nil;
	ab_loop_list_ = subworkspace_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(subworkspace,kb_workspace))
	    kb_workspace_already_subworkspace_qm = T;
	else
	    remove_as_subworkspace_if_necessary(2,subworkspace,Nil);
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(subworkspace_list);
    }
    if ( !TRUEP(kb_workspace_already_subworkspace_qm)) {
	inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
		=  !TRUEP(ISVREF(kb_workspace,(SI_Long)18L)) ? ( 
		!TRUEP(frame_has_note_p(kb_workspace,
		Qworkspace_does_not_belong_to_any_module)) ? T : Nil) : Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		0);
	  remove_as_subworkspace_if_necessary(2,kb_workspace,Nil);
	  result = add_subworkspace(kb_workspace,entity);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Subworkspace_currently_being_deleted_qm, Qsubworkspace_currently_being_deleted_qm);

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* RECLAIM-SUBWORKSPACES-VALUE */
Object reclaim_subworkspaces_value(subworkspaces,entity)
    Object subworkspaces, entity;
{
    Object reference_serial_number, subworkspace, ab_loop_list_;
    Object gensymed_symbol, xa, ya, subworkspace_currently_being_deleted_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(90,9);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(entity,Qsubworkspaces);
    SVREF(entity,FIX((SI_Long)18L)) = Nil;
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    subworkspace = Nil;
    ab_loop_list_ = subworkspaces;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subworkspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(subworkspace,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(subworkspace) ? EQ(ISVREF(subworkspace,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(subworkspace,Qparent_of_subworkspace_qm);
	SVREF(subworkspace,FIX((SI_Long)18L)) = Nil;
	subworkspace_currently_being_deleted_qm = subworkspace;
	PUSH_SPECIAL_WITH_SYMBOL(Subworkspace_currently_being_deleted_qm,Qsubworkspace_currently_being_deleted_qm,subworkspace_currently_being_deleted_qm,
		0);
	  delete_frame(subworkspace);
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:
    reclaim_frame_serial_number(reference_serial_number);
    reclaim_slot_value_list_1(subworkspaces);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* RECLAIM-PARENT-OF-SUBWORKSPACE?-VALUE */
Object reclaim_parent_of_subworkspace_qm_value(parent_of_subworkspace_qm,
	    subworkspace)
    Object parent_of_subworkspace_qm, subworkspace;
{
    Object x2;
    char temp;

    x_note_fn_call(90,10);
    if (SIMPLE_VECTOR_P(parent_of_subworkspace_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parent_of_subworkspace_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(parent_of_subworkspace_qm,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(parent_of_subworkspace_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	remove_as_subworkspace_if_necessary(1,subworkspace);
    return VALUES_1(Nil);
}

/* DISALLOW-CONNECTION-SUBWORKSPACES */
Object disallow_connection_subworkspaces(workspace,connection_frame_1)
    Object workspace, connection_frame_1;
{
    x_note_fn_call(90,11);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qmodule_this_is_part_of_qm);
    set_lookup_slot_value_1(workspace,Qmodule_this_is_part_of_qm,
	    get_module_block_is_in(connection_frame_1));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qparent_of_subworkspace_qm);
    return VALUES_1(SVREF(workspace,FIX((SI_Long)18L)) = Nil);
}

static Object Qworkspace;          /* workspace */

/* INITIALIZE-AFTER-READING-FOR-WORKSPACE */
Object initialize_after_reading_for_workspace(workspace)
    Object workspace;
{
    Object frame, sub_vector_qm, method_function_qm, parent_1, x2;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,12);
    frame = workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qworkspace)) {
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
    compute_workspace_caches_after_reading(workspace);
    parent_1 = ISVREF(workspace,(SI_Long)18L);
    if (SIMPLE_VECTOR_P(parent_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(parent_1)) > (SI_Long)2L &&  
	    !EQ(ISVREF(parent_1,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(parent_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(parent_1,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    add_subworkspace(workspace,parent_1);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		disallow_connection_subworkspaces(workspace,parent_1);
	}
    }
    if ( !TRUEP(workspace_background_images_are_centered_p()))
	return mark_background_image_coordinates_as_needing_update(workspace);
    else
	return VALUES_1(Nil);
}

static Object Qicon_attributes_plist;  /* icon-attributes-plist */

/* CHANGE-ICON-ATTRIBUTE */
Object change_icon_attribute(entity,indicator,value_qm)
    Object entity, indicator, value_qm;
{
    Object icon_attributes_plist, l_trailer_qm, l, temp, temp_1;

    x_note_fn_call(90,13);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(entity,Qicon_attributes_plist);
    icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
    l_trailer_qm = Nil;
    l = icon_attributes_plist;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (EQ(M_CAR(l),indicator)) {
	if (value_qm) {
	    reclaim_slot_value(M_CAR(M_CDR(l)));
	    temp = M_CDR(l);
	    M_CAR(temp) = value_qm;
	}
	else {
	    if (l_trailer_qm) {
		temp_1 = M_CDR(l);
		temp = CDR(temp_1);
		M_CDR(l_trailer_qm) = temp;
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(entity,Qicon_attributes_plist);
		temp = CDDR(l);
		SVREF(entity,FIX((SI_Long)17L)) = temp;
	    }
	    M_CDDR(l) = Nil;
	    reclaim_slot_value(l);
	}
	return VALUES_1(value_qm);
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop;
  end_loop:
    if (value_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(entity,Qicon_attributes_plist);
	temp = slot_value_cons_1(indicator,slot_value_cons_1(value_qm,
		icon_attributes_plist));
	SVREF(entity,FIX((SI_Long)17L)) = temp;
    }
    return VALUES_1(value_qm);
    return VALUES_1(Qnil);
}

static Object Qicon_color_pattern;  /* icon-color-pattern */

static Object list_constant;       /* # */

/* CURRENT-COLOR-PATTERN-OF-ENTITY */
Object current_color_pattern_of_entity(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(90,14);
    temp = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
	    Qicon_color_pattern);
    if (temp);
    else {
	temp = ISVREF(ISVREF(entity,(SI_Long)16L),(SI_Long)10L);
	if (temp);
	else
	    temp = list_constant;
    }
    return VALUES_1(temp);
}

static Object Qline_color;         /* line-color */

/* CURRENT-LINE-COLOR-OF-ENTITY */
Object current_line_color_of_entity(entity)
    Object entity;
{
    Object temp, workspace_qm;

    x_note_fn_call(90,15);
    temp = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),Qline_color);
    if (temp);
    else {
	temp = ISVREF(ISVREF(entity,(SI_Long)16L),(SI_Long)5L);
	if (temp);
	else {
	    workspace_qm = get_workspace_if_any(entity);
	    temp = workspace_qm ? ISVREF(workspace_qm,(SI_Long)22L) : Nil;
	}
	if (temp);
	else
	    temp = Current_default_line_color;
    }
    return VALUES_1(temp);
}

static Object Qpolychrome;         /* polychrome */

/* GET-POLYCHROME-HEADER-FROM-ENTITY-IF-ANY */
Object get_polychrome_header_from_entity_if_any(entity)
    Object entity;
{
    Object icon_description_qm, line_drawing_description, first_element, temp;

    x_note_fn_call(90,16);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	line_drawing_description = ISVREF(icon_description_qm,(SI_Long)8L);
	first_element = CAR(line_drawing_description);
	temp = CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ?
		 first_element : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* POLYCHROME-ICON-P */
Object polychrome_icon_p(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(90,17);
    temp = get_polychrome_header_from_entity_if_any(entity);
    return VALUES_1(temp);
}

static Object Qforeground;         /* foreground */

/* MONOCHROME-ICON-P */
Object monochrome_icon_p(entity)
    Object entity;
{
    Object header_qm, temp, region, color, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(90,18);
    header_qm = get_polychrome_header_from_entity_if_any(entity);
    temp =  !TRUEP(header_qm) ? T : Nil;
    if (temp);
    else {
	region = Nil;
	color = Nil;
	ab_loop_list_ = CDR(header_qm);
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	region = CAR(ab_loop_desetq_);
	color = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(EQ(region,Qforeground) && EQ(color,Qforeground))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qicon_color;         /* icon-color */

/* MULTICHROME-ICON-P */
Object multichrome_icon_p(entity)
    Object entity;
{
    Object header_qm, region, color, ab_loop_list_, ab_loop_it_;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(90,19);
    header_qm = get_polychrome_header_from_entity_if_any(entity);
    if (header_qm) {
	region = Nil;
	color = Nil;
	ab_loop_list_ = CDR(header_qm);
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	region = CAR(ab_loop_desetq_);
	color = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQ(region,Qicon_color) ? T : Nil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* SINGLE-COLOR-ENTITY-P */
Object single_color_entity_p(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(90,20);
    temp = get_polychrome_header_from_entity_if_any(entity);
    temp = CDR(temp);
    return VALUES_1( !TRUEP(CDR(temp)) ? T : Nil);
}

static Object Qentity;             /* entity */

/* INITIALIZE-AFTER-READING-FOR-ENTITY */
Object initialize_after_reading_for_entity(entity)
    Object entity;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(90,21);
    frame = entity;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
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
    return bring_block_edges_in_synch_with_icon_description(entity);
}

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Qfloat_array;        /* float-array */

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

/* TRANSFORMED-EDGES-OF-ENTITY */
Object transformed_edges_of_entity(entity,use_managed_floats_p)
    Object entity, use_managed_floats_p;
{
    Object icon_description_qm, icon_attributes_plist, width_of_icon;
    Object height_of_icon, x_magnification_qm, y_magnification_qm;
    Object width_of_icon_after_magnification, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float;
    Object height_of_icon_after_magnification, rotated_by_90_p_1;
    SI_Long gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(90,22);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
	width_of_icon = icon_attributes_plist ? getf(icon_attributes_plist,
		Qwidth,_) : Nil;
	if (width_of_icon);
	else
	    width_of_icon = ISVREF(icon_description_qm,(SI_Long)1L);
	height_of_icon = icon_attributes_plist ? 
		getf(icon_attributes_plist,Qheight,_) : Nil;
	if (height_of_icon);
	else
	    height_of_icon = ISVREF(icon_description_qm,(SI_Long)2L);
	x_magnification_qm = icon_attributes_plist ? 
		getf(icon_attributes_plist,Qx_magnification,_) : Nil;
	if (x_magnification_qm);
	else
	    x_magnification_qm = ISVREF(icon_description_qm,(SI_Long)6L);
	y_magnification_qm = icon_attributes_plist ? 
		getf(icon_attributes_plist,Qy_magnification,_) : Nil;
	if (y_magnification_qm);
	else
	    y_magnification_qm = ISVREF(icon_description_qm,(SI_Long)7L);
	if (x_magnification_qm) {
	    if (use_managed_floats_p) {
		gensymed_symbol = (SI_Long)255L & IFIX(x_magnification_qm);
		if ((SI_Long)0L == gensymed_symbol)
		    width_of_icon_after_magnification = 
			    FIX(IFIX(FIXNUM_TIMES(width_of_icon,
			    x_magnification_qm)) + (SI_Long)128L >>  -  - 
			    (SI_Long)8L);
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    (double)IFIX(FIXNUM_TIMES(width_of_icon,
			    x_magnification_qm)) / 256.0;
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    width_of_icon_after_magnification = new_float;
		}
	    }
	    else
		width_of_icon_after_magnification = 
			FIX(IFIX(FIXNUM_TIMES(width_of_icon,
			x_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L);
	}
	else
	    width_of_icon_after_magnification = width_of_icon;
	if (y_magnification_qm) {
	    if (use_managed_floats_p) {
		gensymed_symbol = (SI_Long)255L & IFIX(y_magnification_qm);
		if ((SI_Long)0L == gensymed_symbol)
		    height_of_icon_after_magnification = 
			    FIX(IFIX(FIXNUM_TIMES(height_of_icon,
			    y_magnification_qm)) + (SI_Long)128L >>  -  - 
			    (SI_Long)8L);
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    (double)IFIX(FIXNUM_TIMES(height_of_icon,
			    y_magnification_qm)) / 256.0;
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    height_of_icon_after_magnification = new_float;
		}
	    }
	    else
		height_of_icon_after_magnification = 
			FIX(IFIX(FIXNUM_TIMES(height_of_icon,
			y_magnification_qm)) + (SI_Long)128L >>  -  - 
			(SI_Long)8L);
	}
	else
	    height_of_icon_after_magnification = height_of_icon;
	rotated_by_90_p_1 = icon_attributes_plist ? 
		rotated_by_90_p(getf(icon_attributes_plist,
		Qreflection_and_rotation,_)) : Qnil;
	if (rotated_by_90_p_1)
	    return VALUES_2(height_of_icon_after_magnification,
		    width_of_icon_after_magnification);
	else
	    return VALUES_2(width_of_icon_after_magnification,
		    height_of_icon_after_magnification);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_version_from_kb_being_read, Qsystem_version_from_kb_being_read);

static Object Qdefault;            /* default */

static Object Qtransparent;        /* transparent */

/* BRING-BLOCK-EDGES-IN-SYNCH-WITH-ICON-DESCRIPTION */
Object bring_block_edges_in_synch_with_icon_description(entity)
    Object entity;
{
    Object icon_description_qm, width_of_icon_after_transformations;
    Object height_of_icon_after_transformations, icon_attributes_plist;
    Object gensymed_symbol, temp, temp_1, instance_color_pattern_qm, pair_qm;
    Object ab_loop_list_, ab_loop_it_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_color_pattern, symbol, default_color_pattern;
    Object region, ab_loop_desetq_, default_color, new_instance_color_pattern;
    Object line_color, class_color_pattern_qm, color, new_color;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, width_of_block;
    SI_Long height_of_block;
    char temp_2;
    Object result;

    x_note_fn_call(90,23);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	result = transformed_edges_of_entity(entity,Nil);
	MVS_2(result,width_of_icon_after_transformations,
		height_of_icon_after_transformations);
	icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	width_of_block = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	height_of_block = gensymed_symbol_1 - gensymed_symbol_2;
	if ( !(IFIX(width_of_icon_after_transformations) == 
		width_of_block) ||  
		!(IFIX(height_of_icon_after_transformations) == 
		height_of_block)) {
	    temp = getf(icon_attributes_plist,Qx_magnification,_);
	    if (temp);
	    else
		temp = ISVREF(icon_description_qm,(SI_Long)6L);
	    temp_1 = getf(icon_attributes_plist,Qy_magnification,_);
	    if (temp_1);
	    else
		temp_1 = ISVREF(icon_description_qm,(SI_Long)7L);
	    magnify_icon(entity,temp,temp_1,Nil,Nil,Nil);
	}
	instance_color_pattern_qm = icon_attributes_plist ? 
		getfq_function_no_default(icon_attributes_plist,
		Qicon_color_pattern) : Qnil;
	pair_qm = Nil;
	ab_loop_list_ = instance_color_pattern_qm;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pair_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ =  !TRUEP(pair_qm) ? T : Nil;
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_2 = TRUEP(Qnil);
      end_1:;
	if (temp_2) {
	    pair_qm = Nil;
	    ab_loop_list_ = instance_color_pattern_qm;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    pair_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (pair_qm) {
		ab_loopvar__2 = 
			slot_value_cons_1(copy_tree_using_slot_value_conses_1(pair_qm),
			Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    new_color_pattern = ab_loopvar_;
	    goto end_2;
	    new_color_pattern = Qnil;
	  end_2:;
	    change_icon_attribute(entity,Qicon_color_pattern,
		    new_color_pattern);
	    instance_color_pattern_qm = new_color_pattern;
	}
	if (instance_color_pattern_qm) {
	    symbol = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L);
	    if (lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop)) {
		temp = lookup_global_or_kb_specific_property_value(symbol,
			Class_definition_gkbprop);
		temp_2 = CONSP(temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? 
		TRUEP(system_revision_greater_p(System_version_of_current_gensym_product_line,
		System_version_from_kb_being_read)) : TRUEP(Nil)) {
	    default_color_pattern = get_color_pattern_of_item(4,entity,
		    Qdefault,Nil,T);
	    region = Nil;
	    ab_loop_list_ = default_color_pattern;
	    ab_loop_desetq_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    region = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(assq_function(region,instance_color_pattern_qm))) {
		temp_2 = TRUEP(Nil);
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_2 = TRUEP(T);
	    goto end_3;
	    temp_2 = TRUEP(Qnil);
	  end_3:;
	    if (temp_2) {
		region = Nil;
		ab_loop_list_ = instance_color_pattern_qm;
		ab_loop_desetq_ = Nil;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		region = CAR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(assq_function(region,default_color_pattern))) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		goto next_loop_3;
	      end_loop_3:
		temp_2 = TRUEP(T);
		goto end_4;
		temp_2 = TRUEP(Qnil);
	      end_4:;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if ( !temp_2) {
		region = Nil;
		default_color = Nil;
		ab_loop_list_ = default_color_pattern;
		new_instance_color_pattern = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop_4:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_4;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		region = CAR(ab_loop_desetq_);
		default_color = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		temp_1 = region;
		temp = assq_function(region,instance_color_pattern_qm);
		temp = CDR(temp);
		if (temp);
		else
		    temp = default_color;
		ab_loopvar__1 = slot_value_cons_1(slot_value_cons_1(temp_1,
			temp),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    new_instance_color_pattern = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop_4;
	      end_loop_4:
		change_icon_attribute(entity,Qicon_color_pattern,
			new_instance_color_pattern);
		instance_color_pattern_qm = new_instance_color_pattern;
	    }
	    reclaim_slot_value(default_color_pattern);
	}
	if (multichrome_icon_p(entity) && icon_attributes_plist && 
		getfq_function_no_default(icon_attributes_plist,Qline_color)) {
	    line_color = getfq_function_no_default(icon_attributes_plist,
		    Qline_color);
	    class_color_pattern_qm = ISVREF(icon_description_qm,(SI_Long)10L);
	    instance_color_pattern_qm = 
		    getfq_function_no_default(icon_attributes_plist,
		    Qicon_color_pattern);
	    if (instance_color_pattern_qm);
	    else {
		region = Nil;
		color = Nil;
		ab_loop_list_ = class_color_pattern_qm;
		new_color = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		region = CAR(ab_loop_desetq_);
		color = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		new_color =  !EQ(line_color,region) && EQ(line_color,
			Qtransparent) || EQ(region,Qicon_color) ? 
			line_color : color;
		ab_loopvar__2 = slot_value_cons_1(slot_value_cons_1(region,
			new_color),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_5;
	      end_loop_5:
		new_instance_color_pattern = ab_loopvar_;
		goto end_5;
		new_instance_color_pattern = Qnil;
	      end_5:;
		set_icon_colors(entity,Nil,new_instance_color_pattern,Nil);
	    }
	    if (icon_has_region_p(entity,Qicon_color))
		return change_icon_attribute(entity,Qline_color,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-ENTITY */
Object make_entity varargs_1(int, n)
{
    Object subclass_of_entity;
    Object special_stubs_handling_qm, maybe_defer_slot_group_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,24);
    INIT_ARGS_nonrelocating();
    subclass_of_entity = REQUIRED_ARG_nonrelocating();
    special_stubs_handling_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    maybe_defer_slot_group_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return make_entity_of_class_description(lookup_global_or_kb_specific_property_value(subclass_of_entity,
	    Class_description_gkbprop),special_stubs_handling_qm,
	    maybe_defer_slot_group_qm);
}

/* MAKE-ENTITY-OF-CLASS-DESCRIPTION */
Object make_entity_of_class_description(class_description,
	    special_stubs_handling_qm,maybe_defer_slot_group_qm)
    Object class_description, special_stubs_handling_qm;
    Object maybe_defer_slot_group_qm;
{
    Object entity;

    x_note_fn_call(90,25);
    entity = make_frame_of_class_description(class_description);
    if ( !(maybe_defer_slot_group_qm && 
	    slot_group_may_be_deferred_for_entity(entity)))
	set_up_icon_for_entity(2,entity,special_stubs_handling_qm);
    return VALUES_1(entity);
}

static Object Qattribute_displays;  /* attribute-displays */

static Object Qstubs;              /* stubs */

static Object Qnone;               /* none */

/* SLOT-GROUP-MAY-BE-DEFERRED-FOR-ENTITY */
Object slot_group_may_be_deferred_for_entity(entity)
    Object entity;
{
    Object class_description, attribute_displays_class_feature_qm;
    Object stubs_class_feature_qm, icon_attributes_plist_qm, temp;

    x_note_fn_call(90,26);
    class_description = ISVREF(entity,(SI_Long)1L);
    attribute_displays_class_feature_qm = 
	    assq_function(Qattribute_displays,ISVREF(class_description,
	    (SI_Long)12L));
    stubs_class_feature_qm = assq_function(Qstubs,ISVREF(class_description,
	    (SI_Long)12L));
    if (( !TRUEP(stubs_class_feature_qm) || EQ(CDR(stubs_class_feature_qm),
	    Qnone)) && ( !TRUEP(attribute_displays_class_feature_qm) || 
	    EQ(CDR(attribute_displays_class_feature_qm),Qnone))) {
	icon_attributes_plist_qm = ISVREF(entity,(SI_Long)17L);
	temp =  !(icon_attributes_plist_qm ? 
		TRUEP(getf(icon_attributes_plist_qm,
		Qreflection_and_rotation,_)) : TRUEP(Nil)) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* PERFORM-ANY-DEFERRED-ICON-SET-UP */
Object perform_any_deferred_icon_set_up(item)
    Object item;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(90,27);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    if (temp ?  !TRUEP(ISVREF(item,(SI_Long)14L)) : TRUEP(Nil))
	set_up_icon_for_entity(1,item);
    return VALUES_1(Nil);
}

/* LINE-DRAWING-DESCRIPTION-IS-OPAQUE-P */
Object line_drawing_description_is_opaque_p(line_drawing_description,
	    default_variables,computed_values_plist,icon_width,icon_height)
    Object line_drawing_description, default_variables, computed_values_plist;
    Object icon_width, icon_height;
{
    x_note_fn_call(90,28);
    return VALUES_1(Nil);
}

/* IMAGE-COVERS-ICON */
Object image_covers_icon(image_drawing_element,entity)
    Object image_drawing_element, entity;
{
    Object icon_description, icon_width, icon_height, image_data, image_width;
    Object image_height, image_coordinates, image_x_shift, image_y_shift;

    x_note_fn_call(90,29);
    icon_description = ISVREF(entity,(SI_Long)16L);
    icon_width = ISVREF(icon_description,(SI_Long)1L);
    icon_height = ISVREF(icon_description,(SI_Long)2L);
    image_data = find_image_data(SECOND(image_drawing_element));
    if (image_data) {
	image_width = ISVREF(image_data,(SI_Long)5L);
	image_height = ISVREF(image_data,(SI_Long)6L);
	image_coordinates = THIRD(image_drawing_element);
	image_x_shift = CAR(image_coordinates);
	if (image_x_shift);
	else
	    image_x_shift = FIX((SI_Long)0L);
	image_y_shift = SECOND(image_coordinates);
	if (image_y_shift);
	else
	    image_y_shift = FIX((SI_Long)0L);
	if (IFIX(ISVREF(image_data,(SI_Long)13L)) == (SI_Long)-1L && 
		IFIX(image_x_shift) < (SI_Long)1L && IFIX(image_y_shift) < 
		(SI_Long)1L && FIXNUM_GT(FIXNUM_ADD(image_width,
		image_x_shift),icon_width))
	    return VALUES_1(FIXNUM_GT(FIXNUM_ADD(image_height,
		    image_y_shift),icon_height) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qimage;              /* image */

/* BACKGROUND-LAYER-COVERS-ICON */
Object background_layer_covers_icon(background_layer_qm,entity)
    Object background_layer_qm, entity;
{
    Object temp;

    x_note_fn_call(90,30);
    temp =  !(CONSP(background_layer_qm) && EQ(FIRST(background_layer_qm),
	    Qimage)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return image_covers_icon(background_layer_qm,entity);
}

/* VALID-BACKGROUND-LAYER-P */
Object valid_background_layer_p(background_layer_qm,regions)
    Object background_layer_qm, regions;
{
    Object temp;

    x_note_fn_call(90,31);
    temp = CONSP(background_layer_qm) && EQ(FIRST(background_layer_qm),
	    Qimage) ? find_image_data(SECOND(background_layer_qm)) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else
	return valid_region_or_color_p(background_layer_qm,regions);
}

static Object Qbackground;         /* background */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

/* VALID-REGION-OR-COLOR-P */
Object valid_region_or_color_p(region_or_color_qm,regions)
    Object region_or_color_qm, regions;
{
    Object temp, color;

    x_note_fn_call(90,32);
    if (SYMBOLP(region_or_color_qm)) {
	temp = EQ(region_or_color_qm,Qforeground) ? T : Nil;
	if (temp);
	else
	    temp = EQ(region_or_color_qm,Qbackground) ? T : Nil;
	if (temp);
	else
	    temp = EQ(region_or_color_qm,Qtransparent) ? T : Nil;
	if (temp);
	else
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(region_or_color_qm),
		    Qcolor_value_vector_index_and_intensity);
	if (temp);
	else
	    temp = rgb_color_p(region_or_color_qm);
	if (temp)
	    return VALUES_1(temp);
	else {
	    temp = assq_function(region_or_color_qm,regions);
	    color = CDR(temp);
	    temp = EQ(color,Qforeground) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(color,Qbackground) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(color,Qtransparent) ? T : Nil;
	    if (temp);
	    else
		temp = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
			Qcolor_value_vector_index_and_intensity);
	    if (temp)
		return VALUES_1(temp);
	    else
		return rgb_color_p(color);
	}
    }
    else
	return VALUES_1(Nil);
}

/* ENTITY-IS-OPAQUE-P */
Object entity_is_opaque_p(entity)
    Object entity;
{
    Object icon_description, line_drawing_description, icon_attributes_plist;
    Object computed_values_plist, temp, default_variables;
    Object icon_color_pattern_qm, regions, background_layer, result_1;

    x_note_fn_call(90,33);
    icon_description = ISVREF(entity,(SI_Long)16L);
    line_drawing_description = ISVREF(icon_description,(SI_Long)8L);
    icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
    computed_values_plist = get_computed_values_plist(icon_attributes_plist);
    temp = get_variable_specification_if_any(line_drawing_description);
    default_variables = CDR(temp);
    icon_color_pattern_qm = ISVREF(icon_description,(SI_Long)10L);
    if (icon_color_pattern_qm) {
	regions = icon_attributes_plist ? 
		getfq_function_no_default(icon_attributes_plist,
		Qicon_color_pattern) : Nil;
	if (regions);
	else
	    regions = icon_color_pattern_qm;
    }
    else
	regions = Nil;
    background_layer = ISVREF(icon_description,(SI_Long)13L);
    result_1 = valid_background_layer_p(background_layer,regions) ? 
	    background_layer_covers_icon(background_layer,entity) : Qnil;
    if (result_1);
    else
	result_1 = 
		line_drawing_description_is_opaque_p(line_drawing_description,
		default_variables,computed_values_plist,
		ISVREF(icon_description,(SI_Long)1L),
		ISVREF(icon_description,(SI_Long)2L));
    return VALUES_1(result_1);
}

static Object Qframe_flags;        /* frame-flags */

static Object Kno_stubs;           /* :no-stubs */

static Object Qparent_frame;       /* parent-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

static Object Ktransient;          /* :transient */

/* SET-UP-ICON-FOR-ENTITY */
Object set_up_icon_for_entity varargs_1(int, n)
{
    Object entity;
    Object special_stubs_handling_qm, icon_description_qm;
    Object icon_attributes_plist_qm, class_description, sub_class_bit_vector;
    Object width, height, temp_1, stub_specs_qm, x_magnification_qm;
    Object y_magnification_qm, gensymed_symbol_3, temp_2;
    Object reflection_and_rotation_qm, attribute_display_specs_qm;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long x_center_of_entity, y_center_of_entity;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,34);
    INIT_ARGS_nonrelocating();
    entity = REQUIRED_ARG_nonrelocating();
    special_stubs_handling_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(entity,(SI_Long)14L))) {
	icon_description_qm = ISVREF(entity,(SI_Long)16L);
	icon_attributes_plist_qm = ISVREF(entity,(SI_Long)17L);
	if (icon_description_qm) {
	    if (entity_is_opaque_p(entity)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(entity,Qframe_flags);
		svref_new_value = IFIX(ISVREF(entity,(SI_Long)4L)) | 
			(SI_Long)1024L;
		ISVREF(entity,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    class_description = ISVREF(entity,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    if ( !temp) {
		width = icon_attributes_plist_qm ? 
			getf(icon_attributes_plist_qm,Qwidth,_) : Nil;
		if (width);
		else
		    width = ISVREF(icon_description_qm,(SI_Long)1L);
		height = icon_attributes_plist_qm ? 
			getf(icon_attributes_plist_qm,Qheight,_) : Nil;
		if (height);
		else
		    height = ISVREF(icon_description_qm,(SI_Long)2L);
		change_edges_of_block(entity,Nil,Nil,width,height);
	    }
	    if ( !EQ(special_stubs_handling_qm,Kno_stubs)) {
		temp_1 = assq_function(Qstubs,ISVREF(class_description,
			(SI_Long)12L));
		stub_specs_qm = CDR(temp_1);
		if (stub_specs_qm &&  !EQ(stub_specs_qm,Qnone) &&  
			!TRUEP(get_lookup_slot_value_given_default(entity,
			Qparent_frame,Nil)) &&  
			!TRUEP(get_lookup_slot_value_given_default(entity,
			Qparent_attribute_name,Nil)))
		    make_stubs(3,entity,stub_specs_qm,
			    EQ(special_stubs_handling_qm,Ktransient) ? T : 
			    Nil);
	    }
	    x_magnification_qm = icon_attributes_plist_qm ? 
		    getf(icon_attributes_plist_qm,Qx_magnification,_) : Nil;
	    if (x_magnification_qm);
	    else
		x_magnification_qm = ISVREF(icon_description_qm,(SI_Long)6L);
	    y_magnification_qm = icon_attributes_plist_qm ? 
		    getf(icon_attributes_plist_qm,Qy_magnification,_) : Nil;
	    if (y_magnification_qm);
	    else
		y_magnification_qm = ISVREF(icon_description_qm,(SI_Long)7L);
	    if (x_magnification_qm || y_magnification_qm) {
		if (x_magnification_qm) {
		    gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol = IFIX(gensymed_symbol_3);
		    gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		    gensymed_symbol_1 = IFIX(x_magnification_qm);
		    gensymed_symbol = gensymed_symbol * gensymed_symbol_1;
		    gensymed_symbol_1 = (SI_Long)128L;
		    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
		    gensymed_symbol_1 = (SI_Long)8L;
		    temp_1 = FIX(gensymed_symbol >>  -  - gensymed_symbol_1);
		}
		else
		    temp_1 = Nil;
		if (y_magnification_qm) {
		    gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol = IFIX(gensymed_symbol_3);
		    gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		    gensymed_symbol_1 = IFIX(y_magnification_qm);
		    gensymed_symbol = gensymed_symbol * gensymed_symbol_1;
		    gensymed_symbol_1 = (SI_Long)128L;
		    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
		    gensymed_symbol_1 = (SI_Long)8L;
		    temp_2 = FIX(gensymed_symbol >>  -  - gensymed_symbol_1);
		}
		else
		    temp_2 = Nil;
		change_edges_of_block(entity,Nil,Nil,temp_1,temp_2);
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) 
			: Nil;
		if (gensymed_symbol_3)
		    magnify_connections_on_block_in_workspace(entity,
			    x_magnification_qm,y_magnification_qm,Nil,Nil,
			    FIX((SI_Long)0L),FIX((SI_Long)0L),
			    FIX((SI_Long)0L),FIX((SI_Long)0L));
	    }
	    reflection_and_rotation_qm = icon_attributes_plist_qm ? 
		    getf(icon_attributes_plist_qm,Qreflection_and_rotation,
		    _) : Nil;
	    if (reflection_and_rotation_qm) {
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		gensymed_symbol_1 = (SI_Long)1L;
		x_center_of_entity = gensymed_symbol >>  -  - 
			gensymed_symbol_1;
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_3);
		gensymed_symbol_3 = ISVREF(entity,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol_3);
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		gensymed_symbol_1 = (SI_Long)1L;
		y_center_of_entity = gensymed_symbol >>  -  - 
			gensymed_symbol_1;
		change_icon_attribute(entity,Qreflection_and_rotation,Nil);
		reflect_and_rotate_loose_ends_of_block_in_workspace(entity,
			reflection_and_rotation_qm,FIX(x_center_of_entity),
			FIX(y_center_of_entity));
		reflect_and_rotate_block_in_workspace(entity,
			reflection_and_rotation_qm,FIX(x_center_of_entity),
			FIX(y_center_of_entity));
	    }
	    temp_1 = assq_function(Qattribute_displays,
		    ISVREF(class_description,(SI_Long)12L));
	    attribute_display_specs_qm = CDR(temp_1);
	    if (attribute_display_specs_qm) {
		if ( !(EQ(attribute_display_specs_qm,Qnone) || 
			Called_within_clear_text_loading))
		    return make_attribute_displays_per_specs(entity,
			    attribute_display_specs_qm);
		else
		    return VALUES_1(Nil);
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

/* MAKE-ENTITY-WITH-SPECIFIC-ICON-DESCRIPTION */
Object make_entity_with_specific_icon_description varargs_1(int, n)
{
    Object subclass_of_entity, icon_line_drawing_description, width_of_icon;
    Object height_of_icon;
    Object icon_color_qm, icon_background_image_qm, icon_description, entity;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,35);
    INIT_ARGS_nonrelocating();
    subclass_of_entity = REQUIRED_ARG_nonrelocating();
    icon_line_drawing_description = REQUIRED_ARG_nonrelocating();
    width_of_icon = REQUIRED_ARG_nonrelocating();
    height_of_icon = REQUIRED_ARG_nonrelocating();
    icon_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    icon_background_image_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    icon_description = create_icon_description(3,width_of_icon,
	    height_of_icon,icon_line_drawing_description);
    entity = Nil;
    SVREF(icon_description,FIX((SI_Long)13L)) = icon_background_image_qm;
    entity = make_entity(1,subclass_of_entity);
    ISVREF(entity,(SI_Long)16L) = icon_description;
    set_edges_of_block(entity,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    width_of_icon,height_of_icon);
    if (icon_color_qm)
	SVREF(icon_description,FIX((SI_Long)5L)) = icon_color_qm;
    return VALUES_1(entity);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qiconic_entity;      /* iconic-entity */

/* MAKE-ICONIC-ENTITY-WITH-SPECIFIC-ICON-DESCRIPTION */
Object make_iconic_entity_with_specific_icon_description(icon_description,
	    width,height,rotated_p)
    Object icon_description, width, height, rotated_p;
{
    Object orientation, ab_loop_list_, iconic_entity, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(90,36);
    orientation = Nil;
    ab_loop_list_ = rotated_p ? list_constant_1 : list_constant_2;
    iconic_entity = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    orientation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    iconic_entity = make_entity_with_specific_icon_description(4,
	    Qiconic_entity,copy_for_slot_value(icon_description),width,height);
    if (orientation)
	change_icon_attribute(iconic_entity,Qreflection_and_rotation,
		orientation);
    ab_loopvar__2 = graphics_list_2(orientation,iconic_entity);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* RECLAIM-RUBBER-STAMP-WIDGETS */
Object reclaim_rubber_stamp_widgets(plist_of_rubber_stamp_widgets)
    Object plist_of_rubber_stamp_widgets;
{
    x_note_fn_call(90,37);
    return reclaim_graphics_list_1(plist_of_rubber_stamp_widgets);
}

DEFINE_VARIABLE_WITH_SYMBOL(Resize_box_rubber_stamp_widget, Qresize_box_rubber_stamp_widget);

static Object list_constant_3;     /* # */

static Object Qnormal;             /* normal */

static Object Qpending;            /* pending */

static Object Qna;                 /* na */

/* MAKE-TITLE-BAR-WIDGET-ICON-DESCRIPTION */
Object make_title_bar_widget_icon_description(icon_description,
	    pending_icon_description_qm,na_icon_description_qm,width,height)
    Object icon_description, pending_icon_description_qm;
    Object na_icon_description_qm, width, height;
{
    Object situation, ab_loop_list_, iconic_entity, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(90,38);
    situation = Nil;
    ab_loop_list_ = list_constant_3;
    iconic_entity = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    situation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(situation,Qnormal))
	temp = icon_description;
    else if (EQ(situation,Qpending)) {
	temp = pending_icon_description_qm;
	if (temp);
	else
	    temp = icon_description;
    }
    else if (EQ(situation,Qna)) {
	temp = na_icon_description_qm;
	if (temp);
	else
	    temp = icon_description;
    }
    else
	temp = Qnil;
    iconic_entity = make_entity_with_specific_icon_description(4,
	    Qiconic_entity,copy_for_slot_value(temp),width,height);
    ab_loopvar__2 = graphics_list_2(situation,iconic_entity);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Left_scroll_arrow_rubber_stamp_widget, Qleft_scroll_arrow_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Top_scroll_arrow_rubber_stamp_widget, Qtop_scroll_arrow_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Right_scroll_arrow_rubber_stamp_widget, Qright_scroll_arrow_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Bottom_scroll_arrow_rubber_stamp_widget, Qbottom_scroll_arrow_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Scroll_bar_elevator_rubber_stamp_widget, Qscroll_bar_elevator_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Right_marker_for_cascading_menu_rubber_stamp_widget, Qright_marker_for_cascading_menu_rubber_stamp_widget);

DEFINE_VARIABLE_WITH_SYMBOL(Left_marker_for_cascading_menu_rubber_stamp_widget, Qleft_marker_for_cascading_menu_rubber_stamp_widget);

/* DRAW-RUBBER-STAMP-WIDGET */
Object draw_rubber_stamp_widget(frame_widget_name,left_edge_in_workspace,
	    top_edge_in_workspace,right_edge_in_workspace,
	    bottom_edge_in_workspace)
    Object frame_widget_name, left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace;
{
    Object orientation, iconic_entity_of_widget, gensymed_symbol;
    Object left_edge_in_workspace_of_source, top_edge_in_workspace_of_source;
    Object right_edge_in_workspace_of_source;
    Object bottom_edge_in_workspace_of_source, scale, scale_1;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp_1;
    Object dx_source, dx_destination, current_image_x_scale, dy_source;
    Object dy_destination, current_image_y_scale;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long x_in_window, y_in_window, value, gensymed_symbol_3, temp;
    Declare_special(4);

    x_note_fn_call(90,39);
    orientation = Nil;
    iconic_entity_of_widget = 
	    getf(lookup_rubber_stamp_set_of_frame_widget(frame_widget_name),
	    orientation,_);
    if (iconic_entity_of_widget);
    else
	iconic_entity_of_widget = SECOND(Resize_box_rubber_stamp_widget);
    gensymed_symbol = ISVREF(iconic_entity_of_widget,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(iconic_entity_of_widget,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(iconic_entity_of_widget,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(iconic_entity_of_widget,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(left_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    left_edge_in_workspace) && FIXNUM_LT(left_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		left_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_x_scale,
		left_edge_in_workspace));
    x_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(top_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    top_edge_in_workspace) && FIXNUM_LT(top_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		top_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_y_scale,
		top_edge_in_workspace));
    y_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_2 = IFIX(left_edge_in_workspace_of_source);
    scale_1 = Current_image_x_scale;
    value = x_in_window - IFIX(Current_x_origin_of_drawing);
    if (IFIX(scale_1) == (SI_Long)4096L)
	gensymed_symbol_3 = value;
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,FIX(value)));
    else if (value >= (SI_Long)0L) {
	temp = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		(SI_Long)1L)) / IFIX(scale_1);
	gensymed_symbol_3 = temp;
    }
    else {
	temp = (( - value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		(SI_Long)1L)) / IFIX(scale_1);
	temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	gensymed_symbol_3 = temp;
    }
    value = gensymed_symbol_2 - gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    current_x_origin_of_drawing = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	    3);
      gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
      scale = Current_image_y_scale;
      gensymed_symbol_2 = IFIX(top_edge_in_workspace_of_source);
      scale_1 = Current_image_y_scale;
      value = y_in_window - IFIX(Current_y_origin_of_drawing);
      if (IFIX(scale_1) == (SI_Long)4096L)
	  gensymed_symbol_3 = value;
      else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	      value < IFIX(Isqrt_of_most_positive_fixnum)))
	  gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,
		  FIX(value)));
      else if (value >= (SI_Long)0L) {
	  temp = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		  (SI_Long)1L)) / IFIX(scale_1);
	  gensymed_symbol_3 = temp;
      }
      else {
	  temp = (( - value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		  (SI_Long)1L)) / IFIX(scale_1);
	  temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	  gensymed_symbol_3 = temp;
      }
      value = gensymed_symbol_2 - gensymed_symbol_3;
      if (IFIX(scale) == (SI_Long)4096L)
	  gensymed_symbol_2 = value;
      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	      FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	      value < IFIX(Isqrt_of_most_positive_fixnum)) {
	  unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	  gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
      }
      else
	  gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
      current_y_origin_of_drawing = FIX(gensymed_symbol_1 - gensymed_symbol_2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	      2);
	temp_1 = minus(right_edge_in_workspace_of_source,
		left_edge_in_workspace_of_source);
	dx_source = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	temp_1 = minus(right_edge_in_workspace,left_edge_in_workspace);
	dx_destination = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	temp_1 = Current_image_x_scale;
	temp = IFIX(FIXNUM_TIMES(temp_1,
		l_round(FIXNUM_TIMES(convert_to_magnification_at_compile_time(FIX((SI_Long)1L)),
		dx_destination),dx_source))) + (SI_Long)128L;
	current_image_x_scale = FIX(temp >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		1);
	  temp_1 = minus(bottom_edge_in_workspace_of_source,
		  top_edge_in_workspace_of_source);
	  dy_source = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	  temp_1 = minus(bottom_edge_in_workspace,top_edge_in_workspace);
	  dy_destination = FIXNUM_MIN(temp_1,
		  Most_positive_workspace_coordinate);
	  temp_1 = Current_image_y_scale;
	  temp = IFIX(FIXNUM_TIMES(temp_1,
		  l_round(FIXNUM_TIMES(convert_to_magnification_at_compile_time(FIX((SI_Long)1L)),
		  dy_destination),dy_source))) + (SI_Long)128L;
	  current_image_y_scale = FIX(temp >>  -  - (SI_Long)8L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		  0);
	    draw_icon_for_entity(iconic_entity_of_widget);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qright_marker_for_cascading_menu;  /* right-marker-for-cascading-menu */

static Object Qleft_marker_for_cascading_menu;  /* left-marker-for-cascading-menu */

static Object Qgensym_left_scroll_arrow_frame_component;  /* gensym-left-scroll-arrow-frame-component */

static Object Qgensym_up_scroll_arrow_frame_component;  /* gensym-up-scroll-arrow-frame-component */

static Object Qgensym_right_scroll_arrow_frame_component;  /* gensym-right-scroll-arrow-frame-component */

static Object Qgensym_down_scroll_arrow_frame_component;  /* gensym-down-scroll-arrow-frame-component */

static Object Qgensym_resize_box_frame_component;  /* gensym-resize-box-frame-component */

static Object Qgensym_close_box_frame_component;  /* gensym-close-box-frame-component */

static Object Qgensym_scroll_bar_elevator_frame_component;  /* gensym-scroll-bar-elevator-frame-component */

/* LOOKUP-RUBBER-STAMP-SET-OF-FRAME-WIDGET */
Object lookup_rubber_stamp_set_of_frame_widget(frame_widget_name)
    Object frame_widget_name;
{
    x_note_fn_call(90,40);
    if (EQ(frame_widget_name,Qright_marker_for_cascading_menu))
	return VALUES_1(Right_marker_for_cascading_menu_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qleft_marker_for_cascading_menu))
	return VALUES_1(Left_marker_for_cascading_menu_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_left_scroll_arrow_frame_component))
	return VALUES_1(Left_scroll_arrow_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_up_scroll_arrow_frame_component))
	return VALUES_1(Top_scroll_arrow_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_right_scroll_arrow_frame_component))
	return VALUES_1(Right_scroll_arrow_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_down_scroll_arrow_frame_component))
	return VALUES_1(Bottom_scroll_arrow_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_resize_box_frame_component))
	return VALUES_1(Resize_box_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_close_box_frame_component))
	return VALUES_1(Close_box_rubber_stamp_widget);
    else if (EQ(frame_widget_name,Qgensym_scroll_bar_elevator_frame_component))
	return VALUES_1(Scroll_bar_elevator_rubber_stamp_widget);
    else
	return VALUES_1(Resize_box_rubber_stamp_widget);
}

static Object Qblack;              /* black */

static Object Qab_gensym;          /* gensym */

static Object Kxor;                /* :xor */

static Object Qrevise_icon_rendering_of_rubber_stamp;  /* revise-icon-rendering-of-rubber-stamp */

/* CHANGE-COLOR-IN-RUBBER-STAMP */
Object change_color_in_rubber_stamp(workspace,rubber_stamp_entity,
	    left_edge,top_edge,right_edge,bottom_edge,region_to_change,
	    old_color,new_color)
    Object workspace, rubber_stamp_entity, left_edge, top_edge, right_edge;
    Object bottom_edge, region_to_change, old_color, new_color;
{
    Object icon_description, icon_color_pattern_1, region, ab_loop_list_;
    Object current_color_list, ab_loopvar_, ab_loopvar__1, new_color_list;
    Object ab_loopvar__2, ab_loop_desetq_, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, current_drawing_transfer_mode;
    Object last_1, next_qm;
    Declare_special(1);

    x_note_fn_call(90,41);
    icon_description = ISVREF(rubber_stamp_entity,(SI_Long)16L);
    icon_color_pattern_1 = ISVREF(icon_description,(SI_Long)10L);
    region = Nil;
    ab_loop_list_ = icon_color_pattern_1;
    current_color_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    new_color_list = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    temp = EQ(region,region_to_change) ? old_color : Qblack;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__1 = gensymed_symbol;
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	current_color_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    new_cons = ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    temp = EQ(region,region_to_change) ? new_color : Qblack;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__1 = gensymed_symbol;
    if (ab_loopvar__2)
	M_CDR(ab_loopvar__2) = ab_loopvar__1;
    else
	new_color_list = ab_loopvar__1;
    ab_loopvar__2 = ab_loopvar__1;
    goto next_loop;
  end_loop:
    current_drawing_transfer_mode = Kxor;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    0);
      update_images(16,Nil,rubber_stamp_entity,workspace,left_edge,
	      top_edge,right_edge,bottom_edge,Nil,
	      Qrevise_icon_rendering_of_rubber_stamp,rubber_stamp_entity,
	      left_edge,top_edge,right_edge,bottom_edge,current_color_list,
	      new_color_list);
      if (current_color_list) {
	  last_1 = current_color_list;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qab_gensym);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qab_gensym);
	  if (ISVREF(Available_gensym_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_gensym_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = current_color_list;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = last_1;
	  }
	  else {
	      temp = Available_gensym_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = current_color_list;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = last_1;
	  }
	  M_CDR(last_1) = Nil;
      }
      if (new_color_list) {
	  last_1 = new_color_list;
	  next_qm = Nil;
	next_loop_2:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_2;
	  inline_note_reclaim_cons(last_1,Qab_gensym);
	  last_1 = next_qm;
	  goto next_loop_2;
	end_loop_2:
	  inline_note_reclaim_cons(last_1,Qab_gensym);
	  if (ISVREF(Available_gensym_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_gensym_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = new_color_list;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = last_1;
	  }
	  else {
	      temp = Available_gensym_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = new_color_list;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = last_1;
	  }
	  M_CDR(last_1) = Nil;
      }
    POP_SPECIAL();
    return VALUES_1(Qnil);
}

/* REVISE-ICON-RENDERING-OF-RUBBER-STAMP */
Object revise_icon_rendering_of_rubber_stamp(rubber_stamp_entity,left_edge,
	    top_edge,right_edge,bottom_edge,current_color_list,new_color_list)
    Object rubber_stamp_entity, left_edge, top_edge, right_edge, bottom_edge;
    Object current_color_list, new_color_list;
{
    Object gensymed_symbol, left_edge_in_workspace_of_source;
    Object top_edge_in_workspace_of_source, right_edge_in_workspace_of_source;
    Object bottom_edge_in_workspace_of_source, scale, scale_1;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp_1;
    Object dx_source, dx_destination, current_image_x_scale, dy_source;
    Object dy_destination, current_image_y_scale;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long x_in_window, y_in_window, value, gensymed_symbol_3, temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(90,42);
    gensymed_symbol = ISVREF(rubber_stamp_entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(rubber_stamp_entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(rubber_stamp_entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol = ISVREF(rubber_stamp_entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge_in_workspace_of_source = gensymed_symbol;
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(left_edge);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left_edge) && 
	    FIXNUM_LT(left_edge,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		left_edge)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_x_scale,
		left_edge));
    x_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(top_edge);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top_edge) && 
	    FIXNUM_LT(top_edge,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		top_edge)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_y_scale,
		top_edge));
    y_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_2 = IFIX(left_edge_in_workspace_of_source);
    scale_1 = Current_image_x_scale;
    value = x_in_window - IFIX(Current_x_origin_of_drawing);
    if (IFIX(scale_1) == (SI_Long)4096L)
	gensymed_symbol_3 = value;
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,FIX(value)));
    else if (value >= (SI_Long)0L) {
	temp = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		(SI_Long)1L)) / IFIX(scale_1);
	gensymed_symbol_3 = temp;
    }
    else {
	temp = (( - value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		(SI_Long)1L)) / IFIX(scale_1);
	temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	gensymed_symbol_3 = temp;
    }
    value = gensymed_symbol_2 - gensymed_symbol_3;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    current_x_origin_of_drawing = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	    3);
      gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
      scale = Current_image_y_scale;
      gensymed_symbol_2 = IFIX(top_edge_in_workspace_of_source);
      scale_1 = Current_image_y_scale;
      value = y_in_window - IFIX(Current_y_origin_of_drawing);
      if (IFIX(scale_1) == (SI_Long)4096L)
	  gensymed_symbol_3 = value;
      else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	      value < IFIX(Isqrt_of_most_positive_fixnum)))
	  gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,
		  FIX(value)));
      else if (value >= (SI_Long)0L) {
	  temp = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		  (SI_Long)1L)) / IFIX(scale_1);
	  gensymed_symbol_3 = temp;
      }
      else {
	  temp = (( - value << (SI_Long)12L) + (IFIX(scale_1) >>  -  - 
		  (SI_Long)1L)) / IFIX(scale_1);
	  temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	  gensymed_symbol_3 = temp;
      }
      value = gensymed_symbol_2 - gensymed_symbol_3;
      if (IFIX(scale) == (SI_Long)4096L)
	  gensymed_symbol_2 = value;
      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	      FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	      value < IFIX(Isqrt_of_most_positive_fixnum)) {
	  unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	  gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
      }
      else
	  gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
      current_y_origin_of_drawing = FIX(gensymed_symbol_1 - gensymed_symbol_2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	      2);
	temp_1 = minus(right_edge_in_workspace_of_source,
		left_edge_in_workspace_of_source);
	dx_source = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	temp_1 = minus(right_edge,left_edge);
	dx_destination = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	temp_1 = Current_image_x_scale;
	temp = IFIX(FIXNUM_TIMES(temp_1,
		l_round(FIXNUM_TIMES(convert_to_magnification_at_compile_time(FIX((SI_Long)1L)),
		dx_destination),dx_source))) + (SI_Long)128L;
	current_image_x_scale = FIX(temp >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		1);
	  temp_1 = minus(bottom_edge_in_workspace_of_source,
		  top_edge_in_workspace_of_source);
	  dy_source = FIXNUM_MIN(temp_1,Most_positive_workspace_coordinate);
	  temp_1 = minus(bottom_edge,top_edge);
	  dy_destination = FIXNUM_MIN(temp_1,
		  Most_positive_workspace_coordinate);
	  temp_1 = Current_image_y_scale;
	  temp = IFIX(FIXNUM_TIMES(temp_1,
		  l_round(FIXNUM_TIMES(convert_to_magnification_at_compile_time(FIX((SI_Long)1L)),
		  dy_destination),dy_source))) + (SI_Long)128L;
	  current_image_y_scale = FIX(temp >>  -  - (SI_Long)8L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		  0);
	    result = revise_icon_rendering(rubber_stamp_entity,
		    current_color_list,new_color_list,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

static Object Qadd_icon_rendering;  /* add-icon-rendering */

/* DRAW-ICON */
Object draw_icon(left_edge_for_icon_in_workspace,
	    top_edge_for_icon_in_workspace,icon_description,
	    icon_attributes_plist,
	    foreground_color_difference_or_differences,
	    background_color_value_or_values)
    Object left_edge_for_icon_in_workspace, top_edge_for_icon_in_workspace;
    Object icon_description, icon_attributes_plist;
    Object foreground_color_difference_or_differences;
    Object background_color_value_or_values;
{
    Object icon_rendering, atomic_background_color_value_qm, color_value;
    Object old_color_value, current_background_color_value, color_value_1;
    Object ab_loop_list_, p, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object working_color_difference_list, color_difference;
    Object remaining_background_color_values_qm, ab_loop_iter_flag_;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left_edge_in_window, top_edge_in_window, right_edge_in_window;
    SI_Long bottom_edge_in_window, color_meaning_transparent;
    char temp;
    Declare_special(1);

    x_note_fn_call(90,43);
    icon_rendering = get_or_make_icon_rendering(icon_description,
	    icon_attributes_plist);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(left_edge_for_icon_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    left_edge_for_icon_in_workspace) && 
	    FIXNUM_LT(left_edge_for_icon_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		left_edge_for_icon_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		left_edge_for_icon_in_workspace));
    left_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(top_edge_for_icon_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    top_edge_for_icon_in_workspace) && 
	    FIXNUM_LT(top_edge_for_icon_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		top_edge_for_icon_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		top_edge_for_icon_in_workspace));
    top_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    right_edge_in_window = left_edge_in_window + 
	    IFIX(ISVREF(icon_rendering,(SI_Long)10L));
    bottom_edge_in_window = top_edge_in_window + 
	    IFIX(ISVREF(icon_rendering,(SI_Long)11L));
    atomic_background_color_value_qm = 
	    ATOM(background_color_value_or_values) ? 
	    background_color_value_or_values : Nil;
    color_meaning_transparent = EQ(Current_drawing_transfer_mode,
	    Kpaint_infered_from_xor) ? IFIX(Transparent_color_value) : 
	    (SI_Long)0L;
    color_value = atomic_background_color_value_qm;
    if (color_value);
    else
	color_value = FIRST(background_color_value_or_values);
    old_color_value = Current_background_color_value;
    current_background_color_value = Current_background_color_value;
    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
	    0);
      set_current_background_color_value(color_value);
      temp = TRUEP(atomic_background_color_value_qm);
      if (temp);
      else {
	  color_value_1 = Nil;
	  ab_loop_list_ = CDR(background_color_value_or_values);
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  color_value_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !FIXNUM_EQ(FIRST(background_color_value_or_values),
		  color_value_1)) {
	      temp = TRUEP(Nil);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp = TRUEP(T);
	  goto end_1;
	  temp = TRUEP(Qnil);
	end_1:;
      }
      if (temp)
	  draw_graphic_element(7,Qadd_icon_rendering,
		  FIX(left_edge_in_window),FIX(top_edge_in_window),
		  FIX(right_edge_in_window),FIX(bottom_edge_in_window),
		  foreground_color_difference_or_differences,icon_rendering);
      else {
	  p = foreground_color_difference_or_differences;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_1:
	  if ( !TRUEP(p))
	      goto end_loop_1;
	  ab_loopvar__2 = slot_value_cons_1(FIX(color_meaning_transparent),
		  Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  p = M_CDR(p);
	  goto next_loop_1;
	end_loop_1:
	  working_color_difference_list = ab_loopvar_;
	  goto end_2;
	  working_color_difference_list = Qnil;
	end_2:;
	  p = working_color_difference_list;
	  color_difference = Nil;
	  ab_loop_list_ = foreground_color_difference_or_differences;
	  remaining_background_color_values_qm = 
		  CDR(background_color_value_or_values);
	  ab_loop_iter_flag_ = T;
	next_loop_2:
	  if ( !TRUEP(p))
	      goto end_loop_2;
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  color_difference = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      remaining_background_color_values_qm = 
		      CDR(remaining_background_color_values_qm);
	  if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) 
		  ? FIXNUM_EQ(color_difference,Transparent_color_value) : 
		  IFIX(color_difference) == (SI_Long)0L || 
		  FIXNUM_EQ(color_difference,Transparent_color_value))) {
	      M_CAR(p) = color_difference;
	      draw_graphic_element(7,Qadd_icon_rendering,
		      FIX(left_edge_in_window),FIX(top_edge_in_window),
		      FIX(right_edge_in_window),FIX(bottom_edge_in_window),
		      working_color_difference_list,icon_rendering);
	      M_CAR(p) = FIX(color_meaning_transparent);
	  }
	  if (remaining_background_color_values_qm)
	      set_current_background_color_value(FIRST(remaining_background_color_values_qm));
	  ab_loop_iter_flag_ = Nil;
	  p = M_CDR(p);
	  goto next_loop_2;
	end_loop_2:
	  reclaim_slot_value_list_1(working_color_difference_list);
      }
      set_current_background_color_value(old_color_value);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qwhite;              /* white */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qicp;                /* icp */

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

static Object Qlight_grey;         /* light-grey */

static Object Qdim_grey;           /* dim-grey */

static Object Qpaint_icon_background_image;  /* paint-icon-background-image */

/* DRAW-BACKGROUND-IMAGE-FOR-ENTITY */
Object draw_background_image_for_entity(image_data,
	    left_offset_in_workspace,top_offset_in_workspace,
	    rotated_width_in_workspace,rotated_height_in_workspace,x_scale,
	    y_scale,reflection_and_rotation,left,top,right,bottom,
	    block_is_currently_being_dragged_p)
    Object image_data, left_offset_in_workspace, top_offset_in_workspace;
    Object rotated_width_in_workspace, rotated_height_in_workspace, x_scale;
    Object y_scale, reflection_and_rotation, left, top, right, bottom;
    Object block_is_currently_being_dragged_p;
{
    Object support_icon_image_painting_qm, color_or_metacolor;
    Object background_color_or_metacolor, foreground_color_value, clipped_left;
    Object clipped_top, clipped_right, clipped_bottom, x_bleed_width;
    Object y_bleed_width, temp, temp_1, temp_2, temp_3;
    Object x_scale_of_graphic_element, y_scale_of_graphic_element;
    Object rotation_of_graphic_element, quality_of_graphic_element;
    Object foreground_color_value_of_graphic_element;
    Object background_color_value_of_graphic_element;
    Object x_in_window_of_graphic_element, y_in_window_of_graphic_element;
    Declare_special(8);
    Object result;

    x_note_fn_call(90,44);
    support_icon_image_painting_qm = printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_polychrome_icon_images,
	    ISVREF(Current_window,(SI_Long)11L)) ? 
	    window_supports_painting_this_image_data(Current_window,
	    image_data) : Qnil;
    if (BOUNDP(Qcurrent_image_plane)) {
	color_or_metacolor = ISVREF(Current_image_plane,(SI_Long)5L) ? 
		ISVREF(ISVREF(Current_image_plane,(SI_Long)5L),
		(SI_Long)22L) : Nil;
	if (color_or_metacolor);
	else
	    color_or_metacolor = Qblack;
	if (EQ(color_or_metacolor,Qtransparent) || EQ(color_or_metacolor,
		Qbackground)) {
	    background_color_or_metacolor = ISVREF(Current_image_plane,
		    (SI_Long)5L) ? ISVREF(ISVREF(Current_image_plane,
		    (SI_Long)5L),(SI_Long)21L) : Nil;
	    if (background_color_or_metacolor);
	    else
		background_color_or_metacolor = Qwhite;
	    if (EQ(background_color_or_metacolor,Qforeground) || 
		    EQ(background_color_or_metacolor,Qworkspace_foreground)) {
		foreground_color_value = ISVREF(Current_color_map,(SI_Long)4L);
		if (foreground_color_value);
		else
		    foreground_color_value = map_to_color_value_1(Qblack);
	    }
	    else if (EQ(background_color_or_metacolor,Qtransparent) || 
		    EQ(background_color_or_metacolor,Qbackground)) {
		foreground_color_value = ISVREF(Current_color_map,(SI_Long)5L);
		if (foreground_color_value);
		else
		    foreground_color_value = map_to_color_value_1(Qwhite);
	    }
	    else
		foreground_color_value = EQ(background_color_or_metacolor,
			ISVREF(Current_color_map,(SI_Long)6L)) ? 
			ISVREF(Current_color_map,(SI_Long)7L) : 
			map_to_color_value_1(background_color_or_metacolor);
	}
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground)) {
	    foreground_color_value = ISVREF(Current_color_map,(SI_Long)4L);
	    if (foreground_color_value);
	    else
		foreground_color_value = map_to_color_value_1(Qblack);
	}
	else
	    foreground_color_value = EQ(color_or_metacolor,
		    ISVREF(Current_color_map,(SI_Long)6L)) ? 
		    ISVREF(Current_color_map,(SI_Long)7L) : 
		    map_to_color_value_1(color_or_metacolor);
    }
    else
	foreground_color_value = Current_foreground_color_value;
    clipped_left = FIXNUM_MAX(Left_edge_of_draw_area,left);
    clipped_top = FIXNUM_MAX(Top_edge_of_draw_area,top);
    clipped_right = FIXNUM_MIN(Right_edge_of_draw_area,right);
    clipped_bottom = FIXNUM_MIN(Bottom_edge_of_draw_area,bottom);
    x_bleed_width = FIX((SI_Long)1L);
    y_bleed_width = FIX((SI_Long)1L);
    if (EQ(ISVREF(Current_window,(SI_Long)1L),Qicp) && 
	    (printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_scrolling,
	    ISVREF(Current_window,(SI_Long)11L))) && 
	    support_icon_image_painting_qm) {
	if ( !TRUEP(finished_transmitting_image_data_p(image_data))) {
	    if (icp_connection_open_p(Current_icp_socket))
		send_all_image_data(image_data);
	}
    }
    if (block_is_currently_being_dragged_p ||  
	    !TRUEP(support_icon_image_painting_qm) || 
	    EQ(ISVREF(Current_window,(SI_Long)1L),Qicp) && ( 
	    !TRUEP(icp_connection_open_p(Current_icp_socket)) ||  
	    !TRUEP(finished_transmitting_image_data_p(image_data)))) {
	temp = FIXNUM_SUB1(right);
	temp_1 = FIXNUM_SUB1(bottom);
	draw_graphic_element(6,Qadd_solid_rectangle,left,top,temp,temp_1,
		EQ(Qlight_grey,ISVREF(Current_color_map,(SI_Long)6L)) ? 
		ISVREF(Current_color_map,(SI_Long)7L) : 
		map_to_color_value_1(Qlight_grey));
	temp_2 = FIXNUM_ADD1(left);
	temp_3 = FIXNUM_ADD1(top);
	temp_1 = FIXNUM_SUB1(right);
	temp = FIXNUM_SUB1(bottom);
	return draw_rectangle_outline_in_window(temp_2,temp_3,temp_1,temp,
		EQ(Qdim_grey,ISVREF(Current_color_map,(SI_Long)6L)) ? 
		ISVREF(Current_color_map,(SI_Long)7L) : 
		map_to_color_value_1(Qdim_grey),FIX((SI_Long)1L),
		FIX((SI_Long)1L));
    }
    else {
	if ( !(IFIX(x_scale) >= (SI_Long)4096L))
	    x_bleed_width = FIX((SI_Long)2L);
	if ( !(IFIX(y_scale) >= (SI_Long)4096L))
	    y_bleed_width = FIX((SI_Long)2L);
	x_scale_of_graphic_element = x_scale;
	y_scale_of_graphic_element = y_scale;
	rotation_of_graphic_element = reflection_and_rotation;
	quality_of_graphic_element = Nil;
	foreground_color_value_of_graphic_element = foreground_color_value;
	background_color_value_of_graphic_element = 
		Current_background_color_value;
	x_in_window_of_graphic_element = left;
	y_in_window_of_graphic_element = top;
	PUSH_SPECIAL_WITH_SYMBOL(Y_in_window_of_graphic_element,Qy_in_window_of_graphic_element,y_in_window_of_graphic_element,
		7);
	  PUSH_SPECIAL_WITH_SYMBOL(X_in_window_of_graphic_element,Qx_in_window_of_graphic_element,x_in_window_of_graphic_element,
		  6);
	    PUSH_SPECIAL_WITH_SYMBOL(Background_color_value_of_graphic_element,Qbackground_color_value_of_graphic_element,background_color_value_of_graphic_element,
		    5);
	      PUSH_SPECIAL_WITH_SYMBOL(Foreground_color_value_of_graphic_element,Qforeground_color_value_of_graphic_element,foreground_color_value_of_graphic_element,
		      4);
		PUSH_SPECIAL_WITH_SYMBOL(Quality_of_graphic_element,Qquality_of_graphic_element,quality_of_graphic_element,
			3);
		  PUSH_SPECIAL_WITH_SYMBOL(Rotation_of_graphic_element,Qrotation_of_graphic_element,rotation_of_graphic_element,
			  2);
		    PUSH_SPECIAL_WITH_SYMBOL(Y_scale_of_graphic_element,Qy_scale_of_graphic_element,y_scale_of_graphic_element,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(X_scale_of_graphic_element,Qx_scale_of_graphic_element,x_scale_of_graphic_element,
			      0);
			result = draw_graphic_element(10,
				Qpaint_icon_background_image,clipped_left,
				clipped_top,clipped_right,clipped_bottom,
				image_data,left_offset_in_workspace,
				top_offset_in_workspace,
				FIXNUM_ADD(rotated_width_in_workspace,
				x_bleed_width),
				FIXNUM_ADD(rotated_height_in_workspace,
				y_bleed_width));
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
}

/* DRAW-ICON-FOR-ENTITY */
Object draw_icon_for_entity(entity)
    Object entity;
{
    Object icon_description_qm, temp, gensymed_symbol, temp_1, temp_2, temp_3;

    x_note_fn_call(90,45);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	temp = ISVREF(entity,(SI_Long)17L);
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp_1 = gensymed_symbol;
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp_2 = gensymed_symbol;
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp_3 = gensymed_symbol;
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	draw_icon_from_description(icon_description_qm,temp,temp_1,temp_2,
		temp_3,gensymed_symbol,(SI_Long)0L != (IFIX(ISVREF(entity,
		(SI_Long)5L)) & (SI_Long)2048L) ? T : Nil);
    }
    return VALUES_1(Nil);
}

static Object Qeditor_scaling;     /* editor-scaling */

static Object Kbleeding_on_all_sides;  /* :bleeding-on-all-sides */

/* DRAW-ICON-FROM-DESCRIPTION */
Object draw_icon_from_description(icon_description,icon_attributes_plist,
	    block_left,block_top,block_right,block_bottom,
	    block_is_currently_being_dragged_p)
    Object icon_description, icon_attributes_plist, block_left, block_top;
    Object block_right, block_bottom, block_is_currently_being_dragged_p;
{
    Object background_layer, temp, background_image_spec, editor_scaling;
    Object background_image_name, background_image_x_y, background_image;
    Object computed_values_plist, line_drawing_description, default_variables;
    Object reflection_and_rotation, rotated_by_90_p_1, x_magnification_qm;
    Object y_magnification_qm, rotated_x_magnification_qm;
    Object rotated_y_magnification_qm, icon_color_pattern_qm;
    Object line_color_from_plist_qm, icon_foreground_color_qm;
    Object line_color_or_colors_qm, new_metacolor, old_metacolor;
    Object color_value_1, color_value_2, generalized_color_differences;
    Object region_name, color, ab_loop_list_, real_color, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol, right, bottom;
    Object bleeding_hack, image_plane, left_edge_of_workspace_area_within_pane;
    Object top_edge_of_workspace_area_within_pane;
    Object right_edge_of_workspace_area_within_pane;
    Object bottom_edge_of_workspace_area_within_pane, reduced_scale_p;
    Object full_scale_p, left_or_top_extension_for_bleeding_1;
    Object right_or_bottom_extension_for_bleeding_1, temp_3, scale, value;
    Object temp_4, temp_5, temp_6, right_in_window, bottom_in_window;
    Object current_icon_untransformed_width, current_icon_untransformed_height;
    Object current_icon_variables_plist, current_icon_variables_override_plist;
    Object left_offset_in_workspace, top_offset_in_workspace, editor_x_scale;
    Object editor_y_scale, current_x_scale, current_y_scale;
    Object rotated_width_in_workspace, rotated_height_in_workspace;
    Object old_color_value, current_background_color_value, color_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result, left, top;
    SI_Long left_star, top_star, gensymed_symbol_3, width_star, height_star;
    char temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(90,46);
    background_layer = ISVREF(icon_description,(SI_Long)13L);
    if (CONSP(background_layer)) {
	temp = SECOND(background_layer);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    background_image_spec = (temp_1 ? EQ(CAADR(background_layer),
	    Qeditor_scaling) : TRUEP(Nil)) ? CAR(background_layer) : 
	    background_layer;
    editor_scaling =  !EQ(background_image_spec,background_layer) ? 
	    CDADR(background_layer) : Nil;
    background_image_name = CONSP(background_image_spec) && 
	    EQ(FIRST(background_image_spec),Qimage) ? 
	    CADR(background_image_spec) : Nil;
    background_image_x_y = CONSP(background_image_spec) && 
	    EQ(FIRST(background_image_spec),Qimage) ? 
	    CADDR(background_image_spec) : Nil;
    background_image = find_image_data(background_image_name);
    computed_values_plist = get_computed_values_plist(icon_attributes_plist);
    line_drawing_description = ISVREF(icon_description,(SI_Long)8L);
    temp = get_variable_specification_if_any(line_drawing_description);
    default_variables = CDR(temp);
    reflection_and_rotation = 
	    getfq_function_no_default(icon_attributes_plist,
	    Qreflection_and_rotation);
    rotated_by_90_p_1 = rotated_by_90_p(reflection_and_rotation);
    x_magnification_qm = getfq_function_no_default(icon_attributes_plist,
	    Qx_magnification);
    y_magnification_qm = getfq_function_no_default(icon_attributes_plist,
	    Qy_magnification);
    rotated_x_magnification_qm = rotated_by_90_p_1 ? y_magnification_qm : 
	    x_magnification_qm;
    rotated_y_magnification_qm = rotated_by_90_p_1 ? x_magnification_qm : 
	    y_magnification_qm;
    icon_color_pattern_qm = ISVREF(icon_description,(SI_Long)10L);
    line_color_from_plist_qm = icon_attributes_plist ? 
	    getfq_function_no_default(icon_attributes_plist,Qline_color) : Nil;
    icon_foreground_color_qm = line_color_from_plist_qm;
    if (icon_foreground_color_qm);
    else
	icon_foreground_color_qm = ISVREF(icon_description,(SI_Long)5L);
    if (icon_color_pattern_qm) {
	line_color_or_colors_qm = icon_attributes_plist ? 
		getfq_function_no_default(icon_attributes_plist,
		Qicon_color_pattern) : Nil;
	if (line_color_or_colors_qm);
	else
	    line_color_or_colors_qm = icon_color_pattern_qm;
    }
    else
	line_color_or_colors_qm = icon_foreground_color_qm;
    if (ATOM(line_color_or_colors_qm)) {
	new_metacolor = line_color_or_colors_qm;
	if (new_metacolor);
	else
	    new_metacolor = Qforeground;
	old_metacolor = Qbackground;
	if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
	    if (EQ(new_metacolor,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(new_metacolor,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(new_metacolor);
	    if (EQ(old_metacolor,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(old_metacolor,Qforeground) || EQ(old_metacolor,
		    Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(old_metacolor,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(old_metacolor);
	    generalized_color_differences = FIXNUM_LOGXOR(color_value_1,
		    color_value_2);
	}
	else if (EQ(new_metacolor,old_metacolor))
	    generalized_color_differences = 
		    EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(new_metacolor,Qtransparent))
	    generalized_color_differences = 
		    EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(old_metacolor,Qtransparent)) {
	    if (EQ(new_metacolor,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(new_metacolor,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(new_metacolor);
	    generalized_color_differences = FIXNUM_LOGXOR(color_value_1,
		    Current_background_color_value);
	}
	else {
	    if (EQ(new_metacolor,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(new_metacolor,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(new_metacolor);
	    if (EQ(old_metacolor,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(old_metacolor,Qforeground) || EQ(old_metacolor,
		    Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(old_metacolor,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(old_metacolor);
	    generalized_color_differences = FIXNUM_LOGXOR(color_value_1,
		    color_value_2);
	}
    }
    else {
	region_name = Nil;
	color = Nil;
	ab_loop_list_ = line_color_or_colors_qm;
	real_color = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	region_name = CAR(ab_loop_desetq_);
	color = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = EQ(color,Qforeground) ? icon_foreground_color_qm : Nil;
	if (temp);
	else
	    temp = color;
	real_color = temp;
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
	    if (EQ(real_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(real_color,Qforeground) || EQ(real_color,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(real_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(real_color);
	    if (EQ(Qbackground,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
		    Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(Qbackground,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(Qbackground);
	    temp_2 = FIXNUM_LOGXOR(color_value_1,color_value_2);
	}
	else if (EQ(real_color,Qbackground))
	    temp_2 = EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(real_color,Qtransparent))
	    temp_2 = EQ(Current_drawing_transfer_mode,
		    Kpaint_infered_from_xor) ? Transparent_color_value : 
		    FIX((SI_Long)0L);
	else if (EQ(Qbackground,Qtransparent)) {
	    if (EQ(real_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(real_color,Qforeground) || EQ(real_color,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(real_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(real_color);
	    temp_2 = FIXNUM_LOGXOR(color_value_1,
		    Current_background_color_value);
	}
	else {
	    if (EQ(real_color,Qbackground))
		color_value_1 = Current_background_color_value;
	    else if (EQ(real_color,Qforeground) || EQ(real_color,
		    Qworkspace_foreground))
		color_value_1 = Current_foreground_color_value;
	    else if (EQ(real_color,Qtransparent))
		color_value_1 = Current_background_color_value;
	    else
		color_value_1 = map_to_color_value(real_color);
	    if (EQ(Qbackground,Qbackground))
		color_value_2 = Current_background_color_value;
	    else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
		    Qworkspace_foreground))
		color_value_2 = Current_foreground_color_value;
	    else if (EQ(Qbackground,Qtransparent))
		color_value_2 = Current_background_color_value;
	    else
		color_value_2 = map_to_color_value(Qbackground);
	    temp_2 = FIXNUM_LOGXOR(color_value_1,color_value_2);
	}
	M_CAR(gensymed_symbol) = temp_2;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	generalized_color_differences = ab_loopvar_;
	goto end_1;
	generalized_color_differences = Qnil;
      end_1:;
    }
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(block_left);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,block_left) 
	    && FIXNUM_LT(block_left,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		block_left)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_x_scale,
		block_left));
    left = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(block_top);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,block_top) && 
	    FIXNUM_LT(block_top,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		block_top)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_y_scale,
		block_top));
    top = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(block_right);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,block_right) 
	    && FIXNUM_LT(block_right,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		block_right)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_x_scale,
		block_right));
    right = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(block_bottom);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,block_bottom) 
	    && FIXNUM_LT(block_bottom,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		block_bottom)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(Current_image_y_scale,
		block_bottom));
    bottom = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    if (BOUNDP(Qcurrent_image_plane)) {
	bleeding_hack = Kbleeding_on_all_sides;
	image_plane = Current_image_plane;
	left_edge_of_workspace_area_within_pane = 
		left_edge_within_pane(ISVREF(image_plane,(SI_Long)19L),
		image_plane);
	top_edge_of_workspace_area_within_pane = 
		top_edge_within_pane(ISVREF(image_plane,(SI_Long)20L),
		image_plane);
	right_edge_of_workspace_area_within_pane = 
		right_edge_within_pane(ISVREF(image_plane,(SI_Long)21L),
		image_plane);
	bottom_edge_of_workspace_area_within_pane = 
		bottom_edge_within_pane(ISVREF(image_plane,(SI_Long)22L),
		image_plane);
	reduced_scale_p = IFIX(ISVREF(image_plane,(SI_Long)11L)) < 
		(SI_Long)4096L ? T : Nil;
	if (reduced_scale_p);
	else
	    reduced_scale_p = IFIX(ISVREF(image_plane,(SI_Long)12L)) < 
		    (SI_Long)4096L ? T : Nil;
	full_scale_p = IFIX(ISVREF(image_plane,(SI_Long)11L)) == 
		(SI_Long)4096L ? (IFIX(ISVREF(image_plane,(SI_Long)12L)) 
		== (SI_Long)4096L ? T : Nil) : Qnil;
	left_or_top_extension_for_bleeding_1 = 
		left_or_top_extension_for_bleeding(bleeding_hack,
		full_scale_p,reduced_scale_p);
	right_or_bottom_extension_for_bleeding_1 = 
		right_or_bottom_extension_for_bleeding(bleeding_hack,
		full_scale_p,reduced_scale_p);
	gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(block_left);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		block_left) && FIXNUM_LT(block_left,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    block_left)) + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(Current_image_x_scale,
		    block_left));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(left_or_top_extension_for_bleeding_1);
	left_star = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(block_top);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		block_top) && FIXNUM_LT(block_top,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    block_top)) + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(Current_image_y_scale,
		    block_top));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(left_or_top_extension_for_bleeding_1);
	top_star = gensymed_symbol_1 - gensymed_symbol_2;
	scale = ISVREF(image_plane,(SI_Long)11L);
	value = FIXNUM_MINUS(FIXNUM_ADD1(block_right),block_left);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	gensymed_symbol_2 = IFIX(left_or_top_extension_for_bleeding_1);
	gensymed_symbol_3 = IFIX(right_or_bottom_extension_for_bleeding_1);
	width_star = gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3;
	scale = ISVREF(image_plane,(SI_Long)12L);
	value = FIXNUM_MINUS(FIXNUM_ADD1(block_bottom),block_top);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	gensymed_symbol_2 = IFIX(left_or_top_extension_for_bleeding_1);
	gensymed_symbol_3 = IFIX(right_or_bottom_extension_for_bleeding_1);
	height_star = gensymed_symbol_1 + gensymed_symbol_2 + 
		gensymed_symbol_3;
	temp_4 = FIX(MAX(left_star,
		IFIX(left_edge_of_workspace_area_within_pane)));
	temp_5 = FIX(MAX(top_star,
		IFIX(top_edge_of_workspace_area_within_pane)));
	gensymed_symbol_1 = left_star + width_star;
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = FIXNUM_ADD1(block_right);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(scale,value));
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_3 = IFIX(right_or_bottom_extension_for_bleeding_1);
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	gensymed_symbol_2 = IFIX(right_edge_of_workspace_area_within_pane);
	temp_6 = FIX(MIN(gensymed_symbol_1,gensymed_symbol_2));
	gensymed_symbol_1 = top_star + height_star;
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = FIXNUM_ADD1(block_bottom);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(scale,value));
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_3 = IFIX(right_or_bottom_extension_for_bleeding_1);
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	gensymed_symbol_2 = IFIX(bottom_edge_of_workspace_area_within_pane);
	temp = FIX(MIN(gensymed_symbol_1,gensymed_symbol_2));
	result = VALUES_4(temp_4,temp_5,temp_6,temp);
	MVS_4(result,temp,temp,right_in_window,bottom_in_window);
	right = right_in_window;
	bottom = bottom_in_window;
    }
    if (background_image) {
	current_icon_untransformed_width = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
		3);
	  current_icon_untransformed_height = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
		  2);
	    current_icon_variables_plist = default_variables;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
		    1);
	      current_icon_variables_override_plist = computed_values_plist;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
		      0);
		left_offset_in_workspace = 
			FIXNUMP(FIRST(background_image_x_y)) ? 
			FIRST(background_image_x_y) : 
			simple_eval_for_icon(FIRST(background_image_x_y));
		if (left_offset_in_workspace);
		else
		    left_offset_in_workspace = FIX((SI_Long)0L);
		top_offset_in_workspace = 
			FIXNUMP(SECOND(background_image_x_y)) ? 
			SECOND(background_image_x_y) : 
			simple_eval_for_icon(SECOND(background_image_x_y));
		if (top_offset_in_workspace);
		else
		    top_offset_in_workspace = FIX((SI_Long)0L);
		editor_x_scale = CAR(editor_scaling);
		editor_y_scale = SECOND(editor_scaling);
		current_x_scale = Current_image_x_scale;
		current_y_scale = Current_image_y_scale;
		rotated_width_in_workspace = rotated_x_magnification_qm ? 
			inverse_magnify(FIXNUM_MINUS(block_right,
			block_left),rotated_x_magnification_qm) : 
			FIXNUM_MINUS(block_right,block_left);
		rotated_height_in_workspace = rotated_y_magnification_qm ? 
			inverse_magnify(FIXNUM_MINUS(block_bottom,
			block_top),rotated_y_magnification_qm) : 
			FIXNUM_MINUS(block_bottom,block_top);
		if (editor_scaling) {
		    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			current_x_scale = editor_x_scale;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    Current_image_x_scale) && 
			    FIXNUM_LT(Current_image_x_scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    editor_x_scale) && FIXNUM_LT(editor_x_scale,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = 
				IFIX(FIXNUM_TIMES(Current_image_x_scale,
				editor_x_scale)) + (SI_Long)2048L;
			current_x_scale = FIX(unshifted_result >>  -  - 
				(SI_Long)12L);
		    }
		    else
			current_x_scale = 
				scalef_function(Current_image_x_scale,
				editor_x_scale);
		    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			current_y_scale = editor_y_scale;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    Current_image_y_scale) && 
			    FIXNUM_LT(Current_image_y_scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    editor_y_scale) && FIXNUM_LT(editor_y_scale,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = 
				IFIX(FIXNUM_TIMES(Current_image_y_scale,
				editor_y_scale)) + (SI_Long)2048L;
			current_y_scale = FIX(unshifted_result >>  -  - 
				(SI_Long)12L);
		    }
		    else
			current_y_scale = 
				scalef_function(Current_image_y_scale,
				editor_y_scale);
		}
		current_x_scale = rotated_x_magnification_qm ? 
			FIX(IFIX(FIXNUM_TIMES(current_x_scale,
			rotated_x_magnification_qm)) + (SI_Long)128L >>  - 
			 - (SI_Long)8L) : current_x_scale;
		current_y_scale = rotated_y_magnification_qm ? 
			FIX(IFIX(FIXNUM_TIMES(current_y_scale,
			rotated_y_magnification_qm)) + (SI_Long)128L >>  - 
			 - (SI_Long)8L) : current_y_scale;
		draw_background_image_for_entity(background_image,
			left_offset_in_workspace,top_offset_in_workspace,
			rotated_width_in_workspace,
			rotated_height_in_workspace,current_x_scale,
			current_y_scale,reflection_and_rotation,FIX(left),
			FIX(top),right,bottom,
			block_is_currently_being_dragged_p);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else if (background_layer && SYMBOLP(background_layer)) {
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(Current_background_color_value);
	  color_qm = EQ(background_layer,Qforeground) || 
		  EQ(background_layer,Qbackground) || EQ(background_layer,
		  Qtransparent) || 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(background_layer),
		  Qcolor_value_vector_index_and_intensity) || 
		  rgb_color_p(background_layer) ? background_layer : Qnil;
	  if (color_qm);
	  else {
	      temp = assq_function(background_layer,line_color_or_colors_qm);
	      color_qm = CDR(temp);
	  }
	  if (color_qm) {
	      temp = right;
	      temp_6 = bottom;
	      if ( !EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor)) {
		  if (EQ(color_qm,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(color_qm,Qforeground) || EQ(color_qm,
			  Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(color_qm,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(color_qm);
		  if (EQ(Qbackground,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
			  Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(Qbackground,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = map_to_color_value(Qbackground);
		  temp_5 = FIXNUM_LOGXOR(color_value_1,color_value_2);
	      }
	      else if (EQ(color_qm,Qbackground))
		  temp_5 = EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(color_qm,Qtransparent))
		  temp_5 = EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(Qbackground,Qtransparent)) {
		  if (EQ(color_qm,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(color_qm,Qforeground) || EQ(color_qm,
			  Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(color_qm,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(color_qm);
		  temp_5 = FIXNUM_LOGXOR(color_value_1,
			  Current_background_color_value);
	      }
	      else {
		  if (EQ(color_qm,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(color_qm,Qforeground) || EQ(color_qm,
			  Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(color_qm,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(color_qm);
		  if (EQ(Qbackground,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
			  Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(Qbackground,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = map_to_color_value(Qbackground);
		  temp_5 = FIXNUM_LOGXOR(color_value_1,color_value_2);
	      }
	      draw_graphic_element(6,Qadd_solid_rectangle,FIX(left),
		      FIX(top),temp,temp_6,temp_5);
	  }
	  set_current_background_color_value(old_color_value);
	POP_SPECIAL();
    }
    draw_icon(block_left,block_top,icon_description,icon_attributes_plist,
	    generalized_color_differences,Current_background_color_value);
    if (icon_color_pattern_qm)
	reclaim_gensym_list_1(generalized_color_differences);
    return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

/* DRAW-SELECTED-REGIONS-OF-ICON */
Object draw_selected_regions_of_icon(entity,changed_regions)
    Object entity, changed_regions;
{
    Object icon_description_qm, icon_attributes_plist, color_pattern;
    Object multichrome_qm, new_metacolor, old_metacolor, color_value_1;
    Object color_value_2, foreground_color_difference_or_differences;
    Object region_name, color, ab_loop_list_, real_color, region_changed_qm;
    Object color_difference, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, gensymed_symbol, last_1, next_qm, temp_1;
    Object svref_arg_2;

    x_note_fn_call(90,47);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
	color_pattern = current_color_pattern_of_entity(entity);
	multichrome_qm = multichrome_icon_p(entity);
	if (monochrome_icon_p(entity) && EQUAL(changed_regions,
		list_constant_4)) {
	    new_metacolor = current_line_color_of_entity(entity);
	    old_metacolor = Qbackground;
	    if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
		if (EQ(new_metacolor,Qbackground))
		    color_value_1 = Current_background_color_value;
		else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
			Qworkspace_foreground))
		    color_value_1 = Current_foreground_color_value;
		else if (EQ(new_metacolor,Qtransparent))
		    color_value_1 = Current_background_color_value;
		else
		    color_value_1 = map_to_color_value(new_metacolor);
		if (EQ(old_metacolor,Qbackground))
		    color_value_2 = Current_background_color_value;
		else if (EQ(old_metacolor,Qforeground) || EQ(old_metacolor,
			Qworkspace_foreground))
		    color_value_2 = Current_foreground_color_value;
		else if (EQ(old_metacolor,Qtransparent))
		    color_value_2 = Current_background_color_value;
		else
		    color_value_2 = map_to_color_value(old_metacolor);
		foreground_color_difference_or_differences = 
			FIXNUM_LOGXOR(color_value_1,color_value_2);
	    }
	    else if (EQ(new_metacolor,old_metacolor))
		foreground_color_difference_or_differences = 
			EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? Transparent_color_value 
			: FIX((SI_Long)0L);
	    else if (EQ(new_metacolor,Qtransparent))
		foreground_color_difference_or_differences = 
			EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) ? Transparent_color_value 
			: FIX((SI_Long)0L);
	    else if (EQ(old_metacolor,Qtransparent)) {
		if (EQ(new_metacolor,Qbackground))
		    color_value_1 = Current_background_color_value;
		else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
			Qworkspace_foreground))
		    color_value_1 = Current_foreground_color_value;
		else if (EQ(new_metacolor,Qtransparent))
		    color_value_1 = Current_background_color_value;
		else
		    color_value_1 = map_to_color_value(new_metacolor);
		foreground_color_difference_or_differences = 
			FIXNUM_LOGXOR(color_value_1,
			Current_background_color_value);
	    }
	    else {
		if (EQ(new_metacolor,Qbackground))
		    color_value_1 = Current_background_color_value;
		else if (EQ(new_metacolor,Qforeground) || EQ(new_metacolor,
			Qworkspace_foreground))
		    color_value_1 = Current_foreground_color_value;
		else if (EQ(new_metacolor,Qtransparent))
		    color_value_1 = Current_background_color_value;
		else
		    color_value_1 = map_to_color_value(new_metacolor);
		if (EQ(old_metacolor,Qbackground))
		    color_value_2 = Current_background_color_value;
		else if (EQ(old_metacolor,Qforeground) || EQ(old_metacolor,
			Qworkspace_foreground))
		    color_value_2 = Current_foreground_color_value;
		else if (EQ(old_metacolor,Qtransparent))
		    color_value_2 = Current_background_color_value;
		else
		    color_value_2 = map_to_color_value(old_metacolor);
		foreground_color_difference_or_differences = 
			FIXNUM_LOGXOR(color_value_1,color_value_2);
	    }
	}
	else {
	    region_name = Nil;
	    color = Nil;
	    ab_loop_list_ = color_pattern;
	    real_color = Nil;
	    region_changed_qm = Nil;
	    color_difference = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    region_name = CAR(ab_loop_desetq_);
	    color = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = EQ(color,Qforeground) ? 
		    current_line_color_of_entity(entity) : Nil;
	    if (temp);
	    else
		temp = color;
	    real_color = temp;
	    gensymed_symbol = changed_regions;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    if (EQ(M_CAR(gensymed_symbol),region_name)) {
		temp = gensymed_symbol;
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_1:;
	    if (temp);
	    else if (EQ(region_name,Qforeground) &&  !TRUEP(multichrome_qm)) {
		gensymed_symbol = changed_regions;
	      next_loop_2:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_2;
		if (EQ(M_CAR(gensymed_symbol),Qicon_color)) {
		    temp = gensymed_symbol;
		    goto end_2;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_2;
	      end_loop_2:
		temp = Qnil;
	      end_2:;
	    }
	    else
		temp = Nil;
	    region_changed_qm = temp;
	    if (region_changed_qm) {
		if ( !EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor)) {
		    if (EQ(real_color,Qbackground))
			color_value_1 = Current_background_color_value;
		    else if (EQ(real_color,Qforeground) || EQ(real_color,
			    Qworkspace_foreground))
			color_value_1 = Current_foreground_color_value;
		    else if (EQ(real_color,Qtransparent))
			color_value_1 = Current_background_color_value;
		    else
			color_value_1 = map_to_color_value(real_color);
		    if (EQ(Qbackground,Qbackground))
			color_value_2 = Current_background_color_value;
		    else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
			    Qworkspace_foreground))
			color_value_2 = Current_foreground_color_value;
		    else if (EQ(Qbackground,Qtransparent))
			color_value_2 = Current_background_color_value;
		    else
			color_value_2 = map_to_color_value(Qbackground);
		    color_difference = FIXNUM_LOGXOR(color_value_1,
			    color_value_2);
		}
		else if (EQ(real_color,Qbackground))
		    color_difference = EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    Transparent_color_value : FIX((SI_Long)0L);
		else if (EQ(real_color,Qtransparent))
		    color_difference = EQ(Current_drawing_transfer_mode,
			    Kpaint_infered_from_xor) ? 
			    Transparent_color_value : FIX((SI_Long)0L);
		else if (EQ(Qbackground,Qtransparent)) {
		    if (EQ(real_color,Qbackground))
			color_value_1 = Current_background_color_value;
		    else if (EQ(real_color,Qforeground) || EQ(real_color,
			    Qworkspace_foreground))
			color_value_1 = Current_foreground_color_value;
		    else if (EQ(real_color,Qtransparent))
			color_value_1 = Current_background_color_value;
		    else
			color_value_1 = map_to_color_value(real_color);
		    color_difference = FIXNUM_LOGXOR(color_value_1,
			    Current_background_color_value);
		}
		else {
		    if (EQ(real_color,Qbackground))
			color_value_1 = Current_background_color_value;
		    else if (EQ(real_color,Qforeground) || EQ(real_color,
			    Qworkspace_foreground))
			color_value_1 = Current_foreground_color_value;
		    else if (EQ(real_color,Qtransparent))
			color_value_1 = Current_background_color_value;
		    else
			color_value_1 = map_to_color_value(real_color);
		    if (EQ(Qbackground,Qbackground))
			color_value_2 = Current_background_color_value;
		    else if (EQ(Qbackground,Qforeground) || EQ(Qbackground,
			    Qworkspace_foreground))
			color_value_2 = Current_foreground_color_value;
		    else if (EQ(Qbackground,Qtransparent))
			color_value_2 = Current_background_color_value;
		    else
			color_value_2 = map_to_color_value(Qbackground);
		    color_difference = FIXNUM_LOGXOR(color_value_1,
			    color_value_2);
		}
	    }
	    else
		color_difference = Transparent_color_value;
	    ab_loopvar__2 = gensym_cons_1(color_difference,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    foreground_color_difference_or_differences = ab_loopvar_;
	    goto end_3;
	    foreground_color_difference_or_differences = Qnil;
	  end_3:;
	}
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	draw_icon(temp,gensymed_symbol,icon_description_qm,
		icon_attributes_plist,
		foreground_color_difference_or_differences,
		Current_background_color_value);
	if (CONSP(foreground_color_difference_or_differences)) {
	    if (foreground_color_difference_or_differences) {
		last_1 = foreground_color_difference_or_differences;
		next_qm = Nil;
	      next_loop_3:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_3;
		inline_note_reclaim_cons(last_1,Qab_gensym);
		last_1 = next_qm;
		goto next_loop_3;
	      end_loop_3:
		inline_note_reclaim_cons(last_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = foreground_color_difference_or_differences;
		    temp_1 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		else {
		    temp_1 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = 
			    foreground_color_difference_or_differences;
		    temp_1 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
		return VALUES_1(Nil);
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

/* DRAW-FOR-ENTITY */
Object draw_for_entity(entity)
    Object entity;
{
    x_note_fn_call(90,48);
    return draw_icon_for_entity(entity);
}

/* REVISE-ICON-RENDERING */
Object revise_icon_rendering(entity,old_foreground_color_or_colors,
	    new_foreground_color_or_colors,new_line_color_qm)
    Object entity, old_foreground_color_or_colors;
    Object new_foreground_color_or_colors, new_line_color_qm;
{
    Object icon_description_qm, icon_attributes_plist;
    Object old_color_value_or_values;
    Object foreground_color_difference_or_color_differences, old_line_color;
    Object new_line_color, current_foreground_color_value;
    Object old_foreground_color_value, new_foreground_color, color_value_1;
    Object color_value_2, old_foreground_color, ab_loop_list_, ab_loop_list__1;
    Object new_foreground_color_1, color_difference;
    Object foreground_color_differences, ab_loopvar_, ab_loopvar__1;
    Object old_color_values, ab_loopvar__2, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, temp_1, last_1, next_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,49);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm) {
	icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
	old_color_value_or_values = Nil;
	foreground_color_difference_or_color_differences = Nil;
	old_line_color = current_line_color_of_entity(entity);
	new_line_color = new_line_color_qm;
	if (new_line_color);
	else
	    new_line_color = old_line_color;
	if (EQ(old_line_color,Qbackground))
	    current_foreground_color_value = Current_background_color_value;
	else if (EQ(old_line_color,Qforeground) || EQ(old_line_color,
		Qworkspace_foreground))
	    current_foreground_color_value = Current_foreground_color_value;
	else if (EQ(old_line_color,Qtransparent))
	    current_foreground_color_value = Current_background_color_value;
	else
	    current_foreground_color_value = 
		    map_to_color_value(old_line_color);
	PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
		0);
	  if (ATOM(old_foreground_color_or_colors)) {
	      if (EQ(old_foreground_color_or_colors,Qbackground))
		  old_foreground_color_value = Current_background_color_value;
	      else if (EQ(old_foreground_color_or_colors,Qforeground) || 
		      EQ(old_foreground_color_or_colors,Qworkspace_foreground))
		  old_foreground_color_value = Current_foreground_color_value;
	      else if (EQ(old_foreground_color_or_colors,Qtransparent))
		  old_foreground_color_value = Current_background_color_value;
	      else
		  old_foreground_color_value = 
			  map_to_color_value(old_foreground_color_or_colors);
	      new_foreground_color = EQ(new_foreground_color_or_colors,
		      Qforeground) ? new_line_color : 
		      new_foreground_color_or_colors;
	      if ( !EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor)) {
		  if (EQ(new_foreground_color,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color,Qforeground) || 
			  EQ(new_foreground_color,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(new_foreground_color);
		  if (EQ(old_foreground_color_or_colors,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(old_foreground_color_or_colors,Qforeground) 
			  || EQ(old_foreground_color_or_colors,
			  Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(old_foreground_color_or_colors,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = 
			      map_to_color_value(old_foreground_color_or_colors);
		  foreground_color_difference_or_color_differences = 
			  FIXNUM_LOGXOR(color_value_1,color_value_2);
	      }
	      else if (EQ(new_foreground_color,old_foreground_color_or_colors))
		  foreground_color_difference_or_color_differences = 
			  EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(new_foreground_color,Qtransparent))
		  foreground_color_difference_or_color_differences = 
			  EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(old_foreground_color_or_colors,Qtransparent)) {
		  if (EQ(new_foreground_color,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color,Qforeground) || 
			  EQ(new_foreground_color,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(new_foreground_color);
		  foreground_color_difference_or_color_differences = 
			  FIXNUM_LOGXOR(color_value_1,
			  Current_background_color_value);
	      }
	      else {
		  if (EQ(new_foreground_color,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color,Qforeground) || 
			  EQ(new_foreground_color,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = map_to_color_value(new_foreground_color);
		  if (EQ(old_foreground_color_or_colors,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(old_foreground_color_or_colors,Qforeground) 
			  || EQ(old_foreground_color_or_colors,
			  Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(old_foreground_color_or_colors,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = 
			      map_to_color_value(old_foreground_color_or_colors);
		  foreground_color_difference_or_color_differences = 
			  FIXNUM_LOGXOR(color_value_1,color_value_2);
	      }
	      old_color_value_or_values = old_foreground_color_value;
	  }
	  else {
	      old_foreground_color = Nil;
	      ab_loop_list_ = old_foreground_color_or_colors;
	      new_foreground_color = Nil;
	      ab_loop_list__1 = new_foreground_color_or_colors;
	      old_foreground_color_value = Nil;
	      new_foreground_color_1 = Nil;
	      color_difference = Nil;
	      foreground_color_differences = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      old_color_values = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__1 = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      old_foreground_color = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop;
	      new_foreground_color = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      if (EQ(old_foreground_color,Qbackground))
		  old_foreground_color_value = Current_background_color_value;
	      else if (EQ(old_foreground_color,Qforeground) || 
		      EQ(old_foreground_color,Qworkspace_foreground))
		  old_foreground_color_value = Current_foreground_color_value;
	      else if (EQ(old_foreground_color,Qtransparent))
		  old_foreground_color_value = Current_background_color_value;
	      else
		  old_foreground_color_value = 
			  map_to_color_value(old_foreground_color);
	      new_foreground_color_1 = EQ(new_foreground_color,
		      Qforeground) ? new_line_color : new_foreground_color;
	      if ( !EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor)) {
		  if (EQ(new_foreground_color_1,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color_1,Qforeground) || 
			  EQ(new_foreground_color_1,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color_1,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = 
			      map_to_color_value(new_foreground_color_1);
		  if (EQ(old_foreground_color,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(old_foreground_color,Qforeground) || 
			  EQ(old_foreground_color,Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(old_foreground_color,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = map_to_color_value(old_foreground_color);
		  color_difference = FIXNUM_LOGXOR(color_value_1,
			  color_value_2);
	      }
	      else if (EQ(new_foreground_color_1,old_foreground_color))
		  color_difference = EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(new_foreground_color_1,Qtransparent))
		  color_difference = EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) ? 
			  Transparent_color_value : FIX((SI_Long)0L);
	      else if (EQ(old_foreground_color,Qtransparent)) {
		  if (EQ(new_foreground_color_1,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color_1,Qforeground) || 
			  EQ(new_foreground_color_1,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color_1,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = 
			      map_to_color_value(new_foreground_color_1);
		  color_difference = FIXNUM_LOGXOR(color_value_1,
			  Current_background_color_value);
	      }
	      else {
		  if (EQ(new_foreground_color_1,Qbackground))
		      color_value_1 = Current_background_color_value;
		  else if (EQ(new_foreground_color_1,Qforeground) || 
			  EQ(new_foreground_color_1,Qworkspace_foreground))
		      color_value_1 = Current_foreground_color_value;
		  else if (EQ(new_foreground_color_1,Qtransparent))
		      color_value_1 = Current_background_color_value;
		  else
		      color_value_1 = 
			      map_to_color_value(new_foreground_color_1);
		  if (EQ(old_foreground_color,Qbackground))
		      color_value_2 = Current_background_color_value;
		  else if (EQ(old_foreground_color,Qforeground) || 
			  EQ(old_foreground_color,Qworkspace_foreground))
		      color_value_2 = Current_foreground_color_value;
		  else if (EQ(old_foreground_color,Qtransparent))
		      color_value_2 = Current_background_color_value;
		  else
		      color_value_2 = map_to_color_value(old_foreground_color);
		  color_difference = FIXNUM_LOGXOR(color_value_1,
			  color_value_2);
	      }
	      new_cons = ISVREF(Available_gensym_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_gensym_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol = new_cons;
	      }
	      else
		  gensymed_symbol = Nil;
	      if ( !TRUEP(gensymed_symbol))
		  gensymed_symbol = replenish_gensym_cons_pool();
	      M_CAR(gensymed_symbol) = color_difference;
	      M_CDR(gensymed_symbol) = Nil;
	      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	      ab_loopvar__1 = gensymed_symbol;
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  foreground_color_differences = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      new_cons = ISVREF(Available_gensym_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_gensym_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol = new_cons;
	      }
	      else
		  gensymed_symbol = Nil;
	      if ( !TRUEP(gensymed_symbol))
		  gensymed_symbol = replenish_gensym_cons_pool();
	      M_CAR(gensymed_symbol) = old_foreground_color_value;
	      M_CDR(gensymed_symbol) = Nil;
	      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	      ab_loopvar__1 = gensymed_symbol;
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__1;
	      else
		  old_color_values = ab_loopvar__1;
	      ab_loopvar__2 = ab_loopvar__1;
	      goto next_loop;
	    end_loop:
	      foreground_color_difference_or_color_differences = 
		      foreground_color_differences;
	      old_color_value_or_values = old_color_values;
	  }
	  gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  temp_1 = gensymed_symbol;
	  gensymed_symbol = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  draw_icon(temp_1,gensymed_symbol,icon_description_qm,
		  icon_attributes_plist,
		  foreground_color_difference_or_color_differences,
		  old_color_value_or_values);
	  if (CONSP(old_foreground_color_or_colors)) {
	      if (foreground_color_difference_or_color_differences) {
		  last_1 = foreground_color_difference_or_color_differences;
		  next_qm = Nil;
		next_loop_1:
		  next_qm = M_CDR(last_1);
		  if ( !TRUEP(next_qm))
		      goto end_loop_1;
		  inline_note_reclaim_cons(last_1,Qab_gensym);
		  last_1 = next_qm;
		  goto next_loop_1;
		end_loop_1:
		  inline_note_reclaim_cons(last_1,Qab_gensym);
		  if (ISVREF(Available_gensym_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = ISVREF(Available_gensym_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = 
			      foreground_color_difference_or_color_differences;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = last_1;
		  }
		  else {
		      temp = Available_gensym_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = 
			      foreground_color_difference_or_color_differences;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = last_1;
		  }
		  M_CDR(last_1) = Nil;
	      }
	      if (old_color_value_or_values) {
		  last_1 = old_color_value_or_values;
		  next_qm = Nil;
		next_loop_2:
		  next_qm = M_CDR(last_1);
		  if ( !TRUEP(next_qm))
		      goto end_loop_2;
		  inline_note_reclaim_cons(last_1,Qab_gensym);
		  last_1 = next_qm;
		  goto next_loop_2;
		end_loop_2:
		  inline_note_reclaim_cons(last_1,Qab_gensym);
		  if (ISVREF(Available_gensym_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = ISVREF(Available_gensym_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = old_color_value_or_values;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = last_1;
		  }
		  else {
		      temp = Available_gensym_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = old_color_value_or_values;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = last_1;
		  }
		  M_CDR(last_1) = Nil;
		  result = VALUES_1(Nil);
	      }
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

static Object list_constant_5;     /* # */

/* REFLECT-AND-ROTATE-BLOCK-IN-WORKSPACE */
Object reflect_and_rotate_block_in_workspace(block,reflection_and_rotation,
	    center_x,center_y)
    Object block, reflection_and_rotation, center_x, center_y;
{
    Object new_reflection_and_rotation, gensymed_symbol, temp, new_left_top_x;
    Object new_left_top_y, new_right_bottom_x, new_right_bottom_y;
    Object result;

    x_note_fn_call(90,50);
    new_reflection_and_rotation = 
	    multiply_reflection_and_rotation(getfq_function_no_default(ISVREF(block,
	    (SI_Long)17L),Qreflection_and_rotation),reflection_and_rotation);
    if (memq_function(new_reflection_and_rotation,list_constant_5))
	change_icon_attribute(block,Qreflection_and_rotation,Nil);
    else
	change_icon_attribute(block,Qreflection_and_rotation,
		multiply_reflection_and_rotation(getfq_function_no_default(ISVREF(block,
		(SI_Long)17L),Qreflection_and_rotation),
		reflection_and_rotation));
    reflect_and_rotate_connections_on_block_in_workspace(block,
	    reflection_and_rotation);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    result = reflect_and_rotate_point_in_workspace(temp,gensymed_symbol,
	    reflection_and_rotation,center_x,center_y);
    MVS_2(result,new_left_top_x,new_left_top_y);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    result = reflect_and_rotate_point_in_workspace(temp,gensymed_symbol,
	    reflection_and_rotation,center_x,center_y);
    MVS_2(result,new_right_bottom_x,new_right_bottom_y);
    return change_edges_of_block(block,FIXNUM_MIN(new_left_top_x,
	    new_right_bottom_x),FIXNUM_MIN(new_left_top_y,
	    new_right_bottom_y),FIXNUM_MAX(new_left_top_x,
	    new_right_bottom_x),FIXNUM_MAX(new_left_top_y,new_right_bottom_y));
}

/* REFLECT-AND-ROTATE-POINT-IN-WORKSPACE */
Object reflect_and_rotate_point_in_workspace(x,y,reflection_and_rotation,
	    center_x,center_y)
    Object x, y, reflection_and_rotation, center_x, center_y;
{
    Object delta_x, delta_y, temp, temp_1;
    Object result;

    x_note_fn_call(90,51);
    result = rotate_point_in_line_drawing_description(reflection_and_rotation,
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIXNUM_MINUS(x,center_x),
	    FIXNUM_MINUS(y,center_y));
    MVS_2(result,delta_x,delta_y);
    temp = FIXNUM_ADD(delta_x,center_x);
    temp_1 = FIXNUM_ADD(delta_y,center_y);
    return VALUES_2(temp,temp_1);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "Invalid icon description element:~%  ~a" */

static Object string_constant_1;   /* "This icon description is not valid for this height and width." */

/* CREATE-ICON-DESCRIPTION-IF-VALID */
Object create_icon_description_if_valid(icon_width,icon_height,
	    line_drawing_description,line_color_of_icon,icon_background_layer)
    Object icon_width, icon_height, line_drawing_description;
    Object line_color_of_icon, icon_background_layer;
{
    Object ok_qm, information_if_not_ok_or_extrema_if_ok_qm;
    Object new_icon_description, temp, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temporary_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(90,52);
    result = valid_line_drawing_description_p(icon_width,icon_height,
	    line_drawing_description,Nil);
    MVS_2(result,ok_qm,information_if_not_ok_or_extrema_if_ok_qm);
    if (ok_qm) {
	new_icon_description = create_icon_description(9,icon_width,
		icon_height,line_drawing_description,line_color_of_icon,
		Nil,Nil,Nil,Nil,information_if_not_ok_or_extrema_if_ok_qm);
	SVREF(new_icon_description,FIX((SI_Long)13L)) = icon_background_layer;
	return VALUES_1(new_icon_description);
    }
    else {
	if (CONSP(information_if_not_ok_or_extrema_if_ok_qm)) {
	    temp = CAR(information_if_not_ok_or_extrema_if_ok_qm);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
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
		      write_drawing_element(information_if_not_ok_or_extrema_if_ok_qm);
		      temporary_text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_engineer(2,string_constant,temporary_text_string);
	    reclaim_text_string(temporary_text_string);
	}
	else
	    notify_engineer(1,string_constant_1);
	return create_default_entity_icon_description(icon_width,icon_height);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_entity_line_drawing_description_template, Qdefault_entity_line_drawing_description_template);

static Object Kwidth;              /* :width */

static Object Kheight;             /* :height */

/* CREATE-DEFAULT-ENTITY-ICON-DESCRIPTION */
Object create_default_entity_icon_description(icon_width,icon_height)
    Object icon_width, icon_height;
{
    x_note_fn_call(90,53);
    return create_icon_description(3,icon_width,icon_height,
	    slot_value_cons_1(nsubst(3,icon_width,Kwidth,nsubst(3,
	    icon_height,Kheight,
	    copy_tree_using_slot_value_conses_1(Default_entity_line_drawing_description_template))),
	    Nil));
}

static Object Qcar_eq;             /* car-eq */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* OVERRIDE-ICON-DESCRIPTION-FOR-SYSTEM-DEFINED-CLASS-AB */
Object override_icon_description_for_system_defined_class_ab varargs_1(int, n)
{
    Object system_defined_class, icon_description;
    Object stub_feature_qm, present_stubs_class_feature_qm, class_description;
    Object class_features, cons_holding_relevant_class_feature_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,54);
    INIT_ARGS_nonrelocating();
    system_defined_class = REQUIRED_ARG_nonrelocating();
    icon_description = REQUIRED_ARG_nonrelocating();
    stub_feature_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    update_slot_description_for_system_defined_class(3,
	    system_defined_class,Qicon_description,icon_description);
    if (stub_feature_qm) {
	present_stubs_class_feature_qm = 
		get_class_feature_if_any(system_defined_class,Qstubs);
	if ( !EQUAL(present_stubs_class_feature_qm,stub_feature_qm)) {
	    class_description = 
		    lookup_global_or_kb_specific_property_value(system_defined_class,
		    Class_description_gkbprop);
	    class_features = ISVREF(class_description,(SI_Long)12L);
	    cons_holding_relevant_class_feature_qm = member(4,Qstubs,
		    class_features,Ktest,Qcar_eq);
	    if (cons_holding_relevant_class_feature_qm)
		M_CAR(cons_holding_relevant_class_feature_qm) = 
			stub_feature_qm;
	    else
		class_features_function(class_description,
			CONS(stub_feature_qm,class_features));
	}
	return update_slot_description_for_system_defined_class(4,
		system_defined_class,Qslot_group_for_block_qm,Nil,
		LIST_1(stub_feature_qm));
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

/* FIX-UP-ICON-DESCRIPTION-FOR-ENTITY-IF-NECESSARY */
Object fix_up_icon_description_for_entity_if_necessary()
{
    Object slot_description, temp, slot_definition, slot_init_form;
    Object svref_new_value;

    x_note_fn_call(90,55);
    slot_description = 
	    get_slot_description_of_class_description_function(Qicon_description,
	    lookup_global_or_kb_specific_property_value(Qentity,
	    Class_description_gkbprop),Nil);
    temp = lookup_global_or_kb_specific_property_value(Qentity,
	    Class_definition_gkbprop);
    slot_definition = assq_function(Qicon_description,CDDR(temp));
    slot_init_form = list_constant_6;
    if ( !TRUEP(SECOND(slot_definition)))
	M_SECOND(slot_definition) = slot_init_form;
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)6L))) {
	temp = CADR(slot_init_form);
	svref_new_value = APPLY_1(temp,CDDR(slot_init_form));
	return VALUES_1(SVREF(slot_description,FIX((SI_Long)6L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

/* ITEM-X-POSITION */
Object item_x_position(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, width_of_block;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(90,56);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    width_of_block = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    temp =  !temp;
    if (temp);
    else
	temp = TRUEP(memq_function(getf(ISVREF(item,(SI_Long)17L),
		Qreflection_and_rotation,_),list_constant_7));
    gensymed_symbol_2 = temp ? width_of_block >>  -  - (SI_Long)1L : 
	    width_of_block - (width_of_block >>  -  - (SI_Long)1L);
    return VALUES_1(FIX(gensymed_symbol_1 + gensymed_symbol_2));
}

static Object list_constant_8;     /* # */

/* ITEM-Y-POSITION */
Object item_y_position(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, height_of_block;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(90,57);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    height_of_block = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    temp =  !temp;
    if (temp);
    else
	temp = TRUEP(memq_function(getf(ISVREF(item,(SI_Long)17L),
		Qreflection_and_rotation,_),list_constant_8));
    gensymed_symbol_2 = temp ? height_of_block >>  -  - (SI_Long)1L : 
	    height_of_block - (height_of_block >>  -  - (SI_Long)1L);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    return VALUES_1(FIX( - gensymed_symbol_1));
}

/* ITEM-WIDTH */
Object item_width(item)
    Object item;
{
    Object gensymed_symbol, temp, sub_class_bit_vector, icon_description;
    Object icon_attributes_plist_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(90,58);
    if (ISVREF(item,(SI_Long)14L)) {
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	if ( !temp_1) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	if (temp_1 ? TRUEP(ISVREF(item,(SI_Long)16L)) : TRUEP(Nil)) {
	    icon_description = ISVREF(item,(SI_Long)16L);
	    icon_attributes_plist_qm = ISVREF(item,(SI_Long)17L);
	    temp = icon_attributes_plist_qm ? 
		    getf(icon_attributes_plist_qm,Qwidth,_) : Nil;
	    if (temp);
	    else
		temp = ISVREF(icon_description,(SI_Long)1L);
	}
	else
	    temp = FIX((SI_Long)0L);
    }
    return VALUES_1(temp);
}

/* ITEM-HEIGHT */
Object item_height(item)
    Object item;
{
    Object gensymed_symbol, temp, sub_class_bit_vector, icon_description;
    Object icon_attributes_plist_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(90,59);
    if (ISVREF(item,(SI_Long)14L)) {
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	if ( !temp_1) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	if (temp_1 ? TRUEP(ISVREF(item,(SI_Long)16L)) : TRUEP(Nil)) {
	    icon_description = ISVREF(item,(SI_Long)16L);
	    icon_attributes_plist_qm = ISVREF(item,(SI_Long)17L);
	    temp = icon_attributes_plist_qm ? 
		    getf(icon_attributes_plist_qm,Qheight,_) : Nil;
	    if (temp);
	    else
		temp = ISVREF(icon_description,(SI_Long)2L);
	}
	else
	    temp = FIX((SI_Long)0L);
    }
    return VALUES_1(temp);
}

static Object Qreflected;          /* reflected */

static Object Qclockwise_90;       /* clockwise-90 */

static Object Qreflected_clockwise_90;  /* reflected-clockwise-90 */

static Object Qclockwise_180;      /* clockwise-180 */

static Object Qreflected_clockwise_180;  /* reflected-clockwise-180 */

static Object Qclockwise_270;      /* clockwise-270 */

static Object Qreflected_clockwise_270;  /* reflected-clockwise-270 */

/* ICON-HEADING */
Object icon_heading(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(90,60);
    temp = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
	    Qreflection_and_rotation);
    if (EQ(temp,Qnil) || EQ(temp,Qnormal) || EQ(temp,Qreflected))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(temp,Qclockwise_90) || EQ(temp,Qreflected_clockwise_90))
	return VALUES_1(FIX((SI_Long)90L));
    else if (EQ(temp,Qclockwise_180) || EQ(temp,Qreflected_clockwise_180))
	return VALUES_1(FIX((SI_Long)180L));
    else if (EQ(temp,Qclockwise_270) || EQ(temp,Qreflected_clockwise_270))
	return VALUES_1(FIX((SI_Long)270L));
    else
	return VALUES_1(Qnil);
}

static Object list_constant_9;     /* # */

/* REFLECTEDP */
Object reflectedp(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(90,61);
    temp = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
	    Qreflection_and_rotation);
    if (member_eql(temp,list_constant_9))
	return VALUES_1(Nil);
    else
	return VALUES_1(T);
}

/* INITIAL-ITEM-X-POSITION */
Object initial_item_x_position(class_1)
    Object class_1;
{
    x_note_fn_call(90,62);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ITEM-X-POSITION */
Object get_item_x_position(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,63);
    temp = item_x_position(item);
    return VALUES_1(temp);
}

/* INITIAL-ICON-X-POSITION */
Object initial_icon_x_position(class_1)
    Object class_1;
{
    x_note_fn_call(90,64);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ICON-X-POSITION */
Object get_icon_x_position(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,65);
    temp = item_x_position(item);
    return VALUES_1(temp);
}

/* INITIAL-ITEM-Y-POSITION */
Object initial_item_y_position(class_1)
    Object class_1;
{
    x_note_fn_call(90,66);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ITEM-Y-POSITION */
Object get_item_y_position(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,67);
    temp = item_y_position(item);
    return VALUES_1(temp);
}

/* INITIAL-ICON-Y-POSITION */
Object initial_icon_y_position(class_1)
    Object class_1;
{
    x_note_fn_call(90,68);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ICON-Y-POSITION */
Object get_icon_y_position(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,69);
    temp = item_y_position(item);
    return VALUES_1(temp);
}

/* INITIAL-ICON-HEADING */
Object initial_icon_heading(class_1)
    Object class_1;
{
    x_note_fn_call(90,70);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ICON-HEADING */
Object get_icon_heading(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,71);
    temp = icon_heading(item);
    return VALUES_1(temp);
}

/* SET-ICON-HEADING */
Object set_icon_heading(entity,new_heading)
    Object entity, new_heading;
{
    Object temp;

    x_note_fn_call(90,72);
    temp = rotate_and_reflect_icon(entity,FIXNUM_MINUS(new_heading,
	    icon_heading(entity)),Nil,Nil,Nil,T);
    return VALUES_1(temp);
}

static Object Qleft_right;         /* left-right */

/* INITIAL-ICON-REFLECTION */
Object initial_icon_reflection(class_1)
    Object class_1;
{
    x_note_fn_call(90,73);
    return VALUES_1(Qleft_right);
}

/* GET-ICON-REFLECTION */
Object get_icon_reflection(item)
    Object item;
{
    x_note_fn_call(90,74);
    return VALUES_1(reflectedp(item) ? Qleft_right : Nil);
}

static Object Qbad;                /* bad */

static Object array_constant;      /* # */

/* SET-ICON-REFLECTION */
Object set_icon_reflection(entity,new_value)
    Object entity, new_value;
{
    Object reflectp, temp;

    x_note_fn_call(90,75);
    if (EQ(new_value,Nil))
	reflectp = reflectedp(entity);
    else if (EQ(new_value,Qleft_right))
	reflectp =  !TRUEP(reflectedp(entity)) ? T : Nil;
    else
	reflectp = Qbad;
    temp = EQ(reflectp,Qbad) ? 
	    copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)29L)) : reflectp ? rotate_and_reflect_icon(entity,
	    FIX((SI_Long)0L),T,Nil,Nil,T) : Nil;
    return VALUES_1(temp);
}

/* INITIAL-ITEM-HEIGHT */
Object initial_item_height(class_1)
    Object class_1;
{
    x_note_fn_call(90,76);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ITEM-HEIGHT */
Object get_item_height(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,77);
    temp = item_height(item);
    return VALUES_1(temp);
}

/* INITIAL-ICON-HEIGHT */
Object initial_icon_height(class_1)
    Object class_1;
{
    x_note_fn_call(90,78);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ICON-HEIGHT */
Object get_icon_height(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,79);
    temp = item_height(item);
    return VALUES_1(temp);
}

/* INITIAL-ITEM-WIDTH */
Object initial_item_width(class_1)
    Object class_1;
{
    x_note_fn_call(90,80);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ITEM-WIDTH */
Object get_item_width(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,81);
    temp = item_width(item);
    return VALUES_1(temp);
}

/* INITIAL-ICON-WIDTH */
Object initial_icon_width(class_1)
    Object class_1;
{
    x_note_fn_call(90,82);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-ICON-WIDTH */
Object get_icon_width(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,83);
    temp = item_width(item);
    return VALUES_1(temp);
}

/* ICON-COLOR */
Object icon_color(entity)
    Object entity;
{
    Object temp, icon_description_qm;

    x_note_fn_call(90,84);
    temp = assq_function(Qicon_color,icon_color_pattern(entity));
    temp = CDR(temp);
    if (temp);
    else
	temp = getf(ISVREF(entity,(SI_Long)17L),Qline_color,_);
    if (temp);
    else {
	icon_description_qm = ISVREF(entity,(SI_Long)16L);
	temp = icon_description_qm ? ISVREF(icon_description_qm,
		(SI_Long)5L) : Nil;
    }
    if (temp);
    else {
	temp = assq_function(Qforeground,icon_color_pattern(entity));
	temp = CDR(temp);
    }
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Current_default_line_color);
}

/* GET-COLOR-OF-ICON-REGION */
Object get_color_of_icon_region(entity,region)
    Object entity, region;
{
    Object temp;

    x_note_fn_call(90,85);
    if (EQ(region,Qicon_color))
	return icon_color(entity);
    else {
	temp = assq_function(region,icon_color_pattern(entity));
	return VALUES_1(CDR(temp));
    }
}

/* ICON-COLOR-PATTERN */
Object icon_color_pattern(entity)
    Object entity;
{
    Object temp, icon_description_qm;

    x_note_fn_call(90,86);
    temp = getf(ISVREF(entity,(SI_Long)17L),Qicon_color_pattern,_);
    if (temp)
	return VALUES_1(temp);
    else {
	icon_description_qm = ISVREF(entity,(SI_Long)16L);
	if (icon_description_qm)
	    return VALUES_1(ISVREF(icon_description_qm,(SI_Long)10L));
	else
	    return VALUES_1(Nil);
    }
}

static Object Qstripe_color;       /* stripe-color */

static Object Qtext_cell_plist_for_text_box;  /* text-cell-plist-for-text-box */

static Object Qtext_box_format;    /* text-box-format */

static Object Qbackground_color;   /* background-color */

static Object Qtext_cell_background_color_qm;  /* text-cell-background-color? */

static Object Qtext_color;         /* text-color */

static Object Qtext_cell_line_color_qm;  /* text-cell-line-color? */

static Object Qborder_color;       /* border-color */

static Object Qtext_box_border_color_qm;  /* text-box-border-color? */

static Object Qforeground_color;   /* foreground-color */

/* ITEM-COLOR */
Object item_color(item,region_qm)
    Object item, region_qm;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1, text_cell_plist;
    Object text_box_format;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,87);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	temp_1 = region_qm;
	if (temp_1);
	else
	    temp_1 = Qstripe_color;
	return get_connection_color(item,temp_1);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    text_cell_plist = get_slot_value_function(item,
		    Qtext_cell_plist_for_text_box,Nil);
	    text_box_format = get_slot_value_function(item,
		    Qtext_box_format,Nil);
	    if (EQ(region_qm,Qbackground_color)) {
		temp_1 = getf(text_cell_plist,Qbackground_color,_);
		if (temp_1);
		else
		    temp_1 = get_slot_value_function(text_box_format,
			    Qtext_cell_background_color_qm,Nil);
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(Qtransparent);
	    }
	    else if (EQ(region_qm,Qtext_color)) {
		temp_1 = getf(text_cell_plist,Qline_color,_);
		if (temp_1);
		else
		    temp_1 = get_slot_value_function(text_box_format,
			    Qtext_cell_line_color_qm,Nil);
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(Current_default_line_color);
	    }
	    else if (EQ(region_qm,Qborder_color)) {
		temp_1 = getf(text_cell_plist,Qborder_color,_);
		if (temp_1);
		else
		    temp_1 = get_slot_value_function(text_box_format,
			    Qtext_box_border_color_qm,Nil);
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(Current_default_line_color);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		if (region_qm)
		    return get_color_of_icon_region(item,region_qm);
		else
		    return icon_color(item);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		if (temp) {
		    if (EQ(region_qm,Qbackground_color)) {
			temp_1 = ISVREF(item,(SI_Long)21L);
			if (temp_1)
			    return VALUES_1(temp_1);
			else
			    return VALUES_1(Qwhite);
		    }
		    else if (EQ(region_qm,Qforeground_color)) {
			temp_1 = ISVREF(item,(SI_Long)22L);
			if (temp_1)
			    return VALUES_1(temp_1);
			else
			    return VALUES_1(Qblack);
		    }
		    else
			return VALUES_1(Qnil);
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

/* INITIAL-BACKGROUND-COLOR */
Object initial_background_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,88);
    return VALUES_1(Qblack);
}

/* GET-BACKGROUND-COLOR */
Object get_background_color(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, text_cell_plist;
    Object text_box_format, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,89);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	text_cell_plist = get_slot_value_function(item,
		Qtext_cell_plist_for_text_box,Nil);
	text_box_format = get_slot_value_function(item,Qtext_box_format,Nil);
	temp_1 = getf(text_cell_plist,Qbackground_color,_);
	if (temp_1);
	else
	    temp_1 = get_slot_value_function(text_box_format,
		    Qtext_cell_background_color_qm,Nil);
	if (temp_1);
	else
	    temp_1 = Qtransparent;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    temp_1 = ISVREF(item,(SI_Long)21L);
	    if (temp_1);
	    else
		temp_1 = Qwhite;
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		temp_1 = get_color_of_icon_region(item,Qbackground_color);
	    else
		temp_1 = Nil;
	}
    }
    return VALUES_1(temp_1);
}

static Object Kno_change;          /* :no-change */

static Object string_constant_2;   /* "The attribute BACKGROUND-COLOR does not exist in ~NF." */

static Object string_constant_3;   /* "The argument given, ~a, was not a valid color." */

/* SET-BACKGROUND-COLOR */
Object set_background_color(item,new_background_color)
    Object item, new_background_color;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,90);
    if (EQ(new_background_color,Qforeground) || EQ(new_background_color,
	    Qbackground) || EQ(new_background_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_background_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_background_color)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    change_color_of_text_box(5,item,T,new_background_color,
		    Kno_change,Kno_change);
	    temp_1 = Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		change_color_of_workspace(item,T,new_background_color,
			Kno_change);
		temp_1 = Nil;
	    }
	    else
		temp_1 = tformat_text_string(2,string_constant_2,item);
	}
    }
    else
	temp_1 = tformat_text_string(2,string_constant_3,new_background_color);
    return VALUES_1(temp_1);
}

/* INITIAL-FOREGROUND-COLOR */
Object initial_foreground_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,91);
    return VALUES_1(Qblack);
}

/* GET-FOREGROUND-COLOR */
Object get_foreground_color(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,92);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
	temp_1 = ISVREF(item,(SI_Long)22L);
	if (temp_1);
	else
	    temp_1 = Qwhite;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    temp_1 = get_color_of_icon_region(item,Qforeground_color);
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object string_constant_4;   /* "The attribute FOREGROUND-COLOR does not exist in ~NF." */

/* SET-FOREGROUND-COLOR */
Object set_foreground_color(item,new_foreground_color)
    Object item, new_foreground_color;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,93);
    if (EQ(new_foreground_color,Qforeground) || EQ(new_foreground_color,
	    Qbackground) || EQ(new_foreground_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_foreground_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_foreground_color)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    change_color_of_workspace(item,T,Kno_change,new_foreground_color);
	    temp_1 = Nil;
	}
	else
	    temp_1 = tformat_text_string(2,string_constant_4,item);
    }
    else
	temp_1 = tformat_text_string(2,string_constant_3,new_foreground_color);
    return VALUES_1(temp_1);
}

/* INITIAL-TEXT-COLOR */
Object initial_text_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,94);
    return VALUES_1(Qblack);
}

/* GET-TEXT-COLOR */
Object get_text_color(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, text_cell_plist;
    Object text_box_format, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,95);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	text_cell_plist = get_slot_value_function(item,
		Qtext_cell_plist_for_text_box,Nil);
	text_box_format = get_slot_value_function(item,Qtext_box_format,Nil);
	temp_1 = getf(text_cell_plist,Qline_color,_);
	if (temp_1);
	else
	    temp_1 = get_slot_value_function(text_box_format,
		    Qtext_cell_line_color_qm,Nil);
	if (temp_1);
	else
	    temp_1 = Current_default_line_color;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    temp_1 = get_color_of_icon_region(item,Qtext_color);
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object string_constant_5;   /* "The attribute TEXT-COLOR does not exist in ~NF." */

/* SET-TEXT-COLOR */
Object set_text_color(item,new_text_color)
    Object item, new_text_color;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,96);
    if (EQ(new_text_color,Qforeground) || EQ(new_text_color,Qbackground) 
	    || EQ(new_text_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_text_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_text_color)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    change_color_of_text_box(5,item,T,Kno_change,Kno_change,
		    new_text_color);
	    temp_1 = Nil;
	}
	else
	    temp_1 = tformat_text_string(2,string_constant_5,item);
    }
    else
	temp_1 = tformat_text_string(2,string_constant_3,new_text_color);
    return VALUES_1(temp_1);
}

/* INITIAL-BORDER-COLOR */
Object initial_border_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,97);
    return VALUES_1(Qblack);
}

/* GET-BORDER-COLOR */
Object get_border_color(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, text_cell_plist;
    Object text_box_format, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,98);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	text_cell_plist = get_slot_value_function(item,
		Qtext_cell_plist_for_text_box,Nil);
	text_box_format = get_slot_value_function(item,Qtext_box_format,Nil);
	temp_1 = getf(text_cell_plist,Qborder_color,_);
	if (temp_1);
	else
	    temp_1 = get_slot_value_function(text_box_format,
		    Qtext_box_border_color_qm,Nil);
	if (temp_1);
	else
	    temp_1 = Current_default_line_color;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    temp_1 = get_color_of_icon_region(item,Qborder_color);
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object string_constant_6;   /* "The attribute BORDER-COLOR does not exist is ~NF." */

/* SET-BORDER-COLOR */
Object set_border_color(item,new_border_color)
    Object item, new_border_color;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,99);
    if (EQ(new_border_color,Qforeground) || EQ(new_border_color,
	    Qbackground) || EQ(new_border_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_border_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_border_color)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    change_color_of_text_box(5,item,T,Kno_change,new_border_color,
		    Kno_change);
	    temp_1 = Nil;
	}
	else
	    temp_1 = tformat_text_string(2,string_constant_6,item);
    }
    else
	temp_1 = tformat_text_string(2,string_constant_3,new_border_color);
    return VALUES_1(temp_1);
}

/* INITIAL-STRIPE-COLOR */
Object initial_stripe_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,100);
    return VALUES_1(Qblack);
}

/* GET-STRIPE-COLOR */
Object get_stripe_color(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,101);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	temp_1 = get_connection_color(item,Qstripe_color);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    temp_1 = get_color_of_icon_region(item,Qstripe_color);
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

static Object string_constant_7;   /* "The attribute STRIPE-COLOR does not exist in ~s." */

/* SET-STRIPE-COLOR */
Object set_stripe_color(item,new_stripe_color)
    Object item, new_stripe_color;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(90,102);
    if (EQ(new_stripe_color,Qforeground) || EQ(new_stripe_color,
	    Qbackground) || EQ(new_stripe_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_stripe_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_stripe_color)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    change_color_of_connection(item,T,new_stripe_color);
	    temp_1 = Nil;
	}
	else
	    temp_1 = tformat_text_string(2,string_constant_7,item);
    }
    else
	temp_1 = tformat_text_string(2,string_constant_3,new_stripe_color);
    return VALUES_1(temp_1);
}

/* INITIAL-ICON-COLOR */
Object initial_icon_color(class_1)
    Object class_1;
{
    x_note_fn_call(90,103);
    return VALUES_1(Qblack);
}

/* GET-ICON-COLOR */
Object get_icon_color(item)
    Object item;
{
    Object temp;

    x_note_fn_call(90,104);
    temp = icon_color(item);
    return VALUES_1(temp);
}

/* SET-ICON-COLOR */
Object set_icon_color(item,new_icon_color)
    Object item, new_icon_color;
{
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(90,105);
    if (EQ(new_icon_color,Qforeground) || EQ(new_icon_color,Qbackground) 
	    || EQ(new_icon_color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_icon_color),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(new_icon_color)) {
	change_color_of_item(item,T,Qicon_color,new_icon_color);
	temp = Nil;
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
		  tformat(2,string_constant_3,new_icon_color);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

/* MOVE-ICON */
Object move_icon(entity,new_x,new_y)
    Object entity, new_x, new_y;
{
    x_note_fn_call(90,106);
    return move_item(3,entity,new_x,new_y);
}

/* MOVE-ITEM */
Object move_item varargs_1(int, n)
{
    Object item, new_x, new_y;
    Object note_as_kb_state_change_qm, temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,107);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    new_x = REQUIRED_ARG_nonrelocating();
    new_y = REQUIRED_ARG_nonrelocating();
    note_as_kb_state_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      END_ARGS_nonrelocating();
      new_x = FIXNUMP(new_x) ? new_x : l_round(new_x,_);
      new_y = FIXNUMP(new_y) ? new_y : l_round(new_y,_);
      temp = new_x;
      temp_1 = FIXNUM_MINUS(temp,item_x_position(item));
      temp = new_y;
      temp = FIXNUM_MINUS(temp,item_y_position(item));
      result = move_item_by(4,item,temp_1,temp,Note_as_kb_state_change_qm);
    POP_SPECIAL();
    return result;
}

static Object Qitem_position;      /* item-position */

/* MOVE-ITEM-BY */
Object move_item_by varargs_1(int, n)
{
    Object item, delta_x, delta_y;
    Object note_as_kb_state_change_qm, workspace_qm;
    Object do_not_note_permanent_changes_p, delta_x_in_workspace;
    Object delta_y_in_workspace, extreme_left_edge, extreme_top_edge;
    Object extreme_right_edge, extreme_bottom_edge, margin, gensymed_symbol_1;
    Object temp, sub_class_bit_vector, region;
    Object do_not_update_selection_highlights;
    Object region_invalidation_is_preferred;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(90,108);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    delta_x = REQUIRED_ARG_nonrelocating();
    delta_y = REQUIRED_ARG_nonrelocating();
    note_as_kb_state_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    3);
      END_ARGS_nonrelocating();
      workspace_qm = get_workspace_if_any(item);
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      2);
	if (workspace_qm) {
	    delta_x_in_workspace = FIXNUMP(delta_x) ? delta_x : 
		    l_round(delta_x,_);
	    gensymed_symbol = FIXNUMP(delta_y) ? IFIX(delta_y) : 
		    IFIX(l_round(delta_y,_));
	    delta_y_in_workspace = FIX( - gensymed_symbol);
	    if ( !(FIXNUM_EQ(delta_x_in_workspace,delta_y_in_workspace) && 
		    IFIX(delta_y_in_workspace) == (SI_Long)0L)) {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(item,Qitem_position);
		result = determine_extreme_edges_for_item_being_moved(item);
		MVS_4(result,extreme_left_edge,extreme_top_edge,
			extreme_right_edge,extreme_bottom_edge);
		margin = ISVREF(workspace_qm,(SI_Long)17L);
		gensymed_symbol = IFIX(delta_x_in_workspace);
		gensymed_symbol_1 = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_3 = IFIX(margin);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		gensymed_symbol_3 = IFIX(extreme_right_edge);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		gensymed_symbol = MIN(gensymed_symbol,gensymed_symbol_2);
		gensymed_symbol_1 = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_3 = IFIX(margin);
		gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		gensymed_symbol_3 = IFIX(extreme_left_edge);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		delta_x_in_workspace = FIX(MAX(gensymed_symbol,
			gensymed_symbol_2));
		gensymed_symbol = IFIX(delta_y_in_workspace);
		gensymed_symbol_1 = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_3 = IFIX(margin);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		gensymed_symbol_3 = IFIX(extreme_bottom_edge);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		gensymed_symbol = MIN(gensymed_symbol,gensymed_symbol_2);
		gensymed_symbol_1 = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_3 = IFIX(margin);
		gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		gensymed_symbol_3 = IFIX(extreme_top_edge);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		delta_y_in_workspace = FIX(MAX(gensymed_symbol,
			gensymed_symbol_2));
		temp = FIXNUM_EQ(delta_x_in_workspace,
			delta_y_in_workspace) ? 
			(IFIX(delta_y_in_workspace) == (SI_Long)0L ? T : 
			Nil) : Qnil;
		if (temp)
		    result = VALUES_1(temp);
		else {
		    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			    (SI_Long)6L)) : Nil;
		    if (gensymed_symbol_1)
			result = move_blocks_with_their_external_connections(item,
				workspace_qm,delta_x_in_workspace,
				delta_y_in_workspace);
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(item,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Entity_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_2;
			    temp_1 = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1);
			else
			    temp_1 = (SI_Long)0L != (IFIX(ISVREF(item,
				    (SI_Long)4L)) & (SI_Long)1024L);
			if (temp_1) {
			    if (EQ(Current_drawing_transfer_mode,
				    Kpaint_infered_from_xor) &&  
				    !((SI_Long)0L != (IFIX(ISVREF(item,
				    (SI_Long)5L)) & (SI_Long)1024L))) {
				region = 
					make_region_from_rectangle(extreme_left_edge,
					extreme_top_edge,
					extreme_right_edge,FIX((SI_Long)5L 
					+ IFIX(extreme_bottom_edge)));
				region = 
					add_rectangle_to_region(FIXNUM_ADD(extreme_left_edge,
					delta_x_in_workspace),
					FIXNUM_ADD(extreme_top_edge,
					delta_y_in_workspace),
					FIXNUM_ADD(extreme_right_edge,
					delta_x_in_workspace),
					FIXNUM_ADD(extreme_bottom_edge,
					delta_y_in_workspace),region);
				do_not_update_selection_highlights = T;
				PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_selection_highlights,Qdo_not_update_selection_highlights,do_not_update_selection_highlights,
					0);
				  shift_block(item,delta_x_in_workspace,
					  delta_y_in_workspace);
				POP_SPECIAL();
				move_selection_highlights(item,
					workspace_qm,delta_x_in_workspace,
					delta_y_in_workspace);
				invalidate_region_of_workspace(2,
					workspace_qm,region);
				result = reclaim_region(region);
			    }
			    else {
				region_invalidation_is_preferred = 
					(SI_Long)0L != (IFIX(ISVREF(item,
					(SI_Long)4L)) & (SI_Long)1024L) ? 
					T : Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
					1);
				  update_images_of_rectangle_of_block(item,
					  T,extreme_left_edge,
					  extreme_top_edge,
					  extreme_right_edge,
					  extreme_bottom_edge);
				  do_not_update_selection_highlights = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_selection_highlights,Qdo_not_update_selection_highlights,do_not_update_selection_highlights,
					  0);
				    shift_block(item,delta_x_in_workspace,
					    delta_y_in_workspace);
				  POP_SPECIAL();
				  move_selection_highlights(item,
					  workspace_qm,
					  delta_x_in_workspace,
					  delta_y_in_workspace);
				  result = update_images_of_rectangle_of_block(item,
					  Nil,FIXNUM_ADD(extreme_left_edge,
					  delta_x_in_workspace),
					  FIXNUM_ADD(extreme_top_edge,
					  delta_y_in_workspace),
					  FIXNUM_ADD(extreme_right_edge,
					  delta_x_in_workspace),
					  FIXNUM_ADD(extreme_bottom_edge,
					  delta_y_in_workspace));
				POP_SPECIAL();
			    }
			}
			else {
			    update_images_of_block(item,T,Nil);
			    do_not_update_selection_highlights = T;
			    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_selection_highlights,Qdo_not_update_selection_highlights,do_not_update_selection_highlights,
				    0);
			      shift_block(item,delta_x_in_workspace,
				      delta_y_in_workspace);
			    POP_SPECIAL();
			    move_selection_highlights(item,workspace_qm,
				    delta_x_in_workspace,delta_y_in_workspace);
			    result = update_images_of_block(item,Nil,Nil);
			}
		    }
		}
	    }
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TRANSFER-ITEM */
Object transfer_item varargs_1(int, n)
{
    Object item, workspace_qm, new_x_qm, new_y_qm;
    Object note_as_kb_state_change_qm;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,109);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    workspace_qm = REQUIRED_ARG_nonrelocating();
    new_x_qm = REQUIRED_ARG_nonrelocating();
    new_y_qm = REQUIRED_ARG_nonrelocating();
    note_as_kb_state_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      END_ARGS_nonrelocating();
      result = transfer_blocks_with_their_external_connections(item,
	      workspace_qm,new_x_qm,new_y_qm,Note_as_kb_state_change_qm);
    POP_SPECIAL();
    return result;
}

/* ADD-ITEM-TO-WORKSPACE */
Object add_item_to_workspace varargs_1(int, n)
{
    Object item, workspace, new_x_qm, new_y_qm;
    Object note_as_kb_state_change_qm;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,110);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    new_x_qm = REQUIRED_ARG_nonrelocating();
    new_y_qm = REQUIRED_ARG_nonrelocating();
    note_as_kb_state_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      END_ARGS_nonrelocating();
      result = transfer_blocks_with_their_external_connections(item,
	      workspace,new_x_qm,new_y_qm,Note_as_kb_state_change_qm);
    POP_SPECIAL();
    return result;
}

/* CHANGE-COLOR-OF-ICON */
Object change_color_of_icon(entity,note_as_kb_state_change_qm,new_color_qm)
    Object entity, note_as_kb_state_change_qm, new_color_qm;
{
    Object default_color, workspace_qm, new_color, color_change_pattern;
    Object stack_error_or_nil_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,111);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      if (ISVREF(entity,(SI_Long)16L)) {
	  default_color = ISVREF(ISVREF(entity,(SI_Long)16L),(SI_Long)5L);
	  if (default_color);
	  else {
	      workspace_qm = get_workspace_if_any(entity);
	      default_color = workspace_qm ? ISVREF(workspace_qm,
		      (SI_Long)22L) : Nil;
	  }
	  if (default_color);
	  else
	      default_color = Current_default_line_color;
	  new_color = new_color_qm;
	  if (new_color);
	  else
	      new_color = default_color;
	  if ( !EQ(new_color,icon_color(entity))) {
	      color_change_pattern = 
		      slot_value_cons_1(slot_value_cons_1(Qicon_color,
		      new_color),Nil);
	      stack_error_or_nil_qm = change_color_pattern_of_icon(entity,
		      Note_as_kb_state_change_qm,color_change_pattern);
	      reclaim_slot_value_tree_1(color_change_pattern);
	      result = VALUES_1(stack_error_or_nil_qm);
	  }
	  else
	      result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* SET-ICON-COLORS */
Object set_icon_colors(entity,note_as_kb_state_change_qm,new_color_pattern,
	    new_line_color_qm)
    Object entity, note_as_kb_state_change_qm, new_color_pattern;
    Object new_line_color_qm;
{
    Object do_not_note_permanent_changes_p, default_color_pattern_qm;
    Object default_line_color, region, color, ab_loop_list_, ab_loop_desetq_;
    Object temp, color_pattern_is_default_qm;
    char line_color_is_default_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(90,112);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    1);
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      0);
	default_color_pattern_qm = ISVREF(ISVREF(entity,(SI_Long)16L),
		(SI_Long)10L);
	default_line_color = ISVREF(ISVREF(entity,(SI_Long)16L),(SI_Long)5L);
	if (default_line_color);
	else
	    default_line_color = Qforeground;
	region = Nil;
	color = Nil;
	ab_loop_list_ = new_color_pattern;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	region = CAR(ab_loop_desetq_);
	color = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = assq_function(region,default_color_pattern_qm);
	if ( !EQ(color,CDR(temp))) {
	    color_pattern_is_default_qm = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	color_pattern_is_default_qm = T;
	goto end_1;
	color_pattern_is_default_qm = Qnil;
      end_1:;
	line_color_is_default_qm = EQ(new_line_color_qm,default_line_color);
	if (Note_as_kb_state_change_qm) {
	    note_kb_state_change(entity,Qicon_color);
	    note_kb_state_change(entity,Qicon_color_pattern);
	}
	if ( !TRUEP(new_line_color_qm));
	else if (line_color_is_default_qm)
	    change_icon_attribute(entity,Qline_color,Nil);
	else
	    change_icon_attribute(entity,Qline_color,new_line_color_qm);
	if (color_pattern_is_default_qm) {
	    reclaim_slot_value_tree_1(new_color_pattern);
	    result = change_icon_attribute(entity,Qicon_color_pattern,Nil);
	}
	else
	    result = change_icon_attribute(entity,Qicon_color_pattern,
		    new_color_pattern);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Executing_change_item_color_instruction_p, Qexecuting_change_item_color_instruction_p);

static Object Qmissing_color_region;  /* missing-color-region */

static Object Qunnamed_color_region;  /* unnamed-color-region */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qrevise_icon_rendering;  /* revise-icon-rendering */

/* CHANGE-COLOR-PATTERN-OF-ICON */
Object change_color_pattern_of_icon(entity,note_as_kb_state_change_qm,
	    color_change_pattern)
    Object entity, note_as_kb_state_change_qm, color_change_pattern;
{
    Object current_color_pattern, new_color_pattern, new_line_color_qm;
    Object any_changes_qm, error_qm, new_color, ab_loop_list_, ab_loop_it_;
    Object ab_loop_desetq_, becoming_transparent_qm, stack_error_or_nil_qm;
    Object region, color, new_region_and_color_qm, x2, this_block;
    Object superblock_qm, gensymed_symbol, sub_class_bit_vector, workspace_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, changed_regions;
    Object current_region, current_color, new_region, ab_loop_list__1;
    Object current_color_list, new_color_list, new_cons, temp_1, svref_arg_2;
    Object svref_new_value, last_1, next_qm;
    Object changing_colors_of_graphic_elements_qm;
    Object current_drawing_transfer_mode, left, top, right, bottom;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long edge_overflow_if_any;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(90,113);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    2);
      if (ISVREF(entity,(SI_Long)16L)) {
	  current_color_pattern = current_color_pattern_of_entity(entity);
	  new_color_pattern = 
		  copy_tree_using_slot_value_conses_1(current_color_pattern);
	  new_line_color_qm = Nil;
	  any_changes_qm = Nil;
	  error_qm = Nil;
	  new_color = Nil;
	  ab_loop_list_ = color_change_pattern;
	  ab_loop_it_ = Nil;
	  ab_loop_desetq_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  new_color = CDR(ab_loop_desetq_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loop_it_ = EQ(new_color,Qtransparent) ? T : Nil;
	  if (ab_loop_it_) {
	      becoming_transparent_qm = ab_loop_it_;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  becoming_transparent_qm = Qnil;
	end_1:;
	  stack_error_or_nil_qm = Nil;
	  region = Nil;
	  color = Nil;
	  ab_loop_list_ = color_change_pattern;
	  new_region_and_color_qm = Nil;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  region = CAR(ab_loop_desetq_);
	  color = CDR(ab_loop_desetq_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  new_region_and_color_qm = assq_function(region,new_color_pattern);
	  if (EQ(region,Qicon_color) &&  !TRUEP(new_region_and_color_qm)) {
	      new_line_color_qm = color;
	      any_changes_qm = T;
	  }
	  else if ( !TRUEP(new_region_and_color_qm)) {
	      if (Executing_change_item_color_instruction_p) {
		  stack_error_or_nil_qm = 
			  gensym_cons_1(Qmissing_color_region,region);
		  error_qm = T;
		  goto end_loop_1;
	      }
	      else {
		  warn_of_missing_color_region(entity,region);
		  error_qm = T;
	      }
	  }
	  else if (EQ(CAR(new_region_and_color_qm),
		  CDR(new_region_and_color_qm))) {
	      if (Executing_change_item_color_instruction_p) {
		  stack_error_or_nil_qm = 
			  gensym_cons_1(Qunnamed_color_region,region);
		  error_qm = T;
		  goto end_loop_1;
	      }
	      else {
		  warn_of_unnamed_color_region(entity,region);
		  error_qm = T;
	      }
	  }
	  else if ( !EQ(color,CDR(new_region_and_color_qm))) {
	      any_changes_qm = T;
	      M_CDR(new_region_and_color_qm) = color;
	  }
	  goto next_loop_1;
	end_loop_1:;
	  if (error_qm ||  !TRUEP(any_changes_qm))
	      reclaim_slot_value_tree_1(new_color_pattern);
	  else {
	      if (EQ(Current_drawing_transfer_mode,
		      Kpaint_infered_from_xor) && 
		      EQ(Current_drawing_priority,
		      Kdraw_as_late_as_possible) &&  
		      !TRUEP(becoming_transparent_qm)) {
		  if (SIMPLE_VECTOR_P(entity) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(entity,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(entity,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  temp =  !(temp ? (SI_Long)0L != (IFIX(ISVREF(entity,
			  (SI_Long)5L)) & (SI_Long)1024L) : 
			  TRUEP(render_connection_in_xor_overlay_p_function(entity)));
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  this_block = entity;
		  superblock_qm = Nil;
		next_loop_2:
		  gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,
			  (SI_Long)14L));
		  gensymed_symbol = gensymed_symbol ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) 
			  : Nil;
		  superblock_qm = gensymed_symbol;
		  if ( !TRUEP(superblock_qm)) {
		      sub_class_bit_vector = ISVREF(ISVREF(this_block,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Workspace_class_description,
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
		      workspace_qm = temp ? this_block : Nil;
		      goto end_2;
		  }
		  this_block = superblock_qm;
		  goto next_loop_2;
		end_loop_2:
		  workspace_qm = Qnil;
		end_2:;
		  set_icon_colors(entity,Note_as_kb_state_change_qm,
			  new_color_pattern,new_line_color_qm);
		  if (workspace_qm) {
		      region = Nil;
		      color = Nil;
		      ab_loop_list_ = color_change_pattern;
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		      ab_loop_desetq_ = Nil;
		    next_loop_3:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_3;
		      ab_loop_desetq_ = M_CAR(ab_loop_list_);
		      region = CAR(ab_loop_desetq_);
		      color = CDR(ab_loop_desetq_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      ab_loopvar__2 = gensym_cons_1(region,Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_3;
		    end_loop_3:
		      changed_regions = ab_loopvar_;
		      goto end_3;
		      changed_regions = Qnil;
		    end_3:;
		      invalidate_color_of_block(workspace_qm,entity,
			      changed_regions);
		      reclaim_gensym_list_1(changed_regions);
		  }
		  if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
			  (SI_Long)2097152L))
		      update_icon_views(entity);
	      }
	      else {
		  current_region = Nil;
		  current_color = Nil;
		  ab_loop_list_ = current_color_pattern;
		  new_region = Nil;
		  new_color = Nil;
		  ab_loop_list__1 = new_color_pattern;
		  current_color_list = Nil;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  new_color_list = Nil;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loop_desetq_ = Nil;
		next_loop_4:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_4;
		  ab_loop_desetq_ = M_CAR(ab_loop_list_);
		  current_region = CAR(ab_loop_desetq_);
		  current_color = CDR(ab_loop_desetq_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_4;
		  ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		  new_region = CAR(ab_loop_desetq_);
		  new_color = CDR(ab_loop_desetq_);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  new_cons = ISVREF(Available_gensym_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp_1 = Available_gensym_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp_1,svref_arg_2) = svref_new_value;
		      if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp_1 = Available_gensym_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_gensym_cons_pool();
		  M_CAR(gensymed_symbol) = current_color;
		  M_CDR(gensymed_symbol) = Nil;
		  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		  ab_loopvar__1 = gensymed_symbol;
		  if (ab_loopvar_)
		      M_CDR(ab_loopvar_) = ab_loopvar__1;
		  else
		      current_color_list = ab_loopvar__1;
		  ab_loopvar_ = ab_loopvar__1;
		  new_cons = ISVREF(Available_gensym_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp_1 = Available_gensym_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp_1,svref_arg_2) = svref_new_value;
		      if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp_1 = Available_gensym_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_gensym_cons_pool();
		  M_CAR(gensymed_symbol) = new_color;
		  M_CDR(gensymed_symbol) = Nil;
		  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		  ab_loopvar__1 = gensymed_symbol;
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__1;
		  else
		      new_color_list = ab_loopvar__1;
		  ab_loopvar__2 = ab_loopvar__1;
		  goto next_loop_4;
		end_loop_4:
		  if (EQ(Current_drawing_transfer_mode,
			  Kpaint_infered_from_xor) && 
			      becoming_transparent_qm) {
		      if (SIMPLE_VECTOR_P(entity) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(entity,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(entity,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  redraw_transfer_representations_of_block(entity,T);
		      if (current_color_list) {
			  last_1 = current_color_list;
			  next_qm = Nil;
			next_loop_5:
			  next_qm = M_CDR(last_1);
			  if ( !TRUEP(next_qm))
			      goto end_loop_5;
			  inline_note_reclaim_cons(last_1,Qab_gensym);
			  last_1 = next_qm;
			  goto next_loop_5;
			end_loop_5:
			  inline_note_reclaim_cons(last_1,Qab_gensym);
			  if (ISVREF(Available_gensym_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_1 = 
				      ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_1) = current_color_list;
			      temp_1 = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = last_1;
			  }
			  else {
			      temp_1 = Available_gensym_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = current_color_list;
			      temp_1 = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = last_1;
			  }
			  M_CDR(last_1) = Nil;
		      }
		      if (new_color_list) {
			  last_1 = new_color_list;
			  next_qm = Nil;
			next_loop_6:
			  next_qm = M_CDR(last_1);
			  if ( !TRUEP(next_qm))
			      goto end_loop_6;
			  inline_note_reclaim_cons(last_1,Qab_gensym);
			  last_1 = next_qm;
			  goto next_loop_6;
			end_loop_6:
			  inline_note_reclaim_cons(last_1,Qab_gensym);
			  if (ISVREF(Available_gensym_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_1 = 
				      ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_1) = new_color_list;
			      temp_1 = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = last_1;
			  }
			  else {
			      temp_1 = Available_gensym_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = new_color_list;
			      temp_1 = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_1,svref_arg_2) = last_1;
			  }
			  M_CDR(last_1) = Nil;
		      }
		      set_icon_colors(entity,Note_as_kb_state_change_qm,
			      new_color_pattern,new_line_color_qm);
		      if (SIMPLE_VECTOR_P(entity) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(entity,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(entity,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  redraw_transfer_representations_of_block(entity,Nil);
		      invalidate_region_for_block_or_connection(entity);
		  }
		  else {
		      if (SIMPLE_VECTOR_P(entity) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(entity,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(entity,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  sub_class_bit_vector = ISVREF(ISVREF(entity,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Entity_class_description,
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
		      }
		      else
			  temp = TRUEP(Nil);
		      edge_overflow_if_any = temp ? (SI_Long)1L : (SI_Long)0L;
		      changing_colors_of_graphic_elements_qm = T;
		      current_drawing_transfer_mode = 
			      Current_drawing_transfer_mode;
		      if (SIMPLE_VECTOR_P(entity) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(entity,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(entity,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  this_block = entity;
			  superblock_qm = Nil;
			next_loop_7:
			  gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  superblock_qm = gensymed_symbol;
			  if ( !TRUEP(superblock_qm)) {
			      sub_class_bit_vector = 
				      ISVREF(ISVREF(this_block,
				      (SI_Long)1L),(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Workspace_class_description,
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
					  superior_class_bit_number & 
					  (SI_Long)7L;
				  gensymed_symbol_2 = gensymed_symbol_2 << 
					  gensymed_symbol_3;
				  gensymed_symbol_1 = gensymed_symbol_1 & 
					  gensymed_symbol_2;
				  temp = (SI_Long)0L < gensymed_symbol_1;
			      }
			      else
				  temp = TRUEP(Nil);
			      workspace_qm = temp ? this_block : Nil;
			      goto end_4;
			  }
			  this_block = superblock_qm;
			  goto next_loop_7;
			end_loop_7:
			  workspace_qm = Qnil;
			end_4:;
		      }
		      else
			  workspace_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
				0);
			  if (SIMPLE_VECTOR_P(entity) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) 
				  > (SI_Long)2L &&  !EQ(ISVREF(entity,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(entity,(SI_Long)1L);
			      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp ? (SI_Long)0L != (IFIX(ISVREF(entity,
				  (SI_Long)5L)) & (SI_Long)1024L) : 
				  TRUEP(render_connection_in_xor_overlay_p_function(entity)))
			      Current_drawing_transfer_mode = Kxor;
			  result = local_edges_of_block_or_connection(entity);
			  MVS_4(result,left,top,right,bottom);
			  update_images(13,Nil,entity,entity,left,top,
				  FIX(IFIX(right) + edge_overflow_if_any),
				  FIX(IFIX(bottom) + edge_overflow_if_any),
				  Nil,Qrevise_icon_rendering,entity,
				  current_color_list,new_color_list,
				  new_line_color_qm);
			  if (SIMPLE_VECTOR_P(entity) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) 
				  > (SI_Long)2L &&  !EQ(ISVREF(entity,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(entity,(SI_Long)1L);
			      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      redraw_transfer_representations_of_block(entity,
				      T);
			  if (current_color_list) {
			      last_1 = current_color_list;
			      next_qm = Nil;
			    next_loop_8:
			      next_qm = M_CDR(last_1);
			      if ( !TRUEP(next_qm))
				  goto end_loop_8;
			      inline_note_reclaim_cons(last_1,Qab_gensym);
			      last_1 = next_qm;
			      goto next_loop_8;
			    end_loop_8:
			      inline_note_reclaim_cons(last_1,Qab_gensym);
			      if (ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp_1 = 
					  ISVREF(Available_gensym_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp_1) = current_color_list;
				  temp_1 = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = last_1;
			      }
			      else {
				  temp_1 = Available_gensym_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = 
					  current_color_list;
				  temp_1 = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = last_1;
			      }
			      M_CDR(last_1) = Nil;
			  }
			  if (new_color_list) {
			      last_1 = new_color_list;
			      next_qm = Nil;
			    next_loop_9:
			      next_qm = M_CDR(last_1);
			      if ( !TRUEP(next_qm))
				  goto end_loop_9;
			      inline_note_reclaim_cons(last_1,Qab_gensym);
			      last_1 = next_qm;
			      goto next_loop_9;
			    end_loop_9:
			      inline_note_reclaim_cons(last_1,Qab_gensym);
			      if (ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp_1 = 
					  ISVREF(Available_gensym_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp_1) = new_color_list;
				  temp_1 = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = last_1;
			      }
			      else {
				  temp_1 = Available_gensym_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = new_color_list;
				  temp_1 = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_1,svref_arg_2) = last_1;
			      }
			      M_CDR(last_1) = Nil;
			  }
			  set_icon_colors(entity,
				  Note_as_kb_state_change_qm,
				  new_color_pattern,new_line_color_qm);
			  if (SIMPLE_VECTOR_P(entity) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) 
				  > (SI_Long)2L &&  !EQ(ISVREF(entity,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(entity,(SI_Long)1L);
			      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      redraw_transfer_representations_of_block(entity,
				      Nil);
			  if ( !EQ(Current_drawing_transfer_mode,
				  Kpaint_infered_from_xor)) {
			      if (SIMPLE_VECTOR_P(entity) && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) 
				      > (SI_Long)2L &&  !EQ(ISVREF(entity,
				      (SI_Long)1L),Qavailable_frame_vector)) {
				  x2 = ISVREF(entity,(SI_Long)1L);
				  temp = SIMPLE_VECTOR_P(x2) && 
					  EQ(ISVREF(x2,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  ? TRUEP(x2) : TRUEP(Qnil);
			      }
			      else
				  temp = TRUEP(Nil);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp) {
			      sub_class_bit_vector = ISVREF(ISVREF(entity,
				      (SI_Long)1L),(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Meter_class_description,
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
					  superior_class_bit_number & 
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
			  if (temp ? TRUEP(workspace_qm) : TRUEP(Nil)) {
			      region = 
				      bounding_region_of_block_or_connection(get_ruling_for_meter(entity));
			      invalidate_region_of_workspace(2,
				      workspace_qm,region);
			      reclaim_region(region);
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
			  (SI_Long)2097152L))
		      update_icon_views(entity);
	      }
	  }
	  result = VALUES_1(stack_error_or_nil_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* ICON-HAS-REGION-P */
Object icon_has_region_p(entity,region)
    Object entity, region;
{
    Object icon_description_qm;

    x_note_fn_call(90,114);
    icon_description_qm = ISVREF(entity,(SI_Long)16L);
    if (icon_description_qm)
	return assq_function(region,ISVREF(icon_description_qm,(SI_Long)10L));
    else
	return VALUES_1(Nil);
}

static Object Qillegal_colors;     /* illegal-colors */

/* CHANGE-COLOR-OF-ITEM */
Object change_color_of_item(item,note_as_kb_state_change_qm,
	    specific_region_qm,color_or_pattern)
    Object item, note_as_kb_state_change_qm, specific_region_qm;
    Object color_or_pattern;
{
    Object specific_region_ok_qm, gensymed_symbol, sub_class_bit_vector;
    Object temp_1, color_change_pattern_qm, color, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, illegal_colors_qm;
    Object stack_error_or_nil_qm, temp_2, temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(90,115);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      perform_any_deferred_icon_set_up(item);
      if ( !TRUEP(specific_region_qm))
	  specific_region_ok_qm =  ! !TRUEP(color_or_pattern) ? T : Nil;
      else if (EQ(specific_region_qm,Qicon_color) || EQ(specific_region_qm,
	      Qstripe_color) || EQ(specific_region_qm,Qbackground_color) 
	      || EQ(specific_region_qm,Qforeground_color) || 
	      EQ(specific_region_qm,Qborder_color) || 
	      EQ(specific_region_qm,Qtext_color)) {
	  gensymed_symbol = ISVREF(item,(SI_Long)1L);
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	      temp_1 = EQ(specific_region_qm,Qstripe_color) ? T : Nil;
	  else {
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		  temp_1 = EQ(specific_region_qm,Qicon_color) ? T : Nil;
	      else {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Text_box_class_description,
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      temp_1 = EQ(specific_region_qm,Qbackground_color) ? 
			      T : Nil;
		      if (temp_1);
		      else
			  temp_1 = EQ(specific_region_qm,Qborder_color) ? 
				  T : Nil;
		      if (temp_1);
		      else
			  temp_1 = EQ(specific_region_qm,Qtext_color) ? T :
				   Nil;
		  }
		  else {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Workspace_class_description,
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
			  temp_1 = EQ(specific_region_qm,
				  Qbackground_color) ? T : Nil;
			  if (temp_1);
			  else
			      temp_1 = EQ(specific_region_qm,
				      Qforeground_color) ? T : Nil;
		      }
		      else
			  temp_1 = Qnil;
		  }
	      }
	  }
	  if (temp_1)
	      specific_region_ok_qm = T;
	  else {
	      warn_of_invalid_color_attribute(item,specific_region_qm);
	      specific_region_ok_qm = Nil;
	  }
      }
      else {
	  gensymed_symbol = ISVREF(item,(SI_Long)1L);
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	  if (temp);
	  else {
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	  if (temp)
	      specific_region_ok_qm = T;
	  else {
	      warn_of_invalid_color_attribute(item,specific_region_qm);
	      specific_region_ok_qm = Nil;
	  }
      }
      if (specific_region_ok_qm) {
	  color_change_pattern_qm = CONSP(color_or_pattern) ? 
		  color_or_pattern :  !((EQ(specific_region_qm,
		  Qicon_color) || EQ(specific_region_qm,Qstripe_color) || 
		  EQ(specific_region_qm,Qbackground_color) || 
		  EQ(specific_region_qm,Qforeground_color) || 
		  EQ(specific_region_qm,Qborder_color) || 
		  EQ(specific_region_qm,Qtext_color)) &&  
		  !EQ(specific_region_qm,Qicon_color)) ? 
		  gensym_cons_1(gensym_cons_1(specific_region_qm,
		  color_or_pattern),Nil) : Nil;
	  if (color_change_pattern_qm) {
	      color = Nil;
	      ab_loop_list_ = color_change_pattern_qm;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loop_desetq_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      color = CDR(ab_loop_desetq_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !(EQ(color,Qforeground) || EQ(color,Qbackground) || 
		      EQ(color,Qtransparent) || 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
		      Qcolor_value_vector_index_and_intensity) || 
		      rgb_color_p(color))) {
		  ab_loopvar__2 = gensym_cons_1(color,Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
	      }
	      goto next_loop;
	    end_loop:
	      illegal_colors_qm = ab_loopvar_;
	      goto end_1;
	      illegal_colors_qm = Qnil;
	    end_1:;
	  }
	  else if ( !(EQ(color_or_pattern,Qforeground) || 
		  EQ(color_or_pattern,Qbackground) || EQ(color_or_pattern,
		  Qtransparent) || 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(color_or_pattern),
		  Qcolor_value_vector_index_and_intensity) || 
		  rgb_color_p(color_or_pattern)))
	      illegal_colors_qm = gensym_cons_1(color_or_pattern,Nil);
	  else
	      illegal_colors_qm = Qnil;
	  stack_error_or_nil_qm = Nil;
	  if (illegal_colors_qm) {
	      if (Executing_change_item_color_instruction_p)
		  stack_error_or_nil_qm = gensym_cons_1(Qillegal_colors,
			  illegal_colors_qm);
	      else {
		  warn_of_illegal_colors(illegal_colors_qm);
		  reclaim_gensym_list_1(illegal_colors_qm);
	      }
	  }
	  else {
	      gensymed_symbol = ISVREF(item,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	      if (temp) {
		  if (color_change_pattern_qm)
		      change_color_pattern_of_connection(item,
			      Note_as_kb_state_change_qm,
			      color_change_pattern_qm);
		  else
		      change_color_of_connection(item,
			      Note_as_kb_state_change_qm,color_or_pattern);
	      }
	      else {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      stack_error_or_nil_qm = color_change_pattern_qm ? 
			      change_color_pattern_of_icon(item,
			      Note_as_kb_state_change_qm,
			      color_change_pattern_qm) : 
			      change_color_of_icon(item,
			      Note_as_kb_state_change_qm,color_or_pattern);
		  else {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Text_box_class_description,
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
			  if (color_change_pattern_qm) {
			      temp_1 = Note_as_kb_state_change_qm;
			      temp_2 = assq_function(Qbackground_color,
				      color_change_pattern_qm);
			      temp_2 = CDR(temp_2);
			      if (temp_2);
			      else
				  temp_2 = Kno_change;
			      temp_3 = assq_function(Qborder_color,
				      color_change_pattern_qm);
			      temp_3 = CDR(temp_3);
			      if (temp_3);
			      else
				  temp_3 = Kno_change;
			      temp_4 = assq_function(Qtext_color,
				      color_change_pattern_qm);
			      temp_4 = CDR(temp_4);
			      if (temp_4);
			      else
				  temp_4 = Kno_change;
			      change_color_of_text_box(5,item,temp_1,
				      temp_2,temp_3,temp_4);
			  }
			  else
			      change_color_of_text_box(5,item,
				      Note_as_kb_state_change_qm,
				      EQ(specific_region_qm,
				      Qbackground_color) ? 
				      color_or_pattern : Kno_change,
				      EQ(specific_region_qm,Qborder_color) 
				      ? color_or_pattern : Kno_change,
				      EQ(specific_region_qm,Qtext_color) ? 
				      color_or_pattern : Kno_change);
		      }
		      else {
			  sub_class_bit_vector = ISVREF(gensymed_symbol,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Workspace_class_description,
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
			      if (color_change_pattern_qm) {
				  temp_1 = Note_as_kb_state_change_qm;
				  temp_2 = assq_function(Qbackground_color,
					  color_change_pattern_qm);
				  temp_2 = CDR(temp_2);
				  if (temp_2);
				  else
				      temp_2 = Kno_change;
				  temp_3 = assq_function(Qforeground_color,
					  color_change_pattern_qm);
				  temp_3 = CDR(temp_3);
				  if (temp_3);
				  else
				      temp_3 = Kno_change;
				  change_color_of_workspace(item,temp_1,
					  temp_2,temp_3);
			      }
			      else
				  change_color_of_workspace(item,
					  Note_as_kb_state_change_qm,
					  EQ(specific_region_qm,
					  Qbackground_color) ? 
					  color_or_pattern : Kno_change,
					  EQ(specific_region_qm,
					  Qforeground_color) ? 
					  color_or_pattern : Kno_change);
			  }
		      }
		  }
	      }
	      if (G2_has_v5_mode_windows_p) {
		  temp = TRUEP(stack_error_or_nil_qm);
		  if (temp);
		  else {
		      sub_class_bit_vector = ISVREF(ISVREF(item,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Workspace_class_description,
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
		  if ( !temp)
		      send_ws_representations_item_color_pattern_change(item,
			      specific_region_qm,color_or_pattern);
	      }
	      update_subscriptions_for_color_change(item,color_or_pattern,
		      specific_region_qm);
	  }
	  if ( !EQ(color_change_pattern_qm,color_or_pattern))
	      reclaim_gensym_tree_1(color_change_pattern_qm);
	  result = VALUES_1(stack_error_or_nil_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* ADJUST-ICON-RENDERING-USAGE-COUNTS */
Object adjust_icon_rendering_usage_counts(block,image_plane_qm,now_showing_qm)
    Object block, image_plane_qm, now_showing_qm;
{
    Object sub_class_bit_vector, window_qm, icon_rendering, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value, temp_1;
    char temp;

    x_note_fn_call(90,116);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    if (temp ? TRUEP(ISVREF(block,(SI_Long)16L)) : TRUEP(Nil)) {
	window_qm = image_plane_qm ? ISVREF(ISVREF(image_plane_qm,
		(SI_Long)2L),(SI_Long)2L) : Qnil;
	icon_rendering = Nil;
	ab_loop_list_ = ISVREF(ISVREF(block,(SI_Long)16L),(SI_Long)9L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	icon_rendering = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(window_qm) || EQ(window_qm,ISVREF(icon_rendering,
		(SI_Long)17L))) {
	    if (now_showing_qm)
		svref_new_value = IFIX(FIXNUM_ADD1(ISVREF(icon_rendering,
			(SI_Long)16L)));
	    else {
		temp_1 = IFIX(FIXNUM_SUB1(ISVREF(icon_rendering,
			(SI_Long)16L)));
		svref_new_value = MAX((SI_Long)0L,temp_1);
	    }
	    ISVREF(icon_rendering,(SI_Long)16L) = FIX(svref_new_value);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-COLOR-PATTERN-OF-ITEM */
Object get_color_pattern_of_item varargs_1(int, n)
{
    Object item;
    Object state_qm, explicit_qm, include_unnamed_qm, override_only_qm;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,117);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    explicit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    include_unnamed_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    override_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	return get_connection_color_pattern(5,item,state_qm,explicit_qm,
		include_unnamed_qm,override_only_qm);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp)
	    return get_icon_color_pattern(5,item,state_qm,explicit_qm,
		    include_unnamed_qm,override_only_qm);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		return get_workspace_color_pattern(5,item,state_qm,
			explicit_qm,include_unnamed_qm,override_only_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
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
		    return get_text_box_color_pattern(5,item,state_qm,
			    explicit_qm,include_unnamed_qm,override_only_qm);
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qcurrent;            /* current */

static Object Qpermanent;          /* permanent */

static Object Qoriginal_kb_state_plist;  /* original-kb-state-plist */

static Object Qconnection_color_pattern;  /* connection-color-pattern */

/* GET-CONNECTION-COLOR-PATTERN */
Object get_connection_color_pattern varargs_1(int, n)
{
    Object connection;
    Object state_qm, explicit_qm, include_unnamed_qm, override_only_qm;
    Object color_or_region, color, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, base_color_pattern;
    Object override_pattern;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,118);
    INIT_ARGS_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    explicit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    include_unnamed_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    override_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    color_or_region = Nil;
    color = Nil;
    ab_loop_list_ = 
	    get_cross_section_regions_function(get_slot_init_form(2,
	    ISVREF(ISVREF(connection,(SI_Long)1L),(SI_Long)1L),
	    Qcross_section_pattern));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color_or_region = CAR(ab_loop_desetq_);
    color = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (include_unnamed_qm ||  !EQ(color_or_region,color)) {
	ab_loopvar__2 = 
		slot_value_cons_1(slot_value_cons_1(color_or_region,color),
		Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    base_color_pattern = ab_loopvar_;
    goto end_1;
    base_color_pattern = Qnil;
  end_1:;
    if (EQ(state_qm,Qnil) || EQ(state_qm,Qcurrent) || EQ(state_qm,
		Qpermanent)) {
	override_pattern = EQ(state_qm,Qpermanent) ? 
		getf(get_lookup_slot_value_given_default(connection,
		Qoriginal_kb_state_plist,Nil),Qconnection_color_pattern,_) 
		: Nil;
	if (override_pattern);
	else
	    override_pattern = 
		    get_cross_section_regions_function(get_slot_value_function(connection,
		    Qcross_section_pattern,Nil));
    }
    else
	override_pattern = Nil;
    if (override_only_qm) {
	reclaim_slot_value(base_color_pattern);
	return normalize_color_pattern(override_pattern);
    }
    else
	return merge_color_patterns(override_pattern,base_color_pattern, 
		!TRUEP(explicit_qm) ? T : Nil);
}

/* GET-ICON-COLOR-PATTERN */
Object get_icon_color_pattern varargs_1(int, n)
{
    Object entity;
    Object state_qm, explicit_qm, include_unnamed_qm, override_only_qm;
    Object color_or_region, color, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, base_color_pattern;
    Object override_pattern;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,119);
    INIT_ARGS_nonrelocating();
    entity = REQUIRED_ARG_nonrelocating();
    state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    explicit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    include_unnamed_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    override_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    color_or_region = Nil;
    color = Nil;
    ab_loop_list_ = ISVREF(ISVREF(entity,(SI_Long)16L),(SI_Long)10L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color_or_region = CAR(ab_loop_desetq_);
    color = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (include_unnamed_qm ||  !EQ(color_or_region,color)) {
	ab_loopvar__2 = 
		slot_value_cons_1(slot_value_cons_1(color_or_region,color),
		Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    base_color_pattern = ab_loopvar_;
    goto end_1;
    base_color_pattern = Qnil;
  end_1:;
    if (EQ(state_qm,Qnil) || EQ(state_qm,Qcurrent) || EQ(state_qm,
		Qpermanent)) {
	override_pattern = EQ(state_qm,Qpermanent) ? 
		getf(get_lookup_slot_value_given_default(entity,
		Qoriginal_kb_state_plist,Nil),Qicon_color_pattern,_) : Nil;
	if (override_pattern);
	else
	    override_pattern = getf(ISVREF(entity,(SI_Long)17L),
		    Qicon_color_pattern,_);
    }
    else
	override_pattern = Nil;
    if (override_only_qm) {
	reclaim_slot_value(base_color_pattern);
	return normalize_color_pattern(override_pattern);
    }
    else
	return merge_color_patterns(override_pattern,base_color_pattern, 
		!TRUEP(explicit_qm) ? T : Nil);
}

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qworkspace_foreground_color_qm;  /* workspace-foreground-color? */

static Object Kbg;                 /* :bg */

static Object Kfg;                 /* :fg */

static Object list_constant_10;    /* # */

static Object Qworkspace_color_pattern;  /* workspace-color-pattern */

/* GET-WORKSPACE-COLOR-PATTERN */
Object get_workspace_color_pattern varargs_1(int, n)
{
    Object workspace;
    Object state_qm, explicit_qm, override_only_qm, temp, temp_1;
    Object base_color_pattern, override_pattern;
    Declare_varargs_nonrelocating;

    x_note_fn_call(90,120);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    explicit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    override_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = get_slot_init_form(2,ISVREF(ISVREF(workspace,(SI_Long)1L),
	    (SI_Long)1L),Qworkspace_background_color_qm);
    if (temp);
    else
	temp = explicit_qm ? Qwhite : Nil;
    temp_1 = get_slot_init_form(2,ISVREF(ISVREF(workspace,(SI_Long)1L),
	    (SI_Long)1L),Qworkspace_foreground_color_qm);
    if (temp_1);
    else
	temp_1 = explicit_qm ? Qblack : Nil;
    base_color_pattern = nsubst(3,temp,Kbg,nsubst(3,temp_1,Kfg,
	    copy_for_slot_value(list_constant_10)));
    if (EQ(state_qm,Qnil) || EQ(state_qm,Qcurrent) || EQ(state_qm,
		Qpermanent)) {
	override_pattern = EQ(state_qm,Qpermanent) ? 
		copy_for_slot_value(getf(get_lookup_slot_value_given_default(workspace,
		Qoriginal_kb_state_plist,Nil),Qworkspace_color_pattern,_)) 
		: Nil;
	if (override_pattern);
	else {
	    temp_1 = ISVREF(workspace,(SI_Long)21L);
	    override_pattern = nsubst(3,temp_1,Kbg,nsubst(3,
		    ISVREF(workspace,(SI_Long)22L),Kfg,
		    copy_for_slot_value(list_constant_10)));
	}
    }
    else
	override_pattern = Nil;
    if (override_only_qm) {
	reclaim_slot_value(base_color_pattern);
	return VALUES_1(override_pattern);
    }
    else {
	temp_1 = merge_color_patterns(override_pattern,base_color_pattern, 
		!TRUEP(explicit_qm) ? T : Nil);
	reclaim_slot_value(override_pattern);
	return VALUES_1(temp_1);
    }
}

static Object Kborder;             /* :border */

static Object Ktext;               /* :text */

static Object list_constant_11;    /* # */

static Object Qtext_box_color_pattern;  /* text-box-color-pattern */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* GET-TEXT-BOX-COLOR-PATTERN */
Object get_text_box_color_pattern varargs_1(int, n)
{
    Object text_box;
    Object state_qm, explicit_qm, override_only_qm, text_cell_plist;
    Object text_box_format, temp, temp_1, temp_2, base_color_pattern;
    Object override_pattern, symbol, property_name, skip_list, key_value;
    Object marked, pred, curr, succ, reference, entry_hash, gensymed_symbol;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object text_cell_plist_for_class;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(90,121);
    INIT_ARGS_nonrelocating();
    text_box = REQUIRED_ARG_nonrelocating();
    state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    explicit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    override_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    text_cell_plist = get_slot_value_function(text_box,
	    Qtext_cell_plist_for_text_box,Nil);
    text_box_format = get_slot_value_function(text_box,Qtext_box_format,Nil);
    temp = get_slot_value_function(text_box_format,
	    Qtext_cell_background_color_qm,Nil);
    if (temp);
    else
	temp = explicit_qm ? Qtransparent : Nil;
    temp_1 = get_slot_value_function(text_box_format,
	    Qtext_box_border_color_qm,Nil);
    if (temp_1);
    else
	temp_1 = explicit_qm ? Current_default_line_color : Nil;
    temp_2 = get_slot_value_function(text_box_format,
	    Qtext_cell_line_color_qm,Nil);
    if (temp_2);
    else
	temp_2 = explicit_qm ? Current_default_line_color : Nil;
    base_color_pattern = nsubst(3,temp,Kbg,nsubst(3,temp_1,Kborder,
	    nsubst(3,temp_2,Ktext,copy_for_slot_value(list_constant_11))));
    if (EQ(state_qm,Qnil) || EQ(state_qm,Qcurrent) || EQ(state_qm,
		Qpermanent)) {
	override_pattern = EQ(state_qm,Qpermanent) ? 
		copy_for_slot_value(getf(get_lookup_slot_value_given_default(text_box,
		Qoriginal_kb_state_plist,Nil),Qtext_box_color_pattern,_)) :
		 Nil;
	if (override_pattern);
	else {
	    temp = getf(text_cell_plist,Qbackground_color,_);
	    temp_2 = getf(text_cell_plist,Qborder_color,_);
	    override_pattern = nsubst(3,temp,Kbg,nsubst(3,temp_2,Kborder,
		    nsubst(3,getf(text_cell_plist,Qline_color,_),Ktext,
		    copy_for_slot_value(list_constant_11))));
	}
    }
    else if (EQ(state_qm,Qdefault)) {
	symbol = ISVREF(ISVREF(text_box,(SI_Long)1L),(SI_Long)1L);
	property_name = Class_description_gkbprop;
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol;
	key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_2);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_2);
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
	    gensymed_symbol = symbol;
	    temp = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		    Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_2);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_2);
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_2);
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_2);
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
	text_cell_plist_for_class = 
		ISVREF(get_slot_description_of_class_description_function(Qtext_cell_plist_for_text_box,
		gensymed_symbol,Nil),(SI_Long)6L);
	temp = getf(text_cell_plist_for_class,Qbackground_color,_);
	temp_2 = getf(text_cell_plist_for_class,Qborder_color,_);
	override_pattern = nsubst(3,temp,Kbg,nsubst(3,temp_2,Kborder,
		nsubst(3,getf(text_cell_plist_for_class,Qline_color,_),
		Ktext,copy_for_slot_value(list_constant_11))));
    }
    else
	override_pattern = Qnil;
    if (override_only_qm) {
	reclaim_slot_value(base_color_pattern);
	return VALUES_1(override_pattern);
    }
    else {
	temp_2 = merge_color_patterns(override_pattern,base_color_pattern, 
		!TRUEP(explicit_qm) ? T : Nil);
	reclaim_slot_value(override_pattern);
	return VALUES_1(temp_2);
    }
}

/* MERGE-COLOR-PATTERNS */
Object merge_color_patterns(override_pattern,base_color_pattern,
	    null_colors_can_override_qm)
    Object override_pattern, base_color_pattern, null_colors_can_override_qm;
{
    Object color_or_region, color_qm, ab_loop_list_, entry_in_base;
    Object ab_loop_desetq_;

    x_note_fn_call(90,122);
    color_or_region = Nil;
    color_qm = Nil;
    ab_loop_list_ = override_pattern;
    entry_in_base = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color_or_region = CAR(ab_loop_desetq_);
    color_qm = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    entry_in_base = assq_function(color_or_region,base_color_pattern);
    if ( !EQ(color_or_region,color_qm) && entry_in_base && (color_qm || 
	    null_colors_can_override_qm))
	M_CDR(entry_in_base) = color_qm;
    goto next_loop;
  end_loop:;
    return VALUES_1(base_color_pattern);
}

/* NORMALIZE-COLOR-PATTERN */
Object normalize_color_pattern(override_pattern)
    Object override_pattern;
{
    Object color_or_region, color_qm, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;

    x_note_fn_call(90,123);
    color_or_region = Nil;
    color_qm = Nil;
    ab_loop_list_ = override_pattern;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color_or_region = CAR(ab_loop_desetq_);
    color_qm = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(color_or_region,color_qm)) {
	ab_loopvar__2 = 
		slot_value_cons_1(slot_value_cons_1(color_or_region,
		color_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

void entities_INIT()
{
    Object temp, temp_1, temp_2;
    Object AB_package, list_constant_227, list_constant_226, list_constant_224;
    Object list_constant_225, Qset_icon_color, Qget_icon_color;
    Object Qinitial_icon_color, list_constant_211;
    Object Qvirtual_attributes_local_to_class, Qset_stripe_color;
    Object Qget_stripe_color, Qinitial_stripe_color, list_constant_219;
    Object list_constant_223, list_constant_220, list_constant_222, Qab_or;
    Object Qconnection, Qab_class, Qset_border_color, Qget_border_color;
    Object Qinitial_border_color, list_constant_218, Qset_text_color;
    Object Qget_text_color, Qinitial_text_color, Qset_foreground_color;
    Object Qget_foreground_color, Qinitial_foreground_color, list_constant_221;
    Object Qset_background_color, Qget_background_color;
    Object Qinitial_background_color, list_constant_193, Qdeprecated;
    Object list_constant_217, Qtext_box, Qget_icon_width, Qinitial_icon_width;
    Object list_constant_208, list_constant_205, Qicon_width, Qitem;
    Object list_constant_216, list_constant_209, Qget_item_width;
    Object Qinitial_item_width, Qitem_width, Qget_icon_height;
    Object Qinitial_icon_height, Qicon_height, list_constant_215;
    Object Qget_item_height, Qinitial_item_height, Qitem_height;
    Object Qset_icon_reflection, Qget_icon_reflection;
    Object Qinitial_icon_reflection, list_constant_214, Qicon_reflection;
    Object list_constant_213, Qno_item, list_constant_212, list_constant_44;
    Object Qset_icon_heading, Qget_icon_heading, Qinitial_icon_heading;
    Object Qicon_heading, Qget_icon_y_position, Qinitial_icon_y_position;
    Object Qicon_y_position, list_constant_210, Qget_item_y_position;
    Object Qinitial_item_y_position, Qitem_y_position, Qget_icon_x_position;
    Object Qinitial_icon_x_position, Qicon_x_position, list_constant_207;
    Object list_constant_206, Qget_item_x_position, Qinitial_item_x_position;
    Object Qitem_x_position, list_constant_204, list_constant_203;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object list_constant_202, Qcreate_icon_description, Kfuncall_at_load_time;
    Object list_constant_201, list_constant_200, list_constant_199;
    Object list_constant_198, list_constant_196, Qlines, list_constant_197;
    Object list_constant_36, Qoutline, list_constant_195, list_constant_194;
    Object list_constant_34, string_constant_45, string_constant_44;
    Object list_constant_192, list_constant_191, list_constant_190;
    Object list_constant_189, list_constant_188, list_constant_187;
    Object Qcreate_icon_description_if_valid, Qclasses_which_define, Qdraw;
    Object Qdraw_for_entity, Qreclaim_rubber_stamp_widgets, list_constant_186;
    Object list_constant_185, list_constant_184;
    Object Qmake_iconic_entity_with_specific_icon_description, Kfuncall;
    Object list_constant_183, list_constant_182, Qfilled_polygon;
    Object list_constant_181, list_constant_180, list_constant_179;
    Object list_constant_21, list_constant_59, list_constant_178;
    Object list_constant_177, list_constant_176, list_constant_175;
    Object list_constant_174, list_constant_173, list_constant_172;
    Object list_constant_171, list_constant_170, Qborder, list_constant_169;
    Object Qdark_color, list_constant_168, Qlight_color, list_constant_167;
    Object Qface_color, list_constant_166, list_constant_165;
    Object list_constant_117, list_constant_164, list_constant_163;
    Object list_constant_162, list_constant_159, list_constant_161;
    Object list_constant_118, list_constant_160, list_constant_112;
    Object list_constant_158, list_constant_16, Qsolid_rectangle;
    Object list_constant_109, list_constant_106, list_constant_108;
    Object list_constant_107, list_constant_157, list_constant_141;
    Object list_constant_156, list_constant_155, Qarrow_color;
    Object list_constant_131, list_constant_130, list_constant_129;
    Object list_constant_128, list_constant_127, list_constant_154;
    Object list_constant_153, list_constant_152, list_constant_151;
    Object list_constant_15, list_constant_150, list_constant_149;
    Object list_constant_148, list_constant_147, list_constant_146;
    Object list_constant_145, list_constant_144, list_constant_143;
    Object list_constant_20, list_constant_142, list_constant_140;
    Object list_constant_139, list_constant_138, list_constant_137;
    Object list_constant_136, list_constant_135, list_constant_134;
    Object list_constant_133, list_constant_132, list_constant_126;
    Object list_constant_125, list_constant_124, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_119, list_constant_116, list_constant_114;
    Object list_constant_115, list_constant_113, list_constant_111;
    Object list_constant_110, Qlight_gray, Qdark_gray, list_constant_105;
    Object list_constant_53, list_constant_104, list_constant_103;
    Object Qmake_title_bar_widget_icon_description, list_constant_102;
    Object list_constant_101, list_constant_82, Qsmoke, list_constant_81;
    Object list_constant_80, list_constant_79, list_constant_78;
    Object list_constant_77, list_constant_100, list_constant_99;
    Object list_constant_98, list_constant_94, list_constant_97;
    Object list_constant_96, list_constant_95, list_constant_85;
    Object list_constant_86, list_constant_93, list_constant_92;
    Object list_constant_91, list_constant_87, list_constant_90;
    Object list_constant_89, list_constant_88, list_constant_84;
    Object list_constant_83, list_constant_76, list_constant_75;
    Object list_constant_74, list_constant_70, list_constant_73;
    Object list_constant_72, list_constant_71, list_constant_62;
    Object list_constant_60, list_constant_61, list_constant_69;
    Object list_constant_68, list_constant_67, list_constant_63;
    Object list_constant_66, list_constant_65, list_constant_64;
    Object list_constant_58, list_constant_57, list_constant_54;
    Object list_constant_56, list_constant_55, list_constant_46;
    Object list_constant_18, list_constant_17, list_constant_45;
    Object list_constant_19, list_constant_52, list_constant_51;
    Object list_constant_47, list_constant_50, list_constant_49;
    Object list_constant_40, list_constant_48, list_constant_43;
    Object list_constant_42, list_constant_41, list_constant_37;
    Object list_constant_39, list_constant_38, list_constant_35;
    Object Qbackground_layer, Qvariables, list_constant_33, list_constant_32;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_22, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_14, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_entity, list_constant_13;
    Object Qinitialize_after_reading_for_workspace, Qslot_value_reclaimer;
    Object Qreclaim_parent_of_subworkspace_qm_value;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qreclaim_subworkspaces_value;
    Object Qgenerate_spot, Qgenerate_spot_for_entity, Qabsent_slot_putter;
    Object Qput_debugging_specification_where_slot_is_absent;
    Object Qdebugging_specification;
    Object Qreclaim_runtime_structures_affected_by_this_entity_value;
    Object Qruntime_structures_affected_by_this_entity;
    Object Qreclaim_icon_description_value, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, list_constant_12, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, string_constant_8;

    x_note_fn_call(90,124);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_12 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qentity,list_constant_12);
    string_constant_8 = 
	    STATIC_STRING("1m1l8t1m83-Cy7338y3-5y3-Vy3-hy3-gy3fy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3Sy3-Wy3-Xy3-Yy3-by3-gy3-Xy3-Wy3Sy3-hy3-gy3Sy3-");
    string_constant_9 = 
	    STATIC_STRING("1y3-Ay3-Gy3-5y3-Gy3-Ly3ey3Sy3-Uy3-ny3-my3Sy3-by3-ly3Sy3-wyut3-ly3-iy3-Xy3-Vy3-by3-Ty3-ey3-by3-sy3-Xy3-Wy3Sy3-hy3-gy3Sy3-by3-gy3-");
    string_constant_10 = 
	    STATIC_STRING("Wy3-by3-oy3-by3-Wy3-ny3-Ty3-ey3Sy3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3Sy3-Ty3-gy3-Wy3Sy3-ly3-ay3-hy3-py3-ly3Sy3-ny3-iy3Sy3-Wy3-by3-ky3-X");
    string_constant_11 = 
	    STATIC_STRING("y3-Vy3-my3-ey3-ry3Sy3-hy3-gy3Sy3-my3-ay3-hy3-ly3-Xy3Sy3-wyut3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3Sy3-py3-by3-my3-ay3-hy3-ny3-my3Sy3-Ty3-");
    string_constant_12 = 
	    STATIC_STRING("iy3-iy3-Xy3-Ty3-ky3-by3-gy3-Zy3Sy3-by3-gy3Sy3-my3-ay3-Xy3-by3-ky3Sy3-Wy3-Xy3-Yy3fy3-Vy3-ey3-Ty3-ly3-ly3gy3Sy3-Gy3-ay3-by3-ly3Sy3");
    string_constant_13 = 
	    STATIC_STRING("-by3-ly3Sy3-Ty3Sy3-ay3-Ty3-Vy3-dy3Sy3-my3-hy3Sy3-wyut3-by3-gy3-by3-my3-by3-Ty3-ey3-by3-sy3-Xy3Sy3-Xy3-Ty3-Vy3-ay3Sy3-Vy3-ey3-Ty3");
    string_constant_14 = 
	    STATIC_STRING("-ly3-ly3Sy3-py3-by3-my3-ay3Sy3-by3-my3Zy3-ly3Sy3-hy3-py3-gy3Sy3-by3-Vy3-hy3-gy3Sy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3gy");
    string_constant_15 = 
	    STATIC_STRING("3Sy3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-wyut3ay3Sy3-ky3-Xy3-Zy3-by3-hy3-gy3-ly3fy3-Ty3-gy3-Wy3fy3-Wy3-ky3-Ty3-py3-by3-gy3-Zy3");
    string_constant_16 = 
	    STATIC_STRING("fy3-Vy3-hy3-fy3-fy3-Ty3-gy3-Wy3-ly3Sy3cy3Sy3by3Sy3-uy3Sy3-by3-Vy3-hy3-gy3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3");
    string_constant_17 = 
	    STATIC_STRING("-ny3-Xy3gyut3-by3-Vy3-hy3-gy3fy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3fy3-iy3-ey3-by3-ly3-my3ey3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy");
    string_constant_18 = 
	    STATIC_STRING("3-Wy3Sy3-Ty3-ly3Sy3-by3-Vy3-hy3-gy3fy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3Sy3-py3-by3-ey3-ey3Sy3-ly3-ay3-hy3-py3Sy3-ny3-iy3S");
    string_constant_19 = 
	    STATIC_STRING("y3-hy3-gy3Sy3-Ty3-gy3-ry3Sy3-wyut3-Vy3-ey3-Ty3-ly3-ly3Sy3-my3-ay3-Ty3-my3Sy3-ay3-Ty3-ly3Sy3-by3-Vy3-hy3-gy3fy3-Wy3-Xy3-ly3-Vy3-k");
    string_constant_20 = 
	    STATIC_STRING("y3-by3-iy3-my3-by3-hy3-gy3ey3Sy3-Uy3-ny3-my3Sy3-by3-my3Sy3-by3-ly3Sy3-by3-gy3-ay3-Xy3-ky3-by3-my3-Xy3-Wy3Sy3-gy3-hy3-ky3-fy3-Ty3");
    string_constant_21 = 
	    STATIC_STRING("-ey3-ey3-ry3Sy3-Yy3-ky3-hy3-fy3Sy3-wyut3-1y3-Ay3-Gy3-5y3-Gy3-Ly3gy");
    string_constant_22 = 
	    STATIC_STRING("1t4z8r8u8u83-+y83-+y00001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83Rfy83Rfy83-+y83-+y00001o1l8l1l8");
    string_constant_23 = 
	    STATIC_STRING("o1l83Cy1m83Dy53QyExport as Icon-attributes part000004z8r83Amy83Amy83-+y83-+y00001s1l83Ey1l8l1l830Yy1l83Hy1l8z1l83Fy1l83-4y1l83Ny");
    string_constant_24 = 
	    STATIC_STRING("000004z8r83FGy83FGy83-+y83-+y00001s1l83Ey1l8l1l830Yy1l83Hy1l8z1l83Fy1l83-4y1l83Ny000004z8r83b6y83b6y83-+y83-+y00001n1l8l1l8o1l83");
    string_constant_25 = 
	    STATIC_STRING("Cy000004z8r83Zcy83Zcy83-+y83-+y00001m1l8l1l8o000004z8r83L2y83L2y83-+y83-+y00001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83L1y83L1y83-+y83");
    string_constant_26 = 
	    STATIC_STRING("-+y00001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83L0y83L0y83-+y83-+y00001o1l83Ey1l8l1l83Ny1l83Hy00000");
    string_constant_27 = 
	    STATIC_STRING("1v8q1o83-+y1l9k8t1m83-Cy7338y3-5y3-Vy3-hy3-gy3fy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3Sy3-Wy3-Xy3-Yy3-by3-gy3-Xy3-Wy3Sy3-");
    string_constant_28 = 
	    STATIC_STRING("hy3-gy3Sy3-1y3-Ay3-Gy3-5y3-Gy3-Ly3ey3Sy3-Uy3-ny3-my3Sy3-by3-ly3Sy3-wyut3-ly3-iy3-Xy3-Vy3-by3-Ty3-ey3-by3-sy3-Xy3-Wy3Sy3-hy3-gy3S");
    string_constant_29 = 
	    STATIC_STRING("y3-by3-gy3-Wy3-by3-oy3-by3-Wy3-ny3-Ty3-ey3Sy3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3Sy3-Ty3-gy3-Wy3Sy3-ly3-ay3-hy3-py3-ly3Sy3-ny3-iy3Sy3-Wy");
    string_constant_30 = 
	    STATIC_STRING("3-by3-ky3-Xy3-Vy3-my3-ey3-ry3Sy3-hy3-gy3Sy3-my3-ay3-hy3-ly3-Xy3Sy3-wyut3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3Sy3-py3-by3-my3-ay3-hy3-ny3-");
    string_constant_31 = 
	    STATIC_STRING("my3Sy3-Ty3-iy3-iy3-Xy3-Ty3-ky3-by3-gy3-Zy3Sy3-by3-gy3Sy3-my3-ay3-Xy3-by3-ky3Sy3-Wy3-Xy3-Yy3fy3-Vy3-ey3-Ty3-ly3-ly3gy3Sy3-Gy3-ay3");
    string_constant_32 = 
	    STATIC_STRING("-by3-ly3Sy3-by3-ly3Sy3-Ty3Sy3-ay3-Ty3-Vy3-dy3Sy3-my3-hy3Sy3-wyut3-by3-gy3-by3-my3-by3-Ty3-ey3-by3-sy3-Xy3Sy3-Xy3-Ty3-Vy3-ay3Sy3-");
    string_constant_33 = 
	    STATIC_STRING("Vy3-ey3-Ty3-ly3-ly3Sy3-py3-by3-my3-ay3Sy3-by3-my3Zy3-ly3Sy3-hy3-py3-gy3Sy3-by3-Vy3-hy3-gy3Sy3-Wy3-Xy3-ly3-Vy3-ky3-by3-iy3-my3-by");
    string_constant_34 = 
	    STATIC_STRING("3-hy3-gy3gy3Sy3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-wyut3ay3Sy3-ky3-Xy3-Zy3-by3-hy3-gy3-ly3fy3-Ty3-gy3-Wy3fy3-Wy3-ky3-Ty3-py3-");
    string_constant_35 = 
	    STATIC_STRING("by3-gy3-Zy3fy3-Vy3-hy3-fy3-fy3-Ty3-gy3-Wy3-ly3Sy3cy3Sy3by3Sy3-uy3Sy3-by3-Vy3-hy3-gy3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3");
    string_constant_36 = 
	    STATIC_STRING("Sy3-my3-ky3-ny3-Xy3gyut3-by3-Vy3-hy3-gy3fy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3fy3-iy3-ey3-by3-ly3-my3ey3Sy3-Xy3-qy3-iy3-hy3");
    string_constant_37 = 
	    STATIC_STRING("-ky3-my3-Xy3-Wy3Sy3-Ty3-ly3Sy3-by3-Vy3-hy3-gy3fy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3Sy3-py3-by3-ey3-ey3Sy3-ly3-ay3-hy3-py3S");
    string_constant_38 = 
	    STATIC_STRING("y3-ny3-iy3Sy3-hy3-gy3Sy3-Ty3-gy3-ry3Sy3-wyut3-Vy3-ey3-Ty3-ly3-ly3Sy3-my3-ay3-Ty3-my3Sy3-ay3-Ty3-ly3Sy3-by3-Vy3-hy3-gy3fy3-Wy3-Xy");
    string_constant_39 = 
	    STATIC_STRING("3-ly3-Vy3-ky3-by3-iy3-my3-by3-hy3-gy3ey3Sy3-Uy3-ny3-my3Sy3-by3-my3Sy3-by3-ly3Sy3-by3-gy3-ay3-Xy3-ky3-by3-my3-Xy3-Wy3Sy3-gy3-hy3-");
    string_constant_40 = 
	    STATIC_STRING("ky3-fy3-Ty3-ey3-ey3-ry3Sy3-Yy3-ky3-hy3-fy3Sy3-wyut3-1y3-Ay3-Gy3-5y3-Gy3-Ly3gy1q8u08l8o8z1m83Dy53YySee comment on ENTITY class de");
    string_constant_41 = 
	    STATIC_STRING("finition1q83Rfy08l8o83Cy1m83Dy53QyExport as Icon-attributes part1u83Amy083Ey8l830Yy83Hy8z83Fy83-4y83Ny1u83FGy083Ey8l830Yy83Hy8z8");
    string_constant_42 = 
	    STATIC_STRING("3Fy83-4y83Ny1p83b6y08l8o83Cy1o83Zcy08l8o1q83L2y01l83Ey1l8l1l83Ny1l83Hy1q83L1y01l83Ey1l8l1l83Ny1l83Hy1q83L0y01l83Ey1l8l1l83Ny1l83");
    string_constant_43 = STATIC_STRING("Hy");
    temp = regenerate_optimized_constant(list(14,string_constant_8,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12,string_constant_13,string_constant_14,
	    string_constant_15,string_constant_16,string_constant_17,
	    string_constant_18,string_constant_19,string_constant_20,
	    string_constant_21));
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25,
	    string_constant_26));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qentity,list_constant_12,Nil,temp,Nil,
	    temp_1,list_constant_12,regenerate_optimized_constant(list(17,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33,string_constant_34,string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38,
	    string_constant_39,string_constant_40,string_constant_41,
	    string_constant_42,string_constant_43)),Nil);
    Entity_class_description = 
	    lookup_global_or_kb_specific_property_value(Qentity,
	    Class_description_gkbprop);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qg2gl_activity = STATIC_SYMBOL("G2GL-ACTIVITY",AB_package);
    Qg2gl_object_icon_substitutions = 
	    STATIC_SYMBOL("G2GL-OBJECT-ICON-SUBSTITUTIONS",AB_package);
    Qg2gl_object = STATIC_SYMBOL("G2GL-OBJECT",AB_package);
    Qreclaim_icon_description_value = 
	    STATIC_SYMBOL("RECLAIM-ICON-DESCRIPTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icon_description_value,
	    STATIC_FUNCTION(reclaim_icon_description_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qicon_description,
	    SYMBOL_FUNCTION(Qreclaim_icon_description_value),
	    Qslot_value_reclaimer);
    Qruntime_structures_affected_by_this_entity = 
	    STATIC_SYMBOL("RUNTIME-STRUCTURES-AFFECTED-BY-THIS-ENTITY",
	    AB_package);
    Qreclaim_runtime_structures_affected_by_this_entity_value = 
	    STATIC_SYMBOL("RECLAIM-RUNTIME-STRUCTURES-AFFECTED-BY-THIS-ENTITY-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_runtime_structures_affected_by_this_entity_value,
	    STATIC_FUNCTION(reclaim_runtime_structures_affected_by_this_entity_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qruntime_structures_affected_by_this_entity,
	    SYMBOL_FUNCTION(Qreclaim_runtime_structures_affected_by_this_entity_value),
	    Qslot_value_reclaimer);
    Qdebugging_specification = STATIC_SYMBOL("DEBUGGING-SPECIFICATION",
	    AB_package);
    Qput_debugging_specification_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-DEBUGGING-SPECIFICATION-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_debugging_specification_where_slot_is_absent,
	    STATIC_FUNCTION(put_debugging_specification_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qdebugging_specification,
	    SYMBOL_FUNCTION(Qput_debugging_specification_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qgenerate_spot_for_entity = STATIC_SYMBOL("GENERATE-SPOT-FOR-ENTITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_entity,
	    STATIC_FUNCTION(generate_spot_for_entity,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_entity);
    set_get(Qentity,Qgenerate_spot,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qentity,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qparent_of_subworkspace_qm = STATIC_SYMBOL("PARENT-OF-SUBWORKSPACE\?",
	    AB_package);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    Qsubworkspaces = STATIC_SYMBOL("SUBWORKSPACES",AB_package);
    Qworkspace_does_not_belong_to_any_module = 
	    STATIC_SYMBOL("WORKSPACE-DOES-NOT-BELONG-TO-ANY-MODULE",
	    AB_package);
    if (Subworkspace_currently_being_deleted_qm == UNBOUND)
	Subworkspace_currently_being_deleted_qm = Nil;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qreclaim_subworkspaces_value = 
	    STATIC_SYMBOL("RECLAIM-SUBWORKSPACES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_subworkspaces_value,
	    STATIC_FUNCTION(reclaim_subworkspaces_value,NIL,FALSE,2,2));
    mutate_global_property(Qsubworkspaces,
	    SYMBOL_FUNCTION(Qreclaim_subworkspaces_value),
	    Qslot_value_reclaimer);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreclaim_parent_of_subworkspace_qm_value = 
	    STATIC_SYMBOL("RECLAIM-PARENT-OF-SUBWORKSPACE\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_parent_of_subworkspace_qm_value,
	    STATIC_FUNCTION(reclaim_parent_of_subworkspace_qm_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qparent_of_subworkspace_qm,
	    SYMBOL_FUNCTION(Qreclaim_parent_of_subworkspace_qm_value),
	    Qslot_value_reclaimer);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qinitialize_after_reading_for_workspace = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_workspace,
	    STATIC_FUNCTION(initialize_after_reading_for_workspace,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_workspace);
    set_get(Qworkspace,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qworkspace,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qicon_attributes_plist = STATIC_SYMBOL("ICON-ATTRIBUTES-PLIST",AB_package);
    Qicon_color_pattern = STATIC_SYMBOL("ICON-COLOR-PATTERN",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    list_constant_13 = STATIC_CONS(Qforeground,Qforeground);
    list_constant = STATIC_CONS(list_constant_13,Qnil);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qinitialize_after_reading_for_entity = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_entity,
	    STATIC_FUNCTION(initialize_after_reading_for_entity,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_entity);
    set_get(Qentity,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qentity,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qattribute_displays = STATIC_SYMBOL("ATTRIBUTE-DISPLAYS",AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Kno_stubs = STATIC_SYMBOL("NO-STUBS",Pkeyword);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Ktransient = STATIC_SYMBOL("TRANSIENT",Pkeyword);
    Qclockwise_90 = STATIC_SYMBOL("CLOCKWISE-90",AB_package);
    Qclockwise_180 = STATIC_SYMBOL("CLOCKWISE-180",AB_package);
    Qclockwise_270 = STATIC_SYMBOL("CLOCKWISE-270",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qnil,Qclockwise_90,
	    Qclockwise_180,Qclockwise_270);
    list_constant_2 = STATIC_CONS(Qnil,Qnil);
    Qiconic_entity = STATIC_SYMBOL("ICONIC-ENTITY",AB_package);
    Qresize_box_rubber_stamp_widget = 
	    STATIC_SYMBOL("RESIZE-BOX-RUBBER-STAMP-WIDGET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresize_box_rubber_stamp_widget,
	    Resize_box_rubber_stamp_widget);
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_iconic_entity_with_specific_icon_description = 
	    STATIC_SYMBOL("MAKE-ICONIC-ENTITY-WITH-SPECIFIC-ICON-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_iconic_entity_with_specific_icon_description,
	    STATIC_FUNCTION(make_iconic_entity_with_specific_icon_description,
	    NIL,FALSE,4,4));
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    list_constant_14 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_16 = STATIC_CONS(FIX((SI_Long)2L),list_constant_14);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)14L),Qnil);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)2L),list_constant_15);
    list_constant_18 = STATIC_CONS(FIX((SI_Long)14L),list_constant_15);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)14L),list_constant_14);
    list_constant_26 = STATIC_LIST((SI_Long)6L,Qlines,list_constant_16,
	    list_constant_17,list_constant_18,list_constant_19,
	    list_constant_16);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)4L),Qnil);
    list_constant_22 = STATIC_CONS(FIX((SI_Long)4L),list_constant_20);
    list_constant_21 = STATIC_CONS(FIX((SI_Long)10L),Qnil);
    list_constant_23 = STATIC_CONS(FIX((SI_Long)4L),list_constant_21);
    list_constant_24 = STATIC_CONS(FIX((SI_Long)11L),list_constant_21);
    list_constant_25 = STATIC_CONS(FIX((SI_Long)11L),list_constant_20);
    list_constant_27 = STATIC_LIST((SI_Long)6L,Qlines,list_constant_22,
	    list_constant_23,list_constant_24,list_constant_25,
	    list_constant_22);
    list_constant_28 = STATIC_LIST((SI_Long)2L,list_constant_26,
	    list_constant_27);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_28,FIX((SI_Long)16L),FIX((SI_Long)16L),
	    list_constant_2);
    Qreclaim_rubber_stamp_widgets = 
	    STATIC_SYMBOL("RECLAIM-RUBBER-STAMP-WIDGETS",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_rubber_stamp_widgets,
	    STATIC_FUNCTION(reclaim_rubber_stamp_widgets,NIL,FALSE,1,1));
    record_system_variable(Qresize_box_rubber_stamp_widget,Qdraw,
	    list_constant_29,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qpending = STATIC_SYMBOL("PENDING",AB_package);
    Qna = STATIC_SYMBOL("NA",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qnormal,Qpending,Qna);
    Qclose_box_rubber_stamp_widget = 
	    STATIC_SYMBOL("CLOSE-BOX-RUBBER-STAMP-WIDGET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclose_box_rubber_stamp_widget,
	    Close_box_rubber_stamp_widget);
    Qmake_title_bar_widget_icon_description = 
	    STATIC_SYMBOL("MAKE-TITLE-BAR-WIDGET-ICON-DESCRIPTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_title_bar_widget_icon_description,
	    STATIC_FUNCTION(make_title_bar_widget_icon_description,NIL,
	    FALSE,5,5));
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    list_constant_30 = STATIC_CONS(Qblack,Qblack);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    list_constant_31 = STATIC_CONS(Qdark_gray,Qdark_gray);
    Qsmoke = STATIC_SYMBOL("SMOKE",AB_package);
    list_constant_32 = STATIC_CONS(Qsmoke,Qsmoke);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    list_constant_33 = STATIC_CONS(Qlight_gray,Qlight_gray);
    list_constant_77 = STATIC_LIST((SI_Long)5L,Qpolychrome,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_33);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    list_constant_78 = STATIC_CONS(Qvariables,Qnil);
    Qbackground_layer = STATIC_SYMBOL("BACKGROUND-LAYER",AB_package);
    list_constant_79 = STATIC_CONS(Qbackground_layer,Qnil);
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    list_constant_34 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_37 = STATIC_CONS(FIX((SI_Long)15L),list_constant_34);
    list_constant_35 = STATIC_CONS(FIX((SI_Long)15L),Qnil);
    list_constant_38 = STATIC_CONS(FIX((SI_Long)15L),list_constant_35);
    list_constant_39 = STATIC_CONS(FIX((SI_Long)0L),list_constant_35);
    list_constant_36 = STATIC_CONS(FIX((SI_Long)0L),list_constant_34);
    list_constant_40 = STATIC_CONS(list_constant_36,Qnil);
    list_constant_41 = STATIC_LIST_STAR((SI_Long)4L,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40);
    list_constant_42 = STATIC_LIST((SI_Long)3L,list_constant_37,
	    list_constant_38,list_constant_39);
    list_constant_43 = STATIC_LIST((SI_Long)3L,list_constant_39,
	    list_constant_36,list_constant_37);
    list_constant_80 = STATIC_LIST((SI_Long)4L,Qfilled_polygon,
	    list_constant_41,list_constant_42,list_constant_43);
    list_constant_46 = STATIC_CONS(FIX((SI_Long)16L),list_constant_34);
    list_constant_44 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_45 = STATIC_CONS(FIX((SI_Long)0L),list_constant_44);
    list_constant_47 = STATIC_LIST((SI_Long)3L,list_constant_16,
	    list_constant_17,list_constant_45);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)4L,list_constant_36,
	    list_constant_46,list_constant_19,list_constant_47);
    list_constant_50 = STATIC_LIST((SI_Long)3L,list_constant_36,
	    list_constant_46,list_constant_19);
    list_constant_48 = STATIC_LIST((SI_Long)2L,list_constant_19,
	    list_constant_16);
    list_constant_51 = STATIC_CONS(list_constant_36,list_constant_48);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)3L,list_constant_16,
	    list_constant_45,list_constant_40);
    list_constant_81 = STATIC_LIST((SI_Long)6L,Qfilled_polygon,
	    list_constant_49,list_constant_50,list_constant_47,
	    list_constant_51,list_constant_52);
    list_constant_53 = STATIC_CONS(FIX((SI_Long)16L),list_constant_44);
    list_constant_54 = STATIC_LIST((SI_Long)3L,list_constant_18,
	    list_constant_19,list_constant_46);
    list_constant_55 = STATIC_LIST_STAR((SI_Long)4L,list_constant_53,
	    list_constant_45,list_constant_17,list_constant_54);
    list_constant_56 = STATIC_LIST((SI_Long)3L,list_constant_53,
	    list_constant_45,list_constant_17);
    list_constant_57 = STATIC_LIST((SI_Long)3L,list_constant_53,
	    list_constant_17,list_constant_18);
    list_constant_58 = STATIC_LIST((SI_Long)3L,list_constant_18,
	    list_constant_46,list_constant_53);
    list_constant_82 = STATIC_LIST((SI_Long)6L,Qfilled_polygon,
	    list_constant_55,list_constant_56,list_constant_54,
	    list_constant_57,list_constant_58);
    list_constant_59 = STATIC_CONS(FIX((SI_Long)5L),Qnil);
    list_constant_63 = STATIC_CONS(FIX((SI_Long)13L),list_constant_59);
    list_constant_60 = STATIC_CONS(FIX((SI_Long)13L),Qnil);
    list_constant_64 = STATIC_CONS(FIX((SI_Long)5L),list_constant_60);
    list_constant_61 = STATIC_CONS(FIX((SI_Long)11L),Qnil);
    list_constant_65 = STATIC_CONS(FIX((SI_Long)3L),list_constant_61);
    list_constant_62 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_66 = STATIC_CONS(FIX((SI_Long)11L),list_constant_62);
    list_constant_67 = STATIC_LIST((SI_Long)4L,list_constant_63,
	    list_constant_64,list_constant_65,list_constant_66);
    list_constant_68 = STATIC_LIST((SI_Long)3L,list_constant_63,
	    list_constant_64,list_constant_65);
    list_constant_69 = STATIC_LIST((SI_Long)3L,list_constant_65,
	    list_constant_66,list_constant_63);
    list_constant_83 = STATIC_LIST((SI_Long)4L,Qfilled_polygon,
	    list_constant_67,list_constant_68,list_constant_69);
    list_constant_70 = STATIC_CONS(FIX((SI_Long)13L),list_constant_61);
    list_constant_71 = STATIC_CONS(FIX((SI_Long)11L),list_constant_60);
    list_constant_72 = STATIC_CONS(FIX((SI_Long)3L),list_constant_59);
    list_constant_73 = STATIC_CONS(FIX((SI_Long)5L),list_constant_62);
    list_constant_74 = STATIC_LIST((SI_Long)4L,list_constant_70,
	    list_constant_71,list_constant_72,list_constant_73);
    list_constant_75 = STATIC_LIST((SI_Long)3L,list_constant_70,
	    list_constant_71,list_constant_72);
    list_constant_76 = STATIC_LIST((SI_Long)3L,list_constant_72,
	    list_constant_73,list_constant_70);
    list_constant_84 = STATIC_LIST((SI_Long)4L,Qfilled_polygon,
	    list_constant_74,list_constant_75,list_constant_76);
    list_constant_103 = STATIC_LIST((SI_Long)12L,list_constant_77,
	    list_constant_78,list_constant_79,Qlight_gray,list_constant_80,
	    Qsmoke,list_constant_81,Qdark_gray,list_constant_82,Qblack,
	    list_constant_83,list_constant_84);
    list_constant_85 = STATIC_CONS(FIX((SI_Long)6L),Qnil);
    list_constant_87 = STATIC_CONS(FIX((SI_Long)14L),list_constant_85);
    list_constant_88 = STATIC_CONS(FIX((SI_Long)6L),list_constant_15);
    list_constant_86 = STATIC_CONS(FIX((SI_Long)12L),Qnil);
    list_constant_89 = STATIC_CONS(FIX((SI_Long)4L),list_constant_86);
    list_constant_90 = STATIC_CONS(FIX((SI_Long)12L),list_constant_20);
    list_constant_91 = STATIC_LIST((SI_Long)4L,list_constant_87,
	    list_constant_88,list_constant_89,list_constant_90);
    list_constant_92 = STATIC_LIST((SI_Long)3L,list_constant_87,
	    list_constant_88,list_constant_89);
    list_constant_93 = STATIC_LIST((SI_Long)3L,list_constant_89,
	    list_constant_90,list_constant_87);
    list_constant_101 = STATIC_LIST((SI_Long)4L,Qfilled_polygon,
	    list_constant_91,list_constant_92,list_constant_93);
    list_constant_94 = STATIC_CONS(FIX((SI_Long)14L),list_constant_86);
    list_constant_95 = STATIC_CONS(FIX((SI_Long)12L),list_constant_15);
    list_constant_96 = STATIC_CONS(FIX((SI_Long)4L),list_constant_85);
    list_constant_97 = STATIC_CONS(FIX((SI_Long)6L),list_constant_20);
    list_constant_98 = STATIC_LIST((SI_Long)4L,list_constant_94,
	    list_constant_95,list_constant_96,list_constant_97);
    list_constant_99 = STATIC_LIST((SI_Long)3L,list_constant_94,
	    list_constant_95,list_constant_96);
    list_constant_100 = STATIC_LIST((SI_Long)3L,list_constant_96,
	    list_constant_97,list_constant_94);
    list_constant_102 = STATIC_LIST((SI_Long)4L,Qfilled_polygon,
	    list_constant_98,list_constant_99,list_constant_100);
    list_constant_104 = STATIC_LIST((SI_Long)12L,list_constant_77,
	    list_constant_78,list_constant_79,Qlight_gray,list_constant_80,
	    Qdark_gray,list_constant_81,Qsmoke,list_constant_82,Qblack,
	    list_constant_101,list_constant_102);
    list_constant_105 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_title_bar_widget_icon_description,list_constant_103,
	    list_constant_104,Qnil,list_constant_53);
    record_system_variable(Qclose_box_rubber_stamp_widget,Qdraw,
	    list_constant_105,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qleft_scroll_arrow_rubber_stamp_widget = 
	    STATIC_SYMBOL("LEFT-SCROLL-ARROW-RUBBER-STAMP-WIDGET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleft_scroll_arrow_rubber_stamp_widget,
	    Left_scroll_arrow_rubber_stamp_widget);
    Qdark_color = STATIC_SYMBOL("DARK-COLOR",AB_package);
    list_constant_106 = STATIC_CONS(Qdark_color,Qdark_gray);
    Qface_color = STATIC_SYMBOL("FACE-COLOR",AB_package);
    list_constant_107 = STATIC_CONS(Qface_color,Qlight_gray);
    Qlight_color = STATIC_SYMBOL("LIGHT-COLOR",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    list_constant_108 = STATIC_CONS(Qlight_color,Qwhite);
    Qborder = STATIC_SYMBOL("BORDER",AB_package);
    list_constant_109 = STATIC_CONS(Qborder,Qblack);
    Qarrow_color = STATIC_SYMBOL("ARROW-COLOR",AB_package);
    list_constant_110 = STATIC_CONS(Qarrow_color,Qblack);
    list_constant_127 = STATIC_LIST((SI_Long)6L,Qpolychrome,
	    list_constant_106,list_constant_107,list_constant_108,
	    list_constant_109,list_constant_110);
    list_constant_111 = STATIC_CONS(FIX((SI_Long)19L),Qnil);
    list_constant_114 = STATIC_CONS(FIX((SI_Long)1L),list_constant_111);
    list_constant_115 = STATIC_CONS(FIX((SI_Long)19L),list_constant_111);
    list_constant_112 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_113 = STATIC_CONS(FIX((SI_Long)19L),list_constant_112);
    list_constant_116 = STATIC_CONS(list_constant_113,Qnil);
    list_constant_128 = STATIC_LIST_STAR((SI_Long)4L,Qlines,
	    list_constant_114,list_constant_115,list_constant_116);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    list_constant_117 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)18L),
	    FIX((SI_Long)18L));
    list_constant_129 = STATIC_LIST((SI_Long)3L,Qsolid_rectangle,
	    list_constant_16,list_constant_117);
    list_constant_118 = STATIC_CONS(FIX((SI_Long)1L),list_constant_112);
    list_constant_130 = STATIC_LIST_STAR((SI_Long)4L,Qlines,
	    list_constant_114,list_constant_118,list_constant_116);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    list_constant_119 = STATIC_CONS(FIX((SI_Long)20L),Qnil);
    list_constant_120 = STATIC_CONS(FIX((SI_Long)0L),list_constant_119);
    list_constant_121 = STATIC_CONS(FIX((SI_Long)20L),list_constant_119);
    list_constant_122 = STATIC_CONS(FIX((SI_Long)20L),list_constant_34);
    list_constant_131 = STATIC_LIST((SI_Long)5L,Qoutline,list_constant_36,
	    list_constant_120,list_constant_121,list_constant_122);
    list_constant_123 = STATIC_CONS(FIX((SI_Long)7L),list_constant_21);
    list_constant_124 = STATIC_CONS(FIX((SI_Long)13L),list_constant_20);
    list_constant_125 = STATIC_CONS(FIX((SI_Long)13L),list_constant_44);
    list_constant_126 = STATIC_LIST((SI_Long)3L,list_constant_123,
	    list_constant_124,list_constant_125);
    list_constant_132 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_126,list_constant_126);
    list_constant_133 = STATIC_LIST((SI_Long)11L,list_constant_127,
	    Qdark_color,list_constant_128,Qface_color,list_constant_129,
	    Qlight_color,list_constant_130,Qborder,list_constant_131,
	    Qarrow_color,list_constant_132);
    list_constant_134 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_133,FIX((SI_Long)21L),FIX((SI_Long)21L),
	    list_constant_2);
    record_system_variable(Qleft_scroll_arrow_rubber_stamp_widget,Qdraw,
	    list_constant_134,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qtop_scroll_arrow_rubber_stamp_widget = 
	    STATIC_SYMBOL("TOP-SCROLL-ARROW-RUBBER-STAMP-WIDGET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtop_scroll_arrow_rubber_stamp_widget,
	    Top_scroll_arrow_rubber_stamp_widget);
    list_constant_135 = STATIC_CONS(FIX((SI_Long)5L),list_constant_15);
    list_constant_136 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)11L),
	    FIX((SI_Long)8L));
    list_constant_137 = STATIC_CONS(FIX((SI_Long)17L),list_constant_15);
    list_constant_138 = STATIC_LIST((SI_Long)3L,list_constant_135,
	    list_constant_136,list_constant_137);
    list_constant_139 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_138,list_constant_138);
    list_constant_140 = STATIC_LIST((SI_Long)11L,list_constant_127,
	    Qdark_color,list_constant_128,Qface_color,list_constant_129,
	    Qlight_color,list_constant_130,Qborder,list_constant_131,
	    Qarrow_color,list_constant_139);
    list_constant_141 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)21L),
	    FIX((SI_Long)21L),list_constant_2);
    list_constant_142 = STATIC_LIST_STAR((SI_Long)4L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_140,list_constant_141);
    record_system_variable(Qtop_scroll_arrow_rubber_stamp_widget,Qdraw,
	    list_constant_142,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qright_scroll_arrow_rubber_stamp_widget = 
	    STATIC_SYMBOL("RIGHT-SCROLL-ARROW-RUBBER-STAMP-WIDGET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qright_scroll_arrow_rubber_stamp_widget,
	    Right_scroll_arrow_rubber_stamp_widget);
    list_constant_143 = STATIC_CONS(FIX((SI_Long)8L),list_constant_44);
    list_constant_144 = STATIC_CONS(FIX((SI_Long)8L),list_constant_20);
    list_constant_145 = STATIC_CONS(FIX((SI_Long)14L),list_constant_21);
    list_constant_146 = STATIC_LIST((SI_Long)3L,list_constant_143,
	    list_constant_144,list_constant_145);
    list_constant_147 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_146,list_constant_146);
    list_constant_148 = STATIC_LIST((SI_Long)11L,list_constant_127,
	    Qdark_color,list_constant_128,Qface_color,list_constant_129,
	    Qlight_color,list_constant_130,Qborder,list_constant_131,
	    Qarrow_color,list_constant_147);
    list_constant_149 = STATIC_LIST_STAR((SI_Long)4L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_148,list_constant_141);
    record_system_variable(Qright_scroll_arrow_rubber_stamp_widget,Qdraw,
	    list_constant_149,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qbottom_scroll_arrow_rubber_stamp_widget = 
	    STATIC_SYMBOL("BOTTOM-SCROLL-ARROW-RUBBER-STAMP-WIDGET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbottom_scroll_arrow_rubber_stamp_widget,
	    Bottom_scroll_arrow_rubber_stamp_widget);
    list_constant_150 = STATIC_CONS(FIX((SI_Long)8L),Qnil);
    list_constant_151 = STATIC_CONS(FIX((SI_Long)5L),list_constant_150);
    list_constant_152 = STATIC_CONS(FIX((SI_Long)17L),list_constant_150);
    list_constant_153 = STATIC_CONS(FIX((SI_Long)11L),list_constant_15);
    list_constant_154 = STATIC_LIST((SI_Long)3L,list_constant_151,
	    list_constant_152,list_constant_153);
    list_constant_155 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_154,list_constant_154);
    list_constant_156 = STATIC_LIST((SI_Long)11L,list_constant_127,
	    Qdark_color,list_constant_128,Qface_color,list_constant_129,
	    Qlight_color,list_constant_130,Qborder,list_constant_131,
	    Qarrow_color,list_constant_155);
    list_constant_157 = STATIC_LIST_STAR((SI_Long)4L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_156,list_constant_141);
    record_system_variable(Qbottom_scroll_arrow_rubber_stamp_widget,Qdraw,
	    list_constant_157,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qscroll_bar_elevator_rubber_stamp_widget = 
	    STATIC_SYMBOL("SCROLL-BAR-ELEVATOR-RUBBER-STAMP-WIDGET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscroll_bar_elevator_rubber_stamp_widget,
	    Scroll_bar_elevator_rubber_stamp_widget);
    list_constant_166 = STATIC_LIST((SI_Long)5L,Qpolychrome,
	    list_constant_107,list_constant_108,list_constant_106,
	    list_constant_109);
    list_constant_158 = STATIC_CONS(FIX((SI_Long)17L),Qnil);
    list_constant_159 = STATIC_CONS(FIX((SI_Long)17L),list_constant_158);
    list_constant_167 = STATIC_LIST((SI_Long)3L,Qsolid_rectangle,
	    list_constant_16,list_constant_159);
    list_constant_161 = STATIC_CONS(FIX((SI_Long)1L),list_constant_158);
    list_constant_160 = STATIC_CONS(FIX((SI_Long)17L),list_constant_112);
    list_constant_162 = STATIC_CONS(list_constant_160,Qnil);
    list_constant_168 = STATIC_LIST_STAR((SI_Long)4L,Qlines,
	    list_constant_161,list_constant_118,list_constant_162);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)4L,Qlines,
	    list_constant_161,list_constant_159,list_constant_162);
    list_constant_163 = STATIC_CONS(FIX((SI_Long)18L),Qnil);
    list_constant_164 = STATIC_CONS(FIX((SI_Long)0L),list_constant_163);
    list_constant_165 = STATIC_CONS(FIX((SI_Long)18L),list_constant_34);
    list_constant_170 = STATIC_LIST((SI_Long)5L,Qoutline,list_constant_36,
	    list_constant_164,list_constant_117,list_constant_165);
    list_constant_171 = STATIC_LIST((SI_Long)9L,list_constant_166,
	    Qface_color,list_constant_167,Qlight_color,list_constant_168,
	    Qdark_color,list_constant_169,Qborder,list_constant_170);
    list_constant_172 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_171,FIX((SI_Long)18L),FIX((SI_Long)18L),
	    list_constant_2);
    record_system_variable(Qscroll_bar_elevator_rubber_stamp_widget,Qdraw,
	    list_constant_172,Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qright_marker_for_cascading_menu_rubber_stamp_widget = 
	    STATIC_SYMBOL("RIGHT-MARKER-FOR-CASCADING-MENU-RUBBER-STAMP-WIDGET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qright_marker_for_cascading_menu_rubber_stamp_widget,
	    Right_marker_for_cascading_menu_rubber_stamp_widget);
    list_constant_173 = STATIC_CONS(FIX((SI_Long)10L),list_constant_59);
    list_constant_174 = STATIC_CONS(FIX((SI_Long)0L),list_constant_21);
    list_constant_175 = STATIC_LIST((SI_Long)3L,list_constant_36,
	    list_constant_173,list_constant_174);
    list_constant_176 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_175,list_constant_175);
    list_constant_177 = STATIC_CONS(list_constant_176,Qnil);
    list_constant_178 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_177,FIX((SI_Long)10L),FIX((SI_Long)10L),
	    list_constant_2);
    record_system_variable(Qright_marker_for_cascading_menu_rubber_stamp_widget,
	    Qdraw,list_constant_178,Qnil,Qnil,
	    Qreclaim_rubber_stamp_widgets,Qt);
    Qleft_marker_for_cascading_menu_rubber_stamp_widget = 
	    STATIC_SYMBOL("LEFT-MARKER-FOR-CASCADING-MENU-RUBBER-STAMP-WIDGET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleft_marker_for_cascading_menu_rubber_stamp_widget,
	    Left_marker_for_cascading_menu_rubber_stamp_widget);
    list_constant_179 = STATIC_CONS(FIX((SI_Long)10L),list_constant_34);
    list_constant_180 = STATIC_CONS(FIX((SI_Long)0L),list_constant_59);
    list_constant_181 = STATIC_CONS(FIX((SI_Long)10L),list_constant_21);
    list_constant_182 = STATIC_LIST((SI_Long)3L,list_constant_179,
	    list_constant_180,list_constant_181);
    list_constant_183 = STATIC_LIST((SI_Long)3L,Qfilled_polygon,
	    list_constant_182,list_constant_182);
    list_constant_184 = STATIC_CONS(list_constant_183,Qnil);
    list_constant_185 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)10L),
	    FIX((SI_Long)10L),list_constant_2);
    list_constant_186 = STATIC_LIST_STAR((SI_Long)4L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_184,list_constant_185);
    record_system_variable(Qleft_marker_for_cascading_menu_rubber_stamp_widget,
	    Qdraw,list_constant_186,Qnil,Qnil,
	    Qreclaim_rubber_stamp_widgets,Qt);
    Qright_marker_for_cascading_menu = 
	    STATIC_SYMBOL("RIGHT-MARKER-FOR-CASCADING-MENU",AB_package);
    Qleft_marker_for_cascading_menu = 
	    STATIC_SYMBOL("LEFT-MARKER-FOR-CASCADING-MENU",AB_package);
    Qgensym_left_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-LEFT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qgensym_up_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-UP-SCROLL-ARROW-FRAME-COMPONENT",AB_package);
    Qgensym_right_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-RIGHT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qgensym_down_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-DOWN-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qgensym_resize_box_frame_component = 
	    STATIC_SYMBOL("GENSYM-RESIZE-BOX-FRAME-COMPONENT",AB_package);
    Qgensym_close_box_frame_component = 
	    STATIC_SYMBOL("GENSYM-CLOSE-BOX-FRAME-COMPONENT",AB_package);
    Qgensym_scroll_bar_elevator_frame_component = 
	    STATIC_SYMBOL("GENSYM-SCROLL-BAR-ELEVATOR-FRAME-COMPONENT",
	    AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qrevise_icon_rendering_of_rubber_stamp = 
	    STATIC_SYMBOL("REVISE-ICON-RENDERING-OF-RUBBER-STAMP",AB_package);
    SET_SYMBOL_FUNCTION(Qrevise_icon_rendering_of_rubber_stamp,
	    STATIC_FUNCTION(revise_icon_rendering_of_rubber_stamp,NIL,
	    FALSE,7,7));
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Qadd_icon_rendering = STATIC_SYMBOL("ADD-ICON-RENDERING",AB_package);
    Qcurrent_image_plane = STATIC_SYMBOL("CURRENT-IMAGE-PLANE",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    Qlight_grey = STATIC_SYMBOL("LIGHT-GREY",AB_package);
    Qdim_grey = STATIC_SYMBOL("DIM-GREY",AB_package);
    Qpaint_icon_background_image = 
	    STATIC_SYMBOL("PAINT-ICON-BACKGROUND-IMAGE",AB_package);
    Qeditor_scaling = STATIC_SYMBOL("EDITOR-SCALING",AB_package);
    Kbleeding_on_all_sides = STATIC_SYMBOL("BLEEDING-ON-ALL-SIDES",Pkeyword);
    list_constant_4 = STATIC_CONS(Qicon_color,Qnil);
    Qdraw_for_entity = STATIC_SYMBOL("DRAW-FOR-ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_entity,STATIC_FUNCTION(draw_for_entity,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_entity);
    set_get(Qentity,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qentity,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnil,Qnormal);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("Invalid icon description element:~%  ~a");
    string_constant_1 = 
	    STATIC_STRING("This icon description is not valid for this height and width.");
    Qcreate_icon_description_if_valid = 
	    STATIC_SYMBOL("CREATE-ICON-DESCRIPTION-IF-VALID",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_icon_description_if_valid,
	    STATIC_FUNCTION(create_icon_description_if_valid,NIL,FALSE,5,5));
    Kwidth = STATIC_SYMBOL("WIDTH",Pkeyword);
    list_constant_188 = STATIC_CONS(Kwidth,list_constant_34);
    Kheight = STATIC_SYMBOL("HEIGHT",Pkeyword);
    list_constant_187 = STATIC_CONS(Kheight,Qnil);
    list_constant_189 = STATIC_CONS(Kwidth,list_constant_187);
    list_constant_190 = STATIC_CONS(FIX((SI_Long)0L),list_constant_187);
    list_constant_191 = STATIC_LIST((SI_Long)5L,Qoutline,list_constant_36,
	    list_constant_188,list_constant_189,list_constant_190);
    list_constant_192 = STATIC_CONS(list_constant_191,Qnil);
    if (Default_entity_line_drawing_description_template == UNBOUND)
	Default_entity_line_drawing_description_template = list_constant_192;
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    list_constant_193 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qiconic_entity,list_constant_193);
    string_constant_44 = STATIC_STRING("0");
    string_constant_45 = STATIC_STRING("1m8q1m83-*wy1l83-+y");
    temp = regenerate_optimized_constant(string_constant_44);
    temp_1 = regenerate_optimized_constant(string_constant_44);
    add_class_to_environment(9,Qiconic_entity,list_constant_193,Nil,temp,
	    Nil,temp_1,list_constant_193,
	    regenerate_optimized_constant(string_constant_45),Nil);
    Kfuncall_at_load_time = STATIC_SYMBOL("FUNCALL-AT-LOAD-TIME",Pkeyword);
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_icon_description,
	    STATIC_FUNCTION(create_icon_description,NIL,TRUE,3,9));
    list_constant_196 = STATIC_CONS(FIX((SI_Long)50L),list_constant_34);
    list_constant_194 = STATIC_CONS(FIX((SI_Long)50L),Qnil);
    list_constant_197 = STATIC_CONS(FIX((SI_Long)50L),list_constant_194);
    list_constant_195 = STATIC_CONS(FIX((SI_Long)0L),list_constant_194);
    list_constant_198 = STATIC_CONS(list_constant_195,Qnil);
    list_constant_199 = STATIC_LIST_STAR((SI_Long)5L,Qoutline,
	    list_constant_36,list_constant_196,list_constant_197,
	    list_constant_198);
    list_constant_200 = STATIC_LIST((SI_Long)3L,Qlines,list_constant_36,
	    list_constant_197);
    list_constant_201 = STATIC_LIST_STAR((SI_Long)3L,Qlines,
	    list_constant_196,list_constant_198);
    list_constant_202 = STATIC_LIST((SI_Long)3L,list_constant_199,
	    list_constant_200,list_constant_201);
    list_constant_6 = STATIC_LIST((SI_Long)5L,Kfuncall_at_load_time,
	    Qcreate_icon_description,FIX((SI_Long)50L),FIX((SI_Long)50L),
	    list_constant_202);
    fix_up_icon_description_for_entity_if_necessary();
    string_constant_46 = 
	    STATIC_STRING("1q1m83g*y1m9k9l1m83g*y1m9k83-Dry1m83g*y1m9k83Avy1m83g*y1m9k83wWy1m83g*y1m9k83HHy1m83g*y1m9k83biy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qicon_color);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_46));
    Qicon_heading = STATIC_SYMBOL("ICON-HEADING",AB_package);
    Qitem_x_position = STATIC_SYMBOL("ITEM-X-POSITION",AB_package);
    Qitem_y_position = STATIC_SYMBOL("ITEM-Y-POSITION",AB_package);
    Qitem_width = STATIC_SYMBOL("ITEM-WIDTH",AB_package);
    Qitem_height = STATIC_SYMBOL("ITEM-HEIGHT",AB_package);
    string_constant_47 = 
	    STATIC_STRING("1u1m83--Wy1m9k83-Yiy1m83--Wy1m9k83-Yjy1m83--Wy1m9k9l1m83--Wy1m9k83-Yhy1m83--Wy1m9k83-Yey1m83--Wy1m9k9m1m83--Wy1m9k9n1m83--Wy1m9k");
    string_constant_48 = STATIC_STRING("9o1m83--Wy1m9k9p1m83--Wy1m9k83bcy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qicon_heading);
    push_optimized_constant(Qitem_x_position);
    push_optimized_constant(Qitem_y_position);
    push_optimized_constant(Qitem_width);
    push_optimized_constant(Qitem_height);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_47,
	    string_constant_48)));
    Qreflected_clockwise_180 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-180",
	    AB_package);
    Qreflected_clockwise_270 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-270",
	    AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)5L,Qnil,Qnormal,Qclockwise_270,
	    Qreflected_clockwise_180,Qreflected_clockwise_270);
    SET_SYMBOL_FUNCTION(Qitem_x_position,STATIC_FUNCTION(item_x_position,
	    NIL,FALSE,1,1));
    Qreflected = STATIC_SYMBOL("REFLECTED",AB_package);
    list_constant_203 = STATIC_CONS(Qreflected_clockwise_270,Qnil);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)5L,Qnil,Qnormal,
	    Qclockwise_90,Qreflected,list_constant_203);
    SET_SYMBOL_FUNCTION(Qitem_y_position,STATIC_FUNCTION(item_y_position,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qitem_width,STATIC_FUNCTION(item_width,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qitem_height,STATIC_FUNCTION(item_height,NIL,FALSE,
	    1,1));
    Qreflected_clockwise_90 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-90",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qicon_heading,STATIC_FUNCTION(icon_heading,NIL,
	    FALSE,1,1));
    list_constant_204 = STATIC_LIST((SI_Long)3L,Qclockwise_90,
	    Qclockwise_180,Qclockwise_270);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qnil,Qnormal,
	    list_constant_204);
    temp_2 = CONS(Qitem_x_position,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qitem_x_position,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_205 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qinitial_item_x_position = STATIC_SYMBOL("INITIAL-ITEM-X-POSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_x_position,
	    STATIC_FUNCTION(initial_item_x_position,NIL,FALSE,1,1));
    Qget_item_x_position = STATIC_SYMBOL("GET-ITEM-X-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_x_position,
	    STATIC_FUNCTION(get_item_x_position,NIL,FALSE,1,1));
    add_virtual_attribute(Qitem_x_position,list_constant_205,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_item_x_position),
	    SYMBOL_FUNCTION(Qget_item_x_position),Nil);
    Qicon_x_position = STATIC_SYMBOL("ICON-X-POSITION",AB_package);
    temp_2 = CONS(Qicon_x_position,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qdeprecated = STATIC_SYMBOL("DEPRECATED",AB_package);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qicon_x_position,Qdeprecated);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(list_constant_206,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    list_constant_207 = STATIC_CONS(Qitem,Qnil);
    list_constant_208 = STATIC_LIST((SI_Long)2L,Qdeprecated,list_constant_207);
    Qinitial_icon_x_position = STATIC_SYMBOL("INITIAL-ICON-X-POSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_x_position,
	    STATIC_FUNCTION(initial_icon_x_position,NIL,FALSE,1,1));
    Qget_icon_x_position = STATIC_SYMBOL("GET-ICON-X-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_x_position,
	    STATIC_FUNCTION(get_icon_x_position,NIL,FALSE,1,1));
    add_virtual_attribute(Qicon_x_position,list_constant_205,Qinteger,
	    list_constant_208,SYMBOL_FUNCTION(Qinitial_icon_x_position),
	    SYMBOL_FUNCTION(Qget_icon_x_position),Nil);
    temp_2 = CONS(Qitem_y_position,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qitem_y_position,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_item_y_position = STATIC_SYMBOL("INITIAL-ITEM-Y-POSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_y_position,
	    STATIC_FUNCTION(initial_item_y_position,NIL,FALSE,1,1));
    Qget_item_y_position = STATIC_SYMBOL("GET-ITEM-Y-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_y_position,
	    STATIC_FUNCTION(get_item_y_position,NIL,FALSE,1,1));
    add_virtual_attribute(Qitem_y_position,list_constant_205,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_item_y_position),
	    SYMBOL_FUNCTION(Qget_item_y_position),Nil);
    Qicon_y_position = STATIC_SYMBOL("ICON-Y-POSITION",AB_package);
    temp_2 = CONS(Qicon_y_position,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    list_constant_209 = STATIC_CONS(Qdeprecated,Qnil);
    list_constant_210 = STATIC_CONS(Qicon_y_position,list_constant_209);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(list_constant_210,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_icon_y_position = STATIC_SYMBOL("INITIAL-ICON-Y-POSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_y_position,
	    STATIC_FUNCTION(initial_icon_y_position,NIL,FALSE,1,1));
    Qget_icon_y_position = STATIC_SYMBOL("GET-ICON-Y-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_y_position,
	    STATIC_FUNCTION(get_icon_y_position,NIL,FALSE,1,1));
    add_virtual_attribute(Qicon_y_position,list_constant_205,Qinteger,
	    list_constant_208,SYMBOL_FUNCTION(Qinitial_icon_y_position),
	    SYMBOL_FUNCTION(Qget_icon_y_position),Nil);
    temp_2 = CONS(Qicon_heading,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qicon_heading,temp);
    set_property_value_function(get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,temp_2);
    list_constant_211 = STATIC_CONS(Qab_class,list_constant_193);
    Qinitial_icon_heading = STATIC_SYMBOL("INITIAL-ICON-HEADING",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_heading,
	    STATIC_FUNCTION(initial_icon_heading,NIL,FALSE,1,1));
    Qget_icon_heading = STATIC_SYMBOL("GET-ICON-HEADING",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_heading,STATIC_FUNCTION(get_icon_heading,
	    NIL,FALSE,1,1));
    Qset_icon_heading = STATIC_SYMBOL("SET-ICON-HEADING",AB_package);
    SET_SYMBOL_FUNCTION(Qset_icon_heading,STATIC_FUNCTION(set_icon_heading,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qicon_heading,list_constant_211,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_icon_heading),
	    SYMBOL_FUNCTION(Qget_icon_heading),
	    SYMBOL_FUNCTION(Qset_icon_heading));
    Qicon_reflection = STATIC_SYMBOL("ICON-REFLECTION",AB_package);
    temp_2 = CONS(Qicon_reflection,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qicon_reflection,temp);
    set_property_value_function(get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qleft_right = STATIC_SYMBOL("LEFT-RIGHT",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    list_constant_212 = STATIC_CONS(Qunsigned_byte,list_constant_44);
    array_constant = STATIC_ARRAY(list_constant_212,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_213 = STATIC_CONS(Qno_item,Qnil);
    list_constant_214 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_213);
    Qinitial_icon_reflection = STATIC_SYMBOL("INITIAL-ICON-REFLECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_reflection,
	    STATIC_FUNCTION(initial_icon_reflection,NIL,FALSE,1,1));
    Qget_icon_reflection = STATIC_SYMBOL("GET-ICON-REFLECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_reflection,
	    STATIC_FUNCTION(get_icon_reflection,NIL,FALSE,1,1));
    Qset_icon_reflection = STATIC_SYMBOL("SET-ICON-REFLECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qset_icon_reflection,
	    STATIC_FUNCTION(set_icon_reflection,NIL,FALSE,2,2));
    add_virtual_attribute(Qicon_reflection,list_constant_211,
	    list_constant_214,Qnil,
	    SYMBOL_FUNCTION(Qinitial_icon_reflection),
	    SYMBOL_FUNCTION(Qget_icon_reflection),
	    SYMBOL_FUNCTION(Qset_icon_reflection));
    temp_2 = CONS(Qitem_height,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qitem_height,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_item_height = STATIC_SYMBOL("INITIAL-ITEM-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_height,
	    STATIC_FUNCTION(initial_item_height,NIL,FALSE,1,1));
    Qget_item_height = STATIC_SYMBOL("GET-ITEM-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_height,STATIC_FUNCTION(get_item_height,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qitem_height,list_constant_205,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_item_height),
	    SYMBOL_FUNCTION(Qget_item_height),Nil);
    Qicon_height = STATIC_SYMBOL("ICON-HEIGHT",AB_package);
    temp_2 = CONS(Qicon_height,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    list_constant_215 = STATIC_CONS(Qicon_height,list_constant_209);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(list_constant_215,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_icon_height = STATIC_SYMBOL("INITIAL-ICON-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_height,
	    STATIC_FUNCTION(initial_icon_height,NIL,FALSE,1,1));
    Qget_icon_height = STATIC_SYMBOL("GET-ICON-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_height,STATIC_FUNCTION(get_icon_height,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qicon_height,list_constant_205,Qinteger,
	    list_constant_208,SYMBOL_FUNCTION(Qinitial_icon_height),
	    SYMBOL_FUNCTION(Qget_icon_height),Nil);
    temp_2 = CONS(Qitem_width,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qitem_width,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_item_width = STATIC_SYMBOL("INITIAL-ITEM-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_width,
	    STATIC_FUNCTION(initial_item_width,NIL,FALSE,1,1));
    Qget_item_width = STATIC_SYMBOL("GET-ITEM-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_width,STATIC_FUNCTION(get_item_width,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qitem_width,list_constant_205,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_item_width),
	    SYMBOL_FUNCTION(Qget_item_width),Nil);
    Qicon_width = STATIC_SYMBOL("ICON-WIDTH",AB_package);
    temp_2 = CONS(Qicon_width,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    list_constant_216 = STATIC_CONS(Qicon_width,list_constant_209);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(list_constant_216,temp);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_icon_width = STATIC_SYMBOL("INITIAL-ICON-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_width,
	    STATIC_FUNCTION(initial_icon_width,NIL,FALSE,1,1));
    Qget_icon_width = STATIC_SYMBOL("GET-ICON-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_width,STATIC_FUNCTION(get_icon_width,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qicon_width,list_constant_205,Qinteger,
	    list_constant_208,SYMBOL_FUNCTION(Qinitial_icon_width),
	    SYMBOL_FUNCTION(Qget_icon_width),Nil);
    SET_SYMBOL_FUNCTION(Qicon_color,STATIC_FUNCTION(icon_color,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qicon_color_pattern,
	    STATIC_FUNCTION(icon_color_pattern,NIL,FALSE,1,1));
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qtext_cell_background_color_qm = 
	    STATIC_SYMBOL("TEXT-CELL-BACKGROUND-COLOR\?",AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qtext_cell_line_color_qm = STATIC_SYMBOL("TEXT-CELL-LINE-COLOR\?",
	    AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qtext_box_border_color_qm = STATIC_SYMBOL("TEXT-BOX-BORDER-COLOR\?",
	    AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    temp_2 = CONS(Qbackground_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp_2 = CONS(Qbackground_color,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_2;
    Kno_change = STATIC_SYMBOL("NO-CHANGE",Pkeyword);
    string_constant_2 = 
	    STATIC_STRING("The attribute BACKGROUND-COLOR does not exist in ~NF.");
    string_constant_3 = 
	    STATIC_STRING("The argument given, ~a, was not a valid color.");
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_217 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_box);
    list_constant_218 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_217,
	    list_constant_211);
    list_constant_219 = STATIC_LIST((SI_Long)2L,Qdeprecated,list_constant_193);
    Qinitial_background_color = STATIC_SYMBOL("INITIAL-BACKGROUND-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_background_color,
	    STATIC_FUNCTION(initial_background_color,NIL,FALSE,1,1));
    Qget_background_color = STATIC_SYMBOL("GET-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_background_color,
	    STATIC_FUNCTION(get_background_color,NIL,FALSE,1,1));
    Qset_background_color = STATIC_SYMBOL("SET-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_background_color,
	    STATIC_FUNCTION(set_background_color,NIL,FALSE,2,2));
    add_virtual_attribute(Qbackground_color,list_constant_218,Qsymbol,
	    list_constant_219,SYMBOL_FUNCTION(Qinitial_background_color),
	    SYMBOL_FUNCTION(Qget_background_color),
	    SYMBOL_FUNCTION(Qset_background_color));
    temp_2 = CONS(Qforeground_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp_2 = CONS(Qforeground_color,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_2;
    string_constant_4 = 
	    STATIC_STRING("The attribute FOREGROUND-COLOR does not exist in ~NF.");
    list_constant_220 = STATIC_CONS(list_constant_211,Qnil);
    list_constant_221 = STATIC_CONS(Qab_or,list_constant_220);
    Qinitial_foreground_color = STATIC_SYMBOL("INITIAL-FOREGROUND-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_foreground_color,
	    STATIC_FUNCTION(initial_foreground_color,NIL,FALSE,1,1));
    Qget_foreground_color = STATIC_SYMBOL("GET-FOREGROUND-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_foreground_color,
	    STATIC_FUNCTION(get_foreground_color,NIL,FALSE,1,1));
    Qset_foreground_color = STATIC_SYMBOL("SET-FOREGROUND-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_foreground_color,
	    STATIC_FUNCTION(set_foreground_color,NIL,FALSE,2,2));
    add_virtual_attribute(Qforeground_color,list_constant_221,Qsymbol,
	    list_constant_219,SYMBOL_FUNCTION(Qinitial_foreground_color),
	    SYMBOL_FUNCTION(Qget_foreground_color),
	    SYMBOL_FUNCTION(Qset_foreground_color));
    temp_2 = CONS(Qtext_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp_2 = CONS(Qtext_color,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_2;
    string_constant_5 = 
	    STATIC_STRING("The attribute TEXT-COLOR does not exist in ~NF.");
    Qinitial_text_color = STATIC_SYMBOL("INITIAL-TEXT-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_text_color,
	    STATIC_FUNCTION(initial_text_color,NIL,FALSE,1,1));
    Qget_text_color = STATIC_SYMBOL("GET-TEXT-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_text_color,STATIC_FUNCTION(get_text_color,NIL,
	    FALSE,1,1));
    Qset_text_color = STATIC_SYMBOL("SET-TEXT-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_text_color,STATIC_FUNCTION(set_text_color,NIL,
	    FALSE,2,2));
    add_virtual_attribute(Qtext_color,list_constant_218,Qsymbol,
	    list_constant_219,SYMBOL_FUNCTION(Qinitial_text_color),
	    SYMBOL_FUNCTION(Qget_text_color),SYMBOL_FUNCTION(Qset_text_color));
    temp_2 = CONS(Qborder_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp_2 = CONS(Qborder_color,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_2;
    string_constant_6 = 
	    STATIC_STRING("The attribute BORDER-COLOR does not exist is ~NF.");
    Qinitial_border_color = STATIC_SYMBOL("INITIAL-BORDER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_border_color,
	    STATIC_FUNCTION(initial_border_color,NIL,FALSE,1,1));
    Qget_border_color = STATIC_SYMBOL("GET-BORDER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_border_color,STATIC_FUNCTION(get_border_color,
	    NIL,FALSE,1,1));
    Qset_border_color = STATIC_SYMBOL("SET-BORDER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_border_color,STATIC_FUNCTION(set_border_color,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qborder_color,list_constant_218,Qsymbol,
	    list_constant_219,SYMBOL_FUNCTION(Qinitial_border_color),
	    SYMBOL_FUNCTION(Qget_border_color),
	    SYMBOL_FUNCTION(Qset_border_color));
    temp_2 = CONS(Qstripe_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp_2 = CONS(Qstripe_color,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp_2;
    string_constant_7 = 
	    STATIC_STRING("The attribute STRIPE-COLOR does not exist in ~s.");
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_222 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    list_constant_223 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_222,list_constant_220);
    Qinitial_stripe_color = STATIC_SYMBOL("INITIAL-STRIPE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_stripe_color,
	    STATIC_FUNCTION(initial_stripe_color,NIL,FALSE,1,1));
    Qget_stripe_color = STATIC_SYMBOL("GET-STRIPE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_stripe_color,STATIC_FUNCTION(get_stripe_color,
	    NIL,FALSE,1,1));
    Qset_stripe_color = STATIC_SYMBOL("SET-STRIPE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_stripe_color,STATIC_FUNCTION(set_stripe_color,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qstripe_color,list_constant_223,Qsymbol,
	    list_constant_219,SYMBOL_FUNCTION(Qinitial_stripe_color),
	    SYMBOL_FUNCTION(Qget_stripe_color),
	    SYMBOL_FUNCTION(Qset_stripe_color));
    temp_2 = CONS(Qicon_color,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qicon_color,temp);
    set_property_value_function(get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_icon_color = STATIC_SYMBOL("INITIAL-ICON-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_icon_color,
	    STATIC_FUNCTION(initial_icon_color,NIL,FALSE,1,1));
    Qget_icon_color = STATIC_SYMBOL("GET-ICON-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_icon_color,STATIC_FUNCTION(get_icon_color,NIL,
	    FALSE,1,1));
    Qset_icon_color = STATIC_SYMBOL("SET-ICON-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_icon_color,STATIC_FUNCTION(set_icon_color,NIL,
	    FALSE,2,2));
    add_virtual_attribute(Qicon_color,list_constant_211,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_icon_color),
	    SYMBOL_FUNCTION(Qget_icon_color),SYMBOL_FUNCTION(Qset_icon_color));
    Qitem_position = STATIC_SYMBOL("ITEM-POSITION",AB_package);
    Qmissing_color_region = STATIC_SYMBOL("MISSING-COLOR-REGION",AB_package);
    Qunnamed_color_region = STATIC_SYMBOL("UNNAMED-COLOR-REGION",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qrevise_icon_rendering = STATIC_SYMBOL("REVISE-ICON-RENDERING",AB_package);
    SET_SYMBOL_FUNCTION(Qrevise_icon_rendering,
	    STATIC_FUNCTION(revise_icon_rendering,NIL,FALSE,4,4));
    Qillegal_colors = STATIC_SYMBOL("ILLEGAL-COLORS",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qcurrent = STATIC_SYMBOL("CURRENT",AB_package);
    Qpermanent = STATIC_SYMBOL("PERMANENT",AB_package);
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qconnection_color_pattern = STATIC_SYMBOL("CONNECTION-COLOR-PATTERN",
	    AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qworkspace_foreground_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR\?",AB_package);
    Kbg = STATIC_SYMBOL("BG",Pkeyword);
    Kfg = STATIC_SYMBOL("FG",Pkeyword);
    list_constant_224 = STATIC_CONS(Qbackground_color,Kbg);
    list_constant_225 = STATIC_CONS(Qforeground_color,Kfg);
    list_constant_10 = STATIC_LIST((SI_Long)2L,list_constant_224,
	    list_constant_225);
    Qworkspace_color_pattern = STATIC_SYMBOL("WORKSPACE-COLOR-PATTERN",
	    AB_package);
    Kborder = STATIC_SYMBOL("BORDER",Pkeyword);
    Ktext = STATIC_SYMBOL("TEXT",Pkeyword);
    list_constant_226 = STATIC_CONS(Qborder_color,Kborder);
    list_constant_227 = STATIC_CONS(Qtext_color,Ktext);
    list_constant_11 = STATIC_LIST((SI_Long)3L,list_constant_224,
	    list_constant_226,list_constant_227);
    Qtext_box_color_pattern = STATIC_SYMBOL("TEXT-BOX-COLOR-PATTERN",
	    AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
}
