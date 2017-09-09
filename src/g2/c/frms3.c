/* frms3.c
 * Input file:  frames3.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms3.h"


/* NOTE-CHANGE-TO-BLOCK-OR-STRUCT-OR-SEQ */
Object note_change_to_block_or_struct_or_seq(block,slot_name)
    Object block, slot_name;
{
    x_note_fn_call(86,0);
    if (Noting_changes_to_kb_p && ATOM(block))
	return note_change_to_block_1(block,slot_name);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_icon_slot_group = UNBOUND;

Object Chain_of_available_icon_slot_groups = UNBOUND;

Object Icon_slot_group_count = UNBOUND;

/* ICON-SLOT-GROUP-STRUCTURE-MEMORY-USAGE */
Object icon_slot_group_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(86,1);
    temp = Icon_slot_group_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICON-SLOT-GROUP-COUNT */
Object outstanding_icon_slot_group_count()
{
    Object def_structure_icon_slot_group_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(86,2);
    gensymed_symbol = IFIX(Icon_slot_group_count);
    def_structure_icon_slot_group_variable = 
	    Chain_of_available_icon_slot_groups;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icon_slot_group_variable))
	goto end_loop;
    def_structure_icon_slot_group_variable = 
	    ISVREF(def_structure_icon_slot_group_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICON-SLOT-GROUP-1 */
Object reclaim_icon_slot_group_1(icon_slot_group)
    Object icon_slot_group;
{
    Object svref_new_value;

    x_note_fn_call(86,3);
    inline_note_reclaim_cons(icon_slot_group,Nil);
    svref_new_value = Chain_of_available_icon_slot_groups;
    SVREF(icon_slot_group,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_icon_slot_groups = icon_slot_group;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICON-SLOT-GROUP */
Object reclaim_structure_for_icon_slot_group(icon_slot_group)
    Object icon_slot_group;
{
    x_note_fn_call(86,4);
    return reclaim_icon_slot_group_1(icon_slot_group);
}

/* MAKE-PERMANENT-ICON-SLOT-GROUP-STRUCTURE-INTERNAL */
Object make_permanent_icon_slot_group_structure_internal()
{
    Object def_structure_icon_slot_group_variable, the_array;
    Object defstruct_g2_icon_slot_group_variable, svref_new_value;
    SI_Long icon_slot_group_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(86,5);
    def_structure_icon_slot_group_variable = Nil;
    icon_slot_group_count_new_value = IFIX(Icon_slot_group_count) + 
	    (SI_Long)100L;
    Icon_slot_group_count = FIX(icon_slot_group_count_new_value);
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)7L;
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
	defstruct_g2_icon_slot_group_variable = the_array;
	def_structure_icon_slot_group_variable = 
		defstruct_g2_icon_slot_group_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	svref_new_value = Chain_of_available_icon_slot_groups;
	SVREF(def_structure_icon_slot_group_variable,FIX((SI_Long)0L)) = 
		svref_new_value;
	Chain_of_available_icon_slot_groups = 
		def_structure_icon_slot_group_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icon_slot_group_variable);
}

/* MAKE-ICON-SLOT-GROUP-1 */
Object make_icon_slot_group_1()
{
    Object def_structure_icon_slot_group_variable;

    x_note_fn_call(86,6);
    def_structure_icon_slot_group_variable = 
	    Chain_of_available_icon_slot_groups;
    if (def_structure_icon_slot_group_variable)
	Chain_of_available_icon_slot_groups = 
		ISVREF(def_structure_icon_slot_group_variable,(SI_Long)0L);
    else
	def_structure_icon_slot_group_variable = 
		make_permanent_icon_slot_group_structure_internal();
    inline_note_allocate_cons(def_structure_icon_slot_group_variable,Nil);
    ISVREF(def_structure_icon_slot_group_variable,(SI_Long)0L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_slot_group_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_slot_group_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_icon_slot_group_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_icon_slot_group_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_icon_slot_group_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_icon_slot_group_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_icon_slot_group_variable);
}

/* LEFT-EDGE-OF-BLOCK-FUNCTION */
Object left_edge_of_block_function(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(86,7);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    return VALUES_1(gensymed_symbol);
}

/* BOTTOM-EDGE-OF-BLOCK-FUNCTION */
Object bottom_edge_of_block_function(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(86,8);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return VALUES_1(gensymed_symbol);
}

/* SUPERBLOCK?-FUNCTION */
Object superblock_qm_function(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(86,9);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)5L) : Nil;
    return VALUES_1(gensymed_symbol);
}

Object Ws_protocol_handle_moves_from_edge_change_p = UNBOUND;

Object Ws_protocol_trace_p = UNBOUND;

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* SET-EDGES-OF-BLOCK */
Object set_edges_of_block(block,new_left,new_top,new_right,new_bottom)
    Object block, new_left, new_top, new_right, new_bottom;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, temp;

    x_note_fn_call(86,10);
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = new_left;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)0L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)0L)) = gensymed_symbol_1;
    }
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = new_top;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)1L)) = gensymed_symbol_1;
    }
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = new_right;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)2L)) = gensymed_symbol_1;
    }
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = new_bottom;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)3L)) = gensymed_symbol_1;
    }
    return VALUES_1(T);
}

/* CHANGE-EDGES-OF-BLOCK */
Object change_edges_of_block(block,new_left_qm,new_top_qm,new_right_qm,
	    new_bottom_qm)
    Object block, new_left_qm, new_top_qm, new_right_qm, new_bottom_qm;
{
    Object changed_qm, delta_x_l, delta_x_r, delta_y_t, delta_y_b;
    Object gensymed_symbol, old_left, old_top, old_right, old_bottom;
    Object gensymed_symbol_1, slot_group_qm, temp, temp_1, temp_2, temp_3;
    Object temp_4;

    x_note_fn_call(86,11);
    changed_qm = Nil;
    delta_x_l = FIX((SI_Long)0L);
    delta_x_r = FIX((SI_Long)0L);
    delta_y_t = FIX((SI_Long)0L);
    delta_y_b = FIX((SI_Long)0L);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    old_left = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    old_top = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    old_right = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    old_bottom = gensymed_symbol;
    if (new_left_qm && FIXNUM_NE(old_left,new_left_qm)) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = new_left_qm;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)0L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)0L)) = gensymed_symbol_1;
	}
	changed_qm = T;
	delta_x_l = FIXNUM_MINUS(new_left_qm,old_left);
    }
    if (new_top_qm && FIXNUM_NE(old_top,new_top_qm)) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = new_top_qm;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)1L)) = gensymed_symbol_1;
	}
	changed_qm = T;
	delta_y_t = FIXNUM_MINUS(new_top_qm,old_top);
    }
    if (new_right_qm && FIXNUM_NE(old_right,new_right_qm)) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = new_right_qm;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)2L)) = gensymed_symbol_1;
	}
	changed_qm = T;
	delta_x_r = FIXNUM_MINUS(new_right_qm,old_right);
    }
    if (new_bottom_qm && FIXNUM_NE(old_bottom,new_bottom_qm)) {
	gensymed_symbol = block;
	gensymed_symbol_1 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	gensymed_symbol_1 = new_bottom_qm;
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	    temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	    SVREF(temp,FIX((SI_Long)3L)) = gensymed_symbol_1;
	}
	changed_qm = T;
	delta_y_b = FIXNUM_MINUS(new_bottom_qm,old_bottom);
    }
    if (changed_qm) {
	temp_1 = new_left_qm;
	if (temp_1);
	else
	    temp_1 = old_left;
	temp_2 = new_top_qm;
	if (temp_2);
	else
	    temp_2 = old_top;
	temp_3 = new_right_qm;
	if (temp_3);
	else
	    temp_3 = old_right;
	temp_4 = new_bottom_qm;
	if (temp_4);
	else
	    temp_4 = old_bottom;
	note_change_to_edges_of_block(block,old_left,old_top,old_right,
		old_bottom,temp_1,temp_2,temp_3,temp_4);
	if (G2_has_v5_mode_windows_p) {
	    if (FIXNUM_EQ(delta_x_r,delta_x_l) && FIXNUM_EQ(delta_y_t,
		    delta_y_b)) {
		if (Ws_protocol_handle_moves_from_edge_change_p) {
		    if (Ws_protocol_trace_p)
			format((SI_Long)5L,T,
				"edge-change implies move (~s ~s) on ~s~%",
				delta_x_l,delta_y_t,block);
		    send_ws_representations_item_moved(block,delta_x_l,
			    delta_y_t);
		}
	    }
	    else {
		if (Ws_protocol_trace_p) {
		    temp_1 = new_left_qm;
		    if (temp_1);
		    else
			temp_1 = old_left;
		    temp_2 = new_top_qm;
		    if (temp_2);
		    else
			temp_2 = old_top;
		    temp_3 = new_right_qm;
		    if (temp_3);
		    else
			temp_3 = old_right;
		    temp_4 = new_bottom_qm;
		    if (temp_4);
		    else
			temp_4 = old_bottom;
		    format((SI_Long)7L,T,
			    "edge change implies resize of ~s to (~s ~s ~s ~s)~%",
			    block,temp_1,temp_2,temp_3,temp_4);
		}
		temp_1 = new_left_qm;
		if (temp_1);
		else
		    temp_1 = old_left;
		temp_2 = new_top_qm;
		if (temp_2);
		else
		    temp_2 = old_top;
		temp_3 = new_right_qm;
		if (temp_3);
		else
		    temp_3 = old_right;
		temp_4 = new_bottom_qm;
		if (temp_4);
		else
		    temp_4 = old_bottom;
		send_ws_representations_item_resized(block,temp_1,temp_2,
			temp_3,temp_4);
	    }
	}
    }
    return VALUES_1(changed_qm);
}

Object Default_icon_slot_group = UNBOUND;

/* INITIALIZE-DEFAULT-ICON-SLOT-GROUP */
Object initialize_default_icon_slot_group()
{
    x_note_fn_call(86,12);
    return make_icon_slot_group_1();
}

Object Forward_chain_flag = UNBOUND;

Object Invocable_via_backward_chaining_flag = UNBOUND;

Object Savable_kb_workspace_flag = UNBOUND;

Object Recent_procedure_flag = UNBOUND;

Object Sketch_definition_flag = UNBOUND;

Object Backward_chains_to_old_rule_flag = UNBOUND;

Object Depth_first_flag = UNBOUND;

Object Invocable_via_forward_chaining_flag = UNBOUND;

Object Passive_flag = UNBOUND;

Object May_cause_data_seeking_flag = UNBOUND;

Object Always_forward_chain_if_possible_flag = UNBOUND;

Object One_shot_flag = UNBOUND;

Object Opaque_block_flag = UNBOUND;

Object Initial_rule_flag = UNBOUND;

Object Overlapping_block_flag = UNBOUND;

Object Manually_disabled_flag = UNBOUND;

Object Multiple_compilations_flag = UNBOUND;

Object Journal_expiration_flag = UNBOUND;

Object Dont_backward_chain_flag = UNBOUND;

Object May_cause_forward_chaining_flag = UNBOUND;

Object Compiled_as_new_rule_flag = UNBOUND;

Object Class_of_frame_is_user_defined_flag = UNBOUND;

Object Cache_data_for_explanation_flag = UNBOUND;

Object Strip_text_flag = UNBOUND;

Object Do_not_strip_text_flag = UNBOUND;

Object Table_may_not_be_wysiwyg_flag = UNBOUND;

Object Runs_while_inactive_flag = UNBOUND;

Object May_refer_to_inactive_items_flag = UNBOUND;

Object Self_referenced_flag = UNBOUND;

Object Block_has_been_written_flag = UNBOUND;

Object Block_permanently_changed_flag = UNBOUND;

/* SET-BLOCK-PERMANENTLY-CHANGED-FUNCTION */
Object set_block_permanently_changed_function(block)
    Object block;
{
    SI_Long svref_new_value;

    x_note_fn_call(86,13);
    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)4L;
    return VALUES_1(ISVREF(block,(SI_Long)5L) = FIX(svref_new_value));
}

Object Block_existed_at_start_of_save_flag = UNBOUND;

Object Item_was_created_by_load_flag = UNBOUND;

/* SET-ITEM-WAS-CREATED-BY-LOAD-FUNCTION */
Object set_item_was_created_by_load_function(item)
    Object item;
{
    SI_Long svref_new_value;

    x_note_fn_call(86,14);
    svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) | (SI_Long)16L;
    return VALUES_1(ISVREF(item,(SI_Long)5L) = FIX(svref_new_value));
}

Object Failed_flag = UNBOUND;

Object Workspace_was_active_flag = UNBOUND;

Object First_definition_mark_flag = UNBOUND;

Object Module_information_instance_mark_flag = UNBOUND;

Object Table_collected_flag = UNBOUND;

Object Has_indexed_attributes_flag = UNBOUND;

Object Currently_evaluating_formula_flag = UNBOUND;

Object Ancestor_not_activatable_flag = UNBOUND;

/* ANCESTOR-NOT-ACTIVATABLE-FUNCTION-P */
Object ancestor_not_activatable_function_p(block)
    Object block;
{
    x_note_fn_call(86,15);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)256L) ? T : Nil);
}

Object Previous_render_state_was_xor_flag = UNBOUND;

Object Render_frame_in_xor_overlay_flag = UNBOUND;

Object Block_is_currently_being_dragged_flag = UNBOUND;

Object Queued_by_local_data_server_flag = UNBOUND;

Object Second_definition_mark_flag = UNBOUND;

Object Preexisting_frame_flag = UNBOUND;

Object Block_overlap_cache_flag = UNBOUND;

Object Block_is_transformed_flag = UNBOUND;

Object Block_overlap_cache_valid_flag = UNBOUND;

Object Was_once_permanent_flag = UNBOUND;

Object Transient_flag = UNBOUND;

Object Do_not_save_in_kb_flag = UNBOUND;

Object Block_found_in_search_flag = UNBOUND;

/* CLEAR-BLOCKS-FOUND-IN-SEARCH */
Object clear_blocks_found_in_search(blocks)
    Object blocks;
{
    Object block, ab_loop_list_;
    SI_Long svref_new_value;

    x_note_fn_call(86,16);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) &  ~(SI_Long)1048576L;
    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

Object Item_has_icon_views_flag = UNBOUND;

Object Frame_flags_read_flag = UNBOUND;

Object Block_has_been_referenced_flag = UNBOUND;

Object Immutable_consistency_analysis_flag = UNBOUND;

Object Item_mark_flag = UNBOUND;

Object Tracking_item_mark_flag = UNBOUND;

Object Tracking_item_in_set_flag = UNBOUND;

static Object Qframe_flags;        /* frame-flags */

/* PUT-FRAME-FLAGS */
Object put_frame_flags(frame,value,initializing_qm)
    Object frame, value, initializing_qm;
{
    Object adjusted_value, old_value, frame_1, sub_vector_qm, function_qm;
    Object sub_class_bit_vector;
    SI_Long svref_new_value, method_index, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(86,17);
    if (initializing_qm) {
	adjusted_value = frame_flags_revised_function() ? value : 
		FIXNUM_LOGAND(value,Old_mask_for_saved_frame_flags);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_flags);
	svref_new_value = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) 
		& (SI_Long)131072L) ? IFIX(FIXNUM_LOGIOR(adjusted_value,
		Class_of_frame_is_user_defined_flag)) : 
		IFIX(adjusted_value) &  
		~IFIX(Class_of_frame_is_user_defined_flag);
	return VALUES_1(ISVREF(frame,(SI_Long)4L) = FIX(svref_new_value));
    }
    else {
	old_value = ISVREF(frame,(SI_Long)4L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_flags);
	SVREF(frame,FIX((SI_Long)4L)) = value;
	if ( !EQ((SI_Long)0L != (IFIX(old_value) & (SI_Long)33554432L) ? T 
		: Nil,(SI_Long)0L != (IFIX(value) & (SI_Long)33554432L) ? 
		T : Nil)) {
	    method_index = (SI_Long)38L;
	    frame_1 = frame;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		inline_funcall_1(function_qm,frame_1);
	}
	if ( !EQ((SI_Long)0L != (IFIX(old_value) & (SI_Long)16777216L) ? T 
		: Nil,(SI_Long)0L != (IFIX(value) & (SI_Long)16777216L) ? 
		T : Nil)) {
	    method_index = (SI_Long)18L;
	    frame_1 = frame;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		inline_funcall_1(function_qm,frame_1);
	}
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	if (temp ?  !TRUEP(Called_within_clear_text_loading) : TRUEP(Nil)) {
	    if (explanation_related_features_enabled_func_qm() && 
		    (SI_Long)0L != (IFIX(old_value) & (SI_Long)1048576L) 
		    &&  !((SI_Long)0L != (IFIX(value) & (SI_Long)1048576L)))
		clear_cached_explanations(frame);
	    recompile_item(frame);
	}
	return VALUES_1(value);
    }
}

/* RECLAIM-JOURNAL-TREE-FUNCTION */
Object reclaim_journal_tree_function(tree)
    Object tree;
{
    x_note_fn_call(86,18);
    reclaim_gensym_tree_1(tree);
    return VALUES_1(Nil);
}

/* RECLAIM-JOURNAL-LIST-FUNCTION */
Object reclaim_journal_list_function(tree)
    Object tree;
{
    x_note_fn_call(86,19);
    reclaim_gensym_list_1(tree);
    return VALUES_1(Nil);
}

/* NOTE-CHANGE-TO-BLOCK-1 */
Object note_change_to_block_1(block,pretty_slot_name_qm)
    Object block, pretty_slot_name_qm;
{
    Object temp;

    x_note_fn_call(86,20);
    temp = note_change_to_block_2(block,pretty_slot_name_qm);
    return VALUES_1(temp);
}

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

static Object Qdependent_frame;    /* dependent-frame */

/* NOTE-CHANGE-TO-DEPENDENT-FRAME-1 */
Object note_change_to_dependent_frame_1()
{
    Object temp;

    x_note_fn_call(86,21);
    temp =  !EQ(Qdependent_frame_has_no_owner,
	    Current_block_of_dependent_frame) ? 
	    note_change_to_block_2(Current_block_of_dependent_frame,
	    Qdependent_frame) : Nil;
    return VALUES_1(temp);
}

/* PERMANENTLY-RETRACT-CONSISTENCY-ANALYSIS */
Object permanently_retract_consistency_analysis(block)
    Object block;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;
    SI_Long svref_new_value;

    x_note_fn_call(86,22);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = block;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = T;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3);
    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)16777216L;
    return VALUES_1(ISVREF(block,(SI_Long)5L) = FIX(svref_new_value));
}

Object Compiled_items_deferred_for_analysis = UNBOUND;

Object Defer_consistency_analysis_qm = UNBOUND;

/* DEFER-CONSISTENCY-ANALYSIS-OF-ITEM */
Object defer_consistency_analysis_of_item(compiled_item)
    Object compiled_item;
{
    SI_Long svref_new_value;

    x_note_fn_call(86,23);
    if ( !((SI_Long)0L != (IFIX(ISVREF(compiled_item,(SI_Long)5L)) & 
	    (SI_Long)1048576L))) {
	svref_new_value = IFIX(ISVREF(compiled_item,(SI_Long)5L)) | 
		(SI_Long)1048576L;
	ISVREF(compiled_item,(SI_Long)5L) = FIX(svref_new_value);
	Compiled_items_deferred_for_analysis = gensym_cons_1(compiled_item,
		Compiled_items_deferred_for_analysis);
	return VALUES_1(Compiled_items_deferred_for_analysis);
    }
    else
	return VALUES_1(Nil);
}

static Object Qis_created;         /* is-created */

/* MAKE-FRAME */
Object make_frame(class_1)
    Object class_1;
{
    Object gensymed_symbol, sub_class_bit_vector, block_p, frame, result_1;
    Object current_flag_state_qm, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, new_frame;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;

    x_note_fn_call(86,24);
    gensymed_symbol = lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	block_p = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
    }
    else
	block_p = Nil;
    frame = make_frame_internal(gensymed_symbol,Nil,Nil,T,block_p);
    if (block_p) {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		    (SI_Long)16777216L;
	    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	}
	result_1 = initialize_frame(frame);
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		    ~(SI_Long)16777216L;
	    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	}
	if ( !((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)16777216L))) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_4 = frame;
	    gensymed_symbol_5 = T;
	    gensymed_symbol_6 = Nil;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
    }
    else
	initialize_frame(frame);
    new_frame = frame;
    schedule_task_to_invoke_existential_rules(new_frame,Qis_created);
    return VALUES_1(new_frame);
}

/* MAKE-FRAME-OF-CLASS-DESCRIPTION */
Object make_frame_of_class_description(class_description)
    Object class_description;
{
    Object gensymed_symbol, sub_class_bit_vector, block_p, frame, result_1;
    Object current_flag_state_qm, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, new_frame;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;

    x_note_fn_call(86,25);
    gensymed_symbol = class_description;
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	block_p = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
    }
    else
	block_p = Nil;
    frame = make_frame_internal(gensymed_symbol,Nil,Nil,T,block_p);
    if (block_p) {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		    (SI_Long)16777216L;
	    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	}
	result_1 = initialize_frame(frame);
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		    ~(SI_Long)16777216L;
	    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	}
	if ( !((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)16777216L))) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_4 = frame;
	    gensymed_symbol_5 = T;
	    gensymed_symbol_6 = Nil;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
    }
    else
	initialize_frame(frame);
    new_frame = frame;
    schedule_task_to_invoke_existential_rules(new_frame,Qis_created);
    return VALUES_1(new_frame);
}

/* MAKE-FRAME-WITHOUT-COMPUTED-INITIALIZATIONS */
Object make_frame_without_computed_initializations(class_description,
	    frame_serial_number_qm,uuid_qm)
    Object class_description, frame_serial_number_qm, uuid_qm;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(86,26);
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
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    temp = make_frame_internal(class_description,frame_serial_number_qm,
	    uuid_qm,Nil,temp);
    return VALUES_1(temp);
}

static Object Qhas_indexed_attributes;  /* has-indexed-attributes */

/* MAKE-FRAME-INTERNAL */
Object make_frame_internal(class_description,frame_serial_number_qm,
	    uuid_qm,eval_slot_init_forms_p,block_case_p)
    Object class_description, frame_serial_number_qm, uuid_qm;
    Object eval_slot_init_forms_p, block_case_p;
{
    Object frame, noting_changes_to_kb_p, value_1;
    SI_Long svref_new_value;
    char value;
    Declare_special(1);

    x_note_fn_call(86,27);
    frame = allocate_frame(class_description,frame_serial_number_qm,
	    uuid_qm,eval_slot_init_forms_p,block_case_p);
    if (block_case_p) {
	noting_changes_to_kb_p = Nil;
	PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
	  value =  !TRUEP(ISVREF(class_description,(SI_Long)20L));
	  if (value) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(frame,Qframe_flags);
	      svref_new_value = IFIX(ISVREF(frame,(SI_Long)4L)) | 
		      (SI_Long)131072L;
	      ISVREF(frame,(SI_Long)4L) = FIX(svref_new_value);
	  }
	  else {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(frame,Qframe_flags);
	      svref_new_value = IFIX(ISVREF(frame,(SI_Long)4L)) &  
		      ~(SI_Long)131072L;
	      ISVREF(frame,(SI_Long)4L) = FIX(svref_new_value);
	  }
	  value_1 = assq_function(Qhas_indexed_attributes,
		  ISVREF(class_description,(SI_Long)12L));
	  if (value_1) {
	      svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | (SI_Long)64L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	  }
	  else {
	      svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		      ~(SI_Long)64L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	  }
	POP_SPECIAL();
    }
    return VALUES_1(frame);
}

/* PREPARE-TO-SAVING-FRAME-FOR-KB-FRAME */
Object prepare_to_saving_frame_for_kb_frame(kb_frame)
    Object kb_frame;
{
    x_note_fn_call(86,28);
    return VALUES_1(Nil);
}

/* ON-FRAME-SAVED-FOR-KB-FRAME */
Object on_frame_saved_for_kb_frame(kb_frame)
    Object kb_frame;
{
    x_note_fn_call(86,29);
    return VALUES_1(Nil);
}

/* INITIALIZE-FRAME */
Object initialize_frame(frame)
    Object frame;
{
    Object noting_changes_to_kb_p, current_block_of_dependent_frame;
    Object frame_being_made, frame_1, sub_vector_qm, function_qm;
    SI_Long method_index;
    Declare_special(3);

    x_note_fn_call(86,30);
    noting_changes_to_kb_p = Nil;
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    frame_being_made = frame;
    PUSH_SPECIAL(Frame_being_made,frame_being_made,2);
      PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
	      1);
	PUSH_SPECIAL(Noting_changes_to_kb_p,noting_changes_to_kb_p,0);
	  method_index = (SI_Long)2L;
	  frame_1 = frame;
	  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		  (SI_Long)11L),method_index);
	  function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) :
		   Nil;
	  if (function_qm)
	      inline_funcall_1(function_qm,frame_1);
	  note_as_preexisting_frame_if_appropriate(frame);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

Object Note_as_kb_state_change_qm = UNBOUND;

/* HAS-ONLY-ONE-SUBBLOCK-P */
Object has_only_one_subblock_p(block)
    Object block;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp;
    SI_Long count_1;

    x_note_fn_call(86,31);
    count_1 = (SI_Long)0L;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)4L) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
  next_loop:
    if (EQ(ab_next_queue_element_,ab_queue_form_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
    count_1 = count_1 + (SI_Long)1L;
    if (count_1 > (SI_Long)1L)
	goto end_loop;
    goto next_loop;
  end_loop:
    if (count_1 == (SI_Long)1L) {
	temp = T;
	goto end_1;
    }
    else {
	temp = Nil;
	goto end_1;
    }
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIRST-SUBBLOCK */
Object first_subblock(block)
    Object block;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp;

    x_note_fn_call(86,32);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)4L) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
  next_loop:
    if (EQ(ab_next_queue_element_,ab_queue_form_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
    temp = subblock;
    goto end_1;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SECOND-SUBBLOCK */
Object second_subblock(block)
    Object block;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp;
    SI_Long count_1;

    x_note_fn_call(86,33);
    count_1 = (SI_Long)0L;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)4L) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
  next_loop:
    if (EQ(ab_next_queue_element_,ab_queue_form_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
    count_1 = count_1 + (SI_Long)1L;
    if (count_1 == (SI_Long)2L) {
	temp = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* LAST-SUBBLOCK */
Object last_subblock(block)
    Object block;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp;

    x_note_fn_call(86,34);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)4L) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
  next_loop:
    if (EQ(ab_next_queue_element_,ab_queue_form_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
    goto next_loop;
  end_loop:
    temp = subblock;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* UPGRADE-SUBBLOCKS */
Object upgrade_subblocks(blocks)
    Object blocks;
{
    Object constant_queue, block, ab_loop_list_, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;

    x_note_fn_call(86,35);
    constant_queue = make_empty_constant_queue();
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(constant_queue,(SI_Long)1L);
    def_structure_queue_element_variable = Chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	Chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = 
	    constant_queue;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
	    gensymed_symbol;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = block;
    gensymed_symbol_1 = def_structure_queue_element_variable;
    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
    SVREF(constant_queue,FIX((SI_Long)1L)) = gensymed_symbol_1;
    goto next_loop;
  end_loop:;
    return VALUES_1(constant_queue);
}

/* INITIALIZE-FOR-SYSTEM-ITEM */
Object initialize_for_system_item(system_item)
    Object system_item;
{
    x_note_fn_call(86,36);
    return VALUES_1(Nil);
}

static Object Qsystem_item;        /* system-item */

/* INITIALIZE-AFTER-READING-FOR-SYSTEM-ITEM */
Object initialize_after_reading_for_system_item(system_item)
    Object system_item;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(86,37);
    frame = system_item;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qsystem_item)) {
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

void frames3_INIT()
{
    Object temp, reclaim_structure_for_icon_slot_group_1, temp_1;
    Object Qclasses_which_define, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_system_item, AB_package, Qinitialize;
    Object Qinitialize_for_system_item, Qon_frame_saved, Qkb_frame;
    Object Qon_frame_saved_for_kb_frame, Qprepare_to_saving_frame;
    Object Qprepare_to_saving_frame_for_kb_frame, Qgeneric_method_lambda_list;
    Object list_constant_1, Qinstall, Qdefer_consistency_analysis_qm;
    Object Qcompiled_items_deferred_for_analysis, Qslot_putter;
    Object Qput_frame_flags, Qinitialize_default_icon_slot_group;
    Object list_constant, Qframes3, Qdefault_icon_slot_group, Kfuncall;
    Object Qicon_slot_group, Qreclaim_structure;
    Object Qoutstanding_icon_slot_group_count;
    Object Qicon_slot_group_structure_memory_usage, Qutilities2;
    Object Qicon_slot_group_count, Qchain_of_available_icon_slot_groups;
    Object string_constant_1, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_icon_slot_group_g2_struct;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant;

    x_note_fn_call(86,38);
    SET_PACKAGE("AB");
    if (The_type_description_of_icon_slot_group == UNBOUND)
	The_type_description_of_icon_slot_group = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m83imy1m83imy8k1l8k0000001m1m83*gy9k1m83=ey3-Wykrk0k0");
    temp = The_type_description_of_icon_slot_group;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_icon_slot_group = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_icon_slot_group_g2_struct = 
	    STATIC_SYMBOL("ICON-SLOT-GROUP-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icon_slot_group_g2_struct,
	    The_type_description_of_icon_slot_group,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qicon_slot_group = STATIC_SYMBOL("ICON-SLOT-GROUP",AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qicon_slot_group,
	    The_type_description_of_icon_slot_group,Qtype_description_of_type);
    Qoutstanding_icon_slot_group_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICON-SLOT-GROUP-COUNT",AB_package);
    Qicon_slot_group_structure_memory_usage = 
	    STATIC_SYMBOL("ICON-SLOT-GROUP-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_1 = STATIC_STRING("1q83imy8s83-Y+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icon_slot_group_count);
    push_optimized_constant(Qicon_slot_group_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_icon_slot_groups = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICON-SLOT-GROUPS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icon_slot_groups,
	    Chain_of_available_icon_slot_groups);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_icon_slot_groups,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qicon_slot_group_count = STATIC_SYMBOL("ICON-SLOT-GROUP-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicon_slot_group_count,Icon_slot_group_count);
    record_system_variable(Qicon_slot_group_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qicon_slot_group_structure_memory_usage,
	    STATIC_FUNCTION(icon_slot_group_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icon_slot_group_count,
	    STATIC_FUNCTION(outstanding_icon_slot_group_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_icon_slot_group_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icon_slot_group,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicon_slot_group,
	    reclaim_structure_for_icon_slot_group_1);
    Ws_protocol_handle_moves_from_edge_change_p = Nil;
    Ws_protocol_trace_p = Nil;
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qdefault_icon_slot_group = STATIC_SYMBOL("DEFAULT-ICON-SLOT-GROUP",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_icon_slot_group,
	    Default_icon_slot_group);
    Qframes3 = STATIC_SYMBOL("FRAMES3",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_default_icon_slot_group = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-ICON-SLOT-GROUP",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_icon_slot_group);
    record_system_variable(Qdefault_icon_slot_group,Qframes3,list_constant,
	    Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_default_icon_slot_group,
	    STATIC_FUNCTION(initialize_default_icon_slot_group,NIL,FALSE,0,0));
    Forward_chain_flag = FIX((SI_Long)2L);
    Invocable_via_backward_chaining_flag = FIX((SI_Long)2L);
    Savable_kb_workspace_flag = FIX((SI_Long)2L);
    Recent_procedure_flag = FIX((SI_Long)2L);
    Sketch_definition_flag = FIX((SI_Long)2L);
    Backward_chains_to_old_rule_flag = FIX((SI_Long)4L);
    Depth_first_flag = FIX((SI_Long)8L);
    Invocable_via_forward_chaining_flag = FIX((SI_Long)8L);
    Passive_flag = FIX((SI_Long)16L);
    May_cause_data_seeking_flag = FIX((SI_Long)16L);
    Always_forward_chain_if_possible_flag = FIX((SI_Long)32L);
    One_shot_flag = FIX((SI_Long)64L);
    Opaque_block_flag = FIX((SI_Long)1024L);
    Initial_rule_flag = FIX((SI_Long)2048L);
    Overlapping_block_flag = FIX((SI_Long)4096L);
    Manually_disabled_flag = FIX((SI_Long)8192L);
    Multiple_compilations_flag = FIX((SI_Long)16384L);
    Journal_expiration_flag = FIX((SI_Long)16384L);
    Dont_backward_chain_flag = FIX((SI_Long)32768L);
    May_cause_forward_chaining_flag = FIX((SI_Long)32768L);
    Compiled_as_new_rule_flag = FIX((SI_Long)65536L);
    Class_of_frame_is_user_defined_flag = FIX((SI_Long)131072L);
    Cache_data_for_explanation_flag = FIX((SI_Long)1048576L);
    Strip_text_flag = FIX((SI_Long)2097152L);
    Do_not_strip_text_flag = FIX((SI_Long)4194304L);
    Table_may_not_be_wysiwyg_flag = FIX((SI_Long)8388608L);
    Runs_while_inactive_flag = FIX((SI_Long)16777216L);
    May_refer_to_inactive_items_flag = FIX((SI_Long)33554432L);
    Self_referenced_flag = FIX((SI_Long)67108864L);
    Block_has_been_written_flag = FIX((SI_Long)2L);
    Block_permanently_changed_flag = FIX((SI_Long)4L);
    Block_existed_at_start_of_save_flag = FIX((SI_Long)8L);
    Item_was_created_by_load_flag = FIX((SI_Long)16L);
    Failed_flag = FIX((SI_Long)32L);
    Workspace_was_active_flag = FIX((SI_Long)32L);
    First_definition_mark_flag = FIX((SI_Long)32L);
    Module_information_instance_mark_flag = FIX((SI_Long)32L);
    Table_collected_flag = FIX((SI_Long)32L);
    Has_indexed_attributes_flag = FIX((SI_Long)64L);
    Currently_evaluating_formula_flag = FIX((SI_Long)128L);
    Ancestor_not_activatable_flag = FIX((SI_Long)256L);
    Previous_render_state_was_xor_flag = FIX((SI_Long)512L);
    Render_frame_in_xor_overlay_flag = FIX((SI_Long)1024L);
    Block_is_currently_being_dragged_flag = FIX((SI_Long)2048L);
    Queued_by_local_data_server_flag = FIX((SI_Long)4096L);
    Second_definition_mark_flag = FIX((SI_Long)4096L);
    Preexisting_frame_flag = FIX((SI_Long)8192L);
    Block_overlap_cache_flag = FIX((SI_Long)16384L);
    Block_is_transformed_flag = FIX((SI_Long)32768L);
    Block_overlap_cache_valid_flag = FIX((SI_Long)65536L);
    Was_once_permanent_flag = FIX((SI_Long)131072L);
    Transient_flag = FIX((SI_Long)262144L);
    Do_not_save_in_kb_flag = FIX((SI_Long)524288L);
    Block_found_in_search_flag = FIX((SI_Long)1048576L);
    Item_has_icon_views_flag = FIX((SI_Long)2097152L);
    Frame_flags_read_flag = FIX((SI_Long)4194304L);
    Block_has_been_referenced_flag = FIX((SI_Long)8388608L);
    Immutable_consistency_analysis_flag = FIX((SI_Long)16777216L);
    Item_mark_flag = FIX((SI_Long)33554432L);
    Tracking_item_mark_flag = FIX((SI_Long)67108864L);
    Tracking_item_in_set_flag = FIX((SI_Long)134217728L);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qput_frame_flags = STATIC_SYMBOL("PUT-FRAME-FLAGS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_frame_flags,STATIC_FUNCTION(put_frame_flags,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qframe_flags,SYMBOL_FUNCTION(Qput_frame_flags),
	    Qslot_putter);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    Qcompiled_items_deferred_for_analysis = 
	    STATIC_SYMBOL("COMPILED-ITEMS-DEFERRED-FOR-ANALYSIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiled_items_deferred_for_analysis,
	    Compiled_items_deferred_for_analysis);
    Qinstall = STATIC_SYMBOL("INSTALL",AB_package);
    record_system_variable(Qcompiled_items_deferred_for_analysis,Qinstall,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qdefer_consistency_analysis_qm = 
	    STATIC_SYMBOL("DEFER-CONSISTENCY-ANALYSIS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefer_consistency_analysis_qm,
	    Defer_consistency_analysis_qm);
    record_system_variable(Qdefer_consistency_analysis_qm,Qinstall,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qis_created = STATIC_SYMBOL("IS-CREATED",AB_package);
    Qhas_indexed_attributes = STATIC_SYMBOL("HAS-INDEXED-ATTRIBUTES",
	    AB_package);
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    list_constant_1 = STATIC_CONS(Qkb_frame,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qinitialize,list_constant_1,
	    Qgeneric_method_lambda_list);
    Qprepare_to_saving_frame = STATIC_SYMBOL("PREPARE-TO-SAVING-FRAME",
	    AB_package);
    mutate_global_property(Qprepare_to_saving_frame,list_constant_1,
	    Qgeneric_method_lambda_list);
    Qon_frame_saved = STATIC_SYMBOL("ON-FRAME-SAVED",AB_package);
    mutate_global_property(Qon_frame_saved,list_constant_1,
	    Qgeneric_method_lambda_list);
    Qprepare_to_saving_frame_for_kb_frame = 
	    STATIC_SYMBOL("PREPARE-TO-SAVING-FRAME-FOR-KB-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qprepare_to_saving_frame_for_kb_frame,
	    STATIC_FUNCTION(prepare_to_saving_frame_for_kb_frame,NIL,FALSE,
	    1,1));
    temp_1 = SYMBOL_FUNCTION(Qprepare_to_saving_frame_for_kb_frame);
    set_get(Qkb_frame,Qprepare_to_saving_frame,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qprepare_to_saving_frame),
	    Qclasses_which_define);
    temp_1 = CONS(Qkb_frame,temp);
    mutate_global_property(Qprepare_to_saving_frame,temp_1,
	    Qclasses_which_define);
    Qon_frame_saved_for_kb_frame = 
	    STATIC_SYMBOL("ON-FRAME-SAVED-FOR-KB-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qon_frame_saved_for_kb_frame,
	    STATIC_FUNCTION(on_frame_saved_for_kb_frame,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qon_frame_saved_for_kb_frame);
    set_get(Qkb_frame,Qon_frame_saved,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qon_frame_saved),
	    Qclasses_which_define);
    temp_1 = CONS(Qkb_frame,temp);
    mutate_global_property(Qon_frame_saved,temp_1,Qclasses_which_define);
    if (Note_as_kb_state_change_qm == UNBOUND)
	Note_as_kb_state_change_qm = Nil;
    Qinitialize_for_system_item = 
	    STATIC_SYMBOL("INITIALIZE-FOR-SYSTEM-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_system_item,
	    STATIC_FUNCTION(initialize_for_system_item,NIL,FALSE,1,1));
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_system_item);
    set_get(Qsystem_item,Qinitialize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qsystem_item,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qinitialize_after_reading_for_system_item = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-SYSTEM-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_system_item,
	    STATIC_FUNCTION(initialize_after_reading_for_system_item,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_system_item);
    set_get(Qsystem_item,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qsystem_item,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
}
