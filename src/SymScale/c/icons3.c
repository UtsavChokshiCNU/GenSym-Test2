/* icons3.c
 * Input file:  icons3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons3.h"


/* POINT-IN-DRAW-AREA-OF-VIEW-PAD-P */
Object point_in_draw_area_of_view_pad_p(x_in_workspace,y_in_workspace,
	    engine,view_pad)
    Object x_in_workspace, y_in_workspace, engine, view_pad;
{
    Object scale, value;
    SI_Long gensymed_symbol, unshifted_result, gensymed_symbol_1;
    char temp;

    x_note_fn_call(234,0);
    if (FIXNUM_LE(ISVREF(view_pad,(SI_Long)5L),x_in_workspace)) {
	scale = ISVREF(view_pad,(SI_Long)10L);
	value = ISVREF(engine,(SI_Long)1L);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol = IFIX(scalef_function(scale,value));
	gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)5L));
	temp = FIXNUM_LE(x_in_workspace,FIX(gensymed_symbol + 
		gensymed_symbol_1));
    }
    else
	temp = TRUEP(Nil);
    if (temp ? FIXNUM_LE(ISVREF(view_pad,(SI_Long)6L),y_in_workspace) : 
	    TRUEP(Nil)) {
	scale = ISVREF(view_pad,(SI_Long)11L);
	value = ISVREF(engine,(SI_Long)2L);
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol = IFIX(scalef_function(scale,value));
	gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)6L));
	return VALUES_1(FIXNUM_LE(y_in_workspace,FIX(gensymed_symbol + 
		gensymed_symbol_1)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SNAP-TO-LIMITS-OF-WIDTH-AND-HEIGHT-IF-NECESSARY */
Object snap_to_limits_of_width_and_height_if_necessary(x_in_view_pad,
	    y_in_view_pad,icon_width,icon_height)
    Object x_in_view_pad, y_in_view_pad, icon_width, icon_height;
{
    Object temp, temp_1;

    x_note_fn_call(234,1);
    if (IFIX(x_in_view_pad) < (SI_Long)0L)
	temp = FIX((SI_Long)0L);
    else if (FIXNUM_GT(x_in_view_pad,icon_width))
	temp = icon_width;
    else
	temp = x_in_view_pad;
    if (IFIX(y_in_view_pad) < (SI_Long)0L)
	temp_1 = FIX((SI_Long)0L);
    else if (FIXNUM_GT(y_in_view_pad,icon_height))
	temp_1 = icon_height;
    else
	temp_1 = y_in_view_pad;
    return VALUES_2(temp,temp_1);
}

/* CLIP-X-IN-WORKSPACE-TO-ENGINE */
Object clip_x_in_workspace_to_engine(x_in_workspace,engine,view_pad)
    Object x_in_workspace, engine, view_pad;
{
    Object min_x_view_pad_in_workspace, scale, value;
    SI_Long gensymed_symbol, unshifted_result, gensymed_symbol_1;
    SI_Long max_x_view_pad_in_workspace;

    x_note_fn_call(234,2);
    min_x_view_pad_in_workspace = ISVREF(view_pad,(SI_Long)5L);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = ISVREF(engine,(SI_Long)1L);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = IFIX(min_x_view_pad_in_workspace);
    max_x_view_pad_in_workspace = gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LE(x_in_workspace,min_x_view_pad_in_workspace))
	return VALUES_1(min_x_view_pad_in_workspace);
    else if (IFIX(x_in_workspace) >= max_x_view_pad_in_workspace)
	return VALUES_1(FIX(max_x_view_pad_in_workspace));
    else
	return VALUES_1(x_in_workspace);
}

/* CLIP-Y-IN-WORKSPACE-TO-ENGINE */
Object clip_y_in_workspace_to_engine(y_in_workspace,engine,view_pad)
    Object y_in_workspace, engine, view_pad;
{
    Object min_y_view_pad_in_workspace, scale, value;
    SI_Long gensymed_symbol, unshifted_result, gensymed_symbol_1;
    SI_Long max_y_view_pad_in_workspace;

    x_note_fn_call(234,3);
    min_y_view_pad_in_workspace = ISVREF(view_pad,(SI_Long)6L);
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = ISVREF(engine,(SI_Long)2L);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value));
    gensymed_symbol_1 = IFIX(min_y_view_pad_in_workspace);
    max_y_view_pad_in_workspace = gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LE(y_in_workspace,min_y_view_pad_in_workspace))
	return VALUES_1(min_y_view_pad_in_workspace);
    else if (IFIX(y_in_workspace) >= max_y_view_pad_in_workspace)
	return VALUES_1(FIX(max_y_view_pad_in_workspace));
    else
	return VALUES_1(y_in_workspace);
}

/* PUSH-ICON-EDITOR-TRANSLATOR-STATE-INFORMATION */
Object push_icon_editor_translator_state_information(translator,
	    new_state_information)
    Object translator, new_state_information;
{
    Object svref_new_value;

    x_note_fn_call(234,4);
    svref_new_value = icon_editor_cons_1(new_state_information,
	    ISVREF(translator,(SI_Long)2L));
    return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) = svref_new_value);
}

/* ENQUEUE-ICON-EDITOR-TRANSLATOR-STATE-INFORMATION */
Object enqueue_icon_editor_translator_state_information(translator,
	    new_state_information)
    Object translator, new_state_information;
{
    Object state_information_list, state_information, temp;

    x_note_fn_call(234,5);
    state_information_list = ISVREF(translator,(SI_Long)2L);
    if (state_information_list) {
	state_information = state_information_list;
      next_loop:
	if ( !TRUEP(state_information))
	    goto end_loop;
	if ( !TRUEP(CDR(state_information)))
	    goto end_loop;
	state_information = M_CDR(state_information);
	goto next_loop;
      end_loop:
	temp = icon_editor_cons_1(new_state_information,Nil);
	M_CDR(state_information) = temp;
	return VALUES_1(Qnil);
    }
    else {
	temp = icon_editor_cons_1(new_state_information,Nil);
	return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) = temp);
    }
}

/* CLEAR-ICON-EDITOR-TRANSLATOR-STATE-INFORMATION */
Object clear_icon_editor_translator_state_information(translator)
    Object translator;
{
    Object state_information_qm;

    x_note_fn_call(234,6);
    state_information_qm = ISVREF(translator,(SI_Long)2L);
    if (state_information_qm) {
	reclaim_icon_editor_slot_value(state_information_qm);
	return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* POP-ICON-EDITOR-TRANSLATOR-STATE-INFORMATION */
Object pop_icon_editor_translator_state_information(translator)
    Object translator;
{
    Object state_information_qm, popped_state_info, svref_new_value;

    x_note_fn_call(234,7);
    state_information_qm = ISVREF(translator,(SI_Long)2L);
    if (state_information_qm) {
	popped_state_info = FIRST(state_information_qm);
	svref_new_value = CDR(state_information_qm);
	SVREF(translator,FIX((SI_Long)2L)) = svref_new_value;
	reclaim_icon_editor_cons_1(state_information_qm);
	return VALUES_1(popped_state_info);
    }
    else
	return VALUES_1(Nil);
}

/* POP-LAST-MARKER-IF-DRAWN */
Object pop_last_marker_if_drawn(icon_editor,translator)
    Object icon_editor, translator;
{
    Object last_marker_drawn_qm;

    x_note_fn_call(234,8);
    last_marker_drawn_qm = ISVREF(translator,(SI_Long)3L);
    if (last_marker_drawn_qm &&  !EQ(last_marker_drawn_qm,Qspecial))
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)19L),Nil,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qarc;                /* arc */

/* COMPUTE-MAXIMUMS-AND-MINIMUMS-FOR-POINTS */
Object compute_maximums_and_minimums_for_points(list_of_points_or_arcs,
	    min_x,min_y,max_x,max_y)
    Object list_of_points_or_arcs, min_x, min_y, max_x, max_y;
{
    Object point_or_arc, ab_loop_list_, temp, thing, cdr_thing, car_thing;
    Object cadr_thing, x1, y1_1, min_x2, min_y2, max_x2, max_y2, temp_2;
    Object temp_3, temp_4;
    char temp_1;
    Object result;

    x_note_fn_call(234,9);
    point_or_arc = Nil;
    ab_loop_list_ = list_of_points_or_arcs;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point_or_arc = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(list_of_points_or_arcs) && EQ(M_CAR(list_of_points_or_arcs),
	    Qarc)) {
	temp = M_CDR(list_of_points_or_arcs);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(list_of_points_or_arcs))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(list_of_points_or_arcs));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	result = compute_maximums_and_minimums_for_points(CDR(point_or_arc),
		min_x,min_y,max_x,max_y);
	MVS_4(result,min_x,min_y,max_x,max_y);
    }
    else {
	cdr_thing = Nil;
	car_thing = Nil;
	cadr_thing = Nil;
	if (CONSP(point_or_arc)) {
	    cdr_thing = M_CDR(point_or_arc);
	    temp_1 = TRUEP(cdr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		!TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
	    car_thing = M_CAR(point_or_arc);
	    temp_1 = TRUEP(car_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cadr_thing = M_CAR(cdr_thing);
	    temp_1 = TRUEP(cadr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = (temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),Qplus) 
		|| SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : TRUEP(Nil);
	if (temp_1);
	else {
	    if (CONSP(point_or_arc)) {
		temp = M_CDR(point_or_arc);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = ((temp_1 ?  !TRUEP(M_CDR(M_CDR(point_or_arc))) : 
		    TRUEP(Nil)) ? FIXNUMP(M_CAR(point_or_arc)) : 
		    TRUEP(Nil)) ? FIXNUMP(M_CAR(M_CDR(point_or_arc))) : 
		    TRUEP(Nil);
	}
	if (temp_1) {
	    x1 = FIXNUMP(FIRST(point_or_arc)) ? FIRST(point_or_arc) : 
		    simple_eval_for_icon(FIRST(point_or_arc));
	    y1_1 = FIXNUMP(SECOND(point_or_arc)) ? SECOND(point_or_arc) : 
		    simple_eval_for_icon(SECOND(point_or_arc));
	    min_x2 = min_x;
	    min_y2 = min_y;
	    max_x2 = max_x;
	    max_y2 = max_y;
	    temp_2 = FIXNUM_MIN(x1,min_x2);
	    temp_3 = FIXNUM_MIN(y1_1,min_y2);
	    temp_4 = FIXNUM_MAX(x1,max_x2);
	    temp = FIXNUM_MAX(y1_1,max_y2);
	    result = VALUES_4(temp_2,temp_3,temp_4,temp);
	    MVS_4(result,min_x,min_y,max_x,max_y);
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_4(min_x,min_y,max_x,max_y);
}

static Object Qpoint;              /* point */

static Object Qoutline;            /* outline */

static Object Qsolid_rectangle;    /* solid-rectangle */

static Object Qfilled_circle;      /* filled-circle */

static Object Qimage;              /* image */

static Object Qtext;               /* text */

static Object Qlines;              /* lines */

static Object Qcircle;             /* circle */

static Object Qfilled_polygon;     /* filled-polygon */

/* COMPUTE-MAXIMUMS-AND-MINIMUMS-FOR-DRAWING-ELEMENTS */
Object compute_maximums_and_minimums_for_drawing_elements(drawing_elements,
	    variable_spec_list,min_x,min_y,max_x,max_y,icon_width,icon_height)
    Object drawing_elements, variable_spec_list, min_x, min_y, max_x, max_y;
    Object icon_width, icon_height;
{
    Object current_icon_untransformed_width, current_icon_untransformed_height;
    Object current_icon_variables_plist, current_icon_variables_override_plist;
    Object drawing_element, ab_loop_list_, temp, image_name, point_qm, x0;
    Object y0_1, image_data_qm, width, height, temp_1, temp_2, temp_3, x1;
    Object y1_1, min_x2, min_y2, max_x2, max_y2, left, top, right, bottom;
    Object point_1, point_2, point_3, temp_4, arc_min_x_qm, arc_min_y_qm;
    Object arc_max_x_qm, arc_max_y_qm, fixnum_x_center_qm, fixnum_y_center_qm;
    Object fixnum_radius_qm, triangle, ab_loop_list__1;
    Declare_special(4);
    Object result;

    x_note_fn_call(234,10);
    current_icon_untransformed_width = icon_width;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
	    3);
      current_icon_untransformed_height = icon_height;
      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
	      2);
	current_icon_variables_plist = variable_spec_list;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
		1);
	  current_icon_variables_override_plist = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
		  0);
	    drawing_element = Nil;
	    ab_loop_list_ = drawing_elements;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    drawing_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = CAR(drawing_element);
	    if (EQ(temp,Qpoint) || EQ(temp,Qoutline) || EQ(temp,
		    Qsolid_rectangle) || EQ(temp,Qfilled_circle)) {
		result = compute_maximums_and_minimums_for_points(CDR(drawing_element),
			min_x,min_y,max_x,max_y);
		MVS_4(result,min_x,min_y,max_x,max_y);
	    }
	    else if (EQ(temp,Qimage)) {
		image_name = simple_eval_for_icon(SECOND(drawing_element));
		point_qm = THIRD(drawing_element);
		x0 = point_qm ? (FIXNUMP(FIRST(point_qm)) ? 
			FIRST(point_qm) : 
			simple_eval_for_icon(FIRST(point_qm))) : 
			FIX((SI_Long)0L);
		y0_1 = point_qm ? (FIXNUMP(SECOND(point_qm)) ? 
			SECOND(point_qm) : 
			simple_eval_for_icon(SECOND(point_qm))) : 
			FIX((SI_Long)0L);
		image_data_qm = find_image_data(image_name);
		width = image_data_qm ? ISVREF(image_data_qm,(SI_Long)5L) :
			 FIX((SI_Long)0L);
		height = image_data_qm ? ISVREF(image_data_qm,(SI_Long)6L) 
			: FIX((SI_Long)0L);
		temp = FIXNUM_MIN(x0,min_x);
		temp_1 = FIXNUM_MIN(y0_1,min_y);
		temp_2 = FIXNUM_MAX(x0,max_x);
		temp_3 = FIXNUM_MAX(y0_1,max_y);
		min_x = temp;
		min_y = temp_1;
		max_x = temp_2;
		max_y = temp_3;
		x1 = FIXNUM_ADD(x0,width);
		y1_1 = FIXNUM_ADD(y0_1,height);
		min_x2 = min_x;
		min_y2 = min_y;
		max_x2 = max_x;
		max_y2 = max_y;
		temp_3 = FIXNUM_MIN(x1,min_x2);
		temp_2 = FIXNUM_MIN(y1_1,min_y2);
		temp_1 = FIXNUM_MAX(x1,max_x2);
		temp = FIXNUM_MAX(y1_1,max_y2);
		result = VALUES_4(temp_3,temp_2,temp_1,temp);
		MVS_4(result,min_x,min_y,max_x,max_y);
	    }
	    else if (EQ(temp,Qtext)) {
		result = compute_edges_for_text_drawing_element(drawing_element);
		MVS_4(result,left,top,right,bottom);
		temp = FIXNUM_MIN(left,min_x);
		temp_1 = FIXNUM_MIN(top,min_y);
		temp_2 = FIXNUM_MAX(left,max_x);
		temp_3 = FIXNUM_MAX(top,max_y);
		min_x = temp;
		min_y = temp_1;
		max_x = temp_2;
		max_y = temp_3;
		temp = FIXNUM_MIN(right,min_x);
		temp_1 = FIXNUM_MIN(bottom,min_y);
		temp_2 = FIXNUM_MAX(right,max_x);
		temp_3 = FIXNUM_MAX(bottom,max_y);
		min_x = temp;
		min_y = temp_1;
		max_x = temp_2;
		max_y = temp_3;
	    }
	    else if (EQ(temp,Qlines)) {
		temp = THIRD(drawing_element);
		if (EQ(FIRST(temp),Qarc) && IFIX(length(drawing_element)) 
			== (SI_Long)4L) {
		    point_1 = SECOND(drawing_element);
		    temp = THIRD(drawing_element);
		    point_2 = SECOND(temp);
		    point_3 = FOURTH(drawing_element);
		    temp_4 = FIXNUMP(FIRST(point_1)) ? FIRST(point_1) : 
			    simple_eval_for_icon(FIRST(point_1));
		    temp_3 = FIXNUMP(SECOND(point_1)) ? SECOND(point_1) : 
			    simple_eval_for_icon(SECOND(point_1));
		    temp_2 = FIXNUMP(FIRST(point_2)) ? FIRST(point_2) : 
			    simple_eval_for_icon(FIRST(point_2));
		    temp_1 = FIXNUMP(SECOND(point_2)) ? SECOND(point_2) : 
			    simple_eval_for_icon(SECOND(point_2));
		    temp = FIXNUMP(FIRST(point_3)) ? FIRST(point_3) : 
			    simple_eval_for_icon(FIRST(point_3));
		    result = compute_arc_bounding_box(temp_4,temp_3,temp_2,
			    temp_1,temp,FIXNUMP(SECOND(point_3)) ? 
			    SECOND(point_3) : 
			    simple_eval_for_icon(SECOND(point_3)));
		    MVS_4(result,arc_min_x_qm,arc_min_y_qm,arc_max_x_qm,
			    arc_max_y_qm);
		    if (arc_min_x_qm) {
			temp = FIXNUM_MIN(arc_min_x_qm,min_x);
			temp_1 = FIXNUM_MIN(arc_min_y_qm,min_y);
			temp_2 = FIXNUM_MAX(arc_min_x_qm,max_x);
			temp_3 = FIXNUM_MAX(arc_min_y_qm,max_y);
			min_x = temp;
			min_y = temp_1;
			max_x = temp_2;
			max_y = temp_3;
			temp = FIXNUM_MIN(arc_max_x_qm,min_x);
			temp_1 = FIXNUM_MIN(arc_max_y_qm,min_y);
			temp_2 = FIXNUM_MAX(arc_max_x_qm,max_x);
			temp_3 = FIXNUM_MAX(arc_max_y_qm,max_y);
			min_x = temp;
			min_y = temp_1;
			max_x = temp_2;
			max_y = temp_3;
		    }
		    else {
			result = compute_maximums_and_minimums_for_points(CDR(drawing_element),
				min_x,min_y,max_x,max_y);
			MVS_4(result,min_x,min_y,max_x,max_y);
		    }
		}
		else {
		    result = compute_maximums_and_minimums_for_points(CDR(drawing_element),
			    min_x,min_y,max_x,max_y);
		    MVS_4(result,min_x,min_y,max_x,max_y);
		}
	    }
	    else if (EQ(temp,Qcircle)) {
		point_1 = SECOND(drawing_element);
		point_2 = THIRD(drawing_element);
		point_3 = FOURTH(drawing_element);
		temp_4 = FIXNUMP(FIRST(point_1)) ? FIRST(point_1) : 
			simple_eval_for_icon(FIRST(point_1));
		temp_3 = FIXNUMP(SECOND(point_1)) ? SECOND(point_1) : 
			simple_eval_for_icon(SECOND(point_1));
		temp_2 = FIXNUMP(FIRST(point_2)) ? FIRST(point_2) : 
			simple_eval_for_icon(FIRST(point_2));
		temp_1 = FIXNUMP(SECOND(point_2)) ? SECOND(point_2) : 
			simple_eval_for_icon(SECOND(point_2));
		temp = FIXNUMP(FIRST(point_3)) ? FIRST(point_3) : 
			simple_eval_for_icon(FIRST(point_3));
		result = calculate_center_and_radius_of_circle(temp_4,
			temp_3,temp_2,temp_1,temp,FIXNUMP(SECOND(point_3)) 
			? SECOND(point_3) : 
			simple_eval_for_icon(SECOND(point_3)));
		MVS_3(result,fixnum_x_center_qm,fixnum_y_center_qm,
			fixnum_radius_qm);
		if (fixnum_radius_qm) {
		    x1 = FIXNUM_MINUS(fixnum_x_center_qm,fixnum_radius_qm);
		    y1_1 = FIXNUM_MINUS(fixnum_y_center_qm,fixnum_radius_qm);
		    min_x2 = min_x;
		    min_y2 = min_y;
		    max_x2 = max_x;
		    max_y2 = max_y;
		    temp_3 = FIXNUM_MIN(x1,min_x2);
		    temp_2 = FIXNUM_MIN(y1_1,min_y2);
		    temp_1 = FIXNUM_MAX(x1,max_x2);
		    temp = FIXNUM_MAX(y1_1,max_y2);
		    result = VALUES_4(temp_3,temp_2,temp_1,temp);
		    MVS_4(result,min_x,min_y,max_x,max_y);
		    x1 = FIXNUM_ADD(fixnum_x_center_qm,fixnum_radius_qm);
		    y1_1 = FIXNUM_ADD(fixnum_y_center_qm,fixnum_radius_qm);
		    min_x2 = min_x;
		    min_y2 = min_y;
		    max_x2 = max_x;
		    max_y2 = max_y;
		    temp_3 = FIXNUM_MIN(x1,min_x2);
		    temp_2 = FIXNUM_MIN(y1_1,min_y2);
		    temp_1 = FIXNUM_MAX(x1,max_x2);
		    temp = FIXNUM_MAX(y1_1,max_y2);
		    result = VALUES_4(temp_3,temp_2,temp_1,temp);
		    MVS_4(result,min_x,min_y,max_x,max_y);
		}
		else {
		    result = compute_maximums_and_minimums_for_points(CDR(drawing_element),
			    min_x,min_y,max_x,max_y);
		    MVS_4(result,min_x,min_y,max_x,max_y);
		}
	    }
	    else if (EQ(temp,Qfilled_polygon)) {
		result = compute_maximums_and_minimums_for_points(SECOND(drawing_element),
			min_x,min_y,max_x,max_y);
		MVS_4(result,min_x,min_y,max_x,max_y);
		triangle = Nil;
		ab_loop_list__1 = CDDR(drawing_element);
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		triangle = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		result = compute_maximums_and_minimums_for_points(triangle,
			min_x,min_y,max_x,max_y);
		MVS_4(result,min_x,min_y,max_x,max_y);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    goto next_loop;
	  end_loop:;
	    if (IFIX(min_x) < (SI_Long)0L)
		min_x = FIX((SI_Long)0L);
	    if (IFIX(min_y) < (SI_Long)0L)
		min_y = FIX((SI_Long)0L);
	    if (FIXNUM_GT(max_x,icon_width))
		max_x = icon_width;
	    if (FIXNUM_GT(max_y,icon_height))
		max_y = icon_height;
	    result = VALUES_4(min_x,min_y,max_x,max_y);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPUTE-MAXIMUM-AND-MINIMUM-BOUNDS-FOR-LAYER */
Object compute_maximum_and_minimum_bounds_for_layer(layer,
	    variable_spec_list,icon_width,icon_height)
    Object layer, variable_spec_list, icon_width, icon_height;
{
    Object temp, drawing_elements, icon_min_x, icon_min_y, icon_max_x;
    Object icon_max_y;
    Object result;

    x_note_fn_call(234,11);
    temp = CDDR(layer);
    drawing_elements = CAR(temp);
    icon_min_x = icon_width;
    icon_min_y = icon_height;
    icon_max_x = FIX((SI_Long)0L);
    icon_max_y = FIX((SI_Long)0L);
    if (drawing_elements) {
	result = compute_maximums_and_minimums_for_drawing_elements(drawing_elements,
		variable_spec_list,icon_min_x,icon_min_y,icon_max_x,
		icon_max_y,icon_width,icon_height);
	MVS_4(result,icon_min_x,icon_min_y,icon_max_x,icon_max_y);
	return VALUES_4(icon_min_x,icon_min_y,icon_max_x,icon_max_y);
    }
    else
	return VALUES_4(FIX((SI_Long)0L),FIX((SI_Long)0L),icon_width,
		icon_height);
}

static Object Qwhite;              /* white */

static Object Qtransparent;        /* transparent */

static Object Qforeground;         /* foreground */

static Object Qiconic_entity;      /* iconic-entity */

/* MAKE-ENTITY-WITH-ICON-DESCRIPTION-FOR-MOVING-LAYER */
Object make_entity_with_icon_description_for_moving_layer(icon_editor,
	    layer,icon_width_in_workspace_init,
	    icon_height_in_workspace_init,region_and_name_alist)
    Object icon_editor, layer, icon_width_in_workspace_init;
    Object icon_height_in_workspace_init, region_and_name_alist;
{
    Object view_pad, label_of_layer, color_of_layer, list_of_layers, entity;
    Object variable_spec_list, background_layer, stipple_spec;
    SI_Long icon_width_in_workspace, icon_height_in_workspace;

    x_note_fn_call(234,12);
    icon_width_in_workspace = IFIX(icon_width_in_workspace_init);
    icon_height_in_workspace = IFIX(icon_height_in_workspace_init);
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    label_of_layer = FIRST(layer);
    color_of_layer = get_color_of_region_in_icon_editor(icon_editor,
	    label_of_layer);
    list_of_layers = icon_editor_cons_1(layer,Nil);
    entity = Nil;
    variable_spec_list = ISVREF(icon_editor,(SI_Long)7L);
    background_layer = ISVREF(icon_editor,(SI_Long)8L);
    stipple_spec = ISVREF(icon_editor,(SI_Long)9L);
    if (EQ(color_of_layer,Qwhite) || EQ(color_of_layer,Qtransparent))
	M_FIRST(layer) = Qforeground;
    entity = make_entity_with_specific_icon_description(4,Qiconic_entity,
	    convert_list_of_layers_to_line_drawing_description(list_of_layers,
	    region_and_name_alist,variable_spec_list,background_layer,
	    FIX(icon_width_in_workspace),FIX(icon_height_in_workspace),
	    ISVREF(view_pad,(SI_Long)10L),ISVREF(view_pad,(SI_Long)11L),T,
	    T,stipple_spec),FIX(icon_width_in_workspace),
	    FIX(icon_height_in_workspace));
    reclaim_icon_editor_cons_1(list_of_layers);
    M_FIRST(layer) = label_of_layer;
    return VALUES_1(entity);
}

/* CREATE-AND-PLACE-ICON-OF-CURRENT-LAYER-FOR-VIEW-PAD */
Object create_and_place_icon_of_current_layer_for_view_pad(icon_editor,
	    layer,icon_width_init,icon_height_init,region_and_name_alist)
    Object icon_editor, layer, icon_width_init, icon_height_init;
    Object region_and_name_alist;
{
    Object view_pad, scale, color_of_layer, layer_icon, xored_layer_icon_qm;
    Object temp, variable_spec_list, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, icon_min_x, icon_min_y;
    Object icon_max_x, icon_max_y, value_1, inner_left_edge, inner_top_edge;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value_1;
    SI_Long icon_width, icon_height, value, icon_width_in_workspace;
    SI_Long unshifted_result, icon_height_in_workspace, gensymed_symbol;
    SI_Long gensymed_symbol_1, min_x_in_workspace, min_y_in_workspace;
    SI_Long max_x_in_workspace, max_y_in_workspace, inner_right_edge;
    SI_Long inner_bottom_edge;
    SI_Long left_edge_of_icon_to_right_edge_of_layer_in_workspace;
    SI_Long top_edge_of_icon_to_bottom_edge_of_layer_in_workspace;
    SI_Long left_edge_of_icon_to_left_edge_of_layer_in_workspace;
    SI_Long top_edge_of_icon_to_top_edge_of_layer_in_workspace;
    SI_Long svref_new_value;
    Declare_special(4);
    Object result;

    x_note_fn_call(234,13);
    icon_width = IFIX(icon_width_init);
    icon_height = IFIX(icon_height_init);
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    delete_icon_editor_view_pad_icon_for_current_layer(view_pad);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = icon_width;
    if (IFIX(scale) == (SI_Long)4096L)
	icon_width_in_workspace = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	icon_width_in_workspace = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	icon_width_in_workspace = IFIX(scalef_function(scale,FIX(value)));
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = icon_height;
    if (IFIX(scale) == (SI_Long)4096L)
	icon_height_in_workspace = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	icon_height_in_workspace = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	icon_height_in_workspace = IFIX(scalef_function(scale,FIX(value)));
    color_of_layer = get_color_of_region_in_icon_editor(icon_editor,
	    FIRST(layer));
    layer_icon = 
	    make_entity_with_icon_description_for_moving_layer(icon_editor,
	    layer,FIX(icon_width_in_workspace),
	    FIX(icon_height_in_workspace),region_and_name_alist);
    xored_layer_icon_qm =  !(EQ(color_of_layer,Qwhite) || 
	    EQ(color_of_layer,Qtransparent)) ? 
	    make_entity_with_icon_description_for_moving_layer(icon_editor,
	    layer,FIX(icon_width_in_workspace),
	    FIX(icon_height_in_workspace),region_and_name_alist) : Nil;
    temp = ISVREF(icon_editor,(SI_Long)7L);
    variable_spec_list = CDR(temp);
    current_icon_untransformed_width = FIX(icon_width);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
	    3);
      current_icon_untransformed_height = FIX(icon_height);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
	      2);
	current_icon_variables_plist = variable_spec_list;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
		1);
	  current_icon_variables_override_plist = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
		  0);
	    result = compute_maximum_and_minimum_bounds_for_layer(layer,
		    variable_spec_list,FIX(icon_width),FIX(icon_height));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    MVS_4(result,icon_min_x,icon_min_y,icon_max_x,icon_max_y);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value_1 = icon_min_x;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value_1) && 
	    FIXNUM_LT(value_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value_1)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value_1));
    gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)5L));
    min_x_in_workspace = gensymed_symbol + gensymed_symbol_1;
    scale = ISVREF(view_pad,(SI_Long)11L);
    value_1 = icon_min_y;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value_1) && 
	    FIXNUM_LT(value_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value_1)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value_1));
    gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)6L));
    min_y_in_workspace = gensymed_symbol + gensymed_symbol_1;
    scale = ISVREF(view_pad,(SI_Long)10L);
    value_1 = icon_max_x;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value_1) && 
	    FIXNUM_LT(value_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value_1)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value_1));
    gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)5L));
    max_x_in_workspace = gensymed_symbol + gensymed_symbol_1;
    scale = ISVREF(view_pad,(SI_Long)11L);
    value_1 = icon_max_y;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value_1) && 
	    FIXNUM_LT(value_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value_1)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(scale,value_1));
    gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)6L));
    max_y_in_workspace = gensymed_symbol + gensymed_symbol_1;
    inner_left_edge = ISVREF(view_pad,(SI_Long)5L);
    gensymed_symbol = IFIX(inner_left_edge);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = icon_width;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
    inner_right_edge = gensymed_symbol + gensymed_symbol_1;
    inner_top_edge = ISVREF(view_pad,(SI_Long)6L);
    gensymed_symbol = IFIX(inner_top_edge);
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = icon_height;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
    inner_bottom_edge = gensymed_symbol + gensymed_symbol_1;
    left_edge_of_icon_to_right_edge_of_layer_in_workspace = 
	    max_x_in_workspace - IFIX(inner_left_edge);
    top_edge_of_icon_to_bottom_edge_of_layer_in_workspace = 
	    max_y_in_workspace - IFIX(inner_top_edge);
    left_edge_of_icon_to_left_edge_of_layer_in_workspace = 
	    min_x_in_workspace - IFIX(inner_left_edge);
    top_edge_of_icon_to_top_edge_of_layer_in_workspace = 
	    min_y_in_workspace - IFIX(inner_top_edge);
    svref_new_value = IFIX(inner_left_edge) - 
	    left_edge_of_icon_to_right_edge_of_layer_in_workspace + 
	    (SI_Long)1L;
    ISVREF(view_pad,(SI_Long)18L) = FIX(svref_new_value);
    svref_new_value = IFIX(inner_top_edge) - 
	    top_edge_of_icon_to_bottom_edge_of_layer_in_workspace + 
	    (SI_Long)1L;
    ISVREF(view_pad,(SI_Long)19L) = FIX(svref_new_value);
    svref_new_value = inner_right_edge - (SI_Long)1L - 
	    left_edge_of_icon_to_left_edge_of_layer_in_workspace;
    ISVREF(view_pad,(SI_Long)20L) = FIX(svref_new_value);
    svref_new_value = inner_bottom_edge - (SI_Long)1L - 
	    top_edge_of_icon_to_top_edge_of_layer_in_workspace;
    ISVREF(view_pad,(SI_Long)21L) = FIX(svref_new_value);
    SVREF(view_pad,FIX((SI_Long)16L)) = layer_icon;
    frame_serial_number_setf_arg = Current_frame_serial_number;
    old = ISVREF(view_pad,(SI_Long)17L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value_1 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) 
	    ||  !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(view_pad,FIX((SI_Long)17L)) = svref_new_value_1;
    if (xored_layer_icon_qm) {
	SVREF(view_pad,FIX((SI_Long)15L)) = xored_layer_icon_qm;
	add_to_workspace(5,xored_layer_icon_qm,ISVREF(view_pad,
		(SI_Long)9L),ISVREF(view_pad,(SI_Long)5L),ISVREF(view_pad,
		(SI_Long)6L),T);
    }
    return add_to_workspace(5,layer_icon,ISVREF(view_pad,(SI_Long)9L),
	    ISVREF(view_pad,(SI_Long)5L),ISVREF(view_pad,(SI_Long)6L),T);
}

/* COMPUTE-BOUNDED-POINT-IN-WORKSPACE */
Object compute_bounded_point_in_workspace(cursor_x_in_workspace,
	    cursor_y_in_workspace,view_pad,cursor_x_offset,cursor_y_offset)
    Object cursor_x_in_workspace, cursor_y_in_workspace, view_pad;
    Object cursor_x_offset, cursor_y_offset;
{
    Object x_in_workspace, y_in_workspace, temp, temp_1;

    x_note_fn_call(234,14);
    x_in_workspace = FIXNUM_MINUS(cursor_x_in_workspace,cursor_x_offset);
    y_in_workspace = FIXNUM_MINUS(cursor_y_in_workspace,cursor_y_offset);
    if (FIXNUM_LT(x_in_workspace,ISVREF(view_pad,(SI_Long)18L)))
	temp = FIXNUM_ADD(ISVREF(view_pad,(SI_Long)18L),cursor_x_offset);
    else if (FIXNUM_GT(x_in_workspace,ISVREF(view_pad,(SI_Long)20L)))
	temp = FIXNUM_ADD(ISVREF(view_pad,(SI_Long)20L),cursor_x_offset);
    else
	temp = cursor_x_in_workspace;
    if (FIXNUM_LT(y_in_workspace,ISVREF(view_pad,(SI_Long)19L)))
	temp_1 = FIXNUM_ADD(ISVREF(view_pad,(SI_Long)19L),cursor_y_offset);
    else if (FIXNUM_GT(y_in_workspace,ISVREF(view_pad,(SI_Long)21L)))
	temp_1 = FIXNUM_ADD(ISVREF(view_pad,(SI_Long)21L),cursor_y_offset);
    else
	temp_1 = cursor_y_in_workspace;
    return VALUES_2(temp,temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Distance_to_snap_points_together_in_view_pad, Qdistance_to_snap_points_together_in_view_pad);

static Object array_constant;      /* # */

/* HANDLE-MOVE-LAYER-IN-XY-PLANE-IN-TRANSLATOR */
Object handle_move_layer_in_xy_plane_in_translator(icon_editor,translator)
    Object icon_editor, translator;
{
    Object temp, drawing_elements;

    x_note_fn_call(234,15);
    temp = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)6L);
    temp = CDDR(temp);
    drawing_elements = CAR(temp);
    if (drawing_elements) {
	delete_icon_editor_view_pad_icon_for_current_layer(ISVREF(icon_editor,
		(SI_Long)12L));
	ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)17L);
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)3L),FIX((SI_Long)17L),Nil);
    }
    else
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)3L),
		copy_constant_wide_string_given_length(array_constant,
		FIX((SI_Long)30L)),Nil);
}

/* HANDLE-TRANSLATOR-VIEW-PAD-MOUSE-DOWN-EVENT */
Object handle_translator_view_pad_mouse_down_event(x_in_workspace,
	    y_in_workspace,icon_editor,translator,state_1,state_information_qm)
    Object x_in_workspace, y_in_workspace, icon_editor, translator, state_1;
    Object state_information_qm;
{
    Object view_pad, engine, scale, value, x_in_view_pad, temp, y_in_view_pad;
    Object point, ab_loop_list_, ab_loop_it_, x0_in_view_pad_1;
    Object y0_in_view_pad_1, x1_in_view_pad, y1_in_view_pad, d1, d2;
    Object current_layer;
    SI_Long temp_1, x0_in_view_pad, y0_in_view_pad, radius_in_view_pad;
    char temp_2;
    Object result;

    x_note_fn_call(234,16);
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = FIXNUM_MINUS(x_in_workspace,ISVREF(view_pad,(SI_Long)5L));
    if (IFIX(scale) == (SI_Long)4096L)
	x_in_view_pad = value;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	x_in_view_pad = inverse_scalef_function(scale,value);
    else if (IFIX(value) >= (SI_Long)0L) {
	temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	x_in_view_pad = temp;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	x_in_view_pad = temp;
    }
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = FIXNUM_MINUS(y_in_workspace,ISVREF(view_pad,(SI_Long)6L));
    if (IFIX(scale) == (SI_Long)4096L)
	y_in_view_pad = value;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	y_in_view_pad = inverse_scalef_function(scale,value);
    else if (IFIX(value) >= (SI_Long)0L) {
	temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	y_in_view_pad = temp;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	y_in_view_pad = temp;
    }
    temp = state_1;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 3:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad))
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)32L),x_in_view_pad,y_in_view_pad,Nil,Nil);
	    else
		return VALUES_1(Nil);
	  case 4:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		point = Nil;
		ab_loop_list_ = state_information_qm;
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		point = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_it_ = FIXNUM_EQ(CAR(point),x_in_view_pad) ? 
			(FIXNUM_EQ(CDR(point),y_in_view_pad) ? T : Nil) : Qnil;
		if (ab_loop_it_) {
		    temp_2 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_2 = TRUEP(Qnil);
	      end_1:;
		temp_2 =  !temp_2;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)13L),x_in_view_pad,y_in_view_pad);
		return push_icon_editor_translator_state_information(translator,
			icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
	    }
	    else
		return VALUES_1(Nil);
	  case 5:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		if (state_information_qm) {
		    temp = FIRST(state_information_qm);
		    x0_in_view_pad = IFIX(CAR(temp));
		    temp = FIRST(state_information_qm);
		    y0_in_view_pad = IFIX(CDR(temp));
		    SVREF(translator,FIX((SI_Long)2L)) = Nil;
		    reclaim_icon_editor_tree_1(state_information_qm);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)20L),Nil,Nil);
		    return enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)34L),FIX(x0_in_view_pad),
			    FIX(y0_in_view_pad),x_in_view_pad,y_in_view_pad);
		}
		else {
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    SVREF(translator,FIX((SI_Long)3L)) = T;
		    return push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		}
	    }
	    else
		return VALUES_1(Nil);
	  case 6:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		if (state_information_qm) {
		    pop_last_marker_if_drawn(icon_editor,translator);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)15L),
			    copy_list_using_icon_editor_conses_1(FIRST(state_information_qm)),
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    SVREF(translator,FIX((SI_Long)3L)) = T;
		    return push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		}
		else {
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    SVREF(translator,FIX((SI_Long)3L)) = T;
		    return push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		}
	    }
	    else
		return VALUES_1(Nil);
	  case 7:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		if (state_information_qm) {
		    if (SECOND(state_information_qm)) {
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)20L),Nil,Nil);
			enqueue_icon_editor_engine_event(icon_editor,
				FIX((SI_Long)36L),
				FIRST(state_information_qm),
				SECOND(state_information_qm),
				icon_editor_cons_1(x_in_view_pad,
				y_in_view_pad),Nil);
			reclaim_icon_editor_cons_1(state_information_qm);
			return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) 
				= Nil);
		    }
		    else {
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
			return enqueue_icon_editor_translator_state_information(translator,
				icon_editor_cons_1(x_in_view_pad,
				y_in_view_pad));
		    }
		}
		else {
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    return enqueue_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		}
	    }
	    else
		return VALUES_1(Nil);
	  case 8:
	  case 11:
	    if (state_information_qm) {
		result = snap_to_limits_of_width_and_height_if_necessary(x_in_view_pad,
			y_in_view_pad,ISVREF(engine,(SI_Long)1L),
			ISVREF(engine,(SI_Long)2L));
		MVS_2(result,x_in_view_pad,y_in_view_pad);
		temp = FIRST(state_information_qm);
		x0_in_view_pad_1 = CAR(temp);
		temp = FIRST(state_information_qm);
		y0_in_view_pad_1 = CDR(temp);
		x1_in_view_pad = x_in_view_pad;
		y1_in_view_pad = y_in_view_pad;
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)20L),Nil,Nil);
		enqueue_icon_editor_engine_event(icon_editor,IFIX(state_1) 
			== (SI_Long)8L ? FIX((SI_Long)37L) : 
			FIX((SI_Long)40L),x0_in_view_pad_1,
			y0_in_view_pad_1,x1_in_view_pad,y1_in_view_pad);
		reclaim_icon_editor_slot_value(state_information_qm);
		return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) = Nil);
	    }
	    else if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		return push_icon_editor_translator_state_information(translator,
			icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
	    }
	    else
		return VALUES_1(Nil);
	  case 10:
	  case 13:
	    if (state_information_qm) {
		temp = FIRST(state_information_qm);
		x0_in_view_pad_1 = CAR(temp);
		temp = FIRST(state_information_qm);
		y0_in_view_pad_1 = CDR(temp);
		x1_in_view_pad = x_in_view_pad;
		y1_in_view_pad = y_in_view_pad;
		d1 = FIXNUM_MINUS(x1_in_view_pad,x0_in_view_pad_1);
		d2 = FIXNUM_MINUS(y1_in_view_pad,y0_in_view_pad_1);
		radius_in_view_pad = IFIX(isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,
			d1),FIXNUM_TIMES(d2,d2))));
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)20L),Nil,Nil);
		enqueue_icon_editor_engine_event(icon_editor,IFIX(state_1) 
			== (SI_Long)10L ? FIX((SI_Long)39L) : 
			FIX((SI_Long)42L),x0_in_view_pad_1,
			y0_in_view_pad_1,FIX(radius_in_view_pad),Nil);
		reclaim_icon_editor_slot_value(state_information_qm);
		return VALUES_1(SVREF(translator,FIX((SI_Long)2L)) = Nil);
	    }
	    else if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		return push_icon_editor_translator_state_information(translator,
			icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
	    }
	    else
		return VALUES_1(Nil);
	  case 9:
	  case 12:
	  case 15:
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		if (state_information_qm) {
		    if (EQ(FIRST(state_information_qm),T)) {
			state_information_qm = CDR(state_information_qm);
			pop_icon_editor_translator_state_information(translator);
			return translator_end_current_state(5,icon_editor,
				translator,state_1,state_information_qm,T);
		    }
		    else {
			pop_last_marker_if_drawn(icon_editor,translator);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)15L),
				copy_list_using_icon_editor_conses_1(FIRST(state_information_qm)),
				icon_editor_cons_1(x_in_view_pad,
				y_in_view_pad));
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
			SVREF(translator,FIX((SI_Long)3L)) = T;
			return push_icon_editor_translator_state_information(translator,
				icon_editor_cons_1(x_in_view_pad,
				y_in_view_pad));
		    }
		}
		else {
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)14L),x_in_view_pad,y_in_view_pad);
		    SVREF(translator,FIX((SI_Long)3L)) = T;
		    return push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_view_pad,y_in_view_pad));
		}
	    }
	    else
		return VALUES_1(Nil);
	  case 17:
	    if (IFIX(state_1) == (SI_Long)0L)
		handle_move_layer_in_xy_plane_in_translator(icon_editor,
			translator);
	    else
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)17L),Nil);
	    if (point_in_draw_area_of_view_pad_p(x_in_workspace,
		    y_in_workspace,engine,view_pad)) {
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		current_layer = ISVREF(engine,(SI_Long)6L);
		if ( !TRUEP(state_information_qm)) {
		    push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(FIXNUM_MINUS(x_in_workspace,
			    ISVREF(view_pad,(SI_Long)5L)),
			    FIXNUM_MINUS(y_in_workspace,ISVREF(view_pad,
			    (SI_Long)6L))));
		    push_icon_editor_translator_state_information(translator,
			    icon_editor_cons_1(x_in_workspace,y_in_workspace));
		}
		return create_and_place_icon_of_current_layer_for_view_pad(icon_editor,
			current_layer,ISVREF(engine,(SI_Long)1L),
			ISVREF(engine,(SI_Long)2L),ISVREF(icon_editor,
			(SI_Long)6L));
	    }
	    else
		return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

/* TRANSLATOR-END-MOVING-LAYER-IN-XY-PLANE */
Object translator_end_moving_layer_in_xy_plane(icon_editor,translator,
	    state_information_qm)
    Object icon_editor, translator, state_information_qm;
{
    Object view_pad, new_coord, offset_coord, x_offset_in_workspace;
    Object y_offset_in_workspace, new_x_in_workspace, new_y_in_workspace;
    Object new_delta_x_in_workspace, new_delta_y_in_workspace, scale, value;
    Object temp, temp_2;
    SI_Long temp_1;
    Object result;

    x_note_fn_call(234,17);
    delete_icon_editor_view_pad_icon_for_current_layer(ISVREF(icon_editor,
	    (SI_Long)12L));
    if (CDR(state_information_qm)) {
	view_pad = ISVREF(icon_editor,(SI_Long)12L);
	new_coord = FIRST(state_information_qm);
	offset_coord = SECOND(state_information_qm);
	x_offset_in_workspace = CAR(offset_coord);
	y_offset_in_workspace = CDR(offset_coord);
	result = compute_bounded_point_in_workspace(CAR(new_coord),
		CDR(new_coord),view_pad,x_offset_in_workspace,
		y_offset_in_workspace);
	MVS_2(result,new_x_in_workspace,new_y_in_workspace);
	new_delta_x_in_workspace = FIXNUM_MINUS(new_x_in_workspace,
		ISVREF(view_pad,(SI_Long)5L));
	new_delta_y_in_workspace = FIXNUM_MINUS(new_y_in_workspace,
		ISVREF(view_pad,(SI_Long)6L));
	if (FIXNUM_NE(new_delta_x_in_workspace,x_offset_in_workspace) || 
		FIXNUM_NE(new_delta_y_in_workspace,y_offset_in_workspace)) {
	    scale = ISVREF(view_pad,(SI_Long)10L);
	    value = FIXNUM_MINUS(new_delta_x_in_workspace,
		    x_offset_in_workspace);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp = value;
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
		temp = inverse_scalef_function(scale,value);
	    else if (IFIX(value) >= (SI_Long)0L)
		temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			>>  -  - (SI_Long)1L)) / IFIX(scale));
	    else {
		temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		temp = FIXNUM_NEGATE(FIX(temp_1));
	    }
	    scale = ISVREF(view_pad,(SI_Long)11L);
	    value = FIXNUM_MINUS(new_delta_y_in_workspace,
		    y_offset_in_workspace);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_2 = value;
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
		temp_2 = inverse_scalef_function(scale,value);
	    else if (IFIX(value) >= (SI_Long)0L)
		temp_2 = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			>>  -  - (SI_Long)1L)) / IFIX(scale));
	    else {
		temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		temp_2 = FIXNUM_NEGATE(FIX(temp_1));
	    }
	    enqueue_icon_editor_engine_event(icon_editor,FIX((SI_Long)56L),
		    temp,temp_2,Nil,Nil);
	}
    }
    return clear_icon_editor_translator_state_information(translator);
}

/* ENQUEUE-ICON-EDITOR-TRANSLATOR-EVENT */
Object enqueue_icon_editor_translator_event(icon_editor,translator_event,
	    arg_1_qm,arg_2_qm)
    Object icon_editor, translator_event, arg_1_qm, arg_2_qm;
{
    Object translator, state_1, state_information_qm, temp, view_pad, engine;
    Object scale, value, temp_2, x0_in_view_pad, y0_in_view_pad;
    Object point_in_view_pad_qm, x_in_workspace, x1_in_view_pad;
    Object y_in_workspace, y1_in_view_pad, first_point, xn_in_view_pad;
    Object yn_in_view_pad, x2_in_view_pad, y2_in_view_pad, d1, d2, new_width;
    Object new_height, new_coord;
    SI_Long temp_1, radius_in_view_pad, unshifted_result, gensymed_symbol;
    SI_Long gensymed_symbol_1, scale_1;
    char temp_3;

    x_note_fn_call(234,18);
    translator = ISVREF(icon_editor,(SI_Long)10L);
    state_1 = ISVREF(translator,(SI_Long)1L);
    if (IFIX(state_1) != (SI_Long)18L || 
	    handle_layers_pad_translator_event(icon_editor,
	    translator_event,arg_1_qm,arg_2_qm)) {
	state_information_qm = ISVREF(translator,(SI_Long)2L);
	temp = translator_event;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    return VALUES_1(Nil);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = FIXNUM_MINUS(arg_1_qm,ISVREF(view_pad,(SI_Long)5L));
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = value;
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    temp = inverse_scalef_function(scale,value);
		else if (IFIX(value) >= (SI_Long)0L)
		    temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		else {
		    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp = FIXNUM_NEGATE(FIX(temp_1));
		}
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = FIXNUM_MINUS(arg_2_qm,ISVREF(view_pad,(SI_Long)6L));
		if (IFIX(scale) == (SI_Long)4096L)
		    temp_2 = value;
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    temp_2 = inverse_scalef_function(scale,value);
		else if (IFIX(value) >= (SI_Long)0L)
		    temp_2 = FIX(((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		else {
		    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp_2 = FIXNUM_NEGATE(FIX(temp_1));
		}
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)10L),temp,temp_2);
		temp = state_1;
		if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    return VALUES_1(Nil);
		else
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 5:
		      case 6:
			if (state_information_qm) {
			    temp = FIRST(state_information_qm);
			    x0_in_view_pad = CAR(temp);
			    temp = FIRST(state_information_qm);
			    y0_in_view_pad = CDR(temp);
			    point_in_view_pad_qm = 
				    point_in_draw_area_of_view_pad_p(arg_1_qm,
				    arg_2_qm,engine,view_pad);
			    x_in_workspace = 
				    clip_x_in_workspace_to_engine(arg_1_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)10L);
			    value = FIXNUM_MINUS(x_in_workspace,
				    ISVREF(view_pad,(SI_Long)5L));
			    if (IFIX(scale) == (SI_Long)4096L)
				x1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				x1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				x1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				x1_in_view_pad = temp;
			    }
			    y_in_workspace = 
				    clip_y_in_workspace_to_engine(arg_2_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)11L);
			    value = FIXNUM_MINUS(y_in_workspace,
				    ISVREF(view_pad,(SI_Long)6L));
			    if (IFIX(scale) == (SI_Long)4096L)
				y1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				y1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				y1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				y1_in_view_pad = temp;
			    }
			    pop_last_marker_if_drawn(icon_editor,translator);
			    if (point_in_view_pad_qm) {
				handle_icon_editor_visual_event(icon_editor,
					FIX((SI_Long)15L),
					icon_editor_cons_1(x0_in_view_pad,
					y0_in_view_pad),
					icon_editor_cons_1(x1_in_view_pad,
					y1_in_view_pad));
				return VALUES_1(SVREF(translator,
					FIX((SI_Long)3L)) = T);
			    }
			    else
				return VALUES_1(SVREF(translator,
					FIX((SI_Long)3L)) = Nil);
			}
			else
			    return VALUES_1(Nil);
		      case 9:
		      case 12:
		      case 15:
			if (state_information_qm) {
			    if (EQ(FIRST(state_information_qm),T)) {
				pop_last_marker_if_drawn(icon_editor,
					translator);
				state_information_qm = 
					CDR(state_information_qm);
				pop_icon_editor_translator_state_information(translator);
			    }
			    temp = FIRST(state_information_qm);
			    x0_in_view_pad = CAR(temp);
			    temp = FIRST(state_information_qm);
			    y0_in_view_pad = CDR(temp);
			    point_in_view_pad_qm = 
				    point_in_draw_area_of_view_pad_p(arg_1_qm,
				    arg_2_qm,engine,view_pad);
			    x_in_workspace = 
				    clip_x_in_workspace_to_engine(arg_1_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)10L);
			    value = FIXNUM_MINUS(x_in_workspace,
				    ISVREF(view_pad,(SI_Long)5L));
			    if (IFIX(scale) == (SI_Long)4096L)
				x1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				x1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				x1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				x1_in_view_pad = temp;
			    }
			    y_in_workspace = 
				    clip_y_in_workspace_to_engine(arg_2_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)11L);
			    value = FIXNUM_MINUS(y_in_workspace,
				    ISVREF(view_pad,(SI_Long)6L));
			    if (IFIX(scale) == (SI_Long)4096L)
				y1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				y1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				y1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				y1_in_view_pad = temp;
			    }
			    if (point_in_view_pad_qm ||  
				    !TRUEP(point_in_view_pad_qm) &&  
				    !EQ(ISVREF(translator,(SI_Long)3L),
				    Qspecial))
				handle_icon_editor_visual_event(icon_editor,
					FIX((SI_Long)19L),Nil,Nil);
			    if (point_in_view_pad_qm) {
				if (ISVREF(icon_editor,(SI_Long)25L)) {
				    temp = last(state_information_qm,_);
				    first_point = FIRST(temp);
				    xn_in_view_pad = CAR(first_point);
				    yn_in_view_pad = CDR(first_point);
				    temp = FIXNUM_MINUS(xn_in_view_pad,
					    x1_in_view_pad);
				    if (FIXNUM_LE(FIXNUM_ABS(temp),
					    Distance_to_snap_points_together_in_view_pad)) 
						{
					temp = FIXNUM_MINUS(yn_in_view_pad,
						y1_in_view_pad);
					temp_3 = 
						FIXNUM_LE(FIXNUM_ABS(temp),
						Distance_to_snap_points_together_in_view_pad);
				    }
				    else
					temp_3 = TRUEP(Nil);
				    if (temp_3) {
					x1_in_view_pad = xn_in_view_pad;
					y1_in_view_pad = yn_in_view_pad;
					push_icon_editor_translator_state_information(translator,
						T);
					handle_icon_editor_visual_event(icon_editor,
						FIX((SI_Long)14L),
						x1_in_view_pad,y1_in_view_pad);
				    }
				}
				handle_icon_editor_visual_event(icon_editor,
					FIX((SI_Long)15L),
					icon_editor_cons_1(x0_in_view_pad,
					y0_in_view_pad),
					icon_editor_cons_1(x1_in_view_pad,
					y1_in_view_pad));
				return VALUES_1(SVREF(translator,
					FIX((SI_Long)3L)) = T);
			    }
			    else if ( !EQ(ISVREF(translator,(SI_Long)3L),
				    Qspecial)) {
				if ( !TRUEP(CDR(state_information_qm)) || 
					CDDR(state_information_qm)) {
				    temp = last(state_information_qm,_);
				    first_point = FIRST(temp);
				}
				else
				    first_point = FIRST(state_information_qm);
				xn_in_view_pad = CAR(first_point);
				yn_in_view_pad = CDR(first_point);
				handle_icon_editor_visual_event(icon_editor,
					FIX((SI_Long)15L),
					icon_editor_cons_1(x0_in_view_pad,
					y0_in_view_pad),
					icon_editor_cons_1(xn_in_view_pad,
					yn_in_view_pad));
				return VALUES_1(SVREF(translator,
					FIX((SI_Long)3L)) = Qspecial);
			    }
			    else
				return VALUES_1(Nil);
			}
			else
			    return VALUES_1(Nil);
		      case 7:
			if (SECOND(state_information_qm)) {
			    temp = FIRST(state_information_qm);
			    x0_in_view_pad = CAR(temp);
			    temp = FIRST(state_information_qm);
			    y0_in_view_pad = CDR(temp);
			    temp = SECOND(state_information_qm);
			    x1_in_view_pad = CAR(temp);
			    temp = SECOND(state_information_qm);
			    y1_in_view_pad = CDR(temp);
			    x_in_workspace = 
				    clip_x_in_workspace_to_engine(arg_1_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)10L);
			    value = FIXNUM_MINUS(x_in_workspace,
				    ISVREF(view_pad,(SI_Long)5L));
			    if (IFIX(scale) == (SI_Long)4096L)
				x2_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				x2_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				x2_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				x2_in_view_pad = temp;
			    }
			    y_in_workspace = 
				    clip_y_in_workspace_to_engine(arg_2_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)11L);
			    value = FIXNUM_MINUS(y_in_workspace,
				    ISVREF(view_pad,(SI_Long)6L));
			    if (IFIX(scale) == (SI_Long)4096L)
				y2_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				y2_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				y2_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				y2_in_view_pad = temp;
			    }
			    handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)19L),Nil,Nil);
			    return handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)18L),
				    icon_editor_list_2(icon_editor_cons_1(x0_in_view_pad,
				    y0_in_view_pad),
				    icon_editor_cons_1(x1_in_view_pad,
				    y1_in_view_pad)),
				    icon_editor_cons_1(x2_in_view_pad,
				    y2_in_view_pad));
			}
			else
			    return VALUES_1(Nil);
		      case 8:
		      case 11:
		      case 14:
			if (state_information_qm) {
			    temp = FIRST(state_information_qm);
			    x0_in_view_pad = CAR(temp);
			    temp = FIRST(state_information_qm);
			    y0_in_view_pad = CDR(temp);
			    x_in_workspace = 
				    clip_x_in_workspace_to_engine(arg_1_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)10L);
			    value = FIXNUM_MINUS(x_in_workspace,
				    ISVREF(view_pad,(SI_Long)5L));
			    if (IFIX(scale) == (SI_Long)4096L)
				x1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				x1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				x1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				x1_in_view_pad = temp;
			    }
			    y_in_workspace = 
				    clip_y_in_workspace_to_engine(arg_2_qm,
				    engine,view_pad);
			    scale = ISVREF(view_pad,(SI_Long)11L);
			    value = FIXNUM_MINUS(y_in_workspace,
				    ISVREF(view_pad,(SI_Long)6L));
			    if (IFIX(scale) == (SI_Long)4096L)
				y1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				y1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				y1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				y1_in_view_pad = temp;
			    }
			    handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)19L),Nil,Nil);
			    return handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)16L),
				    icon_editor_cons_1(x0_in_view_pad,
				    y0_in_view_pad),
				    icon_editor_cons_1(x1_in_view_pad,
				    y1_in_view_pad));
			}
			else
			    return VALUES_1(Nil);
		      case 10:
		      case 13:
		      case 16:
			if (state_information_qm) {
			    temp = FIRST(state_information_qm);
			    x0_in_view_pad = CAR(temp);
			    temp = FIRST(state_information_qm);
			    y0_in_view_pad = CDR(temp);
			    scale = ISVREF(view_pad,(SI_Long)10L);
			    value = FIXNUM_MINUS(arg_1_qm,ISVREF(view_pad,
				    (SI_Long)5L));
			    if (IFIX(scale) == (SI_Long)4096L)
				x1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				x1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				x1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				x1_in_view_pad = temp;
			    }
			    scale = ISVREF(view_pad,(SI_Long)11L);
			    value = FIXNUM_MINUS(arg_2_qm,ISVREF(view_pad,
				    (SI_Long)6L));
			    if (IFIX(scale) == (SI_Long)4096L)
				y1_in_view_pad = value;
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				y1_in_view_pad = 
					inverse_scalef_function(scale,value);
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp = FIX(((IFIX(value) << (SI_Long)12L) 
					+ (IFIX(scale) >>  -  - 
					(SI_Long)1L)) / IFIX(scale));
				y1_in_view_pad = temp;
			    }
			    else {
				temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale) >>  - 
					 - (SI_Long)1L)) / IFIX(scale);
				temp = FIXNUM_NEGATE(FIX(temp_1));
				y1_in_view_pad = temp;
			    }
			    d1 = FIXNUM_MINUS(x1_in_view_pad,x0_in_view_pad);
			    d2 = FIXNUM_MINUS(y1_in_view_pad,y0_in_view_pad);
			    radius_in_view_pad = 
				    IFIX(isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,
				    d1),FIXNUM_TIMES(d2,d2))));
			    handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)19L),Nil,Nil);
			    return handle_icon_editor_visual_event(icon_editor,
				    FIX((SI_Long)17L),
				    icon_editor_cons_1(x0_in_view_pad,
				    y0_in_view_pad),FIX(radius_in_view_pad));
			}
			else
			    return VALUES_1(Nil);
		      case 17:
			return handle_mouse_motion_for_moving_layer(icon_editor,
				view_pad,state_1,translator,
				state_information_qm,arg_1_qm,arg_2_qm);
		      default:
			return VALUES_1(Nil);
		    }
	      case 23:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = arg_1_qm;
		if (IFIX(scale) == (SI_Long)4096L)
		    new_width = value;
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    new_width = inverse_scalef_function(scale,value);
		else if (IFIX(value) >= (SI_Long)0L) {
		    temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		    new_width = temp;
		}
		else {
		    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp = FIXNUM_NEGATE(FIX(temp_1));
		    new_width = temp;
		}
		temp = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)1L);
		if ( !NUM_EQ(new_width,temp)) {
		    if (IFIX(new_width) <= (SI_Long)0L) {
			new_width = FIX((SI_Long)1L);
			scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
				(SI_Long)10L);
			value = new_width;
			if (IFIX(scale) == (SI_Long)4096L)
			    temp = value;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value) && FIXNUM_LT(value,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value)) + (SI_Long)2048L;
			    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
			}
			else
			    temp = scalef_function(scale,value);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)11L),temp,Nil);
		    }
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)4L),new_width,Nil);
		    return enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)23L),new_width,Nil,Nil,Nil);
		}
		else
		    return VALUES_1(Nil);
	      case 24:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = arg_1_qm;
		if (IFIX(scale) == (SI_Long)4096L)
		    new_height = value;
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    new_height = inverse_scalef_function(scale,value);
		else if (IFIX(value) >= (SI_Long)0L) {
		    temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		    new_height = temp;
		}
		else {
		    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp = FIXNUM_NEGATE(FIX(temp_1));
		    new_height = temp;
		}
		if ( !FIXNUM_EQ(new_height,ISVREF(ISVREF(icon_editor,
			(SI_Long)11L),(SI_Long)2L))) {
		    if (IFIX(new_height) <= (SI_Long)0L) {
			new_height = FIX((SI_Long)1L);
			scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
				(SI_Long)11L);
			value = new_height;
			if (IFIX(scale) == (SI_Long)4096L)
			    temp = value;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				scale) && FIXNUM_LT(scale,
				Isqrt_of_most_positive_fixnum) && 
				FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				value) && FIXNUM_LT(value,
				Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(FIXNUM_TIMES(scale,
				    value)) + (SI_Long)2048L;
			    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
			}
			else
			    temp = scalef_function(scale,value);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)12L),temp,Nil);
		    }
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)5L),new_height,Nil);
		    return enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)24L),new_height,Nil,Nil,Nil);
		}
		else
		    return VALUES_1(Nil);
	      case 25:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)22L),Nil,Nil,Nil,Nil);
	      case 21:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		if ( !FIXNUM_EQ(arg_1_qm,ISVREF(ISVREF(icon_editor,
			(SI_Long)11L),(SI_Long)1L))) {
		    scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
			    (SI_Long)10L);
		    value = arg_1_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			temp = value;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		    }
		    else
			temp = scalef_function(scale,value);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)11L),temp,Nil);
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)23L),arg_1_qm,Nil,Nil,Nil);
		    return enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)22L),Nil,Nil,Nil,Nil);
		}
		else
		    return VALUES_1(Nil);
	      case 22:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		if ( !FIXNUM_EQ(arg_1_qm,ISVREF(ISVREF(icon_editor,
			(SI_Long)11L),(SI_Long)2L))) {
		    scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
			    (SI_Long)11L);
		    value = arg_1_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			temp = value;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		    }
		    else
			temp = scalef_function(scale,value);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)12L),temp,Nil);
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)24L),arg_1_qm,Nil,Nil,Nil);
		    return enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)22L),Nil,Nil,Nil,Nil);
		}
		else
		    return VALUES_1(Nil);
	      case 20:
		scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),(SI_Long)10L);
		value = arg_1_qm;
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,value);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)11L),temp,Nil);
		scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),(SI_Long)11L);
		value = arg_2_qm;
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,value);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)12L),temp,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)4L),arg_1_qm,Nil);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)5L),arg_2_qm,Nil);
	      case 2:
	      case 4:
		temp = state_1;
		if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    return VALUES_1(Nil);
		else
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 17:
			if (CDR(state_information_qm)) {
			    new_coord = FIRST(state_information_qm);
			    M_CAR(new_coord) = arg_1_qm;
			    M_CDR(new_coord) = arg_2_qm;
			}
			return translator_end_moving_layer_in_xy_plane(icon_editor,
				translator,state_information_qm);
		      default:
			return VALUES_1(Nil);
		    }
	      case 1:
	      case 61:
		return handle_translator_view_pad_mouse_down_event(arg_1_qm,
			arg_2_qm,icon_editor,translator,state_1,
			state_information_qm);
	      case 3:
		if (IFIX(state_1) == (SI_Long)17L) {
		    clear_icon_editor_translator_state_information(translator);
		    state_1 = ISVREF(translator,(SI_Long)1L);
		    state_information_qm = ISVREF(translator,(SI_Long)2L);
		}
		else
		    translator_end_current_state(4,icon_editor,translator,
			    state_1,state_information_qm);
		return handle_layers_pad_translator_event(icon_editor,
			translator_event,arg_1_qm,arg_2_qm);
	      case 6:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)6L),Nil,Nil,Nil,Nil);
	      case 5:
		translator_cancel_current_state(icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)5L),Nil,Nil,Nil,Nil);
	      case 27:
	      case 28:
	      case 29:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		gensymed_symbol = (SI_Long)4096L;
		temp = translator_event;
		if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    gensymed_symbol_1 = (SI_Long)0L;
		else
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 27:
			gensymed_symbol_1 = (SI_Long)1L;
			break;
		      case 28:
			gensymed_symbol_1 = (SI_Long)2L;
			break;
		      case 29:
			gensymed_symbol_1 = (SI_Long)3L;
			break;
		      default:
			gensymed_symbol_1 = (SI_Long)0L;
			break;
		    }
		scale_1 = gensymed_symbol * gensymed_symbol_1;
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		ISVREF(view_pad,(SI_Long)10L) = FIX(scale_1);
		ISVREF(view_pad,(SI_Long)11L) = FIX(scale_1);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)20L),ISVREF(engine,(SI_Long)1L),
			ISVREF(engine,(SI_Long)2L));
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)21L),Nil,Nil);
	      case 19:
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)21L),Nil,Nil);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)36L),Nil,Nil);
	      case 33:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)4L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)4L),Nil);
	      case 34:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)5L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)5L),Nil);
	      case 35:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)6L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)6L),Nil);
	      case 36:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)7L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)7L),Nil);
	      case 37:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)8L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)8L),Nil);
	      case 38:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)9L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)9L),Nil);
	      case 39:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)10L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)10L),Nil);
	      case 40:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)11L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)11L),Nil);
	      case 41:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)12L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)12L),Nil);
	      case 42:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)13L);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),FIX((SI_Long)13L),Nil);
	      case 31:
		if (IFIX(state_1) == (SI_Long)17L) {
		    translator_cancel_current_state(icon_editor,translator,
			    state_1,state_information_qm);
		    state_1 = ISVREF(translator,(SI_Long)1L);
		    state_information_qm = ISVREF(translator,(SI_Long)2L);
		}
		if ( !TRUEP(state_information_qm))
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)31L),arg_1_qm,Nil,Nil,Nil);
		return translator_cancel_current_state(icon_editor,
			translator,state_1,state_information_qm);
	      case 46:
		return VALUES_1(Nil);
	      case 50:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)1L),Nil,Nil);
	      case 51:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)2L),Nil,Nil);
	      case 8:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)8L),arg_1_qm,Nil,Nil,Nil);
	      case 30:
		return translator_end_current_state(4,icon_editor,
			translator,state_1,state_information_qm);
	      case 18:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)18L),arg_1_qm,Nil,Nil,Nil);
	      case 17:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)17L),arg_1_qm,Nil,Nil,Nil);
	      case 10:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)10L),Nil,Nil,Nil,Nil);
	      case 11:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)11L),Nil,Nil,Nil,Nil);
	      case 9:
		translator_cancel_current_state(icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)9L),Nil,Nil,Nil,Nil);
	      case 12:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)12L),Nil,Nil,Nil,Nil);
	      case 13:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)13L),Nil,Nil,Nil,Nil);
	      case 14:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)14L),arg_1_qm,Nil,Nil,Nil);
	      case 7:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)7L),Nil,Nil,Nil,Nil);
	      case 55:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)55L),arg_1_qm,arg_2_qm,Nil,Nil);
	      case 56:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return handle_move_layer_in_xy_plane_in_translator(icon_editor,
			translator);
	      case 57:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)57L),Nil,Nil,Nil,Nil);
	      case 58:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)58L),Nil,Nil,Nil,Nil);
	      case 59:
		translator_end_current_state(4,icon_editor,translator,
			state_1,state_information_qm);
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)59L),Nil,Nil,Nil,Nil);
	      case 65:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)64L),arg_1_qm,Nil,Nil,Nil);
	      case 66:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)65L),arg_1_qm,Nil,Nil,Nil);
	      case 67:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)66L),arg_1_qm,Nil,Nil,Nil);
	      case 68:
		return enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)67L),arg_1_qm,Nil,Nil,Nil);
	      case 64:
		return VALUES_1(Nil);
	      default:
		return VALUES_1(Nil);
	    }
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* HANDLE-MOUSE-MOTION-FOR-MOVING-LAYER */
Object handle_mouse_motion_for_moving_layer(icon_editor,view_pad,state_1,
	    translator,state_information_qm,x,y)
    Object icon_editor, view_pad, state_1, translator, state_information_qm, x;
    Object y;
{
    Object layer_icon_qm, serial_number, gensymed_symbol, xa, ya, offset_coord;
    Object x_offset_in_workspace, y_offset_in_workspace;
    Object bounded_x_in_workspace, bounded_y_in_workspace, last_coord;
    Object old_cursor_x_in_workspace, old_cursor_y_in_workspace;
    Object delta_x_in_workspace, delta_y_in_workspace;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, temp_1;
    char temp;
    Object result;

    x_note_fn_call(234,19);
    layer_icon_qm = ISVREF(view_pad,(SI_Long)16L);
    if (layer_icon_qm) {
	serial_number = ISVREF(view_pad,(SI_Long)17L);
	gensymed_symbol = ISVREF(layer_icon_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(layer_icon_qm) ? EQ(ISVREF(layer_icon_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    offset_coord = SECOND(state_information_qm);
	    x_offset_in_workspace = CAR(offset_coord);
	    y_offset_in_workspace = CDR(offset_coord);
	    result = compute_bounded_point_in_workspace(x,y,view_pad,
		    x_offset_in_workspace,y_offset_in_workspace);
	    MVS_2(result,bounded_x_in_workspace,bounded_y_in_workspace);
	    last_coord = FIRST(state_information_qm);
	    old_cursor_x_in_workspace = CAR(last_coord);
	    old_cursor_y_in_workspace = CDR(last_coord);
	    delta_x_in_workspace = FIXNUM_MINUS(bounded_x_in_workspace,
		    old_cursor_x_in_workspace);
	    delta_y_in_workspace = FIXNUM_MINUS(bounded_y_in_workspace,
		    old_cursor_y_in_workspace);
	    move_blocks_with_their_external_connections(layer_icon_qm,
		    ISVREF(icon_editor,(SI_Long)4L),delta_x_in_workspace,
		    delta_y_in_workspace);
	    gensymed_symbol = ISVREF(layer_icon_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(x_offset_in_workspace);
	    temp_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    M_CAR(last_coord) = FIX(temp_1);
	    gensymed_symbol = ISVREF(layer_icon_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(y_offset_in_workspace);
	    temp_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    return VALUES_1(M_CDR(last_coord) = FIX(temp_1));
	}
	else
	    return translator_cancel_current_state(icon_editor,translator,
		    state_1,state_information_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* TRANSLATOR-END-CURRENT-STATE */
Object translator_end_current_state varargs_1(int, n)
{
    Object icon_editor, translator, state_1, state_information_qm;
    Object keep_current_state_qm, temp, failed_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(234,20);
    INIT_ARGS_nonrelocating();
    icon_editor = REQUIRED_ARG_nonrelocating();
    translator = REQUIRED_ARG_nonrelocating();
    state_1 = REQUIRED_ARG_nonrelocating();
    state_information_qm = REQUIRED_ARG_nonrelocating();
    keep_current_state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)20L),Nil,Nil);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
	    FIX((SI_Long)0L),Nil);
    temp = state_1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 3:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_1,
		    FIX((SI_Long)19L)),Nil);
	    break;
	  case 4:
	    if (state_information_qm) {
		enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)33L),state_information_qm,Nil,Nil,Nil);
		SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    }
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_1,
		    FIX((SI_Long)19L)),Nil);
	    break;
	  case 5:
	    if (state_information_qm)
		reclaim_icon_editor_cons_1(state_information_qm);
	    SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_2,
		    FIX((SI_Long)17L)),Nil);
	    break;
	  case 6:
	    if (CDR(state_information_qm))
		enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)35L),state_information_qm,Nil,Nil,Nil);
	    SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_3,
		    FIX((SI_Long)18L)),Nil);
	    break;
	  case 7:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_4,
		    FIX((SI_Long)16L)),Nil);
	    break;
	  case 8:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_5,
		    FIX((SI_Long)31L)),Nil);
	    break;
	  case 9:
	    if (state_information_qm) {
		if (CDDR(state_information_qm)) {
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)38L),state_information_qm,Nil,Nil,
			    Nil);
		    SVREF(translator,FIX((SI_Long)2L)) = Nil;
		}
		else
		    clear_icon_editor_translator_state_information(translator);
	    }
	    if ( !TRUEP(keep_current_state_qm))
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),
			copy_constant_wide_string_given_length(array_constant_6,
			FIX((SI_Long)29L)),Nil);
	    break;
	  case 10:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_7,
		    FIX((SI_Long)28L)),Nil);
	    break;
	  case 11:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_8,
		    FIX((SI_Long)29L)),Nil);
	    break;
	  case 12:
	    failed_p = Nil;
	    if (state_information_qm) {
		if (CDDR(state_information_qm)) {
		    failed_p = 
			    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)41L),state_information_qm,Nil,Nil,
			    Nil);
		    SVREF(translator,FIX((SI_Long)2L)) = Nil;
		}
		else
		    clear_icon_editor_translator_state_information(translator);
	    }
	    if ( !(failed_p || keep_current_state_qm))
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),
			copy_constant_wide_string_given_length(array_constant_9,
			FIX((SI_Long)27L)),Nil);
	    break;
	  case 13:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_10,
		    FIX((SI_Long)26L)),Nil);
	    break;
	  case 14:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_11,
		    FIX((SI_Long)38L)),Nil);
	    break;
	  case 15:
	    if (state_information_qm) {
		enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)44L),state_information_qm,Nil,Nil,Nil);
		SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    }
	    if ( !TRUEP(keep_current_state_qm))
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),
			copy_constant_wide_string_given_length(array_constant_12,
			FIX((SI_Long)36L)),Nil);
	    break;
	  case 16:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_13,
		    FIX((SI_Long)35L)),Nil);
	    break;
	  case 17:
	    translator_end_moving_layer_in_xy_plane(icon_editor,translator,
		    state_information_qm);
	    break;
	  default:
	    break;
	}
    if ( !TRUEP(keep_current_state_qm))
	ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)0L);
    return clear_icon_editor_translator_state_information(translator);
}

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

/* TRANSLATOR-CANCEL-CURRENT-STATE */
Object translator_cancel_current_state(icon_editor,translator,state_1,
	    state_information_qm)
    Object icon_editor, translator, state_1, state_information_qm;
{
    Object temp;

    x_note_fn_call(234,21);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)20L),Nil,Nil);
    temp = state_1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 3:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_14,
		    FIX((SI_Long)22L)),Nil);
	    break;
	  case 4:
	    if (state_information_qm) {
		enqueue_icon_editor_engine_event(icon_editor,
			FIX((SI_Long)33L),state_information_qm,Nil,Nil,Nil);
		SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    }
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_14,
		    FIX((SI_Long)22L)),Nil);
	    break;
	  case 5:
	    if (state_information_qm)
		reclaim_icon_editor_cons_1(state_information_qm);
	    SVREF(translator,FIX((SI_Long)2L)) = Nil;
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_15,
		    FIX((SI_Long)20L)),Nil);
	    break;
	  case 6:
	    if (state_information_qm) {
		reclaim_icon_editor_slot_value(state_information_qm);
		SVREF(translator,FIX((SI_Long)2L)) = Nil;
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),
			copy_constant_wide_string_given_length(array_constant_16,
			FIX((SI_Long)21L)),Nil);
	    }
	    break;
	  case 7:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_4,
		    FIX((SI_Long)16L)),Nil);
	    break;
	  case 8:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_5,
		    FIX((SI_Long)31L)),Nil);
	    break;
	  case 9:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_17,
		    FIX((SI_Long)32L)),Nil);
	    break;
	  case 10:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_7,
		    FIX((SI_Long)28L)),Nil);
	    break;
	  case 11:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_8,
		    FIX((SI_Long)29L)),Nil);
	    break;
	  case 12:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_18,
		    FIX((SI_Long)30L)),Nil);
	    break;
	  case 13:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_10,
		    FIX((SI_Long)26L)),Nil);
	    break;
	  case 14:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_11,
		    FIX((SI_Long)38L)),Nil);
	    break;
	  case 15:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_19,
		    FIX((SI_Long)39L)),Nil);
	    break;
	  case 16:
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    copy_constant_wide_string_given_length(array_constant_13,
		    FIX((SI_Long)35L)),Nil);
	    break;
	  case 17:
	    clear_icon_editor_translator_state_information(translator);
	    translator_end_moving_layer_in_xy_plane(icon_editor,translator,
		    state_information_qm);
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    FIX((SI_Long)0L),Nil);
	    break;
	  default:
	    break;
	}
    ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)0L);
    return clear_icon_editor_translator_state_information(translator);
}

void icons3_INIT()
{
    Object list_constant, AB_package;

    x_note_fn_call(234,22);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qfilled_circle = STATIC_SYMBOL("FILLED-CIRCLE",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qiconic_entity = STATIC_SYMBOL("ICONIC-ENTITY",AB_package);
    if (Distance_to_snap_points_together_in_view_pad == UNBOUND)
	Distance_to_snap_points_together_in_view_pad = FIX((SI_Long)2L);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)57344L);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)32L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)35L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)32L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)34L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)39L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)25L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)26L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)29L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)39L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)33L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)34L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)35L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)47L,(SI_Long)57344L);
}
