/* icons2.c
 * Input file:  icons2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons2.h"


static Object string_constant;     /* "Icon editor ready." */

static Object string_constant_1;   /* "Undo." */

static Object string_constant_2;   /* "Redo." */

static Object string_constant_3;   /* "Drawing point." */

static Object string_constant_4;   /* "Drawing points." */

static Object string_constant_5;   /* "Drawing line." */

static Object string_constant_6;   /* "Drawing lines." */

static Object string_constant_7;   /* "Drawing an arc." */

static Object string_constant_8;   /* "Drawing an outlined rectangle." */

static Object string_constant_9;   /* "Drawing an outlined polygon." */

static Object string_constant_10;  /* "Drawing an outlined circle." */

static Object string_constant_11;  /* "Drawing a filled rectangle." */

static Object string_constant_12;  /* "Drawing a filled polygon." */

static Object string_constant_13;  /* "Drawing a filled circle." */

static Object string_constant_14;  /* "Drawing a filled and outlined rectangle." */

static Object string_constant_15;  /* "Drawing a filled and outlined polygon." */

static Object string_constant_16;  /* "Drawing a filled and outlined circle." */

static Object string_constant_17;  /* "Drag the current layer to its new position." */

static Object string_constant_18;  /* "Working with layers." */

static Object string_constant_19;  /* "~a" */

static Object Qicon_editor_ready;  /* icon-editor-ready */

/* WRITE-ICON-EDITOR-TABLE-INFO-FRAME-INFO-FROM-SLOT */
Object write_icon_editor_table_info_frame_info_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(233,0);
    if (FIXNUMP(value) && (SI_Long)0L <= IFIX(value) && IFIX(value) <= 
	    (SI_Long)18L) {
	temp = value;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = string_constant;
		break;
	      case 1:
		temp = string_constant_1;
		break;
	      case 2:
		temp = string_constant_2;
		break;
	      case 3:
		temp = string_constant_3;
		break;
	      case 4:
		temp = string_constant_4;
		break;
	      case 5:
		temp = string_constant_5;
		break;
	      case 6:
		temp = string_constant_6;
		break;
	      case 7:
		temp = string_constant_7;
		break;
	      case 8:
		temp = string_constant_8;
		break;
	      case 9:
		temp = string_constant_9;
		break;
	      case 10:
		temp = string_constant_10;
		break;
	      case 11:
		temp = string_constant_11;
		break;
	      case 12:
		temp = string_constant_12;
		break;
	      case 13:
		temp = string_constant_13;
		break;
	      case 14:
		temp = string_constant_14;
		break;
	      case 15:
		temp = string_constant_15;
		break;
	      case 16:
		temp = string_constant_16;
		break;
	      case 17:
		temp = string_constant_17;
		break;
	      case 18:
		temp = string_constant_18;
		break;
	      default:
		temp = Nil;
		break;
	    }
	return twrite_general_string(temp);
    }
    else if (text_string_p(value))
	return tformat(2,string_constant_19,value);
    else if ( !TRUEP(value))
	return VALUES_1(Nil);
    else if (SYMBOLP(value)) {
	temp = value;
	if (temp);
	else
	    temp = Qicon_editor_ready;
	return twrite_symbol(1,temp);
    }
    else
	return twrite(value);
}

Object Icon_editor_buttons_specification_list = UNBOUND;

Object Icon_editor_tables_specification_list = UNBOUND;

/* POINT-IN-VIEW-PAD-P */
Object point_in_view_pad_p(x_in_workspace,y_in_workspace,view_pad)
    Object x_in_workspace, y_in_workspace, view_pad;
{
    Object scale, leeway_x_in_workspace, temp, leeway_y_in_workspace;
    Object gensymed_symbol;
    SI_Long leeway, value, temp_1, gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;

    x_note_fn_call(233,1);
    leeway = (SI_Long)10L;
    scale = ISVREF(Current_image_plane_qm,(SI_Long)11L);
    value = leeway;
    if (IFIX(scale) == (SI_Long)4096L)
	leeway_x_in_workspace = FIX(value);
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	leeway_x_in_workspace = inverse_scalef_function(scale,FIX(value));
    else if (value >= (SI_Long)0L) {
	temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	leeway_x_in_workspace = temp;
    }
    else {
	temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	leeway_x_in_workspace = temp;
    }
    scale = ISVREF(Current_image_plane_qm,(SI_Long)12L);
    value = leeway;
    if (IFIX(scale) == (SI_Long)4096L)
	leeway_y_in_workspace = FIX(value);
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	leeway_y_in_workspace = inverse_scalef_function(scale,FIX(value));
    else if (value >= (SI_Long)0L) {
	temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	leeway_y_in_workspace = temp;
    }
    else {
	temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	leeway_y_in_workspace = temp;
    }
    if (FIXNUM_LE(ISVREF(view_pad,(SI_Long)1L),x_in_workspace)) {
	gensymed_symbol = ISVREF(ISVREF(view_pad,(SI_Long)3L),(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(leeway_x_in_workspace);
	temp_2 = FIXNUM_LT(x_in_workspace,FIX(gensymed_symbol_1 + 
		gensymed_symbol_2));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_LE(ISVREF(view_pad,(SI_Long)2L),y_in_workspace) : 
	    TRUEP(Nil)) {
	gensymed_symbol = ISVREF(ISVREF(view_pad,(SI_Long)3L),(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(leeway_y_in_workspace);
	return VALUES_1(FIXNUM_LT(y_in_workspace,FIX(gensymed_symbol_1 + 
		gensymed_symbol_2)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtransparent;        /* transparent */

static Object Qforeground;         /* foreground */

static Object Qab_slot_value;      /* slot-value */

static Object Qpolychrome;         /* polychrome */

/* WRAP-POLYCHROME-DECLARATION-AROUND-SLOT-VALUE-CONSES */
Object wrap_polychrome_declaration_around_slot_value_conses(color,
	    line_drawing_description)
    Object color, line_drawing_description;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(233,2);
    if (EQ(color,Qtransparent))
	color = Qforeground;
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
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
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_slot_value_cons_pool();
    M_CAR(gensymed_symbol_1) = color;
    M_CDR(gensymed_symbol_1) = color;
    inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
    temp = slot_value_list_2(Qpolychrome,gensymed_symbol_1);
    M_CAR(gensymed_symbol) = temp;
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
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_slot_value_cons_pool();
    M_CAR(gensymed_symbol_1) = color;
    M_CDR(gensymed_symbol_1) = line_drawing_description;
    inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    return VALUES_1(gensymed_symbol);
}

static Object Qoutline;            /* outline */

static Object Qlines;              /* lines */

static Object Qiconic_entity;      /* iconic-entity */

/* PUT-LINE-MARKER-IN-VIEW-PAD */
Object put_line_marker_in_view_pad(x0_in_view_pad,y0_in_view_pad,
	    x1_in_view_pad,y1_in_view_pad,view_pad,color,
	    left_edge_to_clip_in_workspace,top_edge_to_clip_in_workspace,
	    right_edge_to_clip_in_workspace,
	    bottom_edge_to_clip_in_workspace,put_rectangle_marker_instead_qm)
    Object x0_in_view_pad, y0_in_view_pad, x1_in_view_pad, y1_in_view_pad;
    Object view_pad, color, left_edge_to_clip_in_workspace;
    Object top_edge_to_clip_in_workspace, right_edge_to_clip_in_workspace;
    Object bottom_edge_to_clip_in_workspace, put_rectangle_marker_instead_qm;
{
    Object scale, value, desired_x0_in_icon, desired_y_for_x0_in_icon;
    Object desired_y_for_x1_in_icon, x1_in_icon, gensymed_symbol_2;
    Object gensymed_symbol_3, temp_2, temp_3, line_marker;
    SI_Long unshifted_result, x0_in_icon, y0_in_icon, y1_in_icon;
    SI_Long x0_in_workspace, gensymed_symbol, gensymed_symbol_1;
    SI_Long y0_in_workspace, temp, desired_icon_width, desired_icon_height;
    SI_Long temp_1, icon_width, icon_height;
    char flip_ends_of_lines_qm, right_end_of_line_higher_qm;

    x_note_fn_call(233,3);
    flip_ends_of_lines_qm = FIXNUM_GT(x0_in_view_pad,x1_in_view_pad);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = flip_ends_of_lines_qm ? x1_in_view_pad : x0_in_view_pad;
    if (IFIX(scale) == (SI_Long)4096L)
	desired_x0_in_icon = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	desired_x0_in_icon = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	desired_x0_in_icon = scalef_function(scale,value);
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = flip_ends_of_lines_qm ? y1_in_view_pad : y0_in_view_pad;
    if (IFIX(scale) == (SI_Long)4096L)
	desired_y_for_x0_in_icon = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	desired_y_for_x0_in_icon = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	desired_y_for_x0_in_icon = scalef_function(scale,value);
    x0_in_icon = MAX(IFIX(desired_x0_in_icon),(SI_Long)0L);
    y0_in_icon = MAX(IFIX(desired_y_for_x0_in_icon),(SI_Long)0L);
    scale = ISVREF(view_pad,(SI_Long)11L);
    value = flip_ends_of_lines_qm ? y0_in_view_pad : y1_in_view_pad;
    if (IFIX(scale) == (SI_Long)4096L)
	desired_y_for_x1_in_icon = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	desired_y_for_x1_in_icon = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	desired_y_for_x1_in_icon = scalef_function(scale,value);
    scale = ISVREF(view_pad,(SI_Long)10L);
    value = flip_ends_of_lines_qm ? x0_in_view_pad : x1_in_view_pad;
    if (IFIX(scale) == (SI_Long)4096L)
	x1_in_icon = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	x1_in_icon = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	x1_in_icon = scalef_function(scale,value);
    y1_in_icon = MAX(IFIX(desired_y_for_x1_in_icon),(SI_Long)0L);
    right_end_of_line_higher_qm = y0_in_icon > y1_in_icon;
    x0_in_workspace = x0_in_icon + IFIX(ISVREF(view_pad,(SI_Long)5L));
    gensymed_symbol = right_end_of_line_higher_qm ? y1_in_icon : y0_in_icon;
    gensymed_symbol_1 = IFIX(ISVREF(view_pad,(SI_Long)6L));
    y0_in_workspace = gensymed_symbol + gensymed_symbol_1;
    temp = IFIX(x1_in_icon) - x0_in_icon;
    desired_icon_width = ABS(temp);
    temp = y1_in_icon - y0_in_icon;
    desired_icon_height = ABS(temp);
    temp_1 = MAX((SI_Long)1L,desired_icon_width);
    temp = IFIX(FIXNUM_ADD1(right_edge_to_clip_in_workspace)) - 
	    MAX(IFIX(left_edge_to_clip_in_workspace),x0_in_workspace);
    icon_width = MIN(temp_1,temp);
    temp_1 = MAX((SI_Long)1L,desired_icon_height);
    temp = IFIX(FIXNUM_ADD1(bottom_edge_to_clip_in_workspace)) - 
	    MAX(IFIX(top_edge_to_clip_in_workspace),y0_in_workspace);
    icon_height = MIN(temp_1,temp);
    if (put_rectangle_marker_instead_qm) {
	gensymed_symbol_2 = make_slot_value_list_1(FIX((SI_Long)5L));
	gensymed_symbol_3 = gensymed_symbol_2;
	M_CAR(gensymed_symbol_3) = Qoutline;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_2 = slot_value_list_2(FIX((SI_Long)0L),FIX((SI_Long)0L));
	M_CAR(gensymed_symbol_3) = temp_2;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_2 = slot_value_list_2(FIX((SI_Long)0L),FIX(desired_icon_height));
	M_CAR(gensymed_symbol_3) = temp_2;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_2 = slot_value_list_2(FIX(desired_icon_width),
		FIX(desired_icon_height));
	M_CAR(gensymed_symbol_3) = temp_2;
	gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	temp_2 = slot_value_list_2(FIX(desired_icon_width),FIX((SI_Long)0L));
	M_CAR(gensymed_symbol_3) = temp_2;
	temp_3 = slot_value_cons_1(gensymed_symbol_2,Nil);
    }
    else
	temp_3 = slot_value_cons_1(slot_value_list_3(Qlines,
		slot_value_list_2(FIX((SI_Long)0L),
		right_end_of_line_higher_qm ? FIX(desired_icon_height) : 
		FIX((SI_Long)0L)),
		slot_value_list_2(FIX(desired_icon_width),
		right_end_of_line_higher_qm ? FIX((SI_Long)0L) : 
		FIX(desired_icon_height))),Nil);
    line_marker = make_entity_with_specific_icon_description(4,
	    Qiconic_entity,
	    wrap_polychrome_declaration_around_slot_value_conses(color,
	    temp_3),FIX(icon_width),FIX(icon_height));
    temp_3 = icon_editor_cons_1(line_marker,
	    copy_frame_serial_number(Current_frame_serial_number));
    temp_2 = icon_editor_cons_1(temp_3,ISVREF(view_pad,(SI_Long)12L));
    SVREF(view_pad,FIX((SI_Long)12L)) = temp_2;
    return add_to_workspace(5,line_marker,ISVREF(view_pad,(SI_Long)9L),
	    FIX(x0_in_workspace),FIX(y0_in_workspace),T);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_20;  /* "~(~a~)" */

static Object Qborderless_free_text;  /* borderless-free-text */

static Object Qborder;             /* border */

static Object Qblack;              /* black */

static Object Qsolid_rectangle;    /* solid-rectangle */

/* CREATE-LAYER-BOX */
Object create_layer_box(icon_editor,layer,layer_index_init,x_scale_init,
	    y_scale_init)
    Object icon_editor, layer, layer_index_init, x_scale_init, y_scale_init;
{
    Object symbol_for_label, engine, layers_pad, alist, temp, color;
    Object border_width, scaled_icon_width, scaled_icon_height, list_of_layers;
    Object layer_box_x_offset_of_layer_icon_from_x0;
    Object layer_box_y_offset_of_layer_icon_from_y0, variable_spec_list;
    Object background_layer, stipple_spec, layer_icon;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_label, scaled_width_of_layer_box, gensymed_symbol_3;
    Object gensymed_symbol_6, temp_1, gensymed_symbol_7, gensymed_symbol_8;
    Object border_icon, layer_box;
    SI_Long layer_index, x_scale, y_scale, icon_width, icon_height;
    SI_Long unshifted_result, icon_outline_left_edge_in_border_icon;
    SI_Long icon_outline_top_edge_in_border_icon;
    SI_Long icon_outline_right_edge_in_border_icon;
    SI_Long icon_outline_bottom_edge_in_border_icon, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long scaled_height_of_layer_box;
    Declare_special(5);

    x_note_fn_call(233,4);
    layer_index = IFIX(layer_index_init);
    x_scale = IFIX(x_scale_init);
    y_scale = IFIX(y_scale_init);
    symbol_for_label = FIRST(layer);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    icon_width = IFIX(ISVREF(engine,(SI_Long)1L));
    icon_height = IFIX(ISVREF(engine,(SI_Long)2L));
    alist = ISVREF(icon_editor,(SI_Long)6L);
    temp = assq_function(symbol_for_label,alist);
    color = CDR(temp);
    border_width = ISVREF(layers_pad,(SI_Long)12L);
    if (x_scale == (SI_Long)4096L)
	scaled_icon_width = FIX(icon_width);
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < x_scale && 
	    x_scale < IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < icon_width && 
	    icon_width < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = x_scale * icon_width + (SI_Long)2048L;
	scaled_icon_width = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	scaled_icon_width = scalef_function(FIX(x_scale),FIX(icon_width));
    if (y_scale == (SI_Long)4096L)
	scaled_icon_height = FIX(icon_height);
    else if (IFIX(Minus_of_isqrt_of_most_positive_fixnum) < y_scale && 
	    y_scale < IFIX(Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < icon_height && 
	    icon_height < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = y_scale * icon_height + (SI_Long)2048L;
	scaled_icon_height = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	scaled_icon_height = scalef_function(FIX(y_scale),FIX(icon_height));
    list_of_layers = icon_editor_cons_1(layer,Nil);
    layer_box_x_offset_of_layer_icon_from_x0 = FIXNUM_ADD1(border_width);
    layer_box_y_offset_of_layer_icon_from_y0 = FIXNUM_ADD1(border_width);
    icon_outline_left_edge_in_border_icon = 
	    IFIX(layer_box_x_offset_of_layer_icon_from_x0) - (SI_Long)2L;
    icon_outline_top_edge_in_border_icon = 
	    IFIX(layer_box_y_offset_of_layer_icon_from_y0) - (SI_Long)2L;
    icon_outline_right_edge_in_border_icon = 
	    IFIX(FIXNUM_ADD(scaled_icon_width,
	    layer_box_x_offset_of_layer_icon_from_x0)) + (SI_Long)2L;
    icon_outline_bottom_edge_in_border_icon = 
	    IFIX(FIXNUM_ADD(scaled_icon_height,
	    layer_box_y_offset_of_layer_icon_from_y0)) + (SI_Long)2L;
    M_FIRST(layer) = Qforeground;
    variable_spec_list = ISVREF(icon_editor,(SI_Long)7L);
    background_layer = ISVREF(icon_editor,(SI_Long)8L);
    stipple_spec = ISVREF(icon_editor,(SI_Long)9L);
    layer_icon = make_entity_with_specific_icon_description(4,
	    Qiconic_entity,
	    convert_list_of_layers_to_line_drawing_description(list_of_layers,
	    alist,variable_spec_list,background_layer,scaled_icon_width,
	    scaled_icon_height,FIX(x_scale),FIX(y_scale),T,T,stipple_spec),
	    scaled_icon_width,scaled_icon_height);
    M_FIRST(layer) = symbol_for_label;
    reclaim_icon_editor_cons_1(list_of_layers);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(2,string_constant_20,symbol_for_label);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    text_for_label = make_free_text_box(5,temp,Qborderless_free_text,Nil,
	    FIX((SI_Long)160L - (SI_Long)22L),Ellipsis_text_string);
    scaled_width_of_layer_box = ISVREF(layers_pad,(SI_Long)15L);
    gensymed_symbol = IFIX(border_width) << (SI_Long)1L;
    gensymed_symbol_1 = (SI_Long)4L * (SI_Long)1L;
    gensymed_symbol_2 = IFIX(scaled_icon_height);
    gensymed_symbol_3 = ISVREF(text_for_label,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol_3);
    gensymed_symbol_3 = ISVREF(text_for_label,(SI_Long)14L);
    gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_5 = IFIX(gensymed_symbol_3);
    gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
    gensymed_symbol_5 = (SI_Long)-1L;
    scaled_height_of_layer_box = gensymed_symbol + gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_4 + gensymed_symbol_5;
    gensymed_symbol_3 = make_slot_value_list_1(FIX((SI_Long)8L));
    gensymed_symbol_6 = gensymed_symbol_3;
    temp_1 = slot_value_list_4(Qpolychrome,slot_value_cons_1(Qborder,
	    Qtransparent),slot_value_cons_1(Qtransparent,Qtransparent),
	    slot_value_cons_1(Qoutline,Qblack));
    M_CAR(gensymed_symbol_6) = temp_1;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = Qborder;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_1 = slot_value_list_3(Qsolid_rectangle,
	    slot_value_list_2(FIX((SI_Long)0L),FIX((SI_Long)0L)),
	    slot_value_list_2(scaled_width_of_layer_box,
	    FIX(scaled_height_of_layer_box)));
    M_CAR(gensymed_symbol_6) = temp_1;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = Qtransparent;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    temp_1 = slot_value_list_3(Qsolid_rectangle,
	    slot_value_list_2(border_width,border_width),
	    slot_value_list_2(FIXNUM_MINUS(scaled_width_of_layer_box,
	    border_width),FIX(scaled_height_of_layer_box - 
	    IFIX(border_width))));
    M_CAR(gensymed_symbol_6) = temp_1;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    M_CAR(gensymed_symbol_6) = Qoutline;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    gensymed_symbol_7 = make_slot_value_list_1(FIX((SI_Long)5L));
    gensymed_symbol_8 = gensymed_symbol_7;
    M_CAR(gensymed_symbol_8) = Qoutline;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX((SI_Long)0L),FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX((SI_Long)0L),
	    FIX(scaled_height_of_layer_box));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(scaled_width_of_layer_box,
	    FIX(scaled_height_of_layer_box));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(scaled_width_of_layer_box,FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_8) = temp_1;
    M_CAR(gensymed_symbol_6) = gensymed_symbol_7;
    gensymed_symbol_6 = M_CDR(gensymed_symbol_6);
    gensymed_symbol_7 = make_slot_value_list_1(FIX((SI_Long)5L));
    gensymed_symbol_8 = gensymed_symbol_7;
    M_CAR(gensymed_symbol_8) = Qoutline;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX(icon_outline_left_edge_in_border_icon),
	    FIX(icon_outline_top_edge_in_border_icon));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX(icon_outline_left_edge_in_border_icon),
	    FIX(icon_outline_bottom_edge_in_border_icon));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX(icon_outline_right_edge_in_border_icon),
	    FIX(icon_outline_bottom_edge_in_border_icon));
    M_CAR(gensymed_symbol_8) = temp_1;
    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
    temp_1 = slot_value_list_2(FIX(icon_outline_right_edge_in_border_icon),
	    FIX(icon_outline_top_edge_in_border_icon));
    M_CAR(gensymed_symbol_8) = temp_1;
    M_CAR(gensymed_symbol_6) = gensymed_symbol_7;
    border_icon = make_entity_with_specific_icon_description(4,
	    Qiconic_entity,gensymed_symbol_3,scaled_width_of_layer_box,
	    FIX(scaled_height_of_layer_box));
    layer_box = make_layer_box_1(border_icon,text_for_label,layer_icon,
	    copy_frame_serial_number(Current_frame_serial_number));
    SVREF(layer_box,FIX((SI_Long)20L)) = layer;
    SVREF(layer_box,FIX((SI_Long)7L)) = 
	    layer_box_x_offset_of_layer_icon_from_x0;
    SVREF(layer_box,FIX((SI_Long)8L)) = 
	    layer_box_y_offset_of_layer_icon_from_y0;
    ISVREF(layer_box,(SI_Long)9L) = FIX((SI_Long)0L);
    ISVREF(layer_box,(SI_Long)10L) = FIX((SI_Long)0L);
    temp_1 = ISVREF(layer_box,(SI_Long)7L);
    SVREF(layer_box,FIX((SI_Long)11L)) = temp_1;
    temp_1 = FIXNUM_ADD1(FIXNUM_ADD(ISVREF(layer_box,(SI_Long)8L),
	    scaled_icon_height));
    SVREF(layer_box,FIX((SI_Long)12L)) = temp_1;
    SVREF(layer_box,FIX((SI_Long)14L)) = color;
    SVREF(layer_box,FIX((SI_Long)15L)) = symbol_for_label;
    ISVREF(layer_box,(SI_Long)16L) = FIX(layer_index);
    return VALUES_1(layer_box);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* GET-OR-CREATE-LAYER-BOX */
Object get_or_create_layer_box(icon_editor,layer,layer_index_init)
    Object icon_editor, layer, layer_index_init;
{
    Object layer_box_qm, serial_number, gensymed_symbol, x, xa, ya, layers_pad;
    SI_Long layer_index;
    char temp;

    x_note_fn_call(233,5);
    layer_index = IFIX(layer_index_init);
    layer_box_qm = SECOND(layer);
    if (layer_box_qm) {
	serial_number = ISVREF(layer_box_qm,(SI_Long)4L);
	gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)1L),(SI_Long)3L);
	x = ISVREF(layer_box_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
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
	if (temp);
	else {
	    gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)2L),
		    (SI_Long)3L);
	    x = ISVREF(layer_box_qm,(SI_Long)2L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
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
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	}
	if (temp);
	else {
	    gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)3L),
		    (SI_Long)3L);
	    x = ISVREF(layer_box_qm,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
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
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	}
	if (temp) {
	    delete_layer_box(layer_box_qm);
	    layer_box_qm = Nil;
	}
    }
    if (layer_box_qm) {
	ISVREF(layer_box_qm,(SI_Long)16L) = FIX(layer_index);
	return VALUES_1(layer_box_qm);
    }
    else {
	layers_pad = ISVREF(icon_editor,(SI_Long)13L);
	layer_box_qm = create_layer_box(icon_editor,layer,FIX(layer_index),
		ISVREF(layers_pad,(SI_Long)8L),ISVREF(layers_pad,(SI_Long)9L));
	M_SECOND(layer) = layer_box_qm;
	return VALUES_1(layer_box_qm);
    }
}

/* RESET-Y-MIDPOINT-OF-LAYER-BOX */
Object reset_y_midpoint_of_layer_box(layer_box)
    Object layer_box;
{
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;

    x_note_fn_call(233,6);
    gensymed_symbol = ISVREF(ISVREF(layer_box,(SI_Long)1L),(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(ISVREF(layer_box,(SI_Long)1L),(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    svref_new_value = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    return VALUES_1(ISVREF(layer_box,(SI_Long)13L) = FIX(svref_new_value));
}

static Object Qicon_color;         /* icon-color */

static Object Qwhite;              /* white */

/* PLACE-LAYER-BOX-IN-WORKSPACE */
Object place_layer_box_in_workspace(x0_in_workspace,y0_in_workspace,
	    layer_box,layers_pad,workspace)
    Object x0_in_workspace, y0_in_workspace, layer_box, layers_pad, workspace;
{
    Object svref_new_value, color_qm, temp;

    x_note_fn_call(233,7);
    svref_new_value = FIXNUM_MINUS(x0_in_workspace,ISVREF(layers_pad,
	    (SI_Long)5L));
    SVREF(layer_box,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = FIXNUM_MINUS(y0_in_workspace,ISVREF(layers_pad,
	    (SI_Long)6L));
    SVREF(layer_box,FIX((SI_Long)6L)) = svref_new_value;
    add_to_workspace(5,ISVREF(layer_box,(SI_Long)1L),workspace,
	    FIXNUM_ADD(x0_in_workspace,ISVREF(layer_box,(SI_Long)9L)),
	    FIXNUM_ADD(y0_in_workspace,ISVREF(layer_box,(SI_Long)10L)),T);
    add_to_workspace(5,ISVREF(layer_box,(SI_Long)2L),workspace,
	    FIXNUM_ADD(x0_in_workspace,ISVREF(layer_box,(SI_Long)11L)),
	    FIXNUM_ADD(y0_in_workspace,ISVREF(layer_box,(SI_Long)12L)),T);
    add_to_workspace(5,ISVREF(layer_box,(SI_Long)3L),workspace,
	    FIXNUM_ADD(x0_in_workspace,ISVREF(layer_box,(SI_Long)7L)),
	    FIXNUM_ADD(y0_in_workspace,ISVREF(layer_box,(SI_Long)8L)),T);
    color_qm = ISVREF(layer_box,(SI_Long)14L);
    temp = ISVREF(layer_box,(SI_Long)20L);
    temp = CDDR(temp);
    if (CAR(temp))
	change_color_of_item(ISVREF(layer_box,(SI_Long)3L),Nil,Qicon_color,
		 !TRUEP(color_qm) || EQ(color_qm,Qtransparent) || 
		EQ(color_qm,Qwhite) ? Qforeground : color_qm);
    return reset_y_midpoint_of_layer_box(layer_box);
}

/* PLACE-LAYER-BOX-IN-LAYERS-PAD */
Object place_layer_box_in_layers_pad(x0_in_layers_pad,y0_in_layers_pad,
	    layer_box,layers_pad,workspace)
    Object x0_in_layers_pad, y0_in_layers_pad, layer_box, layers_pad;
    Object workspace;
{
    Object x0_in_workspace, y0_in_workspace;

    x_note_fn_call(233,8);
    x0_in_workspace = FIXNUM_ADD(ISVREF(layers_pad,(SI_Long)5L),
	    x0_in_layers_pad);
    y0_in_workspace = FIXNUM_ADD(ISVREF(layers_pad,(SI_Long)6L),
	    y0_in_layers_pad);
    return place_layer_box_in_workspace(x0_in_workspace,y0_in_workspace,
	    layer_box,layers_pad,workspace);
}

/* MOVE-LAYER-BOX-IN-WORKSPACE */
Object move_layer_box_in_workspace(x_in_workspace,y_in_workspace,layer_box,
	    layers_pad)
    Object x_in_workspace, y_in_workspace, layer_box, layers_pad;
{
    Object workspace, gensymed_symbol_1, border_icon, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_2, delta_x, delta_y;

    x_note_fn_call(233,9);
    workspace = ISVREF(layers_pad,(SI_Long)7L);
    gensymed_symbol = IFIX(x_in_workspace);
    gensymed_symbol_1 = ISVREF(ISVREF(layer_box,(SI_Long)1L),(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    delta_x = gensymed_symbol - gensymed_symbol_2;
    gensymed_symbol_1 = ISVREF(ISVREF(layer_box,(SI_Long)1L),(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol = IFIX(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(y_in_workspace);
    delta_y = gensymed_symbol - gensymed_symbol_2;
    border_icon = ISVREF(layer_box,(SI_Long)1L);
    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(border_icon,(SI_Long)14L));
    gensymed_symbol_1 = gensymed_symbol_1 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) : Nil;
    if (EQ(gensymed_symbol_1,workspace)) {
	move_item_by(4,border_icon,FIX(delta_x),FIX(delta_y),Nil);
	move_item_by(4,ISVREF(layer_box,(SI_Long)2L),FIX(delta_x),
		FIX(delta_y),Nil);
	move_item_by(4,ISVREF(layer_box,(SI_Long)3L),FIX(delta_x),
		FIX(delta_y),Nil);
    }
    else {
	add_to_workspace(5,border_icon,workspace,x_in_workspace,
		y_in_workspace,T);
	add_to_workspace(5,ISVREF(layer_box,(SI_Long)2L),workspace,
		x_in_workspace,y_in_workspace,T);
	add_to_workspace(5,ISVREF(layer_box,(SI_Long)3L),workspace,
		x_in_workspace,y_in_workspace,T);
    }
    svref_new_value = FIXNUM_MINUS(x_in_workspace,ISVREF(layers_pad,
	    (SI_Long)5L));
    SVREF(layer_box,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = FIXNUM_MINUS(y_in_workspace,ISVREF(layers_pad,
	    (SI_Long)6L));
    SVREF(layer_box,FIX((SI_Long)6L)) = svref_new_value;
    return reset_y_midpoint_of_layer_box(layer_box);
}

/* MOVE-LAYER-BOX-IN-LAYERS-PAD */
Object move_layer_box_in_layers_pad(x_in_layers_pad,y_in_layers_pad,
	    layer_box,layers_pad)
    Object x_in_layers_pad, y_in_layers_pad, layer_box, layers_pad;
{
    x_note_fn_call(233,10);
    return move_layer_box_in_workspace(FIXNUM_ADD(x_in_layers_pad,
	    ISVREF(layers_pad,(SI_Long)5L)),FIXNUM_ADD(y_in_layers_pad,
	    ISVREF(layers_pad,(SI_Long)6L)),layer_box,layers_pad);
}

/* HEURISTICALLY-COMPUTE-MAXIMUM-HEIGHT-OF-LAYERS-BOX */
Object heuristically_compute_maximum_height_of_layers_box(number_of_layers)
    Object number_of_layers;
{
    x_note_fn_call(233,11);
    if (IFIX(number_of_layers) <= (SI_Long)2L)
	return VALUES_1(FIX((SI_Long)148L));
    else if (IFIX(number_of_layers) <= (SI_Long)3L)
	return VALUES_1(FIX((SI_Long)100L));
    else if (IFIX(number_of_layers) <= (SI_Long)4L)
	return VALUES_1(FIX((SI_Long)75L));
    else if (IFIX(number_of_layers) <= (SI_Long)5L)
	return VALUES_1(FIX((SI_Long)50L));
    else if (IFIX(number_of_layers) <= (SI_Long)8L)
	return VALUES_1(FIX((SI_Long)25L));
    else if (IFIX(number_of_layers) <= (SI_Long)10L)
	return VALUES_1(FIX((SI_Long)20L));
    else if (IFIX(number_of_layers) <= (SI_Long)15L)
	return VALUES_1(FIX((SI_Long)20L));
    else
	return VALUES_1(FIX((SI_Long)15L));
}

/* HEURISTICALLY-COMPUTE-LAYERS-PAD-SCALE */
Object heuristically_compute_layers_pad_scale(icon_width,icon_height,
	    maximum_icon_width,maximum_icon_height)
    Object icon_width, icon_height, maximum_icon_width, maximum_icon_height;
{
    Object temp, temp_1;

    x_note_fn_call(233,12);
    if (FIXNUM_LE(icon_width,maximum_icon_width) && FIXNUM_LE(icon_height,
	    maximum_icon_height))
	return VALUES_1(FIX((SI_Long)4096L));
    else {
	temp = l_round(FIXNUM_TIMES(maximum_icon_height,
		FIX((SI_Long)4096L)),icon_height);
	temp_1 = l_round(FIXNUM_TIMES(maximum_icon_width,
		FIX((SI_Long)4096L)),icon_width);
	return VALUES_1(FIXNUM_MIN(temp,temp_1));
    }
}

/* DELETE-ALL-LAYER-BOXES */
Object delete_all_layer_boxes(layers)
    Object layers;
{
    Object layer, ab_loop_list_;

    x_note_fn_call(233,13);
    layer = Nil;
    ab_loop_list_ = layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_icon_editor_slot_value(SECOND(layer));
    M_SECOND(layer) = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECOMPUTE-SCALE-FOR-LAYERS-PAD */
Object recompute_scale_for_layers_pad(icon_editor)
    Object icon_editor;
{
    Object engine, layers_pad, icon_width, icon_height, new_maximum_height;
    Object scale;

    x_note_fn_call(233,14);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    icon_width = ISVREF(engine,(SI_Long)1L);
    icon_height = ISVREF(engine,(SI_Long)2L);
    new_maximum_height = 
	    heuristically_compute_maximum_height_of_layers_box(ISVREF(engine,
	    (SI_Long)5L));
    if (FIXNUM_NE(new_maximum_height,ISVREF(layers_pad,(SI_Long)11L))) {
	SVREF(layers_pad,FIX((SI_Long)11L)) = new_maximum_height;
	delete_all_layer_boxes(ISVREF(engine,(SI_Long)3L));
    }
    scale = heuristically_compute_layers_pad_scale(icon_width,icon_height,
	    ISVREF(layers_pad,(SI_Long)10L),ISVREF(layers_pad,(SI_Long)11L));
    SVREF(layers_pad,FIX((SI_Long)8L)) = scale;
    return VALUES_1(SVREF(layers_pad,FIX((SI_Long)9L)) = scale);
}

/* MOVE-OR-PLACE-LAYER-BOX-IN-WORKSPACE */
Object move_or_place_layer_box_in_workspace(icon_editor,layer,layer_index,
	    x_in_workspace,y_in_workspace)
    Object icon_editor, layer, layer_index, x_in_workspace, y_in_workspace;
{
    Object layer_box_qm, layers_pad, workspace, gensymed_symbol;

    x_note_fn_call(233,15);
    layer_box_qm = SECOND(layer);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    workspace = ISVREF(icon_editor,(SI_Long)4L);
    if (layer_box_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(layer_box_qm,
		(SI_Long)1L),(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if (EQ(gensymed_symbol,workspace))
	    return move_layer_box_in_workspace(x_in_workspace,
		    y_in_workspace,layer_box_qm,layers_pad);
	else
	    return place_layer_box_in_workspace(x_in_workspace,
		    y_in_workspace,layer_box_qm,layers_pad,workspace);
    }
    else {
	layer_box_qm = create_layer_box(icon_editor,layer,layer_index,
		ISVREF(layers_pad,(SI_Long)8L),ISVREF(layers_pad,(SI_Long)9L));
	M_SECOND(layer) = layer_box_qm;
	return place_layer_box_in_workspace(x_in_workspace,y_in_workspace,
		layer_box_qm,layers_pad,workspace);
    }
}

/* MOVE-OR-PLACE-LAYER-BOX-IN-LAYERS-PAD */
Object move_or_place_layer_box_in_layers_pad(icon_editor,layer,layer_index,
	    x_in_layers_pad,y_in_layers_pad)
    Object icon_editor, layer, layer_index, x_in_layers_pad, y_in_layers_pad;
{
    Object layers_pad, x_in_workspace, y_in_workspace;

    x_note_fn_call(233,16);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    x_in_workspace = FIXNUM_ADD(ISVREF(layers_pad,(SI_Long)5L),
	    x_in_layers_pad);
    y_in_workspace = FIXNUM_ADD(ISVREF(layers_pad,(SI_Long)6L),
	    y_in_layers_pad);
    return move_or_place_layer_box_in_workspace(icon_editor,layer,
	    layer_index,x_in_workspace,y_in_workspace);
}

/* DELETE-LAYER-BOX-LABEL-IF-NECESSARY */
Object delete_layer_box_label_if_necessary(layer)
    Object layer;
{
    Object layer_box_qm;

    x_note_fn_call(233,17);
    layer_box_qm = SECOND(layer);
    if (layer_box_qm &&  !EQ(FIRST(layer),ISVREF(layer_box_qm,(SI_Long)15L))) {
	reclaim_icon_editor_slot_value(layer_box_qm);
	M_SECOND(layer) = Nil;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLE-REDRAWING-LAYERS-IN-LAYERS-PAD */
Object handle_redrawing_layers_in_layers_pad(icon_editor)
    Object icon_editor;
{
    Object layers_pad, engine, layers, bounding_box, current_layer;
    Object maximum_y_in_layers_pad, layer_box, layer_index, layer;
    Object ab_loop_list_, block, gensymed_symbol, y_in_layers_pad;
    Object reversed_layers, color, temp, svref_new_value, color_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, incff_1_arg;
    SI_Long maximum_y_in_layers_pad_new_value, x_in_layers_pad;
    SI_Long gensymed_symbol_3;

    x_note_fn_call(233,18);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers = ISVREF(engine,(SI_Long)3L);
    bounding_box = ISVREF(layers_pad,(SI_Long)3L);
    current_layer = ISVREF(engine,(SI_Long)6L);
    maximum_y_in_layers_pad = FIX((SI_Long)0L);
    layer_box = Nil;
    layer_index = FIX((SI_Long)0L);
    layer = Nil;
    ab_loop_list_ = layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    layer_box = get_or_create_layer_box(icon_editor,layer,layer_index);
    block = ISVREF(layer_box,(SI_Long)1L);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    incff_1_arg = gensymed_symbol_1 + gensymed_symbol_2;
    maximum_y_in_layers_pad_new_value = IFIX(maximum_y_in_layers_pad) + 
	    incff_1_arg;
    maximum_y_in_layers_pad = FIX(maximum_y_in_layers_pad_new_value);
    layer_index = FIXNUM_ADD1(layer_index);
    goto next_loop;
  end_loop:;
    update_border_of_bounding_box(bounding_box,Nil,Nil,Nil,
	    FIX(IFIX(FIXNUM_ADD1(ISVREF(layers_pad,(SI_Long)6L))) + 
	    IFIX(maximum_y_in_layers_pad)));
    x_in_layers_pad = (SI_Long)0L;
    y_in_layers_pad = FIX((SI_Long)0L);
    reversed_layers = reverse_using_icon_editor_conses(layers);
    layer_index = ISVREF(engine,(SI_Long)5L);
    layer_box = Nil;
    layer = Nil;
    ab_loop_list_ = reversed_layers;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    layer_index = FIXNUM_SUB1(layer_index);
    delete_layer_box_label_if_necessary(layer);
    move_or_place_layer_box_in_layers_pad(icon_editor,layer,layer_index,
	    FIX(x_in_layers_pad),y_in_layers_pad);
    layer_box = SECOND(layer);
    if (EQ(current_layer,layer)) {
	color = ISVREF(layer_box,(SI_Long)14L);
	if (color);
	else
	    color = Qforeground;
	change_color_of_item(ISVREF(layer_box,(SI_Long)1L),Nil,Qborder,
		EQ(color,Qwhite) || EQ(color,Qtransparent) ? Qforeground : 
		color);
    }
    else
	change_color_of_item(ISVREF(layer_box,(SI_Long)1L),Nil,Qborder,
		Qtransparent);
    temp = assq_function(FIRST(layer),ISVREF(icon_editor,(SI_Long)6L));
    svref_new_value = CDR(temp);
    SVREF(layer_box,FIX((SI_Long)14L)) = svref_new_value;
    color_qm = ISVREF(layer_box,(SI_Long)14L);
    temp = ISVREF(layer_box,(SI_Long)20L);
    temp = CDDR(temp);
    if (CAR(temp))
	change_color_of_item(ISVREF(layer_box,(SI_Long)3L),Nil,Qicon_color,
		 !TRUEP(color_qm) || EQ(color_qm,Qtransparent) || 
		EQ(color_qm,Qwhite) ? Qforeground : color_qm);
    gensymed_symbol_1 = IFIX(y_in_layers_pad);
    block = ISVREF(layer_box,(SI_Long)1L);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)1L;
    y_in_layers_pad = FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
	    gensymed_symbol_3);
    goto next_loop_1;
  end_loop_1:;
    return reclaim_icon_editor_list_1(reversed_layers);
}

/* HANDLE-MOVING-LAYER-BOX-IN-LAYERS-PAD */
Object handle_moving_layer_box_in_layers_pad(icon_editor,x_in_layers_pad,
	    y_in_layers_pad)
    Object icon_editor, x_in_layers_pad, y_in_layers_pad;
{
    Object engine, layers_pad, temp, layer_box_qm;

    x_note_fn_call(233,19);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    temp = ISVREF(engine,(SI_Long)6L);
    layer_box_qm = SECOND(temp);
    if (layer_box_qm) {
	move_layer_box_in_layers_pad(x_in_layers_pad,y_in_layers_pad,
		layer_box_qm,layers_pad);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLE-RESIZING-LAYER-BOXES-IF-NECESSARY */
Object handle_resizing_layer_boxes_if_necessary(icon_editor)
    Object icon_editor;
{
    x_note_fn_call(233,20);
    recompute_scale_for_layers_pad(icon_editor);
    return handle_redrawing_layers_in_layers_pad(icon_editor);
}

/* REDRAW-LABEL-BOX */
Object redraw_label_box(icon_editor,layer,layer_index)
    Object icon_editor, layer, layer_index;
{
    Object engine, old_layer_box_qm, layer_box, gensymed_symbol;
    Object x_in_workspace, y_in_workspace, color;

    x_note_fn_call(233,21);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    old_layer_box_qm = SECOND(layer);
    M_SECOND(layer) = Nil;
    layer_box = get_or_create_layer_box(icon_editor,layer,layer_index);
    if (old_layer_box_qm) {
	gensymed_symbol = ISVREF(ISVREF(old_layer_box_qm,(SI_Long)1L),
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	x_in_workspace = gensymed_symbol;
	gensymed_symbol = ISVREF(ISVREF(old_layer_box_qm,(SI_Long)1L),
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	y_in_workspace = gensymed_symbol;
	reclaim_icon_editor_slot_value(old_layer_box_qm);
	place_layer_box_in_workspace(x_in_workspace,y_in_workspace,
		layer_box,ISVREF(icon_editor,(SI_Long)13L),
		ISVREF(icon_editor,(SI_Long)4L));
	if (EQ(ISVREF(engine,(SI_Long)6L),layer)) {
	    color = ISVREF(layer_box,(SI_Long)14L);
	    if (color);
	    else
		color = Qforeground;
	    return change_color_of_item(ISVREF(layer_box,(SI_Long)1L),Nil,
		    Qborder,EQ(color,Qwhite) || EQ(color,Qtransparent) ? 
		    Qforeground : color);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return handle_redrawing_layers_in_layers_pad(icon_editor);
}

/* HANDLE-CHANGING-LABEL-OF-LAYER-IN-LAYERS-PAD */
Object handle_changing_label_of_layer_in_layers_pad(icon_editor,
	    layer_index,label)
    Object icon_editor, layer_index, label;
{
    Object engine, layer, old_layer_box_qm;

    x_note_fn_call(233,22);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layer = nth(layer_index,ISVREF(engine,(SI_Long)3L));
    old_layer_box_qm = SECOND(layer);
    M_SECOND(layer) = Nil;
    reclaim_icon_editor_slot_value(old_layer_box_qm);
    return redraw_label_box(icon_editor,layer,layer_index);
}

/* PICK-LAYER-IN-LAYERS-PAD */
Object pick_layer_in_layers_pad(icon_editor,x_in_workspace,y_in_workspace)
    Object icon_editor, x_in_workspace, y_in_workspace;
{
    Object engine, layers, reversed_layers, layers_pad, top_layer_index;
    Object number_of_layers, layer_box_picked_p, old_layer_index, index_1;
    Object layer_box_qm, layer, ab_loop_list_, gensymed_symbol;
    char temp;

    x_note_fn_call(233,23);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers = ISVREF(engine,(SI_Long)3L);
    reversed_layers = reverse_using_icon_editor_conses(layers);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    top_layer_index = ISVREF(layers_pad,(SI_Long)13L);
    number_of_layers = ISVREF(engine,(SI_Long)5L);
    layer_box_picked_p = Nil;
    old_layer_index = ISVREF(engine,(SI_Long)7L);
    index_1 = number_of_layers;
    layer_box_qm = Nil;
    layer = Nil;
    ab_loop_list_ = reversed_layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    index_1 = FIXNUM_SUB1(index_1);
    layer_box_qm = SECOND(layer);
    if (layer_box_qm && FIXNUM_LE(index_1,top_layer_index)) {
	gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)1L),
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	if (FIXNUM_LE(gensymed_symbol,x_in_workspace)) {
	    gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)1L),
		    (SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp = FIXNUM_LT(x_in_workspace,gensymed_symbol);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)1L),
		    (SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp = FIXNUM_LE(gensymed_symbol,y_in_workspace);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(ISVREF(layer_box_qm,(SI_Long)1L),
		    (SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp = FIXNUM_LT(y_in_workspace,gensymed_symbol);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (FIXNUM_NE(index_1,old_layer_index))
		enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)14L),index_1,Nil);
	    layer_box_picked_p = T;
	    goto end_1;
	}
    }
    goto next_loop;
  end_loop:
  end_1:;
    reclaim_icon_editor_list_1(reversed_layers);
    if (layer_box_picked_p)
	return VALUES_1(ISVREF(engine,(SI_Long)6L));
    else
	return VALUES_1(Nil);
}

/* HANDLE-LAYERS-PAD-MOUSE-MOTION */
Object handle_layers_pad_mouse_motion(icon_editor,cursor_x_in_workspace,
	    cursor_y_in_workspace)
    Object icon_editor, cursor_x_in_workspace, cursor_y_in_workspace;
{
    Object engine, layers_pad, layer, layer_index, layer_box_qm, x_offset_qm;
    Object y_offset_qm, desired_new_left_edge_in_workspace;
    Object minimum_new_left_edge_in_workspace, block, gensymed_symbol_1;
    Object new_left_edge_in_workspace, new_top_edge_in_workspace;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long maximum_new_left_edge_in_workspace, new_bottom_edge_in_workspace;
    SI_Long adjusted_bounding_box_border_width, y_min_limit, y_max_limit;

    x_note_fn_call(233,24);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    layer = ISVREF(engine,(SI_Long)6L);
    layer_index = ISVREF(engine,(SI_Long)7L);
    layer_box_qm = SECOND(layer);
    if (layer_box_qm) {
	x_offset_qm = ISVREF(layer_box_qm,(SI_Long)17L);
	y_offset_qm = ISVREF(layer_box_qm,(SI_Long)18L);
	if (x_offset_qm && y_offset_qm) {
	    desired_new_left_edge_in_workspace = 
		    FIXNUM_MINUS(cursor_x_in_workspace,x_offset_qm);
	    minimum_new_left_edge_in_workspace = ISVREF(layers_pad,
		    (SI_Long)5L);
	    gensymed_symbol = IFIX(minimum_new_left_edge_in_workspace);
	    block = ISVREF(layers_pad,(SI_Long)3L);
	    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    maximum_new_left_edge_in_workspace = gensymed_symbol + 
		    gensymed_symbol_2;
	    if (IFIX(desired_new_left_edge_in_workspace) > 
		    maximum_new_left_edge_in_workspace)
		new_left_edge_in_workspace = 
			FIX(maximum_new_left_edge_in_workspace);
	    else if (FIXNUM_LT(desired_new_left_edge_in_workspace,
		    minimum_new_left_edge_in_workspace))
		new_left_edge_in_workspace = 
			minimum_new_left_edge_in_workspace;
	    else
		new_left_edge_in_workspace = 
			desired_new_left_edge_in_workspace;
	    new_top_edge_in_workspace = FIXNUM_MINUS(cursor_y_in_workspace,
		    y_offset_qm);
	    gensymed_symbol = IFIX(new_top_edge_in_workspace);
	    block = ISVREF(layer_box_qm,(SI_Long)1L);
	    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    new_bottom_edge_in_workspace = gensymed_symbol + gensymed_symbol_2;
	    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
	    adjusted_bounding_box_border_width = (SI_Long)0L;
	    gensymed_symbol_1 = ISVREF(ISVREF(layers_pad,(SI_Long)3L),
		    (SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_1);
	    gensymed_symbol_2 = adjusted_bounding_box_border_width;
	    y_min_limit = gensymed_symbol + gensymed_symbol_2;
	    gensymed_symbol_1 = ISVREF(ISVREF(layers_pad,(SI_Long)3L),
		    (SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_1);
	    gensymed_symbol_2 = adjusted_bounding_box_border_width;
	    y_max_limit = gensymed_symbol - gensymed_symbol_2;
	    if (IFIX(new_top_edge_in_workspace) < y_min_limit)
		new_top_edge_in_workspace = FIX(y_min_limit);
	    else if (new_bottom_edge_in_workspace > y_max_limit) {
		gensymed_symbol = y_max_limit;
		block = ISVREF(layer_box_qm,(SI_Long)1L);
		gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		new_top_edge_in_workspace = FIX(gensymed_symbol - 
			gensymed_symbol_2);
	    }
	    move_or_place_layer_box_in_workspace(icon_editor,layer,
		    layer_index,new_left_edge_in_workspace,
		    new_top_edge_in_workspace);
	}
    }
    return VALUES_1(Nil);
}

/* COMPUTE-NEW-LAYER-INDEX-FROM-NEW-POSITION */
Object compute_new_layer_index_from_new_position(icon_editor,
	    layer_box_to_check)
    Object icon_editor, layer_box_to_check;
{
    Object engine, layers, layers_pad, gensymed_symbol;
    Object above_layer_box_to_check_p, previous_layer_box_qm;
    Object last_matching_layer_box_qm, layer_box_qm, layer_index, layer;
    Object ab_loop_list_;
    SI_Long visible_top_layer_index, visible_bottom_layer_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, y_midpoint_in_workspace;
    SI_Long temp;

    x_note_fn_call(233,25);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layers = ISVREF(engine,(SI_Long)3L);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    visible_top_layer_index = IFIX(ISVREF(layers_pad,(SI_Long)13L));
    visible_bottom_layer_index = IFIX(ISVREF(layers_pad,(SI_Long)14L));
    gensymed_symbol = ISVREF(ISVREF(layer_box_to_check,(SI_Long)1L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(ISVREF(layer_box_to_check,(SI_Long)1L),
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    y_midpoint_in_workspace = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    above_layer_box_to_check_p = Nil;
    previous_layer_box_qm = Nil;
    last_matching_layer_box_qm = Nil;
    layer_box_qm = Nil;
    layer_index = FIX((SI_Long)0L);
    layer = Nil;
    ab_loop_list_ = layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (visible_bottom_layer_index <= IFIX(layer_index) && 
	    IFIX(layer_index) <= visible_top_layer_index) {
	layer_box_qm = SECOND(layer);
	if (layer_box_qm) {
	    if (y_midpoint_in_workspace >= (EQ(layer_box_qm,
		    layer_box_to_check) ? IFIX(ISVREF(layer_box_qm,
		    (SI_Long)19L)) : IFIX(ISVREF(layer_box_qm,
			(SI_Long)13L)))) {
		if (above_layer_box_to_check_p) {
		    last_matching_layer_box_qm = previous_layer_box_qm;
		    goto end_1;
		}
		last_matching_layer_box_qm = layer_box_qm;
		if ( !TRUEP(above_layer_box_to_check_p))
		    goto end_1;
	    }
	    if (EQ(layer_box_qm,layer_box_to_check))
		above_layer_box_to_check_p = T;
	    previous_layer_box_qm = layer_box_qm;
	}
    }
    layer_index = FIXNUM_ADD1(layer_index);
    goto next_loop;
  end_loop:
  end_1:;
    if (last_matching_layer_box_qm)
	return VALUES_1(ISVREF(last_matching_layer_box_qm,(SI_Long)16L));
    else {
	temp = IFIX(FIXNUM_SUB1(ISVREF(engine,(SI_Long)5L)));
	return VALUES_1(FIX(MAX(temp,(SI_Long)0L)));
    }
}

/* TERMINATE-MOVING-LAYER-BOX */
Object terminate_moving_layer_box(icon_editor,x_in_workspace_qm,
	    y_in_workspace_qm)
    Object icon_editor, x_in_workspace_qm, y_in_workspace_qm;
{
    Object engine, translator, layer, layer_box_qm, x_offset_qm, y_offset_qm;
    Object old_index, new_index;

    x_note_fn_call(233,26);
    if (x_in_workspace_qm && y_in_workspace_qm)
	handle_layers_pad_mouse_motion(icon_editor,x_in_workspace_qm,
		y_in_workspace_qm);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    translator = ISVREF(icon_editor,(SI_Long)10L);
    layer = ISVREF(engine,(SI_Long)6L);
    layer_box_qm = SECOND(layer);
    if (layer_box_qm) {
	x_offset_qm = ISVREF(layer_box_qm,(SI_Long)17L);
	y_offset_qm = ISVREF(layer_box_qm,(SI_Long)18L);
	if (x_offset_qm && y_offset_qm) {
	    SVREF(layer_box_qm,FIX((SI_Long)17L)) = Nil;
	    SVREF(layer_box_qm,FIX((SI_Long)18L)) = Nil;
	    old_index = ISVREF(layer_box_qm,(SI_Long)16L);
	    new_index = 
		    compute_new_layer_index_from_new_position(icon_editor,
		    layer_box_qm);
	    ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)0L);
	    if (FIXNUM_NE(old_index,new_index))
		enqueue_icon_editor_translator_event(icon_editor,
			FIX((SI_Long)55L),old_index,new_index);
	    else
		handle_redrawing_layers_in_layers_pad(icon_editor);
	}
    }
    return VALUES_1(Nil);
}

/* HANDLE-LAYERS-PAD-VISUAL-EVENT */
Object handle_layers_pad_visual_event(icon_editor,visual_event,arg_1_qm,
	    arg_2_qm)
    Object icon_editor, visual_event, arg_1_qm, arg_2_qm;
{
    Object temp, engine, current_layer_index, layer_box, layer_index, layer;
    Object ab_loop_list_, color_qm, color, current_layer, layers, old_layer;
    Object new_layer;

    x_note_fn_call(233,27);
    temp = visual_event;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 27:
	    return handle_redrawing_layers_in_layers_pad(icon_editor);
	  case 28:
	    return handle_moving_layer_box_in_layers_pad(icon_editor,
		    arg_1_qm,arg_2_qm);
	  case 29:
	    return handle_resizing_layer_boxes_if_necessary(icon_editor);
	  case 30:
	    return VALUES_1(Nil);
	  case 31:
	    engine = ISVREF(icon_editor,(SI_Long)11L);
	    if (arg_1_qm) {
		current_layer_index = ISVREF(engine,(SI_Long)7L);
		layer_box = Nil;
		layer_index = FIX((SI_Long)0L);
		layer = Nil;
		ab_loop_list_ = ISVREF(engine,(SI_Long)3L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		layer = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (delete_layer_box_label_if_necessary(layer)) {
		    handle_redrawing_layers_in_layers_pad(icon_editor);
		    return VALUES_1(Nil);
		}
		if (EQ(FIRST(layer),arg_1_qm)) {
		    layer_box = get_or_create_layer_box(icon_editor,layer,
			    layer_index);
		    SVREF(layer_box,FIX((SI_Long)14L)) = arg_2_qm;
		    color_qm = ISVREF(layer_box,(SI_Long)14L);
		    temp = ISVREF(layer_box,(SI_Long)20L);
		    temp = CDDR(temp);
		    if (CAR(temp))
			change_color_of_item(ISVREF(layer_box,(SI_Long)3L),
				Nil,Qicon_color, !TRUEP(color_qm) || 
				EQ(color_qm,Qtransparent) || EQ(color_qm,
				Qwhite) ? Qforeground : color_qm);
		    if (FIXNUM_EQ(current_layer_index,ISVREF(layer_box,
			    (SI_Long)16L))) {
			color = ISVREF(layer_box,(SI_Long)14L);
			if (color);
			else
			    color = Qforeground;
			change_color_of_item(ISVREF(layer_box,(SI_Long)1L),
				Nil,Qborder,EQ(color,Qwhite) || EQ(color,
				Qtransparent) ? Qforeground : color);
		    }
		}
		layer_index = FIXNUM_ADD1(layer_index);
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	    else {
		current_layer = ISVREF(engine,(SI_Long)6L);
		current_layer_index = ISVREF(engine,(SI_Long)7L);
		if (delete_layer_box_label_if_necessary(current_layer))
		    return redraw_label_box(icon_editor,current_layer,
			    current_layer_index);
		else
		    return VALUES_1(Nil);
	    }
	  case 32:
	    return VALUES_1(Nil);
	  case 33:
	    return handle_changing_label_of_layer_in_layers_pad(icon_editor,
		    arg_1_qm,arg_2_qm);
	  case 34:
	    engine = ISVREF(icon_editor,(SI_Long)11L);
	    layers = ISVREF(engine,(SI_Long)3L);
	    old_layer = nth(arg_1_qm,layers);
	    new_layer = nth(arg_2_qm,layers);
	    layer_box = get_or_create_layer_box(icon_editor,new_layer,
		    arg_2_qm);
	    color = ISVREF(layer_box,(SI_Long)14L);
	    if (color);
	    else
		color = Qforeground;
	    change_color_of_item(ISVREF(layer_box,(SI_Long)1L),Nil,Qborder,
		    EQ(color,Qwhite) || EQ(color,Qtransparent) ? 
		    Qforeground : color);
	    layer_box = get_or_create_layer_box(icon_editor,old_layer,
		    arg_1_qm);
	    return change_color_of_item(ISVREF(layer_box,(SI_Long)1L),Nil,
		    Qborder,Qtransparent);
	  case 35:
	    engine = ISVREF(icon_editor,(SI_Long)11L);
	    layer_index = ISVREF(engine,(SI_Long)7L);
	    layer = nth(layer_index,ISVREF(engine,(SI_Long)3L));
	    return redraw_label_box(icon_editor,layer,layer_index);
	  case 36:
	    return handle_resizing_layer_boxes_if_necessary(icon_editor);
	  case 37:
	    layer = nth(arg_1_qm,ISVREF(ISVREF(icon_editor,(SI_Long)11L),
		    (SI_Long)3L));
	    layer_box = get_or_create_layer_box(icon_editor,layer,arg_1_qm);
	    SVREF(layer_box,FIX((SI_Long)14L)) = arg_2_qm;
	    color_qm = ISVREF(layer_box,(SI_Long)14L);
	    temp = ISVREF(layer_box,(SI_Long)20L);
	    temp = CDDR(temp);
	    if (CAR(temp))
		return change_color_of_item(ISVREF(layer_box,(SI_Long)3L),
			Nil,Qicon_color, !TRUEP(color_qm) || EQ(color_qm,
			Qtransparent) || EQ(color_qm,Qwhite) ? Qforeground 
			: color_qm);
	    else
		return VALUES_1(Nil);
	  case 38:
	    delete_all_layer_boxes(ISVREF(ISVREF(icon_editor,(SI_Long)11L),
		    (SI_Long)3L));
	    return handle_resizing_layer_boxes_if_necessary(icon_editor);
	  default:
	    return VALUES_1(Nil);
	}
}

/* HANDLE-LAYERS-PAD-TRANSLATOR-EVENT */
Object handle_layers_pad_translator_event(icon_editor,translator_event,
	    arg_1_qm,arg_2_qm)
    Object icon_editor, translator_event, arg_1_qm, arg_2_qm;
{
    Object translator, temp, layer_qm, layer_box_qm, svref_new_value;
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2, svref_new_value_1;

    x_note_fn_call(233,28);
    translator = ISVREF(icon_editor,(SI_Long)10L);
    temp = translator_event;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(T);
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    return handle_layers_pad_mouse_motion(icon_editor,arg_1_qm,
		    arg_2_qm);
	  case 3:
	    if (IFIX(ISVREF(translator,(SI_Long)1L)) != (SI_Long)18L) {
		translator = ISVREF(icon_editor,(SI_Long)10L);
		layer_qm = pick_layer_in_layers_pad(icon_editor,arg_1_qm,
			arg_2_qm);
		if (layer_qm) {
		    ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)18L);
		    layer_box_qm = SECOND(layer_qm);
		    if (layer_box_qm) {
			svref_new_value = ISVREF(layer_box_qm,(SI_Long)13L);
			SVREF(layer_box_qm,FIX((SI_Long)19L)) = 
				svref_new_value;
			gensymed_symbol = IFIX(arg_1_qm);
			gensymed_symbol_1 = ISVREF(ISVREF(layer_box_qm,
				(SI_Long)1L),(SI_Long)14L);
			gensymed_symbol_1 = gensymed_symbol_1 ? 
				ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol_1);
			svref_new_value_1 = gensymed_symbol - 
				gensymed_symbol_2;
			ISVREF(layer_box_qm,(SI_Long)17L) = 
				FIX(svref_new_value_1);
			gensymed_symbol = IFIX(arg_2_qm);
			gensymed_symbol_1 = ISVREF(ISVREF(layer_box_qm,
				(SI_Long)1L),(SI_Long)14L);
			gensymed_symbol_1 = gensymed_symbol_1 ? 
				ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol_1);
			svref_new_value_1 = gensymed_symbol - 
				gensymed_symbol_2;
			ISVREF(layer_box_qm,(SI_Long)18L) = 
				FIX(svref_new_value_1);
		    }
		}
		else
		    ISVREF(translator,(SI_Long)1L) = FIX((SI_Long)0L);
		return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	  case 4:
	  case 2:
	    terminate_moving_layer_box(icon_editor,arg_1_qm,arg_2_qm);
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(T);
	}
}

static Object Qinfo_box;           /* info-box */

static Object Qsize_table;         /* size-table */

static Object Qlabel_table;        /* label-table */

static Object Qx_position_box;     /* x-position-box */

static Object Qy_position_box;     /* y-position-box */

static Object Qx_y_position_box;   /* x-y-position-box */

/* CREATE-ICON-EDITOR-TABLES */
Object create_icon_editor_tables()
{
    Object tables, info_box_qm, size_table_qm, label_table_qm;
    Object x_y_position_box_qm, x_position_box_qm, y_position_box_qm;
    Object name_of_table, names_of_slots, table_coordinate, use_small_fonts_qm;
    Object table, element, ab_loop_list_;

    x_note_fn_call(233,29);
    tables = Nil;
    info_box_qm = Nil;
    size_table_qm = Nil;
    label_table_qm = Nil;
    x_y_position_box_qm = Nil;
    x_position_box_qm = Nil;
    y_position_box_qm = Nil;
    name_of_table = Nil;
    names_of_slots = Nil;
    table_coordinate = Nil;
    use_small_fonts_qm = Nil;
    table = Nil;
    element = Nil;
    ab_loop_list_ = Icon_editor_tables_specification_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name_of_table = FIRST(element);
    names_of_slots = SECOND(element);
    table_coordinate = THIRD(element);
    use_small_fonts_qm = FOURTH(element);
    table = create_icon_editor_table(FIRST(table_coordinate),
	    SECOND(table_coordinate),
	    copy_list_using_icon_editor_conses_1(names_of_slots),
	    use_small_fonts_qm);
    if (EQ(name_of_table,Qinfo_box))
	info_box_qm = table;
    else if (EQ(name_of_table,Qsize_table))
	size_table_qm = table;
    else if (EQ(name_of_table,Qlabel_table))
	label_table_qm = table;
    else if (EQ(name_of_table,Qx_position_box))
	x_position_box_qm = table;
    else if (EQ(name_of_table,Qy_position_box))
	y_position_box_qm = table;
    else if (EQ(name_of_table,Qx_y_position_box))
	x_y_position_box_qm = table;
    tables = icon_editor_cons_1(table,tables);
    goto next_loop;
  end_loop:;
    return VALUES_7(tables,info_box_qm,size_table_qm,label_table_qm,
	    x_position_box_qm,y_position_box_qm,x_y_position_box_qm);
}

static Object Qicon_editor_workspace;  /* icon-editor-workspace */

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qicon_editor;        /* icon-editor */

static Object Qbutton_action_data_qm;  /* button-action-data? */

/* CREATE-ICON-EDITOR */
Object create_icon_editor(class_definition)
    Object class_definition;
{
    Object workspace, icon_editor, caption_text, bounding_box, view_pad;
    Object bounding_box_border_width, x_in_workspace, y_in_workspace;
    Object x_origin_in_workspace, y_origin_in_workspace, gensymed_symbol;
    Object scale, temp, border_width, layers_pad, buttons, translator_event;
    Object text_or_button_class, button_coordinate, button, element;
    Object ab_loop_list_, tables, info_box, size_table, label_table;
    Object x_position_box, y_position_box, x_y_position_box, table;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value, value, unshifted_result, x_in_workspace_1;
    SI_Long y_in_workspace_1, twice_border_width, inner_width, inner_height;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(233,30);
    SAVE_STACK();
    workspace = make_workspace(4,Qicon_editor_workspace,Nil,Nil,
	    FIX((SI_Long)10L));
    icon_editor = make_icon_editor_1(class_definition,workspace,
	    copy_frame_serial_number(Current_frame_serial_number));
    if (New_g2_classic_ui_p) {
	caption_text = 
		make_caption_text_for_icon_editor_workspace(class_definition);
	change_slot_value(3,workspace,Qtitle_bar_caption_text,caption_text);
    }
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	push_item_to_end_of_current_localization_domains(Qicon_editor);
	bounding_box = make_bounding_box(FIX((SI_Long)110L),
		FIX((SI_Long)110L));
	view_pad = make_icon_editor_view_pad_1(FIX((SI_Long)320L),
		FIX((SI_Long)275L),bounding_box,
		copy_frame_serial_number(Current_frame_serial_number));
	SVREF(view_pad,FIX((SI_Long)12L)) = Nil;
	SVREF(icon_editor,FIX((SI_Long)12L)) = view_pad;
	view_pad = ISVREF(icon_editor,(SI_Long)12L);
	bounding_box = ISVREF(view_pad,(SI_Long)3L);
	bounding_box_border_width = FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,
		(SI_Long)17L),(SI_Long)44L));
	x_in_workspace = ISVREF(view_pad,(SI_Long)1L);
	y_in_workspace = ISVREF(view_pad,(SI_Long)2L);
	x_origin_in_workspace = FIXNUM_ADD(x_in_workspace,
		bounding_box_border_width);
	y_origin_in_workspace = FIXNUM_ADD(y_in_workspace,
		bounding_box_border_width);
	add_to_workspace(4,bounding_box,workspace,x_in_workspace,
		y_in_workspace);
	SVREF(view_pad,FIX((SI_Long)5L)) = x_origin_in_workspace;
	SVREF(view_pad,FIX((SI_Long)6L)) = y_origin_in_workspace;
	SVREF(view_pad,FIX((SI_Long)9L)) = workspace;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = IFIX(x_in_workspace);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	svref_new_value = MAX(gensymed_symbol_1,gensymed_symbol_2);
	ISVREF(view_pad,(SI_Long)7L) = FIX(svref_new_value);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = IFIX(y_in_workspace);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	svref_new_value = MAX(gensymed_symbol_1,gensymed_symbol_2);
	ISVREF(view_pad,(SI_Long)8L) = FIX(svref_new_value);
	scale = ISVREF(view_pad,(SI_Long)10L);
	value = (SI_Long)100L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	scale = ISVREF(view_pad,(SI_Long)11L);
	value = (SI_Long)100L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
	update_border_of_bounding_box(bounding_box,Nil,Nil,temp,
		FIX(gensymed_symbol_1 + gensymed_symbol_2));
	x_in_workspace_1 = (SI_Long)100L;
	y_in_workspace_1 = (SI_Long)150L;
	bounding_box = make_bounding_box(FIX((SI_Long)160L),
		FIX((SI_Long)160L));
	border_width = FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,
		(SI_Long)17L),(SI_Long)44L));
	twice_border_width = IFIX(border_width) << (SI_Long)1L;
	layers_pad = make_icon_editor_layers_pad_1(FIX(x_in_workspace_1),
		FIX(y_in_workspace_1),bounding_box,
		copy_frame_serial_number(Current_frame_serial_number));
	svref_new_value = x_in_workspace_1 + IFIX(border_width);
	ISVREF(layers_pad,(SI_Long)5L) = FIX(svref_new_value);
	svref_new_value = y_in_workspace_1 + IFIX(border_width);
	ISVREF(layers_pad,(SI_Long)6L) = FIX(svref_new_value);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = twice_border_width;
	gensymed_symbol_3 = (SI_Long)1L;
	inner_width = gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = twice_border_width;
	inner_height = gensymed_symbol_1 - gensymed_symbol_2;
	ISVREF(layers_pad,(SI_Long)15L) = FIX(inner_width);
	svref_new_value = inner_width - (SI_Long)10L - (SI_Long)2L;
	ISVREF(layers_pad,(SI_Long)10L) = FIX(svref_new_value);
	ISVREF(layers_pad,(SI_Long)11L) = FIX(inner_height);
	SVREF(icon_editor,FIX((SI_Long)13L)) = layers_pad;
	layers_pad = ISVREF(icon_editor,(SI_Long)13L);
	SVREF(layers_pad,FIX((SI_Long)7L)) = workspace;
	add_to_workspace(4,ISVREF(layers_pad,(SI_Long)3L),workspace,
		ISVREF(layers_pad,(SI_Long)1L),ISVREF(layers_pad,(SI_Long)2L));
	buttons = Nil;
	translator_event = Nil;
	text_or_button_class = Nil;
	button_coordinate = Nil;
	button = Nil;
	element = Nil;
	ab_loop_list_ = Icon_editor_buttons_specification_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	translator_event = FIRST(element);
	text_or_button_class = SECOND(element);
	button_coordinate = THIRD(element);
	button = create_icon_editor_button(FIRST(button_coordinate),
		SECOND(button_coordinate),text_or_button_class);
	set_non_savable_lookup_slot_value(ISVREF(button,(SI_Long)5L),
		Qbutton_action_data_qm,translator_event);
	buttons = icon_editor_cons_1(button,buttons);
	goto next_loop;
      end_loop:;
	SVREF(icon_editor,FIX((SI_Long)14L)) = buttons;
	buttons = ISVREF(icon_editor,(SI_Long)14L);
	button = Nil;
	ab_loop_list_ = buttons;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	button = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_to_workspace(4,ISVREF(button,(SI_Long)5L),workspace,
		ISVREF(button,(SI_Long)1L),ISVREF(button,(SI_Long)2L));
	goto next_loop_1;
      end_loop_1:;
	result = create_icon_editor_tables();
	MVS_7(result,tables,info_box,size_table,label_table,x_position_box,
		y_position_box,x_y_position_box);
	SVREF(icon_editor,FIX((SI_Long)15L)) = tables;
	SVREF(icon_editor,FIX((SI_Long)16L)) = info_box;
	SVREF(icon_editor,FIX((SI_Long)17L)) = size_table;
	SVREF(icon_editor,FIX((SI_Long)18L)) = label_table;
	SVREF(icon_editor,FIX((SI_Long)19L)) = x_position_box;
	SVREF(icon_editor,FIX((SI_Long)20L)) = y_position_box;
	SVREF(icon_editor,FIX((SI_Long)21L)) = x_y_position_box;
	tables = ISVREF(icon_editor,(SI_Long)15L);
	table = Nil;
	ab_loop_list_ = tables;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	table = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_to_workspace(4,ISVREF(table,(SI_Long)6L),workspace,
		ISVREF(table,(SI_Long)1L),ISVREF(table,(SI_Long)2L));
	goto next_loop_2;
      end_loop_2:;
	SAVE_VALUES(VALUES_1(icon_editor));
	remove_last_item_in_current_localization_domains();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_21;  /* "Icon Editor for ~NF" */

/* MAKE-CAPTION-TEXT-FOR-ICON-EDITOR-WORKSPACE */
Object make_caption_text_for_icon_editor_workspace(class_definition)
    Object class_definition;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, gensym_list_of_wide_strings, string_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object svref_new_value, gensymed_symbol, short_string, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(233,31);
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
	      tformat(2,string_constant_21,class_definition);
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
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
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
    goto next_loop;
  end_loop:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp_2);
}

static Object Qtext;               /* text */

/* CLEANUP-ICON-EDITOR */
Object cleanup_icon_editor(icon_editor)
    Object icon_editor;
{
    Object reference_serial_number, translator, engine, gensymed_symbol, x, xa;
    Object ya, view_pad, bounding_box, iconic_entity_qm, serial_number;
    Object layers_pad, buttons, button, ab_loop_list_, tables, table, layer;
    Object drawing_elements, drawing_element_list, ab_loop_list__1;
    Object drawing_element;
    char temp;

    x_note_fn_call(233,32);
    reference_serial_number = ISVREF(icon_editor,(SI_Long)5L);
    reclaim_icon_editor_slot_value(ISVREF(icon_editor,(SI_Long)6L));
    SVREF(icon_editor,FIX((SI_Long)6L)) = Nil;
    reclaim_icon_editor_slot_value(ISVREF(icon_editor,(SI_Long)7L));
    SVREF(icon_editor,FIX((SI_Long)7L)) = Nil;
    translator = ISVREF(icon_editor,(SI_Long)10L);
    reclaim_icon_editor_slot_value(ISVREF(translator,(SI_Long)2L));
    reclaim_icon_editor_translator_1(translator);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    reclaim_icon_editor_engine_1(engine);
    gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)4L),(SI_Long)3L);
    x = ISVREF(icon_editor,(SI_Long)4L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
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
    if ( !temp)
	delete_frame(ISVREF(icon_editor,(SI_Long)4L));
    reclaim_frame_serial_number(reference_serial_number);
    SVREF(icon_editor,FIX((SI_Long)5L)) = Nil;
    reclaim_frame_serial_number(ISVREF(icon_editor,(SI_Long)27L));
    SVREF(icon_editor,FIX((SI_Long)27L)) = Nil;
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    bounding_box = ISVREF(view_pad,(SI_Long)3L);
    reference_serial_number = ISVREF(view_pad,(SI_Long)4L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(bounding_box) ? EQ(ISVREF(bounding_box,
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
    if ( !temp)
	delete_frame(bounding_box);
    delete_view_pad_marker_stack(ISVREF(view_pad,(SI_Long)12L));
    iconic_entity_qm = ISVREF(view_pad,(SI_Long)13L);
    if (iconic_entity_qm) {
	serial_number = ISVREF(view_pad,(SI_Long)14L);
	gensymed_symbol = ISVREF(iconic_entity_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(iconic_entity_qm) ? 
		EQ(ISVREF(iconic_entity_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
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
	    delete_frame(iconic_entity_qm);
	    SVREF(view_pad,FIX((SI_Long)13L)) = Nil;
	}
    }
    delete_icon_editor_view_pad_icon_for_current_layer(view_pad);
    reclaim_icon_editor_view_pad_1(view_pad);
    layers_pad = ISVREF(icon_editor,(SI_Long)13L);
    bounding_box = ISVREF(layers_pad,(SI_Long)3L);
    serial_number = ISVREF(layers_pad,(SI_Long)4L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(bounding_box) ? EQ(ISVREF(bounding_box,
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
    if ( !temp)
	delete_frame(bounding_box);
    reclaim_icon_editor_layers_pad_1(layers_pad);
    buttons = ISVREF(icon_editor,(SI_Long)14L);
    button = Nil;
    ab_loop_list_ = buttons;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    button = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_icon_editor_button(button);
    goto next_loop;
  end_loop:;
    reclaim_icon_editor_list_1(buttons);
    tables = ISVREF(icon_editor,(SI_Long)15L);
    table = Nil;
    ab_loop_list_ = tables;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_icon_editor_table(table);
    goto next_loop_1;
  end_loop_1:;
    reclaim_icon_editor_list_1(tables);
    if (ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)15L))
	reclaim_icon_editor_slot_value(ISVREF(ISVREF(icon_editor,
		(SI_Long)11L),(SI_Long)15L));
    if (ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)16L))
	reclaim_icon_editor_slot_value(ISVREF(ISVREF(icon_editor,
		(SI_Long)11L),(SI_Long)16L));
    layer = Nil;
    ab_loop_list_ = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)3L);
    drawing_elements = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    drawing_elements = CDDR(layer);
    drawing_element_list = Nil;
    ab_loop_list__1 = drawing_elements;
    drawing_element = Nil;
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
  next_loop_3:
    drawing_element_list = M_CAR(ab_loop_list__1);
    drawing_element = FIRST(drawing_element_list);
    if (drawing_element && CONSP(drawing_element) && 
	    EQ(FIRST(drawing_element),Qtext))
	reclaim_icon_editor_slot_value(drawing_element);
    ab_loop_list__1 = CDDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    goto next_loop_3;
  end_loop_3:;
    goto next_loop_2;
  end_loop_2:;
    return delete_icon_editor_main_color_menu(icon_editor);
}

/* RESET-CURRENT-LAYER */
Object reset_current_layer(icon_editor_engine,new_current_layer_index)
    Object icon_editor_engine, new_current_layer_index;
{
    Object layers, number_of_layers, svref_new_value;

    x_note_fn_call(233,33);
    layers = ISVREF(icon_editor_engine,(SI_Long)3L);
    number_of_layers = ISVREF(icon_editor_engine,(SI_Long)5L);
    if (IFIX(number_of_layers) == (SI_Long)0L)
	return VALUES_1(Nil);
    else if (IFIX(new_current_layer_index) <= (SI_Long)0L) {
	ISVREF(icon_editor_engine,(SI_Long)7L) = FIX((SI_Long)0L);
	svref_new_value = CAR(layers);
	return VALUES_1(SVREF(icon_editor_engine,FIX((SI_Long)6L)) = 
		svref_new_value);
    }
    else if (FIXNUM_GE(new_current_layer_index,number_of_layers)) {
	svref_new_value = FIXNUM_SUB1(number_of_layers);
	SVREF(icon_editor_engine,FIX((SI_Long)7L)) = svref_new_value;
	svref_new_value = nth(ISVREF(icon_editor_engine,(SI_Long)7L),layers);
	return VALUES_1(SVREF(icon_editor_engine,FIX((SI_Long)6L)) = 
		svref_new_value);
    }
    else {
	SVREF(icon_editor_engine,FIX((SI_Long)7L)) = new_current_layer_index;
	svref_new_value = nth(new_current_layer_index,layers);
	return VALUES_1(SVREF(icon_editor_engine,FIX((SI_Long)6L)) = 
		svref_new_value);
    }
}

/* PUT-LAYER-BEFORE-SPECIFIC-LAYER */
Object put_layer_before_specific_layer(new_layer,specific_layer_index,
	    icon_editor_engine)
    Object new_layer, specific_layer_index, icon_editor_engine;
{
    Object old_list_of_layers, new_list_of_layers, svref_new_value, new_tail;
    Object tail_of_old_list_of_layers_qm, old_list;
    Object splicing_point_in_old_layers, cons_to_splice_in;

    x_note_fn_call(233,34);
    if (IFIX(specific_layer_index) <= (SI_Long)0L) {
	old_list_of_layers = ISVREF(icon_editor_engine,(SI_Long)3L);
	new_list_of_layers = icon_editor_cons_1(new_layer,old_list_of_layers);
	SVREF(icon_editor_engine,FIX((SI_Long)3L)) = new_list_of_layers;
	if ( !TRUEP(old_list_of_layers))
	    SVREF(icon_editor_engine,FIX((SI_Long)4L)) = new_list_of_layers;
	svref_new_value = FIXNUM_ADD1(ISVREF(icon_editor_engine,(SI_Long)5L));
	SVREF(icon_editor_engine,FIX((SI_Long)5L)) = svref_new_value;
    }
    else if (FIXNUM_GE(specific_layer_index,ISVREF(icon_editor_engine,
	    (SI_Long)5L))) {
	new_tail = icon_editor_cons_1(new_layer,Nil);
	tail_of_old_list_of_layers_qm = ISVREF(icon_editor_engine,(SI_Long)4L);
	if (tail_of_old_list_of_layers_qm)
	    M_CDR(tail_of_old_list_of_layers_qm) = new_tail;
	else
	    SVREF(icon_editor_engine,FIX((SI_Long)3L)) = new_tail;
	SVREF(icon_editor_engine,FIX((SI_Long)4L)) = new_tail;
	svref_new_value = FIXNUM_ADD1(ISVREF(icon_editor_engine,(SI_Long)5L));
	SVREF(icon_editor_engine,FIX((SI_Long)5L)) = svref_new_value;
    }
    else {
	old_list = ISVREF(icon_editor_engine,(SI_Long)3L);
	splicing_point_in_old_layers = 
		nthcdr(FIXNUM_SUB1(specific_layer_index),old_list);
	cons_to_splice_in = icon_editor_cons_1(new_layer,
		CDR(splicing_point_in_old_layers));
	M_CDR(splicing_point_in_old_layers) = cons_to_splice_in;
	svref_new_value = FIXNUM_ADD1(ISVREF(icon_editor_engine,(SI_Long)5L));
	SVREF(icon_editor_engine,FIX((SI_Long)5L)) = svref_new_value;
    }
    return reset_current_layer(icon_editor_engine,
	    ISVREF(icon_editor_engine,(SI_Long)7L));
}

/* DELETE-SPECIFIC-LAYER */
Object delete_specific_layer(specific_layer_index,icon_editor_engine)
    Object specific_layer_index, icon_editor_engine;
{
    Object old_layers, temp, temp_1, cons_preceding_cons_to_splice_out;
    Object cons_to_splice_out;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(233,35);
    arg = (SI_Long)0L;
    arg_1 = IFIX(specific_layer_index);
    arg_2 = IFIX(FIXNUM_SUB1(ISVREF(icon_editor_engine,(SI_Long)5L)));
    if (arg <= arg_1 && arg_1 <= arg_2) {
	if (IFIX(specific_layer_index) <= (SI_Long)0L) {
	    old_layers = ISVREF(icon_editor_engine,(SI_Long)3L);
	    temp = CAR(old_layers);
	    temp_1 = CDR(old_layers);
	    SVREF(icon_editor_engine,FIX((SI_Long)3L)) = temp_1;
	    if ( !TRUEP(CDR(old_layers)))
		SVREF(icon_editor_engine,FIX((SI_Long)4L)) = Nil;
	    reclaim_icon_editor_cons_1(old_layers);
	    temp_1 = FIXNUM_SUB1(ISVREF(icon_editor_engine,(SI_Long)5L));
	    SVREF(icon_editor_engine,FIX((SI_Long)5L)) = temp_1;
	}
	else {
	    old_layers = ISVREF(icon_editor_engine,(SI_Long)3L);
	    cons_preceding_cons_to_splice_out = 
		    nthcdr(FIXNUM_SUB1(specific_layer_index),old_layers);
	    cons_to_splice_out = CDR(cons_preceding_cons_to_splice_out);
	    temp = CAR(cons_to_splice_out);
	    if ( !TRUEP(CDR(cons_to_splice_out)))
		SVREF(icon_editor_engine,FIX((SI_Long)4L)) = 
			cons_preceding_cons_to_splice_out;
	    temp_1 = CDR(cons_to_splice_out);
	    M_CDR(cons_preceding_cons_to_splice_out) = temp_1;
	    reclaim_icon_editor_cons_1(cons_to_splice_out);
	    temp_1 = FIXNUM_SUB1(ISVREF(icon_editor_engine,(SI_Long)5L));
	    SVREF(icon_editor_engine,FIX((SI_Long)5L)) = temp_1;
	}
	reset_current_layer(icon_editor_engine,ISVREF(icon_editor_engine,
		(SI_Long)7L));
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* MOVE-ICON-LAYER */
Object move_icon_layer(get_from_this_layer_index_init,
	    put_before_this_layer_index_init,icon_editor_engine)
    Object get_from_this_layer_index_init, put_before_this_layer_index_init;
    Object icon_editor_engine;
{
    Object layer_to_move;
    SI_Long get_from_this_layer_index, put_before_this_layer_index;

    x_note_fn_call(233,36);
    get_from_this_layer_index = IFIX(get_from_this_layer_index_init);
    put_before_this_layer_index = IFIX(put_before_this_layer_index_init);
    if ( !(get_from_this_layer_index == put_before_this_layer_index - 
	    (SI_Long)1L)) {
	layer_to_move = 
		delete_specific_layer(FIX(get_from_this_layer_index),
		icon_editor_engine);
	return put_layer_before_specific_layer(layer_to_move,
		FIX(put_before_this_layer_index - (SI_Long)1L),
		icon_editor_engine);
    }
    else
	return VALUES_1(Nil);
}

/* NEW-ICON-LAYER */
Object new_icon_layer(color_label,list_of_line_drawing_elements_qm,
	    put_before_this_layer_index,icon_editor_engine)
    Object color_label, list_of_line_drawing_elements_qm;
    Object put_before_this_layer_index, icon_editor_engine;
{
    Object new_layer;

    x_note_fn_call(233,37);
    new_layer = icon_editor_list_4(color_label,Nil,
	    list_of_line_drawing_elements_qm,
	    last(list_of_line_drawing_elements_qm,_));
    return put_layer_before_specific_layer(new_layer,
	    put_before_this_layer_index,icon_editor_engine);
}

static Object Qpoint;              /* point */

static Object Qcircle;             /* circle */

static Object Qarc;                /* arc */

static Object Qicon_editor_table_info_frame_icon_width;  /* icon-editor-table-info-frame-icon-width */

static Object Qicon_editor_table_info_frame_icon_height;  /* icon-editor-table-info-frame-icon-height */

static Object Qicon_editor_table_info_frame_global_stipple;  /* icon-editor-table-info-frame-global-stipple */

static Object Qicon_editor_table_info_frame_main_region;  /* icon-editor-table-info-frame-main-region */

static Object Qicon_editor_table_info_frame_main_color;  /* icon-editor-table-info-frame-main-color */

static Object Qicon_editor_table_info_frame_main_image;  /* icon-editor-table-info-frame-main-image */

static Object Qicon_editor_table_info_frame_text;  /* icon-editor-table-info-frame-text */

static Object Qicon_editor_table_info_frame_stipple;  /* icon-editor-table-info-frame-stipple */

static Object list_constant;       /* # */

static Object Qeditor_scaling;     /* editor-scaling */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* HANDLE-ICON-EDITOR-VISUAL-EVENT */
Object handle_icon_editor_visual_event(icon_editor,visual_event_init,
	    arg_1_qm,arg_2_qm)
    Object icon_editor, visual_event_init, arg_1_qm, arg_2_qm;
{
    Object gensymed_symbol, x, y, xa, ya, x_y_position_box, frame, old_x_value;
    Object old_y_value, temp_2, x_in_view_pad, y_in_view_pad, view_pad, color;
    Object put_point_marker_instead_qm, cross_marker, svref_new_value, temp_3;
    Object scale, value, engine, x_origin_in_workspace, y_origin_in_workspace;
    Object temp_4, temp_5, temp_6, temp_7, x0_in_view_pad, y0_in_view_pad;
    Object radius_in_view_pad, left_edge_to_clip_in_workspace;
    Object top_edge_to_clip_in_workspace, x_radius_in_icon, y_radius_in_icon;
    Object left_edge_in_view_pad, top_edge_in_view_pad, circle_marker;
    Object x1_in_view_pad, y1_in_view_pad, x2_in_view_pad, y2_in_view_pad;
    Object min_x_in_view_pad_qm, min_y_in_view_pad_qm, max_x_in_view_pad_qm;
    Object max_y_in_view_pad_qm, arc_marker, x_in_view_pad_of_left_most_point;
    Object x_in_view_pad_of_right_most_point, y_in_view_pad_of_left_most_point;
    Object y_in_view_pad_of_right_most_point, marker_stack_qm;
    Object frame_and_serial_number_pair, serial_number, info_box, slot_name;
    Object new_value, bounding_box, workspace, reference_serial_number;
    Object icon_width_1, icon_height_1, layers, alist, x_scale, y_scale;
    Object scaled_width, scaled_height, old_iconic_entity_qm;
    Object old_iconic_entity_serial_number, variable_spec_list;
    Object background_layer, stipple_spec, frame_serial_number_setf_arg, old;
    Object new_1, x2_1;
    SI_Long visual_event, temp_1, marker_extent, marker_relative_center;
    SI_Long gensymed_symbol_1, unshifted_result, gensymed_symbol_2;
    SI_Long right_edge_to_clip_in_workspace, bottom_edge_to_clip_in_workspace;
    SI_Long desired_min_x_in_workspace, desired_min_y_in_workspace;
    SI_Long desired_max_x_in_workspace, desired_max_y_in_workspace;
    SI_Long gensymed_symbol_3, clipped_delta_x_in_workspace;
    SI_Long clipped_delta_y_in_workspace, desired_icon_width;
    SI_Long desired_icon_height, icon_width, icon_height, x1, y1_1, x2, y2, x3;
    SI_Long y3, min_x_in_workspace, min_y_in_workspace, max_x_in_workspace;
    SI_Long max_y_in_workspace, left_edge_in_workspace, top_edge_in_workspace;
    SI_Long x0_in_icon, y0_in_icon, x1_in_icon, y1_in_icon, x2_in_icon;
    SI_Long y2_in_icon, gensymed_symbol_4;
    char temp;
    Object result;

    x_note_fn_call(233,38);
    visual_event = IFIX(visual_event_init);
    gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)4L),(SI_Long)3L);
    x = ISVREF(icon_editor,(SI_Long)4L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(icon_editor,(SI_Long)5L);
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
    if (temp) {
	reclaim_icon_editor_slot_value(arg_1_qm);
	reclaim_icon_editor_slot_value(arg_2_qm);
	cleanup_icon_editor(icon_editor);
	return reclaim_icon_editor_1(icon_editor);
    }
    else {
	temp_1 = visual_event;
	if ( !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
	    return VALUES_1(Nil);
	else
	    switch ((char)temp_1) {
	      case 10:
		x_y_position_box = ISVREF(icon_editor,(SI_Long)21L);
		frame = ISVREF(x_y_position_box,(SI_Long)5L);
		old_x_value = ISVREF(frame,(SI_Long)27L);
		old_y_value = ISVREF(frame,(SI_Long)28L);
		if ( !(FIXNUM_EQ(old_x_value,arg_1_qm) && 
			FIXNUM_EQ(old_y_value,arg_2_qm))) {
		    ISVREF(frame,(SI_Long)27L) = arg_1_qm;
		    ISVREF(frame,(SI_Long)28L) = arg_2_qm;
		    temp_2 = ISVREF(x_y_position_box,(SI_Long)8L);
		    return change_slot_value(3,frame,CAR(temp_2),arg_1_qm);
		}
		else
		    return VALUES_1(Nil);
	      case 13:
		x_in_view_pad = arg_1_qm;
		y_in_view_pad = arg_2_qm;
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		color = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)11L);
		put_point_marker_instead_qm = T;
		marker_extent = (SI_Long)5L - (SI_Long)1L;
		marker_relative_center = marker_extent >>  -  - (SI_Long)1L;
		cross_marker = 
			make_entity_with_specific_icon_description(4,
			Qiconic_entity,
			wrap_polychrome_declaration_around_slot_value_conses(color,
			put_point_marker_instead_qm ? 
			slot_value_cons_1(slot_value_list_2(Qpoint,
			slot_value_list_2(FIX(marker_relative_center),
			FIX(marker_relative_center))),Nil) : 
			slot_value_list_2(slot_value_list_3(Qlines,
			slot_value_list_2(FIX((SI_Long)0L),
			FIX(marker_relative_center)),
			slot_value_list_2(FIX(marker_extent),
			FIX(marker_relative_center))),
			slot_value_list_3(Qlines,
			slot_value_list_2(FIX(marker_relative_center),
			FIX((SI_Long)0L)),
			slot_value_list_2(FIX(marker_relative_center),
			FIX(marker_extent))))),FIX(marker_extent),
			FIX(marker_extent));
		temp_2 = icon_editor_cons_1(cross_marker,
			copy_frame_serial_number(Current_frame_serial_number));
		svref_new_value = icon_editor_cons_1(temp_2,
			ISVREF(view_pad,(SI_Long)12L));
		SVREF(view_pad,FIX((SI_Long)12L)) = svref_new_value;
		temp_3 = ISVREF(view_pad,(SI_Long)9L);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = x_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = marker_relative_center;
		temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = y_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = marker_relative_center;
		return add_to_workspace(5,cross_marker,temp_3,temp_2,
			FIX(gensymed_symbol_1 - gensymed_symbol_2),T);
	      case 14:
		x_in_view_pad = arg_1_qm;
		y_in_view_pad = arg_2_qm;
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		color = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)11L);
		put_point_marker_instead_qm = Nil;
		marker_extent = (SI_Long)5L - (SI_Long)1L;
		marker_relative_center = marker_extent >>  -  - (SI_Long)1L;
		cross_marker = 
			make_entity_with_specific_icon_description(4,
			Qiconic_entity,
			wrap_polychrome_declaration_around_slot_value_conses(color,
			put_point_marker_instead_qm ? 
			slot_value_cons_1(slot_value_list_2(Qpoint,
			slot_value_list_2(FIX(marker_relative_center),
			FIX(marker_relative_center))),Nil) : 
			slot_value_list_2(slot_value_list_3(Qlines,
			slot_value_list_2(FIX((SI_Long)0L),
			FIX(marker_relative_center)),
			slot_value_list_2(FIX(marker_extent),
			FIX(marker_relative_center))),
			slot_value_list_3(Qlines,
			slot_value_list_2(FIX(marker_relative_center),
			FIX((SI_Long)0L)),
			slot_value_list_2(FIX(marker_relative_center),
			FIX(marker_extent))))),FIX(marker_extent),
			FIX(marker_extent));
		temp_2 = icon_editor_cons_1(cross_marker,
			copy_frame_serial_number(Current_frame_serial_number));
		svref_new_value = icon_editor_cons_1(temp_2,
			ISVREF(view_pad,(SI_Long)12L));
		SVREF(view_pad,FIX((SI_Long)12L)) = svref_new_value;
		temp_3 = ISVREF(view_pad,(SI_Long)9L);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = x_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = marker_relative_center;
		temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = y_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = marker_relative_center;
		return add_to_workspace(5,cross_marker,temp_3,temp_2,
			FIX(gensymed_symbol_1 - gensymed_symbol_2),T);
	      case 15:
	      case 16:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		x_origin_in_workspace = ISVREF(view_pad,(SI_Long)5L);
		y_origin_in_workspace = ISVREF(view_pad,(SI_Long)6L);
		temp_2 = CAR(arg_1_qm);
		temp_3 = CDR(arg_1_qm);
		temp_4 = CAR(arg_2_qm);
		temp_5 = CDR(arg_2_qm);
		temp_6 = ISVREF(engine,(SI_Long)11L);
		gensymed_symbol_1 = IFIX(x_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = ISVREF(engine,(SI_Long)1L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		temp_7 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
		gensymed_symbol_1 = IFIX(y_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = ISVREF(engine,(SI_Long)2L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		put_line_marker_in_view_pad(temp_2,temp_3,temp_4,temp_5,
			view_pad,temp_6,x_origin_in_workspace,
			y_origin_in_workspace,temp_7,FIX(gensymed_symbol_1 
			+ gensymed_symbol_2),visual_event == (SI_Long)16L ?
			 T : Nil);
		reclaim_icon_editor_cons_1(arg_1_qm);
		return reclaim_icon_editor_cons_1(arg_2_qm);
	      case 17:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		x_origin_in_workspace = ISVREF(view_pad,(SI_Long)5L);
		y_origin_in_workspace = ISVREF(view_pad,(SI_Long)6L);
		x0_in_view_pad = CAR(arg_1_qm);
		y0_in_view_pad = CDR(arg_1_qm);
		radius_in_view_pad = arg_2_qm;
		color = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)11L);
		left_edge_to_clip_in_workspace = x_origin_in_workspace;
		top_edge_to_clip_in_workspace = y_origin_in_workspace;
		gensymed_symbol_1 = IFIX(x_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = ISVREF(engine,(SI_Long)1L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		right_edge_to_clip_in_workspace = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(y_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = ISVREF(engine,(SI_Long)2L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		bottom_edge_to_clip_in_workspace = gensymed_symbol_1 + 
			gensymed_symbol_2;
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = radius_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    x_radius_in_icon = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    x_radius_in_icon = FIX(unshifted_result >>  -  - 
			    (SI_Long)12L);
		}
		else
		    x_radius_in_icon = scalef_function(scale,value);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = radius_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    y_radius_in_icon = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    y_radius_in_icon = FIX(unshifted_result >>  -  - 
			    (SI_Long)12L);
		}
		else
		    y_radius_in_icon = scalef_function(scale,value);
		left_edge_in_view_pad = FIXNUM_MINUS(x0_in_view_pad,
			radius_in_view_pad);
		top_edge_in_view_pad = FIXNUM_MINUS(y0_in_view_pad,
			radius_in_view_pad);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = left_edge_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = IFIX(left_edge_to_clip_in_workspace);
		desired_min_x_in_workspace = MAX(gensymed_symbol_1,
			gensymed_symbol_2);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = top_edge_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = IFIX(top_edge_to_clip_in_workspace);
		desired_min_y_in_workspace = MAX(gensymed_symbol_1,
			gensymed_symbol_2);
		x_in_view_pad = FIXNUM_ADD(x0_in_view_pad,radius_in_view_pad);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = x_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = right_edge_to_clip_in_workspace;
		desired_max_x_in_workspace = MIN(gensymed_symbol_1,
			gensymed_symbol_2);
		y_in_view_pad = FIXNUM_ADD(y0_in_view_pad,radius_in_view_pad);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = y_in_view_pad;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol_2 = bottom_edge_to_clip_in_workspace;
		desired_max_y_in_workspace = MIN(gensymed_symbol_1,
			gensymed_symbol_2);
		if (desired_min_x_in_workspace == 
			IFIX(left_edge_to_clip_in_workspace)) {
		    gensymed_symbol_1 = IFIX(left_edge_to_clip_in_workspace);
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = left_edge_in_view_pad;
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
		    gensymed_symbol_3 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		    clipped_delta_x_in_workspace = gensymed_symbol_1 - 
			    gensymed_symbol_2;
		}
		else
		    clipped_delta_x_in_workspace = (SI_Long)0L;
		if (desired_min_y_in_workspace == 
			IFIX(top_edge_to_clip_in_workspace)) {
		    gensymed_symbol_1 = IFIX(top_edge_to_clip_in_workspace);
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = top_edge_in_view_pad;
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
		    gensymed_symbol_3 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		    clipped_delta_y_in_workspace = gensymed_symbol_1 - 
			    gensymed_symbol_2;
		}
		else
		    clipped_delta_y_in_workspace = (SI_Long)0L;
		desired_icon_width = desired_max_x_in_workspace - 
			desired_min_x_in_workspace;
		desired_icon_height = desired_max_y_in_workspace - 
			desired_min_y_in_workspace;
		icon_width = MAX((SI_Long)1L,desired_icon_width);
		icon_height = MAX((SI_Long)1L,desired_icon_height);
		x1 =  - clipped_delta_x_in_workspace;
		y1_1 = IFIX(y_radius_in_icon) - clipped_delta_y_in_workspace;
		x2 = IFIX(x_radius_in_icon) - clipped_delta_x_in_workspace;
		y2 =  - clipped_delta_y_in_workspace;
		x3 = (IFIX(x_radius_in_icon) << (SI_Long)1L) - 
			clipped_delta_x_in_workspace;
		y3 = y1_1;
		circle_marker = 
			make_entity_with_specific_icon_description(4,
			Qiconic_entity,
			wrap_polychrome_declaration_around_slot_value_conses(color,
			slot_value_cons_1(desired_icon_width == 
			(SI_Long)0L && desired_icon_height == (SI_Long)0L ?
			 slot_value_list_2(Qpoint,
			slot_value_list_2(FIX((SI_Long)0L),
			FIX((SI_Long)0L))) : slot_value_list_4(Qcircle,
			slot_value_list_2(FIX(x1),FIX(y1_1)),
			slot_value_list_2(FIX(x2),FIX(y2)),
			slot_value_list_2(FIX(x3),FIX(y3))),Nil)),
			FIX(icon_width),FIX(icon_height));
		temp_2 = icon_editor_cons_1(circle_marker,
			copy_frame_serial_number(Current_frame_serial_number));
		svref_new_value = icon_editor_cons_1(temp_2,
			ISVREF(view_pad,(SI_Long)12L));
		SVREF(view_pad,FIX((SI_Long)12L)) = svref_new_value;
		return add_to_workspace(5,circle_marker,ISVREF(view_pad,
			(SI_Long)9L),FIX(desired_min_x_in_workspace),
			FIX(desired_min_y_in_workspace),T);
	      case 18:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		engine = ISVREF(icon_editor,(SI_Long)11L);
		x_origin_in_workspace = ISVREF(view_pad,(SI_Long)5L);
		y_origin_in_workspace = ISVREF(view_pad,(SI_Long)6L);
		temp_2 = FIRST(arg_1_qm);
		x0_in_view_pad = CAR(temp_2);
		temp_2 = FIRST(arg_1_qm);
		y0_in_view_pad = CDR(temp_2);
		temp_2 = SECOND(arg_1_qm);
		x1_in_view_pad = CAR(temp_2);
		temp_2 = SECOND(arg_1_qm);
		y1_in_view_pad = CDR(temp_2);
		x2_in_view_pad = CAR(arg_2_qm);
		y2_in_view_pad = CDR(arg_2_qm);
		color = ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)11L);
		left_edge_to_clip_in_workspace = x_origin_in_workspace;
		top_edge_to_clip_in_workspace = y_origin_in_workspace;
		gensymed_symbol_1 = IFIX(x_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)10L);
		value = ISVREF(engine,(SI_Long)1L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		right_edge_to_clip_in_workspace = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(y_origin_in_workspace);
		scale = ISVREF(view_pad,(SI_Long)11L);
		value = ISVREF(engine,(SI_Long)2L);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		bottom_edge_to_clip_in_workspace = gensymed_symbol_1 + 
			gensymed_symbol_2;
		result = compute_arc_bounding_box(x0_in_view_pad,
			y0_in_view_pad,x1_in_view_pad,y1_in_view_pad,
			x2_in_view_pad,y2_in_view_pad);
		MVS_4(result,min_x_in_view_pad_qm,min_y_in_view_pad_qm,
			max_x_in_view_pad_qm,max_y_in_view_pad_qm);
		if (min_x_in_view_pad_qm) {
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = min_x_in_view_pad_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = IFIX(left_edge_to_clip_in_workspace);
		    min_x_in_workspace = MAX(gensymed_symbol_1,
			    gensymed_symbol_2);
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = min_y_in_view_pad_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = IFIX(top_edge_to_clip_in_workspace);
		    min_y_in_workspace = MAX(gensymed_symbol_1,
			    gensymed_symbol_2);
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = max_x_in_view_pad_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = ISVREF(view_pad,(SI_Long)7L);
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
		    gensymed_symbol_3 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		    max_x_in_workspace = MIN(gensymed_symbol_1,
			    gensymed_symbol_2);
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = max_y_in_view_pad_qm;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = ISVREF(view_pad,(SI_Long)8L);
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
		    gensymed_symbol_3 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		    max_y_in_workspace = MIN(gensymed_symbol_1,
			    gensymed_symbol_2);
		    left_edge_in_workspace = min_x_in_workspace;
		    top_edge_in_workspace = min_y_in_workspace;
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = x0_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = left_edge_in_workspace;
		    x0_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = y0_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = top_edge_in_workspace;
		    y0_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = x1_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = left_edge_in_workspace;
		    x1_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = y1_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = top_edge_in_workspace;
		    y1_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)10L);
		    value = x2_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = left_edge_in_workspace;
		    x2_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    scale = ISVREF(view_pad,(SI_Long)11L);
		    value = y2_in_view_pad;
		    if (IFIX(scale) == (SI_Long)4096L)
			gensymed_symbol_1 = IFIX(value);
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			gensymed_symbol_1 = unshifted_result >>  -  - 
				(SI_Long)12L;
		    }
		    else
			gensymed_symbol_1 = IFIX(scalef_function(scale,value));
		    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol_2 = top_edge_in_workspace;
		    y2_in_icon = gensymed_symbol_1 - gensymed_symbol_2;
		    icon_width = max_x_in_workspace - min_x_in_workspace;
		    icon_height = max_y_in_workspace - min_y_in_workspace;
		    temp_3 = 
			    wrap_polychrome_declaration_around_slot_value_conses(color,
			    slot_value_cons_1(slot_value_list_4(Qlines,
			    slot_value_list_2(FIX(x0_in_icon),
			    FIX(y0_in_icon)),slot_value_list_2(Qarc,
			    slot_value_list_2(FIX(x1_in_icon),
			    FIX(y1_in_icon))),
			    slot_value_list_2(FIX(x2_in_icon),
			    FIX(y2_in_icon))),Nil));
		    temp_1 = right_edge_to_clip_in_workspace - 
			    left_edge_in_workspace;
		    temp_2 = FIX(MIN(icon_width,temp_1));
		    temp_1 = bottom_edge_to_clip_in_workspace - 
			    top_edge_in_workspace;
		    arc_marker = 
			    make_entity_with_specific_icon_description(4,
			    Qiconic_entity,temp_3,temp_2,
			    FIX(MIN(icon_height,temp_1)));
		    temp_2 = icon_editor_cons_1(arc_marker,
			    copy_frame_serial_number(Current_frame_serial_number));
		    svref_new_value = icon_editor_cons_1(temp_2,
			    ISVREF(view_pad,(SI_Long)12L));
		    SVREF(view_pad,FIX((SI_Long)12L)) = svref_new_value;
		    return add_to_workspace(5,arc_marker,ISVREF(view_pad,
			    (SI_Long)9L),FIX(left_edge_in_workspace),
			    FIX(top_edge_in_workspace),T);
		}
		else if (FIXNUM_EQ(x0_in_view_pad,x1_in_view_pad) && 
			FIXNUM_EQ(x1_in_view_pad,x2_in_view_pad)) {
		    temp_3 = FIXNUM_MIN(y0_in_view_pad,y1_in_view_pad);
		    temp_2 = FIXNUM_MAX(y0_in_view_pad,y1_in_view_pad);
		    return put_line_marker_in_view_pad(x0_in_view_pad,
			    FIXNUM_MIN(temp_3,y2_in_view_pad),
			    x0_in_view_pad,FIXNUM_MAX(temp_2,
			    y2_in_view_pad),view_pad,color,
			    left_edge_to_clip_in_workspace,
			    top_edge_to_clip_in_workspace,
			    FIX(right_edge_to_clip_in_workspace),
			    FIX(bottom_edge_to_clip_in_workspace),Nil);
		}
		else {
		    temp_2 = FIXNUM_MIN(x0_in_view_pad,x1_in_view_pad);
		    x_in_view_pad_of_left_most_point = FIXNUM_MIN(temp_2,
			    x2_in_view_pad);
		    temp_2 = FIXNUM_MAX(x0_in_view_pad,x1_in_view_pad);
		    x_in_view_pad_of_right_most_point = FIXNUM_MAX(temp_2,
			    x2_in_view_pad);
		    if (FIXNUM_EQ(x_in_view_pad_of_left_most_point,
			    x0_in_view_pad))
			y_in_view_pad_of_left_most_point = y0_in_view_pad;
		    else if (FIXNUM_EQ(x_in_view_pad_of_left_most_point,
			    x1_in_view_pad))
			y_in_view_pad_of_left_most_point = y1_in_view_pad;
		    else
			y_in_view_pad_of_left_most_point = y2_in_view_pad;
		    if (FIXNUM_EQ(x_in_view_pad_of_right_most_point,
			    x0_in_view_pad))
			y_in_view_pad_of_right_most_point = y0_in_view_pad;
		    else if (FIXNUM_EQ(x_in_view_pad_of_right_most_point,
			    x1_in_view_pad))
			y_in_view_pad_of_right_most_point = y1_in_view_pad;
		    else
			y_in_view_pad_of_right_most_point = y2_in_view_pad;
		    return put_line_marker_in_view_pad(x_in_view_pad_of_left_most_point,
			    y_in_view_pad_of_left_most_point,
			    x_in_view_pad_of_right_most_point,
			    y_in_view_pad_of_right_most_point,view_pad,
			    color,left_edge_to_clip_in_workspace,
			    top_edge_to_clip_in_workspace,
			    FIX(right_edge_to_clip_in_workspace),
			    FIX(bottom_edge_to_clip_in_workspace),Nil);
		}
	      case 19:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		marker_stack_qm = ISVREF(view_pad,(SI_Long)12L);
		if (marker_stack_qm) {
		    frame_and_serial_number_pair = CAR(marker_stack_qm);
		    frame = CAR(frame_and_serial_number_pair);
		    serial_number = CDR(frame_and_serial_number_pair);
		    gensymed_symbol = ISVREF(frame,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,
			    (SI_Long)1L),Qavailable_frame_vector) : 
			    TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(serial_number,gensymed_symbol) : 
				TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    if ( !temp)
			delete_frame(frame);
		    reclaim_frame_serial_number(serial_number);
		    reclaim_icon_editor_cons_1(frame_and_serial_number_pair);
		    svref_new_value = CDR(marker_stack_qm);
		    SVREF(view_pad,FIX((SI_Long)12L)) = svref_new_value;
		    return reclaim_icon_editor_cons_1(marker_stack_qm);
		}
		else
		    return VALUES_1(Nil);
	      case 20:
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		delete_view_pad_marker_stack(ISVREF(view_pad,(SI_Long)12L));
		return VALUES_1(SVREF(view_pad,FIX((SI_Long)12L)) = Nil);
	      case 1:
		return VALUES_1(Nil);
	      case 3:
		info_box = ISVREF(icon_editor,(SI_Long)16L);
		temp_2 = ISVREF(info_box,(SI_Long)8L);
		return change_slot_value(3,ISVREF(info_box,(SI_Long)5L),
			CAR(temp_2),arg_1_qm);
	      case 4:
	      case 5:
	      case 52:
		temp_1 = visual_event;
		if ( !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
		    slot_name = Nil;
		else
		    switch ((char)temp_1) {
		      case 4:
			slot_name = Qicon_editor_table_info_frame_icon_width;
			break;
		      case 5:
			slot_name = Qicon_editor_table_info_frame_icon_height;
			break;
		      case 52:
			slot_name = 
				Qicon_editor_table_info_frame_global_stipple;
			break;
		      default:
			slot_name = Nil;
			break;
		    }
		return change_slot_value(3,ISVREF(ISVREF(icon_editor,
			(SI_Long)17L),(SI_Long)5L),slot_name,arg_1_qm);
	      case 6:
	      case 7:
	      case 49:
	      case 50:
	      case 51:
		temp_1 = visual_event;
		if ( !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
		    slot_name = Nil;
		else
		    switch ((char)temp_1) {
		      case 6:
			slot_name = Qicon_editor_table_info_frame_main_region;
			break;
		      case 7:
			slot_name = Qicon_editor_table_info_frame_main_color;
			break;
		      case 49:
			slot_name = Qicon_editor_table_info_frame_main_image;
			break;
		      case 50:
			slot_name = Qicon_editor_table_info_frame_text;
			break;
		      case 51:
			slot_name = Qicon_editor_table_info_frame_stipple;
			break;
		      default:
			slot_name = Nil;
			break;
		    }
		if (CONSP(arg_1_qm))
		    new_value = memq_function(slot_name,list_constant) ? 
			    copy_drawing_element_with_slot_value_conses(arg_1_qm,
			    Nil,Nil,Nil) : 
			    copy_tree_using_slot_value_conses_1(arg_1_qm);
		else if (text_string_p(arg_1_qm))
		    new_value = copy_text_string(arg_1_qm);
		else
		    new_value = arg_1_qm;
		return change_slot_value(3,ISVREF(ISVREF(icon_editor,
			(SI_Long)18L),(SI_Long)5L),slot_name,new_value);
	      case 11:
		bounding_box = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
			(SI_Long)3L);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = 
			IFIX(FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,
			(SI_Long)17L),(SI_Long)44L)));
		gensymed_symbol_3 = IFIX(FIXNUM_ADD1(arg_1_qm));
		gensymed_symbol_4 = (SI_Long)1L;
		return update_border_of_bounding_box(bounding_box,Nil,Nil,
			FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
			gensymed_symbol_3 + gensymed_symbol_4),Nil);
	      case 12:
		bounding_box = ISVREF(ISVREF(icon_editor,(SI_Long)12L),
			(SI_Long)3L);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = 
			IFIX(FIXNUM_ADD1(ISVREF(ISVREF(bounding_box,
			(SI_Long)17L),(SI_Long)44L)));
		gensymed_symbol_3 = IFIX(FIXNUM_ADD1(arg_1_qm));
		gensymed_symbol_4 = (SI_Long)1L;
		return update_border_of_bounding_box(bounding_box,Nil,Nil,
			Nil,FIX(gensymed_symbol_1 + gensymed_symbol_2 + 
			gensymed_symbol_3 + gensymed_symbol_4));
	      case 0:
		workspace = ISVREF(icon_editor,(SI_Long)4L);
		reference_serial_number = ISVREF(icon_editor,(SI_Long)5L);
		gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,
			(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference_serial_number))
		    temp = FIXNUMP(gensymed_symbol) ? 
			    FIXNUM_LT(reference_serial_number,
			    gensymed_symbol) : TRUEP(T);
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
		if ( !temp)
		    return delete_frame(workspace);
		else
		    return VALUES_1(Nil);
	      case 27:
	      case 28:
	      case 29:
	      case 30:
	      case 31:
	      case 32:
	      case 33:
	      case 34:
	      case 35:
	      case 36:
	      case 37:
	      case 38:
		return handle_layers_pad_visual_event(icon_editor,
			FIX(visual_event),arg_1_qm,arg_2_qm);
	      case 24:
		return VALUES_1(Nil);
	      case 21:
	      case 22:
	      case 23:
	      case 25:
	      case 26:
		engine = ISVREF(icon_editor,(SI_Long)11L);
		view_pad = ISVREF(icon_editor,(SI_Long)12L);
		icon_width_1 = ISVREF(engine,(SI_Long)1L);
		icon_height_1 = ISVREF(engine,(SI_Long)2L);
		layers = ISVREF(engine,(SI_Long)3L);
		alist = ISVREF(icon_editor,(SI_Long)6L);
		x_scale = ISVREF(view_pad,(SI_Long)10L);
		y_scale = ISVREF(view_pad,(SI_Long)11L);
		if (IFIX(x_scale) == (SI_Long)4096L)
		    scaled_width = icon_width_1;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			x_scale) && FIXNUM_LT(x_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			icon_width_1) && FIXNUM_LT(icon_width_1,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,
			    icon_width_1)) + (SI_Long)2048L;
		    scaled_width = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    scaled_width = scalef_function(x_scale,icon_width_1);
		if (IFIX(y_scale) == (SI_Long)4096L)
		    scaled_height = icon_height_1;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			y_scale) && FIXNUM_LT(y_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			icon_height_1) && FIXNUM_LT(icon_height_1,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,
			    icon_height_1)) + (SI_Long)2048L;
		    scaled_height = FIX(unshifted_result >>  -  - 
			    (SI_Long)12L);
		}
		else
		    scaled_height = scalef_function(y_scale,icon_height_1);
		old_iconic_entity_qm = ISVREF(view_pad,(SI_Long)13L);
		old_iconic_entity_serial_number = ISVREF(view_pad,
			(SI_Long)14L);
		variable_spec_list = ISVREF(icon_editor,(SI_Long)7L);
		background_layer = ISVREF(icon_editor,(SI_Long)8L);
		stipple_spec = ISVREF(icon_editor,(SI_Long)9L);
		temp_2 = 
			convert_list_of_layers_to_line_drawing_description(layers,
			alist,variable_spec_list,background_layer,
			scaled_width,scaled_height,x_scale,y_scale,T,T,
			stipple_spec);
		svref_new_value = 
			make_entity_with_specific_icon_description(6,
			Qiconic_entity,temp_2,scaled_width,scaled_height,
			Nil,CONSP(background_layer) ? 
			slot_value_list_2(copy_for_slot_value(background_layer),
			slot_value_list_3(Qeditor_scaling,x_scale,
			y_scale)) : copy_for_slot_value(background_layer));
		SVREF(view_pad,FIX((SI_Long)13L)) = svref_new_value;
		frame_serial_number_setf_arg = Current_frame_serial_number;
		old = ISVREF(view_pad,(SI_Long)14L);
		new_1 = frame_serial_number_setf_arg;
		svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
			(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
			frame_serial_number_setf_helper_1(old,new_1);
		SVREF(view_pad,FIX((SI_Long)14L)) = svref_new_value;
		add_to_workspace(5,ISVREF(view_pad,(SI_Long)13L),
			ISVREF(icon_editor,(SI_Long)4L),ISVREF(view_pad,
			(SI_Long)5L),ISVREF(view_pad,(SI_Long)6L),T);
		if (SIMPLE_VECTOR_P(old_iconic_entity_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_iconic_entity_qm)) 
			> (SI_Long)2L &&  !EQ(ISVREF(old_iconic_entity_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2_1 = ISVREF(old_iconic_entity_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2_1) && EQ(ISVREF(x2_1,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2_1) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol = ISVREF(old_iconic_entity_qm,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(old_iconic_entity_qm) ? 
			    EQ(ISVREF(old_iconic_entity_qm,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(old_iconic_entity_serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(old_iconic_entity_serial_number,
				gensymed_symbol) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(old_iconic_entity_serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(old_iconic_entity_serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    return delete_frame(old_iconic_entity_qm);
		else
		    return VALUES_1(Nil);
	      default:
		return VALUES_1(Nil);
	    }
    }
}

/* INFORM-USER-OF-CURRENT-REGIONS */
Object inform_user_of_current_regions(icon_editor)
    Object icon_editor;
{
    x_note_fn_call(233,39);
    return VALUES_1(Nil);
}

void icons2_INIT()
{
    Object temp, temp_1;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, AB_package, list_constant_78;
    Object list_constant_77, list_constant_76, list_constant_75;
    Object list_constant_74, list_constant_66, list_constant_73;
    Object list_constant_72, list_constant_67;
    Object Qicon_editor_table_info_frame_x_y_position, list_constant_71;
    Object list_constant_70, list_constant_63, list_constant_69;
    Object list_constant_68, list_constant_65, list_constant_64;
    Object Qicon_editor_table_info_frame_info, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_59;
    Object list_constant_58, list_constant_57, list_constant_56;
    Object list_constant_55, list_constant_54, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_34, array_constant_16, list_constant_4;
    Object list_constant_33, array_constant_15, list_constant_32;
    Object array_constant_14, list_constant_31, array_constant_13;
    Object list_constant_30, array_constant_12, list_constant_29;
    Object array_constant_11, list_constant_28, array_constant_10;
    Object list_constant_27, array_constant_9, list_constant_26;
    Object array_constant_8, list_constant_21, list_constant_25;
    Object Qfilled_polygon_button, list_constant_24, Qfilled_circle_button;
    Object list_constant_23, Qfilled_rectangle_button, list_constant_22;
    Object Qline_button, list_constant_20, array_constant_7, list_constant_15;
    Object list_constant_19, Qoutlined_polygon_button, list_constant_18;
    Object Qoutlined_circle_button, list_constant_17;
    Object Qoutlined_rectangle_button, list_constant_16, Qlines_button;
    Object list_constant_14, array_constant_6, list_constant_9;
    Object list_constant_13, array_constant_5, list_constant_12;
    Object array_constant_4, list_constant_11, Qpoints_button;
    Object list_constant_10, Qarc_button, list_constant_8, array_constant_3;
    Object list_constant_7, array_constant_2, list_constant_6;
    Object array_constant_1, list_constant_5, array_constant;
    Object string_constant_67, list_constant_3, Qoutlined_filled_circle_button;
    Object Qcreate_action_button_description, string_constant_58;
    Object string_constant_66, string_constant_22, string_constant_65;
    Object string_constant_64, string_constant_63;
    Object Qoutlined_filled_polygon_button, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object Qoutlined_filled_rectangle_button, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_46, string_constant_50, string_constant_49;
    Object string_constant_32, string_constant_48, string_constant_47;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_35;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_34;
    Object string_constant_33, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object Qsmall_icon_editor_text_button, string_constant_26;
    Object string_constant_25, Qbig_icon_editor_text_button;
    Object Qicon_editor_draw_button, string_constant_24, list_constant_2;
    Object Qicon_editor_button, string_constant_23, list_constant_1;
    Object Qgeneric_action_button, Qslot_value_writer;
    Object Qwrite_icon_editor_table_info_frame_info_from_slot;

    x_note_fn_call(233,40);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("Icon editor ready.");
    string_constant_1 = STATIC_STRING("Undo.");
    string_constant_2 = STATIC_STRING("Redo.");
    string_constant_3 = STATIC_STRING("Drawing point.");
    string_constant_4 = STATIC_STRING("Drawing points.");
    string_constant_5 = STATIC_STRING("Drawing line.");
    string_constant_6 = STATIC_STRING("Drawing lines.");
    string_constant_7 = STATIC_STRING("Drawing an arc.");
    string_constant_8 = STATIC_STRING("Drawing an outlined rectangle.");
    string_constant_9 = STATIC_STRING("Drawing an outlined polygon.");
    string_constant_10 = STATIC_STRING("Drawing an outlined circle.");
    string_constant_11 = STATIC_STRING("Drawing a filled rectangle.");
    string_constant_12 = STATIC_STRING("Drawing a filled polygon.");
    string_constant_13 = STATIC_STRING("Drawing a filled circle.");
    string_constant_14 = 
	    STATIC_STRING("Drawing a filled and outlined rectangle.");
    string_constant_15 = 
	    STATIC_STRING("Drawing a filled and outlined polygon.");
    string_constant_16 = 
	    STATIC_STRING("Drawing a filled and outlined circle.");
    string_constant_17 = 
	    STATIC_STRING("Drag the current layer to its new position.");
    string_constant_18 = STATIC_STRING("Working with layers.");
    string_constant_19 = STATIC_STRING("~a");
    AB_package = STATIC_PACKAGE("AB");
    Qicon_editor_ready = STATIC_SYMBOL("ICON-EDITOR-READY",AB_package);
    Qicon_editor_table_info_frame_info = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-INFO",AB_package);
    Qwrite_icon_editor_table_info_frame_info_from_slot = 
	    STATIC_SYMBOL("WRITE-ICON-EDITOR-TABLE-INFO-FRAME-INFO-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icon_editor_table_info_frame_info_from_slot,
	    STATIC_FUNCTION(write_icon_editor_table_info_frame_info_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qicon_editor_table_info_frame_info,
	    SYMBOL_FUNCTION(Qwrite_icon_editor_table_info_frame_info_from_slot),
	    Qslot_value_writer);
    Qicon_editor_button = STATIC_SYMBOL("ICON-EDITOR-BUTTON",AB_package);
    Qgeneric_action_button = STATIC_SYMBOL("GENERIC-ACTION-BUTTON",AB_package);
    list_constant_1 = STATIC_CONS(Qgeneric_action_button,Qnil);
    check_if_superior_classes_are_defined(Qicon_editor_button,list_constant_1);
    string_constant_22 = STATIC_STRING("0");
    string_constant_23 = STATIC_STRING("1m8q1m837+y1l830gy");
    temp = regenerate_optimized_constant(string_constant_22);
    temp_1 = regenerate_optimized_constant(string_constant_22);
    add_class_to_environment(9,Qicon_editor_button,list_constant_1,Nil,
	    temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_23),Nil);
    Qicon_editor_draw_button = STATIC_SYMBOL("ICON-EDITOR-DRAW-BUTTON",
	    AB_package);
    list_constant_2 = STATIC_CONS(Qicon_editor_button,Qnil);
    check_if_superior_classes_are_defined(Qicon_editor_draw_button,
	    list_constant_2);
    string_constant_24 = STATIC_STRING("1m8q1m83*Ty1l837+y");
    temp = regenerate_optimized_constant(string_constant_22);
    temp_1 = regenerate_optimized_constant(string_constant_22);
    add_class_to_environment(9,Qicon_editor_draw_button,list_constant_2,
	    Nil,temp,Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_24),Nil);
    Qbig_icon_editor_text_button = 
	    STATIC_SYMBOL("BIG-ICON-EDITOR-TEXT-BUTTON",AB_package);
    list_constant_3 = STATIC_CONS(Qicon_editor_draw_button,Qnil);
    check_if_superior_classes_are_defined(Qbig_icon_editor_text_button,
	    list_constant_3);
    string_constant_25 = STATIC_STRING("1m8q1m83qVy1l83*Ty");
    temp = regenerate_optimized_constant(string_constant_22);
    temp_1 = regenerate_optimized_constant(string_constant_22);
    add_class_to_environment(9,Qbig_icon_editor_text_button,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_25),Nil);
    Qsmall_icon_editor_text_button = 
	    STATIC_SYMBOL("SMALL-ICON-EDITOR-TEXT-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qsmall_icon_editor_text_button,
	    list_constant_3);
    Qcreate_action_button_description = 
	    STATIC_SYMBOL("CREATE-ACTION-BUTTON-DESCRIPTION",AB_package);
    string_constant_26 = 
	    STATIC_STRING("1l4z8r8u8u83aTy83aTy01o8w9k3uy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_27 = STATIC_STRING("1n8q1m83aTy1l83*Ty1m8u1o8w9k3uy3Qy");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(string_constant_26);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qsmall_icon_editor_text_button,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_27),Nil);
    Qpoints_button = STATIC_SYMBOL("POINTS-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qpoints_button,list_constant_3);
    string_constant_28 = 
	    STATIC_STRING("1l4z8r8u8u83Xty83Xty01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1r83Jy1m3Pyy1m3Py3Cy1m3Ry3Cy1m3Ryy1m3Qyy1m3Qyz001o1l8l1l8o1l8z1m83Dy53YySee");
    string_constant_29 = 
	    STATIC_STRING(" comment on ENTITY class definition00000");
    string_constant_30 = 
	    STATIC_STRING("1n8q1m83Xty1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1r83Jy1m3Pyy1m3Py3Cy1m3Ry3Cy1m3Ryy1m3Qyy1m3Qyz");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_28,
	    string_constant_29));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qpoints_button,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_30),Nil);
    Qline_button = STATIC_SYMBOL("LINE-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qline_button,list_constant_3);
    string_constant_31 = 
	    STATIC_STRING("1l4z8r8u8u83Tuy83Tuy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1n83Oy1muu1m3ky3Gy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class def");
    string_constant_32 = STATIC_STRING("inition00000");
    string_constant_33 = 
	    STATIC_STRING("1n8q1m83Tuy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1n83Oy1muu1m3ky3Gy");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_31,
	    string_constant_32));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qline_button,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_33),Nil);
    Qlines_button = STATIC_SYMBOL("LINES-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qlines_button,list_constant_3);
    string_constant_34 = 
	    STATIC_STRING("1l4z8r8u8u83U*y83U*y01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1p83Oy1muu1m3Qy3Ly1m3Lyw1m3kyr001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTI");
    string_constant_35 = STATIC_STRING("TY class definition00000");
    string_constant_36 = 
	    STATIC_STRING("1n8q1m83U*y1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1p83Oy1muu1m3Qy3Ly1m3Lyw1m3kyr");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_34,
	    string_constant_35));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qlines_button,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_36),Nil);
    Qarc_button = STATIC_SYMBOL("ARC-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qarc_button,list_constant_3);
    string_constant_37 = 
	    STATIC_STRING("1l4z8r8u8u83Gey83Gey01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83Oy1m3Ly3Iy1m83*Hy1m3Yyu1m3Syp001o1l8l1l8o1l8z1m83Dy53YySee comment on E");
    string_constant_38 = STATIC_STRING("NTITY class definition00000");
    string_constant_39 = 
	    STATIC_STRING("1n8q1m83Gey1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83Oy1m3Ly3Iy1m83*Hy1m3Yyu1m3Syp");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_37,
	    string_constant_38));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qarc_button,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_39),Nil);
    Qoutlined_rectangle_button = STATIC_SYMBOL("OUTLINED-RECTANGLE-BUTTON",
	    AB_package);
    check_if_superior_classes_are_defined(Qoutlined_rectangle_button,
	    list_constant_3);
    string_constant_40 = 
	    STATIC_STRING("1l4z8r8u8u83XOy83XOy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1p83Jy1mzp1m3fyp1m3fy3Ly1mz3Ly001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTI");
    string_constant_41 = 
	    STATIC_STRING("1n8q1m83XOy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1p83Jy1mzp1m3fyp1m3fy3Ly1mz3Ly");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_35));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_rectangle_button,list_constant_3,
	    Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_41),Nil);
    Qoutlined_polygon_button = STATIC_SYMBOL("OUTLINED-POLYGON-BUTTON",
	    AB_package);
    check_if_superior_classes_are_defined(Qoutlined_polygon_button,
	    list_constant_3);
    string_constant_42 = 
	    STATIC_STRING("1l4z8r8u8u83XNy83XNy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1s83Jy1muz1m3Dyp1m3byp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly001o1l8l1l8o1l8z1m83D");
    string_constant_43 = 
	    STATIC_STRING("y53YySee comment on ENTITY class definition00000");
    string_constant_44 = 
	    STATIC_STRING("1n8q1m83XNy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1s83Jy1muz1m3Dyp1m3byp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_42,
	    string_constant_43));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_polygon_button,list_constant_3,
	    Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_44),Nil);
    Qoutlined_circle_button = STATIC_SYMBOL("OUTLINED-CIRCLE-BUTTON",
	    AB_package);
    check_if_superior_classes_are_defined(Qoutlined_circle_button,
	    list_constant_3);
    string_constant_45 = 
	    STATIC_STRING("1l4z8r8u8u83XJy83XJy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83*fy1m3Eyz1m3Qyn1m3cyz001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY cl");
    string_constant_46 = STATIC_STRING("ass definition00000");
    string_constant_47 = 
	    STATIC_STRING("1n8q1m83XJy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83*fy1m3Eyz1m3Qyn1m3cyz");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_45,
	    string_constant_46));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_circle_button,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_47),Nil);
    Qfilled_rectangle_button = STATIC_SYMBOL("FILLED-RECTANGLE-BUTTON",
	    AB_package);
    check_if_superior_classes_are_defined(Qfilled_rectangle_button,
	    list_constant_3);
    string_constant_48 = 
	    STATIC_STRING("1l4z8r8u8u83LVy83LVy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1n83jy1mzp1m3fy3Ly001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class def");
    string_constant_49 = 
	    STATIC_STRING("1n8q1m83LVy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1n83jy1mzp1m3fy3Ly");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_48,
	    string_constant_32));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qfilled_rectangle_button,list_constant_3,
	    Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_49),Nil);
    Qfilled_circle_button = STATIC_SYMBOL("FILLED-CIRCLE-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qfilled_circle_button,
	    list_constant_3);
    string_constant_50 = 
	    STATIC_STRING("1l4z8r8u8u83LTy83LTy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83=Ry1m3Eyz1m3Qyn1m3cyz001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY cl");
    string_constant_51 = 
	    STATIC_STRING("1n8q1m83LTy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1o83=Ry1m3Eyz1m3Qyn1m3cyz");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_50,
	    string_constant_46));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qfilled_circle_button,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_51),Nil);
    Qfilled_polygon_button = STATIC_SYMBOL("FILLED-POLYGON-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qfilled_polygon_button,
	    list_constant_3);
    string_constant_52 = 
	    STATIC_STRING("1l4z8r8u8u83LUy83LUy01q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1r83qy1r1muz1m3Dyp1m3ayp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly1n1muz1m3Dyp1m3ayp1");
    string_constant_53 = 
	    STATIC_STRING("n1m3Qy3Dy1m3ky3Dy1m3fy3Ly1n1m3Gy3Ly1m3ayp1m3Qy3Dy1n1m3Qy3Dy1m3fy3Ly1m3Gy3Ly1n1m3Gy3Ly1muz1m3ayp001o1l8l1l8o1l8z1m83Dy53YySee com");
    string_constant_54 = STATIC_STRING("ment on ENTITY class definition00000");
    string_constant_55 = 
	    STATIC_STRING("1n8q1m83LUy1l83*Ty1m8u1q8w9k3uy3Qy1l2l83-ay83Ty1m83-ay1r83qy1r1muz1m3Dyp1m3ayp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly1n1muz1m3Dyp1m3ayp");
    string_constant_56 = 
	    STATIC_STRING("1n1m3Qy3Dy1m3ky3Dy1m3fy3Ly1n1m3Gy3Ly1m3ayp1m3Qy3Dy1n1m3Qy3Dy1m3fy3Ly1m3Gy3Ly1n1m3Gy3Ly1muz1m3ayp");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_52,
	    string_constant_53,string_constant_54));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qfilled_polygon_button,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(LIST_2(string_constant_55,
	    string_constant_56)),Nil);
    Qoutlined_filled_rectangle_button = 
	    STATIC_SYMBOL("OUTLINED-FILLED-RECTANGLE-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qoutlined_filled_rectangle_button,
	    list_constant_3);
    string_constant_57 = 
	    STATIC_STRING("1l4z8r8u8u83XMy83XMy01q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1p83Jy1mzp1m3fyp1m3fy3Ly1mz3Ly83-ay1n83jy1m3Dyr1m3dy3Jy001o1l8l1");
    string_constant_58 = 
	    STATIC_STRING("l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_59 = 
	    STATIC_STRING("1n8q1m83XMy1l83*Ty1m8u1q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1p83Jy1mzp1m3fyp1m3fy3Ly1mz3Ly83-ay1n83jy1m3Dyr1m3dy3Jy");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_57,
	    string_constant_58));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_filled_rectangle_button,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_59),Nil);
    Qoutlined_filled_polygon_button = 
	    STATIC_SYMBOL("OUTLINED-FILLED-POLYGON-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qoutlined_filled_polygon_button,
	    list_constant_3);
    string_constant_60 = 
	    STATIC_STRING("1l4z8r8u8u83XLy83XLy01q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1s83Jy1muz1m3Dyp1m3byp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly83-ay1r83q");
    string_constant_61 = 
	    STATIC_STRING("y1r1mxz1m3Fyr1m3Yyr1m3My3Fy1m3gy3Fy1m3dy3Jy1m3Iy3Jy1n1mxz1m3Fyr1m3Yyr1n1m3My3Fy1m3gy3Fy1m3dy3Jy1n1m3dy3Jy1m3Iy3Jy1mxz1n1mxz1m3Yy");
    string_constant_62 = 
	    STATIC_STRING("r1m3My3Fy1n1m3My3Fy1m3dy3Jy1mxz001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_63 = 
	    STATIC_STRING("1n8q1m83XLy1l83*Ty1m8u1q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1s83Jy1muz1m3Dyp1m3byp1m3Qy3Dy1m3ky3Dy1m3fy3Ly1m3Gy3Ly83-ay1r83");
    string_constant_64 = 
	    STATIC_STRING("qy1r1mxz1m3Fyr1m3Yyr1m3My3Fy1m3gy3Fy1m3dy3Jy1m3Iy3Jy1n1mxz1m3Fyr1m3Yyr1n1m3My3Fy1m3gy3Fy1m3dy3Jy1n1m3dy3Jy1m3Iy3Jy1mxz1n1mxz1m3Y");
    string_constant_65 = STATIC_STRING("yr1m3My3Fy1n1m3My3Fy1m3dy3Jy1mxz");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_60,
	    string_constant_61,string_constant_62));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_filled_polygon_button,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(LIST_3(string_constant_63,
	    string_constant_64,string_constant_65)),Nil);
    Qoutlined_filled_circle_button = 
	    STATIC_SYMBOL("OUTLINED-FILLED-CIRCLE-BUTTON",AB_package);
    check_if_superior_classes_are_defined(Qoutlined_filled_circle_button,
	    list_constant_3);
    string_constant_66 = 
	    STATIC_STRING("1l4z8r8u8u83XKy83XKy01q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1o83*fy1m3Eyz1m3Qyn1m3cyz83-ay1o83=Ry1m3Gyz1m3Qyp1m3ayz001o1l8l1");
    string_constant_67 = 
	    STATIC_STRING("1n8q1m83XKy1l83*Ty1m8u1q8w9k3uy3Qy1m2l832Dy83Ty2l83-ay83Ty1o832Dy1o83*fy1m3Eyz1m3Qyn1m3cyz83-ay1o83=Ry1m3Gyz1m3Qyp1m3ayz");
    temp = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_66,
	    string_constant_58));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_action_button_description);
    add_class_to_environment(9,Qoutlined_filled_circle_button,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_67),Nil);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    list_constant_5 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)160L));
    list_constant_35 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)5L),
	    array_constant,list_constant_5);
    array_constant_1 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    list_constant_6 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)195L));
    list_constant_36 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)6L),
	    array_constant_1,list_constant_6);
    array_constant_2 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    list_constant_7 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)230L));
    list_constant_37 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)7L),
	    array_constant_2,list_constant_7);
    array_constant_3 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    list_constant_8 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)265L));
    list_constant_38 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)19L),
	    array_constant_3,list_constant_8);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)165L),Qnil);
    list_constant_10 = STATIC_CONS(FIX((SI_Long)320L),list_constant_9);
    list_constant_39 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)36L),
	    Qarc_button,list_constant_10);
    list_constant_11 = STATIC_CONS(FIX((SI_Long)385L),list_constant_9);
    list_constant_40 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)33L),
	    Qpoints_button,list_constant_11);
    array_constant_4 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)450L),list_constant_9);
    list_constant_41 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)27L),
	    array_constant_4,list_constant_12);
    array_constant_5 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    list_constant_13 = STATIC_CONS(FIX((SI_Long)515L),list_constant_9);
    list_constant_42 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)28L),
	    array_constant_5,list_constant_13);
    array_constant_6 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    list_constant_14 = STATIC_CONS(FIX((SI_Long)580L),list_constant_9);
    list_constant_43 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)29L),
	    array_constant_6,list_constant_14);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)200L),Qnil);
    list_constant_16 = STATIC_CONS(FIX((SI_Long)320L),list_constant_15);
    list_constant_44 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)35L),
	    Qlines_button,list_constant_16);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)385L),list_constant_15);
    list_constant_45 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)37L),
	    Qoutlined_rectangle_button,list_constant_17);
    list_constant_18 = STATIC_CONS(FIX((SI_Long)450L),list_constant_15);
    list_constant_46 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)39L),
	    Qoutlined_circle_button,list_constant_18);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)515L),list_constant_15);
    list_constant_47 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)38L),
	    Qoutlined_polygon_button,list_constant_19);
    array_constant_7 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)580L),list_constant_15);
    list_constant_48 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)31L),
	    array_constant_7,list_constant_20);
    list_constant_21 = STATIC_CONS(FIX((SI_Long)235L),Qnil);
    list_constant_22 = STATIC_CONS(FIX((SI_Long)320L),list_constant_21);
    list_constant_49 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)34L),
	    Qline_button,list_constant_22);
    list_constant_23 = STATIC_CONS(FIX((SI_Long)385L),list_constant_21);
    list_constant_50 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)40L),
	    Qfilled_rectangle_button,list_constant_23);
    list_constant_24 = STATIC_CONS(FIX((SI_Long)450L),list_constant_21);
    list_constant_51 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)42L),
	    Qfilled_circle_button,list_constant_24);
    list_constant_25 = STATIC_CONS(FIX((SI_Long)515L),list_constant_21);
    list_constant_52 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)41L),
	    Qfilled_polygon_button,list_constant_25);
    array_constant_8 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    list_constant_26 = STATIC_CONS(FIX((SI_Long)580L),list_constant_21);
    list_constant_53 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)30L),
	    array_constant_8,list_constant_26);
    array_constant_9 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    list_constant_27 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)300L));
    list_constant_54 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)8L),
	    array_constant_9,list_constant_27);
    array_constant_10 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    list_constant_28 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)335L));
    list_constant_55 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)9L),
	    array_constant_10,list_constant_28);
    array_constant_11 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    list_constant_29 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)370L));
    list_constant_56 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)10L),
	    array_constant_11,list_constant_29);
    array_constant_12 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    list_constant_30 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)405L));
    list_constant_57 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)11L),
	    array_constant_12,list_constant_30);
    array_constant_13 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    list_constant_31 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)440L));
    list_constant_58 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)57L),
	    array_constant_13,list_constant_31);
    array_constant_14 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    list_constant_32 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)475L));
    list_constant_59 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)58L),
	    array_constant_14,list_constant_32);
    array_constant_15 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    list_constant_33 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)510L));
    list_constant_60 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)59L),
	    array_constant_15,list_constant_33);
    array_constant_16 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    list_constant_34 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)545L));
    list_constant_61 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)56L),
	    array_constant_16,list_constant_34);
    list_constant_62 = STATIC_LIST((SI_Long)27L,list_constant_35,
	    list_constant_36,list_constant_37,list_constant_38,
	    list_constant_39,list_constant_40,list_constant_41,
	    list_constant_42,list_constant_43,list_constant_44,
	    list_constant_45,list_constant_46,list_constant_47,
	    list_constant_48,list_constant_49,list_constant_50,
	    list_constant_51,list_constant_52,list_constant_53,
	    list_constant_54,list_constant_55,list_constant_56,
	    list_constant_57,list_constant_58,list_constant_59,
	    list_constant_60,list_constant_61);
    Icon_editor_buttons_specification_list = list_constant_62;
    Qinfo_box = STATIC_SYMBOL("INFO-BOX",AB_package);
    list_constant_64 = STATIC_CONS(Qicon_editor_table_info_frame_info,Qnil);
    list_constant_63 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_65 = STATIC_CONS(FIX((SI_Long)0L),list_constant_63);
    list_constant_66 = STATIC_CONS(Qt,Qnil);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)4L,Qinfo_box,
	    list_constant_64,list_constant_65,list_constant_66);
    Qsize_table = STATIC_SYMBOL("SIZE-TABLE",AB_package);
    Qicon_editor_table_info_frame_icon_width = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-WIDTH",
	    AB_package);
    Qicon_editor_table_info_frame_icon_height = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-HEIGHT",
	    AB_package);
    Qicon_editor_table_info_frame_global_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-GLOBAL-STIPPLE",
	    AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)3L,
	    Qicon_editor_table_info_frame_icon_width,
	    Qicon_editor_table_info_frame_icon_height,
	    Qicon_editor_table_info_frame_global_stipple);
    list_constant_67 = STATIC_CONS(FIX((SI_Long)50L),Qnil);
    list_constant_69 = STATIC_CONS(FIX((SI_Long)0L),list_constant_67);
    list_constant_75 = STATIC_LIST_STAR((SI_Long)4L,Qsize_table,
	    list_constant_68,list_constant_69,list_constant_66);
    Qlabel_table = STATIC_SYMBOL("LABEL-TABLE",AB_package);
    Qicon_editor_table_info_frame_main_region = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-REGION",
	    AB_package);
    Qicon_editor_table_info_frame_main_color = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-COLOR",
	    AB_package);
    Qicon_editor_table_info_frame_main_image = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-MAIN-IMAGE",
	    AB_package);
    Qicon_editor_table_info_frame_text = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-TEXT",AB_package);
    Qicon_editor_table_info_frame_stipple = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-STIPPLE",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)5L,
	    Qicon_editor_table_info_frame_main_region,
	    Qicon_editor_table_info_frame_main_color,
	    Qicon_editor_table_info_frame_main_image,
	    Qicon_editor_table_info_frame_text,
	    Qicon_editor_table_info_frame_stipple);
    list_constant_71 = STATIC_CONS(FIX((SI_Long)320L),list_constant_63);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)4L,Qlabel_table,
	    list_constant_70,list_constant_71,list_constant_66);
    Qx_y_position_box = STATIC_SYMBOL("X-Y-POSITION-BOX",AB_package);
    Qicon_editor_table_info_frame_x_y_position = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-X-Y-POSITION",
	    AB_package);
    list_constant_72 = 
	    STATIC_CONS(Qicon_editor_table_info_frame_x_y_position,Qnil);
    list_constant_73 = STATIC_CONS(FIX((SI_Long)200L),list_constant_67);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)4L,Qx_y_position_box,
	    list_constant_72,list_constant_73,list_constant_66);
    list_constant_78 = STATIC_LIST((SI_Long)4L,list_constant_74,
	    list_constant_75,list_constant_76,list_constant_77);
    Icon_editor_tables_specification_list = list_constant_78;
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qiconic_entity = STATIC_SYMBOL("ICONIC-ENTITY",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_20 = STATIC_STRING("~(~a~)");
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    Qborder = STATIC_SYMBOL("BORDER",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qx_position_box = STATIC_SYMBOL("X-POSITION-BOX",AB_package);
    Qy_position_box = STATIC_SYMBOL("Y-POSITION-BOX",AB_package);
    Qicon_editor_workspace = STATIC_SYMBOL("ICON-EDITOR-WORKSPACE",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qicon_editor = STATIC_SYMBOL("ICON-EDITOR",AB_package);
    Qbutton_action_data_qm = STATIC_SYMBOL("BUTTON-ACTION-DATA\?",AB_package);
    string_constant_21 = STATIC_STRING("Icon Editor for ~NF");
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,
	    Qicon_editor_table_info_frame_text,
	    Qicon_editor_table_info_frame_stipple);
    Qeditor_scaling = STATIC_SYMBOL("EDITOR-SCALING",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
}
