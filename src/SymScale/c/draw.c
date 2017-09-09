/* draw.c
 * Input file:  draw.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "draw.h"


/* FUNCALL-FOR-WORKSTATION-OF-IMAGE-PLANE */
Object funcall_for_workstation_of_image_plane varargs_1(int, n)
{
    Object image_plane, function;
    Object arg1, arg2, arg3, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(89,0);
    INIT_ARGS_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = ISVREF(ISVREF(ISVREF(image_plane,
		(SI_Long)2L),(SI_Long)2L),(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
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
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
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
				if (EQ(arg1,No_arg))
				    SAVE_VALUES(FUNCALL_0(function));
				else if (EQ(arg2,No_arg))
				    SAVE_VALUES(FUNCALL_1(function,arg1));
				else if (EQ(arg3,No_arg))
				    SAVE_VALUES(FUNCALL_2(function,arg1,arg2));
				else
				    SAVE_VALUES(FUNCALL_3(function,arg1,
					    arg2,arg3));
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

DEFINE_VARIABLE_WITH_SYMBOL(With_extreme_edges, Qwith_extreme_edges);

DEFINE_VARIABLE_WITH_SYMBOL(Extreme_left_edge_so_far, Qextreme_left_edge_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Extreme_top_edge_so_far, Qextreme_top_edge_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Extreme_right_edge_so_far, Qextreme_right_edge_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Extreme_bottom_edge_so_far, Qextreme_bottom_edge_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_update_selection_highlights, Qdo_not_update_selection_highlights);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qgraph_grid;         /* graph-grid */

static Object Qgraph_axis_label;   /* graph-axis-label */

static Object Qworkspace_spacial_index_qm;  /* workspace-spacial-index? */

/* NOTE-CHANGE-TO-EDGES-OF-BLOCK */
Object note_change_to_edges_of_block(block,old_left,old_top,old_right,
	    old_bottom,new_left,new_top,new_right,new_bottom)
    Object block, old_left, old_top, old_right, old_bottom, new_left, new_top;
    Object new_right, new_bottom;
{
    Object workspace_qm, x2, gensymed_symbol, geometry_qm;
    Object sub_class_bit_vector, connections, connection, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,1);
    workspace_qm = get_workspace_if_any(block);
    if (workspace_qm) {
	if (SIMPLE_VECTOR_P(block) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L &&  
		!EQ(ISVREF(block,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
	    temp = EQ(gensymed_symbol,Qgraph_grid);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qgraph_axis_label);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    note_permanent_change_to_slot_group_for_block(block);
	    note_change_to_workspace_geometry(workspace_qm);
	    geometry_qm = get_lookup_slot_value_given_default(workspace_qm,
		    Qworkspace_spacial_index_qm,Nil);
	    if (geometry_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
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
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    old_right = FIXNUM_ADD1(old_right);
		    old_bottom = FIXNUM_ADD1(old_bottom);
		}
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    new_right = FIXNUM_ADD1(new_right);
		    new_bottom = FIXNUM_ADD1(new_bottom);
		}
		geometry_delete(geometry_qm,block,old_left,old_top,
			old_right,old_bottom);
		geometry_insert(geometry_qm,block,new_left,new_top,
			new_right,new_bottom);
		connections = output_connections_of_block(block);
		connection = Nil;
		ab_loop_list_ = connections;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		connection = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		note_change_of_connection_for_drawing(connection);
		goto next_loop;
	      end_loop:;
		if (connections)
		    reclaim_tree_ordering_list_1(connections);
	    }
	    if ( !TRUEP(Do_not_update_selection_highlights))
		return recompute_selection_highlights(block);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-EXTREME-EDGES-FROM-BLOCK-BOUNDS */
Object update_extreme_edges_from_block_bounds(block)
    Object block;
{
    Object gensymed_symbol, left_edge, top_edge, right_edge, bottom_edge;
    Object sub_class_bit_vector, frame_description_reference_qm, decff_1_arg;
    Object incff_1_arg;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge = gensymed_symbol;
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	right_edge = FIXNUM_ADD1(right_edge);
	bottom_edge = FIXNUM_ADD1(bottom_edge);
    }
    frame_description_reference_qm = 
	    fast_lookup_frame_description_reference_of_block_qm(block);
    if (frame_description_reference_qm) {
	decff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)4L);
	left_edge = FIXNUM_MINUS(left_edge,decff_1_arg);
	decff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)5L);
	top_edge = FIXNUM_MINUS(top_edge,decff_1_arg);
	incff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)6L);
	right_edge = FIXNUM_ADD(right_edge,incff_1_arg);
	incff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)7L);
	bottom_edge = FIXNUM_ADD(bottom_edge,incff_1_arg);
    }
    if (FIXNUM_LT(left_edge,Extreme_left_edge_so_far))
	Extreme_left_edge_so_far = left_edge;
    if (FIXNUM_GT(right_edge,Extreme_right_edge_so_far))
	Extreme_right_edge_so_far = right_edge;
    if (FIXNUM_LT(top_edge,Extreme_top_edge_so_far))
	Extreme_top_edge_so_far = top_edge;
    if (FIXNUM_GT(bottom_edge,Extreme_bottom_edge_so_far)) {
	Extreme_bottom_edge_so_far = bottom_edge;
	return VALUES_1(Extreme_bottom_edge_so_far);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-EXTREME-EDGES-FROM-ELEMENTS-FUNCTION */
Object update_extreme_edges_from_elements_function(block,do_only_loose_ends_p)
    Object block, do_only_loose_ends_p;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object subblocks;
    char temp;

    x_note_fn_call(89,3);
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L))) {
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
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	update_extreme_edges_from_block_bounds(subblock);
	gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	temp = subblocks ?  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
		(SI_Long)2L),subblocks)) : TRUEP(Qnil);
	if (temp);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    temp = TRUEP(gensymed_symbol);
	}
	if (temp)
	    update_extreme_edges_from_elements_function(subblock,
		    do_only_loose_ends_p);
	goto next_loop;
      end_loop:;
	update_extreme_edges_from_connections_of_block(block,
		do_only_loose_ends_p);
    }
    return VALUES_1(Nil);
}

static Object Qblock_and_frame_extent;  /* block-and-frame-extent */

/* DETERMINE-EXTREME-EDGES-OF-BLOCK */
Object determine_extreme_edges_of_block(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, subblocks;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,4);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    if ( !EQ(Purpose_of_extreme_edges,Qblock_and_frame_extent)) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		subblocks = gensymed_symbol;
		temp = subblocks ?  ! 
			!TRUEP(constant_queue_next(ISVREF(subblocks,
			(SI_Long)2L),subblocks)) : TRUEP(Qnil);
		if (temp);
		else {
		    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		    gensymed_symbol = gensymed_symbol ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol,
			    (SI_Long)6L)) : Nil;
		    temp = TRUEP(gensymed_symbol);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		update_extreme_edges_from_elements_function(block,Nil);
	    result = VALUES_4(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* LOCAL-EDGES-OF-BLOCK */
Object local_edges_of_block(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,5);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    result = VALUES_4(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* MAKE-REGION-FROM-BLOCK-EDGES */
Object make_region_from_block_edges(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,6);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    result = make_region_from_rectangle(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DETERMINE-EXTREME-EDGES-OF-WORKSPACE-SUBBLOCKS */
Object determine_extreme_edges_of_workspace_subblocks(workspace)
    Object workspace;
{
    Object gensymed_symbol, subblocks, block, extreme_left_edge_so_far;
    Object extreme_top_edge_so_far, extreme_right_edge_so_far;
    Object extreme_bottom_edge_so_far;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,7);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks))) {
	block = first_subblock(workspace);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		3);
	  gensymed_symbol = ISVREF(block,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  extreme_top_edge_so_far = gensymed_symbol;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		  2);
	    extreme_right_edge_so_far = Extreme_left_edge_so_far;
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		    1);
	      extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		      0);
		update_extreme_edges_from_block_bounds(block);
		update_extreme_edges_from_elements_function(workspace,Nil);
		result = VALUES_4(Extreme_left_edge_so_far,
			Extreme_top_edge_so_far,Extreme_right_edge_so_far,
			Extreme_bottom_edge_so_far);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DETERMINE-EXTREME-EDGES-OF-BLOCKS-AND-CONNECTIONS */
Object determine_extreme_edges_of_blocks_and_connections(blocks,
	    connections,do_only_loose_ends_p)
    Object blocks, connections, do_only_loose_ends_p;
{
    Object block, gensymed_symbol, extreme_left_edge_so_far;
    Object extreme_top_edge_so_far, extreme_right_edge_so_far;
    Object extreme_bottom_edge_so_far, block_1, ab_loop_list_, connection;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,8);
    block = FIRST(blocks);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    block_1 = Nil;
	    ab_loop_list_ = blocks;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    update_extreme_edges_from_block_bounds(block_1);
	    update_extreme_edges_from_elements_function(block_1,
		    do_only_loose_ends_p);
	    goto next_loop;
	  end_loop:;
	    connection = Nil;
	    ab_loop_list_ = connections;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    connection = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !(do_only_loose_ends_p &&  
		    !TRUEP(loose_end_connection_p(connection))))
		update_extreme_edges_from_connection(connection);
	    goto next_loop_1;
	  end_loop_1:;
	    result = VALUES_4(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* EXTENT-OF-BLOCK-WITHIN-DRAW-AREA */
Object extent_of_block_within_draw_area(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, temp_1;
    Object temp_2, temp_3, temp_4;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long extreme_left_edge_in_window, extreme_top_edge_in_window;
    SI_Long extreme_right_edge_in_window, extreme_bottom_edge_in_window, temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,9);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    update_extreme_edges_from_block_bounds(block);
	    update_extreme_edges_from_elements_function(block,Nil);
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_left_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_left_edge_so_far) && 
		    FIXNUM_LT(Extreme_left_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Extreme_left_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_x_scale,
			Extreme_left_edge_so_far));
	    extreme_left_edge_in_window = gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_top_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_top_edge_so_far) && 
		    FIXNUM_LT(Extreme_top_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Extreme_top_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_y_scale,
			Extreme_top_edge_so_far));
	    extreme_top_edge_in_window = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_right_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_right_edge_so_far) && 
		    FIXNUM_LT(Extreme_right_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Extreme_right_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_x_scale,
			Extreme_right_edge_so_far));
	    extreme_right_edge_in_window = gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_bottom_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_bottom_edge_so_far) && 
		    FIXNUM_LT(Extreme_bottom_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Extreme_bottom_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_y_scale,
			Extreme_bottom_edge_so_far));
	    extreme_bottom_edge_in_window = gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    if ((IFIX(Bottom_edge_of_draw_area) >= 
		    extreme_bottom_edge_in_window && 
		    extreme_bottom_edge_in_window >= 
		    IFIX(Top_edge_of_draw_area) || 
		    extreme_bottom_edge_in_window >= 
		    IFIX(Bottom_edge_of_draw_area) && 
		    IFIX(Bottom_edge_of_draw_area) >= 
		    extreme_top_edge_in_window) && 
		    (IFIX(Right_edge_of_draw_area) >= 
		    extreme_right_edge_in_window && 
		    extreme_right_edge_in_window >= 
		    IFIX(Left_edge_of_draw_area) || 
		    extreme_right_edge_in_window >= 
		    IFIX(Right_edge_of_draw_area) && 
		    IFIX(Right_edge_of_draw_area) >= 
		    extreme_left_edge_in_window)) {
		temp = IFIX(Left_edge_of_draw_area);
		temp_1 = FIX(MAX(extreme_left_edge_in_window,temp));
		temp = IFIX(Top_edge_of_draw_area);
		temp_2 = FIX(MAX(extreme_top_edge_in_window,temp));
		temp = IFIX(Right_edge_of_draw_area);
		temp_3 = FIX(MIN(extreme_right_edge_in_window,temp));
		temp = IFIX(Bottom_edge_of_draw_area);
		temp_4 = FIX(MIN(extreme_bottom_edge_in_window,temp));
		result = VALUES_4(temp_1,temp_2,temp_3,temp_4);
	    }
	    else
		result = VALUES_4(Left_edge_of_draw_area,
			Top_edge_of_draw_area,Left_edge_of_draw_area,
			Top_edge_of_draw_area);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* BLOCK-OVERLAPS-DRAW-AREA */
Object block_overlaps_draw_area(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result, l1, t1, r1;
    SI_Long b1;
    Declare_special(4);

    x_note_fn_call(89,10);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    update_extreme_edges_from_elements_function(block,Nil);
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_left_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_left_edge_so_far) && 
		    FIXNUM_LT(Extreme_left_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Extreme_left_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_x_scale,
			Extreme_left_edge_so_far));
	    l1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_top_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_top_edge_so_far) && 
		    FIXNUM_LT(Extreme_top_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Extreme_top_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_y_scale,
			Extreme_top_edge_so_far));
	    t1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_right_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_right_edge_so_far) && 
		    FIXNUM_LT(Extreme_right_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Extreme_right_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_x_scale,
			Extreme_right_edge_so_far));
	    r1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(Extreme_bottom_edge_so_far);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Extreme_bottom_edge_so_far) && 
		    FIXNUM_LT(Extreme_bottom_edge_so_far,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Extreme_bottom_edge_so_far)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_y_scale,
			Extreme_bottom_edge_so_far));
	    b1 = gensymed_symbol_1 + gensymed_symbol_2;
	    if (IFIX(Bottom_edge_of_draw_area) >= b1 && b1 >= 
		    IFIX(Top_edge_of_draw_area) || b1 >= 
		    IFIX(Bottom_edge_of_draw_area) && 
		    IFIX(Bottom_edge_of_draw_area) >= t1) {
		temp = IFIX(Right_edge_of_draw_area) >= r1 ? (r1 >= 
			IFIX(Left_edge_of_draw_area) ? T : Nil) : Qnil;
		if (temp);
		else
		    temp = r1 >= IFIX(Right_edge_of_draw_area) ? 
			    (IFIX(Right_edge_of_draw_area) >= l1 ? T : 
			    Nil) : Qnil;
	    }
	    else
		temp = Nil;
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* IN-BLOCK-P */
Object in_block_p(block,x_in_workspace,y_in_workspace)
    Object block, x_in_workspace, y_in_workspace;
{
    Object gensymed_symbol, temp_1, ab_queue_form_, ab_next_queue_element_;
    Object subblock, ab_loop_it_;
    char temp;

    x_note_fn_call(89,11);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    if (FIXNUM_GE(x_in_workspace,gensymed_symbol)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp = FIXNUM_LE(x_in_workspace,gensymed_symbol);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp = FIXNUM_GE(y_in_workspace,gensymed_symbol);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp_1 = FIXNUM_LE(y_in_workspace,gensymed_symbol) ? T : Nil;
    }
    else
	temp_1 = Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	ab_loop_it_ = in_block_p(subblock,x_in_workspace,y_in_workspace);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* IN-EXTREME-EDGES-OF-BLOCK-P */
Object in_extreme_edges_of_block_p(block,x_in_workspace,y_in_workspace)
    Object block, x_in_workspace, y_in_workspace;
{
    Object extreme_left_edge, extreme_top_edge, extreme_right_edge;
    Object extreme_bottom_edge;
    Object result;

    x_note_fn_call(89,12);
    result = determine_extreme_edges_of_block(block);
    MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
	    extreme_bottom_edge);
    if (FIXNUM_GE(x_in_workspace,extreme_left_edge) && 
	    FIXNUM_LE(x_in_workspace,extreme_right_edge) && 
	    FIXNUM_GE(y_in_workspace,extreme_top_edge))
	return VALUES_1(FIXNUM_LE(y_in_workspace,extreme_bottom_edge) ? T :
		 Nil);
    else
	return VALUES_1(Nil);
}

/* EDGES-OF-BLOCK-CONTENT-PLUS-FRAME */
Object edges_of_block_content_plus_frame(block)
    Object block;
{
    Object frame_description_reference_qm, gensymed_symbol, left_edge;
    Object top_edge, right_edge, bottom_edge, decff_1_arg, incff_1_arg;

    x_note_fn_call(89,13);
    frame_description_reference_qm = 
	    fast_lookup_frame_description_reference_of_block_qm(block);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge = gensymed_symbol;
    if (frame_description_reference_qm) {
	decff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)4L);
	left_edge = FIXNUM_MINUS(left_edge,decff_1_arg);
	decff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)5L);
	top_edge = FIXNUM_MINUS(top_edge,decff_1_arg);
	incff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)6L);
	right_edge = FIXNUM_ADD(right_edge,incff_1_arg);
	incff_1_arg = ISVREF(frame_description_reference_qm,(SI_Long)7L);
	bottom_edge = FIXNUM_ADD(bottom_edge,incff_1_arg);
    }
    return VALUES_4(left_edge,top_edge,right_edge,bottom_edge);
}

/* FIND-NEXT-NON-LOOSE-END */
Object find_next_non_loose_end(list_1)
    Object list_1;
{
    Object block, ab_loop_list_, output_connections, temp;

    x_note_fn_call(89,14);
    block = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (loose_end_p_function(block)) {
	output_connections = output_connections_of_block(block);
	if (output_connections) {
	    temp = 
		    get_or_make_connection_frame_and_activate_if_appropriate(CAR(output_connections));
	    reclaim_tree_ordering_list_1(output_connections);
	    goto end_1;
	}
    }
    else {
	temp = get_topmost_child_of_block(block);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FIND-NEXT-NON-LOOSE-END-IN-QUEUE */
Object find_next_non_loose_end_in_queue(constant_queue,cursor)
    Object constant_queue, cursor;
{
    Object head, queue_element, block, output_connections, temp;

    x_note_fn_call(89,15);
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = cursor ? constant_queue_next(cursor,constant_queue) : 
	    constant_queue_next(head,constant_queue);
    block = Nil;
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    block = ISVREF(queue_element,(SI_Long)4L);
    if (loose_end_p_function(block)) {
	output_connections = output_connections_of_block(block);
	if (output_connections) {
	    temp = 
		    get_or_make_connection_frame_and_activate_if_appropriate(CAR(output_connections));
	    reclaim_tree_ordering_list_1(output_connections);
	    goto end_1;
	}
    }
    else {
	temp = get_topmost_child_of_block(block);
	goto end_1;
    }
    queue_element = constant_queue_next(queue_element,constant_queue);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qnumber_of_blocks_on_workspace;  /* number-of-blocks-on-workspace */

static Object Qg2_add;             /* add */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qsubblocks;          /* subblocks */

static Object Qbottom;             /* bottom */

static Object Qlayer_position_of_block;  /* layer-position-of-block */

/* ADD-SUBBLOCK */
Object add_subblock(block,superblock)
    Object block, superblock;
{
    Object workspace_qm, next_item, temp, gensymed_symbol, gensymed_symbol_1;
    Object slot_group_qm, subblocks, block_1, sub_class_bit_vector;
    Object constant_queue, head, queue_element, next_queue_element, subblock;
    Object first_subblock_qm, second_subblock_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(89,16);
    workspace_qm = get_workspace_if_any(superblock);
    next_item = Nil;
    perform_any_deferred_icon_set_up(superblock);
    perform_any_deferred_icon_set_up(block);
    if (workspace_qm) {
	note_change_to_workspace_geometry(workspace_qm);
	temp = 
		FIXNUM_ADD1(get_lookup_slot_value_given_default(workspace_qm,
		Qnumber_of_blocks_on_workspace,FIX((SI_Long)0L)));
	set_non_savable_lookup_slot_value(workspace_qm,
		Qnumber_of_blocks_on_workspace,temp);
	update_spacial_index(workspace_qm,block,Qg2_add);
	if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		    (SI_Long)1024L)) {
	    temp = FIXNUM_ADD1(ISVREF(workspace_qm,(SI_Long)20L));
	    ISVREF(workspace_qm,(SI_Long)20L) = temp;
	}
    }
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    gensymed_symbol_1 = superblock;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)5L)) = gensymed_symbol_1;
    }
    temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1024L);
    if (temp_1);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	temp_1 =  !TRUEP(subblocks);
	if (temp_1);
	else
	    temp_1 =  !TRUEP(constant_queue_next(ISVREF(subblocks,
		    (SI_Long)2L),subblocks));
    }
    if (temp_1);
    else {
	block_1 = first_subblock(superblock);
	temp_1 =  !((SI_Long)0L != (IFIX(ISVREF(block_1,(SI_Long)4L)) & 
		(SI_Long)1024L));
    }
    if (temp_1) {
	if (G2_has_v5_mode_windows_p && workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		    (SI_Long)19L);
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    next_item = EQ(workspace_qm,superblock) ? 
		    get_topmost_child_of_block(first_subblock(superblock)) 
		    : get_topmost_child_of_block(superblock);
	    if (next_item && loose_end_p_function(next_item)) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		next_item = 
			find_next_non_loose_end_in_queue(gensymed_symbol,Nil);
	    }
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superblock;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = make_empty_constant_queue();
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
		temp = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    }
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	constant_queue_push_left(gensymed_symbol,block);
	if (G2_has_v5_mode_windows_p && workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		    (SI_Long)19L);
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    send_ws_representations_item_insert_as_subblock(block,
		    superblock,next_item);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(superblock,Qsubblocks);
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	constant_queue = gensymed_symbol;
	head = ISVREF(constant_queue,(SI_Long)2L);
	queue_element = constant_queue_next(head,constant_queue);
	next_queue_element = Nil;
	subblock = Nil;
      next_loop:
	if ( !TRUEP(queue_element))
	    goto end_loop;
	next_queue_element = constant_queue_next(queue_element,constant_queue);
	subblock = next_queue_element ? ISVREF(next_queue_element,
		(SI_Long)4L) : Nil;
	if ( !TRUEP(next_queue_element)) {
	    constant_queue_insert_after(constant_queue,queue_element,block);
	    if (G2_has_v5_mode_windows_p && workspace_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		send_ws_representations_item_insert_as_subblock(block,
			superblock,Qbottom);
	    goto end_1;
	}
	if ( !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)4L)) & 
		(SI_Long)1024L))) {
	    if (G2_has_v5_mode_windows_p && workspace_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		next_item = EQ(workspace_qm,superblock) ? 
			get_topmost_child_of_block(subblock) : 
			get_topmost_child_of_block(superblock);
	    if (next_item && loose_end_p_function(next_item))
		next_item = 
			find_next_non_loose_end_in_queue(constant_queue,
			next_queue_element);
	    constant_queue_insert_after(constant_queue,queue_element,block);
	    if (G2_has_v5_mode_windows_p && workspace_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		send_ws_representations_item_insert_as_subblock(block,
			superblock,next_item);
	    goto end_1;
	}
	queue_element = next_queue_element;
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (workspace_qm) {
	first_subblock_qm = first_subblock(workspace_qm);
	second_subblock_qm = second_subblock(workspace_qm);
	temp_1 =  !EQ(block,first_subblock_qm);
	if (temp_1);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    subblocks = gensymed_symbol;
	    temp_1 = subblocks ?  ! 
		    !TRUEP(constant_queue_next(ISVREF(subblocks,
		    (SI_Long)2L),subblocks)) : TRUEP(Qnil);
	}
	if (temp_1);
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    temp_1 = TRUEP(gensymed_symbol);
	}
	if (temp_1)
	    invalidate_layer_positions(workspace_qm);
	else if ( !TRUEP(second_subblock_qm)) {
	    ensure_layer_positions(workspace_qm);
	    set_non_savable_lookup_slot_value(block,
		    Qlayer_position_of_block,FIX((SI_Long)0L));
	}
	else {
	    ensure_layer_positions(workspace_qm);
	    set_non_savable_lookup_slot_value(block,
		    Qlayer_position_of_block,
		    FIXNUM_ADD1(get_lookup_slot_value_given_default(second_subblock_qm,
		    Qlayer_position_of_block,FIX((SI_Long)0L))));
	}
    }
    update_block_is_transformed_if_necessary(block,superblock);
    add_as_inferior_block(block,superblock);
    update_new_subblock_activation_and_propagate(block,superblock);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),
		(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	update_new_subblock_connections_activation_and_propagate(block,
		superblock);
    install_superblock_in_model_if_appropriate(block,superblock);
    handle_connection_post_addition_or_removal_as_subblock(block,Nil);
    return VALUES_1(block);
}

/* COMPUTE-WORKSPACE-CACHES-AFTER-READING */
Object compute_workspace_caches_after_reading(workspace)
    Object workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;
    SI_Long nblocks, nopaque;

    x_note_fn_call(89,17);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    nblocks = (SI_Long)0L;
    nopaque = (SI_Long)0L;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    nblocks = nblocks + (SI_Long)1L;
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1024L))
	nopaque = nopaque + (SI_Long)1L;
    goto next_loop;
  end_loop:
    set_non_savable_lookup_slot_value(workspace,
	    Qnumber_of_blocks_on_workspace,FIX(nblocks));
    ISVREF(workspace,(SI_Long)20L) = FIX(nopaque);
    return VALUES_1(Qnil);
}

/* UPDATE-NEW-SUBBLOCK-ACTIVATION-AND-PROPAGATE */
Object update_new_subblock_activation_and_propagate(block,superblock)
    Object block, superblock;
{
    Object gensymed_symbol, gensymed_symbol_1, temp_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(89,18);
    if ((SI_Long)0L != (IFIX(ISVREF(superblock,(SI_Long)5L)) & (SI_Long)1L)) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = block;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else {
	temp = (SI_Long)0L != (IFIX(ISVREF(superblock,(SI_Long)4L)) & 
		(SI_Long)8192L);
	if (temp);
	else {
	    temp_1 = ISVREF(superblock,(SI_Long)8L);
	    temp = TRUEP(CAR(temp_1));
	}
	if (temp);
	else
	    temp = (SI_Long)0L != (IFIX(ISVREF(superblock,(SI_Long)5L)) & 
		    (SI_Long)256L);
	if (temp) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_1 = block;
	    gensymed_symbol_2 = T;
	    return inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	else {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_1 = block;
	    gensymed_symbol_2 = Nil;
	    return inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
    }
}

/* REMOVE-AS-SUBBLOCK-IF-NECESSARY */
Object remove_as_subblock_if_necessary varargs_1(int, n)
{
    Object block;
    Object dont_remove_as_inferior_qm, gensymed_symbol, superblock_qm;
    Object workspace_qm, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,19);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    dont_remove_as_inferior_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    workspace_qm = Nil;
    if (superblock_qm) {
	remove_as_subblock(block,superblock_qm,dont_remove_as_inferior_qm);
	if (SIMPLE_VECTOR_P(superblock_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superblock_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(superblock_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(superblock_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
	if (temp)
	    remove_block_as_cell_of_table(block,superblock_qm);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
	    workspace_qm = workspace_of_connection_frame(block);
	    temp = TRUEP(workspace_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    maintain_workspace_caches_for_remove_block(workspace_qm,block);
	else {
	    workspace_qm = get_workspace_if_any(block);
	    if (workspace_qm)
		maintain_workspace_caches_for_remove_block(workspace_qm,block);
	}
    }
    return VALUES_1(block);
}

/* REMOVE-AS-SUBBLOCK */
Object remove_as_subblock(block,superblock,dont_remove_as_inferior_qm)
    Object block, superblock, dont_remove_as_inferior_qm;
{
    Object sub_class_bit_vector, workspace_qm, discard_superblock_at_end_p;
    Object gensymed_symbol_3, gensymed_symbol_4, slot_group_qm, temp_1, frame;
    Object sub_vector_qm, function_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, method_index;
    char temp;

    x_note_fn_call(89,20);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    workspace_qm = temp ? superblock : get_workspace_if_any(block);
    if (workspace_qm && EQ(workspace_qm,superblock)) {
	sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Temporary_workspace_class_description,
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
	    discard_superblock_at_end_p = has_only_one_subblock_p(superblock);
	    if (discard_superblock_at_end_p);
	    else
		discard_superblock_at_end_p = 
			temporary_workspace_is_for_virtual_attribute_table_p(workspace_qm);
	}
	else
	    discard_superblock_at_end_p = Nil;
    }
    else
	discard_superblock_at_end_p = Nil;
    handle_connection_post_addition_or_removal_as_subblock(block,T);
    if (workspace_qm) {
	maintain_workspace_caches_for_remove_block(workspace_qm,block);
	note_remove_as_subblock_for_selection(block,superblock);
    }
    if ( !TRUEP(dont_remove_as_inferior_qm))
	remove_as_inferior_block(block,superblock);
    gensymed_symbol_3 = block;
    gensymed_symbol_4 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol_3,(SI_Long)14L);
    gensymed_symbol_4 = Nil;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_4;
    else if ( !EQ(gensymed_symbol_4,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol_3,Qslot_group_for_block_qm);
	temp_1 = make_icon_slot_group_1();
	SVREF(gensymed_symbol_3,FIX((SI_Long)14L)) = temp_1;
	temp_1 = ISVREF(gensymed_symbol_3,(SI_Long)14L);
	SVREF(temp_1,FIX((SI_Long)5L)) = gensymed_symbol_4;
    }
    if (workspace_qm && G2_has_v5_mode_windows_p)
	send_ws_representations_item_remove_as_subblock(block,workspace_qm);
    if (workspace_qm && ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L))
	update_subscriptions_for_remove_item_from_workspace(workspace_qm,
		block);
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
    constant_queue_search_and_delete(gensymed_symbol_3,block);
    if ( !TRUEP(dont_remove_as_inferior_qm)) {
	method_index = (SI_Long)31L;
	frame = block;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_2(function_qm,frame,Nil);
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	if (temp)
	    update_removed_subblock_connections_activation_and_propagate(block);
    }
    install_superblock_in_model_if_appropriate(block,superblock);
    if (discard_superblock_at_end_p)
	delete_frame(superblock);
    return VALUES_1(block);
}

/* INSERT-BEFORE-ITEM */
Object insert_before_item(block1,block2,superblock)
    Object block1, block2, superblock;
{
    Object gensymed_symbol, constant_queue, head, queue_element;

    x_note_fn_call(89,21);
    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    constant_queue = gensymed_symbol;
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = constant_queue_next(head,constant_queue);
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    if (EQ(block2,ISVREF(queue_element,(SI_Long)4L))) {
	constant_queue_insert_before(constant_queue,queue_element,block1);
	goto end_loop;
    }
    queue_element = constant_queue_next(queue_element,constant_queue);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qtop;                /* top */

/* PRIMITIVE-INSERT-AS-SUBBLOCK */
Object primitive_insert_as_subblock(block,superblock,position_or_next_item)
    Object block, superblock, position_or_next_item;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, temp;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(89,22);
    if (EQ(position_or_next_item,Qtop)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superblock;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = make_empty_constant_queue();
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
		temp = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    }
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	return constant_queue_push_left(gensymed_symbol,block);
    }
    else if (EQ(position_or_next_item,Qbottom)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superblock;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = make_empty_constant_queue();
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
		temp = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp,FIX((SI_Long)4L)) = gensymed_symbol_1;
	    }
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	return constant_queue_push_right(gensymed_symbol,block);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(position_or_next_item,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	if (temp_1)
	    return insert_before_item(block,position_or_next_item,superblock);
	else
	    return error((SI_Long)1L,"item could not be inserted~%");
    }
}

/* PRIMITIVE-REMOVE-AS-SUBBLOCK */
Object primitive_remove_as_subblock(block,superblock)
    Object block, superblock;
{
    Object gensymed_symbol;

    x_note_fn_call(89,23);
    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    return constant_queue_search_and_delete(gensymed_symbol,block);
}

/* MAINTAIN-WORKSPACE-CACHES-FOR-REMOVE-BLOCK */
Object maintain_workspace_caches_for_remove_block(workspace,block)
    Object workspace, block;
{
    SI_Long temp, svref_new_value;

    x_note_fn_call(89,24);
    note_change_to_workspace_geometry(workspace);
    update_spacial_index(workspace,block,Qremove);
    temp = IFIX(FIXNUM_SUB1(get_lookup_slot_value_given_default(workspace,
	    Qnumber_of_blocks_on_workspace,FIX((SI_Long)0L))));
    set_non_savable_lookup_slot_value(workspace,
	    Qnumber_of_blocks_on_workspace,FIX(MAX((SI_Long)0L,temp)));
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1024L)) {
	temp = IFIX(FIXNUM_SUB1(ISVREF(workspace,(SI_Long)20L)));
	svref_new_value = MAX((SI_Long)0L,temp);
	ISVREF(workspace,(SI_Long)20L) = FIX(svref_new_value);
    }
    remove_block_from_drawing_queues(workspace,block);
    return remove_subblocks_and_connections_from_drawing_queues(workspace,
	    block);
}

/* REMOVE-BLOCK-FROM-DRAWING-QUEUES */
Object remove_block_from_drawing_queues(workspace,block)
    Object workspace, block;
{
    Object svref_new_value, old_qm;

    x_note_fn_call(89,25);
    if (ISVREF(block,(SI_Long)11L)) {
	svref_new_value = delete_slot_value_element_1(block,
		ISVREF(workspace,(SI_Long)24L));
	ISVREF(workspace,(SI_Long)24L) = svref_new_value;
	atomic_incff_symval(Qcount_of_pending_workspace_drawing,FIX( - 
		(SI_Long)1L));
	old_qm = ISVREF(block,(SI_Long)11L);
	if (old_qm && CAS_SVREF(block,(SI_Long)11L,old_qm,Nil))
	    reclaim_block_change(old_qm);
    }
    return remove_thing_from_image_plane_drawing_queues(workspace,block);
}

/* REMOVE-THING-FROM-IMAGE-PLANE-DRAWING-QUEUES */
Object remove_thing_from_image_plane_drawing_queues(workspace,
	    block_or_connection)
    Object workspace, block_or_connection;
{
    Object image_plane, ab_loop_list_, schedule, window, list_1, head;
    Object previous_qm, this_1, next, svref_new_value;

    x_note_fn_call(89,26);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
    schedule = Nil;
    window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    schedule = ISVREF(image_plane,(SI_Long)29L);
    window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    if (queue_non_empty_p(schedule)) {
	list_1 = ISVREF(schedule,(SI_Long)1L);
	if (list_1) {
	    head = list_1;
	    previous_qm = Nil;
	    this_1 = list_1;
	    next = Nil;
	  next_loop_1:
	    if ( !TRUEP(this_1))
		goto end_loop_1;
	    next = CDR(this_1);
	    if ( !EQ(block_or_connection,ISVREF(CAR(this_1),(SI_Long)4L)))
		previous_qm = this_1;
	    else if ( !TRUEP(previous_qm)) {
		head = CDR(head);
		reclaim_drawing_task(M_CAR(this_1));
		atomic_incff_svslot(window,FIX((SI_Long)29L),FIX( - 
			(SI_Long)1L));
		reclaim_queue_item_cons_1(this_1);
	    }
	    else {
		M_CDR(previous_qm) = next;
		reclaim_drawing_task(M_CAR(this_1));
		atomic_incff_svslot(window,FIX((SI_Long)29L),FIX( - 
			(SI_Long)1L));
		reclaim_queue_item_cons_1(this_1);
	    }
	    this_1 = next;
	    goto next_loop_1;
	  end_loop_1:
	    goto end_1;
	    head = Qnil;
	  end_1:;
	}
	else
	    head = Nil;
	SVREF(schedule,FIX((SI_Long)1L)) = head;
	svref_new_value = last(ISVREF(schedule,(SI_Long)1L),_);
	SVREF(schedule,FIX((SI_Long)2L)) = svref_new_value;
    }
    svref_new_value = delete_slot_value_element_1(block_or_connection,
	    ISVREF(image_plane,(SI_Long)30L));
    SVREF(image_plane,FIX((SI_Long)30L)) = svref_new_value;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_projecting, Qframe_projecting);

DEFINE_VARIABLE_WITH_SYMBOL(Purpose_of_frame_projecting, Qpurpose_of_frame_projecting);

DEFINE_VARIABLE_WITH_SYMBOL(Control_stack_of_frame_projecting, Qcontrol_stack_of_frame_projecting);

DEFINE_VARIABLE_WITH_SYMBOL(Orientation_of_frame, Qorientation_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Current_slice_size_qm, Qcurrent_slice_size_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Left_edge_of_frame, Qleft_edge_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Top_edge_of_frame, Qtop_edge_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Right_edge_of_frame, Qright_edge_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Bottom_edge_of_frame, Qbottom_edge_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Remaining_space_for_variable_size_pieces_of_frame, Qremaining_space_for_variable_size_pieces_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Remaining_number_of_size_pieces_of_frame, Qremaining_number_of_size_pieces_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Partition_details_of_current_branch_of_frame, Qpartition_details_of_current_branch_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Mouse_pointer_of_frame, Qmouse_pointer_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Block_of_frame, Qblock_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_transform_of_frame, Qframe_transform_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(New_position_of_horizontal_elevator_of_frame, Qnew_position_of_horizontal_elevator_of_frame);

DEFINE_VARIABLE_WITH_SYMBOL(New_position_of_vertical_elevator_of_frame, Qnew_position_of_vertical_elevator_of_frame);

Object The_type_description_of_workspace_background_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workspace_background_spots, Qchain_of_available_workspace_background_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_background_spot_count, Qworkspace_background_spot_count);

Object Chain_of_available_workspace_background_spots_vector = UNBOUND;

/* WORKSPACE-BACKGROUND-SPOT-STRUCTURE-MEMORY-USAGE */
Object workspace_background_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,27);
    temp = Workspace_background_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSPACE-BACKGROUND-SPOT-COUNT */
Object outstanding_workspace_background_spot_count()
{
    Object def_structure_workspace_background_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,28);
    gensymed_symbol = IFIX(Workspace_background_spot_count);
    def_structure_workspace_background_spot_variable = 
	    Chain_of_available_workspace_background_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_workspace_background_spot_variable))
	goto end_loop;
    def_structure_workspace_background_spot_variable = 
	    ISVREF(def_structure_workspace_background_spot_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WORKSPACE-BACKGROUND-SPOT-1 */
Object reclaim_workspace_background_spot_1(workspace_background_spot)
    Object workspace_background_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,29);
    inline_note_reclaim_cons(workspace_background_spot,Nil);
    structure_being_reclaimed = workspace_background_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(workspace_background_spot,(SI_Long)2L));
      SVREF(workspace_background_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_workspace_background_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(workspace_background_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workspace_background_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workspace_background_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSPACE-BACKGROUND-SPOT */
Object reclaim_structure_for_workspace_background_spot(workspace_background_spot)
    Object workspace_background_spot;
{
    x_note_fn_call(89,30);
    return reclaim_workspace_background_spot_1(workspace_background_spot);
}

static Object Qg2_defstruct_structure_name_workspace_background_spot_g2_struct;  /* g2-defstruct-structure-name::workspace-background-spot-g2-struct */

/* MAKE-PERMANENT-WORKSPACE-BACKGROUND-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_workspace_background_spot_structure_internal()
{
    Object def_structure_workspace_background_spot_variable;
    Object defstruct_g2_workspace_background_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,31);
    def_structure_workspace_background_spot_variable = Nil;
    atomic_incff_symval(Qworkspace_background_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workspace_background_spot_variable = Nil;
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
	defstruct_g2_workspace_background_spot_variable = the_array;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workspace_background_spot_g2_struct;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_workspace_background_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_workspace_background_spot_variable = 
		defstruct_g2_workspace_background_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workspace_background_spot_variable);
}

/* MAKE-WORKSPACE-BACKGROUND-SPOT-1 */
Object make_workspace_background_spot_1()
{
    Object def_structure_workspace_background_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(89,32);
    def_structure_workspace_background_spot_variable = 
	    ISVREF(Chain_of_available_workspace_background_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workspace_background_spot_variable) {
	svref_arg_1 = Chain_of_available_workspace_background_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_workspace_background_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workspace_background_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workspace_background_spot_g2_struct;
    }
    else
	def_structure_workspace_background_spot_variable = 
		make_permanent_workspace_background_spot_structure_internal();
    inline_note_allocate_cons(def_structure_workspace_background_spot_variable,
	    Nil);
    SVREF(def_structure_workspace_background_spot_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_workspace_background_spot_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_workspace_background_spot_variable,
	    FIX((SI_Long)3L)) = T;
    SVREF(def_structure_workspace_background_spot_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_workspace_background_spot_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_workspace_background_spot_variable);
}

/* MAKE-WORKSPACE-BACKGROUND-SPOT-FUNCTION */
Object make_workspace_background_spot_function()
{
    x_note_fn_call(89,33);
    return make_workspace_background_spot_1();
}

Object The_type_description_of_title_bar_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_title_bar_spots, Qchain_of_available_title_bar_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Title_bar_spot_count, Qtitle_bar_spot_count);

Object Chain_of_available_title_bar_spots_vector = UNBOUND;

/* TITLE-BAR-SPOT-STRUCTURE-MEMORY-USAGE */
Object title_bar_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,34);
    temp = Title_bar_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TITLE-BAR-SPOT-COUNT */
Object outstanding_title_bar_spot_count()
{
    Object def_structure_title_bar_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,35);
    gensymed_symbol = IFIX(Title_bar_spot_count);
    def_structure_title_bar_spot_variable = Chain_of_available_title_bar_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_title_bar_spot_variable))
	goto end_loop;
    def_structure_title_bar_spot_variable = 
	    ISVREF(def_structure_title_bar_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TITLE-BAR-SPOT-1 */
Object reclaim_title_bar_spot_1(title_bar_spot)
    Object title_bar_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,36);
    inline_note_reclaim_cons(title_bar_spot,Nil);
    structure_being_reclaimed = title_bar_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(title_bar_spot,(SI_Long)2L));
      SVREF(title_bar_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_title_bar_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(title_bar_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_title_bar_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = title_bar_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TITLE-BAR-SPOT */
Object reclaim_structure_for_title_bar_spot(title_bar_spot)
    Object title_bar_spot;
{
    x_note_fn_call(89,37);
    return reclaim_title_bar_spot_1(title_bar_spot);
}

static Object Qg2_defstruct_structure_name_title_bar_spot_g2_struct;  /* g2-defstruct-structure-name::title-bar-spot-g2-struct */

/* MAKE-PERMANENT-TITLE-BAR-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_title_bar_spot_structure_internal()
{
    Object def_structure_title_bar_spot_variable;
    Object defstruct_g2_title_bar_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,38);
    def_structure_title_bar_spot_variable = Nil;
    atomic_incff_symval(Qtitle_bar_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_title_bar_spot_variable = Nil;
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
	defstruct_g2_title_bar_spot_variable = the_array;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_title_bar_spot_g2_struct;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_title_bar_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_title_bar_spot_variable = 
		defstruct_g2_title_bar_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_title_bar_spot_variable);
}

/* MAKE-TITLE-BAR-SPOT-1 */
Object make_title_bar_spot_1()
{
    Object def_structure_title_bar_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,39);
    def_structure_title_bar_spot_variable = 
	    ISVREF(Chain_of_available_title_bar_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_title_bar_spot_variable) {
	svref_arg_1 = Chain_of_available_title_bar_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_title_bar_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_title_bar_spot_g2_struct;
    }
    else
	def_structure_title_bar_spot_variable = 
		make_permanent_title_bar_spot_structure_internal();
    inline_note_allocate_cons(def_structure_title_bar_spot_variable,Nil);
    SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_title_bar_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_title_bar_spot_variable);
}

/* MAKE-TITLE-BAR-SPOT-FUNCTION */
Object make_title_bar_spot_function()
{
    x_note_fn_call(89,40);
    return make_title_bar_spot_1();
}

DEFINE_VARIABLE_WITH_SYMBOL(Working_on_drawing_workspace, Qworking_on_drawing_workspace);

DEFINE_VARIABLE_WITH_SYMBOL(Currently_working_on_drawing_workspace, Qcurrently_working_on_drawing_workspace);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_with_image_plane_being_refreshed, Qworkstation_with_image_plane_being_refreshed);

static Object Qgraph;              /* graph */

/* SUBBLOCKS-FOR-DRAWING */
Object subblocks_for_drawing(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(89,41);
    if ( !EQ(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L),Qgraph)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	return VALUES_1(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdeferred_draw_block;  /* deferred-draw-block */

static Object Kxor;                /* :xor */

/* DRAW-BLOCK-AND-SUBBLOCKS */
Object draw_block_and_subblocks(block,recurse_to_subblocks_qm)
    Object block, recurse_to_subblocks_qm;
{
    Object compiled_function, block_or_connection, fun, blk, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp, svref_arg_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object current_drawing_transfer_mode, gensymed_symbol, gensymed_symbol_1;
    Object subblocks, ab_queue_form_, ab_next_queue_element_, subblock;
    char temp_1, already_in_synch;
    Declare_special(1);

    x_note_fn_call(89,42);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)1024L)) {
	if (Currently_working_on_drawing_workspace) {
	    compiled_function = SYMBOL_FUNCTION(Qdeferred_draw_block);
	    block_or_connection = block;
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
			slot_value_list_3(SYMBOL_FUNCTION(Qdeferred_draw_block),
			block,copy_frame_serial_number(ISVREF(block,
			(SI_Long)3L)));
		car_1 = slot_value_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)31L);
		svref_new_value = slot_value_cons_1(car_1,cdr_1);
		SVREF(svref_arg_1,FIX((SI_Long)31L)) = svref_new_value;
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
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)5L),(SI_Long)1L);
	      gensymed_symbol_1 = block;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    POP_SPECIAL();
	    if ( !already_in_synch)
		synchronize_transfer_mode();
	}
    }
    else {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)5L),(SI_Long)1L);
	gensymed_symbol_1 = block;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    if (recurse_to_subblocks_qm &&  !EQ(ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)1L),Qgraph)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
		(SI_Long)2L),subblocks))) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_1;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    draw_block_and_subblocks(subblock,recurse_to_subblocks_qm);
	    goto next_loop_1;
	  end_loop_1:;
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	if (gensymed_symbol)
	    return draw_connections_for_block(block);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qframe_transforms_of_block;  /* frame-transforms-of-block */

/* DEFERRED-DRAW-BLOCK */
Object deferred_draw_block(block,reference_frame_serial_number)
    Object block, reference_frame_serial_number;
{
    Object gensymed_symbol, xa, ya, left_edge_of_draw_area;
    Object top_edge_of_draw_area, right_edge_of_draw_area;
    Object bottom_edge_of_draw_area, current_frame_transform_qm;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object enclosing_block, frame_transforms_of_block_qm;
    Object frame_transforms_of_enclosing_block, temp_1, frame_transform, value;
    Object incff_1_arg, temp_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_1, scale, gensymed_symbol_2, unshifted_result;
    SI_Long x_offset, y_offset;
    char temp;
    Declare_special(7);

    x_note_fn_call(89,43);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
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
    if ( !temp) {
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
		      if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) 
			      & (SI_Long)32768L)) {
			  enclosing_block = block;
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
		      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)5L),
			      (SI_Long)1L);
		      gensymed_symbol_3 = block;
		      temp_1 = inline_funcall_1(gensymed_symbol,
			      gensymed_symbol_3);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qdrawing;            /* drawing */

static Object Qdraw_block_within_frame_1;  /* draw-block-within-frame-1 */

static Object Qdraw_block_within_frame_2;  /* draw-block-within-frame-2 */

/* DRAW-BLOCK-POSSIBLY-WITH-FRAME */
Object draw_block_possibly_with_frame(block,recurse_to_subblocks_qm)
    Object block, recurse_to_subblocks_qm;
{
    Object frame_transforms_of_block, left_edge_of_draw_area;
    Object top_edge_of_draw_area, right_edge_of_draw_area;
    Object bottom_edge_of_draw_area, current_frame_transform_qm;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object enclosing_block, frame_transforms_of_block_qm;
    Object frame_transforms_of_enclosing_block, gensymed_symbol, temp;
    Object frame_transform, value, incff_1_arg, temp_1;
    Object frame_transform_of_frame, block_of_frame;
    Object frame_description_reference, left_edge_of_frame, top_edge_of_frame;
    Object right_edge_of_frame, bottom_edge_of_frame;
    SI_Long gensymed_symbol_1, scale, gensymed_symbol_2, unshifted_result;
    SI_Long x_offset, y_offset;
    Declare_special(7);
    Object result;

    x_note_fn_call(89,44);
    frame_transforms_of_block = Nil;
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)32768L)))
	return draw_block_and_subblocks(block,recurse_to_subblocks_qm);
    else {
	frame_transforms_of_block = 
		get_lookup_slot_value_given_default(block,
		Qframe_transforms_of_block,Nil);
	if ( !TRUEP(frame_transforms_of_block)) {
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
			  if ((SI_Long)0L != (IFIX(ISVREF(block,
				  (SI_Long)5L)) & (SI_Long)32768L)) {
			      enclosing_block = block;
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
			      temp = assq_function(Current_image_plane,
				      frame_transforms_of_enclosing_block);
			      frame_transform = CDR(temp);
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
				      unshifted_result = scale * 
					      IFIX(value) + (SI_Long)2048L;
				      gensymed_symbol_2 = unshifted_result 
					      >>  -  - (SI_Long)12L;
				  }
				  else
				      gensymed_symbol_2 = 
					      IFIX(scalef_function(FIX(scale),
					      value));
				  x_offset = gensymed_symbol_1 + 
					  gensymed_symbol_2;
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
					  incff_1_arg = 
						  FIX(unshifted_result >>  
						  -  - (SI_Long)12L);
				      }
				      else
					  incff_1_arg = 
						  scalef_function(Current_image_x_scale,
						  FIX(x_offset));
				      temp_1 = 
					      FIXNUM_ADD(Current_x_origin_of_drawing,
					      incff_1_arg);
				      Current_x_origin_of_drawing = temp_1;
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
				      unshifted_result = scale * 
					      IFIX(value) + (SI_Long)2048L;
				      gensymed_symbol_2 = unshifted_result 
					      >>  -  - (SI_Long)12L;
				  }
				  else
				      gensymed_symbol_2 = 
					      IFIX(scalef_function(FIX(scale),
					      value));
				  y_offset = gensymed_symbol_1 + 
					  gensymed_symbol_2;
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
					  incff_1_arg = 
						  FIX(unshifted_result >>  
						  -  - (SI_Long)12L);
				      }
				      else
					  incff_1_arg = 
						  scalef_function(Current_image_y_scale,
						  FIX(y_offset));
				      temp_1 = 
					      FIXNUM_ADD(Current_y_origin_of_drawing,
					      incff_1_arg);
				      Current_y_origin_of_drawing = temp_1;
				  }
			      }
			  }
			  result = draw_block_and_subblocks(block,
				  recurse_to_subblocks_qm);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else {
	    temp = assq_function(Current_image_plane,
		    frame_transforms_of_block);
	    frame_transform_of_frame = CDR(temp);
	    PUSH_SPECIAL_WITH_SYMBOL(Frame_transform_of_frame,Qframe_transform_of_frame,frame_transform_of_frame,
		    5);
	      block_of_frame = block;
	      PUSH_SPECIAL_WITH_SYMBOL(Block_of_frame,Qblock_of_frame,block_of_frame,
		      4);
		frame_description_reference = 
			ISVREF(Frame_transform_of_frame,(SI_Long)5L);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = 
			IFIX(ISVREF(frame_description_reference,(SI_Long)4L));
		left_edge_of_frame = FIX(gensymed_symbol_1 - 
			gensymed_symbol_2);
		PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
			3);
		  gensymed_symbol = ISVREF(block,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)1L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = 
			  IFIX(ISVREF(frame_description_reference,
			  (SI_Long)5L));
		  top_edge_of_frame = FIX(gensymed_symbol_1 - 
			  gensymed_symbol_2);
		  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
			  2);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = 
			    IFIX(ISVREF(frame_description_reference,
			    (SI_Long)6L));
		    right_edge_of_frame = FIX(gensymed_symbol_1 + 
			    gensymed_symbol_2);
		    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
			    1);
		      gensymed_symbol = ISVREF(block,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)3L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = 
			      IFIX(ISVREF(frame_description_reference,
			      (SI_Long)7L));
		      bottom_edge_of_frame = FIX(gensymed_symbol_1 + 
			      gensymed_symbol_2);
		      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
			      0);
			result = project_frame(Qdrawing,
				ISVREF(frame_description_reference,
				(SI_Long)2L),Left_edge_of_frame,
				Top_edge_of_frame,Right_edge_of_frame,
				Bottom_edge_of_frame,
				recurse_to_subblocks_qm ? 
				SYMBOL_FUNCTION(Qdraw_block_within_frame_1) 
				: SYMBOL_FUNCTION(Qdraw_block_within_frame_2));
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
}

/* DRAW-BLOCK-WITHIN-FRAME-1 */
Object draw_block_within_frame_1()
{
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_frame_transform_qm, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, value, incff_1_arg, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result, scale;
    SI_Long x_offset, y_offset;
    Declare_special(7);
    Object result;

    x_note_fn_call(89,45);
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
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Left_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,
			Left_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Left_edge_of_draw_area);
	    Left_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Top_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,
			Top_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Top_edge_of_draw_area);
	    Top_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Right_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,
			Right_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Right_edge_of_draw_area);
	    Right_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Bottom_edge_of_frame) && 
		    FIXNUM_LT(Bottom_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Bottom_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,
			Bottom_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_draw_area);
	    Bottom_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    if (FIXNUM_LT(Left_edge_of_draw_area,Right_edge_of_draw_area) 
		    && FIXNUM_LT(Top_edge_of_draw_area,
		    Bottom_edge_of_draw_area)) {
		current_frame_transform_qm = Current_frame_transform_qm;
		current_x_origin_of_drawing = Current_x_origin_of_drawing;
		current_y_origin_of_drawing = Current_y_origin_of_drawing;
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
			    0);
		      if ( !EQ(Current_frame_transform_qm,
			      Frame_transform_of_frame)) {
			  Current_frame_transform_qm = 
				  Frame_transform_of_frame;
			  gensymed_symbol = 
				  IFIX(ISVREF(Frame_transform_of_frame,
				  (SI_Long)10L));
			  scale = (SI_Long)4096L;
			  value = ISVREF(Frame_transform_of_frame,(SI_Long)6L);
			  if (scale == (SI_Long)4096L)
			      gensymed_symbol_1 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale && scale < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_1 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_1 = 
				      IFIX(scalef_function(FIX(scale),value));
			  x_offset = gensymed_symbol + gensymed_symbol_1;
			  if ( !((SI_Long)0L == x_offset)) {
			      if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(x_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < x_offset && x_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_x_scale) * 
					  x_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_x_scale,
					  FIX(x_offset));
			      temp = 
				      FIXNUM_ADD(Current_x_origin_of_drawing,
				      incff_1_arg);
			      Current_x_origin_of_drawing = temp;
			  }
			  gensymed_symbol = 
				  IFIX(ISVREF(Frame_transform_of_frame,
				  (SI_Long)11L));
			  scale = (SI_Long)4096L;
			  value = ISVREF(Frame_transform_of_frame,(SI_Long)7L);
			  if (scale == (SI_Long)4096L)
			      gensymed_symbol_1 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale && scale < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_1 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_1 = 
				      IFIX(scalef_function(FIX(scale),value));
			  y_offset = gensymed_symbol + gensymed_symbol_1;
			  if ( !((SI_Long)0L == y_offset)) {
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(y_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < y_offset && y_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_y_scale) * 
					  y_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_y_scale,
					  FIX(y_offset));
			      temp = 
				      FIXNUM_ADD(Current_y_origin_of_drawing,
				      incff_1_arg);
			      Current_y_origin_of_drawing = temp;
			  }
		      }
		      result = draw_block_and_subblocks(Block_of_frame,T);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DRAW-BLOCK-WITHIN-FRAME-2 */
Object draw_block_within_frame_2()
{
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_frame_transform_qm, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, value, incff_1_arg, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result, scale;
    SI_Long x_offset, y_offset;
    Declare_special(7);
    Object result;

    x_note_fn_call(89,46);
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
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Left_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,
			Left_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Left_edge_of_draw_area);
	    Left_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Top_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,
			Top_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Top_edge_of_draw_area);
	    Top_edge_of_draw_area = FIX(MAX(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			Right_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_x_scale,
			Right_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Right_edge_of_draw_area);
	    Right_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Bottom_edge_of_frame) && 
		    FIXNUM_LT(Bottom_edge_of_frame,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Bottom_edge_of_frame)) + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = 
			IFIX(scalef_function(Current_image_y_scale,
			Bottom_edge_of_frame));
	    gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_draw_area);
	    Bottom_edge_of_draw_area = FIX(MIN(gensymed_symbol,
		    gensymed_symbol_1));
	    if (FIXNUM_LT(Left_edge_of_draw_area,Right_edge_of_draw_area) 
		    && FIXNUM_LT(Top_edge_of_draw_area,
		    Bottom_edge_of_draw_area)) {
		current_frame_transform_qm = Current_frame_transform_qm;
		current_x_origin_of_drawing = Current_x_origin_of_drawing;
		current_y_origin_of_drawing = Current_y_origin_of_drawing;
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
			    0);
		      if ( !EQ(Current_frame_transform_qm,
			      Frame_transform_of_frame)) {
			  Current_frame_transform_qm = 
				  Frame_transform_of_frame;
			  gensymed_symbol = 
				  IFIX(ISVREF(Frame_transform_of_frame,
				  (SI_Long)10L));
			  scale = (SI_Long)4096L;
			  value = ISVREF(Frame_transform_of_frame,(SI_Long)6L);
			  if (scale == (SI_Long)4096L)
			      gensymed_symbol_1 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale && scale < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_1 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_1 = 
				      IFIX(scalef_function(FIX(scale),value));
			  x_offset = gensymed_symbol + gensymed_symbol_1;
			  if ( !((SI_Long)0L == x_offset)) {
			      if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(x_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < x_offset && x_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_x_scale) * 
					  x_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_x_scale,
					  FIX(x_offset));
			      temp = 
				      FIXNUM_ADD(Current_x_origin_of_drawing,
				      incff_1_arg);
			      Current_x_origin_of_drawing = temp;
			  }
			  gensymed_symbol = 
				  IFIX(ISVREF(Frame_transform_of_frame,
				  (SI_Long)11L));
			  scale = (SI_Long)4096L;
			  value = ISVREF(Frame_transform_of_frame,(SI_Long)7L);
			  if (scale == (SI_Long)4096L)
			      gensymed_symbol_1 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale && scale < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_1 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_1 = 
				      IFIX(scalef_function(FIX(scale),value));
			  y_offset = gensymed_symbol + gensymed_symbol_1;
			  if ( !((SI_Long)0L == y_offset)) {
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(y_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < y_offset && y_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_y_scale) * 
					  y_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_y_scale,
					  FIX(y_offset));
			      temp = 
				      FIXNUM_ADD(Current_y_origin_of_drawing,
				      incff_1_arg);
			      Current_y_origin_of_drawing = temp;
			  }
		      }
		      result = draw_block_and_subblocks(Block_of_frame,Nil);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qabove;              /* above */

/* DRAW-BLOCK */
Object draw_block(block)
    Object block;
{
    Object compiled_function, block_or_connection, fun, blk, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp, svref_arg_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object current_drawing_transfer_mode, gensymed_symbol, gensymed_symbol_1;
    Object subblocks, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, this_block, superblock_qm, workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1, already_in_synch;
    Declare_special(1);

    x_note_fn_call(89,47);
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L))) {
	if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		    (SI_Long)1024L)) {
	    if (Currently_working_on_drawing_workspace) {
		compiled_function = SYMBOL_FUNCTION(Qdeferred_draw_block);
		block_or_connection = block;
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
			    slot_value_list_3(SYMBOL_FUNCTION(Qdeferred_draw_block),
			    block,copy_frame_serial_number(ISVREF(block,
			    (SI_Long)3L)));
		    car_1 = slot_value_push_modify_macro_arg;
		    cdr_1 = ISVREF(svref_arg_1,(SI_Long)31L);
		    svref_new_value = slot_value_cons_1(car_1,cdr_1);
		    SVREF(svref_arg_1,FIX((SI_Long)31L)) = svref_new_value;
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
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)5L),(SI_Long)1L);
		  gensymed_symbol_1 = block;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		POP_SPECIAL();
		if ( !already_in_synch)
		    synchronize_transfer_mode();
	    }
	}
	else {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)5L),(SI_Long)1L);
	    gensymed_symbol_1 = block;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
	if (T &&  !EQ(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L),Qgraph)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    subblocks = gensymed_symbol;
	    if (subblocks &&  ! 
		    !TRUEP(constant_queue_next(ISVREF(subblocks,
		    (SI_Long)2L),subblocks))) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		ab_queue_form_ = gensymed_symbol;
		ab_next_queue_element_ = Nil;
		subblock = Nil;
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
		draw_block_and_subblocks(subblock,T);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    if (gensymed_symbol)
		draw_connections_for_block(block);
	}
    }
    else
	draw_block_possibly_with_frame(block,T);
    temp_1 = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)1024L);
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
    if (temp_1);
    else
	temp_1 = EQ(Current_drawing_transfer_mode,Kxor) ?  !((SI_Long)0L 
		!= (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1024L)) : 
		TRUEP(Qnil);
    if ( !temp_1) {
	this_block = block;
	superblock_qm = Nil;
      next_loop_2:
	gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	superblock_qm = gensymed_symbol;
	if ( !TRUEP(superblock_qm)) {
	    sub_class_bit_vector = ISVREF(ISVREF(this_block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    workspace_qm = temp_1 ? this_block : Nil;
	    goto end_2;
	}
	this_block = superblock_qm;
	goto next_loop_2;
      end_loop_2:
	workspace_qm = Qnil;
      end_2:;
	if (workspace_qm)
	    return draw_overlapping_blocks(workspace_qm,block,Qabove,Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SCROLL-BLOCK-FOR-BLOCK */
Object scroll_block_for_block(block,image_plane,amount_of_step,
	    direction_of_step)
    Object block, image_plane, amount_of_step, direction_of_step;
{
    x_note_fn_call(89,48);
    return VALUES_1(Nil);
}

static Object Qline;               /* line */

static Object Qup;                 /* up */

static Object Qdown;               /* down */

static Object Qleft;               /* left */

static Object Qright;              /* right */

/* SCROLL-BLOCK-FOR-WORKSPACE */
Object scroll_block_for_workspace(workspace,image_plane,amount_of_step,
	    direction_of_step)
    Object workspace, image_plane, amount_of_step, direction_of_step;
{
    Object x_percent, y_percent;
    SI_Long percent;

    x_note_fn_call(89,49);
    percent = EQ(Qline,amount_of_step) ? (SI_Long)10L : (SI_Long)100L;
    if (EQ(direction_of_step,Qup) || EQ(direction_of_step,Qdown))
	x_percent = FIX((SI_Long)0L);
    else if (EQ(direction_of_step,Qleft))
	x_percent = FIX(percent);
    else
	x_percent = negate(FIX(percent));
    if (EQ(direction_of_step,Qleft) || EQ(direction_of_step,Qright))
	y_percent = FIX((SI_Long)0L);
    else if (EQ(direction_of_step,Qup))
	y_percent = FIX(percent);
    else
	y_percent = negate(FIX(percent));
    return scroll_content_area_of_image_plane(image_plane,
	    l_round(FIXNUM_TIMES(x_percent,FIXNUM_MINUS(ISVREF(image_plane,
	    (SI_Long)34L),ISVREF(image_plane,(SI_Long)32L))),
	    FIX((SI_Long)100L)),l_round(FIXNUM_TIMES(y_percent,
	    FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)35L),
	    ISVREF(image_plane,(SI_Long)33L))),FIX((SI_Long)100L)));
}

static Object Qscroll_entire_block_contents;  /* scroll-entire-block-contents */

/* SCROLL-FRAME-TRANSFORM */
Object scroll_frame_transform(frame_transform,workspace_dx,workspace_dy)
    Object frame_transform, workspace_dx, workspace_dy;
{
    Object block, incff_1_arg, svref_new_value, temp, temp_1, gensymed_symbol;
    Object temp_2, temp_3, temp_4;

    x_note_fn_call(89,50);
    block = ISVREF(frame_transform,(SI_Long)4L);
    incff_1_arg = workspace_dx;
    svref_new_value = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)6L),
	    incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)6L)) = svref_new_value;
    incff_1_arg = workspace_dy;
    svref_new_value = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)7L),
	    incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)7L)) = svref_new_value;
    incff_1_arg = workspace_dx;
    svref_new_value = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)8L),
	    incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)8L)) = svref_new_value;
    incff_1_arg = workspace_dy;
    svref_new_value = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)9L),
	    incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)9L)) = svref_new_value;
    temp = get_workspace_if_any(block);
    temp_1 = get_workspace_if_any(block);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_3 = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_4 = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return map_drawing_over_image_planes(11,temp,temp_1,temp_2,temp_3,
	    temp_4,gensymed_symbol,Nil,Qscroll_entire_block_contents,block,
	    workspace_dx,workspace_dy);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

/* SCROLL-ENTIRE-BLOCK-CONTENTS */
Object scroll_entire_block_contents(block,delta_x_in_workspace,
	    delta_y_in_workspace)
    Object block, delta_x_in_workspace, delta_y_in_workspace;
{
    Object scale, gensymed_symbol_1, value, src_region, left_edge_of_block;
    Object top_edge_of_block, old_x_in_window, old_y_in_window;
    Object new_x_in_window, new_y_in_window, temp, frame_transform;
    Object decff_1_arg, temp_1, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_frame_transform_qm, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, enclosing_block;
    Object frame_transforms_of_block_qm, frame_transforms_of_enclosing_block;
    Object frame_transform_1, incff_1_arg;
    SI_Long gensymed_symbol, gensymed_symbol_2, unshifted_result, src_left;
    SI_Long src_top, src_right, src_bottom, scale_1, x_offset, y_offset;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(89,51);
    SAVE_STACK();
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    src_left = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    src_top = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    src_right = gensymed_symbol + gensymed_symbol_2;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    value = gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    src_bottom = gensymed_symbol + gensymed_symbol_2;
    src_region = Qunbound_in_protected_let;
    src_region = make_region_from_rectangle(FIX(src_left),FIX(src_top),
	    FIX(src_right),FIX(src_bottom));
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge_of_block = gensymed_symbol_1;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge_of_block = gensymed_symbol_1;
    old_x_in_window = Nil;
    old_y_in_window = Nil;
    new_x_in_window = Nil;
    new_y_in_window = Nil;
    temp = Current_image_plane;
    temp = assq_function(temp,get_lookup_slot_value_given_default(block,
	    Qframe_transforms_of_block,Nil));
    frame_transform = CDR(temp);
    decff_1_arg = delta_x_in_workspace;
    temp_1 = FIXNUM_MINUS(ISVREF(frame_transform,(SI_Long)6L),decff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)6L)) = temp_1;
    decff_1_arg = delta_y_in_workspace;
    temp_1 = FIXNUM_MINUS(ISVREF(frame_transform,(SI_Long)7L),decff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)7L)) = temp_1;
    decff_1_arg = delta_x_in_workspace;
    temp_1 = FIXNUM_MINUS(ISVREF(frame_transform,(SI_Long)8L),decff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)8L)) = temp_1;
    decff_1_arg = delta_y_in_workspace;
    temp_1 = FIXNUM_MINUS(ISVREF(frame_transform,(SI_Long)9L),decff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)9L)) = temp_1;
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
		  if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			  (SI_Long)32768L)) {
		      enclosing_block = block;
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
		      gensymed_symbol_1 = 
			      ACCESS_ONCE(ISVREF(enclosing_block,
			      (SI_Long)14L));
		      gensymed_symbol_1 = gensymed_symbol_1 ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			      (SI_Long)5L)) : Nil;
		      enclosing_block = gensymed_symbol_1;
		      goto next_loop;
		    end_loop:
		      frame_transforms_of_enclosing_block = Qnil;
		    end_1:;
		      temp = assq_function(Current_image_plane,
			      frame_transforms_of_enclosing_block);
		      frame_transform_1 = CDR(temp);
		      if ( !EQ(Current_frame_transform_qm,frame_transform_1)) {
			  nest_draw_area_for_frame_1(frame_transform_1);
			  Current_frame_transform_qm = frame_transform_1;
			  gensymed_symbol = IFIX(ISVREF(frame_transform_1,
				  (SI_Long)10L));
			  scale_1 = (SI_Long)4096L;
			  value = ISVREF(frame_transform_1,(SI_Long)6L);
			  if (scale_1 == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale_1 && scale_1 < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale_1 * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(FIX(scale_1),
				      value));
			  x_offset = gensymed_symbol + gensymed_symbol_2;
			  if ( !((SI_Long)0L == x_offset)) {
			      if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(x_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < x_offset && x_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_x_scale) * 
					  x_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_x_scale,
					  FIX(x_offset));
			      temp_1 = 
				      FIXNUM_ADD(Current_x_origin_of_drawing,
				      incff_1_arg);
			      Current_x_origin_of_drawing = temp_1;
			  }
			  gensymed_symbol = IFIX(ISVREF(frame_transform_1,
				  (SI_Long)11L));
			  scale_1 = (SI_Long)4096L;
			  value = ISVREF(frame_transform_1,(SI_Long)7L);
			  if (scale_1 == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale_1 && scale_1 < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale_1 * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(FIX(scale_1),
				      value));
			  y_offset = gensymed_symbol + gensymed_symbol_2;
			  if ( !((SI_Long)0L == y_offset)) {
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(y_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < y_offset && y_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_y_scale) * 
					  y_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_y_scale,
					  FIX(y_offset));
			      temp_1 = 
				      FIXNUM_ADD(Current_y_origin_of_drawing,
				      incff_1_arg);
			      Current_y_origin_of_drawing = temp_1;
			  }
		      }
		  }
		  gensymed_symbol = IFIX(Current_x_origin_of_drawing);
		  if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		      gensymed_symbol_2 = IFIX(left_edge_of_block);
		  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  Current_image_x_scale) && 
			  FIXNUM_LT(Current_image_x_scale,
			  Isqrt_of_most_positive_fixnum) && 
			  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  left_edge_of_block) && 
			  FIXNUM_LT(left_edge_of_block,
			  Isqrt_of_most_positive_fixnum)) {
		      unshifted_result = 
			      IFIX(FIXNUM_TIMES(Current_image_x_scale,
			      left_edge_of_block)) + (SI_Long)2048L;
		      gensymed_symbol_2 = unshifted_result >>  -  - 
			      (SI_Long)12L;
		  }
		  else
		      gensymed_symbol_2 = 
			      IFIX(scalef_function(Current_image_x_scale,
			      left_edge_of_block));
		  old_x_in_window = FIX(gensymed_symbol + gensymed_symbol_2);
		  gensymed_symbol = IFIX(Current_y_origin_of_drawing);
		  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		      gensymed_symbol_2 = IFIX(top_edge_of_block);
		  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  Current_image_y_scale) && 
			  FIXNUM_LT(Current_image_y_scale,
			  Isqrt_of_most_positive_fixnum) && 
			  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  top_edge_of_block) && 
			  FIXNUM_LT(top_edge_of_block,
			  Isqrt_of_most_positive_fixnum)) {
		      unshifted_result = 
			      IFIX(FIXNUM_TIMES(Current_image_y_scale,
			      top_edge_of_block)) + (SI_Long)2048L;
		      gensymed_symbol_2 = unshifted_result >>  -  - 
			      (SI_Long)12L;
		  }
		  else
		      gensymed_symbol_2 = 
			      IFIX(scalef_function(Current_image_y_scale,
			      top_edge_of_block));
		  old_y_in_window = FIX(gensymed_symbol + gensymed_symbol_2);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    incff_1_arg = delta_x_in_workspace;
    temp_1 = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)6L),incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)6L)) = temp_1;
    incff_1_arg = delta_y_in_workspace;
    temp_1 = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)7L),incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)7L)) = temp_1;
    incff_1_arg = delta_x_in_workspace;
    temp_1 = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)8L),incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)8L)) = temp_1;
    incff_1_arg = delta_y_in_workspace;
    temp_1 = FIXNUM_ADD(ISVREF(frame_transform,(SI_Long)9L),incff_1_arg);
    SVREF(frame_transform,FIX((SI_Long)9L)) = temp_1;
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
		  if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			  (SI_Long)32768L)) {
		      enclosing_block = block;
		      frame_transforms_of_block_qm = Nil;
		    next_loop_1:
		      frame_transforms_of_block_qm = 
			      get_lookup_slot_value_given_default(enclosing_block,
			      Qframe_transforms_of_block,Nil);
		      if (frame_transforms_of_block_qm) {
			  frame_transforms_of_enclosing_block = 
				  frame_transforms_of_block_qm;
			  goto end_2;
		      }
		      gensymed_symbol_1 = 
			      ACCESS_ONCE(ISVREF(enclosing_block,
			      (SI_Long)14L));
		      gensymed_symbol_1 = gensymed_symbol_1 ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol_1,
			      (SI_Long)5L)) : Nil;
		      enclosing_block = gensymed_symbol_1;
		      goto next_loop_1;
		    end_loop_1:
		      frame_transforms_of_enclosing_block = Qnil;
		    end_2:;
		      temp = assq_function(Current_image_plane,
			      frame_transforms_of_enclosing_block);
		      frame_transform = CDR(temp);
		      if ( !EQ(Current_frame_transform_qm,frame_transform)) {
			  nest_draw_area_for_frame_1(frame_transform);
			  Current_frame_transform_qm = frame_transform;
			  gensymed_symbol = IFIX(ISVREF(frame_transform,
				  (SI_Long)10L));
			  scale_1 = (SI_Long)4096L;
			  value = ISVREF(frame_transform,(SI_Long)6L);
			  if (scale_1 == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale_1 && scale_1 < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale_1 * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(FIX(scale_1),
				      value));
			  x_offset = gensymed_symbol + gensymed_symbol_2;
			  if ( !((SI_Long)0L == x_offset)) {
			      if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(x_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < x_offset && x_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_x_scale) * 
					  x_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_x_scale,
					  FIX(x_offset));
			      temp_1 = 
				      FIXNUM_ADD(Current_x_origin_of_drawing,
				      incff_1_arg);
			      Current_x_origin_of_drawing = temp_1;
			  }
			  gensymed_symbol = IFIX(ISVREF(frame_transform,
				  (SI_Long)11L));
			  scale_1 = (SI_Long)4096L;
			  value = ISVREF(frame_transform,(SI_Long)7L);
			  if (scale_1 == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(value);
			  else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				  < scale_1 && scale_1 < 
				  IFIX(Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = scale_1 * IFIX(value) + 
				      (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(FIX(scale_1),
				      value));
			  y_offset = gensymed_symbol + gensymed_symbol_2;
			  if ( !((SI_Long)0L == y_offset)) {
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  incff_1_arg = FIX(y_offset);
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < y_offset && y_offset < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_y_scale) * 
					  y_offset + (SI_Long)2048L;
				  incff_1_arg = FIX(unshifted_result >>  - 
					   - (SI_Long)12L);
			      }
			      else
				  incff_1_arg = 
					  scalef_function(Current_image_y_scale,
					  FIX(y_offset));
			      temp_1 = 
				      FIXNUM_ADD(Current_y_origin_of_drawing,
				      incff_1_arg);
			      Current_y_origin_of_drawing = temp_1;
			  }
		      }
		  }
		  gensymed_symbol = IFIX(Current_x_origin_of_drawing);
		  if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		      gensymed_symbol_2 = IFIX(left_edge_of_block);
		  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  Current_image_x_scale) && 
			  FIXNUM_LT(Current_image_x_scale,
			  Isqrt_of_most_positive_fixnum) && 
			  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  left_edge_of_block) && 
			  FIXNUM_LT(left_edge_of_block,
			  Isqrt_of_most_positive_fixnum)) {
		      unshifted_result = 
			      IFIX(FIXNUM_TIMES(Current_image_x_scale,
			      left_edge_of_block)) + (SI_Long)2048L;
		      gensymed_symbol_2 = unshifted_result >>  -  - 
			      (SI_Long)12L;
		  }
		  else
		      gensymed_symbol_2 = 
			      IFIX(scalef_function(Current_image_x_scale,
			      left_edge_of_block));
		  new_x_in_window = FIX(gensymed_symbol + gensymed_symbol_2);
		  gensymed_symbol = IFIX(Current_y_origin_of_drawing);
		  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		      gensymed_symbol_2 = IFIX(top_edge_of_block);
		  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  Current_image_y_scale) && 
			  FIXNUM_LT(Current_image_y_scale,
			  Isqrt_of_most_positive_fixnum) && 
			  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  top_edge_of_block) && 
			  FIXNUM_LT(top_edge_of_block,
			  Isqrt_of_most_positive_fixnum)) {
		      unshifted_result = 
			      IFIX(FIXNUM_TIMES(Current_image_y_scale,
			      top_edge_of_block)) + (SI_Long)2048L;
		      gensymed_symbol_2 = unshifted_result >>  -  - 
			      (SI_Long)12L;
		  }
		  else
		      gensymed_symbol_2 = 
			      IFIX(scalef_function(Current_image_y_scale,
			      top_edge_of_block));
		  new_y_in_window = FIX(gensymed_symbol + gensymed_symbol_2);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    SAVE_VALUES(scroll_region_on_image_plane(src_region,src_region,
	    FIXNUM_MINUS(new_x_in_window,old_x_in_window),
	    FIXNUM_MINUS(new_y_in_window,old_y_in_window)));
    if (src_region) {
	if ( !EQ(src_region,Qunbound_in_protected_let))
	    reclaim_region(src_region);
    }
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* SCROLL-REGION-ON-IMAGE-PLANE */
Object scroll_region_on_image_plane(source_region,clip_region,
	    delta_x_in_window,delta_y_in_window)
    Object source_region, clip_region, delta_x_in_window, delta_y_in_window;
{
    Object clip_visible_region, destination_region, visible_destination_region;
    Object offset_destination_region, useful_source_region;
    Object visible_useful_source_region, temp, visible_source_region;
    Object still_dirty_destination_region, now_dirty_source;
    Object total_dirty_region;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(89,52);
    SAVE_STACK();
    clip_visible_region = Qunbound_in_protected_let;
    destination_region = Qunbound_in_protected_let;
    visible_destination_region = Qunbound_in_protected_let;
    offset_destination_region = Qunbound_in_protected_let;
    useful_source_region = Qunbound_in_protected_let;
    visible_useful_source_region = Qunbound_in_protected_let;
    clip_visible_region = intersect_region(clip_region,
	    ISVREF(Current_image_plane,(SI_Long)28L));
    destination_region = shift_region(copy_region(source_region),
	    delta_x_in_window,delta_y_in_window);
    visible_destination_region = intersect_region(destination_region,
	    clip_visible_region);
    temp = copy_region(visible_destination_region);
    offset_destination_region = shift_region(temp,
	    FIXNUM_NEGATE(delta_x_in_window),FIXNUM_NEGATE(delta_y_in_window));
    useful_source_region = intersect_region(source_region,
	    offset_destination_region);
    visible_useful_source_region = intersect_region(useful_source_region,
	    clip_visible_region);
    scroll_region_of_current_window(visible_useful_source_region,
	    delta_x_in_window,delta_y_in_window);
    visible_source_region = Qunbound_in_protected_let;
    still_dirty_destination_region = Qunbound_in_protected_let;
    now_dirty_source = Qunbound_in_protected_let;
    total_dirty_region = Qunbound_in_protected_let;
    visible_source_region = intersect_region(source_region,
	    clip_visible_region);
    temp = visible_destination_region;
    still_dirty_destination_region = subtract_region(temp,
	    shift_region(visible_useful_source_region,delta_x_in_window,
	    delta_y_in_window));
    now_dirty_source = subtract_region(visible_source_region,
	    visible_destination_region);
    total_dirty_region = union_region(now_dirty_source,
	    still_dirty_destination_region);
    SAVE_VALUES(invalidate_region_of_window_when_on_window(total_dirty_region));
    if (total_dirty_region) {
	if ( !EQ(total_dirty_region,Qunbound_in_protected_let))
	    reclaim_region(total_dirty_region);
    }
    if (now_dirty_source) {
	if ( !EQ(now_dirty_source,Qunbound_in_protected_let))
	    reclaim_region(now_dirty_source);
    }
    if (still_dirty_destination_region) {
	if ( !EQ(still_dirty_destination_region,Qunbound_in_protected_let))
	    reclaim_region(still_dirty_destination_region);
    }
    if (visible_source_region) {
	if ( !EQ(visible_source_region,Qunbound_in_protected_let))
	    reclaim_region(visible_source_region);
    }
    if (visible_useful_source_region) {
	if ( !EQ(visible_useful_source_region,Qunbound_in_protected_let))
	    reclaim_region(visible_useful_source_region);
    }
    if (useful_source_region) {
	if ( !EQ(useful_source_region,Qunbound_in_protected_let))
	    reclaim_region(useful_source_region);
    }
    if (offset_destination_region) {
	if ( !EQ(offset_destination_region,Qunbound_in_protected_let))
	    reclaim_region(offset_destination_region);
    }
    if (visible_destination_region) {
	if ( !EQ(visible_destination_region,Qunbound_in_protected_let))
	    reclaim_region(visible_destination_region);
    }
    if (destination_region) {
	if ( !EQ(destination_region,Qunbound_in_protected_let))
	    reclaim_region(destination_region);
    }
    if (clip_visible_region) {
	if ( !EQ(clip_visible_region,Qunbound_in_protected_let))
	    reclaim_region(clip_visible_region);
    }
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Graphic_element_projection, Qgraphic_element_projection);

DEFINE_VARIABLE_WITH_SYMBOL(Operation_of_graphic_element, Qoperation_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Left_edge_in_window_of_graphic_element, Qleft_edge_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Top_edge_in_window_of_graphic_element, Qtop_edge_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Right_edge_in_window_of_graphic_element, Qright_edge_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Bottom_edge_in_window_of_graphic_element, Qbottom_edge_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Foreground_color_value_of_graphic_element, Qforeground_color_value_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Foreground_color_difference_of_graphic_element, Qforeground_color_difference_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(X_scale_of_graphic_element, Qx_scale_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Y_scale_of_graphic_element, Qy_scale_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Image_data_of_graphic_element, Qimage_data_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(X_in_window_of_graphic_element, Qx_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Y_in_window_of_graphic_element, Qy_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Rotation_of_graphic_element, Qrotation_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Quality_of_graphic_element, Qquality_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Background_color_value_of_graphic_element, Qbackground_color_value_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_or_icon_rendering_of_graphic_element, Qgraph_or_icon_rendering_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Foreground_color_difference_or_differences_of_graphic_element, Qforeground_color_difference_or_differences_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Color_values_of_graph_rasters_of_graphic_element, Qcolor_values_of_graph_rasters_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Left_edge_of_line_of_text_in_window_of_graphic_element, Qleft_edge_of_line_of_text_in_window_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Baseline_in_window_for_line_of_text_of_graphic_element, Qbaseline_in_window_for_line_of_text_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Text_line_for_line_of_text_of_graphic_element, Qtext_line_for_line_of_text_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Word_spacing_for_line_of_text_of_graphic_element, Qword_spacing_for_line_of_text_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Font_map_for_line_of_text_of_graphic_element, Qfont_map_for_line_of_text_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Color_difference_for_line_of_text_of_graphic_element, Qcolor_difference_for_line_of_text_of_graphic_element);

DEFINE_VARIABLE_WITH_SYMBOL(Entity_width_in_ws, Qentity_width_in_ws);

DEFINE_VARIABLE_WITH_SYMBOL(Entity_height_in_ws, Qentity_height_in_ws);

DEFINE_VARIABLE_WITH_SYMBOL(Poly_vertices, Qpoly_vertices);

DEFINE_VARIABLE_WITH_SYMBOL(Poly_line_width, Qpoly_line_width);

DEFINE_VARIABLE_WITH_SYMBOL(Poly_line_pattern, Qpoly_line_pattern);

DEFINE_VARIABLE_WITH_SYMBOL(Poly_line_style, Qpoly_line_style);

DEFINE_VARIABLE_WITH_SYMBOL(Polygon_fill_color_difference, Qpolygon_fill_color_difference);

DEFINE_VARIABLE_WITH_SYMBOL(Polygon_fill_pattern, Qpolygon_fill_pattern);

static Object Qadd_line_of_text;   /* add-line-of-text */

static Object Qadd_icon_rendering;  /* add-icon-rendering */

static Object Qadd_graph_rendering;  /* add-graph-rendering */

static Object Qpaint_solid_rectangle;  /* paint-solid-rectangle */

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

static Object Qadd_upward_sloping_line;  /* add-upward-sloping-line */

static Object Qadd_downward_sloping_line;  /* add-downward-sloping-line */

static Object Qpaint_image;        /* paint-image */

static Object Qpaint_icon_background_image;  /* paint-icon-background-image */

static Object Qadd_wide_polyline;  /* add-wide-polyline */

static Object Qadd_polygon;        /* add-polygon */

static Object Qadd_ellipse;        /* add-ellipse */

/* FILL-OUT-CURRENT-GRAPHIC-ELEMENT */
Object fill_out_current_graphic_element(graphic_element_operation,
	    new_left_edge_of_graphic_element_in_window,
	    new_top_edge_of_graphic_element_in_window,
	    new_right_edge_of_graphic_element_in_window,
	    new_bottom_edge_of_graphic_element_in_window,arg1,arg2,arg3,
	    arg4,arg5,arg6,arg7,arg8)
    Object graphic_element_operation;
    Object new_left_edge_of_graphic_element_in_window;
    Object new_top_edge_of_graphic_element_in_window;
    Object new_right_edge_of_graphic_element_in_window;
    Object new_bottom_edge_of_graphic_element_in_window, arg1, arg2, arg3;
    Object arg4, arg5, arg6, arg7, arg8;
{
    x_note_fn_call(89,53);
    Operation_of_graphic_element = graphic_element_operation;
    Left_edge_in_window_of_graphic_element = 
	    new_left_edge_of_graphic_element_in_window;
    Top_edge_in_window_of_graphic_element = 
	    new_top_edge_of_graphic_element_in_window;
    Right_edge_in_window_of_graphic_element = 
	    new_right_edge_of_graphic_element_in_window;
    Bottom_edge_in_window_of_graphic_element = 
	    new_bottom_edge_of_graphic_element_in_window;
    if (EQ(graphic_element_operation,Qadd_line_of_text)) {
	Text_line_for_line_of_text_of_graphic_element = arg1;
	Word_spacing_for_line_of_text_of_graphic_element = arg2;
	Font_map_for_line_of_text_of_graphic_element = arg3;
	Color_difference_for_line_of_text_of_graphic_element = arg4;
	X_scale_of_graphic_element = arg5;
	Y_scale_of_graphic_element = arg6;
	Left_edge_of_line_of_text_in_window_of_graphic_element = arg7;
	Baseline_in_window_for_line_of_text_of_graphic_element = arg8;
    }
    else if (EQ(graphic_element_operation,Qadd_icon_rendering)) {
	Foreground_color_difference_or_differences_of_graphic_element = arg1;
	Graph_or_icon_rendering_of_graphic_element = arg2;
    }
    else if (EQ(graphic_element_operation,Qadd_graph_rendering)) {
	Color_values_of_graph_rasters_of_graphic_element = arg1;
	Graph_or_icon_rendering_of_graphic_element = arg2;
    }
    else if (EQ(graphic_element_operation,Qpaint_solid_rectangle))
	Foreground_color_value_of_graphic_element = arg1;
    else if (EQ(graphic_element_operation,Qadd_solid_rectangle) || 
	    EQ(graphic_element_operation,Qadd_upward_sloping_line) || 
	    EQ(graphic_element_operation,Qadd_downward_sloping_line))
	Foreground_color_difference_of_graphic_element = arg1;
    else if (EQ(graphic_element_operation,Qpaint_image))
	Image_data_of_graphic_element = arg1;
    else if (EQ(graphic_element_operation,Qpaint_icon_background_image)) {
	Image_data_of_graphic_element = arg1;
	Image_left_offset_in_ws = arg2;
	Image_top_offset_in_ws = arg3;
	Entity_width_in_ws = arg4;
	Entity_height_in_ws = arg5;
    }
    else if (EQ(graphic_element_operation,Qadd_wide_polyline)) {
	Foreground_color_difference_of_graphic_element = arg1;
	Poly_line_width = arg2;
	Poly_line_pattern = arg3;
	Poly_line_style = arg4;
	Poly_vertices = arg5;
    }
    else if (EQ(graphic_element_operation,Qadd_polygon)) {
	Foreground_color_difference_of_graphic_element = arg1;
	Poly_line_width = arg2;
	Polygon_fill_color_difference = arg3;
	Polygon_fill_pattern = arg4;
	Poly_vertices = arg5;
    }
    else if (EQ(graphic_element_operation,Qadd_ellipse)) {
	Foreground_color_difference_of_graphic_element = arg1;
	Poly_line_width = arg2;
	Polygon_fill_color_difference = arg3;
	Polygon_fill_pattern = arg4;
	X_in_window_of_graphic_element = arg5;
	Y_in_window_of_graphic_element = arg6;
	Entity_width_in_ws = arg7;
	Entity_height_in_ws = arg8;
    }
    return VALUES_1(Nil);
}

/* PROJECT-GRAPHIC-ELEMENT-TO-CURRENT-WINDOW */
Object project_graphic_element_to_current_window(left_edge_of_area,
	    top_edge_of_area,right_edge_of_area,bottom_edge_of_area)
    Object left_edge_of_area, top_edge_of_area, right_edge_of_area;
    Object bottom_edge_of_area;
{
    Object top_edge_of_element_within_area, bottom_edge_of_element_within_area;
    Object left_edge_of_element_within_area, right_edge_of_element_within_area;
    Object color_values_for_rasters_qm, graph_rendering, temp, temp_1, temp_2;
    Object temp_3;

    x_note_fn_call(89,54);
    if ((FIXNUM_GE(bottom_edge_of_area,
	    Bottom_edge_in_window_of_graphic_element) && 
	    FIXNUM_GE(Bottom_edge_in_window_of_graphic_element,
	    top_edge_of_area) || 
	    FIXNUM_GE(Bottom_edge_in_window_of_graphic_element,
	    bottom_edge_of_area) && FIXNUM_GE(bottom_edge_of_area,
	    Top_edge_in_window_of_graphic_element)) && 
	    (FIXNUM_GE(right_edge_of_area,
	    Right_edge_in_window_of_graphic_element) && 
	    FIXNUM_GE(Right_edge_in_window_of_graphic_element,
	    left_edge_of_area) || 
	    FIXNUM_GE(Right_edge_in_window_of_graphic_element,
	    right_edge_of_area) && FIXNUM_GE(right_edge_of_area,
	    Left_edge_in_window_of_graphic_element))) {
	top_edge_of_element_within_area = 
		FIXNUM_MAX(Top_edge_in_window_of_graphic_element,
		top_edge_of_area);
	bottom_edge_of_element_within_area = 
		FIXNUM_MIN(Bottom_edge_in_window_of_graphic_element,
		bottom_edge_of_area);
	if (FIXNUM_LT(top_edge_of_element_within_area,
		bottom_edge_of_element_within_area)) {
	    left_edge_of_element_within_area = 
		    FIXNUM_MAX(Left_edge_in_window_of_graphic_element,
		    left_edge_of_area);
	    right_edge_of_element_within_area = 
		    FIXNUM_MIN(Right_edge_in_window_of_graphic_element,
		    right_edge_of_area);
	    if (EQ(Operation_of_graphic_element,Qadd_solid_rectangle))
		add_solid_rectangle_to_current_window(Erase_instead_qm,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_difference_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,Qadd_line_of_text))
		add_from_line_of_text_to_current_window(Erase_instead_qm,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Text_line_for_line_of_text_of_graphic_element,
			Word_spacing_for_line_of_text_of_graphic_element,
			Font_map_for_line_of_text_of_graphic_element,
			Color_difference_for_line_of_text_of_graphic_element,
			X_scale_of_graphic_element,
			Y_scale_of_graphic_element,
			Left_edge_of_line_of_text_in_window_of_graphic_element,
			Baseline_in_window_for_line_of_text_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,Qadd_icon_rendering)) {
		if (CONSP(Foreground_color_difference_or_differences_of_graphic_element))
		    add_from_icon_rendering_to_current_window(Erase_instead_qm,
			    left_edge_of_element_within_area,
			    top_edge_of_element_within_area,
			    right_edge_of_element_within_area,
			    bottom_edge_of_element_within_area,
			    FIX((SI_Long)0L),
			    Graph_or_icon_rendering_of_graphic_element,
			    FIXNUM_MINUS(left_edge_of_element_within_area,
			    Left_edge_in_window_of_graphic_element),
			    FIXNUM_MINUS(top_edge_of_element_within_area,
			    Top_edge_in_window_of_graphic_element),
			    Foreground_color_difference_or_differences_of_graphic_element);
		else
		    add_from_icon_rendering_to_current_window(Erase_instead_qm,
			    left_edge_of_element_within_area,
			    top_edge_of_element_within_area,
			    right_edge_of_element_within_area,
			    bottom_edge_of_element_within_area,
			    Foreground_color_difference_or_differences_of_graphic_element,
			    Graph_or_icon_rendering_of_graphic_element,
			    FIXNUM_MINUS(left_edge_of_element_within_area,
			    Left_edge_in_window_of_graphic_element),
			    FIXNUM_MINUS(top_edge_of_element_within_area,
			    Top_edge_in_window_of_graphic_element),Nil);
	    }
	    else if (EQ(Operation_of_graphic_element,Qpaint_solid_rectangle))
		paint_solid_rectangle_in_current_window(left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_value_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,Qadd_upward_sloping_line))
		add_upward_sloping_line_to_current_window(Erase_instead_qm,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_difference_of_graphic_element,
			Left_edge_in_window_of_graphic_element,
			Top_edge_in_window_of_graphic_element,
			Right_edge_in_window_of_graphic_element,
			Bottom_edge_in_window_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,
		    Qadd_downward_sloping_line))
		add_downward_sloping_line_to_current_window(Erase_instead_qm,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_difference_of_graphic_element,
			Left_edge_in_window_of_graphic_element,
			Top_edge_in_window_of_graphic_element,
			Right_edge_in_window_of_graphic_element,
			Bottom_edge_in_window_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,Qadd_graph_rendering)) {
		color_values_for_rasters_qm = 
			Color_values_of_graph_rasters_of_graphic_element;
		graph_rendering = Graph_or_icon_rendering_of_graphic_element;
		if (CDR(color_values_for_rasters_qm))
		    add_from_graph_rendering_to_current_window(Erase_instead_qm,
			    left_edge_of_element_within_area,
			    top_edge_of_element_within_area,
			    right_edge_of_element_within_area,
			    bottom_edge_of_element_within_area,
			    ISVREF(graph_rendering,(SI_Long)9L),
			    graph_rendering,
			    FIXNUM_MINUS(left_edge_of_element_within_area,
			    Left_edge_in_window_of_graphic_element),
			    FIXNUM_MINUS(top_edge_of_element_within_area,
			    Top_edge_in_window_of_graphic_element),
			    FIX((SI_Long)0L),color_values_for_rasters_qm);
		else
		    add_from_graph_rendering_to_current_window(Erase_instead_qm,
			    left_edge_of_element_within_area,
			    top_edge_of_element_within_area,
			    right_edge_of_element_within_area,
			    bottom_edge_of_element_within_area,
			    ISVREF(graph_rendering,(SI_Long)9L),
			    graph_rendering,
			    FIXNUM_MINUS(left_edge_of_element_within_area,
			    Left_edge_in_window_of_graphic_element),
			    FIXNUM_MINUS(top_edge_of_element_within_area,
			    Top_edge_in_window_of_graphic_element),
			    color_values_for_rasters_qm ? 
			    CAR(color_values_for_rasters_qm) : 
			    FIX((SI_Long)0L),Nil);
	    }
	    else if (EQ(Operation_of_graphic_element,Qpaint_image))
		paint_or_tile_image_in_current_window(Image_data_of_graphic_element,
			X_in_window_of_graphic_element,
			Y_in_window_of_graphic_element,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			X_scale_of_graphic_element,
			Y_scale_of_graphic_element,
			Rotation_of_graphic_element,
			Quality_of_graphic_element,
			Foreground_color_value_of_graphic_element,
			Background_color_value_of_graphic_element);
	    else if (EQ(Operation_of_graphic_element,
		    Qpaint_icon_background_image))
		paint_icon_background_image_in_current_window(Image_data_of_graphic_element,
			X_in_window_of_graphic_element,
			Y_in_window_of_graphic_element,
			left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			X_scale_of_graphic_element,
			Y_scale_of_graphic_element,
			Rotation_of_graphic_element,
			Quality_of_graphic_element,
			Foreground_color_value_of_graphic_element,
			Background_color_value_of_graphic_element,
			Image_left_offset_in_ws,Image_top_offset_in_ws,
			Entity_width_in_ws,Entity_height_in_ws);
	    else if (EQ(Operation_of_graphic_element,Qadd_wide_polyline)) {
		temp = Foreground_color_difference_of_graphic_element;
		temp_1 = Poly_line_width;
		temp_2 = encode_poly_line_style(Poly_line_style,
			Poly_line_pattern);
		temp_3 = encode_poly_line_pattern(Poly_line_pattern);
		add_wide_polyline_to_current_window(left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,temp,temp_1,
			temp_2,temp_3,Poly_vertices);
	    }
	    else if (EQ(Operation_of_graphic_element,Qadd_polygon))
		draw_polygon_on_current_window(left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_difference_of_graphic_element,
			Poly_line_width,Polygon_fill_color_difference,
			Polygon_fill_pattern,Poly_vertices);
	    else if (EQ(Operation_of_graphic_element,Qadd_ellipse))
		draw_ellipse_on_current_window(left_edge_of_element_within_area,
			top_edge_of_element_within_area,
			right_edge_of_element_within_area,
			bottom_edge_of_element_within_area,
			Foreground_color_difference_of_graphic_element,
			Poly_line_width,Polygon_fill_color_difference,
			Polygon_fill_pattern,
			X_in_window_of_graphic_element,
			Y_in_window_of_graphic_element,Entity_width_in_ws,
			Entity_height_in_ws);
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Effectively_infinite_region, Qeffectively_infinite_region);

/* PROJECT-GRAPHIC-ELEMENT */
Object project_graphic_element(left_edge_of_area,top_edge_of_area,
	    right_edge_of_area,bottom_edge_of_area)
    Object left_edge_of_area, top_edge_of_area, right_edge_of_area;
    Object bottom_edge_of_area;
{
    Object region, region_strip, top_edge_of_portion, bottom_edge_of_portion;
    Object region_strip_1, remaining_region_strips, ab_loop_list_;
    Object region_strip_2, a, b, left_edge_of_portion, right_edge_of_portion;
    Object ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(89,55);
    if (BOUNDP(Qcurrent_image_plane))
	region = ISVREF(Current_image_plane,(SI_Long)28L);
    else {
	region = Effectively_infinite_region;
	if (region);
	else {
	    Effectively_infinite_region = 
		    make_region_from_rectangle(FIX((SI_Long)-100000L),
		    FIX((SI_Long)-100000L),FIX((SI_Long)100000L),
		    FIX((SI_Long)100000L));
	    region = Effectively_infinite_region;
	}
    }
    region_strip = Nil;
    top_edge_of_portion = Nil;
    bottom_edge_of_portion = Nil;
    region_strip_1 = Nil;
    remaining_region_strips = Nil;
    ab_loop_list_ = M_CAR(region);
    region_strip_2 = Nil;
    a = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_strip_1 = CAR(ab_loop_list_);
    remaining_region_strips = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(remaining_region_strips))
	goto end_loop;
    region_strip_2 = FIRST(remaining_region_strips);
    a = CAR(region_strip_1);
    b = CAR(region_strip_2);
    if (top_edge_of_area) {
	a = FIXNUM_LE(a,top_edge_of_area) ? top_edge_of_area : 
		FIXNUM_LE(bottom_edge_of_area,a) ? bottom_edge_of_area : a;
	b = FIXNUM_LE(b,top_edge_of_area) ? top_edge_of_area : 
		FIXNUM_LE(bottom_edge_of_area,b) ? bottom_edge_of_area : b;
    }
    if ( !FIXNUM_EQ(a,b)) {
	top_edge_of_portion = a;
	bottom_edge_of_portion = b;
	region_strip = region_strip_1;
	left_edge_of_portion = Nil;
	right_edge_of_portion = Nil;
	ab_loop_list__1 = CDR(region_strip);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left_edge_of_portion = CAR(ab_loop_desetq_);
	right_edge_of_portion = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (left_edge_of_area) {
	    left_edge_of_portion = FIXNUM_LE(left_edge_of_portion,
		    left_edge_of_area) ? left_edge_of_area : 
		    FIXNUM_LE(right_edge_of_area,left_edge_of_portion) ? 
		    right_edge_of_area : left_edge_of_portion;
	    right_edge_of_portion = FIXNUM_LE(right_edge_of_portion,
		    left_edge_of_area) ? left_edge_of_area : 
		    FIXNUM_LE(right_edge_of_area,right_edge_of_portion) ? 
		    right_edge_of_area : right_edge_of_portion;
	}
	if ( !FIXNUM_EQ(left_edge_of_portion,right_edge_of_portion))
	    project_graphic_element_to_current_window(left_edge_of_portion,
		    top_edge_of_portion,right_edge_of_portion,
		    bottom_edge_of_portion);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* DRAW-GRAPHIC-ELEMENT */
Object draw_graphic_element varargs_1(int, n)
{
    Object graphic_element_operation, left_edge_of_graphic_element_in_window;
    Object top_edge_of_graphic_element_in_window;
    Object right_edge_of_graphic_element_in_window;
    Object bottom_edge_of_graphic_element_in_window, arg1;
    Object arg2, arg3, arg4, arg5, arg6, arg7, arg8;
    Object left_edge_within_draw_area, right_edge_within_draw_area;
    Object top_edge_within_draw_area, bottom_edge_within_draw_area;
    Object operation_of_graphic_element;
    Object baseline_in_window_for_line_of_text_of_graphic_element;
    Object bottom_edge_in_window_of_graphic_element;
    Object color_difference_for_line_of_text_of_graphic_element;
    Object color_values_of_graph_rasters_of_graphic_element;
    Object entity_height_in_ws, entity_width_in_ws;
    Object font_map_for_line_of_text_of_graphic_element;
    Object graph_or_icon_rendering_of_graphic_element;
    Object image_data_of_graphic_element, image_left_offset_in_ws;
    Object image_top_offset_in_ws, left_edge_in_window_of_graphic_element;
    Object left_edge_of_line_of_text_in_window_of_graphic_element;
    Object poly_line_width, poly_line_pattern, poly_line_style, poly_vertices;
    Object polygon_fill_color_difference, polygon_fill_pattern;
    Object right_edge_in_window_of_graphic_element;
    Object text_line_for_line_of_text_of_graphic_element;
    Object top_edge_in_window_of_graphic_element;
    Object word_spacing_for_line_of_text_of_graphic_element;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(24);
    Object result;

    x_note_fn_call(89,56);
    INIT_ARGS_nonrelocating();
    graphic_element_operation = REQUIRED_ARG_nonrelocating();
    left_edge_of_graphic_element_in_window = REQUIRED_ARG_nonrelocating();
    top_edge_of_graphic_element_in_window = REQUIRED_ARG_nonrelocating();
    right_edge_of_graphic_element_in_window = REQUIRED_ARG_nonrelocating();
    bottom_edge_of_graphic_element_in_window = REQUIRED_ARG_nonrelocating();
    arg1 = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    left_edge_within_draw_area = 
	    FIXNUM_MAX(left_edge_of_graphic_element_in_window,
	    Left_edge_of_draw_area);
    right_edge_within_draw_area = 
	    FIXNUM_MIN(right_edge_of_graphic_element_in_window,
	    Right_edge_of_draw_area);
    if (FIXNUM_LT(left_edge_within_draw_area,right_edge_within_draw_area)) {
	top_edge_within_draw_area = 
		FIXNUM_MAX(top_edge_of_graphic_element_in_window,
		Top_edge_of_draw_area);
	bottom_edge_within_draw_area = 
		FIXNUM_MIN(bottom_edge_of_graphic_element_in_window,
		Bottom_edge_of_draw_area);
	if (FIXNUM_LT(top_edge_within_draw_area,
		    bottom_edge_within_draw_area)) {
	    LOCK(Graphic_element_projection);
	    if (PUSH_UNWIND_PROTECT(0)) {
		operation_of_graphic_element = Nil;
		baseline_in_window_for_line_of_text_of_graphic_element = Nil;
		bottom_edge_in_window_of_graphic_element = Nil;
		color_difference_for_line_of_text_of_graphic_element = Nil;
		color_values_of_graph_rasters_of_graphic_element = Nil;
		entity_height_in_ws = Nil;
		entity_width_in_ws = Nil;
		font_map_for_line_of_text_of_graphic_element = Nil;
		graph_or_icon_rendering_of_graphic_element = Nil;
		image_data_of_graphic_element = Nil;
		image_left_offset_in_ws = Nil;
		image_top_offset_in_ws = Nil;
		left_edge_in_window_of_graphic_element = Nil;
		left_edge_of_line_of_text_in_window_of_graphic_element = Nil;
		poly_line_width = Nil;
		poly_line_pattern = Nil;
		poly_line_style = Nil;
		poly_vertices = Nil;
		polygon_fill_color_difference = Nil;
		polygon_fill_pattern = Nil;
		right_edge_in_window_of_graphic_element = Nil;
		text_line_for_line_of_text_of_graphic_element = Nil;
		top_edge_in_window_of_graphic_element = Nil;
		word_spacing_for_line_of_text_of_graphic_element = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Word_spacing_for_line_of_text_of_graphic_element,Qword_spacing_for_line_of_text_of_graphic_element,word_spacing_for_line_of_text_of_graphic_element,
			23);
		  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_in_window_of_graphic_element,Qtop_edge_in_window_of_graphic_element,top_edge_in_window_of_graphic_element,
			  22);
		    PUSH_SPECIAL_WITH_SYMBOL(Text_line_for_line_of_text_of_graphic_element,Qtext_line_for_line_of_text_of_graphic_element,text_line_for_line_of_text_of_graphic_element,
			    21);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_in_window_of_graphic_element,Qright_edge_in_window_of_graphic_element,right_edge_in_window_of_graphic_element,
			      20);
			PUSH_SPECIAL_WITH_SYMBOL(Polygon_fill_pattern,Qpolygon_fill_pattern,polygon_fill_pattern,
				19);
			  PUSH_SPECIAL_WITH_SYMBOL(Polygon_fill_color_difference,Qpolygon_fill_color_difference,polygon_fill_color_difference,
				  18);
			    PUSH_SPECIAL_WITH_SYMBOL(Poly_vertices,Qpoly_vertices,poly_vertices,
				    17);
			      PUSH_SPECIAL_WITH_SYMBOL(Poly_line_style,Qpoly_line_style,poly_line_style,
				      16);
				PUSH_SPECIAL_WITH_SYMBOL(Poly_line_pattern,Qpoly_line_pattern,poly_line_pattern,
					15);
				  PUSH_SPECIAL_WITH_SYMBOL(Poly_line_width,Qpoly_line_width,poly_line_width,
					  14);
				    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_line_of_text_in_window_of_graphic_element,Qleft_edge_of_line_of_text_in_window_of_graphic_element,left_edge_of_line_of_text_in_window_of_graphic_element,
					    13);
				      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_in_window_of_graphic_element,Qleft_edge_in_window_of_graphic_element,left_edge_in_window_of_graphic_element,
					      12);
					PUSH_SPECIAL_WITH_SYMBOL(Image_top_offset_in_ws,Qimage_top_offset_in_ws,image_top_offset_in_ws,
						11);
					  PUSH_SPECIAL_WITH_SYMBOL(Image_left_offset_in_ws,Qimage_left_offset_in_ws,image_left_offset_in_ws,
						  10);
					    PUSH_SPECIAL_WITH_SYMBOL(Image_data_of_graphic_element,Qimage_data_of_graphic_element,image_data_of_graphic_element,
						    9);
					      PUSH_SPECIAL_WITH_SYMBOL(Graph_or_icon_rendering_of_graphic_element,Qgraph_or_icon_rendering_of_graphic_element,graph_or_icon_rendering_of_graphic_element,
						      8);
						PUSH_SPECIAL_WITH_SYMBOL(Font_map_for_line_of_text_of_graphic_element,Qfont_map_for_line_of_text_of_graphic_element,font_map_for_line_of_text_of_graphic_element,
							7);
						  PUSH_SPECIAL_WITH_SYMBOL(Entity_width_in_ws,Qentity_width_in_ws,entity_width_in_ws,
							  6);
						    PUSH_SPECIAL_WITH_SYMBOL(Entity_height_in_ws,Qentity_height_in_ws,entity_height_in_ws,
							    5);
						      PUSH_SPECIAL_WITH_SYMBOL(Color_values_of_graph_rasters_of_graphic_element,Qcolor_values_of_graph_rasters_of_graphic_element,color_values_of_graph_rasters_of_graphic_element,
							      4);
							PUSH_SPECIAL_WITH_SYMBOL(Color_difference_for_line_of_text_of_graphic_element,Qcolor_difference_for_line_of_text_of_graphic_element,color_difference_for_line_of_text_of_graphic_element,
								3);
							  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_in_window_of_graphic_element,Qbottom_edge_in_window_of_graphic_element,bottom_edge_in_window_of_graphic_element,
								  2);
							    PUSH_SPECIAL_WITH_SYMBOL(Baseline_in_window_for_line_of_text_of_graphic_element,Qbaseline_in_window_for_line_of_text_of_graphic_element,baseline_in_window_for_line_of_text_of_graphic_element,
								    1);
							      PUSH_SPECIAL_WITH_SYMBOL(Operation_of_graphic_element,Qoperation_of_graphic_element,operation_of_graphic_element,
								      0);
								fill_out_current_graphic_element(graphic_element_operation,
									left_edge_of_graphic_element_in_window,
									top_edge_of_graphic_element_in_window,
									right_edge_of_graphic_element_in_window,
									bottom_edge_of_graphic_element_in_window,
									arg1,
									arg2,
									arg3,
									arg4,
									arg5,
									arg6,
									arg7,
									arg8);
								project_graphic_element(left_edge_within_draw_area,
									top_edge_within_draw_area,
									right_edge_within_draw_area,
									bottom_edge_within_draw_area);
								SAVE_VALUES(VALUES_1(Nil));
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
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Graphic_element_projection);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* DRAW-LINE-OF-TEXT-WITH-TABS */
Object draw_line_of_text_with_tabs(left_edge_in_window_init,
	    top_edge_in_window_init,right_edge_in_window_init,
	    bottom_edge_in_window_init,text_line,word_spacing_init,
	    font_map,color_difference_init,x_scale_init,y_scale_init,
	    left_edge_of_line_of_text_in_window_init,baseline_in_window_init)
    Object left_edge_in_window_init, top_edge_in_window_init;
    Object right_edge_in_window_init, bottom_edge_in_window_init, text_line;
    Object word_spacing_init, font_map, color_difference_init, x_scale_init;
    Object y_scale_init, left_edge_of_line_of_text_in_window_init;
    Object baseline_in_window_init;
{
    Object wide_string_bv16, text_string_substring_1, gensymed_symbol_3;
    Object gensymed_symbol_4;
    SI_Long left_edge_in_window, top_edge_in_window, right_edge_in_window;
    SI_Long bottom_edge_in_window, word_spacing, color_difference, x_scale;
    SI_Long y_scale, left_edge_of_line_of_text_in_window, baseline_in_window;
    SI_Long end_1, bv16_length, aref_arg_2, aref_new_value, previous_start;
    SI_Long start, left_edge_offset_text_width, left_edge, next_end;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long gensymed_symbol_2, i, aref_arg_2_1, arg, arg_1, arg_2, temp_1;
    char temp;

    x_note_fn_call(89,57);
    left_edge_in_window = IFIX(left_edge_in_window_init);
    top_edge_in_window = IFIX(top_edge_in_window_init);
    right_edge_in_window = IFIX(right_edge_in_window_init);
    bottom_edge_in_window = IFIX(bottom_edge_in_window_init);
    word_spacing = IFIX(word_spacing_init);
    color_difference = IFIX(color_difference_init);
    x_scale = IFIX(x_scale_init);
    y_scale = IFIX(y_scale_init);
    left_edge_of_line_of_text_in_window = 
	    IFIX(left_edge_of_line_of_text_in_window_init);
    baseline_in_window = IFIX(baseline_in_window_init);
    end_1 = IFIX(text_string_length(text_line));
    wide_string_bv16 = allocate_byte_vector_16(FIX(end_1 + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = end_1 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | end_1 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,end_1,(SI_Long)0L);
    text_string_substring_1 = wide_string_bv16;
    previous_start = (SI_Long)0L;
    start = (SI_Long)0L;
    left_edge_offset_text_width = (SI_Long)0L;
    left_edge = (SI_Long)0L;
    next_end = (SI_Long)0L;
  next_loop:
    gensymed_symbol = left_edge_of_line_of_text_in_window;
    if (x_scale == (SI_Long)4096L)
	gensymed_symbol_1 = left_edge_offset_text_width;
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < x_scale && 
	    x_scale < IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
	    left_edge_offset_text_width && left_edge_offset_text_width < 
	    IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = x_scale * left_edge_offset_text_width + 
		(SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(FIX(x_scale),
		FIX(left_edge_offset_text_width)));
    gensymed_symbol_2 = (SI_Long)128L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)8L;
    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    left_edge = gensymed_symbol + gensymed_symbol_1;
    i = start;
  next_loop_1:
    if (i == end_1) {
	next_end = end_1;
	goto end_2;
    }
    if (UBYTE_16_ISAREF_1(text_line,i) == (SI_Long)9L) {
	next_end = i;
	goto end_2;
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop:
    next_end = IFIX(Qnil);
  end_2:;
    aref_arg_2_1 = next_end - start;
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string_substring_1));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = aref_arg_2_1 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(text_string_substring_1,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | aref_arg_2_1 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(text_string_substring_1,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(text_string_substring_1,aref_arg_2_1,(SI_Long)0L);
    if (EQ(text_line,text_string_substring_1)) {
	if (start == next_end)
	    temp = TRUEP(T);
	else {
	    temp = start < (SI_Long)0L ? (SI_Long)0L < next_end : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = (SI_Long)0L;
		arg_1 = start;
		arg_2 = (SI_Long)0L + (next_end - start);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(text_line,FIX(start),
			text_string_substring_1,FIX((SI_Long)0L),
			FIX(next_end - start));
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
	gensymed_symbol_3 = text_line;
	gensymed_symbol = start;
	gensymed_symbol_4 = text_string_substring_1;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = next_end - start;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_3),
		gensymed_symbol,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_4),
		gensymed_symbol_1,gensymed_symbol_2);
    }
    draw_graphic_element(13,Qadd_line_of_text,FIX(left_edge_in_window),
	    FIX(top_edge_in_window),FIX(right_edge_in_window),
	    FIX(bottom_edge_in_window),text_string_substring_1,
	    FIX(word_spacing),font_map,FIX(color_difference),FIX(x_scale),
	    FIX(y_scale),FIX(left_edge),FIX(baseline_in_window));
    if (next_end == end_1)
	goto end_loop_1;
    previous_start = start;
    start = next_end + (SI_Long)1L;
    temp_1 = left_edge_offset_text_width;
    left_edge_offset_text_width = temp_1 + 
	    IFIX(compute_width_of_text_line(6,text_line,
	    FIX(previous_start),FIX(start),font_map,FIX(word_spacing),T));
    goto next_loop;
  end_loop_1:
    reclaim_text_string(text_string_substring_1);
    return VALUES_1(Nil);
}

/* DRAW-LINE */
Object draw_line(x1_in_window,y1_in_window,x2_in_window,y2_in_window,
	    color_difference)
    Object x1_in_window, y1_in_window, x2_in_window, y2_in_window;
    Object color_difference;
{
    x_note_fn_call(89,58);
    if (FIXNUM_EQ(y1_in_window,y2_in_window)) {
	if (FIXNUM_LT(x1_in_window,x2_in_window))
	    return draw_graphic_element(6,Qadd_solid_rectangle,
		    x1_in_window,y1_in_window,FIXNUM_ADD1(x2_in_window),
		    FIXNUM_ADD1(y2_in_window),color_difference);
	else
	    return draw_graphic_element(6,Qadd_solid_rectangle,
		    x2_in_window,y2_in_window,FIXNUM_ADD1(x1_in_window),
		    FIXNUM_ADD1(y1_in_window),color_difference);
    }
    else if (FIXNUM_EQ(x1_in_window,x2_in_window)) {
	if (FIXNUM_LT(y1_in_window,y2_in_window))
	    return draw_graphic_element(6,Qadd_solid_rectangle,
		    x1_in_window,y1_in_window,FIXNUM_ADD1(x2_in_window),
		    FIXNUM_ADD1(y2_in_window),color_difference);
	else
	    return draw_graphic_element(6,Qadd_solid_rectangle,
		    x2_in_window,y2_in_window,FIXNUM_ADD1(x1_in_window),
		    FIXNUM_ADD1(y1_in_window),color_difference);
    }
    else if (FIXNUM_LT(x1_in_window,x2_in_window)) {
	if (FIXNUM_LT(y1_in_window,y2_in_window))
	    return draw_downward_sloping_line_1(x1_in_window,y1_in_window,
		    FIX(IFIX(x2_in_window) + (SI_Long)2L),
		    FIX(IFIX(y2_in_window) + (SI_Long)2L),color_difference);
	else
	    return draw_upward_sloping_line_1(x1_in_window,y2_in_window,
		    FIX(IFIX(x2_in_window) + (SI_Long)2L),
		    FIX(IFIX(y1_in_window) + (SI_Long)2L),color_difference);
    }
    else if (FIXNUM_LT(y1_in_window,y2_in_window))
	return draw_upward_sloping_line_1(x2_in_window,y1_in_window,
		FIX(IFIX(x1_in_window) + (SI_Long)2L),
		FIX(IFIX(y2_in_window) + (SI_Long)2L),color_difference);
    else
	return draw_downward_sloping_line_1(x2_in_window,y2_in_window,
		FIX(IFIX(x1_in_window) + (SI_Long)2L),
		FIX(IFIX(y1_in_window) + (SI_Long)2L),color_difference);
}

/* NEW-DRAW-LINE */
Object new_draw_line(x1_in_window,y1_in_window,x2_in_window,y2_in_window,
	    color_difference)
    Object x1_in_window, y1_in_window, x2_in_window, y2_in_window;
    Object color_difference;
{
    x_note_fn_call(89,59);
    if (FIXNUM_LT(x1_in_window,x2_in_window)) {
	if (FIXNUM_LT(y1_in_window,y2_in_window))
	    return draw_downward_sloping_line_1(x1_in_window,y1_in_window,
		    FIXNUM_ADD1(x2_in_window),FIXNUM_ADD1(y2_in_window),
		    color_difference);
	else
	    return draw_upward_sloping_line_1(x1_in_window,y2_in_window,
		    FIXNUM_ADD1(x2_in_window),FIXNUM_ADD1(y1_in_window),
		    color_difference);
    }
    else if (FIXNUM_LT(y1_in_window,y2_in_window))
	return draw_upward_sloping_line_1(x2_in_window,y1_in_window,
		FIXNUM_ADD1(x1_in_window),FIXNUM_ADD1(y2_in_window),
		color_difference);
    else
	return draw_downward_sloping_line_1(x2_in_window,y2_in_window,
		FIXNUM_ADD1(x1_in_window),FIXNUM_ADD1(y1_in_window),
		color_difference);
}

/* DRAW-UPWARD-SLOPING-LINE-1 */
Object draw_upward_sloping_line_1(left_edge_in_window,top_edge_in_window,
	    right_edge_in_window,bottom_edge_in_window,color_difference)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_difference;
{
    x_note_fn_call(89,60);
    return draw_graphic_element(6,Qadd_upward_sloping_line,
	    left_edge_in_window,top_edge_in_window,right_edge_in_window,
	    bottom_edge_in_window,color_difference);
}

/* DRAW-DOWNWARD-SLOPING-LINE-1 */
Object draw_downward_sloping_line_1(left_edge_in_window,top_edge_in_window,
	    right_edge_in_window,bottom_edge_in_window,color_difference)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_difference;
{
    x_note_fn_call(89,61);
    return draw_graphic_element(6,Qadd_downward_sloping_line,
	    left_edge_in_window,top_edge_in_window,right_edge_in_window,
	    bottom_edge_in_window,color_difference);
}

/* PAINT-SOLID-RECTANGLE */
Object paint_solid_rectangle(left_edge_in_window,top_edge_in_window,
	    right_edge_in_window,bottom_edge_in_window,color_value)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_value;
{
    Object left_edge_in_draw_area, right_edge_in_draw_area;
    Object top_edge_in_draw_area, bottom_edge_in_draw_area;

    x_note_fn_call(89,62);
    left_edge_in_draw_area = FIXNUM_MAX(left_edge_in_window,
	    Left_edge_of_draw_area);
    right_edge_in_draw_area = FIXNUM_MIN(right_edge_in_window,
	    Right_edge_of_draw_area);
    if (FIXNUM_LT(left_edge_in_draw_area,right_edge_in_draw_area)) {
	top_edge_in_draw_area = FIXNUM_MAX(top_edge_in_window,
		Top_edge_of_draw_area);
	bottom_edge_in_draw_area = FIXNUM_MIN(bottom_edge_in_window,
		Bottom_edge_of_draw_area);
	if (FIXNUM_LT(top_edge_in_draw_area,bottom_edge_in_draw_area))
	    draw_graphic_element(6,Qpaint_solid_rectangle,
		    left_edge_in_draw_area,top_edge_in_draw_area,
		    right_edge_in_draw_area,bottom_edge_in_draw_area,
		    color_value);
    }
    return VALUES_1(Nil);
}

/* DRAW-WIDE-POLYLINE */
Object draw_wide_polyline(points,color_difference,line_width,line_pattern,
	    line_style)
    Object points, color_difference, line_width, line_pattern, line_style;
{
    x_note_fn_call(89,63);
    return draw_graphic_element(10,Qadd_wide_polyline,
	    Left_edge_of_draw_area,Top_edge_of_draw_area,
	    Right_edge_of_draw_area,Bottom_edge_of_draw_area,
	    color_difference,line_width,line_pattern,line_style,points);
}

/* DRAW-PATTERNED-LINE */
Object draw_patterned_line(x0,y0_1,x1,y1_1,color_value,line_width,line_pattern)
    Object x0, y0_1, x1, y1_1, color_value, line_width, line_pattern;
{
    Object color_difference, points;

    x_note_fn_call(89,64);
    color_difference = FIXNUM_LOGXOR(color_value,
	    Current_background_color_value);
    if (printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_wide_polyline,
	    ISVREF(Current_window,(SI_Long)11L))) {
	points = gensym_list_4(x0,y0_1,x1,y1_1);
	draw_wide_polyline(points,color_difference,line_width,line_pattern,
		Nil);
	return reclaim_gensym_list_1(points);
    }
    else
	return draw_line(x0,y0_1,x1,y1_1,color_difference);
}

/* DRAW-POLYGON */
Object draw_polygon varargs_1(int, n)
{
    Object points, color_difference;
    Object thick, filled_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,65);
    INIT_ARGS_nonrelocating();
    points = REQUIRED_ARG_nonrelocating();
    color_difference = REQUIRED_ARG_nonrelocating();
    thick = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)1L);
    filled_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !(printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_polyarcs,
	    ISVREF(Current_window,(SI_Long)11L))) ||  !TRUEP(filled_qm))
	draw_wide_polyline(points,color_difference,thick,Nil,Nil);
    else
	draw_graphic_element(10,Qadd_polygon,Left_edge_of_draw_area,
		Top_edge_of_draw_area,Right_edge_of_draw_area,
		Bottom_edge_of_draw_area,color_difference,thick,filled_qm ?
		 color_difference : Transparent_color_value,
		FIX((SI_Long)0L),points);
    return VALUES_1(points);
}

/* DRAW-CIRCLE */
Object draw_circle varargs_1(int, n)
{
    Object dimensions, color_difference;
    Object thick, filled_qm, gensymed_symbol, x, y, radius, x1, y1_1, x2, y2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,66);
    INIT_ARGS_nonrelocating();
    dimensions = REQUIRED_ARG_nonrelocating();
    color_difference = REQUIRED_ARG_nonrelocating();
    thick = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)1L);
    filled_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = dimensions;
    x = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    radius = CAR(gensymed_symbol);
    x1 = FIXNUM_MINUS(x,radius);
    y1_1 = FIXNUM_MINUS(y,radius);
    x2 = FIXNUM_ADD(x,radius);
    y2 = FIXNUM_ADD(y,radius);
    if ( !(printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_polyarcs,
	    ISVREF(Current_window,(SI_Long)11L))))
	draw_graphic_element(6,Qadd_solid_rectangle,x1,y1_1,x2,y2,
		color_difference);
    else
	draw_graphic_element(13,Qadd_ellipse,Left_edge_of_draw_area,
		Top_edge_of_draw_area,Right_edge_of_draw_area,
		Bottom_edge_of_draw_area,color_difference,thick,filled_qm ?
		 color_difference : Transparent_color_value,
		FIX((SI_Long)0L),x1,y1_1,x2,y2);
    return VALUES_1(dimensions);
}

DEFINE_VARIABLE_WITH_SYMBOL(Drawing_state_for_project_paper, Qdrawing_state_for_project_paper);

static Object Qwhite;              /* white */

static Object Qtransparent;        /* transparent */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qblack;              /* black */

static Object Qdrawing_paper;      /* drawing-paper */

/* SKETCH-IMAGE-PLANE */
Object sketch_image_plane()
{
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object color_or_metacolor, color_value, temp;
    Object background_color_or_metacolor, old_color_value;
    Object current_background_color_value;
    Declare_stack_pointer;
    Declare_special(5);
    Object result;

    x_note_fn_call(89,67);
    SAVE_STACK();
    current_image_x_scale = FIX((SI_Long)4096L);
    current_image_y_scale = FIX((SI_Long)4096L);
    current_x_origin_of_drawing = FIX((SI_Long)0L);
    current_y_origin_of_drawing = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  1);
	    color_or_metacolor = ISVREF(Current_image_plane,(SI_Long)5L) ? 
		    ISVREF(ISVREF(Current_image_plane,(SI_Long)5L),
		    (SI_Long)21L) : Nil;
	    if (color_or_metacolor);
	    else
		color_or_metacolor = Qwhite;
	    if (EQ(color_or_metacolor,Qtransparent) || 
		    EQ(color_or_metacolor,Qbackground)) {
		color_value = ISVREF(Current_color_map,(SI_Long)5L);
		if (color_value);
		else
		    color_value = map_to_color_value_1(Qwhite);
	    }
	    else if (EQ(color_or_metacolor,Qforeground) || 
		    EQ(color_or_metacolor,Qworkspace_foreground)) {
		temp = ISVREF(Current_image_plane,(SI_Long)5L) ? 
			ISVREF(ISVREF(Current_image_plane,(SI_Long)5L),
			(SI_Long)22L) : Nil;
		if (temp);
		else
		    temp = Qblack;
		color_or_metacolor = temp;
		if (EQ(color_or_metacolor,Qtransparent) || 
			EQ(color_or_metacolor,Qbackground)) {
		    background_color_or_metacolor = 
			    ISVREF(Current_image_plane,(SI_Long)5L) ? 
			    ISVREF(ISVREF(Current_image_plane,(SI_Long)5L),
			    (SI_Long)21L) : Nil;
		    if (background_color_or_metacolor);
		    else
			background_color_or_metacolor = Qwhite;
		    if (EQ(background_color_or_metacolor,Qforeground) || 
			    EQ(background_color_or_metacolor,
			    Qworkspace_foreground)) {
			color_value = ISVREF(Current_color_map,(SI_Long)4L);
			if (color_value);
			else
			    color_value = map_to_color_value_1(Qblack);
		    }
		    else if (EQ(background_color_or_metacolor,
			    Qtransparent) || 
			    EQ(background_color_or_metacolor,Qbackground)) {
			color_value = ISVREF(Current_color_map,(SI_Long)5L);
			if (color_value);
			else
			    color_value = map_to_color_value_1(Qwhite);
		    }
		    else
			color_value = EQ(background_color_or_metacolor,
				ISVREF(Current_color_map,(SI_Long)6L)) ? 
				ISVREF(Current_color_map,(SI_Long)7L) : 
				map_to_color_value_1(background_color_or_metacolor);
		}
		else if (EQ(color_or_metacolor,Qforeground) || 
			EQ(color_or_metacolor,Qworkspace_foreground)) {
		    color_value = ISVREF(Current_color_map,(SI_Long)4L);
		    if (color_value);
		    else
			color_value = map_to_color_value_1(Qblack);
		}
		else
		    color_value = EQ(color_or_metacolor,
			    ISVREF(Current_color_map,(SI_Long)6L)) ? 
			    ISVREF(Current_color_map,(SI_Long)7L) : 
			    map_to_color_value_1(color_or_metacolor);
	    }
	    else
		color_value = EQ(color_or_metacolor,
			ISVREF(Current_color_map,(SI_Long)6L)) ? 
			ISVREF(Current_color_map,(SI_Long)7L) : 
			map_to_color_value_1(color_or_metacolor);
	    old_color_value = Current_background_color_value;
	    current_background_color_value = Current_background_color_value;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		    0);
	      set_current_background_color_value(color_value);
	      SAVE_VALUES(project_frame(Qdrawing_paper,
		      ISVREF(ISVREF(Current_image_plane,(SI_Long)10L),
		      (SI_Long)2L),ISVREF(Current_image_plane,
		      (SI_Long)15L),ISVREF(Current_image_plane,
		      (SI_Long)16L),ISVREF(Current_image_plane,
		      (SI_Long)17L),ISVREF(Current_image_plane,
		      (SI_Long)18L),Nil));
	      set_current_background_color_value(old_color_value);
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qprinter;            /* printer */

/* PAINT-BACKGROUND-OF-IMAGE-PLANE */
Object paint_background_of_image_plane(region,state_qm)
    Object region, state_qm;
{
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, temp;
    Object region_strip, top, bottom, region_strip_1, remaining_region_strips;
    Object ab_loop_list_, region_strip_2, a, b, left, right, ab_loop_list__1;
    Object ab_loop_desetq_, drawing_state_for_project_paper;
    SI_Long arg, arg_1, arg_2, arg_3;
    char temp_1;
    Declare_special(17);

    x_note_fn_call(89,68);
    if ( !TRUEP(client_drawn_image_plane_p(Current_image_plane))) {
	current_image_x_scale = FIX((SI_Long)4096L);
	current_image_y_scale = FIX((SI_Long)4096L);
	current_x_origin_of_drawing = FIX((SI_Long)0L);
	current_y_origin_of_drawing = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		16);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		  15);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		    14);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		      13);
		left_edge_of_draw_area = ISVREF(Current_image_plane,
			(SI_Long)6L);
		top_edge_of_draw_area = ISVREF(Current_image_plane,
			(SI_Long)7L);
		right_edge_of_draw_area = ISVREF(Current_image_plane,
			(SI_Long)8L);
		bottom_edge_of_draw_area = ISVREF(Current_image_plane,
			(SI_Long)9L);
		PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			12);
		  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			  11);
		    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			    10);
		      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			      9);
			left_edge_of_draw_area = Left_edge_of_draw_area;
			top_edge_of_draw_area = Top_edge_of_draw_area;
			right_edge_of_draw_area = Right_edge_of_draw_area;
			bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
			PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
				8);
			  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
				  7);
			    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				      5);
				temp = ISVREF(Current_image_plane,
					(SI_Long)15L);
				Left_edge_of_draw_area = FIXNUM_MAX(temp,
					Left_edge_of_draw_area);
				temp = ISVREF(Current_image_plane,
					(SI_Long)16L);
				Top_edge_of_draw_area = FIXNUM_MAX(temp,
					Top_edge_of_draw_area);
				temp = ISVREF(Current_image_plane,
					(SI_Long)17L);
				Right_edge_of_draw_area = FIXNUM_MIN(temp,
					Right_edge_of_draw_area);
				temp = ISVREF(Current_image_plane,
					(SI_Long)18L);
				Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
					Bottom_edge_of_draw_area);
				if (FIXNUM_LT(Left_edge_of_draw_area,
					Right_edge_of_draw_area) && 
					FIXNUM_LT(Top_edge_of_draw_area,
					Bottom_edge_of_draw_area)) {
				    region_strip = Nil;
				    top = Nil;
				    bottom = Nil;
				    region_strip_1 = Nil;
				    remaining_region_strips = Nil;
				    ab_loop_list_ = M_CAR(region);
				    region_strip_2 = Nil;
				    a = Nil;
				    b = Nil;
				  next_loop:
				    if ( !TRUEP(ab_loop_list_))
					goto end_loop;
				    region_strip_1 = CAR(ab_loop_list_);
				    remaining_region_strips = 
					    CDR(ab_loop_list_);
				    ab_loop_list_ = M_CDR(ab_loop_list_);
				    if ( !TRUEP(remaining_region_strips))
					goto end_loop;
				    region_strip_2 = 
					    FIRST(remaining_region_strips);
				    a = CAR(region_strip_1);
				    b = CAR(region_strip_2);
				    if ( !FIXNUM_EQ(a,b)) {
					top = a;
					bottom = b;
					region_strip = region_strip_1;
					left = Nil;
					right = Nil;
					ab_loop_list__1 = CDR(region_strip);
					ab_loop_desetq_ = Nil;
				      next_loop_1:
					if ( !TRUEP(ab_loop_list__1))
					    goto end_loop_1;
					ab_loop_desetq_ = 
						M_CAR(ab_loop_list__1);
					left = CAR(ab_loop_desetq_);
					right = CDR(ab_loop_desetq_);
					ab_loop_list__1 = 
						M_CDR(ab_loop_list__1);
					if ( !FIXNUM_EQ(left,right)) {
					    left_edge_of_draw_area = 
						    Left_edge_of_draw_area;
					    top_edge_of_draw_area = 
						    Top_edge_of_draw_area;
					    right_edge_of_draw_area = 
						    Right_edge_of_draw_area;
					    bottom_edge_of_draw_area = 
						    Bottom_edge_of_draw_area;
					    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
						    4);
					      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
						      3);
						PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
							2);
						  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
							  1);
						    Left_edge_of_draw_area 
							    = 
							    FIXNUM_MAX(left,
							    Left_edge_of_draw_area);
						    Top_edge_of_draw_area 
							    = 
							    FIXNUM_MAX(top,
							    Top_edge_of_draw_area);
						    Right_edge_of_draw_area 
							    = 
							    FIXNUM_MIN(right,
							    Right_edge_of_draw_area);
						    Bottom_edge_of_draw_area 
							    = 
							    FIXNUM_MIN(bottom,
							    Bottom_edge_of_draw_area);
						    if (FIXNUM_LT(Left_edge_of_draw_area,
							    Right_edge_of_draw_area) 
							    && 
							    FIXNUM_LT(Top_edge_of_draw_area,
							    Bottom_edge_of_draw_area)) 
								{
							arg = 
								IFIX(ISVREF(Current_image_plane,
								(SI_Long)19L));
							arg_1 = 
								IFIX(Left_edge_of_draw_area);
							arg_2 = 
								IFIX(Right_edge_of_draw_area);
							arg_3 = 
								IFIX(ISVREF(Current_image_plane,
								(SI_Long)21L));
							if (arg <= arg_1 
								&& arg_1 
								<= arg_2 
								&& arg_2 
								<= arg_3) {
							    arg = 
								    IFIX(ISVREF(Current_image_plane,
								    (SI_Long)20L));
							    arg_1 = 
								    IFIX(Top_edge_of_draw_area);
							    arg_2 = 
								    IFIX(Bottom_edge_of_draw_area);
							    arg_3 = 
								    IFIX(ISVREF(Current_image_plane,
								    (SI_Long)22L));
							    temp_1 = arg 
								    <= 
								    arg_1 
								    && 
								    arg_1 
								    <= 
								    arg_2 ?
								     arg_2 
								    <= 
								    arg_3 :
								     
								    TRUEP(Qnil);
							}
							else
							    temp_1 = 
								    TRUEP(Nil);
							if (temp_1)
							    state_qm = 
								    draw_paper_for_current_image_plane(state_qm,
								    Left_edge_of_draw_area,
								    Top_edge_of_draw_area,
								    Right_edge_of_draw_area,
								    Bottom_edge_of_draw_area);
							else {
							    drawing_state_for_project_paper 
								    = state_qm;
							    PUSH_SPECIAL_WITH_SYMBOL(Drawing_state_for_project_paper,Qdrawing_state_for_project_paper,drawing_state_for_project_paper,
								    0);
							      if ( 
								      !(EQ(ISVREF(Current_window,
								      (SI_Long)1L),
								      Qprinter) 
								      && 
								      suppress_printing_border_p(Current_image_plane)))
								  project_frame(Qdrawing,
									  ISVREF(ISVREF(Current_image_plane,
									  (SI_Long)10L),
									  (SI_Long)2L),
									  ISVREF(Current_image_plane,
									  (SI_Long)15L),
									  ISVREF(Current_image_plane,
									  (SI_Long)16L),
									  ISVREF(Current_image_plane,
									  (SI_Long)17L),
									  ISVREF(Current_image_plane,
									  (SI_Long)18L),
									  Nil);
							      state_qm = 
								      Drawing_state_for_project_paper;
							    POP_SPECIAL();
							}
						    }
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					}
					goto next_loop_1;
				      end_loop_1:;
				    }
				    goto next_loop;
				  end_loop:;
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
	return VALUES_1(state_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qab_slot_value;      /* slot-value */

static Object Qicp;                /* icp */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

/* WORK-ON-XOR-DRAWING */
Object work_on_xor_drawing(region)
    Object region;
{
    Object current_drawing_transfer_mode, activity, slot_value_pop_store;
    Object svref_arg_1, cons_1, next_cons, temp, svref_arg_2, region_strip;
    Object top, bottom, region_strip_1, remaining_region_strips, ab_loop_list_;
    Object region_strip_2, a, b, left, right, ab_loop_list__1, ab_loop_desetq_;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, temp_1;
    Object maximum_time_slice_size, info;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char already_in_synch, temp_2;
    Declare_stack_pointer;
    Declare_special(5);
    Object result;

    x_note_fn_call(89,69);
    SAVE_STACK();
    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    4);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = Kxor;
	  synchronize_transfer_mode();
      }
      activity = Nil;
    next_loop:
      if ( !TRUEP(ISVREF(Current_image_plane,(SI_Long)31L)))
	  goto end_loop;
      slot_value_pop_store = Nil;
      svref_arg_1 = Current_image_plane;
      cons_1 = ISVREF(svref_arg_1,(SI_Long)31L);
      if (cons_1) {
	  slot_value_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qab_slot_value);
	  if (ISVREF(Available_slot_value_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_slot_value_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_slot_value_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_slot_value_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_slot_value_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      SVREF(svref_arg_1,FIX((SI_Long)31L)) = next_cons;
      activity = slot_value_pop_store;
      region_strip = Nil;
      top = Nil;
      bottom = Nil;
      region_strip_1 = Nil;
      remaining_region_strips = Nil;
      ab_loop_list_ = M_CAR(region);
      region_strip_2 = Nil;
      a = Nil;
      b = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      region_strip_1 = CAR(ab_loop_list_);
      remaining_region_strips = CDR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(remaining_region_strips))
	  goto end_loop_1;
      region_strip_2 = FIRST(remaining_region_strips);
      a = CAR(region_strip_1);
      b = CAR(region_strip_2);
      if ( !FIXNUM_EQ(a,b)) {
	  top = a;
	  bottom = b;
	  region_strip = region_strip_1;
	  left = Nil;
	  right = Nil;
	  ab_loop_list__1 = CDR(region_strip);
	  ab_loop_desetq_ = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_2;
	  ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	  left = CAR(ab_loop_desetq_);
	  right = CDR(ab_loop_desetq_);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  if ( !FIXNUM_EQ(left,right)) {
	      left_edge_of_draw_area = Left_edge_of_draw_area;
	      top_edge_of_draw_area = Top_edge_of_draw_area;
	      right_edge_of_draw_area = Right_edge_of_draw_area;
	      bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
	      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		      3);
		PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			    0);
		      Left_edge_of_draw_area = FIXNUM_MAX(left,
			      Left_edge_of_draw_area);
		      Top_edge_of_draw_area = FIXNUM_MAX(top,
			      Top_edge_of_draw_area);
		      Right_edge_of_draw_area = FIXNUM_MIN(right,
			      Right_edge_of_draw_area);
		      Bottom_edge_of_draw_area = FIXNUM_MIN(bottom,
			      Bottom_edge_of_draw_area);
		      if (FIXNUM_LT(Left_edge_of_draw_area,
			      Right_edge_of_draw_area) && 
			      FIXNUM_LT(Top_edge_of_draw_area,
			      Bottom_edge_of_draw_area))
			  do_activity(activity);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  goto next_loop_2;
	end_loop_2:;
      }
      goto next_loop_1;
    end_loop_1:;
      reclaim_slot_value_list_1(activity);
      if (FIXNUM_LT(Maximum_time_slice_size,Most_positive_fixnum)) {
	  gensymed_symbol = IFIX(Maximum_time_slice_size);
	  temp_1 = Extra_time_for_drawing;
	  if (temp_1);
	  else
	      temp_1 = FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(temp_1);
	  maximum_time_slice_size = FIX(gensymed_symbol + gensymed_symbol_1);
	  PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
		  0);
	    temp_2 = TRUEP(time_slice_expired_p());
	  POP_SPECIAL();
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2);
      else if ( !FIXNUM_EQ(Maximum_time_slice_size,Most_positive_fixnum) 
	      && EQ(ISVREF(Current_window,(SI_Long)1L),Qicp)) {
	  temp_2 = FIXNUM_EQ(ISVREF(Current_icp_socket,(SI_Long)15L),
		  Icp_connection_closed);
	  if (temp_2);
	  else {
	      info = ISVREF(Current_icp_socket,(SI_Long)24L);
	      temp_2 = info ? (EQ(Current_drawing_priority,
		      Kdraw_as_late_as_possible) ? 
		      TRUEP(ISVREF(ISVREF(Current_icp_socket,(SI_Long)4L),
		      (SI_Long)4L)) : FIXNUM_GE(ISVREF(info,(SI_Long)14L),
		      Drawing_max_outstanding_icp_bytes)) : TRUEP(Qnil);
	  }
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2)
	  goto end_loop;
      goto next_loop;
    end_loop:
      SAVE_VALUES(VALUES_1(Qnil));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object Icp_window_max_buffered_drawing_in_bytes = UNBOUND;

Object Icp_window_max_buffered_drawing_in_seconds = UNBOUND;

/* PAINT-CONTENTS-OF-IMAGE-PLANE */
Object paint_contents_of_image_plane(region,using_geometry_p)
    Object region, using_geometry_p;
{
    Object currently_working_on_drawing_workspace;
    Object workstation_with_image_plane_being_refreshed, left, top, right;
    Object bottom, block_or_connection, connection_p, slot_value_pop_store;
    Object svref_arg_1, cons_1, next_cons, temp, svref_arg_2, x2;
    Object gensymed_symbol, scale, value, region_strip, top_1, bottom_1;
    Object region_strip_1, remaining_region_strips, ab_loop_list_;
    Object region_strip_2, a, b, left_1, right_1, ab_loop_list__1;
    Object ab_loop_desetq_, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object compiled_function, fun, blk, ab_loop_list__2, ab_loop_it_, temp_2;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object current_drawing_transfer_mode, gensymed_symbol_3, subblocks;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    Object maximum_time_slice_size, info;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result, l2, t2;
    SI_Long value_1, r2, b2;
    char temp_1, already_in_synch;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(89,70);
    SAVE_STACK();
    LOCK(Working_on_drawing_workspace);
    if (PUSH_UNWIND_PROTECT(0)) {
	currently_working_on_drawing_workspace = T;
	workstation_with_image_plane_being_refreshed = 
		ISVREF(ISVREF(ISVREF(Current_image_plane,(SI_Long)2L),
		(SI_Long)2L),(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Workstation_with_image_plane_being_refreshed,Qworkstation_with_image_plane_being_refreshed,workstation_with_image_plane_being_refreshed,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Currently_working_on_drawing_workspace,Qcurrently_working_on_drawing_workspace,currently_working_on_drawing_workspace,
		  5);
	    result = region_bounding_rectangle(region);
	    MVS_4(result,left,top,right,bottom);
	    block_or_connection = Nil;
	    connection_p = Nil;
	  next_loop:
	    if ( !TRUEP(ISVREF(Current_image_plane,(SI_Long)30L)))
		goto end_loop;
	    slot_value_pop_store = Nil;
	    svref_arg_1 = Current_image_plane;
	    cons_1 = ISVREF(svref_arg_1,(SI_Long)30L);
	    if (cons_1) {
		slot_value_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    SVREF(svref_arg_1,FIX((SI_Long)30L)) = next_cons;
	    block_or_connection = slot_value_pop_store;
	    if (SIMPLE_VECTOR_P(block_or_connection) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(block_or_connection,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(block_or_connection,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    connection_p =  !temp_1 ? T : Nil;
	    if (EQ(ISVREF(Current_window,(SI_Long)1L),Qicp)) {
		maybe_restart_icp_window_update(Icp_window_max_buffered_drawing_in_seconds,
			Icp_window_max_buffered_drawing_in_bytes);
		if (FIXNUM_EQ(ISVREF(Current_icp_socket,(SI_Long)15L),
			Icp_connection_closed))
		    goto end_1;
	    }
	    temp_1 = TRUEP(connection_p);
	    if (temp_1);
	    else
		temp_1 = TRUEP(using_geometry_p);
	    if (temp_1);
	    else {
		gensymed_symbol = ACCESS_ONCE(ISVREF(block_or_connection,
			(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		temp_1 = gensymed_symbol ?  
			!EQ(ISVREF(ISVREF(block_or_connection,(SI_Long)1L),
			(SI_Long)1L),Qgraph) : TRUEP(Nil);
		if (temp_1);
		else {
		    gensymed_symbol = 
			    ACCESS_ONCE(ISVREF(block_or_connection,
			    (SI_Long)14L));
		    gensymed_symbol = gensymed_symbol ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol,
			    (SI_Long)6L)) : Nil;
		    temp_1 = TRUEP(gensymed_symbol);
		}
		if (temp_1);
		else {
		    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		    scale = Current_image_x_scale;
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    value = gensymed_symbol;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_2 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_2 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		    l2 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		    scale = Current_image_y_scale;
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    value = gensymed_symbol;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_2 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_2 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		    t2 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		    scale = Current_image_x_scale;
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    value_1 = gensymed_symbol_2 + (SI_Long)1L;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_2 = value_1;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			    value_1 && value_1 < 
			    IFIX(Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(scale) * value_1 + 
				(SI_Long)2048L;
			gensymed_symbol_2 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_2 = IFIX(scalef_function(scale,
				FIX(value_1)));
		    r2 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		    scale = Current_image_y_scale;
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    value_1 = gensymed_symbol_2 + (SI_Long)1L;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_2 = value_1;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			    value_1 && value_1 < 
			    IFIX(Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(scale) * value_1 + 
				(SI_Long)2048L;
			gensymed_symbol_2 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_2 = IFIX(scalef_function(scale,
				FIX(value_1)));
		    b2 = gensymed_symbol_1 + gensymed_symbol_2;
		    temp_1 = b2 >= IFIX(bottom) && IFIX(bottom) >= t2 || 
			    IFIX(bottom) >= b2 && b2 >= IFIX(top) ? r2 >= 
			    IFIX(right) && IFIX(right) >= l2 || 
			    IFIX(right) >= r2 && r2 >= IFIX(left) : 
			    TRUEP(Qnil);
		}
	    }
	    if (temp_1) {
		region_strip = Nil;
		top_1 = Nil;
		bottom_1 = Nil;
		region_strip_1 = Nil;
		remaining_region_strips = Nil;
		ab_loop_list_ = M_CAR(region);
		region_strip_2 = Nil;
		a = Nil;
		b = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		region_strip_1 = CAR(ab_loop_list_);
		remaining_region_strips = CDR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(remaining_region_strips))
		    goto end_loop_1;
		region_strip_2 = FIRST(remaining_region_strips);
		a = CAR(region_strip_1);
		b = CAR(region_strip_2);
		if ( !FIXNUM_EQ(a,b)) {
		    top_1 = a;
		    bottom_1 = b;
		    region_strip = region_strip_1;
		    left_1 = Nil;
		    right_1 = Nil;
		    ab_loop_list__1 = CDR(region_strip);
		    ab_loop_desetq_ = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_2;
		    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		    left_1 = CAR(ab_loop_desetq_);
		    right_1 = CDR(ab_loop_desetq_);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    if ( !FIXNUM_EQ(left_1,right_1)) {
			left_edge_of_draw_area = Left_edge_of_draw_area;
			top_edge_of_draw_area = Top_edge_of_draw_area;
			right_edge_of_draw_area = Right_edge_of_draw_area;
			bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
			PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
				4);
			  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
				  3);
			    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				    2);
			      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				      1);
				Left_edge_of_draw_area = FIXNUM_MAX(left_1,
					Left_edge_of_draw_area);
				Top_edge_of_draw_area = FIXNUM_MAX(top_1,
					Top_edge_of_draw_area);
				Right_edge_of_draw_area = 
					FIXNUM_MIN(right_1,
					Right_edge_of_draw_area);
				Bottom_edge_of_draw_area = 
					FIXNUM_MIN(bottom_1,
					Bottom_edge_of_draw_area);
				if (FIXNUM_LT(Left_edge_of_draw_area,
					Right_edge_of_draw_area) && 
					FIXNUM_LT(Top_edge_of_draw_area,
					Bottom_edge_of_draw_area)) {
				    if (using_geometry_p || connection_p)
					draw_block_or_connection(block_or_connection);
				    else {
					gensymed_symbol = 
						ACCESS_ONCE(ISVREF(block_or_connection,
						(SI_Long)14L));
					gensymed_symbol = gensymed_symbol ?
						 
						ACCESS_ONCE(ISVREF(gensymed_symbol,
						(SI_Long)4L)) : Nil;
					temp_1 = gensymed_symbol ?  
						!EQ(ISVREF(ISVREF(block_or_connection,
						(SI_Long)1L),(SI_Long)1L),
						Qgraph) : TRUEP(Nil);
					if (temp_1);
					else {
					    gensymed_symbol = 
						    ACCESS_ONCE(ISVREF(block_or_connection,
						    (SI_Long)14L));
					    gensymed_symbol = 
						    gensymed_symbol ? 
						    ACCESS_ONCE(ISVREF(gensymed_symbol,
						    (SI_Long)6L)) : Nil;
					    temp_1 = TRUEP(gensymed_symbol);
					}
					if (temp_1);
					else {
					    gensymed_symbol_1 = 
						    IFIX(Current_x_origin_of_drawing);
					    scale = Current_image_x_scale;
					    gensymed_symbol = 
						    ISVREF(block_or_connection,
						    (SI_Long)14L);
					    gensymed_symbol = 
						    gensymed_symbol ? 
						    ISVREF(gensymed_symbol,
						    (SI_Long)0L) : 
						    FIX((SI_Long)0L);
					    value = gensymed_symbol;
					    if (IFIX(scale) == (SI_Long)4096L)
						gensymed_symbol_2 = 
							IFIX(value);
					    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    scale) && 
						    FIXNUM_LT(scale,
						    Isqrt_of_most_positive_fixnum) 
						    && 
						    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    value) && 
						    FIXNUM_LT(value,
						    Isqrt_of_most_positive_fixnum)) 
							{
						unshifted_result = 
							IFIX(FIXNUM_TIMES(scale,
							value)) + 
							(SI_Long)2048L;
						gensymed_symbol_2 = 
							unshifted_result 
							>>  -  - (SI_Long)12L;
					    }
					    else
						gensymed_symbol_2 = 
							IFIX(scalef_function(scale,
							value));
					    l2 = gensymed_symbol_1 + 
						    gensymed_symbol_2;
					    gensymed_symbol_1 = 
						    IFIX(Current_y_origin_of_drawing);
					    scale = Current_image_y_scale;
					    gensymed_symbol = 
						    ISVREF(block_or_connection,
						    (SI_Long)14L);
					    gensymed_symbol = 
						    gensymed_symbol ? 
						    ISVREF(gensymed_symbol,
						    (SI_Long)1L) : 
						    FIX((SI_Long)0L);
					    value = gensymed_symbol;
					    if (IFIX(scale) == (SI_Long)4096L)
						gensymed_symbol_2 = 
							IFIX(value);
					    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    scale) && 
						    FIXNUM_LT(scale,
						    Isqrt_of_most_positive_fixnum) 
						    && 
						    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    value) && 
						    FIXNUM_LT(value,
						    Isqrt_of_most_positive_fixnum)) 
							{
						unshifted_result = 
							IFIX(FIXNUM_TIMES(scale,
							value)) + 
							(SI_Long)2048L;
						gensymed_symbol_2 = 
							unshifted_result 
							>>  -  - (SI_Long)12L;
					    }
					    else
						gensymed_symbol_2 = 
							IFIX(scalef_function(scale,
							value));
					    t2 = gensymed_symbol_1 + 
						    gensymed_symbol_2;
					    gensymed_symbol_1 = 
						    IFIX(Current_x_origin_of_drawing);
					    scale = Current_image_x_scale;
					    gensymed_symbol = 
						    ISVREF(block_or_connection,
						    (SI_Long)14L);
					    gensymed_symbol = 
						    gensymed_symbol ? 
						    ISVREF(gensymed_symbol,
						    (SI_Long)2L) : 
						    FIX((SI_Long)0L);
					    gensymed_symbol_2 = 
						    IFIX(gensymed_symbol);
					    value_1 = gensymed_symbol_2 + 
						    (SI_Long)1L;
					    if (IFIX(scale) == (SI_Long)4096L)
						gensymed_symbol_2 = value_1;
					    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    scale) && 
						    FIXNUM_LT(scale,
						    Isqrt_of_most_positive_fixnum) 
						    && 
						    IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						    < value_1 && value_1 < 
						    IFIX(Isqrt_of_most_positive_fixnum)) 
							{
						unshifted_result = 
							IFIX(scale) * 
							value_1 + 
							(SI_Long)2048L;
						gensymed_symbol_2 = 
							unshifted_result 
							>>  -  - (SI_Long)12L;
					    }
					    else
						gensymed_symbol_2 = 
							IFIX(scalef_function(scale,
							FIX(value_1)));
					    r2 = gensymed_symbol_1 + 
						    gensymed_symbol_2;
					    gensymed_symbol_1 = 
						    IFIX(Current_y_origin_of_drawing);
					    scale = Current_image_y_scale;
					    gensymed_symbol = 
						    ISVREF(block_or_connection,
						    (SI_Long)14L);
					    gensymed_symbol = 
						    gensymed_symbol ? 
						    ISVREF(gensymed_symbol,
						    (SI_Long)3L) : 
						    FIX((SI_Long)0L);
					    gensymed_symbol_2 = 
						    IFIX(gensymed_symbol);
					    value_1 = gensymed_symbol_2 + 
						    (SI_Long)1L;
					    if (IFIX(scale) == (SI_Long)4096L)
						gensymed_symbol_2 = value_1;
					    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						    scale) && 
						    FIXNUM_LT(scale,
						    Isqrt_of_most_positive_fixnum) 
						    && 
						    IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						    < value_1 && value_1 < 
						    IFIX(Isqrt_of_most_positive_fixnum)) 
							{
						unshifted_result = 
							IFIX(scale) * 
							value_1 + 
							(SI_Long)2048L;
						gensymed_symbol_2 = 
							unshifted_result 
							>>  -  - (SI_Long)12L;
					    }
					    else
						gensymed_symbol_2 = 
							IFIX(scalef_function(scale,
							FIX(value_1)));
					    b2 = gensymed_symbol_1 + 
						    gensymed_symbol_2;
					    temp_1 = b2 >= 
						    IFIX(Bottom_edge_of_draw_area) 
						    && 
						    IFIX(Bottom_edge_of_draw_area) 
						    >= t2 || 
						    IFIX(Bottom_edge_of_draw_area) 
						    >= b2 && b2 >= 
						    IFIX(Top_edge_of_draw_area) 
						    ? r2 >= 
						    IFIX(Right_edge_of_draw_area) 
						    && 
						    IFIX(Right_edge_of_draw_area) 
						    >= l2 || 
						    IFIX(Right_edge_of_draw_area) 
						    >= r2 && r2 >= 
						    IFIX(Left_edge_of_draw_area) 
						    : TRUEP(Qnil);
					}
					if (temp_1) {
					    if ( !((SI_Long)0L != 
						    (IFIX(ISVREF(block_or_connection,
						    (SI_Long)5L)) & 
						    (SI_Long)32768L))) {
						if ((SI_Long)0L != 
							(IFIX(ISVREF(block_or_connection,
							(SI_Long)5L)) & 
							(SI_Long)1024L)) {
						    if (Currently_working_on_drawing_workspace) 
								{
							compiled_function 
								= 
								SYMBOL_FUNCTION(Qdeferred_draw_block);
							fun = Nil;
							blk = Nil;
							ab_loop_list__2 = 
								ISVREF(Current_image_plane,
								(SI_Long)31L);
							ab_loop_it_ = Nil;
							ab_loop_desetq_ = Nil;
						      next_loop_3:
							if ( 
								!TRUEP(ab_loop_list__2))
							    goto end_loop_3;
							ab_loop_desetq_ = 
								M_CAR(ab_loop_list__2);
							fun = 
								CAR(ab_loop_desetq_);
							temp_2 = 
								CDR(ab_loop_desetq_);
							blk = CAR(temp_2);
							ab_loop_list__2 = 
								M_CDR(ab_loop_list__2);
							ab_loop_it_ = 
								EQ(fun,
								compiled_function) 
								? (EQ(blk,
								block_or_connection) 
								? T : Nil) 
								: Qnil;
							if (ab_loop_it_) {
							    temp_1 = 
								    TRUEP(ab_loop_it_);
							    goto end_2;
							}
							goto next_loop_3;
						      end_loop_3:
							temp_1 = TRUEP(Qnil);
						      end_2:;
							if ( !temp_1) {
							    svref_arg_1 = 
								    Current_image_plane;
							    temp_2 = 
								    block_or_connection;
							    slot_value_push_modify_macro_arg 
								    = 
								    slot_value_list_3(SYMBOL_FUNCTION(Qdeferred_draw_block),
								    temp_2,
								    copy_frame_serial_number(ISVREF(block_or_connection,
								    (SI_Long)3L)));
							    car_1 = 
								    slot_value_push_modify_macro_arg;
							    cdr_1 = 
								    ISVREF(svref_arg_1,
								    (SI_Long)31L);
							    temp = 
								    slot_value_cons_1(car_1,
								    cdr_1);
							    SVREF(svref_arg_1,
								    FIX((SI_Long)31L)) 
								    = temp;
							}
						    }
						    else {
							already_in_synch = 
								EQ(Current_drawing_transfer_mode,
								Kxor);
							current_drawing_transfer_mode 
								= 
								Current_drawing_transfer_mode;
							PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
								0);
							  if ( 
								  !already_in_synch) 
								      {
							      Current_drawing_transfer_mode 
								      = Kxor;
							      synchronize_transfer_mode();
							  }
							  gensymed_symbol 
								  = 
								  ISVREF(ISVREF(ISVREF(ISVREF(block_or_connection,
								  (SI_Long)1L),
								  (SI_Long)11L),
								  (SI_Long)5L),
								  (SI_Long)1L);
							  gensymed_symbol_3 
								  = 
								  block_or_connection;
							  inline_funcall_1(gensymed_symbol,
								  gensymed_symbol_3);
							POP_SPECIAL();
							if ( !already_in_synch)
							    synchronize_transfer_mode();
						    }
						}
						else {
						    gensymed_symbol = 
							    ISVREF(ISVREF(ISVREF(ISVREF(block_or_connection,
							    (SI_Long)1L),
							    (SI_Long)11L),
							    (SI_Long)5L),
							    (SI_Long)1L);
						    gensymed_symbol_3 = 
							    block_or_connection;
						    inline_funcall_1(gensymed_symbol,
							    gensymed_symbol_3);
						}
						if (T &&  
							!EQ(ISVREF(ISVREF(block_or_connection,
							(SI_Long)1L),
							(SI_Long)1L),Qgraph)) {
						    gensymed_symbol = 
							    ACCESS_ONCE(ISVREF(block_or_connection,
							    (SI_Long)14L));
						    gensymed_symbol = 
							    gensymed_symbol 
							    ? 
							    ACCESS_ONCE(ISVREF(gensymed_symbol,
							    (SI_Long)4L)) :
							     Nil;
						    subblocks = 
							    gensymed_symbol;
						    if (subblocks &&  ! 
							    !TRUEP(constant_queue_next(ISVREF(subblocks,
							    (SI_Long)2L),
							    subblocks))) {
							gensymed_symbol = 
								ACCESS_ONCE(ISVREF(block_or_connection,
								(SI_Long)14L));
							gensymed_symbol = 
								gensymed_symbol 
								? 
								ACCESS_ONCE(ISVREF(gensymed_symbol,
								(SI_Long)4L)) 
								: Nil;
							ab_queue_form_ = 
								gensymed_symbol;
							ab_next_queue_element_ 
								= Nil;
							subblock = Nil;
							if (ab_queue_form_)
							    ab_next_queue_element_ 
								    = 
								    constant_queue_next(ISVREF(ab_queue_form_,
								    (SI_Long)2L),
								    ab_queue_form_);
						      next_loop_4:
							if ( 
								!TRUEP(ab_next_queue_element_))
							    goto end_loop_4;
							subblock = 
								ISVREF(ab_next_queue_element_,
								(SI_Long)4L);
							ab_next_queue_element_ 
								= 
								constant_queue_next(ab_next_queue_element_,
								ab_queue_form_);
							draw_block_and_subblocks(subblock,
								T);
							goto next_loop_4;
						      end_loop_4:;
						    }
						    gensymed_symbol = 
							    ACCESS_ONCE(ISVREF(block_or_connection,
							    (SI_Long)14L));
						    gensymed_symbol = 
							    gensymed_symbol 
							    ? 
							    ACCESS_ONCE(ISVREF(gensymed_symbol,
							    (SI_Long)6L)) :
							     Nil;
						    if (gensymed_symbol)
							draw_connections_for_block(block_or_connection);
						}
					    }
					    else
						draw_block_possibly_with_frame(block_or_connection,
							T);
					}
				    }
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    goto next_loop_2;
		  end_loop_2:;
		}
		goto next_loop_1;
	      end_loop_1:;
	    }
	    if (FIXNUM_LT(Maximum_time_slice_size,Most_positive_fixnum)) {
		gensymed_symbol_1 = IFIX(Maximum_time_slice_size);
		temp_2 = Extra_time_for_drawing;
		if (temp_2);
		else
		    temp_2 = FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(temp_2);
		maximum_time_slice_size = FIX(gensymed_symbol_1 + 
			gensymed_symbol_2);
		PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
			0);
		  temp_1 = TRUEP(time_slice_expired_p());
		POP_SPECIAL();
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else if ( !FIXNUM_EQ(Maximum_time_slice_size,
		    Most_positive_fixnum) && EQ(ISVREF(Current_window,
		    (SI_Long)1L),Qicp)) {
		temp_1 = FIXNUM_EQ(ISVREF(Current_icp_socket,(SI_Long)15L),
			Icp_connection_closed);
		if (temp_1);
		else {
		    info = ISVREF(Current_icp_socket,(SI_Long)24L);
		    temp_1 = info ? (EQ(Current_drawing_priority,
			    Kdraw_as_late_as_possible) ? 
			    TRUEP(ISVREF(ISVREF(Current_icp_socket,
			    (SI_Long)4L),(SI_Long)4L)) : 
			    FIXNUM_GE(ISVREF(info,(SI_Long)14L),
			    Drawing_max_outstanding_icp_bytes)) : TRUEP(Qnil);
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop;
	    goto next_loop;
	  end_loop:
	  end_1:;
	    if ( !TRUEP(ISVREF(Current_image_plane,(SI_Long)30L)) && 
		    show_selection_handles_p(1,Current_window) && 
		    image_plane_selected_p(Current_image_plane))
		draw_selection_handles_for_current_image_plane(left,top,
			right,bottom);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_drawing_workspace);
    CONTINUE_UNWINDING(0);
    if (ISVREF(Current_image_plane,(SI_Long)31L) &&  
	    !TRUEP(ISVREF(Current_image_plane,(SI_Long)30L))) {
	result = work_on_xor_drawing(region);
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qabove_inclusive;    /* above-inclusive */

/* PAINT-REGION-OF-IMAGE-PLANE-OVERLAPPING-BLOCK */
Object paint_region_of_image_plane_overlapping_block(workspace,image_plane,
	    block,region)
    Object workspace, image_plane, block, region;
{
    Object currently_working_on_drawing_workspace;
    Object workstation_with_image_plane_being_refreshed;
    Object maximum_time_slice_size, priority_of_next_task, region_strip, top;
    Object bottom, region_strip_1, remaining_region_strips, ab_loop_list_;
    Object region_strip_2, a, b, left, right, ab_loop_list__1, ab_loop_desetq_;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, temp;
    char opaque_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(6);
    Object result;

    x_note_fn_call(89,71);
    SAVE_STACK();
    LOCK(Working_on_drawing_workspace);
    if (PUSH_UNWIND_PROTECT(0)) {
	currently_working_on_drawing_workspace = T;
	workstation_with_image_plane_being_refreshed = 
		ISVREF(ISVREF(ISVREF(Current_image_plane,(SI_Long)2L),
		(SI_Long)2L),(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Workstation_with_image_plane_being_refreshed,Qworkstation_with_image_plane_being_refreshed,workstation_with_image_plane_being_refreshed,
		5);
	  PUSH_SPECIAL_WITH_SYMBOL(Currently_working_on_drawing_workspace,Qcurrently_working_on_drawing_workspace,currently_working_on_drawing_workspace,
		  4);
	    opaque_qm = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		    (SI_Long)1024L);
	    if ( !opaque_qm) {
		maximum_time_slice_size = Most_positive_fixnum;
		priority_of_next_task = Most_positive_fixnum;
		PUSH_SPECIAL_WITH_SYMBOL(Priority_of_next_task,Qpriority_of_next_task,priority_of_next_task,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
			  0);
		    paint_background_of_image_plane(region,Nil);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    region_strip = Nil;
	    top = Nil;
	    bottom = Nil;
	    region_strip_1 = Nil;
	    remaining_region_strips = Nil;
	    ab_loop_list_ = M_CAR(region);
	    region_strip_2 = Nil;
	    a = Nil;
	    b = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    region_strip_1 = CAR(ab_loop_list_);
	    remaining_region_strips = CDR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(remaining_region_strips))
		goto end_loop;
	    region_strip_2 = FIRST(remaining_region_strips);
	    a = CAR(region_strip_1);
	    b = CAR(region_strip_2);
	    if ( !FIXNUM_EQ(a,b)) {
		top = a;
		bottom = b;
		region_strip = region_strip_1;
		left = Nil;
		right = Nil;
		ab_loop_list__1 = CDR(region_strip);
		ab_loop_desetq_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		left = CAR(ab_loop_desetq_);
		right = CDR(ab_loop_desetq_);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !FIXNUM_EQ(left,right)) {
		    left_edge_of_draw_area = Left_edge_of_draw_area;
		    top_edge_of_draw_area = Top_edge_of_draw_area;
		    right_edge_of_draw_area = Right_edge_of_draw_area;
		    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			    3);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			      2);
			PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				  0);
			    temp = left_edge_within_pane(left,image_plane);
			    Left_edge_of_draw_area = FIXNUM_MAX(temp,
				    Left_edge_of_draw_area);
			    temp = top_edge_within_pane(top,image_plane);
			    Top_edge_of_draw_area = FIXNUM_MAX(temp,
				    Top_edge_of_draw_area);
			    temp = right_edge_within_pane(right,image_plane);
			    Right_edge_of_draw_area = FIXNUM_MIN(temp,
				    Right_edge_of_draw_area);
			    temp = bottom_edge_within_pane(bottom,image_plane);
			    Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				    Bottom_edge_of_draw_area);
			    if (FIXNUM_LT(Left_edge_of_draw_area,
				    Right_edge_of_draw_area) && 
				    FIXNUM_LT(Top_edge_of_draw_area,
				    Bottom_edge_of_draw_area))
				draw_overlapping_blocks(workspace,block,
					opaque_qm ? Qabove_inclusive : Nil,T);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		goto next_loop_1;
	      end_loop_1:;
	    }
	    goto next_loop;
	  end_loop:;
	    if (show_selection_handles_p(1,Current_window) && 
		    image_plane_selected_p(Current_image_plane)) {
		result = region_bounding_rectangle(region);
		MVS_4(result,left,top,right,bottom);
		draw_selection_handles_for_current_image_plane(left,top,
			right,bottom);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_drawing_workspace);
    CONTINUE_UNWINDING(0);
    if (ISVREF(Current_image_plane,(SI_Long)31L)) {
	maximum_time_slice_size = Most_positive_fixnum;
	priority_of_next_task = Most_positive_fixnum;
	PUSH_SPECIAL_WITH_SYMBOL(Priority_of_next_task,Qpriority_of_next_task,priority_of_next_task,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
		  0);
	    result = work_on_xor_drawing(region);
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* PAINT-BACKGROUND-FOR-OPAQUE-BLOCK */
Object paint_background_for_opaque_block(block)
    Object block;
{
    Object gensymed_symbol, scale, value;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long left_edge_within_draw_area, right_edge_within_draw_area;
    SI_Long top_edge_within_draw_area, bottom_edge_within_draw_area;
    char temp;

    x_note_fn_call(89,72);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1024L)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp = TRUEP(gensymed_symbol);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	value = gensymed_symbol;
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
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(Left_edge_of_draw_area);
	left_edge_within_draw_area = MAX(gensymed_symbol_1,gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	value = gensymed_symbol;
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
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(Right_edge_of_draw_area);
	right_edge_within_draw_area = MIN(gensymed_symbol_1,gensymed_symbol_2);
	if (left_edge_within_draw_area < right_edge_within_draw_area) {
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    value = gensymed_symbol;
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
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(Top_edge_of_draw_area);
	    top_edge_within_draw_area = MAX(gensymed_symbol_1,
		    gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    value = gensymed_symbol;
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
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(Bottom_edge_of_draw_area);
	    bottom_edge_within_draw_area = MIN(gensymed_symbol_1,
		    gensymed_symbol_2);
	    if (top_edge_within_draw_area < bottom_edge_within_draw_area)
		paint_solid_rectangle(FIX(left_edge_within_draw_area),
			FIX(top_edge_within_draw_area),
			FIX(right_edge_within_draw_area),
			FIX(bottom_edge_within_draw_area),
			Current_background_color_value);
	}
    }
    return VALUES_1(Nil);
}

/* DRAW-BLOCK-OUTLINE-IN-CURRENT-IMAGE-PLANE */
Object draw_block_outline_in_current_image_plane varargs_1(int, n)
{
    Object block;
    Object color_or_metacolor_qm, gensymed_symbol, temp, temp_1, temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,73);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    color_or_metacolor_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return draw_rectangle_outline_in_current_image_plane(5,temp,temp_1,
	    temp_2,gensymed_symbol,color_or_metacolor_qm);
}

/* DRAW-RECTANGLE-OUTLINE-IN-CURRENT-IMAGE-PLANE */
Object draw_rectangle_outline_in_current_image_plane varargs_1(int, n)
{
    Object left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace;
    Object color_or_metacolor_qm, line_width_in_workspace_qm;
    Object color_or_metacolor, color_value_1, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,74);
    INIT_ARGS_nonrelocating();
    left_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    top_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    right_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    bottom_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    color_or_metacolor_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_width_in_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    color_or_metacolor = color_or_metacolor_qm;
    if (color_or_metacolor);
    else
	color_or_metacolor = Qforeground;
    if (EQ(color_or_metacolor,Qbackground))
	color_value_1 = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	color_value_1 = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	color_value_1 = Current_background_color_value;
    else
	color_value_1 = map_to_color_value(color_or_metacolor);
    temp = FIXNUM_LOGXOR(color_value_1,Current_background_color_value);
    temp_1 = line_width_in_workspace_qm;
    if (temp_1);
    else
	temp_1 = FIX((SI_Long)1L);
    return draw_rectangle_outline_in_current_image_plane_1(left_edge_in_workspace,
	    top_edge_in_workspace,right_edge_in_workspace,
	    bottom_edge_in_workspace,temp,temp_1);
}

/* PAINT-RECTANGLE-OUTLINE-IN-CURRENT-IMAGE-PLANE */
Object paint_rectangle_outline_in_current_image_plane varargs_1(int, n)
{
    Object left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace;
    Object color_or_metacolor_qm, line_width_in_workspace_qm;
    Object color_or_metacolor, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,75);
    INIT_ARGS_nonrelocating();
    left_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    top_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    right_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    bottom_edge_in_workspace = REQUIRED_ARG_nonrelocating();
    color_or_metacolor_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_width_in_workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    color_or_metacolor = color_or_metacolor_qm;
    if (color_or_metacolor);
    else
	color_or_metacolor = Qforeground;
    if (EQ(color_or_metacolor,Qbackground))
	temp = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	temp = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	temp = Current_background_color_value;
    else
	temp = map_to_color_value(color_or_metacolor);
    temp_1 = line_width_in_workspace_qm;
    if (temp_1);
    else
	temp_1 = FIX((SI_Long)1L);
    return paint_rectangle_outline_in_current_image_plane_1(left_edge_in_workspace,
	    top_edge_in_workspace,right_edge_in_workspace,
	    bottom_edge_in_workspace,temp,temp_1);
}

/* DRAW-RECTANGLE-OUTLINE-IN-CURRENT-IMAGE-PLANE-1 */
Object draw_rectangle_outline_in_current_image_plane_1(left_edge_in_workspace,
	    top_edge_in_workspace,right_edge_in_workspace,
	    bottom_edge_in_workspace,color_difference,line_width_in_workspace)
    Object left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace, color_difference;
    Object line_width_in_workspace;
{
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left_edge_in_window, top_edge_in_window, right_edge_in_window;
    SI_Long bottom_edge_in_window, x_width_in_window, y_width_in_window;

    x_note_fn_call(89,76);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(left_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    left_edge_in_workspace) && FIXNUM_LT(left_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		left_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		left_edge_in_workspace));
    left_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(top_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    top_edge_in_workspace) && FIXNUM_LT(top_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		top_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		top_edge_in_workspace));
    top_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(right_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    right_edge_in_workspace) && FIXNUM_LT(right_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		right_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		right_edge_in_workspace));
    right_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(bottom_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    bottom_edge_in_workspace) && 
	    FIXNUM_LT(bottom_edge_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		bottom_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		bottom_edge_in_workspace));
    bottom_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    if (IFIX(line_width_in_workspace) == (SI_Long)0L)
	x_width_in_window = (SI_Long)1L;
    else {
	gensymed_symbol = (SI_Long)1L;
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(line_width_in_workspace);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		line_width_in_workspace) && 
		FIXNUM_LT(line_width_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    line_width_in_workspace)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    line_width_in_workspace));
	x_width_in_window = MAX(gensymed_symbol,gensymed_symbol_1);
    }
    if (IFIX(line_width_in_workspace) == (SI_Long)0L)
	y_width_in_window = (SI_Long)1L;
    else {
	gensymed_symbol = (SI_Long)1L;
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(line_width_in_workspace);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		line_width_in_workspace) && 
		FIXNUM_LT(line_width_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    line_width_in_workspace)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    line_width_in_workspace));
	y_width_in_window = MAX(gensymed_symbol,gensymed_symbol_1);
    }
    draw_rectangle_outline_in_window(FIX(left_edge_in_window),
	    FIX(top_edge_in_window),FIX(right_edge_in_window),
	    FIX(bottom_edge_in_window),color_difference,
	    FIX(x_width_in_window),FIX(y_width_in_window));
    return VALUES_1(Nil);
}

/* PAINT-RECTANGLE-OUTLINE-IN-CURRENT-IMAGE-PLANE-1 */
Object paint_rectangle_outline_in_current_image_plane_1(left_edge_in_workspace,
	    top_edge_in_workspace,right_edge_in_workspace,
	    bottom_edge_in_workspace,color_value,line_width_in_workspace)
    Object left_edge_in_workspace, top_edge_in_workspace;
    Object right_edge_in_workspace, bottom_edge_in_workspace, color_value;
    Object line_width_in_workspace;
{
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left_edge_in_window, top_edge_in_window, right_edge_in_window;
    SI_Long bottom_edge_in_window, x_width_in_window, y_width_in_window;

    x_note_fn_call(89,77);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(left_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    left_edge_in_workspace) && FIXNUM_LT(left_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		left_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		left_edge_in_workspace));
    left_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(top_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    top_edge_in_workspace) && FIXNUM_LT(top_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		top_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		top_edge_in_workspace));
    top_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(right_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    right_edge_in_workspace) && FIXNUM_LT(right_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		right_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		right_edge_in_workspace));
    right_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(bottom_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    bottom_edge_in_workspace) && 
	    FIXNUM_LT(bottom_edge_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		bottom_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		bottom_edge_in_workspace));
    bottom_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    if (IFIX(line_width_in_workspace) == (SI_Long)0L)
	x_width_in_window = (SI_Long)1L;
    else {
	gensymed_symbol = (SI_Long)1L;
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(line_width_in_workspace);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		line_width_in_workspace) && 
		FIXNUM_LT(line_width_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    line_width_in_workspace)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    line_width_in_workspace));
	x_width_in_window = MAX(gensymed_symbol,gensymed_symbol_1);
    }
    if (IFIX(line_width_in_workspace) == (SI_Long)0L)
	y_width_in_window = (SI_Long)1L;
    else {
	gensymed_symbol = (SI_Long)1L;
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(line_width_in_workspace);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		line_width_in_workspace) && 
		FIXNUM_LT(line_width_in_workspace,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    line_width_in_workspace)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    line_width_in_workspace));
	y_width_in_window = MAX(gensymed_symbol,gensymed_symbol_1);
    }
    paint_rectangle_outline_in_window(FIX(left_edge_in_window),
	    FIX(top_edge_in_window),FIX(right_edge_in_window),
	    FIX(bottom_edge_in_window),color_value,FIX(x_width_in_window),
	    FIX(y_width_in_window));
    return VALUES_1(Nil);
}

/* DRAW-RECTANGLE-OUTLINE-IN-WINDOW */
Object draw_rectangle_outline_in_window(left_edge_in_window,
	    top_edge_in_window,right_edge_in_window,bottom_edge_in_window,
	    color_difference,x_line_width_in_window,y_line_width_in_window)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_difference, x_line_width_in_window;
    Object y_line_width_in_window;
{
    x_note_fn_call(89,78);
    draw_graphic_element(6,Qadd_solid_rectangle,left_edge_in_window,
	    top_edge_in_window,right_edge_in_window,
	    FIXNUM_ADD(top_edge_in_window,y_line_width_in_window),
	    color_difference);
    draw_graphic_element(6,Qadd_solid_rectangle,left_edge_in_window,
	    FIXNUM_MINUS(bottom_edge_in_window,y_line_width_in_window),
	    right_edge_in_window,bottom_edge_in_window,color_difference);
    draw_graphic_element(6,Qadd_solid_rectangle,left_edge_in_window,
	    FIXNUM_ADD(top_edge_in_window,y_line_width_in_window),
	    FIXNUM_ADD(left_edge_in_window,x_line_width_in_window),
	    FIXNUM_MINUS(bottom_edge_in_window,y_line_width_in_window),
	    color_difference);
    draw_graphic_element(6,Qadd_solid_rectangle,
	    FIXNUM_MINUS(right_edge_in_window,x_line_width_in_window),
	    FIXNUM_ADD(top_edge_in_window,y_line_width_in_window),
	    right_edge_in_window,FIXNUM_MINUS(bottom_edge_in_window,
	    y_line_width_in_window),color_difference);
    return VALUES_1(Nil);
}

/* PAINT-RECTANGLE-OUTLINE-IN-WINDOW */
Object paint_rectangle_outline_in_window(left_edge_in_window,
	    top_edge_in_window,right_edge_in_window,bottom_edge_in_window,
	    color_value,x_line_width_in_window,y_line_width_in_window)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_value, x_line_width_in_window;
    Object y_line_width_in_window;
{
    x_note_fn_call(89,79);
    paint_solid_rectangle(left_edge_in_window,top_edge_in_window,
	    right_edge_in_window,FIXNUM_ADD(top_edge_in_window,
	    y_line_width_in_window),color_value);
    paint_solid_rectangle(left_edge_in_window,
	    FIXNUM_MINUS(bottom_edge_in_window,y_line_width_in_window),
	    right_edge_in_window,bottom_edge_in_window,color_value);
    paint_solid_rectangle(left_edge_in_window,
	    FIXNUM_ADD(top_edge_in_window,y_line_width_in_window),
	    FIXNUM_ADD(left_edge_in_window,x_line_width_in_window),
	    FIXNUM_MINUS(bottom_edge_in_window,y_line_width_in_window),
	    color_value);
    paint_solid_rectangle(FIXNUM_MINUS(right_edge_in_window,
	    x_line_width_in_window),FIXNUM_ADD(top_edge_in_window,
	    y_line_width_in_window),right_edge_in_window,
	    FIXNUM_MINUS(bottom_edge_in_window,y_line_width_in_window),
	    color_value);
    return VALUES_1(Nil);
}

/* PAINT-RECTANGLE-FRAME-IN-CURRENT-IMAGE-PLANE */
Object paint_rectangle_frame_in_current_image_plane(outside_left_edge_in_workspace,
	    outside_top_edge_in_workspace,outside_right_edge_in_workspace,
	    outside_bottom_edge_in_workspace,inside_left_edge_in_workspace,
	    inside_top_edge_in_workspace,inside_right_edge_in_workspace,
	    inside_bottom_edge_in_workspace,color_or_metacolor)
    Object outside_left_edge_in_workspace, outside_top_edge_in_workspace;
    Object outside_right_edge_in_workspace, outside_bottom_edge_in_workspace;
    Object inside_left_edge_in_workspace, inside_top_edge_in_workspace;
    Object inside_right_edge_in_workspace, inside_bottom_edge_in_workspace;
    Object color_or_metacolor;
{
    Object color_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long outside_left_edge_in_window, outside_top_edge_in_window;
    SI_Long outside_right_edge_in_window, outside_bottom_edge_in_window;
    SI_Long inside_left_edge_in_window, inside_top_edge_in_window;
    SI_Long inside_right_edge_in_window, inside_bottom_edge_in_window;

    x_note_fn_call(89,80);
    if (EQ(color_or_metacolor,Qbackground))
	color_value = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	color_value = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	color_value = Current_background_color_value;
    else
	color_value = map_to_color_value(color_or_metacolor);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(outside_left_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    outside_left_edge_in_workspace) && 
	    FIXNUM_LT(outside_left_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		outside_left_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		outside_left_edge_in_workspace));
    outside_left_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(outside_top_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    outside_top_edge_in_workspace) && 
	    FIXNUM_LT(outside_top_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		outside_top_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		outside_top_edge_in_workspace));
    outside_top_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(outside_right_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    outside_right_edge_in_workspace) && 
	    FIXNUM_LT(outside_right_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		outside_right_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		outside_right_edge_in_workspace));
    outside_right_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(outside_bottom_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    outside_bottom_edge_in_workspace) && 
	    FIXNUM_LT(outside_bottom_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		outside_bottom_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		outside_bottom_edge_in_workspace));
    outside_bottom_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(inside_left_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    inside_left_edge_in_workspace) && 
	    FIXNUM_LT(inside_left_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		inside_left_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		inside_left_edge_in_workspace));
    inside_left_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(inside_top_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    inside_top_edge_in_workspace) && 
	    FIXNUM_LT(inside_top_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		inside_top_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		inside_top_edge_in_workspace));
    inside_top_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(inside_right_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    inside_right_edge_in_workspace) && 
	    FIXNUM_LT(inside_right_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		inside_right_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		inside_right_edge_in_workspace));
    inside_right_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(inside_bottom_edge_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    inside_bottom_edge_in_workspace) && 
	    FIXNUM_LT(inside_bottom_edge_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		inside_bottom_edge_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		inside_bottom_edge_in_workspace));
    inside_bottom_edge_in_window = gensymed_symbol + gensymed_symbol_1;
    if (outside_left_edge_in_window < outside_right_edge_in_window && 
	    outside_top_edge_in_window < outside_bottom_edge_in_window) {
	if (outside_top_edge_in_window < inside_top_edge_in_window)
	    paint_solid_rectangle(FIX(outside_left_edge_in_window),
		    FIX(outside_top_edge_in_window),
		    FIX(outside_right_edge_in_window),
		    FIX(inside_top_edge_in_window),color_value);
	if (inside_top_edge_in_window < inside_bottom_edge_in_window) {
	    if (outside_left_edge_in_window < inside_left_edge_in_window)
		paint_solid_rectangle(FIX(outside_left_edge_in_window),
			FIX(inside_top_edge_in_window),
			FIX(inside_left_edge_in_window),
			FIX(inside_bottom_edge_in_window),color_value);
	    if (inside_right_edge_in_window < outside_right_edge_in_window)
		paint_solid_rectangle(FIX(inside_right_edge_in_window),
			FIX(inside_top_edge_in_window),
			FIX(outside_right_edge_in_window),
			FIX(inside_bottom_edge_in_window),color_value);
	}
	if (inside_bottom_edge_in_window < outside_bottom_edge_in_window)
	    paint_solid_rectangle(FIX(outside_left_edge_in_window),
		    FIX(inside_bottom_edge_in_window),
		    FIX(outside_right_edge_in_window),
		    FIX(outside_bottom_edge_in_window),color_value);
    }
    return VALUES_1(Nil);
}

static Object Qdrawing_contents;   /* drawing-contents */

static Object Qdrawing_close_box;  /* drawing-close-box */

static Object Qmouse_tracking;     /* mouse-tracking */

static Object Qcompute_content_region;  /* compute-content-region */

static Object Qmove_elevator;      /* move-elevator */

/* FRAME-INTERESTING-P */
Object frame_interesting_p()
{
    Object temp, point_x, point_y;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result, l2, t2, r2;
    SI_Long b2, left, top, right, bottom;

    x_note_fn_call(89,81);
    if (EQ(Purpose_of_frame_projecting,Qdrawing) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_paper) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_contents) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_close_box)) {
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	l2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	t2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	r2 = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	b2 = gensymed_symbol + gensymed_symbol_1;
	if (b2 >= IFIX(Bottom_edge_of_draw_area) && 
		IFIX(Bottom_edge_of_draw_area) >= t2 || 
		IFIX(Bottom_edge_of_draw_area) >= b2 && b2 >= 
		IFIX(Top_edge_of_draw_area)) {
	    temp = r2 >= IFIX(Right_edge_of_draw_area) ? 
		    (IFIX(Right_edge_of_draw_area) >= l2 ? T : Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (IFIX(Right_edge_of_draw_area) >= r2)
		return VALUES_1(r2 >= IFIX(Left_edge_of_draw_area) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	point_x = ISVREF(Mouse_pointer_of_frame,(SI_Long)2L);
	point_y = ISVREF(Mouse_pointer_of_frame,(SI_Long)3L);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	left = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	top = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	right = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	bottom = gensymed_symbol + gensymed_symbol_1;
	if (left <= IFIX(point_x) && IFIX(point_x) < right && top <= 
		IFIX(point_y))
	    return VALUES_1(IFIX(point_y) < bottom ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region))
	return VALUES_1( !TRUEP(CDR(Control_stack_of_frame_projecting)) ? 
		T : Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return VALUES_1(T);
    else
	return VALUES_1(Qnil);
}

/* INDENT-FRAME */
Object indent_frame(indent)
    Object indent;
{
    Object incff_1_arg, temp, decff_1_arg;

    x_note_fn_call(89,82);
    incff_1_arg = indent;
    temp = FIXNUM_ADD(Left_edge_of_frame,incff_1_arg);
    Left_edge_of_frame = temp;
    incff_1_arg = indent;
    temp = FIXNUM_ADD(Top_edge_of_frame,incff_1_arg);
    Top_edge_of_frame = temp;
    decff_1_arg = indent;
    temp = FIXNUM_MINUS(Right_edge_of_frame,decff_1_arg);
    Right_edge_of_frame = temp;
    decff_1_arg = indent;
    temp = FIXNUM_MINUS(Bottom_edge_of_frame,decff_1_arg);
    Bottom_edge_of_frame = temp;
    return VALUES_1(Bottom_edge_of_frame);
}

static Object Qsquare;             /* square */

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

/* PROJECT-FRAME */
Object project_frame(purpose,frame_description,
	    left_edge_of_frame_in_workspace,top_edge_of_frame_in_workspace,
	    right_edge_of_frame_in_workspace,
	    bottom_edge_of_frame_in_workspace,interior_projection_qm)
    Object purpose, frame_description, left_edge_of_frame_in_workspace;
    Object top_edge_of_frame_in_workspace, right_edge_of_frame_in_workspace;
    Object bottom_edge_of_frame_in_workspace, interior_projection_qm;
{
    Object purpose_of_frame_projecting, orientation_of_frame;
    Object control_stack_of_frame_projecting, left_edge_of_frame;
    Object top_edge_of_frame, right_edge_of_frame, bottom_edge_of_frame;
    Object current_drawing_transfer_mode;
    char already_in_synch;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(8);
    Object result;

    x_note_fn_call(89,83);
    SAVE_STACK();
    LOCK(Frame_projecting);
    if (PUSH_UNWIND_PROTECT(0)) {
	purpose_of_frame_projecting = purpose;
	orientation_of_frame = Qsquare;
	control_stack_of_frame_projecting = 
		graphics_cons_1(frame_description,Nil);
	left_edge_of_frame = left_edge_of_frame_in_workspace;
	top_edge_of_frame = top_edge_of_frame_in_workspace;
	right_edge_of_frame = right_edge_of_frame_in_workspace;
	bottom_edge_of_frame = bottom_edge_of_frame_in_workspace;
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
		7);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
		  6);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
		    5);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
		      4);
		PUSH_SPECIAL_WITH_SYMBOL(Control_stack_of_frame_projecting,Qcontrol_stack_of_frame_projecting,control_stack_of_frame_projecting,
			3);
		  PUSH_SPECIAL_WITH_SYMBOL(Orientation_of_frame,Qorientation_of_frame,orientation_of_frame,
			  2);
		    PUSH_SPECIAL_WITH_SYMBOL(Purpose_of_frame_projecting,Qpurpose_of_frame_projecting,purpose_of_frame_projecting,
			    1);
		      already_in_synch = EQ(Current_drawing_transfer_mode,
			      Kpaint_infered_from_xor);
		      current_drawing_transfer_mode = 
			      Current_drawing_transfer_mode;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			      0);
			if ( !already_in_synch) {
			    Current_drawing_transfer_mode = 
				    Kpaint_infered_from_xor;
			    synchronize_transfer_mode();
			}
			project_frame_1(Nil);
		      POP_SPECIAL();
		      if ( !already_in_synch)
			  synchronize_transfer_mode();
		      if (interior_projection_qm)
			  SAVE_VALUES(FUNCALL_0(interior_projection_qm));
		      else
			  SAVE_VALUES(VALUES_1(Nil));
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Frame_projecting);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qvertical;           /* vertical */

static Object Qslice_size;         /* slice-size */

static Object Qgraphics;           /* graphics */

static Object Qhorizontal;         /* horizontal */

static Object Qframe_section;      /* frame-section */

static Object Qborder;             /* border */

static Object Qpaper;              /* paper */

static Object Qscroll_bar;         /* scroll-bar */

static Object Qtitle_bar;          /* title-bar */

static Object Qresize_box;         /* resize-box */

static Object Qclose_box;          /* close-box */

static Object Qelevator_shaft;     /* elevator-shaft */

static Object Qup_arrow;           /* up-arrow */

static Object Qdown_arrow;         /* down-arrow */

static Object Qleft_arrow;         /* left-arrow */

static Object Qright_arrow;        /* right-arrow */

/* PROJECT-FRAME-1 */
Object project_frame_1(partition_details_of_current_branch_of_frame)
    Object partition_details_of_current_branch_of_frame;
{
    Object remaining_space_for_variable_size_pieces_of_frame;
    Object remaining_number_of_size_pieces_of_frame, chunk_size_qm;
    Object ab_loop_list_, decff_1_arg, temp, graphics_pop_store, cons_1;
    Object next_cons, temp_1;
    Object partition_details_of_current_branch_of_frame_old_value, temp_2;
    Object chunk_size_spec, chunk_size, var_chunk_size, first_old_value;
    Object instruction, layout_specification, partition_details, slice_size;
    Object current_slice_size_qm, branch_frame_description;
    Object bottom_edge_of_frame, orientation_of_frame, top_edge_of_frame;
    Object left_edge_of_frame, right_edge_of_frame;
    Declare_special(6);
    Object result;

    x_note_fn_call(89,84);
    PUSH_SPECIAL_WITH_SYMBOL(Partition_details_of_current_branch_of_frame,Qpartition_details_of_current_branch_of_frame,partition_details_of_current_branch_of_frame,
	    5);
      remaining_space_for_variable_size_pieces_of_frame = 
	      EQ(Orientation_of_frame,Qvertical) ? 
	      FIXNUM_MINUS(Bottom_edge_of_frame,Top_edge_of_frame) : 
	      FIXNUM_MINUS(Right_edge_of_frame,Left_edge_of_frame);
      remaining_number_of_size_pieces_of_frame = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Remaining_number_of_size_pieces_of_frame,Qremaining_number_of_size_pieces_of_frame,remaining_number_of_size_pieces_of_frame,
	      4);
	PUSH_SPECIAL_WITH_SYMBOL(Remaining_space_for_variable_size_pieces_of_frame,Qremaining_space_for_variable_size_pieces_of_frame,remaining_space_for_variable_size_pieces_of_frame,
		3);
	  chunk_size_qm = Nil;
	  ab_loop_list_ = Partition_details_of_current_branch_of_frame;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  chunk_size_qm = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (EQ(Qslice_size,chunk_size_qm))
	      chunk_size_qm = Current_slice_size_qm;
	  if (chunk_size_qm) {
	      decff_1_arg = chunk_size_qm;
	      temp = 
		      FIXNUM_MINUS(Remaining_space_for_variable_size_pieces_of_frame,
		      decff_1_arg);
	      Remaining_space_for_variable_size_pieces_of_frame = temp;
	  }
	  else {
	      temp = FIXNUM_ADD1(Remaining_number_of_size_pieces_of_frame);
	      Remaining_number_of_size_pieces_of_frame = temp;
	  }
	  goto next_loop;
	end_loop:;
	next_loop_1:
	  if ( !TRUEP(FIRST(Control_stack_of_frame_projecting))) {
	      graphics_pop_store = Nil;
	      cons_1 = Control_stack_of_frame_projecting;
	      if (cons_1) {
		  graphics_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qgraphics);
		  if (ISVREF(Available_graphics_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = ISVREF(Available_graphics_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_graphics_conses_tail_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		  }
		  else {
		      temp = Available_graphics_conses_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		      temp = Available_graphics_conses_tail_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Control_stack_of_frame_projecting = next_cons;
	      result = VALUES_1(Nil);
	      goto end_1;
	  }
	  if (Partition_details_of_current_branch_of_frame) {
	      partition_details_of_current_branch_of_frame_old_value = 
		      Partition_details_of_current_branch_of_frame;
	      temp_2 = 
		      FIRST(partition_details_of_current_branch_of_frame_old_value);
	      temp = 
		      REST(partition_details_of_current_branch_of_frame_old_value);
	      Partition_details_of_current_branch_of_frame = temp;
	      chunk_size_spec = temp_2;
	      if (EQ(Qslice_size,chunk_size_spec))
		  chunk_size = Current_slice_size_qm;
	      else if (FIXNUMP(chunk_size_spec))
		  chunk_size = chunk_size_spec;
	      else {
		  var_chunk_size = 
			  ltruncate(Remaining_space_for_variable_size_pieces_of_frame,
			  Remaining_number_of_size_pieces_of_frame);
		  temp = FIXNUM_SUB1(Remaining_number_of_size_pieces_of_frame);
		  Remaining_number_of_size_pieces_of_frame = temp;
		  decff_1_arg = var_chunk_size;
		  temp = 
			  FIXNUM_MINUS(Remaining_space_for_variable_size_pieces_of_frame,
			  decff_1_arg);
		  Remaining_space_for_variable_size_pieces_of_frame = temp;
		  chunk_size = var_chunk_size;
	      }
	      if (EQ(Orientation_of_frame,Qvertical))
		  Bottom_edge_of_frame = FIXNUM_ADD(Top_edge_of_frame,
			  chunk_size);
	      else if (EQ(Orientation_of_frame,Qhorizontal))
		  Right_edge_of_frame = FIXNUM_ADD(Left_edge_of_frame,
			  chunk_size);
	  }
	  temp = Control_stack_of_frame_projecting;
	  first_old_value = FIRST(temp);
	  temp_2 = FIRST(first_old_value);
	  temp_1 = REST(first_old_value);
	  M_FIRST(temp) = temp_1;
	  instruction = temp_2;
	  if (EQ(FIRST(instruction),Qframe_section) || frame_interesting_p()) {
	      temp_2 = FIRST(instruction);
	      if (EQ(temp_2,Qframe_section)) {
		  layout_specification = SECOND(instruction);
		  partition_details = CDDR(layout_specification);
		  slice_size = SECOND(layout_specification);
		  current_slice_size_qm = EQ(slice_size,Qslice_size) ? 
			  Current_slice_size_qm : slice_size;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_slice_size_qm,Qcurrent_slice_size_qm,current_slice_size_qm,
			  2);
		    branch_frame_description = CDDR(instruction);
		    temp_2 = FIRST(layout_specification);
		    if (EQ(temp_2,Qtop)) {
			bottom_edge_of_frame = 
				FIXNUM_ADD(Top_edge_of_frame,
				Current_slice_size_qm);
			orientation_of_frame = Qhorizontal;
			PUSH_SPECIAL_WITH_SYMBOL(Orientation_of_frame,Qorientation_of_frame,orientation_of_frame,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
				  0);
			    if (frame_interesting_p()) {
				Control_stack_of_frame_projecting = 
					graphics_cons_1(branch_frame_description,
					Control_stack_of_frame_projecting);
				project_frame_2(partition_details);
			    }
			    Top_edge_of_frame = Bottom_edge_of_frame;
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else if (EQ(temp_2,Qbottom)) {
			top_edge_of_frame = 
				FIXNUM_MINUS(Bottom_edge_of_frame,
				Current_slice_size_qm);
			orientation_of_frame = Qhorizontal;
			PUSH_SPECIAL_WITH_SYMBOL(Orientation_of_frame,Qorientation_of_frame,orientation_of_frame,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
				  0);
			    if (frame_interesting_p()) {
				Control_stack_of_frame_projecting = 
					graphics_cons_1(branch_frame_description,
					Control_stack_of_frame_projecting);
				project_frame_2(partition_details);
			    }
			    Bottom_edge_of_frame = Top_edge_of_frame;
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else if (EQ(temp_2,Qright)) {
			left_edge_of_frame = 
				FIXNUM_MINUS(Right_edge_of_frame,
				Current_slice_size_qm);
			orientation_of_frame = Qvertical;
			PUSH_SPECIAL_WITH_SYMBOL(Orientation_of_frame,Qorientation_of_frame,orientation_of_frame,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
				  0);
			    if (frame_interesting_p()) {
				Control_stack_of_frame_projecting = 
					graphics_cons_1(branch_frame_description,
					Control_stack_of_frame_projecting);
				project_frame_2(partition_details);
			    }
			    Right_edge_of_frame = Left_edge_of_frame;
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    else if (EQ(temp_2,Qleft)) {
			right_edge_of_frame = 
				FIXNUM_ADD(Left_edge_of_frame,
				Current_slice_size_qm);
			orientation_of_frame = Qvertical;
			PUSH_SPECIAL_WITH_SYMBOL(Orientation_of_frame,Qorientation_of_frame,orientation_of_frame,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
				  0);
			    if (frame_interesting_p()) {
				Control_stack_of_frame_projecting = 
					graphics_cons_1(branch_frame_description,
					Control_stack_of_frame_projecting);
				project_frame_2(partition_details);
			    }
			    Left_edge_of_frame = Right_edge_of_frame;
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		  POP_SPECIAL();
	      }
	      else if (EQ(temp_2,Qborder))
		  project_border_for_frame(REST(instruction));
	      else if (EQ(temp_2,Qpaper))
		  project_paper_for_frame();
	      else if (EQ(temp_2,Qscroll_bar))
		  project_scroll_bar_for_frame();
	      else if (EQ(temp_2,Qtitle_bar))
		  project_title_bar_for_frame(SECOND(instruction));
	      else if (EQ(temp_2,Qresize_box))
		  project_resize_box_for_frame();
	      else if (EQ(temp_2,Qclose_box))
		  project_close_box_for_frame(SECOND(instruction));
	      else if (EQ(temp_2,Qelevator_shaft))
		  project_shaft_of_scroll_bar_for_frame();
	      else if (EQ(temp_2,Qup_arrow))
		  project_arrow_of_scroll_bar_for_frame(Qup);
	      else if (EQ(temp_2,Qdown_arrow))
		  project_arrow_of_scroll_bar_for_frame(Qdown);
	      else if (EQ(temp_2,Qleft_arrow))
		  project_arrow_of_scroll_bar_for_frame(Qleft);
	      else if (EQ(temp_2,Qright_arrow))
		  project_arrow_of_scroll_bar_for_frame(Qright);
	  }
	  if (EQ(Orientation_of_frame,Qvertical))
	      Top_edge_of_frame = Bottom_edge_of_frame;
	  else if (EQ(Orientation_of_frame,Qhorizontal))
	      Left_edge_of_frame = Right_edge_of_frame;
	  goto next_loop_1;
	end_loop_1:
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* PROJECT-FRAME-2 */
Object project_frame_2(partition_details)
    Object partition_details;
{
    Object left_edge_of_frame, top_edge_of_frame, right_edge_of_frame;
    Object bottom_edge_of_frame;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,85);
    left_edge_of_frame = Left_edge_of_frame;
    top_edge_of_frame = Top_edge_of_frame;
    right_edge_of_frame = Right_edge_of_frame;
    bottom_edge_of_frame = Bottom_edge_of_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
	      2);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
		  0);
	    result = project_frame_1(partition_details);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_create_frame_description_reference_1, Qcurrent_create_frame_description_reference_1);

static Object Qcreate_frame_description_reference_1;  /* create-frame-description-reference-1 */

/* CREATE-FRAME-DESCRIPTION-REFERENCE */
Object create_frame_description_reference(frame_description)
    Object frame_description;
{
    Object current_create_frame_description_reference_1, temp;
    Declare_special(1);

    x_note_fn_call(89,86);
    current_create_frame_description_reference_1 = 
	    make_frame_description_reference_1(frame_description);
    PUSH_SPECIAL_WITH_SYMBOL(Current_create_frame_description_reference_1,Qcurrent_create_frame_description_reference_1,current_create_frame_description_reference_1,
	    0);
      project_frame(Qcompute_content_region,frame_description,
	      FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)0L),
	      FIX((SI_Long)0L),
	      SYMBOL_FUNCTION(Qcreate_frame_description_reference_1));
      temp = Current_create_frame_description_reference_1;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CREATE-FRAME-DESCRIPTION-REFERENCE-1 */
Object create_frame_description_reference_1()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(89,87);
    svref_arg_1 = Current_create_frame_description_reference_1;
    svref_new_value = Left_edge_of_frame;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    svref_arg_1 = Current_create_frame_description_reference_1;
    svref_new_value = Top_edge_of_frame;
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    svref_arg_1 = Current_create_frame_description_reference_1;
    svref_new_value = FIXNUM_NEGATE(Right_edge_of_frame);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    svref_arg_1 = Current_create_frame_description_reference_1;
    svref_new_value = FIXNUM_NEGATE(Bottom_edge_of_frame);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* MOVE-ELEVATOR */
Object move_elevator(block,new_position_of_horizontal_elevator,
	    new_position_of_vertical_elevator)
    Object block, new_position_of_horizontal_elevator;
    Object new_position_of_vertical_elevator;
{
    Object block_of_frame, new_position_of_horizontal_elevator_of_frame;
    Object new_position_of_vertical_elevator_of_frame;
    Object frame_transforms_of_block_qm, temp, any_frame_transform_of_frame;
    Object frame_description_reference, gensymed_symbol, left_edge_of_frame;
    Object top_edge_of_frame, right_edge_of_frame, bottom_edge_of_frame;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(89,88);
    SAVE_STACK();
    LOCK(Frame_projecting);
    if (PUSH_UNWIND_PROTECT(0)) {
	block_of_frame = block;
	new_position_of_horizontal_elevator_of_frame = 
		new_position_of_horizontal_elevator;
	new_position_of_vertical_elevator_of_frame = 
		new_position_of_vertical_elevator;
	PUSH_SPECIAL_WITH_SYMBOL(New_position_of_vertical_elevator_of_frame,Qnew_position_of_vertical_elevator_of_frame,new_position_of_vertical_elevator_of_frame,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(New_position_of_horizontal_elevator_of_frame,Qnew_position_of_horizontal_elevator_of_frame,new_position_of_horizontal_elevator_of_frame,
		  5);
	    PUSH_SPECIAL_WITH_SYMBOL(Block_of_frame,Qblock_of_frame,block_of_frame,
		    4);
	      frame_transforms_of_block_qm = 
		      get_lookup_slot_value_given_default(block,
		      Qframe_transforms_of_block,Nil);
	      if ( !TRUEP(frame_transforms_of_block_qm)) {
		  update_elevator_positions_of_block_1(Qvertical);
		  SAVE_VALUES(update_elevator_positions_of_block_1(Qhorizontal));
	      }
	      else {
		  temp = FIRST(frame_transforms_of_block_qm);
		  any_frame_transform_of_frame = CDR(temp);
		  frame_description_reference = 
			  ISVREF(any_frame_transform_of_frame,(SI_Long)5L);
		  gensymed_symbol = ISVREF(block,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)0L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = 
			  IFIX(ISVREF(frame_description_reference,
			  (SI_Long)4L));
		  left_edge_of_frame = FIX(gensymed_symbol_1 - 
			  gensymed_symbol_2);
		  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
			  3);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = 
			    IFIX(ISVREF(frame_description_reference,
			    (SI_Long)5L));
		    top_edge_of_frame = FIX(gensymed_symbol_1 - 
			    gensymed_symbol_2);
		    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
			    2);
		      gensymed_symbol = ISVREF(block,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)2L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = 
			      IFIX(ISVREF(frame_description_reference,
			      (SI_Long)6L));
		      right_edge_of_frame = FIX(gensymed_symbol_1 + 
			      gensymed_symbol_2);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
			      1);
			gensymed_symbol = ISVREF(block,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)3L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_1 = IFIX(gensymed_symbol);
			gensymed_symbol_2 = 
				IFIX(ISVREF(frame_description_reference,
				(SI_Long)7L));
			bottom_edge_of_frame = FIX(gensymed_symbol_1 + 
				gensymed_symbol_2);
			PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
				0);
			  SAVE_VALUES(project_frame(Qmove_elevator,
				  ISVREF(frame_description_reference,
				  (SI_Long)2L),Left_edge_of_frame,
				  Top_edge_of_frame,Right_edge_of_frame,
				  Bottom_edge_of_frame,Nil));
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Frame_projecting);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qdraw_block;         /* draw-block */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* MOVE-ELEVATOR-WITHIN-SHAFT */
Object move_elevator_within_shaft(left_of_elevator,top_of_elevator,
	    right_of_elevator,bottom_of_elevator)
    Object left_of_elevator, top_of_elevator, right_of_elevator;
    Object bottom_of_elevator;
{
    Object left_edge_of_new_elevator, top_edge_of_new_elevator;
    Object right_edge_of_new_elevator, bottom_edge_of_new_elevator;
    Object region_invalidation_is_preferred, workspace;
    Object current_drawing_priority;
    Declare_special(2);
    Object result;

    x_note_fn_call(89,89);
    result = edges_of_elevator(Orientation_of_frame,Left_edge_of_frame,
	    Top_edge_of_frame,Right_edge_of_frame,Bottom_edge_of_frame,
	    EQ(Orientation_of_frame,Qvertical) ? 
	    New_position_of_vertical_elevator_of_frame : 
	    New_position_of_horizontal_elevator_of_frame);
    MVS_4(result,left_edge_of_new_elevator,top_edge_of_new_elevator,
	    right_edge_of_new_elevator,bottom_edge_of_new_elevator);
    region_invalidation_is_preferred = T;
    workspace = get_workspace_if_any(Block_of_frame);
    PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
	    1);
      current_drawing_priority = Kdraw_as_late_as_possible;
      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	      0);
	update_images(10,T,Block_of_frame,workspace,left_of_elevator,
		top_of_elevator,FIXNUM_ADD1(right_of_elevator),
		FIXNUM_ADD1(bottom_of_elevator),Nil,Qdraw_block,
		Block_of_frame);
	update_images(10,T,Block_of_frame,workspace,
		left_edge_of_new_elevator,top_edge_of_new_elevator,
		FIXNUM_ADD1(right_edge_of_new_elevator),
		FIXNUM_ADD1(bottom_edge_of_new_elevator),Nil,Qdraw_block,
		Block_of_frame);
	update_elevator_positions_of_block_1(Orientation_of_frame);
	update_images(10,Nil,Block_of_frame,workspace,left_of_elevator,
		top_of_elevator,FIXNUM_ADD1(right_of_elevator),
		FIXNUM_ADD1(bottom_of_elevator),Nil,Qdraw_block,
		Block_of_frame);
	update_images(10,Nil,Block_of_frame,workspace,
		left_edge_of_new_elevator,top_edge_of_new_elevator,
		FIXNUM_ADD1(right_edge_of_new_elevator),
		FIXNUM_ADD1(bottom_edge_of_new_elevator),Nil,Qdraw_block,
		Block_of_frame);
      POP_SPECIAL();
      if (EQ(Current_drawing_priority,Kdraw_as_soon_as_possible))
	  result = force_process_drawing();
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qposition_of_horizontal_elevator;  /* position-of-horizontal-elevator */

static Object Qposition_of_vertical_elevator;  /* position-of-vertical-elevator */

/* UPDATE-ELEVATOR-POSITIONS-OF-BLOCK-1 */
Object update_elevator_positions_of_block_1(orientation)
    Object orientation;
{
    x_note_fn_call(89,90);
    if (EQ(orientation,Qhorizontal)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Block_of_frame,
		    Qposition_of_horizontal_elevator);
	set_lookup_slot_value_1(Block_of_frame,
		Qposition_of_horizontal_elevator,
		New_position_of_horizontal_elevator_of_frame);
    }
    if (EQ(orientation,Qvertical)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Block_of_frame,
		    Qposition_of_vertical_elevator);
	return set_lookup_slot_value_1(Block_of_frame,
		Qposition_of_vertical_elevator,
		New_position_of_vertical_elevator_of_frame);
    }
    else
	return VALUES_1(Nil);
}

/* GENERATE-WORKSPACE-BACKGROUND-SPOT */
Object generate_workspace_background_spot(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(89,91);
    push_last_spot(mouse_pointer,make_workspace_background_spot_1(),
	    ISVREF(ISVREF(mouse_pointer,(SI_Long)5L),(SI_Long)4L));
    return VALUES_1(Nil);
}

/* TRACK-MOUSE-OVER-FRAME */
Object track_mouse_over_frame(mouse_pointer,frame_description,block,left,
	    top,right,bottom)
    Object mouse_pointer, frame_description, block, left, top, right, bottom;
{
    Object block_of_frame, mouse_pointer_of_frame;
    Object original_head_of_stack_of_spots, maximum_time_slice_size;
    Object priority_of_next_task, svref_arg_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(89,92);
    SAVE_STACK();
    LOCK(Frame_projecting);
    if (PUSH_UNWIND_PROTECT(0)) {
	block_of_frame = block;
	mouse_pointer_of_frame = mouse_pointer;
	PUSH_SPECIAL_WITH_SYMBOL(Mouse_pointer_of_frame,Qmouse_pointer_of_frame,mouse_pointer_of_frame,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Block_of_frame,Qblock_of_frame,block_of_frame,
		  2);
	    original_head_of_stack_of_spots = 
		    ISVREF(Mouse_pointer_of_frame,(SI_Long)5L);
	    maximum_time_slice_size = Most_positive_fixnum;
	    priority_of_next_task = Most_positive_fixnum;
	    PUSH_SPECIAL_WITH_SYMBOL(Priority_of_next_task,Qpriority_of_next_task,priority_of_next_task,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
		      0);
		project_frame(Qmouse_tracking,frame_description,left,top,
			right,bottom,Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    if ( !EQ(original_head_of_stack_of_spots,
		    ISVREF(Mouse_pointer_of_frame,(SI_Long)5L))) {
		svref_arg_1 = ISVREF(Mouse_pointer_of_frame,(SI_Long)5L);
		SAVE_VALUES(VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)3L)) = 
			Nil));
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Frame_projecting);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FRAME-RECTANGLE-WITH-CLIPPING */
Object frame_rectangle_with_clipping(pen_thickness)
    Object pen_thickness;
{
    Object scaled_x_pen_thickness, scaled_y_pen_thickness, scale, value;
    Object scaled_left_inner_edge, scaled_top_inner_edge;
    Object scaled_right_inner_edge, scaled_bottom_inner_edge, color_difference;
    Object d_1, c_1, b_1, a_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long scaled_left_edge_of_frame, scaled_top_edge_of_frame;
    SI_Long scaled_right_edge_of_frame, scaled_bottom_edge_of_frame, temp, a;
    SI_Long c, b, d;

    x_note_fn_call(89,93);
    if ( !((SI_Long)0L == IFIX(pen_thickness))) {
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	scaled_left_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	scaled_top_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	scaled_right_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	scaled_bottom_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    scaled_x_pen_thickness = pen_thickness;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		pen_thickness) && FIXNUM_LT(pen_thickness,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    pen_thickness)) + (SI_Long)2048L;
	    scaled_x_pen_thickness = FIX(unshifted_result >>  -  - 
		    (SI_Long)12L);
	}
	else
	    scaled_x_pen_thickness = scalef_function(Current_image_x_scale,
		    pen_thickness);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    scaled_y_pen_thickness = pen_thickness;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		pen_thickness) && FIXNUM_LT(pen_thickness,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    pen_thickness)) + (SI_Long)2048L;
	    scaled_y_pen_thickness = FIX(unshifted_result >>  -  - 
		    (SI_Long)12L);
	}
	else
	    scaled_y_pen_thickness = scalef_function(Current_image_y_scale,
		    pen_thickness);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = FIXNUM_ADD(Left_edge_of_frame,pen_thickness);
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
	scaled_left_inner_edge = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = FIXNUM_ADD(Top_edge_of_frame,pen_thickness);
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
	scaled_top_inner_edge = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = FIXNUM_MINUS(Right_edge_of_frame,pen_thickness);
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
	scaled_right_inner_edge = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = FIXNUM_MINUS(Bottom_edge_of_frame,pen_thickness);
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
	scaled_bottom_inner_edge = FIX(gensymed_symbol + gensymed_symbol_1);
	color_difference = FIXNUM_LOGXOR(Current_foreground_color_value,
		Current_background_color_value);
	if (scaled_left_edge_of_frame >= scaled_right_edge_of_frame - 
		IFIX(scaled_x_pen_thickness) - 
		IFIX(scaled_x_pen_thickness) || scaled_top_edge_of_frame 
		>= scaled_bottom_edge_of_frame - 
		IFIX(scaled_x_pen_thickness) - IFIX(scaled_y_pen_thickness)) {
	    if ( !(scaled_left_edge_of_frame == scaled_right_edge_of_frame 
		    || scaled_top_edge_of_frame == 
		    scaled_bottom_edge_of_frame)) {
		temp = IFIX(Left_edge_of_draw_area);
		a = MAX(scaled_left_edge_of_frame,temp);
		temp = IFIX(Right_edge_of_draw_area);
		c = MIN(scaled_right_edge_of_frame,temp);
		if (a < c) {
		    temp = IFIX(Top_edge_of_draw_area);
		    b = MAX(scaled_top_edge_of_frame,temp);
		    temp = IFIX(Bottom_edge_of_draw_area);
		    d = MIN(scaled_bottom_edge_of_frame,temp);
		    if (b < d)
			return draw_graphic_element(6,Qadd_solid_rectangle,
				FIX(a),FIX(b),FIX(c),FIX(d),color_difference);
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    if (scaled_left_edge_of_frame == IFIX(scaled_left_inner_edge))
		scaled_left_inner_edge = FIXNUM_ADD1(scaled_left_inner_edge);
	    if (scaled_top_edge_of_frame == IFIX(scaled_top_inner_edge))
		scaled_top_inner_edge = FIXNUM_ADD1(scaled_top_inner_edge);
	    if (scaled_right_edge_of_frame == IFIX(scaled_right_inner_edge))
		scaled_right_inner_edge = FIXNUM_SUB1(scaled_right_inner_edge);
	    if (scaled_bottom_edge_of_frame == IFIX(scaled_bottom_inner_edge))
		scaled_bottom_inner_edge = 
			FIXNUM_SUB1(scaled_bottom_inner_edge);
	    temp = IFIX(Left_edge_of_draw_area);
	    a = MAX(scaled_left_edge_of_frame,temp);
	    temp = IFIX(Right_edge_of_draw_area);
	    c = MIN(scaled_right_edge_of_frame,temp);
	    if (a < c) {
		temp = IFIX(Top_edge_of_draw_area);
		b = MAX(scaled_top_edge_of_frame,temp);
		d_1 = FIXNUM_MIN(scaled_top_inner_edge,
			Bottom_edge_of_draw_area);
		if (b < IFIX(d_1))
		    draw_graphic_element(6,Qadd_solid_rectangle,FIX(a),
			    FIX(b),FIX(c),d_1,color_difference);
	    }
	    temp = IFIX(Left_edge_of_draw_area);
	    a = MAX(scaled_left_edge_of_frame,temp);
	    c_1 = FIXNUM_MIN(scaled_left_inner_edge,Right_edge_of_draw_area);
	    if (a < IFIX(c_1)) {
		b_1 = FIXNUM_MAX(scaled_top_inner_edge,Top_edge_of_draw_area);
		d_1 = FIXNUM_MIN(scaled_bottom_inner_edge,
			Bottom_edge_of_draw_area);
		if (FIXNUM_LT(b_1,d_1))
		    draw_graphic_element(6,Qadd_solid_rectangle,FIX(a),b_1,
			    c_1,d_1,color_difference);
	    }
	    a_1 = FIXNUM_MAX(scaled_right_inner_edge,Left_edge_of_draw_area);
	    temp = IFIX(Right_edge_of_draw_area);
	    c = MIN(scaled_right_edge_of_frame,temp);
	    if (IFIX(a_1) < c) {
		b_1 = FIXNUM_MAX(scaled_top_inner_edge,Top_edge_of_draw_area);
		d_1 = FIXNUM_MIN(scaled_bottom_inner_edge,
			Bottom_edge_of_draw_area);
		if (FIXNUM_LT(b_1,d_1))
		    draw_graphic_element(6,Qadd_solid_rectangle,a_1,b_1,
			    FIX(c),d_1,color_difference);
	    }
	    temp = IFIX(Left_edge_of_draw_area);
	    a = MAX(scaled_left_edge_of_frame,temp);
	    temp = IFIX(Right_edge_of_draw_area);
	    c = MIN(scaled_right_edge_of_frame,temp);
	    if (a < c) {
		b_1 = FIXNUM_MAX(scaled_bottom_inner_edge,
			Top_edge_of_draw_area);
		temp = IFIX(Bottom_edge_of_draw_area);
		d = MIN(scaled_bottom_edge_of_frame,temp);
		if (IFIX(b_1) < d)
		    return draw_graphic_element(6,Qadd_solid_rectangle,
			    FIX(a),b_1,FIX(c),FIX(d),color_difference);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* PAINT-RECTANGLE-WITH-CLIPPING */
Object paint_rectangle_with_clipping()
{
    Object color_difference;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long scaled_left_edge_of_frame, scaled_top_edge_of_frame;
    SI_Long scaled_right_edge_of_frame, scaled_bottom_edge_of_frame, temp, a;
    SI_Long c, b, d;

    x_note_fn_call(89,94);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(Left_edge_of_frame);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		Left_edge_of_frame)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		Left_edge_of_frame));
    scaled_left_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(Top_edge_of_frame);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		Top_edge_of_frame)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		Top_edge_of_frame));
    scaled_top_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(Right_edge_of_frame);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		Right_edge_of_frame)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		Right_edge_of_frame));
    scaled_right_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		Bottom_edge_of_frame)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		Bottom_edge_of_frame));
    scaled_bottom_edge_of_frame = gensymed_symbol + gensymed_symbol_1;
    color_difference = FIXNUM_LOGXOR(Current_foreground_color_value,
	    Current_background_color_value);
    temp = IFIX(Left_edge_of_draw_area);
    a = MAX(scaled_left_edge_of_frame,temp);
    temp = IFIX(Right_edge_of_draw_area);
    c = MIN(scaled_right_edge_of_frame,temp);
    if (a < c) {
	temp = IFIX(Top_edge_of_draw_area);
	b = MAX(scaled_top_edge_of_frame,temp);
	temp = IFIX(Bottom_edge_of_draw_area);
	d = MIN(scaled_bottom_edge_of_frame,temp);
	if (b < d)
	    return draw_graphic_element(6,Qadd_solid_rectangle,FIX(a),
		    FIX(b),FIX(c),FIX(d),color_difference);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdim_gray;           /* dim-gray */

/* IMAGE-PLANE-BORDER-COLOR */
Object image_plane_border_color(image_plane,color,index_1)
    Object image_plane, color, index_1;
{
    x_note_fn_call(89,95);
    if (IFIX(index_1) > (SI_Long)0L ||  !TRUEP(selection_enabled_p(1,
	    ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L))) ||  
	    !TRUEP(selectable_image_plane_p(image_plane)) || 
	    image_plane_selected_p(image_plane))
	return VALUES_1(color);
    else
	return VALUES_1(Qdim_gray);
}

static Object Qframe;              /* frame */

static Object Qdrop_shadow;        /* drop-shadow */

/* PROJECT-BORDER-FOR-FRAME */
Object project_border_for_frame(border_description)
    Object border_description;
{
    Object symmetric_indent, drop_shadow_indent, kind, size, ab_loop_list_;
    Object ab_loop_desetq_, temp, incff_1_arg, color;
    Object current_foreground_color_value, ab_loop_iter_flag_;
    Object color_or_metacolor, decff_1_arg, temp_1, point_x, point_y;
    SI_Long index_1, gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left, top, right, bottom;
    Declare_special(1);

    x_note_fn_call(89,96);
    symmetric_indent = FIX((SI_Long)0L);
    drop_shadow_indent = FIX((SI_Long)0L);
    kind = Nil;
    size = Nil;
    ab_loop_list_ = border_description;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    kind = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    size = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(kind,Qframe)) {
	incff_1_arg = size;
	symmetric_indent = FIXNUM_ADD(symmetric_indent,incff_1_arg);
    }
    else if (EQ(kind,Qdrop_shadow)) {
	incff_1_arg = size;
	drop_shadow_indent = FIXNUM_ADD(drop_shadow_indent,incff_1_arg);
    }
    goto next_loop;
  end_loop:;
    if (EQ(Purpose_of_frame_projecting,Qdrawing) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_paper)) {
	kind = Nil;
	color = Nil;
	size = Nil;
	ab_loop_list_ = border_description;
	index_1 = (SI_Long)0L;
	current_foreground_color_value = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
		0);
	  ab_loop_iter_flag_ = T;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  kind = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  color = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  size = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      index_1 = index_1 + (SI_Long)1L;
	  color_or_metacolor = 
		  image_plane_border_color(Current_image_plane,color,
		  FIX(index_1));
	  if (EQ(color_or_metacolor,Qbackground))
	      Current_foreground_color_value = Current_background_color_value;
	  else if (EQ(color_or_metacolor,Qforeground) || 
		  EQ(color_or_metacolor,Qworkspace_foreground));
	  else if (EQ(color_or_metacolor,Qtransparent))
	      Current_foreground_color_value = Current_background_color_value;
	  else
	      Current_foreground_color_value = 
		      map_to_color_value(color_or_metacolor);
	  if (EQ(kind,Qframe)) {
	      if ( !EQ(Qtransparent,color))
		  frame_rectangle_with_clipping(size);
	      indent_frame(size);
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop_1;
	end_loop_1:;
	POP_SPECIAL();
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents));
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region) || 
	    EQ(Purpose_of_frame_projecting,Qmove_elevator)) {
	indent_frame(symmetric_indent);
	decff_1_arg = drop_shadow_indent;
	temp_1 = FIXNUM_MINUS(Right_edge_of_frame,decff_1_arg);
	Right_edge_of_frame = temp_1;
	decff_1_arg = drop_shadow_indent;
	temp_1 = FIXNUM_MINUS(Bottom_edge_of_frame,decff_1_arg);
	Bottom_edge_of_frame = temp_1;
    }
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	indent_frame(symmetric_indent);
	decff_1_arg = drop_shadow_indent;
	temp_1 = FIXNUM_MINUS(Right_edge_of_frame,decff_1_arg);
	Right_edge_of_frame = temp_1;
	decff_1_arg = drop_shadow_indent;
	temp_1 = FIXNUM_MINUS(Bottom_edge_of_frame,decff_1_arg);
	Bottom_edge_of_frame = temp_1;
	point_x = ISVREF(Mouse_pointer_of_frame,(SI_Long)2L);
	point_y = ISVREF(Mouse_pointer_of_frame,(SI_Long)3L);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	left = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	top = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	right = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	bottom = gensymed_symbol + gensymed_symbol_1;
	if ( !(left <= IFIX(point_x) && IFIX(point_x) < right && top <= 
		IFIX(point_y) && IFIX(point_y) < bottom))
	    push_last_spot(Mouse_pointer_of_frame,
		    make_workspace_background_spot_1(),Block_of_frame);
    }
    return VALUES_1(Nil);
}

/* PROJECT-PAPER-FOR-FRAME */
Object project_paper_for_frame()
{
    Object temp, temp_1, temp_2, temp_3;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;

    x_note_fn_call(89,97);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper)) {
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	temp = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	temp_1 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	sketch_paper_for_current_image_plane(temp,temp_1,temp_2,
		FIX(gensymed_symbol + gensymed_symbol_1));
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing)) {
	temp_3 = Drawing_state_for_project_paper;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Left_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Left_edge_of_frame) && FIXNUM_LT(Left_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Left_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Left_edge_of_frame));
	temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Top_edge_of_frame) && FIXNUM_LT(Top_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Top_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Top_edge_of_frame));
	temp_1 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Right_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Right_edge_of_frame) && FIXNUM_LT(Right_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Right_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    Right_edge_of_frame));
	temp = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(Bottom_edge_of_frame);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Bottom_edge_of_frame) && FIXNUM_LT(Bottom_edge_of_frame,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    Bottom_edge_of_frame)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    Bottom_edge_of_frame));
	Drawing_state_for_project_paper = 
		draw_paper_for_current_image_plane(temp_3,temp_2,temp_1,
		temp,FIX(gensymed_symbol + gensymed_symbol_1));
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents));
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region));
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator));
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking));
    return VALUES_1(Nil);
}

/* TILED-IMAGE-SPEC-FOR-IMAGE-PLANE */
Object tiled_image_spec_for_image_plane(image_plane)
    Object image_plane;
{
    Object image_spec, ab_loop_list_;

    x_note_fn_call(89,98);
    image_spec = Nil;
    ab_loop_list_ = image_plane_background_images(image_plane);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(image_spec) && FOURTH(image_spec))
	return VALUES_1(image_spec);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SKETCH-PAPER-FOR-CURRENT-IMAGE-PLANE */
Object sketch_paper_for_current_image_plane(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object left_edge_of_draw_area, right_edge_of_draw_area;
    Object top_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, color_or_metacolor;
    Object background_color_value, temp, background_color_or_metacolor;
    Object tiled_image_spec_qm, tiled_image_data_qm, temp_1, temp_2, temp_3;
    Object temp_4;
    Declare_special(9);
    Object result;

    x_note_fn_call(89,99);
    left_edge_of_draw_area = FIXNUM_MAX(left,Left_edge_of_draw_area);
    right_edge_of_draw_area = FIXNUM_MIN(right,Right_edge_of_draw_area);
    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	    8);
      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
	      7);
	if (FIXNUM_LT(Left_edge_of_draw_area,Right_edge_of_draw_area)) {
	    top_edge_of_draw_area = FIXNUM_MAX(top,Top_edge_of_draw_area);
	    bottom_edge_of_draw_area = FIXNUM_MIN(bottom,
		    Bottom_edge_of_draw_area);
	    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		      5);
		if (FIXNUM_LT(Top_edge_of_draw_area,
			    Bottom_edge_of_draw_area)) {
		    current_frame_transform_qm = Nil;
		    current_image_x_scale = ISVREF(Current_image_plane,
			    (SI_Long)11L);
		    current_image_y_scale = ISVREF(Current_image_plane,
			    (SI_Long)12L);
		    current_x_origin_of_drawing = 
			    ISVREF(Current_image_plane,(SI_Long)13L);
		    current_y_origin_of_drawing = 
			    ISVREF(Current_image_plane,(SI_Long)14L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			    4);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			      3);
			PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				2);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				  1);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
				    0);
			      color_or_metacolor = 
				      ISVREF(Current_image_plane,
				      (SI_Long)5L) ? 
				      ISVREF(ISVREF(Current_image_plane,
				      (SI_Long)5L),(SI_Long)21L) : Nil;
			      if (color_or_metacolor);
			      else
				  color_or_metacolor = Qwhite;
			      if (EQ(color_or_metacolor,Qtransparent) || 
				      EQ(color_or_metacolor,Qbackground)) {
				  background_color_value = 
					  ISVREF(Current_color_map,
					  (SI_Long)5L);
				  if (background_color_value);
				  else
				      background_color_value = 
					      map_to_color_value_1(Qwhite);
			      }
			      else if (EQ(color_or_metacolor,Qforeground) 
				      || EQ(color_or_metacolor,
				      Qworkspace_foreground)) {
				  temp = ISVREF(Current_image_plane,
					  (SI_Long)5L) ? 
					  ISVREF(ISVREF(Current_image_plane,
					  (SI_Long)5L),(SI_Long)22L) : Nil;
				  if (temp);
				  else
				      temp = Qblack;
				  color_or_metacolor = temp;
				  if (EQ(color_or_metacolor,Qtransparent) 
					  || EQ(color_or_metacolor,
					  Qbackground)) {
				      background_color_or_metacolor = 
					      ISVREF(Current_image_plane,
					      (SI_Long)5L) ? 
					      ISVREF(ISVREF(Current_image_plane,
					      (SI_Long)5L),(SI_Long)21L) : Nil;
				      if (background_color_or_metacolor);
				      else
					  background_color_or_metacolor = 
						  Qwhite;
				      if (EQ(background_color_or_metacolor,
					      Qforeground) || 
					      EQ(background_color_or_metacolor,
					      Qworkspace_foreground)) {
					  background_color_value = 
						  ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (background_color_value);
					  else
					      background_color_value = 
						      map_to_color_value_1(Qblack);
				      }
				      else if (EQ(background_color_or_metacolor,
					      Qtransparent) || 
					      EQ(background_color_or_metacolor,
					      Qbackground)) {
					  background_color_value = 
						  ISVREF(Current_color_map,
						  (SI_Long)5L);
					  if (background_color_value);
					  else
					      background_color_value = 
						      map_to_color_value_1(Qwhite);
				      }
				      else
					  background_color_value = 
						  EQ(background_color_or_metacolor,
						  ISVREF(Current_color_map,
						  (SI_Long)6L)) ? 
						  ISVREF(Current_color_map,
						  (SI_Long)7L) : 
						  map_to_color_value_1(background_color_or_metacolor);
				  }
				  else if (EQ(color_or_metacolor,
					  Qforeground) || 
					  EQ(color_or_metacolor,
					  Qworkspace_foreground)) {
				      background_color_value = 
					      ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (background_color_value);
				      else
					  background_color_value = 
						  map_to_color_value_1(Qblack);
				  }
				  else
				      background_color_value = 
					      EQ(color_or_metacolor,
					      ISVREF(Current_color_map,
					      (SI_Long)6L)) ? 
					      ISVREF(Current_color_map,
					      (SI_Long)7L) : 
					      map_to_color_value_1(color_or_metacolor);
			      }
			      else
				  background_color_value = 
					  EQ(color_or_metacolor,
					  ISVREF(Current_color_map,
					  (SI_Long)6L)) ? 
					  ISVREF(Current_color_map,
					  (SI_Long)7L) : 
					  map_to_color_value_1(color_or_metacolor);
			      tiled_image_spec_qm = 
				      tiled_image_spec_for_image_plane(Current_image_plane);
			      tiled_image_data_qm = tiled_image_spec_qm ? 
				      find_image_data(FIRST(tiled_image_spec_qm)) 
				      : Qnil;
			      if (tiled_image_data_qm) {
				  if ( !(printing_window_p(Current_window) 
					  || 
					  FIXNUM_LT(Icp_window_protocol_supports_polychrome_icon_images,
					  ISVREF(Current_window,
					  (SI_Long)11L))))
				      paint_solid_rectangle(Left_edge_of_draw_area,
					      Top_edge_of_draw_area,
					      Right_edge_of_draw_area,
					      Bottom_edge_of_draw_area,
					      background_color_value);
				  temp = Current_image_plane;
				  temp_1 = SECOND(tiled_image_spec_qm);
				  temp_2 = THIRD(tiled_image_spec_qm);
				  temp_3 = CONSP(tiled_image_spec_qm) ? 
					  FOURTH(tiled_image_spec_qm) : Qnil;
				  color_or_metacolor = 
					  ISVREF(Current_image_plane,
					  (SI_Long)5L) ? 
					  ISVREF(ISVREF(Current_image_plane,
					  (SI_Long)5L),(SI_Long)22L) : Nil;
				  if (color_or_metacolor);
				  else
				      color_or_metacolor = Qblack;
				  if (EQ(color_or_metacolor,Qtransparent) 
					  || EQ(color_or_metacolor,
					  Qbackground)) {
				      background_color_or_metacolor = 
					      ISVREF(Current_image_plane,
					      (SI_Long)5L) ? 
					      ISVREF(ISVREF(Current_image_plane,
					      (SI_Long)5L),(SI_Long)21L) : Nil;
				      if (background_color_or_metacolor);
				      else
					  background_color_or_metacolor = 
						  Qwhite;
				      if (EQ(background_color_or_metacolor,
					      Qforeground) || 
					      EQ(background_color_or_metacolor,
					      Qworkspace_foreground)) {
					  temp_4 = 
						  ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (temp_4);
					  else
					      temp_4 = 
						      map_to_color_value_1(Qblack);
				      }
				      else if (EQ(background_color_or_metacolor,
					      Qtransparent) || 
					      EQ(background_color_or_metacolor,
					      Qbackground)) {
					  temp_4 = 
						  ISVREF(Current_color_map,
						  (SI_Long)5L);
					  if (temp_4);
					  else
					      temp_4 = 
						      map_to_color_value_1(Qwhite);
				      }
				      else
					  temp_4 = 
						  EQ(background_color_or_metacolor,
						  ISVREF(Current_color_map,
						  (SI_Long)6L)) ? 
						  ISVREF(Current_color_map,
						  (SI_Long)7L) : 
						  map_to_color_value_1(background_color_or_metacolor);
				  }
				  else if (EQ(color_or_metacolor,
					  Qforeground) || 
					  EQ(color_or_metacolor,
					  Qworkspace_foreground)) {
				      temp_4 = ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (temp_4);
				      else
					  temp_4 = 
						  map_to_color_value_1(Qblack);
				  }
				  else
				      temp_4 = EQ(color_or_metacolor,
					      ISVREF(Current_color_map,
					      (SI_Long)6L)) ? 
					      ISVREF(Current_color_map,
					      (SI_Long)7L) : 
					      map_to_color_value_1(color_or_metacolor);
				  draw_background_image(temp,
					  tiled_image_data_qm,temp_1,
					  temp_2,temp_3,left,top,right,
					  bottom,temp_4,
					  background_color_value);
			      }
			      else
				  paint_solid_rectangle(Left_edge_of_draw_area,
					  Top_edge_of_draw_area,
					  Right_edge_of_draw_area,
					  Bottom_edge_of_draw_area,
					  background_color_value);
			      if (visible_grid_p(Current_image_plane))
				  draw_alignment_grid(Left_edge_of_draw_area,
					  Top_edge_of_draw_area,
					  Right_edge_of_draw_area,
					  Bottom_edge_of_draw_area);
			      if (ISVREF(Current_image_plane,(SI_Long)37L))
				  result = paint_unused_area_of_native_image_plane(Current_image_plane);
			      else
				  result = VALUES_1(Nil);
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qimages;             /* images */

/* DRAW-PAPER-FOR-CURRENT-IMAGE-PLANE */
Object draw_paper_for_current_image_plane(state_qm,left,top,right,bottom)
    Object state_qm, left, top, right, bottom;
{
    Object left_edge_of_draw_area, right_edge_of_draw_area;
    Object top_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, color_or_metacolor;
    Object background_color_value, temp, background_color_or_metacolor;
    Object images_region, background_region, net_region;
    Declare_special(9);

    x_note_fn_call(89,100);
    left_edge_of_draw_area = FIXNUM_MAX(left,Left_edge_of_draw_area);
    right_edge_of_draw_area = FIXNUM_MIN(right,Right_edge_of_draw_area);
    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	    8);
      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
	      7);
	if (FIXNUM_LT(Left_edge_of_draw_area,Right_edge_of_draw_area)) {
	    top_edge_of_draw_area = FIXNUM_MAX(top,Top_edge_of_draw_area);
	    bottom_edge_of_draw_area = FIXNUM_MIN(bottom,
		    Bottom_edge_of_draw_area);
	    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		      5);
		if (FIXNUM_LT(Top_edge_of_draw_area,
			    Bottom_edge_of_draw_area)) {
		    current_frame_transform_qm = Nil;
		    current_image_x_scale = ISVREF(Current_image_plane,
			    (SI_Long)11L);
		    current_image_y_scale = ISVREF(Current_image_plane,
			    (SI_Long)12L);
		    current_x_origin_of_drawing = 
			    ISVREF(Current_image_plane,(SI_Long)13L);
		    current_y_origin_of_drawing = 
			    ISVREF(Current_image_plane,(SI_Long)14L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			    4);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			      3);
			PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				2);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				  1);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
				    0);
			      color_or_metacolor = 
				      ISVREF(Current_image_plane,
				      (SI_Long)5L) ? 
				      ISVREF(ISVREF(Current_image_plane,
				      (SI_Long)5L),(SI_Long)21L) : Nil;
			      if (color_or_metacolor);
			      else
				  color_or_metacolor = Qwhite;
			      if (EQ(color_or_metacolor,Qtransparent) || 
				      EQ(color_or_metacolor,Qbackground)) {
				  background_color_value = 
					  ISVREF(Current_color_map,
					  (SI_Long)5L);
				  if (background_color_value);
				  else
				      background_color_value = 
					      map_to_color_value_1(Qwhite);
			      }
			      else if (EQ(color_or_metacolor,Qforeground) 
				      || EQ(color_or_metacolor,
				      Qworkspace_foreground)) {
				  temp = ISVREF(Current_image_plane,
					  (SI_Long)5L) ? 
					  ISVREF(ISVREF(Current_image_plane,
					  (SI_Long)5L),(SI_Long)22L) : Nil;
				  if (temp);
				  else
				      temp = Qblack;
				  color_or_metacolor = temp;
				  if (EQ(color_or_metacolor,Qtransparent) 
					  || EQ(color_or_metacolor,
					  Qbackground)) {
				      background_color_or_metacolor = 
					      ISVREF(Current_image_plane,
					      (SI_Long)5L) ? 
					      ISVREF(ISVREF(Current_image_plane,
					      (SI_Long)5L),(SI_Long)21L) : Nil;
				      if (background_color_or_metacolor);
				      else
					  background_color_or_metacolor = 
						  Qwhite;
				      if (EQ(background_color_or_metacolor,
					      Qforeground) || 
					      EQ(background_color_or_metacolor,
					      Qworkspace_foreground)) {
					  background_color_value = 
						  ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (background_color_value);
					  else
					      background_color_value = 
						      map_to_color_value_1(Qblack);
				      }
				      else if (EQ(background_color_or_metacolor,
					      Qtransparent) || 
					      EQ(background_color_or_metacolor,
					      Qbackground)) {
					  background_color_value = 
						  ISVREF(Current_color_map,
						  (SI_Long)5L);
					  if (background_color_value);
					  else
					      background_color_value = 
						      map_to_color_value_1(Qwhite);
				      }
				      else
					  background_color_value = 
						  EQ(background_color_or_metacolor,
						  ISVREF(Current_color_map,
						  (SI_Long)6L)) ? 
						  ISVREF(Current_color_map,
						  (SI_Long)7L) : 
						  map_to_color_value_1(background_color_or_metacolor);
				  }
				  else if (EQ(color_or_metacolor,
					  Qforeground) || 
					  EQ(color_or_metacolor,
					  Qworkspace_foreground)) {
				      background_color_value = 
					      ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (background_color_value);
				      else
					  background_color_value = 
						  map_to_color_value_1(Qblack);
				  }
				  else
				      background_color_value = 
					      EQ(color_or_metacolor,
					      ISVREF(Current_color_map,
					      (SI_Long)6L)) ? 
					      ISVREF(Current_color_map,
					      (SI_Long)7L) : 
					      map_to_color_value_1(color_or_metacolor);
			      }
			      else
				  background_color_value = 
					  EQ(color_or_metacolor,
					  ISVREF(Current_color_map,
					  (SI_Long)6L)) ? 
					  ISVREF(Current_color_map,
					  (SI_Long)7L) : 
					  map_to_color_value_1(color_or_metacolor);
			      if ( 
				      !TRUEP(image_plane_background_images(Current_image_plane))) 
					  {
				  paint_solid_rectangle(Left_edge_of_draw_area,
					  Top_edge_of_draw_area,
					  Right_edge_of_draw_area,
					  Bottom_edge_of_draw_area,
					  background_color_value);
				  state_qm = Nil;
			      }
			      else {
				  if ( !TRUEP(state_qm)) {
				      images_region = 
					      region_containing_background_images(Current_image_plane);
				      background_region = 
					      make_region_from_rectangle(ISVREF(Current_image_plane,
					      (SI_Long)19L),
					      ISVREF(Current_image_plane,
					      (SI_Long)20L),
					      ISVREF(Current_image_plane,
					      (SI_Long)21L),
					      ISVREF(Current_image_plane,
					      (SI_Long)22L));
				      net_region = 
					      subtract_region(background_region,
					      images_region);
				      fill_region_with_color(net_region,
					      background_color_value);
				      reclaim_region(net_region);
				      reclaim_region(background_region);
				      reclaim_region(images_region);
				      state_qm = Qimages;
				  }
				  if (state_qm)
				      state_qm = 
					      draw_background_images(Current_image_plane,
					      EQ(state_qm,Qimages) ? Nil : 
					      state_qm,
					      Left_edge_of_draw_area,
					      Top_edge_of_draw_area,
					      Right_edge_of_draw_area,
					      Bottom_edge_of_draw_area);
			      }
			      if ( !TRUEP(state_qm) && 
				      visible_grid_p(Current_image_plane))
				  draw_alignment_grid(Left_edge_of_draw_area,
					  Top_edge_of_draw_area,
					  Right_edge_of_draw_area,
					  Bottom_edge_of_draw_area);
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(state_qm);
}

/* FILL-REGION-WITH-COLOR */
Object fill_region_with_color(region,color_value)
    Object region, color_value;
{
    Object region_strip, top, bottom, region_strip_1, remaining_region_strips;
    Object ab_loop_list_, region_strip_2, a, b, left, right, ab_loop_list__1;
    Object ab_loop_desetq_;

    x_note_fn_call(89,101);
    region_strip = Nil;
    top = Nil;
    bottom = Nil;
    region_strip_1 = Nil;
    remaining_region_strips = Nil;
    ab_loop_list_ = M_CAR(region);
    region_strip_2 = Nil;
    a = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_strip_1 = CAR(ab_loop_list_);
    remaining_region_strips = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(remaining_region_strips))
	goto end_loop;
    region_strip_2 = FIRST(remaining_region_strips);
    a = CAR(region_strip_1);
    b = CAR(region_strip_2);
    if (Top_edge_of_draw_area) {
	a = FIXNUM_LE(a,Top_edge_of_draw_area) ? Top_edge_of_draw_area : 
		FIXNUM_LE(Bottom_edge_of_draw_area,a) ? 
		Bottom_edge_of_draw_area : a;
	b = FIXNUM_LE(b,Top_edge_of_draw_area) ? Top_edge_of_draw_area : 
		FIXNUM_LE(Bottom_edge_of_draw_area,b) ? 
		Bottom_edge_of_draw_area : b;
    }
    if ( !FIXNUM_EQ(a,b)) {
	top = a;
	bottom = b;
	region_strip = region_strip_1;
	left = Nil;
	right = Nil;
	ab_loop_list__1 = CDR(region_strip);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	left = CAR(ab_loop_desetq_);
	right = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (Left_edge_of_draw_area) {
	    left = FIXNUM_LE(left,Left_edge_of_draw_area) ? 
		    Left_edge_of_draw_area : 
		    FIXNUM_LE(Right_edge_of_draw_area,left) ? 
		    Right_edge_of_draw_area : left;
	    right = FIXNUM_LE(right,Left_edge_of_draw_area) ? 
		    Left_edge_of_draw_area : 
		    FIXNUM_LE(Right_edge_of_draw_area,right) ? 
		    Right_edge_of_draw_area : right;
	}
	if ( !FIXNUM_EQ(left,right))
	    paint_solid_rectangle(left,top,right,bottom,color_value);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DRAW-RUBBER-STAMP-WIDGET-IN-FRAME */
Object draw_rubber_stamp_widget_in_frame(rubber_stamp_widget)
    Object rubber_stamp_widget;
{
    x_note_fn_call(89,102);
    draw_rubber_stamp_widget(rubber_stamp_widget,Left_edge_of_frame,
	    Top_edge_of_frame,Right_edge_of_frame,Bottom_edge_of_frame);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* PROJECT-SCROLL-BAR-FOR-FRAME */
Object project_scroll_bar_for_frame()
{
    x_note_fn_call(89,103);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper))
	return frame_rectangle_with_clipping(FIX((SI_Long)1L));
    else if (EQ(Purpose_of_frame_projecting,Qdrawing) || 
	    EQ(Purpose_of_frame_projecting,Qmouse_tracking) || 
	    EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return project_frame(Purpose_of_frame_projecting,
		EQ(Orientation_of_frame,Qvertical) ? list_constant : 
		list_constant_1,Left_edge_of_frame,Top_edge_of_frame,
		Right_edge_of_frame,Bottom_edge_of_frame,Nil);
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

Object The_type_description_of_frame_component_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_frame_component_spots, Qchain_of_available_frame_component_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_component_spot_count, Qframe_component_spot_count);

Object Chain_of_available_frame_component_spots_vector = UNBOUND;

/* FRAME-COMPONENT-SPOT-STRUCTURE-MEMORY-USAGE */
Object frame_component_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,104);
    temp = Frame_component_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FRAME-COMPONENT-SPOT-COUNT */
Object outstanding_frame_component_spot_count()
{
    Object def_structure_frame_component_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,105);
    gensymed_symbol = IFIX(Frame_component_spot_count);
    def_structure_frame_component_spot_variable = 
	    Chain_of_available_frame_component_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_frame_component_spot_variable))
	goto end_loop;
    def_structure_frame_component_spot_variable = 
	    ISVREF(def_structure_frame_component_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FRAME-COMPONENT-SPOT-1 */
Object reclaim_frame_component_spot_1(frame_component_spot)
    Object frame_component_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,106);
    inline_note_reclaim_cons(frame_component_spot,Nil);
    structure_being_reclaimed = frame_component_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(frame_component_spot,(SI_Long)2L));
      SVREF(frame_component_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_frame_component_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(frame_component_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_frame_component_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = frame_component_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FRAME-COMPONENT-SPOT */
Object reclaim_structure_for_frame_component_spot(frame_component_spot)
    Object frame_component_spot;
{
    x_note_fn_call(89,107);
    return reclaim_frame_component_spot_1(frame_component_spot);
}

static Object Qg2_defstruct_structure_name_frame_component_spot_g2_struct;  /* g2-defstruct-structure-name::frame-component-spot-g2-struct */

/* MAKE-PERMANENT-FRAME-COMPONENT-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_frame_component_spot_structure_internal()
{
    Object def_structure_frame_component_spot_variable;
    Object defstruct_g2_frame_component_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,108);
    def_structure_frame_component_spot_variable = Nil;
    atomic_incff_symval(Qframe_component_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_frame_component_spot_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_frame_component_spot_variable = the_array;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_frame_component_spot_g2_struct;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_frame_component_spot_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_frame_component_spot_variable = 
		defstruct_g2_frame_component_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_frame_component_spot_variable);
}

/* MAKE-FRAME-COMPONENT-SPOT-1 */
Object make_frame_component_spot_1()
{
    Object def_structure_frame_component_spot_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,109);
    def_structure_frame_component_spot_variable = 
	    ISVREF(Chain_of_available_frame_component_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_frame_component_spot_variable) {
	temp = Chain_of_available_frame_component_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_frame_component_spot_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_frame_component_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_frame_component_spot_g2_struct;
    }
    else
	def_structure_frame_component_spot_variable = 
		make_permanent_frame_component_spot_structure_internal();
    inline_note_allocate_cons(def_structure_frame_component_spot_variable,Nil);
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)5L)) = Nil;
    temp = Left_edge_of_frame;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)6L)) = temp;
    temp = Top_edge_of_frame;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)7L)) = temp;
    temp = Right_edge_of_frame;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)8L)) = temp;
    temp = Bottom_edge_of_frame;
    SVREF(def_structure_frame_component_spot_variable,FIX((SI_Long)9L)) = temp;
    return VALUES_1(def_structure_frame_component_spot_variable);
}

Object The_type_description_of_elevator_shaft_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_elevator_shaft_spots, Qchain_of_available_elevator_shaft_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Elevator_shaft_spot_count, Qelevator_shaft_spot_count);

Object Chain_of_available_elevator_shaft_spots_vector = UNBOUND;

/* ELEVATOR-SHAFT-SPOT-STRUCTURE-MEMORY-USAGE */
Object elevator_shaft_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,110);
    temp = Elevator_shaft_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ELEVATOR-SHAFT-SPOT-COUNT */
Object outstanding_elevator_shaft_spot_count()
{
    Object def_structure_elevator_shaft_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,111);
    gensymed_symbol = IFIX(Elevator_shaft_spot_count);
    def_structure_elevator_shaft_spot_variable = 
	    Chain_of_available_elevator_shaft_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_elevator_shaft_spot_variable))
	goto end_loop;
    def_structure_elevator_shaft_spot_variable = 
	    ISVREF(def_structure_elevator_shaft_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ELEVATOR-SHAFT-SPOT-1 */
Object reclaim_elevator_shaft_spot_1(elevator_shaft_spot)
    Object elevator_shaft_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,112);
    inline_note_reclaim_cons(elevator_shaft_spot,Nil);
    structure_being_reclaimed = elevator_shaft_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(elevator_shaft_spot,(SI_Long)2L));
      SVREF(elevator_shaft_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_elevator_shaft_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(elevator_shaft_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_elevator_shaft_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = elevator_shaft_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ELEVATOR-SHAFT-SPOT */
Object reclaim_structure_for_elevator_shaft_spot(elevator_shaft_spot)
    Object elevator_shaft_spot;
{
    x_note_fn_call(89,113);
    return reclaim_elevator_shaft_spot_1(elevator_shaft_spot);
}

static Object Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct;  /* g2-defstruct-structure-name::elevator-shaft-spot-g2-struct */

/* MAKE-PERMANENT-ELEVATOR-SHAFT-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_elevator_shaft_spot_structure_internal()
{
    Object def_structure_elevator_shaft_spot_variable;
    Object defstruct_g2_elevator_shaft_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,114);
    def_structure_elevator_shaft_spot_variable = Nil;
    atomic_incff_symval(Qelevator_shaft_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_elevator_shaft_spot_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_elevator_shaft_spot_variable = the_array;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)5L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)6L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)7L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)8L)) 
		= Nil;
	SVREF(defstruct_g2_elevator_shaft_spot_variable,FIX((SI_Long)9L)) 
		= Nil;
	def_structure_elevator_shaft_spot_variable = 
		defstruct_g2_elevator_shaft_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_elevator_shaft_spot_variable);
}

/* MAKE-ELEVATOR-SHAFT-SPOT-1 */
Object make_elevator_shaft_spot_1()
{
    Object def_structure_elevator_shaft_spot_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,115);
    def_structure_elevator_shaft_spot_variable = 
	    ISVREF(Chain_of_available_elevator_shaft_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_elevator_shaft_spot_variable) {
	temp = Chain_of_available_elevator_shaft_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_elevator_shaft_spot_variable,(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct;
    }
    else
	def_structure_elevator_shaft_spot_variable = 
		make_permanent_elevator_shaft_spot_structure_internal();
    inline_note_allocate_cons(def_structure_elevator_shaft_spot_variable,Nil);
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)5L)) = Nil;
    temp = Left_edge_of_frame;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)6L)) = temp;
    temp = Top_edge_of_frame;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)7L)) = temp;
    temp = Right_edge_of_frame;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)8L)) = temp;
    temp = Bottom_edge_of_frame;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_elevator_shaft_spot_variable,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_elevator_shaft_spot_variable);
}

Object The_type_description_of_stepper_of_scroll_bar_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_stepper_of_scroll_bar_spots, Qchain_of_available_stepper_of_scroll_bar_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Stepper_of_scroll_bar_spot_count, Qstepper_of_scroll_bar_spot_count);

Object Chain_of_available_stepper_of_scroll_bar_spots_vector = UNBOUND;

/* STEPPER-OF-SCROLL-BAR-SPOT-STRUCTURE-MEMORY-USAGE */
Object stepper_of_scroll_bar_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,116);
    temp = Stepper_of_scroll_bar_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STEPPER-OF-SCROLL-BAR-SPOT-COUNT */
Object outstanding_stepper_of_scroll_bar_spot_count()
{
    Object def_structure_stepper_of_scroll_bar_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,117);
    gensymed_symbol = IFIX(Stepper_of_scroll_bar_spot_count);
    def_structure_stepper_of_scroll_bar_spot_variable = 
	    Chain_of_available_stepper_of_scroll_bar_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_stepper_of_scroll_bar_spot_variable))
	goto end_loop;
    def_structure_stepper_of_scroll_bar_spot_variable = 
	    ISVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STEPPER-OF-SCROLL-BAR-SPOT-1 */
Object reclaim_stepper_of_scroll_bar_spot_1(stepper_of_scroll_bar_spot)
    Object stepper_of_scroll_bar_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,118);
    inline_note_reclaim_cons(stepper_of_scroll_bar_spot,Nil);
    structure_being_reclaimed = stepper_of_scroll_bar_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(stepper_of_scroll_bar_spot,(SI_Long)2L));
      SVREF(stepper_of_scroll_bar_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_stepper_of_scroll_bar_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(stepper_of_scroll_bar_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_stepper_of_scroll_bar_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = stepper_of_scroll_bar_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STEPPER-OF-SCROLL-BAR-SPOT */
Object reclaim_structure_for_stepper_of_scroll_bar_spot(stepper_of_scroll_bar_spot)
    Object stepper_of_scroll_bar_spot;
{
    x_note_fn_call(89,119);
    return reclaim_stepper_of_scroll_bar_spot_1(stepper_of_scroll_bar_spot);
}

static Object Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct;  /* g2-defstruct-structure-name::stepper-of-scroll-bar-spot-g2-struct */

/* MAKE-PERMANENT-STEPPER-OF-SCROLL-BAR-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_stepper_of_scroll_bar_spot_structure_internal()
{
    Object def_structure_stepper_of_scroll_bar_spot_variable;
    Object defstruct_g2_stepper_of_scroll_bar_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,120);
    def_structure_stepper_of_scroll_bar_spot_variable = Nil;
    atomic_incff_symval(Qstepper_of_scroll_bar_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_stepper_of_scroll_bar_spot_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_stepper_of_scroll_bar_spot_variable = the_array;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)9L)) = Nil;
	def_structure_stepper_of_scroll_bar_spot_variable = 
		defstruct_g2_stepper_of_scroll_bar_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_stepper_of_scroll_bar_spot_variable);
}

/* MAKE-STEPPER-OF-SCROLL-BAR-SPOT-1 */
Object make_stepper_of_scroll_bar_spot_1()
{
    Object def_structure_stepper_of_scroll_bar_spot_variable, temp;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(89,121);
    def_structure_stepper_of_scroll_bar_spot_variable = 
	    ISVREF(Chain_of_available_stepper_of_scroll_bar_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_stepper_of_scroll_bar_spot_variable) {
	temp = Chain_of_available_stepper_of_scroll_bar_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_stepper_of_scroll_bar_spot_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct;
    }
    else
	def_structure_stepper_of_scroll_bar_spot_variable = 
		make_permanent_stepper_of_scroll_bar_spot_structure_internal();
    inline_note_allocate_cons(def_structure_stepper_of_scroll_bar_spot_variable,
	    Nil);
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)3L)) = T;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)5L)) = Nil;
    temp = Left_edge_of_frame;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)6L)) = temp;
    temp = Top_edge_of_frame;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)7L)) = temp;
    temp = Right_edge_of_frame;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)8L)) = temp;
    temp = Bottom_edge_of_frame;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_stepper_of_scroll_bar_spot_variable,
	    FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_stepper_of_scroll_bar_spot_variable);
}

/* MAKE-STEPPER-OF-SCROLL-BAR-SPOT-PLUS */
Object make_stepper_of_scroll_bar_spot_plus(direction,amount)
    Object direction, amount;
{
    Object spot;

    x_note_fn_call(89,122);
    spot = make_stepper_of_scroll_bar_spot_1();
    SVREF(spot,FIX((SI_Long)10L)) = direction;
    SVREF(spot,FIX((SI_Long)11L)) = amount;
    return VALUES_1(spot);
}

Object The_type_description_of_elevator_of_scroll_bar_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_elevator_of_scroll_bar_spots, Qchain_of_available_elevator_of_scroll_bar_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Elevator_of_scroll_bar_spot_count, Qelevator_of_scroll_bar_spot_count);

Object Chain_of_available_elevator_of_scroll_bar_spots_vector = UNBOUND;

/* ELEVATOR-OF-SCROLL-BAR-SPOT-STRUCTURE-MEMORY-USAGE */
Object elevator_of_scroll_bar_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,123);
    temp = Elevator_of_scroll_bar_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ELEVATOR-OF-SCROLL-BAR-SPOT-COUNT */
Object outstanding_elevator_of_scroll_bar_spot_count()
{
    Object def_structure_elevator_of_scroll_bar_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,124);
    gensymed_symbol = IFIX(Elevator_of_scroll_bar_spot_count);
    def_structure_elevator_of_scroll_bar_spot_variable = 
	    Chain_of_available_elevator_of_scroll_bar_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_elevator_of_scroll_bar_spot_variable))
	goto end_loop;
    def_structure_elevator_of_scroll_bar_spot_variable = 
	    ISVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ELEVATOR-OF-SCROLL-BAR-SPOT-1 */
Object reclaim_elevator_of_scroll_bar_spot_1(elevator_of_scroll_bar_spot)
    Object elevator_of_scroll_bar_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,125);
    inline_note_reclaim_cons(elevator_of_scroll_bar_spot,Nil);
    structure_being_reclaimed = elevator_of_scroll_bar_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(elevator_of_scroll_bar_spot,
	      (SI_Long)2L));
      SVREF(elevator_of_scroll_bar_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_elevator_of_scroll_bar_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(elevator_of_scroll_bar_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_elevator_of_scroll_bar_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = elevator_of_scroll_bar_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ELEVATOR-OF-SCROLL-BAR-SPOT */
Object reclaim_structure_for_elevator_of_scroll_bar_spot(elevator_of_scroll_bar_spot)
    Object elevator_of_scroll_bar_spot;
{
    x_note_fn_call(89,126);
    return reclaim_elevator_of_scroll_bar_spot_1(elevator_of_scroll_bar_spot);
}

static Object Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct;  /* g2-defstruct-structure-name::elevator-of-scroll-bar-spot-g2-struct */

/* MAKE-PERMANENT-ELEVATOR-OF-SCROLL-BAR-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_elevator_of_scroll_bar_spot_structure_internal()
{
    Object def_structure_elevator_of_scroll_bar_spot_variable;
    Object defstruct_g2_elevator_of_scroll_bar_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,127);
    def_structure_elevator_of_scroll_bar_spot_variable = Nil;
    atomic_incff_symval(Qelevator_of_scroll_bar_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_elevator_of_scroll_bar_spot_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_elevator_of_scroll_bar_spot_variable = the_array;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)9L)) = Nil;
	def_structure_elevator_of_scroll_bar_spot_variable = 
		defstruct_g2_elevator_of_scroll_bar_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_elevator_of_scroll_bar_spot_variable);
}

/* MAKE-ELEVATOR-OF-SCROLL-BAR-SPOT-1 */
Object make_elevator_of_scroll_bar_spot_1()
{
    Object def_structure_elevator_of_scroll_bar_spot_variable, temp;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(89,128);
    def_structure_elevator_of_scroll_bar_spot_variable = 
	    ISVREF(Chain_of_available_elevator_of_scroll_bar_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_elevator_of_scroll_bar_spot_variable) {
	temp = Chain_of_available_elevator_of_scroll_bar_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_elevator_of_scroll_bar_spot_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct;
    }
    else
	def_structure_elevator_of_scroll_bar_spot_variable = 
		make_permanent_elevator_of_scroll_bar_spot_structure_internal();
    inline_note_allocate_cons(def_structure_elevator_of_scroll_bar_spot_variable,
	    Nil);
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)3L)) = T;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)5L)) = Nil;
    temp = Left_edge_of_frame;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)6L)) = temp;
    temp = Top_edge_of_frame;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)7L)) = temp;
    temp = Right_edge_of_frame;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)8L)) = temp;
    temp = Bottom_edge_of_frame;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_elevator_of_scroll_bar_spot_variable,
	    FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_elevator_of_scroll_bar_spot_variable);
}

/* MAKE-ELEVATOR-OF-SCROLL-BAR-SPOT-PLUS */
Object make_elevator_of_scroll_bar_spot_plus(orientation)
    Object orientation;
{
    Object spot;

    x_note_fn_call(89,129);
    spot = make_elevator_of_scroll_bar_spot_1();
    SVREF(spot,FIX((SI_Long)10L)) = orientation;
    return VALUES_1(spot);
}

static Object Qgensym_left_scroll_arrow_frame_component;  /* gensym-left-scroll-arrow-frame-component */

static Object Qgensym_right_scroll_arrow_frame_component;  /* gensym-right-scroll-arrow-frame-component */

static Object Qgensym_up_scroll_arrow_frame_component;  /* gensym-up-scroll-arrow-frame-component */

static Object Qgensym_down_scroll_arrow_frame_component;  /* gensym-down-scroll-arrow-frame-component */

/* PROJECT-ARROW-OF-SCROLL-BAR-FOR-FRAME */
Object project_arrow_of_scroll_bar_for_frame(direction)
    Object direction;
{
    Object temp, spot;

    x_note_fn_call(89,130);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper))
	return frame_rectangle_with_clipping(FIX((SI_Long)1L));
    else if (EQ(Purpose_of_frame_projecting,Qdrawing)) {
	if (EQ(direction,Qleft))
	    temp = Qgensym_left_scroll_arrow_frame_component;
	else if (EQ(direction,Qright))
	    temp = Qgensym_right_scroll_arrow_frame_component;
	else if (EQ(direction,Qup))
	    temp = Qgensym_up_scroll_arrow_frame_component;
	else if (EQ(direction,Qdown))
	    temp = Qgensym_down_scroll_arrow_frame_component;
	else
	    temp = Qnil;
	return draw_rubber_stamp_widget_in_frame(temp);
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents) || 
	    EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	temp = Mouse_pointer_of_frame;
	spot = make_stepper_of_scroll_bar_spot_plus(direction,Qline);
	return push_last_spot(temp,spot,Block_of_frame);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qlight_grey;         /* light-grey */

/* PROJECT-SHAFT-OF-SCROLL-BAR-FOR-FRAME */
Object project_shaft_of_scroll_bar_for_frame()
{
    Object light_grey_color_value, current_foreground_color_value;
    Object old_color_value, current_background_color_value, spot;
    Object svref_new_value;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(89,131);
    SAVE_STACK();
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper)) {
	result = frame_rectangle_with_clipping(FIX((SI_Long)1L));
	RESTORE_STACK();
	return result;
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing)) {
	light_grey_color_value = map_to_color_value(Qlight_grey);
	current_foreground_color_value = light_grey_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
		0);
	  paint_rectangle_with_clipping();
	POP_SPECIAL();
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(light_grey_color_value);
	  frame_rectangle_with_clipping(FIX((SI_Long)1L));
	  SAVE_VALUES(project_elevator_of_scroll_bar_for_frame());
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator)) {
	result = project_elevator_of_scroll_bar_for_frame();
	RESTORE_STACK();
	return result;
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	spot = make_elevator_shaft_spot_1();
	svref_new_value = Orientation_of_frame;
	SVREF(spot,FIX((SI_Long)10L)) = svref_new_value;
	push_more_detailed_spot(Mouse_pointer_of_frame,spot,Block_of_frame);
	result = project_elevator_of_scroll_bar_for_frame();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
}

/* POSITION-OF-ELEVATOR-AS-OFFSET-GIVEN-SCALE */
Object position_of_elevator_as_offset_given_scale(position_as_scale,
	    shaft_width,shaft_height)
    Object position_as_scale, shaft_width, shaft_height;
{
    Object scale, value;
    SI_Long unshifted_result;

    x_note_fn_call(89,132);
    scale = position_as_scale;
    value = FIXNUM_MINUS(shaft_height,shaft_width);
    if (IFIX(scale) == (SI_Long)4096L)
	return VALUES_1(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	return VALUES_1(FIX(unshifted_result >>  -  - (SI_Long)12L));
    }
    else
	return scalef_function(scale,value);
}

/* POSITION-OF-ELEVATOR-AS-SCALE-GIVEN-OFFSET */
Object position_of_elevator_as_scale_given_offset(position_as_offset,
	    shaft_width,shaft_height)
    Object position_as_offset, shaft_width, shaft_height;
{
    Object temp;

    x_note_fn_call(89,133);
    if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    position_as_offset) && FIXNUM_LT(position_as_offset,
	    Isqrt_of_most_positive_fixnum)) {
	temp = l_round(FIX(IFIX(position_as_offset) * (SI_Long)4096L),
		FIXNUM_MINUS(shaft_height,shaft_width));
	return VALUES_1(temp);
    }
    else
	return inverse_scalef_function(FIXNUM_MINUS(shaft_height,
		shaft_width),position_as_offset);
}

/* EDGES-OF-ELEVATOR */
Object edges_of_elevator(orientation,left_edge_of_shaft,top_edge_of_shaft,
	    right_edge_of_shaft,bottom_edge_of_shaft,
	    position_of_elevator_as_scale)
    Object orientation, left_edge_of_shaft, top_edge_of_shaft;
    Object right_edge_of_shaft, bottom_edge_of_shaft;
    Object position_of_elevator_as_scale;
{
    Object top_of_elevator, left_of_elevator;
    Object position_of_elevator_as_shaft_offset, incff_1_arg;
    SI_Long height, width, shaft_width, shaft_height;
    char vertical_qm;

    x_note_fn_call(89,134);
    vertical_qm = EQ(orientation,Qvertical);
    height = IFIX(FIXNUM_MINUS(bottom_edge_of_shaft,top_edge_of_shaft)) - 
	    (SI_Long)2L;
    width = IFIX(FIXNUM_MINUS(right_edge_of_shaft,left_edge_of_shaft)) - 
	    (SI_Long)2L;
    shaft_width = vertical_qm ? width : height;
    shaft_height = vertical_qm ? height : width;
    top_of_elevator = FIXNUM_ADD1(top_edge_of_shaft);
    left_of_elevator = FIXNUM_ADD1(left_edge_of_shaft);
    position_of_elevator_as_shaft_offset = 
	    position_of_elevator_as_offset_given_scale(position_of_elevator_as_scale,
	    FIX(shaft_width),FIX(shaft_height));
    if (vertical_qm) {
	incff_1_arg = position_of_elevator_as_shaft_offset;
	top_of_elevator = FIXNUM_ADD(top_of_elevator,incff_1_arg);
    }
    else {
	incff_1_arg = position_of_elevator_as_shaft_offset;
	left_of_elevator = FIXNUM_ADD(left_of_elevator,incff_1_arg);
    }
    return VALUES_4(left_of_elevator,top_of_elevator,
	    FIX(IFIX(left_of_elevator) + shaft_width),
	    FIX(IFIX(top_of_elevator) + shaft_width));
}

static Object Qgensym_scroll_bar_elevator_frame_component;  /* gensym-scroll-bar-elevator-frame-component */

static Object Qpage;               /* page */

/* PROJECT-ELEVATOR-OF-SCROLL-BAR-FOR-FRAME */
Object project_elevator_of_scroll_bar_for_frame()
{
    Object temp, temp_1, temp_2, temp_3, temp_4, left_of_elevator;
    Object top_of_elevator, right_of_elevator, bottom_of_elevator;
    Object left_edge_of_frame, top_edge_of_frame, right_edge_of_frame;
    Object bottom_edge_of_frame, x_in_window, y_in_window, spot;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long left_edge_of_elevator_in_window, top_edge_of_elevator_in_window;
    SI_Long right_edge_of_elevator_in_window;
    SI_Long bottom_edge_of_elevator_in_window;
    char vertical_qm;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,135);
    vertical_qm = EQ(Orientation_of_frame,Qvertical);
    temp = Orientation_of_frame;
    temp_1 = Left_edge_of_frame;
    temp_2 = Top_edge_of_frame;
    temp_3 = Right_edge_of_frame;
    temp_4 = Bottom_edge_of_frame;
    result = edges_of_elevator(temp,temp_1,temp_2,temp_3,temp_4,
	    vertical_qm ? 
	    get_lookup_slot_value_given_default(Block_of_frame,
	    Qposition_of_vertical_elevator,FIX((SI_Long)0L)) : 
	    get_lookup_slot_value_given_default(Block_of_frame,
	    Qposition_of_horizontal_elevator,FIX((SI_Long)0L)));
    MVS_4(result,left_of_elevator,top_of_elevator,right_of_elevator,
	    bottom_of_elevator);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qdrawing) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_contents)) {
	left_edge_of_frame = left_of_elevator;
	top_edge_of_frame = top_of_elevator;
	right_edge_of_frame = right_of_elevator;
	bottom_edge_of_frame = bottom_of_elevator;
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
		      0);
		result = draw_rubber_stamp_widget_in_frame(Qgensym_scroll_bar_elevator_frame_component);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return move_elevator_within_shaft(left_of_elevator,top_of_elevator,
		right_of_elevator,bottom_of_elevator);
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	x_in_window = ISVREF(Mouse_pointer_of_frame,(SI_Long)2L);
	y_in_window = ISVREF(Mouse_pointer_of_frame,(SI_Long)3L);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(left_of_elevator);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		left_of_elevator) && FIXNUM_LT(left_of_elevator,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    left_of_elevator)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    left_of_elevator));
	left_edge_of_elevator_in_window = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(top_of_elevator);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		top_of_elevator) && FIXNUM_LT(top_of_elevator,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    top_of_elevator)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    top_of_elevator));
	top_edge_of_elevator_in_window = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(right_of_elevator);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		right_of_elevator) && FIXNUM_LT(right_of_elevator,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    right_of_elevator)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    right_of_elevator));
	right_edge_of_elevator_in_window = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(bottom_of_elevator);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		bottom_of_elevator) && FIXNUM_LT(bottom_of_elevator,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    bottom_of_elevator)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    bottom_of_elevator));
	bottom_edge_of_elevator_in_window = gensymed_symbol + 
		gensymed_symbol_1;
	if (vertical_qm) {
	    if (IFIX(y_in_window) < top_edge_of_elevator_in_window)
		spot = make_stepper_of_scroll_bar_spot_plus(Qup,Qpage);
	    else if (IFIX(y_in_window) < bottom_edge_of_elevator_in_window)
		spot = make_elevator_of_scroll_bar_spot_plus(Qvertical);
	    else
		spot = make_stepper_of_scroll_bar_spot_plus(Qdown,Qpage);
	}
	else if (IFIX(x_in_window) < left_edge_of_elevator_in_window)
	    spot = make_stepper_of_scroll_bar_spot_plus(Qleft,Qpage);
	else if (IFIX(x_in_window) < right_edge_of_elevator_in_window)
	    spot = make_elevator_of_scroll_bar_spot_plus(Qhorizontal);
	else
	    spot = make_stepper_of_scroll_bar_spot_plus(Qright,Qpage);
	if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
		Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct)) 
		    {
	    SVREF(spot,FIX((SI_Long)6L)) = left_of_elevator;
	    SVREF(spot,FIX((SI_Long)7L)) = top_of_elevator;
	    SVREF(spot,FIX((SI_Long)8L)) = right_of_elevator;
	    SVREF(spot,FIX((SI_Long)9L)) = bottom_of_elevator;
	}
	return push_last_spot(Mouse_pointer_of_frame,spot,Block_of_frame);
    }
    else
	return VALUES_1(Qnil);
}

/* IMAGE-PLANE-HAS-NEW-G2-CLASSIC-TITLE-BAR-P */
Object image_plane_has_new_g2_classic_title_bar_p(image_plane)
    Object image_plane;
{
    Object frame_description_reference, frame_description, frame_section_3_qm;
    Object temp;
    char temp_1;

    x_note_fn_call(89,136);
    frame_description_reference = ISVREF(image_plane,(SI_Long)10L);
    frame_description = ISVREF(frame_description_reference,(SI_Long)2L);
    frame_section_3_qm = THIRD(frame_description);
    if (frame_section_3_qm && EQ(FIRST(frame_section_3_qm),Qframe_section)) {
	temp = SECOND(frame_section_3_qm);
	temp_1 = EQ(FIRST(temp),Qtop);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = THIRD(frame_section_3_qm);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = THIRD(frame_section_3_qm);
	return VALUES_1(EQ(FIRST(temp),Qtitle_bar) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Default_workspace_title_bar_text_spec = UNBOUND;

static Object Qwide_string;        /* wide-string */

/* MAKE-TITLE-BAR-TEXT-FOR-WORKSPACE */
Object make_title_bar_text_for_workspace(workspace,spec)
    Object workspace, spec;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object element, ab_loop_list_, temp, temp_1, gensym_list_of_wide_strings;
    Object string_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object svref_new_value, gensymed_symbol, short_string, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(89,137);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      current_wide_string = new_wide_string;
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
	      if (spec) {
		  if (ATOM(spec))
		      make_title_bar_text_per_directive_or_string(workspace,
			      spec);
		  else {
		      element = Nil;
		      ab_loop_list_ = spec;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      element = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (make_title_bar_text_per_directive_or_string(workspace,
			      element))
			  goto end_loop;
		      goto next_loop;
		    end_loop:;
		  }
	      }
	      temp = Current_wide_string;
	      temp_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_1) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(temp_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp = short_string;
    }
    else
	temp = string_1;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp_2);
}

DEFINE_VARIABLE_WITH_SYMBOL(Known_gensym_acronyms, Qknown_gensym_acronyms);

static Object Qname;               /* name */

static Object Qnames;              /* names */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qa_or_an_plus_class;  /* a-or-an+class */

static Object Qab_class;           /* class */

static Object Kfirst_of_each_word;  /* :first-of-each-word */

static Object Qtable_header;       /* table-header */

static Object Quuid;               /* uuid */

/* MAKE-TITLE-BAR-TEXT-PER-DIRECTIVE-OR-STRING */
Object make_title_bar_text_per_directive_or_string(workspace,
	    directive_or_string)
    Object workspace, directive_or_string;
{
    Object name_qm, name_or_names_qm;

    x_note_fn_call(89,138);
    if (EQ(directive_or_string,Qname)) {
	name_qm = get_primary_name_for_frame_if_any(workspace);
	if (name_qm) {
	    twrite_symbol(2,name_qm,T);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(directive_or_string,Qnames)) {
	name_or_names_qm = get_lookup_slot_value_given_default(workspace,
		Qname_or_names_for_frame,Nil);
	if (name_or_names_qm) {
	    write_name_or_names_from_slot(name_or_names_qm,workspace);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(directive_or_string,Qa_or_an_plus_class)) {
	write_symbol_with_a_or_an(1,ISVREF(ISVREF(workspace,(SI_Long)1L),
		(SI_Long)1L));
	return VALUES_1(T);
    }
    else if (EQ(directive_or_string,Qab_class)) {
	twrite_symbol_name(ISVREF(ISVREF(workspace,(SI_Long)1L),
		(SI_Long)1L),Kfirst_of_each_word,T,Nil,Known_gensym_acronyms);
	return VALUES_1(T);
    }
    else if (EQ(directive_or_string,Qtable_header)) {
	write_class_instance_header_from_slot(ISVREF(ISVREF(workspace,
		(SI_Long)1L),(SI_Long)1L),workspace);
	return VALUES_1(T);
    }
    else if (EQ(directive_or_string,Quuid))
	return twrite_uuid_printed_representation_as_string(ISVREF(workspace,
		(SI_Long)2L));
    else if (text_string_p(directive_or_string))
	return twrite_general_string(directive_or_string);
    else
	return VALUES_1(Nil);
}

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qtitle_bar_text;     /* title-bar-text */

/* WORKSPACE-TITLE */
Object workspace_title(workspace_qm)
    Object workspace_qm;
{
    Object temp, text;

    x_note_fn_call(89,139);
    temp =  !TRUEP(workspace_qm) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (get_lookup_slot_value_given_default(workspace_qm,
	    Qtitle_bar_caption_text,Nil))
	return convert_text_to_text_string(1,
		get_lookup_slot_value_given_default(workspace_qm,
		Qtitle_bar_caption_text,Nil));
    else {
	temp = get_lookup_slot_value(workspace_qm,Qtitle_bar_text);
	if (temp);
	else
	    temp = Default_workspace_title_bar_text_spec;
	text = make_title_bar_text_for_workspace(workspace_qm,temp);
	temp = convert_text_to_text_string(1,text);
	reclaim_text(text);
	return VALUES_1(temp);
    }
}

static Object Qdark_slate_blue;    /* dark-slate-blue */

/* TITLE-BAR-BACKGROUND-COLOR */
Object title_bar_background_color(image_plane)
    Object image_plane;
{
    x_note_fn_call(89,140);
    if ( !TRUEP(selection_enabled_p(1,ISVREF(ISVREF(image_plane,
	    (SI_Long)2L),(SI_Long)2L))) || 
	    menu_workspace_p(ISVREF(image_plane,(SI_Long)5L)) || 
	    image_plane_selected_p(image_plane))
	return VALUES_1(Qdark_slate_blue);
    else
	return VALUES_1(Qdim_gray);
}

static Object Qgray;               /* gray */

/* TITLE-BAR-FOREGROUND-COLOR */
Object title_bar_foreground_color(image_plane)
    Object image_plane;
{
    x_note_fn_call(89,141);
    if ( !TRUEP(selection_enabled_p(1,ISVREF(ISVREF(image_plane,
	    (SI_Long)2L),(SI_Long)2L))) || 
	    menu_workspace_p(ISVREF(image_plane,(SI_Long)5L)) || 
	    image_plane_selected_p(image_plane))
	return VALUES_1(Qwhite);
    else
	return VALUES_1(Qgray);
}

DEFINE_VARIABLE_WITH_SYMBOL(Lower_match_rank_for_player_eyes_p, Qlower_match_rank_for_player_eyes_p);

/* PROJECT-TITLE-BAR-FOR-FRAME */
Object project_title_bar_for_frame(font_size)
    Object font_size;
{
    Object workspace_qm, reclaim_title_text_p, title_text_qm, temp;
    Object background_color, foreground_color, old_color_value;
    Object current_background_color_value, current_foreground_color_value;
    Object lower_match_rank_for_player_eyes_p;
    Declare_special(3);

    x_note_fn_call(89,142);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing)) {
	workspace_qm = ISVREF(Current_image_plane,(SI_Long)5L);
	reclaim_title_text_p = Nil;
	if (workspace_qm) {
	    title_text_qm = 
		    get_lookup_slot_value_given_default(workspace_qm,
		    Qtitle_bar_caption_text,Nil);
	    if (title_text_qm);
	    else {
		reclaim_title_text_p = T;
		temp = get_lookup_slot_value(workspace_qm,Qtitle_bar_text);
		if (temp);
		else
		    temp = Default_workspace_title_bar_text_spec;
		title_text_qm = 
			make_title_bar_text_for_workspace(workspace_qm,temp);
	    }
	}
	else
	    title_text_qm = Nil;
	background_color = 
		map_to_color_value(title_bar_background_color(Current_image_plane));
	foreground_color = 
		map_to_color_value(title_bar_foreground_color(Current_image_plane));
	draw_graphic_element(6,Qadd_solid_rectangle,Left_edge_of_frame,
		Top_edge_of_frame,Right_edge_of_frame,Bottom_edge_of_frame,
		FIXNUM_LOGXOR(background_color,
		Current_background_color_value));
	if (title_text_qm) {
	    old_color_value = Current_background_color_value;
	    current_background_color_value = Current_background_color_value;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		    2);
	      set_current_background_color_value(background_color);
	      current_foreground_color_value = foreground_color;
	      lower_match_rank_for_player_eyes_p = T;
	      PUSH_SPECIAL_WITH_SYMBOL(Lower_match_rank_for_player_eyes_p,Qlower_match_rank_for_player_eyes_p,lower_match_rank_for_player_eyes_p,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
			0);
		  draw_title_bar_text(title_text_qm,font_size,
			  Left_edge_of_frame,Top_edge_of_frame,
			  Right_edge_of_frame,Bottom_edge_of_frame);
		POP_SPECIAL();
	      POP_SPECIAL();
	      set_current_background_color_value(old_color_value);
	    POP_SPECIAL();
	}
	if (reclaim_title_text_p)
	    return reclaim_text(title_text_qm);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents) || 
	    EQ(Purpose_of_frame_projecting,Qcompute_content_region) || 
	    EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking))
	return push_more_detailed_spot(Mouse_pointer_of_frame,
		make_title_bar_spot_1(),Block_of_frame);
    else
	return VALUES_1(Qnil);
}

/* REFRESH-TITLE-BAR */
Object refresh_title_bar(workspace)
    Object workspace;
{
    Object image_plane, ab_loop_list_;

    x_note_fn_call(89,143);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    refresh_title_bar_of_image_plane(image_plane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REFRESH-TITLE-BAR-OF-IMAGE-PLANE */
Object refresh_title_bar_of_image_plane(image_plane)
    Object image_plane;
{
    Object left, top, right, bottom, region;

    x_note_fn_call(89,144);
    left = ISVREF(image_plane,(SI_Long)15L);
    top = ISVREF(image_plane,(SI_Long)16L);
    right = ISVREF(image_plane,(SI_Long)17L);
    bottom = ISVREF(image_plane,(SI_Long)20L);
    region = make_region_from_rectangle(left,top,right,bottom);
    invalidate_region_of_image_plane(image_plane,region);
    reclaim_region(region);
    return update_native_title_bar(image_plane);
}

/* REFRESH-BORDERS-OF-IMAGE-PLANE */
Object refresh_borders_of_image_plane(image_plane)
    Object image_plane;
{
    Object outer_region, inner_region, border_region;

    x_note_fn_call(89,145);
    outer_region = make_region_from_rectangle(ISVREF(image_plane,
	    (SI_Long)15L),ISVREF(image_plane,(SI_Long)16L),
	    ISVREF(image_plane,(SI_Long)17L),ISVREF(image_plane,(SI_Long)18L));
    inner_region = make_region_from_rectangle(ISVREF(image_plane,
	    (SI_Long)19L),ISVREF(image_plane,(SI_Long)20L),
	    ISVREF(image_plane,(SI_Long)21L),ISVREF(image_plane,(SI_Long)22L));
    border_region = subtract_region(outer_region,inner_region);
    invalidate_region_of_image_plane(image_plane,border_region);
    reclaim_region(border_region);
    reclaim_region(inner_region);
    return reclaim_region(outer_region);
}

Object The_type_description_of_resize_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resize_box_spots, Qchain_of_available_resize_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Resize_box_spot_count, Qresize_box_spot_count);

Object Chain_of_available_resize_box_spots_vector = UNBOUND;

/* RESIZE-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object resize_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,146);
    temp = Resize_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESIZE-BOX-SPOT-COUNT */
Object outstanding_resize_box_spot_count()
{
    Object def_structure_resize_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,147);
    gensymed_symbol = IFIX(Resize_box_spot_count);
    def_structure_resize_box_spot_variable = 
	    Chain_of_available_resize_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resize_box_spot_variable))
	goto end_loop;
    def_structure_resize_box_spot_variable = 
	    ISVREF(def_structure_resize_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESIZE-BOX-SPOT-1 */
Object reclaim_resize_box_spot_1(resize_box_spot)
    Object resize_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,148);
    inline_note_reclaim_cons(resize_box_spot,Nil);
    structure_being_reclaimed = resize_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(resize_box_spot,(SI_Long)2L));
      SVREF(resize_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resize_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(resize_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resize_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resize_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESIZE-BOX-SPOT */
Object reclaim_structure_for_resize_box_spot(resize_box_spot)
    Object resize_box_spot;
{
    x_note_fn_call(89,149);
    return reclaim_resize_box_spot_1(resize_box_spot);
}

static Object Qg2_defstruct_structure_name_resize_box_spot_g2_struct;  /* g2-defstruct-structure-name::resize-box-spot-g2-struct */

/* MAKE-PERMANENT-RESIZE-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_resize_box_spot_structure_internal()
{
    Object def_structure_resize_box_spot_variable;
    Object defstruct_g2_resize_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,150);
    def_structure_resize_box_spot_variable = Nil;
    atomic_incff_symval(Qresize_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resize_box_spot_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_resize_box_spot_variable = the_array;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resize_box_spot_g2_struct;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resize_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_resize_box_spot_variable = 
		defstruct_g2_resize_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resize_box_spot_variable);
}

/* MAKE-RESIZE-BOX-SPOT-1 */
Object make_resize_box_spot_1()
{
    Object def_structure_resize_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,151);
    def_structure_resize_box_spot_variable = 
	    ISVREF(Chain_of_available_resize_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resize_box_spot_variable) {
	svref_arg_1 = Chain_of_available_resize_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_resize_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resize_box_spot_g2_struct;
    }
    else
	def_structure_resize_box_spot_variable = 
		make_permanent_resize_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_resize_box_spot_variable,Nil);
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_resize_box_spot_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_resize_box_spot_variable);
}

static Object Qgensym_resize_box_frame_component;  /* gensym-resize-box-frame-component */

/* PROJECT-RESIZE-BOX-FOR-FRAME */
Object project_resize_box_for_frame()
{
    Object spot;

    x_note_fn_call(89,152);
    if (EQ(Purpose_of_frame_projecting,Qdrawing_paper))
	return frame_rectangle_with_clipping(FIX((SI_Long)1L));
    else if (EQ(Purpose_of_frame_projecting,Qdrawing))
	return draw_rubber_stamp_widget_in_frame(Qgensym_resize_box_frame_component);
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator))
	return VALUES_1(Nil);
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	spot = make_resize_box_spot_1();
	return push_last_spot(Mouse_pointer_of_frame,spot,Block_of_frame);
    }
    else
	return VALUES_1(Qnil);
}

Object The_type_description_of_close_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_close_box_spots, Qchain_of_available_close_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Close_box_spot_count, Qclose_box_spot_count);

Object Chain_of_available_close_box_spots_vector = UNBOUND;

/* CLOSE-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object close_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,153);
    temp = Close_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLOSE-BOX-SPOT-COUNT */
Object outstanding_close_box_spot_count()
{
    Object def_structure_close_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,154);
    gensymed_symbol = IFIX(Close_box_spot_count);
    def_structure_close_box_spot_variable = Chain_of_available_close_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_close_box_spot_variable))
	goto end_loop;
    def_structure_close_box_spot_variable = 
	    ISVREF(def_structure_close_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CLOSE-BOX-SPOT-1 */
Object reclaim_close_box_spot_1(close_box_spot)
    Object close_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,155);
    inline_note_reclaim_cons(close_box_spot,Nil);
    structure_being_reclaimed = close_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(close_box_spot,(SI_Long)2L));
      SVREF(close_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_close_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(close_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_close_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = close_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLOSE-BOX-SPOT */
Object reclaim_structure_for_close_box_spot(close_box_spot)
    Object close_box_spot;
{
    x_note_fn_call(89,156);
    return reclaim_close_box_spot_1(close_box_spot);
}

static Object Qg2_defstruct_structure_name_close_box_spot_g2_struct;  /* g2-defstruct-structure-name::close-box-spot-g2-struct */

/* MAKE-PERMANENT-CLOSE-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_close_box_spot_structure_internal()
{
    Object def_structure_close_box_spot_variable;
    Object defstruct_g2_close_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,157);
    def_structure_close_box_spot_variable = Nil;
    atomic_incff_symval(Qclose_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_close_box_spot_variable = Nil;
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
	defstruct_g2_close_box_spot_variable = the_array;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_close_box_spot_g2_struct;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_close_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_close_box_spot_variable = 
		defstruct_g2_close_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_close_box_spot_variable);
}

/* MAKE-CLOSE-BOX-SPOT-1 */
Object make_close_box_spot_1()
{
    Object def_structure_close_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,158);
    def_structure_close_box_spot_variable = 
	    ISVREF(Chain_of_available_close_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_close_box_spot_variable) {
	svref_arg_1 = Chain_of_available_close_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_close_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_close_box_spot_g2_struct;
    }
    else
	def_structure_close_box_spot_variable = 
		make_permanent_close_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_close_box_spot_variable,Nil);
    SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_close_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_close_box_spot_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Close_box_rubber_stamp_widget, Qclose_box_rubber_stamp_widget);

static Object Qsmall;              /* small */

/* PROJECT-CLOSE-BOX-FOR-FRAME */
Object project_close_box_for_frame(size)
    Object size;
{
    Object background, temp, temp_1, temp_2, temp_3, color_value_1;
    Object color_value, old_color_value, current_background_color_value;
    Object current_foreground_color_value, situation, widget_entity;
    Object gensymed_symbol, x_in_workspace, y_in_workspace, scale, scale_1;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, spot;
    SI_Long x_in_window, gensymed_symbol_1, gensymed_symbol_2, y_in_window;
    SI_Long value, gensymed_symbol_3, temp_4, unshifted_result;
    Declare_stack_pointer;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,159);
    SAVE_STACK();
    if (EQ(Purpose_of_frame_projecting,Qdrawing) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_paper) || 
	    EQ(Purpose_of_frame_projecting,Qdrawing_close_box)) {
	background = title_bar_background_color(Current_image_plane);
	if (EQ(Purpose_of_frame_projecting,Qdrawing_close_box)) {
	    temp = Left_edge_of_frame;
	    temp_1 = Top_edge_of_frame;
	    temp_2 = Right_edge_of_frame;
	    temp_3 = Bottom_edge_of_frame;
	    color_value_1 = map_to_color_value(background);
	    draw_graphic_element(6,Qadd_solid_rectangle,temp,temp_1,temp_2,
		    temp_3,FIXNUM_LOGXOR(color_value_1,
		    Current_background_color_value));
	}
	color_value = map_to_color_value(background);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		3);
	  set_current_background_color_value(color_value);
	  current_foreground_color_value = map_to_color_value(Qwhite);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
		  2);
	    situation = ISVREF(Current_image_plane,(SI_Long)39L);
	    widget_entity = getf(Close_box_rubber_stamp_widget,situation,_);
	    gensymed_symbol = ISVREF(widget_entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    x_in_workspace = gensymed_symbol;
	    gensymed_symbol = ISVREF(widget_entity,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    y_in_workspace = gensymed_symbol;
	    x_in_window = IFIX(Left_edge_of_frame) + (SI_Long)4L;
	    gensymed_symbol_1 = IFIX(Top_edge_of_frame);
	    gensymed_symbol_2 = EQ(size,Qsmall) ? (SI_Long)4L : (SI_Long)5L;
	    y_in_window = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    gensymed_symbol_2 = IFIX(x_in_workspace);
	    scale_1 = Current_image_x_scale;
	    value = x_in_window - IFIX(Current_x_origin_of_drawing);
	    if (IFIX(scale_1) == (SI_Long)4096L)
		gensymed_symbol_3 = value;
	    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		    value && value < IFIX(Isqrt_of_most_positive_fixnum)))
		gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,
			FIX(value)));
	    else if (value >= (SI_Long)0L) {
		temp_4 = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  -  
			- (SI_Long)1L)) / IFIX(scale_1);
		gensymed_symbol_3 = temp_4;
	    }
	    else {
		temp_4 = (( - value << (SI_Long)12L) + (IFIX(scale_1) >>  
			-  - (SI_Long)1L)) / IFIX(scale_1);
		temp_4 = IFIX(FIXNUM_NEGATE(FIX(temp_4)));
		gensymed_symbol_3 = temp_4;
	    }
	    value = gensymed_symbol_2 - gensymed_symbol_3;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
	    current_x_origin_of_drawing = FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		    1);
	      gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	      scale = Current_image_y_scale;
	      gensymed_symbol_2 = IFIX(y_in_workspace);
	      scale_1 = Current_image_y_scale;
	      value = y_in_window - IFIX(Current_y_origin_of_drawing);
	      if (IFIX(scale_1) == (SI_Long)4096L)
		  gensymed_symbol_3 = value;
	      else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value && value < IFIX(Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol_3 = IFIX(inverse_scalef_function(scale_1,
			  FIX(value)));
	      else if (value >= (SI_Long)0L) {
		  temp_4 = ((value << (SI_Long)12L) + (IFIX(scale_1) >>  - 
			   - (SI_Long)1L)) / IFIX(scale_1);
		  gensymed_symbol_3 = temp_4;
	      }
	      else {
		  temp_4 = (( - value << (SI_Long)12L) + (IFIX(scale_1) >> 
			   -  - (SI_Long)1L)) / IFIX(scale_1);
		  temp_4 = IFIX(FIXNUM_NEGATE(FIX(temp_4)));
		  gensymed_symbol_3 = temp_4;
	      }
	      value = gensymed_symbol_2 - gensymed_symbol_3;
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_2 = value;
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		      && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		  gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
	      current_y_origin_of_drawing = FIX(gensymed_symbol_1 - 
		      gensymed_symbol_2);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		      0);
		SAVE_VALUES(draw_icon_for_entity(widget_entity));
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else if (EQ(Purpose_of_frame_projecting,Qdrawing_contents)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qcompute_content_region)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qmove_elevator)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (EQ(Purpose_of_frame_projecting,Qmouse_tracking)) {
	spot = make_close_box_spot_1();
	result = push_last_spot(Mouse_pointer_of_frame,spot,Block_of_frame);
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
}

static Object array_constant;      /* # */

/* WRITE-FRAME-DESCRIPTION-FROM-SLOT */
Object write_frame_description_from_slot(frame_description_qm,gensymed_symbol)
    Object frame_description_qm, gensymed_symbol;
{
    x_note_fn_call(89,160);
    if (frame_description_qm)
	return write_frame_description_1(frame_description_qm);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Qcolor;              /* color */

static Object string_constant;     /* "Invalid color: ~a" */

static Object Qwidth;              /* width */

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_1;   /* "~NT " */

static Object string_constant_2;   /* "~NV must be one of the following types: ~a" */

/* FRAME-DESCRIPTION-EVALUATION-SETTER */
Object frame_description_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object border_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, color, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(89,161);
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
		      goto end_frame_description_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_4))
	result = VALUES_1(Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_5)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	border_element = Nil;
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
	border_element = validated_elt;
	color = estructure_slot(border_element,Qcolor,Nil);
	if ( !TRUEP(color_or_metacolor_p(color))) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant,color);
	    result = VALUES_2(temp,temp_1);
	    goto end_setter;
	}
	ab_loopvar__2 = phrase_cons(phrase_list_3(Qframe,color,
		estructure_slot(border_element,Qwidth,Nil)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(phrase_cons(Qborder,temp_1),Nil);
      end_setter:;
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_1,list_constant_4);
		  tformat(2,string_constant_1,list_constant_5);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_2,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_frame_description_evaluation_setter:
    return result;
}

static Object Qab_structure;       /* structure */

/* FRAME-DESCRIPTION-EVALUATION-GETTER */
Object frame_description_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object color_width_pairs, frame_component, ab_loop_list_, color, width;
    Object ab_loop_list__1, ab_loop_desetq_, temp, pair, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol_1, temp_1;
    Object item_or_value, x2, svref_new_value, sequence;
    SI_Long gensymed_symbol_2, svref_arg_2;
    char temp_2;

    x_note_fn_call(89,162);
    if (slot_value) {
	color_width_pairs = Qnil;
	frame_component = Nil;
	ab_loop_list_ = slot_value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(frame_component),Qborder)) {
	    color = Nil;
	    width = Nil;
	    ab_loop_list__1 = CDR(frame_component);
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	    temp = CDR(ab_loop_desetq_);
	    color = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    width = CAR(temp);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    color_width_pairs = gensym_cons_1(gensym_cons_1(color,width),
		    color_width_pairs);
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:
	color_width_pairs = nreverse(color_width_pairs);
	pair = Nil;
	ab_loop_list_ = color_width_pairs;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_2 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_2 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = Qcolor;
	else {
	    temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qcolor;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CAR(pair);
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
	    SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    item_or_value = CAR(pair);
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
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = Qwidth;
	else {
	    temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qwidth;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CDR(pair);
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
	    SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    item_or_value = CDR(pair);
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
	ab_loopvar__1 = eval_cons_1(eval_cons_1(gensymed_symbol_1,
		Qab_structure),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_2;
      end_loop_2:
	sequence = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	sequence = Qnil;
      end_1:;
	reclaim_gensym_tree_1(color_width_pairs);
	temp = sequence;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* ";~%" */

/* WRITE-FRAME-DESCRIPTION-1 */
Object write_frame_description_1(frame_description)
    Object frame_description;
{
    Object first_qm, frame_component, remaining_components, ab_loop_list_;

    x_note_fn_call(89,163);
    first_qm = T;
    frame_component = Nil;
    remaining_components = Nil;
    ab_loop_list_ = frame_description;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame_component = CAR(ab_loop_list_);
    remaining_components = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(Qpaper,CAR(frame_component))) {
	if ( !TRUEP(first_qm))
	    tformat(1,string_constant_3);
	first_qm = Nil;
	write_frame_component(frame_component);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_1;    /* # */

static Object string_constant_4;   /* ", " */

static Object string_constant_5;   /* " ~D ~(~A~)" */

static Object string_constant_6;   /* "~(~A~)" */

static Object string_constant_7;   /* "along the ~(~A~) using ~D workspace units place: " */

static Object string_constant_8;   /* "~%    " */

static Object string_constant_9;   /* ",~%    " */

static Object string_constant_10;  /* "a ~(~A~)" */

static Object string_constant_11;  /* " of size ~D" */

static Object string_constant_12;  /* " of variable size" */

/* WRITE-FRAME-COMPONENT */
Object write_frame_component(frame_component)
    Object frame_component;
{
    Object temp, kind, color, size, ab_loop_list_, first_qm;
    Object ab_loop_iter_flag_, ab_loop_desetq_, partition, components, where;
    Object partition_size, layouts, component, layout, ab_loop_list__1;

    x_note_fn_call(89,164);
    temp = CAR(frame_component);
    if (EQ(temp,Qborder)) {
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)6L));
	kind = Nil;
	color = Nil;
	size = Nil;
	ab_loop_list_ = REST(frame_component);
	first_qm = T;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	kind = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	color = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	size = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_qm = Nil;
	if ( !TRUEP(first_qm))
	    tformat(1,string_constant_4);
	tformat(3,string_constant_5,size,color);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (EQ(temp,Qresize_box) || EQ(temp,Qclose_box) || EQ(temp,
	    Qscroll_bar))
	return tformat(2,string_constant_6,FIRST(frame_component));
    else if (EQ(temp,Qframe_section)) {
	partition = SECOND(frame_component);
	components = CDDR(frame_component);
	where = FIRST(partition);
	partition_size = SECOND(partition);
	layouts = CDDR(partition);
	tformat(3,string_constant_7,where,partition_size);
	component = Nil;
	ab_loop_list_ = components;
	layout = Nil;
	ab_loop_list__1 = layouts;
	first_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	layout = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_qm = Nil;
	if (first_qm)
	    tformat(1,string_constant_8);
	else
	    tformat(1,string_constant_9);
	tformat(2,string_constant_10,FIRST(component));
	if (layout)
	    tformat(2,string_constant_11,layout);
	else
	    tformat(1,string_constant_12);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "The frame description width ~a must be a non-negative integer." */

/* COMPILE-FRAME-DESCRIPTION-FOR-SLOT */
Object compile_frame_description_for_slot varargs_1(int, n)
{
    Object parse_of_frame_description, gensymed_symbol, gensymed_symbol_1;
    Object frame_component, ab_loop_list_, color, width, ab_loop_list__1;
    Object ab_loop_desetq_, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,165);
    INIT_ARGS_nonrelocating();
    parse_of_frame_description = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (parse_of_frame_description) {
	frame_component = Nil;
	ab_loop_list_ = parse_of_frame_description;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(frame_component),Qborder)) {
	    color = Nil;
	    width = Nil;
	    ab_loop_list__1 = CDR(frame_component);
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	    temp = CDR(ab_loop_desetq_);
	    color = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    width = CAR(temp);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (IFIX(width) < (SI_Long)0L) {
		temp_1 = Bad_phrase;
		temp = tformat_text_string(2,string_constant_13,width);
		return VALUES_2(temp_1,temp);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:
	return phrase_cons(phrase_cons(Qpaper,Nil),parse_of_frame_description);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object Frame_description_reference_of_built_in_frame_style_kbprop = UNBOUND;

static Object list_constant_6;     /* # */

static Object Qdialog_workspace_frame_style;  /* dialog-workspace-frame-style */

static Object list_constant_7;     /* # */

static Object Qmenu_workspace_frame_style;  /* menu-workspace-frame-style */

static Object list_constant_8;     /* # */

static Object Qworkspace_title_bar_frame_style_small;  /* workspace-title-bar-frame-style-small */

static Object Qworkspace_title_bar_frame_style_large;  /* workspace-title-bar-frame-style-large */

static Object Qwalking_menu_frame_style;  /* walking-menu-frame-style */

static Object Kcredits_workspace_frame_style;  /* :credits-workspace-frame-style */

static Object list_constant_9;     /* # */

static Object Knew_credits_workspace_frame_style;  /* :new-credits-workspace-frame-style */

static Object list_constant_10;    /* # */

static Object Kitem_frame_used_when_frame_style_is_incomplete;  /* :item-frame-used-when-frame-style-is-incomplete */

static Object Kedit_box_with_scroll_bar_frame_style;  /* :edit-box-with-scroll-bar-frame-style */

static Object list_constant_11;    /* # */

static Object Kedit_box_frame_style;  /* :edit-box-frame-style */

static Object list_constant_12;    /* # */

static Object Qthick_workspace_frame_style;  /* thick-workspace-frame-style */

static Object list_constant_13;    /* # */

static Object Qextremely_thin_workspace_frame_style;  /* extremely-thin-workspace-frame-style */

static Object Qdefault_workspace_frame_style;  /* default-workspace-frame-style */

static Object list_constant_14;    /* # */

/* LOOKUP-FRAME-DESCRIPTION-REFERENCE-OF-FRAME-STYLE */
Object lookup_frame_description_reference_of_frame_style(frame_style,
	    default_frame_style)
    Object frame_style, default_frame_style;
{
    Object temp, temp_1, frame_style_reference, svref_new_value;

    x_note_fn_call(89,166);
    temp = 
	    lookup_frame_description_reference_from_frame_style_definition_qm(frame_style);
    if (temp);
    else
	temp = lookup_kb_specific_property_value(frame_style,
		Frame_description_reference_of_built_in_frame_style_kbprop);
    if (temp)
	return VALUES_1(temp);
    else {
	if ( !TRUEP(memq_function(frame_style,list_constant_6)))
	    frame_style = default_frame_style;
	temp = lookup_kb_specific_property_value(frame_style,
		Frame_description_reference_of_built_in_frame_style_kbprop);
	if (temp)
	    return VALUES_1(temp);
	else {
	    temp = frame_style;
	    if (EQ(frame_style,Qdialog_workspace_frame_style))
		temp_1 = list_constant_7;
	    else if (EQ(frame_style,Qmenu_workspace_frame_style))
		temp_1 = list_constant_8;
	    else if (EQ(frame_style,Qworkspace_title_bar_frame_style_small))
		temp_1 = Workspace_title_bar_frame_style_small;
	    else if (EQ(frame_style,Qworkspace_title_bar_frame_style_large))
		temp_1 = Workspace_title_bar_frame_style_large;
	    else if (EQ(frame_style,Qwalking_menu_frame_style))
		temp_1 = list_constant_8;
	    else if (EQ(frame_style,Kcredits_workspace_frame_style))
		temp_1 = list_constant_9;
	    else if (EQ(frame_style,Knew_credits_workspace_frame_style))
		temp_1 = list_constant_10;
	    else if (EQ(frame_style,
		    Kitem_frame_used_when_frame_style_is_incomplete))
		temp_1 = list_constant_8;
	    else if (EQ(frame_style,Kedit_box_with_scroll_bar_frame_style))
		temp_1 = list_constant_11;
	    else if (EQ(frame_style,Kedit_box_frame_style))
		temp_1 = list_constant_12;
	    else if (EQ(frame_style,Qthick_workspace_frame_style))
		temp_1 = list_constant_13;
	    else if (EQ(frame_style,Qextremely_thin_workspace_frame_style))
		temp_1 = list_constant_8;
	    else if (EQ(frame_style,Qdefault_workspace_frame_style))
		temp_1 = list_constant_14;
	    else
		temp_1 = Qnil;
	    frame_style_reference = 
		    create_frame_description_reference(copy_tree_using_graphics_conses_1(temp_1));
	    svref_new_value = FIXNUM_ADD1(ISVREF(frame_style_reference,
		    (SI_Long)1L));
	    SVREF(frame_style_reference,FIX((SI_Long)1L)) = svref_new_value;
	    return mutate_kb_specific_property_value(temp,
		    frame_style_reference,
		    Frame_description_reference_of_built_in_frame_style_kbprop);
	}
    }
}

static Object Qframe_style;        /* frame-style */

/* IMAGE-PLANE-HAS-DEFAULT-FRAME-P */
Object image_plane_has_default_frame_p(image_plane)
    Object image_plane;
{
    Object workspace, temp, frame_description_reference;

    x_note_fn_call(89,167);
    workspace = ISVREF(image_plane,(SI_Long)5L);
    temp =  !TRUEP(workspace) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(get_lookup_slot_value(workspace,Qframe_style)) ? T :
		 Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	frame_description_reference = ISVREF(image_plane,(SI_Long)10L);
	return VALUES_1(EQ(frame_description_reference,
		get_default_workspace_frame_description_reference()) ? T : 
		Nil);
    }
}

/* GET-DEFAULT-WORKSPACE-FRAME-DESCRIPTION-REFERENCE */
Object get_default_workspace_frame_description_reference()
{
    x_note_fn_call(89,168);
    return lookup_frame_description_reference_of_frame_style(Qdefault_workspace_frame_style,
	    Qdefault_workspace_frame_style);
}

/* BLOCK-IS-ALLOWED-TO-HAVE-FRAME-P */
Object block_is_allowed_to_have_frame_p(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,169);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
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
    if (temp)
	return VALUES_1(T);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Edit_box_class_description,
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
	    return VALUES_1(T);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		return VALUES_1(Nil);
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* DEFAULT-FRAME-STYLE-OF-BLOCK-WHEN-USER-REQUEST-IS-BOGUS? */
Object default_frame_style_of_block_when_user_request_is_bogus_qm(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,170);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
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
    if (temp)
	return VALUES_1(Qdefault_workspace_frame_style);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	    return VALUES_1(Kitem_frame_used_when_frame_style_is_incomplete);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qmenu_workspace_for_is_for_walking_submenu_p;  /* menu-workspace-for-is-for-walking-submenu-p */

static Object Qworkspace_title_bar_frame_style;  /* workspace-title-bar-frame-style */

/* DEFAULT-FRAME-STYLE-OF-BLOCK? */
Object default_frame_style_of_block_qm(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,171);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Menu_workspace_class_description,(SI_Long)18L));
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
	if (New_g2_classic_ui_p) {
	    if (get_slot_value_function(block,
		    Qmenu_workspace_for_is_for_walking_submenu_p,Nil))
		return VALUES_1(Qwalking_menu_frame_style);
	    else
		return get_ui_parameter(1,Qworkspace_title_bar_frame_style);
	}
	else
	    return VALUES_1(Qmenu_workspace_frame_style);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Logbook_page_class_description,(SI_Long)18L));
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
	    return VALUES_1(Qdefault_workspace_frame_style);
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
		if (New_g2_classic_ui_p)
		    return get_ui_parameter(1,
			    Qworkspace_title_bar_frame_style);
		else
		    return VALUES_1(Qdefault_workspace_frame_style);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    return VALUES_1(Nil);
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

static Object Qframe_style_of_edit_box;  /* frame-style-of-edit-box */

static Object Qedit_box;           /* edit-box */

/* SET-FRAME-STYLE-OF-BLOCK */
Object set_frame_style_of_block(block,frame_style)
    Object block, frame_style;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,172);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
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
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(block,Qframe_style);
	return set_lookup_slot_value_1(block,Qframe_style,frame_style);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Edit_box_class_description,
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
	    return set_slot_value_function(block,Qframe_style_of_edit_box,
		    frame_style,Qedit_box);
	else
	    return VALUES_1(Qnil);
    }
}

/* LOOKUP-FRAME-DESCRIPTION-REFERENCE-OF-BLOCK? */
Object lookup_frame_description_reference_of_block_qm(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector, frame_style;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,173);
    if (block_is_allowed_to_have_frame_p(block)) {
	gensymed_symbol = ISVREF(block,(SI_Long)1L);
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
	    frame_style = get_lookup_slot_value(block,Qframe_style);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Edit_box_class_description,(SI_Long)18L));
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
		frame_style = get_slot_value_function(block,
			Qframe_style_of_edit_box,Qedit_box);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    frame_style = Nil;
		else
		    frame_style = Qnil;
	    }
	}
	if (frame_style);
	else
	    frame_style = default_frame_style_of_block_qm(block);
	if ( !TRUEP(frame_style))
	    return VALUES_1(Nil);
	else
	    return lookup_frame_description_reference_of_frame_style(frame_style,
		    default_frame_style_of_block_when_user_request_is_bogus_qm(block));
    }
    else
	return VALUES_1(Nil);
}

/* CREATE-FRAME-TRANSFORMS-OF-IMAGE-PLANE */
Object create_frame_transforms_of_image_plane(workspace,image_plane)
    Object workspace, image_plane;
{
    Object frame_description_reference, svref_new_value, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, temp;

    x_note_fn_call(89,174);
    frame_description_reference = Nil;
    frame_description_reference = 
	    lookup_frame_description_reference_of_block_qm(workspace);
    if (frame_description_reference) {
	svref_new_value = FIXNUM_ADD1(ISVREF(frame_description_reference,
		(SI_Long)1L));
	SVREF(frame_description_reference,FIX((SI_Long)1L)) = svref_new_value;
	make_frame_transform(workspace,image_plane,
		frame_description_reference);
    }
    frame_description_reference = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
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
    frame_description_reference = 
	    lookup_frame_description_reference_of_block_qm(subblock);
    if (frame_description_reference) {
	temp = subblock;
	svref_new_value = FIXNUM_ADD1(ISVREF(frame_description_reference,
		(SI_Long)1L));
	SVREF(frame_description_reference,FIX((SI_Long)1L)) = svref_new_value;
	make_frame_transform(temp,image_plane,frame_description_reference);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FAST-LOOKUP-FRAME-DESCRIPTION-REFERENCE-OF-BLOCK? */
Object fast_lookup_frame_description_reference_of_block_qm(block)
    Object block;
{
    Object frame_transforms, frame_transform, frame_style, temp;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(89,175);
    frame_transforms = Nil;
    frame_transform = Nil;
    frame_style = Nil;
    if (showing_p(block,T)) {
	frame_transforms = get_lookup_slot_value_given_default(block,
		Qframe_transforms_of_block,Nil);
	if (frame_transforms) {
	    temp = CAR(frame_transforms);
	    frame_transform = CDR(temp);
	    temp_1 = TRUEP(frame_transform);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(ISVREF(frame_transform,(SI_Long)5L));
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol = ISVREF(block,(SI_Long)1L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = get_lookup_slot_value(block,Qframe_style);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Edit_box_class_description,(SI_Long)18L));
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
	    if (temp_1)
		temp = get_slot_value_function(block,
			Qframe_style_of_edit_box,Qedit_box);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    temp = Nil;
		else
		    temp = Qnil;
	    }
	}
	if (temp);
	else
	    temp = default_frame_style_of_block_qm(block);
	frame_style = temp;
	if (frame_style)
	    return lookup_frame_description_reference_of_frame_style(frame_style,
		    Kitem_frame_used_when_frame_style_is_incomplete);
	else
	    return VALUES_1(Nil);
    }
}

static Object Qreconsider_formatting;  /* reconsider-formatting */

static Object Qframe_description_reference;  /* frame-description-reference */

/* CLEAN-FRAME-DESCRIPTION-REFERENCES */
Object clean_frame_description_references()
{
    Object workstation, ab_loop_list_, gensym_window, pane, ab_loop_list__1;
    Object temp, image_plane, ab_loop_list__2;
    Object frame_description_reference_of_image_plane, method, frame;
    Object generic_method_name, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, frame_transform, ab_loop_it_, ab_queue_form_;
    Object ab_next_queue_element_, subblock, frame_transforms_of_block;
    SI_Long id, temp_1;
    char temp_2;

    x_note_fn_call(89,176);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    pane = Nil;
    ab_loop_list__1 = ISVREF(gensym_window,(SI_Long)3L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    pane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = ISVREF(pane,(SI_Long)5L);
    if (ISVREF(FIRST(temp),(SI_Long)5L)) {
	image_plane = Nil;
	ab_loop_list__2 = ISVREF(pane,(SI_Long)5L);
	frame_description_reference_of_image_plane = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	image_plane = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	frame_description_reference_of_image_plane = ISVREF(image_plane,
		(SI_Long)10L);
	if (ISVREF(frame_description_reference_of_image_plane,(SI_Long)3L)) {
	    method = Qreconsider_formatting;
	    frame = ISVREF(image_plane,(SI_Long)5L);
	    temp = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L);
	    generic_method_name = method;
	    id = (SI_Long)0L;
	  next_loop_3:
	    if (id >= IFIX(Maximum_number_of_generic_methods))
		goto end_loop_3;
	    if (EQ(ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
		    id),generic_method_name)) {
		temp_1 = id;
		goto end_1;
	    }
	    id = id + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp_1 = id;
	    goto end_1;
	    temp_1 = IFIX(Qnil);
	  end_1:;
	    gensymed_symbol = ISVREF(ISVREF(temp,temp_1),(SI_Long)1L);
	    gensymed_symbol_1 = frame;
	    gensymed_symbol_2 = Qframe_description_reference;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	frame_transform = ISVREF(image_plane,(SI_Long)36L);
	ab_loop_it_ = Nil;
      next_loop_4:
	if ( !TRUEP(frame_transform))
	    goto end_loop_4;
	ab_loop_it_ = ISVREF(ISVREF(frame_transform,(SI_Long)5L),(SI_Long)3L);
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	frame_transform = ISVREF(frame_transform,(SI_Long)2L);
	goto next_loop_4;
      end_loop_4:
	temp_2 = TRUEP(Qnil);
      end_2:;
	if (temp_2) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(image_plane,
		    (SI_Long)5L),(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    frame_transforms_of_block = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_5:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_5;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    frame_transforms_of_block = 
		    get_lookup_slot_value_given_default(subblock,
		    Qframe_transforms_of_block,Nil);
	    if (frame_transforms_of_block) {
		temp = FIRST(frame_transforms_of_block);
		temp_2 = TRUEP(ISVREF(ISVREF(CDR(temp),(SI_Long)5L),
			(SI_Long)3L));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subblock,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)39L),(SI_Long)1L);
		gensymed_symbol_1 = subblock;
		gensymed_symbol_2 = Qframe_description_reference;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    goto next_loop_5;
	  end_loop_5:;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qformatting_configuration_changed;  /* formatting-configuration-changed */

static Object Qimage_plane_frame_lookup_eq;  /* image-plane-frame-lookup-eq */

/* RECONSIDER-FORMATTING-FOR-BLOCK */
Object reconsider_formatting_for_block(block,formatting_dimension)
    Object block, formatting_dimension;
{
    Object frame_transforms_of_block, sub_class_bit_vector, image_plane;
    Object ab_loop_list_, temp_1, new_frame_description_reference_qm;
    Object old_frame_description_reference_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(89,177);
    if (EQ(formatting_dimension,Qframe_description_reference)) {
	frame_transforms_of_block = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
	if (temp) {
	    image_plane = Nil;
	    ab_loop_list_ = ISVREF(block,(SI_Long)16L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    image_plane = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ISVREF(ISVREF(image_plane,(SI_Long)10L),(SI_Long)3L))
		return rebind_frame_description_reference_of_workspace(block);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else {
	    frame_transforms_of_block = 
		    get_lookup_slot_value_given_default(block,
		    Qframe_transforms_of_block,Nil);
	    if (frame_transforms_of_block) {
		temp_1 = CAR(frame_transforms_of_block);
		temp = TRUEP(ISVREF(ISVREF(CDR(temp_1),(SI_Long)5L),
			(SI_Long)3L));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = frame_transforms_of_block;
		return rebind_frame_description_references_of_block(block,
			temp_1,
			lookup_frame_description_reference_of_block_qm(block));
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else if (EQ(formatting_dimension,Qformatting_configuration_changed)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
	if (temp) {
	    image_plane = Nil;
	    ab_loop_list_ = ISVREF(block,(SI_Long)16L);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    image_plane = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(funcall_for_workstation_of_image_plane(4,
		    image_plane,
		    SYMBOL_FUNCTION(Qimage_plane_frame_lookup_eq),
		    image_plane,block)))
		return rebind_frame_description_reference_of_workspace(block);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else {
	    new_frame_description_reference_qm = Nil;
	    old_frame_description_reference_qm = Nil;
	    frame_transforms_of_block = Nil;
	    if (showing_p(block,T)) {
		frame_transforms_of_block = 
			get_lookup_slot_value_given_default(block,
			Qframe_transforms_of_block,Nil);
		if (frame_transforms_of_block) {
		    temp_1 = FIRST(frame_transforms_of_block);
		    old_frame_description_reference_qm = 
			    ISVREF(CDR(temp_1),(SI_Long)5L);
		}
		new_frame_description_reference_qm = 
			lookup_frame_description_reference_of_block_qm(block);
		temp_1 = old_frame_description_reference_qm;
		new_frame_description_reference_qm = 
			lookup_frame_description_reference_of_block_qm(block);
		if ( !EQ(temp_1,new_frame_description_reference_qm))
		    return rebind_frame_description_references_of_block(block,
			    frame_transforms_of_block,
			    new_frame_description_reference_qm);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Qnil);
}

/* IMAGE-PLANE-FRAME-LOOKUP-EQ */
Object image_plane_frame_lookup_eq(image_plane,workspace)
    Object image_plane, workspace;
{
    Object temp;

    x_note_fn_call(89,178);
    temp = lookup_frame_description_reference_of_block_qm(workspace);
    return VALUES_1(EQ(temp,ISVREF(image_plane,(SI_Long)10L)) ? T : Nil);
}

/* REBIND-FRAME-DESCRIPTION-REFERENCES-OF-BLOCK */
Object rebind_frame_description_references_of_block(block,
	    old_frame_transforms_of_block,new_frame_description_reference_qm)
    Object block, old_frame_transforms_of_block;
    Object new_frame_description_reference_qm;
{
    Object workspace_qm, current_drawing_priority, frame_transform;
    Object ab_loop_list_, ab_loop_desetq_, svref_new_value, image_planes;
    Object image_plane, temp_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(89,179);
    workspace_qm = Nil;
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    0);
      if (T)
	  update_images_of_block(block,T,Nil);
      if (old_frame_transforms_of_block) {
	  if (new_frame_description_reference_qm) {
	      frame_transform = Nil;
	      ab_loop_list_ = old_frame_transforms_of_block;
	      ab_loop_desetq_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      frame_transform = CDR(ab_loop_desetq_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      release_frame_description_reference_if_any(ISVREF(frame_transform,
		      (SI_Long)5L));
	      svref_new_value = 
		      FIXNUM_ADD1(ISVREF(new_frame_description_reference_qm,
		      (SI_Long)1L));
	      SVREF(new_frame_description_reference_qm,FIX((SI_Long)1L)) = 
		      svref_new_value;
	      SVREF(frame_transform,FIX((SI_Long)5L)) = 
		      new_frame_description_reference_qm;
	      goto next_loop;
	    end_loop:;
	  }
	  else
	      reclaim_frame_transforms_of_block(block);
      }
      else if (new_frame_description_reference_qm) {
	  image_planes = Nil;
	  workspace_qm = get_workspace_if_any(block);
	  if (workspace_qm) {
	      image_planes = ISVREF(workspace_qm,(SI_Long)16L);
	      temp = TRUEP(image_planes);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      image_plane = Nil;
	      ab_loop_list_ = image_planes;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      image_plane = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      temp_1 = image_plane;
	      svref_new_value = 
		      FIXNUM_ADD1(ISVREF(new_frame_description_reference_qm,
		      (SI_Long)1L));
	      SVREF(new_frame_description_reference_qm,FIX((SI_Long)1L)) = 
		      svref_new_value;
	      make_frame_transform(block,temp_1,
		      new_frame_description_reference_qm);
	      goto next_loop_1;
	    end_loop_1:;
	  }
      }
      else;
      if (T)
	  update_images_of_block(block,Nil,Nil);
    POP_SPECIAL();
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return enlarge_workspace_for_block_rectangle_if_necessary(block,
		workspace_qm);
    else
	return VALUES_1(Nil);
}

static Object Qrebind_frame_description_reference_image_plane;  /* rebind-frame-description-reference-image-plane */

/* REBIND-FRAME-DESCRIPTION-REFERENCE-OF-WORKSPACE */
Object rebind_frame_description_reference_of_workspace(workspace)
    Object workspace;
{
    Object image_plane, ab_loop_list_;

    x_note_fn_call(89,180);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    funcall_for_workstation_of_image_plane(4,image_plane,
	    SYMBOL_FUNCTION(Qrebind_frame_description_reference_image_plane),
	    workspace,image_plane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REBIND-FRAME-DESCRIPTION-REFERENCE-IMAGE-PLANE */
Object rebind_frame_description_reference_image_plane(workspace,image_plane)
    Object workspace, image_plane;
{
    Object new_frame_description_reference, svref_new_value, old_left, old_top;
    Object old_right, old_bottom, temp, temp_1, temp_2, temp_3;

    x_note_fn_call(89,181);
    new_frame_description_reference = 
	    lookup_frame_description_reference_of_block_qm(workspace);
    if ( !EQ(new_frame_description_reference,ISVREF(image_plane,
		(SI_Long)10L))) {
	release_frame_description_reference_if_any(ISVREF(image_plane,
		(SI_Long)10L));
	svref_new_value = 
		FIXNUM_ADD1(ISVREF(new_frame_description_reference,
		(SI_Long)1L));
	SVREF(new_frame_description_reference,FIX((SI_Long)1L)) = 
		svref_new_value;
	SVREF(image_plane,FIX((SI_Long)10L)) = new_frame_description_reference;
	old_left = ISVREF(image_plane,(SI_Long)15L);
	old_top = ISVREF(image_plane,(SI_Long)16L);
	old_right = ISVREF(image_plane,(SI_Long)17L);
	old_bottom = ISVREF(image_plane,(SI_Long)18L);
	set_up_edges_for_image_plane(image_plane);
	recompute_visible_regions_for_pane(ISVREF(image_plane,(SI_Long)2L));
	if (native_image_plane_p(image_plane)) {
	    update_native_image_plane_frame_style(image_plane);
	    synchronize_shape_of_native_image_plane(1,image_plane);
	}
	temp = ISVREF(image_plane,(SI_Long)15L);
	temp_1 = ISVREF(image_plane,(SI_Long)16L);
	temp_2 = ISVREF(image_plane,(SI_Long)17L);
	temp_3 = ISVREF(image_plane,(SI_Long)18L);
	return invalidate_rectangle_of_window(ISVREF(ISVREF(image_plane,
		(SI_Long)2L),(SI_Long)2L),FIXNUM_MIN(old_left,temp),
		FIXNUM_MIN(old_top,temp_1),FIXNUM_MAX(old_right,temp_2),
		FIXNUM_MAX(old_bottom,temp_3));
    }
    else
	return VALUES_1(Nil);
}

/* RECONSIDER-FORMATTING */
Object reconsider_formatting(block)
    Object block;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;

    x_note_fn_call(89,182);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)39L),(SI_Long)1L);
    gensymed_symbol_1 = block;
    gensymed_symbol_2 = Qformatting_configuration_changed;
    temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2);
    return VALUES_1(temp);
}

/* GET-IMAGE-PLANE-IF-ANY */
Object get_image_plane_if_any(workspace,pane)
    Object workspace, pane;
{
    Object image_plane, ab_loop_list_, temp;

    x_note_fn_call(89,183);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(image_plane,(SI_Long)5L),workspace)) {
	temp = image_plane;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-OR-MAKE-IMAGE-PLANE */
Object get_or_make_image_plane(workspace,pane)
    Object workspace, pane;
{
    Object temp;

    x_note_fn_call(89,184);
    temp = get_image_plane_if_any(workspace,pane);
    if (temp);
    else
	temp = get_available_image_plane(pane,
		lookup_frame_description_reference_of_block_qm(workspace),Nil);
    return VALUES_1(temp);
}

/* BLOCK-IS-ENCLOSED-BY-SUPERIOR-P */
Object block_is_enclosed_by_superior_p(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(89,185);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)32768L)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	block = gensymed_symbol;
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdraw_extent;        /* draw-extent */

/* ENLARGE-WORKSPACE-FOR-BLOCK-RECTANGLE-IF-NECESSARY */
Object enlarge_workspace_for_block_rectangle_if_necessary(block,
	    known_or_future_workspace_qm)
    Object block, known_or_future_workspace_qm;
{
    Object workspace_qm, purpose_of_extreme_edges, left_edge, top_edge;
    Object right_edge, bottom_edge;
    Declare_special(1);
    Object result;

    x_note_fn_call(89,186);
    workspace_qm = known_or_future_workspace_qm;
    if (workspace_qm);
    else
	workspace_qm = get_workspace_if_any(block);
    if (workspace_qm) {
	if ( !TRUEP(block_is_enclosed_by_superior_p(block))) {
	    purpose_of_extreme_edges = Qdraw_extent;
	    PUSH_SPECIAL_WITH_SYMBOL(Purpose_of_extreme_edges,Qpurpose_of_extreme_edges,purpose_of_extreme_edges,
		    0);
	      result = determine_extreme_edges_of_block(block);
	    POP_SPECIAL();
	    MVS_4(result,left_edge,top_edge,right_edge,bottom_edge);
	    return enlarge_workspace_if_necessary(5,workspace_qm,left_edge,
		    top_edge,right_edge,bottom_edge);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ENLARGE-WORKSPACE-FOR-BLOCK-AND-SUBBLOCKS-AS-NECESSARY */
Object enlarge_workspace_for_block_and_subblocks_as_necessary(block,workspace)
    Object block, workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;

    x_note_fn_call(89,187);
    if ( !TRUEP(block_is_enclosed_by_superior_p(block))) {
	enlarge_workspace_for_block_rectangle_if_necessary(block,workspace);
	if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L))) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
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
	    enlarge_workspace_for_block_and_subblocks_as_necessary(subblock,
		    workspace);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ENLARGE-WORKSPACE-IF-NECESSARY */
Object enlarge_workspace_if_necessary varargs_1(int, n)
{
    Object workspace, left_edge_of_new_element, top_edge_of_new_element;
    Object right_edge_of_new_element, bottom_edge_of_new_element;
    Object draw_document_p, current_draw_document_p;
    Object workspace_for_current_draw_document_qm, margin, new_left_qm;
    Object new_top_qm, new_right_qm, new_bottom_qm, temp, gensymed_symbol;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(89,188);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    left_edge_of_new_element = REQUIRED_ARG_nonrelocating();
    top_edge_of_new_element = REQUIRED_ARG_nonrelocating();
    right_edge_of_new_element = REQUIRED_ARG_nonrelocating();
    bottom_edge_of_new_element = REQUIRED_ARG_nonrelocating();
    draw_document_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_draw_document_p = draw_document_p;
    workspace_for_current_draw_document_qm = workspace;
    margin = ISVREF(workspace,(SI_Long)17L);
    new_left_qm = Nil;
    new_top_qm = Nil;
    new_right_qm = Nil;
    new_bottom_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Workspace_for_current_draw_document_qm,Qworkspace_for_current_draw_document_qm,workspace_for_current_draw_document_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_draw_document_p,Qcurrent_draw_document_p,current_draw_document_p,
	      0);
	temp = FIXNUM_MINUS(left_edge_of_new_element,margin);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	if (FIXNUM_LT(temp,gensymed_symbol))
	    new_left_qm = FIXNUM_MINUS(left_edge_of_new_element,margin);
	temp = FIXNUM_MINUS(top_edge_of_new_element,margin);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	if (FIXNUM_LT(temp,gensymed_symbol))
	    new_top_qm = FIXNUM_MINUS(top_edge_of_new_element,margin);
	temp = FIXNUM_ADD(right_edge_of_new_element,margin);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	if (FIXNUM_GT(temp,gensymed_symbol))
	    new_right_qm = FIXNUM_ADD(right_edge_of_new_element,margin);
	temp = FIXNUM_ADD(bottom_edge_of_new_element,margin);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	if (FIXNUM_GT(temp,gensymed_symbol))
	    new_bottom_qm = FIXNUM_ADD(bottom_edge_of_new_element,margin);
	if (change_edges_of_block(workspace,new_left_qm,new_top_qm,
		new_right_qm,new_bottom_qm))
	    result = move_image_plane_borders(workspace);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SHRINK-WRAP-WORKSPACE */
Object shrink_wrap_workspace(workspace)
    Object workspace;
{
    Object gensymed_symbol, subblocks, extreme_left_edge_so_far;
    Object extreme_top_edge_so_far, extreme_right_edge_so_far;
    Object extreme_bottom_edge_so_far;
    char temp;
    Declare_special(4);

    x_note_fn_call(89,189);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    temp = subblocks ?  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks)) : TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(has_background_images_p(workspace));
    if (temp) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	extreme_top_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_right_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	extreme_bottom_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		      0);
		gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		subblocks = gensymed_symbol;
		if (subblocks &&  ! 
			!TRUEP(constant_queue_next(ISVREF(subblocks,
			(SI_Long)2L),subblocks)))
		    update_extreme_edges_from_elements_function(workspace,Nil);
		update_extreme_edges_from_background_images(workspace);
		change_workspace_edges_after_including_margin(workspace,
			Extreme_left_edge_so_far,Extreme_top_edge_so_far,
			Extreme_right_edge_so_far,Extreme_bottom_edge_so_far);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* SHRINK-WRAP-WORKSPACE-AROUND-MAXIMUM-RECTANGLE */
Object shrink_wrap_workspace_around_maximum_rectangle(workspace)
    Object workspace;
{
    x_note_fn_call(89,190);
    return shrink_wrap_down_workspace_around_rectangle(workspace,
	    Most_negative_workspace_coordinate,
	    Most_negative_workspace_coordinate,
	    Most_positive_workspace_coordinate,
	    Most_positive_workspace_coordinate);
}

/* SHRINK-WRAP-DOWN-WORKSPACE-AROUND-RECTANGLE */
Object shrink_wrap_down_workspace_around_rectangle(workspace,
	    left_edge_limit,top_edge_limit,right_edge_limit,bottom_edge_limit)
    Object workspace, left_edge_limit, top_edge_limit, right_edge_limit;
    Object bottom_edge_limit;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, temp_1;
    Object temp_2, temp_3;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(89,191);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = FIXNUM_LT(gensymed_symbol,left_edge_limit);
    if (temp);
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp = FIXNUM_LT(gensymed_symbol,top_edge_limit);
    }
    if (temp);
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp = FIXNUM_GT(gensymed_symbol,right_edge_limit);
    }
    if (temp);
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp = FIXNUM_GT(gensymed_symbol,bottom_edge_limit);
    }
    if (temp) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	extreme_top_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_right_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	extreme_bottom_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		      0);
		update_extreme_edges_from_elements_function(workspace,Nil);
		update_extreme_edges_from_background_images(workspace);
		gensymed_symbol_1 = IFIX(FIXNUM_MIN(left_edge_limit,
			Extreme_left_edge_so_far));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_1 = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = IFIX(FIXNUM_MIN(top_edge_limit,
			Extreme_top_edge_so_far));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_2 = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = IFIX(FIXNUM_MAX(right_edge_limit,
			Extreme_right_edge_so_far));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_3 = FIX(MIN(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = IFIX(FIXNUM_MAX(bottom_edge_limit,
			Extreme_bottom_edge_so_far));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		result = change_workspace_edges_after_including_margin(workspace,
			temp_1,temp_2,temp_3,FIX(MIN(gensymed_symbol_1,
			gensymed_symbol_2)));
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qworkspace_frame;    /* workspace-frame */

/* CHANGE-SIZE-OF-WORKSPACE-TO-MINIMUM */
Object change_size_of_workspace_to_minimum(workspace)
    Object workspace;
{
    Object note_as_kb_state_change_qm, do_not_note_permanent_changes_p;
    Declare_special(2);

    x_note_fn_call(89,192);
    note_as_kb_state_change_qm = T;
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	      0);
	note_kb_state_change(workspace,Qworkspace_frame);
	shrink_wrap_workspace(workspace);
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CHANGE-WORKSPACE-EDGES-AFTER-MARGIN-CHANGE */
Object change_workspace_edges_after_margin_change(workspace)
    Object workspace;
{
    Object gensymed_symbol, subblocks, extreme_left_edge_so_far;
    Object extreme_top_edge_so_far, extreme_right_edge_so_far;
    Object extreme_bottom_edge_so_far, margin, temp_1, temp_2, temp_3;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(4);

    x_note_fn_call(89,193);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    temp = subblocks ?  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks)) : TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(has_background_images_p(workspace));
    if (temp) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	extreme_top_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_right_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	extreme_bottom_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		      0);
		update_extreme_edges_from_elements_function(workspace,Nil);
		update_extreme_edges_from_background_images(workspace);
		margin = ISVREF(workspace,(SI_Long)17L);
		gensymed_symbol_1 = 
			IFIX(FIXNUM_MINUS(Extreme_left_edge_so_far,margin));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_1 = FIX(MIN(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = 
			IFIX(FIXNUM_MINUS(Extreme_top_edge_so_far,margin));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_2 = FIX(MIN(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = 
			IFIX(FIXNUM_ADD(Extreme_right_edge_so_far,margin));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_3 = FIX(MAX(gensymed_symbol_1,gensymed_symbol_2));
		gensymed_symbol_1 = 
			IFIX(FIXNUM_ADD(Extreme_bottom_edge_so_far,margin));
		gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		new_change_workspace_edges(workspace,temp_1,temp_2,temp_3,
			FIX(MAX(gensymed_symbol_1,gensymed_symbol_2)));
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* CHANGE-WORKSPACE-EDGES-AFTER-INCLUDING-MARGIN */
Object change_workspace_edges_after_including_margin(workspace,
	    left_edge_for_workspace,top_edge_for_workspace,
	    right_edge_for_workspace,bottom_edge_for_workspace)
    Object workspace, left_edge_for_workspace, top_edge_for_workspace;
    Object right_edge_for_workspace, bottom_edge_for_workspace;
{
    Object margin;

    x_note_fn_call(89,194);
    margin = ISVREF(workspace,(SI_Long)17L);
    new_change_workspace_edges(workspace,
	    FIXNUM_MINUS(left_edge_for_workspace,margin),
	    FIXNUM_MINUS(top_edge_for_workspace,margin),
	    FIXNUM_ADD(right_edge_for_workspace,margin),
	    FIXNUM_ADD(bottom_edge_for_workspace,margin));
    return VALUES_1(Nil);
}

/* NEW-CHANGE-WORKSPACE-EDGES */
Object new_change_workspace_edges(workspace,left_edge_for_workspace,
	    top_edge_for_workspace,right_edge_for_workspace,
	    bottom_edge_for_workspace)
    Object workspace, left_edge_for_workspace, top_edge_for_workspace;
    Object right_edge_for_workspace, bottom_edge_for_workspace;
{
    x_note_fn_call(89,195);
    if (change_edges_of_block(workspace,left_edge_for_workspace,
	    top_edge_for_workspace,right_edge_for_workspace,
	    bottom_edge_for_workspace))
	move_image_plane_borders(workspace);
    return VALUES_1(Nil);
}

/* MOVE-IMAGE-PLANE-BORDERS */
Object move_image_plane_borders(workspace)
    Object workspace;
{
    Object image_plane, ab_loop_list_;

    x_note_fn_call(89,196);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reshape_image_plane_of_workspace(image_plane);
    require_that_image_plane_be_visible(1,image_plane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qinflate;            /* inflate */

/* RESHAPE-IMAGE-PLANE-OF-WORKSPACE */
Object reshape_image_plane_of_workspace(image_plane)
    Object image_plane;
{
    Object gensym_window, old_shape, old_left, old_top, old_right, old_bottom;
    Object old_left_1, old_top_1, old_right_1, old_bottom_1, region, new_shape;
    Object new_left, new_top, new_right, new_bottom, new_left_1, new_top_1;
    Object new_right_1, new_bottom_1, union_1, visible;
    Object current_drawing_priority;
    Declare_special(1);

    x_note_fn_call(89,197);
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    old_shape = copy_region(ISVREF(image_plane,(SI_Long)28L));
    old_left = ISVREF(image_plane,(SI_Long)15L);
    old_top = ISVREF(image_plane,(SI_Long)16L);
    old_right = ISVREF(image_plane,(SI_Long)17L);
    old_bottom = ISVREF(image_plane,(SI_Long)18L);
    old_left_1 = ISVREF(image_plane,(SI_Long)19L);
    old_top_1 = ISVREF(image_plane,(SI_Long)20L);
    old_right_1 = ISVREF(image_plane,(SI_Long)21L);
    old_bottom_1 = ISVREF(image_plane,(SI_Long)22L);
    set_up_edges_for_image_plane(image_plane);
    recompute_visible_regions_for_pane(ISVREF(image_plane,(SI_Long)2L));
    region = make_empty_region();
    new_shape = ISVREF(image_plane,(SI_Long)28L);
    new_left = ISVREF(image_plane,(SI_Long)15L);
    new_top = ISVREF(image_plane,(SI_Long)16L);
    new_right = ISVREF(image_plane,(SI_Long)17L);
    new_bottom = ISVREF(image_plane,(SI_Long)18L);
    new_left_1 = ISVREF(image_plane,(SI_Long)19L);
    new_top_1 = ISVREF(image_plane,(SI_Long)20L);
    new_right_1 = ISVREF(image_plane,(SI_Long)21L);
    new_bottom_1 = ISVREF(image_plane,(SI_Long)22L);
    if (FIXNUM_NE(new_left,old_left))
	region = add_rectangle_to_region(FIXNUM_MIN(old_left,new_left),
		FIXNUM_MIN(old_top,new_top),FIXNUM_MAX(old_left_1,
		new_left_1),FIXNUM_MAX(old_bottom,new_bottom),region);
    if (FIXNUM_NE(new_top,old_top) || 
	    image_plane_has_new_g2_classic_title_bar_p(image_plane) && 
	    (FIXNUM_NE(new_left,old_left) || FIXNUM_NE(new_right,old_right)))
	region = add_rectangle_to_region(FIXNUM_MIN(old_left,new_left),
		FIXNUM_MIN(old_top,new_top),FIXNUM_MAX(old_right,
		new_right),FIXNUM_MAX(old_top_1,new_top_1),region);
    if (FIXNUM_NE(new_right,old_right))
	region = add_rectangle_to_region(FIXNUM_MIN(old_right_1,
		new_right_1),FIXNUM_MIN(old_top,new_top),
		FIXNUM_MAX(old_right,new_right),FIXNUM_MAX(old_bottom,
		new_bottom),region);
    if (FIXNUM_NE(new_bottom,old_bottom))
	region = add_rectangle_to_region(FIXNUM_MIN(old_left,new_left),
		FIXNUM_MIN(old_bottom_1,new_bottom_1),FIXNUM_MAX(old_right,
		new_right),FIXNUM_MAX(old_bottom,new_bottom),region);
    union_1 = union_region(old_shape,new_shape);
    visible = intersect_region(region,union_1);
    if (ISVREF(image_plane,(SI_Long)37L)) {
	if ( !EQ(Native_image_plane_updated_by_client,image_plane))
	    synchronize_shape_of_native_image_plane(2,image_plane,Qinflate);
    }
    if ( !TRUEP(shape_decoupled_image_plane_p(image_plane))) {
	current_drawing_priority = Kdraw_as_late_as_possible;
	PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		0);
	  invalidate_region_of_window(gensym_window,visible);
	POP_SPECIAL();
	if (EQ(Current_drawing_priority,Kdraw_as_soon_as_possible))
	    force_process_drawing();
    }
    reclaim_region(visible);
    reclaim_region(union_1);
    reclaim_region(region);
    return reclaim_region(old_shape);
}

Object Default_required_visible_area_size_for_image_planes = UNBOUND;

/* REQUIRE-THAT-IMAGE-PLANE-BE-VISIBLE */
Object require_that_image_plane_be_visible varargs_1(int, n)
{
    Object image_plane;
    Object maximally_qm, temp, temp_1, width_of_minimum_area;
    Object height_of_minimum_area;
    SI_Long temp_2, temp_3, delta_x_to_pull_far_enough_into_pane;
    SI_Long delta_y_to_pull_far_enough_into_pane;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,198);
    INIT_ARGS_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    maximally_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (maximally_qm) {
	temp = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		ISVREF(image_plane,(SI_Long)6L));
	temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)17L),
		ISVREF(image_plane,(SI_Long)15L));
	width_of_minimum_area = FIXNUM_MIN(temp,temp_1);
    }
    else
	width_of_minimum_area = 
		Default_required_visible_area_size_for_image_planes;
    if (maximally_qm) {
	temp = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		ISVREF(image_plane,(SI_Long)7L));
	temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)18L),
		ISVREF(image_plane,(SI_Long)16L));
	height_of_minimum_area = FIXNUM_MIN(temp,temp_1);
    }
    else
	height_of_minimum_area = 
		Default_required_visible_area_size_for_image_planes;
    temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
	    width_of_minimum_area);
    temp_2 = IFIX(FIXNUM_MINUS(temp_1,
	    left_edge_of_view_in_window(image_plane)));
    temp_1 = FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),width_of_minimum_area);
    temp_3 = IFIX(FIXNUM_MINUS(temp_1,
	    right_edge_of_view_in_window(image_plane)));
    temp_3 = MAX(temp_3,(SI_Long)0L);
    delta_x_to_pull_far_enough_into_pane = MIN(temp_2,temp_3);
    temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
	    height_of_minimum_area);
    temp_2 = IFIX(FIXNUM_MINUS(temp_1,
	    top_edge_of_view_in_window(image_plane)));
    temp_1 = FIXNUM_ADD(ISVREF(image_plane,(SI_Long)7L),
	    height_of_minimum_area);
    temp_3 = IFIX(FIXNUM_MINUS(temp_1,
	    bottom_edge_of_view_in_window(image_plane)));
    temp_3 = MAX(temp_3,(SI_Long)0L);
    delta_y_to_pull_far_enough_into_pane = MIN(temp_2,temp_3);
    if (delta_x_to_pull_far_enough_into_pane != (SI_Long)0L || 
	    delta_y_to_pull_far_enough_into_pane != (SI_Long)0L)
	return move_image_plane(image_plane,
		FIX(delta_x_to_pull_far_enough_into_pane),
		FIX(delta_y_to_pull_far_enough_into_pane));
    else
	return VALUES_1(Nil);
}

/* ADD-TO-WORKSPACE */
Object add_to_workspace varargs_1(int, n)
{
    Object block, workspace, left_edge_for_block, top_edge_for_block;
    Object update_images_qm, confine_updating_to_block_rectangle_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,199);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    left_edge_for_block = REQUIRED_ARG_nonrelocating();
    top_edge_for_block = REQUIRED_ARG_nonrelocating();
    update_images_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    confine_updating_to_block_rectangle_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    return add_to_block(7,block,workspace,left_edge_for_block,
	    top_edge_for_block,update_images_qm,
	    confine_updating_to_block_rectangle_qm,workspace);
}

/* ADD-TO-BLOCK */
Object add_to_block varargs_1(int, n)
{
    Object block, superblock, left_edge_for_block, top_edge_for_block;
    Object update_images_qm, confine_updating_to_block_rectangle_qm;
    Object workspace_if_known_qm, gensymed_symbol_1, temp;
    Object sub_class_bit_vector;
    SI_Long gensymed_symbol, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(89,200);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    superblock = REQUIRED_ARG_nonrelocating();
    left_edge_for_block = REQUIRED_ARG_nonrelocating();
    top_edge_for_block = REQUIRED_ARG_nonrelocating();
    update_images_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    confine_updating_to_block_rectangle_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    workspace_if_known_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    perform_any_deferred_icon_set_up(superblock);
    perform_any_deferred_icon_set_up(block);
    gensymed_symbol = IFIX(left_edge_for_block);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    temp = FIX(gensymed_symbol - gensymed_symbol_2);
    gensymed_symbol = IFIX(top_edge_for_block);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    shift_block(block,temp,FIX(gensymed_symbol - gensymed_symbol_2));
    temp = workspace_if_known_qm;
    if (temp);
    else
	temp = get_workspace_if_any(superblock);
    enlarge_workspace_for_block_and_subblocks_as_necessary(block,temp);
    if (EQ(Current_drawing_transfer_mode,Kxor)) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	force_workspace_drawing(superblock);
    add_subblock(block,superblock);
    if (update_images_qm)
	return update_images_of_block(block,Nil,
		confine_updating_to_block_rectangle_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_uninteresting_block_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_uninteresting_block_spots, Qchain_of_available_uninteresting_block_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Uninteresting_block_spot_count, Quninteresting_block_spot_count);

Object Chain_of_available_uninteresting_block_spots_vector = UNBOUND;

/* UNINTERESTING-BLOCK-SPOT-STRUCTURE-MEMORY-USAGE */
Object uninteresting_block_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,201);
    temp = Uninteresting_block_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UNINTERESTING-BLOCK-SPOT-COUNT */
Object outstanding_uninteresting_block_spot_count()
{
    Object def_structure_uninteresting_block_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,202);
    gensymed_symbol = IFIX(Uninteresting_block_spot_count);
    def_structure_uninteresting_block_spot_variable = 
	    Chain_of_available_uninteresting_block_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_uninteresting_block_spot_variable))
	goto end_loop;
    def_structure_uninteresting_block_spot_variable = 
	    ISVREF(def_structure_uninteresting_block_spot_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UNINTERESTING-BLOCK-SPOT-1 */
Object reclaim_uninteresting_block_spot_1(uninteresting_block_spot)
    Object uninteresting_block_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,203);
    inline_note_reclaim_cons(uninteresting_block_spot,Nil);
    structure_being_reclaimed = uninteresting_block_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(uninteresting_block_spot,(SI_Long)2L));
      SVREF(uninteresting_block_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_uninteresting_block_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(uninteresting_block_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_uninteresting_block_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = uninteresting_block_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNINTERESTING-BLOCK-SPOT */
Object reclaim_structure_for_uninteresting_block_spot(uninteresting_block_spot)
    Object uninteresting_block_spot;
{
    x_note_fn_call(89,204);
    return reclaim_uninteresting_block_spot_1(uninteresting_block_spot);
}

static Object Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct;  /* g2-defstruct-structure-name::uninteresting-block-spot-g2-struct */

/* MAKE-PERMANENT-UNINTERESTING-BLOCK-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_uninteresting_block_spot_structure_internal()
{
    Object def_structure_uninteresting_block_spot_variable;
    Object defstruct_g2_uninteresting_block_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,205);
    def_structure_uninteresting_block_spot_variable = Nil;
    atomic_incff_symval(Quninteresting_block_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_uninteresting_block_spot_variable = Nil;
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
	defstruct_g2_uninteresting_block_spot_variable = the_array;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_uninteresting_block_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_uninteresting_block_spot_variable = 
		defstruct_g2_uninteresting_block_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_uninteresting_block_spot_variable);
}

/* MAKE-UNINTERESTING-BLOCK-SPOT-1 */
Object make_uninteresting_block_spot_1()
{
    Object def_structure_uninteresting_block_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(89,206);
    def_structure_uninteresting_block_spot_variable = 
	    ISVREF(Chain_of_available_uninteresting_block_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_uninteresting_block_spot_variable) {
	svref_arg_1 = Chain_of_available_uninteresting_block_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_uninteresting_block_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_uninteresting_block_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct;
    }
    else
	def_structure_uninteresting_block_spot_variable = 
		make_permanent_uninteresting_block_spot_structure_internal();
    inline_note_allocate_cons(def_structure_uninteresting_block_spot_variable,
	    Nil);
    SVREF(def_structure_uninteresting_block_spot_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_uninteresting_block_spot_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_uninteresting_block_spot_variable,
	    FIX((SI_Long)3L)) = T;
    SVREF(def_structure_uninteresting_block_spot_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_uninteresting_block_spot_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_uninteresting_block_spot_variable);
}

/* GENERATE-SPOT-FOR-BLOCK */
Object generate_spot_for_block(block,mouse_pointer)
    Object block, mouse_pointer;
{
    Object spot;

    x_note_fn_call(89,207);
    spot = make_uninteresting_block_spot_1();
    SVREF(spot,FIX((SI_Long)3L)) = Nil;
    return push_more_detailed_spot(mouse_pointer,spot,block);
}

Object The_type_description_of_simple_item_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_simple_item_spots, Qchain_of_available_simple_item_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_item_spot_count, Qsimple_item_spot_count);

Object Chain_of_available_simple_item_spots_vector = UNBOUND;

/* SIMPLE-ITEM-SPOT-STRUCTURE-MEMORY-USAGE */
Object simple_item_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(89,208);
    temp = Simple_item_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SIMPLE-ITEM-SPOT-COUNT */
Object outstanding_simple_item_spot_count()
{
    Object def_structure_simple_item_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(89,209);
    gensymed_symbol = IFIX(Simple_item_spot_count);
    def_structure_simple_item_spot_variable = 
	    Chain_of_available_simple_item_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_simple_item_spot_variable))
	goto end_loop;
    def_structure_simple_item_spot_variable = 
	    ISVREF(def_structure_simple_item_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SIMPLE-ITEM-SPOT-1 */
Object reclaim_simple_item_spot_1(simple_item_spot)
    Object simple_item_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(89,210);
    inline_note_reclaim_cons(simple_item_spot,Nil);
    structure_being_reclaimed = simple_item_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(simple_item_spot,(SI_Long)2L));
      SVREF(simple_item_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_simple_item_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(simple_item_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_simple_item_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = simple_item_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SIMPLE-ITEM-SPOT */
Object reclaim_structure_for_simple_item_spot(simple_item_spot)
    Object simple_item_spot;
{
    x_note_fn_call(89,211);
    return reclaim_simple_item_spot_1(simple_item_spot);
}

static Object Qg2_defstruct_structure_name_simple_item_spot_g2_struct;  /* g2-defstruct-structure-name::simple-item-spot-g2-struct */

/* MAKE-PERMANENT-SIMPLE-ITEM-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_simple_item_spot_structure_internal()
{
    Object def_structure_simple_item_spot_variable;
    Object defstruct_g2_simple_item_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(89,212);
    def_structure_simple_item_spot_variable = Nil;
    atomic_incff_symval(Qsimple_item_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_simple_item_spot_variable = Nil;
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
	defstruct_g2_simple_item_spot_variable = the_array;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_simple_item_spot_g2_struct;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_simple_item_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_simple_item_spot_variable = 
		defstruct_g2_simple_item_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_simple_item_spot_variable);
}

/* MAKE-SIMPLE-ITEM-SPOT-1 */
Object make_simple_item_spot_1()
{
    Object def_structure_simple_item_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(89,213);
    def_structure_simple_item_spot_variable = 
	    ISVREF(Chain_of_available_simple_item_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_simple_item_spot_variable) {
	svref_arg_1 = Chain_of_available_simple_item_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_simple_item_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_simple_item_spot_g2_struct;
    }
    else
	def_structure_simple_item_spot_variable = 
		make_permanent_simple_item_spot_structure_internal();
    inline_note_allocate_cons(def_structure_simple_item_spot_variable,Nil);
    SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_simple_item_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_simple_item_spot_variable);
}

/* GENERATE-SIMPLE-ITEM-SPOT */
Object generate_simple_item_spot(frame_represented,mouse_pointer)
    Object frame_represented, mouse_pointer;
{
    x_note_fn_call(89,214);
    push_last_spot(mouse_pointer,make_simple_item_spot_1(),frame_represented);
    return VALUES_1(Nil);
}

/* GENERATE-SPOT-FOR-AGGREGATE */
Object generate_spot_for_aggregate(aggregate_subblock,mouse_pointer)
    Object aggregate_subblock, mouse_pointer;
{
    Object gensymed_symbol, superior_block, super_super_block_qm;
    Object sub_class_bit_vector, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,215);
    gensymed_symbol = ACCESS_ONCE(ISVREF(aggregate_subblock,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superior_block = gensymed_symbol;
    super_super_block_qm = Nil;
  next_loop:
    gensymed_symbol = ACCESS_ONCE(ISVREF(superior_block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    super_super_block_qm = gensymed_symbol;
    temp =  !TRUEP(super_super_block_qm);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(super_super_block_qm,
		(SI_Long)1L),(SI_Long)19L);
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
    }
    if (temp)
	goto end_loop;
    superior_block = super_super_block_qm;
    goto next_loop;
  end_loop:
    sub_class_bit_vector = ISVREF(ISVREF(superior_block,(SI_Long)1L),
	    (SI_Long)19L);
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
    if (temp)
	push_last_spot(mouse_pointer,make_workspace_background_spot_1(),
		superior_block);
    else {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(superior_block,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)0L),(SI_Long)1L);
	gensymed_symbol_4 = superior_block;
	gensymed_symbol_5 = mouse_pointer;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_4,gensymed_symbol_5);
    }
    return VALUES_1(Qnil);
}

/* INVALIDATE-REGION-OF-WORKSPACE-FOR-BLOCK */
Object invalidate_region_of_workspace_for_block(workspace,block)
    Object workspace, block;
{
    Object purpose_of_extreme_edges, left, top, right, bottom;
    Declare_special(1);
    Object result;

    x_note_fn_call(89,216);
    purpose_of_extreme_edges = Qdraw_extent;
    PUSH_SPECIAL_WITH_SYMBOL(Purpose_of_extreme_edges,Qpurpose_of_extreme_edges,purpose_of_extreme_edges,
	    0);
      result = determine_extreme_edges_of_block(block);
    POP_SPECIAL();
    MVS_4(result,left,top,right,bottom);
    return invalidate_rectangle_of_workspace(workspace,workspace,left,top,
	    right,bottom,Nil);
}

/* GET-BLOCK-LAYER-POSITION */
Object get_block_layer_position(block)
    Object block;
{
    Object workspace_qm;

    x_note_fn_call(89,217);
    workspace_qm = get_workspace_if_any(block);
    if (workspace_qm) {
	ensure_layer_positions(workspace_qm);
	return get_lookup_slot_value_given_default(block,
		Qlayer_position_of_block,FIX((SI_Long)0L));
    }
    else
	return VALUES_1(Nil);
}

/* RAISE-BLOCK-TO-TOP */
Object raise_block_to_top(block)
    Object block;
{
    Object gensymed_symbol, superblock_qm, workspace_qm, constant_queue, head;
    Object queue_element, cursor;

    x_note_fn_call(89,218);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    workspace_qm = get_workspace_if_any(block);
    if (superblock_qm) {
	if (EQ(block,first_subblock(superblock_qm)))
	    return VALUES_1(Nil);
	else {
	    primitive_remove_as_subblock(block,superblock_qm);
	    primitive_insert_as_subblock(block,superblock_qm,Qtop);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock_qm,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    constant_queue = gensymed_symbol;
	    head = ISVREF(constant_queue,(SI_Long)2L);
	    queue_element = constant_queue_next(head,constant_queue);
	  next_loop:
	    if ( !TRUEP(queue_element))
		goto end_loop;
	    if (EQ(block,ISVREF(queue_element,(SI_Long)4L))) {
		cursor = queue_element;
		goto end_1;
	    }
	    queue_element = constant_queue_next(queue_element,constant_queue);
	    goto next_loop;
	  end_loop:
	    cursor = Qnil;
	  end_1:;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock_qm,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    send_ws_representations_item_layer_change(block,superblock_qm,
		    find_next_non_loose_end_in_queue(gensymed_symbol,cursor));
	    if (workspace_qm) {
		note_change_to_workspace_geometry(workspace_qm);
		invalidate_layer_positions(workspace_qm);
		return invalidate_region_of_workspace_for_block(workspace_qm,
			block);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* LOWER-BLOCK-TO-BOTTOM */
Object lower_block_to_bottom(block)
    Object block;
{
    Object sub_class_bit_vector, gensymed_symbol_3, superblock_qm;
    Object workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(89,219);
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
	return lower_connection_frame_to_bottom(block);
    else {
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	superblock_qm = gensymed_symbol_3;
	workspace_qm = get_workspace_if_any(block);
	if (superblock_qm) {
	    if (EQ(block,last_subblock(superblock_qm)))
		return VALUES_1(Nil);
	    else {
		primitive_remove_as_subblock(block,superblock_qm);
		primitive_insert_as_subblock(block,superblock_qm,Qbottom);
		send_ws_representations_item_layer_change(block,
			superblock_qm,Qbottom);
		sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		    note_change_to_workspace_geometry(workspace_qm);
		    invalidate_layer_positions(workspace_qm);
		    return invalidate_region_of_workspace_for_block(superblock_qm,
			    block);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

/* ORDER-BLOCKS */
Object order_blocks(block_1,block_2,in_back_p)
    Object block_1, block_2, in_back_p;
{
    Object gensymed_symbol, superblock_1, superblock_2, constant_queue;
    Object queue_element_1, queue_element_2, changed_something_qm, head;
    Object element, block, sub_class_bit_vector, item_below;
    Object position_or_next_lower_item;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(89,220);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block_1,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_1 = gensymed_symbol;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block_2,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_2 = gensymed_symbol;
    if (superblock_1 && superblock_2 && EQ(superblock_1,superblock_2)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(superblock_1,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	constant_queue = gensymed_symbol;
	queue_element_1 = Nil;
	queue_element_2 = Nil;
	changed_something_qm = Nil;
	head = ISVREF(constant_queue,(SI_Long)2L);
	element = constant_queue_next(head,constant_queue);
	block = Nil;
      next_loop:
	if ( !TRUEP(element))
	    goto end_loop;
	block = ISVREF(element,(SI_Long)4L);
	if (EQ(block,block_1)) {
	    queue_element_1 = element;
	    if ( !TRUEP(queue_element_2) && in_back_p)
		changed_something_qm = T;
	}
	else if (EQ(block,block_2)) {
	    queue_element_2 = element;
	    if ( !TRUEP(queue_element_1) &&  !TRUEP(in_back_p))
		changed_something_qm = T;
	}
	if (queue_element_1 && queue_element_2)
	    goto end_loop;
	element = constant_queue_next(element,constant_queue);
	goto next_loop;
      end_loop:;
	if (changed_something_qm) {
	    if (in_back_p) {
		constant_queue_delete(2,queue_element_2,constant_queue);
		constant_queue_insert_before(constant_queue,
			queue_element_1,block_2);
	    }
	    else {
		constant_queue_delete(2,queue_element_1,constant_queue);
		constant_queue_insert_before(constant_queue,
			queue_element_2,block_1);
	    }
	}
	if (changed_something_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(superblock_1,(SI_Long)1L),
		    (SI_Long)19L);
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (ws_has_ws_representation_p(superblock_1)) {
		if (in_back_p) {
		    item_below = 
			    find_next_non_loose_end_in_queue(constant_queue,
			    queue_element_1);
		    position_or_next_lower_item = item_below;
		    if (position_or_next_lower_item);
		    else
			position_or_next_lower_item = Qbottom;
		    send_ws_representations_item_layer_change(block_1,
			    superblock_1,position_or_next_lower_item);
		}
		else
		    send_ws_representations_item_layer_change(block_1,
			    superblock_1,get_topmost_child_of_block(block_2));
	    }
	    note_change_to_workspace_geometry(superblock_1);
	    invalidate_layer_positions(superblock_1);
	    invalidate_region_of_workspace_for_block(superblock_1,block_1);
	}
	return VALUES_1(changed_something_qm);
    }
    else
	return VALUES_1(Nil);
}

void draw_INIT()
{
    Object named_dynamic_extent_description, temp;
    Object reclaim_structure_for_workspace_background_spot_1, type_description;
    Object temp_1, reclaim_structure_for_title_bar_spot_1;
    Object reclaim_structure_for_frame_component_spot_1;
    Object reclaim_structure_for_elevator_shaft_spot_1;
    Object reclaim_structure_for_stepper_of_scroll_bar_spot_1;
    Object reclaim_structure_for_elevator_of_scroll_bar_spot_1;
    Object reclaim_structure_for_resize_box_spot_1;
    Object reclaim_structure_for_close_box_spot_1;
    Object frame_description_evaluation_setter_1;
    Object frame_description_evaluation_getter_1;
    Object reclaim_structure_for_uninteresting_block_spot_1;
    Object reclaim_structure_for_simple_item_spot_1;
    Object Qentity, Qtype_of_frame_represented, Qabstract_type;
    Object Qimage_plane_spot, Qenclosing_spot_type, Qinnermost_spot_p;
    Object Qtype_description_of_type, Qsimple_item_spot, AB_package;
    Object Qreclaim_structure, Qoutstanding_simple_item_spot_count;
    Object Qsimple_item_spot_structure_memory_usage, Qutilities2;
    Object string_constant_43;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_42, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qclasses_which_define;
    Object Qgenerate_spot, Qgenerate_spot_for_block;
    Object Qgeneric_method_lambda_list, list_constant_80, Qmouse_pointer;
    Object Quninteresting_block_spot;
    Object Qoutstanding_uninteresting_block_spot_count;
    Object Quninteresting_block_spot_structure_memory_usage;
    Object string_constant_41, string_constant_40;
    Object Qreconsider_formatting_for_block, list_constant_79;
    Object Qformatting_dimension, list_constant_78, list_constant_46;
    Object list_constant_77, list_constant_64, list_constant_76;
    Object list_constant_75, list_constant_72, list_constant_74;
    Object list_constant_73, list_constant_71, list_constant_57;
    Object list_constant_70, list_constant_69, list_constant_61;
    Object list_constant_68, list_constant_67, list_constant_66;
    Object list_constant_65, Qdark_gray, list_constant_63, list_constant_59;
    Object list_constant_62, list_constant_60, list_constant_58;
    Object list_constant_37, list_constant_56, list_constant_55;
    Object list_constant_47, list_constant_54, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_41;
    Object list_constant_50, Qlarge, list_constant_49, list_constant_48;
    Object list_constant_45, list_constant_44, list_constant_43;
    Object list_constant_42, list_constant_40, list_constant_39;
    Object list_constant_38;
    Object Qframe_description_reference_of_built_in_frame_style;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qrelease_frame_description_reference_if_any;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qframe_description, Qslot_value_compiler;
    Object Qcompile_frame_description_for_slot, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, list_constant_29, Qnamed;
    Object list_constant_36, Qab_or, list_constant_35, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object list_constant_30, Qtype_specification_simple_expansion, Qno_item;
    Object Qslot_value_writer, Qwrite_frame_description_from_slot, Qworkspace;
    Object Qclose_box_spot, Qoutstanding_close_box_spot_count;
    Object Qclose_box_spot_structure_memory_usage, string_constant_33;
    Object string_constant_32, Qresize_box_spot;
    Object Qoutstanding_resize_box_spot_count;
    Object Qresize_box_spot_structure_memory_usage, string_constant_31;
    Object string_constant_30, list_constant_28, Qelevator_of_scroll_bar_spot;
    Object Qoutstanding_elevator_of_scroll_bar_spot_count;
    Object Qelevator_of_scroll_bar_spot_structure_memory_usage;
    Object string_constant_29, string_constant_28, Qstepper_of_scroll_bar_spot;
    Object Qoutstanding_stepper_of_scroll_bar_spot_count;
    Object Qstepper_of_scroll_bar_spot_structure_memory_usage;
    Object string_constant_27, string_constant_26, Qelevator_shaft_spot;
    Object Qoutstanding_elevator_shaft_spot_count;
    Object Qelevator_shaft_spot_structure_memory_usage, string_constant_25;
    Object string_constant_24, Qframe_component_spot;
    Object Qoutstanding_frame_component_spot_count;
    Object Qframe_component_spot_structure_memory_usage, string_constant_23;
    Object string_constant_22, list_constant_27, list_constant_26;
    Object list_constant_21, list_constant_25, list_constant_24;
    Object list_constant_18, list_constant_23, list_constant_22;
    Object list_constant_20, list_constant_19, Qimage_plane_border_color;
    Object Qdraw, Qnamed_dynamic_extent_description, string_constant_21;
    Object Qscroll_block, Qscroll_block_for_workspace, Qscroll_block_for_block;
    Object list_constant_17, Qdirection_of_step, Qamount_of_step, Qimage_plane;
    Object list_constant_16, string_constant_20, Qtitle_bar_spot;
    Object Qoutstanding_title_bar_spot_count;
    Object Qtitle_bar_spot_structure_memory_usage, string_constant_19;
    Object string_constant_18, Qworkspace_background_spot;
    Object Qoutstanding_workspace_background_spot_count;
    Object Qworkspace_background_spot_structure_memory_usage;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object list_constant_15, string_constant_14;

    x_note_fn_call(89,221);
    SET_PACKAGE("AB");
    string_constant_14 = STATIC_STRING("WITH-EXTREME-EDGES");
    if (With_extreme_edges == UNBOUND)
	With_extreme_edges = make_recursive_lock(2,Kname,string_constant_14);
    AB_package = STATIC_PACKAGE("AB");
    Qwith_extreme_edges = STATIC_SYMBOL("WITH-EXTREME-EDGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwith_extreme_edges,With_extreme_edges);
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qwith_extreme_edges,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qwith_extreme_edges,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qdraw_extent = STATIC_SYMBOL("DRAW-EXTENT",AB_package);
    if (Purpose_of_extreme_edges == UNBOUND)
	Purpose_of_extreme_edges = Qdraw_extent;
    if (Do_not_update_selection_highlights == UNBOUND)
	Do_not_update_selection_highlights = Nil;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgraph_grid = STATIC_SYMBOL("GRAPH-GRID",AB_package);
    Qgraph_axis_label = STATIC_SYMBOL("GRAPH-AXIS-LABEL",AB_package);
    Qworkspace_spacial_index_qm = 
	    STATIC_SYMBOL("WORKSPACE-SPACIAL-INDEX\?",AB_package);
    Qblock_and_frame_extent = STATIC_SYMBOL("BLOCK-AND-FRAME-EXTENT",
	    AB_package);
    Qnumber_of_blocks_on_workspace = 
	    STATIC_SYMBOL("NUMBER-OF-BLOCKS-ON-WORKSPACE",AB_package);
    Qg2_add = STATIC_SYMBOL("ADD",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qsubblocks = STATIC_SYMBOL("SUBBLOCKS",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qlayer_position_of_block = STATIC_SYMBOL("LAYER-POSITION-OF-BLOCK",
	    AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qcount_of_pending_workspace_drawing = 
	    STATIC_SYMBOL("COUNT-OF-PENDING-WORKSPACE-DRAWING",AB_package);
    list_constant_15 = STATIC_CONS(Qblock,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qdraw,list_constant_15,Qgeneric_method_lambda_list);
    string_constant_15 = STATIC_STRING("FRAME-PROJECTING");
    if (Frame_projecting == UNBOUND)
	Frame_projecting = make_recursive_lock(2,Kname,string_constant_15);
    Qframe_projecting = STATIC_SYMBOL("FRAME-PROJECTING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_projecting,Frame_projecting);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qframe_projecting,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qframe_projecting,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qg2_defstruct_structure_name_workspace_background_spot_g2_struct = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qworkspace_background_spot = STATIC_SYMBOL("WORKSPACE-BACKGROUND-SPOT",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workspace_background_spot_g2_struct,
	    Qworkspace_background_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qworkspace_background_spot,
	    Qg2_defstruct_structure_name_workspace_background_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workspace_background_spot == UNBOUND)
	The_type_description_of_workspace_background_spot = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m831By1o831By83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_workspace_background_spot;
    The_type_description_of_workspace_background_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workspace_background_spot_g2_struct,
	    The_type_description_of_workspace_background_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qworkspace_background_spot,
	    The_type_description_of_workspace_background_spot,
	    Qtype_description_of_type);
    Qoutstanding_workspace_background_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSPACE-BACKGROUND-SPOT-COUNT",
	    AB_package);
    Qworkspace_background_spot_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q831By8s83-xPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workspace_background_spot_count);
    push_optimized_constant(Qworkspace_background_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_workspace_background_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSPACE-BACKGROUND-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workspace_background_spots,
	    Chain_of_available_workspace_background_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_workspace_background_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qworkspace_background_spot_count = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_background_spot_count,
	    Workspace_background_spot_count);
    record_system_variable(Qworkspace_background_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workspace_background_spots_vector == UNBOUND)
	Chain_of_available_workspace_background_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkspace_background_spot_structure_memory_usage,
	    STATIC_FUNCTION(workspace_background_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workspace_background_spot_count,
	    STATIC_FUNCTION(outstanding_workspace_background_spot_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_workspace_background_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workspace_background_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qworkspace_background_spot,
	    reclaim_structure_for_workspace_background_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qworkspace_background_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qworkspace),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_title_bar_spot_g2_struct = 
	    STATIC_SYMBOL("TITLE-BAR-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtitle_bar_spot = STATIC_SYMBOL("TITLE-BAR-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_title_bar_spot_g2_struct,
	    Qtitle_bar_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtitle_bar_spot,
	    Qg2_defstruct_structure_name_title_bar_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_title_bar_spot == UNBOUND)
	The_type_description_of_title_bar_spot = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83AFy1o83AFy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_title_bar_spot;
    The_type_description_of_title_bar_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_title_bar_spot_g2_struct,
	    The_type_description_of_title_bar_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtitle_bar_spot,
	    The_type_description_of_title_bar_spot,Qtype_description_of_type);
    Qoutstanding_title_bar_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-TITLE-BAR-SPOT-COUNT",AB_package);
    Qtitle_bar_spot_structure_memory_usage = 
	    STATIC_SYMBOL("TITLE-BAR-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_19 = STATIC_STRING("1q83AFy8s83-tNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_title_bar_spot_count);
    push_optimized_constant(Qtitle_bar_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_title_bar_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TITLE-BAR-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_title_bar_spots,
	    Chain_of_available_title_bar_spots);
    record_system_variable(Qchain_of_available_title_bar_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qtitle_bar_spot_count = STATIC_SYMBOL("TITLE-BAR-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtitle_bar_spot_count,Title_bar_spot_count);
    record_system_variable(Qtitle_bar_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_title_bar_spots_vector == UNBOUND)
	Chain_of_available_title_bar_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtitle_bar_spot_structure_memory_usage,
	    STATIC_FUNCTION(title_bar_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_title_bar_spot_count,
	    STATIC_FUNCTION(outstanding_title_bar_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_title_bar_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_title_bar_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qtitle_bar_spot,
	    reclaim_structure_for_title_bar_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtitle_bar_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qworkspace),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    string_constant_20 = STATIC_STRING("WORKING-ON-DRAWING-WORKSPACE");
    if (Working_on_drawing_workspace == UNBOUND)
	Working_on_drawing_workspace = make_recursive_lock(2,Kname,
		string_constant_20);
    Qworking_on_drawing_workspace = 
	    STATIC_SYMBOL("WORKING-ON-DRAWING-WORKSPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworking_on_drawing_workspace,
	    Working_on_drawing_workspace);
    Qfor_image_plane = STATIC_SYMBOL("FOR-IMAGE-PLANE",AB_package);
    list_constant_16 = STATIC_CONS(Qfor_image_plane,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qworking_on_drawing_workspace,
	    Qdraw,Nil,list_constant_16,Qnil,Qnil,Nil);
    mutate_global_property(Qworking_on_drawing_workspace,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qcurrently_working_on_drawing_workspace = 
	    STATIC_SYMBOL("CURRENTLY-WORKING-ON-DRAWING-WORKSPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrently_working_on_drawing_workspace,
	    Currently_working_on_drawing_workspace);
    record_system_variable(Qcurrently_working_on_drawing_workspace,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qdeferred_draw_block = STATIC_SYMBOL("DEFERRED-DRAW-BLOCK",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeferred_draw_block,
	    STATIC_FUNCTION(deferred_draw_block,NIL,FALSE,2,2));
    Qdrawing = STATIC_SYMBOL("DRAWING",AB_package);
    Qdraw_block_within_frame_1 = STATIC_SYMBOL("DRAW-BLOCK-WITHIN-FRAME-1",
	    AB_package);
    Qdraw_block_within_frame_2 = STATIC_SYMBOL("DRAW-BLOCK-WITHIN-FRAME-2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_block_within_frame_1,
	    STATIC_FUNCTION(draw_block_within_frame_1,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qdraw_block_within_frame_2,
	    STATIC_FUNCTION(draw_block_within_frame_2,NIL,FALSE,0,0));
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qdraw_block = STATIC_SYMBOL("DRAW-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_block,STATIC_FUNCTION(draw_block,NIL,FALSE,1,1));
    Qscroll_block = STATIC_SYMBOL("SCROLL-BLOCK",AB_package);
    Qimage_plane = STATIC_SYMBOL("IMAGE-PLANE",AB_package);
    Qamount_of_step = STATIC_SYMBOL("AMOUNT-OF-STEP",AB_package);
    Qdirection_of_step = STATIC_SYMBOL("DIRECTION-OF-STEP",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)4L,Qblock,Qimage_plane,
	    Qamount_of_step,Qdirection_of_step);
    mutate_global_property(Qscroll_block,list_constant_17,
	    Qgeneric_method_lambda_list);
    Qscroll_block_for_block = STATIC_SYMBOL("SCROLL-BLOCK-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qscroll_block_for_block,
	    STATIC_FUNCTION(scroll_block_for_block,NIL,FALSE,4,4));
    temp_1 = SYMBOL_FUNCTION(Qscroll_block_for_block);
    set_get(Qblock,Qscroll_block,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qscroll_block),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp);
    mutate_global_property(Qscroll_block,temp_1,Qclasses_which_define);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    Qup = STATIC_SYMBOL("UP",AB_package);
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qscroll_block_for_workspace = 
	    STATIC_SYMBOL("SCROLL-BLOCK-FOR-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qscroll_block_for_workspace,
	    STATIC_FUNCTION(scroll_block_for_workspace,NIL,FALSE,4,4));
    temp_1 = SYMBOL_FUNCTION(Qscroll_block_for_workspace);
    set_get(Qworkspace,Qscroll_block,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qscroll_block),
	    Qclasses_which_define);
    temp_1 = CONS(Qworkspace,temp);
    mutate_global_property(Qscroll_block,temp_1,Qclasses_which_define);
    Qscroll_entire_block_contents = 
	    STATIC_SYMBOL("SCROLL-ENTIRE-BLOCK-CONTENTS",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qscroll_entire_block_contents,
	    STATIC_FUNCTION(scroll_entire_block_contents,NIL,FALSE,3,3));
    string_constant_21 = STATIC_STRING("GRAPHIC-ELEMENT-PROJECTION");
    if (Graphic_element_projection == UNBOUND)
	Graphic_element_projection = make_recursive_lock(2,Kname,
		string_constant_21);
    Qgraphic_element_projection = 
	    STATIC_SYMBOL("GRAPHIC-ELEMENT-PROJECTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraphic_element_projection,
	    Graphic_element_projection);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qgraphic_element_projection,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qgraphic_element_projection,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qoperation_of_graphic_element = 
	    STATIC_SYMBOL("OPERATION-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoperation_of_graphic_element,
	    Operation_of_graphic_element);
    record_system_variable(Qoperation_of_graphic_element,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qleft_edge_in_window_of_graphic_element = 
	    STATIC_SYMBOL("LEFT-EDGE-IN-WINDOW-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleft_edge_in_window_of_graphic_element,
	    Left_edge_in_window_of_graphic_element);
    record_system_variable(Qleft_edge_in_window_of_graphic_element,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qtop_edge_in_window_of_graphic_element = 
	    STATIC_SYMBOL("TOP-EDGE-IN-WINDOW-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtop_edge_in_window_of_graphic_element,
	    Top_edge_in_window_of_graphic_element);
    record_system_variable(Qtop_edge_in_window_of_graphic_element,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qright_edge_in_window_of_graphic_element = 
	    STATIC_SYMBOL("RIGHT-EDGE-IN-WINDOW-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qright_edge_in_window_of_graphic_element,
	    Right_edge_in_window_of_graphic_element);
    record_system_variable(Qright_edge_in_window_of_graphic_element,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qbottom_edge_in_window_of_graphic_element = 
	    STATIC_SYMBOL("BOTTOM-EDGE-IN-WINDOW-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbottom_edge_in_window_of_graphic_element,
	    Bottom_edge_in_window_of_graphic_element);
    record_system_variable(Qbottom_edge_in_window_of_graphic_element,Qdraw,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qforeground_color_value_of_graphic_element = 
	    STATIC_SYMBOL("FOREGROUND-COLOR-VALUE-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeground_color_value_of_graphic_element,
	    Foreground_color_value_of_graphic_element);
    record_system_variable(Qforeground_color_value_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qforeground_color_difference_of_graphic_element = 
	    STATIC_SYMBOL("FOREGROUND-COLOR-DIFFERENCE-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeground_color_difference_of_graphic_element,
	    Foreground_color_difference_of_graphic_element);
    record_system_variable(Qforeground_color_difference_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qx_scale_of_graphic_element = 
	    STATIC_SYMBOL("X-SCALE-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qx_scale_of_graphic_element,
	    X_scale_of_graphic_element);
    record_system_variable(Qx_scale_of_graphic_element,Qdraw,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qy_scale_of_graphic_element = 
	    STATIC_SYMBOL("Y-SCALE-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qy_scale_of_graphic_element,
	    Y_scale_of_graphic_element);
    record_system_variable(Qy_scale_of_graphic_element,Qdraw,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qimage_data_of_graphic_element = 
	    STATIC_SYMBOL("IMAGE-DATA-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qimage_data_of_graphic_element,
	    Image_data_of_graphic_element);
    record_system_variable(Qimage_data_of_graphic_element,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qx_in_window_of_graphic_element = 
	    STATIC_SYMBOL("X-IN-WINDOW-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qx_in_window_of_graphic_element,
	    X_in_window_of_graphic_element);
    record_system_variable(Qx_in_window_of_graphic_element,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qy_in_window_of_graphic_element = 
	    STATIC_SYMBOL("Y-IN-WINDOW-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qy_in_window_of_graphic_element,
	    Y_in_window_of_graphic_element);
    record_system_variable(Qy_in_window_of_graphic_element,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qrotation_of_graphic_element = 
	    STATIC_SYMBOL("ROTATION-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrotation_of_graphic_element,
	    Rotation_of_graphic_element);
    record_system_variable(Qrotation_of_graphic_element,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qquality_of_graphic_element = 
	    STATIC_SYMBOL("QUALITY-OF-GRAPHIC-ELEMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qquality_of_graphic_element,
	    Quality_of_graphic_element);
    record_system_variable(Qquality_of_graphic_element,Qdraw,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qbackground_color_value_of_graphic_element = 
	    STATIC_SYMBOL("BACKGROUND-COLOR-VALUE-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackground_color_value_of_graphic_element,
	    Background_color_value_of_graphic_element);
    record_system_variable(Qbackground_color_value_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qgraph_or_icon_rendering_of_graphic_element = 
	    STATIC_SYMBOL("GRAPH-OR-ICON-RENDERING-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_or_icon_rendering_of_graphic_element,
	    Graph_or_icon_rendering_of_graphic_element);
    record_system_variable(Qgraph_or_icon_rendering_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qforeground_color_difference_or_differences_of_graphic_element = 
	    STATIC_SYMBOL("FOREGROUND-COLOR-DIFFERENCE-OR-DIFFERENCES-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforeground_color_difference_or_differences_of_graphic_element,
	    Foreground_color_difference_or_differences_of_graphic_element);
    record_system_variable(Qforeground_color_difference_or_differences_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcolor_values_of_graph_rasters_of_graphic_element = 
	    STATIC_SYMBOL("COLOR-VALUES-OF-GRAPH-RASTERS-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_values_of_graph_rasters_of_graphic_element,
	    Color_values_of_graph_rasters_of_graphic_element);
    record_system_variable(Qcolor_values_of_graph_rasters_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qleft_edge_of_line_of_text_in_window_of_graphic_element = 
	    STATIC_SYMBOL("LEFT-EDGE-OF-LINE-OF-TEXT-IN-WINDOW-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleft_edge_of_line_of_text_in_window_of_graphic_element,
	    Left_edge_of_line_of_text_in_window_of_graphic_element);
    record_system_variable(Qleft_edge_of_line_of_text_in_window_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qbaseline_in_window_for_line_of_text_of_graphic_element = 
	    STATIC_SYMBOL("BASELINE-IN-WINDOW-FOR-LINE-OF-TEXT-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbaseline_in_window_for_line_of_text_of_graphic_element,
	    Baseline_in_window_for_line_of_text_of_graphic_element);
    record_system_variable(Qbaseline_in_window_for_line_of_text_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qtext_line_for_line_of_text_of_graphic_element = 
	    STATIC_SYMBOL("TEXT-LINE-FOR-LINE-OF-TEXT-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_line_for_line_of_text_of_graphic_element,
	    Text_line_for_line_of_text_of_graphic_element);
    record_system_variable(Qtext_line_for_line_of_text_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qword_spacing_for_line_of_text_of_graphic_element = 
	    STATIC_SYMBOL("WORD-SPACING-FOR-LINE-OF-TEXT-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qword_spacing_for_line_of_text_of_graphic_element,
	    Word_spacing_for_line_of_text_of_graphic_element);
    record_system_variable(Qword_spacing_for_line_of_text_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qfont_map_for_line_of_text_of_graphic_element = 
	    STATIC_SYMBOL("FONT-MAP-FOR-LINE-OF-TEXT-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfont_map_for_line_of_text_of_graphic_element,
	    Font_map_for_line_of_text_of_graphic_element);
    record_system_variable(Qfont_map_for_line_of_text_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcolor_difference_for_line_of_text_of_graphic_element = 
	    STATIC_SYMBOL("COLOR-DIFFERENCE-FOR-LINE-OF-TEXT-OF-GRAPHIC-ELEMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_difference_for_line_of_text_of_graphic_element,
	    Color_difference_for_line_of_text_of_graphic_element);
    record_system_variable(Qcolor_difference_for_line_of_text_of_graphic_element,
	    Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qimage_left_offset_in_ws = STATIC_SYMBOL("IMAGE-LEFT-OFFSET-IN-WS",
	    AB_package);
    record_system_variable(Qimage_left_offset_in_ws,Qdraw,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qimage_top_offset_in_ws = STATIC_SYMBOL("IMAGE-TOP-OFFSET-IN-WS",
	    AB_package);
    record_system_variable(Qimage_top_offset_in_ws,Qdraw,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qentity_width_in_ws = STATIC_SYMBOL("ENTITY-WIDTH-IN-WS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentity_width_in_ws,Entity_width_in_ws);
    record_system_variable(Qentity_width_in_ws,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qentity_height_in_ws = STATIC_SYMBOL("ENTITY-HEIGHT-IN-WS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentity_height_in_ws,Entity_height_in_ws);
    record_system_variable(Qentity_height_in_ws,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpoly_vertices = STATIC_SYMBOL("POLY-VERTICES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpoly_vertices,Poly_vertices);
    record_system_variable(Qpoly_vertices,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpoly_line_width = STATIC_SYMBOL("POLY-LINE-WIDTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpoly_line_width,Poly_line_width);
    record_system_variable(Qpoly_line_width,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpoly_line_pattern = STATIC_SYMBOL("POLY-LINE-PATTERN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpoly_line_pattern,Poly_line_pattern);
    record_system_variable(Qpoly_line_pattern,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpoly_line_style = STATIC_SYMBOL("POLY-LINE-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpoly_line_style,Poly_line_style);
    record_system_variable(Qpoly_line_style,Qdraw,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpolygon_fill_color_difference = 
	    STATIC_SYMBOL("POLYGON-FILL-COLOR-DIFFERENCE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpolygon_fill_color_difference,
	    Polygon_fill_color_difference);
    record_system_variable(Qpolygon_fill_color_difference,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qpolygon_fill_pattern = STATIC_SYMBOL("POLYGON-FILL-PATTERN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpolygon_fill_pattern,Polygon_fill_pattern);
    record_system_variable(Qpolygon_fill_pattern,Qdraw,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qadd_line_of_text = STATIC_SYMBOL("ADD-LINE-OF-TEXT",AB_package);
    Qadd_icon_rendering = STATIC_SYMBOL("ADD-ICON-RENDERING",AB_package);
    Qadd_graph_rendering = STATIC_SYMBOL("ADD-GRAPH-RENDERING",AB_package);
    Qpaint_solid_rectangle = STATIC_SYMBOL("PAINT-SOLID-RECTANGLE",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    Qadd_upward_sloping_line = STATIC_SYMBOL("ADD-UPWARD-SLOPING-LINE",
	    AB_package);
    Qadd_downward_sloping_line = STATIC_SYMBOL("ADD-DOWNWARD-SLOPING-LINE",
	    AB_package);
    Qpaint_image = STATIC_SYMBOL("PAINT-IMAGE",AB_package);
    Qpaint_icon_background_image = 
	    STATIC_SYMBOL("PAINT-ICON-BACKGROUND-IMAGE",AB_package);
    Qadd_wide_polyline = STATIC_SYMBOL("ADD-WIDE-POLYLINE",AB_package);
    Qadd_polygon = STATIC_SYMBOL("ADD-POLYGON",AB_package);
    Qadd_ellipse = STATIC_SYMBOL("ADD-ELLIPSE",AB_package);
    Qeffectively_infinite_region = 
	    STATIC_SYMBOL("EFFECTIVELY-INFINITE-REGION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qeffectively_infinite_region,
	    Effectively_infinite_region);
    record_system_variable(Qeffectively_infinite_region,Qdraw,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcurrent_image_plane = STATIC_SYMBOL("CURRENT-IMAGE-PLANE",AB_package);
    SET_SYMBOL_FUNCTION(Qpaint_solid_rectangle,
	    STATIC_FUNCTION(paint_solid_rectangle,NIL,FALSE,5,5));
    if (Drawing_state_for_project_paper == UNBOUND)
	Drawing_state_for_project_paper = Nil;
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qdrawing_paper = STATIC_SYMBOL("DRAWING-PAPER",AB_package);
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Icp_window_max_buffered_drawing_in_bytes = FIX((SI_Long)10000L);
    Icp_window_max_buffered_drawing_in_seconds = FIX((SI_Long)3L);
    Qabove_inclusive = STATIC_SYMBOL("ABOVE-INCLUSIVE",AB_package);
    Qdrawing_contents = STATIC_SYMBOL("DRAWING-CONTENTS",AB_package);
    Qdrawing_close_box = STATIC_SYMBOL("DRAWING-CLOSE-BOX",AB_package);
    Qmouse_tracking = STATIC_SYMBOL("MOUSE-TRACKING",AB_package);
    Qcompute_content_region = STATIC_SYMBOL("COMPUTE-CONTENT-REGION",
	    AB_package);
    Qmove_elevator = STATIC_SYMBOL("MOVE-ELEVATOR",AB_package);
    Qsquare = STATIC_SYMBOL("SQUARE",AB_package);
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Qslice_size = STATIC_SYMBOL("SLICE-SIZE",AB_package);
    Qgraphics = STATIC_SYMBOL("GRAPHICS",AB_package);
    Qhorizontal = STATIC_SYMBOL("HORIZONTAL",AB_package);
    Qframe_section = STATIC_SYMBOL("FRAME-SECTION",AB_package);
    Qborder = STATIC_SYMBOL("BORDER",AB_package);
    Qpaper = STATIC_SYMBOL("PAPER",AB_package);
    Qscroll_bar = STATIC_SYMBOL("SCROLL-BAR",AB_package);
    Qtitle_bar = STATIC_SYMBOL("TITLE-BAR",AB_package);
    Qresize_box = STATIC_SYMBOL("RESIZE-BOX",AB_package);
    Qclose_box = STATIC_SYMBOL("CLOSE-BOX",AB_package);
    Qelevator_shaft = STATIC_SYMBOL("ELEVATOR-SHAFT",AB_package);
    Qup_arrow = STATIC_SYMBOL("UP-ARROW",AB_package);
    Qdown_arrow = STATIC_SYMBOL("DOWN-ARROW",AB_package);
    Qleft_arrow = STATIC_SYMBOL("LEFT-ARROW",AB_package);
    Qright_arrow = STATIC_SYMBOL("RIGHT-ARROW",AB_package);
    Qcreate_frame_description_reference_1 = 
	    STATIC_SYMBOL("CREATE-FRAME-DESCRIPTION-REFERENCE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_frame_description_reference_1,
	    STATIC_FUNCTION(create_frame_description_reference_1,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qmove_elevator,STATIC_FUNCTION(move_elevator,NIL,
	    FALSE,3,3));
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    Qposition_of_horizontal_elevator = 
	    STATIC_SYMBOL("POSITION-OF-HORIZONTAL-ELEVATOR",AB_package);
    Qposition_of_vertical_elevator = 
	    STATIC_SYMBOL("POSITION-OF-VERTICAL-ELEVATOR",AB_package);
    Qdim_gray = STATIC_SYMBOL("DIM-GRAY",AB_package);
    Qimage_plane_border_color = STATIC_SYMBOL("IMAGE-PLANE-BORDER-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qimage_plane_border_color,
	    STATIC_FUNCTION(image_plane_border_color,NIL,FALSE,3,3));
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qdrop_shadow = STATIC_SYMBOL("DROP-SHADOW",AB_package);
    Qimages = STATIC_SYMBOL("IMAGES",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)4L,Qslice_size,Qslice_size,
	    Qnil,Qslice_size);
    list_constant_19 = STATIC_CONS(Qright,list_constant_18);
    list_constant_20 = STATIC_CONS(Qup_arrow,Qnil);
    list_constant_21 = STATIC_CONS(Qelevator_shaft,Qnil);
    list_constant_22 = STATIC_CONS(Qdown_arrow,Qnil);
    list_constant_23 = STATIC_LIST((SI_Long)5L,Qframe_section,
	    list_constant_19,list_constant_20,list_constant_21,
	    list_constant_22);
    list_constant = STATIC_CONS(list_constant_23,Qnil);
    list_constant_24 = STATIC_CONS(Qbottom,list_constant_18);
    list_constant_25 = STATIC_CONS(Qleft_arrow,Qnil);
    list_constant_26 = STATIC_CONS(Qright_arrow,Qnil);
    list_constant_27 = STATIC_LIST((SI_Long)5L,Qframe_section,
	    list_constant_24,list_constant_25,list_constant_21,
	    list_constant_26);
    list_constant_1 = STATIC_CONS(list_constant_27,Qnil);
    Qg2_defstruct_structure_name_frame_component_spot_g2_struct = 
	    STATIC_SYMBOL("FRAME-COMPONENT-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qframe_component_spot = STATIC_SYMBOL("FRAME-COMPONENT-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_frame_component_spot_g2_struct,
	    Qframe_component_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qframe_component_spot,
	    Qg2_defstruct_structure_name_frame_component_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_frame_component_spot == UNBOUND)
	The_type_description_of_frame_component_spot = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m834=y1p834=y831By83Qy8n8k1l831By0000001l1m8x831Bykuk0k0");
    temp = The_type_description_of_frame_component_spot;
    The_type_description_of_frame_component_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    mutate_global_property(Qg2_defstruct_structure_name_frame_component_spot_g2_struct,
	    The_type_description_of_frame_component_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qframe_component_spot,
	    The_type_description_of_frame_component_spot,
	    Qtype_description_of_type);
    Qoutstanding_frame_component_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-FRAME-COMPONENT-SPOT-COUNT",AB_package);
    Qframe_component_spot_structure_memory_usage = 
	    STATIC_SYMBOL("FRAME-COMPONENT-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_23 = STATIC_STRING("1q834=y8s83-Uwy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_frame_component_spot_count);
    push_optimized_constant(Qframe_component_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_frame_component_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FRAME-COMPONENT-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_frame_component_spots,
	    Chain_of_available_frame_component_spots);
    record_system_variable(Qchain_of_available_frame_component_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qframe_component_spot_count = 
	    STATIC_SYMBOL("FRAME-COMPONENT-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_component_spot_count,
	    Frame_component_spot_count);
    record_system_variable(Qframe_component_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_frame_component_spots_vector == UNBOUND)
	Chain_of_available_frame_component_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qframe_component_spot_structure_memory_usage,
	    STATIC_FUNCTION(frame_component_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_frame_component_spot_count,
	    STATIC_FUNCTION(outstanding_frame_component_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_frame_component_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_frame_component_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qframe_component_spot,
	    reclaim_structure_for_frame_component_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qframe_component_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qt),LIST_2(Qtype_of_frame_represented,
	    Qblock),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct = 
	    STATIC_SYMBOL("ELEVATOR-SHAFT-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qelevator_shaft_spot = STATIC_SYMBOL("ELEVATOR-SHAFT-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct,
	    Qelevator_shaft_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qelevator_shaft_spot,
	    Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_elevator_shaft_spot == UNBOUND)
	The_type_description_of_elevator_shaft_spot = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83h*y1q83h*y834=y831By83Qy8n8k1l834=y0000001l1m8x834=ykvk0k0");
    temp = The_type_description_of_elevator_shaft_spot;
    The_type_description_of_elevator_shaft_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    mutate_global_property(Qg2_defstruct_structure_name_elevator_shaft_spot_g2_struct,
	    The_type_description_of_elevator_shaft_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qelevator_shaft_spot,
	    The_type_description_of_elevator_shaft_spot,
	    Qtype_description_of_type);
    Qoutstanding_elevator_shaft_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-ELEVATOR-SHAFT-SPOT-COUNT",AB_package);
    Qelevator_shaft_spot_structure_memory_usage = 
	    STATIC_SYMBOL("ELEVATOR-SHAFT-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_25 = STATIC_STRING("1q83h*y8s83-SVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_elevator_shaft_spot_count);
    push_optimized_constant(Qelevator_shaft_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_elevator_shaft_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ELEVATOR-SHAFT-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_elevator_shaft_spots,
	    Chain_of_available_elevator_shaft_spots);
    record_system_variable(Qchain_of_available_elevator_shaft_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qelevator_shaft_spot_count = STATIC_SYMBOL("ELEVATOR-SHAFT-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qelevator_shaft_spot_count,
	    Elevator_shaft_spot_count);
    record_system_variable(Qelevator_shaft_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_elevator_shaft_spots_vector == UNBOUND)
	Chain_of_available_elevator_shaft_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qelevator_shaft_spot_structure_memory_usage,
	    STATIC_FUNCTION(elevator_shaft_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_elevator_shaft_spot_count,
	    STATIC_FUNCTION(outstanding_elevator_shaft_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_elevator_shaft_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_elevator_shaft_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qelevator_shaft_spot,
	    reclaim_structure_for_elevator_shaft_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelevator_shaft_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qt),LIST_2(Qtype_of_frame_represented,
	    Qblock),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstepper_of_scroll_bar_spot = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct,
	    Qstepper_of_scroll_bar_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstepper_of_scroll_bar_spot,
	    Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_stepper_of_scroll_bar_spot == UNBOUND)
	The_type_description_of_stepper_of_scroll_bar_spot = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8m83FCy1q83FCy834=y831By83Qy8n8k1l834=y0000001l1m8x834=ykwk0k0");
    temp = The_type_description_of_stepper_of_scroll_bar_spot;
    The_type_description_of_stepper_of_scroll_bar_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_26));
    mutate_global_property(Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct,
	    The_type_description_of_stepper_of_scroll_bar_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstepper_of_scroll_bar_spot,
	    The_type_description_of_stepper_of_scroll_bar_spot,
	    Qtype_description_of_type);
    Qoutstanding_stepper_of_scroll_bar_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-STEPPER-OF-SCROLL-BAR-SPOT-COUNT",
	    AB_package);
    Qstepper_of_scroll_bar_spot_structure_memory_usage = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_27 = STATIC_STRING("1q83FCy8s83-r+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_stepper_of_scroll_bar_spot_count);
    push_optimized_constant(Qstepper_of_scroll_bar_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_27));
    Qchain_of_available_stepper_of_scroll_bar_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STEPPER-OF-SCROLL-BAR-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_stepper_of_scroll_bar_spots,
	    Chain_of_available_stepper_of_scroll_bar_spots);
    record_system_variable(Qchain_of_available_stepper_of_scroll_bar_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qstepper_of_scroll_bar_spot_count = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstepper_of_scroll_bar_spot_count,
	    Stepper_of_scroll_bar_spot_count);
    record_system_variable(Qstepper_of_scroll_bar_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_stepper_of_scroll_bar_spots_vector == UNBOUND)
	Chain_of_available_stepper_of_scroll_bar_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstepper_of_scroll_bar_spot_structure_memory_usage,
	    STATIC_FUNCTION(stepper_of_scroll_bar_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_stepper_of_scroll_bar_spot_count,
	    STATIC_FUNCTION(outstanding_stepper_of_scroll_bar_spot_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_stepper_of_scroll_bar_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_stepper_of_scroll_bar_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qstepper_of_scroll_bar_spot,
	    reclaim_structure_for_stepper_of_scroll_bar_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstepper_of_scroll_bar_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qblock),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct = 
	    STATIC_SYMBOL("ELEVATOR-OF-SCROLL-BAR-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qelevator_of_scroll_bar_spot = 
	    STATIC_SYMBOL("ELEVATOR-OF-SCROLL-BAR-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct,
	    Qelevator_of_scroll_bar_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qelevator_of_scroll_bar_spot,
	    Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_elevator_of_scroll_bar_spot == UNBOUND)
	The_type_description_of_elevator_of_scroll_bar_spot = Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8m83KPy1q83KPy834=y831By83Qy8n8k1l834=y0000001l1m8x834=ykvk0k0");
    temp = The_type_description_of_elevator_of_scroll_bar_spot;
    The_type_description_of_elevator_of_scroll_bar_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_28));
    mutate_global_property(Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct,
	    The_type_description_of_elevator_of_scroll_bar_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qelevator_of_scroll_bar_spot,
	    The_type_description_of_elevator_of_scroll_bar_spot,
	    Qtype_description_of_type);
    Qoutstanding_elevator_of_scroll_bar_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-ELEVATOR-OF-SCROLL-BAR-SPOT-COUNT",
	    AB_package);
    Qelevator_of_scroll_bar_spot_structure_memory_usage = 
	    STATIC_SYMBOL("ELEVATOR-OF-SCROLL-BAR-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_29 = STATIC_STRING("1q83KPy8s83-SUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_elevator_of_scroll_bar_spot_count);
    push_optimized_constant(Qelevator_of_scroll_bar_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_elevator_of_scroll_bar_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ELEVATOR-OF-SCROLL-BAR-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_elevator_of_scroll_bar_spots,
	    Chain_of_available_elevator_of_scroll_bar_spots);
    record_system_variable(Qchain_of_available_elevator_of_scroll_bar_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qelevator_of_scroll_bar_spot_count = 
	    STATIC_SYMBOL("ELEVATOR-OF-SCROLL-BAR-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qelevator_of_scroll_bar_spot_count,
	    Elevator_of_scroll_bar_spot_count);
    record_system_variable(Qelevator_of_scroll_bar_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_elevator_of_scroll_bar_spots_vector == UNBOUND)
	Chain_of_available_elevator_of_scroll_bar_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qelevator_of_scroll_bar_spot_structure_memory_usage,
	    STATIC_FUNCTION(elevator_of_scroll_bar_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_elevator_of_scroll_bar_spot_count,
	    STATIC_FUNCTION(outstanding_elevator_of_scroll_bar_spot_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_elevator_of_scroll_bar_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_elevator_of_scroll_bar_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qelevator_of_scroll_bar_spot,
	    reclaim_structure_for_elevator_of_scroll_bar_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelevator_of_scroll_bar_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qblock),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qgensym_left_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-LEFT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qgensym_right_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-RIGHT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qgensym_up_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-UP-SCROLL-ARROW-FRAME-COMPONENT",AB_package);
    Qgensym_down_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-DOWN-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qlight_grey = STATIC_SYMBOL("LIGHT-GREY",AB_package);
    Qgensym_scroll_bar_elevator_frame_component = 
	    STATIC_SYMBOL("GENSYM-SCROLL-BAR-ELEVATOR-FRAME-COMPONENT",
	    AB_package);
    Qpage = STATIC_SYMBOL("PAGE",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qname,Qab_class);
    Default_workspace_title_bar_text_spec = list_constant_28;
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qa_or_an_plus_class = STATIC_SYMBOL("A-OR-AN+CLASS",AB_package);
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Qtable_header = STATIC_SYMBOL("TABLE-HEADER",AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qtitle_bar_text = STATIC_SYMBOL("TITLE-BAR-TEXT",AB_package);
    Qdark_slate_blue = STATIC_SYMBOL("DARK-SLATE-BLUE",AB_package);
    Qgray = STATIC_SYMBOL("GRAY",AB_package);
    Qg2_defstruct_structure_name_resize_box_spot_g2_struct = 
	    STATIC_SYMBOL("RESIZE-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresize_box_spot = STATIC_SYMBOL("RESIZE-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resize_box_spot_g2_struct,
	    Qresize_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresize_box_spot,
	    Qg2_defstruct_structure_name_resize_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resize_box_spot == UNBOUND)
	The_type_description_of_resize_box_spot = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83mJy1p83mJy831By83Qy8n8k1l831By0000001l1m8x831Bykuk0k0");
    temp = The_type_description_of_resize_box_spot;
    The_type_description_of_resize_box_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_30));
    mutate_global_property(Qg2_defstruct_structure_name_resize_box_spot_g2_struct,
	    The_type_description_of_resize_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresize_box_spot,
	    The_type_description_of_resize_box_spot,Qtype_description_of_type);
    Qoutstanding_resize_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESIZE-BOX-SPOT-COUNT",AB_package);
    Qresize_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("RESIZE-BOX-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_31 = STATIC_STRING("1q83mJy8s83-mPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resize_box_spot_count);
    push_optimized_constant(Qresize_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_resize_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESIZE-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resize_box_spots,
	    Chain_of_available_resize_box_spots);
    record_system_variable(Qchain_of_available_resize_box_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresize_box_spot_count = STATIC_SYMBOL("RESIZE-BOX-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresize_box_spot_count,Resize_box_spot_count);
    record_system_variable(Qresize_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resize_box_spots_vector == UNBOUND)
	Chain_of_available_resize_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresize_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(resize_box_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resize_box_spot_count,
	    STATIC_FUNCTION(outstanding_resize_box_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_resize_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resize_box_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qresize_box_spot,
	    reclaim_structure_for_resize_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qresize_box_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qblock),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qgensym_resize_box_frame_component = 
	    STATIC_SYMBOL("GENSYM-RESIZE-BOX-FRAME-COMPONENT",AB_package);
    Qg2_defstruct_structure_name_close_box_spot_g2_struct = 
	    STATIC_SYMBOL("CLOSE-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qclose_box_spot = STATIC_SYMBOL("CLOSE-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_close_box_spot_g2_struct,
	    Qclose_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qclose_box_spot,
	    Qg2_defstruct_structure_name_close_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_close_box_spot == UNBOUND)
	The_type_description_of_close_box_spot = Nil;
    string_constant_32 = 
	    STATIC_STRING("43Dy8m836gy1o836gy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_close_box_spot;
    The_type_description_of_close_box_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_32));
    mutate_global_property(Qg2_defstruct_structure_name_close_box_spot_g2_struct,
	    The_type_description_of_close_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qclose_box_spot,
	    The_type_description_of_close_box_spot,Qtype_description_of_type);
    Qoutstanding_close_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLOSE-BOX-SPOT-COUNT",AB_package);
    Qclose_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("CLOSE-BOX-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_33 = STATIC_STRING("1q836gy8s83-Mmy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_close_box_spot_count);
    push_optimized_constant(Qclose_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_33));
    Qchain_of_available_close_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLOSE-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_close_box_spots,
	    Chain_of_available_close_box_spots);
    record_system_variable(Qchain_of_available_close_box_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qclose_box_spot_count = STATIC_SYMBOL("CLOSE-BOX-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclose_box_spot_count,Close_box_spot_count);
    record_system_variable(Qclose_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_close_box_spots_vector == UNBOUND)
	Chain_of_available_close_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclose_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(close_box_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_close_box_spot_count,
	    STATIC_FUNCTION(outstanding_close_box_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_close_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_close_box_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qclose_box_spot,
	    reclaim_structure_for_close_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclose_box_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qworkspace),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qframe_description = STATIC_SYMBOL("FRAME-DESCRIPTION",AB_package);
    Qwrite_frame_description_from_slot = 
	    STATIC_SYMBOL("WRITE-FRAME-DESCRIPTION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_frame_description_from_slot,
	    STATIC_FUNCTION(write_frame_description_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qframe_description,
	    SYMBOL_FUNCTION(Qwrite_frame_description_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_4 = STATIC_CONS(Qno_item,Qnil);
    list_constant_5 = STATIC_CONS(Qsequence,Qnil);
    list_constant_30 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_4,
	    list_constant_5);
    set_property_value_function(get_symbol_properties_function(Qframe_description),
	    Qtype_specification_simple_expansion,list_constant_30);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qcolor,Qsymbol);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qwidth,Qinteger);
    list_constant_33 = STATIC_LIST((SI_Long)2L,list_constant_31,
	    list_constant_32);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qand,Qcolor,Qwidth);
    list_constant_35 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_33,list_constant_34);
    list_constant_36 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_35,
	    FIX((SI_Long)1L));
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_4,
	    list_constant_36);
    define_type_specification_explicit_complex_type(Qframe_description,
	    list_constant_3);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qframe_description);
    string_constant = STATIC_STRING("Invalid color: ~a");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_1 = STATIC_STRING("~NT ");
    string_constant_2 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    frame_description_evaluation_setter_1 = 
	    STATIC_FUNCTION(frame_description_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qframe_description,
	    frame_description_evaluation_setter_1);
    frame_description_evaluation_getter_1 = 
	    STATIC_FUNCTION(frame_description_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qframe_description,
	    frame_description_evaluation_getter_1);
    string_constant_3 = STATIC_STRING(";~%");
    array_constant_1 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    string_constant_4 = STATIC_STRING(", ");
    string_constant_5 = STATIC_STRING(" ~D ~(~A~)");
    string_constant_6 = STATIC_STRING("~(~A~)");
    string_constant_7 = 
	    STATIC_STRING("along the ~(~A~) using ~D workspace units place: ");
    string_constant_8 = STATIC_STRING("~%    ");
    string_constant_9 = STATIC_STRING(",~%    ");
    string_constant_10 = STATIC_STRING("a ~(~A~)");
    string_constant_11 = STATIC_STRING(" of size ~D");
    string_constant_12 = STATIC_STRING(" of variable size");
    string_constant_34 = 
	    STATIC_STRING("1m1n83wsy83wqy1ll1n83wsy1n83wqy1m9k83-Zy83wsy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_34));
    string_constant_35 = STATIC_STRING("1l1m83wqy83qhy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_35));
    string_constant_36 = STATIC_STRING("1l1n83qhy1m1m9k83-Kvy83qgy2llm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_36));
    string_constant_37 = 
	    STATIC_STRING("1m1n83qgy83qfy1ll1n83qgy1n83qfy1m9k83vy83qgy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_37));
    string_constant_38 = STATIC_STRING("1l1n83qfy1m83-ey83*xy1n83hSyml");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_38));
    string_constant_39 = STATIC_STRING("1m1n838Qy1m9k83Zy01m838Qy83wsy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_39));
    string_constant_13 = 
	    STATIC_STRING("The frame description width ~a must be a non-negative integer.");
    Qcompile_frame_description_for_slot = 
	    STATIC_SYMBOL("COMPILE-FRAME-DESCRIPTION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_frame_description_for_slot,
	    STATIC_FUNCTION(compile_frame_description_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qframe_description,
	    SYMBOL_FUNCTION(Qcompile_frame_description_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qframe_description,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qframe_description_reference_of_built_in_frame_style = 
	    STATIC_SYMBOL("FRAME-DESCRIPTION-REFERENCE-OF-BUILT-IN-FRAME-STYLE",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qframe_description_reference_of_built_in_frame_style,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qframe_description_reference_of_built_in_frame_style,
	    T,Qdo_not_carry_global_property_value_into_kbs_qm);
    Qrelease_frame_description_reference_if_any = 
	    STATIC_SYMBOL("RELEASE-FRAME-DESCRIPTION-REFERENCE-IF-ANY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrelease_frame_description_reference_if_any,
	    STATIC_FUNCTION(release_frame_description_reference_if_any,NIL,
	    FALSE,1,1));
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qframe_description_reference_of_built_in_frame_style,
	    Qrelease_frame_description_reference_if_any,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Frame_description_reference_of_built_in_frame_style_kbprop = 
	    Qframe_description_reference_of_built_in_frame_style;
    list_constant_46 = STATIC_CONS(Qpaper,Qnil);
    list_constant_37 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)3L,Qframe,
	    Qdark_slate_blue,list_constant_37);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_38);
    list_constant_39 = STATIC_CONS(FIX((SI_Long)24L),Qnil);
    list_constant_43 = STATIC_CONS(Qtop,list_constant_39);
    list_constant_40 = STATIC_CONS(Qsmall,Qnil);
    list_constant_44 = STATIC_CONS(Qtitle_bar,list_constant_40);
    list_constant_41 = STATIC_CONS(Qright,list_constant_39);
    list_constant_42 = STATIC_CONS(Qclose_box,list_constant_40);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qframe_section,
	    list_constant_41,list_constant_42);
    list_constant_48 = STATIC_LIST((SI_Long)4L,Qframe_section,
	    list_constant_43,list_constant_44,list_constant_45);
    list_constant_49 = STATIC_LIST((SI_Long)3L,list_constant_46,
	    list_constant_47,list_constant_48);
    Workspace_title_bar_frame_style_small = list_constant_49;
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qtop,FIX((SI_Long)28L));
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    list_constant_50 = STATIC_CONS(Qlarge,Qnil);
    list_constant_53 = STATIC_CONS(Qtitle_bar,list_constant_50);
    list_constant_51 = STATIC_CONS(Qclose_box,list_constant_50);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qframe_section,
	    list_constant_41,list_constant_51);
    list_constant_55 = STATIC_LIST((SI_Long)4L,Qframe_section,
	    list_constant_52,list_constant_53,list_constant_54);
    list_constant_56 = STATIC_LIST((SI_Long)3L,list_constant_46,
	    list_constant_47,list_constant_55);
    Workspace_title_bar_frame_style_large = list_constant_56;
    Qdialog_workspace_frame_style = 
	    STATIC_SYMBOL("DIALOG-WORKSPACE-FRAME-STYLE",AB_package);
    Qmenu_workspace_frame_style = 
	    STATIC_SYMBOL("MENU-WORKSPACE-FRAME-STYLE",AB_package);
    Qworkspace_title_bar_frame_style_small = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE-SMALL",AB_package);
    Qworkspace_title_bar_frame_style_large = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE-LARGE",AB_package);
    Qwalking_menu_frame_style = STATIC_SYMBOL("WALKING-MENU-FRAME-STYLE",
	    AB_package);
    Kcredits_workspace_frame_style = 
	    STATIC_SYMBOL("CREDITS-WORKSPACE-FRAME-STYLE",Pkeyword);
    Knew_credits_workspace_frame_style = 
	    STATIC_SYMBOL("NEW-CREDITS-WORKSPACE-FRAME-STYLE",Pkeyword);
    Kitem_frame_used_when_frame_style_is_incomplete = 
	    STATIC_SYMBOL("ITEM-FRAME-USED-WHEN-FRAME-STYLE-IS-INCOMPLETE",
	    Pkeyword);
    Kedit_box_frame_style = STATIC_SYMBOL("EDIT-BOX-FRAME-STYLE",Pkeyword);
    Kedit_box_with_scroll_bar_frame_style = 
	    STATIC_SYMBOL("EDIT-BOX-WITH-SCROLL-BAR-FRAME-STYLE",Pkeyword);
    Qthick_workspace_frame_style = 
	    STATIC_SYMBOL("THICK-WORKSPACE-FRAME-STYLE",AB_package);
    Qextremely_thin_workspace_frame_style = 
	    STATIC_SYMBOL("EXTREMELY-THIN-WORKSPACE-FRAME-STYLE",AB_package);
    Qdefault_workspace_frame_style = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-FRAME-STYLE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)13L,
	    Qdialog_workspace_frame_style,Qmenu_workspace_frame_style,
	    Qworkspace_title_bar_frame_style_small,
	    Qworkspace_title_bar_frame_style_large,
	    Qwalking_menu_frame_style,Kcredits_workspace_frame_style,
	    Knew_credits_workspace_frame_style,
	    Kitem_frame_used_when_frame_style_is_incomplete,
	    Kedit_box_frame_style,Kedit_box_with_scroll_bar_frame_style,
	    Qthick_workspace_frame_style,
	    Qextremely_thin_workspace_frame_style,
	    Qdefault_workspace_frame_style);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qblack,
	    list_constant_37);
    list_constant_57 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_60 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qwhite,
	    list_constant_57);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qblack,
	    list_constant_57);
    list_constant_61 = STATIC_CONS(list_constant_58,Qnil);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)4L,Qborder,
	    list_constant_59,list_constant_60,list_constant_61);
    list_constant_7 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_62);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_59);
    list_constant_8 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_63);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    list_constant_64 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_65 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qdark_gray,
	    list_constant_64);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_65);
    list_constant_9 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_66);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qdim_gray,
	    list_constant_64);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_67);
    list_constant_10 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_68);
    list_constant_72 = STATIC_CONS(Qborder,list_constant_61);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qright,FIX((SI_Long)21L),Qnil);
    list_constant_70 = STATIC_CONS(Qscroll_bar,Qnil);
    list_constant_73 = STATIC_LIST((SI_Long)3L,Qframe_section,
	    list_constant_69,list_constant_70);
    list_constant_71 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qtransparent,
	    list_constant_57);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_71);
    list_constant_11 = STATIC_LIST((SI_Long)4L,list_constant_46,
	    list_constant_72,list_constant_73,list_constant_74);
    list_constant_12 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_72);
    list_constant_75 = STATIC_LIST((SI_Long)3L,Qframe,Qblack,FIX((SI_Long)5L));
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_75);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_76);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)3L,Qframe,Qblack,
	    list_constant_64);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qborder,list_constant_77);
    list_constant_14 = STATIC_LIST((SI_Long)2L,list_constant_46,
	    list_constant_78);
    Qframe_style = STATIC_SYMBOL("FRAME-STYLE",AB_package);
    Qmenu_workspace_for_is_for_walking_submenu_p = 
	    STATIC_SYMBOL("MENU-WORKSPACE-FOR-IS-FOR-WALKING-SUBMENU-P",
	    AB_package);
    Qworkspace_title_bar_frame_style = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE",AB_package);
    Qframe_style_of_edit_box = STATIC_SYMBOL("FRAME-STYLE-OF-EDIT-BOX",
	    AB_package);
    Qedit_box = STATIC_SYMBOL("EDIT-BOX",AB_package);
    Qreconsider_formatting = STATIC_SYMBOL("RECONSIDER-FORMATTING",AB_package);
    Qframe_description_reference = 
	    STATIC_SYMBOL("FRAME-DESCRIPTION-REFERENCE",AB_package);
    Qformatting_dimension = STATIC_SYMBOL("FORMATTING-DIMENSION",AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qblock,Qformatting_dimension);
    mutate_global_property(Qreconsider_formatting,list_constant_79,
	    Qgeneric_method_lambda_list);
    Qformatting_configuration_changed = 
	    STATIC_SYMBOL("FORMATTING-CONFIGURATION-CHANGED",AB_package);
    Qimage_plane_frame_lookup_eq = 
	    STATIC_SYMBOL("IMAGE-PLANE-FRAME-LOOKUP-EQ",AB_package);
    Qreconsider_formatting_for_block = 
	    STATIC_SYMBOL("RECONSIDER-FORMATTING-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qreconsider_formatting_for_block,
	    STATIC_FUNCTION(reconsider_formatting_for_block,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qreconsider_formatting_for_block);
    set_get(Qblock,Qreconsider_formatting,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qreconsider_formatting),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp);
    mutate_global_property(Qreconsider_formatting,temp_1,
	    Qclasses_which_define);
    SET_SYMBOL_FUNCTION(Qimage_plane_frame_lookup_eq,
	    STATIC_FUNCTION(image_plane_frame_lookup_eq,NIL,FALSE,2,2));
    Qrebind_frame_description_reference_image_plane = 
	    STATIC_SYMBOL("REBIND-FRAME-DESCRIPTION-REFERENCE-IMAGE-PLANE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrebind_frame_description_reference_image_plane,
	    STATIC_FUNCTION(rebind_frame_description_reference_image_plane,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qreconsider_formatting,
	    STATIC_FUNCTION(reconsider_formatting,NIL,FALSE,1,1));
    Qworkspace_frame = STATIC_SYMBOL("WORKSPACE-FRAME",AB_package);
    Qinflate = STATIC_SYMBOL("INFLATE",AB_package);
    Default_required_visible_area_size_for_image_planes = FIX((SI_Long)11L);
    Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct = 
	    STATIC_SYMBOL("UNINTERESTING-BLOCK-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Quninteresting_block_spot = STATIC_SYMBOL("UNINTERESTING-BLOCK-SPOT",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct,
	    Quninteresting_block_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Quninteresting_block_spot,
	    Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_uninteresting_block_spot == UNBOUND)
	The_type_description_of_uninteresting_block_spot = Nil;
    string_constant_40 = 
	    STATIC_STRING("43Dy8m83oBy1o83oBy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_uninteresting_block_spot;
    The_type_description_of_uninteresting_block_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_40));
    mutate_global_property(Qg2_defstruct_structure_name_uninteresting_block_spot_g2_struct,
	    The_type_description_of_uninteresting_block_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Quninteresting_block_spot,
	    The_type_description_of_uninteresting_block_spot,
	    Qtype_description_of_type);
    Qoutstanding_uninteresting_block_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-UNINTERESTING-BLOCK-SPOT-COUNT",
	    AB_package);
    Quninteresting_block_spot_structure_memory_usage = 
	    STATIC_SYMBOL("UNINTERESTING-BLOCK-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_41 = STATIC_STRING("1q83oBy8s83-v-y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_uninteresting_block_spot_count);
    push_optimized_constant(Quninteresting_block_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_41));
    Qchain_of_available_uninteresting_block_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNINTERESTING-BLOCK-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_uninteresting_block_spots,
	    Chain_of_available_uninteresting_block_spots);
    record_system_variable(Qchain_of_available_uninteresting_block_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Quninteresting_block_spot_count = 
	    STATIC_SYMBOL("UNINTERESTING-BLOCK-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quninteresting_block_spot_count,
	    Uninteresting_block_spot_count);
    record_system_variable(Quninteresting_block_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_uninteresting_block_spots_vector == UNBOUND)
	Chain_of_available_uninteresting_block_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Quninteresting_block_spot_structure_memory_usage,
	    STATIC_FUNCTION(uninteresting_block_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_uninteresting_block_spot_count,
	    STATIC_FUNCTION(outstanding_uninteresting_block_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_uninteresting_block_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_uninteresting_block_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Quninteresting_block_spot,
	    reclaim_structure_for_uninteresting_block_spot_1);
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    Qmouse_pointer = STATIC_SYMBOL("MOUSE-POINTER",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qblock,Qmouse_pointer);
    mutate_global_property(Qgenerate_spot,list_constant_80,
	    Qgeneric_method_lambda_list);
    Qgenerate_spot_for_block = STATIC_SYMBOL("GENERATE-SPOT-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_block,
	    STATIC_FUNCTION(generate_spot_for_block,NIL,FALSE,2,2));
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_block);
    set_get(Qblock,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qg2_defstruct_structure_name_simple_item_spot_g2_struct = 
	    STATIC_SYMBOL("SIMPLE-ITEM-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimple_item_spot = STATIC_SYMBOL("SIMPLE-ITEM-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_simple_item_spot_g2_struct,
	    Qsimple_item_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsimple_item_spot,
	    Qg2_defstruct_structure_name_simple_item_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_simple_item_spot == UNBOUND)
	The_type_description_of_simple_item_spot = Nil;
    string_constant_42 = 
	    STATIC_STRING("43Dy8m83F=y1o83F=y83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_simple_item_spot;
    The_type_description_of_simple_item_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_42));
    mutate_global_property(Qg2_defstruct_structure_name_simple_item_spot_g2_struct,
	    The_type_description_of_simple_item_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsimple_item_spot,
	    The_type_description_of_simple_item_spot,
	    Qtype_description_of_type);
    Qoutstanding_simple_item_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-SIMPLE-ITEM-SPOT-COUNT",AB_package);
    Qsimple_item_spot_structure_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-ITEM-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_43 = STATIC_STRING("1q83F=y8s83-pRy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simple_item_spot_count);
    push_optimized_constant(Qsimple_item_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_43));
    Qchain_of_available_simple_item_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SIMPLE-ITEM-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_simple_item_spots,
	    Chain_of_available_simple_item_spots);
    record_system_variable(Qchain_of_available_simple_item_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsimple_item_spot_count = STATIC_SYMBOL("SIMPLE-ITEM-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_item_spot_count,Simple_item_spot_count);
    record_system_variable(Qsimple_item_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_simple_item_spots_vector == UNBOUND)
	Chain_of_available_simple_item_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsimple_item_spot_structure_memory_usage,
	    STATIC_FUNCTION(simple_item_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_simple_item_spot_count,
	    STATIC_FUNCTION(outstanding_simple_item_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_simple_item_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_simple_item_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsimple_item_spot,
	    reclaim_structure_for_simple_item_spot_1);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsimple_item_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qentity),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
}
