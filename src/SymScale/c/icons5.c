/* icons5.c
 * Input file:  icons5.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons5.h"


static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qicon_description;   /* icon-description */

/* GET-INHERITED-DRAWING-DESCRIPTION */
Object get_inherited_drawing_description(class_definition)
    Object class_definition;
{
    Object class_inheritance_path_qm, superior, ab_loop_list_;
    Object superior_class_description, superior_icon_description_qm, temp;
    Object temp_1;

    x_note_fn_call(236,0);
    class_inheritance_path_qm = 
	    get_lookup_slot_value_given_default(class_definition,
	    Qclass_inheritance_path_of_definition,Nil);
    if (class_inheritance_path_qm) {
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path_qm);
	superior_class_description = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	superior_class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop) && 
		(memq_function(Qicon_description,
		ISVREF(lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop),(SI_Long)7L)) || 
		memq_function(Qicon_description,
		ISVREF(lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop),(SI_Long)8L)))) {
	    superior_icon_description_qm = 
		    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
		    superior_class_description,Nil),(SI_Long)6L);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	superior_icon_description_qm = Qnil;
      end_1:;
    }
    else
	superior_icon_description_qm = Nil;
    if (superior_icon_description_qm) {
	temp = ISVREF(superior_icon_description_qm,(SI_Long)1L);
	temp_1 = ISVREF(superior_icon_description_qm,(SI_Long)2L);
	return icon_editor_cons_1(temp,icon_editor_cons_1(temp_1,
		copy_tree_including_leaves_using_icon_editor_conses(ISVREF(superior_icon_description_qm,
		(SI_Long)8L))));
    }
    else
	return VALUES_1(Nil);
}

static Object Qicon_background_images;  /* icon-background-images */

/* GET-INHERITED-BACKGROUND-IMAGE */
Object get_inherited_background_image(class_definition)
    Object class_definition;
{
    Object class_inheritance_path_qm, superior, ab_loop_list_;
    Object class_description_qm, superior_background_image_qm;

    x_note_fn_call(236,1);
    class_inheritance_path_qm = 
	    get_lookup_slot_value_given_default(class_definition,
	    Qclass_inheritance_path_of_definition,Nil);
    if (class_inheritance_path_qm) {
	superior = Nil;
	ab_loop_list_ = CDR(class_inheritance_path_qm);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L)) ? 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop) && 
		(memq_function(Qicon_background_images,
		ISVREF(lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop),(SI_Long)7L)) || 
		memq_function(Qicon_background_images,
		ISVREF(lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop),(SI_Long)8L))) : TRUEP(Nil)) {
	    superior_background_image_qm = 
		    get_lookup_slot_value_given_default(lookup_global_or_kb_specific_property_value(superior,
		    Class_definition_gkbprop),Qicon_background_images,Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	superior_background_image_qm = Qnil;
      end_1:;
    }
    else
	superior_background_image_qm = Nil;
    if (superior_background_image_qm)
	return copy_tree_including_leaves_using_icon_editor_conses(superior_background_image_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_bounding_box_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_bounding_box_states, Qchain_of_available_bounding_box_states);

DEFINE_VARIABLE_WITH_SYMBOL(Bounding_box_state_count, Qbounding_box_state_count);

Object Chain_of_available_bounding_box_states_vector = UNBOUND;

/* BOUNDING-BOX-STATE-STRUCTURE-MEMORY-USAGE */
Object bounding_box_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(236,2);
    temp = Bounding_box_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BOUNDING-BOX-STATE-COUNT */
Object outstanding_bounding_box_state_count()
{
    Object def_structure_bounding_box_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(236,3);
    gensymed_symbol = IFIX(Bounding_box_state_count);
    def_structure_bounding_box_state_variable = 
	    Chain_of_available_bounding_box_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_bounding_box_state_variable))
	goto end_loop;
    def_structure_bounding_box_state_variable = 
	    ISVREF(def_structure_bounding_box_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BOUNDING-BOX-STATE-1 */
Object reclaim_bounding_box_state_1(bounding_box_state)
    Object bounding_box_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(236,4);
    inline_note_reclaim_cons(bounding_box_state,Nil);
    structure_being_reclaimed = bounding_box_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(bounding_box_state,(SI_Long)1L));
      SVREF(bounding_box_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(bounding_box_state,(SI_Long)2L));
      SVREF(bounding_box_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_bounding_box_states_vector,
	    IFIX(Current_thread_index));
    SVREF(bounding_box_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_bounding_box_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = bounding_box_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BOUNDING-BOX-STATE */
Object reclaim_structure_for_bounding_box_state(bounding_box_state)
    Object bounding_box_state;
{
    x_note_fn_call(236,5);
    return reclaim_bounding_box_state_1(bounding_box_state);
}

static Object Qg2_defstruct_structure_name_bounding_box_state_g2_struct;  /* g2-defstruct-structure-name::bounding-box-state-g2-struct */

/* MAKE-PERMANENT-BOUNDING-BOX-STATE-STRUCTURE-INTERNAL */
Object make_permanent_bounding_box_state_structure_internal()
{
    Object def_structure_bounding_box_state_variable;
    Object defstruct_g2_bounding_box_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(236,6);
    def_structure_bounding_box_state_variable = Nil;
    atomic_incff_symval(Qbounding_box_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_bounding_box_state_variable = Nil;
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
	defstruct_g2_bounding_box_state_variable = the_array;
	SVREF(defstruct_g2_bounding_box_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bounding_box_state_g2_struct;
	SVREF(defstruct_g2_bounding_box_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_bounding_box_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_bounding_box_state_variable = 
		defstruct_g2_bounding_box_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_bounding_box_state_variable);
}

/* MAKE-BOUNDING-BOX-STATE-1 */
Object make_bounding_box_state_1(bounding_box_state_bounding_box,
	    bounding_box_state_image_plane,bounding_box_state_x_in_window,
	    bounding_box_state_y_in_window,
	    bounding_box_state_edge_or_corner_qm,
	    bounding_box_state_x_offset_of_mouse_from_edge,
	    bounding_box_state_y_offset_of_mouse_from_edge,
	    bounding_box_state_update_function_qm,
	    bounding_box_state_update_information_qm,
	    bounding_box_state_update_information_reclaimer_qm)
    Object bounding_box_state_bounding_box, bounding_box_state_image_plane;
    Object bounding_box_state_x_in_window, bounding_box_state_y_in_window;
    Object bounding_box_state_edge_or_corner_qm;
    Object bounding_box_state_x_offset_of_mouse_from_edge;
    Object bounding_box_state_y_offset_of_mouse_from_edge;
    Object bounding_box_state_update_function_qm;
    Object bounding_box_state_update_information_qm;
    Object bounding_box_state_update_information_reclaimer_qm;
{
    Object def_structure_bounding_box_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(236,7);
    def_structure_bounding_box_state_variable = 
	    ISVREF(Chain_of_available_bounding_box_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_bounding_box_state_variable) {
	temp = Chain_of_available_bounding_box_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_bounding_box_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_bounding_box_state_g2_struct;
    }
    else
	def_structure_bounding_box_state_variable = 
		make_permanent_bounding_box_state_structure_internal();
    inline_note_allocate_cons(def_structure_bounding_box_state_variable,Nil);
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)3L)) = 
	    bounding_box_state_bounding_box;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)4L)) = 
	    bounding_box_state_image_plane;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)5L)) = 
	    bounding_box_state_x_in_window;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)6L)) = 
	    bounding_box_state_y_in_window;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)7L)) = 
	    bounding_box_state_edge_or_corner_qm;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)8L)) = 
	    bounding_box_state_x_offset_of_mouse_from_edge;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)9L)) = 
	    bounding_box_state_y_offset_of_mouse_from_edge;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)10L)) = 
	    bounding_box_state_update_function_qm;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)11L)) = 
	    bounding_box_state_update_information_qm;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)12L)) = 
	    bounding_box_state_update_information_reclaimer_qm;
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_bounding_box_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_bounding_box_state_variable);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* VALID-WORKSTATION-CONTEXT-P-FOR-BOUNDING-BOX-STATE */
Object valid_workstation_context_p_for_bounding_box_state(bounding_box_state)
    Object bounding_box_state;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(236,8);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_bounding_box_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = bounding_box_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(ISVREF(bounding_box_state,(SI_Long)3L),
		(SI_Long)3L);
	x = ISVREF(bounding_box_state,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(bounding_box_state,(SI_Long)2L);
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

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-BOUNDING-BOX-STATE */
Object clean_up_workstation_context_for_bounding_box_state(bounding_box_state)
    Object bounding_box_state;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(236,9);
    if (ISVREF(bounding_box_state,(SI_Long)12L))
	reclaim_slot_value_list_1(ISVREF(bounding_box_state,(SI_Long)11L));
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_bounding_box_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = bounding_box_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qbounding_box;       /* bounding-box */

/* ANY-MOUSE-UP-OR-DOWN-IN-BOUNDING-BOX-STATE */
Object any_mouse_up_or_down_in_bounding_box_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1;

    x_note_fn_call(236,10);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (mouse_pointer_1) {
	mouse_motion_in_bounding_box_state(mouse_pointer_1);
	return return_from_current_workstation_context(1,Qbounding_box);
    }
    else
	return VALUES_1(Nil);
}

static Object Qright;              /* right */

static Object Qbottom_right;       /* bottom-right */

static Object Qbottom;             /* bottom */

static Object Qleft;               /* left */

static Object Qleft_right;         /* left-right */

static Object Qtop;                /* top */

static Object Qtop_right;          /* top-right */

/* MOUSE-MOTION-IN-BOUNDING-BOX-STATE */
Object mouse_motion_in_bounding_box_state(mouse_pointer)
    Object mouse_pointer;
{
    Object x_in_window, y_in_window, bounding_box_state, bounding_box;
    Object bounding_box_border_width, bounding_box_state_edge_or_corner_qm;
    Object image_plane_of_bounding_box, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, scale;
    Object value, x_in_workspace_of_bounding_box, temp;
    Object y_in_workspace_of_bounding_box, offset_x_in_workspace;
    Object offset_y_in_workspace, gensymed_symbol, new_right_edge_qm;
    Object new_bottom_edge_qm, new_left_edge_qm, new_top_edge_qm;
    Object bounding_box_state_update_function_qm;
    SI_Long twice_bounding_box_border_width, temp_1, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, old_right_edge, old_bottom_edge, old_left_edge;
    SI_Long old_top_edge;
    Declare_special(5);
    Object result;

    x_note_fn_call(236,11);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    bounding_box_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (x_in_window && y_in_window && bounding_box_state) {
	bounding_box = ISVREF(bounding_box_state,(SI_Long)3L);
	bounding_box_border_width = ISVREF(ISVREF(bounding_box,
		(SI_Long)17L),(SI_Long)44L);
	twice_bounding_box_border_width = IFIX(bounding_box_border_width) 
		<< (SI_Long)1L;
	bounding_box_state_edge_or_corner_qm = ISVREF(bounding_box_state,
		(SI_Long)7L);
	image_plane_of_bounding_box = ISVREF(bounding_box_state,(SI_Long)4L);
	current_frame_transform_qm = Nil;
	current_image_x_scale = ISVREF(image_plane_of_bounding_box,
		(SI_Long)11L);
	current_image_y_scale = ISVREF(image_plane_of_bounding_box,
		(SI_Long)12L);
	current_x_origin_of_drawing = ISVREF(image_plane_of_bounding_box,
		(SI_Long)13L);
	current_y_origin_of_drawing = ISVREF(image_plane_of_bounding_box,
		(SI_Long)14L);
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
		  scale = Current_image_x_scale;
		  value = FIXNUM_MINUS(x_in_window,
			  Current_x_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      x_in_workspace_of_bounding_box = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      x_in_workspace_of_bounding_box = 
			      inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L) {
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		      x_in_workspace_of_bounding_box = temp;
		  }
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		      x_in_workspace_of_bounding_box = temp;
		  }
		  scale = Current_image_y_scale;
		  value = FIXNUM_MINUS(y_in_window,
			  Current_y_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      y_in_workspace_of_bounding_box = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      y_in_workspace_of_bounding_box = 
			      inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L) {
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		      y_in_workspace_of_bounding_box = temp;
		  }
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		      y_in_workspace_of_bounding_box = temp;
		  }
		  offset_x_in_workspace = 
			  FIXNUM_MINUS(x_in_workspace_of_bounding_box,
			  ISVREF(bounding_box_state,(SI_Long)8L));
		  offset_y_in_workspace = 
			  FIXNUM_MINUS(y_in_workspace_of_bounding_box,
			  ISVREF(bounding_box_state,(SI_Long)9L));
		  gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)2L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = IFIX(bounding_box_border_width);
		  old_right_edge = gensymed_symbol_1 - gensymed_symbol_2;
		  if (EQ(bounding_box_state_edge_or_corner_qm,Qright) || 
			  EQ(bounding_box_state_edge_or_corner_qm,
			  Qbottom_right)) {
		      gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)0L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = twice_bounding_box_border_width;
		      gensymed_symbol_1 = gensymed_symbol_1 + 
			      gensymed_symbol_2;
		      gensymed_symbol_2 = IFIX(offset_x_in_workspace);
		      gensymed_symbol_1 = MAX(gensymed_symbol_1,
			      gensymed_symbol_2);
		      gensymed_symbol_2 = IFIX(bounding_box_border_width);
		      new_right_edge_qm = FIX(gensymed_symbol_1 - 
			      gensymed_symbol_2);
		  }
		  else
		      new_right_edge_qm = Nil;
		  gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)3L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = IFIX(bounding_box_border_width);
		  old_bottom_edge = gensymed_symbol_1 - gensymed_symbol_2;
		  if (EQ(bounding_box_state_edge_or_corner_qm,Qbottom) || 
			  EQ(bounding_box_state_edge_or_corner_qm,
			  Qbottom_right)) {
		      gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)1L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = twice_bounding_box_border_width;
		      gensymed_symbol_1 = gensymed_symbol_1 + 
			      gensymed_symbol_2;
		      gensymed_symbol_2 = IFIX(offset_y_in_workspace);
		      gensymed_symbol_1 = MAX(gensymed_symbol_1,
			      gensymed_symbol_2);
		      gensymed_symbol_2 = IFIX(bounding_box_border_width);
		      new_bottom_edge_qm = FIX(gensymed_symbol_1 - 
			      gensymed_symbol_2);
		  }
		  else
		      new_bottom_edge_qm = Nil;
		  gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)0L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = IFIX(bounding_box_border_width);
		  old_left_edge = gensymed_symbol_1 + gensymed_symbol_2;
		  if (EQ(bounding_box_state_edge_or_corner_qm,Qleft) || 
			  EQ(bounding_box_state_edge_or_corner_qm,
			      Qleft_right)) {
		      gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)2L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = twice_bounding_box_border_width;
		      gensymed_symbol_1 = gensymed_symbol_1 - 
			      gensymed_symbol_2;
		      gensymed_symbol_2 = IFIX(offset_x_in_workspace);
		      gensymed_symbol_1 = MIN(gensymed_symbol_1,
			      gensymed_symbol_2);
		      gensymed_symbol_2 = IFIX(bounding_box_border_width);
		      new_left_edge_qm = FIX(gensymed_symbol_1 + 
			      gensymed_symbol_2);
		  }
		  else
		      new_left_edge_qm = Nil;
		  gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		  gensymed_symbol = gensymed_symbol ? 
			  ISVREF(gensymed_symbol,(SI_Long)1L) : 
			  FIX((SI_Long)0L);
		  gensymed_symbol_1 = IFIX(gensymed_symbol);
		  gensymed_symbol_2 = IFIX(bounding_box_border_width);
		  old_top_edge = gensymed_symbol_1 + gensymed_symbol_2;
		  if (EQ(bounding_box_state_edge_or_corner_qm,Qtop) || 
			  EQ(bounding_box_state_edge_or_corner_qm,
			      Qtop_right)) {
		      gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)3L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol_2 = twice_bounding_box_border_width;
		      gensymed_symbol_1 = gensymed_symbol_1 - 
			      gensymed_symbol_2;
		      gensymed_symbol_2 = IFIX(offset_y_in_workspace);
		      gensymed_symbol_1 = MIN(gensymed_symbol_1,
			      gensymed_symbol_2);
		      gensymed_symbol_2 = IFIX(bounding_box_border_width);
		      new_top_edge_qm = FIX(gensymed_symbol_1 + 
			      gensymed_symbol_2);
		  }
		  else
		      new_top_edge_qm = Nil;
		  if (new_left_edge_qm && IFIX(new_left_edge_qm) == 
			  old_left_edge)
		      new_left_edge_qm = Nil;
		  if (new_top_edge_qm && IFIX(new_top_edge_qm) == old_top_edge)
		      new_top_edge_qm = Nil;
		  if (new_right_edge_qm && IFIX(new_right_edge_qm) == 
			  old_right_edge)
		      new_right_edge_qm = Nil;
		  if (new_bottom_edge_qm && IFIX(new_bottom_edge_qm) == 
			  old_bottom_edge)
		      new_bottom_edge_qm = Nil;
		  if (new_left_edge_qm || new_top_edge_qm || 
			  new_right_edge_qm || new_bottom_edge_qm) {
		      update_border_of_bounding_box(bounding_box,
			      new_left_edge_qm,new_top_edge_qm,
			      new_right_edge_qm,new_bottom_edge_qm);
		      bounding_box_state_update_function_qm = 
			      ISVREF(bounding_box_state,(SI_Long)10L);
		      if (bounding_box_state_update_function_qm)
			  result = FUNCALL_3(bounding_box_state_update_function_qm,
				  x_in_workspace_of_bounding_box,
				  y_in_workspace_of_bounding_box,
				  ISVREF(bounding_box_state,(SI_Long)11L));
		      else
			  result = VALUES_1(Nil);
		  }
		  else
		      result = VALUES_1(Nil);
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

static Object Qicon_description_for_class_qm;  /* icon-description-for-class? */

static Object Qicon_editor_table_info_frame_icon_editor;  /* icon-editor-table-info-frame-icon-editor */

static Object Qvariables;          /* variables */

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qicon_editor;        /* icon-editor */

/* ENTER-ICON-EDITOR */
Object enter_icon_editor(class_definition)
    Object class_definition;
{
    Object icon_editor, drawing_description_qm;
    Object inherited_drawing_description_qm, engine, view_pad, icon_width;
    Object icon_height, variable_spec_list, icon_background_layer_qm;
    Object icon_stipple_qm, layers, alist, svref_new_value, temp;
    Object current_label, current_image, current_text, current_stipple;
    Object workspace;
    SI_Long svref_new_value_1;
    Object result;

    x_note_fn_call(236,12);
    icon_editor = create_icon_editor(class_definition);
    drawing_description_qm = 
	    get_lookup_slot_value_given_default(class_definition,
	    Qicon_description_for_class_qm,Nil);
    inherited_drawing_description_qm =  !TRUEP(drawing_description_qm) ? 
	    get_inherited_drawing_description(class_definition) : Nil;
    engine = ISVREF(icon_editor,(SI_Long)11L);
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    set_non_savable_lookup_slot_value(ISVREF(ISVREF(icon_editor,
	    (SI_Long)18L),(SI_Long)5L),
	    Qicon_editor_table_info_frame_icon_editor,icon_editor);
    if ( !TRUEP(drawing_description_qm))
	drawing_description_qm = inherited_drawing_description_qm;
    if (drawing_description_qm) {
	icon_width = FIRST(drawing_description_qm);
	icon_height = SECOND(drawing_description_qm);
	variable_spec_list = 
		get_variable_specification_if_any(drawing_description_qm);
	if (variable_spec_list);
	else
	    variable_spec_list = icon_editor_cons_1(Qvariables,Nil);
	icon_background_layer_qm = 
		get_lookup_slot_value_given_default(class_definition,
		Qicon_background_images,Nil);
	if (icon_background_layer_qm);
	else
	    icon_background_layer_qm = 
		    get_inherited_background_image(class_definition);
	icon_stipple_qm = get_icon_stipple_if_any(drawing_description_qm);
	result = convert_line_drawing_description_to_list_of_layers(drawing_description_qm,
		FIX((SI_Long)4096L),FIX((SI_Long)4096L));
	MVS_2(result,layers,alist);
	SVREF(engine,FIX((SI_Long)3L)) = layers;
	SVREF(icon_editor,FIX((SI_Long)6L)) = alist;
	svref_new_value = 
		copy_tree_including_leaves_using_icon_editor_conses(variable_spec_list);
	SVREF(icon_editor,FIX((SI_Long)7L)) = svref_new_value;
	svref_new_value = 
		copy_tree_including_leaves_using_icon_editor_conses(icon_background_layer_qm);
	SVREF(icon_editor,FIX((SI_Long)8L)) = svref_new_value;
	svref_new_value = last(layers,_);
	SVREF(engine,FIX((SI_Long)4L)) = svref_new_value;
	temp = ISVREF(engine,(SI_Long)4L);
	svref_new_value = CAR(temp);
	SVREF(engine,FIX((SI_Long)6L)) = svref_new_value;
	svref_new_value_1 = layers ? IFIX(FIXNUM_SUB1(length(layers))) : 
		(SI_Long)0L;
	ISVREF(engine,(SI_Long)7L) = FIX(svref_new_value_1);
	svref_new_value = length(layers);
	SVREF(engine,FIX((SI_Long)5L)) = svref_new_value;
	SVREF(engine,FIX((SI_Long)8L)) = icon_width;
	SVREF(engine,FIX((SI_Long)9L)) = icon_height;
	SVREF(engine,FIX((SI_Long)1L)) = icon_width;
	SVREF(engine,FIX((SI_Long)2L)) = icon_height;
	SVREF(engine,FIX((SI_Long)17L)) = icon_stipple_qm;
	SVREF(view_pad,FIX((SI_Long)13L)) = Nil;
	if ( !TRUEP(layers)) {
	    new_icon_layer(ISVREF(engine,(SI_Long)11L),Nil,
		    FIX((SI_Long)0L),engine);
	    layers = ISVREF(engine,(SI_Long)3L);
	    alist = ISVREF(icon_editor,(SI_Long)6L);
	}
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)21L),Nil,Nil);
	temp = ISVREF(engine,(SI_Long)6L);
	current_label = FIRST(temp);
	current_image = image_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	current_text = text_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	current_stipple = stipple_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	enqueue_icon_editor_engine_event(icon_editor,FIX((SI_Long)21L),
		current_label,current_image,current_text,current_stipple);
	if (alist)
	    inform_user_of_current_regions(icon_editor);
    }
    else {
	ISVREF(engine,(SI_Long)8L) = FIX((SI_Long)100L);
	ISVREF(engine,(SI_Long)9L) = FIX((SI_Long)100L);
	ISVREF(engine,(SI_Long)1L) = FIX((SI_Long)100L);
	ISVREF(engine,(SI_Long)2L) = FIX((SI_Long)100L);
	SVREF(engine,FIX((SI_Long)17L)) = Nil;
	svref_new_value = icon_editor_cons_1(Qvariables,Nil);
	SVREF(icon_editor,FIX((SI_Long)7L)) = svref_new_value;
	new_icon_layer(ISVREF(engine,(SI_Long)11L),Nil,FIX((SI_Long)0L),
		engine);
    }
    if (Nil)
	reclaim_icon_editor_slot_value(inherited_drawing_description_qm);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)52L),
	    ISVREF(engine,(SI_Long)17L),Nil);
    recompute_scale_for_layers_pad(icon_editor);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)27L),Nil,Nil);
    recompute_view_pad_size(icon_editor);
    enqueue_icon_editor_translator_event(icon_editor,FIX((SI_Long)20L),
	    ISVREF(engine,(SI_Long)8L),ISVREF(engine,(SI_Long)9L));
    workspace = ISVREF(icon_editor,(SI_Long)4L);
    if (New_g2_classic_ui_p)
	change_slot_value(3,workspace,Qworkspace_background_color_qm,
		get_ui_parameter(1,Qsystem_workspace_background_color));
    put_workspace_on_pane_function(workspace,
	    Current_workstation_detail_pane,Qleft,Qtop,Nil,
	    FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    return enter_context_in_current_workstation(2,Qicon_editor,icon_editor);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_editor_event, Qcurrent_icon_editor_event);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_editor, Qcurrent_icon_editor);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_editor_workspace, Qcurrent_icon_editor_workspace);

DEFINE_VARIABLE_WITH_SYMBOL(Current_workspace_on_image_plane_qm, Qcurrent_workspace_on_image_plane_qm);

static Object list_constant;       /* # */

static Object Qfinish_moving_bounding_box_for_icon_editor;  /* finish-moving-bounding-box-for-icon-editor */

static Object Qreclaim_icon_editor_slot_value;  /* reclaim-icon-editor-slot-value */

static Object Qbottom_left;        /* bottom-left */

static Object Qupdate_moving_bounding_box_for_icon_editor;  /* update-moving-bounding-box-for-icon-editor */

/* EXECUTE-ICON-EDITOR-MOUSE-DOWN-IN-VIEW-PAD */
Object execute_icon_editor_mouse_down_in_view_pad(x_in_window,y_in_window,
	    x_in_workspace,y_in_workspace,icon_editor,image_plane,
	    block_near_cursor)
    Object x_in_window, y_in_window, x_in_workspace, y_in_workspace;
    Object icon_editor, image_plane, block_near_cursor;
{
    Object bounding_box, border_width, gensymed_symbol, left_edge, top_edge;
    Object right_edge, bottom_edge, edge_or_corner_qm;
    Object x_offset_of_mouse_from_edge, y_offset_of_mouse_from_edge, temp;
    Object adjusted_right_edge, adjusted_bottom_edge, temp_1;
    SI_Long arg, arg_1, arg_2;
    Object result;

    x_note_fn_call(236,13);
    bounding_box = ISVREF(ISVREF(icon_editor,(SI_Long)12L),(SI_Long)3L);
    border_width = FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,(SI_Long)17L),
	    (SI_Long)44L));
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge = gensymed_symbol;
    result = select_edge_or_corner_of_bounding_box(5,bounding_box,
	    x_in_window,y_in_window,image_plane, 
	    !EQ(ISVREF(ISVREF(icon_editor,(SI_Long)10L),(SI_Long)1L),
	    FIX((SI_Long)0L)) ? T : Nil);
    MVS_3(result,edge_or_corner_qm,x_offset_of_mouse_from_edge,
	    y_offset_of_mouse_from_edge);
    if (memq_function(edge_or_corner_qm,list_constant)) {
	enqueue_icon_editor_translator_event(icon_editor,FIX((SI_Long)1L),
		x_in_workspace,y_in_workspace);
	establish_next_workstation_context_continuation(Nil,
		Qfinish_moving_bounding_box_for_icon_editor,
		slot_value_list_2(icon_editor,bounding_box),
		Qreclaim_icon_editor_slot_value);
	if (EQ(edge_or_corner_qm,Qbottom_left))
	    temp = Qbottom;
	else if (EQ(edge_or_corner_qm,Qtop_right))
	    temp = Qright;
	else if (EQ(edge_or_corner_qm,Qbottom) || EQ(edge_or_corner_qm,
		Qbottom_right) || EQ(edge_or_corner_qm,Qright))
	    temp = edge_or_corner_qm;
	else
	    temp = Nil;
	return enter_context_in_current_workstation(2,Qbounding_box,
		make_bounding_box_state_1(bounding_box,image_plane,
		x_in_window,y_in_window,temp,x_offset_of_mouse_from_edge,
		y_offset_of_mouse_from_edge,
		Qupdate_moving_bounding_box_for_icon_editor,
		icon_editor_list_2(icon_editor,bounding_box),
		Qreclaim_icon_editor_slot_value));
    }
    else if (FIXNUM_GE(x_in_workspace,left_edge) && 
	    FIXNUM_GE(y_in_workspace,top_edge)) {
	adjusted_right_edge = FIXNUM_SUB1(right_edge);
	adjusted_bottom_edge = FIXNUM_SUB1(bottom_edge);
	arg = IFIX(left_edge);
	arg_1 = IFIX(x_in_workspace);
	arg_2 = IFIX(FIXNUM_ADD(left_edge,border_width));
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = FIXNUM_ADD(left_edge,border_width);
	else {
	    arg = IFIX(FIXNUM_MINUS(adjusted_right_edge,border_width));
	    arg_1 = IFIX(x_in_workspace);
	    arg_2 = IFIX(adjusted_right_edge);
	    if (arg <= arg_1 && arg_1 <= arg_2)
		temp = FIXNUM_MINUS(adjusted_right_edge,border_width);
	    else
		temp = x_in_workspace;
	}
	arg = IFIX(top_edge);
	arg_1 = IFIX(y_in_workspace);
	arg_2 = IFIX(FIXNUM_ADD(top_edge,border_width));
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp_1 = FIXNUM_ADD(top_edge,border_width);
	else {
	    arg = IFIX(FIXNUM_MINUS(adjusted_bottom_edge,border_width));
	    arg_1 = IFIX(y_in_workspace);
	    arg_2 = IFIX(adjusted_bottom_edge);
	    if (arg <= arg_1 && arg_1 <= arg_2)
		temp_1 = FIXNUM_MINUS(adjusted_bottom_edge,border_width);
	    else
		temp_1 = y_in_workspace;
	}
	result = VALUES_2(temp,temp_1);
	MVS_2(result,x_in_workspace,y_in_workspace);
	return enqueue_icon_editor_translator_event(icon_editor,
		FIX((SI_Long)1L),x_in_workspace,y_in_workspace);
    }
    else
	return enqueue_icon_editor_translator_event(icon_editor,
		FIX((SI_Long)46L),Nil,Nil);
}

static Object Qg2_defstruct_structure_name_icon_editor_g2_struct;  /* g2-defstruct-structure-name::icon-editor-g2-struct */

/* HANDLE-MENU-CHOICE-FOR-LAYER-COLOR */
Object handle_menu_choice_for_layer_color(menu_1,new_color,menu_item,
	    icon_editor_qm)
    Object menu_1, new_color, menu_item, icon_editor_qm;
{
    Object gensymed_symbol, x, y, xa, ya, frame_serial_number_setf_arg, old;
    Object new_1, svref_new_value;
    char temp;

    x_note_fn_call(236,14);
    if (new_color && SIMPLE_VECTOR_P(icon_editor_qm) && 
	    EQ(ISVREF(icon_editor_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_icon_editor_g2_struct)) {
	gensymed_symbol = ISVREF(ISVREF(icon_editor_qm,(SI_Long)4L),
		(SI_Long)3L);
	x = ISVREF(icon_editor_qm,(SI_Long)4L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icon_editor_qm,(SI_Long)5L);
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if ( !EQ(menu_1,ISVREF(icon_editor_qm,(SI_Long)26L))) {
	    delete_icon_editor_main_color_menu(icon_editor_qm);
	    SVREF(icon_editor_qm,FIX((SI_Long)26L)) = menu_1;
	    frame_serial_number_setf_arg = Current_frame_serial_number;
	    old = ISVREF(icon_editor_qm,(SI_Long)27L);
	    new_1 = frame_serial_number_setf_arg;
	    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(icon_editor_qm,FIX((SI_Long)27L)) = svref_new_value;
	}
	return enqueue_icon_editor_translator_event(icon_editor_qm,
		FIX((SI_Long)18L),new_color,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

static Object Qenqueue_icon_editor_translator_event_on_return;  /* enqueue-icon-editor-translator-event-on-return */

static Object Qbutton_action_data_qm;  /* button-action-data? */

static Object Qicon_editor_table_info_frame_main_color;  /* icon-editor-table-info-frame-main-color */

static Object Qlayer_color;        /* layer-color */

static Object Qhandle_menu_choice_for_layer_color;  /* handle-menu-choice-for-layer-color */

static Object Qicon_editor_table_info_frame_text;  /* icon-editor-table-info-frame-text */

static Object Qtext;               /* text */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qfinish_doing_icon_editor_type_in;  /* finish-doing-icon-editor-type-in */

static Object Qicon_editor_table_info_frame_stipple;  /* icon-editor-table-info-frame-stipple */

static Object Qstippled_area;      /* stippled-area */

static Object Qicon_editor_table_info_frame_main_region;  /* icon-editor-table-info-frame-main-region */

/* EXECUTE-ICON-EDITOR-MOUSE-DOWN-EVENT */
Object execute_icon_editor_mouse_down_event(icon_editor,mouse_pointer,
	    image_plane)
    Object icon_editor, mouse_pointer, image_plane;
{
    Object x_in_window, y_in_window, x_in_workspace, y_in_workspace;
    Object block_near_cursor_qm, layers_pad, bounding_box;
    Object inner_left_edge_in_workspace, inner_top_edge_in_workspace;
    Object adjusted_bounding_box_border_width, gensymed_symbol;
    Object sub_class_bit_vector, cell_qm, table, frame_qm, slot_name_qm;
    Object class_qualifier_qm, x, y, xa, ya, icon_editor_engine, layer, temp_1;
    Object sublist, drawing_element, old_text_place, old_text;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object initial_string, old_stipple_place, old_stipple;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    SI_Long inner_right_edge_in_workspace, inner_bottom_edge_in_workspace;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(236,15);
    mouse_pointer = mouse_pointer_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    if (mouse_pointer && x_in_window && y_in_window && x_in_workspace && 
	    y_in_workspace) {
	block_near_cursor_qm = find_object_near_mouse(x_in_window,
		y_in_window,image_plane,Nil,list_constant_1);
	if (point_in_view_pad_p(x_in_workspace,y_in_workspace,
		ISVREF(icon_editor,(SI_Long)12L)))
	    return execute_icon_editor_mouse_down_in_view_pad(x_in_window,
		    y_in_window,x_in_workspace,y_in_workspace,icon_editor,
		    image_plane,block_near_cursor_qm);
	else {
	    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
	    bounding_box = ISVREF(layers_pad,(SI_Long)3L);
	    inner_left_edge_in_workspace = ISVREF(layers_pad,(SI_Long)5L);
	    inner_top_edge_in_workspace = ISVREF(layers_pad,(SI_Long)6L);
	    adjusted_bounding_box_border_width = 
		    FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,(SI_Long)17L),
		    (SI_Long)44L));
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(adjusted_bounding_box_border_width);
	    inner_right_edge_in_workspace = gensymed_symbol_1 - 
		    gensymed_symbol_2;
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(adjusted_bounding_box_border_width);
	    inner_bottom_edge_in_workspace = gensymed_symbol_1 - 
		    gensymed_symbol_2;
	    if (FIXNUM_LE(inner_left_edge_in_workspace,x_in_workspace) && 
		    IFIX(x_in_workspace) < inner_right_edge_in_workspace 
		    && FIXNUM_LE(inner_top_edge_in_workspace,
		    y_in_workspace) && IFIX(y_in_workspace) < 
		    inner_bottom_edge_in_workspace)
		return enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)3L),x_in_workspace,y_in_workspace);
	    else if (block_near_cursor_qm) {
		gensymed_symbol = ISVREF(block_near_cursor_qm,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Button_class_description,(SI_Long)18L));
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
		    establish_next_workstation_context_continuation(Nil,
			    Qenqueue_icon_editor_translator_event_on_return,
			    icon_editor_list_2(get_lookup_slot_value_given_default(block_near_cursor_qm,
			    Qbutton_action_data_qm,Nil),image_plane),
			    Qreclaim_icon_editor_slot_value);
		    enter_button_down_context(block_near_cursor_qm,
			    image_plane);
		    return VALUES_1(Nil);
		}
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
		    if (temp) {
			cell_qm = Nil;
			table = Nil;
			frame_qm = Nil;
			slot_name_qm = Nil;
			class_qualifier_qm = Nil;
			result = pick_cell_from_table(4,
				block_near_cursor_qm,image_plane,
				x_in_window,y_in_window);
			MVS_2(result,cell_qm,table);
			if (cell_qm ? CONSP(cell_qm) : TRUEP(Nil)) {
			    result = get_slot_represented_by_text_cell_if_any(cell_qm);
			    MVS_3(result,frame_qm,slot_name_qm,
				    class_qualifier_qm);
			    temp = TRUEP(frame_qm);
			}
			else
			    temp = TRUEP(Nil);
			if (temp ? TRUEP(type_of_slot_if_editable(4,
				ISVREF(ISVREF(frame_qm,(SI_Long)1L),
				(SI_Long)1L),slot_name_qm,Nil,
				class_qualifier_qm)) : TRUEP(Nil)) {
			    if (EQ(slot_name_qm,
				    Qicon_editor_table_info_frame_main_color)) 
					{
				if (ISVREF(icon_editor,(SI_Long)26L)) {
				    gensymed_symbol = 
					    ISVREF(ISVREF(icon_editor,
					    (SI_Long)26L),(SI_Long)3L);
				    x = ISVREF(icon_editor,(SI_Long)26L);
				    temp = SIMPLE_VECTOR_P(x) ? 
					    EQ(ISVREF(x,(SI_Long)1L),
					    Qavailable_frame_vector) : 
					    TRUEP(Qnil);
				    if (temp);
				    else
					temp = FIXNUMP(gensymed_symbol) ? 
						IFIX(gensymed_symbol) == 
						(SI_Long)-1L : TRUEP(Nil);
				    if (temp);
				    else {
					x = gensymed_symbol;
					y = ISVREF(icon_editor,(SI_Long)27L);
					if (FIXNUMP(y))
					    temp = FIXNUMP(x) ? 
						    FIXNUM_LT(y,x) : TRUEP(T);
					else if (FIXNUMP(x))
					    temp = TRUEP(Nil);
					else {
					    xa = M_CAR(y);
					    ya = M_CAR(x);
					    temp = FIXNUM_LT(xa,ya);
					    if (temp);
					    else
						temp = FIXNUM_EQ(xa,ya) ? 
							FIXNUM_LT(M_CDR(y),
							M_CDR(x)) : 
							TRUEP(Qnil);
					}
				    }
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    SVREF(icon_editor,FIX((SI_Long)26L)) = Nil;
				return post_full_color_menu(Qlayer_color,
					ISVREF(Current_workstation,
					(SI_Long)13L),ISVREF(icon_editor,
					(SI_Long)4L),
					Qhandle_menu_choice_for_layer_color,
					slot_value_cons_1(icon_editor,Nil));
			    }
			    else if (EQ(slot_name_qm,
				    Qicon_editor_table_info_frame_text)) {
				icon_editor_engine = ISVREF(icon_editor,
					(SI_Long)11L);
				layer = ISVREF(icon_editor_engine,(SI_Long)6L);
				temp_1 = CDDR(layer);
				sublist = CAR(temp_1);
			      next_loop:
				if ( !TRUEP(sublist))
				    goto end_loop;
				drawing_element = CAR(sublist);
				if (CONSP(drawing_element) && 
					EQ(FIRST(drawing_element),Qtext)) {
				    old_text_place = sublist;
				    goto end_1;
				}
				sublist = M_CDR(sublist);
				goto next_loop;
			      end_loop:
				old_text_place = Qnil;
			      end_1:;
				old_text = 
					copy_drawing_element_with_icon_editor_conses(CAR(old_text_place),
					Nil,Nil);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
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
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_text_specification(old_text);
					  temp_1 = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				initial_string = slot_value_cons_1(temp_1,Nil);
				if (T)
				    reclaim_icon_editor_slot_value(old_text);
				return edit_attribute_table_slot_in_place(12,
					table,frame_qm,slot_name_qm,
					class_qualifier_qm,image_plane,
					Qfinish_doing_icon_editor_type_in,
					slot_name_qm,Nil,Nil,Nil,Nil,
					initial_string);
			    }
			    else if (EQ(slot_name_qm,
				    Qicon_editor_table_info_frame_stipple)) {
				icon_editor_engine = ISVREF(icon_editor,
					(SI_Long)11L);
				layer = ISVREF(icon_editor_engine,(SI_Long)6L);
				temp_1 = CDDR(layer);
				sublist = CAR(temp_1);
			      next_loop_1:
				if ( !TRUEP(sublist))
				    goto end_loop_1;
				drawing_element = CAR(sublist);
				if (CONSP(drawing_element) && 
					EQ(FIRST(drawing_element),
					Qstippled_area)) {
				    old_stipple_place = sublist;
				    goto end_2;
				}
				sublist = M_CDR(sublist);
				goto next_loop_1;
			      end_loop_1:
				old_stipple_place = Qnil;
			      end_2:;
				old_stipple = 
					copy_drawing_element_with_icon_editor_conses(CAR(old_stipple_place),
					Nil,Nil);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
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
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_stipple_specification(old_stipple);
					  temp_1 = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				initial_string = slot_value_cons_1(temp_1,Nil);
				if (T)
				    reclaim_icon_editor_slot_value(old_stipple);
				return edit_attribute_table_slot_in_place(12,
					table,frame_qm,slot_name_qm,
					class_qualifier_qm,image_plane,
					Qfinish_doing_icon_editor_type_in,
					slot_name_qm,Nil,Nil,Nil,Nil,
					initial_string);
			    }
			    else {
				if (EQ(slot_name_qm,
					Qicon_editor_table_info_frame_main_region))
				    inform_user_of_current_regions(icon_editor);
				return edit_attribute_table_slot_in_place(8,
					table,frame_qm,slot_name_qm,
					class_qualifier_qm,image_plane,
					Qfinish_doing_icon_editor_type_in,
					slot_name_qm,Nil);
			    }
			}
			else
			    return VALUES_1(Nil);
		    }
		    else
			return enqueue_icon_editor_translator_event(icon_editor,
				FIX((SI_Long)1L),x_in_workspace,
				y_in_workspace);
		}
	    }
	    else {
		enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)1L),x_in_workspace,y_in_workspace);
		enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)46L),Nil,Nil);
		return run_top_level_event_handler(mouse_pointer);
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qlt_mouse_down_gt;   /* <mouse-down> */

static Object Qkey_pattern_named;  /* key-pattern-named */

static Object Qlt_standard_abort_keys_gt;  /* <standard-abort-keys> */

static Object Qlt_standard_enter_keys_gt;  /* <standard-enter-keys> */

/* EXECUTE-ICON-EDITOR-WORKSTATION-EVENT */
Object execute_icon_editor_workstation_event(workstation_event,mouse_pointer)
    Object workstation_event, mouse_pointer;
{
    Object current_icon_editor_event, current_icon_editor;
    Object current_icon_editor_workspace, current_image_plane_qm;
    Object current_workspace_on_image_plane_qm, key, x_in_workspace;
    Object y_in_workspace, current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, temp;
    Object current_bounding_box, gensymed_symbol, current_left_edge;
    Object current_top_edge, current_right_edge, current_bottom_edge;
    Object current_border_width, adjusted_right_edge, adjusted_bottom_edge;
    Object temp_2, svref_arg_1, gensymed_symbol_1;
    SI_Long temp_1, arg, arg_1, arg_2;
    char temp_3;
    Declare_special(10);
    Object result;

    x_note_fn_call(236,16);
    current_icon_editor_event = workstation_event;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_editor_event,Qcurrent_icon_editor_event,current_icon_editor_event,
	    9);
      current_icon_editor = Specific_structure_for_current_workstation_context;
      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_editor,Qcurrent_icon_editor,current_icon_editor,
	      8);
	current_icon_editor_workspace = ISVREF(Current_icon_editor,
		(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_editor_workspace,Qcurrent_icon_editor_workspace,current_icon_editor_workspace,
		7);
	  current_image_plane_qm = ISVREF(Current_icon_editor_event,
		  (SI_Long)7L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane_qm,Qcurrent_image_plane_qm,current_image_plane_qm,
		  6);
	    current_workspace_on_image_plane_qm = Current_image_plane_qm ? 
		    ISVREF(Current_image_plane_qm,(SI_Long)5L) : Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workspace_on_image_plane_qm,Qcurrent_workspace_on_image_plane_qm,current_workspace_on_image_plane_qm,
		    5);
	      key = ISVREF(Current_icon_editor_event,(SI_Long)1L);
	      if (IFIX(key) == (SI_Long)771L) {
		  if (EQ(Current_workspace_on_image_plane_qm,
			  Current_icon_editor_workspace)) {
		      x_in_workspace = Nil;
		      y_in_workspace = Nil;
		      current_frame_transform_qm = Nil;
		      current_image_x_scale = 
			      ISVREF(Current_image_plane_qm,(SI_Long)11L);
		      current_image_y_scale = 
			      ISVREF(Current_image_plane_qm,(SI_Long)12L);
		      current_x_origin_of_drawing = 
			      ISVREF(Current_image_plane_qm,(SI_Long)13L);
		      current_y_origin_of_drawing = 
			      ISVREF(Current_image_plane_qm,(SI_Long)14L);
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
				scale = Current_image_x_scale;
				value = 
					FIXNUM_MINUS(ISVREF(workstation_event,
					(SI_Long)3L),
					Current_x_origin_of_drawing);
				if (IFIX(scale) == (SI_Long)4096L)
				    x_in_workspace = value;
				else if ( 
					!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value) && FIXNUM_LT(value,
					Isqrt_of_most_positive_fixnum)))
				    x_in_workspace = 
					    inverse_scalef_function(scale,
					    value);
				else if (IFIX(value) >= (SI_Long)0L) {
				    temp = FIX(((IFIX(value) << 
					    (SI_Long)12L) + (IFIX(scale) 
					    >>  -  - (SI_Long)1L)) / 
					    IFIX(scale));
				    x_in_workspace = temp;
				}
				else {
				    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) 
					    << (SI_Long)12L) + 
					    (IFIX(scale) >>  -  - 
					    (SI_Long)1L)) / IFIX(scale);
				    temp = FIXNUM_NEGATE(FIX(temp_1));
				    x_in_workspace = temp;
				}
				scale = Current_image_y_scale;
				value = 
					FIXNUM_MINUS(ISVREF(workstation_event,
					(SI_Long)4L),
					Current_y_origin_of_drawing);
				if (IFIX(scale) == (SI_Long)4096L)
				    y_in_workspace = value;
				else if ( 
					!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value) && FIXNUM_LT(value,
					Isqrt_of_most_positive_fixnum)))
				    y_in_workspace = 
					    inverse_scalef_function(scale,
					    value);
				else if (IFIX(value) >= (SI_Long)0L) {
				    temp = FIX(((IFIX(value) << 
					    (SI_Long)12L) + (IFIX(scale) 
					    >>  -  - (SI_Long)1L)) / 
					    IFIX(scale));
				    y_in_workspace = temp;
				}
				else {
				    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) 
					    << (SI_Long)12L) + 
					    (IFIX(scale) >>  -  - 
					    (SI_Long)1L)) / IFIX(scale);
				    temp = FIXNUM_NEGATE(FIX(temp_1));
				    y_in_workspace = temp;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		      if (ISVREF(Current_icon_editor,(SI_Long)22L)) {
			  current_bounding_box = 
				  ISVREF(ISVREF(Current_icon_editor,
				  (SI_Long)12L),(SI_Long)3L);
			  gensymed_symbol = ISVREF(current_bounding_box,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)0L) : 
				  FIX((SI_Long)0L);
			  current_left_edge = gensymed_symbol;
			  gensymed_symbol = ISVREF(current_bounding_box,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)1L) : 
				  FIX((SI_Long)0L);
			  current_top_edge = gensymed_symbol;
			  gensymed_symbol = ISVREF(current_bounding_box,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)2L) : 
				  FIX((SI_Long)0L);
			  current_right_edge = gensymed_symbol;
			  gensymed_symbol = ISVREF(current_bounding_box,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)3L) : 
				  FIX((SI_Long)0L);
			  current_bottom_edge = gensymed_symbol;
			  current_border_width = 
				  FIXNUM_ADD1(ISVREF(ISVREF(current_bounding_box,
				  (SI_Long)17L),(SI_Long)44L));
			  adjusted_right_edge = 
				  FIXNUM_SUB1(current_right_edge);
			  adjusted_bottom_edge = 
				  FIXNUM_SUB1(current_bottom_edge);
			  arg = IFIX(current_left_edge);
			  arg_1 = IFIX(x_in_workspace);
			  arg_2 = IFIX(FIXNUM_ADD(current_left_edge,
				  current_border_width));
			  if (arg <= arg_1 && arg_1 <= arg_2)
			      temp = FIXNUM_ADD(current_left_edge,
				      current_border_width);
			  else {
			      arg = IFIX(FIXNUM_MINUS(adjusted_right_edge,
				      current_border_width));
			      arg_1 = IFIX(x_in_workspace);
			      arg_2 = IFIX(adjusted_right_edge);
			      if (arg <= arg_1 && arg_1 <= arg_2)
				  temp = FIXNUM_MINUS(adjusted_right_edge,
					  current_border_width);
			      else
				  temp = x_in_workspace;
			  }
			  arg = IFIX(current_top_edge);
			  arg_1 = IFIX(y_in_workspace);
			  arg_2 = IFIX(FIXNUM_ADD(current_top_edge,
				  current_border_width));
			  if (arg <= arg_1 && arg_1 <= arg_2)
			      temp_2 = FIXNUM_ADD(current_top_edge,
				      current_border_width);
			  else {
			      arg = IFIX(FIXNUM_MINUS(adjusted_bottom_edge,
				      current_border_width));
			      arg_1 = IFIX(y_in_workspace);
			      arg_2 = IFIX(adjusted_bottom_edge);
			      if (arg <= arg_1 && arg_1 <= arg_2)
				  temp_2 = 
					  FIXNUM_MINUS(adjusted_bottom_edge,
					  current_border_width);
			      else
				  temp_2 = y_in_workspace;
			  }
			  result = VALUES_2(temp,temp_2);
			  MVS_2(result,x_in_workspace,y_in_workspace);
		      }
		      result = enqueue_icon_editor_translator_event(Current_icon_editor,
			      FIX((SI_Long)0L),x_in_workspace,y_in_workspace);
		  }
		  else
		      result = VALUES_1(Nil);
	      }
	      else if (IFIX(key) == (SI_Long)769L) {
		  svref_arg_1 = Current_icon_editor;
		  SVREF(svref_arg_1,FIX((SI_Long)22L)) = Nil;
		  if (EQ(Current_workspace_on_image_plane_qm,
			  Current_icon_editor_workspace)) {
		      x_in_workspace = Nil;
		      y_in_workspace = Nil;
		      current_frame_transform_qm = Nil;
		      current_image_x_scale = 
			      ISVREF(Current_image_plane_qm,(SI_Long)11L);
		      current_image_y_scale = 
			      ISVREF(Current_image_plane_qm,(SI_Long)12L);
		      current_x_origin_of_drawing = 
			      ISVREF(Current_image_plane_qm,(SI_Long)13L);
		      current_y_origin_of_drawing = 
			      ISVREF(Current_image_plane_qm,(SI_Long)14L);
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
				scale = Current_image_x_scale;
				value = 
					FIXNUM_MINUS(ISVREF(workstation_event,
					(SI_Long)3L),
					Current_x_origin_of_drawing);
				if (IFIX(scale) == (SI_Long)4096L)
				    x_in_workspace = value;
				else if ( 
					!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value) && FIXNUM_LT(value,
					Isqrt_of_most_positive_fixnum)))
				    x_in_workspace = 
					    inverse_scalef_function(scale,
					    value);
				else if (IFIX(value) >= (SI_Long)0L) {
				    temp = FIX(((IFIX(value) << 
					    (SI_Long)12L) + (IFIX(scale) 
					    >>  -  - (SI_Long)1L)) / 
					    IFIX(scale));
				    x_in_workspace = temp;
				}
				else {
				    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) 
					    << (SI_Long)12L) + 
					    (IFIX(scale) >>  -  - 
					    (SI_Long)1L)) / IFIX(scale);
				    temp = FIXNUM_NEGATE(FIX(temp_1));
				    x_in_workspace = temp;
				}
				scale = Current_image_y_scale;
				value = 
					FIXNUM_MINUS(ISVREF(workstation_event,
					(SI_Long)4L),
					Current_y_origin_of_drawing);
				if (IFIX(scale) == (SI_Long)4096L)
				    y_in_workspace = value;
				else if ( 
					!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					value) && FIXNUM_LT(value,
					Isqrt_of_most_positive_fixnum)))
				    y_in_workspace = 
					    inverse_scalef_function(scale,
					    value);
				else if (IFIX(value) >= (SI_Long)0L) {
				    temp = FIX(((IFIX(value) << 
					    (SI_Long)12L) + (IFIX(scale) 
					    >>  -  - (SI_Long)1L)) / 
					    IFIX(scale));
				    y_in_workspace = temp;
				}
				else {
				    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) 
					    << (SI_Long)12L) + 
					    (IFIX(scale) >>  -  - 
					    (SI_Long)1L)) / IFIX(scale);
				    temp = FIXNUM_NEGATE(FIX(temp_1));
				    y_in_workspace = temp;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		      current_bounding_box = 
			      ISVREF(ISVREF(Current_icon_editor,
			      (SI_Long)12L),(SI_Long)3L);
		      gensymed_symbol = ISVREF(current_bounding_box,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)0L) : 
			      FIX((SI_Long)0L);
		      current_left_edge = gensymed_symbol;
		      gensymed_symbol = ISVREF(current_bounding_box,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)1L) : 
			      FIX((SI_Long)0L);
		      current_top_edge = gensymed_symbol;
		      gensymed_symbol = ISVREF(current_bounding_box,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)2L) : 
			      FIX((SI_Long)0L);
		      current_right_edge = gensymed_symbol;
		      gensymed_symbol = ISVREF(current_bounding_box,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)3L) : 
			      FIX((SI_Long)0L);
		      current_bottom_edge = gensymed_symbol;
		      current_border_width = 
			      FIXNUM_ADD1(ISVREF(ISVREF(current_bounding_box,
			      (SI_Long)17L),(SI_Long)44L));
		      adjusted_right_edge = FIXNUM_SUB1(current_right_edge);
		      adjusted_bottom_edge = FIXNUM_SUB1(current_bottom_edge);
		      arg = IFIX(current_left_edge);
		      arg_1 = IFIX(x_in_workspace);
		      arg_2 = IFIX(FIXNUM_ADD(current_left_edge,
			      current_border_width));
		      if (arg <= arg_1 && arg_1 <= arg_2)
			  temp = FIXNUM_ADD(current_left_edge,
				  current_border_width);
		      else {
			  arg = IFIX(FIXNUM_MINUS(adjusted_right_edge,
				  current_border_width));
			  arg_1 = IFIX(x_in_workspace);
			  arg_2 = IFIX(adjusted_right_edge);
			  if (arg <= arg_1 && arg_1 <= arg_2)
			      temp = FIXNUM_MINUS(adjusted_right_edge,
				      current_border_width);
			  else
			      temp = x_in_workspace;
		      }
		      arg = IFIX(current_top_edge);
		      arg_1 = IFIX(y_in_workspace);
		      arg_2 = IFIX(FIXNUM_ADD(current_top_edge,
			      current_border_width));
		      if (arg <= arg_1 && arg_1 <= arg_2)
			  temp_2 = FIXNUM_ADD(current_top_edge,
				  current_border_width);
		      else {
			  arg = IFIX(FIXNUM_MINUS(adjusted_bottom_edge,
				  current_border_width));
			  arg_1 = IFIX(y_in_workspace);
			  arg_2 = IFIX(adjusted_bottom_edge);
			  if (arg <= arg_1 && arg_1 <= arg_2)
			      temp_2 = FIXNUM_MINUS(adjusted_bottom_edge,
				      current_border_width);
			  else
			      temp_2 = y_in_workspace;
		      }
		      result = VALUES_2(temp,temp_2);
		      MVS_2(result,x_in_workspace,y_in_workspace);
		      temp_2 = Current_icon_editor;
		      temp = point_in_view_pad_p(x_in_workspace,
			      y_in_workspace,ISVREF(Current_icon_editor,
			      (SI_Long)12L)) ? FIX((SI_Long)2L) : 
			      FIX((SI_Long)4L);
		      result = enqueue_icon_editor_translator_event(temp_2,
			      temp,x_in_workspace,y_in_workspace);
		  }
		  else
		      result = VALUES_1(Nil);
	      }
	      else {
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_mouse_down_gt),
			  Qkey_pattern_named)) {
		      gensymed_symbol = 
			      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_mouse_down_gt),
			      Qkey_pattern_named);
		      gensymed_symbol_1 = key;
		      temp_3 = TRUEP(inline_funcall_1(gensymed_symbol,
			      gensymed_symbol_1));
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3) {
		      svref_arg_1 = Current_icon_editor;
		      SVREF(svref_arg_1,FIX((SI_Long)22L)) = T;
		      if (EQ(Current_workspace_on_image_plane_qm,
			      Current_icon_editor_workspace))
			  result = execute_icon_editor_mouse_down_event(Current_icon_editor,
				  mouse_pointer,Current_image_plane_qm);
		      else
			  result = run_top_level_event_handler(mouse_pointer);
		  }
		  else if (IFIX(key) == (SI_Long)404L)
		      result = enqueue_icon_editor_translator_event(Current_icon_editor,
			      FIX((SI_Long)6L),Nil,Nil);
		  else if (IFIX(key) == (SI_Long)415L)
		      result = enqueue_icon_editor_translator_event(Current_icon_editor,
			      FIX((SI_Long)52L),Nil,Nil);
		  else {
		      if (getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_standard_abort_keys_gt),
			      Qkey_pattern_named)) {
			  gensymed_symbol = 
				  getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_standard_abort_keys_gt),
				  Qkey_pattern_named);
			  gensymed_symbol_1 = key;
			  temp_3 = TRUEP(inline_funcall_1(gensymed_symbol,
				  gensymed_symbol_1));
		      }
		      else
			  temp_3 = TRUEP(Nil);
		      if (temp_3)
			  result = abort_current_workstation_context(Qicon_editor);
		      else {
			  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_standard_enter_keys_gt),
				  Qkey_pattern_named)) {
			      gensymed_symbol = 
				      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlt_standard_enter_keys_gt),
				      Qkey_pattern_named);
			      gensymed_symbol_1 = key;
			      temp = inline_funcall_1(gensymed_symbol,
				      gensymed_symbol_1);
			  }
			  else
			      temp = Nil;
			  if (temp)
			      result = VALUES_1(temp);
			  else
			      result = VALUES_1(Qnil);
		      }
		  }
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qworkspace;          /* workspace */

/* MOUSE-GESTURE-ON-IMAGE-PLANE-ICON-EDITOR */
Object mouse_gesture_on_image_plane_icon_editor(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, icon_editor, workspace;

    x_note_fn_call(236,17);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    icon_editor = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    if (mouse_pointer_1 && icon_editor && workspace) {
	if (EQ(workspace,ISVREF(icon_editor,(SI_Long)4L)))
	    return some_event_in_icon_editor(mouse_pointer_1);
	else
	    return run_top_level_event_handler(mouse_pointer_1);
    }
    else
	return VALUES_1(Nil);
}

/* SOME-EVENT-IN-ICON-EDITOR */
Object some_event_in_icon_editor(mouse_pointer)
    Object mouse_pointer;
{
    Object event, mouse_pointer_1;

    x_note_fn_call(236,18);
    event = event_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (event && mouse_pointer_1)
	return execute_icon_editor_workstation_event(event,mouse_pointer_1);
    else
	return VALUES_1(Nil);
}

static Object Qediting;            /* editing */

static Object list_constant_2;     /* # */

static Object Qicon_editor_table_info_frame_icon_width;  /* icon-editor-table-info-frame-icon-width */

static Object Qicon_editor_table_info_frame_icon_height;  /* icon-editor-table-info-frame-icon-height */

static Object Qicon_editor_table_info_frame_global_stipple;  /* icon-editor-table-info-frame-global-stipple */

static Object string_constant;     /* "Illegal color ~a -- not accepted." */

static Object Qicon_editor_table_info_frame_main_image;  /* icon-editor-table-info-frame-main-image */

/* FINISH-DOING-ICON-EDITOR-TYPE-IN */
Object finish_doing_icon_editor_type_in(workstation_context)
    Object workstation_context;
{
    Object slot_name, edit_state, gensymed_symbol, x, y, xa, ya, icon_editor;
    Object temp_1, table_info_frame, new_color, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(236,19);
    slot_name = ISVREF(workstation_context,(SI_Long)5L);
    edit_state = Specific_structure_for_current_workstation_context;
    exit_current_workstation_context_in_return_function(Qediting);
    gensymed_symbol = 
	    ISVREF(ISVREF(Specific_structure_for_current_workstation_context,
	    (SI_Long)4L),(SI_Long)3L);
    x = ISVREF(Specific_structure_for_current_workstation_context,(SI_Long)4L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(Specific_structure_for_current_workstation_context,
		(SI_Long)5L);
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
    if (temp)
	return abort_current_workstation_context(Qicon_editor);
    else {
	icon_editor = Specific_structure_for_current_workstation_context;
	if (member_eql(slot_name,list_constant_2))
	    temp_1 = ISVREF(icon_editor,(SI_Long)18L);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_icon_width) || 
		EQ(slot_name,Qicon_editor_table_info_frame_icon_height) || 
		EQ(slot_name,Qicon_editor_table_info_frame_global_stipple))
	    temp_1 = ISVREF(icon_editor,(SI_Long)17L);
	else
	    temp_1 = Qnil;
	table_info_frame = ISVREF(temp_1,(SI_Long)5L);
	if (EQ(slot_name,Qicon_editor_table_info_frame_main_region))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)17L),ISVREF(table_info_frame,
		    (SI_Long)21L),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_main_color)) {
	    new_color = ISVREF(table_info_frame,(SI_Long)22L);
	    if (color_or_metacolor_p(new_color))
		return enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)18L),new_color,Nil);
	    else {
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)7L),ISVREF(ISVREF(icon_editor,
			(SI_Long)11L),(SI_Long)11L),Nil);
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
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			  tformat(2,string_constant,new_color);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),temp_1,Nil);
	    }
	}
	else if (EQ(slot_name,Qicon_editor_table_info_frame_main_image))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)65L),
		    get_lookup_slot_value_given_default(table_info_frame,
		    Qicon_editor_table_info_frame_main_image,Nil),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_text))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)66L),
		    get_lookup_slot_value_given_default(table_info_frame,
		    Qicon_editor_table_info_frame_text,Nil),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_stipple))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)67L),
		    get_lookup_slot_value_given_default(table_info_frame,
		    Qicon_editor_table_info_frame_stipple,Nil),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_global_stipple))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)68L),
		    get_lookup_slot_value_given_default(table_info_frame,
		    Qicon_editor_table_info_frame_global_stipple,Nil),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_icon_width))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)21L),ISVREF(table_info_frame,
		    (SI_Long)25L),Nil);
	else if (EQ(slot_name,Qicon_editor_table_info_frame_icon_height))
	    return enqueue_icon_editor_translator_event(icon_editor,
		    FIX((SI_Long)22L),ISVREF(table_info_frame,
		    (SI_Long)26L),Nil);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qbutton_down;        /* button-down */

/* ENQUEUE-ICON-EDITOR-TRANSLATOR-EVENT-ON-RETURN */
Object enqueue_icon_editor_translator_event_on_return(workstation_context)
    Object workstation_context;
{
    Object temp, translator_event, image_plane, icon_editor;

    x_note_fn_call(236,20);
    temp = ISVREF(workstation_context,(SI_Long)5L);
    translator_event = FIRST(temp);
    temp = ISVREF(workstation_context,(SI_Long)5L);
    image_plane = SECOND(temp);
    exit_current_workstation_context_in_return_function(Qbutton_down);
    icon_editor = Specific_structure_for_current_workstation_context;
    return enqueue_icon_editor_translator_event(icon_editor,
	    translator_event,image_plane,Nil);
}

/* UPDATE-MOVING-BOUNDING-BOX-WITH-EXPANDED-ARGUMENTS */
Object update_moving_bounding_box_with_expanded_arguments(x_in_workspace,
	    y_in_workspace,icon_editor,bounding_box)
    Object x_in_workspace, y_in_workspace, icon_editor, bounding_box;
{
    Object gensymed_symbol;
    SI_Long twice_bounding_box_border_width, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, new_width, new_height;

    x_note_fn_call(236,21);
    twice_bounding_box_border_width = 
	    IFIX(FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,(SI_Long)17L),
	    (SI_Long)44L))) << (SI_Long)1L;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = twice_bounding_box_border_width;
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    new_width = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = twice_bounding_box_border_width;
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    new_height = gensymed_symbol_1 - gensymed_symbol_2;
    enqueue_icon_editor_translator_event(icon_editor,FIX((SI_Long)23L),
	    FIX(new_width),Nil);
    enqueue_icon_editor_translator_event(icon_editor,FIX((SI_Long)24L),
	    FIX(new_height),Nil);
    return enqueue_icon_editor_translator_event(icon_editor,
	    FIX((SI_Long)0L),x_in_workspace,y_in_workspace);
}

/* UPDATE-MOVING-BOUNDING-BOX-FOR-ICON-EDITOR */
Object update_moving_bounding_box_for_icon_editor(x_in_workspace,
	    y_in_workspace,icon_editor_and_bounding_box)
    Object x_in_workspace, y_in_workspace, icon_editor_and_bounding_box;
{
    x_note_fn_call(236,22);
    return update_moving_bounding_box_with_expanded_arguments(x_in_workspace,
	    y_in_workspace,CAR(icon_editor_and_bounding_box),
	    SECOND(icon_editor_and_bounding_box));
}

/* FINISH-MOVING-BOUNDING-BOX-FOR-ICON-EDITOR */
Object finish_moving_bounding_box_for_icon_editor(bounding_context)
    Object bounding_context;
{
    Object icon_editor;

    x_note_fn_call(236,23);
    exit_current_workstation_context_in_return_function(Qbounding_box);
    icon_editor = Specific_structure_for_current_workstation_context;
    return enqueue_icon_editor_translator_event(icon_editor,
	    FIX((SI_Long)25L),Nil,Nil);
}

void icons5_INIT()
{
    Object temp, reclaim_structure_for_bounding_box_state_1;
    Object valid_workstation_context_p_for_bounding_box_state_1;
    Object clean_up_workstation_context_for_bounding_box_state_1;
    Object AB_package, Qsome_event_in_icon_editor, Qnew_style_event_handler;
    Object Qmouse_gesture_on_image_plane_icon_editor, Qinternal;
    Object string_constant_4, Qicon_editor_keymap;
    Object Qrun_top_level_event_handler, Qbutton_label, Qname_box;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmouse_motion_in_bounding_box_state;
    Object Qany_mouse_up_or_down_in_bounding_box_state, Qbounding_box_state;
    Object Qclean_up_workstation_context, Qvalid_workstation_context_p;
    Object string_constant_3, Qtop_level;
    Object Qselection_style_of_workstation_context_type;
    Object Qtop_level_with_mouse_tracking_is_selection_style;
    Object Qreclaim_structure, Qoutstanding_bounding_box_state_count;
    Object Qbounding_box_state_structure_memory_usage, Qutilities2;
    Object string_constant_2, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_1, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;

    x_note_fn_call(236,24);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qicon_background_images = STATIC_SYMBOL("ICON-BACKGROUND-IMAGES",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_bounding_box_state_g2_struct = 
	    STATIC_SYMBOL("BOUNDING-BOX-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbounding_box_state = STATIC_SYMBOL("BOUNDING-BOX-STATE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_bounding_box_state_g2_struct,
	    Qbounding_box_state,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qbounding_box_state,
	    Qg2_defstruct_structure_name_bounding_box_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_bounding_box_state == UNBOUND)
	The_type_description_of_bounding_box_state = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8m83fQy1o83fQy83-Sy8n8k1l83-Sy0000001m1n8y83-2uy1u83qly83qny83qry83qty83qmy83qsy83quy83qoy83qqy83qpy1m8x83-Sykxk0k0");
    temp = The_type_description_of_bounding_box_state;
    The_type_description_of_bounding_box_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_1));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_bounding_box_state_g2_struct,
	    The_type_description_of_bounding_box_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qbounding_box_state,
	    The_type_description_of_bounding_box_state,
	    Qtype_description_of_type);
    Qoutstanding_bounding_box_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-BOUNDING-BOX-STATE-COUNT",AB_package);
    Qbounding_box_state_structure_memory_usage = 
	    STATIC_SYMBOL("BOUNDING-BOX-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_2 = STATIC_STRING("1q83fQy8s83-L+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_bounding_box_state_count);
    push_optimized_constant(Qbounding_box_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    Qchain_of_available_bounding_box_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BOUNDING-BOX-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_bounding_box_states,
	    Chain_of_available_bounding_box_states);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_bounding_box_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbounding_box_state_count = STATIC_SYMBOL("BOUNDING-BOX-STATE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbounding_box_state_count,
	    Bounding_box_state_count);
    record_system_variable(Qbounding_box_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_bounding_box_states_vector == UNBOUND)
	Chain_of_available_bounding_box_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbounding_box_state_structure_memory_usage,
	    STATIC_FUNCTION(bounding_box_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_bounding_box_state_count,
	    STATIC_FUNCTION(outstanding_bounding_box_state_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_bounding_box_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_bounding_box_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qbounding_box_state,
	    reclaim_structure_for_bounding_box_state_1);
    Qtop_level_with_mouse_tracking_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qbounding_box_state,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qbounding_box = STATIC_SYMBOL("BOUNDING-BOX",AB_package);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    make_context_description(Qbounding_box,Qtop_level,Qnil,Qnil);
    Qmouse_motion_in_bounding_box_state = 
	    STATIC_SYMBOL("MOUSE-MOTION-IN-BOUNDING-BOX-STATE",AB_package);
    Qany_mouse_up_or_down_in_bounding_box_state = 
	    STATIC_SYMBOL("ANY-MOUSE-UP-OR-DOWN-IN-BOUNDING-BOX-STATE",
	    AB_package);
    string_constant_3 = STATIC_STRING("1n1n830+y8k9k1n830-y8k9l1n830Dy8k9l");
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qmouse_motion_in_bounding_box_state);
    push_optimized_constant(Qany_mouse_up_or_down_in_bounding_box_state);
    make_keymap(Qbounding_box,Qbounding_box,
	    regenerate_optimized_constant(string_constant_3),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qbounding_box,Qbounding_box);
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    valid_workstation_context_p_for_bounding_box_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_bounding_box_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qbounding_box_state,
	    valid_workstation_context_p_for_bounding_box_state_1);
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_bounding_box_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_bounding_box_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qbounding_box_state,
	    clean_up_workstation_context_for_bounding_box_state_1);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qany_mouse_up_or_down_in_bounding_box_state,
	    Qany_mouse_up_or_down_in_bounding_box_state,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qany_mouse_up_or_down_in_bounding_box_state,
	    STATIC_FUNCTION(any_mouse_up_or_down_in_bounding_box_state,NIL,
	    FALSE,1,1));
    mutate_global_property(Qmouse_motion_in_bounding_box_state,
	    Qmouse_motion_in_bounding_box_state,Qnew_style_event_handler);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom_right = STATIC_SYMBOL("BOTTOM-RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qleft_right = STATIC_SYMBOL("LEFT-RIGHT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qtop_right = STATIC_SYMBOL("TOP-RIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_bounding_box_state,
	    STATIC_FUNCTION(mouse_motion_in_bounding_box_state,NIL,FALSE,1,1));
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    Qicon_editor_table_info_frame_icon_editor = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-EDITOR",
	    AB_package);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qicon_editor = STATIC_SYMBOL("ICON-EDITOR",AB_package);
    Qbottom_left = STATIC_SYMBOL("BOTTOM-LEFT",AB_package);
    list_constant = STATIC_LIST((SI_Long)5L,Qbottom_right,Qright,Qbottom,
	    Qbottom_left,Qtop_right);
    Qfinish_moving_bounding_box_for_icon_editor = 
	    STATIC_SYMBOL("FINISH-MOVING-BOUNDING-BOX-FOR-ICON-EDITOR",
	    AB_package);
    Qreclaim_icon_editor_slot_value = 
	    STATIC_SYMBOL("RECLAIM-ICON-EDITOR-SLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icon_editor_slot_value,
	    STATIC_FUNCTION(reclaim_icon_editor_slot_value,NIL,FALSE,1,1));
    Qupdate_moving_bounding_box_for_icon_editor = 
	    STATIC_SYMBOL("UPDATE-MOVING-BOUNDING-BOX-FOR-ICON-EDITOR",
	    AB_package);
    Qg2_defstruct_structure_name_icon_editor_g2_struct = 
	    STATIC_SYMBOL("ICON-EDITOR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    Qbutton_label = STATIC_SYMBOL("BUTTON-LABEL",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qname_box,Qbutton_label);
    Qenqueue_icon_editor_translator_event_on_return = 
	    STATIC_SYMBOL("ENQUEUE-ICON-EDITOR-TRANSLATOR-EVENT-ON-RETURN",
	    AB_package);
    Qbutton_action_data_qm = STATIC_SYMBOL("BUTTON-ACTION-DATA\?",AB_package);
    Qicon_editor_table_info_frame_main_color = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-COLOR",
	    AB_package);
    Qlayer_color = STATIC_SYMBOL("LAYER-COLOR",AB_package);
    Qhandle_menu_choice_for_layer_color = 
	    STATIC_SYMBOL("HANDLE-MENU-CHOICE-FOR-LAYER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_menu_choice_for_layer_color,
	    STATIC_FUNCTION(handle_menu_choice_for_layer_color,NIL,FALSE,4,4));
    Qicon_editor_table_info_frame_text = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-TEXT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qfinish_doing_icon_editor_type_in = 
	    STATIC_SYMBOL("FINISH-DOING-ICON-EDITOR-TYPE-IN",AB_package);
    Qicon_editor_table_info_frame_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-STIPPLE",AB_package);
    Qstippled_area = STATIC_SYMBOL("STIPPLED-AREA",AB_package);
    Qicon_editor_table_info_frame_main_region = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-REGION",
	    AB_package);
    Qlt_mouse_down_gt = STATIC_SYMBOL("<MOUSE-DOWN>",AB_package);
    Qkey_pattern_named = STATIC_SYMBOL("KEY-PATTERN-NAMED",AB_package);
    Qlt_standard_abort_keys_gt = STATIC_SYMBOL("<STANDARD-ABORT-KEYS>",
	    AB_package);
    Qlt_standard_enter_keys_gt = STATIC_SYMBOL("<STANDARD-ENTER-KEYS>",
	    AB_package);
    Qrun_top_level_event_handler = 
	    STATIC_SYMBOL("RUN-TOP-LEVEL-EVENT-HANDLER",AB_package);
    Qmouse_gesture_on_image_plane_icon_editor = 
	    STATIC_SYMBOL("MOUSE-GESTURE-ON-IMAGE-PLANE-ICON-EDITOR",
	    AB_package);
    Qsome_event_in_icon_editor = STATIC_SYMBOL("SOME-EVENT-IN-ICON-EDITOR",
	    AB_package);
    Qicon_editor_keymap = STATIC_SYMBOL("ICON-EDITOR-KEYMAP",AB_package);
    string_constant_4 = 
	    STATIC_STRING("1s1n836Xy8k9k1n834xy8k9k1n83-Idy8349y9l1n83-Idy8k9k1n32Gy8k9m1n32Ry8k9m1n831-y8k9m1n83XHy8k9k");
    clear_optimized_constants();
    push_optimized_constant(Qrun_top_level_event_handler);
    push_optimized_constant(Qmouse_gesture_on_image_plane_icon_editor);
    push_optimized_constant(Qsome_event_in_icon_editor);
    make_keymap(Qicon_editor_keymap,Qnil,
	    regenerate_optimized_constant(string_constant_4),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    mutate_global_property(Qmouse_gesture_on_image_plane_icon_editor,
	    Qmouse_gesture_on_image_plane_icon_editor,
	    Qnew_style_event_handler);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_gesture_on_image_plane_icon_editor,
	    STATIC_FUNCTION(mouse_gesture_on_image_plane_icon_editor,NIL,
	    FALSE,1,1));
    mutate_global_property(Qsome_event_in_icon_editor,
	    Qsome_event_in_icon_editor,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qsome_event_in_icon_editor,
	    STATIC_FUNCTION(some_event_in_icon_editor,NIL,FALSE,1,1));
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    Qicon_editor_table_info_frame_main_image = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-IMAGE",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)5L,
	    Qicon_editor_table_info_frame_main_color,
	    Qicon_editor_table_info_frame_main_region,
	    Qicon_editor_table_info_frame_main_image,
	    Qicon_editor_table_info_frame_text,
	    Qicon_editor_table_info_frame_stipple);
    Qicon_editor_table_info_frame_icon_width = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-WIDTH",
	    AB_package);
    Qicon_editor_table_info_frame_icon_height = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-HEIGHT",
	    AB_package);
    Qicon_editor_table_info_frame_global_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-GLOBAL-STIPPLE",
	    AB_package);
    string_constant = STATIC_STRING("Illegal color ~a -- not accepted.");
    SET_SYMBOL_FUNCTION(Qfinish_doing_icon_editor_type_in,
	    STATIC_FUNCTION(finish_doing_icon_editor_type_in,NIL,FALSE,1,1));
    Qbutton_down = STATIC_SYMBOL("BUTTON-DOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qenqueue_icon_editor_translator_event_on_return,
	    STATIC_FUNCTION(enqueue_icon_editor_translator_event_on_return,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qupdate_moving_bounding_box_for_icon_editor,
	    STATIC_FUNCTION(update_moving_bounding_box_for_icon_editor,NIL,
	    FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qfinish_moving_bounding_box_for_icon_editor,
	    STATIC_FUNCTION(finish_moving_bounding_box_for_icon_editor,NIL,
	    FALSE,1,1));
}
